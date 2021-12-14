#ifndef _IN_GAME_SPLAT_H
#define _IN_GAME_SPLAT_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void splatTick(struct prop *prop);
void splatsCreateForChrHit(struct prop *prop, struct splat *arg1, struct coord *arg2, struct coord *arg3, s32 arg4, s32 arg5, struct chrdata *arg6);
s32 splatsCreate(s32 qty, f32 arg1, struct prop *prop, struct splat *arg3, struct coord *arg4, struct coord *arg5, s32 arg6, s32 arg7, s32 arg8, struct chrdata *arg9, s32 arg10);
bool func0f149274(f32 arg0, struct prop *prop, struct splat *arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, struct chrdata *arg7, s32 arg8);
void func0f149864(void);
u32 func0f14986c(void);
void chrInitSplats(struct chrdata *chr);
void func0f14a3bc(void);

#endif
