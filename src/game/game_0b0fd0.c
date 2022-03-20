#include <ultra64.h>
#include "constants.h"
#include "game/cheats.h"
#include "game/inv.h"
#include "game/bondgun.h"
#include "game/game_0b0fd0.h"
#include "game/player.h"
#include "game/hudmsg.h"
#include "game/playermgr.h"
#include "game/mplayer/setup.h"
#include "game/botcmd.h"
#include "game/lang.h"
#include "game/mplayer/mplayer.h"
#include "game/options.h"
#include "bss.h"
#include "data.h"
#include "types.h"

struct weapon *weaponFindById(s32 itemid)
{
	if (itemid < 0) {
		return NULL;
	}

	if (itemid >= ARRAYCOUNT(g_Weapons)) {
		return NULL;
	}

	return g_Weapons[itemid];
}

struct weaponfunc *weaponGetFunctionById(u32 weaponnum, u32 which)
{
	struct weapon *weapon = weaponFindById(weaponnum);

	if (weapon) {
		return weapon->functions[which];
	}

	return NULL;
}

struct weaponfunc *gsetGetWeaponFunction2(struct gset *gset)
{
	struct weapon *weapon = weaponFindById(gset->weaponnum);

	if (weapon) {
		return weapon->functions[gset->weaponfunc];
	}

	return NULL;
}

struct weaponfunc *gsetGetWeaponFunction(struct gset *gset)
{
	struct weapon *weapon = g_Weapons[gset->weaponnum];

	if (weapon) {
		return weapon->functions[gset->weaponfunc];
	}

	return NULL;
}

struct weaponfunc *weaponGetFunction(struct gset *gset, s32 which)
{
	struct weapon *weapon = g_Weapons[gset->weaponnum];

	if (weapon) {
		return weapon->functions[which];
	}

	return NULL;
}

struct weaponfunc *currentPlayerGetWeaponFunction(u32 hand)
{
	struct weapon *weapon = weaponFindById(g_Vars.currentplayer->hands[hand].gset.weaponnum);

	if (weapon) {
		return weapon->functions[g_Vars.currentplayer->hands[hand].gset.weaponfunc];
	}

	return NULL;
}

u32 weaponGetNumFunctions(u32 weaponnum)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	s32 i;

	if (!weapon) {
		return 0;
	}

	for (i = 0; i < 2; i++) {
		if (weapon->functions[i] == NULL) {
			return i;
		}
	}

	return 2;
}

struct inventory_class *func0f0b11bc(struct gset *gset)
{
	struct weapon *weapon = weaponFindById(gset->weaponnum);

	if (weapon) {
		return weapon->eptr;
	}

	return &invclass_default;
}

struct inventory_ammo *weaponGetAmmoByFunction(u32 weaponnum, u32 funcnum)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	struct weaponfunc *func = weaponGetFunctionById(weaponnum, funcnum);

	if (func && weapon && func->ammoindex >= 0) {
		return weapon->ammos[func->ammoindex];
	}

	return NULL;
}

void currentPlayerGetWeaponSway(struct coord *sway)
{
	struct weapon *weapon = weaponFindById(bgunGetWeaponNum(HAND_RIGHT));

	if (weapon) {
		sway->x = weapon->leftright;
		sway->y = weapon->updown;
		sway->z = weapon->frontback;
	}
}

void currentPlayerSetWeaponSway(struct coord *sway)
{
	struct weapon *weapon = weaponFindById(bgunGetWeaponNum(HAND_RIGHT));

	if (weapon) {
		weapon->leftright = sway->x;
		weapon->updown = sway->y;
		weapon->frontback = sway->z;
	}
}

f32 handGetXShift(s32 handnum)
{
	return g_Vars.currentplayer->hands[handnum].xshift;
}

f32 func0f0b131c(s32 hand)
{
	f32 x;
	struct weapon *weapon;

	if (hand == 0) {
		weapon = weaponFindById(bgunGetWeaponNum2(0));
		x = weapon->leftright;

		if (PLAYERCOUNT() == 2 && optionsGetScreenSplit() == SCREENSPLIT_VERTICAL) {
			x -= 3.5f;

			if (g_Vars.currentplayernum == 0) {
				x += 2.0f;
			}
		}
	} else {
		weapon = weaponFindById(bgunGetWeaponNum2(1));
		x = -weapon->leftright;

		if (PLAYERCOUNT() == 2 && optionsGetScreenSplit() == SCREENSPLIT_VERTICAL) {
			x += 3.5f;

			if (g_Vars.currentplayernum == 0) {
				x += 2.0f;
			}
		}
	}

	return x;
}

