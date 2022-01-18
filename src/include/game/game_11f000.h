#ifndef _IN_GAME_GAME_11F000_H
#define _IN_GAME_GAME_11F000_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

u32 func0f11f000(void);
u32 func0f11f07c(void);
u32 func0f11f1fc(void);
void func0f11f384(struct coord *arg0, struct coord *arg1, struct coord *out);
f32 func0f11f3d0(f32 value, f32 min, f32 max);
f32 func0f11f410(f32 value);
u32 func0f11f438(void);
u32 func0f11f6ec(void);
Gfx *func0f11f984(Gfx *gdl);
u32 func0f1228d0(void);
u32 func0f122ce8(void);
u32 func0f122d4c(void);
u32 func0f123fd4(void);
u32 func0f125948(void);
f32 func0f125a1c(struct bootbufferthingdeep *arg0);
u32 func0f125a6c(void);
Gfx *func0f126384(Gfx *gdl, u32 arg1, u32 arg2, f32 arg3, f32 orbsize, u32 arg5, f32 arg6);
u32 func0f126c3c(void);
Gfx *func0f126de8(Gfx *gdl);
Gfx *func0f12715c(Gfx *gdl);
void func0f127334(s32 arg0, s32 arg1, s32 arg2);
s32 func0f127490(s32 arg0, s32 arg1);
Gfx *func0f1274d8(Gfx *gdl);

#endif
