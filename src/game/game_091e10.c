#include <ultra64.h>
#include "constants.h"
#include "game/prop.h"
#include "game/game_091e10.h"
#include "game/game_0b28d0.h"
#include "game/bg.h"
#include "game/game_1a7560.h"
#include "game/propobj.h"
#include "bss.h"
#include "data.h"
#include "types.h"

struct stagesetup g_StageSetup;
u8 *g_GeCreditsData;

u32 setupGetCommandLength(u32 *cmd)
{
#if VERSION < VERSION_NTSC_1_0
	static u32 crash1 = 0;

	mainOverrideVariable("crash1", &crash1);
#endif

	switch ((u8)cmd[0]) {
	case OBJTYPE_CHR:                return 11;
	case OBJTYPE_DOOR:               return 55;
	case OBJTYPE_DOORSCALE:          return 2;
	case OBJTYPE_BASIC:              return 23;
	case OBJTYPE_DEBRIS:             return 23;
	case OBJTYPE_GLASS:              return 24;
	case OBJTYPE_TINTEDGLASS:        return 26;
	case OBJTYPE_SAFE:               return 23;
	case OBJTYPE_GASBOTTLE:          return 23;
	case OBJTYPE_KEY:                return 24;
	case OBJTYPE_ALARM:              return 23;
	case OBJTYPE_CCTV:               return 49;
	case OBJTYPE_AMMOCRATE:          return 24;
	case OBJTYPE_WEAPON:             return 26;
	case OBJTYPE_SINGLEMONITOR:      return 53;
	case OBJTYPE_MULTIMONITOR:       return 140;
	case OBJTYPE_HANGINGMONITORS:    return 23;
	case OBJTYPE_AUTOGUN:            return 43;
	case OBJTYPE_LINKGUNS:           return 2;
	case OBJTYPE_HAT:                return 23;
	case OBJTYPE_GRENADEPROB:        return 2;
	case OBJTYPE_LINKLIFTDOOR:       return 5;
	case OBJTYPE_SAFEITEM:           return 5;
	case OBJTYPE_MULTIAMMOCRATE:     return 42;
	case OBJTYPE_SHIELD:             return 26;
	case OBJTYPE_TAG:                return 4;
	case OBJTYPE_RENAMEOBJ:          return 10;
	case OBJTYPE_BEGINOBJECTIVE:     return 4;
	case OBJTYPE_ENDOBJECTIVE:       return 1;
	case OBJECTIVETYPE_DESTROYOBJ:   return 2;
	case OBJECTIVETYPE_COMPFLAGS:    return 2;
	case OBJECTIVETYPE_FAILFLAGS:    return 2;
	case OBJECTIVETYPE_COLLECTOBJ:   return 2;
	case OBJECTIVETYPE_THROWOBJ:     return 2;
	case OBJECTIVETYPE_HOLOGRAPH:    return 4;
	case OBJECTIVETYPE_1F:           return 1;
	case OBJECTIVETYPE_ENTERROOM:    return 4;
	case OBJECTIVETYPE_ATTACHOBJ:    return 5;
	case OBJTYPE_22:                 return 1;
	case OBJTYPE_BRIEFING:           return 4;
	case OBJTYPE_PADLOCKEDDOOR:      return 4;
	case OBJTYPE_TRUCK:              return 34;
	case OBJTYPE_HELI:               return 35;
	case OBJTYPE_TANK:               return 32;
	case OBJTYPE_CAMERAPOS:          return 7;
	case OBJTYPE_LIFT:               return 37;
	case OBJTYPE_CONDITIONALSCENERY: return 5;
	case OBJTYPE_BLOCKEDPATH:        return 4;
	case OBJTYPE_HOVERBIKE:          return 56;
	case OBJTYPE_HOVERPROP:          return 39;
	case OBJTYPE_FAN:                return 29;
	case OBJTYPE_HOVERCAR:           return 38;
	case OBJTYPE_CHOPPER:            return 58;
	case OBJTYPE_PADEFFECT:          return 3;
	case OBJTYPE_MINE:               return 26;
	case OBJTYPE_ESCASTEP:           return 27;
	}

#if VERSION < VERSION_NTSC_1_0
	if (crash1) {
		CRASH();
	}
#endif

	return 1;
}

u32 *setupGetPtrToCommandByIndex(s32 wantindex)
{
	u32 *cmd = g_StageSetup.props;

	if (wantindex >= 0 && cmd) {
		s32 cmdindex = 0;

		while ((u8)cmd[0] != OBJTYPE_END) {
			if (cmdindex == wantindex) {
				return cmd;
			}

			cmd = cmd + setupGetCommandLength(cmd);
			cmdindex++;
		}
	}

	return NULL;
}