f32 currentPlayerGetGunZoomFov(void)
{
	s32 index = -1;
	struct weapon *weapon;

	switch (bgunGetWeaponNum2(0)) {
	case WEAPON_SNIPERRIFLE:    index = 0; break;
	case WEAPON_FARSIGHT:   index = 1; break;
	case WEAPON_HORIZONSCANNER: index = 2; break;
	}

	if (index >= 0) {
		return g_Vars.currentplayer->gunzoomfovs[index];
	}

	weapon = weaponFindById(bgunGetWeaponNum2(0));

	if (weapon) {
		f32 fov = weapon->eptr->zoomfov;
		return fov;
	}

	return 0;
}

void currentPlayerZoomOut(f32 fovpersec)
{
	s32 index = -1;

	switch (bgunGetWeaponNum2(0)) {
	case WEAPON_SNIPERRIFLE:    index = 0; break;
	case WEAPON_FARSIGHT:   index = 1; break;
	case WEAPON_HORIZONSCANNER: index = 2; break;
	}

	if (index >= 0) {
#if VERSION >= VERSION_PAL_BETA
		f32 amount = fovpersec * 0.25f * g_Vars.lvupdate240freal;
#else
		f32 amount = fovpersec * 0.25f * g_Vars.lvupdate240f;
#endif

		if (bgunGetWeaponNum2(0) == WEAPON_FARSIGHT) {
			amount *= 0.5f;
		}

		g_Vars.currentplayer->gunzoomfovs[index] *= 1.0f + amount * 0.1f;

		if (g_Vars.currentplayer->gunzoomfovs[index] > 60) {
			g_Vars.currentplayer->gunzoomfovs[index] = 60;
		}
	}
}

void currentPlayerZoomIn(f32 fovpersec)
{
	s32 index = -1;

	switch (bgunGetWeaponNum2(0)) {
	case WEAPON_SNIPERRIFLE:    index = 0; break;
	case WEAPON_FARSIGHT:   index = 1; break;
	case WEAPON_HORIZONSCANNER: index = 2; break;
	}

	if (index >= 0) {
#if VERSION >= VERSION_PAL_BETA
		f32 amount = fovpersec * 0.25f * g_Vars.lvupdate240freal;
#else
		f32 amount = fovpersec * 0.25f * g_Vars.lvupdate240f;
#endif

		if (bgunGetWeaponNum2(0) == WEAPON_FARSIGHT) {
			amount *= 0.5f;
		}

		g_Vars.currentplayer->gunzoomfovs[index] /= 1 + amount * 0.1f;

		if (g_Vars.currentplayer->gunzoomfovs[index] < 2) {
			g_Vars.currentplayer->gunzoomfovs[index] = 2;
		}
	}
}

bool weaponHasFlag(s32 itemid, u32 flag)
{
	struct weapon *weapon = weaponFindById(itemid);

	if (!weapon) {
		return false;
	}

	return (weapon->flags & flag) != 0;
}

bool weaponHasClassFlag(s32 weaponnum, u32 flag)
{
	struct weapon *weapon = weaponFindById(weaponnum);

	if (!weapon) {
		return false;
	}

	return (weapon->eptr->flags & flag) != 0;
}

bool weaponHasAmmoFlag(s32 weaponnum, s32 funcnum, u32 flag)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	struct inventory_ammo *ammo;

	if (weapon == NULL) {
		return false;
	}

	ammo = weapon->ammos[funcnum];

	if (ammo) {
		return (ammo->flags & flag) != 0;
	}

	return false;
}

void func0f0b18ac(s32 arg0)
{
	// empty
}

void func0f0b18b4(s32 arg0)
{
	// empty
}

s32 currentPlayerGetDeviceState(s32 weaponnum)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	s32 i;

	if (!weapon) {
		return DEVICESTATE_UNEQUIPPED;
	}

	for (i = 0; i < ARRAYCOUNT(weapon->functions); i++) {
		if (weapon->functions[i]) {
			struct weaponfunc_device *devicefunc = weapon->functions[i];

			if ((devicefunc->base.type & 0xff) == INVENTORYFUNCTYPE_DEVICE) {
				if ((g_Vars.currentplayer->devicesactive & devicefunc->device) == 0) {
					return DEVICESTATE_INACTIVE;
				}

				return DEVICESTATE_ACTIVE;
			}
		}
	}

	return DEVICESTATE_UNEQUIPPED;
}

