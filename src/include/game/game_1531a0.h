#ifndef _IN_GAME_GAME_1531A0_H
#define _IN_GAME_GAME_1531A0_H
#include <ultra64.h>
#include "data.h"
#include "types.h"

void fontsInit(void);
void textSetRotation90(bool rotated);
void func0f1531c4(s32 arg0);
void func0f1531d0(s32 arg0);
void func0f1531dc(bool arg0);
void fontLoad(u8 *romstart, u8 *romend, struct font **fontptr, struct fontchar **charsptr, bool monospace);
void fontsReset(void);
Gfx *func0f153628(Gfx *gdl);
Gfx *func0f153780(Gfx *gdl);
Gfx *gfxSetPrimColour(Gfx *gdl, u32 colour);
Gfx *func0f153838(Gfx *gdl);
Gfx *func0f153858(Gfx *gdl, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
Gfx *func0f1538e4(Gfx *gdl, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
Gfx *func0f153990(Gfx *gdl, s32 left, s32 top, s32 width, s32 height);
Gfx *func0f153a34(Gfx *gdl, s32 x1, s32 y1, s32 x2, s32 y2, u32 colour);
Gfx *func0f153ab0(Gfx *gdl);
void func0f153b40(void);
void func0f153b6c(s32 arg0);
void func0f153c20(s32 x, s32 y, f32 redrawtimer, u8 populated);
void func0f153c50(void);
void func0f153c88(void);
void func0f153ce8(s32 x1, s32 x2, u32 arg2);
void func0f153d24(void);
void func0f153d3c(void);
void func0f153d50(s32 arg0, s32 arg1, s32 cthresh);
void func0f153d88(f32 arg0);
void func0f153e38(u32 colour1, u32 colour2);
void func0f153e4c(void);
bool func0f153e58(void);
u32 func0f153e94(s32 x, s32 y, u32 colour);
u32 func0f1543ac(s32 arg0, s32 arg1, u32 colour);
Gfx *func0f154ecc(Gfx *gdl, u32 arg1, u32 arg2);
u32 func0f154f38(void);
Gfx *func0f1552d4(Gfx *gdl, f32 x, f32 y, f32 widthscale, f32 heightscale, char *text, struct fontchar *chars, struct font *font, u32 colour, s32 hdir, s32 vdir);
u32 func0f15568c(void);
void func0f156024(s32 arg0);
void func0f156030(u32 colour);
Gfx *textRenderProjected(Gfx *gdl, s32 *x, s32 *y, char *text, struct fontchar *font1, struct font *font2, s32 colour, s16 width, s16 height, s32 arg9, u32 arg10);
Gfx *func0f1566cc(Gfx *gdl, u32 arg1, u32 arg2);
u32 func0f156790(void);
u32 func0f156a24(void);
Gfx *textRender(Gfx *gdl, s32 *x, s32 *y, char *text, struct fontchar *font1, struct font *font2, u32 arg6, u32 colour, s16 arg8, s16 arg9, u32 arg10, u32 arg11);
void textMeasure(s32 *textheight, s32 *textwidth, char *text, struct fontchar *font1, struct font *font2, s32 lineheight);
void textWrap(s32 width, char *in, char *out, struct fontchar *font1, struct font *font2);

Gfx *func0f1574d0jf(Gfx *gdl, s32 *x, s32 *y, char *text, struct fontchar *font1, struct font *font2, s32 colour, u32 colour2, s32 width, s32 height, s32 arg9, u32 arg10);

#endif