s32 tagGetCommandIndex(struct tag *tag)
{
	u32 *cmd = g_StageSetup.props;

	if (cmd) {
		s32 cmdindex = 0;

		while ((u8)cmd[0] != OBJTYPE_END) {
			if ((struct tag *)cmd == tag) {
				return cmdindex;
			}

			cmd = cmd + setupGetCommandLength(cmd);
			cmdindex++;
		}
	}

	return -1;
}

u32 setupGetCommandIndexByProp(struct prop *prop)
{
	u32 *cmd = g_StageSetup.props;

	if (cmd) {
		s32 cmdindex = 0;

		while ((u8)cmd[0] != OBJTYPE_END) {
			if ((struct prop *)cmd[5] == prop) {
				return cmdindex;
			}

			cmd = cmd + setupGetCommandLength(cmd);
			cmdindex++;
		}
	}

	return -1;
}

bool modelLoad(s32 propnum)
{
	if (g_ModelStates[propnum].filedata == NULL) {
		g_ModelStates[propnum].filedata = fileLoad(g_ModelStates[propnum].fileid);
		modelCalculateRwDataLen(g_ModelStates[propnum].filedata);
		return true;
	}

	return false;
}

bool func0f09220c(struct defaultobj *obj, struct coord *pos, f32 *realrot, struct coord *arg3, struct coord *arg4)
{
	struct modelrodata_bbox *bbox = objFindBboxRodata(obj);

	if (bbox != NULL) {
		arg3->x = pos->x + func0f0668fc(bbox, realrot);
		arg3->y = pos->y + func0f06695c(bbox, realrot);
		arg3->z = pos->z + func0f0669bc(bbox, realrot);

		arg4->x = pos->x + func0f06692c(bbox, realrot);
		arg4->y = pos->y + func0f06698c(bbox, realrot);
		arg4->z = pos->z + func0f0669ec(bbox, realrot);

		return true;
	}

	return false;
}

bool func0f092304(struct defaultobj *obj, struct coord *arg1, struct coord *arg2)
{
	return func0f09220c(obj, &obj->prop->pos, obj->realrot, arg1, arg2);
}

void func0f09233c(struct defaultobj *obj, struct coord *pos, f32 *realrot, s16 *rooms)
{
	struct coord a;
	struct coord b;
	u32 stack;

	if (func0f09220c(obj, pos, realrot, &a, &b)) {
		a.x -= 1;
		a.y -= 1;
		a.z -= 1;
		b.x += 1;
		b.y += 1;
		b.z += 1;

		func0f1650d0(&a, &b, rooms, 7, 0);
	}
}

void func0f0923d4(struct defaultobj *obj)
{
	propDeregisterRooms(obj->prop);
	func0f09233c(obj, &obj->prop->pos, obj->realrot, obj->prop->rooms);
	propRegisterRooms(obj->prop);
}

struct defaultobj *setupCommandGetObject(u32 cmdindex)
{
	u32 *cmd = setupGetPtrToCommandByIndex(cmdindex);