void currentPlayerSetDeviceActive(s32 weaponnum, bool active)
{
	struct weapon *weapon = weaponFindById(weaponnum);
	s32 i;

	if (!weapon) {
		return;
	}

	for (i = 0; i < ARRAYCOUNT(weapon->functions); i++) {
		if (weapon->functions[i]) {
			struct weaponfunc_device *devicefunc = weapon->functions[i];

			if ((devicefunc->base.type & 0xff) == INVENTORYFUNCTYPE_DEVICE) {
				if (active) {
					if (devicefunc->device & (DEVICE_NIGHTVISION | DEVICE_XRAYSCANNER | DEVICE_EYESPY | DEVICE_IRSCANNER)) {
						g_Vars.currentplayer->devicesactive &= ~(DEVICE_NIGHTVISION | DEVICE_XRAYSCANNER | DEVICE_EYESPY | DEVICE_IRSCANNER);
					}

					g_Vars.currentplayer->devicesactive |= devicefunc->device;
					return;
				}

				g_Vars.currentplayer->devicesactive &= ~devicefunc->device;
				return;
			}
		}
	}
}

u16 weaponGetModelNum(s32 weaponnum)
{
	struct weapon *weapon = NULL;

	if (weaponnum != -1) {
		weapon = g_Weapons[weaponnum];
	}

	if (weapon) {
		if (PLAYERCOUNT() >= 2) {
			return weapon->lo_model;
		}

		return weapon->hi_model;
	}

	return 0;
}

u16 weaponGetModelNum2(s32 weaponnum)
{
	return weaponGetModelNum(weaponnum);
}

