#ifndef IN_GAME_GAME_00C490_H
#define IN_GAME_GAME_00C490_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void setupInit(void);
void addLiftDoor(struct linkliftdoorobj *link);
void addPadlockedDoor(struct padlockeddoorobj *link);
void addSafeItem(struct safeitemobj *link);
void addConditionalScenery(struct linksceneryobj *link);
void addBlockedPath(struct blockedpathobj *link);
void func0f00cc8c(void);
void setupClearProxyMines(void);
s32 setupCountCommandType(u32 type);
void setupGenericObject(struct defaultobj *obj, s32 cmdindex);
void weaponAssignToHome(struct weaponobj *weapon, s32 cmdindex);
void setupHat(struct hatobj *hat, s32 cmdindex);
void setupKey(struct keyobj *key, s32 cmdindex);
void setupMine(struct mineobj *mine, s32 cmdindex);
void setupCctv(struct cctvobj *camera, s32 cmdindex);
void setupAutogun(struct autogunobj *autogun, s32 cmdindex);
void setupHangingMonitors(struct hangingmonitorsobj *monitors, s32 cmdindex);
void setupSingleMonitor(struct singlemonitorobj *monitor, s32 cmdindex);
void setupMultiMonitor(struct multimonitorobj *monitor, s32 cmdindex);
s32 func0f00e1f8(s32 padnum);
s32 func0f00e2b0(s32 padnum);
void setupDoor(struct doorobj *door, s32 cmdindex);
void setupHov(struct defaultobj *obj, struct hov *hov);
void setupLoadBriefing(s32 stagenum, u8 *buffer, s32 bufferlen, struct briefing *briefing);
void setupLoadFiles(s32 stagenum);
void setupParseObjects(s32 stagenum);

#endif