	if (cmd) {
		switch ((u8)cmd[0]) {
		case OBJTYPE_DOOR:
		case OBJTYPE_BASIC:
		case OBJTYPE_KEY:
		case OBJTYPE_ALARM:
		case OBJTYPE_CCTV:
		case OBJTYPE_AMMOCRATE:
		case OBJTYPE_WEAPON:
		case OBJTYPE_SINGLEMONITOR:
		case OBJTYPE_MULTIMONITOR:
		case OBJTYPE_HANGINGMONITORS:
		case OBJTYPE_AUTOGUN:
		case OBJTYPE_DEBRIS:
		case OBJTYPE_HAT:
		case OBJTYPE_MULTIAMMOCRATE:
		case OBJTYPE_SHIELD:
		case OBJTYPE_GASBOTTLE:
		case OBJTYPE_TRUCK:
		case OBJTYPE_HELI:
		case OBJTYPE_29:
		case OBJTYPE_GLASS:
		case OBJTYPE_SAFE:
		case OBJTYPE_TANK:
		case OBJTYPE_TINTEDGLASS:
		case OBJTYPE_LIFT:
		case OBJTYPE_HOVERBIKE:
		case OBJTYPE_HOVERPROP:
		case OBJTYPE_FAN:
		case OBJTYPE_HOVERCAR:
		case OBJTYPE_CHOPPER:
		case OBJTYPE_ESCASTEP:
			return (struct defaultobj *)cmd;
		case OBJTYPE_DOORSCALE:
		case OBJTYPE_CHR:
		case OBJTYPE_LINKGUNS:
		case OBJTYPE_GRENADEPROB:
		case OBJTYPE_LINKLIFTDOOR:
		case OBJTYPE_TAG:
		case OBJTYPE_BEGINOBJECTIVE:
		case OBJTYPE_ENDOBJECTIVE:
		case OBJECTIVETYPE_DESTROYOBJ:
		case OBJECTIVETYPE_COMPFLAGS:
		case OBJECTIVETYPE_FAILFLAGS:
		case OBJECTIVETYPE_COLLECTOBJ:
		case OBJECTIVETYPE_THROWOBJ:
		case OBJECTIVETYPE_HOLOGRAPH:
		case OBJECTIVETYPE_1F:
		case OBJECTIVETYPE_ENTERROOM:
		case OBJECTIVETYPE_ATTACHOBJ:
		case OBJTYPE_22:
		case OBJTYPE_BRIEFING:
		case OBJTYPE_RENAMEOBJ:
		case OBJTYPE_PADLOCKEDDOOR:
		case OBJTYPE_SAFEITEM:
		case OBJTYPE_CAMERAPOS:
		case OBJTYPE_CONDITIONALSCENERY:
		case OBJTYPE_BLOCKEDPATH:
		case OBJTYPE_PADEFFECT:
			return NULL;
		}
	}