GLOBAL_ASM(
glabel gsetPopulateFromCurrentPlayer
/*  f0b1af0:	3c06800a */ 	lui	$a2,%hi(g_Vars)
/*  f0b1af4:	24c69fc0 */ 	addiu	$a2,$a2,%lo(g_Vars)
/*  f0b1af8:	8cce0284 */ 	lw	$t6,0x284($a2)
/*  f0b1afc:	00041100 */ 	sll	$v0,$a0,0x4
/*  f0b1b00:	00441023 */ 	subu	$v0,$v0,$a0
/*  f0b1b04:	81cf1580 */ 	lb	$t7,0x1580($t6)
/*  f0b1b08:	00021080 */ 	sll	$v0,$v0,0x2
/*  f0b1b0c:	00441021 */ 	addu	$v0,$v0,$a0
/*  f0b1b10:	a0af0000 */ 	sb	$t7,0x0($a1)
/*  f0b1b14:	8cd80284 */ 	lw	$t8,0x284($a2)
/*  f0b1b18:	000210c0 */ 	sll	$v0,$v0,0x3
/*  f0b1b1c:	00441021 */ 	addu	$v0,$v0,$a0
/*  f0b1b20:	00021080 */ 	sll	$v0,$v0,0x2
/*  f0b1b24:	0302c821 */ 	addu	$t9,$t8,$v0
/*  f0b1b28:	9328063b */ 	lbu	$t0,0x63b($t9)
/*  f0b1b2c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f0b1b30:	31e300ff */ 	andi	$v1,$t7,0xff
/*  f0b1b34:	a0a80003 */ 	sb	$t0,0x3($a1)
/*  f0b1b38:	8cc90284 */ 	lw	$t1,0x284($a2)
/*  f0b1b3c:	01225021 */ 	addu	$t2,$t1,$v0
/*  f0b1b40:	914b063a */ 	lbu	$t3,0x63a($t2)
/*  f0b1b44:	a0ab0002 */ 	sb	$t3,0x2($a1)
/*  f0b1b48:	8ccc0284 */ 	lw	$t4,0x284($a2)
/*  f0b1b4c:	01826821 */ 	addu	$t5,$t4,$v0
/*  f0b1b50:	91ae0639 */ 	lbu	$t6,0x639($t5)
/*  f0b1b54:	1461002a */ 	bne	$v1,$at,.L0f0b1c00
/*  f0b1b58:	a0ae0001 */ 	sb	$t6,0x1($a1)
/*  f0b1b5c:	8ccf0284 */ 	lw	$t7,0x284($a2)
/*  f0b1b60:	3c014120 */ 	lui	$at,0x4120
/*  f0b1b64:	44813000 */ 	mtc1	$at,$f6
/*  f0b1b68:	01e2c021 */ 	addu	$t8,$t7,$v0
/*  f0b1b6c:	c7040874 */ 	lwc1	$f4,0x874($t8)
/*  f0b1b70:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f0b1b74:	3c014f00 */ 	lui	$at,0x4f00
/*  f0b1b78:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f0b1b7c:	4459f800 */ 	cfc1	$t9,$31
/*  f0b1b80:	44c8f800 */ 	ctc1	$t0,$31
/*  f0b1b84:	00000000 */ 	nop
/*  f0b1b88:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f0b1b8c:	4448f800 */ 	cfc1	$t0,$31
/*  f0b1b90:	00000000 */ 	nop
/*  f0b1b94:	31080078 */ 	andi	$t0,$t0,0x78
/*  f0b1b98:	51000013 */ 	beqzl	$t0,.L0f0b1be8
/*  f0b1b9c:	44085000 */ 	mfc1	$t0,$f10
/*  f0b1ba0:	44815000 */ 	mtc1	$at,$f10
/*  f0b1ba4:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f0b1ba8:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f0b1bac:	44c8f800 */ 	ctc1	$t0,$31
/*  f0b1bb0:	00000000 */ 	nop
/*  f0b1bb4:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f0b1bb8:	4448f800 */ 	cfc1	$t0,$31
/*  f0b1bbc:	00000000 */ 	nop
/*  f0b1bc0:	31080078 */ 	andi	$t0,$t0,0x78
/*  f0b1bc4:	15000005 */ 	bnez	$t0,.L0f0b1bdc
/*  f0b1bc8:	00000000 */ 	nop
/*  f0b1bcc:	44085000 */ 	mfc1	$t0,$f10
/*  f0b1bd0:	3c018000 */ 	lui	$at,0x8000
/*  f0b1bd4:	10000007 */ 	b	.L0f0b1bf4
/*  f0b1bd8:	01014025 */ 	or	$t0,$t0,$at
.L0f0b1bdc:
/*  f0b1bdc:	10000005 */ 	b	.L0f0b1bf4
/*  f0b1be0:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f0b1be4:	44085000 */ 	mfc1	$t0,$f10
.L0f0b1be8:
/*  f0b1be8:	00000000 */ 	nop
/*  f0b1bec:	0500fffb */ 	bltz	$t0,.L0f0b1bdc
/*  f0b1bf0:	00000000 */ 	nop
.L0f0b1bf4:
/*  f0b1bf4:	44d9f800 */ 	ctc1	$t9,$31
/*  f0b1bf8:	a0a80002 */ 	sb	$t0,0x2($a1)
/*  f0b1bfc:	90a30000 */ 	lbu	$v1,0x0($a1)
.L0f0b1c00:
/*  f0b1c00:	2401001d */ 	addiu	$at,$zero,0x1d
/*  f0b1c04:	14610005 */ 	bne	$v1,$at,.L0f0b1c1c
/*  f0b1c08:	00000000 */ 	nop
/*  f0b1c0c:	8cc90284 */ 	lw	$t1,0x284($a2)
/*  f0b1c10:	01225021 */ 	addu	$t2,$t1,$v0
/*  f0b1c14:	8d4c0b90 */ 	lw	$t4,0xb90($t2)
/*  f0b1c18:	a0ac0002 */ 	sb	$t4,0x2($a1)
.L0f0b1c1c:
/*  f0b1c1c:	03e00008 */ 	jr	$ra
/*  f0b1c20:	00000000 */ 	nop
);

// Mismatch: regalloc
//void gsetPopulateFromCurrentPlayer(s32 handnum, struct gset *gset)
//{
//	gset->weaponnum = g_Vars.currentplayer->weaponnum;
//	gset->weaponfunc = g_Vars.currentplayer->hands[handnum].weaponfunc;
//	gset->unk063a = g_Vars.currentplayer->hands[handnum].unk063a;
//	gset->unk0639 = g_Vars.currentplayer->hands[handnum].unk0639;
//
//	if (gset->weaponnum == WEAPON_MAULER) {
//		gset->unk063a = g_Vars.currentplayer->hands[handnum].matmot1 * 10.0f;
//	}
//
//	if (gset->weaponnum == WEAPON_LASER) {
//		gset->unk063a = g_Vars.currentplayer->hands[handnum].burstbullets;
//	}
//}

