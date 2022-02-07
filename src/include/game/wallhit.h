#ifndef _IN_GAME_WALLHIT_H
#define _IN_GAME_WALLHIT_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

s16 func0f13e0e0(f32 arg0);
void func0f13e1b0(struct var800a41b0 *arg0);
void func0f13e40c(struct prop *prop, s8 arg1);
bool chrIsUsingPaintball(struct chrdata *chr);
void func0f13e5c8(struct prop *prop);
void func0f13e640(struct var800a41b0 *thing, u32 arg1);
u32 func0f13e744(void);
u32 func0f13e994(void);
void func0f13eb44(void);
void func0f13f3f4(struct coord *arg0, struct coord *arg1, struct coord *arg2, u32 arg3, u32 arg4, u32 arg5, s32 room, struct prop *arg7, s32 arg8, u32 arg9, struct chrdata *chr, bool arg11);
u32 func0f13f504(void);
s32 func0f140750(struct coord *coord);
Gfx *func0f1408a8(s32 roomnum, Gfx *gdl);
Gfx *func0f140b7c(s32 roomnum, Gfx *gdl);
Gfx *func0f140e20(Gfx *gdl, struct prop *prop, bool withalpha);
Gfx *wallhitsRender(s32 roomnum, Gfx *gdl);
void func0f141234(void);
void func0f14159c(struct prop *prop);
void func0f141704(struct prop *prop);

#endif
