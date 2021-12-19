#include <ultra64.h>
#include "constants.h"
#include "game/chr/chraction.h"
#include "game/chr/chrai.h"
#include "game/debug.h"
#include "game/dlights.h"
#include "game/game_006900.h"
#include "game/game_01b0a0.h"
#include "game/chr/chr.h"
#include "game/game_02cde0.h"
#include "game/prop.h"
#include "game/game_092610.h"
#include "game/game_095320.h"
#include "game/atan2f.h"
#include "game/game_0969d0.h"
#include "game/bondgun.h"
#include "game/game_0abe70.h"
#include "game/game_0b0fd0.h"
#include "game/game_0b28d0.h"
#include "game/game_0b3350.h"
#include "game/game_0b4950.h"
#include "game/game_0b69d0.h"
#include "game/inventory/inventory.h"
#include "game/game_127910.h"
#include "game/explosions/explosions.h"
#include "game/sparks/sparks.h"
#include "game/bg.h"
#include "game/game_1531a0.h"
#include "game/game_1655c0.h"
#include "game/game_165670.h"
#include "game/game_1657c0.h"
#include "game/lv.h"
#include "game/game_190260.h"
#include "game/game_197600.h"
#include "game/game_1999b0.h"
#include "game/mplayer/mplayer.h"
#include "game/pad.h"
#include "game/padhalllv.h"
#include "game/pak/pak.h"
#include "game/propobj.h"
#include "game/wallhit.h"
#include "game/mpstats.h"
#include "bss.h"
#include "lib/joy.h"
#include "lib/main.h"
#include "lib/model.h"
#include "lib/snd.h"
#include "lib/rng.h"
#include "lib/mtx.h"
#include "lib/ailist.h"
#include "lib/anim.h"
#include "lib/collision.h"
#include "lib/vi.h"
#include "data.h"
#include "types.h"

s32 g_RecentQuipsPlayed[5];
u32 var8009cd84;
u32 var8009cd88;
u32 var8009cd8c;
u32 var8009cd90;
u32 var8009cd94;
u8 g_RecentQuipsIndex;

f32 g_EnemyAccuracyScale = 1;
f32 g_DamageReceivedScale = 1;
f32 g_DamageDealtScale = 1;
f32 var80062cac = 1;

#if VERSION >= VERSION_NTSC_1_0
u32 var80062cb0 = 0x00000000;
u32 var80062cb4 = 0x00000000;
u32 var80062cb8 = 0x00000000;
#endif

s32 var80062cbc = 0;

#if VERSION < VERSION_NTSC_1_0
const char *g_ChrActionNames[] = {
	"ACT_INIT",
	"ACT_STAND",
	"ACT_KNEEL",
	"ACT_ANIM",
	"ACT_DIE",
	"ACT_DEAD",
	"ACT_ARGH",
	"ACT_PREARGH",
	"ACT_ATTACK",
	"ACT_ATTACKWALK",
	"ACT_ATTACKROLL",
	"ACT_SIDESTEP",
	"ACT_JUMPOUT",
	"ACT_RUNPOS",
	"ACT_PATROL",
	"ACT_GOPOS",
	"ACT_SURRENDER",
	"ACT_LOOKATTARGET",
	"ACT_SURPRISED",
	"ACT_STARTALARM",
	"ACT_THROWGRENADE",
	"ACT_TURNDIR",
	"ACT_TEST",
	"ACT_BONDINTRO",
	"ACT_BONDDIE",
	"ACT_BONDMULTI",
	"ACT_NULL",
	"ACT_BOT_ATTACKSTAND",
	"ACT_BOT_ATTACKKNEEL",
	"ACT_BOT_ATTACKSTRAFE",
	"ACT_DRUGGEDDROP",
	"ACT_DRUGGEDKO",
	"ACT_DRUGGEDCOMINGUP",
	"ACT_ATTACKAMOUNT",
	"ACT_ROBOTATTACK",
	"ACT_SKJUMP",
	"ACT_PUNCH",
	"ACT_CUTFIRE",
};

const char *g_ChrMyActionNames[] = {
	"NONE",
	"NORMAL",
	"COVERWAIT",
	"GRENADEWAIT",
	"WAITING",
	"COVERGOTO",
	"COVERBREAK",
	"COVERSEEN",
	"FLANKLEFT",
	"FLANKRIGHT",
	"DODGE",
	"GRENADE",
	"WAITSEEN",
	"WITHDRAW",
	"SHOOTING",
	"SYNCSHOOT",
	"WAITTIMEOUT",
	"COVERTIMEOUT",
	"TRACKING",
	"RETREAT",
	"SURRENDER",
	"TALKING",
	"LISTENING",
	"GOTOALARM",
	"BOTFRIENDFOLLOW",
	"BOTHIDE",
	"BOTPATH",
	"BOTINJURED",
	"BOTNORMAL",
	"BOTSHOOTING",
	"DRUGGED",
	"PANIC",
	"RUNFROMGRENADE",
	"UNARMEDATTACK",
	"MA_SKJUMP_START",
	"MA_SKJUMP_AIR",
	"MA_SKJUMP_LAND",
	"MA_SKJUMP_LANDLOOP",
	"MA_SKJUMP_SHOT",
	"AIBOTDEADLIST",
	"AIBOTINIT",
	"AIBOTMAINLOOP",
	"AIBOTGETITEM",
	"AIBOTGOTOPOS",
	"AIBOTGOTOPROP",
	"AIBOTRUNAWAY",
	"AIBOTDOWNLOAD",
	"AIBOTATTACK",
	"unused1",
	"unused2",
	"AIBOTFOLLOW",
	"AIBOTDEFEND",
	"FLANKBEST",
	"FACING",
	"PUNCHING",
};

const char *g_ChrActionNames2[] = {
	"ACT_INIT",
	"ACT_STAND",
	"ACT_KNEEL",
	"ACT_ANIM",
	"ACT_DIE",
	"ACT_DEAD",
	"ACT_ARGH",
	"ACT_PREARGH",
	"ACT_ATTACK",
	"ACT_ATTACKWALK",
	"ACT_ATTACKROLL",
	"ACT_SIDESTEP",
	"ACT_JUMPOUT",
	"ACT_RUNPOS",
	"ACT_PATROL",
	"ACT_GOPOS",
	"ACT_SURRENDER",
	"ACT_LOOKATTARGET",
	"ACT_SURPRISED",
	"ACT_STARTALARM",
	"ACT_THROWGRENADE",
	"ACT_TURNDIR",
	"ACT_TEST",
	"ACT_BONDINTRO",
	"ACT_BONDDIE",
	"ACT_BONDMULTI",
	"ACT_NULL",
	"ACT_BOT_ATTACKSTAND",
	"ACT_BOT_ATTACKKNEEL",
	"ACT_BOT_ATTACKSTRAFE",
	"ACT_DRUGGEDDROP",
	"ACT_DRUGGEDKO",
	"ACT_DRUGGEDCOMINGUP",
	"ACT_ATTACKAMOUNT",
	"ACT_ROBOTATTACK",
	"ACT_SKJUMP",
};

const char *g_ChrLiftActionNames[] = {
	"NOTUSINGLIFT",
	"WAITINGFORLIFT",
	"ONLIFT",
	"WAITINGONLIFT",
};
#endif


struct animtablerow g_DeathAnimsHumanLfoot[] = {
	{ ANIM_DEATH_0020, 0, -1, 0.5, 0, 26, -1 },
	{ 0,      0,  0, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanLshin[] = {
	{ ANIM_DEATH_0020, 0, -1, 0.5, 0, 26, -1 },
	{ 0,      0,  0, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanLthigh[] = {
	{ ANIM_DEATH_0020, 0, -1, 0.5, 1, 26, -1  },
	{ ANIM_DEATH_STOMACH_LONG, 1, -1, 0.5, 0, -1, -1  },
	{ ANIM_0092, 1, -1, 0.4, 0, 42, 103 },
	{ ANIM_0258, 1, -1, 0.5, 0, 43, 100 },
	{ 0,      0, 0,  0.5, 0, -1, -1  },
};

struct animtablerow g_DeathAnimsHumanRfoot[] = {
	{ ANIM_DEATH_0020, 1, -1, 0.5, 0, 26, -1 },
	{ 0,      0, 0,  0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanRshin[] = {
	{ ANIM_DEATH_0020, 1, -1, 0.5, 0, 26, -1 },
	{ 0,      0, 0,  0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanRthigh[] = {
	{ ANIM_DEATH_0020, 1, -1, 0.5, 1, 26, -1  },
	{ ANIM_DEATH_STOMACH_LONG, 0, -1, 0.5, 0, -1, -1  },
	{ ANIM_0092, 0, -1, 0.4, 0, 42, 103 },
	{ ANIM_0258, 0, -1, 0.5, 0, 43, 100 },
	{ 0,      0, 0,  0.5, 0, -1, -1  },
};

struct animtablerow g_DeathAnimsHumanPelvis[] = {
	{ ANIM_DEATH_001A, 0, -1, 0.5, 0, 55,  39  },
	{ ANIM_DEATH_001A, 1, -1, 0.5, 0, 55,  39  },
	{ ANIM_DEATH_001C, 0, -1, 0.5, 1, 29,  -1  },
	{ ANIM_DEATH_001C, 1, -1, 0.5, 1, 29,  -1  },
	{ ANIM_DEATH_0021, 0, -1, 0.5, 0, 97,  64  },
	{ ANIM_DEATH_0021, 1, -1, 0.5, 0, 97,  64  },
	{ ANIM_DEATH_0023, 0, -1, 0.5, 0, 31,  -1  },
	{ ANIM_DEATH_0023, 1, -1, 0.5, 0, 31,  -1  },
	{ ANIM_DEATH_0024, 0, -1, 0.5, 0, 36,  -1  },
	{ ANIM_DEATH_0024, 1, -1, 0.5, 0, 36,  -1  },
	{ ANIM_DEATH_0025, 0, -1, 0.5, 0, 28,  -1  },
	{ ANIM_DEATH_0025, 1, -1, 0.5, 0, 28,  -1  },
	{ ANIM_0090, 0, -1, 0.6, 0, 157, 234 },
	{ ANIM_0090, 1, -1, 0.6, 0, 157, 234 },
	{ ANIM_0091, 0, -1, 0.6, 0, 75,  265 },
	{ ANIM_0091, 1, -1, 0.6, 0, 75,  265 },
	{ ANIM_0250, 0, -1, 0.5, 0, 65,  105 },
	{ ANIM_0250, 1, -1, 0.5, 0, 65,  105 },
	{ 0,      0, -1, 0.5, 0, -1,  -1  },
};

struct animtablerow g_DeathAnimsHumanHead[] = {
	{ ANIM_DEATH_001A, 0, -1, 0.5, 0, 55,  39  },
	{ ANIM_DEATH_001A, 1, -1, 0.5, 0, 55,  39  },
	{ ANIM_DEATH_001C, 0, -1, 0.5, 1, 29,  -1  },
	{ ANIM_DEATH_001C, 1, -1, 0.5, 1, 29,  -1  },
	{ ANIM_DEATH_0020, 0, -1, 0.5, 1, 26,  -1  },
	{ ANIM_DEATH_0020, 1, -1, 0.5, 1, 26,  -1  },
	{ ANIM_DEATH_0021, 0, -1, 0.5, 0, 97,  64  },
	{ ANIM_DEATH_0021, 1, -1, 0.5, 0, 97,  64  },
	{ ANIM_DEATH_0022, 0, -1, 0.5, 0, 94,  66  },
	{ ANIM_DEATH_0022, 1, -1, 0.5, 0, 94,  66  },
	{ ANIM_DEATH_0023, 0, -1, 0.5, 0, 31,  -1  },
	{ ANIM_DEATH_0023, 1, -1, 0.5, 0, 31,  -1  },
	{ ANIM_DEATH_0024, 0, -1, 0.5, 0, 36,  -1  },
	{ ANIM_DEATH_0024, 1, -1, 0.5, 0, 36,  -1  },
	{ ANIM_DEATH_0025, 0, -1, 0.5, 0, 28,  -1  },
	{ ANIM_DEATH_0025, 1, -1, 0.5, 0, 28,  -1  },
	{ ANIM_0038, 0, -1, 0.5, 0, -1,  -1  },
	{ ANIM_0038, 1, -1, 0.5, 0, -1,  -1  },
	{ ANIM_0251, 0, -1, 0.5, 0, 132, 201 },
	{ ANIM_0251, 1, -1, 0.5, 0, 132, 201 },
	{ ANIM_0252, 0, -1, 0.5, 0, 83,  150 },
	{ ANIM_0252, 1, -1, 0.5, 0, 83,  150 },
	{ ANIM_0256, 0, -1, 0.5, 0, 63,  -1  },
	{ ANIM_0256, 1, -1, 0.5, 0, 63,  -1  },
	{ 0,      0, -1, 0.5, 0, -1,  -1  },
};

struct animtablerow g_DeathAnimsHumanLhand[] = {
	{ ANIM_DEATH_0020, 0, -1, 0.5, 0, 26, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanForearm[] = {
	{ ANIM_DEATH_0020, 0, -1, 0.5, 0, 26, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanLbicep[] = {
	{ ANIM_DEATH_0020, 0, -1, 0.5,  1, 26, -1 },
	{ ANIM_008F, 1, -1, 0.45, 1, 52, -1 },
	{ 0,      0, -1, 0.5,  0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanRhand[] = {
	{ ANIM_DEATH_0020, 1, -1, 0.5, 0, 26, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanRforearm[] = {
	{ ANIM_DEATH_0020, 1, -1, 0.5, 0, 26, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanRbicep[] = {
	{ ANIM_DEATH_0020, 1, -1, 0.5,  1, 26, -1 },
	{ ANIM_008F, 0, -1, 0.45, 1, 52, -1 },
	{ 0,      0, -1, 0.5,  0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanTorso[] = {
	{ ANIM_DEATH_001A, 0, -1, 0.5, 0, 55, 39 },
	{ ANIM_DEATH_001A, 1, -1, 0.5, 0, 55, 39 },
	{ ANIM_DEATH_001C, 0, -1, 0.5, 1, 29, -1 },
	{ ANIM_DEATH_001C, 1, -1, 0.5, 1, 29, -1 },
	{ ANIM_DEATH_0020, 0, -1, 0.5, 1, 26, -1 },
	{ ANIM_DEATH_0020, 1, -1, 0.5, 1, 26, -1 },
	{ ANIM_DEATH_0021, 0, -1, 0.5, 0, 97, 64 },
	{ ANIM_DEATH_0021, 1, -1, 0.5, 0, 97, 64 },
	{ ANIM_DEATH_0022, 0, -1, 0.5, 0, 94, 66 },
	{ ANIM_DEATH_0022, 1, -1, 0.5, 0, 94, 66 },
	{ ANIM_DEATH_0023, 0, -1, 0.5, 0, 31, -1 },
	{ ANIM_DEATH_0023, 1, -1, 0.5, 0, 31, -1 },
	{ ANIM_DEATH_0024, 0, -1, 0.5, 0, 36, -1 },
	{ ANIM_DEATH_0024, 1, -1, 0.5, 0, 36, -1 },
	{ ANIM_DEATH_0025, 0, -1, 0.5, 0, 28, -1 },
	{ ANIM_DEATH_0025, 1, -1, 0.5, 0, 28, -1 },
	{ ANIM_024E, 0, -1, 0.4, 0, 60, -1 },
	{ ANIM_024E, 1, -1, 0.4, 0, 60, -1 },
	{ ANIM_024F, 0, -1, 0.5, 0, 49, 80 },
	{ ANIM_024F, 1, -1, 0.5, 0, 49, 80 },
	{ ANIM_0253, 0, -1, 0.5, 1, 22, -1 },
	{ ANIM_0253, 1, -1, 0.5, 1, 22, -1 },
	{ ANIM_0254, 0, -1, 0.5, 0, 52, 75 },
	{ ANIM_0254, 1, -1, 0.5, 0, 52, 75 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsHumanGun[] = {
	{ ANIM_DEATH_001A, 0, -1, 0.5, 0, 55, 39 },
	{ ANIM_DEATH_001A, 1, -1, 0.5, 0, 55, 39 },
	{ ANIM_DEATH_001C, 0, -1, 0.5, 1, 29, -1 },
	{ ANIM_DEATH_001C, 1, -1, 0.5, 1, 29, -1 },
	{ ANIM_DEATH_0021, 0, -1, 0.5, 0, 97, 64 },
	{ ANIM_DEATH_0021, 1, -1, 0.5, 0, 97, 64 },
	{ ANIM_DEATH_0022, 0, -1, 0.5, 0, 94, 66 },
	{ ANIM_DEATH_0022, 1, -1, 0.5, 0, 94, 66 },
	{ ANIM_DEATH_0023, 0, -1, 0.5, 0, 31, -1 },
	{ ANIM_DEATH_0023, 1, -1, 0.5, 0, 31, -1 },
	{ ANIM_DEATH_0024, 0, -1, 0.5, 0, 36, -1 },
	{ ANIM_DEATH_0024, 1, -1, 0.5, 0, 36, -1 },
	{ ANIM_DEATH_0025, 0, -1, 0.5, 0, 28, -1 },
	{ ANIM_DEATH_0025, 1, -1, 0.5, 0, 28, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_AnimTableHumanSlumped[] = {
	{ ANIM_0019, 0, -1, 0.5, 0, 67, 54 },
	{ ANIM_0019, 1, -1, 0.5, 0, 67, 54 },
	{ ANIM_0257, 0, -1, 0.5, 0, 15, 80 },
	{ ANIM_0257, 1, -1, 0.5, 0, 15, 80 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanLfoot[] = {
	{ ANIM_0014, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0015, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanLshin[] = {
	{ ANIM_0014, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0015, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_00BC, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00BD, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanLthigh[] = {
	{ ANIM_0014, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0015, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_STOMACH_LONG, 1, 20, 0.4, 0, -1, -1 },
	{ ANIM_00BA, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanRfoot[] = {
	{ ANIM_0015, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0014, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_0236, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanRshin[] = {
	{ ANIM_0015, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0014, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_00BE, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanRthigh[] = {
	{ ANIM_0015, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0014, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_STOMACH_LONG, 0, 20, 0.4, 0, -1, -1 },
	{ ANIM_00BF, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanPelvis[] = {
	{ ANIM_DEATH_0022, 0, 20, 0.5,  0, -1, -1 },
	{ ANIM_DEATH_0022, 1, 20, 0.5,  0, -1, -1 },
	{ ANIM_DEATH_001A, 0, 15, 0.5,  0, -1, -1 },
	{ ANIM_DEATH_001A, 1, 15, 0.5,  0, -1, -1 },
	{ ANIM_DEATH_0023, 0, 10, 0.25, 0, -1, -1 },
	{ ANIM_DEATH_0023, 1, 10, 0.25, 0, -1, -1 },
	{ ANIM_00DA, 0, -1, 0.5,  0, -1, -1 },
	{ ANIM_00F4, 0, -1, 0.5,  0, -1, -1 },
	{ 0,      0, -1, 0.5,  0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanHead[] = {
	{ ANIM_DEATH_0022, 0, 20, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_0022, 1, 20, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_001A, 0, 15, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_001A, 1, 15, 0.5, 0, -1, -1 },
	{ ANIM_00F8, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00FB, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0101, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0113, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanLhand[] = {
	{ ANIM_0012, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0013, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B8, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanForearm[] = {
	{ ANIM_0010, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0011, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B4, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_021B, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanLbicep[] = {
	{ ANIM_000E, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_000F, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_0022, 0, 20, 0.5, 0, -1, -1 },
	{ ANIM_00B0, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B1, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_021C, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B5, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanRhand[] = {
	{ ANIM_0013, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0012, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B9, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanRforearm[] = {
	{ ANIM_0011, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0010, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanRbicep[] = {
	{ ANIM_000F, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_000E, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_0022, 1, 20, 0.5, 0, -1, -1 },
	{ ANIM_0190, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B2, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B3, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B6, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_00B7, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanTorso[] = {
	{ ANIM_DEATH_0022, 0, 20, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_0022, 1, 20, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_001A, 0, 15, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_001A, 1, 15, 0.5, 0, -1, -1 },
	{ ANIM_0114, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_0130, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsHumanGun[] = {
	{ ANIM_DEATH_0022, 0, 20, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_0022, 1, 20, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_001A, 0, 15, 0.5, 0, -1, -1 },
	{ ANIM_DEATH_001A, 1, 15, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarLfoot[] = {
	{ ANIM_0337, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_033C, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_033B, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarLshin[] = {
	{ ANIM_0337, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_033C, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_033B, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarLthigh[] = {
	{ ANIM_0337, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_033C, 1, -1, 0.5, 0, -1, -1 },
	{ ANIM_033B, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarRfoot[] = {
	{ ANIM_0337, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033C, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033B, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarRshin[] = {
	{ ANIM_0337, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033C, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033B, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarRthigh[] = {
	{ ANIM_0337, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033C, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033B, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarPelvis[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarHead[] = {
	{ ANIM_0339, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_0338, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033A, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarLhand[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarLforearm[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarLbicep[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarRhand[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarRforearm[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarRbicep[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarTorso[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarGun[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_DeathAnimsSkedarTail[] = {
	{ ANIM_0336, 0, -1, 0.5, 0, -1, -1 },
	{ ANIM_033D, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarLfoot[] = {
	{ ANIM_038E, 0, -1, 1,   0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarLshin[] = {
	{ ANIM_0390, 0, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarLthigh[] = {
	{ ANIM_0390, 0, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarRfoot[] = {
	{ ANIM_038E, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarRshin[] = {
	{ ANIM_0390, 1, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarRthigh[] = {
	{ ANIM_0390, 1, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarPelvis[] = {
	{ ANIM_038C, 0, -1, 0.9, 0, -1, -1 },
	{ ANIM_038C, 1, -1, 0.9, 0, -1, -1 },
	{ ANIM_0341, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarHead[] = {
	{ ANIM_0341, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarLhand[] = {
	{ ANIM_0343, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarLforearm[] = {
	{ ANIM_038B, 0, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarLbicep[] = {
	{ ANIM_038B, 0, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarRhand[] = {
	{ ANIM_0343, 1, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarRforearm[] = {
	{ ANIM_038B, 1, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarRbicep[] = {
	{ ANIM_038B, 1, -1, 0.9, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarTorso[] = {
	{ ANIM_038C, 0, -1, 0.9, 0, -1, -1 },
	{ ANIM_038C, 1, -1, 0.9, 0, -1, -1 },
	{ ANIM_0341, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarGun[] = {
	{ ANIM_0343, 0, -1, 0.5, 0, -1, -1 },
	{ 0,      0, -1, 0.5, 0, -1, -1 },
};

struct animtablerow g_InjuryAnimsSkedarTail[] = {
	{ ANIM_0341, 0, -1, 0.5, 0, -1,  -1  },
	{ 0,      0, -1, 0.5, 0, -1,  -1  },
};

struct animtablerow g_SpecialDieAnims[] = {
	{ ANIM_SPECIALDIE_FALLBACK,    0, -1, 0.5, 0, 149, 175 },
	{ ANIM_SPECIALDIE_ROLL1,       0, -1, 0.5, 0, 115, 152 },
	{ ANIM_SPECIALDIE_ROLL2,       0, -1, 0.5, 0, 115, 152 },
	{ ANIM_SPECIALDIE_ROLL3,       0, -1, 0.5, 0, 115, 152 },
	{ ANIM_SPECIALDIE_OVERRAILING, 0, -1, 0.5, 0, 83,  99  },
	{ ANIM_022B,                   0, -1, 0.5, 0, 0,   0   },
	{ ANIM_022C,                   0, -1, 0.5, 0, 0,   0   },
	{ ANIM_022D,                   0, -1, 0.5, 0, 0,   0   },
	{ ANIM_022E,                   0, -1, 0.5, 0, 0,   0   },
	{ 0,                           0, -1, 0.5, 0, -1,  -1  },
};

struct animtable g_AnimTablesHuman[] = {
	{ 0,                NULL,                      NULL,                       0, 0 },
	{ HITPART_LFOOT,    g_DeathAnimsHumanLfoot,    g_InjuryAnimsHumanLfoot,    0, 0 },
	{ HITPART_LSHIN,    g_DeathAnimsHumanLshin,    g_InjuryAnimsHumanLshin,    0, 0 },
	{ HITPART_LTHIGH,   g_DeathAnimsHumanLthigh,   g_InjuryAnimsHumanLthigh,   0, 0 },
	{ HITPART_RFOOT,    g_DeathAnimsHumanRfoot,    g_InjuryAnimsHumanRfoot,    0, 0 },
	{ HITPART_RSHIN,    g_DeathAnimsHumanRshin,    g_InjuryAnimsHumanRshin,    0, 0 },
	{ HITPART_RTHIGH,   g_DeathAnimsHumanRthigh,   g_InjuryAnimsHumanRthigh,   0, 0 },
	{ HITPART_PELVIS,   g_DeathAnimsHumanPelvis,   g_InjuryAnimsHumanPelvis,   0, 0 },
	{ HITPART_HEAD,     g_DeathAnimsHumanHead,     g_InjuryAnimsHumanHead,     0, 0 },
	{ HITPART_LHAND,    g_DeathAnimsHumanLhand,    g_InjuryAnimsHumanLhand,    0, 0 },
	{ HITPART_LFOREARM, g_DeathAnimsHumanForearm,  g_InjuryAnimsHumanForearm,  0, 0 },
	{ HITPART_LBICEP,   g_DeathAnimsHumanLbicep,   g_InjuryAnimsHumanLbicep,   0, 0 },
	{ HITPART_RHAND,    g_DeathAnimsHumanRhand,    g_InjuryAnimsHumanRhand,    0, 0 },
	{ HITPART_RFOREARM, g_DeathAnimsHumanRforearm, g_InjuryAnimsHumanRforearm, 0, 0 },
	{ HITPART_RBICEP,   g_DeathAnimsHumanRbicep,   g_InjuryAnimsHumanRbicep,   0, 0 },
	{ HITPART_TORSO,    g_DeathAnimsHumanTorso,    g_InjuryAnimsHumanTorso,    0, 0 },
	{ HITPART_GUN,      g_DeathAnimsHumanGun,      g_InjuryAnimsHumanGun,      0, 0 },
	{ HITPART_HAT,      NULL,                      NULL,                       0, 0 },
	{ -1,               NULL,                      NULL,                       0, 0 },
};

struct animtable g_AnimTablesSkedar[] = {
	{ 0,                NULL,                       NULL,                        0, 0 },
	{ HITPART_LFOOT,    g_DeathAnimsSkedarLfoot,    g_InjuryAnimsSkedarLfoot,    0, 0 },
	{ HITPART_LSHIN,    g_DeathAnimsSkedarLshin,    g_InjuryAnimsSkedarLshin,    0, 0 },
	{ HITPART_LTHIGH,   g_DeathAnimsSkedarLthigh,   g_InjuryAnimsSkedarLthigh,   0, 0 },
	{ HITPART_RFOOT,    g_DeathAnimsSkedarRfoot,    g_InjuryAnimsSkedarRfoot,    0, 0 },
	{ HITPART_RSHIN,    g_DeathAnimsSkedarRshin,    g_InjuryAnimsSkedarRshin,    0, 0 },
	{ HITPART_RTHIGH,   g_DeathAnimsSkedarRthigh,   g_InjuryAnimsSkedarRthigh,   0, 0 },
	{ HITPART_PELVIS,   g_DeathAnimsSkedarPelvis,   g_InjuryAnimsSkedarPelvis,   0, 0 },
	{ HITPART_HEAD,     g_DeathAnimsSkedarHead,     g_InjuryAnimsSkedarHead,     0, 0 },
	{ HITPART_LHAND,    g_DeathAnimsSkedarLhand,    g_InjuryAnimsSkedarLhand,    0, 0 },
	{ HITPART_LFOREARM, g_DeathAnimsSkedarLforearm, g_InjuryAnimsSkedarLforearm, 0, 0 },
	{ HITPART_LBICEP,   g_DeathAnimsSkedarLbicep,   g_InjuryAnimsSkedarLbicep,   0, 0 },
	{ HITPART_RHAND,    g_DeathAnimsSkedarRhand,    g_InjuryAnimsSkedarRhand,    0, 0 },
	{ HITPART_RFOREARM, g_DeathAnimsSkedarRforearm, g_InjuryAnimsSkedarRforearm, 0, 0 },
	{ HITPART_RBICEP,   g_DeathAnimsSkedarRbicep,   g_InjuryAnimsSkedarRbicep,   0, 0 },
	{ HITPART_TORSO,    g_DeathAnimsSkedarTorso,    g_InjuryAnimsSkedarTorso,    0, 0 },
	{ HITPART_GUN,      g_DeathAnimsSkedarGun,      g_InjuryAnimsSkedarGun,      0, 0 },
	{ HITPART_HAT,      g_DeathAnimsSkedarHead,     g_InjuryAnimsSkedarHead,     0, 0 },
	{ HITPART_TAIL,     g_DeathAnimsSkedarTail,     g_InjuryAnimsSkedarTail,     0, 0 },
	{ -1,               NULL,                       NULL,                        0, 0 },
};

struct animtable g_AnimTablesDrCaroll[] = {
	{ 0,  NULL, NULL, 0, 0 },
	{ -1, NULL, NULL, 0, 0 },
};

struct animtable g_AnimTablesEyespy[] = {
	{ 0,  NULL, NULL, 0, 0 },
	{ -1, NULL, NULL, 0, 0 },
};

struct animtable g_AnimTablesRobot[] = {
	{ 0,  NULL, NULL, 0, 0 },
	{ -1, NULL, NULL, 0, 0 },
};

struct animtable *g_AnimTablesByRace[] = {
	g_AnimTablesHuman,
	g_AnimTablesSkedar,
	g_AnimTablesDrCaroll,
	g_AnimTablesEyespy,
	g_AnimTablesRobot,
};

/**
 * A yeet anim is an animation config for a chr being launched by an explosion.
 */
struct yeetanim {
	s16 animnum;
	bool flip;
	f32 speed;
	f32 startframe;
	f32 thudframe;
	f32 endframe;
};

struct yeetanim g_YeetAnimsHuman[] = {
	/* 0*/ { ANIM_0082, 0, 0.5, 9,  29, -1 },
	/* 1*/ { ANIM_0082, 1, 0.5, 9,  29, -1 },
	/* 2*/ { ANIM_008A, 0, 0.5, 11, 31, -1 },
	/* 3*/ { ANIM_008A, 1, 0.5, 11, 31, -1 },
	/* 4*/ { ANIM_0089, 0, 0.5, 6,  27, -1 },
	/* 5*/ { ANIM_0089, 1, 0.5, 6,  27, -1 },
	/* 6*/ { ANIM_008C, 0, 0.5, 29, 48, -1 },
	/* 7*/ { ANIM_008C, 1, 0.5, 29, 48, -1 },
	/* 8*/ { ANIM_008D, 0, 0.5, 29, 49, -1 },
	/* 9*/ { ANIM_008D, 1, 0.5, 29, 49, -1 },
	/*10*/ { ANIM_008E, 0, 0.5, 19, 42, -1 },
	/*11*/ { ANIM_008E, 1, 0.5, 19, 42, -1 },
	/*12*/ { ANIM_0086, 0, 0.5, 0,  60, -1 },
	/*13*/ { ANIM_0086, 1, 0.5, 0,  60, -1 },
	/*14*/ { ANIM_0087, 0, 0.5, 6,  29, -1 },
	/*15*/ { ANIM_0087, 1, 0.5, 6,  29, -1 },
	/*16*/ { ANIM_0084, 0, 0.5, 8,  25, -1 },
	/*17*/ { ANIM_0084, 1, 0.5, 8,  25, -1 },
	/*18*/ { ANIM_0085, 0, 0.5, 8,  25, -1 },
	/*19*/ { ANIM_0085, 1, 0.5, 8,  25, -1 },
	/*20*/ { ANIM_0088, 0, 0.5, 12, 29, -1 },
	/*21*/ { ANIM_0088, 1, 0.5, 12, 29, -1 },
	/*22*/ { ANIM_008B, 0, 0.5, 22, 41, -1 },
	/*23*/ { ANIM_008B, 1, 0.5, 22, 41, -1 },
	/*24*/ { 0,         0, 0.5, 0,  0,  -1 },
};

s8 g_YeetAnimIndexesHumanAngle0[] = { 0,  1,  2,  3, 4, 5 };
s8 g_YeetAnimIndexesHumanAngle1[] = { 7,  9,  11          };
s8 g_YeetAnimIndexesHumanAngle2[] = { 6,  8,  10          };
s8 g_YeetAnimIndexesHumanAngle3[] = { 12, 15, 0           };
s8 g_YeetAnimIndexesHumanAngle4[] = { 13, 14, 0           };
s8 g_YeetAnimIndexesHumanAngle5[] = { 18, 19, 20, 21      };
s8 g_YeetAnimIndexesHumanAngle6[] = { 16, 22              };
s8 g_YeetAnimIndexesHumanAngle7[] = { 17, 23              };

struct yeetanim g_YeetAnimsSkedar[] = {
	/* 0*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 1*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 2*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 3*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 4*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 5*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 6*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 7*/ { ANIM_033F, 0, 0.5, 0, -1, -1 },
	/* 8*/ { 0,         0, 0.5, 0, 0,  -1 },
};

s8 g_YeetAnimIndexesSkedarAngle0[] = { 0 };
s8 g_YeetAnimIndexesSkedarAngle1[] = { 1 };
s8 g_YeetAnimIndexesSkedarAngle2[] = { 2 };
s8 g_YeetAnimIndexesSkedarAngle3[] = { 3 };
s8 g_YeetAnimIndexesSkedarAngle4[] = { 4 };
s8 g_YeetAnimIndexesSkedarAngle5[] = { 7 };
s8 g_YeetAnimIndexesSkedarAngle6[] = { 5 };
s8 g_YeetAnimIndexesSkedarAngle7[] = { 6 };

struct yeetanimindexlist {
	s8 *indexes;
	s32 count;
};

struct yeetanimindexlist g_YeetAnimIndexesByRaceAngle[][8] = {
	{
		{ g_YeetAnimIndexesHumanAngle0, 6 },
		{ g_YeetAnimIndexesHumanAngle1, 3 },
		{ g_YeetAnimIndexesHumanAngle3, 3 },
		{ g_YeetAnimIndexesHumanAngle6, 2 },
		{ g_YeetAnimIndexesHumanAngle5, 4 },
		{ g_YeetAnimIndexesHumanAngle7, 2 },
		{ g_YeetAnimIndexesHumanAngle4, 3 },
		{ g_YeetAnimIndexesHumanAngle2, 3 },
	}, {
		{ g_YeetAnimIndexesSkedarAngle0, 1 },
		{ g_YeetAnimIndexesSkedarAngle1, 1 },
		{ g_YeetAnimIndexesSkedarAngle3, 1 },
		{ g_YeetAnimIndexesSkedarAngle6, 1 },
		{ g_YeetAnimIndexesSkedarAngle5, 1 },
		{ g_YeetAnimIndexesSkedarAngle7, 1 },
		{ g_YeetAnimIndexesSkedarAngle4, 1 },
		{ g_YeetAnimIndexesSkedarAngle2, 1 },
	},
};

struct attackanimconfig var800656c0[] = {
	{ ANIM_0002, 28, 0, 0, 0, -1, 23, 54, -1, -1, 18, 54, 0.87252569198608, -0.52351540327072, 1.0470308065414, -0.34901028871536, 1.6000000238419, 1.7999999523163 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,               0,                 0,               0               },
};

struct attackanimgroup var80065750 = { var800656c0, 0xffffffff };

struct attackanimconfig var80065758[] = {
	{ ANIM_0032, 37, 0, 0, 0, -1, 30, 81, -1, -1, 25, 81, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 1.6000000238419, 1.75 },
	{ ANIM_0003, 27, 0, 0, 0, -1, 22, 61, -1, -1, 17, 61, 0.87252569198608, -0.26175770163536, 0.69802057743073, -0.69802057743073, 2,               1    },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0,               0    },
};

struct attackanimgroup var80065830 = { var80065758, 0xffffffff };

struct attackanimconfig var80065838[] = {
	{ ANIM_0032, 37, 0, 0, 0, -1, 30, 81, -1, -1, 25, 81, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 1.6000000238419, 1.75 },
	{ ANIM_0003, 27, 0, 0, 0, -1, 22, 61, -1, -1, 17, 61, 0.87252569198608, -0.26175770163536, 0.69802057743073, -0.69802057743073, 2,               1    },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0,               0    },
};

struct attackanimgroup var80065910 = { var80065838, 0xffffffff };

struct attackanimconfig var80065918[] = {
	{ ANIM_0004, 19, 0, 1.5707963705063, 0, -1, 19, 61, -1, -1, 14, 61, 0.87252569198608, -0.34901028871536, 0.43626284599304, -1.0470308065414, 2.5, 2.5 },
	{ 0, 0,  0, 0,               0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                0,   0   },
};

struct attackanimgroup var800659a8 = { var80065918, 0xffffffff };

struct attackanimconfig var800659b0[] = {
	{ ANIM_0006, 27, 0, 0, 0, -1, 39, 74, -1, -1, 34, 74, 0.87252569198608, -0.69802057743073, 0.7852731347084, -0.69802057743073, 1.5, 1.5 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,               0,                 0,   0   },
};

struct attackanimgroup var80065a40 = { var800659b0, 0xffffffff };

struct attackanimconfig var80065a48[] = {
	{ ANIM_034A, 20, 0, 0, 0, -1, 25, 50, -1, -1, 10, 50, 0.34901028871536, -0.34901028871536, 0.52351540327072, -0.52351540327072, 1, 1 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80065ad8 = { var80065a48, 0xffffffff };

struct attackanimgroup *g_StandHeavyAttackAnims[][32] = {
	{
		// RACE_HUMAN
		&var80065750, &var80065830, &var80065830, &var80065830,
		&var80065830, &var80065830, &var80065830, &var80065830,
		&var80065830, &var80065830, &var800659a8, &var800659a8,
		&var800659a8, &var800659a8, &var800659a8, &var800659a8,
		&var80065a40, &var80065a40, &var80065a40, &var80065a40,
		&var80065a40, &var80065a40, &var80065910, &var80065910,
		&var80065910, &var80065910, &var80065910, &var80065910,
		&var80065910, &var80065910, &var80065910, &var80065750,
	}, {
		// RACE_SKEDAR
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
		&var80065ad8, &var80065ad8, &var80065ad8, &var80065ad8,
	},
};

struct attackanimconfig var80065be0[] = {
	{ ANIM_0041, 26, 0, 0, 12, 140, 58, 92, 60, 79, 20, 120, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 0, 0 },
	{ ANIM_0044, 0,  0, 0, 17, 100, 25, 87, 30, 55, 20, 93,  0.87252569198608, -0.69802057743073, 0.69802057743073, -1.0470308065414,  0, 0 },
	{ ANIM_0045, 0,  0, 0, 12, 64,  19, 51, 24, 46, 14, 58,  0.87252569198608, -0.69802057743073, 0.52351540327072, -0.7852731347084,  0, 0 },
	{ ANIM_0046, 22, 0, 0, 4,  69,  22, 49, 22, 33, 8,  58,  0.87252569198608, -0.69802057743073, 0.43626284599304, -0.7852731347084,  0, 0 },
	{ 0, 0,  0, 0, 0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80065d48 = { var80065be0, 0xffffffff };

struct attackanimconfig var80065d50[] = {
	{ ANIM_0041, 26, 0, 0, 12, 140, 58, 92, 60, 79, 20, 120, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 0, 0 },
	{ ANIM_0046, 22, 0, 0, 4,  69,  22, 49, 22, 33, 8,  58,  0.87252569198608, -0.69802057743073, 0.43626284599304, -0.7852731347084,  0, 0 },
	{ 0, 0,  0, 0, 0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80065e28 = { var80065d50, 0xffffffff };

struct attackanimconfig var80065e30[] = {
	{ ANIM_0041, 26, 0, 0,               12, 140, 58, 92, 60, 79, 20, 120, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 0, 0 },
	{ ANIM_0046, 22, 0, 0,               4,  69,  22, 49, 22, 33, 8,  58,  0.87252569198608, -0.69802057743073, 0.43626284599304, -0.7852731347084,  0, 0 },
	{ ANIM_0049, 0,  0, 1.5707963705063, 7,  130, 45, 93, 56, 73, 26, 107, 0.87252569198608, -0.69802057743073, 0.34901028871536, -0.52351540327072, 0, 0 },
	{ ANIM_004A, 15, 0, 1.5707963705063, 5,  76,  20, 31, 31, 38, 15, 49,  0.87252569198608, -0.69802057743073, 0.52351540327072, -1.0470308065414,  0, 0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80065f98 = { var80065e30, 0xffffffff };

struct attackanimconfig var80065fa0[] = {
	{ ANIM_0041, 26, 0, 0,               12, 140, 58, 92,  60, 79, 20, 120, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 0, 0 },
	{ ANIM_0046, 22, 0, 0,               4,  69,  22, 49,  22, 33, 8,  58,  0.87252569198608, -0.69802057743073, 0.43626284599304, -0.7852731347084,  0, 0 },
	{ ANIM_0047, 0,  0, 4.7123889923096, 7,  139, 54, 105, 61, 88, 26, 120, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.61076802015305, 0, 0 },
	{ ANIM_0048, 19, 0, 4.7123889923096, 4,  79,  21, 50,  26, 42, 10, 64,  0.87252569198608, -0.69802057743073, 0.69802057743073, -0.61076802015305, 0, 0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,   0,  0,  0,  0,   0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066108 = { var80065fa0, 0xffffffff };

struct attackanimconfig var80066110[] = {
	{ ANIM_004A, 19, 0, 1.5707963705063, 5, 76, 20, 31, 31, 38, 15, 49, 0.87252569198608, -0.69802057743073, 0.52351540327072, -1.0470308065414, 0, 0 },
	{ 0, 0,  0, 0,               0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                0, 0 },
};

struct attackanimgroup var800661a0 = { var80066110, 0xffffffff };

struct attackanimconfig var800661a8[] = {
	{ ANIM_0048, 19, 0, 4.7123889923096, 4, 79, 21, 50, 26, 42, 10, 64, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.61076802015305, 0, 0 },
	{ 0, 0,  0, 0,               0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066238 = { var800661a8, 0xffffffff };

struct attackanimconfig var80066240[] = {
	{ ANIM_034A, 20, 0, 0, 0, -1, 25, 50, -1, -1, 10, 50, 0.34901028871536, -0.34901028871536, 0.52351540327072, -0.52351540327072, 1, 1 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var800662d0 = { var80066240, 0xffffffff };

struct attackanimgroup *g_StandLightAttackAnims[][32] = {
	{
		// RACE_HUMAN
		&var80065d48, &var80065d48, &var80065e28, &var80065e28,
		&var80065e28, &var80065f98, &var80065f98, &var80065f98,
		&var80065f98, &var80065f98, &var800661a0, &var800661a0,
		&var800661a0, &var800661a0, &var800661a0, &var800661a0,
		&var80066238, &var80066238, &var80066238, &var80066238,
		&var80066238, &var80066238, &var80066108, &var80066108,
		&var80066108, &var80066108, &var80066108, &var80065e28,
		&var80065e28, &var80065e28, &var80065d48, &var80065d48,
	}, {
		// RACE_SKEDAR
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
		&var800662d0, &var800662d0, &var800662d0, &var800662d0,
	},
};


struct attackanimconfig var800663d8[] = {
	{ ANIM_007A, 26, 0, 0, 7, 92, 28, 68, -1, -1, 11, 73, 0.87252569198608, -0.69802057743073, 0.69802057743073, -0.69802057743073, 0, 0 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066468 = { var800663d8, 0xffffffff };

struct attackanimconfig var80066470[] = {
	{ ANIM_007B, 26, 0, 1.5707963705063, 9,  112, 38, 87, -1, -1, 19, 98, 0.87252569198608, -0.69802057743073, 0.43626284599304, -0.43626284599304, 0, 0 },
	{ ANIM_007D, 25, 0, 1.5707963705063, 10, 112, 32, 86, -1, -1, 19, 97, 0.87252569198608, -0.69802057743073, 0.43626284599304, -0.43626284599304, 0, 0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066548 = { var80066470, 0xffffffff };

struct attackanimconfig var80066550[] = {
	{ ANIM_007C, 39, 0, 4.7123889923096, 22, 127, 44, 102, -1, -1, 28, 112, 0.87252569198608, -0.69802057743073, 0.43626284599304, -0.43626284599304, 0, 0 },
	{ ANIM_007E, 39, 0, 4.7123889923096, 23, 130, 46, 100, -1, -1, 30, 110, 0.87252569198608, -0.69802057743073, 0.43626284599304, -0.43626284599304, 0, 0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,   0,  0,  0,  0,   0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066628 = { var80066550, 0xffffffff };

struct attackanimconfig var80066630[] = {
	{ ANIM_034A, 20, 0, 0, 0, -1, 25, 50, -1, -1, 10, 50, 0.34901028871536, -0.34901028871536, 0.52351540327072, -0.52351540327072, 1, 1 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var800666c0 = { var80066630, 0xffffffff };

struct attackanimgroup *g_StandDualAttackAnims[][32] = {
	{
		// RACE_HUMAN
		&var80066468, &var80066468, &var80066468, &var80066468,
		&var80066468, &var80066548, &var80066548, &var80066548,
		&var80066548, &var80066548, &var80066548, &var80066548,
		&var80066548, &var80066548, &var80066548, &var80066548,
		&var80066628, &var80066628, &var80066628, &var80066628,
		&var80066628, &var80066628, &var80066628, &var80066628,
		&var80066628, &var80066628, &var80066628, &var80066468,
		&var80066468, &var80066468, &var80066468, &var80066468,
	}, {
		// RACE_SKEDAR
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
		&var800666c0, &var800666c0, &var800666c0, &var800666c0,
	},
};

struct attackanimconfig var800667c8[] = {
	{ ANIM_0007, 27, 0, 0, 0, -1, 35, 75, -1, -1, 31, 75, 0.87252569198608, -0.69802057743073, 0.90742671489716, -0.69802057743073, 1.5,             1.5             },
	{ ANIM_KNEEL_TWO_HANDED_GUN, 24, 0, 0, 0, -1, 46, 98, -1, -1, 41, 98, 0.87252569198608, -0.52351540327072, 1.1342834234238,  -0.69802057743073, 1.6000000238419, 1.6000000238419 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0,               0               },
};

struct attackanimgroup var800668a0 = { var800667c8, 0xffffffff };

struct attackanimconfig var800668a8[] = {
	{ ANIM_0009, 26, 0, 0, 0, -1, 34, 87, -1, -1, 29, 87, 0.87252569198608, -0.52351540327072, 0.69802057743073, -0.95977824926376, 1.6000000238419, 2 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0,               0 },
};

struct attackanimgroup var80066938 = { var800668a8, 0xffffffff };

struct attackanimconfig var80066940[] = {
	{ ANIM_000A, 28, 0, 0, 0, -1, 36, 88, -1, -1, 31, 88, 0.87252569198608, -0.69802057743073, 0.87252569198608, -0.43626284599304, 1.6000000238419, 1.5 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0,               0   },
};

struct attackanimgroup var800669d0 = { var80066940, 0xffffffff };

struct attackanimconfig var800669d8[] = {
	{ ANIM_034A, 20, 0, 0, 0, -1, 25, 50, -1, -1, 10, 50, 0.34901028871536, -0.34901028871536, 0.52351540327072, -0.52351540327072, 1, 1 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066a68 = { var800669d8, 0xffffffff };

struct attackanimgroup *g_KneelHeavyAttackAnims[][32] = {
	{
		&var800668a0, &var800668a0, &var800668a0, &var800668a0,
		&var800668a0, &var800668a0, &var800668a0, &var800668a0,
		&var800668a0, &var800668a0, &var80066938, &var80066938,
		&var80066938, &var80066938, &var80066938, &var80066938,
		&var800669d0, &var800669d0, &var800669d0, &var800669d0,
		&var800669d0, &var800669d0, &var800668a0, &var800668a0,
		&var800668a0, &var800668a0, &var800668a0, &var800668a0,
		&var800668a0, &var800668a0, &var800668a0, &var800668a0,
	}, {
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
		&var80066a68, &var80066a68, &var80066a68, &var80066a68,
	},
};

struct attackanimconfig var80066b70[] = {
	{ ANIM_KNEEL_SHOOT_RIGHT_HAND, 25, 0, 0, 12, 132, 55, 87, 67, 87, 26, 111, 0.87252569198608, -0.69802057743073, 0.61076802015305, -0.7852731347084, 0, 0 },
	{ ANIM_004C, 26, 0, 0, 8,  89,  31, 63, 41, 51, 21, 80,  0.87252569198608, -0.69802057743073, 0.34901028871536, -1.1342834234238, 0, 0 },
	{ 0, 0,  0, 0, 0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                 0,                0,                0, 0 },
};

struct attackanimgroup var80066c48 = { var80066b70, 0xffffffff };

struct attackanimconfig var80066c50[] = {
	{ ANIM_004F, 47, 0, 1.5707963705063, 7,  128, 33, 86, 47, 74, 23, 106, 0.87252569198608, -0.52351540327072,  0.52351540327072, -0.7852731347084,  0,   0 },
	{ ANIM_0050, 18, 0, 1.5707963705063, 7,  78,  28, 52, 35, 45, 15, 66,  0.87252569198608, -0.087252572178841, 0.69802057743073, -0.7852731347084,  1.5, 1 },
	{ ANIM_0051, 20, 0, 1.5707963705063, 13, 92,  37, 67, 42, 55, 25, 84,  0.87252569198608, -0.52351540327072,  0.34901028871536, -0.69802057743073, 0,   0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                  0,                0,                 0,   0 },
};

struct attackanimgroup var80066d70 = { var80066c50, 0xffffffff };

struct attackanimconfig var80066d78[] = {
	{ ANIM_004D, 28, 0, 4.7123889923096, 15, 124, 38, 97, 60, 84, 20, 106, 0.87252569198608, -0.69802057743073, 0.52351540327072, -0.87252569198608, 0, 0 },
	{ ANIM_004E, 23, 0, 4.7123889923096, 0,  85,  32, 38, 38, 60, 14, 71,  0.87252569198608, -0.69802057743073, 0.61076802015305, -0.95977824926376, 0, 0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066e50 = { var80066d78, 0xffffffff };

struct attackanimconfig var80066e58[] = {
	{ ANIM_034A, 20, 0, 0, 0, -1, 25, 50, -1, -1, 10, 50, 0.34901028871536, -0.34901028871536, 0.52351540327072, -0.52351540327072, 1, 1 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80066ee8 = { var80066e58, 0xffffffff };

struct attackanimgroup *g_KneelLightAttackAnims[][32] = {
	{
		&var80066c48, &var80066c48, &var80066c48, &var80066c48,
		&var80066c48, &var80066c48, &var80066c48, &var80066c48,
		&var80066c48, &var80066c48, &var80066d70, &var80066d70,
		&var80066d70, &var80066d70, &var80066d70, &var80066d70,
		&var80066e50, &var80066e50, &var80066e50, &var80066e50,
		&var80066e50, &var80066e50, &var80066c48, &var80066c48,
		&var80066c48, &var80066c48, &var80066c48, &var80066c48,
		&var80066c48, &var80066c48, &var80066c48, &var80066c48,
	}, {
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
		&var80066ee8, &var80066ee8, &var80066ee8, &var80066ee8,
	},
};

struct attackanimconfig var80066ff0[] = {
	{ ANIM_0074, 22, 0, 0, 10, 111, 34, 87, -1, -1, 17, 104, 0.87252569198608, -0.69802057743073, 0.61076802015305, -0.7852731347084, 0, 0 },
	{ ANIM_0077, 25, 0, 0, 9,  92,  33, 62, -1, -1, 18, 69,  0.87252569198608, -0.69802057743073, 0.61076802015305, -0.7852731347084, 0, 0 },
	{ 0, 0,  0, 0, 0,  -1,  0,  0,  0,  0,  0,  0,   0,                0,                 0,                0,                0, 0 },
};

struct attackanimgroup var800670c8 = { var80066ff0, 0xffffffff };

struct attackanimconfig var800670d0[] = {
	{ ANIM_0075, 28, 0, 1.5707963705063, 15, 108, 34, 73, -1, -1, 17, 93, 0.87252569198608, -0.69802057743073, 0.52351540327072, -0.7852731347084, 0,   0 },
	{ ANIM_0078, 19, 0, 1.5707963705063, 3,  95,  30, 64, -1, -1, 14, 71, 0.87252569198608, -0.69802057743073, 0.52351540327072, -0.7852731347084, 1.5, 1 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                0,   0 },
};

struct attackanimgroup var800671a8 = { var800670d0, 0xffffffff };

struct attackanimconfig var800671b0[] = {
	{ ANIM_0076, 31, 0, 4.7123889923096, 14, 111, 40, 83, -1, -1, 21, 94, 0.87252569198608, -0.69802057743073, 0.52351540327072, -0.7852731347084, 0, 0 },
	{ ANIM_0079, 26, 0, 4.7123889923096, 7,  89,  34, 60, -1, -1, 20, 68, 0.87252569198608, -0.69802057743073, 0.52351540327072, -0.7852731347084, 0, 0 },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                0, 0 },
};

struct attackanimgroup var80067288 = { var800671b0, 0xffffffff };

struct attackanimconfig var80067290[] = {
	{ ANIM_034A, 20, 0, 0, 0, -1, 25, 50, -1, -1, 10, 50, 0.34901028871536, -0.34901028871536, 0.52351540327072, -0.52351540327072, 1, 1 },
	{ 0, 0,  0, 0, 0, -1, 0,  0,  0,  0,  0,  0,  0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80067320 = { var80067290, 0xffffffff };

struct attackanimgroup *g_KneelDualAttackAnims[][32] = {
	{
		&var800670c8, &var800670c8, &var800670c8, &var800670c8,
		&var800670c8, &var800670c8, &var800670c8, &var800670c8,
		&var800670c8, &var800670c8, &var800671a8, &var800671a8,
		&var800671a8, &var800671a8, &var800671a8, &var800671a8,
		&var80067288, &var80067288, &var80067288, &var80067288,
		&var80067288, &var80067288, &var800670c8, &var800670c8,
		&var800670c8, &var800670c8, &var800670c8, &var800670c8,
		&var800670c8, &var800670c8, &var800670c8, &var800670c8,
	}, {
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
		&var80067320, &var80067320, &var80067320, &var80067320,
	},
};

struct attackanimconfig g_RollAttackAnims[] = {
	{ ANIM_000B, 76, 0, 0,               20, -1,  98, 161, -1, -1, 93, 161, 0.87252569198608, -0.52351540327072,  0.69802057743073, -0.69802057743073, 1.7000000476837, 2               },
	{ ANIM_000C, 58, 0, 0,               10, -1,  77, 104, -1, -1, 72, 104, 0.87252569198608, -0.34901028871536,  0.61076802015305, -0.69802057743073, 1.5499999523163, 1.5             },
	{ ANIM_000D, 61, 0, 0,               10, -1,  83, 128, -1, -1, 78, 128, 0.87252569198608, -0.52351540327072,  0.87252569198608, -0.52351540327072, 1.2000000476837, 1.2999999523163 },
	{ ANIM_0027, 63, 0, 0,               10, -1,  73, 114, -1, -1, 68, 114, 0.87252569198608, -0.52351540327072,  0.61076802015305, -0.61076802015305, 1.6499999761581, 1.5             },
	{ ANIM_000B, 76, 0, 0,               20, 76,  98, 161, -1, -1, 93, 161, 0.87252569198608, -0.52351540327072,  0.69802057743073, -0.69802057743073, 1.7000000476837, 2               },
	{ ANIM_000C, 58, 0, 0,               10, 63,  77, 104, -1, -1, 72, 104, 0.87252569198608, -0.34901028871536,  0.61076802015305, -0.69802057743073, 1.5499999523163, 1.5             },
	{ ANIM_000D, 61, 0, 0,               10, 56,  83, 128, -1, -1, 78, 128, 0.87252569198608, -0.52351540327072,  0.87252569198608, -0.52351540327072, 1.2000000476837, 1.2999999523163 },
	{ ANIM_0027, 63, 0, 0,               10, 50,  73, 114, -1, -1, 68, 114, 0.87252569198608, -0.52351540327072,  0.61076802015305, -0.61076802015305, 1.6499999761581, 1.5             },
	{ ANIM_0045, 0,  0, 0,               7,  64,  19, 51,  24, 46, 14, 58,  0.87252569198608, -0.69802057743073,  0.52351540327072, -0.7852731347084,  0,               0               },
	{ ANIM_004A, 0,  0, 1.5707963705063, 14, 76,  26, 31,  31, 38, 15, 49,  0.87252569198608, -0.69802057743073,  0.52351540327072, -1.0470308065414,  0,               0               },
	{ ANIM_004C, 26, 0, 0,               25, 89,  41, 63,  41, 51, 21, 80,  0.87252569198608, -0.69802057743073,  0.34901028871536, -1.1342834234238,  0,               0               },
	{ ANIM_0050, 18, 0, 1.5707963705063, 11, 78,  33, 52,  35, 45, 15, 66,  0.87252569198608, -0.087252572178841, 0.69802057743073, -0.7852731347084,  1.5,             1               },
	{ ANIM_007A, 26, 0, 0,               7,  92,  28, 68,  -1, -1, 11, 73,  0.87252569198608, -0.69802057743073,  0.69802057743073, -0.69802057743073, 0,               0               },
	{ ANIM_007B, 26, 0, 1.5707963705063, 9,  112, 38, 87,  -1, -1, 19, 98,  0.87252569198608, -0.69802057743073,  0.43626284599304, -0.43626284599304, 0,               0               },
	{ ANIM_0074, 22, 0, 0,               10, 11,  34, 87,  -1, -1, 17, 104, 0.87252569198608, -0.69802057743073,  0.61076802015305, -0.7852731347084,  0,               0               },
	{ ANIM_0075, 28, 0, 1.5707963705063, 15, 108, 34, 73,  -1, -1, 17, 93,  0.87252569198608, -0.69802057743073,  0.52351540327072, -0.7852731347084,  0,               0               },
	{ ANIM_007A, 26, 0, 0,               7,  92,  28, 68,  -1, -1, 11, 73,  0.87252569198608, -0.69802057743073,  0.69802057743073, -0.69802057743073, 0,               0               },
	{ ANIM_007D, 25, 0, 1.5707963705063, 10, 112, 32, 86,  -1, -1, 19, 97,  0.87252569198608, -0.69802057743073,  0.43626284599304, -0.43626284599304, 0,               0               },
	{ ANIM_0077, 25, 0, 0,               9,  92,  33, 62,  -1, -1, 18, 69,  0.87252569198608, -0.69802057743073,  0.61076802015305, -0.7852731347084,  0,               0               },
	{ ANIM_0078, 19, 0, 1.5707963705063, 3,  95,  30, 64,  -1, -1, 14, 71,  0.87252569198608, -0.69802057743073,  0.52351540327072, -0.7852731347084,  1.5,             1               },
	{ 0, 0,  0, 0,               0,  -1,  0,  0,   0,  0,  0,  0,   0,                0,                  0,                0,                 0,               0               },
};

struct attackanimconfig g_AttackAnimHeavyWalk       = { ANIM_0030, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 1.3999999761581, 1.2999999523163 };
struct attackanimconfig g_AttackAnimHeavyRun        = { ANIM_0031, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 1.1000000238419, 1.2000000476837 };
struct attackanimconfig g_AttackAnimLightWalk       = { ANIM_0052, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0,               0               };
struct attackanimconfig g_AttackAnimLightRun        = { ANIM_0055, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0,               0               };
struct attackanimconfig g_AttackAnimDualWalk        = { ANIM_006C, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0,               0               };
struct attackanimconfig g_AttackAnimDualRun         = { ANIM_006E, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0,               0               };
struct attackanimconfig g_AttackAnimDualCrossedWalk = { ANIM_006D, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0,               0               };
struct attackanimconfig g_AttackAnimDualCrossedRun  = { ANIM_006F, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0,               0               };

struct attackanimconfig var80067c50[] = {
	{ ANIM_0057, 0, 0, 1.5707963705063, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0, 0 },
	{ ANIM_0056, 0, 0, 4.7123889923096, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0, 0 },
	{ 0, 0, 0, 0,               0, -1, 0, 0, 0,  0,  0, 0, 0,                0,                 0,                0,                 0, 0 },
};

struct attackanimconfig var80067d28[] = { ANIM_SNIPING_GETDOWN, 0, 0, 0, 0, 236, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0, 0 };

struct attackanimconfig var80067d70[] = {
	{ ANIM_SNIPING_ONGROUND, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0, 0 },
	{ ANIM_SNIPING_GETUP, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, 0.87252569198608, -0.52351540327072, 0.52351540327072, -0.52351540327072, 0, 0 },
	{ 0, 0, 0, 0, 0, -1, 0, 0, 0,  0,  0, 0, 0,                0,                 0,                0,                 0, 0 },
};

struct attackanimgroup var80067e48 = { var80067d28, 0xffffffff };

struct attackanimgroup *g_LieAttackAnims = &var80067e48;

u32 g_StageFlags = 0;

struct chrdata *g_BgChrs = NULL;
s16 *g_BgChrnums = NULL;
s32 g_NumBgChrs = 0;

s16 *g_TeamList = NULL;
s16 *g_SquadronList = NULL;

struct var80067e6c var80067e6c[] = {
	{ ANIM_0028, 0 },
	{ ANIM_RUNNING_TWOHANDGUN, 0 },
	{ ANIM_0029, 0 },
	{ ANIM_006B, 0 },
	{ ANIM_RUNNING_ONEHANDGUN, 0 },
	{ ANIM_005A, 0 },
	{ ANIM_0072, 0 },
	{ ANIM_0073, 0 },
	{ ANIM_005A, 0 },
	{ ANIM_006C, 0 },
	{ ANIM_0030, 0 },
	{ ANIM_0031, 0 },
	{ ANIM_0052, 0 },
	{ ANIM_0055, 0 },
	{ ANIM_006E, 0 },
	{ ANIM_006F, 0 },
	{ ANIM_0057, 0 },
	{ ANIM_0056, 0 },
	{ ANIM_006D, 0 },
	{ ANIM_RUNNING_ONEHANDGUN, 0 },
	{ ANIM_020A, 0 },
	{ ANIM_020D, 0 },
	{ ANIM_01F9, 0 },
	{ ANIM_01F8, 0 },
	{ ANIM_021D, 0 },
	{ ANIM_0016, 0 },
	{ ANIM_0018, 0 },
	{ ANIM_001B, 0 },
	{ ANIM_001D, 0 },
	{ ANIM_001E, 0 },
	{ ANIM_005C, 0 },
	{ ANIM_005D, 0 },
	{ ANIM_005E, 0 },
	{ ANIM_005F, 0 },
	{ -1 },
};

struct var80067e6c var80067f84[] = {
	{ ANIM_0392, 0 },
	{ ANIM_0393, 0 },
	{ ANIM_SKEDAR_RUNNING, 0 },
	{ -1 },
};

struct var80067e6c var80067fa4[] = {
	{ ANIM_015F, 0 },
	{ ANIM_0160, 0 },
	{ -1 },
};

struct var80067e6c var80067fbc[] = {
	{ ANIM_015F, 0 },
	{ -1 },
};

struct var80067e6c var80067fcc[] = {
	{ ANIM_0238, 0 },
	{ -1 },
};

struct var80067e6c *var80067fdc[] = {
	var80067e6c,
	var80067f84,
	var80067fa4,
	var80067fbc,
	var80067fcc,
};

s16 var80067ff0[] = { ANIM_TWO_GUN_HOLD, ANIM_006A, -1 };
s16 var80067ff8[] = { ANIM_00C0, -1 };
s16 var80067ffc[] = { ANIM_013E, -1 };
s16 var80068000[] = { ANIM_013E, -1 };
s16 var80068004[] = { ANIM_0237, -1 };

s16 *var80068008[] = {
	var80067ff0,
	var80067ff8,
	var80067ffc,
	var80068000,
	var80068004,
};

f32 func0f02dff0(s16 animnum)
{
	s32 i;

	for (i = 0; i < ARRAYCOUNT(var80067fdc); i++) {
		s32 j = 0;
		s16 thisanimnum = var80067fdc[i][j].animnum;

		while (thisanimnum >= 0) {
			if (thisanimnum == animnum) {
				return var80067fdc[i][j].value;
			}

			j++;
			thisanimnum = var80067fdc[i][j].animnum;
		}
	}

	return 1;
}

bool func0f02e064(struct chrdata *chr)
{
	if (chr->aibot) {
		if (chr->actiontype == ACT_STAND
				|| (chr->actiontype == ACT_GOPOS && (chr->act_gopos.flags & GOPOSFLAG_20))) {
			return true;
		}
	} else {
		s16 animnum = modelGetAnimNum(chr->model);
		s32 i;

		for (i = 0; i < ARRAYCOUNT(var80068008); i++) {
			s16 thisanimnum;
			s32 j;

			for (j = 0; (thisanimnum = var80068008[i][j]) >= 0; j++) {
				if (thisanimnum == animnum) {
					return true;
				}
			}
		}
	}

	return false;
}

bool weaponIsOneHanded(struct prop *prop)
{
	if (prop) {
		struct weaponobj *weapon = prop->weapon;
		return weaponHasFlag(weapon->weaponnum, WEAPONFLAG_ONEHANDED);
	}

	return false;
}

/**
 * Returns a value between min and max based on the chr's speedrating property.
 *
 * chr->speedrating is between 0 and 100. The result is scaled between min and
 * max accordingly.
 *
 * This function also applies the PD mode reaction speed, but the PD mode
 * reaction speed is always zero because PD doesn't have it in the settings.
 * It was used in GE but disabled in PD.
 */
f32 chrGetRangedSpeed(struct chrdata *chr, f32 min, f32 max)
{
	f32 speedrating = chr->speedrating;

	speedrating = pdmodeGetEnemyReactionSpeed() * (100.0f - speedrating) + speedrating;

	return (max - min) * speedrating * 0.01f + min;
}

/**
 * Calculates a percentage of how slow the chr is.
 *
 * percentage is expected to be between 0 and 100.
 * chr->speedrating is between 0 and 100.
 *
 * This function takes the difference between the speedrating and the max (100),
 * then multiplies that amount by the given percentage and returns it.
 *
 * For example, if the chr's speedrating is 10 (out of 100) and the given
 * percentage is 50, the result will be 45.
 */
s32 chrGetPercentageOfSlowness(struct chrdata *chr, s32 percentage)
{
	s32 speedrating = chr->speedrating;
	s32 extra = pdmodeGetEnemyReactionSpeed() * (100 - speedrating);

	speedrating = extra + speedrating;

	return (100 - speedrating) * percentage / 100;
}

f32 chrGetRangedArghSpeed(struct chrdata *chr, f32 min, f32 max)
{
	f32 arghrating = chr->arghrating;

	arghrating = pdmodeGetEnemyReactionSpeed() * (100.0f - arghrating) + arghrating;

	return (max - min) * arghrating * 0.01f + min;
}

f32 chrGetAttackEntityRelativeAngle(struct chrdata *chr, s32 attackflags, s32 entityid)
{
	f32 angle;
	struct coord pos;
	s16 rooms[8];

	if (attackflags & ATTACKFLAG_AIMFORWARD) {
		return 0;
	}

	if (attackflags & ATTACKFLAG_AIMATDIRECTION) {
		angle = entityid * (M_BADTAU / 65536);
		angle -= chrGetInverseTheta(chr);

		if (angle < 0) {
			angle += M_BADTAU;
		}

		return angle;
	}

	chrGetAttackEntityPos(chr, attackflags, entityid, &pos, rooms);

	return chrGetAngleToPos(chr, &pos);
}

f32 chrGetAttackEntityDistance(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	if (attackflags & ATTACKFLAG_AIMATTARGET) {
		return chrGetDistanceToTarget(chr);
	}

	if (attackflags & ATTACKFLAG_AIMATCHR) {
		return chrGetDistanceToChr(chr, entityid);
	}

	if (attackflags & ATTACKFLAG_AIMATPAD) {
		return chrGetDistanceToPad(chr, entityid);
	}

	return 0;
}

void func0f02e3dc(struct coord *a, struct coord *b,struct coord *c, struct coord *d, struct coord *dst)
{
	f32 value = d->z * (b->x - a->x) - (b->z - a->z) * d->x;

	if (value != 0) {
		f32 tmp = ((b->z - a->z) * (c->x - a->x) + (a->z - c->z) * (b->x - a->x)) / value;
		dst->x = d->x * tmp + c->x;
		dst->y = d->y * tmp + c->y;
		dst->z = d->z * tmp + c->z;
	} else if (d->x == 0 && d->z == 0) {
		dst->x = c->x;
		dst->y = c->y;
		dst->z = c->z;
	} else {
		dst->x = a->x;
		dst->y = a->y;
		dst->z = a->z;
	}
}

void func0f02e4f8(struct coord *arg0, struct coord *arg1, struct coord *dst)
{
	struct coord sp2c;
	struct coord sp20;

#if VERSION >= VERSION_PAL_FINAL
	cd00024e4c(&sp2c, &sp20, 2298, "chr/chraction.c");
#elif VERSION >= VERSION_NTSC_1_0
	cd00024e4c(&sp2c, &sp20, 2298, "chraction.c");
#else
	cd00024e4c(&sp2c, &sp20, 2338, "chraction.c");
#endif

	func0f02e3dc(&sp2c, &sp20, arg0, arg1, dst);
}

f32 func0f02e550(struct prop *prop, f32 arg1, f32 arg2, u32 arg3, f32 ymax, f32 ymin)
{
	struct coord sp5c;
	struct coord sp50;
	struct chrdata *chr = prop->chr;
	f32 result;
	struct coord sp3c;
	f32 xdiff;
	f32 zdiff;

	sp5c.x = sinf(arg1);
	sp5c.y = 0;
	sp5c.z = cosf(arg1);

	sp50.x = prop->pos.x + sp5c.f[0] * arg2;
	sp50.y = prop->pos.y;
	sp50.z = prop->pos.z + sp5c.f[2] * arg2;

	chrSetPerimEnabled(chr, false);

	if (cd0002d7c0(&prop->pos, prop->rooms, &sp50, arg3, 1, ymax - prop->pos.y, ymin - prop->pos.y) != CDRESULT_COLLISION) {
		result = arg2;
	} else {
#if VERSION >= VERSION_PAL_FINAL
		cdGetPos(&sp3c, 2377, "chr/chraction.c");
#elif VERSION >= VERSION_NTSC_1_0
		cdGetPos(&sp3c, 2377, "chraction.c");
#else
		cdGetPos(&sp3c, 2417, "chraction.c");
#endif

		xdiff = sp3c.x - prop->pos.x;
		zdiff = sp3c.z - prop->pos.z;

		result = sqrtf(xdiff * xdiff + zdiff * zdiff);
	}

	chrSetPerimEnabled(chr, true);

	return result;
}

f32 func0f02e684(struct prop *prop, f32 arg1, f32 arg2)
{
	f32 ymax;
	f32 ymin;
	f32 width;

	chrGetBbox(prop, &width, &ymax, &ymin);

	return func0f02e550(prop, arg1, arg2, CDTYPE_ALL, ymax, ymin);
}

void chrStandChooseAnimation(struct chrdata *chr, f32 mergetime)
{
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);
	s32 race = CHRRACE(chr);
	s32 prevanimnum = modelGetAnimNum(chr->model);

	if (chr->actiontype == ACT_GOPOS) {
		chr->act_gopos.flags |= GOPOSFLAG_20;
	}

	if (chr->aibot) {
		return;
	}

	if (race == RACE_EYESPY) {
		modelSetAnimation(chr->model, ANIM_013E, 0, 0, 0, mergetime);
	} else if (race == RACE_HUMAN) {
		if (prevanimnum == ANIM_SNIPING_GETDOWN
				|| prevanimnum == ANIM_SNIPING_GETUP
				|| prevanimnum == ANIM_SNIPING_ONGROUND) {
			modelSetAnimation(chr->model, ANIM_SNIPING_GETUP, chr->model->anim->flip, -1, chrGetRangedSpeed(chr, 0.5, 0.8), 16);
		} else if ((gun1 && gun2) || (!gun1 && !gun2)
				|| weaponIsOneHanded(gun1)
				|| weaponIsOneHanded(gun2)) {
			modelSetAnimation(chr->model, ANIM_006A, random() % 2, 0, 0.25, mergetime);
			modelSetAnimLooping(chr->model, 0, 16);
		} else if (gun2 || gun1) {
			modelSetAnimation(chr->model, ANIM_TWO_GUN_HOLD, gun1 != NULL, 0, 0.25, mergetime);
			modelSetAnimLooping(chr->model, 0, 16);
			modelSetAnimEndFrame(chr->model, 120);
		}
	} else if (race == RACE_SKEDAR) {
		modelSetAnimation(chr->model, ANIM_00C0, random() % 2, 0, 0.5, mergetime);
	} else if (race == RACE_DRCAROLL) {
		modelSetAnimation(chr->model, ANIM_013E, 0, 0, 0.5, mergetime);
	} else if (race == RACE_ROBOT) {
		modelSetAnimation(chr->model, ANIM_0237, 0, 0, 0.5, mergetime);
	}
}

void func0f02e9a0(struct chrdata *chr, f32 mergetime)
{
	f32 limit = 127;
	f32 fsleep;

	chrStopFiring(chr);
	chr->actiontype = ACT_STAND;
	chr->act_stand.prestand = false;
	chr->act_stand.flags = 0;
	chr->act_stand.entityid = 0;
	chr->act_stand.reaim = 0;
	chr->act_stand.turning = TURNSTATE_OFF;
	chr->act_stand.checkfacingwall = false;
	chr->act_stand.wallcount = random() % 120 + 180; // 180 to 299
	chr->act_stand.mergetime = mergetime;
	chr->act_stand.playwalkanim = false;

	fsleep = mergetime;

	if (chr->model->anim->playspeed != PALUPF(1.0f)) {
		fsleep *= PALUPF(1.0f) / chr->model->anim->playspeed;
	}

	if (fsleep > limit) {
		fsleep = limit;
	}

	chr->sleep = fsleep;

	if (modelIsAnimMerging(chr->model) && !chr->aibot) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrStandChooseAnimation(chr, mergetime);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrStand(struct chrdata *chr)
{
	s32 race = CHRRACE(chr);
	f32 result;

	if (race != RACE_EYESPY) {
		chrStopFiring(chr);

		if (race == RACE_HUMAN && chr->actiontype == ACT_KNEEL) {
			chrStopFiring(chr);

			chr->actiontype = ACT_STAND;
			chr->act_stand.prestand = true;
			chr->act_stand.flags = 0;
			chr->act_stand.entityid = 0;
			chr->act_stand.reaim = 0;
			chr->act_stand.turning = TURNSTATE_OFF;
			chr->act_stand.checkfacingwall = false;
			chr->act_stand.wallcount = random() % 120 + 180;
			chr->sleep = 0;
			chr->act_stand.playwalkanim = false;

			if (chr->aibot == NULL) {
				if (modelGetAnimNum(chr->model) == ANIM_KNEEL_SHOOT_RIGHT_HAND) {
					result = chrGetRangedSpeed(chr, 0.5, 0.8);
					modelSetAnimation(chr->model, ANIM_KNEEL_SHOOT_RIGHT_HAND,
							chr->model->anim->flip, 109, result, 16);
					modelSetAnimEndFrame(chr->model, 140);
				} else {
					result = chrGetRangedSpeed(chr, 0.5, 0.8);
					modelSetAnimation(chr->model, ANIM_KNEEL_TWO_HANDED_GUN,
							chr->model->anim->flip, 120, result, 16);
					modelSetAnimEndFrame(chr->model, 151);
				}
			}
		} else if (race == RACE_DRCAROLL || race == RACE_ROBOT) {
			chr->actiontype = ACT_STAND;
			chr->act_stand.prestand = true;
			chr->act_stand.flags = 0;
			chr->act_stand.entityid = 0;
			chr->act_stand.reaim = 0;
			chr->act_stand.turning = TURNSTATE_OFF;
			chr->act_stand.checkfacingwall = false;
			chr->act_stand.wallcount = random() % 120 + 180;
			chr->sleep = 0;
			chr->act_stand.playwalkanim = false;

			func0f02e9a0(chr, 16);
		} else {
			func0f02e9a0(chr, 16);
		}
	}
}

bool chrFaceCover(struct chrdata *chr)
{
	struct cover cover;

	if (!coverUnpack(chr->cover, &cover)) {
		return false;
	}

	chrStand(chr);
	chr->act_stand.reaim = 0;
	chr->act_stand.flags = ATTACKFLAG_AIMATDIRECTION;
	chr->act_stand.turning = TURNSTATE_TURNING;
	//chr->act_stand.entityid = atan2f(-cover.look->x, -cover.look->z) * (0x4000 / BADDEG2RAD(90));
	chr->act_stand.entityid = atan2f(-cover.look->x, -cover.look->z) * 10432.039f;

	return true;
}

void func0f02ed28(struct chrdata *chr, f32 mergetime)
{
	func0f02e9a0(chr, mergetime);

	chr->act_stand.checkfacingwall = true;
}

void chrStop(struct chrdata *chr)
{
	chrStand(chr);

	chr->act_stand.checkfacingwall = true;
}

void chrKneelChooseAnimation(struct chrdata *chr)
{
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);

	if (chr->aibot == NULL) {
		if ((gun1 && gun2)
				|| (!gun1 && !gun2)
				|| weaponIsOneHanded(gun1)
				|| weaponIsOneHanded(gun2)) {
			bool flip = random() % 2;
			modelSetAnimation(chr->model, ANIM_KNEEL_SHOOT_RIGHT_HAND, flip, 0, chrGetRangedSpeed(chr, 0.5, 0.8), 16);
			modelSetAnimEndFrame(chr->model, 28);
		} else if (gun2 || gun1) {
			modelSetAnimation(chr->model, ANIM_KNEEL_TWO_HANDED_GUN, gun1 != NULL, 0, chrGetRangedSpeed(chr, 0.5, 0.8), 16);
			modelSetAnimEndFrame(chr->model, 27);
		}
	}
}

void chrKneel(struct chrdata *chr)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_KNEEL;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrKneelChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrStartAlarmChooseAnimation(struct chrdata *chr)
{
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);
	bool flip = false;

	if (gun1 && !gun2) {
		flip = true;
	} else if ((gun1 && gun2) || (!gun1 && !gun2)) {
		flip = random() % 2;
	}

	modelSetAnimation(chr->model, ANIM_TALKING_003D, flip, 40, 1, 16);
	modelSetAnimEndFrame(chr->model, 82);
}

void chrStartAlarm(struct chrdata *chr)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_STARTALARM;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrStartAlarmChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrThrowGrenadeChooseAnimation(struct chrdata *chr)
{
	u32 rand = random();

	if (chr->act_throwgrenade.needsequip) {
		if (rand % 3 == 0) {
			modelSetAnimation(chr->model, ANIM_THROWGRENADE_CROUCHING, chr->act_throwgrenade.hand != 0, 0, chrGetRangedSpeed(chr, 0.5, 1.2), 16);
		} else if (rand % 3 == 1) {
			modelSetAnimation(chr->model, ANIM_THROWGRENADE_NOPIN, chr->act_throwgrenade.hand != 0, 0, chrGetRangedSpeed(chr, 0.5, 1.2), 16);
		} else {
			modelSetAnimation(chr->model, ANIM_THROWGRENADE_STANDING, chr->act_throwgrenade.hand != 0, 0, chrGetRangedSpeed(chr, 0.5, 1.2), 16);
		}
	} else {
		if (rand % 3 == 0) {
			modelSetAnimation(chr->model, ANIM_THROWGRENADE_CROUCHING, chr->act_throwgrenade.hand != 0, 5, chrGetRangedSpeed(chr, 0.5, 1.2), 16);
		} else if (rand % 3 == 1) {
			modelSetAnimation(chr->model, ANIM_THROWGRENADE_NOPIN, chr->act_throwgrenade.hand != 0, 6, chrGetRangedSpeed(chr, 0.5, 1.2), 16);
		} else {
			modelSetAnimation(chr->model, ANIM_THROWGRENADE_STANDING, chr->act_throwgrenade.hand != 0, 84, chrGetRangedSpeed(chr, 0.5, 1.2), 16);
		}
	}

	modelSetAnimEndFrame(chr->model, -1);
}

void chrThrowGrenade(struct chrdata *chr, s32 hand, s32 needsequip)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_THROWGRENADE;
	chr->act_throwgrenade.hand = hand;
	chr->act_throwgrenade.needsequip = needsequip;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrThrowGrenadeChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrSurprisedChooseAnimation(struct chrdata *chr)
{
	if (chr->act_surprised.type == 1) {
		struct prop *gun1 = chrGetHeldProp(chr, 1);
		struct prop *gun0 = chrGetHeldProp(chr, 0);
		s32 flip = 0;

		if (gun1 != NULL && gun0 == NULL) {
			flip = 1;
		} else if ((gun1 != NULL && gun0 != NULL) || (gun1 == NULL && gun0 == NULL)) {
			flip = random() & 1;
		}

		modelSetAnimation(chr->model, ANIM_003F, flip, 10, chrGetRangedSpeed(chr, 0.6f, 0.96000003f), 16);
		modelSetAnimEndFrame(chr->model, 52);
	} else if (chr->act_surprised.type == 2) {
		modelSetAnimation(chr->model, ANIM_SURRENDER_002E, random() & 1, 0, chrGetRangedSpeed(chr, 0.35f, 0.56f), 16);
		modelSetAnimEndFrame(chr->model, 7);
	} else {
		u32 part = random() % 3;
		modelSetAnimation(chr->model, ANIM_0040, random() & 1, 17, 0.6f, 16);

		if (part == 0) {
			modelSetAnimEndFrame(chr->model, chrGetRangedSpeed(chr, 38, 8));
		} else if (part == 1) {
			modelSetAnimEndFrame(chr->model, chrGetRangedSpeed(chr, 66, 8));
		} else {
			modelSetAnimEndFrame(chr->model, chrGetRangedSpeed(chr, 96, 8));
		}
	}
}

void chrDoSurprisedOneHand(struct chrdata *chr)
{
	struct prop *prop = chrGetTargetProp(chr);
	f32 angle = chrGetAngleToPos(chr, &prop->pos);

	// BADDEG2RAD(10) doesn't match due to float precision :(
	if (angle < 0.17450514435768f || angle > BADDEG2RAD(350)) {
		chrStopFiring(chr);
		chr->actiontype = ACT_SURPRISED;
		chr->act_surprised.type = 1;
		chr->sleep = 0;

		if (modelIsAnimMerging(chr->model)) {
			chr->hidden |= CHRHFLAG_NEEDANIM;
		} else {
			chrSurprisedChooseAnimation(chr);
			chr->hidden &= ~CHRHFLAG_NEEDANIM;
		}
	} else if (!chrIsStopped(chr)) {
		chrStand(chr);
	}
}

void chrDoSurprisedSurrender(struct chrdata *chr)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_SURPRISED;
	chr->act_surprised.type = 2;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrSurprisedChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrDoSurprisedLookAround(struct chrdata *chr)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_SURPRISED;
	chr->act_surprised.type = 3;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrSurprisedChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrSurrenderChooseAnimation(struct chrdata *chr)
{
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun0 = chrGetHeldProp(chr, 0);

	if (gun0 || gun1) {
		modelSetAnimation(chr->model, ANIM_SURRENDER_002F, random() & 1, 0, 0.5, 16);
		modelSetAnimLooping(chr->model, 40, 16);

		if (gun1) {
			objSetDropped(gun1, DROPTYPE_SURRENDER);
		}

		if (gun0) {
			objSetDropped(gun0, DROPTYPE_SURRENDER);
		}

		chr->hidden |= CHRHFLAG_00000001;
	} else {
		modelSetAnimation(chr->model, ANIM_SURRENDER_002E, random() & 1, 0, 0.5, 16);
		modelSetAnimLooping(chr->model, 30, 16);
	}

	chrDropConcealedItems(chr);
}

void chrSurrender(struct chrdata *chr)
{
	u32 action = ACT_SURRENDER;

	if (chr->actiontype != action) {
		chrStopFiring(chr);
		chr->actiontype = action;
		chr->sleep = action;

		if (modelIsAnimMerging(chr->model)) {
			chr->hidden |= CHRHFLAG_NEEDANIM;
		} else {
			chrSurrenderChooseAnimation(chr);
			chr->hidden &= ~CHRHFLAG_NEEDANIM;
		}
	}
}

void chrSidestepChooseAnimation(struct chrdata *chr)
{
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);
	bool flip = false;
	bool allowflip = false;
	u32 race = CHRRACE(chr);

	if (gun1 && gun2) {
		flip = random() % 2;
		allowflip = random() % 2;
	} else {
		if (weaponIsOneHanded(gun1) == false
				&& weaponIsOneHanded(gun2) == false
				&& (gun1 || gun2)) {
			flip = (gun1 != 0);
			allowflip = random() % 2;
		}
	}

	if (race == RACE_HUMAN) {
		if (allowflip == false) {
			if (chr->act_sidestep.side) {
				modelSetAnimation(chr->model, ANIM_0068, true, 5, chrGetRangedSpeed(chr, 0.55, 0.88000005), 16);
				modelSetAnimEndFrame(chr->model, 36);
			} else {
				modelSetAnimation(chr->model, ANIM_0068, false, 5, chrGetRangedSpeed(chr, 0.55, 0.88000005), 16);
				modelSetAnimEndFrame(chr->model, 36);
			}
		} else {
			if ((chr->act_sidestep.side && !flip) || (chr->act_sidestep.side == 0 && flip)) {
				modelSetAnimation(chr->model, ANIM_003B, flip, 5, chrGetRangedSpeed(chr, 0.7, 1.12), 16);
				modelSetAnimEndFrame(chr->model, 34);
			} else {
				modelSetAnimation(chr->model, ANIM_003A, flip, 5, chrGetRangedSpeed(chr, 0.7, 1.12), 16);
				modelSetAnimEndFrame(chr->model, 32);
			}
		}
	} else if (race == RACE_SKEDAR) {
		if (chr->act_sidestep.side) {
			modelSetAnimation(chr->model, ANIM_0328, false, 5, chrGetRangedSpeed(chr, 0.55, 0.88000005), 16);
			modelSetAnimEndFrame(chr->model, 27);
		} else {
			modelSetAnimation(chr->model, ANIM_0328, true, 5, chrGetRangedSpeed(chr, 0.55, 0.88000005), 16);
			modelSetAnimEndFrame(chr->model, 27);
		}
	}
}

void chrSidestep(struct chrdata *chr, bool side)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_SIDESTEP;
	chr->act_sidestep.side = side;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrSidestepChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrJumpOutChooseAnimation(struct chrdata *chr)
{
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);
	bool flip = false;

	if (gun1 && !gun2) {
		flip = true;
	} else if ((gun1 && gun2) || (!gun1 && !gun2)
			|| weaponIsOneHanded(gun1) || weaponIsOneHanded(gun2)) {
		flip = random() % 2;
	}

	if ((chr->act_jumpout.side && !flip) || (chr->act_jumpout.side == 0 && flip)) {
		modelSetAnimation(chr->model, ANIM_0068, true, 5, chrGetRangedSpeed(chr, 0.55, 0.88000005), 16);
		modelSetAnimEndFrame(chr->model, 36);
	} else {
		modelSetAnimation(chr->model, ANIM_0068, false, 5, chrGetRangedSpeed(chr, 0.55, 0.88000005), 16);
		modelSetAnimEndFrame(chr->model, 36);
	}
}

void chrJumpOut(struct chrdata *chr, bool side)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_JUMPOUT;
	chr->act_jumpout.side = side;
	chr->sleep = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrJumpOutChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrRunPosChooseAnimation(struct chrdata *chr)
{
	f32 xdiff = chr->prop->pos.x - chr->act_runpos.pos.x;
	f32 ydiff = chr->prop->pos.y - chr->act_runpos.pos.y;
	f32 zdiff = chr->prop->pos.z - chr->act_runpos.pos.z;
	f32 distance = sqrtf(xdiff * xdiff + zdiff * zdiff);
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);
	bool heavy = true;
	bool flip;
	s32 race = CHRRACE(chr);

	if ((gun1 && gun2) || (!gun1 && !gun2)) {
		heavy = false;
		flip = random() % 2;
	} else if (weaponIsOneHanded(gun1) || weaponIsOneHanded(gun2)) {
		heavy = false;
		flip = (bool)gun1 != false;
	} else {
		flip = (bool)gun1 != false;
	}

	if (race == RACE_HUMAN) {
		if (heavy) {
			f32 mult = 0.5;
#if PAL
			chr->act_runpos.eta60 = 1.0f / (func0f02dff0(0x2a) * mult) * distance * 0.83333331346512f;
#else
			chr->act_runpos.eta60 = 1.0f / (func0f02dff0(0x2a) * mult) * distance;
#endif
			modelSetAnimation(chr->model, ANIM_RUNNING_TWOHANDGUN, flip, 0, mult, 16);
		} else {
			f32 mult = 0.5;
#if PAL
			chr->act_runpos.eta60 = 1.0f / (func0f02dff0(0x59) * mult) * distance * 0.83333331346512f;
#else
			chr->act_runpos.eta60 = 1.0f / (func0f02dff0(0x59) * mult) * distance;
#endif
			modelSetAnimation(chr->model, ANIM_RUNNING_ONEHANDGUN, flip, 0, mult, 16);
		}
	} else if (race == RACE_SKEDAR) {
		f32 mult = 0.5;
#if PAL
		chr->act_runpos.eta60 = 1.0f / (func0f02dff0(0x394) * mult) * distance * 0.83333331346512f;
#else
		chr->act_runpos.eta60 = 1.0f / (func0f02dff0(0x394) * mult) * distance;
#endif
		modelSetAnimation(chr->model, ANIM_SKEDAR_RUNNING, flip, 0, mult, 16);
	}
}

void chrRunToPos(struct chrdata *chr, struct coord *pos)
{
	chrStopFiring(chr);
	chr->actiontype = ACT_RUNPOS;
	chr->act_runpos.pos.x = pos->x;
	chr->act_runpos.pos.y = pos->y;
	chr->act_runpos.pos.z = pos->z;
	chr->sleep = 0;
	chr->act_runpos.neardist = 30;
	chr->act_runpos.turnspeed = 0;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrRunPosChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrAttackStand(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	struct prop *leftgun = chrGetHeldProp(chr, HAND_LEFT);
	struct prop *rightgun = chrGetHeldProp(chr, HAND_RIGHT);
	bool flip;
	struct attackanimgroup **animgroup;
	bool firing[] = {false, false};
	s32 race = CHRRACE(chr);

	if (leftgun && rightgun) {
		struct prop *leftgun2 = chrGetHeldUsableProp(chr, HAND_LEFT);
		struct prop *rightgun2 = chrGetHeldUsableProp(chr, HAND_RIGHT);

		if (leftgun2 && rightgun2) {
			flip = random() % 2;

			if (random() % 3 == 0) {
				animgroup = g_StandLightAttackAnims[race];
				firing[HAND_LEFT] = flip;
				firing[HAND_RIGHT] = !flip;
			} else {
				animgroup = g_StandDualAttackAnims[race];
				firing[HAND_LEFT] = true;
				firing[HAND_RIGHT] = true;
			}
		} else {
			flip = (bool)rightgun2 == false;
			animgroup = g_StandLightAttackAnims[race];
			firing[HAND_LEFT] = (bool)rightgun2 == false;
			firing[HAND_RIGHT] = !flip;
		}
	} else {
		if (weaponIsOneHanded(leftgun) || weaponIsOneHanded(rightgun)) {
			flip = (bool)leftgun != false;
			animgroup = g_StandLightAttackAnims[race];
			firing[HAND_LEFT] = (bool)leftgun != false;
			firing[HAND_RIGHT] = !flip;
		} else {
			flip = (bool)leftgun != false;
			animgroup = g_StandHeavyAttackAnims[race];
			firing[HAND_LEFT] = (bool)leftgun != false;
			firing[HAND_RIGHT] = !flip;
		}
	}

	chrAttack(chr, animgroup, flip, firing, attackflags, entityid, true);
}

u32 var80068024 = 0x00000000;
u32 var80068028 = 0x00000000;

GLOBAL_ASM(
glabel chrAttackLie
/*  f030308:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*  f03030c:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f030310:	afa5004c */ 	sw	$a1,0x4c($sp)
/*  f030314:	afa60050 */ 	sw	$a2,0x50($sp)
/*  f030318:	00002825 */ 	or	$a1,$zero,$zero
/*  f03031c:	0fc0a209 */ 	jal	chrGetHeldProp
/*  f030320:	afa40048 */ 	sw	$a0,0x48($sp)
/*  f030324:	3c0e8007 */ 	lui	$t6,%hi(var80068024)
/*  f030328:	25ce8024 */ 	addiu	$t6,$t6,%lo(var80068024)
/*  f03032c:	8dc10000 */ 	lw	$at,0x0($t6)
/*  f030330:	8fa9004c */ 	lw	$t1,0x4c($sp)
/*  f030334:	8fa40048 */ 	lw	$a0,0x48($sp)
/*  f030338:	27a70034 */ 	addiu	$a3,$sp,0x34
/*  f03033c:	ace10000 */ 	sw	$at,0x0($a3)
/*  f030340:	8dd90004 */ 	lw	$t9,0x4($t6)
/*  f030344:	312a0020 */ 	andi	$t2,$t1,0x20
/*  f030348:	00404025 */ 	or	$t0,$v0,$zero
/*  f03034c:	11400004 */ 	beqz	$t2,.L0f030360
/*  f030350:	acf90004 */ 	sw	$t9,0x4($a3)
/*  f030354:	afa00038 */ 	sw	$zero,0x38($sp)
/*  f030358:	10000005 */ 	b	.L0f030370
/*  f03035c:	afa00034 */ 	sw	$zero,0x34($sp)
.L0f030360:
/*  f030360:	2c430001 */ 	sltiu	$v1,$v0,0x1
/*  f030364:	2c6b0001 */ 	sltiu	$t3,$v1,0x1
/*  f030368:	afa30038 */ 	sw	$v1,0x38($sp)
/*  f03036c:	afab0034 */ 	sw	$t3,0x34($sp)
.L0f030370:
/*  f030370:	8fac0050 */ 	lw	$t4,0x50($sp)
/*  f030374:	3c058006 */ 	lui	$a1,%hi(g_LieAttackAnims)
/*  f030378:	24a57e50 */ 	addiu	$a1,$a1,%lo(g_LieAttackAnims)
/*  f03037c:	2d060001 */ 	sltiu	$a2,$t0,0x1
/*  f030380:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f030384:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f030388:	0fc0c4e1 */ 	jal	chrAttack
/*  f03038c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f030390:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f030394:	27bd0048 */ 	addiu	$sp,$sp,0x48
/*  f030398:	03e00008 */ 	jr	$ra
/*  f03039c:	00000000 */ 	nop
);

// Mismatch because some instructions are swapped
//void chrAttackLie(struct chrdata *chr, u32 attackflags, s32 entityid)
//{
//	u32 stack1[2];
//	struct prop *gun = chrGetHeldProp(chr, 0);
//	s32 firing[2] = {false, false};
//	u32 stack2[2];
//
//	if (attackflags & 0x20) {
//		firing[1] = false;
//		firing[0] = false;
//	} else {
//		firing[1] = gun == NULL;
//		firing[0] = !firing[1];
//	}
//
//	chrAttack(chr, &g_LieAttackAnims, gun == NULL, firing, attackflags, entityid, false);
//}

void chrAttackKneel(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	struct prop *leftgun = chrGetHeldProp(chr, HAND_LEFT);
	struct prop *rightgun = chrGetHeldProp(chr, HAND_RIGHT);
	s32 flip;
	struct attackanimgroup **animgroup;
	bool firing[2] = {false, false};
	s32 race = CHRRACE(chr);
	struct prop *leftgun2;
	struct prop *rightgun2;

	if (leftgun && rightgun) {
		leftgun2 = chrGetHeldUsableProp(chr, HAND_LEFT);
		rightgun2 = chrGetHeldUsableProp(chr, HAND_RIGHT);

		if (leftgun2 && rightgun2) {
			flip = random() % 2;

			if (random() % 3 == 0) {
				animgroup = g_KneelLightAttackAnims[race];
				firing[HAND_LEFT] = flip;
				firing[HAND_RIGHT] = !flip;
			} else {
				animgroup = g_KneelDualAttackAnims[race];
				firing[HAND_LEFT] = true;
				firing[HAND_RIGHT] = true;
			}
		} else {
			flip = (bool)rightgun2 == false;
			animgroup = g_KneelLightAttackAnims[race];
			firing[HAND_LEFT] = (bool)rightgun2 == false;
			firing[HAND_RIGHT] = !flip;
		}
	} else {
		if (weaponIsOneHanded(leftgun) || weaponIsOneHanded(rightgun)) {
			flip = (bool)leftgun != false;
			animgroup = g_KneelLightAttackAnims[race];
			firing[HAND_LEFT] = (bool)leftgun != false;
			firing[HAND_RIGHT] = !flip;
		} else {
			flip = (bool)leftgun != false;
			animgroup = g_KneelHeavyAttackAnims[race];
			firing[HAND_LEFT] = (bool)leftgun != false;
			firing[HAND_RIGHT] = !flip;
		}
	}

	chrAttack(chr, animgroup, flip, firing, attackflags, entityid, false);
}

void chrAttackWalkChooseAnimation(struct chrdata *chr)
{
	if (chr->aibot == NULL) {
		modelSetAnimation(chr->model, chr->act_attackwalk.animcfg->animnum,
				chr->act_attackwalk.flip, chr->act_attackwalk.animcfg->unk10, 0.5, 16);
	}
}

void chrAttackWalk(struct chrdata *chr, bool run)
{
	struct attackanimconfig *animcfg;
	struct prop *leftgun = chrGetHeldProp(chr, HAND_LEFT);
	struct prop *rightgun = chrGetHeldProp(chr, HAND_RIGHT);
	bool flip;
	bool firing[] = {false, false};
	bool everytick[] = {false, false};
	bool singleshot[] = {false, false};
	s32 i;
	struct prop *prop;
	struct weaponobj *weapon;

	if (leftgun && rightgun) {
		struct prop *leftgun2 = chrGetHeldUsableProp(chr, HAND_LEFT);
		struct prop *rightgun2 = chrGetHeldUsableProp(chr, HAND_RIGHT);
		s32 style = 0;

		if (leftgun2 && rightgun2) {
			flip = random() % 2;
			style = random() % 3;
		} else {
			flip = (bool)rightgun2 == false;
		}

		if (style == 0) {
			if (run) {
				animcfg = &g_AttackAnimLightRun;
			} else {
				animcfg = &g_AttackAnimLightWalk;
			}

			if (flip) {
				firing[HAND_LEFT] = true;
			} else {
				firing[HAND_RIGHT] = true;
			}
		} else if (style == 1) {
			if (run) {
				animcfg = &g_AttackAnimDualRun;
			} else {
				animcfg = &g_AttackAnimDualWalk;
			}

			firing[HAND_LEFT] = firing[HAND_RIGHT] = true;
		} else {
			if (run) {
				animcfg = &g_AttackAnimDualCrossedRun;
			} else {
				animcfg = &g_AttackAnimDualCrossedWalk;
			}

			firing[HAND_LEFT] = firing[HAND_RIGHT] = true;
		}
	} else {
		if (weaponIsOneHanded(leftgun) || weaponIsOneHanded(rightgun)) {
			flip = (bool)leftgun != false;

			if (run) {
				animcfg = &g_AttackAnimLightRun;
			} else {
				animcfg = &g_AttackAnimLightWalk;
			}

			if (flip) {
				firing[HAND_LEFT] = true;
			} else {
				firing[HAND_RIGHT] = true;
			}
		} else {
			flip = (bool)leftgun != false;

			if (run) {
				animcfg = &g_AttackAnimHeavyRun;
			} else {
				animcfg = &g_AttackAnimHeavyWalk;
			}

			if (flip) {
				firing[HAND_LEFT] = true;
			} else {
				firing[HAND_RIGHT] = true;
			}
		}
	}

	for (i = 0; i < 2; i++) {
		if (firing[i]) {
			prop = chrGetHeldProp(chr, i);
			weapon = prop->weapon;

			if (weaponGetNumTicksPerShot(weapon->weaponnum, weapon->gunfunc) < 1) {
				everytick[i] = true;
			}

			if (weapon->weaponnum == WEAPON_ROCKETLAUNCHER
					|| weapon->weaponnum == WEAPON_ROCKETLAUNCHER_34
					|| weapon->weaponnum == WEAPON_SLAYER
					|| weapon->weaponnum == WEAPON_DEVASTATOR
					|| (
						!g_Vars.normmplayerisrunning
						&& weapon->weaponnum == WEAPON_DY357MAGNUM
						&& chr->headnum != HEAD_JONATHAN
						&& chr->headnum != HEAD_CHRIST)
					|| (
						!g_Vars.normmplayerisrunning
						&& weapon->weaponnum == WEAPON_DY357LX)
					|| (
						!g_Vars.normmplayerisrunning
						&& weapon->weaponnum == WEAPON_SHOTGUN)) {
				singleshot[i] = true;
			}
		}
	}

	chr->actiontype = ACT_ATTACKWALK;

	chr->act_attackwalk.frame60count = 0;
#if PAL
	// This is really PALDOWN(400.0f), but off by one bit :(
	chr->act_attackwalk.frame60max = random() % (s32)(333.33331298828f * var80062cac) + PALDOWN(120);
#else
	chr->act_attackwalk.frame60max = random() % (s32)(400 * var80062cac) + PALDOWN(120);
#endif
	chr->act_attackwalk.facedtarget = false;
	chr->act_attackwalk.animcfg = animcfg;
	chr->act_attackwalk.nextshot60 = 0;
	chr->act_attackwalk.nextgun = random() % 2;
	chr->act_attackwalk.firegun[HAND_LEFT] = firing[HAND_LEFT];
	chr->act_attackwalk.firegun[HAND_RIGHT] = firing[HAND_RIGHT];
	chr->act_attackwalk.everytick[HAND_LEFT] = everytick[HAND_LEFT];
	chr->act_attackwalk.everytick[HAND_RIGHT] = everytick[HAND_RIGHT];
	chr->act_attackwalk.singleshot[HAND_LEFT] = singleshot[HAND_LEFT];
	chr->act_attackwalk.singleshot[HAND_RIGHT] = singleshot[HAND_RIGHT];
	chr->act_attackwalk.turnspeed = 0;
	chr->act_attackwalk.flip = flip;

	chr->sleep = 0;
	chr->chrflags &= ~CHRCFLAG_INJUREDTARGET;

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrAttackWalkChooseAnimation(chr);

		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrAttackRollChooseAnimation(struct chrdata *chr)
{
	modelSetAnimation(chr->model, chr->act_attack.animcfg->animnum, chr->act_attack.flip,
			chr->act_attack.animcfg->unk10, chrGetRangedSpeed(chr, 0.5, 0.8), 16);

	if (chr->act_attack.onehanded == false) {
		if (chr->act_attack.dorecoil) {
			if (chr->act_attack.animcfg->unk24 >= 0) {
				modelSetAnimEndFrame(chr->model, chr->act_attack.animcfg->unk24);
			} else {
				modelSetAnimEndFrame(chr->model, chr->act_attack.animcfg->unk1c);
			}
		} else {
			if (chr->act_attack.animcfg->unk20 >= 0) {
				modelSetAnimEndFrame(chr->model, chr->act_attack.animcfg->unk20);
			} else if (chr->act_attack.animcfg->unk14 >= 0) {
				modelSetAnimEndFrame(chr->model, chr->act_attack.animcfg->unk14);
			}
		}
	}
}

void chrAttackRoll(struct chrdata *chr, bool toleft)
{
	struct attackanimconfig *animcfg;
	struct prop *leftgun = chrGetHeldProp(chr, HAND_LEFT);
	struct prop *rightgun = chrGetHeldProp(chr, HAND_RIGHT);
	bool flip;
	bool onehanded = false;
	struct prop *prop;
	struct weaponobj *weapon;
	bool dorecoil = true;
	bool firing[] = {false, false};
	s32 i;
	bool dooneburst = false;
	bool everytick[] = {false, false};
	bool singleshot[] = {false, false};

	if (leftgun && rightgun) {
		struct prop *leftgun2 = chrGetHeldUsableProp(chr, HAND_LEFT);
		struct prop *rightgun2 = chrGetHeldUsableProp(chr, HAND_RIGHT);

		if (leftgun2 && rightgun2) {
			flip = random() % 2;
			onehanded = true;

			if (random() % 3 == 0) {
				firing[HAND_LEFT] = flip;
				firing[HAND_RIGHT] = !flip;
			} else {
				firing[HAND_LEFT] = true;
				firing[HAND_RIGHT] = true;
			}
		} else {
			flip = (bool)rightgun2 == false;
			onehanded = true;
			firing[HAND_LEFT] = flip;
			firing[HAND_RIGHT] = !flip;
		}
	} else {
		if (weaponIsOneHanded(leftgun) || weaponIsOneHanded(rightgun)) {
			flip = (bool)leftgun != false;
			onehanded = true;
			firing[HAND_LEFT] = flip;
			firing[HAND_RIGHT] = !flip;
		} else {
			flip = (bool)leftgun != false;
			firing[HAND_LEFT] = flip;
			firing[HAND_RIGHT] = !flip;
		}
	}

	if ((toleft && !flip) || (!toleft && flip)) {
		// Roll to left
		if (random() % 2) {
			animcfg = &g_RollAttackAnims[0];
		} else {
			animcfg = &g_RollAttackAnims[2];
		}
	} else {
		// Roll to right
		if (random() % 2) {
			animcfg = &g_RollAttackAnims[1];
		} else {
			animcfg = &g_RollAttackAnims[3];
		}
	}

	if (onehanded) {
		// Move the animation pointer to the one-handed version of the same
		// animation. The one-handed versions are in the array immediately after
		// the four heavy-weapon versions.
		animcfg += 4;
	}

	for (i = 0; i < 2; i++) {
		if (firing[i]) {
			prop = chrGetHeldProp(chr, i);
			weapon = prop->weapon;

			if (weaponGetNumTicksPerShot(weapon->weaponnum, weapon->gunfunc) < 1) {
				everytick[i] = true;

				if (weapon->weaponnum == WEAPON_LASER) {
					dorecoil = false;
				}
			} else {
				dorecoil = false;
				dooneburst = true;
			}

			if (weapon->weaponnum == WEAPON_ROCKETLAUNCHER
					|| weapon->weaponnum == WEAPON_ROCKETLAUNCHER_34
					|| weapon->weaponnum == WEAPON_SLAYER
					|| weapon->weaponnum == WEAPON_DEVASTATOR
					|| (
						!g_Vars.normmplayerisrunning
						&& weapon->weaponnum == WEAPON_DY357MAGNUM
						&& chr->headnum != HEAD_JONATHAN
						&& chr->headnum != HEAD_CHRIST)
					|| (
						!g_Vars.normmplayerisrunning
						&& weapon->weaponnum == WEAPON_DY357LX)
					|| (
						!g_Vars.normmplayerisrunning
						&& weapon->weaponnum == WEAPON_SHOTGUN)) {
				singleshot[i] = true;
			}
		}
	}

	chr->actiontype = ACT_ATTACKROLL;

	chr->act_attack.animcfg = animcfg;
	chr->act_attack.fired = false;
	chr->act_attack.nextgun = random() % 2;
	chr->act_attack.firegun[HAND_LEFT] = firing[HAND_LEFT];
	chr->act_attack.firegun[HAND_RIGHT] = firing[HAND_RIGHT];
	chr->act_attack.everytick[HAND_LEFT] = everytick[HAND_LEFT];
	chr->act_attack.everytick[HAND_RIGHT] = everytick[HAND_RIGHT];
	chr->act_attack.singleshot[HAND_LEFT] = singleshot[HAND_LEFT];
	chr->act_attack.singleshot[HAND_RIGHT] = singleshot[HAND_RIGHT];
	chr->act_attack.dorecoil = dorecoil;
	chr->act_attack.dooneburst = dooneburst;
	chr->act_attack.onehanded = onehanded;
	chr->act_attack.pausecount = 0;
	chr->act_attack.numshots = 0;
	chr->act_attack.turning = TURNSTATE_TURNING;

	if (singleshot[HAND_LEFT] || singleshot[HAND_RIGHT]) {
		if (singleshot[HAND_LEFT] && singleshot[HAND_RIGHT]) {
			chr->act_attack.maxshots = 2;
		} else {
			chr->act_attack.maxshots = 1;
		}
	} else {
		chr->act_attack.maxshots = (random() % 4) + 2;

		if (firing[HAND_RIGHT] && firing[HAND_LEFT]) {
			chr->act_attack.maxshots += (random() % 4) + 2;
		}
	}

	chr->act_attack.flags = ATTACKFLAG_AIMATTARGET;
	chr->act_attack.entityid = 0;
	chr->act_attack.standing = true;
	chr->act_attack.reaim = 0;
	chr->act_attack.lastfire60 = 0;
	chr->act_attack.lastontarget60 = 0;
	chr->act_attack.flip = flip;

	chr->sleep = 0;

	// @bug: CHRCFLAG_INJUREDTARGET is not unset here. This means if the chr
	// does an attack that hits the target, then does a roll attack which
	// misses, their AI list will incorrectly read the roll attack as a hit
	// provided it didn't read and clear the flag between the attacks.
	// It usually (always?) does though, so this isn't really an issue.

	if (modelIsAnimMerging(chr->model)) {
		chr->hidden |= CHRHFLAG_NEEDANIM;
	} else {
		chrAttackRollChooseAnimation(chr);

		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrStartAnim(struct chrdata *chr, s32 animnum, f32 startframe, f32 endframe, u8 chranimflags, s32 merge, f32 speed)
{
	u32 stack;

	if (chr && chr->model) {
		if (chranimflags & CHRANIMFLAG_REVERSE) {
			speed = -speed;
		}

		if (CHRRACE(chr) != RACE_DRCAROLL) {
			chrStopFiring(chr);
		}

		chr->actiontype = ACT_ANIM;

		chr->act_anim.movewheninvis = (chranimflags & CHRANIMFLAG_MOVEWHENINVIS) != 0;
		chr->act_anim.pauseatend = (chranimflags & CHRANIMFLAG_PAUSEATEND) != 0;
		chr->act_anim.completed = (chranimflags & CHRANIMFLAG_COMPLETED) != 0;
		chr->act_anim.slowupdate = (chranimflags & CHRANIMFLAG_SLOWUPDATE) != 0;
		chr->act_anim.lockpos = (chranimflags & CHRANIMFLAG_LOCKPOS) != 0;
		chr->act_anim.ishitanim = false;
		chr->act_anim.animnum = animnum;
		chr->act_anim.flip = (chranimflags & CHRANIMFLAG_FLIP) != 0;
		chr->act_anim.startframe = startframe;
		chr->act_anim.endframe = endframe;
		chr->act_anim.speed = speed;
		chr->act_anim.blend = merge;

		chr->sleep = chr->act_anim.slowupdate ? merge : 0;

		if (merge > 0 && modelIsAnimMerging(chr->model)) {
			chr->hidden |= CHRHFLAG_NEEDANIM;
		} else {
			modelSetAnimation(chr->model, animnum, (chranimflags & CHRANIMFLAG_FLIP) != 0, startframe, speed, merge);

			if (endframe >= 0) {
				modelSetAnimEndFrame(chr->model, endframe);
			}

			chr->hidden &= ~CHRHFLAG_NEEDANIM;
		}
	}
}

void chrBeginDead(struct chrdata *chr)
{
	if (chr->actiontype != ACT_DEAD) {
		chrStopFiring(chr);

		if (chr->cover != -1) {
			coverSetInUse(chr->cover, false);
			chr->cover = -1;
		}

		chr->actiontype = ACT_DEAD;
		chr->act_dead.fadetimer60 = chr->aibot ? 0 : -1;
		chr->act_dead.fadenow = false;
		chr->act_dead.fadewheninvis = false;
		chr->act_dead.invistimer60 = 0;
		chr->act_dead.notifychrindex = 0;
		chr->sleep = 0;

		if (chr->race == RACE_DRCAROLL) {
			chr->drcarollimage_left = DRCAROLLIMAGE_STATIC;
			chr->drcarollimage_right = DRCAROLLIMAGE_STATIC;
		}
	}
}

void func0f031254(struct chrdata *chr)
{
	struct model *model = chr->model;
	struct attackanimconfig *animcfg = chr->act_attack.animcfg;

	if (chr->act_attack.flags & ATTACKFLAG_AIMONLY) {
		if (animcfg->unk20 >= 0 && animcfg->unk20 < animcfg->unk18) {
			modelSetAnimEndFrame(model, animcfg->unk20);
		} else {
			modelSetAnimEndFrame(model, animcfg->unk18);
		}
	} else if (chr->act_attack.dorecoil) {
		if (animcfg->unk20 >= 0) {
			modelSetAnimEndFrame(model, animcfg->unk20);
		} else {
			modelSetAnimEndFrame(model, animcfg->unk18);
		}
	} else {
		if (animcfg->unk20 >= 0) {
			modelSetAnimEndFrame(model, animcfg->unk20);
		} else if (animcfg->unk14 >= 0) {
			modelSetAnimEndFrame(model, animcfg->unk14);
		} else {
			modelSetAnimEndFrame(model, -1);
		}
	}
}

/**
 * This function implements attack behaviour common to all the attack types,
 * such as stand, kneel and lie.
 */
void chrAttack(struct chrdata *chr, struct attackanimgroup **animgroups, bool flip, bool *firing, u32 attackflags, s32 entityid, bool standing)
{
	struct model *model = chr->model;
	s32 i;
	f32 angle;
	struct attackanimconfig *animcfg;
	struct prop *prop;
	struct weaponobj *weapon;
	s32 groupindex;
	bool dooneburst = false;
	s32 index;
	bool everytick[] = {false, false};
	bool singleshot[] = {false, false};
	bool dorecoil = true;
	s32 race = CHRRACE(chr);
	u8 sniping = false;

	if (race != RACE_DRCAROLL && race != RACE_EYESPY && race != RACE_ROBOT) {
		chr->actiontype = ACT_ATTACK;

		if (&animgroups[0] == &g_LieAttackAnims) {
			sniping = true;

			if (modelGetAnimNum(chr->model) != ANIM_SNIPING_ONGROUND) {
				// Getting up or getting down
				animcfg = var80067d28;
				modelSetAnimation(model, animcfg->animnum, flip, animcfg->unk10, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);
				modelSetAnimEndFrame(model, 236);
			} else {
				animcfg = var80067d70;
			}
		} else {
			// Non-sniping animations: Choose animation based on angle to target
			angle = chrGetAttackEntityRelativeAngle(chr, attackflags, entityid);

			if (flip) {
				groupindex = (M_BADTAU - angle) * 5.0937690734863f + 0.5f;
			} else {
				groupindex = angle * 5.0937690734863f + 0.5f;
			}

			if (groupindex < 0 || groupindex > 31) {
				groupindex = 0;
			}

			index = random() % animgroups[groupindex]->len;
			animcfg = &animgroups[groupindex]->animcfg[index];
		}

		for (i = 0; i < 2; i++) {
			if (firing[i]) {
				prop = chrGetHeldProp(chr, i);

				if (prop == NULL) {
					chrStandChooseAnimation(chr, 16);
					return;
				}

				weapon = prop->weapon;

				if (weaponGetNumTicksPerShot(weapon->weaponnum, weapon->gunfunc) < 1) {
					// Note: the only weapon that can enter this branch is the laser
					everytick[i] = true;

					if (weapon->weaponnum == WEAPON_LASER) {
						dorecoil = false;
					}
				} else {
					dorecoil = false;
					dooneburst = true;
				}

				// There's an easter egg here: Any guard with Chris T's head
				// (Foster from the firing range) can fire multiple shots with
				// the magnum.
				if (weapon->weaponnum == WEAPON_ROCKETLAUNCHER
						|| weapon->weaponnum == WEAPON_ROCKETLAUNCHER_34
						|| weapon->weaponnum == WEAPON_SLAYER
						|| weapon->weaponnum == WEAPON_DEVASTATOR
						|| (
							!g_Vars.normmplayerisrunning
							&& weapon->weaponnum == WEAPON_DY357MAGNUM
							&& chr->headnum != HEAD_JONATHAN
							&& chr->headnum != HEAD_CHRIST)
						|| (
							!g_Vars.normmplayerisrunning
							&& weapon->weaponnum == WEAPON_DY357LX)
						|| (
							!g_Vars.normmplayerisrunning
							&& weapon->weaponnum == WEAPON_SHOTGUN)) {
					singleshot[i] = true;
				}
			}
		}

		chr->act_attack.turning = TURNSTATE_TURNING;
		chr->act_attack.animcfg = animcfg;
		chr->act_attack.fired = false;
		chr->act_attack.nextgun = random() % 2;
		chr->act_attack.firegun[HAND_LEFT] = firing[HAND_LEFT];
		chr->act_attack.firegun[HAND_RIGHT] = firing[HAND_RIGHT];
		chr->act_attack.everytick[HAND_LEFT] = everytick[HAND_LEFT];
		chr->act_attack.everytick[HAND_RIGHT] = everytick[HAND_RIGHT];
		chr->act_attack.singleshot[HAND_LEFT] = singleshot[HAND_LEFT];
		chr->act_attack.singleshot[HAND_RIGHT] = singleshot[HAND_RIGHT];
		chr->act_attack.dorecoil = dorecoil;
		chr->act_attack.dooneburst = dooneburst;
		chr->act_attack.pausecount = 0;
		chr->act_attack.numshots = 0;

		if (singleshot[HAND_LEFT] || singleshot[HAND_RIGHT]) {
			if (singleshot[HAND_LEFT] && singleshot[HAND_RIGHT]) {
				chr->act_attack.maxshots = 2;
			} else {
				chr->act_attack.maxshots = 1;
			}
		} else {
			if (attackflags & ATTACKFLAG_SINGLESHOT) {
				chr->act_attack.maxshots = 1;
			} else {
				chr->act_attack.maxshots = (random() % 4) + 2;
			}

			// @bug: ATTACKFLAG_SINGLESHOT is not respected here if both guns
			// are firing.
			if (firing[HAND_RIGHT] && firing[HAND_LEFT]) {
				chr->act_attack.maxshots += (random() % 4) + 2;
			}
		}

		chr->act_attack.flags = attackflags;
		chr->act_attack.entityid = entityid;
		chr->act_attack.standing = standing;
		chr->act_attack.reaim = 0;
		chr->act_attack.lastfire60 = 0;
		chr->act_attack.lastontarget60 = 0;
		chr->act_attack.flip = flip;

		chr->sleep = 0;
		chr->chrflags &= ~CHRCFLAG_INJUREDTARGET;

		if (!sniping && !chr->aibot) {
			if (modelIsAnimMerging(chr->model)) {
				chr->hidden |= CHRHFLAG_NEEDANIM;
			} else {
				modelSetAnimation(model, animcfg->animnum, flip, animcfg->unk10, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);
				func0f031254(chr);

				chr->hidden &= ~CHRHFLAG_NEEDANIM;
			}
		}
	}
}

void chrAttackAmount(struct chrdata *chr, u32 attackflags, u32 entityid, u32 maxshots)
{
	u32 stack;
	struct prop *prop = chrGetHeldProp(chr, 0);
	struct attackanimgroup **things = NULL;
	bool firing[] = {false, false};
	u32 race = CHRRACE(chr);

	if (prop) {
		things = weaponIsOneHanded(prop) ? g_StandLightAttackAnims[race] : g_StandHeavyAttackAnims[race];

		firing[1] = false;
		firing[0] = true;
	}

	chrAttack(chr, things, false, firing, attackflags, entityid, false);

	chr->actiontype = ACT_ATTACKAMOUNT;
	chr->act_attack.numshots = 0;
	chr->act_attack.maxshots = maxshots;
	chr->act_attack.dooneburst = false;
}

#if PAL
s32 g_DrCarollDyingTimer = 8;
#else
s32 g_DrCarollDyingTimer = 10;
#endif

u8 var80068080 = 50;

/**
 * Given a perfectly alive chr, make them begin the process of dying or being
 * knocked unconscious.
 *
 * This function handles:
 * - Eyespy destruction
 * - Transitioning to ACT_DIE
 * - Choosing and applying death animations
 * - Updating kill statistics
 * - Dropping items
 */
void chrBeginDeath(struct chrdata *chr, struct coord *dir, f32 relangle, s32 hitpart, struct gset *gset, bool knockout, s32 aplayernum)
{
	bool overridden = false;
	bool instant;
	s32 index = -1;
	s32 animnum;
	u32 stack1;
	struct prop *prop = chr->prop;
	struct model *model = chr->model;
	u32 stack2;
	s32 race = CHRRACE(chr);
	bool wasknockedout = false;
	s32 prevplayernum;
	s32 i;
	s32 buddyplayernum;
	struct eyespy *eyespy;
	s32 objectivenum;
	f32 mult1;
	f32 mult2;
	f32 mult3;

	// If chr was previously knocked out, they are now dead so decrease KO counter
	if (chr->actiontype == ACT_DRUGGEDCOMINGUP
			|| chr->actiontype == ACT_DRUGGEDDROP
			|| chr->actiontype == ACT_DRUGGEDKO) {
#if VERSION >= VERSION_NTSC_1_0
		if (chr->actiontype == ACT_DRUGGEDKO) {
			wasknockedout = true;
		}
#else
		wasknockedout = true;
#endif

		mpstatsDecrementTotalKnockoutCount();
	}

	// Handle eyespy then return early
	if (race == RACE_EYESPY) {
		prevplayernum = g_Vars.currentplayernum;
		buddyplayernum = -1;
		eyespy = chrToEyespy(chr);
		objectivenum = -1;

		// Figure out which playernum has the eyespy that's being destroyed,
		// and the buddy's playernum if applicable. Note that the player count
		// can only be 1 or 2 here.
		for (i = 0; i < PLAYERCOUNT(); i++) {
			if (eyespy == g_Vars.players[i]->eyespy) {
				setCurrentPlayerNum(i);
			} else {
				buddyplayernum = i;
			}
		}

		if (g_Vars.currentplayer->eyespy) {
			// Stop using eyespy if active
			if (g_Vars.currentplayer->eyespy->active) {
				g_Vars.currentplayer->eyespy->active = false;
				g_Vars.currentplayer->devicesactive &= ~DEVICE_EYESPY;
			}

			// Destroy the eyespy
			chr->hidden |= CHRHFLAG_REAPED;

			explosionCreateSimple(g_Vars.currentplayer->eyespy->prop,
					&g_Vars.currentplayer->eyespy->prop->pos,
					g_Vars.currentplayer->eyespy->prop->rooms, EXPLOSIONTYPE_2, 0);
			invRemoveItemByNum(WEAPON_EYESPY);

			func0f0926bc(g_Vars.currentplayer->eyespy->prop, 1, 0xffff);
			g_Vars.currentplayer->eyespy = NULL;
			setCurrentPlayerNum(prevplayernum);

			// For Investigation and G5 Building, set a stage flag to show that
			// the eyespy is destroyed. The scripting in those stages checks for
			// this flag and fails the objective if set.
			switch (stageGetIndex(g_Vars.stagenum)) {
			case STAGEINDEX_INVESTIGATION:
				objectivenum = 0;
				break;
			case STAGEINDEX_G5BUILDING:
				if (lvGetDifficulty() == DIFF_A) {
					objectivenum = 2;
				} else if (lvGetDifficulty() == DIFF_SA) {
					objectivenum = 2;
				} else {
					objectivenum = 2;
				}
				break;
			}

			// But don't set the flag if the coop buddy still has an eyespy
			if (objectivenum >= 0 && buddyplayernum >= 0) {
				setCurrentPlayerNum(buddyplayernum);

				if (g_Vars.currentplayer->eyespy) {
					objectivenum = -1;
				}

				setCurrentPlayerNum(prevplayernum);
			}

			if (objectivenum >= 0 && objectiveCheck(objectivenum) != OBJECTIVE_COMPLETE) {
				g_StageFlags |= STAGEFLAG_EYESPY_DESTROYED;
			}
		}

		setCurrentPlayerNum(prevplayernum);
		return;
	}

	// instant = whether to merge into death animation or switch to it instantly
	instant = chr->actiontype == ACT_ARGH && chr->act_argh.lvframe60 == g_Vars.lvframe60;

	for (i = 0; g_AnimTablesByRace[race][i].hitpart != -1; i++) {
		if (g_AnimTablesByRace[race][i].hitpart == hitpart) {
			index = i;
			break;
		}
	}

	// Set up chr's new action
	chr->blurdrugamount = 0;

	chrStopFiring(chr);
	chrUncloak(chr, true);

#if VERSION >= VERSION_NTSC_1_0
	chr->chrflags &= ~CHRCFLAG_HIDDEN;
#endif

	chr->actiontype = (knockout == true ? ACT_DRUGGEDDROP : ACT_DIE);

	chr->act_die.notifychrindex = 0;
	chr->act_die.timeextra = 0;
	chr->act_die.drcarollimagedelay = PALDOWN(45);
	chr->act_die.thudframe1 = -1;
	chr->act_die.thudframe2 = -1;

	if (chr->race == RACE_DRCAROLL) {
		chr->drcarollimage_left = (s32)((random() % 400) * 0.01f) + 1;
		chr->drcarollimage_right = (s32)((random() % 400) * 0.01f) + 1;
	}

	chr->sleep = 0;

	// Handle robots and Dr Caroll then return early
	if (race == RACE_ROBOT || race == RACE_DRCAROLL) {
		mult1 = gsetGetStrength(gset) * 0.5f;

		if (mult1 <= 0) {
			mult1 = 3;
		}

		if (mult1 != 0.0f) {
			chr->elapseextra = 0;
			chr->timeextra = mult1 * 15;
			chr->extraspeed.x = dir->x * mult1;
			chr->extraspeed.y = dir->y * mult1;
			chr->extraspeed.z = dir->z * mult1;
		}

		if (race == RACE_DRCAROLL) {
			g_DrCarollDyingTimer = 0;

			chr->soundtimer = 0;
			chr->voicebox = VOICEBOX_MALE1;

			modelSetAnimation(chr->model, ANIM_0164, false, 0, 0.5f, 16);
		}

		return;
	}

	// Handle humans and Skedar
	if (race == RACE_HUMAN) {
		animnum = modelGetAnimNum(chr->model);

		// Chrs in lying-down sniping poses don't use standard death animations
		if (animnum == ANIM_SNIPING_GETDOWN
				|| animnum == ANIM_SNIPING_GETUP
				|| animnum == ANIM_SNIPING_ONGROUND) {
			modelSetAnimation(chr->model, ANIM_SNIPING_DIE, false, 0, 0.5f, 16);
		} else {
			// Consider making the chr do an animation where they slump against
			// a wall or object which is behind them.
			if ((relangle < 1.5705462694168f || relangle > 4.7116389274597f)
					&& random() % 20 == 0
					&& chr->specialdie == SPECIALDIE_NONE) {
				f32 angle1;
				f32 angle2 = chrGetInverseTheta(chr);
				f32 fval1;
				f32 fval2;

				angle1 = angle2 + 3.3155977725983f;
				angle2 += 2.966587305069f;

				if (angle1 >= M_BADTAU) {
					angle1 -= M_BADTAU;
				}

				if (angle2 >= M_BADTAU) {
					angle2 -= M_BADTAU;
				}

				fval1 = func0f02e684(prop, angle1, 150);
				fval2 = func0f02e684(prop, angle2, 150);

				if (fval1 < 150 && fval2 < 150
						&& fval1 - fval2 < 10 && fval1 - fval2 > -10
						&& !wasknockedout) {
					struct animtablerow *row = &g_AnimTableHumanSlumped[random() % 4];
					u32 stack3;

					chr->act_die.thudframe1 = row->thudframe1;
					chr->act_die.thudframe2 = row->thudframe2;

					modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, !instant);

					if (row->endframe >= 0) {
						modelSetAnimEndFrame(model, row->endframe);
					}

					chr->chrwidth = 10;
					chr->chrflags &= ~CHRCFLAG_HAS_SPECIAL_DEATH_ANIMATION;

					overridden = true;
				}
			}

			// Consider making the chr do a fall forward animation.
			// The player must be behind the chr for it to happen.
			if (relangle > 2.3558194637299f && relangle < 3.9263656139374f
					&& random() % 5 < 2
					&& chr->specialdie == SPECIALDIE_NONE) {
				struct animtablerow *row;

				struct animtablerow rows[] = {
					{ 0x005b, 0, -1, 0.6, 0, 27, -1 },
					{ 0x0255, 0, -1, 0.5, 0, 25, -1 },
				};

				bool flip;

				overridden = true;

				if (hitpart == HITPART_LBICEP || hitpart == HITPART_RBICEP) {
					row = &rows[0];

					if (hitpart == HITPART_LBICEP) {
						flip = true;
					} else {
						flip = false;
					}
				} else {
					row = &rows[1];
					flip = random() % 2;
				}

				chr->act_die.thudframe1 = row->thudframe1;
				chr->act_die.thudframe2 = row->thudframe2;

				modelSetAnimationWithMerge(model, row->animnum, flip, 0, row->speed, 16, !instant);

				if (row->endframe >= 0) {
					modelSetAnimEndFrame(model, chrGetRangedArghSpeed(chr, row->endframe, 8));
				} else {
					modelSetAnimEndFrame(model, chrGetRangedArghSpeed(chr, animGetNumFrames(row->animnum) - 1, 8));
				}

				chr->chrflags &= ~CHRCFLAG_HAS_SPECIAL_DEATH_ANIMATION;
			}

			if (!overridden && index >= 0) {
				// Handle specialdie animations or choose a random one if not
				// using specialdie
				if (g_AnimTablesByRace[race][index].deathanims
						&& g_AnimTablesByRace[race][index].deathanimcount > 0
						&& !wasknockedout) {
					struct animtablerow *row;

					if (chr->specialdie == SPECIALDIE_NONE) {
						s32 tmp = random() % g_AnimTablesByRace[race][index].deathanimcount;
						row = &g_AnimTablesByRace[race][index].deathanims[tmp];
					} else if (chr->specialdie == SPECIALDIE_ONCHAIR) {
						row = &g_SpecialDieAnims[chr->specialdie + random() % 2];

						// chr->myspecial is the tag number of the chr's chair
						if (chr->myspecial >= 0) {
							struct defaultobj *obj = objFindByTagId(chr->myspecial);
							obj->flags3 &= ~OBJFLAG3_PUSHABLE;
							obj->flags |= OBJFLAG_INVINCIBLE;

							// The original source likely didn't have the brackets here,
							// but I'm including them to show the logic that's actually
							// being used. There is no bug here, as obj and obj->prop
							// are always set at this point so these checks are
							// unnecessary.
							if ((obj && obj->prop && obj->modelnum == MODEL_DD_REDARM)
									|| obj->modelnum == MODEL_DD_REDSOFA) {
								row = &g_SpecialDieAnims[chr->specialdie - 1];
							}
						}
					} else {
						row = &g_SpecialDieAnims[chr->specialdie - 1];
					}

					chr->act_die.thudframe1 = row->thudframe1;
					chr->act_die.thudframe2 = row->thudframe2;

					if (chr->specialdie == SPECIALDIE_NONE) {
						modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, !instant);
					} else {
						modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 30, !instant);
					}

					if (row->endframe >= 0) {
						modelSetAnimEndFrame(model, row->endframe);
					}

					mult2 = gsetGetStrength(gset);

					if (mult2 <= 0 && (chr->chrflags & CHRCFLAG_DIEWITHFORCE)) {
						mult2 = 6;
					}

					if (row->unk10 && mult2 > 0) {
						chr->act_die.timeextra = mult2 * 15;
						chr->act_die.elapseextra = 0;
						chr->act_die.extraspeed.x = dir->x * mult2;
						chr->act_die.extraspeed.y = dir->y * mult2;
						chr->act_die.extraspeed.z = dir->z * mult2;
					}

					chr->chrflags &= ~CHRCFLAG_HAS_SPECIAL_DEATH_ANIMATION;
				}
			}
		}
	} else if (race == RACE_SKEDAR) {
		struct animtablerow *row;

		if (relangle > 2.3558194637299f && relangle < 3.9263656139374f) {
			// Player is behind the Skedar - use specific set of anims
			row = &g_AnimTablesByRace[race][1 + (random() % 6)].deathanims[random() % 3];

			chr->act_die.thudframe1 = row->thudframe1;
			chr->act_die.thudframe2 = row->thudframe2;

			modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, !instant);

			if (row->endframe >= 0) {
				modelSetAnimEndFrame(model, row->endframe);
			}
		} else {
			// Normal Skedar death
			if (index >= 0
					&& g_AnimTablesByRace[race][index].deathanims != NULL
					&& g_AnimTablesByRace[race][index].deathanimcount > 0) {
				s32 tmp = random() % g_AnimTablesByRace[race][index].deathanimcount;
				row = &g_AnimTablesByRace[race][index].deathanims[tmp];
			} else {
				row = &g_AnimTablesByRace[race][0].deathanims[0];
			}

			chr->act_die.thudframe1 = row->thudframe1;
			chr->act_die.thudframe2 = row->thudframe2;

			modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, !instant);

			if (row->endframe >= 0) {
				modelSetAnimEndFrame(model, row->endframe);
			}

			mult3 = gsetGetStrength(gset);

			if (mult3 <= 0 && (chr->chrflags & CHRCFLAG_DIEWITHFORCE)) {
				mult3 = 6;
			}

			if (row->unk10 != 0 && mult3 > 0) {
				chr->act_die.timeextra = mult3 * 15;
				chr->act_die.elapseextra = 0;
				chr->act_die.extraspeed.x = dir->x * mult3;
				chr->act_die.extraspeed.y = dir->y * mult3;
				chr->act_die.extraspeed.z = dir->z * mult3;
			}
		}
	} else if (race == RACE_DRCAROLL) {
		// empty
	}

	// Handle multiplayer stats and kill count
	if (g_Vars.mplayerisrunning) {
		mpstatsRecordDeath(aplayernum, mpPlayerGetIndex(chr));
	} else if (aplayernum >= 0) {
		s32 prevplayernum = g_Vars.currentplayernum;
		setCurrentPlayerNum(aplayernum);
		mpstatsRecordPlayerKill();
		setCurrentPlayerNum(prevplayernum);
	}

	if (chr->chrflags & CHRCFLAG_KILLCOUNTABLE) {
		mpstatsIncrementTotalKillCount();
	}

	// Drop items
	if (race == RACE_HUMAN || race == RACE_SKEDAR) {
		if (chr->weapons_held[0] && (chr->weapons_held[0]->obj->flags & OBJFLAG_AIUNDROPPABLE) == 0) {
			objSetDropped(chr->weapons_held[0], DROPTYPE_DEFAULT);
			chr->hidden |= CHRHFLAG_00000001;
		}

		if (chr->weapons_held[1] && (chr->weapons_held[1]->obj->flags & OBJFLAG_AIUNDROPPABLE) == 0) {
			objSetDropped(chr->weapons_held[1], DROPTYPE_DEFAULT);
			chr->hidden |= CHRHFLAG_00000001;
		}

		chrDropConcealedItems(chr);
	}
}

void chrBeginArgh(struct chrdata *chr, f32 angle, s32 hitpart)
{
	bool doneanim = false;
	s32 instant;
	s32 index = -1;
	struct model *model = chr->model;
	s32 i;
	s32 race = CHRRACE(chr);
	s32 animnum = modelGetAnimNum(chr->model);

	if (animnum == ANIM_SNIPING_GETDOWN
			|| animnum == ANIM_SNIPING_GETUP
			|| animnum == ANIM_SNIPING_ONGROUND) {
		chrFlinchBody(chr);
		return;
	}

	if (race == RACE_EYESPY || chr->aibot) {
		return;
	}

	if (race == RACE_DRCAROLL) {
		chr->actiontype = ACT_ARGH;
		chr->act_argh.notifychrindex = 0;
		chr->act_argh.lvframe60 = g_Vars.lvframe60;

		chr->sleep = 0;

		modelSetAnimation(chr->model, ANIM_0163, false, 0, 0.5f, 16);

		chr->drcarollimage_left = DRCAROLLIMAGE_X;
		chr->drcarollimage_right = DRCAROLLIMAGE_X;
		return;
	}

	instant = chr->actiontype == ACT_ARGH && chr->act_argh.lvframe60 == g_Vars.lvframe60;

	for (i = 0; g_AnimTablesByRace[race][i].hitpart != -1; i++) {
		if (g_AnimTablesByRace[race][i].hitpart == hitpart) {
			index = i;

			if (chr->hitpart == 0) {
				chr->hitpart = hitpart;
			}

			break;
		}
	}

	// If shot in the butt from behind, 2 in 5 chance of doing a special anim
	if (race == RACE_HUMAN
			&& hitpart == HITPART_PELVIS
			&& angle > 2.3558194637299f
			&& angle < 3.9263656139374f
			&& random() % 5 < 2) {
		struct animtablerow *row;
		struct animtablerow rows[] = {
			{ 0x013b, 0, -1, 0.5, 0, -1, -1 },
			{ 0x013c, 0, -1, 0.5, 0, -1, -1 },
			{ 0x013f, 0, -1, 0.5, 0, -1, -1 },
			{ 0x0142, 0, -1, 0.5, 0, -1, -1 },
			{ 0x0145, 0, -1, 0.5, 0, -1, -1 },
			{ 0x0148, 0, -1, 0.5, 0, -1, -1 },
			{ 0x0036, 0, -1, 0.5, 0, -1, -1 },
			{ 0x0037, 0, -1, 0.5, 0, -1, -1 },
		};

		chrStopFiring(chr);

		chr->actiontype = ACT_ARGH;
		chr->act_argh.notifychrindex = 0;
		chr->act_argh.lvframe60 = g_Vars.lvframe60;
		chr->sleep = 0;

		row = &rows[random() % 8];

		modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, !instant);

		if (row->endframe >= 0) {
			modelSetAnimEndFrame(model, chrGetRangedArghSpeed(chr, row->endframe, 8));
			doneanim = true;
		} else {
			modelSetAnimEndFrame(model, chrGetRangedArghSpeed(chr, animGetNumFrames(row->animnum) - 1, 8));
			doneanim = true;
		}
	}

	if (!doneanim
			&& index >= 0
			&& g_AnimTablesByRace[race][index].injuryanims
			&& g_AnimTablesByRace[race][index].injuryanimcount > 0) {
		// If shot in a hand that's holding a gun, remap the hit location to the
		// forearm because the hand injury animations assume the hand is empty.
		struct prop *lgun = chrGetHeldProp(chr, HAND_LEFT);
		struct prop *rgun = chrGetHeldProp(chr, HAND_RIGHT);
		s32 rowindex;
		struct animtablerow *row;

		if (race == RACE_HUMAN) {
			if (index == 9 && lgun) { // left hand
				index = 10; // left forearm
			} else if (index == 12 && rgun) { // right hand
				index = 13; // right forearm
			}
		}

		// Select a random animation for this hit location and apply it
		rowindex = random() % g_AnimTablesByRace[race][index].injuryanimcount;

		row = &g_AnimTablesByRace[race][index].injuryanims[rowindex];

		chrStopFiring(chr);

		chr->actiontype = ACT_ARGH;
		chr->act_argh.notifychrindex = 0;
		chr->act_argh.lvframe60 = g_Vars.lvframe60;
		chr->sleep = 0;

		modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, !instant);

		if (row->endframe >= 0) {
			modelSetAnimEndFrame(model, chrGetRangedArghSpeed(chr, row->endframe, 8));
		} else {
			modelSetAnimEndFrame(model, chrGetRangedArghSpeed(chr, animGetNumFrames(row->animnum) - 1, 8));
		}
	}
}

void chrReactToDamage(struct chrdata *chr, struct coord *vector, f32 angle, s32 hitpart, struct gset *gset, s32 aplayernum)
{
	s32 race = CHRRACE(chr);
	bool knockedout = false;
	s32 animnum = modelGetAnimNum(chr->model);

#if VERSION >= VERSION_NTSC_1_0
	if (chr->actiontype == ACT_DRUGGEDKO)
#else
	if (chr->actiontype == ACT_DRUGGEDCOMINGUP
			|| chr->actiontype == ACT_DRUGGEDDROP
			|| chr->actiontype == ACT_DRUGGEDKO)
#endif
	{
		knockedout = true;
	}

	if (race == RACE_EYESPY) {
		f32 strength = gsetGetStrength(gset);
		struct eyespy *eyespy = chrToEyespy(chr);

		if (eyespy) {
			if (strength <= 0) {
				strength = 6;
			}

			strength *= 4;

			eyespy->hit = 4;
			eyespy->vel.x += vector->x * strength;
			eyespy->vel.z += vector->z * strength;
		}
	}

	if (chr->damage >= chr->maxdamage) {
		chrBeginDeath(chr, vector, angle, hitpart, gset, false, aplayernum);
	} else if (animnum == ANIM_SNIPING_GETDOWN
			|| animnum == ANIM_SNIPING_GETUP
			|| animnum == ANIM_SNIPING_ONGROUND) {
		chrFlinchBody(chr);
	} else if (race == RACE_EYESPY) {
		// empty
	} else if (race == RACE_DRCAROLL || race == RACE_ROBOT) {
		f32 strength = gsetGetStrength(gset);

		if (race == RACE_DRCAROLL) {
			strength *= 0.5f;
		}

		if (strength <= 0) {
			strength = 6;
		}

		if (strength > 0) {
			chr->elapseextra = 0;
			chr->timeextra = strength * 15;
			chr->extraspeed.x = vector->x * strength;
			chr->extraspeed.y = vector->y * strength;
			chr->extraspeed.z = vector->z * strength;
		}

		if (race == RACE_DRCAROLL) {
			chrBeginArgh(chr, 0, 0);
		}
	} else if (!knockedout) {
		chrBeginArgh(chr, angle, hitpart);
	}
}

/**
 * Launch a chr away from the given pos (for explosions).
 */
void chrYeetFromPos(struct chrdata *chr, struct coord *exppos, f32 force)
{
	struct model *model = chr->model;
	struct prop *prop = chr->prop;
	f32 faceangle;
	f32 latangle;
	u32 stack1;
	s32 angleindex;
	u32 stack2;
	struct yeetanim *row;
	struct coord dist;
	u32 stack3;
	s32 race = CHRRACE(chr);
	f32 speed;
	s32 subindex;
	f32 angletoexplosion;

	if (race != RACE_DRCAROLL && race != RACE_EYESPY && race != RACE_ROBOT) {
		faceangle = chrGetInverseTheta(chr);
		latangle = atan2f(prop->pos.x - exppos->x, prop->pos.z - exppos->z);

		dist.x = prop->pos.x - exppos->x;
		dist.y = prop->pos.y - exppos->y;
		dist.z = prop->pos.z - exppos->z;

		if (dist.f[0] == 0 && dist.f[1] == 0 && dist.f[2] == 0) {
			dist.z = 1;
		}

		speed = 0.625f * force / sqrtf(dist.f[0] * dist.f[0] + dist.f[1] * dist.f[1] + dist.f[2] * dist.f[2]);
		angletoexplosion = latangle - faceangle;

		dist.x *= speed;
		dist.y *= speed;
		dist.z *= speed;

		chr->fallspeed.x = dist.x;
		chr->fallspeed.y = dist.y;
		chr->fallspeed.z = dist.z;

		if (latangle < faceangle) {
			angletoexplosion += M_BADTAU;
		}

		angleindex = angletoexplosion * 1.2734422683716f + 0.5f;

		if (angleindex >= 8) {
			angleindex = 0;
		}

		subindex = random() % g_YeetAnimIndexesByRaceAngle[race][angleindex].count;

		if (race == RACE_HUMAN) {
			row = &g_YeetAnimsHuman[g_YeetAnimIndexesByRaceAngle[race][angleindex].indexes[subindex]];
		} else if (race == RACE_SKEDAR) {
			row = &g_YeetAnimsSkedar[g_YeetAnimIndexesByRaceAngle[race][angleindex].indexes[subindex]];
		}

		chrStopFiring(chr);
		chrUncloak(chr, true);

#if VERSION >= VERSION_NTSC_1_0
		chr->chrflags &= ~CHRCFLAG_HIDDEN;
#endif

		chr->actiontype = ACT_DIE;

		chr->act_die.notifychrindex = 0;
		chr->act_die.thudframe1 = row->thudframe;
		chr->act_die.thudframe2 = -1;
		chr->act_die.timeextra = 0;
		chr->act_die.drcarollimagedelay = PALDOWN(45);

		if (chr->race == RACE_DRCAROLL) {
			chr->drcarollimage_left = 1 + (s32)((random() % 400) * 0.01f);
			chr->drcarollimage_right = 1 + (s32)((random() % 400) * 0.01f);
		}

		chr->sleep = 0;
		modelSetAnimation(model, row->animnum, row->flip, row->startframe, row->speed, 8);

		if (row->endframe >= 0.0f) {
			modelSetAnimEndFrame(model, row->endframe);
		}
	}
}

s32 gsetGetBlurAmount(struct gset *gset)
{
	s32 amount = PALDOWN(1000);

	if (g_Vars.normmplayerisrunning == false) {
		amount = PALDOWN(250);
	}

	if (gset->weaponnum == WEAPON_TRANQUILIZER) {
		amount = PALDOWN(2000);
	}

	if (gset->weaponnum == WEAPON_BOLT) {
		amount = PALDOWN(5000);
	}

	if (gset->weaponnum == WEAPON_NBOMB) {
		amount = PALDOWN(100);
	}

	return amount;
}

void chrKnockOut(struct chrdata *chr, f32 angle, s32 hitpart, struct gset *gset)
{
	if (chr->actiontype != ACT_DRUGGEDCOMINGUP
			&& chr->actiontype != ACT_DRUGGEDDROP
			&& chr->actiontype != ACT_DRUGGEDKO) {
#if VERSION >= VERSION_PAL_FINAL
		if (mpstatsGetTotalKnockoutCount() < 2) {
			chr->chrflags |= CHRCFLAG_KEEPCORPSEKO;

			if (mainGetStageNum() == STAGE_VILLA) {
				chr->hidden |= CHRHFLAG_ANTINONINTERACTABLE;
			}
		}
#elif VERSION >= VERSION_NTSC_1_0
		if (mpstatsGetTotalKnockoutCount() < 2) {
			chr->chrflags |= CHRCFLAG_KEEPCORPSEKO;
		}
#endif

		mpstatsIncrementTotalKnockoutCount();

		chr->actiontype = ACT_DRUGGEDCOMINGUP;
		chr->act_druggedcomingup.timer60 = 0;
	}
}

/**
 * Return true if the chr's current animation would be too awkward to transition
 * into an injury animation or if they're already in the PREARGH action state,
 * and set dst to the anim frame number where the chr will become available for
 * transition to an injury animation.
 *
 * The attack roll animation is the only one which is too awkward to transition.
 */
bool chrIsAnimPreventingArgh(struct chrdata *chr, f32 *dst)
{
	bool result = false;
	s32 race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_EYESPY || chr->aibot) {
		return false;
	}

	if (race == RACE_HUMAN) {
		s32 animnum = modelGetAnimNum(chr->model);
		f32 endframe;

		if (animnum == ANIM_SNIPING_GETDOWN
				|| animnum == ANIM_SNIPING_GETUP
				|| animnum == ANIM_SNIPING_ONGROUND) {
			chrFlinchBody(chr);
		} else if (chr->actiontype == ACT_ATTACKROLL
				&& modelGetAnimNum(chr->model) == chr->act_attack.animcfg->animnum) {
			if (chr->act_attack.onehanded) {
				if (chr->act_attack.animcfg == &g_RollAttackAnims[4]
						|| chr->act_attack.animcfg == &g_RollAttackAnims[5]
						|| chr->act_attack.animcfg == &g_RollAttackAnims[6]
						|| chr->act_attack.animcfg == &g_RollAttackAnims[7]) {
					endframe = chr->act_attack.animcfg->unk04 - 8;

					if (chr->act_attack.animcfg->unk14 < chr->act_attack.animcfg->unk04) {
						endframe = chr->act_attack.animcfg->unk14;
					}

					if (endframe > modelGetCurAnimFrame(chr->model)) {
						*dst = endframe;
						result = true;
					}
				}
			} else {
				endframe = chr->act_attack.animcfg->unk04 - 8;

				if (endframe > modelGetCurAnimFrame(chr->model)) {
					*dst = endframe;
					result = true;
				}
			}
		}
	}

	if (chr->actiontype == ACT_PREARGH) {
		result = true;
	}

	return result;
}

void chrChoke(struct chrdata *chr, s32 choketype)
{
	bool male = false;
	s16 soundnum = -1;
	s32 race = CHRRACE(chr);
	s32 playernum;
	s32 allowoverride = false;

	static s32 nextindexdrcaroll = 0;
	static s32 nextindexmaian = 0;
	static s32 nextindexskedar = 0;
	static s32 nextindexshock = 0;
	static s32 nextindexmale = 0;
	static s32 nextindexfemale = 0;

	if (race == RACE_EYESPY || race == RACE_ROBOT) {
		return;
	}

	if (chr->prop->type == PROPTYPE_PLAYER) {
		playernum = propGetPlayerNum(chr->prop);

		if (g_Vars.players[playernum]->isdead) {
			return;
		}
	}

	if (g_HeadsAndBodies[chr->headnum].ismale) {
		male = true;
	}

	if (race == RACE_DRCAROLL) {
		s16 sounds[] = {
			SFX_ARGH_DRCAROLL_0240,
			SFX_ARGH_DRCAROLL_024C,
			SFX_ARGH_DRCAROLL_0250,
			SFX_ARGH_DRCAROLL_0251,
			SFX_ARGH_DRCAROLL_0259,
			SFX_ARGH_DRCAROLL_025A,
		};

		if (g_DrCarollDyingTimer > PALDOWN(10)) {
			g_DrCarollDyingTimer = 0;

			soundnum = sounds[nextindexdrcaroll];
			nextindexdrcaroll++;

			if (nextindexdrcaroll >= ARRAYCOUNT(sounds)) {
				nextindexdrcaroll = 0;
			}
		}
	} else if (chr->headnum == HEAD_THEKING
			|| chr->headnum == HEAD_ELVIS
			|| chr->headnum == HEAD_MAIAN_S
			|| chr->headnum == HEAD_ELVIS_GOGS) {
		s16 sounds[] = {
			SFX_ARGH_MAIAN_05DF,
			SFX_ARGH_MAIAN_05E0,
			SFX_ARGH_MAIAN_05E1
		};

		soundnum = sounds[random() % 3];
		nextindexmaian++;

		if (nextindexmaian >= ARRAYCOUNT(sounds)) {
			nextindexmaian = 0;
		}
	} else if (race == RACE_SKEDAR) {
		if (chr->bodynum == BODY_MINISKEDAR) {
			s16 sounds[] = {
				SFX_SKEDAR_ROAR_0536,
				SFX_SKEDAR_ROAR_0537,
				SFX_SKEDAR_ROAR_0538,
				SFX_SKEDAR_ROAR_0539,
				SFX_SKEDAR_ROAR_053A,
			};

			soundnum = sounds[random() % 5];
			nextindexskedar++;

			if (nextindexskedar >= ARRAYCOUNT(sounds)) {
				nextindexskedar = 0;
			}
		} else {
			s16 sounds[] = {
				SFX_SKEDAR_ROAR_052D,
				SFX_SKEDAR_ROAR_052E,
				SFX_SKEDAR_ROAR_052F,
			};

			soundnum = sounds[random() % 3];
			nextindexskedar++;

			if (nextindexskedar >= ARRAYCOUNT(sounds)) {
				nextindexskedar = 0;
			}
		}
	} else if (chr->headnum == HEAD_DDSHOCK) {
		s16 sounds[] = {
			SFX_ARGH_MALE_0086,
			SFX_ARGH_MALE_0088,
			SFX_ARGH_MALE_008A,
			SFX_ARGH_MALE_008C,
			SFX_ARGH_MALE_008E,
			SFX_ARGH_MALE_0090,
			SFX_ARGH_MALE_0092,
			SFX_ARGH_MALE_0094,
			SFX_ARGH_MALE_0096,
			SFX_ARGH_MALE_0098,
			SFX_ARGH_MALE_009A,
			SFX_ARGH_MALE_009C,
			SFX_ARGH_MALE_009E,
			SFX_ARGH_MALE_0087,
		};

		soundnum = sounds[nextindexshock];
		nextindexshock++;

		if (nextindexshock >= ARRAYCOUNT(sounds)) {
			nextindexshock = 0;
		}

		allowoverride = true;
	} else if (male) {
		s16 sounds[] = {
			SFX_ARGH_MALE_0086,
			SFX_ARGH_MALE_0087,
			SFX_ARGH_MALE_0088,
			SFX_ARGH_MALE_0089,
			SFX_ARGH_MALE_008A,
			SFX_ARGH_MALE_008B,
			SFX_ARGH_MALE_008C,
			SFX_ARGH_MALE_008D,
			SFX_ARGH_MALE_008E,
			SFX_ARGH_MALE_008F,
			SFX_ARGH_MALE_0090,
			SFX_ARGH_MALE_0091,
			SFX_ARGH_MALE_0092,
			SFX_ARGH_MALE_0093,
			SFX_ARGH_MALE_0094,
			SFX_ARGH_MALE_0095,
			SFX_ARGH_MALE_0096,
			SFX_ARGH_MALE_0097,
			SFX_ARGH_MALE_0098,
			SFX_ARGH_MALE_0099,
			SFX_ARGH_MALE_009A,
			SFX_ARGH_MALE_009B,
			SFX_ARGH_MALE_009C,
			SFX_ARGH_MALE_009D,
			SFX_ARGH_MALE_009E,
		};

		soundnum = sounds[nextindexmale];
		nextindexmale++;

		allowoverride = true;

		if (nextindexmale >= ARRAYCOUNT(sounds)) {
			nextindexmale = 0;
		}
	} else if (chr->headnum == HEAD_DARK_COMBAT
			|| chr->headnum == HEAD_DARK_FROCK
			|| chr->headnum == HEAD_DARKAQUA
			|| chr->headnum == HEAD_DARK_SNOW) {
		s16 sounds[] = {
			SFX_ARGH_JO_02AA,
			SFX_ARGH_JO_02AB,
			SFX_ARGH_JO_02AC,
			SFX_ARGH_JO_02AD,
			SFX_ARGH_JO_02AE,
			SFX_ARGH_JO_02AF,
			SFX_ARGH_JO_02B0,
			SFX_ARGH_JO_02B1,
			SFX_ARGH_JO_02B2,
			SFX_ARGH_JO_02B3,
		};

		soundnum = sounds[random() % 10];
		allowoverride = true;
	} else {
		s16 sounds[] = {
			SFX_ARGH_FEMALE_000D,
			SFX_ARGH_FEMALE_000E,
			SFX_ARGH_FEMALE_000F,
		};

		soundnum = sounds[nextindexfemale];
		nextindexfemale++;

		if (nextindexfemale >= ARRAYCOUNT(sounds)) {
			nextindexfemale = 0;
		}

		allowoverride = true;
	}

	if (allowoverride) {
		if (choketype == CHOKETYPE_GURGLE) {
			s32 sounds[] = {
				SFX_M1_CHOKING,
				SFX_GURGLE_05B1,
				SFX_GURGLE_05B2,
			};

			if ((random() % 8) == 0) {
				soundnum = sounds[random() % 3];
			}

			chr->soundgap = 10;
			chr->soundtimer = 0;
		} else if (choketype == CHOKETYPE_COUGH) {
			if (male) {
				if ((random() % 2) == 0) {
					soundnum = SFX_COUGH_04AF;
				} else {
					soundnum = SFX_COUGH_04B0;
				}
			} else {
				s32 index = random() % 4;
				s32 sounds[] = {
					SFX_COUGH_05AB,
					SFX_COUGH_05AC,
					SFX_COUGH_05AD,
					SFX_COUGH_05AE,
				};

				soundnum = sounds[index];
			}

			chr->soundgap = 10;
			chr->soundtimer = 0;
		}
	}

	if (soundnum >= 0) {
		if (chr->prop->type == PROPTYPE_PLAYER) {
			if (g_Vars.players[playernum]->chokehandle == NULL) {
				sndStart(var80095200, soundnum, &g_Vars.players[playernum]->chokehandle, -1, -1, -1, -1, -1);
			}
		} else {
			func0f0926bc(chr->prop, 9, 0);

			if (!func0f092610(chr->prop, 13)) {
				func0f0939f8(NULL, chr->prop, soundnum, -1,
						-1, 0, 0, 13, NULL, -1, NULL, -1, -1, -1, -1);
			}
		}
	}
}

f32 chrGetShield(struct chrdata *chr)
{
	return chr->cshield;
}

void chrSetShield(struct chrdata *chr, f32 amount)
{
	if (amount < 0) {
		amount = 0;
	}

	chr->cshield = amount;

	if ((chr->hidden & CHRHFLAG_INFINITESHIELD) && chr->cshield < 1) {
		chr->cshield = 1;
	}

	if (chr->prop->type == PROPTYPE_PLAYER) {
		s32 playernum = propGetPlayerNum(chr->prop);

		if (playernum >= 0) {
			s32 prevplayernum = g_Vars.currentplayernum;
			setCurrentPlayerNum(playernum);
			currentPlayerDisplayHealth();
			g_Vars.currentplayerstats->armourcount += amount * 0.125f;
			setCurrentPlayerNum(prevplayernum);
		}
	}
}

bool func0f034080(struct chrdata *chr, struct modelnode *node, struct prop *prop, struct model *model, s32 side, s16 *arg5)
{
	if (chrGetShield(chr) > 0) {
		if (node && (node->type & 0xff) == MODELNODETYPE_BBOX) {
			shieldhitCreate(chr->prop, chrGetShield(chr), prop, node, model, side, arg5);
		}

		return true;
	}

	return false;
}

/**
 * Damage the chr, bypassing any shield.
 *
 * Used for knife poison, nbomb damage, Investigation radioactivity and Escape gas.
 */
void chrDamageByMisc(struct chrdata *chr, f32 damage, struct coord *vector, struct gset *gset, struct prop *prop)
{
	chrDamage(chr, damage, vector, gset, prop, HITPART_GENERAL,
			false,     // damageshield
			NULL,      // prop2
			NULL,      // node
			NULL,      // model
			-1,        // side
			NULL,      // arg11
			false,     // explosion
			NULL);     // explosionpos
}

void chrDamageByLaser(struct chrdata *chr, f32 damage, struct coord *vector, struct gset *gset, struct prop *prop)
{
	chrDamage(chr, damage, vector, gset, prop, HITPART_GENERAL,
			true,      // damageshield
			chr->prop, // prop2
			NULL,      // node
			NULL,      // model
			-1,        // side
			NULL,      // arg11
			false,     // explosion
			NULL);     // explosionpos
}

void func0f0341dc(struct chrdata *chr, f32 damage, struct coord *vector, struct gset *gset, struct prop *prop, s32 hitpart, struct prop *prop2, struct modelnode *node, struct model *model, s32 side, s16 *arg10)
{
	chrDamage(chr, damage, vector, gset, prop, hitpart,
			true,      // damageshield
			prop2,     // prop2
			node,      // node
			model,     // model
			side,      // side
			arg10,     // arg11
			false,     // explosion
			NULL);     // explosionpos
}

/**
 * Unused, and same as chrDamageByImpact but sets hitpart to HITPART_GENERAL instead of argument.
 */
void func0f034248(struct chrdata *chr, f32 damage, struct coord *vector, struct gset *gset, struct prop *prop)
{
	struct modelnode *node = NULL;
	struct model *model = NULL;
	s32 side = 0;
	s32 hitpart = HITPART_GENERAL;

	if (chrGetShield(chr) >= 0 && chr->model) {
		chrCalculateShieldHit(chr, &chr->prop->pos, vector, &node, &hitpart, &model, &side);
	}

	chrDamage(chr, damage, vector, gset, prop, HITPART_GENERAL,
			true,      // damageshield
			chr->prop, // prop2
			node,      // node
			model,     // model
			side,      // side
			NULL,      // arg11
			false,     // explosion
			NULL);     // explosionpos
}

/**
 * Used for punching, but also used by AI commands to make chrs take damage.
 */
void chrDamageByImpact(struct chrdata *chr, f32 damage, struct coord *vector, struct gset *gset, struct prop *prop, s32 hitpart)
{
	struct modelnode *node = NULL;
	struct model *model = NULL;
	s32 side = 0;

	if (chrGetShield(chr) >= 0 && chr->model) {
		chrCalculateShieldHit(chr, &chr->prop->pos, vector, &node, &hitpart, &model, &side);
	}

	chrDamage(chr, damage, vector, gset, prop, hitpart,
			true,      // damageshield
			chr->prop, // prop2
			node,      // node
			model,     // model
			side,      // side
			NULL,      // arg11
			false,     // explosion
			NULL);     // explosionpos
}

void chrDamageByExplosion(struct chrdata *chr, f32 damage, struct coord *vector, struct prop *prop, struct coord *explosionpos)
{
	chrDamage(chr, damage, vector, NULL, prop, HITPART_GENERAL,
			true,      // damageshield
			chr->prop, // prop2
			NULL,      // node
			NULL,      // model
			-1,        // side
			NULL,      // arg11
			true,      // explosion
			explosionpos);
}

void playerUpdateDamageStats(struct prop *attacker, struct prop *victim, f32 damage)
{
	s32 playernum;

	if (attacker && attacker->type == PROPTYPE_PLAYER) {
		playernum = propGetPlayerNum(attacker);

		if (playernum >= 0) {
			g_Vars.playerstats[playernum].damtransmitted += damage;
		}
	}

	if (victim && victim->type == PROPTYPE_PLAYER) {
		playernum = propGetPlayerNum(victim);

		if (playernum >= 0) {
			g_Vars.playerstats[playernum].damreceived += damage;
		}
	}
}

/**
 * Handle a chr being damaged.
 *
 * Calculates and damage based on many factors and applies it to the chr,
 * killing them if needed.
 *
 * The chr can be a player, aibot or regular chr. The chr can also be of any
 * race (human, Skedar, Dr Caroll, robot or eyespy).
 *
 * chr - the chr being damaged
 * damage - the base amount of damage to deal, prior to scaling factors
 * vector - position of the attacker?
 * gset - gun settings struct
 * aprop - the attacker's prop struct
 * hitpart - "i've been hit" value, ie. the body part (see HITPART constants)
 * damageshield - false if attack should bypass shield if any
 * prop2 - ?
 * node - if shielded, model node (of type bbox) which was hit
 * model - if shielded, model of chr
 * side - if shielded, side of the model node's bounding box which was hit (0-5)
 * arg11 - ?
 * explosion - true if damage is coming from an explosion
 * explosionpos - position of said explosion
 */
void chrDamage(struct chrdata *chr, f32 damage, struct coord *vector, struct gset *gset,
		struct prop *aprop, s32 hitpart, bool damageshield, struct prop *prop2,
		struct modelnode *node, struct model *model, s32 side, s16 *arg11,
		bool explosion, struct coord *explosionpos)
{
	bool onehitko = false;
	s32 race = CHRRACE(chr);
	f32 shield;
	bool makedizzy;
	bool isclose;
	struct prop *vprop = chr->prop;
	f32 headshotdamagescale = 1;
	bool usedshield = false;
	bool showshield = false;
	bool showdamage = false;
	struct gset gset2 = {0};
	f32 explosionforce = damage;
	f32 healthscale = 1;
	f32 armourscale = 1;
	bool isfar = true;
	bool forceapplydamage = false;
	struct weaponfunc *func;
	f32 amount;
	bool canchoke = true;
	s32 aplayernum = -1;
	s32 choketype = CHOKETYPE_NONE;

	if (hitpart == HITPART_HEAD) {
		choketype = CHOKETYPE_GURGLE;
	}

	if (gset) {
		if (gset->weaponnum == WEAPON_COMBATKNIFE) {
			if (gset->weaponfunc == FUNC_2) {
				canchoke = false;
			}

			if (gset->weaponfunc == FUNC_POISON) {
				choketype = CHOKETYPE_COUGH;
			}
		} else if (gset->weaponnum == WEAPON_TRANQUILIZER) {
			if (gset->weaponfunc == FUNC_SECONDARY) {
				choketype = CHOKETYPE_GURGLE;
			}
		}
	}

	// Don't damage if in CI training outside of training session
	if (chr->prop == g_Vars.currentplayer->prop
			&& g_Vars.currentplayer->training == false
			&& mainGetStageNum() == STAGE_CITRAINING) {
		return;
	}

	// Don't damage if attacker was anti and chr is non-interactable by anti
	if (g_Vars.antiplayernum >= 0
			&& aprop
			&& aprop == g_Vars.anti->prop
			&& (chr->hidden & CHRHFLAG_ANTINONINTERACTABLE)) {
		return;
	}

	// Don't damage if coop and friendly fire is off (human buddy)
	if (g_Vars.coopplayernum >= 0
			&& g_Vars.coopfriendlyfire == false
			&& aprop
			&& aprop != vprop
			&& aprop->type == PROPTYPE_PLAYER
			&& vprop->type == PROPTYPE_PLAYER) {
		return;
	}

	// Don't damage if coop and friendly fire is off (AI buddy)
	if (g_MissionConfig.iscoop
			&& g_Vars.coopfriendlyfire == false
			&& aprop
			&& aprop != vprop
			&& (aprop->type == PROPTYPE_PLAYER || aprop->type == PROPTYPE_CHR)
			&& chr->team == TEAM_ALLY
			&& aprop->chr->team == TEAM_ALLY) {
		return;
	}

	// Don't allow coop AI to kill or destroy anything
	// which anti wouldn't be able to
	if (g_MissionConfig.iscoop
			&& aprop
			&& aprop != vprop
			&& aprop->type == PROPTYPE_CHR
			&& aprop->chr->team == TEAM_ALLY
			&& (chr->hidden & CHRHFLAG_ANTINONINTERACTABLE)) {
		return;
	}

	if (gset == NULL) {
		gset = &gset2;
	}

	func = gsetGetWeaponFunction(gset);
	isclose = func && (func->type & 0xff) == INVENTORYFUNCTYPE_CLOSE;
	makedizzy = race != RACE_DRCAROLL && gsetHasFunctionFlags(gset, FUNCFLAG_MAKEDIZZY);

	if (chr->prop == g_Vars.currentplayer->prop && g_Vars.currentplayer->invincible) {
		return;
	}

	if (isclose) {
		isfar = false;
	}

	// Set a flag on the victim that makes them switch to their "shot" AI list
	chr->chrflags |= CHRCFLAG_TRIGGERSHOTLIST;

	// Set a flag on the attacker so their AI scripting can tell that they've
	// hit their target
	if (aprop
			&& aprop->type == PROPTYPE_CHR
			&& chrGetTargetProp(aprop->chr) == chr->prop) {
		aprop->chr->chrflags |= CHRCFLAG_INJUREDTARGET;
	}

	// Disarm only hurts the victim in solo missions and if the victim is an NPC
	if (gsetHasFunctionFlags(gset, FUNCFLAG_DROPWEAPON)
			&& gset->weaponnum == WEAPON_UNARMED
			&& (vprop->type == PROPTYPE_PLAYER || g_Vars.normmplayerisrunning)) {
		damage = 0;
	}

	// Apply damage scaling based on difficulty settings
	if (g_Vars.mplayerisrunning == false) {
		// Solo
		if (explosion) {
			if (vprop->type == PROPTYPE_PLAYER) {
				damage *= g_ExplosionDamageReceivedScale;
			}
		} else if (aprop && aprop->type == PROPTYPE_PLAYER) {
			// Player is attacking
			damage *= g_DamageDealtScale;
			headshotdamagescale = 25;
		} else if (aprop && aprop->type == PROPTYPE_CHR && vprop->type == PROPTYPE_PLAYER) {
			// Chr is attacking player
			damage *= g_DamageReceivedScale * pdmodeGetEnemyDamage();
		}

		if (vprop->type != PROPTYPE_PLAYER) {
			damage /= pdmodeGetEnemyHealth();
		}

		if (vprop->type == PROPTYPE_PLAYER) {
			healthscale = g_Vars.players[propGetPlayerNum(vprop)]->healthscale;
			armourscale = g_Vars.players[propGetPlayerNum(vprop)]->armourscale;
		}
	} else if (g_Vars.coopplayernum >= 0) {
		// Co-op
		if (explosion) {
			if (vprop->type == PROPTYPE_PLAYER) {
				damage *= g_ExplosionDamageReceivedScale;
			}
		} else if (aprop && aprop->type == PROPTYPE_PLAYER && vprop->type != PROPTYPE_PLAYER) {
			damage *= g_DamageDealtScale;
			headshotdamagescale = 25;
		} else if (aprop && aprop->type == PROPTYPE_CHR && vprop->type == PROPTYPE_PLAYER) {
			damage *= g_DamageReceivedScale * pdmodeGetEnemyDamage();
		}

		if (vprop->type != PROPTYPE_PLAYER) {
			damage /= pdmodeGetEnemyHealth();
		}

		if (vprop->type == PROPTYPE_PLAYER) {
			healthscale = g_Vars.players[propGetPlayerNum(vprop)]->healthscale;
			armourscale = g_Vars.players[propGetPlayerNum(vprop)]->armourscale;
		}
	} else if (g_Vars.antiplayernum >= 0) {
		// Anti
		if (explosion) {
			if (vprop == g_Vars.bond->prop) {
				damage *= g_ExplosionDamageReceivedScale;
			}
		} else if (aprop && aprop == g_Vars.bond->prop) {
			damage *= g_DamageDealtScale;
			headshotdamagescale = 25;
		} else if (aprop && aprop != g_Vars.bond->prop && vprop == g_Vars.bond->prop) {
			damage *= g_DamageReceivedScale * pdmodeGetEnemyDamage();
		}

		if (vprop != g_Vars.bond->prop) {
			damage /= pdmodeGetEnemyHealth();
		}

		if (vprop == g_Vars.bond->prop) {
			healthscale = g_Vars.players[propGetPlayerNum(vprop)]->healthscale;
			armourscale = g_Vars.players[propGetPlayerNum(vprop)]->armourscale;
		}

		// Anti shooting other enemies is lethal
		if (aprop && aprop == g_Vars.anti->prop && vprop != g_Vars.bond->prop) {
			damage *= 100;
		}
	} else {
		// Normal multiplayer
		if (vprop->type == PROPTYPE_PLAYER) {
			s32 prevplayernum = g_Vars.currentplayernum;
			setCurrentPlayerNum(propGetPlayerNum(vprop));
			damage *= g_Vars.currentplayerstats->damagescale;
			setCurrentPlayerNum(prevplayernum);
		}
	}

	// Apply rumble
	if (vprop->type == PROPTYPE_PLAYER) {
		s32 prevplayernum = g_Vars.currentplayernum;

#if VERSION >= VERSION_NTSC_1_0
		s32 contpad1;
		s32 contpad2;

		setCurrentPlayerNum(propGetPlayerNum(vprop));

		joyGetContpadNumsForPlayer(g_Vars.currentplayernum, &contpad1, &contpad2);

		if (contpad1 >= 0) {
			pakRumble(contpad1, 0.25f, -1, -1);
		}

		if (contpad2 >= 0) {
			pakRumble(contpad2, 0.25f, -1, -1);
		}
#else
		setCurrentPlayerNum(propGetPlayerNum(vprop));

		pakRumble((s8)g_Vars.currentplayernum, 0.25f, -1, -1);

		if (optionsGetControlMode(g_Vars.currentplayerstats->mpindex) >= CONTROLMODE_21) {
			pakRumble((s8)(PLAYERCOUNT() + g_Vars.currentplayernum), 0.25f, -1, -1);
		}
#endif

		setCurrentPlayerNum(prevplayernum);
	}

	// Find the attacker's player number if possible
	// (includes MP aibots, not applicable for solo chrs)
	if (g_Vars.mplayerisrunning) {
		if (aprop && (aprop->type == PROPTYPE_PLAYER || aprop->type == PROPTYPE_CHR)) {
			aplayernum = mpPlayerGetIndex(aprop->chr);
		}
	} else {
		if (aprop && aprop->type == PROPTYPE_PLAYER) {
			aplayernum = propGetPlayerNum(aprop);
		}
	}

	// If using the shotgun, scale the damage based on distance
	if (aprop && aprop->type == PROPTYPE_CHR && gset->weaponnum == WEAPON_SHOTGUN) {
		f32 xdiff = aprop->pos.x - vprop->pos.x;
		f32 ydiff = aprop->pos.y - vprop->pos.y;
		f32 zdiff = aprop->pos.z - vprop->pos.z;
		f32 sqdist = xdiff * xdiff + ydiff * ydiff + zdiff * zdiff;

		if (sqdist < 200 * 200) {
			damage *= 4.0f + (s32)(random() % 3); // 4, 5 or 6
		} else if (sqdist < 400 * 400) {
			damage *= 3.0f + (s32)(random() % 2); // 3 or 4
		} else if (sqdist < 800 * 800) {
			damage *= 2.0f + (s32)(random() % 2); // 2 or 3
		} else if (sqdist < 1600 * 1600) {
			damage *= 1.0f + (s32)(random() % 2); // 1 or 2
		}
	}

	// damageshield is an argument to this function,
	// but is forced on if using the Farsight.
	if (gset && gset->weaponnum == WEAPON_FARSIGHT) {
		damageshield = true;
		damage *= 10;
	}

	// Handle shield damage
	if (damageshield) {
		shield = chrGetShield(chr);

		if (chr->aibot && chr->aibot->simulant->base.simtype == SIMTYPE_TURTLE) {
			armourscale = 4;
		}

		if (shield > 0) {
			if (g_Vars.normmplayerisrunning) {
#if VERSION >= VERSION_PAL_FINAL
				// Fixing a @bug?
				damage = damage * mpHandicapToDamageScale(g_MpPlayers[g_Vars.currentplayerstats->mpindex].handicap);
#else
				damage /= mpHandicapToDamageScale(g_MpPlayers[g_Vars.currentplayerstats->mpindex].handicap);
#endif
			}

			chr->chrflags |= CHRCFLAG_SHIELDDAMAGED;

			if (prop2 && node && chr->model) {
				func0f034080(chr, node, prop2, model, side, arg11);
			} else {
				shieldhitCreate(chr->prop, chrGetShield(chr), NULL, NULL, NULL, 0, 0);
			}

			if (g_Vars.normmplayerisrunning && (g_MpSetup.options & MPOPTION_ONEHITKILLS)) {
				damage = 0;
				chrSetShield(chr, 0);
			} else if (shield >= damage / armourscale) {
				// Has enough shield to sustain the damage
				shield -= damage / armourscale;
				damage = 0;
				chrSetShield(chr, shield);
			} else {
				// Shield is now gone
				damage = 0;
				chrSetShield(chr, 0);
			}

			showshield = true;
			usedshield = true;
		}
	}

	// Handle hat shots. This is left over from GE, as hats don't exist in PD
	if (damage > 0 && hitpart == HITPART_HAT && chr->weapons_held[2]) {
		s32 type = hatGetType(chr->weapons_held[2]);

		if (type == HATTYPE_CLOTH) {
			// Hat remains on head and damages the chr (eg. Moonraker Elite)
			hitpart = HITPART_HEAD;
		} else if (type != HATTYPE_METAL) {
			// Normal hat
			damage = 0;
			objSetDropped(chr->weapons_held[2], DROPTYPE_HAT);
			chr->hidden |= CHRHFLAG_00000001;
		} else {
			// Metal helmets don't fall off and make a metallic chink noise when shot
			u16 sounds[] = { SFX_HIT_METAL_807B, SFX_HIT_METAL_8079, SFX_HATHIT_807C };
			damage = 0;

			func0f0939f8(NULL, chr->prop, sounds[random() % 3], -1,
					-1, 0, 0, 0, NULL, -1, NULL, -1, -1, -1, -1);
		}
	}

	// Handle incrementing player shot count
	if (aprop && aprop->type == PROPTYPE_PLAYER && !explosion) {
		bool alreadydead = false;
		s32 prevplayernum = g_Vars.currentplayernum;
		setCurrentPlayerNum(propGetPlayerNum(aprop));

		// ACT_DIE is not checked here, so it would appear that shooting
		// a chr as they're dying will increment the shots hit count
		if (chr && chr->actiontype == ACT_DEAD) {
			alreadydead = true;
		}

		if (vprop->type == PROPTYPE_PLAYER && g_Vars.players[propGetPlayerNum(vprop)]->isdead) {
			alreadydead = true;
		}

		if (!alreadydead && hitpart) {
			switch (hitpart) {
			case HITPART_HEAD:
				mpstatsIncrementPlayerShotCount2(gset, SHOTREGION_HEAD);
				break;
			case HITPART_GUN:
				mpstatsIncrementPlayerShotCount2(gset, SHOTREGION_GUN);
				break;
			case HITPART_HAT:
				mpstatsIncrementPlayerShotCount2(gset, SHOTREGION_HAT);
				break;
			case HITPART_PELVIS:
			case HITPART_TORSO:
				mpstatsIncrementPlayerShotCount2(gset, SHOTREGION_BODY);
				break;
			default:
				mpstatsIncrementPlayerShotCount2(gset, SHOTREGION_LIMB);
				break;
			}
		}

		setCurrentPlayerNum(prevplayernum);
	}

	// If the chr is invincible, make them flinch then we're done
	if (chr->chrflags & CHRCFLAG_INVINCIBLE) {
		chrFlinchBody(chr);
		return;
	}

	// If chr is dying or already dead, consider making their head flinch
	// then we're done
	if (chr->actiontype == ACT_DIE || chr->actiontype == ACT_DEAD) {
		if (hitpart == HITPART_HEAD && chr->actiontype == ACT_DIE && race != RACE_SKEDAR && isfar) {
			struct coord pos;
			pos.x = vprop->pos.x - vector->x;
			pos.y = vprop->pos.y - vector->y;
			pos.z = vprop->pos.z - vector->z;
			chrFlinchHead(chr, chrGetAngleToPos(chr, &pos));
		}

		return;
	}

	// At this point the chr is known to be alive before they were shot
	{
		struct prop *weapon;
		struct coord sp9c;
		f32 angle;

		sp9c.x = vprop->pos.x - vector->x;
		sp9c.y = vprop->pos.y - vector->y;
		sp9c.z = vprop->pos.z - vector->z;
		angle = chrGetAngleToPos(chr, &sp9c);

		// Knife in the back to an unalerted chr is lethal
		if (gset->weaponnum == WEAPON_COMBATKNIFE
				&& gset->weaponfunc == FUNC_PRIMARY
				&& angle > 2.0940616130829f
				&& angle < 4.1881237030029f
				&& (chr->alertness < 100 || chr->lastseetarget60 == 0)) {
			damage *= 1000;
		}

		// Punching and pistol whipping is less effective from the front
		if (gsetHasFunctionFlags(gset, FUNCFLAG_BLUNTIMPACT)) {
			if (angle < 1.0470308065414f || angle > 5.2351541519165f) {
				damage *= 0.4f;
			} else if (angle < 2.0940616130829f || angle > 4.1881237030029f) {
				damage *= 0.7f;
			} else if (chr->alertness < 100) {
				onehitko = true;
			}

			if (chrGetHeldProp(chr, HAND_RIGHT) == NULL
					&& chrGetHeldProp(chr, HAND_LEFT) == NULL
					&& (chr->gunprop == NULL || chr->actiontype == ACT_SURRENDER || chr->actiontype == ACT_SURPRISED)) {
				// Chr is unarmed and has no hope of getting their gun
				onehitko = true;
			}

			forceapplydamage = true;
		}

		if (hitpart == HITPART_GENERAL) {
			// Halve the damage because it's doubled for torso below
			hitpart = HITPART_TORSO;
			damage *= 0.5f;
		} else if (hitpart == HITPART_GENERALHALF) {
			// Likewise, quarter it here so it becomes half below
			hitpart = HITPART_TORSO;
			damage *= 0.25f;
		}

		// Hits to a Skedar's tail are 10x more lethal
		if (race == RACE_SKEDAR && hitpart == HITPART_TAIL) {
			damage *= 10;
		}

		// Apply damage multipliers based on which body parts were hit,
		// and flinch head if shot in the head
		if (hitpart == HITPART_HEAD) {
			if (race == RACE_SKEDAR) {
				damage += damage;
				chrFlinchHead(chr, angle);
			} else {
				damage *= 4;

				if (isfar && !usedshield) {
					chrFlinchHead(chr, angle);
					damage *= headshotdamagescale;

					if (gset->weaponnum == WEAPON_COMBATKNIFE && gset->weaponfunc != FUNC_POISON) {
						damage += damage;
					}
				}
			}
		} else if (hitpart == HITPART_TORSO) {
			// Double damage for torso hits
			damage += damage;
		} else if (hitpart == HITPART_GUN) {
			// No damage for gun hits
			damage = 0;
			makedizzy = false;
		} else if (hitpart == HITPART_HAT) {
			// No damage for hat hits
			damage = 0;
			makedizzy = false;
		}

		// Handle situations where the player is the one being shot, then return
		if (vprop->type == PROPTYPE_PLAYER) {
			s32 prevplayernum = g_Vars.currentplayernum;
			setCurrentPlayerNum(propGetPlayerNum(vprop));

			if (g_Vars.normmplayerisrunning) {
				damage /= mpHandicapToDamageScale(g_MpPlayers[g_Vars.currentplayerstats->mpindex].handicap);
			}

			if (g_Vars.currentplayer->isdead == false && !g_PlayerInvincible) {
				f32 boostscale;

				// Handle player losing gun
				if (gsetHasFunctionFlags(gset, FUNCFLAG_DROPWEAPON)) {
					bgunLoseGun(aprop);
				}

				// Handle player dizziness
				if (makedizzy && g_Vars.currentplayer->invincible == false) {
					f32 blurscale = 1;
					struct chrdata *achr = NULL;

					if (aprop) {
						achr = aprop->chr;

						if (achr && achr->bodynum == BODY_MINISKEDAR) {
							blurscale = 4;
						}
					}

					if (!achr
							|| !achr->aibot
							|| !gsetHasFunctionFlags(gset, FUNCFLAG_00400000)
							|| chr->blurdrugamount < PALDOWN(4500)) {
						chr->blurdrugamount += gsetGetBlurAmount(gset) * blurscale;
					}

					chr->blurnumtimesdied = 0;
				}

				// Handle player damage
				if (g_Vars.currentplayer->invincible == false && damage > 0) {
					f32 statsamount = amount = damage * 0.125f;

					if (statsamount > g_Vars.currentplayer->bondhealth) {
						statsamount = g_Vars.currentplayer->bondhealth;
					}

					if (g_Vars.normmplayerisrunning && (g_MpSetup.options & MPOPTION_ONEHITKILLS)) {
						statsamount = g_Vars.currentplayer->bondhealth;
					}

					playerUpdateDamageStats(aprop, vprop, statsamount);
					currentPlayerDisplayHealth();

					if (g_Vars.normmplayerisrunning && (g_MpSetup.options & MPOPTION_ONEHITKILLS)) {
						g_Vars.currentplayer->bondhealth = 0;
					}

					g_Vars.currentplayer->bondhealth -= amount / healthscale;

					chr->lastattacker = (aprop ? aprop->chr : NULL);

					showdamage = true;

					if (g_Vars.currentplayer->training == false
							&& g_Vars.currentplayer->bondhealth <= 0) {
						currentPlayerDieByShooter(aplayernum, false);
						chr->blurnumtimesdied++;
					}

					if (!lvIsPaused() && canchoke) {
						chrChoke(chr, choketype);
					}

					chrFlinchBody(chr);
				}

				// Handle player boost
				if (isclose && gset->weaponnum == WEAPON_REAPER) {
					boostscale = 0.1f;
				} else if (g_Vars.normmplayerisrunning) {
					boostscale = 0.75f;
				} else {
					boostscale = 1;
				}

				g_Vars.currentplayer->bondshotspeed[0] += vector->x * boostscale;
				g_Vars.currentplayer->bondshotspeed[2] += vector->z * boostscale;

				if (showdamage) {
					currentPlayerDisplayDamage();
				}

				if (showshield) {
					currentPlayerDisplayShield();
				}

				if (g_Vars.normmplayerisrunning && aprop && aprop->type == PROPTYPE_PLAYER) {
					currentPlayerCheckIfShotInBack(prevplayernum, vector->x, vector->z);
				}
			}

			setCurrentPlayerNum(prevplayernum);
			return;
		}

		// This check is pointless - a similar check and return exists earlier
		if (chr->actiontype == ACT_DIE || chr->actiontype == ACT_DEAD) {
			return;
		}

		// At this point we know we're dealing with a NPC being shot, and the
		// NPC was alive prior to being shot.

		// Handle aibot/chr losing gun
		if (gsetHasFunctionFlags(gset, FUNCFLAG_DROPWEAPON)
				&& ((chr->flags & CHRFLAG0_CANLOSEGUN) || chr->aibot)) {
			if (chr->aibot) {
				aibotLoseGun(chr, aprop);
			} else {
				weapon = chrGetHeldProp(chr, HAND_RIGHT);

				if (weapon) {
					chr->gunprop = weapon;
					objSetDropped(weapon, DROPTYPE_DEFAULT);
					chr->hidden |= CHRHFLAG_00000001;
				}

				weapon = chrGetHeldProp(chr, HAND_LEFT);

				if (weapon) {
					chr->gunprop = weapon;
					objSetDropped(weapon, DROPTYPE_DEFAULT);
					chr->hidden |= CHRHFLAG_00000001;
				}
			}
		}

		// Handle chr damage
		if (chr->damage < chr->maxdamage
				|| (!g_Vars.normmplayerisrunning && chr->actiontype != ACT_PREARGH)) {
			f32 sp80 = 0;

			chr->numarghs++;

			// Handle chr dizziness and psychosis
			if (makedizzy && race != RACE_DRCAROLL && race != RACE_ROBOT) {
				if (gsetHasFunctionFlags(gset, FUNCFLAG_PSYCHOSIS)) {
					chr->hidden |= CHRHFLAG_PSYCHOSISED;
				} else {
					chr->blurdrugamount += gsetGetBlurAmount(gset);
					chr->blurnumtimesdied = 0;

					if (!chr->aibot && chr->blurdrugamount >= PALDOWN(5000)) {
						onehitko = true;
					}
				}
			}

			// Handle chr boost
			if (chr->aibot) {
				f32 boostscale;

				if (isclose && gset->weaponnum == WEAPON_REAPER) {
					boostscale = 0.1f;
				} else {
					boostscale = 0.75f;
				}

				chr->aibot->shotspeed.x += vector->x * boostscale;
				chr->aibot->shotspeed.z += vector->z * boostscale;
			}

			if (gset->weaponnum == WEAPON_UNARMED) {
				sp80 = 2;
			}

			if (gset->weaponnum == WEAPON_TRANQUILIZER || gset->weaponnum == WEAPON_PSYCHOSISGUN) {
				forceapplydamage = true;
			}

			// Handle one-hit knockouts
			if (onehitko && chr->aibot == NULL && race == RACE_HUMAN) {
				chrKnockOut(chr, angle, hitpart, gset);
				func0f0926bc(chr->prop, 9, 0);

				if (canchoke) {
					chrChoke(chr, choketype);
				}

				if (gset->weaponnum == WEAPON_UNARMED && chr->actiontype != ACT_DRUGGEDKO) {
					return;
				}

				return;
			}

			// Handle applying damage to NPCs
			// Don't enter this branch if there is no damage to give,
			// or we are making a chr dizzy in solo mode (unless force is set)
			if (damage > 0 && (g_Vars.normmplayerisrunning || !makedizzy || forceapplydamage)) {
				f32 amount = damage;

				if (chr->damage + damage > chr->maxdamage) {
					amount = chr->maxdamage - chr->damage;
				}

				amount *= 0.125f;

				playerUpdateDamageStats(aprop, vprop, amount);

				chr->damage += damage;
				chr->lastattacker = (aprop ? aprop->chr : NULL);
				chr->chrflags |= CHRCFLAG_JUST_INJURED;

				if (chr->aibot) {
					if (g_Vars.normmplayerisrunning && (g_MpSetup.options & MPOPTION_ONEHITKILLS)) {
						chr->damage = chr->maxdamage;
					}

					if (canchoke) {
						chrChoke(chr, choketype);
					}

					chrFlinchBody(chr);

					if (chr->damage >= chr->maxdamage) {
						chrDie(chr, aplayernum);
					}
				} else if (explosion) {
					// Chrs die instantly from explosion damage provided they
					// don't have any armour (the chr has armour if their
					// chr->damage is negative). Note that damage has already
					// been applied to the chr above, so a perfectly healthy chr
					// with no armour will already have a damage value > 0 at
					// this point.
					if (chr->damage > 0) {
						chr->damage = chr->maxdamage;

						if (race == RACE_DRCAROLL || race == RACE_EYESPY || race == RACE_ROBOT) {
							chrBeginDeath(chr, vector, angle, hitpart, gset, false, aplayernum);
						} else {
							chrYeetFromPos(chr, explosionpos, explosionforce);
						}

						if (canchoke) {
							chrChoke(chr, choketype);
						}

						if (g_Vars.mplayerisrunning) {
							mpstatsRecordDeath(aplayernum, mpPlayerGetIndex(chr));
						} else if (aprop && aprop->type == PROPTYPE_PLAYER) {
							s32 prevplayernum = g_Vars.currentplayernum;
							setCurrentPlayerNum(propGetPlayerNum(aprop));
							mpstatsRecordPlayerKill();
							setCurrentPlayerNum(prevplayernum);
						}

						if (chr->chrflags & CHRCFLAG_KILLCOUNTABLE) {
							mpstatsIncrementTotalKillCount();
						}

						if (chr->aibot == NULL) {
							chrDropConcealedItems(chr);
						}

						if (chr->aibot == NULL) {
							weapon = chr->weapons_held[HAND_RIGHT];

							if (weapon && (weapon->obj->flags & OBJFLAG_AIUNDROPPABLE) == 0) {
								objSetDropped(weapon, DROPTYPE_DEFAULT);
								chr->hidden |= CHRHFLAG_00000001;
							}

							weapon = chr->weapons_held[HAND_LEFT];

							if (weapon && (weapon->obj->flags & OBJFLAG_AIUNDROPPABLE) == 0) {
								objSetDropped(weapon, DROPTYPE_DEFAULT);
								chr->hidden |= CHRHFLAG_00000001;
							}
						}
					}
				} else {
					// Non-explosion damage to solo mode chr
					if (chr->actiontype != ACT_DRUGGEDKO && canchoke) {
						chrChoke(chr, choketype);
					}

					if (makedizzy && chr->damage >= chr->maxdamage) {
						chr->damage = chr->maxdamage - 0.1f;
						chrKnockOut(chr, angle, hitpart, gset);
					}

					// If chr has armour or the weapon doesn't stun
					if (chr->damage < 0 ||
							(gsetHasFunctionFlags(gset, FUNCFLAG_NOSTUN) && chr->damage < chr->maxdamage)) {
						f32 endframe = -1;

						if (!chrIsAnimPreventingArgh(chr, &endframe)) {
							chrFlinchBody(chr);
						}
					} else if (hitpart != HITPART_HAT) {
						// Cancel current animation and prepare for argh
						f32 endframe = -1;

						if (chrIsAnimPreventingArgh(chr, &endframe)) {
							if (endframe >= 0) {
								modelSetAnimEndFrame(chr->model, endframe);
							}

							chr->actiontype = ACT_PREARGH;
							chr->act_preargh.dir.x = vector->x;
							chr->act_preargh.dir.y = vector->y;
							chr->act_preargh.dir.z = vector->z;
							chr->act_preargh.relshotdir = angle;
							chr->act_preargh.hitpart = hitpart;
							chr->act_preargh.aplayernum = aplayernum;
							chr->act_preargh.gset.weaponnum = gset->weaponnum;
							chr->act_preargh.gset.unk0639 = gset->unk0639;
							chr->act_preargh.gset.unk063a = gset->unk063a;
							chr->act_preargh.gset.weaponfunc = gset->weaponfunc;

							chr->sleep = 0;
						} else {
							chrReactToDamage(chr, vector, angle, hitpart, gset, aplayernum);
						}
					}
				}

				if (sp80 > 0) {
					chr->timeextra = sp80 * 15;
					chr->elapseextra = 0;

					chr->extraspeed.x = prop2->pos.x - aprop->pos.x;
					chr->extraspeed.y = prop2->pos.y - aprop->pos.y;
					chr->extraspeed.z = prop2->pos.z - aprop->pos.z;

					guNormalize(&chr->extraspeed.x, &chr->extraspeed.y, &chr->extraspeed.z);

					chr->extraspeed.x *= sp80;
					chr->extraspeed.y *= sp80;
					chr->extraspeed.z *= sp80;
				}
			}
		}
	}
}

void chrDie(struct chrdata *chr, s32 aplayernum)
{
	if (chr->actiontype != ACT_DIE) {
		chrStopFiring(chr);
		chrUncloak(chr, true);

		chr->actiontype = ACT_DIE;
		chr->act_die.notifychrindex = 0;
		chr->sleep = 0;
		chr->blurnumtimesdied++;
		chr->act_die.thudframe1 = -1;
		chr->act_die.thudframe2 = -1;
		chr->act_die.timeextra = 0;

		chr->ailist = ailistFindById(GAILIST_AI_BOT_DEAD);
		chr->aioffset = 0;

		mpstatsRecordDeath(aplayernum, mpPlayerGetIndex(chr));
		func0f199964(chr, chr->aibot->weaponnum);

#if VERSION >= VERSION_NTSC_1_0
		chr->aibot->unk09c_00 = 0;
		chr->aibot->unk09c_01 = 0;
		chr->aibot->unk04c_04 = 0;
		chr->aibot->unk04c_03 = 0;
		chr->aibot->unk04c_05 = 0;
#endif
	}
}

bool func0f03645c(struct chrdata *chr, struct coord *arg1, s16 *arg2, struct coord *arg3, struct coord *arg4, s32 arg5)
{
	bool result = false;
	f32 ymax;
	f32 ymin;
	f32 width;
	u32 stack[3];
	s16 sp32;
	s16 sp30;
	struct prop *prop = chr->prop;

	chrGetBbox(prop, &width, &ymax, &ymin);
	chrSetPerimEnabled(chr, false);

	if (cd0002d840(arg1, arg2, arg3, &sp30, arg5, 1, ymax - prop->pos.y, ymin - prop->pos.y) != CDRESULT_COLLISION) {
		if (cd0002d6ac(arg3, &sp30, arg4, arg5, 1, ymax - prop->pos.y, ymin - prop->pos.y) != CDRESULT_COLLISION) {
			result = true;
		}
	}

	chrSetPerimEnabled(chr, true);

	return result;
}

bool func0f03654c(struct chrdata *chr, struct coord *pos, s16 *rooms, struct coord *pos2, s16 *rooms2, struct coord *vector, f32 arg6, u32 types)
{
	struct coord tmp;
	f32 a;
	f32 b;
	struct prop *prop;
	bool result = false;
	f32 ymax;
	f32 ymin;
	f32 width;
	struct coord sp5c;
	struct coord sp50;
	s16 sp40[8];
	f32 mult;

	prop = chr->prop;

	chrSetPerimEnabled(chr, false);
	chrGetBbox(prop, &width, &ymax, &ymin);

	if ((rooms2 && cdTestAToB2(pos, rooms, pos2, rooms2, types, 1, ymax - prop->pos.y, ymin - prop->pos.y))
			|| (rooms2 == NULL && cd0002d6ac(pos, rooms, pos2, types, 1, ymax - prop->pos.y, ymin - prop->pos.y))) {
		if (vector == NULL) {
			vector = &tmp;

			tmp.x = pos2->x - pos->x;
			tmp.y = 0;
			tmp.z = pos2->z - pos->z;

			if (tmp.f[0] == 0 && tmp.f[2] == 0) {
				// @bug: Needs to call chrSetPerimEnabled(chr, true)
				// before returning
				return true;
			}

			mult = 1.0f / sqrtf(tmp.f[0] * tmp.f[0] + tmp.f[2] * tmp.f[2]);
			tmp.x *= mult;
			tmp.z *= mult;
		}

		a = vector->x * arg6;
		b = vector->z * arg6;

		sp5c.x = pos->x + b;
		sp5c.y = pos->y;
		sp5c.z = pos->z - a;

		sp50.x = pos2->x + b;
		sp50.y = pos2->y;
		sp50.z = pos2->z - a;

		if (cd0002d840(pos, rooms, &sp5c, sp40, types, 1, ymax - prop->pos.y, ymin - prop->pos.y)
				&& cd0002d6ac(&sp5c, sp40, &sp50, types, 1, ymax - prop->pos.y, ymin - prop->pos.y)) {
			sp5c.x = pos->x - b;
			sp5c.y = pos->y;
			sp5c.z = pos->z + a;

			sp50.x = pos2->x - b;
			sp50.y = pos2->y;
			sp50.z = pos2->z + a;

			if (cd0002d840(pos, rooms, &sp5c, sp40, types, 1, ymax - prop->pos.y, ymin - prop->pos.y)
					&& cd0002d6ac(&sp5c, sp40, &sp50, types, 1, ymax - prop->pos.y, ymin - prop->pos.y)) {
				result = true;
			}
		}
	}

	chrSetPerimEnabled(chr, true);

	return result;
}

bool propchrHasClearLineToPos(struct prop *prop, struct coord *dstpos, struct coord *vector)
{
	return func0f03654c(prop->chr, &prop->pos, prop->rooms, dstpos, NULL, vector, prop->chr->chrwidth * 1.2f, CDTYPE_ALL);
}

bool propchrHasClearLineInVector(struct prop *prop, struct coord *vector, f32 mult)
{
	struct coord dstpos;

	dstpos.x = vector->x * mult + prop->pos.x;
	dstpos.y = prop->pos.y;
	dstpos.z = vector->z * mult + prop->pos.z;

	return propchrHasClearLineToPos(prop, &dstpos, vector);
}

bool func0f036974(struct prop *prop, struct coord *pos)
{
	return func0f03654c(prop->chr, &prop->pos, prop->rooms, pos, NULL, NULL, prop->chr->chrwidth * 1.2f, CDTYPE_ALL);
}

void chrGetSideVectorToTarget(struct chrdata *chr, bool side, struct coord *vector)
{
	struct prop *prop = chr->prop;
	struct prop *target = chrGetTargetProp(chr);

	vector->x = 0;
	vector->y = 0;
	vector->z = 1;

	if (target) {
		f32 x = target->pos.x - prop->pos.x;
		f32 z = target->pos.z - prop->pos.z;
		f32 distance = sqrtf(x * x + z * z);

		if (distance > 0) {
			x = x / distance;
			z = z / distance;

			if (side) {
				vector->x = z;
				vector->y = 0;
				vector->z = -x;
			} else {
				vector->x = -z;
				vector->y = 0;
				vector->z = x;
			}
		}
	}
}

bool chrCanRollInDirection(struct chrdata *chr, bool side, f32 distance)
{
	struct prop *prop = chr->prop;
	struct coord vector;
	struct coord dstpos;

	chrGetSideVectorToTarget(chr, side, &vector);

	dstpos.x = vector.x * distance + prop->pos.x;
	dstpos.y = prop->pos.y;
	dstpos.z = vector.z * distance + prop->pos.z;

	return propchrHasClearLineToPos(prop, &dstpos, &vector);
}

void chrGetSideVector(struct chrdata *chr, bool side, struct coord *vector)
{
	f32 angle = chrGetInverseTheta(chr);

	if (side) {
		vector->x = cosf(angle);
		vector->y = 0;
		vector->z = -sinf(angle);
	} else {
		vector->x = -cosf(angle);
		vector->y = 0;
		vector->z = sinf(angle);
	}
}

bool chrCanJumpInDirection(struct chrdata *chr, bool side, f32 distance)
{
	struct prop *prop = chr->prop;
	struct coord vector;
	struct coord dstpos;

	chrGetSideVector(chr, side, &vector);

	dstpos.x = vector.x * distance + prop->pos.x;
	dstpos.y = prop->pos.y;
	dstpos.z = vector.z * distance + prop->pos.z;

	return propchrHasClearLineToPos(prop, &dstpos, &vector);
}

GLOBAL_ASM(
glabel func0f036c08
/*  f036c08:	27bdff58 */ 	addiu	$sp,$sp,-168
/*  f036c0c:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f036c10:	afb30028 */ 	sw	$s3,0x28($sp)
/*  f036c14:	afb20024 */ 	sw	$s2,0x24($sp)
/*  f036c18:	afb10020 */ 	sw	$s1,0x20($sp)
/*  f036c1c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f036c20:	afa500ac */ 	sw	$a1,0xac($sp)
/*  f036c24:	afa600b0 */ 	sw	$a2,0xb0($sp)
/*  f036c28:	8c88001c */ 	lw	$t0,0x1c($a0)
/*  f036c2c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f036c30:	afae0060 */ 	sw	$t6,0x60($sp)
/*  f036c34:	8c8f0014 */ 	lw	$t7,0x14($a0)
/*  f036c38:	3c13800a */ 	lui	$s3,%hi(g_Vars)
/*  f036c3c:	26739fc0 */ 	addiu	$s3,$s3,%lo(g_Vars)
/*  f036c40:	000fc080 */ 	sll	$t8,$t7,0x2
/*  f036c44:	07010018 */ 	bgez	$t8,.L0f036ca8
/*  f036c48:	25040008 */ 	addiu	$a0,$t0,0x8
/*  f036c4c:	8e630284 */ 	lw	$v1,0x284($s3)
/*  f036c50:	3c098007 */ 	lui	$t1,%hi(g_InCutscene)
/*  f036c54:	8c7900d8 */ 	lw	$t9,0xd8($v1)
/*  f036c58:	57200049 */ 	bnezl	$t9,.L0f036d80
/*  f036c5c:	8fab0060 */ 	lw	$t3,0x60($sp)
/*  f036c60:	8d290764 */ 	lw	$t1,%lo(g_InCutscene)($t1)
/*  f036c64:	55200046 */ 	bnezl	$t1,.L0f036d80
/*  f036c68:	8fab0060 */ 	lw	$t3,0x60($sp)
/*  f036c6c:	8c620480 */ 	lw	$v0,0x480($v1)
/*  f036c70:	50400007 */ 	beqzl	$v0,.L0f036c90
/*  f036c74:	8c6c1c54 */ 	lw	$t4,0x1c54($v1)
/*  f036c78:	50400041 */ 	beqzl	$v0,.L0f036d80
/*  f036c7c:	8fab0060 */ 	lw	$t3,0x60($sp)
/*  f036c80:	804a0037 */ 	lb	$t2,0x37($v0)
/*  f036c84:	5540003e */ 	bnezl	$t2,.L0f036d80
/*  f036c88:	8fab0060 */ 	lw	$t3,0x60($sp)
/*  f036c8c:	8c6c1c54 */ 	lw	$t4,0x1c54($v1)
.L0f036c90:
/*  f036c90:	8c6b00c4 */ 	lw	$t3,0xc4($v1)
/*  f036c94:	01806827 */ 	nor	$t5,$t4,$zero
/*  f036c98:	016d7024 */ 	and	$t6,$t3,$t5
/*  f036c9c:	31cf0008 */ 	andi	$t7,$t6,0x8
/*  f036ca0:	51e00037 */ 	beqzl	$t7,.L0f036d80
/*  f036ca4:	8fab0060 */ 	lw	$t3,0x60($sp)
.L0f036ca8:
/*  f036ca8:	3c13800a */ 	lui	$s3,%hi(g_Vars)
/*  f036cac:	27b8007c */ 	addiu	$t8,$sp,0x7c
/*  f036cb0:	24190014 */ 	addiu	$t9,$zero,0x14
/*  f036cb4:	26739fc0 */ 	addiu	$s3,$s3,%lo(g_Vars)
/*  f036cb8:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f036cbc:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f036cc0:	25050028 */ 	addiu	$a1,$t0,0x28
/*  f036cc4:	8fa600ac */ 	lw	$a2,0xac($sp)
/*  f036cc8:	0fc1977f */ 	jal	func0f065dfc
/*  f036ccc:	27a70064 */ 	addiu	$a3,$sp,0x64
/*  f036cd0:	8e690314 */ 	lw	$t1,0x314($s3)
/*  f036cd4:	87aa007c */ 	lh	$t2,0x7c($sp)
/*  f036cd8:	87af007c */ 	lh	$t7,0x7c($sp)
/*  f036cdc:	11200013 */ 	beqz	$t1,.L0f036d2c
/*  f036ce0:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f036ce4:	108a0025 */ 	beq	$a0,$t2,.L0f036d7c
/*  f036ce8:	27a2007c */ 	addiu	$v0,$sp,0x7c
/*  f036cec:	3c05800a */ 	lui	$a1,%hi(g_MpRoomVisibility)
/*  f036cf0:	8ca5492c */ 	lw	$a1,%lo(g_MpRoomVisibility)($a1)
/*  f036cf4:	84430000 */ 	lh	$v1,0x0($v0)
/*  f036cf8:	00655821 */ 	addu	$t3,$v1,$a1
.L0f036cfc:
/*  f036cfc:	916d0000 */ 	lbu	$t5,0x0($t3)
/*  f036d00:	31ae000f */ 	andi	$t6,$t5,0xf
/*  f036d04:	51c00004 */ 	beqzl	$t6,.L0f036d18
/*  f036d08:	84430002 */ 	lh	$v1,0x2($v0)
/*  f036d0c:	1000001b */ 	b	.L0f036d7c
/*  f036d10:	afa00060 */ 	sw	$zero,0x60($sp)
/*  f036d14:	84430002 */ 	lh	$v1,0x2($v0)
.L0f036d18:
/*  f036d18:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f036d1c:	5483fff7 */ 	bnel	$a0,$v1,.L0f036cfc
/*  f036d20:	00655821 */ 	addu	$t3,$v1,$a1
/*  f036d24:	10000016 */ 	b	.L0f036d80
/*  f036d28:	8fab0060 */ 	lw	$t3,0x60($sp)
.L0f036d2c:
/*  f036d2c:	2404ffff */ 	addiu	$a0,$zero,-1
/*  f036d30:	108f0012 */ 	beq	$a0,$t7,.L0f036d7c
/*  f036d34:	27a2007c */ 	addiu	$v0,$sp,0x7c
/*  f036d38:	3c05800a */ 	lui	$a1,%hi(g_Rooms)
/*  f036d3c:	8ca54928 */ 	lw	$a1,%lo(g_Rooms)($a1)
/*  f036d40:	84430000 */ 	lh	$v1,0x0($v0)
/*  f036d44:	2406008c */ 	addiu	$a2,$zero,0x8c
.L0f036d48:
/*  f036d48:	00660019 */ 	multu	$v1,$a2
/*  f036d4c:	0000c812 */ 	mflo	$t9
/*  f036d50:	00b94821 */ 	addu	$t1,$a1,$t9
/*  f036d54:	952a0000 */ 	lhu	$t2,0x0($t1)
/*  f036d58:	314c0004 */ 	andi	$t4,$t2,0x4
/*  f036d5c:	51800004 */ 	beqzl	$t4,.L0f036d70
/*  f036d60:	84430002 */ 	lh	$v1,0x2($v0)
/*  f036d64:	10000005 */ 	b	.L0f036d7c
/*  f036d68:	afa00060 */ 	sw	$zero,0x60($sp)
/*  f036d6c:	84430002 */ 	lh	$v1,0x2($v0)
.L0f036d70:
/*  f036d70:	24420002 */ 	addiu	$v0,$v0,0x2
/*  f036d74:	1483fff4 */ 	bne	$a0,$v1,.L0f036d48
/*  f036d78:	00000000 */ 	nop
.L0f036d7c:
/*  f036d7c:	8fab0060 */ 	lw	$t3,0x60($sp)
.L0f036d80:
/*  f036d80:	51600051 */ 	beqzl	$t3,.L0f036ec8
/*  f036d84:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f036d88:	8e6d006c */ 	lw	$t5,0x6c($s3)
/*  f036d8c:	00009025 */ 	or	$s2,$zero,$zero
/*  f036d90:	00002825 */ 	or	$a1,$zero,$zero
/*  f036d94:	11a00003 */ 	beqz	$t5,.L0f036da4
/*  f036d98:	00002025 */ 	or	$a0,$zero,$zero
/*  f036d9c:	10000001 */ 	b	.L0f036da4
/*  f036da0:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f036da4:
/*  f036da4:	8e6e0068 */ 	lw	$t6,0x68($s3)
/*  f036da8:	00001825 */ 	or	$v1,$zero,$zero
/*  f036dac:	00001025 */ 	or	$v0,$zero,$zero
/*  f036db0:	11c00003 */ 	beqz	$t6,.L0f036dc0
/*  f036db4:	00126080 */ 	sll	$t4,$s2,0x2
/*  f036db8:	10000001 */ 	b	.L0f036dc0
/*  f036dbc:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f036dc0:
/*  f036dc0:	8e6f0064 */ 	lw	$t7,0x64($s3)
/*  f036dc4:	026c8021 */ 	addu	$s0,$s3,$t4
/*  f036dc8:	27b10050 */ 	addiu	$s1,$sp,0x50
/*  f036dcc:	11e00003 */ 	beqz	$t7,.L0f036ddc
/*  f036dd0:	00000000 */ 	nop
/*  f036dd4:	10000001 */ 	b	.L0f036ddc
/*  f036dd8:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f036ddc:
/*  f036ddc:	8e780070 */ 	lw	$t8,0x70($s3)
/*  f036de0:	13000003 */ 	beqz	$t8,.L0f036df0
/*  f036de4:	00000000 */ 	nop
/*  f036de8:	10000001 */ 	b	.L0f036df0
/*  f036dec:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f036df0:
/*  f036df0:	0043c821 */ 	addu	$t9,$v0,$v1
/*  f036df4:	03244821 */ 	addu	$t1,$t9,$a0
/*  f036df8:	01255021 */ 	addu	$t2,$t1,$a1
/*  f036dfc:	59400032 */ 	blezl	$t2,.L0f036ec8
/*  f036e00:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f036e04:	8e0b0064 */ 	lw	$t3,0x64($s0)
.L0f036e08:
/*  f036e08:	8fa400ac */ 	lw	$a0,0xac($sp)
/*  f036e0c:	8fa600b0 */ 	lw	$a2,0xb0($sp)
/*  f036e10:	8d6500bc */ 	lw	$a1,0xbc($t3)
/*  f036e14:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f036e18:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f036e1c:	02203825 */ 	or	$a3,$s1,$zero
/*  f036e20:	0c006052 */ 	jal	func00018148
/*  f036e24:	24a50008 */ 	addiu	$a1,$a1,8
/*  f036e28:	8e0d0064 */ 	lw	$t5,0x64($s0)
/*  f036e2c:	02202825 */ 	or	$a1,$s1,$zero
/*  f036e30:	8da400bc */ 	lw	$a0,0xbc($t5)
/*  f036e34:	0fc19620 */ 	jal	arrayIntersects
/*  f036e38:	24840028 */ 	addiu	$a0,$a0,0x28
/*  f036e3c:	10400003 */ 	beqz	$v0,.L0f036e4c
/*  f036e40:	00002825 */ 	or	$a1,$zero,$zero
/*  f036e44:	1000001f */ 	b	.L0f036ec4
/*  f036e48:	afa00060 */ 	sw	$zero,0x60($sp)
.L0f036e4c:
/*  f036e4c:	8e6e006c */ 	lw	$t6,0x6c($s3)
/*  f036e50:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f036e54:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f036e58:	11c00003 */ 	beqz	$t6,.L0f036e68
/*  f036e5c:	00002025 */ 	or	$a0,$zero,$zero
/*  f036e60:	10000001 */ 	b	.L0f036e68
/*  f036e64:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f036e68:
/*  f036e68:	8e6f0068 */ 	lw	$t7,0x68($s3)
/*  f036e6c:	00001825 */ 	or	$v1,$zero,$zero
/*  f036e70:	00001025 */ 	or	$v0,$zero,$zero
/*  f036e74:	11e00003 */ 	beqz	$t7,.L0f036e84
/*  f036e78:	00000000 */ 	nop
/*  f036e7c:	10000001 */ 	b	.L0f036e84
/*  f036e80:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f036e84:
/*  f036e84:	8e780064 */ 	lw	$t8,0x64($s3)
/*  f036e88:	13000003 */ 	beqz	$t8,.L0f036e98
/*  f036e8c:	00000000 */ 	nop
/*  f036e90:	10000001 */ 	b	.L0f036e98
/*  f036e94:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f036e98:
/*  f036e98:	8e790070 */ 	lw	$t9,0x70($s3)
/*  f036e9c:	13200003 */ 	beqz	$t9,.L0f036eac
/*  f036ea0:	00000000 */ 	nop
/*  f036ea4:	10000001 */ 	b	.L0f036eac
/*  f036ea8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f036eac:
/*  f036eac:	00434821 */ 	addu	$t1,$v0,$v1
/*  f036eb0:	01245021 */ 	addu	$t2,$t1,$a0
/*  f036eb4:	01456021 */ 	addu	$t4,$t2,$a1
/*  f036eb8:	024c082a */ 	slt	$at,$s2,$t4
/*  f036ebc:	5420ffd2 */ 	bnezl	$at,.L0f036e08
/*  f036ec0:	8e0b0064 */ 	lw	$t3,0x64($s0)
.L0f036ec4:
/*  f036ec4:	8fbf002c */ 	lw	$ra,0x2c($sp)
.L0f036ec8:
/*  f036ec8:	8fa20060 */ 	lw	$v0,0x60($sp)
/*  f036ecc:	8fb0001c */ 	lw	$s0,0x1c($sp)
/*  f036ed0:	8fb10020 */ 	lw	$s1,0x20($sp)
/*  f036ed4:	8fb20024 */ 	lw	$s2,0x24($sp)
/*  f036ed8:	8fb30028 */ 	lw	$s3,0x28($sp)
/*  f036edc:	03e00008 */ 	jr	$ra
/*  f036ee0:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
);

void chrGoPosInitMagic(struct chrdata *chr, struct waydata *waydata, struct coord *padpos, struct coord *chrpos)
{
	f32 xdiff1 = padpos->x - chr->prop->pos.x;
	f32 zdiff1 = padpos->z - chr->prop->pos.z;

	f32 angle = atan2f(xdiff1, zdiff1);

	f32 xdiff2 = padpos->x - chrpos->x;
	f32 zdiff2 = padpos->z - chrpos->z;

	waydata->mode = WAYMODE_MAGIC;

	waydata->magictotal = sqrtf(xdiff1 * xdiff1 + zdiff1 * zdiff1);
	waydata->magicdone = waydata->magictotal - sqrtf(xdiff2 * xdiff2 + zdiff2 * zdiff2);

	chrSetLookAngle(chr, angle);
}

void chrGoPosGetCurWaypointInfoWithFlags(struct chrdata *chr, struct coord *pos, s16 *rooms, u32 *flags)
{
	struct waypoint *waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex];
	struct pad pad;

	if (waypoint) {
		padUnpack(waypoint->padnum, PADFIELD_POS | PADFIELD_ROOM | PADFIELD_FLAGS, &pad);

		pos->x = pad.pos.x;
		pos->y = pad.pos.y;
		pos->z = pad.pos.z;

		rooms[0] = pad.room;
		rooms[1] = -1;

		if (flags) {
			*flags = pad.flags;
		}
	} else {
		pos->x = chr->act_gopos.endpos.x;
		pos->y = chr->act_gopos.endpos.y;
		pos->z = chr->act_gopos.endpos.z;

		rooms[0] = chr->act_gopos.endrooms[0];
		rooms[1] = -1;

		if (flags) {
			*flags = 0;
		}
	}
}

void chrGoPosGetCurWaypointInfo(struct chrdata *chr, struct coord *pos, s16 *rooms)
{
	chrGoPosGetCurWaypointInfoWithFlags(chr, pos, rooms, NULL);
}

f32 func0f0370a8(struct chrdata *chr)
{
	f32 result;

	if (chr->aibot) {
		result = aibotCalculateMaxSpeed(chr);
	} else {
		s16 animnum = modelGetAnimNum(chr->model);
		result = func0f02dff0(animnum) * (chr->model->scale * 9.999999f);
	}

	return result;
}

s32 chrGoPosCalculateBaseTtl(struct chrdata *chr)
{
	f32 xdiff;
	f32 zdiff;
	u32 stack;
	struct coord pos;
	s16 rooms[8];
	f32 speed;

	chrGoPosGetCurWaypointInfo(chr, &pos, rooms);

	xdiff = pos.x - chr->prop->pos.x;
	zdiff = pos.z - chr->prop->pos.z;

	if (xdiff < 0) {
		xdiff = -xdiff;
	}

	if (zdiff < 0) {
		zdiff = -zdiff;
	}

	speed = func0f0370a8(chr);

	if (chr->aibot == NULL) {
		speed *= modelGetAbsAnimSpeed(chr->model);
	}

	if (speed < 0.001f) {
		speed = 0.001f;
	}

	return (xdiff + zdiff) / speed;
}

void chrGoPosClearRestartTtl(struct chrdata *chr)
{
	chr->act_gopos.restartttl = 0;
}

void chrGoPosConsiderRestart(struct chrdata *chr)
{
	if (chr->act_gopos.waydata.mode != WAYMODE_MAGIC
			&& chr->liftaction != LIFTACTION_WAITINGONLIFT
			&& chr->liftaction != LIFTACTION_WAITINGFORLIFT) {
		if (chr->act_gopos.restartttl == 0) {
#if VERSION >= VERSION_PAL_FINAL
			s32 value = (chrGoPosCalculateBaseTtl(chr) * 100 + 15000) / 60;
#else
			s32 value = chrGoPosCalculateBaseTtl(chr) * 2 + 300;
#endif

			if (value > 0xffff) {
				value = 0xffff;
			}

			chr->act_gopos.restartttl = value;
		} else if (chr->act_gopos.restartttl <= (u16)g_Vars.lvupdate240_60) {
			if (chr->aibot) {
				func0f197544(chr);
			} else {
				chrGoToPos(chr, &chr->act_gopos.endpos, chr->act_gopos.endrooms, chr->act_gopos.flags);
			}
		} else {
			chr->act_gopos.restartttl -= (u16)g_Vars.lvupdate240_60;
		}
	}
}

void chrGoPosInitExpensive(struct chrdata *chr)
{
	struct coord pos;
	s16 rooms[8];

	chrGoPosGetCurWaypointInfo(chr, &pos, rooms);

	chr->act_gopos.waydata.mode = WAYMODE_EXPENSIVE;
	chr->act_gopos.waydata.iter = 0;
	chr->act_gopos.waydata.gotaimpos = false;
	chr->act_gopos.waydata.aimpos.x = pos.x;
	chr->act_gopos.waydata.aimpos.y = pos.y;
	chr->act_gopos.waydata.aimpos.z = pos.z;

	chrGoPosClearRestartTtl(chr);
}

/**
 * Advance the chr's current waypoint index to the next one in the route.
 *
 * The waypoints array allows 6 waypoints and it's important that they have a
 * couple loaded in front of their current one. So if the index is moving too
 * far into the array, new pathfinding will be done and the array and index will
 * be reset.
 */
void chrGoPosAdvanceWaypoint(struct chrdata *chr)
{
	if (chr->act_gopos.curindex < 3) {
		chr->act_gopos.curindex++;
	} else {
		struct waypoint *from = chr->act_gopos.waypoints[chr->act_gopos.curindex];
		u32 hash;
		chr->act_gopos.curindex = 1;

		hash = (g_Vars.lvframe60 >> 9) * 0x80 + chr->chrnum * 8;

		waypointSetHashThing(hash, hash);
		waypointFindRoute(from, chr->act_gopos.target, chr->act_gopos.waypoints, MAX_CHRWAYPOINTS);
		waypointSetHashThing(0, 0);
	}

	chrGoPosInitExpensive(chr);
}

/**
 * Determines which step index the chr will be at given their current index, the
 * number of steps to take and in which direction (forward or back).
 *
 * Returns the step index and populates *forward with true or false depending on
 * whether the chr will be traversing the path in the forward direction at that
 * point.
 */
s32 chrPatrolCalculateStep(struct chrdata *chr, bool *forward, s32 numsteps)
{
	s32 nextstep = chr->act_patrol.nextstep;
	bool isforward = *forward;

	if (numsteps < 0) {
		isforward = !isforward;
		numsteps = -numsteps;
	}

	while (numsteps > 0) {
		numsteps--;

		if (isforward) {
			nextstep++;

			if (chr->act_patrol.path->pads[nextstep] < 0) {
				// Reached the end of the list
				if (chr->act_patrol.path->flags & PATHFLAG_CIRCULAR) {
					nextstep = 0;
				} else {
					isforward = false;
					nextstep -= 2;

					if (nextstep < 0) {
						nextstep = 0;
					}
				}
			}
		} else {
			nextstep--;

			if (nextstep < 0) {
				// Reached the start of the list
				if (chr->act_patrol.path->flags & PATHFLAG_CIRCULAR) {
					nextstep = chr->act_patrol.path->len - 1;
				} else {
					isforward = true;
					nextstep = 1;

					if (chr->act_patrol.path->len - 1 <= 0) {
						nextstep = chr->act_patrol.path->len - 1;
					}
				}
			}
		}
	}

	*forward = isforward;

	return nextstep;
}

/**
 * Determines which pad number the chr will be at given their current index and
 * the number of steps to take.
 */
s16 chrPatrolCalculatePadNum(struct chrdata *chr, s32 numsteps)
{
	s32 *padnumptr;
	bool forward = chr->act_patrol.forward;
	s32 step = chrPatrolCalculateStep(chr, &forward, numsteps);
	padnumptr = &chr->act_patrol.path->pads[step];

	return *padnumptr;
}

void chrPatrolGetCurWaypointInfoWithFlags(struct chrdata *chr, struct coord *pos, s16 *rooms, u32 *flags)
{
	s32 padnum = chrPatrolCalculatePadNum(chr, 0);
	struct pad pad;

	padUnpack(padnum, PADFIELD_POS | PADFIELD_ROOM | PADFIELD_FLAGS, &pad);

	pos->x = pad.pos.x;
	pos->y = pad.pos.y;
	pos->z = pad.pos.z;

	rooms[0] = pad.room;
	rooms[1] = -1;

	if (flags) {
		*flags = pad.flags;
	}
}

void chrPatrolGetCurWaypointInfo(struct chrdata *chr, struct coord *pos, s16 *rooms)
{
	chrPatrolGetCurWaypointInfoWithFlags(chr, pos, rooms, NULL);
}

void func0f037580(struct chrdata *chr)
{
	s16 rooms[8];

	chr->act_patrol.waydata.mode = WAYMODE_EXPENSIVE;
	chr->act_patrol.waydata.iter = 0;
	chr->act_patrol.waydata.gotaimpos = false;

	chrPatrolGetCurWaypointInfo(chr, &chr->act_patrol.waydata.aimpos, rooms);
}

void func0f0375b0(struct chrdata *chr)
{
	s32 nextstep = chrPatrolCalculateStep(chr, &chr->act_patrol.forward, 1);

	chr->act_patrol.nextstep = nextstep;
	chr->patrolnextstep = nextstep;

	func0f037580(chr);
}

void chrGoPosTickMagic(struct chrdata *chr, struct waydata *waydata, f32 speed, struct coord *arg3, s16 *rooms)
{
	s16 sp118[8];
	f32 ymax;
	f32 ymin;
	f32 width;
	f32 ground;
	u16 floorcol;
	u8 floortype;
	s16 floorroom;
	struct coord spf4;
	struct prop *prop = chr->prop;
	union modelrwdata *rwdata;
	struct waypoint *waypoint;
	struct coord spdc;
	s16 spcc[8];
	u32 stack[4];
	struct pad pad;
	struct coord sp5c;
	s16 sp4c[8];

	chr->invalidmove = 0;
	chr->lastmoveok60 = g_Vars.lvframe60;

	waydata->magicdone += speed * modelGetAbsAnimSpeed(chr->model) * g_Vars.lvupdate240freal;

	if (waydata->magicdone >= waydata->magictotal) {
		// Reached end of segment
		chrSetPerimEnabled(chr, false);
		roomsCopy(rooms, sp118);
		chr0f021fa8(chr, arg3, sp118);

		ground = cdFindGroundY(arg3, chr->chrwidth, sp118, &floorcol, &floortype, 0, &floorroom, NULL, NULL);

		spf4.x = arg3->x;
		spf4.y = prop->pos.y - chr->ground + ground;
		spf4.z = arg3->z;

		roomsCopy(rooms, sp118);
		chr0f021fa8(chr, &spf4, sp118);
		chrGetBbox(chr->prop, &width, &ymax, &ymin);

		if (cdTestVolume(&spf4, chr->chrwidth, sp118, CDTYPE_ALL, 1, ymax - prop->pos.y, ymin - prop->pos.y) != CDRESULT_COLLISION) {
			// Reached end of segment with no collision
			prop->pos.x = spf4.x;
			prop->pos.y = spf4.y;
			prop->pos.z = spf4.z;

			chr->ground = ground;
			chr->manground = ground;
			chr->sumground = ground * (PAL ? 8.4175090789795f : 9.999998f);

			chr->floorcol = floorcol;
			chr->floortype = floortype;
			chr->floorroom = floorroom;

			propDeregisterRooms(prop);
			roomsCopy(sp118, prop->rooms);
			propRegisterRooms(prop);

			modelSetRootPosition(chr->model, &prop->pos);

			rwdata = modelGetNodeRwData(chr->model, chr->model->filedata->rootnode);
			rwdata->chrinfo.ground = ground;

			chr->chrflags |= CHRCFLAG_00000001;

			if (chr->actiontype == ACT_PATROL) {
				func0f0375b0(chr);
				chrPatrolGetCurWaypointInfo(chr, &spdc, spcc);
				chrGoPosInitMagic(chr, waydata, &spdc, &prop->pos);
			} else if (chr->actiontype == ACT_GOPOS) {
				if (chr->act_gopos.waypoints[chr->act_gopos.curindex] == NULL) {
					// Reached the end of the route
					if (chr->act_gopos.flags & GOPOSFLAG_FORPATHSTART) {
						chrTryStartPatrol(chr);
					} else {
						if (chr->act_gopos.curindex >= 2) {
							waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex - 2];
							padUnpack(waypoint->padnum, PADFIELD_POS, &pad);
							chrSetLookAngle(chr, atan2f(prop->pos.x - pad.pos.x, prop->pos.z - pad.pos.z));
						}

						if (CHRRACE(chr) == RACE_HUMAN || CHRRACE(chr) == RACE_SKEDAR) {
							chrStop(chr);
						}
					}
				} else {
					// Advance to next segment, still using magic
					chrGoPosAdvanceWaypoint(chr);
					chrGoPosGetCurWaypointInfo(chr, &sp5c, sp4c);
					chrGoPosInitMagic(chr, waydata, &sp5c, &prop->pos);
				}
			}
		} else {
			// Collision
			waydata->magicdone = waydata->magictotal;

			if (chr->actiontype == ACT_PATROL) {
				chr->act_patrol.waydata.lastvisible60 = g_Vars.lvframe60;
				func0f037580(chr);
			} else {
				chr->act_gopos.waydata.lastvisible60 = g_Vars.lvframe60;
				chrGoPosInitExpensive(chr);
			}
		}

		chrSetPerimEnabled(chr, true);
	}
}

/**
 * Calculate the chr's position when using the magic method of navigating.
 *
 * The magic method is used when the chr is off-screen. It measures the distance
 * between two consecutive pads in the route and simply increments a distance
 * value along that segment on each tick, ignoring collisions. Meanwhile, the
 * chr's prop->pos is left as the original location where this segment started.
 *
 * The calculation is finding the fraction of the distance travelled in this
 * segment, then finding the position between the starting pos and the pad's
 * pos.
 *
 * The pos variable is used for both loading the next pad's position and for
 * returning the new position, which means there's less stack usage.
 */
void chrCalculatePosition(struct chrdata *chr, struct coord *pos)
{
	s16 rooms[8];
	f32 frac;

	if (chr->actiontype == ACT_PATROL && chr->act_patrol.waydata.mode == WAYMODE_MAGIC) {
		chrPatrolGetCurWaypointInfo(chr, pos, rooms);

		if (!(chr->act_patrol.waydata.magicdone >= chr->act_patrol.waydata.magictotal)
				&& chr->act_patrol.waydata.magictotal > 0) {
			frac = chr->act_patrol.waydata.magicdone / chr->act_patrol.waydata.magictotal;
			pos->x = (pos->x - chr->prop->pos.x) * frac + chr->prop->pos.x;
			pos->y = (pos->y - chr->prop->pos.y) * frac + chr->prop->pos.y;
			pos->z = (pos->z - chr->prop->pos.z) * frac + chr->prop->pos.z;
		}
	} else if (chr->actiontype == ACT_GOPOS && chr->act_gopos.waydata.mode == WAYMODE_MAGIC) {
		chrGoPosGetCurWaypointInfo(chr, pos, rooms);

		if (!(chr->act_gopos.waydata.magicdone >= chr->act_gopos.waydata.magictotal)
				&& chr->act_gopos.waydata.magictotal > 0) {
			frac = chr->act_gopos.waydata.magicdone / chr->act_gopos.waydata.magictotal;
			pos->x = (pos->x - chr->prop->pos.x) * frac + chr->prop->pos.x;
			pos->y = (pos->y - chr->prop->pos.y) * frac + chr->prop->pos.y;
			pos->z = (pos->z - chr->prop->pos.z) * frac + chr->prop->pos.z;
		}
	} else {
		pos->x = chr->prop->pos.x;
		pos->y = chr->prop->pos.y;
		pos->z = chr->prop->pos.z;
	}
}

void chrGoPosChooseAnimation(struct chrdata *chr)
{
	s32 gospeed = chr->act_gopos.flags & 3;
	s32 male = g_HeadsAndBodies[chr->bodynum].ismale;
	struct prop *gun1 = chrGetHeldProp(chr, 1);
	struct prop *gun2 = chrGetHeldProp(chr, 0);
	s32 flip = false;
	s32 heavy;
	s32 race = CHRRACE(chr);
	s32 anim = -1;
	u32 stack;
	f32 speed = 0.5;
	f32 sp60 = 16;
	f32 animspeed = -1;
	f32 startframe = 16;

	if (chr->actiontype == ACT_GOPOS) {
		chr->act_gopos.flags &= ~GOPOSFLAG_20;
	}

	if (race == RACE_EYESPY || chr->aibot) {
		return;
	}

	if (race == RACE_HUMAN || race == RACE_SKEDAR) {
		if ((gun1 && gun2) || (!gun1 && !gun2)) {
			heavy = false;
			flip = random() % 2;
		} else {
			if (weaponIsOneHanded(gun1) || weaponIsOneHanded(gun2)) {
				heavy = false;
				flip = (bool)gun1 != false;
			} else {
				heavy = true;
				flip = (bool)gun1 != false;
			}
		}

		if (race == RACE_SKEDAR) {
			if (gospeed == SPEED_RUN) {
				anim = ANIM_SKEDAR_RUNNING;
			} else if (gospeed == SPEED_JOG) {
				anim = ANIM_0393;
			} else if (gospeed == SPEED_WALK) {
				anim = ANIM_0392;
			}
		} else {
			if (heavy) {
				if (gospeed == SPEED_RUN) {
					// Human, heavy weapon, running
					if (chr->hitpart == HITPART_LFOOT
							|| chr->hitpart == HITPART_LSHIN
							|| chr->hitpart == HITPART_LTHIGH
							|| chr->hitpart == HITPART_RFOOT
							|| chr->hitpart == HITPART_RSHIN
							|| chr->hitpart == HITPART_RTHIGH) {
						anim = ANIM_020A;
						speed = 0.4;
					} else if (chr->hitpart == HITPART_LHAND
							|| chr->hitpart == HITPART_LFOREARM
							|| chr->hitpart == HITPART_LBICEP
							|| chr->hitpart == HITPART_RHAND
							|| chr->hitpart == HITPART_RFOREARM
							|| chr->hitpart == HITPART_RBICEP) {
						anim = ANIM_020D;
						speed = 0.4;
					} else {
						anim = ANIM_0029;
						speed = 0.25;
					}

					if (chr->chrflags & CHRCFLAG_RUNFASTER) {
						animspeed = 0.65;
						startframe = 48;
					} else {
						animspeed = 0.5;
						startframe = 48;
					}
				} else if (gospeed == SPEED_JOG) {
					// Human, heavy weapon, jogging
					if (chr->hitpart == HITPART_LFOOT
							|| chr->hitpart == HITPART_LSHIN
							|| chr->hitpart == HITPART_LTHIGH
							|| chr->hitpart == HITPART_RFOOT
							|| chr->hitpart == HITPART_RSHIN
							|| chr->hitpart == HITPART_RTHIGH) {
						anim = ANIM_01F9;
					} else if (chr->hitpart == HITPART_LHAND
							|| chr->hitpart == HITPART_LFOREARM
							|| chr->hitpart == HITPART_LBICEP
							|| chr->hitpart == HITPART_RHAND
							|| chr->hitpart == HITPART_RFOREARM
							|| chr->hitpart == HITPART_RBICEP) {
						anim = ANIM_01F8;
					} else {
						anim = ANIM_RUNNING_TWOHANDGUN;
					}
				} else {
					// Human, heavy weapon, walking
					if (chr->hitpart == HITPART_LFOOT
							|| chr->hitpart == HITPART_LSHIN
							|| chr->hitpart == HITPART_LTHIGH
							|| chr->hitpart == HITPART_RFOOT
							|| chr->hitpart == HITPART_RSHIN
							|| chr->hitpart == HITPART_RTHIGH) {
						anim = ANIM_01F9;
					} else if (chr->hitpart == HITPART_LHAND
							|| chr->hitpart == HITPART_LFOREARM
							|| chr->hitpart == HITPART_LBICEP
							|| chr->hitpart == HITPART_RHAND
							|| chr->hitpart == HITPART_RFOREARM
							|| chr->hitpart == HITPART_RBICEP) {
						anim = ANIM_01F8;
					} else {
						if (random() % 2) {
							anim = ANIM_0018;
						} else {
							anim = ANIM_0028;
						}
					}
				}
			} else {
				if (gospeed == SPEED_RUN) {
					// Human, light weapon, running
					if (chr->hitpart == HITPART_LFOOT
							|| chr->hitpart == HITPART_LSHIN
							|| chr->hitpart == HITPART_LTHIGH) {
						anim = ANIM_020A;
						flip = true;
						speed = 0.4;
					} else if (chr->hitpart == HITPART_RFOOT
							|| chr->hitpart == HITPART_RSHIN
							|| chr->hitpart == HITPART_RTHIGH) {
						anim = ANIM_020A;
						speed = 0.4;
						flip = false;
					} else if (chr->hitpart == HITPART_LHAND
							|| chr->hitpart == HITPART_LFOREARM
							|| chr->hitpart == HITPART_LBICEP) {
						anim = ANIM_020D;
						speed = 0.4;
						flip = true;
					} else if (chr->hitpart == HITPART_RHAND
							|| chr->hitpart == HITPART_RFOREARM
							|| chr->hitpart == HITPART_RBICEP) {
						anim = ANIM_020D;
						speed = 0.4;
						flip = false;
					} else if (male) {
						if (random() % 4 == 0) {
							speed = 0.25;
							anim = ANIM_001E;
						} else {
							speed = 0.25;
							anim = ANIM_005A;
							sp60 = 24;
						}
					} else {
						if (random() % 2) {
							anim = ANIM_005E;
						} else {
							anim = ANIM_005A;
						}

						speed = 0.25;
					}

					if (chr->chrflags & CHRCFLAG_RUNFASTER) {
						animspeed = 0.65;
						startframe = 48;
					} else {
						animspeed = 0.5;
						startframe = 48;
					}
				} else if (gospeed == SPEED_JOG) {
					// Human, light weapon, jogging
					if (chr->hitpart == HITPART_LFOOT
							|| chr->hitpart == HITPART_LSHIN
							|| chr->hitpart == HITPART_LTHIGH) {
						anim = ANIM_01F9;
						flip = false;
					} else if (chr->hitpart == HITPART_RFOOT
							|| chr->hitpart == HITPART_RSHIN
							|| chr->hitpart == HITPART_RTHIGH) {
						anim = ANIM_01F9;
						flip = true;
					} else if (chr->hitpart == HITPART_LHAND
							|| chr->hitpart == HITPART_LFOREARM
							|| chr->hitpart == HITPART_LBICEP) {
						anim = ANIM_01F8;
						flip = false;
					} else if (chr->hitpart == HITPART_RHAND
							|| chr->hitpart == HITPART_RFOREARM
							|| chr->hitpart == HITPART_RBICEP) {
						anim = ANIM_01F8;
						flip = true;
					} else if (stageGetIndex(g_Vars.stagenum) == STAGEINDEX_CHICAGO) {
						anim = ANIM_005F;
					} else if (male) {
						if (random() % 2) {
							anim = ANIM_001D;
						} else {
							anim = ANIM_RUNNING_ONEHANDGUN;
						}
					} else {
						if (chr->myaction != MA_PANIC) {
							if (random() % 2) {
								anim = ANIM_005D;
							} else {
								anim = ANIM_0073;
							}
						} else {
							anim = ANIM_021D;
						}
					}
				} else {
					// Human, light weapon, walking
					s32 anims[] = {ANIM_006B, ANIM_001B, ANIM_0016};

					if (chr->hitpart == HITPART_LFOOT
							|| chr->hitpart == HITPART_LSHIN
							|| chr->hitpart == HITPART_LTHIGH) {
						anim = ANIM_01F9;
						flip = false;
					} else if (chr->hitpart == HITPART_RFOOT
							|| chr->hitpart == HITPART_RSHIN
							|| chr->hitpart == HITPART_RTHIGH) {
						anim = ANIM_01F9;
						flip = true;
					} else if (chr->hitpart == HITPART_LHAND
							|| chr->hitpart == HITPART_LFOREARM
							|| chr->hitpart == HITPART_LBICEP) {
						anim = ANIM_01F8;
						flip = false;
					} else if (chr->hitpart == HITPART_RHAND
							|| chr->hitpart == HITPART_RFOREARM
							|| chr->hitpart == HITPART_RBICEP) {
						anim = ANIM_01F8;
						flip = true;
					} else if (male) {
						anim = anims[random() % 3];
					} else {
						if (random() % 2) {
							anim = ANIM_005C;
						} else {
							anim = ANIM_0072;
						}
					}
				}
			}
		}
	} else if (race == RACE_DRCAROLL) {
		if (gospeed == SPEED_RUN) {
			anim = ANIM_0160;
		} else if (gospeed == SPEED_WALK) {
			anim = ANIM_015F;
		} else {
			anim = ANIM_015F;
		}
	} else if (race == RACE_ROBOT) {
		anim = ANIM_0238;
	}

	if (anim >= 0) {
		modelSetAnimation(chr->model, anim, flip, 0, speed, sp60);

		if (animspeed > 0) {
			modelSetAnimSpeed(chr->model, animspeed, startframe);
		}
	}
}

bool chrGoToPos(struct chrdata *chr, struct coord *pos, s16 *room, u32 flags)
{
	struct prop *prop = chr->prop;
	struct waypoint *nextwaypoint;
	struct waypoint *lastwaypoint;
	struct waypoint *waypoints[MAX_CHRWAYPOINTS];
	s32 i;
	struct coord curwppos;
	s16 curwprooms[8];
	s32 isgopos = chr->actiontype == ACT_GOPOS
		&& (chr->act_gopos.flags & GOPOSFLAG_SPEED) == (flags & 0xff & GOPOSFLAG_SPEED)
		&& !func0f02e064(chr);
	s32 ismagic = isgopos && chr->act_gopos.waydata.mode == WAYMODE_MAGIC;
	struct coord prevpos;
	s32 numwaypoints = 0;

	for (i = 0; chr->prop->rooms[i] != -1; i++) {
		chr->oldrooms[i] = chr->prop->rooms[i];
	}

	chr->oldrooms[i] = -1;

	if (isgopos && ismagic && chr->act_gopos.waypoints[chr->act_gopos.curindex]) {
		nextwaypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex];
	} else {
		nextwaypoint = waypointFindClosestToPos(&prop->pos, prop->rooms);
	}

	lastwaypoint = waypointFindClosestToPos(pos, room);

	if (nextwaypoint && lastwaypoint) {
		waypointSetHashThing(
				((g_Vars.lvframe60 >> 9) << 7) + chr->chrnum * 8,
				((g_Vars.lvframe60 >> 9) << 7) + chr->chrnum * 8);
		numwaypoints = waypointFindRoute(nextwaypoint, lastwaypoint, waypoints, MAX_CHRWAYPOINTS);
		waypointSetHashThing(0, 0);
	}

	if (numwaypoints > 1) {
		if (isgopos && ismagic) {
			chrCalculatePosition(chr, &prevpos);
		} else {
			prevpos.x = prop->pos.x;
			prevpos.y = prop->pos.y;
			prevpos.z = prop->pos.z;
		}

		chrStopFiring(chr);

		chr->actiontype = ACT_GOPOS;
		chr->act_gopos.endpos.x = pos->x;
		chr->act_gopos.endpos.y = pos->y;
		chr->act_gopos.endpos.z = pos->z;
		roomsCopy(room, chr->act_gopos.endrooms);

		chr->act_gopos.target = lastwaypoint;
		chr->act_gopos.curindex = 0;
		chr->act_gopos.flags = flags | GOPOSFLAG_INIT;
		chr->act_gopos.turnspeed = 0;
		chr->unk32c_21 = 0;
		chr->act_gopos.waydata.age = random() % 100;
		chr->act_gopos.waydata.gotaimposobj = 0;

		if (!isgopos) {
			chr->act_gopos.waydata.lastvisible60 = -1;
		}

		for (i = 0; i < MAX_CHRWAYPOINTS; i++) {
			chr->act_gopos.waypoints[i] = waypoints[i];
		}

		chrGoPosInitExpensive(chr);
#if VERSION >= VERSION_NTSC_1_0
		chr->goposforce = -1;
#endif
		chr->sleep = 0;
		chr->liftaction = 0;
		chr->act_gopos.flags &= ~(GOPOSFLAG_80 | GOPOSFLAG_DUCK | GOPOSFLAG_20);
		chrGoPosGetCurWaypointInfo(chr, &curwppos, curwprooms);

		if ((!isgopos || ismagic)
				&& g_Vars.normmplayerisrunning == false
				&& (prop->flags & (PROPFLAG_ONANYSCREENPREVTICK | PROPFLAG_ONANYSCREENTHISTICK | PROPFLAG_ONTHISSCREENTHISTICK)) == 0
				&& func0f036c08(chr, &curwppos, curwprooms)
				&& chr->inlift == false) {
			chrGoPosInitMagic(chr, &chr->act_gopos.waydata, &curwppos, &prevpos);
		}

		if (chr->act_gopos.waydata.mode != WAYMODE_MAGIC
				&& modelIsAnimMerging(chr->model) && !chr->aibot) {
			chr->hidden |= CHRHFLAG_NEEDANIM;
			return true;
		} else {
			if (!isgopos) {
				chrGoPosChooseAnimation(chr);
			}

			chr->hidden &= ~CHRHFLAG_NEEDANIM;
			return true;
		}
	}

	return false;
}

struct path *pathFindById(u32 path_id)
{
	s32 i = 0;

	for (i = 0; g_StageSetup.paths[i].pads; i++) {
		if (path_id == g_StageSetup.paths[i].id) {
			return &g_StageSetup.paths[i];
		}
	}

	return NULL;
}

void chrPatrolChooseAnimation(struct chrdata *chr)
{
	struct prop *leftprop = chrGetHeldProp(chr, HAND_LEFT);
	struct prop *rightprop = chrGetHeldProp(chr, HAND_RIGHT);
	s32 flip;
	bool heavy;
	s32 race = CHRRACE(chr);
	s32 ismale = g_HeadsAndBodies[chr->bodynum].ismale;
	f32 speed;

	if (race == RACE_EYESPY) {
		// empty
	} else if (race == RACE_HUMAN || race == RACE_SKEDAR) {
		if ((leftprop && rightprop) || (!leftprop && !rightprop)) {
			// No weapon, or double weapons
			heavy = false;
			flip = random() % 2;
		} else {
			// Single weapon
			if (weaponIsOneHanded(leftprop) || weaponIsOneHanded(rightprop)) {
				heavy = false;
				flip = ((bool)leftprop != false);
			} else {
				heavy = true;
				flip = ((bool)leftprop != false);
			}
		}

		if (race == RACE_SKEDAR) {
			modelSetAnimation(chr->model, ANIM_0392, flip, 0, 0.25f, 16);
		} else {
			speed = 0.5f * func0f02dff0(0x28) / func0f02dff0(0x6b);

			if (heavy) {
				modelSetAnimation(chr->model, random() % 2 ? ANIM_0018 : ANIM_0028, flip, 0, speed, 16);
			} else if (ismale) {
				s32 anims[] = { ANIM_006B, ANIM_001B, ANIM_0016 };
				modelSetAnimation(chr->model, anims[random() % 3], flip, 0, speed, 16);
			} else {
				modelSetAnimation(chr->model, random() % 2 ? ANIM_005C : ANIM_0072, flip, 0, speed, 16);
			}
		}
	} else if (race == RACE_DRCAROLL) {
		modelSetAnimation(chr->model, ANIM_015F, false, 0, 0.5f, 16);
	} else if (race == RACE_ROBOT) {
		modelSetAnimation(chr->model, ANIM_0238, false, 0, 0.5f, 16);
	}
}

GLOBAL_ASM(
glabel chrStartPatrol
.late_rodata
glabel var7f1a8dd0
.word 0x3f99999a
.text
/*  f038b9c:	27bdfef0 */ 	addiu	$sp,$sp,-272
/*  f038ba0:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*  f038ba4:	afbf0044 */ 	sw	$ra,0x44($sp)
/*  f038ba8:	afb40040 */ 	sw	$s4,0x40($sp)
/*  f038bac:	afb3003c */ 	sw	$s3,0x3c($sp)
/*  f038bb0:	afb20038 */ 	sw	$s2,0x38($sp)
/*  f038bb4:	afb10034 */ 	sw	$s1,0x34($sp)
/*  f038bb8:	afb00030 */ 	sw	$s0,0x30($sp)
/*  f038bbc:	4480a000 */ 	mtc1	$zero,$f20
/*  f038bc0:	00809825 */ 	or	$s3,$a0,$zero
/*  f038bc4:	00a0a025 */ 	or	$s4,$a1,$zero
/*  f038bc8:	2412ffff */ 	addiu	$s2,$zero,-1
/*  f038bcc:	10800003 */ 	beqz	$a0,.L0f038bdc
/*  f038bd0:	8c91001c */ 	lw	$s1,0x1c($a0)
/*  f038bd4:	10000002 */ 	b	.L0f038be0
/*  f038bd8:	908202fe */ 	lbu	$v0,0x2fe($a0)
.L0f038bdc:
/*  f038bdc:	00001025 */ 	or	$v0,$zero,$zero
.L0f038be0:
/*  f038be0:	24010003 */ 	addiu	$at,$zero,0x3
/*  f038be4:	504100ca */ 	beql	$v0,$at,.L0f038f10
/*  f038be8:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*  f038bec:	82620333 */ 	lb	$v0,0x333($s3)
/*  f038bf0:	0442002e */ 	bltzl	$v0,.L0f038cac
/*  f038bf4:	262b0008 */ 	addiu	$t3,$s1,0x8
/*  f038bf8:	968e0006 */ 	lhu	$t6,0x6($s4)
/*  f038bfc:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f038c00:	004e082a */ 	slt	$at,$v0,$t6
/*  f038c04:	50200029 */ 	beqzl	$at,.L0f038cac
/*  f038c08:	262b0008 */ 	addiu	$t3,$s1,0x8
/*  f038c0c:	8e8f0000 */ 	lw	$t7,0x0($s4)
/*  f038c10:	24050042 */ 	addiu	$a1,$zero,0x42
/*  f038c14:	27a600a8 */ 	addiu	$a2,$sp,0xa8
/*  f038c18:	01f81821 */ 	addu	$v1,$t7,$t8
/*  f038c1c:	0fc456ac */ 	jal	padUnpack
/*  f038c20:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f038c24:	8fb900f0 */ 	lw	$t9,0xf0($sp)
/*  f038c28:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f038c2c:	a7a8007e */ 	sh	$t0,0x7e($sp)
/*  f038c30:	02202025 */ 	or	$a0,$s1,$zero
/*  f038c34:	27a50070 */ 	addiu	$a1,$sp,0x70
/*  f038c38:	27a60078 */ 	addiu	$a2,$sp,0x78
/*  f038c3c:	27a70074 */ 	addiu	$a3,$sp,0x74
/*  f038c40:	0fc0a277 */ 	jal	chrGetBbox
/*  f038c44:	a7b9007c */ 	sh	$t9,0x7c($sp)
/*  f038c48:	02602025 */ 	or	$a0,$s3,$zero
/*  f038c4c:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f038c50:	00002825 */ 	or	$a1,$zero,$zero
/*  f038c54:	24090020 */ 	addiu	$t1,$zero,0x20
/*  f038c58:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f038c5c:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f038c60:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f038c64:	c620000c */ 	lwc1	$f0,0xc($s1)
/*  f038c68:	c7a40078 */ 	lwc1	$f4,0x78($sp)
/*  f038c6c:	c7a80074 */ 	lwc1	$f8,0x74($sp)
/*  f038c70:	26240008 */ 	addiu	$a0,$s1,0x8
/*  f038c74:	46002181 */ 	sub.s	$f6,$f4,$f0
/*  f038c78:	26250028 */ 	addiu	$a1,$s1,0x28
/*  f038c7c:	27a600a8 */ 	addiu	$a2,$sp,0xa8
/*  f038c80:	46004281 */ 	sub.s	$f10,$f8,$f0
/*  f038c84:	e7a60018 */ 	swc1	$f6,0x18($sp)
/*  f038c88:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f038c8c:	0c00b610 */ 	jal	cd0002d840
/*  f038c90:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f038c94:	10400002 */ 	beqz	$v0,.L0f038ca0
/*  f038c98:	02602025 */ 	or	$a0,$s3,$zero
/*  f038c9c:	82720333 */ 	lb	$s2,0x333($s3)
.L0f038ca0:
/*  f038ca0:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f038ca4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f038ca8:	262b0008 */ 	addiu	$t3,$s1,0x8
.L0f038cac:
/*  f038cac:	262c0028 */ 	addiu	$t4,$s1,0x28
/*  f038cb0:	afac0050 */ 	sw	$t4,0x50($sp)
/*  f038cb4:	06410028 */ 	bgez	$s2,.L0f038d58
/*  f038cb8:	afab0054 */ 	sw	$t3,0x54($sp)
/*  f038cbc:	8e820000 */ 	lw	$v0,0x0($s4)
/*  f038cc0:	00008025 */ 	or	$s0,$zero,$zero
/*  f038cc4:	00003825 */ 	or	$a3,$zero,$zero
/*  f038cc8:	8c4d0000 */ 	lw	$t5,0x0($v0)
/*  f038ccc:	05a00022 */ 	bltz	$t5,.L0f038d58
/*  f038cd0:	00107080 */ 	sll	$t6,$s0,0x2
.L0f038cd4:
/*  f038cd4:	004e1821 */ 	addu	$v1,$v0,$t6
/*  f038cd8:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f038cdc:	afa7004c */ 	sw	$a3,0x4c($sp)
/*  f038ce0:	24050002 */ 	addiu	$a1,$zero,0x2
/*  f038ce4:	0fc456ac */ 	jal	padUnpack
/*  f038ce8:	27a600a8 */ 	addiu	$a2,$sp,0xa8
/*  f038cec:	c7b200a8 */ 	lwc1	$f18,0xa8($sp)
/*  f038cf0:	c6300008 */ 	lwc1	$f16,0x8($s1)
/*  f038cf4:	c7ae00b0 */ 	lwc1	$f14,0xb0($sp)
/*  f038cf8:	c62c0010 */ 	lwc1	$f12,0x10($s1)
/*  f038cfc:	46109001 */ 	sub.s	$f0,$f18,$f16
/*  f038d00:	8fa7004c */ 	lw	$a3,0x4c($sp)
/*  f038d04:	06400009 */ 	bltz	$s2,.L0f038d2c
/*  f038d08:	460c7081 */ 	sub.s	$f2,$f14,$f12
/*  f038d0c:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f038d10:	00000000 */ 	nop
/*  f038d14:	46021282 */ 	mul.s	$f10,$f2,$f2
/*  f038d18:	460a4400 */ 	add.s	$f16,$f8,$f10
/*  f038d1c:	4614803c */ 	c.lt.s	$f16,$f20
/*  f038d20:	00000000 */ 	nop
/*  f038d24:	45000005 */ 	bc1f	.L0f038d3c
/*  f038d28:	00000000 */ 	nop
.L0f038d2c:
/*  f038d2c:	46000482 */ 	mul.s	$f18,$f0,$f0
/*  f038d30:	02009025 */ 	or	$s2,$s0,$zero
/*  f038d34:	46021102 */ 	mul.s	$f4,$f2,$f2
/*  f038d38:	46049500 */ 	add.s	$f20,$f18,$f4
.L0f038d3c:
/*  f038d3c:	8e820000 */ 	lw	$v0,0x0($s4)
/*  f038d40:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f038d44:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f038d48:	00477821 */ 	addu	$t7,$v0,$a3
/*  f038d4c:	8df80000 */ 	lw	$t8,0x0($t7)
/*  f038d50:	0703ffe0 */ 	bgezl	$t8,.L0f038cd4
/*  f038d54:	00107080 */ 	sll	$t6,$s0,0x2
.L0f038d58:
/*  f038d58:	8e990000 */ 	lw	$t9,0x0($s4)
/*  f038d5c:	00124080 */ 	sll	$t0,$s2,0x2
/*  f038d60:	24050042 */ 	addiu	$a1,$zero,0x42
/*  f038d64:	03281821 */ 	addu	$v1,$t9,$t0
/*  f038d68:	8c640000 */ 	lw	$a0,0x0($v1)
/*  f038d6c:	0fc456ac */ 	jal	padUnpack
/*  f038d70:	27a600a8 */ 	addiu	$a2,$sp,0xa8
/*  f038d74:	8fa900f0 */ 	lw	$t1,0xf0($sp)
/*  f038d78:	240affff */ 	addiu	$t2,$zero,-1
/*  f038d7c:	27ab007c */ 	addiu	$t3,$sp,0x7c
/*  f038d80:	a7aa007e */ 	sh	$t2,0x7e($sp)
/*  f038d84:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f038d88:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f038d8c:	3c017f1b */ 	lui	$at,%hi(var7f1a8dd0)
/*  f038d90:	a7a9007c */ 	sh	$t1,0x7c($sp)
/*  f038d94:	c6660024 */ 	lwc1	$f6,0x24($s3)
/*  f038d98:	c4288dd0 */ 	lwc1	$f8,%lo(var7f1a8dd0)($at)
/*  f038d9c:	240c0030 */ 	addiu	$t4,$zero,0x30
/*  f038da0:	afac001c */ 	sw	$t4,0x1c($sp)
/*  f038da4:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f038da8:	02602025 */ 	or	$a0,$s3,$zero
/*  f038dac:	8fa50054 */ 	lw	$a1,0x54($sp)
/*  f038db0:	8fa60050 */ 	lw	$a2,0x50($sp)
/*  f038db4:	27a700a8 */ 	addiu	$a3,$sp,0xa8
/*  f038db8:	0fc0d953 */ 	jal	func0f03654c
/*  f038dbc:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f038dc0:	1040004a */ 	beqz	$v0,.L0f038eec
/*  f038dc4:	8fa900f0 */ 	lw	$t1,0xf0($sp)
/*  f038dc8:	0fc0fe3d */ 	jal	chrStopFiring
/*  f038dcc:	02602025 */ 	or	$a0,$s3,$zero
/*  f038dd0:	240d000e */ 	addiu	$t5,$zero,0xe
/*  f038dd4:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f038dd8:	a26d0007 */ 	sb	$t5,0x7($s3)
/*  f038ddc:	ae74002c */ 	sw	$s4,0x2c($s3)
/*  f038de0:	ae720030 */ 	sw	$s2,0x30($s3)
/*  f038de4:	0c004b70 */ 	jal	random
/*  f038de8:	ae6e0034 */ 	sw	$t6,0x34($s3)
/*  f038dec:	24010064 */ 	addiu	$at,$zero,0x64
/*  f038df0:	0041001b */ 	divu	$zero,$v0,$at
/*  f038df4:	44808000 */ 	mtc1	$zero,$f16
/*  f038df8:	00007810 */ 	mfhi	$t7
/*  f038dfc:	2418ffff */ 	addiu	$t8,$zero,-1
/*  f038e00:	ae6f0060 */ 	sw	$t7,0x60($s3)
/*  f038e04:	a260003b */ 	sb	$zero,0x3b($s3)
/*  f038e08:	ae780078 */ 	sw	$t8,0x78($s3)
/*  f038e0c:	02602025 */ 	or	$a0,$s3,$zero
/*  f038e10:	0fc0dd60 */ 	jal	func0f037580
/*  f038e14:	e670007c */ 	swc1	$f16,0x7c($s3)
/*  f038e18:	8e790030 */ 	lw	$t9,0x30($s3)
/*  f038e1c:	27b0009c */ 	addiu	$s0,$sp,0x9c
/*  f038e20:	27b1008c */ 	addiu	$s1,$sp,0x8c
/*  f038e24:	a2600008 */ 	sb	$zero,0x8($s3)
/*  f038e28:	a260032c */ 	sb	$zero,0x32c($s3)
/*  f038e2c:	02203025 */ 	or	$a2,$s1,$zero
/*  f038e30:	02002825 */ 	or	$a1,$s0,$zero
/*  f038e34:	02602025 */ 	or	$a0,$s3,$zero
/*  f038e38:	0fc0dd58 */ 	jal	chrPatrolGetCurWaypointInfo
/*  f038e3c:	a2790333 */ 	sb	$t9,0x333($s3)
/*  f038e40:	3c08800a */ 	lui	$t0,%hi(g_Vars+0x318)
/*  f038e44:	8d08a2d8 */ 	lw	$t0,%lo(g_Vars+0x318)($t0)
/*  f038e48:	55000014 */ 	bnezl	$t0,.L0f038e9c
/*  f038e4c:	826e0068 */ 	lb	$t6,0x68($s3)
/*  f038e50:	8e69001c */ 	lw	$t1,0x1c($s3)
/*  f038e54:	02602025 */ 	or	$a0,$s3,$zero
/*  f038e58:	02002825 */ 	or	$a1,$s0,$zero
/*  f038e5c:	912a0001 */ 	lbu	$t2,0x1($t1)
/*  f038e60:	314b00c2 */ 	andi	$t3,$t2,0xc2
/*  f038e64:	5560000d */ 	bnezl	$t3,.L0f038e9c
/*  f038e68:	826e0068 */ 	lb	$t6,0x68($s3)
/*  f038e6c:	0fc0db02 */ 	jal	func0f036c08
/*  f038e70:	02203025 */ 	or	$a2,$s1,$zero
/*  f038e74:	50400009 */ 	beqzl	$v0,.L0f038e9c
/*  f038e78:	826e0068 */ 	lb	$t6,0x68($s3)
/*  f038e7c:	826d032d */ 	lb	$t5,0x32d($s3)
/*  f038e80:	02602025 */ 	or	$a0,$s3,$zero
/*  f038e84:	26650038 */ 	addiu	$a1,$s3,0x38
/*  f038e88:	05a00003 */ 	bltz	$t5,.L0f038e98
/*  f038e8c:	02003025 */ 	or	$a2,$s0,$zero
/*  f038e90:	0fc0dbb9 */ 	jal	chrGoPosInitMagic
/*  f038e94:	8fa70054 */ 	lw	$a3,0x54($sp)
.L0f038e98:
/*  f038e98:	826e0068 */ 	lb	$t6,0x68($s3)
.L0f038e9c:
/*  f038e9c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f038ea0:	11c1000a */ 	beq	$t6,$at,.L0f038ecc
/*  f038ea4:	00000000 */ 	nop
/*  f038ea8:	0c0076e5 */ 	jal	modelIsAnimMerging
/*  f038eac:	8e640020 */ 	lw	$a0,0x20($s3)
/*  f038eb0:	10400006 */ 	beqz	$v0,.L0f038ecc
/*  f038eb4:	00000000 */ 	nop
/*  f038eb8:	8e6f0014 */ 	lw	$t7,0x14($s3)
/*  f038ebc:	3c010020 */ 	lui	$at,0x20
/*  f038ec0:	01e1c025 */ 	or	$t8,$t7,$at
/*  f038ec4:	10000011 */ 	b	.L0f038f0c
/*  f038ec8:	ae780014 */ 	sw	$t8,0x14($s3)
.L0f038ecc:
/*  f038ecc:	0fc0e21a */ 	jal	chrPatrolChooseAnimation
/*  f038ed0:	02602025 */ 	or	$a0,$s3,$zero
/*  f038ed4:	8e790014 */ 	lw	$t9,0x14($s3)
/*  f038ed8:	3c01ffdf */ 	lui	$at,0xffdf
/*  f038edc:	3421ffff */ 	ori	$at,$at,0xffff
/*  f038ee0:	03214024 */ 	and	$t0,$t9,$at
/*  f038ee4:	10000009 */ 	b	.L0f038f0c
/*  f038ee8:	ae680014 */ 	sw	$t0,0x14($s3)
.L0f038eec:
/*  f038eec:	240affff */ 	addiu	$t2,$zero,-1
/*  f038ef0:	a7a90060 */ 	sh	$t1,0x60($sp)
/*  f038ef4:	a7aa0062 */ 	sh	$t2,0x62($sp)
/*  f038ef8:	02602025 */ 	or	$a0,$s3,$zero
/*  f038efc:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f038f00:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f038f04:	0fc0e10f */ 	jal	chrGoToPos
/*  f038f08:	24070008 */ 	addiu	$a3,$zero,0x8
.L0f038f0c:
/*  f038f0c:	8fbf0044 */ 	lw	$ra,0x44($sp)
.L0f038f10:
/*  f038f10:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*  f038f14:	8fb00030 */ 	lw	$s0,0x30($sp)
/*  f038f18:	8fb10034 */ 	lw	$s1,0x34($sp)
/*  f038f1c:	8fb20038 */ 	lw	$s2,0x38($sp)
/*  f038f20:	8fb3003c */ 	lw	$s3,0x3c($sp)
/*  f038f24:	8fb40040 */ 	lw	$s4,0x40($sp)
/*  f038f28:	03e00008 */ 	jr	$ra
/*  f038f2c:	27bd0110 */ 	addiu	$sp,$sp,0x110
);

//void chrStartPatrol(struct chrdata *chr, struct path *path)
//{
//	f32 bestdistance = 0;
//	s32 nextstep = -1;
//	f32 xdiff;
//	f32 zdiff;
//	s32 i;
//	struct pad pad; // a8
//	struct coord nextpos; // 9c
//	s16 nextrooms[8]; // 8c
//	s16 rooms[8]; // 7c
//	f32 ymax; // 78
//	f32 ymin; // 74
//	f32 width; // 70
//	s16 sp60[8]; // 60
//	struct prop *prop = chr->prop;
//
//	if (CHRRACE(chr) != RACE_EYESPY) {
//		// Do some kind of collision test with the pad to resume from...
//		// maybe a line of sight check?
//		if (chr->patrolnextstep >= 0 && chr->patrolnextstep < path->len) {
//			padUnpack(path->pads[chr->patrolnextstep], PADFIELD_POS | PADFIELD_ROOM, &pad);
//
//			rooms[0] = pad.room;
//			rooms[1] = -1;
//
//			chrGetBbox(prop, &width, &ymax, &ymin);
//
//			chrSetPerimEnabled(chr, false);
//
//			if (cd0002d840(&prop->pos, prop->rooms, &pad.pos, rooms, CDTYPE_BG, 1,
//						ymax - prop->pos.y, ymin - prop->pos.y) != CDRESULT_COLLISION) {
//				nextstep = chr->patrolnextstep;
//			}
//
//			chrSetPerimEnabled(chr, true);
//		}
//
//		// If the pad to resume from is not in sight, find the closest pad
//		// to the chr's current position and start from there.
//		if (nextstep < 0) {
//			for (i = 0; path->pads[i] >= 0; i++) {
//				f32 dist;
//				padUnpack(path->pads[i], PADFIELD_POS, &pad);
//
//				xdiff = pad.pos.x - prop->pos.x;
//				zdiff = pad.pos.z - prop->pos.z;
//				dist = xdiff * xdiff + zdiff * zdiff;
//
//				if (nextstep < 0 || dist < bestdistance) {
//					bestdistance = dist;
//					nextstep = i;
//				}
//			}
//		}
//
//		padUnpack(path->pads[nextstep], PADFIELD_POS | PADFIELD_ROOM, &pad);
//
//		rooms[0] = pad.room;
//		rooms[1] = -1;
//
//		// If chr has line of sight to the pad then begin the patrol,
//		// otherwise use gopos to get to the starting pad
//		if (func0f03654c(chr, &prop->pos, prop->rooms, &pad.pos, rooms, NULL, chr->chrwidth * 1.2f, CDTYPE_PATHBLOCKER | CDTYPE_BG) != CDRESULT_COLLISION) {
//			chrStopFiring(chr);
//
//			chr->actiontype = ACT_PATROL;
//			chr->act_patrol.path = path;
//			chr->act_patrol.nextstep = nextstep;
//			chr->act_patrol.forward = true;
//
//			chr->act_patrol.waydata.age = random() % 100;
//			chr->act_patrol.waydata.gotaimposobj = 0;
//
//			chr->act_patrol.unk78 = -1;
//			chr->act_patrol.unk7c = 0;
//
//			func0f037580(chr);
//
//			chr->sleep = 0;
//			chr->liftaction = LIFTACTION_NOTUSINGLIFT;
//			chr->patrolnextstep = chr->act_patrol.nextstep;
//
//			chrPatrolGetCurWaypointInfo(chr, &nextpos, nextrooms);
//
//			if (!g_Vars.normmplayerisrunning
//					&& (chr->prop->flags & (PROPFLAG_ONTHISSCREENTHISTICK | PROPFLAG_ONANYSCREENTHISTICK | PROPFLAG_ONANYSCREENPREVTICK)) == 0
//					&& func0f036c08(chr, &nextpos, nextrooms)
//					&& !chr->inlift) {
//				chrGoPosInitMagic(chr, &chr->act_patrol.waydata, &nextpos, &prop->pos);
//			}
//
//			if (chr->act_patrol.waydata.unk30 != 6 && modelIsAnimMerging(chr->model)) {
//				chr->hidden |= CHRHFLAG_NEEDANIM;
//			} else {
//				chrPatrolChooseAnimation(chr);
//				chr->hidden &= ~CHRHFLAG_NEEDANIM;
//			}
//		} else {
//			sp60[0] = pad.room;
//			sp60[1] = -1;
//
//			chrGoToPos(chr, &pad.pos, sp60, GOPOSFLAG_FORPATHSTART);
//		}
//	}
//}

void chrRecordLastVisibleTargetTime(struct chrdata *chr)
{
	chr->lastvisibletarget60 = g_Vars.lvframe60;
}

bool chrCanSeeEntity(struct chrdata *chr, struct coord *chrpos, s16 *chrrooms, bool allowextraheight, u32 attackflags, u32 entityid)
{
	bool result = false;
	struct coord targetpos;
	s16 targetrooms[8];
	struct prop *targetprop;
	struct chrdata *targetchr;
	u32 types;
	struct prop *weaponprop;

	if (attackflags & ATTACKFLAG_AIMFORWARD) {
		result = true;
	} else {
		types = CDTYPE_DOORSWITHOUTFLAG | CDTYPE_ALL;
		weaponprop = chrGetHeldProp(chr, HAND_RIGHT);

		if (weaponprop == NULL) {
			weaponprop = chrGetHeldProp(chr, HAND_LEFT);
		}

		if (weaponprop) {
			struct weaponobj *weapon = weaponprop->weapon;

			if (weapon->weaponnum == WEAPON_ROCKETLAUNCHER
					|| weapon->weaponnum == WEAPON_SLAYER
					|| weapon->weaponnum == WEAPON_ROCKETLAUNCHER_34) {
				types = CDTYPE_DOORSWITHOUTFLAG | CDTYPE_OBJSWITHFLAG2 | CDTYPE_ALL;
			} else {
				types = CDTYPE_DOORSWITHOUTFLAG | CDTYPE_OBJSWITHFLAG | CDTYPE_ALL;
			}
		}

		chrGetAttackEntityPos(chr, attackflags, entityid, &targetpos, targetrooms);
		chrSetPerimEnabled(chr, false);

		if ((attackflags & ATTACKFLAG_AIMATTARGET)) {
			targetprop = chrGetTargetProp(chr);

			if (targetprop->type != PROPTYPE_PLAYER || g_Vars.bondvisible) {
				propSetPerimEnabled(targetprop, false);

				if (allowextraheight && (chr->chrflags & CHRCFLAG_LOSEXTRAHEIGHT)) {
					struct coord frompos;
					s16 fromrooms[8];

					frompos.x = chrpos->x;
					frompos.y = chrpos->y + 70;
					frompos.z = chrpos->z;

					func0f065dd8(chrpos, chrrooms, &frompos, fromrooms);

					if (cdHasLineOfSight(&frompos, fromrooms, &targetpos, targetrooms, types, 0x10)) {
						chrRecordLastVisibleTargetTime(chr);
						result = true;
					}
				} else {
					if (cdHasLineOfSight(chrpos, chrrooms, &targetpos, targetrooms, types, 0x10)) {
						chrRecordLastVisibleTargetTime(chr);
						result = true;
					}
				}

				propSetPerimEnabled(targetprop, true);
			}
		} else if (attackflags & ATTACKFLAG_AIMATCHR) {
			targetchr = chrFindById(chr, entityid);

			if (!targetchr || !targetchr->prop) {
				targetchr = chr;
			}

			chrSetPerimEnabled(targetchr, false);

			if (cdHasLineOfSight(chrpos, chrrooms, &targetpos, targetrooms, types, 0x10)) {
				result = true;
			}

			chrSetPerimEnabled(targetchr, true);
		} else if (attackflags & ATTACKFLAG_AIMATPAD) {
			if (cdHasLineOfSight(chrpos, chrrooms, &targetpos, targetrooms, types, 0x10)) {
				result = true;
			}
		}

		chrSetPerimEnabled(chr, true);
	}

	return result;
}

bool chrCanSeeAttackTarget(struct chrdata *chr, struct coord *pos, s16 *rooms, bool allowextraheight)
{
	u32 attackflags = ATTACKFLAG_AIMATTARGET;
	u32 entityid = 0;

	if (chr->actiontype == ACT_ATTACK) {
		attackflags = chr->act_attack.flags;
		entityid = chr->act_attack.entityid;
	}

	return chrCanSeeEntity(chr, pos, rooms, allowextraheight, attackflags, entityid);
}

bool chrCanSeeChr(struct chrdata *chr, struct chrdata *target, s16 *room)
{
	bool cansee = false;
	u32 stack;
	s16 sp88[] = {-1, 0, 0, 0, 0, 0, 0, 0};

	if (func0f19294c(chr, target) == 0) {
		struct prop *prop = chr->prop;
		struct coord pos;
		s16 rooms[8];

		pos.x = prop->pos.x;
		pos.y = chr->ground + chr->chrheight - 20;
		pos.z = prop->pos.z;

		chrSetPerimEnabled(chr, false);
		chrSetPerimEnabled(target, false);

		func0f065e74(&prop->pos, prop->rooms, &pos, rooms);

		if (cd0002dcfc(&pos, rooms, &target->prop->pos, target->prop->rooms, sp88, 307, 8)) {
			cansee = true;
		}

		chrSetPerimEnabled(chr, true);
		chrSetPerimEnabled(target, true);
	}

	if (room) {
		*room = sp88[0];
	}

	return cansee;
}

bool chrCanSeeTarget(struct chrdata *chr)
{
	bool cansee;
	struct prop *prop = chrGetTargetProp(chr);
	cansee = chrCanSeeChr(chr, prop->chr, NULL);

	if (cansee) {
		chrRecordLastVisibleTargetTime(chr);
	}

	return cansee;
}

bool chrHasLineOfSightToPos(struct chrdata *viewerchr, struct coord *pos, s16 *rooms)
{
	struct prop *viewerprop = viewerchr->prop;
	bool result = false;
	struct coord viewerpos;
	s16 viewerrooms[8];

	viewerpos.x = viewerprop->pos.x;
	viewerpos.y = viewerchr->ground + viewerchr->chrheight - 20;
	viewerpos.z = viewerprop->pos.z;

	chrSetPerimEnabled(viewerchr, false);
	func0f065e74(&viewerprop->pos, viewerprop->rooms, &viewerpos, viewerrooms);

	if (cdHasLineOfSight(&viewerpos, viewerrooms, pos, rooms, 307, 8)) {
		result = true;
	}

	chrSetPerimEnabled(viewerchr, true);

	return result;
}

bool chrCanSeePos(struct chrdata *chr, struct coord *pos, s16 *rooms)
{
	f32 facingangle = chrGetInverseTheta(chr);
	f32 posangle = atan2f(pos->x - chr->prop->pos.x, pos->z - chr->prop->pos.z);
	f32 diffangle = posangle - facingangle;

	if (posangle < facingangle) {
		diffangle += M_BADTAU;
	}

	// This check is pointless because chrHasLineOfSightToPos is called
	// with the same arguments regardless.
	if ((diffangle < 1.7450513839722f || diffangle > 4.5371336936951f)
			&& chrHasFlag(chr, CHRFLAG1_00200000, BANK_1) == false) {
		return chrHasLineOfSightToPos(chr, pos, rooms);
	}

	return chrHasLineOfSightToPos(chr, pos, rooms);
}

bool chrCanSeeProp(struct chrdata *chr, struct prop *prop)
{
	bool result;

	propSetPerimEnabled(prop, false);
	result = chrCanSeePos(chr, &prop->pos, prop->rooms);
	propSetPerimEnabled(prop, true);

	return result;
}

void chrRecordLastSeeTargetTime(struct chrdata *chr)
{
	chr->lastseetarget60 = g_Vars.lvframe60;
}

void chrRecordLastHearTargetTime(struct chrdata *chr)
{
	chr->hidden |= CHRHFLAG_IS_HEARING_TARGET;
	chr->lastheartarget60 = g_Vars.lvframe60;
}

bool chrIsStopped(struct chrdata *chr)
{
	s16 anim = modelGetAnimNum(chr->model);

	if (anim == ANIM_SNIPING_GETDOWN || anim == ANIM_SNIPING_GETUP) {
		return false;
	}

	if (anim == ANIM_SNIPING_ONGROUND && chr->act_attack.numshots >= chr->act_attack.maxshots) {
		chrStopFiring(chr);
		return true;
	}

	if (chr->actiontype == ACT_ROBOTATTACK && chr->act_robotattack.finished) {
		return true;
	}

	if (chr->actiontype == ACT_ATTACKAMOUNT && chr->act_attack.numshots >= chr->act_attack.maxshots) {
		return true;
	}

	if (chr->actiontype == ACT_STAND
			&& !chr->act_stand.prestand
			&& !chr->act_stand.reaim
			&& chr->act_stand.turning != 1) {
		return true;
	}

	if (chr->actiontype == ACT_ANIM) {
		if (chr->act_anim.completed
				|| (modelGetAnimSpeed(chr->model) >= 0 && modelGetCurAnimFrame(chr->model) >= modelGetAnimEndFrame(chr->model))
				|| (modelGetAnimSpeed(chr->model) < 0 && modelGetCurAnimFrame(chr->model) <= 0)) {
			return true;
		}
	} else if (chr->actiontype == ACT_PATROL) {
		return true;
	}

	return false;
}

bool chrCheckTargetInSight(struct chrdata *chr)
{
	struct prop *prop = chr->prop;
	struct prop *target = chrGetTargetProp(chr);
	f32 sqdistance;
	f32 fVar5 = chrGetInverseTheta(chr);

	f32 x = target->pos.x - prop->pos.x;
	f32 y = target->pos.y - prop->pos.y;
	f32 z = target->pos.z - prop->pos.z;

	f32 fVar6 = atan2f(x, z);
	f32 angle = fVar6 - fVar5;
	bool result = false;

	if (fVar6 < fVar5) {
		angle += M_BADTAU;
	}

	sqdistance = x * x + y * y + z * z;

	if ((sqdistance < chr->visionrange * chr->visionrange * 10000.0f && (angle < 1.9195564985275f || angle > 4.3626284599304f))
			|| (sqdistance < 40000.0f && (angle < 1.9195564985275f || angle > 4.3626284599304f))) {
		result = false;

		if (sqdistance < func0f1657e4()) {
			f32 tmp;
			s32 iVar8 = (sqrtf(sqdistance) * 0.0018749999580905f);
			s32 tmp2;

			if (angle > 0.7852731347084f && angle < 5.4969120025635f) {
				tmp = angle;

				if (tmp > M_PI) {
					tmp = M_BADTAU - angle;
				}

				tmp -= 0.7852731347084f;
				tmp2 = tmp * 3.8203268051147f;
				iVar8 *= 1 + tmp2;
			}

			iVar8 = chrGetPercentageOfSlowness(chr, iVar8) + 1;
			result = random() % iVar8 == 0;
		}
	}

	if (result) {
		result = chrCanSeeTarget(chr);
	}

	if (result) {
		chrRecordLastSeeTargetTime(chr);
	}

	return result;
}

bool chrIsReadyForOrders(struct chrdata *chr)
{
	if (chr->onladder) {
		return false;
	}

	switch (chr->actiontype) {
	case ACT_DIE:
	case ACT_DEAD:
	case ACT_PREARGH:
	case ACT_DRUGGEDDROP:
	case ACT_DRUGGEDKO:
	case ACT_DRUGGEDCOMINGUP:
#if VERSION < VERSION_NTSC_1_0
	case ACT_ARGH:
	case 0x200:
#endif
		return false;
#if VERSION >= VERSION_NTSC_1_0
	case ACT_ARGH:
		if ((chr->chrflags & CHRCFLAG_00000200) == 0) {
			return false;
		}
		break;
#endif
	case ACT_ROBOTATTACK:
		if (!chr->act_robotattack.finished) {
			return false;
		}
		break;
	}

	return true;
}

bool chrIsDead(struct chrdata *chr)
{
	if (!chr || chr->actiontype == ACT_DIE || chr->actiontype == ACT_DEAD) {
		return true;
	}

	if (chr->prop && chr->prop->type == PROPTYPE_PLAYER) {
		u32 playernum = propGetPlayerNum(chr->prop);

		if (g_Vars.players[playernum]->isdead) {
			return true;
		}
	}

	return false;
}

bool chrTrySidestep(struct chrdata *chr)
{
	u8 race = CHRRACE(chr);

	if ((race == RACE_HUMAN || race == RACE_SKEDAR)
			&& chrIsReadyForOrders(chr)) {
		struct prop *prop = chr->prop;
		struct prop *target = chrGetTargetProp(chr);
		f32 a = chrGetInverseTheta(chr);
		f32 b = atan2f(target->pos.x - prop->pos.x, target->pos.z - prop->pos.z);
		f32 angle = b - a;
		u32 stack[2];

		if (b < a) {
			angle += M_BADTAU;
		}

		if (angle < 0.7852731347084f || angle > 5.4969120025635f
				|| (angle > 2.3558194637299f && angle < 3.9263656139374f)) {
			bool side = (random() % 2) == 0;

			if (chrCanJumpInDirection(chr, side, 100)) {
				chrSidestep(chr, side);
				return true;
			}

			if (chrCanJumpInDirection(chr, !side, 100)) {
				chrSidestep(chr, !side);
				return true;
			}
		}
	}

	return false;
}

bool chrTryJumpOut(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		struct prop *prop = chr->prop;
		struct prop *target = chrGetTargetProp(chr);

		f32 a = chrGetInverseTheta(chr);
		f32 b = atan2f(target->pos.x - prop->pos.x, target->pos.z - prop->pos.z);
		f32 angle = b - a;
		u32 stack[2];

		if (b < a) {
			angle += M_BADTAU;
		}

		// This commented code is what the floats represent, but mismatches due
		// to float precision:
		//if (angle < BADDEG2RAD(45) || angle > BADDEG2RAD(315)
		//		|| (angle > BADDEG2RAD(135) && angle < BADDEG2RAD(225))) {
		if (angle < 0.7852731347084f || angle > 5.4969120025635f
				|| (angle > 2.3558194637299f && angle < BADDEG2RAD(225))) {
			bool side = (random() % 2) == 0;

			if (chrCanJumpInDirection(chr, side, 200)) {
				chrJumpOut(chr, side);
				return true;
			}

			if (chrCanJumpInDirection(chr, !side, 200)) {
				chrJumpOut(chr, !side);
				return true;
			}
		}
	}

	return false;
}

bool chrTryRunSideways(struct chrdata *chr)
{
	u32 race = CHRRACE(chr);

	if ((race == RACE_HUMAN || race == RACE_SKEDAR)
			&& chrIsReadyForOrders(chr)
			&& g_Vars.lvframe60 - chr->lastwalk60 > PALDOWN(180)) {
		struct prop *prop = chr->prop;
		f32 distance = 200.0f + random() * (1.0f / U32_MAX) * 200.0f;
		struct coord vector;
		struct coord dstpos;

		chrGetSideVectorToTarget(chr, random() % 2 == 0, &vector);

		dstpos.x = vector.x * distance + prop->pos.x;
		dstpos.y = prop->pos.y;
		dstpos.z = vector.z * distance + prop->pos.z;

		if (propchrHasClearLineToPos(prop, &dstpos, &vector)) {
			chrRunToPos(chr, &dstpos);
			return true;
		}

		vector.x = -vector.x;
		vector.z = -vector.z;

		dstpos.x = vector.x * distance + prop->pos.x;
		dstpos.y = prop->pos.y;
		dstpos.z = vector.z * distance + prop->pos.z;

		if (propchrHasClearLineToPos(prop, &dstpos, &vector)) {
			chrRunToPos(chr, &dstpos);
			return true;
		}
	}

	return false;
}

bool chrTryAttackWalk(struct chrdata *chr)
{
	u32 race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_EYESPY) {
		return false;
	}

	if (chrIsReadyForOrders(chr)) {
		struct prop *prop = chr->prop;

		if (chrCanSeeAttackTarget(chr, &prop->pos, prop->rooms, false)
				&& (chrGetHeldUsableProp(chr, 0) || chrGetHeldUsableProp(chr, 1))
				&& g_Vars.lvframe60 - chr->lastwalk60 > PALDOWN(120)) {
			struct prop *target = chrGetTargetProp(chr);
			f32 x = target->pos.x - prop->pos.x;
			f32 y = target->pos.y - prop->pos.y;
			f32 z = target->pos.z - prop->pos.z;

			if (race == RACE_HUMAN && x * x + y * y + z * z >= 1000 * 1000) {
				chrAttackWalk(chr, false);
				return true;
			}
		}
	}

	return false;
}

bool chrTryAttackRun(struct chrdata *chr)
{
	u32 race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_EYESPY) {
		return false;
	}

	if (chrIsReadyForOrders(chr)) {
		struct prop *prop = chr->prop;

		if (chrCanSeeAttackTarget(chr, &prop->pos, prop->rooms, false)
				&& (chrGetHeldUsableProp(chr, 0) || chrGetHeldUsableProp(chr, 1))
				&& g_Vars.lvframe60 - chr->lastwalk60 > PALDOWN(180)) {
			struct prop *target = chrGetTargetProp(chr);
			f32 x = target->pos.x - prop->pos.x;
			f32 y = target->pos.y - prop->pos.y;
			f32 z = target->pos.z - prop->pos.z;

			if (race == RACE_HUMAN && x * x + y * y + z * z >= 1000 * 1000) {
				chrAttackWalk(chr, true);
				return true;
			}
		}
	}

	return false;
}

bool chrTryAttackRoll(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		struct prop *prop = chr->prop;

		if (chrCanSeeAttackTarget(chr, &prop->pos, prop->rooms, false) &&
				(chrGetHeldUsableProp(chr, 0) || chrGetHeldUsableProp(chr, 1))) {
			struct prop *target = chrGetTargetProp(chr);
			f32 x = target->pos.x - prop->pos.x;
			f32 y = target->pos.y - prop->pos.y;
			f32 z = target->pos.z - prop->pos.z;
			f32 sqdistance = x * x + y * y + z * z;

			if (sqdistance >= 200 * 200) {
				bool toleft = (random() % 2) == 0;

				if (chrCanRollInDirection(chr, toleft, 200)) {
					chrAttackRoll(chr, toleft);
					return true;
				}

				if (chrCanRollInDirection(chr, !toleft, 200)) {
					chrAttackRoll(chr, !toleft);
					return true;
				}
			}
		}
	}

	return false;
}

bool chrTryAttackAmount(struct chrdata *chr, u32 arg1, u32 arg2, u8 lower, u8 upper)
{
	u8 race = CHRRACE(chr);

	if ((race == RACE_HUMAN || race == RACE_SKEDAR)
			&& chrIsReadyForOrders(chr)
			&& chr->weapons_held[0]) {
		s32 quantity;
		f32 percentage;
		struct weaponobj *weapon = chr->weapons_held[0]->weapon;
		struct inventory_ammo *ammo;

		quantity = 1;

		if (upper > 100) {
			upper = 100;
		}

		if (lower < upper) {
			percentage = ((random() % (upper - lower)) + (u32)lower) * 0.01f;
		} else {
			percentage = 0;
		}

		ammo = weaponGetAmmoByFunction(weapon->weaponnum, 0);

		if (ammo) {
			quantity = ammo->clipsize * percentage;
		}

		if (quantity < 1) {
			quantity = 1;
		}

		chr->aimendrshoulder = 0;
		chr->aimendlshoulder = 0;
		chr->aimendback = 0;
		chr->aimendsideback = 0;
		chr->aimendcount = 10;

		chrAttackAmount(chr, arg1, arg2, quantity);

		return true;
	}

	return false;
}

bool chrTryAttackStand(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	s32 race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_EYESPY) {
		return false;
	}

	if (chrIsReadyForOrders(chr)) {
		if (race == RACE_ROBOT) {
			robotAttack(chr);
			return true;
		}

		if (race == RACE_HUMAN || race == RACE_SKEDAR) {
			if (chrGetHeldUsableProp(chr, 0) ||
					(chrGetHeldUsableProp(chr, 1))) {
				chrAttackStand(chr, attackflags, entityid);
				return true;
			}
		}
	}

	return false;
}

bool chrTryAttackKneel(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	s32 race = CHRRACE(chr);

	if (race == RACE_HUMAN || race == RACE_SKEDAR) {
		if (chrIsReadyForOrders(chr) && (chrGetHeldUsableProp(chr, 0) || chrGetHeldUsableProp(chr, 1))) {
			chrAttackKneel(chr, attackflags, entityid);
			return true;
		}
	}

	return false;
}

bool chrTryAttackLie(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	s32 race = CHRRACE(chr);

	if (race == RACE_HUMAN || race == RACE_SKEDAR) {
		if (chrIsReadyForOrders(chr) && (chrGetHeldUsableProp(chr, 0) || chrGetHeldUsableProp(chr, 1))) {
			chrAttackLie(chr, attackflags, entityid);
			return true;
		}
	}

	return false;
}

bool chrTryModifyAttack(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	s32 race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_EYESPY) {
		return false;
	}

	if (chr->actiontype == ACT_ATTACK
			&& (chr->act_attack.flags & (ATTACKFLAG_AIMONLY | ATTACKFLAG_DONTTURN))) {
		chr->act_attack.flags = attackflags;
		chr->act_attack.entityid = entityid;
		func0f031254(chr);
		return true;
	}

	return false;
}

bool chrFaceEntity(struct chrdata *chr, u32 attackflags, s32 entityid)
{
	if (chrIsReadyForOrders(chr)) {
		if (chr->actiontype != ACT_STAND) {
			chrStand(chr);
		}

		if (attackflags != chr->act_stand.flags || entityid != chr->act_stand.entityid) {
			chr->act_stand.flags = attackflags;
			chr->act_stand.entityid = entityid;
			chr->act_stand.reaim = 0;
			chr->act_stand.checkfacingwall = false;

			if (attackflags == ATTACKFLAG_AIMATTARGET && entityid == 1) {
				chr->act_stand.playwalkanim = true;
				chr->act_stand.entityid = 0;
			}
		}

		return true;
	}

	return false;
}

bool chrGoToPad(struct chrdata *chr, s32 padnum, u32 speed)
{
	if (padnum >= 0
			&& chrIsReadyForOrders(chr)
#if VERSION >= VERSION_NTSC_1_0
			&& (var80062cbc <= 8
				|| (chr->hidden & CHRHFLAG_00400000) == 0
				|| (chr->flags & CHRFLAG0_CAN_GO_TO_PLACES))
#else
			&& var80062cbc <= 9
#endif
				) {
		padnum = chrResolvePadId(chr, padnum);

#if VERSION >= VERSION_NTSC_1_0
		if (padnum >= 0)
#endif
		{
			s16 rooms[2];
			struct pad pad;

			padUnpack(padnum, PADFIELD_ROOM | PADFIELD_POS, &pad);

			rooms[0] = pad.room;
			rooms[1] = -1;

			if (chrGoToPos(chr, &pad.pos, rooms, speed)) {
				return true;
			}
		}
	}

	return false;
}

bool chrSetPath(struct chrdata *chr, u32 path_id)
{
	chr->path = path_id;
	return true;
}

bool chrTryStartPatrol(struct chrdata *chr)
{
	struct path *path = pathFindById(chr->path);

	if (path && chrIsReadyForOrders(chr)) {
		chrStartPatrol(chr, path);
		return true;
	}

	return false;
}

bool chrTrySurrender(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		chrSurrender(chr);
		return true;
	}

	return false;
}

bool chrFadeOut(struct chrdata *chr)
{
	chrBeginDead(chr);
	chrFadeCorpse(chr);

	return true;
}

bool chrGoToTarget(struct chrdata *chr, u32 speed)
{
	if (chrIsReadyForOrders(chr)) {
		if (
#if VERSION >= VERSION_NTSC_1_0
				var80062cbc <= 8 ||
				(chr->hidden & CHRHFLAG_00400000) == 0 ||
				(chr->flags & CHRFLAG0_CAN_GO_TO_PLACES)
#else
				var80062cbc <= 9
#endif
				) {
			struct prop *prop = chrGetTargetProp(chr);

			if (chrGoToPos(chr, &prop->pos, prop->rooms, speed)) {
				return true;
			}
		}
	}

	return false;
}

bool chrGoToChr(struct chrdata *chr, u32 dst_chrnum, u32 speed)
{
	if (chrIsReadyForOrders(chr)) {
		if (
#if VERSION >= VERSION_NTSC_1_0
				var80062cbc <= 8 ||
				(chr->hidden & CHRHFLAG_00400000) == 0 ||
				(chr->flags & CHRFLAG0_CAN_GO_TO_PLACES)
#else
				var80062cbc <= 9
#endif
				) {
			struct chrdata *dstchr = chrFindById(chr, dst_chrnum);

			if (dstchr && dstchr->prop && chrGoToPos(chr, &dstchr->prop->pos, dstchr->prop->rooms, speed)) {
				return true;
			}
		}
	}

	return false;
}

bool chrGoToProp(struct chrdata *chr, struct prop *prop, s32 speed)
{
	if (chrIsReadyForOrders(chr) && prop) {
		if (chrGoToPos(chr, &prop->pos, prop->rooms, speed)) {
			return true;
		}
	}

	return false;
}

bool func0f03abd0(struct chrdata *chr, struct coord *pos, u32 flags)
{
	s16 roomlist1[21];
	s16 roomlist2[21];

	if (chrIsReadyForOrders(chr)) {
#if VERSION >= VERSION_NTSC_1_0
		if (var80062cbc < 9
				|| (chr->hidden & CHRHFLAG_00400000) == 0
				|| (chr->flags & CHRCFLAG_00040000))
#else
		if (var80062cbc < 10)
#endif
		{
			s16 *rooms = NULL;

			func0f162194(pos, roomlist1, roomlist2, 20, NULL);

			if (roomlist1[0] != -1) {
				rooms = roomlist1;
			} else if (roomlist2[0] != -1) {
				rooms = roomlist2;
			}

			if (rooms != NULL && chrGoToPos(chr, pos, rooms, flags)) {
				return true;
			}
		}
	}

	return false;
}

s32 func0f03aca0(struct chrdata *chr, f32 arg1, u8 arg2)
{
	f32 somefloat;

	if (!arg2) {
		arg1 -= chrGetDistanceToCoord(chr, &chr->runfrompos);
	}

	if (arg1 < 0) {
		chrAssignCoverByCriteria(g_Vars.chrdata,
				COVERCRITERIA_FURTHEREST
				| COVERCRITERIA_DISTTOTARGET
				| COVERCRITERIA_ONLYNEIGHBOURINGROOMS
				| COVERCRITERIA_ROOMSFROMME, 0);
		return chrGoToCover(chr, SPEED_RUN);
	}

	somefloat = arg1 - 2000;

	if (somefloat < 2000) {
		somefloat = 2000;
	}

	if (!chrAssignCoverAwayFromDanger(chr, somefloat, arg1 + 10000)) {
		chrAssignCoverByCriteria(g_Vars.chrdata,
				COVERCRITERIA_FURTHEREST
				| COVERCRITERIA_DISTTOTARGET
				| COVERCRITERIA_ONLYNEIGHBOURINGROOMS
				| COVERCRITERIA_ROOMSFROMME, 0);
	}

	return chrGoToCover(chr, SPEED_RUN);
}

bool chrTryStop(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_EYESPY) {
		func0f02e9a0(chr, 0);
		return true;
	}

	if (chrIsReadyForOrders(chr)) {
		chrStop(chr);
		return true;
	}

	return false;
}

bool chrTrySurprisedOneHand(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		chrDoSurprisedOneHand(chr);
		return true;
	}

	return false;
}

bool chrTrySurprisedSurrender(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		chrDoSurprisedSurrender(chr);
		return true;
	}

	return false;
}

bool chrTrySurprisedLookAround(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		chrDoSurprisedLookAround(chr);
		return true;
	}

	return false;
}

bool chrTryKneel(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		chrKneel(chr);
		return true;
	}

	return false;
}

bool chrTryStartAnim(struct chrdata *chr, s32 animfnum, f32 startframe, f32 endframe, u8 chranimflags, s32 merge, f32 speed)
{
	if (chrIsReadyForOrders(chr)) {
		chrStartAnim(chr, animfnum, startframe, endframe, chranimflags, merge, speed);
		return true;
	}

	return false;
}

bool chrTryRunFromTarget(struct chrdata *chr)
{
	struct prop *target = chrGetTargetProp(chr);
	struct prop *prop = chr->prop;
	f32 ymax;
	f32 ymin;
	f32 width;
	struct coord dst;
	s16 rooms[8];
	struct coord diff;
	f32 distance;

	if (chrIsReadyForOrders(chr)) {
		if (!target) {
			return false;
		}

		diff.x = target->pos.x - prop->pos.x;
		diff.z = target->pos.z - prop->pos.z;
		diff.y = 0;

		distance = sqrtf(diff.f[0] * diff.f[0] + diff.f[2] * diff.f[2]);

		// Scale diff into range -1 to +1
		diff.x *= (1 / distance);
		diff.z *= (1 / distance);

		// Set dst to 1000 units in the opposite direction
		dst.x = prop->pos.x - diff.x * 1000;
		dst.z = prop->pos.z - diff.z * 1000;
		dst.y = prop->pos.y;

		propGetBbox(prop, &width, &ymax, &ymin);

		// If dst runs into a wall, set it to closest valid spot
		if (!cd0002d7c0(&prop->pos, prop->rooms, &dst, 0x33, 1,
					ymax - prop->pos.y, ymin - prop->pos.y)) {
#if VERSION >= VERSION_PAL_FINAL
			cdGetPos(&dst, 8793, "chr/chraction.c");
#elif VERSION >= VERSION_NTSC_1_0
			cdGetPos(&dst, 8788, "chraction.c");
#else
			cdGetPos(&dst, 8782, "chraction.c");
#endif
		}

		// Adjust dst to be two chr widths closer to avoid collision with wall
		dst.x = dst.x + (diff.x * width + diff.x * width);
		dst.z = dst.z + (diff.z * width + diff.z * width);

		if (func0f036974(prop, &dst)) {
			u32 speed = SPEED_RUN;

			if (CHRRACE(chr) == RACE_HUMAN) {
				f32 dist = chrGetDistanceToCoord(chr, &dst);

				if (dist > 100) {
					speed = SPEED_RUN;
				} else if (dist < 50) {
					speed = SPEED_WALK;
				} else {
					speed = SPEED_JOG;
				}
			}

			func0f065e74(&prop->pos, prop->rooms, &dst, rooms);
			chrGoToPos(chr, &dst, rooms, speed);

			return true;
		}
	}

	return false;
}

const char var7f1a8ae4[] = "aimadjust=%d";

#if VERSION >= VERSION_PAL_FINAL
const char var7f1a8af4[] = "chr/chraction.c";
#else
const char var7f1a8af4[] = "chraction.c";
#endif

const char var7f1a8b00[] = "firing(%d) %d, beam(%d) %s";
const char var7f1a8b1c[] = "on";
const char var7f1a8b20[] = "off";
const char var7f1a8b24[] = "firecount(%d) = %d";
const char var7f1a8b38[] = "numshots(%d) = %d";

/**
 * Attempt to make the chr find a suitable prop in their current room to use as
 * cover and run to it. However, a bug prevents this from working.
 */
bool chrGoToCoverProp(struct chrdata *chr)
{
	struct prop *targetprop = chrGetTargetProp(chr);
	struct prop *chrprop = chr->prop;
	s16 i;
	s16 propnums[258];
	struct defaultobj *obj;
	s16 numprops;
	s16 startindex;

	if (targetprop == NULL) {
		return false;
	}

	if (chrIsReadyForOrders(chr)) {
		roomGetProps(chrprop->rooms, propnums, 256);

		for (numprops = 0; propnums[numprops] >= 0; numprops++);

		if (numprops > 0) {
			startindex = random() % numprops;
		}

		for (i = 0; i < numprops; i++) {
			struct prop *prop = &g_Vars.props[propnums[(i + startindex) % numprops]];
			obj = prop->obj;

			if (prop->type == PROPTYPE_OBJ
					&& (obj->hidden2 & OBJH2FLAG_DESTROYED) == 0
					&& (obj->hidden & OBJHFLAG_00008000) == 0
					&& (obj->hidden & OBJHFLAG_OCCUPIEDCHAIR) == 0) {
				f32 targetdist = propGetDistanceToProp(targetprop, prop);
				f32 chrdist = propGetDistanceToProp(chrprop, prop);

				// @bug: This condition cannot pass
				// (should be chrdist < targetdist + targetdist)
				if (chrdist < 300 && chrdist > targetdist + targetdist && targetdist > 800) {
					f32 propymax;
					f32 propymin;
					f32 propwidth;
					f32 chrymax;
					f32 chrymin;
					f32 chrwidth;
					f32 propheight;
					f32 chrheight;
					struct coord dstpos;
					s16 dstrooms[8];

					propGetBbox(prop, &propwidth, &propymax, &propymin);
					propGetBbox(chrprop, &chrwidth, &chrymax, &chrymin);

					propheight = propymax - propymin;
					chrheight = chrymax - chrymin;

					if (propheight > chrheight * 0.4f && propheight < chrheight * 0.9f) {
						propSetPerimEnabled(prop, false);

						if (cd0002dc18(&chrprop->pos, chrprop->rooms, &prop->pos, CDTYPE_DOORS | CDTYPE_BG)) {
							propSetPerimEnabled(prop, true);

							dstpos.x = prop->pos.x - (targetprop->pos.x - prop->pos.x) / targetdist * (propwidth * 1.25f + chrwidth);
							dstpos.z = prop->pos.z - (targetprop->pos.z - prop->pos.z) / targetdist * (propwidth * 1.25f + chrwidth);
							dstpos.y = prop->pos.y;

							if (func0f036974(chrprop, &dstpos)) {
								u32 speed = SPEED_JOG;

								if (CHRRACE(chr) == RACE_HUMAN) {
									if (chrdist > 1500) {
										speed = SPEED_RUN;
									} else if (chrdist < 100) {
										speed = SPEED_WALK;
									}
								}

								func0f065e74(&chrprop->pos, chrprop->rooms, &dstpos, dstrooms);
								chrGoToPos(chr, &dstpos, dstrooms, speed);

								chr->proppreset1 = prop - g_Vars.props;
								obj->hidden |= OBJHFLAG_OCCUPIEDCHAIR;

								return true;
							}
						}
					}

					propSetPerimEnabled(prop, true);
				}
			}
		}
	}

	return false;
}

bool chrTryStartAlarm(struct chrdata *chr, s32 pad_id)
{
	if (CHRRACE(chr) == RACE_HUMAN && chrIsReadyForOrders(chr)) {
		pad_id = chrResolvePadId(chr, pad_id);

#if VERSION >= VERSION_NTSC_1_0
		if (pad_id >= 0)
#endif
		{
			struct defaultobj *obj = objFindByPadNum(pad_id);

			if (obj && objIsHealthy(obj)) {
				chrStartAlarm(chr);
				return true;
			}
		}
	}

	return false;
}

s32 chrConsiderGrenadeThrow(struct chrdata *chr, u32 attackflags, u32 entityid)
{
	bool done = false;

	if (CHRRACE(chr) == RACE_HUMAN &&
			chr->grenadeprob > (random() % 255) &&
			chrGetDistanceToTarget(chr) > 200 &&
			chrIsReadyForOrders(chr)) {
		struct prop *target = chrGetTargetProp(chr);
		struct coord pos;

		if (target) {
			pos.x = target->pos.x;
			pos.y = target->pos.y;
			pos.z = target->pos.z;
		}

		if (target && cd0002dc18(&chr->prop->pos, chr->prop->rooms, &pos, 0x33)) {
			struct prop *leftprop = chrGetHeldProp(chr, 1);
			struct prop *rightprop = chrGetHeldProp(chr, 0);
			struct weaponobj *weapon;

#if PIRACYCHECKS
			{
				u32 checksum = 0;
				s32 *i = (s32 *)&bgInit;
				s32 *end = (s32 *)&bgBuildTables;
				u32 stackpadding[1];

				while (i < end) {
					checksum += *i;
					checksum += (*i >> 1);
					i++;
				}

				if (checksum != CHECKSUM_PLACEHOLDER) {
					// Make player explode continuously
					g_Vars.currentplayer->bondexploding = true;
					g_Vars.currentplayer->bondnextexplode = g_Vars.lvframe60 + 120;
					g_Vars.currentplayer->bondcurexplode = 0;
				}
			}
#endif

			// If grenade is equipped in either hand, use it
			if (rightprop) {
				weapon = rightprop->weapon;

				if (weapon->weaponnum == WEAPON_GRENADE || weapon->weaponnum == WEAPON_NBOMB) {
					chrThrowGrenade(chr, 0, false);
					chr->act_throwgrenade.flags = attackflags;
					chr->act_throwgrenade.entityid = entityid;
					done = true;
				}
			}

			if (!done && leftprop) {
				weapon = leftprop->weapon;

				if (weapon->weaponnum == WEAPON_GRENADE || weapon->weaponnum == WEAPON_NBOMB) {
					chrThrowGrenade(chr, 1, false);
					chr->act_throwgrenade.flags = attackflags;
					chr->act_throwgrenade.entityid = entityid;
					done = true;
				}
			}

			// Grenade not equipped, and using a single weapon
			if (!done && (leftprop == NULL || rightprop == NULL)) {
				struct prop *prop;
				u32 flags = 0;
				u32 stackpadding2[2];

				if (rightprop) {
					flags = OBJFLAG_WEAPON_LEFTHANDED;
				}

				if (stageGetIndex(g_Vars.stagenum) == STAGEINDEX_MBR) {
					prop = chrGiveWeapon(chr, MODEL_CHRGRENADE, WEAPON_NBOMB, flags);
				} else {
					prop = chrGiveWeapon(chr, MODEL_CHRGRENADE, WEAPON_GRENADE, flags);
				}

				if (prop) {
					weapon = prop->weapon;
					weapon->base.hidden |= OBJHFLAG_00000800;
					chrThrowGrenade(chr, rightprop == NULL ? 0 : 1, true);
					chr->act_throwgrenade.flags = attackflags;
					chr->act_throwgrenade.entityid = entityid;
					done = true;
				}
			}
		}
	}

	return done;
}

bool chrDropItem(struct chrdata *chr, u32 modelnum, u32 weaponnum)
{
	struct weaponobj *weapon;
	u8 race = CHRRACE(chr);

	if (race == RACE_DRCAROLL || race == RACE_ROBOT) {
		return false;
	}

	weapon = func0f08b880(modelnum, (u8)weaponnum, chr);

	if (weapon && weapon->base.prop) {
		modelSetScale(weapon->base.model, weapon->base.model->scale);
		propReparent(weapon->base.prop, chr->prop);
		weapon->timer240 = PALDOWN(720);
		objSetDropped(weapon->base.prop, DROPTYPE_DEFAULT);
		chr->hidden |= CHRHFLAG_00000001;

		return true;
	}

	return false;
}

void chrPunchInflictDamage(struct chrdata *chr, s32 damage, s32 range, u8 reverse)
{
	struct prop *targetprop = chrGetTargetProp(chr);
	struct gset gset = {WEAPON_UNARMED, 0, 0, FUNC_PRIMARY};
	struct coord vector;

	if (chr->aibot) {
		gset.weaponnum = chr->aibot->weaponnum;
		gset.weaponfunc = chr->aibot->gunfunc;
	}

	if (chrIsTargetInFov(chr, 20, reverse)
			&& chrGetDistanceToTarget(chr) < range
			&& cd0002dc18(&chr->prop->pos, chr->prop->rooms, &targetprop->pos, 0x33)) {
		vector.x = targetprop->pos.x - chr->prop->pos.x;
		vector.y = 0;
		vector.z = targetprop->pos.z - chr->prop->pos.z;

		guNormalize(&vector.x, &vector.y, &vector.z);

		bgunPlayPropHitSound(&gset, targetprop, -1);

		if (targetprop->type == PROPTYPE_PLAYER || targetprop->type == PROPTYPE_CHR) {
			chrDamageByImpact(targetprop->chr, gsetGetDamage(&gset) * damage, &vector, &gset, chr->prop, 200);
		}
	}

	weaponPlayWhooshSound(gset.weaponnum, chr->prop);
}

struct punchanim {
	s32 animnum;
	u32 damage;
	s16 hitframe;
	f32 endframe;
};

struct punchanim g_HumanPunchAnims[] = {
	{ 0x027c, 5, 20, 60 },
	{ 0x027d, 5, 20, 31 },
	{ 0x027e, 5, 20, 48 },
	{ 0x027f, 5, 20, 69 },
	{ 0x0212, 5, 20, 64 },
	{ 0x0213, 5, 20, 52 },
	{ 0x0214, 5, 20, 51 },
	{ 0x020e, 5, 20, 53 },
	{ 0x020f, 5, 20, 89 },
	{ 0x0210, 5, 20, 71 },
	{ 0x0215, 5, 20, 62 },
	{ 0x0211, 5, 20, 72 },
};

struct punchanim g_SkedarPunchAnims[] = {
	{ 0x034c, 15, 25, 100 },
	{ 0x034d, 15, 25, -1  },
	{ 0x0395, 15, 25, -1  },
	{ 0x0346, 15, 25, -1  },
	{ 0x0347, 15, 25, -1  },
	{ 0x034f, 15, 25, -1  },
};

/**
 * Make the chr try to punch or kick.
 *
 * The function is only ever called with reverse = 0. If non-zero, it would
 * cause Skedar to kick behind them.
 *
 * Note that the final human anim can't be used because the modulus value is too
 * short by one.
 */
bool chrTryPunch(struct chrdata *chr, u8 reverse)
{
	struct punchanim *anims = NULL;
	s32 race = CHRRACE(chr);
	s32 animindex;
	u32 chranimflags = (random() % 256 > 128) ? CHRANIMFLAG_FLIP : 0;
	s32 chrhitradius;
	s32 playerhitradius;
	f32 startframe;
	bool ok;

	if (race == RACE_HUMAN) {
		anims = g_HumanPunchAnims;
		startframe = 10;
		chrhitradius = 120;
		playerhitradius = 120;
		animindex = random() % 11;
	} else if (race == RACE_SKEDAR) {
		anims = g_SkedarPunchAnims;
		chrhitradius = 200;
#if VERSION >= VERSION_NTSC_1_0
		playerhitradius = 200;
#else
		playerhitradius = 350;
#endif
		startframe = 20;

		if (reverse) {
			// Skedar kick behind
			animindex = 5;
		} else if (!chr->weapons_held[HAND_RIGHT] && !chr->weapons_held[HAND_LEFT]) {
			// Unarmed: Only use indexes 0 or 1
			animindex = random() % 2;
		} else {
			// Allow indexes 0-4, but if 3 or 4 then flip the anim based on
			// which hand is holding the gun
			animindex = random() % 5;

			if (animindex >= 3) {
				if (!chr->weapons_held[HAND_RIGHT] || !chr->weapons_held[HAND_LEFT]) {
					if (chr->weapons_held[HAND_RIGHT]) {
						chranimflags = 0;
					} else if (chr->weapons_held[HAND_LEFT]) {
						chranimflags = CHRANIMFLAG_FLIP;
					}
				}
			}
		}
	}

	if (chrHasFlag(chr, CHRFLAG1_ADJUSTPUNCHSPEED, BANK_1)) {
		if (chrHasFlag(chr, CHRFLAG0_CHUCKNORRIS, BANK_0)) {
			// Fast punch
			ok = chrTryStartAnim(chr, anims[animindex].animnum, startframe, anims[animindex].endframe, chranimflags, 16, 1.5f);
		} else {
			// Slow punch
			ok = chrTryStartAnim(chr, anims[animindex].animnum, startframe, anims[animindex].endframe - 25, chranimflags, 16, 0.5f);
		}

		chr->dodgerating = 0;
	} else {
		// Normal punch
		ok = chrTryStartAnim(chr, anims[animindex].animnum, startframe, anims[animindex].endframe, chranimflags, 16, 0.85f);
		chr->dodgerating = 0;
	}

	if (ok) {
		struct prop *targetprop = chrGetTargetProp(chr);

		if (targetprop->type == PROPTYPE_EYESPY || targetprop->type == PROPTYPE_PLAYER) {
			chr->act_anim.hitradius = playerhitradius;
		} else {
			chr->act_anim.hitradius = chrhitradius;
		}

		chr->act_anim.ishitanim = true;
		chr->act_anim.hitframe = anims[animindex].hitframe;

		if (g_Vars.normmplayerisrunning) {
			chr->act_anim.hitdamage = 1;
		} else if (chrHasFlag(chr, CHRFLAG1_ADJUSTPUNCHSPEED, BANK_1) && chrHasFlag(chr, CHRFLAG0_CHUCKNORRIS, BANK_0)) {
			chr->act_anim.hitdamage = (u16)anims[animindex].damage * (f32)chr->morale + (u16)anims[animindex].damage * (f32)chr->morale;
		} else if (chrHasFlag(chr, CHRFLAG1_PUNCHHARDER, BANK_1)) {
			chr->act_anim.hitdamage = (u16)anims[animindex].damage * 6;
		} else {
			chr->act_anim.hitdamage = anims[animindex].damage;
		}

		chr->act_anim.reverse = reverse;
		chr->chrflags &= ~CHRCFLAG_INJUREDTARGET;

		return true;
	}

	return false;
}

void func0f03c03c(void)
{
	// empty
}

/**
 * Verifies that the given chr struct is actually an eyespy and returns the
 * eyespy struct.
 *
 * Eyespys have their own chr struct, even though they aren't a chr. Iterating
 * the player list is required because the only pointer to an eyespy is via the
 * player struct.
 */
struct eyespy *chrToEyespy(struct chrdata *chr)
{
	if (chr && chr->prop) {
		if (CHRRACE(chr) == RACE_EYESPY) {
			s32 playercount = PLAYERCOUNT();
			s32 i;

			for (i = 0; i < playercount; i++) {
				if (g_Vars.players[i]->eyespy && chr->prop == g_Vars.players[i]->eyespy->prop) {
					return g_Vars.players[i]->eyespy;
				}
			}

			return NULL;
		}
	}

	return NULL;
}

void chrTickStand(struct chrdata *chr)
{
	s32 race;
	s32 i;
	s32 j;
	s32 stack2;
	struct prop *leftgun;
	struct prop *rightgun;
	u32 stack[2];
	f32 angle;
	f32 sp74[8];
	f32 sp70;
	f32 sp6c;
	s32 tmp;
	s32 index;
	s32 sp44[8];

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrStandChooseAnimation(chr, chr->act_stand.mergetime);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (modelGetAnimNum(chr->model) == ANIM_SNIPING_GETUP) {
		if (modelGetCurAnimFrame(chr->model) >= modelGetAnimEndFrame(chr->model)) {
			chrStandChooseAnimation(chr, 8);
			chr->act_stand.prestand = 0;
		}

		return;
	}

	if (chr->sleep > 0) {
		return;
	}

	race = CHRRACE(chr);

	if (race == RACE_EYESPY) {
		return;
	}

	if (chr->act_stand.prestand) {
		if (modelGetCurAnimFrame(chr->model) >= modelGetAnimEndFrame(chr->model)) {
			chrStandChooseAnimation(chr, 8);
			chr->act_stand.prestand = 0;
		}

		chr->sleep = 0;
		return;
	}

	if (!chr->aibot && (race == RACE_HUMAN || race == RACE_SKEDAR) && chr->act_stand.flags > 0) {
		if (chr->act_stand.reaim) {
			chr->act_stand.turning = chrTurn(chr, chr->act_stand.turning, modelGetNumAnimFrames(chr->model) - 1, 1, 0);

			if (chr->act_stand.turning != TURNSTATE_TURNING) {
				chrStandChooseAnimation(chr, 8);
				chr->act_stand.reaim = false;

				if (chr->act_stand.flags & ATTACKFLAG_AIMATDIRECTION) {
					chr->act_stand.flags = 0;
				}
			}
		} else {
			f32 relangle = chrGetAttackEntityRelativeAngle(chr, chr->act_stand.flags, chr->act_stand.entityid);

			if ((relangle > 0.34901028871536f && relangle < 5.9331746101379f)
					|| (relangle > 0.17450514435768f && relangle < 6.1076798439026f && !chr->act_stand.playwalkanim)) {
				leftgun = chrGetHeldProp(chr, HAND_LEFT);
				rightgun = chrGetHeldProp(chr, HAND_RIGHT);

				chr->act_stand.reaim = true;
				chr->act_stand.turning = TURNSTATE_TURNING;

				if (race == RACE_HUMAN) {
					if ((leftgun && rightgun)
							|| (!leftgun && !rightgun)
							|| weaponIsOneHanded(leftgun)
							|| weaponIsOneHanded(rightgun)) {
						modelSetAnimation(chr->model, ANIM_006B, random() % 2, 0, 0.5f, 16);
						modelSetAnimEndFrame(chr->model, animGetNumFrames(ANIM_006B) - 1);
					} else {
						if (rightgun || leftgun) {
							modelSetAnimation(chr->model, ANIM_0028, leftgun != NULL, 0, 0.5f, 16);
							modelSetAnimEndFrame(chr->model, animGetNumFrames(ANIM_0028) - 1);
						}
					}
				} else if (race == RACE_SKEDAR) {
					modelSetAnimation(chr->model, ANIM_0392, random() % 2, 0, 0.5f, 16);
					modelSetAnimEndFrame(chr->model, animGetNumFrames(ANIM_0392) - 1);
				}
			} else if (chr->act_stand.flags & ATTACKFLAG_AIMATDIRECTION) {
				chr->act_stand.flags = 0;
			}
		}

		chr->sleep = 0;
		return;
	}

	if (chr->aibot) {
		return;
	}

	if (chr->prop->flags & PROPFLAG_ONANYSCREENPREVTICK) {
		chr->sleep = 0;
	} else {
		chr->sleep = 14 + (random() % 5);
	}

	if (chr->act_stand.checkfacingwall == false) {
		return;
	}

	if (chr->chrflags & CHRCFLAG_CANFACEWALL) {
		chr->act_stand.checkfacingwall = false;
		return;
	}

	chr->act_stand.wallcount -= chr->sleep;

	if (chr->act_stand.wallcount >= 0) {
		return;
	}

	sp6c = sp70 = chrGetInverseTheta(chr);

	for (i = 0; i < 8; i++) {
		sp6c += 0.7852731347084f;

		if (sp6c >= M_BADTAU) {
			sp6c -= M_BADTAU;
		}

		sp74[i] = func0f02e550(chr->prop, sp6c, 1000, CDTYPE_BG, 0, 1);
	}

	for (i = 0; i < 8; i++) {
		sp44[i] = i;
	}

	for (i = 0; i < 7; i++) {
		index = i;

		for (j = index + 1; j < 8; j++) {
			if (sp74[sp44[j]] < sp74[sp44[index]]) {
				index = j;
			}
		}

		j = sp44[i];
		sp44[i] = sp44[index];
		sp44[index] = j;
	}

	index = -1;

	if (sp74[0] < 490) {
		if (sp74[sp44[4]] < 200) {
			index = 7;
		} else if (sp44[0] == 0 || sp44[1] == 0 || sp44[2] == 0) {
			if ((sp44[3] == 4 || sp44[4] == 4) && (random() % 3) == 0) {
				if (sp44[3] == 4) {
					index = 3;
				} else {
					index = 4;
				}
			} else {
				index = 5 + random() % 3;
			}
		} else if ((sp44[0] == 1 || sp44[0] == 7) && sp44[5] && sp44[6] && sp44[7]) {
			index = 5 + random() % 3;
		}
	}

	if (index >= 0) {
		i = sp44[index];
		angle = sp70 + i * 0.7852731347084f;

		if (angle >= M_BADTAU) {
			angle -= M_BADTAU;
		}

		chrFaceEntity(chr, ATTACKFLAG_AIMATDIRECTION, angle * 10432.0390625f);
	} else {
		chr->act_stand.checkfacingwall = false;
	}
}

void chrTickKneel(struct chrdata *chr)
{
	chr->sleep = 0;

	if ((chr->hidden & CHRHFLAG_NEEDANIM) && !modelIsAnimMerging(chr->model)) {
		chrKneelChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}
}

void chrTickAnim(struct chrdata *chr)
{
	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		modelSetAnimation(chr->model, chr->act_anim.animnum, chr->act_anim.flip,
				chr->act_anim.startframe, chr->act_anim.speed, chr->act_anim.blend);

		if (chr->act_anim.endframe >= 0) {
			modelSetAnimEndFrame(chr->model, chr->act_anim.endframe);
		}

		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (!chr->act_anim.pauseatend && modelGetCurAnimFrame(chr->model) >= modelGetAnimEndFrame(chr->model)) {
		chrStand(chr);
	}

	if (chr->act_anim.ishitanim && modelGetCurAnimFrame(chr->model) >= (s32)chr->act_anim.hitframe) {
		chr->act_anim.ishitanim = false;
		chrPunchInflictDamage(chr, chr->act_anim.hitdamage, chr->act_anim.hitradius, chr->act_anim.reverse);
	}

	// Play sneezing sound
	if (CHRRACE(chr) == RACE_HUMAN
			&& modelGetAnimNum(chr->model) == ANIM_SNEEZE
			&& modelGetCurAnimFrame(chr->model) >= 42
			&& (g_Vars.lvframenum % 2) == 0
			&& chrGetDistanceToCurrentPlayer(chr) < 800) {
		func0f0939f8(NULL, chr->prop, SFX_0037, -1,
				-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
	}

	if (chr->sleep <= 0 && chr->act_anim.slowupdate) {
		chr->sleep = 14 + (random() % 5);
	}

	if (modelGetAnimNum(chr->model) == ANIM_RELOAD_0209) {
		chrSetFiring(chr, HAND_RIGHT, false);
		chrSetFiring(chr, HAND_LEFT, false);
	}
}

void chrTickSurrender(struct chrdata *chr)
{
	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrSurrenderChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (chr->sleep <= 0) {
		if (CHRRACE(chr) == RACE_HUMAN) {
			struct model *model = chr->model;
			chr->sleep = 16;

			if (modelGetAnimNum(model) == ANIM_SURRENDER_002F && modelGetCurAnimFrame(model) >= 80.0f) {
				struct coord coord = {0, 0, 0};
				f32 value = chrGetInverseTheta(chr);
				coord.x = -sinf(value);
				coord.z = -cosf(value);

				if (!propchrHasClearLineInVector(chr->prop, &coord, 20)) {
					modelSetAnimation(chr->model, ANIM_SURRENDER_002E, random() & 1, 30, 0.5, 16);
					modelSetAnimLooping(chr->model, 30, 16);
				}
			}
		}
	}
}

void chrFadeCorpse(struct chrdata *chr)
{
	if (chr->actiontype == ACT_DEAD || chr->actiontype == ACT_DRUGGEDKO) {
		chr->act_dead.fadenow = true;
	}
}

void chrFadeCorpseWhenOffScreen(struct chrdata *chr)
{
	if (chr->actiontype == ACT_DEAD) {
		chr->act_dead.fadewheninvis = true;
	}
}

void chrTickDead(struct chrdata *chr)
{
	struct aibot *aibot = chr->aibot;

	// If fade is active, handle it
	if (chr->act_dead.fadetimer60 >= 0) {
		chr->act_dead.fadetimer60 += g_Vars.lvupdate240_60;

		if (chr->act_dead.fadetimer60 >= PALDOWN(90)) {
			// Fade finished
			chr->fadealpha = 0;

			if (aibot) {
				mpInitSimulant(chr, true);
			} else {
				chr->hidden |= CHRHFLAG_REAPED;
			}
		} else {
			// Still fading
			chr->fadealpha = (PALDOWN(90) - chr->act_dead.fadetimer60) * 255 / PALDOWN(90);
		}
	} else {
		// If fade has been triggered (this can happen when the corpse is on
		// screen and there's lots of other chrs around)
		if (chr->act_dead.fadenow) {
			chr->act_dead.fadetimer60 = 0;
			chrDropItemsForOwnerReap(chr);
		}

		if (chr->prop->flags & PROPFLAG_ONANYSCREENPREVTICK) {
			// Keep corpse for now
			chr->act_dead.invistimer60 = 0;
		} else {
			chr->act_dead.invistimer60 += g_Vars.lvupdate240_60;
		}

		if (chr->act_dead.fadewheninvis && chr->act_dead.invistimer60 >= PALDOWN(120)) {
			// Remove corpse (off-screen)
			if (aibot == NULL) {
				chr->hidden |= CHRHFLAG_REAPED;
			}

			chr->fadealpha = 0;

			chrDropItemsForOwnerReap(chr);
		}
	}

	if (aibot == NULL) {
		chr->ailist = NULL;
	}
}

/**
 * This function is called when a chr is injured or killed. It iterates other
 * chrs within 2000 units who can see the chr and updates their chrseeshot or
 * chrseedie properties.
 *
 * The search stops once 7 chrs have been found in range, regardless of whether
 * they can see the chr, presumably to avoid doing too many expensive line of
 * sight checks in one tick. The last iterated chr index is stored and continued
 * from there next time the function is called. The function is called on
 * subsequent ticks while the chr is still in their injured or dying action.
 */
void chrAlertOthersOfInjury(struct chrdata *chr, bool dying)
{
	s32 index = 0;
	s32 numinrange = 0;
	s32 numchrs = chrsGetNumSlots();

	if (g_Vars.antiplayernum >= 0 && chr->prop == g_Vars.anti->prop) {
		return;
	}

	if (chr->actiontype == ACT_ARGH) {
		index = chr->act_argh.notifychrindex;
	} else if (chr->actiontype == ACT_DIE || chr->actiontype == ACT_DRUGGEDDROP) {
		index = chr->act_die.notifychrindex;
	} else if (chr->actiontype == ACT_DEAD) {
		index = chr->act_dead.notifychrindex;
	}

	for (; index < numchrs && numinrange < 7; index++) {
		struct chrdata *loopchr = &g_ChrSlots[index];

		if (loopchr->model && loopchr->prop && (loopchr->prop->flags & PROPFLAG_ENABLED)) {
			f32 xdiff = loopchr->prop->pos.x - chr->prop->pos.x;
			f32 ydiff = loopchr->prop->pos.y - chr->prop->pos.y;
			f32 zdiff = loopchr->prop->pos.z - chr->prop->pos.z;

			if (xdiff * xdiff + ydiff * ydiff + zdiff * zdiff < 4000000.0f) {
				numinrange++;

				if (chrCanSeePos(loopchr, &chr->prop->pos, chr->prop->rooms)) {
					if (dying == false) {
						loopchr->chrseeshot = chr->chrnum;
					} else {
						loopchr->chrseedie = chr->chrnum;
					}
				}
			}
		}
	}

	if (chr->actiontype == ACT_ARGH) {
		chr->act_argh.notifychrindex = index;
	} else if (chr->actiontype == ACT_DIE || chr->actiontype == ACT_DRUGGEDDROP) {
		chr->act_die.notifychrindex = index;
	} else if (chr->actiontype == ACT_DEAD) {
		chr->act_dead.notifychrindex = index;
	}
}

void chrTickDie(struct chrdata *chr)
{
	struct model *model = chr->model;
	u32 race = CHRRACE(chr);

	u16 thuds[] = {
		SFX_THUD_808D,
		SFX_THUD_808E,
		SFX_THUD_808F,
		SFX_THUD_8090,
		SFX_THUD_8091,
		SFX_THUD_8092,
		SFX_THUD_8093,
		SFX_THUD_8094,
		SFX_THUD_8095,
		SFX_THUD_8096,
		SFX_THUD_8097,
	};

	u16 specialdiesounds[] = {
#if VERSION >= VERSION_NTSC_1_0
		SFX_M1_NOOO, // "Noooo!"
		SFX_M1_SCREAM, // Death scream
		SFX_M2_NOOO, // "Noooo!"
		SFX_M2_NOOO, // "Noooo!"
		SFX_M1_SCREAM, // Death scream
#else
		SFX_0313,
		SFX_034C,
		SFX_0411,
		SFX_0411,
		SFX_034C,
#endif
		SFX_THUD_8092,
		SFX_THUD_8093,
		SFX_THUD_8094,
		SFX_THUD_8095,
		SFX_THUD_8096,
		SFX_THUD_8097,
	};

	static s32 thudindex = 0;

	if (race == RACE_EYESPY) {
		return;
	}

	if (race == RACE_ROBOT) {
		struct prop *prop = chr->prop;
		func0f0926bc(prop, 1, 0xffff);
		explosionCreateSimple(prop, &prop->pos, prop->rooms, EXPLOSIONTYPE_8, g_Vars.currentplayernum);
		chr->hidden |= CHRHFLAG_REAPED;
		return;
	}

	if (race == RACE_DRCAROLL) {
		struct prop *prop = chr->prop;

		if (g_DrCarollDyingTimer > PALDOWN(120) && chr->voicebox) {
			// Play speech
			u16 phrases[] = {
				SFX_DRCAROLL_SYSTEMS_FAILURE,
				SFX_DRCAROLL_YOU_GO_ON,
				SFX_DRCAROLL_I_CANT_MAKE_IT,
				SFX_DRCAROLL_IM_DYING,
				SFX_DRCAROLL_GOODBYE,
				SFX_DRCAROLL_YOU_WERE_SUPPOSED,
			};

			func0f0939f8(NULL, chr->prop, phrases[random() % 5], -1,
					-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
			chr->voicebox = 0;
		}

		// Change images randomly
		if (chr->act_die.drcarollimagedelay > 0) {
			chr->act_die.drcarollimagedelay -= g_Vars.lvupdate240_60;
		} else {
			chr->act_die.drcarollimagedelay = (random() % PALDOWN(1000)) * 0.01f + 5.0f;
			chr->drcarollimage_left = 1 + (s32)((random() % 400) * 0.01f);
			chr->drcarollimage_right = 1 + (s32)((random() % 400) * 0.01f);
		}

		if (g_DrCarollDyingTimer > PALDOWN(310)) {
			// Explode
			func0f0926bc(prop, 1, 0xffff);
			explosionCreateSimple(prop, &prop->pos, prop->rooms, EXPLOSIONTYPE_8, g_Vars.currentplayernum);
			chrBeginDead(chr);
		} else if (chr->soundtimer > (s32)var80068080) {
			// Play shield damage sound
			chr->soundtimer = 0;
			var80068080 -= 5;
			func0f0939f8(NULL, prop, SFX_SHIELD_DAMAGE, -1,
					-1, 1024, 0, 0, 0, -1, 0, -1, -1, -1, -1);
			sparksCreate(prop->rooms[0], prop, &prop->pos, NULL, 0, SPARKTYPE_01);
		}

		return;
	}

	// Human or Skedar
	// If due, play thud 1 sound
	if (chr->act_die.thudframe1 >= 0 && modelGetCurAnimFrame(model) >= chr->act_die.thudframe1) {
		if (chr->specialdie == 0) {
			func0f0939f8(NULL, chr->prop, thuds[thudindex], -1,
					-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		} else if (chr->specialdie != SPECIALDIE_OVERRAILING) {
			func0f0939f8(NULL, chr->prop, specialdiesounds[chr->specialdie - 1], -1,
					-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		}

		thudindex++;

		if (thudindex > 10) {
			thudindex = 0;
		}

		chr->act_die.thudframe1 = -1;
	}

	// If due, play thud 2 sound
	if (chr->act_die.thudframe2 >= 0 && modelGetCurAnimFrame(model) >= chr->act_die.thudframe2) {
		if (chr->specialdie < 5) {
			func0f0939f8(NULL, chr->prop, SFX_THUD_808E, -1,
					-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		} else {
			func0f0939f8(NULL, chr->prop, thuds[thudindex], -1,
					-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		}

		thudindex++;

		if (thudindex > 10) {
			thudindex = 0;
		}

		chr->act_die.thudframe2 = -1;
	}

	// Check for end of death animation and switch to ACT_DEAD
	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		if (CHRRACE(chr) == RACE_HUMAN && modelGetAnimNum(model) == ANIM_DEATH_STOMACH_LONG) {
			modelSetAnimation(model, ANIM_003C, !modelIsFlipped(model), 50, 0.3, animGetNumFrames(ANIM_003C) - 51.0f);
			modelSetAnimSpeed(model, 0.5, animGetNumFrames(ANIM_003C) - 51.0f);
			return;
		}

		chrBeginDead(chr);
	}

	chrAlertOthersOfInjury(chr, true);
}

u32 var80068408 = 0x808d808e;
u32 var8006840c = 0x808f8090;
u32 var80068410 = 0x80918092;
u32 var80068414 = 0x80938094;
u32 var80068418 = 0x80958096;
u32 var8006841c = 0x80970000;

GLOBAL_ASM(
glabel chrTickDruggedComingUp
/*  f03d7ec:	27bdff58 */ 	addiu	$sp,$sp,-168
/*  f03d7f0:	3c0f8007 */ 	lui	$t7,%hi(var80068408)
/*  f03d7f4:	afbf005c */ 	sw	$ra,0x5c($sp)
/*  f03d7f8:	afbe0058 */ 	sw	$s8,0x58($sp)
/*  f03d7fc:	afb70054 */ 	sw	$s7,0x54($sp)
/*  f03d800:	afb60050 */ 	sw	$s6,0x50($sp)
/*  f03d804:	afb5004c */ 	sw	$s5,0x4c($sp)
/*  f03d808:	afb40048 */ 	sw	$s4,0x48($sp)
/*  f03d80c:	afb30044 */ 	sw	$s3,0x44($sp)
/*  f03d810:	afb20040 */ 	sw	$s2,0x40($sp)
/*  f03d814:	afb1003c */ 	sw	$s1,0x3c($sp)
/*  f03d818:	afb00038 */ 	sw	$s0,0x38($sp)
/*  f03d81c:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*  f03d820:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*  f03d824:	25ef8408 */ 	addiu	$t7,$t7,%lo(var80068408)
/*  f03d828:	8de10000 */ 	lw	$at,0x0($t7)
/*  f03d82c:	27ae0090 */ 	addiu	$t6,$sp,0x90
/*  f03d830:	8de90004 */ 	lw	$t1,0x4($t7)
/*  f03d834:	adc10000 */ 	sw	$at,0x0($t6)
/*  f03d838:	8de10008 */ 	lw	$at,0x8($t7)
/*  f03d83c:	adc90004 */ 	sw	$t1,0x4($t6)
/*  f03d840:	8de9000c */ 	lw	$t1,0xc($t7)
/*  f03d844:	adc10008 */ 	sw	$at,0x8($t6)
/*  f03d848:	8de10010 */ 	lw	$at,0x10($t7)
/*  f03d84c:	adc9000c */ 	sw	$t1,0xc($t6)
/*  f03d850:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x38)
/*  f03d854:	adc10010 */ 	sw	$at,0x10($t6)
/*  f03d858:	95e10014 */ 	lhu	$at,0x14($t7)
/*  f03d85c:	0080f025 */ 	or	$s8,$a0,$zero
/*  f03d860:	00009825 */ 	or	$s3,$zero,$zero
/*  f03d864:	a5c10014 */ 	sh	$at,0x14($t6)
/*  f03d868:	848a002c */ 	lh	$t2,0x2c($a0)
/*  f03d86c:	8d6b9ff8 */ 	lw	$t3,%lo(g_Vars+0x38)($t3)
/*  f03d870:	0000a025 */ 	or	$s4,$zero,$zero
/*  f03d874:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f03d878:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f03d87c:	a48c002c */ 	sh	$t4,0x2c($a0)
/*  f03d880:	848d002c */ 	lh	$t5,0x2c($a0)
/*  f03d884:	59a00074 */ 	blezl	$t5,.L0f03da58
/*  f03d888:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*  f03d88c:	50800005 */ 	beqzl	$a0,.L0f03d8a4
/*  f03d890:	afa00088 */ 	sw	$zero,0x88($sp)
/*  f03d894:	909902fe */ 	lbu	$t9,0x2fe($a0)
/*  f03d898:	10000002 */ 	b	.L0f03d8a4
/*  f03d89c:	afb90088 */ 	sw	$t9,0x88($sp)
/*  f03d8a0:	afa00088 */ 	sw	$zero,0x88($sp)
.L0f03d8a4:
/*  f03d8a4:	8fd70020 */ 	lw	$s7,0x20($s8)
/*  f03d8a8:	0fc08946 */ 	jal	chrUncloak
/*  f03d8ac:	03c02025 */ 	or	$a0,$s8,$zero
/*  f03d8b0:	2418001e */ 	addiu	$t8,$zero,0x1e
/*  f03d8b4:	3c014180 */ 	lui	$at,0x4180
/*  f03d8b8:	a3d80007 */ 	sb	$t8,0x7($s8)
/*  f03d8bc:	3c158006 */ 	lui	$s5,%hi(g_AnimTablesByRace)
/*  f03d8c0:	4481b000 */ 	mtc1	$at,$f22
/*  f03d8c4:	4480a000 */ 	mtc1	$zero,$f20
/*  f03d8c8:	26b552b8 */ 	addiu	$s5,$s5,%lo(g_AnimTablesByRace)
/*  f03d8cc:	8fa20088 */ 	lw	$v0,0x88($sp)
/*  f03d8d0:	24160014 */ 	addiu	$s6,$zero,0x14
.L0f03d8d4:
/*  f03d8d4:	06600033 */ 	bltz	$s3,.L0f03d9a4
/*  f03d8d8:	00000000 */ 	nop
/*  f03d8dc:	02760019 */ 	multu	$s3,$s6
/*  f03d8e0:	00027080 */ 	sll	$t6,$v0,0x2
/*  f03d8e4:	02ae8821 */ 	addu	$s1,$s5,$t6
/*  f03d8e8:	8e2f0000 */ 	lw	$t7,0x0($s1)
/*  f03d8ec:	00009012 */ 	mflo	$s2
/*  f03d8f0:	01f21821 */ 	addu	$v1,$t7,$s2
/*  f03d8f4:	8c690004 */ 	lw	$t1,0x4($v1)
/*  f03d8f8:	1120002a */ 	beqz	$t1,.L0f03d9a4
/*  f03d8fc:	00000000 */ 	nop
/*  f03d900:	8c6a000c */ 	lw	$t2,0xc($v1)
/*  f03d904:	19400027 */ 	blez	$t2,.L0f03d9a4
/*  f03d908:	00000000 */ 	nop
/*  f03d90c:	0c004b70 */ 	jal	random
/*  f03d910:	24140001 */ 	addiu	$s4,$zero,0x1
/*  f03d914:	8e2b0000 */ 	lw	$t3,0x0($s1)
/*  f03d918:	4407a000 */ 	mfc1	$a3,$f20
/*  f03d91c:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f03d920:	01721821 */ 	addu	$v1,$t3,$s2
/*  f03d924:	8c6c000c */ 	lw	$t4,0xc($v1)
/*  f03d928:	8c6d0004 */ 	lw	$t5,0x4($v1)
/*  f03d92c:	02e02025 */ 	or	$a0,$s7,$zero
/*  f03d930:	004c001b */ 	divu	$zero,$v0,$t4
/*  f03d934:	00004010 */ 	mfhi	$t0
/*  f03d938:	0008c8c0 */ 	sll	$t9,$t0,0x3
/*  f03d93c:	0328c823 */ 	subu	$t9,$t9,$t0
/*  f03d940:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f03d944:	01b98021 */ 	addu	$s0,$t5,$t9
/*  f03d948:	c6040014 */ 	lwc1	$f4,0x14($s0)
/*  f03d94c:	15800002 */ 	bnez	$t4,.L0f03d958
/*  f03d950:	00000000 */ 	nop
/*  f03d954:	0007000d */ 	break	0x7
.L0f03d958:
/*  f03d958:	e7c40030 */ 	swc1	$f4,0x30($s8)
/*  f03d95c:	c6060018 */ 	lwc1	$f6,0x18($s0)
/*  f03d960:	e7c60034 */ 	swc1	$f6,0x34($s8)
/*  f03d964:	c608000c */ 	lwc1	$f8,0xc($s0)
/*  f03d968:	8e060004 */ 	lw	$a2,0x4($s0)
/*  f03d96c:	86050000 */ 	lh	$a1,0x0($s0)
/*  f03d970:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f03d974:	e7b60014 */ 	swc1	$f22,0x14($sp)
/*  f03d978:	0c0076ff */ 	jal	modelSetAnimationWithMerge
/*  f03d97c:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f03d980:	c6000008 */ 	lwc1	$f0,0x8($s0)
/*  f03d984:	4600a03e */ 	c.le.s	$f20,$f0
/*  f03d988:	00000000 */ 	nop
/*  f03d98c:	45020005 */ 	bc1fl	.L0f03d9a4
/*  f03d990:	8fa20088 */ 	lw	$v0,0x88($sp)
/*  f03d994:	44050000 */ 	mfc1	$a1,$f0
/*  f03d998:	0c007787 */ 	jal	modelSetAnimEndFrame
/*  f03d99c:	02e02025 */ 	or	$a0,$s7,$zero
/*  f03d9a0:	8fa20088 */ 	lw	$v0,0x88($sp)
.L0f03d9a4:
/*  f03d9a4:	1680000d */ 	bnez	$s4,.L0f03d9dc
/*  f03d9a8:	00000000 */ 	nop
/*  f03d9ac:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f03d9b0:	02760019 */ 	multu	$s3,$s6
/*  f03d9b4:	00027080 */ 	sll	$t6,$v0,0x2
/*  f03d9b8:	02ae7821 */ 	addu	$t7,$s5,$t6
/*  f03d9bc:	8de90000 */ 	lw	$t1,0x0($t7)
/*  f03d9c0:	2401ffff */ 	addiu	$at,$zero,-1
/*  f03d9c4:	00005012 */ 	mflo	$t2
/*  f03d9c8:	012a5821 */ 	addu	$t3,$t1,$t2
/*  f03d9cc:	8d6c0000 */ 	lw	$t4,0x0($t3)
/*  f03d9d0:	15810002 */ 	bne	$t4,$at,.L0f03d9dc
/*  f03d9d4:	00000000 */ 	nop
/*  f03d9d8:	24140001 */ 	addiu	$s4,$zero,0x1
.L0f03d9dc:
/*  f03d9dc:	1280ffbd */ 	beqz	$s4,.L0f03d8d4
/*  f03d9e0:	00000000 */ 	nop
/*  f03d9e4:	8fc40170 */ 	lw	$a0,0x170($s8)
/*  f03d9e8:	5080000c */ 	beqzl	$a0,.L0f03da1c
/*  f03d9ec:	8fc40174 */ 	lw	$a0,0x174($s8)
/*  f03d9f0:	8c8d0004 */ 	lw	$t5,0x4($a0)
/*  f03d9f4:	8db90008 */ 	lw	$t9,0x8($t5)
/*  f03d9f8:	33382000 */ 	andi	$t8,$t9,0x2000
/*  f03d9fc:	57000007 */ 	bnezl	$t8,.L0f03da1c
/*  f03da00:	8fc40174 */ 	lw	$a0,0x174($s8)
/*  f03da04:	0fc20a59 */ 	jal	objSetDropped
/*  f03da08:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f03da0c:	8fce0014 */ 	lw	$t6,0x14($s8)
/*  f03da10:	35cf0001 */ 	ori	$t7,$t6,0x1
/*  f03da14:	afcf0014 */ 	sw	$t7,0x14($s8)
/*  f03da18:	8fc40174 */ 	lw	$a0,0x174($s8)
.L0f03da1c:
/*  f03da1c:	1080000b */ 	beqz	$a0,.L0f03da4c
/*  f03da20:	00000000 */ 	nop
/*  f03da24:	8c890004 */ 	lw	$t1,0x4($a0)
/*  f03da28:	8d2a0008 */ 	lw	$t2,0x8($t1)
/*  f03da2c:	314b2000 */ 	andi	$t3,$t2,0x2000
/*  f03da30:	15600006 */ 	bnez	$t3,.L0f03da4c
/*  f03da34:	00000000 */ 	nop
/*  f03da38:	0fc20a59 */ 	jal	objSetDropped
/*  f03da3c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f03da40:	8fcc0014 */ 	lw	$t4,0x14($s8)
/*  f03da44:	358d0001 */ 	ori	$t5,$t4,0x1
/*  f03da48:	afcd0014 */ 	sw	$t5,0x14($s8)
.L0f03da4c:
/*  f03da4c:	0fc09149 */ 	jal	chrDropConcealedItems
/*  f03da50:	03c02025 */ 	or	$a0,$s8,$zero
/*  f03da54:	8fbf005c */ 	lw	$ra,0x5c($sp)
.L0f03da58:
/*  f03da58:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*  f03da5c:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*  f03da60:	8fb00038 */ 	lw	$s0,0x38($sp)
/*  f03da64:	8fb1003c */ 	lw	$s1,0x3c($sp)
/*  f03da68:	8fb20040 */ 	lw	$s2,0x40($sp)
/*  f03da6c:	8fb30044 */ 	lw	$s3,0x44($sp)
/*  f03da70:	8fb40048 */ 	lw	$s4,0x48($sp)
/*  f03da74:	8fb5004c */ 	lw	$s5,0x4c($sp)
/*  f03da78:	8fb60050 */ 	lw	$s6,0x50($sp)
/*  f03da7c:	8fb70054 */ 	lw	$s7,0x54($sp)
/*  f03da80:	8fbe0058 */ 	lw	$s8,0x58($sp)
/*  f03da84:	03e00008 */ 	jr	$ra
/*  f03da88:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
);

// Mismatch: regalloc
//void chrTickDruggedComingUp(struct chrdata *chr)
//{
//	u16 thuds[] = {
//		SFX_THUD_808D,
//		SFX_THUD_808E,
//		SFX_THUD_808F,
//		SFX_THUD_8090,
//		SFX_THUD_8091,
//		SFX_THUD_8092,
//		SFX_THUD_8093,
//		SFX_THUD_8094,
//		SFX_THUD_8095,
//		SFX_THUD_8096,
//		SFX_THUD_8097,
//	};
//
//	u32 stack;
//
//	chr->act_druggedcomingup.timer60 += g_Vars.lvupdate240_60;
//
//	if (chr->act_druggedcomingup.timer60 > 0) {
//		s32 race = CHRRACE(chr);
//		struct model *model = chr->model;
//		s32 i = 0;
//		bool done = false;
//		struct prop *weapon;
//
//		chrUncloak(chr, true);
//
//		chr->actiontype = ACT_DRUGGEDDROP;
//
//		while (!done) {
//			if (i >= 0
//					&& g_AnimTablesByRace[race][i].deathanims != NULL
//					&& g_AnimTablesByRace[race][i].deathanimcount > 0) {
//				struct animtablerow *row = &g_AnimTablesByRace[race][i].deathanims[random() % g_AnimTablesByRace[race][i].deathanimcount];
//
//				chr->act_die.thudframe1 = row->thudframe1;
//				chr->act_die.thudframe2 = row->thudframe2;
//
//				modelSetAnimationWithMerge(model, row->animnum, row->flip, 0, row->speed, 16, true);
//
//				if (row->endframe >= 0) {
//					modelSetAnimEndFrame(model, row->endframe);
//				}
//
//				done = true;
//			}
//
//			if (!done) {
//				i++;
//
//				if (g_AnimTablesByRace[race][i].hitpart == -1) {
//					done = true;
//				}
//			}
//		}
//
//		weapon = chr->weapons_held[HAND_RIGHT];
//
//		if (weapon && (weapon->obj->flags & OBJFLAG_AIUNDROPPABLE) == 0) {
//			objSetDropped(weapon, DROPTYPE_DEFAULT);
//			chr->hidden |= CHRHFLAG_00000001;
//		}
//
//		weapon = chr->weapons_held[HAND_LEFT];
//
//		if (weapon && (weapon->obj->flags & OBJFLAG_AIUNDROPPABLE) == 0) {
//			objSetDropped(weapon, DROPTYPE_DEFAULT);
//			chr->hidden |= CHRHFLAG_00000001;
//		}
//
//		chrDropConcealedItems(chr);
//	}
//}

void chrTickDruggedDrop(struct chrdata *chr)
{
	struct model *model = chr->model;

	u16 thuds[11] = {
		SFX_THUD_808D,
		SFX_THUD_808E,
		SFX_THUD_808F,
		SFX_THUD_8090,
		SFX_THUD_8091,
		SFX_THUD_8092,
		SFX_THUD_8093,
		SFX_THUD_8094,
		SFX_THUD_8095,
		SFX_THUD_8096,
		SFX_THUD_8097,
	};

	static s32 thudindex = 0;

	// If due, play thud 1 sound
	if (chr->act_die.thudframe1 >= 0 && modelGetCurAnimFrame(model) >= chr->act_die.thudframe1) {
		func0f0939f8(NULL, chr->prop, thuds[thudindex], -1,
				-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);

		thudindex++;

		if (thudindex > 10) {
			thudindex = 0;
		}

		chr->act_die.thudframe1 = -1;
	}

	// If due, play thud 2 sound
	if (chr->act_die.thudframe2 >= 0 && modelGetCurAnimFrame(model) >= chr->act_die.thudframe2) {
		func0f0939f8(NULL, chr->prop, thuds[thudindex], -1,
				-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);

		thudindex++;

		if (thudindex > 10) {
			thudindex = 0;
		}

		chr->act_die.thudframe2 = -1;
	}

	// If falling animation finished, assign ACT_DRUGGEDKO
	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		chr->actiontype = ACT_DRUGGEDKO;
		chr->act_dead.fadetimer60 = chr->aibot ? 0 : -1;
		chr->act_dead.fadenow = false;
		chr->act_dead.fadewheninvis = false;
		chr->act_dead.invistimer60 = 0;
		chr->act_dead.notifychrindex = 0;
		chr->sleep = 0;
	}

	chrAlertOthersOfInjury(chr, true);
}

void chrTickDruggedKo(struct chrdata *chr)
{
	bool reap = false;

	// If fade is active, handle it
	if (chr->act_dead.fadetimer60 >= 0) {
		chr->act_dead.fadetimer60 += g_Vars.lvupdate240_60;

		if (chr->act_dead.fadetimer60 >= PALDOWN(90)) {
			reap = true;
		} else {
			chr->fadealpha = (PALDOWN(90) - chr->act_dead.fadetimer60) * 255 / PALDOWN(90);
		}
	} else if ((chr->chrflags & CHRCFLAG_KEEPCORPSEKO) == 0) {
		if (chr->act_dead.fadenow) {
			chr->act_dead.fadetimer60 = 0;
		}

		if (chr->prop->flags & PROPFLAG_ONANYSCREENPREVTICK) {
			chr->act_dead.invistimer60 = 0;
		} else {
			chr->act_dead.invistimer60 += g_Vars.lvupdate240_60;
		}

		if (chr->act_dead.fadewheninvis && chr->act_dead.invistimer60 >= PALDOWN(120)) {
			reap = true;
		}
	}

	if (reap) {
		chr->fadealpha = 0;
		chr->hidden |= CHRHFLAG_REAPED;
		chrDropItemsForOwnerReap(chr);
	}
}

void chrTickArgh(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		chrRecordLastSeeTargetTime(chr);

		if (CHRRACE(chr) == RACE_HUMAN && modelGetAnimNum(model) == ANIM_DEATH_STOMACH_LONG) {
			func0f02ed28(chr, 26);
		} else {
			if (chr->race == RACE_DRCAROLL) {
				chr->drcarollimage_left = DRCAROLLIMAGE_EYESDEFAULT;
				chr->drcarollimage_right = DRCAROLLIMAGE_EYESDEFAULT;
			}

			chrStop(chr);
		}
	}

	chrAlertOthersOfInjury(chr, false);
}

void chrTickPreArgh(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		struct coord dir;
		dir.x = chr->act_preargh.dir.x;
		dir.y = chr->act_preargh.dir.y;
		dir.z = chr->act_preargh.dir.z;

		chrReactToDamage(chr, &dir,
				chr->act_preargh.relshotdir,
				chr->act_preargh.hitpart,
				&chr->act_preargh.gset,
				chr->act_preargh.aplayernum);
	}
}

void chrTickSidestep(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrSidestepChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		chrRecordLastSeeTargetTime(chr);
		func0f02ed28(chr, 10);
	}
}

void chrTickJumpOut(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrJumpOutChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		chrRecordLastSeeTargetTime(chr);
		chrStop(chr);
	}
}

void chrTickTest(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		chrStand(chr);
	}
}

void chrTickStartAlarm(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrStartAlarmChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (modelGetCurAnimFrame(model) >= 60) {
		alarmActivate();
	}

	if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
		chrStop(chr);
	}
}

void chrTickSurprised(struct chrdata *chr)
{
	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrSurprisedChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (CHRRACE(chr) == RACE_HUMAN) {
		struct model *model = chr->model;

		if (modelGetCurAnimFrame(model) >= modelGetAnimEndFrame(model)) {
			if (modelGetAnimNum(model) == ANIM_SURRENDER_002E) {
				func0f02ed28(chr, 26);
			} else if (modelGetAnimNum(model) == ANIM_003F) {
				func0f02ed28(chr, 26);
			} else {
				chrStop(chr);
			}
		}
	}
}

void chrCreateFireslot(struct chrdata *chr, s32 handnum, bool withsound, bool withbeam, struct coord *from, struct coord *to)
{
	struct prop *weaponprop;
	struct weaponobj *weapon;
	s32 weaponnum;
	bool playsound = false;
	u8 duration;
	u16 soundnum;

	weaponprop = chrGetHeldProp(chr, handnum);

	if (weaponprop) {
		weapon = weaponprop->weapon;
		weaponnum = weapon->weaponnum;
		duration = gsetGetFireslotDuration((struct gset *) &weapon->weaponnum);
		soundnum = gsetGetSingleShootSound((struct gset *) &weapon->weaponnum);

		if (chr->fireslots[handnum] < 0) {
			chr->fireslots[handnum] = bgunAllocateFireslot();
		}

		if (chr->fireslots[handnum] >= 0) {
			struct fireslot *fireslot = &g_Fireslots[chr->fireslots[handnum]];

			if (withsound) {
				if (duration > 0) {
#if VERSION >= VERSION_NTSC_1_0
					if (chr->hidden2 & CHRH2FLAG_0020)
#else
					if (chr->hidden & CHRHFLAG_00000080)
#endif
					{
						playsound = false;
					} else {
						if (g_Vars.lvframe60 > fireslot->endlvframe) {
							playsound = true;
						} else {
							playsound = false;
						}
					}
				} else {
					playsound = true;
				}
			}

			if (playsound) {
#if VERSION >= VERSION_NTSC_1_0
				func0f0939f8(NULL, chr->prop, soundnum, -1, -1, 0x400, 4, 0x11, NULL, -1, NULL, -1, -1, -1, -1);
				fireslot->endlvframe = (u32)g_Vars.lvframe60 + duration;
				chr->hidden2 |= CHRH2FLAG_0020;
#else
				func0f0939f8(NULL, chr->prop, soundnum, -1, -1, 0x400, 4, 0, NULL, -1, NULL, -1, -1, -1, -1);
				fireslot->endlvframe = (u32)g_Vars.lvframe60 + duration;
				chr->hidden |= CHRHFLAG_00000080;

				if (chr);
#endif
			}

			if (withbeam) {
				beamCreate(&fireslot->beam, weaponnum, from, to);
			}
		}
	}
}

/**
 * Returns the chr's turn angle difference to 360 degrees, in radians.
 */
f32 chrGetInverseTheta(struct chrdata *chr)
{
	if (chr->aibot) {
		return chr->aibot->unk0b0;
	}

	if (chr->model == NULL && chr->prop && chr->prop->type == PROPTYPE_PLAYER) {
		struct player *player = g_Vars.players[propGetPlayerNum(chr->prop)];
		f32 angle = (360.0f - player->vv_theta) * 0.017450513318181f;

		if (angle >= M_BADTAU) {
			angle -= M_BADTAU;
		} else if (angle < 0) {
			angle += M_BADTAU;
		}

		return angle;
	}

	return model0001ae44(chr->model);
}

void chrSetLookAngle(struct chrdata *chr, f32 angle)
{
	if (chr->aibot) {
		chr->aibot->unk0b0 = angle;
	} else {
		model0001ae90(chr->model, angle);
	}
}

f32 func0f03e578(struct chrdata *chr)
{
	if (chr->aibot) {
		return chr->aibot->unk0a4;
	}

	return model0001ae44(chr->model);
}

void func0f03e5b0(struct chrdata *chr, f32 arg1)
{
	if (chr->aibot) {
		chr->aibot->unk0a4 = arg1;
	} else {
		model0001ae90(chr->model, arg1);
	}
}

f32 chrGetAimAngle(struct chrdata *chr)
{
	f32 angle = chrGetInverseTheta(chr) + chr->aimsideback;
	f32 offset = 0;

	if (angle >= M_BADTAU) {
		angle -= M_BADTAU;
	} else if (angle < 0) {
		angle += M_BADTAU;
	}

	if (chr->aibot) {
		if (chr->aibot->unk068) {
			// empty
		}
	} else if (chr->actiontype == ACT_ATTACK
			|| chr->actiontype == ACT_ATTACKROLL
			|| chr->actiontype == ACT_BOT_ATTACKSTAND
			|| chr->actiontype == ACT_BOT_ATTACKKNEEL
			|| chr->actiontype == ACT_BOT_ATTACKSTRAFE) {
		offset = chr->act_attack.animcfg->unk0c;
	} else if (chr->prop->type == PROPTYPE_PLAYER) {
		offset += g_Vars.players[propGetPlayerNum(chr->prop)]->angleoffset;
	}

	if (offset) {
		if (chr->model->anim->flip) {
			offset = M_BADTAU - offset;
		}

		angle += offset;

		if (angle >= M_BADTAU) {
			angle -= M_BADTAU;
		} else if (angle < M_BADTAU) {
			angle += M_BADTAU;
		}
	}

	return angle;
}

f32 func0f03e754(struct chrdata *chr)
{
	f32 sum = chr->aimuprshoulder + chr->aimupback;

	if (sum < 0) {
		sum += M_BADTAU;
	}

	return sum;
}

/**
 * Turn the chr slightly towards their target.
 */
s32 chrTurn(struct chrdata *chr, s32 turning, f32 endanimframe, f32 speed, f32 toleranceangle)
{
	if (turning != TURNSTATE_OFF) {
		struct model *model = chr->model;
		f32 curframe = modelGetCurAnimFrame(model);
		u32 stack;
		f32 finalangle = chrGetInverseTheta(chr);
		f32 remainingangle;
		f32 increment = M_BADTAU / 100.0f * speed * g_Vars.lvupdate240f * model->anim->playspeed;

		if (chr->aibot) {
			struct prop *target = chrGetTargetProp(chr);
			remainingangle = chrGetAngleToPos(chr, &target->pos);
		} else if (chr->actiontype == ACT_ATTACK
				|| chr->actiontype == ACT_BOT_ATTACKSTAND
				|| chr->actiontype == ACT_BOT_ATTACKKNEEL
				|| chr->actiontype == ACT_BOT_ATTACKSTRAFE) {
			remainingangle = chrGetAttackEntityRelativeAngle(chr, chr->act_attack.flags, chr->act_attack.entityid);
		} else if (chr->actiontype == ACT_STAND) {
			remainingangle = chrGetAttackEntityRelativeAngle(chr, chr->act_stand.flags, chr->act_stand.entityid);
		} else if (chr->actiontype == ACT_THROWGRENADE) {
			remainingangle = chrGetAttackEntityRelativeAngle(chr, chr->act_throwgrenade.flags, chr->act_throwgrenade.entityid);
		} else {
			struct prop *target = chrGetTargetProp(chr);
			remainingangle = chrGetAngleToPos(chr, &target->pos);
		}

		remainingangle -= toleranceangle;

		if (remainingangle < 0) {
			remainingangle += M_BADTAU;
		}

		if (increment > remainingangle || M_BADTAU - increment < remainingangle) {
			// Close enough to stop
			finalangle += remainingangle;

			if (finalangle >= M_BADTAU) {
				finalangle -= M_BADTAU;
			}

			chrSetLookAngle(chr, finalangle);
			turning = TURNSTATE_ONTARGET;
		} else if (remainingangle < M_PI) {
			// Turning in one direction
			finalangle += increment;

			if (finalangle >= M_BADTAU) {
				finalangle -= M_BADTAU;
			}

			chrSetLookAngle(chr, finalangle);
		} else {
			// Turning in the other direction
			finalangle -= increment;

			if (finalangle < 0) {
				finalangle += M_BADTAU;
			}

			chrSetLookAngle(chr, finalangle);
		}

		if (curframe >= endanimframe) {
			turning = TURNSTATE_OFF;
		}
	}

	return turning;
}

GLOBAL_ASM(
glabel func0f03e9f4
.late_rodata
glabel var7f1a8f44
.word 0x3d4ccccd
glabel var7f1a8f48
.word 0x3ecccccd
glabel var7f1a8f4c
.word 0x481c4000
glabel var7f1a8f50
.word 0x3dcccccd
glabel var7f1a8f54
.word 0x3f0ccccd
glabel var7f1a8f58
.word 0x3dcccccd
glabel var7f1a8f5c
.word 0x3e19999a
glabel var7f1a8f60
.word 0x3dcccccd
glabel var7f1a8f64
.word 0x3d4ccccd
glabel var7f1a8f68
.word 0x3ccccccd
glabel var7f1a8f6c
.word 0x49742400
glabel var7f1a8f70
.word 0x3dcccccd
glabel var7f1a8f74
.word 0x3d4ccccd
glabel var7f1a8f78
.word 0x3f0ccccd
glabel var7f1a8f7c
.word 0x3d4ccccd
glabel var7f1a8f80
.word 0x3dcccccd
glabel var7f1a8f84
.word 0x3f0ccccd
glabel var7f1a8f88
.word 0x3dcccccd
glabel var7f1a8f8c
.word 0x3e19999a
glabel var7f1a8f90
.word 0x3dcccccd
glabel var7f1a8f94
.word 0x3d4ccccd
glabel var7f1a8f98
.word 0x40490fdb
glabel var7f1a8f9c
.word 0x40c907a9
glabel var7f1a8fa0
.word 0x49742400
glabel var7f1a8fa4
.word 0x40c907a9
glabel var7f1a8fa8
.word 0x40c907a9
glabel var7f1a8fac
.word 0x40c907a9
glabel var7f1a8fb0
.word 0x40c907a9
glabel var7f1a8fb4
.word 0x3dd66e92
glabel var7f1a8fb8
.word 0x40c907a9
glabel var7f1a8fbc
.word 0x40c907a9
glabel var7f1a8fc0
.word 0x40c907a9
glabel var7f1a8fc4
.word 0x40490fdb
glabel var7f1a8fc8
.word 0x40c907a9
.text
/*  f03e9f4:	27bdfe70 */ 	addiu	$sp,$sp,-400
/*  f03e9f8:	44808000 */ 	mtc1	$zero,$f16
/*  f03e9fc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f03ea00:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f03ea04:	afa50194 */ 	sw	$a1,0x194($sp)
/*  f03ea08:	afa60198 */ 	sw	$a2,0x198($sp)
/*  f03ea0c:	afa7019c */ 	sw	$a3,0x19c($sp)
/*  f03ea10:	afae017c */ 	sw	$t6,0x17c($sp)
/*  f03ea14:	e7b0018c */ 	swc1	$f16,0x18c($sp)
/*  f03ea18:	8c8f02d4 */ 	lw	$t7,0x2d4($a0)
/*  f03ea1c:	24080200 */ 	addiu	$t0,$zero,0x200
/*  f03ea20:	00001825 */ 	or	$v1,$zero,$zero
/*  f03ea24:	55e00014 */ 	bnezl	$t7,.L0f03ea78
/*  f03ea28:	31180002 */ 	andi	$t8,$t0,0x2
/*  f03ea2c:	80820007 */ 	lb	$v0,0x7($a0)
/*  f03ea30:	24010008 */ 	addiu	$at,$zero,0x8
/*  f03ea34:	10410007 */ 	beq	$v0,$at,.L0f03ea54
/*  f03ea38:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f03ea3c:	10410005 */ 	beq	$v0,$at,.L0f03ea54
/*  f03ea40:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f03ea44:	10410003 */ 	beq	$v0,$at,.L0f03ea54
/*  f03ea48:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f03ea4c:	54410005 */ 	bnel	$v0,$at,.L0f03ea64
/*  f03ea50:	24010001 */ 	addiu	$at,$zero,0x1
.L0f03ea54:
/*  f03ea54:	8c88004c */ 	lw	$t0,0x4c($a0)
/*  f03ea58:	10000006 */ 	b	.L0f03ea74
/*  f03ea5c:	8c830050 */ 	lw	$v1,0x50($a0)
/*  f03ea60:	24010001 */ 	addiu	$at,$zero,0x1
.L0f03ea64:
/*  f03ea64:	54410004 */ 	bnel	$v0,$at,.L0f03ea78
/*  f03ea68:	31180002 */ 	andi	$t8,$t0,0x2
/*  f03ea6c:	8c880030 */ 	lw	$t0,0x30($a0)
/*  f03ea70:	8c830034 */ 	lw	$v1,0x34($a0)
.L0f03ea74:
/*  f03ea74:	31180002 */ 	andi	$t8,$t0,0x2
.L0f03ea78:
/*  f03ea78:	1700032d */ 	bnez	$t8,.L0f03f730
/*  f03ea7c:	afa40190 */ 	sw	$a0,0x190($sp)
/*  f03ea80:	8c99001c */ 	lw	$t9,0x1c($a0)
/*  f03ea84:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03ea88:	afa80184 */ 	sw	$t0,0x184($sp)
/*  f03ea8c:	afa40190 */ 	sw	$a0,0x190($sp)
/*  f03ea90:	afa30180 */ 	sw	$v1,0x180($sp)
/*  f03ea94:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f03ea98:	afb9016c */ 	sw	$t9,0x16c($sp)
/*  f03ea9c:	8fa3016c */ 	lw	$v1,0x16c($sp)
/*  f03eaa0:	afa20168 */ 	sw	$v0,0x168($sp)
/*  f03eaa4:	c4440008 */ 	lwc1	$f4,0x8($v0)
/*  f03eaa8:	c4660008 */ 	lwc1	$f6,0x8($v1)
/*  f03eaac:	8fa60190 */ 	lw	$a2,0x190($sp)
/*  f03eab0:	8fac0184 */ 	lw	$t4,0x184($sp)
/*  f03eab4:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f03eab8:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03eabc:	318d0200 */ 	andi	$t5,$t4,0x200
/*  f03eac0:	e7a80178 */ 	swc1	$f8,0x178($sp)
/*  f03eac4:	c44a000c */ 	lwc1	$f10,0xc($v0)
/*  f03eac8:	c472000c */ 	lwc1	$f18,0xc($v1)
/*  f03eacc:	46125101 */ 	sub.s	$f4,$f10,$f18
/*  f03ead0:	c7b20178 */ 	lwc1	$f18,0x178($sp)
/*  f03ead4:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f03ead8:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f03eadc:	c4680010 */ 	lwc1	$f8,0x10($v1)
/*  f03eae0:	46129102 */ 	mul.s	$f4,$f18,$f18
/*  f03eae4:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f03eae8:	c7a60174 */ 	lwc1	$f6,0x174($sp)
/*  f03eaec:	46063202 */ 	mul.s	$f8,$f6,$f6
/*  f03eaf0:	e7aa0170 */ 	swc1	$f10,0x170($sp)
/*  f03eaf4:	c7b20170 */ 	lwc1	$f18,0x170($sp)
/*  f03eaf8:	46129182 */ 	mul.s	$f6,$f18,$f18
/*  f03eafc:	46082280 */ 	add.s	$f10,$f4,$f8
/*  f03eb00:	46065000 */ 	add.s	$f0,$f10,$f6
/*  f03eb04:	e7a00164 */ 	swc1	$f0,0x164($sp)
/*  f03eb08:	8cc902d4 */ 	lw	$t1,0x2d4($a2)
/*  f03eb0c:	11200006 */ 	beqz	$t1,.L0f03eb28
/*  f03eb10:	00000000 */ 	nop
/*  f03eb14:	8faa0184 */ 	lw	$t2,0x184($sp)
/*  f03eb18:	afa00160 */ 	sw	$zero,0x160($sp)
/*  f03eb1c:	314b0200 */ 	andi	$t3,$t2,0x200
/*  f03eb20:	10000013 */ 	b	.L0f03eb70
/*  f03eb24:	afab0020 */ 	sw	$t3,0x20($sp)
.L0f03eb28:
/*  f03eb28:	11a0000f */ 	beqz	$t5,.L0f03eb68
/*  f03eb2c:	afad0020 */ 	sw	$t5,0x20($sp)
/*  f03eb30:	318e0040 */ 	andi	$t6,$t4,0x40
/*  f03eb34:	11c00004 */ 	beqz	$t6,.L0f03eb48
/*  f03eb38:	00c02025 */ 	or	$a0,$a2,$zero
/*  f03eb3c:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f03eb40:	1000000b */ 	b	.L0f03eb70
/*  f03eb44:	afaf0160 */ 	sw	$t7,0x160($sp)
.L0f03eb48:
/*  f03eb48:	e7a00024 */ 	swc1	$f0,0x24($sp)
/*  f03eb4c:	0fc0e4da */ 	jal	chrCanSeeTarget
/*  f03eb50:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03eb54:	c7a00024 */ 	lwc1	$f0,0x24($sp)
/*  f03eb58:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03eb5c:	afa20160 */ 	sw	$v0,0x160($sp)
/*  f03eb60:	10000003 */ 	b	.L0f03eb70
/*  f03eb64:	8fa60190 */ 	lw	$a2,0x190($sp)
.L0f03eb68:
/*  f03eb68:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f03eb6c:	afb80160 */ 	sw	$t8,0x160($sp)
.L0f03eb70:
/*  f03eb70:	8fb90020 */ 	lw	$t9,0x20($sp)
/*  f03eb74:	8fa90168 */ 	lw	$t1,0x168($sp)
/*  f03eb78:	27a50134 */ 	addiu	$a1,$sp,0x134
/*  f03eb7c:	5320016c */ 	beqzl	$t9,.L0f03f130
/*  f03eb80:	8cc40020 */ 	lw	$a0,0x20($a2)
/*  f03eb84:	912a0000 */ 	lbu	$t2,0x0($t1)
/*  f03eb88:	24010006 */ 	addiu	$at,$zero,0x6
/*  f03eb8c:	01202025 */ 	or	$a0,$t1,$zero
/*  f03eb90:	55410167 */ 	bnel	$t2,$at,.L0f03f130
/*  f03eb94:	8cc40020 */ 	lw	$a0,0x20($a2)
/*  f03eb98:	e7a00024 */ 	swc1	$f0,0x24($sp)
/*  f03eb9c:	0fc4a25f */ 	jal	propGetPlayerNum
/*  f03eba0:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03eba4:	8fa40168 */ 	lw	$a0,0x168($sp)
/*  f03eba8:	00025880 */ 	sll	$t3,$v0,0x2
/*  f03ebac:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x64)
/*  f03ebb0:	01ab6821 */ 	addu	$t5,$t5,$t3
/*  f03ebb4:	8dada024 */ 	lw	$t5,%lo(g_Vars+0x64)($t5)
/*  f03ebb8:	c4840008 */ 	lwc1	$f4,0x8($a0)
/*  f03ebbc:	8fa30190 */ 	lw	$v1,0x190($sp)
/*  f03ebc0:	c5a219c4 */ 	lwc1	$f2,0x19c4($t5)
/*  f03ebc4:	e7a40154 */ 	swc1	$f4,0x154($sp)
/*  f03ebc8:	c488000c */ 	lwc1	$f8,0xc($a0)
/*  f03ebcc:	c7a00024 */ 	lwc1	$f0,0x24($sp)
/*  f03ebd0:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03ebd4:	e7a80158 */ 	swc1	$f8,0x158($sp)
/*  f03ebd8:	c4920010 */ 	lwc1	$f18,0x10($a0)
/*  f03ebdc:	e7b2015c */ 	swc1	$f18,0x15c($sp)
/*  f03ebe0:	8c6c02d4 */ 	lw	$t4,0x2d4($v1)
/*  f03ebe4:	5180001e */ 	beqzl	$t4,.L0f03ec60
/*  f03ebe8:	8c6e0018 */ 	lw	$t6,0x18($v1)
/*  f03ebec:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03ebf0:	0c004b70 */ 	jal	random
/*  f03ebf4:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03ebf8:	44825000 */ 	mtc1	$v0,$f10
/*  f03ebfc:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03ec00:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03ec04:	04410005 */ 	bgez	$v0,.L0f03ec1c
/*  f03ec08:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f03ec0c:	3c014f80 */ 	lui	$at,0x4f80
/*  f03ec10:	44812000 */ 	mtc1	$at,$f4
/*  f03ec14:	00000000 */ 	nop
/*  f03ec18:	46043180 */ 	add.s	$f6,$f6,$f4
.L0f03ec1c:
/*  f03ec1c:	3c012f80 */ 	lui	$at,0x2f80
/*  f03ec20:	44814000 */ 	mtc1	$at,$f8
/*  f03ec24:	3c017f1b */ 	lui	$at,%hi(var7f1a8f44)
/*  f03ec28:	c42a8f44 */ 	lwc1	$f10,%lo(var7f1a8f44)($at)
/*  f03ec2c:	46083482 */ 	mul.s	$f18,$f6,$f8
/*  f03ec30:	c7a601a0 */ 	lwc1	$f6,0x1a0($sp)
/*  f03ec34:	3c017f1b */ 	lui	$at,%hi(var7f1a8f48)
/*  f03ec38:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f03ec3c:	c42a8f48 */ 	lwc1	$f10,%lo(var7f1a8f48)($at)
/*  f03ec40:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f03ec44:	c7a60174 */ 	lwc1	$f6,0x174($sp)
/*  f03ec48:	46085480 */ 	add.s	$f18,$f10,$f8
/*  f03ec4c:	46121102 */ 	mul.s	$f4,$f2,$f18
/*  f03ec50:	46043281 */ 	sub.s	$f10,$f6,$f4
/*  f03ec54:	1000014c */ 	b	.L0f03f188
/*  f03ec58:	e7aa0174 */ 	swc1	$f10,0x174($sp)
/*  f03ec5c:	8c6e0018 */ 	lw	$t6,0x18($v1)
.L0f03ec60:
/*  f03ec60:	3c017f1b */ 	lui	$at,%hi(var7f1a8f4c)
/*  f03ec64:	31cf0020 */ 	andi	$t7,$t6,0x20
/*  f03ec68:	11e00087 */ 	beqz	$t7,.L0f03ee88
/*  f03ec6c:	00000000 */ 	nop
/*  f03ec70:	3c017f1b */ 	lui	$at,%hi(var7f1a8f50)
/*  f03ec74:	c4288f4c */ 	lwc1	$f8,%lo(var7f1a8f4c)($at)
/*  f03ec78:	4608003c */ 	c.lt.s	$f0,$f8
/*  f03ec7c:	00000000 */ 	nop
/*  f03ec80:	45020066 */ 	bc1fl	.L0f03ee1c
/*  f03ec84:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03ec88:	46021180 */ 	add.s	$f6,$f2,$f2
/*  f03ec8c:	c7b20158 */ 	lwc1	$f18,0x158($sp)
/*  f03ec90:	8fb8016c */ 	lw	$t8,0x16c($sp)
/*  f03ec94:	3c013f00 */ 	lui	$at,0x3f00
/*  f03ec98:	46069101 */ 	sub.s	$f4,$f18,$f6
/*  f03ec9c:	c700000c */ 	lwc1	$f0,0xc($t8)
/*  f03eca0:	4604003c */ 	c.lt.s	$f0,$f4
/*  f03eca4:	00000000 */ 	nop
/*  f03eca8:	4502001e */ 	bc1fl	.L0f03ed24
/*  f03ecac:	44812000 */ 	mtc1	$at,$f4
/*  f03ecb0:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03ecb4:	0c004b70 */ 	jal	random
/*  f03ecb8:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03ecbc:	44825000 */ 	mtc1	$v0,$f10
/*  f03ecc0:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03ecc4:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03ecc8:	04410005 */ 	bgez	$v0,.L0f03ece0
/*  f03eccc:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f03ecd0:	3c014f80 */ 	lui	$at,0x4f80
/*  f03ecd4:	44819000 */ 	mtc1	$at,$f18
/*  f03ecd8:	00000000 */ 	nop
/*  f03ecdc:	46124200 */ 	add.s	$f8,$f8,$f18
.L0f03ece0:
/*  f03ece0:	3c012f80 */ 	lui	$at,0x2f80
/*  f03ece4:	44813000 */ 	mtc1	$at,$f6
/*  f03ece8:	3c017f1b */ 	lui	$at,%hi(var7f1a8f54)
/*  f03ecec:	c42a8f50 */ 	lwc1	$f10,%lo(var7f1a8f50)($at)
/*  f03ecf0:	46064102 */ 	mul.s	$f4,$f8,$f6
/*  f03ecf4:	c7a801a0 */ 	lwc1	$f8,0x1a0($sp)
/*  f03ecf8:	3c017f1b */ 	lui	$at,%hi(var7f1a8f58)
/*  f03ecfc:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f03ed00:	c42a8f54 */ 	lwc1	$f10,%lo(var7f1a8f54)($at)
/*  f03ed04:	46089182 */ 	mul.s	$f6,$f18,$f8
/*  f03ed08:	c7a80174 */ 	lwc1	$f8,0x174($sp)
/*  f03ed0c:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f03ed10:	46041482 */ 	mul.s	$f18,$f2,$f4
/*  f03ed14:	46124281 */ 	sub.s	$f10,$f8,$f18
/*  f03ed18:	1000011b */ 	b	.L0f03f188
/*  f03ed1c:	e7aa0174 */ 	swc1	$f10,0x174($sp)
/*  f03ed20:	44812000 */ 	mtc1	$at,$f4
.L0f03ed24:
/*  f03ed24:	c7a60158 */ 	lwc1	$f6,0x158($sp)
/*  f03ed28:	46041202 */ 	mul.s	$f8,$f2,$f4
/*  f03ed2c:	46083481 */ 	sub.s	$f18,$f6,$f8
/*  f03ed30:	4600903c */ 	c.lt.s	$f18,$f0
/*  f03ed34:	00000000 */ 	nop
/*  f03ed38:	4500001d */ 	bc1f	.L0f03edb0
/*  f03ed3c:	00000000 */ 	nop
/*  f03ed40:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03ed44:	0c004b70 */ 	jal	random
/*  f03ed48:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03ed4c:	44825000 */ 	mtc1	$v0,$f10
/*  f03ed50:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03ed54:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03ed58:	04410005 */ 	bgez	$v0,.L0f03ed70
/*  f03ed5c:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f03ed60:	3c014f80 */ 	lui	$at,0x4f80
/*  f03ed64:	44813000 */ 	mtc1	$at,$f6
/*  f03ed68:	00000000 */ 	nop
/*  f03ed6c:	46062100 */ 	add.s	$f4,$f4,$f6
.L0f03ed70:
/*  f03ed70:	3c012f80 */ 	lui	$at,0x2f80
/*  f03ed74:	44814000 */ 	mtc1	$at,$f8
/*  f03ed78:	3c017f1b */ 	lui	$at,%hi(var7f1a8f5c)
/*  f03ed7c:	c42a8f58 */ 	lwc1	$f10,%lo(var7f1a8f58)($at)
/*  f03ed80:	46082482 */ 	mul.s	$f18,$f4,$f8
/*  f03ed84:	c7a401a0 */ 	lwc1	$f4,0x1a0($sp)
/*  f03ed88:	3c017f1b */ 	lui	$at,%hi(var7f1a8f60)
/*  f03ed8c:	46125182 */ 	mul.s	$f6,$f10,$f18
/*  f03ed90:	c42a8f5c */ 	lwc1	$f10,%lo(var7f1a8f5c)($at)
/*  f03ed94:	46043202 */ 	mul.s	$f8,$f6,$f4
/*  f03ed98:	c7a40174 */ 	lwc1	$f4,0x174($sp)
/*  f03ed9c:	46085480 */ 	add.s	$f18,$f10,$f8
/*  f03eda0:	46121182 */ 	mul.s	$f6,$f2,$f18
/*  f03eda4:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f03eda8:	100000f7 */ 	b	.L0f03f188
/*  f03edac:	e7aa0174 */ 	swc1	$f10,0x174($sp)
.L0f03edb0:
/*  f03edb0:	0c004b70 */ 	jal	random
/*  f03edb4:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03edb8:	44824000 */ 	mtc1	$v0,$f8
/*  f03edbc:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03edc0:	04410005 */ 	bgez	$v0,.L0f03edd8
/*  f03edc4:	468044a0 */ 	cvt.s.w	$f18,$f8
/*  f03edc8:	3c014f80 */ 	lui	$at,0x4f80
/*  f03edcc:	44812000 */ 	mtc1	$at,$f4
/*  f03edd0:	00000000 */ 	nop
/*  f03edd4:	46049480 */ 	add.s	$f18,$f18,$f4
.L0f03edd8:
/*  f03edd8:	3c012f80 */ 	lui	$at,0x2f80
/*  f03eddc:	44813000 */ 	mtc1	$at,$f6
/*  f03ede0:	3c017f1b */ 	lui	$at,%hi(var7f1a8f64)
/*  f03ede4:	c4288f60 */ 	lwc1	$f8,%lo(var7f1a8f60)($at)
/*  f03ede8:	46069282 */ 	mul.s	$f10,$f18,$f6
/*  f03edec:	c7b201a0 */ 	lwc1	$f18,0x1a0($sp)
/*  f03edf0:	3c013f80 */ 	lui	$at,0x3f80
/*  f03edf4:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f03edf8:	44815000 */ 	mtc1	$at,$f10
/*  f03edfc:	3c014220 */ 	lui	$at,0x4220
/*  f03ee00:	46122182 */ 	mul.s	$f6,$f4,$f18
/*  f03ee04:	44812000 */ 	mtc1	$at,$f4
/*  f03ee08:	460a3200 */ 	add.s	$f8,$f6,$f10
/*  f03ee0c:	46044482 */ 	mul.s	$f18,$f8,$f4
/*  f03ee10:	100000dd */ 	b	.L0f03f188
/*  f03ee14:	e7b20174 */ 	swc1	$f18,0x174($sp)
/*  f03ee18:	e7a20140 */ 	swc1	$f2,0x140($sp)
.L0f03ee1c:
/*  f03ee1c:	0c004b70 */ 	jal	random
/*  f03ee20:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03ee24:	44823000 */ 	mtc1	$v0,$f6
/*  f03ee28:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03ee2c:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03ee30:	04410005 */ 	bgez	$v0,.L0f03ee48
/*  f03ee34:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f03ee38:	3c014f80 */ 	lui	$at,0x4f80
/*  f03ee3c:	44814000 */ 	mtc1	$at,$f8
/*  f03ee40:	00000000 */ 	nop
/*  f03ee44:	46085280 */ 	add.s	$f10,$f10,$f8
.L0f03ee48:
/*  f03ee48:	3c012f80 */ 	lui	$at,0x2f80
/*  f03ee4c:	44812000 */ 	mtc1	$at,$f4
/*  f03ee50:	3c017f1b */ 	lui	$at,%hi(var7f1a8f68)
/*  f03ee54:	c4268f64 */ 	lwc1	$f6,%lo(var7f1a8f64)($at)
/*  f03ee58:	46045482 */ 	mul.s	$f18,$f10,$f4
/*  f03ee5c:	c7aa01a0 */ 	lwc1	$f10,0x1a0($sp)
/*  f03ee60:	3c017f1b */ 	lui	$at,%hi(var7f1a8f6c)
/*  f03ee64:	46123202 */ 	mul.s	$f8,$f6,$f18
/*  f03ee68:	c4268f68 */ 	lwc1	$f6,%lo(var7f1a8f68)($at)
/*  f03ee6c:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f03ee70:	c7aa0174 */ 	lwc1	$f10,0x174($sp)
/*  f03ee74:	46043481 */ 	sub.s	$f18,$f6,$f4
/*  f03ee78:	46121202 */ 	mul.s	$f8,$f2,$f18
/*  f03ee7c:	46085180 */ 	add.s	$f6,$f10,$f8
/*  f03ee80:	100000c1 */ 	b	.L0f03f188
/*  f03ee84:	e7a60174 */ 	swc1	$f6,0x174($sp)
.L0f03ee88:
/*  f03ee88:	c4248f6c */ 	lwc1	$f4,%lo(var7f1a8f6c)($at)
/*  f03ee8c:	c7a80158 */ 	lwc1	$f8,0x158($sp)
/*  f03ee90:	4600203c */ 	c.lt.s	$f4,$f0
/*  f03ee94:	00000000 */ 	nop
/*  f03ee98:	45020043 */ 	bc1fl	.L0f03efa8
/*  f03ee9c:	8faa016c */ 	lw	$t2,0x16c($sp)
/*  f03eea0:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03eea4:	0c004b70 */ 	jal	random
/*  f03eea8:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03eeac:	24010003 */ 	addiu	$at,$zero,0x3
/*  f03eeb0:	0041001b */ 	divu	$zero,$v0,$at
/*  f03eeb4:	0000c810 */ 	mfhi	$t9
/*  f03eeb8:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03eebc:	1720001d */ 	bnez	$t9,.L0f03ef34
/*  f03eec0:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03eec4:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03eec8:	0c004b70 */ 	jal	random
/*  f03eecc:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03eed0:	44829000 */ 	mtc1	$v0,$f18
/*  f03eed4:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03eed8:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03eedc:	04410005 */ 	bgez	$v0,.L0f03eef4
/*  f03eee0:	468092a0 */ 	cvt.s.w	$f10,$f18
/*  f03eee4:	3c014f80 */ 	lui	$at,0x4f80
/*  f03eee8:	44814000 */ 	mtc1	$at,$f8
/*  f03eeec:	00000000 */ 	nop
/*  f03eef0:	46085280 */ 	add.s	$f10,$f10,$f8
.L0f03eef4:
/*  f03eef4:	3c012f80 */ 	lui	$at,0x2f80
/*  f03eef8:	44813000 */ 	mtc1	$at,$f6
/*  f03eefc:	3c017f1b */ 	lui	$at,%hi(var7f1a8f70)
/*  f03ef00:	c4328f70 */ 	lwc1	$f18,%lo(var7f1a8f70)($at)
/*  f03ef04:	46065102 */ 	mul.s	$f4,$f10,$f6
/*  f03ef08:	c7aa01a0 */ 	lwc1	$f10,0x1a0($sp)
/*  f03ef0c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f74)
/*  f03ef10:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f03ef14:	c4328f74 */ 	lwc1	$f18,%lo(var7f1a8f74)($at)
/*  f03ef18:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f03ef1c:	c7aa0174 */ 	lwc1	$f10,0x174($sp)
/*  f03ef20:	46069100 */ 	add.s	$f4,$f18,$f6
/*  f03ef24:	46041202 */ 	mul.s	$f8,$f2,$f4
/*  f03ef28:	46085480 */ 	add.s	$f18,$f10,$f8
/*  f03ef2c:	10000096 */ 	b	.L0f03f188
/*  f03ef30:	e7b20174 */ 	swc1	$f18,0x174($sp)
.L0f03ef34:
/*  f03ef34:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03ef38:	0c004b70 */ 	jal	random
/*  f03ef3c:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03ef40:	44823000 */ 	mtc1	$v0,$f6
/*  f03ef44:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03ef48:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03ef4c:	04410005 */ 	bgez	$v0,.L0f03ef64
/*  f03ef50:	46803120 */ 	cvt.s.w	$f4,$f6
/*  f03ef54:	3c014f80 */ 	lui	$at,0x4f80
/*  f03ef58:	44815000 */ 	mtc1	$at,$f10
/*  f03ef5c:	00000000 */ 	nop
/*  f03ef60:	460a2100 */ 	add.s	$f4,$f4,$f10
.L0f03ef64:
/*  f03ef64:	3c012f80 */ 	lui	$at,0x2f80
/*  f03ef68:	44814000 */ 	mtc1	$at,$f8
/*  f03ef6c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f78)
/*  f03ef70:	c4268f78 */ 	lwc1	$f6,%lo(var7f1a8f78)($at)
/*  f03ef74:	46082482 */ 	mul.s	$f18,$f4,$f8
/*  f03ef78:	c7a401a0 */ 	lwc1	$f4,0x1a0($sp)
/*  f03ef7c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f7c)
/*  f03ef80:	46123282 */ 	mul.s	$f10,$f6,$f18
/*  f03ef84:	c4268f7c */ 	lwc1	$f6,%lo(var7f1a8f7c)($at)
/*  f03ef88:	46045202 */ 	mul.s	$f8,$f10,$f4
/*  f03ef8c:	c7a40174 */ 	lwc1	$f4,0x174($sp)
/*  f03ef90:	46083480 */ 	add.s	$f18,$f6,$f8
/*  f03ef94:	46121282 */ 	mul.s	$f10,$f2,$f18
/*  f03ef98:	460a2181 */ 	sub.s	$f6,$f4,$f10
/*  f03ef9c:	1000007a */ 	b	.L0f03f188
/*  f03efa0:	e7a60174 */ 	swc1	$f6,0x174($sp)
/*  f03efa4:	8faa016c */ 	lw	$t2,0x16c($sp)
.L0f03efa8:
/*  f03efa8:	46024481 */ 	sub.s	$f18,$f8,$f2
/*  f03efac:	3c013f00 */ 	lui	$at,0x3f00
/*  f03efb0:	c540000c */ 	lwc1	$f0,0xc($t2)
/*  f03efb4:	4612003c */ 	c.lt.s	$f0,$f18
/*  f03efb8:	00000000 */ 	nop
/*  f03efbc:	4502001e */ 	bc1fl	.L0f03f038
/*  f03efc0:	44819000 */ 	mtc1	$at,$f18
/*  f03efc4:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03efc8:	0c004b70 */ 	jal	random
/*  f03efcc:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03efd0:	44822000 */ 	mtc1	$v0,$f4
/*  f03efd4:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03efd8:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03efdc:	04410005 */ 	bgez	$v0,.L0f03eff4
/*  f03efe0:	468022a0 */ 	cvt.s.w	$f10,$f4
/*  f03efe4:	3c014f80 */ 	lui	$at,0x4f80
/*  f03efe8:	44813000 */ 	mtc1	$at,$f6
/*  f03efec:	00000000 */ 	nop
/*  f03eff0:	46065280 */ 	add.s	$f10,$f10,$f6
.L0f03eff4:
/*  f03eff4:	3c012f80 */ 	lui	$at,0x2f80
/*  f03eff8:	44814000 */ 	mtc1	$at,$f8
/*  f03effc:	3c017f1b */ 	lui	$at,%hi(var7f1a8f80)
/*  f03f000:	c4248f80 */ 	lwc1	$f4,%lo(var7f1a8f80)($at)
/*  f03f004:	46085482 */ 	mul.s	$f18,$f10,$f8
/*  f03f008:	c7aa01a0 */ 	lwc1	$f10,0x1a0($sp)
/*  f03f00c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f84)
/*  f03f010:	46122182 */ 	mul.s	$f6,$f4,$f18
/*  f03f014:	c4248f84 */ 	lwc1	$f4,%lo(var7f1a8f84)($at)
/*  f03f018:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f03f01c:	c7aa0174 */ 	lwc1	$f10,0x174($sp)
/*  f03f020:	46082480 */ 	add.s	$f18,$f4,$f8
/*  f03f024:	46121182 */ 	mul.s	$f6,$f2,$f18
/*  f03f028:	46065101 */ 	sub.s	$f4,$f10,$f6
/*  f03f02c:	10000056 */ 	b	.L0f03f188
/*  f03f030:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f03f034:	44819000 */ 	mtc1	$at,$f18
.L0f03f038:
/*  f03f038:	c7a80158 */ 	lwc1	$f8,0x158($sp)
/*  f03f03c:	46121282 */ 	mul.s	$f10,$f2,$f18
/*  f03f040:	460a4181 */ 	sub.s	$f6,$f8,$f10
/*  f03f044:	4600303c */ 	c.lt.s	$f6,$f0
/*  f03f048:	00000000 */ 	nop
/*  f03f04c:	4502001e */ 	bc1fl	.L0f03f0c8
/*  f03f050:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03f054:	e7a20140 */ 	swc1	$f2,0x140($sp)
/*  f03f058:	0c004b70 */ 	jal	random
/*  f03f05c:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f060:	44822000 */ 	mtc1	$v0,$f4
/*  f03f064:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03f068:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f06c:	04410005 */ 	bgez	$v0,.L0f03f084
/*  f03f070:	468024a0 */ 	cvt.s.w	$f18,$f4
/*  f03f074:	3c014f80 */ 	lui	$at,0x4f80
/*  f03f078:	44814000 */ 	mtc1	$at,$f8
/*  f03f07c:	00000000 */ 	nop
/*  f03f080:	46089480 */ 	add.s	$f18,$f18,$f8
.L0f03f084:
/*  f03f084:	3c012f80 */ 	lui	$at,0x2f80
/*  f03f088:	44815000 */ 	mtc1	$at,$f10
/*  f03f08c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f88)
/*  f03f090:	c4248f88 */ 	lwc1	$f4,%lo(var7f1a8f88)($at)
/*  f03f094:	460a9182 */ 	mul.s	$f6,$f18,$f10
/*  f03f098:	c7b201a0 */ 	lwc1	$f18,0x1a0($sp)
/*  f03f09c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f8c)
/*  f03f0a0:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f03f0a4:	c4248f8c */ 	lwc1	$f4,%lo(var7f1a8f8c)($at)
/*  f03f0a8:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f03f0ac:	c7b20174 */ 	lwc1	$f18,0x174($sp)
/*  f03f0b0:	460a2180 */ 	add.s	$f6,$f4,$f10
/*  f03f0b4:	46061202 */ 	mul.s	$f8,$f2,$f6
/*  f03f0b8:	46089101 */ 	sub.s	$f4,$f18,$f8
/*  f03f0bc:	10000032 */ 	b	.L0f03f188
/*  f03f0c0:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f03f0c4:	e7a20140 */ 	swc1	$f2,0x140($sp)
.L0f03f0c8:
/*  f03f0c8:	0c004b70 */ 	jal	random
/*  f03f0cc:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f0d0:	44825000 */ 	mtc1	$v0,$f10
/*  f03f0d4:	c7a20140 */ 	lwc1	$f2,0x140($sp)
/*  f03f0d8:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f0dc:	04410005 */ 	bgez	$v0,.L0f03f0f4
/*  f03f0e0:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f03f0e4:	3c014f80 */ 	lui	$at,0x4f80
/*  f03f0e8:	44819000 */ 	mtc1	$at,$f18
/*  f03f0ec:	00000000 */ 	nop
/*  f03f0f0:	46123180 */ 	add.s	$f6,$f6,$f18
.L0f03f0f4:
/*  f03f0f4:	3c012f80 */ 	lui	$at,0x2f80
/*  f03f0f8:	44814000 */ 	mtc1	$at,$f8
/*  f03f0fc:	3c017f1b */ 	lui	$at,%hi(var7f1a8f90)
/*  f03f100:	c42a8f90 */ 	lwc1	$f10,%lo(var7f1a8f90)($at)
/*  f03f104:	46083102 */ 	mul.s	$f4,$f6,$f8
/*  f03f108:	c7a601a0 */ 	lwc1	$f6,0x1a0($sp)
/*  f03f10c:	3c017f1b */ 	lui	$at,%hi(var7f1a8f94)
/*  f03f110:	460a2482 */ 	mul.s	$f18,$f4,$f10
/*  f03f114:	c4248f94 */ 	lwc1	$f4,%lo(var7f1a8f94)($at)
/*  f03f118:	46069202 */ 	mul.s	$f8,$f18,$f6
/*  f03f11c:	46044281 */ 	sub.s	$f10,$f8,$f4
/*  f03f120:	46025482 */ 	mul.s	$f18,$f10,$f2
/*  f03f124:	10000018 */ 	b	.L0f03f188
/*  f03f128:	e7b20174 */ 	swc1	$f18,0x174($sp)
/*  f03f12c:	8cc40020 */ 	lw	$a0,0x20($a2)
.L0f03f130:
/*  f03f130:	0c006b43 */ 	jal	modelGetRootPosition
/*  f03f134:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f138:	27a90144 */ 	addiu	$t1,$sp,0x144
/*  f03f13c:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f03f140:	8fa40190 */ 	lw	$a0,0x190($sp)
/*  f03f144:	8fa50184 */ 	lw	$a1,0x184($sp)
/*  f03f148:	8fa60180 */ 	lw	$a2,0x180($sp)
/*  f03f14c:	0fc122de */ 	jal	chrGetAttackEntityPos
/*  f03f150:	27a70154 */ 	addiu	$a3,$sp,0x154
/*  f03f154:	c7a60154 */ 	lwc1	$f6,0x154($sp)
/*  f03f158:	c7a80134 */ 	lwc1	$f8,0x134($sp)
/*  f03f15c:	c7aa0158 */ 	lwc1	$f10,0x158($sp)
/*  f03f160:	c7b20138 */ 	lwc1	$f18,0x138($sp)
/*  f03f164:	46083101 */ 	sub.s	$f4,$f6,$f8
/*  f03f168:	c7a8015c */ 	lwc1	$f8,0x15c($sp)
/*  f03f16c:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f170:	46125181 */ 	sub.s	$f6,$f10,$f18
/*  f03f174:	e7a40178 */ 	swc1	$f4,0x178($sp)
/*  f03f178:	c7a4013c */ 	lwc1	$f4,0x13c($sp)
/*  f03f17c:	e7a60174 */ 	swc1	$f6,0x174($sp)
/*  f03f180:	46044281 */ 	sub.s	$f10,$f8,$f4
/*  f03f184:	e7aa0170 */ 	swc1	$f10,0x170($sp)
.L0f03f188:
/*  f03f188:	8fab0184 */ 	lw	$t3,0x184($sp)
/*  f03f18c:	c7b20178 */ 	lwc1	$f18,0x178($sp)
/*  f03f190:	c7a80170 */ 	lwc1	$f8,0x170($sp)
/*  f03f194:	316d0100 */ 	andi	$t5,$t3,0x100
/*  f03f198:	55a00015 */ 	bnezl	$t5,.L0f03f1f0
/*  f03f19c:	8fac0160 */ 	lw	$t4,0x160($sp)
/*  f03f1a0:	46129182 */ 	mul.s	$f6,$f18,$f18
/*  f03f1a4:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f1a8:	46084102 */ 	mul.s	$f4,$f8,$f8
/*  f03f1ac:	0c012974 */ 	jal	sqrtf
/*  f03f1b0:	46043300 */ 	add.s	$f12,$f6,$f4
/*  f03f1b4:	c7ac0174 */ 	lwc1	$f12,0x174($sp)
/*  f03f1b8:	0fc259d4 */ 	jal	atan2f
/*  f03f1bc:	46000386 */ 	mov.s	$f14,$f0
/*  f03f1c0:	3c017f1b */ 	lui	$at,%hi(var7f1a8f98)
/*  f03f1c4:	c42a8f98 */ 	lwc1	$f10,%lo(var7f1a8f98)($at)
/*  f03f1c8:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f1cc:	e7a0018c */ 	swc1	$f0,0x18c($sp)
/*  f03f1d0:	4600503e */ 	c.le.s	$f10,$f0
/*  f03f1d4:	3c017f1b */ 	lui	$at,%hi(var7f1a8f9c)
/*  f03f1d8:	45020005 */ 	bc1fl	.L0f03f1f0
/*  f03f1dc:	8fac0160 */ 	lw	$t4,0x160($sp)
/*  f03f1e0:	c4328f9c */ 	lwc1	$f18,%lo(var7f1a8f9c)($at)
/*  f03f1e4:	46120201 */ 	sub.s	$f8,$f0,$f18
/*  f03f1e8:	e7a8018c */ 	swc1	$f8,0x18c($sp)
/*  f03f1ec:	8fac0160 */ 	lw	$t4,0x160($sp)
.L0f03f1f0:
/*  f03f1f0:	51800150 */ 	beqzl	$t4,.L0f03f734
/*  f03f1f4:	c7a4018c */ 	lwc1	$f4,0x18c($sp)
/*  f03f1f8:	0fc0f97c */ 	jal	chrGetAimAngle
/*  f03f1fc:	8fa40190 */ 	lw	$a0,0x190($sp)
/*  f03f200:	8fae0020 */ 	lw	$t6,0x20($sp)
/*  f03f204:	e7a00130 */ 	swc1	$f0,0x130($sp)
/*  f03f208:	8faf019c */ 	lw	$t7,0x19c($sp)
/*  f03f20c:	51c000aa */ 	beqzl	$t6,.L0f03f4b8
/*  f03f210:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f03f214:	11e00006 */ 	beqz	$t7,.L0f03f230
/*  f03f218:	8fa40190 */ 	lw	$a0,0x190($sp)
/*  f03f21c:	8fa40190 */ 	lw	$a0,0x190($sp)
/*  f03f220:	0fc0a209 */ 	jal	chrGetHeldProp
/*  f03f224:	00002825 */ 	or	$a1,$zero,$zero
/*  f03f228:	10000004 */ 	b	.L0f03f23c
/*  f03f22c:	00404025 */ 	or	$t0,$v0,$zero
.L0f03f230:
/*  f03f230:	0fc0a209 */ 	jal	chrGetHeldProp
/*  f03f234:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f03f238:	00404025 */ 	or	$t0,$v0,$zero
.L0f03f23c:
/*  f03f23c:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x6c)
/*  f03f240:	8f18a02c */ 	lw	$t8,%lo(g_Vars+0x6c)($t8)
/*  f03f244:	3c19800a */ 	lui	$t9,%hi(g_Vars+0x68)
/*  f03f248:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x64)
/*  f03f24c:	13000003 */ 	beqz	$t8,.L0f03f25c
/*  f03f250:	3c09800a */ 	lui	$t1,%hi(g_Vars+0x70)
/*  f03f254:	10000002 */ 	b	.L0f03f260
/*  f03f258:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f03f25c:
/*  f03f25c:	00003025 */ 	or	$a2,$zero,$zero
.L0f03f260:
/*  f03f260:	8f39a028 */ 	lw	$t9,%lo(g_Vars+0x68)($t9)
/*  f03f264:	24010001 */ 	addiu	$at,$zero,0x1
/*  f03f268:	00002025 */ 	or	$a0,$zero,$zero
/*  f03f26c:	13200003 */ 	beqz	$t9,.L0f03f27c
/*  f03f270:	00002825 */ 	or	$a1,$zero,$zero
/*  f03f274:	10000001 */ 	b	.L0f03f27c
/*  f03f278:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f03f27c:
/*  f03f27c:	8d4aa024 */ 	lw	$t2,%lo(g_Vars+0x64)($t2)
/*  f03f280:	00001825 */ 	or	$v1,$zero,$zero
/*  f03f284:	11400003 */ 	beqz	$t2,.L0f03f294
/*  f03f288:	00000000 */ 	nop
/*  f03f28c:	10000001 */ 	b	.L0f03f294
/*  f03f290:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f03f294:
/*  f03f294:	8d29a030 */ 	lw	$t1,%lo(g_Vars+0x70)($t1)
/*  f03f298:	11200003 */ 	beqz	$t1,.L0f03f2a8
/*  f03f29c:	00000000 */ 	nop
/*  f03f2a0:	10000001 */ 	b	.L0f03f2a8
/*  f03f2a4:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f03f2a8:
/*  f03f2a8:	00655821 */ 	addu	$t3,$v1,$a1
/*  f03f2ac:	01646821 */ 	addu	$t5,$t3,$a0
/*  f03f2b0:	01a66021 */ 	addu	$t4,$t5,$a2
/*  f03f2b4:	55810080 */ 	bnel	$t4,$at,.L0f03f4b8
/*  f03f2b8:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f03f2bc:	5040007e */ 	beqzl	$v0,.L0f03f4b8
/*  f03f2c0:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f03f2c4:	904e0001 */ 	lbu	$t6,0x1($v0)
/*  f03f2c8:	c7a60164 */ 	lwc1	$f6,0x164($sp)
/*  f03f2cc:	3c017f1b */ 	lui	$at,%hi(var7f1a8fa0)
/*  f03f2d0:	31cf0080 */ 	andi	$t7,$t6,0x80
/*  f03f2d4:	51e00078 */ 	beqzl	$t7,.L0f03f4b8
/*  f03f2d8:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f03f2dc:	c4248fa0 */ 	lwc1	$f4,%lo(var7f1a8fa0)($at)
/*  f03f2e0:	4604303c */ 	c.lt.s	$f6,$f4
/*  f03f2e4:	00000000 */ 	nop
/*  f03f2e8:	45020073 */ 	bc1fl	.L0f03f4b8
/*  f03f2ec:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f03f2f0:	8d020004 */ 	lw	$v0,0x4($t0)
/*  f03f2f4:	00002825 */ 	or	$a1,$zero,$zero
/*  f03f2f8:	8c470018 */ 	lw	$a3,0x18($v0)
/*  f03f2fc:	afa00114 */ 	sw	$zero,0x114($sp)
/*  f03f300:	8ce40008 */ 	lw	$a0,0x8($a3)
/*  f03f304:	0c006a47 */ 	jal	modelGetPart
/*  f03f308:	afa70124 */ 	sw	$a3,0x124($sp)
/*  f03f30c:	8fa70124 */ 	lw	$a3,0x124($sp)
/*  f03f310:	10400026 */ 	beqz	$v0,.L0f03f3ac
/*  f03f314:	00402825 */ 	or	$a1,$v0,$zero
/*  f03f318:	00e02025 */ 	or	$a0,$a3,$zero
/*  f03f31c:	00003025 */ 	or	$a2,$zero,$zero
/*  f03f320:	0c006973 */ 	jal	model0001a5cc
/*  f03f324:	afa20110 */ 	sw	$v0,0x110($sp)
/*  f03f328:	8fa50110 */ 	lw	$a1,0x110($sp)
/*  f03f32c:	afa20108 */ 	sw	$v0,0x108($sp)
/*  f03f330:	00402025 */ 	or	$a0,$v0,$zero
/*  f03f334:	8cb80004 */ 	lw	$t8,0x4($a1)
/*  f03f338:	0fc2d4e9 */ 	jal	func0f0b53a4
/*  f03f33c:	afb800c4 */ 	sw	$t8,0xc4($sp)
/*  f03f340:	10400037 */ 	beqz	$v0,.L0f03f420
/*  f03f344:	8fa40108 */ 	lw	$a0,0x108($sp)
/*  f03f348:	27a500c8 */ 	addiu	$a1,$sp,0xc8
/*  f03f34c:	0c0059e6 */ 	jal	mtx00016798
/*  f03f350:	afa200b4 */ 	sw	$v0,0xb4($sp)
/*  f03f354:	8fa400b4 */ 	lw	$a0,0xb4($sp)
/*  f03f358:	0c0056f8 */ 	jal	mtx00015be0
/*  f03f35c:	27a500c8 */ 	addiu	$a1,$sp,0xc8
/*  f03f360:	8fa200c4 */ 	lw	$v0,0xc4($sp)
/*  f03f364:	27a400c8 */ 	addiu	$a0,$sp,0xc8
/*  f03f368:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f03f36c:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f03f370:	e7aa00b8 */ 	swc1	$f10,0xb8($sp)
/*  f03f374:	c4520004 */ 	lwc1	$f18,0x4($v0)
/*  f03f378:	e7b200bc */ 	swc1	$f18,0xbc($sp)
/*  f03f37c:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f03f380:	0c0056d9 */ 	jal	mtx4TransformVecInPlace
/*  f03f384:	e7a800c0 */ 	swc1	$f8,0xc0($sp)
/*  f03f388:	c7a600b8 */ 	lwc1	$f6,0xb8($sp)
/*  f03f38c:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f03f390:	c7aa00c0 */ 	lwc1	$f10,0xc0($sp)
/*  f03f394:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f03f398:	afb90114 */ 	sw	$t9,0x114($sp)
/*  f03f39c:	e7a60118 */ 	swc1	$f6,0x118($sp)
/*  f03f3a0:	e7a4011c */ 	swc1	$f4,0x11c($sp)
/*  f03f3a4:	1000001e */ 	b	.L0f03f420
/*  f03f3a8:	e7aa0120 */ 	swc1	$f10,0x120($sp)
.L0f03f3ac:
/*  f03f3ac:	8ce40008 */ 	lw	$a0,0x8($a3)
/*  f03f3b0:	afa70124 */ 	sw	$a3,0x124($sp)
/*  f03f3b4:	0c006a47 */ 	jal	modelGetPart
/*  f03f3b8:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f03f3bc:	8fa70124 */ 	lw	$a3,0x124($sp)
/*  f03f3c0:	10400017 */ 	beqz	$v0,.L0f03f420
/*  f03f3c4:	00402825 */ 	or	$a1,$v0,$zero
/*  f03f3c8:	00e02025 */ 	or	$a0,$a3,$zero
/*  f03f3cc:	0c006973 */ 	jal	model0001a5cc
/*  f03f3d0:	00003025 */ 	or	$a2,$zero,$zero
/*  f03f3d4:	afa200b0 */ 	sw	$v0,0xb0($sp)
/*  f03f3d8:	0fc2d4e9 */ 	jal	func0f0b53a4
/*  f03f3dc:	00402025 */ 	or	$a0,$v0,$zero
/*  f03f3e0:	1040000f */ 	beqz	$v0,.L0f03f420
/*  f03f3e4:	8fa400b0 */ 	lw	$a0,0xb0($sp)
/*  f03f3e8:	27a50070 */ 	addiu	$a1,$sp,0x70
/*  f03f3ec:	0c0059e6 */ 	jal	mtx00016798
/*  f03f3f0:	afa2006c */ 	sw	$v0,0x6c($sp)
/*  f03f3f4:	8fa4006c */ 	lw	$a0,0x6c($sp)
/*  f03f3f8:	0c0056f8 */ 	jal	mtx00015be0
/*  f03f3fc:	27a50070 */ 	addiu	$a1,$sp,0x70
/*  f03f400:	c7b200a0 */ 	lwc1	$f18,0xa0($sp)
/*  f03f404:	c7a800a4 */ 	lwc1	$f8,0xa4($sp)
/*  f03f408:	c7a600a8 */ 	lwc1	$f6,0xa8($sp)
/*  f03f40c:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f03f410:	afaa0114 */ 	sw	$t2,0x114($sp)
/*  f03f414:	e7b20118 */ 	swc1	$f18,0x118($sp)
/*  f03f418:	e7a8011c */ 	swc1	$f8,0x11c($sp)
/*  f03f41c:	e7a60120 */ 	swc1	$f6,0x120($sp)
.L0f03f420:
/*  f03f420:	8fa90114 */ 	lw	$t1,0x114($sp)
/*  f03f424:	51200024 */ 	beqzl	$t1,.L0f03f4b8
/*  f03f428:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
/*  f03f42c:	0c0068f7 */ 	jal	sinf
/*  f03f430:	c7ac0130 */ 	lwc1	$f12,0x130($sp)
/*  f03f434:	44802000 */ 	mtc1	$zero,$f4
/*  f03f438:	e7a00054 */ 	swc1	$f0,0x54($sp)
/*  f03f43c:	c7ac0130 */ 	lwc1	$f12,0x130($sp)
/*  f03f440:	0c0068f4 */ 	jal	cosf
/*  f03f444:	e7a40058 */ 	swc1	$f4,0x58($sp)
/*  f03f448:	8fa2016c */ 	lw	$v0,0x16c($sp)
/*  f03f44c:	e7a0005c */ 	swc1	$f0,0x5c($sp)
/*  f03f450:	c7b20170 */ 	lwc1	$f18,0x170($sp)
/*  f03f454:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f03f458:	27ab0060 */ 	addiu	$t3,$sp,0x60
/*  f03f45c:	27a50048 */ 	addiu	$a1,$sp,0x48
/*  f03f460:	46125201 */ 	sub.s	$f8,$f10,$f18
/*  f03f464:	c7aa0178 */ 	lwc1	$f10,0x178($sp)
/*  f03f468:	27a60118 */ 	addiu	$a2,$sp,0x118
/*  f03f46c:	27a70054 */ 	addiu	$a3,$sp,0x54
/*  f03f470:	e7a80048 */ 	swc1	$f8,0x48($sp)
/*  f03f474:	c446000c */ 	lwc1	$f6,0xc($v0)
/*  f03f478:	24440008 */ 	addiu	$a0,$v0,0x8
/*  f03f47c:	e7a6004c */ 	swc1	$f6,0x4c($sp)
/*  f03f480:	c4440010 */ 	lwc1	$f4,0x10($v0)
/*  f03f484:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f03f488:	460a2480 */ 	add.s	$f18,$f4,$f10
/*  f03f48c:	0fc0b8f7 */ 	jal	func0f02e3dc
/*  f03f490:	e7b20050 */ 	swc1	$f18,0x50($sp)
/*  f03f494:	c7a80154 */ 	lwc1	$f8,0x154($sp)
/*  f03f498:	c7a60060 */ 	lwc1	$f6,0x60($sp)
/*  f03f49c:	c7aa015c */ 	lwc1	$f10,0x15c($sp)
/*  f03f4a0:	c7b20068 */ 	lwc1	$f18,0x68($sp)
/*  f03f4a4:	46064101 */ 	sub.s	$f4,$f8,$f6
/*  f03f4a8:	46125201 */ 	sub.s	$f8,$f10,$f18
/*  f03f4ac:	e7a40178 */ 	swc1	$f4,0x178($sp)
/*  f03f4b0:	e7a80170 */ 	swc1	$f8,0x170($sp)
/*  f03f4b4:	c7ac0178 */ 	lwc1	$f12,0x178($sp)
.L0f03f4b8:
/*  f03f4b8:	0fc259d4 */ 	jal	atan2f
/*  f03f4bc:	c7ae0170 */ 	lwc1	$f14,0x170($sp)
/*  f03f4c0:	c7a60130 */ 	lwc1	$f6,0x130($sp)
/*  f03f4c4:	3c017f1b */ 	lui	$at,%hi(var7f1a8fa4)
/*  f03f4c8:	8fad0190 */ 	lw	$t5,0x190($sp)
/*  f03f4cc:	4606003c */ 	c.lt.s	$f0,$f6
/*  f03f4d0:	46060081 */ 	sub.s	$f2,$f0,$f6
/*  f03f4d4:	45000003 */ 	bc1f	.L0f03f4e4
/*  f03f4d8:	46001406 */ 	mov.s	$f16,$f2
/*  f03f4dc:	c4248fa4 */ 	lwc1	$f4,%lo(var7f1a8fa4)($at)
/*  f03f4e0:	46041400 */ 	add.s	$f16,$f2,$f4
.L0f03f4e4:
/*  f03f4e4:	8da40020 */ 	lw	$a0,0x20($t5)
/*  f03f4e8:	8c8c0008 */ 	lw	$t4,0x8($a0)
/*  f03f4ec:	8d850000 */ 	lw	$a1,0x0($t4)
/*  f03f4f0:	0c006a87 */ 	jal	modelGetNodeRwData
/*  f03f4f4:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f4f8:	44801000 */ 	mtc1	$zero,$f2
/*  f03f4fc:	c440005c */ 	lwc1	$f0,0x5c($v0)
/*  f03f500:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f504:	8fae0190 */ 	lw	$t6,0x190($sp)
/*  f03f508:	4600103c */ 	c.lt.s	$f2,$f0
/*  f03f50c:	8fb80020 */ 	lw	$t8,0x20($sp)
/*  f03f510:	45020015 */ 	bc1fl	.L0f03f568
/*  f03f514:	8dcf02d4 */ 	lw	$t7,0x2d4($t6)
/*  f03f518:	c44a0058 */ 	lwc1	$f10,0x58($v0)
/*  f03f51c:	3c017f1b */ 	lui	$at,%hi(var7f1a8fa8)
/*  f03f520:	460a0482 */ 	mul.s	$f18,$f0,$f10
/*  f03f524:	46128401 */ 	sub.s	$f16,$f16,$f18
/*  f03f528:	4602803c */ 	c.lt.s	$f16,$f2
/*  f03f52c:	00000000 */ 	nop
/*  f03f530:	45000003 */ 	bc1f	.L0f03f540
/*  f03f534:	00000000 */ 	nop
/*  f03f538:	c4288fa8 */ 	lwc1	$f8,%lo(var7f1a8fa8)($at)
/*  f03f53c:	46088400 */ 	add.s	$f16,$f16,$f8
.L0f03f540:
/*  f03f540:	3c017f1b */ 	lui	$at,%hi(var7f1a8fac)
/*  f03f544:	c4268fac */ 	lwc1	$f6,%lo(var7f1a8fac)($at)
/*  f03f548:	3c017f1b */ 	lui	$at,%hi(var7f1a8fb0)
/*  f03f54c:	4610303e */ 	c.le.s	$f6,$f16
/*  f03f550:	00000000 */ 	nop
/*  f03f554:	45020004 */ 	bc1fl	.L0f03f568
/*  f03f558:	8dcf02d4 */ 	lw	$t7,0x2d4($t6)
/*  f03f55c:	c4248fb0 */ 	lwc1	$f4,%lo(var7f1a8fb0)($at)
/*  f03f560:	46048401 */ 	sub.s	$f16,$f16,$f4
/*  f03f564:	8dcf02d4 */ 	lw	$t7,0x2d4($t6)
.L0f03f568:
/*  f03f568:	15e0003d */ 	bnez	$t7,.L0f03f660
/*  f03f56c:	00000000 */ 	nop
/*  f03f570:	1300003b */ 	beqz	$t8,.L0f03f660
/*  f03f574:	8fb90184 */ 	lw	$t9,0x184($sp)
/*  f03f578:	332a0060 */ 	andi	$t2,$t9,0x60
/*  f03f57c:	15400038 */ 	bnez	$t2,.L0f03f660
/*  f03f580:	8fa90168 */ 	lw	$t1,0x168($sp)
/*  f03f584:	912b0000 */ 	lbu	$t3,0x0($t1)
/*  f03f588:	24010006 */ 	addiu	$at,$zero,0x6
/*  f03f58c:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x8)
/*  f03f590:	15610033 */ 	bne	$t3,$at,.L0f03f660
/*  f03f594:	8fac0190 */ 	lw	$t4,0x190($sp)
/*  f03f598:	8dad9fc8 */ 	lw	$t5,%lo(g_Vars+0x8)($t5)
/*  f03f59c:	8d8e0020 */ 	lw	$t6,0x20($t4)
/*  f03f5a0:	858a0000 */ 	lh	$t2,0x0($t4)
/*  f03f5a4:	448d5000 */ 	mtc1	$t5,$f10
/*  f03f5a8:	8dcf0020 */ 	lw	$t7,0x20($t6)
/*  f03f5ac:	2401003c */ 	addiu	$at,$zero,0x3c
/*  f03f5b0:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f03f5b4:	c5e80074 */ 	lwc1	$f8,0x74($t7)
/*  f03f5b8:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f5bc:	46089182 */ 	mul.s	$f6,$f18,$f8
/*  f03f5c0:	4600310d */ 	trunc.w.s	$f4,$f6
/*  f03f5c4:	44192000 */ 	mfc1	$t9,$f4
/*  f03f5c8:	00000000 */ 	nop
/*  f03f5cc:	032a4821 */ 	addu	$t1,$t9,$t2
/*  f03f5d0:	0121001a */ 	div	$zero,$t1,$at
/*  f03f5d4:	00005810 */ 	mfhi	$t3
/*  f03f5d8:	448b5000 */ 	mtc1	$t3,$f10
/*  f03f5dc:	3c017f1b */ 	lui	$at,%hi(var7f1a8fb4)
/*  f03f5e0:	c4288fb4 */ 	lwc1	$f8,%lo(var7f1a8fb4)($at)
/*  f03f5e4:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f03f5e8:	46089302 */ 	mul.s	$f12,$f18,$f8
/*  f03f5ec:	0c0068f7 */ 	jal	sinf
/*  f03f5f0:	00000000 */ 	nop
/*  f03f5f4:	e7a00028 */ 	swc1	$f0,0x28($sp)
/*  f03f5f8:	0fc0fe84 */ 	jal	chrGetAimLimitAngle
/*  f03f5fc:	c7ac0164 */ 	lwc1	$f12,0x164($sp)
/*  f03f600:	3c013f00 */ 	lui	$at,0x3f00
/*  f03f604:	44813000 */ 	mtc1	$at,$f6
/*  f03f608:	c7aa0028 */ 	lwc1	$f10,0x28($sp)
/*  f03f60c:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f610:	46060102 */ 	mul.s	$f4,$f0,$f6
/*  f03f614:	44804000 */ 	mtc1	$zero,$f8
/*  f03f618:	3c017f1b */ 	lui	$at,%hi(var7f1a8fb8)
/*  f03f61c:	460a2482 */ 	mul.s	$f18,$f4,$f10
/*  f03f620:	46128400 */ 	add.s	$f16,$f16,$f18
/*  f03f624:	4608803c */ 	c.lt.s	$f16,$f8
/*  f03f628:	00000000 */ 	nop
/*  f03f62c:	45000003 */ 	bc1f	.L0f03f63c
/*  f03f630:	00000000 */ 	nop
/*  f03f634:	c4268fb8 */ 	lwc1	$f6,%lo(var7f1a8fb8)($at)
/*  f03f638:	46068400 */ 	add.s	$f16,$f16,$f6
.L0f03f63c:
/*  f03f63c:	3c017f1b */ 	lui	$at,%hi(var7f1a8fbc)
/*  f03f640:	c4248fbc */ 	lwc1	$f4,%lo(var7f1a8fbc)($at)
/*  f03f644:	3c017f1b */ 	lui	$at,%hi(var7f1a8fc0)
/*  f03f648:	4610203e */ 	c.le.s	$f4,$f16
/*  f03f64c:	00000000 */ 	nop
/*  f03f650:	45000003 */ 	bc1f	.L0f03f660
/*  f03f654:	00000000 */ 	nop
/*  f03f658:	c42a8fc0 */ 	lwc1	$f10,%lo(var7f1a8fc0)($at)
/*  f03f65c:	460a8401 */ 	sub.s	$f16,$f16,$f10
.L0f03f660:
/*  f03f660:	3c017f1b */ 	lui	$at,%hi(var7f1a8fc4)
/*  f03f664:	c4328fc4 */ 	lwc1	$f18,%lo(var7f1a8fc4)($at)
/*  f03f668:	3c017f1b */ 	lui	$at,%hi(var7f1a8fc8)
/*  f03f66c:	8fad0190 */ 	lw	$t5,0x190($sp)
/*  f03f670:	4610903e */ 	c.le.s	$f18,$f16
/*  f03f674:	00000000 */ 	nop
/*  f03f678:	45020004 */ 	bc1fl	.L0f03f68c
/*  f03f67c:	8fa20194 */ 	lw	$v0,0x194($sp)
/*  f03f680:	c4288fc8 */ 	lwc1	$f8,%lo(var7f1a8fc8)($at)
/*  f03f684:	46088401 */ 	sub.s	$f16,$f16,$f8
/*  f03f688:	8fa20194 */ 	lw	$v0,0x194($sp)
.L0f03f68c:
/*  f03f68c:	c5a6015c */ 	lwc1	$f6,0x15c($t5)
/*  f03f690:	10400027 */ 	beqz	$v0,.L0f03f730
/*  f03f694:	46068400 */ 	add.s	$f16,$f16,$f6
/*  f03f698:	8dae0020 */ 	lw	$t6,0x20($t5)
/*  f03f69c:	8dcf0020 */ 	lw	$t7,0x20($t6)
/*  f03f6a0:	81f80008 */ 	lb	$t8,0x8($t7)
/*  f03f6a4:	53000014 */ 	beqzl	$t8,.L0f03f6f8
/*  f03f6a8:	c4400038 */ 	lwc1	$f0,0x38($v0)
/*  f03f6ac:	c4400038 */ 	lwc1	$f0,0x38($v0)
/*  f03f6b0:	46000007 */ 	neg.s	$f0,$f0
/*  f03f6b4:	4600803c */ 	c.lt.s	$f16,$f0
/*  f03f6b8:	00000000 */ 	nop
/*  f03f6bc:	45020005 */ 	bc1fl	.L0f03f6d4
/*  f03f6c0:	c440003c */ 	lwc1	$f0,0x3c($v0)
/*  f03f6c4:	46000406 */ 	mov.s	$f16,$f0
/*  f03f6c8:	10000019 */ 	b	.L0f03f730
/*  f03f6cc:	afa0017c */ 	sw	$zero,0x17c($sp)
/*  f03f6d0:	c440003c */ 	lwc1	$f0,0x3c($v0)
.L0f03f6d4:
/*  f03f6d4:	46000007 */ 	neg.s	$f0,$f0
/*  f03f6d8:	4610003c */ 	c.lt.s	$f0,$f16
/*  f03f6dc:	00000000 */ 	nop
/*  f03f6e0:	45020014 */ 	bc1fl	.L0f03f734
/*  f03f6e4:	c7a4018c */ 	lwc1	$f4,0x18c($sp)
/*  f03f6e8:	46000406 */ 	mov.s	$f16,$f0
/*  f03f6ec:	10000010 */ 	b	.L0f03f730
/*  f03f6f0:	afa0017c */ 	sw	$zero,0x17c($sp)
/*  f03f6f4:	c4400038 */ 	lwc1	$f0,0x38($v0)
.L0f03f6f8:
/*  f03f6f8:	4610003c */ 	c.lt.s	$f0,$f16
/*  f03f6fc:	00000000 */ 	nop
/*  f03f700:	45020005 */ 	bc1fl	.L0f03f718
/*  f03f704:	c440003c */ 	lwc1	$f0,0x3c($v0)
/*  f03f708:	46000406 */ 	mov.s	$f16,$f0
/*  f03f70c:	10000008 */ 	b	.L0f03f730
/*  f03f710:	afa0017c */ 	sw	$zero,0x17c($sp)
/*  f03f714:	c440003c */ 	lwc1	$f0,0x3c($v0)
.L0f03f718:
/*  f03f718:	4600803c */ 	c.lt.s	$f16,$f0
/*  f03f71c:	00000000 */ 	nop
/*  f03f720:	45020004 */ 	bc1fl	.L0f03f734
/*  f03f724:	c7a4018c */ 	lwc1	$f4,0x18c($sp)
/*  f03f728:	46000406 */ 	mov.s	$f16,$f0
/*  f03f72c:	afa0017c */ 	sw	$zero,0x17c($sp)
.L0f03f730:
/*  f03f730:	c7a4018c */ 	lwc1	$f4,0x18c($sp)
.L0f03f734:
/*  f03f734:	8fa40190 */ 	lw	$a0,0x190($sp)
/*  f03f738:	8fa50194 */ 	lw	$a1,0x194($sp)
/*  f03f73c:	8fa60198 */ 	lw	$a2,0x198($sp)
/*  f03f740:	8fa7019c */ 	lw	$a3,0x19c($sp)
/*  f03f744:	e7b00188 */ 	swc1	$f16,0x188($sp)
/*  f03f748:	0fc0fdde */ 	jal	chrCalculateAimEndProperties
/*  f03f74c:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*  f03f750:	8fac0190 */ 	lw	$t4,0x190($sp)
/*  f03f754:	c7b00188 */ 	lwc1	$f16,0x188($sp)
/*  f03f758:	2419000a */ 	addiu	$t9,$zero,0xa
/*  f03f75c:	a199000e */ 	sb	$t9,0xe($t4)
/*  f03f760:	e590016c */ 	swc1	$f16,0x16c($t4)
/*  f03f764:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f03f768:	8fa2017c */ 	lw	$v0,0x17c($sp)
/*  f03f76c:	27bd0190 */ 	addiu	$sp,$sp,0x190
/*  f03f770:	03e00008 */ 	jr	$ra
/*  f03f774:	00000000 */ 	nop
);

void chrCalculateAimEndProperties(struct chrdata *chr, struct attackanimconfig *animcfg, bool hasleftgun, bool hasrightgun, f32 shootrotx)
{
	f32 aimfreeshoulder = 0;
	f32 aimendback = 0;
	f32 aimgunshoulder = shootrotx;

	if (animcfg != NULL) {
		if (shootrotx > animcfg->unk30) {
			aimendback = shootrotx - animcfg->unk30;
			aimgunshoulder = animcfg->unk30;
		} else if (shootrotx < animcfg->unk34) {
			aimendback = shootrotx - animcfg->unk34;
			aimgunshoulder = animcfg->unk34;
		}

		if (aimgunshoulder > 0) {
			aimfreeshoulder = animcfg->unk40 * aimgunshoulder;
		} else {
			aimfreeshoulder = animcfg->unk44 * aimgunshoulder;
		}
	}

	if (hasrightgun) {
		chr->aimendrshoulder = aimgunshoulder;

		if (hasleftgun) {
			chr->aimendlshoulder = aimgunshoulder;
		} else {
			chr->aimendlshoulder = aimfreeshoulder;
		}
	} else {
		chr->aimendrshoulder = aimfreeshoulder;
		chr->aimendlshoulder = aimgunshoulder;
	}

	chr->aimendback = aimendback;
}

void chrResetAimEndProperties(struct chrdata *chr)
{
	chr->aimendcount = 10;
	chr->aimendrshoulder = 0;
	chr->aimendlshoulder = 0;
	chr->aimendback = 0;
	chr->aimendsideback = 0;
}

void chrSetFiring(struct chrdata *chr, s32 hand, bool firing)
{
	struct prop *prop = chrGetHeldProp(chr, hand);

	chr->prop->forcetick = firing ? true : false;

	if (prop) {
		weaponSetGunfireVisible(prop, firing, chr->prop->rooms[0]);
	}
}

bool chrIsGunfireVisible(struct chrdata *chr, s32 hand)
{
	struct prop *prop = chrGetHeldProp(chr, hand);

	if (prop) {
		return weaponIsGunfireVisible(prop);
	}

	return false;
}

void chrStopFiring(struct chrdata *chr)
{
	u8 race = CHRRACE(chr);

	if (race != RACE_DRCAROLL && race != RACE_EYESPY && chr->aibot == NULL) {
		chrSetFiring(chr, HAND_RIGHT, false);
		chrSetFiring(chr, HAND_LEFT, false);

		chrResetAimEndProperties(chr);

		chr->fireslots[0] = bgunFreeFireslot(chr->fireslots[0]);
		chr->fireslots[1] = bgunFreeFireslot(chr->fireslots[1]);
	}
}

void chrSetHandFiring(struct chrdata *chr, s32 hand, bool firing)
{
	if (firing) {
		if (hand == HAND_LEFT) {
			chr->hidden |= CHRHFLAG_FIRINGLEFT;
		} else {
			chr->hidden |= CHRHFLAG_FIRINGRIGHT;
		}
	} else {
		if (hand == HAND_LEFT) {
			chr->hidden &= ~CHRHFLAG_FIRINGLEFT;
		} else {
			chr->hidden &= ~CHRHFLAG_FIRINGRIGHT;
		}
	}

	if (!firing) {
		chrSetFiring(chr, hand, false);
	}
}

f32 chrGetAimLimitAngle(f32 sqdist)
{
	if (sqdist > 1600 * 1600) {
		return 0.018752790987492f;
	}

	if (sqdist > 800 * 800) {
		return 0.03761787340045f;
	}

	if (sqdist > 400 * 400) {
		return 0.07478791475296f;
	}

	if (sqdist > 200 * 200) {
		return 0.14957582950592f;
	}

	return 0.2512874007225f;
}

/**
 * Calculate whether a chr's shot hits their target on this tick.
 *
 * Each chr maintains a shotbondsum property which is a float ranging from
 * 0 to 1. Each time this function is called, the value is increased slightly
 * based on the chr's accuracy and other factors. Once it reaches 1, the target
 * is considered to be hit and the value is reset to 0.
 *
 * The function writes to the angleokptr argument if the angle to their target
 * is within range, and writes to the hit argument to indicate if the target is
 * being hit or not.
 */
void chrCalculateHit(struct chrdata *chr, bool *angleokptr, bool *hit, struct gset *gset)
{
	struct prop *prop;
	struct prop *target;
	f32 xdist;
	f32 ydist;
	f32 zdist;
	f32 angletotarget;
	f32 angleaiming;
	f32 anglediff;
	f32 limitangle;
	bool angleok;
	u32 stack;
	f32 taperdist;
	f32 sqdist;

	taperdist = 300;

	// Check that the chr's aim angle is within an acceptable range to their
	// target.
	prop = chr->prop;
	target = chrGetTargetProp(chr);

	xdist = target->pos.x - prop->pos.x;
	ydist = target->pos.y - prop->pos.y;
	zdist = target->pos.z - prop->pos.z;

	angletotarget = atan2f(xdist, zdist);
	angleaiming = chrGetAimAngle(chr);
	anglediff = angletotarget - angleaiming;

	sqdist = xdist * xdist + ydist * ydist + zdist * zdist;
	limitangle = chrGetAimLimitAngle(sqdist);

	if (anglediff < 0) {
		anglediff += M_BADTAU;
	}

	angleok = anglediff < limitangle || anglediff > M_BADTAU - limitangle;

	*angleokptr = angleok;
	*hit = false;

	// Determine the distance at which accuracy starts to taper off
	switch (gset->weaponnum) {
	case WEAPON_FALCON2:
	case WEAPON_FALCON2_SILENCER:
	case WEAPON_MAULER:
	case WEAPON_PHOENIX:
	case WEAPON_DY357MAGNUM:
	case WEAPON_DY357LX:
	case WEAPON_CMP150:
	case WEAPON_CYCLONE:
	case WEAPON_CALLISTO:
	case WEAPON_RCP120:
	case WEAPON_LAPTOPGUN:
	case WEAPON_DRAGON:
	case WEAPON_K7AVENGER:
	case WEAPON_AR34:
	case WEAPON_SUPERDRAGON:
	case WEAPON_SHOTGUN:
	case WEAPON_REAPER:
	case WEAPON_DEVASTATOR:
	case WEAPON_ROCKETLAUNCHER:
	case WEAPON_SLAYER:
	case WEAPON_COMBATKNIFE:
	case WEAPON_CROSSBOW:
	case WEAPON_TRANQUILIZER:
	case WEAPON_LASER:
	case WEAPON_GRENADE:
	case WEAPON_NBOMB:
	case WEAPON_TIMEDMINE:
	case WEAPON_PROXIMITYMINE:
	case WEAPON_REMOTEMINE:
	case WEAPON_COMBATBOOST:
	case WEAPON_PP9I:
	case WEAPON_CC13:
	case WEAPON_KL01313:
	case WEAPON_KF7SPECIAL:
	case WEAPON_ZZT:
	case WEAPON_DMC:
	case WEAPON_AR53:
	case WEAPON_RCP45:
	case WEAPON_PSYCHOSISGUN:
	default:
		// Use default distance (300)
		break;
	case WEAPON_FALCON2_SCOPE:
	case WEAPON_MAGSEC4:
		taperdist = 600;
		break;
	case WEAPON_SNIPERRIFLE:
	case WEAPON_FARSIGHT:
		taperdist = 1200;
		break;
	}

	if (angleok) {
		f32 dist = sqrtf(xdist * xdist + ydist * ydist + zdist * zdist);
		f32 accuracy = 0.16f;

		// Decrease accuracy if further than taperdist
		if (dist > taperdist) {
			accuracy *= taperdist / dist;
		}

		// Scale accuracy up or down based on chr's accuracyrating
		if (chr->accuracyrating > 0) {
			accuracy *= 1 + chr->accuracyrating * 0.1f;
		} else if (chr->accuracyrating < 0) {
			if (chr->accuracyrating <= -100) {
				accuracy = 0;
			} else {
				accuracy *= (chr->accuracyrating + 100) * 0.01f;
			}
		}

		// Apply PD mode enemy accuracy setting (default 1 which is no op)
		if (pdmodeGetEnemyAccuracy() <= 1) {
			accuracy *= pdmodeGetEnemyAccuracy();
		} else {
			accuracy *= 9 / (10.001f - pdmodeGetEnemyAccuracy());
		}

		// Apply difficulty multiplier (solo A = 0.6, SA = 0.8, PA = 1.175)
		accuracy *= g_EnemyAccuracyScale;

		// If the weapon fires more than once per tick, double the value to
		// account for it. No weapons meet this criteria, however.
		if (weaponGetNumTicksPerShot(gset->weaponnum, gset->weaponfunc) <= 0) {
			accuracy += accuracy;
		}

		// Shotgun doubles the value due to more bullets
		if (gset->weaponnum == WEAPON_SHOTGUN) {
			accuracy += accuracy;
		}

		chr->shotbondsum += accuracy;

		if (chr->hidden & CHRHFLAG_PERFECTACCURACY) {
			chr->shotbondsum += 1.1f;
		}

		if (chr->shotbondsum >= 1) {
			*hit = true;
			chr->shotbondsum = 0;
		}
	}
}

bool func0f03fde4(struct chrdata *chr, s32 handnum, struct coord *arg2)
{
	struct prop *weaponprop = chrGetHeldProp(chr, handnum);
	struct defaultobj *obj;
	struct model *model;
	bool result = false;
	struct modelnode *part0;
	struct modelnode *part1;
	Mtxf *spac;
	Mtxf sp6c;
	struct modelrodata_gunfire *rodata;
	Mtxf *sp64;
	Mtxf sp24;

	if (weaponprop) {
		obj = weaponprop->obj;
		model = obj->model;

		if ((chr->prop->flags & PROPFLAG_ONTHISSCREENTHISTICK) && (weaponprop->flags & PROPFLAG_ONTHISSCREENTHISTICK)) {
			if ((part0 = modelGetPart(model->filedata, MODELPART_0000))) {
				spac = model0001a5cc(model, part0, 0);
				rodata = &part0->rodata->gunfire;

				arg2->x = rodata->pos.x;
				arg2->y = rodata->pos.y;
				arg2->z = rodata->pos.z;

				mtx00015be4(currentPlayerGetUnk174c(), spac, &sp6c);
				mtx4TransformVecInPlace(&sp6c, arg2);
				result = true;
			} else if ((part1 = modelGetPart(model->filedata, MODELPART_0001))) {
				sp64 = model0001a5cc(model, part1, 0);

				mtx00015be4(currentPlayerGetUnk174c(), sp64, &sp24);

				arg2->x = sp24.m[3][0];
				arg2->y = sp24.m[3][1];
				arg2->z = sp24.m[3][2];

				result = true;
			}
		}
	}

	return result;
}

/**
 * For a shielded chr, determine which model node has been shot and populate the
 * last 4 pointer arguments with information about the hit.
 *
 * Shield hits are calculated using the bounding box of each body part.
 * This gives a bit of padding around the chr which can register as a hit.
 *
 * nodeptr    - will be populated with a pointer to the bbox model node.
 * hitpartptr - will be populated with the HITPART constant value.
 * modelptr   - will be populated with a pointer to the chr's model.
 * sideptr    - will be populated with an index in the range 0-5 which
 *              represents which side of the node's bounding box was hit.
 */
void chrCalculateShieldHit(struct chrdata *chr, struct coord *pos, struct coord *vector,
		struct modelnode **nodeptr, s32 *hitpartptr, struct model **modelptr, s32 *sideptr)
{
	u32 stack1;
	struct prop *prop = chr->prop;
	bool done = false;
	bool isdifferentmtx;
	struct coord sp124;
	struct coord sp118;
	s32 i;
	struct modelnode *bestnode;
	u32 stack2[2];
	Mtxf spc8;
	f32 bestvolume;
	Mtxf *lVar4;
	struct modelnode *node;
	f32 x;
	f32 y;
	f32 z;
	f32 volume;
	Mtxf *mtxptr1;
	Mtxf *mtxptr2;
	f32 sides[6];
	u32 stack3;

	if (prop->type != PROPTYPE_PLAYER || g_Vars.normmplayerisrunning || chrGetShield(chr) > 0) {
		if (prop->flags & (PROPFLAG_ONTHISSCREENTHISTICK | PROPFLAG_ONANYSCREENTHISTICK | PROPFLAG_ONANYSCREENPREVTICK)) {
			bestnode = NULL;
			bestvolume = MAXFLOAT;
			lVar4 = func0f0b5050(chr->model->matrices);

			if (lVar4) {
				mtx4TransformVec(lVar4, pos, &sp124);
				mtx4RotateVec(lVar4, vector, &sp118);

				isdifferentmtx = (currentPlayerGetMatrix1740() != lVar4);
				node = chr->model->filedata->rootnode;

				while (node) {
					if ((node->type & 0xff) == MODELNODETYPE_BBOX) {
						mtxptr1 = model0001a5cc(chr->model, node, 0);

						if (isdifferentmtx) {
							mtx00016798(mtxptr1, &spc8);
							mtxptr1 = &spc8;
						}

						x = mtxptr1->m[3][0] - sp124.f[0];
						y = mtxptr1->m[3][1] - sp124.f[1];
						z = mtxptr1->m[3][2] - sp124.f[2];

						volume = x * x + y * y + z * z;

						if (volume < bestvolume) {
							bestvolume = volume;
							bestnode = node;
						}
					}

					// Iterate all nodes recursively except headspot's chidlren
					if (node->child && (node->type & 0xff) != MODELNODETYPE_HEADSPOT) {
						node = node->child;
					} else {
						while (node) {
							if (node->next) {
								node = node->next;
								break;
							}

							node = node->parent;
						}
					}
				}

				if (bestvolume);

#if VERSION >= VERSION_NTSC_1_0
				if (bestnode != NULL)
#endif
				{
					Mtxf sp48;
					struct modelrodata_bbox *rodata = &bestnode->rodata->bbox;

					*hitpartptr = rodata->hitpart;
					*nodeptr = bestnode;
					*modelptr = chr->model;
					*sideptr = 0;

					mtxptr2 = model0001a5cc(chr->model, bestnode, 0);

					if (isdifferentmtx) {
						mtx00016798(mtxptr2, &sp48);
						mtxptr2 = &sp48;
					}

					bestvolume = -2;

					x = (sp118.f[0] * mtxptr2->m[0][0]) + (sp118.f[1] * mtxptr2->m[0][1]) + (sp118.f[2] * mtxptr2->m[0][2]);
					y = (sp118.f[0] * mtxptr2->m[1][0]) + (sp118.f[1] * mtxptr2->m[1][1]) + (sp118.f[2] * mtxptr2->m[1][2]);
					z = (sp118.f[0] * mtxptr2->m[2][0]) + (sp118.f[1] * mtxptr2->m[2][1]) + (sp118.f[2] * mtxptr2->m[2][2]);

					sides[0] = x;
					sides[1] = -x;
					sides[2] = y;
					sides[3] = -y;
					sides[4] = z;
					sides[5] = -z;

					for (i = 0; i < 6; i++) {
						if (sides[i] > bestvolume) {
							bestvolume = sides[i];
							*sideptr = i;
						}
					}

					done = true;
				}
			}
		}

		// If no node was found above, search the model for the torso bbox
		// and return that.
		if (!done) {
			node = chr->model->filedata->rootnode;

			while (node) {

				if ((node->type & 0xff) == MODELNODETYPE_BBOX) {
					struct modelrodata_bbox *rodata = &node->rodata->bbox;

					if (rodata->hitpart == HITPART_TORSO) {
						*hitpartptr = rodata->hitpart;
						*nodeptr = node;
						*modelptr = chr->model;
						*sideptr = 0;
						return;
					}
				}

				if (node->child) {
					node = node->child;
				} else {
					while (node) {
						if (node->next) {
							node = node->next;
							break;
						}

						node = node->parent;
					}
				}
			}
		}
	}
}

/**
 * Sets the speed and trajectory for some thrown items. Specifically, for bots
 * throwing grenades, and maybe other things.
 */
void func0f04031c(struct coord *frompos, f32 arg1, struct coord *aimpos, struct coord *arg3)
{
	f32 xvel;
	f32 yvel;
	f32 zvel;
	f32 latvel;
	f32 vel;
	f32 sp40;
	f32 sp3c;
	f32 sp38;
	f32 sp30;
	f32 sp2c;
	f32 sp24;
	f32 sp28;
	f32 sp20;

	arg1 *= 0.59999999f;

	xvel = (aimpos->x - frompos->x) * 0.01f;
	yvel = (aimpos->y - frompos->y) * 0.01f;
	zvel = (aimpos->z - frompos->z) * 0.01f;

	vel = sqrtf(xvel * xvel + yvel * yvel + zvel * zvel);
	latvel = sqrtf(xvel * xvel + zvel * zvel);
	sp38 = latvel / vel;
	sp40 = func0f0969d0(sp38);

	if (yvel < 0) {
		sp40 = -sp40;
	}

	sp2c = (vel * 9.81f * sp38 * sp38) / (arg1 * arg1) + yvel / vel;

	if (sp2c < -1) {
		sp2c = -1;
	} else if (sp2c > 1) {
		sp2c = 1;
	}

	sp3c = (func0f096a7c(sp2c) - sp40) * 0.5f + sp40;
	sp28 = cosf(sp3c);
	sp30 = sinf(sp3c);

	arg3->x = xvel / latvel * sp28;
	arg3->y = sp30;
	arg3->z = zvel / latvel * sp28;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f0404d4
.late_rodata
glabel var7f1a90c8
.word 0x3d888889
glabel var7f1a90cc
.word 0x481c4000
glabel var7f1a90d0
.word 0x3fd55555
glabel var7f1a90d4
.word 0x3fd55555
glabel var7f1a90d8
.word 0x3fd55555
glabel var7f1a90dc
.word 0x461c4000
glabel var7f1a90e0
.word func0f0404d4+0x14fc
glabel var7f1a90e4
.word func0f0404d4+0x14fc
glabel var7f1a90e8
.word func0f0404d4+0x14fc
glabel var7f1a90ec
.word func0f0404d4+0x14fc
glabel var7f1a90f0
.word func0f0404d4+0x14fc
glabel var7f1a90f4
.word func0f0404d4+0x14fc
glabel var7f1a90f8
.word func0f0404d4+0x14fc
glabel var7f1a90fc
.word func0f0404d4+0x14fc
glabel var7f1a9100
.word func0f0404d4+0x14fc
glabel var7f1a9104
.word func0f0404d4+0x14fc
glabel var7f1a9108
.word func0f0404d4+0x14fc
glabel var7f1a910c
.word func0f0404d4+0x14fc
glabel var7f1a9110
.word func0f0404d4+0x14fc
glabel var7f1a9114
.word func0f0404d4+0x14fc
glabel var7f1a9118
.word func0f0404d4+0x14fc
glabel var7f1a911c
.word func0f0404d4+0x14fc
glabel var7f1a9120
.word func0f0404d4+0x14fc
glabel var7f1a9124
.word func0f0404d4+0x1508
glabel var7f1a9128
.word func0f0404d4+0x14fc
glabel var7f1a912c
.word func0f0404d4+0x14fc
glabel var7f1a9130
.word func0f0404d4+0x14fc
glabel var7f1a9134
.word func0f0404d4+0x1508
glabel var7f1a9138
.word func0f0404d4+0x1508
glabel var7f1a913c
.word func0f0404d4+0x1508
glabel var7f1a9140
.word func0f0404d4+0x1508
glabel var7f1a9144
.word func0f0404d4+0x1508
glabel var7f1a9148
.word func0f0404d4+0x14fc
glabel var7f1a914c
.word func0f0404d4+0x14fc
glabel var7f1a9150
.word func0f0404d4+0x1508
glabel var7f1a9154
.word func0f0404d4+0x1508
glabel var7f1a9158
.word func0f0404d4+0x1508
glabel var7f1a915c
.word func0f0404d4+0x1508
glabel var7f1a9160
.word func0f0404d4+0x1508
glabel var7f1a9164
.word func0f0404d4+0x1508
glabel var7f1a9168
.word func0f0404d4+0x14fc
glabel var7f1a916c
.word func0f0404d4+0x14fc
glabel var7f1a9170
.word func0f0404d4+0x14fc
glabel var7f1a9174
.word func0f0404d4+0x14fc
glabel var7f1a9178
.word func0f0404d4+0x14fc
glabel var7f1a917c
.word func0f0404d4+0x14fc
glabel var7f1a9180
.word func0f0404d4+0x14fc
glabel var7f1a9184
.word func0f0404d4+0x14fc
.text
/*  f040658:	27bdfd88 */ 	addiu	$sp,$sp,-632
/*  f04065c:	afbf0044 */ 	sw	$ra,0x44($sp)
/*  f040660:	afa5027c */ 	sw	$a1,0x27c($sp)
/*  f040664:	8c8e001c */ 	lw	$t6,0x1c($a0)
/*  f040668:	240f0001 */ 	li	$t7,0x1
/*  f04066c:	a3af026e */ 	sb	$t7,0x26e($sp)
/*  f040670:	afae0274 */ 	sw	$t6,0x274($sp)
/*  f040674:	8c9802d4 */ 	lw	$t8,0x2d4($a0)
/*  f040678:	00001025 */ 	move	$v0,$zero
/*  f04067c:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f040680:	53000003 */ 	beqzl	$t8,.PF0f040690
/*  f040684:	a3a2026f */ 	sb	$v0,0x26f($sp)
/*  f040688:	24020001 */ 	li	$v0,0x1
/*  f04068c:	a3a2026f */ 	sb	$v0,0x26f($sp)
.PF0f040690:
/*  f040690:	0fc0a252 */ 	jal	chrGetHeldProp
/*  f040694:	afa40278 */ 	sw	$a0,0x278($sp)
/*  f040698:	5040055c */ 	beqzl	$v0,.PF0f041c0c
/*  f04069c:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*  f0406a0:	afa00268 */ 	sw	$zero,0x268($sp)
/*  f0406a4:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f0406a8:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0406ac:	0fc0a26a */ 	jal	chrGetTargetProp
/*  f0406b0:	afb90264 */ 	sw	$t9,0x264($sp)
/*  f0406b4:	8fab0264 */ 	lw	$t3,0x264($sp)
/*  f0406b8:	afa2025c */ 	sw	$v0,0x25c($sp)
/*  f0406bc:	8fa70278 */ 	lw	$a3,0x278($sp)
/*  f0406c0:	8961005c */ 	lwl	$at,0x5c($t3)
/*  f0406c4:	9961005f */ 	lwr	$at,0x5f($t3)
/*  f0406c8:	27aa0260 */ 	addiu	$t2,$sp,0x260
/*  f0406cc:	24080200 */ 	li	$t0,0x200
/*  f0406d0:	ad410000 */ 	sw	$at,0x0($t2)
/*  f0406d4:	80e30007 */ 	lb	$v1,0x7($a3)
/*  f0406d8:	24010008 */ 	li	$at,0x8
/*  f0406dc:	10610007 */ 	beq	$v1,$at,.PF0f0406fc
/*  f0406e0:	2401001b */ 	li	$at,0x1b
/*  f0406e4:	10610005 */ 	beq	$v1,$at,.PF0f0406fc
/*  f0406e8:	2401001c */ 	li	$at,0x1c
/*  f0406ec:	10610003 */ 	beq	$v1,$at,.PF0f0406fc
/*  f0406f0:	2401001d */ 	li	$at,0x1d
/*  f0406f4:	54610003 */ 	bnel	$v1,$at,.PF0f040704
/*  f0406f8:	afa00250 */ 	sw	$zero,0x250($sp)
.PF0f0406fc:
/*  f0406fc:	8ce8004c */ 	lw	$t0,0x4c($a3)
/*  f040700:	afa00250 */ 	sw	$zero,0x250($sp)
.PF0f040704:
/*  f040704:	afa00224 */ 	sw	$zero,0x224($sp)
/*  f040708:	afa00210 */ 	sw	$zero,0x210($sp)
/*  f04070c:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040710:	93a50263 */ 	lbu	$a1,0x263($sp)
/*  f040714:	afa00254 */ 	sw	$zero,0x254($sp)
/*  f040718:	0fc2c8f8 */ 	jal	weaponGetNumTicksPerShot
/*  f04071c:	afa80258 */ 	sw	$t0,0x258($sp)
/*  f040720:	8fa60254 */ 	lw	$a2,0x254($sp)
/*  f040724:	1c400005 */ 	bgtz	$v0,.PF0f04073c
/*  f040728:	00402025 */ 	move	$a0,$v0
/*  f04072c:	240f0001 */ 	li	$t7,0x1
/*  f040730:	24060001 */ 	li	$a2,0x1
/*  f040734:	10000055 */ 	b	.PF0f04088c
/*  f040738:	afaf0250 */ 	sw	$t7,0x250($sp)
.PF0f04073c:
/*  f04073c:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f040740:	8f0302d4 */ 	lw	$v1,0x2d4($t8)
/*  f040744:	5060001d */ 	beqzl	$v1,.PF0f0407bc
/*  f040748:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f04074c:	8c790020 */ 	lw	$t9,0x20($v1)
/*  f040750:	24010014 */ 	li	$at,0x14
/*  f040754:	57210019 */ 	bnel	$t9,$at,.PF0f0407bc
/*  f040758:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f04075c:	8c6d004c */ 	lw	$t5,0x4c($v1)
/*  f040760:	8fab027c */ 	lw	$t3,0x27c($sp)
/*  f040764:	000d5080 */ 	sll	$t2,$t5,0x2
/*  f040768:	05400013 */ 	bltz	$t2,.PF0f0407b8
/*  f04076c:	000b7040 */ 	sll	$t6,$t3,0x1
/*  f040770:	006e7821 */ 	addu	$t7,$v1,$t6
/*  f040774:	85f800e0 */ 	lh	$t8,0xe0($t7)
/*  f040778:	2419004b */ 	li	$t9,0x4b
/*  f04077c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f040780:	03386823 */ 	subu	$t5,$t9,$t8
/*  f040784:	448d2000 */ 	mtc1	$t5,$f4
/*  f040788:	c428a32c */ 	lwc1	$f8,-0x5cd4($at)
/*  f04078c:	44825000 */ 	mtc1	$v0,$f10
/*  f040790:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f040794:	3c013f80 */ 	lui	$at,0x3f80
/*  f040798:	44819000 */ 	mtc1	$at,$f18
/*  f04079c:	46805420 */ 	cvt.s.w	$f16,$f10
/*  f0407a0:	46083002 */ 	mul.s	$f0,$f6,$f8
/*  f0407a4:	46009100 */ 	add.s	$f4,$f18,$f0
/*  f0407a8:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f0407ac:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f0407b0:	44044000 */ 	mfc1	$a0,$f8
/*  f0407b4:	00000000 */ 	nop
.PF0f0407b8:
/*  f0407b8:	8faa0278 */ 	lw	$t2,0x278($sp)
.PF0f0407bc:
/*  f0407bc:	8fab027c */ 	lw	$t3,0x27c($sp)
/*  f0407c0:	3c0f800a */ 	lui	$t7,0x800a
/*  f0407c4:	8defa548 */ 	lw	$t7,-0x5ab8($t7)
/*  f0407c8:	014b1821 */ 	addu	$v1,$t2,$t3
/*  f0407cc:	906e0004 */ 	lbu	$t6,0x4($v1)
/*  f0407d0:	01cfc821 */ 	addu	$t9,$t6,$t7
/*  f0407d4:	333800ff */ 	andi	$t8,$t9,0xff
/*  f0407d8:	0304082a */ 	slt	$at,$t8,$a0
/*  f0407dc:	1420002b */ 	bnez	$at,.PF0f04088c
/*  f0407e0:	a0790004 */ 	sb	$t9,0x4($v1)
/*  f0407e4:	a0600004 */ 	sb	$zero,0x4($v1)
/*  f0407e8:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f0407ec:	8fad027c */ 	lw	$t5,0x27c($sp)
/*  f0407f0:	240c0001 */ 	li	$t4,0x1
/*  f0407f4:	8d4b032c */ 	lw	$t3,0x32c($t2)
/*  f0407f8:	01ac1004 */ 	sllv	$v0,$t4,$t5
/*  f0407fc:	24060001 */ 	li	$a2,0x1
/*  f040800:	000b7300 */ 	sll	$t6,$t3,0xc
/*  f040804:	914b032d */ 	lbu	$t3,0x32d($t2)
/*  f040808:	000e7f82 */ 	srl	$t7,$t6,0x1e
/*  f04080c:	01e2c026 */ 	xor	$t8,$t7,$v0
/*  f040810:	00186080 */ 	sll	$t4,$t8,0x2
/*  f040814:	318d000c */ 	andi	$t5,$t4,0xc
/*  f040818:	316efff3 */ 	andi	$t6,$t3,0xfff3
/*  f04081c:	01ae7825 */ 	or	$t7,$t5,$t6
/*  f040820:	a14f032d */ 	sb	$t7,0x32d($t2)
/*  f040824:	8d59032c */ 	lw	$t9,0x32c($t2)
/*  f040828:	93ad0260 */ 	lbu	$t5,0x260($sp)
/*  f04082c:	2401001d */ 	li	$at,0x1d
/*  f040830:	0019c300 */ 	sll	$t8,$t9,0xc
/*  f040834:	00186782 */ 	srl	$t4,$t8,0x1e
/*  f040838:	01825824 */ 	and	$t3,$t4,$v0
/*  f04083c:	15600003 */ 	bnez	$t3,.PF0f04084c
/*  f040840:	240e0001 */ 	li	$t6,0x1
/*  f040844:	55a10003 */ 	bnel	$t5,$at,.PF0f040854
/*  f040848:	8faf0278 */ 	lw	$t7,0x278($sp)
.PF0f04084c:
/*  f04084c:	afae0250 */ 	sw	$t6,0x250($sp)
/*  f040850:	8faf0278 */ 	lw	$t7,0x278($sp)
.PF0f040854:
/*  f040854:	24010008 */ 	li	$at,0x8
/*  f040858:	81ea0007 */ 	lb	$t2,0x7($t7)
/*  f04085c:	1541000b */ 	bne	$t2,$at,.PF0f04088c
/*  f040860:	00000000 */ 	nop
/*  f040864:	8de40020 */ 	lw	$a0,0x20($t7)
/*  f040868:	0c0073c3 */ 	jal	modelGetAnimNum
/*  f04086c:	afa60254 */ 	sw	$a2,0x254($sp)
/*  f040870:	2401026a */ 	li	$at,0x26a
/*  f040874:	14410005 */ 	bne	$v0,$at,.PF0f04088c
/*  f040878:	8fa60254 */ 	lw	$a2,0x254($sp)
/*  f04087c:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f040880:	83380033 */ 	lb	$t8,0x33($t9)
/*  f040884:	270c0001 */ 	addiu	$t4,$t8,0x1
/*  f040888:	a32c0033 */ 	sb	$t4,0x33($t9)
.PF0f04088c:
/*  f04088c:	50c004a3 */ 	beqzl	$a2,.PF0f041b1c
/*  f040890:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f040894:	0fc0f9dd */ 	jal	chrGetAimAngle
/*  f040898:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f04089c:	e7a00204 */ 	swc1	$f0,0x204($sp)
/*  f0408a0:	0fc0fa36 */ 	jal	func0f03e754
/*  f0408a4:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0408a8:	93ab026f */ 	lbu	$t3,0x26f($sp)
/*  f0408ac:	e7a00200 */ 	swc1	$f0,0x200($sp)
/*  f0408b0:	240e0001 */ 	li	$t6,0x1
/*  f0408b4:	11600004 */ 	beqz	$t3,.PF0f0408c8
/*  f0408b8:	27a60244 */ 	addiu	$a2,$sp,0x244
/*  f0408bc:	240d0004 */ 	li	$t5,0x4
/*  f0408c0:	10000002 */ 	b	.PF0f0408cc
/*  f0408c4:	afad01fc */ 	sw	$t5,0x1fc($sp)
.PF0f0408c8:
/*  f0408c8:	afa001fc */ 	sw	$zero,0x1fc($sp)
.PF0f0408cc:
/*  f0408cc:	afae0268 */ 	sw	$t6,0x268($sp)
/*  f0408d0:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0408d4:	0fc0ffda */ 	jal	func0f03fde4
/*  f0408d8:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f0408dc:	54400032 */ 	bnezl	$v0,.PF0f0409a8
/*  f0408e0:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0408e4:	8fa20274 */ 	lw	$v0,0x274($sp)
/*  f0408e8:	3c0141f0 */ 	lui	$at,0x41f0
/*  f0408ec:	44818000 */ 	mtc1	$at,$f16
/*  f0408f0:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f0408f4:	8faa027c */ 	lw	$t2,0x27c($sp)
/*  f0408f8:	24010001 */ 	li	$at,0x1
/*  f0408fc:	e7aa0244 */ 	swc1	$f10,0x244($sp)
/*  f040900:	c452000c */ 	lwc1	$f18,0xc($v0)
/*  f040904:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f040908:	e7a40248 */ 	swc1	$f4,0x248($sp)
/*  f04090c:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f040910:	15410013 */ 	bne	$t2,$at,.PF0f040960
/*  f040914:	e7a6024c */ 	swc1	$f6,0x24c($sp)
/*  f040918:	0c006858 */ 	jal	cosf
/*  f04091c:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040920:	3c014120 */ 	lui	$at,0x4120
/*  f040924:	44815000 */ 	mtc1	$at,$f10
/*  f040928:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f04092c:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040930:	460a0482 */ 	mul.s	$f18,$f0,$f10
/*  f040934:	46124400 */ 	add.s	$f16,$f8,$f18
/*  f040938:	0c00685b */ 	jal	sinf
/*  f04093c:	e7b00244 */ 	swc1	$f16,0x244($sp)
/*  f040940:	3c014120 */ 	lui	$at,0x4120
/*  f040944:	44813000 */ 	mtc1	$at,$f6
/*  f040948:	46000107 */ 	neg.s	$f4,$f0
/*  f04094c:	c7a8024c */ 	lwc1	$f8,0x24c($sp)
/*  f040950:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f040954:	460a4480 */ 	add.s	$f18,$f8,$f10
/*  f040958:	10000012 */ 	b	.PF0f0409a4
/*  f04095c:	e7b2024c */ 	swc1	$f18,0x24c($sp)
.PF0f040960:
/*  f040960:	0c006858 */ 	jal	cosf
/*  f040964:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040968:	3c014120 */ 	lui	$at,0x4120
/*  f04096c:	44812000 */ 	mtc1	$at,$f4
/*  f040970:	46000407 */ 	neg.s	$f16,$f0
/*  f040974:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f040978:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f04097c:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040980:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f040984:	0c00685b */ 	jal	sinf
/*  f040988:	e7aa0244 */ 	swc1	$f10,0x244($sp)
/*  f04098c:	3c014120 */ 	lui	$at,0x4120
/*  f040990:	44818000 */ 	mtc1	$at,$f16
/*  f040994:	c7b2024c */ 	lwc1	$f18,0x24c($sp)
/*  f040998:	46100102 */ 	mul.s	$f4,$f0,$f16
/*  f04099c:	46049200 */ 	add.s	$f8,$f18,$f4
/*  f0409a0:	e7a8024c */ 	swc1	$f8,0x24c($sp)
.PF0f0409a4:
/*  f0409a4:	8fa40278 */ 	lw	$a0,0x278($sp)
.PF0f0409a8:
/*  f0409a8:	0fc07a37 */ 	jal	chrSetPerimEnabled
/*  f0409ac:	00002825 */ 	move	$a1,$zero
/*  f0409b0:	8fb801fc */ 	lw	$t8,0x1fc($sp)
/*  f0409b4:	8faf0274 */ 	lw	$t7,0x274($sp)
/*  f0409b8:	24190010 */ 	li	$t9,0x10
/*  f0409bc:	370c082a */ 	ori	$t4,$t8,0x82a
/*  f0409c0:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f0409c4:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f0409c8:	27a60244 */ 	addiu	$a2,$sp,0x244
/*  f0409cc:	27a70234 */ 	addiu	$a3,$sp,0x234
/*  f0409d0:	25e40008 */ 	addiu	$a0,$t7,0x8
/*  f0409d4:	0c00b5cd */ 	jal	cd0002de34
/*  f0409d8:	25e50028 */ 	addiu	$a1,$t7,0x28
/*  f0409dc:	14400002 */ 	bnez	$v0,.PF0f0409e8
/*  f0409e0:	24050001 */ 	li	$a1,0x1
/*  f0409e4:	afa00268 */ 	sw	$zero,0x268($sp)
.PF0f0409e8:
/*  f0409e8:	0fc07a37 */ 	jal	chrSetPerimEnabled
/*  f0409ec:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0409f0:	8fab0268 */ 	lw	$t3,0x268($sp)
/*  f0409f4:	240d0001 */ 	li	$t5,0x1
/*  f0409f8:	51600448 */ 	beqzl	$t3,.PF0f041b1c
/*  f0409fc:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f040a00:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f040a04:	afa001f8 */ 	sw	$zero,0x1f8($sp)
/*  f040a08:	afa001f4 */ 	sw	$zero,0x1f4($sp)
/*  f040a0c:	afad01f0 */ 	sw	$t5,0x1f0($sp)
/*  f040a10:	11c00004 */ 	beqz	$t6,.PF0f040a24
/*  f040a14:	afa001cc */ 	sw	$zero,0x1cc($sp)
/*  f040a18:	240a083f */ 	li	$t2,0x83f
/*  f040a1c:	10000003 */ 	b	.PF0f040a2c
/*  f040a20:	afaa01c8 */ 	sw	$t2,0x1c8($sp)
.PF0f040a24:
/*  f040a24:	240f083b */ 	li	$t7,0x83b
/*  f040a28:	afaf01c8 */ 	sw	$t7,0x1c8($sp)
.PF0f040a2c:
/*  f040a2c:	8fa7025c */ 	lw	$a3,0x25c($sp)
/*  f040a30:	8ce20004 */ 	lw	$v0,0x4($a3)
/*  f040a34:	50400004 */ 	beqzl	$v0,.PF0f040a48
/*  f040a38:	00004825 */ 	move	$t1,$zero
/*  f040a3c:	10000002 */ 	b	.PF0f040a48
/*  f040a40:	904902fe */ 	lbu	$t1,0x2fe($v0)
/*  f040a44:	00004825 */ 	move	$t1,$zero
.PF0f040a48:
/*  f040a48:	39220003 */ 	xori	$v0,$t1,0x3
/*  f040a4c:	2c420001 */ 	sltiu	$v0,$v0,0x1
/*  f040a50:	1040000f */ 	beqz	$v0,.PF0f040a90
/*  f040a54:	00401825 */ 	move	$v1,$v0
/*  f040a58:	afa2005c */ 	sw	$v0,0x5c($sp)
/*  f040a5c:	0fc124d8 */ 	jal	chrGetDistanceToTarget
/*  f040a60:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040a64:	3c014316 */ 	lui	$at,0x4316
/*  f040a68:	44813000 */ 	mtc1	$at,$f6
/*  f040a6c:	0000c025 */ 	move	$t8,$zero
/*  f040a70:	4600303c */ 	c.lt.s	$f6,$f0
/*  f040a74:	00000000 */ 	nop
/*  f040a78:	45020003 */ 	bc1fl	.PF0f040a88
/*  f040a7c:	afb8005c */ 	sw	$t8,0x5c($sp)
/*  f040a80:	24180001 */ 	li	$t8,0x1
/*  f040a84:	afb8005c */ 	sw	$t8,0x5c($sp)
.PF0f040a88:
/*  f040a88:	8fa7025c */ 	lw	$a3,0x25c($sp)
/*  f040a8c:	03001825 */ 	move	$v1,$t8
.PF0f040a90:
/*  f040a90:	afa301c0 */ 	sw	$v1,0x1c0($sp)
/*  f040a94:	10600016 */ 	beqz	$v1,.PF0f040af0
/*  f040a98:	afa001bc */ 	sw	$zero,0x1bc($sp)
/*  f040a9c:	c4ea0008 */ 	lwc1	$f10,0x8($a3)
/*  f040aa0:	c7b00244 */ 	lwc1	$f16,0x244($sp)
/*  f040aa4:	c7a80248 */ 	lwc1	$f8,0x248($sp)
/*  f040aa8:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f040aac:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f040ab0:	c7b0024c */ 	lwc1	$f16,0x24c($sp)
/*  f040ab4:	27a501e4 */ 	addiu	$a1,$sp,0x1e4
/*  f040ab8:	27a601e8 */ 	addiu	$a2,$sp,0x1e8
/*  f040abc:	e7b201e0 */ 	swc1	$f18,0x1e0($sp)
/*  f040ac0:	c4e4000c */ 	lwc1	$f4,0xc($a3)
/*  f040ac4:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f040ac8:	e7a601e4 */ 	swc1	$f6,0x1e4($sp)
/*  f040acc:	c4ea0010 */ 	lwc1	$f10,0x10($a3)
/*  f040ad0:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f040ad4:	0c0011d8 */ 	jal	guNormalize
/*  f040ad8:	e7b201e8 */ 	swc1	$f18,0x1e8($sp)
/*  f040adc:	8fa4025c */ 	lw	$a0,0x25c($sp)
/*  f040ae0:	0fc19102 */ 	jal	propSetPerimEnabled
/*  f040ae4:	24050001 */ 	li	$a1,0x1
/*  f040ae8:	1000002f */ 	b	.PF0f040ba8
/*  f040aec:	8fab0278 */ 	lw	$t3,0x278($sp)
.PF0f040af0:
/*  f040af0:	0c006858 */ 	jal	cosf
/*  f040af4:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040af8:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*  f040afc:	0c00685b */ 	jal	sinf
/*  f040b00:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040b04:	c7a40060 */ 	lwc1	$f4,0x60($sp)
/*  f040b08:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040b0c:	46040202 */ 	mul.s	$f8,$f0,$f4
/*  f040b10:	0c00685b */ 	jal	sinf
/*  f040b14:	e7a801e0 */ 	swc1	$f8,0x1e0($sp)
/*  f040b18:	e7a001e4 */ 	swc1	$f0,0x1e4($sp)
/*  f040b1c:	0c006858 */ 	jal	cosf
/*  f040b20:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040b24:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*  f040b28:	0c006858 */ 	jal	cosf
/*  f040b2c:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040b30:	c7a60060 */ 	lwc1	$f6,0x60($sp)
/*  f040b34:	93ac026f */ 	lbu	$t4,0x26f($sp)
/*  f040b38:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f040b3c:	11800019 */ 	beqz	$t4,.PF0f040ba4
/*  f040b40:	e7aa01e8 */ 	swc1	$f10,0x1e8($sp)
/*  f040b44:	0fc6492c */ 	jal	chrGuessCrouchPos
/*  f040b48:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040b4c:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f040b50:	00404825 */ 	move	$t1,$v0
/*  f040b54:	8fae0278 */ 	lw	$t6,0x278($sp)
/*  f040b58:	8f280170 */ 	lw	$t0,0x170($t9)
/*  f040b5c:	0008582b */ 	sltu	$t3,$zero,$t0
/*  f040b60:	11600004 */ 	beqz	$t3,.PF0f040b74
/*  f040b64:	01604025 */ 	move	$t0,$t3
/*  f040b68:	8f280174 */ 	lw	$t0,0x174($t9)
/*  f040b6c:	0008682b */ 	sltu	$t5,$zero,$t0
/*  f040b70:	01a04025 */ 	move	$t0,$t5
.PF0f040b74:
/*  f040b74:	8dc302d4 */ 	lw	$v1,0x2d4($t6)
/*  f040b78:	8fb8027c */ 	lw	$t8,0x27c($sp)
/*  f040b7c:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f040b80:	8c66004c */ 	lw	$a2,0x4c($v1)
/*  f040b84:	00786021 */ 	addu	$t4,$v1,$t8
/*  f040b88:	9187004d */ 	lbu	$a3,0x4d($t4)
/*  f040b8c:	8c650020 */ 	lw	$a1,0x20($v1)
/*  f040b90:	00065080 */ 	sll	$t2,$a2,0x2
/*  f040b94:	000a37c2 */ 	srl	$a2,$t2,0x1f
/*  f040b98:	afa80014 */ 	sw	$t0,0x14($sp)
/*  f040b9c:	0fc284b4 */ 	jal	bgun0f0a0fac
/*  f040ba0:	afa90010 */ 	sw	$t1,0x10($sp)
.PF0f040ba4:
/*  f040ba4:	8fab0278 */ 	lw	$t3,0x278($sp)
.PF0f040ba8:
/*  f040ba8:	93b90260 */ 	lbu	$t9,0x260($sp)
/*  f040bac:	24010016 */ 	li	$at,0x16
/*  f040bb0:	8d6302d4 */ 	lw	$v1,0x2d4($t3)
/*  f040bb4:	50600018 */ 	beqzl	$v1,.PF0f040c18
/*  f040bb8:	3c014780 */ 	lui	$at,0x4780
/*  f040bbc:	57210016 */ 	bnel	$t9,$at,.PF0f040c18
/*  f040bc0:	3c014780 */ 	lui	$at,0x4780
/*  f040bc4:	8c6d0128 */ 	lw	$t5,0x128($v1)
/*  f040bc8:	240e0001 */ 	li	$t6,0x1
/*  f040bcc:	01602025 */ 	move	$a0,$t3
/*  f040bd0:	15a00010 */ 	bnez	$t5,.PF0f040c14
/*  f040bd4:	00002825 */ 	move	$a1,$zero
/*  f040bd8:	afae0250 */ 	sw	$t6,0x250($sp)
/*  f040bdc:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f040be0:	0fc66c21 */ 	jal	aibotDoFarsightThing
/*  f040be4:	27a70244 */ 	addiu	$a3,$sp,0x244
/*  f040be8:	24010002 */ 	li	$at,0x2
/*  f040bec:	5441000a */ 	bnel	$v0,$at,.PF0f040c18
/*  f040bf0:	3c014780 */ 	lui	$at,0x4780
/*  f040bf4:	0c004ad4 */ 	jal	random
/*  f040bf8:	00000000 */ 	nop
/*  f040bfc:	240100ff */ 	li	$at,0xff
/*  f040c00:	0041001b */ 	divu	$zero,$v0,$at
/*  f040c04:	00005010 */ 	mfhi	$t2
/*  f040c08:	2d4f00c9 */ 	sltiu	$t7,$t2,0xc9
/*  f040c0c:	39ef0001 */ 	xori	$t7,$t7,0x1
/*  f040c10:	a3af026e */ 	sb	$t7,0x26e($sp)
.PF0f040c14:
/*  f040c14:	3c014780 */ 	lui	$at,0x4780
.PF0f040c18:
/*  f040c18:	44810000 */ 	mtc1	$at,$f0
/*  f040c1c:	c7b001e0 */ 	lwc1	$f16,0x1e0($sp)
/*  f040c20:	c7a40244 */ 	lwc1	$f4,0x244($sp)
/*  f040c24:	c7a601e4 */ 	lwc1	$f6,0x1e4($sp)
/*  f040c28:	46008482 */ 	mul.s	$f18,$f16,$f0
/*  f040c2c:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f040c30:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040c34:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f040c38:	c7a6024c */ 	lwc1	$f6,0x24c($sp)
/*  f040c3c:	00002825 */ 	move	$a1,$zero
/*  f040c40:	46049200 */ 	add.s	$f8,$f18,$f4
/*  f040c44:	c7a401e8 */ 	lwc1	$f4,0x1e8($sp)
/*  f040c48:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f040c4c:	e7a80228 */ 	swc1	$f8,0x228($sp)
/*  f040c50:	46002202 */ 	mul.s	$f8,$f4,$f0
/*  f040c54:	e7b2022c */ 	swc1	$f18,0x22c($sp)
/*  f040c58:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f040c5c:	0fc07a37 */ 	jal	chrSetPerimEnabled
/*  f040c60:	e7aa0230 */ 	swc1	$f10,0x230($sp)
/*  f040c64:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f040c68:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f040c6c:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f040c70:	13000004 */ 	beqz	$t8,.PF0f040c84
/*  f040c74:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f040c78:	240c0001 */ 	li	$t4,0x1
/*  f040c7c:	3c01800a */ 	lui	$at,0x800a
/*  f040c80:	ac2ca99c */ 	sw	$t4,-0x5664($at)
.PF0f040c84:
/*  f040c84:	24190010 */ 	li	$t9,0x10
/*  f040c88:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f040c8c:	0c00b5a4 */ 	jal	cdTestAToB4
/*  f040c90:	8fa701c8 */ 	lw	$a3,0x1c8($sp)
/*  f040c94:	1440000a */ 	bnez	$v0,.PF0f040cc0
/*  f040c98:	240d0001 */ 	li	$t5,0x1
/*  f040c9c:	3c067f1b */ 	lui	$a2,0x7f1b
/*  f040ca0:	afad0224 */ 	sw	$t5,0x224($sp)
/*  f040ca4:	24c69d20 */ 	addiu	$a2,$a2,-25312
/*  f040ca8:	27a40228 */ 	addiu	$a0,$sp,0x228
/*  f040cac:	0c0091ef */ 	jal	cdGetPos
/*  f040cb0:	24052f2d */ 	li	$a1,0x2f2d
/*  f040cb4:	0c0091ec */ 	jal	cdGetObstacle
/*  f040cb8:	00000000 */ 	nop
/*  f040cbc:	afa201cc */ 	sw	$v0,0x1cc($sp)
.PF0f040cc0:
/*  f040cc0:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040cc4:	0fc07a37 */ 	jal	chrSetPerimEnabled
/*  f040cc8:	24050001 */ 	li	$a1,0x1
/*  f040ccc:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f040cd0:	3c01800a */ 	lui	$at,0x800a
/*  f040cd4:	51c00003 */ 	beqzl	$t6,.PF0f040ce4
/*  f040cd8:	8fab01cc */ 	lw	$t3,0x1cc($sp)
/*  f040cdc:	ac20a99c */ 	sw	$zero,-0x5664($at)
/*  f040ce0:	8fab01cc */ 	lw	$t3,0x1cc($sp)
.PF0f040ce4:
/*  f040ce4:	8faa01c0 */ 	lw	$t2,0x1c0($sp)
/*  f040ce8:	55600015 */ 	bnezl	$t3,.PF0f040d40
/*  f040cec:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f040cf0:	51400013 */ 	beqzl	$t2,.PF0f040d40
/*  f040cf4:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f040cf8:	0c004ad4 */ 	jal	random
/*  f040cfc:	00000000 */ 	nop
/*  f040d00:	24010064 */ 	li	$at,0x64
/*  f040d04:	0041001b */ 	divu	$zero,$v0,$at
/*  f040d08:	00001810 */ 	mfhi	$v1
/*  f040d0c:	2c6f0033 */ 	sltiu	$t7,$v1,0x33
/*  f040d10:	39ef0001 */ 	xori	$t7,$t7,0x1
/*  f040d14:	11e00009 */ 	beqz	$t7,.PF0f040d3c
/*  f040d18:	afaf01bc */ 	sw	$t7,0x1bc($sp)
/*  f040d1c:	8fb8025c */ 	lw	$t8,0x25c($sp)
/*  f040d20:	afb801cc */ 	sw	$t8,0x1cc($sp)
/*  f040d24:	c7100008 */ 	lwc1	$f16,0x8($t8)
/*  f040d28:	e7b00228 */ 	swc1	$f16,0x228($sp)
/*  f040d2c:	c712000c */ 	lwc1	$f18,0xc($t8)
/*  f040d30:	e7b2022c */ 	swc1	$f18,0x22c($sp)
/*  f040d34:	c7040010 */ 	lwc1	$f4,0x10($t8)
/*  f040d38:	e7a40230 */ 	swc1	$f4,0x230($sp)
.PF0f040d3c:
/*  f040d3c:	c7a80228 */ 	lwc1	$f8,0x228($sp)
.PF0f040d40:
/*  f040d40:	c7a60244 */ 	lwc1	$f6,0x244($sp)
/*  f040d44:	c7aa022c */ 	lwc1	$f10,0x22c($sp)
/*  f040d48:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f040d4c:	46064001 */ 	sub.s	$f0,$f8,$f6
/*  f040d50:	c7b20230 */ 	lwc1	$f18,0x230($sp)
/*  f040d54:	c7a4024c */ 	lwc1	$f4,0x24c($sp)
/*  f040d58:	46105081 */ 	sub.s	$f2,$f10,$f16
/*  f040d5c:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f040d60:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040d64:	46049301 */ 	sub.s	$f12,$f18,$f4
/*  f040d68:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f040d6c:	24010018 */ 	li	$at,0x18
/*  f040d70:	460c6402 */ 	mul.s	$f16,$f12,$f12
/*  f040d74:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f040d78:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f040d7c:	1081000f */ 	beq	$a0,$at,.PF0f040dbc
/*  f040d80:	e7b201d0 */ 	swc1	$f18,0x1d0($sp)
/*  f040d84:	24010019 */ 	li	$at,0x19
/*  f040d88:	1081000c */ 	beq	$a0,$at,.PF0f040dbc
/*  f040d8c:	24010012 */ 	li	$at,0x12
/*  f040d90:	14810003 */ 	bne	$a0,$at,.PF0f040da0
/*  f040d94:	93ac0263 */ 	lbu	$t4,0x263($sp)
/*  f040d98:	24010001 */ 	li	$at,0x1
/*  f040d9c:	11810007 */ 	beq	$t4,$at,.PF0f040dbc
.PF0f040da0:
/*  f040da0:	24010017 */ 	li	$at,0x17
/*  f040da4:	10810005 */ 	beq	$a0,$at,.PF0f040dbc
/*  f040da8:	2401001b */ 	li	$at,0x1b
/*  f040dac:	10810003 */ 	beq	$a0,$at,.PF0f040dbc
/*  f040db0:	24010034 */ 	li	$at,0x34
/*  f040db4:	54810179 */ 	bnel	$a0,$at,.PF0f04139c
/*  f040db8:	24010006 */ 	li	$at,0x6
.PF0f040dbc:
/*  f040dbc:	93b9026f */ 	lbu	$t9,0x26f($sp)
/*  f040dc0:	afa00250 */ 	sw	$zero,0x250($sp)
/*  f040dc4:	3c017f1b */ 	lui	$at,0x7f1b
/*  f040dc8:	17200006 */ 	bnez	$t9,.PF0f040de4
/*  f040dcc:	c7a801d0 */ 	lwc1	$f8,0x1d0($sp)
/*  f040dd0:	c424a330 */ 	lwc1	$f4,-0x5cd0($at)
/*  f040dd4:	4608203c */ 	c.lt.s	$f4,$f8
/*  f040dd8:	00000000 */ 	nop
/*  f040ddc:	4502016c */ 	bc1fl	.PF0f041390
/*  f040de0:	afa00268 */ 	sw	$zero,0x268($sp)
.PF0f040de4:
/*  f040de4:	0fc2c524 */ 	jal	weaponFindById
/*  f040de8:	00000000 */ 	nop
/*  f040dec:	93ad0263 */ 	lbu	$t5,0x263($sp)
/*  f040df0:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040df4:	24010018 */ 	li	$at,0x18
/*  f040df8:	000d7080 */ 	sll	$t6,$t5,0x2
/*  f040dfc:	004e5821 */ 	addu	$t3,$v0,$t6
/*  f040e00:	10810006 */ 	beq	$a0,$at,.PF0f040e1c
/*  f040e04:	8d630014 */ 	lw	$v1,0x14($t3)
/*  f040e08:	24010034 */ 	li	$at,0x34
/*  f040e0c:	10810003 */ 	beq	$a0,$at,.PF0f040e1c
/*  f040e10:	24010019 */ 	li	$at,0x19
/*  f040e14:	5481000e */ 	bnel	$a0,$at,.PF0f040e50
/*  f040e18:	2401001b */ 	li	$at,0x1b
.PF0f040e1c:
/*  f040e1c:	8c6a0010 */ 	lw	$t2,0x10($v1)
/*  f040e20:	24050053 */ 	li	$a1,0x53
/*  f040e24:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040e28:	000a7840 */ 	sll	$t7,$t2,0x1
/*  f040e2c:	05e30003 */ 	bgezl	$t7,.PF0f040e3c
/*  f040e30:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040e34:	24050054 */ 	li	$a1,0x54
/*  f040e38:	8c640040 */ 	lw	$a0,0x40($v1)
.PF0f040e3c:
/*  f040e3c:	0fc22deb */ 	jal	func0f08b880
/*  f040e40:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040e44:	1000002e */ 	b	.PF0f040f00
/*  f040e48:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040e4c:	2401001b */ 	li	$at,0x1b
.PF0f040e50:
/*  f040e50:	1481000a */ 	bne	$a0,$at,.PF0f040e7c
/*  f040e54:	24050056 */ 	li	$a1,0x56
/*  f040e58:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040e5c:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040e60:	0fc22deb */ 	jal	func0f08b880
/*  f040e64:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040e68:	10400025 */ 	beqz	$v0,.PF0f040f00
/*  f040e6c:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040e70:	93b80263 */ 	lbu	$t8,0x263($sp)
/*  f040e74:	10000022 */ 	b	.PF0f040f00
/*  f040e78:	a058005f */ 	sb	$t8,0x5f($v0)
.PF0f040e7c:
/*  f040e7c:	24010017 */ 	li	$at,0x17
/*  f040e80:	1481000a */ 	bne	$a0,$at,.PF0f040eac
/*  f040e84:	24050055 */ 	li	$a1,0x55
/*  f040e88:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040e8c:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040e90:	0fc22deb */ 	jal	func0f08b880
/*  f040e94:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040e98:	10400019 */ 	beqz	$v0,.PF0f040f00
/*  f040e9c:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040ea0:	93ac0263 */ 	lbu	$t4,0x263($sp)
/*  f040ea4:	10000016 */ 	b	.PF0f040f00
/*  f040ea8:	a04c005f */ 	sb	$t4,0x5f($v0)
.PF0f040eac:
/*  f040eac:	24010012 */ 	li	$at,0x12
/*  f040eb0:	1481000b */ 	bne	$a0,$at,.PF0f040ee0
/*  f040eb4:	3c0d800a */ 	lui	$t5,0x800a
/*  f040eb8:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040ebc:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040ec0:	24050055 */ 	li	$a1,0x55
/*  f040ec4:	0fc22deb */ 	jal	func0f08b880
/*  f040ec8:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040ecc:	1040000c */ 	beqz	$v0,.PF0f040f00
/*  f040ed0:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040ed4:	24190002 */ 	li	$t9,0x2
/*  f040ed8:	10000009 */ 	b	.PF0f040f00
/*  f040edc:	a059005f */ 	sb	$t9,0x5f($v0)
.PF0f040ee0:
/*  f040ee0:	8dada794 */ 	lw	$t5,-0x586c($t5)
/*  f040ee4:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040ee8:	27a50260 */ 	addiu	$a1,$sp,0x260
/*  f040eec:	8dae00bc */ 	lw	$t6,0xbc($t5)
/*  f040ef0:	8dc60004 */ 	lw	$a2,0x4($t6)
/*  f040ef4:	0fc22d61 */ 	jal	func0f08b658
/*  f040ef8:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040efc:	afa201b8 */ 	sw	$v0,0x1b8($sp)
.PF0f040f00:
/*  f040f00:	10400123 */ 	beqz	$v0,.PF0f041390
/*  f040f04:	8fab00d4 */ 	lw	$t3,0xd4($sp)
/*  f040f08:	8d6a004c */ 	lw	$t2,0x4c($t3)
/*  f040f0c:	3c017f1b */ 	lui	$at,0x7f1b
/*  f040f10:	c430a334 */ 	lwc1	$f16,-0x5ccc($at)
/*  f040f14:	448a3000 */ 	mtc1	$t2,$f6
/*  f040f18:	3c014270 */ 	lui	$at,0x4270
/*  f040f1c:	44812000 */ 	mtc1	$at,$f4
/*  f040f20:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f040f24:	3c017f1b */ 	lui	$at,0x7f1b
/*  f040f28:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f040f2c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040f30:	2405001e */ 	li	$a1,0x1e
/*  f040f34:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f040f38:	c430a338 */ 	lwc1	$f16,-0x5cc8($at)
/*  f040f3c:	46049203 */ 	div.s	$f8,$f18,$f4
/*  f040f40:	e7a80168 */ 	swc1	$f8,0x168($sp)
/*  f040f44:	8d6f0054 */ 	lw	$t7,0x54($t3)
/*  f040f48:	448f3000 */ 	mtc1	$t7,$f6
/*  f040f4c:	00000000 */ 	nop
/*  f040f50:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f040f54:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f040f58:	13000080 */ 	beqz	$t8,.PF0f04115c
/*  f040f5c:	e7b200cc */ 	swc1	$f18,0xcc($sp)
/*  f040f60:	0fc12480 */ 	jal	chrIsTargetInFov
/*  f040f64:	00003025 */ 	move	$a2,$zero
/*  f040f68:	1040007c */ 	beqz	$v0,.PF0f04115c
/*  f040f6c:	00000000 */ 	nop
/*  f040f70:	93a20263 */ 	lbu	$v0,0x263($sp)
/*  f040f74:	00001825 */ 	move	$v1,$zero
/*  f040f78:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040f7c:	14400025 */ 	bnez	$v0,.PF0f041014
/*  f040f80:	24010018 */ 	li	$at,0x18
/*  f040f84:	10810006 */ 	beq	$a0,$at,.PF0f040fa0
/*  f040f88:	8fac025c */ 	lw	$t4,0x25c($sp)
/*  f040f8c:	24010034 */ 	li	$at,0x34
/*  f040f90:	10810003 */ 	beq	$a0,$at,.PF0f040fa0
/*  f040f94:	24010019 */ 	li	$at,0x19
/*  f040f98:	5481001f */ 	bnel	$a0,$at,.PF0f041018
/*  f040f9c:	93a40260 */ 	lbu	$a0,0x260($sp)
.PF0f040fa0:
/*  f040fa0:	91820000 */ 	lbu	$v0,0x0($t4)
/*  f040fa4:	24010003 */ 	li	$at,0x3
/*  f040fa8:	8fb9025c */ 	lw	$t9,0x25c($sp)
/*  f040fac:	10410003 */ 	beq	$v0,$at,.PF0f040fbc
/*  f040fb0:	24010006 */ 	li	$at,0x6
/*  f040fb4:	14410051 */ 	bne	$v0,$at,.PF0f0410fc
/*  f040fb8:	00000000 */ 	nop
.PF0f040fbc:
/*  f040fbc:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f040fc0:	c7aa0244 */ 	lwc1	$f10,0x244($sp)
/*  f040fc4:	c7b20248 */ 	lwc1	$f18,0x248($sp)
/*  f040fc8:	e7a400b8 */ 	swc1	$f4,0xb8($sp)
/*  f040fcc:	8f2d0004 */ 	lw	$t5,0x4($t9)
/*  f040fd0:	460a2401 */ 	sub.s	$f16,$f4,$f10
/*  f040fd4:	c7aa024c */ 	lwc1	$f10,0x24c($sp)
/*  f040fd8:	c5a800b4 */ 	lwc1	$f8,0xb4($t5)
/*  f040fdc:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f040fe0:	27a501e4 */ 	addiu	$a1,$sp,0x1e4
/*  f040fe4:	e7a800bc */ 	swc1	$f8,0xbc($sp)
/*  f040fe8:	c7260010 */ 	lwc1	$f6,0x10($t9)
/*  f040fec:	e7b001e0 */ 	swc1	$f16,0x1e0($sp)
/*  f040ff0:	46124101 */ 	sub.s	$f4,$f8,$f18
/*  f040ff4:	27a601e8 */ 	addiu	$a2,$sp,0x1e8
/*  f040ff8:	e7a600c0 */ 	swc1	$f6,0xc0($sp)
/*  f040ffc:	460a3401 */ 	sub.s	$f16,$f6,$f10
/*  f041000:	e7a401e4 */ 	swc1	$f4,0x1e4($sp)
/*  f041004:	0c0011d8 */ 	jal	guNormalize
/*  f041008:	e7b001e8 */ 	swc1	$f16,0x1e8($sp)
/*  f04100c:	1000003b */ 	b	.PF0f0410fc
/*  f041010:	24030001 */ 	li	$v1,0x1
.PF0f041014:
/*  f041014:	93a40260 */ 	lbu	$a0,0x260($sp)
.PF0f041018:
/*  f041018:	24050017 */ 	li	$a1,0x17
/*  f04101c:	24010012 */ 	li	$at,0x12
/*  f041020:	14a40003 */ 	bne	$a1,$a0,.PF0f041030
/*  f041024:	00000000 */ 	nop
/*  f041028:	50400004 */ 	beqzl	$v0,.PF0f04103c
/*  f04102c:	8fae025c */ 	lw	$t6,0x25c($sp)
.PF0f041030:
/*  f041030:	14810017 */ 	bne	$a0,$at,.PF0f041090
/*  f041034:	00000000 */ 	nop
/*  f041038:	8fae025c */ 	lw	$t6,0x25c($sp)
.PF0f04103c:
/*  f04103c:	24010003 */ 	li	$at,0x3
/*  f041040:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f041044:	91c20000 */ 	lbu	$v0,0x0($t6)
/*  f041048:	10410003 */ 	beq	$v0,$at,.PF0f041058
/*  f04104c:	24010006 */ 	li	$at,0x6
/*  f041050:	1441002a */ 	bne	$v0,$at,.PF0f0410fc
/*  f041054:	00000000 */ 	nop
.PF0f041058:
/*  f041058:	c5480008 */ 	lwc1	$f8,0x8($t2)
/*  f04105c:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041060:	8fa500cc */ 	lw	$a1,0xcc($sp)
/*  f041064:	e7a800b8 */ 	swc1	$f8,0xb8($sp)
/*  f041068:	8d4b0004 */ 	lw	$t3,0x4($t2)
/*  f04106c:	27a600b8 */ 	addiu	$a2,$sp,0xb8
/*  f041070:	27a701e0 */ 	addiu	$a3,$sp,0x1e0
/*  f041074:	c57200b4 */ 	lwc1	$f18,0xb4($t3)
/*  f041078:	e7b200bc */ 	swc1	$f18,0xbc($sp)
/*  f04107c:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f041080:	0fc10128 */ 	jal	func0f04031c
/*  f041084:	e7a400c0 */ 	swc1	$f4,0xc0($sp)
/*  f041088:	1000001c */ 	b	.PF0f0410fc
/*  f04108c:	24030001 */ 	li	$v1,0x1
.PF0f041090:
/*  f041090:	14a40002 */ 	bne	$a1,$a0,.PF0f04109c
/*  f041094:	24010001 */ 	li	$at,0x1
/*  f041098:	10410003 */ 	beq	$v0,$at,.PF0f0410a8
.PF0f04109c:
/*  f04109c:	2401001b */ 	li	$at,0x1b
/*  f0410a0:	14810016 */ 	bne	$a0,$at,.PF0f0410fc
/*  f0410a4:	00000000 */ 	nop
.PF0f0410a8:
/*  f0410a8:	8faf025c */ 	lw	$t7,0x25c($sp)
/*  f0410ac:	24010006 */ 	li	$at,0x6
/*  f0410b0:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f0410b4:	c5e60008 */ 	lwc1	$f6,0x8($t7)
/*  f0410b8:	27a600b8 */ 	addiu	$a2,$sp,0xb8
/*  f0410bc:	27a701e0 */ 	addiu	$a3,$sp,0x1e0
/*  f0410c0:	e7a600b8 */ 	swc1	$f6,0xb8($sp)
/*  f0410c4:	c5ea000c */ 	lwc1	$f10,0xc($t7)
/*  f0410c8:	e7aa00bc */ 	swc1	$f10,0xbc($sp)
/*  f0410cc:	c5f00010 */ 	lwc1	$f16,0x10($t7)
/*  f0410d0:	e7b000c0 */ 	swc1	$f16,0xc0($sp)
/*  f0410d4:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f0410d8:	17010005 */ 	bne	$t8,$at,.PF0f0410f0
/*  f0410dc:	3c0141c8 */ 	lui	$at,0x41c8
/*  f0410e0:	44814000 */ 	mtc1	$at,$f8
/*  f0410e4:	00000000 */ 	nop
/*  f0410e8:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f0410ec:	e7b200bc */ 	swc1	$f18,0xbc($sp)
.PF0f0410f0:
/*  f0410f0:	0fc10128 */ 	jal	func0f04031c
/*  f0410f4:	8fa500cc */ 	lw	$a1,0xcc($sp)
/*  f0410f8:	24030001 */ 	li	$v1,0x1
.PF0f0410fc:
/*  f0410fc:	10600017 */ 	beqz	$v1,.PF0f04115c
/*  f041100:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041104:	0fc12307 */ 	jal	chrGetAngleToPos
/*  f041108:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f04110c:	e7a000b4 */ 	swc1	$f0,0xb4($sp)
/*  f041110:	0c006858 */ 	jal	cosf
/*  f041114:	46000306 */ 	mov.s	$f12,$f0
/*  f041118:	c7ac00b4 */ 	lwc1	$f12,0xb4($sp)
/*  f04111c:	0c00685b */ 	jal	sinf
/*  f041120:	e7a000b0 */ 	swc1	$f0,0xb0($sp)
/*  f041124:	c7ac01e8 */ 	lwc1	$f12,0x1e8($sp)
/*  f041128:	c7ae00b0 */ 	lwc1	$f14,0xb0($sp)
/*  f04112c:	c7a201e0 */ 	lwc1	$f2,0x1e0($sp)
/*  f041130:	460c0102 */ 	mul.s	$f4,$f0,$f12
/*  f041134:	00000000 */ 	nop
/*  f041138:	46027182 */ 	mul.s	$f6,$f14,$f2
/*  f04113c:	00000000 */ 	nop
/*  f041140:	460c7282 */ 	mul.s	$f10,$f14,$f12
/*  f041144:	00000000 */ 	nop
/*  f041148:	46020202 */ 	mul.s	$f8,$f0,$f2
/*  f04114c:	46062400 */ 	add.s	$f16,$f4,$f6
/*  f041150:	e7b001e0 */ 	swc1	$f16,0x1e0($sp)
/*  f041154:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f041158:	e7b201e8 */ 	swc1	$f18,0x1e8($sp)
.PF0f04115c:
/*  f04115c:	0c0055d0 */ 	jal	mtx4LoadIdentity
/*  f041160:	27a40178 */ 	addiu	$a0,$sp,0x178
/*  f041164:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f041168:	0c00581e */ 	jal	mtx4LoadXRotation
/*  f04116c:	27a5011c */ 	addiu	$a1,$sp,0x11c
/*  f041170:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f041174:	0c005841 */ 	jal	mtx4LoadYRotation
/*  f041178:	27a500dc */ 	addiu	$a1,$sp,0xdc
/*  f04117c:	27a400dc */ 	addiu	$a0,$sp,0xdc
/*  f041180:	0c00565c */ 	jal	mtx00015be0
/*  f041184:	27a5011c */ 	addiu	$a1,$sp,0x11c
/*  f041188:	c7ac0168 */ 	lwc1	$f12,0x168($sp)
/*  f04118c:	c7a401e0 */ 	lwc1	$f4,0x1e0($sp)
/*  f041190:	c7b001e4 */ 	lwc1	$f16,0x1e4($sp)
/*  f041194:	c7a801e8 */ 	lwc1	$f8,0x1e8($sp)
/*  f041198:	460c2182 */ 	mul.s	$f6,$f4,$f12
/*  f04119c:	c7a200cc */ 	lwc1	$f2,0xcc($sp)
/*  f0411a0:	3c01800a */ 	lui	$at,0x800a
/*  f0411a4:	460c8282 */ 	mul.s	$f10,$f16,$f12
/*  f0411a8:	c420a55c */ 	lwc1	$f0,-0x5aa4($at)
/*  f0411ac:	8fac00d4 */ 	lw	$t4,0xd4($sp)
/*  f0411b0:	460c4482 */ 	mul.s	$f18,$f8,$f12
/*  f0411b4:	e7a6015c */ 	swc1	$f6,0x15c($sp)
/*  f0411b8:	8fa401b8 */ 	lw	$a0,0x1b8($sp)
/*  f0411bc:	46022102 */ 	mul.s	$f4,$f4,$f2
/*  f0411c0:	e7aa0160 */ 	swc1	$f10,0x160($sp)
/*  f0411c4:	2401ffff */ 	li	$at,-1
/*  f0411c8:	46003182 */ 	mul.s	$f6,$f6,$f0
/*  f0411cc:	e7b20164 */ 	swc1	$f18,0x164($sp)
/*  f0411d0:	27a50244 */ 	addiu	$a1,$sp,0x244
/*  f0411d4:	27a60234 */ 	addiu	$a2,$sp,0x234
/*  f0411d8:	27a7011c */ 	addiu	$a3,$sp,0x11c
/*  f0411dc:	27ab016c */ 	addiu	$t3,$sp,0x16c
/*  f0411e0:	27aa0178 */ 	addiu	$t2,$sp,0x178
/*  f0411e4:	46062100 */ 	add.s	$f4,$f4,$f6
/*  f0411e8:	46028182 */ 	mul.s	$f6,$f16,$f2
/*  f0411ec:	e7a4016c */ 	swc1	$f4,0x16c($sp)
/*  f0411f0:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f0411f4:	46043400 */ 	add.s	$f16,$f6,$f4
/*  f0411f8:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f0411fc:	00000000 */ 	nop
/*  f041200:	46009182 */ 	mul.s	$f6,$f18,$f0
/*  f041204:	e7b00170 */ 	swc1	$f16,0x170($sp)
/*  f041208:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f04120c:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f041210:	8d8d0058 */ 	lw	$t5,0x58($t4)
/*  f041214:	a48d0062 */ 	sh	$t5,0x62($a0)
/*  f041218:	84820062 */ 	lh	$v0,0x62($a0)
/*  f04121c:	1041000a */ 	beq	$v0,$at,.PF0f041248
/*  f041220:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f041224:	0322c823 */ 	subu	$t9,$t9,$v0
/*  f041228:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f04122c:	0322c821 */ 	addu	$t9,$t9,$v0
/*  f041230:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*  f041234:	2401003c */ 	li	$at,0x3c
/*  f041238:	0321001a */ 	div	$zero,$t9,$at
/*  f04123c:	00007012 */ 	mflo	$t6
/*  f041240:	a48e0062 */ 	sh	$t6,0x62($a0)
/*  f041244:	00000000 */ 	nop
.PF0f041248:
/*  f041248:	8faf0274 */ 	lw	$t7,0x274($sp)
/*  f04124c:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f041250:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f041254:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f041258:	0fc27bac */ 	jal	bgun0f09ebcc
/*  f04125c:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f041260:	8fa301b8 */ 	lw	$v1,0x1b8($sp)
/*  f041264:	8fad00d4 */ 	lw	$t5,0xd4($sp)
/*  f041268:	8c780040 */ 	lw	$t8,0x40($v1)
/*  f04126c:	330c0080 */ 	andi	$t4,$t8,0x80
/*  f041270:	11800047 */ 	beqz	$t4,.PF0f041390
/*  f041274:	00000000 */ 	nop
/*  f041278:	8da20010 */ 	lw	$v0,0x10($t5)
/*  f04127c:	0002c800 */ 	sll	$t9,$v0,0x0
/*  f041280:	07210007 */ 	bgez	$t9,.PF0f0412a0
/*  f041284:	00025100 */ 	sll	$t2,$v0,0x4
/*  f041288:	8c620048 */ 	lw	$v0,0x48($v1)
/*  f04128c:	3c014000 */ 	lui	$at,0x4000
/*  f041290:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*  f041294:	01c15825 */ 	or	$t3,$t6,$at
/*  f041298:	10000007 */ 	b	.PF0f0412b8
/*  f04129c:	ac4b0000 */ 	sw	$t3,0x0($v0)
.PF0f0412a0:
/*  f0412a0:	05430006 */ 	bgezl	$t2,.PF0f0412bc
/*  f0412a4:	c7b0015c */ 	lwc1	$f16,0x15c($sp)
/*  f0412a8:	8c620048 */ 	lw	$v0,0x48($v1)
/*  f0412ac:	8c4f0000 */ 	lw	$t7,0x0($v0)
/*  f0412b0:	35f80010 */ 	ori	$t8,$t7,0x10
/*  f0412b4:	ac580000 */ 	sw	$t8,0x0($v0)
.PF0f0412b8:
/*  f0412b8:	c7b0015c */ 	lwc1	$f16,0x15c($sp)
.PF0f0412bc:
/*  f0412bc:	8c6c0048 */ 	lw	$t4,0x48($v1)
/*  f0412c0:	240e00c8 */ 	li	$t6,0xc8
/*  f0412c4:	3c017f1b */ 	lui	$at,0x7f1b
/*  f0412c8:	e5900010 */ 	swc1	$f16,0x10($t4)
/*  f0412cc:	8c6d0048 */ 	lw	$t5,0x48($v1)
/*  f0412d0:	c7a80160 */ 	lwc1	$f8,0x160($sp)
/*  f0412d4:	e5a80014 */ 	swc1	$f8,0x14($t5)
/*  f0412d8:	8c790048 */ 	lw	$t9,0x48($v1)
/*  f0412dc:	c7b20164 */ 	lwc1	$f18,0x164($sp)
/*  f0412e0:	e7320018 */ 	swc1	$f18,0x18($t9)
/*  f0412e4:	8c6b0048 */ 	lw	$t3,0x48($v1)
/*  f0412e8:	ad6e00b4 */ 	sw	$t6,0xb4($t3)
/*  f0412ec:	8faa00d4 */ 	lw	$t2,0xd4($sp)
/*  f0412f0:	8c6f0048 */ 	lw	$t7,0x48($v1)
/*  f0412f4:	c54a005c */ 	lwc1	$f10,0x5c($t2)
/*  f0412f8:	e5ea008c */ 	swc1	$f10,0x8c($t7)
/*  f0412fc:	8fb800d4 */ 	lw	$t8,0xd4($sp)
/*  f041300:	c424a33c */ 	lwc1	$f4,-0x5cc4($at)
/*  f041304:	8c6c0048 */ 	lw	$t4,0x48($v1)
/*  f041308:	c7060050 */ 	lwc1	$f6,0x50($t8)
/*  f04130c:	46043402 */ 	mul.s	$f16,$f6,$f4
/*  f041310:	e5900098 */ 	swc1	$f16,0x98($t4)
/*  f041314:	0fc0a26a */ 	jal	chrGetTargetProp
/*  f041318:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f04131c:	8fad01b8 */ 	lw	$t5,0x1b8($sp)
/*  f041320:	3c01bf80 */ 	lui	$at,0xbf80
/*  f041324:	00002025 */ 	move	$a0,$zero
/*  f041328:	8db90048 */ 	lw	$t9,0x48($t5)
/*  f04132c:	2407ffff */ 	li	$a3,-1
/*  f041330:	240bffff */ 	li	$t3,-1
/*  f041334:	af2200e8 */ 	sw	$v0,0xe8($t9)
/*  f041338:	8fae00d4 */ 	lw	$t6,0xd4($sp)
/*  f04133c:	240affff */ 	li	$t2,-1
/*  f041340:	85c60060 */ 	lh	$a2,0x60($t6)
/*  f041344:	18c00012 */ 	blez	$a2,.PF0f041390
/*  f041348:	00000000 */ 	nop
/*  f04134c:	8da50014 */ 	lw	$a1,0x14($t5)
/*  f041350:	44810000 */ 	mtc1	$at,$f0
/*  f041354:	afaa002c */ 	sw	$t2,0x2c($sp)
/*  f041358:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f04135c:	afa00020 */ 	sw	$zero,0x20($sp)
/*  f041360:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f041364:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f041368:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f04136c:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f041370:	e7a00024 */ 	swc1	$f0,0x24($sp)
/*  f041374:	e7a00030 */ 	swc1	$f0,0x30($sp)
/*  f041378:	e7a00034 */ 	swc1	$f0,0x34($sp)
/*  f04137c:	0fc24e3a */ 	jal	func0f0939f8
/*  f041380:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*  f041384:	10000002 */ 	b	.PF0f041390
/*  f041388:	00000000 */ 	nop
/*  f04138c:	afa00268 */ 	sw	$zero,0x268($sp)
.PF0f041390:
/*  f041390:	10000019 */ 	b	.PF0f0413f8
/*  f041394:	a3a0026e */ 	sb	$zero,0x26e($sp)
/*  f041398:	24010006 */ 	li	$at,0x6
.PF0f04139c:
/*  f04139c:	14810016 */ 	bne	$a0,$at,.PF0f0413f8
/*  f0413a0:	93af026f */ 	lbu	$t7,0x26f($sp)
/*  f0413a4:	11e00014 */ 	beqz	$t7,.PF0f0413f8
/*  f0413a8:	93b80263 */ 	lbu	$t8,0x263($sp)
/*  f0413ac:	24010001 */ 	li	$at,0x1
/*  f0413b0:	17010011 */ 	bne	$t8,$at,.PF0f0413f8
/*  f0413b4:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f0413b8:	8fa2027c */ 	lw	$v0,0x27c($sp)
/*  f0413bc:	8f2e02d4 */ 	lw	$t6,0x2d4($t9)
/*  f0413c0:	3c014120 */ 	lui	$at,0x4120
/*  f0413c4:	00026080 */ 	sll	$t4,$v0,0x2
/*  f0413c8:	01cc6821 */ 	addu	$t5,$t6,$t4
/*  f0413cc:	c5a800e4 */ 	lwc1	$f8,0xe4($t5)
/*  f0413d0:	44819000 */ 	mtc1	$at,$f18
/*  f0413d4:	44802000 */ 	mtc1	$zero,$f4
/*  f0413d8:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f0413dc:	4600518d */ 	trunc.w.s	$f6,$f10
/*  f0413e0:	440a3000 */ 	mfc1	$t2,$f6
/*  f0413e4:	00000000 */ 	nop
/*  f0413e8:	a3aa0262 */ 	sb	$t2,0x262($sp)
/*  f0413ec:	8f2f02d4 */ 	lw	$t7,0x2d4($t9)
/*  f0413f0:	01ecc021 */ 	addu	$t8,$t7,$t4
/*  f0413f4:	e70400e4 */ 	swc1	$f4,0xe4($t8)
.PF0f0413f8:
/*  f0413f8:	93ac026e */ 	lbu	$t4,0x26e($sp)
/*  f0413fc:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f041400:	518001c0 */ 	beqzl	$t4,.PF0f041b04
/*  f041404:	8fab01c0 */ 	lw	$t3,0x1c0($sp)
/*  f041408:	15c000d6 */ 	bnez	$t6,.PF0f041764
/*  f04140c:	8fad0258 */ 	lw	$t5,0x258($sp)
/*  f041410:	31ab0200 */ 	andi	$t3,$t5,0x200
/*  f041414:	1160004c */ 	beqz	$t3,.PF0f041548
/*  f041418:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f04141c:	91590000 */ 	lbu	$t9,0x0($t2)
/*  f041420:	24010006 */ 	li	$at,0x6
/*  f041424:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041428:	17210047 */ 	bne	$t9,$at,.PF0f041548
/*  f04142c:	27a50244 */ 	addiu	$a1,$sp,0x244
/*  f041430:	27a60234 */ 	addiu	$a2,$sp,0x234
/*  f041434:	0fc0e4dc */ 	jal	chrCanSeeAttackTarget
/*  f041438:	00003825 */ 	move	$a3,$zero
/*  f04143c:	10400042 */ 	beqz	$v0,.PF0f041548
/*  f041440:	8faf025c */ 	lw	$t7,0x25c($sp)
/*  f041444:	8de40004 */ 	lw	$a0,0x4($t7)
/*  f041448:	8fa50278 */ 	lw	$a1,0x278($sp)
/*  f04144c:	0fc12b09 */ 	jal	chrCompareTeams
/*  f041450:	24060002 */ 	li	$a2,0x2
/*  f041454:	1040003c */ 	beqz	$v0,.PF0f041548
/*  f041458:	3c014170 */ 	lui	$at,0x4170
/*  f04145c:	44817000 */ 	mtc1	$at,$f14
/*  f041460:	8fb8025c */ 	lw	$t8,0x25c($sp)
/*  f041464:	c7aa01e0 */ 	lwc1	$f10,0x1e0($sp)
/*  f041468:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f04146c:	c7100008 */ 	lwc1	$f16,0x8($t8)
/*  f041470:	460e5182 */ 	mul.s	$f6,$f10,$f14
/*  f041474:	c7aa01e4 */ 	lwc1	$f10,0x1e4($sp)
/*  f041478:	46088481 */ 	sub.s	$f18,$f16,$f8
/*  f04147c:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f041480:	c704000c */ 	lwc1	$f4,0xc($t8)
/*  f041484:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041488:	27a501f8 */ 	addiu	$a1,$sp,0x1f8
/*  f04148c:	46069001 */ 	sub.s	$f0,$f18,$f6
/*  f041490:	460e5482 */ 	mul.s	$f18,$f10,$f14
/*  f041494:	c7aa01e8 */ 	lwc1	$f10,0x1e8($sp)
/*  f041498:	46102201 */ 	sub.s	$f8,$f4,$f16
/*  f04149c:	c7a4024c */ 	lwc1	$f4,0x24c($sp)
/*  f0414a0:	c7060010 */ 	lwc1	$f6,0x10($t8)
/*  f0414a4:	27a601f4 */ 	addiu	$a2,$sp,0x1f4
/*  f0414a8:	46124081 */ 	sub.s	$f2,$f8,$f18
/*  f0414ac:	460e5202 */ 	mul.s	$f8,$f10,$f14
/*  f0414b0:	c7b201d0 */ 	lwc1	$f18,0x1d0($sp)
/*  f0414b4:	46043401 */ 	sub.s	$f16,$f6,$f4
/*  f0414b8:	46000182 */ 	mul.s	$f6,$f0,$f0
/*  f0414bc:	00000000 */ 	nop
/*  f0414c0:	46021102 */ 	mul.s	$f4,$f2,$f2
/*  f0414c4:	46088301 */ 	sub.s	$f12,$f16,$f8
/*  f0414c8:	460c6402 */ 	mul.s	$f16,$f12,$f12
/*  f0414cc:	46043280 */ 	add.s	$f10,$f6,$f4
/*  f0414d0:	46105200 */ 	add.s	$f8,$f10,$f16
/*  f0414d4:	4612403e */ 	c.le.s	$f8,$f18
/*  f0414d8:	00000000 */ 	nop
/*  f0414dc:	4500002b */ 	bc1f	.PF0f04158c
/*  f0414e0:	00000000 */ 	nop
/*  f0414e4:	0fc0ff0d */ 	jal	chrCalculateHit
/*  f0414e8:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f0414ec:	8fac01f4 */ 	lw	$t4,0x1f4($sp)
/*  f0414f0:	8fad01f8 */ 	lw	$t5,0x1f8($sp)
/*  f0414f4:	8fab0278 */ 	lw	$t3,0x278($sp)
/*  f0414f8:	2d8e0001 */ 	sltiu	$t6,$t4,0x1
/*  f0414fc:	11a00023 */ 	beqz	$t5,.PF0f04158c
/*  f041500:	afae01f0 */ 	sw	$t6,0x1f0($sp)
/*  f041504:	81630007 */ 	lb	$v1,0x7($t3)
/*  f041508:	24010008 */ 	li	$at,0x8
/*  f04150c:	3c0a800a */ 	lui	$t2,0x800a
/*  f041510:	1061000a */ 	beq	$v1,$at,.PF0f04153c
/*  f041514:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f041518:	2401000a */ 	li	$at,0xa
/*  f04151c:	10610007 */ 	beq	$v1,$at,.PF0f04153c
/*  f041520:	2401001b */ 	li	$at,0x1b
/*  f041524:	10610005 */ 	beq	$v1,$at,.PF0f04153c
/*  f041528:	2401001c */ 	li	$at,0x1c
/*  f04152c:	10610003 */ 	beq	$v1,$at,.PF0f04153c
/*  f041530:	2401001d */ 	li	$at,0x1d
/*  f041534:	54610016 */ 	bnel	$v1,$at,.PF0f041590
/*  f041538:	8fae01f4 */ 	lw	$t6,0x1f4($sp)
.PF0f04153c:
/*  f04153c:	8d4aa518 */ 	lw	$t2,-0x5ae8($t2)
/*  f041540:	10000012 */ 	b	.PF0f04158c
/*  f041544:	af2a0048 */ 	sw	$t2,0x48($t9)
.PF0f041548:
/*  f041548:	8faf0278 */ 	lw	$t7,0x278($sp)
/*  f04154c:	24010008 */ 	li	$at,0x8
/*  f041550:	3c18800a */ 	lui	$t8,0x800a
/*  f041554:	81e30007 */ 	lb	$v1,0x7($t7)
/*  f041558:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f04155c:	10610009 */ 	beq	$v1,$at,.PF0f041584
/*  f041560:	2401000a */ 	li	$at,0xa
/*  f041564:	10610007 */ 	beq	$v1,$at,.PF0f041584
/*  f041568:	2401001b */ 	li	$at,0x1b
/*  f04156c:	10610005 */ 	beq	$v1,$at,.PF0f041584
/*  f041570:	2401001c */ 	li	$at,0x1c
/*  f041574:	10610003 */ 	beq	$v1,$at,.PF0f041584
/*  f041578:	2401001d */ 	li	$at,0x1d
/*  f04157c:	54610004 */ 	bnel	$v1,$at,.PF0f041590
/*  f041580:	8fae01f4 */ 	lw	$t6,0x1f4($sp)
.PF0f041584:
/*  f041584:	8f18a518 */ 	lw	$t8,-0x5ae8($t8)
/*  f041588:	ad980048 */ 	sw	$t8,0x48($t4)
.PF0f04158c:
/*  f04158c:	8fae01f4 */ 	lw	$t6,0x1f4($sp)
.PF0f041590:
/*  f041590:	8faf01cc */ 	lw	$t7,0x1cc($sp)
/*  f041594:	11c00065 */ 	beqz	$t6,.PF0f04172c
/*  f041598:	00000000 */ 	nop
/*  f04159c:	0fc2c87a */ 	jal	gsetGetDamage
/*  f0415a0:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f0415a4:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f0415a8:	240dffff */ 	li	$t5,-1
/*  f0415ac:	240b00c8 */ 	li	$t3,0xc8
/*  f0415b0:	e7a0009c */ 	swc1	$f0,0x9c($sp)
/*  f0415b4:	afa00098 */ 	sw	$zero,0x98($sp)
/*  f0415b8:	afa00094 */ 	sw	$zero,0x94($sp)
/*  f0415bc:	afad0090 */ 	sw	$t5,0x90($sp)
/*  f0415c0:	afab008c */ 	sw	$t3,0x8c($sp)
/*  f0415c4:	8d590004 */ 	lw	$t9,0x4($t2)
/*  f0415c8:	afb90088 */ 	sw	$t9,0x88($sp)
/*  f0415cc:	c5460008 */ 	lwc1	$f6,0x8($t2)
/*  f0415d0:	e7a60228 */ 	swc1	$f6,0x228($sp)
/*  f0415d4:	c544000c */ 	lwc1	$f4,0xc($t2)
/*  f0415d8:	e7a4022c */ 	swc1	$f4,0x22c($sp)
/*  f0415dc:	c54a0010 */ 	lwc1	$f10,0x10($t2)
/*  f0415e0:	0c004ad4 */ 	jal	random
/*  f0415e4:	e7aa0230 */ 	swc1	$f10,0x230($sp)
/*  f0415e8:	304f0001 */ 	andi	$t7,$v0,0x1
/*  f0415ec:	11e00012 */ 	beqz	$t7,.PF0f041638
/*  f0415f0:	00000000 */ 	nop
/*  f0415f4:	0c004ad4 */ 	jal	random
/*  f0415f8:	00000000 */ 	nop
/*  f0415fc:	2401000a */ 	li	$at,0xa
/*  f041600:	0041001b */ 	divu	$zero,$v0,$at
/*  f041604:	0000c010 */ 	mfhi	$t8
/*  f041608:	270c0002 */ 	addiu	$t4,$t8,0x2
/*  f04160c:	448c9000 */ 	mtc1	$t4,$f18
/*  f041610:	c7b0022c */ 	lwc1	$f16,0x22c($sp)
/*  f041614:	05810005 */ 	bgez	$t4,.PF0f04162c
/*  f041618:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f04161c:	3c014f80 */ 	lui	$at,0x4f80
/*  f041620:	44813000 */ 	mtc1	$at,$f6
/*  f041624:	00000000 */ 	nop
/*  f041628:	46064200 */ 	add.s	$f8,$f8,$f6
.PF0f04162c:
/*  f04162c:	46088100 */ 	add.s	$f4,$f16,$f8
/*  f041630:	10000011 */ 	b	.PF0f041678
/*  f041634:	e7a4022c */ 	swc1	$f4,0x22c($sp)
.PF0f041638:
/*  f041638:	0c004ad4 */ 	jal	random
/*  f04163c:	00000000 */ 	nop
/*  f041640:	2401000a */ 	li	$at,0xa
/*  f041644:	0041001b */ 	divu	$zero,$v0,$at
/*  f041648:	00007010 */ 	mfhi	$t6
/*  f04164c:	25cd0002 */ 	addiu	$t5,$t6,0x2
/*  f041650:	448d9000 */ 	mtc1	$t5,$f18
/*  f041654:	c7aa022c */ 	lwc1	$f10,0x22c($sp)
/*  f041658:	05a10005 */ 	bgez	$t5,.PF0f041670
/*  f04165c:	468091a0 */ 	cvt.s.w	$f6,$f18
/*  f041660:	3c014f80 */ 	lui	$at,0x4f80
/*  f041664:	44818000 */ 	mtc1	$at,$f16
/*  f041668:	00000000 */ 	nop
/*  f04166c:	46103180 */ 	add.s	$f6,$f6,$f16
.PF0f041670:
/*  f041670:	46065201 */ 	sub.s	$f8,$f10,$f6
/*  f041674:	e7a8022c */ 	swc1	$f8,0x22c($sp)
.PF0f041678:
/*  f041678:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f04167c:	8fa5025c */ 	lw	$a1,0x25c($sp)
/*  f041680:	0fc2a079 */ 	jal	bgunPlayPropHitSound
/*  f041684:	2406ffff */ 	li	$a2,-1
/*  f041688:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f04168c:	8c8b0020 */ 	lw	$t3,0x20($a0)
/*  f041690:	51600012 */ 	beqzl	$t3,.PF0f0416dc
/*  f041694:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f041698:	0fc0d042 */ 	jal	chrGetShield
/*  f04169c:	00000000 */ 	nop
/*  f0416a0:	44802000 */ 	mtc1	$zero,$f4
/*  f0416a4:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f0416a8:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f0416ac:	4600203c */ 	c.lt.s	$f4,$f0
/*  f0416b0:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f0416b4:	27a70098 */ 	addiu	$a3,$sp,0x98
/*  f0416b8:	27b9008c */ 	addiu	$t9,$sp,0x8c
/*  f0416bc:	45000006 */ 	bc1f	.PF0f0416d8
/*  f0416c0:	27aa0094 */ 	addiu	$t2,$sp,0x94
/*  f0416c4:	27af0090 */ 	addiu	$t7,$sp,0x90
/*  f0416c8:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f0416cc:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f0416d0:	0fc1002c */ 	jal	chrCalculateShieldHit
/*  f0416d4:	afaa0014 */ 	sw	$t2,0x14($sp)
.PF0f0416d8:
/*  f0416d8:	8fb80278 */ 	lw	$t8,0x278($sp)
.PF0f0416dc:
/*  f0416dc:	8fad025c */ 	lw	$t5,0x25c($sp)
/*  f0416e0:	8fab0098 */ 	lw	$t3,0x98($sp)
/*  f0416e4:	8f0c001c */ 	lw	$t4,0x1c($t8)
/*  f0416e8:	8fb90094 */ 	lw	$t9,0x94($sp)
/*  f0416ec:	8faa0090 */ 	lw	$t2,0x90($sp)
/*  f0416f0:	240e00c8 */ 	li	$t6,0xc8
/*  f0416f4:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f0416f8:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f0416fc:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f041700:	8fa5009c */ 	lw	$a1,0x9c($sp)
/*  f041704:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f041708:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f04170c:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f041710:	afab001c */ 	sw	$t3,0x1c($sp)
/*  f041714:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f041718:	afb90020 */ 	sw	$t9,0x20($sp)
/*  f04171c:	0fc0d0d1 */ 	jal	func0f0341dc
/*  f041720:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f041724:	10000010 */ 	b	.PF0f041768
/*  f041728:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
.PF0f04172c:
/*  f04172c:	11e00006 */ 	beqz	$t7,.PF0f041748
/*  f041730:	c7b201d0 */ 	lwc1	$f18,0x1d0($sp)
/*  f041734:	91e20000 */ 	lbu	$v0,0x0($t7)
/*  f041738:	24010003 */ 	li	$at,0x3
/*  f04173c:	10410009 */ 	beq	$v0,$at,.PF0f041764
/*  f041740:	24010006 */ 	li	$at,0x6
/*  f041744:	10410007 */ 	beq	$v0,$at,.PF0f041764
.PF0f041748:
/*  f041748:	3c017f1b */ 	lui	$at,0x7f1b
/*  f04174c:	c430a340 */ 	lwc1	$f16,-0x5cc0($at)
/*  f041750:	4610903c */ 	c.lt.s	$f18,$f16
/*  f041754:	00000000 */ 	nop
/*  f041758:	45020003 */ 	bc1fl	.PF0f041768
/*  f04175c:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
/*  f041760:	afa001f0 */ 	sw	$zero,0x1f0($sp)
.PF0f041764:
/*  f041764:	8fb801f0 */ 	lw	$t8,0x1f0($sp)
.PF0f041768:
/*  f041768:	8fac01cc */ 	lw	$t4,0x1cc($sp)
/*  f04176c:	530000e5 */ 	beqzl	$t8,.PF0f041b04
/*  f041770:	8fab01c0 */ 	lw	$t3,0x1c0($sp)
/*  f041774:	118000a2 */ 	beqz	$t4,.PF0f041a00
/*  f041778:	8fab0224 */ 	lw	$t3,0x224($sp)
/*  f04177c:	91820000 */ 	lbu	$v0,0x0($t4)
/*  f041780:	24010006 */ 	li	$at,0x6
/*  f041784:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f041788:	10410003 */ 	beq	$v0,$at,.PF0f041798
/*  f04178c:	24010003 */ 	li	$at,0x3
/*  f041790:	54410053 */ 	bnel	$v0,$at,.PF0f0418e0
/*  f041794:	24010001 */ 	li	$at,0x1
.PF0f041798:
/*  f041798:	15c0000c */ 	bnez	$t6,.PF0f0417cc
/*  f04179c:	8fad01bc */ 	lw	$t5,0x1bc($sp)
/*  f0417a0:	15a0000a */ 	bnez	$t5,.PF0f0417cc
/*  f0417a4:	8fab0278 */ 	lw	$t3,0x278($sp)
/*  f0417a8:	8d790018 */ 	lw	$t9,0x18($t3)
/*  f0417ac:	8faf01cc */ 	lw	$t7,0x1cc($sp)
/*  f0417b0:	01602825 */ 	move	$a1,$t3
/*  f0417b4:	332a0040 */ 	andi	$t2,$t9,0x40
/*  f0417b8:	11400045 */ 	beqz	$t2,.PF0f0418d0
/*  f0417bc:	24060002 */ 	li	$a2,0x2
/*  f0417c0:	0fc12b09 */ 	jal	chrCompareTeams
/*  f0417c4:	8de40004 */ 	lw	$a0,0x4($t7)
/*  f0417c8:	10400041 */ 	beqz	$v0,.PF0f0418d0
.PF0f0417cc:
/*  f0417cc:	2418ffff */ 	li	$t8,-1
/*  f0417d0:	240c00c8 */ 	li	$t4,0xc8
/*  f0417d4:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f0417d8:	afa00080 */ 	sw	$zero,0x80($sp)
/*  f0417dc:	afb8007c */ 	sw	$t8,0x7c($sp)
/*  f0417e0:	afac0078 */ 	sw	$t4,0x78($sp)
/*  f0417e4:	0fc2c87a */ 	jal	gsetGetDamage
/*  f0417e8:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f0417ec:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f0417f0:	e7a00074 */ 	swc1	$f0,0x74($sp)
/*  f0417f4:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f0417f8:	8cad0004 */ 	lw	$t5,0x4($a1)
/*  f0417fc:	2406ffff */ 	li	$a2,-1
/*  f041800:	0fc2a079 */ 	jal	bgunPlayPropHitSound
/*  f041804:	afad0070 */ 	sw	$t5,0x70($sp)
/*  f041808:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f04180c:	8c990020 */ 	lw	$t9,0x20($a0)
/*  f041810:	53200012 */ 	beqzl	$t9,.PF0f04185c
/*  f041814:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f041818:	0fc0d042 */ 	jal	chrGetShield
/*  f04181c:	00000000 */ 	nop
/*  f041820:	44805000 */ 	mtc1	$zero,$f10
/*  f041824:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f041828:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f04182c:	4600503c */ 	c.lt.s	$f10,$f0
/*  f041830:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f041834:	27a70084 */ 	addiu	$a3,$sp,0x84
/*  f041838:	27aa0078 */ 	addiu	$t2,$sp,0x78
/*  f04183c:	45000006 */ 	bc1f	.PF0f041858
/*  f041840:	27af0080 */ 	addiu	$t7,$sp,0x80
/*  f041844:	27ab007c */ 	addiu	$t3,$sp,0x7c
/*  f041848:	afab0018 */ 	sw	$t3,0x18($sp)
/*  f04184c:	afaa0010 */ 	sw	$t2,0x10($sp)
/*  f041850:	0fc1002c */ 	jal	chrCalculateShieldHit
/*  f041854:	afaf0014 */ 	sw	$t7,0x14($sp)
.PF0f041858:
/*  f041858:	8fac0278 */ 	lw	$t4,0x278($sp)
.PF0f04185c:
/*  f04185c:	27b801e0 */ 	addiu	$t8,$sp,0x1e0
/*  f041860:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f041864:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f041868:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f04186c:	8fa60078 */ 	lw	$a2,0x78($sp)
/*  f041870:	27a70228 */ 	addiu	$a3,$sp,0x228
/*  f041874:	0fc097f2 */ 	jal	chrEmitSparks
/*  f041878:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f04187c:	8fad0278 */ 	lw	$t5,0x278($sp)
/*  f041880:	8faa01cc */ 	lw	$t2,0x1cc($sp)
/*  f041884:	8faf0084 */ 	lw	$t7,0x84($sp)
/*  f041888:	8dae001c */ 	lw	$t6,0x1c($t5)
/*  f04188c:	8fab0080 */ 	lw	$t3,0x80($sp)
/*  f041890:	8fb8007c */ 	lw	$t8,0x7c($sp)
/*  f041894:	241900c8 */ 	li	$t9,0xc8
/*  f041898:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f04189c:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f0418a0:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f0418a4:	8fa50074 */ 	lw	$a1,0x74($sp)
/*  f0418a8:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f0418ac:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f0418b0:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f0418b4:	afaf001c */ 	sw	$t7,0x1c($sp)
/*  f0418b8:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0418bc:	afab0020 */ 	sw	$t3,0x20($sp)
/*  f0418c0:	0fc0d0d1 */ 	jal	func0f0341dc
/*  f0418c4:	afb80024 */ 	sw	$t8,0x24($sp)
/*  f0418c8:	1000006f */ 	b	.PF0f041a88
/*  f0418cc:	93ad0260 */ 	lbu	$t5,0x260($sp)
.PF0f0418d0:
/*  f0418d0:	afa00250 */ 	sw	$zero,0x250($sp)
/*  f0418d4:	1000006b */ 	b	.PF0f041a84
/*  f0418d8:	afa00268 */ 	sw	$zero,0x268($sp)
/*  f0418dc:	24010001 */ 	li	$at,0x1
.PF0f0418e0:
/*  f0418e0:	10410005 */ 	beq	$v0,$at,.PF0f0418f8
/*  f0418e4:	8fac01cc */ 	lw	$t4,0x1cc($sp)
/*  f0418e8:	24010004 */ 	li	$at,0x4
/*  f0418ec:	10410002 */ 	beq	$v0,$at,.PF0f0418f8
/*  f0418f0:	24010002 */ 	li	$at,0x2
/*  f0418f4:	14410063 */ 	bne	$v0,$at,.PF0f041a84
.PF0f0418f8:
/*  f0418f8:	3c19800a */ 	lui	$t9,0x800a
/*  f0418fc:	8f39a824 */ 	lw	$t9,-0x57dc($t9)
/*  f041900:	8d8d0004 */ 	lw	$t5,0x4($t4)
/*  f041904:	240effff */ 	li	$t6,-1
/*  f041908:	afae0068 */ 	sw	$t6,0x68($sp)
/*  f04190c:	13200004 */ 	beqz	$t9,.PF0f041920
/*  f041910:	afad006c */ 	sw	$t5,0x6c($sp)
/*  f041914:	0fc63831 */ 	jal	mpPlayerGetIndex
/*  f041918:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f04191c:	afa20068 */ 	sw	$v0,0x68($sp)
.PF0f041920:
/*  f041920:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041924:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f041928:	0fc2a079 */ 	jal	bgunPlayPropHitSound
/*  f04192c:	2406ffff */ 	li	$a2,-1
/*  f041930:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041934:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f041938:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f04193c:	0fc19841 */ 	jal	func0f065e74
/*  f041940:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041944:	240a0001 */ 	li	$t2,0x1
/*  f041948:	afaa0210 */ 	sw	$t2,0x210($sp)
/*  f04194c:	0fc4fc06 */ 	jal	chrIsUsingPaintball
/*  f041950:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041954:	1040000b */ 	beqz	$v0,.PF0f041984
/*  f041958:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f04195c:	240f0019 */ 	li	$t7,0x19
/*  f041960:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f041964:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f041968:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f04196c:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041970:	00003825 */ 	move	$a3,$zero
/*  f041974:	0fc4c159 */ 	jal	sparksCreate
/*  f041978:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f04197c:	10000007 */ 	b	.PF0f04199c
/*  f041980:	00000000 */ 	nop
.PF0f041984:
/*  f041984:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f041988:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f04198c:	00003825 */ 	move	$a3,$zero
/*  f041990:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f041994:	0fc4c159 */ 	jal	sparksCreate
/*  f041998:	afa00014 */ 	sw	$zero,0x14($sp)
.PF0f04199c:
/*  f04199c:	3c0b800a */ 	lui	$t3,0x800a
/*  f0419a0:	8178e58b */ 	lb	$t8,-0x1a75($t3)
/*  f0419a4:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f0419a8:	0701000a */ 	bgez	$t8,.PF0f0419d4
/*  f0419ac:	00000000 */ 	nop
/*  f0419b0:	918d0125 */ 	lbu	$t5,0x125($t4)
/*  f0419b4:	24010010 */ 	li	$at,0x10
/*  f0419b8:	8fae006c */ 	lw	$t6,0x6c($sp)
/*  f0419bc:	15a10005 */ 	bne	$t5,$at,.PF0f0419d4
/*  f0419c0:	00000000 */ 	nop
/*  f0419c4:	8dd9000c */ 	lw	$t9,0xc($t6)
/*  f0419c8:	332a0001 */ 	andi	$t2,$t9,0x1
/*  f0419cc:	5540002e */ 	bnezl	$t2,.PF0f041a88
/*  f0419d0:	93ad0260 */ 	lbu	$t5,0x260($sp)
.PF0f0419d4:
/*  f0419d4:	0fc2c87a */ 	jal	gsetGetDamage
/*  f0419d8:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f0419dc:	8faf0068 */ 	lw	$t7,0x68($sp)
/*  f0419e0:	44050000 */ 	mfc1	$a1,$f0
/*  f0419e4:	8fa4006c */ 	lw	$a0,0x6c($sp)
/*  f0419e8:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0419ec:	93a70260 */ 	lbu	$a3,0x260($sp)
/*  f0419f0:	0fc21530 */ 	jal	objTakeGunfire
/*  f0419f4:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0419f8:	10000023 */ 	b	.PF0f041a88
/*  f0419fc:	93ad0260 */ 	lbu	$t5,0x260($sp)
.PF0f041a00:
/*  f041a00:	11600020 */ 	beqz	$t3,.PF0f041a84
/*  f041a04:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041a08:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f041a0c:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041a10:	0fc19841 */ 	jal	func0f065e74
/*  f041a14:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041a18:	24180001 */ 	li	$t8,0x1
/*  f041a1c:	afb80210 */ 	sw	$t8,0x210($sp)
/*  f041a20:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041a24:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f041a28:	2406ffff */ 	li	$a2,-1
/*  f041a2c:	0fc2a245 */ 	jal	bgunPlayBgHitSound
/*  f041a30:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041a34:	0fc4fc06 */ 	jal	chrIsUsingPaintball
/*  f041a38:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041a3c:	1040000b */ 	beqz	$v0,.PF0f041a6c
/*  f041a40:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f041a44:	240c0019 */ 	li	$t4,0x19
/*  f041a48:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f041a4c:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f041a50:	00002825 */ 	move	$a1,$zero
/*  f041a54:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041a58:	00003825 */ 	move	$a3,$zero
/*  f041a5c:	0fc4c159 */ 	jal	sparksCreate
/*  f041a60:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f041a64:	10000008 */ 	b	.PF0f041a88
/*  f041a68:	93ad0260 */ 	lbu	$t5,0x260($sp)
.PF0f041a6c:
/*  f041a6c:	00002825 */ 	move	$a1,$zero
/*  f041a70:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041a74:	00003825 */ 	move	$a3,$zero
/*  f041a78:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f041a7c:	0fc4c159 */ 	jal	sparksCreate
/*  f041a80:	afa00014 */ 	sw	$zero,0x14($sp)
.PF0f041a84:
/*  f041a84:	93ad0260 */ 	lbu	$t5,0x260($sp)
.PF0f041a88:
/*  f041a88:	24010007 */ 	li	$at,0x7
/*  f041a8c:	93ae0263 */ 	lbu	$t6,0x263($sp)
/*  f041a90:	15a1001b */ 	bne	$t5,$at,.PF0f041b00
/*  f041a94:	24010001 */ 	li	$at,0x1
/*  f041a98:	15c10019 */ 	bne	$t6,$at,.PF0f041b00
/*  f041a9c:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f041aa0:	8f2a02d4 */ 	lw	$t2,0x2d4($t9)
/*  f041aa4:	3c03800a */ 	lui	$v1,0x800a
/*  f041aa8:	11400005 */ 	beqz	$t2,.PF0f041ac0
/*  f041aac:	00000000 */ 	nop
/*  f041ab0:	0fc63831 */ 	jal	mpPlayerGetIndex
/*  f041ab4:	03202025 */ 	move	$a0,$t9
/*  f041ab8:	10000002 */ 	b	.PF0f041ac4
/*  f041abc:	00401825 */ 	move	$v1,$v0
.PF0f041ac0:
/*  f041ac0:	8c63a79c */ 	lw	$v1,-0x5864($v1)
.PF0f041ac4:
/*  f041ac4:	8faf0210 */ 	lw	$t7,0x210($sp)
/*  f041ac8:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041acc:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f041ad0:	15e00005 */ 	bnez	$t7,.PF0f041ae8
/*  f041ad4:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041ad8:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041adc:	0fc19841 */ 	jal	func0f065e74
/*  f041ae0:	afa30064 */ 	sw	$v1,0x64($sp)
/*  f041ae4:	8fa30064 */ 	lw	$v1,0x64($sp)
.PF0f041ae8:
/*  f041ae8:	00002025 */ 	move	$a0,$zero
/*  f041aec:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f041af0:	27a60214 */ 	addiu	$a2,$sp,0x214
/*  f041af4:	24070016 */ 	li	$a3,0x16
/*  f041af8:	0fc4a8f4 */ 	jal	explosionCreateSimple
/*  f041afc:	afa30010 */ 	sw	$v1,0x10($sp)
.PF0f041b00:
/*  f041b00:	8fab01c0 */ 	lw	$t3,0x1c0($sp)
.PF0f041b04:
/*  f041b04:	8fa4025c */ 	lw	$a0,0x25c($sp)
/*  f041b08:	51600004 */ 	beqzl	$t3,.PF0f041b1c
/*  f041b0c:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f041b10:	0fc19102 */ 	jal	propSetPerimEnabled
/*  f041b14:	00002825 */ 	move	$a1,$zero
/*  f041b18:	8fa80268 */ 	lw	$t0,0x268($sp)
.PF0f041b1c:
/*  f041b1c:	8fac0250 */ 	lw	$t4,0x250($sp)
/*  f041b20:	93ad0260 */ 	lbu	$t5,0x260($sp)
/*  f041b24:	0008c02b */ 	sltu	$t8,$zero,$t0
/*  f041b28:	1180000e */ 	beqz	$t4,.PF0f041b64
/*  f041b2c:	03004025 */ 	move	$t0,$t8
/*  f041b30:	25aefffe */ 	addiu	$t6,$t5,-2
/*  f041b34:	2dc1002a */ 	sltiu	$at,$t6,0x2a
/*  f041b38:	10200009 */ 	beqz	$at,.PF0f041b60
/*  f041b3c:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f041b40:	3c017f1b */ 	lui	$at,0x7f1b
/*  f041b44:	002e0821 */ 	addu	$at,$at,$t6
/*  f041b48:	8c2ea344 */ 	lw	$t6,-0x5cbc($at)
/*  f041b4c:	01c00008 */ 	jr	$t6
/*  f041b50:	00000000 */ 	nop
/*  f041b54:	240a0001 */ 	li	$t2,0x1
/*  f041b58:	10000002 */ 	b	.PF0f041b64
/*  f041b5c:	afaa0250 */ 	sw	$t2,0x250($sp)
.PF0f041b60:
/*  f041b60:	afa00250 */ 	sw	$zero,0x250($sp)
.PF0f041b64:
/*  f041b64:	11000004 */ 	beqz	$t0,.PF0f041b78
/*  f041b68:	01003825 */ 	move	$a3,$t0
/*  f041b6c:	8fa70250 */ 	lw	$a3,0x250($sp)
/*  f041b70:	0007c82b */ 	sltu	$t9,$zero,$a3
/*  f041b74:	03203825 */ 	move	$a3,$t9
.PF0f041b78:
/*  f041b78:	27af0244 */ 	addiu	$t7,$sp,0x244
/*  f041b7c:	27ab0228 */ 	addiu	$t3,$sp,0x228
/*  f041b80:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f041b84:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f041b88:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041b8c:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f041b90:	8fa60268 */ 	lw	$a2,0x268($sp)
/*  f041b94:	0fc0f908 */ 	jal	chrCreateFireslot
/*  f041b98:	afa80054 */ 	sw	$t0,0x54($sp)
/*  f041b9c:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f041ba0:	8fa80054 */ 	lw	$t0,0x54($sp)
/*  f041ba4:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041ba8:	13000015 */ 	beqz	$t8,.PF0f041c00
/*  f041bac:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f041bb0:	1100000a */ 	beqz	$t0,.PF0f041bdc
/*  f041bb4:	01003025 */ 	move	$a2,$t0
/*  f041bb8:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f041bbc:	8fae027c */ 	lw	$t6,0x27c($sp)
/*  f041bc0:	8d8d02d4 */ 	lw	$t5,0x2d4($t4)
/*  f041bc4:	000e5080 */ 	sll	$t2,$t6,0x2
/*  f041bc8:	01aa1021 */ 	addu	$v0,$t5,$t2
/*  f041bcc:	8c430024 */ 	lw	$v1,0x24($v0)
/*  f041bd0:	18600002 */ 	blez	$v1,.PF0f041bdc
/*  f041bd4:	2479ffff */ 	addiu	$t9,$v1,-1
/*  f041bd8:	ac590024 */ 	sw	$t9,0x24($v0)
.PF0f041bdc:
/*  f041bdc:	11000004 */ 	beqz	$t0,.PF0f041bf0
/*  f041be0:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041be4:	93a6026e */ 	lbu	$a2,0x26e($sp)
/*  f041be8:	0006782b */ 	sltu	$t7,$zero,$a2
/*  f041bec:	01e03025 */ 	move	$a2,$t7
.PF0f041bf0:
/*  f041bf0:	0fc0fe73 */ 	jal	chrSetFiring
/*  f041bf4:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f041bf8:	10000004 */ 	b	.PF0f041c0c
/*  f041bfc:	8fbf0044 */ 	lw	$ra,0x44($sp)
.PF0f041c00:
/*  f041c00:	0fc0fe73 */ 	jal	chrSetFiring
/*  f041c04:	8fa60268 */ 	lw	$a2,0x268($sp)
/*  f041c08:	8fbf0044 */ 	lw	$ra,0x44($sp)
.PF0f041c0c:
/*  f041c0c:	27bd0278 */ 	addiu	$sp,$sp,0x278
/*  f041c10:	03e00008 */ 	jr	$ra
/*  f041c14:	00000000 */ 	nop
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f0404d4
.late_rodata
glabel var7f1a90c8
.word 0x3d638e39
glabel var7f1a90cc
.word 0x481c4000
glabel var7f1a90d0
.word 0x3fd55555
glabel var7f1a90d4
.word 0x3fd55555
glabel var7f1a90d8
.word 0x3fd55555
glabel var7f1a90dc
.word 0x461c4000
glabel var7f1a90e0
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90e4
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90e8
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90ec
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90f0
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90f4
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90f8
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a90fc
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9100
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9104
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9108
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a910c
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9110
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9114
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9118
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a911c
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9120
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9124
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9128
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a912c
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9130
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9134
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9138
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a913c
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9140
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9144
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9148
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a914c
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9150
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9154
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9158
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a915c
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9160
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9164
.word func0f0404d4+0x14e8 # f0419bc
glabel var7f1a9168
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a916c
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9170
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9174
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9178
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a917c
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9180
.word func0f0404d4+0x14dc # f0419b0
glabel var7f1a9184
.word func0f0404d4+0x14dc # f0419b0
.text
/*  f0404d4:	27bdfd88 */ 	addiu	$sp,$sp,-632
/*  f0404d8:	afbf0044 */ 	sw	$ra,0x44($sp)
/*  f0404dc:	afa5027c */ 	sw	$a1,0x27c($sp)
/*  f0404e0:	8c8e001c */ 	lw	$t6,0x1c($a0)
/*  f0404e4:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f0404e8:	a3af026e */ 	sb	$t7,0x26e($sp)
/*  f0404ec:	afae0274 */ 	sw	$t6,0x274($sp)
/*  f0404f0:	8c9802d4 */ 	lw	$t8,0x2d4($a0)
/*  f0404f4:	00001025 */ 	or	$v0,$zero,$zero
/*  f0404f8:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f0404fc:	53000003 */ 	beqzl	$t8,.L0f04050c
/*  f040500:	a3a2026f */ 	sb	$v0,0x26f($sp)
/*  f040504:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f040508:	a3a2026f */ 	sb	$v0,0x26f($sp)
.L0f04050c:
/*  f04050c:	0fc0a209 */ 	jal	chrGetHeldProp
/*  f040510:	afa40278 */ 	sw	$a0,0x278($sp)
/*  f040514:	50400554 */ 	beqzl	$v0,.L0f041a68
/*  f040518:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*  f04051c:	afa00268 */ 	sw	$zero,0x268($sp)
/*  f040520:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f040524:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040528:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f04052c:	afb90264 */ 	sw	$t9,0x264($sp)
/*  f040530:	8fab0264 */ 	lw	$t3,0x264($sp)
/*  f040534:	afa2025c */ 	sw	$v0,0x25c($sp)
/*  f040538:	8fa70278 */ 	lw	$a3,0x278($sp)
/*  f04053c:	8961005c */ 	lwl	$at,0x5c($t3)
/*  f040540:	9961005f */ 	lwr	$at,0x5f($t3)
/*  f040544:	27aa0260 */ 	addiu	$t2,$sp,0x260
/*  f040548:	24080200 */ 	addiu	$t0,$zero,0x200
/*  f04054c:	ad410000 */ 	sw	$at,0x0($t2)
/*  f040550:	80e30007 */ 	lb	$v1,0x7($a3)
/*  f040554:	24010008 */ 	addiu	$at,$zero,0x8
/*  f040558:	10610007 */ 	beq	$v1,$at,.L0f040578
/*  f04055c:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f040560:	10610005 */ 	beq	$v1,$at,.L0f040578
/*  f040564:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f040568:	10610003 */ 	beq	$v1,$at,.L0f040578
/*  f04056c:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f040570:	54610003 */ 	bnel	$v1,$at,.L0f040580
/*  f040574:	afa00250 */ 	sw	$zero,0x250($sp)
.L0f040578:
/*  f040578:	8ce8004c */ 	lw	$t0,0x4c($a3)
/*  f04057c:	afa00250 */ 	sw	$zero,0x250($sp)
.L0f040580:
/*  f040580:	afa00224 */ 	sw	$zero,0x224($sp)
/*  f040584:	afa00210 */ 	sw	$zero,0x210($sp)
/*  f040588:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f04058c:	93a50263 */ 	lbu	$a1,0x263($sp)
/*  f040590:	afa00254 */ 	sw	$zero,0x254($sp)
/*  f040594:	0fc2c7ba */ 	jal	weaponGetNumTicksPerShot
/*  f040598:	afa80258 */ 	sw	$t0,0x258($sp)
/*  f04059c:	8fa60254 */ 	lw	$a2,0x254($sp)
/*  f0405a0:	1c400005 */ 	bgtz	$v0,.L0f0405b8
/*  f0405a4:	00402025 */ 	or	$a0,$v0,$zero
/*  f0405a8:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f0405ac:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f0405b0:	10000055 */ 	b	.L0f040708
/*  f0405b4:	afaf0250 */ 	sw	$t7,0x250($sp)
.L0f0405b8:
/*  f0405b8:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f0405bc:	8f0302d4 */ 	lw	$v1,0x2d4($t8)
/*  f0405c0:	5060001d */ 	beqzl	$v1,.L0f040638
/*  f0405c4:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f0405c8:	8c790020 */ 	lw	$t9,0x20($v1)
/*  f0405cc:	24010014 */ 	addiu	$at,$zero,0x14
/*  f0405d0:	57210019 */ 	bnel	$t9,$at,.L0f040638
/*  f0405d4:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f0405d8:	8c6d004c */ 	lw	$t5,0x4c($v1)
/*  f0405dc:	8fab027c */ 	lw	$t3,0x27c($sp)
/*  f0405e0:	000d5080 */ 	sll	$t2,$t5,0x2
/*  f0405e4:	05400013 */ 	bltz	$t2,.L0f040634
/*  f0405e8:	000b7040 */ 	sll	$t6,$t3,0x1
/*  f0405ec:	006e7821 */ 	addu	$t7,$v1,$t6
/*  f0405f0:	85f800e0 */ 	lh	$t8,0xe0($t7)
/*  f0405f4:	2419005a */ 	addiu	$t9,$zero,0x5a
/*  f0405f8:	3c017f1b */ 	lui	$at,%hi(var7f1a90c8)
/*  f0405fc:	03386823 */ 	subu	$t5,$t9,$t8
/*  f040600:	448d2000 */ 	mtc1	$t5,$f4
/*  f040604:	c42890c8 */ 	lwc1	$f8,%lo(var7f1a90c8)($at)
/*  f040608:	44825000 */ 	mtc1	$v0,$f10
/*  f04060c:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f040610:	3c013f80 */ 	lui	$at,0x3f80
/*  f040614:	44819000 */ 	mtc1	$at,$f18
/*  f040618:	46805420 */ 	cvt.s.w	$f16,$f10
/*  f04061c:	46083002 */ 	mul.s	$f0,$f6,$f8
/*  f040620:	46009100 */ 	add.s	$f4,$f18,$f0
/*  f040624:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f040628:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f04062c:	44044000 */ 	mfc1	$a0,$f8
/*  f040630:	00000000 */ 	nop
.L0f040634:
/*  f040634:	8faa0278 */ 	lw	$t2,0x278($sp)
.L0f040638:
/*  f040638:	8fab027c */ 	lw	$t3,0x27c($sp)
/*  f04063c:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x38)
/*  f040640:	8def9ff8 */ 	lw	$t7,%lo(g_Vars+0x38)($t7)
/*  f040644:	014b1821 */ 	addu	$v1,$t2,$t3
/*  f040648:	906e0004 */ 	lbu	$t6,0x4($v1)
/*  f04064c:	01cfc821 */ 	addu	$t9,$t6,$t7
/*  f040650:	333800ff */ 	andi	$t8,$t9,0xff
/*  f040654:	0304082a */ 	slt	$at,$t8,$a0
/*  f040658:	1420002b */ 	bnez	$at,.L0f040708
/*  f04065c:	a0790004 */ 	sb	$t9,0x4($v1)
/*  f040660:	a0600004 */ 	sb	$zero,0x4($v1)
/*  f040664:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f040668:	8fad027c */ 	lw	$t5,0x27c($sp)
/*  f04066c:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f040670:	8d4b032c */ 	lw	$t3,0x32c($t2)
/*  f040674:	01ac1004 */ 	sllv	$v0,$t4,$t5
/*  f040678:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f04067c:	000b7300 */ 	sll	$t6,$t3,0xc
/*  f040680:	914b032d */ 	lbu	$t3,0x32d($t2)
/*  f040684:	000e7f82 */ 	srl	$t7,$t6,0x1e
/*  f040688:	01e2c026 */ 	xor	$t8,$t7,$v0
/*  f04068c:	00186080 */ 	sll	$t4,$t8,0x2
/*  f040690:	318d000c */ 	andi	$t5,$t4,0xc
/*  f040694:	316efff3 */ 	andi	$t6,$t3,0xfff3
/*  f040698:	01ae7825 */ 	or	$t7,$t5,$t6
/*  f04069c:	a14f032d */ 	sb	$t7,0x32d($t2)
/*  f0406a0:	8d59032c */ 	lw	$t9,0x32c($t2)
/*  f0406a4:	93ad0260 */ 	lbu	$t5,0x260($sp)
/*  f0406a8:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f0406ac:	0019c300 */ 	sll	$t8,$t9,0xc
/*  f0406b0:	00186782 */ 	srl	$t4,$t8,0x1e
/*  f0406b4:	01825824 */ 	and	$t3,$t4,$v0
/*  f0406b8:	15600003 */ 	bnez	$t3,.L0f0406c8
/*  f0406bc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f0406c0:	55a10003 */ 	bnel	$t5,$at,.L0f0406d0
/*  f0406c4:	8faf0278 */ 	lw	$t7,0x278($sp)
.L0f0406c8:
/*  f0406c8:	afae0250 */ 	sw	$t6,0x250($sp)
/*  f0406cc:	8faf0278 */ 	lw	$t7,0x278($sp)
.L0f0406d0:
/*  f0406d0:	24010008 */ 	addiu	$at,$zero,0x8
/*  f0406d4:	81ea0007 */ 	lb	$t2,0x7($t7)
/*  f0406d8:	1541000b */ 	bne	$t2,$at,.L0f040708
/*  f0406dc:	00000000 */ 	nop
/*  f0406e0:	8de40020 */ 	lw	$a0,0x20($t7)
/*  f0406e4:	0c00744f */ 	jal	modelGetAnimNum
/*  f0406e8:	afa60254 */ 	sw	$a2,0x254($sp)
/*  f0406ec:	2401026a */ 	addiu	$at,$zero,0x26a
/*  f0406f0:	14410005 */ 	bne	$v0,$at,.L0f040708
/*  f0406f4:	8fa60254 */ 	lw	$a2,0x254($sp)
/*  f0406f8:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f0406fc:	83380033 */ 	lb	$t8,0x33($t9)
/*  f040700:	270c0001 */ 	addiu	$t4,$t8,0x1
/*  f040704:	a32c0033 */ 	sb	$t4,0x33($t9)
.L0f040708:
/*  f040708:	50c0049b */ 	beqzl	$a2,.L0f041978
/*  f04070c:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f040710:	0fc0f97c */ 	jal	chrGetAimAngle
/*  f040714:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040718:	e7a00204 */ 	swc1	$f0,0x204($sp)
/*  f04071c:	0fc0f9d5 */ 	jal	func0f03e754
/*  f040720:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040724:	93ab026f */ 	lbu	$t3,0x26f($sp)
/*  f040728:	e7a00200 */ 	swc1	$f0,0x200($sp)
/*  f04072c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f040730:	11600004 */ 	beqz	$t3,.L0f040744
/*  f040734:	27a60244 */ 	addiu	$a2,$sp,0x244
/*  f040738:	240d0004 */ 	addiu	$t5,$zero,0x4
/*  f04073c:	10000002 */ 	b	.L0f040748
/*  f040740:	afad01fc */ 	sw	$t5,0x1fc($sp)
.L0f040744:
/*  f040744:	afa001fc */ 	sw	$zero,0x1fc($sp)
.L0f040748:
/*  f040748:	afae0268 */ 	sw	$t6,0x268($sp)
/*  f04074c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040750:	0fc0ff79 */ 	jal	func0f03fde4
/*  f040754:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f040758:	54400032 */ 	bnezl	$v0,.L0f040824
/*  f04075c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040760:	8fa20274 */ 	lw	$v0,0x274($sp)
/*  f040764:	3c0141f0 */ 	lui	$at,0x41f0
/*  f040768:	44818000 */ 	mtc1	$at,$f16
/*  f04076c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f040770:	8faa027c */ 	lw	$t2,0x27c($sp)
/*  f040774:	24010001 */ 	addiu	$at,$zero,0x1
/*  f040778:	e7aa0244 */ 	swc1	$f10,0x244($sp)
/*  f04077c:	c452000c */ 	lwc1	$f18,0xc($v0)
/*  f040780:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f040784:	e7a40248 */ 	swc1	$f4,0x248($sp)
/*  f040788:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f04078c:	15410013 */ 	bne	$t2,$at,.L0f0407dc
/*  f040790:	e7a6024c */ 	swc1	$f6,0x24c($sp)
/*  f040794:	0c0068f4 */ 	jal	cosf
/*  f040798:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f04079c:	3c014120 */ 	lui	$at,0x4120
/*  f0407a0:	44815000 */ 	mtc1	$at,$f10
/*  f0407a4:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f0407a8:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f0407ac:	460a0482 */ 	mul.s	$f18,$f0,$f10
/*  f0407b0:	46124400 */ 	add.s	$f16,$f8,$f18
/*  f0407b4:	0c0068f7 */ 	jal	sinf
/*  f0407b8:	e7b00244 */ 	swc1	$f16,0x244($sp)
/*  f0407bc:	3c014120 */ 	lui	$at,0x4120
/*  f0407c0:	44813000 */ 	mtc1	$at,$f6
/*  f0407c4:	46000107 */ 	neg.s	$f4,$f0
/*  f0407c8:	c7a8024c */ 	lwc1	$f8,0x24c($sp)
/*  f0407cc:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f0407d0:	460a4480 */ 	add.s	$f18,$f8,$f10
/*  f0407d4:	10000012 */ 	b	.L0f040820
/*  f0407d8:	e7b2024c */ 	swc1	$f18,0x24c($sp)
.L0f0407dc:
/*  f0407dc:	0c0068f4 */ 	jal	cosf
/*  f0407e0:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f0407e4:	3c014120 */ 	lui	$at,0x4120
/*  f0407e8:	44812000 */ 	mtc1	$at,$f4
/*  f0407ec:	46000407 */ 	neg.s	$f16,$f0
/*  f0407f0:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f0407f4:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f0407f8:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f0407fc:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f040800:	0c0068f7 */ 	jal	sinf
/*  f040804:	e7aa0244 */ 	swc1	$f10,0x244($sp)
/*  f040808:	3c014120 */ 	lui	$at,0x4120
/*  f04080c:	44818000 */ 	mtc1	$at,$f16
/*  f040810:	c7b2024c */ 	lwc1	$f18,0x24c($sp)
/*  f040814:	46100102 */ 	mul.s	$f4,$f0,$f16
/*  f040818:	46049200 */ 	add.s	$f8,$f18,$f4
/*  f04081c:	e7a8024c */ 	swc1	$f8,0x24c($sp)
.L0f040820:
/*  f040820:	8fa40278 */ 	lw	$a0,0x278($sp)
.L0f040824:
/*  f040824:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f040828:	00002825 */ 	or	$a1,$zero,$zero
/*  f04082c:	8fb801fc */ 	lw	$t8,0x1fc($sp)
/*  f040830:	8faf0274 */ 	lw	$t7,0x274($sp)
/*  f040834:	24190010 */ 	addiu	$t9,$zero,0x10
/*  f040838:	370c082a */ 	ori	$t4,$t8,0x82a
/*  f04083c:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f040840:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f040844:	27a60244 */ 	addiu	$a2,$sp,0x244
/*  f040848:	27a70234 */ 	addiu	$a3,$sp,0x234
/*  f04084c:	25e40008 */ 	addiu	$a0,$t7,0x8
/*  f040850:	0c00b78d */ 	jal	cd0002de34
/*  f040854:	25e50028 */ 	addiu	$a1,$t7,0x28
/*  f040858:	14400002 */ 	bnez	$v0,.L0f040864
/*  f04085c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f040860:	afa00268 */ 	sw	$zero,0x268($sp)
.L0f040864:
/*  f040864:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f040868:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f04086c:	8fab0268 */ 	lw	$t3,0x268($sp)
/*  f040870:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f040874:	51600440 */ 	beqzl	$t3,.L0f041978
/*  f040878:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f04087c:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f040880:	afa001f8 */ 	sw	$zero,0x1f8($sp)
/*  f040884:	afa001f4 */ 	sw	$zero,0x1f4($sp)
/*  f040888:	afad01f0 */ 	sw	$t5,0x1f0($sp)
/*  f04088c:	11c00004 */ 	beqz	$t6,.L0f0408a0
/*  f040890:	afa001cc */ 	sw	$zero,0x1cc($sp)
/*  f040894:	240a083f */ 	addiu	$t2,$zero,0x83f
/*  f040898:	10000003 */ 	b	.L0f0408a8
/*  f04089c:	afaa01c8 */ 	sw	$t2,0x1c8($sp)
.L0f0408a0:
/*  f0408a0:	240f083b */ 	addiu	$t7,$zero,0x83b
/*  f0408a4:	afaf01c8 */ 	sw	$t7,0x1c8($sp)
.L0f0408a8:
/*  f0408a8:	8fa7025c */ 	lw	$a3,0x25c($sp)
/*  f0408ac:	8ce20004 */ 	lw	$v0,0x4($a3)
/*  f0408b0:	50400004 */ 	beqzl	$v0,.L0f0408c4
/*  f0408b4:	00004825 */ 	or	$t1,$zero,$zero
/*  f0408b8:	10000002 */ 	b	.L0f0408c4
/*  f0408bc:	904902fe */ 	lbu	$t1,0x2fe($v0)
/*  f0408c0:	00004825 */ 	or	$t1,$zero,$zero
.L0f0408c4:
/*  f0408c4:	39220003 */ 	xori	$v0,$t1,0x3
/*  f0408c8:	2c420001 */ 	sltiu	$v0,$v0,0x1
/*  f0408cc:	1040000f */ 	beqz	$v0,.L0f04090c
/*  f0408d0:	00401825 */ 	or	$v1,$v0,$zero
/*  f0408d4:	afa2005c */ 	sw	$v0,0x5c($sp)
/*  f0408d8:	0fc12472 */ 	jal	chrGetDistanceToTarget
/*  f0408dc:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0408e0:	3c014316 */ 	lui	$at,0x4316
/*  f0408e4:	44813000 */ 	mtc1	$at,$f6
/*  f0408e8:	0000c025 */ 	or	$t8,$zero,$zero
/*  f0408ec:	4600303c */ 	c.lt.s	$f6,$f0
/*  f0408f0:	00000000 */ 	nop
/*  f0408f4:	45020003 */ 	bc1fl	.L0f040904
/*  f0408f8:	afb8005c */ 	sw	$t8,0x5c($sp)
/*  f0408fc:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f040900:	afb8005c */ 	sw	$t8,0x5c($sp)
.L0f040904:
/*  f040904:	8fa7025c */ 	lw	$a3,0x25c($sp)
/*  f040908:	03001825 */ 	or	$v1,$t8,$zero
.L0f04090c:
/*  f04090c:	afa301c0 */ 	sw	$v1,0x1c0($sp)
/*  f040910:	10600016 */ 	beqz	$v1,.L0f04096c
/*  f040914:	afa001bc */ 	sw	$zero,0x1bc($sp)
/*  f040918:	c4ea0008 */ 	lwc1	$f10,0x8($a3)
/*  f04091c:	c7b00244 */ 	lwc1	$f16,0x244($sp)
/*  f040920:	c7a80248 */ 	lwc1	$f8,0x248($sp)
/*  f040924:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f040928:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f04092c:	c7b0024c */ 	lwc1	$f16,0x24c($sp)
/*  f040930:	27a501e4 */ 	addiu	$a1,$sp,0x1e4
/*  f040934:	27a601e8 */ 	addiu	$a2,$sp,0x1e8
/*  f040938:	e7b201e0 */ 	swc1	$f18,0x1e0($sp)
/*  f04093c:	c4e4000c */ 	lwc1	$f4,0xc($a3)
/*  f040940:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f040944:	e7a601e4 */ 	swc1	$f6,0x1e4($sp)
/*  f040948:	c4ea0010 */ 	lwc1	$f10,0x10($a3)
/*  f04094c:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f040950:	0c0011e4 */ 	jal	guNormalize
/*  f040954:	e7b201e8 */ 	swc1	$f18,0x1e8($sp)
/*  f040958:	8fa4025c */ 	lw	$a0,0x25c($sp)
/*  f04095c:	0fc1905e */ 	jal	propSetPerimEnabled
/*  f040960:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f040964:	1000002f */ 	b	.L0f040a24
/*  f040968:	8fab0278 */ 	lw	$t3,0x278($sp)
.L0f04096c:
/*  f04096c:	0c0068f4 */ 	jal	cosf
/*  f040970:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040974:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*  f040978:	0c0068f7 */ 	jal	sinf
/*  f04097c:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040980:	c7a40060 */ 	lwc1	$f4,0x60($sp)
/*  f040984:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040988:	46040202 */ 	mul.s	$f8,$f0,$f4
/*  f04098c:	0c0068f7 */ 	jal	sinf
/*  f040990:	e7a801e0 */ 	swc1	$f8,0x1e0($sp)
/*  f040994:	e7a001e4 */ 	swc1	$f0,0x1e4($sp)
/*  f040998:	0c0068f4 */ 	jal	cosf
/*  f04099c:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f0409a0:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*  f0409a4:	0c0068f4 */ 	jal	cosf
/*  f0409a8:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f0409ac:	c7a60060 */ 	lwc1	$f6,0x60($sp)
/*  f0409b0:	93ac026f */ 	lbu	$t4,0x26f($sp)
/*  f0409b4:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f0409b8:	11800019 */ 	beqz	$t4,.L0f040a20
/*  f0409bc:	e7aa01e8 */ 	swc1	$f10,0x1e8($sp)
/*  f0409c0:	0fc644fe */ 	jal	chrGuessCrouchPos
/*  f0409c4:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0409c8:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f0409cc:	00404825 */ 	or	$t1,$v0,$zero
/*  f0409d0:	8fae0278 */ 	lw	$t6,0x278($sp)
/*  f0409d4:	8f280170 */ 	lw	$t0,0x170($t9)
/*  f0409d8:	0008582b */ 	sltu	$t3,$zero,$t0
/*  f0409dc:	11600004 */ 	beqz	$t3,.L0f0409f0
/*  f0409e0:	01604025 */ 	or	$t0,$t3,$zero
/*  f0409e4:	8f280174 */ 	lw	$t0,0x174($t9)
/*  f0409e8:	0008682b */ 	sltu	$t5,$zero,$t0
/*  f0409ec:	01a04025 */ 	or	$t0,$t5,$zero
.L0f0409f0:
/*  f0409f0:	8dc302d4 */ 	lw	$v1,0x2d4($t6)
/*  f0409f4:	8fb8027c */ 	lw	$t8,0x27c($sp)
/*  f0409f8:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f0409fc:	8c66004c */ 	lw	$a2,0x4c($v1)
/*  f040a00:	00786021 */ 	addu	$t4,$v1,$t8
/*  f040a04:	9187004d */ 	lbu	$a3,0x4d($t4)
/*  f040a08:	8c650020 */ 	lw	$a1,0x20($v1)
/*  f040a0c:	00065080 */ 	sll	$t2,$a2,0x2
/*  f040a10:	000a37c2 */ 	srl	$a2,$t2,0x1f
/*  f040a14:	afa80014 */ 	sw	$t0,0x14($sp)
/*  f040a18:	0fc283eb */ 	jal	bgun0f0a0fac
/*  f040a1c:	afa90010 */ 	sw	$t1,0x10($sp)
.L0f040a20:
/*  f040a20:	8fab0278 */ 	lw	$t3,0x278($sp)
.L0f040a24:
/*  f040a24:	93b90260 */ 	lbu	$t9,0x260($sp)
/*  f040a28:	24010016 */ 	addiu	$at,$zero,0x16
/*  f040a2c:	8d6302d4 */ 	lw	$v1,0x2d4($t3)
/*  f040a30:	50600018 */ 	beqzl	$v1,.L0f040a94
/*  f040a34:	3c014780 */ 	lui	$at,0x4780
/*  f040a38:	57210016 */ 	bnel	$t9,$at,.L0f040a94
/*  f040a3c:	3c014780 */ 	lui	$at,0x4780
/*  f040a40:	8c6d0128 */ 	lw	$t5,0x128($v1)
/*  f040a44:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f040a48:	01602025 */ 	or	$a0,$t3,$zero
/*  f040a4c:	15a00010 */ 	bnez	$t5,.L0f040a90
/*  f040a50:	00002825 */ 	or	$a1,$zero,$zero
/*  f040a54:	afae0250 */ 	sw	$t6,0x250($sp)
/*  f040a58:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f040a5c:	0fc667e1 */ 	jal	aibotDoFarsightThing
/*  f040a60:	27a70244 */ 	addiu	$a3,$sp,0x244
/*  f040a64:	24010002 */ 	addiu	$at,$zero,0x2
/*  f040a68:	5441000a */ 	bnel	$v0,$at,.L0f040a94
/*  f040a6c:	3c014780 */ 	lui	$at,0x4780
/*  f040a70:	0c004b70 */ 	jal	random
/*  f040a74:	00000000 */ 	nop
/*  f040a78:	240100ff */ 	addiu	$at,$zero,0xff
/*  f040a7c:	0041001b */ 	divu	$zero,$v0,$at
/*  f040a80:	00005010 */ 	mfhi	$t2
/*  f040a84:	2d4f00c9 */ 	sltiu	$t7,$t2,0xc9
/*  f040a88:	39ef0001 */ 	xori	$t7,$t7,0x1
/*  f040a8c:	a3af026e */ 	sb	$t7,0x26e($sp)
.L0f040a90:
/*  f040a90:	3c014780 */ 	lui	$at,0x4780
.L0f040a94:
/*  f040a94:	44810000 */ 	mtc1	$at,$f0
/*  f040a98:	c7b001e0 */ 	lwc1	$f16,0x1e0($sp)
/*  f040a9c:	c7a40244 */ 	lwc1	$f4,0x244($sp)
/*  f040aa0:	c7a601e4 */ 	lwc1	$f6,0x1e4($sp)
/*  f040aa4:	46008482 */ 	mul.s	$f18,$f16,$f0
/*  f040aa8:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f040aac:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040ab0:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f040ab4:	c7a6024c */ 	lwc1	$f6,0x24c($sp)
/*  f040ab8:	00002825 */ 	or	$a1,$zero,$zero
/*  f040abc:	46049200 */ 	add.s	$f8,$f18,$f4
/*  f040ac0:	c7a401e8 */ 	lwc1	$f4,0x1e8($sp)
/*  f040ac4:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f040ac8:	e7a80228 */ 	swc1	$f8,0x228($sp)
/*  f040acc:	46002202 */ 	mul.s	$f8,$f4,$f0
/*  f040ad0:	e7b2022c */ 	swc1	$f18,0x22c($sp)
/*  f040ad4:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f040ad8:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f040adc:	e7aa0230 */ 	swc1	$f10,0x230($sp)
/*  f040ae0:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f040ae4:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f040ae8:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f040aec:	13000004 */ 	beqz	$t8,.L0f040b00
/*  f040af0:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f040af4:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f040af8:	3c01800a */ 	lui	$at,%hi(g_Vars+0x48c)
/*  f040afc:	ac2ca44c */ 	sw	$t4,%lo(g_Vars+0x48c)($at)
.L0f040b00:
/*  f040b00:	24190010 */ 	addiu	$t9,$zero,0x10
/*  f040b04:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f040b08:	0c00b764 */ 	jal	cdTestAToB4
/*  f040b0c:	8fa701c8 */ 	lw	$a3,0x1c8($sp)
/*  f040b10:	1440000a */ 	bnez	$v0,.L0f040b3c
/*  f040b14:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f040b18:	3c067f1b */ 	lui	$a2,%hi(var7f1a8af4)
/*  f040b1c:	afad0224 */ 	sw	$t5,0x224($sp)
/*  f040b20:	24c68af4 */ 	addiu	$a2,$a2,%lo(var7f1a8af4)
/*  f040b24:	27a40228 */ 	addiu	$a0,$sp,0x228
/*  f040b28:	0c0093af */ 	jal	cdGetPos
/*  f040b2c:	24052f28 */ 	addiu	$a1,$zero,0x2f28
/*  f040b30:	0c0093ac */ 	jal	cdGetObstacle
/*  f040b34:	00000000 */ 	nop
/*  f040b38:	afa201cc */ 	sw	$v0,0x1cc($sp)
.L0f040b3c:
/*  f040b3c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040b40:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f040b44:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f040b48:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f040b4c:	3c01800a */ 	lui	$at,%hi(g_Vars+0x48c)
/*  f040b50:	51c00003 */ 	beqzl	$t6,.L0f040b60
/*  f040b54:	8fab01cc */ 	lw	$t3,0x1cc($sp)
/*  f040b58:	ac20a44c */ 	sw	$zero,%lo(g_Vars+0x48c)($at)
/*  f040b5c:	8fab01cc */ 	lw	$t3,0x1cc($sp)
.L0f040b60:
/*  f040b60:	8faa01c0 */ 	lw	$t2,0x1c0($sp)
/*  f040b64:	55600015 */ 	bnezl	$t3,.L0f040bbc
/*  f040b68:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f040b6c:	51400013 */ 	beqzl	$t2,.L0f040bbc
/*  f040b70:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f040b74:	0c004b70 */ 	jal	random
/*  f040b78:	00000000 */ 	nop
/*  f040b7c:	24010064 */ 	addiu	$at,$zero,0x64
/*  f040b80:	0041001b */ 	divu	$zero,$v0,$at
/*  f040b84:	00001810 */ 	mfhi	$v1
/*  f040b88:	2c6f0033 */ 	sltiu	$t7,$v1,0x33
/*  f040b8c:	39ef0001 */ 	xori	$t7,$t7,0x1
/*  f040b90:	11e00009 */ 	beqz	$t7,.L0f040bb8
/*  f040b94:	afaf01bc */ 	sw	$t7,0x1bc($sp)
/*  f040b98:	8fb8025c */ 	lw	$t8,0x25c($sp)
/*  f040b9c:	afb801cc */ 	sw	$t8,0x1cc($sp)
/*  f040ba0:	c7100008 */ 	lwc1	$f16,0x8($t8)
/*  f040ba4:	e7b00228 */ 	swc1	$f16,0x228($sp)
/*  f040ba8:	c712000c */ 	lwc1	$f18,0xc($t8)
/*  f040bac:	e7b2022c */ 	swc1	$f18,0x22c($sp)
/*  f040bb0:	c7040010 */ 	lwc1	$f4,0x10($t8)
/*  f040bb4:	e7a40230 */ 	swc1	$f4,0x230($sp)
.L0f040bb8:
/*  f040bb8:	c7a80228 */ 	lwc1	$f8,0x228($sp)
.L0f040bbc:
/*  f040bbc:	c7a60244 */ 	lwc1	$f6,0x244($sp)
/*  f040bc0:	c7aa022c */ 	lwc1	$f10,0x22c($sp)
/*  f040bc4:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f040bc8:	46064001 */ 	sub.s	$f0,$f8,$f6
/*  f040bcc:	c7b20230 */ 	lwc1	$f18,0x230($sp)
/*  f040bd0:	c7a4024c */ 	lwc1	$f4,0x24c($sp)
/*  f040bd4:	46105081 */ 	sub.s	$f2,$f10,$f16
/*  f040bd8:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f040bdc:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040be0:	46049301 */ 	sub.s	$f12,$f18,$f4
/*  f040be4:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f040be8:	24010018 */ 	addiu	$at,$zero,0x18
/*  f040bec:	460c6402 */ 	mul.s	$f16,$f12,$f12
/*  f040bf0:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f040bf4:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f040bf8:	1081000f */ 	beq	$a0,$at,.L0f040c38
/*  f040bfc:	e7b201d0 */ 	swc1	$f18,0x1d0($sp)
/*  f040c00:	24010019 */ 	addiu	$at,$zero,0x19
/*  f040c04:	1081000c */ 	beq	$a0,$at,.L0f040c38
/*  f040c08:	24010012 */ 	addiu	$at,$zero,0x12
/*  f040c0c:	14810003 */ 	bne	$a0,$at,.L0f040c1c
/*  f040c10:	93ac0263 */ 	lbu	$t4,0x263($sp)
/*  f040c14:	24010001 */ 	addiu	$at,$zero,0x1
/*  f040c18:	11810007 */ 	beq	$t4,$at,.L0f040c38
.L0f040c1c:
/*  f040c1c:	24010017 */ 	addiu	$at,$zero,0x17
/*  f040c20:	10810005 */ 	beq	$a0,$at,.L0f040c38
/*  f040c24:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f040c28:	10810003 */ 	beq	$a0,$at,.L0f040c38
/*  f040c2c:	24010034 */ 	addiu	$at,$zero,0x34
/*  f040c30:	54810171 */ 	bnel	$a0,$at,.L0f0411f8
/*  f040c34:	24010006 */ 	addiu	$at,$zero,0x6
.L0f040c38:
/*  f040c38:	93b9026f */ 	lbu	$t9,0x26f($sp)
/*  f040c3c:	afa00250 */ 	sw	$zero,0x250($sp)
/*  f040c40:	3c017f1b */ 	lui	$at,%hi(var7f1a90cc)
/*  f040c44:	17200006 */ 	bnez	$t9,.L0f040c60
/*  f040c48:	c7a801d0 */ 	lwc1	$f8,0x1d0($sp)
/*  f040c4c:	c42490cc */ 	lwc1	$f4,%lo(var7f1a90cc)($at)
/*  f040c50:	4608203c */ 	c.lt.s	$f4,$f8
/*  f040c54:	00000000 */ 	nop
/*  f040c58:	45020164 */ 	bc1fl	.L0f0411ec
/*  f040c5c:	afa00268 */ 	sw	$zero,0x268($sp)
.L0f040c60:
/*  f040c60:	0fc2c3f4 */ 	jal	weaponFindById
/*  f040c64:	00000000 */ 	nop
/*  f040c68:	93ad0263 */ 	lbu	$t5,0x263($sp)
/*  f040c6c:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040c70:	24010018 */ 	addiu	$at,$zero,0x18
/*  f040c74:	000d7080 */ 	sll	$t6,$t5,0x2
/*  f040c78:	004e5821 */ 	addu	$t3,$v0,$t6
/*  f040c7c:	10810006 */ 	beq	$a0,$at,.L0f040c98
/*  f040c80:	8d630014 */ 	lw	$v1,0x14($t3)
/*  f040c84:	24010034 */ 	addiu	$at,$zero,0x34
/*  f040c88:	10810003 */ 	beq	$a0,$at,.L0f040c98
/*  f040c8c:	24010019 */ 	addiu	$at,$zero,0x19
/*  f040c90:	5481000e */ 	bnel	$a0,$at,.L0f040ccc
/*  f040c94:	2401001b */ 	addiu	$at,$zero,0x1b
.L0f040c98:
/*  f040c98:	8c6a0010 */ 	lw	$t2,0x10($v1)
/*  f040c9c:	24050053 */ 	addiu	$a1,$zero,0x53
/*  f040ca0:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040ca4:	000a7840 */ 	sll	$t7,$t2,0x1
/*  f040ca8:	05e30003 */ 	bgezl	$t7,.L0f040cb8
/*  f040cac:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040cb0:	24050054 */ 	addiu	$a1,$zero,0x54
/*  f040cb4:	8c640040 */ 	lw	$a0,0x40($v1)
.L0f040cb8:
/*  f040cb8:	0fc22e20 */ 	jal	func0f08b880
/*  f040cbc:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040cc0:	1000002e */ 	b	.L0f040d7c
/*  f040cc4:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040cc8:	2401001b */ 	addiu	$at,$zero,0x1b
.L0f040ccc:
/*  f040ccc:	1481000a */ 	bne	$a0,$at,.L0f040cf8
/*  f040cd0:	24050056 */ 	addiu	$a1,$zero,0x56
/*  f040cd4:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040cd8:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040cdc:	0fc22e20 */ 	jal	func0f08b880
/*  f040ce0:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040ce4:	10400025 */ 	beqz	$v0,.L0f040d7c
/*  f040ce8:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040cec:	93b80263 */ 	lbu	$t8,0x263($sp)
/*  f040cf0:	10000022 */ 	b	.L0f040d7c
/*  f040cf4:	a058005f */ 	sb	$t8,0x5f($v0)
.L0f040cf8:
/*  f040cf8:	24010017 */ 	addiu	$at,$zero,0x17
/*  f040cfc:	1481000a */ 	bne	$a0,$at,.L0f040d28
/*  f040d00:	24050055 */ 	addiu	$a1,$zero,0x55
/*  f040d04:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040d08:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040d0c:	0fc22e20 */ 	jal	func0f08b880
/*  f040d10:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040d14:	10400019 */ 	beqz	$v0,.L0f040d7c
/*  f040d18:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040d1c:	93ac0263 */ 	lbu	$t4,0x263($sp)
/*  f040d20:	10000016 */ 	b	.L0f040d7c
/*  f040d24:	a04c005f */ 	sb	$t4,0x5f($v0)
.L0f040d28:
/*  f040d28:	24010012 */ 	addiu	$at,$zero,0x12
/*  f040d2c:	1481000b */ 	bne	$a0,$at,.L0f040d5c
/*  f040d30:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x284)
/*  f040d34:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040d38:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040d3c:	24050055 */ 	addiu	$a1,$zero,0x55
/*  f040d40:	0fc22e20 */ 	jal	func0f08b880
/*  f040d44:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040d48:	1040000c */ 	beqz	$v0,.L0f040d7c
/*  f040d4c:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040d50:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f040d54:	10000009 */ 	b	.L0f040d7c
/*  f040d58:	a059005f */ 	sb	$t9,0x5f($v0)
.L0f040d5c:
/*  f040d5c:	8dada244 */ 	lw	$t5,%lo(g_Vars+0x284)($t5)
/*  f040d60:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040d64:	27a50260 */ 	addiu	$a1,$sp,0x260
/*  f040d68:	8dae00bc */ 	lw	$t6,0xbc($t5)
/*  f040d6c:	8dc60004 */ 	lw	$a2,0x4($t6)
/*  f040d70:	0fc22d96 */ 	jal	func0f08b658
/*  f040d74:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040d78:	afa201b8 */ 	sw	$v0,0x1b8($sp)
.L0f040d7c:
/*  f040d7c:	1040011b */ 	beqz	$v0,.L0f0411ec
/*  f040d80:	8fab00d4 */ 	lw	$t3,0xd4($sp)
/*  f040d84:	8d6a004c */ 	lw	$t2,0x4c($t3)
/*  f040d88:	3c017f1b */ 	lui	$at,%hi(var7f1a90d0)
/*  f040d8c:	c43090d0 */ 	lwc1	$f16,%lo(var7f1a90d0)($at)
/*  f040d90:	448a3000 */ 	mtc1	$t2,$f6
/*  f040d94:	3c014270 */ 	lui	$at,0x4270
/*  f040d98:	44812000 */ 	mtc1	$at,$f4
/*  f040d9c:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f040da0:	3c017f1b */ 	lui	$at,%hi(var7f1a90d4)
/*  f040da4:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f040da8:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040dac:	2405001e */ 	addiu	$a1,$zero,0x1e
/*  f040db0:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f040db4:	c43090d4 */ 	lwc1	$f16,%lo(var7f1a90d4)($at)
/*  f040db8:	46049203 */ 	div.s	$f8,$f18,$f4
/*  f040dbc:	e7a80168 */ 	swc1	$f8,0x168($sp)
/*  f040dc0:	8d6f0054 */ 	lw	$t7,0x54($t3)
/*  f040dc4:	448f3000 */ 	mtc1	$t7,$f6
/*  f040dc8:	00000000 */ 	nop
/*  f040dcc:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f040dd0:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f040dd4:	13000080 */ 	beqz	$t8,.L0f040fd8
/*  f040dd8:	e7b200cc */ 	swc1	$f18,0xcc($sp)
/*  f040ddc:	0fc1241a */ 	jal	chrIsTargetInFov
/*  f040de0:	00003025 */ 	or	$a2,$zero,$zero
/*  f040de4:	1040007c */ 	beqz	$v0,.L0f040fd8
/*  f040de8:	00000000 */ 	nop
/*  f040dec:	93a20263 */ 	lbu	$v0,0x263($sp)
/*  f040df0:	00001825 */ 	or	$v1,$zero,$zero
/*  f040df4:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040df8:	14400025 */ 	bnez	$v0,.L0f040e90
/*  f040dfc:	24010018 */ 	addiu	$at,$zero,0x18
/*  f040e00:	10810006 */ 	beq	$a0,$at,.L0f040e1c
/*  f040e04:	8fac025c */ 	lw	$t4,0x25c($sp)
/*  f040e08:	24010034 */ 	addiu	$at,$zero,0x34
/*  f040e0c:	10810003 */ 	beq	$a0,$at,.L0f040e1c
/*  f040e10:	24010019 */ 	addiu	$at,$zero,0x19
/*  f040e14:	5481001f */ 	bnel	$a0,$at,.L0f040e94
/*  f040e18:	93a40260 */ 	lbu	$a0,0x260($sp)
.L0f040e1c:
/*  f040e1c:	91820000 */ 	lbu	$v0,0x0($t4)
/*  f040e20:	24010003 */ 	addiu	$at,$zero,0x3
/*  f040e24:	8fb9025c */ 	lw	$t9,0x25c($sp)
/*  f040e28:	10410003 */ 	beq	$v0,$at,.L0f040e38
/*  f040e2c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040e30:	14410051 */ 	bne	$v0,$at,.L0f040f78
/*  f040e34:	00000000 */ 	nop
.L0f040e38:
/*  f040e38:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f040e3c:	c7aa0244 */ 	lwc1	$f10,0x244($sp)
/*  f040e40:	c7b20248 */ 	lwc1	$f18,0x248($sp)
/*  f040e44:	e7a400b8 */ 	swc1	$f4,0xb8($sp)
/*  f040e48:	8f2d0004 */ 	lw	$t5,0x4($t9)
/*  f040e4c:	460a2401 */ 	sub.s	$f16,$f4,$f10
/*  f040e50:	c7aa024c */ 	lwc1	$f10,0x24c($sp)
/*  f040e54:	c5a800b4 */ 	lwc1	$f8,0xb4($t5)
/*  f040e58:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f040e5c:	27a501e4 */ 	addiu	$a1,$sp,0x1e4
/*  f040e60:	e7a800bc */ 	swc1	$f8,0xbc($sp)
/*  f040e64:	c7260010 */ 	lwc1	$f6,0x10($t9)
/*  f040e68:	e7b001e0 */ 	swc1	$f16,0x1e0($sp)
/*  f040e6c:	46124101 */ 	sub.s	$f4,$f8,$f18
/*  f040e70:	27a601e8 */ 	addiu	$a2,$sp,0x1e8
/*  f040e74:	e7a600c0 */ 	swc1	$f6,0xc0($sp)
/*  f040e78:	460a3401 */ 	sub.s	$f16,$f6,$f10
/*  f040e7c:	e7a401e4 */ 	swc1	$f4,0x1e4($sp)
/*  f040e80:	0c0011e4 */ 	jal	guNormalize
/*  f040e84:	e7b001e8 */ 	swc1	$f16,0x1e8($sp)
/*  f040e88:	1000003b */ 	b	.L0f040f78
/*  f040e8c:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f040e90:
/*  f040e90:	93a40260 */ 	lbu	$a0,0x260($sp)
.L0f040e94:
/*  f040e94:	24050017 */ 	addiu	$a1,$zero,0x17
/*  f040e98:	24010012 */ 	addiu	$at,$zero,0x12
/*  f040e9c:	14a40003 */ 	bne	$a1,$a0,.L0f040eac
/*  f040ea0:	00000000 */ 	nop
/*  f040ea4:	50400004 */ 	beqzl	$v0,.L0f040eb8
/*  f040ea8:	8fae025c */ 	lw	$t6,0x25c($sp)
.L0f040eac:
/*  f040eac:	14810017 */ 	bne	$a0,$at,.L0f040f0c
/*  f040eb0:	00000000 */ 	nop
/*  f040eb4:	8fae025c */ 	lw	$t6,0x25c($sp)
.L0f040eb8:
/*  f040eb8:	24010003 */ 	addiu	$at,$zero,0x3
/*  f040ebc:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f040ec0:	91c20000 */ 	lbu	$v0,0x0($t6)
/*  f040ec4:	10410003 */ 	beq	$v0,$at,.L0f040ed4
/*  f040ec8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040ecc:	1441002a */ 	bne	$v0,$at,.L0f040f78
/*  f040ed0:	00000000 */ 	nop
.L0f040ed4:
/*  f040ed4:	c5480008 */ 	lwc1	$f8,0x8($t2)
/*  f040ed8:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f040edc:	8fa500cc */ 	lw	$a1,0xcc($sp)
/*  f040ee0:	e7a800b8 */ 	swc1	$f8,0xb8($sp)
/*  f040ee4:	8d4b0004 */ 	lw	$t3,0x4($t2)
/*  f040ee8:	27a600b8 */ 	addiu	$a2,$sp,0xb8
/*  f040eec:	27a701e0 */ 	addiu	$a3,$sp,0x1e0
/*  f040ef0:	c57200b4 */ 	lwc1	$f18,0xb4($t3)
/*  f040ef4:	e7b200bc */ 	swc1	$f18,0xbc($sp)
/*  f040ef8:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f040efc:	0fc100c7 */ 	jal	func0f04031c
/*  f040f00:	e7a400c0 */ 	swc1	$f4,0xc0($sp)
/*  f040f04:	1000001c */ 	b	.L0f040f78
/*  f040f08:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f040f0c:
/*  f040f0c:	14a40002 */ 	bne	$a1,$a0,.L0f040f18
/*  f040f10:	24010001 */ 	addiu	$at,$zero,0x1
/*  f040f14:	10410003 */ 	beq	$v0,$at,.L0f040f24
.L0f040f18:
/*  f040f18:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f040f1c:	14810016 */ 	bne	$a0,$at,.L0f040f78
/*  f040f20:	00000000 */ 	nop
.L0f040f24:
/*  f040f24:	8faf025c */ 	lw	$t7,0x25c($sp)
/*  f040f28:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040f2c:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f040f30:	c5e60008 */ 	lwc1	$f6,0x8($t7)
/*  f040f34:	27a600b8 */ 	addiu	$a2,$sp,0xb8
/*  f040f38:	27a701e0 */ 	addiu	$a3,$sp,0x1e0
/*  f040f3c:	e7a600b8 */ 	swc1	$f6,0xb8($sp)
/*  f040f40:	c5ea000c */ 	lwc1	$f10,0xc($t7)
/*  f040f44:	e7aa00bc */ 	swc1	$f10,0xbc($sp)
/*  f040f48:	c5f00010 */ 	lwc1	$f16,0x10($t7)
/*  f040f4c:	e7b000c0 */ 	swc1	$f16,0xc0($sp)
/*  f040f50:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f040f54:	17010005 */ 	bne	$t8,$at,.L0f040f6c
/*  f040f58:	3c0141c8 */ 	lui	$at,0x41c8
/*  f040f5c:	44814000 */ 	mtc1	$at,$f8
/*  f040f60:	00000000 */ 	nop
/*  f040f64:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f040f68:	e7b200bc */ 	swc1	$f18,0xbc($sp)
.L0f040f6c:
/*  f040f6c:	0fc100c7 */ 	jal	func0f04031c
/*  f040f70:	8fa500cc */ 	lw	$a1,0xcc($sp)
/*  f040f74:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f040f78:
/*  f040f78:	10600017 */ 	beqz	$v1,.L0f040fd8
/*  f040f7c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040f80:	0fc122a1 */ 	jal	chrGetAngleToPos
/*  f040f84:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f040f88:	e7a000b4 */ 	swc1	$f0,0xb4($sp)
/*  f040f8c:	0c0068f4 */ 	jal	cosf
/*  f040f90:	46000306 */ 	mov.s	$f12,$f0
/*  f040f94:	c7ac00b4 */ 	lwc1	$f12,0xb4($sp)
/*  f040f98:	0c0068f7 */ 	jal	sinf
/*  f040f9c:	e7a000b0 */ 	swc1	$f0,0xb0($sp)
/*  f040fa0:	c7ac01e8 */ 	lwc1	$f12,0x1e8($sp)
/*  f040fa4:	c7ae00b0 */ 	lwc1	$f14,0xb0($sp)
/*  f040fa8:	c7a201e0 */ 	lwc1	$f2,0x1e0($sp)
/*  f040fac:	460c0102 */ 	mul.s	$f4,$f0,$f12
/*  f040fb0:	00000000 */ 	nop
/*  f040fb4:	46027182 */ 	mul.s	$f6,$f14,$f2
/*  f040fb8:	00000000 */ 	nop
/*  f040fbc:	460c7282 */ 	mul.s	$f10,$f14,$f12
/*  f040fc0:	00000000 */ 	nop
/*  f040fc4:	46020202 */ 	mul.s	$f8,$f0,$f2
/*  f040fc8:	46062400 */ 	add.s	$f16,$f4,$f6
/*  f040fcc:	e7b001e0 */ 	swc1	$f16,0x1e0($sp)
/*  f040fd0:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f040fd4:	e7b201e8 */ 	swc1	$f18,0x1e8($sp)
.L0f040fd8:
/*  f040fd8:	0c00566c */ 	jal	mtx4LoadIdentity
/*  f040fdc:	27a40178 */ 	addiu	$a0,$sp,0x178
/*  f040fe0:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040fe4:	0c0058ba */ 	jal	mtx4LoadXRotation
/*  f040fe8:	27a5011c */ 	addiu	$a1,$sp,0x11c
/*  f040fec:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040ff0:	0c0058dd */ 	jal	mtx4LoadYRotation
/*  f040ff4:	27a500dc */ 	addiu	$a1,$sp,0xdc
/*  f040ff8:	27a400dc */ 	addiu	$a0,$sp,0xdc
/*  f040ffc:	0c0056f8 */ 	jal	mtx00015be0
/*  f041000:	27a5011c */ 	addiu	$a1,$sp,0x11c
/*  f041004:	c7ac0168 */ 	lwc1	$f12,0x168($sp)
/*  f041008:	c7a401e0 */ 	lwc1	$f4,0x1e0($sp)
/*  f04100c:	c7b001e4 */ 	lwc1	$f16,0x1e4($sp)
/*  f041010:	c7a801e8 */ 	lwc1	$f8,0x1e8($sp)
/*  f041014:	460c2182 */ 	mul.s	$f6,$f4,$f12
/*  f041018:	c7a200cc */ 	lwc1	$f2,0xcc($sp)
/*  f04101c:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4c)
/*  f041020:	460c8282 */ 	mul.s	$f10,$f16,$f12
/*  f041024:	c420a00c */ 	lwc1	$f0,%lo(g_Vars+0x4c)($at)
/*  f041028:	8fac00d4 */ 	lw	$t4,0xd4($sp)
/*  f04102c:	460c4482 */ 	mul.s	$f18,$f8,$f12
/*  f041030:	e7a6015c */ 	swc1	$f6,0x15c($sp)
/*  f041034:	8fa401b8 */ 	lw	$a0,0x1b8($sp)
/*  f041038:	46022102 */ 	mul.s	$f4,$f4,$f2
/*  f04103c:	e7aa0160 */ 	swc1	$f10,0x160($sp)
/*  f041040:	2401ffff */ 	addiu	$at,$zero,-1
/*  f041044:	46003182 */ 	mul.s	$f6,$f6,$f0
/*  f041048:	e7b20164 */ 	swc1	$f18,0x164($sp)
/*  f04104c:	27a50244 */ 	addiu	$a1,$sp,0x244
/*  f041050:	27a60234 */ 	addiu	$a2,$sp,0x234
/*  f041054:	27a7011c */ 	addiu	$a3,$sp,0x11c
/*  f041058:	27ae016c */ 	addiu	$t6,$sp,0x16c
/*  f04105c:	27ab0178 */ 	addiu	$t3,$sp,0x178
/*  f041060:	46062100 */ 	add.s	$f4,$f4,$f6
/*  f041064:	46028182 */ 	mul.s	$f6,$f16,$f2
/*  f041068:	e7a4016c */ 	swc1	$f4,0x16c($sp)
/*  f04106c:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f041070:	46043400 */ 	add.s	$f16,$f6,$f4
/*  f041074:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f041078:	00000000 */ 	nop
/*  f04107c:	46009182 */ 	mul.s	$f6,$f18,$f0
/*  f041080:	e7b00170 */ 	swc1	$f16,0x170($sp)
/*  f041084:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f041088:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f04108c:	8d8d0058 */ 	lw	$t5,0x58($t4)
/*  f041090:	a48d0062 */ 	sh	$t5,0x62($a0)
/*  f041094:	84820062 */ 	lh	$v0,0x62($a0)
/*  f041098:	10410002 */ 	beq	$v0,$at,.L0f0410a4
/*  f04109c:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f0410a0:	a4990062 */ 	sh	$t9,0x62($a0)
.L0f0410a4:
/*  f0410a4:	8faa0274 */ 	lw	$t2,0x274($sp)
/*  f0410a8:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0410ac:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f0410b0:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f0410b4:	0fc27af3 */ 	jal	bgun0f09ebcc
/*  f0410b8:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f0410bc:	8fa301b8 */ 	lw	$v1,0x1b8($sp)
/*  f0410c0:	8fac00d4 */ 	lw	$t4,0xd4($sp)
/*  f0410c4:	8c6f0040 */ 	lw	$t7,0x40($v1)
/*  f0410c8:	31f80080 */ 	andi	$t8,$t7,0x80
/*  f0410cc:	13000047 */ 	beqz	$t8,.L0f0411ec
/*  f0410d0:	00000000 */ 	nop
/*  f0410d4:	8d820010 */ 	lw	$v0,0x10($t4)
/*  f0410d8:	00026800 */ 	sll	$t5,$v0,0x0
/*  f0410dc:	05a10007 */ 	bgez	$t5,.L0f0410fc
/*  f0410e0:	00025900 */ 	sll	$t3,$v0,0x4
/*  f0410e4:	8c620048 */ 	lw	$v0,0x48($v1)
/*  f0410e8:	3c014000 */ 	lui	$at,0x4000
/*  f0410ec:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f0410f0:	03217025 */ 	or	$t6,$t9,$at
/*  f0410f4:	10000007 */ 	b	.L0f041114
/*  f0410f8:	ac4e0000 */ 	sw	$t6,0x0($v0)
.L0f0410fc:
/*  f0410fc:	05630006 */ 	bgezl	$t3,.L0f041118
/*  f041100:	c7b0015c */ 	lwc1	$f16,0x15c($sp)
/*  f041104:	8c620048 */ 	lw	$v0,0x48($v1)
/*  f041108:	8c4a0000 */ 	lw	$t2,0x0($v0)
/*  f04110c:	354f0010 */ 	ori	$t7,$t2,0x10
/*  f041110:	ac4f0000 */ 	sw	$t7,0x0($v0)
.L0f041114:
/*  f041114:	c7b0015c */ 	lwc1	$f16,0x15c($sp)
.L0f041118:
/*  f041118:	8c780048 */ 	lw	$t8,0x48($v1)
/*  f04111c:	241900f0 */ 	addiu	$t9,$zero,0xf0
/*  f041120:	3c017f1b */ 	lui	$at,%hi(var7f1a90d8)
/*  f041124:	e7100010 */ 	swc1	$f16,0x10($t8)
/*  f041128:	8c6c0048 */ 	lw	$t4,0x48($v1)
/*  f04112c:	c7a80160 */ 	lwc1	$f8,0x160($sp)
/*  f041130:	e5880014 */ 	swc1	$f8,0x14($t4)
/*  f041134:	8c6d0048 */ 	lw	$t5,0x48($v1)
/*  f041138:	c7b20164 */ 	lwc1	$f18,0x164($sp)
/*  f04113c:	e5b20018 */ 	swc1	$f18,0x18($t5)
/*  f041140:	8c6e0048 */ 	lw	$t6,0x48($v1)
/*  f041144:	add900b4 */ 	sw	$t9,0xb4($t6)
/*  f041148:	8fab00d4 */ 	lw	$t3,0xd4($sp)
/*  f04114c:	8c6a0048 */ 	lw	$t2,0x48($v1)
/*  f041150:	c56a005c */ 	lwc1	$f10,0x5c($t3)
/*  f041154:	e54a008c */ 	swc1	$f10,0x8c($t2)
/*  f041158:	8faf00d4 */ 	lw	$t7,0xd4($sp)
/*  f04115c:	c42490d8 */ 	lwc1	$f4,%lo(var7f1a90d8)($at)
/*  f041160:	8c780048 */ 	lw	$t8,0x48($v1)
/*  f041164:	c5e60050 */ 	lwc1	$f6,0x50($t7)
/*  f041168:	46043402 */ 	mul.s	$f16,$f6,$f4
/*  f04116c:	e7100098 */ 	swc1	$f16,0x98($t8)
/*  f041170:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f041174:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041178:	8fac01b8 */ 	lw	$t4,0x1b8($sp)
/*  f04117c:	3c01bf80 */ 	lui	$at,0xbf80
/*  f041180:	00002025 */ 	or	$a0,$zero,$zero
/*  f041184:	8d8d0048 */ 	lw	$t5,0x48($t4)
/*  f041188:	2407ffff */ 	addiu	$a3,$zero,-1
/*  f04118c:	240effff */ 	addiu	$t6,$zero,-1
/*  f041190:	ada200e8 */ 	sw	$v0,0xe8($t5)
/*  f041194:	8fb900d4 */ 	lw	$t9,0xd4($sp)
/*  f041198:	240bffff */ 	addiu	$t3,$zero,-1
/*  f04119c:	87260060 */ 	lh	$a2,0x60($t9)
/*  f0411a0:	18c00012 */ 	blez	$a2,.L0f0411ec
/*  f0411a4:	00000000 */ 	nop
/*  f0411a8:	8d850014 */ 	lw	$a1,0x14($t4)
/*  f0411ac:	44810000 */ 	mtc1	$at,$f0
/*  f0411b0:	afab002c */ 	sw	$t3,0x2c($sp)
/*  f0411b4:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f0411b8:	afa00020 */ 	sw	$zero,0x20($sp)
/*  f0411bc:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f0411c0:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f0411c4:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f0411c8:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0411cc:	e7a00024 */ 	swc1	$f0,0x24($sp)
/*  f0411d0:	e7a00030 */ 	swc1	$f0,0x30($sp)
/*  f0411d4:	e7a00034 */ 	swc1	$f0,0x34($sp)
/*  f0411d8:	0fc24e7e */ 	jal	func0f0939f8
/*  f0411dc:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*  f0411e0:	10000002 */ 	b	.L0f0411ec
/*  f0411e4:	00000000 */ 	nop
/*  f0411e8:	afa00268 */ 	sw	$zero,0x268($sp)
.L0f0411ec:
/*  f0411ec:	10000019 */ 	b	.L0f041254
/*  f0411f0:	a3a0026e */ 	sb	$zero,0x26e($sp)
/*  f0411f4:	24010006 */ 	addiu	$at,$zero,0x6
.L0f0411f8:
/*  f0411f8:	14810016 */ 	bne	$a0,$at,.L0f041254
/*  f0411fc:	93aa026f */ 	lbu	$t2,0x26f($sp)
/*  f041200:	11400014 */ 	beqz	$t2,.L0f041254
/*  f041204:	93af0263 */ 	lbu	$t7,0x263($sp)
/*  f041208:	24010001 */ 	addiu	$at,$zero,0x1
/*  f04120c:	15e10011 */ 	bne	$t7,$at,.L0f041254
/*  f041210:	8fad0278 */ 	lw	$t5,0x278($sp)
/*  f041214:	8fa2027c */ 	lw	$v0,0x27c($sp)
/*  f041218:	8db902d4 */ 	lw	$t9,0x2d4($t5)
/*  f04121c:	3c014120 */ 	lui	$at,0x4120
/*  f041220:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f041224:	03386021 */ 	addu	$t4,$t9,$t8
/*  f041228:	c58800e4 */ 	lwc1	$f8,0xe4($t4)
/*  f04122c:	44819000 */ 	mtc1	$at,$f18
/*  f041230:	44802000 */ 	mtc1	$zero,$f4
/*  f041234:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f041238:	4600518d */ 	trunc.w.s	$f6,$f10
/*  f04123c:	440b3000 */ 	mfc1	$t3,$f6
/*  f041240:	00000000 */ 	nop
/*  f041244:	a3ab0262 */ 	sb	$t3,0x262($sp)
/*  f041248:	8daa02d4 */ 	lw	$t2,0x2d4($t5)
/*  f04124c:	01587821 */ 	addu	$t7,$t2,$t8
/*  f041250:	e5e400e4 */ 	swc1	$f4,0xe4($t7)
.L0f041254:
/*  f041254:	93b8026e */ 	lbu	$t8,0x26e($sp)
/*  f041258:	93b9026f */ 	lbu	$t9,0x26f($sp)
/*  f04125c:	530001c0 */ 	beqzl	$t8,.L0f041960
/*  f041260:	8fae01c0 */ 	lw	$t6,0x1c0($sp)
/*  f041264:	172000d6 */ 	bnez	$t9,.L0f0415c0
/*  f041268:	8fac0258 */ 	lw	$t4,0x258($sp)
/*  f04126c:	318e0200 */ 	andi	$t6,$t4,0x200
/*  f041270:	11c0004c */ 	beqz	$t6,.L0f0413a4
/*  f041274:	8fab025c */ 	lw	$t3,0x25c($sp)
/*  f041278:	916d0000 */ 	lbu	$t5,0x0($t3)
/*  f04127c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f041280:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041284:	15a10047 */ 	bne	$t5,$at,.L0f0413a4
/*  f041288:	27a50244 */ 	addiu	$a1,$sp,0x244
/*  f04128c:	27a60234 */ 	addiu	$a2,$sp,0x234
/*  f041290:	0fc0e47b */ 	jal	chrCanSeeAttackTarget
/*  f041294:	00003825 */ 	or	$a3,$zero,$zero
/*  f041298:	10400042 */ 	beqz	$v0,.L0f0413a4
/*  f04129c:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f0412a0:	8d440004 */ 	lw	$a0,0x4($t2)
/*  f0412a4:	8fa50278 */ 	lw	$a1,0x278($sp)
/*  f0412a8:	0fc12aa3 */ 	jal	chrCompareTeams
/*  f0412ac:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f0412b0:	1040003c */ 	beqz	$v0,.L0f0413a4
/*  f0412b4:	3c014170 */ 	lui	$at,0x4170
/*  f0412b8:	44817000 */ 	mtc1	$at,$f14
/*  f0412bc:	8faf025c */ 	lw	$t7,0x25c($sp)
/*  f0412c0:	c7aa01e0 */ 	lwc1	$f10,0x1e0($sp)
/*  f0412c4:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f0412c8:	c5f00008 */ 	lwc1	$f16,0x8($t7)
/*  f0412cc:	460e5182 */ 	mul.s	$f6,$f10,$f14
/*  f0412d0:	c7aa01e4 */ 	lwc1	$f10,0x1e4($sp)
/*  f0412d4:	46088481 */ 	sub.s	$f18,$f16,$f8
/*  f0412d8:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f0412dc:	c5e4000c */ 	lwc1	$f4,0xc($t7)
/*  f0412e0:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0412e4:	27a501f8 */ 	addiu	$a1,$sp,0x1f8
/*  f0412e8:	46069001 */ 	sub.s	$f0,$f18,$f6
/*  f0412ec:	460e5482 */ 	mul.s	$f18,$f10,$f14
/*  f0412f0:	c7aa01e8 */ 	lwc1	$f10,0x1e8($sp)
/*  f0412f4:	46102201 */ 	sub.s	$f8,$f4,$f16
/*  f0412f8:	c7a4024c */ 	lwc1	$f4,0x24c($sp)
/*  f0412fc:	c5e60010 */ 	lwc1	$f6,0x10($t7)
/*  f041300:	27a601f4 */ 	addiu	$a2,$sp,0x1f4
/*  f041304:	46124081 */ 	sub.s	$f2,$f8,$f18
/*  f041308:	460e5202 */ 	mul.s	$f8,$f10,$f14
/*  f04130c:	c7b201d0 */ 	lwc1	$f18,0x1d0($sp)
/*  f041310:	46043401 */ 	sub.s	$f16,$f6,$f4
/*  f041314:	46000182 */ 	mul.s	$f6,$f0,$f0
/*  f041318:	00000000 */ 	nop
/*  f04131c:	46021102 */ 	mul.s	$f4,$f2,$f2
/*  f041320:	46088301 */ 	sub.s	$f12,$f16,$f8
/*  f041324:	460c6402 */ 	mul.s	$f16,$f12,$f12
/*  f041328:	46043280 */ 	add.s	$f10,$f6,$f4
/*  f04132c:	46105200 */ 	add.s	$f8,$f10,$f16
/*  f041330:	4612403e */ 	c.le.s	$f8,$f18
/*  f041334:	00000000 */ 	nop
/*  f041338:	4500002b */ 	bc1f	.L0f0413e8
/*  f04133c:	00000000 */ 	nop
/*  f041340:	0fc0feac */ 	jal	chrCalculateHit
/*  f041344:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f041348:	8fb801f4 */ 	lw	$t8,0x1f4($sp)
/*  f04134c:	8fac01f8 */ 	lw	$t4,0x1f8($sp)
/*  f041350:	8fae0278 */ 	lw	$t6,0x278($sp)
/*  f041354:	2f190001 */ 	sltiu	$t9,$t8,0x1
/*  f041358:	11800023 */ 	beqz	$t4,.L0f0413e8
/*  f04135c:	afb901f0 */ 	sw	$t9,0x1f0($sp)
/*  f041360:	81c30007 */ 	lb	$v1,0x7($t6)
/*  f041364:	24010008 */ 	addiu	$at,$zero,0x8
/*  f041368:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x8)
/*  f04136c:	1061000a */ 	beq	$v1,$at,.L0f041398
/*  f041370:	8fad0278 */ 	lw	$t5,0x278($sp)
/*  f041374:	2401000a */ 	addiu	$at,$zero,0xa
/*  f041378:	10610007 */ 	beq	$v1,$at,.L0f041398
/*  f04137c:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f041380:	10610005 */ 	beq	$v1,$at,.L0f041398
/*  f041384:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f041388:	10610003 */ 	beq	$v1,$at,.L0f041398
/*  f04138c:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f041390:	54610016 */ 	bnel	$v1,$at,.L0f0413ec
/*  f041394:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.L0f041398:
/*  f041398:	8d6b9fc8 */ 	lw	$t3,%lo(g_Vars+0x8)($t3)
/*  f04139c:	10000012 */ 	b	.L0f0413e8
/*  f0413a0:	adab0048 */ 	sw	$t3,0x48($t5)
.L0f0413a4:
/*  f0413a4:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f0413a8:	24010008 */ 	addiu	$at,$zero,0x8
/*  f0413ac:	3c0f800a */ 	lui	$t7,%hi(g_Vars+0x8)
/*  f0413b0:	81430007 */ 	lb	$v1,0x7($t2)
/*  f0413b4:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f0413b8:	10610009 */ 	beq	$v1,$at,.L0f0413e0
/*  f0413bc:	2401000a */ 	addiu	$at,$zero,0xa
/*  f0413c0:	10610007 */ 	beq	$v1,$at,.L0f0413e0
/*  f0413c4:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f0413c8:	10610005 */ 	beq	$v1,$at,.L0f0413e0
/*  f0413cc:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f0413d0:	10610003 */ 	beq	$v1,$at,.L0f0413e0
/*  f0413d4:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f0413d8:	54610004 */ 	bnel	$v1,$at,.L0f0413ec
/*  f0413dc:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.L0f0413e0:
/*  f0413e0:	8def9fc8 */ 	lw	$t7,%lo(g_Vars+0x8)($t7)
/*  f0413e4:	af0f0048 */ 	sw	$t7,0x48($t8)
.L0f0413e8:
/*  f0413e8:	8fb901f4 */ 	lw	$t9,0x1f4($sp)
.L0f0413ec:
/*  f0413ec:	8faa01cc */ 	lw	$t2,0x1cc($sp)
/*  f0413f0:	13200065 */ 	beqz	$t9,.L0f041588
/*  f0413f4:	00000000 */ 	nop
/*  f0413f8:	0fc2c74a */ 	jal	gsetGetDamage
/*  f0413fc:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041400:	8fab025c */ 	lw	$t3,0x25c($sp)
/*  f041404:	240cffff */ 	addiu	$t4,$zero,-1
/*  f041408:	240e00c8 */ 	addiu	$t6,$zero,0xc8
/*  f04140c:	e7a0009c */ 	swc1	$f0,0x9c($sp)
/*  f041410:	afa00098 */ 	sw	$zero,0x98($sp)
/*  f041414:	afa00094 */ 	sw	$zero,0x94($sp)
/*  f041418:	afac0090 */ 	sw	$t4,0x90($sp)
/*  f04141c:	afae008c */ 	sw	$t6,0x8c($sp)
/*  f041420:	8d6d0004 */ 	lw	$t5,0x4($t3)
/*  f041424:	afad0088 */ 	sw	$t5,0x88($sp)
/*  f041428:	c5660008 */ 	lwc1	$f6,0x8($t3)
/*  f04142c:	e7a60228 */ 	swc1	$f6,0x228($sp)
/*  f041430:	c564000c */ 	lwc1	$f4,0xc($t3)
/*  f041434:	e7a4022c */ 	swc1	$f4,0x22c($sp)
/*  f041438:	c56a0010 */ 	lwc1	$f10,0x10($t3)
/*  f04143c:	0c004b70 */ 	jal	random
/*  f041440:	e7aa0230 */ 	swc1	$f10,0x230($sp)
/*  f041444:	304a0001 */ 	andi	$t2,$v0,0x1
/*  f041448:	11400012 */ 	beqz	$t2,.L0f041494
/*  f04144c:	00000000 */ 	nop
/*  f041450:	0c004b70 */ 	jal	random
/*  f041454:	00000000 */ 	nop
/*  f041458:	2401000a */ 	addiu	$at,$zero,0xa
/*  f04145c:	0041001b */ 	divu	$zero,$v0,$at
/*  f041460:	00007810 */ 	mfhi	$t7
/*  f041464:	25f80002 */ 	addiu	$t8,$t7,0x2
/*  f041468:	44989000 */ 	mtc1	$t8,$f18
/*  f04146c:	c7b0022c */ 	lwc1	$f16,0x22c($sp)
/*  f041470:	07010005 */ 	bgez	$t8,.L0f041488
/*  f041474:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f041478:	3c014f80 */ 	lui	$at,0x4f80
/*  f04147c:	44813000 */ 	mtc1	$at,$f6
/*  f041480:	00000000 */ 	nop
/*  f041484:	46064200 */ 	add.s	$f8,$f8,$f6
.L0f041488:
/*  f041488:	46088100 */ 	add.s	$f4,$f16,$f8
/*  f04148c:	10000011 */ 	b	.L0f0414d4
/*  f041490:	e7a4022c */ 	swc1	$f4,0x22c($sp)
.L0f041494:
/*  f041494:	0c004b70 */ 	jal	random
/*  f041498:	00000000 */ 	nop
/*  f04149c:	2401000a */ 	addiu	$at,$zero,0xa
/*  f0414a0:	0041001b */ 	divu	$zero,$v0,$at
/*  f0414a4:	0000c810 */ 	mfhi	$t9
/*  f0414a8:	272c0002 */ 	addiu	$t4,$t9,0x2
/*  f0414ac:	448c9000 */ 	mtc1	$t4,$f18
/*  f0414b0:	c7aa022c */ 	lwc1	$f10,0x22c($sp)
/*  f0414b4:	05810005 */ 	bgez	$t4,.L0f0414cc
/*  f0414b8:	468091a0 */ 	cvt.s.w	$f6,$f18
/*  f0414bc:	3c014f80 */ 	lui	$at,0x4f80
/*  f0414c0:	44818000 */ 	mtc1	$at,$f16
/*  f0414c4:	00000000 */ 	nop
/*  f0414c8:	46103180 */ 	add.s	$f6,$f6,$f16
.L0f0414cc:
/*  f0414cc:	46065201 */ 	sub.s	$f8,$f10,$f6
/*  f0414d0:	e7a8022c */ 	swc1	$f8,0x22c($sp)
.L0f0414d4:
/*  f0414d4:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f0414d8:	8fa5025c */ 	lw	$a1,0x25c($sp)
/*  f0414dc:	0fc29f66 */ 	jal	bgunPlayPropHitSound
/*  f0414e0:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f0414e4:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f0414e8:	8c8e0020 */ 	lw	$t6,0x20($a0)
/*  f0414ec:	51c00012 */ 	beqzl	$t6,.L0f041538
/*  f0414f0:	8faf0278 */ 	lw	$t7,0x278($sp)
/*  f0414f4:	0fc0cfe8 */ 	jal	chrGetShield
/*  f0414f8:	00000000 */ 	nop
/*  f0414fc:	44802000 */ 	mtc1	$zero,$f4
/*  f041500:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f041504:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f041508:	4600203c */ 	c.lt.s	$f4,$f0
/*  f04150c:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f041510:	27a70098 */ 	addiu	$a3,$sp,0x98
/*  f041514:	27ad008c */ 	addiu	$t5,$sp,0x8c
/*  f041518:	45000006 */ 	bc1f	.L0f041534
/*  f04151c:	27ab0094 */ 	addiu	$t3,$sp,0x94
/*  f041520:	27aa0090 */ 	addiu	$t2,$sp,0x90
/*  f041524:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f041528:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f04152c:	0fc0ffcb */ 	jal	chrCalculateShieldHit
/*  f041530:	afab0014 */ 	sw	$t3,0x14($sp)
.L0f041534:
/*  f041534:	8faf0278 */ 	lw	$t7,0x278($sp)
.L0f041538:
/*  f041538:	8fac025c */ 	lw	$t4,0x25c($sp)
/*  f04153c:	8fae0098 */ 	lw	$t6,0x98($sp)
/*  f041540:	8df8001c */ 	lw	$t8,0x1c($t7)
/*  f041544:	8fad0094 */ 	lw	$t5,0x94($sp)
/*  f041548:	8fab0090 */ 	lw	$t3,0x90($sp)
/*  f04154c:	241900c8 */ 	addiu	$t9,$zero,0xc8
/*  f041550:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f041554:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f041558:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f04155c:	8fa5009c */ 	lw	$a1,0x9c($sp)
/*  f041560:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f041564:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f041568:	afac0018 */ 	sw	$t4,0x18($sp)
/*  f04156c:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f041570:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f041574:	afad0020 */ 	sw	$t5,0x20($sp)
/*  f041578:	0fc0d077 */ 	jal	func0f0341dc
/*  f04157c:	afab0024 */ 	sw	$t3,0x24($sp)
/*  f041580:	10000010 */ 	b	.L0f0415c4
/*  f041584:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
.L0f041588:
/*  f041588:	11400006 */ 	beqz	$t2,.L0f0415a4
/*  f04158c:	c7b201d0 */ 	lwc1	$f18,0x1d0($sp)
/*  f041590:	91420000 */ 	lbu	$v0,0x0($t2)
/*  f041594:	24010003 */ 	addiu	$at,$zero,0x3
/*  f041598:	10410009 */ 	beq	$v0,$at,.L0f0415c0
/*  f04159c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0415a0:	10410007 */ 	beq	$v0,$at,.L0f0415c0
.L0f0415a4:
/*  f0415a4:	3c017f1b */ 	lui	$at,%hi(var7f1a90dc)
/*  f0415a8:	c43090dc */ 	lwc1	$f16,%lo(var7f1a90dc)($at)
/*  f0415ac:	4610903c */ 	c.lt.s	$f18,$f16
/*  f0415b0:	00000000 */ 	nop
/*  f0415b4:	45020003 */ 	bc1fl	.L0f0415c4
/*  f0415b8:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
/*  f0415bc:	afa001f0 */ 	sw	$zero,0x1f0($sp)
.L0f0415c0:
/*  f0415c0:	8faf01f0 */ 	lw	$t7,0x1f0($sp)
.L0f0415c4:
/*  f0415c4:	8fb801cc */ 	lw	$t8,0x1cc($sp)
/*  f0415c8:	51e000e5 */ 	beqzl	$t7,.L0f041960
/*  f0415cc:	8fae01c0 */ 	lw	$t6,0x1c0($sp)
/*  f0415d0:	130000a2 */ 	beqz	$t8,.L0f04185c
/*  f0415d4:	8fae0224 */ 	lw	$t6,0x224($sp)
/*  f0415d8:	93020000 */ 	lbu	$v0,0x0($t8)
/*  f0415dc:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0415e0:	93b9026f */ 	lbu	$t9,0x26f($sp)
/*  f0415e4:	10410003 */ 	beq	$v0,$at,.L0f0415f4
/*  f0415e8:	24010003 */ 	addiu	$at,$zero,0x3
/*  f0415ec:	54410053 */ 	bnel	$v0,$at,.L0f04173c
/*  f0415f0:	24010001 */ 	addiu	$at,$zero,0x1
.L0f0415f4:
/*  f0415f4:	1720000c */ 	bnez	$t9,.L0f041628
/*  f0415f8:	8fac01bc */ 	lw	$t4,0x1bc($sp)
/*  f0415fc:	1580000a */ 	bnez	$t4,.L0f041628
/*  f041600:	8fae0278 */ 	lw	$t6,0x278($sp)
/*  f041604:	8dcd0018 */ 	lw	$t5,0x18($t6)
/*  f041608:	8faa01cc */ 	lw	$t2,0x1cc($sp)
/*  f04160c:	01c02825 */ 	or	$a1,$t6,$zero
/*  f041610:	31ab0040 */ 	andi	$t3,$t5,0x40
/*  f041614:	11600045 */ 	beqz	$t3,.L0f04172c
/*  f041618:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f04161c:	0fc12aa3 */ 	jal	chrCompareTeams
/*  f041620:	8d440004 */ 	lw	$a0,0x4($t2)
/*  f041624:	10400041 */ 	beqz	$v0,.L0f04172c
.L0f041628:
/*  f041628:	240fffff */ 	addiu	$t7,$zero,-1
/*  f04162c:	241800c8 */ 	addiu	$t8,$zero,0xc8
/*  f041630:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f041634:	afa00080 */ 	sw	$zero,0x80($sp)
/*  f041638:	afaf007c */ 	sw	$t7,0x7c($sp)
/*  f04163c:	afb80078 */ 	sw	$t8,0x78($sp)
/*  f041640:	0fc2c74a */ 	jal	gsetGetDamage
/*  f041644:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041648:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f04164c:	e7a00074 */ 	swc1	$f0,0x74($sp)
/*  f041650:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041654:	8cac0004 */ 	lw	$t4,0x4($a1)
/*  f041658:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f04165c:	0fc29f66 */ 	jal	bgunPlayPropHitSound
/*  f041660:	afac0070 */ 	sw	$t4,0x70($sp)
/*  f041664:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f041668:	8c8d0020 */ 	lw	$t5,0x20($a0)
/*  f04166c:	51a00012 */ 	beqzl	$t5,.L0f0416b8
/*  f041670:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f041674:	0fc0cfe8 */ 	jal	chrGetShield
/*  f041678:	00000000 */ 	nop
/*  f04167c:	44805000 */ 	mtc1	$zero,$f10
/*  f041680:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f041684:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f041688:	4600503c */ 	c.lt.s	$f10,$f0
/*  f04168c:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f041690:	27a70084 */ 	addiu	$a3,$sp,0x84
/*  f041694:	27ab0078 */ 	addiu	$t3,$sp,0x78
/*  f041698:	45000006 */ 	bc1f	.L0f0416b4
/*  f04169c:	27aa0080 */ 	addiu	$t2,$sp,0x80
/*  f0416a0:	27ae007c */ 	addiu	$t6,$sp,0x7c
/*  f0416a4:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f0416a8:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0416ac:	0fc0ffcb */ 	jal	chrCalculateShieldHit
/*  f0416b0:	afaa0014 */ 	sw	$t2,0x14($sp)
.L0f0416b4:
/*  f0416b4:	8fb80278 */ 	lw	$t8,0x278($sp)
.L0f0416b8:
/*  f0416b8:	27af01e0 */ 	addiu	$t7,$sp,0x1e0
/*  f0416bc:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f0416c0:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0416c4:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f0416c8:	8fa60078 */ 	lw	$a2,0x78($sp)
/*  f0416cc:	27a70228 */ 	addiu	$a3,$sp,0x228
/*  f0416d0:	0fc097a9 */ 	jal	chrEmitSparks
/*  f0416d4:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0416d8:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f0416dc:	8fab01cc */ 	lw	$t3,0x1cc($sp)
/*  f0416e0:	8faa0084 */ 	lw	$t2,0x84($sp)
/*  f0416e4:	8d99001c */ 	lw	$t9,0x1c($t4)
/*  f0416e8:	8fae0080 */ 	lw	$t6,0x80($sp)
/*  f0416ec:	8faf007c */ 	lw	$t7,0x7c($sp)
/*  f0416f0:	240d00c8 */ 	addiu	$t5,$zero,0xc8
/*  f0416f4:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f0416f8:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f0416fc:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f041700:	8fa50074 */ 	lw	$a1,0x74($sp)
/*  f041704:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f041708:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f04170c:	afab0018 */ 	sw	$t3,0x18($sp)
/*  f041710:	afaa001c */ 	sw	$t2,0x1c($sp)
/*  f041714:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f041718:	afae0020 */ 	sw	$t6,0x20($sp)
/*  f04171c:	0fc0d077 */ 	jal	func0f0341dc
/*  f041720:	afaf0024 */ 	sw	$t7,0x24($sp)
/*  f041724:	1000006f */ 	b	.L0f0418e4
/*  f041728:	93ac0260 */ 	lbu	$t4,0x260($sp)
.L0f04172c:
/*  f04172c:	afa00250 */ 	sw	$zero,0x250($sp)
/*  f041730:	1000006b */ 	b	.L0f0418e0
/*  f041734:	afa00268 */ 	sw	$zero,0x268($sp)
/*  f041738:	24010001 */ 	addiu	$at,$zero,0x1
.L0f04173c:
/*  f04173c:	10410005 */ 	beq	$v0,$at,.L0f041754
/*  f041740:	8fb801cc */ 	lw	$t8,0x1cc($sp)
/*  f041744:	24010004 */ 	addiu	$at,$zero,0x4
/*  f041748:	10410002 */ 	beq	$v0,$at,.L0f041754
/*  f04174c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f041750:	14410063 */ 	bne	$v0,$at,.L0f0418e0
.L0f041754:
/*  f041754:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x314)
/*  f041758:	8dada2d4 */ 	lw	$t5,%lo(g_Vars+0x314)($t5)
/*  f04175c:	8f0c0004 */ 	lw	$t4,0x4($t8)
/*  f041760:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f041764:	afb90068 */ 	sw	$t9,0x68($sp)
/*  f041768:	11a00004 */ 	beqz	$t5,.L0f04177c
/*  f04176c:	afac006c */ 	sw	$t4,0x6c($sp)
/*  f041770:	0fc633fe */ 	jal	mpPlayerGetIndex
/*  f041774:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041778:	afa20068 */ 	sw	$v0,0x68($sp)
.L0f04177c:
/*  f04177c:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041780:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f041784:	0fc29f66 */ 	jal	bgunPlayPropHitSound
/*  f041788:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f04178c:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041790:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f041794:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041798:	0fc1979d */ 	jal	func0f065e74
/*  f04179c:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f0417a0:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f0417a4:	afab0210 */ 	sw	$t3,0x210($sp)
/*  f0417a8:	0fc4f92a */ 	jal	chrIsUsingPaintball
/*  f0417ac:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0417b0:	1040000b */ 	beqz	$v0,.L0f0417e0
/*  f0417b4:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f0417b8:	240a0019 */ 	addiu	$t2,$zero,0x19
/*  f0417bc:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f0417c0:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f0417c4:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f0417c8:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0417cc:	00003825 */ 	or	$a3,$zero,$zero
/*  f0417d0:	0fc4be7c */ 	jal	sparksCreate
/*  f0417d4:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0417d8:	10000007 */ 	b	.L0f0417f8
/*  f0417dc:	00000000 */ 	nop
.L0f0417e0:
/*  f0417e0:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f0417e4:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0417e8:	00003825 */ 	or	$a3,$zero,$zero
/*  f0417ec:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0417f0:	0fc4be7c */ 	jal	sparksCreate
/*  f0417f4:	afa00014 */ 	sw	$zero,0x14($sp)
.L0f0417f8:
/*  f0417f8:	3c0e800a */ 	lui	$t6,%hi(g_MissionConfig+0x3)
/*  f0417fc:	81cfdfeb */ 	lb	$t7,%lo(g_MissionConfig+0x3)($t6)
/*  f041800:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f041804:	05e1000a */ 	bgez	$t7,.L0f041830
/*  f041808:	00000000 */ 	nop
/*  f04180c:	930c0125 */ 	lbu	$t4,0x125($t8)
/*  f041810:	24010010 */ 	addiu	$at,$zero,0x10
/*  f041814:	8fb9006c */ 	lw	$t9,0x6c($sp)
/*  f041818:	15810005 */ 	bne	$t4,$at,.L0f041830
/*  f04181c:	00000000 */ 	nop
/*  f041820:	8f2d000c */ 	lw	$t5,0xc($t9)
/*  f041824:	31ab0001 */ 	andi	$t3,$t5,0x1
/*  f041828:	5560002e */ 	bnezl	$t3,.L0f0418e4
/*  f04182c:	93ac0260 */ 	lbu	$t4,0x260($sp)
.L0f041830:
/*  f041830:	0fc2c74a */ 	jal	gsetGetDamage
/*  f041834:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041838:	8faa0068 */ 	lw	$t2,0x68($sp)
/*  f04183c:	44050000 */ 	mfc1	$a1,$f0
/*  f041840:	8fa4006c */ 	lw	$a0,0x6c($sp)
/*  f041844:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041848:	93a70260 */ 	lbu	$a3,0x260($sp)
/*  f04184c:	0fc2149c */ 	jal	objTakeGunfire
/*  f041850:	afaa0010 */ 	sw	$t2,0x10($sp)
/*  f041854:	10000023 */ 	b	.L0f0418e4
/*  f041858:	93ac0260 */ 	lbu	$t4,0x260($sp)
.L0f04185c:
/*  f04185c:	11c00020 */ 	beqz	$t6,.L0f0418e0
/*  f041860:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041864:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f041868:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f04186c:	0fc1979d */ 	jal	func0f065e74
/*  f041870:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041874:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f041878:	afaf0210 */ 	sw	$t7,0x210($sp)
/*  f04187c:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041880:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f041884:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f041888:	0fc2a132 */ 	jal	bgunPlayBgHitSound
/*  f04188c:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041890:	0fc4f92a */ 	jal	chrIsUsingPaintball
/*  f041894:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041898:	1040000b */ 	beqz	$v0,.L0f0418c8
/*  f04189c:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f0418a0:	24180019 */ 	addiu	$t8,$zero,0x19
/*  f0418a4:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0418a8:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f0418ac:	00002825 */ 	or	$a1,$zero,$zero
/*  f0418b0:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0418b4:	00003825 */ 	or	$a3,$zero,$zero
/*  f0418b8:	0fc4be7c */ 	jal	sparksCreate
/*  f0418bc:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0418c0:	10000008 */ 	b	.L0f0418e4
/*  f0418c4:	93ac0260 */ 	lbu	$t4,0x260($sp)
.L0f0418c8:
/*  f0418c8:	00002825 */ 	or	$a1,$zero,$zero
/*  f0418cc:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0418d0:	00003825 */ 	or	$a3,$zero,$zero
/*  f0418d4:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0418d8:	0fc4be7c */ 	jal	sparksCreate
/*  f0418dc:	afa00014 */ 	sw	$zero,0x14($sp)
.L0f0418e0:
/*  f0418e0:	93ac0260 */ 	lbu	$t4,0x260($sp)
.L0f0418e4:
/*  f0418e4:	24010007 */ 	addiu	$at,$zero,0x7
/*  f0418e8:	93b90263 */ 	lbu	$t9,0x263($sp)
/*  f0418ec:	1581001b */ 	bne	$t4,$at,.L0f04195c
/*  f0418f0:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0418f4:	17210019 */ 	bne	$t9,$at,.L0f04195c
/*  f0418f8:	8fad0278 */ 	lw	$t5,0x278($sp)
/*  f0418fc:	8dab02d4 */ 	lw	$t3,0x2d4($t5)
/*  f041900:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x28c)
/*  f041904:	11600005 */ 	beqz	$t3,.L0f04191c
/*  f041908:	00000000 */ 	nop
/*  f04190c:	0fc633fe */ 	jal	mpPlayerGetIndex
/*  f041910:	01a02025 */ 	or	$a0,$t5,$zero
/*  f041914:	10000002 */ 	b	.L0f041920
/*  f041918:	00401825 */ 	or	$v1,$v0,$zero
.L0f04191c:
/*  f04191c:	8c63a24c */ 	lw	$v1,%lo(g_Vars+0x28c)($v1)
.L0f041920:
/*  f041920:	8faa0210 */ 	lw	$t2,0x210($sp)
/*  f041924:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f041928:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f04192c:	15400005 */ 	bnez	$t2,.L0f041944
/*  f041930:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041934:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041938:	0fc1979d */ 	jal	func0f065e74
/*  f04193c:	afa30064 */ 	sw	$v1,0x64($sp)
/*  f041940:	8fa30064 */ 	lw	$v1,0x64($sp)
.L0f041944:
/*  f041944:	00002025 */ 	or	$a0,$zero,$zero
/*  f041948:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f04194c:	27a60214 */ 	addiu	$a2,$sp,0x214
/*  f041950:	24070016 */ 	addiu	$a3,$zero,0x16
/*  f041954:	0fc4a640 */ 	jal	explosionCreateSimple
/*  f041958:	afa30010 */ 	sw	$v1,0x10($sp)
.L0f04195c:
/*  f04195c:	8fae01c0 */ 	lw	$t6,0x1c0($sp)
.L0f041960:
/*  f041960:	8fa4025c */ 	lw	$a0,0x25c($sp)
/*  f041964:	51c00004 */ 	beqzl	$t6,.L0f041978
/*  f041968:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f04196c:	0fc1905e */ 	jal	propSetPerimEnabled
/*  f041970:	00002825 */ 	or	$a1,$zero,$zero
/*  f041974:	8fa80268 */ 	lw	$t0,0x268($sp)
.L0f041978:
/*  f041978:	8fb80250 */ 	lw	$t8,0x250($sp)
/*  f04197c:	93ac0260 */ 	lbu	$t4,0x260($sp)
/*  f041980:	0008782b */ 	sltu	$t7,$zero,$t0
/*  f041984:	1300000e */ 	beqz	$t8,.L0f0419c0
/*  f041988:	01e04025 */ 	or	$t0,$t7,$zero
/*  f04198c:	2599fffe */ 	addiu	$t9,$t4,-2
/*  f041990:	2f21002a */ 	sltiu	$at,$t9,0x2a
/*  f041994:	10200009 */ 	beqz	$at,.L0f0419bc
/*  f041998:	0019c880 */ 	sll	$t9,$t9,0x2
/*  f04199c:	3c017f1b */ 	lui	$at,%hi(var7f1a90e0)
/*  f0419a0:	00390821 */ 	addu	$at,$at,$t9
/*  f0419a4:	8c3990e0 */ 	lw	$t9,%lo(var7f1a90e0)($at)
/*  f0419a8:	03200008 */ 	jr	$t9
/*  f0419ac:	00000000 */ 	nop
/*  f0419b0:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f0419b4:	10000002 */ 	b	.L0f0419c0
/*  f0419b8:	afab0250 */ 	sw	$t3,0x250($sp)
.L0f0419bc:
/*  f0419bc:	afa00250 */ 	sw	$zero,0x250($sp)
.L0f0419c0:
/*  f0419c0:	11000004 */ 	beqz	$t0,.L0f0419d4
/*  f0419c4:	01003825 */ 	or	$a3,$t0,$zero
/*  f0419c8:	8fa70250 */ 	lw	$a3,0x250($sp)
/*  f0419cc:	0007682b */ 	sltu	$t5,$zero,$a3
/*  f0419d0:	01a03825 */ 	or	$a3,$t5,$zero
.L0f0419d4:
/*  f0419d4:	27aa0244 */ 	addiu	$t2,$sp,0x244
/*  f0419d8:	27ae0228 */ 	addiu	$t6,$sp,0x228
/*  f0419dc:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f0419e0:	afaa0010 */ 	sw	$t2,0x10($sp)
/*  f0419e4:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0419e8:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f0419ec:	8fa60268 */ 	lw	$a2,0x268($sp)
/*  f0419f0:	0fc0f8a7 */ 	jal	chrCreateFireslot
/*  f0419f4:	afa80054 */ 	sw	$t0,0x54($sp)
/*  f0419f8:	93af026f */ 	lbu	$t7,0x26f($sp)
/*  f0419fc:	8fa80054 */ 	lw	$t0,0x54($sp)
/*  f041a00:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041a04:	11e00015 */ 	beqz	$t7,.L0f041a5c
/*  f041a08:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f041a0c:	1100000a */ 	beqz	$t0,.L0f041a38
/*  f041a10:	01003025 */ 	or	$a2,$t0,$zero
/*  f041a14:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f041a18:	8fb9027c */ 	lw	$t9,0x27c($sp)
/*  f041a1c:	8f0c02d4 */ 	lw	$t4,0x2d4($t8)
/*  f041a20:	00195880 */ 	sll	$t3,$t9,0x2
/*  f041a24:	018b1021 */ 	addu	$v0,$t4,$t3
/*  f041a28:	8c430024 */ 	lw	$v1,0x24($v0)
/*  f041a2c:	18600002 */ 	blez	$v1,.L0f041a38
/*  f041a30:	246dffff */ 	addiu	$t5,$v1,-1
/*  f041a34:	ac4d0024 */ 	sw	$t5,0x24($v0)
.L0f041a38:
/*  f041a38:	11000004 */ 	beqz	$t0,.L0f041a4c
/*  f041a3c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041a40:	93a6026e */ 	lbu	$a2,0x26e($sp)
/*  f041a44:	0006502b */ 	sltu	$t2,$zero,$a2
/*  f041a48:	01403025 */ 	or	$a2,$t2,$zero
.L0f041a4c:
/*  f041a4c:	0fc0fe12 */ 	jal	chrSetFiring
/*  f041a50:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f041a54:	10000004 */ 	b	.L0f041a68
/*  f041a58:	8fbf0044 */ 	lw	$ra,0x44($sp)
.L0f041a5c:
/*  f041a5c:	0fc0fe12 */ 	jal	chrSetFiring
/*  f041a60:	8fa60268 */ 	lw	$a2,0x268($sp)
/*  f041a64:	8fbf0044 */ 	lw	$ra,0x44($sp)
.L0f041a68:
/*  f041a68:	27bd0278 */ 	addiu	$sp,$sp,0x278
/*  f041a6c:	03e00008 */ 	jr	$ra
/*  f041a70:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0f0404d4
.late_rodata
glabel var7f1a90c8
.word 0x3d638e39
glabel var7f1a90cc
.word 0x481c4000
glabel var7f1a90d0
.word 0x3fd55555
glabel var7f1a90d4
.word 0x3fd55555
glabel var7f1a90d8
.word 0x3fd55555
glabel var7f1a90dc
.word 0x461c4000
glabel var7f1a90e0
.word func0f0404d4+0x14c4
glabel var7f1a90e4
.word func0f0404d4+0x14c4
glabel var7f1a90e8
.word func0f0404d4+0x14c4
glabel var7f1a90ec
.word func0f0404d4+0x14c4
glabel var7f1a90f0
.word func0f0404d4+0x14c4
glabel var7f1a90f4
.word func0f0404d4+0x14c4
glabel var7f1a90f8
.word func0f0404d4+0x14c4
glabel var7f1a90fc
.word func0f0404d4+0x14c4
glabel var7f1a9100
.word func0f0404d4+0x14c4
glabel var7f1a9104
.word func0f0404d4+0x14c4
glabel var7f1a9108
.word func0f0404d4+0x14c4
glabel var7f1a910c
.word func0f0404d4+0x14c4
glabel var7f1a9110
.word func0f0404d4+0x14c4
glabel var7f1a9114
.word func0f0404d4+0x14c4
glabel var7f1a9118
.word func0f0404d4+0x14c4
glabel var7f1a911c
.word func0f0404d4+0x14c4
glabel var7f1a9120
.word func0f0404d4+0x14c4
glabel var7f1a9124
.word func0f0404d4+0x14d0
glabel var7f1a9128
.word func0f0404d4+0x14c4
glabel var7f1a912c
.word func0f0404d4+0x14c4
glabel var7f1a9130
.word func0f0404d4+0x14c4
glabel var7f1a9134
.word func0f0404d4+0x14d0
glabel var7f1a9138
.word func0f0404d4+0x14d0
glabel var7f1a913c
.word func0f0404d4+0x14d0
glabel var7f1a9140
.word func0f0404d4+0x14d0
glabel var7f1a9144
.word func0f0404d4+0x14d0
glabel var7f1a9148
.word func0f0404d4+0x14c4
glabel var7f1a914c
.word func0f0404d4+0x14c4
glabel var7f1a9150
.word func0f0404d4+0x14d0
glabel var7f1a9154
.word func0f0404d4+0x14d0
glabel var7f1a9158
.word func0f0404d4+0x14d0
glabel var7f1a915c
.word func0f0404d4+0x14d0
glabel var7f1a9160
.word func0f0404d4+0x14d0
glabel var7f1a9164
.word func0f0404d4+0x14d0
glabel var7f1a9168
.word func0f0404d4+0x14c4
glabel var7f1a916c
.word func0f0404d4+0x14c4
glabel var7f1a9170
.word func0f0404d4+0x14c4
glabel var7f1a9174
.word func0f0404d4+0x14c4
glabel var7f1a9178
.word func0f0404d4+0x14c4
glabel var7f1a917c
.word func0f0404d4+0x14c4
glabel var7f1a9180
.word func0f0404d4+0x14c4
glabel var7f1a9184
.word func0f0404d4+0x14c4
.text
/*  f03fcb4:	27bdfd88 */ 	addiu	$sp,$sp,-632
/*  f03fcb8:	afbf0044 */ 	sw	$ra,0x44($sp)
/*  f03fcbc:	afa5027c */ 	sw	$a1,0x27c($sp)
/*  f03fcc0:	8c8e001c */ 	lw	$t6,0x1c($a0)
/*  f03fcc4:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f03fcc8:	a3af026e */ 	sb	$t7,0x26e($sp)
/*  f03fccc:	afae0274 */ 	sw	$t6,0x274($sp)
/*  f03fcd0:	8c9802d4 */ 	lw	$t8,0x2d4($a0)
/*  f03fcd4:	00001025 */ 	or	$v0,$zero,$zero
/*  f03fcd8:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f03fcdc:	53000003 */ 	beqzl	$t8,.NB0f03fcec
/*  f03fce0:	a3a2026f */ 	sb	$v0,0x26f($sp)
/*  f03fce4:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f03fce8:	a3a2026f */ 	sb	$v0,0x26f($sp)
.NB0f03fcec:
/*  f03fcec:	0fc0a074 */ 	jal	chrGetHeldProp
/*  f03fcf0:	afa40278 */ 	sw	$a0,0x278($sp)
/*  f03fcf4:	5040054e */ 	beqzl	$v0,.NB0f041230
/*  f03fcf8:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*  f03fcfc:	afa00268 */ 	sw	$zero,0x268($sp)
/*  f03fd00:	8c590004 */ 	lw	$t9,0x4($v0)
/*  f03fd04:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f03fd08:	0fc0a08c */ 	jal	chrGetTargetProp
/*  f03fd0c:	afb90264 */ 	sw	$t9,0x264($sp)
/*  f03fd10:	8fab0264 */ 	lw	$t3,0x264($sp)
/*  f03fd14:	afa2025c */ 	sw	$v0,0x25c($sp)
/*  f03fd18:	8fa70278 */ 	lw	$a3,0x278($sp)
/*  f03fd1c:	8961005c */ 	lwl	$at,0x5c($t3)
/*  f03fd20:	9961005f */ 	lwr	$at,0x5f($t3)
/*  f03fd24:	27aa0260 */ 	addiu	$t2,$sp,0x260
/*  f03fd28:	24080200 */ 	addiu	$t0,$zero,0x200
/*  f03fd2c:	ad410000 */ 	sw	$at,0x0($t2)
/*  f03fd30:	80e30007 */ 	lb	$v1,0x7($a3)
/*  f03fd34:	24010008 */ 	addiu	$at,$zero,0x8
/*  f03fd38:	10610007 */ 	beq	$v1,$at,.NB0f03fd58
/*  f03fd3c:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f03fd40:	10610005 */ 	beq	$v1,$at,.NB0f03fd58
/*  f03fd44:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f03fd48:	10610003 */ 	beq	$v1,$at,.NB0f03fd58
/*  f03fd4c:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f03fd50:	54610003 */ 	bnel	$v1,$at,.NB0f03fd60
/*  f03fd54:	afa00250 */ 	sw	$zero,0x250($sp)
.NB0f03fd58:
/*  f03fd58:	8ce8004c */ 	lw	$t0,0x4c($a3)
/*  f03fd5c:	afa00250 */ 	sw	$zero,0x250($sp)
.NB0f03fd60:
/*  f03fd60:	afa00224 */ 	sw	$zero,0x224($sp)
/*  f03fd64:	afa00210 */ 	sw	$zero,0x210($sp)
/*  f03fd68:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f03fd6c:	93a50263 */ 	lbu	$a1,0x263($sp)
/*  f03fd70:	afa00254 */ 	sw	$zero,0x254($sp)
/*  f03fd74:	0fc2bf12 */ 	jal	weaponGetNumTicksPerShot
/*  f03fd78:	afa80258 */ 	sw	$t0,0x258($sp)
/*  f03fd7c:	8fa60254 */ 	lw	$a2,0x254($sp)
/*  f03fd80:	1c400005 */ 	bgtz	$v0,.NB0f03fd98
/*  f03fd84:	00402025 */ 	or	$a0,$v0,$zero
/*  f03fd88:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f03fd8c:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f03fd90:	10000055 */ 	beqz	$zero,.NB0f03fee8
/*  f03fd94:	afaf0250 */ 	sw	$t7,0x250($sp)
.NB0f03fd98:
/*  f03fd98:	8fb80278 */ 	lw	$t8,0x278($sp)
/*  f03fd9c:	8f0302d4 */ 	lw	$v1,0x2d4($t8)
/*  f03fda0:	5060001d */ 	beqzl	$v1,.NB0f03fe18
/*  f03fda4:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f03fda8:	8c790020 */ 	lw	$t9,0x20($v1)
/*  f03fdac:	24010014 */ 	addiu	$at,$zero,0x14
/*  f03fdb0:	57210019 */ 	bnel	$t9,$at,.NB0f03fe18
/*  f03fdb4:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f03fdb8:	8c6d004c */ 	lw	$t5,0x4c($v1)
/*  f03fdbc:	8fab027c */ 	lw	$t3,0x27c($sp)
/*  f03fdc0:	000d5080 */ 	sll	$t2,$t5,0x2
/*  f03fdc4:	05400013 */ 	bltz	$t2,.NB0f03fe14
/*  f03fdc8:	000b7040 */ 	sll	$t6,$t3,0x1
/*  f03fdcc:	006e7821 */ 	addu	$t7,$v1,$t6
/*  f03fdd0:	85f800e0 */ 	lh	$t8,0xe0($t7)
/*  f03fdd4:	2419005a */ 	addiu	$t9,$zero,0x5a
/*  f03fdd8:	3c017f1a */ 	lui	$at,0x7f1a
/*  f03fddc:	03386823 */ 	subu	$t5,$t9,$t8
/*  f03fde0:	448d2000 */ 	mtc1	$t5,$f4
/*  f03fde4:	c42833fc */ 	lwc1	$f8,0x33fc($at)
/*  f03fde8:	44825000 */ 	mtc1	$v0,$f10
/*  f03fdec:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f03fdf0:	3c013f80 */ 	lui	$at,0x3f80
/*  f03fdf4:	44819000 */ 	mtc1	$at,$f18
/*  f03fdf8:	46805420 */ 	cvt.s.w	$f16,$f10
/*  f03fdfc:	46083002 */ 	mul.s	$f0,$f6,$f8
/*  f03fe00:	46009100 */ 	add.s	$f4,$f18,$f0
/*  f03fe04:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f03fe08:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f03fe0c:	44044000 */ 	mfc1	$a0,$f8
/*  f03fe10:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f03fe14:
/*  f03fe14:	8faa0278 */ 	lw	$t2,0x278($sp)
.NB0f03fe18:
/*  f03fe18:	8fab027c */ 	lw	$t3,0x27c($sp)
/*  f03fe1c:	3c0f800a */ 	lui	$t7,0x800a
/*  f03fe20:	8defe6f8 */ 	lw	$t7,-0x1908($t7)
/*  f03fe24:	014b1821 */ 	addu	$v1,$t2,$t3
/*  f03fe28:	906e0004 */ 	lbu	$t6,0x4($v1)
/*  f03fe2c:	01cfc821 */ 	addu	$t9,$t6,$t7
/*  f03fe30:	333800ff */ 	andi	$t8,$t9,0xff
/*  f03fe34:	0304082a */ 	slt	$at,$t8,$a0
/*  f03fe38:	1420002b */ 	bnez	$at,.NB0f03fee8
/*  f03fe3c:	a0790004 */ 	sb	$t9,0x4($v1)
/*  f03fe40:	a0600004 */ 	sb	$zero,0x4($v1)
/*  f03fe44:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f03fe48:	8fad027c */ 	lw	$t5,0x27c($sp)
/*  f03fe4c:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f03fe50:	8d4b032c */ 	lw	$t3,0x32c($t2)
/*  f03fe54:	01ac1004 */ 	sllv	$v0,$t4,$t5
/*  f03fe58:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f03fe5c:	000b7300 */ 	sll	$t6,$t3,0xc
/*  f03fe60:	914b032d */ 	lbu	$t3,0x32d($t2)
/*  f03fe64:	000e7f82 */ 	srl	$t7,$t6,0x1e
/*  f03fe68:	01e2c026 */ 	xor	$t8,$t7,$v0
/*  f03fe6c:	00186080 */ 	sll	$t4,$t8,0x2
/*  f03fe70:	318d000c */ 	andi	$t5,$t4,0xc
/*  f03fe74:	316efff3 */ 	andi	$t6,$t3,0xfff3
/*  f03fe78:	01ae7825 */ 	or	$t7,$t5,$t6
/*  f03fe7c:	a14f032d */ 	sb	$t7,0x32d($t2)
/*  f03fe80:	8d59032c */ 	lw	$t9,0x32c($t2)
/*  f03fe84:	93ad0260 */ 	lbu	$t5,0x260($sp)
/*  f03fe88:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f03fe8c:	0019c300 */ 	sll	$t8,$t9,0xc
/*  f03fe90:	00186782 */ 	srl	$t4,$t8,0x1e
/*  f03fe94:	01825824 */ 	and	$t3,$t4,$v0
/*  f03fe98:	15600003 */ 	bnez	$t3,.NB0f03fea8
/*  f03fe9c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f03fea0:	55a10003 */ 	bnel	$t5,$at,.NB0f03feb0
/*  f03fea4:	8faf0278 */ 	lw	$t7,0x278($sp)
.NB0f03fea8:
/*  f03fea8:	afae0250 */ 	sw	$t6,0x250($sp)
/*  f03feac:	8faf0278 */ 	lw	$t7,0x278($sp)
.NB0f03feb0:
/*  f03feb0:	24010008 */ 	addiu	$at,$zero,0x8
/*  f03feb4:	81ea0007 */ 	lb	$t2,0x7($t7)
/*  f03feb8:	1541000b */ 	bne	$t2,$at,.NB0f03fee8
/*  f03febc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f03fec0:	8de40020 */ 	lw	$a0,0x20($t7)
/*  f03fec4:	0c00786f */ 	jal	modelGetAnimNum
/*  f03fec8:	afa60254 */ 	sw	$a2,0x254($sp)
/*  f03fecc:	2401026a */ 	addiu	$at,$zero,0x26a
/*  f03fed0:	14410005 */ 	bne	$v0,$at,.NB0f03fee8
/*  f03fed4:	8fa60254 */ 	lw	$a2,0x254($sp)
/*  f03fed8:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f03fedc:	83380033 */ 	lb	$t8,0x33($t9)
/*  f03fee0:	270c0001 */ 	addiu	$t4,$t8,0x1
/*  f03fee4:	a32c0033 */ 	sb	$t4,0x33($t9)
.NB0f03fee8:
/*  f03fee8:	50c00495 */ 	beqzl	$a2,.NB0f041140
/*  f03feec:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f03fef0:	0fc0f779 */ 	jal	chrGetAimAngle
/*  f03fef4:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f03fef8:	e7a00204 */ 	swc1	$f0,0x204($sp)
/*  f03fefc:	0fc0f7d2 */ 	jal	func0f03e754
/*  f03ff00:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f03ff04:	93ab026f */ 	lbu	$t3,0x26f($sp)
/*  f03ff08:	e7a00200 */ 	swc1	$f0,0x200($sp)
/*  f03ff0c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f03ff10:	11600004 */ 	beqz	$t3,.NB0f03ff24
/*  f03ff14:	27a60244 */ 	addiu	$a2,$sp,0x244
/*  f03ff18:	240d0004 */ 	addiu	$t5,$zero,0x4
/*  f03ff1c:	10000002 */ 	beqz	$zero,.NB0f03ff28
/*  f03ff20:	afad01fc */ 	sw	$t5,0x1fc($sp)
.NB0f03ff24:
/*  f03ff24:	afa001fc */ 	sw	$zero,0x1fc($sp)
.NB0f03ff28:
/*  f03ff28:	afae0268 */ 	sw	$t6,0x268($sp)
/*  f03ff2c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f03ff30:	0fc0fd76 */ 	jal	func0f03fde4
/*  f03ff34:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f03ff38:	54400032 */ 	bnezl	$v0,.NB0f040004
/*  f03ff3c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f03ff40:	8fa20274 */ 	lw	$v0,0x274($sp)
/*  f03ff44:	3c0141f0 */ 	lui	$at,0x41f0
/*  f03ff48:	44818000 */ 	mtc1	$at,$f16
/*  f03ff4c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f03ff50:	8faa027c */ 	lw	$t2,0x27c($sp)
/*  f03ff54:	24010001 */ 	addiu	$at,$zero,0x1
/*  f03ff58:	e7aa0244 */ 	swc1	$f10,0x244($sp)
/*  f03ff5c:	c452000c */ 	lwc1	$f18,0xc($v0)
/*  f03ff60:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f03ff64:	e7a40248 */ 	swc1	$f4,0x248($sp)
/*  f03ff68:	c4460010 */ 	lwc1	$f6,0x10($v0)
/*  f03ff6c:	15410013 */ 	bne	$t2,$at,.NB0f03ffbc
/*  f03ff70:	e7a6024c */ 	swc1	$f6,0x24c($sp)
/*  f03ff74:	0c006d52 */ 	jal	cosf
/*  f03ff78:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f03ff7c:	3c014120 */ 	lui	$at,0x4120
/*  f03ff80:	44815000 */ 	mtc1	$at,$f10
/*  f03ff84:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f03ff88:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f03ff8c:	460a0482 */ 	mul.s	$f18,$f0,$f10
/*  f03ff90:	46124400 */ 	add.s	$f16,$f8,$f18
/*  f03ff94:	0c006d55 */ 	jal	sinf
/*  f03ff98:	e7b00244 */ 	swc1	$f16,0x244($sp)
/*  f03ff9c:	3c014120 */ 	lui	$at,0x4120
/*  f03ffa0:	44813000 */ 	mtc1	$at,$f6
/*  f03ffa4:	46000107 */ 	neg.s	$f4,$f0
/*  f03ffa8:	c7a8024c */ 	lwc1	$f8,0x24c($sp)
/*  f03ffac:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f03ffb0:	460a4480 */ 	add.s	$f18,$f8,$f10
/*  f03ffb4:	10000012 */ 	beqz	$zero,.NB0f040000
/*  f03ffb8:	e7b2024c */ 	swc1	$f18,0x24c($sp)
.NB0f03ffbc:
/*  f03ffbc:	0c006d52 */ 	jal	cosf
/*  f03ffc0:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f03ffc4:	3c014120 */ 	lui	$at,0x4120
/*  f03ffc8:	44812000 */ 	mtc1	$at,$f4
/*  f03ffcc:	46000407 */ 	neg.s	$f16,$f0
/*  f03ffd0:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f03ffd4:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f03ffd8:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f03ffdc:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f03ffe0:	0c006d55 */ 	jal	sinf
/*  f03ffe4:	e7aa0244 */ 	swc1	$f10,0x244($sp)
/*  f03ffe8:	3c014120 */ 	lui	$at,0x4120
/*  f03ffec:	44818000 */ 	mtc1	$at,$f16
/*  f03fff0:	c7b2024c */ 	lwc1	$f18,0x24c($sp)
/*  f03fff4:	46100102 */ 	mul.s	$f4,$f0,$f16
/*  f03fff8:	46049200 */ 	add.s	$f8,$f18,$f4
/*  f03fffc:	e7a8024c */ 	swc1	$f8,0x24c($sp)
.NB0f040000:
/*  f040000:	8fa40278 */ 	lw	$a0,0x278($sp)
.NB0f040004:
/*  f040004:	0fc07927 */ 	jal	chrSetPerimEnabled
/*  f040008:	00002825 */ 	or	$a1,$zero,$zero
/*  f04000c:	8fb801fc */ 	lw	$t8,0x1fc($sp)
/*  f040010:	8faf0274 */ 	lw	$t7,0x274($sp)
/*  f040014:	24190010 */ 	addiu	$t9,$zero,0x10
/*  f040018:	370c082a */ 	ori	$t4,$t8,0x82a
/*  f04001c:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f040020:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f040024:	27a60244 */ 	addiu	$a2,$sp,0x244
/*  f040028:	27a70234 */ 	addiu	$a3,$sp,0x234
/*  f04002c:	25e40008 */ 	addiu	$a0,$t7,0x8
/*  f040030:	0c00bc8f */ 	jal	cd0002de34
/*  f040034:	25e50028 */ 	addiu	$a1,$t7,0x28
/*  f040038:	14400002 */ 	bnez	$v0,.NB0f040044
/*  f04003c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f040040:	afa00268 */ 	sw	$zero,0x268($sp)
.NB0f040044:
/*  f040044:	0fc07927 */ 	jal	chrSetPerimEnabled
/*  f040048:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f04004c:	8fab0268 */ 	lw	$t3,0x268($sp)
/*  f040050:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f040054:	5160043a */ 	beqzl	$t3,.NB0f041140
/*  f040058:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f04005c:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f040060:	afa001f8 */ 	sw	$zero,0x1f8($sp)
/*  f040064:	afa001f4 */ 	sw	$zero,0x1f4($sp)
/*  f040068:	afad01f0 */ 	sw	$t5,0x1f0($sp)
/*  f04006c:	11c00004 */ 	beqz	$t6,.NB0f040080
/*  f040070:	afa001cc */ 	sw	$zero,0x1cc($sp)
/*  f040074:	240a083f */ 	addiu	$t2,$zero,0x83f
/*  f040078:	10000003 */ 	beqz	$zero,.NB0f040088
/*  f04007c:	afaa01c8 */ 	sw	$t2,0x1c8($sp)
.NB0f040080:
/*  f040080:	240f083b */ 	addiu	$t7,$zero,0x83b
/*  f040084:	afaf01c8 */ 	sw	$t7,0x1c8($sp)
.NB0f040088:
/*  f040088:	8fa7025c */ 	lw	$a3,0x25c($sp)
/*  f04008c:	8ce20004 */ 	lw	$v0,0x4($a3)
/*  f040090:	50400004 */ 	beqzl	$v0,.NB0f0400a4
/*  f040094:	00004825 */ 	or	$t1,$zero,$zero
/*  f040098:	10000002 */ 	beqz	$zero,.NB0f0400a4
/*  f04009c:	904902fe */ 	lbu	$t1,0x2fe($v0)
/*  f0400a0:	00004825 */ 	or	$t1,$zero,$zero
.NB0f0400a4:
/*  f0400a4:	39220003 */ 	xori	$v0,$t1,0x3
/*  f0400a8:	2c420001 */ 	sltiu	$v0,$v0,0x1
/*  f0400ac:	1040000f */ 	beqz	$v0,.NB0f0400ec
/*  f0400b0:	00401825 */ 	or	$v1,$v0,$zero
/*  f0400b4:	afa2005c */ 	sw	$v0,0x5c($sp)
/*  f0400b8:	0fc121b6 */ 	jal	chrGetDistanceToTarget
/*  f0400bc:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0400c0:	3c014316 */ 	lui	$at,0x4316
/*  f0400c4:	44813000 */ 	mtc1	$at,$f6
/*  f0400c8:	0000c025 */ 	or	$t8,$zero,$zero
/*  f0400cc:	4600303c */ 	c.lt.s	$f6,$f0
/*  f0400d0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0400d4:	45020003 */ 	bc1fl	.NB0f0400e4
/*  f0400d8:	afb8005c */ 	sw	$t8,0x5c($sp)
/*  f0400dc:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f0400e0:	afb8005c */ 	sw	$t8,0x5c($sp)
.NB0f0400e4:
/*  f0400e4:	8fa7025c */ 	lw	$a3,0x25c($sp)
/*  f0400e8:	03001825 */ 	or	$v1,$t8,$zero
.NB0f0400ec:
/*  f0400ec:	afa301c0 */ 	sw	$v1,0x1c0($sp)
/*  f0400f0:	10600016 */ 	beqz	$v1,.NB0f04014c
/*  f0400f4:	afa001bc */ 	sw	$zero,0x1bc($sp)
/*  f0400f8:	c4ea0008 */ 	lwc1	$f10,0x8($a3)
/*  f0400fc:	c7b00244 */ 	lwc1	$f16,0x244($sp)
/*  f040100:	c7a80248 */ 	lwc1	$f8,0x248($sp)
/*  f040104:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f040108:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f04010c:	c7b0024c */ 	lwc1	$f16,0x24c($sp)
/*  f040110:	27a501e4 */ 	addiu	$a1,$sp,0x1e4
/*  f040114:	27a601e8 */ 	addiu	$a2,$sp,0x1e8
/*  f040118:	e7b201e0 */ 	swc1	$f18,0x1e0($sp)
/*  f04011c:	c4e4000c */ 	lwc1	$f4,0xc($a3)
/*  f040120:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f040124:	e7a601e4 */ 	swc1	$f6,0x1e4($sp)
/*  f040128:	c4ea0010 */ 	lwc1	$f10,0x10($a3)
/*  f04012c:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f040130:	0c0012a8 */ 	jal	guNormalize
/*  f040134:	e7b201e8 */ 	swc1	$f18,0x1e8($sp)
/*  f040138:	8fa4025c */ 	lw	$a0,0x25c($sp)
/*  f04013c:	0fc18cfb */ 	jal	propSetPerimEnabled
/*  f040140:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f040144:	1000002f */ 	beqz	$zero,.NB0f040204
/*  f040148:	8fab0278 */ 	lw	$t3,0x278($sp)
.NB0f04014c:
/*  f04014c:	0c006d52 */ 	jal	cosf
/*  f040150:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040154:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*  f040158:	0c006d55 */ 	jal	sinf
/*  f04015c:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f040160:	c7a40060 */ 	lwc1	$f4,0x60($sp)
/*  f040164:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040168:	46040202 */ 	mul.s	$f8,$f0,$f4
/*  f04016c:	0c006d55 */ 	jal	sinf
/*  f040170:	e7a801e0 */ 	swc1	$f8,0x1e0($sp)
/*  f040174:	e7a001e4 */ 	swc1	$f0,0x1e4($sp)
/*  f040178:	0c006d52 */ 	jal	cosf
/*  f04017c:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f040180:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*  f040184:	0c006d52 */ 	jal	cosf
/*  f040188:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f04018c:	c7a60060 */ 	lwc1	$f6,0x60($sp)
/*  f040190:	93ac026f */ 	lbu	$t4,0x26f($sp)
/*  f040194:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f040198:	11800019 */ 	beqz	$t4,.NB0f040200
/*  f04019c:	e7aa01e8 */ 	swc1	$f10,0x1e8($sp)
/*  f0401a0:	0fc62d37 */ 	jal	chrGuessCrouchPos
/*  f0401a4:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0401a8:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f0401ac:	00404825 */ 	or	$t1,$v0,$zero
/*  f0401b0:	8fae0278 */ 	lw	$t6,0x278($sp)
/*  f0401b4:	8f280170 */ 	lw	$t0,0x170($t9)
/*  f0401b8:	0008582b */ 	sltu	$t3,$zero,$t0
/*  f0401bc:	11600004 */ 	beqz	$t3,.NB0f0401d0
/*  f0401c0:	01604025 */ 	or	$t0,$t3,$zero
/*  f0401c4:	8f280174 */ 	lw	$t0,0x174($t9)
/*  f0401c8:	0008682b */ 	sltu	$t5,$zero,$t0
/*  f0401cc:	01a04025 */ 	or	$t0,$t5,$zero
.NB0f0401d0:
/*  f0401d0:	8dc302d4 */ 	lw	$v1,0x2d4($t6)
/*  f0401d4:	8fb8027c */ 	lw	$t8,0x27c($sp)
/*  f0401d8:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f0401dc:	8c66004c */ 	lw	$a2,0x4c($v1)
/*  f0401e0:	00786021 */ 	addu	$t4,$v1,$t8
/*  f0401e4:	9187004d */ 	lbu	$a3,0x4d($t4)
/*  f0401e8:	8c650020 */ 	lw	$a1,0x20($v1)
/*  f0401ec:	00065080 */ 	sll	$t2,$a2,0x2
/*  f0401f0:	000a37c2 */ 	srl	$a2,$t2,0x1f
/*  f0401f4:	afa80014 */ 	sw	$t0,0x14($sp)
/*  f0401f8:	0fc27b58 */ 	jal	bgun0f0a0fac
/*  f0401fc:	afa90010 */ 	sw	$t1,0x10($sp)
.NB0f040200:
/*  f040200:	8fab0278 */ 	lw	$t3,0x278($sp)
.NB0f040204:
/*  f040204:	93b90260 */ 	lbu	$t9,0x260($sp)
/*  f040208:	24010016 */ 	addiu	$at,$zero,0x16
/*  f04020c:	8d6302d4 */ 	lw	$v1,0x2d4($t3)
/*  f040210:	50600018 */ 	beqzl	$v1,.NB0f040274
/*  f040214:	3c014780 */ 	lui	$at,0x4780
/*  f040218:	57210016 */ 	bnel	$t9,$at,.NB0f040274
/*  f04021c:	3c014780 */ 	lui	$at,0x4780
/*  f040220:	8c6d0128 */ 	lw	$t5,0x128($v1)
/*  f040224:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f040228:	01602025 */ 	or	$a0,$t3,$zero
/*  f04022c:	15a00010 */ 	bnez	$t5,.NB0f040270
/*  f040230:	00002825 */ 	or	$a1,$zero,$zero
/*  f040234:	afae0250 */ 	sw	$t6,0x250($sp)
/*  f040238:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f04023c:	0fc64fd9 */ 	jal	aibotDoFarsightThing
/*  f040240:	27a70244 */ 	addiu	$a3,$sp,0x244
/*  f040244:	24010002 */ 	addiu	$at,$zero,0x2
/*  f040248:	5441000a */ 	bnel	$v0,$at,.NB0f040274
/*  f04024c:	3c014780 */ 	lui	$at,0x4780
/*  f040250:	0c004d84 */ 	jal	random
/*  f040254:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040258:	240100ff */ 	addiu	$at,$zero,0xff
/*  f04025c:	0041001b */ 	divu	$zero,$v0,$at
/*  f040260:	00005010 */ 	mfhi	$t2
/*  f040264:	2d4f00c9 */ 	sltiu	$t7,$t2,0xc9
/*  f040268:	39ef0001 */ 	xori	$t7,$t7,0x1
/*  f04026c:	a3af026e */ 	sb	$t7,0x26e($sp)
.NB0f040270:
/*  f040270:	3c014780 */ 	lui	$at,0x4780
.NB0f040274:
/*  f040274:	44810000 */ 	mtc1	$at,$f0
/*  f040278:	c7b001e0 */ 	lwc1	$f16,0x1e0($sp)
/*  f04027c:	c7a40244 */ 	lwc1	$f4,0x244($sp)
/*  f040280:	c7a601e4 */ 	lwc1	$f6,0x1e4($sp)
/*  f040284:	46008482 */ 	mul.s	$f18,$f16,$f0
/*  f040288:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f04028c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040290:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f040294:	c7a6024c */ 	lwc1	$f6,0x24c($sp)
/*  f040298:	00002825 */ 	or	$a1,$zero,$zero
/*  f04029c:	46049200 */ 	add.s	$f8,$f18,$f4
/*  f0402a0:	c7a401e8 */ 	lwc1	$f4,0x1e8($sp)
/*  f0402a4:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f0402a8:	e7a80228 */ 	swc1	$f8,0x228($sp)
/*  f0402ac:	46002202 */ 	mul.s	$f8,$f4,$f0
/*  f0402b0:	e7b2022c */ 	swc1	$f18,0x22c($sp)
/*  f0402b4:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f0402b8:	0fc07927 */ 	jal	chrSetPerimEnabled
/*  f0402bc:	e7aa0230 */ 	swc1	$f10,0x230($sp)
/*  f0402c0:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f0402c4:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f0402c8:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f0402cc:	13000004 */ 	beqz	$t8,.NB0f0402e0
/*  f0402d0:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0402d4:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0402d8:	3c01800a */ 	lui	$at,0x800a
/*  f0402dc:	ac2ceb4c */ 	sw	$t4,-0x14b4($at)
.NB0f0402e0:
/*  f0402e0:	24190010 */ 	addiu	$t9,$zero,0x10
/*  f0402e4:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f0402e8:	0c00bc66 */ 	jal	cdTestAToB4
/*  f0402ec:	8fa701c8 */ 	lw	$a3,0x1c8($sp)
/*  f0402f0:	1440000a */ 	bnez	$v0,.NB0f04031c
/*  f0402f4:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f0402f8:	3c067f1a */ 	lui	$a2,0x7f1a
/*  f0402fc:	afad0224 */ 	sw	$t5,0x224($sp)
/*  f040300:	24c62e9c */ 	addiu	$a2,$a2,0x2e9c
/*  f040304:	27a40228 */ 	addiu	$a0,$sp,0x228
/*  f040308:	0c0098a7 */ 	jal	cdGetPos
/*  f04030c:	24052f36 */ 	addiu	$a1,$zero,0x2f36
/*  f040310:	0c0098a4 */ 	jal	cdGetObstacle
/*  f040314:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040318:	afa201cc */ 	sw	$v0,0x1cc($sp)
.NB0f04031c:
/*  f04031c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040320:	0fc07927 */ 	jal	chrSetPerimEnabled
/*  f040324:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f040328:	93ae026f */ 	lbu	$t6,0x26f($sp)
/*  f04032c:	3c01800a */ 	lui	$at,0x800a
/*  f040330:	51c00003 */ 	beqzl	$t6,.NB0f040340
/*  f040334:	8fab01cc */ 	lw	$t3,0x1cc($sp)
/*  f040338:	ac20eb4c */ 	sw	$zero,-0x14b4($at)
/*  f04033c:	8fab01cc */ 	lw	$t3,0x1cc($sp)
.NB0f040340:
/*  f040340:	8faa01c0 */ 	lw	$t2,0x1c0($sp)
/*  f040344:	55600015 */ 	bnezl	$t3,.NB0f04039c
/*  f040348:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f04034c:	51400013 */ 	beqzl	$t2,.NB0f04039c
/*  f040350:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f040354:	0c004d84 */ 	jal	random
/*  f040358:	00000000 */ 	sll	$zero,$zero,0x0
/*  f04035c:	24010064 */ 	addiu	$at,$zero,0x64
/*  f040360:	0041001b */ 	divu	$zero,$v0,$at
/*  f040364:	00001810 */ 	mfhi	$v1
/*  f040368:	2c6f0033 */ 	sltiu	$t7,$v1,0x33
/*  f04036c:	39ef0001 */ 	xori	$t7,$t7,0x1
/*  f040370:	11e00009 */ 	beqz	$t7,.NB0f040398
/*  f040374:	afaf01bc */ 	sw	$t7,0x1bc($sp)
/*  f040378:	8fb8025c */ 	lw	$t8,0x25c($sp)
/*  f04037c:	afb801cc */ 	sw	$t8,0x1cc($sp)
/*  f040380:	c7100008 */ 	lwc1	$f16,0x8($t8)
/*  f040384:	e7b00228 */ 	swc1	$f16,0x228($sp)
/*  f040388:	c712000c */ 	lwc1	$f18,0xc($t8)
/*  f04038c:	e7b2022c */ 	swc1	$f18,0x22c($sp)
/*  f040390:	c7040010 */ 	lwc1	$f4,0x10($t8)
/*  f040394:	e7a40230 */ 	swc1	$f4,0x230($sp)
.NB0f040398:
/*  f040398:	c7a80228 */ 	lwc1	$f8,0x228($sp)
.NB0f04039c:
/*  f04039c:	c7a60244 */ 	lwc1	$f6,0x244($sp)
/*  f0403a0:	c7aa022c */ 	lwc1	$f10,0x22c($sp)
/*  f0403a4:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f0403a8:	46064001 */ 	sub.s	$f0,$f8,$f6
/*  f0403ac:	c7b20230 */ 	lwc1	$f18,0x230($sp)
/*  f0403b0:	c7a4024c */ 	lwc1	$f4,0x24c($sp)
/*  f0403b4:	46105081 */ 	sub.s	$f2,$f10,$f16
/*  f0403b8:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f0403bc:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f0403c0:	46049301 */ 	sub.s	$f12,$f18,$f4
/*  f0403c4:	46021182 */ 	mul.s	$f6,$f2,$f2
/*  f0403c8:	24010018 */ 	addiu	$at,$zero,0x18
/*  f0403cc:	460c6402 */ 	mul.s	$f16,$f12,$f12
/*  f0403d0:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f0403d4:	46105480 */ 	add.s	$f18,$f10,$f16
/*  f0403d8:	1081000f */ 	beq	$a0,$at,.NB0f040418
/*  f0403dc:	e7b201d0 */ 	swc1	$f18,0x1d0($sp)
/*  f0403e0:	24010019 */ 	addiu	$at,$zero,0x19
/*  f0403e4:	1081000c */ 	beq	$a0,$at,.NB0f040418
/*  f0403e8:	24010012 */ 	addiu	$at,$zero,0x12
/*  f0403ec:	14810003 */ 	bne	$a0,$at,.NB0f0403fc
/*  f0403f0:	93ac0263 */ 	lbu	$t4,0x263($sp)
/*  f0403f4:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0403f8:	11810007 */ 	beq	$t4,$at,.NB0f040418
.NB0f0403fc:
/*  f0403fc:	24010017 */ 	addiu	$at,$zero,0x17
/*  f040400:	10810005 */ 	beq	$a0,$at,.NB0f040418
/*  f040404:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f040408:	10810003 */ 	beq	$a0,$at,.NB0f040418
/*  f04040c:	24010034 */ 	addiu	$at,$zero,0x34
/*  f040410:	54810171 */ 	bnel	$a0,$at,.NB0f0409d8
/*  f040414:	24010006 */ 	addiu	$at,$zero,0x6
.NB0f040418:
/*  f040418:	93b9026f */ 	lbu	$t9,0x26f($sp)
/*  f04041c:	afa00250 */ 	sw	$zero,0x250($sp)
/*  f040420:	3c017f1a */ 	lui	$at,0x7f1a
/*  f040424:	17200006 */ 	bnez	$t9,.NB0f040440
/*  f040428:	c7a801d0 */ 	lwc1	$f8,0x1d0($sp)
/*  f04042c:	c4243400 */ 	lwc1	$f4,0x3400($at)
/*  f040430:	4608203c */ 	c.lt.s	$f4,$f8
/*  f040434:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040438:	45020164 */ 	bc1fl	.NB0f0409cc
/*  f04043c:	afa00268 */ 	sw	$zero,0x268($sp)
.NB0f040440:
/*  f040440:	0fc2bb4c */ 	jal	weaponFindById
/*  f040444:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040448:	93ad0263 */ 	lbu	$t5,0x263($sp)
/*  f04044c:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f040450:	24010018 */ 	addiu	$at,$zero,0x18
/*  f040454:	000d7080 */ 	sll	$t6,$t5,0x2
/*  f040458:	004e5821 */ 	addu	$t3,$v0,$t6
/*  f04045c:	10810006 */ 	beq	$a0,$at,.NB0f040478
/*  f040460:	8d630014 */ 	lw	$v1,0x14($t3)
/*  f040464:	24010034 */ 	addiu	$at,$zero,0x34
/*  f040468:	10810003 */ 	beq	$a0,$at,.NB0f040478
/*  f04046c:	24010019 */ 	addiu	$at,$zero,0x19
/*  f040470:	5481000e */ 	bnel	$a0,$at,.NB0f0404ac
/*  f040474:	2401001b */ 	addiu	$at,$zero,0x1b
.NB0f040478:
/*  f040478:	8c6a0010 */ 	lw	$t2,0x10($v1)
/*  f04047c:	24050052 */ 	addiu	$a1,$zero,0x52
/*  f040480:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040484:	000a7840 */ 	sll	$t7,$t2,0x1
/*  f040488:	05e30003 */ 	bgezl	$t7,.NB0f040498
/*  f04048c:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040490:	24050053 */ 	addiu	$a1,$zero,0x53
/*  f040494:	8c640040 */ 	lw	$a0,0x40($v1)
.NB0f040498:
/*  f040498:	0fc2282a */ 	jal	func0f08b880
/*  f04049c:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f0404a0:	1000002e */ 	beqz	$zero,.NB0f04055c
/*  f0404a4:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f0404a8:	2401001b */ 	addiu	$at,$zero,0x1b
.NB0f0404ac:
/*  f0404ac:	1481000a */ 	bne	$a0,$at,.NB0f0404d8
/*  f0404b0:	24050055 */ 	addiu	$a1,$zero,0x55
/*  f0404b4:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f0404b8:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f0404bc:	0fc2282a */ 	jal	func0f08b880
/*  f0404c0:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f0404c4:	10400025 */ 	beqz	$v0,.NB0f04055c
/*  f0404c8:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f0404cc:	93b80263 */ 	lbu	$t8,0x263($sp)
/*  f0404d0:	10000022 */ 	beqz	$zero,.NB0f04055c
/*  f0404d4:	a058005f */ 	sb	$t8,0x5f($v0)
.NB0f0404d8:
/*  f0404d8:	24010017 */ 	addiu	$at,$zero,0x17
/*  f0404dc:	1481000a */ 	bne	$a0,$at,.NB0f040508
/*  f0404e0:	24050054 */ 	addiu	$a1,$zero,0x54
/*  f0404e4:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f0404e8:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f0404ec:	0fc2282a */ 	jal	func0f08b880
/*  f0404f0:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f0404f4:	10400019 */ 	beqz	$v0,.NB0f04055c
/*  f0404f8:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f0404fc:	93ac0263 */ 	lbu	$t4,0x263($sp)
/*  f040500:	10000016 */ 	beqz	$zero,.NB0f04055c
/*  f040504:	a04c005f */ 	sb	$t4,0x5f($v0)
.NB0f040508:
/*  f040508:	24010012 */ 	addiu	$at,$zero,0x12
/*  f04050c:	1481000b */ 	bne	$a0,$at,.NB0f04053c
/*  f040510:	3c0d800a */ 	lui	$t5,0x800a
/*  f040514:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040518:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f04051c:	24050054 */ 	addiu	$a1,$zero,0x54
/*  f040520:	0fc2282a */ 	jal	func0f08b880
/*  f040524:	8fa60278 */ 	lw	$a2,0x278($sp)
/*  f040528:	1040000c */ 	beqz	$v0,.NB0f04055c
/*  f04052c:	afa201b8 */ 	sw	$v0,0x1b8($sp)
/*  f040530:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f040534:	10000009 */ 	beqz	$zero,.NB0f04055c
/*  f040538:	a059005f */ 	sb	$t9,0x5f($v0)
.NB0f04053c:
/*  f04053c:	8dade944 */ 	lw	$t5,-0x16bc($t5)
/*  f040540:	8c640040 */ 	lw	$a0,0x40($v1)
/*  f040544:	27a50260 */ 	addiu	$a1,$sp,0x260
/*  f040548:	8dae00bc */ 	lw	$t6,0xbc($t5)
/*  f04054c:	8dc60004 */ 	lw	$a2,0x4($t6)
/*  f040550:	0fc227a4 */ 	jal	func0f08b658
/*  f040554:	afa300d4 */ 	sw	$v1,0xd4($sp)
/*  f040558:	afa201b8 */ 	sw	$v0,0x1b8($sp)
.NB0f04055c:
/*  f04055c:	1040011b */ 	beqz	$v0,.NB0f0409cc
/*  f040560:	8fab00d4 */ 	lw	$t3,0xd4($sp)
/*  f040564:	8d6a004c */ 	lw	$t2,0x4c($t3)
/*  f040568:	3c017f1a */ 	lui	$at,0x7f1a
/*  f04056c:	c4303404 */ 	lwc1	$f16,0x3404($at)
/*  f040570:	448a3000 */ 	mtc1	$t2,$f6
/*  f040574:	3c014270 */ 	lui	$at,0x4270
/*  f040578:	44812000 */ 	mtc1	$at,$f4
/*  f04057c:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f040580:	3c017f1a */ 	lui	$at,0x7f1a
/*  f040584:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f040588:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f04058c:	2405001e */ 	addiu	$a1,$zero,0x1e
/*  f040590:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f040594:	c4303408 */ 	lwc1	$f16,0x3408($at)
/*  f040598:	46049203 */ 	div.s	$f8,$f18,$f4
/*  f04059c:	e7a80168 */ 	swc1	$f8,0x168($sp)
/*  f0405a0:	8d6f0054 */ 	lw	$t7,0x54($t3)
/*  f0405a4:	448f3000 */ 	mtc1	$t7,$f6
/*  f0405a8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0405ac:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f0405b0:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f0405b4:	13000080 */ 	beqz	$t8,.NB0f0407b8
/*  f0405b8:	e7b200cc */ 	swc1	$f18,0xcc($sp)
/*  f0405bc:	0fc1215e */ 	jal	chrIsTargetInFov
/*  f0405c0:	00003025 */ 	or	$a2,$zero,$zero
/*  f0405c4:	1040007c */ 	beqz	$v0,.NB0f0407b8
/*  f0405c8:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0405cc:	93a20263 */ 	lbu	$v0,0x263($sp)
/*  f0405d0:	00001825 */ 	or	$v1,$zero,$zero
/*  f0405d4:	93a40260 */ 	lbu	$a0,0x260($sp)
/*  f0405d8:	14400025 */ 	bnez	$v0,.NB0f040670
/*  f0405dc:	24010018 */ 	addiu	$at,$zero,0x18
/*  f0405e0:	10810006 */ 	beq	$a0,$at,.NB0f0405fc
/*  f0405e4:	8fac025c */ 	lw	$t4,0x25c($sp)
/*  f0405e8:	24010034 */ 	addiu	$at,$zero,0x34
/*  f0405ec:	10810003 */ 	beq	$a0,$at,.NB0f0405fc
/*  f0405f0:	24010019 */ 	addiu	$at,$zero,0x19
/*  f0405f4:	5481001f */ 	bnel	$a0,$at,.NB0f040674
/*  f0405f8:	93a40260 */ 	lbu	$a0,0x260($sp)
.NB0f0405fc:
/*  f0405fc:	91820000 */ 	lbu	$v0,0x0($t4)
/*  f040600:	24010003 */ 	addiu	$at,$zero,0x3
/*  f040604:	8fb9025c */ 	lw	$t9,0x25c($sp)
/*  f040608:	10410003 */ 	beq	$v0,$at,.NB0f040618
/*  f04060c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040610:	14410051 */ 	bne	$v0,$at,.NB0f040758
/*  f040614:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f040618:
/*  f040618:	c7240008 */ 	lwc1	$f4,0x8($t9)
/*  f04061c:	c7aa0244 */ 	lwc1	$f10,0x244($sp)
/*  f040620:	c7b20248 */ 	lwc1	$f18,0x248($sp)
/*  f040624:	e7a400b8 */ 	swc1	$f4,0xb8($sp)
/*  f040628:	8f2d0004 */ 	lw	$t5,0x4($t9)
/*  f04062c:	460a2401 */ 	sub.s	$f16,$f4,$f10
/*  f040630:	c7aa024c */ 	lwc1	$f10,0x24c($sp)
/*  f040634:	c5a800b4 */ 	lwc1	$f8,0xb4($t5)
/*  f040638:	27a401e0 */ 	addiu	$a0,$sp,0x1e0
/*  f04063c:	27a501e4 */ 	addiu	$a1,$sp,0x1e4
/*  f040640:	e7a800bc */ 	swc1	$f8,0xbc($sp)
/*  f040644:	c7260010 */ 	lwc1	$f6,0x10($t9)
/*  f040648:	e7b001e0 */ 	swc1	$f16,0x1e0($sp)
/*  f04064c:	46124101 */ 	sub.s	$f4,$f8,$f18
/*  f040650:	27a601e8 */ 	addiu	$a2,$sp,0x1e8
/*  f040654:	e7a600c0 */ 	swc1	$f6,0xc0($sp)
/*  f040658:	460a3401 */ 	sub.s	$f16,$f6,$f10
/*  f04065c:	e7a401e4 */ 	swc1	$f4,0x1e4($sp)
/*  f040660:	0c0012a8 */ 	jal	guNormalize
/*  f040664:	e7b001e8 */ 	swc1	$f16,0x1e8($sp)
/*  f040668:	1000003b */ 	beqz	$zero,.NB0f040758
/*  f04066c:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0f040670:
/*  f040670:	93a40260 */ 	lbu	$a0,0x260($sp)
.NB0f040674:
/*  f040674:	24050017 */ 	addiu	$a1,$zero,0x17
/*  f040678:	24010012 */ 	addiu	$at,$zero,0x12
/*  f04067c:	14a40003 */ 	bne	$a1,$a0,.NB0f04068c
/*  f040680:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040684:	50400004 */ 	beqzl	$v0,.NB0f040698
/*  f040688:	8fae025c */ 	lw	$t6,0x25c($sp)
.NB0f04068c:
/*  f04068c:	14810017 */ 	bne	$a0,$at,.NB0f0406ec
/*  f040690:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040694:	8fae025c */ 	lw	$t6,0x25c($sp)
.NB0f040698:
/*  f040698:	24010003 */ 	addiu	$at,$zero,0x3
/*  f04069c:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f0406a0:	91c20000 */ 	lbu	$v0,0x0($t6)
/*  f0406a4:	10410003 */ 	beq	$v0,$at,.NB0f0406b4
/*  f0406a8:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0406ac:	1441002a */ 	bne	$v0,$at,.NB0f040758
/*  f0406b0:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f0406b4:
/*  f0406b4:	c5480008 */ 	lwc1	$f8,0x8($t2)
/*  f0406b8:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f0406bc:	8fa500cc */ 	lw	$a1,0xcc($sp)
/*  f0406c0:	e7a800b8 */ 	swc1	$f8,0xb8($sp)
/*  f0406c4:	8d4b0004 */ 	lw	$t3,0x4($t2)
/*  f0406c8:	27a600b8 */ 	addiu	$a2,$sp,0xb8
/*  f0406cc:	27a701e0 */ 	addiu	$a3,$sp,0x1e0
/*  f0406d0:	c57200b4 */ 	lwc1	$f18,0xb4($t3)
/*  f0406d4:	e7b200bc */ 	swc1	$f18,0xbc($sp)
/*  f0406d8:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f0406dc:	0fc0febf */ 	jal	func0f04031c
/*  f0406e0:	e7a400c0 */ 	swc1	$f4,0xc0($sp)
/*  f0406e4:	1000001c */ 	beqz	$zero,.NB0f040758
/*  f0406e8:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0f0406ec:
/*  f0406ec:	14a40002 */ 	bne	$a1,$a0,.NB0f0406f8
/*  f0406f0:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0406f4:	10410003 */ 	beq	$v0,$at,.NB0f040704
.NB0f0406f8:
/*  f0406f8:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f0406fc:	14810016 */ 	bne	$a0,$at,.NB0f040758
/*  f040700:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f040704:
/*  f040704:	8faf025c */ 	lw	$t7,0x25c($sp)
/*  f040708:	24010006 */ 	addiu	$at,$zero,0x6
/*  f04070c:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f040710:	c5e60008 */ 	lwc1	$f6,0x8($t7)
/*  f040714:	27a600b8 */ 	addiu	$a2,$sp,0xb8
/*  f040718:	27a701e0 */ 	addiu	$a3,$sp,0x1e0
/*  f04071c:	e7a600b8 */ 	swc1	$f6,0xb8($sp)
/*  f040720:	c5ea000c */ 	lwc1	$f10,0xc($t7)
/*  f040724:	e7aa00bc */ 	swc1	$f10,0xbc($sp)
/*  f040728:	c5f00010 */ 	lwc1	$f16,0x10($t7)
/*  f04072c:	e7b000c0 */ 	swc1	$f16,0xc0($sp)
/*  f040730:	91f80000 */ 	lbu	$t8,0x0($t7)
/*  f040734:	17010005 */ 	bne	$t8,$at,.NB0f04074c
/*  f040738:	3c0141c8 */ 	lui	$at,0x41c8
/*  f04073c:	44814000 */ 	mtc1	$at,$f8
/*  f040740:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040744:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f040748:	e7b200bc */ 	swc1	$f18,0xbc($sp)
.NB0f04074c:
/*  f04074c:	0fc0febf */ 	jal	func0f04031c
/*  f040750:	8fa500cc */ 	lw	$a1,0xcc($sp)
/*  f040754:	24030001 */ 	addiu	$v1,$zero,0x1
.NB0f040758:
/*  f040758:	10600017 */ 	beqz	$v1,.NB0f0407b8
/*  f04075c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040760:	0fc11fe5 */ 	jal	chrGetAngleToPos
/*  f040764:	27a500b8 */ 	addiu	$a1,$sp,0xb8
/*  f040768:	e7a000b4 */ 	swc1	$f0,0xb4($sp)
/*  f04076c:	0c006d52 */ 	jal	cosf
/*  f040770:	46000306 */ 	mov.s	$f12,$f0
/*  f040774:	c7ac00b4 */ 	lwc1	$f12,0xb4($sp)
/*  f040778:	0c006d55 */ 	jal	sinf
/*  f04077c:	e7a000b0 */ 	swc1	$f0,0xb0($sp)
/*  f040780:	c7ac01e8 */ 	lwc1	$f12,0x1e8($sp)
/*  f040784:	c7ae00b0 */ 	lwc1	$f14,0xb0($sp)
/*  f040788:	c7a201e0 */ 	lwc1	$f2,0x1e0($sp)
/*  f04078c:	460c0102 */ 	mul.s	$f4,$f0,$f12
/*  f040790:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040794:	46027182 */ 	mul.s	$f6,$f14,$f2
/*  f040798:	00000000 */ 	sll	$zero,$zero,0x0
/*  f04079c:	460c7282 */ 	mul.s	$f10,$f14,$f12
/*  f0407a0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0407a4:	46020202 */ 	mul.s	$f8,$f0,$f2
/*  f0407a8:	46062400 */ 	add.s	$f16,$f4,$f6
/*  f0407ac:	e7b001e0 */ 	swc1	$f16,0x1e0($sp)
/*  f0407b0:	46085481 */ 	sub.s	$f18,$f10,$f8
/*  f0407b4:	e7b201e8 */ 	swc1	$f18,0x1e8($sp)
.NB0f0407b8:
/*  f0407b8:	0c005a28 */ 	jal	mtx4LoadIdentity
/*  f0407bc:	27a40178 */ 	addiu	$a0,$sp,0x178
/*  f0407c0:	c7ac0200 */ 	lwc1	$f12,0x200($sp)
/*  f0407c4:	0c005c9e */ 	jal	mtx4LoadXRotation
/*  f0407c8:	27a5011c */ 	addiu	$a1,$sp,0x11c
/*  f0407cc:	c7ac0204 */ 	lwc1	$f12,0x204($sp)
/*  f0407d0:	0c005cc1 */ 	jal	mtx4LoadYRotation
/*  f0407d4:	27a500dc */ 	addiu	$a1,$sp,0xdc
/*  f0407d8:	27a400dc */ 	addiu	$a0,$sp,0xdc
/*  f0407dc:	0c005ab4 */ 	jal	mtx00015be0
/*  f0407e0:	27a5011c */ 	addiu	$a1,$sp,0x11c
/*  f0407e4:	c7ac0168 */ 	lwc1	$f12,0x168($sp)
/*  f0407e8:	c7a401e0 */ 	lwc1	$f4,0x1e0($sp)
/*  f0407ec:	c7b001e4 */ 	lwc1	$f16,0x1e4($sp)
/*  f0407f0:	c7a801e8 */ 	lwc1	$f8,0x1e8($sp)
/*  f0407f4:	460c2182 */ 	mul.s	$f6,$f4,$f12
/*  f0407f8:	c7a200cc */ 	lwc1	$f2,0xcc($sp)
/*  f0407fc:	3c01800a */ 	lui	$at,0x800a
/*  f040800:	460c8282 */ 	mul.s	$f10,$f16,$f12
/*  f040804:	c420e70c */ 	lwc1	$f0,-0x18f4($at)
/*  f040808:	8fac00d4 */ 	lw	$t4,0xd4($sp)
/*  f04080c:	460c4482 */ 	mul.s	$f18,$f8,$f12
/*  f040810:	e7a6015c */ 	swc1	$f6,0x15c($sp)
/*  f040814:	8fa401b8 */ 	lw	$a0,0x1b8($sp)
/*  f040818:	46022102 */ 	mul.s	$f4,$f4,$f2
/*  f04081c:	e7aa0160 */ 	swc1	$f10,0x160($sp)
/*  f040820:	2401ffff */ 	addiu	$at,$zero,-1
/*  f040824:	46003182 */ 	mul.s	$f6,$f6,$f0
/*  f040828:	e7b20164 */ 	swc1	$f18,0x164($sp)
/*  f04082c:	27a50244 */ 	addiu	$a1,$sp,0x244
/*  f040830:	27a60234 */ 	addiu	$a2,$sp,0x234
/*  f040834:	27a7011c */ 	addiu	$a3,$sp,0x11c
/*  f040838:	27ae016c */ 	addiu	$t6,$sp,0x16c
/*  f04083c:	27ab0178 */ 	addiu	$t3,$sp,0x178
/*  f040840:	46062100 */ 	add.s	$f4,$f4,$f6
/*  f040844:	46028182 */ 	mul.s	$f6,$f16,$f2
/*  f040848:	e7a4016c */ 	swc1	$f4,0x16c($sp)
/*  f04084c:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f040850:	46043400 */ 	add.s	$f16,$f6,$f4
/*  f040854:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f040858:	00000000 */ 	sll	$zero,$zero,0x0
/*  f04085c:	46009182 */ 	mul.s	$f6,$f18,$f0
/*  f040860:	e7b00170 */ 	swc1	$f16,0x170($sp)
/*  f040864:	46065100 */ 	add.s	$f4,$f10,$f6
/*  f040868:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f04086c:	8d8d0058 */ 	lw	$t5,0x58($t4)
/*  f040870:	a48d0062 */ 	sh	$t5,0x62($a0)
/*  f040874:	84820062 */ 	lh	$v0,0x62($a0)
/*  f040878:	10410002 */ 	beq	$v0,$at,.NB0f040884
/*  f04087c:	0002c880 */ 	sll	$t9,$v0,0x2
/*  f040880:	a4990062 */ 	sh	$t9,0x62($a0)
.NB0f040884:
/*  f040884:	8faa0274 */ 	lw	$t2,0x274($sp)
/*  f040888:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f04088c:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f040890:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f040894:	0fc27298 */ 	jal	bgun0f09ebcc
/*  f040898:	afaa0018 */ 	sw	$t2,0x18($sp)
/*  f04089c:	8fa301b8 */ 	lw	$v1,0x1b8($sp)
/*  f0408a0:	8fac00d4 */ 	lw	$t4,0xd4($sp)
/*  f0408a4:	8c6f0040 */ 	lw	$t7,0x40($v1)
/*  f0408a8:	31f80080 */ 	andi	$t8,$t7,0x80
/*  f0408ac:	13000047 */ 	beqz	$t8,.NB0f0409cc
/*  f0408b0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0408b4:	8d820010 */ 	lw	$v0,0x10($t4)
/*  f0408b8:	00026800 */ 	sll	$t5,$v0,0x0
/*  f0408bc:	05a10007 */ 	bgez	$t5,.NB0f0408dc
/*  f0408c0:	00025900 */ 	sll	$t3,$v0,0x4
/*  f0408c4:	8c620048 */ 	lw	$v0,0x48($v1)
/*  f0408c8:	3c014000 */ 	lui	$at,0x4000
/*  f0408cc:	8c590000 */ 	lw	$t9,0x0($v0)
/*  f0408d0:	03217025 */ 	or	$t6,$t9,$at
/*  f0408d4:	10000007 */ 	beqz	$zero,.NB0f0408f4
/*  f0408d8:	ac4e0000 */ 	sw	$t6,0x0($v0)
.NB0f0408dc:
/*  f0408dc:	05630006 */ 	bgezl	$t3,.NB0f0408f8
/*  f0408e0:	c7b0015c */ 	lwc1	$f16,0x15c($sp)
/*  f0408e4:	8c620048 */ 	lw	$v0,0x48($v1)
/*  f0408e8:	8c4a0000 */ 	lw	$t2,0x0($v0)
/*  f0408ec:	354f0010 */ 	ori	$t7,$t2,0x10
/*  f0408f0:	ac4f0000 */ 	sw	$t7,0x0($v0)
.NB0f0408f4:
/*  f0408f4:	c7b0015c */ 	lwc1	$f16,0x15c($sp)
.NB0f0408f8:
/*  f0408f8:	8c780048 */ 	lw	$t8,0x48($v1)
/*  f0408fc:	241900f0 */ 	addiu	$t9,$zero,0xf0
/*  f040900:	3c017f1a */ 	lui	$at,0x7f1a
/*  f040904:	e7100010 */ 	swc1	$f16,0x10($t8)
/*  f040908:	8c6c0048 */ 	lw	$t4,0x48($v1)
/*  f04090c:	c7a80160 */ 	lwc1	$f8,0x160($sp)
/*  f040910:	e5880014 */ 	swc1	$f8,0x14($t4)
/*  f040914:	8c6d0048 */ 	lw	$t5,0x48($v1)
/*  f040918:	c7b20164 */ 	lwc1	$f18,0x164($sp)
/*  f04091c:	e5b20018 */ 	swc1	$f18,0x18($t5)
/*  f040920:	8c6e0048 */ 	lw	$t6,0x48($v1)
/*  f040924:	add900b4 */ 	sw	$t9,0xb4($t6)
/*  f040928:	8fab00d4 */ 	lw	$t3,0xd4($sp)
/*  f04092c:	8c6a0048 */ 	lw	$t2,0x48($v1)
/*  f040930:	c56a005c */ 	lwc1	$f10,0x5c($t3)
/*  f040934:	e54a008c */ 	swc1	$f10,0x8c($t2)
/*  f040938:	8faf00d4 */ 	lw	$t7,0xd4($sp)
/*  f04093c:	c424340c */ 	lwc1	$f4,0x340c($at)
/*  f040940:	8c780048 */ 	lw	$t8,0x48($v1)
/*  f040944:	c5e60050 */ 	lwc1	$f6,0x50($t7)
/*  f040948:	46043402 */ 	mul.s	$f16,$f6,$f4
/*  f04094c:	e7100098 */ 	swc1	$f16,0x98($t8)
/*  f040950:	0fc0a08c */ 	jal	chrGetTargetProp
/*  f040954:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040958:	8fac01b8 */ 	lw	$t4,0x1b8($sp)
/*  f04095c:	3c01bf80 */ 	lui	$at,0xbf80
/*  f040960:	00002025 */ 	or	$a0,$zero,$zero
/*  f040964:	8d8d0048 */ 	lw	$t5,0x48($t4)
/*  f040968:	2407ffff */ 	addiu	$a3,$zero,-1
/*  f04096c:	240effff */ 	addiu	$t6,$zero,-1
/*  f040970:	ada200e8 */ 	sw	$v0,0xe8($t5)
/*  f040974:	8fb900d4 */ 	lw	$t9,0xd4($sp)
/*  f040978:	240bffff */ 	addiu	$t3,$zero,-1
/*  f04097c:	87260060 */ 	lh	$a2,0x60($t9)
/*  f040980:	18c00012 */ 	blez	$a2,.NB0f0409cc
/*  f040984:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040988:	8d850014 */ 	lw	$a1,0x14($t4)
/*  f04098c:	44810000 */ 	mtc1	$at,$f0
/*  f040990:	afab002c */ 	sw	$t3,0x2c($sp)
/*  f040994:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f040998:	afa00020 */ 	sw	$zero,0x20($sp)
/*  f04099c:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f0409a0:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f0409a4:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f0409a8:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0409ac:	e7a00024 */ 	swc1	$f0,0x24($sp)
/*  f0409b0:	e7a00030 */ 	swc1	$f0,0x30($sp)
/*  f0409b4:	e7a00034 */ 	swc1	$f0,0x34($sp)
/*  f0409b8:	0fc24762 */ 	jal	func0f0939f8
/*  f0409bc:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*  f0409c0:	10000002 */ 	beqz	$zero,.NB0f0409cc
/*  f0409c4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0409c8:	afa00268 */ 	sw	$zero,0x268($sp)
.NB0f0409cc:
/*  f0409cc:	10000019 */ 	beqz	$zero,.NB0f040a34
/*  f0409d0:	a3a0026e */ 	sb	$zero,0x26e($sp)
/*  f0409d4:	24010006 */ 	addiu	$at,$zero,0x6
.NB0f0409d8:
/*  f0409d8:	14810016 */ 	bne	$a0,$at,.NB0f040a34
/*  f0409dc:	93aa026f */ 	lbu	$t2,0x26f($sp)
/*  f0409e0:	11400014 */ 	beqz	$t2,.NB0f040a34
/*  f0409e4:	93af0263 */ 	lbu	$t7,0x263($sp)
/*  f0409e8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0409ec:	15e10011 */ 	bne	$t7,$at,.NB0f040a34
/*  f0409f0:	8fad0278 */ 	lw	$t5,0x278($sp)
/*  f0409f4:	8fa2027c */ 	lw	$v0,0x27c($sp)
/*  f0409f8:	8db902d4 */ 	lw	$t9,0x2d4($t5)
/*  f0409fc:	3c014120 */ 	lui	$at,0x4120
/*  f040a00:	0002c080 */ 	sll	$t8,$v0,0x2
/*  f040a04:	03386021 */ 	addu	$t4,$t9,$t8
/*  f040a08:	c58800e4 */ 	lwc1	$f8,0xe4($t4)
/*  f040a0c:	44819000 */ 	mtc1	$at,$f18
/*  f040a10:	44802000 */ 	mtc1	$zero,$f4
/*  f040a14:	46124282 */ 	mul.s	$f10,$f8,$f18
/*  f040a18:	4600518d */ 	trunc.w.s	$f6,$f10
/*  f040a1c:	440b3000 */ 	mfc1	$t3,$f6
/*  f040a20:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040a24:	a3ab0262 */ 	sb	$t3,0x262($sp)
/*  f040a28:	8daa02d4 */ 	lw	$t2,0x2d4($t5)
/*  f040a2c:	01587821 */ 	addu	$t7,$t2,$t8
/*  f040a30:	e5e400e4 */ 	swc1	$f4,0xe4($t7)
.NB0f040a34:
/*  f040a34:	93b8026e */ 	lbu	$t8,0x26e($sp)
/*  f040a38:	93b9026f */ 	lbu	$t9,0x26f($sp)
/*  f040a3c:	530001ba */ 	beqzl	$t8,.NB0f041128
/*  f040a40:	8fac01c0 */ 	lw	$t4,0x1c0($sp)
/*  f040a44:	172000d0 */ 	bnez	$t9,.NB0f040d88
/*  f040a48:	8fac0258 */ 	lw	$t4,0x258($sp)
/*  f040a4c:	318e0200 */ 	andi	$t6,$t4,0x200
/*  f040a50:	11c00046 */ 	beqz	$t6,.NB0f040b6c
/*  f040a54:	8fab025c */ 	lw	$t3,0x25c($sp)
/*  f040a58:	916d0000 */ 	lbu	$t5,0x0($t3)
/*  f040a5c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040a60:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040a64:	15a10041 */ 	bne	$t5,$at,.NB0f040b6c
/*  f040a68:	27a50244 */ 	addiu	$a1,$sp,0x244
/*  f040a6c:	27a60234 */ 	addiu	$a2,$sp,0x234
/*  f040a70:	0fc0e2c1 */ 	jal	chrCanSeeAttackTarget
/*  f040a74:	00003825 */ 	or	$a3,$zero,$zero
/*  f040a78:	1040003c */ 	beqz	$v0,.NB0f040b6c
/*  f040a7c:	3c014170 */ 	lui	$at,0x4170
/*  f040a80:	44817000 */ 	mtc1	$at,$f14
/*  f040a84:	8faa025c */ 	lw	$t2,0x25c($sp)
/*  f040a88:	c7aa01e0 */ 	lwc1	$f10,0x1e0($sp)
/*  f040a8c:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f040a90:	c5500008 */ 	lwc1	$f16,0x8($t2)
/*  f040a94:	460e5182 */ 	mul.s	$f6,$f10,$f14
/*  f040a98:	c7aa01e4 */ 	lwc1	$f10,0x1e4($sp)
/*  f040a9c:	46088481 */ 	sub.s	$f18,$f16,$f8
/*  f040aa0:	c7b00248 */ 	lwc1	$f16,0x248($sp)
/*  f040aa4:	c544000c */ 	lwc1	$f4,0xc($t2)
/*  f040aa8:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040aac:	27a501f8 */ 	addiu	$a1,$sp,0x1f8
/*  f040ab0:	46069001 */ 	sub.s	$f0,$f18,$f6
/*  f040ab4:	460e5482 */ 	mul.s	$f18,$f10,$f14
/*  f040ab8:	c7aa01e8 */ 	lwc1	$f10,0x1e8($sp)
/*  f040abc:	46102201 */ 	sub.s	$f8,$f4,$f16
/*  f040ac0:	c7a4024c */ 	lwc1	$f4,0x24c($sp)
/*  f040ac4:	c5460010 */ 	lwc1	$f6,0x10($t2)
/*  f040ac8:	27a601f4 */ 	addiu	$a2,$sp,0x1f4
/*  f040acc:	46124081 */ 	sub.s	$f2,$f8,$f18
/*  f040ad0:	460e5202 */ 	mul.s	$f8,$f10,$f14
/*  f040ad4:	c7b201d0 */ 	lwc1	$f18,0x1d0($sp)
/*  f040ad8:	46043401 */ 	sub.s	$f16,$f6,$f4
/*  f040adc:	46000182 */ 	mul.s	$f6,$f0,$f0
/*  f040ae0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040ae4:	46021102 */ 	mul.s	$f4,$f2,$f2
/*  f040ae8:	46088301 */ 	sub.s	$f12,$f16,$f8
/*  f040aec:	460c6402 */ 	mul.s	$f16,$f12,$f12
/*  f040af0:	46043280 */ 	add.s	$f10,$f6,$f4
/*  f040af4:	46105200 */ 	add.s	$f8,$f10,$f16
/*  f040af8:	4612403e */ 	c.le.s	$f8,$f18
/*  f040afc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040b00:	4500002b */ 	bc1f	.NB0f040bb0
/*  f040b04:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040b08:	0fc0fca9 */ 	jal	chrCalculateHit
/*  f040b0c:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f040b10:	8faf01f4 */ 	lw	$t7,0x1f4($sp)
/*  f040b14:	8fb901f8 */ 	lw	$t9,0x1f8($sp)
/*  f040b18:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f040b1c:	2df80001 */ 	sltiu	$t8,$t7,0x1
/*  f040b20:	13200023 */ 	beqz	$t9,.NB0f040bb0
/*  f040b24:	afb801f0 */ 	sw	$t8,0x1f0($sp)
/*  f040b28:	81830007 */ 	lb	$v1,0x7($t4)
/*  f040b2c:	24010008 */ 	addiu	$at,$zero,0x8
/*  f040b30:	3c0e800a */ 	lui	$t6,0x800a
/*  f040b34:	1061000a */ 	beq	$v1,$at,.NB0f040b60
/*  f040b38:	8fab0278 */ 	lw	$t3,0x278($sp)
/*  f040b3c:	2401000a */ 	addiu	$at,$zero,0xa
/*  f040b40:	10610007 */ 	beq	$v1,$at,.NB0f040b60
/*  f040b44:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f040b48:	10610005 */ 	beq	$v1,$at,.NB0f040b60
/*  f040b4c:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f040b50:	10610003 */ 	beq	$v1,$at,.NB0f040b60
/*  f040b54:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f040b58:	54610016 */ 	bnel	$v1,$at,.NB0f040bb4
/*  f040b5c:	8fb801f4 */ 	lw	$t8,0x1f4($sp)
.NB0f040b60:
/*  f040b60:	8dcee6c8 */ 	lw	$t6,-0x1938($t6)
/*  f040b64:	10000012 */ 	beqz	$zero,.NB0f040bb0
/*  f040b68:	ad6e0048 */ 	sw	$t6,0x48($t3)
.NB0f040b6c:
/*  f040b6c:	8fad0278 */ 	lw	$t5,0x278($sp)
/*  f040b70:	24010008 */ 	addiu	$at,$zero,0x8
/*  f040b74:	3c0a800a */ 	lui	$t2,0x800a
/*  f040b78:	81a30007 */ 	lb	$v1,0x7($t5)
/*  f040b7c:	8faf0278 */ 	lw	$t7,0x278($sp)
/*  f040b80:	10610009 */ 	beq	$v1,$at,.NB0f040ba8
/*  f040b84:	2401000a */ 	addiu	$at,$zero,0xa
/*  f040b88:	10610007 */ 	beq	$v1,$at,.NB0f040ba8
/*  f040b8c:	2401001b */ 	addiu	$at,$zero,0x1b
/*  f040b90:	10610005 */ 	beq	$v1,$at,.NB0f040ba8
/*  f040b94:	2401001c */ 	addiu	$at,$zero,0x1c
/*  f040b98:	10610003 */ 	beq	$v1,$at,.NB0f040ba8
/*  f040b9c:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f040ba0:	54610004 */ 	bnel	$v1,$at,.NB0f040bb4
/*  f040ba4:	8fb801f4 */ 	lw	$t8,0x1f4($sp)
.NB0f040ba8:
/*  f040ba8:	8d4ae6c8 */ 	lw	$t2,-0x1938($t2)
/*  f040bac:	adea0048 */ 	sw	$t2,0x48($t7)
.NB0f040bb0:
/*  f040bb0:	8fb801f4 */ 	lw	$t8,0x1f4($sp)
.NB0f040bb4:
/*  f040bb4:	8fad01cc */ 	lw	$t5,0x1cc($sp)
/*  f040bb8:	13000065 */ 	beqz	$t8,.NB0f040d50
/*  f040bbc:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040bc0:	0fc2bea2 */ 	jal	gsetGetDamage
/*  f040bc4:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f040bc8:	8fae025c */ 	lw	$t6,0x25c($sp)
/*  f040bcc:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f040bd0:	240c00c8 */ 	addiu	$t4,$zero,0xc8
/*  f040bd4:	e7a0009c */ 	swc1	$f0,0x9c($sp)
/*  f040bd8:	afa00098 */ 	sw	$zero,0x98($sp)
/*  f040bdc:	afa00094 */ 	sw	$zero,0x94($sp)
/*  f040be0:	afb90090 */ 	sw	$t9,0x90($sp)
/*  f040be4:	afac008c */ 	sw	$t4,0x8c($sp)
/*  f040be8:	8dcb0004 */ 	lw	$t3,0x4($t6)
/*  f040bec:	afab0088 */ 	sw	$t3,0x88($sp)
/*  f040bf0:	c5c60008 */ 	lwc1	$f6,0x8($t6)
/*  f040bf4:	e7a60228 */ 	swc1	$f6,0x228($sp)
/*  f040bf8:	c5c4000c */ 	lwc1	$f4,0xc($t6)
/*  f040bfc:	e7a4022c */ 	swc1	$f4,0x22c($sp)
/*  f040c00:	c5ca0010 */ 	lwc1	$f10,0x10($t6)
/*  f040c04:	0c004d84 */ 	jal	random
/*  f040c08:	e7aa0230 */ 	swc1	$f10,0x230($sp)
/*  f040c0c:	304d0001 */ 	andi	$t5,$v0,0x1
/*  f040c10:	11a00012 */ 	beqz	$t5,.NB0f040c5c
/*  f040c14:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040c18:	0c004d84 */ 	jal	random
/*  f040c1c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040c20:	2401000a */ 	addiu	$at,$zero,0xa
/*  f040c24:	0041001b */ 	divu	$zero,$v0,$at
/*  f040c28:	00005010 */ 	mfhi	$t2
/*  f040c2c:	254f0002 */ 	addiu	$t7,$t2,0x2
/*  f040c30:	448f9000 */ 	mtc1	$t7,$f18
/*  f040c34:	c7b0022c */ 	lwc1	$f16,0x22c($sp)
/*  f040c38:	05e10005 */ 	bgez	$t7,.NB0f040c50
/*  f040c3c:	46809220 */ 	cvt.s.w	$f8,$f18
/*  f040c40:	3c014f80 */ 	lui	$at,0x4f80
/*  f040c44:	44813000 */ 	mtc1	$at,$f6
/*  f040c48:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040c4c:	46064200 */ 	add.s	$f8,$f8,$f6
.NB0f040c50:
/*  f040c50:	46088100 */ 	add.s	$f4,$f16,$f8
/*  f040c54:	10000011 */ 	beqz	$zero,.NB0f040c9c
/*  f040c58:	e7a4022c */ 	swc1	$f4,0x22c($sp)
.NB0f040c5c:
/*  f040c5c:	0c004d84 */ 	jal	random
/*  f040c60:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040c64:	2401000a */ 	addiu	$at,$zero,0xa
/*  f040c68:	0041001b */ 	divu	$zero,$v0,$at
/*  f040c6c:	0000c010 */ 	mfhi	$t8
/*  f040c70:	27190002 */ 	addiu	$t9,$t8,0x2
/*  f040c74:	44999000 */ 	mtc1	$t9,$f18
/*  f040c78:	c7aa022c */ 	lwc1	$f10,0x22c($sp)
/*  f040c7c:	07210005 */ 	bgez	$t9,.NB0f040c94
/*  f040c80:	468091a0 */ 	cvt.s.w	$f6,$f18
/*  f040c84:	3c014f80 */ 	lui	$at,0x4f80
/*  f040c88:	44818000 */ 	mtc1	$at,$f16
/*  f040c8c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040c90:	46103180 */ 	add.s	$f6,$f6,$f16
.NB0f040c94:
/*  f040c94:	46065201 */ 	sub.s	$f8,$f10,$f6
/*  f040c98:	e7a8022c */ 	swc1	$f8,0x22c($sp)
.NB0f040c9c:
/*  f040c9c:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f040ca0:	8fa5025c */ 	lw	$a1,0x25c($sp)
/*  f040ca4:	0fc296b1 */ 	jal	bgunPlayPropHitSound
/*  f040ca8:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f040cac:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f040cb0:	8c8c0020 */ 	lw	$t4,0x20($a0)
/*  f040cb4:	51800012 */ 	beqzl	$t4,.NB0f040d00
/*  f040cb8:	8faa0278 */ 	lw	$t2,0x278($sp)
/*  f040cbc:	0fc0ce2a */ 	jal	chrGetShield
/*  f040cc0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040cc4:	44802000 */ 	mtc1	$zero,$f4
/*  f040cc8:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f040ccc:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f040cd0:	4600203c */ 	c.lt.s	$f4,$f0
/*  f040cd4:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f040cd8:	27a70098 */ 	addiu	$a3,$sp,0x98
/*  f040cdc:	27ab008c */ 	addiu	$t3,$sp,0x8c
/*  f040ce0:	45000006 */ 	bc1f	.NB0f040cfc
/*  f040ce4:	27ae0094 */ 	addiu	$t6,$sp,0x94
/*  f040ce8:	27ad0090 */ 	addiu	$t5,$sp,0x90
/*  f040cec:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f040cf0:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f040cf4:	0fc0fdc8 */ 	jal	chrCalculateShieldHit
/*  f040cf8:	afae0014 */ 	sw	$t6,0x14($sp)
.NB0f040cfc:
/*  f040cfc:	8faa0278 */ 	lw	$t2,0x278($sp)
.NB0f040d00:
/*  f040d00:	8fb9025c */ 	lw	$t9,0x25c($sp)
/*  f040d04:	8fac0098 */ 	lw	$t4,0x98($sp)
/*  f040d08:	8d4f001c */ 	lw	$t7,0x1c($t2)
/*  f040d0c:	8fab0094 */ 	lw	$t3,0x94($sp)
/*  f040d10:	8fae0090 */ 	lw	$t6,0x90($sp)
/*  f040d14:	241800c8 */ 	addiu	$t8,$zero,0xc8
/*  f040d18:	8fa40088 */ 	lw	$a0,0x88($sp)
/*  f040d1c:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f040d20:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f040d24:	8fa5009c */ 	lw	$a1,0x9c($sp)
/*  f040d28:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f040d2c:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f040d30:	afb90018 */ 	sw	$t9,0x18($sp)
/*  f040d34:	afac001c */ 	sw	$t4,0x1c($sp)
/*  f040d38:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f040d3c:	afab0020 */ 	sw	$t3,0x20($sp)
/*  f040d40:	0fc0ceb9 */ 	jal	func0f0341dc
/*  f040d44:	afae0024 */ 	sw	$t6,0x24($sp)
/*  f040d48:	10000010 */ 	beqz	$zero,.NB0f040d8c
/*  f040d4c:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
.NB0f040d50:
/*  f040d50:	11a00006 */ 	beqz	$t5,.NB0f040d6c
/*  f040d54:	c7b201d0 */ 	lwc1	$f18,0x1d0($sp)
/*  f040d58:	91a20000 */ 	lbu	$v0,0x0($t5)
/*  f040d5c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f040d60:	10410009 */ 	beq	$v0,$at,.NB0f040d88
/*  f040d64:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040d68:	10410007 */ 	beq	$v0,$at,.NB0f040d88
.NB0f040d6c:
/*  f040d6c:	3c017f1a */ 	lui	$at,0x7f1a
/*  f040d70:	c4303410 */ 	lwc1	$f16,0x3410($at)
/*  f040d74:	4610903c */ 	c.lt.s	$f18,$f16
/*  f040d78:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040d7c:	45020003 */ 	bc1fl	.NB0f040d8c
/*  f040d80:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
/*  f040d84:	afa001f0 */ 	sw	$zero,0x1f0($sp)
.NB0f040d88:
/*  f040d88:	8faa01f0 */ 	lw	$t2,0x1f0($sp)
.NB0f040d8c:
/*  f040d8c:	8faf01cc */ 	lw	$t7,0x1cc($sp)
/*  f040d90:	514000e5 */ 	beqzl	$t2,.NB0f041128
/*  f040d94:	8fac01c0 */ 	lw	$t4,0x1c0($sp)
/*  f040d98:	11e000a2 */ 	beqz	$t7,.NB0f041024
/*  f040d9c:	8fac0224 */ 	lw	$t4,0x224($sp)
/*  f040da0:	91e20000 */ 	lbu	$v0,0x0($t7)
/*  f040da4:	24010006 */ 	addiu	$at,$zero,0x6
/*  f040da8:	93b8026f */ 	lbu	$t8,0x26f($sp)
/*  f040dac:	10410003 */ 	beq	$v0,$at,.NB0f040dbc
/*  f040db0:	24010003 */ 	addiu	$at,$zero,0x3
/*  f040db4:	54410053 */ 	bnel	$v0,$at,.NB0f040f04
/*  f040db8:	24010001 */ 	addiu	$at,$zero,0x1
.NB0f040dbc:
/*  f040dbc:	1700000c */ 	bnez	$t8,.NB0f040df0
/*  f040dc0:	8fb901bc */ 	lw	$t9,0x1bc($sp)
/*  f040dc4:	1720000a */ 	bnez	$t9,.NB0f040df0
/*  f040dc8:	8fac0278 */ 	lw	$t4,0x278($sp)
/*  f040dcc:	8d8b0018 */ 	lw	$t3,0x18($t4)
/*  f040dd0:	8fad01cc */ 	lw	$t5,0x1cc($sp)
/*  f040dd4:	01802825 */ 	or	$a1,$t4,$zero
/*  f040dd8:	316e0040 */ 	andi	$t6,$t3,0x40
/*  f040ddc:	11c00045 */ 	beqz	$t6,.NB0f040ef4
/*  f040de0:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f040de4:	0fc1279f */ 	jal	chrCompareTeams
/*  f040de8:	8da40004 */ 	lw	$a0,0x4($t5)
/*  f040dec:	10400041 */ 	beqz	$v0,.NB0f040ef4
.NB0f040df0:
/*  f040df0:	240affff */ 	addiu	$t2,$zero,-1
/*  f040df4:	240f00c8 */ 	addiu	$t7,$zero,0xc8
/*  f040df8:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f040dfc:	afa00080 */ 	sw	$zero,0x80($sp)
/*  f040e00:	afaa007c */ 	sw	$t2,0x7c($sp)
/*  f040e04:	afaf0078 */ 	sw	$t7,0x78($sp)
/*  f040e08:	0fc2bea2 */ 	jal	gsetGetDamage
/*  f040e0c:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f040e10:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f040e14:	e7a00074 */ 	swc1	$f0,0x74($sp)
/*  f040e18:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f040e1c:	8cb90004 */ 	lw	$t9,0x4($a1)
/*  f040e20:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f040e24:	0fc296b1 */ 	jal	bgunPlayPropHitSound
/*  f040e28:	afb90070 */ 	sw	$t9,0x70($sp)
/*  f040e2c:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f040e30:	8c8b0020 */ 	lw	$t3,0x20($a0)
/*  f040e34:	51600012 */ 	beqzl	$t3,.NB0f040e80
/*  f040e38:	8faf0278 */ 	lw	$t7,0x278($sp)
/*  f040e3c:	0fc0ce2a */ 	jal	chrGetShield
/*  f040e40:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040e44:	44805000 */ 	mtc1	$zero,$f10
/*  f040e48:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f040e4c:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f040e50:	4600503c */ 	c.lt.s	$f10,$f0
/*  f040e54:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f040e58:	27a70084 */ 	addiu	$a3,$sp,0x84
/*  f040e5c:	27ae0078 */ 	addiu	$t6,$sp,0x78
/*  f040e60:	45000006 */ 	bc1f	.NB0f040e7c
/*  f040e64:	27ad0080 */ 	addiu	$t5,$sp,0x80
/*  f040e68:	27ac007c */ 	addiu	$t4,$sp,0x7c
/*  f040e6c:	afac0018 */ 	sw	$t4,0x18($sp)
/*  f040e70:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f040e74:	0fc0fdc8 */ 	jal	chrCalculateShieldHit
/*  f040e78:	afad0014 */ 	sw	$t5,0x14($sp)
.NB0f040e7c:
/*  f040e7c:	8faf0278 */ 	lw	$t7,0x278($sp)
.NB0f040e80:
/*  f040e80:	27aa01e0 */ 	addiu	$t2,$sp,0x1e0
/*  f040e84:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f040e88:	afaa0010 */ 	sw	$t2,0x10($sp)
/*  f040e8c:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f040e90:	8fa60078 */ 	lw	$a2,0x78($sp)
/*  f040e94:	27a70228 */ 	addiu	$a3,$sp,0x228
/*  f040e98:	0fc09630 */ 	jal	chrEmitSparks
/*  f040e9c:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f040ea0:	8fb90278 */ 	lw	$t9,0x278($sp)
/*  f040ea4:	8fae01cc */ 	lw	$t6,0x1cc($sp)
/*  f040ea8:	8fad0084 */ 	lw	$t5,0x84($sp)
/*  f040eac:	8f38001c */ 	lw	$t8,0x1c($t9)
/*  f040eb0:	8fac0080 */ 	lw	$t4,0x80($sp)
/*  f040eb4:	8faa007c */ 	lw	$t2,0x7c($sp)
/*  f040eb8:	240b00c8 */ 	addiu	$t3,$zero,0xc8
/*  f040ebc:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f040ec0:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f040ec4:	8fa40070 */ 	lw	$a0,0x70($sp)
/*  f040ec8:	8fa50074 */ 	lw	$a1,0x74($sp)
/*  f040ecc:	27a601e0 */ 	addiu	$a2,$sp,0x1e0
/*  f040ed0:	27a70260 */ 	addiu	$a3,$sp,0x260
/*  f040ed4:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f040ed8:	afad001c */ 	sw	$t5,0x1c($sp)
/*  f040edc:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f040ee0:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f040ee4:	0fc0ceb9 */ 	jal	func0f0341dc
/*  f040ee8:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f040eec:	1000006f */ 	beqz	$zero,.NB0f0410ac
/*  f040ef0:	93b90260 */ 	lbu	$t9,0x260($sp)
.NB0f040ef4:
/*  f040ef4:	afa00250 */ 	sw	$zero,0x250($sp)
/*  f040ef8:	1000006b */ 	beqz	$zero,.NB0f0410a8
/*  f040efc:	afa00268 */ 	sw	$zero,0x268($sp)
/*  f040f00:	24010001 */ 	addiu	$at,$zero,0x1
.NB0f040f04:
/*  f040f04:	10410005 */ 	beq	$v0,$at,.NB0f040f1c
/*  f040f08:	8faf01cc */ 	lw	$t7,0x1cc($sp)
/*  f040f0c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f040f10:	10410002 */ 	beq	$v0,$at,.NB0f040f1c
/*  f040f14:	24010002 */ 	addiu	$at,$zero,0x2
/*  f040f18:	14410063 */ 	bne	$v0,$at,.NB0f0410a8
.NB0f040f1c:
/*  f040f1c:	3c0b800a */ 	lui	$t3,0x800a
/*  f040f20:	8d6be9d4 */ 	lw	$t3,-0x162c($t3)
/*  f040f24:	8df90004 */ 	lw	$t9,0x4($t7)
/*  f040f28:	2418ffff */ 	addiu	$t8,$zero,-1
/*  f040f2c:	afb80068 */ 	sw	$t8,0x68($sp)
/*  f040f30:	11600004 */ 	beqz	$t3,.NB0f040f44
/*  f040f34:	afb9006c */ 	sw	$t9,0x6c($sp)
/*  f040f38:	0fc61c7f */ 	jal	mpPlayerGetIndex
/*  f040f3c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040f40:	afa20068 */ 	sw	$v0,0x68($sp)
.NB0f040f44:
/*  f040f44:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f040f48:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f040f4c:	0fc296b1 */ 	jal	bgunPlayPropHitSound
/*  f040f50:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f040f54:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f040f58:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f040f5c:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f040f60:	0fc19437 */ 	jal	func0f065e74
/*  f040f64:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f040f68:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f040f6c:	afae0210 */ 	sw	$t6,0x210($sp)
/*  f040f70:	0fc4e3ea */ 	jal	chrIsUsingPaintball
/*  f040f74:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f040f78:	1040000b */ 	beqz	$v0,.NB0f040fa8
/*  f040f7c:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f040f80:	240d0019 */ 	addiu	$t5,$zero,0x19
/*  f040f84:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f040f88:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f040f8c:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f040f90:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f040f94:	00003825 */ 	or	$a3,$zero,$zero
/*  f040f98:	0fc4a960 */ 	jal	sparksCreate
/*  f040f9c:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f040fa0:	10000007 */ 	beqz	$zero,.NB0f040fc0
/*  f040fa4:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f040fa8:
/*  f040fa8:	8fa501cc */ 	lw	$a1,0x1cc($sp)
/*  f040fac:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f040fb0:	00003825 */ 	or	$a3,$zero,$zero
/*  f040fb4:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f040fb8:	0fc4a960 */ 	jal	sparksCreate
/*  f040fbc:	afa00014 */ 	sw	$zero,0x14($sp)
.NB0f040fc0:
/*  f040fc0:	3c0c800a */ 	lui	$t4,0x800a
/*  f040fc4:	818a27ab */ 	lb	$t2,0x27ab($t4)
/*  f040fc8:	8faf0278 */ 	lw	$t7,0x278($sp)
/*  f040fcc:	0541000a */ 	bgez	$t2,.NB0f040ff8
/*  f040fd0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040fd4:	91f90125 */ 	lbu	$t9,0x125($t7)
/*  f040fd8:	24010010 */ 	addiu	$at,$zero,0x10
/*  f040fdc:	8fb8006c */ 	lw	$t8,0x6c($sp)
/*  f040fe0:	17210005 */ 	bne	$t9,$at,.NB0f040ff8
/*  f040fe4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f040fe8:	8f0b000c */ 	lw	$t3,0xc($t8)
/*  f040fec:	316e0001 */ 	andi	$t6,$t3,0x1
/*  f040ff0:	55c0002e */ 	bnezl	$t6,.NB0f0410ac
/*  f040ff4:	93b90260 */ 	lbu	$t9,0x260($sp)
.NB0f040ff8:
/*  f040ff8:	0fc2bea2 */ 	jal	gsetGetDamage
/*  f040ffc:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041000:	8fad0068 */ 	lw	$t5,0x68($sp)
/*  f041004:	44050000 */ 	mfc1	$a1,$f0
/*  f041008:	8fa4006c */ 	lw	$a0,0x6c($sp)
/*  f04100c:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041010:	93a70260 */ 	lbu	$a3,0x260($sp)
/*  f041014:	0fc20ebd */ 	jal	objTakeGunfire
/*  f041018:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f04101c:	10000023 */ 	beqz	$zero,.NB0f0410ac
/*  f041020:	93b90260 */ 	lbu	$t9,0x260($sp)
.NB0f041024:
/*  f041024:	11800020 */ 	beqz	$t4,.NB0f0410a8
/*  f041028:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f04102c:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f041030:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041034:	0fc19437 */ 	jal	func0f065e74
/*  f041038:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f04103c:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f041040:	afaa0210 */ 	sw	$t2,0x210($sp)
/*  f041044:	27a40260 */ 	addiu	$a0,$sp,0x260
/*  f041048:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f04104c:	2406ffff */ 	addiu	$a2,$zero,-1
/*  f041050:	0fc298a8 */ 	jal	bgunPlayBgHitSound
/*  f041054:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041058:	0fc4e3ea */ 	jal	chrIsUsingPaintball
/*  f04105c:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041060:	1040000b */ 	beqz	$v0,.NB0f041090
/*  f041064:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f041068:	240f0019 */ 	addiu	$t7,$zero,0x19
/*  f04106c:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f041070:	87a40214 */ 	lh	$a0,0x214($sp)
/*  f041074:	00002825 */ 	or	$a1,$zero,$zero
/*  f041078:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f04107c:	00003825 */ 	or	$a3,$zero,$zero
/*  f041080:	0fc4a960 */ 	jal	sparksCreate
/*  f041084:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f041088:	10000008 */ 	beqz	$zero,.NB0f0410ac
/*  f04108c:	93b90260 */ 	lbu	$t9,0x260($sp)
.NB0f041090:
/*  f041090:	00002825 */ 	or	$a1,$zero,$zero
/*  f041094:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f041098:	00003825 */ 	or	$a3,$zero,$zero
/*  f04109c:	afa00010 */ 	sw	$zero,0x10($sp)
/*  f0410a0:	0fc4a960 */ 	jal	sparksCreate
/*  f0410a4:	afa00014 */ 	sw	$zero,0x14($sp)
.NB0f0410a8:
/*  f0410a8:	93b90260 */ 	lbu	$t9,0x260($sp)
.NB0f0410ac:
/*  f0410ac:	24010007 */ 	addiu	$at,$zero,0x7
/*  f0410b0:	93b80263 */ 	lbu	$t8,0x263($sp)
/*  f0410b4:	1721001b */ 	bne	$t9,$at,.NB0f041124
/*  f0410b8:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0410bc:	17010019 */ 	bne	$t8,$at,.NB0f041124
/*  f0410c0:	8fab0278 */ 	lw	$t3,0x278($sp)
/*  f0410c4:	8d6e02d4 */ 	lw	$t6,0x2d4($t3)
/*  f0410c8:	3c03800a */ 	lui	$v1,0x800a
/*  f0410cc:	11c00005 */ 	beqz	$t6,.NB0f0410e4
/*  f0410d0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f0410d4:	0fc61c7f */ 	jal	mpPlayerGetIndex
/*  f0410d8:	01602025 */ 	or	$a0,$t3,$zero
/*  f0410dc:	10000002 */ 	beqz	$zero,.NB0f0410e8
/*  f0410e0:	00401825 */ 	or	$v1,$v0,$zero
.NB0f0410e4:
/*  f0410e4:	8c63e94c */ 	lw	$v1,-0x16b4($v1)
.NB0f0410e8:
/*  f0410e8:	8fad0210 */ 	lw	$t5,0x210($sp)
/*  f0410ec:	27a40244 */ 	addiu	$a0,$sp,0x244
/*  f0410f0:	27a50234 */ 	addiu	$a1,$sp,0x234
/*  f0410f4:	15a00005 */ 	bnez	$t5,.NB0f04110c
/*  f0410f8:	27a60228 */ 	addiu	$a2,$sp,0x228
/*  f0410fc:	27a70214 */ 	addiu	$a3,$sp,0x214
/*  f041100:	0fc19437 */ 	jal	func0f065e74
/*  f041104:	afa30064 */ 	sw	$v1,0x64($sp)
/*  f041108:	8fa30064 */ 	lw	$v1,0x64($sp)
.NB0f04110c:
/*  f04110c:	00002025 */ 	or	$a0,$zero,$zero
/*  f041110:	27a50228 */ 	addiu	$a1,$sp,0x228
/*  f041114:	27a60214 */ 	addiu	$a2,$sp,0x214
/*  f041118:	24070016 */ 	addiu	$a3,$zero,0x16
/*  f04111c:	0fc49158 */ 	jal	explosionCreateSimple
/*  f041120:	afa30010 */ 	sw	$v1,0x10($sp)
.NB0f041124:
/*  f041124:	8fac01c0 */ 	lw	$t4,0x1c0($sp)
.NB0f041128:
/*  f041128:	8fa4025c */ 	lw	$a0,0x25c($sp)
/*  f04112c:	51800004 */ 	beqzl	$t4,.NB0f041140
/*  f041130:	8fa80268 */ 	lw	$t0,0x268($sp)
/*  f041134:	0fc18cfb */ 	jal	propSetPerimEnabled
/*  f041138:	00002825 */ 	or	$a1,$zero,$zero
/*  f04113c:	8fa80268 */ 	lw	$t0,0x268($sp)
.NB0f041140:
/*  f041140:	8faf0250 */ 	lw	$t7,0x250($sp)
/*  f041144:	93b90260 */ 	lbu	$t9,0x260($sp)
/*  f041148:	0008502b */ 	sltu	$t2,$zero,$t0
/*  f04114c:	11e0000e */ 	beqz	$t7,.NB0f041188
/*  f041150:	01404025 */ 	or	$t0,$t2,$zero
/*  f041154:	2738fffe */ 	addiu	$t8,$t9,-2
/*  f041158:	2f01002a */ 	sltiu	$at,$t8,0x2a
/*  f04115c:	10200009 */ 	beqz	$at,.NB0f041184
/*  f041160:	0018c080 */ 	sll	$t8,$t8,0x2
/*  f041164:	3c017f1a */ 	lui	$at,0x7f1a
/*  f041168:	00380821 */ 	addu	$at,$at,$t8
/*  f04116c:	8c383414 */ 	lw	$t8,0x3414($at)
/*  f041170:	03000008 */ 	jr	$t8
/*  f041174:	00000000 */ 	sll	$zero,$zero,0x0
/*  f041178:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f04117c:	10000002 */ 	beqz	$zero,.NB0f041188
/*  f041180:	afae0250 */ 	sw	$t6,0x250($sp)
.NB0f041184:
/*  f041184:	afa00250 */ 	sw	$zero,0x250($sp)
.NB0f041188:
/*  f041188:	11000004 */ 	beqz	$t0,.NB0f04119c
/*  f04118c:	01003825 */ 	or	$a3,$t0,$zero
/*  f041190:	8fa70250 */ 	lw	$a3,0x250($sp)
/*  f041194:	0007582b */ 	sltu	$t3,$zero,$a3
/*  f041198:	01603825 */ 	or	$a3,$t3,$zero
.NB0f04119c:
/*  f04119c:	27ad0244 */ 	addiu	$t5,$sp,0x244
/*  f0411a0:	27ac0228 */ 	addiu	$t4,$sp,0x228
/*  f0411a4:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f0411a8:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f0411ac:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0411b0:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f0411b4:	8fa60268 */ 	lw	$a2,0x268($sp)
/*  f0411b8:	0fc0f6a6 */ 	jal	chrCreateFireslot
/*  f0411bc:	afa80054 */ 	sw	$t0,0x54($sp)
/*  f0411c0:	93aa026f */ 	lbu	$t2,0x26f($sp)
/*  f0411c4:	8fa80054 */ 	lw	$t0,0x54($sp)
/*  f0411c8:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f0411cc:	11400015 */ 	beqz	$t2,.NB0f041224
/*  f0411d0:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f0411d4:	1100000a */ 	beqz	$t0,.NB0f041200
/*  f0411d8:	01003025 */ 	or	$a2,$t0,$zero
/*  f0411dc:	8faf0278 */ 	lw	$t7,0x278($sp)
/*  f0411e0:	8fb8027c */ 	lw	$t8,0x27c($sp)
/*  f0411e4:	8df902d4 */ 	lw	$t9,0x2d4($t7)
/*  f0411e8:	00187080 */ 	sll	$t6,$t8,0x2
/*  f0411ec:	032e1021 */ 	addu	$v0,$t9,$t6
/*  f0411f0:	8c430024 */ 	lw	$v1,0x24($v0)
/*  f0411f4:	18600002 */ 	blez	$v1,.NB0f041200
/*  f0411f8:	246bffff */ 	addiu	$t3,$v1,-1
/*  f0411fc:	ac4b0024 */ 	sw	$t3,0x24($v0)
.NB0f041200:
/*  f041200:	11000004 */ 	beqz	$t0,.NB0f041214
/*  f041204:	8fa40278 */ 	lw	$a0,0x278($sp)
/*  f041208:	93a6026e */ 	lbu	$a2,0x26e($sp)
/*  f04120c:	0006682b */ 	sltu	$t5,$zero,$a2
/*  f041210:	01a03025 */ 	or	$a2,$t5,$zero
.NB0f041214:
/*  f041214:	0fc0fc0f */ 	jal	chrSetFiring
/*  f041218:	8fa5027c */ 	lw	$a1,0x27c($sp)
/*  f04121c:	10000004 */ 	beqz	$zero,.NB0f041230
/*  f041220:	8fbf0044 */ 	lw	$ra,0x44($sp)
.NB0f041224:
/*  f041224:	0fc0fc0f */ 	jal	chrSetFiring
/*  f041228:	8fa60268 */ 	lw	$a2,0x268($sp)
/*  f04122c:	8fbf0044 */ 	lw	$ra,0x44($sp)
.NB0f041230:
/*  f041230:	27bd0278 */ 	addiu	$sp,$sp,0x278
/*  f041234:	03e00008 */ 	jr	$ra
/*  f041238:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

void func0f041a74(struct chrdata *chr)
{
#if VERSION >= VERSION_NTSC_1_0
	chr->hidden2 &= ~CHRH2FLAG_0020;
#else
	chr->hidden &= ~CHRHFLAG_00000080;
#endif

	if (chr->actiontype == ACT_ROBOTATTACK) {
		if (chr->act_robotattack.firing[0]) {
			chr->prop->forcetick = true;
			projectileCreate(chr->prop, chr->unk348[0], &chr->act_robotattack.pos[0],
					&chr->act_robotattack.dir[0], chr->act_robotattack.guntype[0], chrGetTargetProp(chr));
			chr->unk348[1]->unk08 = g_Vars.lvframe60 + 2;
			chr->unk348[1]->unk14 = chr->unk348[0]->unk14;
		} else {
			chr->prop->forcetick = false;
		}

		if (chr->act_robotattack.firing[1]) {
			chr->prop->forcetick = true;
			projectileCreate(chr->prop, chr->unk348[1], &chr->act_robotattack.pos[1],
					&chr->act_robotattack.dir[1], chr->act_robotattack.guntype[1], chrGetTargetProp(chr));
			chr->unk348[0]->unk14 = chr->unk348[1]->unk14;
		} else {
			chr->prop->forcetick = false;
		}

		beamTick(chr->unk348[0]->beam);
		beamTick(chr->unk348[1]->beam);
	} else if (chr->actiontype == ACT_ATTACKAMOUNT) {
		if (chr->act_attack.numshots < chr->act_attack.maxshots
				&& (chr->hidden & CHRHFLAG_FIRINGRIGHT)) {
			func0f0404d4(chr, 0);
		}
	} else {
		if (chr->hidden & CHRHFLAG_FIRINGRIGHT) {
			func0f0404d4(chr, 0);
			chr->hidden &= ~CHRHFLAG_FIRINGRIGHT;
		}

		if (chr->hidden & CHRHFLAG_FIRINGLEFT) {
			func0f0404d4(chr, 1);
			chr->hidden &= ~CHRHFLAG_FIRINGLEFT;
		}
	}
}

bool func0f041c44(struct chrdata *chr)
{
	if (CHRRACE(chr) == RACE_HUMAN) {
		if (chr->act_attack.animcfg == &g_RollAttackAnims[2] || chr->act_attack.animcfg == &g_RollAttackAnims[3]) {
			struct model *model = chr->model;
			struct attackanimconfig *animcfg = &g_RollAttackAnims[1];
			bool flip = model->anim->flip;

			chr->act_attack.turning = TURNSTATE_OFF;
			chr->act_attack.animcfg = animcfg;
			chr->sleep = 0;

			modelSetAnimation(model, animcfg->animnum, flip, animcfg->unk1c, chrGetRangedSpeed(chr, 0.7f, 1.12f), 22);

			if (animcfg->unk14 >= 0) {
				modelSetAnimEndFrame(model, animcfg->unk14);
			}

			return true;
		}
	}

	return false;
}

void chrAttackAmountUpdateAnimation(struct chrdata *chr)
{
	struct model *model = chr->model;

	if (chr->act_attack.animcfg->unk24 > 0) {
		modelSetAnimation(model,
				modelGetAnimNum(model),
				model->anim->flip,
				chr->act_attack.animcfg->unk24,
				chrGetRangedSpeed(chr, 0.5f, 0.8f),
				8);
	} else {
		modelSetAnimation(model,
				modelGetAnimNum(model),
				model->anim->flip,
				chr->act_attack.animcfg->unk1c,
				chrGetRangedSpeed(chr, 0.5f, 0.8f),
				8);
	}

	if (chr->act_attack.animcfg->unk14 >= 0) {
		modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk14);
	}
}

void chrTickFire(struct chrdata *chr)
{
	struct model *model = chr->model;
	f32 curframe = modelGetCurAnimFrame(model);
	s32 i;

	if (modelGetAnimNum(model) == ANIM_SNIPING_GETDOWN) {
		return;
	}

	if (chr->act_attack.lastontarget60 < chr->act_attack.lastfire60 - PALDOWN(30)
			&& model->anim->animnum2 == 0
			&& curframe > chr->act_attack.animcfg->unk18 + 10
			&& curframe < chr->act_attack.animcfg->unk1c
			&& (chr->act_attack.animcfg->unk24 < 0 || curframe < chr->act_attack.animcfg->unk24)) {
		if (!chr->act_attack.dorecoil) {
			if (!func0f041c44(chr)) {
				modelSetAnimation(model, modelGetAnimNum(model), model->anim->flip,
						chr->act_attack.animcfg->unk1c, chrGetRangedSpeed(chr, 0.5f, 0.8f), 8);

				if (chr->act_attack.animcfg->unk14 >= 0) {
					modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk14);
				}
			}
		} else {
			chrAttackAmountUpdateAnimation(chr);
		}

		chr->act_attack.numshots = chr->act_attack.maxshots + 1;

		curframe = modelGetCurAnimFrame(model);
	}

	if (curframe >= modelGetAnimEndFrame(model)) {
		if (modelGetAnimNum(model) != ANIM_SNIPING_ONGROUND
				&& (chr->act_attack.dooneburst || chr->act_attack.numshots > chr->act_attack.maxshots)) {
			if (!func0f041c44(chr)) {
				if (chr->act_attack.flags & ATTACKFLAG_AIMATTARGET) {
					chrRecordLastSeeTargetTime(chr);
				}

				chrStop(chr);
				return;
			}
		} else if (chr->act_attack.numshots == chr->act_attack.maxshots) {
			chr->act_attack.numshots++;
			chrAttackAmountUpdateAnimation(chr);
		} else if (chr->act_attack.fired) {
			f32 f2 = 0.5f;
			f32 startframe;
			f32 endframe;
			f32 diff;

			if (chr->act_attack.dorecoil) {
				if (chr->act_attack.animcfg->unk20 > 0) {
					startframe = chr->act_attack.animcfg->unk20;
				} else {
					startframe = chr->act_attack.animcfg->unk18;
				}

				if (chr->act_attack.animcfg->unk24 > 0) {
					endframe = chr->act_attack.animcfg->unk24;
				} else {
					endframe = chr->act_attack.animcfg->unk1c;
				}
			} else {
				startframe = chr->act_attack.animcfg->unk18;

				if (chr->act_attack.animcfg->unk20 > 0) {
					endframe = chr->act_attack.animcfg->unk20;
				} else {
					endframe = chr->act_attack.animcfg->unk1c;
				}
			}

			diff = endframe - startframe;

			if (diff < 12) {
				f2 = diff * (1.0f / 24.0f);
			} else if (diff > 16) {
				f2 = diff * (1.0f / 32.0f);
			}

			if (chr->act_attack.everytick[HAND_RIGHT] && chr->act_attack.everytick[HAND_LEFT]) {
				f2 = f2 + f2;
			}

			chr->act_attack.fired = false;

			modelSetAnimation(model, modelGetAnimNum(model), model->anim->flip, startframe, f2, 8);
			modelSetAnimEndFrame(model, endframe);
		}

		curframe = modelGetCurAnimFrame(model);
	}

	if (modelGetAnimNum(model) != ANIM_SNIPING_ONGROUND && (chr->act_attack.flags & ATTACKFLAG_DONTTURN) == 0) {
		f32 f2 = chr->act_attack.animcfg->unk0c;
		f32 f12 = chr->act_attack.animcfg->unk04;

		if ((chr->act_attack.flags & ATTACKFLAG_AIMONLY) && f12 > modelGetAnimEndFrame(model)) {
			f12 = modelGetAnimEndFrame(model);
		}

		if (model->anim->flip) {
			f2 = M_BADTAU - f2;
		}

		chr->act_attack.turning = chrTurn(chr, chr->act_attack.turning, f12, chrGetRangedSpeed(chr, 1, 1.6f), f2);
	}

	if ((curframe > chr->act_attack.animcfg->unk28 && curframe < chr->act_attack.animcfg->unk2c)
			|| modelGetAnimNum(model) == ANIM_SNIPING_ONGROUND) {
		func0f03e9f4(chr, chr->act_attack.animcfg, chr->act_attack.firegun[HAND_LEFT], chr->act_attack.firegun[HAND_RIGHT], 1);
	} else {
		chrResetAimEndProperties(chr);
	}

	for (i = 0; i < 2; i++) {
		if (chr->act_attack.firegun[i]) {
			if (chr->act_attack.everytick[i] == 0) {
				if (modelGetAnimNum(model) == ANIM_SNIPING_ONGROUND
						|| (curframe >= chr->act_attack.animcfg->unk18 && curframe < chr->act_attack.animcfg->unk1c)) {
					chrSetHandFiring(chr, i, true);

					chr->act_attack.lastfire60 = g_Vars.lvframe60;

					if (chr->actiontype == ACT_ATTACKROLL) {
						f32 f12 = chr->act_attack.animcfg->unk1c - chr->act_attack.animcfg->unk18;

						if (f12 < 30) {
							if (chr->act_attack.pausecount >= PALDOWN(60) - (s32)(PAL ? f12 * (50.0f / 60.0f) : f12) * 2) {
								modelSetAnimSpeed(model, 0.5f, 0);
							} else {
								modelSetAnimSpeed(model, 0.1f, 0);
								chr->act_attack.pausecount += g_Vars.lvupdate240_60;
							}
						} else {
							modelSetAnimSpeed(model, 0.5f, 0);
						}
					} else {
						modelSetAnimSpeed(model, 0.5f, 0);
					}
				} else {
					chrSetHandFiring(chr, i, false);

					if (chr->actiontype == ACT_ATTACKROLL) {
						modelSetAnimSpeed(model, chrGetRangedSpeed(chr, 0.5f, 0.8f), 0);
					} else {
						modelSetAnimSpeed(model, chrGetRangedSpeed(chr, 0.5f, 0.8f), 0);
					}
				}
			} else if (modelGetAnimNum(model) == ANIM_SNIPING_ONGROUND
					|| ((!chr->act_attack.fired && (i == chr->act_attack.nextgun || !chr->act_attack.everytick[chr->act_attack.nextgun]))
						&& ((chr->act_attack.animcfg->unk20 >= 0 && curframe >= chr->act_attack.animcfg->unk20 && curframe <= chr->act_attack.animcfg->unk24)
							|| (chr->act_attack.animcfg->unk20 < 0 && curframe >= chr->act_attack.animcfg->unk18)))) {
				chr->act_attack.fired = true;
				chr->act_attack.nextgun = 1 - chr->act_attack.nextgun;
				chr->act_attack.numshots++;
				chr->act_attack.lastfire60 = g_Vars.lvframe60;

				chrSetHandFiring(chr, i, true);
			} else {
				chrSetHandFiring(chr, i, false);
			}
		} else {
			chrSetHandFiring(chr, i, false);
		}
	}
}

void chrTickAttackAmount(struct chrdata *chr)
{
	struct model *model = chr->model;
	f32 frame = modelGetCurAnimFrame(model);
	f32 unk0c = chr->act_attack.animcfg->unk0c;
	f32 unk04 = chr->act_attack.animcfg->unk04;

	chrTurn(chr, 1, unk04, chrGetRangedSpeed(chr, 1, 1.6f), unk0c);

	if (frame > chr->act_attack.animcfg->unk28
			&& frame < chr->act_attack.animcfg->unk2c) {
		func0f03e9f4(chr, chr->act_attack.animcfg, 0, 1, 0.2f);
	} else {
		chrResetAimEndProperties(chr);
	}

	if (frame >= chr->act_attack.animcfg->unk18 && chr->act_attack.dooneburst == false) {
		chr->act_attack.dooneburst = true;
	}

	if (chr->act_attack.dooneburst) {
		if (chr->act_attack.numshots++ < chr->act_attack.maxshots) {
			chrSetHandFiring(chr, HAND_RIGHT, true);
		} else {
			chrAttackAmountUpdateAnimation(chr);
			chrSetHandFiring(chr, HAND_RIGHT, false);
		}
	} else {
		chrSetHandFiring(chr, HAND_RIGHT, false);
	}
}

/**
 * Sets the robot's muzzle flash to on or off.
 *
 * There are two muzzles, left and right, which is specified using the `right`
 * argument.
 */
void robotSetMuzzleFlash(struct chrdata *chr, bool right, bool visible)
{
	struct modelnode *node;
	union modelrwdata *rwdata;
	s32 partnum;

	if (right) {
		partnum = MODELPART_ROBOT_RGUNFIRE;
	} else {
		partnum = MODELPART_ROBOT_LGUNFIRE;
	}

	node = modelGetPart(chr->model->filedata, partnum);

	if (node) {
		rwdata = modelGetNodeRwData(chr->model, node);
	}

	if (rwdata) {
		rwdata->gunfire.visible = visible;
	}
}

void robotAttack(struct chrdata *chr)
{
	u32 numshots = random() % 20;

	if (chr->unk348[0] && chr->unk348[1]) {
		chr->actiontype = ACT_ROBOTATTACK;

		chr->unk348[0]->beam->age = -1;
		chr->unk348[0]->unk00 = random() % 3;
		chr->unk348[0]->unk01 = 0;
		chr->unk348[0]->unk08 = -1;
		chr->unk348[0]->unk0c = 0.85f;

		if ((lvGetDifficulty() == DIFF_PA) * 0.2f) {
			chr->unk348[0]->unk10 = 2.0f;
		} else {
			chr->unk348[0]->unk10 = 1.0f;
		}

		chr->unk348[0]->unk14 = 0.0f;

		chr->act_robotattack.pos[0].x = 0.0f;
		chr->act_robotattack.pos[0].y = 0.0f;
		chr->act_robotattack.pos[0].z = 0.0f;
		chr->act_robotattack.dir[0].x = 0.0f;
		chr->act_robotattack.dir[0].y = 0.0f;
		chr->act_robotattack.dir[0].z = 0.0f;
		chr->act_robotattack.guntype[0] = WEAPON_WATCHLASER;
		chr->act_robotattack.firing[0] = false;

		chr->unk348[1]->beam->age = -1;
		chr->unk348[1]->unk00 = random() % 3;
		chr->unk348[1]->unk01 = 0;
		chr->unk348[1]->unk08 = -1;
		chr->unk348[1]->unk0c = 0.85f;
		chr->unk348[1]->unk10 = 0.2f;
		chr->unk348[1]->unk14 = 0.0f;

		chr->act_robotattack.guntype[1] = WEAPON_WATCHLASER;
		chr->act_robotattack.firing[1] = false;
		chr->act_robotattack.finished = false;
		chr->act_robotattack.numshots[0] = numshots;
		chr->act_robotattack.numshots[1] = numshots;
		chr->act_robotattack.pos[1].x = 0.0f;
		chr->act_robotattack.pos[1].y = 0.0f;
		chr->act_robotattack.pos[1].z = 0.0f;
		chr->act_robotattack.dir[1].x = 0.0f;
		chr->act_robotattack.dir[1].y = 0.0f;
		chr->act_robotattack.dir[1].z = 0.0f;

		chrStandChooseAnimation(chr, 16);
	}
}

void func0f0429d8(struct chrdata *chr, f32 arg1, f32 arg2)
{
	struct prop *prop = chrGetTargetProp(chr);
	f32 distance = atan2f(prop->pos.x - chr->prop->pos.x, prop->pos.z - chr->prop->pos.z);
	f32 value = model0001afe8(arg2, distance, arg1);
	chrSetLookAngle(chr, value);
}

GLOBAL_ASM(
glabel chrTickRobotAttack
.late_rodata
glabel var7f1a91a4
.word 0x40c907a9
glabel var7f1a91a8
.word 0x3cf5c28f
glabel var7f1a91ac
.word 0x3cf5c28f
glabel var7f1a91b0
.word 0x3cf5c28f
glabel var7f1a91b4
.word 0x3cf5c28f
glabel var7f1a91b8
.word 0x404907a9
glabel var7f1a91bc
.word 0xbf0624dd
glabel var7f1a91c0
.word 0x3f0624dd
glabel var7f1a91c4
.word 0x404907a9
glabel var7f1a91c8
.word 0xbf0624dd
glabel var7f1a91cc
.word 0xbf0624dd
glabel var7f1a91d0
.word 0x3f0624dd
glabel var7f1a91d4
.word 0x3f0624dd
glabel var7f1a91d8
.word 0x3e19999a
glabel var7f1a91dc
.word 0x3e19999a
.text
/*  f042a40:	27bdfee8 */ 	addiu	$sp,$sp,-280
/*  f042a44:	f7bc0038 */ 	sdc1	$f28,0x38($sp)
/*  f042a48:	4480e000 */ 	mtc1	$zero,$f28
/*  f042a4c:	afbf006c */ 	sw	$ra,0x6c($sp)
/*  f042a50:	afb20050 */ 	sw	$s2,0x50($sp)
/*  f042a54:	f7ba0030 */ 	sdc1	$f26,0x30($sp)
/*  f042a58:	00809025 */ 	or	$s2,$a0,$zero
/*  f042a5c:	afbe0068 */ 	sw	$s8,0x68($sp)
/*  f042a60:	afb70064 */ 	sw	$s7,0x64($sp)
/*  f042a64:	afb60060 */ 	sw	$s6,0x60($sp)
/*  f042a68:	afb5005c */ 	sw	$s5,0x5c($sp)
/*  f042a6c:	afb40058 */ 	sw	$s4,0x58($sp)
/*  f042a70:	afb30054 */ 	sw	$s3,0x54($sp)
/*  f042a74:	afb1004c */ 	sw	$s1,0x4c($sp)
/*  f042a78:	afb00048 */ 	sw	$s0,0x48($sp)
/*  f042a7c:	f7be0040 */ 	sdc1	$f30,0x40($sp)
/*  f042a80:	f7b80028 */ 	sdc1	$f24,0x28($sp)
/*  f042a84:	f7b60020 */ 	sdc1	$f22,0x20($sp)
/*  f042a88:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f042a8c:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f042a90:	4600e686 */ 	mov.s	$f26,$f28
/*  f042a94:	0040f025 */ 	or	$s8,$v0,$zero
/*  f042a98:	0fc0f917 */ 	jal	chrGetInverseTheta
/*  f042a9c:	02402025 */ 	or	$a0,$s2,$zero
/*  f042aa0:	3c053dae */ 	lui	$a1,0x3dae
/*  f042aa4:	44060000 */ 	mfc1	$a2,$f0
/*  f042aa8:	e7a000fc */ 	swc1	$f0,0xfc($sp)
/*  f042aac:	34a5147b */ 	ori	$a1,$a1,0x147b
/*  f042ab0:	0fc10a76 */ 	jal	func0f0429d8
/*  f042ab4:	02402025 */ 	or	$a0,$s2,$zero
/*  f042ab8:	8e4f0020 */ 	lw	$t7,0x20($s2)
/*  f042abc:	3c0e8008 */ 	lui	$t6,%hi(g_ModelTypeRobot)
/*  f042ac0:	25cecefc */ 	addiu	$t6,$t6,%lo(g_ModelTypeRobot)
/*  f042ac4:	8df80008 */ 	lw	$t8,0x8($t7)
/*  f042ac8:	2655002c */ 	addiu	$s5,$s2,0x2c
/*  f042acc:	02a0b825 */ 	or	$s7,$s5,$zero
/*  f042ad0:	8f190004 */ 	lw	$t9,0x4($t8)
/*  f042ad4:	0000a025 */ 	or	$s4,$zero,$zero
/*  f042ad8:	02408825 */ 	or	$s1,$s2,$zero
/*  f042adc:	11d90004 */ 	beq	$t6,$t9,.L0f042af0
/*  f042ae0:	3c017f1b */ 	lui	$at,%hi(var7f1a91a4)
/*  f042ae4:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f042ae8:	10000132 */ 	b	.L0f042fb4
/*  f042aec:	a248006e */ 	sb	$t0,0x6e($s2)
.L0f042af0:
/*  f042af0:	afb50070 */ 	sw	$s5,0x70($sp)
/*  f042af4:	c43e91a4 */ 	lwc1	$f30,%lo(var7f1a91a4)($at)
.L0f042af8:
/*  f042af8:	8ee90038 */ 	lw	$t1,0x38($s7)
/*  f042afc:	00009825 */ 	or	$s3,$zero,$zero
/*  f042b00:	5920000e */ 	blezl	$t1,.L0f042b3c
/*  f042b04:	8e380348 */ 	lw	$t8,0x348($s1)
/*  f042b08:	8e220348 */ 	lw	$v0,0x348($s1)
/*  f042b0c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f042b10:	90450000 */ 	lbu	$a1,0x0($v0)
/*  f042b14:	00a1001a */ 	div	$zero,$a1,$at
/*  f042b18:	00005010 */ 	mfhi	$t2
/*  f042b1c:	2d4b0001 */ 	sltiu	$t3,$t2,0x1
/*  f042b20:	a04b0001 */ 	sb	$t3,0x1($v0)
/*  f042b24:	8e2c0348 */ 	lw	$t4,0x348($s1)
/*  f042b28:	91850000 */ 	lbu	$a1,0x0($t4)
/*  f042b2c:	30ad0001 */ 	andi	$t5,$a1,0x1
/*  f042b30:	10000004 */ 	b	.L0f042b44
/*  f042b34:	2db60001 */ 	sltiu	$s6,$t5,0x1
/*  f042b38:	8e380348 */ 	lw	$t8,0x348($s1)
.L0f042b3c:
/*  f042b3c:	0000b025 */ 	or	$s6,$zero,$zero
/*  f042b40:	a3000001 */ 	sb	$zero,0x1($t8)
.L0f042b44:
/*  f042b44:	8fae0070 */ 	lw	$t6,0x70($sp)
/*  f042b48:	00145080 */ 	sll	$t2,$s4,0x2
/*  f042b4c:	01545023 */ 	subu	$t2,$t2,$s4
/*  f042b50:	a1d60040 */ 	sb	$s6,0x40($t6)
/*  f042b54:	8eb90038 */ 	lw	$t9,0x38($s5)
/*  f042b58:	000a5080 */ 	sll	$t2,$t2,0x2
/*  f042b5c:	1f200045 */ 	bgtz	$t9,.L0f042c74
/*  f042b60:	00000000 */ 	nop
/*  f042b64:	8ea8003c */ 	lw	$t0,0x3c($s5)
/*  f042b68:	3c017f1b */ 	lui	$at,%hi(var7f1a91a8)
/*  f042b6c:	1d000041 */ 	bgtz	$t0,.L0f042c74
/*  f042b70:	00000000 */ 	nop
/*  f042b74:	c640030c */ 	lwc1	$f0,0x30c($s2)
/*  f042b78:	44802000 */ 	mtc1	$zero,$f4
/*  f042b7c:	24130001 */ 	addiu	$s3,$zero,0x1
/*  f042b80:	4600203c */ 	c.lt.s	$f4,$f0
/*  f042b84:	00000000 */ 	nop
/*  f042b88:	45020004 */ 	bc1fl	.L0f042b9c
/*  f042b8c:	46000587 */ 	neg.s	$f22,$f0
/*  f042b90:	10000002 */ 	b	.L0f042b9c
/*  f042b94:	46000586 */ 	mov.s	$f22,$f0
/*  f042b98:	46000587 */ 	neg.s	$f22,$f0
.L0f042b9c:
/*  f042b9c:	c42691a8 */ 	lwc1	$f6,%lo(var7f1a91a8)($at)
/*  f042ba0:	3c017f1b */ 	lui	$at,%hi(var7f1a91ac)
/*  f042ba4:	4606b03c */ 	c.lt.s	$f22,$f6
/*  f042ba8:	00000000 */ 	nop
/*  f042bac:	45000031 */ 	bc1f	.L0f042c74
/*  f042bb0:	00000000 */ 	nop
/*  f042bb4:	c6400314 */ 	lwc1	$f0,0x314($s2)
/*  f042bb8:	44804000 */ 	mtc1	$zero,$f8
/*  f042bbc:	00000000 */ 	nop
/*  f042bc0:	4600403c */ 	c.lt.s	$f8,$f0
/*  f042bc4:	00000000 */ 	nop
/*  f042bc8:	45020004 */ 	bc1fl	.L0f042bdc
/*  f042bcc:	46000087 */ 	neg.s	$f2,$f0
/*  f042bd0:	10000002 */ 	b	.L0f042bdc
/*  f042bd4:	46000086 */ 	mov.s	$f2,$f0
/*  f042bd8:	46000087 */ 	neg.s	$f2,$f0
.L0f042bdc:
/*  f042bdc:	c42a91ac */ 	lwc1	$f10,%lo(var7f1a91ac)($at)
/*  f042be0:	3c017f1b */ 	lui	$at,%hi(var7f1a91b0)
/*  f042be4:	460a103c */ 	c.lt.s	$f2,$f10
/*  f042be8:	00000000 */ 	nop
/*  f042bec:	45000021 */ 	bc1f	.L0f042c74
/*  f042bf0:	00000000 */ 	nop
/*  f042bf4:	c6400310 */ 	lwc1	$f0,0x310($s2)
/*  f042bf8:	44808000 */ 	mtc1	$zero,$f16
/*  f042bfc:	00000000 */ 	nop
/*  f042c00:	4600803c */ 	c.lt.s	$f16,$f0
/*  f042c04:	00000000 */ 	nop
/*  f042c08:	45020004 */ 	bc1fl	.L0f042c1c
/*  f042c0c:	46000087 */ 	neg.s	$f2,$f0
/*  f042c10:	10000002 */ 	b	.L0f042c1c
/*  f042c14:	46000086 */ 	mov.s	$f2,$f0
/*  f042c18:	46000087 */ 	neg.s	$f2,$f0
.L0f042c1c:
/*  f042c1c:	c43291b0 */ 	lwc1	$f18,%lo(var7f1a91b0)($at)
/*  f042c20:	3c017f1b */ 	lui	$at,%hi(var7f1a91b4)
/*  f042c24:	4612103c */ 	c.lt.s	$f2,$f18
/*  f042c28:	00000000 */ 	nop
/*  f042c2c:	45000011 */ 	bc1f	.L0f042c74
/*  f042c30:	00000000 */ 	nop
/*  f042c34:	c6400318 */ 	lwc1	$f0,0x318($s2)
/*  f042c38:	44802000 */ 	mtc1	$zero,$f4
/*  f042c3c:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f042c40:	4600203c */ 	c.lt.s	$f4,$f0
/*  f042c44:	00000000 */ 	nop
/*  f042c48:	45020004 */ 	bc1fl	.L0f042c5c
/*  f042c4c:	46000087 */ 	neg.s	$f2,$f0
/*  f042c50:	10000002 */ 	b	.L0f042c5c
/*  f042c54:	46000086 */ 	mov.s	$f2,$f0
/*  f042c58:	46000087 */ 	neg.s	$f2,$f0
.L0f042c5c:
/*  f042c5c:	c42691b4 */ 	lwc1	$f6,%lo(var7f1a91b4)($at)
/*  f042c60:	4606103c */ 	c.lt.s	$f2,$f6
/*  f042c64:	00000000 */ 	nop
/*  f042c68:	45000002 */ 	bc1f	.L0f042c74
/*  f042c6c:	00000000 */ 	nop
/*  f042c70:	a2a90042 */ 	sb	$t1,0x42($s5)
.L0f042c74:
/*  f042c74:	16600083 */ 	bnez	$s3,.L0f042e84
/*  f042c78:	3c0141a0 */ 	lui	$at,0x41a0
/*  f042c7c:	c7c8000c */ 	lwc1	$f8,0xc($s8)
/*  f042c80:	44815000 */ 	mtc1	$at,$f10
/*  f042c84:	02aa8021 */ 	addu	$s0,$s5,$t2
/*  f042c88:	12800003 */ 	beqz	$s4,.L0f042c98
/*  f042c8c:	460a4501 */ 	sub.s	$f20,$f8,$f10
/*  f042c90:	10000002 */ 	b	.L0f042c9c
/*  f042c94:	00002825 */ 	or	$a1,$zero,$zero
.L0f042c98:
/*  f042c98:	24050001 */ 	addiu	$a1,$zero,0x1
.L0f042c9c:
/*  f042c9c:	8e4b0020 */ 	lw	$t3,0x20($s2)
/*  f042ca0:	0c006a6f */ 	jal	modelGetPartRodata
/*  f042ca4:	8d640008 */ 	lw	$a0,0x8($t3)
/*  f042ca8:	c4500000 */ 	lwc1	$f16,0x0($v0)
/*  f042cac:	3c014396 */ 	lui	$at,0x4396
/*  f042cb0:	44812000 */ 	mtc1	$at,$f4
/*  f042cb4:	e6100000 */ 	swc1	$f16,0x0($s0)
/*  f042cb8:	c4520004 */ 	lwc1	$f18,0x4($v0)
/*  f042cbc:	27a500a4 */ 	addiu	$a1,$sp,0xa4
/*  f042cc0:	46049181 */ 	sub.s	$f6,$f18,$f4
/*  f042cc4:	e6060004 */ 	swc1	$f6,0x4($s0)
/*  f042cc8:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f042ccc:	e6080008 */ 	swc1	$f8,0x8($s0)
/*  f042cd0:	0c0058dd */ 	jal	mtx4LoadYRotation
/*  f042cd4:	c7ac00fc */ 	lwc1	$f12,0xfc($sp)
/*  f042cd8:	27a400a4 */ 	addiu	$a0,$sp,0xa4
/*  f042cdc:	02002825 */ 	or	$a1,$s0,$zero
/*  f042ce0:	0c0056c5 */ 	jal	mtx4RotateVec
/*  f042ce4:	27a600e4 */ 	addiu	$a2,$sp,0xe4
/*  f042ce8:	8e4c0020 */ 	lw	$t4,0x20($s2)
/*  f042cec:	c7aa00e4 */ 	lwc1	$f10,0xe4($sp)
/*  f042cf0:	c7a400e8 */ 	lwc1	$f4,0xe8($sp)
/*  f042cf4:	c5900014 */ 	lwc1	$f16,0x14($t4)
/*  f042cf8:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f042cfc:	c7aa00ec */ 	lwc1	$f10,0xec($sp)
/*  f042d00:	e7b200e4 */ 	swc1	$f18,0xe4($sp)
/*  f042d04:	8e4d0020 */ 	lw	$t5,0x20($s2)
/*  f042d08:	c5a60014 */ 	lwc1	$f6,0x14($t5)
/*  f042d0c:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f042d10:	e7a800e8 */ 	swc1	$f8,0xe8($sp)
/*  f042d14:	8e4f0020 */ 	lw	$t7,0x20($s2)
/*  f042d18:	c5f00014 */ 	lwc1	$f16,0x14($t7)
/*  f042d1c:	46105102 */ 	mul.s	$f4,$f10,$f16
/*  f042d20:	e7a400ec */ 	swc1	$f4,0xec($sp)
/*  f042d24:	8e58001c */ 	lw	$t8,0x1c($s2)
/*  f042d28:	c7060008 */ 	lwc1	$f6,0x8($t8)
/*  f042d2c:	46123200 */ 	add.s	$f8,$f6,$f18
/*  f042d30:	e6080000 */ 	swc1	$f8,0x0($s0)
/*  f042d34:	8e4e001c */ 	lw	$t6,0x1c($s2)
/*  f042d38:	c7b000e8 */ 	lwc1	$f16,0xe8($sp)
/*  f042d3c:	c5ca000c */ 	lwc1	$f10,0xc($t6)
/*  f042d40:	46105100 */ 	add.s	$f4,$f10,$f16
/*  f042d44:	c6100000 */ 	lwc1	$f16,0x0($s0)
/*  f042d48:	e6040004 */ 	swc1	$f4,0x4($s0)
/*  f042d4c:	8e59001c */ 	lw	$t9,0x1c($s2)
/*  f042d50:	c7b200ec */ 	lwc1	$f18,0xec($sp)
/*  f042d54:	c7260010 */ 	lwc1	$f6,0x10($t9)
/*  f042d58:	46123200 */ 	add.s	$f8,$f6,$f18
/*  f042d5c:	e6080008 */ 	swc1	$f8,0x8($s0)
/*  f042d60:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f042d64:	c7c40010 */ 	lwc1	$f4,0x10($s8)
/*  f042d68:	c7ca0008 */ 	lwc1	$f10,0x8($s8)
/*  f042d6c:	46062381 */ 	sub.s	$f14,$f4,$f6
/*  f042d70:	0fc259d4 */ 	jal	atan2f
/*  f042d74:	46105301 */ 	sub.s	$f12,$f10,$f16
/*  f042d78:	c7ac00fc */ 	lwc1	$f12,0xfc($sp)
/*  f042d7c:	3c017f1b */ 	lui	$at,%hi(var7f1a91b8)
/*  f042d80:	460c003c */ 	c.lt.s	$f0,$f12
/*  f042d84:	460c0081 */ 	sub.s	$f2,$f0,$f12
/*  f042d88:	45000002 */ 	bc1f	.L0f042d94
/*  f042d8c:	46001686 */ 	mov.s	$f26,$f2
/*  f042d90:	461e1680 */ 	add.s	$f26,$f2,$f30
.L0f042d94:
/*  f042d94:	c43291b8 */ 	lwc1	$f18,%lo(var7f1a91b8)($at)
/*  f042d98:	3c017f1b */ 	lui	$at,%hi(var7f1a91bc)
/*  f042d9c:	461a903c */ 	c.lt.s	$f18,$f26
/*  f042da0:	00000000 */ 	nop
/*  f042da4:	45000002 */ 	bc1f	.L0f042db0
/*  f042da8:	00000000 */ 	nop
/*  f042dac:	461ed681 */ 	sub.s	$f26,$f26,$f30
.L0f042db0:
/*  f042db0:	c42e91bc */ 	lwc1	$f14,%lo(var7f1a91bc)($at)
/*  f042db4:	3c017f1b */ 	lui	$at,%hi(var7f1a91c0)
/*  f042db8:	460ed03c */ 	c.lt.s	$f26,$f14
/*  f042dbc:	00000000 */ 	nop
/*  f042dc0:	45000002 */ 	bc1f	.L0f042dcc
/*  f042dc4:	00000000 */ 	nop
/*  f042dc8:	46007686 */ 	mov.s	$f26,$f14
.L0f042dcc:
/*  f042dcc:	c42091c0 */ 	lwc1	$f0,%lo(var7f1a91c0)($at)
/*  f042dd0:	461a003c */ 	c.lt.s	$f0,$f26
/*  f042dd4:	00000000 */ 	nop
/*  f042dd8:	45020003 */ 	bc1fl	.L0f042de8
/*  f042ddc:	c7c80008 */ 	lwc1	$f8,0x8($s8)
/*  f042de0:	46000686 */ 	mov.s	$f26,$f0
/*  f042de4:	c7c80008 */ 	lwc1	$f8,0x8($s8)
.L0f042de8:
/*  f042de8:	c60a0000 */ 	lwc1	$f10,0x0($s0)
/*  f042dec:	c7d00010 */ 	lwc1	$f16,0x10($s8)
/*  f042df0:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f042df4:	460a4001 */ 	sub.s	$f0,$f8,$f10
/*  f042df8:	46048081 */ 	sub.s	$f2,$f16,$f4
/*  f042dfc:	46000182 */ 	mul.s	$f6,$f0,$f0
/*  f042e00:	00000000 */ 	nop
/*  f042e04:	46021482 */ 	mul.s	$f18,$f2,$f2
/*  f042e08:	0c012974 */ 	jal	sqrtf
/*  f042e0c:	46123300 */ 	add.s	$f12,$f6,$f18
/*  f042e10:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f042e14:	46000386 */ 	mov.s	$f14,$f0
/*  f042e18:	0fc259d4 */ 	jal	atan2f
/*  f042e1c:	4608a301 */ 	sub.s	$f12,$f20,$f8
/*  f042e20:	4600f081 */ 	sub.s	$f2,$f30,$f0
/*  f042e24:	3c017f1b */ 	lui	$at,%hi(var7f1a91c4)
/*  f042e28:	c42a91c4 */ 	lwc1	$f10,%lo(var7f1a91c4)($at)
/*  f042e2c:	3c017f1b */ 	lui	$at,%hi(var7f1a91c8)
/*  f042e30:	46001706 */ 	mov.s	$f28,$f2
/*  f042e34:	4602503c */ 	c.lt.s	$f10,$f2
/*  f042e38:	00000000 */ 	nop
/*  f042e3c:	45000002 */ 	bc1f	.L0f042e48
/*  f042e40:	00000000 */ 	nop
/*  f042e44:	461e1701 */ 	sub.s	$f28,$f2,$f30
.L0f042e48:
/*  f042e48:	c43091c8 */ 	lwc1	$f16,%lo(var7f1a91c8)($at)
/*  f042e4c:	3c017f1b */ 	lui	$at,%hi(var7f1a91cc)
/*  f042e50:	4610e03c */ 	c.lt.s	$f28,$f16
/*  f042e54:	00000000 */ 	nop
/*  f042e58:	45000002 */ 	bc1f	.L0f042e64
/*  f042e5c:	00000000 */ 	nop
/*  f042e60:	c43c91cc */ 	lwc1	$f28,%lo(var7f1a91cc)($at)
.L0f042e64:
/*  f042e64:	3c017f1b */ 	lui	$at,%hi(var7f1a91d0)
/*  f042e68:	c42491d0 */ 	lwc1	$f4,%lo(var7f1a91d0)($at)
/*  f042e6c:	3c017f1b */ 	lui	$at,%hi(var7f1a91d4)
/*  f042e70:	461c203c */ 	c.lt.s	$f4,$f28
/*  f042e74:	00000000 */ 	nop
/*  f042e78:	45020003 */ 	bc1fl	.L0f042e88
/*  f042e7c:	c620030c */ 	lwc1	$f0,0x30c($s1)
/*  f042e80:	c43c91d4 */ 	lwc1	$f28,%lo(var7f1a91d4)($at)
.L0f042e84:
/*  f042e84:	c620030c */ 	lwc1	$f0,0x30c($s1)
.L0f042e88:
/*  f042e88:	3c017f1b */ 	lui	$at,%hi(var7f1a91d8)
/*  f042e8c:	c43291d8 */ 	lwc1	$f18,%lo(var7f1a91d8)($at)
/*  f042e90:	4600d181 */ 	sub.s	$f6,$f26,$f0
/*  f042e94:	c6220314 */ 	lwc1	$f2,0x314($s1)
/*  f042e98:	3c017f1b */ 	lui	$at,%hi(var7f1a91dc)
/*  f042e9c:	46123202 */ 	mul.s	$f8,$f6,$f18
/*  f042ea0:	4602e401 */ 	sub.s	$f16,$f28,$f2
/*  f042ea4:	46080280 */ 	add.s	$f10,$f0,$f8
/*  f042ea8:	e62a030c */ 	swc1	$f10,0x30c($s1)
/*  f042eac:	c42491dc */ 	lwc1	$f4,%lo(var7f1a91dc)($at)
/*  f042eb0:	46048182 */ 	mul.s	$f6,$f16,$f4
/*  f042eb4:	46061480 */ 	add.s	$f18,$f2,$f6
/*  f042eb8:	16600036 */ 	bnez	$s3,.L0f042f94
/*  f042ebc:	e6320314 */ 	swc1	$f18,0x314($s1)
/*  f042ec0:	12c00030 */ 	beqz	$s6,.L0f042f84
/*  f042ec4:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*  f042ec8:	44800000 */ 	mtc1	$zero,$f0
/*  f042ecc:	c6380314 */ 	lwc1	$f24,0x314($s1)
/*  f042ed0:	00144080 */ 	sll	$t0,$s4,0x2
/*  f042ed4:	01144023 */ 	subu	$t0,$t0,$s4
/*  f042ed8:	4600c03c */ 	c.lt.s	$f24,$f0
/*  f042edc:	00084080 */ 	sll	$t0,$t0,0x2
/*  f042ee0:	c634030c */ 	lwc1	$f20,0x30c($s1)
/*  f042ee4:	02a88021 */ 	addu	$s0,$s5,$t0
/*  f042ee8:	45020003 */ 	bc1fl	.L0f042ef8
/*  f042eec:	4600a03c */ 	c.lt.s	$f20,$f0
/*  f042ef0:	461ec600 */ 	add.s	$f24,$f24,$f30
/*  f042ef4:	4600a03c */ 	c.lt.s	$f20,$f0
.L0f042ef8:
/*  f042ef8:	00000000 */ 	nop
/*  f042efc:	45020003 */ 	bc1fl	.L0f042f0c
/*  f042f00:	4608a500 */ 	add.s	$f20,$f20,$f8
/*  f042f04:	461ea500 */ 	add.s	$f20,$f20,$f30
/*  f042f08:	4608a500 */ 	add.s	$f20,$f20,$f8
.L0f042f0c:
/*  f042f0c:	4614f03e */ 	c.le.s	$f30,$f20
/*  f042f10:	00000000 */ 	nop
/*  f042f14:	45000002 */ 	bc1f	.L0f042f20
/*  f042f18:	00000000 */ 	nop
/*  f042f1c:	461ea501 */ 	sub.s	$f20,$f20,$f30
.L0f042f20:
/*  f042f20:	0c0068f7 */ 	jal	sinf
/*  f042f24:	4600a306 */ 	mov.s	$f12,$f20
/*  f042f28:	46000586 */ 	mov.s	$f22,$f0
/*  f042f2c:	0c0068f4 */ 	jal	cosf
/*  f042f30:	4600c306 */ 	mov.s	$f12,$f24
/*  f042f34:	46160282 */ 	mul.s	$f10,$f0,$f22
/*  f042f38:	4600c306 */ 	mov.s	$f12,$f24
/*  f042f3c:	0c0068f7 */ 	jal	sinf
/*  f042f40:	e60a0018 */ 	swc1	$f10,0x18($s0)
/*  f042f44:	46000407 */ 	neg.s	$f16,$f0
/*  f042f48:	4600a306 */ 	mov.s	$f12,$f20
/*  f042f4c:	0c0068f4 */ 	jal	cosf
/*  f042f50:	e610001c */ 	swc1	$f16,0x1c($s0)
/*  f042f54:	46000586 */ 	mov.s	$f22,$f0
/*  f042f58:	0c0068f4 */ 	jal	cosf
/*  f042f5c:	4600c306 */ 	mov.s	$f12,$f24
/*  f042f60:	46160102 */ 	mul.s	$f4,$f0,$f22
/*  f042f64:	02402025 */ 	or	$a0,$s2,$zero
/*  f042f68:	02802825 */ 	or	$a1,$s4,$zero
/*  f042f6c:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f042f70:	0fc109e7 */ 	jal	robotSetMuzzleFlash
/*  f042f74:	e6040020 */ 	swc1	$f4,0x20($s0)
/*  f042f78:	8ee90038 */ 	lw	$t1,0x38($s7)
/*  f042f7c:	252affff */ 	addiu	$t2,$t1,-1
/*  f042f80:	aeea0038 */ 	sw	$t2,0x38($s7)
.L0f042f84:
/*  f042f84:	8e220348 */ 	lw	$v0,0x348($s1)
/*  f042f88:	904b0000 */ 	lbu	$t3,0x0($v0)
/*  f042f8c:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f042f90:	a04c0000 */ 	sb	$t4,0x0($v0)
.L0f042f94:
/*  f042f94:	8fad0070 */ 	lw	$t5,0x70($sp)
/*  f042f98:	26940001 */ 	addiu	$s4,$s4,0x1
/*  f042f9c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f042fa0:	25af0001 */ 	addiu	$t7,$t5,0x1
/*  f042fa4:	afaf0070 */ 	sw	$t7,0x70($sp)
/*  f042fa8:	26310004 */ 	addiu	$s1,$s1,0x4
/*  f042fac:	1681fed2 */ 	bne	$s4,$at,.L0f042af8
/*  f042fb0:	26f70004 */ 	addiu	$s7,$s7,0x4
.L0f042fb4:
/*  f042fb4:	8fbf006c */ 	lw	$ra,0x6c($sp)
/*  f042fb8:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f042fbc:	d7b60020 */ 	ldc1	$f22,0x20($sp)
/*  f042fc0:	d7b80028 */ 	ldc1	$f24,0x28($sp)
/*  f042fc4:	d7ba0030 */ 	ldc1	$f26,0x30($sp)
/*  f042fc8:	d7bc0038 */ 	ldc1	$f28,0x38($sp)
/*  f042fcc:	d7be0040 */ 	ldc1	$f30,0x40($sp)
/*  f042fd0:	8fb00048 */ 	lw	$s0,0x48($sp)
/*  f042fd4:	8fb1004c */ 	lw	$s1,0x4c($sp)
/*  f042fd8:	8fb20050 */ 	lw	$s2,0x50($sp)
/*  f042fdc:	8fb30054 */ 	lw	$s3,0x54($sp)
/*  f042fe0:	8fb40058 */ 	lw	$s4,0x58($sp)
/*  f042fe4:	8fb5005c */ 	lw	$s5,0x5c($sp)
/*  f042fe8:	8fb60060 */ 	lw	$s6,0x60($sp)
/*  f042fec:	8fb70064 */ 	lw	$s7,0x64($sp)
/*  f042ff0:	8fbe0068 */ 	lw	$s8,0x68($sp)
/*  f042ff4:	03e00008 */ 	jr	$ra
/*  f042ff8:	27bd0118 */ 	addiu	$sp,$sp,0x118
);

// Mismatch: float regalloc near first atan2f and too much stack usage.
//void chrTickRobotAttack(struct chrdata *chr)
//{
//	f32 f26 = 0;
//	f32 f28 = 0;
//	struct prop *targetprop = chrGetTargetProp(chr);
//	bool firing;
//	f32 f20;
//	f32 f24;
//	f32 invtheta = chrGetInverseTheta(chr);
//	union modelrodata *rodata;
//	f32 aimy;
//	struct act_robotattack *act = &chr->act_robotattack;
//	struct coord spe4;
//	Mtxf spa4;
//	s32 i;
//	f32 xdiff;
//	f32 zdiff;
//
//	func0f0429d8(chr, 0.085f, invtheta);
//
//	if (chr->model->filedata->type != &g_ModelTypeRobot) {
//		act->finished = true;
//		return;
//	}
//
//	for (i = 0; i < 2; i++) {
//		bool empty = false;
//
//		if (act->numshots[i] > 0) {
//			chr->unk348[i]->unk01 = !(chr->unk348[i]->unk00 % 3);
//			firing = !(chr->unk348[i]->unk00 % 2);
//		} else {
//			chr->unk348[i]->unk01 = 0;
//			firing = false;
//		}
//
//		act->firing[i] = firing;
//
//		if (act->numshots[0] <= 0 && act->numshots[1] <= 0) {
//			empty = true;
//
//			if (ABS(chr->gunroty[0]) < 0.03f
//					&& ABS(chr->gunrotx[0]) < 0.03f
//					&& ABS(chr->gunroty[1]) < 0.03f
//					&& ABS(chr->gunrotx[1]) < 0.03f) {
//				act->finished = true;
//			}
//		}
//
//		if (!empty) {
//			aimy = targetprop->pos.y - 20;
//			rodata = modelGetPartRodata(chr->model->filedata, (i ? MODELPART_ROBOT_0000 : MODELPART_ROBOT_0001));
//
//			act->pos[i].x = rodata->position.pos.x;
//			act->pos[i].y = rodata->position.pos.y - 300;
//			act->pos[i].z = rodata->position.pos.z;
//
//			mtx4LoadYRotation(invtheta, &spa4);
//			mtx4RotateVec(&spa4, &act->pos[i], &spe4);
//
//			spe4.x *= chr->model->scale;
//			spe4.y *= chr->model->scale;
//			spe4.z *= chr->model->scale;
//
//			act->pos[i].x = chr->prop->pos.x + spe4.x;
//			act->pos[i].y = chr->prop->pos.y + spe4.y;
//			act->pos[i].z = chr->prop->pos.z + spe4.z;
//
//			f26 = atan2f(targetprop->pos.x - act->pos[i].x, targetprop->pos.z - act->pos[i].z) - invtheta;
//
//			if (f26 < 0.0f) {
//				f26 += M_BADTAU;
//			}
//
//			if (f26 > M_BADPI) {
//				f26 -= M_BADTAU;
//			}
//
//			if (f26 < -0.524f) {
//				f26 = -0.524f;
//			}
//
//			if (f26 > 0.524f) {
//				f26 = 0.524f;
//			}
//
//			xdiff = targetprop->pos.x - act->pos[i].x;
//			zdiff = targetprop->pos.z - act->pos[i].z;
//			f28 = M_BADTAU - atan2f(aimy - act->pos[i].y, sqrtf(xdiff * xdiff + zdiff * zdiff));
//
//			if (f28 > M_BADPI) {
//				f28 -= M_BADTAU;
//			}
//
//			if (f28 < -0.524f) {
//				f28 = -0.524f;
//			}
//
//			if (f28 > 0.524f) {
//				f28 = 0.524f;
//			}
//		}
//
//		chr->gunroty[i] += (f26 - chr->gunroty[i]) * 0.15f;
//		chr->gunrotx[i] += (f28 - chr->gunrotx[i]) * 0.15f;
//
//		if (!empty) {
//			if (firing) {
//				f24 = chr->gunrotx[i];
//				f20 = chr->gunroty[i];
//
//				if (f24 < 0.0f) {
//					f24 += M_BADTAU;
//				}
//
//				if (f20 < 0.0f) {
//					f20 += M_BADTAU;
//				}
//
//				f20 += invtheta;
//
//				if (f20 >= M_BADTAU) {
//					f20 -= M_BADTAU;
//				}
//
//				act->dir[i].x = sinf(f20) * cosf(f24);
//				act->dir[i].y = -sinf(f24);
//				act->dir[i].z = cosf(f20) * cosf(f24);
//
//				robotSetMuzzleFlash(chr, i, true);
//
//				act->numshots[i]--;
//			}
//
//			chr->unk348[i]->unk00++;
//		}
//	}
//}

void chrTickAttack(struct chrdata *chr)
{
	struct model *model = chr->model;
	f32 curframe = modelGetCurAnimFrame(model);

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		modelSetAnimation(model, chr->act_attack.animcfg->animnum, chr->act_attack.flip,
				chr->act_attack.animcfg->unk10, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);
		func0f031254(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (chr->act_attack.animcfg->animnum == ANIM_SNIPING_GETDOWN) {
		if (curframe >= modelGetAnimEndFrame(model)) {
			chr->act_attack.animcfg = var80067d70;

			modelSetAnimation(model, chr->act_attack.animcfg->animnum, chr->act_attack.flip,
					chr->act_attack.animcfg->unk10, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);
		}
	}

	if (!chr->aibot && chr->act_attack.reaim != 0) {
		if (chr->act_attack.reaim == 1) {
			f32 startframe;

			if (chr->act_attack.animcfg->unk24 >= 0) {
				startframe = chr->act_attack.animcfg->unk24;
			} else {
				startframe = chr->act_attack.animcfg->unk1c;
			}

			modelSetAnimation(model, modelGetAnimNum(model), model->anim->flip, startframe, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);

			if (chr->act_attack.animcfg->unk14 >= 0) {
				modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk14);
			}

			chr->act_attack.reaim = 2;
			chrResetAimEndProperties(chr);
			return;
		}

		if (chr->act_attack.reaim == 2) {
			if (curframe >= modelGetAnimEndFrame(model)) {
				chr->act_attack.flags &= ~ATTACKFLAG_DONTTURN;

				if (chr->act_attack.standing) {
					chrAttackStand(chr, chr->act_attack.flags, chr->act_attack.entityid);
				} else {
					chrAttackKneel(chr, chr->act_attack.flags, chr->act_attack.entityid);
				}
			}
			return;
		}
	}

	if (!chr->aibot && (chr->act_attack.flags & ATTACKFLAG_AIMONLY)) {
		if (chr->act_attack.flags & ATTACKFLAG_DONTTURN) {
			if (!func0f03e9f4(chr, chr->act_attack.animcfg, chr->act_attack.firegun[HAND_LEFT], chr->act_attack.firegun[HAND_RIGHT], 0.2f)) {
				chr->act_attack.reaim = 1;
			}
			return;
		}

		if (curframe >= modelGetAnimEndFrame(model)) {
			chr->act_attack.flags |= ATTACKFLAG_DONTTURN;
			chr->act_attack.turning = TURNSTATE_OFF;
			return;
		}
	}

	if (!chr->aibot
			&& chr->act_attack.dorecoil == 0
			&& chr->act_attack.animcfg->unk24 > 0
			&& curframe <= chr->act_attack.animcfg->unk24
			&& curframe >= modelGetAnimEndFrame(model)) {
		modelSetAnimation(model, modelGetAnimNum(model), model->anim->flip,
				chr->act_attack.animcfg->unk24, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);

		if (chr->act_attack.dooneburst) {
			if (chr->act_attack.animcfg->unk14 >= 0) {
				modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk14);
			}
		} else {
			modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk1c);
		}
	}

	chrTickFire(chr);
}

void chrTickAttackRoll(struct chrdata *chr)
{
	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrAttackRollChooseAnimation(chr);

		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	if (chr->act_attack.onehanded) {
		struct model *model = chr->model;
		f32 curframe = modelGetCurAnimFrame(model);

		if (chr->act_attack.animcfg == &g_RollAttackAnims[4]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[5]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[6]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[7]) {
			if (curframe >= chr->act_attack.animcfg->unk14) {
				struct attackanimconfig *newanimcfg = chr->act_attack.animcfg + 4;
				bool flip = model->anim->flip;
				f32 sp34 = 16;

				if (chr->act_attack.firegun[HAND_LEFT] && chr->act_attack.firegun[HAND_RIGHT]) {
					if (random() % 2 == 0) {
						newanimcfg += 4;
					} else {
						newanimcfg += 8;
					}
				}

				if (newanimcfg == &g_RollAttackAnims[8]) {
					sp34 = 24;
				} else if (newanimcfg == &g_RollAttackAnims[9]) {
					sp34 = 24;
				} else if (newanimcfg == &g_RollAttackAnims[10]) {
					sp34 = 32;
				} else if (newanimcfg == &g_RollAttackAnims[11]) {
					sp34 = 44;
				} else if (newanimcfg == &g_RollAttackAnims[12]) {
					sp34 = 24;
				} else if (newanimcfg == &g_RollAttackAnims[13]) {
					sp34 = 34;
				} else if (newanimcfg == &g_RollAttackAnims[14]) {
					sp34 = 32;
				} else if (newanimcfg == &g_RollAttackAnims[15]) {
					sp34 = 44;
				} else if (newanimcfg == &g_RollAttackAnims[16]) {
					sp34 = 24;
				} else if (newanimcfg == &g_RollAttackAnims[17]) {
					sp34 = 34;
				} else if (newanimcfg == &g_RollAttackAnims[18]) {
					sp34 = 32;
				} else if (newanimcfg == &g_RollAttackAnims[19]) {
					sp34 = 44;
				}

				chr->act_attack.turning = TURNSTATE_OFF;
				chr->act_attack.animcfg = newanimcfg;
				chr->sleep = 0;

				modelSetAnimation(model, newanimcfg->animnum, flip, newanimcfg->unk10,
						chrGetRangedSpeed(chr, 0.5f, 0.8f), sp34);

				if (chr->act_attack.dorecoil) {
					if (newanimcfg->unk24 >= 0.0f) {
						modelSetAnimEndFrame(model, newanimcfg->unk24);
					} else {
						modelSetAnimEndFrame(model, newanimcfg->unk1c);
					}
				} else {
					if (newanimcfg->unk20 >= 0.0f) {
						modelSetAnimEndFrame(model, newanimcfg->unk20);
					} else {
						if (newanimcfg->unk14 >= 0.0f) {
							modelSetAnimEndFrame(model, newanimcfg->unk14);
						}
					}
				}

				if (chr->act_attack.animcfg->unk0c != 0.0f) {
					union modelrwdata *rwdata = modelGetNodeRwData(model, model->filedata->rootnode);
					rwdata->chrinfo.unk5c = sp34;
					rwdata->chrinfo.unk58 = -chr->act_attack.animcfg->unk0c / sp34;

					if (flip) {
						rwdata->chrinfo.unk58 = -rwdata->chrinfo.unk58;
					}
				}
			}
		} else if (chr->act_attack.animcfg == &g_RollAttackAnims[8]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[9]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[10]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[11]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[12]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[13]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[14]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[15]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[16]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[17]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[18]
				|| chr->act_attack.animcfg == &g_RollAttackAnims[19]) {
			if (!chr->act_attack.dorecoil
					&& chr->act_attack.animcfg->unk24 > 0
					&& curframe <= chr->act_attack.animcfg->unk24
					&& curframe >= modelGetAnimEndFrame(model)) {
				modelSetAnimation(model, modelGetAnimNum(model), model->anim->flip,
						chr->act_attack.animcfg->unk24, chrGetRangedSpeed(chr, 0.5f, 0.8f), 16);

				if (chr->act_attack.dooneburst) {
					if (chr->act_attack.animcfg->unk14 >= 0) {
						modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk14);
					}
				} else {
					u32 stack;
					modelSetAnimEndFrame(model, chr->act_attack.animcfg->unk1c);
				}
			}
		}
	}

	chrTickFire(chr);
}

void propPrintDangerous(void)
{
	u8 i;

	osSyncPrintf("Current dangerous items:");

	for (i = 0; i < MAX_DANGEROUSPROPS; i++) {
		struct prop *prop = g_DangerousProps[i];

		if (prop) {
			if (prop->weapon
					&& prop->weapon->weaponnum == WEAPON_GRENADE
					&& prop->type == PROPTYPE_WEAPON) {
				osSyncPrintf("    Grenade %x", prop);
			} else if (prop->type == PROPTYPE_EXPLOSION) {
				osSyncPrintf("    Explosion %x", prop);
			} else {
				osSyncPrintf("misc dangerous prop");
			}
		}
	}
}

void propUnsetDangerous(struct prop *prop)
{
	s32 i;

	for (i = 0; i != MAX_DANGEROUSPROPS; i++) {
		if (g_DangerousProps[i] == prop) {
			g_DangerousProps[i] = NULL;
			return;
		}
	}
}

void propSetDangerous(struct prop *prop)
{
	s32 i;

	for (i = 0; i != MAX_DANGEROUSPROPS; i++) {
		if (g_DangerousProps[i] == NULL) {
			g_DangerousProps[i] = prop;
			return;
		}
	}
}

void chrTickThrowGrenade(struct chrdata *chr)
{
	struct model *model;
	f32 frame;
	u32 hand;
	struct prop *weaponprop;
	struct defaultobj *obj;
	struct weaponobj *weapon;
	f32 frame2;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrThrowGrenadeChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	model = chr->model;
	frame = modelGetCurAnimFrame(model);
	hand = model->anim->flip ? 1 : 0;
	weaponprop = chrGetHeldProp(chr, hand);

	if ((frame >= 20 && weaponprop && modelGetAnimNum(model) == ANIM_THROWGRENADE_STANDING) ||
			(frame >= 1 && weaponprop && modelGetAnimNum(model) == ANIM_THROWGRENADE_NOPIN) ||
			(frame >= 1 && weaponprop && modelGetAnimNum(model) == ANIM_THROWGRENADE_CROUCHING)) {
		obj = weaponprop->obj;
		obj->hidden &= ~OBJHFLAG_00000800;
	}

	if ((frame >= 119 && weaponprop && modelGetAnimNum(model) == ANIM_THROWGRENADE_STANDING) ||
			(frame >= 57 && weaponprop && modelGetAnimNum(model) == ANIM_THROWGRENADE_NOPIN) ||
			(frame >= 58 && weaponprop && modelGetAnimNum(model) == ANIM_THROWGRENADE_CROUCHING)) {
		weapon = weaponprop->weapon;
		objSetDropped(weaponprop, DROPTYPE_THROWGRENADE);
		chr->hidden |= CHRHFLAG_00000001;
		weapon->timer240 = PALDOWN(240);
	}

	frame2 = modelGetCurAnimFrame(model);

	if (frame2 >= modelGetAnimEndFrame(model)) {
		chrStop(chr);
	} else {
		if ((frame >= 87 && frame <= 110 && modelGetAnimNum(model) == ANIM_THROWGRENADE_STANDING) ||
				(frame >= 5 && frame <= 45 && modelGetAnimNum(model) == ANIM_THROWGRENADE_NOPIN) ||
				((frame >= 20 && frame <= 45 && modelGetAnimNum(model) == ANIM_THROWGRENADE_CROUCHING))) {
			f32 value = chrGetRangedSpeed(chr, 1, 3.2);
			chrTurn(chr, 1, 110, value, 0);
		}
	}
}

bool chrDetectDangerousObject(struct chrdata *chr, u8 flags)
{
	s32 i;

	for (i = 0; i != MAX_DANGEROUSPROPS; i++) {
		struct prop *prop = g_DangerousProps[i];
		bool pass = false;

		if (prop) {
			if ((flags & 1) && prop->weapon &&
					prop->weapon->weaponnum == WEAPON_GRENADE &&
					prop->weapon->timer240 < PALDOWN(480)) {
				pass = true;
			}

			if ((flags & 2) && prop->type == PROPTYPE_EXPLOSION) {
				pass = true;
			}

			if (pass && chrGetSquaredDistanceToCoord(chr, &prop->pos) < 1600) {
				chr->runfrompos.x = g_DangerousProps[i]->pos.x;
				chr->runfrompos.y = g_DangerousProps[i]->pos.y;
				chr->runfrompos.z = g_DangerousProps[i]->pos.z;

				if (chr->aibot) {
					chr->aibot->unk064 |= 0x0004;
					chr->aibot->dangerouspropnum = i;
				}

				return true;
			}
		}
	}

	if (chr->aibot) {
		chr->aibot->unk064 &= ~0x0004;
		chr->aibot->dangerouspropnum = -1;
	}

	return false;
}

void chrTickBondDie(struct chrdata *chr)
{
	// empty
}

#if VERSION >= VERSION_PAL_FINAL
const char var7f1a8ba0[] = "chr/chraction.c";
const char var7f1a8bac[] = "chr/chraction.c";
const char var7f1a8bb8[] = "chr/chraction.c";
const char var7f1a8bc4[] = "chr/chraction.c";
const char var7f1a8bd0[] = "chr/chraction.c";
const char var7f1a8bdc[] = "chr/chraction.c";
#else
const char var7f1a8ba0[] = "chraction.c";
const char var7f1a8bac[] = "chraction.c";
const char var7f1a8bb8[] = "chraction.c";
const char var7f1a8bc4[] = "chraction.c";
const char var7f1a8bd0[] = "chraction.c";
const char var7f1a8bdc[] = "chraction.c";
#endif

#if VERSION >=  VERSION_NTSC_1_0
const char var7f1a8be8[] = "CHARS -> FRAMETIMESCALEI(240)  = %d";
const char var7f1a8c0c[] = "CHARS -> numseenbond1      \t= %d/%d";
const char var7f1a8c30[] = "CHARS -> numseenbond2      \t= %d/%d";
const char var7f1a8c54[] = "CHARS -> numseenbond3      \t= %d/%d";
const char var7f1a8c78[] = "CHARS -> numseenbond       \t= %d/%d";
#endif

const char var7f1a8c9c[] = "CHARS -> DEAD = %d/%d";
const char var7f1a8cb4[] = "chrdisttopad : %x -> %d : Dist=%f";

bool func0f043f2c(struct chrdata *chr, struct coord *runpos, u32 arg2, f32 *turnspeed)
{
	struct prop *prop = chr->prop;
	struct model *model = chr->model;
	f32 accel;
	f32 maxspeed;
	f32 angle1;
	f32 finalangle;
	f32 angle2;
	f32 angle3;
	f32 xdiff = runpos->f[0] - prop->pos.f[0];
	f32 zdiff = runpos->f[2] - prop->pos.f[2];
	bool result;

	result = false;
	angle1 = atan2f(xdiff, zdiff);
	finalangle = func0f03e578(chr);
	angle2 = angle1 - finalangle;

	if (finalangle > angle1) {
		angle2 += M_BADTAU;
	}

	if (chr->aibot) {
		if (chr->blurdrugamount > 0) {
			angle1 += chr->blurdrugamount * PALUPF(0.00031410926021636f) * sinf((g_Vars.lvframe60 % PALDOWN(1200)) * PALUPF(0.0052351541817188f));

			if (angle1 >= M_BADTAU) {
				angle1 -= M_BADTAU;
			}

			angle1 += M_BADTAU;
		}

		finalangle = angle1;
		*turnspeed = 0;
		result = true;
	} else {
		angle3 = angle2;

		if (angle2 > M_BADPI) {
			angle3 = M_BADTAU - angle3;
		}

		if ((arg2 % 4) == 2) {
			maxspeed = 0.29915165901184f;
			accel = 0.014957583509386f;
		} else if ((arg2 % 4) == 1) {
			if (angle3 < 0.3926365673542f) {
				maxspeed = 0.019631829112768f;
			} else if (angle3 < 1.2564370632172f) {
				maxspeed = 0.098159141838551f;
			} else {
				maxspeed = 0.1963182836771f;
			}

			accel = 0.014957583509386f;
		} else {
			if (angle3 < 0.3926365673542f) {
				maxspeed = 0.0098159145563841f;
			} else if (angle3 < 1.2564370632172f) {
				maxspeed = 0.049079570919275f;
			} else {
				maxspeed = 0.12564370036125f;
			}

			accel = 0.0098159145563841f;
		}

		maxspeed *= model->anim->playspeed;
		accel *= model->anim->playspeed;

		applyRotation(&finalangle, angle1, turnspeed, accel, accel + accel, maxspeed);

		if (ABS(finalangle - angle1) < 0.01f) {
			*turnspeed = 0;
			result = true;
		}
	}

	func0f03e5b0(chr, finalangle);

	return result;
}

void chrTickAttackWalk(struct chrdata *chr)
{
	struct model *model = chr->model;
	struct prop *prop = chr->prop;
	struct prop *targetprop = chrGetTargetProp(chr);
	s32 i;
	f32 xdiff;
	f32 zdiff;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrAttackWalkChooseAnimation(chr);

		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	chr->act_attackwalk.frame60count += g_Vars.lvupdate240_60;
	chr->lastwalk60 = g_Vars.lvframe60;

	// If stuck or time exceeded, stop
	if (chr->invalidmove == 1
			|| chr->lastmoveok60 < g_Vars.lvframe60 - PALDOWN(60)
			|| chr->act_attackwalk.frame60count > chr->act_attackwalk.frame60max) {
		if (modelGetCurAnimFrame(model) > modelGetNumAnimFrames(model) * 0.5f) {
			modelSetAnimSpeedAuto(model, 0, 16);
		} else {
			modelSetAnimSpeedAuto(model, modelGetNumAnimFrames(model) * 0.5f, 16);
		}

		chrRecordLastSeeTargetTime(chr);
		chrStop(chr);
		return;
	}

	// If within 3 metres of the player, stop
	xdiff = targetprop->pos.x - prop->pos.x;
	zdiff = targetprop->pos.z - prop->pos.z;

	if (xdiff < 300 && xdiff > -300 && zdiff < 300 && zdiff > -300) {
		chrRecordLastSeeTargetTime(chr);
		chrStop(chr);
		return;
	}

	if (func0f043f2c(chr, &targetprop->pos, 0, &chr->act_attackwalk.turnspeed)) {
		chr->act_attackwalk.facedtarget = true;
	}

	if (chr->act_attackwalk.frame60count > PALDOWN(20)) {
		func0f03e9f4(chr, chr->act_attackwalk.animcfg,
				chr->act_attackwalk.firegun[HAND_LEFT],
				chr->act_attackwalk.firegun[HAND_RIGHT], 1);
	} else {
		chrResetAimEndProperties(chr);
	}

	if (chr->act_attackwalk.facedtarget && chr->act_attackwalk.frame60count > PALDOWN(30)) {
		for (i = 0; i < 2; i++) {
			if (chr->act_attackwalk.firegun[i]) {
				if (!chr->act_attackwalk.everytick[i]) {
					chrSetHandFiring(chr, i, true);
				} else if (chr->act_attackwalk.frame60count > chr->act_attackwalk.nextshot60
						&& (i == chr->act_attackwalk.nextgun || chr->act_attackwalk.everytick[chr->act_attackwalk.nextgun] == 0)) {
					chr->act_attackwalk.nextshot60 = chr->act_attackwalk.frame60count;

					if (chr->act_attackwalk.everytick[1 - i]) {
						if (chr->act_attackwalk.singleshot[i]) {
							chr->act_attackwalk.nextshot60 += PALDOWN(90);
						} else {
							chr->act_attackwalk.nextshot60 += PALDOWN(20);
						}
					} else {
						if (chr->act_attackwalk.singleshot[i]) {
							chr->act_attackwalk.nextshot60 += PALDOWN(180);
						} else {
							chr->act_attackwalk.nextshot60 += PALDOWN(40);
						}
					}

					chr->act_attackwalk.nextgun = 1 - chr->act_attackwalk.nextgun;

					chrSetHandFiring(chr, i, true);
				} else {
					chrSetHandFiring(chr, i, false);
				}
			} else {
				chrSetHandFiring(chr, i, false);
			}
		}
	} else {
		chrSetHandFiring(chr, HAND_LEFT, false);
		chrSetHandFiring(chr, HAND_RIGHT, false);
	}
}

/**
 * This function might be misnamed. It was named by isolating it and testing it
 * with different inputs to see what it returns, but I couldn't determine how
 * the range affects the latter part of the function.
 */
bool posIsMovingTowardsPosOrStoppedInRange(struct coord *prevpos, struct coord *moveddelta, struct coord *targetpos, f32 range)
{
	struct coord prevdist;
	f32 tmp;

	prevdist.x = targetpos->x - prevpos->x;
	prevdist.z = targetpos->z - prevpos->z;

	if (moveddelta->f[0] == 0 && moveddelta->f[2] == 0) {
		return prevdist.f[0] * prevdist.f[0] + prevdist.f[2] * prevdist.f[2] <= range * range;
	}

	tmp = moveddelta->f[0] * prevdist.f[0] + moveddelta->f[2] * prevdist.f[2];

	if (tmp > 0) {
		f32 sqmoveddist = moveddelta->f[0] * moveddelta->f[0] + moveddelta->f[2] * moveddelta->f[2];
		f32 sqprevdist = prevdist.f[0] * prevdist.f[0] + prevdist.f[2] * prevdist.f[2];

		if ((sqprevdist - range * range) * sqmoveddist <= tmp * tmp) {
			return true;
		}

		return false;
	}

	return false;
}

/**
 * Return true if:
 * - either prevpos or curpos is within the given range of targetpos, and
 * - the prev -> cur delta is moving towards the targetpos or is stopped inside
 *   the range.
 *
 * This is a lateral check, meaning the Y value is not considered.
 */
bool posIsArrivingLaterallyAtPos(struct coord *prevpos, struct coord *curpos, struct coord *targetpos, f32 range)
{
	struct coord moveddelta;

	if (prevpos->x <= targetpos->x - range && curpos->x <= targetpos->x - range) {
		return false;
	}

	if (prevpos->x >= targetpos->x + range && curpos->x >= targetpos->x + range) {
		return false;
	}

	if (prevpos->z <= targetpos->z - range && curpos->z <= targetpos->z - range) {
		return false;
	}

	if (prevpos->z >= targetpos->z + range && curpos->z >= targetpos->z + range) {
		return false;
	}

	moveddelta.x = curpos->x - prevpos->x;
	moveddelta.y = 0;
	moveddelta.z = curpos->z - prevpos->z;

	return posIsMovingTowardsPosOrStoppedInRange(prevpos, &moveddelta, targetpos, range);
}

/**
 * Return true if:
 * - either prevpos or curpos is within the given range of targetpos,
 * - the prev -> cur delta is moving towards the targetpos or is stopped inside
 *   the range, and
 * - either prevpos or curpos is within 150cm vertically of targetpos.
 */
bool posIsArrivingAtPos(struct coord *prevpos, struct coord *curpos, struct coord *targetpos, f32 range)
{
	if (prevpos->y <= targetpos->y - 150 && curpos->y <= targetpos->y - 150) {
		return false;
	}

	if (prevpos->y >= targetpos->y + 150 && curpos->y >= targetpos->y + 150) {
		return false;
	}

	return posIsArrivingLaterallyAtPos(prevpos, curpos, targetpos, range);
}

void chrTickRunPos(struct chrdata *chr)
{
	struct prop *prop = chr->prop;
	struct model *model = chr->model;
	u32 race = CHRRACE(chr);
	f32 fVar6;
	f32 zero;
	f32 fVar7;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrRunPosChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	chr->lastwalk60 = g_Vars.lvframe60;

	if (chr->invalidmove == 1
			|| g_Vars.lvframe60 - PALDOWN(60) > chr->lastmoveok60
			|| posIsArrivingLaterallyAtPos(&chr->prevpos, &prop->pos, &chr->act_runpos.pos, chr->act_runpos.neardist)) {
		if (race == RACE_HUMAN) {
			modelGetAnimNum(model);
		}

		zero = 0;
		fVar7 = modelGetCurAnimFrame(model);
		fVar6 = fVar7 - zero;

		if (fVar7 < 0) {
			fVar6 += modelGetNumAnimFrames(model);
		}

		if (modelGetNumAnimFrames(model) * 0.5f < fVar6) {
			zero = 0;
			modelSetAnimSpeedAuto(model, modelGetNumAnimFrames(model) - zero, 16);
		} else {
			zero = 0;
			fVar7 = modelGetNumAnimFrames(model) * 0.5f;
			fVar6 = fVar7 - zero;

			if (fVar7 < 0) {
				fVar6 += modelGetNumAnimFrames(model);
			}

			modelSetAnimSpeedAuto(model, fVar6, 16);
		}

		chrStop(chr);
		return;
	}

	func0f043f2c(chr, &chr->act_runpos.pos, 1, &chr->act_runpos.turnspeed);

	if (chr->act_runpos.eta60 > 0) {
		chr->act_runpos.eta60 -= g_Vars.lvupdate240_60;
	} else {
		fVar7 = 1;

		if (race == RACE_HUMAN) {
			if (modelGetAnimNum(model) == ANIM_RUNNING_ONEHANDGUN) {
				fVar7 = func0f02dff0(ANIM_RUNNING_ONEHANDGUN);
			} else {
				fVar7 = func0f02dff0(ANIM_RUNNING_TWOHANDGUN);
			}
		} else if (race == RACE_SKEDAR) {
			fVar7 = func0f02dff0(ANIM_SKEDAR_RUNNING);
		}

		chr->act_runpos.neardist += fVar7 * g_Vars.lvupdate240freal * modelGetAbsAnimSpeed(model);
	}
}

void func0f044b68(struct coord *arg0, struct coord *arg1, struct coord *arg2)
{
	struct coord sp0c;
	struct coord sp00;

	sp0c.x = arg1->x - arg0->x;
	sp0c.y = arg1->y - arg0->y;
	sp0c.z = arg1->z - arg0->z;

	sp00.x = -arg2->z;
	sp00.y = 0;
	sp00.z = arg2->x;

	if (sp00.f[0] * sp0c.f[0] + sp00.f[2] * sp0c.f[2] > 0) {
		// empty
	} else {
		sp0c.x = arg0->x;
		sp0c.y = arg0->y;
		sp0c.z = arg0->z;

		arg0->x = arg1->x;
		arg0->y = arg1->y;
		arg0->z = arg1->z;

		arg1->x = sp0c.x;
		arg1->y = sp0c.y;
		arg1->z = sp0c.z;
	}
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f044c38
.late_rodata
glabel var7f1a9238
.word 0x3f733333
glabel var7f1a923c
.word 0x3f733333
glabel var7f1a9240
.word 0x3f99999a
glabel var7f1a9244
.word 0x3f99999a
.text
/*  f044c38:	27bdff20 */ 	addiu	$sp,$sp,-224
/*  f044c3c:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f044c40:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f044c44:	afa400e0 */ 	sw	$a0,0xe0($sp)
/*  f044c48:	afa600e8 */ 	sw	$a2,0xe8($sp)
/*  f044c4c:	afa700ec */ 	sw	$a3,0xec($sp)
/*  f044c50:	afa000bc */ 	sw	$zero,0xbc($sp)
/*  f044c54:	afa000b8 */ 	sw	$zero,0xb8($sp)
/*  f044c58:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f044c5c:	8c84001c */ 	lw	$a0,0x1c($a0)
/*  f044c60:	00a08025 */ 	or	$s0,$a1,$zero
/*  f044c64:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f044c68:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f044c6c:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f044c70:	0fc0a277 */ 	jal	chrGetBbox
/*  f044c74:	afa4003c */ 	sw	$a0,0x3c($sp)
/*  f044c78:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044c7c:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f044c80:	44800000 */ 	mtc1	$zero,$f0
/*  f044c84:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f044c88:	e7a000d8 */ 	swc1	$f0,0xd8($sp)
/*  f044c8c:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f044c90:	e7a800d4 */ 	swc1	$f8,0xd4($sp)
/*  f044c94:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f044c98:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f044c9c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f044ca0:	46080032 */ 	c.eq.s	$f0,$f8
/*  f044ca4:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f044ca8:	45000008 */ 	bc1f	.L0f044ccc
/*  f044cac:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f044cb0:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cb4:	46120032 */ 	c.eq.s	$f0,$f18
/*  f044cb8:	00000000 */ 	nop
/*  f044cbc:	45020004 */ 	bc1fl	.L0f044cd0
/*  f044cc0:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cc4:	10000133 */ 	b	.L0f045194
/*  f044cc8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f044ccc:
/*  f044ccc:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
.L0f044cd0:
/*  f044cd0:	c7b000d4 */ 	lwc1	$f16,0xd4($sp)
/*  f044cd4:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f044cd8:	00000000 */ 	nop
/*  f044cdc:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f044ce0:	0c012974 */ 	jal	sqrtf
/*  f044ce4:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f044ce8:	3c013f80 */ 	lui	$at,0x3f80
/*  f044cec:	44813000 */ 	mtc1	$at,$f6
/*  f044cf0:	c7b000d4 */ 	lwc1	$f16,0xd4($sp)
/*  f044cf4:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cf8:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f044cfc:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*  f044d00:	3c017f1b */ 	lui	$at,%hi(var7f1a9238)
/*  f044d04:	c42a9238 */ 	lwc1	$f10,%lo(var7f1a9238)($at)
/*  f044d08:	3c017f1b */ 	lui	$at,%hi(var7f1a923c)
/*  f044d0c:	c426923c */ 	lwc1	$f6,%lo(var7f1a923c)($at)
/*  f044d10:	3c017f1b */ 	lui	$at,%hi(var7f1a9240)
/*  f044d14:	8fa400e0 */ 	lw	$a0,0xe0($sp)
/*  f044d18:	00002825 */ 	or	$a1,$zero,$zero
/*  f044d1c:	46028402 */ 	mul.s	$f16,$f16,$f2
/*  f044d20:	00000000 */ 	nop
/*  f044d24:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f044d28:	00000000 */ 	nop
/*  f044d2c:	46088302 */ 	mul.s	$f12,$f16,$f8
/*  f044d30:	e7b000d4 */ 	swc1	$f16,0xd4($sp)
/*  f044d34:	e7b200dc */ 	swc1	$f18,0xdc($sp)
/*  f044d38:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f044d3c:	00000000 */ 	nop
/*  f044d40:	46089382 */ 	mul.s	$f14,$f18,$f8
/*  f044d44:	e7a400d0 */ 	swc1	$f4,0xd0($sp)
/*  f044d48:	c4249240 */ 	lwc1	$f4,%lo(var7f1a9240)($at)
/*  f044d4c:	3c017f1b */ 	lui	$at,%hi(var7f1a9244)
/*  f044d50:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f044d54:	c4269244 */ 	lwc1	$f6,%lo(var7f1a9244)($at)
/*  f044d58:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f044d5c:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f044d60:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f044d64:	e7a800c8 */ 	swc1	$f8,0xc8($sp)
/*  f044d68:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f044d6c:	e7aa00c4 */ 	swc1	$f10,0xc4($sp)
/*  f044d70:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f044d74:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f044d78:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044d7c:	c7a200f8 */ 	lwc1	$f2,0xf8($sp)
/*  f044d80:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f044d84:	c7a800d0 */ 	lwc1	$f8,0xd0($sp)
/*  f044d88:	8faf0100 */ 	lw	$t7,0x100($sp)
/*  f044d8c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f044d90:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f044d94:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f044d98:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f044d9c:	02002025 */ 	or	$a0,$s0,$zero
/*  f044da0:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f044da4:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f044da8:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044dac:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f044db0:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f044db4:	c7a400c4 */ 	lwc1	$f4,0xc4($sp)
/*  f044db8:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f044dbc:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f044dc0:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f044dc4:	c7a600d4 */ 	lwc1	$f6,0xd4($sp)
/*  f044dc8:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f044dcc:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f044dd0:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f044dd4:	c7a800c8 */ 	lwc1	$f8,0xc8($sp)
/*  f044dd8:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f044ddc:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f044de0:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f044de4:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f044de8:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f044dec:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f044df0:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f044df4:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f044df8:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f044dfc:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f044e00:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f044e04:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f044e08:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f044e0c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f044e10:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044e14:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044e18:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f044e1c:	0c00b694 */ 	jal	cd0002da50
/*  f044e20:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f044e24:	10400010 */ 	beqz	$v0,.L0f044e68
/*  f044e28:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f044e2c:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*  f044e30:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f044e34:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f044e38:	c520000c */ 	lwc1	$f0,0xc($t1)
/*  f044e3c:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f044e40:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f044e44:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044e48:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f044e4c:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f044e50:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044e54:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f044e58:	8fa70100 */ 	lw	$a3,0x100($sp)
/*  f044e5c:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f044e60:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f044e64:	1440000c */ 	bnez	$v0,.L0f044e98
.L0f044e68:
/*  f044e68:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f044e6c:	3c077f1b */ 	lui	$a3,%hi(var7f1a8ba0)
/*  f044e70:	afaa00bc */ 	sw	$t2,0xbc($sp)
/*  f044e74:	24e78ba0 */ 	addiu	$a3,$a3,%lo(var7f1a8ba0)
/*  f044e78:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044e7c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f044e80:	0c009393 */ 	jal	cd00024e4c
/*  f044e84:	24063741 */ 	addiu	$a2,$zero,0x3747
/*  f044e88:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044e8c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f044e90:	0fc112da */ 	jal	func0f044b68
/*  f044e94:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f044e98:
/*  f044e98:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f044e9c:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f044ea0:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044ea4:	c7a200f8 */ 	lwc1	$f2,0xf8($sp)
/*  f044ea8:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f044eac:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f044eb0:	8fab0100 */ 	lw	$t3,0x100($sp)
/*  f044eb4:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f044eb8:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f044ebc:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f044ec0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f044ec4:	02002025 */ 	or	$a0,$s0,$zero
/*  f044ec8:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f044ecc:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f044ed0:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044ed4:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f044ed8:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f044edc:	c7a600c4 */ 	lwc1	$f6,0xc4($sp)
/*  f044ee0:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f044ee4:	e7a40074 */ 	swc1	$f4,0x74($sp)
/*  f044ee8:	c4480000 */ 	lwc1	$f8,0x0($v0)
/*  f044eec:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f044ef0:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f044ef4:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f044ef8:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f044efc:	c7aa00c8 */ 	lwc1	$f10,0xc8($sp)
/*  f044f00:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f044f04:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f044f08:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f044f0c:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f044f10:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f044f14:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f044f18:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f044f1c:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f044f20:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f044f24:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f044f28:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f044f2c:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f044f30:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f044f34:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f044f38:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044f3c:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044f40:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f044f44:	0c00b694 */ 	jal	cd0002da50
/*  f044f48:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f044f4c:	10400010 */ 	beqz	$v0,.L0f044f90
/*  f044f50:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f044f54:	8faf003c */ 	lw	$t7,0x3c($sp)
/*  f044f58:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f044f5c:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f044f60:	c5e0000c */ 	lwc1	$f0,0xc($t7)
/*  f044f64:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f044f68:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f044f6c:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044f70:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044f74:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f044f78:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044f7c:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f044f80:	8fa70100 */ 	lw	$a3,0x100($sp)
/*  f044f84:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f044f88:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f044f8c:	1440000c */ 	bnez	$v0,.L0f044fc0
.L0f044f90:
/*  f044f90:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f044f94:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bac)
/*  f044f98:	afb800b8 */ 	sw	$t8,0xb8($sp)
/*  f044f9c:	24e78bac */ 	addiu	$a3,$a3,%lo(var7f1a8bac)
/*  f044fa0:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f044fa4:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044fa8:	0c009393 */ 	jal	cd00024e4c
/*  f044fac:	24063750 */ 	addiu	$a2,$zero,0x3756
/*  f044fb0:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f044fb4:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044fb8:	0fc112da */ 	jal	func0f044b68
/*  f044fbc:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f044fc0:
/*  f044fc0:	8fb900bc */ 	lw	$t9,0xbc($sp)
/*  f044fc4:	8fa800b8 */ 	lw	$t0,0xb8($sp)
/*  f044fc8:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*  f044fcc:	13200019 */ 	beqz	$t9,.L0f045034
/*  f044fd0:	00000000 */ 	nop
/*  f044fd4:	11000017 */ 	beqz	$t0,.L0f045034
/*  f044fd8:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044fdc:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f044fe0:	0fc112da */ 	jal	func0f044b68
/*  f044fe4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f044fe8:	27a400a0 */ 	addiu	$a0,$sp,0xa0
/*  f044fec:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044ff0:	0fc112da */ 	jal	func0f044b68
/*  f044ff4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f044ff8:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f044ffc:	c7a400ac */ 	lwc1	$f4,0xac($sp)
/*  f045000:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045004:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045008:	c7a800b0 */ 	lwc1	$f8,0xb0($sp)
/*  f04500c:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045010:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f045014:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f045018:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f04501c:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f045020:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f045024:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f045028:	c7a80090 */ 	lwc1	$f8,0x90($sp)
/*  f04502c:	10000055 */ 	b	.L0f045184
/*  f045030:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f045034:
/*  f045034:	11200010 */ 	beqz	$t1,.L0f045078
/*  f045038:	8faa00b8 */ 	lw	$t2,0xb8($sp)
/*  f04503c:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045040:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f045044:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045048:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f04504c:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f045050:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f045054:	c7a400b4 */ 	lwc1	$f4,0xb4($sp)
/*  f045058:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f04505c:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f045060:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f045064:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f045068:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f04506c:	c7aa00a8 */ 	lwc1	$f10,0xa8($sp)
/*  f045070:	10000044 */ 	b	.L0f045184
/*  f045074:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f045078:
/*  f045078:	11400010 */ 	beqz	$t2,.L0f0450bc
/*  f04507c:	8fab0100 */ 	lw	$t3,0x100($sp)
/*  f045080:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045084:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f045088:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f04508c:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045090:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f045094:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045098:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f04509c:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f0450a0:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f0450a4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f0450a8:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f0450ac:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f0450b0:	c7a80090 */ 	lwc1	$f8,0x90($sp)
/*  f0450b4:	10000033 */ 	b	.L0f045184
/*  f0450b8:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f0450bc:
/*  f0450bc:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f0450c0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0450c4:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f0450c8:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0450cc:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f0450d0:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0450d4:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0450d8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0450dc:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0450e0:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f0450e4:	8fa600ec */ 	lw	$a2,0xec($sp)
/*  f0450e8:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0450ec:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0450f0:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0450f4:	0c00b694 */ 	jal	cd0002da50
/*  f0450f8:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0450fc:	10400017 */ 	beqz	$v0,.L0f04515c
/*  f045100:	8fae0104 */ 	lw	$t6,0x104($sp)
/*  f045104:	11c00012 */ 	beqz	$t6,.L0f045150
/*  f045108:	8faf0100 */ 	lw	$t7,0x100($sp)
/*  f04510c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f045110:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f045114:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f045118:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f04511c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f045120:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f045124:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045128:	02002025 */ 	or	$a0,$s0,$zero
/*  f04512c:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045130:	8fa500ec */ 	lw	$a1,0xec($sp)
/*  f045134:	8fa600fc */ 	lw	$a2,0xfc($sp)
/*  f045138:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f04513c:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045140:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f045144:	0c00a9bf */ 	jal	cd0002a6fc
/*  f045148:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f04514c:	10400003 */ 	beqz	$v0,.L0f04515c
.L0f045150:
/*  f045150:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f045154:	1000000b */ 	b	.L0f045184
/*  f045158:	afa80084 */ 	sw	$t0,0x84($sp)
.L0f04515c:
/*  f04515c:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bb8)
/*  f045160:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045164:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045168:	24e78bb8 */ 	addiu	$a3,$a3,%lo(var7f1a8bb8)
/*  f04516c:	0c009393 */ 	jal	cd00024e4c
/*  f045170:	24063796 */ 	addiu	$a2,$zero,0x379c
/*  f045174:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045178:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f04517c:	0fc112da */ 	jal	func0f044b68
/*  f045180:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f045184:
/*  f045184:	8fa400e0 */ 	lw	$a0,0xe0($sp)
/*  f045188:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f04518c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f045190:	8fa20084 */ 	lw	$v0,0x84($sp)
.L0f045194:
/*  f045194:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045198:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f04519c:	27bd00e0 */ 	addiu	$sp,$sp,0xe0
/*  f0451a0:	03e00008 */ 	jr	$ra
/*  f0451a4:	00000000 */ 	nop
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f044c38
.late_rodata
glabel var7f1a9238
.word 0x3f733333
glabel var7f1a923c
.word 0x3f733333
glabel var7f1a9240
.word 0x3f99999a
glabel var7f1a9244
.word 0x3f99999a
.text
/*  f044c38:	27bdff20 */ 	addiu	$sp,$sp,-224
/*  f044c3c:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f044c40:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f044c44:	afa400e0 */ 	sw	$a0,0xe0($sp)
/*  f044c48:	afa600e8 */ 	sw	$a2,0xe8($sp)
/*  f044c4c:	afa700ec */ 	sw	$a3,0xec($sp)
/*  f044c50:	afa000bc */ 	sw	$zero,0xbc($sp)
/*  f044c54:	afa000b8 */ 	sw	$zero,0xb8($sp)
/*  f044c58:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f044c5c:	8c84001c */ 	lw	$a0,0x1c($a0)
/*  f044c60:	00a08025 */ 	or	$s0,$a1,$zero
/*  f044c64:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f044c68:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f044c6c:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f044c70:	0fc0a277 */ 	jal	chrGetBbox
/*  f044c74:	afa4003c */ 	sw	$a0,0x3c($sp)
/*  f044c78:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044c7c:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f044c80:	44800000 */ 	mtc1	$zero,$f0
/*  f044c84:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f044c88:	e7a000d8 */ 	swc1	$f0,0xd8($sp)
/*  f044c8c:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f044c90:	e7a800d4 */ 	swc1	$f8,0xd4($sp)
/*  f044c94:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f044c98:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f044c9c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f044ca0:	46080032 */ 	c.eq.s	$f0,$f8
/*  f044ca4:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f044ca8:	45000008 */ 	bc1f	.L0f044ccc
/*  f044cac:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f044cb0:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cb4:	46120032 */ 	c.eq.s	$f0,$f18
/*  f044cb8:	00000000 */ 	nop
/*  f044cbc:	45020004 */ 	bc1fl	.L0f044cd0
/*  f044cc0:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cc4:	10000133 */ 	b	.L0f045194
/*  f044cc8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f044ccc:
/*  f044ccc:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
.L0f044cd0:
/*  f044cd0:	c7b000d4 */ 	lwc1	$f16,0xd4($sp)
/*  f044cd4:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f044cd8:	00000000 */ 	nop
/*  f044cdc:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f044ce0:	0c012974 */ 	jal	sqrtf
/*  f044ce4:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f044ce8:	3c013f80 */ 	lui	$at,0x3f80
/*  f044cec:	44813000 */ 	mtc1	$at,$f6
/*  f044cf0:	c7b000d4 */ 	lwc1	$f16,0xd4($sp)
/*  f044cf4:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cf8:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f044cfc:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*  f044d00:	3c017f1b */ 	lui	$at,%hi(var7f1a9238)
/*  f044d04:	c42a9238 */ 	lwc1	$f10,%lo(var7f1a9238)($at)
/*  f044d08:	3c017f1b */ 	lui	$at,%hi(var7f1a923c)
/*  f044d0c:	c426923c */ 	lwc1	$f6,%lo(var7f1a923c)($at)
/*  f044d10:	3c017f1b */ 	lui	$at,%hi(var7f1a9240)
/*  f044d14:	8fa400e0 */ 	lw	$a0,0xe0($sp)
/*  f044d18:	00002825 */ 	or	$a1,$zero,$zero
/*  f044d1c:	46028402 */ 	mul.s	$f16,$f16,$f2
/*  f044d20:	00000000 */ 	nop
/*  f044d24:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f044d28:	00000000 */ 	nop
/*  f044d2c:	46088302 */ 	mul.s	$f12,$f16,$f8
/*  f044d30:	e7b000d4 */ 	swc1	$f16,0xd4($sp)
/*  f044d34:	e7b200dc */ 	swc1	$f18,0xdc($sp)
/*  f044d38:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f044d3c:	00000000 */ 	nop
/*  f044d40:	46089382 */ 	mul.s	$f14,$f18,$f8
/*  f044d44:	e7a400d0 */ 	swc1	$f4,0xd0($sp)
/*  f044d48:	c4249240 */ 	lwc1	$f4,%lo(var7f1a9240)($at)
/*  f044d4c:	3c017f1b */ 	lui	$at,%hi(var7f1a9244)
/*  f044d50:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f044d54:	c4269244 */ 	lwc1	$f6,%lo(var7f1a9244)($at)
/*  f044d58:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f044d5c:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f044d60:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f044d64:	e7a800c8 */ 	swc1	$f8,0xc8($sp)
/*  f044d68:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f044d6c:	e7aa00c4 */ 	swc1	$f10,0xc4($sp)
/*  f044d70:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f044d74:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f044d78:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044d7c:	c7a200f8 */ 	lwc1	$f2,0xf8($sp)
/*  f044d80:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f044d84:	c7a800d0 */ 	lwc1	$f8,0xd0($sp)
/*  f044d88:	8faf0100 */ 	lw	$t7,0x100($sp)
/*  f044d8c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f044d90:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f044d94:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f044d98:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f044d9c:	02002025 */ 	or	$a0,$s0,$zero
/*  f044da0:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f044da4:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f044da8:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044dac:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f044db0:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f044db4:	c7a400c4 */ 	lwc1	$f4,0xc4($sp)
/*  f044db8:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f044dbc:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f044dc0:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f044dc4:	c7a600d4 */ 	lwc1	$f6,0xd4($sp)
/*  f044dc8:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f044dcc:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f044dd0:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f044dd4:	c7a800c8 */ 	lwc1	$f8,0xc8($sp)
/*  f044dd8:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f044ddc:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f044de0:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f044de4:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f044de8:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f044dec:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f044df0:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f044df4:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f044df8:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f044dfc:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f044e00:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f044e04:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f044e08:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f044e0c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f044e10:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044e14:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044e18:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f044e1c:	0c00b694 */ 	jal	cd0002da50
/*  f044e20:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f044e24:	10400010 */ 	beqz	$v0,.L0f044e68
/*  f044e28:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f044e2c:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*  f044e30:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f044e34:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f044e38:	c520000c */ 	lwc1	$f0,0xc($t1)
/*  f044e3c:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f044e40:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f044e44:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044e48:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f044e4c:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f044e50:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044e54:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f044e58:	8fa70100 */ 	lw	$a3,0x100($sp)
/*  f044e5c:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f044e60:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f044e64:	1440000c */ 	bnez	$v0,.L0f044e98
.L0f044e68:
/*  f044e68:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f044e6c:	3c077f1b */ 	lui	$a3,%hi(var7f1a8ba0)
/*  f044e70:	afaa00bc */ 	sw	$t2,0xbc($sp)
/*  f044e74:	24e78ba0 */ 	addiu	$a3,$a3,%lo(var7f1a8ba0)
/*  f044e78:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044e7c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f044e80:	0c009393 */ 	jal	cd00024e4c
/*  f044e84:	24063741 */ 	addiu	$a2,$zero,0x3741
/*  f044e88:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044e8c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f044e90:	0fc112da */ 	jal	func0f044b68
/*  f044e94:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f044e98:
/*  f044e98:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f044e9c:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f044ea0:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044ea4:	c7a200f8 */ 	lwc1	$f2,0xf8($sp)
/*  f044ea8:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f044eac:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f044eb0:	8fab0100 */ 	lw	$t3,0x100($sp)
/*  f044eb4:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f044eb8:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f044ebc:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f044ec0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f044ec4:	02002025 */ 	or	$a0,$s0,$zero
/*  f044ec8:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f044ecc:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f044ed0:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044ed4:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f044ed8:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f044edc:	c7a600c4 */ 	lwc1	$f6,0xc4($sp)
/*  f044ee0:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f044ee4:	e7a40074 */ 	swc1	$f4,0x74($sp)
/*  f044ee8:	c4480000 */ 	lwc1	$f8,0x0($v0)
/*  f044eec:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f044ef0:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f044ef4:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f044ef8:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f044efc:	c7aa00c8 */ 	lwc1	$f10,0xc8($sp)
/*  f044f00:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f044f04:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f044f08:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f044f0c:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f044f10:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f044f14:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f044f18:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f044f1c:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f044f20:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f044f24:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f044f28:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f044f2c:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f044f30:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f044f34:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f044f38:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044f3c:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044f40:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f044f44:	0c00b694 */ 	jal	cd0002da50
/*  f044f48:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f044f4c:	10400010 */ 	beqz	$v0,.L0f044f90
/*  f044f50:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f044f54:	8faf003c */ 	lw	$t7,0x3c($sp)
/*  f044f58:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f044f5c:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f044f60:	c5e0000c */ 	lwc1	$f0,0xc($t7)
/*  f044f64:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f044f68:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f044f6c:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044f70:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044f74:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f044f78:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044f7c:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f044f80:	8fa70100 */ 	lw	$a3,0x100($sp)
/*  f044f84:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f044f88:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f044f8c:	1440000c */ 	bnez	$v0,.L0f044fc0
.L0f044f90:
/*  f044f90:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f044f94:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bac)
/*  f044f98:	afb800b8 */ 	sw	$t8,0xb8($sp)
/*  f044f9c:	24e78bac */ 	addiu	$a3,$a3,%lo(var7f1a8bac)
/*  f044fa0:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f044fa4:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044fa8:	0c009393 */ 	jal	cd00024e4c
/*  f044fac:	24063750 */ 	addiu	$a2,$zero,0x3750
/*  f044fb0:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f044fb4:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044fb8:	0fc112da */ 	jal	func0f044b68
/*  f044fbc:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f044fc0:
/*  f044fc0:	8fb900bc */ 	lw	$t9,0xbc($sp)
/*  f044fc4:	8fa800b8 */ 	lw	$t0,0xb8($sp)
/*  f044fc8:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*  f044fcc:	13200019 */ 	beqz	$t9,.L0f045034
/*  f044fd0:	00000000 */ 	nop
/*  f044fd4:	11000017 */ 	beqz	$t0,.L0f045034
/*  f044fd8:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044fdc:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f044fe0:	0fc112da */ 	jal	func0f044b68
/*  f044fe4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f044fe8:	27a400a0 */ 	addiu	$a0,$sp,0xa0
/*  f044fec:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044ff0:	0fc112da */ 	jal	func0f044b68
/*  f044ff4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f044ff8:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f044ffc:	c7a400ac */ 	lwc1	$f4,0xac($sp)
/*  f045000:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045004:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045008:	c7a800b0 */ 	lwc1	$f8,0xb0($sp)
/*  f04500c:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045010:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f045014:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f045018:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f04501c:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f045020:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f045024:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f045028:	c7a80090 */ 	lwc1	$f8,0x90($sp)
/*  f04502c:	10000055 */ 	b	.L0f045184
/*  f045030:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f045034:
/*  f045034:	11200010 */ 	beqz	$t1,.L0f045078
/*  f045038:	8faa00b8 */ 	lw	$t2,0xb8($sp)
/*  f04503c:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045040:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f045044:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045048:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f04504c:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f045050:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f045054:	c7a400b4 */ 	lwc1	$f4,0xb4($sp)
/*  f045058:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f04505c:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f045060:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f045064:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f045068:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f04506c:	c7aa00a8 */ 	lwc1	$f10,0xa8($sp)
/*  f045070:	10000044 */ 	b	.L0f045184
/*  f045074:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f045078:
/*  f045078:	11400010 */ 	beqz	$t2,.L0f0450bc
/*  f04507c:	8fab0100 */ 	lw	$t3,0x100($sp)
/*  f045080:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045084:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f045088:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f04508c:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045090:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f045094:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045098:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f04509c:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f0450a0:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f0450a4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f0450a8:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f0450ac:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f0450b0:	c7a80090 */ 	lwc1	$f8,0x90($sp)
/*  f0450b4:	10000033 */ 	b	.L0f045184
/*  f0450b8:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f0450bc:
/*  f0450bc:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f0450c0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0450c4:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f0450c8:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0450cc:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f0450d0:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0450d4:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0450d8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0450dc:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0450e0:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f0450e4:	8fa600ec */ 	lw	$a2,0xec($sp)
/*  f0450e8:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0450ec:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0450f0:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0450f4:	0c00b694 */ 	jal	cd0002da50
/*  f0450f8:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0450fc:	10400017 */ 	beqz	$v0,.L0f04515c
/*  f045100:	8fae0104 */ 	lw	$t6,0x104($sp)
/*  f045104:	11c00012 */ 	beqz	$t6,.L0f045150
/*  f045108:	8faf0100 */ 	lw	$t7,0x100($sp)
/*  f04510c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f045110:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f045114:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f045118:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f04511c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f045120:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f045124:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045128:	02002025 */ 	or	$a0,$s0,$zero
/*  f04512c:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045130:	8fa500ec */ 	lw	$a1,0xec($sp)
/*  f045134:	8fa600fc */ 	lw	$a2,0xfc($sp)
/*  f045138:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f04513c:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045140:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f045144:	0c00a9bf */ 	jal	cd0002a6fc
/*  f045148:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f04514c:	10400003 */ 	beqz	$v0,.L0f04515c
.L0f045150:
/*  f045150:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f045154:	1000000b */ 	b	.L0f045184
/*  f045158:	afa80084 */ 	sw	$t0,0x84($sp)
.L0f04515c:
/*  f04515c:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bb8)
/*  f045160:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045164:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045168:	24e78bb8 */ 	addiu	$a3,$a3,%lo(var7f1a8bb8)
/*  f04516c:	0c009393 */ 	jal	cd00024e4c
/*  f045170:	24063796 */ 	addiu	$a2,$zero,0x3796
/*  f045174:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045178:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f04517c:	0fc112da */ 	jal	func0f044b68
/*  f045180:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f045184:
/*  f045184:	8fa400e0 */ 	lw	$a0,0xe0($sp)
/*  f045188:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f04518c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f045190:	8fa20084 */ 	lw	$v0,0x84($sp)
.L0f045194:
/*  f045194:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045198:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f04519c:	27bd00e0 */ 	addiu	$sp,$sp,0xe0
/*  f0451a0:	03e00008 */ 	jr	$ra
/*  f0451a4:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0f044c38
.late_rodata
glabel var7f1a9238
.word 0x3f733333
glabel var7f1a923c
.word 0x3f733333
glabel var7f1a9240
.word 0x3f99999a
glabel var7f1a9244
.word 0x3f99999a
.text
/*  f044c38:	27bdff20 */ 	addiu	$sp,$sp,-224
/*  f044c3c:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f044c40:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f044c44:	afa400e0 */ 	sw	$a0,0xe0($sp)
/*  f044c48:	afa600e8 */ 	sw	$a2,0xe8($sp)
/*  f044c4c:	afa700ec */ 	sw	$a3,0xec($sp)
/*  f044c50:	afa000bc */ 	sw	$zero,0xbc($sp)
/*  f044c54:	afa000b8 */ 	sw	$zero,0xb8($sp)
/*  f044c58:	afa00084 */ 	sw	$zero,0x84($sp)
/*  f044c5c:	8c84001c */ 	lw	$a0,0x1c($a0)
/*  f044c60:	00a08025 */ 	or	$s0,$a1,$zero
/*  f044c64:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f044c68:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f044c6c:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f044c70:	0fc0a277 */ 	jal	chrGetBbox
/*  f044c74:	afa4003c */ 	sw	$a0,0x3c($sp)
/*  f044c78:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044c7c:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f044c80:	44800000 */ 	mtc1	$zero,$f0
/*  f044c84:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f044c88:	e7a000d8 */ 	swc1	$f0,0xd8($sp)
/*  f044c8c:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f044c90:	e7a800d4 */ 	swc1	$f8,0xd4($sp)
/*  f044c94:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f044c98:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f044c9c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f044ca0:	46080032 */ 	c.eq.s	$f0,$f8
/*  f044ca4:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f044ca8:	45000008 */ 	bc1f	.L0f044ccc
/*  f044cac:	e7a600dc */ 	swc1	$f6,0xdc($sp)
/*  f044cb0:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cb4:	46120032 */ 	c.eq.s	$f0,$f18
/*  f044cb8:	00000000 */ 	nop
/*  f044cbc:	45020004 */ 	bc1fl	.L0f044cd0
/*  f044cc0:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cc4:	10000133 */ 	b	.L0f045194
/*  f044cc8:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f044ccc:
/*  f044ccc:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
.L0f044cd0:
/*  f044cd0:	c7b000d4 */ 	lwc1	$f16,0xd4($sp)
/*  f044cd4:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f044cd8:	00000000 */ 	nop
/*  f044cdc:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f044ce0:	0c012974 */ 	jal	sqrtf
/*  f044ce4:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f044ce8:	3c013f80 */ 	lui	$at,0x3f80
/*  f044cec:	44813000 */ 	mtc1	$at,$f6
/*  f044cf0:	c7b000d4 */ 	lwc1	$f16,0xd4($sp)
/*  f044cf4:	c7b200dc */ 	lwc1	$f18,0xdc($sp)
/*  f044cf8:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f044cfc:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*  f044d00:	3c017f1b */ 	lui	$at,%hi(var7f1a9238)
/*  f044d04:	c42a9238 */ 	lwc1	$f10,%lo(var7f1a9238)($at)
/*  f044d08:	3c017f1b */ 	lui	$at,%hi(var7f1a923c)
/*  f044d0c:	c426923c */ 	lwc1	$f6,%lo(var7f1a923c)($at)
/*  f044d10:	3c017f1b */ 	lui	$at,%hi(var7f1a9240)
/*  f044d14:	8fa400e0 */ 	lw	$a0,0xe0($sp)
/*  f044d18:	00002825 */ 	or	$a1,$zero,$zero
/*  f044d1c:	46028402 */ 	mul.s	$f16,$f16,$f2
/*  f044d20:	00000000 */ 	nop
/*  f044d24:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f044d28:	00000000 */ 	nop
/*  f044d2c:	46088302 */ 	mul.s	$f12,$f16,$f8
/*  f044d30:	e7b000d4 */ 	swc1	$f16,0xd4($sp)
/*  f044d34:	e7b200dc */ 	swc1	$f18,0xdc($sp)
/*  f044d38:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f044d3c:	00000000 */ 	nop
/*  f044d40:	46089382 */ 	mul.s	$f14,$f18,$f8
/*  f044d44:	e7a400d0 */ 	swc1	$f4,0xd0($sp)
/*  f044d48:	c4249240 */ 	lwc1	$f4,%lo(var7f1a9240)($at)
/*  f044d4c:	3c017f1b */ 	lui	$at,%hi(var7f1a9244)
/*  f044d50:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f044d54:	c4269244 */ 	lwc1	$f6,%lo(var7f1a9244)($at)
/*  f044d58:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f044d5c:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f044d60:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f044d64:	e7a800c8 */ 	swc1	$f8,0xc8($sp)
/*  f044d68:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f044d6c:	e7aa00c4 */ 	swc1	$f10,0xc4($sp)
/*  f044d70:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f044d74:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f044d78:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044d7c:	c7a200f8 */ 	lwc1	$f2,0xf8($sp)
/*  f044d80:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f044d84:	c7a800d0 */ 	lwc1	$f8,0xd0($sp)
/*  f044d88:	8faf0100 */ 	lw	$t7,0x100($sp)
/*  f044d8c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f044d90:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f044d94:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f044d98:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f044d9c:	02002025 */ 	or	$a0,$s0,$zero
/*  f044da0:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f044da4:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f044da8:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044dac:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f044db0:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f044db4:	c7a400c4 */ 	lwc1	$f4,0xc4($sp)
/*  f044db8:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f044dbc:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f044dc0:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f044dc4:	c7a600d4 */ 	lwc1	$f6,0xd4($sp)
/*  f044dc8:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f044dcc:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f044dd0:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f044dd4:	c7a800c8 */ 	lwc1	$f8,0xc8($sp)
/*  f044dd8:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f044ddc:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f044de0:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f044de4:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f044de8:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f044dec:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f044df0:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f044df4:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f044df8:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f044dfc:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f044e00:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f044e04:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f044e08:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f044e0c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f044e10:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044e14:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044e18:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f044e1c:	0c00b694 */ 	jal	cd0002da50
/*  f044e20:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f044e24:	10400010 */ 	beqz	$v0,.L0f044e68
/*  f044e28:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f044e2c:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*  f044e30:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f044e34:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f044e38:	c520000c */ 	lwc1	$f0,0xc($t1)
/*  f044e3c:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f044e40:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f044e44:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044e48:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f044e4c:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f044e50:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044e54:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f044e58:	8fa70100 */ 	lw	$a3,0x100($sp)
/*  f044e5c:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f044e60:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f044e64:	1440000c */ 	bnez	$v0,.L0f044e98
.L0f044e68:
/*  f044e68:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f044e6c:	3c077f1b */ 	lui	$a3,%hi(var7f1a8ba0)
/*  f044e70:	afaa00bc */ 	sw	$t2,0xbc($sp)
/*  f044e74:	24e78ba0 */ 	addiu	$a3,$a3,%lo(var7f1a8ba0)
/*  f044e78:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044e7c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f044e80:	0c009393 */ 	jal	cd00024e4c
/*  f044e84:	24063741 */ 	addiu	$a2,$zero,0x374e
/*  f044e88:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044e8c:	27a500a0 */ 	addiu	$a1,$sp,0xa0
/*  f044e90:	0fc112da */ 	jal	func0f044b68
/*  f044e94:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f044e98:
/*  f044e98:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f044e9c:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f044ea0:	8fa200ec */ 	lw	$v0,0xec($sp)
/*  f044ea4:	c7a200f8 */ 	lwc1	$f2,0xf8($sp)
/*  f044ea8:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f044eac:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f044eb0:	8fab0100 */ 	lw	$t3,0x100($sp)
/*  f044eb4:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f044eb8:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f044ebc:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f044ec0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f044ec4:	02002025 */ 	or	$a0,$s0,$zero
/*  f044ec8:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f044ecc:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f044ed0:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044ed4:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f044ed8:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f044edc:	c7a600c4 */ 	lwc1	$f6,0xc4($sp)
/*  f044ee0:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f044ee4:	e7a40074 */ 	swc1	$f4,0x74($sp)
/*  f044ee8:	c4480000 */ 	lwc1	$f8,0x0($v0)
/*  f044eec:	c7a400d4 */ 	lwc1	$f4,0xd4($sp)
/*  f044ef0:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f044ef4:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f044ef8:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f044efc:	c7aa00c8 */ 	lwc1	$f10,0xc8($sp)
/*  f044f00:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f044f04:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f044f08:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f044f0c:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f044f10:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f044f14:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f044f18:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f044f1c:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f044f20:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f044f24:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f044f28:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f044f2c:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f044f30:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f044f34:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f044f38:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044f3c:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044f40:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f044f44:	0c00b694 */ 	jal	cd0002da50
/*  f044f48:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f044f4c:	10400010 */ 	beqz	$v0,.L0f044f90
/*  f044f50:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f044f54:	8faf003c */ 	lw	$t7,0x3c($sp)
/*  f044f58:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f044f5c:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f044f60:	c5e0000c */ 	lwc1	$f0,0xc($t7)
/*  f044f64:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f044f68:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f044f6c:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f044f70:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f044f74:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f044f78:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f044f7c:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f044f80:	8fa70100 */ 	lw	$a3,0x100($sp)
/*  f044f84:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f044f88:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f044f8c:	1440000c */ 	bnez	$v0,.L0f044fc0
.L0f044f90:
/*  f044f90:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f044f94:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bac)
/*  f044f98:	afb800b8 */ 	sw	$t8,0xb8($sp)
/*  f044f9c:	24e78bac */ 	addiu	$a3,$a3,%lo(var7f1a8bac)
/*  f044fa0:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f044fa4:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044fa8:	0c009393 */ 	jal	cd00024e4c
/*  f044fac:	24063750 */ 	addiu	$a2,$zero,0x375d
/*  f044fb0:	27a40094 */ 	addiu	$a0,$sp,0x94
/*  f044fb4:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044fb8:	0fc112da */ 	jal	func0f044b68
/*  f044fbc:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f044fc0:
/*  f044fc0:	8fb900bc */ 	lw	$t9,0xbc($sp)
/*  f044fc4:	8fa800b8 */ 	lw	$t0,0xb8($sp)
/*  f044fc8:	8fa900bc */ 	lw	$t1,0xbc($sp)
/*  f044fcc:	13200019 */ 	beqz	$t9,.L0f045034
/*  f044fd0:	00000000 */ 	nop
/*  f044fd4:	11000017 */ 	beqz	$t0,.L0f045034
/*  f044fd8:	27a400ac */ 	addiu	$a0,$sp,0xac
/*  f044fdc:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f044fe0:	0fc112da */ 	jal	func0f044b68
/*  f044fe4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f044fe8:	27a400a0 */ 	addiu	$a0,$sp,0xa0
/*  f044fec:	27a50088 */ 	addiu	$a1,$sp,0x88
/*  f044ff0:	0fc112da */ 	jal	func0f044b68
/*  f044ff4:	27a600d4 */ 	addiu	$a2,$sp,0xd4
/*  f044ff8:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f044ffc:	c7a400ac */ 	lwc1	$f4,0xac($sp)
/*  f045000:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045004:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045008:	c7a800b0 */ 	lwc1	$f8,0xb0($sp)
/*  f04500c:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045010:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f045014:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f045018:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f04501c:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f045020:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f045024:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f045028:	c7a80090 */ 	lwc1	$f8,0x90($sp)
/*  f04502c:	10000055 */ 	b	.L0f045184
/*  f045030:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f045034:
/*  f045034:	11200010 */ 	beqz	$t1,.L0f045078
/*  f045038:	8faa00b8 */ 	lw	$t2,0xb8($sp)
/*  f04503c:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045040:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f045044:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045048:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f04504c:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f045050:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f045054:	c7a400b4 */ 	lwc1	$f4,0xb4($sp)
/*  f045058:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f04505c:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f045060:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f045064:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f045068:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f04506c:	c7aa00a8 */ 	lwc1	$f10,0xa8($sp)
/*  f045070:	10000044 */ 	b	.L0f045184
/*  f045074:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f045078:
/*  f045078:	11400010 */ 	beqz	$t2,.L0f0450bc
/*  f04507c:	8fab0100 */ 	lw	$t3,0x100($sp)
/*  f045080:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045084:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f045088:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f04508c:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045090:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f045094:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045098:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f04509c:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f0450a0:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f0450a4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f0450a8:	c7a4008c */ 	lwc1	$f4,0x8c($sp)
/*  f0450ac:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f0450b0:	c7a80090 */ 	lwc1	$f8,0x90($sp)
/*  f0450b4:	10000033 */ 	b	.L0f045184
/*  f0450b8:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f0450bc:
/*  f0450bc:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f0450c0:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0450c4:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f0450c8:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0450cc:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f0450d0:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0450d4:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0450d8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0450dc:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0450e0:	8fa500e8 */ 	lw	$a1,0xe8($sp)
/*  f0450e4:	8fa600ec */ 	lw	$a2,0xec($sp)
/*  f0450e8:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0450ec:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0450f0:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0450f4:	0c00b694 */ 	jal	cd0002da50
/*  f0450f8:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0450fc:	10400017 */ 	beqz	$v0,.L0f04515c
/*  f045100:	8fae0104 */ 	lw	$t6,0x104($sp)
/*  f045104:	11c00012 */ 	beqz	$t6,.L0f045150
/*  f045108:	8faf0100 */ 	lw	$t7,0x100($sp)
/*  f04510c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f045110:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f045114:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f045118:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f04511c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f045120:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f045124:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045128:	02002025 */ 	or	$a0,$s0,$zero
/*  f04512c:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045130:	8fa500ec */ 	lw	$a1,0xec($sp)
/*  f045134:	8fa600fc */ 	lw	$a2,0xfc($sp)
/*  f045138:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f04513c:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045140:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f045144:	0c00a9bf */ 	jal	cd0002a6fc
/*  f045148:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f04514c:	10400003 */ 	beqz	$v0,.L0f04515c
.L0f045150:
/*  f045150:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f045154:	1000000b */ 	b	.L0f045184
/*  f045158:	afa80084 */ 	sw	$t0,0x84($sp)
.L0f04515c:
/*  f04515c:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bb8)
/*  f045160:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045164:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f045168:	24e78bb8 */ 	addiu	$a3,$a3,%lo(var7f1a8bb8)
/*  f04516c:	0c009393 */ 	jal	cd00024e4c
/*  f045170:	24063796 */ 	addiu	$a2,$zero,0x37a3
/*  f045174:	8fa400f0 */ 	lw	$a0,0xf0($sp)
/*  f045178:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f04517c:	0fc112da */ 	jal	func0f044b68
/*  f045180:	27a600d4 */ 	addiu	$a2,$sp,0xd4
.L0f045184:
/*  f045184:	8fa400e0 */ 	lw	$a0,0xe0($sp)
/*  f045188:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f04518c:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f045190:	8fa20084 */ 	lw	$v0,0x84($sp)
.L0f045194:
/*  f045194:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045198:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f04519c:	27bd00e0 */ 	addiu	$sp,$sp,0xe0
/*  f0451a0:	03e00008 */ 	jr	$ra
/*  f0451a4:	00000000 */ 	nop
);
#endif

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f0451a8
.late_rodata
glabel var7f1a9248
.word 0x3f733333
glabel var7f1a924c
.word 0x3f733333
glabel var7f1a9250
.word 0x3f99999a
glabel var7f1a9254
.word 0x3f99999a
.text
/*  f0451a8:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f0451ac:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0451b0:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f0451b4:	afa400e8 */ 	sw	$a0,0xe8($sp)
/*  f0451b8:	afa600f0 */ 	sw	$a2,0xf0($sp)
/*  f0451bc:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f0451c0:	afa000c4 */ 	sw	$zero,0xc4($sp)
/*  f0451c4:	afa000c0 */ 	sw	$zero,0xc0($sp)
/*  f0451c8:	afa0008c */ 	sw	$zero,0x8c($sp)
/*  f0451cc:	8c84001c */ 	lw	$a0,0x1c($a0)
/*  f0451d0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f0451d4:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f0451d8:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f0451dc:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f0451e0:	0fc0a277 */ 	jal	chrGetBbox
/*  f0451e4:	afa4003c */ 	sw	$a0,0x3c($sp)
/*  f0451e8:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f0451ec:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f0451f0:	44800000 */ 	mtc1	$zero,$f0
/*  f0451f4:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f0451f8:	e7a000e0 */ 	swc1	$f0,0xe0($sp)
/*  f0451fc:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f045200:	e7a800dc */ 	swc1	$f8,0xdc($sp)
/*  f045204:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f045208:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f04520c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f045210:	46080032 */ 	c.eq.s	$f0,$f8
/*  f045214:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f045218:	45000008 */ 	bc1f	.L0f04523c
/*  f04521c:	e7a600e4 */ 	swc1	$f6,0xe4($sp)
/*  f045220:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045224:	46120032 */ 	c.eq.s	$f0,$f18
/*  f045228:	00000000 */ 	nop
/*  f04522c:	45020004 */ 	bc1fl	.L0f045240
/*  f045230:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045234:	10000145 */ 	b	.L0f04574c
/*  f045238:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f04523c:
/*  f04523c:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
.L0f045240:
/*  f045240:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f045244:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f045248:	00000000 */ 	nop
/*  f04524c:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f045250:	0c012974 */ 	jal	sqrtf
/*  f045254:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f045258:	3c013f80 */ 	lui	$at,0x3f80
/*  f04525c:	44813000 */ 	mtc1	$at,$f6
/*  f045260:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f045264:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045268:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f04526c:	c7a80104 */ 	lwc1	$f8,0x104($sp)
/*  f045270:	3c017f1b */ 	lui	$at,%hi(var7f1a9248)
/*  f045274:	c42a9248 */ 	lwc1	$f10,%lo(var7f1a9248)($at)
/*  f045278:	3c017f1b */ 	lui	$at,%hi(var7f1a924c)
/*  f04527c:	c426924c */ 	lwc1	$f6,%lo(var7f1a924c)($at)
/*  f045280:	3c017f1b */ 	lui	$at,%hi(var7f1a9250)
/*  f045284:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f045288:	00002825 */ 	or	$a1,$zero,$zero
/*  f04528c:	46028402 */ 	mul.s	$f16,$f16,$f2
/*  f045290:	00000000 */ 	nop
/*  f045294:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f045298:	00000000 */ 	nop
/*  f04529c:	46088302 */ 	mul.s	$f12,$f16,$f8
/*  f0452a0:	e7b000dc */ 	swc1	$f16,0xdc($sp)
/*  f0452a4:	e7b200e4 */ 	swc1	$f18,0xe4($sp)
/*  f0452a8:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f0452ac:	00000000 */ 	nop
/*  f0452b0:	46089382 */ 	mul.s	$f14,$f18,$f8
/*  f0452b4:	e7a400d8 */ 	swc1	$f4,0xd8($sp)
/*  f0452b8:	c4249250 */ 	lwc1	$f4,%lo(var7f1a9250)($at)
/*  f0452bc:	3c017f1b */ 	lui	$at,%hi(var7f1a9254)
/*  f0452c0:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f0452c4:	c4269254 */ 	lwc1	$f6,%lo(var7f1a9254)($at)
/*  f0452c8:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f0452cc:	e7aa00d4 */ 	swc1	$f10,0xd4($sp)
/*  f0452d0:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f0452d4:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f0452d8:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f0452dc:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f0452e0:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f0452e4:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f0452e8:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f0452ec:	c7a20100 */ 	lwc1	$f2,0x100($sp)
/*  f0452f0:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f0452f4:	c7a800d8 */ 	lwc1	$f8,0xd8($sp)
/*  f0452f8:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f0452fc:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f045300:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f045304:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f045308:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f04530c:	02002025 */ 	or	$a0,$s0,$zero
/*  f045310:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f045314:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f045318:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f04531c:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f045320:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f045324:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f045328:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f04532c:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f045330:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f045334:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f045338:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f04533c:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f045340:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f045344:	c7a800d0 */ 	lwc1	$f8,0xd0($sp)
/*  f045348:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f04534c:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f045350:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f045354:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f045358:	c7a600e4 */ 	lwc1	$f6,0xe4($sp)
/*  f04535c:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f045360:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f045364:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f045368:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f04536c:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f045370:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f045374:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045378:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f04537c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f045380:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045384:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f045388:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f04538c:	0c00b694 */ 	jal	cd0002da50
/*  f045390:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f045394:	10400010 */ 	beqz	$v0,.L0f0453d8
/*  f045398:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04539c:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*  f0453a0:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f0453a4:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0453a8:	c520000c */ 	lwc1	$f0,0xc($t1)
/*  f0453ac:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0453b0:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f0453b4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0453b8:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f0453bc:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0453c0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0453c4:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f0453c8:	8fa70108 */ 	lw	$a3,0x108($sp)
/*  f0453cc:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f0453d0:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f0453d4:	1440000f */ 	bnez	$v0,.L0f045414
.L0f0453d8:
/*  f0453d8:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0453dc:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bc4)
/*  f0453e0:	afaa00c4 */ 	sw	$t2,0xc4($sp)
/*  f0453e4:	24e78bc4 */ 	addiu	$a3,$a3,%lo(var7f1a8bc4)
/*  f0453e8:	27a400b4 */ 	addiu	$a0,$sp,0xb4
/*  f0453ec:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f0453f0:	0c009393 */ 	jal	cd00024e4c
/*  f0453f4:	240637e6 */ 	addiu	$a2,$zero,0x37ec
/*  f0453f8:	27a400b4 */ 	addiu	$a0,$sp,0xb4
/*  f0453fc:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f045400:	0fc112da */ 	jal	func0f044b68
/*  f045404:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f045408:	0c009390 */ 	jal	cd00024e40
/*  f04540c:	00000000 */ 	nop
/*  f045410:	e7a00088 */ 	swc1	$f0,0x88($sp)
.L0f045414:
/*  f045414:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f045418:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f04541c:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f045420:	c7a20100 */ 	lwc1	$f2,0x100($sp)
/*  f045424:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f045428:	c7aa00d8 */ 	lwc1	$f10,0xd8($sp)
/*  f04542c:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f045430:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f045434:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f045438:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f04543c:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f045440:	02002025 */ 	or	$a0,$s0,$zero
/*  f045444:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f045448:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f04544c:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f045450:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f045454:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f045458:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04545c:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f045460:	e7a40074 */ 	swc1	$f4,0x74($sp)
/*  f045464:	c4480000 */ 	lwc1	$f8,0x0($v0)
/*  f045468:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f04546c:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f045470:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f045474:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f045478:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f04547c:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f045480:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f045484:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f045488:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f04548c:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
/*  f045490:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f045494:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f045498:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f04549c:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0454a0:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0454a4:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f0454a8:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f0454ac:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f0454b0:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f0454b4:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0454b8:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0454bc:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f0454c0:	0c00b694 */ 	jal	cd0002da50
/*  f0454c4:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f0454c8:	10400010 */ 	beqz	$v0,.L0f04550c
/*  f0454cc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f0454d0:	8faf003c */ 	lw	$t7,0x3c($sp)
/*  f0454d4:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0454d8:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0454dc:	c5e0000c */ 	lwc1	$f0,0xc($t7)
/*  f0454e0:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f0454e4:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f0454e8:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0454ec:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f0454f0:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0454f4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0454f8:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f0454fc:	8fa70108 */ 	lw	$a3,0x108($sp)
/*  f045500:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f045504:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045508:	1440000f */ 	bnez	$v0,.L0f045548
.L0f04550c:
/*  f04550c:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f045510:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bd0)
/*  f045514:	afb800c0 */ 	sw	$t8,0xc0($sp)
/*  f045518:	24e78bd0 */ 	addiu	$a3,$a3,%lo(var7f1a8bd0)
/*  f04551c:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f045520:	27a50090 */ 	addiu	$a1,$sp,0x90
/*  f045524:	0c009393 */ 	jal	cd00024e4c
/*  f045528:	240637f5 */ 	addiu	$a2,$zero,0x37fb
/*  f04552c:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f045530:	27a50090 */ 	addiu	$a1,$sp,0x90
/*  f045534:	0fc112da */ 	jal	func0f044b68
/*  f045538:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f04553c:	0c009390 */ 	jal	cd00024e40
/*  f045540:	00000000 */ 	nop
/*  f045544:	e7a00084 */ 	swc1	$f0,0x84($sp)
.L0f045548:
/*  f045548:	8fb900c4 */ 	lw	$t9,0xc4($sp)
/*  f04554c:	8fa800c0 */ 	lw	$t0,0xc0($sp)
/*  f045550:	8fa900c4 */ 	lw	$t1,0xc4($sp)
/*  f045554:	13200025 */ 	beqz	$t9,.L0f0455ec
/*  f045558:	00000000 */ 	nop
/*  f04555c:	11000023 */ 	beqz	$t0,.L0f0455ec
/*  f045560:	c7a40088 */ 	lwc1	$f4,0x88($sp)
/*  f045564:	c7a80084 */ 	lwc1	$f8,0x84($sp)
/*  f045568:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f04556c:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045570:	4608203c */ 	c.lt.s	$f4,$f8
/*  f045574:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f045578:	45020010 */ 	bc1fl	.L0f0455bc
/*  f04557c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045580:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045584:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045588:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f04558c:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*  f045590:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f045594:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f045598:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f04559c:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f0455a0:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f0455a4:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f0455a8:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f0455ac:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f0455b0:	10000062 */ 	b	.L0f04573c
/*  f0455b4:	e4aa0008 */ 	swc1	$f10,0x8($a1)
/*  f0455b8:	8fa500fc */ 	lw	$a1,0xfc($sp)
.L0f0455bc:
/*  f0455bc:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f0455c0:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f0455c4:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f0455c8:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f0455cc:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f0455d0:	c7aa0090 */ 	lwc1	$f10,0x90($sp)
/*  f0455d4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f0455d8:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f0455dc:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f0455e0:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f0455e4:	10000055 */ 	b	.L0f04573c
/*  f0455e8:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f0455ec:
/*  f0455ec:	11200010 */ 	beqz	$t1,.L0f045630
/*  f0455f0:	8faa00c0 */ 	lw	$t2,0xc0($sp)
/*  f0455f4:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f0455f8:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f0455fc:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045600:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f045604:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*  f045608:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f04560c:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f045610:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f045614:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f045618:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f04561c:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f045620:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f045624:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f045628:	10000044 */ 	b	.L0f04573c
/*  f04562c:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f045630:
/*  f045630:	11400010 */ 	beqz	$t2,.L0f045674
/*  f045634:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f045638:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f04563c:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f045640:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045644:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045648:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f04564c:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045650:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f045654:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f045658:	c7aa0090 */ 	lwc1	$f10,0x90($sp)
/*  f04565c:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f045660:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f045664:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f045668:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f04566c:	10000033 */ 	b	.L0f04573c
/*  f045670:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f045674:
/*  f045674:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f045678:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f04567c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f045680:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f045684:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f045688:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f04568c:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045690:	02002025 */ 	or	$a0,$s0,$zero
/*  f045694:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045698:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f04569c:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*  f0456a0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0456a4:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0456a8:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0456ac:	0c00b694 */ 	jal	cd0002da50
/*  f0456b0:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0456b4:	10400017 */ 	beqz	$v0,.L0f045714
/*  f0456b8:	8fae010c */ 	lw	$t6,0x10c($sp)
/*  f0456bc:	11c00012 */ 	beqz	$t6,.L0f045708
/*  f0456c0:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f0456c4:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f0456c8:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f0456cc:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0456d0:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0456d4:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f0456d8:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0456dc:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0456e0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0456e4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0456e8:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f0456ec:	8fa60104 */ 	lw	$a2,0x104($sp)
/*  f0456f0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0456f4:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0456f8:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0456fc:	0c00a9bf */ 	jal	cd0002a6fc
/*  f045700:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f045704:	10400003 */ 	beqz	$v0,.L0f045714
.L0f045708:
/*  f045708:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04570c:	1000000b */ 	b	.L0f04573c
/*  f045710:	afa8008c */ 	sw	$t0,0x8c($sp)
.L0f045714:
/*  f045714:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bdc)
/*  f045718:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f04571c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045720:	24e78bdc */ 	addiu	$a3,$a3,%lo(var7f1a8bdc)
/*  f045724:	0c009393 */ 	jal	cd00024e4c
/*  f045728:	2406383b */ 	addiu	$a2,$zero,0x3841
/*  f04572c:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045730:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045734:	0fc112da */ 	jal	func0f044b68
/*  f045738:	27a600dc */ 	addiu	$a2,$sp,0xdc
.L0f04573c:
/*  f04573c:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f045740:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f045744:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f045748:	8fa2008c */ 	lw	$v0,0x8c($sp)
.L0f04574c:
/*  f04574c:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045750:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f045754:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f045758:	03e00008 */ 	jr	$ra
/*  f04575c:	00000000 */ 	nop
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f0451a8
.late_rodata
glabel var7f1a9248
.word 0x3f733333
glabel var7f1a924c
.word 0x3f733333
glabel var7f1a9250
.word 0x3f99999a
glabel var7f1a9254
.word 0x3f99999a
.text
/*  f0451a8:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f0451ac:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0451b0:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f0451b4:	afa400e8 */ 	sw	$a0,0xe8($sp)
/*  f0451b8:	afa600f0 */ 	sw	$a2,0xf0($sp)
/*  f0451bc:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f0451c0:	afa000c4 */ 	sw	$zero,0xc4($sp)
/*  f0451c4:	afa000c0 */ 	sw	$zero,0xc0($sp)
/*  f0451c8:	afa0008c */ 	sw	$zero,0x8c($sp)
/*  f0451cc:	8c84001c */ 	lw	$a0,0x1c($a0)
/*  f0451d0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f0451d4:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f0451d8:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f0451dc:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f0451e0:	0fc0a277 */ 	jal	chrGetBbox
/*  f0451e4:	afa4003c */ 	sw	$a0,0x3c($sp)
/*  f0451e8:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f0451ec:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f0451f0:	44800000 */ 	mtc1	$zero,$f0
/*  f0451f4:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f0451f8:	e7a000e0 */ 	swc1	$f0,0xe0($sp)
/*  f0451fc:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f045200:	e7a800dc */ 	swc1	$f8,0xdc($sp)
/*  f045204:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f045208:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f04520c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f045210:	46080032 */ 	c.eq.s	$f0,$f8
/*  f045214:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f045218:	45000008 */ 	bc1f	.L0f04523c
/*  f04521c:	e7a600e4 */ 	swc1	$f6,0xe4($sp)
/*  f045220:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045224:	46120032 */ 	c.eq.s	$f0,$f18
/*  f045228:	00000000 */ 	nop
/*  f04522c:	45020004 */ 	bc1fl	.L0f045240
/*  f045230:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045234:	10000145 */ 	b	.L0f04574c
/*  f045238:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f04523c:
/*  f04523c:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
.L0f045240:
/*  f045240:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f045244:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f045248:	00000000 */ 	nop
/*  f04524c:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f045250:	0c012974 */ 	jal	sqrtf
/*  f045254:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f045258:	3c013f80 */ 	lui	$at,0x3f80
/*  f04525c:	44813000 */ 	mtc1	$at,$f6
/*  f045260:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f045264:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045268:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f04526c:	c7a80104 */ 	lwc1	$f8,0x104($sp)
/*  f045270:	3c017f1b */ 	lui	$at,%hi(var7f1a9248)
/*  f045274:	c42a9248 */ 	lwc1	$f10,%lo(var7f1a9248)($at)
/*  f045278:	3c017f1b */ 	lui	$at,%hi(var7f1a924c)
/*  f04527c:	c426924c */ 	lwc1	$f6,%lo(var7f1a924c)($at)
/*  f045280:	3c017f1b */ 	lui	$at,%hi(var7f1a9250)
/*  f045284:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f045288:	00002825 */ 	or	$a1,$zero,$zero
/*  f04528c:	46028402 */ 	mul.s	$f16,$f16,$f2
/*  f045290:	00000000 */ 	nop
/*  f045294:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f045298:	00000000 */ 	nop
/*  f04529c:	46088302 */ 	mul.s	$f12,$f16,$f8
/*  f0452a0:	e7b000dc */ 	swc1	$f16,0xdc($sp)
/*  f0452a4:	e7b200e4 */ 	swc1	$f18,0xe4($sp)
/*  f0452a8:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f0452ac:	00000000 */ 	nop
/*  f0452b0:	46089382 */ 	mul.s	$f14,$f18,$f8
/*  f0452b4:	e7a400d8 */ 	swc1	$f4,0xd8($sp)
/*  f0452b8:	c4249250 */ 	lwc1	$f4,%lo(var7f1a9250)($at)
/*  f0452bc:	3c017f1b */ 	lui	$at,%hi(var7f1a9254)
/*  f0452c0:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f0452c4:	c4269254 */ 	lwc1	$f6,%lo(var7f1a9254)($at)
/*  f0452c8:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f0452cc:	e7aa00d4 */ 	swc1	$f10,0xd4($sp)
/*  f0452d0:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f0452d4:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f0452d8:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f0452dc:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f0452e0:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f0452e4:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f0452e8:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f0452ec:	c7a20100 */ 	lwc1	$f2,0x100($sp)
/*  f0452f0:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f0452f4:	c7a800d8 */ 	lwc1	$f8,0xd8($sp)
/*  f0452f8:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f0452fc:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f045300:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f045304:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f045308:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f04530c:	02002025 */ 	or	$a0,$s0,$zero
/*  f045310:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f045314:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f045318:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f04531c:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f045320:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f045324:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f045328:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f04532c:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f045330:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f045334:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f045338:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f04533c:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f045340:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f045344:	c7a800d0 */ 	lwc1	$f8,0xd0($sp)
/*  f045348:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f04534c:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f045350:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f045354:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f045358:	c7a600e4 */ 	lwc1	$f6,0xe4($sp)
/*  f04535c:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f045360:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f045364:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f045368:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f04536c:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f045370:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f045374:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045378:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f04537c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f045380:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045384:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f045388:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f04538c:	0c00b694 */ 	jal	cd0002da50
/*  f045390:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f045394:	10400010 */ 	beqz	$v0,.L0f0453d8
/*  f045398:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04539c:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*  f0453a0:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f0453a4:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0453a8:	c520000c */ 	lwc1	$f0,0xc($t1)
/*  f0453ac:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0453b0:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f0453b4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0453b8:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f0453bc:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0453c0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0453c4:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f0453c8:	8fa70108 */ 	lw	$a3,0x108($sp)
/*  f0453cc:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f0453d0:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f0453d4:	1440000f */ 	bnez	$v0,.L0f045414
.L0f0453d8:
/*  f0453d8:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0453dc:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bc4)
/*  f0453e0:	afaa00c4 */ 	sw	$t2,0xc4($sp)
/*  f0453e4:	24e78bc4 */ 	addiu	$a3,$a3,%lo(var7f1a8bc4)
/*  f0453e8:	27a400b4 */ 	addiu	$a0,$sp,0xb4
/*  f0453ec:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f0453f0:	0c009393 */ 	jal	cd00024e4c
/*  f0453f4:	240637e6 */ 	addiu	$a2,$zero,0x37e6
/*  f0453f8:	27a400b4 */ 	addiu	$a0,$sp,0xb4
/*  f0453fc:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f045400:	0fc112da */ 	jal	func0f044b68
/*  f045404:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f045408:	0c009390 */ 	jal	cd00024e40
/*  f04540c:	00000000 */ 	nop
/*  f045410:	e7a00088 */ 	swc1	$f0,0x88($sp)
.L0f045414:
/*  f045414:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f045418:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f04541c:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f045420:	c7a20100 */ 	lwc1	$f2,0x100($sp)
/*  f045424:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f045428:	c7aa00d8 */ 	lwc1	$f10,0xd8($sp)
/*  f04542c:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f045430:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f045434:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f045438:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f04543c:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f045440:	02002025 */ 	or	$a0,$s0,$zero
/*  f045444:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f045448:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f04544c:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f045450:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f045454:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f045458:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04545c:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f045460:	e7a40074 */ 	swc1	$f4,0x74($sp)
/*  f045464:	c4480000 */ 	lwc1	$f8,0x0($v0)
/*  f045468:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f04546c:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f045470:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f045474:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f045478:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f04547c:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f045480:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f045484:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f045488:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f04548c:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
/*  f045490:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f045494:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f045498:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f04549c:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0454a0:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0454a4:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f0454a8:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f0454ac:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f0454b0:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f0454b4:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0454b8:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0454bc:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f0454c0:	0c00b694 */ 	jal	cd0002da50
/*  f0454c4:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f0454c8:	10400010 */ 	beqz	$v0,.L0f04550c
/*  f0454cc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f0454d0:	8faf003c */ 	lw	$t7,0x3c($sp)
/*  f0454d4:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0454d8:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0454dc:	c5e0000c */ 	lwc1	$f0,0xc($t7)
/*  f0454e0:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f0454e4:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f0454e8:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0454ec:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f0454f0:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0454f4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0454f8:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f0454fc:	8fa70108 */ 	lw	$a3,0x108($sp)
/*  f045500:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f045504:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045508:	1440000f */ 	bnez	$v0,.L0f045548
.L0f04550c:
/*  f04550c:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f045510:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bd0)
/*  f045514:	afb800c0 */ 	sw	$t8,0xc0($sp)
/*  f045518:	24e78bd0 */ 	addiu	$a3,$a3,%lo(var7f1a8bd0)
/*  f04551c:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f045520:	27a50090 */ 	addiu	$a1,$sp,0x90
/*  f045524:	0c009393 */ 	jal	cd00024e4c
/*  f045528:	240637f5 */ 	addiu	$a2,$zero,0x37f5
/*  f04552c:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f045530:	27a50090 */ 	addiu	$a1,$sp,0x90
/*  f045534:	0fc112da */ 	jal	func0f044b68
/*  f045538:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f04553c:	0c009390 */ 	jal	cd00024e40
/*  f045540:	00000000 */ 	nop
/*  f045544:	e7a00084 */ 	swc1	$f0,0x84($sp)
.L0f045548:
/*  f045548:	8fb900c4 */ 	lw	$t9,0xc4($sp)
/*  f04554c:	8fa800c0 */ 	lw	$t0,0xc0($sp)
/*  f045550:	8fa900c4 */ 	lw	$t1,0xc4($sp)
/*  f045554:	13200025 */ 	beqz	$t9,.L0f0455ec
/*  f045558:	00000000 */ 	nop
/*  f04555c:	11000023 */ 	beqz	$t0,.L0f0455ec
/*  f045560:	c7a40088 */ 	lwc1	$f4,0x88($sp)
/*  f045564:	c7a80084 */ 	lwc1	$f8,0x84($sp)
/*  f045568:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f04556c:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045570:	4608203c */ 	c.lt.s	$f4,$f8
/*  f045574:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f045578:	45020010 */ 	bc1fl	.L0f0455bc
/*  f04557c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045580:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045584:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045588:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f04558c:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*  f045590:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f045594:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f045598:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f04559c:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f0455a0:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f0455a4:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f0455a8:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f0455ac:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f0455b0:	10000062 */ 	b	.L0f04573c
/*  f0455b4:	e4aa0008 */ 	swc1	$f10,0x8($a1)
/*  f0455b8:	8fa500fc */ 	lw	$a1,0xfc($sp)
.L0f0455bc:
/*  f0455bc:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f0455c0:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f0455c4:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f0455c8:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f0455cc:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f0455d0:	c7aa0090 */ 	lwc1	$f10,0x90($sp)
/*  f0455d4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f0455d8:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f0455dc:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f0455e0:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f0455e4:	10000055 */ 	b	.L0f04573c
/*  f0455e8:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f0455ec:
/*  f0455ec:	11200010 */ 	beqz	$t1,.L0f045630
/*  f0455f0:	8faa00c0 */ 	lw	$t2,0xc0($sp)
/*  f0455f4:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f0455f8:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f0455fc:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045600:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f045604:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*  f045608:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f04560c:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f045610:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f045614:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f045618:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f04561c:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f045620:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f045624:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f045628:	10000044 */ 	b	.L0f04573c
/*  f04562c:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f045630:
/*  f045630:	11400010 */ 	beqz	$t2,.L0f045674
/*  f045634:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f045638:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f04563c:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f045640:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045644:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045648:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f04564c:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045650:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f045654:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f045658:	c7aa0090 */ 	lwc1	$f10,0x90($sp)
/*  f04565c:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f045660:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f045664:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f045668:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f04566c:	10000033 */ 	b	.L0f04573c
/*  f045670:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f045674:
/*  f045674:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f045678:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f04567c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f045680:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f045684:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f045688:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f04568c:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045690:	02002025 */ 	or	$a0,$s0,$zero
/*  f045694:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045698:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f04569c:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*  f0456a0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0456a4:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0456a8:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0456ac:	0c00b694 */ 	jal	cd0002da50
/*  f0456b0:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0456b4:	10400017 */ 	beqz	$v0,.L0f045714
/*  f0456b8:	8fae010c */ 	lw	$t6,0x10c($sp)
/*  f0456bc:	11c00012 */ 	beqz	$t6,.L0f045708
/*  f0456c0:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f0456c4:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f0456c8:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f0456cc:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0456d0:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0456d4:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f0456d8:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0456dc:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0456e0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0456e4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0456e8:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f0456ec:	8fa60104 */ 	lw	$a2,0x104($sp)
/*  f0456f0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0456f4:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0456f8:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0456fc:	0c00a9bf */ 	jal	cd0002a6fc
/*  f045700:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f045704:	10400003 */ 	beqz	$v0,.L0f045714
.L0f045708:
/*  f045708:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04570c:	1000000b */ 	b	.L0f04573c
/*  f045710:	afa8008c */ 	sw	$t0,0x8c($sp)
.L0f045714:
/*  f045714:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bdc)
/*  f045718:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f04571c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045720:	24e78bdc */ 	addiu	$a3,$a3,%lo(var7f1a8bdc)
/*  f045724:	0c009393 */ 	jal	cd00024e4c
/*  f045728:	2406383b */ 	addiu	$a2,$zero,0x383b
/*  f04572c:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045730:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045734:	0fc112da */ 	jal	func0f044b68
/*  f045738:	27a600dc */ 	addiu	$a2,$sp,0xdc
.L0f04573c:
/*  f04573c:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f045740:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f045744:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f045748:	8fa2008c */ 	lw	$v0,0x8c($sp)
.L0f04574c:
/*  f04574c:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045750:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f045754:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f045758:	03e00008 */ 	jr	$ra
/*  f04575c:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel func0f0451a8
.late_rodata
glabel var7f1a9248
.word 0x3f733333
glabel var7f1a924c
.word 0x3f733333
glabel var7f1a9250
.word 0x3f99999a
glabel var7f1a9254
.word 0x3f99999a
.text
/*  f0451a8:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f0451ac:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f0451b0:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f0451b4:	afa400e8 */ 	sw	$a0,0xe8($sp)
/*  f0451b8:	afa600f0 */ 	sw	$a2,0xf0($sp)
/*  f0451bc:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f0451c0:	afa000c4 */ 	sw	$zero,0xc4($sp)
/*  f0451c4:	afa000c0 */ 	sw	$zero,0xc0($sp)
/*  f0451c8:	afa0008c */ 	sw	$zero,0x8c($sp)
/*  f0451cc:	8c84001c */ 	lw	$a0,0x1c($a0)
/*  f0451d0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f0451d4:	27a50078 */ 	addiu	$a1,$sp,0x78
/*  f0451d8:	27a7007c */ 	addiu	$a3,$sp,0x7c
/*  f0451dc:	27a60080 */ 	addiu	$a2,$sp,0x80
/*  f0451e0:	0fc0a277 */ 	jal	chrGetBbox
/*  f0451e4:	afa4003c */ 	sw	$a0,0x3c($sp)
/*  f0451e8:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f0451ec:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f0451f0:	44800000 */ 	mtc1	$zero,$f0
/*  f0451f4:	c4440000 */ 	lwc1	$f4,0x0($v0)
/*  f0451f8:	e7a000e0 */ 	swc1	$f0,0xe0($sp)
/*  f0451fc:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f045200:	e7a800dc */ 	swc1	$f8,0xdc($sp)
/*  f045204:	c7a800dc */ 	lwc1	$f8,0xdc($sp)
/*  f045208:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f04520c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f045210:	46080032 */ 	c.eq.s	$f0,$f8
/*  f045214:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f045218:	45000008 */ 	bc1f	.L0f04523c
/*  f04521c:	e7a600e4 */ 	swc1	$f6,0xe4($sp)
/*  f045220:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045224:	46120032 */ 	c.eq.s	$f0,$f18
/*  f045228:	00000000 */ 	nop
/*  f04522c:	45020004 */ 	bc1fl	.L0f045240
/*  f045230:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045234:	10000145 */ 	b	.L0f04574c
/*  f045238:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f04523c:
/*  f04523c:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
.L0f045240:
/*  f045240:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f045244:	46129282 */ 	mul.s	$f10,$f18,$f18
/*  f045248:	00000000 */ 	nop
/*  f04524c:	46108102 */ 	mul.s	$f4,$f16,$f16
/*  f045250:	0c012974 */ 	jal	sqrtf
/*  f045254:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f045258:	3c013f80 */ 	lui	$at,0x3f80
/*  f04525c:	44813000 */ 	mtc1	$at,$f6
/*  f045260:	c7b000dc */ 	lwc1	$f16,0xdc($sp)
/*  f045264:	c7b200e4 */ 	lwc1	$f18,0xe4($sp)
/*  f045268:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f04526c:	c7a80104 */ 	lwc1	$f8,0x104($sp)
/*  f045270:	3c017f1b */ 	lui	$at,%hi(var7f1a9248)
/*  f045274:	c42a9248 */ 	lwc1	$f10,%lo(var7f1a9248)($at)
/*  f045278:	3c017f1b */ 	lui	$at,%hi(var7f1a924c)
/*  f04527c:	c426924c */ 	lwc1	$f6,%lo(var7f1a924c)($at)
/*  f045280:	3c017f1b */ 	lui	$at,%hi(var7f1a9250)
/*  f045284:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f045288:	00002825 */ 	or	$a1,$zero,$zero
/*  f04528c:	46028402 */ 	mul.s	$f16,$f16,$f2
/*  f045290:	00000000 */ 	nop
/*  f045294:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f045298:	00000000 */ 	nop
/*  f04529c:	46088302 */ 	mul.s	$f12,$f16,$f8
/*  f0452a0:	e7b000dc */ 	swc1	$f16,0xdc($sp)
/*  f0452a4:	e7b200e4 */ 	swc1	$f18,0xe4($sp)
/*  f0452a8:	460a6102 */ 	mul.s	$f4,$f12,$f10
/*  f0452ac:	00000000 */ 	nop
/*  f0452b0:	46089382 */ 	mul.s	$f14,$f18,$f8
/*  f0452b4:	e7a400d8 */ 	swc1	$f4,0xd8($sp)
/*  f0452b8:	c4249250 */ 	lwc1	$f4,%lo(var7f1a9250)($at)
/*  f0452bc:	3c017f1b */ 	lui	$at,%hi(var7f1a9254)
/*  f0452c0:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f0452c4:	c4269254 */ 	lwc1	$f6,%lo(var7f1a9254)($at)
/*  f0452c8:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f0452cc:	e7aa00d4 */ 	swc1	$f10,0xd4($sp)
/*  f0452d0:	46067282 */ 	mul.s	$f10,$f14,$f6
/*  f0452d4:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f0452d8:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f0452dc:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f0452e0:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f0452e4:	c7a800d4 */ 	lwc1	$f8,0xd4($sp)
/*  f0452e8:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f0452ec:	c7a20100 */ 	lwc1	$f2,0x100($sp)
/*  f0452f0:	46082180 */ 	add.s	$f6,$f4,$f8
/*  f0452f4:	c7a800d8 */ 	lwc1	$f8,0xd8($sp)
/*  f0452f8:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f0452fc:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f045300:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*  f045304:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f045308:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f04530c:	02002025 */ 	or	$a0,$s0,$zero
/*  f045310:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f045314:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f045318:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f04531c:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f045320:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f045324:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f045328:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f04532c:	e7a60074 */ 	swc1	$f6,0x74($sp)
/*  f045330:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f045334:	c7a600dc */ 	lwc1	$f6,0xdc($sp)
/*  f045338:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f04533c:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f045340:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f045344:	c7a800d0 */ 	lwc1	$f8,0xd0($sp)
/*  f045348:	e7a40060 */ 	swc1	$f4,0x60($sp)
/*  f04534c:	c4460004 */ 	lwc1	$f6,0x4($v0)
/*  f045350:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f045354:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f045358:	c7a600e4 */ 	lwc1	$f6,0xe4($sp)
/*  f04535c:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f045360:	46085101 */ 	sub.s	$f4,$f10,$f8
/*  f045364:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f045368:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f04536c:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f045370:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f045374:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045378:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f04537c:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f045380:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045384:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f045388:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f04538c:	0c00b694 */ 	jal	cd0002da50
/*  f045390:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f045394:	10400010 */ 	beqz	$v0,.L0f0453d8
/*  f045398:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04539c:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*  f0453a0:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f0453a4:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0453a8:	c520000c */ 	lwc1	$f0,0xc($t1)
/*  f0453ac:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0453b0:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f0453b4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0453b8:	27a50050 */ 	addiu	$a1,$sp,0x50
/*  f0453bc:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0453c0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0453c4:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f0453c8:	8fa70108 */ 	lw	$a3,0x108($sp)
/*  f0453cc:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f0453d0:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f0453d4:	1440000f */ 	bnez	$v0,.L0f045414
.L0f0453d8:
/*  f0453d8:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f0453dc:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bc4)
/*  f0453e0:	afaa00c4 */ 	sw	$t2,0xc4($sp)
/*  f0453e4:	24e78bc4 */ 	addiu	$a3,$a3,%lo(var7f1a8bc4)
/*  f0453e8:	27a400b4 */ 	addiu	$a0,$sp,0xb4
/*  f0453ec:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f0453f0:	0c009393 */ 	jal	cd00024e4c
/*  f0453f4:	240637e6 */ 	addiu	$a2,$zero,0x37f3
/*  f0453f8:	27a400b4 */ 	addiu	$a0,$sp,0xb4
/*  f0453fc:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f045400:	0fc112da */ 	jal	func0f044b68
/*  f045404:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f045408:	0c009390 */ 	jal	cd00024e40
/*  f04540c:	00000000 */ 	nop
/*  f045410:	e7a00088 */ 	swc1	$f0,0x88($sp)
.L0f045414:
/*  f045414:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f045418:	c7aa00d4 */ 	lwc1	$f10,0xd4($sp)
/*  f04541c:	8fa200f4 */ 	lw	$v0,0xf4($sp)
/*  f045420:	c7a20100 */ 	lwc1	$f2,0x100($sp)
/*  f045424:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f045428:	c7aa00d8 */ 	lwc1	$f10,0xd8($sp)
/*  f04542c:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f045430:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f045434:	e7a4006c */ 	swc1	$f4,0x6c($sp)
/*  f045438:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f04543c:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f045440:	02002025 */ 	or	$a0,$s0,$zero
/*  f045444:	e7a80070 */ 	swc1	$f8,0x70($sp)
/*  f045448:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f04544c:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f045450:	27a6006c */ 	addiu	$a2,$sp,0x6c
/*  f045454:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f045458:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04545c:	27a70050 */ 	addiu	$a3,$sp,0x50
/*  f045460:	e7a40074 */ 	swc1	$f4,0x74($sp)
/*  f045464:	c4480000 */ 	lwc1	$f8,0x0($v0)
/*  f045468:	c7a400dc */ 	lwc1	$f4,0xdc($sp)
/*  f04546c:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f045470:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f045474:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f045478:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f04547c:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f045480:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f045484:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f045488:	c4480008 */ 	lwc1	$f8,0x8($v0)
/*  f04548c:	c7a400e4 */ 	lwc1	$f4,0xe4($sp)
/*  f045490:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f045494:	460a4180 */ 	add.s	$f6,$f8,$f10
/*  f045498:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f04549c:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f0454a0:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0454a4:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f0454a8:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f0454ac:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f0454b0:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f0454b4:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0454b8:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0454bc:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f0454c0:	0c00b694 */ 	jal	cd0002da50
/*  f0454c4:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f0454c8:	10400010 */ 	beqz	$v0,.L0f04550c
/*  f0454cc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f0454d0:	8faf003c */ 	lw	$t7,0x3c($sp)
/*  f0454d4:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f0454d8:	c7a40080 */ 	lwc1	$f4,0x80($sp)
/*  f0454dc:	c5e0000c */ 	lwc1	$f0,0xc($t7)
/*  f0454e0:	c7a6007c */ 	lwc1	$f6,0x7c($sp)
/*  f0454e4:	27a4006c */ 	addiu	$a0,$sp,0x6c
/*  f0454e8:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0454ec:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f0454f0:	27a60060 */ 	addiu	$a2,$sp,0x60
/*  f0454f4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0454f8:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*  f0454fc:	8fa70108 */ 	lw	$a3,0x108($sp)
/*  f045500:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f045504:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045508:	1440000f */ 	bnez	$v0,.L0f045548
.L0f04550c:
/*  f04550c:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f045510:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bd0)
/*  f045514:	afb800c0 */ 	sw	$t8,0xc0($sp)
/*  f045518:	24e78bd0 */ 	addiu	$a3,$a3,%lo(var7f1a8bd0)
/*  f04551c:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f045520:	27a50090 */ 	addiu	$a1,$sp,0x90
/*  f045524:	0c009393 */ 	jal	cd00024e4c
/*  f045528:	240637f5 */ 	addiu	$a2,$zero,0x3802
/*  f04552c:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f045530:	27a50090 */ 	addiu	$a1,$sp,0x90
/*  f045534:	0fc112da */ 	jal	func0f044b68
/*  f045538:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f04553c:	0c009390 */ 	jal	cd00024e40
/*  f045540:	00000000 */ 	nop
/*  f045544:	e7a00084 */ 	swc1	$f0,0x84($sp)
.L0f045548:
/*  f045548:	8fb900c4 */ 	lw	$t9,0xc4($sp)
/*  f04554c:	8fa800c0 */ 	lw	$t0,0xc0($sp)
/*  f045550:	8fa900c4 */ 	lw	$t1,0xc4($sp)
/*  f045554:	13200025 */ 	beqz	$t9,.L0f0455ec
/*  f045558:	00000000 */ 	nop
/*  f04555c:	11000023 */ 	beqz	$t0,.L0f0455ec
/*  f045560:	c7a40088 */ 	lwc1	$f4,0x88($sp)
/*  f045564:	c7a80084 */ 	lwc1	$f8,0x84($sp)
/*  f045568:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f04556c:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045570:	4608203c */ 	c.lt.s	$f4,$f8
/*  f045574:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f045578:	45020010 */ 	bc1fl	.L0f0455bc
/*  f04557c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045580:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045584:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045588:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f04558c:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*  f045590:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f045594:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f045598:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f04559c:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f0455a0:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f0455a4:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f0455a8:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f0455ac:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f0455b0:	10000062 */ 	b	.L0f04573c
/*  f0455b4:	e4aa0008 */ 	swc1	$f10,0x8($a1)
/*  f0455b8:	8fa500fc */ 	lw	$a1,0xfc($sp)
.L0f0455bc:
/*  f0455bc:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f0455c0:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f0455c4:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f0455c8:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f0455cc:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f0455d0:	c7aa0090 */ 	lwc1	$f10,0x90($sp)
/*  f0455d4:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f0455d8:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f0455dc:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f0455e0:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f0455e4:	10000055 */ 	b	.L0f04573c
/*  f0455e8:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f0455ec:
/*  f0455ec:	11200010 */ 	beqz	$t1,.L0f045630
/*  f0455f0:	8faa00c0 */ 	lw	$t2,0xc0($sp)
/*  f0455f4:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f0455f8:	c7a600b4 */ 	lwc1	$f6,0xb4($sp)
/*  f0455fc:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045600:	e4860000 */ 	swc1	$f6,0x0($a0)
/*  f045604:	c7aa00b8 */ 	lwc1	$f10,0xb8($sp)
/*  f045608:	e48a0004 */ 	swc1	$f10,0x4($a0)
/*  f04560c:	c7a400bc */ 	lwc1	$f4,0xbc($sp)
/*  f045610:	e4840008 */ 	swc1	$f4,0x8($a0)
/*  f045614:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f045618:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*  f04561c:	c7a600ac */ 	lwc1	$f6,0xac($sp)
/*  f045620:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*  f045624:	c7aa00b0 */ 	lwc1	$f10,0xb0($sp)
/*  f045628:	10000044 */ 	b	.L0f04573c
/*  f04562c:	e4aa0008 */ 	swc1	$f10,0x8($a1)
.L0f045630:
/*  f045630:	11400010 */ 	beqz	$t2,.L0f045674
/*  f045634:	8fab0108 */ 	lw	$t3,0x108($sp)
/*  f045638:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f04563c:	c7a4009c */ 	lwc1	$f4,0x9c($sp)
/*  f045640:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045644:	e4840000 */ 	swc1	$f4,0x0($a0)
/*  f045648:	c7a800a0 */ 	lwc1	$f8,0xa0($sp)
/*  f04564c:	e4880004 */ 	swc1	$f8,0x4($a0)
/*  f045650:	c7a600a4 */ 	lwc1	$f6,0xa4($sp)
/*  f045654:	e4860008 */ 	swc1	$f6,0x8($a0)
/*  f045658:	c7aa0090 */ 	lwc1	$f10,0x90($sp)
/*  f04565c:	e4aa0000 */ 	swc1	$f10,0x0($a1)
/*  f045660:	c7a40094 */ 	lwc1	$f4,0x94($sp)
/*  f045664:	e4a40004 */ 	swc1	$f4,0x4($a1)
/*  f045668:	c7a80098 */ 	lwc1	$f8,0x98($sp)
/*  f04566c:	10000033 */ 	b	.L0f04573c
/*  f045670:	e4a80008 */ 	swc1	$f8,0x8($a1)
.L0f045674:
/*  f045674:	8fad003c */ 	lw	$t5,0x3c($sp)
/*  f045678:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f04567c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f045680:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f045684:	c5a0000c */ 	lwc1	$f0,0xc($t5)
/*  f045688:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f04568c:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f045690:	02002025 */ 	or	$a0,$s0,$zero
/*  f045694:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f045698:	8fa500f0 */ 	lw	$a1,0xf0($sp)
/*  f04569c:	8fa600f4 */ 	lw	$a2,0xf4($sp)
/*  f0456a0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0456a4:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0456a8:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0456ac:	0c00b694 */ 	jal	cd0002da50
/*  f0456b0:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f0456b4:	10400017 */ 	beqz	$v0,.L0f045714
/*  f0456b8:	8fae010c */ 	lw	$t6,0x10c($sp)
/*  f0456bc:	11c00012 */ 	beqz	$t6,.L0f045708
/*  f0456c0:	8faf0108 */ 	lw	$t7,0x108($sp)
/*  f0456c4:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*  f0456c8:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f0456cc:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f0456d0:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f0456d4:	c720000c */ 	lwc1	$f0,0xc($t9)
/*  f0456d8:	c7a60080 */ 	lwc1	$f6,0x80($sp)
/*  f0456dc:	c7a4007c */ 	lwc1	$f4,0x7c($sp)
/*  f0456e0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0456e4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f0456e8:	8fa500f4 */ 	lw	$a1,0xf4($sp)
/*  f0456ec:	8fa60104 */ 	lw	$a2,0x104($sp)
/*  f0456f0:	46002201 */ 	sub.s	$f8,$f4,$f0
/*  f0456f4:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f0456f8:	27a70040 */ 	addiu	$a3,$sp,0x40
/*  f0456fc:	0c00a9bf */ 	jal	cd0002a6fc
/*  f045700:	e7a8001c */ 	swc1	$f8,0x1c($sp)
/*  f045704:	10400003 */ 	beqz	$v0,.L0f045714
.L0f045708:
/*  f045708:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04570c:	1000000b */ 	b	.L0f04573c
/*  f045710:	afa8008c */ 	sw	$t0,0x8c($sp)
.L0f045714:
/*  f045714:	3c077f1b */ 	lui	$a3,%hi(var7f1a8bdc)
/*  f045718:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f04571c:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045720:	24e78bdc */ 	addiu	$a3,$a3,%lo(var7f1a8bdc)
/*  f045724:	0c009393 */ 	jal	cd00024e4c
/*  f045728:	2406383b */ 	addiu	$a2,$zero,0x3848
/*  f04572c:	8fa400f8 */ 	lw	$a0,0xf8($sp)
/*  f045730:	8fa500fc */ 	lw	$a1,0xfc($sp)
/*  f045734:	0fc112da */ 	jal	func0f044b68
/*  f045738:	27a600dc */ 	addiu	$a2,$sp,0xdc
.L0f04573c:
/*  f04573c:	8fa400e8 */ 	lw	$a0,0xe8($sp)
/*  f045740:	0fc079ef */ 	jal	chrSetPerimEnabled
/*  f045744:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f045748:	8fa2008c */ 	lw	$v0,0x8c($sp)
.L0f04574c:
/*  f04574c:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045750:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f045754:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f045758:	03e00008 */ 	jr	$ra
/*  f04575c:	00000000 */ 	nop
);
#endif

GLOBAL_ASM(
glabel func0f045760
.late_rodata
glabel var7f1a9258
.word 0x3f4907a9
glabel var7f1a925c
.word 0x40c907a9
.text
/*  f045760:	27bdff88 */ 	addiu	$sp,$sp,-120
/*  f045764:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f045768:	afa40078 */ 	sw	$a0,0x78($sp)
/*  f04576c:	afa5007c */ 	sw	$a1,0x7c($sp)
/*  f045770:	afa60080 */ 	sw	$a2,0x80($sp)
/*  f045774:	8c8f001c */ 	lw	$t7,0x1c($a0)
/*  f045778:	10c00004 */ 	beqz	$a2,.L0f04578c
/*  f04577c:	afaf0074 */ 	sw	$t7,0x74($sp)
/*  f045780:	afa50044 */ 	sw	$a1,0x44($sp)
/*  f045784:	10000004 */ 	b	.L0f045798
/*  f045788:	afa70040 */ 	sw	$a3,0x40($sp)
.L0f04578c:
/*  f04578c:	8fa8007c */ 	lw	$t0,0x7c($sp)
/*  f045790:	afa70044 */ 	sw	$a3,0x44($sp)
/*  f045794:	afa80040 */ 	sw	$t0,0x40($sp)
.L0f045798:
/*  f045798:	8fa9007c */ 	lw	$t1,0x7c($sp)
/*  f04579c:	8faa0074 */ 	lw	$t2,0x74($sp)
/*  f0457a0:	44808000 */ 	mtc1	$zero,$f16
/*  f0457a4:	c5240000 */ 	lwc1	$f4,0x0($t1)
/*  f0457a8:	c5460008 */ 	lwc1	$f6,0x8($t2)
/*  f0457ac:	e7b0006c */ 	swc1	$f16,0x6c($sp)
/*  f0457b0:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f0457b4:	e7a80068 */ 	swc1	$f8,0x68($sp)
/*  f0457b8:	c52a0008 */ 	lwc1	$f10,0x8($t1)
/*  f0457bc:	c5440010 */ 	lwc1	$f4,0x10($t2)
/*  f0457c0:	46088032 */ 	c.eq.s	$f16,$f8
/*  f0457c4:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f0457c8:	45000006 */ 	bc1f	.L0f0457e4
/*  f0457cc:	e7a60070 */ 	swc1	$f6,0x70($sp)
/*  f0457d0:	46068032 */ 	c.eq.s	$f16,$f6
/*  f0457d4:	c7ae0088 */ 	lwc1	$f14,0x88($sp)
/*  f0457d8:	3c013f80 */ 	lui	$at,0x3f80
/*  f0457dc:	45030023 */ 	bc1tl	.L0f04586c
/*  f0457e0:	44811000 */ 	mtc1	$at,$f2
.L0f0457e4:
/*  f0457e4:	c7aa0070 */ 	lwc1	$f10,0x70($sp)
/*  f0457e8:	c7b20068 */ 	lwc1	$f18,0x68($sp)
/*  f0457ec:	460a5102 */ 	mul.s	$f4,$f10,$f10
/*  f0457f0:	00000000 */ 	nop
/*  f0457f4:	46129202 */ 	mul.s	$f8,$f18,$f18
/*  f0457f8:	0c012974 */ 	jal	sqrtf
/*  f0457fc:	46082300 */ 	add.s	$f12,$f4,$f8
/*  f045800:	44808000 */ 	mtc1	$zero,$f16
/*  f045804:	c7ae0088 */ 	lwc1	$f14,0x88($sp)
/*  f045808:	3c013f80 */ 	lui	$at,0x3f80
/*  f04580c:	4600803c */ 	c.lt.s	$f16,$f0
/*  f045810:	00000000 */ 	nop
/*  f045814:	45020010 */ 	bc1fl	.L0f045858
/*  f045818:	44811000 */ 	mtc1	$at,$f2
/*  f04581c:	3c013f80 */ 	lui	$at,0x3f80
/*  f045820:	44813000 */ 	mtc1	$at,$f6
/*  f045824:	c7ae0088 */ 	lwc1	$f14,0x88($sp)
/*  f045828:	c7b20068 */ 	lwc1	$f18,0x68($sp)
/*  f04582c:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f045830:	c7aa0070 */ 	lwc1	$f10,0x70($sp)
/*  f045834:	46027302 */ 	mul.s	$f12,$f14,$f2
/*  f045838:	00000000 */ 	nop
/*  f04583c:	460c9482 */ 	mul.s	$f18,$f18,$f12
/*  f045840:	00000000 */ 	nop
/*  f045844:	460c5102 */ 	mul.s	$f4,$f10,$f12
/*  f045848:	e7b20068 */ 	swc1	$f18,0x68($sp)
/*  f04584c:	1000000a */ 	b	.L0f045878
/*  f045850:	e7a40070 */ 	swc1	$f4,0x70($sp)
/*  f045854:	44811000 */ 	mtc1	$at,$f2
.L0f045858:
/*  f045858:	e7ae0070 */ 	swc1	$f14,0x70($sp)
/*  f04585c:	46027302 */ 	mul.s	$f12,$f14,$f2
/*  f045860:	10000006 */ 	b	.L0f04587c
/*  f045864:	3c013f80 */ 	lui	$at,0x3f80
/*  f045868:	44811000 */ 	mtc1	$at,$f2
.L0f04586c:
/*  f04586c:	e7ae0070 */ 	swc1	$f14,0x70($sp)
/*  f045870:	46027302 */ 	mul.s	$f12,$f14,$f2
/*  f045874:	00000000 */ 	nop
.L0f045878:
/*  f045878:	3c013f80 */ 	lui	$at,0x3f80
.L0f04587c:
/*  f04587c:	44814000 */ 	mtc1	$at,$f8
/*  f045880:	3c017f1b */ 	lui	$at,%hi(var7f1a9258)
/*  f045884:	460c403c */ 	c.lt.s	$f8,$f12
/*  f045888:	00000000 */ 	nop
/*  f04588c:	45000003 */ 	bc1f	.L0f04589c
/*  f045890:	00000000 */ 	nop
/*  f045894:	10000005 */ 	b	.L0f0458ac
/*  f045898:	c42c9258 */ 	lwc1	$f12,%lo(var7f1a9258)($at)
.L0f04589c:
/*  f04589c:	0fc25a74 */ 	jal	func0f0969d0
/*  f0458a0:	00000000 */ 	nop
/*  f0458a4:	44808000 */ 	mtc1	$zero,$f16
/*  f0458a8:	46000306 */ 	mov.s	$f12,$f0
.L0f0458ac:
/*  f0458ac:	8fab0080 */ 	lw	$t3,0x80($sp)
/*  f0458b0:	15600007 */ 	bnez	$t3,.L0f0458d0
/*  f0458b4:	00000000 */ 	nop
/*  f0458b8:	46106032 */ 	c.eq.s	$f12,$f16
/*  f0458bc:	3c017f1b */ 	lui	$at,%hi(var7f1a925c)
/*  f0458c0:	45010003 */ 	bc1t	.L0f0458d0
/*  f0458c4:	00000000 */ 	nop
/*  f0458c8:	c426925c */ 	lwc1	$f6,%lo(var7f1a925c)($at)
/*  f0458cc:	460c3301 */ 	sub.s	$f12,$f6,$f12
.L0f0458d0:
/*  f0458d0:	0c0068f4 */ 	jal	cosf
/*  f0458d4:	e7ac0054 */ 	swc1	$f12,0x54($sp)
/*  f0458d8:	c7ac0054 */ 	lwc1	$f12,0x54($sp)
/*  f0458dc:	0c0068f7 */ 	jal	sinf
/*  f0458e0:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*  f0458e4:	c7aa0070 */ 	lwc1	$f10,0x70($sp)
/*  f0458e8:	c7a80038 */ 	lwc1	$f8,0x38($sp)
/*  f0458ec:	c7b20068 */ 	lwc1	$f18,0x68($sp)
/*  f0458f0:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f0458f4:	46004187 */ 	neg.s	$f6,$f8
/*  f0458f8:	44808000 */ 	mtc1	$zero,$f16
/*  f0458fc:	46123282 */ 	mul.s	$f10,$f6,$f18
/*  f045900:	c7ac0054 */ 	lwc1	$f12,0x54($sp)
/*  f045904:	e7b0004c */ 	swc1	$f16,0x4c($sp)
/*  f045908:	460a2200 */ 	add.s	$f8,$f4,$f10
/*  f04590c:	0c0068f7 */ 	jal	sinf
/*  f045910:	e7a80048 */ 	swc1	$f8,0x48($sp)
/*  f045914:	c7ac0054 */ 	lwc1	$f12,0x54($sp)
/*  f045918:	0c0068f4 */ 	jal	cosf
/*  f04591c:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*  f045920:	c7a60038 */ 	lwc1	$f6,0x38($sp)
/*  f045924:	c7aa0068 */ 	lwc1	$f10,0x68($sp)
/*  f045928:	8fac007c */ 	lw	$t4,0x7c($sp)
/*  f04592c:	46003107 */ 	neg.s	$f4,$f6
/*  f045930:	c7a60070 */ 	lwc1	$f6,0x70($sp)
/*  f045934:	460a2202 */ 	mul.s	$f8,$f4,$f10
/*  f045938:	8fae0044 */ 	lw	$t6,0x44($sp)
/*  f04593c:	8faf0040 */ 	lw	$t7,0x40($sp)
/*  f045940:	46003102 */ 	mul.s	$f4,$f6,$f0
/*  f045944:	c7a60048 */ 	lwc1	$f6,0x48($sp)
/*  f045948:	8fa40078 */ 	lw	$a0,0x78($sp)
/*  f04594c:	8fa50074 */ 	lw	$a1,0x74($sp)
/*  f045950:	8fa60074 */ 	lw	$a2,0x74($sp)
/*  f045954:	8fb8009c */ 	lw	$t8,0x9c($sp)
/*  f045958:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f04595c:	46044281 */ 	sub.s	$f10,$f8,$f4
/*  f045960:	24a50008 */ 	addiu	$a1,$a1,0x8
/*  f045964:	24c60028 */ 	addiu	$a2,$a2,0x28
/*  f045968:	27a7005c */ 	addiu	$a3,$sp,0x5c
/*  f04596c:	e7aa0050 */ 	swc1	$f10,0x50($sp)
/*  f045970:	c5880000 */ 	lwc1	$f8,0x0($t4)
/*  f045974:	46083100 */ 	add.s	$f4,$f6,$f8
/*  f045978:	e7a4005c */ 	swc1	$f4,0x5c($sp)
/*  f04597c:	c5860004 */ 	lwc1	$f6,0x4($t4)
/*  f045980:	e7a60060 */ 	swc1	$f6,0x60($sp)
/*  f045984:	c5880008 */ 	lwc1	$f8,0x8($t4)
/*  f045988:	c7a60098 */ 	lwc1	$f6,0x98($sp)
/*  f04598c:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f045990:	46085100 */ 	add.s	$f4,$f10,$f8
/*  f045994:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f045998:	e7a60018 */ 	swc1	$f6,0x18($sp)
/*  f04599c:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f0459a0:	c48a0024 */ 	lwc1	$f10,0x24($a0)
/*  f0459a4:	afa60030 */ 	sw	$a2,0x30($sp)
/*  f0459a8:	afa50034 */ 	sw	$a1,0x34($sp)
/*  f0459ac:	afb90024 */ 	sw	$t9,0x24($sp)
/*  f0459b0:	afb80020 */ 	sw	$t8,0x20($sp)
/*  f0459b4:	0fc1130e */ 	jal	func0f044c38
/*  f0459b8:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*  f0459bc:	8fa50034 */ 	lw	$a1,0x34($sp)
/*  f0459c0:	10400026 */ 	beqz	$v0,.L0f045a5c
/*  f0459c4:	8fa60030 */ 	lw	$a2,0x30($sp)
/*  f0459c8:	8fa8008c */ 	lw	$t0,0x8c($sp)
/*  f0459cc:	8fa40078 */ 	lw	$a0,0x78($sp)
/*  f0459d0:	8fa90090 */ 	lw	$t1,0x90($sp)
/*  f0459d4:	51000009 */ 	beqzl	$t0,.L0f0459fc
/*  f0459d8:	8fab00a0 */ 	lw	$t3,0xa0($sp)
/*  f0459dc:	8faa009c */ 	lw	$t2,0x9c($sp)
/*  f0459e0:	27a7005c */ 	addiu	$a3,$sp,0x5c
/*  f0459e4:	afa90010 */ 	sw	$t1,0x10($sp)
/*  f0459e8:	0fc0d917 */ 	jal	func0f03645c
/*  f0459ec:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f0459f0:	5040001b */ 	beqzl	$v0,.L0f045a60
/*  f0459f4:	00001025 */ 	or	$v0,$zero,$zero
/*  f0459f8:	8fab00a0 */ 	lw	$t3,0xa0($sp)
.L0f0459fc:
/*  f0459fc:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f045a00:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f045a04:	5160000d */ 	beqzl	$t3,.L0f045a3c
/*  f045a08:	a04e0002 */ 	sb	$t6,0x2($v0)
/*  f045a0c:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f045a10:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f045a14:	a04c0003 */ 	sb	$t4,0x3($v0)
/*  f045a18:	c7a8005c */ 	lwc1	$f8,0x5c($sp)
/*  f045a1c:	e448002c */ 	swc1	$f8,0x2c($v0)
/*  f045a20:	c7a40060 */ 	lwc1	$f4,0x60($sp)
/*  f045a24:	e4440030 */ 	swc1	$f4,0x30($v0)
/*  f045a28:	c7a60064 */ 	lwc1	$f6,0x64($sp)
/*  f045a2c:	e4460034 */ 	swc1	$f6,0x34($v0)
/*  f045a30:	1000000b */ 	b	.L0f045a60
/*  f045a34:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f045a38:	a04e0002 */ 	sb	$t6,0x2($v0)
.L0f045a3c:
/*  f045a3c:	c7aa005c */ 	lwc1	$f10,0x5c($sp)
/*  f045a40:	e44a0004 */ 	swc1	$f10,0x4($v0)
/*  f045a44:	c7a80060 */ 	lwc1	$f8,0x60($sp)
/*  f045a48:	e4480008 */ 	swc1	$f8,0x8($v0)
/*  f045a4c:	c7a40064 */ 	lwc1	$f4,0x64($sp)
/*  f045a50:	e444000c */ 	swc1	$f4,0xc($v0)
/*  f045a54:	10000002 */ 	b	.L0f045a60
/*  f045a58:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f045a5c:
/*  f045a5c:	00001025 */ 	or	$v0,$zero,$zero
.L0f045a60:
/*  f045a60:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f045a64:	27bd0078 */ 	addiu	$sp,$sp,0x78
/*  f045a68:	03e00008 */ 	jr	$ra
/*  f045a6c:	00000000 */ 	nop
);

/**
 * Check for doors in front of the chr and open them if possible.
 *
 * I'm guessing the coord argument is a position in front of the chr, and the
 * collision check is looking for doors between the chr and that point.
 *
 * - Multiplayer simulants can open any doors
 * - Solo chrs cannot open doors with OBJFLAG2_AICANNOTUSE
 * - In ntsc-beta, solo chrs can bring down lasers even if they have that flag
 *
 * The chr must be within 200cm of the door unless it's a laser.
 */
struct prop *chrOpenDoor(struct chrdata *chr, struct coord *coord)
{
	struct prop *doorprop = NULL;

	if (cd0002d7c0(&chr->prop->pos, chr->prop->rooms, coord, 0x5020, 1, 0, 0) == CDRESULT_COLLISION) {
		doorprop = cdGetObstacle();
	}

	if (doorprop) {
		struct doorobj *door = doorprop->door;

#if VERSION >= VERSION_NTSC_1_0
		if (chr->aibot || (door->base.flags2 & OBJFLAG2_AICANNOTUSE) == 0)
#else
		if (chr->aibot
				|| (door->base.flags2 & OBJFLAG2_AICANNOTUSE) == 0
				|| (door->doorflags & DOORFLAG_DAMAGEONCONTACT))
#endif
		{
			f32 xdiff = doorprop->pos.x - chr->prop->pos.x;
			f32 zdiff = doorprop->pos.z - chr->prop->pos.z;

			if (xdiff * xdiff + zdiff * zdiff < 200 * 200 || (door->doorflags & DOORFLAG_DAMAGEONCONTACT)) {
				chrGoPosClearRestartTtl(chr);
				doorsChooseSwingDirection(chr->prop, doorprop->door);

				if (!doorCallLift(doorprop, false)) {
					doorsRequestMode(doorprop->door, DOORMODE_OPENING);
				}
			} else {
				doorprop = NULL;
			}
		} else {
			doorprop = NULL;
		}
	}

	return doorprop;
}

GLOBAL_ASM(
glabel func0f045b9c
.late_rodata
glabel var7f1a9264
.word 0x404907a9
glabel var7f1a9268
.word 0x40c907a9
glabel var7f1a926c
.word 0x3fa147ae
glabel var7f1a9270
.word 0x3fa147ae
glabel var7f1a9274
.word 0x3fa147ae
glabel var7f1a9278
.word 0x3f8ccccd
glabel var7f1a927c
.word 0x3f8ccccd
.text
/*  f045b9c:	27bdfef0 */ 	addiu	$sp,$sp,-272
/*  f045ba0:	afbf0084 */ 	sw	$ra,0x84($sp)
/*  f045ba4:	afb70080 */ 	sw	$s7,0x80($sp)
/*  f045ba8:	afb6007c */ 	sw	$s6,0x7c($sp)
/*  f045bac:	afb50078 */ 	sw	$s5,0x78($sp)
/*  f045bb0:	afb40074 */ 	sw	$s4,0x74($sp)
/*  f045bb4:	afb30070 */ 	sw	$s3,0x70($sp)
/*  f045bb8:	afb2006c */ 	sw	$s2,0x6c($sp)
/*  f045bbc:	afb10068 */ 	sw	$s1,0x68($sp)
/*  f045bc0:	afb00064 */ 	sw	$s0,0x64($sp)
/*  f045bc4:	f7be0058 */ 	sdc1	$f30,0x58($sp)
/*  f045bc8:	f7bc0050 */ 	sdc1	$f28,0x50($sp)
/*  f045bcc:	f7ba0048 */ 	sdc1	$f26,0x48($sp)
/*  f045bd0:	f7b80040 */ 	sdc1	$f24,0x40($sp)
/*  f045bd4:	f7b60038 */ 	sdc1	$f22,0x38($sp)
/*  f045bd8:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*  f045bdc:	afa7011c */ 	sw	$a3,0x11c($sp)
/*  f045be0:	8c8e0014 */ 	lw	$t6,0x14($a0)
/*  f045be4:	00c08025 */ 	or	$s0,$a2,$zero
/*  f045be8:	00809025 */ 	or	$s2,$a0,$zero
/*  f045bec:	31cf0010 */ 	andi	$t7,$t6,0x10
/*  f045bf0:	00a09825 */ 	or	$s3,$a1,$zero
/*  f045bf4:	8c91001c */ 	lw	$s1,0x1c($a0)
/*  f045bf8:	11e00002 */ 	beqz	$t7,.L0f045c04
/*  f045bfc:	3416803d */ 	dli	$s6,0x803d
/*  f045c00:	2416003f */ 	addiu	$s6,$zero,0x3f
.L0f045c04:
/*  f045c04:	3c017f1b */ 	lui	$at,%hi(var7f1a9264)
/*  f045c08:	c43e9264 */ 	lwc1	$f30,%lo(var7f1a9264)($at)
/*  f045c0c:	3c017f1b */ 	lui	$at,%hi(var7f1a9268)
/*  f045c10:	4480d000 */ 	mtc1	$zero,$f26
/*  f045c14:	c43c9268 */ 	lwc1	$f28,%lo(var7f1a9268)($at)
/*  f045c18:	afa000f0 */ 	sw	$zero,0xf0($sp)
/*  f045c1c:	24170001 */ 	addiu	$s7,$zero,0x1
/*  f045c20:	24150004 */ 	addiu	$s5,$zero,0x4
/*  f045c24:	27b400f4 */ 	addiu	$s4,$sp,0xf4
.L0f045c28:
/*  f045c28:	82020000 */ 	lb	$v0,0x0($s0)
/*  f045c2c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f045c30:	02402025 */ 	or	$a0,$s2,$zero
/*  f045c34:	10400003 */ 	beqz	$v0,.L0f045c44
/*  f045c38:	26250008 */ 	addiu	$a1,$s1,0x8
/*  f045c3c:	1441002d */ 	bne	$v0,$at,.L0f045cf4
/*  f045c40:	00000000 */ 	nop
.L0f045c44:
/*  f045c44:	c6640000 */ 	lwc1	$f4,0x0($s3)
/*  f045c48:	26180010 */ 	addiu	$t8,$s0,0x10
/*  f045c4c:	2619001c */ 	addiu	$t9,$s0,0x1c
/*  f045c50:	e7a40100 */ 	swc1	$f4,0x100($sp)
/*  f045c54:	c6660004 */ 	lwc1	$f6,0x4($s3)
/*  f045c58:	8faa011c */ 	lw	$t2,0x11c($sp)
/*  f045c5c:	24090030 */ 	addiu	$t1,$zero,0x30
/*  f045c60:	e7a60104 */ 	swc1	$f6,0x104($sp)
/*  f045c64:	c6680008 */ 	lwc1	$f8,0x8($s3)
/*  f045c68:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f045c6c:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f045c70:	e7a80108 */ 	swc1	$f8,0x108($sp)
/*  f045c74:	c6400024 */ 	lwc1	$f0,0x24($s2)
/*  f045c78:	afa90020 */ 	sw	$t1,0x20($sp)
/*  f045c7c:	26260028 */ 	addiu	$a2,$s1,0x28
/*  f045c80:	46000287 */ 	neg.s	$f10,$f0
/*  f045c84:	27a70100 */ 	addiu	$a3,$sp,0x100
/*  f045c88:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*  f045c8c:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f045c90:	0fc1130e */ 	jal	func0f044c38
/*  f045c94:	e7a0001c */ 	swc1	$f0,0x1c($sp)
/*  f045c98:	5040000b */ 	beqzl	$v0,.L0f045cc8
/*  f045c9c:	82020000 */ 	lb	$v0,0x0($s0)
/*  f045ca0:	a2170002 */ 	sb	$s7,0x2($s0)
/*  f045ca4:	c7b20100 */ 	lwc1	$f18,0x100($sp)
/*  f045ca8:	e6120004 */ 	swc1	$f18,0x4($s0)
/*  f045cac:	c7a40104 */ 	lwc1	$f4,0x104($sp)
/*  f045cb0:	e6040008 */ 	swc1	$f4,0x8($s0)
/*  f045cb4:	c7a60108 */ 	lwc1	$f6,0x108($sp)
/*  f045cb8:	a2150000 */ 	sb	$s5,0x0($s0)
/*  f045cbc:	100001a9 */ 	b	.L0f046364
/*  f045cc0:	e606000c */ 	swc1	$f6,0xc($s0)
/*  f045cc4:	82020000 */ 	lb	$v0,0x0($s0)
.L0f045cc8:
/*  f045cc8:	24010002 */ 	addiu	$at,$zero,0x2
/*  f045ccc:	14400004 */ 	bnez	$v0,.L0f045ce0
/*  f045cd0:	00000000 */ 	nop
/*  f045cd4:	a2170000 */ 	sb	$s7,0x0($s0)
/*  f045cd8:	100001a2 */ 	b	.L0f046364
/*  f045cdc:	a2000001 */ 	sb	$zero,0x1($s0)
.L0f045ce0:
/*  f045ce0:	144101a0 */ 	bne	$v0,$at,.L0f046364
/*  f045ce4:	240b0003 */ 	addiu	$t3,$zero,0x3
/*  f045ce8:	a20b0000 */ 	sb	$t3,0x0($s0)
/*  f045cec:	1000019d */ 	b	.L0f046364
/*  f045cf0:	a2000001 */ 	sb	$zero,0x1($s0)
.L0f045cf4:
/*  f045cf4:	16e20032 */ 	bne	$s7,$v0,.L0f045dc0
/*  f045cf8:	24010003 */ 	addiu	$at,$zero,0x3
/*  f045cfc:	3c017f1b */ 	lui	$at,%hi(var7f1a926c)
/*  f045d00:	c42a926c */ 	lwc1	$f10,%lo(var7f1a926c)($at)
/*  f045d04:	c6480024 */ 	lwc1	$f8,0x24($s2)
/*  f045d08:	240c0030 */ 	addiu	$t4,$zero,0x30
/*  f045d0c:	afac0024 */ 	sw	$t4,0x24($sp)
/*  f045d10:	460a4002 */ 	mul.s	$f0,$f8,$f10
/*  f045d14:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f045d18:	e7ba0020 */ 	swc1	$f26,0x20($sp)
/*  f045d1c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f045d20:	afb30018 */ 	sw	$s3,0x18($sp)
/*  f045d24:	afb70014 */ 	sw	$s7,0x14($sp)
/*  f045d28:	02402025 */ 	or	$a0,$s2,$zero
/*  f045d2c:	e7a00010 */ 	swc1	$f0,0x10($sp)
/*  f045d30:	e7a000e8 */ 	swc1	$f0,0xe8($sp)
/*  f045d34:	26050010 */ 	addiu	$a1,$s0,0x10
/*  f045d38:	02e03025 */ 	or	$a2,$s7,$zero
/*  f045d3c:	0fc115d8 */ 	jal	func0f045760
/*  f045d40:	02803825 */ 	or	$a3,$s4,$zero
/*  f045d44:	10400003 */ 	beqz	$v0,.L0f045d54
/*  f045d48:	c7a000e8 */ 	lwc1	$f0,0xe8($sp)
/*  f045d4c:	10000185 */ 	b	.L0f046364
/*  f045d50:	a2150000 */ 	sb	$s5,0x0($s0)
.L0f045d54:
/*  f045d54:	240d0030 */ 	addiu	$t5,$zero,0x30
/*  f045d58:	afad0024 */ 	sw	$t5,0x24($sp)
/*  f045d5c:	02402025 */ 	or	$a0,$s2,$zero
/*  f045d60:	2605001c */ 	addiu	$a1,$s0,0x1c
/*  f045d64:	00003025 */ 	or	$a2,$zero,$zero
/*  f045d68:	02803825 */ 	or	$a3,$s4,$zero
/*  f045d6c:	e7a00010 */ 	swc1	$f0,0x10($sp)
/*  f045d70:	afb70014 */ 	sw	$s7,0x14($sp)
/*  f045d74:	afb30018 */ 	sw	$s3,0x18($sp)
/*  f045d78:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f045d7c:	e7ba0020 */ 	swc1	$f26,0x20($sp)
/*  f045d80:	0fc115d8 */ 	jal	func0f045760
/*  f045d84:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f045d88:	50400004 */ 	beqzl	$v0,.L0f045d9c
/*  f045d8c:	820e0001 */ 	lb	$t6,0x1($s0)
/*  f045d90:	10000174 */ 	b	.L0f046364
/*  f045d94:	a2150000 */ 	sb	$s5,0x0($s0)
/*  f045d98:	820e0001 */ 	lb	$t6,0x1($s0)
.L0f045d9c:
/*  f045d9c:	24190002 */ 	addiu	$t9,$zero,0x2
/*  f045da0:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*  f045da4:	a20f0001 */ 	sb	$t7,0x1($s0)
/*  f045da8:	82180001 */ 	lb	$t8,0x1($s0)
/*  f045dac:	2b010006 */ 	slti	$at,$t8,0x6
/*  f045db0:	5420016d */ 	bnezl	$at,.L0f046368
/*  f045db4:	8fab00f0 */ 	lw	$t3,0xf0($sp)
/*  f045db8:	1000016a */ 	b	.L0f046364
/*  f045dbc:	a2190000 */ 	sb	$t9,0x0($s0)
.L0f045dc0:
/*  f045dc0:	1441003c */ 	bne	$v0,$at,.L0f045eb4
/*  f045dc4:	02402025 */ 	or	$a0,$s2,$zero
/*  f045dc8:	3c017f1b */ 	lui	$at,%hi(var7f1a9270)
/*  f045dcc:	c4249270 */ 	lwc1	$f4,%lo(var7f1a9270)($at)
/*  f045dd0:	c6520024 */ 	lwc1	$f18,0x24($s2)
/*  f045dd4:	24090030 */ 	addiu	$t1,$zero,0x30
/*  f045dd8:	afa90024 */ 	sw	$t1,0x24($sp)
/*  f045ddc:	46049002 */ 	mul.s	$f0,$f18,$f4
/*  f045de0:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f045de4:	e7ba0020 */ 	swc1	$f26,0x20($sp)
/*  f045de8:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f045dec:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f045df0:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f045df4:	26050010 */ 	addiu	$a1,$s0,0x10
/*  f045df8:	e7a00010 */ 	swc1	$f0,0x10($sp)
/*  f045dfc:	e7a000e4 */ 	swc1	$f0,0xe4($sp)
/*  f045e00:	02e03025 */ 	or	$a2,$s7,$zero
/*  f045e04:	0fc115d8 */ 	jal	func0f045760
/*  f045e08:	02803825 */ 	or	$a3,$s4,$zero
/*  f045e0c:	10400003 */ 	beqz	$v0,.L0f045e1c
/*  f045e10:	c7a000e4 */ 	lwc1	$f0,0xe4($sp)
/*  f045e14:	10000153 */ 	b	.L0f046364
/*  f045e18:	a2150000 */ 	sb	$s5,0x0($s0)
.L0f045e1c:
/*  f045e1c:	240a0030 */ 	addiu	$t2,$zero,0x30
/*  f045e20:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f045e24:	02402025 */ 	or	$a0,$s2,$zero
/*  f045e28:	2605001c */ 	addiu	$a1,$s0,0x1c
/*  f045e2c:	00003025 */ 	or	$a2,$zero,$zero
/*  f045e30:	02803825 */ 	or	$a3,$s4,$zero
/*  f045e34:	e7a00010 */ 	swc1	$f0,0x10($sp)
/*  f045e38:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f045e3c:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f045e40:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f045e44:	e7ba0020 */ 	swc1	$f26,0x20($sp)
/*  f045e48:	0fc115d8 */ 	jal	func0f045760
/*  f045e4c:	afa00028 */ 	sw	$zero,0x28($sp)
/*  f045e50:	50400004 */ 	beqzl	$v0,.L0f045e64
/*  f045e54:	820b0001 */ 	lb	$t3,0x1($s0)
/*  f045e58:	10000142 */ 	b	.L0f046364
/*  f045e5c:	a2150000 */ 	sb	$s5,0x0($s0)
/*  f045e60:	820b0001 */ 	lb	$t3,0x1($s0)
.L0f045e64:
/*  f045e64:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f045e68:	a20c0001 */ 	sb	$t4,0x1($s0)
/*  f045e6c:	820d0001 */ 	lb	$t5,0x1($s0)
/*  f045e70:	29a10006 */ 	slti	$at,$t5,0x6
/*  f045e74:	5420013c */ 	bnezl	$at,.L0f046368
/*  f045e78:	8fab00f0 */ 	lw	$t3,0xf0($sp)
/*  f045e7c:	a2000002 */ 	sb	$zero,0x2($s0)
/*  f045e80:	820e0002 */ 	lb	$t6,0x2($s0)
/*  f045e84:	a20e0003 */ 	sb	$t6,0x3($s0)
/*  f045e88:	c6600000 */ 	lwc1	$f0,0x0($s3)
/*  f045e8c:	e6000004 */ 	swc1	$f0,0x4($s0)
/*  f045e90:	e600002c */ 	swc1	$f0,0x2c($s0)
/*  f045e94:	c6600004 */ 	lwc1	$f0,0x4($s3)
/*  f045e98:	e6000008 */ 	swc1	$f0,0x8($s0)
/*  f045e9c:	e6000030 */ 	swc1	$f0,0x30($s0)
/*  f045ea0:	c6600008 */ 	lwc1	$f0,0x8($s3)
/*  f045ea4:	a2000000 */ 	sb	$zero,0x0($s0)
/*  f045ea8:	e600000c */ 	swc1	$f0,0xc($s0)
/*  f045eac:	1000012d */ 	b	.L0f046364
/*  f045eb0:	e6000034 */ 	swc1	$f0,0x34($s0)
.L0f045eb4:
/*  f045eb4:	16a20034 */ 	bne	$s5,$v0,.L0f045f88
/*  f045eb8:	24010005 */ 	addiu	$at,$zero,0x5
/*  f045ebc:	8faf011c */ 	lw	$t7,0x11c($sp)
/*  f045ec0:	02e01025 */ 	or	$v0,$s7,$zero
/*  f045ec4:	26250008 */ 	addiu	$a1,$s1,0x8
/*  f045ec8:	26260028 */ 	addiu	$a2,$s1,0x28
/*  f045ecc:	26030010 */ 	addiu	$v1,$s0,0x10
/*  f045ed0:	2608001c */ 	addiu	$t0,$s0,0x1c
/*  f045ed4:	15e00014 */ 	bnez	$t7,.L0f045f28
/*  f045ed8:	26070004 */ 	addiu	$a3,$s0,0x4
/*  f045edc:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f045ee0:	c6680000 */ 	lwc1	$f8,0x0($s3)
/*  f045ee4:	46083032 */ 	c.eq.s	$f6,$f8
/*  f045ee8:	00000000 */ 	nop
/*  f045eec:	4502000f */ 	bc1fl	.L0f045f2c
/*  f045ef0:	afa30010 */ 	sw	$v1,0x10($sp)
/*  f045ef4:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f045ef8:	c6720004 */ 	lwc1	$f18,0x4($s3)
/*  f045efc:	46125032 */ 	c.eq.s	$f10,$f18
/*  f045f00:	00000000 */ 	nop
/*  f045f04:	45020009 */ 	bc1fl	.L0f045f2c
/*  f045f08:	afa30010 */ 	sw	$v1,0x10($sp)
/*  f045f0c:	c604000c */ 	lwc1	$f4,0xc($s0)
/*  f045f10:	c6660008 */ 	lwc1	$f6,0x8($s3)
/*  f045f14:	46062032 */ 	c.eq.s	$f4,$f6
/*  f045f18:	00000000 */ 	nop
/*  f045f1c:	45020003 */ 	bc1fl	.L0f045f2c
/*  f045f20:	afa30010 */ 	sw	$v1,0x10($sp)
/*  f045f24:	00001025 */ 	or	$v0,$zero,$zero
.L0f045f28:
/*  f045f28:	afa30010 */ 	sw	$v1,0x10($sp)
.L0f045f2c:
/*  f045f2c:	afa80014 */ 	sw	$t0,0x14($sp)
/*  f045f30:	c6400024 */ 	lwc1	$f0,0x24($s2)
/*  f045f34:	afa20024 */ 	sw	$v0,0x24($sp)
/*  f045f38:	afb60020 */ 	sw	$s6,0x20($sp)
/*  f045f3c:	46000207 */ 	neg.s	$f8,$f0
/*  f045f40:	02402025 */ 	or	$a0,$s2,$zero
/*  f045f44:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*  f045f48:	0fc1146a */ 	jal	func0f0451a8
/*  f045f4c:	e7a0001c */ 	swc1	$f0,0x1c($sp)
/*  f045f50:	1040000a */ 	beqz	$v0,.L0f045f7c
/*  f045f54:	24180005 */ 	addiu	$t8,$zero,0x5
/*  f045f58:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f045f5c:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f045f60:	c604000c */ 	lwc1	$f4,0xc($s0)
/*  f045f64:	a2170003 */ 	sb	$s7,0x3($s0)
/*  f045f68:	a2000000 */ 	sb	$zero,0x0($s0)
/*  f045f6c:	e60a002c */ 	swc1	$f10,0x2c($s0)
/*  f045f70:	e6120030 */ 	swc1	$f18,0x30($s0)
/*  f045f74:	100000fb */ 	b	.L0f046364
/*  f045f78:	e6040034 */ 	swc1	$f4,0x34($s0)
.L0f045f7c:
/*  f045f7c:	a2180000 */ 	sb	$t8,0x0($s0)
/*  f045f80:	100000f8 */ 	b	.L0f046364
/*  f045f84:	a2000001 */ 	sb	$zero,0x1($s0)
.L0f045f88:
/*  f045f88:	144100f6 */ 	bne	$v0,$at,.L0f046364
/*  f045f8c:	3c017f1b */ 	lui	$at,%hi(var7f1a9274)
/*  f045f90:	c4289274 */ 	lwc1	$f8,%lo(var7f1a9274)($at)
/*  f045f94:	c6460024 */ 	lwc1	$f6,0x24($s2)
/*  f045f98:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f045f9c:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*  f045fa0:	46083602 */ 	mul.s	$f24,$f6,$f8
/*  f045fa4:	c6260010 */ 	lwc1	$f6,0x10($s1)
/*  f045fa8:	c604000c */ 	lwc1	$f4,0xc($s0)
/*  f045fac:	46125301 */ 	sub.s	$f12,$f10,$f18
/*  f045fb0:	0fc259d4 */ 	jal	atan2f
/*  f045fb4:	46062381 */ 	sub.s	$f14,$f4,$f6
/*  f045fb8:	c6160010 */ 	lwc1	$f22,0x10($s0)
/*  f045fbc:	c6320008 */ 	lwc1	$f18,0x8($s1)
/*  f045fc0:	c6100018 */ 	lwc1	$f16,0x18($s0)
/*  f045fc4:	c62a0010 */ 	lwc1	$f10,0x10($s1)
/*  f045fc8:	4612b301 */ 	sub.s	$f12,$f22,$f18
/*  f045fcc:	46000506 */ 	mov.s	$f20,$f0
/*  f045fd0:	0fc259d4 */ 	jal	atan2f
/*  f045fd4:	460a8381 */ 	sub.s	$f14,$f16,$f10
/*  f045fd8:	4600a581 */ 	sub.s	$f22,$f20,$f0
/*  f045fdc:	c612001c */ 	lwc1	$f18,0x1c($s0)
/*  f045fe0:	c6300008 */ 	lwc1	$f16,0x8($s1)
/*  f045fe4:	c60a0024 */ 	lwc1	$f10,0x24($s0)
/*  f045fe8:	c6280010 */ 	lwc1	$f8,0x10($s1)
/*  f045fec:	46109301 */ 	sub.s	$f12,$f18,$f16
/*  f045ff0:	e7b600d0 */ 	swc1	$f22,0xd0($sp)
/*  f045ff4:	0fc259d4 */ 	jal	atan2f
/*  f045ff8:	46085381 */ 	sub.s	$f14,$f10,$f8
/*  f045ffc:	c7b000d0 */ 	lwc1	$f16,0xd0($sp)
/*  f046000:	4600a301 */ 	sub.s	$f12,$f20,$f0
/*  f046004:	02803825 */ 	or	$a3,$s4,$zero
/*  f046008:	02402025 */ 	or	$a0,$s2,$zero
/*  f04600c:	461a803c */ 	c.lt.s	$f16,$f26
/*  f046010:	46006086 */ 	mov.s	$f2,$f12
/*  f046014:	2605001c */ 	addiu	$a1,$s0,0x1c
/*  f046018:	00003025 */ 	or	$a2,$zero,$zero
/*  f04601c:	45000002 */ 	bc1f	.L0f046028
/*  f046020:	3c017f1b */ 	lui	$at,%hi(var7f1a9278)
/*  f046024:	461c8400 */ 	add.s	$f16,$f16,$f28
.L0f046028:
/*  f046028:	4610f03e */ 	c.le.s	$f30,$f16
/*  f04602c:	00000000 */ 	nop
/*  f046030:	45020003 */ 	bc1fl	.L0f046040
/*  f046034:	461a803c */ 	c.lt.s	$f16,$f26
/*  f046038:	461c8401 */ 	sub.s	$f16,$f16,$f28
/*  f04603c:	461a803c */ 	c.lt.s	$f16,$f26
.L0f046040:
/*  f046040:	00000000 */ 	nop
/*  f046044:	45020003 */ 	bc1fl	.L0f046054
/*  f046048:	461a603c */ 	c.lt.s	$f12,$f26
/*  f04604c:	46008407 */ 	neg.s	$f16,$f16
/*  f046050:	461a603c */ 	c.lt.s	$f12,$f26
.L0f046054:
/*  f046054:	00000000 */ 	nop
/*  f046058:	45020003 */ 	bc1fl	.L0f046068
/*  f04605c:	4602f03e */ 	c.le.s	$f30,$f2
/*  f046060:	461c6080 */ 	add.s	$f2,$f12,$f28
/*  f046064:	4602f03e */ 	c.le.s	$f30,$f2
.L0f046068:
/*  f046068:	00000000 */ 	nop
/*  f04606c:	45020003 */ 	bc1fl	.L0f04607c
/*  f046070:	461a103c */ 	c.lt.s	$f2,$f26
/*  f046074:	461c1081 */ 	sub.s	$f2,$f2,$f28
/*  f046078:	461a103c */ 	c.lt.s	$f2,$f26
.L0f04607c:
/*  f04607c:	00000000 */ 	nop
/*  f046080:	45020003 */ 	bc1fl	.L0f046090
/*  f046084:	4602803c */ 	c.lt.s	$f16,$f2
/*  f046088:	46001087 */ 	neg.s	$f2,$f2
/*  f04608c:	4602803c */ 	c.lt.s	$f16,$f2
.L0f046090:
/*  f046090:	00000000 */ 	nop
/*  f046094:	45000057 */ 	bc1f	.L0f0461f4
/*  f046098:	00000000 */ 	nop
/*  f04609c:	3c017f1b */ 	lui	$at,%hi(var7f1a927c)
/*  f0460a0:	c4249278 */ 	lwc1	$f4,%lo(var7f1a9278)($at)
/*  f0460a4:	02402025 */ 	or	$a0,$s2,$zero
/*  f0460a8:	26050010 */ 	addiu	$a1,$s0,0x10
/*  f0460ac:	4604c582 */ 	mul.s	$f22,$f24,$f4
/*  f0460b0:	02e03025 */ 	or	$a2,$s7,$zero
/*  f0460b4:	e7b80010 */ 	swc1	$f24,0x10($sp)
/*  f0460b8:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f0460bc:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f0460c0:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f0460c4:	afb60024 */ 	sw	$s6,0x24($sp)
/*  f0460c8:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*  f0460cc:	0fc115d8 */ 	jal	func0f045760
/*  f0460d0:	afb70028 */ 	sw	$s7,0x28($sp)
/*  f0460d4:	50400004 */ 	beqzl	$v0,.L0f0460e8
/*  f0460d8:	c6060010 */ 	lwc1	$f6,0x10($s0)
/*  f0460dc:	100000a5 */ 	b	.L0f046374
/*  f0460e0:	a2000000 */ 	sb	$zero,0x0($s0)
/*  f0460e4:	c6060010 */ 	lwc1	$f6,0x10($s0)
.L0f0460e8:
/*  f0460e8:	c6280008 */ 	lwc1	$f8,0x8($s1)
/*  f0460ec:	c60a0018 */ 	lwc1	$f10,0x18($s0)
/*  f0460f0:	c6320010 */ 	lwc1	$f18,0x10($s1)
/*  f0460f4:	46083301 */ 	sub.s	$f12,$f6,$f8
/*  f0460f8:	0fc259d4 */ 	jal	atan2f
/*  f0460fc:	46125381 */ 	sub.s	$f14,$f10,$f18
/*  f046100:	4600a481 */ 	sub.s	$f18,$f20,$f0
/*  f046104:	c7b000f4 */ 	lwc1	$f16,0xf4($sp)
/*  f046108:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f04610c:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*  f046110:	c6260010 */ 	lwc1	$f6,0x10($s1)
/*  f046114:	460a8301 */ 	sub.s	$f12,$f16,$f10
/*  f046118:	e7b200c0 */ 	swc1	$f18,0xc0($sp)
/*  f04611c:	0fc259d4 */ 	jal	atan2f
/*  f046120:	46064381 */ 	sub.s	$f14,$f8,$f6
/*  f046124:	c7b000c0 */ 	lwc1	$f16,0xc0($sp)
/*  f046128:	4600a301 */ 	sub.s	$f12,$f20,$f0
/*  f04612c:	02402025 */ 	or	$a0,$s2,$zero
/*  f046130:	02802825 */ 	or	$a1,$s4,$zero
/*  f046134:	461a803c */ 	c.lt.s	$f16,$f26
/*  f046138:	46006086 */ 	mov.s	$f2,$f12
/*  f04613c:	00003025 */ 	or	$a2,$zero,$zero
/*  f046140:	02803825 */ 	or	$a3,$s4,$zero
/*  f046144:	45020003 */ 	bc1fl	.L0f046154
/*  f046148:	4610f03e */ 	c.le.s	$f30,$f16
/*  f04614c:	461c8400 */ 	add.s	$f16,$f16,$f28
/*  f046150:	4610f03e */ 	c.le.s	$f30,$f16
.L0f046154:
/*  f046154:	00000000 */ 	nop
/*  f046158:	45020003 */ 	bc1fl	.L0f046168
/*  f04615c:	461a803c */ 	c.lt.s	$f16,$f26
/*  f046160:	461c8401 */ 	sub.s	$f16,$f16,$f28
/*  f046164:	461a803c */ 	c.lt.s	$f16,$f26
.L0f046168:
/*  f046168:	00000000 */ 	nop
/*  f04616c:	45020003 */ 	bc1fl	.L0f04617c
/*  f046170:	461a603c */ 	c.lt.s	$f12,$f26
/*  f046174:	46008407 */ 	neg.s	$f16,$f16
/*  f046178:	461a603c */ 	c.lt.s	$f12,$f26
.L0f04617c:
/*  f04617c:	00000000 */ 	nop
/*  f046180:	45020003 */ 	bc1fl	.L0f046190
/*  f046184:	4602f03e */ 	c.le.s	$f30,$f2
/*  f046188:	461c6080 */ 	add.s	$f2,$f12,$f28
/*  f04618c:	4602f03e */ 	c.le.s	$f30,$f2
.L0f046190:
/*  f046190:	00000000 */ 	nop
/*  f046194:	45020003 */ 	bc1fl	.L0f0461a4
/*  f046198:	461a103c */ 	c.lt.s	$f2,$f26
/*  f04619c:	461c1081 */ 	sub.s	$f2,$f2,$f28
/*  f0461a0:	461a103c */ 	c.lt.s	$f2,$f26
.L0f0461a4:
/*  f0461a4:	00000000 */ 	nop
/*  f0461a8:	45020003 */ 	bc1fl	.L0f0461b8
/*  f0461ac:	4610103c */ 	c.lt.s	$f2,$f16
/*  f0461b0:	46001087 */ 	neg.s	$f2,$f2
/*  f0461b4:	4610103c */ 	c.lt.s	$f2,$f16
.L0f0461b8:
/*  f0461b8:	00000000 */ 	nop
/*  f0461bc:	45020061 */ 	bc1fl	.L0f046344
/*  f0461c0:	82190001 */ 	lb	$t9,0x1($s0)
/*  f0461c4:	e7b80010 */ 	swc1	$f24,0x10($sp)
/*  f0461c8:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f0461cc:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f0461d0:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f0461d4:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*  f0461d8:	afb60024 */ 	sw	$s6,0x24($sp)
/*  f0461dc:	0fc115d8 */ 	jal	func0f045760
/*  f0461e0:	afb70028 */ 	sw	$s7,0x28($sp)
/*  f0461e4:	50400057 */ 	beqzl	$v0,.L0f046344
/*  f0461e8:	82190001 */ 	lb	$t9,0x1($s0)
/*  f0461ec:	10000061 */ 	b	.L0f046374
/*  f0461f0:	a2000000 */ 	sb	$zero,0x0($s0)
.L0f0461f4:
/*  f0461f4:	c432927c */ 	lwc1	$f18,%lo(var7f1a927c)($at)
/*  f0461f8:	02803825 */ 	or	$a3,$s4,$zero
/*  f0461fc:	e7b80010 */ 	swc1	$f24,0x10($sp)
/*  f046200:	4612c582 */ 	mul.s	$f22,$f24,$f18
/*  f046204:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f046208:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f04620c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f046210:	afb60024 */ 	sw	$s6,0x24($sp)
/*  f046214:	afb70028 */ 	sw	$s7,0x28($sp)
/*  f046218:	0fc115d8 */ 	jal	func0f045760
/*  f04621c:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*  f046220:	50400004 */ 	beqzl	$v0,.L0f046234
/*  f046224:	c604001c */ 	lwc1	$f4,0x1c($s0)
/*  f046228:	10000052 */ 	b	.L0f046374
/*  f04622c:	a2000000 */ 	sb	$zero,0x0($s0)
/*  f046230:	c604001c */ 	lwc1	$f4,0x1c($s0)
.L0f046234:
/*  f046234:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f046238:	c6080024 */ 	lwc1	$f8,0x24($s0)
/*  f04623c:	c62a0010 */ 	lwc1	$f10,0x10($s1)
/*  f046240:	46062301 */ 	sub.s	$f12,$f4,$f6
/*  f046244:	0fc259d4 */ 	jal	atan2f
/*  f046248:	460a4381 */ 	sub.s	$f14,$f8,$f10
/*  f04624c:	4600a481 */ 	sub.s	$f18,$f20,$f0
/*  f046250:	c7b000f4 */ 	lwc1	$f16,0xf4($sp)
/*  f046254:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f046258:	c7a800fc */ 	lwc1	$f8,0xfc($sp)
/*  f04625c:	c6260010 */ 	lwc1	$f6,0x10($s1)
/*  f046260:	460a8301 */ 	sub.s	$f12,$f16,$f10
/*  f046264:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*  f046268:	0fc259d4 */ 	jal	atan2f
/*  f04626c:	46064381 */ 	sub.s	$f14,$f8,$f6
/*  f046270:	c7b000b0 */ 	lwc1	$f16,0xb0($sp)
/*  f046274:	4600a301 */ 	sub.s	$f12,$f20,$f0
/*  f046278:	02402025 */ 	or	$a0,$s2,$zero
/*  f04627c:	02802825 */ 	or	$a1,$s4,$zero
/*  f046280:	461a803c */ 	c.lt.s	$f16,$f26
/*  f046284:	46006086 */ 	mov.s	$f2,$f12
/*  f046288:	02e03025 */ 	or	$a2,$s7,$zero
/*  f04628c:	02803825 */ 	or	$a3,$s4,$zero
/*  f046290:	45020003 */ 	bc1fl	.L0f0462a0
/*  f046294:	4610f03e */ 	c.le.s	$f30,$f16
/*  f046298:	461c8400 */ 	add.s	$f16,$f16,$f28
/*  f04629c:	4610f03e */ 	c.le.s	$f30,$f16
.L0f0462a0:
/*  f0462a0:	00000000 */ 	nop
/*  f0462a4:	45020003 */ 	bc1fl	.L0f0462b4
/*  f0462a8:	461a803c */ 	c.lt.s	$f16,$f26
/*  f0462ac:	461c8401 */ 	sub.s	$f16,$f16,$f28
/*  f0462b0:	461a803c */ 	c.lt.s	$f16,$f26
.L0f0462b4:
/*  f0462b4:	00000000 */ 	nop
/*  f0462b8:	45020003 */ 	bc1fl	.L0f0462c8
/*  f0462bc:	461a603c */ 	c.lt.s	$f12,$f26
/*  f0462c0:	46008407 */ 	neg.s	$f16,$f16
/*  f0462c4:	461a603c */ 	c.lt.s	$f12,$f26
.L0f0462c8:
/*  f0462c8:	00000000 */ 	nop
/*  f0462cc:	45020003 */ 	bc1fl	.L0f0462dc
/*  f0462d0:	4602f03e */ 	c.le.s	$f30,$f2
/*  f0462d4:	461c6080 */ 	add.s	$f2,$f12,$f28
/*  f0462d8:	4602f03e */ 	c.le.s	$f30,$f2
.L0f0462dc:
/*  f0462dc:	00000000 */ 	nop
/*  f0462e0:	45020003 */ 	bc1fl	.L0f0462f0
/*  f0462e4:	461a103c */ 	c.lt.s	$f2,$f26
/*  f0462e8:	461c1081 */ 	sub.s	$f2,$f2,$f28
/*  f0462ec:	461a103c */ 	c.lt.s	$f2,$f26
.L0f0462f0:
/*  f0462f0:	00000000 */ 	nop
/*  f0462f4:	45020003 */ 	bc1fl	.L0f046304
/*  f0462f8:	4610103c */ 	c.lt.s	$f2,$f16
/*  f0462fc:	46001087 */ 	neg.s	$f2,$f2
/*  f046300:	4610103c */ 	c.lt.s	$f2,$f16
.L0f046304:
/*  f046304:	00000000 */ 	nop
/*  f046308:	4502000e */ 	bc1fl	.L0f046344
/*  f04630c:	82190001 */ 	lb	$t9,0x1($s0)
/*  f046310:	e7b80010 */ 	swc1	$f24,0x10($sp)
/*  f046314:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f046318:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f04631c:	afb0001c */ 	sw	$s0,0x1c($sp)
/*  f046320:	e7b60020 */ 	swc1	$f22,0x20($sp)
/*  f046324:	afb60024 */ 	sw	$s6,0x24($sp)
/*  f046328:	0fc115d8 */ 	jal	func0f045760
/*  f04632c:	afb70028 */ 	sw	$s7,0x28($sp)
/*  f046330:	50400004 */ 	beqzl	$v0,.L0f046344
/*  f046334:	82190001 */ 	lb	$t9,0x1($s0)
/*  f046338:	1000000e */ 	b	.L0f046374
/*  f04633c:	a2000000 */ 	sb	$zero,0x0($s0)
/*  f046340:	82190001 */ 	lb	$t9,0x1($s0)
.L0f046344:
/*  f046344:	27290001 */ 	addiu	$t1,$t9,0x1
/*  f046348:	a2090001 */ 	sb	$t1,0x1($s0)
/*  f04634c:	820a0001 */ 	lb	$t2,0x1($s0)
/*  f046350:	29410006 */ 	slti	$at,$t2,0x6
/*  f046354:	54200004 */ 	bnezl	$at,.L0f046368
/*  f046358:	8fab00f0 */ 	lw	$t3,0xf0($sp)
/*  f04635c:	a2000003 */ 	sb	$zero,0x3($s0)
/*  f046360:	a2000000 */ 	sb	$zero,0x0($s0)
.L0f046364:
/*  f046364:	8fab00f0 */ 	lw	$t3,0xf0($sp)
.L0f046368:
/*  f046368:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f04636c:	1597fe2e */ 	bne	$t4,$s7,.L0f045c28
/*  f046370:	afac00f0 */ 	sw	$t4,0xf0($sp)
.L0f046374:
/*  f046374:	820d0003 */ 	lb	$t5,0x3($s0)
/*  f046378:	02402025 */ 	or	$a0,$s2,$zero
/*  f04637c:	55a00008 */ 	bnezl	$t5,.L0f0463a0
/*  f046380:	8e0e0028 */ 	lw	$t6,0x28($s0)
/*  f046384:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f046388:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04638c:	c604000c */ 	lwc1	$f4,0xc($s0)
/*  f046390:	e60a002c */ 	swc1	$f10,0x2c($s0)
/*  f046394:	e6120030 */ 	swc1	$f18,0x30($s0)
/*  f046398:	e6040034 */ 	swc1	$f4,0x34($s0)
/*  f04639c:	8e0e0028 */ 	lw	$t6,0x28($s0)
.L0f0463a0:
/*  f0463a0:	2401000a */ 	addiu	$at,$zero,0xa
/*  f0463a4:	01c1001a */ 	div	$zero,$t6,$at
/*  f0463a8:	00007810 */ 	mfhi	$t7
/*  f0463ac:	55e00039 */ 	bnezl	$t7,.L0f046494
/*  f0463b0:	82590007 */ 	lb	$t9,0x7($s2)
/*  f0463b4:	0fc1169c */ 	jal	chrOpenDoor
/*  f0463b8:	2605002c */ 	addiu	$a1,$s0,0x2c
/*  f0463bc:	10400011 */ 	beqz	$v0,.L0f046404
/*  f0463c0:	00408825 */ 	or	$s1,$v0,$zero
/*  f0463c4:	8e5802d4 */ 	lw	$t8,0x2d4($s2)
/*  f0463c8:	1700000e */ 	bnez	$t8,.L0f046404
/*  f0463cc:	00000000 */ 	nop
/*  f0463d0:	8e590014 */ 	lw	$t9,0x14($s2)
/*  f0463d4:	33290010 */ 	andi	$t1,$t9,0x10
/*  f0463d8:	1520000a */ 	bnez	$t1,.L0f046404
/*  f0463dc:	00000000 */ 	nop
/*  f0463e0:	0fc0b819 */ 	jal	func0f02e064
/*  f0463e4:	02402025 */ 	or	$a0,$s2,$zero
/*  f0463e8:	14400006 */ 	bnez	$v0,.L0f046404
/*  f0463ec:	02402025 */ 	or	$a0,$s2,$zero
/*  f0463f0:	0fc0b9b7 */ 	jal	chrStandChooseAnimation
/*  f0463f4:	3c054180 */ 	lui	$a1,0x4180
/*  f0463f8:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x8)
/*  f0463fc:	8d4a9fc8 */ 	lw	$t2,%lo(g_Vars+0x8)($t2)
/*  f046400:	ae4a00d8 */ 	sw	$t2,0xd8($s2)
.L0f046404:
/*  f046404:	52200006 */ 	beqzl	$s1,.L0f046420
/*  f046408:	8e4d02d4 */ 	lw	$t5,0x2d4($s2)
/*  f04640c:	8e4b0014 */ 	lw	$t3,0x14($s2)
/*  f046410:	316c0010 */ 	andi	$t4,$t3,0x10
/*  f046414:	5180001f */ 	beqzl	$t4,.L0f046494
/*  f046418:	82590007 */ 	lb	$t9,0x7($s2)
/*  f04641c:	8e4d02d4 */ 	lw	$t5,0x2d4($s2)
.L0f046420:
/*  f046420:	15a00015 */ 	bnez	$t5,.L0f046478
/*  f046424:	00000000 */ 	nop
/*  f046428:	0fc0b819 */ 	jal	func0f02e064
/*  f04642c:	02402025 */ 	or	$a0,$s2,$zero
/*  f046430:	10400011 */ 	beqz	$v0,.L0f046478
/*  f046434:	00000000 */ 	nop
/*  f046438:	9242032c */ 	lbu	$v0,0x32c($s2)
/*  f04643c:	24010003 */ 	addiu	$at,$zero,0x3
/*  f046440:	12e2000d */ 	beq	$s7,$v0,.L0f046478
/*  f046444:	00000000 */ 	nop
/*  f046448:	1041000b */ 	beq	$v0,$at,.L0f046478
/*  f04644c:	00000000 */ 	nop
/*  f046450:	824e0007 */ 	lb	$t6,0x7($s2)
/*  f046454:	2401000e */ 	addiu	$at,$zero,0xe
/*  f046458:	15c10005 */ 	bne	$t6,$at,.L0f046470
/*  f04645c:	00000000 */ 	nop
/*  f046460:	0fc0e21a */ 	jal	chrPatrolChooseAnimation
/*  f046464:	02402025 */ 	or	$a0,$s2,$zero
/*  f046468:	10000003 */ 	b	.L0f046478
/*  f04646c:	00000000 */ 	nop
.L0f046470:
/*  f046470:	0fc0dedc */ 	jal	chrGoPosChooseAnimation
/*  f046474:	02402025 */ 	or	$a0,$s2,$zero
.L0f046478:
/*  f046478:	56200006 */ 	bnezl	$s1,.L0f046494
/*  f04647c:	82590007 */ 	lb	$t9,0x7($s2)
/*  f046480:	8e4f0014 */ 	lw	$t7,0x14($s2)
/*  f046484:	2401ffef */ 	addiu	$at,$zero,-17
/*  f046488:	01e1c024 */ 	and	$t8,$t7,$at
/*  f04648c:	ae580014 */ 	sw	$t8,0x14($s2)
/*  f046490:	82590007 */ 	lb	$t9,0x7($s2)
.L0f046494:
/*  f046494:	2401000e */ 	addiu	$at,$zero,0xe
/*  f046498:	2605002c */ 	addiu	$a1,$s0,0x2c
/*  f04649c:	17210007 */ 	bne	$t9,$at,.L0f0464bc
/*  f0464a0:	02402025 */ 	or	$a0,$s2,$zero
/*  f0464a4:	02402025 */ 	or	$a0,$s2,$zero
/*  f0464a8:	00003025 */ 	or	$a2,$zero,$zero
/*  f0464ac:	0fc10fcb */ 	jal	func0f043f2c
/*  f0464b0:	2647007c */ 	addiu	$a3,$s2,0x7c
/*  f0464b4:	10000054 */ 	b	.L0f046608
/*  f0464b8:	8fbf0084 */ 	lw	$ra,0x84($sp)
.L0f0464bc:
/*  f0464bc:	c64600ac */ 	lwc1	$f6,0xac($s2)
/*  f0464c0:	00004825 */ 	or	$t1,$zero,$zero
/*  f0464c4:	264700ac */ 	addiu	$a3,$s2,0xac
/*  f0464c8:	4606d032 */ 	c.eq.s	$f26,$f6
/*  f0464cc:	00000000 */ 	nop
/*  f0464d0:	45030003 */ 	bc1tl	.L0f0464e0
/*  f0464d4:	924d032e */ 	lbu	$t5,0x32e($s2)
/*  f0464d8:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f0464dc:	924d032e */ 	lbu	$t5,0x32e($s2)
.L0f0464e0:
/*  f0464e0:	00095880 */ 	sll	$t3,$t1,0x2
/*  f0464e4:	316c0004 */ 	andi	$t4,$t3,0x4
/*  f0464e8:	31aefffb */ 	andi	$t6,$t5,0xfffb
/*  f0464ec:	018e7825 */ 	or	$t7,$t4,$t6
/*  f0464f0:	a24f032e */ 	sb	$t7,0x32e($s2)
/*  f0464f4:	0fc10fcb */ 	jal	func0f043f2c
/*  f0464f8:	92460065 */ 	lbu	$a2,0x65($s2)
/*  f0464fc:	8e5802d4 */ 	lw	$t8,0x2d4($s2)
/*  f046500:	57000041 */ 	bnezl	$t8,.L0f046608
/*  f046504:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f046508:	0fc0b819 */ 	jal	func0f02e064
/*  f04650c:	02402025 */ 	or	$a0,$s2,$zero
/*  f046510:	5440003d */ 	bnezl	$v0,.L0f046608
/*  f046514:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f046518:	92420065 */ 	lbu	$v0,0x65($s2)
/*  f04651c:	24010002 */ 	addiu	$at,$zero,0x2
/*  f046520:	30590003 */ 	andi	$t9,$v0,0x3
/*  f046524:	17210025 */ 	bne	$t9,$at,.L0f0465bc
/*  f046528:	03201025 */ 	or	$v0,$t9,$zero
/*  f04652c:	c64800ac */ 	lwc1	$f8,0xac($s2)
/*  f046530:	4608d032 */ 	c.eq.s	$f26,$f8
/*  f046534:	00000000 */ 	nop
/*  f046538:	4503000c */ 	bc1tl	.L0f04656c
/*  f04653c:	8e4d032c */ 	lw	$t5,0x32c($s2)
/*  f046540:	8e49032c */ 	lw	$t1,0x32c($s2)
/*  f046544:	3c053e80 */ 	lui	$a1,0x3e80
/*  f046548:	3c064100 */ 	lui	$a2,0x4100
/*  f04654c:	00095d40 */ 	sll	$t3,$t1,0x15
/*  f046550:	0562002d */ 	bltzl	$t3,.L0f046608
/*  f046554:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f046558:	0c0077ac */ 	jal	modelSetAnimSpeed
/*  f04655c:	8e440020 */ 	lw	$a0,0x20($s2)
/*  f046560:	10000029 */ 	b	.L0f046608
/*  f046564:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f046568:	8e4d032c */ 	lw	$t5,0x32c($s2)
.L0f04656c:
/*  f04656c:	000d7540 */ 	sll	$t6,$t5,0x15
/*  f046570:	05c30025 */ 	bgezl	$t6,.L0f046608
/*  f046574:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f046578:	8e4f0018 */ 	lw	$t7,0x18($s2)
/*  f04657c:	3c053f00 */ 	lui	$a1,0x3f00
/*  f046580:	3c064200 */ 	lui	$a2,0x4200
/*  f046584:	000fc300 */ 	sll	$t8,$t7,0xc
/*  f046588:	07010008 */ 	bgez	$t8,.L0f0465ac
/*  f04658c:	00000000 */ 	nop
/*  f046590:	3c053f26 */ 	lui	$a1,0x3f26
/*  f046594:	34a56666 */ 	ori	$a1,$a1,0x6666
/*  f046598:	8e440020 */ 	lw	$a0,0x20($s2)
/*  f04659c:	0c0077ac */ 	jal	modelSetAnimSpeed
/*  f0465a0:	3c064200 */ 	lui	$a2,0x4200
/*  f0465a4:	10000018 */ 	b	.L0f046608
/*  f0465a8:	8fbf0084 */ 	lw	$ra,0x84($sp)
.L0f0465ac:
/*  f0465ac:	0c0077ac */ 	jal	modelSetAnimSpeed
/*  f0465b0:	8e440020 */ 	lw	$a0,0x20($s2)
/*  f0465b4:	10000014 */ 	b	.L0f046608
/*  f0465b8:	8fbf0084 */ 	lw	$ra,0x84($sp)
.L0f0465bc:
/*  f0465bc:	56e20012 */ 	bnel	$s7,$v0,.L0f046608
/*  f0465c0:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f0465c4:	c64a00ac */ 	lwc1	$f10,0xac($s2)
/*  f0465c8:	3c053f00 */ 	lui	$a1,0x3f00
/*  f0465cc:	460ad032 */ 	c.eq.s	$f26,$f10
/*  f0465d0:	00000000 */ 	nop
/*  f0465d4:	45030009 */ 	bc1tl	.L0f0465fc
/*  f0465d8:	4406d000 */ 	mfc1	$a2,$f26
/*  f0465dc:	3c053ecc */ 	lui	$a1,0x3ecc
/*  f0465e0:	4406d000 */ 	mfc1	$a2,$f26
/*  f0465e4:	34a5cccd */ 	ori	$a1,$a1,0xcccd
/*  f0465e8:	0c0077ac */ 	jal	modelSetAnimSpeed
/*  f0465ec:	8e440020 */ 	lw	$a0,0x20($s2)
/*  f0465f0:	10000005 */ 	b	.L0f046608
/*  f0465f4:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f0465f8:	4406d000 */ 	mfc1	$a2,$f26
.L0f0465fc:
/*  f0465fc:	0c0077ac */ 	jal	modelSetAnimSpeed
/*  f046600:	8e440020 */ 	lw	$a0,0x20($s2)
/*  f046604:	8fbf0084 */ 	lw	$ra,0x84($sp)
.L0f046608:
/*  f046608:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*  f04660c:	d7b60038 */ 	ldc1	$f22,0x38($sp)
/*  f046610:	d7b80040 */ 	ldc1	$f24,0x40($sp)
/*  f046614:	d7ba0048 */ 	ldc1	$f26,0x48($sp)
/*  f046618:	d7bc0050 */ 	ldc1	$f28,0x50($sp)
/*  f04661c:	d7be0058 */ 	ldc1	$f30,0x58($sp)
/*  f046620:	8fb00064 */ 	lw	$s0,0x64($sp)
/*  f046624:	8fb10068 */ 	lw	$s1,0x68($sp)
/*  f046628:	8fb2006c */ 	lw	$s2,0x6c($sp)
/*  f04662c:	8fb30070 */ 	lw	$s3,0x70($sp)
/*  f046630:	8fb40074 */ 	lw	$s4,0x74($sp)
/*  f046634:	8fb50078 */ 	lw	$s5,0x78($sp)
/*  f046638:	8fb6007c */ 	lw	$s6,0x7c($sp)
/*  f04663c:	8fb70080 */ 	lw	$s7,0x80($sp)
/*  f046640:	03e00008 */ 	jr	$ra
/*  f046644:	27bd0110 */ 	addiu	$sp,$sp,0x110
);

GLOBAL_ASM(
glabel goPosUpdateLiftAction
/*  f046648:	27bdff60 */ 	addiu	$sp,$sp,-160
/*  f04664c:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f046650:	00808025 */ 	or	$s0,$a0,$zero
/*  f046654:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f046658:	afa500a4 */ 	sw	$a1,0xa4($sp)
/*  f04665c:	afa600a8 */ 	sw	$a2,0xa8($sp)
/*  f046660:	afa700ac */ 	sw	$a3,0xac($sp)
/*  f046664:	87a400b2 */ 	lh	$a0,0xb2($sp)
/*  f046668:	afa00044 */ 	sw	$zero,0x44($sp)
/*  f04666c:	0fc1c396 */ 	jal	liftFindByPad
/*  f046670:	afa0009c */ 	sw	$zero,0x9c($sp)
/*  f046674:	8fa30044 */ 	lw	$v1,0x44($sp)
/*  f046678:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f04667c:	14400003 */ 	bnez	$v0,.L0f04668c
/*  f046680:	00402825 */ 	or	$a1,$v0,$zero
/*  f046684:	100000e5 */ 	b	.L0f046a1c
/*  f046688:	00001025 */ 	or	$v0,$zero,$zero
.L0f04668c:
/*  f04668c:	8ca40004 */ 	lw	$a0,0x4($a1)
/*  f046690:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f046694:	afa30044 */ 	sw	$v1,0x44($sp)
/*  f046698:	0fc1c3ab */ 	jal	liftGetY
/*  f04669c:	afa40038 */ 	sw	$a0,0x38($sp)
/*  f0466a0:	8fae00b4 */ 	lw	$t6,0xb4($sp)
/*  f0466a4:	8fa30044 */ 	lw	$v1,0x44($sp)
/*  f0466a8:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f0466ac:	8fa90038 */ 	lw	$t1,0x38($sp)
/*  f0466b0:	05c0000b */ 	bltz	$t6,.L0f0466e0
/*  f0466b4:	46000086 */ 	mov.s	$f2,$f0
/*  f0466b8:	01c02025 */ 	or	$a0,$t6,$zero
/*  f0466bc:	240500c2 */ 	addiu	$a1,$zero,0xc2
/*  f0466c0:	27a60048 */ 	addiu	$a2,$sp,0x48
/*  f0466c4:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f0466c8:	0fc456ac */ 	jal	padUnpack
/*  f0466cc:	e7a2003c */ 	swc1	$f2,0x3c($sp)
/*  f0466d0:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f0466d4:	8fa90038 */ 	lw	$t1,0x38($sp)
/*  f0466d8:	c7a2003c */ 	lwc1	$f2,0x3c($sp)
/*  f0466dc:	8fa30094 */ 	lw	$v1,0x94($sp)
.L0f0466e0:
/*  f0466e0:	8fa200a4 */ 	lw	$v0,0xa4($sp)
/*  f0466e4:	30780800 */ 	andi	$t8,$v1,0x800
/*  f0466e8:	304f0400 */ 	andi	$t7,$v0,0x400
/*  f0466ec:	11e00061 */ 	beqz	$t7,.L0f046874
/*  f0466f0:	304b0800 */ 	andi	$t3,$v0,0x800
/*  f0466f4:	1300005a */ 	beqz	$t8,.L0f046860
/*  f0466f8:	8faa00ac */ 	lw	$t2,0xac($sp)
/*  f0466fc:	8fa400ac */ 	lw	$a0,0xac($sp)
/*  f046700:	3c0a800a */ 	lui	$t2,%hi(g_Vars+0x318)
/*  f046704:	54800005 */ 	bnezl	$a0,.L0f04671c
/*  f046708:	3c014220 */ 	lui	$at,0x4220
/*  f04670c:	9219032c */ 	lbu	$t9,0x32c($s0)
/*  f046710:	24010001 */ 	addiu	$at,$zero,0x1
/*  f046714:	17210028 */ 	bne	$t9,$at,.L0f0467b8
/*  f046718:	3c014220 */ 	lui	$at,0x4220
.L0f04671c:
/*  f04671c:	44812000 */ 	mtc1	$at,$f4
/*  f046720:	c60000b4 */ 	lwc1	$f0,0xb4($s0)
/*  f046724:	00004025 */ 	or	$t0,$zero,$zero
/*  f046728:	46040180 */ 	add.s	$f6,$f0,$f4
/*  f04672c:	4606103e */ 	c.le.s	$f2,$f6
/*  f046730:	00000000 */ 	nop
/*  f046734:	45000002 */ 	bc1f	.L0f046740
/*  f046738:	00000000 */ 	nop
/*  f04673c:	24080001 */ 	addiu	$t0,$zero,0x1
.L0f046740:
/*  f046740:	8d4aa2d8 */ 	lw	$t2,%lo(g_Vars+0x318)($t2)
/*  f046744:	1540000b */ 	bnez	$t2,.L0f046774
/*  f046748:	00000000 */ 	nop
/*  f04674c:	11000009 */ 	beqz	$t0,.L0f046774
/*  f046750:	3c0142c8 */ 	lui	$at,0x42c8
/*  f046754:	44814000 */ 	mtc1	$at,$f8
/*  f046758:	00004025 */ 	or	$t0,$zero,$zero
/*  f04675c:	46080281 */ 	sub.s	$f10,$f0,$f8
/*  f046760:	4602503c */ 	c.lt.s	$f10,$f2
/*  f046764:	00000000 */ 	nop
/*  f046768:	45000002 */ 	bc1f	.L0f046774
/*  f04676c:	00000000 */ 	nop
/*  f046770:	24080001 */ 	addiu	$t0,$zero,0x1
.L0f046774:
/*  f046774:	11000010 */ 	beqz	$t0,.L0f0467b8
/*  f046778:	00000000 */ 	nop
/*  f04677c:	812b0085 */ 	lb	$t3,0x85($t1)
/*  f046780:	3c013f00 */ 	lui	$at,0x3f00
/*  f046784:	000b6080 */ 	sll	$t4,$t3,0x2
/*  f046788:	012c6821 */ 	addu	$t5,$t1,$t4
/*  f04678c:	8da20064 */ 	lw	$v0,0x64($t5)
/*  f046790:	10400009 */ 	beqz	$v0,.L0f0467b8
/*  f046794:	00000000 */ 	nop
/*  f046798:	c450007c */ 	lwc1	$f16,0x7c($v0)
/*  f04679c:	44819000 */ 	mtc1	$at,$f18
/*  f0467a0:	00000000 */ 	nop
/*  f0467a4:	4612803c */ 	c.lt.s	$f16,$f18
/*  f0467a8:	00000000 */ 	nop
/*  f0467ac:	45000002 */ 	bc1f	.L0f0467b8
/*  f0467b0:	00000000 */ 	nop
/*  f0467b4:	00004025 */ 	or	$t0,$zero,$zero
.L0f0467b8:
/*  f0467b8:	55000016 */ 	bnezl	$t0,.L0f046814
/*  f0467bc:	a200032c */ 	sb	$zero,0x32c($s0)
/*  f0467c0:	50800096 */ 	beqzl	$a0,.L0f046a1c
/*  f0467c4:	01001025 */ 	or	$v0,$t0,$zero
/*  f0467c8:	920e032c */ 	lbu	$t6,0x32c($s0)
/*  f0467cc:	24010001 */ 	addiu	$at,$zero,0x1
/*  f0467d0:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f0467d4:	11c10090 */ 	beq	$t6,$at,.L0f046a18
/*  f0467d8:	02002025 */ 	or	$a0,$s0,$zero
/*  f0467dc:	a20f032c */ 	sb	$t7,0x32c($s0)
/*  f0467e0:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f0467e4:	0fc0b9b7 */ 	jal	chrStandChooseAnimation
/*  f0467e8:	3c054180 */ 	lui	$a1,0x4180
/*  f0467ec:	8fb800b4 */ 	lw	$t8,0xb4($sp)
/*  f0467f0:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f0467f4:	02002025 */ 	or	$a0,$s0,$zero
/*  f0467f8:	07000087 */ 	bltz	$t8,.L0f046a18
/*  f0467fc:	27a50048 */ 	addiu	$a1,$sp,0x48
/*  f046800:	0fc1169c */ 	jal	chrOpenDoor
/*  f046804:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f046808:	10000083 */ 	b	.L0f046a18
/*  f04680c:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f046810:	a200032c */ 	sb	$zero,0x32c($s0)
.L0f046814:
/*  f046814:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f046818:	0fc0b819 */ 	jal	func0f02e064
/*  f04681c:	02002025 */ 	or	$a0,$s0,$zero
/*  f046820:	1040007d */ 	beqz	$v0,.L0f046a18
/*  f046824:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f046828:	82190007 */ 	lb	$t9,0x7($s0)
/*  f04682c:	2401000e */ 	addiu	$at,$zero,0xe
/*  f046830:	02002025 */ 	or	$a0,$s0,$zero
/*  f046834:	17210006 */ 	bne	$t9,$at,.L0f046850
/*  f046838:	00000000 */ 	nop
/*  f04683c:	02002025 */ 	or	$a0,$s0,$zero
/*  f046840:	0fc0e21a */ 	jal	chrPatrolChooseAnimation
/*  f046844:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f046848:	10000073 */ 	b	.L0f046a18
/*  f04684c:	8fa8009c */ 	lw	$t0,0x9c($sp)
.L0f046850:
/*  f046850:	0fc0dedc */ 	jal	chrGoPosChooseAnimation
/*  f046854:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f046858:	1000006f */ 	b	.L0f046a18
/*  f04685c:	8fa8009c */ 	lw	$t0,0x9c($sp)
.L0f046860:
/*  f046860:	5140006e */ 	beqzl	$t2,.L0f046a1c
/*  f046864:	01001025 */ 	or	$v0,$t0,$zero
/*  f046868:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f04686c:	1000006a */ 	b	.L0f046a18
/*  f046870:	a200032c */ 	sb	$zero,0x32c($s0)
.L0f046874:
/*  f046874:	11600068 */ 	beqz	$t3,.L0f046a18
/*  f046878:	306c0400 */ 	andi	$t4,$v1,0x400
/*  f04687c:	11800060 */ 	beqz	$t4,.L0f046a00
/*  f046880:	8fad00a8 */ 	lw	$t5,0xa8($sp)
/*  f046884:	15a00004 */ 	bnez	$t5,.L0f046898
/*  f046888:	27a5002c */ 	addiu	$a1,$sp,0x2c
/*  f04688c:	920e032c */ 	lbu	$t6,0x32c($s0)
/*  f046890:	24010003 */ 	addiu	$at,$zero,0x3
/*  f046894:	15c10036 */ 	bne	$t6,$at,.L0f046970
.L0f046898:
/*  f046898:	3c0f8007 */ 	lui	$t7,%hi(var8006843c)
/*  f04689c:	25ef843c */ 	addiu	$t7,$t7,%lo(var8006843c)
/*  f0468a0:	8de10000 */ 	lw	$at,0x0($t7)
/*  f0468a4:	27a40048 */ 	addiu	$a0,$sp,0x48
/*  f0468a8:	00003025 */ 	or	$a2,$zero,$zero
/*  f0468ac:	aca10000 */ 	sw	$at,0x0($a1)
/*  f0468b0:	8faa0090 */ 	lw	$t2,0x90($sp)
/*  f0468b4:	e7a2003c */ 	swc1	$f2,0x3c($sp)
/*  f0468b8:	00003825 */ 	or	$a3,$zero,$zero
/*  f0468bc:	0c00a8db */ 	jal	cd0002a36c
/*  f0468c0:	a7aa002c */ 	sh	$t2,0x2c($sp)
/*  f0468c4:	3c0141f0 */ 	lui	$at,0x41f0
/*  f0468c8:	44812000 */ 	mtc1	$at,$f4
/*  f0468cc:	c7a2003c */ 	lwc1	$f2,0x3c($sp)
/*  f0468d0:	8fa90038 */ 	lw	$t1,0x38($sp)
/*  f0468d4:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f0468d8:	00001025 */ 	or	$v0,$zero,$zero
/*  f0468dc:	3c0b800a */ 	lui	$t3,%hi(g_Vars+0x318)
/*  f0468e0:	4602303e */ 	c.le.s	$f6,$f2
/*  f0468e4:	00000000 */ 	nop
/*  f0468e8:	45000002 */ 	bc1f	.L0f0468f4
/*  f0468ec:	00000000 */ 	nop
/*  f0468f0:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f0468f4:
/*  f0468f4:	8d6ba2d8 */ 	lw	$t3,%lo(g_Vars+0x318)($t3)
/*  f0468f8:	00404025 */ 	or	$t0,$v0,$zero
/*  f0468fc:	1560000b */ 	bnez	$t3,.L0f04692c
/*  f046900:	00000000 */ 	nop
/*  f046904:	10400009 */ 	beqz	$v0,.L0f04692c
/*  f046908:	3c0142c8 */ 	lui	$at,0x42c8
/*  f04690c:	44814000 */ 	mtc1	$at,$f8
/*  f046910:	00004025 */ 	or	$t0,$zero,$zero
/*  f046914:	46080280 */ 	add.s	$f10,$f0,$f8
/*  f046918:	460a103c */ 	c.lt.s	$f2,$f10
/*  f04691c:	00000000 */ 	nop
/*  f046920:	45000002 */ 	bc1f	.L0f04692c
/*  f046924:	00000000 */ 	nop
/*  f046928:	24080001 */ 	addiu	$t0,$zero,0x1
.L0f04692c:
/*  f04692c:	11000010 */ 	beqz	$t0,.L0f046970
/*  f046930:	00000000 */ 	nop
/*  f046934:	812c0085 */ 	lb	$t4,0x85($t1)
/*  f046938:	3c013f00 */ 	lui	$at,0x3f00
/*  f04693c:	000c6880 */ 	sll	$t5,$t4,0x2
/*  f046940:	012d7021 */ 	addu	$t6,$t1,$t5
/*  f046944:	8dc20064 */ 	lw	$v0,0x64($t6)
/*  f046948:	10400009 */ 	beqz	$v0,.L0f046970
/*  f04694c:	00000000 */ 	nop
/*  f046950:	c450007c */ 	lwc1	$f16,0x7c($v0)
/*  f046954:	44819000 */ 	mtc1	$at,$f18
/*  f046958:	00000000 */ 	nop
/*  f04695c:	4612803c */ 	c.lt.s	$f16,$f18
/*  f046960:	00000000 */ 	nop
/*  f046964:	45000002 */ 	bc1f	.L0f046970
/*  f046968:	00000000 */ 	nop
/*  f04696c:	00004025 */ 	or	$t0,$zero,$zero
.L0f046970:
/*  f046970:	1500000f */ 	bnez	$t0,.L0f0469b0
/*  f046974:	240a0002 */ 	addiu	$t2,$zero,0x2
/*  f046978:	8fb800a8 */ 	lw	$t8,0xa8($sp)
/*  f04697c:	53000027 */ 	beqzl	$t8,.L0f046a1c
/*  f046980:	01001025 */ 	or	$v0,$t0,$zero
/*  f046984:	920f032c */ 	lbu	$t7,0x32c($s0)
/*  f046988:	24010003 */ 	addiu	$at,$zero,0x3
/*  f04698c:	24190003 */ 	addiu	$t9,$zero,0x3
/*  f046990:	11e10021 */ 	beq	$t7,$at,.L0f046a18
/*  f046994:	02002025 */ 	or	$a0,$s0,$zero
/*  f046998:	a219032c */ 	sb	$t9,0x32c($s0)
/*  f04699c:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f0469a0:	0fc0b9b7 */ 	jal	chrStandChooseAnimation
/*  f0469a4:	3c054180 */ 	lui	$a1,0x4180
/*  f0469a8:	1000001b */ 	b	.L0f046a18
/*  f0469ac:	8fa8009c */ 	lw	$t0,0x9c($sp)
.L0f0469b0:
/*  f0469b0:	a20a032c */ 	sb	$t2,0x32c($s0)
/*  f0469b4:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f0469b8:	0fc0b819 */ 	jal	func0f02e064
/*  f0469bc:	02002025 */ 	or	$a0,$s0,$zero
/*  f0469c0:	10400015 */ 	beqz	$v0,.L0f046a18
/*  f0469c4:	8fa8009c */ 	lw	$t0,0x9c($sp)
/*  f0469c8:	820b0007 */ 	lb	$t3,0x7($s0)
/*  f0469cc:	2401000e */ 	addiu	$at,$zero,0xe
/*  f0469d0:	02002025 */ 	or	$a0,$s0,$zero
/*  f0469d4:	15610006 */ 	bne	$t3,$at,.L0f0469f0
/*  f0469d8:	00000000 */ 	nop
/*  f0469dc:	02002025 */ 	or	$a0,$s0,$zero
/*  f0469e0:	0fc0e21a */ 	jal	chrPatrolChooseAnimation
/*  f0469e4:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f0469e8:	1000000b */ 	b	.L0f046a18
/*  f0469ec:	8fa8009c */ 	lw	$t0,0x9c($sp)
.L0f0469f0:
/*  f0469f0:	0fc0dedc */ 	jal	chrGoPosChooseAnimation
/*  f0469f4:	afa8009c */ 	sw	$t0,0x9c($sp)
/*  f0469f8:	10000007 */ 	b	.L0f046a18
/*  f0469fc:	8fa8009c */ 	lw	$t0,0x9c($sp)
.L0f046a00:
/*  f046a00:	8fac00a8 */ 	lw	$t4,0xa8($sp)
/*  f046a04:	240d0002 */ 	addiu	$t5,$zero,0x2
/*  f046a08:	51800004 */ 	beqzl	$t4,.L0f046a1c
/*  f046a0c:	01001025 */ 	or	$v0,$t0,$zero
/*  f046a10:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f046a14:	a20d032c */ 	sb	$t5,0x32c($s0)
.L0f046a18:
/*  f046a18:	01001025 */ 	or	$v0,$t0,$zero
.L0f046a1c:
/*  f046a1c:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f046a20:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f046a24:	27bd00a0 */ 	addiu	$sp,$sp,0xa0
/*  f046a28:	03e00008 */ 	jr	$ra
/*  f046a2c:	00000000 */ 	nop
);

u32 var8006843c = 0x0000ffff;

// Mismatch: Goal loads arrivingatlift into a0 then later copies s0 (chr) to a0.
// The below loads arrivingatlift into v1 and copies s0 to a0 earlier.
//bool goPosUpdateLiftAction(struct chrdata *chr, u32 curpadflags, bool arg2, bool arrivingatlift, s16 curpadnum, s32 nextpadnum)
//{
//	bool advance = false;
//	struct pad nextpad;
//	u32 nextpadflags = 0;
//	f32 nextground;
//	f32 lifty;
//	struct liftobj *lift;
//	struct prop *liftprop = liftFindByPad(curpadnum);
//	u32 stack;
//
//	if (!liftprop) {
//		return false;
//	}
//
//	lift = (struct liftobj *) liftprop->obj;
//
//	lifty = liftGetY(lift);
//
//	if (nextpadnum >= 0) {
//		padUnpack(nextpadnum, PADFIELD_POS | PADFIELD_ROOM | PADFIELD_FLAGS, &nextpad);
//		nextpadflags = nextpad.flags;
//	}
//
//	if (curpadflags & PADFLAG_AIWAITLIFT) {
//		if (nextpadflags & PADFLAG_AIONLIFT) {
//			if (arrivingatlift || chr->liftaction == LIFTACTION_WAITINGFORLIFT) {
//				// Begin entering lift if lift is under 40cm above this level
//				advance = (lifty <= chr->manground + 40);
//
//				// ...and (if solo mode) lift is over 1m under this level
//				// (this logic allows MP simulants to drop down onto lifts)
//				if (!g_Vars.normmplayerisrunning && advance) {
//					advance = (lifty > chr->manground - 100);
//				}
//
//				// ...and if the lift has a door, is at least halfway open
//				if (advance && lift->doors[lift->levelcur] && lift->doors[lift->levelcur]->frac < 0.5f) {
//					advance = false;
//				}
//			}
//
//			if (!advance) {
//				if (arrivingatlift && chr->liftaction != LIFTACTION_WAITINGFORLIFT) {
//					// Just arrived at lift
//					chr->liftaction = LIFTACTION_WAITINGFORLIFT;
//
//					chrStandChooseAnimation(chr, 16);
//
//					if (nextpadnum >= 0) {
//						// Call the lift
//						chrOpenDoor(chr, &nextpad.pos);
//					}
//				}
//			} else {
//				// Enter lift
//				chr->liftaction = LIFTACTION_NOTUSINGLIFT;
//
//				if (func0f02e064(chr)) {
//					if (chr->actiontype == ACT_PATROL) {
//						chrPatrolChooseAnimation(chr);
//					} else {
//						chrGoPosChooseAnimation(chr);
//					}
//				}
//			}
//		} else {
//			// On a wait lift pad, but the next pad in the route is not on the
//			// lift, so the chr is running past the lift without using it.
//			if (arrivingatlift) {
//				advance = true;
//				chr->liftaction = LIFTACTION_NOTUSINGLIFT;
//			}
//		}
//	} else if (curpadflags & PADFLAG_AIONLIFT) {
//		if (nextpadflags & PADFLAG_AIWAITLIFT) {
//			// Waiting for door to close or lift to arrive at destination
//			if (arg2 || chr->liftaction == LIFTACTION_WAITINGONLIFT) {
//				// Continue waiting
//				s16 rooms[] = {0, -1};
//				u32 stack2;
//
//				rooms[0] = nextpad.room;
//
//				nextground = cd0002a36c(&nextpad.pos, rooms, NULL, NULL);
//
//				// Begin exiting lift if lift is 30cm under destination or higher
//				advance = (lifty >= nextground - 30);
//
//				// ...and (if solo) lift is under 1m above destination
//				if (!g_Vars.normmplayerisrunning && advance) {
//					advance = (lifty < nextground + 100);
//				}
//
//				// ...and if the lift has a door, is at least halfway open
//				if (advance && lift->doors[lift->levelcur] && lift->doors[lift->levelcur]->frac < 0.5f) {
//					advance = false;
//				}
//			}
//
//			if (!advance) {
//				if (arg2 && chr->liftaction != LIFTACTION_WAITINGONLIFT) {
//					// Just arrived inside lift
//					chr->liftaction = LIFTACTION_WAITINGONLIFT;
//					chrStandChooseAnimation(chr, 16);
//				}
//			} else {
//				// Start disembarking
//				chr->liftaction = LIFTACTION_ONLIFT;
//
//				if (func0f02e064(chr)) {
//					if (chr->actiontype == ACT_PATROL) {
//						chrPatrolChooseAnimation(chr);
//					} else {
//						chrGoPosChooseAnimation(chr);
//					}
//				}
//			}
//		} else {
//			// Not our stop? Not sure why advance is true here. I guess the chr
//			// can't go anywhere anyway because the next pad is above or below
//			// them.
//			if (arg2) {
//				advance = true;
//				chr->liftaction = LIFTACTION_ONLIFT;
//			}
//		}
//	}
//
//	return advance;
//}

s32 chrIsUsingLift(struct chrdata *chr)
{
	return (chr->actiontype == ACT_GOPOS || chr->actiontype == ACT_PATROL) && chr->liftaction > 0;
}

s16 chrGoPosGetNextPadNum(struct chrdata *chr)
{
	if (chr->act_gopos.waypoints[chr->act_gopos.curindex + 1]) {
		return chr->act_gopos.waypoints[chr->act_gopos.curindex + 1]->padnum;
	}

	return -1;
}

void chrTickGoPos(struct chrdata *chr)
{
	struct waypoint *waypoint;
	struct coord pos;
	s16 rooms[8];
	struct prop *prop = chr->prop;
	bool enteringmagic = false;
	struct pad pad;
	bool sp240 = true;
	struct coord curwppos;
	s16 curwprooms[8];
	u32 curwpflags;

	chr->act_gopos.flags &= ~(GOPOSFLAG_DUCK | GOPOSFLAG_80);

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrGoPosChooseAnimation(chr);

		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	chr->act_gopos.waydata.age++;

	// If stuck for 1 second
	if (chr->lastmoveok60 < g_Vars.lvframe60 - PALDOWN(60)) {
#if VERSION >= VERSION_NTSC_1_0
		if (chr->goposforce >= 0) {
			// Try and warp the chr past whatever obstacle is blocking them?
			struct coord sp196 = {0, 0, 0};

			chrDamageByMisc(chr, 1, &sp196, NULL, NULL);

			chr->lastmoveok60 = g_Vars.lvframe60;
			return;
		}
#endif

		// Goposforce was not set - restart the action to try and find a new route
		chrGoToPos(chr, &chr->act_gopos.endpos, chr->act_gopos.endrooms, chr->act_gopos.flags);
	}

	chrGoPosConsiderRestart(chr);
	chrGoPosGetCurWaypointInfoWithFlags(chr, &curwppos, curwprooms, &curwpflags);

	// If magic mode ended over 3 seconds ago, not multiplayer, not in view of
	// eyespy, pad is nothing special and not in lift, then enter the magic move
	// mode.
	if (chr->act_gopos.waydata.mode != WAYMODE_MAGIC
			&& chr->act_gopos.waydata.lastvisible60 + PALDOWN(180) < g_Vars.lvframe60
			&& g_Vars.normmplayerisrunning == false
			&& func0f036c08(chr, &curwppos, curwprooms) // related to eyespy
			&& (curwpflags & (PADFLAG_AIWAITLIFT | PADFLAG_AIONLIFT)) == 0
			&& chr->inlift == false) {
		enteringmagic = true;
		chrGoPosInitMagic(chr, &chr->act_gopos.waydata, &curwppos, &prop->pos);
	}

#if VERSION >= VERSION_NTSC_1_0
	if (var80062cbc >= 9
			&& (chr->hidden & CHRHFLAG_00400000)
			&& (chr->flags & CHRFLAG0_CAN_GO_TO_PLACES) == 0) {
		chrStop(chr);
		return;
	}
#else
	if (var80062cbc >= 10) {
		chrStop(chr);
		return;
	}
#endif

	// If goposforce is set then decrease it on each tick. If it's reached -1
	// then stop the chr. I guess goposforce is not only used to warp past
	// obstacles, but is also used as a run countdown timer.
#if VERSION >= VERSION_NTSC_1_0
	if (chr->goposforce >= 0) {
		chr->goposforce -= g_Vars.lvupdate240_60;

		if (chr->goposforce < 0) {
			chrStop(chr);
			return;
		}
	}
#endif

	// Check if chr needs to exit magic mode
	if (chr->act_gopos.waydata.mode == WAYMODE_MAGIC) {
		if ((!enteringmagic && ((prop->flags & (PROPFLAG_ONANYSCREENPREVTICK | PROPFLAG_ONANYSCREENTHISTICK | PROPFLAG_ONTHISSCREENTHISTICK)) || !func0f036c08(chr, &curwppos, curwprooms)))
				|| (curwpflags & (PADFLAG_AIWAITLIFT | PADFLAG_AIONLIFT))
				|| chr->inlift) {
			// Exiting magic mode
			chrGoPosInitExpensive(chr);
			chr->act_gopos.waydata.lastvisible60 = g_Vars.lvframe60;
			return;
		}

		chrGoPosTickMagic(chr, &chr->act_gopos.waydata, func0f0370a8(chr), &curwppos, curwprooms);
	} else {
		bool advance = false;
		bool sp188;
		bool sp184;
		f32 sp180;
		f32 sp176;
		f32 sp172;
		f32 sp168;
		bool candosomething;
		f32 sp160;
		f32 sp156;
		struct waypoint *next;
		struct pad pad2;

		waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex];

		if (waypoint) {
			padUnpack(waypoint->padnum, PADFIELD_FLAGS | PADFIELD_POS, &pad);

			// Both of these functions are calculating something with the coords
			// and are returning a boolean. There are no write operations.
			sp188 = posIsArrivingAtPos(&chr->prevpos, &prop->pos, &pad.pos, 30);
			sp184 = posIsArrivingLaterallyAtPos(&chr->prevpos, &prop->pos, &pad.pos, 30);

			if (pad.flags & PADFLAG_AIDUCK) {
				chr->act_gopos.flags |= GOPOSFLAG_DUCK;
			} else if (pad.flags & PADFLAG_10000) {
				chr->act_gopos.flags |= GOPOSFLAG_80;
			}

			if ((pad.flags & PADFLAG_AIWAITLIFT) || (pad.flags & PADFLAG_AIONLIFT)) {
				advance = goPosUpdateLiftAction(chr, pad.flags, sp184, sp188, waypoint->padnum, chrGoPosGetNextPadNum(chr));
			} else {
				if (sp188 || (sp184 && (chr->inlift || (pad.flags & PADFLAG_8000)))) {
					advance = true;
				}
			}
		} else {
			// No more waypoints - chr is finished
			if (posIsArrivingAtPos(&chr->prevpos, &prop->pos, &chr->act_gopos.endpos, 30) ||
					(chr->inlift && posIsArrivingLaterallyAtPos(&chr->prevpos, &prop->pos, &chr->act_gopos.endpos, 30))) {
				if (chr->act_gopos.flags & GOPOSFLAG_FORPATHSTART) {
					chrTryStartPatrol(chr);
					return;
				}

				chrStop(chr);
				return;
			}
		}

		if (advance) {
			chrGoPosAdvanceWaypoint(chr);
		}

		// Every 10 ticks: Check something a couple of waypoints ahead
		// This might be checking if the chr has line of sight to that pad and can
		// walk straight to it.
		if (chr->act_gopos.waydata.age % 10 == 5 || (chr->act_gopos.flags & GOPOSFLAG_INIT)) {
			// Load waypoint that the chr is running to
			waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex];

			if (waypoint) {
				padUnpack(waypoint->padnum, PADFIELD_FLAGS, &pad);

				if ((pad.flags & PADFLAG_AIWALKDIRECT) == 0) {
					// The waypoint the chr is running to doesn't have
					// PADFLAG_AIWALKDIRECT, so the chr is able to ignore it and run
					// towards the next one if it's in sight.

					// Load the next waypoint after the one the chr is running to
					waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex + 1];

					if (waypoint) {
						padUnpack(waypoint->padnum, PADFIELD_FLAGS, &pad);

						if ((pad.flags & PADFLAG_AIWALKDIRECT) == 0) {
							// And this one doesn't have PADFLAG_AIWALKDIRECT either,
							// so the chr can consider skipping this one too.
							waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex + 2];

							if (waypoint) {
								padUnpack(waypoint->padnum, PADFIELD_ROOM | PADFIELD_POS, &pad);

								pos.x = pad.pos.x;
								pos.y = pad.pos.y;
								pos.z = pad.pos.z;

								rooms[0] = pad.room;
								rooms[1] = -1;
							} else {
								pos.x = chr->act_gopos.endpos.x;
								pos.y = chr->act_gopos.endpos.y;
								pos.z = chr->act_gopos.endpos.z;

								roomsCopy(chr->act_gopos.endrooms, rooms);
							}

							// Some bbox related check
							if (func0f03654c(chr, &prop->pos, prop->rooms, &pos, rooms, NULL, chr->chrwidth * 1.2f, CDTYPE_PATHBLOCKER | CDTYPE_BG)) {
								chrGoPosAdvanceWaypoint(chr);
								chrGoPosAdvanceWaypoint(chr);
							}
						}
					}
				}
			}
		}

		if (chr->act_gopos.waydata.age % 10 == 0 || (chr->act_gopos.flags & GOPOSFLAG_INIT)) {
			waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex];

			if (waypoint) {
				candosomething = (chr->act_gopos.flags & GOPOSFLAG_INIT) != 0;
				padUnpack(waypoint->padnum, PADFIELD_FLAGS | PADFIELD_POS, &pad);

				next = chr->act_gopos.waypoints[chr->act_gopos.curindex + 1];

				if (next) {
					padUnpack(next->padnum, PADFIELD_ROOM | PADFIELD_POS, &pad2);

					if ((pad.flags & (PADFLAG_AIWAITLIFT | PADFLAG_AIONLIFT))
							&& (pad2.flags & (PADFLAG_AIWAITLIFT | PADFLAG_AIONLIFT))) {
						candosomething = false;
					}
				}

				if ((pad.flags & PADFLAG_AIWALKDIRECT) == 0 || candosomething) {
					if (next) {
						pos.x = pad2.pos.x;
						pos.y = pad2.pos.y;
						pos.z = pad2.pos.z;

						rooms[0] = pad2.room;
						rooms[1] = -1;
					} else {
						pos.x = chr->act_gopos.endpos.x;
						pos.y = chr->act_gopos.endpos.y;
						pos.z = chr->act_gopos.endpos.z;

						roomsCopy(chr->act_gopos.endrooms, rooms);
					}

					// I suspect this is making the chr turn to face the next pad
					if ((pad.flags & PADFLAG_AIWALKDIRECT) && candosomething) {
						if (true) {
							sp180 = prop->pos.x - pad.pos.x;
							sp176 = prop->pos.z - pad.pos.z;
							sp172 = pos.x - pad.pos.x;
							sp168 = pos.z - pad.pos.z;
						}

						sp156 = sqrtf((sp180 * sp180 + sp176 * sp176) * (sp172 * sp172 + sp168 * sp168));

						if (sp156 > 0) {
							sp160 = func0f0969d0((sp180 * sp172 + sp176 * sp168) / sp156);

							// sp160 < DEG2RAD(45) || sp160 > DEG2RAD(315)
							if (sp160 < 0.7852731347084f || sp160 > 5.4969120025635f) {
								if (func0f03654c(chr, &prop->pos, prop->rooms, &pos, rooms, NULL, chr->chrwidth * 1.2f, CDTYPE_PATHBLOCKER | CDTYPE_BG)) {
									chrGoPosAdvanceWaypoint(chr);
								}
							}
						}
					} else {
						if (func0f03654c(chr, &prop->pos, prop->rooms, &pos, rooms, NULL, chr->chrwidth * 1.2f, CDTYPE_PATHBLOCKER | CDTYPE_BG)) {
							chrGoPosAdvanceWaypoint(chr);
						}
					}
				}
			}

			chr->act_gopos.flags &= ~GOPOSFLAG_INIT;
		}

		waypoint = chr->act_gopos.waypoints[chr->act_gopos.curindex];

		if (waypoint) {
			padUnpack(waypoint->padnum, PADFIELD_POS, &pad);

			pos.x = pad.pos.x;
			pos.y = pad.pos.y;
			pos.z = pad.pos.z;
		} else {
			pos.x = chr->act_gopos.endpos.x;
			pos.y = chr->act_gopos.endpos.y;
			pos.z = chr->act_gopos.endpos.z;

			if (chr->aibot && chr->myaction == MA_AIBOTGETITEM) {
				sp240 = false;
			}
		}

		func0f045b9c(chr, &pos, &chr->act_gopos.waydata, sp240);
	}
}

void chrTickPatrol(struct chrdata *chr)
{
	struct prop *prop = chr->prop;
	bool enteringmagic;
	u32 flags = 0;
	struct coord sp58;
	s16 sp48[8];
	s32 arrivinglaterally;
	s32 arriving;
	bool advance;

	enteringmagic = 0;

	if (chr->hidden & CHRHFLAG_NEEDANIM) {
		if (modelIsAnimMerging(chr->model)) {
			return;
		}

		chrPatrolChooseAnimation(chr);
		chr->hidden &= ~CHRHFLAG_NEEDANIM;
	}

	chrPatrolGetCurWaypointInfoWithFlags(chr, &sp58, sp48, &flags);

	chr->act_patrol.waydata.age++;

	// Consider starting magic
	if (chr->act_patrol.waydata.mode != WAYMODE_MAGIC
			&& g_Vars.lvframe60 > chr->act_patrol.waydata.lastvisible60 + PALDOWN(180)
			&& !g_Vars.normmplayerisrunning
			&& func0f036c08(chr, &sp58, sp48)
			&& (flags & (PADFLAG_AIWAITLIFT | PADFLAG_AIONLIFT)) == 0
			&& !chr->inlift) {
		enteringmagic = true;
		chrGoPosInitMagic(chr, &chr->act_patrol.waydata, &sp58, &prop->pos);
	}

	if (chr->act_patrol.waydata.mode == WAYMODE_MAGIC) {
		if ((!enteringmagic && ((prop->flags & (PROPFLAG_ONTHISSCREENTHISTICK | PROPFLAG_ONANYSCREENTHISTICK | PROPFLAG_ONANYSCREENPREVTICK)) || !func0f036c08(chr, &sp58, sp48)))
				|| (flags & (PADFLAG_AIWAITLIFT | PADFLAG_AIONLIFT))
				|| chr->inlift) {
			// Exit magic for lifts
			chr->act_patrol.waydata.lastvisible60 = g_Vars.lvframe60;
			func0f037580(chr);
		} else {
			// Continue magic
			chrGoPosTickMagic(chr, &chr->act_patrol.waydata, func0f0370a8(chr), &sp58, sp48);
		}

		chrCheckFootstepMagic(chr);
	} else {
		arrivinglaterally = posIsArrivingLaterallyAtPos(&chr->prevpos, &prop->pos, &sp58, 30);
		arriving = posIsArrivingAtPos(&chr->prevpos, &prop->pos, &sp58, 30);
		advance = false;

		if ((flags & PADFLAG_AIWAITLIFT) || (flags & PADFLAG_AIONLIFT)) {
			advance = goPosUpdateLiftAction(chr, flags, arrivinglaterally, arriving,
					chrPatrolCalculatePadNum(chr, 0),
					chrPatrolCalculatePadNum(chr, 1));
		} else if (arriving) {
			advance = true;
		}

		if (advance) {
			func0f0375b0(chr);
			chrPatrolGetCurWaypointInfo(chr, &sp58, sp48);
		}

		func0f045b9c(chr, &sp58, &chr->act_patrol.waydata, 1);
		chrCheckFootstep(chr);
	}
}

bool chrTrySkJump(struct chrdata *chr, u8 arg1, u8 arg2, s32 arg3, u8 arg4)
{
	if (chr && chr->actiontype != ACT_SKJUMP
			&& chrIsReadyForOrders(chr)
			&& CHRRACE(chr) == RACE_SKEDAR) {
		return chrStartSkJump(chr, arg1, arg2, arg3, arg4);
	}

	return false;
}

bool chrStartSkJump(struct chrdata *chr, u8 arg1, u8 arg2, s32 arg3, u8 arg4)
{
	f32 width;
	f32 ymax;
	f32 ymin;
	struct prop *prop = chr->prop;
	struct prop *target = chrGetTargetProp(chr);
	bool iVar2;
	f32 distance = chrGetDistanceToCoord(chr, &target->pos);
	f32 diffs[2];
	f32 thing;
	s32 time60;

	if (distance < 200 || distance > 550 || !target) {
		return false;
	}

	chrGetBbox(prop, &width, &ymax, &ymin);
	chrSetPerimEnabled(chr, false);
	propSetPerimEnabled(target, false);
	iVar2 = cd0002d6ac(&prop->pos, prop->rooms, &target->pos, 51, 1,
			ymax - prop->pos.y, ymin - prop->pos.y);
	chrSetPerimEnabled(chr, true);
	propSetPerimEnabled(target, true);

	if (iVar2) {
		diffs[0] = target->pos.x - chr->prop->pos.x;
		diffs[1] = target->pos.z - chr->prop->pos.z;
		thing = sqrtf(diffs[0] * diffs[0] + diffs[1] * diffs[1]) * 2.5f / PALUPF(21.0f);
		time60 = thing;

		if (time60 < PALDOWN(10)) {
			time60 = PALDOWN(10);
		}

		chr->act_skjump.vel[0] = diffs[0] / time60;
		chr->act_skjump.vel[1] = diffs[1] / time60;
		chr->act_skjump.roty = chrGetInverseTheta(chr) + chrGetAngleToPos(chr, &target->pos);
		chr->act_skjump.hit = false;
		chr->act_skjump.timer60 = time60;
		chr->act_skjump.total60 = time60;
		chr->act_skjump.ground = cdFindGroundYSimple(&chr->prop->pos, chr->chrwidth, chr->prop->rooms, NULL, NULL);
	} else {
		return false;
	}

	chr->actiontype = ACT_SKJUMP;
	chr->act_skjump.needsnewanim = true;
	chr->act_skjump.state = SKJUMPSTATE_TAKEOFF;

	return true;
}

void chrTickSkJump(struct chrdata *chr)
{
	if (g_Vars.lvupdate240_60 == 0) {
		return;
	}

	if (chr->act_skjump.needsnewanim) {
		chr->act_skjump.needsnewanim = false;

		switch (chr->act_skjump.state) {
		case SKJUMPSTATE_TAKEOFF:
			modelSetAnimation(chr->model, ANIM_SKEDAR_JUMPSTART, 0, 0, -1, 8);
			modelSetAnimSpeed(chr->model, 2.5, 0);
			break;
		case SKJUMPSTATE_AIRBORNE: {
				u16 sounds[] = {
					SFX_SKEDAR_ROAR_0532,
					SFX_SKEDAR_ROAR_0533,
					SFX_SKEDAR_ROAR_0534,
				};

				func0f0939f8(NULL, chr->prop, sounds[random() % 3], -1,
						-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
				modelSetAnimation(chr->model, ANIM_SKEDAR_JUMPAIR, 0, 0, -1, 16);
				modelSetAnimSpeed(chr->model, 1, 0);
			}
			break;
		}
	}

	{
		f32 fVar5;
		f32 fVar6;
		f32 fVar7;
		u32 stack[1];
		f32 frame;

		switch (chr->act_skjump.state) {
		case SKJUMPSTATE_TAKEOFF:
			fVar6 = chrGetInverseTheta(chr);
			fVar5 = model0001afe8(fVar6, chr->act_skjump.roty, 0.35);
			chrSetLookAngle(chr, fVar5);
			frame = modelGetCurAnimFrame(chr->model);

			if (frame >= modelGetAnimEndFrame(chr->model)) {
				chr->act_skjump.state++;
				chr->act_skjump.needsnewanim = true;
			}
			break;
		case SKJUMPSTATE_AIRBORNE:
			chr->act_skjump.pos.x = chr->act_skjump.vel[0] * g_Vars.lvupdate240_60 + chr->prop->pos.x;
			chr->act_skjump.pos.z = chr->act_skjump.vel[1] * g_Vars.lvupdate240_60 + chr->prop->pos.z;

			if (chr->act_skjump.total60 > 0) {
				fVar6 = 1.0f - chr->act_skjump.timer60 / (f32)chr->act_skjump.total60;
				fVar7 = sinf(M_PI * fVar6);
				fVar7 = fVar7 * 160.0f + chr->act_skjump.ground;
			} else {
				fVar6 = 1;
				fVar7 = chr->act_skjump.ground;
			}

			chr->act_skjump.pos.y = fVar7 - chr->prop->pos.y;

			if (fVar6 < 0.5f && chr->act_skjump.pos.y < 0.0f) {
				chr->act_skjump.pos.y = 0;
			}

			if (!chr->act_skjump.hit && chrGetDistanceToTarget(chr) < 150.0f) {
				chrPunchInflictDamage(chr, 3, 150, false);
				chr->act_skjump.hit = true;
			}

			if (chr->act_skjump.timer60 > 0) {
				chr->act_skjump.timer60 -= g_Vars.lvupdate240_60;
			} else {
				chrTryStop(chr);
			}
			break;
		}
	}
}

void chraTick(struct chrdata *chr)
{
	u32 race = CHRRACE(chr);

	if (g_Vars.lvupdate240 < 1) {
		return;
	}

	if (chr->actiontype == ACT_INIT) {
		chr->chrflags |= CHRCFLAG_00000001;
		func0f02e9a0(chr, 0);
		chr->sleep = 0;
	}

	if (race == RACE_DRCAROLL) {
		g_DrCarollDyingTimer += g_Vars.lvupdate240_60;
	}

	chr->soundtimer += g_Vars.lvupdate240_60;
	chr->talktimer += g_Vars.lvupdate240_60;

#if VERSION < VERSION_PAL_FINAL
	if (chr->aibot) {
		chr->aibot->unk030 += g_Vars.lvupdate240_60;
	}
#endif

	if (chr->hidden & CHRHFLAG_TIMER_RUNNING) {
		chr->timer60 += g_Vars.lvupdate240_60;
	}

	chr->sleep -= g_Vars.lvupdate240_60;

	if (chr->sleep < 0
			|| (chr->chrflags & CHRCFLAG_00040000)
			|| chr->alertness >= 65
			|| (chr->aibot && (chr->actiontype == ACT_DIE || chr->actiontype == ACT_DEAD))) {
		u8 pass = race == RACE_HUMAN || race == RACE_SKEDAR;
		chr->sleep = 0;

		chraiExecute(chr, PROPTYPE_CHR);

		// Consider setting shootingatmelist
		if (chr->prop) {
			if (chr->aimtesttimer60 < 1) {
				chr->aimtesttimer60 = PALDOWN(30);

				if (chr->aishootingatmelist >= 0
						&& ailistFindById(chr->aishootingatmelist) != chr->ailist
						&& chrCanSeeTargetWithExtraCheck(chr)) {
					chr->chrflags |= CHRCFLAG_CONSIDER_DODGE;
				}
			} else {
				chr->aimtesttimer60 -= g_Vars.lvupdate240_60;
			}
		}

		// Consider setting darkroomlist
		if (chr->prop
				&& chr->aidarkroomlist >= 0
				&& roomGetBrightness(chr->prop->rooms[0]) < 25
				&& ailistFindById(chr->aidarkroomlist) != chr->ailist) {
			chr->darkroomthing = true;
		}

		// Consider setting playerdeadlist
		if (chr->prop && chr->aiplayerdeadlist >= 0 && g_Vars.currentplayer->isdead) {
			u32 prevplayernum = g_Vars.currentplayernum;
			s32 i;
			s32 playercount = PLAYERCOUNT();
			bool alldead = true;

			if (playercount >= 2) {
				for (i = 0; i < playercount && alldead; i++) {
					if (i != prevplayernum) {
						setCurrentPlayerNum(i);

						if (g_Vars.currentplayer->isdead == false) {
							alldead = false;
						}
					}
				}

				setCurrentPlayerNum(prevplayernum);
			}

			if (alldead && ailistFindById(chr->aiplayerdeadlist) != chr->ailist) {
				chr->playerdeadthing = true;
			}
		}

		if (race == RACE_ROBOT) {
			robotSetMuzzleFlash(chr, 0, false);
			robotSetMuzzleFlash(chr, 1, false);
		}

		if (chr->prop) {
			if (g_Vars.in_cutscene) {
				switch (chr->actiontype) {
				case ACT_ANIM:   chrTickAnim(chr);   break;
				case ACT_PATROL: chrTickPatrol(chr); pass = false; break;
				}
			} else {
				switch (chr->actiontype) {
				case ACT_STAND:           chrTickStand(chr);           break;
				case ACT_KNEEL:           chrTickKneel(chr);           break;
				case ACT_ANIM:            chrTickAnim(chr);            break;
				case ACT_DIE:             chrTickDie(chr);             break;
				case ACT_ARGH:            chrTickArgh(chr);            break;
				case ACT_PREARGH:         chrTickPreArgh(chr);         break;
				case ACT_SIDESTEP:        chrTickSidestep(chr);        break;
				case ACT_JUMPOUT:         chrTickJumpOut(chr);         break;
				case ACT_DEAD:            chrTickDead(chr);            break;
				case ACT_ATTACK:          chrTickAttack(chr);          break;
				case ACT_ATTACKWALK:      chrTickAttackWalk(chr);      break;
				case ACT_ATTACKROLL:      chrTickAttackRoll(chr);      break;
				case ACT_RUNPOS:          chrTickRunPos(chr);          break;
				case ACT_PATROL:          chrTickPatrol(chr);          pass = false; break;
				case ACT_GOPOS:           chrTickGoPos(chr);           break;
				case ACT_SURRENDER:       chrTickSurrender(chr);       break;
				case ACT_TEST:            chrTickTest(chr);            break;
				case ACT_SURPRISED:       chrTickSurprised(chr);       break;
				case ACT_STARTALARM:      chrTickStartAlarm(chr);      break;
				case ACT_THROWGRENADE:    chrTickThrowGrenade(chr);    break;
				case ACT_BONDDIE:         chrTickBondDie(chr);         break;
				case ACT_DRUGGEDCOMINGUP: chrTickDruggedComingUp(chr); break;
				case ACT_DRUGGEDDROP:     chrTickDruggedDrop(chr);     break;
				case ACT_DRUGGEDKO:       chrTickDruggedKo(chr);       break;
				case ACT_ATTACKAMOUNT:    chrTickAttackAmount(chr);    break;
				case ACT_ROBOTATTACK:     chrTickRobotAttack(chr);     break;
				case ACT_SKJUMP:          chrTickSkJump(chr);          break;
				}
			}
		}

#if VERSION >= VERSION_NTSC_1_0
		chr->hidden &= ~CHRHFLAG_IS_HEARING_TARGET;
		chr->hidden2 &= ~CHRH2FLAG_0040;
#else
		chr->hidden &= ~(CHRHFLAG_IS_HEARING_TARGET | CHRHFLAG_00000200);
#endif

		if (pass) {
			chrCheckFootstep(chr);
		}
	} else {
		chrCheckFootstepMagic(chr);
	}
}

void cutsceneStart(u32 ailistid)
{
	struct prop *prop;

#if VERSION >= VERSION_PAL_FINAL
	var8009e388pf = 0;
#else
	g_CutsceneFrameOverrun240 = 0;
#endif
	g_CutsceneSkipRequested = false;
	g_CutsceneCurTotalFrame60f = 0;

	prop = g_Vars.activeprops;

	while (prop) {
		prop->lastupdateframe = 0xffff;
		prop->propupdate240 = 0;
		prop->propupdate60err = 2;

		prop = prop->next;
	}

	g_BgChrs[g_NumBgChrs - 1].ailist = ailistFindById(ailistid);
	g_BgChrs[g_NumBgChrs - 1].aioffset = 0;
	g_BgChrs[g_NumBgChrs - 1].aireturnlist = -1;
}


#if VERSION >= VERSION_NTSC_1_0
u32 var80068454 = 0;
#endif

s32 var80068458 = 0;

#if PAL
GLOBAL_ASM(
glabel func0f048398
/*  f048398:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f04839c:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f0483a0:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f0483a4:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f0483a8:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f0483ac:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f0483b0:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0483b4:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f0483b8:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0483bc:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0483c0:	0fc07934 */ 	jal	chrsGetNumSlots
/*  f0483c4:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f0483c8:	3c1e8006 */ 	lui	$s8,%hi(var80062cb0)
/*  f0483cc:	27de2cb0 */ 	addiu	$s8,$s8,%lo(var80062cb0)
/*  f0483d0:	afc00000 */ 	sw	$zero,0x0($s8)
/*  f0483d4:	3c018006 */ 	lui	$at,%hi(var80062cb4)
/*  f0483d8:	ac202cb4 */ 	sw	$zero,%lo(var80062cb4)($at)
/*  f0483dc:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x318)
/*  f0483e0:	8dcea2d8 */ 	lw	$t6,%lo(g_Vars+0x318)($t6)
/*  f0483e4:	3c018006 */ 	lui	$at,%hi(var80062cb8)
/*  f0483e8:	ac202cb8 */ 	sw	$zero,%lo(var80062cb8)($at)
/*  f0483ec:	3c018006 */ 	lui	$at,%hi(var80062cbc)
/*  f0483f0:	afa200e0 */ 	sw	$v0,0xe0($sp)
/*  f0483f4:	afa000dc */ 	sw	$zero,0xdc($sp)
/*  f0483f8:	00009025 */ 	or	$s2,$zero,$zero
/*  f0483fc:	0000b025 */ 	or	$s6,$zero,$zero
/*  f048400:	15c0005a */ 	bnez	$t6,.L0f04856c
/*  f048404:	ac202cbc */ 	sw	$zero,%lo(var80062cbc)($at)
/*  f048408:	18400058 */ 	blez	$v0,.L0f04856c
/*  f04840c:	0000a825 */ 	or	$s5,$zero,$zero
/*  f048410:	00009825 */ 	or	$s3,$zero,$zero
/*  f048414:	24170006 */ 	addiu	$s7,$zero,0x6
/*  f048418:	24140003 */ 	addiu	$s4,$zero,0x3
.L0f04841c:
/*  f04841c:	3c0f8006 */ 	lui	$t7,%hi(g_ChrSlots)
/*  f048420:	8def2988 */ 	lw	$t7,%lo(g_ChrSlots)($t7)
/*  f048424:	026f8021 */ 	addu	$s0,$s3,$t7
/*  f048428:	8e180020 */ 	lw	$t8,0x20($s0)
/*  f04842c:	5300004b */ 	beqzl	$t8,.L0f04855c
/*  f048430:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f048434:	8e19001c */ 	lw	$t9,0x1c($s0)
/*  f048438:	53200048 */ 	beqzl	$t9,.L0f04855c
/*  f04843c:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f048440:	0fc0e6a5 */ 	jal	chrIsDead
/*  f048444:	02002025 */ 	or	$a0,$s0,$zero
/*  f048448:	54400044 */ 	bnezl	$v0,.L0f04855c
/*  f04844c:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f048450:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f048454:	02002025 */ 	or	$a0,$s0,$zero
/*  f048458:	1040003f */ 	beqz	$v0,.L0f048558
/*  f04845c:	00408825 */ 	or	$s1,$v0,$zero
/*  f048460:	90430000 */ 	lbu	$v1,0x0($v0)
/*  f048464:	12830003 */ 	beq	$s4,$v1,.L0f048474
/*  f048468:	00000000 */ 	nop
/*  f04846c:	56e3003b */ 	bnel	$s7,$v1,.L0f04855c
/*  f048470:	8faa00e0 */ 	lw	$t2,0xe0($sp)
.L0f048474:
/*  f048474:	16e30011 */ 	bne	$s7,$v1,.L0f0484bc
/*  f048478:	3c07800a */ 	lui	$a3,%hi(g_Vars)
/*  f04847c:	24e79fc0 */ 	addiu	$a3,$a3,%lo(g_Vars)
/*  f048480:	8ce8029c */ 	lw	$t0,0x29c($a3)
/*  f048484:	02002025 */ 	or	$a0,$s0,$zero
/*  f048488:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f04848c:	05000007 */ 	bltz	$t0,.L0f0484ac
/*  f048490:	00000000 */ 	nop
/*  f048494:	8ce302a8 */ 	lw	$v1,0x2a8($a3)
/*  f048498:	10600004 */ 	beqz	$v1,.L0f0484ac
/*  f04849c:	00000000 */ 	nop
/*  f0484a0:	8c6900bc */ 	lw	$t1,0xbc($v1)
/*  f0484a4:	50490006 */ 	beql	$v0,$t1,.L0f0484c0
/*  f0484a8:	8e220004 */ 	lw	$v0,0x4($s1)
.L0f0484ac:
/*  f0484ac:	0fc12aa3 */ 	jal	chrCompareTeams
/*  f0484b0:	8e250004 */ 	lw	$a1,0x4($s1)
/*  f0484b4:	5440000a */ 	bnezl	$v0,.L0f0484e0
/*  f0484b8:	8fca0000 */ 	lw	$t2,0x0($s8)
.L0f0484bc:
/*  f0484bc:	8e220004 */ 	lw	$v0,0x4($s1)
.L0f0484c0:
/*  f0484c0:	00001825 */ 	or	$v1,$zero,$zero
/*  f0484c4:	10400003 */ 	beqz	$v0,.L0f0484d4
/*  f0484c8:	00000000 */ 	nop
/*  f0484cc:	10000001 */ 	b	.L0f0484d4
/*  f0484d0:	904302fe */ 	lbu	$v1,0x2fe($v0)
.L0f0484d4:
/*  f0484d4:	54740021 */ 	bnel	$v1,$s4,.L0f04855c
/*  f0484d8:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f0484dc:	8fca0000 */ 	lw	$t2,0x0($s8)
.L0f0484e0:
/*  f0484e0:	254b0001 */ 	addiu	$t3,$t2,0x1
/*  f0484e4:	afcb0000 */ 	sw	$t3,0x0($s8)
/*  f0484e8:	8e0300e0 */ 	lw	$v1,0xe0($s0)
/*  f0484ec:	8e0400e4 */ 	lw	$a0,0xe4($s0)
/*  f0484f0:	0083082a */ 	slt	$at,$a0,$v1
/*  f0484f4:	10200003 */ 	beqz	$at,.L0f048504
/*  f0484f8:	00801025 */ 	or	$v0,$a0,$zero
/*  f0484fc:	10000001 */ 	b	.L0f048504
/*  f048500:	00601025 */ 	or	$v0,$v1,$zero
.L0f048504:
/*  f048504:	10400014 */ 	beqz	$v0,.L0f048558
/*  f048508:	3c038006 */ 	lui	$v1,%hi(var80062cb4)
/*  f04850c:	24632cb4 */ 	addiu	$v1,$v1,%lo(var80062cb4)
/*  f048510:	8c6c0000 */ 	lw	$t4,0x0($v1)
/*  f048514:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x8)
/*  f048518:	3c048006 */ 	lui	$a0,%hi(var80062cbc)
/*  f04851c:	258d0001 */ 	addiu	$t5,$t4,0x1
/*  f048520:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*  f048524:	8dce9fc8 */ 	lw	$t6,%lo(g_Vars+0x8)($t6)
/*  f048528:	24842cbc */ 	addiu	$a0,$a0,%lo(var80062cbc)
/*  f04852c:	01c27823 */ 	subu	$t7,$t6,$v0
/*  f048530:	29e100f0 */ 	slti	$at,$t7,0xc8
/*  f048534:	10200008 */ 	beqz	$at,.L0f048558
/*  f048538:	3c028006 */ 	lui	$v0,%hi(var80062cb8)
/*  f04853c:	24422cb8 */ 	addiu	$v0,$v0,%lo(var80062cb8)
/*  f048540:	8c580000 */ 	lw	$t8,0x0($v0)
/*  f048544:	8c880000 */ 	lw	$t0,0x0($a0)
/*  f048548:	27190001 */ 	addiu	$t9,$t8,0x1
/*  f04854c:	25090001 */ 	addiu	$t1,$t0,0x1
/*  f048550:	ac590000 */ 	sw	$t9,0x0($v0)
/*  f048554:	ac890000 */ 	sw	$t1,0x0($a0)
.L0f048558:
/*  f048558:	8faa00e0 */ 	lw	$t2,0xe0($sp)
.L0f04855c:
/*  f04855c:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f048560:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f048564:	16aaffad */ 	bne	$s5,$t2,.L0f04841c
/*  f048568:	00000000 */ 	nop
.L0f04856c:
/*  f04856c:	3c028007 */ 	lui	$v0,%hi(var80068454)
/*  f048570:	8c428454 */ 	lw	$v0,%lo(var80068454)($v0)
/*  f048574:	3c018007 */ 	lui	$at,%hi(var80068454)
/*  f048578:	0000a825 */ 	or	$s5,$zero,$zero
/*  f04857c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f048580:	ac228454 */ 	sw	$v0,%lo(var80068454)($at)
/*  f048584:	2c41000b */ 	sltiu	$at,$v0,0xb
/*  f048588:	14200002 */ 	bnez	$at,.L0f048594
/*  f04858c:	3c018007 */ 	lui	$at,%hi(var80068454)
/*  f048590:	ac208454 */ 	sw	$zero,%lo(var80068454)($at)
.L0f048594:
/*  f048594:	0fc47bac */ 	jal	debugDangerousProps
/*  f048598:	00000000 */ 	nop
/*  f04859c:	10400003 */ 	beqz	$v0,.L0f0485ac
/*  f0485a0:	00000000 */ 	nop
/*  f0485a4:	0fc10e51 */ 	jal	propPrintDangerous
/*  f0485a8:	00000000 */ 	nop
.L0f0485ac:
/*  f0485ac:	3c02800a */ 	lui	$v0,%hi(g_Vars+0x4d2)
/*  f0485b0:	8042a492 */ 	lb	$v0,%lo(g_Vars+0x4d2)($v0)
/*  f0485b4:	04400009 */ 	bltz	$v0,.L0f0485dc
/*  f0485b8:	00000000 */ 	nop
/*  f0485bc:	0fc120b3 */ 	jal	cutsceneStart
/*  f0485c0:	24440c00 */ 	addiu	$a0,$v0,0xc00
/*  f0485c4:	240bffff */ 	addiu	$t3,$zero,-1
/*  f0485c8:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4d2)
/*  f0485cc:	a02ba492 */ 	sb	$t3,%lo(g_Vars+0x4d2)($at)
/*  f0485d0:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4d3)
/*  f0485d4:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0485d8:	a02ca493 */ 	sb	$t4,%lo(g_Vars+0x4d3)($at)
.L0f0485dc:
/*  f0485dc:	3c038006 */ 	lui	$v1,%hi(g_NumBgChrs)
/*  f0485e0:	8c637e60 */ 	lw	$v1,%lo(g_NumBgChrs)($v1)
/*  f0485e4:	00009825 */ 	or	$s3,$zero,$zero
/*  f0485e8:	18600013 */ 	blez	$v1,.L0f048638
.L0f0485ec:
/*  f0485ec:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x4d3)
/*  f0485f0:	81ada493 */ 	lb	$t5,%lo(g_Vars+0x4d3)($t5)
/*  f0485f4:	3c028006 */ 	lui	$v0,%hi(g_BgChrs)
/*  f0485f8:	8c427e58 */ 	lw	$v0,%lo(g_BgChrs)($v0)
/*  f0485fc:	11a00005 */ 	beqz	$t5,.L0f048614
/*  f048600:	00537021 */ 	addu	$t6,$v0,$s3
/*  f048604:	95cf0192 */ 	lhu	$t7,0x192($t6)
/*  f048608:	31f80010 */ 	andi	$t8,$t7,0x10
/*  f04860c:	53000006 */ 	beqzl	$t8,.L0f048628
/*  f048610:	26b50001 */ 	addiu	$s5,$s5,0x1
.L0f048614:
/*  f048614:	0fc11f20 */ 	jal	chraTick
/*  f048618:	02622021 */ 	addu	$a0,$s3,$v0
/*  f04861c:	3c038006 */ 	lui	$v1,%hi(g_NumBgChrs)
/*  f048620:	8c637e60 */ 	lw	$v1,%lo(g_NumBgChrs)($v1)
/*  f048624:	26b50001 */ 	addiu	$s5,$s5,0x1
.L0f048628:
/*  f048628:	02a3082a */ 	slt	$at,$s5,$v1
/*  f04862c:	1420ffef */ 	bnez	$at,.L0f0485ec
/*  f048630:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f048634:	0000a825 */ 	or	$s5,$zero,$zero
.L0f048638:
/*  f048638:	8fb900e0 */ 	lw	$t9,0xe0($sp)
/*  f04863c:	0000a025 */ 	or	$s4,$zero,$zero
/*  f048640:	00009825 */ 	or	$s3,$zero,$zero
/*  f048644:	1b200052 */ 	blez	$t9,.L0f048790
/*  f048648:	241e001f */ 	addiu	$s8,$zero,0x1f
/*  f04864c:	24170005 */ 	addiu	$s7,$zero,0x5
/*  f048650:	27b1007c */ 	addiu	$s1,$sp,0x7c
.L0f048654:
/*  f048654:	3c088006 */ 	lui	$t0,%hi(g_ChrSlots)
/*  f048658:	8d082988 */ 	lw	$t0,%lo(g_ChrSlots)($t0)
/*  f04865c:	02682021 */ 	addu	$a0,$s3,$t0
/*  f048660:	8c890020 */ 	lw	$t1,0x20($a0)
/*  f048664:	51200046 */ 	beqzl	$t1,.L0f048780
/*  f048668:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f04866c:	8c83001c */ 	lw	$v1,0x1c($a0)
/*  f048670:	50600043 */ 	beqzl	$v1,.L0f048780
/*  f048674:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f048678:	80820007 */ 	lb	$v0,0x7($a0)
/*  f04867c:	52e20005 */ 	beql	$s7,$v0,.L0f048694
/*  f048680:	906a0001 */ 	lbu	$t2,0x1($v1)
/*  f048684:	53c20003 */ 	beql	$s8,$v0,.L0f048694
/*  f048688:	906a0001 */ 	lbu	$t2,0x1($v1)
/*  f04868c:	26940001 */ 	addiu	$s4,$s4,0x1
/*  f048690:	906a0001 */ 	lbu	$t2,0x1($v1)
.L0f048694:
/*  f048694:	314b0080 */ 	andi	$t3,$t2,0x80
/*  f048698:	11600011 */ 	beqz	$t3,.L0f0486e0
/*  f04869c:	00000000 */ 	nop
/*  f0486a0:	12e20006 */ 	beq	$s7,$v0,.L0f0486bc
/*  f0486a4:	00000000 */ 	nop
/*  f0486a8:	13c20004 */ 	beq	$s8,$v0,.L0f0486bc
/*  f0486ac:	8fac00dc */ 	lw	$t4,0xdc($sp)
/*  f0486b0:	258d0001 */ 	addiu	$t5,$t4,0x1
/*  f0486b4:	1000000a */ 	b	.L0f0486e0
/*  f0486b8:	afad00dc */ 	sw	$t5,0xdc($sp)
.L0f0486bc:
/*  f0486bc:	57c20008 */ 	bnel	$s8,$v0,.L0f0486e0
/*  f0486c0:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f0486c4:	8c8e0018 */ 	lw	$t6,0x18($a0)
/*  f0486c8:	000e7940 */ 	sll	$t7,$t6,0x5
/*  f0486cc:	05e00004 */ 	bltz	$t7,.L0f0486e0
/*  f0486d0:	00000000 */ 	nop
/*  f0486d4:	10000002 */ 	b	.L0f0486e0
/*  f0486d8:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f0486dc:	26d60001 */ 	addiu	$s6,$s6,0x1
.L0f0486e0:
/*  f0486e0:	52e20008 */ 	beql	$s7,$v0,.L0f048704
/*  f0486e4:	94880192 */ 	lhu	$t0,0x192($a0)
/*  f0486e8:	57c20025 */ 	bnel	$s8,$v0,.L0f048780
/*  f0486ec:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f0486f0:	8c980018 */ 	lw	$t8,0x18($a0)
/*  f0486f4:	0018c940 */ 	sll	$t9,$t8,0x5
/*  f0486f8:	07220021 */ 	bltzl	$t9,.L0f048780
/*  f0486fc:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f048700:	94880192 */ 	lhu	$t0,0x192($a0)
.L0f048704:
/*  f048704:	00125080 */ 	sll	$t2,$s2,0x2
/*  f048708:	022a1821 */ 	addu	$v1,$s1,$t2
/*  f04870c:	31090080 */ 	andi	$t1,$t0,0x80
/*  f048710:	5120001b */ 	beqzl	$t1,.L0f048780
/*  f048714:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f048718:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f04871c:	2a41000a */ 	slti	$at,$s2,0xa
/*  f048720:	ac640000 */ 	sw	$a0,0x0($v1)
/*  f048724:	14200015 */ 	bnez	$at,.L0f04877c
/*  f048728:	24630004 */ 	addiu	$v1,$v1,4
/*  f04872c:	0c004b70 */ 	jal	random
/*  f048730:	afa30048 */ 	sw	$v1,0x48($sp)
/*  f048734:	0052001b */ 	divu	$zero,$v0,$s2
/*  f048738:	00002810 */ 	mfhi	$a1
/*  f04873c:	00055880 */ 	sll	$t3,$a1,0x2
/*  f048740:	022b6021 */ 	addu	$t4,$s1,$t3
/*  f048744:	00a08025 */ 	or	$s0,$a1,$zero
/*  f048748:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f04874c:	16400002 */ 	bnez	$s2,.L0f048758
/*  f048750:	00000000 */ 	nop
/*  f048754:	0007000d */ 	break	0x7
.L0f048758:
/*  f048758:	8d840000 */ 	lw	$a0,0x0($t4)
/*  f04875c:	0fc0f337 */ 	jal	chrFadeCorpse
/*  f048760:	00000000 */ 	nop
/*  f048764:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f048768:	00107080 */ 	sll	$t6,$s0,0x2
/*  f04876c:	022e7821 */ 	addu	$t7,$s1,$t6
/*  f048770:	8c6dfffc */ 	lw	$t5,-0x4($v1)
/*  f048774:	2652ffff */ 	addiu	$s2,$s2,-1
/*  f048778:	aded0000 */ 	sw	$t5,0x0($t7)
.L0f04877c:
/*  f04877c:	8fb800e0 */ 	lw	$t8,0xe0($sp)
.L0f048780:
/*  f048780:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f048784:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f048788:	16b8ffb2 */ 	bne	$s5,$t8,.L0f048654
/*  f04878c:	00000000 */ 	nop
.L0f048790:
/*  f048790:	3c198007 */ 	lui	$t9,%hi(var80068458)
/*  f048794:	8f398458 */ 	lw	$t9,%lo(var80068458)($t9)
/*  f048798:	24170005 */ 	addiu	$s7,$zero,0x5
/*  f04879c:	241e001f */ 	addiu	$s8,$zero,0x1f
/*  f0487a0:	0334082a */ 	slt	$at,$t9,$s4
/*  f0487a4:	10200003 */ 	beqz	$at,.L0f0487b4
/*  f0487a8:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x38)
/*  f0487ac:	3c018007 */ 	lui	$at,%hi(var80068458)
/*  f0487b0:	ac348458 */ 	sw	$s4,%lo(var80068458)($at)
.L0f0487b4:
/*  f0487b4:	8fa800dc */ 	lw	$t0,0xdc($sp)
/*  f0487b8:	8c639ff8 */ 	lw	$v1,%lo(g_Vars+0x38)($v1)
/*  f0487bc:	00008825 */ 	or	$s1,$zero,$zero
/*  f0487c0:	02e81023 */ 	subu	$v0,$s7,$t0
/*  f0487c4:	28610007 */ 	slti	$at,$v1,0x7
/*  f0487c8:	14200004 */ 	bnez	$at,.L0f0487dc
/*  f0487cc:	afa20074 */ 	sw	$v0,0x74($sp)
/*  f0487d0:	00434823 */ 	subu	$t1,$v0,$v1
/*  f0487d4:	252a0006 */ 	addiu	$t2,$t1,0x6
/*  f0487d8:	afaa0074 */ 	sw	$t2,0x74($sp)
.L0f0487dc:
/*  f0487dc:	8fab0074 */ 	lw	$t3,0x74($sp)
/*  f0487e0:	05610002 */ 	bgez	$t3,.L0f0487ec
/*  f0487e4:	00000000 */ 	nop
/*  f0487e8:	afa00074 */ 	sw	$zero,0x74($sp)
.L0f0487ec:
/*  f0487ec:	12c0007d */ 	beqz	$s6,.L0f0489e4
/*  f0487f0:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f0487f4:	0000b025 */ 	or	$s6,$zero,$zero
/*  f0487f8:	00009025 */ 	or	$s2,$zero,$zero
/*  f0487fc:	19800079 */ 	blez	$t4,.L0f0489e4
/*  f048800:	0000a825 */ 	or	$s5,$zero,$zero
/*  f048804:	00009825 */ 	or	$s3,$zero,$zero
/*  f048808:	27b400a4 */ 	addiu	$s4,$sp,0xa4
.L0f04880c:
/*  f04880c:	3c0e8006 */ 	lui	$t6,%hi(g_ChrSlots)
/*  f048810:	8dce2988 */ 	lw	$t6,%lo(g_ChrSlots)($t6)
/*  f048814:	026e2021 */ 	addu	$a0,$s3,$t6
/*  f048818:	8c8d0020 */ 	lw	$t5,0x20($a0)
/*  f04881c:	51a0006d */ 	beqzl	$t5,.L0f0489d4
/*  f048820:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048824:	80820007 */ 	lb	$v0,0x7($a0)
/*  f048828:	52e2000b */ 	beql	$s7,$v0,.L0f048858
/*  f04882c:	8c88001c */ 	lw	$t0,0x1c($a0)
/*  f048830:	57c20068 */ 	bnel	$s8,$v0,.L0f0489d4
/*  f048834:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048838:	8c8f001c */ 	lw	$t7,0x1c($a0)
/*  f04883c:	51e00065 */ 	beqzl	$t7,.L0f0489d4
/*  f048840:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048844:	8c980018 */ 	lw	$t8,0x18($a0)
/*  f048848:	0018c940 */ 	sll	$t9,$t8,0x5
/*  f04884c:	07220061 */ 	bltzl	$t9,.L0f0489d4
/*  f048850:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048854:	8c88001c */ 	lw	$t0,0x1c($a0)
.L0f048858:
/*  f048858:	91090001 */ 	lbu	$t1,0x1($t0)
/*  f04885c:	312a0080 */ 	andi	$t2,$t1,0x80
/*  f048860:	51400033 */ 	beqzl	$t2,.L0f048930
/*  f048864:	8c8c0030 */ 	lw	$t4,0x30($a0)
/*  f048868:	8c8b0038 */ 	lw	$t3,0x38($a0)
/*  f04886c:	05630059 */ 	bgezl	$t3,.L0f0489d4
/*  f048870:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048874:	8c8c002c */ 	lw	$t4,0x2c($a0)
/*  f048878:	8fae0074 */ 	lw	$t6,0x74($sp)
/*  f04887c:	55800055 */ 	bnezl	$t4,.L0f0489d4
/*  f048880:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048884:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f048888:	01d6082a */ 	slt	$at,$t6,$s6
/*  f04888c:	14200004 */ 	bnez	$at,.L0f0488a0
/*  f048890:	00000000 */ 	nop
/*  f048894:	8c8d02d4 */ 	lw	$t5,0x2d4($a0)
/*  f048898:	51a00006 */ 	beqzl	$t5,.L0f0488b4
/*  f04889c:	8c8f0030 */ 	lw	$t7,0x30($a0)
.L0f0488a0:
/*  f0488a0:	0fc0f337 */ 	jal	chrFadeCorpse
/*  f0488a4:	00000000 */ 	nop
/*  f0488a8:	10000049 */ 	b	.L0f0489d0
/*  f0488ac:	26d6ffff */ 	addiu	$s6,$s6,-1
/*  f0488b0:	8c8f0030 */ 	lw	$t7,0x30($a0)
.L0f0488b4:
/*  f0488b4:	0011c080 */ 	sll	$t8,$s1,0x2
/*  f0488b8:	27b900b8 */ 	addiu	$t9,$sp,0xb8
/*  f0488bc:	15e00044 */ 	bnez	$t7,.L0f0489d0
/*  f0488c0:	03191821 */ 	addu	$v1,$t8,$t9
/*  f0488c4:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0488c8:	2a210002 */ 	slti	$at,$s1,0x2
/*  f0488cc:	ac640000 */ 	sw	$a0,0x0($v1)
/*  f0488d0:	1420003f */ 	bnez	$at,.L0f0489d0
/*  f0488d4:	24630004 */ 	addiu	$v1,$v1,4
/*  f0488d8:	0c004b70 */ 	jal	random
/*  f0488dc:	afa30048 */ 	sw	$v1,0x48($sp)
/*  f0488e0:	0051001b */ 	divu	$zero,$v0,$s1
/*  f0488e4:	00002810 */ 	mfhi	$a1
/*  f0488e8:	00054080 */ 	sll	$t0,$a1,0x2
/*  f0488ec:	03a82021 */ 	addu	$a0,$sp,$t0
/*  f0488f0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f0488f4:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f0488f8:	16200002 */ 	bnez	$s1,.L0f048904
/*  f0488fc:	00000000 */ 	nop
/*  f048900:	0007000d */ 	break	0x7
.L0f048904:
/*  f048904:	8c8400b8 */ 	lw	$a0,0xb8($a0)
/*  f048908:	0fc0f341 */ 	jal	chrFadeCorpseWhenOffScreen
/*  f04890c:	00000000 */ 	nop
/*  f048910:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f048914:	00105080 */ 	sll	$t2,$s0,0x2
/*  f048918:	03aa5821 */ 	addu	$t3,$sp,$t2
/*  f04891c:	8c69fffc */ 	lw	$t1,-0x4($v1)
/*  f048920:	2631ffff */ 	addiu	$s1,$s1,-1
/*  f048924:	1000002a */ 	b	.L0f0489d0
/*  f048928:	ad6900b8 */ 	sw	$t1,0xb8($t3)
/*  f04892c:	8c8c0030 */ 	lw	$t4,0x30($a0)
.L0f048930:
/*  f048930:	00127080 */ 	sll	$t6,$s2,0x2
/*  f048934:	028e2821 */ 	addu	$a1,$s4,$t6
/*  f048938:	55800026 */ 	bnezl	$t4,.L0f0489d4
/*  f04893c:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048940:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f048944:	2a410005 */ 	slti	$at,$s2,0x5
/*  f048948:	aca40000 */ 	sw	$a0,0x0($a1)
/*  f04894c:	14200020 */ 	bnez	$at,.L0f0489d0
/*  f048950:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f048954:	0c004b70 */ 	jal	random
/*  f048958:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f04895c:	0052001b */ 	divu	$zero,$v0,$s2
/*  f048960:	00001810 */ 	mfhi	$v1
/*  f048964:	00036880 */ 	sll	$t5,$v1,0x2
/*  f048968:	028d7821 */ 	addu	$t7,$s4,$t5
/*  f04896c:	8df80000 */ 	lw	$t8,0x0($t7)
/*  f048970:	00608025 */ 	or	$s0,$v1,$zero
/*  f048974:	8fa50048 */ 	lw	$a1,0x48($sp)
/*  f048978:	83190007 */ 	lb	$t9,0x7($t8)
/*  f04897c:	16400002 */ 	bnez	$s2,.L0f048988
/*  f048980:	00000000 */ 	nop
/*  f048984:	0007000d */ 	break	0x7
.L0f048988:
/*  f048988:	00034080 */ 	sll	$t0,$v1,0x2
/*  f04898c:	12f90005 */ 	beq	$s7,$t9,.L0f0489a4
/*  f048990:	02884821 */ 	addu	$t1,$s4,$t0
/*  f048994:	8d240000 */ 	lw	$a0,0x0($t1)
/*  f048998:	0fc0c467 */ 	jal	chrBeginDead
/*  f04899c:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f0489a0:	8fa50048 */ 	lw	$a1,0x48($sp)
.L0f0489a4:
/*  f0489a4:	00105080 */ 	sll	$t2,$s0,0x2
/*  f0489a8:	028a1021 */ 	addu	$v0,$s4,$t2
/*  f0489ac:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f0489b0:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f0489b4:	0fc0f341 */ 	jal	chrFadeCorpseWhenOffScreen
/*  f0489b8:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f0489bc:	8fa50048 */ 	lw	$a1,0x48($sp)
/*  f0489c0:	8fa20044 */ 	lw	$v0,0x44($sp)
/*  f0489c4:	2652ffff */ 	addiu	$s2,$s2,-1
/*  f0489c8:	8cabfffc */ 	lw	$t3,-0x4($a1)
/*  f0489cc:	ac4b0000 */ 	sw	$t3,0x0($v0)
.L0f0489d0:
/*  f0489d0:	8fac00e0 */ 	lw	$t4,0xe0($sp)
.L0f0489d4:
/*  f0489d4:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f0489d8:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f0489dc:	16acff8b */ 	bne	$s5,$t4,.L0f04880c
/*  f0489e0:	00000000 */ 	nop
.L0f0489e4:
/*  f0489e4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0489e8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0489ec:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f0489f0:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f0489f4:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0489f8:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0489fc:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f048a00:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f048a04:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f048a08:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f048a0c:	03e00008 */ 	jr	$ra
/*  f048a10:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f048398
/*  f048398:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f04839c:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f0483a0:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f0483a4:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f0483a8:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f0483ac:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f0483b0:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f0483b4:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f0483b8:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f0483bc:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f0483c0:	0fc07934 */ 	jal	chrsGetNumSlots
/*  f0483c4:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f0483c8:	3c1e8006 */ 	lui	$s8,%hi(var80062cb0)
/*  f0483cc:	27de2cb0 */ 	addiu	$s8,$s8,%lo(var80062cb0)
/*  f0483d0:	afc00000 */ 	sw	$zero,0x0($s8)
/*  f0483d4:	3c018006 */ 	lui	$at,%hi(var80062cb4)
/*  f0483d8:	ac202cb4 */ 	sw	$zero,%lo(var80062cb4)($at)
/*  f0483dc:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x318)
/*  f0483e0:	8dcea2d8 */ 	lw	$t6,%lo(g_Vars+0x318)($t6)
/*  f0483e4:	3c018006 */ 	lui	$at,%hi(var80062cb8)
/*  f0483e8:	ac202cb8 */ 	sw	$zero,%lo(var80062cb8)($at)
/*  f0483ec:	3c018006 */ 	lui	$at,%hi(var80062cbc)
/*  f0483f0:	afa200e0 */ 	sw	$v0,0xe0($sp)
/*  f0483f4:	afa000dc */ 	sw	$zero,0xdc($sp)
/*  f0483f8:	00009025 */ 	or	$s2,$zero,$zero
/*  f0483fc:	0000b025 */ 	or	$s6,$zero,$zero
/*  f048400:	15c0005a */ 	bnez	$t6,.L0f04856c
/*  f048404:	ac202cbc */ 	sw	$zero,%lo(var80062cbc)($at)
/*  f048408:	18400058 */ 	blez	$v0,.L0f04856c
/*  f04840c:	0000a825 */ 	or	$s5,$zero,$zero
/*  f048410:	00009825 */ 	or	$s3,$zero,$zero
/*  f048414:	24170006 */ 	addiu	$s7,$zero,0x6
/*  f048418:	24140003 */ 	addiu	$s4,$zero,0x3
.L0f04841c:
/*  f04841c:	3c0f8006 */ 	lui	$t7,%hi(g_ChrSlots)
/*  f048420:	8def2988 */ 	lw	$t7,%lo(g_ChrSlots)($t7)
/*  f048424:	026f8021 */ 	addu	$s0,$s3,$t7
/*  f048428:	8e180020 */ 	lw	$t8,0x20($s0)
/*  f04842c:	5300004b */ 	beqzl	$t8,.L0f04855c
/*  f048430:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f048434:	8e19001c */ 	lw	$t9,0x1c($s0)
/*  f048438:	53200048 */ 	beqzl	$t9,.L0f04855c
/*  f04843c:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f048440:	0fc0e6a5 */ 	jal	chrIsDead
/*  f048444:	02002025 */ 	or	$a0,$s0,$zero
/*  f048448:	54400044 */ 	bnezl	$v0,.L0f04855c
/*  f04844c:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f048450:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f048454:	02002025 */ 	or	$a0,$s0,$zero
/*  f048458:	1040003f */ 	beqz	$v0,.L0f048558
/*  f04845c:	00408825 */ 	or	$s1,$v0,$zero
/*  f048460:	90430000 */ 	lbu	$v1,0x0($v0)
/*  f048464:	12830003 */ 	beq	$s4,$v1,.L0f048474
/*  f048468:	00000000 */ 	nop
/*  f04846c:	56e3003b */ 	bnel	$s7,$v1,.L0f04855c
/*  f048470:	8faa00e0 */ 	lw	$t2,0xe0($sp)
.L0f048474:
/*  f048474:	16e30011 */ 	bne	$s7,$v1,.L0f0484bc
/*  f048478:	3c07800a */ 	lui	$a3,%hi(g_Vars)
/*  f04847c:	24e79fc0 */ 	addiu	$a3,$a3,%lo(g_Vars)
/*  f048480:	8ce8029c */ 	lw	$t0,0x29c($a3)
/*  f048484:	02002025 */ 	or	$a0,$s0,$zero
/*  f048488:	24060002 */ 	addiu	$a2,$zero,0x2
/*  f04848c:	05000007 */ 	bltz	$t0,.L0f0484ac
/*  f048490:	00000000 */ 	nop
/*  f048494:	8ce302a8 */ 	lw	$v1,0x2a8($a3)
/*  f048498:	10600004 */ 	beqz	$v1,.L0f0484ac
/*  f04849c:	00000000 */ 	nop
/*  f0484a0:	8c6900bc */ 	lw	$t1,0xbc($v1)
/*  f0484a4:	50490006 */ 	beql	$v0,$t1,.L0f0484c0
/*  f0484a8:	8e220004 */ 	lw	$v0,0x4($s1)
.L0f0484ac:
/*  f0484ac:	0fc12aa3 */ 	jal	chrCompareTeams
/*  f0484b0:	8e250004 */ 	lw	$a1,0x4($s1)
/*  f0484b4:	5440000a */ 	bnezl	$v0,.L0f0484e0
/*  f0484b8:	8fca0000 */ 	lw	$t2,0x0($s8)
.L0f0484bc:
/*  f0484bc:	8e220004 */ 	lw	$v0,0x4($s1)
.L0f0484c0:
/*  f0484c0:	00001825 */ 	or	$v1,$zero,$zero
/*  f0484c4:	10400003 */ 	beqz	$v0,.L0f0484d4
/*  f0484c8:	00000000 */ 	nop
/*  f0484cc:	10000001 */ 	b	.L0f0484d4
/*  f0484d0:	904302fe */ 	lbu	$v1,0x2fe($v0)
.L0f0484d4:
/*  f0484d4:	54740021 */ 	bnel	$v1,$s4,.L0f04855c
/*  f0484d8:	8faa00e0 */ 	lw	$t2,0xe0($sp)
/*  f0484dc:	8fca0000 */ 	lw	$t2,0x0($s8)
.L0f0484e0:
/*  f0484e0:	254b0001 */ 	addiu	$t3,$t2,0x1
/*  f0484e4:	afcb0000 */ 	sw	$t3,0x0($s8)
/*  f0484e8:	8e0300e0 */ 	lw	$v1,0xe0($s0)
/*  f0484ec:	8e0400e4 */ 	lw	$a0,0xe4($s0)
/*  f0484f0:	0083082a */ 	slt	$at,$a0,$v1
/*  f0484f4:	10200003 */ 	beqz	$at,.L0f048504
/*  f0484f8:	00801025 */ 	or	$v0,$a0,$zero
/*  f0484fc:	10000001 */ 	b	.L0f048504
/*  f048500:	00601025 */ 	or	$v0,$v1,$zero
.L0f048504:
/*  f048504:	10400014 */ 	beqz	$v0,.L0f048558
/*  f048508:	3c038006 */ 	lui	$v1,%hi(var80062cb4)
/*  f04850c:	24632cb4 */ 	addiu	$v1,$v1,%lo(var80062cb4)
/*  f048510:	8c6c0000 */ 	lw	$t4,0x0($v1)
/*  f048514:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x8)
/*  f048518:	3c048006 */ 	lui	$a0,%hi(var80062cbc)
/*  f04851c:	258d0001 */ 	addiu	$t5,$t4,0x1
/*  f048520:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*  f048524:	8dce9fc8 */ 	lw	$t6,%lo(g_Vars+0x8)($t6)
/*  f048528:	24842cbc */ 	addiu	$a0,$a0,%lo(var80062cbc)
/*  f04852c:	01c27823 */ 	subu	$t7,$t6,$v0
/*  f048530:	29e100f0 */ 	slti	$at,$t7,0xf0
/*  f048534:	10200008 */ 	beqz	$at,.L0f048558
/*  f048538:	3c028006 */ 	lui	$v0,%hi(var80062cb8)
/*  f04853c:	24422cb8 */ 	addiu	$v0,$v0,%lo(var80062cb8)
/*  f048540:	8c580000 */ 	lw	$t8,0x0($v0)
/*  f048544:	8c880000 */ 	lw	$t0,0x0($a0)
/*  f048548:	27190001 */ 	addiu	$t9,$t8,0x1
/*  f04854c:	25090001 */ 	addiu	$t1,$t0,0x1
/*  f048550:	ac590000 */ 	sw	$t9,0x0($v0)
/*  f048554:	ac890000 */ 	sw	$t1,0x0($a0)
.L0f048558:
/*  f048558:	8faa00e0 */ 	lw	$t2,0xe0($sp)
.L0f04855c:
/*  f04855c:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f048560:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f048564:	16aaffad */ 	bne	$s5,$t2,.L0f04841c
/*  f048568:	00000000 */ 	nop
.L0f04856c:
/*  f04856c:	3c028007 */ 	lui	$v0,%hi(var80068454)
/*  f048570:	8c428454 */ 	lw	$v0,%lo(var80068454)($v0)
/*  f048574:	3c018007 */ 	lui	$at,%hi(var80068454)
/*  f048578:	0000a825 */ 	or	$s5,$zero,$zero
/*  f04857c:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f048580:	ac228454 */ 	sw	$v0,%lo(var80068454)($at)
/*  f048584:	2c41000b */ 	sltiu	$at,$v0,0xb
/*  f048588:	14200002 */ 	bnez	$at,.L0f048594
/*  f04858c:	3c018007 */ 	lui	$at,%hi(var80068454)
/*  f048590:	ac208454 */ 	sw	$zero,%lo(var80068454)($at)
.L0f048594:
/*  f048594:	0fc47bac */ 	jal	debugDangerousProps
/*  f048598:	00000000 */ 	nop
/*  f04859c:	10400003 */ 	beqz	$v0,.L0f0485ac
/*  f0485a0:	00000000 */ 	nop
/*  f0485a4:	0fc10e51 */ 	jal	propPrintDangerous
/*  f0485a8:	00000000 */ 	nop
.L0f0485ac:
/*  f0485ac:	3c02800a */ 	lui	$v0,%hi(g_Vars+0x4d2)
/*  f0485b0:	8042a492 */ 	lb	$v0,%lo(g_Vars+0x4d2)($v0)
/*  f0485b4:	04400009 */ 	bltz	$v0,.L0f0485dc
/*  f0485b8:	00000000 */ 	nop
/*  f0485bc:	0fc120b3 */ 	jal	cutsceneStart
/*  f0485c0:	24440c00 */ 	addiu	$a0,$v0,0xc00
/*  f0485c4:	240bffff */ 	addiu	$t3,$zero,-1
/*  f0485c8:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4d2)
/*  f0485cc:	a02ba492 */ 	sb	$t3,%lo(g_Vars+0x4d2)($at)
/*  f0485d0:	3c01800a */ 	lui	$at,%hi(g_Vars+0x4d3)
/*  f0485d4:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f0485d8:	a02ca493 */ 	sb	$t4,%lo(g_Vars+0x4d3)($at)
.L0f0485dc:
/*  f0485dc:	3c038006 */ 	lui	$v1,%hi(g_NumBgChrs)
/*  f0485e0:	8c637e60 */ 	lw	$v1,%lo(g_NumBgChrs)($v1)
/*  f0485e4:	00009825 */ 	or	$s3,$zero,$zero
/*  f0485e8:	18600013 */ 	blez	$v1,.L0f048638
.L0f0485ec:
/*  f0485ec:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x4d3)
/*  f0485f0:	81ada493 */ 	lb	$t5,%lo(g_Vars+0x4d3)($t5)
/*  f0485f4:	3c028006 */ 	lui	$v0,%hi(g_BgChrs)
/*  f0485f8:	8c427e58 */ 	lw	$v0,%lo(g_BgChrs)($v0)
/*  f0485fc:	11a00005 */ 	beqz	$t5,.L0f048614
/*  f048600:	00537021 */ 	addu	$t6,$v0,$s3
/*  f048604:	95cf0192 */ 	lhu	$t7,0x192($t6)
/*  f048608:	31f80010 */ 	andi	$t8,$t7,0x10
/*  f04860c:	53000006 */ 	beqzl	$t8,.L0f048628
/*  f048610:	26b50001 */ 	addiu	$s5,$s5,0x1
.L0f048614:
/*  f048614:	0fc11f20 */ 	jal	chraTick
/*  f048618:	02622021 */ 	addu	$a0,$s3,$v0
/*  f04861c:	3c038006 */ 	lui	$v1,%hi(g_NumBgChrs)
/*  f048620:	8c637e60 */ 	lw	$v1,%lo(g_NumBgChrs)($v1)
/*  f048624:	26b50001 */ 	addiu	$s5,$s5,0x1
.L0f048628:
/*  f048628:	02a3082a */ 	slt	$at,$s5,$v1
/*  f04862c:	1420ffef */ 	bnez	$at,.L0f0485ec
/*  f048630:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f048634:	0000a825 */ 	or	$s5,$zero,$zero
.L0f048638:
/*  f048638:	8fb900e0 */ 	lw	$t9,0xe0($sp)
/*  f04863c:	0000a025 */ 	or	$s4,$zero,$zero
/*  f048640:	00009825 */ 	or	$s3,$zero,$zero
/*  f048644:	1b200052 */ 	blez	$t9,.L0f048790
/*  f048648:	241e001f */ 	addiu	$s8,$zero,0x1f
/*  f04864c:	24170005 */ 	addiu	$s7,$zero,0x5
/*  f048650:	27b1007c */ 	addiu	$s1,$sp,0x7c
.L0f048654:
/*  f048654:	3c088006 */ 	lui	$t0,%hi(g_ChrSlots)
/*  f048658:	8d082988 */ 	lw	$t0,%lo(g_ChrSlots)($t0)
/*  f04865c:	02682021 */ 	addu	$a0,$s3,$t0
/*  f048660:	8c890020 */ 	lw	$t1,0x20($a0)
/*  f048664:	51200046 */ 	beqzl	$t1,.L0f048780
/*  f048668:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f04866c:	8c83001c */ 	lw	$v1,0x1c($a0)
/*  f048670:	50600043 */ 	beqzl	$v1,.L0f048780
/*  f048674:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f048678:	80820007 */ 	lb	$v0,0x7($a0)
/*  f04867c:	52e20005 */ 	beql	$s7,$v0,.L0f048694
/*  f048680:	906a0001 */ 	lbu	$t2,0x1($v1)
/*  f048684:	53c20003 */ 	beql	$s8,$v0,.L0f048694
/*  f048688:	906a0001 */ 	lbu	$t2,0x1($v1)
/*  f04868c:	26940001 */ 	addiu	$s4,$s4,0x1
/*  f048690:	906a0001 */ 	lbu	$t2,0x1($v1)
.L0f048694:
/*  f048694:	314b0080 */ 	andi	$t3,$t2,0x80
/*  f048698:	11600011 */ 	beqz	$t3,.L0f0486e0
/*  f04869c:	00000000 */ 	nop
/*  f0486a0:	12e20006 */ 	beq	$s7,$v0,.L0f0486bc
/*  f0486a4:	00000000 */ 	nop
/*  f0486a8:	13c20004 */ 	beq	$s8,$v0,.L0f0486bc
/*  f0486ac:	8fac00dc */ 	lw	$t4,0xdc($sp)
/*  f0486b0:	258d0001 */ 	addiu	$t5,$t4,0x1
/*  f0486b4:	1000000a */ 	b	.L0f0486e0
/*  f0486b8:	afad00dc */ 	sw	$t5,0xdc($sp)
.L0f0486bc:
/*  f0486bc:	57c20008 */ 	bnel	$s8,$v0,.L0f0486e0
/*  f0486c0:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f0486c4:	8c8e0018 */ 	lw	$t6,0x18($a0)
/*  f0486c8:	000e7940 */ 	sll	$t7,$t6,0x5
/*  f0486cc:	05e00004 */ 	bltz	$t7,.L0f0486e0
/*  f0486d0:	00000000 */ 	nop
/*  f0486d4:	10000002 */ 	b	.L0f0486e0
/*  f0486d8:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f0486dc:	26d60001 */ 	addiu	$s6,$s6,0x1
.L0f0486e0:
/*  f0486e0:	52e20008 */ 	beql	$s7,$v0,.L0f048704
/*  f0486e4:	94880192 */ 	lhu	$t0,0x192($a0)
/*  f0486e8:	57c20025 */ 	bnel	$s8,$v0,.L0f048780
/*  f0486ec:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f0486f0:	8c980018 */ 	lw	$t8,0x18($a0)
/*  f0486f4:	0018c940 */ 	sll	$t9,$t8,0x5
/*  f0486f8:	07220021 */ 	bltzl	$t9,.L0f048780
/*  f0486fc:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f048700:	94880192 */ 	lhu	$t0,0x192($a0)
.L0f048704:
/*  f048704:	00125080 */ 	sll	$t2,$s2,0x2
/*  f048708:	022a1821 */ 	addu	$v1,$s1,$t2
/*  f04870c:	31090080 */ 	andi	$t1,$t0,0x80
/*  f048710:	5120001b */ 	beqzl	$t1,.L0f048780
/*  f048714:	8fb800e0 */ 	lw	$t8,0xe0($sp)
/*  f048718:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f04871c:	2a41000a */ 	slti	$at,$s2,0xa
/*  f048720:	ac640000 */ 	sw	$a0,0x0($v1)
/*  f048724:	14200015 */ 	bnez	$at,.L0f04877c
/*  f048728:	24630004 */ 	addiu	$v1,$v1,4
/*  f04872c:	0c004b70 */ 	jal	random
/*  f048730:	afa30048 */ 	sw	$v1,0x48($sp)
/*  f048734:	0052001b */ 	divu	$zero,$v0,$s2
/*  f048738:	00002810 */ 	mfhi	$a1
/*  f04873c:	00055880 */ 	sll	$t3,$a1,0x2
/*  f048740:	022b6021 */ 	addu	$t4,$s1,$t3
/*  f048744:	00a08025 */ 	or	$s0,$a1,$zero
/*  f048748:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f04874c:	16400002 */ 	bnez	$s2,.L0f048758
/*  f048750:	00000000 */ 	nop
/*  f048754:	0007000d */ 	break	0x7
.L0f048758:
/*  f048758:	8d840000 */ 	lw	$a0,0x0($t4)
/*  f04875c:	0fc0f337 */ 	jal	chrFadeCorpse
/*  f048760:	00000000 */ 	nop
/*  f048764:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f048768:	00107080 */ 	sll	$t6,$s0,0x2
/*  f04876c:	022e7821 */ 	addu	$t7,$s1,$t6
/*  f048770:	8c6dfffc */ 	lw	$t5,-0x4($v1)
/*  f048774:	2652ffff */ 	addiu	$s2,$s2,-1
/*  f048778:	aded0000 */ 	sw	$t5,0x0($t7)
.L0f04877c:
/*  f04877c:	8fb800e0 */ 	lw	$t8,0xe0($sp)
.L0f048780:
/*  f048780:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f048784:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f048788:	16b8ffb2 */ 	bne	$s5,$t8,.L0f048654
/*  f04878c:	00000000 */ 	nop
.L0f048790:
/*  f048790:	3c198007 */ 	lui	$t9,%hi(var80068458)
/*  f048794:	8f398458 */ 	lw	$t9,%lo(var80068458)($t9)
/*  f048798:	24170005 */ 	addiu	$s7,$zero,0x5
/*  f04879c:	241e001f */ 	addiu	$s8,$zero,0x1f
/*  f0487a0:	0334082a */ 	slt	$at,$t9,$s4
/*  f0487a4:	10200003 */ 	beqz	$at,.L0f0487b4
/*  f0487a8:	3c03800a */ 	lui	$v1,%hi(g_Vars+0x38)
/*  f0487ac:	3c018007 */ 	lui	$at,%hi(var80068458)
/*  f0487b0:	ac348458 */ 	sw	$s4,%lo(var80068458)($at)
.L0f0487b4:
/*  f0487b4:	8fa800dc */ 	lw	$t0,0xdc($sp)
/*  f0487b8:	8c639ff8 */ 	lw	$v1,%lo(g_Vars+0x38)($v1)
/*  f0487bc:	00008825 */ 	or	$s1,$zero,$zero
/*  f0487c0:	02e81023 */ 	subu	$v0,$s7,$t0
/*  f0487c4:	28610007 */ 	slti	$at,$v1,0x7
/*  f0487c8:	14200004 */ 	bnez	$at,.L0f0487dc
/*  f0487cc:	afa20074 */ 	sw	$v0,0x74($sp)
/*  f0487d0:	00434823 */ 	subu	$t1,$v0,$v1
/*  f0487d4:	252a0006 */ 	addiu	$t2,$t1,0x6
/*  f0487d8:	afaa0074 */ 	sw	$t2,0x74($sp)
.L0f0487dc:
/*  f0487dc:	8fab0074 */ 	lw	$t3,0x74($sp)
/*  f0487e0:	05610002 */ 	bgez	$t3,.L0f0487ec
/*  f0487e4:	00000000 */ 	nop
/*  f0487e8:	afa00074 */ 	sw	$zero,0x74($sp)
.L0f0487ec:
/*  f0487ec:	12c0007d */ 	beqz	$s6,.L0f0489e4
/*  f0487f0:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f0487f4:	0000b025 */ 	or	$s6,$zero,$zero
/*  f0487f8:	00009025 */ 	or	$s2,$zero,$zero
/*  f0487fc:	19800079 */ 	blez	$t4,.L0f0489e4
/*  f048800:	0000a825 */ 	or	$s5,$zero,$zero
/*  f048804:	00009825 */ 	or	$s3,$zero,$zero
/*  f048808:	27b400a4 */ 	addiu	$s4,$sp,0xa4
.L0f04880c:
/*  f04880c:	3c0e8006 */ 	lui	$t6,%hi(g_ChrSlots)
/*  f048810:	8dce2988 */ 	lw	$t6,%lo(g_ChrSlots)($t6)
/*  f048814:	026e2021 */ 	addu	$a0,$s3,$t6
/*  f048818:	8c8d0020 */ 	lw	$t5,0x20($a0)
/*  f04881c:	51a0006d */ 	beqzl	$t5,.L0f0489d4
/*  f048820:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048824:	80820007 */ 	lb	$v0,0x7($a0)
/*  f048828:	52e2000b */ 	beql	$s7,$v0,.L0f048858
/*  f04882c:	8c88001c */ 	lw	$t0,0x1c($a0)
/*  f048830:	57c20068 */ 	bnel	$s8,$v0,.L0f0489d4
/*  f048834:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048838:	8c8f001c */ 	lw	$t7,0x1c($a0)
/*  f04883c:	51e00065 */ 	beqzl	$t7,.L0f0489d4
/*  f048840:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048844:	8c980018 */ 	lw	$t8,0x18($a0)
/*  f048848:	0018c940 */ 	sll	$t9,$t8,0x5
/*  f04884c:	07220061 */ 	bltzl	$t9,.L0f0489d4
/*  f048850:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048854:	8c88001c */ 	lw	$t0,0x1c($a0)
.L0f048858:
/*  f048858:	91090001 */ 	lbu	$t1,0x1($t0)
/*  f04885c:	312a0080 */ 	andi	$t2,$t1,0x80
/*  f048860:	51400033 */ 	beqzl	$t2,.L0f048930
/*  f048864:	8c8c0030 */ 	lw	$t4,0x30($a0)
/*  f048868:	8c8b0038 */ 	lw	$t3,0x38($a0)
/*  f04886c:	05630059 */ 	bgezl	$t3,.L0f0489d4
/*  f048870:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048874:	8c8c002c */ 	lw	$t4,0x2c($a0)
/*  f048878:	8fae0074 */ 	lw	$t6,0x74($sp)
/*  f04887c:	55800055 */ 	bnezl	$t4,.L0f0489d4
/*  f048880:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048884:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f048888:	01d6082a */ 	slt	$at,$t6,$s6
/*  f04888c:	14200004 */ 	bnez	$at,.L0f0488a0
/*  f048890:	00000000 */ 	nop
/*  f048894:	8c8d02d4 */ 	lw	$t5,0x2d4($a0)
/*  f048898:	51a00006 */ 	beqzl	$t5,.L0f0488b4
/*  f04889c:	8c8f0030 */ 	lw	$t7,0x30($a0)
.L0f0488a0:
/*  f0488a0:	0fc0f337 */ 	jal	chrFadeCorpse
/*  f0488a4:	00000000 */ 	nop
/*  f0488a8:	10000049 */ 	b	.L0f0489d0
/*  f0488ac:	26d6ffff */ 	addiu	$s6,$s6,-1
/*  f0488b0:	8c8f0030 */ 	lw	$t7,0x30($a0)
.L0f0488b4:
/*  f0488b4:	0011c080 */ 	sll	$t8,$s1,0x2
/*  f0488b8:	27b900b8 */ 	addiu	$t9,$sp,0xb8
/*  f0488bc:	15e00044 */ 	bnez	$t7,.L0f0489d0
/*  f0488c0:	03191821 */ 	addu	$v1,$t8,$t9
/*  f0488c4:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f0488c8:	2a210002 */ 	slti	$at,$s1,0x2
/*  f0488cc:	ac640000 */ 	sw	$a0,0x0($v1)
/*  f0488d0:	1420003f */ 	bnez	$at,.L0f0489d0
/*  f0488d4:	24630004 */ 	addiu	$v1,$v1,4
/*  f0488d8:	0c004b70 */ 	jal	random
/*  f0488dc:	afa30048 */ 	sw	$v1,0x48($sp)
/*  f0488e0:	0051001b */ 	divu	$zero,$v0,$s1
/*  f0488e4:	00002810 */ 	mfhi	$a1
/*  f0488e8:	00054080 */ 	sll	$t0,$a1,0x2
/*  f0488ec:	03a82021 */ 	addu	$a0,$sp,$t0
/*  f0488f0:	00a08025 */ 	or	$s0,$a1,$zero
/*  f0488f4:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f0488f8:	16200002 */ 	bnez	$s1,.L0f048904
/*  f0488fc:	00000000 */ 	nop
/*  f048900:	0007000d */ 	break	0x7
.L0f048904:
/*  f048904:	8c8400b8 */ 	lw	$a0,0xb8($a0)
/*  f048908:	0fc0f341 */ 	jal	chrFadeCorpseWhenOffScreen
/*  f04890c:	00000000 */ 	nop
/*  f048910:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f048914:	00105080 */ 	sll	$t2,$s0,0x2
/*  f048918:	03aa5821 */ 	addu	$t3,$sp,$t2
/*  f04891c:	8c69fffc */ 	lw	$t1,-0x4($v1)
/*  f048920:	2631ffff */ 	addiu	$s1,$s1,-1
/*  f048924:	1000002a */ 	b	.L0f0489d0
/*  f048928:	ad6900b8 */ 	sw	$t1,0xb8($t3)
/*  f04892c:	8c8c0030 */ 	lw	$t4,0x30($a0)
.L0f048930:
/*  f048930:	00127080 */ 	sll	$t6,$s2,0x2
/*  f048934:	028e2821 */ 	addu	$a1,$s4,$t6
/*  f048938:	55800026 */ 	bnezl	$t4,.L0f0489d4
/*  f04893c:	8fac00e0 */ 	lw	$t4,0xe0($sp)
/*  f048940:	26520001 */ 	addiu	$s2,$s2,0x1
/*  f048944:	2a410005 */ 	slti	$at,$s2,0x5
/*  f048948:	aca40000 */ 	sw	$a0,0x0($a1)
/*  f04894c:	14200020 */ 	bnez	$at,.L0f0489d0
/*  f048950:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f048954:	0c004b70 */ 	jal	random
/*  f048958:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f04895c:	0052001b */ 	divu	$zero,$v0,$s2
/*  f048960:	00001810 */ 	mfhi	$v1
/*  f048964:	00036880 */ 	sll	$t5,$v1,0x2
/*  f048968:	028d7821 */ 	addu	$t7,$s4,$t5
/*  f04896c:	8df80000 */ 	lw	$t8,0x0($t7)
/*  f048970:	00608025 */ 	or	$s0,$v1,$zero
/*  f048974:	8fa50048 */ 	lw	$a1,0x48($sp)
/*  f048978:	83190007 */ 	lb	$t9,0x7($t8)
/*  f04897c:	16400002 */ 	bnez	$s2,.L0f048988
/*  f048980:	00000000 */ 	nop
/*  f048984:	0007000d */ 	break	0x7
.L0f048988:
/*  f048988:	00034080 */ 	sll	$t0,$v1,0x2
/*  f04898c:	12f90005 */ 	beq	$s7,$t9,.L0f0489a4
/*  f048990:	02884821 */ 	addu	$t1,$s4,$t0
/*  f048994:	8d240000 */ 	lw	$a0,0x0($t1)
/*  f048998:	0fc0c467 */ 	jal	chrBeginDead
/*  f04899c:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f0489a0:	8fa50048 */ 	lw	$a1,0x48($sp)
.L0f0489a4:
/*  f0489a4:	00105080 */ 	sll	$t2,$s0,0x2
/*  f0489a8:	028a1021 */ 	addu	$v0,$s4,$t2
/*  f0489ac:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f0489b0:	afa50048 */ 	sw	$a1,0x48($sp)
/*  f0489b4:	0fc0f341 */ 	jal	chrFadeCorpseWhenOffScreen
/*  f0489b8:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f0489bc:	8fa50048 */ 	lw	$a1,0x48($sp)
/*  f0489c0:	8fa20044 */ 	lw	$v0,0x44($sp)
/*  f0489c4:	2652ffff */ 	addiu	$s2,$s2,-1
/*  f0489c8:	8cabfffc */ 	lw	$t3,-0x4($a1)
/*  f0489cc:	ac4b0000 */ 	sw	$t3,0x0($v0)
.L0f0489d0:
/*  f0489d0:	8fac00e0 */ 	lw	$t4,0xe0($sp)
.L0f0489d4:
/*  f0489d4:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f0489d8:	26730368 */ 	addiu	$s3,$s3,0x368
/*  f0489dc:	16acff8b */ 	bne	$s5,$t4,.L0f04880c
/*  f0489e0:	00000000 */ 	nop
.L0f0489e4:
/*  f0489e4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f0489e8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f0489ec:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f0489f0:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f0489f4:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f0489f8:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f0489fc:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f048a00:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f048a04:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f048a08:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f048a0c:	03e00008 */ 	jr	$ra
/*  f048a10:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
);
#else
GLOBAL_ASM(
glabel func0f048398
/*  f047abc:	27bdff60 */ 	addiu	$sp,$sp,-160
/*  f047ac0:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f047ac4:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f047ac8:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f047acc:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f047ad0:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f047ad4:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f047ad8:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f047adc:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f047ae0:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f047ae4:	0fc0786c */ 	jal	chrsGetNumSlots
/*  f047ae8:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f047aec:	afa20098 */ 	sw	$v0,0x98($sp)
/*  f047af0:	00008025 */ 	or	$s0,$zero,$zero
/*  f047af4:	0000a025 */ 	or	$s4,$zero,$zero
/*  f047af8:	0000b025 */ 	or	$s6,$zero,$zero
/*  f047afc:	0fc466ab */ 	jal	debugDangerousProps
/*  f047b00:	0000b825 */ 	or	$s7,$zero,$zero
/*  f047b04:	10400003 */ 	beqz	$v0,.NB0f047b14
/*  f047b08:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047b0c:	0fc10c44 */ 	jal	propPrintDangerous
/*  f047b10:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f047b14:
/*  f047b14:	3c02800a */ 	lui	$v0,0x800a
/*  f047b18:	8042eb92 */ 	lb	$v0,-0x146e($v0)
/*  f047b1c:	04400009 */ 	bltz	$v0,.NB0f047b44
/*  f047b20:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047b24:	0fc11e7c */ 	jal	cutsceneStart
/*  f047b28:	24440c00 */ 	addiu	$a0,$v0,0xc00
/*  f047b2c:	3c02800a */ 	lui	$v0,0x800a
/*  f047b30:	2442e6c0 */ 	addiu	$v0,$v0,-6464
/*  f047b34:	240effff */ 	addiu	$t6,$zero,-1
/*  f047b38:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f047b3c:	a04e04d2 */ 	sb	$t6,0x4d2($v0)
/*  f047b40:	a04f04d3 */ 	sb	$t7,0x4d3($v0)
.NB0f047b44:
/*  f047b44:	3c038007 */ 	lui	$v1,0x8007
/*  f047b48:	8c63a578 */ 	lw	$v1,-0x5a88($v1)
/*  f047b4c:	00009825 */ 	or	$s3,$zero,$zero
/*  f047b50:	00009025 */ 	or	$s2,$zero,$zero
/*  f047b54:	18600013 */ 	blez	$v1,.NB0f047ba4
.NB0f047b58:
/*  f047b58:	3c18800a */ 	lui	$t8,0x800a
/*  f047b5c:	8318eb93 */ 	lb	$t8,-0x146d($t8)
/*  f047b60:	3c028007 */ 	lui	$v0,0x8007
/*  f047b64:	8c42a570 */ 	lw	$v0,-0x5a90($v0)
/*  f047b68:	13000005 */ 	beqz	$t8,.NB0f047b80
/*  f047b6c:	0052c821 */ 	addu	$t9,$v0,$s2
/*  f047b70:	972a0192 */ 	lhu	$t2,0x192($t9)
/*  f047b74:	314b0010 */ 	andi	$t3,$t2,0x10
/*  f047b78:	51600006 */ 	beqzl	$t3,.NB0f047b94
/*  f047b7c:	26730001 */ 	addiu	$s3,$s3,0x1
.NB0f047b80:
/*  f047b80:	0fc11cec */ 	jal	chraTick
/*  f047b84:	02422021 */ 	addu	$a0,$s2,$v0
/*  f047b88:	3c038007 */ 	lui	$v1,0x8007
/*  f047b8c:	8c63a578 */ 	lw	$v1,-0x5a88($v1)
/*  f047b90:	26730001 */ 	addiu	$s3,$s3,0x1
.NB0f047b94:
/*  f047b94:	0263082a */ 	slt	$at,$s3,$v1
/*  f047b98:	1420ffef */ 	bnez	$at,.NB0f047b58
/*  f047b9c:	26520368 */ 	addiu	$s2,$s2,0x368
/*  f047ba0:	00009825 */ 	or	$s3,$zero,$zero
.NB0f047ba4:
/*  f047ba4:	8fa90098 */ 	lw	$t1,0x98($sp)
/*  f047ba8:	00003025 */ 	or	$a2,$zero,$zero
/*  f047bac:	3c058006 */ 	lui	$a1,0x8006
/*  f047bb0:	19200027 */ 	blez	$t1,.NB0f047c50
/*  f047bb4:	3c198007 */ 	lui	$t9,0x8007
/*  f047bb8:	8ca54e98 */ 	lw	$a1,0x4e98($a1)
/*  f047bbc:	2408001f */ 	addiu	$t0,$zero,0x1f
/*  f047bc0:	24070005 */ 	addiu	$a3,$zero,0x5
.NB0f047bc4:
/*  f047bc4:	8cac0020 */ 	lw	$t4,0x20($a1)
/*  f047bc8:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f047bcc:	00a02025 */ 	or	$a0,$a1,$zero
/*  f047bd0:	1180001d */ 	beqz	$t4,.NB0f047c48
/*  f047bd4:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047bd8:	8c83001c */ 	lw	$v1,0x1c($a0)
/*  f047bdc:	1060001a */ 	beqz	$v1,.NB0f047c48
/*  f047be0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047be4:	80820007 */ 	lb	$v0,0x7($a0)
/*  f047be8:	50e20005 */ 	beql	$a3,$v0,.NB0f047c00
/*  f047bec:	906d0001 */ 	lbu	$t5,0x1($v1)
/*  f047bf0:	51020003 */ 	beql	$t0,$v0,.NB0f047c00
/*  f047bf4:	906d0001 */ 	lbu	$t5,0x1($v1)
/*  f047bf8:	24c60001 */ 	addiu	$a2,$a2,0x1
/*  f047bfc:	906d0001 */ 	lbu	$t5,0x1($v1)
.NB0f047c00:
/*  f047c00:	31ae0080 */ 	andi	$t6,$t5,0x80
/*  f047c04:	11c00010 */ 	beqz	$t6,.NB0f047c48
/*  f047c08:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047c0c:	10e20005 */ 	beq	$a3,$v0,.NB0f047c24
/*  f047c10:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047c14:	11020003 */ 	beq	$t0,$v0,.NB0f047c24
/*  f047c18:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047c1c:	1000000a */ 	beqz	$zero,.NB0f047c48
/*  f047c20:	26100001 */ 	addiu	$s0,$s0,0x1
.NB0f047c24:
/*  f047c24:	55020008 */ 	bnel	$t0,$v0,.NB0f047c48
/*  f047c28:	26940001 */ 	addiu	$s4,$s4,0x1
/*  f047c2c:	8c8f0018 */ 	lw	$t7,0x18($a0)
/*  f047c30:	000fc140 */ 	sll	$t8,$t7,0x5
/*  f047c34:	07000004 */ 	bltz	$t8,.NB0f047c48
/*  f047c38:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047c3c:	10000002 */ 	beqz	$zero,.NB0f047c48
/*  f047c40:	26940001 */ 	addiu	$s4,$s4,0x1
/*  f047c44:	26940001 */ 	addiu	$s4,$s4,0x1
.NB0f047c48:
/*  f047c48:	1669ffde */ 	bne	$s3,$t1,.NB0f047bc4
/*  f047c4c:	24a50368 */ 	addiu	$a1,$a1,0x368
.NB0f047c50:
/*  f047c50:	8f39ab60 */ 	lw	$t9,-0x54a0($t9)
/*  f047c54:	24070005 */ 	addiu	$a3,$zero,0x5
/*  f047c58:	3c03800a */ 	lui	$v1,0x800a
/*  f047c5c:	0326082a */ 	slt	$at,$t9,$a2
/*  f047c60:	10200003 */ 	beqz	$at,.NB0f047c70
/*  f047c64:	00009825 */ 	or	$s3,$zero,$zero
/*  f047c68:	3c018007 */ 	lui	$at,0x8007
/*  f047c6c:	ac26ab60 */ 	sw	$a2,-0x54a0($at)
.NB0f047c70:
/*  f047c70:	8c63e6f8 */ 	lw	$v1,-0x1908($v1)
/*  f047c74:	00f01023 */ 	subu	$v0,$a3,$s0
/*  f047c78:	afa20058 */ 	sw	$v0,0x58($sp)
/*  f047c7c:	28610007 */ 	slti	$at,$v1,0x7
/*  f047c80:	14200003 */ 	bnez	$at,.NB0f047c90
/*  f047c84:	00435023 */ 	subu	$t2,$v0,$v1
/*  f047c88:	254b0006 */ 	addiu	$t3,$t2,0x6
/*  f047c8c:	afab0058 */ 	sw	$t3,0x58($sp)
.NB0f047c90:
/*  f047c90:	8fac0058 */ 	lw	$t4,0x58($sp)
/*  f047c94:	3c018006 */ 	lui	$at,0x8006
/*  f047c98:	05810002 */ 	bgez	$t4,.NB0f047ca4
/*  f047c9c:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047ca0:	afa00058 */ 	sw	$zero,0x58($sp)
.NB0f047ca4:
/*  f047ca4:	12800093 */ 	beqz	$s4,.NB0f047ef4
/*  f047ca8:	0000a025 */ 	or	$s4,$zero,$zero
/*  f047cac:	19200091 */ 	blez	$t1,.NB0f047ef4
/*  f047cb0:	ac2051c0 */ 	sw	$zero,0x51c0($at)
/*  f047cb4:	00009025 */ 	or	$s2,$zero,$zero
/*  f047cb8:	27be0074 */ 	addiu	$s8,$sp,0x74
/*  f047cbc:	27b50060 */ 	addiu	$s5,$sp,0x60
.NB0f047cc0:
/*  f047cc0:	3c0d8006 */ 	lui	$t5,0x8006
/*  f047cc4:	8dad4e98 */ 	lw	$t5,0x4e98($t5)
/*  f047cc8:	3c0f800a */ 	lui	$t7,0x800a
/*  f047ccc:	024d2021 */ 	addu	$a0,$s2,$t5
/*  f047cd0:	8c8e0020 */ 	lw	$t6,0x20($a0)
/*  f047cd4:	51c00083 */ 	beqzl	$t6,.NB0f047ee4
/*  f047cd8:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047cdc:	8defe9d4 */ 	lw	$t7,-0x162c($t7)
/*  f047ce0:	55e00017 */ 	bnezl	$t7,.NB0f047d40
/*  f047ce4:	80820007 */ 	lb	$v0,0x7($a0)
/*  f047ce8:	0fc0a08c */ 	jal	chrGetTargetProp
/*  f047cec:	afa4004c */ 	sw	$a0,0x4c($sp)
/*  f047cf0:	90580000 */ 	lbu	$t8,0x0($v0)
/*  f047cf4:	24010006 */ 	addiu	$at,$zero,0x6
/*  f047cf8:	8fa4004c */ 	lw	$a0,0x4c($sp)
/*  f047cfc:	57010010 */ 	bnel	$t8,$at,.NB0f047d40
/*  f047d00:	80820007 */ 	lb	$v0,0x7($a0)
/*  f047d04:	8c8200e0 */ 	lw	$v0,0xe0($a0)
/*  f047d08:	3c19800a */ 	lui	$t9,0x800a
/*  f047d0c:	5840000c */ 	blezl	$v0,.NB0f047d40
/*  f047d10:	80820007 */ 	lb	$v0,0x7($a0)
/*  f047d14:	8f39e6c8 */ 	lw	$t9,-0x1938($t9)
/*  f047d18:	3c0b8006 */ 	lui	$t3,0x8006
/*  f047d1c:	03225023 */ 	subu	$t2,$t9,$v0
/*  f047d20:	29410078 */ 	slti	$at,$t2,0x78
/*  f047d24:	50200006 */ 	beqzl	$at,.NB0f047d40
/*  f047d28:	80820007 */ 	lb	$v0,0x7($a0)
/*  f047d2c:	8d6b51c0 */ 	lw	$t3,0x51c0($t3)
/*  f047d30:	3c018006 */ 	lui	$at,0x8006
/*  f047d34:	256c0001 */ 	addiu	$t4,$t3,0x1
/*  f047d38:	ac2c51c0 */ 	sw	$t4,0x51c0($at)
/*  f047d3c:	80820007 */ 	lb	$v0,0x7($a0)
.NB0f047d40:
/*  f047d40:	24010005 */ 	addiu	$at,$zero,0x5
/*  f047d44:	1041000a */ 	beq	$v0,$at,.NB0f047d70
/*  f047d48:	2401001f */ 	addiu	$at,$zero,0x1f
/*  f047d4c:	54410065 */ 	bnel	$v0,$at,.NB0f047ee4
/*  f047d50:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047d54:	8c8d001c */ 	lw	$t5,0x1c($a0)
/*  f047d58:	51a00062 */ 	beqzl	$t5,.NB0f047ee4
/*  f047d5c:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047d60:	8c8e0018 */ 	lw	$t6,0x18($a0)
/*  f047d64:	000e7940 */ 	sll	$t7,$t6,0x5
/*  f047d68:	05e2005e */ 	bltzl	$t7,.NB0f047ee4
/*  f047d6c:	8fb80098 */ 	lw	$t8,0x98($sp)
.NB0f047d70:
/*  f047d70:	8c98001c */ 	lw	$t8,0x1c($a0)
/*  f047d74:	93190001 */ 	lbu	$t9,0x1($t8)
/*  f047d78:	332a0080 */ 	andi	$t2,$t9,0x80
/*  f047d7c:	51400033 */ 	beqzl	$t2,.NB0f047e4c
/*  f047d80:	8c8e0030 */ 	lw	$t6,0x30($a0)
/*  f047d84:	8c8b0038 */ 	lw	$t3,0x38($a0)
/*  f047d88:	05630056 */ 	bgezl	$t3,.NB0f047ee4
/*  f047d8c:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047d90:	8c8c002c */ 	lw	$t4,0x2c($a0)
/*  f047d94:	8fad0058 */ 	lw	$t5,0x58($sp)
/*  f047d98:	55800052 */ 	bnezl	$t4,.NB0f047ee4
/*  f047d9c:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047da0:	26940001 */ 	addiu	$s4,$s4,0x1
/*  f047da4:	01b4082a */ 	slt	$at,$t5,$s4
/*  f047da8:	14200004 */ 	bnez	$at,.NB0f047dbc
/*  f047dac:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047db0:	8c8e02d4 */ 	lw	$t6,0x2d4($a0)
/*  f047db4:	51c00006 */ 	beqzl	$t6,.NB0f047dd0
/*  f047db8:	8c8f0030 */ 	lw	$t7,0x30($a0)
.NB0f047dbc:
/*  f047dbc:	0fc0f136 */ 	jal	chrFadeCorpse
/*  f047dc0:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047dc4:	10000046 */ 	beqz	$zero,.NB0f047ee0
/*  f047dc8:	2694ffff */ 	addiu	$s4,$s4,-1
/*  f047dcc:	8c8f0030 */ 	lw	$t7,0x30($a0)
.NB0f047dd0:
/*  f047dd0:	0016c080 */ 	sll	$t8,$s6,0x2
/*  f047dd4:	03d81821 */ 	addu	$v1,$s8,$t8
/*  f047dd8:	55e00042 */ 	bnezl	$t7,.NB0f047ee4
/*  f047ddc:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047de0:	26d60001 */ 	addiu	$s6,$s6,0x1
/*  f047de4:	2ac10003 */ 	slti	$at,$s6,0x3
/*  f047de8:	ac640000 */ 	sw	$a0,0x0($v1)
/*  f047dec:	1420003c */ 	bnez	$at,.NB0f047ee0
/*  f047df0:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f047df4:	0c004d84 */ 	jal	random
/*  f047df8:	afa30048 */ 	sw	$v1,0x48($sp)
/*  f047dfc:	0056001b */ 	divu	$zero,$v0,$s6
/*  f047e00:	00002810 */ 	mfhi	$a1
/*  f047e04:	0005c880 */ 	sll	$t9,$a1,0x2
/*  f047e08:	03d95021 */ 	addu	$t2,$s8,$t9
/*  f047e0c:	00a08825 */ 	or	$s1,$a1,$zero
/*  f047e10:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f047e14:	16c00002 */ 	bnez	$s6,.NB0f047e20
/*  f047e18:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047e1c:	0007000d */ 	break	0x7
.NB0f047e20:
/*  f047e20:	8d440000 */ 	lw	$a0,0x0($t2)
/*  f047e24:	0fc0f140 */ 	jal	chrFadeCorpseWhenOffScreen
/*  f047e28:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047e2c:	8fa30048 */ 	lw	$v1,0x48($sp)
/*  f047e30:	00116080 */ 	sll	$t4,$s1,0x2
/*  f047e34:	03cc6821 */ 	addu	$t5,$s8,$t4
/*  f047e38:	8c6bfffc */ 	lw	$t3,-0x4($v1)
/*  f047e3c:	26d6ffff */ 	addiu	$s6,$s6,-1
/*  f047e40:	10000027 */ 	beqz	$zero,.NB0f047ee0
/*  f047e44:	adab0000 */ 	sw	$t3,0x0($t5)
/*  f047e48:	8c8e0030 */ 	lw	$t6,0x30($a0)
.NB0f047e4c:
/*  f047e4c:	00177880 */ 	sll	$t7,$s7,0x2
/*  f047e50:	55c00024 */ 	bnezl	$t6,.NB0f047ee4
/*  f047e54:	8fb80098 */ 	lw	$t8,0x98($sp)
/*  f047e58:	26f70001 */ 	addiu	$s7,$s7,0x1
/*  f047e5c:	02af8021 */ 	addu	$s0,$s5,$t7
/*  f047e60:	2ae10006 */ 	slti	$at,$s7,0x6
/*  f047e64:	ae040000 */ 	sw	$a0,0x0($s0)
/*  f047e68:	1420001d */ 	bnez	$at,.NB0f047ee0
/*  f047e6c:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f047e70:	0c004d84 */ 	jal	random
/*  f047e74:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047e78:	0057001b */ 	divu	$zero,$v0,$s7
/*  f047e7c:	00001810 */ 	mfhi	$v1
/*  f047e80:	0003c080 */ 	sll	$t8,$v1,0x2
/*  f047e84:	02b8c821 */ 	addu	$t9,$s5,$t8
/*  f047e88:	8f2a0000 */ 	lw	$t2,0x0($t9)
/*  f047e8c:	16e00002 */ 	bnez	$s7,.NB0f047e98
/*  f047e90:	00000000 */ 	sll	$zero,$zero,0x0
/*  f047e94:	0007000d */ 	break	0x7
.NB0f047e98:
/*  f047e98:	814c0007 */ 	lb	$t4,0x7($t2)
/*  f047e9c:	24010005 */ 	addiu	$at,$zero,0x5
/*  f047ea0:	00608825 */ 	or	$s1,$v1,$zero
/*  f047ea4:	11810004 */ 	beq	$t4,$at,.NB0f047eb8
/*  f047ea8:	00035880 */ 	sll	$t3,$v1,0x2
/*  f047eac:	02ab6821 */ 	addu	$t5,$s5,$t3
/*  f047eb0:	0fc0c2b7 */ 	jal	chrBeginDead
/*  f047eb4:	8da40000 */ 	lw	$a0,0x0($t5)
.NB0f047eb8:
/*  f047eb8:	00117080 */ 	sll	$t6,$s1,0x2
/*  f047ebc:	02ae1021 */ 	addu	$v0,$s5,$t6
/*  f047ec0:	8c440000 */ 	lw	$a0,0x0($v0)
/*  f047ec4:	0fc0f140 */ 	jal	chrFadeCorpseWhenOffScreen
/*  f047ec8:	afa20044 */ 	sw	$v0,0x44($sp)
/*  f047ecc:	8fa20044 */ 	lw	$v0,0x44($sp)
/*  f047ed0:	8e0ffffc */ 	lw	$t7,-0x4($s0)
/*  f047ed4:	26f7ffff */ 	addiu	$s7,$s7,-1
/*  f047ed8:	2610fffc */ 	addiu	$s0,$s0,-4
/*  f047edc:	ac4f0000 */ 	sw	$t7,0x0($v0)
.NB0f047ee0:
/*  f047ee0:	8fb80098 */ 	lw	$t8,0x98($sp)
.NB0f047ee4:
/*  f047ee4:	26730001 */ 	addiu	$s3,$s3,0x1
/*  f047ee8:	26520368 */ 	addiu	$s2,$s2,0x368
/*  f047eec:	1678ff74 */ 	bne	$s3,$t8,.NB0f047cc0
/*  f047ef0:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f047ef4:
/*  f047ef4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f047ef8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f047efc:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f047f00:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f047f04:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f047f08:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f047f0c:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f047f10:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f047f14:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f047f18:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f047f1c:	03e00008 */ 	jr	$ra
/*  f047f20:	27bd00a0 */ 	addiu	$sp,$sp,0xa0
);
#endif

// Mismatch because it uses the stack differently.
//void func0f048398(void)
//{
//	s32 numchrs = chrsGetNumSlots(); // e0
//	s32 numalivewithpropflag80; // dc
//	struct chrdata *spb8[10];
//	struct chrdata *spa4[5]; // a4
//	struct chrdata *sp7c[10]; // 7c
//	s32 writeindex;
//	s32 sp74;
//	s32 numreapablewithpropflag80;
//	s32 numalive;
//	s32 s1len;
//	s32 s2len;
//	s32 i;
//	s32 time60;
//
//	var80062cb0 = 0;
//	var80062cb4 = 0;
//	var80062cb8 = 0;
//	numalivewithpropflag80 = 0;
//	var80062cbc = 0;
//
//	// 400
//	if (g_Vars.normmplayerisrunning == false) {
//		for (i = 0; i < numchrs; i++) {
//			struct chrdata *chr = &g_ChrSlots[i]; // s0
//
//			if (chr->model && chr->prop && chrIsDead(chr) == false) {
//				struct prop *targetprop = chrGetTargetProp(chr);
//
//				if (targetprop && (targetprop->type == PROPTYPE_CHR || targetprop->type == PROPTYPE_PLAYER)) {
//					if ((targetprop->type == PROPTYPE_PLAYER
//								&& !(g_Vars.antiplayernum >= 0 && g_Vars.anti && g_Vars.anti->prop == targetprop)
//								&& chrCompareTeams(chr, targetprop->chr, COMPARE_ENEMIES))
//							|| CHRRACE(targetprop->chr) == RACE_EYESPY) {
//						var80062cb0++;
//
//						if (chr->lastvisibletarget60 < chr->lastseetarget60) {
//							time60 = chr->lastseetarget60;
//						} else {
//							time60 = chr->lastvisibletarget60;
//						}
//
//						if (time60) {
//							var80062cb4++;
//
//							if (g_Vars.lvframe60 - time60 < 240) {
//								var80062cb8++;
//								var80062cbc++;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// 56c
//	var80068454++;
//
//	if (var80068454 > 10) {
//		var80068454 = 0;
//	}
//
//	if (debugDangerousProps()) {
//		propPrintDangerous();
//	}
//
//	if (g_Vars.autocutnum >= 0) {
//		cutsceneStart(g_Vars.autocutnum + 0xc00);
//		g_Vars.autocutnum = -1;
//		g_Vars.autocutplaying = true;
//	}
//
//	for (i = 0; i < g_NumBgChrs; i++) {
//		if (!g_Vars.autocutplaying || (g_BgChrs[i].hidden2 & CHRH2FLAG_TICKDURINGAUTOCUT)) {
//			chraTick(&g_BgChrs[i]);
//		}
//	}
//
//	// 634
//	numalive = 0;
//	s2len = 0;
//
//	for (i = 0; i < numchrs; i++) {
//		struct chrdata *chr = &g_ChrSlots[i];
//
//		// 664
//		if (chr->model && chr->prop) {
//			// 67c
//			if (chr->actiontype != ACT_DEAD && chr->actiontype != ACT_DRUGGEDKO) {
//				numalive++;
//			}
//
//			// 698
//			if (chr->prop->flags & PROPFLAG_ONANYSCREENPREVTICK) {
//				// 6a0
//				if (chr->actiontype != ACT_DEAD && chr->actiontype != ACT_DRUGGEDKO) {
//					numalivewithpropflag80++;
//				} else /*6bc*/ if (chr->actiontype == ACT_DRUGGEDKO) {
//					if ((chr->chrflags & CHRCFLAG_KEEPCORPSEKO) == 0) {
//						numreapablewithpropflag80++;
//					}
//				} else {
//					numreapablewithpropflag80++;
//				}
//			}
//
//			// 6e0
//			if (chr->actiontype == ACT_DEAD
//					|| (chr->actiontype == ACT_DRUGGEDKO && (chr->chrflags & CHRCFLAG_KEEPCORPSEKO) == 0)) {
//				if (chr->hidden2 & CHRH2FLAG_0080) {
//					sp7c[s2len] = chr;
//					s2len++;
//
//					if (s2len >= 10) {
//						writeindex = random() % s2len;
//						chrFadeCorpse(sp7c[writeindex]);
//						sp7c[writeindex] = sp7c[s2len - 1];
//						s2len--;
//					}
//				}
//			}
//		}
//	}
//
//	// 790
//	if (var80068458 < numalive) {
//		var80068458 = numalive;
//	}
//
//	// 7b4
//	sp74 = 5 - numalivewithpropflag80;
//
//	// 7c8
//	if (g_Vars.lvupdate240_60 > 6) {
//		sp74 = (sp74 - g_Vars.lvupdate240_60) + 6;
//	}
//
//	// 7dc
//	if (sp74 < 0) {
//		sp74 = 0;
//	}
//
//	// 7ec
//	if (numreapablewithpropflag80) {
//		numreapablewithpropflag80 = 0;
//		s1len = 0;
//		s2len = 0;
//
//		for (i = 0; i < numchrs; i++) {
//			struct chrdata *chr = &g_ChrSlots[i];
//
//			if (chr->model) {
//				if (chr->actiontype == ACT_DEAD
//						|| (chr->actiontype == ACT_DRUGGEDKO && chr->prop && (chr->chrflags & CHRCFLAG_KEEPCORPSEKO) == 0)) {
//					if (chr->prop->flags & PROPFLAG_ONANYSCREENPREVTICK) {
//						if (chr->act_dead.fadetimer60 < 0 && !chr->act_dead.fadenow) {
//							numreapablewithpropflag80++;
//
//							if (sp74 < numreapablewithpropflag80 || chr->aibot) {
//								chrFadeCorpse(chr);
//								numreapablewithpropflag80--;
//							} else {
//								if (chr->act_dead.fadewheninvis == 0) {
//									spb8[s1len] = chr;
//									s1len++;
//
//									if (s1len >= 2) {
//										writeindex = random() % s1len;
//
//
//										chrFadeCorpseWhenOffScreen(spb8[writeindex]);
//										spb8[writeindex] = spb8[s1len - 1];
//										s1len--;
//									}
//								}
//							}
//						}
//					} else {
//						// 938
//						if (chr->act_dead.fadewheninvis == 0) {
//							spa4[s2len] = chr;
//							s2len++;
//
//							if (s2len >= 5) {
//								writeindex = random() % s2len;
//
//								if (spa4[writeindex]->actiontype != ACT_DEAD);
//								if (spa4[writeindex]->actiontype != ACT_DEAD) {
//									chrBeginDead(spa4[writeindex]);
//								}
//
//								chrFadeCorpseWhenOffScreen(spa4[writeindex]);
//								spa4[writeindex] = spa4[s2len - 1];
//								s2len--;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}

bool chrSawTargetRecently(struct chrdata *chr)
{
	if (chr->lastseetarget60 > 0 && g_Vars.lvframe60 - chr->lastseetarget60 < PALDOWN(600)) {
		return true;
	}

	return false;
}

bool chrHeardTargetRecently(struct chrdata *chr)
{
	if (chr->lastheartarget60 > 0 && g_Vars.lvframe60 - chr->lastheartarget60 < PALDOWN(600)) {
		return true;
	}

	return false;
}

f32 chrGetAngleToPos(struct chrdata *chr, struct coord *pos)
{
	f32 fVar3;
	f32 fVar2;
	f32 fVar4;
	struct prop *prop;

	if (chr->prop->type == PROPTYPE_PLAYER) {
		u32 playernum = propGetPlayerNum(chr->prop);
		fVar3 = (360 - g_Vars.players[playernum]->vv_theta) * (M_BADTAU / 360);
	} else {
		fVar3 = chrGetInverseTheta(chr);
	}

	prop = chr->prop;
	fVar2 = atan2f(pos->x - prop->pos.x, pos->z - prop->pos.z);
	fVar4 = fVar2 - fVar3;

	if (fVar2 < fVar3) {
		fVar4 += M_BADTAU;
	}

	return fVar4;
}

f32 chrGetAngleToTarget(struct chrdata *chr)
{
	struct prop *prop = chrGetTargetProp(chr);
	return chrGetAngleToPos(chr, &prop->pos);
}

GLOBAL_ASM(
glabel chrGetAttackEntityPos
/*  f048b78:	27bdff80 */ 	addiu	$sp,$sp,-128
/*  f048b7c:	30ae0004 */ 	andi	$t6,$a1,0x4
/*  f048b80:	11c0001f */ 	beqz	$t6,.L0f048c00
/*  f048b84:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f048b88:	00c02825 */ 	or	$a1,$a2,$zero
/*  f048b8c:	afa40080 */ 	sw	$a0,0x80($sp)
/*  f048b90:	0fc126d1 */ 	jal	chrFindById
/*  f048b94:	afa7008c */ 	sw	$a3,0x8c($sp)
/*  f048b98:	8fa40080 */ 	lw	$a0,0x80($sp)
/*  f048b9c:	8fa7008c */ 	lw	$a3,0x8c($sp)
/*  f048ba0:	10400004 */ 	beqz	$v0,.L0f048bb4
/*  f048ba4:	00401825 */ 	or	$v1,$v0,$zero
/*  f048ba8:	8c4f001c */ 	lw	$t7,0x1c($v0)
/*  f048bac:	55e00003 */ 	bnezl	$t7,.L0f048bbc
/*  f048bb0:	8c78001c */ 	lw	$t8,0x1c($v1)
.L0f048bb4:
/*  f048bb4:	00801825 */ 	or	$v1,$a0,$zero
/*  f048bb8:	8c78001c */ 	lw	$t8,0x1c($v1)
.L0f048bbc:
/*  f048bbc:	c7040008 */ 	lwc1	$f4,0x8($t8)
/*  f048bc0:	e4e40000 */ 	swc1	$f4,0x0($a3)
/*  f048bc4:	8c79001c */ 	lw	$t9,0x1c($v1)
/*  f048bc8:	c726000c */ 	lwc1	$f6,0xc($t9)
/*  f048bcc:	e4e60004 */ 	swc1	$f6,0x4($a3)
/*  f048bd0:	8c68001c */ 	lw	$t0,0x1c($v1)
/*  f048bd4:	c5080010 */ 	lwc1	$f8,0x10($t0)
/*  f048bd8:	10600003 */ 	beqz	$v1,.L0f048be8
/*  f048bdc:	e4e80008 */ 	swc1	$f8,0x8($a3)
/*  f048be0:	10000002 */ 	b	.L0f048bec
/*  f048be4:	8c64001c */ 	lw	$a0,0x1c($v1)
.L0f048be8:
/*  f048be8:	8c64001c */ 	lw	$a0,0x1c($v1)
.L0f048bec:
/*  f048bec:	8fa50090 */ 	lw	$a1,0x90($sp)
/*  f048bf0:	0fc195e9 */ 	jal	roomsCopy
/*  f048bf4:	24840028 */ 	addiu	$a0,$a0,0x28
/*  f048bf8:	1000002e */ 	b	.L0f048cb4
/*  f048bfc:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f048c00:
/*  f048c00:	30a90008 */ 	andi	$t1,$a1,0x8
/*  f048c04:	11200014 */ 	beqz	$t1,.L0f048c58
/*  f048c08:	00c02825 */ 	or	$a1,$a2,$zero
/*  f048c0c:	0fc1258b */ 	jal	chrResolvePadId
/*  f048c10:	afa7008c */ 	sw	$a3,0x8c($sp)
/*  f048c14:	00402025 */ 	or	$a0,$v0,$zero
/*  f048c18:	24050042 */ 	addiu	$a1,$zero,0x42
/*  f048c1c:	0fc456ac */ 	jal	padUnpack
/*  f048c20:	27a60024 */ 	addiu	$a2,$sp,0x24
/*  f048c24:	8fa7008c */ 	lw	$a3,0x8c($sp)
/*  f048c28:	c7aa0024 */ 	lwc1	$f10,0x24($sp)
/*  f048c2c:	8fa50090 */ 	lw	$a1,0x90($sp)
/*  f048c30:	240bffff */ 	addiu	$t3,$zero,-1
/*  f048c34:	e4ea0000 */ 	swc1	$f10,0x0($a3)
/*  f048c38:	c7b00028 */ 	lwc1	$f16,0x28($sp)
/*  f048c3c:	e4f00004 */ 	swc1	$f16,0x4($a3)
/*  f048c40:	c7b2002c */ 	lwc1	$f18,0x2c($sp)
/*  f048c44:	e4f20008 */ 	swc1	$f18,0x8($a3)
/*  f048c48:	8faa006c */ 	lw	$t2,0x6c($sp)
/*  f048c4c:	a4ab0002 */ 	sh	$t3,0x2($a1)
/*  f048c50:	10000017 */ 	b	.L0f048cb0
/*  f048c54:	a4aa0000 */ 	sh	$t2,0x0($a1)
.L0f048c58:
/*  f048c58:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f048c5c:	afa7008c */ 	sw	$a3,0x8c($sp)
/*  f048c60:	8fa7008c */ 	lw	$a3,0x8c($sp)
/*  f048c64:	c4440008 */ 	lwc1	$f4,0x8($v0)
/*  f048c68:	24010003 */ 	addiu	$at,$zero,0x3
/*  f048c6c:	00403025 */ 	or	$a2,$v0,$zero
/*  f048c70:	e4e40000 */ 	swc1	$f4,0x0($a3)
/*  f048c74:	c446000c */ 	lwc1	$f6,0xc($v0)
/*  f048c78:	e4e60004 */ 	swc1	$f6,0x4($a3)
/*  f048c7c:	c4480010 */ 	lwc1	$f8,0x10($v0)
/*  f048c80:	e4e80008 */ 	swc1	$f8,0x8($a3)
/*  f048c84:	904c0000 */ 	lbu	$t4,0x0($v0)
/*  f048c88:	8fa50090 */ 	lw	$a1,0x90($sp)
/*  f048c8c:	15810006 */ 	bne	$t4,$at,.L0f048ca8
/*  f048c90:	00000000 */ 	nop
/*  f048c94:	8c430004 */ 	lw	$v1,0x4($v0)
/*  f048c98:	10600003 */ 	beqz	$v1,.L0f048ca8
/*  f048c9c:	00000000 */ 	nop
/*  f048ca0:	10000001 */ 	b	.L0f048ca8
/*  f048ca4:	00000000 */ 	nop
.L0f048ca8:
/*  f048ca8:	0fc195e9 */ 	jal	roomsCopy
/*  f048cac:	24c40028 */ 	addiu	$a0,$a2,0x28
.L0f048cb0:
/*  f048cb0:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f048cb4:
/*  f048cb4:	27bd0080 */ 	addiu	$sp,$sp,0x80
/*  f048cb8:	03e00008 */ 	jr	$ra
/*  f048cbc:	00000000 */ 	nop
);

// Mismatch: reallgoc for targetprop in first section
//void chrGetAttackEntityPos(struct chrdata *chr, u32 attackflags, s32 entityid, struct coord *pos, s16 *rooms)
//{
//	struct prop *targetprop;
//	struct chrdata *targetchr;
//	struct pad pad;
//
//	if (attackflags & ATTACKFLAG_AIMATCHR) {
//		// Aiming at a chr by chrnum
//		targetchr = chrFindById(chr, entityid);
//
//		if (!targetchr || !targetchr->prop) {
//			targetchr = chr;
//		}
//
//		chr = targetchr;
//
//		pos->x = chr->prop->pos.x;
//		pos->y = chr->prop->pos.y;
//		pos->z = chr->prop->pos.z;
//
//		if (targetchr) {
//			targetprop = targetchr->prop;
//		} else {
//			targetprop = chr->prop;
//		}
//
//		roomsCopy(targetprop->rooms, rooms);
//	} else if (attackflags & ATTACKFLAG_AIMATPAD) {
//		// Aiming at a pad by padnum
//		s32 padnum = chrResolvePadId(chr, entityid);
//		padUnpack(padnum, PADFIELD_POS | PADFIELD_ROOM, &pad);
//
//		pos->x = pad.pos.x;
//		pos->y = pad.pos.y;
//		pos->z = pad.pos.z;
//
//		rooms[0] = pad.room;
//		rooms[1] = -1;
//	} else {
//		// Aiming at the chr's preconfigured target
//		targetprop = chrGetTargetProp(chr);
//
//		pos->x = targetprop->pos.x;
//		pos->y = targetprop->pos.y;
//		pos->z = targetprop->pos.z;
//
//		if (targetprop->type == PROPTYPE_CHR && targetprop->chr) {
//			chr = targetprop->chr;
//		} else {
//			chr = NULL;
//		}
//
//		if (chr);
//
//		roomsCopy(targetprop->rooms, rooms);
//	}
//}

f32 chrGetAngleFromTargetsFov(struct chrdata *chr)
{
	f32 targetfacingangle = 0;
	struct prop *prop = chr->prop;
	struct prop *target = chrGetTargetProp(chr);
	f32 xdiff;
	f32 zdiff;
	f32 angletotarget;
	f32 result;

	if (prop && target) {
		xdiff = prop->pos.f[0] - target->pos.f[0];
		zdiff = prop->pos.f[2] - target->pos.f[2];
		angletotarget = atan2f(xdiff, zdiff);

		if (target->type == PROPTYPE_PLAYER) {
			s32 playernum = propGetPlayerNum(target);
			targetfacingangle = (360.0f - g_Vars.players[playernum]->vv_theta) * M_BADTAU / 360.0f;
		} else if (target->type == PROPTYPE_CHR) {
			targetfacingangle = chrGetInverseTheta(target->chr);
		}

		result = angletotarget - targetfacingangle;

		if (angletotarget < targetfacingangle) {
			result += M_BADTAU;
		}
	}

	return result;
}

f32 chrGetVerticalAngleToTarget(struct chrdata *chr)
{
	struct prop *prop = chr->prop;
	struct prop *target = chrGetTargetProp(chr);
	f32 result = 0;

	if (prop && target) {
		f32 ydiff;
		f32 xdiff;
		f32 zdiff;

		xdiff = prop->pos.x - target->pos.x;
		ydiff = prop->pos.y - target->pos.y;
		zdiff = prop->pos.z - target->pos.z;

		result = atan2f(ydiff, sqrtf(xdiff * xdiff + zdiff * zdiff));

		if (result < 0) {
			result += M_BADTAU;
		}
	}

	return result;
}

bool chrIsInTargetsFovX(struct chrdata *chr, u8 fov360)
{
	f32 angle = chrGetAngleFromTargetsFov(chr);

	if ((angle < fov360 * 0.024539785459638f && angle < M_PI)
			|| (angle > M_BADTAU - fov360 * 0.024539785459638f && angle > M_PI)) {
		return true;
	}

	return false;
}

bool chrIsVerticalAngleToTargetWithin(struct chrdata *chr, u8 fov360)
{
	f32 val = chrGetVerticalAngleToTarget(chr);

	if ((val < fov360 * 0.024539785459638f && val < M_PI)
			|| (val > M_BADTAU - fov360 * 0.024539785459638f && val > M_PI)) {
		return true;
	}

	return false;
}

f32 func0f048fcc(struct chrdata *chr, u8 reverse)
{
	f32 result;

	struct prop *chrprop = chr->prop;
	struct prop *targetprop = chrGetTargetProp(chr);

	f32 xdiff = chrprop->pos.x - targetprop->pos.x;
	f32 zdiff = chrprop->pos.z - targetprop->pos.z;

	f32 angle1 = atan2f(-xdiff, -zdiff);
	f32 angle2 = chrGetInverseTheta(chr) + M_PI * (s32)reverse;

	result = angle1 - angle2;

	if (angle1 < angle2) {
		result += M_BADTAU;
	}

	return result;
}

bool chrIsTargetInFov(struct chrdata *chr, u8 arg1, u8 reverse)
{
	f32 angle = func0f048fcc(chr, reverse);

	if ((angle < arg1 * 0.024539785459638f && angle < M_PI)
			|| (angle > M_BADTAU - arg1 * 0.024539785459638f && angle > M_PI)) {
		return true;
	}

	return false;
}

bool func0f04911c(struct chrdata *chr, struct coord *pos, u8 arg2)
{
	f32 angle = chrGetAngleToPos(chr, pos);

	if ((angle < arg2 * 0.024539785459638f && angle < M_PI) ||
			(M_BADTAU - arg2 * 0.024539785459638f < angle && M_PI < angle)) {
		return true;
	}

	return false;
}

f32 chrGetDistanceToTarget(struct chrdata *chr)
{
	struct prop *prop = chrGetTargetProp(chr);
	return propGetDistanceToProp(chr->prop, prop);
}

// Redundant function - it's the same as above
f32 chrGetDistanceToTarget2(struct chrdata *chr)
{
	struct prop *prop = chrGetTargetProp(chr);
	return propGetDistanceToProp(chr->prop, prop);
}

f32 chrGetDistanceToCurrentPlayer(struct chrdata *chr)
{
	return propGetDistanceToProp(chr->prop, g_Vars.currentplayer->prop);
}

f32 propGetDistanceToProp(struct prop *a, struct prop *b)
{
	f32 xdiff = a->pos.x - b->pos.x;
	f32 ydiff = a->pos.y - b->pos.y;
	f32 zdiff = a->pos.z - b->pos.z;

	return sqrtf(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
}

f32 propGetLateralDistanceToProp(struct prop *a, struct prop *b)
{
	f32 xdiff = a->pos.x - b->pos.x;
	f32 zdiff = a->pos.z - b->pos.z;

	return sqrtf(xdiff * xdiff + zdiff * zdiff);
}

f32 chrGetDistanceToPad(struct chrdata *chr, s32 pad_id)
{
	struct prop *prop = chr->prop;
	f32 xdiff, ydiff, zdiff;
	f32 distance = 0;
	struct pad pad;
	pad_id = chrResolvePadId(chr, pad_id);

#if VERSION >= VERSION_NTSC_1_0
	if (pad_id >= 0)
#endif
	{
		padUnpack(pad_id, PADFIELD_POS, &pad);
		xdiff = pad.pos.x - prop->pos.x;
		ydiff = pad.pos.y - prop->pos.y;
		zdiff = pad.pos.z - prop->pos.z;
		distance = sqrtf(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
	}

	return distance;
}

#if VERSION >= VERSION_NTSC_1_0
f32 chrGetSameFloorDistanceToPad(struct chrdata *chr, s32 pad_id)
{
	struct prop *prop = chr->prop;
	f32 xdiff, ydiff, zdiff, ydiff_absolute;
	struct pad pad;
	f32 ret;

	pad_id = chrResolvePadId(chr, pad_id);
	padUnpack(pad_id, PADFIELD_POS, &pad);
	xdiff = pad.pos.x - prop->pos.x;
	ydiff = pad.pos.y - prop->pos.y;
	zdiff = pad.pos.z - prop->pos.z;

	if (ydiff > 0) {
		ydiff_absolute = ydiff;
	} else {
		ydiff_absolute = -ydiff;
	}

	if (ydiff_absolute < 150) {
		ret = sqrtf(xdiff * xdiff + zdiff * zdiff);
	} else {
		ret = 100000000;
	}

	return ret;
}
#endif

f32 chrGetDistanceToCoord(struct chrdata *chr, struct coord *pos)
{
	f32 xdiff = pos->x - chr->prop->pos.x;
	f32 ydiff = pos->y - chr->prop->pos.y;
	f32 zdiff = pos->z - chr->prop->pos.z;

	return sqrtf(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
}

f32 chrGetLateralDistanceToCoord(struct chrdata *chr, struct coord *pos)
{
	f32 xdiff = pos->x - chr->prop->pos.x;
	f32 zdiff = pos->z - chr->prop->pos.z;

	return sqrtf(xdiff * xdiff + zdiff * zdiff);
}

f32 chrGetLateralDistanceToPad(struct chrdata *chr, s32 pad_id)
{
	struct prop *prop = chr->prop;
	f32 xdiff, zdiff;
	struct pad pad;

#if VERSION >= VERSION_NTSC_1_0
	f32 distance = 0;

	pad_id = chrResolvePadId(chr, pad_id);

	if (pad_id >= 0) {
		padUnpack(pad_id, PADFIELD_POS, &pad);
		xdiff = pad.pos.x - prop->pos.x;
		zdiff = pad.pos.z - prop->pos.z;
		distance = sqrtf(xdiff * xdiff + zdiff * zdiff);
	}

	return distance;
#else
	pad_id = chrResolvePadId(chr, pad_id);
	padUnpack(pad_id, PADFIELD_POS, &pad);
	xdiff = pad.pos.x - prop->pos.x;
	zdiff = pad.pos.z - prop->pos.z;
	return sqrtf(xdiff * xdiff + zdiff * zdiff);
#endif
}

f32 chrGetSquaredDistanceToCoord(struct chrdata *chr, struct coord *pos)
{
	f32 xdiff = pos->x - chr->prop->pos.x;
	f32 ydiff = pos->y - chr->prop->pos.y;
	f32 zdiff = pos->z - chr->prop->pos.z;

	return xdiff * xdiff + ydiff * ydiff + zdiff * zdiff;
}

f32 coordGetSquaredDistanceToCoord(struct coord *a, struct coord *b)
{
	f32 xdiff = a->x - b->x;
	f32 ydiff = a->y - b->y;
	f32 zdiff = a->z - b->z;

	return xdiff * xdiff + ydiff * ydiff + zdiff * zdiff;
}

s32 chrGetPadRoom(struct chrdata *chr, s32 pad_id)
{
	s32 ret = -1;
	s32 pad_id_backup = pad_id;
	struct pad pad;

	if (pad_id >= 10000) {
		s32 resolved_pad_id = chrResolvePadId(chr, pad_id - 10000);

#if VERSION >= VERSION_NTSC_1_0
		if (resolved_pad_id >= 0)
#endif
		{
			padUnpack(resolved_pad_id, PADFIELD_ROOM, &pad);
			ret = pad.room;
		}
	} else {
		ret = pad_id;
	}

	return ret;
}

s32 chrResolvePadId(struct chrdata *chr, s32 pad_id)
{
	if (pad_id == 9000) {
		pad_id = chr->padpreset1;
	}

	return pad_id;
}

/**
 * For all chrs, clear their target and p1p2 values if set to the given player.
 *
 * This function is called when the given player has died. It causes all guards
 * to switch their focus to the remaining coop player.
 */
void chrsClearRefsToPlayer(s32 playernum)
{
	s32 otherplayernum;
	s32 playerpropnum;
	s32 i;

	if (g_Vars.coopplayernum >= 0) {
		if (playernum == g_Vars.bondplayernum) {
			otherplayernum = g_Vars.coopplayernum;
			playerpropnum = g_Vars.bond->prop - g_Vars.props;
		} else {
			otherplayernum = g_Vars.bondplayernum;
			playerpropnum = g_Vars.coop->prop - g_Vars.props;
		}

		for (i = 0; i < chrsGetNumSlots(); i++) {
			if (g_ChrSlots[i].p1p2 == playernum) {
				g_ChrSlots[i].p1p2 = otherplayernum;
			}

			if (g_ChrSlots[i].target == playerpropnum) {
				g_ChrSlots[i].target = -1;
			}
		}

		for (i = 0; i < g_NumBgChrs; i++) {
			if (g_BgChrs[i].p1p2 == playernum) {
				g_BgChrs[i].p1p2 = otherplayernum;
			}

			if (g_BgChrs[i].target == playerpropnum) {
				g_BgChrs[i].target = -1;
			}
		}
	}
}

s32 chrResolveId(struct chrdata *ref, s32 id)
{
	if (ref) {
		switch (id) {
		case CHR_SEESHOT:
			id = ref->chrseeshot;
			break;
		case CHR_SEEDIE:
			id = ref->chrseedie;
			break;
		case CHR_PRESET:
			id = ref->chrpreset1;
			break;
		case CHR_SELF:
			id = ref->chrnum;
			break;
		case CHR_CLONE:
			id = ref->chrdup;
			break;
		case CHR_BOND:
			if (g_Vars.bond && g_Vars.bond->prop && g_Vars.bond->prop->chr) {
				id = g_Vars.bond->prop->chr->chrnum;
			}
			break;
		case CHR_COOP:
			if (g_Vars.coop && g_Vars.coop->prop && g_Vars.coop->prop->chr) {
				id = g_Vars.coop->prop->chr->chrnum;
			}
			break;
		case CHR_ANTI:
			if (g_Vars.anti && g_Vars.anti->prop && g_Vars.anti->prop->chr) {
				id = g_Vars.anti->prop->chr->chrnum;
			}
			break;
		case CHR_P1P2:
			{
				u32 index = g_Vars.coopplayernum >= 0 ? ref->p1p2 : g_Vars.bondplayernum;
				struct player *player = g_Vars.players[index];
				if (player && player->prop && player->prop->chr) {
					id = player->prop->chr->chrnum;
				}
			}
			break;
		case CHR_P1P2_OPPOSITE:
			if (g_Vars.coopplayernum >= 0) {
				struct player *player = g_Vars.players[1 - ref->p1p2];
				if (player && player->prop && player->prop->chr) {
					id = player->prop->chr->chrnum;
				}
			}
			break;
		case CHR_TARGET:
			{
				struct prop *target = chrGetTargetProp(ref);
				if ((target->type == PROPTYPE_CHR || target->type == PROPTYPE_PLAYER) && target->chr) {
					id = target->chr->chrnum;
				}
			}
			break;
		}
	} else { // ref is NULL
		switch (id) {
		case CHR_BOND:
			if (g_Vars.bond && g_Vars.bond->prop && g_Vars.bond->prop->chr) {
				id = g_Vars.bond->prop->chr->chrnum;
			}
			break;
		case CHR_COOP:
			if (g_Vars.coop && g_Vars.coop->prop && g_Vars.coop->prop->chr) {
				id = g_Vars.coop->prop->chr->chrnum;
			}
			break;
		case CHR_ANTI:
			if (g_Vars.anti && g_Vars.anti->prop && g_Vars.anti->prop->chr) {
				id = g_Vars.anti->prop->chr->chrnum;
			}
			break;
		case CHR_P1P2:
			{
				struct player *player = g_Vars.players[g_Vars.bondplayernum];
				if (player && player->prop && player->prop->chr) {
					id = player->prop->chr->chrnum;
				}
			}
			break;
		case CHR_P1P2_OPPOSITE:
			if (g_Vars.coopplayernum >= 0) {
				struct player *player = g_Vars.players[g_Vars.coopplayernum];
				if (player && player->prop && player->prop->chr) {
					id = player->prop->chr->chrnum;
				}
			}
			break;
		}
	}

	return id;
}

struct chrdata *chrFindById(struct chrdata *basechr, s32 chrnum)
{
	struct chrdata *chr;
	s32 lower;
	s32 upper;
	s32 i;

	chrnum = chrResolveId(basechr, chrnum);
	chr = chrFindByLiteralId(chrnum);

	if (chr) {
		return chr;
	}

	lower = 0;
	upper = g_NumBgChrs;

	while (upper >= lower) {
		i = (lower + upper) / 2;

		if (chrnum == g_BgChrnums[i]) {
			return &g_BgChrs[i];
		}

		if (chrnum < g_BgChrnums[i]) {
			upper = i - 1;
		} else {
			lower = i + 1;
		}
	}

	return NULL;
}

s32 propGetIndexByChrId(struct chrdata *basechr, s32 chrnum)
{
	s32 index;

	if (chrnum == CHR_BOND || chrnum == CHR_BOND) {
		index = g_Vars.bond->prop - g_Vars.props;
	} else {
		struct chrdata *chr = chrFindById(basechr, chrnum);

		if (chr && chr->prop) {
			index = chr->prop - g_Vars.props;
		} else {
			index = -1;
		}
	}

	return index;
}

f32 chrGetDistanceToChr(struct chrdata *chr1, s32 chr2num)
{
	struct prop *prop1 = chr1->prop;
	struct chrdata *chr2 = chrFindById(chr1, chr2num);
	f32 distance = 0;

	if (chr2 && chr2->prop) {
		f32 xdiff = chr2->prop->pos.x - prop1->pos.x;
		f32 ydiff = chr2->prop->pos.y - prop1->pos.y;
		f32 zdiff = chr2->prop->pos.z - prop1->pos.z;
		distance = sqrtf(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
	}

	return distance;
}

f32 chrGetDistanceFromTargetToPad(struct chrdata *chr, s32 pad_id)
{
	struct prop *prop = chrGetTargetProp(chr);
	f32 xdiff, ydiff, zdiff;
	struct pad pad;
	f32 distance = 0;
	pad_id = chrResolvePadId(chr, pad_id);

#if VERSION >= VERSION_NTSC_1_0
	if (pad_id >= 0)
#endif
	{
		padUnpack(pad_id, PADFIELD_POS, &pad);
		xdiff = pad.pos.x - prop->pos.x;
		ydiff = pad.pos.y - prop->pos.y;
		zdiff = pad.pos.z - prop->pos.z;
		distance = sqrtf(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
	}

	return distance;
}

void chrSetFlags(struct chrdata *chr, u32 flags, u8 bank)
{
	if (bank == 0) {
		chr->flags |= flags;
	} else {
		chr->flags2 |= flags;
	}
}

void chrUnsetFlags(struct chrdata *chr, u32 flags, u8 bank)
{
	if (bank == 0) {
		chr->flags &= ~flags;
	} else {
		chr->flags2 &= ~flags;
	}
}

bool chrHasFlag(struct chrdata *chr, u32 flag, u8 bank)
{
	if (bank == 0) {
		return (chr->flags & flag) != 0;
	} else {
		return (chr->flags2 & flag) != 0;
	}
}

void chrSetFlagsById(struct chrdata *ref, u32 chrnum, u32 flags, u32 bank)
{
	struct chrdata *chr = chrFindById(ref, chrnum);

	if (chr) {
		chrSetFlags(chr, flags, bank);
	}
}

void chrUnsetFlagsById(struct chrdata *ref, u32 chrnum, u32 flags, u32 bank)
{
	struct chrdata *chr = chrFindById(ref, chrnum);

	if (chr) {
		chrUnsetFlags(chr, flags, bank);
	}
}

bool chrHasFlagById(struct chrdata *ref, u32 chrnum, u32 flag, u32 bank)
{
	struct chrdata *chr = chrFindById(ref, chrnum);

	if (chr) {
		return chrHasFlag(chr, flag, bank);
	}

	return false;
}

void chrSetStageFlag(struct chrdata *chr, u32 flag)
{
	g_StageFlags |= flag;
}

void chrUnsetStageFlag(struct chrdata *chr, u32 flag)
{
	g_StageFlags = g_StageFlags & ~flag;
}

bool chrHasStageFlag(struct chrdata *chr, u32 flag)
{
	return (g_StageFlags & flag) != 0;
}

bool chrIsHearingTarget(struct chrdata *chr)
{
	return (chr->hidden & CHRHFLAG_IS_HEARING_TARGET) != 0;
}

void chrRestartTimer(struct chrdata *chr)
{
	chr->timer60 = 0;
	chr->hidden |= CHRHFLAG_TIMER_RUNNING;
}

f32 chrGetTimer(struct chrdata *chr)
{
	return chr->timer60 * FRAMEDURATION;
}

bool chrCanSeeTargetWithExtraCheck(struct chrdata *chr)
{
	struct prop *target = chrGetTargetProp(chr);

	if (target) {
		if (target->type == PROPTYPE_CHR) {
			if (!chrCanSeeTarget(chr)) {
				return false;
			}

			return chrIsInTargetsFovX(chr, 20);
		}

		if (target->type == PROPTYPE_PLAYER) {
			if (g_Vars.bondvisible &&
					(cdHasLineOfSight(&target->pos, target->rooms, &chr->prop->pos, chr->prop->rooms, 51, 8))) {
				struct model *model = chr->model;
				struct coord sp68;
				struct coord sp56;
				struct coord sp44;
				f32 somefloat = model0001af80(model) * 0.8f;

				bgun0f0a0c08(&sp68, &sp56);
				modelGetRootPosition(model, &sp44);
				mtx4TransformVecInPlace(currentPlayerGetMatrix1740(), &sp44);

				if (func0f06b39c(&sp68, &sp56, &sp44, somefloat)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool chrResetNearMiss(struct chrdata *chr)
{
	bool has_flag = (chr->chrflags & CHRCFLAG_NEAR_MISS) != 0;
	chr->chrflags &= ~CHRCFLAG_NEAR_MISS;

	return has_flag;
}

s32 chrGetNumArghs(struct chrdata *chr)
{
	return chr->numarghs;
}

s32 chrGetNumCloseArghs(struct chrdata *chr)
{
	return chr->numclosearghs;
}

bool chrSawInjury(struct chrdata *chr, u8 arg1)
{
	bool saw_injury = chr->chrseeshot >= 0;

	if (saw_injury && arg1 == 0) {
		chr->chrseeshot = -1;
	} else if (saw_injury && arg1 == 1) {
		struct chrdata *victim = chrFindById(chr, chr->chrseeshot);

		if (victim && !chrCompareTeams(chr, victim, COMPARE_FRIENDS)) {
			saw_injury = false;
		}
	} else {
		chr->chrseeshot = -1;
	}

	return saw_injury;
}

bool chrSawDeath(struct chrdata *chr, u8 arg1)
{
	bool saw_death = chr->chrseedie >= 0;

	// The commented line below was likely originally there but removed before
	// the final version. Compare with chrSawInjury above.
	if (saw_death && arg1 == 0) {
		//chr->chrseedie = -1;
	} else if (saw_death && arg1 == 1) {
		struct chrdata *victim = chrFindById(chr, chr->chrseedie);

		if (victim && !chrCompareTeams(chr, victim, COMPARE_FRIENDS)) {
			saw_death = false;
			chr->chrseedie = -1;
		}
	} else {
		chr->chrseedie = -1;
	}

	return saw_death;
}

void decrementByte(u8 *dst, u8 amount)
{
	if (*dst < amount) {
		*dst = 0;
		return;
	}

	*dst -= amount;
}

void incrementByte(u8 *dst, u8 amount)
{
	if (0xff - amount < *dst) {
		*dst = 0xff;
		return;
	}

	*dst += amount;
}

bool chrCanHearAlarm(struct chrdata *chr)
{
	return alarmIsActive();
}

bool waypointIsWithin90DegreesOfPosAngle(struct waypoint *waypoint, struct coord *pos, f32 angle)
{
	u32 stack[3];
	f32 diffangle;
	struct pad pad;

	padUnpack(waypoint->padnum, PADFIELD_POS, &pad);

	diffangle = angle - atan2f(pad.pos.x - pos->x, pad.pos.z - pos->z);

	if (diffangle < 0) {
		diffangle += M_BADTAU;
	}

	if (diffangle < 1.5705462694168f || diffangle > 4.7116389274597f) {
		return true;
	}

	return false;
}

/**
 * Attempt to find a waypoint near pos which is in a particular quadrant to pos,
 * then return its padnum.
 *
 * For example, pos is typically the player's position, angle is the direction
 * the player is facing, and quadrant is which quadrant (front/back/left/right)
 * that is desired relative to the player's position and angle.
 *
 * The function starts by finding the closest waypoint to the pos. If it's not
 * in the quadrant then its neighouring waypoints are checked too. If none of
 * those are in the quadrant then no further checks are made and the function
 * returns -1.
 */
s32 chrFindWaypointWithinPosQuadrant(struct coord *pos, s16 *rooms, f32 angle, u8 quadrant)
{
	struct waypoint *waypoint = waypointFindClosestToPos(pos, rooms);
	s32 neighbournum;
	s32 i;

	if (waypoint) {
		switch (quadrant) {
		case QUADRANT_BACK:
			angle += M_BADPI;
			break;
		case QUADRANT_SIDE1:
			angle += 1.5705462694168f;
			break;
		case QUADRANT_SIDE2:
			angle += 4.7116389274597f;
			break;
		case QUADRANT_FRONT:
			break;
		}

		if (angle >= M_BADTAU) {
			angle -= M_BADTAU;
		}

		if (waypointIsWithin90DegreesOfPosAngle(waypoint, pos, angle)) {
			return waypoint->padnum;
		}

		for (i = 0; (neighbournum = waypoint->neighbours[i]) >= 0; i++) {
			if ((neighbournum & 0x8000) == 0) {
				neighbournum &= 0x3fff;

				if (waypointIsWithin90DegreesOfPosAngle(&g_StageSetup.waypoints[neighbournum], pos, angle)) {
					return g_StageSetup.waypoints[neighbournum].padnum;
				}
			}

		}
	}

	return -1;
}

bool func0f04a4ec(struct chrdata *chr, u8 quadrant)
{
	if (quadrant == QUADRANT_2NDWPTOTARGET || quadrant == QUADRANT_20) {
		struct prop *prop = chr->prop;
		struct prop *target = chrGetTargetProp(chr);

		struct waypoint *fromwp = waypointFindClosestToPos(&prop->pos, prop->rooms);
		struct waypoint *towp = waypointFindClosestToPos(&target->pos, target->rooms);

		// @dangerous: I'm creating an array overflow here to get a match.
		// waypoints should have len 3 but this causes a mismatch due to too
		// much stack usage. If compiling using anything other than IDO and -O2
		// then this will need to be changed to 3.
		s32 numwaypoints;
		struct waypoint *waypoints[2];
		u32 hash;

		if (fromwp && towp) {
			if (quadrant == QUADRANT_2NDWPTOTARGET) {
				hash = (g_Vars.lvframe60 >> 9) * 128 + chr->chrnum * 8;

				waypointSetHashThing(hash, hash);
				numwaypoints = waypointFindRoute(fromwp, towp, waypoints, 3);
				waypointSetHashThing(0, 0);

				if (numwaypoints >= 3) {
					chr->padpreset1 = waypoints[1]->padnum;
					return true;
				}
			} else {
				hash = (g_Vars.lvframe60 >> 9) * 128 + chr->chrnum * 8;

				waypointSetHashThing(hash, hash);
				fromwp = func0f1155e0(fromwp, towp);
				waypointSetHashThing(0, 0);

				if (fromwp) {
					chr->padpreset1 = fromwp->padnum;
					return true;
				}
			}
		}
	} else {
		s32 padnum = chrFindWaypointWithinPosQuadrant(&chr->prop->pos, chr->prop->rooms, chrGetInverseTheta(chr), quadrant);

		if (padnum >= 0) {
			chr->padpreset1 = padnum;
			return true;
		}
	}

	return false;
}

bool chrSetPadPresetToWaypointWithinTargetQuadrant(struct chrdata *chr, u8 quadrant)
{
	f32 angle;
	s32 padnum;
	struct prop *prop;

	if (quadrant == QUADRANT_2NDWPTOTARGET || quadrant == QUADRANT_20) {
		return func0f04a4ec(chr, quadrant);
	}

	angle = 0;
	prop = chrGetTargetProp(chr);

	if (prop->type == PROPTYPE_PLAYER) {
		angle = (360.0f - g_Vars.players[propGetPlayerNum(prop)]->vv_theta) * M_BADTAU / 360.0f;
	} else if (prop->type == PROPTYPE_CHR) {
		angle = chrGetInverseTheta(prop->chr);
	}

	padnum = chrFindWaypointWithinPosQuadrant(&prop->pos, prop->rooms, angle, quadrant);

	if (padnum >= 0) {
		chr->padpreset1 = padnum;
		return true;
	}

	return false;
}

bool chrSetChrPresetToAnyChrNearSelf(struct chrdata *chr, f32 distance)
{
	return chrSetChrPresetToChrNearSelf(COMPARE_ANY, chr, distance);
}

bool chrSetChrPresetToChrNearSelf(u8 checktype, struct chrdata *chr, f32 distance)
{
	return chrSetChrPresetToChrNearPos(checktype, chr, distance, &chr->prop->pos, chr->prop->rooms);
}

bool chrSetChrPresetToChrNearPad(u32 checktype, struct chrdata *chr, f32 distance, s32 padnum)
{
	struct pad pad;
	s16 rooms[2];

	padnum = chrResolvePadId(chr, padnum);
	padUnpack(padnum, PADFIELD_POS | PADFIELD_ROOM, &pad);

	rooms[0] = pad.room;
	rooms[1] = -1;

	return chrSetChrPresetToChrNearPos(checktype, chr, distance, &pad.pos, rooms);
}

bool chrSetChrPresetToChrNearPos(u8 checktype, struct chrdata *chr, f32 distance, struct coord *pos, s16 *rooms)
{
	s32 i;
	s16 *propnumptr;
	s16 propnums[256];
	s16 allrooms[21];
	f32 xmin = pos->x - distance;
	f32 xmax = pos->x + distance;
	f32 ymin = pos->y - distance;
	f32 ymax = pos->y + distance;
	f32 zmin = pos->z - distance;
	f32 zmax = pos->z + distance;
	s16 neighbours[11];

	roomsCopy(rooms, allrooms);

	for (i = 0; rooms[i] != -1; i++) {
		roomGetNeighbours(rooms[i], neighbours, 10);
		roomsAppend(neighbours, allrooms, 20);
	}

	roomGetProps(allrooms, propnums, 256);

	propnumptr = propnums;

	while (*propnumptr >= 0) {
		struct prop *prop = &g_Vars.props[*propnumptr];

		if (prop->type == PROPTYPE_CHR || prop->type == PROPTYPE_PLAYER) {
			struct chrdata *loopchr = prop->chr;

			if (loopchr->chrnum != chr->chrnum
					&& !chrIsDead(loopchr)
					&& prop->pos.x >= xmin
					&& prop->pos.x <= xmax
					&& prop->pos.y >= ymin
					&& prop->pos.y <= ymax
					&& prop->pos.z >= zmin
					&& prop->pos.z <= zmax
					&& chrCompareTeams(loopchr, chr, checktype)) {
				chr->chrpreset1 = loopchr->chrnum;
				return true;
			}
		}

		*propnumptr++;
	}

	return false;
}

bool chrCompareTeams(struct chrdata *chr1, struct chrdata *chr2, u8 checktype)
{
	if (chr1 && chr1->prop) {
		if (checktype == COMPARE_ANY) {
			return true;
		}

		if (checktype == COMPARE_FRIENDS) { // Return true if chrs are friends
			if (g_Vars.normmplayerisrunning) {
				if ((g_MpSetup.options & MPOPTION_TEAMSENABLED) && chr2->team == chr1->team) {
					return true;
				}
			} else {
				if (g_Vars.bond && g_Vars.bond->prop) {
					struct chrdata *playerchr = g_Vars.bond->prop->chr;

					// @bug: This makes Jon an ally in Duel
					if ((chr2 == playerchr && chr1->headnum == HEAD_JONATHAN) ||
							(chr1 == playerchr && chr2->headnum == HEAD_JONATHAN)) {
						return true;
					}
				}

				if ((chr2->team & chr1->team) != 0) {
					return true;
				}
			}
		} else if (checktype == COMPARE_ENEMIES) { // Return true if chrs are enemies
			if (g_Vars.normmplayerisrunning) {
				if ((g_MpSetup.options & MPOPTION_TEAMSENABLED) == 0 || chr2->team != chr1->team) {
					return true;
				}
			} else {
				if (g_Vars.bond && g_Vars.bond->prop) {
					struct chrdata *playerchr = g_Vars.bond->prop->chr;

					// @bug: This makes Jon an ally in Duel
					if ((chr2 == playerchr && chr1->headnum == HEAD_JONATHAN) ||
							(chr1 == playerchr && chr2->headnum == HEAD_JONATHAN)) {
						return false;
					}
				}

				if ((chr2->team & chr1->team) == 0) {
					return true;
				}
			}
		}

		return false;
	}

	return false;
}

void chrSetChrPreset(struct chrdata *chr, s32 chrpreset)
{
	chr->chrpreset1 = chrResolveId(chr, chrpreset);
}

void chrSetChrPresetByChrnum(struct chrdata *basechr, s32 chrnum, s32 chrpreset)
{
	struct chrdata *chr = chrFindById(basechr, chrnum);

	if (chr) {
		chr->chrpreset1 = chrResolveId(basechr, chrpreset);
	}
}

void chrSetPadPreset(struct chrdata *chr, s32 pad_id)
{
	chr->padpreset1 = chrResolvePadId(chr, pad_id);
}

void chrSetPadPresetByChrnum(struct chrdata *basechr, s32 chrnum, s32 pad_id)
{
	struct chrdata *chr = chrFindById(basechr, chrnum);

	if (chr) {
		chr->padpreset1 = chrResolvePadId(basechr, pad_id);
	}
}

/**
 * Check if chr has line of sight (I think?) to their target. If so, find a
 * route to them, then iterate the route backwards (from target to chr). Find
 * the first waypoint with line of sight and store it as the chr's pad preset.
 */
bool chrSetPadPresetToPadOnRouteToTarget(struct chrdata *chr)
{
	struct prop *target = chrGetTargetProp(chr);
	struct prop *prop = chr->prop;
	struct waypoint *fromwp;
	struct waypoint *towp;
	struct waypoint *waypoints[5];
	s32 numwaypoints;
	s32 i;
	struct pad pad;

	if (target->type != PROPTYPE_PLAYER || g_Vars.bondvisible) {
		if (cd0002dc18(&prop->pos, prop->rooms, &target->pos, CDTYPE_BG)) {
			return false;
		}

		fromwp = waypointFindClosestToPos(&prop->pos, prop->rooms);
		towp = waypointFindClosestToPos(&target->pos, target->rooms);

		if (fromwp && towp) {
			u32 hash = (g_Vars.lvframe60 >> 9) * 128 + chr->chrnum * 8;

			// Note from/to are swapped here, so the route is from target to chr
			waypointSetHashThing(hash, hash);
			numwaypoints = waypointFindRoute(towp, fromwp, waypoints, 5);
			waypointSetHashThing(0, 0);

			if (numwaypoints >= 3) {
				for (i = 0; waypoints[i] != NULL; i++) {
					struct waypoint *wp = waypoints[i];

					padUnpack(wp->padnum, PADFIELD_POS, &pad);

					if (cd0002dc18(&target->pos, target->rooms, &pad.pos, CDTYPE_BG)) {
						if (cd0002dc18(&prop->pos, prop->rooms, &pad.pos, CDTYPE_BG)) {
							chr->padpreset1 = wp->padnum;
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool func0f04aeb0(struct coord *pos, s16 *rooms)
{
	bool result = true;
	s32 i;

	if (func0f1666f8(pos, 0)) {
		for (i = 0; rooms[i] != -1; i++) {
			if (roomIsVisibleByAnyPlayer(rooms[i])) {
				break;
			}
		}

		if (rooms[i] != -1) {
			// Room is visible by player
			result = !func0f0b5d38(pos, 200, func0f158140(rooms[i]));
		}
	}

	return result;
}

/**
 * Test if a chr can be spawned into or nearby the given position, taking into
 * consideration collision checks.
 *
 * If the spawn can happen, the position and rooms are updated with the actual
 * position to be used and the function returns true.
 *
 * If the spawn cannot happen, the function return false.
 */
#if VERSION >= VERSION_NTSC_1_0
bool chrAdjustPosForSpawn(f32 width, struct coord *pos, s16 *rooms, f32 angle, bool arg4, bool ignorebg, bool arg6)
{
	struct coord testpos;
	s32 i;
	u32 types;
	s16 testrooms[8];
	f32 ymin;
	f32 ymax = 200;
	f32 curangle = angle;
	f32 ground;

	if (ignorebg) {
		types = CDTYPE_ALL & ~CDTYPE_BG;
		arg4 = true;
	} else {
		types = CDTYPE_ALL;
	}

	if (arg6) {
		// Skip testing the given pos, and just do the surrounding checks below.
		// Add 45 degrees to the angle here, but this isn't necessary.
		curangle += 0.7852731347084f;

		if (curangle >= M_BADTAU) {
			curangle -= M_BADTAU;
		}
	} else {
		// Check that the chr isn't being spawned out of bounds, and do a volume
		// test reaching 200cm above and below the chr's feet... unless there is
		// ground under the chr (highly likely), in which case reduce the volume
		// to be tested to the ground Y value. I'm not sure why this is useful,
		// because if the chr was being spawned on top of another chr or object
		// then the calculated ground value would be raised.
		ymin = -200;
		ground = cdFindGroundYSimple(pos, width, rooms, NULL, NULL);

		if (ground > -100000 && ground - pos->y < -200) {
			ymin = ground - pos->y;
		}

		if (cdTestVolume(pos, width, rooms, types, 1, ymax, ymin) != CDRESULT_COLLISION
				&& (arg4 || func0f04aeb0(pos, rooms))) {
			return true;
		}
	}

	// Try 60cm in 8 directions
	for (i = 0; i < 8; i++) {
		testpos.x = pos->x + sinf(curangle) * 60;
		testpos.y = pos->y;
		testpos.z = pos->z + cosf(curangle) * 60;

		if ((arg6 && cd0002d840(pos, rooms, &testpos, testrooms, CDTYPE_ALL & ~CDTYPE_PLAYERS, 1, ymax, -200) != CDRESULT_COLLISION)
				|| (!arg6 && cd0002deac(pos, rooms, &testpos, testrooms, CDTYPE_BG))) {
			chr0f021fa8(NULL, &testpos, testrooms);
			ground = cdFindGroundYSimple(&testpos, width, testrooms, 0, 0);
			ymin = -200;

			if (ground > -100000 && ground - pos->y < -200) {
				ymin = ground - pos->y;
			}

			if (cdTestVolume(&testpos, width, testrooms, CDTYPE_ALL, 1, ymax, ymin) != CDRESULT_COLLISION
					&& (arg4 || func0f04aeb0(&testpos, testrooms))
					&& (!arg6 || ground > -100000)) {
				pos->x = testpos.x;
				pos->y = testpos.y;
				pos->z = testpos.z;
				roomsCopy(testrooms, rooms);
				return true;
			}
		}

		curangle += 0.7852731347084f;

		if (curangle >= M_BADTAU) {
			curangle -= M_BADTAU;
		}
	}

	return false;
}
#else
/**
 * ntsc-beta's version of this function doesn't have the arg6 argument
 * nor out of bounds checking, and lacks the reduction for the volume test.
 */
bool chrAdjustPosForSpawn(f32 width, struct coord *pos, s16 *rooms, f32 angle, bool arg4, bool ignorebg)
{
	struct coord testpos;
	s32 i;
	u32 types;
	s16 testrooms[8];
	f32 curangle = angle;

	if (ignorebg) {
		types = CDTYPE_ALL & ~CDTYPE_BG;
		arg4 = true;
	} else {
		types = CDTYPE_ALL;
	}

	if (cdTestVolume(pos, width, rooms, types, 1, 200, -200) != CDRESULT_COLLISION
			&& (arg4 || func0f04aeb0(pos, rooms))) {
		return true;
	}

	for (i = 0; i < 8; i++) {
		testpos.x = sinf(curangle) * 60 + pos->x;
		testpos.y = pos->y;
		testpos.z = cosf(curangle) * 60 + pos->z;

		if (cd0002deac(pos, rooms, &testpos, testrooms, CDTYPE_BG)
				&& cdTestVolume(&testpos, width, testrooms, CDTYPE_ALL, 1, 200, -200.0f) != CDRESULT_COLLISION
				&& (arg4 || func0f04aeb0(&testpos, testrooms))) {
			pos->x = testpos.x;
			pos->y = testpos.y;
			pos->z = testpos.z;
			roomsCopy(testrooms, rooms);
			return true;
		}

		curangle += 0.7852731347084f;

		if (curangle >= M_BADTAU) {
			curangle -= M_BADTAU;
		}
	}

	return false;
}
#endif

/**
 * Attempts to spawn a chr at the given coordinates.
 *
 * In low memory conditions, the function will iterate all existing chrs in
 * search of a corpse that can be reaped. If one is found then the reap will be
 * triggered, but the function will not attempt to spawn the chr until the next
 * time it's called.
 */
struct prop *chrSpawnAtCoord(s32 bodynum, s32 headnum, struct coord *pos, s16 *rooms, f32 angle, u8 *ailist, u32 spawnflags)
{
	struct prop *prop;
	struct coord pos2;
	s16 rooms2[8];
	s32 stack;

	if (chrsGetNumFree() > 1) {
		if (headnum < 0) {
			headnum = bodyChooseHead(bodynum);
		}

		pos2.x = pos->x;
		pos2.y = pos->y;
		pos2.z = pos->z;
		roomsCopy(rooms, rooms2);

#if VERSION >= VERSION_NTSC_1_0
		if (chrAdjustPosForSpawn(20, &pos2, rooms2, angle, (spawnflags & SPAWNFLAG_00000010) != 0, 0, 0))
#else
		if (chrAdjustPosForSpawn(20, &pos2, rooms2, angle, (spawnflags & SPAWNFLAG_00000010) != 0, 0))
#endif
		{
			struct model *model = modelAllocateChr(bodynum, headnum, spawnflags);
			struct chrdata *chr;

			if (model) {
				prop = chrAllocate(model, &pos2, rooms2, angle, ailist);

				if (prop) {
					propActivateThisFrame(prop);
					propEnable(prop);

					chr = prop->chr;
					chr->headnum = headnum;
					chr->bodynum = bodynum;
					chr->race = bodyGetRace(chr->bodynum);
					chr->flags = 0;
					chr->flags2 = 0;
#if VERSION >= VERSION_NTSC_1_0
					chr->hidden2 |= CHRH2FLAG_0080;
#endif

					if (spawnflags & SPAWNFLAG_NOBLOOD) {
						chr->noblood = true;
					}

					return prop;
				}

				modelFree(model);
			}
		}
	}

	// Low memory - find a corpse to reap
	if (chrsGetNumFree() < 4) {
#if VERSION >= VERSION_NTSC_1_0
		s32 stack2;
		struct chrdata *replacechr;
		s32 startindex;
		s32 index;
#else
		s32 startindex;
		struct chrdata *replacechr;
		s32 index;
#endif

		replacechr = NULL;
		startindex = random() % g_NumChrSlots;
		index = startindex;

#if VERSION < VERSION_NTSC_1_0
		if (startindex);
#endif

		do {
			if (g_ChrSlots[index].chrnum >= 0 && g_ChrSlots[index].model && g_ChrSlots[index].prop) {
				if (g_ChrSlots[index].actiontype == ACT_DEAD
#if VERSION >= VERSION_NTSC_1_0
						|| (g_ChrSlots[index].actiontype == ACT_DRUGGEDKO && (g_ChrSlots[index].chrflags & CHRCFLAG_KEEPCORPSEKO) == 0)
#endif
						) {
					// If we've found a chr that's ready to be reaped, great.
					// Bail out of the loop.
					if (g_ChrSlots[index].act_dead.invistimer60 >= PALDOWN(120)) {
						replacechr = &g_ChrSlots[index];
						break;
					}

					// Otherwise, this chr is dead/KO'ed and can be reaped as a
					// last resort, so store them and keep looping in search of
					// a better chr.
					if (replacechr == NULL) {
						replacechr = &g_ChrSlots[index];
					}
				}
			}

			index = (index + 1) % g_NumChrSlots;
		} while (index != startindex);

		if (replacechr) {
			replacechr->act_dead.fadewheninvis = true;
			replacechr->act_dead.fadenow = true;
		}
	}

	return NULL;
}

struct prop *chrSpawnAtPad(struct chrdata *basechr, s32 body, s32 head, s32 pad_id, u8 *ailist, u32 spawnflags)
{
	s32 resolved_pad_id = chrResolvePadId(basechr, pad_id);
	struct pad pad;
	s16 room[2];
	f32 fvalue;
	padUnpack(resolved_pad_id, PADFIELD_POS | PADFIELD_LOOK | PADFIELD_ROOM, &pad);
	fvalue = atan2f(pad.look.x, pad.look.z);
	room[0] = pad.room;
	room[1] = -1;

	return chrSpawnAtCoord(body, head, &pad.pos, &room[0], fvalue, ailist, spawnflags);
}

struct prop *chrSpawnAtChr(struct chrdata *basechr, s32 body, s32 head, u32 chrnum, u8 *ailist, u32 spawnflags)
{
	struct chrdata *chr = chrFindById(basechr, chrnum);
	f32 fvalue;

	if (1) {
		fvalue = chrGetInverseTheta(chr);
	}

	return chrSpawnAtCoord(body, head, &chr->prop->pos, chr->prop->rooms, fvalue, ailist, spawnflags);
}

bool func0f04b658(struct chrdata *chr)
{
	bool result = false;
	struct prop *prop = chr->prop;
	struct prop *target = chrGetTargetProp(chr);

	if (chr->proppreset1 >= 0) {
		chrSetPerimEnabled(chr, false);
		propSetPerimEnabled(target, false);

		if (!cd0002dc18(&prop->pos, prop->rooms, &target->pos, 0x33)) {
			struct prop *thing = cdGetObstacle();

			if (thing && thing->type == PROPTYPE_OBJ
					&& chr->proppreset1 == (s16)(thing - g_Vars.props)) {
				result = true;
			}
		}

		chrSetPerimEnabled(chr, true);
		propSetPerimEnabled(target, true);
	}

	return result;
}

void func0f04b740(void)
{
	// empty
}

bool chrMoveToPos(struct chrdata *chr, struct coord *pos, s16 *rooms, f32 angle, bool allowonscreen)
{
	struct coord pos2;
	s16 rooms2[8];
	bool result = false;
	u32 nodetype;
	union modelrwdata *rwdata;
	struct player *player;
	f32 ground;

	pos2.x = pos->x;
	pos2.y = pos->y;
	pos2.z = pos->z;

	roomsCopy(rooms, rooms2);
	propSetPerimEnabled(chr->prop, false);

#if VERSION >= VERSION_NTSC_1_0
	if (chrAdjustPosForSpawn(chr->chrwidth, &pos2, rooms2, angle, (chr->hidden & CHRHFLAG_00100000) != 0, allowonscreen, (chr->hidden & CHRHFLAG_00000200) != 0))
#else
	if (chrAdjustPosForSpawn(chr->chrwidth, &pos2, rooms2, angle, (chr->hidden & CHRHFLAG_00100000) != 0, allowonscreen))
#endif
	{
		ground = cdFindGroundY(&pos2, chr->chrwidth, rooms2, &chr->floorcol,
				&chr->floortype, NULL, &chr->floorroom, NULL, NULL);

		chr->ground = ground;
		chr->manground = ground;
		chr->sumground = ground * (PAL ? 8.4175090789795f : 9.999998f);
		chr->prop->pos.x = pos2.x;
		chr->prop->pos.y = pos2.y;
		chr->prop->pos.z = pos2.z;

		propDeregisterRooms(chr->prop);
		roomsCopy(rooms2, chr->prop->rooms);
		chr0f0220ac(chr);
		modelSetRootPosition(chr->model, &pos2);

		nodetype = chr->model->filedata->rootnode->type;

		if ((nodetype & 0xff) == MODELNODETYPE_CHRINFO) {
			rwdata = modelGetNodeRwData(chr->model, chr->model->filedata->rootnode);
			rwdata->chrinfo.ground = ground;
		}

		chr->chrflags |= CHRCFLAG_00000001;
		chrSetLookAngle(chr, angle);

		if (chr->prop->type == PROPTYPE_PLAYER) {
			player = g_Vars.players[propGetPlayerNum(chr->prop)];
			player->vv_manground = ground;
			player->vv_ground = ground;
			player->vv_theta = ((M_BADTAU - angle) * 360.0f) / M_BADTAU;
			player->vv_verta = 0;
			player->unk1c64 = 1;
		}

		result = true;
	}

	propSetPerimEnabled(chr->prop, true);

	return result;
}

bool chrCheckCoverOutOfSight(struct chrdata *chr, s32 covernum, bool arg2)
{
	struct cover cover;
	struct prop *target;
	bool targetcanseecover;

	// @bug: Should be >= coverGetCount()
	if (covernum < 0 || covernum > coverGetCount() || !coverUnpack(covernum, &cover)) {
		return false;
	}

	target = chrGetTargetProp(chr);

	if (!target) {
		return false;
	}

	if (arg2) {
		targetcanseecover = cd0002db98(&target->pos, target->rooms, cover.pos, 35, 8);
	} else {
		targetcanseecover = cd0002f450(&target->pos, target->rooms, cover.pos, 50, 35);
	}

	if (!targetcanseecover != false) {
		// Target can't see cover
		coverSetFlag0001(covernum, true);
		return true;
	}

	coverSetFlag0001(covernum, false);
	return false;
}

GLOBAL_ASM(
glabel chrAssignCoverByCriteria
/*  f04ba34:	27bdff48 */ 	addiu	$sp,$sp,-184
/*  f04ba38:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f04ba3c:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f04ba40:	afa500bc */ 	sw	$a1,0xbc($sp)
/*  f04ba44:	0080a025 */ 	or	$s4,$a0,$zero
/*  f04ba48:	afbe0038 */ 	sw	$s8,0x38($sp)
/*  f04ba4c:	afb70034 */ 	sw	$s7,0x34($sp)
/*  f04ba50:	afb60030 */ 	sw	$s6,0x30($sp)
/*  f04ba54:	afb5002c */ 	sw	$s5,0x2c($sp)
/*  f04ba58:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f04ba5c:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f04ba60:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f04ba64:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f04ba68:	afa600c0 */ 	sw	$a2,0xc0($sp)
/*  f04ba6c:	0fc458b4 */ 	jal	coverGetCount
/*  f04ba70:	a7a500be */ 	sh	$a1,0xbe($sp)
/*  f04ba74:	afa20078 */ 	sw	$v0,0x78($sp)
/*  f04ba78:	0000f025 */ 	or	$s8,$zero,$zero
/*  f04ba7c:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f04ba80:	02802025 */ 	or	$a0,$s4,$zero
/*  f04ba84:	8e8f001c */ 	lw	$t7,0x1c($s4)
/*  f04ba88:	3c01432a */ 	lui	$at,0x432a
/*  f04ba8c:	44813000 */ 	mtc1	$at,$f6
/*  f04ba90:	c5e4000c */ 	lwc1	$f4,0xc($t7)
/*  f04ba94:	97b100be */ 	lhu	$s1,0xbe($sp)
/*  f04ba98:	8fa400c0 */ 	lw	$a0,0xc0($sp)
/*  f04ba9c:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f04baa0:	32384000 */ 	andi	$t8,$s1,0x4000
/*  f04baa4:	0040b025 */ 	or	$s6,$v0,$zero
/*  f04baa8:	00009825 */ 	or	$s3,$zero,$zero
/*  f04baac:	e7a80060 */ 	swc1	$f8,0x60($sp)
/*  f04bab0:	1300000a */ 	beqz	$t8,.L0f04badc
/*  f04bab4:	0080b825 */ 	or	$s7,$a0,$zero
/*  f04bab8:	8e8202d4 */ 	lw	$v0,0x2d4($s4)
/*  f04babc:	10400004 */ 	beqz	$v0,.L0f04bad0
/*  f04bac0:	00000000 */ 	nop
/*  f04bac4:	8c430010 */ 	lw	$v1,0x10($v0)
/*  f04bac8:	54600004 */ 	bnezl	$v1,.L0f04badc
/*  f04bacc:	afa30058 */ 	sw	$v1,0x58($sp)
.L0f04bad0:
/*  f04bad0:	1000013e */ 	b	.L0f04bfcc
/*  f04bad4:	2402ffff */ 	addiu	$v0,$zero,-1
/*  f04bad8:	afa30058 */ 	sw	$v1,0x58($sp)
.L0f04badc:
/*  f04badc:	16800003 */ 	bnez	$s4,.L0f04baec
/*  f04bae0:	00000000 */ 	nop
/*  f04bae4:	10000139 */ 	b	.L0f04bfcc
/*  f04bae8:	00001025 */ 	or	$v0,$zero,$zero
.L0f04baec:
/*  f04baec:	00840019 */ 	multu	$a0,$a0
/*  f04baf0:	8fa80078 */ 	lw	$t0,0x78($sp)
/*  f04baf4:	86990292 */ 	lh	$t9,0x292($s4)
/*  f04baf8:	3c12800a */ 	lui	$s2,%hi(g_CoverCandidates)
/*  f04bafc:	26522368 */ 	addiu	$s2,$s2,%lo(g_CoverCandidates)
/*  f04bb00:	00008025 */ 	or	$s0,$zero,$zero
/*  f04bb04:	27b500a0 */ 	addiu	$s5,$sp,0xa0
/*  f04bb08:	afb90084 */ 	sw	$t9,0x84($sp)
/*  f04bb0c:	00002012 */ 	mflo	$a0
/*  f04bb10:	190000ba */ 	blez	$t0,.L0f04bdfc
/*  f04bb14:	00000000 */ 	nop
/*  f04bb18:	afa400c0 */ 	sw	$a0,0xc0($sp)
/*  f04bb1c:	02002025 */ 	or	$a0,$s0,$zero
.L0f04bb20:
/*  f04bb20:	0fc458b8 */ 	jal	coverUnpack
/*  f04bb24:	27a50098 */ 	addiu	$a1,$sp,0x98
/*  f04bb28:	504000b0 */ 	beqzl	$v0,.L0f04bdec
/*  f04bb2c:	8fae0078 */ 	lw	$t6,0x78($sp)
/*  f04bb30:	0fc4596c */ 	jal	coverIsSpecial
/*  f04bb34:	27a40098 */ 	addiu	$a0,$sp,0x98
/*  f04bb38:	144000ab */ 	bnez	$v0,.L0f04bde8
/*  f04bb3c:	32292000 */ 	andi	$t1,$s1,0x2000
/*  f04bb40:	11200003 */ 	beqz	$t1,.L0f04bb50
/*  f04bb44:	97aa00a4 */ 	lhu	$t2,0xa4($sp)
/*  f04bb48:	314b0010 */ 	andi	$t3,$t2,0x10
/*  f04bb4c:	116000a6 */ 	beqz	$t3,.L0f04bde8
.L0f04bb50:
/*  f04bb50:	322c1000 */ 	andi	$t4,$s1,0x1000
/*  f04bb54:	15800007 */ 	bnez	$t4,.L0f04bb74
/*  f04bb58:	97ad00a4 */ 	lhu	$t5,0xa4($sp)
/*  f04bb5c:	31ae0008 */ 	andi	$t6,$t5,0x8
/*  f04bb60:	11c00004 */ 	beqz	$t6,.L0f04bb74
/*  f04bb64:	02a02025 */ 	or	$a0,$s5,$zero
/*  f04bb68:	0fc19620 */ 	jal	arrayIntersects
/*  f04bb6c:	26c50028 */ 	addiu	$a1,$s6,0x28
/*  f04bb70:	1440009d */ 	bnez	$v0,.L0f04bde8
.L0f04bb74:
/*  f04bb74:	322f0001 */ 	andi	$t7,$s1,0x1
/*  f04bb78:	11e00006 */ 	beqz	$t7,.L0f04bb94
/*  f04bb7c:	00009825 */ 	or	$s3,$zero,$zero
/*  f04bb80:	32380002 */ 	andi	$t8,$s1,0x2
/*  f04bb84:	13000003 */ 	beqz	$t8,.L0f04bb94
/*  f04bb88:	02202825 */ 	or	$a1,$s1,$zero
/*  f04bb8c:	24130001 */ 	addiu	$s3,$zero,0x1
/*  f04bb90:	30b1fffc */ 	andi	$s1,$a1,0xfffc
.L0f04bb94:
/*  f04bb94:	32280010 */ 	andi	$t0,$s1,0x10
/*  f04bb98:	11000002 */ 	beqz	$t0,.L0f04bba4
/*  f04bb9c:	8fa90084 */ 	lw	$t1,0x84($sp)
/*  f04bba0:	12090091 */ 	beq	$s0,$t1,.L0f04bde8
.L0f04bba4:
/*  f04bba4:	322a2000 */ 	andi	$t2,$s1,0x2000
/*  f04bba8:	5540000b */ 	bnezl	$t2,.L0f04bbd8
/*  f04bbac:	322c0040 */ 	andi	$t4,$s1,0x40
/*  f04bbb0:	0fc45917 */ 	jal	coverIsInUse
/*  f04bbb4:	02002025 */ 	or	$a0,$s0,$zero
/*  f04bbb8:	1440008b */ 	bnez	$v0,.L0f04bde8
/*  f04bbbc:	8fab0098 */ 	lw	$t3,0x98($sp)
/*  f04bbc0:	c7aa0060 */ 	lwc1	$f10,0x60($sp)
/*  f04bbc4:	c5700004 */ 	lwc1	$f16,0x4($t3)
/*  f04bbc8:	4610503c */ 	c.lt.s	$f10,$f16
/*  f04bbcc:	00000000 */ 	nop
/*  f04bbd0:	45010085 */ 	bc1t	.L0f04bde8
/*  f04bbd4:	322c0040 */ 	andi	$t4,$s1,0x40
.L0f04bbd8:
/*  f04bbd8:	322d0800 */ 	andi	$t5,$s1,0x800
/*  f04bbdc:	afac004c */ 	sw	$t4,0x4c($sp)
/*  f04bbe0:	11a00003 */ 	beqz	$t5,.L0f04bbf0
/*  f04bbe4:	32230080 */ 	andi	$v1,$s1,0x80
/*  f04bbe8:	1000000b */ 	b	.L0f04bc18
/*  f04bbec:	8e82001c */ 	lw	$v0,0x1c($s4)
.L0f04bbf0:
/*  f04bbf0:	322e0400 */ 	andi	$t6,$s1,0x400
/*  f04bbf4:	11c00003 */ 	beqz	$t6,.L0f04bc04
/*  f04bbf8:	322f0008 */ 	andi	$t7,$s1,0x8
/*  f04bbfc:	10000006 */ 	b	.L0f04bc18
/*  f04bc00:	02c01025 */ 	or	$v0,$s6,$zero
.L0f04bc04:
/*  f04bc04:	51e00004 */ 	beqzl	$t7,.L0f04bc18
/*  f04bc08:	8e82001c */ 	lw	$v0,0x1c($s4)
/*  f04bc0c:	10000002 */ 	b	.L0f04bc18
/*  f04bc10:	02c01025 */ 	or	$v0,$s6,$zero
/*  f04bc14:	8e82001c */ 	lw	$v0,0x1c($s4)
.L0f04bc18:
/*  f04bc18:	84580028 */ 	lh	$t8,0x28($v0)
/*  f04bc1c:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f04bc20:	a7b900aa */ 	sh	$t9,0xaa($sp)
/*  f04bc24:	10600007 */ 	beqz	$v1,.L0f04bc44
/*  f04bc28:	a7b800a8 */ 	sh	$t8,0xa8($sp)
/*  f04bc2c:	84440028 */ 	lh	$a0,0x28($v0)
/*  f04bc30:	27a500aa */ 	addiu	$a1,$sp,0xaa
/*  f04bc34:	0fc5916a */ 	jal	roomGetNeighbours
/*  f04bc38:	24060006 */ 	addiu	$a2,$zero,0x6
/*  f04bc3c:	10000008 */ 	b	.L0f04bc60
/*  f04bc40:	8fa9004c */ 	lw	$t1,0x4c($sp)
.L0f04bc44:
/*  f04bc44:	32280100 */ 	andi	$t0,$s1,0x100
/*  f04bc48:	11000004 */ 	beqz	$t0,.L0f04bc5c
/*  f04bc4c:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f04bc50:	84440028 */ 	lh	$a0,0x28($v0)
/*  f04bc54:	0fc5916a */ 	jal	roomGetNeighbours
/*  f04bc58:	24060007 */ 	addiu	$a2,$zero,0x7
.L0f04bc5c:
/*  f04bc5c:	8fa9004c */ 	lw	$t1,0x4c($sp)
.L0f04bc60:
/*  f04bc60:	02a02025 */ 	or	$a0,$s5,$zero
/*  f04bc64:	51200005 */ 	beqzl	$t1,.L0f04bc7c
/*  f04bc68:	322a0020 */ 	andi	$t2,$s1,0x20
/*  f04bc6c:	0fc19620 */ 	jal	arrayIntersects
/*  f04bc70:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f04bc74:	1440005c */ 	bnez	$v0,.L0f04bde8
/*  f04bc78:	322a0020 */ 	andi	$t2,$s1,0x20
.L0f04bc7c:
/*  f04bc7c:	11400005 */ 	beqz	$t2,.L0f04bc94
/*  f04bc80:	02a02025 */ 	or	$a0,$s5,$zero
/*  f04bc84:	0fc19620 */ 	jal	arrayIntersects
/*  f04bc88:	27a500a8 */ 	addiu	$a1,$sp,0xa8
/*  f04bc8c:	50400057 */ 	beqzl	$v0,.L0f04bdec
/*  f04bc90:	8fae0078 */ 	lw	$t6,0x78($sp)
.L0f04bc94:
/*  f04bc94:	87ab00aa */ 	lh	$t3,0xaa($sp)
/*  f04bc98:	2401ffff */ 	addiu	$at,$zero,-1
/*  f04bc9c:	5161000c */ 	beql	$t3,$at,.L0f04bcd0
/*  f04bca0:	322e0004 */ 	andi	$t6,$s1,0x4
/*  f04bca4:	868c02b8 */ 	lh	$t4,0x2b8($s4)
/*  f04bca8:	2401ffff */ 	addiu	$at,$zero,-1
/*  f04bcac:	322d0200 */ 	andi	$t5,$s1,0x200
/*  f04bcb0:	51810007 */ 	beql	$t4,$at,.L0f04bcd0
/*  f04bcb4:	322e0004 */ 	andi	$t6,$s1,0x4
/*  f04bcb8:	11a00004 */ 	beqz	$t5,.L0f04bccc
/*  f04bcbc:	02a02025 */ 	or	$a0,$s5,$zero
/*  f04bcc0:	0fc19620 */ 	jal	arrayIntersects
/*  f04bcc4:	268502b8 */ 	addiu	$a1,$s4,0x2b8
/*  f04bcc8:	14400047 */ 	bnez	$v0,.L0f04bde8
.L0f04bccc:
/*  f04bccc:	322e0004 */ 	andi	$t6,$s1,0x4
.L0f04bcd0:
/*  f04bcd0:	11c00006 */ 	beqz	$t6,.L0f04bcec
/*  f04bcd4:	322f0008 */ 	andi	$t7,$s1,0x8
/*  f04bcd8:	02802025 */ 	or	$a0,$s4,$zero
/*  f04bcdc:	0fc12555 */ 	jal	chrGetSquaredDistanceToCoord
/*  f04bce0:	8fa50098 */ 	lw	$a1,0x98($sp)
/*  f04bce4:	10000021 */ 	b	.L0f04bd6c
/*  f04bce8:	46000306 */ 	mov.s	$f12,$f0
.L0f04bcec:
/*  f04bcec:	11e00006 */ 	beqz	$t7,.L0f04bd08
/*  f04bcf0:	32384000 */ 	andi	$t8,$s1,0x4000
/*  f04bcf4:	26c40008 */ 	addiu	$a0,$s6,0x8
/*  f04bcf8:	0fc12565 */ 	jal	coordGetSquaredDistanceToCoord
/*  f04bcfc:	8fa50098 */ 	lw	$a1,0x98($sp)
/*  f04bd00:	1000001a */ 	b	.L0f04bd6c
/*  f04bd04:	46000306 */ 	mov.s	$f12,$f0
.L0f04bd08:
/*  f04bd08:	13000006 */ 	beqz	$t8,.L0f04bd24
/*  f04bd0c:	8fa40058 */ 	lw	$a0,0x58($sp)
/*  f04bd10:	24840008 */ 	addiu	$a0,$a0,0x8
/*  f04bd14:	0fc12565 */ 	jal	coordGetSquaredDistanceToCoord
/*  f04bd18:	8fa50098 */ 	lw	$a1,0x98($sp)
/*  f04bd1c:	10000013 */ 	b	.L0f04bd6c
/*  f04bd20:	46000306 */ 	mov.s	$f12,$f0
.L0f04bd24:
/*  f04bd24:	52600010 */ 	beqzl	$s3,.L0f04bd68
/*  f04bd28:	44806000 */ 	mtc1	$zero,$f12
/*  f04bd2c:	0c004b70 */ 	jal	random
/*  f04bd30:	00000000 */ 	nop
/*  f04bd34:	3401f000 */ 	dli	$at,0xf000
/*  f04bd38:	0041001b */ 	divu	$zero,$v0,$at
/*  f04bd3c:	0000c810 */ 	mfhi	$t9
/*  f04bd40:	44999000 */ 	mtc1	$t9,$f18
/*  f04bd44:	3c014f80 */ 	lui	$at,0x4f80
/*  f04bd48:	07210008 */ 	bgez	$t9,.L0f04bd6c
/*  f04bd4c:	46809320 */ 	cvt.s.w	$f12,$f18
/*  f04bd50:	44812000 */ 	mtc1	$at,$f4
/*  f04bd54:	00000000 */ 	nop
/*  f04bd58:	46046300 */ 	add.s	$f12,$f12,$f4
/*  f04bd5c:	10000003 */ 	b	.L0f04bd6c
/*  f04bd60:	00000000 */ 	nop
/*  f04bd64:	44806000 */ 	mtc1	$zero,$f12
.L0f04bd68:
/*  f04bd68:	0000b825 */ 	or	$s7,$zero,$zero
.L0f04bd6c:
/*  f04bd6c:	12e00013 */ 	beqz	$s7,.L0f04bdbc
/*  f04bd70:	001e2100 */ 	sll	$a0,$s8,0x4
/*  f04bd74:	06e10008 */ 	bgez	$s7,.L0f04bd98
/*  f04bd78:	8fa800c0 */ 	lw	$t0,0xc0($sp)
/*  f04bd7c:	44883000 */ 	mtc1	$t0,$f6
/*  f04bd80:	00000000 */ 	nop
/*  f04bd84:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f04bd88:	460c403c */ 	c.lt.s	$f8,$f12
/*  f04bd8c:	00000000 */ 	nop
/*  f04bd90:	4501000a */ 	bc1t	.L0f04bdbc
/*  f04bd94:	00000000 */ 	nop
.L0f04bd98:
/*  f04bd98:	1ae00013 */ 	blez	$s7,.L0f04bde8
/*  f04bd9c:	8fa900c0 */ 	lw	$t1,0xc0($sp)
/*  f04bda0:	44895000 */ 	mtc1	$t1,$f10
/*  f04bda4:	00000000 */ 	nop
/*  f04bda8:	46805420 */ 	cvt.s.w	$f16,$f10
/*  f04bdac:	4610603c */ 	c.lt.s	$f12,$f16
/*  f04bdb0:	00000000 */ 	nop
/*  f04bdb4:	4502000d */ 	bc1fl	.L0f04bdec
/*  f04bdb8:	8fae0078 */ 	lw	$t6,0x78($sp)
.L0f04bdbc:
/*  f04bdbc:	0c00169f */ 	jal	__f_to_ull
/*  f04bdc0:	afa40050 */ 	sw	$a0,0x50($sp)
/*  f04bdc4:	8fa40050 */ 	lw	$a0,0x50($sp)
/*  f04bdc8:	8e4a0000 */ 	lw	$t2,0x0($s2)
/*  f04bdcc:	27de0001 */ 	addiu	$s8,$s8,0x1
/*  f04bdd0:	01445821 */ 	addu	$t3,$t2,$a0
/*  f04bdd4:	ad620000 */ 	sw	$v0,0x0($t3)
/*  f04bdd8:	ad630004 */ 	sw	$v1,0x4($t3)
/*  f04bddc:	8e4c0000 */ 	lw	$t4,0x0($s2)
/*  f04bde0:	01846821 */ 	addu	$t5,$t4,$a0
/*  f04bde4:	adb00008 */ 	sw	$s0,0x8($t5)
.L0f04bde8:
/*  f04bde8:	8fae0078 */ 	lw	$t6,0x78($sp)
.L0f04bdec:
/*  f04bdec:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04bdf0:	560eff4b */ 	bnel	$s0,$t6,.L0f04bb20
/*  f04bdf4:	02002025 */ 	or	$a0,$s0,$zero
/*  f04bdf8:	00008025 */ 	or	$s0,$zero,$zero
.L0f04bdfc:
/*  f04bdfc:	3c12800a */ 	lui	$s2,%hi(g_CoverCandidates)
/*  f04be00:	2bc10002 */ 	slti	$at,$s8,0x2
/*  f04be04:	1420004b */ 	bnez	$at,.L0f04bf34
/*  f04be08:	26522368 */ 	addiu	$s2,$s2,%lo(g_CoverCandidates)
/*  f04be0c:	27c6ffff */ 	addiu	$a2,$s8,-1
/*  f04be10:	27a30088 */ 	addiu	$v1,$sp,0x88
.L0f04be14:
/*  f04be14:	18c00045 */ 	blez	$a2,.L0f04bf2c
/*  f04be18:	00002825 */ 	or	$a1,$zero,$zero
/*  f04be1c:	32240001 */ 	andi	$a0,$s1,0x1
.L0f04be20:
/*  f04be20:	14800005 */ 	bnez	$a0,.L0f04be38
/*  f04be24:	322f4000 */ 	andi	$t7,$s1,0x4000
/*  f04be28:	55e00004 */ 	bnezl	$t7,.L0f04be3c
/*  f04be2c:	8e580000 */ 	lw	$t8,0x0($s2)
/*  f04be30:	5260000f */ 	beqzl	$s3,.L0f04be70
/*  f04be34:	32390002 */ 	andi	$t9,$s1,0x2
.L0f04be38:
/*  f04be38:	8e580000 */ 	lw	$t8,0x0($s2)
.L0f04be3c:
/*  f04be3c:	00103900 */ 	sll	$a3,$s0,0x4
/*  f04be40:	03071021 */ 	addu	$v0,$t8,$a3
/*  f04be44:	8c480010 */ 	lw	$t0,0x10($v0)
/*  f04be48:	8c4a0000 */ 	lw	$t2,0x0($v0)
/*  f04be4c:	8c490014 */ 	lw	$t1,0x14($v0)
/*  f04be50:	8c4b0004 */ 	lw	$t3,0x4($v0)
/*  f04be54:	010a082b */ 	sltu	$at,$t0,$t2
/*  f04be58:	14200015 */ 	bnez	$at,.L0f04beb0
/*  f04be5c:	0148082b */ 	sltu	$at,$t2,$t0
/*  f04be60:	14200002 */ 	bnez	$at,.L0f04be6c
/*  f04be64:	012b082b */ 	sltu	$at,$t1,$t3
/*  f04be68:	14200011 */ 	bnez	$at,.L0f04beb0
.L0f04be6c:
/*  f04be6c:	32390002 */ 	andi	$t9,$s1,0x2
.L0f04be70:
/*  f04be70:	5320002b */ 	beqzl	$t9,.L0f04bf20
/*  f04be74:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04be78:	8e4c0000 */ 	lw	$t4,0x0($s2)
/*  f04be7c:	00103900 */ 	sll	$a3,$s0,0x4
/*  f04be80:	01871021 */ 	addu	$v0,$t4,$a3
/*  f04be84:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*  f04be88:	8c580010 */ 	lw	$t8,0x10($v0)
/*  f04be8c:	8c4f0004 */ 	lw	$t7,0x4($v0)
/*  f04be90:	8c590014 */ 	lw	$t9,0x14($v0)
/*  f04be94:	030e082b */ 	sltu	$at,$t8,$t6
/*  f04be98:	14200020 */ 	bnez	$at,.L0f04bf1c
/*  f04be9c:	01d8082b */ 	sltu	$at,$t6,$t8
/*  f04bea0:	14200003 */ 	bnez	$at,.L0f04beb0
/*  f04bea4:	01f9082b */ 	sltu	$at,$t7,$t9
/*  f04bea8:	5020001d */ 	beqzl	$at,.L0f04bf20
/*  f04beac:	26100001 */ 	addiu	$s0,$s0,0x1
.L0f04beb0:
/*  f04beb0:	8c410000 */ 	lw	$at,0x0($v0)
/*  f04beb4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f04beb8:	ac610000 */ 	sw	$at,0x0($v1)
/*  f04bebc:	8c480004 */ 	lw	$t0,0x4($v0)
/*  f04bec0:	ac680004 */ 	sw	$t0,0x4($v1)
/*  f04bec4:	8c410008 */ 	lw	$at,0x8($v0)
/*  f04bec8:	ac610008 */ 	sw	$at,0x8($v1)
/*  f04becc:	8c48000c */ 	lw	$t0,0xc($v0)
/*  f04bed0:	ac68000c */ 	sw	$t0,0xc($v1)
/*  f04bed4:	8c4a0014 */ 	lw	$t2,0x14($v0)
/*  f04bed8:	8c410010 */ 	lw	$at,0x10($v0)
/*  f04bedc:	ac4a0004 */ 	sw	$t2,0x4($v0)
/*  f04bee0:	ac410000 */ 	sw	$at,0x0($v0)
/*  f04bee4:	8c410018 */ 	lw	$at,0x18($v0)
/*  f04bee8:	8c4a001c */ 	lw	$t2,0x1c($v0)
/*  f04beec:	ac410008 */ 	sw	$at,0x8($v0)
/*  f04bef0:	ac4a000c */ 	sw	$t2,0xc($v0)
/*  f04bef4:	8e4b0000 */ 	lw	$t3,0x0($s2)
/*  f04bef8:	8c610000 */ 	lw	$at,0x0($v1)
/*  f04befc:	01676021 */ 	addu	$t4,$t3,$a3
/*  f04bf00:	ad810010 */ 	sw	$at,0x10($t4)
/*  f04bf04:	8c6f0004 */ 	lw	$t7,0x4($v1)
/*  f04bf08:	ad8f0014 */ 	sw	$t7,0x14($t4)
/*  f04bf0c:	8c610008 */ 	lw	$at,0x8($v1)
/*  f04bf10:	ad810018 */ 	sw	$at,0x18($t4)
/*  f04bf14:	8c6f000c */ 	lw	$t7,0xc($v1)
/*  f04bf18:	ad8f001c */ 	sw	$t7,0x1c($t4)
.L0f04bf1c:
/*  f04bf1c:	26100001 */ 	addiu	$s0,$s0,0x1
.L0f04bf20:
/*  f04bf20:	1606ffbf */ 	bne	$s0,$a2,.L0f04be20
/*  f04bf24:	00000000 */ 	nop
/*  f04bf28:	00008025 */ 	or	$s0,$zero,$zero
.L0f04bf2c:
/*  f04bf2c:	14a0ffb9 */ 	bnez	$a1,.L0f04be14
/*  f04bf30:	00000000 */ 	nop
.L0f04bf34:
/*  f04bf34:	1bc00024 */ 	blez	$s8,.L0f04bfc8
/*  f04bf38:	00003825 */ 	or	$a3,$zero,$zero
/*  f04bf3c:	32388000 */ 	andi	$t8,$s1,0x8000
/*  f04bf40:	afb80050 */ 	sw	$t8,0x50($sp)
.L0f04bf44:
/*  f04bf44:	8e420000 */ 	lw	$v0,0x0($s2)
/*  f04bf48:	02802025 */ 	or	$a0,$s4,$zero
/*  f04bf4c:	8fa60050 */ 	lw	$a2,0x50($sp)
/*  f04bf50:	0047c821 */ 	addu	$t9,$v0,$a3
/*  f04bf54:	8f250008 */ 	lw	$a1,0x8($t9)
/*  f04bf58:	0fc12e54 */ 	jal	chrCheckCoverOutOfSight
/*  f04bf5c:	afa70048 */ 	sw	$a3,0x48($sp)
/*  f04bf60:	10400016 */ 	beqz	$v0,.L0f04bfbc
/*  f04bf64:	8fa70048 */ 	lw	$a3,0x48($sp)
/*  f04bf68:	8e4d0000 */ 	lw	$t5,0x0($s2)
/*  f04bf6c:	2401ffff */ 	addiu	$at,$zero,-1
/*  f04bf70:	00002825 */ 	or	$a1,$zero,$zero
/*  f04bf74:	01a74021 */ 	addu	$t0,$t5,$a3
/*  f04bf78:	8d090008 */ 	lw	$t1,0x8($t0)
/*  f04bf7c:	a6890292 */ 	sh	$t1,0x292($s4)
/*  f04bf80:	8faa0084 */ 	lw	$t2,0x84($sp)
/*  f04bf84:	11410004 */ 	beq	$t2,$at,.L0f04bf98
/*  f04bf88:	01402025 */ 	or	$a0,$t2,$zero
/*  f04bf8c:	0fc45929 */ 	jal	coverSetInUse
/*  f04bf90:	afa70048 */ 	sw	$a3,0x48($sp)
/*  f04bf94:	8fa70048 */ 	lw	$a3,0x48($sp)
.L0f04bf98:
/*  f04bf98:	86840292 */ 	lh	$a0,0x292($s4)
/*  f04bf9c:	afa70048 */ 	sw	$a3,0x48($sp)
/*  f04bfa0:	0fc45929 */ 	jal	coverSetInUse
/*  f04bfa4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f04bfa8:	8fa70048 */ 	lw	$a3,0x48($sp)
/*  f04bfac:	8e4b0000 */ 	lw	$t3,0x0($s2)
/*  f04bfb0:	01677021 */ 	addu	$t6,$t3,$a3
/*  f04bfb4:	10000005 */ 	b	.L0f04bfcc
/*  f04bfb8:	8dc20008 */ 	lw	$v0,0x8($t6)
.L0f04bfbc:
/*  f04bfbc:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04bfc0:	161effe0 */ 	bne	$s0,$s8,.L0f04bf44
/*  f04bfc4:	24e70010 */ 	addiu	$a3,$a3,0x10
.L0f04bfc8:
/*  f04bfc8:	2402ffff */ 	addiu	$v0,$zero,-1
.L0f04bfcc:
/*  f04bfcc:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*  f04bfd0:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f04bfd4:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f04bfd8:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f04bfdc:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f04bfe0:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f04bfe4:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*  f04bfe8:	8fb60030 */ 	lw	$s6,0x30($sp)
/*  f04bfec:	8fb70034 */ 	lw	$s7,0x34($sp)
/*  f04bff0:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*  f04bff4:	03e00008 */ 	jr	$ra
/*  f04bff8:	27bd00b8 */ 	addiu	$sp,$sp,0xb8
);

// Mismatch: regalloc
//s32 chrAssignCoverByCriteria(struct chrdata *chr, u16 criteria, s32 refdist)
//{
//	s16 rooms[8];
//	struct cover cover;
//	struct covercandidate tmp;
//	s32 oldcover;
//	s32 i;
//	struct prop *roomprop;
//	s32 numcovers = coverGetCount();
//	s32 numcandidates = 0;
//	struct prop *target = chrGetTargetProp(chr);
//	bool userandomdist = false;
//	bool changed;
//	f32 sqdist;
//	f32 y = chr->prop->pos.y + 170;
//	s32 currefdist = refdist;
//	struct prop *fetchprop;
//
//	if (criteria & COVERCRITERIA_DISTTOFETCHPROP) {
//		if (!chr->aibot || !chr->aibot->fetchprop) {
//			return -1;
//		}
//
//		fetchprop = chr->aibot->fetchprop;
//	}
//
//	if (chr == NULL) {
//		return 0;
//	}
//
//	oldcover = chr->cover;
//	refdist *= refdist;
//
//	// Iterate all cover, filter them by criteria and store them in g_CoverCandidates
//	for (i = 0; i < numcovers; i++) {
//		if (coverUnpack(i, &cover)
//				&& !coverIsSpecial(&cover)
//				&& ((criteria & COVERCRITERIA_2000) == 0 || (cover.flags & COVERFLAG_OMNIDIRECTIONAL))
//				&& ((criteria & COVERCRITERIA_1000) || (cover.flags & COVERFLAG_AIMDIFFROOM) == 0 || !arrayIntersects(cover.rooms, target->rooms))) {
//			userandomdist = false;
//
//			if ((criteria & COVERCRITERIA_0001) && (criteria & COVERCRITERIA_FURTHEREST)) {
//				userandomdist = true;
//				criteria &= ~(COVERCRITERIA_0001 | COVERCRITERIA_FURTHEREST);
//			}
//
//			if (((criteria & COVERCRITERIA_FORCENEWCOVER) == 0 || i != oldcover)
//					&& ((criteria & COVERCRITERIA_2000) || !(coverIsInUse(i) || cover.pos->y > y))) {
//				if (criteria & COVERCRITERIA_ROOMSFROMME) {
//					roomprop = chr->prop;
//				} else if (criteria & COVERCRITERIA_ROOMSFROMTARGET) {
//					roomprop = target;
//				} else if (criteria & COVERCRITERIA_DISTTOTARGET) {
//					roomprop = target;
//				} else {
//					roomprop = chr->prop;
//				}
//
//				rooms[0] = roomprop->rooms[0];
//				rooms[1] = -1;
//
//				if (criteria & COVERCRITERIA_ALLOWNEIGHBOURINGROOMS) {
//					roomGetNeighbours(roomprop->rooms[0], &rooms[1], 6);
//				} else if (criteria & COVERCRITERIA_ONLYNEIGHBOURINGROOMS) {
//					roomGetNeighbours(roomprop->rooms[0], &rooms[0], 7);
//				}
//
//				if (((criteria & COVERCRITERIA_0040) == 0 || !arrayIntersects(cover.rooms, rooms))
//						&& ((criteria & COVERCRITERIA_0020) == 0 || arrayIntersects(cover.rooms, rooms))
//						&& (rooms[1] == -1
//							|| chr->oldrooms[0] == -1
//							|| (criteria & COVERCRITERIA_0200) == 0
//							|| !arrayIntersects(cover.rooms, chr->oldrooms))) {
//					if (criteria & COVERCRITERIA_DISTTOME) {
//						sqdist = chrGetSquaredDistanceToCoord(chr, cover.pos);
//					} else if (criteria & COVERCRITERIA_DISTTOTARGET) {
//						sqdist = coordGetSquaredDistanceToCoord(&target->pos, cover.pos);
//					} else if (criteria & COVERCRITERIA_DISTTOFETCHPROP) {
//						sqdist = coordGetSquaredDistanceToCoord(&fetchprop->pos, cover.pos);
//					} else if (userandomdist) {
//						sqdist = random() % 0xf000;
//					} else {
//						sqdist = 0;
//						currefdist = 0;
//					}
//
//					if (!currefdist
//							|| (currefdist < 0 && sqdist > refdist)
//							|| (currefdist > 0 && sqdist < refdist)) {
//						g_CoverCandidates[numcandidates].sqdist = sqdist;
//						g_CoverCandidates[numcandidates].covernum = i;
//						numcandidates++;
//					}
//				}
//			}
//		}
//	}
//
//	// Sort candidates by distance ascending, or descending if using COVERCRITERIA_FURTHEREST
//	if (numcandidates >= 2) {
//		do {
//			changed = false;
//
//			for (i = 0; i < numcandidates - 1; i++) {
//				if ((((criteria & COVERCRITERIA_0001) || (criteria & COVERCRITERIA_DISTTOFETCHPROP) || userandomdist) && (g_CoverCandidates[i].sqdist > g_CoverCandidates[i + 1].sqdist))
//						|| ((criteria & COVERCRITERIA_FURTHEREST) && g_CoverCandidates[i].sqdist < g_CoverCandidates[i + 1].sqdist)) {
//					changed = true;
//
//					tmp = g_CoverCandidates[i];
//					g_CoverCandidates[i] = g_CoverCandidates[i + 1];
//					g_CoverCandidates[i + 1] = tmp;
//				}
//			}
//		} while (changed);
//	}
//
//	// Assign the first out of sight cover
//	for (i = 0; i < numcandidates; i++) {
//		if (chrCheckCoverOutOfSight(chr, g_CoverCandidates[i].covernum, criteria & COVERCRITERIA_8000)) {
//			chr->cover = g_CoverCandidates[i].covernum;
//
//			if (oldcover != -1) {
//				coverSetInUse(oldcover, false);
//			}
//
//			coverSetInUse(chr->cover, true);
//
//			return g_CoverCandidates[i].covernum;
//		}
//	}
//
//	return -1;
//}

GLOBAL_ASM(
glabel chrAssignCoverAwayFromDanger
/*  f04bffc:	27bdff58 */ 	addiu	$sp,$sp,-168
/*  f04c000:	afbf005c */ 	sw	$ra,0x5c($sp)
/*  f04c004:	afbe0058 */ 	sw	$s8,0x58($sp)
/*  f04c008:	afb70054 */ 	sw	$s7,0x54($sp)
/*  f04c00c:	afb60050 */ 	sw	$s6,0x50($sp)
/*  f04c010:	afb5004c */ 	sw	$s5,0x4c($sp)
/*  f04c014:	afb40048 */ 	sw	$s4,0x48($sp)
/*  f04c018:	afb30044 */ 	sw	$s3,0x44($sp)
/*  f04c01c:	afb20040 */ 	sw	$s2,0x40($sp)
/*  f04c020:	afb1003c */ 	sw	$s1,0x3c($sp)
/*  f04c024:	afb00038 */ 	sw	$s0,0x38($sp)
/*  f04c028:	f7ba0030 */ 	sdc1	$f26,0x30($sp)
/*  f04c02c:	f7b80028 */ 	sdc1	$f24,0x28($sp)
/*  f04c030:	f7b60020 */ 	sdc1	$f22,0x20($sp)
/*  f04c034:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f04c038:	8c8e001c */ 	lw	$t6,0x1c($a0)
/*  f04c03c:	4480d000 */ 	mtc1	$zero,$f26
/*  f04c040:	3c01432a */ 	lui	$at,0x432a
/*  f04c044:	44813000 */ 	mtc1	$at,$f6
/*  f04c048:	c5c4000c */ 	lwc1	$f4,0xc($t6)
/*  f04c04c:	240fffff */ 	addiu	$t7,$zero,-1
/*  f04c050:	00808825 */ 	or	$s1,$a0,$zero
/*  f04c054:	00a0a025 */ 	or	$s4,$a1,$zero
/*  f04c058:	00c0a825 */ 	or	$s5,$a2,$zero
/*  f04c05c:	afaf0078 */ 	sw	$t7,0x78($sp)
/*  f04c060:	e7ba0090 */ 	swc1	$f26,0x90($sp)
/*  f04c064:	4600d586 */ 	mov.s	$f22,$f26
/*  f04c068:	0fc458b4 */ 	jal	coverGetCount
/*  f04c06c:	46062600 */ 	add.s	$f24,$f4,$f6
/*  f04c070:	02940019 */ 	multu	$s4,$s4
/*  f04c074:	86380292 */ 	lh	$t8,0x292($s1)
/*  f04c078:	27b60090 */ 	addiu	$s6,$sp,0x90
/*  f04c07c:	00409825 */ 	or	$s3,$v0,$zero
/*  f04c080:	afb8007c */ 	sw	$t8,0x7c($sp)
/*  f04c084:	8e39001c */ 	lw	$t9,0x1c($s1)
/*  f04c088:	c62a02c8 */ 	lwc1	$f10,0x2c8($s1)
/*  f04c08c:	02c02825 */ 	or	$a1,$s6,$zero
/*  f04c090:	c7280008 */ 	lwc1	$f8,0x8($t9)
/*  f04c094:	27a4009c */ 	addiu	$a0,$sp,0x9c
/*  f04c098:	0000a012 */ 	mflo	$s4
/*  f04c09c:	460a4401 */ 	sub.s	$f16,$f8,$f10
/*  f04c0a0:	27a600a0 */ 	addiu	$a2,$sp,0xa0
/*  f04c0a4:	02b50019 */ 	multu	$s5,$s5
/*  f04c0a8:	e7b0009c */ 	swc1	$f16,0x9c($sp)
/*  f04c0ac:	8e28001c */ 	lw	$t0,0x1c($s1)
/*  f04c0b0:	c62402d0 */ 	lwc1	$f4,0x2d0($s1)
/*  f04c0b4:	c5120010 */ 	lwc1	$f18,0x10($t0)
/*  f04c0b8:	46049181 */ 	sub.s	$f6,$f18,$f4
/*  f04c0bc:	0000a812 */ 	mflo	$s5
/*  f04c0c0:	0c0011e4 */ 	jal	guNormalize
/*  f04c0c4:	e7a600a0 */ 	swc1	$f6,0xa0($sp)
/*  f04c0c8:	1a600048 */ 	blez	$s3,.L0f04c1ec
/*  f04c0cc:	00008025 */ 	or	$s0,$zero,$zero
/*  f04c0d0:	27be0098 */ 	addiu	$s8,$sp,0x98
/*  f04c0d4:	27b70094 */ 	addiu	$s7,$sp,0x94
/*  f04c0d8:	27b20064 */ 	addiu	$s2,$sp,0x64
/*  f04c0dc:	02002025 */ 	or	$a0,$s0,$zero
.L0f04c0e0:
/*  f04c0e0:	0fc458b8 */ 	jal	coverUnpack
/*  f04c0e4:	02402825 */ 	or	$a1,$s2,$zero
/*  f04c0e8:	5040003e */ 	beqzl	$v0,.L0f04c1e4
/*  f04c0ec:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04c0f0:	0fc45917 */ 	jal	coverIsInUse
/*  f04c0f4:	02002025 */ 	or	$a0,$s0,$zero
/*  f04c0f8:	14400039 */ 	bnez	$v0,.L0f04c1e0
/*  f04c0fc:	8fa90064 */ 	lw	$t1,0x64($sp)
/*  f04c100:	c5280004 */ 	lwc1	$f8,0x4($t1)
/*  f04c104:	4608c03c */ 	c.lt.s	$f24,$f8
/*  f04c108:	00000000 */ 	nop
/*  f04c10c:	45030035 */ 	bc1tl	.L0f04c1e4
/*  f04c110:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04c114:	0fc4596c */ 	jal	coverIsSpecial
/*  f04c118:	02402025 */ 	or	$a0,$s2,$zero
/*  f04c11c:	14400030 */ 	bnez	$v0,.L0f04c1e0
/*  f04c120:	262402c8 */ 	addiu	$a0,$s1,0x2c8
/*  f04c124:	44945000 */ 	mtc1	$s4,$f10
/*  f04c128:	8fa50064 */ 	lw	$a1,0x64($sp)
/*  f04c12c:	0fc12565 */ 	jal	coordGetSquaredDistanceToCoord
/*  f04c130:	46805520 */ 	cvt.s.w	$f20,$f10
/*  f04c134:	4614003c */ 	c.lt.s	$f0,$f20
/*  f04c138:	00000000 */ 	nop
/*  f04c13c:	45030029 */ 	bc1tl	.L0f04c1e4
/*  f04c140:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04c144:	44958000 */ 	mtc1	$s5,$f16
/*  f04c148:	8faa0064 */ 	lw	$t2,0x64($sp)
/*  f04c14c:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f04c150:	4600903c */ 	c.lt.s	$f18,$f0
/*  f04c154:	00000000 */ 	nop
/*  f04c158:	45030022 */ 	bc1tl	.L0f04c1e4
/*  f04c15c:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04c160:	8e2b001c */ 	lw	$t3,0x1c($s1)
/*  f04c164:	c5440000 */ 	lwc1	$f4,0x0($t2)
/*  f04c168:	02e02025 */ 	or	$a0,$s7,$zero
/*  f04c16c:	c5660008 */ 	lwc1	$f6,0x8($t3)
/*  f04c170:	02c02825 */ 	or	$a1,$s6,$zero
/*  f04c174:	03c03025 */ 	or	$a2,$s8,$zero
/*  f04c178:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f04c17c:	e7a80094 */ 	swc1	$f8,0x94($sp)
/*  f04c180:	8e2c001c */ 	lw	$t4,0x1c($s1)
/*  f04c184:	c54a0008 */ 	lwc1	$f10,0x8($t2)
/*  f04c188:	c5900010 */ 	lwc1	$f16,0x10($t4)
/*  f04c18c:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f04c190:	0c0011e4 */ 	jal	guNormalize
/*  f04c194:	e7b20098 */ 	swc1	$f18,0x98($sp)
/*  f04c198:	c7a40098 */ 	lwc1	$f4,0x98($sp)
/*  f04c19c:	c7a600a0 */ 	lwc1	$f6,0xa0($sp)
/*  f04c1a0:	c7aa009c */ 	lwc1	$f10,0x9c($sp)
/*  f04c1a4:	c7b00094 */ 	lwc1	$f16,0x94($sp)
/*  f04c1a8:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f04c1ac:	00000000 */ 	nop
/*  f04c1b0:	46105482 */ 	mul.s	$f18,$f10,$f16
/*  f04c1b4:	46124080 */ 	add.s	$f2,$f8,$f18
/*  f04c1b8:	461a103c */ 	c.lt.s	$f2,$f26
/*  f04c1bc:	00000000 */ 	nop
/*  f04c1c0:	45010007 */ 	bc1t	.L0f04c1e0
/*  f04c1c4:	00000000 */ 	nop
/*  f04c1c8:	4602b03c */ 	c.lt.s	$f22,$f2
/*  f04c1cc:	00000000 */ 	nop
/*  f04c1d0:	45020004 */ 	bc1fl	.L0f04c1e4
/*  f04c1d4:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f04c1d8:	46001586 */ 	mov.s	$f22,$f2
/*  f04c1dc:	afb00078 */ 	sw	$s0,0x78($sp)
.L0f04c1e0:
/*  f04c1e0:	26100001 */ 	addiu	$s0,$s0,0x1
.L0f04c1e4:
/*  f04c1e4:	5613ffbe */ 	bnel	$s0,$s3,.L0f04c0e0
/*  f04c1e8:	02002025 */ 	or	$a0,$s0,$zero
.L0f04c1ec:
/*  f04c1ec:	8fad0078 */ 	lw	$t5,0x78($sp)
/*  f04c1f0:	2402ffff */ 	addiu	$v0,$zero,-1
/*  f04c1f4:	a62d0292 */ 	sh	$t5,0x292($s1)
/*  f04c1f8:	8fae0078 */ 	lw	$t6,0x78($sp)
/*  f04c1fc:	8fa4007c */ 	lw	$a0,0x7c($sp)
/*  f04c200:	51c20009 */ 	beql	$t6,$v0,.L0f04c228
/*  f04c204:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*  f04c208:	50820004 */ 	beql	$a0,$v0,.L0f04c21c
/*  f04c20c:	86240292 */ 	lh	$a0,0x292($s1)
/*  f04c210:	0fc45929 */ 	jal	coverSetInUse
/*  f04c214:	00002825 */ 	or	$a1,$zero,$zero
/*  f04c218:	86240292 */ 	lh	$a0,0x292($s1)
.L0f04c21c:
/*  f04c21c:	0fc45929 */ 	jal	coverSetInUse
/*  f04c220:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f04c224:	8fbf005c */ 	lw	$ra,0x5c($sp)
.L0f04c228:
/*  f04c228:	8fa20078 */ 	lw	$v0,0x78($sp)
/*  f04c22c:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f04c230:	d7b60020 */ 	ldc1	$f22,0x20($sp)
/*  f04c234:	d7b80028 */ 	ldc1	$f24,0x28($sp)
/*  f04c238:	d7ba0030 */ 	ldc1	$f26,0x30($sp)
/*  f04c23c:	8fb00038 */ 	lw	$s0,0x38($sp)
/*  f04c240:	8fb1003c */ 	lw	$s1,0x3c($sp)
/*  f04c244:	8fb20040 */ 	lw	$s2,0x40($sp)
/*  f04c248:	8fb30044 */ 	lw	$s3,0x44($sp)
/*  f04c24c:	8fb40048 */ 	lw	$s4,0x48($sp)
/*  f04c250:	8fb5004c */ 	lw	$s5,0x4c($sp)
/*  f04c254:	8fb60050 */ 	lw	$s6,0x50($sp)
/*  f04c258:	8fb70054 */ 	lw	$s7,0x54($sp)
/*  f04c25c:	8fbe0058 */ 	lw	$s8,0x58($sp)
/*  f04c260:	03e00008 */ 	jr	$ra
/*  f04c264:	27bd00a8 */ 	addiu	$sp,$sp,0xa8
);

/**
 * Find cover in the opposite direction (?) of the chr's runfrompos and assign
 * it to the chr. The distance from the runfrompos to the cover must be between
 * mindist and maxdist along the X/Z plane. The chr will not choose cover more
 * than 170cm higher than their current elevation, but strangely there is no
 * lower Y limit.
 *
 * Testing with this function logic results in the following, where:
 * R = run from pos
 * C = chr's pos
 * A = available cover
 * . = unavailable cover
 *
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A R A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . .
 *  A A A A A A A A A A A A A A . . . . . A
 *  A A A A A A A A A A A A A A . . . A A A
 *  A A A A A A A A A A A A A A . A A A A A
 *  A A A A A A A A A A A A A C A A A A A A
 *  . . . . . . . . . . . A A A A A A A A A
 *  . . . . . . . . . A A A A A A A A A A A
 *
 * The block of available cover around the runfrompos might be a bug, but if
 * this function is called with mindist = chr - runfrompos or higher then it
 * will work as expected.
 *
 * Preference is given to cover which is the "most opposite", meaning ones
 * which are directly behind the chr from the perspective of runfrompos.
 */
// Mismatch: Regalloc in callee-save registers
//s32 chrAssignCoverAwayFromDanger(struct chrdata *chr, s32 mindist, s32 maxdist)
//{
//	s32 i;
//	f32 vecfromdanger[2];
//	f32 vectocover[2];
//	f32 y;
//	f32 ymax;
//	f32 bestsqdist;
//	f32 sqdist;
//	s32 numcovers;
//	s32 prevcover;
//	s32 newcover;
//	f32 coversqdistfrompos;
//	struct cover cover;
//
//	ymax = chr->prop->pos.y + 170;
//	y = 0;
//	bestsqdist = 0;
//	newcover = -1;
//	numcovers = coverGetCount();
//	prevcover = chr->cover;
//
//	mindist = mindist * mindist;
//	maxdist = maxdist * maxdist;
//
//	if (mindist);
//	if (maxdist);
//
//	vecfromdanger[0] = chr->prop->pos.x - chr->runfrompos.x;
//	vecfromdanger[1] = chr->prop->pos.z - chr->runfrompos.z;
//
//	guNormalize(&vecfromdanger[0], &y, &vecfromdanger[1]);
//
//	for (i = 0; i < numcovers; i++) {
//		if (coverUnpack(i, &cover)
//				&& !coverIsInUse(i)
//				&& !(cover.pos->y > ymax)
//				&& !coverIsSpecial(&cover)) {
//			coversqdistfrompos = coordGetSquaredDistanceToCoord(&chr->runfrompos, cover.pos);
//
//			if (!(coversqdistfrompos < mindist) && !(coversqdistfrompos > maxdist)) {
//				vectocover[0] = cover.pos->x - chr->prop->pos.x;
//				vectocover[1] = cover.pos->z - chr->prop->pos.z;
//
//				guNormalize(&vectocover[0], &y, &vectocover[1]);
//
//				sqdist = vecfromdanger[0] * vectocover[0] + vecfromdanger[1] * vectocover[1];
//
//				if (!(sqdist < 0) && sqdist > bestsqdist) {
//					bestsqdist = sqdist;
//					newcover = i;
//				}
//			}
//		}
//
//		if (numcovers);
//	}
//
//	chr->cover = newcover;
//
//	if (newcover != -1) {
//		if (prevcover != -1) {
//			coverSetInUse(prevcover, false);
//		}
//
//		coverSetInUse(chr->cover, true);
//	}
//
//	return newcover;
//}

s16 chrGoToCover(struct chrdata *chr, u8 speed)
{
	struct cover cover;

	if (!chr) {
		return 0;
	}

	if (chrIsReadyForOrders(chr) && chr->cover != -1 && coverUnpack(chr->cover, &cover)) {
		chrGoToPos(chr, cover.pos, &cover.rooms[0], speed);
		return chr->cover;
	}

	return -1;
}

bool chrRunFromPos(struct chrdata *chr, u32 speed, f32 rundist, struct coord *frompos)
{
	f32 curdistfrompos;
	struct coord delta;
	s16 rooms[8];
	f32 zero = 0;

	if (chrIsReadyForOrders(chr)) {
		delta.x = chr->prop->pos.x - frompos->x;
		delta.y = chr->prop->pos.y;
		delta.z = chr->prop->pos.z - frompos->z;

		// @bug: This check should be &&. The runfrompos will fail if the
		// frompos is on the same X or Z axis as the chr, which is unlikely
		// because it's a floating point number.
		if (zero == delta.x || zero == delta.z) {
			return false;
		}

		curdistfrompos = sqrtf(delta.z * delta.z + delta.x * delta.x);
		delta.x *= rundist / curdistfrompos;
		delta.z *= rundist / curdistfrompos;

		chrSetPerimEnabled(chr, false);

		if (cdTestAToB4(&chr->prop->pos, chr->prop->rooms, &delta, CDTYPE_ALL, 4) == CDRESULT_COLLISION) {
#if VERSION >= VERSION_PAL_FINAL
			cdGetPos(&delta, 18555, "chr/chraction.c");
#elif VERSION >= VERSION_NTSC_1_0
			cdGetPos(&delta, 18547, "chraction.c");
#else
			cdGetPos(&delta, 18277, "chraction.c");
#endif
		}

		chrSetPerimEnabled(chr, true);

		func0f065e74(&chr->prop->pos, chr->prop->rooms, &delta, rooms);

		return chrGoToPos(chr, &delta, rooms, speed);
	}

	return false;
}

void chrAddTargetToBdlist(struct chrdata *chr)
{
	if (chr->prop) {
		struct prop *target = chrGetTargetProp(chr);
		s32 i;

		if (target) {
			for (i = 0; i < g_Vars.lvupdate240_60; i++) {
				chr->bdlist[chr->bdstart] = target->pos.x - chr->prop->pos.x;
				chr->bdstart++;
				chr->bdstart %= 60;

				chr->bdlist[chr->bdstart] = target->pos.z - chr->prop->pos.z;
				chr->bdstart++;
				chr->bdstart %= 60;
			}
		}
	}
}

s32 chrGetDistanceLostToTargetInLastSecond(struct chrdata *chr)
{
	s32 *bdlist = &chr->bdlist[0];
	s32 index = chr->bdstart;
	u32 stack[2];

	s32 x1 = bdlist[(index + 1) % 60];
	s32 z1 = bdlist[index];
	s32 olddist = sqrtf(x1 * x1 + z1 * z1);

	s32 x2 = bdlist[(index + 59) % 60];
	s32 z2 = bdlist[(index + 58) % 60];
	s32 curdist = sqrtf(x2 * x2 + z2 * z2);

	return curdist - olddist;
}

bool chrIsTargetNearlyInSight(struct chrdata *chr, u32 distance)
{
	struct prop *target = chrGetTargetProp(chr);

	return cd0002f450(&chr->prop->pos, chr->prop->rooms, &target->pos, distance, 32);
}

bool chrIsNearlyInTargetsSight(struct chrdata *chr, u32 distance)
{
	struct prop *target = chrGetTargetProp(chr);

	return cd0002f450(&target->pos, target->rooms, &chr->prop->pos, distance, 32);
}

f32 func0f04c784(struct chrdata *chr)
{
	f32 targetfacingangle = 0;
	u32 stack;
	struct prop *target = chrGetTargetProp(chr);
	f32 angletotarget;
	f32 result;

	if (target->type == PROPTYPE_CHR) {
		targetfacingangle = chrGetInverseTheta(target->chr);
	} else if (target->type == PROPTYPE_PLAYER) {
		s32 playernum = propGetPlayerNum(target);
		targetfacingangle = g_Vars.players[playernum]->vv_theta;
	}

	angletotarget = atan2f(target->pos.z - chr->prop->pos.z, target->pos.x - chr->prop->pos.x);
	result = (angletotarget * 360 / M_BADTAU - targetfacingangle) + 90;

	if (result > 180) {
		result -= 360;
	}

	return result;
}

#if VERSION >= VERSION_PAL_FINAL
const char var7f1a8ce4[] = "chr/chraction.c";
#else
const char var7f1a8ce4[] = "chraction.c";
#endif

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f04c874
.late_rodata
glabel var7f1a942c
.word 0x3c8ef461
.text
/*  f04c874:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f04c878:	afbf007c */ 	sw	$ra,0x7c($sp)
/*  f04c87c:	afb40068 */ 	sw	$s4,0x68($sp)
/*  f04c880:	afb30064 */ 	sw	$s3,0x64($sp)
/*  f04c884:	afb20060 */ 	sw	$s2,0x60($sp)
/*  f04c888:	afb00058 */ 	sw	$s0,0x58($sp)
/*  f04c88c:	00c08025 */ 	or	$s0,$a2,$zero
/*  f04c890:	00a09025 */ 	or	$s2,$a1,$zero
/*  f04c894:	00809825 */ 	or	$s3,$a0,$zero
/*  f04c898:	30f400ff */ 	andi	$s4,$a3,0xff
/*  f04c89c:	afbe0078 */ 	sw	$s8,0x78($sp)
/*  f04c8a0:	afb70074 */ 	sw	$s7,0x74($sp)
/*  f04c8a4:	afb60070 */ 	sw	$s6,0x70($sp)
/*  f04c8a8:	afb5006c */ 	sw	$s5,0x6c($sp)
/*  f04c8ac:	afb1005c */ 	sw	$s1,0x5c($sp)
/*  f04c8b0:	f7be0050 */ 	sdc1	$f30,0x50($sp)
/*  f04c8b4:	f7bc0048 */ 	sdc1	$f28,0x48($sp)
/*  f04c8b8:	f7ba0040 */ 	sdc1	$f26,0x40($sp)
/*  f04c8bc:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*  f04c8c0:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*  f04c8c4:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*  f04c8c8:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f04c8cc:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f04c8d0:	4480d000 */ 	mtc1	$zero,$f26
/*  f04c8d4:	00408825 */ 	or	$s1,$v0,$zero
/*  f04c8d8:	0fc131e1 */ 	jal	func0f04c784
/*  f04c8dc:	02602025 */ 	or	$a0,$s3,$zero
/*  f04c8e0:	8e6e001c */ 	lw	$t6,0x1c($s3)
/*  f04c8e4:	3c0143b4 */ 	lui	$at,0x43b4
/*  f04c8e8:	4481f000 */ 	mtc1	$at,$f30
/*  f04c8ec:	c5c40008 */ 	lwc1	$f4,0x8($t6)
/*  f04c8f0:	3c014334 */ 	lui	$at,0x4334
/*  f04c8f4:	4481e000 */ 	mtc1	$at,$f28
/*  f04c8f8:	e7a400c8 */ 	swc1	$f4,0xc8($sp)
/*  f04c8fc:	8e6f001c */ 	lw	$t7,0x1c($s3)
/*  f04c900:	46000606 */ 	mov.s	$f24,$f0
/*  f04c904:	27be00c8 */ 	addiu	$s8,$sp,0xc8
/*  f04c908:	c5e6000c */ 	lwc1	$f6,0xc($t7)
/*  f04c90c:	27b7009c */ 	addiu	$s7,$sp,0x9c
/*  f04c910:	27b600a0 */ 	addiu	$s6,$sp,0xa0
/*  f04c914:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f04c918:	8e78001c */ 	lw	$t8,0x1c($s3)
/*  f04c91c:	27b50098 */ 	addiu	$s5,$sp,0x98
/*  f04c920:	c7080010 */ 	lwc1	$f8,0x10($t8)
/*  f04c924:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f04c928:	44925000 */ 	mtc1	$s2,$f10
.L0f04c92c:
/*  f04c92c:	3c014f80 */ 	lui	$at,0x4f80
/*  f04c930:	06410004 */ 	bgez	$s2,.L0f04c944
/*  f04c934:	46805020 */ 	cvt.s.w	$f0,$f10
/*  f04c938:	44818000 */ 	mtc1	$at,$f16
/*  f04c93c:	00000000 */ 	nop
/*  f04c940:	46100000 */ 	add.s	$f0,$f0,$f16
.L0f04c944:
/*  f04c944:	4600e03c */ 	c.lt.s	$f28,$f0
/*  f04c948:	46000506 */ 	mov.s	$f20,$f0
/*  f04c94c:	3c017f1b */ 	lui	$at,%hi(var7f1a942c)
/*  f04c950:	45020003 */ 	bc1fl	.L0f04c960
/*  f04c954:	4618a501 */ 	sub.s	$f20,$f20,$f24
/*  f04c958:	461e0501 */ 	sub.s	$f20,$f0,$f30
/*  f04c95c:	4618a501 */ 	sub.s	$f20,$f20,$f24
.L0f04c960:
/*  f04c960:	c432942c */ 	lwc1	$f18,%lo(var7f1a942c)($at)
/*  f04c964:	4612a502 */ 	mul.s	$f20,$f20,$f18
/*  f04c968:	0c0068f4 */ 	jal	cosf
/*  f04c96c:	4600a306 */ 	mov.s	$f12,$f20
/*  f04c970:	46000586 */ 	mov.s	$f22,$f0
/*  f04c974:	0c0068f7 */ 	jal	sinf
/*  f04c978:	4600a306 */ 	mov.s	$f12,$f20
/*  f04c97c:	c62e0008 */ 	lwc1	$f14,0x8($s1)
/*  f04c980:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f04c984:	c7a600d0 */ 	lwc1	$f6,0xd0($sp)
/*  f04c988:	c6280010 */ 	lwc1	$f8,0x10($s1)
/*  f04c98c:	460e2081 */ 	sub.s	$f2,$f4,$f14
/*  f04c990:	02a02825 */ 	or	$a1,$s5,$zero
/*  f04c994:	02c03025 */ 	or	$a2,$s6,$zero
/*  f04c998:	46083301 */ 	sub.s	$f12,$f6,$f8
/*  f04c99c:	46161282 */ 	mul.s	$f10,$f2,$f22
/*  f04c9a0:	02e03825 */ 	or	$a3,$s7,$zero
/*  f04c9a4:	46006402 */ 	mul.s	$f16,$f12,$f0
/*  f04c9a8:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f04c9ac:	46001202 */ 	mul.s	$f8,$f2,$f0
/*  f04c9b0:	00000000 */ 	nop
/*  f04c9b4:	46166282 */ 	mul.s	$f10,$f12,$f22
/*  f04c9b8:	46127100 */ 	add.s	$f4,$f14,$f18
/*  f04c9bc:	e6040000 */ 	swc1	$f4,0x0($s0)
/*  f04c9c0:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04c9c4:	460a4400 */ 	add.s	$f16,$f8,$f10
/*  f04c9c8:	e6060004 */ 	swc1	$f6,0x4($s0)
/*  f04c9cc:	c6320010 */ 	lwc1	$f18,0x10($s1)
/*  f04c9d0:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f04c9d4:	e6040008 */ 	swc1	$f4,0x8($s0)
/*  f04c9d8:	0fc0a277 */ 	jal	chrGetBbox
/*  f04c9dc:	8e64001c */ 	lw	$a0,0x1c($s3)
/*  f04c9e0:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f04c9e4:	c7a600a0 */ 	lwc1	$f6,0xa0($sp)
/*  f04c9e8:	c7b2009c */ 	lwc1	$f18,0x9c($sp)
/*  f04c9ec:	8e65001c */ 	lw	$a1,0x1c($s3)
/*  f04c9f0:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f04c9f4:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f04c9f8:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f04c9fc:	46089401 */ 	sub.s	$f16,$f18,$f8
/*  f04ca00:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f04ca04:	03c02025 */ 	or	$a0,$s8,$zero
/*  f04ca08:	02003025 */ 	or	$a2,$s0,$zero
/*  f04ca0c:	e7b00018 */ 	swc1	$f16,0x18($sp)
/*  f04ca10:	24070023 */ 	addiu	$a3,$zero,0x23
/*  f04ca14:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f04ca18:	24a50028 */ 	addiu	$a1,$a1,0x28
/*  f04ca1c:	1440002a */ 	bnez	$v0,.L0f04cac8
/*  f04ca20:	02002025 */ 	or	$a0,$s0,$zero
/*  f04ca24:	3c067f1b */ 	lui	$a2,%hi(var7f1a8ce4)
/*  f04ca28:	24c68ce4 */ 	addiu	$a2,$a2,%lo(var7f1a8ce4)
/*  f04ca2c:	0c0093af */ 	jal	cdGetPos
/*  f04ca30:	240548fe */ 	addiu	$a1,$zero,0x4906
/*  f04ca34:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f04ca38:	c7a600c8 */ 	lwc1	$f6,0xc8($sp)
/*  f04ca3c:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f04ca40:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04ca44:	46062501 */ 	sub.s	$f20,$f4,$f6
/*  f04ca48:	46125581 */ 	sub.s	$f22,$f10,$f18
/*  f04ca4c:	4614a202 */ 	mul.s	$f8,$f20,$f20
/*  f04ca50:	00000000 */ 	nop
/*  f04ca54:	4616b402 */ 	mul.s	$f16,$f22,$f22
/*  f04ca58:	0c012974 */ 	jal	sqrtf
/*  f04ca5c:	46104300 */ 	add.s	$f12,$f8,$f16
/*  f04ca60:	3c014248 */ 	lui	$at,0x4248
/*  f04ca64:	44812000 */ 	mtc1	$at,$f4
/*  f04ca68:	44805000 */ 	mtc1	$zero,$f10
/*  f04ca6c:	c7b200c8 */ 	lwc1	$f18,0xc8($sp)
/*  f04ca70:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f04ca74:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f04ca78:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f04ca7c:	460a103c */ 	c.lt.s	$f2,$f10
/*  f04ca80:	00000000 */ 	nop
/*  f04ca84:	45000007 */ 	bc1f	.L0f04caa4
/*  f04ca88:	00000000 */ 	nop
/*  f04ca8c:	e6120000 */ 	swc1	$f18,0x0($s0)
/*  f04ca90:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f04ca94:	e6080004 */ 	swc1	$f8,0x4($s0)
/*  f04ca98:	c7b000d0 */ 	lwc1	$f16,0xd0($sp)
/*  f04ca9c:	1000000a */ 	b	.L0f04cac8
/*  f04caa0:	e6100008 */ 	swc1	$f16,0x8($s0)
.L0f04caa4:
/*  f04caa4:	4602a502 */ 	mul.s	$f20,$f20,$f2
/*  f04caa8:	46142180 */ 	add.s	$f6,$f4,$f20
/*  f04caac:	4602b582 */ 	mul.s	$f22,$f22,$f2
/*  f04cab0:	e6060000 */ 	swc1	$f6,0x0($s0)
/*  f04cab4:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f04cab8:	e60a0004 */ 	swc1	$f10,0x4($s0)
/*  f04cabc:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04cac0:	46169200 */ 	add.s	$f8,$f18,$f22
/*  f04cac4:	e6080008 */ 	swc1	$f8,0x8($s0)
.L0f04cac8:
/*  f04cac8:	12800019 */ 	beqz	$s4,.L0f04cb30
/*  f04cacc:	00001025 */ 	or	$v0,$zero,$zero
/*  f04cad0:	c6000000 */ 	lwc1	$f0,0x0($s0)
/*  f04cad4:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f04cad8:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f04cadc:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f04cae0:	46008081 */ 	sub.s	$f2,$f16,$f0
/*  f04cae4:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f04cae8:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04caec:	46062381 */ 	sub.s	$f14,$f4,$f6
/*  f04caf0:	46021202 */ 	mul.s	$f8,$f2,$f2
/*  f04caf4:	e7a000a8 */ 	swc1	$f0,0xa8($sp)
/*  f04caf8:	46125301 */ 	sub.s	$f12,$f10,$f18
/*  f04cafc:	460e7402 */ 	mul.s	$f16,$f14,$f14
/*  f04cb00:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f04cb04:	24080168 */ 	addiu	$t0,$zero,0x168
/*  f04cb08:	460c6182 */ 	mul.s	$f6,$f12,$f12
/*  f04cb0c:	e7aa00ac */ 	swc1	$f10,0xac($sp)
/*  f04cb10:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04cb14:	01129023 */ 	subu	$s2,$t0,$s2
/*  f04cb18:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f04cb1c:	46104100 */ 	add.s	$f4,$f8,$f16
/*  f04cb20:	0000a025 */ 	or	$s4,$zero,$zero
/*  f04cb24:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*  f04cb28:	10000001 */ 	b	.L0f04cb30
/*  f04cb2c:	46062680 */ 	add.s	$f26,$f4,$f6
.L0f04cb30:
/*  f04cb30:	5440ff7e */ 	bnezl	$v0,.L0f04c92c
/*  f04cb34:	44925000 */ 	mtc1	$s2,$f10
/*  f04cb38:	44804000 */ 	mtc1	$zero,$f8
/*  f04cb3c:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f04cb40:	02602025 */ 	or	$a0,$s3,$zero
/*  f04cb44:	4608d032 */ 	c.eq.s	$f26,$f8
/*  f04cb48:	02002825 */ 	or	$a1,$s0,$zero
/*  f04cb4c:	45010018 */ 	bc1t	.L0f04cbb0
/*  f04cb50:	00000000 */ 	nop
/*  f04cb54:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f04cb58:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04cb5c:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f04cb60:	46048081 */ 	sub.s	$f2,$f16,$f4
/*  f04cb64:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04cb68:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*  f04cb6c:	460a3381 */ 	sub.s	$f14,$f6,$f10
/*  f04cb70:	46021402 */ 	mul.s	$f16,$f2,$f2
/*  f04cb74:	46089301 */ 	sub.s	$f12,$f18,$f8
/*  f04cb78:	460e7102 */ 	mul.s	$f4,$f14,$f14
/*  f04cb7c:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f04cb80:	460c6282 */ 	mul.s	$f10,$f12,$f12
/*  f04cb84:	46048180 */ 	add.s	$f6,$f16,$f4
/*  f04cb88:	460a3480 */ 	add.s	$f18,$f6,$f10
/*  f04cb8c:	461a903c */ 	c.lt.s	$f18,$f26
/*  f04cb90:	00000000 */ 	nop
/*  f04cb94:	45000006 */ 	bc1f	.L0f04cbb0
/*  f04cb98:	00000000 */ 	nop
/*  f04cb9c:	e6080000 */ 	swc1	$f8,0x0($s0)
/*  f04cba0:	c7b000ac */ 	lwc1	$f16,0xac($sp)
/*  f04cba4:	e6100004 */ 	swc1	$f16,0x4($s0)
/*  f04cba8:	c7a400b0 */ 	lwc1	$f4,0xb0($sp)
/*  f04cbac:	e6040008 */ 	swc1	$f4,0x8($s0)
.L0f04cbb0:
/*  f04cbb0:	0fc0eaf4 */ 	jal	func0f03abd0
/*  f04cbb4:	93a600fb */ 	lbu	$a2,0xfb($sp)
/*  f04cbb8:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*  f04cbbc:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*  f04cbc0:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*  f04cbc4:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*  f04cbc8:	d7ba0040 */ 	ldc1	$f26,0x40($sp)
/*  f04cbcc:	d7bc0048 */ 	ldc1	$f28,0x48($sp)
/*  f04cbd0:	d7be0050 */ 	ldc1	$f30,0x50($sp)
/*  f04cbd4:	8fb00058 */ 	lw	$s0,0x58($sp)
/*  f04cbd8:	8fb1005c */ 	lw	$s1,0x5c($sp)
/*  f04cbdc:	8fb20060 */ 	lw	$s2,0x60($sp)
/*  f04cbe0:	8fb30064 */ 	lw	$s3,0x64($sp)
/*  f04cbe4:	8fb40068 */ 	lw	$s4,0x68($sp)
/*  f04cbe8:	8fb5006c */ 	lw	$s5,0x6c($sp)
/*  f04cbec:	8fb60070 */ 	lw	$s6,0x70($sp)
/*  f04cbf0:	8fb70074 */ 	lw	$s7,0x74($sp)
/*  f04cbf4:	8fbe0078 */ 	lw	$s8,0x78($sp)
/*  f04cbf8:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f04cbfc:	03e00008 */ 	jr	$ra
/*  f04cc00:	24020001 */ 	addiu	$v0,$zero,0x1
);
#elif VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func0f04c874
.late_rodata
glabel var7f1a942c
.word 0x3c8ef461
.text
/*  f04c874:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f04c878:	afbf007c */ 	sw	$ra,0x7c($sp)
/*  f04c87c:	afb40068 */ 	sw	$s4,0x68($sp)
/*  f04c880:	afb30064 */ 	sw	$s3,0x64($sp)
/*  f04c884:	afb20060 */ 	sw	$s2,0x60($sp)
/*  f04c888:	afb00058 */ 	sw	$s0,0x58($sp)
/*  f04c88c:	00c08025 */ 	or	$s0,$a2,$zero
/*  f04c890:	00a09025 */ 	or	$s2,$a1,$zero
/*  f04c894:	00809825 */ 	or	$s3,$a0,$zero
/*  f04c898:	30f400ff */ 	andi	$s4,$a3,0xff
/*  f04c89c:	afbe0078 */ 	sw	$s8,0x78($sp)
/*  f04c8a0:	afb70074 */ 	sw	$s7,0x74($sp)
/*  f04c8a4:	afb60070 */ 	sw	$s6,0x70($sp)
/*  f04c8a8:	afb5006c */ 	sw	$s5,0x6c($sp)
/*  f04c8ac:	afb1005c */ 	sw	$s1,0x5c($sp)
/*  f04c8b0:	f7be0050 */ 	sdc1	$f30,0x50($sp)
/*  f04c8b4:	f7bc0048 */ 	sdc1	$f28,0x48($sp)
/*  f04c8b8:	f7ba0040 */ 	sdc1	$f26,0x40($sp)
/*  f04c8bc:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*  f04c8c0:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*  f04c8c4:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*  f04c8c8:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f04c8cc:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f04c8d0:	4480d000 */ 	mtc1	$zero,$f26
/*  f04c8d4:	00408825 */ 	or	$s1,$v0,$zero
/*  f04c8d8:	0fc131e1 */ 	jal	func0f04c784
/*  f04c8dc:	02602025 */ 	or	$a0,$s3,$zero
/*  f04c8e0:	8e6e001c */ 	lw	$t6,0x1c($s3)
/*  f04c8e4:	3c0143b4 */ 	lui	$at,0x43b4
/*  f04c8e8:	4481f000 */ 	mtc1	$at,$f30
/*  f04c8ec:	c5c40008 */ 	lwc1	$f4,0x8($t6)
/*  f04c8f0:	3c014334 */ 	lui	$at,0x4334
/*  f04c8f4:	4481e000 */ 	mtc1	$at,$f28
/*  f04c8f8:	e7a400c8 */ 	swc1	$f4,0xc8($sp)
/*  f04c8fc:	8e6f001c */ 	lw	$t7,0x1c($s3)
/*  f04c900:	46000606 */ 	mov.s	$f24,$f0
/*  f04c904:	27be00c8 */ 	addiu	$s8,$sp,0xc8
/*  f04c908:	c5e6000c */ 	lwc1	$f6,0xc($t7)
/*  f04c90c:	27b7009c */ 	addiu	$s7,$sp,0x9c
/*  f04c910:	27b600a0 */ 	addiu	$s6,$sp,0xa0
/*  f04c914:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f04c918:	8e78001c */ 	lw	$t8,0x1c($s3)
/*  f04c91c:	27b50098 */ 	addiu	$s5,$sp,0x98
/*  f04c920:	c7080010 */ 	lwc1	$f8,0x10($t8)
/*  f04c924:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f04c928:	44925000 */ 	mtc1	$s2,$f10
.L0f04c92c:
/*  f04c92c:	3c014f80 */ 	lui	$at,0x4f80
/*  f04c930:	06410004 */ 	bgez	$s2,.L0f04c944
/*  f04c934:	46805020 */ 	cvt.s.w	$f0,$f10
/*  f04c938:	44818000 */ 	mtc1	$at,$f16
/*  f04c93c:	00000000 */ 	nop
/*  f04c940:	46100000 */ 	add.s	$f0,$f0,$f16
.L0f04c944:
/*  f04c944:	4600e03c */ 	c.lt.s	$f28,$f0
/*  f04c948:	46000506 */ 	mov.s	$f20,$f0
/*  f04c94c:	3c017f1b */ 	lui	$at,%hi(var7f1a942c)
/*  f04c950:	45020003 */ 	bc1fl	.L0f04c960
/*  f04c954:	4618a501 */ 	sub.s	$f20,$f20,$f24
/*  f04c958:	461e0501 */ 	sub.s	$f20,$f0,$f30
/*  f04c95c:	4618a501 */ 	sub.s	$f20,$f20,$f24
.L0f04c960:
/*  f04c960:	c432942c */ 	lwc1	$f18,%lo(var7f1a942c)($at)
/*  f04c964:	4612a502 */ 	mul.s	$f20,$f20,$f18
/*  f04c968:	0c0068f4 */ 	jal	cosf
/*  f04c96c:	4600a306 */ 	mov.s	$f12,$f20
/*  f04c970:	46000586 */ 	mov.s	$f22,$f0
/*  f04c974:	0c0068f7 */ 	jal	sinf
/*  f04c978:	4600a306 */ 	mov.s	$f12,$f20
/*  f04c97c:	c62e0008 */ 	lwc1	$f14,0x8($s1)
/*  f04c980:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f04c984:	c7a600d0 */ 	lwc1	$f6,0xd0($sp)
/*  f04c988:	c6280010 */ 	lwc1	$f8,0x10($s1)
/*  f04c98c:	460e2081 */ 	sub.s	$f2,$f4,$f14
/*  f04c990:	02a02825 */ 	or	$a1,$s5,$zero
/*  f04c994:	02c03025 */ 	or	$a2,$s6,$zero
/*  f04c998:	46083301 */ 	sub.s	$f12,$f6,$f8
/*  f04c99c:	46161282 */ 	mul.s	$f10,$f2,$f22
/*  f04c9a0:	02e03825 */ 	or	$a3,$s7,$zero
/*  f04c9a4:	46006402 */ 	mul.s	$f16,$f12,$f0
/*  f04c9a8:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f04c9ac:	46001202 */ 	mul.s	$f8,$f2,$f0
/*  f04c9b0:	00000000 */ 	nop
/*  f04c9b4:	46166282 */ 	mul.s	$f10,$f12,$f22
/*  f04c9b8:	46127100 */ 	add.s	$f4,$f14,$f18
/*  f04c9bc:	e6040000 */ 	swc1	$f4,0x0($s0)
/*  f04c9c0:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04c9c4:	460a4400 */ 	add.s	$f16,$f8,$f10
/*  f04c9c8:	e6060004 */ 	swc1	$f6,0x4($s0)
/*  f04c9cc:	c6320010 */ 	lwc1	$f18,0x10($s1)
/*  f04c9d0:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f04c9d4:	e6040008 */ 	swc1	$f4,0x8($s0)
/*  f04c9d8:	0fc0a277 */ 	jal	chrGetBbox
/*  f04c9dc:	8e64001c */ 	lw	$a0,0x1c($s3)
/*  f04c9e0:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f04c9e4:	c7a600a0 */ 	lwc1	$f6,0xa0($sp)
/*  f04c9e8:	c7b2009c */ 	lwc1	$f18,0x9c($sp)
/*  f04c9ec:	8e65001c */ 	lw	$a1,0x1c($s3)
/*  f04c9f0:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f04c9f4:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f04c9f8:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f04c9fc:	46089401 */ 	sub.s	$f16,$f18,$f8
/*  f04ca00:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f04ca04:	03c02025 */ 	or	$a0,$s8,$zero
/*  f04ca08:	02003025 */ 	or	$a2,$s0,$zero
/*  f04ca0c:	e7b00018 */ 	swc1	$f16,0x18($sp)
/*  f04ca10:	24070023 */ 	addiu	$a3,$zero,0x23
/*  f04ca14:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f04ca18:	24a50028 */ 	addiu	$a1,$a1,0x28
/*  f04ca1c:	1440002a */ 	bnez	$v0,.L0f04cac8
/*  f04ca20:	02002025 */ 	or	$a0,$s0,$zero
/*  f04ca24:	3c067f1b */ 	lui	$a2,%hi(var7f1a8ce4)
/*  f04ca28:	24c68ce4 */ 	addiu	$a2,$a2,%lo(var7f1a8ce4)
/*  f04ca2c:	0c0093af */ 	jal	cdGetPos
/*  f04ca30:	240548fe */ 	addiu	$a1,$zero,0x48fe
/*  f04ca34:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f04ca38:	c7a600c8 */ 	lwc1	$f6,0xc8($sp)
/*  f04ca3c:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f04ca40:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04ca44:	46062501 */ 	sub.s	$f20,$f4,$f6
/*  f04ca48:	46125581 */ 	sub.s	$f22,$f10,$f18
/*  f04ca4c:	4614a202 */ 	mul.s	$f8,$f20,$f20
/*  f04ca50:	00000000 */ 	nop
/*  f04ca54:	4616b402 */ 	mul.s	$f16,$f22,$f22
/*  f04ca58:	0c012974 */ 	jal	sqrtf
/*  f04ca5c:	46104300 */ 	add.s	$f12,$f8,$f16
/*  f04ca60:	3c014248 */ 	lui	$at,0x4248
/*  f04ca64:	44812000 */ 	mtc1	$at,$f4
/*  f04ca68:	44805000 */ 	mtc1	$zero,$f10
/*  f04ca6c:	c7b200c8 */ 	lwc1	$f18,0xc8($sp)
/*  f04ca70:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f04ca74:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f04ca78:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f04ca7c:	460a103c */ 	c.lt.s	$f2,$f10
/*  f04ca80:	00000000 */ 	nop
/*  f04ca84:	45000007 */ 	bc1f	.L0f04caa4
/*  f04ca88:	00000000 */ 	nop
/*  f04ca8c:	e6120000 */ 	swc1	$f18,0x0($s0)
/*  f04ca90:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f04ca94:	e6080004 */ 	swc1	$f8,0x4($s0)
/*  f04ca98:	c7b000d0 */ 	lwc1	$f16,0xd0($sp)
/*  f04ca9c:	1000000a */ 	b	.L0f04cac8
/*  f04caa0:	e6100008 */ 	swc1	$f16,0x8($s0)
.L0f04caa4:
/*  f04caa4:	4602a502 */ 	mul.s	$f20,$f20,$f2
/*  f04caa8:	46142180 */ 	add.s	$f6,$f4,$f20
/*  f04caac:	4602b582 */ 	mul.s	$f22,$f22,$f2
/*  f04cab0:	e6060000 */ 	swc1	$f6,0x0($s0)
/*  f04cab4:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f04cab8:	e60a0004 */ 	swc1	$f10,0x4($s0)
/*  f04cabc:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04cac0:	46169200 */ 	add.s	$f8,$f18,$f22
/*  f04cac4:	e6080008 */ 	swc1	$f8,0x8($s0)
.L0f04cac8:
/*  f04cac8:	12800019 */ 	beqz	$s4,.L0f04cb30
/*  f04cacc:	00001025 */ 	or	$v0,$zero,$zero
/*  f04cad0:	c6000000 */ 	lwc1	$f0,0x0($s0)
/*  f04cad4:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f04cad8:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f04cadc:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f04cae0:	46008081 */ 	sub.s	$f2,$f16,$f0
/*  f04cae4:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f04cae8:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04caec:	46062381 */ 	sub.s	$f14,$f4,$f6
/*  f04caf0:	46021202 */ 	mul.s	$f8,$f2,$f2
/*  f04caf4:	e7a000a8 */ 	swc1	$f0,0xa8($sp)
/*  f04caf8:	46125301 */ 	sub.s	$f12,$f10,$f18
/*  f04cafc:	460e7402 */ 	mul.s	$f16,$f14,$f14
/*  f04cb00:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f04cb04:	24080168 */ 	addiu	$t0,$zero,0x168
/*  f04cb08:	460c6182 */ 	mul.s	$f6,$f12,$f12
/*  f04cb0c:	e7aa00ac */ 	swc1	$f10,0xac($sp)
/*  f04cb10:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04cb14:	01129023 */ 	subu	$s2,$t0,$s2
/*  f04cb18:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f04cb1c:	46104100 */ 	add.s	$f4,$f8,$f16
/*  f04cb20:	0000a025 */ 	or	$s4,$zero,$zero
/*  f04cb24:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*  f04cb28:	10000001 */ 	b	.L0f04cb30
/*  f04cb2c:	46062680 */ 	add.s	$f26,$f4,$f6
.L0f04cb30:
/*  f04cb30:	5440ff7e */ 	bnezl	$v0,.L0f04c92c
/*  f04cb34:	44925000 */ 	mtc1	$s2,$f10
/*  f04cb38:	44804000 */ 	mtc1	$zero,$f8
/*  f04cb3c:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f04cb40:	02602025 */ 	or	$a0,$s3,$zero
/*  f04cb44:	4608d032 */ 	c.eq.s	$f26,$f8
/*  f04cb48:	02002825 */ 	or	$a1,$s0,$zero
/*  f04cb4c:	45010018 */ 	bc1t	.L0f04cbb0
/*  f04cb50:	00000000 */ 	nop
/*  f04cb54:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f04cb58:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04cb5c:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f04cb60:	46048081 */ 	sub.s	$f2,$f16,$f4
/*  f04cb64:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04cb68:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*  f04cb6c:	460a3381 */ 	sub.s	$f14,$f6,$f10
/*  f04cb70:	46021402 */ 	mul.s	$f16,$f2,$f2
/*  f04cb74:	46089301 */ 	sub.s	$f12,$f18,$f8
/*  f04cb78:	460e7102 */ 	mul.s	$f4,$f14,$f14
/*  f04cb7c:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f04cb80:	460c6282 */ 	mul.s	$f10,$f12,$f12
/*  f04cb84:	46048180 */ 	add.s	$f6,$f16,$f4
/*  f04cb88:	460a3480 */ 	add.s	$f18,$f6,$f10
/*  f04cb8c:	461a903c */ 	c.lt.s	$f18,$f26
/*  f04cb90:	00000000 */ 	nop
/*  f04cb94:	45000006 */ 	bc1f	.L0f04cbb0
/*  f04cb98:	00000000 */ 	nop
/*  f04cb9c:	e6080000 */ 	swc1	$f8,0x0($s0)
/*  f04cba0:	c7b000ac */ 	lwc1	$f16,0xac($sp)
/*  f04cba4:	e6100004 */ 	swc1	$f16,0x4($s0)
/*  f04cba8:	c7a400b0 */ 	lwc1	$f4,0xb0($sp)
/*  f04cbac:	e6040008 */ 	swc1	$f4,0x8($s0)
.L0f04cbb0:
/*  f04cbb0:	0fc0eaf4 */ 	jal	func0f03abd0
/*  f04cbb4:	93a600fb */ 	lbu	$a2,0xfb($sp)
/*  f04cbb8:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*  f04cbbc:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*  f04cbc0:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*  f04cbc4:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*  f04cbc8:	d7ba0040 */ 	ldc1	$f26,0x40($sp)
/*  f04cbcc:	d7bc0048 */ 	ldc1	$f28,0x48($sp)
/*  f04cbd0:	d7be0050 */ 	ldc1	$f30,0x50($sp)
/*  f04cbd4:	8fb00058 */ 	lw	$s0,0x58($sp)
/*  f04cbd8:	8fb1005c */ 	lw	$s1,0x5c($sp)
/*  f04cbdc:	8fb20060 */ 	lw	$s2,0x60($sp)
/*  f04cbe0:	8fb30064 */ 	lw	$s3,0x64($sp)
/*  f04cbe4:	8fb40068 */ 	lw	$s4,0x68($sp)
/*  f04cbe8:	8fb5006c */ 	lw	$s5,0x6c($sp)
/*  f04cbec:	8fb60070 */ 	lw	$s6,0x70($sp)
/*  f04cbf0:	8fb70074 */ 	lw	$s7,0x74($sp)
/*  f04cbf4:	8fbe0078 */ 	lw	$s8,0x78($sp)
/*  f04cbf8:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f04cbfc:	03e00008 */ 	jr	$ra
/*  f04cc00:	24020001 */ 	addiu	$v0,$zero,0x1
);
#else
GLOBAL_ASM(
glabel func0f04c874
.late_rodata
glabel var7f1a942c
.word 0x3c8ef461
.text
/*  f04c874:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f04c878:	afbf007c */ 	sw	$ra,0x7c($sp)
/*  f04c87c:	afb40068 */ 	sw	$s4,0x68($sp)
/*  f04c880:	afb30064 */ 	sw	$s3,0x64($sp)
/*  f04c884:	afb20060 */ 	sw	$s2,0x60($sp)
/*  f04c888:	afb00058 */ 	sw	$s0,0x58($sp)
/*  f04c88c:	00c08025 */ 	or	$s0,$a2,$zero
/*  f04c890:	00a09025 */ 	or	$s2,$a1,$zero
/*  f04c894:	00809825 */ 	or	$s3,$a0,$zero
/*  f04c898:	30f400ff */ 	andi	$s4,$a3,0xff
/*  f04c89c:	afbe0078 */ 	sw	$s8,0x78($sp)
/*  f04c8a0:	afb70074 */ 	sw	$s7,0x74($sp)
/*  f04c8a4:	afb60070 */ 	sw	$s6,0x70($sp)
/*  f04c8a8:	afb5006c */ 	sw	$s5,0x6c($sp)
/*  f04c8ac:	afb1005c */ 	sw	$s1,0x5c($sp)
/*  f04c8b0:	f7be0050 */ 	sdc1	$f30,0x50($sp)
/*  f04c8b4:	f7bc0048 */ 	sdc1	$f28,0x48($sp)
/*  f04c8b8:	f7ba0040 */ 	sdc1	$f26,0x40($sp)
/*  f04c8bc:	f7b80038 */ 	sdc1	$f24,0x38($sp)
/*  f04c8c0:	f7b60030 */ 	sdc1	$f22,0x30($sp)
/*  f04c8c4:	f7b40028 */ 	sdc1	$f20,0x28($sp)
/*  f04c8c8:	0fc0a221 */ 	jal	chrGetTargetProp
/*  f04c8cc:	afa700f4 */ 	sw	$a3,0xf4($sp)
/*  f04c8d0:	4480d000 */ 	mtc1	$zero,$f26
/*  f04c8d4:	00408825 */ 	or	$s1,$v0,$zero
/*  f04c8d8:	0fc131e1 */ 	jal	func0f04c784
/*  f04c8dc:	02602025 */ 	or	$a0,$s3,$zero
/*  f04c8e0:	8e6e001c */ 	lw	$t6,0x1c($s3)
/*  f04c8e4:	3c0143b4 */ 	lui	$at,0x43b4
/*  f04c8e8:	4481f000 */ 	mtc1	$at,$f30
/*  f04c8ec:	c5c40008 */ 	lwc1	$f4,0x8($t6)
/*  f04c8f0:	3c014334 */ 	lui	$at,0x4334
/*  f04c8f4:	4481e000 */ 	mtc1	$at,$f28
/*  f04c8f8:	e7a400c8 */ 	swc1	$f4,0xc8($sp)
/*  f04c8fc:	8e6f001c */ 	lw	$t7,0x1c($s3)
/*  f04c900:	46000606 */ 	mov.s	$f24,$f0
/*  f04c904:	27be00c8 */ 	addiu	$s8,$sp,0xc8
/*  f04c908:	c5e6000c */ 	lwc1	$f6,0xc($t7)
/*  f04c90c:	27b7009c */ 	addiu	$s7,$sp,0x9c
/*  f04c910:	27b600a0 */ 	addiu	$s6,$sp,0xa0
/*  f04c914:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f04c918:	8e78001c */ 	lw	$t8,0x1c($s3)
/*  f04c91c:	27b50098 */ 	addiu	$s5,$sp,0x98
/*  f04c920:	c7080010 */ 	lwc1	$f8,0x10($t8)
/*  f04c924:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f04c928:	44925000 */ 	mtc1	$s2,$f10
.L0f04c92c:
/*  f04c92c:	3c014f80 */ 	lui	$at,0x4f80
/*  f04c930:	06410004 */ 	bgez	$s2,.L0f04c944
/*  f04c934:	46805020 */ 	cvt.s.w	$f0,$f10
/*  f04c938:	44818000 */ 	mtc1	$at,$f16
/*  f04c93c:	00000000 */ 	nop
/*  f04c940:	46100000 */ 	add.s	$f0,$f0,$f16
.L0f04c944:
/*  f04c944:	4600e03c */ 	c.lt.s	$f28,$f0
/*  f04c948:	46000506 */ 	mov.s	$f20,$f0
/*  f04c94c:	3c017f1b */ 	lui	$at,%hi(var7f1a942c)
/*  f04c950:	45020003 */ 	bc1fl	.L0f04c960
/*  f04c954:	4618a501 */ 	sub.s	$f20,$f20,$f24
/*  f04c958:	461e0501 */ 	sub.s	$f20,$f0,$f30
/*  f04c95c:	4618a501 */ 	sub.s	$f20,$f20,$f24
.L0f04c960:
/*  f04c960:	c432942c */ 	lwc1	$f18,%lo(var7f1a942c)($at)
/*  f04c964:	4612a502 */ 	mul.s	$f20,$f20,$f18
/*  f04c968:	0c0068f4 */ 	jal	cosf
/*  f04c96c:	4600a306 */ 	mov.s	$f12,$f20
/*  f04c970:	46000586 */ 	mov.s	$f22,$f0
/*  f04c974:	0c0068f7 */ 	jal	sinf
/*  f04c978:	4600a306 */ 	mov.s	$f12,$f20
/*  f04c97c:	c62e0008 */ 	lwc1	$f14,0x8($s1)
/*  f04c980:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f04c984:	c7a600d0 */ 	lwc1	$f6,0xd0($sp)
/*  f04c988:	c6280010 */ 	lwc1	$f8,0x10($s1)
/*  f04c98c:	460e2081 */ 	sub.s	$f2,$f4,$f14
/*  f04c990:	02a02825 */ 	or	$a1,$s5,$zero
/*  f04c994:	02c03025 */ 	or	$a2,$s6,$zero
/*  f04c998:	46083301 */ 	sub.s	$f12,$f6,$f8
/*  f04c99c:	46161282 */ 	mul.s	$f10,$f2,$f22
/*  f04c9a0:	02e03825 */ 	or	$a3,$s7,$zero
/*  f04c9a4:	46006402 */ 	mul.s	$f16,$f12,$f0
/*  f04c9a8:	46105481 */ 	sub.s	$f18,$f10,$f16
/*  f04c9ac:	46001202 */ 	mul.s	$f8,$f2,$f0
/*  f04c9b0:	00000000 */ 	nop
/*  f04c9b4:	46166282 */ 	mul.s	$f10,$f12,$f22
/*  f04c9b8:	46127100 */ 	add.s	$f4,$f14,$f18
/*  f04c9bc:	e6040000 */ 	swc1	$f4,0x0($s0)
/*  f04c9c0:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04c9c4:	460a4400 */ 	add.s	$f16,$f8,$f10
/*  f04c9c8:	e6060004 */ 	swc1	$f6,0x4($s0)
/*  f04c9cc:	c6320010 */ 	lwc1	$f18,0x10($s1)
/*  f04c9d0:	46109100 */ 	add.s	$f4,$f18,$f16
/*  f04c9d4:	e6040008 */ 	swc1	$f4,0x8($s0)
/*  f04c9d8:	0fc0a277 */ 	jal	chrGetBbox
/*  f04c9dc:	8e64001c */ 	lw	$a0,0x1c($s3)
/*  f04c9e0:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f04c9e4:	c7a600a0 */ 	lwc1	$f6,0xa0($sp)
/*  f04c9e8:	c7b2009c */ 	lwc1	$f18,0x9c($sp)
/*  f04c9ec:	8e65001c */ 	lw	$a1,0x1c($s3)
/*  f04c9f0:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f04c9f4:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f04c9f8:	afb90010 */ 	sw	$t9,0x10($sp)
/*  f04c9fc:	46089401 */ 	sub.s	$f16,$f18,$f8
/*  f04ca00:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*  f04ca04:	03c02025 */ 	or	$a0,$s8,$zero
/*  f04ca08:	02003025 */ 	or	$a2,$s0,$zero
/*  f04ca0c:	e7b00018 */ 	swc1	$f16,0x18($sp)
/*  f04ca10:	24070023 */ 	addiu	$a3,$zero,0x23
/*  f04ca14:	0c00b5f0 */ 	jal	cd0002d7c0
/*  f04ca18:	24a50028 */ 	addiu	$a1,$a1,0x28
/*  f04ca1c:	1440002a */ 	bnez	$v0,.L0f04cac8
/*  f04ca20:	02002025 */ 	or	$a0,$s0,$zero
/*  f04ca24:	3c067f1b */ 	lui	$a2,%hi(var7f1a8ce4)
/*  f04ca28:	24c68ce4 */ 	addiu	$a2,$a2,%lo(var7f1a8ce4)
/*  f04ca2c:	0c0093af */ 	jal	cdGetPos
/*  f04ca30:	240548fe */ 	addiu	$a1,$zero,0x47f0
/*  f04ca34:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f04ca38:	c7a600c8 */ 	lwc1	$f6,0xc8($sp)
/*  f04ca3c:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f04ca40:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04ca44:	46062501 */ 	sub.s	$f20,$f4,$f6
/*  f04ca48:	46125581 */ 	sub.s	$f22,$f10,$f18
/*  f04ca4c:	4614a202 */ 	mul.s	$f8,$f20,$f20
/*  f04ca50:	00000000 */ 	nop
/*  f04ca54:	4616b402 */ 	mul.s	$f16,$f22,$f22
/*  f04ca58:	0c012974 */ 	jal	sqrtf
/*  f04ca5c:	46104300 */ 	add.s	$f12,$f8,$f16
/*  f04ca60:	3c014248 */ 	lui	$at,0x4248
/*  f04ca64:	44812000 */ 	mtc1	$at,$f4
/*  f04ca68:	44805000 */ 	mtc1	$zero,$f10
/*  f04ca6c:	c7b200c8 */ 	lwc1	$f18,0xc8($sp)
/*  f04ca70:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f04ca74:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f04ca78:	46003083 */ 	div.s	$f2,$f6,$f0
/*  f04ca7c:	460a103c */ 	c.lt.s	$f2,$f10
/*  f04ca80:	00000000 */ 	nop
/*  f04ca84:	45000007 */ 	bc1f	.L0f04caa4
/*  f04ca88:	00000000 */ 	nop
/*  f04ca8c:	e6120000 */ 	swc1	$f18,0x0($s0)
/*  f04ca90:	c7a800cc */ 	lwc1	$f8,0xcc($sp)
/*  f04ca94:	e6080004 */ 	swc1	$f8,0x4($s0)
/*  f04ca98:	c7b000d0 */ 	lwc1	$f16,0xd0($sp)
/*  f04ca9c:	1000000a */ 	b	.L0f04cac8
/*  f04caa0:	e6100008 */ 	swc1	$f16,0x8($s0)
.L0f04caa4:
/*  f04caa4:	4602a502 */ 	mul.s	$f20,$f20,$f2
/*  f04caa8:	46142180 */ 	add.s	$f6,$f4,$f20
/*  f04caac:	4602b582 */ 	mul.s	$f22,$f22,$f2
/*  f04cab0:	e6060000 */ 	swc1	$f6,0x0($s0)
/*  f04cab4:	c7aa00cc */ 	lwc1	$f10,0xcc($sp)
/*  f04cab8:	e60a0004 */ 	swc1	$f10,0x4($s0)
/*  f04cabc:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04cac0:	46169200 */ 	add.s	$f8,$f18,$f22
/*  f04cac4:	e6080008 */ 	swc1	$f8,0x8($s0)
.L0f04cac8:
/*  f04cac8:	12800019 */ 	beqz	$s4,.L0f04cb30
/*  f04cacc:	00001025 */ 	or	$v0,$zero,$zero
/*  f04cad0:	c6000000 */ 	lwc1	$f0,0x0($s0)
/*  f04cad4:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f04cad8:	c7a400cc */ 	lwc1	$f4,0xcc($sp)
/*  f04cadc:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f04cae0:	46008081 */ 	sub.s	$f2,$f16,$f0
/*  f04cae4:	c7aa00d0 */ 	lwc1	$f10,0xd0($sp)
/*  f04cae8:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04caec:	46062381 */ 	sub.s	$f14,$f4,$f6
/*  f04caf0:	46021202 */ 	mul.s	$f8,$f2,$f2
/*  f04caf4:	e7a000a8 */ 	swc1	$f0,0xa8($sp)
/*  f04caf8:	46125301 */ 	sub.s	$f12,$f10,$f18
/*  f04cafc:	460e7402 */ 	mul.s	$f16,$f14,$f14
/*  f04cb00:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f04cb04:	24080168 */ 	addiu	$t0,$zero,0x168
/*  f04cb08:	460c6182 */ 	mul.s	$f6,$f12,$f12
/*  f04cb0c:	e7aa00ac */ 	swc1	$f10,0xac($sp)
/*  f04cb10:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f04cb14:	01129023 */ 	subu	$s2,$t0,$s2
/*  f04cb18:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f04cb1c:	46104100 */ 	add.s	$f4,$f8,$f16
/*  f04cb20:	0000a025 */ 	or	$s4,$zero,$zero
/*  f04cb24:	e7b200b0 */ 	swc1	$f18,0xb0($sp)
/*  f04cb28:	10000001 */ 	b	.L0f04cb30
/*  f04cb2c:	46062680 */ 	add.s	$f26,$f4,$f6
.L0f04cb30:
/*  f04cb30:	5440ff7e */ 	bnezl	$v0,.L0f04c92c
/*  f04cb34:	44925000 */ 	mtc1	$s2,$f10
/*  f04cb38:	44804000 */ 	mtc1	$zero,$f8
/*  f04cb3c:	c7b000c8 */ 	lwc1	$f16,0xc8($sp)
/*  f04cb40:	02602025 */ 	or	$a0,$s3,$zero
/*  f04cb44:	4608d032 */ 	c.eq.s	$f26,$f8
/*  f04cb48:	02002825 */ 	or	$a1,$s0,$zero
/*  f04cb4c:	45010018 */ 	bc1t	.L0f04cbb0
/*  f04cb50:	00000000 */ 	nop
/*  f04cb54:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f04cb58:	c7a600cc */ 	lwc1	$f6,0xcc($sp)
/*  f04cb5c:	c60a0004 */ 	lwc1	$f10,0x4($s0)
/*  f04cb60:	46048081 */ 	sub.s	$f2,$f16,$f4
/*  f04cb64:	c7b200d0 */ 	lwc1	$f18,0xd0($sp)
/*  f04cb68:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*  f04cb6c:	460a3381 */ 	sub.s	$f14,$f6,$f10
/*  f04cb70:	46021402 */ 	mul.s	$f16,$f2,$f2
/*  f04cb74:	46089301 */ 	sub.s	$f12,$f18,$f8
/*  f04cb78:	460e7102 */ 	mul.s	$f4,$f14,$f14
/*  f04cb7c:	c7a800a8 */ 	lwc1	$f8,0xa8($sp)
/*  f04cb80:	460c6282 */ 	mul.s	$f10,$f12,$f12
/*  f04cb84:	46048180 */ 	add.s	$f6,$f16,$f4
/*  f04cb88:	460a3480 */ 	add.s	$f18,$f6,$f10
/*  f04cb8c:	461a903c */ 	c.lt.s	$f18,$f26
/*  f04cb90:	00000000 */ 	nop
/*  f04cb94:	45000006 */ 	bc1f	.L0f04cbb0
/*  f04cb98:	00000000 */ 	nop
/*  f04cb9c:	e6080000 */ 	swc1	$f8,0x0($s0)
/*  f04cba0:	c7b000ac */ 	lwc1	$f16,0xac($sp)
/*  f04cba4:	e6100004 */ 	swc1	$f16,0x4($s0)
/*  f04cba8:	c7a400b0 */ 	lwc1	$f4,0xb0($sp)
/*  f04cbac:	e6040008 */ 	swc1	$f4,0x8($s0)
.L0f04cbb0:
/*  f04cbb0:	0fc0eaf4 */ 	jal	func0f03abd0
/*  f04cbb4:	93a600fb */ 	lbu	$a2,0xfb($sp)
/*  f04cbb8:	8fbf007c */ 	lw	$ra,0x7c($sp)
/*  f04cbbc:	d7b40028 */ 	ldc1	$f20,0x28($sp)
/*  f04cbc0:	d7b60030 */ 	ldc1	$f22,0x30($sp)
/*  f04cbc4:	d7b80038 */ 	ldc1	$f24,0x38($sp)
/*  f04cbc8:	d7ba0040 */ 	ldc1	$f26,0x40($sp)
/*  f04cbcc:	d7bc0048 */ 	ldc1	$f28,0x48($sp)
/*  f04cbd0:	d7be0050 */ 	ldc1	$f30,0x50($sp)
/*  f04cbd4:	8fb00058 */ 	lw	$s0,0x58($sp)
/*  f04cbd8:	8fb1005c */ 	lw	$s1,0x5c($sp)
/*  f04cbdc:	8fb20060 */ 	lw	$s2,0x60($sp)
/*  f04cbe0:	8fb30064 */ 	lw	$s3,0x64($sp)
/*  f04cbe4:	8fb40068 */ 	lw	$s4,0x68($sp)
/*  f04cbe8:	8fb5006c */ 	lw	$s5,0x6c($sp)
/*  f04cbec:	8fb60070 */ 	lw	$s6,0x70($sp)
/*  f04cbf0:	8fb70074 */ 	lw	$s7,0x74($sp)
/*  f04cbf4:	8fbe0078 */ 	lw	$s8,0x78($sp)
/*  f04cbf8:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
/*  f04cbfc:	03e00008 */ 	jr	$ra
/*  f04cc00:	24020001 */ 	addiu	$v0,$zero,0x1
);
#endif

// Mismatch: Probably due to variable reuse.
//bool func0f04c874(struct chrdata *chr, u32 angle360, struct coord *pos, u8 arg3, u8 arg4)
//{
//	struct prop *target = chrGetTargetProp(chr);
//	f32 fVar7 = 0;
//	f32 uVar9 = func0f04c784(chr);
//	struct coord chrpos; // c8, cc, d0
//	struct coord saved; // a8, ac, b0
//	f32 ymax; // a0
//	f32 ymin; // 9c
//	f32 width; // 98
//	f32 cosine;
//	f32 sine;
//	f32 xdiff;
//	f32 ydiff;
//	f32 zdiff;
//	f32 xdiff2;
//	f32 ydiff2;
//	f32 zdiff2;
//	f32 scale;
//	bool again;
//
//	chrpos.x = chr->prop->pos.x;
//	chrpos.y = chr->prop->pos.y;
//	chrpos.z = chr->prop->pos.z;
//
//	do {
//		s32 result;
//		f32 angle360f = angle360;
//
//		if (angle360f > 180) {
//			angle360f -= 360;
//		}
//
//		cosine = cosf((angle360f - uVar9) * 0.017450513318181f);
//		sine = sinf((angle360f - uVar9) * 0.017450513318181f);
//		xdiff = chrpos.x - target->pos.x;
//		zdiff = chrpos.z - target->pos.z;
//
//		pos->x = target->pos.x + (xdiff * cosine - zdiff * sine);
//		pos->y = chrpos.y;
//		pos->z = target->pos.z + (xdiff * sine + zdiff * cosine);
//
//		chrGetBbox(chr->prop, &width, &ymax, &ymin);
//
//		// a14
//		result = cd0002d7c0(&chrpos, chr->prop->rooms, pos,
//				CDTYPE_BG | CDTYPE_OBJS | CDTYPE_DOORS, 1,
//				ymax - chrpos.y,
//				ymin - chrpos.y);
//
//		if (result == CDRESULT_COLLISION) {
//			f32 xdiff;
//			f32 zdiff;
//			f32 tmp;
//			cdGetPos(pos, 18686, "chraction.c");
//
//			xdiff = pos->x - chrpos.x;
//			zdiff = pos->z - chrpos.z;
//			tmp = sqrtf(xdiff * xdiff + zdiff * zdiff);
//			scale = (tmp - 50.0f) / tmp;
//
//			if (scale < 0) {
//				pos->x = chrpos.x;
//				pos->y = chrpos.y;
//				pos->z = chrpos.z;
//			} else {
//				pos->x = chrpos.x + xdiff * scale;
//				pos->y = chrpos.y;
//				pos->z = chrpos.z + zdiff * scale;
//			}
//		}
//
//		// ac8
//		if (arg3) {
//			xdiff2 = chrpos.x - pos->x;
//			ydiff2 = chrpos.y - pos->y;
//			zdiff2 = chrpos.z - pos->z;
//
//			saved.x = pos->x;
//			saved.y = pos->y;
//			saved.z = pos->z;
//
//			fVar7 = xdiff2 * xdiff2 + ydiff2 * ydiff2 + zdiff2 * zdiff2;
//
//			angle360 = 360 - angle360;
//			again = true;
//			arg3 = 0;
//		} else {
//			again = false;
//		}
//	} while (again);
//
//	if (fVar7 != 0) {
//		f32 tmp;
//		xdiff2 = chrpos.x - pos->x;
//		ydiff2 = chrpos.y - pos->y;
//		zdiff2 = chrpos.z - pos->z;
//
//		tmp = xdiff2 * xdiff2 + ydiff2 * ydiff2 + zdiff2 * zdiff2;
//
//		if (tmp < fVar7) {
//			pos->x = saved.x;
//			pos->y = saved.y;
//			pos->z = saved.z;
//		}
//	}
//
//	func0f03abd0(chr, pos, arg4);
//
//	return true;
//}

/**
 * Chrs are assigned to teams, and they can be assigned to more than one.
 * The team assignments determine if a chr considers another chr to be friendly
 * or not.
 *
 * The chr->team value is a bitmask of which teams they belong to. There are 8
 * teams total. Each team supports up to 32 chrs. If a team is overallocated
 * then the overallocated chrs won't be registered in the team list and won't
 * be considered to be part of the team. This means they may attack each other.
 *
 * The team list is an array of 264 shorts. The first 7 are indexes into
 * the same list which mark the start of each team. Team 0 does not have
 * an entry in this list because it always starts at offset 7.
 *
 * Elements 7 onwards are chrnums. Each team is terminated with -2.
 */
void rebuildTeams(void)
{
	s32 numchrs = chrsGetNumSlots();
	s16 index = 7;
	s32 team;
	s32 i;
	struct chrdata *chr;
	u8 teammasks[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

	for (team = 0; team < 8; team++) {
		if (team != 0) {
			g_TeamList[team - 1] = index;
		}

		for (i = 0; i < numchrs; i++) {
			chr = &g_ChrSlots[i];

			if (chr->chrnum >= 0 && (chr->team & teammasks[team])) {
				g_TeamList[index] = chr->chrnum;
				index++;
			}
		}

		g_TeamList[index] = -2;
		index++;

		if (index >= 8 * 33) {
			break;
		}
	}
}

/**
 * Chrs are partitioned into squadrons for AI scripting purposes, where their
 * squadron number is in the range 0-15. Each squadron supports up to 16 chrs.
 * If a squadron is overallocated then the overallocated chrs won't be
 * registered in the squadron list and won't be considered to be part of the
 * squadron.
 *
 * The squadron list is an array of 272 shorts. The first 15 are indexes into
 * the same list which mark the start of each squadron. Squadron 0 does not have
 * an entry in this list because it always starts at offset 15.
 *
 * Elements 15 onwards are chrnums. Each squadron is terminated with -2.
 */
void rebuildSquadrons(void)
{
	s32 numchrs = chrsGetNumSlots();
	s16 index = 15;
	s32 squadron;
	s32 i;

	for (squadron = 0; squadron < 16; squadron++) {
		if (squadron != 0) {
			g_SquadronList[squadron - 1] = index;
		}

		for (i = 0; i < numchrs; i++) {
			struct chrdata *chr = &g_ChrSlots[i];

			if (chr->chrnum >= 0 && chr->squadron == squadron) {
				if (chr->prop == NULL || chr->prop->type != PROPTYPE_PLAYER) {
					g_SquadronList[index] = chr->chrnum;
					index++;
				}
			}
		}

		g_SquadronList[index] = -2;
		index++;

		if (index >= 16 * 17) {
			break;
		}
	}
}

s16 *teamGetChrIds(s32 team_id)
{
	s32 i;
	u8 lookup[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

	for (i = 0; i != MAX_TEAMS; i++) {
		if (lookup[i] == team_id) {
			team_id = i;
			break;
		}
	}

	if (team_id < 0 || team_id >= MAX_TEAMS) {
		return NULL;
	}

	if (team_id != 0) {
		return &g_TeamList[g_TeamList[team_id - 1]];
	}

	return &g_TeamList[MAX_TEAMS - 1];
}

s16 *squadronGetChrIds(s32 squadron_id)
{
	if (squadron_id < 0 || squadron_id >= MAX_SQUADRONS) {
		return NULL;
	}

	if (squadron_id != 0) {
		return &g_SquadronList[g_SquadronList[squadron_id - 1]];
	}

	return &g_SquadronList[MAX_SQUADRONS - 1];
}

void audioMarkAsRecentlyPlayed(s16 audioid)
{
	g_RecentQuipsPlayed[g_RecentQuipsIndex++] = audioid;

	if (g_RecentQuipsIndex > 4) {
		g_RecentQuipsIndex = 0;
	}
}

bool audioWasNotPlayedRecently(s16 audioid)
{
	u8 i;

	for (i = 0; i < 5; i++) {
		if (g_RecentQuipsPlayed[i] == audioid) {
			return false;
		}
	}

	return true;
}

#if VERSION >= VERSION_NTSC_1_0
Gfx *chrsRenderChrStats(Gfx *gdl, s16 *rooms)
{
	return gdl;
}
#else
Gfx *chrsRenderChrStats(Gfx *gdl, s16 *rooms)
{
	s32 x;
	s32 y;
	s32 textwidth = 0;
	s32 textheight = 0;
	s32 x2;
	s32 y2;
	struct coord sp20c;
	f32 sp204[2];
	char fullbuffer[256];
	char aibotbuffer[120];
	u8 aibot = 0;
	s32 i;
	s32 numchrs = chrsGetNumSlots();

	gdl = func0f153628(gdl);

	for (i = 0; i < numchrs; i++) {
		struct chrdata *chr = &g_ChrSlots[i];

		if (chr && chr->prop && arrayIntersects(chr->prop->rooms, rooms)) {
			sp20c.x = chr->prop->pos.x;
			sp20c.y = chr->ground + chr->chrheight - 30;
			sp20c.z = chr->prop->pos.z;

			mtx4TransformVecInPlace(g_Vars.currentplayer->matrix1740, &sp20c);

			if (sp20c.z < -100 && sp20c.z > -1000) {
				func0f0b4eb8(&sp20c, sp204, g_Vars.currentplayer->c_perspfovy, g_Vars.currentplayer->c_perspaspect);
				x = sp204[0];
				y = sp204[1];

				if (chr->aibot) {
					if (g_MpSetup.options & MPOPTION_TEAMSENABLED) {
						aibot = 1;
						sprintf(aibotbuffer, "\nTEAM %d: Cmd: %s", chr->team, mpGetBotCommandName(chr->aibot->command));
					}
				}

				sprintf(fullbuffer, "CHR[%d]\n%s\n%s\n%s%s", chr->chrnum,
						chr->myaction >= ARRAYCOUNT(g_ChrMyActionNames) ? "myaction?" : g_ChrMyActionNames[chr->myaction],
						chr->actiontype >= ARRAYCOUNT(g_ChrActionNames) || chr->actiontype < 0 ? "ACT_?" : g_ChrActionNames2[chr->actiontype],
						chr->actiontype == ACT_GOPOS || chr->actiontype == ACT_PATROL ? g_ChrLiftActionNames[chr->liftaction] : g_ChrLiftActionNames[0],
						aibot ? aibotbuffer : "");

				textMeasure(&textheight, &textwidth, fullbuffer, g_CharsHandelGothicXs, g_FontHandelGothicXs, 0);

				x2 = x + textwidth;
				y2 = y + textheight;

				gdl = func0f153858(gdl, &x, &y, &x2, &y2);
				gdl = textRender(gdl, &x, &y, fullbuffer,
						g_CharsHandelGothicXs, g_FontHandelGothicXs,
						0xff8800aa, 0x00000088, viGetWidth(), viGetHeight(), 0, 0);
			}
		}
	}

	gdl = func0f153780(gdl);

	return gdl;
}
#endif

void chrToggleModelPart(struct chrdata *chr, s32 partnum)
{
	if (chr && chr->model && chr->model->filedata) {
		struct modelnode *node = modelGetPart(chr->model->filedata, partnum);
		union modelrwdata *rwdata = NULL;

		if (node) {
			rwdata = modelGetNodeRwData(chr->model, node);
		}

		if (rwdata) {
			bool visible = rwdata->toggle.visible;
			rwdata->toggle.visible = !visible;
		}
	}
}

/**
 * Make the chr do an avoiding animation, as if they are avoiding some object
 * being thrown at them.
 *
 * The chosen animation is based on the chr's relative angle to their target.
 *
 * Collision checks are done, and no animation will be done if there would be a
 * collision.
 */
void chrAvoid(struct chrdata *chr)
{
	// The first 4 items here are animation numbers
	// and the second 4 are their corresponding end frames.
	s32 anims[] = {
		ANIM_0064, ANIM_0065, ANIM_0066, ANIM_0067,
		48, 58, 35, 35
	};

	s32 animindex;
	struct prop *target = chrGetTargetProp(chr);
	f32 relangle = chrGetAngleToPos(chr, &target->pos) / M_BADTAU * 360;
	u32 chranimflags = 0;
	f32 ymax;
	f32 ymin;
	f32 width;
	s32 cdresult = CDRESULT_NOCOLLISION;
	f32 xdiff;
	f32 zdiff;
	f32 halfchrwidth;
	f32 chrangle = model0001ae44(chr->model);
	s16 dstrooms[8];
	struct coord dstpos;

	// @bug: This shouldn't be here, and the perim is not enabled again
	// if the chr is not ready for orders.
	chrSetPerimEnabled(chr, false);

	if (chrIsReadyForOrders(chr)) {
		chrSetPerimEnabled(chr, false);

		if (relangle > 45 && relangle <= 135) {
			animindex = 3;
			chranimflags = CHRANIMFLAG_FLIP;
			chrangle += M_PI;
		} else if (relangle > 135 && relangle < 225) {
			animindex = 2;

			if ((random() % 255) >= 2) {
				cdresult = CDRESULT_COLLISION;
				chr->chrflags &= ~CHRCFLAG_10000000;
			}
		} else if (relangle > 225 && relangle < 315) {
			animindex = 3;
			chrangle += M_PI;
		} else {
			animindex = (random() % 100 < 50) ? 0 : 1;

			if (animindex == 0) {
				chrangle -= 1.5707963705063f;
			} else {
				chrangle += 1.5707963705063f;
			}
		}

		if (cdresult != CDRESULT_COLLISION) {
			dstpos.x = chr->prop->pos.x - sinf(chrangle) * 100;
			dstpos.y = chr->prop->pos.y;
			dstpos.z = chr->prop->pos.z + cosf(chrangle) * 100;

			chrGetBbox(chr->prop, &width, &ymax, &ymin);

			halfchrwidth = width * 0.5f;

			func0f065e74(&chr->prop->pos, chr->prop->rooms, &dstpos, dstrooms);
			chr0f021fa8(chr, &dstpos, dstrooms);

			xdiff = dstpos.x - chr->prop->pos.x;
			zdiff = dstpos.z - chr->prop->pos.z;

			if (xdiff > halfchrwidth || zdiff > halfchrwidth || xdiff < -halfchrwidth || zdiff < -halfchrwidth) {
				cdresult = cd0002d8b8(&chr->prop->pos, chr->prop->rooms, &dstpos, dstrooms, CDTYPE_ALL, true, ymax - chr->prop->pos.y, ymin - chr->prop->pos.y);
			}

			if (cdresult == CDRESULT_ERROR) {
				chr->chrflags &= ~CHRCFLAG_10000000;
			} else if (cdresult == CDRESULT_NOCOLLISION) {
				chrStartAnim(chr, anims[animindex], 0, anims[4 + animindex], chranimflags, 2, 0.6f);
			} else {
				chr->chrflags &= ~CHRCFLAG_10000000;
			}
		}

		chrSetPerimEnabled(chr, true);
	}
}

/**
 * Checks if the chr is doing an avoiding animation.
 *
 * These animations are possibly unused. In each one, the chr jumps backwards or
 * to the side as if avoiding something, then looks at whatever it was that just
 * went past.
 */
bool chrIsAvoiding(struct chrdata *chr)
{
	s32 anim = modelGetAnimNum(chr->model);
	chr->chrflags &= ~CHRCFLAG_10000000;

	// Possible @bug or just sloppy code: The flag check below can never pass
	// because that flag was just turned off above.
	if (anim == ANIM_0064
			|| anim == ANIM_0065
			|| anim == ANIM_0066
			|| anim == ANIM_0067
			|| (chr->chrflags & CHRCFLAG_10000000)) {
		return true;
	}

	return false;
}

void chrDrCarollEmitSparks(struct chrdata *chr)
{
	if (chr && chr->prop) {
		func0f0939f8(0, chr->prop, SFX_SHIELD_DAMAGE, -1, -1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);
		sparksCreate(chr->prop->rooms[0], chr->prop, &chr->prop->pos, NULL, 0, SPARKTYPE_01);
	}
}
