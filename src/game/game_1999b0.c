#include <ultra64.h>
#include "constants.h"
#include "game/chr/chraction.h"
#include "game/debug.h"
#include "game/chr/chr.h"
#include "game/game_092610.h"
#include "game/bondgun.h"
#include "game/game_0b0fd0.h"
#include "game/game_127910.h"
#include "game/game_1999b0.h"
#include "game/pad.h"
#include "game/padhalllv.h"
#include "game/propobj.h"
#include "bss.h"
#include "lib/rng.h"
#include "lib/mtx.h"
#include "lib/anim.h"
#include "lib/collision.h"
#include "data.h"
#include "types.h"

s32 weaponGetAmmoTypeByFunction(s32 weaponnum, u32 funcnum)
{
	if (weaponnum >= WEAPON_FALCON2 && weaponnum <= WEAPON_SUICIDEPILL) {
		struct inventory_ammo *ammo = weaponGetAmmoByFunction(weaponnum, funcnum);

		if (ammo) {
			return ammo->type;
		}
	}

	return 0;
}

s32 weaponGetClipCapacityByFunction(s32 weaponnum, u32 funcnum)
{
	if (weaponnum >= WEAPON_FALCON2 && weaponnum <= WEAPON_SUICIDEPILL) {
		struct inventory_ammo *ammo = weaponGetAmmoByFunction(weaponnum, funcnum);

		if (ammo) {
			return ammo->clipsize;
		}
	}

	return 0;
}

void aibotReloadWeapon(struct chrdata *chr, s32 handnum, bool withsound)
{
	struct aibot *aibot = chr->aibot;
	aibot->unk02c[handnum] = 0;
	aibot->unk0e4[handnum] = 0;

	if (chr->weapons_held[handnum]
			&& func0f19a29c(aibot->weaponnum, aibot->gunfunc) == 0) {
		s32 capacity = weaponGetClipCapacityByFunction(aibot->weaponnum, aibot->gunfunc);

		if (capacity > 0) {
			s32 tryamount = capacity - aibot->loadedammo[handnum];
			s32 actualamount = aibotTryRemoveAmmoFromReserve(aibot, aibot->weaponnum, aibot->gunfunc, tryamount);

			if (actualamount > 0) {
				aibot->loadedammo[handnum] += actualamount;

				if (withsound) {
					if (aibot->weaponnum == WEAPON_FARSIGHT) {
						// FarSight reload sound
						func0f0939f8(NULL, chr->prop, SFX_RELOAD_FARSIGHT, -1,
								-1, 1024, 0, 0, 0, -1, 0, -1, -1, -1, -1);
					} else {
						// Normal reload sound
						func0f0939f8(NULL, chr->prop, SFX_RELOAD_DEFAULT, -1,
								-1, 1024, 0, 0, 0, -1, 0, -1, -1, -1, -1);
					}
				}
			}
		}
	}
}

s32 aibotGetAmmoQuantityByWeapon(struct aibot *aibot, s32 weaponnum, s32 funcnum, bool include_equipped)
{
	s32 qty = 0;
	s32 ammotype;
	s32 equippedammotype;

	if (aibot) {
		if (aibot->unk064 & 1) {
			ammotype = weaponGetAmmoTypeByFunction(weaponnum, funcnum);
			qty = bgunGetCapacityByAmmotype(ammotype);
		} else {
			ammotype = weaponGetAmmoTypeByFunction(weaponnum, funcnum);
			qty = aibot->ammoheld[ammotype];
		}

		if (include_equipped) {
			ammotype = weaponGetAmmoTypeByFunction(weaponnum, funcnum);
			equippedammotype = weaponGetAmmoTypeByFunction(aibot->weaponnum, aibot->gunfunc);

			if (equippedammotype == ammotype) {
				qty += aibot->loadedammo[HAND_LEFT] + aibot->loadedammo[HAND_RIGHT];
			}
		}
	}

	return qty;
}

s32 aibotGetAmmoQuantityByType(struct aibot *aibot, s32 ammotype, bool include_equipped)
{
	s32 qty = 0;

	if (aibot) {
		if (aibot->unk064 & 1) {
			qty = bgunGetCapacityByAmmotype(ammotype);
		} else {
			qty = aibot->ammoheld[ammotype];
		}

		if (include_equipped
				&& weaponGetAmmoTypeByFunction(aibot->weaponnum, aibot->gunfunc) == ammotype) {
			qty += aibot->loadedammo[HAND_LEFT] + aibot->loadedammo[HAND_RIGHT];
		}
	}

	return qty;
}

