#include "versions.h"
#include <ultra64.h>
#include "constants.h"
#include "game/camdraw.h"
#include "game/menu.h"
#include "game/crc.h"
#include "game/gamefile.h"
#include "game/pak/pak.h"
#include "game/utils.h"
#include "bss.h"
#include "lib/args.h"
#include "lib/joy.h"
#include "lib/lib_06440.h"
#include "lib/main.h"
#include "lib/memp.h"
#include "lib/rng.h"
#include "data.h"
#include "types.h"

/**
 * Perfect Dark supports saving to an in-cartridge EEPROM chip, as well as to
 * controller paks which can be inserted in any of the four controllers.
 *
 * This file provides an abstraction layer between a generic "pak" and the
 * backend device it uses, and also manages the structure of data within the
 * pak.
 *
 * -- EEPROM --
 *
 * The EEPROM chip is 2KB (0x800 bytes) and is rather simple: The game reads and
 * writes to it using address and length arguments to osEeprom functions.
 *
 * -- Controller Paks --
 *
 * The controller paks are accessed via osPfs functions which are provided by
 * Nintendo. Controller paks use a filesystem and can hold data from other games
 * which is why these functions must be used.
 *
 * Controller paks have a capacity of 256Kbits (32KB). Each controller pak
 * consists of 128 "pages", where each page is a block of 256 bytes. The first
 * 5 pages are reserved for the file allocation table, leaving 123 pages
 * available for game data.
 *
 * Games use osPfsAllocateFile to create a file, also known as a game note.
 * Controller paks can hold up to 16 game notes. Perfect Dark's game note uses
 * 28 pages (7168 bytes). This single game note holds all saved information
 * (game files, MP players and MP games).
 *
 * -- Data Structure --
 *
 * Regardless of whether the data is being written to EEPROM or to a controller
 * pak, the format of it is the same. The data is a list of files, with
 * different lengths based on their file type.
 *
 * Each file has a 16-byte header, followed by its variable length body.
 * The header contains a checksum of the body data, as well as its filetype,
 * size and identifiers.
 *
 * The only way to iterate the files in the filesystem is to read the first
 * file's header (at offset 0), then read its file length out of that header and
 * add it to the offset. Repeat until a PAKFILETYPE_TERMINATOR is found which
 * marks the end of the filesystem. The filesystem may be smaller than the size
 * of the EEPROM or controller pak note.
 *
 * The effective file types are:
 *
 * BOS (length 0x70) - The "boss" file stores things global to all game files,
 *     such as the alternative title setting and chosen language if PAL.
 * GAM (length 0xb0) - Single player game files
 * MPP (length 0x60) - Multiplayer player files
 * MPG (length 0x50) - Multiplayer game setup files
 *
 * Each device can store 4 GAM, MPG and MPP files, and one BOS file. There is
 * additionally a single swap space per game type, making the total usage
 * 1984 bytes (0x7c0), which is 0x30 short of the EEPROM capacity.
 *
 * Controller paks, however, use 28 pages which is 20 pages more than necessary.
 * This is likely because they were going to hold PerfectHead photos, but when
 * the feature was removed the controller pak allocation was not adjusted.
 *
 * -- GUIDs --
 *
 * GUID is an abbreviation for globally unique identifier. GUIDs are used to
 * minimise the chance of the game overwriting a wrong file in the event that
 * a player loads a file from a controller pak, then swaps the controller pak
 * for another during gameplay. By using GUIDs, the game is very likely to
 * detect when this has happened and will prompt the player to reinsert the
 * original pak.
 *
 * When creating a game note on a controller pak, the game generates a serial
 * number for the controller pak. This serial number persists throughout the
 * life of the note. The serial number is saved into the header of every file
 * in that note.
 *
 * Additionally, when creating a file on a pak, the file is given an
 * incrementing ID number which is unique to that pak. That ID is also saved
 * into the header of that file.
 *
 * The combination of the device serial and file ID is the GUID.
 */

#define NUM_PAGES 28

#define MAX_HEADERCACHE_ENTRIES 50

#if VERSION >= VERSION_JPN_FINAL
#define LINE_825  830
#define LINE_1058 1063
#define LINE_1551 1556
#define LINE_1802 1807
#define LINE_3486 3498
#define LINE_3495 3507
#define LINE_3599 3611
#define LINE_3829 3841
#define LINE_3865 3877
#define LINE_3889 3901
#define LINE_3948 3960
#define LINE_4140 4152
#define LINE_4394 4406
#define LINE_4801 4813
#elif VERSION >= VERSION_PAL_BETA
#define LINE_825  825
#define LINE_1058 1058
#define LINE_1551 1551
#define LINE_1802 1802
#define LINE_3486 3493
#define LINE_3495 3502
#define LINE_3599 3606
#define LINE_3829 3836
#define LINE_3865 3872
#define LINE_3889 3896
#define LINE_3948 3955
#define LINE_4140 4147
#define LINE_4394 4401
#define LINE_4801 4808
#elif VERSION >= VERSION_NTSC_FINAL
#define LINE_825  825
#define LINE_1058 1058
#define LINE_1551 1551
#define LINE_1802 1802
#define LINE_3486 3486
#define LINE_3495 3495
#define LINE_3599 3599
#define LINE_3829 3829
#define LINE_3865 3865
#define LINE_3889 3889
#define LINE_3948 3948
#define LINE_4140 4140
#define LINE_4394 4394
#define LINE_4801 4801
#elif VERSION >= VERSION_NTSC_1_0
#define LINE_825  822
#define LINE_1058 1055
#define LINE_1551 1551
#define LINE_1802 1788
#define LINE_3486 3290
#define LINE_3495 3299
#define LINE_3599 3403
#define LINE_3829 3634
#define LINE_3865 3670
#define LINE_3889 3694
#define LINE_3948 3753
#define LINE_4140 3945
#define LINE_4394 4199
#define LINE_4801 4606
#else
#define LINE_825  742
#define LINE_1058 994
#define LINE_1551 1461
#define LINE_1802 1698
#define LINE_3486 3133
#define LINE_3495 3142
#define LINE_3599 3246
#define LINE_3829 3829
#define LINE_3865 3865
#define LINE_3889 3889
#define LINE_3948 3573
#define LINE_4140 3779
#define LINE_4394 4029
#define LINE_4801 4436
#endif

/**
 * In NTSC Beta the functions joyDisableCyclicPolling and joyEnableCyclicPolling
 * take two arguments: __LINE__ and __FILE__. In newer versions of the game
 * these functions take no arguments. This macro is here to avoid using VERSION
 * checks everywhere where these are called.
 */
#if VERSION >= VERSION_NTSC_1_0
#define JOYARGS(line)
#else
#define JOYARGS(line) line, "pak.c"
#endif

const char g_N64FontCodeMap[] = "\0************** 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#'*+,-./:=?@";
const char var7f1b3ad4[] = "Pak %d -> Pak_UpdateAndGetPakNoteInfo - ERROR - ekPakErrorPakFatal\n";
const char var7f1b3b18[] = "Pak %d -> Pak_UpdateAndGetPakNoteInfo - ERROR - ekPakErrorNoPakPresent\n";

struct pak g_Paks[5];

#if VERSION >= VERSION_NTSC_1_0
u32 var800a317c;
#endif

OSPfs g_Pfses[4];
u32 var800a3320;
u32 var800a3324;
u32 var800a3328;
u32 var800a332c;
u32 var800a3330;
u32 var800a3334;
u32 var800a3338;
u32 var800a333c;
u32 var800a3340;
u32 var800a3344;
u32 var800a3348;
u32 var800a334c;
u32 var800a3350;
u32 var800a3354;
u32 var800a3358;
u32 var800a335c;
u32 var800a3360;
u32 var800a3364;
u32 var800a3368;
u32 var800a336c;
u32 var800a3370;
u32 var800a3374;
u32 var800a3378;
u32 var800a337c;
u32 var800a3380;
u32 var800a3384;

#if VERSION != VERSION_NTSC_BETA && VERSION != VERSION_PAL_BETA
// This is likely g_DebugCutsceneLabelPtrs and/or g_DebugCutsceneLabelBuffers
// but with reduced lengths
u32 var800a3388;
u32 var800a338c;
u32 var800a3390;
u32 var800a3394;
u32 var800a3398;
u32 var800a339c;
#endif

#if VERSION >= VERSION_NTSC_1_0
u16 var80075cb0 = ROM_COMPANYCODE;
char var80075cb4[] = "PerfDark";
char var80075cc0[] = "PerfDark";
#else
u16 var80075cb0 = ROM_COMPANYCODE;
u16 var80078054nb = ROM_COMPANYCODE;
char var80078058nb[] = "POCKETCAMERA";
char var80078068nb[] = "GAMEBOYCAMERA";
char var80078078nb[] = "PerfDark";
char var80078084nb[] = "GAMEBOYCAMERA";
#endif

u32 var80075ccc = 0x00000400;
u32 g_PakHasEeprom = false;
u32 var80075cd4 = 0x00000000;
u32 var80075cd8 = 0x00000000;
u32 var80075cdc = 0x00000000;

u32 g_PakDebugForceScrub = 0;
u32 g_PakDebugPakDump = 0;
u32 g_PakDebugPakCache = 1;
u32 g_PakDebugPakInit = 0;

#if VERSION >= VERSION_NTSC_1_0
u32 g_PakDebugWipeEeprom = 0;
u32 g_PakDebugCorruptMe = 0;
#endif

char g_PakNoteGameName[] = {
	N64CHAR('P'),
	N64CHAR('E'),
	N64CHAR('R'),
	N64CHAR('F'),
	N64CHAR('E'),
	N64CHAR('C'),
	N64CHAR('T'),
	N64CHAR(' '),
	N64CHAR('D'),
	N64CHAR('A'),
	N64CHAR('R'),
	N64CHAR('K'),
	0, // fill to 16 bytes
	0,
	0,
	0,
};

char g_PakNoteExtName[] = {0, 0, 0, 0};

u32 var80075d0c = 0x00000000;
u8 var80075d10 = 0;

#if VERSION >= VERSION_NTSC_1_0
u32 var80075d14 = 0x00000001;
#endif

u32 pakGetBlockSize(s8 device)
{
	return device == SAVEDEVICE_GAMEPAK ? 0x10 : 0x20;
}

u32 pakAlign(s8 device, u32 size)
{
	return pakGetBlockSize(device) == 0x20 ? align32(size) : align16(size);
}

void pak0f116650(void)
{
	// empty
}

s32 pakGetAlignedFileLenByBodyLen(s8 device, u32 bodylen)
{
	return pakAlign(device, sizeof(struct pakfileheader) + bodylen);
}

u32 pakGetBodyLenByFileLen(u32 filelen)
{
	return filelen - sizeof(struct pakfileheader);
}

#if VERSION >= VERSION_NTSC_1_0
u32 pakGenerateSerial(s8 device)
{
	s32 value;
	s32 rand;
	s32 count;

	if (device == SAVEDEVICE_GAMEPAK) {
		return 0xbaa;
	}

	value = g_Paks[device].unk2c8;
	rand = (random() % 496) + 16; // range 16-511
	count = osGetCount();

	return value ^ rand ^ count;
}
#endif

bool pakIsMemoryPak(s8 device)
{
	if (g_Paks[device].type == PAKTYPE_MEMORY) {
		switch (g_Paks[device].unk010) {
		case PAK010_14:
		case PAK010_15:
		case PAK010_19:
		case PAK010_20:
		case PAK010_22:
			return false;
		}

		return true;
	}

	return false;
}

s32 pakGetFileIdsByType(s8 device, u32 filetype, u32 *fileids)
{
	return _pakGetFileIdsByType(device, filetype, fileids);
}

s32 pak0f1167d8(s8 device)
{
	return pak0f119298(device);
}

s32 pakReadBodyAtGuid(s8 device, s32 fileid, u8 *body, s32 arg3)
{
	return _pakReadBodyAtGuid(device, fileid, body, arg3);
}

s32 pakSaveAtGuid(s8 device, s32 fileid, s32 filetype, u8 *body, s32 *outfileid, u8 *olddata)
{
	return _pakSaveAtGuid(device, fileid, filetype, body, outfileid, olddata);
}

bool pakDeleteFile(s8 device, s32 fileid)
{
	return _pakDeleteFile(device, fileid);
}

s32 pakDeleteGameNote(s8 device, u16 company_code, u32 game_code, char *game_name, char *ext_name)
{
	return _pakDeleteGameNote(device, company_code, game_code, game_name, ext_name);
}

s32 pak0f1168c4(s8 device, struct pakdata **arg1)
{
	return pak0f116df0(device, arg1);
}

s32 pakCreateCameraFile(s8 device, s32 *outfileid)
{
	return _pakCreateCameraFile(device, outfileid);
}

u32 pakGetType(s8 device)
{
	return _pakGetType(device);
}

s32 pakGetSerial(s8 device)
{
	return _pakGetSerial(device);
}

void pak0f116984(s8 arg0, u8 *arg1, u8 *arg2)
{
	pak0f116bdc(arg0, arg1, arg2);
}

void pak0f11698c(s8 device)
{
	// empty
}

#if VERSION >= VERSION_NTSC_1_0
void pak0f116994(void)
{
	if (g_Vars.stagenum == STAGE_BOOTPAKMENU) {
		g_Vars.unk0004e4 = 0xf8;
	}
}
#endif

#if VERSION >= VERSION_NTSC_1_0
void pak0f1169bc(u32 arg0, u32 arg1)
{
	// empty
}
#endif

void pak0f1169c8(s8 device, s32 arg1)
{
#if VERSION >= VERSION_NTSC_1_0
	u8 prevvalue = g_Vars.paksconnected;

	g_Vars.paksconnected = 0x1f;

	if ((g_Vars.paksconnected2 | g_Vars.paksconnected) & (1 << device)) {
		var80075d10 &= ~(1 << device);

		pak0f11ca30();
		pak0f11ca30();

		if (arg1) {
			var8005eedc = false;

			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);

			var8005eedc = true;
		}
	}

	g_Vars.paksconnected = prevvalue;
#else
	if ((g_Vars.paksconnected2 | g_Vars.paksconnected) & (1 << device)) {
		var80075d10 &= ~(1 << device);

		pak0f11ca30();

		if (arg1) {
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
			pak0f11df94(device);
		}
	}
#endif
}

bool pak0f116aec(s8 device)
{
	if (g_Paks[device].unk010 == PAK010_11 && g_Paks[device].type == PAKTYPE_MEMORY) {
		return true;
	}

	return false;
}

bool pak0f116b5c(s8 device)
{
	if ((g_Paks[device].unk010 == PAK010_11
				|| g_Paks[device].unk010 == PAK010_16
				|| g_Paks[device].unk010 == PAK010_21)
			&& g_Paks[device].type == PAKTYPE_MEMORY) {
		return true;
	}

	return false;
}

void pak0f116bdc(s8 device, u8 *arg1, u8 *arg2)
{
	*arg1 = g_Paks[device].unk2ba;
	*arg2 = g_Paks[device].unk2bb;
}

void pak0f116c2c(s8 index)
{
	joySetPfsTemporarilyPlugged(index);
}

u16 _pakGetSerial(s8 device)
{
	return g_Paks[device].serial;
}

u32 _pakGetType(s8 device)
{
	return g_Paks[device].type;
}

ubool pak0f116cd4(s8 device)
{
	pak0f11d620(device);

	return g_Paks[device].unk2b8_05 && g_Paks[device].unk2b8_03;
}

ubool pak0f116d4c(s8 device)
{
	return g_Paks[device].unk2b8_05 && g_Paks[device].unk2b8_03 == 0;
}

void pakSetUnk010(s8 device, s32 value)
{
	g_Paks[device].unk010 = value;
}

s32 pak0f116df0(s8 device, struct pakdata **pakdata)
{
	*pakdata = NULL;

	if (pak0f116b5c(device)) {
		if (pakQueryTotalUsage(device)) {
			*pakdata = &g_Paks[device].pakdata;
			return 0;
		}

		return 2;
	}

	return 1;
}

s32 _pakDeleteGameNote(s8 device, u16 company_code, u32 game_code, char *game_name, char *ext_name)
{
	s32 result;

	if (pak0f116b5c(device)) {
		joyDisableCyclicPolling(JOYARGS(738));
		result = pakDeleteGameNote3(PFS(device), company_code, game_code, game_name, ext_name);
		joyEnableCyclicPolling(JOYARGS(740));

		if (pakHandleResult(result, device, true, LINE_825)) {
			g_Paks[device].unk2b8_02 = 1;
			return 0;
		}

		return 2;
	}

	return 1;
}

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b3b60[] = "-> Unknown PakFileType_e - %d\n";
#else
const char var7f1b3b60[] = "-> Unknown PakFileType_e - %d";
#endif

#if VERSION < VERSION_NTSC_1_0
const char var7f1ad850nb[] = "Bad     ";
const char var7f1ad85cnb[] = "Blank   ";
const char var7f1ad868nb[] = "Swap    ";
const char var7f1ad874nb[] = "Camera  ";
const char var7f1ad880nb[] = "GmSetup ";
const char var7f1ad88cnb[] = "Boss    ";
const char var7f1ad898nb[] = "Multi Pl";
const char var7f1ad8a4nb[] = "Multi Gm";
const char var7f1ad8b0n0[] = "????????";
#endif

#if VERSION >= VERSION_NTSC_1_0
s32 _pakDeleteFile(s8 device, s32 fileid)
{
	struct pakfileheader header;
	s32 result = pakFindFile(device, fileid, &header);

	if (result == -1) {
		return 1;
	}

	result = pakWriteFileAtOffset(device, result, header.filetype, NULL, 0, NULL, NULL, 0, header.generation + 1);

	if (result) {
		return result;
	}

	return 0;
}
#else
s32 _pakDeleteFile(s8 device, s32 fileid)
{
	struct pakfileheader header;
	u32 result;
	u32 tmp = pakFindFile(device, fileid, &header);

	if (tmp && (!tmp || tmp >= pakGetPdNumBytes(device) || (pakGetBlockSize(device) - 1U & tmp))) {
		return 3;
	}

	result = pakWriteFileAtOffset(device, tmp, header.filetype, NULL, 0, NULL, NULL, 0, header.generation + 1);

	if (result) {
		return result;
	}

	return 0;
}
#endif

s32 pakGetUnk264(s8 device)
{
	return g_Paks[device].unk264;
}

u32 pakGetMaxFileSize(s8 device)
{
	if (device != SAVEDEVICE_GAMEPAK) {
		return 0x4c0;
	}

	return 0x100;
}

s32 pakGetBodyLenByType(s8 device, u32 filetype)
{
	s32 len = 0;

	switch (filetype) {
	case PAKFILETYPE_001:
	case PAKFILETYPE_BLANK:
		break;
	case PAKFILETYPE_TERMINATOR:
		len = pakGetMaxFileSize(device) - sizeof(struct pakfileheader);
		break;
	case PAKFILETYPE_BOSS:
		len = 0x5b;
		break;
	case PAKFILETYPE_MPPLAYER:
		len = 0x4e;
		break;
	case PAKFILETYPE_MPSETUP:
		len = 0x31;
		break;
	case PAKFILETYPE_CAMERA:
		len = 0x4a0;
		break;
	case PAKFILETYPE_GAME:
		len = 0xa0;
		break;
	}

	return len;
}

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f1114a0nb
.late_rodata
glabel var7f1aefa8nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefacnb
.word pak0f1114a0nb+0x5c
glabel var7f1aefb0nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefb4nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefb8nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefbcnb
.word pak0f1114a0nb+0x5c
glabel var7f1aefc0nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefc4nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefc8nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefccnb
.word pak0f1114a0nb+0x5c
glabel var7f1aefd0nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefd4nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefd8nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefdcnb
.word pak0f1114a0nb+0x5c
glabel var7f1aefe0nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefe4nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefe8nb
.word pak0f1114a0nb+0x5c
glabel var7f1aefecnb
.word pak0f1114a0nb+0x5c
glabel var7f1aeff0nb
.word pak0f1114a0nb+0x5c
glabel var7f1aeff4nb
.word pak0f1114a0nb+0x5c
glabel var7f1aeff8nb
.word pak0f1114a0nb+0x5c
glabel var7f1aeffcnb
.word pak0f1114a0nb+0x5c
glabel var7f1af000nb
.word pak0f1114a0nb+0x5c
glabel var7f1af004nb
.word pak0f1114a0nb+0x5c
glabel var7f1af008nb
.word pak0f1114a0nb+0x5c
glabel var7f1af00cnb
.word pak0f1114a0nb+0x5c
glabel var7f1af010nb
.word pak0f1114a0nb+0x5c
glabel var7f1af014nb
.word pak0f1114a0nb+0x5c
glabel var7f1af018nb
.word pak0f1114a0nb+0x5c
glabel var7f1af01cnb
.word pak0f1114a0nb+0x5c
glabel var7f1af020nb
.word pak0f1114a0nb+0x5c
glabel var7f1af024nb
.word pak0f1114a0nb+0x5c
.text
/*  f1114a0:	2c810041 */ 	sltiu	$at,$a0,0x41
/*  f1114a4:	14200005 */ 	bnez	$at,.NB0f1114bc
/*  f1114a8:	24010080 */ 	addiu	$at,$zero,0x80
/*  f1114ac:	10810013 */ 	beq	$a0,$at,.NB0f1114fc
/*  f1114b0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1114b4:	03e00008 */ 	jr	$ra
/*  f1114b8:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f1114bc:
/*  f1114bc:	2c810021 */ 	sltiu	$at,$a0,0x21
/*  f1114c0:	14200006 */ 	bnez	$at,.NB0f1114dc
/*  f1114c4:	248effff */ 	addiu	$t6,$a0,-1
/*  f1114c8:	24010040 */ 	addiu	$at,$zero,0x40
/*  f1114cc:	1081000b */ 	beq	$a0,$at,.NB0f1114fc
/*  f1114d0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1114d4:	03e00008 */ 	jr	$ra
/*  f1114d8:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f1114dc:
/*  f1114dc:	2dc10020 */ 	sltiu	$at,$t6,0x20
/*  f1114e0:	10200006 */ 	beqz	$at,.NB0f1114fc
/*  f1114e4:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1114e8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f1114ec:	002e0821 */ 	addu	$at,$at,$t6
/*  f1114f0:	8c2eefa8 */ 	lw	$t6,-0x1058($at)
/*  f1114f4:	01c00008 */ 	jr	$t6
/*  f1114f8:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f1114fc:
/*  f1114fc:	03e00008 */ 	jr	$ra
/*  f111500:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

void pak0f117150(s8 device, u8 *ptr)
{
	s32 i;

	g_Paks[device].unk2c4 = ptr;

	for (i = 0; i < 4096; i++) {
		g_Paks[device].unk2c4[i] = 0;
	}
}

void pak0f1171b4(s8 device, s32 arg1, s32 arg2)
{
	g_Paks[device].unk00c = arg1;
	g_Paks[device].unk2b8_06 = arg2;
}

s32 pakGetUnk008(s8 device)
{
	return g_Paks[device].unk008;
}

void pakSetUnk008(s8 device, s32 value)
{
	g_Paks[device].unk008 = value;
}

s32 pakGetUnk270(s8 device)
{
	return g_Paks[device].unk270;
}

s32 pakGetRumbleState(s8 device)
{
	return g_Paks[device].rumblestate;
}

void pakSetRumbleState(s8 device, s32 state)
{
	g_Paks[device].rumblestate = state;
}

s32 pak0f117350(s8 device)
{
	return g_Paks[device].unk2b8_01;
}

void pak0f117398(s8 device)
{
	g_Paks[device].unk2b8_01 = 1;
}

void pak0f1173e4(s8 device)
{
	g_Paks[device].unk2b8_01 = 0;
}

bool pakRetrieveBlockFromCache(s8 device, u32 offset, u8 *dst)
{
	u32 blocksize = pakGetBlockSize(device);
	u32 stack;
	s32 i;

	if (g_Paks[device].headercachecount < MAX_HEADERCACHE_ENTRIES) {
		for (i = 0; i < g_Paks[device].headercachecount; i++) {
			if (offset / blocksize == g_Paks[device].headercache[i].blocknum) {
				memcpy(dst, g_Paks[device].headercache[i].payload, pakGetBlockSize(device));
				return true;
			}
		}
	}

	return false;
}

PakErr2 pakReadHeaderAtOffset(s8 device, u32 offset, struct pakfileheader *header)
{
	struct pakfileheader localheader;
	struct pakfileheader *headerptr;
	u32 blocknum;
	s32 result;
	u16 checksum[2];
	u8 sp38[0x20];

	headerptr = header ? header : &localheader;

	blocknum = offset / pakGetBlockSize(device);

	if (blocknum >= g_Paks[device].pdnumblocks) {
		return PAK_ERR2_BADOFFSET;
	}

	if (!pakRetrieveHeaderFromCache(device, blocknum, headerptr)) {
		result = pakReadWriteBlock(device, PFS(device), g_Paks[device].pdnoteindex, 0, offset, sizeof(sp38), sp38);

		if (pakHandleResult(result, device, true, LINE_1058) == 0) {
			if (result == PAK_ERR1_NOPAK) {
				return PAK_ERR2_NOPAK;
			}

			return PAK_ERR2_BADOFFSET;
		}

		memcpy(headerptr, sp38, sizeof(struct pakfileheader));
		pakCalculateChecksum(&sp38[0x08], &sp38[0x10], checksum);

		if (headerptr->headersum[0] != checksum[0] || headerptr->headersum[1] != checksum[1]) {
			return PAK_ERR2_CHECKSUM;
		}

		if (!headerptr->writecompleted) {
			return PAK_ERR2_INCOMPLETE;
		}

		if ((argFindByPrefix(1, "-forceversion") ? 1 : 0) != headerptr->version) {
			return PAK_ERR2_VERSION;
		}

		if (g_PakDebugPakCache) {
			pakSaveHeaderToCache(device, blocknum, (struct pakfileheader *) sp38);

			if (!pakRetrieveHeaderFromCache(device, blocknum, headerptr)) {
#if VERSION >= VERSION_NTSC_1_0
				osSyncPrintf("Pak %d -> Header Cache 2 - FATAL ERROR\n");
#else
				osSyncPrintf("Pak %d -> Header Cache 2 - FATAL ERROR");
#endif
				return PAK_ERR2_CORRUPT;
			}
		}
	}

	if (headerptr->filelen == 0) {
		return PAK_ERR2_CORRUPT;
	}

	return PAK_ERR2_OK;
}

void pakDumpBuffer(u8 *buffer, u32 len, char *name)
{
	s32 i;
	char line[256];
	char tmp[256];

	osSyncPrintf(name);
	sprintf(line, "\n");

	for (i = 0; i != len; i++) {
		if ((i % 16) == 0) {
			osSyncPrintf(line);
			sprintf(line, "\nAddress = %u : ", i);
		}

		sprintf(tmp, "%2x ", buffer[i]);
		strcat(line, tmp);
	}

	strcat(line, "\n");

	osSyncPrintf(line);
}

void pakDumpEeprom(void)
{
	u8 buffer[2048];

	joyDisableCyclicPolling(JOYARGS(1098));
	osEepromLongRead(&g_PiMesgQueue, 0, buffer, 2048);
	joyEnableCyclicPolling(JOYARGS(1100));

	pakDumpBuffer(buffer, 2048, "EEPROM DUMP");
}

/**
 * Overwrite the save file which has the specified fileid. This is typically an
 * earlier version of the same logical save file. A new fileid will be generated
 * and returned to *outfileid.
 *
 * The function doesn't literally overwrite the old file. On the pak, there is
 * a swap file reserved for atomic writes. The new file is written into the
 * swap file, then the old file is marked as swap.
 */
s32 _pakSaveAtGuid(s8 device, s32 fileid, s32 filetype, u8 *newdata, s32 *outfileid, u8 *olddataptr)
{
	struct pakfileheader header;
	struct pakfileheader swapheader;
	s32 result;
	s32 oldoffset;
	s32 i;
	s32 swapoffset;
	u32 fileids[1024];
	s32 swapfileid = 0;
	u8 olddata[0x800];

	// Find the file to be "replaced"
	oldoffset = pakFindFile(device, fileid, &header);

	if (oldoffset && (!oldoffset || oldoffset >= pakGetPdNumBytes(device) || (pakGetBlockSize(device) - 1 & oldoffset))) {
		return 3;
	}

	if (filetype != header.filetype) {
		return 12;
	}

	// Find all files on the pak of the same filetype,
	// then iterate them to find the swap file
	pakGetFileIdsByType(device, header.filetype, fileids);

	// NTSC Beta initialises swapoffset to -1 so it can detect if the loop below
	// has been entered. But in NTSC 1.0 they realised that pakFindFile can
	// return -1, so they initialised the variable to 0xeeeeeeee instead and
	// added the check for -1 in the loop below.
#if VERSION >= VERSION_NTSC_1_0
	swapoffset = 0xeeeeeeee;
#else
	swapoffset = -1;
#endif

	for (i = 0; fileids[i] != 0; i++) {
		swapoffset = pakFindFile(device, fileids[i], &swapheader);

#if VERSION >= VERSION_NTSC_1_0
		if (swapoffset == -1) {
			return 1;
		}
#endif

		if (!swapheader.occupied && swapheader.fileid != fileid) {
			// Found the swap file
			swapfileid = swapheader.fileid;
			break;
		}
	}

	// For the game pak, don't trust the olddataptr argument and instead
	// populate it by loading the data at the swap file (olddataptr is used to
	// skip writes if any old and new blocks are matching).
	// @bug? Shouldn't this also apply to controller paks? How would the caller
	// know which swap space was going to be used? Maybe controller paks don't
	// use the olddataptr optimisation?
	if (device == SAVEDEVICE_GAMEPAK) {
		result = pakReadBodyAtGuid(device, swapfileid, olddata, -1);

		// NTSC 1.0 just writes the same thing a different way
#if VERSION >= VERSION_NTSC_1_0
		if (result == 0) {
			olddataptr = olddata;
		} else if (result == 10) {
			olddataptr = olddata;
		} else {
			olddataptr = NULL;
		}
#else
		if (result == 0 || result == 10) {
			olddataptr = olddata;
		} else {
			olddataptr = NULL;
		}
#endif
	}

	// Write the new file into the swap space
	result = pakWriteFileAtOffset(device, swapoffset, filetype, newdata, 0, outfileid, olddataptr, fileid, header.generation + 1);

	if (result != 0) {
		return 4;
	}

	if (outfileid) {
		osSyncPrintf("PakSaveAtGuid: new guid = %x\n", outfileid);
	}

	// NTSC Beta skips marking the old file as vacant if the file wasn't found
	// and returns an OK value. NTSC Final makes it return an error instead.
	// @bug: The 0xeeeeeeee check should have been done earlier for swapoffset
	// instead. As it turns out, if swap space wasn't found then
	// pakWriteFileAtOffset would have returned an error above and this function
	// would have returned before this check occurs. And oldoffset will never be
	// 0xeeeeeeee (even with 4GB of storage) because 0xeeeeeeee is not aligned
	// to a 16-byte boundary. So this bug is harmless.
#if VERSION >= VERSION_NTSC_1_0
	if (oldoffset == -1) {
		return 1;
	}

	if (oldoffset != 0xeeeeeeee) {
		pakWriteFileAtOffset(device, oldoffset, filetype, NULL, 0, NULL, NULL, swapfileid, header.generation);
	}
#else
	if (oldoffset != -1) {
		pakWriteFileAtOffset(device, oldoffset, filetype, NULL, 0, NULL, NULL, swapfileid, header.generation);
	}
#endif

	return 0;
}

#if VERSION >= VERSION_NTSC_1_0
PakErr1 pakInitPak(OSMesgQueue *mq, OSPfs *pfs, s32 channel, s32 *arg3)
#else
PakErr1 pakInitPak(OSMesgQueue *mq, OSPfs *pfs, s32 channel)
#endif
{
	if (pfs) {
#if VERSION >= VERSION_NTSC_1_0
		return osPfsInitPak(mq, pfs, channel, arg3);
#else
		return osPfsInitPak(mq, pfs, channel);
#endif
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	return PAK_ERR1_OK;
}

PakErr1 _pakReadWriteBlock(OSPfs *pfs, s32 file_no, u8 flag, u32 address, u32 len, u8 *buffer)
{
	u32 newaddress;

#if VERSION >= VERSION_NTSC_1_0
	joyCheckPfs(2);
#endif

	if (pfs) {
		return osPfsReadWriteFile(pfs, file_no, flag, address, len, buffer);
	}

	newaddress = address / 8;

	if (newaddress >= 256) {
#if VERSION < VERSION_NTSC_1_0
		u32 stack;
		crashSetMessage("ILLEGAL EEPROM ADDRESS (>=256)");
		CRASH();
#endif
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	if (flag == OS_WRITE) {
		return pakWriteEeprom(newaddress, buffer, len);
	}

	if (flag == OS_READ) {
		return pakReadEeprom(newaddress, buffer, len);
	}

	return PAK_ERR1_EEPROMINVALIDOP;
}

PakErr1 pakQueryNumNotes(OSPfs *pfs, s32 *max_files, s32 *files_used)
{
	if (pfs) {
		s32 result;

		joyDisableCyclicPolling(JOYARGS(1308));
		result = osPfsNumFiles(pfs, max_files, files_used);
		joyEnableCyclicPolling(JOYARGS(1310));

		return result;
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	*max_files = 1;
	*files_used = 1;

	return PAK_ERR1_OK;
}

PakErr1 pakQueryNumFreeBytes(OSPfs *pfs, s32 *bytes_not_used)
{
	if (pfs) {
		s32 result;

		joyDisableCyclicPolling(JOYARGS(1337));
		result = osPfsFreeBlocks(pfs, bytes_not_used);
		joyEnableCyclicPolling(JOYARGS(1339));

		return result;
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	*bytes_not_used = 0;

	return PAK_ERR1_OK;
}

PakErr1 pakQueryNoteState(OSPfs *pfs, s32 file_no, OSPfsState *note)
{
	if (pfs) {
		s32 result;

		joyDisableCyclicPolling(JOYARGS(1363));
		result = osPfsFileState(pfs, file_no, note);
		joyEnableCyclicPolling(JOYARGS(1365));

		return result;
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	if (file_no) {
		return PAK_ERR1_EEPROMINVALIDARG;
	}

	note->file_size = 0x800;
	note->company_code = ROM_COMPANYCODE;
	strcpy(note->game_name, g_PakNoteGameName);
	strcpy(note->ext_name, g_PakNoteExtName);

	return PAK_ERR1_OK;
}

const char var7f1b3c08[] = "Call to osPfsReSizeFile -> pfs=%x, cc=%u, gc=%u, gn=%s, en=%s, l=%d\n";

PakErr1 pakAllocateNote(OSPfs *pfs, u16 company_code, u32 game_code, char *game_name, char *ext_name, s32 size, s32 *file_no)
{
	if (pfs) {
		return osPfsAllocateFile(pfs, company_code, game_code, game_name, ext_name, size, file_no);
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	*file_no = 0;

	return PAK_ERR1_OK;
}

PakErr1 pakDeleteGameNote3(OSPfs *pfs, u16 company_code, u32 game_code, char *game_name, char *ext_name)
{
	if (pfs) {
		return osPfsDeleteFile(pfs, company_code, game_code, game_name, ext_name);
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	return PAK_ERR1_OK;
}

PakErr1 pakFindNote(OSPfs *pfs, u16 company_code, u32 game_code, char *game_name, char *ext_name, s32 *file_no)
{
	if (pfs) {
		return osPfsFindFile(pfs, company_code, game_code, game_name, ext_name, file_no);
	}

	if (g_PakHasEeprom) {
#if VERSION >= VERSION_NTSC_FINAL
		*file_no = 0;
		return PAK_ERR1_OK;
#else
		u8 sp64[8];
		u32 ret;
		u16 sp56[2];
		u32 b;
		u16 sp44[4];

		*file_no = 0;
		ret = pakReadWriteBlock(SAVEDEVICE_GAMEPAK, 0, 0, 0, 0, align16(0x10), (u8 *)sp56);

		if (pakHandleResult(ret, SAVEDEVICE_GAMEPAK, true, LINE_1551)) {
			pakCalculateChecksum(sp64, sp64 + sizeof(sp64), sp44);

			if (sp56[0] == sp44[0] && sp56[1] == sp44[1]) {
				return PAK_ERR1_OK;
			}

			return PAK_ERR1_EEPROMINVALIDARG;
		}

		return PAK_ERR1_EEPROMINVALIDARG;
#endif
	}

	return PAK_ERR1_EEPROMMISSING;
}

PakErr1 _pakResizeNote(OSPfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, u32 numbytes)
{
	if (pfs) {
		s32 result;

		joyDisableCyclicPolling(JOYARGS(1496));
		result = osPfsReSizeFile(pfs, company_code, game_code, game_name, ext_name, numbytes);
		joyEnableCyclicPolling(JOYARGS(1498));

		return result;
	}

	if (!g_PakHasEeprom) {
		return PAK_ERR1_EEPROMMISSING;
	}

	return PAK_ERR1_OK;
}

const char var7f1b3c50[] = "Pak %d -> Pak_AddOneCameraFile\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b3c70[] = "Pak %d -> Pak_AddOneCameraFile - Making one default camera file\n";
#else
const char var7f1b3c70[] = "Pak %d -> Pak_AddOneCameraFile - Making one default camera file";
#endif

const char var7f1b3cb4[] = "Pak %d -> Pak_AddOneCameraFile : Got Space - No need for resize\n";
const char var7f1b3cf8[] = "Pak %d -> Pak_AddOneCameraFile : No Space - Need to resize by %d pages\n";
const char var7f1b3d40[] = "Pak %d -> Pak_AddOneCameraFile - Make of one default camera files failed\n";
const char var7f1b3d8c[] = "Pak %d -> Pak_AddOneCameraFile : Error - No Room\n";
const char var7f1b3dc0[] = "Pak %d -> Pak_GameNoteResetSize : New=%u\n";
const char var7f1b3dec[] = "bDoUpdate7\n";
const char var7f1b3df8[] = "Pak_SetThisGameSetupFile -> Pak=%d, File=%d, EEPROM=%d\n";

#if VERSION < VERSION_NTSC_1_0
const char var7f1adbd8nb[] = "RWI : Pak_OneNewFile - Using a snug in a bug offset\n";
const char var7f1adc10nb[] = "pak.c";
const char var7f1adc18nb[] = "Pak_Make -> Dumping details of file types found\n";
const char var7f1adc4cnb[] = "Type %d -> ";
const char var7f1adc58nb[] = ", dSize=%u, fSize=%u\n";
const char var7f1adc70nb[] = "Pak_Make -> Checking for inserted pakz\n";
const char var7f1adc98nb[] = "Pak_Make -> Loading Boss File\n";
const char var7f1adcb8nb[] = "Pak_Make -> Boss file load failed - Try to make a new one\n";
const char var7f1adcf4nb[] = "Pak_Make -> Setting up default game file\n";
#endif

s32 pakGetPdNumBlocks(s8 device)
{
	return g_Paks[device].pdnumblocks;
}

s32 pakGetPdNumPages(s8 device)
{
	return g_Paks[device].pdnumpages;
}

u32 pakGetPdNumBytes(s8 device)
{
	return g_Paks[device].pdnumbytes;
}

s32 pakQueryNumFreePages(s8 device)
{
	s32 bytesfree;

	pakQueryNumFreeBytes(PFS(device), &bytesfree);

	return bytesfree / 256;
}

s32 pakGetNumPagesRequired(void)
{
	return NUM_PAGES;
}

/**
 * Determine if the pak could accommodate a new camera file,
 * considering the possibility of resizing the game note to make it larger.
 */
bool pakCanFitCameraFileInPak(s8 device)
{
	if (device != SAVEDEVICE_GAMEPAK) {
		s32 pagesneeded;
		u32 bytesneeded = pakGetMaxFileSize(device);

		if (pakCheckFileCanFitInNote(device, PAKFILETYPE_CAMERA, NULL) == 0) {
			return true;
		}

		pagesneeded = bytesneeded / 256;

		if (bytesneeded & 0xff) {
			pagesneeded++;
		}

		if (g_Paks[device].pakdata.pagesused + pagesneeded < 128) {
			return (g_Paks[device].pakdata.pagesfree >= pagesneeded);
		}
	}

	return false;
}

/**
 * Determine how many camera files the pak could accommodate,
 * considering the possibility of resizing the game note to make it larger.
 */
s32 pakGetNumFreeCameraSpacesInPak(s8 device)
{
	if (device != SAVEDEVICE_GAMEPAK) {
		s32 numspaces = 0;
		s32 pagesneeded;
		u32 bytesneeded;

		bytesneeded = pakGetMaxFileSize(device);
		pakCheckFileCanFitInNote(device, PAKFILETYPE_CAMERA, &numspaces);
		pagesneeded = bytesneeded / 256;

		if (bytesneeded & 0xff) {
			pagesneeded++;
		}

		// 128 is the total number of pages on a controller pak
		numspaces += (128 - g_Paks[device].pakdata.pagesused) / pagesneeded;

		return numspaces;
	}

	return 0;
}

s32 _pakCreateCameraFile(s8 device, s32 *outfileid)
{
	if (device != SAVEDEVICE_GAMEPAK && pakCanFitCameraFileInPak(device)) {
		s32 result;
		u32 bytesneeded = pakGetMaxFileSize(device);

		if (pakCheckFileCanFitInNote(device, PAKFILETYPE_CAMERA, NULL) != 0) {
			s32 pages = pakGetPdNumPages(device);
			s32 pagesneeded = bytesneeded / 256;

			if (bytesneeded & 0xff) {
				pagesneeded++;
			}

			pages += pagesneeded;

			if (!pakResizeNote(device, pages)) {
				return 4;
			}
		}

		result = pak0f118674(device, PAKFILETYPE_CAMERA, outfileid);

		if (result) {
			return result;
		}

		return 0;
	}

	return 14;
}

bool pakResizeNote(s8 device, s32 numpages)
{
	s32 stack1[2];
	s32 errno;
	struct pak *devicedata;
	s32 stack2[2];
	OSPfsState *note;
	u32 numbytes;

	pakGetPdNumPages(device);
	pakQueryNumFreePages(device);

	numbytes = numpages * 256;
	errno = _pakResizeNote(PFS(device), ROM_COMPANYCODE, ROM_GAMECODE, g_PakNoteGameName, g_PakNoteExtName, numbytes);
	pakHandleResult(errno, device, true, LINE_1802);

	if (errno == PAK_ERR1_OK) {
		devicedata = &g_Paks[device];
		note = &devicedata->pakdata.notes[devicedata->pdnoteindex];

		devicedata->pakdata.pagesfree -= numpages - devicedata->pdnumpages;
		devicedata->pakdata.pagesused += numpages - devicedata->pdnumpages;

		note->file_size = devicedata->pakdata.pagesused * 256;

		devicedata->pdnumbytes = numbytes;
		devicedata->pdnumblocks = devicedata->pdnumbytes / pakGetBlockSize(device);
		devicedata->pdnumpages = devicedata->pdnumbytes / 256;

		return true;
	}

	return false;
}

void pak0f1184d8(s8 device, u32 *arg1, bool *arg2)
{
	if (device != SAVEDEVICE_GAMEPAK) {
		if (g_Paks[device].type != PAKTYPE_MEMORY || g_Paks[device].unk010 != PAK010_11) {
			pak0f1185e0(device, g_Paks[SAVEDEVICE_GAMEPAK].unk2bd & 0x0f, 1);
			device = SAVEDEVICE_GAMEPAK;
		}
	}

	if (g_Paks[device].unk2bd & 0x80) {
		*arg2 = true;
	} else {
		*arg2 = false;
	}

	*arg1 = g_Paks[device].unk2bd & 0x0f;
}

void pak0f1185e0(s8 device, s32 arg1, s32 arg2)
{
	if (arg2) {
		g_Paks[device].unk2bd = 0x80;
	} else {
		g_Paks[device].unk2bd = 0;
	}

	g_Paks[device].unk2bd += arg1;
}

#if VERSION >= VERSION_NTSC_FINAL
GLOBAL_ASM(
glabel pak0f118674
/*  f118674:	27bdff80 */ 	addiu	$sp,$sp,-128
/*  f118678:	afb20038 */ 	sw	$s2,0x38($sp)
/*  f11867c:	00049600 */ 	sll	$s2,$a0,0x18
/*  f118680:	00127603 */ 	sra	$t6,$s2,0x18
/*  f118684:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f118688:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f11868c:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f118690:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f118694:	01c09025 */ 	or	$s2,$t6,$zero
/*  f118698:	afb10034 */ 	sw	$s1,0x34($sp)
/*  f11869c:	afb00030 */ 	sw	$s0,0x30($sp)
/*  f1186a0:	afa50084 */ 	sw	$a1,0x84($sp)
/*  f1186a4:	afa60088 */ 	sw	$a2,0x88($sp)
/*  f1186a8:	0fc45c25 */ 	jal	pakGetBodyLenByType
/*  f1186ac:	01e02025 */ 	or	$a0,$t7,$zero
/*  f1186b0:	00122600 */ 	sll	$a0,$s2,0x18
/*  f1186b4:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f1186b8:	03002025 */ 	or	$a0,$t8,$zero
/*  f1186bc:	0fc45996 */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f1186c0:	00402825 */ 	or	$a1,$v0,$zero
/*  f1186c4:	00122600 */ 	sll	$a0,$s2,0x18
/*  f1186c8:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f1186cc:	00044603 */ 	sra	$t0,$a0,0x18
/*  f1186d0:	afa20064 */ 	sw	$v0,0x64($sp)
/*  f1186d4:	afb90060 */ 	sw	$t9,0x60($sp)
/*  f1186d8:	00008025 */ 	or	$s0,$zero,$zero
/*  f1186dc:	afa00058 */ 	sw	$zero,0x58($sp)
/*  f1186e0:	afa00054 */ 	sw	$zero,0x54($sp)
/*  f1186e4:	0fc459f6 */ 	jal	pak0f1167d8
/*  f1186e8:	01002025 */ 	or	$a0,$t0,$zero
/*  f1186ec:	10400007 */ 	beqz	$v0,.L0f11870c
/*  f1186f0:	00125080 */ 	sll	$t2,$s2,0x2
/*  f1186f4:	00122600 */ 	sll	$a0,$s2,0x18
/*  f1186f8:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f1186fc:	0fc459f6 */ 	jal	pak0f1167d8
/*  f118700:	01202025 */ 	or	$a0,$t1,$zero
/*  f118704:	100000ad */ 	beqz	$zero,.L0f1189bc
/*  f118708:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f11870c:
/*  f11870c:	01525023 */ 	subu	$t2,$t2,$s2
/*  f118710:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f118714:	01525023 */ 	subu	$t2,$t2,$s2
/*  f118718:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f11871c:	01525021 */ 	addu	$t2,$t2,$s2
/*  f118720:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f118724:	01525023 */ 	subu	$t2,$t2,$s2
/*  f118728:	3c0b800a */ 	lui	$t3,%hi(g_Paks)
/*  f11872c:	256b2380 */ 	addiu	$t3,$t3,%lo(g_Paks)
/*  f118730:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f118734:	014b8821 */ 	addu	$s1,$t2,$t3
/*  f118738:	8e2c02a0 */ 	lw	$t4,0x2a0($s1)
/*  f11873c:	11800033 */ 	beqz	$t4,.L0f11880c
/*  f118740:	00122600 */ 	sll	$a0,$s2,0x18
.L0f118744:
/*  f118744:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f118748:	01a02025 */ 	or	$a0,$t5,$zero
/*  f11874c:	02002825 */ 	or	$a1,$s0,$zero
/*  f118750:	0fc45d48 */ 	jal	pakReadHeaderAtOffset
/*  f118754:	27a60070 */ 	addiu	$a2,$sp,0x70
/*  f118758:	14400020 */ 	bnez	$v0,.L0f1187dc
/*  f11875c:	24010001 */ 	addiu	$at,$zero,0x1
/*  f118760:	8fa30078 */ 	lw	$v1,0x78($sp)
/*  f118764:	000315c2 */ 	srl	$v0,$v1,0x17
/*  f118768:	304e0004 */ 	andi	$t6,$v0,0x4
/*  f11876c:	11c0000c */ 	beqz	$t6,.L0f1187a0
/*  f118770:	30490002 */ 	andi	$t1,$v0,0x2
/*  f118774:	8faf0064 */ 	lw	$t7,0x64($sp)
/*  f118778:	8e3902a0 */ 	lw	$t9,0x2a0($s1)
/*  f11877c:	020fc021 */ 	addu	$t8,$s0,$t7
/*  f118780:	2728ffe0 */ 	addiu	$t0,$t9,-32
/*  f118784:	0118082b */ 	sltu	$at,$t0,$t8
/*  f118788:	10200003 */ 	beqz	$at,.L0f118798
/*  f11878c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f118790:	10000089 */ 	beqz	$zero,.L0f1189b8
/*  f118794:	2402000e */ 	addiu	$v0,$zero,0xe
.L0f118798:
/*  f118798:	1000001c */ 	beqz	$zero,.L0f11880c
/*  f11879c:	afb00060 */ 	sw	$s0,0x60($sp)
.L0f1187a0:
/*  f1187a0:	1120000c */ 	beqz	$t1,.L0f1187d4
/*  f1187a4:	306e0fff */ 	andi	$t6,$v1,0xfff
/*  f1187a8:	8faa0064 */ 	lw	$t2,0x64($sp)
/*  f1187ac:	306b0fff */ 	andi	$t3,$v1,0xfff
/*  f1187b0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f1187b4:	154b0004 */ 	bne	$t2,$t3,.L0f1187c8
/*  f1187b8:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f1187bc:	afac0058 */ 	sw	$t4,0x58($sp)
/*  f1187c0:	10000012 */ 	beqz	$zero,.L0f11880c
/*  f1187c4:	afb00060 */ 	sw	$s0,0x60($sp)
.L0f1187c8:
/*  f1187c8:	afad0054 */ 	sw	$t5,0x54($sp)
/*  f1187cc:	1000000f */ 	beqz	$zero,.L0f11880c
/*  f1187d0:	afb00060 */ 	sw	$s0,0x60($sp)
.L0f1187d4:
/*  f1187d4:	10000009 */ 	beqz	$zero,.L0f1187fc
/*  f1187d8:	020e8021 */ 	addu	$s0,$s0,$t6
.L0f1187dc:
/*  f1187dc:	14410003 */ 	bne	$v0,$at,.L0f1187ec
/*  f1187e0:	00122600 */ 	sll	$a0,$s2,0x18
/*  f1187e4:	10000074 */ 	beqz	$zero,.L0f1189b8
/*  f1187e8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f1187ec:
/*  f1187ec:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f1187f0:	0fc45974 */ 	jal	pakGetBlockSize
/*  f1187f4:	01e02025 */ 	or	$a0,$t7,$zero
/*  f1187f8:	02028021 */ 	addu	$s0,$s0,$v0
.L0f1187fc:
/*  f1187fc:	8e3902a0 */ 	lw	$t9,0x2a0($s1)
/*  f118800:	0219082b */ 	sltu	$at,$s0,$t9
/*  f118804:	5420ffcf */ 	bnezl	$at,.L0f118744
/*  f118808:	00122600 */ 	sll	$a0,$s2,0x18
.L0f11880c:
/*  f11880c:	52000011 */ 	beqzl	$s0,.L0f118854
/*  f118810:	8fab0060 */ 	lw	$t3,0x60($sp)
/*  f118814:	12000057 */ 	beqz	$s0,.L0f118974
/*  f118818:	00122600 */ 	sll	$a0,$s2,0x18
/*  f11881c:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f118820:	0fc45ff0 */ 	jal	pakGetPdNumBytes
/*  f118824:	03002025 */ 	or	$a0,$t8,$zero
/*  f118828:	0202082b */ 	sltu	$at,$s0,$v0
/*  f11882c:	10200051 */ 	beqz	$at,.L0f118974
/*  f118830:	00122600 */ 	sll	$a0,$s2,0x18
/*  f118834:	00044603 */ 	sra	$t0,$a0,0x18
/*  f118838:	0fc45974 */ 	jal	pakGetBlockSize
/*  f11883c:	01002025 */ 	or	$a0,$t0,$zero
/*  f118840:	2449ffff */ 	addiu	$t1,$v0,-1
/*  f118844:	01305024 */ 	and	$t2,$t1,$s0
/*  f118848:	5540004b */ 	bnezl	$t2,.L0f118978
/*  f11884c:	00124080 */ 	sll	$t0,$s2,0x2
/*  f118850:	8fab0060 */ 	lw	$t3,0x60($sp)
.L0f118854:
/*  f118854:	2401ffff */ 	addiu	$at,$zero,-1
/*  f118858:	00122600 */ 	sll	$a0,$s2,0x18
/*  f11885c:	15610003 */ 	bne	$t3,$at,.L0f11886c
/*  f118860:	00046603 */ 	sra	$t4,$a0,0x18
/*  f118864:	10000054 */ 	beqz	$zero,.L0f1189b8
/*  f118868:	2402000e */ 	addiu	$v0,$zero,0xe
.L0f11886c:
/*  f11886c:	8fad0088 */ 	lw	$t5,0x88($sp)
/*  f118870:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f118874:	afae0020 */ 	sw	$t6,0x20($sp)
/*  f118878:	01802025 */ 	or	$a0,$t4,$zero
/*  f11887c:	8fa50060 */ 	lw	$a1,0x60($sp)
/*  f118880:	8fa60084 */ 	lw	$a2,0x84($sp)
/*  f118884:	00003825 */ 	or	$a3,$zero,$zero
/*  f118888:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f11888c:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f118890:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f118894:	0fc46f15 */ 	jal	pakWriteFileAtOffset
/*  f118898:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f11889c:	14400033 */ 	bnez	$v0,.L0f11896c
/*  f1188a0:	8faf0054 */ 	lw	$t7,0x54($sp)
/*  f1188a4:	11e0000d */ 	beqz	$t7,.L0f1188dc
/*  f1188a8:	8faa0058 */ 	lw	$t2,0x58($sp)
/*  f1188ac:	8fb90060 */ 	lw	$t9,0x60($sp)
/*  f1188b0:	8fb80064 */ 	lw	$t8,0x64($sp)
/*  f1188b4:	00122600 */ 	sll	$a0,$s2,0x18
/*  f1188b8:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f1188bc:	03384021 */ 	addu	$t0,$t9,$t8
/*  f1188c0:	afa80050 */ 	sw	$t0,0x50($sp)
/*  f1188c4:	01202025 */ 	or	$a0,$t1,$zero
/*  f1188c8:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f1188cc:	0fc46538 */ 	jal	pakRepairAsBlank
/*  f1188d0:	00003025 */ 	or	$a2,$zero,$zero
/*  f1188d4:	10000038 */ 	beqz	$zero,.L0f1189b8
/*  f1188d8:	00001025 */ 	or	$v0,$zero,$zero
.L0f1188dc:
/*  f1188dc:	15400003 */ 	bnez	$t2,.L0f1188ec
/*  f1188e0:	8fab0054 */ 	lw	$t3,0x54($sp)
/*  f1188e4:	11600003 */ 	beqz	$t3,.L0f1188f4
/*  f1188e8:	00122600 */ 	sll	$a0,$s2,0x18
.L0f1188ec:
/*  f1188ec:	10000032 */ 	beqz	$zero,.L0f1189b8
/*  f1188f0:	00001025 */ 	or	$v0,$zero,$zero
.L0f1188f4:
/*  f1188f4:	00046603 */ 	sra	$t4,$a0,0x18
/*  f1188f8:	01802025 */ 	or	$a0,$t4,$zero
/*  f1188fc:	0fc45c25 */ 	jal	pakGetBodyLenByType
/*  f118900:	8fa50084 */ 	lw	$a1,0x84($sp)
/*  f118904:	00122600 */ 	sll	$a0,$s2,0x18
/*  f118908:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11890c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f118910:	0fc45996 */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f118914:	00402825 */ 	or	$a1,$v0,$zero
/*  f118918:	8fae0060 */ 	lw	$t6,0x60($sp)
/*  f11891c:	00122600 */ 	sll	$a0,$s2,0x18
/*  f118920:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f118924:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f118928:	01c22821 */ 	addu	$a1,$t6,$v0
/*  f11892c:	afa50060 */ 	sw	$a1,0x60($sp)
/*  f118930:	afb80020 */ 	sw	$t8,0x20($sp)
/*  f118934:	03202025 */ 	or	$a0,$t9,$zero
/*  f118938:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f11893c:	00003825 */ 	or	$a3,$zero,$zero
/*  f118940:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f118944:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f118948:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f11894c:	0fc46f15 */ 	jal	pakWriteFileAtOffset
/*  f118950:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f118954:	14400003 */ 	bnez	$v0,.L0f118964
/*  f118958:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11895c:	10000016 */ 	beqz	$zero,.L0f1189b8
/*  f118960:	00001025 */ 	or	$v0,$zero,$zero
.L0f118964:
/*  f118964:	10000014 */ 	beqz	$zero,.L0f1189b8
/*  f118968:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f11896c:
/*  f11896c:	10000012 */ 	beqz	$zero,.L0f1189b8
/*  f118970:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f118974:
/*  f118974:	00124080 */ 	sll	$t0,$s2,0x2
.L0f118978:
/*  f118978:	01124023 */ 	subu	$t0,$t0,$s2
/*  f11897c:	00084080 */ 	sll	$t0,$t0,0x2
/*  f118980:	01124023 */ 	subu	$t0,$t0,$s2
/*  f118984:	00084080 */ 	sll	$t0,$t0,0x2
/*  f118988:	01124021 */ 	addu	$t0,$t0,$s2
/*  f11898c:	00084080 */ 	sll	$t0,$t0,0x2
/*  f118990:	01124023 */ 	subu	$t0,$t0,$s2
/*  f118994:	3c09800a */ 	lui	$t1,%hi(g_Paks)
/*  f118998:	25292380 */ 	addiu	$t1,$t1,%lo(g_Paks)
/*  f11899c:	00084080 */ 	sll	$t0,$t0,0x2
/*  f1189a0:	01098821 */ 	addu	$s1,$t0,$t1
/*  f1189a4:	240a0010 */ 	addiu	$t2,$zero,0x10
/*  f1189a8:	240b0002 */ 	addiu	$t3,$zero,0x2
/*  f1189ac:	ae2a0010 */ 	sw	$t2,0x10($s1)
/*  f1189b0:	ae2b0000 */ 	sw	$t3,0x0($s1)
/*  f1189b4:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f1189b8:
/*  f1189b8:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f1189bc:
/*  f1189bc:	8fb00030 */ 	lw	$s0,0x30($sp)
/*  f1189c0:	8fb10034 */ 	lw	$s1,0x34($sp)
/*  f1189c4:	8fb20038 */ 	lw	$s2,0x38($sp)
/*  f1189c8:	03e00008 */ 	jr	$ra
/*  f1189cc:	27bd0080 */ 	addiu	$sp,$sp,0x80
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f118674
/*  f118674:	27bdff88 */ 	addiu	$sp,$sp,-120
/*  f118678:	afb10030 */ 	sw	$s1,0x30($sp)
/*  f11867c:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f118680:	00117603 */ 	sra	$t6,$s1,0x18
/*  f118684:	afa40078 */ 	sw	$a0,0x78($sp)
/*  f118688:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f11868c:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f118690:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f118694:	01c08825 */ 	or	$s1,$t6,$zero
/*  f118698:	afb30038 */ 	sw	$s3,0x38($sp)
/*  f11869c:	afb20034 */ 	sw	$s2,0x34($sp)
/*  f1186a0:	afb0002c */ 	sw	$s0,0x2c($sp)
/*  f1186a4:	afa5007c */ 	sw	$a1,0x7c($sp)
/*  f1186a8:	afa60080 */ 	sw	$a2,0x80($sp)
/*  f1186ac:	0fc45c05 */ 	jal	pakGetBodyLenByType
/*  f1186b0:	01e02025 */ 	or	$a0,$t7,$zero
/*  f1186b4:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1186b8:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f1186bc:	03002025 */ 	or	$a0,$t8,$zero
/*  f1186c0:	0fc45976 */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f1186c4:	00402825 */ 	or	$a1,$v0,$zero
/*  f1186c8:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1186cc:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f1186d0:	00044603 */ 	sra	$t0,$a0,0x18
/*  f1186d4:	00409825 */ 	or	$s3,$v0,$zero
/*  f1186d8:	afb90058 */ 	sw	$t9,0x58($sp)
/*  f1186dc:	00008025 */ 	or	$s0,$zero,$zero
/*  f1186e0:	afa00050 */ 	sw	$zero,0x50($sp)
/*  f1186e4:	0fc459d6 */ 	jal	pak0f1167d8
/*  f1186e8:	01002025 */ 	or	$a0,$t0,$zero
/*  f1186ec:	10400007 */ 	beqz	$v0,.L0f11870c
/*  f1186f0:	00115080 */ 	sll	$t2,$s1,0x2
/*  f1186f4:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1186f8:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f1186fc:	0fc459d6 */ 	jal	pak0f1167d8
/*  f118700:	01202025 */ 	or	$a0,$t1,$zero
/*  f118704:	10000097 */ 	beqz	$zero,.L0f118964
/*  f118708:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f11870c:
/*  f11870c:	01515023 */ 	subu	$t2,$t2,$s1
/*  f118710:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f118714:	01515023 */ 	subu	$t2,$t2,$s1
/*  f118718:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f11871c:	01515021 */ 	addu	$t2,$t2,$s1
/*  f118720:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f118724:	01515023 */ 	subu	$t2,$t2,$s1
/*  f118728:	3c0b800a */ 	lui	$t3,%hi(g_Paks)
/*  f11872c:	256b2380 */ 	addiu	$t3,$t3,%lo(g_Paks)
/*  f118730:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f118734:	014b9021 */ 	addu	$s2,$t2,$t3
/*  f118738:	8e4c02a0 */ 	lw	$t4,0x2a0($s2)
/*  f11873c:	1180002d */ 	beqz	$t4,.L0f1187f4
/*  f118740:	00112600 */ 	sll	$a0,$s1,0x18
.L0f118744:
/*  f118744:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f118748:	01a02025 */ 	or	$a0,$t5,$zero
/*  f11874c:	02002825 */ 	or	$a1,$s0,$zero
/*  f118750:	0fc45d28 */ 	jal	pakReadHeaderAtOffset
/*  f118754:	27a60068 */ 	addiu	$a2,$sp,0x68
/*  f118758:	1440001a */ 	bnez	$v0,.L0f1187c4
/*  f11875c:	24010001 */ 	addiu	$at,$zero,0x1
/*  f118760:	8fa30070 */ 	lw	$v1,0x70($sp)
/*  f118764:	000315c2 */ 	srl	$v0,$v1,0x17
/*  f118768:	304e0004 */ 	andi	$t6,$v0,0x4
/*  f11876c:	11c0000b */ 	beqz	$t6,.L0f11879c
/*  f118770:	30480002 */ 	andi	$t0,$v0,0x2
/*  f118774:	8e5802a0 */ 	lw	$t8,0x2a0($s2)
/*  f118778:	02137821 */ 	addu	$t7,$s0,$s3
/*  f11877c:	2719ffe0 */ 	addiu	$t9,$t8,-32
/*  f118780:	032f082b */ 	sltu	$at,$t9,$t7
/*  f118784:	10200003 */ 	beqz	$at,.L0f118794
/*  f118788:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11878c:	10000074 */ 	beqz	$zero,.L0f118960
/*  f118790:	2402000e */ 	addiu	$v0,$zero,0xe
.L0f118794:
/*  f118794:	10000017 */ 	beqz	$zero,.L0f1187f4
/*  f118798:	afb00058 */ 	sw	$s0,0x58($sp)
.L0f11879c:
/*  f11879c:	11000006 */ 	beqz	$t0,.L0f1187b8
/*  f1187a0:	30690fff */ 	andi	$t1,$v1,0xfff
/*  f1187a4:	16690004 */ 	bne	$s3,$t1,.L0f1187b8
/*  f1187a8:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f1187ac:	afaa0050 */ 	sw	$t2,0x50($sp)
/*  f1187b0:	10000010 */ 	beqz	$zero,.L0f1187f4
/*  f1187b4:	afb00058 */ 	sw	$s0,0x58($sp)
.L0f1187b8:
/*  f1187b8:	306b0fff */ 	andi	$t3,$v1,0xfff
/*  f1187bc:	10000009 */ 	beqz	$zero,.L0f1187e4
/*  f1187c0:	020b8021 */ 	addu	$s0,$s0,$t3
.L0f1187c4:
/*  f1187c4:	14410003 */ 	bne	$v0,$at,.L0f1187d4
/*  f1187c8:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1187cc:	10000064 */ 	beqz	$zero,.L0f118960
/*  f1187d0:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f1187d4:
/*  f1187d4:	00046603 */ 	sra	$t4,$a0,0x18
/*  f1187d8:	0fc45954 */ 	jal	pakGetBlockSize
/*  f1187dc:	01802025 */ 	or	$a0,$t4,$zero
/*  f1187e0:	02028021 */ 	addu	$s0,$s0,$v0
.L0f1187e4:
/*  f1187e4:	8e4d02a0 */ 	lw	$t5,0x2a0($s2)
/*  f1187e8:	020d082b */ 	sltu	$at,$s0,$t5
/*  f1187ec:	5420ffd5 */ 	bnezl	$at,.L0f118744
/*  f1187f0:	00112600 */ 	sll	$a0,$s1,0x18
.L0f1187f4:
/*  f1187f4:	52000011 */ 	beqzl	$s0,.L0f11883c
/*  f1187f8:	8fa80058 */ 	lw	$t0,0x58($sp)
/*  f1187fc:	12000047 */ 	beqz	$s0,.L0f11891c
/*  f118800:	00112600 */ 	sll	$a0,$s1,0x18
/*  f118804:	00047603 */ 	sra	$t6,$a0,0x18
/*  f118808:	0fc45ff0 */ 	jal	pakGetPdNumBytes
/*  f11880c:	01c02025 */ 	or	$a0,$t6,$zero
/*  f118810:	0202082b */ 	sltu	$at,$s0,$v0
/*  f118814:	10200041 */ 	beqz	$at,.L0f11891c
/*  f118818:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11881c:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f118820:	0fc45954 */ 	jal	pakGetBlockSize
/*  f118824:	03002025 */ 	or	$a0,$t8,$zero
/*  f118828:	244fffff */ 	addiu	$t7,$v0,-1
/*  f11882c:	01f0c824 */ 	and	$t9,$t7,$s0
/*  f118830:	5720003b */ 	bnezl	$t9,.L0f118920
/*  f118834:	00114880 */ 	sll	$t1,$s1,0x2
/*  f118838:	8fa80058 */ 	lw	$t0,0x58($sp)
.L0f11883c:
/*  f11883c:	2401ffff */ 	addiu	$at,$zero,-1
/*  f118840:	00112600 */ 	sll	$a0,$s1,0x18
/*  f118844:	15010003 */ 	bne	$t0,$at,.L0f118854
/*  f118848:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11884c:	10000044 */ 	beqz	$zero,.L0f118960
/*  f118850:	2402000e */ 	addiu	$v0,$zero,0xe
.L0f118854:
/*  f118854:	8faa0080 */ 	lw	$t2,0x80($sp)
/*  f118858:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f11885c:	afab0020 */ 	sw	$t3,0x20($sp)
/*  f118860:	01202025 */ 	or	$a0,$t1,$zero
/*  f118864:	8fa50058 */ 	lw	$a1,0x58($sp)
/*  f118868:	8fa6007c */ 	lw	$a2,0x7c($sp)
/*  f11886c:	00003825 */ 	or	$a3,$zero,$zero
/*  f118870:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f118874:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f118878:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f11887c:	0fc46e75 */ 	jal	pakWriteFileAtOffset
/*  f118880:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f118884:	14400023 */ 	bnez	$v0,.L0f118914
/*  f118888:	8fac0050 */ 	lw	$t4,0x50($sp)
/*  f11888c:	11800003 */ 	beqz	$t4,.L0f11889c
/*  f118890:	00112600 */ 	sll	$a0,$s1,0x18
/*  f118894:	10000032 */ 	beqz	$zero,.L0f118960
/*  f118898:	00001025 */ 	or	$v0,$zero,$zero
.L0f11889c:
/*  f11889c:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f1188a0:	01a02025 */ 	or	$a0,$t5,$zero
/*  f1188a4:	0fc45c05 */ 	jal	pakGetBodyLenByType
/*  f1188a8:	8fa5007c */ 	lw	$a1,0x7c($sp)
/*  f1188ac:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1188b0:	00047603 */ 	sra	$t6,$a0,0x18
/*  f1188b4:	01c02025 */ 	or	$a0,$t6,$zero
/*  f1188b8:	0fc45976 */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f1188bc:	00402825 */ 	or	$a1,$v0,$zero
/*  f1188c0:	8fb80058 */ 	lw	$t8,0x58($sp)
/*  f1188c4:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1188c8:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f1188cc:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f1188d0:	03022821 */ 	addu	$a1,$t8,$v0
/*  f1188d4:	afa50058 */ 	sw	$a1,0x58($sp)
/*  f1188d8:	afa80020 */ 	sw	$t0,0x20($sp)
/*  f1188dc:	03202025 */ 	or	$a0,$t9,$zero
/*  f1188e0:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f1188e4:	00003825 */ 	or	$a3,$zero,$zero
/*  f1188e8:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f1188ec:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f1188f0:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f1188f4:	0fc46e75 */ 	jal	pakWriteFileAtOffset
/*  f1188f8:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f1188fc:	14400003 */ 	bnez	$v0,.L0f11890c
/*  f118900:	00000000 */ 	sll	$zero,$zero,0x0
/*  f118904:	10000016 */ 	beqz	$zero,.L0f118960
/*  f118908:	00001025 */ 	or	$v0,$zero,$zero
.L0f11890c:
/*  f11890c:	10000014 */ 	beqz	$zero,.L0f118960
/*  f118910:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f118914:
/*  f118914:	10000012 */ 	beqz	$zero,.L0f118960
/*  f118918:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f11891c:
/*  f11891c:	00114880 */ 	sll	$t1,$s1,0x2
.L0f118920:
/*  f118920:	01314823 */ 	subu	$t1,$t1,$s1
/*  f118924:	00094880 */ 	sll	$t1,$t1,0x2
/*  f118928:	01314823 */ 	subu	$t1,$t1,$s1
/*  f11892c:	00094880 */ 	sll	$t1,$t1,0x2
/*  f118930:	01314821 */ 	addu	$t1,$t1,$s1
/*  f118934:	00094880 */ 	sll	$t1,$t1,0x2
/*  f118938:	01314823 */ 	subu	$t1,$t1,$s1
/*  f11893c:	3c0a800a */ 	lui	$t2,%hi(g_Paks)
/*  f118940:	254a2380 */ 	addiu	$t2,$t2,%lo(g_Paks)
/*  f118944:	00094880 */ 	sll	$t1,$t1,0x2
/*  f118948:	012a9021 */ 	addu	$s2,$t1,$t2
/*  f11894c:	240b0010 */ 	addiu	$t3,$zero,0x10
/*  f118950:	240c0002 */ 	addiu	$t4,$zero,0x2
/*  f118954:	ae4b0010 */ 	sw	$t3,0x10($s2)
/*  f118958:	ae4c0000 */ 	sw	$t4,0x0($s2)
/*  f11895c:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f118960:
/*  f118960:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f118964:
/*  f118964:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*  f118968:	8fb10030 */ 	lw	$s1,0x30($sp)
/*  f11896c:	8fb20034 */ 	lw	$s2,0x34($sp)
/*  f118970:	8fb30038 */ 	lw	$s3,0x38($sp)
/*  f118974:	03e00008 */ 	jr	$ra
/*  f118978:	27bd0078 */ 	addiu	$sp,$sp,0x78
);
#else
GLOBAL_ASM(
glabel pak0f118674
/*  f112a60:	27bdff88 */ 	addiu	$sp,$sp,-120
/*  f112a64:	afb20034 */ 	sw	$s2,0x34($sp)
/*  f112a68:	00049600 */ 	sll	$s2,$a0,0x18
/*  f112a6c:	00127603 */ 	sra	$t6,$s2,0x18
/*  f112a70:	afa40078 */ 	sw	$a0,0x78($sp)
/*  f112a74:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f112a78:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f112a7c:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f112a80:	01c09025 */ 	or	$s2,$t6,$zero
/*  f112a84:	afb30038 */ 	sw	$s3,0x38($sp)
/*  f112a88:	afb10030 */ 	sw	$s1,0x30($sp)
/*  f112a8c:	afb0002c */ 	sw	$s0,0x2c($sp)
/*  f112a90:	afa5007c */ 	sw	$a1,0x7c($sp)
/*  f112a94:	afa60080 */ 	sw	$a2,0x80($sp)
/*  f112a98:	0fc444f9 */ 	jal	pakGetBodyLenByType
/*  f112a9c:	01e02025 */ 	or	$a0,$t7,$zero
/*  f112aa0:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112aa4:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f112aa8:	03002025 */ 	or	$a0,$t8,$zero
/*  f112aac:	0fc442ae */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f112ab0:	00402825 */ 	or	$a1,$v0,$zero
/*  f112ab4:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112ab8:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f112abc:	00044603 */ 	sra	$t0,$a0,0x18
/*  f112ac0:	00409825 */ 	or	$s3,$v0,$zero
/*  f112ac4:	afb90058 */ 	sw	$t9,0x58($sp)
/*  f112ac8:	00008025 */ 	or	$s0,$zero,$zero
/*  f112acc:	afa00050 */ 	sw	$zero,0x50($sp)
/*  f112ad0:	0fc442e7 */ 	jal	pak0f1167d8
/*  f112ad4:	01002025 */ 	or	$a0,$t0,$zero
/*  f112ad8:	10400007 */ 	beqz	$v0,.NB0f112af8
/*  f112adc:	00125080 */ 	sll	$t2,$s2,0x2
/*  f112ae0:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112ae4:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f112ae8:	0fc442e7 */ 	jal	pak0f1167d8
/*  f112aec:	01202025 */ 	or	$a0,$t1,$zero
/*  f112af0:	10000087 */ 	beqz	$zero,.NB0f112d10
/*  f112af4:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f112af8:
/*  f112af8:	01525023 */ 	subu	$t2,$t2,$s2
/*  f112afc:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f112b00:	01525023 */ 	subu	$t2,$t2,$s2
/*  f112b04:	000a50c0 */ 	sll	$t2,$t2,0x3
/*  f112b08:	01525021 */ 	addu	$t2,$t2,$s2
/*  f112b0c:	3c0b800a */ 	lui	$t3,0x800a
/*  f112b10:	256b6870 */ 	addiu	$t3,$t3,0x6870
/*  f112b14:	000a50c0 */ 	sll	$t2,$t2,0x3
/*  f112b18:	014b8821 */ 	addu	$s1,$t2,$t3
/*  f112b1c:	8e2c02a0 */ 	lw	$t4,0x2a0($s1)
/*  f112b20:	11800021 */ 	beqz	$t4,.NB0f112ba8
/*  f112b24:	00122600 */ 	sll	$a0,$s2,0x18
.NB0f112b28:
/*  f112b28:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f112b2c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f112b30:	02002825 */ 	or	$a1,$s0,$zero
/*  f112b34:	0fc4461f */ 	jal	pakReadHeaderAtOffset
/*  f112b38:	27a60068 */ 	addiu	$a2,$sp,0x68
/*  f112b3c:	14400012 */ 	bnez	$v0,.NB0f112b88
/*  f112b40:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112b44:	8fa30070 */ 	lw	$v1,0x70($sp)
/*  f112b48:	000315c2 */ 	srl	$v0,$v1,0x17
/*  f112b4c:	304e0004 */ 	andi	$t6,$v0,0x4
/*  f112b50:	11c00003 */ 	beqz	$t6,.NB0f112b60
/*  f112b54:	304f0002 */ 	andi	$t7,$v0,0x2
/*  f112b58:	10000013 */ 	beqz	$zero,.NB0f112ba8
/*  f112b5c:	afb00058 */ 	sw	$s0,0x58($sp)
.NB0f112b60:
/*  f112b60:	11e00006 */ 	beqz	$t7,.NB0f112b7c
/*  f112b64:	30780fff */ 	andi	$t8,$v1,0xfff
/*  f112b68:	16780004 */ 	bne	$s3,$t8,.NB0f112b7c
/*  f112b6c:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f112b70:	afb90050 */ 	sw	$t9,0x50($sp)
/*  f112b74:	1000000c */ 	beqz	$zero,.NB0f112ba8
/*  f112b78:	afb00058 */ 	sw	$s0,0x58($sp)
.NB0f112b7c:
/*  f112b7c:	30680fff */ 	andi	$t0,$v1,0xfff
/*  f112b80:	10000005 */ 	beqz	$zero,.NB0f112b98
/*  f112b84:	02088021 */ 	addu	$s0,$s0,$t0
.NB0f112b88:
/*  f112b88:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f112b8c:	0fc4428c */ 	jal	pakGetBlockSize
/*  f112b90:	01202025 */ 	or	$a0,$t1,$zero
/*  f112b94:	02028021 */ 	addu	$s0,$s0,$v0
.NB0f112b98:
/*  f112b98:	8e2a02a0 */ 	lw	$t2,0x2a0($s1)
/*  f112b9c:	020a082b */ 	sltu	$at,$s0,$t2
/*  f112ba0:	5420ffe1 */ 	bnezl	$at,.NB0f112b28
/*  f112ba4:	00122600 */ 	sll	$a0,$s2,0x18
.NB0f112ba8:
/*  f112ba8:	52000011 */ 	beqzl	$s0,.NB0f112bf0
/*  f112bac:	8faf0058 */ 	lw	$t7,0x58($sp)
/*  f112bb0:	12000047 */ 	beqz	$s0,.NB0f112cd0
/*  f112bb4:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112bb8:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f112bbc:	0fc448fb */ 	jal	pakGetPdNumBytes
/*  f112bc0:	01602025 */ 	or	$a0,$t3,$zero
/*  f112bc4:	0202082b */ 	sltu	$at,$s0,$v0
/*  f112bc8:	10200041 */ 	beqz	$at,.NB0f112cd0
/*  f112bcc:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112bd0:	00046603 */ 	sra	$t4,$a0,0x18
/*  f112bd4:	0fc4428c */ 	jal	pakGetBlockSize
/*  f112bd8:	01802025 */ 	or	$a0,$t4,$zero
/*  f112bdc:	244dffff */ 	addiu	$t5,$v0,-1
/*  f112be0:	01b07024 */ 	and	$t6,$t5,$s0
/*  f112be4:	55c0003b */ 	bnezl	$t6,.NB0f112cd4
/*  f112be8:	0012c080 */ 	sll	$t8,$s2,0x2
/*  f112bec:	8faf0058 */ 	lw	$t7,0x58($sp)
.NB0f112bf0:
/*  f112bf0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f112bf4:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112bf8:	15e10003 */ 	bne	$t7,$at,.NB0f112c08
/*  f112bfc:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f112c00:	10000042 */ 	beqz	$zero,.NB0f112d0c
/*  f112c04:	2402000e */ 	addiu	$v0,$zero,0xe
.NB0f112c08:
/*  f112c08:	8fb90080 */ 	lw	$t9,0x80($sp)
/*  f112c0c:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f112c10:	afa80020 */ 	sw	$t0,0x20($sp)
/*  f112c14:	03002025 */ 	or	$a0,$t8,$zero
/*  f112c18:	8fa50058 */ 	lw	$a1,0x58($sp)
/*  f112c1c:	8fa6007c */ 	lw	$a2,0x7c($sp)
/*  f112c20:	00003825 */ 	or	$a3,$zero,$zero
/*  f112c24:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f112c28:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f112c2c:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f112c30:	0fc456f6 */ 	jal	pakWriteFileAtOffset
/*  f112c34:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f112c38:	14400023 */ 	bnez	$v0,.NB0f112cc8
/*  f112c3c:	8fa90050 */ 	lw	$t1,0x50($sp)
/*  f112c40:	11200003 */ 	beqz	$t1,.NB0f112c50
/*  f112c44:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112c48:	10000030 */ 	beqz	$zero,.NB0f112d0c
/*  f112c4c:	00001025 */ 	or	$v0,$zero,$zero
.NB0f112c50:
/*  f112c50:	00045603 */ 	sra	$t2,$a0,0x18
/*  f112c54:	01402025 */ 	or	$a0,$t2,$zero
/*  f112c58:	0fc444f9 */ 	jal	pakGetBodyLenByType
/*  f112c5c:	8fa5007c */ 	lw	$a1,0x7c($sp)
/*  f112c60:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112c64:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f112c68:	01602025 */ 	or	$a0,$t3,$zero
/*  f112c6c:	0fc442ae */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f112c70:	00402825 */ 	or	$a1,$v0,$zero
/*  f112c74:	8fac0058 */ 	lw	$t4,0x58($sp)
/*  f112c78:	00122600 */ 	sll	$a0,$s2,0x18
/*  f112c7c:	00047603 */ 	sra	$t6,$a0,0x18
/*  f112c80:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f112c84:	01822821 */ 	addu	$a1,$t4,$v0
/*  f112c88:	afa50058 */ 	sw	$a1,0x58($sp)
/*  f112c8c:	afaf0020 */ 	sw	$t7,0x20($sp)
/*  f112c90:	01c02025 */ 	or	$a0,$t6,$zero
/*  f112c94:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f112c98:	00003825 */ 	or	$a3,$zero,$zero
/*  f112c9c:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f112ca0:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f112ca4:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f112ca8:	0fc456f6 */ 	jal	pakWriteFileAtOffset
/*  f112cac:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f112cb0:	14400003 */ 	bnez	$v0,.NB0f112cc0
/*  f112cb4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f112cb8:	10000014 */ 	beqz	$zero,.NB0f112d0c
/*  f112cbc:	00001025 */ 	or	$v0,$zero,$zero
.NB0f112cc0:
/*  f112cc0:	10000012 */ 	beqz	$zero,.NB0f112d0c
/*  f112cc4:	24020004 */ 	addiu	$v0,$zero,0x4
.NB0f112cc8:
/*  f112cc8:	10000010 */ 	beqz	$zero,.NB0f112d0c
/*  f112ccc:	24020004 */ 	addiu	$v0,$zero,0x4
.NB0f112cd0:
/*  f112cd0:	0012c080 */ 	sll	$t8,$s2,0x2
.NB0f112cd4:
/*  f112cd4:	0312c023 */ 	subu	$t8,$t8,$s2
/*  f112cd8:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f112cdc:	0312c023 */ 	subu	$t8,$t8,$s2
/*  f112ce0:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f112ce4:	0312c021 */ 	addu	$t8,$t8,$s2
/*  f112ce8:	3c19800a */ 	lui	$t9,0x800a
/*  f112cec:	27396870 */ 	addiu	$t9,$t9,0x6870
/*  f112cf0:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f112cf4:	03198821 */ 	addu	$s1,$t8,$t9
/*  f112cf8:	24080010 */ 	addiu	$t0,$zero,0x10
/*  f112cfc:	24090002 */ 	addiu	$t1,$zero,0x2
/*  f112d00:	ae280010 */ 	sw	$t0,0x10($s1)
/*  f112d04:	ae290000 */ 	sw	$t1,0x0($s1)
/*  f112d08:	24020004 */ 	addiu	$v0,$zero,0x4
.NB0f112d0c:
/*  f112d0c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f112d10:
/*  f112d10:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*  f112d14:	8fb10030 */ 	lw	$s1,0x30($sp)
/*  f112d18:	8fb20034 */ 	lw	$s2,0x34($sp)
/*  f112d1c:	8fb30038 */ 	lw	$s3,0x38($sp)
/*  f112d20:	03e00008 */ 	jr	$ra
/*  f112d24:	27bd0078 */ 	addiu	$sp,$sp,0x78
);
#endif

/**
 * Find a spot for the given filetype and write it.
 *
 * Replace a blank spot or extend the filesystem if needed and possible.
 */
// Mismatch because goal calculates s1 (address of g_Paks[device]) twice.
// Mine also does it twice using the u32 cast but stores the second one in v1.
// Removing the cast causes mine to calculate s1 only once and reuse it.
//u32 pak0f118674(s8 device, u32 filetype, s32 *outfileid)
//{
//	struct pakfileheader header;
//	u32 sp108;
//	s32 ret;
//	s32 filelen = pakGetAlignedFileLenByBodyLen(device, pakGetBodyLenByType(device, filetype));
//	s32 bestoffset = -1;
//	u32 offset = 0;
//	bool foundperfectblank = false;
//#if VERSION >= VERSION_NTSC_FINAL
//	bool foundblank = false;
//#endif
//
//	if (pak0f1167d8(device)) {
//		return pak0f1167d8(device);
//	}
//
//	while (offset < g_Paks[device].pdnumbytes) {
//		ret = pakReadHeaderAtOffset(device, offset, &header);
//
//		if (ret == PAK_ERR2_OK) {
//			if (header.filetype & PAKFILETYPE_TERMINATOR) {
//				if (offset + filelen > g_Paks[device].pdnumbytes - 0x20) {
//					return 14;
//				}
//
//				bestoffset = offset;
//				break;
//			}
//
//			if (header.filetype & PAKFILETYPE_BLANK) {
//				if (header.filelen == filelen) {
//					foundperfectblank = true;
//					bestoffset = offset;
//					break;
//				}
//
//#if VERSION >= VERSION_NTSC_FINAL
//				foundblank = true;
//				bestoffset = offset;
//				break;
//#endif
//			}
//
//			offset += header.filelen;
//		} else if (ret == PAK_ERR2_NOPAK) {
//			return 1;
//		} else {
//			offset += pakGetBlockSize(device);
//		}
//	}
//
//	if (offset == 0 ||
//			(offset && offset < pakGetPdNumBytes(device) && (pakGetBlockSize(device) - 1 & offset) == 0)) {
//		if (bestoffset == -1) {
//			return 14;
//		}
//
//		// Write the file
//		if (pakWriteFileAtOffset(device, bestoffset, filetype, NULL, 0, outfileid, NULL, 0, 1) == 0) {
//#if VERSION >= VERSION_NTSC_FINAL
//			if (foundblank) {
//				u32 endoffset = bestoffset + filelen;
//				pakRepairAsBlank(device, &endoffset, NULL);
//				return 0;
//			}
//
//			if (foundperfectblank || foundblank) {
//				return 0;
//			}
//#else
//			if (foundperfectblank) {
//				return 0;
//			}
//#endif
//
//			// Write new terminator after file
//			bestoffset += pakGetAlignedFileLenByBodyLen(device, pakGetBodyLenByType(device, filetype));
//
//			if (pakWriteFileAtOffset(device, bestoffset, PAKFILETYPE_TERMINATOR, NULL, 0, NULL, NULL, 0, 1) == 0) {
//				return 0;
//			}
//
//			return 4;
//		}
//
//		return 4;
//	}
//
//	g_Paks[(u32)device].unk010 = PAK010_16;
//	g_Paks[(u32)device].type = PAKTYPE_MEMORY;
//
//	return 4;
//}

void pak0f1189d0(void)
{
	// empty
}

#if VERSION >= VERSION_NTSC_1_0
void pakInitAll(void)
{
	u8 prevvalue = g_Vars.paksconnected;
	s8 i;

	g_Vars.unk0004e4 = 0;

	for (i = 0; i < 5; i++) {
		pakInit(i);
	}

	for (i = 0; i < 5; i++) {
#if VERSION >= VERSION_JPN_FINAL
		pak0f11a32c(i, 7, 2054, "pak/pak.c");
#elif VERSION >= VERSION_PAL_BETA
		pak0f11a32c(i, 7, 2049, "pak.c");
#elif VERSION >= VERSION_NTSC_FINAL
		pak0f11a32c(i, 7, 2049, "pak/pak.c");
#else
		pak0f11a32c(i, 7, 2016, "pak.c");
#endif
	}

	pakProbeEeprom();
	joyRecordPfsState(0x10);

	g_Vars.paksconnected = 0x10;

	pak0f1169c8(SAVEDEVICE_GAMEPAK, 1);
	bossfileLoadFull();

	gamefileLoadDefaults(&g_GameFile);
	gamefileApplyOptions(&g_GameFile);

	g_GameFileGuid.deviceserial = 0;
	g_Vars.unk0004e4 = 0xf5;
	g_Vars.paksconnected = prevvalue;
}
#else
GLOBAL_ASM(
glabel pakInitAll
/*  f112d30:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*  f112d34:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f112d38:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f112d3c:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f112d40:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f112d44:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f112d48:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f112d4c:	00008025 */ 	or	$s0,$zero,$zero
/*  f112d50:	00102600 */ 	sll	$a0,$s0,0x18
.NB0f112d54:
/*  f112d54:	00047603 */ 	sra	$t6,$a0,0x18
/*  f112d58:	0fc450bb */ 	jal	pakInit
/*  f112d5c:	01c02025 */ 	or	$a0,$t6,$zero
/*  f112d60:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f112d64:	00107e00 */ 	sll	$t7,$s0,0x18
/*  f112d68:	000f8603 */ 	sra	$s0,$t7,0x18
/*  f112d6c:	2a010005 */ 	slti	$at,$s0,0x5
/*  f112d70:	5420fff8 */ 	bnezl	$at,.NB0f112d54
/*  f112d74:	00102600 */ 	sll	$a0,$s0,0x18
/*  f112d78:	2419001f */ 	addiu	$t9,$zero,0x1f
/*  f112d7c:	3c01800a */ 	lui	$at,0x800a
/*  f112d80:	3c117f1b */ 	lui	$s1,0x7f1b
/*  f112d84:	a039eb91 */ 	sb	$t9,-0x146f($at)
/*  f112d88:	2631dc10 */ 	addiu	$s1,$s1,-9200
/*  f112d8c:	00008025 */ 	or	$s0,$zero,$zero
/*  f112d90:	00102600 */ 	sll	$a0,$s0,0x18
.NB0f112d94:
/*  f112d94:	00044603 */ 	sra	$t0,$a0,0x18
/*  f112d98:	01002025 */ 	or	$a0,$t0,$zero
/*  f112d9c:	24050007 */ 	addiu	$a1,$zero,0x7
/*  f112da0:	24060789 */ 	addiu	$a2,$zero,0x789
/*  f112da4:	0fc4507d */ 	jal	pak0f11a32c
/*  f112da8:	02203825 */ 	or	$a3,$s1,$zero
/*  f112dac:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f112db0:	00104e00 */ 	sll	$t1,$s0,0x18
/*  f112db4:	00098603 */ 	sra	$s0,$t1,0x18
/*  f112db8:	2a010005 */ 	slti	$at,$s0,0x5
/*  f112dbc:	5420fff5 */ 	bnezl	$at,.NB0f112d94
/*  f112dc0:	00102600 */ 	sll	$a0,$s0,0x18
/*  f112dc4:	0fc4608d */ 	jal	pakProbeEeprom
/*  f112dc8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f112dcc:	00008825 */ 	or	$s1,$zero,$zero
/*  f112dd0:	24140009 */ 	addiu	$s4,$zero,0x9
/*  f112dd4:	240b0001 */ 	addiu	$t3,$zero,0x1
.NB0f112dd8:
/*  f112dd8:	022b9004 */ 	sllv	$s2,$t3,$s1
/*  f112ddc:	02402825 */ 	or	$a1,$s2,$zero
/*  f112de0:	0fc444f9 */ 	jal	pakGetBodyLenByType
/*  f112de4:	00002025 */ 	or	$a0,$zero,$zero
/*  f112de8:	00409825 */ 	or	$s3,$v0,$zero
/*  f112dec:	0fc44528 */ 	jal	pak0f1114a0nb
/*  f112df0:	02402025 */ 	or	$a0,$s2,$zero
/*  f112df4:	00102600 */ 	sll	$a0,$s0,0x18
/*  f112df8:	00046603 */ 	sra	$t4,$a0,0x18
/*  f112dfc:	01802025 */ 	or	$a0,$t4,$zero
/*  f112e00:	0fc442ae */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f112e04:	02602825 */ 	or	$a1,$s3,$zero
/*  f112e08:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f112e0c:	5634fff2 */ 	bnel	$s1,$s4,.NB0f112dd8
/*  f112e10:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f112e14:	0fc45920 */ 	jal	pakExecuteDebugOperations
/*  f112e18:	00000000 */ 	sll	$zero,$zero,0x0
/*  f112e1c:	0fc42ace */ 	jal	bossfileLoadFull
/*  f112e20:	00000000 */ 	sll	$zero,$zero,0x0
/*  f112e24:	3c10800a */ 	lui	$s0,0x800a
/*  f112e28:	261066f0 */ 	addiu	$s0,$s0,0x66f0
/*  f112e2c:	0fc426fe */ 	jal	gamefileLoadDefaults
/*  f112e30:	02002025 */ 	or	$a0,$s0,$zero
/*  f112e34:	0fc425d9 */ 	jal	gamefileApplyOptions
/*  f112e38:	02002025 */ 	or	$a0,$s0,$zero
/*  f112e3c:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f112e40:	3c01800a */ 	lui	$at,0x800a
/*  f112e44:	a42067b4 */ 	sh	$zero,0x67b4($at)
/*  f112e48:	3c01800a */ 	lui	$at,0x800a
/*  f112e4c:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f112e50:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f112e54:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f112e58:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f112e5c:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f112e60:	a020eb91 */ 	sb	$zero,-0x146f($at)
/*  f112e64:	03e00008 */ 	jr	$ra
/*  f112e68:	27bd0030 */ 	addiu	$sp,$sp,0x30
);
#endif

const char var7f1b3e3c[] = "Pak %d -> Pak_Dir - ERROR : Pak Not Ready\n";
const char var7f1b3e68[] = "Pak %d -> Pak_Dir - Done - Pak_GetOffsetEOF\n";
const char var7f1b3e98[] = "Pak %d -> Pak_Dir - Done - ekPakErrorHeaderCrcCheckFail\n";
const char var7f1b3ed4[] = "Pak Return Code = ekPakOk";
const char var7f1b3ef0[] = "Pak Return Code = ekPakErrorNoPakPresent";
const char var7f1b3f1c[] = "Pak Return Code = ekPakErrorPakFatal";
const char var7f1b3f44[] = "Pak Return Code = ekPakErrorFileNotFound";
const char var7f1b3f70[] = "Pak Return Code = ekPakErrorFileSystem";
const char var7f1b3f98[] = "Pak Return Code = ekPakErrorOutOfMemory";
const char var7f1b3fc0[] = "Pak Return Code = ekPakErrorPakWaitingForInit";
const char var7f1b3ff0[] = "Pak Return Code = ekPakErrorHeaderCrcCheckFail";
const char var7f1b4020[] = "Pak Return Code = ekPakErrorDataCrcCheckFail";
const char var7f1b4050[] = "Pak Return Code = ekPakErrorDataNotValid";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b407c[] = "Pak Return Code = Unknown - %d\n";
#else
const char var7f1b407c[] = "Pak Return Code = Unknown - %d";
#endif

void pakCalculateChecksum(u8 *start, u8 *end, u16 *checksum)
{
	crcCalculateU16Pair(start, end, checksum);
}

s32 pak0f118b04(s8 device, u32 fileid)
{
	s32 offset;
	s32 result = pak0f1167d8(device);

	if (result == 0) {
		offset = pakFindFile(device, fileid, 0);

#if VERSION >= VERSION_NTSC_1_0
		if (offset == -1) {
			return 1;
		}
#endif

		if (offset == 0 || (offset != 0 && offset < pakGetPdNumBytes(device) && (pakGetBlockSize(device) - 1 & offset) == 0)) {
			if (!pakReplaceFileAtOffsetWithBlank(device, offset)) {
				return 4;
			}
		} else {
			return 3;
		}
	} else {
		return 6;
	}

	return 0;
}

s32 _pakReadBodyAtGuid(s8 device, s32 fileid, u8 *body, s32 arg3)
{
	s32 offset;
	struct pakfileheader header;
	s32 result;
	u16 checksum[2];

	if (!pak0f1167d8(device)) {
		offset = pakFindFile(device, fileid, NULL);

#if VERSION >= VERSION_NTSC_1_0
		if (offset == -1) {
			return 1;
		}
#endif

		if (offset == 0 || (offset && offset < pakGetPdNumBytes(device) && ((pakGetBlockSize(device) - 1) & offset) == 0)) {
			result = pak0f11b86c(device, offset, body, &header, arg3);

			if (result) {
				return result;
			}

			if (arg3 == -1) {
				arg3 = 0;
			}

			if (header.occupied) {
				if (!arg3) {
					pakCalculateChecksum(body, body + header.bodylen, checksum);

					if (header.bodysum[0] != checksum[0] || header.bodysum[1] != checksum[1]) {
						return 8;
					}
				}
			} else {
				return 10;
			}
		} else {
			return 3;
		}
	} else {
		return 6;
	}

	return 0;
}

s32 _pakGetFileIdsByType(s8 device, u32 filetype, u32 *fileids)
{
	struct pakfileheader header;
	u32 offset = 0;
	u32 fslen;
	s32 len = 0;
	s32 result = pak0f119298(device);

	if (result != 0) {
		return result;
	}

	result = pakGetFilesystemLength(device, &fslen);

	if (result != 0) {
		return result;
	}

	result = pak0f1167d8(device);

	if (result != 0) {
		return pak0f1167d8(device);
	}

	result = pakReadHeaderAtOffset(device, offset, &header);

	while (result == PAK_ERR2_OK) {
		if ((filetype & PAKFILETYPE_ALL) || (filetype & header.filetype)) {
			fileids[len] = header.fileid;
			len++;
		}

		offset += header.filelen;

		if (offset >= fslen) {
			break;
		}

		result = pakReadHeaderAtOffset(device, offset, &header);
	}

	fileids[len] = 0;

	if (result == PAK_ERR2_CHECKSUM) {
		return 7;
	}

#if VERSION >= VERSION_NTSC_1_0
	if (result == PAK_ERR2_NOPAK) {
		return 1;
	}
#endif

	return 0;
}

/**
 * This function makes no sense. If it's trying to get a usage percentage then
 * it should be adding the number of blank blocks, not number of blank files.
 *
 * It's not called anyway - likely a broken debug function.
 */
s32 pak0f118eb0(s8 device, u32 *dst)
{
	struct pakfileheader header;
	f32 numblanks = 0; // This was probably supposed to be an s32
	u32 offset = 0;

	s32 ret = pak0f1167d8(device);

	if (ret != 0) {
		return ret;
	}

	while (pakReadHeaderAtOffset(device, offset, &header) == 0) {
		if (PAKFILETYPE_BLANK == header.filetype) {
			numblanks++;
		}

		offset += header.filelen;
	}

	*dst = 100.0f / g_Paks[device].pdnumblocks * numblanks;

	return 0;
}

s32 pakDefrag(s8 device)
{
	s32 result = pak0f1167d8(device);

	if (result != 0) {
		return result;
	}

	pakMergeBlanks(device);

	return 0;
}

/**
 * Calculate the number of times the given filetype can fit in the note.
 *
 * Return 0 if it can fit, otherwise 5.
 */
s32 pakCheckFileCanFitInNote(s8 device, s32 filetype, s32 *numspaces)
{
	struct pakfileheader header;
	u32 filelen;
	bool hasspace;
	u32 fslen;
	u32 offset;
	u32 roomtogrow;

	filelen = pakGetAlignedFileLenByBodyLen(device, pakGetBodyLenByType(device, filetype));

	hasspace = false;

	pakGetFilesystemLength(device, &fslen);

	if (numspaces != NULL) {
		*numspaces = 0;
	}

	for (offset = 0; pakReadHeaderAtOffset(device, offset, &header) == PAK_ERR2_OK && offset < fslen; offset += header.filelen) {
		if (PAKFILETYPE_BLANK == header.filetype && header.filelen >= filelen) {
			hasspace = true;

			if (numspaces != NULL) {
				*numspaces = *numspaces + 1;
			}
		}
	}

	roomtogrow = g_Paks[device].pdnumbytes - fslen;

	if (numspaces != NULL) {
		*numspaces += roomtogrow / filelen;
	}

	if (!hasspace && roomtogrow >= pakGetMaxFileSize(device)) {
		hasspace = true;
	}

	return (hasspace ? 0 : 5);
}

u32 pak0f119298(s8 device)
{
	if (g_Paks[device].type != PAKTYPE_MEMORY) {
		return 1;
	}

	switch (g_Paks[device].unk010) {
	case PAK010_11:
		return 0;
	case PAK010_17:
		return 14;
	case PAK010_18:
		return 4;
	case PAK010_03:
	case PAK010_04:
	case PAK010_05:
	case PAK010_06:
	case PAK010_07:
		return 13;
	}

	return 1;
}

void pak0f119340(u32 arg0)
{
	switch (arg0) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		break;
	}
}

#if VERSION >= VERSION_NTSC_1_0
// Note: ntsc-beta doesn't match the below due to stack size
s32 pakFindFile(s8 device, u32 fileid, struct pakfileheader *headerptr)
{
	struct pakfileheader header;
	s32 offset = 0;
	u32 fslen;
	s32 ret;

	pakGetFilesystemLength(device, &fslen);

	ret = pakReadHeaderAtOffset(device, offset, &header);

	while (ret == PAK_ERR2_OK && offset < fslen) {
		if (fileid == header.fileid) {
			if (headerptr) {
				memcpy(headerptr, &header, sizeof(struct pakfileheader));
			}

			return offset;
		}

		offset += header.filelen;

		ret = pakReadHeaderAtOffset(device, offset, &header);
	}

#if VERSION >= VERSION_NTSC_1_0
	if (ret == PAK_ERR2_NOPAK) {
		return -1;
	}
#endif

	return 0xffff;
}
#else
GLOBAL_ASM(
glabel pakFindFile
/*  f11369c:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f1136a0:	afb10018 */ 	sw	$s1,0x18($sp)
/*  f1136a4:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f1136a8:	00117603 */ 	sra	$t6,$s1,0x18
/*  f1136ac:	afa40040 */ 	sw	$a0,0x40($sp)
/*  f1136b0:	afb2001c */ 	sw	$s2,0x1c($sp)
/*  f1136b4:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f1136b8:	00a09025 */ 	or	$s2,$a1,$zero
/*  f1136bc:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f1136c0:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f1136c4:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f1136c8:	01c08825 */ 	or	$s1,$t6,$zero
/*  f1136cc:	afb30020 */ 	sw	$s3,0x20($sp)
/*  f1136d0:	afa60048 */ 	sw	$a2,0x48($sp)
/*  f1136d4:	00008025 */ 	or	$s0,$zero,$zero
/*  f1136d8:	01e02025 */ 	or	$a0,$t7,$zero
/*  f1136dc:	0fc455c3 */ 	jal	pakGetFilesystemLength
/*  f1136e0:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f1136e4:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1136e8:	27b30030 */ 	addiu	$s3,$sp,0x30
/*  f1136ec:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f1136f0:	03002025 */ 	or	$a0,$t8,$zero
/*  f1136f4:	02603025 */ 	or	$a2,$s3,$zero
/*  f1136f8:	0fc4461f */ 	jal	pakReadHeaderAtOffset
/*  f1136fc:	00002825 */ 	or	$a1,$zero,$zero
/*  f113700:	1440001d */ 	bnez	$v0,.NB0f113778
/*  f113704:	8fb9002c */ 	lw	$t9,0x2c($sp)
/*  f113708:	5320001c */ 	beqzl	$t9,.NB0f11377c
/*  f11370c:	3402ffff */ 	dli	$v0,0xffff
/*  f113710:	8fa8003c */ 	lw	$t0,0x3c($sp)
.NB0f113714:
/*  f113714:	8fab0038 */ 	lw	$t3,0x38($sp)
/*  f113718:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11371c:	00084b40 */ 	sll	$t1,$t0,0xd
/*  f113720:	00095642 */ 	srl	$t2,$t1,0x19
/*  f113724:	164a0009 */ 	bne	$s2,$t2,.NB0f11374c
/*  f113728:	316c0fff */ 	andi	$t4,$t3,0xfff
/*  f11372c:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f113730:	02602825 */ 	or	$a1,$s3,$zero
/*  f113734:	10800003 */ 	beqz	$a0,.NB0f113744
/*  f113738:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11373c:	0c012e88 */ 	jal	memcpy
/*  f113740:	24060010 */ 	addiu	$a2,$zero,0x10
.NB0f113744:
/*  f113744:	1000000d */ 	beqz	$zero,.NB0f11377c
/*  f113748:	02001025 */ 	or	$v0,$s0,$zero
.NB0f11374c:
/*  f11374c:	020c8021 */ 	addu	$s0,$s0,$t4
/*  f113750:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f113754:	01a02025 */ 	or	$a0,$t5,$zero
/*  f113758:	02002825 */ 	or	$a1,$s0,$zero
/*  f11375c:	0fc4461f */ 	jal	pakReadHeaderAtOffset
/*  f113760:	02603025 */ 	or	$a2,$s3,$zero
/*  f113764:	14400004 */ 	bnez	$v0,.NB0f113778
/*  f113768:	8fae002c */ 	lw	$t6,0x2c($sp)
/*  f11376c:	020e082b */ 	sltu	$at,$s0,$t6
/*  f113770:	5420ffe8 */ 	bnezl	$at,.NB0f113714
/*  f113774:	8fa8003c */ 	lw	$t0,0x3c($sp)
.NB0f113778:
/*  f113778:	3402ffff */ 	dli	$v0,0xffff
.NB0f11377c:
/*  f11377c:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f113780:	8fb00014 */ 	lw	$s0,0x14($sp)
/*  f113784:	8fb10018 */ 	lw	$s1,0x18($sp)
/*  f113788:	8fb2001c */ 	lw	$s2,0x1c($sp)
/*  f11378c:	8fb30020 */ 	lw	$s3,0x20($sp)
/*  f113790:	03e00008 */ 	jr	$ra
/*  f113794:	27bd0040 */ 	addiu	$sp,$sp,0x40
);
#endif

#if VERSION >= VERSION_NTSC_FINAL
bool pakWriteBlankFile(s8 device, u32 offset, struct pakfileheader *header)
{
	if (pakWriteFileAtOffset(device, offset, PAKFILETYPE_BLANK, NULL, pakGetBodyLenByFileLen(header->filelen), NULL, NULL, 0, 1) == 0) {
		return true;
	}

	return false;
}
#endif

#if VERSION >= VERSION_NTSC_FINAL
GLOBAL_ASM(
glabel pakRepairAsBlank
/*  f1194e0:	27bdff70 */ 	addiu	$sp,$sp,-144
/*  f1194e4:	afb10034 */ 	sw	$s1,0x34($sp)
/*  f1194e8:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f1194ec:	00117603 */ 	sra	$t6,$s1,0x18
/*  f1194f0:	afa40090 */ 	sw	$a0,0x90($sp)
/*  f1194f4:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f1194f8:	afbf0054 */ 	sw	$ra,0x54($sp)
/*  f1194fc:	afb20038 */ 	sw	$s2,0x38($sp)
/*  f119500:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f119504:	00c09025 */ 	or	$s2,$a2,$zero
/*  f119508:	01c08825 */ 	or	$s1,$t6,$zero
/*  f11950c:	afbe0050 */ 	sw	$s8,0x50($sp)
/*  f119510:	afb7004c */ 	sw	$s7,0x4c($sp)
/*  f119514:	afb60048 */ 	sw	$s6,0x48($sp)
/*  f119518:	afb50044 */ 	sw	$s5,0x44($sp)
/*  f11951c:	afb40040 */ 	sw	$s4,0x40($sp)
/*  f119520:	afb3003c */ 	sw	$s3,0x3c($sp)
/*  f119524:	afb00030 */ 	sw	$s0,0x30($sp)
/*  f119528:	afa50094 */ 	sw	$a1,0x94($sp)
/*  f11952c:	0fc45c1b */ 	jal	pakGetMaxFileSize
/*  f119530:	01e02025 */ 	or	$a0,$t7,$zero
/*  f119534:	8fb80094 */ 	lw	$t8,0x94($sp)
/*  f119538:	00114880 */ 	sll	$t1,$s1,0x2
/*  f11953c:	01314823 */ 	subu	$t1,$t1,$s1
/*  f119540:	8f030000 */ 	lw	$v1,0x0($t8)
/*  f119544:	0040b825 */ 	or	$s7,$v0,$zero
/*  f119548:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11954c:	0060b025 */ 	or	$s6,$v1,$zero
/*  f119550:	0060f025 */ 	or	$s8,$v1,$zero
/*  f119554:	12400004 */ 	beqz	$s2,.L0f119568
/*  f119558:	00608025 */ 	or	$s0,$v1,$zero
/*  f11955c:	8e590008 */ 	lw	$t9,0x8($s2)
/*  f119560:	33280fff */ 	andi	$t0,$t9,0xfff
/*  f119564:	00688021 */ 	addu	$s0,$v1,$t0
.L0f119568:
/*  f119568:	01314823 */ 	subu	$t1,$t1,$s1
/*  f11956c:	00094880 */ 	sll	$t1,$t1,0x2
/*  f119570:	01314821 */ 	addu	$t1,$t1,$s1
/*  f119574:	00094880 */ 	sll	$t1,$t1,0x2
/*  f119578:	01314823 */ 	subu	$t1,$t1,$s1
/*  f11957c:	3c0a800a */ 	lui	$t2,%hi(g_Paks)
/*  f119580:	254a2380 */ 	addiu	$t2,$t2,%lo(g_Paks)
/*  f119584:	00094880 */ 	sll	$t1,$t1,0x2
/*  f119588:	012aa821 */ 	addu	$s5,$t1,$t2
/*  f11958c:	8eab02a0 */ 	lw	$t3,0x2a0($s5)
/*  f119590:	24140001 */ 	addiu	$s4,$zero,0x1
/*  f119594:	24130004 */ 	addiu	$s3,$zero,0x4
/*  f119598:	020b082b */ 	sltu	$at,$s0,$t3
/*  f11959c:	10200038 */ 	beqz	$at,.L0f119680
/*  f1195a0:	27b20080 */ 	addiu	$s2,$sp,0x80
/*  f1195a4:	00112600 */ 	sll	$a0,$s1,0x18
.L0f1195a8:
/*  f1195a8:	00046603 */ 	sra	$t4,$a0,0x18
/*  f1195ac:	01802025 */ 	or	$a0,$t4,$zero
/*  f1195b0:	02002825 */ 	or	$a1,$s0,$zero
/*  f1195b4:	0fc45d48 */ 	jal	pakReadHeaderAtOffset
/*  f1195b8:	02403025 */ 	or	$a2,$s2,$zero
/*  f1195bc:	14400009 */ 	bnez	$v0,.L0f1195e4
/*  f1195c0:	8fad0088 */ 	lw	$t5,0x88($sp)
/*  f1195c4:	000d75c2 */ 	srl	$t6,$t5,0x17
/*  f1195c8:	31cf0002 */ 	andi	$t7,$t6,0x2
/*  f1195cc:	15e00009 */ 	bnez	$t7,.L0f1195f4
/*  f1195d0:	03d0082b */ 	sltu	$at,$s8,$s0
/*  f1195d4:	50200008 */ 	beqzl	$at,.L0f1195f8
/*  f1195d8:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1195dc:	10000028 */ 	beqz	$zero,.L0f119680
/*  f1195e0:	00000000 */ 	sll	$zero,$zero,0x0
.L0f1195e4:
/*  f1195e4:	54540004 */ 	bnel	$v0,$s4,.L0f1195f8
/*  f1195e8:	00112600 */ 	sll	$a0,$s1,0x18
/*  f1195ec:	1000003b */ 	beqz	$zero,.L0f1196dc
/*  f1195f0:	00001025 */ 	or	$v0,$zero,$zero
.L0f1195f4:
/*  f1195f4:	00112600 */ 	sll	$a0,$s1,0x18
.L0f1195f8:
/*  f1195f8:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f1195fc:	0fc45974 */ 	jal	pakGetBlockSize
/*  f119600:	03002025 */ 	or	$a0,$t8,$zero
/*  f119604:	12330009 */ 	beq	$s1,$s3,.L0f11962c
/*  f119608:	02028021 */ 	addu	$s0,$s0,$v0
/*  f11960c:	0216c823 */ 	subu	$t9,$s0,$s6
/*  f119610:	02f9082b */ 	sltu	$at,$s7,$t9
/*  f119614:	50200006 */ 	beqzl	$at,.L0f119630
/*  f119618:	8ea202a0 */ 	lw	$v0,0x2a0($s5)
/*  f11961c:	8fa80094 */ 	lw	$t0,0x94($sp)
/*  f119620:	00001025 */ 	or	$v0,$zero,$zero
/*  f119624:	1000002d */ 	beqz	$zero,.L0f1196dc
/*  f119628:	ad100000 */ 	sw	$s0,0x0($t0)
.L0f11962c:
/*  f11962c:	8ea202a0 */ 	lw	$v0,0x2a0($s5)
.L0f119630:
/*  f119630:	0202082b */ 	sltu	$at,$s0,$v0
/*  f119634:	1420000f */ 	bnez	$at,.L0f119674
/*  f119638:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11963c:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f119640:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f119644:	afaa0020 */ 	sw	$t2,0x20($sp)
/*  f119648:	01202025 */ 	or	$a0,$t1,$zero
/*  f11964c:	02c02825 */ 	or	$a1,$s6,$zero
/*  f119650:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f119654:	00003825 */ 	or	$a3,$zero,$zero
/*  f119658:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f11965c:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f119660:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f119664:	0fc46f15 */ 	jal	pakWriteFileAtOffset
/*  f119668:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f11966c:	1000001b */ 	beqz	$zero,.L0f1196dc
/*  f119670:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f119674:
/*  f119674:	0202082b */ 	sltu	$at,$s0,$v0
/*  f119678:	5420ffcb */ 	bnezl	$at,.L0f1195a8
/*  f11967c:	00112600 */ 	sll	$a0,$s1,0x18
.L0f119680:
/*  f119680:	0fc459a1 */ 	jal	pakGetBodyLenByFileLen
/*  f119684:	02162023 */ 	subu	$a0,$s0,$s6
/*  f119688:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11968c:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f119690:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f119694:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f119698:	01602025 */ 	or	$a0,$t3,$zero
/*  f11969c:	02c02825 */ 	or	$a1,$s6,$zero
/*  f1196a0:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f1196a4:	00003825 */ 	or	$a3,$zero,$zero
/*  f1196a8:	afa20010 */ 	sw	$v0,0x10($sp)
/*  f1196ac:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f1196b0:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f1196b4:	0fc46f15 */ 	jal	pakWriteFileAtOffset
/*  f1196b8:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f1196bc:	10400005 */ 	beqz	$v0,.L0f1196d4
/*  f1196c0:	8fae0094 */ 	lw	$t6,0x94($sp)
/*  f1196c4:	8fad0094 */ 	lw	$t5,0x94($sp)
/*  f1196c8:	00001025 */ 	or	$v0,$zero,$zero
/*  f1196cc:	10000003 */ 	beqz	$zero,.L0f1196dc
/*  f1196d0:	adb00000 */ 	sw	$s0,0x0($t5)
.L0f1196d4:
/*  f1196d4:	add00000 */ 	sw	$s0,0x0($t6)
/*  f1196d8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f1196dc:
/*  f1196dc:	8fbf0054 */ 	lw	$ra,0x54($sp)
/*  f1196e0:	8fb00030 */ 	lw	$s0,0x30($sp)
/*  f1196e4:	8fb10034 */ 	lw	$s1,0x34($sp)
/*  f1196e8:	8fb20038 */ 	lw	$s2,0x38($sp)
/*  f1196ec:	8fb3003c */ 	lw	$s3,0x3c($sp)
/*  f1196f0:	8fb40040 */ 	lw	$s4,0x40($sp)
/*  f1196f4:	8fb50044 */ 	lw	$s5,0x44($sp)
/*  f1196f8:	8fb60048 */ 	lw	$s6,0x48($sp)
/*  f1196fc:	8fb7004c */ 	lw	$s7,0x4c($sp)
/*  f119700:	8fbe0050 */ 	lw	$s8,0x50($sp)
/*  f119704:	03e00008 */ 	jr	$ra
/*  f119708:	27bd0090 */ 	addiu	$sp,$sp,0x90
);

#if VERSION < VERSION_NTSC_FINAL
const char var7f1b407c_2[] = "Pak %d -> Pak_RepairAsBlank : Repairing as Blank, Offset=%u, pH=%x\n";
const char var7f1b407c_3[] = "Pak %d -> Pak_RepairAsBlank -> Summing @ offset=%u, ret=%d\n";
const char var7f1b407c_4[] = "Pak %d -> Pak_RepairAsBlank -> Fault Speads Over More Than One File - TERMINAL";
#endif
const char var7f1b409c[] = "Pak %d -> Pak_RepairAsBlank - St=%u, Ed=%u, Gap=%u, Blank Size=%u\n";
const char var7f1b40e0[] = "Pak %d -> Pak_RepairAsBlank - Fatal Error at tOffset %u\n";
#else
/**
 * Repair the pak by writing a blank file from the given offset up until the
 * start of the next file.
 *
 * If done successfully, update the value at the offset pointer with the end
 * offset of the blank file and return true.
 *
 * For controller paks, enforce a max file size. If the blank file would exceed
 * the max file size, store the current search offset in the pointer and return
 * false.
 *
 * If the end of the note/device is reached without finding the subequent file,
 * write a terminator file at the start address and return true. A blank file
 * is not written in this case.
 *
 * If an error code is returned by called functions, the value at the offset
 * pointer is not changed and the function returns false.
 *
 * If the header argument is not NULL, it's assumed it's the header
 * corresponding to the starting offset and the function takes a shortcut by
 * starting the scan at the end of the header.
 */
// ntsc-final mismatches due to regalloc
bool pakRepairAsBlank(s8 device, u32 *offsetptr, struct pakfileheader *header)
{
	struct pakfileheader iterheader;

	u32 maxfilesize = pakGetMaxFileSize(device);
	u32 start = *offsetptr;
	u32 start2 = *offsetptr;
	u32 offset = *offsetptr;
	s32 result;
	u32 bodylen;

#if VERSION < VERSION_NTSC_FINAL
	osSyncPrintf("Pak %d -> Pak_RepairAsBlank : Repairing as Blank, Offset=%u, pH=%x\n", device, offset, header);
#endif

	// Skip past the header if given
	if (header != NULL) {
		offset += header->filelen;
	}

	while (offset < g_Paks[device].pdnumbytes) {
		result = pakReadHeaderAtOffset(device, offset, &iterheader);

#if VERSION >= VERSION_NTSC_FINAL
		if (result == PAK_ERR2_OK) {
			// Found a valid header
			if ((iterheader.filetype & PAKFILETYPE_BLANK) == 0 && offset > start2) {
				break;
			}
		} else if (result == PAK_ERR2_NOPAK) {
			return false;
		}

		// No header at this offset
		offset += pakGetBlockSize(device);

		// For controller paks, consider giving up
		if (device != SAVEDEVICE_GAMEPAK && offset - start > maxfilesize) {
			osSyncPrintf("Pak %d -> Pak_RepairAsBlank -> Fault Speads Over More Than One File - TERMINAL", device);
			*offsetptr = offset;
			return false;
		}

		// If the end was reached, write a terminator at the starting offset
		if (offset >= g_Paks[device].pdnumbytes) {
			pakWriteFileAtOffset(device, start, PAKFILETYPE_TERMINATOR, NULL, 0, NULL, NULL, 0, 1);
			return true;
		}
#elif VERSION >= VERSION_NTSC_1_0
		osSyncPrintf("Pak %d -> Pak_RepairAsBlank -> Summing @ offset=%u, ret=%d\n", device, offset, result);

		if (result == PAK_ERR2_OK) {
			// Found a valid header
			if (iterheader.filetype & PAKFILETYPE_BLANK) {
				// empty
			} else {
				break;
			}
		} else if (result == PAK_ERR2_NOPAK) {
			return false;
		}

		// No header at this offset
		offset += pakGetBlockSize(device);

		if (offset - start > maxfilesize) {
			osSyncPrintf("Pak %d -> Pak_RepairAsBlank -> Fault Speads Over More Than One File - TERMINAL", device);
			*offsetptr = offset;
			return false;
		}
#else
		osSyncPrintf("Pak %d -> Pak_RepairAsBlank -> Summing @ offset=%u, ret=%d\n", device, offset, result);

		if (result == PAK_ERR2_OK) {
			// Found a valid header
			if (iterheader.filetype & PAKFILETYPE_BLANK) {
				// empty
			} else {
				break;
			}
		}

		// No header at this offset
		offset += pakGetBlockSize(device);

		if (offset - start > maxfilesize) {
			osSyncPrintf("Pak %d -> Pak_RepairAsBlank -> Fault Speads Over More Than One File - TERMINAL", device);
			*offsetptr = offset;
			return false;
		}
#endif
	}

	bodylen = pakGetBodyLenByFileLen(offset - start);

	osSyncPrintf("Pak %d -> Pak_RepairAsBlank - St=%u, Ed=%u, Gap=%u, Blank Size=%u\n", device, start, offset, offset - start, bodylen);

	// Write the blank file ranging from to the start to the current offset
	result = pakWriteFileAtOffset(device, start, PAKFILETYPE_BLANK, NULL, bodylen, NULL, NULL, 0, 1);

	if (result != 0) {
		osSyncPrintf("Pak %d -> Pak_RepairAsBlank - Fatal Error at tOffset %u\n", device, offset);
		*offsetptr = offset;
		return false;
	}

	*offsetptr = offset;
	return true;
}
#endif

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b411c[] = "Pak %d -> Pak_ValidateVersion - Start - Game File Size = %d\n";
const char var7f1b415c[] = "Pak %d -> Pak_ValidateVersion - Clearing cache 2\n";
const char var7f1b4190[] = "Pak %d -> Pak_ValidateVersion 1 - Loaded with ret=%d at offset %u\n";
const char var7f1b41d4[] = "Pak %d -> Pak_ValidateVersion 1 - Blank at %u\n";
const char var7f1b4204[] = "Pak %d -> Pak_ValidateVersion 2 - Loaded  at offset %u\n";
#endif

struct serialcount {
	u32 serial;
	s32 count;
};

/**
 * Attempt to repair the filesystem on the pak.
 *
 * ntsc-final:
 * - Ensures the same device serial is used across all files
 *
 * ntsc-1.0:
 * - Fixes the terminator if missing
 * - Changes return code to -1, 0 or 1, where:
 *     -1 means a fatal error occurred and the filesystem is hosed
 *     0 means the filesystem was fine or is now repaired
 *     1 means the pak is not inserted or the repair failed
 *
 * ntsc-beta:
 * - Removes duplicate files
 * - Removes files if header checksum mismatches
 * - Removes files if partially written
 * - Returns 1 if filesystem is good, or 0 if unrepairable
 */
#if VERSION == VERSION_PAL_BETA
GLOBAL_ASM(
glabel pakRepairFilesystem
/*  f119fac:	27bdf850 */ 	addiu	$sp,$sp,-1968
/*  f119fb0:	afb4003c */ 	sw	$s4,0x3c($sp)
/*  f119fb4:	0004a600 */ 	sll	$s4,$a0,0x18
/*  f119fb8:	00147603 */ 	sra	$t6,$s4,0x18
/*  f119fbc:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f119fc0:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f119fc4:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f119fc8:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f119fcc:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f119fd0:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f119fd4:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f119fd8:	afa407b0 */ 	sw	$a0,0x7b0($sp)
/*  f119fdc:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f119fe0:	3c18800a */ 	lui	$t8,0x800a
/*  f119fe4:	afb60044 */ 	sw	$s6,0x44($sp)
/*  f119fe8:	271868b0 */ 	addiu	$t8,$t8,0x68b0
/*  f119fec:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f119ff0:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f119ff4:	afbf004c */ 	sw	$ra,0x4c($sp)
/*  f119ff8:	afb70048 */ 	sw	$s7,0x48($sp)
/*  f119ffc:	afb10030 */ 	sw	$s1,0x30($sp)
/*  f11a000:	01f8b021 */ 	addu	$s6,$t7,$t8
/*  f11a004:	3419baba */ 	li	$t9,0xbaba
/*  f11a008:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11a00c:	01c0a025 */ 	move	$s4,$t6
/*  f11a010:	afb50040 */ 	sw	$s5,0x40($sp)
/*  f11a014:	afb30038 */ 	sw	$s3,0x38($sp)
/*  f11a018:	afb20034 */ 	sw	$s2,0x34($sp)
/*  f11a01c:	afb0002c */ 	sw	$s0,0x2c($sp)
/*  f11a020:	0000b825 */ 	move	$s7,$zero
/*  f11a024:	afa007a4 */ 	sw	$zero,0x7a4($sp)
/*  f11a028:	00008825 */ 	move	$s1,$zero
/*  f11a02c:	aed90260 */ 	sw	$t9,0x260($s6)
/*  f11a030:	a2c002be */ 	sb	$zero,0x2be($s6)
/*  f11a034:	0fc45c1e */ 	jal	pak0f1167d8
/*  f11a038:	01202025 */ 	move	$a0,$t1
/*  f11a03c:	50400004 */ 	beqzl	$v0,.PB0f11a050
/*  f11a040:	8eca02a0 */ 	lw	$t2,0x2a0($s6)
/*  f11a044:	1000017c */ 	b	.PB0f11a638
/*  f11a048:	24020001 */ 	li	$v0,0x1
/*  f11a04c:	8eca02a0 */ 	lw	$t2,0x2a0($s6)
.PB0f11a050:
/*  f11a050:	afa003a4 */ 	sw	$zero,0x3a4($sp)
/*  f11a054:	27b50474 */ 	addiu	$s5,$sp,0x474
/*  f11a058:	114000a6 */ 	beqz	$t2,.PB0f11a2f4
/*  f11a05c:	27b30484 */ 	addiu	$s3,$sp,0x484
/*  f11a060:	2412ffff */ 	li	$s2,-1
/*  f11a064:	00142600 */ 	sll	$a0,$s4,0x18
.PB0f11a068:
/*  f11a068:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11a06c:	01602025 */ 	move	$a0,$t3
/*  f11a070:	8fa503a4 */ 	lw	$a1,0x3a4($sp)
/*  f11a074:	0fc45f70 */ 	jal	pakReadHeaderAtOffset
/*  f11a078:	02a03025 */ 	move	$a2,$s5
/*  f11a07c:	14400071 */ 	bnez	$v0,.PB0f11a244
/*  f11a080:	24010001 */ 	li	$at,0x1
/*  f11a084:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a088:	8fae03a4 */ 	lw	$t6,0x3a4($sp)
/*  f11a08c:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a090:	000615c2 */ 	srl	$v0,$a2,0x17
/*  f11a094:	304c0002 */ 	andi	$t4,$v0,0x2
/*  f11a098:	15800096 */ 	bnez	$t4,.PB0f11a2f4
/*  f11a09c:	304d0004 */ 	andi	$t5,$v0,0x4
/*  f11a0a0:	15a00094 */ 	bnez	$t5,.PB0f11a2f4
/*  f11a0a4:	00001025 */ 	move	$v0,$zero
/*  f11a0a8:	8ed902a0 */ 	lw	$t9,0x2a0($s6)
/*  f11a0ac:	30cf0fff */ 	andi	$t7,$a2,0xfff
/*  f11a0b0:	01cfc021 */ 	addu	$t8,$t6,$t7
/*  f11a0b4:	0319082b */ 	sltu	$at,$t8,$t9
/*  f11a0b8:	14200010 */ 	bnez	$at,.PB0f11a0fc
/*  f11a0bc:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11a0c0:	240a0001 */ 	li	$t2,0x1
/*  f11a0c4:	afaa0020 */ 	sw	$t2,0x20($sp)
/*  f11a0c8:	01202025 */ 	move	$a0,$t1
/*  f11a0cc:	01c02825 */ 	move	$a1,$t6
/*  f11a0d0:	24060004 */ 	li	$a2,0x4
/*  f11a0d4:	00003825 */ 	move	$a3,$zero
/*  f11a0d8:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f11a0dc:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f11a0e0:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f11a0e4:	0fc47144 */ 	jal	pakWriteFileAtOffset
/*  f11a0e8:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f11a0ec:	50400082 */ 	beqzl	$v0,.PB0f11a2f8
/*  f11a0f0:	8fae07a4 */ 	lw	$t6,0x7a4($sp)
/*  f11a0f4:	10000079 */ 	b	.PB0f11a2dc
/*  f11a0f8:	24170001 */ 	li	$s7,0x1
.PB0f11a0fc:
/*  f11a0fc:	1220003c */ 	beqz	$s1,.PB0f11a1f0
/*  f11a100:	afa0039c */ 	sw	$zero,0x39c($sp)
/*  f11a104:	27a703a8 */ 	addiu	$a3,$sp,0x3a8
/*  f11a108:	8fa80480 */ 	lw	$t0,0x480($sp)
.PB0f11a10c:
/*  f11a10c:	8ceb0000 */ 	lw	$t3,0x0($a3)
/*  f11a110:	00026100 */ 	sll	$t4,$v0,0x4
/*  f11a114:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11a118:	124b0033 */ 	beq	$s2,$t3,.PB0f11a1e8
/*  f11a11c:	026c3021 */ 	addu	$a2,$s3,$t4
/*  f11a120:	8cc3000c */ 	lw	$v1,0xc($a2)
/*  f11a124:	00086b40 */ 	sll	$t5,$t0,0xd
/*  f11a128:	000d7e42 */ 	srl	$t7,$t5,0x19
/*  f11a12c:	0003c340 */ 	sll	$t8,$v1,0xd
/*  f11a130:	0018ce42 */ 	srl	$t9,$t8,0x19
/*  f11a134:	15f9002c */ 	bne	$t7,$t9,.PB0f11a1e8
/*  f11a138:	00087500 */ 	sll	$t6,$t0,0x14
/*  f11a13c:	00035d00 */ 	sll	$t3,$v1,0x14
/*  f11a140:	000b65c2 */ 	srl	$t4,$t3,0x17
/*  f11a144:	000e55c2 */ 	srl	$t2,$t6,0x17
/*  f11a148:	24090001 */ 	li	$t1,0x1
/*  f11a14c:	014c082b */ 	sltu	$at,$t2,$t4
/*  f11a150:	10200009 */ 	beqz	$at,.PB0f11a178
/*  f11a154:	afa9039c */ 	sw	$t1,0x39c($sp)
/*  f11a158:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a15c:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11a160:	01a02025 */ 	move	$a0,$t5
/*  f11a164:	27a503a4 */ 	addiu	$a1,$sp,0x3a4
/*  f11a168:	0fc46760 */ 	jal	pakRepairAsBlank
/*  f11a16c:	02a03025 */ 	move	$a2,$s5
/*  f11a170:	1000001f */ 	b	.PB0f11a1f0
/*  f11a174:	2c570001 */ 	sltiu	$s7,$v0,0x1
.PB0f11a178:
/*  f11a178:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a17c:	00117900 */ 	sll	$t7,$s1,0x4
/*  f11a180:	026fc821 */ 	addu	$t9,$s3,$t7
/*  f11a184:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f11a188:	00114880 */ 	sll	$t1,$s1,0x2
/*  f11a18c:	27ae03a8 */ 	addiu	$t6,$sp,0x3a8
/*  f11a190:	012e8021 */ 	addu	$s0,$t1,$t6
/*  f11a194:	03002025 */ 	move	$a0,$t8
/*  f11a198:	afb90054 */ 	sw	$t9,0x54($sp)
/*  f11a19c:	00e02825 */ 	move	$a1,$a3
/*  f11a1a0:	0fc46760 */ 	jal	pakRepairAsBlank
/*  f11a1a4:	afa7005c */ 	sw	$a3,0x5c($sp)
/*  f11a1a8:	8fa7005c */ 	lw	$a3,0x5c($sp)
/*  f11a1ac:	2c570001 */ 	sltiu	$s7,$v0,0x1
/*  f11a1b0:	02a02825 */ 	move	$a1,$s5
/*  f11a1b4:	acf20000 */ 	sw	$s2,0x0($a3)
/*  f11a1b8:	8fa40054 */ 	lw	$a0,0x54($sp)
/*  f11a1bc:	0c012ae8 */ 	jal	memcpy
/*  f11a1c0:	24060010 */ 	li	$a2,0x10
/*  f11a1c4:	8fab03a4 */ 	lw	$t3,0x3a4($sp)
/*  f11a1c8:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a1cc:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f11a1d0:	ae0b0000 */ 	sw	$t3,0x0($s0)
/*  f11a1d4:	8faa03a4 */ 	lw	$t2,0x3a4($sp)
/*  f11a1d8:	30cc0fff */ 	andi	$t4,$a2,0xfff
/*  f11a1dc:	014c6821 */ 	addu	$t5,$t2,$t4
/*  f11a1e0:	10000003 */ 	b	.PB0f11a1f0
/*  f11a1e4:	afad03a4 */ 	sw	$t5,0x3a4($sp)
.PB0f11a1e8:
/*  f11a1e8:	1451ffc8 */ 	bne	$v0,$s1,.PB0f11a10c
/*  f11a1ec:	24e70004 */ 	addiu	$a3,$a3,0x4
.PB0f11a1f0:
/*  f11a1f0:	8fb8039c */ 	lw	$t8,0x39c($sp)
/*  f11a1f4:	17000039 */ 	bnez	$t8,.PB0f11a2dc
/*  f11a1f8:	00000000 */ 	nop
/*  f11a1fc:	16e00037 */ 	bnez	$s7,.PB0f11a2dc
/*  f11a200:	00117900 */ 	sll	$t7,$s1,0x4
/*  f11a204:	0011c880 */ 	sll	$t9,$s1,0x2
/*  f11a208:	27a903a8 */ 	addiu	$t1,$sp,0x3a8
/*  f11a20c:	03298021 */ 	addu	$s0,$t9,$t1
/*  f11a210:	026f2021 */ 	addu	$a0,$s3,$t7
/*  f11a214:	02a02825 */ 	move	$a1,$s5
/*  f11a218:	0c012ae8 */ 	jal	memcpy
/*  f11a21c:	24060010 */ 	li	$a2,0x10
/*  f11a220:	8fae03a4 */ 	lw	$t6,0x3a4($sp)
/*  f11a224:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a228:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f11a22c:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f11a230:	8fab03a4 */ 	lw	$t3,0x3a4($sp)
/*  f11a234:	30ca0fff */ 	andi	$t2,$a2,0xfff
/*  f11a238:	016a6021 */ 	addu	$t4,$t3,$t2
/*  f11a23c:	10000027 */ 	b	.PB0f11a2dc
/*  f11a240:	afac03a4 */ 	sw	$t4,0x3a4($sp)
.PB0f11a244:
/*  f11a244:	14410003 */ 	bne	$v0,$at,.PB0f11a254
/*  f11a248:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a24c:	100000fa */ 	b	.PB0f11a638
/*  f11a250:	24020001 */ 	li	$v0,0x1
.PB0f11a254:
/*  f11a254:	24010007 */ 	li	$at,0x7
/*  f11a258:	14410007 */ 	bne	$v0,$at,.PB0f11a278
/*  f11a25c:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11a260:	01a02025 */ 	move	$a0,$t5
/*  f11a264:	27a503a4 */ 	addiu	$a1,$sp,0x3a4
/*  f11a268:	0fc46760 */ 	jal	pakRepairAsBlank
/*  f11a26c:	00003025 */ 	move	$a2,$zero
/*  f11a270:	1000001a */ 	b	.PB0f11a2dc
/*  f11a274:	2c570001 */ 	sltiu	$s7,$v0,0x1
.PB0f11a278:
/*  f11a278:	2401000f */ 	li	$at,0xf
/*  f11a27c:	1441000a */ 	bne	$v0,$at,.PB0f11a2a8
/*  f11a280:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a284:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f11a288:	03002025 */ 	move	$a0,$t8
/*  f11a28c:	27a503a4 */ 	addiu	$a1,$sp,0x3a4
/*  f11a290:	0fc46760 */ 	jal	pakRepairAsBlank
/*  f11a294:	02a03025 */ 	move	$a2,$s5
/*  f11a298:	14400010 */ 	bnez	$v0,.PB0f11a2dc
/*  f11a29c:	00000000 */ 	nop
/*  f11a2a0:	10000014 */ 	b	.PB0f11a2f4
/*  f11a2a4:	24170001 */ 	li	$s7,0x1
.PB0f11a2a8:
/*  f11a2a8:	24100009 */ 	li	$s0,0x9
/*  f11a2ac:	14500004 */ 	bne	$v0,$s0,.PB0f11a2c0
/*  f11a2b0:	24010004 */ 	li	$at,0x4
/*  f11a2b4:	240f0001 */ 	li	$t7,0x1
/*  f11a2b8:	1000000e */ 	b	.PB0f11a2f4
/*  f11a2bc:	afaf07a4 */ 	sw	$t7,0x7a4($sp)
.PB0f11a2c0:
/*  f11a2c0:	1041000c */ 	beq	$v0,$at,.PB0f11a2f4
/*  f11a2c4:	24170001 */ 	li	$s7,0x1
/*  f11a2c8:	2401000b */ 	li	$at,0xb
/*  f11a2cc:	5441000a */ 	bnel	$v0,$at,.PB0f11a2f8
/*  f11a2d0:	8fae07a4 */ 	lw	$t6,0x7a4($sp)
/*  f11a2d4:	10000008 */ 	b	.PB0f11a2f8
/*  f11a2d8:	8fae07a4 */ 	lw	$t6,0x7a4($sp)
.PB0f11a2dc:
/*  f11a2dc:	16e00005 */ 	bnez	$s7,.PB0f11a2f4
/*  f11a2e0:	8fb903a4 */ 	lw	$t9,0x3a4($sp)
/*  f11a2e4:	8ec902a0 */ 	lw	$t1,0x2a0($s6)
/*  f11a2e8:	0329082b */ 	sltu	$at,$t9,$t1
/*  f11a2ec:	5420ff5e */ 	bnezl	$at,.PB0f11a068
/*  f11a2f0:	00142600 */ 	sll	$a0,$s4,0x18
.PB0f11a2f4:
/*  f11a2f4:	8fae07a4 */ 	lw	$t6,0x7a4($sp)
.PB0f11a2f8:
/*  f11a2f8:	24100009 */ 	li	$s0,0x9
/*  f11a2fc:	27b50474 */ 	addiu	$s5,$sp,0x474
/*  f11a300:	15c0003d */ 	bnez	$t6,.PB0f11a3f8
/*  f11a304:	afa003a4 */ 	sw	$zero,0x3a4($sp)
/*  f11a308:	56e0003c */ 	bnezl	$s7,.PB0f11a3fc
/*  f11a30c:	8fb907a4 */ 	lw	$t9,0x7a4($sp)
/*  f11a310:	8ecb02a0 */ 	lw	$t3,0x2a0($s6)
/*  f11a314:	11600038 */ 	beqz	$t3,.PB0f11a3f8
/*  f11a318:	00142600 */ 	sll	$a0,$s4,0x18
.PB0f11a31c:
/*  f11a31c:	00045603 */ 	sra	$t2,$a0,0x18
/*  f11a320:	01402025 */ 	move	$a0,$t2
/*  f11a324:	8fa503a4 */ 	lw	$a1,0x3a4($sp)
/*  f11a328:	0fc45f70 */ 	jal	pakReadHeaderAtOffset
/*  f11a32c:	02a03025 */ 	move	$a2,$s5
/*  f11a330:	14400017 */ 	bnez	$v0,.PB0f11a390
/*  f11a334:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a338:	000615c2 */ 	srl	$v0,$a2,0x17
/*  f11a33c:	304c0002 */ 	andi	$t4,$v0,0x2
/*  f11a340:	11800003 */ 	beqz	$t4,.PB0f11a350
/*  f11a344:	8fad03a4 */ 	lw	$t5,0x3a4($sp)
/*  f11a348:	1000000b */ 	b	.PB0f11a378
/*  f11a34c:	30430004 */ 	andi	$v1,$v0,0x4
.PB0f11a350:
/*  f11a350:	11a00003 */ 	beqz	$t5,.PB0f11a360
/*  f11a354:	8fa80480 */ 	lw	$t0,0x480($sp)
/*  f11a358:	10000007 */ 	b	.PB0f11a378
/*  f11a35c:	30430004 */ 	andi	$v1,$v0,0x4
.PB0f11a360:
/*  f11a360:	0008c4c2 */ 	srl	$t8,$t0,0x13
/*  f11a364:	30430004 */ 	andi	$v1,$v0,0x4
/*  f11a368:	10600003 */ 	beqz	$v1,.PB0f11a378
/*  f11a36c:	aed80260 */ 	sw	$t8,0x260($s6)
/*  f11a370:	100000b1 */ 	b	.PB0f11a638
/*  f11a374:	00001025 */ 	move	$v0,$zero
.PB0f11a378:
/*  f11a378:	1460001f */ 	bnez	$v1,.PB0f11a3f8
/*  f11a37c:	8faf03a4 */ 	lw	$t7,0x3a4($sp)
/*  f11a380:	30d90fff */ 	andi	$t9,$a2,0xfff
/*  f11a384:	01f94821 */ 	addu	$t1,$t7,$t9
/*  f11a388:	10000011 */ 	b	.PB0f11a3d0
/*  f11a38c:	afa903a4 */ 	sw	$t1,0x3a4($sp)
.PB0f11a390:
/*  f11a390:	14500008 */ 	bne	$v0,$s0,.PB0f11a3b4
/*  f11a394:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a398:	8fab03a4 */ 	lw	$t3,0x3a4($sp)
/*  f11a39c:	30ca0fff */ 	andi	$t2,$a2,0xfff
/*  f11a3a0:	240e0001 */ 	li	$t6,0x1
/*  f11a3a4:	016a6021 */ 	addu	$t4,$t3,$t2
/*  f11a3a8:	afae07a4 */ 	sw	$t6,0x7a4($sp)
/*  f11a3ac:	10000008 */ 	b	.PB0f11a3d0
/*  f11a3b0:	afac03a4 */ 	sw	$t4,0x3a4($sp)
.PB0f11a3b4:
/*  f11a3b4:	24010001 */ 	li	$at,0x1
/*  f11a3b8:	14410003 */ 	bne	$v0,$at,.PB0f11a3c8
/*  f11a3bc:	00000000 */ 	nop
/*  f11a3c0:	1000009d */ 	b	.PB0f11a638
/*  f11a3c4:	24020001 */ 	li	$v0,0x1
.PB0f11a3c8:
/*  f11a3c8:	1000009b */ 	b	.PB0f11a638
/*  f11a3cc:	24020001 */ 	li	$v0,0x1
.PB0f11a3d0:
/*  f11a3d0:	8fad07a4 */ 	lw	$t5,0x7a4($sp)
/*  f11a3d4:	8fb803a4 */ 	lw	$t8,0x3a4($sp)
/*  f11a3d8:	55a00008 */ 	bnezl	$t5,.PB0f11a3fc
/*  f11a3dc:	8fb907a4 */ 	lw	$t9,0x7a4($sp)
/*  f11a3e0:	56e00006 */ 	bnezl	$s7,.PB0f11a3fc
/*  f11a3e4:	8fb907a4 */ 	lw	$t9,0x7a4($sp)
/*  f11a3e8:	8ecf02a0 */ 	lw	$t7,0x2a0($s6)
/*  f11a3ec:	030f082b */ 	sltu	$at,$t8,$t7
/*  f11a3f0:	5420ffca */ 	bnezl	$at,.PB0f11a31c
/*  f11a3f4:	00142600 */ 	sll	$a0,$s4,0x18
.PB0f11a3f8:
/*  f11a3f8:	8fb907a4 */ 	lw	$t9,0x7a4($sp)
.PB0f11a3fc:
/*  f11a3fc:	17200079 */ 	bnez	$t9,.PB0f11a5e4
/*  f11a400:	00000000 */ 	nop
/*  f11a404:	16e00077 */ 	bnez	$s7,.PB0f11a5e4
/*  f11a408:	00000000 */ 	nop
/*  f11a40c:	8ec902a0 */ 	lw	$t1,0x2a0($s6)
/*  f11a410:	00008025 */ 	move	$s0,$zero
/*  f11a414:	afa003a4 */ 	sw	$zero,0x3a4($sp)
/*  f11a418:	1120002e */ 	beqz	$t1,.PB0f11a4d4
/*  f11a41c:	27b2007c */ 	addiu	$s2,$sp,0x7c
/*  f11a420:	24110001 */ 	li	$s1,0x1
.PB0f11a424:
/*  f11a424:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a428:	00047603 */ 	sra	$t6,$a0,0x18
/*  f11a42c:	01c02025 */ 	move	$a0,$t6
/*  f11a430:	8fa503a4 */ 	lw	$a1,0x3a4($sp)
/*  f11a434:	0fc45f70 */ 	jal	pakReadHeaderAtOffset
/*  f11a438:	02a03025 */ 	move	$a2,$s5
/*  f11a43c:	14400025 */ 	bnez	$v0,.PB0f11a4d4
/*  f11a440:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a444:	000615c2 */ 	srl	$v0,$a2,0x17
/*  f11a448:	304b0002 */ 	andi	$t3,$v0,0x2
/*  f11a44c:	1560001a */ 	bnez	$t3,.PB0f11a4b8
/*  f11a450:	304a0004 */ 	andi	$t2,$v0,0x4
/*  f11a454:	1540001f */ 	bnez	$t2,.PB0f11a4d4
/*  f11a458:	00002825 */ 	move	$a1,$zero
/*  f11a45c:	1a00000e */ 	blez	$s0,.PB0f11a498
/*  f11a460:	00001825 */ 	move	$v1,$zero
/*  f11a464:	8fa80480 */ 	lw	$t0,0x480($sp)
/*  f11a468:	27a2007c */ 	addiu	$v0,$sp,0x7c
/*  f11a46c:	000824c2 */ 	srl	$a0,$t0,0x13
.PB0f11a470:
/*  f11a470:	8c4c0000 */ 	lw	$t4,0x0($v0)
/*  f11a474:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11a478:	148c0005 */ 	bne	$a0,$t4,.PB0f11a490
/*  f11a47c:	00000000 */ 	nop
/*  f11a480:	8c4d0004 */ 	lw	$t5,0x4($v0)
/*  f11a484:	02202825 */ 	move	$a1,$s1
/*  f11a488:	25b80001 */ 	addiu	$t8,$t5,0x1
/*  f11a48c:	ac580004 */ 	sw	$t8,0x4($v0)
.PB0f11a490:
/*  f11a490:	1470fff7 */ 	bne	$v1,$s0,.PB0f11a470
/*  f11a494:	24420008 */ 	addiu	$v0,$v0,0x8
.PB0f11a498:
/*  f11a498:	14a00007 */ 	bnez	$a1,.PB0f11a4b8
/*  f11a49c:	8fa80480 */ 	lw	$t0,0x480($sp)
/*  f11a4a0:	001078c0 */ 	sll	$t7,$s0,0x3
/*  f11a4a4:	024f1021 */ 	addu	$v0,$s2,$t7
/*  f11a4a8:	0008ccc2 */ 	srl	$t9,$t0,0x13
/*  f11a4ac:	ac590000 */ 	sw	$t9,0x0($v0)
/*  f11a4b0:	ac510004 */ 	sw	$s1,0x4($v0)
/*  f11a4b4:	26100001 */ 	addiu	$s0,$s0,0x1
.PB0f11a4b8:
/*  f11a4b8:	8fa903a4 */ 	lw	$t1,0x3a4($sp)
/*  f11a4bc:	8ecc02a0 */ 	lw	$t4,0x2a0($s6)
/*  f11a4c0:	30ce0fff */ 	andi	$t6,$a2,0xfff
/*  f11a4c4:	012e5821 */ 	addu	$t3,$t1,$t6
/*  f11a4c8:	016c082b */ 	sltu	$at,$t3,$t4
/*  f11a4cc:	1420ffd5 */ 	bnez	$at,.PB0f11a424
/*  f11a4d0:	afab03a4 */ 	sw	$t3,0x3a4($sp)
.PB0f11a4d4:
/*  f11a4d4:	2a010002 */ 	slti	$at,$s0,0x2
/*  f11a4d8:	14200040 */ 	bnez	$at,.PB0f11a5dc
/*  f11a4dc:	27b2007c */ 	addiu	$s2,$sp,0x7c
/*  f11a4e0:	2406ffff */ 	li	$a2,-1
/*  f11a4e4:	2405ffff */ 	li	$a1,-1
/*  f11a4e8:	1a00000b */ 	blez	$s0,.PB0f11a518
/*  f11a4ec:	00001825 */ 	move	$v1,$zero
/*  f11a4f0:	27a2007c */ 	addiu	$v0,$sp,0x7c
.PB0f11a4f4:
/*  f11a4f4:	8c440004 */ 	lw	$a0,0x4($v0)
/*  f11a4f8:	00a4082a */ 	slt	$at,$a1,$a0
/*  f11a4fc:	50200004 */ 	beqzl	$at,.PB0f11a510
/*  f11a500:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11a504:	00603025 */ 	move	$a2,$v1
/*  f11a508:	00802825 */ 	move	$a1,$a0
/*  f11a50c:	24630001 */ 	addiu	$v1,$v1,0x1
.PB0f11a510:
/*  f11a510:	1470fff8 */ 	bne	$v1,$s0,.PB0f11a4f4
/*  f11a514:	24420008 */ 	addiu	$v0,$v0,0x8
.PB0f11a518:
/*  f11a518:	2401ffff */ 	li	$at,-1
/*  f11a51c:	10c10031 */ 	beq	$a2,$at,.PB0f11a5e4
/*  f11a520:	000668c0 */ 	sll	$t5,$a2,0x3
/*  f11a524:	024dc021 */ 	addu	$t8,$s2,$t5
/*  f11a528:	8f020000 */ 	lw	$v0,0x0($t8)
/*  f11a52c:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a530:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f11a534:	2c410010 */ 	sltiu	$at,$v0,0x10
/*  f11a538:	10200004 */ 	beqz	$at,.PB0f11a54c
/*  f11a53c:	aec20260 */ 	sw	$v0,0x260($s6)
/*  f11a540:	0fc45bcb */ 	jal	pakGenerateSerial
/*  f11a544:	01e02025 */ 	move	$a0,$t7
/*  f11a548:	aec20260 */ 	sw	$v0,0x260($s6)
.PB0f11a54c:
/*  f11a54c:	8ed902a0 */ 	lw	$t9,0x2a0($s6)
/*  f11a550:	afa003a4 */ 	sw	$zero,0x3a4($sp)
/*  f11a554:	13200023 */ 	beqz	$t9,.PB0f11a5e4
.PB0f11a558:
/*  f11a558:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a55c:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11a560:	01202025 */ 	move	$a0,$t1
/*  f11a564:	8fa503a4 */ 	lw	$a1,0x3a4($sp)
/*  f11a568:	0fc45f70 */ 	jal	pakReadHeaderAtOffset
/*  f11a56c:	02a03025 */ 	move	$a2,$s5
/*  f11a570:	1440001c */ 	bnez	$v0,.PB0f11a5e4
/*  f11a574:	8fa6047c */ 	lw	$a2,0x47c($sp)
/*  f11a578:	000615c2 */ 	srl	$v0,$a2,0x17
/*  f11a57c:	304e0002 */ 	andi	$t6,$v0,0x2
/*  f11a580:	15c0000d */ 	bnez	$t6,.PB0f11a5b8
/*  f11a584:	304b0004 */ 	andi	$t3,$v0,0x4
/*  f11a588:	15600016 */ 	bnez	$t3,.PB0f11a5e4
/*  f11a58c:	8fa80480 */ 	lw	$t0,0x480($sp)
/*  f11a590:	8ecc0260 */ 	lw	$t4,0x260($s6)
/*  f11a594:	000854c2 */ 	srl	$t2,$t0,0x13
/*  f11a598:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a59c:	114c0006 */ 	beq	$t2,$t4,.PB0f11a5b8
/*  f11a5a0:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11a5a4:	01a02025 */ 	move	$a0,$t5
/*  f11a5a8:	8fa503a4 */ 	lw	$a1,0x3a4($sp)
/*  f11a5ac:	0fc46746 */ 	jal	pakWriteBlankFile
/*  f11a5b0:	02a03025 */ 	move	$a2,$s5
/*  f11a5b4:	8fa6047c */ 	lw	$a2,0x47c($sp)
.PB0f11a5b8:
/*  f11a5b8:	8fb803a4 */ 	lw	$t8,0x3a4($sp)
/*  f11a5bc:	8ece02a0 */ 	lw	$t6,0x2a0($s6)
/*  f11a5c0:	30cf0fff */ 	andi	$t7,$a2,0xfff
/*  f11a5c4:	030fc821 */ 	addu	$t9,$t8,$t7
/*  f11a5c8:	032e082b */ 	sltu	$at,$t9,$t6
/*  f11a5cc:	1420ffe2 */ 	bnez	$at,.PB0f11a558
/*  f11a5d0:	afb903a4 */ 	sw	$t9,0x3a4($sp)
/*  f11a5d4:	10000003 */ 	b	.PB0f11a5e4
/*  f11a5d8:	00000000 */ 	nop
.PB0f11a5dc:
/*  f11a5dc:	8fab007c */ 	lw	$t3,0x7c($sp)
/*  f11a5e0:	aecb0260 */ 	sw	$t3,0x260($s6)
.PB0f11a5e4:
/*  f11a5e4:	12e00003 */ 	beqz	$s7,.PB0f11a5f4
/*  f11a5e8:	8faa07a4 */ 	lw	$t2,0x7a4($sp)
/*  f11a5ec:	10000012 */ 	b	.PB0f11a638
/*  f11a5f0:	2402ffff */ 	li	$v0,-1
.PB0f11a5f4:
/*  f11a5f4:	11400003 */ 	beqz	$t2,.PB0f11a604
/*  f11a5f8:	24010004 */ 	li	$at,0x4
/*  f11a5fc:	1000000e */ 	b	.PB0f11a638
/*  f11a600:	2402ffff */ 	li	$v0,-1
.PB0f11a604:
/*  f11a604:	5281000c */ 	beql	$s4,$at,.PB0f11a638
/*  f11a608:	00001025 */ 	move	$v0,$zero
/*  f11a60c:	8ecc0260 */ 	lw	$t4,0x260($s6)
/*  f11a610:	00142600 */ 	sll	$a0,$s4,0x18
/*  f11a614:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11a618:	55800007 */ 	bnezl	$t4,.PB0f11a638
/*  f11a61c:	00001025 */ 	move	$v0,$zero
/*  f11a620:	0fc45bcb */ 	jal	pakGenerateSerial
/*  f11a624:	01a02025 */ 	move	$a0,$t5
/*  f11a628:	aec20260 */ 	sw	$v0,0x260($s6)
/*  f11a62c:	10000002 */ 	b	.PB0f11a638
/*  f11a630:	2402ffff */ 	li	$v0,-1
/*  f11a634:	00001025 */ 	move	$v0,$zero
.PB0f11a638:
/*  f11a638:	8fbf004c */ 	lw	$ra,0x4c($sp)
/*  f11a63c:	8fb0002c */ 	lw	$s0,0x2c($sp)
/*  f11a640:	8fb10030 */ 	lw	$s1,0x30($sp)
/*  f11a644:	8fb20034 */ 	lw	$s2,0x34($sp)
/*  f11a648:	8fb30038 */ 	lw	$s3,0x38($sp)
/*  f11a64c:	8fb4003c */ 	lw	$s4,0x3c($sp)
/*  f11a650:	8fb50040 */ 	lw	$s5,0x40($sp)
/*  f11a654:	8fb60044 */ 	lw	$s6,0x44($sp)
/*  f11a658:	8fb70048 */ 	lw	$s7,0x48($sp)
/*  f11a65c:	03e00008 */ 	jr	$ra
/*  f11a660:	27bd07b0 */ 	addiu	$sp,$sp,0x7b0
);
#else
s32 pakRepairFilesystem(s8 device)
{
	s32 ret;
	bool fatal = false;
	bool foundotherversion = false;
	struct pakfileheader headers[50];
	struct pakfileheader header;
	s32 numheaders = 0;
	u32 headeroffsets[50];
	u32 offset;
#if VERSION >= VERSION_NTSC_FINAL
	s32 i;
	bool foundduplicate;
	struct serialcount serials[100];
	u32 stack[1];
#else
	bool foundduplicate;
#endif

#if VERSION >= VERSION_NTSC_1_0
	if (device);
	if (device);
	if (device);
	if (device);
	if (device);
	if (device);
#endif

	g_Paks[device].serial = (VERSION >= VERSION_NTSC_1_0 ? 0xbaba : 0);
	g_Paks[device].headercachecount = 0;

	if (pak0f1167d8(device) != 0) {
		return (VERSION >= VERSION_NTSC_1_0 ? 1 : 0);
	}

	// Iterate the headers on the pak and copy each one onto the stack.
	// As each header is read, check if a duplicate exists on the stack.
	// If a duplicate is found, blank the oldest one.
	// Stop when the end is reached, or a blank file or terminator is found.
	// If any headers are unreadable, replace them with a blank file.
	offset = 0;

	while (!fatal && offset < g_Paks[device].pdnumbytes) {
		ret = pakReadHeaderAtOffset(device, offset, &header);

		if (ret == PAK_ERR2_OK) {
			if (header.filetype & PAKFILETYPE_BLANK) {
#if VERSION >= VERSION_NTSC_FINAL
				break;
#else
				fatal = !pakRepairAsBlank(device, &offset, NULL);
				continue;
#endif
			}

			if (header.filetype & PAKFILETYPE_TERMINATOR) {
				break;
			}

#if VERSION >= VERSION_NTSC_1_0
			if (offset + header.filelen >= g_Paks[device].pdnumbytes)
#else
			if (false)
#endif
			{
				// File overflows the device length -> replace with terminator
				ret = pakWriteFileAtOffset(device, offset, PAKFILETYPE_TERMINATOR, NULL, 0, NULL, NULL, 0, 1);

				if (ret != 0) {
					fatal = true;
				} else {
					break;
				}
			} else {
				// Check for duplicates
				s32 i;
				foundduplicate = false;

				for (i = 0; i != numheaders; i++) {
					if (headeroffsets[i] != -1 && header.fileid == headers[i].fileid) {
						foundduplicate = true;

						if (header.generation < headers[i].generation) {
							// The header that was just read is older -> delete it
							fatal = pakRepairAsBlank(device, &offset, &header) == 0;
						} else {
							// The header that was just read is newer -> delete the older one
							fatal = pakRepairAsBlank(device, &headeroffsets[i], &headers[i]) == 0;
							headeroffsets[i] = -1;

							// Add this header to the list
							memcpy(&headers[numheaders], &header, sizeof(header));
							headeroffsets[numheaders] = offset;
							numheaders++;

							offset += header.filelen;
						}

						break;
					}
				}

				if (!foundduplicate && !fatal) {
					memcpy(&headers[numheaders], &header, sizeof(header));
					headeroffsets[numheaders] = offset;
					numheaders++;

					offset += header.filelen;
				}
			}
		} else {
#if VERSION >= VERSION_NTSC_1_0
			if (ret == PAK_ERR2_NOPAK) {
				return 1;
			} else if (ret == PAK_ERR2_CHECKSUM) {
				fatal = pakRepairAsBlank(device, &offset, NULL) == false;
			} else if (ret == PAK_ERR2_INCOMPLETE) {
				if (!pakRepairAsBlank(device, &offset, &header)) {
					fatal = true;
					break;
				}
			} else if (ret == PAK_ERR2_VERSION) {
				foundotherversion = true;
				break;
			} else if (ret == PAK_ERR2_BADOFFSET) {
				fatal = true;
				break;
			} else if (ret == PAK_ERR2_CORRUPT) {
				fatal = true;
				break;
			} else {
				fatal = true;
				break;
			}
#else
			if (ret == PAK_ERR2_CHECKSUM) {
				fatal = pakRepairAsBlank(device, &offset, NULL) == false;
			} else if (ret == PAK_ERR2_INCOMPLETE) {
				fatal = pakRepairAsBlank(device, &offset, &header) == false;
			} else if (ret == PAK_ERR2_VERSION) {
				foundotherversion = true;
				break;
			} else if (ret == PAK_ERR2_BADOFFSET || ret == PAK_ERR2_NOPAK || ret == PAK_ERR2_CORRUPT) {
				return 0;
			} else {
				return 0;
			}
#endif
		}

#if VERSION < VERSION_NTSC_1_0
		if (offset);
#endif
	}

	// Recheck all the headers.
	// Return 0 if the first file was a terminator (ie. pak is empty).
	// Return 1 if any header still has problems.
	offset = 0;

#if VERSION >= VERSION_NTSC_1_0
	while (!foundotherversion && !fatal && offset < g_Paks[device].pdnumbytes) {
		ret = pakReadHeaderAtOffset(device, offset, &header);

		if (ret == 0) { // success
			if (header.filetype & PAKFILETYPE_BLANK) {
				// empty
			} else if (offset) {
#if VERSION < VERSION_NTSC_FINAL
				if (header.deviceserial != g_Paks[device].serial) {
					if (pakRepairAsBlank(device, &offset, &header)) {
						// empty
					} else {
						fatal = true;
					}
				}

				g_Paks[device].serial = header.deviceserial;
#endif
			} else {
				g_Paks[device].serial = header.deviceserial;

				if (header.filetype & PAKFILETYPE_TERMINATOR) {
					return 0;
				}
			}

			if ((header.filetype & PAKFILETYPE_TERMINATOR) == 0) {
				offset += header.filelen;
			} else {
				break;
			}
		} else if (ret == PAK_ERR2_VERSION) {
			foundotherversion = true;
			offset += header.filelen;
		} else if (ret == PAK_ERR2_NOPAK) {
			return 1;
		} else {
			return (VERSION >= VERSION_NTSC_FINAL ? 1 : -1);
		}
	}
#else
	while (!foundotherversion && !fatal && offset < g_Paks[device].pdnumbytes) {
		ret = pakReadHeaderAtOffset(device, offset, &header);

		if (ret == PAK_ERR2_OK) {
			if (header.filetype & PAKFILETYPE_TERMINATOR) {
				break;
			} else if (header.filetype & PAKFILETYPE_BLANK) {
				// emtpy
			} else if (offset) {
				if (header.deviceserial);
				g_Paks[device].serial = header.deviceserial;
			} else {
				g_Paks[device].serial = header.deviceserial;

			}

			offset += header.filelen;
		} else if (ret == PAK_ERR2_VERSION) {
			foundotherversion = true;
			offset += header.filelen;
		} else {
			return 0;
		}
	}
#endif

#if VERSION >= VERSION_NTSC_FINAL
	// NTSC Final ensures serials are all the same
	if (!foundotherversion && !fatal) {
		// Build list of serials and how many times each was found.
		// There should only be one serial across all files.
		s32 numserials = 0;
		offset = 0;

		while (offset < g_Paks[device].pdnumbytes) {
			ret = pakReadHeaderAtOffset(device, offset, &header);

			if (ret == PAK_ERR2_NOPAK);

			if (ret != PAK_ERR2_OK) {
				break;
			}

			if ((header.filetype & PAKFILETYPE_BLANK) == 0) {
				bool found = false;

				if (header.filetype & PAKFILETYPE_TERMINATOR) {
					break;
				}

				for (i = 0; i < numserials; i++) {
					if (serials[i].serial == header.deviceserial) {
						found = true;
						serials[i].count++;
					}
				}

				if (!found) {
					serials[numserials].serial = header.deviceserial;
					serials[numserials].count = 1;
					numserials++;
				}
			}

			offset += header.filelen;

			if (offset);
		}

		if (numserials >= 2) {
			// Decide which serial to use based on majority
			s32 bestindex = -1;
			s32 bestcount = -1;

			for (i = 0; i < numserials; i++) {
				if (serials[i].count > bestcount) {
					bestindex = i;
					bestcount = serials[i].count;
				}
			}

			if (bestindex != -1) {
				// Apply the chosen serial
				g_Paks[device].serial = serials[bestindex].serial;

#if VERSION >= VERSION_PAL_FINAL
				if (g_Paks[device].serial < 0x10) {
					g_Paks[device].serial = pakGenerateSerial(device);
				}
#endif

				offset = 0;

				while (offset < g_Paks[device].pdnumbytes) {
					ret = pakReadHeaderAtOffset(device, offset, &header);

					if (ret != PAK_ERR2_OK) {
						break;
					}

					if ((header.filetype & PAKFILETYPE_BLANK) == 0) {
						if (header.filetype & PAKFILETYPE_TERMINATOR) {
							break;
						}

						if (header.deviceserial != g_Paks[device].serial) {
							pakWriteBlankFile(device, offset, &header);
						}
					}

					offset += header.filelen;

					if (offset);
				}
			}
		} else {
			g_Paks[device].serial = serials[0].serial;
		}
	}
#endif

	if (fatal) {
		return (VERSION >= VERSION_NTSC_1_0 ? -1 : 0);
	}

	if (foundotherversion) {
		return (VERSION >= VERSION_NTSC_1_0 ? -1 : 0);
	}

#if VERSION >= VERSION_NTSC_1_0
	if (device != SAVEDEVICE_GAMEPAK && g_Paks[device].serial == 0) {
		g_Paks[device].serial = pakGenerateSerial(device);
		return -1;
	}
#else
	if (device != SAVEDEVICE_GAMEPAK && g_Paks[device].serial == 0) {
		g_Paks[device].serial = 0x10 + random() % 0x1ff0;
		return 0;
	}
#endif

	return (VERSION >= VERSION_NTSC_1_0 ? 0 : 1);
}
#endif

#if VERSION >= VERSION_NTSC_1_0
/**
 * Find all game files on the game pak and write random data into them.
 * This should cause a checksum mismatch the next time the file is read.
 */
void pakCorrupt(void)
{
	struct pakfileheader header;
	u32 fileids[1025];
	s32 address;
	s32 i;
	s32 j;
	u8 payload[8];

	pakGetFileIdsByType(SAVEDEVICE_GAMEPAK, PAKFILETYPE_GAME, fileids);

	for (i = 0; fileids[i] != 0; i++) {
		for (j = 0; j < 8; j++) {
			payload[j] = random() & 0xff;
		}

		address = pakFindFile(SAVEDEVICE_GAMEPAK, fileids[i], &header);
		address += i * 8;
		address += 0x30;

		joyDisableCyclicPolling();
		osEepromLongWrite(&g_PiMesgQueue, address, payload, sizeof(payload));
		joyEnableCyclicPolling();
	}
}
#endif

/**
 * Create the initial files on a pak. Return true if all good.
 *
 * NTSC Beta forgets to include return values.
 */
bool pakCreateInitialFiles(s8 device)
{
	struct pakfileheader header;
	s32 i;
	u32 fileids[1024];
	s32 j;
	u32 stack[2];

	u32 filetypes[] = {
		PAKFILETYPE_BOSS,
		PAKFILETYPE_CAMERA,
		PAKFILETYPE_MPPLAYER,
		PAKFILETYPE_MPSETUP,
		PAKFILETYPE_GAME,
	};

	u32 filecounts[] = { 2, 3, 5, 5, 5 };

#if VERSION >= VERSION_NTSC_1_0
	char *filenames[] = { "BOS\n", "CAM\n", "MPP\n", "MPG\n", "GAM" };
#else
	char *filenames[] = { "BOS", "CAM", "MPP", "MPG", "GAM" };
#endif

	// Iterate all files on the pak and decrease the counts per filetype
	if (pakGetFileIdsByType(device, PAKFILETYPE_ALL, fileids) != 0) {
#if VERSION >= VERSION_NTSC_1_0
		return false;
#else
		return;
#endif
	}

	for (i = 0; fileids[i] != 0; i++) {
#if VERSION >= VERSION_NTSC_1_0
		if (pakFindFile(device, fileids[i], &header) == -1) {
			return false;
		}
#else
		pakFindFile(device, fileids[i], &header);
#endif

		for (j = 0; j < ARRAYCOUNT(filetypes); j++) {
			if (header.filetype == filetypes[j]) {
				if (filecounts[j]) {
					filecounts[j]--;
				}
				break;
			}
		}
	}

	// Create files
#if VERSION >= VERSION_NTSC_1_0
	for (i = 0; i < ARRAYCOUNT(filetypes); i++) {
		// Skip creating camera files on the game pak (they are controller pak only)
		if (filecounts[i] != 0 && !(device == SAVEDEVICE_GAMEPAK && i == 1)) {
			for (j = 0; j < filecounts[i]; j++) {
				s32 ret = pak0f118674(device, filetypes[i], NULL);

				if (ret != 0) {
					if (ret == 14) {
						return true;
					}

					pak0f119340(ret);
					return false;
				}
			}
		}
	}

	return true;
#else
	for (i = 0; i < ARRAYCOUNT(filetypes); i++) {
		// Skip creating camera files on the game pak (they are controller pak only)
		if (filecounts[i] != 0 && !(device == SAVEDEVICE_GAMEPAK && i == 1)) {
			for (j = 0; j < filecounts[i]; j++) {
				s32 ret = pak0f118674(device, filetypes[i], NULL);

				if (ret != 0) {
					pak0f119340(ret);
					return;
				}
			}
		}
	}
#endif
}

s32 pakFindMaxFileId(s8 device)
{
	struct pakfileheader header;
	u32 fileids[1025];
	s32 result;
	s32 max = 0;
	s32 i;

	result = pakGetFileIdsByType(device, PAKFILETYPE_ALL, fileids);

#if VERSION >= VERSION_NTSC_1_0
	if (result == 0) {
		for (i = 0; fileids[i] != 0; i++) {
			s32 offset = pakFindFile(device, fileids[i], &header);

			if (offset == -1) {
				return -1;
			}

			if (header.fileid > max) {
				max = header.fileid;
			}
		}
	} else {
		return -1;
	}
#else
	for (i = 0; fileids[i] != 0; i++) {
		s32 offset = pakFindFile(device, fileids[i], &header);

		if (header.fileid > max) {
			max = header.fileid;
		}
	}

	osSyncPrintf("Pak %d -> Pak_GetCurrentSaveId - SaveID = %u\n", device, max);
#endif

	return max;
}

void pakMergeBlanks(s8 device)
{
	struct pakfileheader header;
	u32 offset = 0;
	u32 nextoffset;
	s32 mergestartoffset = 0xffff;

	while (pakReadHeaderAtOffset(device, offset, &header) == PAK_ERR2_OK) {
		nextoffset = offset + header.filelen;

		if (offset);

		if (PAKFILETYPE_BLANK == header.filetype) {
			if (mergestartoffset != 0xffff) {
				u32 filelen = offset - mergestartoffset + header.filelen - sizeof(struct pakfileheader);

				if (pakWriteFileAtOffset(device, mergestartoffset, PAKFILETYPE_BLANK, NULL, filelen, NULL, NULL, 0, 1) != 0) {
					osSyncPrintf("> Pak_DefragPak_Level1 - Merge of two blanks failed");
				}

				nextoffset = 0;
				mergestartoffset = 0xffff;
			} else {
				mergestartoffset = offset;
			}
		} else {
			mergestartoffset = 0xffff;
		}

		offset = nextoffset;
	}
}

void pak0f11a2e4(void)
{
	// empty
}

s32 pakGetUnk014(s8 device)
{
	return g_Paks[device].unk014;
}

void pak0f11a32c(s8 device, u8 arg1, u32 line, char *file)
{
	if (g_Paks[device].unk014 == 0) {
		g_Paks[device].unk014 = arg1;

		if ((g_Paks[device].unk014 & 1) && g_Paks[device].headercache == NULL) {
			g_Paks[device].headercachecount = 0;
			g_Paks[device].headercache = mempAlloc(align32(sizeof(struct pakheadercache) * MAX_HEADERCACHE_ENTRIES), MEMPOOL_PERMANENT);

			// This would have been used in an osSyncPrintf call.
			// Perhaps using the strings at var7f1b4318 through var7f1b43ac?
			align32(sizeof(struct pakheadercache) * MAX_HEADERCACHE_ENTRIES);
		}
	}
}

void pak0f11a3dc(s8 device, u32 arg1, u32 arg2)
{
	if (g_Paks[device].unk014) {
		g_Paks[device].unk014 = 0;
	}

	if (g_Paks[device].unk014) {
		// empty
	}
}

const char var7f1b4294[] = "Pak %d - Pak_StartOne called from line %d in %s -> Flags = %0x\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b42d4[] = "\nPak_StartOne -> Pak%d, Modes -\n";
#else
const char var7f1b42d4[] = "\nPak_StartOne -> Pak%d, Modes -";
#endif

const char var7f1b42f8[] = "Memory,";
const char var7f1b4300[] = "Rumble,";
const char var7f1b4308[] = "Game Boy";
const char var7f1b4314[] = "\n";
const char var7f1b4318[] = "Pak %d -> %u Bytes of scratch for cache 2 memory at %0x\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b4354[] = "\nPak%d -> Pak_EndOne - Called from line %d in %s : Modes -\n";
#else
const char var7f1b4354[] = "\nPak%d -> Pak_EndOne - Called from line %d in %s : Modes -";
#endif

const char var7f1b4390[] = "Memory,";
const char var7f1b4398[] = "Rumble,";
const char var7f1b43a0[] = "Game Boy";
const char var7f1b43ac[] = "\n";
const char var7f1b43b0[] = "Pak -> FATAL ERROR -> MEMORY INSTANCE ENDING IS NO LONGER SUPPORTED\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b43f8[] = "Pak -> Pak_MakeOne - Id=%d is finished\n";
#else
const char var7f1b43f8[] = "Pak -> Pak_MakeOne - Id=%d is finished";
#endif

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pakInit
/*  f11a434:	00047600 */ 	sll	$t6,$a0,0x18
/*  f11a438:	000e7e03 */ 	sra	$t7,$t6,0x18
/*  f11a43c:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f11a440:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11a444:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11a448:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11a44c:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11a450:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f11a454:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11a458:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11a45c:	3c19800a */ 	lui	$t9,%hi(g_Paks)
/*  f11a460:	27392380 */ 	addiu	$t9,$t9,%lo(g_Paks)
/*  f11a464:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11a468:	03191021 */ 	addu	$v0,$t8,$t9
/*  f11a46c:	904902b8 */ 	lbu	$t1,0x2b8($v0)
/*  f11a470:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f11a474:	ac48029c */ 	sw	$t0,0x29c($v0)
/*  f11a478:	312bff7f */ 	andi	$t3,$t1,0xff7f
/*  f11a47c:	316d00f7 */ 	andi	$t5,$t3,0xf7
/*  f11a480:	a04b02b8 */ 	sb	$t3,0x2b8($v0)
/*  f11a484:	31af00df */ 	andi	$t7,$t5,0xdf
/*  f11a488:	a04d02b8 */ 	sb	$t5,0x2b8($v0)
/*  f11a48c:	31e800bf */ 	andi	$t0,$t7,0xbf
/*  f11a490:	a04f02b8 */ 	sb	$t7,0x2b8($v0)
/*  f11a494:	310a00fb */ 	andi	$t2,$t0,0xfb
/*  f11a498:	3c01bf80 */ 	lui	$at,0xbf80
/*  f11a49c:	44812000 */ 	mtc1	$at,$f4
/*  f11a4a0:	a04802b8 */ 	sb	$t0,0x2b8($v0)
/*  f11a4a4:	24030003 */ 	addiu	$v1,$zero,0x3
/*  f11a4a8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11a4ac:	24190080 */ 	addiu	$t9,$zero,0x80
/*  f11a4b0:	a04a02b8 */ 	sb	$t2,0x2b8($v0)
/*  f11a4b4:	314b00fd */ 	andi	$t3,$t2,0xfd
/*  f11a4b8:	240c0008 */ 	addiu	$t4,$zero,0x8
/*  f11a4bc:	afa40000 */ 	sw	$a0,0x0($sp)
/*  f11a4c0:	ac430274 */ 	sw	$v1,0x274($v0)
/*  f11a4c4:	a0400014 */ 	sb	$zero,0x14($v0)
/*  f11a4c8:	ac400000 */ 	sw	$zero,0x0($v0)
/*  f11a4cc:	ac450008 */ 	sw	$a1,0x8($v0)
/*  f11a4d0:	ac450004 */ 	sw	$a1,0x4($v0)
/*  f11a4d4:	ac43000c */ 	sw	$v1,0xc($v0)
/*  f11a4d8:	ac400010 */ 	sw	$zero,0x10($v0)
/*  f11a4dc:	a05902bd */ 	sb	$t9,0x2bd($v0)
/*  f11a4e0:	ac400264 */ 	sw	$zero,0x264($v0)
/*  f11a4e4:	a04b02b8 */ 	sb	$t3,0x2b8($v0)
/*  f11a4e8:	ac4002c0 */ 	sw	$zero,0x2c0($v0)
/*  f11a4ec:	ac4002c4 */ 	sw	$zero,0x2c4($v0)
/*  f11a4f0:	ac4c025c */ 	sw	$t4,0x25c($v0)
/*  f11a4f4:	ac400260 */ 	sw	$zero,0x260($v0)
/*  f11a4f8:	ac4002c8 */ 	sw	$zero,0x2c8($v0)
/*  f11a4fc:	03e00008 */ 	jr	$ra
/*  f11a500:	e44402b4 */ 	swc1	$f4,0x2b4($v0)
);
#else
GLOBAL_ASM(
glabel pakInit
/*  f1142ec:	00047600 */ 	sll	$t6,$a0,0x18
/*  f1142f0:	000e7e03 */ 	sra	$t7,$t6,0x18
/*  f1142f4:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f1142f8:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f1142fc:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f114300:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f114304:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f114308:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f11430c:	3c19800a */ 	lui	$t9,0x800a
/*  f114310:	27396870 */ 	addiu	$t9,$t9,0x6870
/*  f114314:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f114318:	03191021 */ 	addu	$v0,$t8,$t9
/*  f11431c:	904902b8 */ 	lbu	$t1,0x2b8($v0)
/*  f114320:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f114324:	ac48029c */ 	sw	$t0,0x29c($v0)
/*  f114328:	312bff7f */ 	andi	$t3,$t1,0xff7f
/*  f11432c:	316d00f7 */ 	andi	$t5,$t3,0xf7
/*  f114330:	a04b02b8 */ 	sb	$t3,0x2b8($v0)
/*  f114334:	31af00df */ 	andi	$t7,$t5,0xdf
/*  f114338:	a04d02b8 */ 	sb	$t5,0x2b8($v0)
/*  f11433c:	31e800bf */ 	andi	$t0,$t7,0xbf
/*  f114340:	3c01bf80 */ 	lui	$at,0xbf80
/*  f114344:	44812000 */ 	mtc1	$at,$f4
/*  f114348:	a04f02b8 */ 	sb	$t7,0x2b8($v0)
/*  f11434c:	24030003 */ 	addiu	$v1,$zero,0x3
/*  f114350:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f114354:	a04802b8 */ 	sb	$t0,0x2b8($v0)
/*  f114358:	24190080 */ 	addiu	$t9,$zero,0x80
/*  f11435c:	310900fb */ 	andi	$t1,$t0,0xfb
/*  f114360:	240a0008 */ 	addiu	$t2,$zero,0x8
/*  f114364:	afa40000 */ 	sw	$a0,0x0($sp)
/*  f114368:	ac430274 */ 	sw	$v1,0x274($v0)
/*  f11436c:	a0400014 */ 	sb	$zero,0x14($v0)
/*  f114370:	ac400000 */ 	sw	$zero,0x0($v0)
/*  f114374:	ac450008 */ 	sw	$a1,0x8($v0)
/*  f114378:	ac450004 */ 	sw	$a1,0x4($v0)
/*  f11437c:	ac43000c */ 	sw	$v1,0xc($v0)
/*  f114380:	ac400010 */ 	sw	$zero,0x10($v0)
/*  f114384:	a05902bd */ 	sb	$t9,0x2bd($v0)
/*  f114388:	ac400264 */ 	sw	$zero,0x264($v0)
/*  f11438c:	a04902b8 */ 	sb	$t1,0x2b8($v0)
/*  f114390:	ac4002c0 */ 	sw	$zero,0x2c0($v0)
/*  f114394:	ac4002c4 */ 	sw	$zero,0x2c4($v0)
/*  f114398:	ac4a025c */ 	sw	$t2,0x25c($v0)
/*  f11439c:	ac400260 */ 	sw	$zero,0x260($v0)
/*  f1143a0:	03e00008 */ 	jr	$ra
/*  f1143a4:	e44402b4 */ 	swc1	$f4,0x2b4($v0)
);
#endif

// Mismatch due to regalloc
//void pakInit(s8 device)
//{
//	g_Paks[device].unk274 = 3;
//	g_Paks[device].unk014 = 0;
//	g_Paks[device].type = PAKTYPE_NONE;
//	g_Paks[device].unk008 = 1;
//	g_Paks[device].rumblestate = RUMBLESTATE_1;
//	g_Paks[device].unk00c = 3;
//	g_Paks[device].unk010 = PAK010_00;
//	g_Paks[device].pdnoteindex = -1;
//	g_Paks[device].unk2bd = 128;
//	g_Paks[device].unk264 = 0;
//	g_Paks[device].unk2b8_01 = 0;
//	g_Paks[device].unk2b8_05 = 0;
//	g_Paks[device].unk2b8_03 = 0;
//	g_Paks[device].unk2b8_02 = 0;
//	g_Paks[device].unk2b8_06 = 0;
//	g_Paks[device].unk2b8_07 = 0;
//	g_Paks[device].headercache = NULL;
//	g_Paks[device].unk2c4 = NULL;
//	g_Paks[device].maxfileid = 8;
//	g_Paks[device].serial = 0;
//	g_Paks[device].unk2c8 = 0;
//	g_Paks[device].rumblettl = -1;
//}

PakErr1 pakReadWriteBlock(s8 device, OSPfs *pfs, s32 file_no, u8 flag, u32 address, u32 len, u8 *buffer)
{
	s32 result;
	len = pakAlign(device, len);

	joyDisableCyclicPolling(JOYARGS(3096));
	result = _pakReadWriteBlock(pfs, file_no, flag, address, len, buffer);
	joyEnableCyclicPolling(JOYARGS(3098));

	return result;
}

bool pakQueryTotalUsage(s8 device)
{
	struct pak *pak = &g_Paks[device];
	s32 noteerrors[16];
	s32 bytesfree;
	s32 ret;
	s32 i;

#if VERSION >= VERSION_NTSC_1_0
	osSyncPrintf("Pak %d -> Pak_Memory_UpdateNoteInfo\n", device);
#else
	osSyncPrintf("Pak %d -> Pak_Memory_UpdateNoteInfo", device);
#endif

	if (!pak->unk2b8_02) {
		return true;
	}

	ret = pakQueryNumNotes(PFS(device), &pak->notestotal, &pak->notesused);

	if (!pakHandleResult(ret, device, true, LINE_3486)) {
		pak->unk2b8_02 = false;
		return false;
	}

	ret = pakQueryNumFreeBytes(PFS(device), &bytesfree);
	pak->pakdata.pagesfree = ((bytesfree + 255) & 0xffff) >> 8;

	if (!pakHandleResult(ret, device, true, LINE_3495)) {
		pak->unk2b8_02 = false;
		return false;
	}

	for (i = 0; i < 16; i++) {
		noteerrors[i] = pakQueryNoteState(PFS(device), i, &pak->pakdata.notes[i]);

		if (noteerrors[i] != PAK_ERR1_OK) {
			pak->pakdata.notesinuse[i] = false;
		} else {
			pak->pakdata.notesinuse[i] = true;
		}
	}

	for (i = 0, pak->pakdata.pagesused = 0; i < 16; i++) {
		if (noteerrors[i] == PAK_ERR1_OK) {
			pak->pakdata.pagesused += (pak->pakdata.notes[i].file_size + 255) >> 8;
		}
	}

	pak->unk2b8_02 = false;

	return true;
}

void pakQueryPdSize(s8 device)
{
	u32 stack;
	OSPfsState note;
	s32 result;

	joyDisableCyclicPolling(JOYARGS(3242));
	result = pakQueryNoteState(PFS(device), g_Paks[device].pdnoteindex, &note);
	joyEnableCyclicPolling(JOYARGS(3244));

	if (pakHandleResult(result, device, true, LINE_3599)) {
		g_Paks[device].pdnumbytes = note.file_size;
		g_Paks[device].pdnumblocks = g_Paks[device].pdnumbytes / pakGetBlockSize(device);
		g_Paks[device].pdnumpages = g_Paks[device].pdnumbytes / 256;
		g_Paks[device].pdnumnotes = g_Paks[device].pdnumbytes / (256 * NUM_PAGES);
	}

	// These strings belong in this function, but the function needs to be
	// reworked to put them in their correct places
#if VERSION >= VERSION_NTSC_1_0
	osSyncPrintf("Pak %d -> Couldn't assertain the game note size\n");
	osSyncPrintf("Pak %d -> Pak_AnalyseCurrentGameNote - Game note size = %uk\n");
#else
	osSyncPrintf("Pak %d -> Couldn't assertain the game note size");
	osSyncPrintf("Pak %d -> Pak_AnalyseCurrentGameNote - Game note size = %uk");
#endif
}

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f1147b8nb
/*  f1147b8:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f1147bc:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f1147c0:	00048600 */ 	sll	$s0,$a0,0x18
/*  f1147c4:	00107603 */ 	sra	$t6,$s0,0x18
/*  f1147c8:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f1147cc:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f1147d0:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1147d4:	01c08025 */ 	or	$s0,$t6,$zero
/*  f1147d8:	24a5e39c */ 	addiu	$a1,$a1,-7268
/*  f1147dc:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f1147e0:	24040cc8 */ 	addiu	$a0,$zero,0xcc8
/*  f1147e4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f1147e8:	16010003 */ 	bne	$s0,$at,.NB0f1147f8
/*  f1147ec:	3c04800a */ 	lui	$a0,0x800a
/*  f1147f0:	10000009 */ 	beqz	$zero,.NB0f114818
/*  f1147f4:	00002825 */ 	or	$a1,$zero,$zero
.NB0f1147f8:
/*  f1147f8:	00107880 */ 	sll	$t7,$s0,0x2
/*  f1147fc:	01f07823 */ 	subu	$t7,$t7,$s0
/*  f114800:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f114804:	01f07821 */ 	addu	$t7,$t7,$s0
/*  f114808:	3c18800a */ 	lui	$t8,0x800a
/*  f11480c:	27187658 */ 	addiu	$t8,$t8,0x7658
/*  f114810:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f114814:	01f82821 */ 	addu	$a1,$t7,$t8
.NB0f114818:
/*  f114818:	2484e5d8 */ 	addiu	$a0,$a0,-6696
/*  f11481c:	0fc4478e */ 	jal	pakInitPak
/*  f114820:	02003025 */ 	or	$a2,$s0,$zero
/*  f114824:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114828:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f11482c:	24a5e3a4 */ 	addiu	$a1,$a1,-7260
/*  f114830:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f114834:	24040cca */ 	addiu	$a0,$zero,0xcca
/*  f114838:	00102e00 */ 	sll	$a1,$s0,0x18
/*  f11483c:	0005ce03 */ 	sra	$t9,$a1,0x18
/*  f114840:	03202825 */ 	or	$a1,$t9,$zero
/*  f114844:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f114848:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f11484c:	0fc458cb */ 	jal	pakHandleResult
/*  f114850:	24070ccc */ 	addiu	$a3,$zero,0xccc
/*  f114854:	14400003 */ 	bnez	$v0,.NB0f114864
/*  f114858:	24080003 */ 	addiu	$t0,$zero,0x3
/*  f11485c:	10000015 */ 	beqz	$zero,.NB0f1148b4
/*  f114860:	00001025 */ 	or	$v0,$zero,$zero
.NB0f114864:
/*  f114864:	00104880 */ 	sll	$t1,$s0,0x2
/*  f114868:	01304823 */ 	subu	$t1,$t1,$s0
/*  f11486c:	00094880 */ 	sll	$t1,$t1,0x2
/*  f114870:	01304823 */ 	subu	$t1,$t1,$s0
/*  f114874:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f114878:	01304821 */ 	addu	$t1,$t1,$s0
/*  f11487c:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f114880:	3c01800a */ 	lui	$at,0x800a
/*  f114884:	00290821 */ 	addu	$at,$at,$t1
/*  f114888:	ac286880 */ 	sw	$t0,0x6880($at)
/*  f11488c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f114890:	56010008 */ 	bnel	$s0,$at,.NB0f1148b4
/*  f114894:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f114898:	0fc45920 */ 	jal	pakExecuteDebugOperations
/*  f11489c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1148a0:	0fc45920 */ 	jal	pakExecuteDebugOperations
/*  f1148a4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1148a8:	0fc45920 */ 	jal	pakExecuteDebugOperations
/*  f1148ac:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1148b0:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f1148b4:
/*  f1148b4:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f1148b8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1148bc:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f1148c0:	03e00008 */ 	jr	$ra
/*  f1148c4:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

#if VERSION >= VERSION_NTSC_FINAL
GLOBAL_ASM(
glabel mempakPrepare
/*  f11a8f4:	27bdefa0 */ 	addiu	$sp,$sp,-4192
/*  f11a8f8:	afb10028 */ 	sw	$s1,0x28($sp)
/*  f11a8fc:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f11a900:	00117603 */ 	sra	$t6,$s1,0x18
/*  f11a904:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f11a908:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11a90c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a910:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11a914:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a918:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f11a91c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a920:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11a924:	3c18800a */ 	lui	$t8,%hi(g_Paks)
/*  f11a928:	afb00024 */ 	sw	$s0,0x24($sp)
/*  f11a92c:	27182380 */ 	addiu	$t8,$t8,%lo(g_Paks)
/*  f11a930:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a934:	01f88021 */ 	addu	$s0,$t7,$t8
/*  f11a938:	920902b8 */ 	lbu	$t1,0x2b8($s0)
/*  f11a93c:	afa41060 */ 	sw	$a0,0x1060($sp)
/*  f11a940:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f11a944:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f11a948:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f11a94c:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11a950:	352a0040 */ 	ori	$t2,$t1,0x40
/*  f11a954:	01c08825 */ 	or	$s1,$t6,$zero
/*  f11a958:	afa01054 */ 	sw	$zero,0x1054($sp)
/*  f11a95c:	afa01050 */ 	sw	$zero,0x1050($sp)
/*  f11a960:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f11a964:	a20a02b8 */ 	sb	$t2,0x2b8($s0)
/*  f11a968:	0fc4695d */ 	jal	pakQueryTotalUsage
/*  f11a96c:	01602025 */ 	or	$a0,$t3,$zero
/*  f11a970:	8e0c0010 */ 	lw	$t4,0x10($s0)
/*  f11a974:	24010001 */ 	addiu	$at,$zero,0x1
/*  f11a978:	15810003 */ 	bne	$t4,$at,.L0f11a988
/*  f11a97c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11a980:	100000b9 */ 	beqz	$zero,.L0f11ac68
/*  f11a984:	00001025 */ 	or	$v0,$zero,$zero
.L0f11a988:
/*  f11a988:	0c00543a */ 	jal	joyDisableCyclicPolling
/*  f11a98c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11a990:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11a994:	16210003 */ 	bne	$s1,$at,.L0f11a9a4
/*  f11a998:	24053459 */ 	addiu	$a1,$zero,0x3459
/*  f11a99c:	10000009 */ 	beqz	$zero,.L0f11a9c4
/*  f11a9a0:	00002025 */ 	or	$a0,$zero,$zero
.L0f11a9a4:
/*  f11a9a4:	00116880 */ 	sll	$t5,$s1,0x2
/*  f11a9a8:	01b16823 */ 	subu	$t5,$t5,$s1
/*  f11a9ac:	000d6880 */ 	sll	$t5,$t5,0x2
/*  f11a9b0:	01b16821 */ 	addu	$t5,$t5,$s1
/*  f11a9b4:	3c0e800a */ 	lui	$t6,%hi(g_Pfses)
/*  f11a9b8:	25ce3180 */ 	addiu	$t6,$t6,%lo(g_Pfses)
/*  f11a9bc:	000d68c0 */ 	sll	$t5,$t5,0x3
/*  f11a9c0:	01ae2021 */ 	addu	$a0,$t5,$t6
.L0f11a9c4:
/*  f11a9c4:	3c0f8007 */ 	lui	$t7,%hi(g_PakNoteExtName)
/*  f11a9c8:	25ef5d08 */ 	addiu	$t7,$t7,%lo(g_PakNoteExtName)
/*  f11a9cc:	3c064e50 */ 	lui	$a2,0x4e50
/*  f11a9d0:	3c078007 */ 	lui	$a3,%hi(g_PakNoteGameName)
/*  f11a9d4:	2602029c */ 	addiu	$v0,$s0,0x29c
/*  f11a9d8:	afa20014 */ 	sw	$v0,0x14($sp)
/*  f11a9dc:	afa20030 */ 	sw	$v0,0x30($sp)
/*  f11a9e0:	24e75cf8 */ 	addiu	$a3,$a3,%lo(g_PakNoteGameName)
/*  f11a9e4:	34c64445 */ 	ori	$a2,$a2,_gamecode
/*  f11a9e8:	0fc45f96 */ 	jal	pakFindNote
/*  f11a9ec:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f11a9f0:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11a9f4:	afa20048 */ 	sw	$v0,0x48($sp)
/*  f11a9f8:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f11a9fc:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f11aa00:	0005c603 */ 	sra	$t8,$a1,0x18
/*  f11aa04:	1080003e */ 	beqz	$a0,.L0f11ab00
/*  f11aa08:	03002825 */ 	or	$a1,$t8,$zero
/*  f11aa0c:	00003025 */ 	or	$a2,$zero,$zero
/*  f11aa10:	0fc470e7 */ 	jal	pakHandleResult
/*  f11aa14:	24070e46 */ 	addiu	$a3,$zero,_val7f11aa14
/*  f11aa18:	9619025a */ 	lhu	$t9,0x25a($s0)
/*  f11aa1c:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f11aa20:	24080002 */ 	addiu	$t0,$zero,0x2
/*  f11aa24:	2b210081 */ 	slti	$at,$t9,0x81
/*  f11aa28:	54200004 */ 	bnezl	$at,.L0f11aa3c
/*  f11aa2c:	a20902bc */ 	sb	$t1,0x2bc($s0)
/*  f11aa30:	10000002 */ 	beqz	$zero,.L0f11aa3c
/*  f11aa34:	a20802bc */ 	sb	$t0,0x2bc($s0)
/*  f11aa38:	a20902bc */ 	sb	$t1,0x2bc($s0)
.L0f11aa3c:
/*  f11aa3c:	920a02bc */ 	lbu	$t2,0x2bc($s0)
/*  f11aa40:	000a58c0 */ 	sll	$t3,$t2,0x3
/*  f11aa44:	016a5823 */ 	subu	$t3,$t3,$t2
/*  f11aa48:	000b5a80 */ 	sll	$t3,$t3,0xa
/*  f11aa4c:	0c00543a */ 	jal	joyDisableCyclicPolling
/*  f11aa50:	afab0044 */ 	sw	$t3,0x44($sp)
/*  f11aa54:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11aa58:	16210003 */ 	bne	$s1,$at,.L0f11aa68
/*  f11aa5c:	24053459 */ 	addiu	$a1,$zero,0x3459
/*  f11aa60:	10000009 */ 	beqz	$zero,.L0f11aa88
/*  f11aa64:	00002025 */ 	or	$a0,$zero,$zero
.L0f11aa68:
/*  f11aa68:	00116080 */ 	sll	$t4,$s1,0x2
/*  f11aa6c:	01916023 */ 	subu	$t4,$t4,$s1
/*  f11aa70:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f11aa74:	01916021 */ 	addu	$t4,$t4,$s1
/*  f11aa78:	3c0d800a */ 	lui	$t5,%hi(g_Pfses)
/*  f11aa7c:	25ad3180 */ 	addiu	$t5,$t5,%lo(g_Pfses)
/*  f11aa80:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f11aa84:	018d2021 */ 	addu	$a0,$t4,$t5
.L0f11aa88:
/*  f11aa88:	8faf0044 */ 	lw	$t7,0x44($sp)
/*  f11aa8c:	8fb80030 */ 	lw	$t8,0x30($sp)
/*  f11aa90:	3c0e8007 */ 	lui	$t6,%hi(g_PakNoteExtName)
/*  f11aa94:	25ce5d08 */ 	addiu	$t6,$t6,%lo(g_PakNoteExtName)
/*  f11aa98:	3c064e50 */ 	lui	$a2,0x4e50
/*  f11aa9c:	3c078007 */ 	lui	$a3,%hi(g_PakNoteGameName)
/*  f11aaa0:	24e75cf8 */ 	addiu	$a3,$a3,%lo(g_PakNoteGameName)
/*  f11aaa4:	34c64445 */ 	ori	$a2,$a2,_gamecode
/*  f11aaa8:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f11aaac:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f11aab0:	0fc45f64 */ 	jal	pakAllocateNote
/*  f11aab4:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f11aab8:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11aabc:	afa20048 */ 	sw	$v0,0x48($sp)
/*  f11aac0:	920802b8 */ 	lbu	$t0,0x2b8($s0)
/*  f11aac4:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f11aac8:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f11aacc:	00055603 */ 	sra	$t2,$a1,0x18
/*  f11aad0:	35090040 */ 	ori	$t1,$t0,0x40
/*  f11aad4:	a20902b8 */ 	sb	$t1,0x2b8($s0)
/*  f11aad8:	01402825 */ 	or	$a1,$t2,$zero
/*  f11aadc:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f11aae0:	0fc470e7 */ 	jal	pakHandleResult
/*  f11aae4:	24070e54 */ 	addiu	$a3,$zero,_val7f11aae4
/*  f11aae8:	10400003 */ 	beqz	$v0,.L0f11aaf8
/*  f11aaec:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f11aaf0:	10000003 */ 	beqz	$zero,.L0f11ab00
/*  f11aaf4:	afab1054 */ 	sw	$t3,0x1054($sp)
.L0f11aaf8:
/*  f11aaf8:	1000005b */ 	beqz	$zero,.L0f11ac68
/*  f11aafc:	00001025 */ 	or	$v0,$zero,$zero
.L0f11ab00:
/*  f11ab00:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11ab04:	00046603 */ 	sra	$t4,$a0,0x18
/*  f11ab08:	0fc4695d */ 	jal	pakQueryTotalUsage
/*  f11ab0c:	01802025 */ 	or	$a0,$t4,$zero
/*  f11ab10:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11ab14:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11ab18:	0fc469f7 */ 	jal	pakQueryPdSize
/*  f11ab1c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f11ab20:	920e02b8 */ 	lbu	$t6,0x2b8($s0)
/*  f11ab24:	2418000b */ 	addiu	$t8,$zero,0xb
/*  f11ab28:	a20002be */ 	sb	$zero,0x2be($s0)
/*  f11ab2c:	31cffffd */ 	andi	$t7,$t6,0xfffd
/*  f11ab30:	a20f02b8 */ 	sb	$t7,0x2b8($s0)
/*  f11ab34:	ae180010 */ 	sw	$t8,0x10($s0)
/*  f11ab38:	8fb91054 */ 	lw	$t9,0x1054($sp)
/*  f11ab3c:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11ab40:	00044603 */ 	sra	$t0,$a0,0x18
/*  f11ab44:	5320000a */ 	beqzl	$t9,.L0f11ab70
/*  f11ab48:	8faa1050 */ 	lw	$t2,0x1050($sp)
/*  f11ab4c:	0fc46d52 */ 	jal	pakCreateFilesystem
/*  f11ab50:	01002025 */ 	or	$a0,$t0,$zero
/*  f11ab54:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11ab58:	10410003 */ 	beq	$v0,$at,.L0f11ab68
/*  f11ab5c:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f11ab60:	10000002 */ 	beqz	$zero,.L0f11ab6c
/*  f11ab64:	ae020260 */ 	sw	$v0,0x260($s0)
.L0f11ab68:
/*  f11ab68:	afa91050 */ 	sw	$t1,0x1050($sp)
.L0f11ab6c:
/*  f11ab6c:	8faa1050 */ 	lw	$t2,0x1050($sp)
.L0f11ab70:
/*  f11ab70:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11ab74:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11ab78:	55400016 */ 	bnezl	$t2,.L0f11abd4
/*  f11ab7c:	8fb91050 */ 	lw	$t9,0x1050($sp)
/*  f11ab80:	0fc465c3 */ 	jal	pakRepairFilesystem
/*  f11ab84:	01602025 */ 	or	$a0,$t3,$zero
/*  f11ab88:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11ab8c:	14410010 */ 	bne	$v0,$at,.L0f11abd0
/*  f11ab90:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11ab94:	00046603 */ 	sra	$t4,$a0,0x18
/*  f11ab98:	0fc46d52 */ 	jal	pakCreateFilesystem
/*  f11ab9c:	01802025 */ 	or	$a0,$t4,$zero
/*  f11aba0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11aba4:	10410003 */ 	beq	$v0,$at,.L0f11abb4
/*  f11aba8:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f11abac:	10000002 */ 	beqz	$zero,.L0f11abb8
/*  f11abb0:	ae020260 */ 	sw	$v0,0x260($s0)
.L0f11abb4:
/*  f11abb4:	afad1050 */ 	sw	$t5,0x1050($sp)
.L0f11abb8:
/*  f11abb8:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11abbc:	52210005 */ 	beql	$s1,$at,.L0f11abd4
/*  f11abc0:	8fb91050 */ 	lw	$t9,0x1050($sp)
/*  f11abc4:	920f02b8 */ 	lbu	$t7,0x2b8($s0)
/*  f11abc8:	35f80002 */ 	ori	$t8,$t7,0x2
/*  f11abcc:	a21802b8 */ 	sb	$t8,0x2b8($s0)
.L0f11abd0:
/*  f11abd0:	8fb91050 */ 	lw	$t9,0x1050($sp)
.L0f11abd4:
/*  f11abd4:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11abd8:	00044603 */ 	sra	$t0,$a0,0x18
/*  f11abdc:	5720001e */ 	bnezl	$t9,.L0f11ac58
/*  f11abe0:	240d0016 */ 	addiu	$t5,$zero,0x16
/*  f11abe4:	0fc4683a */ 	jal	pakFindMaxFileId
/*  f11abe8:	01002025 */ 	or	$a0,$t0,$zero
/*  f11abec:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11abf0:	10410018 */ 	beq	$v0,$at,.L0f11ac54
/*  f11abf4:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11abf8:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11abfc:	ae02025c */ 	sw	$v0,0x25c($s0)
/*  f11ac00:	01202025 */ 	or	$a0,$t1,$zero
/*  f11ac04:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f11ac08:	0fc459ec */ 	jal	pakGetFileIdsByType
/*  f11ac0c:	27a60050 */ 	addiu	$a2,$sp,0x50
/*  f11ac10:	14400010 */ 	bnez	$v0,.L0f11ac54
/*  f11ac14:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11ac18:	00045603 */ 	sra	$t2,$a0,0x18
/*  f11ac1c:	0fc467a3 */ 	jal	pakCreateInitialFiles
/*  f11ac20:	01402025 */ 	or	$a0,$t2,$zero
/*  f11ac24:	1040000b */ 	beqz	$v0,.L0f11ac54
/*  f11ac28:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11ac2c:	16210004 */ 	bne	$s1,$at,.L0f11ac40
/*  f11ac30:	240c0006 */ 	addiu	$t4,$zero,0x6
/*  f11ac34:	240b000b */ 	addiu	$t3,$zero,0xb
/*  f11ac38:	10000002 */ 	beqz	$zero,.L0f11ac44
/*  f11ac3c:	ae0b0010 */ 	sw	$t3,0x10($s0)
.L0f11ac40:
/*  f11ac40:	ae0c0010 */ 	sw	$t4,0x10($s0)
.L0f11ac44:
/*  f11ac44:	0fc44364 */ 	jal	func0f110d90
/*  f11ac48:	02202025 */ 	or	$a0,$s1,$zero
/*  f11ac4c:	10000006 */ 	beqz	$zero,.L0f11ac68
/*  f11ac50:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f11ac54:
/*  f11ac54:	240d0016 */ 	addiu	$t5,$zero,0x16
.L0f11ac58:
/*  f11ac58:	ae0d0010 */ 	sw	$t5,0x10($s0)
/*  f11ac5c:	0fc44364 */ 	jal	func0f110d90
/*  f11ac60:	02202025 */ 	or	$a0,$s1,$zero
/*  f11ac64:	00001025 */ 	or	$v0,$zero,$zero
.L0f11ac68:
/*  f11ac68:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f11ac6c:	8fb00024 */ 	lw	$s0,0x24($sp)
/*  f11ac70:	8fb10028 */ 	lw	$s1,0x28($sp)
/*  f11ac74:	03e00008 */ 	jr	$ra
/*  f11ac78:	27bd1060 */ 	addiu	$sp,$sp,0x1060
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel mempakPrepare
/*  f11a674:	27bdef98 */ 	addiu	$sp,$sp,-4200
/*  f11a678:	afb10028 */ 	sw	$s1,0x28($sp)
/*  f11a67c:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f11a680:	00117603 */ 	sra	$t6,$s1,0x18
/*  f11a684:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f11a688:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11a68c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a690:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11a694:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a698:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f11a69c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a6a0:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11a6a4:	3c18800a */ 	lui	$t8,%hi(g_Paks)
/*  f11a6a8:	afb00024 */ 	sw	$s0,0x24($sp)
/*  f11a6ac:	27182380 */ 	addiu	$t8,$t8,%lo(g_Paks)
/*  f11a6b0:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11a6b4:	01f88021 */ 	addu	$s0,$t7,$t8
/*  f11a6b8:	920902b8 */ 	lbu	$t1,0x2b8($s0)
/*  f11a6bc:	afa41068 */ 	sw	$a0,0x1068($sp)
/*  f11a6c0:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f11a6c4:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f11a6c8:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f11a6cc:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11a6d0:	352a0040 */ 	ori	$t2,$t1,0x40
/*  f11a6d4:	01c08825 */ 	or	$s1,$t6,$zero
/*  f11a6d8:	afa0105c */ 	sw	$zero,0x105c($sp)
/*  f11a6dc:	afa01058 */ 	sw	$zero,0x1058($sp)
/*  f11a6e0:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f11a6e4:	a20a02b8 */ 	sb	$t2,0x2b8($s0)
/*  f11a6e8:	0fc468bd */ 	jal	pakQueryTotalUsage
/*  f11a6ec:	01602025 */ 	or	$a0,$t3,$zero
/*  f11a6f0:	8e0c0010 */ 	lw	$t4,0x10($s0)
/*  f11a6f4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f11a6f8:	15810003 */ 	bne	$t4,$at,.L0f11a708_2
/*  f11a6fc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11a700:	100000b9 */ 	beqz	$zero,.L0f11a9e8_2
/*  f11a704:	00001025 */ 	or	$v0,$zero,$zero
.L0f11a708_2:
/*  f11a708:	0c00543a */ 	jal	joyDisableCyclicPolling
/*  f11a70c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11a710:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11a714:	16210003 */ 	bne	$s1,$at,.L0f11a724_2
/*  f11a718:	24053459 */ 	addiu	$a1,$zero,0x3459
/*  f11a71c:	10000009 */ 	beqz	$zero,.L0f11a744_2
/*  f11a720:	00002025 */ 	or	$a0,$zero,$zero
.L0f11a724_2:
/*  f11a724:	00116880 */ 	sll	$t5,$s1,0x2
/*  f11a728:	01b16823 */ 	subu	$t5,$t5,$s1
/*  f11a72c:	000d6880 */ 	sll	$t5,$t5,0x2
/*  f11a730:	01b16821 */ 	addu	$t5,$t5,$s1
/*  f11a734:	3c0e800a */ 	lui	$t6,%hi(g_Pfses)
/*  f11a738:	25ce3180 */ 	addiu	$t6,$t6,%lo(g_Pfses)
/*  f11a73c:	000d68c0 */ 	sll	$t5,$t5,0x3
/*  f11a740:	01ae2021 */ 	addu	$a0,$t5,$t6
.L0f11a744_2:
/*  f11a744:	3c0f8007 */ 	lui	$t7,%hi(g_PakNoteExtName)
/*  f11a748:	25ef5d08 */ 	addiu	$t7,$t7,%lo(g_PakNoteExtName)
/*  f11a74c:	3c064e50 */ 	lui	$a2,0x4e50
/*  f11a750:	3c078007 */ 	lui	$a3,%hi(g_PakNoteGameName)
/*  f11a754:	2602029c */ 	addiu	$v0,$s0,0x29c
/*  f11a758:	afa20014 */ 	sw	$v0,0x14($sp)
/*  f11a75c:	afa20034 */ 	sw	$v0,0x34($sp)
/*  f11a760:	24e75cf8 */ 	addiu	$a3,$a3,%lo(g_PakNoteGameName)
/*  f11a764:	34c64445 */ 	ori	$a2,$a2,_gamecode
/*  f11a768:	0fc45f76 */ 	jal	pakFindNote
/*  f11a76c:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f11a770:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11a774:	afa2004c */ 	sw	$v0,0x4c($sp)
/*  f11a778:	8fa4004c */ 	lw	$a0,0x4c($sp)
/*  f11a77c:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f11a780:	0005c603 */ 	sra	$t8,$a1,0x18
/*  f11a784:	1080003e */ 	beqz	$a0,.L0f11a880_2
/*  f11a788:	03002825 */ 	or	$a1,$t8,$zero
/*  f11a78c:	00003025 */ 	or	$a2,$zero,$zero
/*  f11a790:	0fc47047 */ 	jal	pakHandleResult
/*  f11a794:	24070d83 */ 	addiu	$a3,$zero,0xd83
/*  f11a798:	9619025a */ 	lhu	$t9,0x25a($s0)
/*  f11a79c:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f11a7a0:	24080002 */ 	addiu	$t0,$zero,0x2
/*  f11a7a4:	2b210081 */ 	slti	$at,$t9,0x81
/*  f11a7a8:	54200004 */ 	bnezl	$at,.L0f11a7bc_2
/*  f11a7ac:	a20902bc */ 	sb	$t1,0x2bc($s0)
/*  f11a7b0:	10000002 */ 	beqz	$zero,.L0f11a7bc_2
/*  f11a7b4:	a20802bc */ 	sb	$t0,0x2bc($s0)
/*  f11a7b8:	a20902bc */ 	sb	$t1,0x2bc($s0)
.L0f11a7bc_2:
/*  f11a7bc:	920a02bc */ 	lbu	$t2,0x2bc($s0)
/*  f11a7c0:	000a58c0 */ 	sll	$t3,$t2,0x3
/*  f11a7c4:	016a5823 */ 	subu	$t3,$t3,$t2
/*  f11a7c8:	000b5a80 */ 	sll	$t3,$t3,0xa
/*  f11a7cc:	0c00543a */ 	jal	joyDisableCyclicPolling
/*  f11a7d0:	afab0048 */ 	sw	$t3,0x48($sp)
/*  f11a7d4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11a7d8:	16210003 */ 	bne	$s1,$at,.L0f11a7e8_2
/*  f11a7dc:	24053459 */ 	addiu	$a1,$zero,0x3459
/*  f11a7e0:	10000009 */ 	beqz	$zero,.L0f11a808_2
/*  f11a7e4:	00002025 */ 	or	$a0,$zero,$zero
.L0f11a7e8_2:
/*  f11a7e8:	00116080 */ 	sll	$t4,$s1,0x2
/*  f11a7ec:	01916023 */ 	subu	$t4,$t4,$s1
/*  f11a7f0:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f11a7f4:	01916021 */ 	addu	$t4,$t4,$s1
/*  f11a7f8:	3c0d800a */ 	lui	$t5,%hi(g_Pfses)
/*  f11a7fc:	25ad3180 */ 	addiu	$t5,$t5,%lo(g_Pfses)
/*  f11a800:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f11a804:	018d2021 */ 	addu	$a0,$t4,$t5
.L0f11a808_2:
/*  f11a808:	8faf0048 */ 	lw	$t7,0x48($sp)
/*  f11a80c:	8fb80034 */ 	lw	$t8,0x34($sp)
/*  f11a810:	3c0e8007 */ 	lui	$t6,%hi(g_PakNoteExtName)
/*  f11a814:	25ce5d08 */ 	addiu	$t6,$t6,%lo(g_PakNoteExtName)
/*  f11a818:	3c064e50 */ 	lui	$a2,0x4e50
/*  f11a81c:	3c078007 */ 	lui	$a3,%hi(g_PakNoteGameName)
/*  f11a820:	24e75cf8 */ 	addiu	$a3,$a3,%lo(g_PakNoteGameName)
/*  f11a824:	34c64445 */ 	ori	$a2,$a2,_gamecode
/*  f11a828:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f11a82c:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f11a830:	0fc45f44 */ 	jal	pakAllocateNote
/*  f11a834:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f11a838:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11a83c:	afa2004c */ 	sw	$v0,0x4c($sp)
/*  f11a840:	920802b8 */ 	lbu	$t0,0x2b8($s0)
/*  f11a844:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f11a848:	8fa4004c */ 	lw	$a0,0x4c($sp)
/*  f11a84c:	00055603 */ 	sra	$t2,$a1,0x18
/*  f11a850:	35090040 */ 	ori	$t1,$t0,0x40
/*  f11a854:	a20902b8 */ 	sb	$t1,0x2b8($s0)
/*  f11a858:	01402825 */ 	or	$a1,$t2,$zero
/*  f11a85c:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f11a860:	0fc47047 */ 	jal	pakHandleResult
/*  f11a864:	24070d91 */ 	addiu	$a3,$zero,0xd91
/*  f11a868:	10400003 */ 	beqz	$v0,.L0f11a878_2
/*  f11a86c:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f11a870:	10000003 */ 	beqz	$zero,.L0f11a880_2
/*  f11a874:	afab105c */ 	sw	$t3,0x105c($sp)
.L0f11a878_2:
/*  f11a878:	1000005b */ 	beqz	$zero,.L0f11a9e8_2
/*  f11a87c:	00001025 */ 	or	$v0,$zero,$zero
.L0f11a880_2:
/*  f11a880:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a884:	00046603 */ 	sra	$t4,$a0,0x18
/*  f11a888:	0fc468bd */ 	jal	pakQueryTotalUsage
/*  f11a88c:	01802025 */ 	or	$a0,$t4,$zero
/*  f11a890:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a894:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f11a898:	0fc46957 */ 	jal	pakQueryPdSize
/*  f11a89c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f11a8a0:	920e02b8 */ 	lbu	$t6,0x2b8($s0)
/*  f11a8a4:	2418000b */ 	addiu	$t8,$zero,0xb
/*  f11a8a8:	a20002be */ 	sb	$zero,0x2be($s0)
/*  f11a8ac:	31cffffd */ 	andi	$t7,$t6,0xfffd
/*  f11a8b0:	a20f02b8 */ 	sb	$t7,0x2b8($s0)
/*  f11a8b4:	ae180010 */ 	sw	$t8,0x10($s0)
/*  f11a8b8:	8fb9105c */ 	lw	$t9,0x105c($sp)
/*  f11a8bc:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a8c0:	00044603 */ 	sra	$t0,$a0,0x18
/*  f11a8c4:	5320000a */ 	beqzl	$t9,.L0f11a8f0_2
/*  f11a8c8:	8faa1058 */ 	lw	$t2,0x1058($sp)
/*  f11a8cc:	0fc46cb2 */ 	jal	pakCreateFilesystem
/*  f11a8d0:	01002025 */ 	or	$a0,$t0,$zero
/*  f11a8d4:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11a8d8:	10410003 */ 	beq	$v0,$at,.L0f11a8e8_2
/*  f11a8dc:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f11a8e0:	10000002 */ 	beqz	$zero,.L0f11a8ec_2
/*  f11a8e4:	ae020260 */ 	sw	$v0,0x260($s0)
.L0f11a8e8_2:
/*  f11a8e8:	afa91058 */ 	sw	$t1,0x1058($sp)
.L0f11a8ec_2:
/*  f11a8ec:	8faa1058 */ 	lw	$t2,0x1058($sp)
.L0f11a8f0_2:
/*  f11a8f0:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a8f4:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11a8f8:	55400016 */ 	bnezl	$t2,.L0f11a954_2
/*  f11a8fc:	8fb91058 */ 	lw	$t9,0x1058($sp)
/*  f11a900:	0fc46579 */ 	jal	pakRepairFilesystem
/*  f11a904:	01602025 */ 	or	$a0,$t3,$zero
/*  f11a908:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11a90c:	14410010 */ 	bne	$v0,$at,.L0f11a950_2
/*  f11a910:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a914:	00046603 */ 	sra	$t4,$a0,0x18
/*  f11a918:	0fc46cb2 */ 	jal	pakCreateFilesystem
/*  f11a91c:	01802025 */ 	or	$a0,$t4,$zero
/*  f11a920:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11a924:	10410003 */ 	beq	$v0,$at,.L0f11a934_2
/*  f11a928:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f11a92c:	10000002 */ 	beqz	$zero,.L0f11a938_2
/*  f11a930:	ae020260 */ 	sw	$v0,0x260($s0)
.L0f11a934_2:
/*  f11a934:	afad1058 */ 	sw	$t5,0x1058($sp)
.L0f11a938_2:
/*  f11a938:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11a93c:	52210005 */ 	beql	$s1,$at,.L0f11a954_2
/*  f11a940:	8fb91058 */ 	lw	$t9,0x1058($sp)
/*  f11a944:	920f02b8 */ 	lbu	$t7,0x2b8($s0)
/*  f11a948:	35f80002 */ 	ori	$t8,$t7,0x2
/*  f11a94c:	a21802b8 */ 	sb	$t8,0x2b8($s0)
.L0f11a950_2:
/*  f11a950:	8fb91058 */ 	lw	$t9,0x1058($sp)
.L0f11a954_2:
/*  f11a954:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a958:	00044603 */ 	sra	$t0,$a0,0x18
/*  f11a95c:	5720001e */ 	bnezl	$t9,.L0f11a9d8_2
/*  f11a960:	240d0016 */ 	addiu	$t5,$zero,0x16
/*  f11a964:	0fc4679a */ 	jal	pakFindMaxFileId
/*  f11a968:	01002025 */ 	or	$a0,$t0,$zero
/*  f11a96c:	2401ffff */ 	addiu	$at,$zero,-1
/*  f11a970:	10410018 */ 	beq	$v0,$at,.L0f11a9d4_2
/*  f11a974:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a978:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11a97c:	ae02025c */ 	sw	$v0,0x25c($s0)
/*  f11a980:	01202025 */ 	or	$a0,$t1,$zero
/*  f11a984:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f11a988:	0fc459cc */ 	jal	pakGetFileIdsByType
/*  f11a98c:	27a60054 */ 	addiu	$a2,$sp,0x54
/*  f11a990:	14400010 */ 	bnez	$v0,.L0f11a9d4_2
/*  f11a994:	00112600 */ 	sll	$a0,$s1,0x18
/*  f11a998:	00045603 */ 	sra	$t2,$a0,0x18
/*  f11a99c:	0fc46703 */ 	jal	pakCreateInitialFiles
/*  f11a9a0:	01402025 */ 	or	$a0,$t2,$zero
/*  f11a9a4:	1040000b */ 	beqz	$v0,.L0f11a9d4_2
/*  f11a9a8:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11a9ac:	16210004 */ 	bne	$s1,$at,.L0f11a9c0_2
/*  f11a9b0:	240c0006 */ 	addiu	$t4,$zero,0x6
/*  f11a9b4:	240b000b */ 	addiu	$t3,$zero,0xb
/*  f11a9b8:	10000002 */ 	beqz	$zero,.L0f11a9c4_2
/*  f11a9bc:	ae0b0010 */ 	sw	$t3,0x10($s0)
.L0f11a9c0_2:
/*  f11a9c0:	ae0c0010 */ 	sw	$t4,0x10($s0)
.L0f11a9c4_2:
/*  f11a9c4:	0fc44344 */ 	jal	func0f110d90
/*  f11a9c8:	02202025 */ 	or	$a0,$s1,$zero
/*  f11a9cc:	10000006 */ 	beqz	$zero,.L0f11a9e8_2
/*  f11a9d0:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f11a9d4_2:
/*  f11a9d4:	240d0016 */ 	addiu	$t5,$zero,0x16
.L0f11a9d8_2:
/*  f11a9d8:	ae0d0010 */ 	sw	$t5,0x10($s0)
/*  f11a9dc:	0fc44344 */ 	jal	func0f110d90
/*  f11a9e0:	02202025 */ 	or	$a0,$s1,$zero
/*  f11a9e4:	00001025 */ 	or	$v0,$zero,$zero
.L0f11a9e8_2:
/*  f11a9e8:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f11a9ec:	8fb00024 */ 	lw	$s0,0x24($sp)
/*  f11a9f0:	8fb10028 */ 	lw	$s1,0x28($sp)
/*  f11a9f4:	03e00008 */ 	jr	$ra
/*  f11a9f8:	27bd1068 */ 	addiu	$sp,$sp,0x1068
);
#else
GLOBAL_ASM(
glabel mempakPrepare
/*  f1148c8:	27bdefb0 */ 	addiu	$sp,$sp,-4176
/*  f1148cc:	afb10028 */ 	sw	$s1,0x28($sp)
/*  f1148d0:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f1148d4:	00117603 */ 	sra	$t6,$s1,0x18
/*  f1148d8:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f1148dc:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f1148e0:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f1148e4:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f1148e8:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f1148ec:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f1148f0:	3c18800a */ 	lui	$t8,0x800a
/*  f1148f4:	afb00024 */ 	sw	$s0,0x24($sp)
/*  f1148f8:	27186870 */ 	addiu	$t8,$t8,0x6870
/*  f1148fc:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f114900:	01f88021 */ 	addu	$s0,$t7,$t8
/*  f114904:	920902b8 */ 	lbu	$t1,0x2b8($s0)
/*  f114908:	afa41050 */ 	sw	$a0,0x1050($sp)
/*  f11490c:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f114910:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f114914:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f114918:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11491c:	352a0040 */ 	ori	$t2,$t1,0x40
/*  f114920:	01c08825 */ 	or	$s1,$t6,$zero
/*  f114924:	afa01044 */ 	sw	$zero,0x1044($sp)
/*  f114928:	ae190000 */ 	sw	$t9,0x0($s0)
/*  f11492c:	a20a02b8 */ 	sb	$t2,0x2b8($s0)
/*  f114930:	0fc4510c */ 	jal	pakQueryTotalUsage
/*  f114934:	01602025 */ 	or	$a0,$t3,$zero
/*  f114938:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f11493c:	24a5e3d4 */ 	addiu	$a1,$a1,-7212
/*  f114940:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f114944:	24040cf7 */ 	addiu	$a0,$zero,0xcf7
/*  f114948:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11494c:	16210003 */ 	bne	$s1,$at,.NB0f11495c
/*  f114950:	24053031 */ 	addiu	$a1,$zero,0x3031
/*  f114954:	10000009 */ 	beqz	$zero,.NB0f11497c
/*  f114958:	00002025 */ 	or	$a0,$zero,$zero
.NB0f11495c:
/*  f11495c:	00116080 */ 	sll	$t4,$s1,0x2
/*  f114960:	01916023 */ 	subu	$t4,$t4,$s1
/*  f114964:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f114968:	01916021 */ 	addu	$t4,$t4,$s1
/*  f11496c:	3c0d800a */ 	lui	$t5,0x800a
/*  f114970:	25ad7658 */ 	addiu	$t5,$t5,0x7658
/*  f114974:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f114978:	018d2021 */ 	addu	$a0,$t4,$t5
.NB0f11497c:
/*  f11497c:	3c0e8008 */ 	lui	$t6,0x8008
/*  f114980:	25ce80c8 */ 	addiu	$t6,$t6,-32568
/*  f114984:	3c064e50 */ 	lui	$a2,0x4e50
/*  f114988:	3c078008 */ 	lui	$a3,0x8008
/*  f11498c:	2602029c */ 	addiu	$v0,$s0,0x29c
/*  f114990:	afa20014 */ 	sw	$v0,0x14($sp)
/*  f114994:	afa20030 */ 	sw	$v0,0x30($sp)
/*  f114998:	24e780b8 */ 	addiu	$a3,$a3,-32584
/*  f11499c:	34c64445 */ 	ori	$a2,$a2,0x4445
/*  f1149a0:	0fc4487f */ 	jal	pakFindNote
/*  f1149a4:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f1149a8:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1149ac:	afa20040 */ 	sw	$v0,0x40($sp)
/*  f1149b0:	24a5e3dc */ 	addiu	$a1,$a1,-7204
/*  f1149b4:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f1149b8:	24040cf9 */ 	addiu	$a0,$zero,0xcf9
/*  f1149bc:	8fa40040 */ 	lw	$a0,0x40($sp)
/*  f1149c0:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f1149c4:	00057e03 */ 	sra	$t7,$a1,0x18
/*  f1149c8:	10800043 */ 	beqz	$a0,.NB0f114ad8
/*  f1149cc:	01e02825 */ 	or	$a1,$t7,$zero
/*  f1149d0:	00003025 */ 	or	$a2,$zero,$zero
/*  f1149d4:	0fc458cb */ 	jal	pakHandleResult
/*  f1149d8:	24070d00 */ 	addiu	$a3,$zero,0xd00
/*  f1149dc:	9618025a */ 	lhu	$t8,0x25a($s0)
/*  f1149e0:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f1149e4:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f1149e8:	2b010081 */ 	slti	$at,$t8,0x81
/*  f1149ec:	14200003 */ 	bnez	$at,.NB0f1149fc
/*  f1149f0:	24040d08 */ 	addiu	$a0,$zero,0xd08
/*  f1149f4:	10000002 */ 	beqz	$zero,.NB0f114a00
/*  f1149f8:	a21902bc */ 	sb	$t9,0x2bc($s0)
.NB0f1149fc:
/*  f1149fc:	a20802bc */ 	sb	$t0,0x2bc($s0)
.NB0f114a00:
/*  f114a00:	920902bc */ 	lbu	$t1,0x2bc($s0)
/*  f114a04:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114a08:	24a5e3e4 */ 	addiu	$a1,$a1,-7196
/*  f114a0c:	000950c0 */ 	sll	$t2,$t1,0x3
/*  f114a10:	01495023 */ 	subu	$t2,$t2,$t1
/*  f114a14:	000a5280 */ 	sll	$t2,$t2,0xa
/*  f114a18:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f114a1c:	afaa003c */ 	sw	$t2,0x3c($sp)
/*  f114a20:	24010004 */ 	addiu	$at,$zero,0x4
/*  f114a24:	16210003 */ 	bne	$s1,$at,.NB0f114a34
/*  f114a28:	24053031 */ 	addiu	$a1,$zero,0x3031
/*  f114a2c:	10000009 */ 	beqz	$zero,.NB0f114a54
/*  f114a30:	00002025 */ 	or	$a0,$zero,$zero
.NB0f114a34:
/*  f114a34:	00115880 */ 	sll	$t3,$s1,0x2
/*  f114a38:	01715823 */ 	subu	$t3,$t3,$s1
/*  f114a3c:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f114a40:	01715821 */ 	addu	$t3,$t3,$s1
/*  f114a44:	3c0c800a */ 	lui	$t4,0x800a
/*  f114a48:	258c7658 */ 	addiu	$t4,$t4,0x7658
/*  f114a4c:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f114a50:	016c2021 */ 	addu	$a0,$t3,$t4
.NB0f114a54:
/*  f114a54:	8fae003c */ 	lw	$t6,0x3c($sp)
/*  f114a58:	8faf0030 */ 	lw	$t7,0x30($sp)
/*  f114a5c:	3c0d8008 */ 	lui	$t5,0x8008
/*  f114a60:	25ad80c8 */ 	addiu	$t5,$t5,-32568
/*  f114a64:	3c064e50 */ 	lui	$a2,0x4e50
/*  f114a68:	3c078008 */ 	lui	$a3,0x8008
/*  f114a6c:	24e780b8 */ 	addiu	$a3,$a3,-32584
/*  f114a70:	34c64445 */ 	ori	$a2,$a2,0x4445
/*  f114a74:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f114a78:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f114a7c:	0fc4484d */ 	jal	pakAllocateNote
/*  f114a80:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f114a84:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114a88:	afa20040 */ 	sw	$v0,0x40($sp)
/*  f114a8c:	24a5e3ec */ 	addiu	$a1,$a1,-7188
/*  f114a90:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f114a94:	24040d0a */ 	addiu	$a0,$zero,0xd0a
/*  f114a98:	921902b8 */ 	lbu	$t9,0x2b8($s0)
/*  f114a9c:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f114aa0:	00054e03 */ 	sra	$t1,$a1,0x18
/*  f114aa4:	37280040 */ 	ori	$t0,$t9,0x40
/*  f114aa8:	8fa40040 */ 	lw	$a0,0x40($sp)
/*  f114aac:	a20802b8 */ 	sb	$t0,0x2b8($s0)
/*  f114ab0:	01202825 */ 	or	$a1,$t1,$zero
/*  f114ab4:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f114ab8:	0fc458cb */ 	jal	pakHandleResult
/*  f114abc:	24070d0e */ 	addiu	$a3,$zero,0xd0e
/*  f114ac0:	10400003 */ 	beqz	$v0,.NB0f114ad0
/*  f114ac4:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f114ac8:	10000003 */ 	beqz	$zero,.NB0f114ad8
/*  f114acc:	afaa1044 */ 	sw	$t2,0x1044($sp)
.NB0f114ad0:
/*  f114ad0:	10000048 */ 	beqz	$zero,.NB0f114bf4
/*  f114ad4:	00001025 */ 	or	$v0,$zero,$zero
.NB0f114ad8:
/*  f114ad8:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114adc:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f114ae0:	0fc4510c */ 	jal	pakQueryTotalUsage
/*  f114ae4:	01602025 */ 	or	$a0,$t3,$zero
/*  f114ae8:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114aec:	00046603 */ 	sra	$t4,$a0,0x18
/*  f114af0:	0fc451a4 */ 	jal	pakQueryPdSize
/*  f114af4:	01802025 */ 	or	$a0,$t4,$zero
/*  f114af8:	240d000b */ 	addiu	$t5,$zero,0xb
/*  f114afc:	a20002be */ 	sb	$zero,0x2be($s0)
/*  f114b00:	ae0d0010 */ 	sw	$t5,0x10($s0)
/*  f114b04:	8fae1044 */ 	lw	$t6,0x1044($sp)
/*  f114b08:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114b0c:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f114b10:	15c00006 */ 	bnez	$t6,.NB0f114b2c
/*  f114b14:	00000000 */ 	sll	$zero,$zero,0x0
/*  f114b18:	0fc44e4b */ 	jal	pakRepairFilesystem
/*  f114b1c:	01e02025 */ 	or	$a0,$t7,$zero
/*  f114b20:	14400002 */ 	bnez	$v0,.NB0f114b2c
/*  f114b24:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f114b28:	afb81044 */ 	sw	$t8,0x1044($sp)
.NB0f114b2c:
/*  f114b2c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114b30:	24a5e3f4 */ 	addiu	$a1,$a1,-7180
/*  f114b34:	0c004e18 */ 	jal	argFindByPrefix
/*  f114b38:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f114b3c:	10400009 */ 	beqz	$v0,.NB0f114b64
/*  f114b40:	8fa81044 */ 	lw	$t0,0x1044($sp)
/*  f114b44:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114b48:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f114b4c:	03202025 */ 	or	$a0,$t9,$zero
/*  f114b50:	00002825 */ 	or	$a1,$zero,$zero
/*  f114b54:	0fc453e4 */ 	jal	pakWipe
/*  f114b58:	8e0602a4 */ 	lw	$a2,0x2a4($s0)
/*  f114b5c:	1000000d */ 	beqz	$zero,.NB0f114b94
/*  f114b60:	00112600 */ 	sll	$a0,$s1,0x18
.NB0f114b64:
/*  f114b64:	15000005 */ 	bnez	$t0,.NB0f114b7c
/*  f114b68:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f114b6c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114b70:	0c004e18 */ 	jal	argFindByPrefix
/*  f114b74:	24a5e400 */ 	addiu	$a1,$a1,-7168
/*  f114b78:	10400005 */ 	beqz	$v0,.NB0f114b90
.NB0f114b7c:
/*  f114b7c:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114b80:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f114b84:	0fc45544 */ 	jal	pakCreateFilesystem
/*  f114b88:	01202025 */ 	or	$a0,$t1,$zero
/*  f114b8c:	ae020260 */ 	sw	$v0,0x260($s0)
.NB0f114b90:
/*  f114b90:	00112600 */ 	sll	$a0,$s1,0x18
.NB0f114b94:
/*  f114b94:	00045603 */ 	sra	$t2,$a0,0x18
/*  f114b98:	0fc44ff9 */ 	jal	pakFindMaxFileId
/*  f114b9c:	01402025 */ 	or	$a0,$t2,$zero
/*  f114ba0:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114ba4:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f114ba8:	ae02025c */ 	sw	$v0,0x25c($s0)
/*  f114bac:	01602025 */ 	or	$a0,$t3,$zero
/*  f114bb0:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f114bb4:	0fc442dd */ 	jal	pakGetFileIdsByType
/*  f114bb8:	27a60044 */ 	addiu	$a2,$sp,0x44
/*  f114bbc:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114bc0:	00046603 */ 	sra	$t4,$a0,0x18
/*  f114bc4:	0fc44f6e */ 	jal	pakCreateInitialFiles
/*  f114bc8:	01802025 */ 	or	$a0,$t4,$zero
/*  f114bcc:	8fad0030 */ 	lw	$t5,0x30($sp)
/*  f114bd0:	3c0e800a */ 	lui	$t6,0x800a
/*  f114bd4:	25ce762c */ 	addiu	$t6,$t6,0x762c
/*  f114bd8:	15ae0004 */ 	bne	$t5,$t6,.NB0f114bec
/*  f114bdc:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f114be0:	240f000b */ 	addiu	$t7,$zero,0xb
/*  f114be4:	10000003 */ 	beqz	$zero,.NB0f114bf4
/*  f114be8:	ae0f0010 */ 	sw	$t7,0x10($s0)
.NB0f114bec:
/*  f114bec:	24180006 */ 	addiu	$t8,$zero,0x6
/*  f114bf0:	ae180010 */ 	sw	$t8,0x10($s0)
.NB0f114bf4:
/*  f114bf4:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f114bf8:	8fb00024 */ 	lw	$s0,0x24($sp)
/*  f114bfc:	8fb10028 */ 	lw	$s1,0x28($sp)
/*  f114c00:	03e00008 */ 	jr	$ra
/*  f114c04:	27bd1050 */ 	addiu	$sp,$sp,0x1050
);
#endif

/**
 * Prepare a controller pak for use by making sure a note is allocated and that
 * the filesystem is good, among other things.
 */
// Mismatch: Swapped instructions. Seems related to sp48. Splitting the two uses
// of sp48 into separate variables helps, but both variables are saved to sp48.
//bool mempakPrepare(s8 device)
//{
//	u32 stack[2];
//	bool isnewnote = false; // 1054
//	bool error = false; // 1050
//	u32 fileids[1024]; // 50
//	s32 serial;
//	s32 sp48; // 48
//	s32 notesize; // 44
//	s32 maxfileid;
//
//	g_Paks[device].type = PAKTYPE_MEMORY;
//	g_Paks[device].unk2b8_02 = true;
//
//	pakQueryTotalUsage(device);
//
//	if (g_Paks[device].unk010 == PAK010_01) {
//		return false;
//	}
//
//	// Find the PD note if it exists
//	joyDisableCyclicPolling();
//	sp48 = pakFindNote(PFS(device), ROM_COMPANYCODE, ROM_GAMECODE, g_PakNoteGameName, g_PakNoteExtName, &g_Paks[device].pdnoteindex);
//	joyEnableCyclicPolling();
//
//	// If it doesn't exist, allocate it
//	if (sp48 != PAK_ERR1_OK) {
//		pakHandleResult(sp48, device, false, 3654);
//
//		g_Paks[device].pdnumnotes = (g_Paks[device].pakdata.pagesfree > 128) ? 2 : 1;
//
//		notesize = g_Paks[device].pdnumnotes * (256 * NUM_PAGES);
//
//		joyDisableCyclicPolling();
//		sp48 = pakAllocateNote(PFS(device), ROM_COMPANYCODE, ROM_GAMECODE, g_PakNoteGameName, g_PakNoteExtName, notesize, &g_Paks[device].pdnoteindex);
//		joyEnableCyclicPolling();
//
//		g_Paks[device].unk2b8_02 = true;
//
//		if (pakHandleResult(sp48, device, true, 3668)) {
//			isnewnote = true;
//		} else {
//			return false;
//		}
//	}
//
//	pakQueryTotalUsage(device);
//	pakQueryPdSize(device);
//
//	g_Paks[device].unk2b8_07 = false;
//	g_Paks[device].headercachecount = 0;
//	g_Paks[device].unk010 = PAK010_11;
//
//	// If it's a new note, create the filesystem
//	if (isnewnote) {
//		serial = pakCreateFilesystem(device);
//
//		if (serial != -1) {
//			g_Paks[device].serial = serial;
//		} else {
//			error = true;
//		}
//	}
//
//	// Maybe check the filesystem for correctness and recreate it if needed?
//	if (!error) {
//		if (pakRepairFilesystem(device) == -1) {
//			serial = pakCreateFilesystem(device);
//
//			if (serial != -1) {
//				g_Paks[device].serial = serial;
//			} else {
//				error = true;
//			}
//
//			if (device != SAVEDEVICE_GAMEPAK) {
//				g_Paks[device].unk2b8_06 = true;
//			}
//		}
//	}
//
//	if (!error) {
//		maxfileid = pakFindMaxFileId(device);
//
//		if (maxfileid != -1) {
//			g_Paks[device].maxfileid = maxfileid;
//
//			if (pakGetFileIdsByType(device, PAKFILETYPE_TERMINATOR, fileids) == 0 && pakCreateInitialFiles(device)) {
//				if (device == SAVEDEVICE_GAMEPAK) {
//					g_Paks[device].unk010 = PAK010_11;
//				} else {
//					g_Paks[device].unk010 = PAK010_06;
//				}
//
//				func0f110d90(device);
//
//				return true;
//			}
//		}
//	}
//
//	g_Paks[device].unk010 = PAK010_22;
//
//	func0f110d90(device);
//
//	return false;
//}

#if VERSION < VERSION_NTSC_1_0
const char var7f1ae380nb[] = "Pak %d -> Pak_Memory_Init1";
const char var7f1ae39cnb[] = "pak.c";
const char var7f1ae3a4nb[] = "pak.c";
#endif

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b44bc[] = "Pak %d -> Searching for the game file\n";
#else
const char var7f1b44bc[] = "Pak %d -> Searching for the game file";
#endif

#if VERSION < VERSION_NTSC_1_0
const char var7f1ae3d4nb[] = "pak.c";
const char var7f1ae3dcnb[] = "pak.c";
const char var7f1ae3e4nb[] = "pak.c";
const char var7f1ae3ecnb[] = "pak.c";
const char var7f1ae3f4nb[] = "-forcewipe";
const char var7f1ae400nb[] = "-forcescrub";
const char var7f1ae40cnb[] = "Pak %d -> Initialisation - No swap file";
const char var7f1ae434nb[] = "Pak %d -> Initialisation - Found a swap file";
#endif

bool pakProbe(s8 device)
{
	bool plugged = false;
	s32 ret;
	bool done = false;

#if VERSION >= VERSION_NTSC_1_0
	joyDisableCyclicPolling();

	// Try memory pak
	ret = pakInitPak(&g_PiMesgQueue, PFS(device), device, NULL);

	if (pakHandleResult(ret, device, true, LINE_3829)) {
		g_Paks[device].unk010 = PAK010_03;

		if (device == SAVEDEVICE_GAMEPAK) {
			pakExecuteDebugOperations();
			pakExecuteDebugOperations();
			pakExecuteDebugOperations();
		}

		plugged = true;
		done = true;
	} else if (ret == PAK_ERR1_NOPAK) {
		done = true;
	}

	if (!done) {
		if (device == SAVEDEVICE_GAMEPAK) {
			plugged = false;
			done = true;
		}

		if (!done) {
			// Try rumble pak
			ret = osMotorProbe(&g_PiMesgQueue, PFS(device), device);

			if (pakHandleResult(ret, device, false, LINE_3865)) {
				g_Paks[device].type = PAKTYPE_RUMBLE;
				g_Paks[device].unk010 = PAK010_11;
				g_Paks[device].rumblestate = RUMBLESTATE_1;
				g_Paks[device].unk264++;

				plugged = true;
				done = true;
			} else if (ret == PAK_ERR1_NOPAK) {
				plugged = false;
				done = true;
			}

			if (!done) {
				// Try game boy pak
				ret = osGbpakInit(&g_PiMesgQueue, PFS(device), device);

				if (pakHandleResult(ret, device, false, LINE_3889)) {
					if (IS4MB()) {
						g_Paks[device].type = PAKTYPE_NONE;
						g_Paks[device].unk010 = PAK010_22;
					} else {
						g_Paks[device].type = PAKTYPE_GAMEBOY;
						g_Paks[device].unk010 = PAK010_08;
						g_Paks[device].unk2b8_01 = false;
						g_Paks[device].unk264++;
					}

					plugged = true;
				} else if (ret == PAK_ERR1_NOPAK) {
					plugged = false;
				}
			}
		}
	}

	joyEnableCyclicPolling();

	return plugged;
#else
	if (device == SAVEDEVICE_GAMEPAK) {
		return true;
	}

	joyDisableCyclicPolling(JOYARGS(3434));

	// Try memory pak
	ret = pakInitPak(&g_PiMesgQueue, PFS(device), device);

	if (pakHandleResult(ret, device, true, 3437)) {
		joyEnableCyclicPolling(JOYARGS(3439));
		return true;
	}

	// Try rumble pak
	ret = osMotorProbe(&g_PiMesgQueue, PFS(device), device);

	if (pakHandleResult(ret, device, false, 3446)) {
		joyEnableCyclicPolling(JOYARGS(3448));
		return true;
	}

	// Try game boy pak
	ret = osGbpakInit(&g_PiMesgQueue, PFS(device), device);

	if (pakHandleResult(ret, device, false, 3455)) {
		joyEnableCyclicPolling(JOYARGS(3457));
		return true;
	}

	joyEnableCyclicPolling(JOYARGS(3462));

	return false;
#endif
}

#if VERSION < VERSION_NTSC_1_0
const char var7f1ae48cnb[] = "pak.c";
const char var7f1ae494nb[] = "pak.c";
const char var7f1ae49cnb[] = "Pak %d -> About to wipe blocks %d to %d of the game file with the wipe byte %d";
#endif

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f114dd4nb
/*  f114dd4:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f114dd8:	afb10018 */ 	sw	$s1,0x18($sp)
/*  f114ddc:	00048e00 */ 	sll	$s1,$a0,0x18
/*  f114de0:	00117603 */ 	sra	$t6,$s1,0x18
/*  f114de4:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f114de8:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f114dec:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f114df0:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f114df4:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f114df8:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f114dfc:	3c18800a */ 	lui	$t8,0x800a
/*  f114e00:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f114e04:	27186870 */ 	addiu	$t8,$t8,0x6870
/*  f114e08:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f114e0c:	01f88021 */ 	addu	$s0,$t7,$t8
/*  f114e10:	920802b8 */ 	lbu	$t0,0x2b8($s0)
/*  f114e14:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f114e18:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f114e1c:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f114e20:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f114e24:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f114e28:	240a0003 */ 	addiu	$t2,$zero,0x3
/*  f114e2c:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f114e30:	3109ff7f */ 	andi	$t1,$t0,0xff7f
/*  f114e34:	01c08825 */ 	or	$s1,$t6,$zero
/*  f114e38:	ae19029c */ 	sw	$t9,0x29c($s0)
/*  f114e3c:	a20902b8 */ 	sb	$t1,0x2b8($s0)
/*  f114e40:	ae000000 */ 	sw	$zero,0x0($s0)
/*  f114e44:	ae020008 */ 	sw	$v0,0x8($s0)
/*  f114e48:	ae020004 */ 	sw	$v0,0x4($s0)
/*  f114e4c:	ae0a000c */ 	sw	$t2,0xc($s0)
/*  f114e50:	0fc45302 */ 	jal	pakProbe
/*  f114e54:	01602025 */ 	or	$a0,$t3,$zero
/*  f114e58:	50400049 */ 	beqzl	$v0,.NB0f114f80
/*  f114e5c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f114e60:	92020014 */ 	lbu	$v0,0x14($s0)
/*  f114e64:	00112600 */ 	sll	$a0,$s1,0x18
/*  f114e68:	00046e03 */ 	sra	$t5,$a0,0x18
/*  f114e6c:	304c0001 */ 	andi	$t4,$v0,0x1
/*  f114e70:	5180000b */ 	beqzl	$t4,.NB0f114ea0
/*  f114e74:	30580002 */ 	andi	$t8,$v0,0x2
/*  f114e78:	0fc451ee */ 	jal	pak0f1147b8nb
/*  f114e7c:	01a02025 */ 	or	$a0,$t5,$zero
/*  f114e80:	50400006 */ 	beqzl	$v0,.NB0f114e9c
/*  f114e84:	92020014 */ 	lbu	$v0,0x14($s0)
/*  f114e88:	8e0e0264 */ 	lw	$t6,0x264($s0)
/*  f114e8c:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*  f114e90:	1000003a */ 	beqz	$zero,.NB0f114f7c
/*  f114e94:	ae0f0264 */ 	sw	$t7,0x264($s0)
/*  f114e98:	92020014 */ 	lbu	$v0,0x14($s0)
.NB0f114e9c:
/*  f114e9c:	30580002 */ 	andi	$t8,$v0,0x2
.NB0f114ea0:
/*  f114ea0:	1300002c */ 	beqz	$t8,.NB0f114f54
/*  f114ea4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f114ea8:	12210034 */ 	beq	$s1,$at,.NB0f114f7c
/*  f114eac:	24040dba */ 	addiu	$a0,$zero,0xdba
/*  f114eb0:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114eb4:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f114eb8:	24a5e48c */ 	addiu	$a1,$a1,-7028
/*  f114ebc:	24010004 */ 	addiu	$at,$zero,0x4
/*  f114ec0:	16210003 */ 	bne	$s1,$at,.NB0f114ed0
/*  f114ec4:	3c04800a */ 	lui	$a0,0x800a
/*  f114ec8:	10000009 */ 	beqz	$zero,.NB0f114ef0
/*  f114ecc:	00002825 */ 	or	$a1,$zero,$zero
.NB0f114ed0:
/*  f114ed0:	0011c880 */ 	sll	$t9,$s1,0x2
/*  f114ed4:	0331c823 */ 	subu	$t9,$t9,$s1
/*  f114ed8:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f114edc:	0331c821 */ 	addu	$t9,$t9,$s1
/*  f114ee0:	3c08800a */ 	lui	$t0,0x800a
/*  f114ee4:	25087658 */ 	addiu	$t0,$t0,0x7658
/*  f114ee8:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f114eec:	03282821 */ 	addu	$a1,$t9,$t0
.NB0f114ef0:
/*  f114ef0:	2484e5d8 */ 	addiu	$a0,$a0,-6696
/*  f114ef4:	0c01440d */ 	jal	osMotorProbe
/*  f114ef8:	02203025 */ 	or	$a2,$s1,$zero
/*  f114efc:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f114f00:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f114f04:	24a5e494 */ 	addiu	$a1,$a1,-7020
/*  f114f08:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f114f0c:	24040dbc */ 	addiu	$a0,$zero,0xdbc
/*  f114f10:	00112e00 */ 	sll	$a1,$s1,0x18
/*  f114f14:	00054e03 */ 	sra	$t1,$a1,0x18
/*  f114f18:	01202825 */ 	or	$a1,$t1,$zero
/*  f114f1c:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f114f20:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f114f24:	0fc458cb */ 	jal	pakHandleResult
/*  f114f28:	24070dbe */ 	addiu	$a3,$zero,0xdbe
/*  f114f2c:	10400008 */ 	beqz	$v0,.NB0f114f50
/*  f114f30:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f114f34:	8e0c0264 */ 	lw	$t4,0x264($s0)
/*  f114f38:	240b000b */ 	addiu	$t3,$zero,0xb
/*  f114f3c:	ae0a0000 */ 	sw	$t2,0x0($s0)
/*  f114f40:	258d0001 */ 	addiu	$t5,$t4,0x1
/*  f114f44:	ae0b0010 */ 	sw	$t3,0x10($s0)
/*  f114f48:	1000000c */ 	beqz	$zero,.NB0f114f7c
/*  f114f4c:	ae0d0264 */ 	sw	$t5,0x264($s0)
.NB0f114f50:
/*  f114f50:	92020014 */ 	lbu	$v0,0x14($s0)
.NB0f114f54:
/*  f114f54:	304e0004 */ 	andi	$t6,$v0,0x4
/*  f114f58:	11c00008 */ 	beqz	$t6,.NB0f114f7c
/*  f114f5c:	240f0008 */ 	addiu	$t7,$zero,0x8
/*  f114f60:	921802b8 */ 	lbu	$t8,0x2b8($s0)
/*  f114f64:	8e080264 */ 	lw	$t0,0x264($s0)
/*  f114f68:	ae0f0010 */ 	sw	$t7,0x10($s0)
/*  f114f6c:	3319ff7f */ 	andi	$t9,$t8,0xff7f
/*  f114f70:	25090001 */ 	addiu	$t1,$t0,0x1
/*  f114f74:	a21902b8 */ 	sb	$t9,0x2b8($s0)
/*  f114f78:	ae090264 */ 	sw	$t1,0x264($s0)
.NB0f114f7c:
/*  f114f7c:	8fbf001c */ 	lw	$ra,0x1c($sp)
.NB0f114f80:
/*  f114f80:	8fb00014 */ 	lw	$s0,0x14($sp)
/*  f114f84:	8fb10018 */ 	lw	$s1,0x18($sp)
/*  f114f88:	03e00008 */ 	jr	$ra
/*  f114f8c:	27bd0028 */ 	addiu	$sp,$sp,0x28
);
#endif

/**
 * Replace data between the given blocks with '!'.
 */
void pakWipe(s8 device, u32 blocknumstart, u32 blocknumend)
{
	u8 buffer[128];
	u32 i;

	for (i = 0; i < pakGetBlockSize(device); i++) {
		buffer[i] = '!';
	}

	for (i = blocknumstart; i < blocknumend; i++) {
		s32 result = pakReadWriteBlock(device, PFS(device), g_Paks[device].pdnoteindex, PFS_WRITE, i * pakGetBlockSize(device), pakGetBlockSize(device), buffer);

		g_Paks[device].headercachecount = 0;

		if (!pakHandleResult(result, device, true, LINE_3948)) {
#if VERSION >= VERSION_NTSC_1_0
			osSyncPrintf("Pak %d -> Game file wipe failed\n", device);
#else
			osSyncPrintf("Pak %d -> Game file wipe failed", device);
#endif
			g_Paks[device].pdnoteindex = -1;
			break;
		}
	}
}

void pakSaveHeaderToCache(s8 device, s32 blocknum, struct pakfileheader *header)
{
	struct pak *pak = &g_Paks[device];
	s32 count;
	s32 overview[1024];
	u32 stack[2];
	s32 j;
	s32 k;
	s32 i;
	s32 endblocknum = header->filelen / pakGetBlockSize(device) + blocknum;

	for (i = 0; i < ARRAYCOUNT(overview); i++) {
		overview[i] = -1;
	}

	// Iterate existing cache items and write their indexes into the overview array,
	// where the index in the overview array is determined by the cache item's blocknum.
	for (i = 0; i < pak->headercachecount; i++) {
		struct pakfileheader *tmp = (struct pakfileheader *) pak->headercache[i].payload;

		for (j = 0; j < tmp->filelen / pakGetBlockSize(device); j++) {
			overview[pak->headercache[i].blocknum + j] = i;
		}
	}

	// Examine the overview range where the new cache entry is going to go.
	// If any cache entries are there then they're likely an older version of
	// the cache header that's being inserted, so invalidate them.
	for (k = blocknum; k < endblocknum; k++) {
		if (overview[k] != -1) {
			pak->headercache[overview[k]].blocknum = -1;
		}
	}

	// Save the header into the cache
	pak->headercache[pak->headercachecount].blocknum = blocknum;
	memcpy(pak->headercache[pak->headercachecount].payload, header, pakGetBlockSize(device));

	pak->headercachecount++;

	// Close any gaps in the cache list and recount for good measure
	count = 0;

	for (i = 0; i < pak->headercachecount; i++) {
		if (pak->headercache[i].blocknum != -1) {
			pak->headercache[count].blocknum = pak->headercache[i].blocknum;
			memcpy(&pak->headercache[count].payload, &pak->headercache[i].payload, pakGetBlockSize(device));
			count++;
		}
	}

	pak->headercachecount = count;
}

bool pakRetrieveHeaderFromCache(s8 device, s32 blocknum, struct pakfileheader *dst)
{
	struct pak *pak = &g_Paks[device];
	s32 i;

	if (pak->headercachecount < MAX_HEADERCACHE_ENTRIES) {
		for (i = 0; i < pak->headercachecount; i++) {
			if (blocknum == pak->headercache[i].blocknum) {
				memcpy(dst, &pak->headercache[i].payload, sizeof(struct pakfileheader));
				return true;
			}
		}
	}

	return false;
}

/**
 * Initialise a game pak or controller pak note's filesystem from scratch.
 *
 * - A serial is generated for the pak.
 * - A terminator file (containing the serial) is then written at the start of the pak.
 * - Random bytes are then written into a block after the terminator.
 *
 * Return the pak's serial on success, or -1 on failure.
 */
s32 pakCreateFilesystem(s8 device)
{
	u8 data[32];
	s32 address;
	s32 result;
	s32 i;

	for (i = 0; i < 32; i++) {
		data[i] = random() & 0xff;
	}

	address = pakGetAlignedFileLenByBodyLen(device, pakGetBodyLenByType(device, PAKFILETYPE_TERMINATOR));

	g_Paks[device].maxfileid = 0x10;
#if VERSION >= VERSION_NTSC_1_0
	g_Paks[device].serial = pakGenerateSerial(device);
#else
	g_Paks[device].serial = 0x10 + random() % 0x1ff0;
#endif
	g_Paks[device].headercachecount = 0;

	pakWriteFileAtOffset(device, 0, PAKFILETYPE_TERMINATOR, NULL, 0, NULL, NULL, 0, 1);

	result = pakReadWriteBlock(device, PFS(device), g_Paks[device].pdnoteindex, PFS_WRITE, address, pakGetBlockSize(device), data);

#if VERSION >= VERSION_NTSC_1_0
	if (pakHandleResult(result, device, true, LINE_4140) == 0) {
		return -1;
	}
#else
	pakHandleResult(result, device, true, LINE_4140);
#endif

	return g_Paks[device].serial;
}

s32 pak0f11b6ec(s8 device)
{
	if (g_Paks[device].unk010 == PAK010_11 && g_Paks[device].type == PAKTYPE_MEMORY) {
		return 3;
	}

	return 0;
}

bool pakGetFilesystemLength(s8 device, u32 *outlen)
{
	struct pakfileheader header;
	s32 offset = 0;
	u32 stack[2];

	while (offset < g_Paks[device].pdnumbytes) {
		s32 ret = pakReadHeaderAtOffset(device, offset, &header);
		offset += header.filelen;

#if VERSION >= VERSION_NTSC_1_0
		if (ret == PAK_ERR2_NOPAK) {
			return true;
		}
#endif

		if (PAKFILETYPE_TERMINATOR == header.filetype) {
			*outlen = offset;
			return false;
		}

		if (ret != PAK_ERR2_OK) {
			return false;
		}
	}

	return false;
}

const char var7f1b4508[] = "RWI : Warning : tOffset > gPakObj[PakNum].GameFileSize\n";

/**
 * Read a file from cache or from the pak and write it to *data.
 */
s32 pak0f11b86c(s8 device, u32 offset, u8 *data, struct pakfileheader *header, s32 bodylen)
{
	struct pakfileheader headerstack;
	s32 s0;
#if VERSION >= VERSION_NTSC_1_0
	s32 negativebodylen2;
#endif
	bool negativebodylen;
	s32 ret;
	bool isoneblock;
	u32 i;
	u32 filelen;
	u32 blocksize;
	u32 alignedfilelen;
	u32 stack[3];
	u8 buffer[16];
	s32 offsetinblock;
	s32 blocknum;
	u8 sp58[128];

#if VERSION >= VERSION_NTSC_1_0
	if (bodylen == -1) {
		negativebodylen = true;
		negativebodylen2 = true;
		bodylen = 0;
	} else {
		negativebodylen = false;
		negativebodylen2 = false;
	}
#else
	if (bodylen == -1) {
		negativebodylen = true;
		bodylen = 0;
	} else {
		negativebodylen = false;
	}
#endif

	blocksize = pakGetBlockSize(device);
	isoneblock = bodylen && data && (bool)(bodylen + sizeof(struct pakfileheader) <= blocksize);

	if (header == NULL) {
		header = &headerstack;
	}

	ret = pakReadHeaderAtOffset(device, offset, header);

	if (ret != 0) {
		return ret;
	}

#if VERSION >= VERSION_NTSC_1_0
	if (!negativebodylen2 && !header->occupied) {
		return 10;
	}
#else
	if (!header->occupied) {
		return 10;
	}
#endif

	if (isoneblock) {
		if (pakRetrieveBlockFromCache(device, offset, buffer)) {
			for (i = 0; i < bodylen; i++) {
				data[i] = buffer[sizeof(struct pakfileheader) + i];
			}

			return 0;
		}
	}

	if (bodylen == header->bodylen) {
		bodylen = 0;
	}

	alignedfilelen = pakGetAlignedFileLenByBodyLen(device, header->bodylen);

	filelen = (bodylen == 0 ? header->bodylen : bodylen) + sizeof(struct pakfileheader);

	if (negativebodylen) {
		filelen = alignedfilelen;
	}

	joyDisableCyclicPolling(JOYARGS(4008));

	for (i = 0; i != filelen; i++) {
		offsetinblock = i % pakGetBlockSize(device);
		blocknum = i / pakGetBlockSize(device);

		if (offsetinblock == 0) {
			s32 absoluteoffset = pakGetBlockSize(device) * blocknum + offset;
			s32 ret;

			ret = pakReadWriteBlock(device, PFS(device), g_Paks[device].pdnoteindex, OS_READ, absoluteoffset, pakGetBlockSize(device), sp58);

			if (!pakHandleResult(ret, device, true, LINE_4394)) {
				joyEnableCyclicPolling(JOYARGS(4032));

				if (ret == 1) {
					return 1;
				}

				return 4;
			}
		}

		if (i >= 0x10 && data != NULL) {
			*data = sp58[offsetinblock];
			data++;
		}
	}

	joyEnableCyclicPolling(JOYARGS(4054));

	return 0;
}

const char var7f1b4540[] = "Pak %d -> Pak_DeleteFile_Offset - DataSize = %u\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b4574[] = "Pak %d -> Delete file offset (file id %d) failed\n";
const char var7f1b45a8[] = "Pak %d -> Delete file offset failed - Bad Offset passed\n";
#else
const char var7f1b4574[] = "Pak %d -> Delete file offset (file id %d) failed";
const char var7f1b45a8[] = "Pak %d -> Delete file offset failed - Bad Offset passed";
#endif

bool pakReplaceFileAtOffsetWithBlank(s8 device, u32 offset)
{
	struct pakfileheader header;
	s32 result;

	result = pakReadHeaderAtOffset(device, offset, &header);

	if (result == PAK_ERR2_OK) {
		result = pakWriteFileAtOffset(device, offset, PAKFILETYPE_BLANK, NULL, header.filelen - sizeof(struct pakfileheader), NULL, NULL, 0, 1);

		if (result == 0) {
			return true;
		}
	}

	return false;
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pakWriteFileAtOffset
/*  f11bc54:	27bddf40 */ 	addiu	$sp,$sp,-8384
/*  f11bc58:	afb70044 */ 	sw	$s7,0x44($sp)
/*  f11bc5c:	0004be00 */ 	sll	$s7,$a0,0x18
/*  f11bc60:	00177603 */ 	sra	$t6,$s7,0x18
/*  f11bc64:	afa420c0 */ 	sw	$a0,0x20c0($sp)
/*  f11bc68:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f11bc6c:	afbf004c */ 	sw	$ra,0x4c($sp)
/*  f11bc70:	afb40038 */ 	sw	$s4,0x38($sp)
/*  f11bc74:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f11bc78:	00c0a025 */ 	or	$s4,$a2,$zero
/*  f11bc7c:	01c0b825 */ 	or	$s7,$t6,$zero
/*  f11bc80:	afbe0048 */ 	sw	$s8,0x48($sp)
/*  f11bc84:	afb60040 */ 	sw	$s6,0x40($sp)
/*  f11bc88:	afb5003c */ 	sw	$s5,0x3c($sp)
/*  f11bc8c:	afb30034 */ 	sw	$s3,0x34($sp)
/*  f11bc90:	afb20030 */ 	sw	$s2,0x30($sp)
/*  f11bc94:	afb1002c */ 	sw	$s1,0x2c($sp)
/*  f11bc98:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f11bc9c:	afa520c4 */ 	sw	$a1,0x20c4($sp)
/*  f11bca0:	afa720cc */ 	sw	$a3,0x20cc($sp)
/*  f11bca4:	0fc45974 */ 	jal	pakGetBlockSize
/*  f11bca8:	01e02025 */ 	or	$a0,$t7,$zero
/*  f11bcac:	8fb220e0 */ 	lw	$s2,0x20e0($sp)
/*  f11bcb0:	8fa320d0 */ 	lw	$v1,0x20d0($sp)
/*  f11bcb4:	00409825 */ 	or	$s3,$v0,$zero
/*  f11bcb8:	325801ff */ 	andi	$t8,$s2,0x1ff
/*  f11bcbc:	10600003 */ 	beqz	$v1,.L0f11bccc
/*  f11bcc0:	03009025 */ 	or	$s2,$t8,$zero
/*  f11bcc4:	10000007 */ 	beqz	$zero,.L0f11bce4
/*  f11bcc8:	00608825 */ 	or	$s1,$v1,$zero
.L0f11bccc:
/*  f11bccc:	00172600 */ 	sll	$a0,$s7,0x18
/*  f11bcd0:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f11bcd4:	03202025 */ 	or	$a0,$t9,$zero
/*  f11bcd8:	0fc45c25 */ 	jal	pakGetBodyLenByType
/*  f11bcdc:	02802825 */ 	or	$a1,$s4,$zero
/*  f11bce0:	00408825 */ 	or	$s1,$v0,$zero
.L0f11bce4:
/*  f11bce4:	00172600 */ 	sll	$a0,$s7,0x18
/*  f11bce8:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f11bcec:	01202025 */ 	or	$a0,$t1,$zero
/*  f11bcf0:	0fc45996 */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f11bcf4:	02202825 */ 	or	$a1,$s1,$zero
/*  f11bcf8:	8fa320dc */ 	lw	$v1,0x20dc($sp)
/*  f11bcfc:	0040b025 */ 	or	$s6,$v0,$zero
/*  f11bd00:	27b020b0 */ 	addiu	$s0,$sp,0x20b0
/*  f11bd04:	10600015 */ 	beqz	$v1,.L0f11bd5c
/*  f11bd08:	00177880 */ 	sll	$t7,$s7,0x2
/*  f11bd0c:	8e02000c */ 	lw	$v0,0xc($s0)
/*  f11bd10:	01f77823 */ 	subu	$t7,$t7,$s7
/*  f11bd14:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11bd18:	01f77823 */ 	subu	$t7,$t7,$s7
/*  f11bd1c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11bd20:	00025302 */ 	srl	$t2,$v0,0xc
/*  f11bd24:	006a5826 */ 	xor	$t3,$v1,$t2
/*  f11bd28:	01f77821 */ 	addu	$t7,$t7,$s7
/*  f11bd2c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11bd30:	000b6640 */ 	sll	$t4,$t3,0x19
/*  f11bd34:	000c6b42 */ 	srl	$t5,$t4,0xd
/*  f11bd38:	01f77823 */ 	subu	$t7,$t7,$s7
/*  f11bd3c:	3c18800a */ 	lui	$t8,%hi(g_Paks)
/*  f11bd40:	27182380 */ 	addiu	$t8,$t8,%lo(g_Paks)
/*  f11bd44:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11bd48:	01a27026 */ 	xor	$t6,$t5,$v0
/*  f11bd4c:	ae0e000c */ 	sw	$t6,0xc($s0)
/*  f11bd50:	01f8c821 */ 	addu	$t9,$t7,$t8
/*  f11bd54:	10000019 */ 	beqz	$zero,.L0f11bdbc
/*  f11bd58:	afb90058 */ 	sw	$t9,0x58($sp)
.L0f11bd5c:
/*  f11bd5c:	00174880 */ 	sll	$t1,$s7,0x2
/*  f11bd60:	01374823 */ 	subu	$t1,$t1,$s7
/*  f11bd64:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11bd68:	01374823 */ 	subu	$t1,$t1,$s7
/*  f11bd6c:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11bd70:	01374821 */ 	addu	$t1,$t1,$s7
/*  f11bd74:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11bd78:	01374823 */ 	subu	$t1,$t1,$s7
/*  f11bd7c:	3c0a800a */ 	lui	$t2,%hi(g_Paks)
/*  f11bd80:	254a2380 */ 	addiu	$t2,$t2,%lo(g_Paks)
/*  f11bd84:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11bd88:	012a1021 */ 	addu	$v0,$t1,$t2
/*  f11bd8c:	8c4b025c */ 	lw	$t3,0x25c($v0)
/*  f11bd90:	8fa320bc */ 	lw	$v1,0x20bc($sp)
/*  f11bd94:	afa20058 */ 	sw	$v0,0x58($sp)
/*  f11bd98:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f11bd9c:	00037302 */ 	srl	$t6,$v1,0xc
/*  f11bda0:	018e7826 */ 	xor	$t7,$t4,$t6
/*  f11bda4:	000fc640 */ 	sll	$t8,$t7,0x19
/*  f11bda8:	0018cb42 */ 	srl	$t9,$t8,0xd
/*  f11bdac:	03231826 */ 	xor	$v1,$t9,$v1
/*  f11bdb0:	afa320bc */ 	sw	$v1,0x20bc($sp)
/*  f11bdb4:	ac4c025c */ 	sw	$t4,0x25c($v0)
/*  f11bdb8:	27b020b0 */ 	addiu	$s0,$sp,0x20b0
.L0f11bdbc:
/*  f11bdbc:	8fa90058 */ 	lw	$t1,0x58($sp)
/*  f11bdc0:	960e000c */ 	lhu	$t6,0xc($s0)
/*  f11bdc4:	960a000a */ 	lhu	$t2,0xa($s0)
/*  f11bdc8:	8d2b0260 */ 	lw	$t3,0x260($t1)
/*  f11bdcc:	32c90fff */ 	andi	$t1,$s6,0xfff
/*  f11bdd0:	31cf0007 */ 	andi	$t7,$t6,0x7
/*  f11bdd4:	000b68c0 */ 	sll	$t5,$t3,0x3
/*  f11bdd8:	314bf000 */ 	andi	$t3,$t2,0xf000
/*  f11bddc:	01afc025 */ 	or	$t8,$t5,$t7
/*  f11bde0:	012b6025 */ 	or	$t4,$t1,$t3
/*  f11bde4:	3c057f1b */ 	lui	$a1,%hi(var7f1b45e4)
/*  f11bde8:	a618000c */ 	sh	$t8,0xc($s0)
/*  f11bdec:	a60c000a */ 	sh	$t4,0xa($s0)
/*  f11bdf0:	24a545e4 */ 	addiu	$a1,$a1,%lo(var7f1b45e4)
/*  f11bdf4:	0c004c04 */ 	jal	argFindByPrefix
/*  f11bdf8:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f11bdfc:	10400003 */ 	beqz	$v0,.L0f11be0c
/*  f11be00:	8fa420d4 */ 	lw	$a0,0x20d4($sp)
/*  f11be04:	10000002 */ 	beqz	$zero,.L0f11be10
/*  f11be08:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f11be0c:
/*  f11be0c:	00001825 */ 	or	$v1,$zero,$zero
.L0f11be10:
/*  f11be10:	920f000f */ 	lbu	$t7,0xf($s0)
/*  f11be14:	00607025 */ 	or	$t6,$v1,$zero
/*  f11be18:	31cd0001 */ 	andi	$t5,$t6,0x1
/*  f11be1c:	31f8fffe */ 	andi	$t8,$t7,0xfffe
/*  f11be20:	01b8c825 */ 	or	$t9,$t5,$t8
/*  f11be24:	a219000f */ 	sb	$t9,0xf($s0)
/*  f11be28:	8fa920b8 */ 	lw	$t1,0x20b8($sp)
/*  f11be2c:	0012c8c0 */ 	sll	$t9,$s2,0x3
/*  f11be30:	332a0ff8 */ 	andi	$t2,$t9,0xff8
/*  f11be34:	00095b02 */ 	srl	$t3,$t1,0xc
/*  f11be38:	022b6026 */ 	xor	$t4,$s1,$t3
/*  f11be3c:	000c7540 */ 	sll	$t6,$t4,0x15
/*  f11be40:	000e7a42 */ 	srl	$t7,$t6,0x9
/*  f11be44:	01e96826 */ 	xor	$t5,$t7,$t1
/*  f11be48:	afad20b8 */ 	sw	$t5,0x20b8($sp)
/*  f11be4c:	960b000e */ 	lhu	$t3,0xe($s0)
/*  f11be50:	96180008 */ 	lhu	$t8,0x8($s0)
/*  f11be54:	02807825 */ 	or	$t7,$s4,$zero
/*  f11be58:	316cf007 */ 	andi	$t4,$t3,0xf007
/*  f11be5c:	014c7025 */ 	or	$t6,$t2,$t4
/*  f11be60:	a60e000e */ 	sh	$t6,0xe($s0)
/*  f11be64:	8e02000c */ 	lw	$v0,0xc($s0)
/*  f11be68:	000f69c0 */ 	sll	$t5,$t7,0x7
/*  f11be6c:	3319007f */ 	andi	$t9,$t8,0x7f
/*  f11be70:	00025340 */ 	sll	$t2,$v0,0xd
/*  f11be74:	000a6642 */ 	srl	$t4,$t2,0x19
/*  f11be78:	318e007f */ 	andi	$t6,$t4,0x7f
/*  f11be7c:	00027b02 */ 	srl	$t7,$v0,0xc
/*  f11be80:	01cf4826 */ 	xor	$t1,$t6,$t7
/*  f11be84:	01b95825 */ 	or	$t3,$t5,$t9
/*  f11be88:	0009c640 */ 	sll	$t8,$t1,0x19
/*  f11be8c:	00186b42 */ 	srl	$t5,$t8,0xd
/*  f11be90:	01a2c826 */ 	xor	$t9,$t5,$v0
/*  f11be94:	a60b0008 */ 	sh	$t3,0x8($s0)
/*  f11be98:	10800004 */ 	beqz	$a0,.L0f11beac
/*  f11be9c:	ae19000c */ 	sw	$t9,0xc($s0)
/*  f11bea0:	00195340 */ 	sll	$t2,$t9,0xd
/*  f11bea4:	000a6642 */ 	srl	$t4,$t2,0x19
/*  f11bea8:	ac8c0000 */ 	sw	$t4,0x0($a0)
.L0f11beac:
/*  f11beac:	8fa720cc */ 	lw	$a3,0x20cc($sp)
/*  f11beb0:	50e00007 */ 	beqzl	$a3,.L0f11bed0
/*  f11beb4:	9218000f */ 	lbu	$t8,0xf($s0)
/*  f11beb8:	920e000f */ 	lbu	$t6,0xf($s0)
/*  f11bebc:	31cffffb */ 	andi	$t7,$t6,0xfffb
/*  f11bec0:	35e90004 */ 	ori	$t1,$t7,0x4
/*  f11bec4:	10000004 */ 	beqz	$zero,.L0f11bed8
/*  f11bec8:	a209000f */ 	sb	$t1,0xf($s0)
/*  f11becc:	9218000f */ 	lbu	$t8,0xf($s0)
.L0f11bed0:
/*  f11bed0:	330dfffb */ 	andi	$t5,$t8,0xfffb
/*  f11bed4:	a20d000f */ 	sb	$t5,0xf($s0)
.L0f11bed8:
/*  f11bed8:	8e19000c */ 	lw	$t9,0xc($s0)
/*  f11bedc:	3409ffff */ 	dli	$t1,0xffff
/*  f11bee0:	3418ffff */ 	dli	$t8,0xffff
/*  f11bee4:	00195f40 */ 	sll	$t3,$t9,0x1d
/*  f11bee8:	000b57c2 */ 	srl	$t2,$t3,0x1f
/*  f11beec:	5140000b */ 	beqzl	$t2,.L0f11bf1c
/*  f11bef0:	a7a920b4 */ 	sh	$t1,0x20b4($sp)
/*  f11bef4:	8fac20b8 */ 	lw	$t4,0x20b8($sp)
/*  f11bef8:	00e02025 */ 	or	$a0,$a3,$zero
/*  f11befc:	27a620b4 */ 	addiu	$a2,$sp,0x20b4
/*  f11bf00:	000c7240 */ 	sll	$t6,$t4,0x9
/*  f11bf04:	000e7d42 */ 	srl	$t7,$t6,0x15
/*  f11bf08:	0fc462b9 */ 	jal	pakCalculateChecksum
/*  f11bf0c:	01e72821 */ 	addu	$a1,$t7,$a3
/*  f11bf10:	10000003 */ 	beqz	$zero,.L0f11bf20
/*  f11bf14:	8fa720cc */ 	lw	$a3,0x20cc($sp)
/*  f11bf18:	a7a920b4 */ 	sh	$t1,0x20b4($sp)
.L0f11bf1c:
/*  f11bf1c:	a7b820b6 */ 	sh	$t8,0x20b6($sp)
.L0f11bf20:
/*  f11bf20:	02d14023 */ 	subu	$t0,$s6,$s1
/*  f11bf24:	27b2109c */ 	addiu	$s2,$sp,0x109c
/*  f11bf28:	27b4009c */ 	addiu	$s4,$sp,0x9c
/*  f11bf2c:	2508fff0 */ 	addiu	$t0,$t0,-16
/*  f11bf30:	01003025 */ 	or	$a2,$t0,$zero
/*  f11bf34:	02401025 */ 	or	$v0,$s2,$zero
/*  f11bf38:	02801825 */ 	or	$v1,$s4,$zero
/*  f11bf3c:	0000a825 */ 	or	$s5,$zero,$zero
/*  f11bf40:	2404002b */ 	addiu	$a0,$zero,0x2b
.L0f11bf44:
/*  f11bf44:	02156821 */ 	addu	$t5,$s0,$s5
/*  f11bf48:	91b90000 */ 	lbu	$t9,0x0($t5)
/*  f11bf4c:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f11bf50:	2ea10010 */ 	sltiu	$at,$s5,0x10
/*  f11bf54:	a0590000 */ 	sb	$t9,0x0($v0)
/*  f11bf58:	a0640000 */ 	sb	$a0,0x0($v1)
/*  f11bf5c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11bf60:	1420fff8 */ 	bnez	$at,.L0f11bf44
/*  f11bf64:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11bf68:	12200014 */ 	beqz	$s1,.L0f11bfbc
/*  f11bf6c:	0000a825 */ 	or	$s5,$zero,$zero
/*  f11bf70:	8fa520d8 */ 	lw	$a1,0x20d8($sp)
.L0f11bf74:
/*  f11bf74:	50e00006 */ 	beqzl	$a3,.L0f11bf90
/*  f11bf78:	a0440000 */ 	sb	$a0,0x0($v0)
/*  f11bf7c:	00f55821 */ 	addu	$t3,$a3,$s5
/*  f11bf80:	916a0000 */ 	lbu	$t2,0x0($t3)
/*  f11bf84:	10000002 */ 	beqz	$zero,.L0f11bf90
/*  f11bf88:	a04a0000 */ 	sb	$t2,0x0($v0)
/*  f11bf8c:	a0440000 */ 	sb	$a0,0x0($v0)
.L0f11bf90:
/*  f11bf90:	10a00005 */ 	beqz	$a1,.L0f11bfa8
/*  f11bf94:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11bf98:	00b56021 */ 	addu	$t4,$a1,$s5
/*  f11bf9c:	918e0000 */ 	lbu	$t6,0x0($t4)
/*  f11bfa0:	10000002 */ 	beqz	$zero,.L0f11bfac
/*  f11bfa4:	a06e0000 */ 	sb	$t6,0x0($v1)
.L0f11bfa8:
/*  f11bfa8:	a0640000 */ 	sb	$a0,0x0($v1)
.L0f11bfac:
/*  f11bfac:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f11bfb0:	16b1fff0 */ 	bne	$s5,$s1,.L0f11bf74
/*  f11bfb4:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11bfb8:	0000a825 */ 	or	$s5,$zero,$zero
.L0f11bfbc:
/*  f11bfbc:	11000012 */ 	beqz	$t0,.L0f11c008
/*  f11bfc0:	8fa520d8 */ 	lw	$a1,0x20d8($sp)
.L0f11bfc4:
/*  f11bfc4:	50e00006 */ 	beqzl	$a3,.L0f11bfe0
/*  f11bfc8:	a0440000 */ 	sb	$a0,0x0($v0)
/*  f11bfcc:	00f57821 */ 	addu	$t7,$a3,$s5
/*  f11bfd0:	91e90000 */ 	lbu	$t1,0x0($t7)
/*  f11bfd4:	10000002 */ 	beqz	$zero,.L0f11bfe0
/*  f11bfd8:	a0490000 */ 	sb	$t1,0x0($v0)
/*  f11bfdc:	a0440000 */ 	sb	$a0,0x0($v0)
.L0f11bfe0:
/*  f11bfe0:	10a00005 */ 	beqz	$a1,.L0f11bff8
/*  f11bfe4:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11bfe8:	00b5c021 */ 	addu	$t8,$a1,$s5
/*  f11bfec:	930d0000 */ 	lbu	$t5,0x0($t8)
/*  f11bff0:	10000002 */ 	beqz	$zero,.L0f11bffc
/*  f11bff4:	a06d0000 */ 	sb	$t5,0x0($v1)
.L0f11bff8:
/*  f11bff8:	a0640000 */ 	sb	$a0,0x0($v1)
.L0f11bffc:
/*  f11bffc:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f11c000:	16a6fff0 */ 	bne	$s5,$a2,.L0f11bfc4
/*  f11c004:	24630001 */ 	addiu	$v1,$v1,0x1
.L0f11c008:
/*  f11c008:	02d3001b */ 	divu	$zero,$s6,$s3
/*  f11c00c:	00001012 */ 	mflo	$v0
/*  f11c010:	0000c810 */ 	mfhi	$t9
/*  f11c014:	00401825 */ 	or	$v1,$v0,$zero
/*  f11c018:	16600002 */ 	bnez	$s3,.L0f11c024
/*  f11c01c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c020:	0007000d */ 	break	0x7
.L0f11c024:
/*  f11c024:	13200002 */ 	beqz	$t9,.L0f11c030
/*  f11c028:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c02c:	24430001 */ 	addiu	$v1,$v0,0x1
.L0f11c030:
/*  f11c030:	0c00543a */ 	jal	joyDisableCyclicPolling
/*  f11c034:	afa30098 */ 	sw	$v1,0x98($sp)
/*  f11c038:	0000f025 */ 	or	$s8,$zero,$zero
.L0f11c03c:
/*  f11c03c:	13c00005 */ 	beqz	$s8,.L0f11c054
/*  f11c040:	0000a825 */ 	or	$s5,$zero,$zero
/*  f11c044:	93aa10ab */ 	lbu	$t2,0x10ab($sp)
/*  f11c048:	354c0002 */ 	ori	$t4,$t2,0x2
/*  f11c04c:	10000004 */ 	beqz	$zero,.L0f11c060
/*  f11c050:	a3ac10ab */ 	sb	$t4,0x10ab($sp)
.L0f11c054:
/*  f11c054:	93ae10ab */ 	lbu	$t6,0x10ab($sp)
/*  f11c058:	31cffffd */ 	andi	$t7,$t6,0xfffd
/*  f11c05c:	a3af10ab */ 	sb	$t7,0x10ab($sp)
.L0f11c060:
/*  f11c060:	27a410a4 */ 	addiu	$a0,$sp,0x10a4
/*  f11c064:	27a510ac */ 	addiu	$a1,$sp,0x10ac
/*  f11c068:	0fc462b9 */ 	jal	pakCalculateChecksum
/*  f11c06c:	02403025 */ 	or	$a2,$s2,$zero
/*  f11c070:	8fa90098 */ 	lw	$t1,0x98($sp)
/*  f11c074:	11200066 */ 	beqz	$t1,.L0f11c210
/*  f11c078:	00172600 */ 	sll	$a0,$s7,0x18
.L0f11c07c:
/*  f11c07c:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f11c080:	03002025 */ 	or	$a0,$t8,$zero
/*  f11c084:	0fc45974 */ 	jal	pakGetBlockSize
/*  f11c088:	00008025 */ 	or	$s0,$zero,$zero
/*  f11c08c:	00550019 */ 	multu	$v0,$s5
/*  f11c090:	8fad10a4 */ 	lw	$t5,0x10a4($sp)
/*  f11c094:	8fab20cc */ 	lw	$t3,0x20cc($sp)
/*  f11c098:	000dcdc2 */ 	srl	$t9,$t5,0x17
/*  f11c09c:	0000b012 */ 	mflo	$s6
/*  f11c0a0:	2ec10010 */ 	sltiu	$at,$s6,0x10
/*  f11c0a4:	50200004 */ 	beqzl	$at,.L0f11c0b8
/*  f11c0a8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f11c0ac:	10000020 */ 	beqz	$zero,.L0f11c130
/*  f11c0b0:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f11c0b4:	24010001 */ 	addiu	$at,$zero,0x1
.L0f11c0b8:
/*  f11c0b8:	13c10055 */ 	beq	$s8,$at,.L0f11c210
/*  f11c0bc:	8faa20d8 */ 	lw	$t2,0x20d8($sp)
/*  f11c0c0:	24010002 */ 	addiu	$at,$zero,0x2
/*  f11c0c4:	53210053 */ 	beql	$t9,$at,.L0f11c214
/*  f11c0c8:	27de0001 */ 	addiu	$s8,$s8,0x1
/*  f11c0cc:	51600051 */ 	beqzl	$t3,.L0f11c214
/*  f11c0d0:	27de0001 */ 	addiu	$s8,$s8,0x1
/*  f11c0d4:	51400016 */ 	beqzl	$t2,.L0f11c130
/*  f11c0d8:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f11c0dc:	12600014 */ 	beqz	$s3,.L0f11c130
/*  f11c0e0:	00001825 */ 	or	$v1,$zero,$zero
/*  f11c0e4:	02b30019 */ 	multu	$s5,$s3
/*  f11c0e8:	00002012 */ 	mflo	$a0
/*  f11c0ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c0f0:	00000000 */ 	sll	$zero,$zero,0x0
.L0f11c0f4:
/*  f11c0f4:	02446021 */ 	addu	$t4,$s2,$a0
/*  f11c0f8:	02847821 */ 	addu	$t7,$s4,$a0
/*  f11c0fc:	91e90000 */ 	lbu	$t1,0x0($t7)
/*  f11c100:	918e0000 */ 	lbu	$t6,0x0($t4)
/*  f11c104:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11c108:	0073082b */ 	sltu	$at,$v1,$s3
/*  f11c10c:	11c90003 */ 	beq	$t6,$t1,.L0f11c11c
/*  f11c110:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c114:	10000006 */ 	beqz	$zero,.L0f11c130
/*  f11c118:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f11c11c:
/*  f11c11c:	1420fff5 */ 	bnez	$at,.L0f11c0f4
/*  f11c120:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f11c124:	10000002 */ 	beqz	$zero,.L0f11c130
/*  f11c128:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c12c:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f11c130:
/*  f11c130:	12000033 */ 	beqz	$s0,.L0f11c200
/*  f11c134:	00172600 */ 	sll	$a0,$s7,0x18
/*  f11c138:	02b30019 */ 	multu	$s5,$s3
/*  f11c13c:	0017c880 */ 	sll	$t9,$s7,0x2
/*  f11c140:	0337c823 */ 	subu	$t9,$t9,$s7
/*  f11c144:	8fad20c4 */ 	lw	$t5,0x20c4($sp)
/*  f11c148:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f11c14c:	0337c821 */ 	addu	$t9,$t9,$s7
/*  f11c150:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11c154:	3c0b800a */ 	lui	$t3,%hi(g_Pfses)
/*  f11c158:	256b3180 */ 	addiu	$t3,$t3,%lo(g_Pfses)
/*  f11c15c:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f11c160:	0000c012 */ 	mflo	$t8
/*  f11c164:	00045603 */ 	sra	$t2,$a0,0x18
/*  f11c168:	16e10003 */ 	bne	$s7,$at,.L0f11c178
/*  f11c16c:	030d8821 */ 	addu	$s1,$t8,$t5
/*  f11c170:	10000002 */ 	beqz	$zero,.L0f11c17c
/*  f11c174:	00008025 */ 	or	$s0,$zero,$zero
.L0f11c178:
/*  f11c178:	032b8021 */ 	addu	$s0,$t9,$t3
.L0f11c17c:
/*  f11c17c:	0fc45974 */ 	jal	pakGetBlockSize
/*  f11c180:	01402025 */ 	or	$a0,$t2,$zero
/*  f11c184:	8faf0058 */ 	lw	$t7,0x58($sp)
/*  f11c188:	00172600 */ 	sll	$a0,$s7,0x18
/*  f11c18c:	00046603 */ 	sra	$t4,$a0,0x18
/*  f11c190:	8de6029c */ 	lw	$a2,0x29c($t7)
/*  f11c194:	02567021 */ 	addu	$t6,$s2,$s6
/*  f11c198:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f11c19c:	afa20014 */ 	sw	$v0,0x14($sp)
/*  f11c1a0:	afb10010 */ 	sw	$s1,0x10($sp)
/*  f11c1a4:	01802025 */ 	or	$a0,$t4,$zero
/*  f11c1a8:	02002825 */ 	or	$a1,$s0,$zero
/*  f11c1ac:	0fc46941 */ 	jal	pakReadWriteBlock
/*  f11c1b0:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f11c1b4:	00172e00 */ 	sll	$a1,$s7,0x18
/*  f11c1b8:	00054e03 */ 	sra	$t1,$a1,0x18
/*  f11c1bc:	00408025 */ 	or	$s0,$v0,$zero
/*  f11c1c0:	01202825 */ 	or	$a1,$t1,$zero
/*  f11c1c4:	00402025 */ 	or	$a0,$v0,$zero
/*  f11c1c8:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f11c1cc:	0fc470e7 */ 	jal	pakHandleResult
/*  f11c1d0:	24071286 */ 	addiu	$a3,$zero,_val7f11c1d0
/*  f11c1d4:	5440000b */ 	bnezl	$v0,.L0f11c204
/*  f11c1d8:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f11c1dc:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11c1e0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c1e4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f11c1e8:	16010003 */ 	bne	$s0,$at,.L0f11c1f8
/*  f11c1ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c1f0:	10000022 */ 	beqz	$zero,.L0f11c27c
/*  f11c1f4:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f11c1f8:
/*  f11c1f8:	10000020 */ 	beqz	$zero,.L0f11c27c
/*  f11c1fc:	24020004 */ 	addiu	$v0,$zero,0x4
.L0f11c200:
/*  f11c200:	8fb80098 */ 	lw	$t8,0x98($sp)
.L0f11c204:
/*  f11c204:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f11c208:	56b8ff9c */ 	bnel	$s5,$t8,.L0f11c07c
/*  f11c20c:	00172600 */ 	sll	$a0,$s7,0x18
.L0f11c210:
/*  f11c210:	27de0001 */ 	addiu	$s8,$s8,0x1
.L0f11c214:
/*  f11c214:	24010002 */ 	addiu	$at,$zero,0x2
/*  f11c218:	17c1ff88 */ 	bne	$s8,$at,.L0f11c03c
/*  f11c21c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c220:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11c224:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c228:	3c0d8007 */ 	lui	$t5,%hi(g_PakDebugPakCache)
/*  f11c22c:	8dad5ce8 */ 	lw	$t5,%lo(g_PakDebugPakCache)($t5)
/*  f11c230:	00172600 */ 	sll	$a0,$s7,0x18
/*  f11c234:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f11c238:	51a00010 */ 	beqzl	$t5,.L0f11c27c
/*  f11c23c:	00001025 */ 	or	$v0,$zero,$zero
/*  f11c240:	0fc45974 */ 	jal	pakGetBlockSize
/*  f11c244:	03202025 */ 	or	$a0,$t9,$zero
/*  f11c248:	8faa20c4 */ 	lw	$t2,0x20c4($sp)
/*  f11c24c:	00172600 */ 	sll	$a0,$s7,0x18
/*  f11c250:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f11c254:	0142001b */ 	divu	$zero,$t2,$v0
/*  f11c258:	00002812 */ 	mflo	$a1
/*  f11c25c:	01602025 */ 	or	$a0,$t3,$zero
/*  f11c260:	14400002 */ 	bnez	$v0,.L0f11c26c
/*  f11c264:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c268:	0007000d */ 	break	0x7
.L0f11c26c:
/*  f11c26c:	02403025 */ 	or	$a2,$s2,$zero
/*  f11c270:	0fc46c5e */ 	jal	pakSaveHeaderToCache
/*  f11c274:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11c278:	00001025 */ 	or	$v0,$zero,$zero
.L0f11c27c:
/*  f11c27c:	8fbf004c */ 	lw	$ra,0x4c($sp)
/*  f11c280:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f11c284:	8fb1002c */ 	lw	$s1,0x2c($sp)
/*  f11c288:	8fb20030 */ 	lw	$s2,0x30($sp)
/*  f11c28c:	8fb30034 */ 	lw	$s3,0x34($sp)
/*  f11c290:	8fb40038 */ 	lw	$s4,0x38($sp)
/*  f11c294:	8fb5003c */ 	lw	$s5,0x3c($sp)
/*  f11c298:	8fb60040 */ 	lw	$s6,0x40($sp)
/*  f11c29c:	8fb70044 */ 	lw	$s7,0x44($sp)
/*  f11c2a0:	8fbe0048 */ 	lw	$s8,0x48($sp)
/*  f11c2a4:	03e00008 */ 	jr	$ra
/*  f11c2a8:	27bd20c0 */ 	addiu	$sp,$sp,0x20c0
);
#else
GLOBAL_ASM(
glabel pakWriteFileAtOffset
/*  f115bd8:	27bddf40 */ 	addiu	$sp,$sp,-8384
/*  f115bdc:	afb70044 */ 	sw	$s7,0x44($sp)
/*  f115be0:	0004be00 */ 	sll	$s7,$a0,0x18
/*  f115be4:	00177603 */ 	sra	$t6,$s7,0x18
/*  f115be8:	afa420c0 */ 	sw	$a0,0x20c0($sp)
/*  f115bec:	000e2600 */ 	sll	$a0,$t6,0x18
/*  f115bf0:	afbf004c */ 	sw	$ra,0x4c($sp)
/*  f115bf4:	afb40038 */ 	sw	$s4,0x38($sp)
/*  f115bf8:	00047e03 */ 	sra	$t7,$a0,0x18
/*  f115bfc:	00c0a025 */ 	or	$s4,$a2,$zero
/*  f115c00:	01c0b825 */ 	or	$s7,$t6,$zero
/*  f115c04:	afbe0048 */ 	sw	$s8,0x48($sp)
/*  f115c08:	afb60040 */ 	sw	$s6,0x40($sp)
/*  f115c0c:	afb5003c */ 	sw	$s5,0x3c($sp)
/*  f115c10:	afb30034 */ 	sw	$s3,0x34($sp)
/*  f115c14:	afb20030 */ 	sw	$s2,0x30($sp)
/*  f115c18:	afb1002c */ 	sw	$s1,0x2c($sp)
/*  f115c1c:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f115c20:	afa520c4 */ 	sw	$a1,0x20c4($sp)
/*  f115c24:	afa720cc */ 	sw	$a3,0x20cc($sp)
/*  f115c28:	0fc4428c */ 	jal	pakGetBlockSize
/*  f115c2c:	01e02025 */ 	or	$a0,$t7,$zero
/*  f115c30:	8fb220e0 */ 	lw	$s2,0x20e0($sp)
/*  f115c34:	8fa320d0 */ 	lw	$v1,0x20d0($sp)
/*  f115c38:	00409825 */ 	or	$s3,$v0,$zero
/*  f115c3c:	325801ff */ 	andi	$t8,$s2,0x1ff
/*  f115c40:	10600003 */ 	beqz	$v1,.NB0f115c50
/*  f115c44:	03009025 */ 	or	$s2,$t8,$zero
/*  f115c48:	10000007 */ 	beqz	$zero,.NB0f115c68
/*  f115c4c:	00608825 */ 	or	$s1,$v1,$zero
.NB0f115c50:
/*  f115c50:	00172600 */ 	sll	$a0,$s7,0x18
/*  f115c54:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f115c58:	03202025 */ 	or	$a0,$t9,$zero
/*  f115c5c:	0fc444f9 */ 	jal	pakGetBodyLenByType
/*  f115c60:	02802825 */ 	or	$a1,$s4,$zero
/*  f115c64:	00408825 */ 	or	$s1,$v0,$zero
.NB0f115c68:
/*  f115c68:	00172600 */ 	sll	$a0,$s7,0x18
/*  f115c6c:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f115c70:	01202025 */ 	or	$a0,$t1,$zero
/*  f115c74:	0fc442ae */ 	jal	pakGetAlignedFileLenByBodyLen
/*  f115c78:	02202825 */ 	or	$a1,$s1,$zero
/*  f115c7c:	0040b025 */ 	or	$s6,$v0,$zero
/*  f115c80:	8fa220dc */ 	lw	$v0,0x20dc($sp)
/*  f115c84:	27b020b0 */ 	addiu	$s0,$sp,0x20b0
/*  f115c88:	8e03000c */ 	lw	$v1,0xc($s0)
/*  f115c8c:	10400013 */ 	beqz	$v0,.NB0f115cdc
/*  f115c90:	24040001 */ 	addiu	$a0,$zero,0x1
/*  f115c94:	00177880 */ 	sll	$t7,$s7,0x2
/*  f115c98:	01f77823 */ 	subu	$t7,$t7,$s7
/*  f115c9c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f115ca0:	00035302 */ 	srl	$t2,$v1,0xc
/*  f115ca4:	004a5826 */ 	xor	$t3,$v0,$t2
/*  f115ca8:	01f77823 */ 	subu	$t7,$t7,$s7
/*  f115cac:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f115cb0:	000b6640 */ 	sll	$t4,$t3,0x19
/*  f115cb4:	000c6b42 */ 	srl	$t5,$t4,0xd
/*  f115cb8:	01f77821 */ 	addu	$t7,$t7,$s7
/*  f115cbc:	3c18800a */ 	lui	$t8,0x800a
/*  f115cc0:	27186870 */ 	addiu	$t8,$t8,0x6870
/*  f115cc4:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f115cc8:	01a37026 */ 	xor	$t6,$t5,$v1
/*  f115ccc:	ae0e000c */ 	sw	$t6,0xc($s0)
/*  f115cd0:	01f8c821 */ 	addu	$t9,$t7,$t8
/*  f115cd4:	10000016 */ 	beqz	$zero,.NB0f115d30
/*  f115cd8:	afb90058 */ 	sw	$t9,0x58($sp)
.NB0f115cdc:
/*  f115cdc:	00174880 */ 	sll	$t1,$s7,0x2
/*  f115ce0:	01374823 */ 	subu	$t1,$t1,$s7
/*  f115ce4:	00094880 */ 	sll	$t1,$t1,0x2
/*  f115ce8:	01374823 */ 	subu	$t1,$t1,$s7
/*  f115cec:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f115cf0:	01374821 */ 	addu	$t1,$t1,$s7
/*  f115cf4:	3c0a800a */ 	lui	$t2,0x800a
/*  f115cf8:	254a6870 */ 	addiu	$t2,$t2,0x6870
/*  f115cfc:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f115d00:	012a1021 */ 	addu	$v0,$t1,$t2
/*  f115d04:	8c4b025c */ 	lw	$t3,0x25c($v0)
/*  f115d08:	8fa320bc */ 	lw	$v1,0x20bc($sp)
/*  f115d0c:	afa20058 */ 	sw	$v0,0x58($sp)
/*  f115d10:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f115d14:	00037302 */ 	srl	$t6,$v1,0xc
/*  f115d18:	018e7826 */ 	xor	$t7,$t4,$t6
/*  f115d1c:	000fc640 */ 	sll	$t8,$t7,0x19
/*  f115d20:	0018cb42 */ 	srl	$t9,$t8,0xd
/*  f115d24:	03231826 */ 	xor	$v1,$t9,$v1
/*  f115d28:	afa320bc */ 	sw	$v1,0x20bc($sp)
/*  f115d2c:	ac4c025c */ 	sw	$t4,0x25c($v0)
.NB0f115d30:
/*  f115d30:	8fa90058 */ 	lw	$t1,0x58($sp)
/*  f115d34:	960e000c */ 	lhu	$t6,0xc($s0)
/*  f115d38:	960a000a */ 	lhu	$t2,0xa($s0)
/*  f115d3c:	8d2b0260 */ 	lw	$t3,0x260($t1)
/*  f115d40:	32c90fff */ 	andi	$t1,$s6,0xfff
/*  f115d44:	31cf0007 */ 	andi	$t7,$t6,0x7
/*  f115d48:	000b68c0 */ 	sll	$t5,$t3,0x3
/*  f115d4c:	314bf000 */ 	andi	$t3,$t2,0xf000
/*  f115d50:	01afc025 */ 	or	$t8,$t5,$t7
/*  f115d54:	012b6025 */ 	or	$t4,$t1,$t3
/*  f115d58:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f115d5c:	a618000c */ 	sh	$t8,0xc($s0)
/*  f115d60:	a60c000a */ 	sh	$t4,0xa($s0)
/*  f115d64:	0c004e18 */ 	jal	argFindByPrefix
/*  f115d68:	24a5e5fc */ 	addiu	$a1,$a1,-6660
/*  f115d6c:	10400003 */ 	beqz	$v0,.NB0f115d7c
/*  f115d70:	8fa420d4 */ 	lw	$a0,0x20d4($sp)
/*  f115d74:	10000002 */ 	beqz	$zero,.NB0f115d80
/*  f115d78:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f115d7c:
/*  f115d7c:	00001025 */ 	or	$v0,$zero,$zero
.NB0f115d80:
/*  f115d80:	920f000f */ 	lbu	$t7,0xf($s0)
/*  f115d84:	00407025 */ 	or	$t6,$v0,$zero
/*  f115d88:	31cd0001 */ 	andi	$t5,$t6,0x1
/*  f115d8c:	31f8fffe */ 	andi	$t8,$t7,0xfffe
/*  f115d90:	01b8c825 */ 	or	$t9,$t5,$t8
/*  f115d94:	a219000f */ 	sb	$t9,0xf($s0)
/*  f115d98:	8fa920b8 */ 	lw	$t1,0x20b8($sp)
/*  f115d9c:	0012c8c0 */ 	sll	$t9,$s2,0x3
/*  f115da0:	332a0ff8 */ 	andi	$t2,$t9,0xff8
/*  f115da4:	00095b02 */ 	srl	$t3,$t1,0xc
/*  f115da8:	022b6026 */ 	xor	$t4,$s1,$t3
/*  f115dac:	000c7540 */ 	sll	$t6,$t4,0x15
/*  f115db0:	000e7a42 */ 	srl	$t7,$t6,0x9
/*  f115db4:	01e96826 */ 	xor	$t5,$t7,$t1
/*  f115db8:	afad20b8 */ 	sw	$t5,0x20b8($sp)
/*  f115dbc:	960b000e */ 	lhu	$t3,0xe($s0)
/*  f115dc0:	96180008 */ 	lhu	$t8,0x8($s0)
/*  f115dc4:	02807825 */ 	or	$t7,$s4,$zero
/*  f115dc8:	316cf007 */ 	andi	$t4,$t3,0xf007
/*  f115dcc:	014c7025 */ 	or	$t6,$t2,$t4
/*  f115dd0:	a60e000e */ 	sh	$t6,0xe($s0)
/*  f115dd4:	8e03000c */ 	lw	$v1,0xc($s0)
/*  f115dd8:	000f69c0 */ 	sll	$t5,$t7,0x7
/*  f115ddc:	3319007f */ 	andi	$t9,$t8,0x7f
/*  f115de0:	00035340 */ 	sll	$t2,$v1,0xd
/*  f115de4:	000a6642 */ 	srl	$t4,$t2,0x19
/*  f115de8:	318e007f */ 	andi	$t6,$t4,0x7f
/*  f115dec:	00037b02 */ 	srl	$t7,$v1,0xc
/*  f115df0:	01cf4826 */ 	xor	$t1,$t6,$t7
/*  f115df4:	01b95825 */ 	or	$t3,$t5,$t9
/*  f115df8:	0009c640 */ 	sll	$t8,$t1,0x19
/*  f115dfc:	00186b42 */ 	srl	$t5,$t8,0xd
/*  f115e00:	01a3c826 */ 	xor	$t9,$t5,$v1
/*  f115e04:	a60b0008 */ 	sh	$t3,0x8($s0)
/*  f115e08:	10800004 */ 	beqz	$a0,.NB0f115e1c
/*  f115e0c:	ae19000c */ 	sw	$t9,0xc($s0)
/*  f115e10:	00195340 */ 	sll	$t2,$t9,0xd
/*  f115e14:	000a6642 */ 	srl	$t4,$t2,0x19
/*  f115e18:	ac8c0000 */ 	sw	$t4,0x0($a0)
.NB0f115e1c:
/*  f115e1c:	8fa720cc */ 	lw	$a3,0x20cc($sp)
/*  f115e20:	50e00007 */ 	beqzl	$a3,.NB0f115e40
/*  f115e24:	9218000f */ 	lbu	$t8,0xf($s0)
/*  f115e28:	920e000f */ 	lbu	$t6,0xf($s0)
/*  f115e2c:	31cffffb */ 	andi	$t7,$t6,0xfffb
/*  f115e30:	35e90004 */ 	ori	$t1,$t7,0x4
/*  f115e34:	10000004 */ 	beqz	$zero,.NB0f115e48
/*  f115e38:	a209000f */ 	sb	$t1,0xf($s0)
/*  f115e3c:	9218000f */ 	lbu	$t8,0xf($s0)
.NB0f115e40:
/*  f115e40:	330dfffb */ 	andi	$t5,$t8,0xfffb
/*  f115e44:	a20d000f */ 	sb	$t5,0xf($s0)
.NB0f115e48:
/*  f115e48:	8e19000c */ 	lw	$t9,0xc($s0)
/*  f115e4c:	3409ffff */ 	dli	$t1,0xffff
/*  f115e50:	3418ffff */ 	dli	$t8,0xffff
/*  f115e54:	00195f40 */ 	sll	$t3,$t9,0x1d
/*  f115e58:	000b57c2 */ 	srl	$t2,$t3,0x1f
/*  f115e5c:	5140000b */ 	beqzl	$t2,.NB0f115e8c
/*  f115e60:	a7a920b4 */ 	sh	$t1,0x20b4($sp)
/*  f115e64:	8fac20b8 */ 	lw	$t4,0x20b8($sp)
/*  f115e68:	00e02025 */ 	or	$a0,$a3,$zero
/*  f115e6c:	27a620b4 */ 	addiu	$a2,$sp,0x20b4
/*  f115e70:	000c7240 */ 	sll	$t6,$t4,0x9
/*  f115e74:	000e7d42 */ 	srl	$t7,$t6,0x15
/*  f115e78:	0fc44b9b */ 	jal	pakCalculateChecksum
/*  f115e7c:	01e72821 */ 	addu	$a1,$t7,$a3
/*  f115e80:	10000003 */ 	beqz	$zero,.NB0f115e90
/*  f115e84:	8fa720cc */ 	lw	$a3,0x20cc($sp)
/*  f115e88:	a7a920b4 */ 	sh	$t1,0x20b4($sp)
.NB0f115e8c:
/*  f115e8c:	a7b820b6 */ 	sh	$t8,0x20b6($sp)
.NB0f115e90:
/*  f115e90:	02d14023 */ 	subu	$t0,$s6,$s1
/*  f115e94:	27b2109c */ 	addiu	$s2,$sp,0x109c
/*  f115e98:	27b4009c */ 	addiu	$s4,$sp,0x9c
/*  f115e9c:	2508fff0 */ 	addiu	$t0,$t0,-16
/*  f115ea0:	01002825 */ 	or	$a1,$t0,$zero
/*  f115ea4:	02401025 */ 	or	$v0,$s2,$zero
/*  f115ea8:	02801825 */ 	or	$v1,$s4,$zero
/*  f115eac:	0000a825 */ 	or	$s5,$zero,$zero
/*  f115eb0:	2404002b */ 	addiu	$a0,$zero,0x2b
.NB0f115eb4:
/*  f115eb4:	02156821 */ 	addu	$t5,$s0,$s5
/*  f115eb8:	91b90000 */ 	lbu	$t9,0x0($t5)
/*  f115ebc:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f115ec0:	2ea10010 */ 	sltiu	$at,$s5,0x10
/*  f115ec4:	a0590000 */ 	sb	$t9,0x0($v0)
/*  f115ec8:	a0640000 */ 	sb	$a0,0x0($v1)
/*  f115ecc:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f115ed0:	1420fff8 */ 	bnez	$at,.NB0f115eb4
/*  f115ed4:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f115ed8:	12200014 */ 	beqz	$s1,.NB0f115f2c
/*  f115edc:	0000a825 */ 	or	$s5,$zero,$zero
/*  f115ee0:	8fa620d8 */ 	lw	$a2,0x20d8($sp)
.NB0f115ee4:
/*  f115ee4:	50e00006 */ 	beqzl	$a3,.NB0f115f00
/*  f115ee8:	a0440000 */ 	sb	$a0,0x0($v0)
/*  f115eec:	00f55821 */ 	addu	$t3,$a3,$s5
/*  f115ef0:	916a0000 */ 	lbu	$t2,0x0($t3)
/*  f115ef4:	10000002 */ 	beqz	$zero,.NB0f115f00
/*  f115ef8:	a04a0000 */ 	sb	$t2,0x0($v0)
/*  f115efc:	a0440000 */ 	sb	$a0,0x0($v0)
.NB0f115f00:
/*  f115f00:	10c00005 */ 	beqz	$a2,.NB0f115f18
/*  f115f04:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f115f08:	00d56021 */ 	addu	$t4,$a2,$s5
/*  f115f0c:	918e0000 */ 	lbu	$t6,0x0($t4)
/*  f115f10:	10000002 */ 	beqz	$zero,.NB0f115f1c
/*  f115f14:	a06e0000 */ 	sb	$t6,0x0($v1)
.NB0f115f18:
/*  f115f18:	a0640000 */ 	sb	$a0,0x0($v1)
.NB0f115f1c:
/*  f115f1c:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f115f20:	16b1fff0 */ 	bne	$s5,$s1,.NB0f115ee4
/*  f115f24:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f115f28:	0000a825 */ 	or	$s5,$zero,$zero
.NB0f115f2c:
/*  f115f2c:	11000012 */ 	beqz	$t0,.NB0f115f78
/*  f115f30:	8fa620d8 */ 	lw	$a2,0x20d8($sp)
.NB0f115f34:
/*  f115f34:	50e00006 */ 	beqzl	$a3,.NB0f115f50
/*  f115f38:	a0440000 */ 	sb	$a0,0x0($v0)
/*  f115f3c:	00f57821 */ 	addu	$t7,$a3,$s5
/*  f115f40:	91e90000 */ 	lbu	$t1,0x0($t7)
/*  f115f44:	10000002 */ 	beqz	$zero,.NB0f115f50
/*  f115f48:	a0490000 */ 	sb	$t1,0x0($v0)
/*  f115f4c:	a0440000 */ 	sb	$a0,0x0($v0)
.NB0f115f50:
/*  f115f50:	10c00005 */ 	beqz	$a2,.NB0f115f68
/*  f115f54:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f115f58:	00d5c021 */ 	addu	$t8,$a2,$s5
/*  f115f5c:	930d0000 */ 	lbu	$t5,0x0($t8)
/*  f115f60:	10000002 */ 	beqz	$zero,.NB0f115f6c
/*  f115f64:	a06d0000 */ 	sb	$t5,0x0($v1)
.NB0f115f68:
/*  f115f68:	a0640000 */ 	sb	$a0,0x0($v1)
.NB0f115f6c:
/*  f115f6c:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f115f70:	16a5fff0 */ 	bne	$s5,$a1,.NB0f115f34
/*  f115f74:	24630001 */ 	addiu	$v1,$v1,0x1
.NB0f115f78:
/*  f115f78:	02d3001b */ 	divu	$zero,$s6,$s3
/*  f115f7c:	00001012 */ 	mflo	$v0
/*  f115f80:	0000c810 */ 	mfhi	$t9
/*  f115f84:	00401825 */ 	or	$v1,$v0,$zero
/*  f115f88:	16600002 */ 	bnez	$s3,.NB0f115f94
/*  f115f8c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f115f90:	0007000d */ 	break	0x7
.NB0f115f94:
/*  f115f94:	240410c4 */ 	addiu	$a0,$zero,0x10c4
/*  f115f98:	13200002 */ 	beqz	$t9,.NB0f115fa4
/*  f115f9c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f115fa0:	24430001 */ 	addiu	$v1,$v0,0x1
.NB0f115fa4:
/*  f115fa4:	24a5e60c */ 	addiu	$a1,$a1,-6644
/*  f115fa8:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f115fac:	afa30098 */ 	sw	$v1,0x98($sp)
/*  f115fb0:	0000f025 */ 	or	$s8,$zero,$zero
.NB0f115fb4:
/*  f115fb4:	13c00005 */ 	beqz	$s8,.NB0f115fcc
/*  f115fb8:	0000a825 */ 	or	$s5,$zero,$zero
/*  f115fbc:	93aa10ab */ 	lbu	$t2,0x10ab($sp)
/*  f115fc0:	354c0002 */ 	ori	$t4,$t2,0x2
/*  f115fc4:	10000004 */ 	beqz	$zero,.NB0f115fd8
/*  f115fc8:	a3ac10ab */ 	sb	$t4,0x10ab($sp)
.NB0f115fcc:
/*  f115fcc:	93ae10ab */ 	lbu	$t6,0x10ab($sp)
/*  f115fd0:	31cffffd */ 	andi	$t7,$t6,0xfffd
/*  f115fd4:	a3af10ab */ 	sb	$t7,0x10ab($sp)
.NB0f115fd8:
/*  f115fd8:	27a410a4 */ 	addiu	$a0,$sp,0x10a4
/*  f115fdc:	27a510ac */ 	addiu	$a1,$sp,0x10ac
/*  f115fe0:	0fc44b9b */ 	jal	pakCalculateChecksum
/*  f115fe4:	02403025 */ 	or	$a2,$s2,$zero
/*  f115fe8:	8fa90098 */ 	lw	$t1,0x98($sp)
/*  f115fec:	11200067 */ 	beqz	$t1,.NB0f11618c
/*  f115ff0:	00172600 */ 	sll	$a0,$s7,0x18
.NB0f115ff4:
/*  f115ff4:	0004c603 */ 	sra	$t8,$a0,0x18
/*  f115ff8:	03002025 */ 	or	$a0,$t8,$zero
/*  f115ffc:	0fc4428c */ 	jal	pakGetBlockSize
/*  f116000:	00008025 */ 	or	$s0,$zero,$zero
/*  f116004:	00550019 */ 	multu	$v0,$s5
/*  f116008:	8fad10a4 */ 	lw	$t5,0x10a4($sp)
/*  f11600c:	8fab20cc */ 	lw	$t3,0x20cc($sp)
/*  f116010:	000dcdc2 */ 	srl	$t9,$t5,0x17
/*  f116014:	0000b012 */ 	mflo	$s6
/*  f116018:	2ec10010 */ 	sltiu	$at,$s6,0x10
/*  f11601c:	50200004 */ 	beqzl	$at,.NB0f116030
/*  f116020:	24010001 */ 	addiu	$at,$zero,0x1
/*  f116024:	10000020 */ 	beqz	$zero,.NB0f1160a8
/*  f116028:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f11602c:	24010001 */ 	addiu	$at,$zero,0x1
.NB0f116030:
/*  f116030:	13c10056 */ 	beq	$s8,$at,.NB0f11618c
/*  f116034:	8faa20d8 */ 	lw	$t2,0x20d8($sp)
/*  f116038:	24010002 */ 	addiu	$at,$zero,0x2
/*  f11603c:	53210054 */ 	beql	$t9,$at,.NB0f116190
/*  f116040:	27de0001 */ 	addiu	$s8,$s8,0x1
/*  f116044:	51600052 */ 	beqzl	$t3,.NB0f116190
/*  f116048:	27de0001 */ 	addiu	$s8,$s8,0x1
/*  f11604c:	51400016 */ 	beqzl	$t2,.NB0f1160a8
/*  f116050:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f116054:	12600014 */ 	beqz	$s3,.NB0f1160a8
/*  f116058:	00001825 */ 	or	$v1,$zero,$zero
/*  f11605c:	02b30019 */ 	multu	$s5,$s3
/*  f116060:	00002012 */ 	mflo	$a0
/*  f116064:	00000000 */ 	sll	$zero,$zero,0x0
/*  f116068:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f11606c:
/*  f11606c:	02446021 */ 	addu	$t4,$s2,$a0
/*  f116070:	02847821 */ 	addu	$t7,$s4,$a0
/*  f116074:	91e90000 */ 	lbu	$t1,0x0($t7)
/*  f116078:	918e0000 */ 	lbu	$t6,0x0($t4)
/*  f11607c:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f116080:	0073082b */ 	sltu	$at,$v1,$s3
/*  f116084:	11c90003 */ 	beq	$t6,$t1,.NB0f116094
/*  f116088:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11608c:	10000006 */ 	beqz	$zero,.NB0f1160a8
/*  f116090:	24100001 */ 	addiu	$s0,$zero,0x1
.NB0f116094:
/*  f116094:	1420fff5 */ 	bnez	$at,.NB0f11606c
/*  f116098:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f11609c:	10000002 */ 	beqz	$zero,.NB0f1160a8
/*  f1160a0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1160a4:	24100001 */ 	addiu	$s0,$zero,0x1
.NB0f1160a8:
/*  f1160a8:	12000034 */ 	beqz	$s0,.NB0f11617c
/*  f1160ac:	00172600 */ 	sll	$a0,$s7,0x18
/*  f1160b0:	02b30019 */ 	multu	$s5,$s3
/*  f1160b4:	0017c880 */ 	sll	$t9,$s7,0x2
/*  f1160b8:	0337c823 */ 	subu	$t9,$t9,$s7
/*  f1160bc:	8fad20c4 */ 	lw	$t5,0x20c4($sp)
/*  f1160c0:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f1160c4:	0337c821 */ 	addu	$t9,$t9,$s7
/*  f1160c8:	24010004 */ 	addiu	$at,$zero,0x4
/*  f1160cc:	3c0b800a */ 	lui	$t3,0x800a
/*  f1160d0:	256b7658 */ 	addiu	$t3,$t3,0x7658
/*  f1160d4:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f1160d8:	0000c012 */ 	mflo	$t8
/*  f1160dc:	00045603 */ 	sra	$t2,$a0,0x18
/*  f1160e0:	16e10003 */ 	bne	$s7,$at,.NB0f1160f0
/*  f1160e4:	030d8821 */ 	addu	$s1,$t8,$t5
/*  f1160e8:	10000002 */ 	beqz	$zero,.NB0f1160f4
/*  f1160ec:	00008025 */ 	or	$s0,$zero,$zero
.NB0f1160f0:
/*  f1160f0:	032b8021 */ 	addu	$s0,$t9,$t3
.NB0f1160f4:
/*  f1160f4:	0fc4428c */ 	jal	pakGetBlockSize
/*  f1160f8:	01402025 */ 	or	$a0,$t2,$zero
/*  f1160fc:	8faf0058 */ 	lw	$t7,0x58($sp)
/*  f116100:	00172600 */ 	sll	$a0,$s7,0x18
/*  f116104:	00046603 */ 	sra	$t4,$a0,0x18
/*  f116108:	8de6029c */ 	lw	$a2,0x29c($t7)
/*  f11610c:	02567021 */ 	addu	$t6,$s2,$s6
/*  f116110:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f116114:	afa20014 */ 	sw	$v0,0x14($sp)
/*  f116118:	afb10010 */ 	sw	$s1,0x10($sp)
/*  f11611c:	01802025 */ 	or	$a0,$t4,$zero
/*  f116120:	02002825 */ 	or	$a1,$s0,$zero
/*  f116124:	0fc450ea */ 	jal	pakReadWriteBlock
/*  f116128:	24070001 */ 	addiu	$a3,$zero,0x1
/*  f11612c:	00172e00 */ 	sll	$a1,$s7,0x18
/*  f116130:	00054e03 */ 	sra	$t1,$a1,0x18
/*  f116134:	00408025 */ 	or	$s0,$v0,$zero
/*  f116138:	01202825 */ 	or	$a1,$t1,$zero
/*  f11613c:	00402025 */ 	or	$a0,$v0,$zero
/*  f116140:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f116144:	0fc458cb */ 	jal	pakHandleResult
/*  f116148:	24071119 */ 	addiu	$a3,$zero,0x1119
/*  f11614c:	1440000b */ 	bnez	$v0,.NB0f11617c
/*  f116150:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f116154:	24a5e614 */ 	addiu	$a1,$a1,-6636
/*  f116158:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f11615c:	2404111c */ 	addiu	$a0,$zero,0x111c
/*  f116160:	24010001 */ 	addiu	$at,$zero,0x1
/*  f116164:	16010003 */ 	bne	$s0,$at,.NB0f116174
/*  f116168:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11616c:	10000024 */ 	beqz	$zero,.NB0f116200
/*  f116170:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f116174:
/*  f116174:	10000022 */ 	beqz	$zero,.NB0f116200
/*  f116178:	24020004 */ 	addiu	$v0,$zero,0x4
.NB0f11617c:
/*  f11617c:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f116180:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f116184:	56b8ff9b */ 	bnel	$s5,$t8,.NB0f115ff4
/*  f116188:	00172600 */ 	sll	$a0,$s7,0x18
.NB0f11618c:
/*  f11618c:	27de0001 */ 	addiu	$s8,$s8,0x1
.NB0f116190:
/*  f116190:	24010002 */ 	addiu	$at,$zero,0x2
/*  f116194:	17c1ff87 */ 	bne	$s8,$at,.NB0f115fb4
/*  f116198:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11619c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1161a0:	24a5e61c */ 	addiu	$a1,$a1,-6628
/*  f1161a4:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f1161a8:	24041129 */ 	addiu	$a0,$zero,0x1129
/*  f1161ac:	3c0d8008 */ 	lui	$t5,0x8008
/*  f1161b0:	8dad80b0 */ 	lw	$t5,-0x7f50($t5)
/*  f1161b4:	00172600 */ 	sll	$a0,$s7,0x18
/*  f1161b8:	0004ce03 */ 	sra	$t9,$a0,0x18
/*  f1161bc:	51a00010 */ 	beqzl	$t5,.NB0f116200
/*  f1161c0:	00001025 */ 	or	$v0,$zero,$zero
/*  f1161c4:	0fc4428c */ 	jal	pakGetBlockSize
/*  f1161c8:	03202025 */ 	or	$a0,$t9,$zero
/*  f1161cc:	8faa20c4 */ 	lw	$t2,0x20c4($sp)
/*  f1161d0:	00172600 */ 	sll	$a0,$s7,0x18
/*  f1161d4:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f1161d8:	0142001b */ 	divu	$zero,$t2,$v0
/*  f1161dc:	00002812 */ 	mflo	$a1
/*  f1161e0:	01602025 */ 	or	$a0,$t3,$zero
/*  f1161e4:	14400002 */ 	bnez	$v0,.NB0f1161f0
/*  f1161e8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1161ec:	0007000d */ 	break	0x7
.NB0f1161f0:
/*  f1161f0:	02403025 */ 	or	$a2,$s2,$zero
/*  f1161f4:	0fc45454 */ 	jal	pakSaveHeaderToCache
/*  f1161f8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1161fc:	00001025 */ 	or	$v0,$zero,$zero
.NB0f116200:
/*  f116200:	8fbf004c */ 	lw	$ra,0x4c($sp)
/*  f116204:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f116208:	8fb1002c */ 	lw	$s1,0x2c($sp)
/*  f11620c:	8fb20030 */ 	lw	$s2,0x30($sp)
/*  f116210:	8fb30034 */ 	lw	$s3,0x34($sp)
/*  f116214:	8fb40038 */ 	lw	$s4,0x38($sp)
/*  f116218:	8fb5003c */ 	lw	$s5,0x3c($sp)
/*  f11621c:	8fb60040 */ 	lw	$s6,0x40($sp)
/*  f116220:	8fb70044 */ 	lw	$s7,0x44($sp)
/*  f116224:	8fbe0048 */ 	lw	$s8,0x48($sp)
/*  f116228:	03e00008 */ 	jr	$ra
/*  f11622c:	27bd20c0 */ 	addiu	$sp,$sp,0x20c0
);
#endif

const char var7f1b45e4[] = "-forceversion";

// Mismatch: callee-save registers are handled differently
//s32 pakWriteFileAtOffset(s8 device, u32 offset, s32 filetype, u8 *newdata, s32 bodylenarg, s32 *outfileid, u8 *olddata, u32 fileid, u32 generation)
//{
//	u8 header[sizeof(struct pakfileheader)]; // 20b0
//	struct pakfileheader *headerptr;
//	u32 blocksize;
//	u32 filelen;
//	u32 bodylen;
//	u8 newfile[0x1000]; // 109c
//	u8 oldfile[0x1000]; // 9c
//	u32 numblocks; // 98
//	s32 i = 0;
//	s32 j;
//	s32 k;
//	s32 index;
//	u32 result;
//	u8 version;
//	u32 paddinglen;
//	struct pakfileheader *s2;
//	struct pakfileheader *s4;
//
//	blocksize = pakGetBlockSize(device);
//
//	generation &= 0x1ff;
//	bodylen = bodylenarg ? bodylenarg : pakGetBodyLenByType(device, filetype);
//	filelen = pakGetAlignedFileLenByBodyLen(device, bodylen);
//
//	// Build the header bytes on the stack
//	headerptr = (struct pakfileheader *) &header;
//
//	headerptr->fileid = fileid ? fileid : ++g_Paks[device].maxfileid;
//	headerptr->deviceserial = g_Paks[device].serial;
//	headerptr->filelen = filelen;
//
//	version = argFindByPrefix(1, "-forceversion") ? 1 : 0;
//
//	headerptr->version = version;
//	headerptr->bodylen = bodylen;
//	headerptr->generation = generation;
//	headerptr->filetype = filetype;
//	headerptr->fileid &= 0x7f;
//
//	if (outfileid != NULL) {
//		*outfileid = headerptr->fileid;
//	}
//
//	headerptr->occupied = newdata ? 1 : 0;
//
//	if (headerptr->occupied) {
//		pakCalculateChecksum(newdata, newdata + headerptr->bodylen, headerptr->bodysum);
//	} else {
//		headerptr->bodysum[0] = 0xffff;
//		headerptr->bodysum[1] = 0xffff;
//	}
//
//	// Build "old" and "new" versions of the complete file on the stack.
//	// "old" is what is believed to be on the pak already, and "new" is what is
//	// needed to be written if any. Either the olddata or newdata pointers can
//	// be null when creating or deleting files, so substitute their bytes with
//	// a plus sign if so.
//	// These will then be compared block by block to decide which blocks need
//	// to be written to the pak.
//	s2 = (struct pakfileheader *) newfile;
//	s4 = (struct pakfileheader *) oldfile;
//	paddinglen = filelen - bodylen - sizeof(struct pakfileheader);
//	index = 0;
//
//	// Header
//	// f44
//	for (i = 0; i < sizeof(struct pakfileheader); i++) {
//		s2->bytes[index] = header[i];
//		s4->bytes[index] = '+';
//		index++;
//	}
//
//	// Data
//	// f74
//	for (i = 0; i != bodylen; i++) {
//		s2->bytes[index] = newdata ? newdata[i] : '+';
//		s4->bytes[index] = olddata ? olddata[i] : '+';
//		index++;
//	}
//
//	// Data padding to reach alignment
//	// fc4
//	for (i = 0; i != paddinglen; i++) {
//		s2->bytes[index] = newdata ? newdata[i] : '+';
//		s4->bytes[index] = olddata ? olddata[i] : '+';
//		index++;
//	}
//
//	// 008
//	numblocks = filelen / blocksize;
//
//	if (filelen % blocksize != 0) {
//		numblocks++;
//	}
//
//	joyDisableCyclicPolling();
//
//	// Write the header with writecompleted = 0, followed by the data, then
//	// rewrite the header with writecompleted = 1. This allows the game to
//	// detect if data on the pak was only partially written.
//	// 03c
//	for (j = 0; j < 2; j++) {
//		//struct pakfileheader *headerptr = (struct pakfileheader *) &newfile;
//		s2->writecompleted = j ? 1 : 0;
//
//		pakCalculateChecksum(&s2->bytes[0x08], &s2->bytes[0x10], s2->headersum); // sp10a4, sp10ac, s2
//
//		// 07c
//		for (i = 0; i != numblocks; i++) {
//			u32 offsetinfile = pakGetBlockSize(device) * i;
//			u32 writethisblock = false;
//
//			// 0a4
//			if (offsetinfile < sizeof(struct pakfileheader)) {
//				// Header - always write it
//				writethisblock = true;
//			} else {
//				// 0b8
//				// Don't write data on the second iteration
//				if (j == 1) {
//					break;
//				}
//
//				// 0c4, 0cc
//				// Don't write data for blank files or if the file is being deleted
//				if (s2->filetype == PAKFILETYPE_BLANK || newdata == NULL) {
//					break;
//				}
//
//				// 0d4
//				if (olddata) {
//					// Check if any bytes in the old and new blocks are different
//					for (k = 0; k < blocksize; k++) {
//						if (s2->bytes[i * blocksize + k] != s4->bytes[i * blocksize + k]) { // s2 and s4
//							writethisblock = true;
//							break;
//						}
//					}
//				} else {
//					writethisblock = true;
//				}
//			}
//
//			// 130
//			if (writethisblock) {
//				result = pakReadWriteBlock(device, PFS(device), g_Paks[device].pdnoteindex, OS_WRITE, offset + i * blocksize, pakGetBlockSize(device), &s2->bytes[offsetinfile]);
//
//				if (!pakHandleResult(result, device, true, 0x1286)) {
//					joyEnableCyclicPolling();
//
//					if (result == PAK_ERR1_NOPAK) {
//						return 1;
//					}
//
//					return 4;
//				}
//			}
//		}
//	}
//
//	joyEnableCyclicPolling();
//
//	if (g_PakDebugPakCache) {
//		pakSaveHeaderToCache(device, offset / pakGetBlockSize(device), s2);
//	}
//
//	return 0;
//}

#if VERSION < VERSION_NTSC_1_0
const char var7f1ae60cnb[] = "pak.c";
const char var7f1ae614nb[] = "pak.c";
const char var7f1ae61cnb[] = "pak.c";
#endif

bool pakRepair(s8 device)
{
	s32 result;

	switch (g_Paks[device].unk010) {
	case PAK010_14:
	case PAK010_19:
		break;
	default:
		joyDisableCyclicPolling(JOYARGS(4425));
		result = osPfsChecker(PFS(device));
		joyEnableCyclicPolling(JOYARGS(4427));

		if (result == PAK_ERR1_OK) {
			g_Paks[device].unk010 = PAK010_02;
			return true;
		}

		pakHandleResult(result, device, false, LINE_4801);

#if VERSION >= VERSION_NTSC_1_0
		g_Paks[device].unk010 = PAK010_22;
#endif
		break;
	}

#if VERSION < VERSION_NTSC_1_0
	g_Paks[device].unk010 = PAK010_22;
#endif

	return false;
}

const char var7f1b45f4[] = "PakMac_PaksLive()=%x\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b460c[] = "paksNeedToBeLive4Game=%x\n";
const char var7f1b4628[] = "paksNeedToBeLive4Menu=%x\n";
#endif

const char var7f1b4644[] = "g_LastPackPattern=%x\n";

#if VERSION < VERSION_NTSC_1_0
const char var7f1ae664nb[] = "lvGetPause    = %s";
const char var7f1ae678nb[] = "TRUE";
const char var7f1ae680nb[] = "FALSE";
const char var7f1ae688nb[] = "MP_GetPause   = %s";
const char var7f1ae69cnb[] = "TRUE";
const char var7f1ae6a4nb[] = "FALSE";
const char var7f1ae6acnb[] = "getnumplayers = %d";
const char var7f1ae6c0nb[] = "forcecrc";
const char var7f1ae6ccnb[] = "forcescrub";
const char var7f1ae6d8nb[] = "dumph";
const char var7f1ae6e0nb[] = "pakcache";
const char var7f1ae6ecnb[] = "pakinit";
const char var7f1ae6f4nb[] = "dumpeeprom";
const char var7f1ae700nb[] = "pak.c";
const char var7f1ae708nb[] = "pak.c";
#endif

#if VERSION >= VERSION_NTSC_1_0
bool pakHandleResult(s32 err1, s8 device, bool arg2, u32 line)
{
	if (err1 == PAK_ERR1_OK) {
		return true;
	}

	if (arg2) {
		switch (err1) {
		case PAK_ERR1_NOPAK:
			g_Paks[device].type = PAKTYPE_MEMORY;
			g_Paks[device].unk010 = PAK010_01;
			break;
		case PAK_ERR1_DEVICE:
			g_Paks[device].type = PAKTYPE_MEMORY;
			g_Paks[device].unk010 = PAK010_14;
			break;
		case PAK_ERR1_INCONSISTENT:
		case PAK_ERR1_IDFATAL:
			g_Paks[device].type = PAKTYPE_MEMORY;
			g_Paks[device].unk010 = PAK010_15;
			break;
		case PAK_ERR1_DATAFULL:
		case PAK_ERR1_DIRFULL:
			g_Paks[device].type = PAKTYPE_MEMORY;
			g_Paks[device].unk010 = PAK010_16;
			break;
		}
	}

	switch (err1) {
	case PAK_ERR1_NOPAK:
	case PAK_ERR1_NEWPAK:
	case PAK_ERR1_INCONSISTENT:
	case PAK_ERR1_CONTRFAIL:
	case PAK_ERR1_INVALID:
	case PAK_ERR1_BADDATA:
	case PAK_ERR1_DATAFULL:
	case PAK_ERR1_DIRFULL:
	case PAK_ERR1_EXIST:
	case PAK_ERR1_IDFATAL:
	case PAK_ERR1_DEVICE:
	case PAK_ERR1_NOGBCART:
	case PAK_ERR1_NEWGBCART:
	case PAK_ERR1_EEPROMMISSING:
	case PAK_ERR1_EEPROMREADFAILED:
	case PAK_ERR1_EEPROMWRITEFAILED:
	case PAK_ERR1_EEPROMINVALIDOP:
	case PAK_ERR1_EEPROMINVALIDARG:
		break;
	}

	return false;
}
#else
GLOBAL_ASM(
glabel pakHandleResult
.late_rodata
glabel var7f1af094nb
.word pakHandleResult+0x080
glabel var7f1af098nb
.word pakHandleResult+0x0f4
glabel var7f1af09cnb
.word pakHandleResult+0x0f4
glabel var7f1af0a0nb
.word pakHandleResult+0x0f4
glabel var7f1af0a4nb
.word pakHandleResult+0x0bc
glabel var7f1af0a8nb
.word pakHandleResult+0x0bc
glabel var7f1af0acnb
.word pakHandleResult+0x0f4
glabel var7f1af0b0nb
.word pakHandleResult+0x080
glabel var7f1af0b4nb
.word pakHandleResult+0x044
glabel var7f1af0b8nb
.word pakHandleResult+0x148
glabel var7f1af0bcnb
.word pakHandleResult+0x148
glabel var7f1af0c0nb
.word pakHandleResult+0x148
glabel var7f1af0c4nb
.word pakHandleResult+0x148
glabel var7f1af0c8nb
.word pakHandleResult+0x148
glabel var7f1af0ccnb
.word pakHandleResult+0x148
glabel var7f1af0d0nb
.word pakHandleResult+0x148
glabel var7f1af0d4nb
.word pakHandleResult+0x148
glabel var7f1af0d8nb
.word pakHandleResult+0x148
glabel var7f1af0dcnb
.word pakHandleResult+0x148
glabel var7f1af0e0nb
.word pakHandleResult+0x148
glabel var7f1af0e4nb
.word pakHandleResult+0x148
glabel var7f1af0e8nb
.word pakHandleResult+0x148
glabel var7f1af0ecnb
.word pakHandleResult+0x148
glabel var7f1af0f0nb
.word pakHandleResult+0x148
glabel var7f1af0f4nb
.word pakHandleResult+0x148
glabel var7f1af0f8nb
.word pakHandleResult+0x148
glabel var7f1af0fcnb
.word pakHandleResult+0x148
.text
/*  f11632c:	afa50004 */ 	sw	$a1,0x4($sp)
/*  f116330:	00057600 */ 	sll	$t6,$a1,0x18
/*  f116334:	000e2e03 */ 	sra	$a1,$t6,0x18
/*  f116338:	14800003 */ 	bnez	$a0,.NB0f116348
/*  f11633c:	afa7000c */ 	sw	$a3,0xc($sp)
/*  f116340:	03e00008 */ 	jr	$ra
/*  f116344:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f116348:
/*  f116348:	10c00035 */ 	beqz	$a2,.NB0f116420
/*  f11634c:	2498fffd */ 	addiu	$t8,$a0,-3
/*  f116350:	2f010009 */ 	sltiu	$at,$t8,0x9
/*  f116354:	10200032 */ 	beqz	$at,.NB0f116420
/*  f116358:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11635c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f116360:	00380821 */ 	addu	$at,$at,$t8
/*  f116364:	8c38f094 */ 	lw	$t8,-0xf6c($at)
/*  f116368:	03000008 */ 	jr	$t8
/*  f11636c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f116370:	0005c880 */ 	sll	$t9,$a1,0x2
/*  f116374:	0325c823 */ 	subu	$t9,$t9,$a1
/*  f116378:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f11637c:	0325c823 */ 	subu	$t9,$t9,$a1
/*  f116380:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f116384:	0325c821 */ 	addu	$t9,$t9,$a1
/*  f116388:	3c08800a */ 	lui	$t0,0x800a
/*  f11638c:	25086870 */ 	addiu	$t0,$t0,0x6870
/*  f116390:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f116394:	03281021 */ 	addu	$v0,$t9,$t0
/*  f116398:	24090002 */ 	addiu	$t1,$zero,0x2
/*  f11639c:	240a000e */ 	addiu	$t2,$zero,0xe
/*  f1163a0:	ac490000 */ 	sw	$t1,0x0($v0)
/*  f1163a4:	1000001e */ 	beqz	$zero,.NB0f116420
/*  f1163a8:	ac4a0010 */ 	sw	$t2,0x10($v0)
/*  f1163ac:	00055880 */ 	sll	$t3,$a1,0x2
/*  f1163b0:	01655823 */ 	subu	$t3,$t3,$a1
/*  f1163b4:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f1163b8:	01655823 */ 	subu	$t3,$t3,$a1
/*  f1163bc:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f1163c0:	01655821 */ 	addu	$t3,$t3,$a1
/*  f1163c4:	3c0c800a */ 	lui	$t4,0x800a
/*  f1163c8:	258c6870 */ 	addiu	$t4,$t4,0x6870
/*  f1163cc:	000b58c0 */ 	sll	$t3,$t3,0x3
/*  f1163d0:	016c1021 */ 	addu	$v0,$t3,$t4
/*  f1163d4:	240d0002 */ 	addiu	$t5,$zero,0x2
/*  f1163d8:	240e000f */ 	addiu	$t6,$zero,0xf
/*  f1163dc:	ac4d0000 */ 	sw	$t5,0x0($v0)
/*  f1163e0:	1000000f */ 	beqz	$zero,.NB0f116420
/*  f1163e4:	ac4e0010 */ 	sw	$t6,0x10($v0)
/*  f1163e8:	00057880 */ 	sll	$t7,$a1,0x2
/*  f1163ec:	01e57823 */ 	subu	$t7,$t7,$a1
/*  f1163f0:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f1163f4:	01e57823 */ 	subu	$t7,$t7,$a1
/*  f1163f8:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f1163fc:	01e57821 */ 	addu	$t7,$t7,$a1
/*  f116400:	3c18800a */ 	lui	$t8,0x800a
/*  f116404:	27186870 */ 	addiu	$t8,$t8,0x6870
/*  f116408:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f11640c:	01f81021 */ 	addu	$v0,$t7,$t8
/*  f116410:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f116414:	24080010 */ 	addiu	$t0,$zero,0x10
/*  f116418:	ac590000 */ 	sw	$t9,0x0($v0)
/*  f11641c:	ac480010 */ 	sw	$t0,0x10($v0)
.NB0f116420:
/*  f116420:	2881000e */ 	slti	$at,$a0,0xe
/*  f116424:	1420000a */ 	bnez	$at,.NB0f116450
/*  f116428:	00801025 */ 	or	$v0,$a0,$zero
/*  f11642c:	2449ff80 */ 	addiu	$t1,$v0,-128
/*  f116430:	2d210005 */ 	sltiu	$at,$t1,0x5
/*  f116434:	1020000f */ 	beqz	$at,.NB0f116474
/*  f116438:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11643c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f116440:	00290821 */ 	addu	$at,$at,$t1
/*  f116444:	8c29f0b8 */ 	lw	$t1,-0xf48($at)
/*  f116448:	01200008 */ 	jr	$t1
/*  f11644c:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f116450:
/*  f116450:	244affff */ 	addiu	$t2,$v0,-1
/*  f116454:	2d41000d */ 	sltiu	$at,$t2,0xd
/*  f116458:	10200006 */ 	beqz	$at,.NB0f116474
/*  f11645c:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f116460:	3c017f1b */ 	lui	$at,0x7f1b
/*  f116464:	002a0821 */ 	addu	$at,$at,$t2
/*  f116468:	8c2af0cc */ 	lw	$t2,-0xf34($at)
/*  f11646c:	01400008 */ 	jr	$t2
/*  f116470:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f116474:
/*  f116474:	00001025 */ 	or	$v0,$zero,$zero
/*  f116478:	03e00008 */ 	jr	$ra
/*  f11647c:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

#if VERSION >= VERSION_NTSC_1_0
void pak0f11c54c(void)
{
	s32 i;

	if (g_Vars.unk0004e4) {
		g_MpPlayerNum = 0;

		menuSetBanner(MENUBANNER_CHECKINGPAK, true);

		var80075d14 = 0;

		if (g_Vars.unk0004e4 & 0x0f) {
			joy00013974(0);

			// Waiting for some timer
			if ((g_Vars.unk0004e4 & 0x0f) > 9) {
				if ((g_Vars.lvframenum % 7) == 0) {
					g_Vars.unk0004e4--;
				}
			} else {
				g_Vars.unk0004e4--;
			}
		} else {
			joyCheckPfs(2);

			for (i = 0; i < 4; i++) {
				if (g_Vars.unk0004e4 & (1 << (i + 4))) {
					pak0f1169c8(i, true);
					g_Vars.unk0004e4 &= ~(1 << (i + 4));
				} else if (g_Vars.unk0004e4 & (1 << (i + 8))) {
					pak0f1169c8(i, false);
					g_Vars.unk0004e4 &= ~(1 << (i + 8));
				}
			}

			if (!joy00013980()) {
				joy00013974(1);
				joy000139c8();
			}

			menuSetBanner(-1, true);

			var80075d14 = 1;
		}
	}
}
#endif

#if VERSION >= VERSION_NTSC_1_0
void pak0f11c6d0(void)
{
	s32 i;

	for (i = 0; i < 4; i++) {
		switch (g_Paks[i].unk010) {
		case PAK010_02:
		case PAK010_03:
		case PAK010_04:
		case PAK010_05:
		case PAK010_06:
			g_Paks[i].unk010 = PAK010_01;
			var80075d10 &= ~(1 << i);
			g_MpPlayerNum = i;
			menuSetBanner(-1, true);
			break;
		}
	}

	var8005eedc = true;
}
#endif

#if VERSION >= VERSION_NTSC_1_0
void pakExecuteDebugOperations(void)
{
	static u32 g_PakDebugDumpEeprom = 0;
	s32 pass = false;
	s8 i;

	mainOverrideVariable("forcescrub", &g_PakDebugForceScrub);
	mainOverrideVariable("pakdump", &g_PakDebugPakDump);
	mainOverrideVariable("pakcache", &g_PakDebugPakCache);
	mainOverrideVariable("pakinit", &g_PakDebugPakInit);
	mainOverrideVariable("corruptme", &g_PakDebugCorruptMe);
	mainOverrideVariable("wipeeeprom", &g_PakDebugWipeEeprom);
	mainOverrideVariable("dumpeeprom", &g_PakDebugDumpEeprom);

	if (g_PakDebugCorruptMe) {
		g_PakDebugCorruptMe = false;
		pakCorrupt();
	}

	if (g_PakDebugPakDump) {
		pakDumpPak();
		g_PakDebugPakDump = false;
	}

	if (g_PakDebugDumpEeprom) {
		g_PakDebugDumpEeprom = false;
		pakDumpEeprom();
	}

	if (g_PakDebugWipeEeprom) {
		pakWipe(SAVEDEVICE_GAMEPAK, 0, 0x80);
		g_PakDebugWipeEeprom = false;
	}

	if (g_PakDebugPakInit) {
		s32 device = g_PakDebugPakInit - 1;

		joyDisableCyclicPolling();
		pakInitPak(&g_PiMesgQueue, PFS(device), device, 0);
		joyEnableCyclicPolling();

		g_PakDebugPakInit = false;
	}

	if (g_PakDebugForceScrub) {
		pakCreateFilesystem(SAVEDEVICE_GAMEPAK);
		g_PakDebugForceScrub = false;
	}

	pak0f11ca30();

	for (i = 0; i < 5; i++) {
		if (g_Paks[i].unk014) {
			pak0f11df94(i);
		}
	}

	for (i = 0; i < 5; i++) {
		switch (g_Paks[i].unk010) {
		case PAK010_02:
		case PAK010_03:
		case PAK010_04:
		case PAK010_05:
		case PAK010_06:
			pass = true;
			break;
		}
	}

	if (pass) {
		var8005eedc = false;
	} else {
		var8005eedc = true;
	}
}
#else
GLOBAL_ASM(
glabel pakExecuteDebugOperations
/*  f116480:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f116484:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f116488:	0fc59ed0 */ 	jal	lvIsPaused
/*  f11648c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f116490:	0fc60e8c */ 	jal	mpIsPaused
/*  f116494:	00000000 */ 	sll	$zero,$zero,0x0
/*  f116498:	3c047f1b */ 	lui	$a0,0x7f1b
/*  f11649c:	3c058008 */ 	lui	$a1,0x8008
/*  f1164a0:	24a580a4 */ 	addiu	$a1,$a1,-32604
/*  f1164a4:	0c00381c */ 	jal	mainOverrideVariable
/*  f1164a8:	2484e6c0 */ 	addiu	$a0,$a0,-6464
/*  f1164ac:	3c047f1b */ 	lui	$a0,0x7f1b
/*  f1164b0:	3c058008 */ 	lui	$a1,0x8008
/*  f1164b4:	24a580a8 */ 	addiu	$a1,$a1,-32600
/*  f1164b8:	0c00381c */ 	jal	mainOverrideVariable
/*  f1164bc:	2484e6cc */ 	addiu	$a0,$a0,-6452
/*  f1164c0:	3c047f1b */ 	lui	$a0,0x7f1b
/*  f1164c4:	3c058008 */ 	lui	$a1,0x8008
/*  f1164c8:	24a580ac */ 	addiu	$a1,$a1,-32596
/*  f1164cc:	0c00381c */ 	jal	mainOverrideVariable
/*  f1164d0:	2484e6d8 */ 	addiu	$a0,$a0,-6440
/*  f1164d4:	3c047f1b */ 	lui	$a0,0x7f1b
/*  f1164d8:	3c058008 */ 	lui	$a1,0x8008
/*  f1164dc:	24a580b0 */ 	addiu	$a1,$a1,-32592
/*  f1164e0:	0c00381c */ 	jal	mainOverrideVariable
/*  f1164e4:	2484e6e0 */ 	addiu	$a0,$a0,-6432
/*  f1164e8:	3c047f1b */ 	lui	$a0,0x7f1b
/*  f1164ec:	3c058008 */ 	lui	$a1,0x8008
/*  f1164f0:	24a580b4 */ 	addiu	$a1,$a1,-32588
/*  f1164f4:	0c00381c */ 	jal	mainOverrideVariable
/*  f1164f8:	2484e6ec */ 	addiu	$a0,$a0,-6420
/*  f1164fc:	3c047f1b */ 	lui	$a0,0x7f1b
/*  f116500:	3c058008 */ 	lui	$a1,0x8008
/*  f116504:	24a58110 */ 	addiu	$a1,$a1,-32496
/*  f116508:	0c00381c */ 	jal	mainOverrideVariable
/*  f11650c:	2484e6f4 */ 	addiu	$a0,$a0,-6412
/*  f116510:	3c0e8008 */ 	lui	$t6,0x8008
/*  f116514:	8dce8110 */ 	lw	$t6,-0x7ef0($t6)
/*  f116518:	3c018008 */ 	lui	$at,0x8008
/*  f11651c:	11c00003 */ 	beqz	$t6,.NB0f11652c
/*  f116520:	00000000 */ 	sll	$zero,$zero,0x0
/*  f116524:	0fc446e7 */ 	jal	pakDumpEeprom
/*  f116528:	ac208110 */ 	sw	$zero,-0x7ef0($at)
.NB0f11652c:
/*  f11652c:	3c028008 */ 	lui	$v0,0x8008
/*  f116530:	8c4280b4 */ 	lw	$v0,-0x7f4c($v0)
/*  f116534:	240411ce */ 	addiu	$a0,$zero,0x11ce
/*  f116538:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f11653c:	10400019 */ 	beqz	$v0,.NB0f1165a4
/*  f116540:	2450ffff */ 	addiu	$s0,$v0,-1
/*  f116544:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f116548:	24a5e700 */ 	addiu	$a1,$a1,-6400
/*  f11654c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f116550:	16010003 */ 	bne	$s0,$at,.NB0f116560
/*  f116554:	3c04800a */ 	lui	$a0,0x800a
/*  f116558:	10000009 */ 	beqz	$zero,.NB0f116580
/*  f11655c:	00002825 */ 	or	$a1,$zero,$zero
.NB0f116560:
/*  f116560:	00107880 */ 	sll	$t7,$s0,0x2
/*  f116564:	01f07823 */ 	subu	$t7,$t7,$s0
/*  f116568:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11656c:	01f07821 */ 	addu	$t7,$t7,$s0
/*  f116570:	3c18800a */ 	lui	$t8,0x800a
/*  f116574:	27187658 */ 	addiu	$t8,$t8,0x7658
/*  f116578:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f11657c:	01f82821 */ 	addu	$a1,$t7,$t8
.NB0f116580:
/*  f116580:	2484e5d8 */ 	addiu	$a0,$a0,-6696
/*  f116584:	0fc4478e */ 	jal	pakInitPak
/*  f116588:	02003025 */ 	or	$a2,$s0,$zero
/*  f11658c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f116590:	24a5e708 */ 	addiu	$a1,$a1,-6392
/*  f116594:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f116598:	240411d0 */ 	addiu	$a0,$zero,0x11d0
/*  f11659c:	3c018008 */ 	lui	$at,0x8008
/*  f1165a0:	ac2080b4 */ 	sw	$zero,-0x7f4c($at)
.NB0f1165a4:
/*  f1165a4:	3c198008 */ 	lui	$t9,0x8008
/*  f1165a8:	8f3980a4 */ 	lw	$t9,-0x7f5c($t9)
/*  f1165ac:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f1165b0:	2405004d */ 	addiu	$a1,$zero,0x4d
/*  f1165b4:	13200005 */ 	beqz	$t9,.NB0f1165cc
/*  f1165b8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1165bc:	0fc453e4 */ 	jal	pakWipe
/*  f1165c0:	2406004e */ 	addiu	$a2,$zero,0x4e
/*  f1165c4:	3c018008 */ 	lui	$at,0x8008
/*  f1165c8:	ac2080a4 */ 	sw	$zero,-0x7f5c($at)
.NB0f1165cc:
/*  f1165cc:	3c088008 */ 	lui	$t0,0x8008
/*  f1165d0:	8d0880a8 */ 	lw	$t0,-0x7f58($t0)
/*  f1165d4:	11000005 */ 	beqz	$t0,.NB0f1165ec
/*  f1165d8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1165dc:	0fc45544 */ 	jal	pakCreateFilesystem
/*  f1165e0:	24040004 */ 	addiu	$a0,$zero,0x4
/*  f1165e4:	3c018008 */ 	lui	$at,0x8008
/*  f1165e8:	ac2080a8 */ 	sw	$zero,-0x7f58($at)
.NB0f1165ec:
/*  f1165ec:	0fc4599b */ 	jal	pak0f11ca30
/*  f1165f0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1165f4:	0fc45ede */ 	jal	pakDumpPak
/*  f1165f8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1165fc:	00008025 */ 	or	$s0,$zero,$zero
/*  f116600:	00104880 */ 	sll	$t1,$s0,0x2
.NB0f116604:
/*  f116604:	01304823 */ 	subu	$t1,$t1,$s0
/*  f116608:	00094880 */ 	sll	$t1,$t1,0x2
/*  f11660c:	01304823 */ 	subu	$t1,$t1,$s0
/*  f116610:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f116614:	01304821 */ 	addu	$t1,$t1,$s0
/*  f116618:	000948c0 */ 	sll	$t1,$t1,0x3
/*  f11661c:	3c0a800a */ 	lui	$t2,0x800a
/*  f116620:	01495021 */ 	addu	$t2,$t2,$t1
/*  f116624:	914a6884 */ 	lbu	$t2,0x6884($t2)
/*  f116628:	00102600 */ 	sll	$a0,$s0,0x18
/*  f11662c:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f116630:	51400004 */ 	beqzl	$t2,.NB0f116644
/*  f116634:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f116638:	0fc45ee0 */ 	jal	pak0f11df94
/*  f11663c:	01602025 */ 	or	$a0,$t3,$zero
/*  f116640:	26100001 */ 	addiu	$s0,$s0,0x1
.NB0f116644:
/*  f116644:	00106600 */ 	sll	$t4,$s0,0x18
/*  f116648:	000c8603 */ 	sra	$s0,$t4,0x18
/*  f11664c:	2a010005 */ 	slti	$at,$s0,0x5
/*  f116650:	5420ffec */ 	bnezl	$at,.NB0f116604
/*  f116654:	00104880 */ 	sll	$t1,$s0,0x2
/*  f116658:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f11665c:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f116660:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f116664:	03e00008 */ 	jr	$ra
/*  f116668:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

const char var7f1b46a8[] = "\nOS_GBPAK_GBCART_ON       - ";
const char var7f1b46c8[] = "\nOS_GBPAK_GBCART_PULL     - ";
const char var7f1b46e8[] = "\nOS_GBPAK_POWER           - ";
const char var7f1b4708[] = "\nOS_GBPAK_RSTB_DETECTION  - ";
const char var7f1b4728[] = "Pak -> Dumping contents of Game Boy Pack(TM) Id file";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b4760[] = "(u16) - Fixed1             - %d\n";
const char var7f1b4784[] = "(u16) - StartAddress       - %d\n";
const char var7f1b47a8[] = "(u8*) - Nintendo chr data  - %s\n";
const char var7f1b47cc[] = "(u8*) - Game Title         - %s\n";
const char var7f1b47f0[] = "(u16) - Company Code       - %d\n";
const char var7f1b4814[] = "(u8 ) - Body Code          - %d\n";
const char var7f1b4838[] = "(u8 ) - Rom Size           - %d\n";
const char var7f1b485c[] = "(u8 ) - Ram Size           - %d\n";
const char var7f1b4880[] = "(u8 ) - country_code       - %d\n";
const char var7f1b48a4[] = "(u8 ) - Fixed 2 (0x33)     - %d\n";
const char var7f1b48c8[] = "(u8 ) - Version Number     - %d\n";
const char var7f1b48ec[] = "(u8 ) - isum               - %d\n";
const char var7f1b4910[] = "(u16) - sum                - %d\n";
#else
const char var7f1b4760[] = "(u16) - Fixed1             - %d";
const char var7f1b4784[] = "(u16) - StartAddress       - %d";
const char var7f1b47a8[] = "(u8*) - Nintendo chr data  - %s";
const char var7f1b47cc[] = "(u8*) - Game Title         - %s";
const char var7f1b47f0[] = "(u16) - Company Code       - %d";
const char var7f1b4814[] = "(u8 ) - Body Code          - %d";
const char var7f1b4838[] = "(u8 ) - Rom Size           - %d";
const char var7f1b485c[] = "(u8 ) - Ram Size           - %d";
const char var7f1b4880[] = "(u8 ) - country_code       - %d";
const char var7f1b48a4[] = "(u8 ) - Fixed 2 (0x33)     - %d";
const char var7f1b48c8[] = "(u8 ) - Version Number     - %d";
const char var7f1b48ec[] = "(u8 ) - isum               - %d";
const char var7f1b4910[] = "(u16) - sum                - %d";
#endif

const char var7f1b4934[] = "Pak -> Finished Dump";

#if VERSION < VERSION_NTSC_1_0
const char var7f1ae980nb[] = "Pak -> Game Boy Pack reset was sucessful\n";
const char var7f1ae9acnb[] = "Pak -> Connector Check Failed";
const char var7f1ae9ccnb[] = "Pak -> osGbpakReadId - Failed";
#endif

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f11ca30
/*  f11ca30:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f11ca34:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f11ca38:	3c15800a */ 	lui	$s5,%hi(g_Vars)
/*  f11ca3c:	26b59fc0 */ 	addiu	$s5,$s5,%lo(g_Vars)
/*  f11ca40:	8eae02ac */ 	lw	$t6,0x2ac($s5)
/*  f11ca44:	24010006 */ 	addiu	$at,$zero,0x6
/*  f11ca48:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f11ca4c:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f11ca50:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f11ca54:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f11ca58:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f11ca5c:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f11ca60:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f11ca64:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f11ca68:	15c10005 */ 	bne	$t6,$at,.L0f11ca80
/*  f11ca6c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f11ca70:	3c0f800a */ 	lui	$t7,%hi(g_MenuData)
/*  f11ca74:	8def19c0 */ 	lw	$t7,%lo(g_MenuData)($t7)
/*  f11ca78:	59e0003d */ 	blezl	$t7,.L0f11cb70
/*  f11ca7c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f11ca80:
/*  f11ca80:	96b804e4 */ 	lhu	$t8,0x4e4($s5)
/*  f11ca84:	3c028007 */ 	lui	$v0,%hi(var80075d10)
/*  f11ca88:	90565d10 */ 	lbu	$s6,%lo(var80075d10)($v0)
/*  f11ca8c:	3319000f */ 	andi	$t9,$t8,0xf
/*  f11ca90:	241400ff */ 	addiu	$s4,$zero,0xff
/*  f11ca94:	17200035 */ 	bnez	$t9,.L0f11cb6c
/*  f11ca98:	02c09825 */ 	or	$s3,$s6,$zero
/*  f11ca9c:	00008825 */ 	or	$s1,$zero,$zero
/*  f11caa0:	241e0002 */ 	addiu	$s8,$zero,0x2
/*  f11caa4:	241700ff */ 	addiu	$s7,$zero,0xff
/*  f11caa8:	92a904d1 */ 	lbu	$t1,0x4d1($s5)
.L0f11caac:
/*  f11caac:	92aa04d0 */ 	lbu	$t2,0x4d0($s5)
/*  f11cab0:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f11cab4:	02288004 */ 	sllv	$s0,$t0,$s1
/*  f11cab8:	012a5825 */ 	or	$t3,$t1,$t2
/*  f11cabc:	01706024 */ 	and	$t4,$t3,$s0
/*  f11cac0:	11800024 */ 	beqz	$t4,.L0f11cb54
/*  f11cac4:	02801825 */ 	or	$v1,$s4,$zero
/*  f11cac8:	16f40005 */ 	bne	$s7,$s4,.L0f11cae0
/*  f11cacc:	02c09025 */ 	or	$s2,$s6,$zero
/*  f11cad0:	0c004e7a */ 	jal	joyShiftPfsStates
/*  f11cad4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11cad8:	305400ff */ 	andi	$s4,$v0,0xff
/*  f11cadc:	02801825 */ 	or	$v1,$s4,$zero
.L0f11cae0:
/*  f11cae0:	00701024 */ 	and	$v0,$v1,$s0
/*  f11cae4:	02506824 */ 	and	$t5,$s2,$s0
/*  f11cae8:	11a2001a */ 	beq	$t5,$v0,.L0f11cb54
/*  f11caec:	00117080 */ 	sll	$t6,$s1,0x2
/*  f11caf0:	01d17023 */ 	subu	$t6,$t6,$s1
/*  f11caf4:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f11caf8:	01d17023 */ 	subu	$t6,$t6,$s1
/*  f11cafc:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f11cb00:	01d17021 */ 	addu	$t6,$t6,$s1
/*  f11cb04:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f11cb08:	01d17023 */ 	subu	$t6,$t6,$s1
/*  f11cb0c:	3c0f800a */ 	lui	$t7,%hi(g_Paks)
/*  f11cb10:	25ef2380 */ 	addiu	$t7,$t7,%lo(g_Paks)
/*  f11cb14:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f11cb18:	10400006 */ 	beqz	$v0,.L0f11cb34
/*  f11cb1c:	01cf1821 */ 	addu	$v1,$t6,$t7
/*  f11cb20:	02709825 */ 	or	$s3,$s3,$s0
/*  f11cb24:	327800ff */ 	andi	$t8,$s3,0xff
/*  f11cb28:	ac7e0010 */ 	sw	$s8,0x10($v1)
/*  f11cb2c:	10000009 */ 	beqz	$zero,.L0f11cb54
/*  f11cb30:	03009825 */ 	or	$s3,$t8,$zero
.L0f11cb34:
/*  f11cb34:	02004027 */ 	nor	$t0,$s0,$zero
/*  f11cb38:	02689824 */ 	and	$s3,$s3,$t0
/*  f11cb3c:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f11cb40:	326900ff */ 	andi	$t1,$s3,0xff
/*  f11cb44:	ac790010 */ 	sw	$t9,0x10($v1)
/*  f11cb48:	01209825 */ 	or	$s3,$t1,$zero
/*  f11cb4c:	0fc44364 */ 	jal	func0f110d90
/*  f11cb50:	02202025 */ 	or	$a0,$s1,$zero
.L0f11cb54:
/*  f11cb54:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f11cb58:	24010005 */ 	addiu	$at,$zero,0x5
/*  f11cb5c:	5621ffd3 */ 	bnel	$s1,$at,.L0f11caac
/*  f11cb60:	92a904d1 */ 	lbu	$t1,0x4d1($s5)
/*  f11cb64:	3c018007 */ 	lui	$at,%hi(var80075d10)
/*  f11cb68:	a0335d10 */ 	sb	$s3,%lo(var80075d10)($at)
.L0f11cb6c:
/*  f11cb6c:	8fbf003c */ 	lw	$ra,0x3c($sp)
.L0f11cb70:
/*  f11cb70:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f11cb74:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f11cb78:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f11cb7c:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f11cb80:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f11cb84:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f11cb88:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f11cb8c:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f11cb90:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f11cb94:	03e00008 */ 	jr	$ra
/*  f11cb98:	27bd0040 */ 	addiu	$sp,$sp,0x40
);

// Mismatch: regalloc
//void pak0f11ca30(void)
//{
//	if (g_Vars.tickmode != TICKMODE_CUTSCENE || g_MenuData.count > 0) {
//		u8 oldvalue = var80075d10;
//		u8 newvalue = var80075d10;
//		u8 thing = 0xff;
//		s32 i;
//
//		if ((g_Vars.unk0004e4 & 0xf) == 0) {
//			for (i = 0; i < 5; i++) {
//				u32 thisbit = 1 << i;
//
//				if ((g_Vars.paksconnected2 | g_Vars.paksconnected) & thisbit) {
//					if (thing == 0xff) {
//						thing = joyShiftPfsStates();
//					}
//
//					if ((thing & thisbit) != (oldvalue & thisbit)) {
//						if (thing & thisbit) {
//							g_Paks[i].unk010 = PAK010_02;
//							newvalue |= thisbit;
//						} else {
//							g_Paks[i].unk010 = PAK010_01;
//							newvalue &= ~thisbit;
//							func0f110d90(i);
//						}
//					}
//				}
//			}
//
//			var80075d10 = newvalue;
//		}
//	}
//}
#else
void pak0f11ca30(void)
{
	if (g_Vars.tickmode != TICKMODE_CUTSCENE) {
		u32 thing = joy00013980();
		u8 oldvalue = var80075d10;
		u8 newvalue = var80075d10;
		s32 i;

		for (i = 0; i < 5; i++) {
			u32 thisbit = 1 << i;

			if ((g_Vars.paksconnected2 | g_Vars.paksconnected) & thisbit) {
				if ((thing & thisbit) != (oldvalue & thisbit)) {
					if (thing & thisbit) {
						g_Paks[i].unk010 = PAK010_02;
						newvalue |= thisbit;
					} else {
						g_Paks[i].unk010 = PAK010_01;
						newvalue &= ~thisbit;
					}
				}
			}
		}

		var80075d10 = newvalue;
	}
}
#endif

void gbpakHandleError(u32 err)
{
#if VERSION >= VERSION_NTSC_1_0
	switch (err) {
		case PFS_ERR_NOPACK:
		case PFS_ERR_NEW_PACK:
		case PFS_ERR_INCONSISTENT:
		case PFS_ERR_CONTRFAIL:
		case PFS_ERR_INVALID:
		case PFS_ERR_BAD_DATA:
		case PFS_DATA_FULL:
		case PFS_DIR_FULL:
		case PFS_ERR_EXIST:
		case PFS_ERR_ID_FATAL:
		case PFS_ERR_DEVICE:
		case PFS_ERR_NO_GBCART:
		case PFS_ERR_NEW_GBCART:
			break;
	}
#endif
}

#if VERSION >= VERSION_NTSC_1_0
void pak0f11cbc8(void)
{
	// empty
}

void pak0f11cbd0(void)
{
	// empty
}
#endif

#if VERSION < VERSION_NTSC_1_0
void pak0f116758nb(u32 arg0)
{
	// empty
}

void pak0f116760nb(u32 arg0)
{
	// empty
}
#endif

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f116768nb
/*  f116768:	00043e00 */ 	sll	$a3,$a0,0x18
/*  f11676c:	00077603 */ 	sra	$t6,$a3,0x18
/*  f116770:	27bdff88 */ 	addiu	$sp,$sp,-120
/*  f116774:	24010004 */ 	addiu	$at,$zero,0x4
/*  f116778:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f11677c:	afa40078 */ 	sw	$a0,0x78($sp)
/*  f116780:	15c10003 */ 	bne	$t6,$at,.NB0f116790
/*  f116784:	01c03825 */ 	or	$a3,$t6,$zero
/*  f116788:	10000009 */ 	beqz	$zero,.NB0f1167b0
/*  f11678c:	00002025 */ 	or	$a0,$zero,$zero
.NB0f116790:
/*  f116790:	00077880 */ 	sll	$t7,$a3,0x2
/*  f116794:	01e77823 */ 	subu	$t7,$t7,$a3
/*  f116798:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11679c:	01e77821 */ 	addu	$t7,$t7,$a3
/*  f1167a0:	3c18800a */ 	lui	$t8,0x800a
/*  f1167a4:	27187658 */ 	addiu	$t8,$t8,0x7658
/*  f1167a8:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f1167ac:	01f82021 */ 	addu	$a0,$t7,$t8
.NB0f1167b0:
/*  f1167b0:	27a50028 */ 	addiu	$a1,$sp,0x28
/*  f1167b4:	27a60023 */ 	addiu	$a2,$sp,0x23
/*  f1167b8:	0c014950 */ 	jal	osGbpakReadId
/*  f1167bc:	a3a7007b */ 	sb	$a3,0x7b($sp)
/*  f1167c0:	83a7007b */ 	lb	$a3,0x7b($sp)
/*  f1167c4:	1440001d */ 	bnez	$v0,.NB0f11683c
/*  f1167c8:	00402025 */ 	or	$a0,$v0,$zero
/*  f1167cc:	93a40023 */ 	lbu	$a0,0x23($sp)
/*  f1167d0:	0fc459d6 */ 	jal	pak0f116758nb
/*  f1167d4:	a3a7007b */ 	sb	$a3,0x7b($sp)
/*  f1167d8:	0fc459d8 */ 	jal	pak0f116760nb
/*  f1167dc:	27a40028 */ 	addiu	$a0,$sp,0x28
/*  f1167e0:	83a7007b */ 	lb	$a3,0x7b($sp)
/*  f1167e4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f1167e8:	3c08800a */ 	lui	$t0,0x800a
/*  f1167ec:	14e10003 */ 	bne	$a3,$at,.NB0f1167fc
/*  f1167f0:	0007c880 */ 	sll	$t9,$a3,0x2
/*  f1167f4:	10000007 */ 	beqz	$zero,.NB0f116814
/*  f1167f8:	00002025 */ 	or	$a0,$zero,$zero
.NB0f1167fc:
/*  f1167fc:	0327c823 */ 	subu	$t9,$t9,$a3
/*  f116800:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f116804:	0327c821 */ 	addu	$t9,$t9,$a3
/*  f116808:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f11680c:	25087658 */ 	addiu	$t0,$t0,0x7658
/*  f116810:	03282021 */ 	addu	$a0,$t9,$t0
.NB0f116814:
/*  f116814:	0c0149c0 */ 	jal	osGbpakCheckConnector
/*  f116818:	27a50023 */ 	addiu	$a1,$sp,0x23
/*  f11681c:	14400003 */ 	bnez	$v0,.NB0f11682c
/*  f116820:	00402025 */ 	or	$a0,$v0,$zero
/*  f116824:	10000008 */ 	beqz	$zero,.NB0f116848
/*  f116828:	24020001 */ 	addiu	$v0,$zero,0x1
.NB0f11682c:
/*  f11682c:	0fc459d4 */ 	jal	gbpakHandleError
/*  f116830:	00000000 */ 	sll	$zero,$zero,0x0
/*  f116834:	10000004 */ 	beqz	$zero,.NB0f116848
/*  f116838:	00001025 */ 	or	$v0,$zero,$zero
.NB0f11683c:
/*  f11683c:	0fc459d4 */ 	jal	gbpakHandleError
/*  f116840:	00000000 */ 	sll	$zero,$zero,0x0
/*  f116844:	00001025 */ 	or	$v0,$zero,$zero
.NB0f116848:
/*  f116848:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11684c:	27bd0078 */ 	addiu	$sp,$sp,0x78
/*  f116850:	03e00008 */ 	jr	$ra
/*  f116854:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

bool gbpakRead(s8 device, u16 address, u8 *buffer, u16 size)
{
	s32 result = osGbpakReadWrite(PFS(device), OS_READ, address, buffer, size);

	if (result) {
		gbpakHandleError(result);
		return false;
	}

	return true;
}

bool gbpakWrite(s8 device, u16 address, u8 *buffer, u16 size)
{
	s32 result = osGbpakReadWrite(PFS(device), OS_WRITE, address, buffer, size);

	if (result) {
		gbpakHandleError(result);
		return false;
	}

	return true;
}

/**
 * Note: ntsc-beta needs the tmp variable to get the instruction ordering
 * correct, but there is not enough room in the stack to do this. So for
 * matching purposes, the buffer is being reduced to make room for tmp.
 * buffer is actually 32 though.
 */
bool pak0f11cd00(s8 device, u16 arg1, char *arg2, s32 arg3, s32 arg4)
{
#if VERSION >= VERSION_NTSC_1_0
	u8 buffer[32];
	bool result = false;
	s32 i;

	for (i = 0; i < 32; i++) {
		buffer[i] = '\n';
	}

	gbpakWrite(device, 0, buffer, sizeof(buffer));
#else
	bool result = false;
	s32 i;
	s32 tmp;
	u8 buffer[28];
#endif

	if (arg4 >= 0) {
#if VERSION >= VERSION_NTSC_1_0
		for (i = 0; i < 32; i++) {
			buffer[i] = (s32)(arg1 + 0xffff6000) / 0x2000;
		}
#else
		tmp = (s32)(arg1 + 0xffff6000) / 0x2000;

		for (i = 0; i < 32; i++) {
			buffer[i] = tmp;
		}
#endif

		if (gbpakWrite(device, 0x4000, buffer, 32)) {
			result = true;
		}
	} else {
		result = true;
	}

	if (result && gbpakWrite(device, arg1, arg2, arg3)) {
		result = true;
	}

	return result;
}

bool pak0f11ce00(s8 device, u16 arg1, char *arg2, s32 arg3, bool arg4)
{
#if VERSION >= VERSION_NTSC_1_0
	u8 buffer[32];
	bool result = false;
	s32 i;

	for (i = 0; i < 32; i++) {
		buffer[i] = 0;
	}

	gbpakWrite(device, 0, buffer, sizeof(buffer));
#else
	bool result = false;
	s32 i;
	u8 buffer[32];
#endif

	if (arg4) {
		for (i = 0; i < 32; i++) {
			buffer[i] = 0;
		}

		buffer[31] = (s32)(arg1 + 0xffff6000) / 0x2000;

		if (gbpakWrite(device, 0x4000, buffer, sizeof(buffer))) {
			result = true;
		}
	} else {
		result = true;
	}

	if (result && gbpakRead(device, arg1, arg2, arg3)) {
		result = true;
	}

	return result;
}

bool gbpak0f11cef8(s8 device)
{
	struct pak *pak = &g_Paks[device];
	u8 spac[32];
	u8 sp8c[32];
	u8 sp6c[32];
	u8 sp2c[64];
	s32 i;

	if (pak->type == PAKTYPE_GAMEBOY) {
		for (i = 0; i < (s32)sizeof(spac); i++) {
			spac[i] = 2;
		}

		if (!gbpakWrite(device, 0x4000, spac, sizeof(spac))) {
			return false;
		}

		if (!gbpakRead(device, 0xafe0, sp8c, sizeof(sp8c))) {
			return false;
		}

		for (i = 0; i < (s32)sizeof(spac); i++) {
			spac[i] = 8;
		}

		if (!gbpakWrite(device, 0x4000, spac, sizeof(spac))) {
			return false;
		}

		if (!gbpakRead(device, 0xbfe0, sp6c, sizeof(sp6c))) {
			return false;
		}

		for (i = 0; i < (s32)sizeof(spac); i++) {
			spac[i] = 16;
		}

		if (!gbpakWrite(device, 0x4000, spac, sizeof(spac))) {
			return false;
		}

		for (i = 0; i < sizeof(sp2c); i++) {
			sp2c[i] = 0;
		}

		pak->unk2ba = sp8c[26];
		pak->unk2bb = sp6c[26];
		pak->unk2b9 = (pak->unk2ba == pak->unk2bb ? pak->unk2ba : pak->unk2bb);

		if (pak->unk2b9);

		pak0f11d118(sp2c, pak->unk2b9, func0f14aa70());
		pak0f11d174(device, sp2c);

		sp2c[0] |= 1;

		if (!gbpakWrite(device, 0xa000, sp2c, sizeof(sp2c))) {
			return false;
		}
	}

	pak->unk008 = 1;

	return true;
}

#if VERSION >= VERSION_NTSC_1_0
void pak0f11d110(void)
{
	// empty
}
#endif

#if VERSION < VERSION_NTSC_1_0
u32 pak0f116d1cnb(s8 device)
{
	u8 readbuffer[0x40];
	u8 writebuffer[0x20];
	s32 i;

	for (i = 0; i < sizeof(writebuffer); i++) {
		writebuffer[i] = 0x10;
	}

	if (gbpakWrite(device, 0x4000, writebuffer, sizeof(writebuffer)) == 0) {
		return 0;
	}

	if (gbpakRead(device, 0xa000, readbuffer, sizeof(readbuffer)) == 0) {
		return 0;
	}

	return readbuffer[0] & 1;
}
#endif

void pak0f11d118(u8 *arg0, u8 arg1, u32 arg2)
{
	arg0[0] = 2;
	arg0[1] = 0xe4;
	arg0[2] = 0x10;
	arg0[3] = 0;
	arg0[4] = arg1 & 7;
	arg0[5] = (arg1 & 0x3f) + 0x80;

	pak0f11d214(&arg0[6], arg2);
}

void pak0f11d174(s8 device, u8 *arg1)
{
	u8 tmp1;
	s32 tmp2;

	pak0f11d118(arg1, g_Paks[device].unk2b9, func0f14aa70());

	tmp1 = func0f14ad38(device);
	tmp2 = func0f14ad14(device);

	arg1[1] = (arg1[1] & 0xe0) + tmp1;
	arg1[2] = (tmp2 >> 8) & 0xff;
	arg1[3] = tmp2;
}

void pak0f11d214(u8 *arg0, u32 arg1)
{
	const f32 spa8[][4] = {
		{ 128, 148, 220, 255 },
		{ 130, 149, 210, 255 },
		{ 132, 150, 202, 255 },
		{ 134, 150, 196, 255 },
		{ 136, 151, 190, 255 },
		{ 138, 151, 184, 255 },
		{ 139, 152, 178, 245 },
		{ 140, 152, 172, 235 },
		{ 141, 152, 170, 221 },
		{ 142, 152, 168, 208 },
		{ 143, 152, 166, 196 },
		{ 144, 152, 164, 186 },
		{ 146, 152, 161, 177 },
		{ 148, 152, 157, 168 },
		{ 150, 152, 153, 160 },
		{ 152, 152, 152, 152 },
		{ 0,   0,   0,   0   },
	};

	const f32 sp68[][4] = {
		{ 0,  8,  2,  10 },
		{ 12, 4,  14, 6  },
		{ 3,  11, 1,  9  },
		{ 15, 7,  13, 5  },
	};

	const f32 sp28[][4] = {
		{ 0,  14, 3,  13 },
		{ 11, 5,  8,  6  },
		{ 12, 2,  15, 1  },
		{ 7,  9,  4,  10 },
	};

	s32 i;
	s32 j;
	s32 k;

	for (i = 0; i < 3; i++) {
		f32 mult = (spa8[arg1][i + 1] - spa8[arg1][i]) * (1.0f / 16.0f);

		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++) {
				arg0[j * 12 + k * 3 + i] = 0.5f + spa8[arg1][i] + sp28[j][k] * mult;
			}
		}
	}
}

const char var7f1b4adc[] = "Pak_StartCapture -> Failed - Code = %d\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b4b04[] = "Pak_DownloadNextBlockToPackBuffer : eQuality=ekCapQualityHeader, BufferNum=%d\n";
#else
const char var7f1b4b04[] = "Pak_DownloadNextBlockToPackBuffer : eQuality=ekCapQualityHeader, BufferNum=%d";
#endif

const char var7f1b4b54[] = "Pak : Doing Frame - Top    = %d\n";
const char var7f1b4b78[] = "Pak : Doing Frame - Height = %d\n";
const char var7f1b4b9c[] = "Pak : Doing Frame - Bottom = %d\n";

#if VERSION == VERSION_NTSC_1_0
const char var7f1b4b9c_2[] = "Pak %d - PakDamage_UjiWipedMyAss\n";
#endif

#if VERSION < VERSION_NTSC_1_0
const char var7f1aec60nb[] = "Pak %d -> ekPakInitStatusInitMemoryPak1\n";
const char var7f1aec8cnb[] = "Pak %d -> ekPakInitStatusInitMemoryPak2\n";
const char var7f1aecb8nb[] = "Pak %d -> ekPakInitStatusInitMemoryPak3\n";
const char var7f1aece4nb[] = "pak.c";
const char var7f1aececnb[] = "pak.c";
const char var7f1aecf4nb[] = "pak.c";
const char var7f1aecfcnb[] = "pak.c";
#endif

const char var7f1b4bc0[] = "Pak %d - ekPakInitStatusError_CorruptedPak\n";

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b4bec[] = "Pak %d - ekPakInitStatusInitGameBoy_PDGB_Check_Error\n";
#endif

const char var7f1b4c24[] = "Pak %d - ekPakInitStatusError_DamagedPak\n";
const char var7f1b4c50[] = "Pak %d - ekPakInitStatusError_StuffedPak\n";
const char var7f1b4c7c[] = "Pak %d - ekPakInitStatusError_StuffedAndCheckedPak\n";
const char var7f1b4cb0[] = "Pak %d - ekPakInitStatusVoid\n";
const char var7f1b4cd0[] = "Pak %d -> Unhandled Init Status - %d\n";

#if VERSION >= VERSION_NTSC_FINAL
const char var7f1b4cf8[] = "Pak %d - PakDamage_UjiWipedMyAss\n";
#endif

#if VERSION < VERSION_NTSC_1_0
const char var7f1aee04nb[] = "Pak_EEPROM_Init";
#endif

u32 var80075d58 = 0x00000000;
u32 var80075d5c = 0x00000000;

s32 pak0f11d3f8(s8 device)
{
	if (g_Paks[device].type == PAKTYPE_GAMEBOY
			&& (g_Paks[device].unk010 == PAK010_11 || g_Paks[device].unk010 == PAK010_12 || g_Paks[device].unk010 == PAK010_13)) {
		return true;
	}

	return false;
}

bool pak0f11d478(s8 device)
{
	if (g_Paks[device].unk008 == 11) {
		g_Paks[device].unk008 = 1;
		return true;
	}

	return false;
}

bool pak0f11d4dc(s8 device)
{
	if (g_Paks[device].unk008 == 1 || g_Paks[device].unk008 == 0) {
		g_Paks[device].unk008 = 2;
		g_Paks[device].unk270 = 0;
	}

	return false;
}

s32 pak0f11d540(s8 device, s32 arg1)
{
	if (g_Paks[device].unk008 == 1 || g_Paks[device].unk008 == 0) {
		g_Paks[device].unk008 = 4;
		g_Paks[device].unk270 = arg1;
		return true;
	}

	return false;
}

s32 pak0f11d5b0(s8 device)
{
	if (g_Paks[device].unk008 == 1 || g_Paks[device].unk008 == 0) {
		g_Paks[device].unk008 = 4;
		g_Paks[device].unk270 = 1;
		return true;
	}

	return false;
}

void pak0f11d620(s8 device)
{
	if (g_Paks[device].unk010 == PAK010_11) {
		g_Paks[device].unk010 = PAK010_12;
	}
}

#if VERSION >= VERSION_NTSC_1_0
void pak0f11d678(void)
{
	// empty
}
#endif

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak7f1172c8nb
/*  f1172c8:	00047600 */ 	sll	$t6,$a0,0x18
/*  f1172cc:	000e7e03 */ 	sra	$t7,$t6,0x18
/*  f1172d0:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f1172d4:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f1172d8:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f1172dc:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f1172e0:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f1172e4:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f1172e8:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f1172ec:	3c01800a */ 	lui	$at,0x800a
/*  f1172f0:	00380821 */ 	addu	$at,$at,$t8
/*  f1172f4:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f1172f8:	ac206ae8 */ 	sw	$zero,0x6ae8($at)
/*  f1172fc:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f117300:	00001825 */ 	or	$v1,$zero,$zero
/*  f117304:	01e02025 */ 	or	$a0,$t7,$zero
/*  f117308:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f11730c:	27a30048 */ 	addiu	$v1,$sp,0x48
/*  f117310:	27a20028 */ 	addiu	$v0,$sp,0x28
/*  f117314:	04a10003 */ 	bgez	$a1,.NB0f117324
/*  f117318:	00053043 */ 	sra	$a2,$a1,0x1
/*  f11731c:	24a10001 */ 	addiu	$at,$a1,0x1
/*  f117320:	00013043 */ 	sra	$a2,$at,0x1
.NB0f117324:
/*  f117324:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f117328:	1443fffe */ 	bne	$v0,$v1,.NB0f117324
/*  f11732c:	a046ffff */ 	sb	$a2,-0x1($v0)
/*  f117330:	24054000 */ 	addiu	$a1,$zero,0x4000
/*  f117334:	27a60028 */ 	addiu	$a2,$sp,0x28
/*  f117338:	0fc45a3b */ 	jal	gbpakWrite
/*  f11733c:	24070020 */ 	addiu	$a3,$zero,0x20
/*  f117340:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f117344:	27bd0048 */ 	addiu	$sp,$sp,0x48
/*  f117348:	03e00008 */ 	jr	$ra
/*  f11734c:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

bool gbpak0f11d680(s8 device, bool arg1)
{
	u32 offset = 0;
	u16 addr;
	u16 size;

	switch (g_Paks[device].unk00c) {
	case 0:
		offset = 0x1a0;
		size = 0x40;
		arg1 = true;
		break;
	case 1:
		offset = g_Paks[device].unk278 * 0x100 + 0x660;
		size = 0x40;
		break;
	case 2:
		offset = g_Paks[device].unk278 * 0x100 + 0x440;
		size = 0x80;
		break;
	case 3:
		offset = g_Paks[device].unk278 * var80075ccc;
		size = var80075ccc;
		break;
	}

	addr = 0xa000 + (arg1 & 1 ? 0x1000 : 0) + offset;

	if (gbpakRead(device, addr, &g_Paks[device].unk2c4[offset], size) == 0) {
		return false;
	}

	g_Paks[device].unk278++;
	return true;
}

bool pak0f11d7c4(s8 device)
{
	switch (g_Paks[device].unk00c) {
	case 0:
		if (g_Paks[device].unk278 == 1) {
			return true;
		}
		break;
	case 1:
		if (g_Paks[device].unk278 == 4) {
			return true;
		}
		break;
	case 2:
		if (g_Paks[device].unk278 == 8) {
			return true;
		}
		break;
	case 3:
		if (g_Paks[device].unk278 == 0x1000 / var80075ccc) {
			return true;
		}
		break;
	}

	return false;
}

GLOBAL_ASM(
glabel pak0f11d8b4
/*  f11d8b4:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f11d8b8:	afb6001c */ 	sw	$s6,0x1c($sp)
/*  f11d8bc:	afb50018 */ 	sw	$s5,0x18($sp)
/*  f11d8c0:	afb40014 */ 	sw	$s4,0x14($sp)
/*  f11d8c4:	afb30010 */ 	sw	$s3,0x10($sp)
/*  f11d8c8:	afb10008 */ 	sw	$s1,0x8($sp)
/*  f11d8cc:	afb00004 */ 	sw	$s0,0x4($sp)
/*  f11d8d0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f11d8d4:	00808825 */ 	or	$s1,$a0,$zero
/*  f11d8d8:	afb2000c */ 	sw	$s2,0xc($sp)
/*  f11d8dc:	24130008 */ 	addiu	$s3,$zero,0x8
/*  f11d8e0:	24140010 */ 	addiu	$s4,$zero,0x10
/*  f11d8e4:	24150080 */ 	addiu	$s5,$zero,0x80
/*  f11d8e8:	24160080 */ 	addiu	$s6,$zero,0x80
/*  f11d8ec:	00001825 */ 	or	$v1,$zero,$zero
/*  f11d8f0:	00004025 */ 	or	$t0,$zero,$zero
.L0f11d8f4:
/*  f11d8f4:	00032100 */ 	sll	$a0,$v1,0x4
/*  f11d8f8:	00003025 */ 	or	$a2,$zero,$zero
.L0f11d8fc:
/*  f11d8fc:	00002825 */ 	or	$a1,$zero,$zero
/*  f11d900:	01004825 */ 	or	$t1,$t0,$zero
/*  f11d904:	00919021 */ 	addu	$s2,$a0,$s1
.L0f11d908:
/*  f11d908:	000951c0 */ 	sll	$t2,$t1,0x7
/*  f11d90c:	020a5821 */ 	addu	$t3,$s0,$t2
/*  f11d910:	00001025 */ 	or	$v0,$zero,$zero
/*  f11d914:	00c03825 */ 	or	$a3,$a2,$zero
.L0f11d918:
/*  f11d918:	01677021 */ 	addu	$t6,$t3,$a3
/*  f11d91c:	a1c00000 */ 	sb	$zero,0x0($t6)
/*  f11d920:	92580000 */ 	lbu	$t8,0x0($s2)
/*  f11d924:	240f0080 */ 	addiu	$t7,$zero,0x80
/*  f11d928:	004f6007 */ 	srav	$t4,$t7,$v0
/*  f11d92c:	030cc824 */ 	and	$t9,$t8,$t4
/*  f11d930:	17200006 */ 	bnez	$t9,.L0f11d94c
/*  f11d934:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11d938:	01477021 */ 	addu	$t6,$t2,$a3
/*  f11d93c:	01d06821 */ 	addu	$t5,$t6,$s0
/*  f11d940:	91af0000 */ 	lbu	$t7,0x0($t5)
/*  f11d944:	25f80040 */ 	addiu	$t8,$t7,0x40
/*  f11d948:	a1b80000 */ 	sb	$t8,0x0($t5)
.L0f11d94c:
/*  f11d94c:	92590001 */ 	lbu	$t9,0x1($s2)
/*  f11d950:	01477821 */ 	addu	$t7,$t2,$a3
/*  f11d954:	01f06821 */ 	addu	$t5,$t7,$s0
/*  f11d958:	032c7024 */ 	and	$t6,$t9,$t4
/*  f11d95c:	15c00004 */ 	bnez	$t6,.L0f11d970
/*  f11d960:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11d964:	91b80000 */ 	lbu	$t8,0x0($t5)
/*  f11d968:	27190080 */ 	addiu	$t9,$t8,0x80
/*  f11d96c:	a1b90000 */ 	sb	$t9,0x0($t5)
.L0f11d970:
/*  f11d970:	1453ffe9 */ 	bne	$v0,$s3,.L0f11d918
/*  f11d974:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f11d978:	24a50002 */ 	addiu	$a1,$a1,0x2
/*  f11d97c:	25290001 */ 	addiu	$t1,$t1,0x1
/*  f11d980:	14b4ffe1 */ 	bne	$a1,$s4,.L0f11d908
/*  f11d984:	26520002 */ 	addiu	$s2,$s2,0x2
/*  f11d988:	24c60008 */ 	addiu	$a2,$a2,0x8
/*  f11d98c:	14d5ffdb */ 	bne	$a2,$s5,.L0f11d8fc
/*  f11d990:	24840010 */ 	addiu	$a0,$a0,0x10
/*  f11d994:	25080008 */ 	addiu	$t0,$t0,0x8
/*  f11d998:	1516ffd6 */ 	bne	$t0,$s6,.L0f11d8f4
/*  f11d99c:	24630010 */ 	addiu	$v1,$v1,0x10
/*  f11d9a0:	8fb00004 */ 	lw	$s0,0x4($sp)
/*  f11d9a4:	8fb10008 */ 	lw	$s1,0x8($sp)
/*  f11d9a8:	8fb2000c */ 	lw	$s2,0xc($sp)
/*  f11d9ac:	8fb30010 */ 	lw	$s3,0x10($sp)
/*  f11d9b0:	8fb40014 */ 	lw	$s4,0x14($sp)
/*  f11d9b4:	8fb50018 */ 	lw	$s5,0x18($sp)
/*  f11d9b8:	8fb6001c */ 	lw	$s6,0x1c($sp)
/*  f11d9bc:	03e00008 */ 	jr	$ra
/*  f11d9c0:	27bd0020 */ 	addiu	$sp,$sp,0x20
);

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f11d9c4
/*  f11d9c4:	00047600 */ 	sll	$t6,$a0,0x18
/*  f11d9c8:	000e7e03 */ 	sra	$t7,$t6,0x18
/*  f11d9cc:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f11d9d0:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11d9d4:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11d9d8:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11d9dc:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11d9e0:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f11d9e4:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11d9e8:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11d9ec:	3c19800a */ 	lui	$t9,%hi(g_Paks)
/*  f11d9f0:	27392380 */ 	addiu	$t9,$t9,%lo(g_Paks)
/*  f11d9f4:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f11d9f8:	03194021 */ 	addu	$t0,$t8,$t9
/*  f11d9fc:	8d02000c */ 	lw	$v0,0xc($t0)
/*  f11da00:	27bdbfa0 */ 	addiu	$sp,$sp,-16480
/*  f11da04:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f11da08:	00a08025 */ 	or	$s0,$a1,$zero
/*  f11da0c:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f11da10:	afa44060 */ 	sw	$a0,0x4060($sp)
/*  f11da14:	1040000a */ 	beqz	$v0,.L0f11da40
/*  f11da18:	afa7406c */ 	sw	$a3,0x406c($sp)
/*  f11da1c:	24010001 */ 	addiu	$at,$zero,0x1
/*  f11da20:	10410016 */ 	beq	$v0,$at,.L0f11da7c
/*  f11da24:	24010002 */ 	addiu	$at,$zero,0x2
/*  f11da28:	1041002c */ 	beq	$v0,$at,.L0f11dadc
/*  f11da2c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f11da30:	10410042 */ 	beq	$v0,$at,.L0f11db3c
/*  f11da34:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11da38:	10000044 */ 	beqz	$zero,.L0f11db4c
/*  f11da3c:	00000000 */ 	sll	$zero,$zero,0x0
.L0f11da40:
/*  f11da40:	10c00042 */ 	beqz	$a2,.L0f11db4c
/*  f11da44:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11da48:	8d0502c4 */ 	lw	$a1,0x2c4($t0)
/*  f11da4c:	00001025 */ 	or	$v0,$zero,$zero
/*  f11da50:	00c01825 */ 	or	$v1,$a2,$zero
/*  f11da54:	24a401b2 */ 	addiu	$a0,$a1,0x1b2
/*  f11da58:	2405001e */ 	addiu	$a1,$zero,0x1e
.L0f11da5c:
/*  f11da5c:	90890000 */ 	lbu	$t1,0x0($a0)
/*  f11da60:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11da64:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11da68:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f11da6c:	1445fffb */ 	bne	$v0,$a1,.L0f11da5c
/*  f11da70:	a069ffff */ 	sb	$t1,-0x1($v1)
/*  f11da74:	10000035 */ 	beqz	$zero,.L0f11db4c
/*  f11da78:	00000000 */ 	sll	$zero,$zero,0x0
.L0f11da7c:
/*  f11da7c:	12000033 */ 	beqz	$s0,.L0f11db4c
/*  f11da80:	27a50060 */ 	addiu	$a1,$sp,0x60
/*  f11da84:	0fc4762d */ 	jal	pak0f11d8b4
/*  f11da88:	8d0402c4 */ 	lw	$a0,0x2c4($t0)
/*  f11da8c:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f11da90:	00003825 */ 	or	$a3,$zero,$zero
/*  f11da94:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f11da98:	00001025 */ 	or	$v0,$zero,$zero
.L0f11da9c:
/*  f11da9c:	02071821 */ 	addu	$v1,$s0,$a3
/*  f11daa0:	00072882 */ 	srl	$a1,$a3,0x2
.L0f11daa4:
/*  f11daa4:	00025082 */ 	srl	$t2,$v0,0x2
/*  f11daa8:	000a59c0 */ 	sll	$t3,$t2,0x7
/*  f11daac:	00cb6021 */ 	addu	$t4,$a2,$t3
/*  f11dab0:	01856821 */ 	addu	$t5,$t4,$a1
/*  f11dab4:	91ae1830 */ 	lbu	$t6,0x1830($t5)
/*  f11dab8:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11dabc:	24630080 */ 	addiu	$v1,$v1,0x80
/*  f11dac0:	1444fff8 */ 	bne	$v0,$a0,.L0f11daa4
/*  f11dac4:	a06eff80 */ 	sb	$t6,-0x80($v1)
/*  f11dac8:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f11dacc:	54e4fff3 */ 	bnel	$a3,$a0,.L0f11da9c
/*  f11dad0:	00001025 */ 	or	$v0,$zero,$zero
/*  f11dad4:	1000001d */ 	beqz	$zero,.L0f11db4c
/*  f11dad8:	00000000 */ 	sll	$zero,$zero,0x0
.L0f11dadc:
/*  f11dadc:	1200001b */ 	beqz	$s0,.L0f11db4c
/*  f11dae0:	27a50060 */ 	addiu	$a1,$sp,0x60
/*  f11dae4:	0fc4762d */ 	jal	pak0f11d8b4
/*  f11dae8:	8d0402c4 */ 	lw	$a0,0x2c4($t0)
/*  f11daec:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f11daf0:	00003825 */ 	or	$a3,$zero,$zero
/*  f11daf4:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f11daf8:	00001025 */ 	or	$v0,$zero,$zero
.L0f11dafc:
/*  f11dafc:	02071821 */ 	addu	$v1,$s0,$a3
/*  f11db00:	00072842 */ 	srl	$a1,$a3,0x1
.L0f11db04:
/*  f11db04:	00027842 */ 	srl	$t7,$v0,0x1
/*  f11db08:	000fc1c0 */ 	sll	$t8,$t7,0x7
/*  f11db0c:	00d8c821 */ 	addu	$t9,$a2,$t8
/*  f11db10:	03254821 */ 	addu	$t1,$t9,$a1
/*  f11db14:	912a1020 */ 	lbu	$t2,0x1020($t1)
/*  f11db18:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11db1c:	24630080 */ 	addiu	$v1,$v1,0x80
/*  f11db20:	1444fff8 */ 	bne	$v0,$a0,.L0f11db04
/*  f11db24:	a06aff80 */ 	sb	$t2,-0x80($v1)
/*  f11db28:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f11db2c:	54e4fff3 */ 	bnel	$a3,$a0,.L0f11dafc
/*  f11db30:	00001025 */ 	or	$v0,$zero,$zero
/*  f11db34:	10000005 */ 	beqz	$zero,.L0f11db4c
/*  f11db38:	00000000 */ 	sll	$zero,$zero,0x0
.L0f11db3c:
/*  f11db3c:	12000003 */ 	beqz	$s0,.L0f11db4c
/*  f11db40:	02002825 */ 	or	$a1,$s0,$zero
/*  f11db44:	0fc4762d */ 	jal	pak0f11d8b4
/*  f11db48:	8d0402c4 */ 	lw	$a0,0x2c4($t0)
.L0f11db4c:
/*  f11db4c:	12000028 */ 	beqz	$s0,.L0f11dbf0
/*  f11db50:	8fab406c */ 	lw	$t3,0x406c($sp)
/*  f11db54:	11600026 */ 	beqz	$t3,.L0f11dbf0
/*  f11db58:	24080008 */ 	addiu	$t0,$zero,0x8
/*  f11db5c:	24053c00 */ 	addiu	$a1,$zero,0x3c00
/*  f11db60:	24060400 */ 	addiu	$a2,$zero,0x400
/*  f11db64:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f11db68:	00001025 */ 	or	$v0,$zero,$zero
.L0f11db6c:
/*  f11db6c:	00b01821 */ 	addu	$v1,$a1,$s0
.L0f11db70:
/*  f11db70:	906cfc00 */ 	lbu	$t4,-0x400($v1)
/*  f11db74:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11db78:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11db7c:	1444fffc */ 	bne	$v0,$a0,.L0f11db70
/*  f11db80:	a06cffff */ 	sb	$t4,-0x1($v1)
/*  f11db84:	24a5ff80 */ 	addiu	$a1,$a1,-128
/*  f11db88:	00c5082a */ 	slt	$at,$a2,$a1
/*  f11db8c:	5420fff7 */ 	bnezl	$at,.L0f11db6c
/*  f11db90:	00001025 */ 	or	$v0,$zero,$zero
/*  f11db94:	00003825 */ 	or	$a3,$zero,$zero
/*  f11db98:	02003025 */ 	or	$a2,$s0,$zero
.L0f11db9c:
/*  f11db9c:	00001025 */ 	or	$v0,$zero,$zero
/*  f11dba0:	00c01825 */ 	or	$v1,$a2,$zero
.L0f11dba4:
/*  f11dba4:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11dba8:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11dbac:	1444fffd */ 	bne	$v0,$a0,.L0f11dba4
/*  f11dbb0:	a060ffff */ 	sb	$zero,-0x1($v1)
/*  f11dbb4:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f11dbb8:	14e8fff8 */ 	bne	$a3,$t0,.L0f11db9c
/*  f11dbbc:	24c60080 */ 	addiu	$a2,$a2,0x80
/*  f11dbc0:	24053c00 */ 	addiu	$a1,$zero,0x3c00
/*  f11dbc4:	26063c00 */ 	addiu	$a2,$s0,0x3c00
/*  f11dbc8:	24074000 */ 	addiu	$a3,$zero,0x4000
.L0f11dbcc:
/*  f11dbcc:	00001025 */ 	or	$v0,$zero,$zero
/*  f11dbd0:	00c01825 */ 	or	$v1,$a2,$zero
.L0f11dbd4:
/*  f11dbd4:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11dbd8:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f11dbdc:	1444fffd */ 	bne	$v0,$a0,.L0f11dbd4
/*  f11dbe0:	a060ffff */ 	sb	$zero,-0x1($v1)
/*  f11dbe4:	24a50080 */ 	addiu	$a1,$a1,0x80
/*  f11dbe8:	14a7fff8 */ 	bne	$a1,$a3,.L0f11dbcc
/*  f11dbec:	24c60080 */ 	addiu	$a2,$a2,0x80
.L0f11dbf0:
/*  f11dbf0:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f11dbf4:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f11dbf8:	27bd4060 */ 	addiu	$sp,$sp,0x4060
/*  f11dbfc:	03e00008 */ 	jr	$ra
/*  f11dc00:	00000000 */ 	sll	$zero,$zero,0x0
);
#else
GLOBAL_ASM(
glabel pak0f11d9c4
/*  f117684:	00047600 */ 	sll	$t6,$a0,0x18
/*  f117688:	000e7e03 */ 	sra	$t7,$t6,0x18
/*  f11768c:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f117690:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f117694:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f117698:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f11769c:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f1176a0:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f1176a4:	3c19800a */ 	lui	$t9,0x800a
/*  f1176a8:	27396870 */ 	addiu	$t9,$t9,0x6870
/*  f1176ac:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f1176b0:	03194021 */ 	addu	$t0,$t8,$t9
/*  f1176b4:	8d02000c */ 	lw	$v0,0xc($t0)
/*  f1176b8:	27bdbfa0 */ 	addiu	$sp,$sp,-16480
/*  f1176bc:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f1176c0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f1176c4:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f1176c8:	afa44060 */ 	sw	$a0,0x4060($sp)
/*  f1176cc:	1040000a */ 	beqz	$v0,.NB0f1176f8
/*  f1176d0:	afa7406c */ 	sw	$a3,0x406c($sp)
/*  f1176d4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f1176d8:	10410016 */ 	beq	$v0,$at,.NB0f117734
/*  f1176dc:	24010002 */ 	addiu	$at,$zero,0x2
/*  f1176e0:	1041002c */ 	beq	$v0,$at,.NB0f117794
/*  f1176e4:	24010003 */ 	addiu	$at,$zero,0x3
/*  f1176e8:	10410042 */ 	beq	$v0,$at,.NB0f1177f4
/*  f1176ec:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1176f0:	10000044 */ 	beqz	$zero,.NB0f117804
/*  f1176f4:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f1176f8:
/*  f1176f8:	10c00042 */ 	beqz	$a2,.NB0f117804
/*  f1176fc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f117700:	8d0502c4 */ 	lw	$a1,0x2c4($t0)
/*  f117704:	00001025 */ 	or	$v0,$zero,$zero
/*  f117708:	00c01825 */ 	or	$v1,$a2,$zero
/*  f11770c:	24a401b2 */ 	addiu	$a0,$a1,0x1b2
/*  f117710:	2405001e */ 	addiu	$a1,$zero,0x1e
.NB0f117714:
/*  f117714:	90890000 */ 	lbu	$t1,0x0($a0)
/*  f117718:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11771c:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f117720:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f117724:	1445fffb */ 	bne	$v0,$a1,.NB0f117714
/*  f117728:	a069ffff */ 	sb	$t1,-0x1($v1)
/*  f11772c:	10000035 */ 	beqz	$zero,.NB0f117804
/*  f117730:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f117734:
/*  f117734:	12000033 */ 	beqz	$s0,.NB0f117804
/*  f117738:	27a50060 */ 	addiu	$a1,$sp,0x60
/*  f11773c:	0fc45d5d */ 	jal	pak0f11d8b4
/*  f117740:	8d0402c4 */ 	lw	$a0,0x2c4($t0)
/*  f117744:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f117748:	00003825 */ 	or	$a3,$zero,$zero
/*  f11774c:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f117750:	00001025 */ 	or	$v0,$zero,$zero
.NB0f117754:
/*  f117754:	02071821 */ 	addu	$v1,$s0,$a3
/*  f117758:	00072882 */ 	srl	$a1,$a3,0x2
.NB0f11775c:
/*  f11775c:	00025082 */ 	srl	$t2,$v0,0x2
/*  f117760:	000a59c0 */ 	sll	$t3,$t2,0x7
/*  f117764:	00cb6021 */ 	addu	$t4,$a2,$t3
/*  f117768:	01856821 */ 	addu	$t5,$t4,$a1
/*  f11776c:	91ae1830 */ 	lbu	$t6,0x1830($t5)
/*  f117770:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f117774:	24630080 */ 	addiu	$v1,$v1,0x80
/*  f117778:	1444fff8 */ 	bne	$v0,$a0,.NB0f11775c
/*  f11777c:	a06eff80 */ 	sb	$t6,-0x80($v1)
/*  f117780:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f117784:	54e4fff3 */ 	bnel	$a3,$a0,.NB0f117754
/*  f117788:	00001025 */ 	or	$v0,$zero,$zero
/*  f11778c:	1000001d */ 	beqz	$zero,.NB0f117804
/*  f117790:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f117794:
/*  f117794:	1200001b */ 	beqz	$s0,.NB0f117804
/*  f117798:	27a50060 */ 	addiu	$a1,$sp,0x60
/*  f11779c:	0fc45d5d */ 	jal	pak0f11d8b4
/*  f1177a0:	8d0402c4 */ 	lw	$a0,0x2c4($t0)
/*  f1177a4:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f1177a8:	00003825 */ 	or	$a3,$zero,$zero
/*  f1177ac:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f1177b0:	00001025 */ 	or	$v0,$zero,$zero
.NB0f1177b4:
/*  f1177b4:	02071821 */ 	addu	$v1,$s0,$a3
/*  f1177b8:	00072842 */ 	srl	$a1,$a3,0x1
.NB0f1177bc:
/*  f1177bc:	00027842 */ 	srl	$t7,$v0,0x1
/*  f1177c0:	000fc1c0 */ 	sll	$t8,$t7,0x7
/*  f1177c4:	00d8c821 */ 	addu	$t9,$a2,$t8
/*  f1177c8:	03254821 */ 	addu	$t1,$t9,$a1
/*  f1177cc:	912a1020 */ 	lbu	$t2,0x1020($t1)
/*  f1177d0:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f1177d4:	24630080 */ 	addiu	$v1,$v1,0x80
/*  f1177d8:	1444fff8 */ 	bne	$v0,$a0,.NB0f1177bc
/*  f1177dc:	a06aff80 */ 	sb	$t2,-0x80($v1)
/*  f1177e0:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f1177e4:	54e4fff3 */ 	bnel	$a3,$a0,.NB0f1177b4
/*  f1177e8:	00001025 */ 	or	$v0,$zero,$zero
/*  f1177ec:	10000005 */ 	beqz	$zero,.NB0f117804
/*  f1177f0:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f1177f4:
/*  f1177f4:	12000003 */ 	beqz	$s0,.NB0f117804
/*  f1177f8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1177fc:	0fc45d5d */ 	jal	pak0f11d8b4
/*  f117800:	8d0402c4 */ 	lw	$a0,0x2c4($t0)
.NB0f117804:
/*  f117804:	12000028 */ 	beqz	$s0,.NB0f1178a8
/*  f117808:	8fab406c */ 	lw	$t3,0x406c($sp)
/*  f11780c:	11600026 */ 	beqz	$t3,.NB0f1178a8
/*  f117810:	24080008 */ 	addiu	$t0,$zero,0x8
/*  f117814:	24053c00 */ 	addiu	$a1,$zero,0x3c00
/*  f117818:	24060400 */ 	addiu	$a2,$zero,0x400
/*  f11781c:	24040080 */ 	addiu	$a0,$zero,0x80
/*  f117820:	00001025 */ 	or	$v0,$zero,$zero
.NB0f117824:
/*  f117824:	00b01821 */ 	addu	$v1,$a1,$s0
.NB0f117828:
/*  f117828:	906cfc00 */ 	lbu	$t4,-0x400($v1)
/*  f11782c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f117830:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f117834:	1444fffc */ 	bne	$v0,$a0,.NB0f117828
/*  f117838:	a06cffff */ 	sb	$t4,-0x1($v1)
/*  f11783c:	24a5ff80 */ 	addiu	$a1,$a1,-128
/*  f117840:	00c5082a */ 	slt	$at,$a2,$a1
/*  f117844:	5420fff7 */ 	bnezl	$at,.NB0f117824
/*  f117848:	00001025 */ 	or	$v0,$zero,$zero
/*  f11784c:	00003825 */ 	or	$a3,$zero,$zero
/*  f117850:	02003025 */ 	or	$a2,$s0,$zero
.NB0f117854:
/*  f117854:	00001025 */ 	or	$v0,$zero,$zero
/*  f117858:	00c01825 */ 	or	$v1,$a2,$zero
.NB0f11785c:
/*  f11785c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f117860:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f117864:	1444fffd */ 	bne	$v0,$a0,.NB0f11785c
/*  f117868:	a060ffff */ 	sb	$zero,-0x1($v1)
/*  f11786c:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f117870:	14e8fff8 */ 	bne	$a3,$t0,.NB0f117854
/*  f117874:	24c60080 */ 	addiu	$a2,$a2,0x80
/*  f117878:	24053c00 */ 	addiu	$a1,$zero,0x3c00
/*  f11787c:	26063c00 */ 	addiu	$a2,$s0,0x3c00
/*  f117880:	24074000 */ 	addiu	$a3,$zero,0x4000
.NB0f117884:
/*  f117884:	00001025 */ 	or	$v0,$zero,$zero
/*  f117888:	00c01825 */ 	or	$v1,$a2,$zero
.NB0f11788c:
/*  f11788c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f117890:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f117894:	1444fffd */ 	bne	$v0,$a0,.NB0f11788c
/*  f117898:	a060ffff */ 	sb	$zero,-0x1($v1)
/*  f11789c:	24a50080 */ 	addiu	$a1,$a1,0x80
/*  f1178a0:	14a7fff8 */ 	bne	$a1,$a3,.NB0f117884
/*  f1178a4:	24c60080 */ 	addiu	$a2,$a2,0x80
.NB0f1178a8:
/*  f1178a8:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f1178ac:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1178b0:	27bd4060 */ 	addiu	$sp,$sp,0x4060
/*  f1178b4:	03e00008 */ 	jr	$ra
/*  f1178b8:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

#if VERSION >= VERSION_NTSC_1_0
void pakRumble(s32 device, f32 numsecs, s32 onduration, s32 offduration)
{
	if (g_Paks[device].unk010 == PAK010_11
			&& g_Paks[device].type == PAKTYPE_RUMBLE
			&& g_Paks[device].rumblestate != RUMBLESTATE_DISABLED_STOPPING
			&& g_Paks[device].rumblestate != RUMBLESTATE_DISABLED_STOPPED
			&& g_Paks[device].rumblettl < 60 * numsecs) {
		g_Paks[device].rumblestate = RUMBLESTATE_ENABLED_STARTING;
		g_Paks[device].rumblettl = 60 * numsecs;
		g_Paks[device].rumblepulsestopat = onduration;
		g_Paks[device].rumblepulselen = onduration + offduration;
		g_Paks[device].rumblepulsetimer = 0;
	}
}
#else
void pakRumble(s8 device, f32 numsecs, s32 onduration, s32 offduration)
{
	u8 index = g_Vars.playertojoymap[device];

	if (g_Paks[index].unk010 == PAK010_11
			&& g_Paks[index].type == PAKTYPE_RUMBLE
			&& g_Paks[index].rumblestate != RUMBLESTATE_DISABLED_STOPPING
			&& g_Paks[index].rumblestate != RUMBLESTATE_DISABLED_STOPPED
			&& g_Paks[index].rumblettl < 60 * numsecs) {
		g_Paks[index].rumblestate = RUMBLESTATE_ENABLED_STARTING;
		g_Paks[index].rumblettl = 60 * numsecs;
		g_Paks[index].rumblepulsestopat = onduration;
		g_Paks[index].rumblepulselen = onduration + offduration;
		g_Paks[index].rumblepulsetimer = 0;
	}
}
#endif

void pakStopRumbleForAllPaks(bool disablepolling)
{
	s8 i;

	for (i = 0; i < 5; i++) {
		s32 type = g_Paks[i].type;

		if (type);

		if (type != PAKTYPE_MEMORY && type != PAKTYPE_GAMEBOY) {
			joyStopRumble(i, disablepolling);
		}
	}
}

void pakDisableRumbleForPlayer(s8 playernum)
{
	s32 i;
	s32 tmp = playernum;
	s32 contpads[2];

#if VERSION >= VERSION_NTSC_1_0
	joyGetContpadNumsForPlayer(tmp, &contpads[0], &contpads[1]);

	for (i = 0; i < 2; i++) {
		if (contpads[i] >= 0 && g_Paks[contpads[i]].type == PAKTYPE_RUMBLE) {
			g_Paks[contpads[i]].rumblestate = RUMBLESTATE_DISABLED_STOPPING;
			joyStopRumble(contpads[i], true);
		}
	}
#else
	if (g_Paks[playernum].type == PAKTYPE_RUMBLE) {
		g_Paks[playernum].rumblestate = RUMBLESTATE_DISABLED_STOPPING;
		joyStopRumble(playernum, true);
	}
#endif
}

void pakEnableRumbleForPlayer(s8 playernum)
{
	s32 i;
	s32 tmp = playernum;
	s32 contpads[2];

#if VERSION >= VERSION_NTSC_1_0
	joyGetContpadNumsForPlayer(tmp, &contpads[0], &contpads[1]);

	for (i = 0; i < 2; i++) {
		if (contpads[i] >= 0
				&& g_Paks[contpads[i]].type == PAKTYPE_RUMBLE
				&& g_Paks[contpads[i]].rumblestate == RUMBLESTATE_DISABLED_STOPPED) {
			g_Paks[contpads[i]].rumblestate = RUMBLESTATE_ENABLING;
		}
	}
#else
	if (g_Paks[playernum].type == PAKTYPE_RUMBLE
			&& g_Paks[playernum].rumblestate == RUMBLESTATE_DISABLED_STOPPED) {
		g_Paks[playernum].rumblestate = RUMBLESTATE_ENABLING;
	}
#endif
}

void pakDisableRumbleForAllPlayers(void)
{
	s32 i;

#if VERSION >= VERSION_NTSC_1_0
	for (i = 0; i < 4; i++) {
		if (g_Paks[i].type == PAKTYPE_RUMBLE) {
			g_Paks[i].rumblestate = RUMBLESTATE_DISABLED_STOPPING;
			joyStopRumble(i, true);
		}
	}
#else
	for (i = 0; i < 4; i++) {
		pakDisableRumbleForPlayer(i);
	}
#endif
}

void pakEnableRumbleForAllPlayers(void)
{
	s32 i;

#if VERSION >= VERSION_NTSC_FINAL
	for (i = 0; i < 4; i++) {
		if (g_Paks[i].type == PAKTYPE_RUMBLE && g_Paks[i].rumblestate == RUMBLESTATE_DISABLED_STOPPED) {
			g_Paks[i].rumblestate = RUMBLESTATE_ENABLING;
		}
	}
#else
	for (i = 0; i < 4; i++) {
		pakEnableRumbleForPlayer(i);
	}
#endif
}

#if VERSION >= VERSION_NTSC_1_0
s32 pak0f11df84(s32 arg0)
{
	return arg0;
}
#endif

void pakDumpPak(void)
{
	// empty
}

#if VERSION >= VERSION_NTSC_FINAL
void pak0f11df94(s8 device)
{
	switch (g_Paks[device].unk010) {
	case PAK010_00:
		break;
	case PAK010_01:
		g_Paks[device].unk010 = PAK010_00;
		g_Paks[device].unk264++;
		g_Paks[device].unk2b8_07 = false;
		g_Paks[device].type = PAKTYPE_NONE;

		if (var80075d14) {
			menuSetBanner(-1, true);
		}

		func0f14aed0(device);
		break;
	case PAK010_02:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}

		pakProbe(device);
		func0f14aed0(device);
		break;
	case PAK010_03:
		if (g_Vars.paksconnected & (1 << device)) {
			if (device == SAVEDEVICE_GAMEPAK) {
				g_Paks[device].unk010 = PAK010_05;
			} else {
				g_Paks[device].unk010 = PAK010_04;
			}
		} else {
			g_Paks[device].unk010 = PAK010_07;
		}
		break;
	case PAK010_07:
		if (g_Vars.paksconnected & (1 << device)) {
			g_Paks[device].unk010 = PAK010_02;
		}
		break;
	case PAK010_04:
		g_MpPlayerNum = device;

		if (var80075d14) {
			menuSetBanner(MENUBANNER_CHECKINGPAK, true);
		}

		g_Paks[device].unk010 = PAK010_05;
		break;
	case PAK010_05:
		joyDisableCyclicPolling();
		mempakPrepare(device);
		joyEnableCyclicPolling();
		break;
	case PAK010_06:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}

		g_Paks[device].unk010 = PAK010_11;
		break;
	case PAK010_08:
		if (func0f14aea0(device)) {
			g_Paks[device].unk010 = PAK010_09;
		}
		break;
	case PAK010_09:
		g_Paks[device].unk008 = 0;
		g_Paks[device].unk010 = PAK010_10;
		break;
	case PAK010_10:
		g_Paks[device].unk010 = PAK010_24;
		break;
	case PAK010_24:
		g_Paks[device].unk010 = PAK010_25;
		break;
	case PAK010_25:
		g_Paks[device].unk010 = PAK010_11;
		break;
	case PAK010_12:
		g_Paks[device].unk010 = PAK010_11;
		break;
	case PAK010_15:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}
		if ((g_Vars.paksconnected & (1 << device)) && func0f0fd1f4(device, 1)) {
			func0f0fd320(device, 1);
			g_Paks[device].unk010 = PAK010_20;
		}
		break;
	case PAK010_26:
		if (func0f0fd1f4(device, 3)) {
			func0f0fd320(device, 3);
			g_Paks[device].unk010 = PAK010_27;
		}
		break;
	case PAK010_27:
		g_Paks[device].unk010 = PAK010_11;
		break;
	case PAK010_14:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}
		if (((g_Vars.paksconnected & (1 << device))) && func0f0fd1f4(device, 2)) {
			func0f0fd320(device, 2);
			g_Paks[device].unk010 = PAK010_19;
		}
		break;
	case PAK010_16:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}
		if ((g_Vars.paksconnected & (1 << device)) && func0f0fd1f4(device, 0)) {
			func0f0fd320(device, 0);
			g_Paks[device].unk010 = PAK010_21;
		}
		break;
	case PAK010_21:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}
		break;
	case PAK010_22:
		if (var80075d14) {
			menuSetBanner(-1, true);
		}
		break;
	}

	if (g_Paks[device].unk2b8_07) {
		if (var80075d14) {
			menuSetBanner(-1, true);
		}

		if (func0f0fd1f4(device, 4)) {
			func0f0fd320(device, 4);
			g_Paks[device].unk2b8_07 = false;
		}
	}
}
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak0f11df94
.late_rodata
glabel var7f1b4f6c
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4f70
.word pak0f11df94+0xd8 # f11dde8
glabel var7f1b4f74
.word pak0f11df94+0x110 # f11de20
glabel var7f1b4f78
.word pak0f11df94+0x140 # f11de50
glabel var7f1b4f7c
.word pak0f11df94+0x1b4 # f11dec4
glabel var7f1b4f80
.word pak0f11df94+0x1ec # f11defc
glabel var7f1b4f84
.word pak0f11df94+0x20c # f11df1c
glabel var7f1b4f88
.word pak0f11df94+0x18c # f11de9c
glabel var7f1b4f8c
.word pak0f11df94+0x238 # f11df48
glabel var7f1b4f90
.word pak0f11df94+0x258 # f11df68
glabel var7f1b4f94
.word pak0f11df94+0x268 # f11df78
glabel var7f1b4f98
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4f9c
.word pak0f11df94+0x28c # f11df9c
glabel var7f1b4fa0
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4fa4
.word pak0f11df94+0x34c # f11e05c
glabel var7f1b4fa8
.word pak0f11df94+0x298 # f11dfa8
glabel var7f1b4fac
.word pak0f11df94+0x3c0 # f11e0d0
glabel var7f1b4fb0
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4fb4
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4fb8
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4fbc
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4fc0
.word pak0f11df94+0x430 # f11e140
glabel var7f1b4fc4
.word pak0f11df94+0x44c # f11e15c
glabel var7f1b4fc8
.word pak0f11df94+0x464 # f11e174
glabel var7f1b4fcc
.word pak0f11df94+0x274 # f11df84
glabel var7f1b4fd0
.word pak0f11df94+0x280 # f11df90
glabel var7f1b4fd4
.word pak0f11df94+0x308 # f11e018
glabel var7f1b4fd8
.word pak0f11df94+0x340 # f11e050
.text
/*  f11dd10:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*  f11dd14:	afa40020 */ 	sw	$a0,0x20($sp)
/*  f11dd18:	83ae0023 */ 	lb	$t6,0x23($sp)
/*  f11dd1c:	3c18800a */ 	lui	$t8,%hi(g_Paks)
/*  f11dd20:	27182380 */ 	addiu	$t8,$t8,%lo(g_Paks)
/*  f11dd24:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f11dd28:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11dd2c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11dd30:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11dd34:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11dd38:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f11dd3c:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11dd40:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f11dd44:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f11dd48:	01f81821 */ 	addu	$v1,$t7,$t8
/*  f11dd4c:	8c7902b8 */ 	lw	$t9,0x2b8($v1)
/*  f11dd50:	3c068007 */ 	lui	$a2,%hi(var80075d14)
/*  f11dd54:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f11dd58:	00194980 */ 	sll	$t1,$t9,0x6
/*  f11dd5c:	05210017 */ 	bgez	$t1,.L0f11ddbc
/*  f11dd60:	24c65d14 */ 	addiu	$a2,$a2,%lo(var80075d14)
/*  f11dd64:	8cca0000 */ 	lw	$t2,0x0($a2)
/*  f11dd68:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11dd6c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11dd70:	51400005 */ 	beqzl	$t2,.L0f11dd88
/*  f11dd74:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11dd78:	0fc3c320 */ 	jal	menuSetBanner
/*  f11dd7c:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11dd80:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11dd84:	83a40023 */ 	lb	$a0,0x23($sp)
.L0f11dd88:
/*  f11dd88:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f11dd8c:	0fc3f475 */ 	jal	func0f0fd1f4
/*  f11dd90:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11dd94:	10400009 */ 	beqz	$v0,.L0f11ddbc
/*  f11dd98:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11dd9c:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11dda0:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f11dda4:	0fc3f4c0 */ 	jal	func0f0fd320
/*  f11dda8:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11ddac:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11ddb0:	906b02b8 */ 	lbu	$t3,0x2b8($v1)
/*  f11ddb4:	316cfffd */ 	andi	$t4,$t3,0xfffd
/*  f11ddb8:	a06c02b8 */ 	sb	$t4,0x2b8($v1)
.L0f11ddbc:
/*  f11ddbc:	8c6d0010 */ 	lw	$t5,0x10($v1)
/*  f11ddc0:	3c068007 */ 	lui	$a2,%hi(var80075d14)
/*  f11ddc4:	24c65d14 */ 	addiu	$a2,$a2,%lo(var80075d14)
/*  f11ddc8:	2da1001c */ 	sltiu	$at,$t5,0x1c
/*  f11ddcc:	102000e9 */ 	beqz	$at,.L0f11e174
/*  f11ddd0:	000d6880 */ 	sll	$t5,$t5,0x2
/*  f11ddd4:	3c017f1b */ 	lui	$at,0x7f1b
/*  f11ddd8:	002d0821 */ 	addu	$at,$at,$t5
/*  f11dddc:	8c2d4df8 */ 	lw	$t5,0x4df8($at)
/*  f11dde0:	01a00008 */ 	jr	$t5
/*  f11dde4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11dde8:	8c6e0264 */ 	lw	$t6,0x264($v1)
/*  f11ddec:	8cd80000 */ 	lw	$t8,0x0($a2)
/*  f11ddf0:	ac600010 */ 	sw	$zero,0x10($v1)
/*  f11ddf4:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*  f11ddf8:	ac6f0264 */ 	sw	$t7,0x264($v1)
/*  f11ddfc:	13000004 */ 	beqz	$t8,.L0f11de10
/*  f11de00:	ac600000 */ 	sw	$zero,0x0($v1)
/*  f11de04:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11de08:	0fc3c320 */ 	jal	menuSetBanner
/*  f11de0c:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f11de10:
/*  f11de10:	0fc52b28 */ 	jal	func0f14aed0
/*  f11de14:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11de18:	100000d7 */ 	beqz	$zero,.L0f11e178
/*  f11de1c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11de20:	8cd90000 */ 	lw	$t9,0x0($a2)
/*  f11de24:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11de28:	13200003 */ 	beqz	$t9,.L0f11de38
/*  f11de2c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11de30:	0fc3c320 */ 	jal	menuSetBanner
/*  f11de34:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f11de38:
/*  f11de38:	0fc46a7f */ 	jal	pakProbe
/*  f11de3c:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11de40:	0fc52b28 */ 	jal	func0f14aed0
/*  f11de44:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11de48:	100000cb */ 	beqz	$zero,.L0f11e178
/*  f11de4c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11de50:	83a90023 */ 	lb	$t1,0x23($sp)
/*  f11de54:	3c08800a */ 	lui	$t0,%hi(g_Vars+0x4d0)
/*  f11de58:	9108a490 */ 	lbu	$t0,%lo(g_Vars+0x4d0)($t0)
/*  f11de5c:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f11de60:	012a5804 */ 	sllv	$t3,$t2,$t1
/*  f11de64:	010b6024 */ 	and	$t4,$t0,$t3
/*  f11de68:	1180000a */ 	beqz	$t4,.L0f11de94
/*  f11de6c:	24180007 */ 	addiu	$t8,$zero,0x7
/*  f11de70:	3c0d800a */ 	lui	$t5,%hi(g_Paks+0xb30)
/*  f11de74:	25ad2eb0 */ 	addiu	$t5,$t5,%lo(g_Paks+0xb30)
/*  f11de78:	146d0004 */ 	bne	$v1,$t5,.L0f11de8c
/*  f11de7c:	240f0004 */ 	addiu	$t7,$zero,0x4
/*  f11de80:	240e0005 */ 	addiu	$t6,$zero,0x5
/*  f11de84:	100000bb */ 	beqz	$zero,.L0f11e174
/*  f11de88:	ac6e0010 */ 	sw	$t6,0x10($v1)
.L0f11de8c:
/*  f11de8c:	100000b9 */ 	beqz	$zero,.L0f11e174
/*  f11de90:	ac6f0010 */ 	sw	$t7,0x10($v1)
.L0f11de94:
/*  f11de94:	100000b7 */ 	beqz	$zero,.L0f11e174
/*  f11de98:	ac780010 */ 	sw	$t8,0x10($v1)
/*  f11de9c:	83aa0023 */ 	lb	$t2,0x23($sp)
/*  f11dea0:	3c19800a */ 	lui	$t9,%hi(g_Vars+0x4d0)
/*  f11dea4:	9339a490 */ 	lbu	$t9,%lo(g_Vars+0x4d0)($t9)
/*  f11dea8:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f11deac:	01494004 */ 	sllv	$t0,$t1,$t2
/*  f11deb0:	03285824 */ 	and	$t3,$t9,$t0
/*  f11deb4:	116000af */ 	beqz	$t3,.L0f11e174
/*  f11deb8:	240c0002 */ 	addiu	$t4,$zero,0x2
/*  f11debc:	100000ad */ 	beqz	$zero,.L0f11e174
/*  f11dec0:	ac6c0010 */ 	sw	$t4,0x10($v1)
/*  f11dec4:	83ad0023 */ 	lb	$t5,0x23($sp)
/*  f11dec8:	3c018007 */ 	lui	$at,%hi(g_MpPlayerNum)
/*  f11decc:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f11ded0:	ac2d1448 */ 	sw	$t5,%lo(g_MpPlayerNum)($at)
/*  f11ded4:	8cce0000 */ 	lw	$t6,0x0($a2)
/*  f11ded8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11dedc:	51c00005 */ 	beqzl	$t6,.L0f11def4
/*  f11dee0:	240f0005 */ 	addiu	$t7,$zero,0x5
/*  f11dee4:	0fc3c320 */ 	jal	menuSetBanner
/*  f11dee8:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11deec:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11def0:	240f0005 */ 	addiu	$t7,$zero,0x5
.L0f11def4:
/*  f11def4:	1000009f */ 	beqz	$zero,.L0f11e174
/*  f11def8:	ac6f0010 */ 	sw	$t7,0x10($v1)
/*  f11defc:	0c00543a */ 	jal	joyDisableCyclicPolling
/*  f11df00:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11df04:	0fc4699d */ 	jal	mempakPrepare
/*  f11df08:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11df0c:	0c005451 */ 	jal	joyEnableCyclicPolling
/*  f11df10:	00000000 */ 	sll	$zero,$zero,0x0
/*  f11df14:	10000098 */ 	beqz	$zero,.L0f11e178
/*  f11df18:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11df1c:	8cd80000 */ 	lw	$t8,0x0($a2)
/*  f11df20:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11df24:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11df28:	53000005 */ 	beqzl	$t8,.L0f11df40
/*  f11df2c:	2409000b */ 	addiu	$t1,$zero,0xb
/*  f11df30:	0fc3c320 */ 	jal	menuSetBanner
/*  f11df34:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11df38:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11df3c:	2409000b */ 	addiu	$t1,$zero,0xb
.L0f11df40:
/*  f11df40:	1000008c */ 	beqz	$zero,.L0f11e174
/*  f11df44:	ac690010 */ 	sw	$t1,0x10($v1)
/*  f11df48:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11df4c:	0fc52b1c */ 	jal	func0f14aea0
/*  f11df50:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11df54:	10400087 */ 	beqz	$v0,.L0f11e174
/*  f11df58:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11df5c:	240a0009 */ 	addiu	$t2,$zero,0x9
/*  f11df60:	10000084 */ 	beqz	$zero,.L0f11e174
/*  f11df64:	ac6a0010 */ 	sw	$t2,0x10($v1)
/*  f11df68:	2419000a */ 	addiu	$t9,$zero,0xa
/*  f11df6c:	ac600008 */ 	sw	$zero,0x8($v1)
/*  f11df70:	10000080 */ 	beqz	$zero,.L0f11e174
/*  f11df74:	ac790010 */ 	sw	$t9,0x10($v1)
/*  f11df78:	24080018 */ 	addiu	$t0,$zero,0x18
/*  f11df7c:	1000007d */ 	beqz	$zero,.L0f11e174
/*  f11df80:	ac680010 */ 	sw	$t0,0x10($v1)
/*  f11df84:	240b0019 */ 	addiu	$t3,$zero,0x19
/*  f11df88:	1000007a */ 	beqz	$zero,.L0f11e174
/*  f11df8c:	ac6b0010 */ 	sw	$t3,0x10($v1)
/*  f11df90:	240c000b */ 	addiu	$t4,$zero,0xb
/*  f11df94:	10000077 */ 	beqz	$zero,.L0f11e174
/*  f11df98:	ac6c0010 */ 	sw	$t4,0x10($v1)
/*  f11df9c:	240d000b */ 	addiu	$t5,$zero,0xb
/*  f11dfa0:	10000074 */ 	beqz	$zero,.L0f11e174
/*  f11dfa4:	ac6d0010 */ 	sw	$t5,0x10($v1)
/*  f11dfa8:	8cce0000 */ 	lw	$t6,0x0($a2)
/*  f11dfac:	11c00005 */ 	beqz	$t6,.L0f11dfc4
/*  f11dfb0:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11dfb4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11dfb8:	0fc3c320 */ 	jal	menuSetBanner
/*  f11dfbc:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11dfc0:	8fa3001c */ 	lw	$v1,0x1c($sp)
.L0f11dfc4:
/*  f11dfc4:	83b80023 */ 	lb	$t8,0x23($sp)
/*  f11dfc8:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x4d0)
/*  f11dfcc:	91efa490 */ 	lbu	$t7,%lo(g_Vars+0x4d0)($t7)
/*  f11dfd0:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f11dfd4:	03095004 */ 	sllv	$t2,$t1,$t8
/*  f11dfd8:	01eac824 */ 	and	$t9,$t7,$t2
/*  f11dfdc:	13200065 */ 	beqz	$t9,.L0f11e174
/*  f11dfe0:	03002025 */ 	or	$a0,$t8,$zero
/*  f11dfe4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11dfe8:	0fc3f475 */ 	jal	func0f0fd1f4
/*  f11dfec:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11dff0:	10400060 */ 	beqz	$v0,.L0f11e174
/*  f11dff4:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11dff8:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11dffc:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11e000:	0fc3f4c0 */ 	jal	func0f0fd320
/*  f11e004:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e008:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e00c:	24080014 */ 	addiu	$t0,$zero,0x14
/*  f11e010:	10000058 */ 	beqz	$zero,.L0f11e174
/*  f11e014:	ac680010 */ 	sw	$t0,0x10($v1)
/*  f11e018:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11e01c:	24050003 */ 	addiu	$a1,$zero,0x3
/*  f11e020:	0fc3f475 */ 	jal	func0f0fd1f4
/*  f11e024:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e028:	10400052 */ 	beqz	$v0,.L0f11e174
/*  f11e02c:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e030:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11e034:	24050003 */ 	addiu	$a1,$zero,0x3
/*  f11e038:	0fc3f4c0 */ 	jal	func0f0fd320
/*  f11e03c:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e040:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e044:	240b001b */ 	addiu	$t3,$zero,0x1b
/*  f11e048:	1000004a */ 	beqz	$zero,.L0f11e174
/*  f11e04c:	ac6b0010 */ 	sw	$t3,0x10($v1)
/*  f11e050:	240c000b */ 	addiu	$t4,$zero,0xb
/*  f11e054:	10000047 */ 	beqz	$zero,.L0f11e174
/*  f11e058:	ac6c0010 */ 	sw	$t4,0x10($v1)
/*  f11e05c:	8ccd0000 */ 	lw	$t5,0x0($a2)
/*  f11e060:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11e064:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11e068:	51a00005 */ 	beqzl	$t5,.L0f11e080
/*  f11e06c:	83a90023 */ 	lb	$t1,0x23($sp)
/*  f11e070:	0fc3c320 */ 	jal	menuSetBanner
/*  f11e074:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e078:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e07c:	83a90023 */ 	lb	$t1,0x23($sp)
.L0f11e080:
/*  f11e080:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x4d0)
/*  f11e084:	91cea490 */ 	lbu	$t6,%lo(g_Vars+0x4d0)($t6)
/*  f11e088:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f11e08c:	012f5004 */ 	sllv	$t2,$t7,$t1
/*  f11e090:	01cac824 */ 	and	$t9,$t6,$t2
/*  f11e094:	13200037 */ 	beqz	$t9,.L0f11e174
/*  f11e098:	01202025 */ 	or	$a0,$t1,$zero
/*  f11e09c:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f11e0a0:	0fc3f475 */ 	jal	func0f0fd1f4
/*  f11e0a4:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e0a8:	10400032 */ 	beqz	$v0,.L0f11e174
/*  f11e0ac:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e0b0:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11e0b4:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f11e0b8:	0fc3f4c0 */ 	jal	func0f0fd320
/*  f11e0bc:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e0c0:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e0c4:	24180013 */ 	addiu	$t8,$zero,0x13
/*  f11e0c8:	1000002a */ 	beqz	$zero,.L0f11e174
/*  f11e0cc:	ac780010 */ 	sw	$t8,0x10($v1)
/*  f11e0d0:	8cc80000 */ 	lw	$t0,0x0($a2)
/*  f11e0d4:	11000005 */ 	beqz	$t0,.L0f11e0ec
/*  f11e0d8:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11e0dc:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11e0e0:	0fc3c320 */ 	jal	menuSetBanner
/*  f11e0e4:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e0e8:	8fa3001c */ 	lw	$v1,0x1c($sp)
.L0f11e0ec:
/*  f11e0ec:	83ac0023 */ 	lb	$t4,0x23($sp)
/*  f11e0f0:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x4d0)
/*  f11e0f4:	916ba490 */ 	lbu	$t3,%lo(g_Vars+0x4d0)($t3)
/*  f11e0f8:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f11e0fc:	018d7804 */ 	sllv	$t7,$t5,$t4
/*  f11e100:	016f7024 */ 	and	$t6,$t3,$t7
/*  f11e104:	11c0001b */ 	beqz	$t6,.L0f11e174
/*  f11e108:	01802025 */ 	or	$a0,$t4,$zero
/*  f11e10c:	00002825 */ 	or	$a1,$zero,$zero
/*  f11e110:	0fc3f475 */ 	jal	func0f0fd1f4
/*  f11e114:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e118:	10400016 */ 	beqz	$v0,.L0f11e174
/*  f11e11c:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e120:	83a40023 */ 	lb	$a0,0x23($sp)
/*  f11e124:	00002825 */ 	or	$a1,$zero,$zero
/*  f11e128:	0fc3f4c0 */ 	jal	func0f0fd320
/*  f11e12c:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f11e130:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f11e134:	240a0015 */ 	addiu	$t2,$zero,0x15
/*  f11e138:	1000000e */ 	beqz	$zero,.L0f11e174
/*  f11e13c:	ac6a0010 */ 	sw	$t2,0x10($v1)
/*  f11e140:	8cd90000 */ 	lw	$t9,0x0($a2)
/*  f11e144:	1320000b */ 	beqz	$t9,.L0f11e174
/*  f11e148:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11e14c:	0fc3c320 */ 	jal	menuSetBanner
/*  f11e150:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11e154:	10000008 */ 	beqz	$zero,.L0f11e178
/*  f11e158:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11e15c:	8cc90000 */ 	lw	$t1,0x0($a2)
/*  f11e160:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f11e164:	51200004 */ 	beqzl	$t1,.L0f11e178
/*  f11e168:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11e16c:	0fc3c320 */ 	jal	menuSetBanner
/*  f11e170:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f11e174:
/*  f11e174:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f11e178:
/*  f11e178:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*  f11e17c:	03e00008 */ 	jr	$ra
/*  f11e180:	00000000 */ 	sll	$zero,$zero,0x0
);
#else
GLOBAL_ASM(
glabel pak0f11df94
.late_rodata
glabel var7f1af100nb
.word pak0f11df94+0x404
glabel var7f1af104nb
.word pak0f11df94+0x064
glabel var7f1af108nb
.word pak0f11df94+0x098
glabel var7f1af10cnb
.word pak0f11df94+0x0bc
glabel var7f1af110nb
.word pak0f11df94+0x140
glabel var7f1af114nb
.word pak0f11df94+0x168
glabel var7f1af118nb
.word pak0f11df94+0x180
glabel var7f1af11cnb
.word pak0f11df94+0x110
glabel var7f1af120nb
.word pak0f11df94+0x1a0
glabel var7f1af124nb
.word pak0f11df94+0x1c0
glabel var7f1af128nb
.word pak0f11df94+0x278
glabel var7f1af12cnb
.word pak0f11df94+0x404
glabel var7f1af130nb
.word pak0f11df94+0x29c
glabel var7f1af134nb
.word pak0f11df94+0x404
glabel var7f1af138nb
.word pak0f11df94+0x34c
glabel var7f1af13cnb
.word pak0f11df94+0x300
glabel var7f1af140nb
.word pak0f11df94+0x398
glabel var7f1af144nb
.word pak0f11df94+0x404
glabel var7f1af148nb
.word pak0f11df94+0x404
glabel var7f1af14cnb
.word pak0f11df94+0x404
glabel var7f1af150nb
.word pak0f11df94+0x404
glabel var7f1af154nb
.word pak0f11df94+0x3e4
glabel var7f1af158nb
.word pak0f11df94+0x3f8
glabel var7f1af15cnb
.word pak0f11df94+0x404
glabel var7f1af160nb
.word pak0f11df94+0x284
glabel var7f1af164nb
.word pak0f11df94+0x290
.text
/*  f117b80:	00043600 */ 	sll	$a2,$a0,0x18
/*  f117b84:	00067603 */ 	sra	$t6,$a2,0x18
/*  f117b88:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f117b8c:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f117b90:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f117b94:	01ee7823 */ 	subu	$t7,$t7,$t6
/*  f117b98:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f117b9c:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f117ba0:	3c18800a */ 	lui	$t8,0x800a
/*  f117ba4:	27186870 */ 	addiu	$t8,$t8,0x6870
/*  f117ba8:	000f78c0 */ 	sll	$t7,$t7,0x3
/*  f117bac:	01f81821 */ 	addu	$v1,$t7,$t8
/*  f117bb0:	8c790010 */ 	lw	$t9,0x10($v1)
/*  f117bb4:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f117bb8:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f117bbc:	2f21001a */ 	sltiu	$at,$t9,0x1a
/*  f117bc0:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f117bc4:	102000ef */ 	beqz	$at,.NB0f117f84
/*  f117bc8:	01c03025 */ 	or	$a2,$t6,$zero
/*  f117bcc:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f117bd0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f117bd4:	00390821 */ 	addu	$at,$at,$t9
/*  f117bd8:	8c39f100 */ 	lw	$t9,-0xf00($at)
/*  f117bdc:	03200008 */ 	jr	$t9
/*  f117be0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f117be4:	8c680264 */ 	lw	$t0,0x264($v1)
/*  f117be8:	ac600010 */ 	sw	$zero,0x10($v1)
/*  f117bec:	ac600000 */ 	sw	$zero,0x0($v1)
/*  f117bf0:	25090001 */ 	addiu	$t1,$t0,0x1
/*  f117bf4:	ac690264 */ 	sw	$t1,0x264($v1)
/*  f117bf8:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117bfc:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117c00:	0fc3b669 */ 	jal	menuSetBanner
/*  f117c04:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117c08:	0fc515a8 */ 	jal	func0f14aed0
/*  f117c0c:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117c10:	100000dd */ 	beqz	$zero,.NB0f117f88
/*  f117c14:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f117c18:	00062600 */ 	sll	$a0,$a2,0x18
/*  f117c1c:	00045603 */ 	sra	$t2,$a0,0x18
/*  f117c20:	01402025 */ 	or	$a0,$t2,$zero
/*  f117c24:	0fc45375 */ 	jal	pak0f114dd4nb
/*  f117c28:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117c2c:	0fc515a8 */ 	jal	func0f14aed0
/*  f117c30:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117c34:	100000d4 */ 	beqz	$zero,.NB0f117f88
/*  f117c38:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f117c3c:	3c02800a */ 	lui	$v0,0x800a
/*  f117c40:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f117c44:	904b04d1 */ 	lbu	$t3,0x4d1($v0)
/*  f117c48:	904c04d0 */ 	lbu	$t4,0x4d0($v0)
/*  f117c4c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f117c50:	00ce7804 */ 	sllv	$t7,$t6,$a2
/*  f117c54:	016c6825 */ 	or	$t5,$t3,$t4
/*  f117c58:	01afc024 */ 	and	$t8,$t5,$t7
/*  f117c5c:	1300000a */ 	beqz	$t8,.NB0f117c88
/*  f117c60:	240a0007 */ 	addiu	$t2,$zero,0x7
/*  f117c64:	3c19800a */ 	lui	$t9,0x800a
/*  f117c68:	27397390 */ 	addiu	$t9,$t9,0x7390
/*  f117c6c:	14790004 */ 	bne	$v1,$t9,.NB0f117c80
/*  f117c70:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f117c74:	24080005 */ 	addiu	$t0,$zero,0x5
/*  f117c78:	100000c2 */ 	beqz	$zero,.NB0f117f84
/*  f117c7c:	ac680010 */ 	sw	$t0,0x10($v1)
.NB0f117c80:
/*  f117c80:	100000c0 */ 	beqz	$zero,.NB0f117f84
/*  f117c84:	ac690010 */ 	sw	$t1,0x10($v1)
.NB0f117c88:
/*  f117c88:	100000be */ 	beqz	$zero,.NB0f117f84
/*  f117c8c:	ac6a0010 */ 	sw	$t2,0x10($v1)
/*  f117c90:	3c02800a */ 	lui	$v0,0x800a
/*  f117c94:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f117c98:	904b04d1 */ 	lbu	$t3,0x4d1($v0)
/*  f117c9c:	904c04d0 */ 	lbu	$t4,0x4d0($v0)
/*  f117ca0:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f117ca4:	00cd7804 */ 	sllv	$t7,$t5,$a2
/*  f117ca8:	016c7025 */ 	or	$t6,$t3,$t4
/*  f117cac:	01cfc024 */ 	and	$t8,$t6,$t7
/*  f117cb0:	130000b4 */ 	beqz	$t8,.NB0f117f84
/*  f117cb4:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f117cb8:	100000b2 */ 	beqz	$zero,.NB0f117f84
/*  f117cbc:	ac790010 */ 	sw	$t9,0x10($v1)
/*  f117cc0:	3c018007 */ 	lui	$at,0x8007
/*  f117cc4:	ac263af0 */ 	sw	$a2,0x3af0($at)
/*  f117cc8:	24040007 */ 	addiu	$a0,$zero,0x7
/*  f117ccc:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117cd0:	0fc3b669 */ 	jal	menuSetBanner
/*  f117cd4:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117cd8:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117cdc:	24080005 */ 	addiu	$t0,$zero,0x5
/*  f117ce0:	100000a8 */ 	beqz	$zero,.NB0f117f84
/*  f117ce4:	ac680010 */ 	sw	$t0,0x10($v1)
/*  f117ce8:	00062600 */ 	sll	$a0,$a2,0x18
/*  f117cec:	00044e03 */ 	sra	$t1,$a0,0x18
/*  f117cf0:	0fc45232 */ 	jal	mempakPrepare
/*  f117cf4:	01202025 */ 	or	$a0,$t1,$zero
/*  f117cf8:	100000a3 */ 	beqz	$zero,.NB0f117f88
/*  f117cfc:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f117d00:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117d04:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117d08:	0fc3b669 */ 	jal	menuSetBanner
/*  f117d0c:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117d10:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117d14:	240a000b */ 	addiu	$t2,$zero,0xb
/*  f117d18:	1000009a */ 	beqz	$zero,.NB0f117f84
/*  f117d1c:	ac6a0010 */ 	sw	$t2,0x10($v1)
/*  f117d20:	00c02025 */ 	or	$a0,$a2,$zero
/*  f117d24:	0fc5159c */ 	jal	func0f14aea0
/*  f117d28:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117d2c:	10400095 */ 	beqz	$v0,.NB0f117f84
/*  f117d30:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117d34:	240b0009 */ 	addiu	$t3,$zero,0x9
/*  f117d38:	10000092 */ 	beqz	$zero,.NB0f117f84
/*  f117d3c:	ac6b0010 */ 	sw	$t3,0x10($v1)
/*  f117d40:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f117d44:	24a5ece4 */ 	addiu	$a1,$a1,-4892
/*  f117d48:	2404171a */ 	addiu	$a0,$zero,0x171a
/*  f117d4c:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117d50:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f117d54:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117d58:	83a6002b */ 	lb	$a2,0x2b($sp)
/*  f117d5c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f117d60:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117d64:	14c10003 */ 	bne	$a2,$at,.NB0f117d74
/*  f117d68:	3c04800a */ 	lui	$a0,0x800a
/*  f117d6c:	10000009 */ 	beqz	$zero,.NB0f117d94
/*  f117d70:	00002825 */ 	or	$a1,$zero,$zero
.NB0f117d74:
/*  f117d74:	00066080 */ 	sll	$t4,$a2,0x2
/*  f117d78:	01866023 */ 	subu	$t4,$t4,$a2
/*  f117d7c:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f117d80:	01866021 */ 	addu	$t4,$t4,$a2
/*  f117d84:	3c0d800a */ 	lui	$t5,0x800a
/*  f117d88:	25ad7658 */ 	addiu	$t5,$t5,0x7658
/*  f117d8c:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f117d90:	018d2821 */ 	addu	$a1,$t4,$t5
.NB0f117d94:
/*  f117d94:	2484e5d8 */ 	addiu	$a0,$a0,-6696
/*  f117d98:	0c001890 */ 	jal	osGbpakInit
/*  f117d9c:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117da0:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f117da4:	24a5ecec */ 	addiu	$a1,$a1,-4884
/*  f117da8:	2404171c */ 	addiu	$a0,$zero,0x171c
/*  f117dac:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f117db0:	afa20024 */ 	sw	$v0,0x24($sp)
/*  f117db4:	8fa60024 */ 	lw	$a2,0x24($sp)
/*  f117db8:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117dbc:	240e0003 */ 	addiu	$t6,$zero,0x3
/*  f117dc0:	14c00006 */ 	bnez	$a2,.NB0f117ddc
/*  f117dc4:	00c02025 */ 	or	$a0,$a2,$zero
/*  f117dc8:	240f000a */ 	addiu	$t7,$zero,0xa
/*  f117dcc:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f117dd0:	ac600008 */ 	sw	$zero,0x8($v1)
/*  f117dd4:	1000006b */ 	beqz	$zero,.NB0f117f84
/*  f117dd8:	ac6f0010 */ 	sw	$t7,0x10($v1)
.NB0f117ddc:
/*  f117ddc:	0fc459d4 */ 	jal	gbpakHandleError
/*  f117de0:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117de4:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117de8:	24180004 */ 	addiu	$t8,$zero,0x4
/*  f117dec:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f117df0:	10000064 */ 	beqz	$zero,.NB0f117f84
/*  f117df4:	ac600010 */ 	sw	$zero,0x10($v1)
/*  f117df8:	24190018 */ 	addiu	$t9,$zero,0x18
/*  f117dfc:	10000061 */ 	beqz	$zero,.NB0f117f84
/*  f117e00:	ac790010 */ 	sw	$t9,0x10($v1)
/*  f117e04:	24080019 */ 	addiu	$t0,$zero,0x19
/*  f117e08:	1000005e */ 	beqz	$zero,.NB0f117f84
/*  f117e0c:	ac680010 */ 	sw	$t0,0x10($v1)
/*  f117e10:	2409000b */ 	addiu	$t1,$zero,0xb
/*  f117e14:	1000005b */ 	beqz	$zero,.NB0f117f84
/*  f117e18:	ac690010 */ 	sw	$t1,0x10($v1)
/*  f117e1c:	8c6a0000 */ 	lw	$t2,0x0($v1)
/*  f117e20:	24010003 */ 	addiu	$at,$zero,0x3
/*  f117e24:	24041748 */ 	addiu	$a0,$zero,0x1748
/*  f117e28:	15410013 */ 	bne	$t2,$at,.NB0f117e78
/*  f117e2c:	240d000b */ 	addiu	$t5,$zero,0xb
/*  f117e30:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f117e34:	24a5ecf4 */ 	addiu	$a1,$a1,-4876
/*  f117e38:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117e3c:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f117e40:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117e44:	83a6002b */ 	lb	$a2,0x2b($sp)
/*  f117e48:	00062600 */ 	sll	$a0,$a2,0x18
/*  f117e4c:	00045e03 */ 	sra	$t3,$a0,0x18
/*  f117e50:	0fc45fe5 */ 	jal	pak7f117f94nb
/*  f117e54:	01602025 */ 	or	$a0,$t3,$zero
/*  f117e58:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f117e5c:	24a5ecfc */ 	addiu	$a1,$a1,-4868
/*  f117e60:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f117e64:	2404174a */ 	addiu	$a0,$zero,0x174a
/*  f117e68:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117e6c:	240c000d */ 	addiu	$t4,$zero,0xd
/*  f117e70:	10000044 */ 	beqz	$zero,.NB0f117f84
/*  f117e74:	ac6c0010 */ 	sw	$t4,0x10($v1)
.NB0f117e78:
/*  f117e78:	10000042 */ 	beqz	$zero,.NB0f117f84
/*  f117e7c:	ac6d0010 */ 	sw	$t5,0x10($v1)
/*  f117e80:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117e84:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117e88:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117e8c:	0fc3b669 */ 	jal	menuSetBanner
/*  f117e90:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117e94:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117e98:	0fc3e5ed */ 	jal	func0f0fd1f4
/*  f117e9c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117ea0:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117ea4:	10400037 */ 	beqz	$v0,.NB0f117f84
/*  f117ea8:	83a6002b */ 	lb	$a2,0x2b($sp)
/*  f117eac:	00c02025 */ 	or	$a0,$a2,$zero
/*  f117eb0:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117eb4:	0fc3e632 */ 	jal	func0f0fd320
/*  f117eb8:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117ebc:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117ec0:	240e0014 */ 	addiu	$t6,$zero,0x14
/*  f117ec4:	1000002f */ 	beqz	$zero,.NB0f117f84
/*  f117ec8:	ac6e0010 */ 	sw	$t6,0x10($v1)
/*  f117ecc:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117ed0:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117ed4:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117ed8:	0fc3b669 */ 	jal	menuSetBanner
/*  f117edc:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117ee0:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117ee4:	0fc3e5ed */ 	jal	func0f0fd1f4
/*  f117ee8:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f117eec:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117ef0:	10400024 */ 	beqz	$v0,.NB0f117f84
/*  f117ef4:	83a6002b */ 	lb	$a2,0x2b($sp)
/*  f117ef8:	00c02025 */ 	or	$a0,$a2,$zero
/*  f117efc:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f117f00:	0fc3e632 */ 	jal	func0f0fd320
/*  f117f04:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117f08:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117f0c:	240f0013 */ 	addiu	$t7,$zero,0x13
/*  f117f10:	1000001c */ 	beqz	$zero,.NB0f117f84
/*  f117f14:	ac6f0010 */ 	sw	$t7,0x10($v1)
/*  f117f18:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117f1c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117f20:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117f24:	0fc3b669 */ 	jal	menuSetBanner
/*  f117f28:	a3a6002b */ 	sb	$a2,0x2b($sp)
/*  f117f2c:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117f30:	0fc3e5ed */ 	jal	func0f0fd1f4
/*  f117f34:	00002825 */ 	or	$a1,$zero,$zero
/*  f117f38:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117f3c:	10400011 */ 	beqz	$v0,.NB0f117f84
/*  f117f40:	83a6002b */ 	lb	$a2,0x2b($sp)
/*  f117f44:	00c02025 */ 	or	$a0,$a2,$zero
/*  f117f48:	00002825 */ 	or	$a1,$zero,$zero
/*  f117f4c:	0fc3e632 */ 	jal	func0f0fd320
/*  f117f50:	afa3001c */ 	sw	$v1,0x1c($sp)
/*  f117f54:	8fa3001c */ 	lw	$v1,0x1c($sp)
/*  f117f58:	24180015 */ 	addiu	$t8,$zero,0x15
/*  f117f5c:	10000009 */ 	beqz	$zero,.NB0f117f84
/*  f117f60:	ac780010 */ 	sw	$t8,0x10($v1)
/*  f117f64:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117f68:	0fc3b669 */ 	jal	menuSetBanner
/*  f117f6c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f117f70:	10000005 */ 	beqz	$zero,.NB0f117f88
/*  f117f74:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f117f78:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f117f7c:	0fc3b669 */ 	jal	menuSetBanner
/*  f117f80:	24050001 */ 	addiu	$a1,$zero,0x1
.NB0f117f84:
/*  f117f84:	8fbf0014 */ 	lw	$ra,0x14($sp)
.NB0f117f88:
/*  f117f88:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f117f8c:	03e00008 */ 	jr	$ra
/*  f117f90:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

#if VERSION >= VERSION_NTSC_1_0
void pak0f11e3b4(void)
{
	// empty
}
#endif

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel pak7f117f94nb
/*  f117f94:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f117f98:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f117f9c:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f117fa0:	0fc461b0 */ 	jal	gbpakIdentifyGame
/*  f117fa4:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117fa8:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f117fac:	3c0f800a */ 	lui	$t7,0x800a
/*  f117fb0:	25ef6870 */ 	addiu	$t7,$t7,0x6870
/*  f117fb4:	00047080 */ 	sll	$t6,$a0,0x2
/*  f117fb8:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f117fbc:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f117fc0:	01c47023 */ 	subu	$t6,$t6,$a0
/*  f117fc4:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f117fc8:	01c47021 */ 	addu	$t6,$t6,$a0
/*  f117fcc:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f117fd0:	01cf3021 */ 	addu	$a2,$t6,$t7
/*  f117fd4:	90c902b8 */ 	lbu	$t1,0x2b8($a2)
/*  f117fd8:	8ccc0008 */ 	lw	$t4,0x8($a2)
/*  f117fdc:	0002c8c0 */ 	sll	$t9,$v0,0x3
/*  f117fe0:	33280008 */ 	andi	$t0,$t9,0x8
/*  f117fe4:	312afff7 */ 	andi	$t2,$t1,0xfff7
/*  f117fe8:	010a5825 */ 	or	$t3,$t0,$t2
/*  f117fec:	2401000c */ 	addiu	$at,$zero,0xc
/*  f117ff0:	15810011 */ 	bne	$t4,$at,.NB0f118038
/*  f117ff4:	a0cb02b8 */ 	sb	$t3,0x2b8($a2)
/*  f117ff8:	0fc461b0 */ 	jal	gbpakIdentifyGame
/*  f117ffc:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f118000:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f118004:	000270c0 */ 	sll	$t6,$v0,0x3
/*  f118008:	31cf0008 */ 	andi	$t7,$t6,0x8
/*  f11800c:	90d802b8 */ 	lbu	$t8,0x2b8($a2)
/*  f118010:	3319fff7 */ 	andi	$t9,$t8,0xfff7
/*  f118014:	01f94825 */ 	or	$t1,$t7,$t9
/*  f118018:	a0c902b8 */ 	sb	$t1,0x2b8($a2)
/*  f11801c:	8cc302b8 */ 	lw	$v1,0x2b8($a2)
/*  f118020:	00035100 */ 	sll	$t2,$v1,0x4
/*  f118024:	05410004 */ 	bgez	$t2,.NB0f118038
/*  f118028:	00036080 */ 	sll	$t4,$v1,0x2
/*  f11802c:	05830003 */ 	bgezl	$t4,.NB0f11803c
/*  f118030:	8ccd02b8 */ 	lw	$t5,0x2b8($a2)
/*  f118034:	acc00008 */ 	sw	$zero,0x8($a2)
.NB0f118038:
/*  f118038:	8ccd02b8 */ 	lw	$t5,0x2b8($a2)
.NB0f11803c:
/*  f11803c:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f118040:	000dc100 */ 	sll	$t8,$t5,0x4
/*  f118044:	07020008 */ 	bltzl	$t8,.NB0f118068
/*  f118048:	8cc30008 */ 	lw	$v1,0x8($a2)
/*  f11804c:	0fc51dcf */ 	jal	func0f14cf6c
/*  f118050:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f118054:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f118058:	240f000c */ 	addiu	$t7,$zero,0xc
/*  f11805c:	10000063 */ 	beqz	$zero,.NB0f1181ec
/*  f118060:	accf0008 */ 	sw	$t7,0x8($a2)
/*  f118064:	8cc30008 */ 	lw	$v1,0x8($a2)
.NB0f118068:
/*  f118068:	24010001 */ 	addiu	$at,$zero,0x1
/*  f11806c:	50610060 */ 	beql	$v1,$at,.NB0f1181f0
/*  f118070:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f118074:	14600005 */ 	bnez	$v1,.NB0f11808c
/*  f118078:	24010002 */ 	addiu	$at,$zero,0x2
/*  f11807c:	0fc45ac3 */ 	jal	gbpak0f11cef8
/*  f118080:	00000000 */ 	sll	$zero,$zero,0x0
/*  f118084:	1000005a */ 	beqz	$zero,.NB0f1181f0
/*  f118088:	8fbf0014 */ 	lw	$ra,0x14($sp)
.NB0f11808c:
/*  f11808c:	54610008 */ 	bnel	$v1,$at,.NB0f1180b0
/*  f118090:	24010003 */ 	addiu	$at,$zero,0x3
/*  f118094:	0fc45ac3 */ 	jal	gbpak0f11cef8
/*  f118098:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f11809c:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f1180a0:	24030003 */ 	addiu	$v1,$zero,0x3
/*  f1180a4:	acc30008 */ 	sw	$v1,0x8($a2)
/*  f1180a8:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f1180ac:	24010003 */ 	addiu	$at,$zero,0x3
.NB0f1180b0:
/*  f1180b0:	54610008 */ 	bnel	$v1,$at,.NB0f1180d4
/*  f1180b4:	8cc30008 */ 	lw	$v1,0x8($a2)
/*  f1180b8:	0fc45b47 */ 	jal	pak0f116d1cnb
/*  f1180bc:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f1180c0:	14400003 */ 	bnez	$v0,.NB0f1180d0
/*  f1180c4:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f1180c8:	24090004 */ 	addiu	$t1,$zero,0x4
/*  f1180cc:	acc90008 */ 	sw	$t1,0x8($a2)
.NB0f1180d0:
/*  f1180d0:	8cc30008 */ 	lw	$v1,0x8($a2)
.NB0f1180d4:
/*  f1180d4:	24010004 */ 	addiu	$at,$zero,0x4
/*  f1180d8:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f1180dc:	5461000b */ 	bnel	$v1,$at,.NB0f11810c
/*  f1180e0:	24010005 */ 	addiu	$at,$zero,0x5
/*  f1180e4:	8cc802b8 */ 	lw	$t0,0x2b8($a2)
/*  f1180e8:	24030008 */ 	addiu	$v1,$zero,0x8
/*  f1180ec:	00085940 */ 	sll	$t3,$t0,0x5
/*  f1180f0:	05630005 */ 	bgezl	$t3,.NB0f118108
/*  f1180f4:	acc30008 */ 	sw	$v1,0x8($a2)
/*  f1180f8:	24030005 */ 	addiu	$v1,$zero,0x5
/*  f1180fc:	10000002 */ 	beqz	$zero,.NB0f118108
/*  f118100:	acc30008 */ 	sw	$v1,0x8($a2)
/*  f118104:	acc30008 */ 	sw	$v1,0x8($a2)
.NB0f118108:
/*  f118108:	24010005 */ 	addiu	$at,$zero,0x5
.NB0f11810c:
/*  f11810c:	54610008 */ 	bnel	$v1,$at,.NB0f118130
/*  f118110:	24010006 */ 	addiu	$at,$zero,0x6
/*  f118114:	0fc45ac3 */ 	jal	gbpak0f11cef8
/*  f118118:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f11811c:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f118120:	24030006 */ 	addiu	$v1,$zero,0x6
/*  f118124:	acc30008 */ 	sw	$v1,0x8($a2)
/*  f118128:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f11812c:	24010006 */ 	addiu	$at,$zero,0x6
.NB0f118130:
/*  f118130:	54610008 */ 	bnel	$v1,$at,.NB0f118154
/*  f118134:	8cc30008 */ 	lw	$v1,0x8($a2)
/*  f118138:	0fc45b47 */ 	jal	pak0f116d1cnb
/*  f11813c:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f118140:	14400003 */ 	bnez	$v0,.NB0f118150
/*  f118144:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f118148:	24180007 */ 	addiu	$t8,$zero,0x7
/*  f11814c:	acd80008 */ 	sw	$t8,0x8($a2)
.NB0f118150:
/*  f118150:	8cc30008 */ 	lw	$v1,0x8($a2)
.NB0f118154:
/*  f118154:	24010007 */ 	addiu	$at,$zero,0x7
/*  f118158:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f11815c:	14610003 */ 	bne	$v1,$at,.NB0f11816c
/*  f118160:	00001025 */ 	or	$v0,$zero,$zero
/*  f118164:	24030008 */ 	addiu	$v1,$zero,0x8
/*  f118168:	acc30008 */ 	sw	$v1,0x8($a2)
.NB0f11816c:
/*  f11816c:	24010008 */ 	addiu	$at,$zero,0x8
/*  f118170:	5461000f */ 	bnel	$v1,$at,.NB0f1181b0
/*  f118174:	24010009 */ 	addiu	$at,$zero,0x9
/*  f118178:	24031000 */ 	addiu	$v1,$zero,0x1000
.NB0f11817c:
/*  f11817c:	8cd902c4 */ 	lw	$t9,0x2c4($a2)
/*  f118180:	03224821 */ 	addu	$t1,$t9,$v0
/*  f118184:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f118188:	1443fffc */ 	bne	$v0,$v1,.NB0f11817c
/*  f11818c:	a1200000 */ 	sb	$zero,0x0($t1)
/*  f118190:	8cc50270 */ 	lw	$a1,0x270($a2)
/*  f118194:	0fc45cb2 */ 	jal	pak7f1172c8nb
/*  f118198:	afa60018 */ 	sw	$a2,0x18($sp)
/*  f11819c:	8fa60018 */ 	lw	$a2,0x18($sp)
/*  f1181a0:	24030009 */ 	addiu	$v1,$zero,0x9
/*  f1181a4:	acc30008 */ 	sw	$v1,0x8($a2)
/*  f1181a8:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f1181ac:	24010009 */ 	addiu	$at,$zero,0x9
.NB0f1181b0:
/*  f1181b0:	5461000f */ 	bnel	$v1,$at,.NB0f1181f0
/*  f1181b4:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1181b8:	0fc44589 */ 	jal	pakGetUnk270
/*  f1181bc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1181c0:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f1181c4:	0fc45cd4 */ 	jal	gbpak0f11d680
/*  f1181c8:	00402825 */ 	or	$a1,$v0,$zero
/*  f1181cc:	50400008 */ 	beqzl	$v0,.NB0f1181f0
/*  f1181d0:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1181d4:	0fc45d23 */ 	jal	pak0f11d7c4
/*  f1181d8:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f1181dc:	10400003 */ 	beqz	$v0,.NB0f1181ec
/*  f1181e0:	83a4002b */ 	lb	$a0,0x2b($sp)
/*  f1181e4:	0fc4457b */ 	jal	pakSetUnk008
/*  f1181e8:	2405000b */ 	addiu	$a1,$zero,0xb
.NB0f1181ec:
/*  f1181ec:	8fbf0014 */ 	lw	$ra,0x14($sp)
.NB0f1181f0:
/*  f1181f0:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f1181f4:	03e00008 */ 	jr	$ra
/*  f1181f8:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

void pak0f11e3bc(s8 device)
{
	g_Paks[device].unk008 = 0;
}

void pakProbeEeprom(void)
{
	s32 type;

	joyDisableCyclicPolling(JOYARGS(6199));
	type = osEepromProbe(&g_PiMesgQueue);
	joyEnableCyclicPolling(JOYARGS(6201));

	if (type == EEPROM_TYPE_16K) {
		g_PakHasEeprom = true;

		if (argFindByPrefix(1, "-scrub")) {
			pakCreateFilesystem(SAVEDEVICE_GAMEPAK);
		}
	} else {
		g_PakHasEeprom = false;
	}
}

PakErr1 pakReadEeprom(u8 address, u8 *buffer, u32 len)
{
	s32 result;

	joyDisableCyclicPolling(JOYARGS(6234));
	result = osEepromLongRead(&g_PiMesgQueue, address, buffer, len);
	joyEnableCyclicPolling(JOYARGS(6236));

	return result == PAK_ERR1_OK ? PAK_ERR1_OK : PAK_ERR1_EEPROMREADFAILED;
}

PakErr1 pakWriteEeprom(u8 address, u8 *buffer, u32 len)
{
	s32 result;

	joyDisableCyclicPolling(JOYARGS(6269));
	result = osEepromLongWrite(&g_PiMesgQueue, address, buffer, len);
	joyEnableCyclicPolling(JOYARGS(6271));

	return result == PAK_ERR1_OK ? PAK_ERR1_OK : PAK_ERR1_EEPROMWRITEFAILED;
}

GLOBAL_ASM(
glabel pakSetBitflag
/*  f11e530:	10c0000a */ 	beqz	$a2,.L0f11e55c
/*  f11e534:	000458c2 */ 	srl	$t3,$a0,0x3
/*  f11e538:	000470c2 */ 	srl	$t6,$a0,0x3
/*  f11e53c:	00ae1021 */ 	addu	$v0,$a1,$t6
/*  f11e540:	904f0000 */ 	lbu	$t7,0x0($v0)
/*  f11e544:	30980007 */ 	andi	$t8,$a0,0x7
/*  f11e548:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f11e54c:	03194804 */ 	sllv	$t1,$t9,$t8
/*  f11e550:	01e95025 */ 	or	$t2,$t7,$t1
/*  f11e554:	03e00008 */ 	jr	$ra
/*  f11e558:	a04a0000 */ 	sb	$t2,0x0($v0)
.L0f11e55c:
/*  f11e55c:	00ab1021 */ 	addu	$v0,$a1,$t3
/*  f11e560:	904c0000 */ 	lbu	$t4,0x0($v0)
/*  f11e564:	308d0007 */ 	andi	$t5,$a0,0x7
/*  f11e568:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f11e56c:	01aec004 */ 	sllv	$t8,$t6,$t5
/*  f11e570:	03007827 */ 	nor	$t7,$t8,$zero
/*  f11e574:	018f4824 */ 	and	$t1,$t4,$t7
/*  f11e578:	a0490000 */ 	sb	$t1,0x0($v0)
/*  f11e57c:	03e00008 */ 	jr	$ra
/*  f11e580:	00000000 */ 	sll	$zero,$zero,0x0
);

// Mismatch: regalloc
//void pakSetBitflag(u32 flagnum, u8 *bitstream, bool set)
//{
//	u32 byteindex = flagnum / 8;
//	u8 mask = 1 << (flagnum % 8);
//
//	if (set) {
//		bitstream[byteindex] |= mask;
//	} else {
//		bitstream[byteindex] &= ~mask;
//	}
//}

bool pakHasBitflag(u32 flagnum, u8 *bitstream)
{
	u32 byteindex = flagnum / 8;
	u8 mask = 1 << (flagnum % 8);

	return bitstream[byteindex] & mask ? 1 : 0;
}

void pakClearAllBitflags(u8 *flags)
{
	s32 i;

	for (i = 0; i <= GAMEFILEFLAG_4E; i++) {
		pakSetBitflag(i, flags, false);
	}
}

u32 pak0f11e610(u32 arg0)
{
	return arg0;
}

#if VERSION >= VERSION_JPN_FINAL
GLOBAL_ASM(
glabel pakN64FontCodeToAscii
/*  f11e9e4:	27bdfed0 */ 	addiu	$sp,$sp,-304
/*  f11e9e8:	afb10018 */ 	sw	$s1,0x18($sp)
/*  f11e9ec:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f11e9f0:	00808025 */ 	move	$s0,$a0
/*  f11e9f4:	00c08825 */ 	move	$s1,$a2
/*  f11e9f8:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f11e9fc:	afa50134 */ 	sw	$a1,0x134($sp)
/*  f11ea00:	27a20030 */ 	addiu	$v0,$sp,0x30
/*  f11ea04:	18c00021 */ 	blez	$a2,.JF0f11ea8c
/*  f11ea08:	00003825 */ 	move	$a3,$zero
/*  f11ea0c:	3c067f1b */ 	lui	$a2,0x7f1b
/*  f11ea10:	24c64760 */ 	addiu	$a2,$a2,0x4760
/*  f11ea14:	24080022 */ 	li	$t0,0x22
/*  f11ea18:	24050027 */ 	li	$a1,0x27
.JF0f11ea1c:
/*  f11ea1c:	92030000 */ 	lbu	$v1,0x0($s0)
/*  f11ea20:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f11ea24:	24e70001 */ 	addiu	$a3,$a3,0x1
/*  f11ea28:	28610042 */ 	slti	$at,$v1,0x42
/*  f11ea2c:	10200003 */ 	beqz	$at,.JF0f11ea3c
/*  f11ea30:	2404002a */ 	li	$a0,0x2a
/*  f11ea34:	00c37021 */ 	addu	$t6,$a2,$v1
/*  f11ea38:	91c40000 */ 	lbu	$a0,0x0($t6)
.JF0f11ea3c:
/*  f11ea3c:	14880005 */ 	bne	$a0,$t0,.JF0f11ea54
/*  f11ea40:	28610042 */ 	slti	$at,$v1,0x42
/*  f11ea44:	a0450000 */ 	sb	$a1,0x0($v0)
/*  f11ea48:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11ea4c:	1000000d */ 	b	.JF0f11ea84
/*  f11ea50:	a0450000 */ 	sb	$a1,0x0($v0)
.JF0f11ea54:
/*  f11ea54:	1420000a */ 	bnez	$at,.JF0f11ea80
/*  f11ea58:	28610095 */ 	slti	$at,$v1,0x95
/*  f11ea5c:	10200008 */ 	beqz	$at,.JF0f11ea80
/*  f11ea60:	000379c3 */ 	sra	$t7,$v1,0x7
/*  f11ea64:	3079007f */ 	andi	$t9,$v1,0x7f
/*  f11ea68:	35f80080 */ 	ori	$t8,$t7,0x80
/*  f11ea6c:	37290080 */ 	ori	$t1,$t9,0x80
/*  f11ea70:	a0580000 */ 	sb	$t8,0x0($v0)
/*  f11ea74:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f11ea78:	10000002 */ 	b	.JF0f11ea84
/*  f11ea7c:	a0490000 */ 	sb	$t1,0x0($v0)
.JF0f11ea80:
/*  f11ea80:	a0440000 */ 	sb	$a0,0x0($v0)
.JF0f11ea84:
/*  f11ea84:	14f1ffe5 */ 	bne	$a3,$s1,.JF0f11ea1c
/*  f11ea88:	24420001 */ 	addiu	$v0,$v0,0x1
.JF0f11ea8c:
/*  f11ea8c:	a0400000 */ 	sb	$zero,0x0($v0)
/*  f11ea90:	8fa40134 */ 	lw	$a0,0x134($sp)
/*  f11ea94:	0c004c34 */ 	jal	strcpy
/*  f11ea98:	27a50030 */ 	addiu	$a1,$sp,0x30
/*  f11ea9c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f11eaa0:	8fb00014 */ 	lw	$s0,0x14($sp)
/*  f11eaa4:	8fb10018 */ 	lw	$s1,0x18($sp)
/*  f11eaa8:	03e00008 */ 	jr	$ra
/*  f11eaac:	27bd0130 */ 	addiu	$sp,$sp,0x130
);
#else
/**
 * The note name and note extension are stored on the pak using N64 font code.
 * This is different to ASCII.
 *
 * This function expects src to be a pointer to an N64 font code string.
 * It converts it to ASCII and writes it to dst. Characters are replaced with
 * an asterisk if they are invalid font codes or if the character doesn't exist
 * in PD's font.
 */
void pakN64FontCodeToAscii(char *src, char *dst, s32 len)
{
	char buffer[256];
	s32 i;
	char in;
	char c;
	char *ptr = buffer;

	for (i = 0; i < len;) {
		in = *src;
		src++;
		i++;
		c = '*';

		// @bug: The length check of the map is off by 1. The last char in the
		// list is '@', so if an @ sign appears in a note name then PD will
		// incorrectly replace it with '*' when displaying the name.
		// The original source likely used a literal here instead of sizeof().
		if (in < (s32)(sizeof(g_N64FontCodeMap) - 1)) {
			c = g_N64FontCodeMap[in];
		}

		// PD has a double quote in its fonts, but I guess it doesn't render
		// very well. So it gets replaced with two single quotes.
		if ((u32)c == '"') {
			*ptr = '\'';
			ptr++;
			*ptr = '\'';
		} else {
			*ptr = c;
		}

		ptr++;
	}

	*ptr = '\0';

	strcpy(dst, buffer);
}
#endif

s8 pakFindBySerial(s32 findserial)
{
	s8 device = -1;
	s32 i;

	for (i = 0; i < 5; i++) {
		if (pak0f116aec(i)) {
			s32 serial = pakGetSerial(i);

			if (findserial == serial) {
				device = i;
			}
		}
	}

	return device;
}

#if VERSION >= VERSION_NTSC_1_0
const char var7f1b4d24[] = "Pak %d -> Pak_PdGameBoySetRWByte - Fatal Error\n";
#else
const char var7f1b4d24[] = "Pak %d -> Pak_PdGameBoySetRWByte - Fatal Error";
#endif

s32 pak0f11e750(s8 device)
{
	u8 buffer[32];
	buffer[0] = 0x0a;

	return gbpakWrite(device, 0, buffer, sizeof(buffer));
}

bool gbpakIsAnyPerfectDark(void)
{
	s8 i;

	for (i = 0; i < 4; i++) {
		if (gbpakIdentifyGame(i) == GBGAME_PD) {
			return true;
		}
	}

	return false;
}

/**
 * Probable @bug: This function is probably intended to be a "strings are equal"
 * check, however it's actually checking if either string starts with the other.
 */
bool gbpakStrcmp(char *a, char *b)
{
	while (*a != '\0' && *b != '\0') {
		if (*a != *b) {
			return false;
		}

		a++;
		b++;
	}

	return true;
}

#if VERSION >= VERSION_NTSC_1_0
s32 gbpakIdentifyGame(s8 device)
{
	OSGbpakId id;
	u8 status;
	s32 ret;
	s32 game = GBGAME_OTHER;
	bool poweredon = false;
	bool ok = true;

	if (g_Paks[device].type != PAKTYPE_GAMEBOY) {
		return GBGAME_OTHER;
	}

	joyDisableCyclicPolling();

	ret = osGbpakReadId(PFS(device), &id, &status);

#if VERSION >= VERSION_NTSC_FINAL
	// NTSC Final sets poweredon to true unconditionally.
	// If we just set it to true without the if-statement then it creates a
	// mismatch because the compiler optimises out the poweredon = false line
	// earlier. Using this if-statement with a condition that's always true
	// makes the compiler optimise out the if-statement but leave both
	// assignments to poweredon intact.
	if (ok) {
		poweredon = true;
	}

	if (ret != PAK_ERR1_OK) {
		ok = false;
	}
#else
	// NTSC 1.0 only sets poweredon to true if the call to osGbpakReadId
	// returned PAK_ERR1_OK.
	// The else here might have been else if (ok). This optimises itself out,
	// but may explain why the final code appears to use a condition. They could
	// have moved the else-if into its own check (and had to do it prior to the
	// ret check for it to work as intended).
	if (ret != PAK_ERR1_OK) {
		ok = false;
	} else {
		poweredon = true;
	}
#endif

	if (var80075cb0 == id.company_code) {
		if (gbpakStrcmp(var80075cb4, id.game_title) || gbpakStrcmp(var80075cc0, id.game_title)) {
			g_Paks[device].unk2b8_03 = 0;
			g_Paks[device].unk2b8_04 = 1;
			game = GBGAME_PD;
		}
	}

	if (game != GBGAME_PD) {
		ok = false;
	}

	if (poweredon) {
		if (osGbpakPower(PFS(device), OS_GBPAK_POWER_OFF) != PAK_ERR1_OK) {
			ok = false;
		}
	}

	joyEnableCyclicPolling();

	if (ok) {
		return game;
	}

	g_Paks[device].unk010 = PAK010_26;
	return GBGAME_OTHER;
}
#else
const char var7f1aee7c[] = "pak.c";
const char var7f1aee84[] = "pak.c";
const char var7f1aee8c[] = "pak.c";
const char var7f1aee94[] = "pak.c";
const char var7f1aee9c[] = "pak.c";
const char var7f1aeea4[] = "pak.c";
const char var7f1aeeac[] = "pak.c";
const char var7f1aeeb4[] = "pak.c";
const char var7f1aeebc[] = "pak.c";
const char var7f1aeec4[] = "pak.c";

GLOBAL_ASM(
glabel gbpakIdentifyGame
/*  f1186c0:	27bdff80 */ 	addiu	$sp,$sp,-128
/*  f1186c4:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f1186c8:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f1186cc:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1186d0:	24a5ee7c */ 	addiu	$a1,$a1,-4484
/*  f1186d4:	0c00581b */ 	jal	joyDisableCyclicPolling
/*  f1186d8:	24041b85 */ 	addiu	$a0,$zero,0x1b85
/*  f1186dc:	83a20083 */ 	lb	$v0,0x83($sp)
/*  f1186e0:	3c0f800a */ 	lui	$t7,0x800a
/*  f1186e4:	25ef6870 */ 	addiu	$t7,$t7,0x6870
/*  f1186e8:	00027080 */ 	sll	$t6,$v0,0x2
/*  f1186ec:	01c27023 */ 	subu	$t6,$t6,$v0
/*  f1186f0:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f1186f4:	01c27023 */ 	subu	$t6,$t6,$v0
/*  f1186f8:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f1186fc:	01c27021 */ 	addu	$t6,$t6,$v0
/*  f118700:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f118704:	01cf1821 */ 	addu	$v1,$t6,$t7
/*  f118708:	8c780000 */ 	lw	$t8,0x0($v1)
/*  f11870c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f118710:	24041b8a */ 	addiu	$a0,$zero,0x1b8a
/*  f118714:	13010006 */ 	beq	$t8,$at,.NB0f118730
/*  f118718:	27a5002f */ 	addiu	$a1,$sp,0x2f
/*  f11871c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f118720:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f118724:	24a5ee84 */ 	addiu	$a1,$a1,-4476
/*  f118728:	100000a3 */ 	beqz	$zero,.NB0f1189b8
/*  f11872c:	00001025 */ 	or	$v0,$zero,$zero
.NB0f118730:
/*  f118730:	24010004 */ 	addiu	$at,$zero,0x4
/*  f118734:	14410003 */ 	bne	$v0,$at,.NB0f118744
/*  f118738:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f11873c:	10000008 */ 	beqz	$zero,.NB0f118760
/*  f118740:	00002025 */ 	or	$a0,$zero,$zero
.NB0f118744:
/*  f118744:	0322c823 */ 	subu	$t9,$t9,$v0
/*  f118748:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f11874c:	0322c821 */ 	addu	$t9,$t9,$v0
/*  f118750:	3c08800a */ 	lui	$t0,0x800a
/*  f118754:	25087658 */ 	addiu	$t0,$t0,0x7658
/*  f118758:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f11875c:	03282021 */ 	addu	$a0,$t9,$t0
.NB0f118760:
/*  f118760:	0c0148f0 */ 	jal	osGbpakGetStatus
/*  f118764:	afa30020 */ 	sw	$v1,0x20($sp)
/*  f118768:	10400007 */ 	beqz	$v0,.NB0f118788
/*  f11876c:	93a3002f */ 	lbu	$v1,0x2f($sp)
/*  f118770:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f118774:	24a5ee8c */ 	addiu	$a1,$a1,-4468
/*  f118778:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f11877c:	24041b91 */ 	addiu	$a0,$zero,0x1b91
/*  f118780:	1000008d */ 	beqz	$zero,.NB0f1189b8
/*  f118784:	00001025 */ 	or	$v0,$zero,$zero
.NB0f118788:
/*  f118788:	30690004 */ 	andi	$t1,$v1,0x4
/*  f11878c:	11200010 */ 	beqz	$t1,.NB0f1187d0
/*  f118790:	83a20083 */ 	lb	$v0,0x83($sp)
/*  f118794:	24010004 */ 	addiu	$at,$zero,0x4
/*  f118798:	14410003 */ 	bne	$v0,$at,.NB0f1187a8
/*  f11879c:	00025080 */ 	sll	$t2,$v0,0x2
/*  f1187a0:	10000008 */ 	beqz	$zero,.NB0f1187c4
/*  f1187a4:	00002025 */ 	or	$a0,$zero,$zero
.NB0f1187a8:
/*  f1187a8:	01425023 */ 	subu	$t2,$t2,$v0
/*  f1187ac:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f1187b0:	01425021 */ 	addu	$t2,$t2,$v0
/*  f1187b4:	3c0b800a */ 	lui	$t3,0x800a
/*  f1187b8:	256b7658 */ 	addiu	$t3,$t3,0x7658
/*  f1187bc:	000a50c0 */ 	sll	$t2,$t2,0x3
/*  f1187c0:	014b2021 */ 	addu	$a0,$t2,$t3
.NB0f1187c4:
/*  f1187c4:	0c0148f0 */ 	jal	osGbpakGetStatus
/*  f1187c8:	27a5002f */ 	addiu	$a1,$sp,0x2f
/*  f1187cc:	93a3002f */ 	lbu	$v1,0x2f($sp)
.NB0f1187d0:
/*  f1187d0:	30620080 */ 	andi	$v0,$v1,0x80
/*  f1187d4:	14400006 */ 	bnez	$v0,.NB0f1187f0
/*  f1187d8:	24041b9f */ 	addiu	$a0,$zero,0x1b9f
/*  f1187dc:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1187e0:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f1187e4:	24a5ee94 */ 	addiu	$a1,$a1,-4460
/*  f1187e8:	10000073 */ 	beqz	$zero,.NB0f1189b8
/*  f1187ec:	00001025 */ 	or	$v0,$zero,$zero
.NB0f1187f0:
/*  f1187f0:	14400006 */ 	bnez	$v0,.NB0f11880c
/*  f1187f4:	24041ba6 */ 	addiu	$a0,$zero,0x1ba6
/*  f1187f8:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1187fc:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f118800:	24a5ee9c */ 	addiu	$a1,$a1,-4452
/*  f118804:	1000006c */ 	beqz	$zero,.NB0f1189b8
/*  f118808:	00001025 */ 	or	$v0,$zero,$zero
.NB0f11880c:
/*  f11880c:	83a20083 */ 	lb	$v0,0x83($sp)
/*  f118810:	24010004 */ 	addiu	$at,$zero,0x4
/*  f118814:	3c0d800a */ 	lui	$t5,0x800a
/*  f118818:	14410003 */ 	bne	$v0,$at,.NB0f118828
/*  f11881c:	00026080 */ 	sll	$t4,$v0,0x2
/*  f118820:	10000007 */ 	beqz	$zero,.NB0f118840
/*  f118824:	00002025 */ 	or	$a0,$zero,$zero
.NB0f118828:
/*  f118828:	01826023 */ 	subu	$t4,$t4,$v0
/*  f11882c:	000c6080 */ 	sll	$t4,$t4,0x2
/*  f118830:	01826021 */ 	addu	$t4,$t4,$v0
/*  f118834:	000c60c0 */ 	sll	$t4,$t4,0x3
/*  f118838:	25ad7658 */ 	addiu	$t5,$t5,0x7658
/*  f11883c:	018d2021 */ 	addu	$a0,$t4,$t5
.NB0f118840:
/*  f118840:	0c00191c */ 	jal	osGbpakPower
/*  f118844:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f118848:	10400007 */ 	beqz	$v0,.NB0f118868
/*  f11884c:	83ae0083 */ 	lb	$t6,0x83($sp)
/*  f118850:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f118854:	24a5eea4 */ 	addiu	$a1,$a1,-4444
/*  f118858:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f11885c:	24041bad */ 	addiu	$a0,$zero,0x1bad
/*  f118860:	10000055 */ 	beqz	$zero,.NB0f1189b8
/*  f118864:	00001025 */ 	or	$v0,$zero,$zero
.NB0f118868:
/*  f118868:	24010004 */ 	addiu	$at,$zero,0x4
/*  f11886c:	15c10003 */ 	bne	$t6,$at,.NB0f11887c
/*  f118870:	27a50030 */ 	addiu	$a1,$sp,0x30
/*  f118874:	1000000a */ 	beqz	$zero,.NB0f1188a0
/*  f118878:	00002025 */ 	or	$a0,$zero,$zero
.NB0f11887c:
/*  f11887c:	83af0083 */ 	lb	$t7,0x83($sp)
/*  f118880:	3c19800a */ 	lui	$t9,0x800a
/*  f118884:	27397658 */ 	addiu	$t9,$t9,0x7658
/*  f118888:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f11888c:	030fc023 */ 	subu	$t8,$t8,$t7
/*  f118890:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f118894:	030fc021 */ 	addu	$t8,$t8,$t7
/*  f118898:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*  f11889c:	03192021 */ 	addu	$a0,$t8,$t9
.NB0f1188a0:
/*  f1188a0:	0c014950 */ 	jal	osGbpakReadId
/*  f1188a4:	27a6002f */ 	addiu	$a2,$sp,0x2f
/*  f1188a8:	10400007 */ 	beqz	$v0,.NB0f1188c8
/*  f1188ac:	97a80074 */ 	lhu	$t0,0x74($sp)
/*  f1188b0:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1188b4:	24a5eeac */ 	addiu	$a1,$a1,-4436
/*  f1188b8:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f1188bc:	24041bb8 */ 	addiu	$a0,$zero,0x1bb8
/*  f1188c0:	1000003d */ 	beqz	$zero,.NB0f1189b8
/*  f1188c4:	00001025 */ 	or	$v0,$zero,$zero
.NB0f1188c8:
/*  f1188c8:	3c098008 */ 	lui	$t1,0x8008
/*  f1188cc:	95298050 */ 	lhu	$t1,-0x7fb0($t1)
/*  f1188d0:	3c048008 */ 	lui	$a0,0x8008
/*  f1188d4:	24848058 */ 	addiu	$a0,$a0,-32680
/*  f1188d8:	15090014 */ 	bne	$t0,$t1,.NB0f11892c
/*  f1188dc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f1188e0:	0fc4619b */ 	jal	gbpakStrcmp
/*  f1188e4:	27a50064 */ 	addiu	$a1,$sp,0x64
/*  f1188e8:	14400006 */ 	bnez	$v0,.NB0f118904
/*  f1188ec:	3c048008 */ 	lui	$a0,0x8008
/*  f1188f0:	24848068 */ 	addiu	$a0,$a0,-32664
/*  f1188f4:	0fc4619b */ 	jal	gbpakStrcmp
/*  f1188f8:	27a50064 */ 	addiu	$a1,$sp,0x64
/*  f1188fc:	1040000b */ 	beqz	$v0,.NB0f11892c
/*  f118900:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f118904:
/*  f118904:	8fa20020 */ 	lw	$v0,0x20($sp)
/*  f118908:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f11890c:	24a5eeb4 */ 	addiu	$a1,$a1,-4428
/*  f118910:	904b02b8 */ 	lbu	$t3,0x2b8($v0)
/*  f118914:	24041bc7 */ 	addiu	$a0,$zero,0x1bc7
/*  f118918:	356d0020 */ 	ori	$t5,$t3,0x20
/*  f11891c:	31ae00ef */ 	andi	$t6,$t5,0xef
/*  f118920:	a04d02b8 */ 	sb	$t5,0x2b8($v0)
/*  f118924:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f118928:	a04e02b8 */ 	sb	$t6,0x2b8($v0)
.NB0f11892c:
/*  f11892c:	3c188008 */ 	lui	$t8,0x8008
/*  f118930:	97188054 */ 	lhu	$t8,-0x7fac($t8)
/*  f118934:	97af0074 */ 	lhu	$t7,0x74($sp)
/*  f118938:	3c048008 */ 	lui	$a0,0x8008
/*  f11893c:	24848078 */ 	addiu	$a0,$a0,-32648
/*  f118940:	15f80018 */ 	bne	$t7,$t8,.NB0f1189a4
/*  f118944:	00000000 */ 	sll	$zero,$zero,0x0
/*  f118948:	0fc4619b */ 	jal	gbpakStrcmp
/*  f11894c:	27a50064 */ 	addiu	$a1,$sp,0x64
/*  f118950:	14400006 */ 	bnez	$v0,.NB0f11896c
/*  f118954:	3c048008 */ 	lui	$a0,0x8008
/*  f118958:	24848084 */ 	addiu	$a0,$a0,-32636
/*  f11895c:	0fc4619b */ 	jal	gbpakStrcmp
/*  f118960:	27a50064 */ 	addiu	$a1,$sp,0x64
/*  f118964:	1040000f */ 	beqz	$v0,.NB0f1189a4
/*  f118968:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f11896c:
/*  f11896c:	8fa20020 */ 	lw	$v0,0x20($sp)
/*  f118970:	83a40083 */ 	lb	$a0,0x83($sp)
/*  f118974:	905902b8 */ 	lbu	$t9,0x2b8($v0)
/*  f118978:	332affdf */ 	andi	$t2,$t9,0xffdf
/*  f11897c:	354b0010 */ 	ori	$t3,$t2,0x10
/*  f118980:	a04a02b8 */ 	sb	$t2,0x2b8($v0)
/*  f118984:	0fc462a0 */ 	jal	pak0f11eaec
/*  f118988:	a04b02b8 */ 	sb	$t3,0x2b8($v0)
/*  f11898c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f118990:	24a5eebc */ 	addiu	$a1,$a1,-4420
/*  f118994:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f118998:	24041bdf */ 	addiu	$a0,$zero,0x1bdf
/*  f11899c:	10000006 */ 	beqz	$zero,.NB0f1189b8
/*  f1189a0:	24020002 */ 	addiu	$v0,$zero,0x2
.NB0f1189a4:
/*  f1189a4:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f1189a8:	24a5eec4 */ 	addiu	$a1,$a1,-4412
/*  f1189ac:	0c005834 */ 	jal	joyEnableCyclicPolling
/*  f1189b0:	24041be4 */ 	addiu	$a0,$zero,0x1be4
/*  f1189b4:	00001025 */ 	or	$v0,$zero,$zero
.NB0f1189b8:
/*  f1189b8:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1189bc:	27bd0080 */ 	addiu	$sp,$sp,0x80
/*  f1189c0:	03e00008 */ 	jr	$ra
/*  f1189c4:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

bool pak0f11ea34(s8 arg0)
{
	char numbers[] = "0123456789012345678901234567890123456789";
	u8 sp20[36];

	if (!pak0f11cd00(arg0, 0xa000, numbers, 32, true)) {
		return false;
	}

	if (!pak0f11ce00(arg0, 0xa000, sp20, 32, true)) {
		return false;
	}

	return true;
}

bool pak0f11eaec(s8 device)
{
	u8 sp78[32];
	u8 sp58[32];
	u8 sp38[32];
	s32 i;
	bool sp30 = false;
	bool result = false;
	u8 sp28[2];

	for (i = 0; i < 32; i++) {
		sp78[i] = 0;
		sp58[i] = 0;
	}

	sp78[0] = 0;

	pak0f11ea34(device);
	pak0f11ea34(device);
	pak0f11ea34(device);

	if (!pak0f11ce00(device, 0xbfe0, sp38, 32, true)) {
		sp30 = true;
	}

	for (i = 0; i < 32; i++) {
		sp28[0] = sp38[i];
		sp28[1] = 0;
	}

#if VERSION >= VERSION_NTSC_1_0
	gbpakStrcmp("PerfDark\n", sp38);
#else
	gbpakStrcmp("PerfDark", sp38);
#endif

	if (!pak0f11ce00(device, 0xa000, sp38, 32, true)) {
		sp30 = true;
	}

	if (sp38[0] & 1) {
		result = true;
	}

	if (sp30) {
		return false;
	}

	return result;
}

/**
 * This function isn't called.
 *
 * It reads data from the game boy pak, unsets a bit, writes it, reads it back,
 * sets the bit, writes it and then reads it back.
 */
void gbpakFiddle(s8 device)
{
	u8 buffer[32];

	if (gbpakRead(device, 0xa000, buffer, sizeof(buffer))) {
		pak0f11e750(device);
		buffer[0] &= 0x7f;

		if (gbpakWrite(device, 0xa000, buffer, sizeof(buffer))) {
			if (gbpakRead(device, 0xa000, buffer, sizeof(buffer))) {
				buffer[0] |= 0x80;

				if (gbpakWrite(device, 0xa000, buffer, sizeof(buffer))) {
					gbpakRead(device, 0xa000, buffer, sizeof(buffer));
				}
			}
		}
	}
}