struct inventory_ammo *gsetGetAmmoDefinition(struct gset *gset)
{
	struct weaponfunc *func = gsetGetWeaponFunction(gset);
	struct weapon *weapon = weaponFindById(gset->weaponnum);

	if (func && func->ammoindex >= 0) {
		return weapon->ammos[func->ammoindex];
	}

	return NULL;
}

u8 gsetGetSingleUnk3c(struct gset *gset)
{
	struct weaponfunc *func = gsetGetWeaponFunction(gset);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT) {
		struct weaponfunc_shoot *funcshoot = (struct weaponfunc_shoot *)func;
		return funcshoot->unk3c;
	}

	return 0;
}

u32 handGetCasingEject(struct gset *gset)
{
	u32 result = 0;
	struct inventory_ammo *ammo = gsetGetAmmoDefinition(gset);

	if (ammo) {
		result = ammo->casingeject;
	}

	return result;
}

f32 gsetGetStrength(struct gset *gset)
{
	struct weaponfunc *func = gsetGetWeaponFunction(gset);
	f32 result = 0;

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT) {
		struct weaponfunc_shoot *funcshoot = (struct weaponfunc_shoot *)func;
		result = funcshoot->strength;
	}

	return result;
}

f32 gsetGetDamage(struct gset *gset)
{
	struct weaponfunc *func = gsetGetWeaponFunction(gset);
	f32 damage = 0;

	if (func) {
		if ((func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT) {
			struct weaponfunc_shoot *fullfunc = (struct weaponfunc_shoot *)func;
			damage = fullfunc->damage;
		}

		if ((func->type & 0xff) == INVENTORYFUNCTYPE_CLOSE) {
			struct weaponfunc_close *fullfunc = (struct weaponfunc_close *)func;
			damage = fullfunc->damage;

			if (gset->weaponnum == WEAPON_REAPER) {
#if VERSION >= VERSION_PAL_BETA
				damage *= g_Vars.lvupdate240freal;
#else
				damage *= g_Vars.lvupdate240f;
#endif
			}
		}

		if ((func->type & 0xff) == INVENTORYFUNCTYPE_THROW) {
			struct weaponfunc_throw *fullfunc = (struct weaponfunc_throw *)func;
			damage = fullfunc->damage;
		}
	}

	if (gset->weaponnum == WEAPON_MAULER) {
		damage = (gset->unk063a / 3.0f + 1.0f) * damage;
	}

	if (bgunIsFiring(HAND_LEFT) && bgunIsFiring(HAND_RIGHT)) {
		damage += damage;
	}

	return damage;
}

u8 gsetGetFireslotDuration(struct gset *gset)
{
#if VERSION >= VERSION_PAL_FINAL
	struct weaponfunc *func = gsetGetWeaponFunction(gset);
	u8 result = 0;

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT) {
		struct weaponfunc_shoot *funcshoot = (struct weaponfunc_shoot *)func;
		result = funcshoot->unk38;
	}

	if (result >= 4) {
		result = TICKS(result);
	}

	return result;
#else
	struct weaponfunc *func = gsetGetWeaponFunction(gset);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT) {
		struct weaponfunc_shoot *funcshoot = (struct weaponfunc_shoot *)func;
		return funcshoot->unk38;
	}

	return 0;
#endif
}

u16 gsetGetSingleShootSound(struct gset *gset)
{
	struct weaponfunc *func = gsetGetWeaponFunction(gset);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_SHOOT) {
		struct weaponfunc_shoot *funcshoot = (struct weaponfunc_shoot *)func;
		return funcshoot->shootsound;
	}

	return 0;
}

bool gsetHasFunctionFlags(struct gset *gset, u32 flags)
{
	struct weaponfunc *func = gsetGetWeaponFunction(gset);

	if (func) {
		return (func->flags & flags) == flags;
	}

	return false;
}

s8 weaponGetNumTicksPerShot(u32 weaponnum, u32 funcindex)
{
	u32 stack[2];
	s32 result = 0;
	struct weapon *weapon = weaponFindById(weaponnum);
	struct weaponfunc *func = weapon->functions[funcindex];

	if (func && func->type == INVENTORYFUNCTYPE_SHOOT_AUTOMATIC) {
		struct weaponfunc_shootauto *autofunc = (struct weaponfunc_shootauto *)func;

		result = 3600.0f / autofunc->maxfirerate;
	}

#if VERSION != VERSION_PAL_BETA
	// PAL beta removes this check, only for it to be added back in PAL final
	if (result > 3) {
		result = TICKS(result);
	}
#endif

	return result;
}

u32 currentPlayerGetSight(void)
{
	struct weaponfunc *func = weaponGetFunctionById(
			g_Vars.currentplayer->hands[HAND_RIGHT].gset.weaponnum,
			g_Vars.currentplayer->hands[HAND_RIGHT].gset.weaponfunc);

	if (func && (func->type & 0xff) == INVENTORYFUNCTYPE_CLOSE) {
		return SIGHT_NONE;
	}

	if (cheatIsActive(CHEAT_CLASSICSIGHT)) {
		return SIGHT_CLASSIC;
	}

	switch (g_Vars.currentplayer->hands[HAND_RIGHT].gset.weaponnum) {
	case WEAPON_HORIZONSCANNER:
		return SIGHT_NONE;
	case WEAPON_NONE:
	case WEAPON_UNARMED:
	case WEAPON_FALCON2:
	case WEAPON_FALCON2_SILENCER:
	case WEAPON_DY357MAGNUM:
	case WEAPON_DY357LX:
	case WEAPON_CMP150:
	case WEAPON_CYCLONE:
	case WEAPON_RCP120:
	case WEAPON_SHOTGUN:
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
	case WEAPON_ECMMINE:
		return SIGHT_DEFAULT;
	case WEAPON_FALCON2_SCOPE:
	case WEAPON_MAGSEC4:
	case WEAPON_SNIPERRIFLE:
	case WEAPON_LAPTOPGUN:
	case WEAPON_DRAGON:
	case WEAPON_K7AVENGER:
	case WEAPON_AR34:
	case WEAPON_SUPERDRAGON:
		return SIGHT_ZOOM;
	case WEAPON_MAULER:
	case WEAPON_REAPER:
		return SIGHT_SKEDAR;
	case WEAPON_PHOENIX:
	case WEAPON_CALLISTO:
	case WEAPON_FARSIGHT:
		return SIGHT_MAIAN;
	case WEAPON_PP9I:
	case WEAPON_CC13:
	case WEAPON_KL01313:
	case WEAPON_KF7SPECIAL:
	case WEAPON_ZZT:
	case WEAPON_DMC:
	case WEAPON_AR53:
	case WEAPON_RCP45:
		return SIGHT_CLASSIC;
	}

	return SIGHT_DEFAULT;
}

void gsetGetNoiseSettings(struct gset *gset, struct noisesettings *dst)
{
	struct noisesettings *settings = NULL;
	struct weaponfunc *func = gsetGetWeaponFunction(gset);

	if (func != NULL) {
		settings = func->noisesettings;
	}

	if (settings == NULL) {
		settings = &invnoisesettings_00010fd0;
	}

	dst->minradius = settings->minradius;
	dst->maxradius = settings->maxradius;
	dst->incradius = settings->incradius;
	dst->unk0c = settings->unk0c;
	dst->unk10 = settings->unk10;
}

struct guncmd *handGetEquipAnim(struct gset *gset)
{
	struct weapon *weapon = g_Weapons[gset->weaponnum];

	if (weapon) {
		return weapon->equip_animation;
	}

	return NULL;
}

struct guncmd *handGetUnequipAnim(struct gset *gset)
{
	struct weapon *weapon = g_Weapons[gset->weaponnum];

	if (weapon) {
		return weapon->unequip_animation;
	}

	return NULL;
}

struct guncmd *gsetGetPriToSecAnim(struct gset *gset)
{
	struct weapon *weapon = g_Weapons[gset->weaponnum];

	if (weapon) {
		return weapon->pritosec_animation;
	}

	return NULL;
}

struct guncmd *gsetGetSecToPriAnim(struct gset *gset)
{
	struct weapon *weapon = g_Weapons[gset->weaponnum];

	if (weapon) {
		return weapon->sectopri_animation;
	}

	return NULL;
}