/**
 * Attempt to remove the given quantity of ammo from the aibot's reserve and
 * return the amount actually removed.
 *
 * The amount removed will be less than the attempted amount if the aibot
 * doesn't have enough ammo in reserve.
 */
s32 aibotTryRemoveAmmoFromReserve(struct aibot *aibot, s32 weaponnum, s32 funcnum, s32 tryqty)
{
	s32 result;
	s32 *ammoheld = &aibot->ammoheld[weaponGetAmmoTypeByFunction(weaponnum, funcnum)];

	if (!aibot || *ammoheld <= 0 || tryqty <= 0) {
		return 0;
	}

	if (aibot->unk064 & 1) {
		return tryqty;
	}

	dprint();
	*ammoheld -= tryqty;

	if (*ammoheld < 0) {
		result = tryqty + *ammoheld;
		*ammoheld = 0;

		if (dprint()) {
			return result;
		}
	} else {
		result = tryqty;
		dprint();
	}

	return result;
}

void aibotGiveAmmoByWeapon(struct aibot *aibot, s32 weaponnum, s32 funcnum, s32 qty)
{
	s32 max;
	s32 *heldquantity = &aibot->ammoheld[weaponGetAmmoTypeByFunction(weaponnum, funcnum)];

	if (aibot && (aibot->unk064 & 1) == 0 && qty > 0) {
		dprint();
		*heldquantity += qty;

		if (heldquantity);

		max = bgunGetCapacityByAmmotype(weaponGetAmmoTypeByFunction(weaponnum, funcnum));

		if (*heldquantity > max) {
			*heldquantity = max;
		}

		dprint();
	}
}

void aibotGiveAmmoByType(struct aibot *aibot, u32 ammotype, s32 quantity)
{
	s32 max;
	s32 *heldquantity = &aibot->ammoheld[ammotype];

	if (!aibot || (aibot->unk064 & 1) || quantity <= 0) {
		return;
	}

	dprint();

	*heldquantity += quantity;

	if (heldquantity);

	max = bgunGetCapacityByAmmotype(ammotype);

	if (*heldquantity > max) {
		*heldquantity = max;
	}

	dprint();
}

/**
 * This function appears to handle aibots shooting chrs with the Farsight, but
 * is called conditionally and I haven't determined what those conditions are.
 */
bool aibotDoFarsightThing(struct chrdata *chr, u32 arg1, struct coord *vector, struct coord *arg3)
{
	struct aibot *aibot;
	struct chrdata *oppchr;
	struct prop *oppprop;
	s32 i;
	s32 rand;
	f32 speed;

	if (!chr || !chr->aibot) {
		return false;
	}

	aibot = chr->aibot;

	if (aibot->weaponnum == WEAPON_FARSIGHT) {
		rand = random() % 100;

		// 3 in 10 chance of this passing
		if (rand < 30) {
			struct modelnode *node = NULL;
			struct model *model = NULL;
			s32 side = -1;
			s32 hitpart = HITPART_GENERAL;
			struct gset gset = {WEAPON_FARSIGHT, 0, 0, FUNC_PRIMARY};
			f32 damage = gsetGetDamage(&gset);
			s32 fallback = 30;
			s32 value = fallback;

			for (i = 0; i < g_MpNumPlayers; i++) {
				oppchr = g_MpPlayerChrs[i];
				oppprop = g_MpPlayerChrs[i]->prop;

				if (oppprop->type == PROPTYPE_PLAYER) {
					struct player *player = g_Vars.players[propGetPlayerNum(oppprop)];
					speed = player->speedforwards * player->speedforwards
							+ player->speedsideways * player->speedsideways;

					if (speed > 0) {
						value = fallback * 0.05f;
					}
				} else {
					if (oppchr->actiontype != ACT_STAND) {
						value = fallback * 0.05f;
					}
				}

				// value is 30 if player was still, or 1.5 if moving. So if 30
				// then this will always pass, or if 1.5 then this has 1 in 15
				// chance of passing.
				if (oppchr != chr
						&& value > rand
						&& func0f06b39c(arg3, vector, &oppprop->pos, func0f0278a4(oppchr))) {
					bgunPlayPropHitSound(&gset, oppprop, -1);

					if (oppchr->model && chrGetShield(oppchr) > 0) {
						chrCalculateShieldHit(oppchr, &oppprop->pos, vector, &node, &hitpart, &model, &side);
					}

					chrEmitSparks(oppchr, oppprop, hitpart, &oppprop->pos, vector, chr);
					func0f0341dc(oppchr, damage, vector, &gset, chr->prop, HITPART_GENERAL, oppprop, node, model, side, 0);
				}
			}

			return true;
		}

		return false;
	}

	return true;
}