	return (struct defaultobj *)cmd;
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f092484
/*  f092484:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f092488:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f09248c:	3c10800a */ 	lui	$s0,%hi(g_StageSetup+0x10)
/*  f092490:	8e10d040 */ 	lw	$s0,%lo(g_StageSetup+0x10)($s0)
/*  f092494:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f092498:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f09249c:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0924a0:	0080b825 */ 	or	$s7,$a0,$zero
/*  f0924a4:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f0924a8:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f0924ac:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f0924b0:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f0924b4:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0924b8:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0924bc:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f0924c0:	afa60048 */ 	sw	$a2,0x48($sp)
/*  f0924c4:	afa7004c */ 	sw	$a3,0x4c($sp)
/*  f0924c8:	00009025 */ 	or	$s2,$zero,$zero
/*  f0924cc:	1200003f */ 	beqz	$s0,.L0f0925cc
/*  f0924d0:	00009825 */ 	or	$s3,$zero,$zero
/*  f0924d4:	92030003 */ 	lbu	$v1,0x3($s0)
/*  f0924d8:	24010034 */ 	addiu	$at,$zero,0x34
/*  f0924dc:	309e00ff */ 	andi	$s8,$a0,0xff
/*  f0924e0:	1061003a */ 	beq	$v1,$at,.L0f0925cc
/*  f0924e4:	3c160080 */ 	lui	$s6,0x80
/*  f0924e8:	24150008 */ 	addiu	$s5,$zero,0x8
/*  f0924ec:	8fb40054 */ 	lw	$s4,0x54($sp)
/*  f0924f0:	8fb10050 */ 	lw	$s1,0x50($sp)
.L0f0924f4:
/*  f0924f4:	17c3002d */ 	bne	$s8,$v1,.L0f0925ac
/*  f0924f8:	00000000 */ 	nop
/*  f0924fc:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f092500:	8fae004c */ 	lw	$t6,0x4c($sp)
/*  f092504:	14400007 */ 	bnez	$v0,.L0f092524
/*  f092508:	00000000 */ 	nop
/*  f09250c:	15c00027 */ 	bnez	$t6,.L0f0925ac
/*  f092510:	00000000 */ 	nop
/*  f092514:	16200025 */ 	bnez	$s1,.L0f0925ac
/*  f092518:	00000000 */ 	nop
/*  f09251c:	10000030 */ 	b	.L0f0925e0
/*  f092520:	02001025 */ 	or	$v0,$s0,$zero
.L0f092524:
/*  f092524:	12f50021 */ 	beq	$s7,$s5,.L0f0925ac
/*  f092528:	00000000 */ 	nop
/*  f09252c:	8e0f0040 */ 	lw	$t7,0x40($s0)
/*  f092530:	31f80080 */ 	andi	$t8,$t7,0x80
/*  f092534:	1700001d */ 	bnez	$t8,.L0f0925ac
/*  f092538:	00000000 */ 	nop
/*  f09253c:	92190002 */ 	lbu	$t9,0x2($s0)
/*  f092540:	33280004 */ 	andi	$t0,$t9,0x4
/*  f092544:	15000019 */ 	bnez	$t0,.L0f0925ac
/*  f092548:	00000000 */ 	nop
/*  f09254c:	8e090008 */ 	lw	$t1,0x8($s0)
/*  f092550:	01365024 */ 	and	$t2,$t1,$s6
/*  f092554:	15400015 */ 	bnez	$t2,.L0f0925ac
/*  f092558:	00000000 */ 	nop
/*  f09255c:	8c4b0018 */ 	lw	$t3,0x18($v0)
/*  f092560:	15600012 */ 	bnez	$t3,.L0f0925ac
/*  f092564:	00000000 */ 	nop
/*  f092568:	12200005 */ 	beqz	$s1,.L0f092580
/*  f09256c:	02802825 */ 	or	$a1,$s4,$zero
/*  f092570:	0fc2ca34 */ 	jal	func0f0b28d0
/*  f092574:	8e040018 */ 	lw	$a0,0x18($s0)
/*  f092578:	1040000c */ 	beqz	$v0,.L0f0925ac
/*  f09257c:	00000000 */ 	nop
.L0f092580:
/*  f092580:	16400007 */ 	bnez	$s2,.L0f0925a0
/*  f092584:	00000000 */ 	nop
/*  f092588:	8e0c0014 */ 	lw	$t4,0x14($s0)
/*  f09258c:	918d0001 */ 	lbu	$t5,0x1($t4)
/*  f092590:	31ae00c2 */ 	andi	$t6,$t5,0xc2
/*  f092594:	15c00002 */ 	bnez	$t6,.L0f0925a0
/*  f092598:	00000000 */ 	nop
/*  f09259c:	02009025 */ 	or	$s2,$s0,$zero
.L0f0925a0:
/*  f0925a0:	16600002 */ 	bnez	$s3,.L0f0925ac
/*  f0925a4:	00000000 */ 	nop
/*  f0925a8:	02009825 */ 	or	$s3,$s0,$zero
.L0f0925ac:
/*  f0925ac:	0fc24784 */ 	jal	setupGetCommandLength
/*  f0925b0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0925b4:	00027880 */ 	sll	$t7,$v0,0x2
/*  f0925b8:	01f08021 */ 	addu	$s0,$t7,$s0
/*  f0925bc:	92030003 */ 	lbu	$v1,0x3($s0)
/*  f0925c0:	24010034 */ 	addiu	$at,$zero,0x34
/*  f0925c4:	1461ffcb */ 	bne	$v1,$at,.L0f0924f4
/*  f0925c8:	00000000 */ 	nop
.L0f0925cc:
/*  f0925cc:	8fb80044 */ 	lw	$t8,0x44($sp)
/*  f0925d0:	00001025 */ 	or	$v0,$zero,$zero
/*  f0925d4:	af120000 */ 	sw	$s2,0x0($t8)
/*  f0925d8:	8fb90048 */ 	lw	$t9,0x48($sp)
/*  f0925dc:	af330000 */ 	sw	$s3,0x0($t9)
.L0f0925e0:
/*  f0925e0:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0925e4:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0925e8:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f0925ec:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f0925f0:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0925f4:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0925f8:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f0925fc:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f092600:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f092604:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f092608:	03e00008 */ 	jr	$ra
/*  f09260c:	27bd0040 */ 	addiu	$sp,$sp,0x40
);
#else
GLOBAL_ASM(
glabel func0f092484
/*  f090ac8:	27bdffc0 */ 	addiu	$sp,$sp,-64
/*  f090acc:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f090ad0:	3c10800a */ 	lui	$s0,0x800a
/*  f090ad4:	8e101770 */ 	lw	$s0,0x1770($s0)
/*  f090ad8:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f090adc:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f090ae0:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f090ae4:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f090ae8:	0080b825 */ 	or	$s7,$a0,$zero
/*  f090aec:	00e0f025 */ 	or	$s8,$a3,$zero
/*  f090af0:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f090af4:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f090af8:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f090afc:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f090b00:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f090b04:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f090b08:	afa60048 */ 	sw	$a2,0x48($sp)
/*  f090b0c:	00009025 */ 	or	$s2,$zero,$zero
/*  f090b10:	12000039 */ 	beqz	$s0,.NB0f090bf8
/*  f090b14:	00009825 */ 	or	$s3,$zero,$zero
/*  f090b18:	92030003 */ 	lbu	$v1,0x3($s0)
/*  f090b1c:	24010034 */ 	addiu	$at,$zero,0x34
/*  f090b20:	309400ff */ 	andi	$s4,$a0,0xff
/*  f090b24:	10610034 */ 	beq	$v1,$at,.NB0f090bf8
/*  f090b28:	24160008 */ 	addiu	$s6,$zero,0x8
/*  f090b2c:	8fb50054 */ 	lw	$s5,0x54($sp)
/*  f090b30:	8fb10050 */ 	lw	$s1,0x50($sp)
.NB0f090b34:
/*  f090b34:	16830028 */ 	bne	$s4,$v1,.NB0f090bd8
/*  f090b38:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b3c:	8e020014 */ 	lw	$v0,0x14($s0)
/*  f090b40:	14400007 */ 	bnez	$v0,.NB0f090b60
/*  f090b44:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b48:	17c00023 */ 	bnez	$s8,.NB0f090bd8
/*  f090b4c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b50:	16200021 */ 	bnez	$s1,.NB0f090bd8
/*  f090b54:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b58:	1000002c */ 	beqz	$zero,.NB0f090c0c
/*  f090b5c:	02001025 */ 	or	$v0,$s0,$zero
.NB0f090b60:
/*  f090b60:	12f6001d */ 	beq	$s7,$s6,.NB0f090bd8
/*  f090b64:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b68:	8e0e0040 */ 	lw	$t6,0x40($s0)
/*  f090b6c:	31cf0080 */ 	andi	$t7,$t6,0x80
/*  f090b70:	15e00019 */ 	bnez	$t7,.NB0f090bd8
/*  f090b74:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b78:	92180002 */ 	lbu	$t8,0x2($s0)
/*  f090b7c:	33190004 */ 	andi	$t9,$t8,0x4
/*  f090b80:	17200015 */ 	bnez	$t9,.NB0f090bd8
/*  f090b84:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b88:	8c480018 */ 	lw	$t0,0x18($v0)
/*  f090b8c:	15000012 */ 	bnez	$t0,.NB0f090bd8
/*  f090b90:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090b94:	12200005 */ 	beqz	$s1,.NB0f090bac
/*  f090b98:	02a02825 */ 	or	$a1,$s5,$zero
/*  f090b9c:	0fc2c18c */ 	jal	func0f0b28d0
/*  f090ba0:	8e040018 */ 	lw	$a0,0x18($s0)
/*  f090ba4:	1040000c */ 	beqz	$v0,.NB0f090bd8
/*  f090ba8:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f090bac:
/*  f090bac:	16400007 */ 	bnez	$s2,.NB0f090bcc
/*  f090bb0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090bb4:	8e090014 */ 	lw	$t1,0x14($s0)
/*  f090bb8:	912a0001 */ 	lbu	$t2,0x1($t1)
/*  f090bbc:	314b00c2 */ 	andi	$t3,$t2,0xc2
/*  f090bc0:	15600002 */ 	bnez	$t3,.NB0f090bcc
/*  f090bc4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090bc8:	02009025 */ 	or	$s2,$s0,$zero
.NB0f090bcc:
/*  f090bcc:	16600002 */ 	bnez	$s3,.NB0f090bd8
/*  f090bd0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f090bd4:	02009825 */ 	or	$s3,$s0,$zero
.NB0f090bd8:
/*  f090bd8:	0fc24104 */ 	jal	setupGetCommandLength
/*  f090bdc:	02002025 */ 	or	$a0,$s0,$zero
/*  f090be0:	00026080 */ 	sll	$t4,$v0,0x2
/*  f090be4:	01908021 */ 	addu	$s0,$t4,$s0
/*  f090be8:	92030003 */ 	lbu	$v1,0x3($s0)
/*  f090bec:	24010034 */ 	addiu	$at,$zero,0x34
/*  f090bf0:	1461ffd0 */ 	bne	$v1,$at,.NB0f090b34
/*  f090bf4:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f090bf8:
/*  f090bf8:	8fad0044 */ 	lw	$t5,0x44($sp)
/*  f090bfc:	00001025 */ 	or	$v0,$zero,$zero
/*  f090c00:	adb20000 */ 	sw	$s2,0x0($t5)
/*  f090c04:	8fae0048 */ 	lw	$t6,0x48($sp)
/*  f090c08:	add30000 */ 	sw	$s3,0x0($t6)
.NB0f090c0c:
/*  f090c0c:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f090c10:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f090c14:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f090c18:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f090c1c:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f090c20:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f090c24:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f090c28:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f090c2c:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f090c30:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f090c34:	03e00008 */ 	jr	$ra
/*  f090c38:	27bd0040 */ 	addiu	$sp,$sp,0x40
/*  f090c3c:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif
