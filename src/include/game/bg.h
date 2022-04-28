#ifndef IN_GAME_BG_H
#define IN_GAME_BG_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void roomUnpauseProps(u32 roomnum, bool tintedglassonly);
void func0f157e94(s32 room, s32 draworder, struct screenbox *arg2);
void func0f158108(s32 roomnum, u8 *arg1, u8 *arg2);
struct var800a4640_00 *func0f158140(s32 roomnum);
u32 func0f158184(void);
u32 func0f158400(void);
u32 func0f158884(void);
u32 func0f158d9c(void);
u32 func0f1598b4(void);
Gfx *func0f159f1c(Gfx *gdl, s32 roomnum, struct roomgfxdata18 *arg2, s32 arg3, s16 arg4[3]);
Gfx *bgRenderRoomInXray(Gfx *gdl, s32 roomnum);
Gfx *bgRenderSceneInXray(Gfx *gdl);
Gfx *bgRenderScene(Gfx *gdl);
Gfx *func0f15b114(Gfx *gdl);
void bgLoadFile(void *memaddr, u32 offset, u32 len);
s32 stageGetIndex2(s32 stagenum);
f32 portal0f15b274(s32 portal);
u8 func0f15b4c0(s32 portal);
u32 not(u32 arg);
u32 xorBabebabe(u32 value);
void bgReset(s32 stagenum);
void bgBuildTables(s32 stagenum);
void bgStop(void);
void func0f15c880(f32 arg0);
f32 func0f15c888(void);
f32 currentPlayerGetScaleBg2Gfx(void);
void currentPlayerSetScaleBg2Gfx(f32 arg0);
void func0f15c920(void);
void bgTick(void);
Gfx *bgRender(Gfx *gdl);
Gfx *currentPlayerScissorToViewport(Gfx *gdl);
Gfx *currentPlayerScissorWithinViewportF(Gfx *gdl, f32 viewleft, f32 viewtop, f32 viewright, f32 viewbottom);
Gfx *currentPlayerScissorWithinViewport(Gfx *gdl, s32 viewleft, s32 viewtop, s32 viewright, s32 viewbottom);
void func0f15cd28(void);
bool func0f15cd90(u32 room, struct screenbox *arg1);
bool func0f15d08c(struct coord *a, struct coord *b);
bool func0f15d10c(s32 portal, struct screenbox *arg1);
Gfx *boxRenderBorder(Gfx *gdl, s32 x1, s32 y1, s32 x2, s32 y2);
bool boxGetIntersection(struct screenbox *a, struct screenbox *b);
void boxExpand(struct screenbox *a, struct screenbox *b);
void boxCopy(struct screenbox *dst, struct screenbox *src);
bool roomIsVisibleByAnyPlayer(s32 room);
bool roomIsVisibleByAnyAibot(s32 room);
bool roomIsVisibleByPlayer(s32 room, u32 playernum);
bool roomIsVisibleByAibot(s32 room, u32 aibotindex);
s32 portalFindNumByVertices(struct portalvertices *pvertices);
u32 bgInflate(u8 *src, u8 *dst, u32 len);
Gfx *func0f15da00(struct roomgfxdata18 *arg0, Gfx *arg1, Gfx *arg2);
Gfx *room0f15dab4(s32 roomnum, Gfx *arg1, u32 arg2);
struct gfxvtx *room0f15dbb4(s32 roomnum, Gfx *gdl);
void roomLoad(s32 roomnum);
void roomUnload(s32 room);
void bgUnloadAllRooms(void);
void bgGarbageCollectRooms(s32 bytesneeded, bool desparate);
void bgTickRooms(void);
Gfx *room0f15e85c(Gfx *gdl, s32 roomnum, struct roomgfxdata18 *arg2, bool arg3);
Gfx *bgRenderRoomOpaque(Gfx *gdl, s32 roomnum);
Gfx *bgRenderRoomAlpha(Gfx *gdl, s32 roomnum);
s32 func0f15ecd8(s32 roomnum, void *allocation, Gfx *gdl, s32 arg3, struct gfxvtx *vtx, s32 arg5);
void room0f15ef9c(s32 roomnum);
bool func0f15f20c(struct coord *arg0, struct coord *arg1, s32 *arg2, s32 *arg3);
bool func0f15f2b0(struct coord *arg0, struct coord *arg1, struct coord *arg2, struct coord *arg3);
bool func0f15f560(struct coord *arg0, struct coord *arg1, struct coord *arg2, Gfx *arg3, void *arg4, struct gfxvtx *vertices, struct hitthing *hitthing);
bool func0f15ffdc(struct model *model, struct coord *arg1, struct coord *arg2, struct coord *arg3, Gfx *arg4, Gfx *arg5, struct gfxvtx *vertices, f32 *arg7, void *arg8);
u32 func0f160a38(void);
u32 func0f1612e4(void);
bool func0f161520(struct coord *arg0, struct coord *arg1, s16 room, void *arg3);
bool roomIsLoaded(s32 room);
bool roomContainsCoord(struct coord *pos, s16 roomnum);
bool func0f161c08(struct coord *arg0, s16 roomnum);
bool func0f161d30(struct coord *arg0, s16 roomnum);
bool func0f162128(struct coord *arg0, s16 roomnum);
void bgFindRoomsByPos(struct coord *pos, s16 *inrooms, s16 *aboverooms, s32 max, s16 *bestroom);
bool portalPushValue(bool value);
bool portalPopValue(void);
bool portalGetNthValueFromEnd(s32 offset);
struct portalcmd *portalCommandsExecute(struct portalcmd *cmd, bool s2);
struct portalcmd *portalCommandsExecuteForCurrentPlayer(struct portalcmd *cmd);
u32 func0f162d9c(void);
void func0f1632d4(s16 roomnum1, s16 roomnum2, s16 draworder, struct screenbox *box);
void func0f163528(struct var800a4d00 *arg0);
bool func0f163904(void);
u32 func0f16397c(void);
void bgTickPortals(void);
Gfx *func0f164150(Gfx *gdl);
s32 roomsGetActive(s16 *rooms, s32 len);
s32 roomGetNeighbours(s32 room, s16 *rooms, s32 len);
bool roomsAreNeighbours(s32 roomnum1, s32 roomnum2);
void currentPlayerCalculateScreenProperties(void);
void bgExpandRoomToPortals(s32 roomnum);
void portalSwapRooms(u32 portal);
void func0f164ab8(s32 portalnum);
void room0f164c64(s32 roomnum);
void portalSetEnabled(s32 portal, bool enable);
s32 func0f164e8c(struct coord *arg0, struct coord *arg1);
bool func0f164f9c(struct coord *arg0, struct coord *arg1, struct coord *arg2, struct coord *arg3);
void portalFindBbox(s32 portalnum, struct coord *bbmin, struct coord *bbmax);
void func0f1650d0(struct coord *lower, struct coord *upper, s16 *rooms, s32 arg3, s32 arg4);

#endif