s32 func0f19a27c(s32 weapon)
{
	return weaponGetModel(weapon);
}

bool func0f19a29c(u32 weaponnum, bool is_secondary)
{
	switch (weaponnum) {
	case WEAPON_LAPTOPGUN:
	case WEAPON_DRAGON:
	case WEAPON_COMBATKNIFE:
		return is_secondary;
	case WEAPON_GRENADE:
	case WEAPON_NBOMB:
	case WEAPON_TIMEDMINE:
	case WEAPON_PROXIMITYMINE:
	case WEAPON_REMOTEMINE:
		return true;
	}

	return false;
}

u32 aibotGetProjectileThrowInterval(u32 weapon)
{
	switch (weapon) {
	case WEAPON_COMBATKNIFE:
		return PALDOWN(120);
	case WEAPON_GRENADE:
	case WEAPON_NBOMB:
		return PALDOWN(90);
	case WEAPON_CROSSBOW:
	case WEAPON_TRANQUILIZER:
	case WEAPON_LASER:
	case WEAPON_TIMEDMINE:
	case WEAPON_PROXIMITYMINE:
	case WEAPON_REMOTEMINE:
	default:
		return PALDOWN(60);
	}
}

u32 ammotypeGetWeapon(u32 ammotype)
{
	switch (ammotype) {
	case AMMOTYPE_NBOMB:       return WEAPON_NBOMB;
	case AMMOTYPE_GRENADE:     return WEAPON_GRENADE;
	case AMMOTYPE_KNIFE:       return WEAPON_COMBATKNIFE;
	case AMMOTYPE_REMOTE_MINE: return WEAPON_REMOTEMINE;
	case AMMOTYPE_PROXY_MINE:  return WEAPON_PROXIMITYMINE;
	case AMMOTYPE_TIMED_MINE:  return WEAPON_TIMEDMINE;
	}

	return 0;
}

void func0f19a37c(struct chrdata *chr)
{
	struct coord sp228 = {0, 0, 0};
	Mtxf sp164;
	f32 sp152[3];
	struct prop *prop = chr->prop;
	Mtxf sp84;
	f32 sp80 = chrGetAimAngle(chr);
	u32 stack;
	struct gset gset = {0};
	struct prop *target = chrGetTargetProp(chr);
	struct coord sp56;
	f32 mult;

	gset.weaponnum = chr->aibot->weaponnum;
	gset.weaponfunc = chr->aibot->gunfunc;

	if (chrIsTargetInFov(chr, WEAPON_GRENADE, 0)) {
		sp56.x = target->pos.x;
		sp56.z = target->pos.z;

		if (chr->aibot->weaponnum == WEAPON_GRENADE || chr->aibot->weaponnum == WEAPON_NBOMB) {
			sp56.y = target->chr->manground;
		} else {
			sp56.y = target->pos.y;

			if (target->type == PROPTYPE_PLAYER) {
				sp56.y -= 25.0f;
			}
		}

		func0f04031c(&prop->pos, 16.666666f, &sp56, sp152);
	} else {
		// These numbers are about 2 billionths away from BADDEG2RAD(20),
		// but tweaking the multiplier in BADDEG2RAD doesn't make this match
		// without creating mismatches in other places :(
		sp152[0] = cosf(0.34901028871536f) * sinf(sp80);
		sp152[1] = sinf(0.34901028871536f);
		sp152[2] = cosf(0.34901028871536f) * cosf(sp80);
	}

	mult = 16.666666f;

	sp228.x = sp152[0] * mult;
	sp228.y = sp152[1] * mult;
	sp228.z = sp152[2] * mult;

	mtx000159b0(&sp164);

	if (chr->aibot->weaponnum == WEAPON_COMBATKNIFE) {
		mtx00016400(M_BADPI * 1.5f, &sp164);
		mtx000162e8(M_BADPI, &sp84);
		mtx000159fc(&sp84, &sp164);
	}

	mtx000162e8(0.34901028871536f, &sp84);
	mtx00015be0(&sp84, &sp164);
	mtx00016374(sp80, &sp84);
	mtx00015be0(&sp84, &sp164);

	bgun0f09ee18(chr, &gset, &prop->pos, prop->rooms, &sp164, &sp228);

	if (gset.weaponnum == WEAPON_REMOTEMINE) {
		chr->aibot->unk064 |= 0x1000;
	}
}

s32 func0f19a60c(s32 weaponnum, s32 funcnum)
{
	s32 stack[2];
	s32 iVar4 = 1;
	struct weapon *weapon = weaponFindById(weaponnum);

	if (weapon) {
		struct weaponfunc *func = weapon->functions[funcnum];

		if (func) {
			if (func->type == INVENTORYFUNCTYPE_SHOOT_SINGLE) {
				struct weaponfunc_shoot *func2 = (struct weaponfunc_shoot *)func;
				iVar4 = func2->unk24 + func2->unk25;
			} else if (func->type == INVENTORYFUNCTYPE_SHOOT_AUTOMATIC) {
				struct weaponfunc_shoot *func2 = (struct weaponfunc_shoot *)func;
				iVar4 = func2->unk24 + func2->unk25;
			} else if (func->type == INVENTORYFUNCTYPE_SHOOT_PROJECTILE) {
				struct weaponfunc_shoot *func2 = (struct weaponfunc_shoot *)func;
				iVar4 = func2->unk24 + func2->unk25;
			} else if (func->type == INVENTORYFUNCTYPE_CLOSE && weaponnum != WEAPON_REAPER) {
				iVar4 = 60;
			}
		}
	}

	return iVar4;
}

bool func0f19a6d0(struct chrdata *chr, struct coord *frompos, struct coord *topos, s16 *fromrooms, s16 *torooms, struct projectile *projectile)
{
	struct waypoint *from = waypointFindClosestToPos(frompos, fromrooms);
	struct waypoint *to = waypointFindClosestToPos(topos, torooms);
	struct waypoint *waypoints[6];
	s32 numwaypoints;

	if (from && to) {
		s32 hash = (g_Vars.lvframe60 >> 9) * 128 + chr->chrnum * 8;

		waypointSetHashThing(hash, hash);
		numwaypoints = waypointFindRoute(from, to, waypoints, 6);
		waypointSetHashThing(0, 0);

		if (numwaypoints > 1) {
			s32 i = 0;

			while (waypoints[i]) {
				projectile->waypads[i] = waypoints[i]->padnum;
				i++;
			}

			projectile->unk105 = 0;
			projectile->numwaypads = i;

			return true;
		}
	}

	return false;
}

void func0f19a7d0(u16 padnum, struct coord *pos)
{
	struct pad pad;
	s16 rooms[2];

	padUnpack(padnum, PADFIELD_ROOM | PADFIELD_POS, &pad);

	rooms[0] = pad.room;
	rooms[1] = -1;

	pos->x = pad.pos.x;
	pos->y = cd0002a36c(&pad.pos, rooms, 0, 0) + 150;
	pos->z = pad.pos.z;
}

void aibotCreateSlayerRocket(struct chrdata *chr)
{
	struct weaponobj *rocket = func0f08b880(MODEL_CHRSKROCKETMIS, WEAPON_SKROCKET, chr);

	if (rocket) {
		Mtxf sp260;
		Mtxf sp196;
		Mtxf sp132;
		struct coord sp120 = {0, 0, 0};
		f32 a;
		f32 b;
		f32 sp100[3];

		a = chrGetAimAngle(chr);
		b = func0f03e754(chr);

		sp100[0] = cosf(b) * sinf(a);
		sp100[1] = sinf(b);
		sp100[2] = cosf(b) * cosf(a);

		mtx000162e8(b, &sp196);
		mtx00016374(a, &sp132);
		mtx00015be0(&sp132, &sp196);
		mtx000159b0(&sp260);

		bgun0f09ebcc(&rocket->base, &chr->prop->pos, chr->prop->rooms, &sp196, sp100, &sp260, chr->prop, &chr->prop->pos);

		if (rocket->base.hidden & OBJHFLAG_AIRBORNE) {
			struct prop *target = chrGetTargetProp(chr);
			rocket->timer240 = -1;
			rocket->base.projectile->unk010 = 7.5;
			rocket->base.projectile->unk014 = b;
			rocket->base.projectile->unk018 = a;
			rocket->base.projectile->unk0f4 = 0;
			rocket->base.projectile->unk0b4 = 0x20000000;

			// Fire rocket sound
			func0f0939f8(NULL, rocket->base.prop, SFX_LAUNCH_ROCKET_8053, -1,
					-1, 0, 0, 0, 0, -1, 0, -1, -1, -1, -1);

			if (!func0f19a6d0(chr, &chr->prop->pos, &target->pos, chr->prop->rooms, target->rooms, rocket->base.projectile)) {
				rocket->timer240 = 0; // blow up rocket
			} else {
				func0f19a7d0(rocket->base.projectile->waypads[0], &rocket->base.projectile->pos);
				chr->aibot->skrocket = rocket->base.prop;
			}
		}
	}
}
