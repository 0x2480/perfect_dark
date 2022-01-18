#include <ultra64.h>
#include "constants.h"
#include "game/game_096ca0.h"
#include "game/game_0b2150.h"
#include "game/game_0b4950.h"
#include "game/game_11f000.h"
#include "game/game_152fa0.h"
#include "game/game_1657c0.h"
#include "game/pad.h"
#include "bss.h"
#include "lib/vi.h"
#include "lib/mtx.h"
#include "lib/sched.h"
#include "data.h"
#include "types.h"

u32 var800a33a0;
u32 var800a33a4;
u32 var800a33a8;
u32 var800a33ac;
u32 var800a33b0;
u32 var800a33b4;
u32 var800a33b8;
u32 var800a33bc;
u32 var800a33c0;
u32 var800a33c4;
u32 var800a33c8;
u32 var800a33cc;
u32 var800a33d0;
u32 var800a33d4;
u32 var800a33d8;
u32 var800a33dc;
u32 var800a33e0;
u32 var800a33e4;
f32 var800a33e8[1][3];
u32 var800a33f4;
u32 var800a33f8;
u32 var800a33fc;
u32 var800a3400;
u32 var800a3404;
u32 var800a3408;
u32 var800a340c;
f32 var800a3410[1];
u32 var800a3414;
u32 var800a3418;
u32 var800a341c;
f32 var800a3420[1];
u32 var800a3424;
u32 var800a3428;
u32 var800a342c;

f32 var8007db80 = 0;
f32 var8007db84 = 1;
f32 var8007db88[1] = {0};
u32 var8007db8c = 0x00000000;
u32 var8007db90 = 0x00000000;
u32 var8007db94[1] = {0};
u32 var8007db98 = 0x00000000;
u32 var8007db9c = 0x00000000;
u32 var8007dba0 = 0x00000010;
u32 var8007dba4 = 0x00000020;
u32 var8007dba8 = 0x0000000c;
u32 var8007dbac = 0x00000020;
u32 var8007dbb0 = 0x00000018;
u32 var8007dbb4 = 0x00000040;
u32 var8007dbb8 = 0x0000003c;
u32 var8007dbbc = 0x00000050;
u32 var8007dbc0 = 0x000000e1;
u32 var8007dbc4 = 0x00000113;
u32 var8007dbc8 = 0x000001d6;
u32 var8007dbcc = 0x0000023a;
u32 var8007dbd0 = 0xff99ffff;
u32 var8007dbd4 = 0x9999ffff;
u32 var8007dbd8 = 0x99ffffff;
u32 var8007dbdc = 0x99ff99ff;
u32 var8007dbe0 = 0xffff99ff;
u32 var8007dbe4 = 0xff9999ff;
struct coord g_TeleportToPos = {0, 0, 0};
struct coord g_TeleportToUp = {0, 0, 1};
struct coord g_TeleportToLook = {0, 1, 0};

void func0f11f000(f32 left, f32 top, struct coord *arg2)
{
	Mtxf *mtx = currentPlayerGetUnk174c();
	f32 pos[2];

	pos[0] = left + currentPlayerGetScreenLeft();
	pos[1] = top + currentPlayerGetScreenTop() + skyGetCurrent()->unk40;

	func0f0b4c3c(pos, arg2, 100);
	mtx4RotateVecInPlace(mtx, arg2);
}

GLOBAL_ASM(
glabel func0f11f07c
.late_rodata
glabel var7f1b4fe0
.word 0x38d1b717
glabel var7f1b4fe4
.word 0x3c23d70a
glabel var7f1b4fe8
.word 0x48927c00
.text
/*  f11f07c:	27bdffc8 */ 	addiu	$sp,$sp,-56
/*  f11f080:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f11f084:	afb10018 */ 	sw	$s1,0x18($sp)
/*  f11f088:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f11f08c:	afa5003c */ 	sw	$a1,0x3c($sp)
/*  f11f090:	afa60040 */ 	sw	$a2,0x40($sp)
/*  f11f094:	c4800008 */ 	lwc1	$f0,0x8($a0)
/*  f11f098:	c48e0000 */ 	lwc1	$f14,0x0($a0)
/*  f11f09c:	3c11800a */ 	lui	$s1,%hi(g_Vars+0x284)
/*  f11f0a0:	46000102 */ 	mul.s	$f4,$f0,$f0
/*  f11f0a4:	3c017f1b */ 	lui	$at,%hi(var7f1b4fe0)
/*  f11f0a8:	8e31a244 */ 	lw	$s1,%lo(g_Vars+0x284)($s1)
/*  f11f0ac:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*  f11f0b0:	c42a4fe0 */ 	lwc1	$f10,%lo(var7f1b4fe0)($at)
/*  f11f0b4:	00808025 */ 	or	$s0,$a0,$zero
/*  f11f0b8:	26311bb0 */ 	addiu	$s1,$s1,7088
/*  f11f0bc:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f11f0c0:	0c012974 */ 	jal	sqrtf
/*  f11f0c4:	460a4300 */ 	add.s	$f12,$f8,$f10
/*  f11f0c8:	c6020004 */ 	lwc1	$f2,0x4($s0)
/*  f11f0cc:	3c013f80 */ 	lui	$at,0x3f80
/*  f11f0d0:	44817000 */ 	mtc1	$at,$f14
/*  f11f0d4:	46021100 */ 	add.s	$f4,$f2,$f2
/*  f11f0d8:	3c017f1b */ 	lui	$at,%hi(var7f1b4fe4)
/*  f11f0dc:	00001025 */ 	or	$v0,$zero,$zero
/*  f11f0e0:	46002303 */ 	div.s	$f12,$f4,$f0
/*  f11f0e4:	460c703c */ 	c.lt.s	$f14,$f12
/*  f11f0e8:	00000000 */ 	nop
/*  f11f0ec:	45020003 */ 	bc1fl	.L0f11f0fc
/*  f11f0f0:	460c7181 */ 	sub.s	$f6,$f14,$f12
/*  f11f0f4:	46007306 */ 	mov.s	$f12,$f14
/*  f11f0f8:	460c7181 */ 	sub.s	$f6,$f14,$f12
.L0f11f0fc:
/*  f11f0fc:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f11f100:	44800000 */ 	mtc1	$zero,$f0
/*  f11f104:	e5c60000 */ 	swc1	$f6,0x0($t6)
/*  f11f108:	c6020004 */ 	lwc1	$f2,0x4($s0)
/*  f11f10c:	46020032 */ 	c.eq.s	$f0,$f2
/*  f11f110:	00000000 */ 	nop
/*  f11f114:	45020004 */ 	bc1fl	.L0f11f128
/*  f11f118:	46001406 */ 	mov.s	$f16,$f2
/*  f11f11c:	10000002 */ 	b	.L0f11f128
/*  f11f120:	c4304fe4 */ 	lwc1	$f16,%lo(var7f1b4fe4)($at)
/*  f11f124:	46001406 */ 	mov.s	$f16,$f2
.L0f11f128:
/*  f11f128:	4610003c */ 	c.lt.s	$f0,$f16
/*  f11f12c:	00000000 */ 	nop
/*  f11f130:	4500002d */ 	bc1f	.L0f11f1e8
/*  f11f134:	00000000 */ 	nop
/*  f11f138:	0fc595f3 */ 	jal	skyGetCurrent
/*  f11f13c:	e7b00024 */ 	swc1	$f16,0x24($sp)
/*  f11f140:	c4480014 */ 	lwc1	$f8,0x14($v0)
/*  f11f144:	c62a0004 */ 	lwc1	$f10,0x4($s1)
/*  f11f148:	c7b00024 */ 	lwc1	$f16,0x24($sp)
/*  f11f14c:	c6000008 */ 	lwc1	$f0,0x8($s0)
/*  f11f150:	460a4101 */ 	sub.s	$f4,$f8,$f10
/*  f11f154:	c60e0000 */ 	lwc1	$f14,0x0($s0)
/*  f11f158:	46000182 */ 	mul.s	$f6,$f0,$f0
/*  f11f15c:	00000000 */ 	nop
/*  f11f160:	460e7202 */ 	mul.s	$f8,$f14,$f14
/*  f11f164:	46102083 */ 	div.s	$f2,$f4,$f16
/*  f11f168:	46083300 */ 	add.s	$f12,$f6,$f8
/*  f11f16c:	0c012974 */ 	jal	sqrtf
/*  f11f170:	e7a2002c */ 	swc1	$f2,0x2c($sp)
/*  f11f174:	c7a2002c */ 	lwc1	$f2,0x2c($sp)
/*  f11f178:	3c017f1b */ 	lui	$at,%hi(var7f1b4fe8)
/*  f11f17c:	c4324fe8 */ 	lwc1	$f18,%lo(var7f1b4fe8)($at)
/*  f11f180:	46020302 */ 	mul.s	$f12,$f0,$f2
/*  f11f184:	c7b00024 */ 	lwc1	$f16,0x24($sp)
/*  f11f188:	460c903c */ 	c.lt.s	$f18,$f12
/*  f11f18c:	00000000 */ 	nop
/*  f11f190:	45020005 */ 	bc1fl	.L0f11f1a8
/*  f11f194:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f11f198:	460c9283 */ 	div.s	$f10,$f18,$f12
/*  f11f19c:	460a1082 */ 	mul.s	$f2,$f2,$f10
/*  f11f1a0:	00000000 */ 	nop
/*  f11f1a4:	c6040000 */ 	lwc1	$f4,0x0($s0)
.L0f11f1a8:
/*  f11f1a8:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f11f1ac:	8fa3003c */ 	lw	$v1,0x3c($sp)
/*  f11f1b0:	46022182 */ 	mul.s	$f6,$f4,$f2
/*  f11f1b4:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f11f1b8:	46083280 */ 	add.s	$f10,$f6,$f8
/*  f11f1bc:	46101182 */ 	mul.s	$f6,$f2,$f16
/*  f11f1c0:	e46a0000 */ 	swc1	$f10,0x0($v1)
/*  f11f1c4:	c6240004 */ 	lwc1	$f4,0x4($s1)
/*  f11f1c8:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f11f1cc:	e4680004 */ 	swc1	$f8,0x4($v1)
/*  f11f1d0:	c60a0008 */ 	lwc1	$f10,0x8($s0)
/*  f11f1d4:	c6260008 */ 	lwc1	$f6,0x8($s1)
/*  f11f1d8:	46025102 */ 	mul.s	$f4,$f10,$f2
/*  f11f1dc:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f11f1e0:	10000001 */ 	b	.L0f11f1e8
/*  f11f1e4:	e4680008 */ 	swc1	$f8,0x8($v1)
.L0f11f1e8:
/*  f11f1e8:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f11f1ec:	8fb00014 */ 	lw	$s0,0x14($sp)
/*  f11f1f0:	8fb10018 */ 	lw	$s1,0x18($sp)
/*  f11f1f4:	03e00008 */ 	jr	$ra
/*  f11f1f8:	27bd0038 */ 	addiu	$sp,$sp,0x38
);

GLOBAL_ASM(
glabel func0f11f1fc
.late_rodata
glabel var7f1b4fec
.word 0x38d1b717
glabel var7f1b4ff0
.word 0xbc23d70a
glabel var7f1b4ff4
.word 0x48927c00
.text
/*  f11f1fc:	27bdffc8 */ 	addiu	$sp,$sp,-56
/*  f11f200:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f11f204:	afb10018 */ 	sw	$s1,0x18($sp)
/*  f11f208:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f11f20c:	afa5003c */ 	sw	$a1,0x3c($sp)
/*  f11f210:	afa60040 */ 	sw	$a2,0x40($sp)
/*  f11f214:	c4800008 */ 	lwc1	$f0,0x8($a0)
/*  f11f218:	c48e0000 */ 	lwc1	$f14,0x0($a0)
/*  f11f21c:	3c11800a */ 	lui	$s1,%hi(g_Vars+0x284)
/*  f11f220:	46000102 */ 	mul.s	$f4,$f0,$f0
/*  f11f224:	3c017f1b */ 	lui	$at,%hi(var7f1b4fec)
/*  f11f228:	8e31a244 */ 	lw	$s1,%lo(g_Vars+0x284)($s1)
/*  f11f22c:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*  f11f230:	c42a4fec */ 	lwc1	$f10,%lo(var7f1b4fec)($at)
/*  f11f234:	00808025 */ 	or	$s0,$a0,$zero
/*  f11f238:	26311bb0 */ 	addiu	$s1,$s1,7088
/*  f11f23c:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f11f240:	0c012974 */ 	jal	sqrtf
/*  f11f244:	460a4300 */ 	add.s	$f12,$f8,$f10
/*  f11f248:	3c013f80 */ 	lui	$at,0x3f80
/*  f11f24c:	44816000 */ 	mtc1	$at,$f12
/*  f11f250:	3c01c000 */ 	lui	$at,0xc000
/*  f11f254:	44812000 */ 	mtc1	$at,$f4
/*  f11f258:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f11f25c:	3c017f1b */ 	lui	$at,%hi(var7f1b4ff0)
/*  f11f260:	00001025 */ 	or	$v0,$zero,$zero
/*  f11f264:	46062202 */ 	mul.s	$f8,$f4,$f6
/*  f11f268:	46004083 */ 	div.s	$f2,$f8,$f0
/*  f11f26c:	4602603c */ 	c.lt.s	$f12,$f2
/*  f11f270:	00000000 */ 	nop
/*  f11f274:	45020003 */ 	bc1fl	.L0f11f284
/*  f11f278:	46026281 */ 	sub.s	$f10,$f12,$f2
/*  f11f27c:	46006086 */ 	mov.s	$f2,$f12
/*  f11f280:	46026281 */ 	sub.s	$f10,$f12,$f2
.L0f11f284:
/*  f11f284:	8fae0040 */ 	lw	$t6,0x40($sp)
/*  f11f288:	44807000 */ 	mtc1	$zero,$f14
/*  f11f28c:	e5ca0000 */ 	swc1	$f10,0x0($t6)
/*  f11f290:	c6000004 */ 	lwc1	$f0,0x4($s0)
/*  f11f294:	46007032 */ 	c.eq.s	$f14,$f0
/*  f11f298:	00000000 */ 	nop
/*  f11f29c:	45020004 */ 	bc1fl	.L0f11f2b0
/*  f11f2a0:	46000406 */ 	mov.s	$f16,$f0
/*  f11f2a4:	10000002 */ 	b	.L0f11f2b0
/*  f11f2a8:	c4304ff0 */ 	lwc1	$f16,%lo(var7f1b4ff0)($at)
/*  f11f2ac:	46000406 */ 	mov.s	$f16,$f0
.L0f11f2b0:
/*  f11f2b0:	460e803c */ 	c.lt.s	$f16,$f14
/*  f11f2b4:	00000000 */ 	nop
/*  f11f2b8:	4500002d */ 	bc1f	.L0f11f370
/*  f11f2bc:	00000000 */ 	nop
/*  f11f2c0:	0fc595f3 */ 	jal	skyGetCurrent
/*  f11f2c4:	e7b00024 */ 	swc1	$f16,0x24($sp)
/*  f11f2c8:	c444002c */ 	lwc1	$f4,0x2c($v0)
/*  f11f2cc:	c6260004 */ 	lwc1	$f6,0x4($s1)
/*  f11f2d0:	c7b00024 */ 	lwc1	$f16,0x24($sp)
/*  f11f2d4:	c6000008 */ 	lwc1	$f0,0x8($s0)
/*  f11f2d8:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f11f2dc:	c60e0000 */ 	lwc1	$f14,0x0($s0)
/*  f11f2e0:	46000282 */ 	mul.s	$f10,$f0,$f0
/*  f11f2e4:	00000000 */ 	nop
/*  f11f2e8:	460e7102 */ 	mul.s	$f4,$f14,$f14
/*  f11f2ec:	46104083 */ 	div.s	$f2,$f8,$f16
/*  f11f2f0:	46045300 */ 	add.s	$f12,$f10,$f4
/*  f11f2f4:	0c012974 */ 	jal	sqrtf
/*  f11f2f8:	e7a2002c */ 	swc1	$f2,0x2c($sp)
/*  f11f2fc:	c7a2002c */ 	lwc1	$f2,0x2c($sp)
/*  f11f300:	3c017f1b */ 	lui	$at,%hi(var7f1b4ff4)
/*  f11f304:	c4324ff4 */ 	lwc1	$f18,%lo(var7f1b4ff4)($at)
/*  f11f308:	46020302 */ 	mul.s	$f12,$f0,$f2
/*  f11f30c:	c7b00024 */ 	lwc1	$f16,0x24($sp)
/*  f11f310:	460c903c */ 	c.lt.s	$f18,$f12
/*  f11f314:	00000000 */ 	nop
/*  f11f318:	45020005 */ 	bc1fl	.L0f11f330
/*  f11f31c:	c6080000 */ 	lwc1	$f8,0x0($s0)
/*  f11f320:	460c9183 */ 	div.s	$f6,$f18,$f12
/*  f11f324:	46061082 */ 	mul.s	$f2,$f2,$f6
/*  f11f328:	00000000 */ 	nop
/*  f11f32c:	c6080000 */ 	lwc1	$f8,0x0($s0)
.L0f11f330:
/*  f11f330:	c6240000 */ 	lwc1	$f4,0x0($s1)
/*  f11f334:	8fa3003c */ 	lw	$v1,0x3c($sp)
/*  f11f338:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f11f33c:	24020001 */ 	addiu	$v0,$zero,0x1
/*  f11f340:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f11f344:	46101282 */ 	mul.s	$f10,$f2,$f16
/*  f11f348:	e4660000 */ 	swc1	$f6,0x0($v1)
/*  f11f34c:	c6280004 */ 	lwc1	$f8,0x4($s1)
/*  f11f350:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f11f354:	e4640004 */ 	swc1	$f4,0x4($v1)
/*  f11f358:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f11f35c:	c62a0008 */ 	lwc1	$f10,0x8($s1)
/*  f11f360:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f11f364:	460a4100 */ 	add.s	$f4,$f8,$f10
/*  f11f368:	10000001 */ 	b	.L0f11f370
/*  f11f36c:	e4640008 */ 	swc1	$f4,0x8($v1)
.L0f11f370:
/*  f11f370:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f11f374:	8fb00014 */ 	lw	$s0,0x14($sp)
/*  f11f378:	8fb10018 */ 	lw	$s1,0x18($sp)
/*  f11f37c:	03e00008 */ 	jr	$ra
/*  f11f380:	27bd0038 */ 	addiu	$sp,$sp,0x38
);

/**
 * Scale base based on the height percentage between base and ref...
 * except the new y is zero.
 */
void func0f11f384(struct coord *base, struct coord *ref, struct coord *out)
{
	f32 mult = base->y / (base->y - ref->y);

	out->x = (ref->x - base->x) * mult + base->x;
	out->y = 0;
	out->z = (ref->z - base->z) * mult + base->z;
}

/**
 * A clamp function.
 */
f32 func0f11f3d0(f32 value, f32 min, f32 max)
{
	if (value < min) {
		return min;
	}

	if (value > max) {
		return max;
	}

	return value;
}

/**
 * A round function.
 */
f32 func0f11f410(f32 value)
{
	return (s32)(value + 0.5f);
}

GLOBAL_ASM(
glabel func0f11f438
.late_rodata
glabel var7f1b4ff8
.word 0x3b808081
.text
/*  f11f438:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f11f43c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f11f440:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f11f444:	0fc595f3 */ 	jal	skyGetCurrent
/*  f11f448:	afa40018 */ 	sw	$a0,0x18($sp)
/*  f11f44c:	904e0008 */ 	lbu	$t6,0x8($v0)
/*  f11f450:	3c013f80 */ 	lui	$at,0x3f80
/*  f11f454:	44818000 */ 	mtc1	$at,$f16
/*  f11f458:	448e2000 */ 	mtc1	$t6,$f4
/*  f11f45c:	3c017f1b */ 	lui	$at,%hi(var7f1b4ff8)
/*  f11f460:	c4324ff8 */ 	lwc1	$f18,%lo(var7f1b4ff8)($at)
/*  f11f464:	8fa40018 */ 	lw	$a0,0x18($sp)
/*  f11f468:	05c10005 */ 	bgez	$t6,.L0f11f480
/*  f11f46c:	468020a0 */ 	cvt.s.w	$f2,$f4
/*  f11f470:	3c014f80 */ 	lui	$at,0x4f80
/*  f11f474:	44813000 */ 	mtc1	$at,$f6
/*  f11f478:	00000000 */ 	nop
/*  f11f47c:	46061080 */ 	add.s	$f2,$f2,$f6
.L0f11f480:
/*  f11f480:	904f0009 */ 	lbu	$t7,0x9($v0)
/*  f11f484:	3c014f80 */ 	lui	$at,0x4f80
/*  f11f488:	3c0d800a */ 	lui	$t5,%hi(var800a33a4)
/*  f11f48c:	448f4000 */ 	mtc1	$t7,$f8
/*  f11f490:	05e10004 */ 	bgez	$t7,.L0f11f4a4
/*  f11f494:	46804320 */ 	cvt.s.w	$f12,$f8
/*  f11f498:	44815000 */ 	mtc1	$at,$f10
/*  f11f49c:	00000000 */ 	nop
/*  f11f4a0:	460a6300 */ 	add.s	$f12,$f12,$f10
.L0f11f4a4:
/*  f11f4a4:	9058000a */ 	lbu	$t8,0xa($v0)
/*  f11f4a8:	3c014f80 */ 	lui	$at,0x4f80
/*  f11f4ac:	c7a8001c */ 	lwc1	$f8,0x1c($sp)
/*  f11f4b0:	44982000 */ 	mtc1	$t8,$f4
/*  f11f4b4:	240f00ff */ 	addiu	$t7,$zero,0xff
/*  f11f4b8:	468023a0 */ 	cvt.s.w	$f14,$f4
/*  f11f4bc:	46121102 */ 	mul.s	$f4,$f2,$f18
/*  f11f4c0:	07030005 */ 	bgezl	$t8,.L0f11f4d8
/*  f11f4c4:	46048181 */ 	sub.s	$f6,$f16,$f4
/*  f11f4c8:	44813000 */ 	mtc1	$at,$f6
/*  f11f4cc:	00000000 */ 	nop
/*  f11f4d0:	46067380 */ 	add.s	$f14,$f14,$f6
/*  f11f4d4:	46048181 */ 	sub.s	$f6,$f16,$f4
.L0f11f4d8:
/*  f11f4d8:	c44a001c */ 	lwc1	$f10,0x1c($v0)
/*  f11f4dc:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f11f4e0:	46088001 */ 	sub.s	$f0,$f16,$f8
/*  f11f4e4:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f11f4e8:	3c014f00 */ 	lui	$at,0x4f00
/*  f11f4ec:	46004102 */ 	mul.s	$f4,$f8,$f0
/*  f11f4f0:	46022280 */ 	add.s	$f10,$f4,$f2
/*  f11f4f4:	4459f800 */ 	cfc1	$t9,$31
/*  f11f4f8:	44c8f800 */ 	ctc1	$t0,$31
/*  f11f4fc:	00000000 */ 	nop
/*  f11f500:	460051a4 */ 	cvt.w.s	$f6,$f10
/*  f11f504:	4448f800 */ 	cfc1	$t0,$31
/*  f11f508:	00000000 */ 	nop
/*  f11f50c:	31080078 */ 	andi	$t0,$t0,0x78
/*  f11f510:	51000013 */ 	beqzl	$t0,.L0f11f560
/*  f11f514:	44083000 */ 	mfc1	$t0,$f6
/*  f11f518:	44813000 */ 	mtc1	$at,$f6
/*  f11f51c:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f11f520:	46065181 */ 	sub.s	$f6,$f10,$f6
/*  f11f524:	44c8f800 */ 	ctc1	$t0,$31
/*  f11f528:	00000000 */ 	nop
/*  f11f52c:	460031a4 */ 	cvt.w.s	$f6,$f6
/*  f11f530:	4448f800 */ 	cfc1	$t0,$31
/*  f11f534:	00000000 */ 	nop
/*  f11f538:	31080078 */ 	andi	$t0,$t0,0x78
/*  f11f53c:	15000005 */ 	bnez	$t0,.L0f11f554
/*  f11f540:	00000000 */ 	nop
/*  f11f544:	44083000 */ 	mfc1	$t0,$f6
/*  f11f548:	3c018000 */ 	lui	$at,0x8000
/*  f11f54c:	10000007 */ 	b	.L0f11f56c
/*  f11f550:	01014025 */ 	or	$t0,$t0,$at
.L0f11f554:
/*  f11f554:	10000005 */ 	b	.L0f11f56c
/*  f11f558:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f11f55c:	44083000 */ 	mfc1	$t0,$f6
.L0f11f560:
/*  f11f560:	00000000 */ 	nop
/*  f11f564:	0500fffb */ 	bltz	$t0,.L0f11f554
/*  f11f568:	00000000 */ 	nop
.L0f11f56c:
/*  f11f56c:	44d9f800 */ 	ctc1	$t9,$31
/*  f11f570:	a0880014 */ 	sb	$t0,0x14($a0)
/*  f11f574:	c4480020 */ 	lwc1	$f8,0x20($v0)
/*  f11f578:	46126102 */ 	mul.s	$f4,$f12,$f18
/*  f11f57c:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f11f580:	3c014f00 */ 	lui	$at,0x4f00
/*  f11f584:	46048281 */ 	sub.s	$f10,$f16,$f4
/*  f11f588:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f11f58c:	00000000 */ 	nop
/*  f11f590:	46003102 */ 	mul.s	$f4,$f6,$f0
/*  f11f594:	460c2200 */ 	add.s	$f8,$f4,$f12
/*  f11f598:	4449f800 */ 	cfc1	$t1,$31
/*  f11f59c:	44caf800 */ 	ctc1	$t2,$31
/*  f11f5a0:	00000000 */ 	nop
/*  f11f5a4:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f11f5a8:	444af800 */ 	cfc1	$t2,$31
/*  f11f5ac:	00000000 */ 	nop
/*  f11f5b0:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f11f5b4:	11400012 */ 	beqz	$t2,.L0f11f600
/*  f11f5b8:	00000000 */ 	nop
/*  f11f5bc:	44815000 */ 	mtc1	$at,$f10
/*  f11f5c0:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f11f5c4:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f11f5c8:	44caf800 */ 	ctc1	$t2,$31
/*  f11f5cc:	00000000 */ 	nop
/*  f11f5d0:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f11f5d4:	444af800 */ 	cfc1	$t2,$31
/*  f11f5d8:	00000000 */ 	nop
/*  f11f5dc:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f11f5e0:	15400005 */ 	bnez	$t2,.L0f11f5f8
/*  f11f5e4:	00000000 */ 	nop
/*  f11f5e8:	440a5000 */ 	mfc1	$t2,$f10
/*  f11f5ec:	3c018000 */ 	lui	$at,0x8000
/*  f11f5f0:	10000007 */ 	b	.L0f11f610
/*  f11f5f4:	01415025 */ 	or	$t2,$t2,$at
.L0f11f5f8:
/*  f11f5f8:	10000005 */ 	b	.L0f11f610
/*  f11f5fc:	240affff */ 	addiu	$t2,$zero,-1
.L0f11f600:
/*  f11f600:	440a5000 */ 	mfc1	$t2,$f10
/*  f11f604:	00000000 */ 	nop
/*  f11f608:	0540fffb */ 	bltz	$t2,.L0f11f5f8
/*  f11f60c:	00000000 */ 	nop
.L0f11f610:
/*  f11f610:	44c9f800 */ 	ctc1	$t1,$31
/*  f11f614:	a08a0015 */ 	sb	$t2,0x15($a0)
/*  f11f618:	c4460024 */ 	lwc1	$f6,0x24($v0)
/*  f11f61c:	46127102 */ 	mul.s	$f4,$f14,$f18
/*  f11f620:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f11f624:	3c014f00 */ 	lui	$at,0x4f00
/*  f11f628:	240200ff */ 	addiu	$v0,$zero,0xff
/*  f11f62c:	46048201 */ 	sub.s	$f8,$f16,$f4
/*  f11f630:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f11f634:	00000000 */ 	nop
/*  f11f638:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f11f63c:	460e2180 */ 	add.s	$f6,$f4,$f14
/*  f11f640:	444bf800 */ 	cfc1	$t3,$31
/*  f11f644:	44ccf800 */ 	ctc1	$t4,$31
/*  f11f648:	00000000 */ 	nop
/*  f11f64c:	46003224 */ 	cvt.w.s	$f8,$f6
/*  f11f650:	444cf800 */ 	cfc1	$t4,$31
/*  f11f654:	00000000 */ 	nop
/*  f11f658:	318c0078 */ 	andi	$t4,$t4,0x78
/*  f11f65c:	11800012 */ 	beqz	$t4,.L0f11f6a8
/*  f11f660:	00000000 */ 	nop
/*  f11f664:	44814000 */ 	mtc1	$at,$f8
/*  f11f668:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f11f66c:	46083201 */ 	sub.s	$f8,$f6,$f8
/*  f11f670:	44ccf800 */ 	ctc1	$t4,$31
/*  f11f674:	00000000 */ 	nop
/*  f11f678:	46004224 */ 	cvt.w.s	$f8,$f8
/*  f11f67c:	444cf800 */ 	cfc1	$t4,$31
/*  f11f680:	00000000 */ 	nop
/*  f11f684:	318c0078 */ 	andi	$t4,$t4,0x78
/*  f11f688:	15800005 */ 	bnez	$t4,.L0f11f6a0
/*  f11f68c:	00000000 */ 	nop
/*  f11f690:	440c4000 */ 	mfc1	$t4,$f8
/*  f11f694:	3c018000 */ 	lui	$at,0x8000
/*  f11f698:	10000007 */ 	b	.L0f11f6b8
/*  f11f69c:	01816025 */ 	or	$t4,$t4,$at
.L0f11f6a0:
/*  f11f6a0:	10000005 */ 	b	.L0f11f6b8
/*  f11f6a4:	240cffff */ 	addiu	$t4,$zero,-1
.L0f11f6a8:
/*  f11f6a8:	440c4000 */ 	mfc1	$t4,$f8
/*  f11f6ac:	00000000 */ 	nop
/*  f11f6b0:	0580fffb */ 	bltz	$t4,.L0f11f6a0
/*  f11f6b4:	00000000 */ 	nop
.L0f11f6b8:
/*  f11f6b8:	a08c0016 */ 	sb	$t4,0x16($a0)
/*  f11f6bc:	8dad33a4 */ 	lw	$t5,%lo(var800a33a4)($t5)
/*  f11f6c0:	44cbf800 */ 	ctc1	$t3,$31
/*  f11f6c4:	51a00005 */ 	beqzl	$t5,.L0f11f6dc
/*  f11f6c8:	a08f0017 */ 	sb	$t7,0x17($a0)
/*  f11f6cc:	a0820016 */ 	sb	$v0,0x16($a0)
/*  f11f6d0:	a0820015 */ 	sb	$v0,0x15($a0)
/*  f11f6d4:	a0820014 */ 	sb	$v0,0x14($a0)
/*  f11f6d8:	a08f0017 */ 	sb	$t7,0x17($a0)
.L0f11f6dc:
/*  f11f6dc:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11f6e0:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f11f6e4:	03e00008 */ 	jr	$ra
/*  f11f6e8:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0f11f6ec
.late_rodata
glabel var7f1b4ffc
.word 0x3b808081
.text
/*  f11f6ec:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f11f6f0:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f11f6f4:	afa5001c */ 	sw	$a1,0x1c($sp)
/*  f11f6f8:	0fc595f3 */ 	jal	skyGetCurrent
/*  f11f6fc:	afa40018 */ 	sw	$a0,0x18($sp)
/*  f11f700:	904e0008 */ 	lbu	$t6,0x8($v0)
/*  f11f704:	3c013f80 */ 	lui	$at,0x3f80
/*  f11f708:	44818000 */ 	mtc1	$at,$f16
/*  f11f70c:	448e2000 */ 	mtc1	$t6,$f4
/*  f11f710:	3c017f1b */ 	lui	$at,%hi(var7f1b4ffc)
/*  f11f714:	c4324ffc */ 	lwc1	$f18,%lo(var7f1b4ffc)($at)
/*  f11f718:	8fa40018 */ 	lw	$a0,0x18($sp)
/*  f11f71c:	05c10005 */ 	bgez	$t6,.L0f11f734
/*  f11f720:	468020a0 */ 	cvt.s.w	$f2,$f4
/*  f11f724:	3c014f80 */ 	lui	$at,0x4f80
/*  f11f728:	44813000 */ 	mtc1	$at,$f6
/*  f11f72c:	00000000 */ 	nop
/*  f11f730:	46061080 */ 	add.s	$f2,$f2,$f6
.L0f11f734:
/*  f11f734:	904f0009 */ 	lbu	$t7,0x9($v0)
/*  f11f738:	3c014f80 */ 	lui	$at,0x4f80
/*  f11f73c:	240d00ff */ 	addiu	$t5,$zero,0xff
/*  f11f740:	448f4000 */ 	mtc1	$t7,$f8
/*  f11f744:	05e10004 */ 	bgez	$t7,.L0f11f758
/*  f11f748:	46804320 */ 	cvt.s.w	$f12,$f8
/*  f11f74c:	44815000 */ 	mtc1	$at,$f10
/*  f11f750:	00000000 */ 	nop
/*  f11f754:	460a6300 */ 	add.s	$f12,$f12,$f10
.L0f11f758:
/*  f11f758:	9058000a */ 	lbu	$t8,0xa($v0)
/*  f11f75c:	3c014f80 */ 	lui	$at,0x4f80
/*  f11f760:	c7a8001c */ 	lwc1	$f8,0x1c($sp)
/*  f11f764:	44982000 */ 	mtc1	$t8,$f4
/*  f11f768:	00000000 */ 	nop
/*  f11f76c:	468023a0 */ 	cvt.s.w	$f14,$f4
/*  f11f770:	46121102 */ 	mul.s	$f4,$f2,$f18
/*  f11f774:	07030005 */ 	bgezl	$t8,.L0f11f78c
/*  f11f778:	46048181 */ 	sub.s	$f6,$f16,$f4
/*  f11f77c:	44813000 */ 	mtc1	$at,$f6
/*  f11f780:	00000000 */ 	nop
/*  f11f784:	46067380 */ 	add.s	$f14,$f14,$f6
/*  f11f788:	46048181 */ 	sub.s	$f6,$f16,$f4
.L0f11f78c:
/*  f11f78c:	c44a0034 */ 	lwc1	$f10,0x34($v0)
/*  f11f790:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f11f794:	46088001 */ 	sub.s	$f0,$f16,$f8
/*  f11f798:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f11f79c:	3c014f00 */ 	lui	$at,0x4f00
/*  f11f7a0:	46004102 */ 	mul.s	$f4,$f8,$f0
/*  f11f7a4:	46022280 */ 	add.s	$f10,$f4,$f2
/*  f11f7a8:	4459f800 */ 	cfc1	$t9,$31
/*  f11f7ac:	44c8f800 */ 	ctc1	$t0,$31
/*  f11f7b0:	00000000 */ 	nop
/*  f11f7b4:	460051a4 */ 	cvt.w.s	$f6,$f10
/*  f11f7b8:	4448f800 */ 	cfc1	$t0,$31
/*  f11f7bc:	00000000 */ 	nop
/*  f11f7c0:	31080078 */ 	andi	$t0,$t0,0x78
/*  f11f7c4:	51000013 */ 	beqzl	$t0,.L0f11f814
/*  f11f7c8:	44083000 */ 	mfc1	$t0,$f6
/*  f11f7cc:	44813000 */ 	mtc1	$at,$f6
/*  f11f7d0:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f11f7d4:	46065181 */ 	sub.s	$f6,$f10,$f6
/*  f11f7d8:	44c8f800 */ 	ctc1	$t0,$31
/*  f11f7dc:	00000000 */ 	nop
/*  f11f7e0:	460031a4 */ 	cvt.w.s	$f6,$f6
/*  f11f7e4:	4448f800 */ 	cfc1	$t0,$31
/*  f11f7e8:	00000000 */ 	nop
/*  f11f7ec:	31080078 */ 	andi	$t0,$t0,0x78
/*  f11f7f0:	15000005 */ 	bnez	$t0,.L0f11f808
/*  f11f7f4:	00000000 */ 	nop
/*  f11f7f8:	44083000 */ 	mfc1	$t0,$f6
/*  f11f7fc:	3c018000 */ 	lui	$at,0x8000
/*  f11f800:	10000007 */ 	b	.L0f11f820
/*  f11f804:	01014025 */ 	or	$t0,$t0,$at
.L0f11f808:
/*  f11f808:	10000005 */ 	b	.L0f11f820
/*  f11f80c:	2408ffff */ 	addiu	$t0,$zero,-1
/*  f11f810:	44083000 */ 	mfc1	$t0,$f6
.L0f11f814:
/*  f11f814:	00000000 */ 	nop
/*  f11f818:	0500fffb */ 	bltz	$t0,.L0f11f808
/*  f11f81c:	00000000 */ 	nop
.L0f11f820:
/*  f11f820:	44d9f800 */ 	ctc1	$t9,$31
/*  f11f824:	a0880014 */ 	sb	$t0,0x14($a0)
/*  f11f828:	c4480038 */ 	lwc1	$f8,0x38($v0)
/*  f11f82c:	46126102 */ 	mul.s	$f4,$f12,$f18
/*  f11f830:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f11f834:	3c014f00 */ 	lui	$at,0x4f00
/*  f11f838:	46048281 */ 	sub.s	$f10,$f16,$f4
/*  f11f83c:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f11f840:	00000000 */ 	nop
/*  f11f844:	46003102 */ 	mul.s	$f4,$f6,$f0
/*  f11f848:	460c2200 */ 	add.s	$f8,$f4,$f12
/*  f11f84c:	4449f800 */ 	cfc1	$t1,$31
/*  f11f850:	44caf800 */ 	ctc1	$t2,$31
/*  f11f854:	00000000 */ 	nop
/*  f11f858:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f11f85c:	444af800 */ 	cfc1	$t2,$31
/*  f11f860:	00000000 */ 	nop
/*  f11f864:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f11f868:	11400012 */ 	beqz	$t2,.L0f11f8b4
/*  f11f86c:	00000000 */ 	nop
/*  f11f870:	44815000 */ 	mtc1	$at,$f10
/*  f11f874:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f11f878:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f11f87c:	44caf800 */ 	ctc1	$t2,$31
/*  f11f880:	00000000 */ 	nop
/*  f11f884:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f11f888:	444af800 */ 	cfc1	$t2,$31
/*  f11f88c:	00000000 */ 	nop
/*  f11f890:	314a0078 */ 	andi	$t2,$t2,0x78
/*  f11f894:	15400005 */ 	bnez	$t2,.L0f11f8ac
/*  f11f898:	00000000 */ 	nop
/*  f11f89c:	440a5000 */ 	mfc1	$t2,$f10
/*  f11f8a0:	3c018000 */ 	lui	$at,0x8000
/*  f11f8a4:	10000007 */ 	b	.L0f11f8c4
/*  f11f8a8:	01415025 */ 	or	$t2,$t2,$at
.L0f11f8ac:
/*  f11f8ac:	10000005 */ 	b	.L0f11f8c4
/*  f11f8b0:	240affff */ 	addiu	$t2,$zero,-1
.L0f11f8b4:
/*  f11f8b4:	440a5000 */ 	mfc1	$t2,$f10
/*  f11f8b8:	00000000 */ 	nop
/*  f11f8bc:	0540fffb */ 	bltz	$t2,.L0f11f8ac
/*  f11f8c0:	00000000 */ 	nop
.L0f11f8c4:
/*  f11f8c4:	44c9f800 */ 	ctc1	$t1,$31
/*  f11f8c8:	a08a0015 */ 	sb	$t2,0x15($a0)
/*  f11f8cc:	c446003c */ 	lwc1	$f6,0x3c($v0)
/*  f11f8d0:	46127102 */ 	mul.s	$f4,$f14,$f18
/*  f11f8d4:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f11f8d8:	3c014f00 */ 	lui	$at,0x4f00
/*  f11f8dc:	46048201 */ 	sub.s	$f8,$f16,$f4
/*  f11f8e0:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f11f8e4:	00000000 */ 	nop
/*  f11f8e8:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f11f8ec:	460e2180 */ 	add.s	$f6,$f4,$f14
/*  f11f8f0:	444bf800 */ 	cfc1	$t3,$31
/*  f11f8f4:	44ccf800 */ 	ctc1	$t4,$31
/*  f11f8f8:	00000000 */ 	nop
/*  f11f8fc:	46003224 */ 	cvt.w.s	$f8,$f6
/*  f11f900:	444cf800 */ 	cfc1	$t4,$31
/*  f11f904:	00000000 */ 	nop
/*  f11f908:	318c0078 */ 	andi	$t4,$t4,0x78
/*  f11f90c:	11800012 */ 	beqz	$t4,.L0f11f958
/*  f11f910:	00000000 */ 	nop
/*  f11f914:	44814000 */ 	mtc1	$at,$f8
/*  f11f918:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f11f91c:	46083201 */ 	sub.s	$f8,$f6,$f8
/*  f11f920:	44ccf800 */ 	ctc1	$t4,$31
/*  f11f924:	00000000 */ 	nop
/*  f11f928:	46004224 */ 	cvt.w.s	$f8,$f8
/*  f11f92c:	444cf800 */ 	cfc1	$t4,$31
/*  f11f930:	00000000 */ 	nop
/*  f11f934:	318c0078 */ 	andi	$t4,$t4,0x78
/*  f11f938:	15800005 */ 	bnez	$t4,.L0f11f950
/*  f11f93c:	00000000 */ 	nop
/*  f11f940:	440c4000 */ 	mfc1	$t4,$f8
/*  f11f944:	3c018000 */ 	lui	$at,0x8000
/*  f11f948:	10000007 */ 	b	.L0f11f968
/*  f11f94c:	01816025 */ 	or	$t4,$t4,$at
.L0f11f950:
/*  f11f950:	10000005 */ 	b	.L0f11f968
/*  f11f954:	240cffff */ 	addiu	$t4,$zero,-1
.L0f11f958:
/*  f11f958:	440c4000 */ 	mfc1	$t4,$f8
/*  f11f95c:	00000000 */ 	nop
/*  f11f960:	0580fffb */ 	bltz	$t4,.L0f11f950
/*  f11f964:	00000000 */ 	nop
.L0f11f968:
/*  f11f968:	a08c0016 */ 	sb	$t4,0x16($a0)
/*  f11f96c:	a08d0017 */ 	sb	$t5,0x17($a0)
/*  f11f970:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f11f974:	44cbf800 */ 	ctc1	$t3,$31
/*  f11f978:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f11f97c:	03e00008 */ 	jr	$ra
/*  f11f980:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func0f11f984
.late_rodata
glabel var7f1b5000
.word 0x3dcccccd
glabel var7f1b5004
.word func0f11f984+0x6a0 # f120024
glabel var7f1b5008
.word func0f11f984+0xf24 # f1208a8
glabel var7f1b500c
.word func0f11f984+0x1074 # f1209f8
glabel var7f1b5010
.word func0f11f984+0x7ac # f120130
glabel var7f1b5014
.word func0f11f984+0x11c4 # f120b48
glabel var7f1b5018
.word func0f11f984+0xad8 # f12045c
glabel var7f1b501c
.word func0f11f984+0x1464 # f120de8
glabel var7f1b5020
.word func0f11f984+0xe54 # f1207d8
glabel var7f1b5024
.word func0f11f984+0x1314 # f120c98
glabel var7f1b5028
.word func0f11f984+0x1464 # f120de8
glabel var7f1b502c
.word func0f11f984+0x9cc # f120350
glabel var7f1b5030
.word func0f11f984+0xd84 # f120708
glabel var7f1b5034
.word func0f11f984+0x8b8 # f12023c
glabel var7f1b5038
.word func0f11f984+0xcb4 # f120638
glabel var7f1b503c
.word func0f11f984+0xbe4 # f120568
glabel var7f1b5040
.word func0f11f984+0x690 # f120014
glabel var7f1b5044
.word 0x3d088889
glabel var7f1b5048
.word 0x3d088889
glabel var7f1b504c
.word 0x3d088889
glabel var7f1b5050
.word 0x3d088889
glabel var7f1b5054
.word 0x3d088889
glabel var7f1b5058
.word 0x3d088889
glabel var7f1b505c
.word 0x3d088889
glabel var7f1b5060
.word 0x3d088889
glabel var7f1b5064
.word 0x3d088889
glabel var7f1b5068
.word 0x3d088889
glabel var7f1b506c
.word 0x3d088889
glabel var7f1b5070
.word 0x3d088889
glabel var7f1b5074
.word 0x3d088889
glabel var7f1b5078
.word 0x3d088889
glabel var7f1b507c
.word 0x477fff00
glabel var7f1b5080
.word 0x449fe000
glabel var7f1b5084
.word 0x446fc000
glabel var7f1b5088
.word func0f11f984+0x19e8 # f12136c
glabel var7f1b508c
.word func0f11f984+0x2010 # f121994
glabel var7f1b5090
.word func0f11f984+0x2100 # f121a84
glabel var7f1b5094
.word func0f11f984+0x1c68 # f1215ec
glabel var7f1b5098
.word func0f11f984+0x21f0 # f121b74
glabel var7f1b509c
.word func0f11f984+0x1da0 # f121724
glabel var7f1b50a0
.word func0f11f984+0x29f4 # f122378
glabel var7f1b50a4
.word func0f11f984+0x286c # f1221f0
glabel var7f1b50a8
.word func0f11f984+0x22e0 # f121c64
glabel var7f1b50ac
.word func0f11f984+0x29f4 # f122378
glabel var7f1b50b0
.word func0f11f984+0x1ed8 # f12185c
glabel var7f1b50b4
.word func0f11f984+0x26e4 # f122068
glabel var7f1b50b8
.word func0f11f984+0x1b2c # f1214b0
glabel var7f1b50bc
.word func0f11f984+0x2558 # f121edc
glabel var7f1b50c0
.word func0f11f984+0x23d0 # f121d54
glabel var7f1b50c4
.word func0f11f984+0x19f0 # f121374
glabel var7f1b50c8
.word 0x477fff00
.text
/*  f11f984:	27bdf950 */ 	addiu	$sp,$sp,-1712
/*  f11f988:	afbf0054 */ 	sw	$ra,0x54($sp)
/*  f11f98c:	afb10050 */ 	sw	$s1,0x50($sp)
/*  f11f990:	afb0004c */ 	sw	$s0,0x4c($sp)
/*  f11f994:	f7bc0040 */ 	sdc1	$f28,0x40($sp)
/*  f11f998:	f7ba0038 */ 	sdc1	$f26,0x38($sp)
/*  f11f99c:	f7b80030 */ 	sdc1	$f24,0x30($sp)
/*  f11f9a0:	f7b60028 */ 	sdc1	$f22,0x28($sp)
/*  f11f9a4:	f7b40020 */ 	sdc1	$f20,0x20($sp)
/*  f11f9a8:	afa406b0 */ 	sw	$a0,0x6b0($sp)
/*  f11f9ac:	0fc595f3 */ 	jal	skyGetCurrent
/*  f11f9b0:	afa00430 */ 	sw	$zero,0x430($sp)
/*  f11f9b4:	904e0010 */ 	lbu	$t6,0x10($v0)
/*  f11f9b8:	3c11800a */ 	lui	$s1,%hi(g_Vars)
/*  f11f9bc:	00404025 */ 	or	$t0,$v0,$zero
/*  f11f9c0:	11c00005 */ 	beqz	$t6,.L0f11f9d8
/*  f11f9c4:	26319fc0 */ 	addiu	$s1,$s1,%lo(g_Vars)
/*  f11f9c8:	8e2f0284 */ 	lw	$t7,0x284($s1)
/*  f11f9cc:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11f9d0:	95f80010 */ 	lhu	$t8,0x10($t7)
/*  f11f9d4:	14b800ae */ 	bne	$a1,$t8,.L0f11fc90
.L0f11f9d8:
/*  f11f9d8:	3c11800a */ 	lui	$s1,%hi(g_Vars)
/*  f11f9dc:	26319fc0 */ 	addiu	$s1,$s1,%lo(g_Vars)
/*  f11f9e0:	8e39006c */ 	lw	$t9,0x6c($s1)
/*  f11f9e4:	24050001 */ 	addiu	$a1,$zero,0x1
/*  f11f9e8:	00002025 */ 	or	$a0,$zero,$zero
/*  f11f9ec:	13200003 */ 	beqz	$t9,.L0f11f9fc
/*  f11f9f0:	00001825 */ 	or	$v1,$zero,$zero
/*  f11f9f4:	10000001 */ 	b	.L0f11f9fc
/*  f11f9f8:	00a02025 */ 	or	$a0,$a1,$zero
.L0f11f9fc:
/*  f11f9fc:	8e290068 */ 	lw	$t1,0x68($s1)
/*  f11fa00:	00008025 */ 	or	$s0,$zero,$zero
/*  f11fa04:	00001025 */ 	or	$v0,$zero,$zero
/*  f11fa08:	11200003 */ 	beqz	$t1,.L0f11fa18
/*  f11fa0c:	8fb806b0 */ 	lw	$t8,0x6b0($sp)
/*  f11fa10:	10000001 */ 	b	.L0f11fa18
/*  f11fa14:	00a01825 */ 	or	$v1,$a1,$zero
.L0f11fa18:
/*  f11fa18:	8e2a0064 */ 	lw	$t2,0x64($s1)
/*  f11fa1c:	8faf06b0 */ 	lw	$t7,0x6b0($sp)
/*  f11fa20:	3c090030 */ 	lui	$t1,0x30
/*  f11fa24:	11400003 */ 	beqz	$t2,.L0f11fa34
/*  f11fa28:	27190008 */ 	addiu	$t9,$t8,0x8
/*  f11fa2c:	10000001 */ 	b	.L0f11fa34
/*  f11fa30:	00a08025 */ 	or	$s0,$a1,$zero
.L0f11fa34:
/*  f11fa34:	8e2b0070 */ 	lw	$t3,0x70($s1)
/*  f11fa38:	11600003 */ 	beqz	$t3,.L0f11fa48
/*  f11fa3c:	00000000 */ 	nop
/*  f11fa40:	10000001 */ 	b	.L0f11fa48
/*  f11fa44:	00a01025 */ 	or	$v0,$a1,$zero
.L0f11fa48:
/*  f11fa48:	00506021 */ 	addu	$t4,$v0,$s0
/*  f11fa4c:	01836821 */ 	addu	$t5,$t4,$v1
/*  f11fa50:	01a47021 */ 	addu	$t6,$t5,$a0
/*  f11fa54:	14ae0046 */ 	bne	$a1,$t6,.L0f11fb70
/*  f11fa58:	3c0be700 */ 	lui	$t3,0xe700
/*  f11fa5c:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f11fa60:	afb806b0 */ 	sw	$t8,0x6b0($sp)
/*  f11fa64:	3c19ba00 */ 	lui	$t9,0xba00
/*  f11fa68:	37391402 */ 	ori	$t9,$t9,0x1402
/*  f11fa6c:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f11fa70:	ade90004 */ 	sw	$t1,0x4($t7)
/*  f11fa74:	8e2a0284 */ 	lw	$t2,0x284($s1)
/*  f11fa78:	00003025 */ 	or	$a2,$zero,$zero
/*  f11fa7c:	00003825 */ 	or	$a3,$zero,$zero
/*  f11fa80:	954b0010 */ 	lhu	$t3,0x10($t2)
/*  f11fa84:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f11fa88:	54ab0007 */ 	bnel	$a1,$t3,.L0f11faa8
/*  f11fa8c:	91050008 */ 	lbu	$a1,0x8($t0)
/*  f11fa90:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f11fa94:	0c002fc1 */ 	jal	viSetFillColour
/*  f11fa98:	00002825 */ 	or	$a1,$zero,$zero
/*  f11fa9c:	10000007 */ 	b	.L0f11fabc
/*  f11faa0:	00401825 */ 	or	$v1,$v0,$zero
/*  f11faa4:	91050008 */ 	lbu	$a1,0x8($t0)
.L0f11faa8:
/*  f11faa8:	91060009 */ 	lbu	$a2,0x9($t0)
/*  f11faac:	0c002fc1 */ 	jal	viSetFillColour
/*  f11fab0:	9107000a */ 	lbu	$a3,0xa($t0)
/*  f11fab4:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f11fab8:	00401825 */ 	or	$v1,$v0,$zero
.L0f11fabc:
/*  f11fabc:	00608825 */ 	or	$s1,$v1,$zero
/*  f11fac0:	24630008 */ 	addiu	$v1,$v1,0x8
/*  f11fac4:	0c002f22 */ 	jal	viGetViewWidth
/*  f11fac8:	afa306b0 */ 	sw	$v1,0x6b0($sp)
/*  f11facc:	0c002f40 */ 	jal	viGetViewLeft
/*  f11fad0:	a7a2007a */ 	sh	$v0,0x7a($sp)
/*  f11fad4:	0c002f44 */ 	jal	viGetViewTop
/*  f11fad8:	a7a2007c */ 	sh	$v0,0x7c($sp)
/*  f11fadc:	00028400 */ 	sll	$s0,$v0,0x10
/*  f11fae0:	00106403 */ 	sra	$t4,$s0,0x10
/*  f11fae4:	0c002f26 */ 	jal	viGetViewHeight
/*  f11fae8:	01808025 */ 	or	$s0,$t4,$zero
/*  f11faec:	87ad007c */ 	lh	$t5,0x7c($sp)
/*  f11faf0:	87ae007a */ 	lh	$t6,0x7a($sp)
/*  f11faf4:	00505021 */ 	addu	$t2,$v0,$s0
/*  f11faf8:	254bffff */ 	addiu	$t3,$t2,-1
/*  f11fafc:	01ae7821 */ 	addu	$t7,$t5,$t6
/*  f11fb00:	25f8ffff */ 	addiu	$t8,$t7,-1
/*  f11fb04:	316c03ff */ 	andi	$t4,$t3,0x3ff
/*  f11fb08:	000c6880 */ 	sll	$t5,$t4,0x2
/*  f11fb0c:	331903ff */ 	andi	$t9,$t8,0x3ff
/*  f11fb10:	3c01f600 */ 	lui	$at,0xf600
/*  f11fb14:	01a17025 */ 	or	$t6,$t5,$at
/*  f11fb18:	00194b80 */ 	sll	$t1,$t9,0xe
/*  f11fb1c:	01c97825 */ 	or	$t7,$t6,$t1
/*  f11fb20:	0c002f40 */ 	jal	viGetViewLeft
/*  f11fb24:	ae2f0000 */ 	sw	$t7,0x0($s1)
/*  f11fb28:	00028400 */ 	sll	$s0,$v0,0x10
/*  f11fb2c:	0010c403 */ 	sra	$t8,$s0,0x10
/*  f11fb30:	0c002f44 */ 	jal	viGetViewTop
/*  f11fb34:	03008025 */ 	or	$s0,$t8,$zero
/*  f11fb38:	305903ff */ 	andi	$t9,$v0,0x3ff
/*  f11fb3c:	320b03ff */ 	andi	$t3,$s0,0x3ff
/*  f11fb40:	000b6380 */ 	sll	$t4,$t3,0xe
/*  f11fb44:	00195080 */ 	sll	$t2,$t9,0x2
/*  f11fb48:	014c6825 */ 	or	$t5,$t2,$t4
/*  f11fb4c:	ae2d0004 */ 	sw	$t5,0x4($s1)
/*  f11fb50:	8fae06b0 */ 	lw	$t6,0x6b0($sp)
/*  f11fb54:	3c0fe700 */ 	lui	$t7,0xe700
/*  f11fb58:	25c90008 */ 	addiu	$t1,$t6,0x8
/*  f11fb5c:	afa906b0 */ 	sw	$t1,0x6b0($sp)
/*  f11fb60:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f11fb64:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f11fb68:	10000b4f */ 	b	.L0f1228a8
/*  f11fb6c:	8fa206b0 */ 	lw	$v0,0x6b0($sp)
.L0f11fb70:
/*  f11fb70:	afb906b0 */ 	sw	$t9,0x6b0($sp)
/*  f11fb74:	af000004 */ 	sw	$zero,0x4($t8)
/*  f11fb78:	af0b0000 */ 	sw	$t3,0x0($t8)
/*  f11fb7c:	8faa06b0 */ 	lw	$t2,0x6b0($sp)
/*  f11fb80:	3c0dba00 */ 	lui	$t5,0xba00
/*  f11fb84:	35ad1402 */ 	ori	$t5,$t5,0x1402
/*  f11fb88:	254c0008 */ 	addiu	$t4,$t2,0x8
/*  f11fb8c:	afac06b0 */ 	sw	$t4,0x6b0($sp)
/*  f11fb90:	3c0e0030 */ 	lui	$t6,0x30
/*  f11fb94:	ad4e0004 */ 	sw	$t6,0x4($t2)
/*  f11fb98:	ad4d0000 */ 	sw	$t5,0x0($t2)
/*  f11fb9c:	8e290284 */ 	lw	$t1,0x284($s1)
/*  f11fba0:	00003025 */ 	or	$a2,$zero,$zero
/*  f11fba4:	00003825 */ 	or	$a3,$zero,$zero
/*  f11fba8:	952f0010 */ 	lhu	$t7,0x10($t1)
/*  f11fbac:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f11fbb0:	54af0007 */ 	bnel	$a1,$t7,.L0f11fbd0
/*  f11fbb4:	91050008 */ 	lbu	$a1,0x8($t0)
/*  f11fbb8:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f11fbbc:	0c002fc1 */ 	jal	viSetFillColour
/*  f11fbc0:	00002825 */ 	or	$a1,$zero,$zero
/*  f11fbc4:	10000006 */ 	b	.L0f11fbe0
/*  f11fbc8:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f11fbcc:	91050008 */ 	lbu	$a1,0x8($t0)
.L0f11fbd0:
/*  f11fbd0:	91060009 */ 	lbu	$a2,0x9($t0)
/*  f11fbd4:	0c002fc1 */ 	jal	viSetFillColour
/*  f11fbd8:	9107000a */ 	lbu	$a3,0xa($t0)
/*  f11fbdc:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f11fbe0:
/*  f11fbe0:	8fb806b0 */ 	lw	$t8,0x6b0($sp)
/*  f11fbe4:	3c0bb900 */ 	lui	$t3,0xb900
/*  f11fbe8:	356b031d */ 	ori	$t3,$t3,0x31d
/*  f11fbec:	27190008 */ 	addiu	$t9,$t8,0x8
/*  f11fbf0:	afb906b0 */ 	sw	$t9,0x6b0($sp)
/*  f11fbf4:	af000004 */ 	sw	$zero,0x4($t8)
/*  f11fbf8:	af0b0000 */ 	sw	$t3,0x0($t8)
/*  f11fbfc:	8fa506b0 */ 	lw	$a1,0x6b0($sp)
/*  f11fc00:	8e230284 */ 	lw	$v1,0x284($s1)
/*  f11fc04:	3c01f600 */ 	lui	$at,0xf600
/*  f11fc08:	24ac0008 */ 	addiu	$t4,$a1,0x8
/*  f11fc0c:	afac06b0 */ 	sw	$t4,0x6b0($sp)
/*  f11fc10:	846d0634 */ 	lh	$t5,0x634($v1)
/*  f11fc14:	846e0630 */ 	lh	$t6,0x630($v1)
/*  f11fc18:	846a0636 */ 	lh	$t2,0x636($v1)
/*  f11fc1c:	846c0632 */ 	lh	$t4,0x632($v1)
/*  f11fc20:	01ae4821 */ 	addu	$t1,$t5,$t6
/*  f11fc24:	252fffff */ 	addiu	$t7,$t1,-1
/*  f11fc28:	014c6821 */ 	addu	$t5,$t2,$t4
/*  f11fc2c:	25aeffff */ 	addiu	$t6,$t5,-1
/*  f11fc30:	31f803ff */ 	andi	$t8,$t7,0x3ff
/*  f11fc34:	0018cb80 */ 	sll	$t9,$t8,0xe
/*  f11fc38:	31c903ff */ 	andi	$t1,$t6,0x3ff
/*  f11fc3c:	00097880 */ 	sll	$t7,$t1,0x2
/*  f11fc40:	03215825 */ 	or	$t3,$t9,$at
/*  f11fc44:	016fc025 */ 	or	$t8,$t3,$t7
/*  f11fc48:	acb80000 */ 	sw	$t8,0x0($a1)
/*  f11fc4c:	8e230284 */ 	lw	$v1,0x284($s1)
/*  f11fc50:	84790634 */ 	lh	$t9,0x634($v1)
/*  f11fc54:	846d0636 */ 	lh	$t5,0x636($v1)
/*  f11fc58:	332a03ff */ 	andi	$t2,$t9,0x3ff
/*  f11fc5c:	31ae03ff */ 	andi	$t6,$t5,0x3ff
/*  f11fc60:	000e4880 */ 	sll	$t1,$t6,0x2
/*  f11fc64:	000a6380 */ 	sll	$t4,$t2,0xe
/*  f11fc68:	01895825 */ 	or	$t3,$t4,$t1
/*  f11fc6c:	acab0004 */ 	sw	$t3,0x4($a1)
/*  f11fc70:	8faf06b0 */ 	lw	$t7,0x6b0($sp)
/*  f11fc74:	3c19e700 */ 	lui	$t9,0xe700
/*  f11fc78:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f11fc7c:	afb806b0 */ 	sw	$t8,0x6b0($sp)
/*  f11fc80:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f11fc84:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f11fc88:	10000b07 */ 	b	.L0f1228a8
/*  f11fc8c:	8fa206b0 */ 	lw	$v0,0x6b0($sp)
.L0f11fc90:
/*  f11fc90:	91050008 */ 	lbu	$a1,0x8($t0)
/*  f11fc94:	91060009 */ 	lbu	$a2,0x9($t0)
/*  f11fc98:	9107000a */ 	lbu	$a3,0xa($t0)
/*  f11fc9c:	afa8042c */ 	sw	$t0,0x42c($sp)
/*  f11fca0:	0c002fc1 */ 	jal	viSetFillColour
/*  f11fca4:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f11fca8:	44806000 */ 	mtc1	$zero,$f12
/*  f11fcac:	27b106a4 */ 	addiu	$s1,$sp,0x6a4
/*  f11fcb0:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f11fcb4:	02203025 */ 	or	$a2,$s1,$zero
/*  f11fcb8:	0fc47c00 */ 	jal	func0f11f000
/*  f11fcbc:	46006386 */ 	mov.s	$f14,$f12
/*  f11fcc0:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f11fcc4:	00000000 */ 	nop
/*  f11fcc8:	3c017f1b */ 	lui	$at,%hi(var7f1b5000)
/*  f11fccc:	c43c5000 */ 	lwc1	$f28,%lo(var7f1b5000)($at)
/*  f11fcd0:	44807000 */ 	mtc1	$zero,$f14
/*  f11fcd4:	27a60698 */ 	addiu	$a2,$sp,0x698
/*  f11fcd8:	0fc47c00 */ 	jal	func0f11f000
/*  f11fcdc:	461c0301 */ 	sub.s	$f12,$f0,$f28
/*  f11fce0:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f11fce4:	00000000 */ 	nop
/*  f11fce8:	44806000 */ 	mtc1	$zero,$f12
/*  f11fcec:	461c0381 */ 	sub.s	$f14,$f0,$f28
/*  f11fcf0:	0fc47c00 */ 	jal	func0f11f000
/*  f11fcf4:	27a6068c */ 	addiu	$a2,$sp,0x68c
/*  f11fcf8:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f11fcfc:	00000000 */ 	nop
/*  f11fd00:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f11fd04:	46000586 */ 	mov.s	$f22,$f0
/*  f11fd08:	461cb301 */ 	sub.s	$f12,$f22,$f28
/*  f11fd0c:	27a60680 */ 	addiu	$a2,$sp,0x680
/*  f11fd10:	0fc47c00 */ 	jal	func0f11f000
/*  f11fd14:	461c0381 */ 	sub.s	$f14,$f0,$f28
/*  f11fd18:	02202025 */ 	or	$a0,$s1,$zero
/*  f11fd1c:	27a50644 */ 	addiu	$a1,$sp,0x644
/*  f11fd20:	0fc47c1f */ 	jal	func0f11f07c
/*  f11fd24:	27a6058c */ 	addiu	$a2,$sp,0x58c
/*  f11fd28:	afa20538 */ 	sw	$v0,0x538($sp)
/*  f11fd2c:	27a40698 */ 	addiu	$a0,$sp,0x698
/*  f11fd30:	27a50638 */ 	addiu	$a1,$sp,0x638
/*  f11fd34:	0fc47c1f */ 	jal	func0f11f07c
/*  f11fd38:	27a60588 */ 	addiu	$a2,$sp,0x588
/*  f11fd3c:	afa20534 */ 	sw	$v0,0x534($sp)
/*  f11fd40:	27a4068c */ 	addiu	$a0,$sp,0x68c
/*  f11fd44:	27a5062c */ 	addiu	$a1,$sp,0x62c
/*  f11fd48:	0fc47c1f */ 	jal	func0f11f07c
/*  f11fd4c:	27a60584 */ 	addiu	$a2,$sp,0x584
/*  f11fd50:	afa20530 */ 	sw	$v0,0x530($sp)
/*  f11fd54:	27a40680 */ 	addiu	$a0,$sp,0x680
/*  f11fd58:	27a50620 */ 	addiu	$a1,$sp,0x620
/*  f11fd5c:	0fc47c1f */ 	jal	func0f11f07c
/*  f11fd60:	27a60580 */ 	addiu	$a2,$sp,0x580
/*  f11fd64:	afa2052c */ 	sw	$v0,0x52c($sp)
/*  f11fd68:	02202025 */ 	or	$a0,$s1,$zero
/*  f11fd6c:	27a505e4 */ 	addiu	$a1,$sp,0x5e4
/*  f11fd70:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11fd74:	27a6056c */ 	addiu	$a2,$sp,0x56c
/*  f11fd78:	27a40698 */ 	addiu	$a0,$sp,0x698
/*  f11fd7c:	27a505d8 */ 	addiu	$a1,$sp,0x5d8
/*  f11fd80:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11fd84:	27a60568 */ 	addiu	$a2,$sp,0x568
/*  f11fd88:	27a4068c */ 	addiu	$a0,$sp,0x68c
/*  f11fd8c:	27a505cc */ 	addiu	$a1,$sp,0x5cc
/*  f11fd90:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11fd94:	27a60564 */ 	addiu	$a2,$sp,0x564
/*  f11fd98:	27a40680 */ 	addiu	$a0,$sp,0x680
/*  f11fd9c:	27a505c0 */ 	addiu	$a1,$sp,0x5c0
/*  f11fda0:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11fda4:	27a60560 */ 	addiu	$a2,$sp,0x560
/*  f11fda8:	8faa0538 */ 	lw	$t2,0x538($sp)
/*  f11fdac:	8fad0530 */ 	lw	$t5,0x530($sp)
/*  f11fdb0:	514d001f */ 	beql	$t2,$t5,.L0f11fe30
/*  f11fdb4:	44805000 */ 	mtc1	$zero,$f10
/*  f11fdb8:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f11fdbc:	00000000 */ 	nop
/*  f11fdc0:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f11fdc4:	46000586 */ 	mov.s	$f22,$f0
/*  f11fdc8:	c7a206a8 */ 	lwc1	$f2,0x6a8($sp)
/*  f11fdcc:	c7b00690 */ 	lwc1	$f16,0x690($sp)
/*  f11fdd0:	27b0065c */ 	addiu	$s0,$sp,0x65c
/*  f11fdd4:	44806000 */ 	mtc1	$zero,$f12
/*  f11fdd8:	46101101 */ 	sub.s	$f4,$f2,$f16
/*  f11fddc:	02003025 */ 	or	$a2,$s0,$zero
/*  f11fde0:	46041183 */ 	div.s	$f6,$f2,$f4
/*  f11fde4:	46003202 */ 	mul.s	$f8,$f6,$f0
/*  f11fde8:	46164380 */ 	add.s	$f14,$f8,$f22
/*  f11fdec:	0fc47c00 */ 	jal	func0f11f000
/*  f11fdf0:	e7ae054c */ 	swc1	$f14,0x54c($sp)
/*  f11fdf4:	02202025 */ 	or	$a0,$s1,$zero
/*  f11fdf8:	27a5068c */ 	addiu	$a1,$sp,0x68c
/*  f11fdfc:	0fc47ce1 */ 	jal	func0f11f384
/*  f11fe00:	02003025 */ 	or	$a2,$s0,$zero
/*  f11fe04:	02002025 */ 	or	$a0,$s0,$zero
/*  f11fe08:	27a505fc */ 	addiu	$a1,$sp,0x5fc
/*  f11fe0c:	0fc47c1f */ 	jal	func0f11f07c
/*  f11fe10:	27a60574 */ 	addiu	$a2,$sp,0x574
/*  f11fe14:	02002025 */ 	or	$a0,$s0,$zero
/*  f11fe18:	27a5059c */ 	addiu	$a1,$sp,0x59c
/*  f11fe1c:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11fe20:	27a60554 */ 	addiu	$a2,$sp,0x554
/*  f11fe24:	10000005 */ 	b	.L0f11fe3c
/*  f11fe28:	8fae0534 */ 	lw	$t6,0x534($sp)
/*  f11fe2c:	44805000 */ 	mtc1	$zero,$f10
.L0f11fe30:
/*  f11fe30:	00000000 */ 	nop
/*  f11fe34:	e7aa054c */ 	swc1	$f10,0x54c($sp)
/*  f11fe38:	8fae0534 */ 	lw	$t6,0x534($sp)
.L0f11fe3c:
/*  f11fe3c:	8fac052c */ 	lw	$t4,0x52c($sp)
/*  f11fe40:	51cc0021 */ 	beql	$t6,$t4,.L0f11fec8
/*  f11fe44:	44803000 */ 	mtc1	$zero,$f6
/*  f11fe48:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f11fe4c:	00000000 */ 	nop
/*  f11fe50:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f11fe54:	46000586 */ 	mov.s	$f22,$f0
/*  f11fe58:	c7b0069c */ 	lwc1	$f16,0x69c($sp)
/*  f11fe5c:	c7a40684 */ 	lwc1	$f4,0x684($sp)
/*  f11fe60:	46048181 */ 	sub.s	$f6,$f16,$f4
/*  f11fe64:	46068203 */ 	div.s	$f8,$f16,$f6
/*  f11fe68:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f11fe6c:	46165100 */ 	add.s	$f4,$f10,$f22
/*  f11fe70:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f11fe74:	e7a40548 */ 	swc1	$f4,0x548($sp)
/*  f11fe78:	27b00650 */ 	addiu	$s0,$sp,0x650
/*  f11fe7c:	02003025 */ 	or	$a2,$s0,$zero
/*  f11fe80:	461c0301 */ 	sub.s	$f12,$f0,$f28
/*  f11fe84:	0fc47c00 */ 	jal	func0f11f000
/*  f11fe88:	c7ae0548 */ 	lwc1	$f14,0x548($sp)
/*  f11fe8c:	27a40698 */ 	addiu	$a0,$sp,0x698
/*  f11fe90:	27a50680 */ 	addiu	$a1,$sp,0x680
/*  f11fe94:	0fc47ce1 */ 	jal	func0f11f384
/*  f11fe98:	02003025 */ 	or	$a2,$s0,$zero
/*  f11fe9c:	02002025 */ 	or	$a0,$s0,$zero
/*  f11fea0:	27a505f0 */ 	addiu	$a1,$sp,0x5f0
/*  f11fea4:	0fc47c1f */ 	jal	func0f11f07c
/*  f11fea8:	27a60570 */ 	addiu	$a2,$sp,0x570
/*  f11feac:	02002025 */ 	or	$a0,$s0,$zero
/*  f11feb0:	27a50590 */ 	addiu	$a1,$sp,0x590
/*  f11feb4:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11feb8:	27a60550 */ 	addiu	$a2,$sp,0x550
/*  f11febc:	10000005 */ 	b	.L0f11fed4
/*  f11fec0:	8fa90538 */ 	lw	$t1,0x538($sp)
/*  f11fec4:	44803000 */ 	mtc1	$zero,$f6
.L0f11fec8:
/*  f11fec8:	00000000 */ 	nop
/*  f11fecc:	e7a60548 */ 	swc1	$f6,0x548($sp)
/*  f11fed0:	8fa90538 */ 	lw	$t1,0x538($sp)
.L0f11fed4:
/*  f11fed4:	8fab0534 */ 	lw	$t3,0x534($sp)
/*  f11fed8:	512b001c */ 	beql	$t1,$t3,.L0f11ff4c
/*  f11fedc:	8faf0530 */ 	lw	$t7,0x530($sp)
/*  f11fee0:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f11fee4:	00000000 */ 	nop
/*  f11fee8:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f11feec:	46000586 */ 	mov.s	$f22,$f0
/*  f11fef0:	c7a206a8 */ 	lwc1	$f2,0x6a8($sp)
/*  f11fef4:	c7b0069c */ 	lwc1	$f16,0x69c($sp)
/*  f11fef8:	27b00674 */ 	addiu	$s0,$sp,0x674
/*  f11fefc:	44807000 */ 	mtc1	$zero,$f14
/*  f11ff00:	46101201 */ 	sub.s	$f8,$f2,$f16
/*  f11ff04:	02003025 */ 	or	$a2,$s0,$zero
/*  f11ff08:	46081283 */ 	div.s	$f10,$f2,$f8
/*  f11ff0c:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f11ff10:	0fc47c00 */ 	jal	func0f11f000
/*  f11ff14:	46162300 */ 	add.s	$f12,$f4,$f22
/*  f11ff18:	02202025 */ 	or	$a0,$s1,$zero
/*  f11ff1c:	27a50698 */ 	addiu	$a1,$sp,0x698
/*  f11ff20:	0fc47ce1 */ 	jal	func0f11f384
/*  f11ff24:	02003025 */ 	or	$a2,$s0,$zero
/*  f11ff28:	02002025 */ 	or	$a0,$s0,$zero
/*  f11ff2c:	27a50614 */ 	addiu	$a1,$sp,0x614
/*  f11ff30:	0fc47c1f */ 	jal	func0f11f07c
/*  f11ff34:	27a6057c */ 	addiu	$a2,$sp,0x57c
/*  f11ff38:	02002025 */ 	or	$a0,$s0,$zero
/*  f11ff3c:	27a505b4 */ 	addiu	$a1,$sp,0x5b4
/*  f11ff40:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11ff44:	27a6055c */ 	addiu	$a2,$sp,0x55c
/*  f11ff48:	8faf0530 */ 	lw	$t7,0x530($sp)
.L0f11ff4c:
/*  f11ff4c:	8fb8052c */ 	lw	$t8,0x52c($sp)
/*  f11ff50:	51f8001e */ 	beql	$t7,$t8,.L0f11ffcc
/*  f11ff54:	8fb90538 */ 	lw	$t9,0x538($sp)
/*  f11ff58:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f11ff5c:	00000000 */ 	nop
/*  f11ff60:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f11ff64:	46000586 */ 	mov.s	$f22,$f0
/*  f11ff68:	c7b00690 */ 	lwc1	$f16,0x690($sp)
/*  f11ff6c:	c7a60684 */ 	lwc1	$f6,0x684($sp)
/*  f11ff70:	46068201 */ 	sub.s	$f8,$f16,$f6
/*  f11ff74:	46088283 */ 	div.s	$f10,$f16,$f8
/*  f11ff78:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f11ff7c:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f11ff80:	46162500 */ 	add.s	$f20,$f4,$f22
/*  f11ff84:	27b00668 */ 	addiu	$s0,$sp,0x668
/*  f11ff88:	02003025 */ 	or	$a2,$s0,$zero
/*  f11ff8c:	4600a306 */ 	mov.s	$f12,$f20
/*  f11ff90:	0fc47c00 */ 	jal	func0f11f000
/*  f11ff94:	461c0381 */ 	sub.s	$f14,$f0,$f28
/*  f11ff98:	27a4068c */ 	addiu	$a0,$sp,0x68c
/*  f11ff9c:	27a50680 */ 	addiu	$a1,$sp,0x680
/*  f11ffa0:	0fc47ce1 */ 	jal	func0f11f384
/*  f11ffa4:	02003025 */ 	or	$a2,$s0,$zero
/*  f11ffa8:	02002025 */ 	or	$a0,$s0,$zero
/*  f11ffac:	27a50608 */ 	addiu	$a1,$sp,0x608
/*  f11ffb0:	0fc47c1f */ 	jal	func0f11f07c
/*  f11ffb4:	27a60578 */ 	addiu	$a2,$sp,0x578
/*  f11ffb8:	02002025 */ 	or	$a0,$s0,$zero
/*  f11ffbc:	27a505a8 */ 	addiu	$a1,$sp,0x5a8
/*  f11ffc0:	0fc47c7f */ 	jal	func0f11f1fc
/*  f11ffc4:	27a60558 */ 	addiu	$a2,$sp,0x558
/*  f11ffc8:	8fb90538 */ 	lw	$t9,0x538($sp)
.L0f11ffcc:
/*  f11ffcc:	8fad0534 */ 	lw	$t5,0x534($sp)
/*  f11ffd0:	8fa90530 */ 	lw	$t1,0x530($sp)
/*  f11ffd4:	8fb8052c */ 	lw	$t8,0x52c($sp)
/*  f11ffd8:	001950c0 */ 	sll	$t2,$t9,0x3
/*  f11ffdc:	000d7080 */ 	sll	$t6,$t5,0x2
/*  f11ffe0:	014e6025 */ 	or	$t4,$t2,$t6
/*  f11ffe4:	00095840 */ 	sll	$t3,$t1,0x1
/*  f11ffe8:	018b7825 */ 	or	$t7,$t4,$t3
/*  f11ffec:	01f8c825 */ 	or	$t9,$t7,$t8
/*  f11fff0:	2f210010 */ 	sltiu	$at,$t9,0x10
/*  f11fff4:	1020037c */ 	beqz	$at,.L0f120de8
/*  f11fff8:	afb90068 */ 	sw	$t9,0x68($sp)
/*  f11fffc:	00196880 */ 	sll	$t5,$t9,0x2
/*  f120000:	3c017f1b */ 	lui	$at,%hi(var7f1b5004)
/*  f120004:	002d0821 */ 	addu	$at,$at,$t5
/*  f120008:	8c2d5004 */ 	lw	$t5,%lo(var7f1b5004)($at)
/*  f12000c:	01a00008 */ 	jr	$t5
/*  f120010:	00000000 */ 	nop
/*  f120014:	3c017f1b */ 	lui	$at,%hi(var7f1b5044)
/*  f120018:	00008825 */ 	or	$s1,$zero,$zero
/*  f12001c:	10000374 */ 	b	.L0f120df0
/*  f120020:	c4385044 */ 	lwc1	$f24,%lo(var7f1b5044)($at)
/*  f120024:	3c017f1b */ 	lui	$at,%hi(var7f1b5048)
/*  f120028:	c4385048 */ 	lwc1	$f24,%lo(var7f1b5048)($at)
/*  f12002c:	c7a205e4 */ 	lwc1	$f2,0x5e4($sp)
/*  f120030:	c7a805e8 */ 	lwc1	$f8,0x5e8($sp)
/*  f120034:	c7ac05ec */ 	lwc1	$f12,0x5ec($sp)
/*  f120038:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f12003c:	c7ae05d8 */ 	lwc1	$f14,0x5d8($sp)
/*  f120040:	c7b005e0 */ 	lwc1	$f16,0x5e0($sp)
/*  f120044:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120048:	c7a805dc */ 	lwc1	$f8,0x5dc($sp)
/*  f12004c:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f120050:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f120054:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f120058:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f12005c:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f120060:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f120064:	c7b605c0 */ 	lwc1	$f22,0x5c0($sp)
/*  f120068:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f12006c:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f120070:	c7a805d0 */ 	lwc1	$f8,0x5d0($sp)
/*  f120074:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f120078:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f12007c:	c7ba05c8 */ 	lwc1	$f26,0x5c8($sp)
/*  f120080:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f120084:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f120088:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f12008c:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120090:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f120094:	c7a805c4 */ 	lwc1	$f8,0x5c4($sp)
/*  f120098:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f12009c:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1200a0:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1200a4:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f1200a8:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f1200ac:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1200b0:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1200b4:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f1200b8:	46008200 */ 	add.s	$f8,$f16,$f0
/*  f1200bc:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f1200c0:	e7a60484 */ 	swc1	$f6,0x484($sp)
/*  f1200c4:	46006180 */ 	add.s	$f6,$f12,$f0
/*  f1200c8:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f1200cc:	e7aa0488 */ 	swc1	$f10,0x488($sp)
/*  f1200d0:	4600a280 */ 	add.s	$f10,$f20,$f0
/*  f1200d4:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f1200d8:	e7a4048c */ 	swc1	$f4,0x48c($sp)
/*  f1200dc:	4600d100 */ 	add.s	$f4,$f26,$f0
/*  f1200e0:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f1200e4:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f1200e8:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f1200ec:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f1200f0:	e7a20448 */ 	swc1	$f2,0x448($sp)
/*  f1200f4:	e7ae0460 */ 	swc1	$f14,0x460($sp)
/*  f1200f8:	e7b20478 */ 	swc1	$f18,0x478($sp)
/*  f1200fc:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120100:	e7b60490 */ 	swc1	$f22,0x490($sp)
/*  f120104:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120108:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12010c:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f120110:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120114:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120118:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f12011c:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f120120:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120124:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f120128:	10000331 */ 	b	.L0f120df0
/*  f12012c:	00000000 */ 	nop
/*  f120130:	3c017f1b */ 	lui	$at,%hi(var7f1b504c)
/*  f120134:	c438504c */ 	lwc1	$f24,%lo(var7f1b504c)($at)
/*  f120138:	c7a205e4 */ 	lwc1	$f2,0x5e4($sp)
/*  f12013c:	c7a805e8 */ 	lwc1	$f8,0x5e8($sp)
/*  f120140:	c7ac05ec */ 	lwc1	$f12,0x5ec($sp)
/*  f120144:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f120148:	c7ae05d8 */ 	lwc1	$f14,0x5d8($sp)
/*  f12014c:	c7b005e0 */ 	lwc1	$f16,0x5e0($sp)
/*  f120150:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120154:	c7a805dc */ 	lwc1	$f8,0x5dc($sp)
/*  f120158:	c7b2059c */ 	lwc1	$f18,0x59c($sp)
/*  f12015c:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f120160:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f120164:	c7b405a4 */ 	lwc1	$f20,0x5a4($sp)
/*  f120168:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f12016c:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f120170:	c7b60590 */ 	lwc1	$f22,0x590($sp)
/*  f120174:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120178:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f12017c:	c7a805a0 */ 	lwc1	$f8,0x5a0($sp)
/*  f120180:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f120184:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f120188:	c7ba0598 */ 	lwc1	$f26,0x598($sp)
/*  f12018c:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f120190:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f120194:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f120198:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f12019c:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f1201a0:	c7a80594 */ 	lwc1	$f8,0x594($sp)
/*  f1201a4:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f1201a8:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1201ac:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1201b0:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f1201b4:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f1201b8:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1201bc:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1201c0:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f1201c4:	46008200 */ 	add.s	$f8,$f16,$f0
/*  f1201c8:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f1201cc:	e7a60484 */ 	swc1	$f6,0x484($sp)
/*  f1201d0:	46006180 */ 	add.s	$f6,$f12,$f0
/*  f1201d4:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f1201d8:	e7aa0488 */ 	swc1	$f10,0x488($sp)
/*  f1201dc:	4600a280 */ 	add.s	$f10,$f20,$f0
/*  f1201e0:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f1201e4:	e7a4048c */ 	swc1	$f4,0x48c($sp)
/*  f1201e8:	4600d100 */ 	add.s	$f4,$f26,$f0
/*  f1201ec:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f1201f0:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f1201f4:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f1201f8:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f1201fc:	e7a20448 */ 	swc1	$f2,0x448($sp)
/*  f120200:	e7ae0460 */ 	swc1	$f14,0x460($sp)
/*  f120204:	e7b20478 */ 	swc1	$f18,0x478($sp)
/*  f120208:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12020c:	e7b60490 */ 	swc1	$f22,0x490($sp)
/*  f120210:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120214:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120218:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f12021c:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120220:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120224:	8fa50554 */ 	lw	$a1,0x554($sp)
/*  f120228:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f12022c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120230:	8fa50550 */ 	lw	$a1,0x550($sp)
/*  f120234:	100002ee */ 	b	.L0f120df0
/*  f120238:	00000000 */ 	nop
/*  f12023c:	3c017f1b */ 	lui	$at,%hi(var7f1b5050)
/*  f120240:	c4385050 */ 	lwc1	$f24,%lo(var7f1b5050)($at)
/*  f120244:	c7b605c0 */ 	lwc1	$f22,0x5c0($sp)
/*  f120248:	c7a805c4 */ 	lwc1	$f8,0x5c4($sp)
/*  f12024c:	c7ba05c8 */ 	lwc1	$f26,0x5c8($sp)
/*  f120250:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f120254:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f120258:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f12025c:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120260:	c7a805d0 */ 	lwc1	$f8,0x5d0($sp)
/*  f120264:	c7ae0590 */ 	lwc1	$f14,0x590($sp)
/*  f120268:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f12026c:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f120270:	c7b00598 */ 	lwc1	$f16,0x598($sp)
/*  f120274:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f120278:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f12027c:	c7a2059c */ 	lwc1	$f2,0x59c($sp)
/*  f120280:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120284:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f120288:	c7a80594 */ 	lwc1	$f8,0x594($sp)
/*  f12028c:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f120290:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f120294:	c7ac05a4 */ 	lwc1	$f12,0x5a4($sp)
/*  f120298:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f12029c:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f1202a0:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1202a4:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1202a8:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f1202ac:	c7a805a0 */ 	lwc1	$f8,0x5a0($sp)
/*  f1202b0:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f1202b4:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1202b8:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1202bc:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f1202c0:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f1202c4:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f1202c8:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1202cc:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f1202d0:	4600a200 */ 	add.s	$f8,$f20,$f0
/*  f1202d4:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f1202d8:	e7a60484 */ 	swc1	$f6,0x484($sp)
/*  f1202dc:	4600d180 */ 	add.s	$f6,$f26,$f0
/*  f1202e0:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1202e4:	e7aa0488 */ 	swc1	$f10,0x488($sp)
/*  f1202e8:	46008280 */ 	add.s	$f10,$f16,$f0
/*  f1202ec:	afaa0430 */ 	sw	$t2,0x430($sp)
/*  f1202f0:	e7a4048c */ 	swc1	$f4,0x48c($sp)
/*  f1202f4:	46006100 */ 	add.s	$f4,$f12,$f0
/*  f1202f8:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f1202fc:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f120300:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f120304:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f120308:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f12030c:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f120310:	e7b60448 */ 	swc1	$f22,0x448($sp)
/*  f120314:	e7b20460 */ 	swc1	$f18,0x460($sp)
/*  f120318:	e7ae0478 */ 	swc1	$f14,0x478($sp)
/*  f12031c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120320:	e7a20490 */ 	swc1	$f2,0x490($sp)
/*  f120324:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120328:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12032c:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f120330:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120334:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120338:	8fa50550 */ 	lw	$a1,0x550($sp)
/*  f12033c:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f120340:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120344:	8fa50554 */ 	lw	$a1,0x554($sp)
/*  f120348:	100002a9 */ 	b	.L0f120df0
/*  f12034c:	00000000 */ 	nop
/*  f120350:	3c017f1b */ 	lui	$at,%hi(var7f1b5054)
/*  f120354:	c4385054 */ 	lwc1	$f24,%lo(var7f1b5054)($at)
/*  f120358:	c7ae05d8 */ 	lwc1	$f14,0x5d8($sp)
/*  f12035c:	c7a805dc */ 	lwc1	$f8,0x5dc($sp)
/*  f120360:	c7b005e0 */ 	lwc1	$f16,0x5e0($sp)
/*  f120364:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f120368:	c7b605c0 */ 	lwc1	$f22,0x5c0($sp)
/*  f12036c:	c7ba05c8 */ 	lwc1	$f26,0x5c8($sp)
/*  f120370:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120374:	c7a805c4 */ 	lwc1	$f8,0x5c4($sp)
/*  f120378:	c7a205b4 */ 	lwc1	$f2,0x5b4($sp)
/*  f12037c:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f120380:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f120384:	c7ac05bc */ 	lwc1	$f12,0x5bc($sp)
/*  f120388:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f12038c:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f120390:	c7b205a8 */ 	lwc1	$f18,0x5a8($sp)
/*  f120394:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120398:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f12039c:	c7a805b8 */ 	lwc1	$f8,0x5b8($sp)
/*  f1203a0:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f1203a4:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f1203a8:	c7b405b0 */ 	lwc1	$f20,0x5b0($sp)
/*  f1203ac:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f1203b0:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f1203b4:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1203b8:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1203bc:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f1203c0:	c7a805ac */ 	lwc1	$f8,0x5ac($sp)
/*  f1203c4:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f1203c8:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1203cc:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1203d0:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f1203d4:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f1203d8:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1203dc:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1203e0:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f1203e4:	4600d200 */ 	add.s	$f8,$f26,$f0
/*  f1203e8:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f1203ec:	e7a60484 */ 	swc1	$f6,0x484($sp)
/*  f1203f0:	46008180 */ 	add.s	$f6,$f16,$f0
/*  f1203f4:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f1203f8:	e7aa0488 */ 	swc1	$f10,0x488($sp)
/*  f1203fc:	46006280 */ 	add.s	$f10,$f12,$f0
/*  f120400:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f120404:	e7a4048c */ 	swc1	$f4,0x48c($sp)
/*  f120408:	4600a100 */ 	add.s	$f4,$f20,$f0
/*  f12040c:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f120410:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120414:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f120418:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f12041c:	e7ae0448 */ 	swc1	$f14,0x448($sp)
/*  f120420:	e7b60460 */ 	swc1	$f22,0x460($sp)
/*  f120424:	e7a20478 */ 	swc1	$f2,0x478($sp)
/*  f120428:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12042c:	e7b20490 */ 	swc1	$f18,0x490($sp)
/*  f120430:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120434:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120438:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f12043c:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120440:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120444:	8fa5055c */ 	lw	$a1,0x55c($sp)
/*  f120448:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f12044c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120450:	8fa50558 */ 	lw	$a1,0x558($sp)
/*  f120454:	10000266 */ 	b	.L0f120df0
/*  f120458:	00000000 */ 	nop
/*  f12045c:	3c017f1b */ 	lui	$at,%hi(var7f1b5058)
/*  f120460:	c4385058 */ 	lwc1	$f24,%lo(var7f1b5058)($at)
/*  f120464:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f120468:	c7a805d0 */ 	lwc1	$f8,0x5d0($sp)
/*  f12046c:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f120470:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f120474:	c7a205e4 */ 	lwc1	$f2,0x5e4($sp)
/*  f120478:	c7ac05ec */ 	lwc1	$f12,0x5ec($sp)
/*  f12047c:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120480:	c7a805e8 */ 	lwc1	$f8,0x5e8($sp)
/*  f120484:	c7b605a8 */ 	lwc1	$f22,0x5a8($sp)
/*  f120488:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f12048c:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f120490:	c7ba05b0 */ 	lwc1	$f26,0x5b0($sp)
/*  f120494:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f120498:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f12049c:	c7ae05b4 */ 	lwc1	$f14,0x5b4($sp)
/*  f1204a0:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1204a4:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f1204a8:	c7a805ac */ 	lwc1	$f8,0x5ac($sp)
/*  f1204ac:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f1204b0:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f1204b4:	c7b005bc */ 	lwc1	$f16,0x5bc($sp)
/*  f1204b8:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f1204bc:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f1204c0:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1204c4:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1204c8:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f1204cc:	c7a805b8 */ 	lwc1	$f8,0x5b8($sp)
/*  f1204d0:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f1204d4:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1204d8:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1204dc:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f1204e0:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f1204e4:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1204e8:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1204ec:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f1204f0:	46006200 */ 	add.s	$f8,$f12,$f0
/*  f1204f4:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f1204f8:	e7a60484 */ 	swc1	$f6,0x484($sp)
/*  f1204fc:	4600a180 */ 	add.s	$f6,$f20,$f0
/*  f120500:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f120504:	e7aa0488 */ 	swc1	$f10,0x488($sp)
/*  f120508:	4600d280 */ 	add.s	$f10,$f26,$f0
/*  f12050c:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f120510:	e7a4048c */ 	swc1	$f4,0x48c($sp)
/*  f120514:	46008100 */ 	add.s	$f4,$f16,$f0
/*  f120518:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f12051c:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120520:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f120524:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f120528:	e7b20448 */ 	swc1	$f18,0x448($sp)
/*  f12052c:	e7a20460 */ 	swc1	$f2,0x460($sp)
/*  f120530:	e7b60478 */ 	swc1	$f22,0x478($sp)
/*  f120534:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120538:	e7ae0490 */ 	swc1	$f14,0x490($sp)
/*  f12053c:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120540:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120544:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f120548:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f12054c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120550:	8fa50558 */ 	lw	$a1,0x558($sp)
/*  f120554:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f120558:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12055c:	8fa5055c */ 	lw	$a1,0x55c($sp)
/*  f120560:	10000223 */ 	b	.L0f120df0
/*  f120564:	00000000 */ 	nop
/*  f120568:	3c017f1b */ 	lui	$at,%hi(var7f1b505c)
/*  f12056c:	c438505c */ 	lwc1	$f24,%lo(var7f1b505c)($at)
/*  f120570:	c7b605c0 */ 	lwc1	$f22,0x5c0($sp)
/*  f120574:	c7a805c4 */ 	lwc1	$f8,0x5c4($sp)
/*  f120578:	c7ba05c8 */ 	lwc1	$f26,0x5c8($sp)
/*  f12057c:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f120580:	c7ae05a8 */ 	lwc1	$f14,0x5a8($sp)
/*  f120584:	c7b005b0 */ 	lwc1	$f16,0x5b0($sp)
/*  f120588:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f12058c:	c7a805ac */ 	lwc1	$f8,0x5ac($sp)
/*  f120590:	c7a20590 */ 	lwc1	$f2,0x590($sp)
/*  f120594:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f120598:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f12059c:	c7ac0598 */ 	lwc1	$f12,0x598($sp)
/*  f1205a0:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f1205a4:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f1205a8:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1205ac:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1205b0:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f1205b4:	c7a80594 */ 	lwc1	$f8,0x594($sp)
/*  f1205b8:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f1205bc:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f1205c0:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1205c4:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f1205c8:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f1205cc:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f1205d0:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1205d4:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f1205d8:	46008200 */ 	add.s	$f8,$f16,$f0
/*  f1205dc:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f1205e0:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1205e4:	4600d180 */ 	add.s	$f6,$f26,$f0
/*  f1205e8:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f1205ec:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f1205f0:	46006280 */ 	add.s	$f10,$f12,$f0
/*  f1205f4:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f1205f8:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f1205fc:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120600:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f120604:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f120608:	e7b60448 */ 	swc1	$f22,0x448($sp)
/*  f12060c:	e7ae0460 */ 	swc1	$f14,0x460($sp)
/*  f120610:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120614:	e7a20478 */ 	swc1	$f2,0x478($sp)
/*  f120618:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f12061c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120620:	8fa50558 */ 	lw	$a1,0x558($sp)
/*  f120624:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120628:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12062c:	8fa50550 */ 	lw	$a1,0x550($sp)
/*  f120630:	100001ef */ 	b	.L0f120df0
/*  f120634:	00000000 */ 	nop
/*  f120638:	3c017f1b */ 	lui	$at,%hi(var7f1b5060)
/*  f12063c:	c4385060 */ 	lwc1	$f24,%lo(var7f1b5060)($at)
/*  f120640:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f120644:	c7a605d0 */ 	lwc1	$f6,0x5d0($sp)
/*  f120648:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f12064c:	46189102 */ 	mul.s	$f4,$f18,$f24
/*  f120650:	c7a2059c */ 	lwc1	$f2,0x59c($sp)
/*  f120654:	c7ac05a4 */ 	lwc1	$f12,0x5a4($sp)
/*  f120658:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f12065c:	c7a605a0 */ 	lwc1	$f6,0x5a0($sp)
/*  f120660:	c7ae05a8 */ 	lwc1	$f14,0x5a8($sp)
/*  f120664:	4618a282 */ 	mul.s	$f10,$f20,$f24
/*  f120668:	e7a4043c */ 	swc1	$f4,0x43c($sp)
/*  f12066c:	c7b005b0 */ 	lwc1	$f16,0x5b0($sp)
/*  f120670:	46181102 */ 	mul.s	$f4,$f2,$f24
/*  f120674:	e7a80440 */ 	swc1	$f8,0x440($sp)
/*  f120678:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f12067c:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120680:	e7aa0444 */ 	swc1	$f10,0x444($sp)
/*  f120684:	c7a605ac */ 	lwc1	$f6,0x5ac($sp)
/*  f120688:	46186282 */ 	mul.s	$f10,$f12,$f24
/*  f12068c:	e7a40454 */ 	swc1	$f4,0x454($sp)
/*  f120690:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f120694:	46187102 */ 	mul.s	$f4,$f14,$f24
/*  f120698:	e7a80458 */ 	swc1	$f8,0x458($sp)
/*  f12069c:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f1206a0:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f1206a4:	e7aa045c */ 	swc1	$f10,0x45c($sp)
/*  f1206a8:	46006180 */ 	add.s	$f6,$f12,$f0
/*  f1206ac:	46188282 */ 	mul.s	$f10,$f16,$f24
/*  f1206b0:	e7a4046c */ 	swc1	$f4,0x46c($sp)
/*  f1206b4:	4600a100 */ 	add.s	$f4,$f20,$f0
/*  f1206b8:	e7a60464 */ 	swc1	$f6,0x464($sp)
/*  f1206bc:	e7a80470 */ 	swc1	$f8,0x470($sp)
/*  f1206c0:	46008200 */ 	add.s	$f8,$f16,$f0
/*  f1206c4:	e7a4044c */ 	swc1	$f4,0x44c($sp)
/*  f1206c8:	e7aa0474 */ 	swc1	$f10,0x474($sp)
/*  f1206cc:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f1206d0:	e7a8047c */ 	swc1	$f8,0x47c($sp)
/*  f1206d4:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f1206d8:	e7b20448 */ 	swc1	$f18,0x448($sp)
/*  f1206dc:	e7a20460 */ 	swc1	$f2,0x460($sp)
/*  f1206e0:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1206e4:	e7ae0478 */ 	swc1	$f14,0x478($sp)
/*  f1206e8:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f1206ec:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1206f0:	8fa50554 */ 	lw	$a1,0x554($sp)
/*  f1206f4:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f1206f8:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1206fc:	8fa50558 */ 	lw	$a1,0x558($sp)
/*  f120700:	100001bb */ 	b	.L0f120df0
/*  f120704:	00000000 */ 	nop
/*  f120708:	3c017f1b */ 	lui	$at,%hi(var7f1b5064)
/*  f12070c:	c4385064 */ 	lwc1	$f24,%lo(var7f1b5064)($at)
/*  f120710:	c7ae05d8 */ 	lwc1	$f14,0x5d8($sp)
/*  f120714:	c7a405dc */ 	lwc1	$f4,0x5dc($sp)
/*  f120718:	c7b005e0 */ 	lwc1	$f16,0x5e0($sp)
/*  f12071c:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f120720:	c7b20590 */ 	lwc1	$f18,0x590($sp)
/*  f120724:	c7b40598 */ 	lwc1	$f20,0x598($sp)
/*  f120728:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f12072c:	c7a40594 */ 	lwc1	$f4,0x594($sp)
/*  f120730:	c7a205b4 */ 	lwc1	$f2,0x5b4($sp)
/*  f120734:	46188202 */ 	mul.s	$f8,$f16,$f24
/*  f120738:	e7aa043c */ 	swc1	$f10,0x43c($sp)
/*  f12073c:	c7ac05bc */ 	lwc1	$f12,0x5bc($sp)
/*  f120740:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f120744:	e7a60440 */ 	swc1	$f6,0x440($sp)
/*  f120748:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f12074c:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120750:	e7a80444 */ 	swc1	$f8,0x444($sp)
/*  f120754:	c7a405b8 */ 	lwc1	$f4,0x5b8($sp)
/*  f120758:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f12075c:	e7aa0454 */ 	swc1	$f10,0x454($sp)
/*  f120760:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f120764:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f120768:	e7a60458 */ 	swc1	$f6,0x458($sp)
/*  f12076c:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f120770:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120774:	e7a8045c */ 	swc1	$f8,0x45c($sp)
/*  f120778:	4600a100 */ 	add.s	$f4,$f20,$f0
/*  f12077c:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f120780:	e7aa046c */ 	swc1	$f10,0x46c($sp)
/*  f120784:	46008280 */ 	add.s	$f10,$f16,$f0
/*  f120788:	e7a40464 */ 	swc1	$f4,0x464($sp)
/*  f12078c:	e7a60470 */ 	swc1	$f6,0x470($sp)
/*  f120790:	46006180 */ 	add.s	$f6,$f12,$f0
/*  f120794:	e7aa044c */ 	swc1	$f10,0x44c($sp)
/*  f120798:	e7a80474 */ 	swc1	$f8,0x474($sp)
/*  f12079c:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f1207a0:	e7a6047c */ 	swc1	$f6,0x47c($sp)
/*  f1207a4:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f1207a8:	e7ae0448 */ 	swc1	$f14,0x448($sp)
/*  f1207ac:	e7b20460 */ 	swc1	$f18,0x460($sp)
/*  f1207b0:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1207b4:	e7a20478 */ 	swc1	$f2,0x478($sp)
/*  f1207b8:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f1207bc:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1207c0:	8fa50550 */ 	lw	$a1,0x550($sp)
/*  f1207c4:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f1207c8:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1207cc:	8fa5055c */ 	lw	$a1,0x55c($sp)
/*  f1207d0:	10000187 */ 	b	.L0f120df0
/*  f1207d4:	00000000 */ 	nop
/*  f1207d8:	3c017f1b */ 	lui	$at,%hi(var7f1b5068)
/*  f1207dc:	c4385068 */ 	lwc1	$f24,%lo(var7f1b5068)($at)
/*  f1207e0:	c7a205e4 */ 	lwc1	$f2,0x5e4($sp)
/*  f1207e4:	c7aa05e8 */ 	lwc1	$f10,0x5e8($sp)
/*  f1207e8:	c7ac05ec */ 	lwc1	$f12,0x5ec($sp)
/*  f1207ec:	46181202 */ 	mul.s	$f8,$f2,$f24
/*  f1207f0:	c7ae05b4 */ 	lwc1	$f14,0x5b4($sp)
/*  f1207f4:	c7b005bc */ 	lwc1	$f16,0x5bc($sp)
/*  f1207f8:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f1207fc:	c7aa05b8 */ 	lwc1	$f10,0x5b8($sp)
/*  f120800:	c7b2059c */ 	lwc1	$f18,0x59c($sp)
/*  f120804:	46186182 */ 	mul.s	$f6,$f12,$f24
/*  f120808:	e7a8043c */ 	swc1	$f8,0x43c($sp)
/*  f12080c:	c7b405a4 */ 	lwc1	$f20,0x5a4($sp)
/*  f120810:	46187202 */ 	mul.s	$f8,$f14,$f24
/*  f120814:	e7a40440 */ 	swc1	$f4,0x440($sp)
/*  f120818:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f12081c:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f120820:	e7a60444 */ 	swc1	$f6,0x444($sp)
/*  f120824:	c7aa05a0 */ 	lwc1	$f10,0x5a0($sp)
/*  f120828:	46188182 */ 	mul.s	$f6,$f16,$f24
/*  f12082c:	e7a80454 */ 	swc1	$f8,0x454($sp)
/*  f120830:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f120834:	46189202 */ 	mul.s	$f8,$f18,$f24
/*  f120838:	e7a40458 */ 	swc1	$f4,0x458($sp)
/*  f12083c:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f120840:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f120844:	e7a6045c */ 	swc1	$f6,0x45c($sp)
/*  f120848:	46008280 */ 	add.s	$f10,$f16,$f0
/*  f12084c:	4618a182 */ 	mul.s	$f6,$f20,$f24
/*  f120850:	e7a8046c */ 	swc1	$f8,0x46c($sp)
/*  f120854:	46006200 */ 	add.s	$f8,$f12,$f0
/*  f120858:	e7aa0464 */ 	swc1	$f10,0x464($sp)
/*  f12085c:	e7a40470 */ 	swc1	$f4,0x470($sp)
/*  f120860:	4600a100 */ 	add.s	$f4,$f20,$f0
/*  f120864:	e7a8044c */ 	swc1	$f8,0x44c($sp)
/*  f120868:	e7a60474 */ 	swc1	$f6,0x474($sp)
/*  f12086c:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120870:	e7a4047c */ 	swc1	$f4,0x47c($sp)
/*  f120874:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f120878:	e7a20448 */ 	swc1	$f2,0x448($sp)
/*  f12087c:	e7ae0460 */ 	swc1	$f14,0x460($sp)
/*  f120880:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120884:	e7b20478 */ 	swc1	$f18,0x478($sp)
/*  f120888:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f12088c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120890:	8fa5055c */ 	lw	$a1,0x55c($sp)
/*  f120894:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120898:	0fc47dbb */ 	jal	func0f11f6ec
/*  f12089c:	8fa50554 */ 	lw	$a1,0x554($sp)
/*  f1208a0:	10000153 */ 	b	.L0f120df0
/*  f1208a4:	00000000 */ 	nop
/*  f1208a8:	3c017f1b */ 	lui	$at,%hi(var7f1b506c)
/*  f1208ac:	c438506c */ 	lwc1	$f24,%lo(var7f1b506c)($at)
/*  f1208b0:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f1208b4:	c7a805d0 */ 	lwc1	$f8,0x5d0($sp)
/*  f1208b8:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f1208bc:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f1208c0:	c7a205e4 */ 	lwc1	$f2,0x5e4($sp)
/*  f1208c4:	c7ac05ec */ 	lwc1	$f12,0x5ec($sp)
/*  f1208c8:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1208cc:	c7a805e8 */ 	lwc1	$f8,0x5e8($sp)
/*  f1208d0:	c7ae05d8 */ 	lwc1	$f14,0x5d8($sp)
/*  f1208d4:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f1208d8:	e7a6043c */ 	swc1	$f6,0x43c($sp)
/*  f1208dc:	c7b005e0 */ 	lwc1	$f16,0x5e0($sp)
/*  f1208e0:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f1208e4:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f1208e8:	c7b60590 */ 	lwc1	$f22,0x590($sp)
/*  f1208ec:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1208f0:	e7a40444 */ 	swc1	$f4,0x444($sp)
/*  f1208f4:	c7a805dc */ 	lwc1	$f8,0x5dc($sp)
/*  f1208f8:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f1208fc:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f120900:	c7ba0598 */ 	lwc1	$f26,0x598($sp)
/*  f120904:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f120908:	e7aa0458 */ 	swc1	$f10,0x458($sp)
/*  f12090c:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f120910:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120914:	e7a4045c */ 	swc1	$f4,0x45c($sp)
/*  f120918:	c7a80594 */ 	lwc1	$f8,0x594($sp)
/*  f12091c:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f120920:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f120924:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f120928:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f12092c:	e7aa0470 */ 	swc1	$f10,0x470($sp)
/*  f120930:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f120934:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120938:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f12093c:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120940:	4618d102 */ 	mul.s	$f4,$f26,$f24
/*  f120944:	e7a60484 */ 	swc1	$f6,0x484($sp)
/*  f120948:	c7a605a8 */ 	lwc1	$f6,0x5a8($sp)
/*  f12094c:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f120950:	e7aa0488 */ 	swc1	$f10,0x488($sp)
/*  f120954:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120958:	c7aa05ac */ 	lwc1	$f10,0x5ac($sp)
/*  f12095c:	e7a4048c */ 	swc1	$f4,0x48c($sp)
/*  f120960:	c7a605b0 */ 	lwc1	$f6,0x5b0($sp)
/*  f120964:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f120968:	4600a280 */ 	add.s	$f10,$f20,$f0
/*  f12096c:	e7b20448 */ 	swc1	$f18,0x448($sp)
/*  f120970:	e7a8049c */ 	swc1	$f8,0x49c($sp)
/*  f120974:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120978:	46008180 */ 	add.s	$f6,$f16,$f0
/*  f12097c:	e7aa044c */ 	swc1	$f10,0x44c($sp)
/*  f120980:	e7a404a0 */ 	swc1	$f4,0x4a0($sp)
/*  f120984:	c7aa05a8 */ 	lwc1	$f10,0x5a8($sp)
/*  f120988:	46006100 */ 	add.s	$f4,$f12,$f0
/*  f12098c:	e7a6047c */ 	swc1	$f6,0x47c($sp)
/*  f120990:	e7a804a4 */ 	swc1	$f8,0x4a4($sp)
/*  f120994:	4600d200 */ 	add.s	$f8,$f26,$f0
/*  f120998:	e7a40464 */ 	swc1	$f4,0x464($sp)
/*  f12099c:	c7a405b0 */ 	lwc1	$f4,0x5b0($sp)
/*  f1209a0:	e7a20460 */ 	swc1	$f2,0x460($sp)
/*  f1209a4:	e7a80494 */ 	swc1	$f8,0x494($sp)
/*  f1209a8:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f1209ac:	e7ae0478 */ 	swc1	$f14,0x478($sp)
/*  f1209b0:	e7b60490 */ 	swc1	$f22,0x490($sp)
/*  f1209b4:	e7aa04a8 */ 	swc1	$f10,0x4a8($sp)
/*  f1209b8:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1209bc:	e7a604ac */ 	swc1	$f6,0x4ac($sp)
/*  f1209c0:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f1209c4:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1209c8:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f1209cc:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f1209d0:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1209d4:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f1209d8:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f1209dc:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1209e0:	8fa50550 */ 	lw	$a1,0x550($sp)
/*  f1209e4:	27a4049c */ 	addiu	$a0,$sp,0x49c
/*  f1209e8:	0fc47dbb */ 	jal	func0f11f6ec
/*  f1209ec:	8fa50558 */ 	lw	$a1,0x558($sp)
/*  f1209f0:	100000ff */ 	b	.L0f120df0
/*  f1209f4:	00000000 */ 	nop
/*  f1209f8:	c7ba05e4 */ 	lwc1	$f26,0x5e4($sp)
/*  f1209fc:	c7b605ec */ 	lwc1	$f22,0x5ec($sp)
/*  f120a00:	c7b405d8 */ 	lwc1	$f20,0x5d8($sp)
/*  f120a04:	c7b205e0 */ 	lwc1	$f18,0x5e0($sp)
/*  f120a08:	c7b005c0 */ 	lwc1	$f16,0x5c0($sp)
/*  f120a0c:	c7ae059c */ 	lwc1	$f14,0x59c($sp)
/*  f120a10:	c7ac05a4 */ 	lwc1	$f12,0x5a4($sp)
/*  f120a14:	c7aa05e8 */ 	lwc1	$f10,0x5e8($sp)
/*  f120a18:	c7a805c8 */ 	lwc1	$f8,0x5c8($sp)
/*  f120a1c:	c7a605dc */ 	lwc1	$f6,0x5dc($sp)
/*  f120a20:	3c017f1b */ 	lui	$at,%hi(var7f1b5070)
/*  f120a24:	c4385070 */ 	lwc1	$f24,%lo(var7f1b5070)($at)
/*  f120a28:	c7a405c4 */ 	lwc1	$f4,0x5c4($sp)
/*  f120a2c:	c7a205a8 */ 	lwc1	$f2,0x5a8($sp)
/*  f120a30:	46185282 */ 	mul.s	$f10,$f10,$f24
/*  f120a34:	c7a005ac */ 	lwc1	$f0,0x5ac($sp)
/*  f120a38:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f120a3c:	46183182 */ 	mul.s	$f6,$f6,$f24
/*  f120a40:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f120a44:	e7ba0448 */ 	swc1	$f26,0x448($sp)
/*  f120a48:	4618d682 */ 	mul.s	$f26,$f26,$f24
/*  f120a4c:	e7aa0440 */ 	swc1	$f10,0x440($sp)
/*  f120a50:	c7aa05b0 */ 	lwc1	$f10,0x5b0($sp)
/*  f120a54:	46182102 */ 	mul.s	$f4,$f4,$f24
/*  f120a58:	e7a60458 */ 	swc1	$f6,0x458($sp)
/*  f120a5c:	c7a605a0 */ 	lwc1	$f6,0x5a0($sp)
/*  f120a60:	46181082 */ 	mul.s	$f2,$f2,$f24
/*  f120a64:	e7ba043c */ 	swc1	$f26,0x43c($sp)
/*  f120a68:	c43adb80 */ 	lwc1	$f26,%lo(var8007db80)($at)
/*  f120a6c:	46185282 */ 	mul.s	$f10,$f10,$f24
/*  f120a70:	e7a40470 */ 	swc1	$f4,0x470($sp)
/*  f120a74:	c7a405b0 */ 	lwc1	$f4,0x5b0($sp)
/*  f120a78:	e7b40460 */ 	swc1	$f20,0x460($sp)
/*  f120a7c:	4618a502 */ 	mul.s	$f20,$f20,$f24
/*  f120a80:	e7a20484 */ 	swc1	$f2,0x484($sp)
/*  f120a84:	c7a205a8 */ 	lwc1	$f2,0x5a8($sp)
/*  f120a88:	e7aa048c */ 	swc1	$f10,0x48c($sp)
/*  f120a8c:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f120a90:	e7a20490 */ 	swc1	$f2,0x490($sp)
/*  f120a94:	e7b00478 */ 	swc1	$f16,0x478($sp)
/*  f120a98:	46188402 */ 	mul.s	$f16,$f16,$f24
/*  f120a9c:	e7b40454 */ 	swc1	$f20,0x454($sp)
/*  f120aa0:	e7ae04a8 */ 	swc1	$f14,0x4a8($sp)
/*  f120aa4:	46189502 */ 	mul.s	$f20,$f18,$f24
/*  f120aa8:	e7aa0444 */ 	swc1	$f10,0x444($sp)
/*  f120aac:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120ab0:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120ab4:	e7b0046c */ 	swc1	$f16,0x46c($sp)
/*  f120ab8:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f120abc:	46180002 */ 	mul.s	$f0,$f0,$f24
/*  f120ac0:	e7b4045c */ 	swc1	$f20,0x45c($sp)
/*  f120ac4:	461a9480 */ 	add.s	$f18,$f18,$f26
/*  f120ac8:	46187382 */ 	mul.s	$f14,$f14,$f24
/*  f120acc:	e7aa0474 */ 	swc1	$f10,0x474($sp)
/*  f120ad0:	461ab580 */ 	add.s	$f22,$f22,$f26
/*  f120ad4:	46183182 */ 	mul.s	$f6,$f6,$f24
/*  f120ad8:	e7a00488 */ 	swc1	$f0,0x488($sp)
/*  f120adc:	461a4200 */ 	add.s	$f8,$f8,$f26
/*  f120ae0:	46186002 */ 	mul.s	$f0,$f12,$f24
/*  f120ae4:	e7ae049c */ 	swc1	$f14,0x49c($sp)
/*  f120ae8:	461a2100 */ 	add.s	$f4,$f4,$f26
/*  f120aec:	e7b6044c */ 	swc1	$f22,0x44c($sp)
/*  f120af0:	e7a604a0 */ 	swc1	$f6,0x4a0($sp)
/*  f120af4:	461a6680 */ 	add.s	$f26,$f12,$f26
/*  f120af8:	e7b20464 */ 	swc1	$f18,0x464($sp)
/*  f120afc:	e7a004a4 */ 	swc1	$f0,0x4a4($sp)
/*  f120b00:	e7a8047c */ 	swc1	$f8,0x47c($sp)
/*  f120b04:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f120b08:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120b0c:	e7ba04ac */ 	swc1	$f26,0x4ac($sp)
/*  f120b10:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120b14:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120b18:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f120b1c:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120b20:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120b24:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f120b28:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f120b2c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120b30:	8fa50558 */ 	lw	$a1,0x558($sp)
/*  f120b34:	27a4049c */ 	addiu	$a0,$sp,0x49c
/*  f120b38:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120b3c:	8fa50554 */ 	lw	$a1,0x554($sp)
/*  f120b40:	100000ab */ 	b	.L0f120df0
/*  f120b44:	00000000 */ 	nop
/*  f120b48:	3c017f1b */ 	lui	$at,%hi(var7f1b5074)
/*  f120b4c:	c4385074 */ 	lwc1	$f24,%lo(var7f1b5074)($at)
/*  f120b50:	c7b605c0 */ 	lwc1	$f22,0x5c0($sp)
/*  f120b54:	c7a405c4 */ 	lwc1	$f4,0x5c4($sp)
/*  f120b58:	c7ba05c8 */ 	lwc1	$f26,0x5c8($sp)
/*  f120b5c:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f120b60:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f120b64:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f120b68:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120b6c:	c7a405d0 */ 	lwc1	$f4,0x5d0($sp)
/*  f120b70:	c7a205e4 */ 	lwc1	$f2,0x5e4($sp)
/*  f120b74:	4618d202 */ 	mul.s	$f8,$f26,$f24
/*  f120b78:	e7aa043c */ 	swc1	$f10,0x43c($sp)
/*  f120b7c:	c7ac05ec */ 	lwc1	$f12,0x5ec($sp)
/*  f120b80:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f120b84:	e7a60440 */ 	swc1	$f6,0x440($sp)
/*  f120b88:	c7ae05b4 */ 	lwc1	$f14,0x5b4($sp)
/*  f120b8c:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120b90:	e7a80444 */ 	swc1	$f8,0x444($sp)
/*  f120b94:	c7a405e8 */ 	lwc1	$f4,0x5e8($sp)
/*  f120b98:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f120b9c:	e7aa0454 */ 	swc1	$f10,0x454($sp)
/*  f120ba0:	c7b005bc */ 	lwc1	$f16,0x5bc($sp)
/*  f120ba4:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f120ba8:	e7a60458 */ 	swc1	$f6,0x458($sp)
/*  f120bac:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f120bb0:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120bb4:	e7a8045c */ 	swc1	$f8,0x45c($sp)
/*  f120bb8:	c7a405b8 */ 	lwc1	$f4,0x5b8($sp)
/*  f120bbc:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f120bc0:	e7aa046c */ 	swc1	$f10,0x46c($sp)
/*  f120bc4:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f120bc8:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f120bcc:	e7a60470 */ 	swc1	$f6,0x470($sp)
/*  f120bd0:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f120bd4:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120bd8:	e7a80474 */ 	swc1	$f8,0x474($sp)
/*  f120bdc:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120be0:	46188202 */ 	mul.s	$f8,$f16,$f24
/*  f120be4:	e7aa0484 */ 	swc1	$f10,0x484($sp)
/*  f120be8:	c7aa0590 */ 	lwc1	$f10,0x590($sp)
/*  f120bec:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f120bf0:	e7a60488 */ 	swc1	$f6,0x488($sp)
/*  f120bf4:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f120bf8:	c7a60594 */ 	lwc1	$f6,0x594($sp)
/*  f120bfc:	e7a8048c */ 	swc1	$f8,0x48c($sp)
/*  f120c00:	c7aa0598 */ 	lwc1	$f10,0x598($sp)
/*  f120c04:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120c08:	4600d180 */ 	add.s	$f6,$f26,$f0
/*  f120c0c:	e7b60448 */ 	swc1	$f22,0x448($sp)
/*  f120c10:	e7a4049c */ 	swc1	$f4,0x49c($sp)
/*  f120c14:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f120c18:	46006280 */ 	add.s	$f10,$f12,$f0
/*  f120c1c:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f120c20:	e7a804a0 */ 	swc1	$f8,0x4a0($sp)
/*  f120c24:	c7a60590 */ 	lwc1	$f6,0x590($sp)
/*  f120c28:	4600a200 */ 	add.s	$f8,$f20,$f0
/*  f120c2c:	e7aa047c */ 	swc1	$f10,0x47c($sp)
/*  f120c30:	e7a404a4 */ 	swc1	$f4,0x4a4($sp)
/*  f120c34:	46008100 */ 	add.s	$f4,$f16,$f0
/*  f120c38:	e7a80464 */ 	swc1	$f8,0x464($sp)
/*  f120c3c:	c7a80598 */ 	lwc1	$f8,0x598($sp)
/*  f120c40:	e7b20460 */ 	swc1	$f18,0x460($sp)
/*  f120c44:	e7a40494 */ 	swc1	$f4,0x494($sp)
/*  f120c48:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f120c4c:	e7a20478 */ 	swc1	$f2,0x478($sp)
/*  f120c50:	e7ae0490 */ 	swc1	$f14,0x490($sp)
/*  f120c54:	e7a604a8 */ 	swc1	$f6,0x4a8($sp)
/*  f120c58:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120c5c:	e7aa04ac */ 	swc1	$f10,0x4ac($sp)
/*  f120c60:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120c64:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120c68:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f120c6c:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120c70:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120c74:	8fa5056c */ 	lw	$a1,0x56c($sp)
/*  f120c78:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f120c7c:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120c80:	8fa5055c */ 	lw	$a1,0x55c($sp)
/*  f120c84:	27a4049c */ 	addiu	$a0,$sp,0x49c
/*  f120c88:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120c8c:	8fa50550 */ 	lw	$a1,0x550($sp)
/*  f120c90:	10000057 */ 	b	.L0f120df0
/*  f120c94:	00000000 */ 	nop
/*  f120c98:	3c017f1b */ 	lui	$at,%hi(var7f1b5078)
/*  f120c9c:	c4385078 */ 	lwc1	$f24,%lo(var7f1b5078)($at)
/*  f120ca0:	c7ae05d8 */ 	lwc1	$f14,0x5d8($sp)
/*  f120ca4:	c7a605dc */ 	lwc1	$f6,0x5dc($sp)
/*  f120ca8:	c7b005e0 */ 	lwc1	$f16,0x5e0($sp)
/*  f120cac:	46187102 */ 	mul.s	$f4,$f14,$f24
/*  f120cb0:	c7b605c0 */ 	lwc1	$f22,0x5c0($sp)
/*  f120cb4:	c7ba05c8 */ 	lwc1	$f26,0x5c8($sp)
/*  f120cb8:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120cbc:	c7a605c4 */ 	lwc1	$f6,0x5c4($sp)
/*  f120cc0:	c7b205cc */ 	lwc1	$f18,0x5cc($sp)
/*  f120cc4:	46188282 */ 	mul.s	$f10,$f16,$f24
/*  f120cc8:	e7a4043c */ 	swc1	$f4,0x43c($sp)
/*  f120ccc:	c7b405d4 */ 	lwc1	$f20,0x5d4($sp)
/*  f120cd0:	4618b102 */ 	mul.s	$f4,$f22,$f24
/*  f120cd4:	e7a80440 */ 	swc1	$f8,0x440($sp)
/*  f120cd8:	c7a2059c */ 	lwc1	$f2,0x59c($sp)
/*  f120cdc:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120ce0:	e7aa0444 */ 	swc1	$f10,0x444($sp)
/*  f120ce4:	c7a605d0 */ 	lwc1	$f6,0x5d0($sp)
/*  f120ce8:	4618d282 */ 	mul.s	$f10,$f26,$f24
/*  f120cec:	e7a40454 */ 	swc1	$f4,0x454($sp)
/*  f120cf0:	c7ac05a4 */ 	lwc1	$f12,0x5a4($sp)
/*  f120cf4:	46189102 */ 	mul.s	$f4,$f18,$f24
/*  f120cf8:	e7a80458 */ 	swc1	$f8,0x458($sp)
/*  f120cfc:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f120d00:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120d04:	e7aa045c */ 	swc1	$f10,0x45c($sp)
/*  f120d08:	c7a605a0 */ 	lwc1	$f6,0x5a0($sp)
/*  f120d0c:	4618a282 */ 	mul.s	$f10,$f20,$f24
/*  f120d10:	e7a4046c */ 	swc1	$f4,0x46c($sp)
/*  f120d14:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f120d18:	46181102 */ 	mul.s	$f4,$f2,$f24
/*  f120d1c:	e7a80470 */ 	swc1	$f8,0x470($sp)
/*  f120d20:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f120d24:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f120d28:	e7aa0474 */ 	swc1	$f10,0x474($sp)
/*  f120d2c:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120d30:	46186282 */ 	mul.s	$f10,$f12,$f24
/*  f120d34:	e7a40484 */ 	swc1	$f4,0x484($sp)
/*  f120d38:	c7a405b4 */ 	lwc1	$f4,0x5b4($sp)
/*  f120d3c:	8fa50568 */ 	lw	$a1,0x568($sp)
/*  f120d40:	e7a80488 */ 	swc1	$f8,0x488($sp)
/*  f120d44:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120d48:	c7a805b8 */ 	lwc1	$f8,0x5b8($sp)
/*  f120d4c:	e7aa048c */ 	swc1	$f10,0x48c($sp)
/*  f120d50:	c7a405bc */ 	lwc1	$f4,0x5bc($sp)
/*  f120d54:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f120d58:	46008200 */ 	add.s	$f8,$f16,$f0
/*  f120d5c:	e7ae0448 */ 	swc1	$f14,0x448($sp)
/*  f120d60:	e7a6049c */ 	swc1	$f6,0x49c($sp)
/*  f120d64:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f120d68:	4600a100 */ 	add.s	$f4,$f20,$f0
/*  f120d6c:	e7a8044c */ 	swc1	$f8,0x44c($sp)
/*  f120d70:	e7aa04a0 */ 	swc1	$f10,0x4a0($sp)
/*  f120d74:	c7a805b4 */ 	lwc1	$f8,0x5b4($sp)
/*  f120d78:	4600d280 */ 	add.s	$f10,$f26,$f0
/*  f120d7c:	e7a4047c */ 	swc1	$f4,0x47c($sp)
/*  f120d80:	e7a604a4 */ 	swc1	$f6,0x4a4($sp)
/*  f120d84:	46006180 */ 	add.s	$f6,$f12,$f0
/*  f120d88:	e7aa0464 */ 	swc1	$f10,0x464($sp)
/*  f120d8c:	c7aa05bc */ 	lwc1	$f10,0x5bc($sp)
/*  f120d90:	e7b60460 */ 	swc1	$f22,0x460($sp)
/*  f120d94:	e7a60494 */ 	swc1	$f6,0x494($sp)
/*  f120d98:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f120d9c:	e7b20478 */ 	swc1	$f18,0x478($sp)
/*  f120da0:	e7a20490 */ 	swc1	$f2,0x490($sp)
/*  f120da4:	e7a804a8 */ 	swc1	$f8,0x4a8($sp)
/*  f120da8:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120dac:	e7a404ac */ 	swc1	$f4,0x4ac($sp)
/*  f120db0:	27a40454 */ 	addiu	$a0,$sp,0x454
/*  f120db4:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120db8:	8fa50560 */ 	lw	$a1,0x560($sp)
/*  f120dbc:	27a4046c */ 	addiu	$a0,$sp,0x46c
/*  f120dc0:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120dc4:	8fa50564 */ 	lw	$a1,0x564($sp)
/*  f120dc8:	27a40484 */ 	addiu	$a0,$sp,0x484
/*  f120dcc:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120dd0:	8fa50554 */ 	lw	$a1,0x554($sp)
/*  f120dd4:	27a4049c */ 	addiu	$a0,$sp,0x49c
/*  f120dd8:	0fc47dbb */ 	jal	func0f11f6ec
/*  f120ddc:	8fa5055c */ 	lw	$a1,0x55c($sp)
/*  f120de0:	10000003 */ 	b	.L0f120df0
/*  f120de4:	00000000 */ 	nop
.L0f120de8:
/*  f120de8:	100006af */ 	b	.L0f1228a8
/*  f120dec:	8fa206b0 */ 	lw	$v0,0x6b0($sp)
.L0f120df0:
/*  f120df0:	5a200153 */ 	blezl	$s1,.L0f121340
/*  f120df4:	8fae0068 */ 	lw	$t6,0x68($sp)
/*  f120df8:	0fc2d5c6 */ 	jal	currentPlayerGetUnk1754
/*  f120dfc:	00000000 */ 	nop
/*  f120e00:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f120e04:	00408025 */ 	or	$s0,$v0,$zero
/*  f120e08:	02002025 */ 	or	$a0,$s0,$zero
/*  f120e0c:	00402825 */ 	or	$a1,$v0,$zero
/*  f120e10:	0c005680 */ 	jal	mtx4MultMtx4
/*  f120e14:	27a603cc */ 	addiu	$a2,$sp,0x3cc
/*  f120e18:	3c013f80 */ 	lui	$at,0x3f80
/*  f120e1c:	44813000 */ 	mtc1	$at,$f6
/*  f120e20:	3c04800a */ 	lui	$a0,%hi(var800a33a8)
/*  f120e24:	248433a8 */ 	addiu	$a0,$a0,%lo(var800a33a8)
/*  f120e28:	46183003 */ 	div.s	$f0,$f6,$f24
/*  f120e2c:	44050000 */ 	mfc1	$a1,$f0
/*  f120e30:	44060000 */ 	mfc1	$a2,$f0
/*  f120e34:	44070000 */ 	mfc1	$a3,$f0
/*  f120e38:	0c014024 */ 	jal	guScaleF
/*  f120e3c:	00000000 */ 	nop
/*  f120e40:	3c05800a */ 	lui	$a1,%hi(var800a33a8)
/*  f120e44:	24a533a8 */ 	addiu	$a1,$a1,%lo(var800a33a8)
/*  f120e48:	27a403cc */ 	addiu	$a0,$sp,0x3cc
/*  f120e4c:	0c005680 */ 	jal	mtx4MultMtx4
/*  f120e50:	27a6038c */ 	addiu	$a2,$sp,0x38c
/*  f120e54:	1a20004e */ 	blez	$s1,.L0f120f90
/*  f120e58:	afa00270 */ 	sw	$zero,0x270($sp)
/*  f120e5c:	3c014080 */ 	lui	$at,0x4080
/*  f120e60:	27a4043c */ 	addiu	$a0,$sp,0x43c
/*  f120e64:	4481d000 */ 	mtc1	$at,$f26
/*  f120e68:	afa40064 */ 	sw	$a0,0x64($sp)
/*  f120e6c:	27b00274 */ 	addiu	$s0,$sp,0x274
.L0f120e70:
/*  f120e70:	3c017f1b */ 	lui	$at,%hi(var7f1b507c)
/*  f120e74:	c420507c */ 	lwc1	$f0,%lo(var7f1b507c)($at)
/*  f120e78:	8fa40064 */ 	lw	$a0,0x64($sp)
/*  f120e7c:	27a5038c */ 	addiu	$a1,$sp,0x38c
/*  f120e80:	44070000 */ 	mfc1	$a3,$f0
/*  f120e84:	24060082 */ 	addiu	$a2,$zero,0x82
/*  f120e88:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f120e8c:	0fc48a34 */ 	jal	func0f1228d0
/*  f120e90:	e7a00010 */ 	swc1	$f0,0x10($sp)
/*  f120e94:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f120e98:	00000000 */ 	nop
/*  f120e9c:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f120ea0:	46000506 */ 	mov.s	$f20,$f0
/*  f120ea4:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f120ea8:	46000586 */ 	mov.s	$f22,$f0
/*  f120eac:	46160200 */ 	add.s	$f8,$f0,$f22
/*  f120eb0:	461aa382 */ 	mul.s	$f14,$f20,$f26
/*  f120eb4:	3c013f80 */ 	lui	$at,0x3f80
/*  f120eb8:	44812000 */ 	mtc1	$at,$f4
/*  f120ebc:	461a4282 */ 	mul.s	$f10,$f8,$f26
/*  f120ec0:	c60c0028 */ 	lwc1	$f12,0x28($s0)
/*  f120ec4:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f120ec8:	44063000 */ 	mfc1	$a2,$f6
/*  f120ecc:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f120ed0:	00000000 */ 	nop
/*  f120ed4:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f120ed8:	e6000028 */ 	swc1	$f0,0x28($s0)
/*  f120edc:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f120ee0:	46000506 */ 	mov.s	$f20,$f0
/*  f120ee4:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f120ee8:	46000586 */ 	mov.s	$f22,$f0
/*  f120eec:	46160200 */ 	add.s	$f8,$f0,$f22
/*  f120ef0:	461aa382 */ 	mul.s	$f14,$f20,$f26
/*  f120ef4:	3c013f80 */ 	lui	$at,0x3f80
/*  f120ef8:	44812000 */ 	mtc1	$at,$f4
/*  f120efc:	461a4282 */ 	mul.s	$f10,$f8,$f26
/*  f120f00:	c60c002c */ 	lwc1	$f12,0x2c($s0)
/*  f120f04:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f120f08:	44063000 */ 	mfc1	$a2,$f6
/*  f120f0c:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f120f10:	00000000 */ 	nop
/*  f120f14:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f120f18:	e600002c */ 	swc1	$f0,0x2c($s0)
/*  f120f1c:	461a0202 */ 	mul.s	$f8,$f0,$f26
/*  f120f20:	c604002c */ 	lwc1	$f4,0x2c($s0)
/*  f120f24:	461a4280 */ 	add.s	$f10,$f8,$f26
/*  f120f28:	4604503c */ 	c.lt.s	$f10,$f4
/*  f120f2c:	00000000 */ 	nop
/*  f120f30:	45020010 */ 	bc1fl	.L0f120f74
/*  f120f34:	8fae0064 */ 	lw	$t6,0x64($sp)
/*  f120f38:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f120f3c:	00000000 */ 	nop
/*  f120f40:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f120f44:	46000506 */ 	mov.s	$f20,$f0
/*  f120f48:	46140180 */ 	add.s	$f6,$f0,$f20
/*  f120f4c:	c602002c */ 	lwc1	$f2,0x2c($s0)
/*  f120f50:	461a3202 */ 	mul.s	$f8,$f6,$f26
/*  f120f54:	461a4281 */ 	sub.s	$f10,$f8,$f26
/*  f120f58:	460a103c */ 	c.lt.s	$f2,$f10
/*  f120f5c:	00000000 */ 	nop
/*  f120f60:	45020004 */ 	bc1fl	.L0f120f74
/*  f120f64:	8fae0064 */ 	lw	$t6,0x64($sp)
/*  f120f68:	461a1101 */ 	sub.s	$f4,$f2,$f26
/*  f120f6c:	e604002c */ 	swc1	$f4,0x2c($s0)
/*  f120f70:	8fae0064 */ 	lw	$t6,0x64($sp)
.L0f120f74:
/*  f120f74:	8fa20270 */ 	lw	$v0,0x270($sp)
/*  f120f78:	26100038 */ 	addiu	$s0,$s0,0x38
/*  f120f7c:	25c90018 */ 	addiu	$t1,$t6,0x18
/*  f120f80:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f120f84:	afa20270 */ 	sw	$v0,0x270($sp)
/*  f120f88:	1451ffb9 */ 	bne	$v0,$s1,.L0f120e70
/*  f120f8c:	afa90064 */ 	sw	$t1,0x64($sp)
.L0f120f90:
/*  f120f90:	8fac042c */ 	lw	$t4,0x42c($sp)
/*  f120f94:	8fb806b0 */ 	lw	$t8,0x6b0($sp)
/*  f120f98:	3c0ee700 */ 	lui	$t6,0xe700
/*  f120f9c:	918b0028 */ 	lbu	$t3,0x28($t4)
/*  f120fa0:	27a406b0 */ 	addiu	$a0,$sp,0x6b0
/*  f120fa4:	3c19800b */ 	lui	$t9,%hi(var800ab598)
/*  f120fa8:	1560006b */ 	bnez	$t3,.L0f121158
/*  f120fac:	270a0008 */ 	addiu	$t2,$t8,0x8
/*  f120fb0:	3c017f1b */ 	lui	$at,%hi(var7f1b5080)
/*  f120fb4:	c42e5080 */ 	lwc1	$f14,%lo(var7f1b5080)($at)
/*  f120fb8:	3c017f1b */ 	lui	$at,%hi(var7f1b5084)
/*  f120fbc:	44801000 */ 	mtc1	$zero,$f2
/*  f120fc0:	44806000 */ 	mtc1	$zero,$f12
/*  f120fc4:	c4305084 */ 	lwc1	$f16,%lo(var7f1b5084)($at)
/*  f120fc8:	1a20001b */ 	blez	$s1,.L0f121038
/*  f120fcc:	00001825 */ 	or	$v1,$zero,$zero
/*  f120fd0:	27a20274 */ 	addiu	$v0,$sp,0x274
.L0f120fd4:
/*  f120fd4:	c4400028 */ 	lwc1	$f0,0x28($v0)
/*  f120fd8:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f120fdc:	460e003c */ 	c.lt.s	$f0,$f14
/*  f120fe0:	00000000 */ 	nop
/*  f120fe4:	45020003 */ 	bc1fl	.L0f120ff4
/*  f120fe8:	4600103c */ 	c.lt.s	$f2,$f0
/*  f120fec:	46000386 */ 	mov.s	$f14,$f0
/*  f120ff0:	4600103c */ 	c.lt.s	$f2,$f0
.L0f120ff4:
/*  f120ff4:	00000000 */ 	nop
/*  f120ff8:	45020003 */ 	bc1fl	.L0f121008
/*  f120ffc:	c440002c */ 	lwc1	$f0,0x2c($v0)
/*  f121000:	46000086 */ 	mov.s	$f2,$f0
/*  f121004:	c440002c */ 	lwc1	$f0,0x2c($v0)
.L0f121008:
/*  f121008:	4610003c */ 	c.lt.s	$f0,$f16
/*  f12100c:	00000000 */ 	nop
/*  f121010:	45020003 */ 	bc1fl	.L0f121020
/*  f121014:	4600603c */ 	c.lt.s	$f12,$f0
/*  f121018:	46000406 */ 	mov.s	$f16,$f0
/*  f12101c:	4600603c */ 	c.lt.s	$f12,$f0
.L0f121020:
/*  f121020:	00000000 */ 	nop
/*  f121024:	45000002 */ 	bc1f	.L0f121030
/*  f121028:	00000000 */ 	nop
/*  f12102c:	46000306 */ 	mov.s	$f12,$f0
.L0f121030:
/*  f121030:	1471ffe8 */ 	bne	$v1,$s1,.L0f120fd4
/*  f121034:	24420038 */ 	addiu	$v0,$v0,0x38
.L0f121038:
/*  f121038:	8faf06b0 */ 	lw	$t7,0x6b0($sp)
/*  f12103c:	3c19e700 */ 	lui	$t9,0xe700
/*  f121040:	3c013e80 */ 	lui	$at,0x3e80
/*  f121044:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f121048:	afb806b0 */ 	sw	$t8,0x6b0($sp)
/*  f12104c:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f121050:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f121054:	8fad06b0 */ 	lw	$t5,0x6b0($sp)
/*  f121058:	44810000 */ 	mtc1	$at,$f0
/*  f12105c:	3c0eba00 */ 	lui	$t6,0xba00
/*  f121060:	25aa0008 */ 	addiu	$t2,$t5,0x8
/*  f121064:	afaa06b0 */ 	sw	$t2,0x6b0($sp)
/*  f121068:	46001182 */ 	mul.s	$f6,$f2,$f0
/*  f12106c:	35ce1402 */ 	ori	$t6,$t6,0x1402
/*  f121070:	3c090030 */ 	lui	$t1,0x30
/*  f121074:	ada90004 */ 	sw	$t1,0x4($t5)
/*  f121078:	adae0000 */ 	sw	$t6,0x0($t5)
/*  f12107c:	8fac06b0 */ 	lw	$t4,0x6b0($sp)
/*  f121080:	46006282 */ 	mul.s	$f10,$f12,$f0
/*  f121084:	3c0fb900 */ 	lui	$t7,0xb900
/*  f121088:	258b0008 */ 	addiu	$t3,$t4,0x8
/*  f12108c:	afab06b0 */ 	sw	$t3,0x6b0($sp)
/*  f121090:	35ef031d */ 	ori	$t7,$t7,0x31d
/*  f121094:	ad8f0000 */ 	sw	$t7,0x0($t4)
/*  f121098:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f12109c:	ad800004 */ 	sw	$zero,0x4($t4)
/*  f1210a0:	46007182 */ 	mul.s	$f6,$f14,$f0
/*  f1210a4:	8fb806b0 */ 	lw	$t8,0x6b0($sp)
/*  f1210a8:	3c07ba00 */ 	lui	$a3,0xba00
/*  f1210ac:	34e71301 */ 	ori	$a3,$a3,0x1301
/*  f1210b0:	27190008 */ 	addiu	$t9,$t8,0x8
/*  f1210b4:	afb906b0 */ 	sw	$t9,0x6b0($sp)
/*  f1210b8:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f1210bc:	46008282 */ 	mul.s	$f10,$f16,$f0
/*  f1210c0:	af000004 */ 	sw	$zero,0x4($t8)
/*  f1210c4:	af070000 */ 	sw	$a3,0x0($t8)
/*  f1210c8:	8fa606b0 */ 	lw	$a2,0x6b0($sp)
/*  f1210cc:	44192000 */ 	mfc1	$t9,$f4
/*  f1210d0:	44094000 */ 	mfc1	$t1,$f8
/*  f1210d4:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f1210d8:	24ca0008 */ 	addiu	$t2,$a2,0x8
/*  f1210dc:	312c03ff */ 	andi	$t4,$t1,0x3ff
/*  f1210e0:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f1210e4:	000c5b80 */ 	sll	$t3,$t4,0xe
/*  f1210e8:	afaa06b0 */ 	sw	$t2,0x6b0($sp)
/*  f1210ec:	332d03ff */ 	andi	$t5,$t9,0x3ff
/*  f1210f0:	000d5080 */ 	sll	$t2,$t5,0x2
/*  f1210f4:	3c01f600 */ 	lui	$at,0xf600
/*  f1210f8:	440d2000 */ 	mfc1	$t5,$f4
/*  f1210fc:	440c4000 */ 	mfc1	$t4,$f8
/*  f121100:	01617825 */ 	or	$t7,$t3,$at
/*  f121104:	01ea7025 */ 	or	$t6,$t7,$t2
/*  f121108:	31af03ff */ 	andi	$t7,$t5,0x3ff
/*  f12110c:	318b03ff */ 	andi	$t3,$t4,0x3ff
/*  f121110:	000bc380 */ 	sll	$t8,$t3,0xe
/*  f121114:	000f5080 */ 	sll	$t2,$t7,0x2
/*  f121118:	acce0000 */ 	sw	$t6,0x0($a2)
/*  f12111c:	030a7025 */ 	or	$t6,$t8,$t2
/*  f121120:	acce0004 */ 	sw	$t6,0x4($a2)
/*  f121124:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121128:	3c0be700 */ 	lui	$t3,0xe700
/*  f12112c:	3c0f0008 */ 	lui	$t7,0x8
/*  f121130:	252c0008 */ 	addiu	$t4,$t1,0x8
/*  f121134:	afac06b0 */ 	sw	$t4,0x6b0($sp)
/*  f121138:	ad200004 */ 	sw	$zero,0x4($t1)
/*  f12113c:	ad2b0000 */ 	sw	$t3,0x0($t1)
/*  f121140:	8fb906b0 */ 	lw	$t9,0x6b0($sp)
/*  f121144:	272d0008 */ 	addiu	$t5,$t9,0x8
/*  f121148:	afad06b0 */ 	sw	$t5,0x6b0($sp)
/*  f12114c:	af2f0004 */ 	sw	$t7,0x4($t9)
/*  f121150:	1000007a */ 	b	.L0f12133c
/*  f121154:	af270000 */ 	sw	$a3,0x0($t9)
.L0f121158:
/*  f121158:	afaa06b0 */ 	sw	$t2,0x6b0($sp)
/*  f12115c:	af000004 */ 	sw	$zero,0x4($t8)
/*  f121160:	af0e0000 */ 	sw	$t6,0x0($t8)
/*  f121164:	8fa9042c */ 	lw	$t1,0x42c($sp)
/*  f121168:	8f39b598 */ 	lw	$t9,%lo(var800ab598)($t9)
/*  f12116c:	240d0002 */ 	addiu	$t5,$zero,0x2
/*  f121170:	852c0030 */ 	lh	$t4,0x30($t1)
/*  f121174:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f121178:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f12117c:	000c5880 */ 	sll	$t3,$t4,0x2
/*  f121180:	016c5823 */ 	subu	$t3,$t3,$t4
/*  f121184:	000b5880 */ 	sll	$t3,$t3,0x2
/*  f121188:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f12118c:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f121190:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f121194:	00003825 */ 	or	$a3,$zero,$zero
/*  f121198:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f12119c:	01792821 */ 	addu	$a1,$t3,$t9
/*  f1211a0:	8fb806b0 */ 	lw	$t8,0x6b0($sp)
/*  f1211a4:	3c0eb900 */ 	lui	$t6,0xb900
/*  f1211a8:	3c090f0a */ 	lui	$t1,0xf0a
/*  f1211ac:	270a0008 */ 	addiu	$t2,$t8,0x8
/*  f1211b0:	afaa06b0 */ 	sw	$t2,0x6b0($sp)
/*  f1211b4:	35294000 */ 	ori	$t1,$t1,0x4000
/*  f1211b8:	35ce031d */ 	ori	$t6,$t6,0x31d
/*  f1211bc:	24010004 */ 	addiu	$at,$zero,0x4
/*  f1211c0:	af0e0000 */ 	sw	$t6,0x0($t8)
/*  f1211c4:	1621002a */ 	bne	$s1,$at,.L0f121270
/*  f1211c8:	af090004 */ 	sw	$t1,0x4($t8)
/*  f1211cc:	3c014302 */ 	lui	$at,0x4302
/*  f1211d0:	44813000 */ 	mtc1	$at,$f6
/*  f1211d4:	27b00274 */ 	addiu	$s0,$sp,0x274
/*  f1211d8:	27b1031c */ 	addiu	$s1,$sp,0x31c
/*  f1211dc:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f1211e0:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f1211e4:	02203825 */ 	or	$a3,$s1,$zero
/*  f1211e8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1211ec:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f1211f0:	27a602ac */ 	addiu	$a2,$sp,0x2ac
/*  f1211f4:	0fc48b53 */ 	jal	func0f122d4c
/*  f1211f8:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*  f1211fc:	8fab0430 */ 	lw	$t3,0x430($sp)
/*  f121200:	00402025 */ 	or	$a0,$v0,$zero
/*  f121204:	02202825 */ 	or	$a1,$s1,$zero
/*  f121208:	1160000f */ 	beqz	$t3,.L0f121248
/*  f12120c:	27a602e4 */ 	addiu	$a2,$sp,0x2e4
/*  f121210:	3c013f80 */ 	lui	$at,0x3f80
/*  f121214:	44810000 */ 	mtc1	$at,$f0
/*  f121218:	c7a802a0 */ 	lwc1	$f8,0x2a0($sp)
/*  f12121c:	c7a402d8 */ 	lwc1	$f4,0x2d8($sp)
/*  f121220:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121224:	c7a80310 */ 	lwc1	$f8,0x310($sp)
/*  f121228:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f12122c:	c7a40348 */ 	lwc1	$f4,0x348($sp)
/*  f121230:	e7aa02a0 */ 	swc1	$f10,0x2a0($sp)
/*  f121234:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121238:	e7a602d8 */ 	swc1	$f6,0x2d8($sp)
/*  f12123c:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121240:	e7aa0310 */ 	swc1	$f10,0x310($sp)
/*  f121244:	e7a60348 */ 	swc1	$f6,0x348($sp)
.L0f121248:
/*  f121248:	3c014302 */ 	lui	$at,0x4302
/*  f12124c:	44814000 */ 	mtc1	$at,$f8
/*  f121250:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f121254:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f121258:	02003825 */ 	or	$a3,$s0,$zero
/*  f12125c:	afa406b0 */ 	sw	$a0,0x6b0($sp)
/*  f121260:	0fc48b53 */ 	jal	func0f122d4c
/*  f121264:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f121268:	10000034 */ 	b	.L0f12133c
/*  f12126c:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f121270:
/*  f121270:	24010005 */ 	addiu	$at,$zero,0x5
/*  f121274:	16210024 */ 	bne	$s1,$at,.L0f121308
/*  f121278:	27b00274 */ 	addiu	$s0,$sp,0x274
/*  f12127c:	3c014302 */ 	lui	$at,0x4302
/*  f121280:	44815000 */ 	mtc1	$at,$f10
/*  f121284:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f121288:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f12128c:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f121290:	02002825 */ 	or	$a1,$s0,$zero
/*  f121294:	27a602ac */ 	addiu	$a2,$sp,0x2ac
/*  f121298:	27a702e4 */ 	addiu	$a3,$sp,0x2e4
/*  f12129c:	0fc48b53 */ 	jal	func0f122d4c
/*  f1212a0:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*  f1212a4:	3c014302 */ 	lui	$at,0x4302
/*  f1212a8:	44812000 */ 	mtc1	$at,$f4
/*  f1212ac:	27b1031c */ 	addiu	$s1,$sp,0x31c
/*  f1212b0:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f1212b4:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f1212b8:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f1212bc:	02203825 */ 	or	$a3,$s1,$zero
/*  f1212c0:	00402025 */ 	or	$a0,$v0,$zero
/*  f1212c4:	02002825 */ 	or	$a1,$s0,$zero
/*  f1212c8:	27a602e4 */ 	addiu	$a2,$sp,0x2e4
/*  f1212cc:	0fc48b53 */ 	jal	func0f122d4c
/*  f1212d0:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*  f1212d4:	3c014302 */ 	lui	$at,0x4302
/*  f1212d8:	44813000 */ 	mtc1	$at,$f6
/*  f1212dc:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f1212e0:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f1212e4:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f1212e8:	00402025 */ 	or	$a0,$v0,$zero
/*  f1212ec:	02002825 */ 	or	$a1,$s0,$zero
/*  f1212f0:	02203025 */ 	or	$a2,$s1,$zero
/*  f1212f4:	27a70354 */ 	addiu	$a3,$sp,0x354
/*  f1212f8:	0fc48b53 */ 	jal	func0f122d4c
/*  f1212fc:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*  f121300:	1000000e */ 	b	.L0f12133c
/*  f121304:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f121308:
/*  f121308:	24010003 */ 	addiu	$at,$zero,0x3
/*  f12130c:	1621000b */ 	bne	$s1,$at,.L0f12133c
/*  f121310:	27a50274 */ 	addiu	$a1,$sp,0x274
/*  f121314:	3c014302 */ 	lui	$at,0x4302
/*  f121318:	44814000 */ 	mtc1	$at,$f8
/*  f12131c:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f121320:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f121324:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f121328:	27a602ac */ 	addiu	$a2,$sp,0x2ac
/*  f12132c:	27a702e4 */ 	addiu	$a3,$sp,0x2e4
/*  f121330:	0fc48b53 */ 	jal	func0f122d4c
/*  f121334:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f121338:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f12133c:
/*  f12133c:	8fae0068 */ 	lw	$t6,0x68($sp)
.L0f121340:
/*  f121340:	3c014080 */ 	lui	$at,0x4080
/*  f121344:	4481d000 */ 	mtc1	$at,$f26
/*  f121348:	2dc10010 */ 	sltiu	$at,$t6,0x10
/*  f12134c:	1020040a */ 	beqz	$at,.L0f122378
/*  f121350:	8fa306b0 */ 	lw	$v1,0x6b0($sp)
/*  f121354:	000e7080 */ 	sll	$t6,$t6,0x2
/*  f121358:	3c017f1b */ 	lui	$at,%hi(var7f1b5088)
/*  f12135c:	002e0821 */ 	addu	$at,$at,$t6
/*  f121360:	8c2e5088 */ 	lw	$t6,%lo(var7f1b5088)($at)
/*  f121364:	01c00008 */ 	jr	$t6
/*  f121368:	00000000 */ 	nop
/*  f12136c:	1000054e */ 	b	.L0f1228a8
/*  f121370:	00601025 */ 	or	$v0,$v1,$zero
/*  f121374:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f121378:	c7a40648 */ 	lwc1	$f4,0x648($sp)
/*  f12137c:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f121380:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f121384:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f121388:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f12138c:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121390:	c7a4063c */ 	lwc1	$f4,0x63c($sp)
/*  f121394:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f121398:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f12139c:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f1213a0:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f1213a4:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f1213a8:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f1213ac:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f1213b0:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1213b4:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f1213b8:	c7a40630 */ 	lwc1	$f4,0x630($sp)
/*  f1213bc:	46188202 */ 	mul.s	$f8,$f16,$f24
/*  f1213c0:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f1213c4:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1213c8:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f1213cc:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f1213d0:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1213d4:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1213d8:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f1213dc:	c7a40624 */ 	lwc1	$f4,0x624($sp)
/*  f1213e0:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f1213e4:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f1213e8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1213ec:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f1213f0:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f1213f4:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1213f8:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1213fc:	e7a804ec */ 	swc1	$f8,0x4ec($sp)
/*  f121400:	c7a80628 */ 	lwc1	$f8,0x628($sp)
/*  f121404:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121408:	e7aa04fc */ 	swc1	$f10,0x4fc($sp)
/*  f12140c:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121410:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f121414:	e7a60500 */ 	swc1	$f6,0x500($sp)
/*  f121418:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f12141c:	00000000 */ 	nop
/*  f121420:	461c6182 */ 	mul.s	$f6,$f12,$f28
/*  f121424:	e7aa0504 */ 	swc1	$f10,0x504($sp)
/*  f121428:	461c7282 */ 	mul.s	$f10,$f14,$f28
/*  f12142c:	e7a404c0 */ 	swc1	$f4,0x4c0($sp)
/*  f121430:	461c8102 */ 	mul.s	$f4,$f16,$f28
/*  f121434:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121438:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f12143c:	e7a804c4 */ 	swc1	$f8,0x4c4($sp)
/*  f121440:	461c9202 */ 	mul.s	$f8,$f18,$f28
/*  f121444:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121448:	461ca282 */ 	mul.s	$f10,$f20,$f28
/*  f12144c:	e7a604dc */ 	swc1	$f6,0x4dc($sp)
/*  f121450:	461cb182 */ 	mul.s	$f6,$f22,$f28
/*  f121454:	e7a804f0 */ 	swc1	$f8,0x4f0($sp)
/*  f121458:	c7a80628 */ 	lwc1	$f8,0x628($sp)
/*  f12145c:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121460:	461c4282 */ 	mul.s	$f10,$f8,$f28
/*  f121464:	e7a60508 */ 	swc1	$f6,0x508($sp)
/*  f121468:	44813000 */ 	mtc1	$at,$f6
/*  f12146c:	e7a404f4 */ 	swc1	$f4,0x4f4($sp)
/*  f121470:	46183203 */ 	div.s	$f8,$f6,$f24
/*  f121474:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121478:	e7a4050c */ 	swc1	$f4,0x50c($sp)
/*  f12147c:	0fc47d0e */ 	jal	func0f11f438
/*  f121480:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f121484:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121488:	0fc47d0e */ 	jal	func0f11f438
/*  f12148c:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f121490:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121494:	0fc47d0e */ 	jal	func0f11f438
/*  f121498:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f12149c:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f1214a0:	0fc47d0e */ 	jal	func0f11f438
/*  f1214a4:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f1214a8:	100003b6 */ 	b	.L0f122384
/*  f1214ac:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f1214b0:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f1214b4:	c7a40648 */ 	lwc1	$f4,0x648($sp)
/*  f1214b8:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f1214bc:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f1214c0:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f1214c4:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f1214c8:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1214cc:	c7a4063c */ 	lwc1	$f4,0x63c($sp)
/*  f1214d0:	c7b205fc */ 	lwc1	$f18,0x5fc($sp)
/*  f1214d4:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f1214d8:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f1214dc:	c7b40604 */ 	lwc1	$f20,0x604($sp)
/*  f1214e0:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f1214e4:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f1214e8:	c7b605f0 */ 	lwc1	$f22,0x5f0($sp)
/*  f1214ec:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1214f0:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f1214f4:	c7a40600 */ 	lwc1	$f4,0x600($sp)
/*  f1214f8:	46188202 */ 	mul.s	$f8,$f16,$f24
/*  f1214fc:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f121500:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121504:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f121508:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f12150c:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121510:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121514:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f121518:	c7a405f4 */ 	lwc1	$f4,0x5f4($sp)
/*  f12151c:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f121520:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f121524:	3c013f80 */ 	lui	$at,0x3f80
/*  f121528:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f12152c:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f121530:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f121534:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121538:	e7a804ec */ 	swc1	$f8,0x4ec($sp)
/*  f12153c:	c7a805f8 */ 	lwc1	$f8,0x5f8($sp)
/*  f121540:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121544:	e7aa04fc */ 	swc1	$f10,0x4fc($sp)
/*  f121548:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f12154c:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f121550:	e7a60500 */ 	swc1	$f6,0x500($sp)
/*  f121554:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f121558:	00000000 */ 	nop
/*  f12155c:	461c6182 */ 	mul.s	$f6,$f12,$f28
/*  f121560:	e7aa0504 */ 	swc1	$f10,0x504($sp)
/*  f121564:	461c7282 */ 	mul.s	$f10,$f14,$f28
/*  f121568:	e7a404c0 */ 	swc1	$f4,0x4c0($sp)
/*  f12156c:	461c8102 */ 	mul.s	$f4,$f16,$f28
/*  f121570:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121574:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f121578:	e7a804c4 */ 	swc1	$f8,0x4c4($sp)
/*  f12157c:	461c9202 */ 	mul.s	$f8,$f18,$f28
/*  f121580:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121584:	461ca282 */ 	mul.s	$f10,$f20,$f28
/*  f121588:	e7a604dc */ 	swc1	$f6,0x4dc($sp)
/*  f12158c:	461cb182 */ 	mul.s	$f6,$f22,$f28
/*  f121590:	e7a804f0 */ 	swc1	$f8,0x4f0($sp)
/*  f121594:	c7a805f8 */ 	lwc1	$f8,0x5f8($sp)
/*  f121598:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f12159c:	461c4282 */ 	mul.s	$f10,$f8,$f28
/*  f1215a0:	e7a60508 */ 	swc1	$f6,0x508($sp)
/*  f1215a4:	44813000 */ 	mtc1	$at,$f6
/*  f1215a8:	e7a404f4 */ 	swc1	$f4,0x4f4($sp)
/*  f1215ac:	46183203 */ 	div.s	$f8,$f6,$f24
/*  f1215b0:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f1215b4:	e7a4050c */ 	swc1	$f4,0x50c($sp)
/*  f1215b8:	0fc47d0e */ 	jal	func0f11f438
/*  f1215bc:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f1215c0:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f1215c4:	0fc47d0e */ 	jal	func0f11f438
/*  f1215c8:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f1215cc:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f1215d0:	0fc47d0e */ 	jal	func0f11f438
/*  f1215d4:	8fa50574 */ 	lw	$a1,0x574($sp)
/*  f1215d8:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f1215dc:	0fc47d0e */ 	jal	func0f11f438
/*  f1215e0:	8fa50570 */ 	lw	$a1,0x570($sp)
/*  f1215e4:	10000367 */ 	b	.L0f122384
/*  f1215e8:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f1215ec:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f1215f0:	c7a40624 */ 	lwc1	$f4,0x624($sp)
/*  f1215f4:	c7a20628 */ 	lwc1	$f2,0x628($sp)
/*  f1215f8:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f1215fc:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f121600:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f121604:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121608:	c7a40630 */ 	lwc1	$f4,0x630($sp)
/*  f12160c:	c7b005f0 */ 	lwc1	$f16,0x5f0($sp)
/*  f121610:	46181202 */ 	mul.s	$f8,$f2,$f24
/*  f121614:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f121618:	c7ac05fc */ 	lwc1	$f12,0x5fc($sp)
/*  f12161c:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f121620:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f121624:	c7ae0604 */ 	lwc1	$f14,0x604($sp)
/*  f121628:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f12162c:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f121630:	c7a405f4 */ 	lwc1	$f4,0x5f4($sp)
/*  f121634:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f121638:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f12163c:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121640:	46188282 */ 	mul.s	$f10,$f16,$f24
/*  f121644:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f121648:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f12164c:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121650:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f121654:	c7a805f8 */ 	lwc1	$f8,0x5f8($sp)
/*  f121658:	3c013f80 */ 	lui	$at,0x3f80
/*  f12165c:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f121660:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121664:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f121668:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f12166c:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f121670:	c7a60600 */ 	lwc1	$f6,0x600($sp)
/*  f121674:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121678:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f12167c:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f121680:	e7aa04ec */ 	swc1	$f10,0x4ec($sp)
/*  f121684:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f121688:	e7a404fc */ 	swc1	$f4,0x4fc($sp)
/*  f12168c:	461cb102 */ 	mul.s	$f4,$f22,$f28
/*  f121690:	e7a80500 */ 	swc1	$f8,0x500($sp)
/*  f121694:	461c1182 */ 	mul.s	$f6,$f2,$f28
/*  f121698:	e7aa0504 */ 	swc1	$f10,0x504($sp)
/*  f12169c:	461c9282 */ 	mul.s	$f10,$f18,$f28
/*  f1216a0:	e7a404c0 */ 	swc1	$f4,0x4c0($sp)
/*  f1216a4:	461ca102 */ 	mul.s	$f4,$f20,$f28
/*  f1216a8:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f1216ac:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f1216b0:	c7aa05f8 */ 	lwc1	$f10,0x5f8($sp)
/*  f1216b4:	e7a804c4 */ 	swc1	$f8,0x4c4($sp)
/*  f1216b8:	461c8202 */ 	mul.s	$f8,$f16,$f28
/*  f1216bc:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f1216c0:	461c5102 */ 	mul.s	$f4,$f10,$f28
/*  f1216c4:	e7a604dc */ 	swc1	$f6,0x4dc($sp)
/*  f1216c8:	e7a804f0 */ 	swc1	$f8,0x4f0($sp)
/*  f1216cc:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f1216d0:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f1216d4:	461c7282 */ 	mul.s	$f10,$f14,$f28
/*  f1216d8:	e7a604f4 */ 	swc1	$f6,0x4f4($sp)
/*  f1216dc:	44813000 */ 	mtc1	$at,$f6
/*  f1216e0:	e7a80508 */ 	swc1	$f8,0x508($sp)
/*  f1216e4:	46183203 */ 	div.s	$f8,$f6,$f24
/*  f1216e8:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f1216ec:	e7a4050c */ 	swc1	$f4,0x50c($sp)
/*  f1216f0:	0fc47d0e */ 	jal	func0f11f438
/*  f1216f4:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f1216f8:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f1216fc:	0fc47d0e */ 	jal	func0f11f438
/*  f121700:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f121704:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121708:	0fc47d0e */ 	jal	func0f11f438
/*  f12170c:	8fa50570 */ 	lw	$a1,0x570($sp)
/*  f121710:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f121714:	0fc47d0e */ 	jal	func0f11f438
/*  f121718:	8fa50574 */ 	lw	$a1,0x574($sp)
/*  f12171c:	10000319 */ 	b	.L0f122384
/*  f121720:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121724:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f121728:	c7a4063c */ 	lwc1	$f4,0x63c($sp)
/*  f12172c:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f121730:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f121734:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f121738:	c7a20628 */ 	lwc1	$f2,0x628($sp)
/*  f12173c:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121740:	c7a40624 */ 	lwc1	$f4,0x624($sp)
/*  f121744:	c7b40614 */ 	lwc1	$f20,0x614($sp)
/*  f121748:	46188202 */ 	mul.s	$f8,$f16,$f24
/*  f12174c:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f121750:	c7ac0608 */ 	lwc1	$f12,0x608($sp)
/*  f121754:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f121758:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f12175c:	c7b20610 */ 	lwc1	$f18,0x610($sp)
/*  f121760:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121764:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f121768:	c7a40618 */ 	lwc1	$f4,0x618($sp)
/*  f12176c:	46181202 */ 	mul.s	$f8,$f2,$f24
/*  f121770:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f121774:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121778:	4618a282 */ 	mul.s	$f10,$f20,$f24
/*  f12177c:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f121780:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121784:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121788:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f12178c:	c7a8061c */ 	lwc1	$f8,0x61c($sp)
/*  f121790:	3c013f80 */ 	lui	$at,0x3f80
/*  f121794:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f121798:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f12179c:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1217a0:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f1217a4:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f1217a8:	c7a6060c */ 	lwc1	$f6,0x60c($sp)
/*  f1217ac:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f1217b0:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f1217b4:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f1217b8:	e7aa04ec */ 	swc1	$f10,0x4ec($sp)
/*  f1217bc:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f1217c0:	e7a404fc */ 	swc1	$f4,0x4fc($sp)
/*  f1217c4:	461c7102 */ 	mul.s	$f4,$f14,$f28
/*  f1217c8:	e7a80500 */ 	swc1	$f8,0x500($sp)
/*  f1217cc:	461c8182 */ 	mul.s	$f6,$f16,$f28
/*  f1217d0:	e7aa0504 */ 	swc1	$f10,0x504($sp)
/*  f1217d4:	461cb282 */ 	mul.s	$f10,$f22,$f28
/*  f1217d8:	e7a404c0 */ 	swc1	$f4,0x4c0($sp)
/*  f1217dc:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f1217e0:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f1217e4:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f1217e8:	c7aa061c */ 	lwc1	$f10,0x61c($sp)
/*  f1217ec:	e7a804c4 */ 	swc1	$f8,0x4c4($sp)
/*  f1217f0:	461ca202 */ 	mul.s	$f8,$f20,$f28
/*  f1217f4:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f1217f8:	461c5102 */ 	mul.s	$f4,$f10,$f28
/*  f1217fc:	e7a604dc */ 	swc1	$f6,0x4dc($sp)
/*  f121800:	e7a804f0 */ 	swc1	$f8,0x4f0($sp)
/*  f121804:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f121808:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f12180c:	461c9282 */ 	mul.s	$f10,$f18,$f28
/*  f121810:	e7a604f4 */ 	swc1	$f6,0x4f4($sp)
/*  f121814:	44813000 */ 	mtc1	$at,$f6
/*  f121818:	e7a80508 */ 	swc1	$f8,0x508($sp)
/*  f12181c:	46183203 */ 	div.s	$f8,$f6,$f24
/*  f121820:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121824:	e7a4050c */ 	swc1	$f4,0x50c($sp)
/*  f121828:	0fc47d0e */ 	jal	func0f11f438
/*  f12182c:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f121830:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121834:	0fc47d0e */ 	jal	func0f11f438
/*  f121838:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f12183c:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121840:	0fc47d0e */ 	jal	func0f11f438
/*  f121844:	8fa5057c */ 	lw	$a1,0x57c($sp)
/*  f121848:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f12184c:	0fc47d0e */ 	jal	func0f11f438
/*  f121850:	8fa50578 */ 	lw	$a1,0x578($sp)
/*  f121854:	100002cb */ 	b	.L0f122384
/*  f121858:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f12185c:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f121860:	c7a40630 */ 	lwc1	$f4,0x630($sp)
/*  f121864:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f121868:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f12186c:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f121870:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f121874:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121878:	c7a40648 */ 	lwc1	$f4,0x648($sp)
/*  f12187c:	c7b60608 */ 	lwc1	$f22,0x608($sp)
/*  f121880:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f121884:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f121888:	c7ae0614 */ 	lwc1	$f14,0x614($sp)
/*  f12188c:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f121890:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f121894:	c7b0061c */ 	lwc1	$f16,0x61c($sp)
/*  f121898:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f12189c:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f1218a0:	c7a4060c */ 	lwc1	$f4,0x60c($sp)
/*  f1218a4:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f1218a8:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f1218ac:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1218b0:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f1218b4:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f1218b8:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1218bc:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1218c0:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f1218c4:	c7a80610 */ 	lwc1	$f8,0x610($sp)
/*  f1218c8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1218cc:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f1218d0:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f1218d4:	24110004 */ 	addiu	$s1,$zero,0x4
/*  f1218d8:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f1218dc:	46187102 */ 	mul.s	$f4,$f14,$f24
/*  f1218e0:	c7a60618 */ 	lwc1	$f6,0x618($sp)
/*  f1218e4:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f1218e8:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f1218ec:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f1218f0:	e7aa04ec */ 	swc1	$f10,0x4ec($sp)
/*  f1218f4:	46188282 */ 	mul.s	$f10,$f16,$f24
/*  f1218f8:	e7a404fc */ 	swc1	$f4,0x4fc($sp)
/*  f1218fc:	461c9102 */ 	mul.s	$f4,$f18,$f28
/*  f121900:	e7a80500 */ 	swc1	$f8,0x500($sp)
/*  f121904:	461ca182 */ 	mul.s	$f6,$f20,$f28
/*  f121908:	e7aa0504 */ 	swc1	$f10,0x504($sp)
/*  f12190c:	461c1282 */ 	mul.s	$f10,$f2,$f28
/*  f121910:	e7a404c0 */ 	swc1	$f4,0x4c0($sp)
/*  f121914:	461c6102 */ 	mul.s	$f4,$f12,$f28
/*  f121918:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f12191c:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f121920:	c7aa0610 */ 	lwc1	$f10,0x610($sp)
/*  f121924:	e7a804c4 */ 	swc1	$f8,0x4c4($sp)
/*  f121928:	461cb202 */ 	mul.s	$f8,$f22,$f28
/*  f12192c:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121930:	461c5102 */ 	mul.s	$f4,$f10,$f28
/*  f121934:	e7a604dc */ 	swc1	$f6,0x4dc($sp)
/*  f121938:	e7a804f0 */ 	swc1	$f8,0x4f0($sp)
/*  f12193c:	461c7202 */ 	mul.s	$f8,$f14,$f28
/*  f121940:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121944:	461c8282 */ 	mul.s	$f10,$f16,$f28
/*  f121948:	e7a604f4 */ 	swc1	$f6,0x4f4($sp)
/*  f12194c:	44813000 */ 	mtc1	$at,$f6
/*  f121950:	e7a80508 */ 	swc1	$f8,0x508($sp)
/*  f121954:	46183203 */ 	div.s	$f8,$f6,$f24
/*  f121958:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f12195c:	e7a4050c */ 	swc1	$f4,0x50c($sp)
/*  f121960:	0fc47d0e */ 	jal	func0f11f438
/*  f121964:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f121968:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f12196c:	0fc47d0e */ 	jal	func0f11f438
/*  f121970:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f121974:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121978:	0fc47d0e */ 	jal	func0f11f438
/*  f12197c:	8fa50578 */ 	lw	$a1,0x578($sp)
/*  f121980:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f121984:	0fc47d0e */ 	jal	func0f11f438
/*  f121988:	8fa5057c */ 	lw	$a1,0x57c($sp)
/*  f12198c:	1000027d */ 	b	.L0f122384
/*  f121990:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121994:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f121998:	c7a40624 */ 	lwc1	$f4,0x624($sp)
/*  f12199c:	c7a20628 */ 	lwc1	$f2,0x628($sp)
/*  f1219a0:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f1219a4:	c7ae0608 */ 	lwc1	$f14,0x608($sp)
/*  f1219a8:	c7b20610 */ 	lwc1	$f18,0x610($sp)
/*  f1219ac:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1219b0:	c7a4060c */ 	lwc1	$f4,0x60c($sp)
/*  f1219b4:	c7b005f0 */ 	lwc1	$f16,0x5f0($sp)
/*  f1219b8:	46181202 */ 	mul.s	$f8,$f2,$f24
/*  f1219bc:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f1219c0:	c7ac05f8 */ 	lwc1	$f12,0x5f8($sp)
/*  f1219c4:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f1219c8:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f1219cc:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1219d0:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1219d4:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f1219d8:	c7a405f4 */ 	lwc1	$f4,0x5f4($sp)
/*  f1219dc:	46189202 */ 	mul.s	$f8,$f18,$f24
/*  f1219e0:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f1219e4:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1219e8:	46188282 */ 	mul.s	$f10,$f16,$f24
/*  f1219ec:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f1219f0:	3c013f80 */ 	lui	$at,0x3f80
/*  f1219f4:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f1219f8:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f1219fc:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f121a00:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f121a04:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f121a08:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121a0c:	461cb282 */ 	mul.s	$f10,$f22,$f28
/*  f121a10:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f121a14:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f121a18:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f121a1c:	e7a804ec */ 	swc1	$f8,0x4ec($sp)
/*  f121a20:	461c7202 */ 	mul.s	$f8,$f14,$f28
/*  f121a24:	e7aa04c0 */ 	swc1	$f10,0x4c0($sp)
/*  f121a28:	461c9282 */ 	mul.s	$f10,$f18,$f28
/*  f121a2c:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121a30:	e7a804d8 */ 	swc1	$f8,0x4d8($sp)
/*  f121a34:	e7a604c4 */ 	swc1	$f6,0x4c4($sp)
/*  f121a38:	461c8182 */ 	mul.s	$f6,$f16,$f28
/*  f121a3c:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121a40:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f121a44:	e7a404dc */ 	swc1	$f4,0x4dc($sp)
/*  f121a48:	44812000 */ 	mtc1	$at,$f4
/*  f121a4c:	e7a604f0 */ 	swc1	$f6,0x4f0($sp)
/*  f121a50:	46182183 */ 	div.s	$f6,$f4,$f24
/*  f121a54:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121a58:	e7aa04f4 */ 	swc1	$f10,0x4f4($sp)
/*  f121a5c:	0fc47d0e */ 	jal	func0f11f438
/*  f121a60:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f121a64:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121a68:	0fc47d0e */ 	jal	func0f11f438
/*  f121a6c:	8fa50578 */ 	lw	$a1,0x578($sp)
/*  f121a70:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121a74:	0fc47d0e */ 	jal	func0f11f438
/*  f121a78:	8fa50570 */ 	lw	$a1,0x570($sp)
/*  f121a7c:	10000241 */ 	b	.L0f122384
/*  f121a80:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121a84:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f121a88:	c7aa0630 */ 	lwc1	$f10,0x630($sp)
/*  f121a8c:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f121a90:	46189202 */ 	mul.s	$f8,$f18,$f24
/*  f121a94:	c7ac05fc */ 	lwc1	$f12,0x5fc($sp)
/*  f121a98:	c7ae0604 */ 	lwc1	$f14,0x604($sp)
/*  f121a9c:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121aa0:	c7aa0600 */ 	lwc1	$f10,0x600($sp)
/*  f121aa4:	c7a20608 */ 	lwc1	$f2,0x608($sp)
/*  f121aa8:	4618a182 */ 	mul.s	$f6,$f20,$f24
/*  f121aac:	e7a804b4 */ 	swc1	$f8,0x4b4($sp)
/*  f121ab0:	c7b00610 */ 	lwc1	$f16,0x610($sp)
/*  f121ab4:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f121ab8:	e7a404b8 */ 	swc1	$f4,0x4b8($sp)
/*  f121abc:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121ac0:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121ac4:	e7a604bc */ 	swc1	$f6,0x4bc($sp)
/*  f121ac8:	c7aa060c */ 	lwc1	$f10,0x60c($sp)
/*  f121acc:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f121ad0:	e7a804cc */ 	swc1	$f8,0x4cc($sp)
/*  f121ad4:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121ad8:	46181202 */ 	mul.s	$f8,$f2,$f24
/*  f121adc:	e7a404d0 */ 	swc1	$f4,0x4d0($sp)
/*  f121ae0:	3c013f80 */ 	lui	$at,0x3f80
/*  f121ae4:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121ae8:	e7a604d4 */ 	swc1	$f6,0x4d4($sp)
/*  f121aec:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f121af0:	46188182 */ 	mul.s	$f6,$f16,$f24
/*  f121af4:	e7a804e4 */ 	swc1	$f8,0x4e4($sp)
/*  f121af8:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121afc:	461c9202 */ 	mul.s	$f8,$f18,$f28
/*  f121b00:	e7a404e8 */ 	swc1	$f4,0x4e8($sp)
/*  f121b04:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f121b08:	461ca282 */ 	mul.s	$f10,$f20,$f28
/*  f121b0c:	e7a604ec */ 	swc1	$f6,0x4ec($sp)
/*  f121b10:	461c6182 */ 	mul.s	$f6,$f12,$f28
/*  f121b14:	e7a804c0 */ 	swc1	$f8,0x4c0($sp)
/*  f121b18:	461c7202 */ 	mul.s	$f8,$f14,$f28
/*  f121b1c:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121b20:	e7a604d8 */ 	swc1	$f6,0x4d8($sp)
/*  f121b24:	e7a404c4 */ 	swc1	$f4,0x4c4($sp)
/*  f121b28:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f121b2c:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121b30:	461c8182 */ 	mul.s	$f6,$f16,$f28
/*  f121b34:	e7aa04dc */ 	swc1	$f10,0x4dc($sp)
/*  f121b38:	44815000 */ 	mtc1	$at,$f10
/*  f121b3c:	e7a404f0 */ 	swc1	$f4,0x4f0($sp)
/*  f121b40:	46185103 */ 	div.s	$f4,$f10,$f24
/*  f121b44:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121b48:	e7a804f4 */ 	swc1	$f8,0x4f4($sp)
/*  f121b4c:	0fc47d0e */ 	jal	func0f11f438
/*  f121b50:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f121b54:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121b58:	0fc47d0e */ 	jal	func0f11f438
/*  f121b5c:	8fa50574 */ 	lw	$a1,0x574($sp)
/*  f121b60:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121b64:	0fc47d0e */ 	jal	func0f11f438
/*  f121b68:	8fa50578 */ 	lw	$a1,0x578($sp)
/*  f121b6c:	10000205 */ 	b	.L0f122384
/*  f121b70:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121b74:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f121b78:	c7a8063c */ 	lwc1	$f8,0x63c($sp)
/*  f121b7c:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f121b80:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f121b84:	c7a205f0 */ 	lwc1	$f2,0x5f0($sp)
/*  f121b88:	c7ac05f8 */ 	lwc1	$f12,0x5f8($sp)
/*  f121b8c:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121b90:	c7a805f4 */ 	lwc1	$f8,0x5f4($sp)
/*  f121b94:	c7b40614 */ 	lwc1	$f20,0x614($sp)
/*  f121b98:	46188102 */ 	mul.s	$f4,$f16,$f24
/*  f121b9c:	e7a604b4 */ 	swc1	$f6,0x4b4($sp)
/*  f121ba0:	c7b2061c */ 	lwc1	$f18,0x61c($sp)
/*  f121ba4:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f121ba8:	e7aa04b8 */ 	swc1	$f10,0x4b8($sp)
/*  f121bac:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121bb0:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121bb4:	e7a404bc */ 	swc1	$f4,0x4bc($sp)
/*  f121bb8:	c7a80618 */ 	lwc1	$f8,0x618($sp)
/*  f121bbc:	46186102 */ 	mul.s	$f4,$f12,$f24
/*  f121bc0:	e7a604cc */ 	swc1	$f6,0x4cc($sp)
/*  f121bc4:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121bc8:	4618a182 */ 	mul.s	$f6,$f20,$f24
/*  f121bcc:	e7aa04d0 */ 	swc1	$f10,0x4d0($sp)
/*  f121bd0:	3c013f80 */ 	lui	$at,0x3f80
/*  f121bd4:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121bd8:	e7a404d4 */ 	swc1	$f4,0x4d4($sp)
/*  f121bdc:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f121be0:	46189102 */ 	mul.s	$f4,$f18,$f24
/*  f121be4:	e7a604e4 */ 	swc1	$f6,0x4e4($sp)
/*  f121be8:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121bec:	461c7182 */ 	mul.s	$f6,$f14,$f28
/*  f121bf0:	e7aa04e8 */ 	swc1	$f10,0x4e8($sp)
/*  f121bf4:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f121bf8:	461c8202 */ 	mul.s	$f8,$f16,$f28
/*  f121bfc:	e7a404ec */ 	swc1	$f4,0x4ec($sp)
/*  f121c00:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f121c04:	e7a604c0 */ 	swc1	$f6,0x4c0($sp)
/*  f121c08:	461c6182 */ 	mul.s	$f6,$f12,$f28
/*  f121c0c:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121c10:	e7a404d8 */ 	swc1	$f4,0x4d8($sp)
/*  f121c14:	e7aa04c4 */ 	swc1	$f10,0x4c4($sp)
/*  f121c18:	461ca282 */ 	mul.s	$f10,$f20,$f28
/*  f121c1c:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121c20:	461c9102 */ 	mul.s	$f4,$f18,$f28
/*  f121c24:	e7a804dc */ 	swc1	$f8,0x4dc($sp)
/*  f121c28:	44814000 */ 	mtc1	$at,$f8
/*  f121c2c:	e7aa04f0 */ 	swc1	$f10,0x4f0($sp)
/*  f121c30:	46184283 */ 	div.s	$f10,$f8,$f24
/*  f121c34:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121c38:	e7a604f4 */ 	swc1	$f6,0x4f4($sp)
/*  f121c3c:	0fc47d0e */ 	jal	func0f11f438
/*  f121c40:	e7aa0064 */ 	swc1	$f10,0x64($sp)
/*  f121c44:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121c48:	0fc47d0e */ 	jal	func0f11f438
/*  f121c4c:	8fa50570 */ 	lw	$a1,0x570($sp)
/*  f121c50:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121c54:	0fc47d0e */ 	jal	func0f11f438
/*  f121c58:	8fa5057c */ 	lw	$a1,0x57c($sp)
/*  f121c5c:	100001c9 */ 	b	.L0f122384
/*  f121c60:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121c64:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f121c68:	c7a60648 */ 	lwc1	$f6,0x648($sp)
/*  f121c6c:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f121c70:	46181102 */ 	mul.s	$f4,$f2,$f24
/*  f121c74:	c7b20614 */ 	lwc1	$f18,0x614($sp)
/*  f121c78:	c7b4061c */ 	lwc1	$f20,0x61c($sp)
/*  f121c7c:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f121c80:	c7a60618 */ 	lwc1	$f6,0x618($sp)
/*  f121c84:	c7ae05fc */ 	lwc1	$f14,0x5fc($sp)
/*  f121c88:	46186282 */ 	mul.s	$f10,$f12,$f24
/*  f121c8c:	e7a404b4 */ 	swc1	$f4,0x4b4($sp)
/*  f121c90:	c7b00604 */ 	lwc1	$f16,0x604($sp)
/*  f121c94:	46189102 */ 	mul.s	$f4,$f18,$f24
/*  f121c98:	e7a804b8 */ 	swc1	$f8,0x4b8($sp)
/*  f121c9c:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121ca0:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f121ca4:	e7aa04bc */ 	swc1	$f10,0x4bc($sp)
/*  f121ca8:	c7a60600 */ 	lwc1	$f6,0x600($sp)
/*  f121cac:	4618a282 */ 	mul.s	$f10,$f20,$f24
/*  f121cb0:	e7a404cc */ 	swc1	$f4,0x4cc($sp)
/*  f121cb4:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121cb8:	46187102 */ 	mul.s	$f4,$f14,$f24
/*  f121cbc:	e7a804d0 */ 	swc1	$f8,0x4d0($sp)
/*  f121cc0:	3c013f80 */ 	lui	$at,0x3f80
/*  f121cc4:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f121cc8:	e7aa04d4 */ 	swc1	$f10,0x4d4($sp)
/*  f121ccc:	24110003 */ 	addiu	$s1,$zero,0x3
/*  f121cd0:	46188282 */ 	mul.s	$f10,$f16,$f24
/*  f121cd4:	e7a404e4 */ 	swc1	$f4,0x4e4($sp)
/*  f121cd8:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121cdc:	461c1102 */ 	mul.s	$f4,$f2,$f28
/*  f121ce0:	e7a804e8 */ 	swc1	$f8,0x4e8($sp)
/*  f121ce4:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f121ce8:	461c6182 */ 	mul.s	$f6,$f12,$f28
/*  f121cec:	e7aa04ec */ 	swc1	$f10,0x4ec($sp)
/*  f121cf0:	461c9282 */ 	mul.s	$f10,$f18,$f28
/*  f121cf4:	e7a404c0 */ 	swc1	$f4,0x4c0($sp)
/*  f121cf8:	461ca102 */ 	mul.s	$f4,$f20,$f28
/*  f121cfc:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121d00:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f121d04:	e7a804c4 */ 	swc1	$f8,0x4c4($sp)
/*  f121d08:	461c7202 */ 	mul.s	$f8,$f14,$f28
/*  f121d0c:	46002180 */ 	add.s	$f6,$f4,$f0
/*  f121d10:	461c8282 */ 	mul.s	$f10,$f16,$f28
/*  f121d14:	e7a604dc */ 	swc1	$f6,0x4dc($sp)
/*  f121d18:	44813000 */ 	mtc1	$at,$f6
/*  f121d1c:	e7a804f0 */ 	swc1	$f8,0x4f0($sp)
/*  f121d20:	46183203 */ 	div.s	$f8,$f6,$f24
/*  f121d24:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121d28:	e7a404f4 */ 	swc1	$f4,0x4f4($sp)
/*  f121d2c:	0fc47d0e */ 	jal	func0f11f438
/*  f121d30:	e7a80064 */ 	swc1	$f8,0x64($sp)
/*  f121d34:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121d38:	0fc47d0e */ 	jal	func0f11f438
/*  f121d3c:	8fa5057c */ 	lw	$a1,0x57c($sp)
/*  f121d40:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121d44:	0fc47d0e */ 	jal	func0f11f438
/*  f121d48:	8fa50574 */ 	lw	$a1,0x574($sp)
/*  f121d4c:	1000018d */ 	b	.L0f122384
/*  f121d50:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121d54:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f121d58:	c7a40630 */ 	lwc1	$f4,0x630($sp)
/*  f121d5c:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f121d60:	46189282 */ 	mul.s	$f10,$f18,$f24
/*  f121d64:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f121d68:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f121d6c:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121d70:	c7a40648 */ 	lwc1	$f4,0x648($sp)
/*  f121d74:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f121d78:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f121d7c:	e7aa04b4 */ 	swc1	$f10,0x4b4($sp)
/*  f121d80:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f121d84:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f121d88:	e7a604b8 */ 	swc1	$f6,0x4b8($sp)
/*  f121d8c:	c7b605f0 */ 	lwc1	$f22,0x5f0($sp)
/*  f121d90:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121d94:	e7a804bc */ 	swc1	$f8,0x4bc($sp)
/*  f121d98:	c7a4063c */ 	lwc1	$f4,0x63c($sp)
/*  f121d9c:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f121da0:	e7aa04cc */ 	swc1	$f10,0x4cc($sp)
/*  f121da4:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121da8:	46187282 */ 	mul.s	$f10,$f14,$f24
/*  f121dac:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f121db0:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121db4:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121db8:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f121dbc:	c7a405f4 */ 	lwc1	$f4,0x5f4($sp)
/*  f121dc0:	46188202 */ 	mul.s	$f8,$f16,$f24
/*  f121dc4:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f121dc8:	3c013f80 */ 	lui	$at,0x3f80
/*  f121dcc:	4618b282 */ 	mul.s	$f10,$f22,$f24
/*  f121dd0:	e7a604e8 */ 	swc1	$f6,0x4e8($sp)
/*  f121dd4:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f121dd8:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121ddc:	e7a804ec */ 	swc1	$f8,0x4ec($sp)
/*  f121de0:	c7a805f8 */ 	lwc1	$f8,0x5f8($sp)
/*  f121de4:	c7a40608 */ 	lwc1	$f4,0x608($sp)
/*  f121de8:	e7aa04fc */ 	swc1	$f10,0x4fc($sp)
/*  f121dec:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121df0:	c7a8060c */ 	lwc1	$f8,0x60c($sp)
/*  f121df4:	e7a60500 */ 	swc1	$f6,0x500($sp)
/*  f121df8:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121dfc:	c7a40610 */ 	lwc1	$f4,0x610($sp)
/*  f121e00:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121e04:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f121e08:	e7aa0504 */ 	swc1	$f10,0x504($sp)
/*  f121e0c:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121e10:	e7a60514 */ 	swc1	$f6,0x514($sp)
/*  f121e14:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f121e18:	00000000 */ 	nop
/*  f121e1c:	461c9202 */ 	mul.s	$f8,$f18,$f28
/*  f121e20:	e7aa0518 */ 	swc1	$f10,0x518($sp)
/*  f121e24:	461ca282 */ 	mul.s	$f10,$f20,$f28
/*  f121e28:	e7a6051c */ 	swc1	$f6,0x51c($sp)
/*  f121e2c:	461c1182 */ 	mul.s	$f6,$f2,$f28
/*  f121e30:	e7a804c0 */ 	swc1	$f8,0x4c0($sp)
/*  f121e34:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f121e38:	46005100 */ 	add.s	$f4,$f10,$f0
/*  f121e3c:	e7a604d8 */ 	swc1	$f6,0x4d8($sp)
/*  f121e40:	e7a404c4 */ 	swc1	$f4,0x4c4($sp)
/*  f121e44:	461c7102 */ 	mul.s	$f4,$f14,$f28
/*  f121e48:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121e4c:	461c8182 */ 	mul.s	$f6,$f16,$f28
/*  f121e50:	e7aa04dc */ 	swc1	$f10,0x4dc($sp)
/*  f121e54:	461cb282 */ 	mul.s	$f10,$f22,$f28
/*  f121e58:	e7a404f0 */ 	swc1	$f4,0x4f0($sp)
/*  f121e5c:	c7a405f8 */ 	lwc1	$f4,0x5f8($sp)
/*  f121e60:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121e64:	461c2182 */ 	mul.s	$f6,$f4,$f28
/*  f121e68:	e7aa0508 */ 	swc1	$f10,0x508($sp)
/*  f121e6c:	c7aa0608 */ 	lwc1	$f10,0x608($sp)
/*  f121e70:	e7a804f4 */ 	swc1	$f8,0x4f4($sp)
/*  f121e74:	461c5102 */ 	mul.s	$f4,$f10,$f28
/*  f121e78:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121e7c:	c7a60610 */ 	lwc1	$f6,0x610($sp)
/*  f121e80:	e7a8050c */ 	swc1	$f8,0x50c($sp)
/*  f121e84:	e7a40520 */ 	swc1	$f4,0x520($sp)
/*  f121e88:	44812000 */ 	mtc1	$at,$f4
/*  f121e8c:	461c3202 */ 	mul.s	$f8,$f6,$f28
/*  f121e90:	46182183 */ 	div.s	$f6,$f4,$f24
/*  f121e94:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121e98:	e7aa0524 */ 	swc1	$f10,0x524($sp)
/*  f121e9c:	0fc47d0e */ 	jal	func0f11f438
/*  f121ea0:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f121ea4:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f121ea8:	0fc47d0e */ 	jal	func0f11f438
/*  f121eac:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f121eb0:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f121eb4:	0fc47d0e */ 	jal	func0f11f438
/*  f121eb8:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f121ebc:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f121ec0:	0fc47d0e */ 	jal	func0f11f438
/*  f121ec4:	8fa50570 */ 	lw	$a1,0x570($sp)
/*  f121ec8:	27a40514 */ 	addiu	$a0,$sp,0x514
/*  f121ecc:	0fc47d0e */ 	jal	func0f11f438
/*  f121ed0:	8fa50578 */ 	lw	$a1,0x578($sp)
/*  f121ed4:	1000012b */ 	b	.L0f122384
/*  f121ed8:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f121edc:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f121ee0:	c7aa0648 */ 	lwc1	$f10,0x648($sp)
/*  f121ee4:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f121ee8:	46181202 */ 	mul.s	$f8,$f2,$f24
/*  f121eec:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f121ef0:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f121ef4:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121ef8:	c7aa063c */ 	lwc1	$f10,0x63c($sp)
/*  f121efc:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f121f00:	46186182 */ 	mul.s	$f6,$f12,$f24
/*  f121f04:	e7a804b4 */ 	swc1	$f8,0x4b4($sp)
/*  f121f08:	c7b205fc */ 	lwc1	$f18,0x5fc($sp)
/*  f121f0c:	46187202 */ 	mul.s	$f8,$f14,$f24
/*  f121f10:	e7a404b8 */ 	swc1	$f4,0x4b8($sp)
/*  f121f14:	c7b40604 */ 	lwc1	$f20,0x604($sp)
/*  f121f18:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121f1c:	e7a604bc */ 	swc1	$f6,0x4bc($sp)
/*  f121f20:	c7aa0624 */ 	lwc1	$f10,0x624($sp)
/*  f121f24:	46188182 */ 	mul.s	$f6,$f16,$f24
/*  f121f28:	e7a804cc */ 	swc1	$f8,0x4cc($sp)
/*  f121f2c:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f121f30:	4618b202 */ 	mul.s	$f8,$f22,$f24
/*  f121f34:	e7a404d0 */ 	swc1	$f4,0x4d0($sp)
/*  f121f38:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f121f3c:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121f40:	e7a604d4 */ 	swc1	$f6,0x4d4($sp)
/*  f121f44:	c7a60628 */ 	lwc1	$f6,0x628($sp)
/*  f121f48:	c7aa0608 */ 	lwc1	$f10,0x608($sp)
/*  f121f4c:	e7a804e4 */ 	swc1	$f8,0x4e4($sp)
/*  f121f50:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f121f54:	c7a6060c */ 	lwc1	$f6,0x60c($sp)
/*  f121f58:	e7a404e8 */ 	swc1	$f4,0x4e8($sp)
/*  f121f5c:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121f60:	c7aa0610 */ 	lwc1	$f10,0x610($sp)
/*  f121f64:	3c013f80 */ 	lui	$at,0x3f80
/*  f121f68:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f121f6c:	e7a804ec */ 	swc1	$f8,0x4ec($sp)
/*  f121f70:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f121f74:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f121f78:	e7a404fc */ 	swc1	$f4,0x4fc($sp)
/*  f121f7c:	46185102 */ 	mul.s	$f4,$f10,$f24
/*  f121f80:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f121f84:	46189182 */ 	mul.s	$f6,$f18,$f24
/*  f121f88:	e7a80500 */ 	swc1	$f8,0x500($sp)
/*  f121f8c:	c7a80600 */ 	lwc1	$f8,0x600($sp)
/*  f121f90:	e7a40504 */ 	swc1	$f4,0x504($sp)
/*  f121f94:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f121f98:	e7a60514 */ 	swc1	$f6,0x514($sp)
/*  f121f9c:	4618a102 */ 	mul.s	$f4,$f20,$f24
/*  f121fa0:	00000000 */ 	nop
/*  f121fa4:	461c1182 */ 	mul.s	$f6,$f2,$f28
/*  f121fa8:	e7aa0518 */ 	swc1	$f10,0x518($sp)
/*  f121fac:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f121fb0:	e7a4051c */ 	swc1	$f4,0x51c($sp)
/*  f121fb4:	461c7102 */ 	mul.s	$f4,$f14,$f28
/*  f121fb8:	e7a604c0 */ 	swc1	$f6,0x4c0($sp)
/*  f121fbc:	461c8182 */ 	mul.s	$f6,$f16,$f28
/*  f121fc0:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f121fc4:	e7a404d8 */ 	swc1	$f4,0x4d8($sp)
/*  f121fc8:	c7a40628 */ 	lwc1	$f4,0x628($sp)
/*  f121fcc:	e7aa04c4 */ 	swc1	$f10,0x4c4($sp)
/*  f121fd0:	461cb282 */ 	mul.s	$f10,$f22,$f28
/*  f121fd4:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121fd8:	461c2182 */ 	mul.s	$f6,$f4,$f28
/*  f121fdc:	e7a804dc */ 	swc1	$f8,0x4dc($sp)
/*  f121fe0:	e7aa04f0 */ 	swc1	$f10,0x4f0($sp)
/*  f121fe4:	c7aa0608 */ 	lwc1	$f10,0x608($sp)
/*  f121fe8:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f121fec:	461c5102 */ 	mul.s	$f4,$f10,$f28
/*  f121ff0:	c7a60610 */ 	lwc1	$f6,0x610($sp)
/*  f121ff4:	e7a804f4 */ 	swc1	$f8,0x4f4($sp)
/*  f121ff8:	461c3202 */ 	mul.s	$f8,$f6,$f28
/*  f121ffc:	e7a40508 */ 	swc1	$f4,0x508($sp)
/*  f122000:	461c9102 */ 	mul.s	$f4,$f18,$f28
/*  f122004:	46004280 */ 	add.s	$f10,$f8,$f0
/*  f122008:	461ca182 */ 	mul.s	$f6,$f20,$f28
/*  f12200c:	e7a40520 */ 	swc1	$f4,0x520($sp)
/*  f122010:	e7aa050c */ 	swc1	$f10,0x50c($sp)
/*  f122014:	44815000 */ 	mtc1	$at,$f10
/*  f122018:	00000000 */ 	nop
/*  f12201c:	46185103 */ 	div.s	$f4,$f10,$f24
/*  f122020:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f122024:	e7a80524 */ 	swc1	$f8,0x524($sp)
/*  f122028:	0fc47d0e */ 	jal	func0f11f438
/*  f12202c:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f122030:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f122034:	0fc47d0e */ 	jal	func0f11f438
/*  f122038:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f12203c:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f122040:	0fc47d0e */ 	jal	func0f11f438
/*  f122044:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f122048:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f12204c:	0fc47d0e */ 	jal	func0f11f438
/*  f122050:	8fa50578 */ 	lw	$a1,0x578($sp)
/*  f122054:	27a40514 */ 	addiu	$a0,$sp,0x514
/*  f122058:	0fc47d0e */ 	jal	func0f11f438
/*  f12205c:	8fa50574 */ 	lw	$a1,0x574($sp)
/*  f122060:	100000c8 */ 	b	.L0f122384
/*  f122064:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f122068:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f12206c:	c7a80624 */ 	lwc1	$f8,0x624($sp)
/*  f122070:	c7a40628 */ 	lwc1	$f4,0x628($sp)
/*  f122074:	4618b182 */ 	mul.s	$f6,$f22,$f24
/*  f122078:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f12207c:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f122080:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f122084:	c7a20644 */ 	lwc1	$f2,0x644($sp)
/*  f122088:	c7ac064c */ 	lwc1	$f12,0x64c($sp)
/*  f12208c:	c7ae0614 */ 	lwc1	$f14,0x614($sp)
/*  f122090:	e7a604b4 */ 	swc1	$f6,0x4b4($sp)
/*  f122094:	46182182 */ 	mul.s	$f6,$f4,$f24
/*  f122098:	c7b0061c */ 	lwc1	$f16,0x61c($sp)
/*  f12209c:	e7aa04b8 */ 	swc1	$f10,0x4b8($sp)
/*  f1220a0:	46189202 */ 	mul.s	$f8,$f18,$f24
/*  f1220a4:	c7aa0630 */ 	lwc1	$f10,0x630($sp)
/*  f1220a8:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f1220ac:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f1220b0:	e7a604bc */ 	swc1	$f6,0x4bc($sp)
/*  f1220b4:	46185182 */ 	mul.s	$f6,$f10,$f24
/*  f1220b8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1220bc:	e7a804cc */ 	swc1	$f8,0x4cc($sp)
/*  f1220c0:	4618a202 */ 	mul.s	$f8,$f20,$f24
/*  f1220c4:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f1220c8:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f1220cc:	46181282 */ 	mul.s	$f10,$f2,$f24
/*  f1220d0:	e7a604d0 */ 	swc1	$f6,0x4d0($sp)
/*  f1220d4:	c7a60648 */ 	lwc1	$f6,0x648($sp)
/*  f1220d8:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f1220dc:	e7a804d4 */ 	swc1	$f8,0x4d4($sp)
/*  f1220e0:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f1220e4:	e7aa04e4 */ 	swc1	$f10,0x4e4($sp)
/*  f1220e8:	46186282 */ 	mul.s	$f10,$f12,$f24
/*  f1220ec:	e7a804e8 */ 	swc1	$f8,0x4e8($sp)
/*  f1220f0:	46187182 */ 	mul.s	$f6,$f14,$f24
/*  f1220f4:	c7a80618 */ 	lwc1	$f8,0x618($sp)
/*  f1220f8:	e7aa04ec */ 	swc1	$f10,0x4ec($sp)
/*  f1220fc:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f122100:	c7a805f0 */ 	lwc1	$f8,0x5f0($sp)
/*  f122104:	e7a604fc */ 	swc1	$f6,0x4fc($sp)
/*  f122108:	46188182 */ 	mul.s	$f6,$f16,$f24
/*  f12210c:	e7aa0500 */ 	swc1	$f10,0x500($sp)
/*  f122110:	46184282 */ 	mul.s	$f10,$f8,$f24
/*  f122114:	e7a60504 */ 	swc1	$f6,0x504($sp)
/*  f122118:	c7a605f4 */ 	lwc1	$f6,0x5f4($sp)
/*  f12211c:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f122120:	e7aa0514 */ 	swc1	$f10,0x514($sp)
/*  f122124:	c7aa05f8 */ 	lwc1	$f10,0x5f8($sp)
/*  f122128:	46185182 */ 	mul.s	$f6,$f10,$f24
/*  f12212c:	e7a80518 */ 	swc1	$f8,0x518($sp)
/*  f122130:	461cb202 */ 	mul.s	$f8,$f22,$f28
/*  f122134:	00000000 */ 	nop
/*  f122138:	461c2282 */ 	mul.s	$f10,$f4,$f28
/*  f12213c:	e7a6051c */ 	swc1	$f6,0x51c($sp)
/*  f122140:	e7a804c0 */ 	swc1	$f8,0x4c0($sp)
/*  f122144:	461c9202 */ 	mul.s	$f8,$f18,$f28
/*  f122148:	46005180 */ 	add.s	$f6,$f10,$f0
/*  f12214c:	461ca102 */ 	mul.s	$f4,$f20,$f28
/*  f122150:	e7a604c4 */ 	swc1	$f6,0x4c4($sp)
/*  f122154:	461c1182 */ 	mul.s	$f6,$f2,$f28
/*  f122158:	e7a804d8 */ 	swc1	$f8,0x4d8($sp)
/*  f12215c:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f122160:	46002280 */ 	add.s	$f10,$f4,$f0
/*  f122164:	e7a604f0 */ 	swc1	$f6,0x4f0($sp)
/*  f122168:	e7aa04dc */ 	swc1	$f10,0x4dc($sp)
/*  f12216c:	461c7282 */ 	mul.s	$f10,$f14,$f28
/*  f122170:	46004100 */ 	add.s	$f4,$f8,$f0
/*  f122174:	461c8182 */ 	mul.s	$f6,$f16,$f28
/*  f122178:	e7a404f4 */ 	swc1	$f4,0x4f4($sp)
/*  f12217c:	c7a405f0 */ 	lwc1	$f4,0x5f0($sp)
/*  f122180:	e7aa0508 */ 	swc1	$f10,0x508($sp)
/*  f122184:	461c2282 */ 	mul.s	$f10,$f4,$f28
/*  f122188:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f12218c:	c7a605f8 */ 	lwc1	$f6,0x5f8($sp)
/*  f122190:	e7a8050c */ 	swc1	$f8,0x50c($sp)
/*  f122194:	461c3202 */ 	mul.s	$f8,$f6,$f28
/*  f122198:	e7aa0520 */ 	swc1	$f10,0x520($sp)
/*  f12219c:	44815000 */ 	mtc1	$at,$f10
/*  f1221a0:	00000000 */ 	nop
/*  f1221a4:	46185183 */ 	div.s	$f6,$f10,$f24
/*  f1221a8:	46004100 */ 	add.s	$f4,$f8,$f0
/*  f1221ac:	e7a40524 */ 	swc1	$f4,0x524($sp)
/*  f1221b0:	0fc47d0e */ 	jal	func0f11f438
/*  f1221b4:	e7a60064 */ 	swc1	$f6,0x64($sp)
/*  f1221b8:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f1221bc:	0fc47d0e */ 	jal	func0f11f438
/*  f1221c0:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f1221c4:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f1221c8:	0fc47d0e */ 	jal	func0f11f438
/*  f1221cc:	8fa5058c */ 	lw	$a1,0x58c($sp)
/*  f1221d0:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f1221d4:	0fc47d0e */ 	jal	func0f11f438
/*  f1221d8:	8fa5057c */ 	lw	$a1,0x57c($sp)
/*  f1221dc:	27a40514 */ 	addiu	$a0,$sp,0x514
/*  f1221e0:	0fc47d0e */ 	jal	func0f11f438
/*  f1221e4:	8fa50570 */ 	lw	$a1,0x570($sp)
/*  f1221e8:	10000066 */ 	b	.L0f122384
/*  f1221ec:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
/*  f1221f0:	c7ae0638 */ 	lwc1	$f14,0x638($sp)
/*  f1221f4:	c7a4063c */ 	lwc1	$f4,0x63c($sp)
/*  f1221f8:	c7b00640 */ 	lwc1	$f16,0x640($sp)
/*  f1221fc:	46187202 */ 	mul.s	$f8,$f14,$f24
/*  f122200:	c7b60620 */ 	lwc1	$f22,0x620($sp)
/*  f122204:	c7a20628 */ 	lwc1	$f2,0x628($sp)
/*  f122208:	46182282 */ 	mul.s	$f10,$f4,$f24
/*  f12220c:	c7a40624 */ 	lwc1	$f4,0x624($sp)
/*  f122210:	c7b2062c */ 	lwc1	$f18,0x62c($sp)
/*  f122214:	46188182 */ 	mul.s	$f6,$f16,$f24
/*  f122218:	e7a804b4 */ 	swc1	$f8,0x4b4($sp)
/*  f12221c:	c7b40634 */ 	lwc1	$f20,0x634($sp)
/*  f122220:	4618b202 */ 	mul.s	$f8,$f22,$f24
/*  f122224:	e7aa04b8 */ 	swc1	$f10,0x4b8($sp)
/*  f122228:	c7ac05fc */ 	lwc1	$f12,0x5fc($sp)
/*  f12222c:	46182282 */ 	mul.s	$f10,$f4,$f24
/*  f122230:	e7a604bc */ 	swc1	$f6,0x4bc($sp)
/*  f122234:	c7a40630 */ 	lwc1	$f4,0x630($sp)
/*  f122238:	46181182 */ 	mul.s	$f6,$f2,$f24
/*  f12223c:	e7a804cc */ 	swc1	$f8,0x4cc($sp)
/*  f122240:	3c018008 */ 	lui	$at,%hi(var8007db80)
/*  f122244:	46189202 */ 	mul.s	$f8,$f18,$f24
/*  f122248:	e7aa04d0 */ 	swc1	$f10,0x4d0($sp)
/*  f12224c:	c420db80 */ 	lwc1	$f0,%lo(var8007db80)($at)
/*  f122250:	46182282 */ 	mul.s	$f10,$f4,$f24
/*  f122254:	e7a604d4 */ 	swc1	$f6,0x4d4($sp)
/*  f122258:	c7a40600 */ 	lwc1	$f4,0x600($sp)
/*  f12225c:	4618a182 */ 	mul.s	$f6,$f20,$f24
/*  f122260:	e7a804e4 */ 	swc1	$f8,0x4e4($sp)
/*  f122264:	3c013f80 */ 	lui	$at,0x3f80
/*  f122268:	46186202 */ 	mul.s	$f8,$f12,$f24
/*  f12226c:	e7aa04e8 */ 	swc1	$f10,0x4e8($sp)
/*  f122270:	24110005 */ 	addiu	$s1,$zero,0x5
/*  f122274:	46182282 */ 	mul.s	$f10,$f4,$f24
/*  f122278:	e7a604ec */ 	swc1	$f6,0x4ec($sp)
/*  f12227c:	c7a60604 */ 	lwc1	$f6,0x604($sp)
/*  f122280:	c7a40614 */ 	lwc1	$f4,0x614($sp)
/*  f122284:	e7a804fc */ 	swc1	$f8,0x4fc($sp)
/*  f122288:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f12228c:	c7a60618 */ 	lwc1	$f6,0x618($sp)
/*  f122290:	e7aa0500 */ 	swc1	$f10,0x500($sp)
/*  f122294:	46182282 */ 	mul.s	$f10,$f4,$f24
/*  f122298:	c7a4061c */ 	lwc1	$f4,0x61c($sp)
/*  f12229c:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f1222a0:	8fa50588 */ 	lw	$a1,0x588($sp)
/*  f1222a4:	e7a80504 */ 	swc1	$f8,0x504($sp)
/*  f1222a8:	46183202 */ 	mul.s	$f8,$f6,$f24
/*  f1222ac:	e7aa0514 */ 	swc1	$f10,0x514($sp)
/*  f1222b0:	46182282 */ 	mul.s	$f10,$f4,$f24
/*  f1222b4:	00000000 */ 	nop
/*  f1222b8:	461c7182 */ 	mul.s	$f6,$f14,$f28
/*  f1222bc:	e7a80518 */ 	swc1	$f8,0x518($sp)
/*  f1222c0:	461c8202 */ 	mul.s	$f8,$f16,$f28
/*  f1222c4:	e7aa051c */ 	swc1	$f10,0x51c($sp)
/*  f1222c8:	461cb282 */ 	mul.s	$f10,$f22,$f28
/*  f1222cc:	e7a604c0 */ 	swc1	$f6,0x4c0($sp)
/*  f1222d0:	461c1182 */ 	mul.s	$f6,$f2,$f28
/*  f1222d4:	46004100 */ 	add.s	$f4,$f8,$f0
/*  f1222d8:	e7aa04d8 */ 	swc1	$f10,0x4d8($sp)
/*  f1222dc:	e7a404c4 */ 	swc1	$f4,0x4c4($sp)
/*  f1222e0:	461c9102 */ 	mul.s	$f4,$f18,$f28
/*  f1222e4:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f1222e8:	461ca282 */ 	mul.s	$f10,$f20,$f28
/*  f1222ec:	e7a804dc */ 	swc1	$f8,0x4dc($sp)
/*  f1222f0:	461c6202 */ 	mul.s	$f8,$f12,$f28
/*  f1222f4:	e7a404f0 */ 	swc1	$f4,0x4f0($sp)
/*  f1222f8:	c7a40604 */ 	lwc1	$f4,0x604($sp)
/*  f1222fc:	46005180 */ 	add.s	$f6,$f10,$f0
/*  f122300:	461c2282 */ 	mul.s	$f10,$f4,$f28
/*  f122304:	e7a80508 */ 	swc1	$f8,0x508($sp)
/*  f122308:	c7a80614 */ 	lwc1	$f8,0x614($sp)
/*  f12230c:	e7a604f4 */ 	swc1	$f6,0x4f4($sp)
/*  f122310:	461c4102 */ 	mul.s	$f4,$f8,$f28
/*  f122314:	46005180 */ 	add.s	$f6,$f10,$f0
/*  f122318:	c7aa061c */ 	lwc1	$f10,0x61c($sp)
/*  f12231c:	e7a6050c */ 	swc1	$f6,0x50c($sp)
/*  f122320:	e7a40520 */ 	swc1	$f4,0x520($sp)
/*  f122324:	44812000 */ 	mtc1	$at,$f4
/*  f122328:	461c5182 */ 	mul.s	$f6,$f10,$f28
/*  f12232c:	46182283 */ 	div.s	$f10,$f4,$f24
/*  f122330:	46003200 */ 	add.s	$f8,$f6,$f0
/*  f122334:	e7a80524 */ 	swc1	$f8,0x524($sp)
/*  f122338:	0fc47d0e */ 	jal	func0f11f438
/*  f12233c:	e7aa0064 */ 	swc1	$f10,0x64($sp)
/*  f122340:	27a404cc */ 	addiu	$a0,$sp,0x4cc
/*  f122344:	0fc47d0e */ 	jal	func0f11f438
/*  f122348:	8fa50580 */ 	lw	$a1,0x580($sp)
/*  f12234c:	27a404e4 */ 	addiu	$a0,$sp,0x4e4
/*  f122350:	0fc47d0e */ 	jal	func0f11f438
/*  f122354:	8fa50584 */ 	lw	$a1,0x584($sp)
/*  f122358:	27a404fc */ 	addiu	$a0,$sp,0x4fc
/*  f12235c:	0fc47d0e */ 	jal	func0f11f438
/*  f122360:	8fa50574 */ 	lw	$a1,0x574($sp)
/*  f122364:	27a40514 */ 	addiu	$a0,$sp,0x514
/*  f122368:	0fc47d0e */ 	jal	func0f11f438
/*  f12236c:	8fa5057c */ 	lw	$a1,0x57c($sp)
/*  f122370:	10000004 */ 	b	.L0f122384
/*  f122374:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
.L0f122378:
/*  f122378:	1000014b */ 	b	.L0f1228a8
/*  f12237c:	00601025 */ 	or	$v0,$v1,$zero
/*  f122380:	8fa906b0 */ 	lw	$t1,0x6b0($sp)
.L0f122384:
/*  f122384:	3c0be700 */ 	lui	$t3,0xe700
/*  f122388:	3c18800b */ 	lui	$t8,%hi(var800ab598)
/*  f12238c:	252c0008 */ 	addiu	$t4,$t1,0x8
/*  f122390:	afac06b0 */ 	sw	$t4,0x6b0($sp)
/*  f122394:	ad200004 */ 	sw	$zero,0x4($t1)
/*  f122398:	ad2b0000 */ 	sw	$t3,0x0($t1)
/*  f12239c:	8fb9042c */ 	lw	$t9,0x42c($sp)
/*  f1223a0:	8f18b598 */ 	lw	$t8,%lo(var800ab598)($t8)
/*  f1223a4:	240a0002 */ 	addiu	$t2,$zero,0x2
/*  f1223a8:	872d0018 */ 	lh	$t5,0x18($t9)
/*  f1223ac:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f1223b0:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f1223b4:	000d7880 */ 	sll	$t7,$t5,0x2
/*  f1223b8:	01ed7823 */ 	subu	$t7,$t7,$t5
/*  f1223bc:	000f7880 */ 	sll	$t7,$t7,0x2
/*  f1223c0:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f1223c4:	afaa0010 */ 	sw	$t2,0x10($sp)
/*  f1223c8:	27a406b0 */ 	addiu	$a0,$sp,0x6b0
/*  f1223cc:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f1223d0:	00003825 */ 	or	$a3,$zero,$zero
/*  f1223d4:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f1223d8:	01f82821 */ 	addu	$a1,$t7,$t8
/*  f1223dc:	8fa206b0 */ 	lw	$v0,0x6b0($sp)
/*  f1223e0:	3c0bfb00 */ 	lui	$t3,0xfb00
/*  f1223e4:	244c0008 */ 	addiu	$t4,$v0,0x8
/*  f1223e8:	afac06b0 */ 	sw	$t4,0x6b0($sp)
/*  f1223ec:	ac4b0000 */ 	sw	$t3,0x0($v0)
/*  f1223f0:	8fb9042c */ 	lw	$t9,0x42c($sp)
/*  f1223f4:	3c0b55fe */ 	lui	$t3,0x55fe
/*  f1223f8:	356bf97c */ 	ori	$t3,$t3,0xf97c
/*  f1223fc:	932f0008 */ 	lbu	$t7,0x8($t9)
/*  f122400:	932e0009 */ 	lbu	$t6,0x9($t9)
/*  f122404:	932d000a */ 	lbu	$t5,0xa($t9)
/*  f122408:	000fc600 */ 	sll	$t8,$t7,0x18
/*  f12240c:	000e4c00 */ 	sll	$t1,$t6,0x10
/*  f122410:	03096025 */ 	or	$t4,$t8,$t1
/*  f122414:	000d7a00 */ 	sll	$t7,$t5,0x8
/*  f122418:	018f5025 */ 	or	$t2,$t4,$t7
/*  f12241c:	354e00ff */ 	ori	$t6,$t2,0xff
/*  f122420:	ac4e0004 */ 	sw	$t6,0x4($v0)
/*  f122424:	8fb806b0 */ 	lw	$t8,0x6b0($sp)
/*  f122428:	3c19fc40 */ 	lui	$t9,0xfc40
/*  f12242c:	3739fe81 */ 	ori	$t9,$t9,0xfe81
/*  f122430:	27090008 */ 	addiu	$t1,$t8,0x8
/*  f122434:	afa906b0 */ 	sw	$t1,0x6b0($sp)
/*  f122438:	af0b0004 */ 	sw	$t3,0x4($t8)
/*  f12243c:	0fc2d5c6 */ 	jal	currentPlayerGetUnk1754
/*  f122440:	af190000 */ 	sw	$t9,0x0($t8)
/*  f122444:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f122448:	00408025 */ 	or	$s0,$v0,$zero
/*  f12244c:	02002025 */ 	or	$a0,$s0,$zero
/*  f122450:	00402825 */ 	or	$a1,$v0,$zero
/*  f122454:	0c005680 */ 	jal	mtx4MultMtx4
/*  f122458:	27a601ec */ 	addiu	$a2,$sp,0x1ec
/*  f12245c:	c7a60064 */ 	lwc1	$f6,0x64($sp)
/*  f122460:	3c04800a */ 	lui	$a0,%hi(var800a33a8)
/*  f122464:	248433a8 */ 	addiu	$a0,$a0,%lo(var800a33a8)
/*  f122468:	44053000 */ 	mfc1	$a1,$f6
/*  f12246c:	44063000 */ 	mfc1	$a2,$f6
/*  f122470:	44073000 */ 	mfc1	$a3,$f6
/*  f122474:	0c014024 */ 	jal	guScaleF
/*  f122478:	00000000 */ 	nop
/*  f12247c:	3c05800a */ 	lui	$a1,%hi(var800a33a8)
/*  f122480:	24a533a8 */ 	addiu	$a1,$a1,%lo(var800a33a8)
/*  f122484:	27a401ec */ 	addiu	$a0,$sp,0x1ec
/*  f122488:	0c005680 */ 	jal	mtx4MultMtx4
/*  f12248c:	27a601ac */ 	addiu	$a2,$sp,0x1ac
/*  f122490:	1a200036 */ 	blez	$s1,.L0f12256c
/*  f122494:	afa00090 */ 	sw	$zero,0x90($sp)
/*  f122498:	27a404b4 */ 	addiu	$a0,$sp,0x4b4
/*  f12249c:	afa40064 */ 	sw	$a0,0x64($sp)
/*  f1224a0:	27b00094 */ 	addiu	$s0,$sp,0x94
.L0f1224a4:
/*  f1224a4:	3c017f1b */ 	lui	$at,%hi(var7f1b50c8)
/*  f1224a8:	c42050c8 */ 	lwc1	$f0,%lo(var7f1b50c8)($at)
/*  f1224ac:	8fa40064 */ 	lw	$a0,0x64($sp)
/*  f1224b0:	27a501ac */ 	addiu	$a1,$sp,0x1ac
/*  f1224b4:	44070000 */ 	mfc1	$a3,$f0
/*  f1224b8:	24060082 */ 	addiu	$a2,$zero,0x82
/*  f1224bc:	afb00014 */ 	sw	$s0,0x14($sp)
/*  f1224c0:	0fc48a34 */ 	jal	func0f1228d0
/*  f1224c4:	e7a00010 */ 	swc1	$f0,0x10($sp)
/*  f1224c8:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1224cc:	00000000 */ 	nop
/*  f1224d0:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1224d4:	46000506 */ 	mov.s	$f20,$f0
/*  f1224d8:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1224dc:	46000586 */ 	mov.s	$f22,$f0
/*  f1224e0:	46160200 */ 	add.s	$f8,$f0,$f22
/*  f1224e4:	461aa382 */ 	mul.s	$f14,$f20,$f26
/*  f1224e8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1224ec:	44815000 */ 	mtc1	$at,$f10
/*  f1224f0:	461a4102 */ 	mul.s	$f4,$f8,$f26
/*  f1224f4:	c60c0028 */ 	lwc1	$f12,0x28($s0)
/*  f1224f8:	460a2181 */ 	sub.s	$f6,$f4,$f10
/*  f1224fc:	44063000 */ 	mfc1	$a2,$f6
/*  f122500:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f122504:	00000000 */ 	nop
/*  f122508:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f12250c:	e6000028 */ 	swc1	$f0,0x28($s0)
/*  f122510:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f122514:	46000506 */ 	mov.s	$f20,$f0
/*  f122518:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f12251c:	46000586 */ 	mov.s	$f22,$f0
/*  f122520:	46160200 */ 	add.s	$f8,$f0,$f22
/*  f122524:	461aa382 */ 	mul.s	$f14,$f20,$f26
/*  f122528:	3c013f80 */ 	lui	$at,0x3f80
/*  f12252c:	44815000 */ 	mtc1	$at,$f10
/*  f122530:	461a4102 */ 	mul.s	$f4,$f8,$f26
/*  f122534:	c60c002c */ 	lwc1	$f12,0x2c($s0)
/*  f122538:	460a2181 */ 	sub.s	$f6,$f4,$f10
/*  f12253c:	44063000 */ 	mfc1	$a2,$f6
/*  f122540:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f122544:	00000000 */ 	nop
/*  f122548:	8fa20090 */ 	lw	$v0,0x90($sp)
/*  f12254c:	e600002c */ 	swc1	$f0,0x2c($s0)
/*  f122550:	8fad0064 */ 	lw	$t5,0x64($sp)
/*  f122554:	24420001 */ 	addiu	$v0,$v0,0x1
/*  f122558:	afa20090 */ 	sw	$v0,0x90($sp)
/*  f12255c:	25ac0018 */ 	addiu	$t4,$t5,0x18
/*  f122560:	afac0064 */ 	sw	$t4,0x64($sp)
/*  f122564:	1451ffcf */ 	bne	$v0,$s1,.L0f1224a4
/*  f122568:	26100038 */ 	addiu	$s0,$s0,0x38
.L0f12256c:
/*  f12256c:	24010004 */ 	addiu	$at,$zero,0x4
/*  f122570:	16210099 */ 	bne	$s1,$at,.L0f1227d8
/*  f122574:	8faf0068 */ 	lw	$t7,0x68($sp)
/*  f122578:	2401000c */ 	addiu	$at,$zero,0xc
/*  f12257c:	15e1007e */ 	bne	$t7,$at,.L0f122778
/*  f122580:	27b00094 */ 	addiu	$s0,$sp,0x94
/*  f122584:	c7a80548 */ 	lwc1	$f8,0x548($sp)
/*  f122588:	c7a4054c */ 	lwc1	$f4,0x54c($sp)
/*  f12258c:	c7a600f8 */ 	lwc1	$f6,0xf8($sp)
/*  f122590:	4604403c */ 	c.lt.s	$f8,$f4
/*  f122594:	c7a800c0 */ 	lwc1	$f8,0xc0($sp)
/*  f122598:	4502003d */ 	bc1fl	.L0f122690
/*  f12259c:	461a4100 */ 	add.s	$f4,$f8,$f26
/*  f1225a0:	461a3200 */ 	add.s	$f8,$f6,$f26
/*  f1225a4:	c7aa0168 */ 	lwc1	$f10,0x168($sp)
/*  f1225a8:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f1225ac:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f1225b0:	460a403e */ 	c.le.s	$f8,$f10
/*  f1225b4:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f1225b8:	27a70104 */ 	addiu	$a3,$sp,0x104
/*  f1225bc:	3c014302 */ 	lui	$at,0x4302
/*  f1225c0:	4500002c */ 	bc1f	.L0f122674
/*  f1225c4:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f1225c8:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1225cc:	00000000 */ 	nop
/*  f1225d0:	461a0102 */ 	mul.s	$f4,$f0,$f26
/*  f1225d4:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f1225d8:	e7a400bc */ 	swc1	$f4,0xbc($sp)
/*  f1225dc:	461a0182 */ 	mul.s	$f6,$f0,$f26
/*  f1225e0:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1225e4:	e7a600c0 */ 	swc1	$f6,0xc0($sp)
/*  f1225e8:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1225ec:	46000506 */ 	mov.s	$f20,$f0
/*  f1225f0:	46140280 */ 	add.s	$f10,$f0,$f20
/*  f1225f4:	3c013f80 */ 	lui	$at,0x3f80
/*  f1225f8:	44812000 */ 	mtc1	$at,$f4
/*  f1225fc:	461a5202 */ 	mul.s	$f8,$f10,$f26
/*  f122600:	46044181 */ 	sub.s	$f6,$f8,$f4
/*  f122604:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f122608:	e7a600f4 */ 	swc1	$f6,0xf4($sp)
/*  f12260c:	461a0282 */ 	mul.s	$f10,$f0,$f26
/*  f122610:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f122614:	e7aa00f8 */ 	swc1	$f10,0xf8($sp)
/*  f122618:	461a0202 */ 	mul.s	$f8,$f0,$f26
/*  f12261c:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f122620:	e7a8012c */ 	swc1	$f8,0x12c($sp)
/*  f122624:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f122628:	46000506 */ 	mov.s	$f20,$f0
/*  f12262c:	46140100 */ 	add.s	$f4,$f0,$f20
/*  f122630:	3c013f80 */ 	lui	$at,0x3f80
/*  f122634:	44815000 */ 	mtc1	$at,$f10
/*  f122638:	3c014302 */ 	lui	$at,0x4302
/*  f12263c:	461a2182 */ 	mul.s	$f6,$f4,$f26
/*  f122640:	44812000 */ 	mtc1	$at,$f4
/*  f122644:	27b1013c */ 	addiu	$s1,$sp,0x13c
/*  f122648:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f12264c:	afb10010 */ 	sw	$s1,0x10($sp)
/*  f122650:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f122654:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f122658:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f12265c:	27a70104 */ 	addiu	$a3,$sp,0x104
/*  f122660:	e7a40014 */ 	swc1	$f4,0x14($sp)
/*  f122664:	0fc48ff5 */ 	jal	func0f123fd4
/*  f122668:	e7a80164 */ 	swc1	$f8,0x164($sp)
/*  f12266c:	1000008d */ 	b	.L0f1228a4
/*  f122670:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f122674:
/*  f122674:	44813000 */ 	mtc1	$at,$f6
/*  f122678:	afaa0014 */ 	sw	$t2,0x14($sp)
/*  f12267c:	0fc48b53 */ 	jal	func0f122d4c
/*  f122680:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*  f122684:	10000087 */ 	b	.L0f1228a4
/*  f122688:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f12268c:	461a4100 */ 	add.s	$f4,$f8,$f26
.L0f122690:
/*  f122690:	c7aa0130 */ 	lwc1	$f10,0x130($sp)
/*  f122694:	27a60094 */ 	addiu	$a2,$sp,0x94
/*  f122698:	27a7013c */ 	addiu	$a3,$sp,0x13c
/*  f12269c:	460a203e */ 	c.le.s	$f4,$f10
/*  f1226a0:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f1226a4:	27a500cc */ 	addiu	$a1,$sp,0xcc
/*  f1226a8:	3c014302 */ 	lui	$at,0x4302
/*  f1226ac:	4500002c */ 	bc1f	.L0f122760
/*  f1226b0:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f1226b4:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1226b8:	00000000 */ 	nop
/*  f1226bc:	461a0182 */ 	mul.s	$f6,$f0,$f26
/*  f1226c0:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f1226c4:	e7a600bc */ 	swc1	$f6,0xbc($sp)
/*  f1226c8:	461a0202 */ 	mul.s	$f8,$f0,$f26
/*  f1226cc:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1226d0:	e7a800c0 */ 	swc1	$f8,0xc0($sp)
/*  f1226d4:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1226d8:	46000506 */ 	mov.s	$f20,$f0
/*  f1226dc:	46140280 */ 	add.s	$f10,$f0,$f20
/*  f1226e0:	3c013f80 */ 	lui	$at,0x3f80
/*  f1226e4:	44813000 */ 	mtc1	$at,$f6
/*  f1226e8:	461a5102 */ 	mul.s	$f4,$f10,$f26
/*  f1226ec:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f1226f0:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f1226f4:	e7a800f4 */ 	swc1	$f8,0xf4($sp)
/*  f1226f8:	461a0282 */ 	mul.s	$f10,$f0,$f26
/*  f1226fc:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f122700:	e7aa00f8 */ 	swc1	$f10,0xf8($sp)
/*  f122704:	461a0102 */ 	mul.s	$f4,$f0,$f26
/*  f122708:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f12270c:	e7a4012c */ 	swc1	$f4,0x12c($sp)
/*  f122710:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f122714:	46000506 */ 	mov.s	$f20,$f0
/*  f122718:	46140180 */ 	add.s	$f6,$f0,$f20
/*  f12271c:	3c013f80 */ 	lui	$at,0x3f80
/*  f122720:	44815000 */ 	mtc1	$at,$f10
/*  f122724:	3c014302 */ 	lui	$at,0x4302
/*  f122728:	461a3202 */ 	mul.s	$f8,$f6,$f26
/*  f12272c:	44813000 */ 	mtc1	$at,$f6
/*  f122730:	27ae0104 */ 	addiu	$t6,$sp,0x104
/*  f122734:	27a60094 */ 	addiu	$a2,$sp,0x94
/*  f122738:	27a7013c */ 	addiu	$a3,$sp,0x13c
/*  f12273c:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f122740:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f122744:	460a4101 */ 	sub.s	$f4,$f8,$f10
/*  f122748:	27a500cc */ 	addiu	$a1,$sp,0xcc
/*  f12274c:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*  f122750:	0fc48ff5 */ 	jal	func0f123fd4
/*  f122754:	e7a40164 */ 	swc1	$f4,0x164($sp)
/*  f122758:	10000052 */ 	b	.L0f1228a4
/*  f12275c:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f122760:
/*  f122760:	44814000 */ 	mtc1	$at,$f8
/*  f122764:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f122768:	0fc48b53 */ 	jal	func0f122d4c
/*  f12276c:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f122770:	1000004c */ 	b	.L0f1228a4
/*  f122774:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f122778:
/*  f122778:	3c014302 */ 	lui	$at,0x4302
/*  f12277c:	44815000 */ 	mtc1	$at,$f10
/*  f122780:	27b1013c */ 	addiu	$s1,$sp,0x13c
/*  f122784:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f122788:	afa90014 */ 	sw	$t1,0x14($sp)
/*  f12278c:	02203825 */ 	or	$a3,$s1,$zero
/*  f122790:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f122794:	02002825 */ 	or	$a1,$s0,$zero
/*  f122798:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f12279c:	0fc48b53 */ 	jal	func0f122d4c
/*  f1227a0:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*  f1227a4:	3c014302 */ 	lui	$at,0x4302
/*  f1227a8:	44812000 */ 	mtc1	$at,$f4
/*  f1227ac:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f1227b0:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f1227b4:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f1227b8:	00402025 */ 	or	$a0,$v0,$zero
/*  f1227bc:	02202825 */ 	or	$a1,$s1,$zero
/*  f1227c0:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f1227c4:	02003825 */ 	or	$a3,$s0,$zero
/*  f1227c8:	0fc48b53 */ 	jal	func0f122d4c
/*  f1227cc:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*  f1227d0:	10000034 */ 	b	.L0f1228a4
/*  f1227d4:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f1227d8:
/*  f1227d8:	24010005 */ 	addiu	$at,$zero,0x5
/*  f1227dc:	16210024 */ 	bne	$s1,$at,.L0f122870
/*  f1227e0:	27b00094 */ 	addiu	$s0,$sp,0x94
/*  f1227e4:	3c014302 */ 	lui	$at,0x4302
/*  f1227e8:	44813000 */ 	mtc1	$at,$f6
/*  f1227ec:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f1227f0:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f1227f4:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f1227f8:	02002825 */ 	or	$a1,$s0,$zero
/*  f1227fc:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f122800:	27a70104 */ 	addiu	$a3,$sp,0x104
/*  f122804:	0fc48b53 */ 	jal	func0f122d4c
/*  f122808:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*  f12280c:	3c014302 */ 	lui	$at,0x4302
/*  f122810:	44814000 */ 	mtc1	$at,$f8
/*  f122814:	27b1013c */ 	addiu	$s1,$sp,0x13c
/*  f122818:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f12281c:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f122820:	afad0014 */ 	sw	$t5,0x14($sp)
/*  f122824:	02203825 */ 	or	$a3,$s1,$zero
/*  f122828:	00402025 */ 	or	$a0,$v0,$zero
/*  f12282c:	02002825 */ 	or	$a1,$s0,$zero
/*  f122830:	27a60104 */ 	addiu	$a2,$sp,0x104
/*  f122834:	0fc48b53 */ 	jal	func0f122d4c
/*  f122838:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*  f12283c:	3c014302 */ 	lui	$at,0x4302
/*  f122840:	44815000 */ 	mtc1	$at,$f10
/*  f122844:	240c0001 */ 	addiu	$t4,$zero,0x1
/*  f122848:	afa206b0 */ 	sw	$v0,0x6b0($sp)
/*  f12284c:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f122850:	00402025 */ 	or	$a0,$v0,$zero
/*  f122854:	02002825 */ 	or	$a1,$s0,$zero
/*  f122858:	02203025 */ 	or	$a2,$s1,$zero
/*  f12285c:	27a70174 */ 	addiu	$a3,$sp,0x174
/*  f122860:	0fc48b53 */ 	jal	func0f122d4c
/*  f122864:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*  f122868:	1000000e */ 	b	.L0f1228a4
/*  f12286c:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f122870:
/*  f122870:	24010003 */ 	addiu	$at,$zero,0x3
/*  f122874:	1621000b */ 	bne	$s1,$at,.L0f1228a4
/*  f122878:	27a50094 */ 	addiu	$a1,$sp,0x94
/*  f12287c:	3c014302 */ 	lui	$at,0x4302
/*  f122880:	44812000 */ 	mtc1	$at,$f4
/*  f122884:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f122888:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f12288c:	8fa406b0 */ 	lw	$a0,0x6b0($sp)
/*  f122890:	27a600cc */ 	addiu	$a2,$sp,0xcc
/*  f122894:	27a70104 */ 	addiu	$a3,$sp,0x104
/*  f122898:	0fc48b53 */ 	jal	func0f122d4c
/*  f12289c:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*  f1228a0:	afa206b0 */ 	sw	$v0,0x6b0($sp)
.L0f1228a4:
/*  f1228a4:	8fa206b0 */ 	lw	$v0,0x6b0($sp)
.L0f1228a8:
/*  f1228a8:	8fbf0054 */ 	lw	$ra,0x54($sp)
/*  f1228ac:	d7b40020 */ 	ldc1	$f20,0x20($sp)
/*  f1228b0:	d7b60028 */ 	ldc1	$f22,0x28($sp)
/*  f1228b4:	d7b80030 */ 	ldc1	$f24,0x30($sp)
/*  f1228b8:	d7ba0038 */ 	ldc1	$f26,0x38($sp)
/*  f1228bc:	d7bc0040 */ 	ldc1	$f28,0x40($sp)
/*  f1228c0:	8fb0004c */ 	lw	$s0,0x4c($sp)
/*  f1228c4:	8fb10050 */ 	lw	$s1,0x50($sp)
/*  f1228c8:	03e00008 */ 	jr	$ra
/*  f1228cc:	27bd06b0 */ 	addiu	$sp,$sp,0x6b0
);

GLOBAL_ASM(
glabel func0f1228d0
.late_rodata
glabel var7f1b50cc
.word 0x46fffe00
glabel var7f1b50d0
.word 0x46fffe00
glabel var7f1b50d4
.word 0x43ff8000
glabel var7f1b50d8
.word 0xc57fa000
glabel var7f1b50dc
.word 0xc57fa000
.text
/*  f1228d0:	27bdff88 */ 	addiu	$sp,$sp,-120
/*  f1228d4:	30ceffff */ 	andi	$t6,$a2,0xffff
/*  f1228d8:	448e2000 */ 	mtc1	$t6,$f4
/*  f1228dc:	afb00028 */ 	sw	$s0,0x28($sp)
/*  f1228e0:	44877000 */ 	mtc1	$a3,$f14
/*  f1228e4:	00808025 */ 	or	$s0,$a0,$zero
/*  f1228e8:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f1228ec:	f7b60020 */ 	sdc1	$f22,0x20($sp)
/*  f1228f0:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f1228f4:	afa60080 */ 	sw	$a2,0x80($sp)
/*  f1228f8:	05c10005 */ 	bgez	$t6,.L0f122910
/*  f1228fc:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f122900:	3c014f80 */ 	lui	$at,0x4f80
/*  f122904:	44814000 */ 	mtc1	$at,$f8
/*  f122908:	00000000 */ 	nop
/*  f12290c:	46083180 */ 	add.s	$f6,$f6,$f8
.L0f122910:
/*  f122910:	3c014780 */ 	lui	$at,0x4780
/*  f122914:	44815000 */ 	mtc1	$at,$f10
/*  f122918:	c6120000 */ 	lwc1	$f18,0x0($s0)
/*  f12291c:	c4a40000 */ 	lwc1	$f4,0x0($a1)
/*  f122920:	460a3003 */ 	div.s	$f0,$f6,$f10
/*  f122924:	c4aa0010 */ 	lwc1	$f10,0x10($a1)
/*  f122928:	c6060004 */ 	lwc1	$f6,0x4($s0)
/*  f12292c:	3c013780 */ 	lui	$at,0x3780
/*  f122930:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f122934:	44816000 */ 	mtc1	$at,$f12
/*  f122938:	44808000 */ 	mtc1	$zero,$f16
/*  f12293c:	460a3482 */ 	mul.s	$f18,$f6,$f10
/*  f122940:	c4aa0020 */ 	lwc1	$f10,0x20($a1)
/*  f122944:	c6060008 */ 	lwc1	$f6,0x8($s0)
/*  f122948:	46124100 */ 	add.s	$f4,$f8,$f18
/*  f12294c:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f122950:	c4a60030 */ 	lwc1	$f6,0x30($a1)
/*  f122954:	46000086 */ 	mov.s	$f2,$f0
/*  f122958:	46082480 */ 	add.s	$f18,$f4,$f8
/*  f12295c:	46123280 */ 	add.s	$f10,$f6,$f18
/*  f122960:	e7aa0068 */ 	swc1	$f10,0x68($sp)
/*  f122964:	c6040000 */ 	lwc1	$f4,0x0($s0)
/*  f122968:	c4a80004 */ 	lwc1	$f8,0x4($a1)
/*  f12296c:	c6120004 */ 	lwc1	$f18,0x4($s0)
/*  f122970:	c4aa0014 */ 	lwc1	$f10,0x14($a1)
/*  f122974:	46082182 */ 	mul.s	$f6,$f4,$f8
/*  f122978:	00000000 */ 	nop
/*  f12297c:	460a9102 */ 	mul.s	$f4,$f18,$f10
/*  f122980:	c4aa0024 */ 	lwc1	$f10,0x24($a1)
/*  f122984:	c6120008 */ 	lwc1	$f18,0x8($s0)
/*  f122988:	46043200 */ 	add.s	$f8,$f6,$f4
/*  f12298c:	460a9182 */ 	mul.s	$f6,$f18,$f10
/*  f122990:	c4b20034 */ 	lwc1	$f18,0x34($a1)
/*  f122994:	46064100 */ 	add.s	$f4,$f8,$f6
/*  f122998:	46049280 */ 	add.s	$f10,$f18,$f4
/*  f12299c:	e7aa006c */ 	swc1	$f10,0x6c($sp)
/*  f1229a0:	c6080000 */ 	lwc1	$f8,0x0($s0)
/*  f1229a4:	c4a60008 */ 	lwc1	$f6,0x8($a1)
/*  f1229a8:	c6040004 */ 	lwc1	$f4,0x4($s0)
/*  f1229ac:	c4aa0018 */ 	lwc1	$f10,0x18($a1)
/*  f1229b0:	46064482 */ 	mul.s	$f18,$f8,$f6
/*  f1229b4:	00000000 */ 	nop
/*  f1229b8:	460a2202 */ 	mul.s	$f8,$f4,$f10
/*  f1229bc:	c4aa0028 */ 	lwc1	$f10,0x28($a1)
/*  f1229c0:	c6040008 */ 	lwc1	$f4,0x8($s0)
/*  f1229c4:	46089180 */ 	add.s	$f6,$f18,$f8
/*  f1229c8:	460a2482 */ 	mul.s	$f18,$f4,$f10
/*  f1229cc:	c4a40038 */ 	lwc1	$f4,0x38($a1)
/*  f1229d0:	46123200 */ 	add.s	$f8,$f6,$f18
/*  f1229d4:	46082280 */ 	add.s	$f10,$f4,$f8
/*  f1229d8:	e7aa0070 */ 	swc1	$f10,0x70($sp)
/*  f1229dc:	c4b2000c */ 	lwc1	$f18,0xc($a1)
/*  f1229e0:	c6060000 */ 	lwc1	$f6,0x0($s0)
/*  f1229e4:	c4aa001c */ 	lwc1	$f10,0x1c($a1)
/*  f1229e8:	c6080004 */ 	lwc1	$f8,0x4($s0)
/*  f1229ec:	46123102 */ 	mul.s	$f4,$f6,$f18
/*  f1229f0:	00000000 */ 	nop
/*  f1229f4:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f1229f8:	c4aa002c */ 	lwc1	$f10,0x2c($a1)
/*  f1229fc:	c6080008 */ 	lwc1	$f8,0x8($s0)
/*  f122a00:	46062480 */ 	add.s	$f18,$f4,$f6
/*  f122a04:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f122a08:	c4a8003c */ 	lwc1	$f8,0x3c($a1)
/*  f122a0c:	46049180 */ 	add.s	$f6,$f18,$f4
/*  f122a10:	460c7102 */ 	mul.s	$f4,$f14,$f12
/*  f122a14:	46064280 */ 	add.s	$f10,$f8,$f6
/*  f122a18:	e7aa0074 */ 	swc1	$f10,0x74($sp)
/*  f122a1c:	c612000c */ 	lwc1	$f18,0xc($s0)
/*  f122a20:	c7aa0088 */ 	lwc1	$f10,0x88($sp)
/*  f122a24:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f122a28:	e7a80060 */ 	swc1	$f8,0x60($sp)
/*  f122a2c:	460c5482 */ 	mul.s	$f18,$f10,$f12
/*  f122a30:	c6060010 */ 	lwc1	$f6,0x10($s0)
/*  f122a34:	c7a80074 */ 	lwc1	$f8,0x74($sp)
/*  f122a38:	46088032 */ 	c.eq.s	$f16,$f8
/*  f122a3c:	46123102 */ 	mul.s	$f4,$f6,$f18
/*  f122a40:	e7a40064 */ 	swc1	$f4,0x64($sp)
/*  f122a44:	45000004 */ 	bc1f	.L0f122a58
/*  f122a48:	c7a40068 */ 	lwc1	$f4,0x68($sp)
/*  f122a4c:	3c017f1b */ 	lui	$at,%hi(var7f1b50cc)
/*  f122a50:	10000006 */ 	b	.L0f122a6c
/*  f122a54:	c43650cc */ 	lwc1	$f22,%lo(var7f1b50cc)($at)
.L0f122a58:
/*  f122a58:	c7a60074 */ 	lwc1	$f6,0x74($sp)
/*  f122a5c:	3c013f80 */ 	lui	$at,0x3f80
/*  f122a60:	44815000 */ 	mtc1	$at,$f10
/*  f122a64:	46003482 */ 	mul.s	$f18,$f6,$f0
/*  f122a68:	46125583 */ 	div.s	$f22,$f10,$f18
.L0f122a6c:
/*  f122a6c:	4610b03c */ 	c.lt.s	$f22,$f16
/*  f122a70:	4600b006 */ 	mov.s	$f0,$f22
/*  f122a74:	45000002 */ 	bc1f	.L0f122a80
/*  f122a78:	3c017f1b */ 	lui	$at,%hi(var7f1b50d0)
/*  f122a7c:	c42050d0 */ 	lwc1	$f0,%lo(var7f1b50d0)($at)
.L0f122a80:
/*  f122a80:	46002202 */ 	mul.s	$f8,$f4,$f0
/*  f122a84:	c7aa006c */ 	lwc1	$f10,0x6c($sp)
/*  f122a88:	46024182 */ 	mul.s	$f6,$f8,$f2
/*  f122a8c:	c7a80070 */ 	lwc1	$f8,0x70($sp)
/*  f122a90:	46005482 */ 	mul.s	$f18,$f10,$f0
/*  f122a94:	e7a60048 */ 	swc1	$f6,0x48($sp)
/*  f122a98:	46029102 */ 	mul.s	$f4,$f18,$f2
/*  f122a9c:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*  f122aa0:	46004182 */ 	mul.s	$f6,$f8,$f0
/*  f122aa4:	e7a4004c */ 	swc1	$f4,0x4c($sp)
/*  f122aa8:	46023282 */ 	mul.s	$f10,$f6,$f2
/*  f122aac:	00000000 */ 	nop
/*  f122ab0:	46009102 */ 	mul.s	$f4,$f18,$f0
/*  f122ab4:	e7aa0050 */ 	swc1	$f10,0x50($sp)
/*  f122ab8:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f122abc:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f122ac0:	e7a80054 */ 	swc1	$f8,0x54($sp)
/*  f122ac4:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f122ac8:	46000506 */ 	mov.s	$f20,$f0
/*  f122acc:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f122ad0:	e7a00030 */ 	swc1	$f0,0x30($sp)
/*  f122ad4:	3c014080 */ 	lui	$at,0x4080
/*  f122ad8:	44813000 */ 	mtc1	$at,$f6
/*  f122adc:	c7a20030 */ 	lwc1	$f2,0x30($sp)
/*  f122ae0:	c7a80048 */ 	lwc1	$f8,0x48($sp)
/*  f122ae4:	46060282 */ 	mul.s	$f10,$f0,$f6
/*  f122ae8:	46021480 */ 	add.s	$f18,$f2,$f2
/*  f122aec:	4614a180 */ 	add.s	$f6,$f20,$f20
/*  f122af0:	46125100 */ 	add.s	$f4,$f10,$f18
/*  f122af4:	46064282 */ 	mul.s	$f10,$f8,$f6
/*  f122af8:	460a2480 */ 	add.s	$f18,$f4,$f10
/*  f122afc:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f122b00:	e7b20038 */ 	swc1	$f18,0x38($sp)
/*  f122b04:	0fc2d5fa */ 	jal	currentPlayerGetScreenHeight
/*  f122b08:	46000506 */ 	mov.s	$f20,$f0
/*  f122b0c:	0fc2d602 */ 	jal	currentPlayerGetScreenTop
/*  f122b10:	e7a00030 */ 	swc1	$f0,0x30($sp)
/*  f122b14:	3c017f1b */ 	lui	$at,%hi(var7f1b50d4)
/*  f122b18:	c43050d4 */ 	lwc1	$f16,%lo(var7f1b50d4)($at)
/*  f122b1c:	3c014080 */ 	lui	$at,0x4080
/*  f122b20:	44814000 */ 	mtc1	$at,$f8
/*  f122b24:	c7a20030 */ 	lwc1	$f2,0x30($sp)
/*  f122b28:	c7b2004c */ 	lwc1	$f18,0x4c($sp)
/*  f122b2c:	46080182 */ 	mul.s	$f6,$f0,$f8
/*  f122b30:	46021100 */ 	add.s	$f4,$f2,$f2
/*  f122b34:	3c017f1b */ 	lui	$at,%hi(var7f1b50d8)
/*  f122b38:	3c06457f */ 	lui	$a2,0x457f
/*  f122b3c:	46009207 */ 	neg.s	$f8,$f18
/*  f122b40:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f122b44:	c42e50d8 */ 	lwc1	$f14,%lo(var7f1b50d8)($at)
/*  f122b48:	46043280 */ 	add.s	$f10,$f6,$f4
/*  f122b4c:	c7ac0038 */ 	lwc1	$f12,0x38($sp)
/*  f122b50:	4614a180 */ 	add.s	$f6,$f20,$f20
/*  f122b54:	46064102 */ 	mul.s	$f4,$f8,$f6
/*  f122b58:	c7a80050 */ 	lwc1	$f8,0x50($sp)
/*  f122b5c:	46104182 */ 	mul.s	$f6,$f8,$f16
/*  f122b60:	46045480 */ 	add.s	$f18,$f10,$f4
/*  f122b64:	c7a40054 */ 	lwc1	$f4,0x54($sp)
/*  f122b68:	46103280 */ 	add.s	$f10,$f6,$f16
/*  f122b6c:	e7b2003c */ 	swc1	$f18,0x3c($sp)
/*  f122b70:	44809000 */ 	mtc1	$zero,$f18
/*  f122b74:	e7aa0040 */ 	swc1	$f10,0x40($sp)
/*  f122b78:	46122202 */ 	mul.s	$f8,$f4,$f18
/*  f122b7c:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f122b80:	e7a80044 */ 	swc1	$f8,0x44($sp)
/*  f122b84:	3c017f1b */ 	lui	$at,%hi(var7f1b50dc)
/*  f122b88:	3c06457f */ 	lui	$a2,0x457f
/*  f122b8c:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*  f122b90:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f122b94:	c42e50dc */ 	lwc1	$f14,%lo(var7f1b50dc)($at)
/*  f122b98:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f122b9c:	c7ac003c */ 	lwc1	$f12,0x3c($sp)
/*  f122ba0:	44807000 */ 	mtc1	$zero,$f14
/*  f122ba4:	3c0646ff */ 	lui	$a2,0x46ff
/*  f122ba8:	e7a0003c */ 	swc1	$f0,0x3c($sp)
/*  f122bac:	34c6fe00 */ 	ori	$a2,$a2,0xfe00
/*  f122bb0:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f122bb4:	c7ac0040 */ 	lwc1	$f12,0x40($sp)
/*  f122bb8:	44807000 */ 	mtc1	$zero,$f14
/*  f122bbc:	3c0646ff */ 	lui	$a2,0x46ff
/*  f122bc0:	e7a00040 */ 	swc1	$f0,0x40($sp)
/*  f122bc4:	34c6fe00 */ 	ori	$a2,$a2,0xfe00
/*  f122bc8:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f122bcc:	c7ac0044 */ 	lwc1	$f12,0x44($sp)
/*  f122bd0:	8fa3008c */ 	lw	$v1,0x8c($sp)
/*  f122bd4:	c7a60068 */ 	lwc1	$f6,0x68($sp)
/*  f122bd8:	e7a00044 */ 	swc1	$f0,0x44($sp)
/*  f122bdc:	e4660000 */ 	swc1	$f6,0x0($v1)
/*  f122be0:	c7aa006c */ 	lwc1	$f10,0x6c($sp)
/*  f122be4:	e46a0004 */ 	swc1	$f10,0x4($v1)
/*  f122be8:	c7a40070 */ 	lwc1	$f4,0x70($sp)
/*  f122bec:	e4640008 */ 	swc1	$f4,0x8($v1)
/*  f122bf0:	c7b20074 */ 	lwc1	$f18,0x74($sp)
/*  f122bf4:	e472000c */ 	swc1	$f18,0xc($v1)
/*  f122bf8:	c7a80060 */ 	lwc1	$f8,0x60($sp)
/*  f122bfc:	e4680020 */ 	swc1	$f8,0x20($v1)
/*  f122c00:	c7a60064 */ 	lwc1	$f6,0x64($sp)
/*  f122c04:	e4660024 */ 	swc1	$f6,0x24($v1)
/*  f122c08:	c7aa0038 */ 	lwc1	$f10,0x38($sp)
/*  f122c0c:	0fc595f3 */ 	jal	skyGetCurrent
/*  f122c10:	e46a0028 */ 	swc1	$f10,0x28($v1)
/*  f122c14:	3c014080 */ 	lui	$at,0x4080
/*  f122c18:	44819000 */ 	mtc1	$at,$f18
/*  f122c1c:	c4440040 */ 	lwc1	$f4,0x40($v0)
/*  f122c20:	c7a6003c */ 	lwc1	$f6,0x3c($sp)
/*  f122c24:	8fa3008c */ 	lw	$v1,0x8c($sp)
/*  f122c28:	46122202 */ 	mul.s	$f8,$f4,$f18
/*  f122c2c:	3c014f80 */ 	lui	$at,0x4f80
/*  f122c30:	46083281 */ 	sub.s	$f10,$f6,$f8
/*  f122c34:	e46a002c */ 	swc1	$f10,0x2c($v1)
/*  f122c38:	c7a40040 */ 	lwc1	$f4,0x40($sp)
/*  f122c3c:	e4760034 */ 	swc1	$f22,0x34($v1)
/*  f122c40:	e4640030 */ 	swc1	$f4,0x30($v1)
/*  f122c44:	920f0014 */ 	lbu	$t7,0x14($s0)
/*  f122c48:	448f9000 */ 	mtc1	$t7,$f18
/*  f122c4c:	05e10004 */ 	bgez	$t7,.L0f122c60
/*  f122c50:	468091a0 */ 	cvt.s.w	$f6,$f18
/*  f122c54:	44814000 */ 	mtc1	$at,$f8
/*  f122c58:	00000000 */ 	nop
/*  f122c5c:	46083180 */ 	add.s	$f6,$f6,$f8
.L0f122c60:
/*  f122c60:	e4660010 */ 	swc1	$f6,0x10($v1)
/*  f122c64:	92180015 */ 	lbu	$t8,0x15($s0)
/*  f122c68:	3c014f80 */ 	lui	$at,0x4f80
/*  f122c6c:	44985000 */ 	mtc1	$t8,$f10
/*  f122c70:	07010004 */ 	bgez	$t8,.L0f122c84
/*  f122c74:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f122c78:	44819000 */ 	mtc1	$at,$f18
/*  f122c7c:	00000000 */ 	nop
/*  f122c80:	46122100 */ 	add.s	$f4,$f4,$f18
.L0f122c84:
/*  f122c84:	e4640014 */ 	swc1	$f4,0x14($v1)
/*  f122c88:	92190016 */ 	lbu	$t9,0x16($s0)
/*  f122c8c:	3c014f80 */ 	lui	$at,0x4f80
/*  f122c90:	44994000 */ 	mtc1	$t9,$f8
/*  f122c94:	07210004 */ 	bgez	$t9,.L0f122ca8
/*  f122c98:	468041a0 */ 	cvt.s.w	$f6,$f8
/*  f122c9c:	44815000 */ 	mtc1	$at,$f10
/*  f122ca0:	00000000 */ 	nop
/*  f122ca4:	460a3180 */ 	add.s	$f6,$f6,$f10
.L0f122ca8:
/*  f122ca8:	e4660018 */ 	swc1	$f6,0x18($v1)
/*  f122cac:	92080017 */ 	lbu	$t0,0x17($s0)
/*  f122cb0:	3c014f80 */ 	lui	$at,0x4f80
/*  f122cb4:	44889000 */ 	mtc1	$t0,$f18
/*  f122cb8:	05010004 */ 	bgez	$t0,.L0f122ccc
/*  f122cbc:	46809120 */ 	cvt.s.w	$f4,$f18
/*  f122cc0:	44814000 */ 	mtc1	$at,$f8
/*  f122cc4:	00000000 */ 	nop
/*  f122cc8:	46082100 */ 	add.s	$f4,$f4,$f8
.L0f122ccc:
/*  f122ccc:	e464001c */ 	swc1	$f4,0x1c($v1)
/*  f122cd0:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f122cd4:	8fb00028 */ 	lw	$s0,0x28($sp)
/*  f122cd8:	d7b60020 */ 	ldc1	$f22,0x20($sp)
/*  f122cdc:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f122ce0:	03e00008 */ 	jr	$ra
/*  f122ce4:	27bd0078 */ 	addiu	$sp,$sp,0x78
);

GLOBAL_ASM(
glabel func0f122ce8
/*  f122ce8:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f122cec:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f122cf0:	c4a60028 */ 	lwc1	$f6,0x28($a1)
/*  f122cf4:	c4840028 */ 	lwc1	$f4,0x28($a0)
/*  f122cf8:	c4aa002c */ 	lwc1	$f10,0x2c($a1)
/*  f122cfc:	c488002c */ 	lwc1	$f8,0x2c($a0)
/*  f122d00:	46062001 */ 	sub.s	$f0,$f4,$f6
/*  f122d04:	460a4081 */ 	sub.s	$f2,$f8,$f10
/*  f122d08:	46000402 */ 	mul.s	$f16,$f0,$f0
/*  f122d0c:	00000000 */ 	nop
/*  f122d10:	46021482 */ 	mul.s	$f18,$f2,$f2
/*  f122d14:	0c012974 */ 	jal	sqrtf
/*  f122d18:	46128300 */ 	add.s	$f12,$f16,$f18
/*  f122d1c:	3c013f80 */ 	lui	$at,0x3f80
/*  f122d20:	44812000 */ 	mtc1	$at,$f4
/*  f122d24:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f122d28:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*  f122d2c:	4604003c */ 	c.lt.s	$f0,$f4
/*  f122d30:	00001825 */ 	or	$v1,$zero,$zero
/*  f122d34:	45000003 */ 	bc1f	.L0f122d44
/*  f122d38:	00000000 */ 	nop
/*  f122d3c:	10000001 */ 	b	.L0f122d44
/*  f122d40:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f122d44:
/*  f122d44:	03e00008 */ 	jr	$ra
/*  f122d48:	00601025 */ 	or	$v0,$v1,$zero
);

GLOBAL_ASM(
glabel func0f122d4c
.late_rodata
glabel var7f1b50e0
.word 0xc4eac000
glabel var7f1b50e4
.word 0xc4eac000
glabel var7f1b50e8
.word 0xc4eac000
glabel var7f1b50ec
.word 0x46fffe00
.text
/*  f122d4c:	27bdfb78 */ 	addiu	$sp,$sp,-1160
/*  f122d50:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f122d54:	00808025 */ 	or	$s0,$a0,$zero
/*  f122d58:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f122d5c:	afa5048c */ 	sw	$a1,0x48c($sp)
/*  f122d60:	00a02025 */ 	or	$a0,$a1,$zero
/*  f122d64:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f122d68:	00c02825 */ 	or	$a1,$a2,$zero
/*  f122d6c:	afa60490 */ 	sw	$a2,0x490($sp)
/*  f122d70:	0fc48b3a */ 	jal	func0f122ce8
/*  f122d74:	afa70494 */ 	sw	$a3,0x494($sp)
/*  f122d78:	8fa60490 */ 	lw	$a2,0x490($sp)
/*  f122d7c:	14400013 */ 	bnez	$v0,.L0f122dcc
/*  f122d80:	8fa70494 */ 	lw	$a3,0x494($sp)
/*  f122d84:	00c02025 */ 	or	$a0,$a2,$zero
/*  f122d88:	00e02825 */ 	or	$a1,$a3,$zero
/*  f122d8c:	afa60490 */ 	sw	$a2,0x490($sp)
/*  f122d90:	0fc48b3a */ 	jal	func0f122ce8
/*  f122d94:	afa70494 */ 	sw	$a3,0x494($sp)
/*  f122d98:	8faf048c */ 	lw	$t7,0x48c($sp)
/*  f122d9c:	8fa60490 */ 	lw	$a2,0x490($sp)
/*  f122da0:	1440000a */ 	bnez	$v0,.L0f122dcc
/*  f122da4:	8fa70494 */ 	lw	$a3,0x494($sp)
/*  f122da8:	00e02025 */ 	or	$a0,$a3,$zero
/*  f122dac:	01e02825 */ 	or	$a1,$t7,$zero
/*  f122db0:	afa60490 */ 	sw	$a2,0x490($sp)
/*  f122db4:	0fc48b3a */ 	jal	func0f122ce8
/*  f122db8:	afa70494 */ 	sw	$a3,0x494($sp)
/*  f122dbc:	8fa3048c */ 	lw	$v1,0x48c($sp)
/*  f122dc0:	8fa60490 */ 	lw	$a2,0x490($sp)
/*  f122dc4:	10400003 */ 	beqz	$v0,.L0f122dd4
/*  f122dc8:	8fa70494 */ 	lw	$a3,0x494($sp)
.L0f122dcc:
/*  f122dcc:	1000047c */ 	b	.L0f123fc0
/*  f122dd0:	02001025 */ 	or	$v0,$s0,$zero
.L0f122dd4:
/*  f122dd4:	3c014780 */ 	lui	$at,0x4780
/*  f122dd8:	44813000 */ 	mtc1	$at,$f6
/*  f122ddc:	c7a40498 */ 	lwc1	$f4,0x498($sp)
/*  f122de0:	3c013780 */ 	lui	$at,0x3780
/*  f122de4:	4480a000 */ 	mtc1	$zero,$f20
/*  f122de8:	46062203 */ 	div.s	$f8,$f4,$f6
/*  f122dec:	e7a80378 */ 	swc1	$f8,0x378($sp)
/*  f122df0:	c4c4002c */ 	lwc1	$f4,0x2c($a2)
/*  f122df4:	c4ca0028 */ 	lwc1	$f10,0x28($a2)
/*  f122df8:	c4600028 */ 	lwc1	$f0,0x28($v1)
/*  f122dfc:	e7a4005c */ 	swc1	$f4,0x5c($sp)
/*  f122e00:	c4e80028 */ 	lwc1	$f8,0x28($a3)
/*  f122e04:	46005301 */ 	sub.s	$f12,$f10,$f0
/*  f122e08:	c46e002c */ 	lwc1	$f14,0x2c($v1)
/*  f122e0c:	c7a6005c */ 	lwc1	$f6,0x5c($sp)
/*  f122e10:	46004281 */ 	sub.s	$f10,$f8,$f0
/*  f122e14:	460e3401 */ 	sub.s	$f16,$f6,$f14
/*  f122e18:	e7aa046c */ 	swc1	$f10,0x46c($sp)
/*  f122e1c:	c4e4002c */ 	lwc1	$f4,0x2c($a3)
/*  f122e20:	c7a8046c */ 	lwc1	$f8,0x46c($sp)
/*  f122e24:	e7a40054 */ 	swc1	$f4,0x54($sp)
/*  f122e28:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*  f122e2c:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f122e30:	44814000 */ 	mtc1	$at,$f8
/*  f122e34:	460e3481 */ 	sub.s	$f18,$f6,$f14
/*  f122e38:	46126102 */ 	mul.s	$f4,$f12,$f18
/*  f122e3c:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f122e40:	c7a4005c */ 	lwc1	$f4,0x5c($sp)
/*  f122e44:	46083082 */ 	mul.s	$f2,$f6,$f8
/*  f122e48:	4602a032 */ 	c.eq.s	$f20,$f2
/*  f122e4c:	e7a20444 */ 	swc1	$f2,0x444($sp)
/*  f122e50:	45020004 */ 	bc1fl	.L0f122e64
/*  f122e54:	460e203c */ 	c.lt.s	$f4,$f14
/*  f122e58:	10000459 */ 	b	.L0f123fc0
/*  f122e5c:	02001025 */ 	or	$v0,$s0,$zero
/*  f122e60:	460e203c */ 	c.lt.s	$f4,$f14
.L0f122e64:
/*  f122e64:	3c013f80 */ 	lui	$at,0x3f80
/*  f122e68:	44815000 */ 	mtc1	$at,$f10
/*  f122e6c:	00604825 */ 	or	$t1,$v1,$zero
/*  f122e70:	00c04025 */ 	or	$t0,$a2,$zero
/*  f122e74:	00e05825 */ 	or	$t3,$a3,$zero
/*  f122e78:	45000009 */ 	bc1f	.L0f122ea0
/*  f122e7c:	46025403 */ 	div.s	$f16,$f10,$f2
/*  f122e80:	3c01bf80 */ 	lui	$at,0xbf80
/*  f122e84:	44816000 */ 	mtc1	$at,$f12
/*  f122e88:	00604025 */ 	or	$t0,$v1,$zero
/*  f122e8c:	00c04825 */ 	or	$t1,$a2,$zero
/*  f122e90:	460c1382 */ 	mul.s	$f14,$f2,$f12
/*  f122e94:	e7ae0444 */ 	swc1	$f14,0x444($sp)
/*  f122e98:	460c8402 */ 	mul.s	$f16,$f16,$f12
/*  f122e9c:	00000000 */ 	nop
.L0f122ea0:
/*  f122ea0:	c500002c */ 	lwc1	$f0,0x2c($t0)
/*  f122ea4:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*  f122ea8:	3c01bf80 */ 	lui	$at,0xbf80
/*  f122eac:	44816000 */ 	mtc1	$at,$f12
/*  f122eb0:	4600303c */ 	c.lt.s	$f6,$f0
/*  f122eb4:	c7ae0444 */ 	lwc1	$f14,0x444($sp)
/*  f122eb8:	3c013e80 */ 	lui	$at,0x3e80
/*  f122ebc:	45020007 */ 	bc1fl	.L0f122edc
/*  f122ec0:	e7ae0444 */ 	swc1	$f14,0x444($sp)
/*  f122ec4:	460c7382 */ 	mul.s	$f14,$f14,$f12
/*  f122ec8:	01005825 */ 	or	$t3,$t0,$zero
/*  f122ecc:	00e04025 */ 	or	$t0,$a3,$zero
/*  f122ed0:	460c8402 */ 	mul.s	$f16,$f16,$f12
/*  f122ed4:	c4e0002c */ 	lwc1	$f0,0x2c($a3)
/*  f122ed8:	e7ae0444 */ 	swc1	$f14,0x444($sp)
.L0f122edc:
/*  f122edc:	e7b00440 */ 	swc1	$f16,0x440($sp)
/*  f122ee0:	c528002c */ 	lwc1	$f8,0x2c($t1)
/*  f122ee4:	4608003c */ 	c.lt.s	$f0,$f8
/*  f122ee8:	44810000 */ 	mtc1	$at,$f0
/*  f122eec:	3c014080 */ 	lui	$at,0x4080
/*  f122ef0:	44811000 */ 	mtc1	$at,$f2
/*  f122ef4:	45000008 */ 	bc1f	.L0f122f18
/*  f122ef8:	3c013e80 */ 	lui	$at,0x3e80
/*  f122efc:	460c7382 */ 	mul.s	$f14,$f14,$f12
/*  f122f00:	01001025 */ 	or	$v0,$t0,$zero
/*  f122f04:	01204025 */ 	or	$t0,$t1,$zero
/*  f122f08:	460c8402 */ 	mul.s	$f16,$f16,$f12
/*  f122f0c:	00404825 */ 	or	$t1,$v0,$zero
/*  f122f10:	e7ae0444 */ 	swc1	$f14,0x444($sp)
/*  f122f14:	e7b00440 */ 	swc1	$f16,0x440($sp)
.L0f122f18:
/*  f122f18:	c50a0028 */ 	lwc1	$f10,0x28($t0)
/*  f122f1c:	44812000 */ 	mtc1	$at,$f4
/*  f122f20:	e7b40424 */ 	swc1	$f20,0x424($sp)
/*  f122f24:	3c0644ea */ 	lui	$a2,0x44ea
/*  f122f28:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f122f2c:	44815000 */ 	mtc1	$at,$f10
/*  f122f30:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f122f34:	e7a60420 */ 	swc1	$f6,0x420($sp)
/*  f122f38:	c5280028 */ 	lwc1	$f8,0x28($t1)
/*  f122f3c:	e7b4042c */ 	swc1	$f20,0x42c($sp)
/*  f122f40:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f122f44:	44814000 */ 	mtc1	$at,$f8
/*  f122f48:	3c017f1b */ 	lui	$at,%hi(var7f1b50e0)
/*  f122f4c:	e7a40428 */ 	swc1	$f4,0x428($sp)
/*  f122f50:	c5260028 */ 	lwc1	$f6,0x28($t1)
/*  f122f54:	e7b40434 */ 	swc1	$f20,0x434($sp)
/*  f122f58:	e7b4043c */ 	swc1	$f20,0x43c($sp)
/*  f122f5c:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f122f60:	e7b40438 */ 	swc1	$f20,0x438($sp)
/*  f122f64:	e7aa0430 */ 	swc1	$f10,0x430($sp)
/*  f122f68:	c5640028 */ 	lwc1	$f4,0x28($t3)
/*  f122f6c:	e7a40448 */ 	swc1	$f4,0x448($sp)
/*  f122f70:	c566002c */ 	lwc1	$f6,0x2c($t3)
/*  f122f74:	e7a6044c */ 	swc1	$f6,0x44c($sp)
/*  f122f78:	c5080028 */ 	lwc1	$f8,0x28($t0)
/*  f122f7c:	e7a80450 */ 	swc1	$f8,0x450($sp)
/*  f122f80:	c50a002c */ 	lwc1	$f10,0x2c($t0)
/*  f122f84:	c7a80450 */ 	lwc1	$f8,0x450($sp)
/*  f122f88:	e7aa0454 */ 	swc1	$f10,0x454($sp)
/*  f122f8c:	c5240028 */ 	lwc1	$f4,0x28($t1)
/*  f122f90:	e7a40458 */ 	swc1	$f4,0x458($sp)
/*  f122f94:	c7aa0458 */ 	lwc1	$f10,0x458($sp)
/*  f122f98:	c526002c */ 	lwc1	$f6,0x2c($t1)
/*  f122f9c:	e7a80028 */ 	swc1	$f8,0x28($sp)
/*  f122fa0:	460a4101 */ 	sub.s	$f4,$f8,$f10
/*  f122fa4:	e7a6045c */ 	swc1	$f6,0x45c($sp)
/*  f122fa8:	c7a60454 */ 	lwc1	$f6,0x454($sp)
/*  f122fac:	c7a8045c */ 	lwc1	$f8,0x45c($sp)
/*  f122fb0:	e7a40474 */ 	swc1	$f4,0x474($sp)
/*  f122fb4:	e7a40030 */ 	swc1	$f4,0x30($sp)
/*  f122fb8:	e7aa002c */ 	swc1	$f10,0x2c($sp)
/*  f122fbc:	c7a4002c */ 	lwc1	$f4,0x2c($sp)
/*  f122fc0:	46083401 */ 	sub.s	$f16,$f6,$f8
/*  f122fc4:	e7a6002c */ 	swc1	$f6,0x2c($sp)
/*  f122fc8:	c7a6044c */ 	lwc1	$f6,0x44c($sp)
/*  f122fcc:	c7aa0448 */ 	lwc1	$f10,0x448($sp)
/*  f122fd0:	e7b403fc */ 	swc1	$f20,0x3fc($sp)
/*  f122fd4:	46083481 */ 	sub.s	$f18,$f6,$f8
/*  f122fd8:	c7a80028 */ 	lwc1	$f8,0x28($sp)
/*  f122fdc:	e7b403f8 */ 	swc1	$f20,0x3f8($sp)
/*  f122fe0:	46045101 */ 	sub.s	$f4,$f10,$f4
/*  f122fe4:	e7b403dc */ 	swc1	$f20,0x3dc($sp)
/*  f122fe8:	e7b403d8 */ 	swc1	$f20,0x3d8($sp)
/*  f122fec:	46085301 */ 	sub.s	$f12,$f10,$f8
/*  f122ff0:	c7aa002c */ 	lwc1	$f10,0x2c($sp)
/*  f122ff4:	e7a4046c */ 	swc1	$f4,0x46c($sp)
/*  f122ff8:	e7b403a0 */ 	swc1	$f20,0x3a0($sp)
/*  f122ffc:	46006202 */ 	mul.s	$f8,$f12,$f0
/*  f123000:	460a3381 */ 	sub.s	$f14,$f6,$f10
/*  f123004:	c7aa0030 */ 	lwc1	$f10,0x30($sp)
/*  f123008:	e7ac0464 */ 	swc1	$f12,0x464($sp)
/*  f12300c:	e7b403a8 */ 	swc1	$f20,0x3a8($sp)
/*  f123010:	46007182 */ 	mul.s	$f6,$f14,$f0
/*  f123014:	e7ae0460 */ 	swc1	$f14,0x460($sp)
/*  f123018:	e7a803e0 */ 	swc1	$f8,0x3e0($sp)
/*  f12301c:	46005202 */ 	mul.s	$f8,$f10,$f0
/*  f123020:	e7b403b0 */ 	swc1	$f20,0x3b0($sp)
/*  f123024:	e7b403bc */ 	swc1	$f20,0x3bc($sp)
/*  f123028:	e7b403b8 */ 	swc1	$f20,0x3b8($sp)
/*  f12302c:	e7a603e4 */ 	swc1	$f6,0x3e4($sp)
/*  f123030:	46008182 */ 	mul.s	$f6,$f16,$f0
/*  f123034:	e7b40380 */ 	swc1	$f20,0x380($sp)
/*  f123038:	e7a803e8 */ 	swc1	$f8,0x3e8($sp)
/*  f12303c:	46002202 */ 	mul.s	$f8,$f4,$f0
/*  f123040:	e7b40388 */ 	swc1	$f20,0x388($sp)
/*  f123044:	e7b40390 */ 	swc1	$f20,0x390($sp)
/*  f123048:	e7b4039c */ 	swc1	$f20,0x39c($sp)
/*  f12304c:	e7a603ec */ 	swc1	$f6,0x3ec($sp)
/*  f123050:	46009182 */ 	mul.s	$f6,$f18,$f0
/*  f123054:	c7a00460 */ 	lwc1	$f0,0x460($sp)
/*  f123058:	e7a803f0 */ 	swc1	$f8,0x3f0($sp)
/*  f12305c:	46026202 */ 	mul.s	$f8,$f12,$f2
/*  f123060:	e7b40398 */ 	swc1	$f20,0x398($sp)
/*  f123064:	afab047c */ 	sw	$t3,0x47c($sp)
/*  f123068:	afa90484 */ 	sw	$t1,0x484($sp)
/*  f12306c:	e7a603f4 */ 	swc1	$f6,0x3f4($sp)
/*  f123070:	46027182 */ 	mul.s	$f6,$f14,$f2
/*  f123074:	c42e50e0 */ 	lwc1	$f14,%lo(var7f1b50e0)($at)
/*  f123078:	e7a803c0 */ 	swc1	$f8,0x3c0($sp)
/*  f12307c:	46025202 */ 	mul.s	$f8,$f10,$f2
/*  f123080:	afa80480 */ 	sw	$t0,0x480($sp)
/*  f123084:	e7a603c4 */ 	swc1	$f6,0x3c4($sp)
/*  f123088:	46028182 */ 	mul.s	$f6,$f16,$f2
/*  f12308c:	e7a803c8 */ 	swc1	$f8,0x3c8($sp)
/*  f123090:	46022202 */ 	mul.s	$f8,$f4,$f2
/*  f123094:	e7a603cc */ 	swc1	$f6,0x3cc($sp)
/*  f123098:	46029182 */ 	mul.s	$f6,$f18,$f2
/*  f12309c:	e7a803d0 */ 	swc1	$f8,0x3d0($sp)
/*  f1230a0:	46001203 */ 	div.s	$f8,$f2,$f0
/*  f1230a4:	e7a603d4 */ 	swc1	$f6,0x3d4($sp)
/*  f1230a8:	46101183 */ 	div.s	$f6,$f2,$f16
/*  f1230ac:	e7a803a4 */ 	swc1	$f8,0x3a4($sp)
/*  f1230b0:	46121203 */ 	div.s	$f8,$f2,$f18
/*  f1230b4:	e7a603ac */ 	swc1	$f6,0x3ac($sp)
/*  f1230b8:	c7a60464 */ 	lwc1	$f6,0x464($sp)
/*  f1230bc:	46003303 */ 	div.s	$f12,$f6,$f0
/*  f1230c0:	e7a803b4 */ 	swc1	$f8,0x3b4($sp)
/*  f1230c4:	46122183 */ 	div.s	$f6,$f4,$f18
/*  f1230c8:	e7ac0384 */ 	swc1	$f12,0x384($sp)
/*  f1230cc:	46105203 */ 	div.s	$f8,$f10,$f16
/*  f1230d0:	e7a60394 */ 	swc1	$f6,0x394($sp)
/*  f1230d4:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f1230d8:	e7a8038c */ 	swc1	$f8,0x38c($sp)
/*  f1230dc:	3c017f1b */ 	lui	$at,%hi(var7f1b50e4)
/*  f1230e0:	3c0644ea */ 	lui	$a2,0x44ea
/*  f1230e4:	e7a00384 */ 	swc1	$f0,0x384($sp)
/*  f1230e8:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f1230ec:	c42e50e4 */ 	lwc1	$f14,%lo(var7f1b50e4)($at)
/*  f1230f0:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f1230f4:	c7ac038c */ 	lwc1	$f12,0x38c($sp)
/*  f1230f8:	3c017f1b */ 	lui	$at,%hi(var7f1b50e8)
/*  f1230fc:	3c0644ea */ 	lui	$a2,0x44ea
/*  f123100:	e7a0038c */ 	swc1	$f0,0x38c($sp)
/*  f123104:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f123108:	c42e50e8 */ 	lwc1	$f14,%lo(var7f1b50e8)($at)
/*  f12310c:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f123110:	c7ac0394 */ 	lwc1	$f12,0x394($sp)
/*  f123114:	8fa90484 */ 	lw	$t1,0x484($sp)
/*  f123118:	e7a00394 */ 	swc1	$f0,0x394($sp)
/*  f12311c:	3c013e80 */ 	lui	$at,0x3e80
/*  f123120:	44814000 */ 	mtc1	$at,$f8
/*  f123124:	c52a002c */ 	lwc1	$f10,0x2c($t1)
/*  f123128:	3c014600 */ 	lui	$at,0x4600
/*  f12312c:	46085082 */ 	mul.s	$f2,$f10,$f8
/*  f123130:	4600110d */ 	trunc.w.s	$f4,$f2
/*  f123134:	44192000 */ 	mfc1	$t9,$f4
/*  f123138:	c7a4038c */ 	lwc1	$f4,0x38c($sp)
/*  f12313c:	44993000 */ 	mtc1	$t9,$f6
/*  f123140:	00000000 */ 	nop
/*  f123144:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f123148:	44813000 */ 	mtc1	$at,$f6
/*  f12314c:	00000000 */ 	nop
/*  f123150:	46062302 */ 	mul.s	$f12,$f4,$f6
/*  f123154:	460a1201 */ 	sub.s	$f8,$f2,$f10
/*  f123158:	0fc47d04 */ 	jal	func0f11f410
/*  f12315c:	e7a8037c */ 	swc1	$f8,0x37c($sp)
/*  f123160:	3c013900 */ 	lui	$at,0x3900
/*  f123164:	44815000 */ 	mtc1	$at,$f10
/*  f123168:	c7a4037c */ 	lwc1	$f4,0x37c($sp)
/*  f12316c:	3c014600 */ 	lui	$at,0x4600
/*  f123170:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f123174:	c7aa0428 */ 	lwc1	$f10,0x428($sp)
/*  f123178:	46044182 */ 	mul.s	$f6,$f8,$f4
/*  f12317c:	c7a40394 */ 	lwc1	$f4,0x394($sp)
/*  f123180:	46065201 */ 	sub.s	$f8,$f10,$f6
/*  f123184:	44815000 */ 	mtc1	$at,$f10
/*  f123188:	00000000 */ 	nop
/*  f12318c:	460a2302 */ 	mul.s	$f12,$f4,$f10
/*  f123190:	0fc47d04 */ 	jal	func0f11f410
/*  f123194:	e7a80408 */ 	swc1	$f8,0x408($sp)
/*  f123198:	3c013900 */ 	lui	$at,0x3900
/*  f12319c:	44813000 */ 	mtc1	$at,$f6
/*  f1231a0:	c7a4037c */ 	lwc1	$f4,0x37c($sp)
/*  f1231a4:	3c07b400 */ 	lui	$a3,0xb400
/*  f1231a8:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f1231ac:	c7a60430 */ 	lwc1	$f6,0x430($sp)
/*  f1231b0:	8fa80480 */ 	lw	$t0,0x480($sp)
/*  f1231b4:	8fa90484 */ 	lw	$t1,0x484($sp)
/*  f1231b8:	8fab047c */ 	lw	$t3,0x47c($sp)
/*  f1231bc:	02002825 */ 	or	$a1,$s0,$zero
/*  f1231c0:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1231c4:	46044282 */ 	mul.s	$f10,$f8,$f4
/*  f1231c8:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f1231cc:	3c06c800 */ 	lui	$a2,0xc800
/*  f1231d0:	02001025 */ 	or	$v0,$s0,$zero
/*  f1231d4:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f1231d8:	e7a80410 */ 	swc1	$f8,0x410($sp)
/*  f1231dc:	aca70000 */ 	sw	$a3,0x0($a1)
/*  f1231e0:	8fb8049c */ 	lw	$t8,0x49c($sp)
/*  f1231e4:	c7a40444 */ 	lwc1	$f4,0x444($sp)
/*  f1231e8:	13000003 */ 	beqz	$t8,.L0f1231f8
/*  f1231ec:	00000000 */ 	nop
/*  f1231f0:	10000001 */ 	b	.L0f1231f8
/*  f1231f4:	3c06ce00 */ 	lui	$a2,0xce00
.L0f1231f8:
/*  f1231f8:	4614203c */ 	c.lt.s	$f4,$f20
/*  f1231fc:	00001825 */ 	or	$v1,$zero,$zero
/*  f123200:	45000003 */ 	bc1f	.L0f123210
/*  f123204:	00000000 */ 	nop
/*  f123208:	10000001 */ 	b	.L0f123210
/*  f12320c:	3c030080 */ 	lui	$v1,0x80
.L0f123210:
/*  f123210:	444ef800 */ 	cfc1	$t6,$31
/*  f123214:	44d9f800 */ 	ctc1	$t9,$31
/*  f123218:	c566002c */ 	lwc1	$f6,0x2c($t3)
/*  f12321c:	00667825 */ 	or	$t7,$v1,$a2
/*  f123220:	3c014f00 */ 	lui	$at,0x4f00
/*  f123224:	460032a4 */ 	cvt.w.s	$f10,$f6
/*  f123228:	4459f800 */ 	cfc1	$t9,$31
/*  f12322c:	00000000 */ 	nop
/*  f123230:	33390078 */ 	andi	$t9,$t9,0x78
/*  f123234:	53200013 */ 	beqzl	$t9,.L0f123284
/*  f123238:	44195000 */ 	mfc1	$t9,$f10
/*  f12323c:	44815000 */ 	mtc1	$at,$f10
/*  f123240:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f123244:	460a3281 */ 	sub.s	$f10,$f6,$f10
/*  f123248:	44d9f800 */ 	ctc1	$t9,$31
/*  f12324c:	00000000 */ 	nop
/*  f123250:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f123254:	4459f800 */ 	cfc1	$t9,$31
/*  f123258:	00000000 */ 	nop
/*  f12325c:	33390078 */ 	andi	$t9,$t9,0x78
/*  f123260:	17200005 */ 	bnez	$t9,.L0f123278
/*  f123264:	00000000 */ 	nop
/*  f123268:	44195000 */ 	mfc1	$t9,$f10
/*  f12326c:	3c018000 */ 	lui	$at,0x8000
/*  f123270:	10000007 */ 	b	.L0f123290
/*  f123274:	0321c825 */ 	or	$t9,$t9,$at
.L0f123278:
/*  f123278:	10000005 */ 	b	.L0f123290
/*  f12327c:	2419ffff */ 	addiu	$t9,$zero,-1
/*  f123280:	44195000 */ 	mfc1	$t9,$f10
.L0f123284:
/*  f123284:	00000000 */ 	nop
/*  f123288:	0720fffb */ 	bltz	$t9,.L0f123278
/*  f12328c:	00000000 */ 	nop
.L0f123290:
/*  f123290:	44cef800 */ 	ctc1	$t6,$31
/*  f123294:	01f9c025 */ 	or	$t8,$t7,$t9
/*  f123298:	acb80004 */ 	sw	$t8,0x4($a1)
/*  f12329c:	3c0eb200 */ 	lui	$t6,0xb200
/*  f1232a0:	ac4e0000 */ 	sw	$t6,0x0($v0)
/*  f1232a4:	c508002c */ 	lwc1	$f8,0x2c($t0)
/*  f1232a8:	c526002c */ 	lwc1	$f6,0x2c($t1)
/*  f1232ac:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1232b0:	4600410d */ 	trunc.w.s	$f4,$f8
/*  f1232b4:	02002025 */ 	or	$a0,$s0,$zero
/*  f1232b8:	3c013e80 */ 	lui	$at,0x3e80
/*  f1232bc:	4600328d */ 	trunc.w.s	$f10,$f6
/*  f1232c0:	44192000 */ 	mfc1	$t9,$f4
/*  f1232c4:	44812000 */ 	mtc1	$at,$f4
/*  f1232c8:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1232cc:	440f5000 */ 	mfc1	$t7,$f10
/*  f1232d0:	0019c400 */ 	sll	$t8,$t9,0x10
/*  f1232d4:	030fc825 */ 	or	$t9,$t8,$t7
/*  f1232d8:	ac590004 */ 	sw	$t9,0x4($v0)
/*  f1232dc:	ac870000 */ 	sw	$a3,0x0($a0)
/*  f1232e0:	c5080028 */ 	lwc1	$f8,0x28($t0)
/*  f1232e4:	afab047c */ 	sw	$t3,0x47c($sp)
/*  f1232e8:	afa90484 */ 	sw	$t1,0x484($sp)
/*  f1232ec:	46044302 */ 	mul.s	$f12,$f8,$f4
/*  f1232f0:	afa80480 */ 	sw	$t0,0x480($sp)
/*  f1232f4:	0fc54be8 */ 	jal	func0f152fa0
/*  f1232f8:	afa40180 */ 	sw	$a0,0x180($sp)
/*  f1232fc:	8fa40180 */ 	lw	$a0,0x180($sp)
/*  f123300:	02001825 */ 	or	$v1,$s0,$zero
/*  f123304:	3c0eb200 */ 	lui	$t6,0xb200
/*  f123308:	ac820004 */ 	sw	$v0,0x4($a0)
/*  f12330c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f123310:	afa3017c */ 	sw	$v1,0x17c($sp)
/*  f123314:	c7ac0384 */ 	lwc1	$f12,0x384($sp)
/*  f123318:	0fc54be8 */ 	jal	func0f152fa0
/*  f12331c:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123320:	8fa3017c */ 	lw	$v1,0x17c($sp)
/*  f123324:	02002025 */ 	or	$a0,$s0,$zero
/*  f123328:	3c18b400 */ 	lui	$t8,0xb400
/*  f12332c:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f123330:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f123334:	afa40178 */ 	sw	$a0,0x178($sp)
/*  f123338:	c7ac0410 */ 	lwc1	$f12,0x410($sp)
/*  f12333c:	0fc54be8 */ 	jal	func0f152fa0
/*  f123340:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123344:	8fa40178 */ 	lw	$a0,0x178($sp)
/*  f123348:	02001825 */ 	or	$v1,$s0,$zero
/*  f12334c:	3c0fb200 */ 	lui	$t7,0xb200
/*  f123350:	ac820004 */ 	sw	$v0,0x4($a0)
/*  f123354:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f123358:	afa30174 */ 	sw	$v1,0x174($sp)
/*  f12335c:	c7ac0394 */ 	lwc1	$f12,0x394($sp)
/*  f123360:	0fc54be8 */ 	jal	func0f152fa0
/*  f123364:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123368:	8fa30174 */ 	lw	$v1,0x174($sp)
/*  f12336c:	02002025 */ 	or	$a0,$s0,$zero
/*  f123370:	3c19b400 */ 	lui	$t9,0xb400
/*  f123374:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f123378:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f12337c:	afa40170 */ 	sw	$a0,0x170($sp)
/*  f123380:	c7ac0408 */ 	lwc1	$f12,0x408($sp)
/*  f123384:	0fc54be8 */ 	jal	func0f152fa0
/*  f123388:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12338c:	8fa40170 */ 	lw	$a0,0x170($sp)
/*  f123390:	02001825 */ 	or	$v1,$s0,$zero
/*  f123394:	3c0eb200 */ 	lui	$t6,0xb200
/*  f123398:	ac820004 */ 	sw	$v0,0x4($a0)
/*  f12339c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f1233a0:	afa3016c */ 	sw	$v1,0x16c($sp)
/*  f1233a4:	c7ac038c */ 	lwc1	$f12,0x38c($sp)
/*  f1233a8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1233ac:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1233b0:	8fa3016c */ 	lw	$v1,0x16c($sp)
/*  f1233b4:	8fa80480 */ 	lw	$t0,0x480($sp)
/*  f1233b8:	8fa90484 */ 	lw	$t1,0x484($sp)
/*  f1233bc:	8fab047c */ 	lw	$t3,0x47c($sp)
/*  f1233c0:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f1233c4:	8fb8049c */ 	lw	$t8,0x49c($sp)
/*  f1233c8:	c7a00378 */ 	lwc1	$f0,0x378($sp)
/*  f1233cc:	3c017f1b */ 	lui	$at,%hi(var7f1b50ec)
/*  f1233d0:	57000004 */ 	bnezl	$t8,.L0f1233e4
/*  f1233d4:	c526000c */ 	lwc1	$f6,0xc($t1)
/*  f1233d8:	100002f9 */ 	b	.L0f123fc0
/*  f1233dc:	02001025 */ 	or	$v0,$s0,$zero
/*  f1233e0:	c526000c */ 	lwc1	$f6,0xc($t1)
.L0f1233e4:
/*  f1233e4:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f1233e8:	e7aa036c */ 	swc1	$f10,0x36c($sp)
/*  f1233ec:	c508000c */ 	lwc1	$f8,0xc($t0)
/*  f1233f0:	c7b2036c */ 	lwc1	$f18,0x36c($sp)
/*  f1233f4:	46004102 */ 	mul.s	$f4,$f8,$f0
/*  f1233f8:	e7a40370 */ 	swc1	$f4,0x370($sp)
/*  f1233fc:	c566000c */ 	lwc1	$f6,0xc($t3)
/*  f123400:	c7a80370 */ 	lwc1	$f8,0x370($sp)
/*  f123404:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f123408:	4612403c */ 	c.lt.s	$f8,$f18
/*  f12340c:	e7aa0374 */ 	swc1	$f10,0x374($sp)
/*  f123410:	45000002 */ 	bc1f	.L0f12341c
/*  f123414:	c7a00374 */ 	lwc1	$f0,0x374($sp)
/*  f123418:	46004486 */ 	mov.s	$f18,$f8
.L0f12341c:
/*  f12341c:	4612003c */ 	c.lt.s	$f0,$f18
/*  f123420:	00000000 */ 	nop
/*  f123424:	45000002 */ 	bc1f	.L0f123430
/*  f123428:	00000000 */ 	nop
/*  f12342c:	46000486 */ 	mov.s	$f18,$f0
.L0f123430:
/*  f123430:	c42050ec */ 	lwc1	$f0,%lo(var7f1b50ec)($at)
/*  f123434:	3c013f00 */ 	lui	$at,0x3f00
/*  f123438:	44811000 */ 	mtc1	$at,$f2
/*  f12343c:	c5240034 */ 	lwc1	$f4,0x34($t1)
/*  f123440:	46029482 */ 	mul.s	$f18,$f18,$f2
/*  f123444:	00000000 */ 	nop
/*  f123448:	46122182 */ 	mul.s	$f6,$f4,$f18
/*  f12344c:	e7a6035c */ 	swc1	$f6,0x35c($sp)
/*  f123450:	c50a0034 */ 	lwc1	$f10,0x34($t0)
/*  f123454:	46125202 */ 	mul.s	$f8,$f10,$f18
/*  f123458:	c7aa035c */ 	lwc1	$f10,0x35c($sp)
/*  f12345c:	e7a80360 */ 	swc1	$f8,0x360($sp)
/*  f123460:	c5640034 */ 	lwc1	$f4,0x34($t3)
/*  f123464:	46122182 */ 	mul.s	$f6,$f4,$f18
/*  f123468:	e7a60364 */ 	swc1	$f6,0x364($sp)
/*  f12346c:	c5280020 */ 	lwc1	$f8,0x20($t1)
/*  f123470:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f123474:	e7a40338 */ 	swc1	$f4,0x338($sp)
/*  f123478:	c5260024 */ 	lwc1	$f6,0x24($t1)
/*  f12347c:	4604a03e */ 	c.le.s	$f20,$f4
/*  f123480:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f123484:	00000000 */ 	nop
/*  f123488:	46005182 */ 	mul.s	$f6,$f10,$f0
/*  f12348c:	e7a8033c */ 	swc1	$f8,0x33c($sp)
/*  f123490:	c7a80360 */ 	lwc1	$f8,0x360($sp)
/*  f123494:	e7a60340 */ 	swc1	$f6,0x340($sp)
/*  f123498:	c50a0020 */ 	lwc1	$f10,0x20($t0)
/*  f12349c:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f1234a0:	e7a60344 */ 	swc1	$f6,0x344($sp)
/*  f1234a4:	c50a0024 */ 	lwc1	$f10,0x24($t0)
/*  f1234a8:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f1234ac:	00000000 */ 	nop
/*  f1234b0:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f1234b4:	e7a60348 */ 	swc1	$f6,0x348($sp)
/*  f1234b8:	c7a60364 */ 	lwc1	$f6,0x364($sp)
/*  f1234bc:	e7aa034c */ 	swc1	$f10,0x34c($sp)
/*  f1234c0:	c5680020 */ 	lwc1	$f8,0x20($t3)
/*  f1234c4:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f1234c8:	e7aa0350 */ 	swc1	$f10,0x350($sp)
/*  f1234cc:	c5680024 */ 	lwc1	$f8,0x24($t3)
/*  f1234d0:	46083282 */ 	mul.s	$f10,$f6,$f8
/*  f1234d4:	00000000 */ 	nop
/*  f1234d8:	46003202 */ 	mul.s	$f8,$f6,$f0
/*  f1234dc:	c7a0033c */ 	lwc1	$f0,0x33c($sp)
/*  f1234e0:	e7aa0354 */ 	swc1	$f10,0x354($sp)
/*  f1234e4:	45000003 */ 	bc1f	.L0f1234f4
/*  f1234e8:	e7a80358 */ 	swc1	$f8,0x358($sp)
/*  f1234ec:	10000003 */ 	b	.L0f1234fc
/*  f1234f0:	46002386 */ 	mov.s	$f14,$f4
.L0f1234f4:
/*  f1234f4:	c7ae0338 */ 	lwc1	$f14,0x338($sp)
/*  f1234f8:	46007387 */ 	neg.s	$f14,$f14
.L0f1234fc:
/*  f1234fc:	4600a03e */ 	c.le.s	$f20,$f0
/*  f123500:	00000000 */ 	nop
/*  f123504:	45020004 */ 	bc1fl	.L0f123518
/*  f123508:	46000407 */ 	neg.s	$f16,$f0
/*  f12350c:	10000002 */ 	b	.L0f123518
/*  f123510:	46000406 */ 	mov.s	$f16,$f0
/*  f123514:	46000407 */ 	neg.s	$f16,$f0
.L0f123518:
/*  f123518:	c7a00344 */ 	lwc1	$f0,0x344($sp)
/*  f12351c:	4600a03e */ 	c.le.s	$f20,$f0
/*  f123520:	00000000 */ 	nop
/*  f123524:	45020004 */ 	bc1fl	.L0f123538
/*  f123528:	46000307 */ 	neg.s	$f12,$f0
/*  f12352c:	10000002 */ 	b	.L0f123538
/*  f123530:	46000306 */ 	mov.s	$f12,$f0
/*  f123534:	46000307 */ 	neg.s	$f12,$f0
.L0f123538:
/*  f123538:	460c703c */ 	c.lt.s	$f14,$f12
/*  f12353c:	00000000 */ 	nop
/*  f123540:	45020009 */ 	bc1fl	.L0f123568
/*  f123544:	c7a00348 */ 	lwc1	$f0,0x348($sp)
/*  f123548:	4600a03e */ 	c.le.s	$f20,$f0
/*  f12354c:	00000000 */ 	nop
/*  f123550:	45020004 */ 	bc1fl	.L0f123564
/*  f123554:	46000387 */ 	neg.s	$f14,$f0
/*  f123558:	10000002 */ 	b	.L0f123564
/*  f12355c:	46000386 */ 	mov.s	$f14,$f0
/*  f123560:	46000387 */ 	neg.s	$f14,$f0
.L0f123564:
/*  f123564:	c7a00348 */ 	lwc1	$f0,0x348($sp)
.L0f123568:
/*  f123568:	4600a03e */ 	c.le.s	$f20,$f0
/*  f12356c:	00000000 */ 	nop
/*  f123570:	45020004 */ 	bc1fl	.L0f123584
/*  f123574:	46000307 */ 	neg.s	$f12,$f0
/*  f123578:	10000002 */ 	b	.L0f123584
/*  f12357c:	46000306 */ 	mov.s	$f12,$f0
/*  f123580:	46000307 */ 	neg.s	$f12,$f0
.L0f123584:
/*  f123584:	460c803c */ 	c.lt.s	$f16,$f12
/*  f123588:	e7b20368 */ 	swc1	$f18,0x368($sp)
/*  f12358c:	4502000b */ 	bc1fl	.L0f1235bc
/*  f123590:	c7a00350 */ 	lwc1	$f0,0x350($sp)
/*  f123594:	4600a03e */ 	c.le.s	$f20,$f0
/*  f123598:	00000000 */ 	nop
/*  f12359c:	45020005 */ 	bc1fl	.L0f1235b4
/*  f1235a0:	46000407 */ 	neg.s	$f16,$f0
/*  f1235a4:	46000406 */ 	mov.s	$f16,$f0
/*  f1235a8:	10000003 */ 	b	.L0f1235b8
/*  f1235ac:	e7b20368 */ 	swc1	$f18,0x368($sp)
/*  f1235b0:	46000407 */ 	neg.s	$f16,$f0
.L0f1235b4:
/*  f1235b4:	e7b20368 */ 	swc1	$f18,0x368($sp)
.L0f1235b8:
/*  f1235b8:	c7a00350 */ 	lwc1	$f0,0x350($sp)
.L0f1235bc:
/*  f1235bc:	4600a03e */ 	c.le.s	$f20,$f0
/*  f1235c0:	00000000 */ 	nop
/*  f1235c4:	45020004 */ 	bc1fl	.L0f1235d8
/*  f1235c8:	46000307 */ 	neg.s	$f12,$f0
/*  f1235cc:	10000002 */ 	b	.L0f1235d8
/*  f1235d0:	46000306 */ 	mov.s	$f12,$f0
/*  f1235d4:	46000307 */ 	neg.s	$f12,$f0
.L0f1235d8:
/*  f1235d8:	460c703c */ 	c.lt.s	$f14,$f12
/*  f1235dc:	e7ae0330 */ 	swc1	$f14,0x330($sp)
/*  f1235e0:	4502000a */ 	bc1fl	.L0f12360c
/*  f1235e4:	c7a00354 */ 	lwc1	$f0,0x354($sp)
/*  f1235e8:	4600a03e */ 	c.le.s	$f20,$f0
/*  f1235ec:	00000000 */ 	nop
/*  f1235f0:	45020004 */ 	bc1fl	.L0f123604
/*  f1235f4:	46000387 */ 	neg.s	$f14,$f0
/*  f1235f8:	10000003 */ 	b	.L0f123608
/*  f1235fc:	e7a00330 */ 	swc1	$f0,0x330($sp)
/*  f123600:	46000387 */ 	neg.s	$f14,$f0
.L0f123604:
/*  f123604:	e7ae0330 */ 	swc1	$f14,0x330($sp)
.L0f123608:
/*  f123608:	c7a00354 */ 	lwc1	$f0,0x354($sp)
.L0f12360c:
/*  f12360c:	4600a03e */ 	c.le.s	$f20,$f0
/*  f123610:	00000000 */ 	nop
/*  f123614:	45020004 */ 	bc1fl	.L0f123628
/*  f123618:	46000307 */ 	neg.s	$f12,$f0
/*  f12361c:	10000002 */ 	b	.L0f123628
/*  f123620:	46000306 */ 	mov.s	$f12,$f0
/*  f123624:	46000307 */ 	neg.s	$f12,$f0
.L0f123628:
/*  f123628:	460c803c */ 	c.lt.s	$f16,$f12
/*  f12362c:	e7b00334 */ 	swc1	$f16,0x334($sp)
/*  f123630:	4502000a */ 	bc1fl	.L0f12365c
/*  f123634:	c52a0010 */ 	lwc1	$f10,0x10($t1)
/*  f123638:	4600a03e */ 	c.le.s	$f20,$f0
/*  f12363c:	00000000 */ 	nop
/*  f123640:	45020004 */ 	bc1fl	.L0f123654
/*  f123644:	46000407 */ 	neg.s	$f16,$f0
/*  f123648:	10000003 */ 	b	.L0f123658
/*  f12364c:	e7a00334 */ 	swc1	$f0,0x334($sp)
/*  f123650:	46000407 */ 	neg.s	$f16,$f0
.L0f123654:
/*  f123654:	e7b00334 */ 	swc1	$f16,0x334($sp)
.L0f123658:
/*  f123658:	c52a0010 */ 	lwc1	$f10,0x10($t1)
.L0f12365c:
/*  f12365c:	27a402b0 */ 	addiu	$a0,$sp,0x2b0
/*  f123660:	27a602f0 */ 	addiu	$a2,$sp,0x2f0
/*  f123664:	46025180 */ 	add.s	$f6,$f10,$f2
/*  f123668:	27a20310 */ 	addiu	$v0,$sp,0x310
/*  f12366c:	27a30290 */ 	addiu	$v1,$sp,0x290
/*  f123670:	27a502d0 */ 	addiu	$a1,$sp,0x2d0
/*  f123674:	e7a60310 */ 	swc1	$f6,0x310($sp)
/*  f123678:	c5280014 */ 	lwc1	$f8,0x14($t1)
/*  f12367c:	27a702f0 */ 	addiu	$a3,$sp,0x2f0
/*  f123680:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f123684:	e7a40314 */ 	swc1	$f4,0x314($sp)
/*  f123688:	c52a0018 */ 	lwc1	$f10,0x18($t1)
/*  f12368c:	46025180 */ 	add.s	$f6,$f10,$f2
/*  f123690:	e7a60318 */ 	swc1	$f6,0x318($sp)
/*  f123694:	c528001c */ 	lwc1	$f8,0x1c($t1)
/*  f123698:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f12369c:	e7a4031c */ 	swc1	$f4,0x31c($sp)
/*  f1236a0:	c50a0010 */ 	lwc1	$f10,0x10($t0)
/*  f1236a4:	46025180 */ 	add.s	$f6,$f10,$f2
/*  f1236a8:	e7a602f0 */ 	swc1	$f6,0x2f0($sp)
/*  f1236ac:	c5080014 */ 	lwc1	$f8,0x14($t0)
/*  f1236b0:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f1236b4:	e7a402f4 */ 	swc1	$f4,0x2f4($sp)
/*  f1236b8:	c50a0018 */ 	lwc1	$f10,0x18($t0)
/*  f1236bc:	46025180 */ 	add.s	$f6,$f10,$f2
/*  f1236c0:	e7a602f8 */ 	swc1	$f6,0x2f8($sp)
/*  f1236c4:	c508001c */ 	lwc1	$f8,0x1c($t0)
/*  f1236c8:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f1236cc:	e7a402fc */ 	swc1	$f4,0x2fc($sp)
/*  f1236d0:	c56a0010 */ 	lwc1	$f10,0x10($t3)
/*  f1236d4:	46025180 */ 	add.s	$f6,$f10,$f2
/*  f1236d8:	e7a602d0 */ 	swc1	$f6,0x2d0($sp)
/*  f1236dc:	c5680014 */ 	lwc1	$f8,0x14($t3)
/*  f1236e0:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f1236e4:	e7a402d4 */ 	swc1	$f4,0x2d4($sp)
/*  f1236e8:	c56a0018 */ 	lwc1	$f10,0x18($t3)
/*  f1236ec:	46025180 */ 	add.s	$f6,$f10,$f2
/*  f1236f0:	c7aa0338 */ 	lwc1	$f10,0x338($sp)
/*  f1236f4:	e7a602d8 */ 	swc1	$f6,0x2d8($sp)
/*  f1236f8:	c568001c */ 	lwc1	$f8,0x1c($t3)
/*  f1236fc:	e7aa0320 */ 	swc1	$f10,0x320($sp)
/*  f123700:	c7a6033c */ 	lwc1	$f6,0x33c($sp)
/*  f123704:	46024100 */ 	add.s	$f4,$f8,$f2
/*  f123708:	c7a80340 */ 	lwc1	$f8,0x340($sp)
/*  f12370c:	c7aa0348 */ 	lwc1	$f10,0x348($sp)
/*  f123710:	e7a60324 */ 	swc1	$f6,0x324($sp)
/*  f123714:	e7a402dc */ 	swc1	$f4,0x2dc($sp)
/*  f123718:	c7a40344 */ 	lwc1	$f4,0x344($sp)
/*  f12371c:	e7a80328 */ 	swc1	$f8,0x328($sp)
/*  f123720:	e7aa0304 */ 	swc1	$f10,0x304($sp)
/*  f123724:	e7a40300 */ 	swc1	$f4,0x300($sp)
/*  f123728:	c7a6034c */ 	lwc1	$f6,0x34c($sp)
/*  f12372c:	c7a40354 */ 	lwc1	$f4,0x354($sp)
/*  f123730:	c7aa0358 */ 	lwc1	$f10,0x358($sp)
/*  f123734:	c7a80350 */ 	lwc1	$f8,0x350($sp)
/*  f123738:	e7a60308 */ 	swc1	$f6,0x308($sp)
/*  f12373c:	e7a402e4 */ 	swc1	$f4,0x2e4($sp)
/*  f123740:	e7aa02e8 */ 	swc1	$f10,0x2e8($sp)
/*  f123744:	e7a802e0 */ 	swc1	$f8,0x2e0($sp)
/*  f123748:	c5260030 */ 	lwc1	$f6,0x30($t1)
/*  f12374c:	27a90230 */ 	addiu	$t1,$sp,0x230
/*  f123750:	e7a6032c */ 	swc1	$f6,0x32c($sp)
/*  f123754:	c5080030 */ 	lwc1	$f8,0x30($t0)
/*  f123758:	27a80230 */ 	addiu	$t0,$sp,0x230
/*  f12375c:	e7a8030c */ 	swc1	$f8,0x30c($sp)
/*  f123760:	c5640030 */ 	lwc1	$f4,0x30($t3)
/*  f123764:	e7a402ec */ 	swc1	$f4,0x2ec($sp)
.L0f123768:
/*  f123768:	c4400000 */ 	lwc1	$f0,0x0($v0)
/*  f12376c:	c4ca0000 */ 	lwc1	$f10,0x0($a2)
/*  f123770:	c4a80000 */ 	lwc1	$f8,0x0($a1)
/*  f123774:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f123778:	46005181 */ 	sub.s	$f6,$f10,$f0
/*  f12377c:	00a7082b */ 	sltu	$at,$a1,$a3
/*  f123780:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f123784:	46004101 */ 	sub.s	$f4,$f8,$f0
/*  f123788:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f12378c:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f123790:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f123794:	e486fffc */ 	swc1	$f6,-0x4($a0)
/*  f123798:	1420fff3 */ 	bnez	$at,.L0f123768
/*  f12379c:	e464fffc */ 	swc1	$f4,-0x4($v1)
/*  f1237a0:	27a402b0 */ 	addiu	$a0,$sp,0x2b0
/*  f1237a4:	27a20310 */ 	addiu	$v0,$sp,0x310
/*  f1237a8:	27a30290 */ 	addiu	$v1,$sp,0x290
/*  f1237ac:	27a70250 */ 	addiu	$a3,$sp,0x250
/*  f1237b0:	27a50270 */ 	addiu	$a1,$sp,0x270
/*  f1237b4:	27a60210 */ 	addiu	$a2,$sp,0x210
/*  f1237b8:	c7b203c8 */ 	lwc1	$f18,0x3c8($sp)
.L0f1237bc:
/*  f1237bc:	c4600000 */ 	lwc1	$f0,0x0($v1)
/*  f1237c0:	c7aa03cc */ 	lwc1	$f10,0x3cc($sp)
/*  f1237c4:	c4820000 */ 	lwc1	$f2,0x0($a0)
/*  f1237c8:	c7a803d4 */ 	lwc1	$f8,0x3d4($sp)
/*  f1237cc:	460a0182 */ 	mul.s	$f6,$f0,$f10
/*  f1237d0:	3c013780 */ 	lui	$at,0x3780
/*  f1237d4:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f1237d8:	46024102 */ 	mul.s	$f4,$f8,$f2
/*  f1237dc:	44814000 */ 	mtc1	$at,$f8
/*  f1237e0:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f1237e4:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f1237e8:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f1237ec:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f1237f0:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f1237f4:	46043281 */ 	sub.s	$f10,$f6,$f4
/*  f1237f8:	25080004 */ 	addiu	$t0,$t0,0x4
/*  f1237fc:	46085302 */ 	mul.s	$f12,$f10,$f8
/*  f123800:	e4ecfffc */ 	swc1	$f12,-0x4($a3)
/*  f123804:	c7a603d0 */ 	lwc1	$f6,0x3d0($sp)
/*  f123808:	46061102 */ 	mul.s	$f4,$f2,$f6
/*  f12380c:	44813000 */ 	mtc1	$at,$f6
/*  f123810:	00c9082b */ 	sltu	$at,$a2,$t1
/*  f123814:	46009282 */ 	mul.s	$f10,$f18,$f0
/*  f123818:	460a2201 */ 	sub.s	$f8,$f4,$f10
/*  f12381c:	46064102 */ 	mul.s	$f4,$f8,$f6
/*  f123820:	e4a4fffc */ 	swc1	$f4,-0x4($a1)
/*  f123824:	c7aa0440 */ 	lwc1	$f10,0x440($sp)
/*  f123828:	c4a6fffc */ 	lwc1	$f6,-0x4($a1)
/*  f12382c:	460a6202 */ 	mul.s	$f8,$f12,$f10
/*  f123830:	e468fffc */ 	swc1	$f8,-0x4($v1)
/*  f123834:	c7a40440 */ 	lwc1	$f4,0x440($sp)
/*  f123838:	c468fffc */ 	lwc1	$f8,-0x4($v1)
/*  f12383c:	46043382 */ 	mul.s	$f14,$f6,$f4
/*  f123840:	c444fffc */ 	lwc1	$f4,-0x4($v0)
/*  f123844:	e48efffc */ 	swc1	$f14,-0x4($a0)
/*  f123848:	c7aa0394 */ 	lwc1	$f10,0x394($sp)
/*  f12384c:	46085182 */ 	mul.s	$f6,$f10,$f8
/*  f123850:	460e3400 */ 	add.s	$f16,$f6,$f14
/*  f123854:	e510fffc */ 	swc1	$f16,-0x4($t0)
/*  f123858:	c7aa037c */ 	lwc1	$f10,0x37c($sp)
/*  f12385c:	460a8202 */ 	mul.s	$f8,$f16,$f10
/*  f123860:	46082181 */ 	sub.s	$f6,$f4,$f8
/*  f123864:	1420ffd5 */ 	bnez	$at,.L0f1237bc
/*  f123868:	e4c6fffc */ 	swc1	$f6,-0x4($a2)
/*  f12386c:	0fc54be8 */ 	jal	func0f152fa0
/*  f123870:	c7ac0210 */ 	lwc1	$f12,0x210($sp)
/*  f123874:	afa20168 */ 	sw	$v0,0x168($sp)
/*  f123878:	0fc54be8 */ 	jal	func0f152fa0
/*  f12387c:	c7ac0214 */ 	lwc1	$f12,0x214($sp)
/*  f123880:	afa20164 */ 	sw	$v0,0x164($sp)
/*  f123884:	0fc54be8 */ 	jal	func0f152fa0
/*  f123888:	c7ac0218 */ 	lwc1	$f12,0x218($sp)
/*  f12388c:	afa20160 */ 	sw	$v0,0x160($sp)
/*  f123890:	0fc54be8 */ 	jal	func0f152fa0
/*  f123894:	c7ac021c */ 	lwc1	$f12,0x21c($sp)
/*  f123898:	afa2015c */ 	sw	$v0,0x15c($sp)
/*  f12389c:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238a0:	c7ac0290 */ 	lwc1	$f12,0x290($sp)
/*  f1238a4:	afa20158 */ 	sw	$v0,0x158($sp)
/*  f1238a8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238ac:	c7ac0294 */ 	lwc1	$f12,0x294($sp)
/*  f1238b0:	afa20154 */ 	sw	$v0,0x154($sp)
/*  f1238b4:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238b8:	c7ac0298 */ 	lwc1	$f12,0x298($sp)
/*  f1238bc:	afa20150 */ 	sw	$v0,0x150($sp)
/*  f1238c0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238c4:	c7ac029c */ 	lwc1	$f12,0x29c($sp)
/*  f1238c8:	afa2014c */ 	sw	$v0,0x14c($sp)
/*  f1238cc:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238d0:	c7ac02b0 */ 	lwc1	$f12,0x2b0($sp)
/*  f1238d4:	afa20138 */ 	sw	$v0,0x138($sp)
/*  f1238d8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238dc:	c7ac02b4 */ 	lwc1	$f12,0x2b4($sp)
/*  f1238e0:	afa20134 */ 	sw	$v0,0x134($sp)
/*  f1238e4:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238e8:	c7ac02b8 */ 	lwc1	$f12,0x2b8($sp)
/*  f1238ec:	afa20130 */ 	sw	$v0,0x130($sp)
/*  f1238f0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1238f4:	c7ac02bc */ 	lwc1	$f12,0x2bc($sp)
/*  f1238f8:	afa2012c */ 	sw	$v0,0x12c($sp)
/*  f1238fc:	0fc54be8 */ 	jal	func0f152fa0
/*  f123900:	c7ac0230 */ 	lwc1	$f12,0x230($sp)
/*  f123904:	afa20148 */ 	sw	$v0,0x148($sp)
/*  f123908:	0fc54be8 */ 	jal	func0f152fa0
/*  f12390c:	c7ac0234 */ 	lwc1	$f12,0x234($sp)
/*  f123910:	afa20144 */ 	sw	$v0,0x144($sp)
/*  f123914:	0fc54be8 */ 	jal	func0f152fa0
/*  f123918:	c7ac0238 */ 	lwc1	$f12,0x238($sp)
/*  f12391c:	c7ac023c */ 	lwc1	$f12,0x23c($sp)
/*  f123920:	0fc54be8 */ 	jal	func0f152fa0
/*  f123924:	afa20140 */ 	sw	$v0,0x140($sp)
/*  f123928:	8fac0140 */ 	lw	$t4,0x140($sp)
/*  f12392c:	8fad015c */ 	lw	$t5,0x15c($sp)
/*  f123930:	8fbf0168 */ 	lw	$ra,0x168($sp)
/*  f123934:	3c08b400 */ 	lui	$t0,0xb400
/*  f123938:	02001825 */ 	or	$v1,$s0,$zero
/*  f12393c:	ac680000 */ 	sw	$t0,0x0($v1)
/*  f123940:	8fb90164 */ 	lw	$t9,0x164($sp)
/*  f123944:	3c09ffff */ 	lui	$t1,0xffff
/*  f123948:	03e97824 */ 	and	$t7,$ra,$t1
/*  f12394c:	03297024 */ 	and	$t6,$t9,$t1
/*  f123950:	000ec402 */ 	srl	$t8,$t6,0x10
/*  f123954:	01f8c825 */ 	or	$t9,$t7,$t8
/*  f123958:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12395c:	3c0ab200 */ 	lui	$t2,0xb200
/*  f123960:	ac790004 */ 	sw	$t9,0x4($v1)
/*  f123964:	02002025 */ 	or	$a0,$s0,$zero
/*  f123968:	ac8a0000 */ 	sw	$t2,0x0($a0)
/*  f12396c:	8fae0160 */ 	lw	$t6,0x160($sp)
/*  f123970:	01a9c024 */ 	and	$t8,$t5,$t1
/*  f123974:	0018cc02 */ 	srl	$t9,$t8,0x10
/*  f123978:	01c97824 */ 	and	$t7,$t6,$t1
/*  f12397c:	01f97025 */ 	or	$t6,$t7,$t9
/*  f123980:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123984:	ac8e0004 */ 	sw	$t6,0x4($a0)
/*  f123988:	02002825 */ 	or	$a1,$s0,$zero
/*  f12398c:	aca80000 */ 	sw	$t0,0x0($a1)
/*  f123990:	8fb90154 */ 	lw	$t9,0x154($sp)
/*  f123994:	8fb80158 */ 	lw	$t8,0x158($sp)
/*  f123998:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12399c:	03297024 */ 	and	$t6,$t9,$t1
/*  f1239a0:	03097824 */ 	and	$t7,$t8,$t1
/*  f1239a4:	000ec402 */ 	srl	$t8,$t6,0x10
/*  f1239a8:	01f8c825 */ 	or	$t9,$t7,$t8
/*  f1239ac:	acb90004 */ 	sw	$t9,0x4($a1)
/*  f1239b0:	8fab014c */ 	lw	$t3,0x14c($sp)
/*  f1239b4:	02003025 */ 	or	$a2,$s0,$zero
/*  f1239b8:	acca0000 */ 	sw	$t2,0x0($a2)
/*  f1239bc:	8fae0150 */ 	lw	$t6,0x150($sp)
/*  f1239c0:	0169c024 */ 	and	$t8,$t3,$t1
/*  f1239c4:	0018cc02 */ 	srl	$t9,$t8,0x10
/*  f1239c8:	01c97824 */ 	and	$t7,$t6,$t1
/*  f1239cc:	01f97025 */ 	or	$t6,$t7,$t9
/*  f1239d0:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1239d4:	acce0004 */ 	sw	$t6,0x4($a2)
/*  f1239d8:	02001825 */ 	or	$v1,$s0,$zero
/*  f1239dc:	ac680000 */ 	sw	$t0,0x0($v1)
/*  f1239e0:	8fb90164 */ 	lw	$t9,0x164($sp)
/*  f1239e4:	001f7c00 */ 	sll	$t7,$ra,0x10
/*  f1239e8:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1239ec:	332effff */ 	andi	$t6,$t9,0xffff
/*  f1239f0:	01eec025 */ 	or	$t8,$t7,$t6
/*  f1239f4:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f1239f8:	02002025 */ 	or	$a0,$s0,$zero
/*  f1239fc:	ac8a0000 */ 	sw	$t2,0x0($a0)
/*  f123a00:	8faf0160 */ 	lw	$t7,0x160($sp)
/*  f123a04:	31b8ffff */ 	andi	$t8,$t5,0xffff
/*  f123a08:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123a0c:	000f7400 */ 	sll	$t6,$t7,0x10
/*  f123a10:	01d8c825 */ 	or	$t9,$t6,$t8
/*  f123a14:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f123a18:	02003825 */ 	or	$a3,$s0,$zero
/*  f123a1c:	ace80000 */ 	sw	$t0,0x0($a3)
/*  f123a20:	8fb90154 */ 	lw	$t9,0x154($sp)
/*  f123a24:	8fae0158 */ 	lw	$t6,0x158($sp)
/*  f123a28:	8fa80148 */ 	lw	$t0,0x148($sp)
/*  f123a2c:	332fffff */ 	andi	$t7,$t9,0xffff
/*  f123a30:	000ec400 */ 	sll	$t8,$t6,0x10
/*  f123a34:	8fa60144 */ 	lw	$a2,0x144($sp)
/*  f123a38:	030f7025 */ 	or	$t6,$t8,$t7
/*  f123a3c:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123a40:	acee0004 */ 	sw	$t6,0x4($a3)
/*  f123a44:	02001825 */ 	or	$v1,$s0,$zero
/*  f123a48:	ac6a0000 */ 	sw	$t2,0x0($v1)
/*  f123a4c:	8fb80150 */ 	lw	$t8,0x150($sp)
/*  f123a50:	316effff */ 	andi	$t6,$t3,0xffff
/*  f123a54:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123a58:	00187c00 */ 	sll	$t7,$t8,0x10
/*  f123a5c:	01eec825 */ 	or	$t9,$t7,$t6
/*  f123a60:	ac790004 */ 	sw	$t9,0x4($v1)
/*  f123a64:	3c18b400 */ 	lui	$t8,0xb400
/*  f123a68:	02002025 */ 	or	$a0,$s0,$zero
/*  f123a6c:	00c97024 */ 	and	$t6,$a2,$t1
/*  f123a70:	000ecc02 */ 	srl	$t9,$t6,0x10
/*  f123a74:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f123a78:	01097824 */ 	and	$t7,$t0,$t1
/*  f123a7c:	01f9c025 */ 	or	$t8,$t7,$t9
/*  f123a80:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123a84:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f123a88:	02002825 */ 	or	$a1,$s0,$zero
/*  f123a8c:	00497824 */ 	and	$t7,$v0,$t1
/*  f123a90:	000fcc02 */ 	srl	$t9,$t7,0x10
/*  f123a94:	01897024 */ 	and	$t6,$t4,$t1
/*  f123a98:	01d9c025 */ 	or	$t8,$t6,$t9
/*  f123a9c:	acb80004 */ 	sw	$t8,0x4($a1)
/*  f123aa0:	acaa0000 */ 	sw	$t2,0x0($a1)
/*  f123aa4:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123aa8:	8fad0130 */ 	lw	$t5,0x130($sp)
/*  f123aac:	3c07b400 */ 	lui	$a3,0xb400
/*  f123ab0:	02001825 */ 	or	$v1,$s0,$zero
/*  f123ab4:	ac670000 */ 	sw	$a3,0x0($v1)
/*  f123ab8:	8fb90134 */ 	lw	$t9,0x134($sp)
/*  f123abc:	8faf0138 */ 	lw	$t7,0x138($sp)
/*  f123ac0:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123ac4:	0329c024 */ 	and	$t8,$t9,$t1
/*  f123ac8:	01e97024 */ 	and	$t6,$t7,$t1
/*  f123acc:	00187c02 */ 	srl	$t7,$t8,0x10
/*  f123ad0:	01cfc825 */ 	or	$t9,$t6,$t7
/*  f123ad4:	ac790004 */ 	sw	$t9,0x4($v1)
/*  f123ad8:	3c18b200 */ 	lui	$t8,0xb200
/*  f123adc:	02002025 */ 	or	$a0,$s0,$zero
/*  f123ae0:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f123ae4:	8faf012c */ 	lw	$t7,0x12c($sp)
/*  f123ae8:	01a97024 */ 	and	$t6,$t5,$t1
/*  f123aec:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123af0:	01e9c824 */ 	and	$t9,$t7,$t1
/*  f123af4:	0019c402 */ 	srl	$t8,$t9,0x10
/*  f123af8:	01d87825 */ 	or	$t7,$t6,$t8
/*  f123afc:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*  f123b00:	02002825 */ 	or	$a1,$s0,$zero
/*  f123b04:	00087400 */ 	sll	$t6,$t0,0x10
/*  f123b08:	30d8ffff */ 	andi	$t8,$a2,0xffff
/*  f123b0c:	01d87825 */ 	or	$t7,$t6,$t8
/*  f123b10:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123b14:	acaf0004 */ 	sw	$t7,0x4($a1)
/*  f123b18:	aca70000 */ 	sw	$a3,0x0($a1)
/*  f123b1c:	02005825 */ 	or	$t3,$s0,$zero
/*  f123b20:	3058ffff */ 	andi	$t8,$v0,0xffff
/*  f123b24:	000c7400 */ 	sll	$t6,$t4,0x10
/*  f123b28:	01d87825 */ 	or	$t7,$t6,$t8
/*  f123b2c:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123b30:	3c1fb200 */ 	lui	$ra,0xb200
/*  f123b34:	ad7f0000 */ 	sw	$ra,0x0($t3)
/*  f123b38:	ad6f0004 */ 	sw	$t7,0x4($t3)
/*  f123b3c:	02003825 */ 	or	$a3,$s0,$zero
/*  f123b40:	3c19b400 */ 	lui	$t9,0xb400
/*  f123b44:	acf90000 */ 	sw	$t9,0x0($a3)
/*  f123b48:	8fb90134 */ 	lw	$t9,0x134($sp)
/*  f123b4c:	8fb80138 */ 	lw	$t8,0x138($sp)
/*  f123b50:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123b54:	332effff */ 	andi	$t6,$t9,0xffff
/*  f123b58:	00187c00 */ 	sll	$t7,$t8,0x10
/*  f123b5c:	01eec025 */ 	or	$t8,$t7,$t6
/*  f123b60:	acf80004 */ 	sw	$t8,0x4($a3)
/*  f123b64:	02004025 */ 	or	$t0,$s0,$zero
/*  f123b68:	ad1f0000 */ 	sw	$ra,0x0($t0)
/*  f123b6c:	8fae012c */ 	lw	$t6,0x12c($sp)
/*  f123b70:	000d7c00 */ 	sll	$t7,$t5,0x10
/*  f123b74:	3c013d00 */ 	lui	$at,0x3d00
/*  f123b78:	31d8ffff */ 	andi	$t8,$t6,0xffff
/*  f123b7c:	01f8c825 */ 	or	$t9,$t7,$t8
/*  f123b80:	ad190004 */ 	sw	$t9,0x4($t0)
/*  f123b84:	44817000 */ 	mtc1	$at,$f14
/*  f123b88:	c7aa0330 */ 	lwc1	$f10,0x330($sp)
/*  f123b8c:	c7a80334 */ 	lwc1	$f8,0x334($sp)
/*  f123b90:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f123b94:	460e5102 */ 	mul.s	$f4,$f10,$f14
/*  f123b98:	c7aa0368 */ 	lwc1	$f10,0x368($sp)
/*  f123b9c:	27a201d0 */ 	addiu	$v0,$sp,0x1d0
/*  f123ba0:	460e4182 */ 	mul.s	$f6,$f8,$f14
/*  f123ba4:	27a501b0 */ 	addiu	$a1,$sp,0x1b0
/*  f123ba8:	27a601d0 */ 	addiu	$a2,$sp,0x1d0
/*  f123bac:	27a402b0 */ 	addiu	$a0,$sp,0x2b0
/*  f123bb0:	e7a40200 */ 	swc1	$f4,0x200($sp)
/*  f123bb4:	460e5102 */ 	mul.s	$f4,$f10,$f14
/*  f123bb8:	27a30290 */ 	addiu	$v1,$sp,0x290
/*  f123bbc:	e7a60204 */ 	swc1	$f6,0x204($sp)
/*  f123bc0:	3c013f80 */ 	lui	$at,0x3f80
/*  f123bc4:	e7a40208 */ 	swc1	$f4,0x208($sp)
.L0f123bc8:
/*  f123bc8:	c4600000 */ 	lwc1	$f0,0x0($v1)
/*  f123bcc:	4600a03e */ 	c.le.s	$f20,$f0
/*  f123bd0:	00000000 */ 	nop
/*  f123bd4:	45020004 */ 	bc1fl	.L0f123be8
/*  f123bd8:	46000307 */ 	neg.s	$f12,$f0
/*  f123bdc:	10000002 */ 	b	.L0f123be8
/*  f123be0:	46000306 */ 	mov.s	$f12,$f0
/*  f123be4:	46000307 */ 	neg.s	$f12,$f0
.L0f123be8:
/*  f123be8:	c4820000 */ 	lwc1	$f2,0x0($a0)
/*  f123bec:	460e6202 */ 	mul.s	$f8,$f12,$f14
/*  f123bf0:	4602a03e */ 	c.le.s	$f20,$f2
/*  f123bf4:	00000000 */ 	nop
/*  f123bf8:	45000003 */ 	bc1f	.L0f123c08
/*  f123bfc:	e4c80000 */ 	swc1	$f8,0x0($a2)
/*  f123c00:	10000002 */ 	b	.L0f123c0c
/*  f123c04:	46001306 */ 	mov.s	$f12,$f2
.L0f123c08:
/*  f123c08:	46001307 */ 	neg.s	$f12,$f2
.L0f123c0c:
/*  f123c0c:	460e6182 */ 	mul.s	$f6,$f12,$f14
/*  f123c10:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f123c14:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f123c18:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f123c1c:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f123c20:	14a2ffe9 */ 	bne	$a1,$v0,.L0f123bc8
/*  f123c24:	e4a6fffc */ 	swc1	$f6,-0x4($a1)
/*  f123c28:	c7a201e0 */ 	lwc1	$f2,0x1e0($sp)
/*  f123c2c:	c7aa0200 */ 	lwc1	$f10,0x200($sp)
/*  f123c30:	c7ac01e4 */ 	lwc1	$f12,0x1e4($sp)
/*  f123c34:	46021100 */ 	add.s	$f4,$f2,$f2
/*  f123c38:	c7a601c0 */ 	lwc1	$f6,0x1c0($sp)
/*  f123c3c:	c7ae01e8 */ 	lwc1	$f14,0x1e8($sp)
/*  f123c40:	44811000 */ 	mtc1	$at,$f2
/*  f123c44:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f123c48:	c7aa0204 */ 	lwc1	$f10,0x204($sp)
/*  f123c4c:	3c013a80 */ 	lui	$at,0x3a80
/*  f123c50:	460c6100 */ 	add.s	$f4,$f12,$f12
/*  f123c54:	46083000 */ 	add.s	$f0,$f6,$f8
/*  f123c58:	c7a801c4 */ 	lwc1	$f8,0x1c4($sp)
/*  f123c5c:	46045180 */ 	add.s	$f6,$f10,$f4
/*  f123c60:	c7aa0208 */ 	lwc1	$f10,0x208($sp)
/*  f123c64:	460e7100 */ 	add.s	$f4,$f14,$f14
/*  f123c68:	46064400 */ 	add.s	$f16,$f8,$f6
/*  f123c6c:	c7a601c8 */ 	lwc1	$f6,0x1c8($sp)
/*  f123c70:	46045200 */ 	add.s	$f8,$f10,$f4
/*  f123c74:	44815000 */ 	mtc1	$at,$f10
/*  f123c78:	e7b001a4 */ 	swc1	$f16,0x1a4($sp)
/*  f123c7c:	4610003c */ 	c.lt.s	$f0,$f16
/*  f123c80:	46083480 */ 	add.s	$f18,$f6,$f8
/*  f123c84:	45020004 */ 	bc1fl	.L0f123c98
/*  f123c88:	4612003c */ 	c.lt.s	$f0,$f18
/*  f123c8c:	46008006 */ 	mov.s	$f0,$f16
/*  f123c90:	e7b001a4 */ 	swc1	$f16,0x1a4($sp)
/*  f123c94:	4612003c */ 	c.lt.s	$f0,$f18
.L0f123c98:
/*  f123c98:	e7b201a8 */ 	swc1	$f18,0x1a8($sp)
/*  f123c9c:	45000003 */ 	bc1f	.L0f123cac
/*  f123ca0:	00000000 */ 	nop
/*  f123ca4:	46009006 */ 	mov.s	$f0,$f18
/*  f123ca8:	e7b201a8 */ 	swc1	$f18,0x1a8($sp)
.L0f123cac:
/*  f123cac:	460a0002 */ 	mul.s	$f0,$f0,$f10
/*  f123cb0:	4600103c */ 	c.lt.s	$f2,$f0
/*  f123cb4:	00000000 */ 	nop
/*  f123cb8:	45020005 */ 	bc1fl	.L0f123cd0
/*  f123cbc:	e7a001a0 */ 	swc1	$f0,0x1a0($sp)
/*  f123cc0:	46001503 */ 	div.s	$f20,$f2,$f0
/*  f123cc4:	10000003 */ 	b	.L0f123cd4
/*  f123cc8:	e7a001a0 */ 	swc1	$f0,0x1a0($sp)
/*  f123ccc:	e7a001a0 */ 	swc1	$f0,0x1a0($sp)
.L0f123cd0:
/*  f123cd0:	46001506 */ 	mov.s	$f20,$f2
.L0f123cd4:
/*  f123cd4:	c7a40220 */ 	lwc1	$f4,0x220($sp)
/*  f123cd8:	e7b40190 */ 	swc1	$f20,0x190($sp)
/*  f123cdc:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f123ce0:	0fc54be8 */ 	jal	func0f152fa0
/*  f123ce4:	00000000 */ 	nop
/*  f123ce8:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123cec:	c7a60224 */ 	lwc1	$f6,0x224($sp)
/*  f123cf0:	afa200e8 */ 	sw	$v0,0xe8($sp)
/*  f123cf4:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f123cf8:	0fc54be8 */ 	jal	func0f152fa0
/*  f123cfc:	00000000 */ 	nop
/*  f123d00:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d04:	c7a80228 */ 	lwc1	$f8,0x228($sp)
/*  f123d08:	afa200e4 */ 	sw	$v0,0xe4($sp)
/*  f123d0c:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f123d10:	0fc54be8 */ 	jal	func0f152fa0
/*  f123d14:	00000000 */ 	nop
/*  f123d18:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d1c:	c7aa02a0 */ 	lwc1	$f10,0x2a0($sp)
/*  f123d20:	afa200e0 */ 	sw	$v0,0xe0($sp)
/*  f123d24:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f123d28:	0fc54be8 */ 	jal	func0f152fa0
/*  f123d2c:	00000000 */ 	nop
/*  f123d30:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d34:	c7a402a4 */ 	lwc1	$f4,0x2a4($sp)
/*  f123d38:	afa200d8 */ 	sw	$v0,0xd8($sp)
/*  f123d3c:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f123d40:	0fc54be8 */ 	jal	func0f152fa0
/*  f123d44:	00000000 */ 	nop
/*  f123d48:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d4c:	c7a602a8 */ 	lwc1	$f6,0x2a8($sp)
/*  f123d50:	afa200d4 */ 	sw	$v0,0xd4($sp)
/*  f123d54:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f123d58:	0fc54be8 */ 	jal	func0f152fa0
/*  f123d5c:	00000000 */ 	nop
/*  f123d60:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d64:	c7a802c0 */ 	lwc1	$f8,0x2c0($sp)
/*  f123d68:	afa200d0 */ 	sw	$v0,0xd0($sp)
/*  f123d6c:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f123d70:	0fc54be8 */ 	jal	func0f152fa0
/*  f123d74:	00000000 */ 	nop
/*  f123d78:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d7c:	c7aa02c4 */ 	lwc1	$f10,0x2c4($sp)
/*  f123d80:	afa200b8 */ 	sw	$v0,0xb8($sp)
/*  f123d84:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f123d88:	0fc54be8 */ 	jal	func0f152fa0
/*  f123d8c:	00000000 */ 	nop
/*  f123d90:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123d94:	c7a402c8 */ 	lwc1	$f4,0x2c8($sp)
/*  f123d98:	afa200b4 */ 	sw	$v0,0xb4($sp)
/*  f123d9c:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f123da0:	0fc54be8 */ 	jal	func0f152fa0
/*  f123da4:	00000000 */ 	nop
/*  f123da8:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123dac:	c7a60240 */ 	lwc1	$f6,0x240($sp)
/*  f123db0:	afa200b0 */ 	sw	$v0,0xb0($sp)
/*  f123db4:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f123db8:	0fc54be8 */ 	jal	func0f152fa0
/*  f123dbc:	00000000 */ 	nop
/*  f123dc0:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123dc4:	c7a80244 */ 	lwc1	$f8,0x244($sp)
/*  f123dc8:	afa200c8 */ 	sw	$v0,0xc8($sp)
/*  f123dcc:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f123dd0:	0fc54be8 */ 	jal	func0f152fa0
/*  f123dd4:	00000000 */ 	nop
/*  f123dd8:	c7b40190 */ 	lwc1	$f20,0x190($sp)
/*  f123ddc:	c7aa0248 */ 	lwc1	$f10,0x248($sp)
/*  f123de0:	afa200c4 */ 	sw	$v0,0xc4($sp)
/*  f123de4:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f123de8:	0fc54be8 */ 	jal	func0f152fa0
/*  f123dec:	00000000 */ 	nop
/*  f123df0:	8fad00e4 */ 	lw	$t5,0xe4($sp)
/*  f123df4:	8fac00e8 */ 	lw	$t4,0xe8($sp)
/*  f123df8:	3c09ffff */ 	lui	$t1,0xffff
/*  f123dfc:	8fa600c4 */ 	lw	$a2,0xc4($sp)
/*  f123e00:	8fbf00e0 */ 	lw	$ra,0xe0($sp)
/*  f123e04:	3c0eb400 */ 	lui	$t6,0xb400
/*  f123e08:	01a9c024 */ 	and	$t8,$t5,$t1
/*  f123e0c:	0018cc02 */ 	srl	$t9,$t8,0x10
/*  f123e10:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f123e14:	01897824 */ 	and	$t7,$t4,$t1
/*  f123e18:	01f97025 */ 	or	$t6,$t7,$t9
/*  f123e1c:	26040008 */ 	addiu	$a0,$s0,0x8
/*  f123e20:	ae0e0004 */ 	sw	$t6,0x4($s0)
/*  f123e24:	3c18b200 */ 	lui	$t8,0xb200
/*  f123e28:	03e97824 */ 	and	$t7,$ra,$t1
/*  f123e2c:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*  f123e30:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f123e34:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f123e38:	3c19b400 */ 	lui	$t9,0xb400
/*  f123e3c:	acb90000 */ 	sw	$t9,0x0($a1)
/*  f123e40:	8faf00d4 */ 	lw	$t7,0xd4($sp)
/*  f123e44:	8fae00d8 */ 	lw	$t6,0xd8($sp)
/*  f123e48:	24a70008 */ 	addiu	$a3,$a1,0x8
/*  f123e4c:	01e9c824 */ 	and	$t9,$t7,$t1
/*  f123e50:	01c9c024 */ 	and	$t8,$t6,$t1
/*  f123e54:	00197402 */ 	srl	$t6,$t9,0x10
/*  f123e58:	030e7825 */ 	or	$t7,$t8,$t6
/*  f123e5c:	acaf0004 */ 	sw	$t7,0x4($a1)
/*  f123e60:	8fab00d0 */ 	lw	$t3,0xd0($sp)
/*  f123e64:	3c19b200 */ 	lui	$t9,0xb200
/*  f123e68:	acf90000 */ 	sw	$t9,0x0($a3)
/*  f123e6c:	0169c024 */ 	and	$t8,$t3,$t1
/*  f123e70:	acf80004 */ 	sw	$t8,0x4($a3)
/*  f123e74:	24e30008 */ 	addiu	$v1,$a3,0x8
/*  f123e78:	3c0eb400 */ 	lui	$t6,0xb400
/*  f123e7c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f123e80:	31b8ffff */ 	andi	$t8,$t5,0xffff
/*  f123e84:	000ccc00 */ 	sll	$t9,$t4,0x10
/*  f123e88:	03387025 */ 	or	$t6,$t9,$t8
/*  f123e8c:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f123e90:	24700008 */ 	addiu	$s0,$v1,0x8
/*  f123e94:	3c0fb200 */ 	lui	$t7,0xb200
/*  f123e98:	001fc400 */ 	sll	$t8,$ra,0x10
/*  f123e9c:	ae180004 */ 	sw	$t8,0x4($s0)
/*  f123ea0:	ae0f0000 */ 	sw	$t7,0x0($s0)
/*  f123ea4:	26080008 */ 	addiu	$t0,$s0,0x8
/*  f123ea8:	3c0eb400 */ 	lui	$t6,0xb400
/*  f123eac:	ad0e0000 */ 	sw	$t6,0x0($t0)
/*  f123eb0:	8fae00d4 */ 	lw	$t6,0xd4($sp)
/*  f123eb4:	8fb900d8 */ 	lw	$t9,0xd8($sp)
/*  f123eb8:	8fa700c8 */ 	lw	$a3,0xc8($sp)
/*  f123ebc:	31cfffff */ 	andi	$t7,$t6,0xffff
/*  f123ec0:	0019c400 */ 	sll	$t8,$t9,0x10
/*  f123ec4:	030fc825 */ 	or	$t9,$t8,$t7
/*  f123ec8:	ad190004 */ 	sw	$t9,0x4($t0)
/*  f123ecc:	25030008 */ 	addiu	$v1,$t0,0x8
/*  f123ed0:	3c0eb200 */ 	lui	$t6,0xb200
/*  f123ed4:	000b7c00 */ 	sll	$t7,$t3,0x10
/*  f123ed8:	ac6f0004 */ 	sw	$t7,0x4($v1)
/*  f123edc:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f123ee0:	24640008 */ 	addiu	$a0,$v1,0x8
/*  f123ee4:	3c19b400 */ 	lui	$t9,0xb400
/*  f123ee8:	00c9c024 */ 	and	$t8,$a2,$t1
/*  f123eec:	00187c02 */ 	srl	$t7,$t8,0x10
/*  f123ef0:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f123ef4:	00e97024 */ 	and	$t6,$a3,$t1
/*  f123ef8:	01cfc825 */ 	or	$t9,$t6,$t7
/*  f123efc:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f123f00:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f123f04:	00497024 */ 	and	$t6,$v0,$t1
/*  f123f08:	3c18b200 */ 	lui	$t8,0xb200
/*  f123f0c:	acb80000 */ 	sw	$t8,0x0($a1)
/*  f123f10:	acae0004 */ 	sw	$t6,0x4($a1)
/*  f123f14:	8fa800b4 */ 	lw	$t0,0xb4($sp)
/*  f123f18:	8fac00b8 */ 	lw	$t4,0xb8($sp)
/*  f123f1c:	00405025 */ 	or	$t2,$v0,$zero
/*  f123f20:	24b00008 */ 	addiu	$s0,$a1,0x8
/*  f123f24:	8fab00b0 */ 	lw	$t3,0xb0($sp)
/*  f123f28:	02001025 */ 	or	$v0,$s0,$zero
/*  f123f2c:	3c0fb400 */ 	lui	$t7,0xb400
/*  f123f30:	0109c024 */ 	and	$t8,$t0,$t1
/*  f123f34:	00187402 */ 	srl	$t6,$t8,0x10
/*  f123f38:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f123f3c:	0189c824 */ 	and	$t9,$t4,$t1
/*  f123f40:	032e7825 */ 	or	$t7,$t9,$t6
/*  f123f44:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f123f48:	26030008 */ 	addiu	$v1,$s0,0x8
/*  f123f4c:	3c18b200 */ 	lui	$t8,0xb200
/*  f123f50:	0169c824 */ 	and	$t9,$t3,$t1
/*  f123f54:	ac790004 */ 	sw	$t9,0x4($v1)
/*  f123f58:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f123f5c:	24700008 */ 	addiu	$s0,$v1,0x8
/*  f123f60:	3c0eb400 */ 	lui	$t6,0xb400
/*  f123f64:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f123f68:	30d9ffff */ 	andi	$t9,$a2,0xffff
/*  f123f6c:	0007c400 */ 	sll	$t8,$a3,0x10
/*  f123f70:	03197025 */ 	or	$t6,$t8,$t9
/*  f123f74:	ae0e0004 */ 	sw	$t6,0x4($s0)
/*  f123f78:	26050008 */ 	addiu	$a1,$s0,0x8
/*  f123f7c:	000acc00 */ 	sll	$t9,$t2,0x10
/*  f123f80:	acb90004 */ 	sw	$t9,0x4($a1)
/*  f123f84:	3c0fb200 */ 	lui	$t7,0xb200
/*  f123f88:	acaf0000 */ 	sw	$t7,0x0($a1)
/*  f123f8c:	24a30008 */ 	addiu	$v1,$a1,0x8
/*  f123f90:	3c0eb400 */ 	lui	$t6,0xb400
/*  f123f94:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f123f98:	3119ffff */ 	andi	$t9,$t0,0xffff
/*  f123f9c:	000cc400 */ 	sll	$t8,$t4,0x10
/*  f123fa0:	03197025 */ 	or	$t6,$t8,$t9
/*  f123fa4:	24640008 */ 	addiu	$a0,$v1,0x8
/*  f123fa8:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f123fac:	3c0fb300 */ 	lui	$t7,0xb300
/*  f123fb0:	000bcc00 */ 	sll	$t9,$t3,0x10
/*  f123fb4:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f123fb8:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*  f123fbc:	24820008 */ 	addiu	$v0,$a0,0x8
.L0f123fc0:
/*  f123fc0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f123fc4:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f123fc8:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f123fcc:	03e00008 */ 	jr	$ra
/*  f123fd0:	27bd0488 */ 	addiu	$sp,$sp,0x488
);

GLOBAL_ASM(
glabel func0f123fd4
.late_rodata
glabel var7f1b50f0
.word 0xc4eac000
glabel var7f1b50f4
.word 0xc4eac000
glabel var7f1b50f8
.word 0xc4eac000
glabel var7f1b50fc
.word 0xc4eac000
glabel var7f1b5100
.word 0x44eaa000
glabel var7f1b5104
.word 0x46fffe00
.text
/*  f123fd4:	27bdfb30 */ 	addiu	$sp,$sp,-1232
/*  f123fd8:	afb00020 */ 	sw	$s0,0x20($sp)
/*  f123fdc:	00808025 */ 	or	$s0,$a0,$zero
/*  f123fe0:	afbf0024 */ 	sw	$ra,0x24($sp)
/*  f123fe4:	afa504d4 */ 	sw	$a1,0x4d4($sp)
/*  f123fe8:	00a02025 */ 	or	$a0,$a1,$zero
/*  f123fec:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f123ff0:	afa604d8 */ 	sw	$a2,0x4d8($sp)
/*  f123ff4:	afa704dc */ 	sw	$a3,0x4dc($sp)
/*  f123ff8:	0fc48b3a */ 	jal	func0f122ce8
/*  f123ffc:	00c02825 */ 	or	$a1,$a2,$zero
/*  f124000:	14400015 */ 	bnez	$v0,.L0f124058
/*  f124004:	8fa404d8 */ 	lw	$a0,0x4d8($sp)
/*  f124008:	0fc48b3a */ 	jal	func0f122ce8
/*  f12400c:	8fa504dc */ 	lw	$a1,0x4dc($sp)
/*  f124010:	14400011 */ 	bnez	$v0,.L0f124058
/*  f124014:	8fa404dc */ 	lw	$a0,0x4dc($sp)
/*  f124018:	0fc48b3a */ 	jal	func0f122ce8
/*  f12401c:	8fa504d4 */ 	lw	$a1,0x4d4($sp)
/*  f124020:	1440000d */ 	bnez	$v0,.L0f124058
/*  f124024:	8fa404e0 */ 	lw	$a0,0x4e0($sp)
/*  f124028:	0fc48b3a */ 	jal	func0f122ce8
/*  f12402c:	8fa504d4 */ 	lw	$a1,0x4d4($sp)
/*  f124030:	14400009 */ 	bnez	$v0,.L0f124058
/*  f124034:	8fa404e0 */ 	lw	$a0,0x4e0($sp)
/*  f124038:	0fc48b3a */ 	jal	func0f122ce8
/*  f12403c:	8fa504d8 */ 	lw	$a1,0x4d8($sp)
/*  f124040:	14400005 */ 	bnez	$v0,.L0f124058
/*  f124044:	8fa404e0 */ 	lw	$a0,0x4e0($sp)
/*  f124048:	0fc48b3a */ 	jal	func0f122ce8
/*  f12404c:	8fa504dc */ 	lw	$a1,0x4dc($sp)
/*  f124050:	10400003 */ 	beqz	$v0,.L0f124060
/*  f124054:	c7aa04e4 */ 	lwc1	$f10,0x4e4($sp)
.L0f124058:
/*  f124058:	10000636 */ 	b	.L0f125934
/*  f12405c:	02001025 */ 	or	$v0,$s0,$zero
.L0f124060:
/*  f124060:	3c013780 */ 	lui	$at,0x3780
/*  f124064:	44812000 */ 	mtc1	$at,$f4
/*  f124068:	8fa304d4 */ 	lw	$v1,0x4d4($sp)
/*  f12406c:	8fa404dc */ 	lw	$a0,0x4dc($sp)
/*  f124070:	46045202 */ 	mul.s	$f8,$f10,$f4
/*  f124074:	8fa904d8 */ 	lw	$t1,0x4d8($sp)
/*  f124078:	00603825 */ 	or	$a3,$v1,$zero
/*  f12407c:	00804025 */ 	or	$t0,$a0,$zero
/*  f124080:	01202825 */ 	or	$a1,$t1,$zero
/*  f124084:	e7a803c0 */ 	swc1	$f8,0x3c0($sp)
/*  f124088:	c46c0028 */ 	lwc1	$f12,0x28($v1)
/*  f12408c:	c48a0028 */ 	lwc1	$f10,0x28($a0)
/*  f124090:	c460002c */ 	lwc1	$f0,0x2c($v1)
/*  f124094:	c52e002c */ 	lwc1	$f14,0x2c($t1)
/*  f124098:	460c5101 */ 	sub.s	$f4,$f10,$f12
/*  f12409c:	c5260028 */ 	lwc1	$f6,0x28($t1)
/*  f1240a0:	46007081 */ 	sub.s	$f2,$f14,$f0
/*  f1240a4:	e7a404b0 */ 	swc1	$f4,0x4b0($sp)
/*  f1240a8:	c494002c */ 	lwc1	$f20,0x2c($a0)
/*  f1240ac:	c7a804b0 */ 	lwc1	$f8,0x4b0($sp)
/*  f1240b0:	460c3481 */ 	sub.s	$f18,$f6,$f12
/*  f1240b4:	46024182 */ 	mul.s	$f6,$f8,$f2
/*  f1240b8:	4600a401 */ 	sub.s	$f16,$f20,$f0
/*  f1240bc:	44814000 */ 	mtc1	$at,$f8
/*  f1240c0:	3c013f80 */ 	lui	$at,0x3f80
/*  f1240c4:	46109282 */ 	mul.s	$f10,$f18,$f16
/*  f1240c8:	4600703c */ 	c.lt.s	$f14,$f0
/*  f1240cc:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f1240d0:	44815000 */ 	mtc1	$at,$f10
/*  f1240d4:	46082182 */ 	mul.s	$f6,$f4,$f8
/*  f1240d8:	46065103 */ 	div.s	$f4,$f10,$f6
/*  f1240dc:	e7a60054 */ 	swc1	$f6,0x54($sp)
/*  f1240e0:	e7a60488 */ 	swc1	$f6,0x488($sp)
/*  f1240e4:	e7a40050 */ 	swc1	$f4,0x50($sp)
/*  f1240e8:	4500000a */ 	bc1f	.L0f124114
/*  f1240ec:	e7a40484 */ 	swc1	$f4,0x484($sp)
/*  f1240f0:	3c01bf80 */ 	lui	$at,0xbf80
/*  f1240f4:	44811000 */ 	mtc1	$at,$f2
/*  f1240f8:	00602825 */ 	or	$a1,$v1,$zero
/*  f1240fc:	01203825 */ 	or	$a3,$t1,$zero
/*  f124100:	46023302 */ 	mul.s	$f12,$f6,$f2
/*  f124104:	00000000 */ 	nop
/*  f124108:	46022382 */ 	mul.s	$f14,$f4,$f2
/*  f12410c:	e7ac0488 */ 	swc1	$f12,0x488($sp)
/*  f124110:	e7ae0484 */ 	swc1	$f14,0x484($sp)
.L0f124114:
/*  f124114:	c4a0002c */ 	lwc1	$f0,0x2c($a1)
/*  f124118:	3c01bf80 */ 	lui	$at,0xbf80
/*  f12411c:	44811000 */ 	mtc1	$at,$f2
/*  f124120:	4600a03c */ 	c.lt.s	$f20,$f0
/*  f124124:	c7ac0488 */ 	lwc1	$f12,0x488($sp)
/*  f124128:	c7ae0484 */ 	lwc1	$f14,0x484($sp)
/*  f12412c:	3c014080 */ 	lui	$at,0x4080
/*  f124130:	45020006 */ 	bc1fl	.L0f12414c
/*  f124134:	e7ae0484 */ 	swc1	$f14,0x484($sp)
/*  f124138:	00a04025 */ 	or	$t0,$a1,$zero
/*  f12413c:	46027382 */ 	mul.s	$f14,$f14,$f2
/*  f124140:	00802825 */ 	or	$a1,$a0,$zero
/*  f124144:	c480002c */ 	lwc1	$f0,0x2c($a0)
/*  f124148:	e7ae0484 */ 	swc1	$f14,0x484($sp)
.L0f12414c:
/*  f12414c:	c4e8002c */ 	lwc1	$f8,0x2c($a3)
/*  f124150:	4608003c */ 	c.lt.s	$f0,$f8
/*  f124154:	44810000 */ 	mtc1	$at,$f0
/*  f124158:	3c013e80 */ 	lui	$at,0x3e80
/*  f12415c:	44813000 */ 	mtc1	$at,$f6
/*  f124160:	45020007 */ 	bc1fl	.L0f124180
/*  f124164:	c4aa0028 */ 	lwc1	$f10,0x28($a1)
/*  f124168:	46027382 */ 	mul.s	$f14,$f14,$f2
/*  f12416c:	00a01025 */ 	or	$v0,$a1,$zero
/*  f124170:	00e02825 */ 	or	$a1,$a3,$zero
/*  f124174:	00403825 */ 	or	$a3,$v0,$zero
/*  f124178:	e7ae0484 */ 	swc1	$f14,0x484($sp)
/*  f12417c:	c4aa0028 */ 	lwc1	$f10,0x28($a1)
.L0f124180:
/*  f124180:	4480a000 */ 	mtc1	$zero,$f20
/*  f124184:	3c0644ea */ 	lui	$a2,0x44ea
/*  f124188:	46065102 */ 	mul.s	$f4,$f10,$f6
/*  f12418c:	e7b40468 */ 	swc1	$f20,0x468($sp)
/*  f124190:	44815000 */ 	mtc1	$at,$f10
/*  f124194:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f124198:	e7a40464 */ 	swc1	$f4,0x464($sp)
/*  f12419c:	c4e80028 */ 	lwc1	$f8,0x28($a3)
/*  f1241a0:	e7b40470 */ 	swc1	$f20,0x470($sp)
/*  f1241a4:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f1241a8:	44814000 */ 	mtc1	$at,$f8
/*  f1241ac:	e7a6046c */ 	swc1	$f6,0x46c($sp)
/*  f1241b0:	c4e40028 */ 	lwc1	$f4,0x28($a3)
/*  f1241b4:	e7b40478 */ 	swc1	$f20,0x478($sp)
/*  f1241b8:	e7b40480 */ 	swc1	$f20,0x480($sp)
/*  f1241bc:	46082282 */ 	mul.s	$f10,$f4,$f8
/*  f1241c0:	e7b4047c */ 	swc1	$f20,0x47c($sp)
/*  f1241c4:	e7aa0474 */ 	swc1	$f10,0x474($sp)
/*  f1241c8:	c5060028 */ 	lwc1	$f6,0x28($t0)
/*  f1241cc:	e7a6048c */ 	swc1	$f6,0x48c($sp)
/*  f1241d0:	c504002c */ 	lwc1	$f4,0x2c($t0)
/*  f1241d4:	e7a40490 */ 	swc1	$f4,0x490($sp)
/*  f1241d8:	c4a80028 */ 	lwc1	$f8,0x28($a1)
/*  f1241dc:	e7a80494 */ 	swc1	$f8,0x494($sp)
/*  f1241e0:	c4aa002c */ 	lwc1	$f10,0x2c($a1)
/*  f1241e4:	c7a80494 */ 	lwc1	$f8,0x494($sp)
/*  f1241e8:	e7aa0498 */ 	swc1	$f10,0x498($sp)
/*  f1241ec:	c4e60028 */ 	lwc1	$f6,0x28($a3)
/*  f1241f0:	e7a6049c */ 	swc1	$f6,0x49c($sp)
/*  f1241f4:	c4e4002c */ 	lwc1	$f4,0x2c($a3)
/*  f1241f8:	c7a60498 */ 	lwc1	$f6,0x498($sp)
/*  f1241fc:	c7aa049c */ 	lwc1	$f10,0x49c($sp)
/*  f124200:	e7a404a0 */ 	swc1	$f4,0x4a0($sp)
/*  f124204:	c7a404a0 */ 	lwc1	$f4,0x4a0($sp)
/*  f124208:	e7a6002c */ 	swc1	$f6,0x2c($sp)
/*  f12420c:	e7a80028 */ 	swc1	$f8,0x28($sp)
/*  f124210:	46043081 */ 	sub.s	$f2,$f6,$f4
/*  f124214:	c7a60490 */ 	lwc1	$f6,0x490($sp)
/*  f124218:	afa804c4 */ 	sw	$t0,0x4c4($sp)
/*  f12421c:	460a4481 */ 	sub.s	$f18,$f8,$f10
/*  f124220:	c7a8048c */ 	lwc1	$f8,0x48c($sp)
/*  f124224:	afa704cc */ 	sw	$a3,0x4cc($sp)
/*  f124228:	46043401 */ 	sub.s	$f16,$f6,$f4
/*  f12422c:	c7a40028 */ 	lwc1	$f4,0x28($sp)
/*  f124230:	afa504c8 */ 	sw	$a1,0x4c8($sp)
/*  f124234:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f124238:	e7b40440 */ 	swc1	$f20,0x440($sp)
/*  f12423c:	e7b4043c */ 	swc1	$f20,0x43c($sp)
/*  f124240:	46044301 */ 	sub.s	$f12,$f8,$f4
/*  f124244:	c7a8002c */ 	lwc1	$f8,0x2c($sp)
/*  f124248:	44812000 */ 	mtc1	$at,$f4
/*  f12424c:	e7aa04b0 */ 	swc1	$f10,0x4b0($sp)
/*  f124250:	46083381 */ 	sub.s	$f14,$f6,$f8
/*  f124254:	46046182 */ 	mul.s	$f6,$f12,$f4
/*  f124258:	44814000 */ 	mtc1	$at,$f8
/*  f12425c:	e7ac04a8 */ 	swc1	$f12,0x4a8($sp)
/*  f124260:	e7ae04a4 */ 	swc1	$f14,0x4a4($sp)
/*  f124264:	46087102 */ 	mul.s	$f4,$f14,$f8
/*  f124268:	e7b40420 */ 	swc1	$f20,0x420($sp)
/*  f12426c:	e7b4041c */ 	swc1	$f20,0x41c($sp)
/*  f124270:	e7a60424 */ 	swc1	$f6,0x424($sp)
/*  f124274:	44813000 */ 	mtc1	$at,$f6
/*  f124278:	e7b403e4 */ 	swc1	$f20,0x3e4($sp)
/*  f12427c:	e7b403ec */ 	swc1	$f20,0x3ec($sp)
/*  f124280:	46069202 */ 	mul.s	$f8,$f18,$f6
/*  f124284:	e7a40428 */ 	swc1	$f4,0x428($sp)
/*  f124288:	44812000 */ 	mtc1	$at,$f4
/*  f12428c:	e7b403f4 */ 	swc1	$f20,0x3f4($sp)
/*  f124290:	e7b40400 */ 	swc1	$f20,0x400($sp)
/*  f124294:	46041182 */ 	mul.s	$f6,$f2,$f4
/*  f124298:	e7b403fc */ 	swc1	$f20,0x3fc($sp)
/*  f12429c:	e7a8042c */ 	swc1	$f8,0x42c($sp)
/*  f1242a0:	44814000 */ 	mtc1	$at,$f8
/*  f1242a4:	e7b403c4 */ 	swc1	$f20,0x3c4($sp)
/*  f1242a8:	e7b403cc */ 	swc1	$f20,0x3cc($sp)
/*  f1242ac:	46085102 */ 	mul.s	$f4,$f10,$f8
/*  f1242b0:	e7a60430 */ 	swc1	$f6,0x430($sp)
/*  f1242b4:	44813000 */ 	mtc1	$at,$f6
/*  f1242b8:	3c017f1b */ 	lui	$at,%hi(var7f1b50f0)
/*  f1242bc:	e7b403d4 */ 	swc1	$f20,0x3d4($sp)
/*  f1242c0:	46068202 */ 	mul.s	$f8,$f16,$f6
/*  f1242c4:	e7b403e0 */ 	swc1	$f20,0x3e0($sp)
/*  f1242c8:	e7a40434 */ 	swc1	$f4,0x434($sp)
/*  f1242cc:	46006102 */ 	mul.s	$f4,$f12,$f0
/*  f1242d0:	e7b403dc */ 	swc1	$f20,0x3dc($sp)
/*  f1242d4:	46007182 */ 	mul.s	$f6,$f14,$f0
/*  f1242d8:	e7a80438 */ 	swc1	$f8,0x438($sp)
/*  f1242dc:	c42e50f0 */ 	lwc1	$f14,%lo(var7f1b50f0)($at)
/*  f1242e0:	46009202 */ 	mul.s	$f8,$f18,$f0
/*  f1242e4:	e7a40404 */ 	swc1	$f4,0x404($sp)
/*  f1242e8:	46001102 */ 	mul.s	$f4,$f2,$f0
/*  f1242ec:	e7a60408 */ 	swc1	$f6,0x408($sp)
/*  f1242f0:	46005182 */ 	mul.s	$f6,$f10,$f0
/*  f1242f4:	e7a8040c */ 	swc1	$f8,0x40c($sp)
/*  f1242f8:	46008202 */ 	mul.s	$f8,$f16,$f0
/*  f1242fc:	e7a40410 */ 	swc1	$f4,0x410($sp)
/*  f124300:	c7a404a4 */ 	lwc1	$f4,0x4a4($sp)
/*  f124304:	e7a60414 */ 	swc1	$f6,0x414($sp)
/*  f124308:	46040183 */ 	div.s	$f6,$f0,$f4
/*  f12430c:	e7a80418 */ 	swc1	$f8,0x418($sp)
/*  f124310:	46020203 */ 	div.s	$f8,$f0,$f2
/*  f124314:	e7a603e8 */ 	swc1	$f6,0x3e8($sp)
/*  f124318:	46100183 */ 	div.s	$f6,$f0,$f16
/*  f12431c:	e7a803f0 */ 	swc1	$f8,0x3f0($sp)
/*  f124320:	c7a804a8 */ 	lwc1	$f8,0x4a8($sp)
/*  f124324:	46044303 */ 	div.s	$f12,$f8,$f4
/*  f124328:	e7a603f8 */ 	swc1	$f6,0x3f8($sp)
/*  f12432c:	46029183 */ 	div.s	$f6,$f18,$f2
/*  f124330:	e7ac03c8 */ 	swc1	$f12,0x3c8($sp)
/*  f124334:	46105203 */ 	div.s	$f8,$f10,$f16
/*  f124338:	e7a603d0 */ 	swc1	$f6,0x3d0($sp)
/*  f12433c:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f124340:	e7a803d8 */ 	swc1	$f8,0x3d8($sp)
/*  f124344:	3c017f1b */ 	lui	$at,%hi(var7f1b50f4)
/*  f124348:	3c0644ea */ 	lui	$a2,0x44ea
/*  f12434c:	e7a003c8 */ 	swc1	$f0,0x3c8($sp)
/*  f124350:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f124354:	c42e50f4 */ 	lwc1	$f14,%lo(var7f1b50f4)($at)
/*  f124358:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f12435c:	c7ac03d0 */ 	lwc1	$f12,0x3d0($sp)
/*  f124360:	3c017f1b */ 	lui	$at,%hi(var7f1b50f8)
/*  f124364:	3c0644ea */ 	lui	$a2,0x44ea
/*  f124368:	e7a003d0 */ 	swc1	$f0,0x3d0($sp)
/*  f12436c:	34c6a000 */ 	ori	$a2,$a2,0xa000
/*  f124370:	c42e50f8 */ 	lwc1	$f14,%lo(var7f1b50f8)($at)
/*  f124374:	0fc47cf4 */ 	jal	func0f11f3d0
/*  f124378:	c7ac03d8 */ 	lwc1	$f12,0x3d8($sp)
/*  f12437c:	c7a4046c */ 	lwc1	$f4,0x46c($sp)
/*  f124380:	c7a60474 */ 	lwc1	$f6,0x474($sp)
/*  f124384:	8fae04d4 */ 	lw	$t6,0x4d4($sp)
/*  f124388:	8fb804d8 */ 	lw	$t8,0x4d8($sp)
/*  f12438c:	e7a003d8 */ 	swc1	$f0,0x3d8($sp)
/*  f124390:	e7a4044c */ 	swc1	$f4,0x44c($sp)
/*  f124394:	e7a60454 */ 	swc1	$f6,0x454($sp)
/*  f124398:	c5ca0028 */ 	lwc1	$f10,0x28($t6)
/*  f12439c:	c7080028 */ 	lwc1	$f8,0x28($t8)
/*  f1243a0:	4608503c */ 	c.lt.s	$f10,$f8
/*  f1243a4:	00000000 */ 	nop
/*  f1243a8:	4502009d */ 	bc1fl	.L0f124620
/*  f1243ac:	8fae04dc */ 	lw	$t6,0x4dc($sp)
/*  f1243b0:	8fb904dc */ 	lw	$t9,0x4dc($sp)
/*  f1243b4:	8faf04e0 */ 	lw	$t7,0x4e0($sp)
/*  f1243b8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1243bc:	c724002c */ 	lwc1	$f4,0x2c($t9)
/*  f1243c0:	c5e6002c */ 	lwc1	$f6,0x2c($t7)
/*  f1243c4:	44814000 */ 	mtc1	$at,$f8
/*  f1243c8:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f1243cc:	4608503c */ 	c.lt.s	$f10,$f8
/*  f1243d0:	00000000 */ 	nop
/*  f1243d4:	45000004 */ 	bc1f	.L0f1243e8
/*  f1243d8:	3c017f1b */ 	lui	$at,%hi(var7f1b50fc)
/*  f1243dc:	c42450fc */ 	lwc1	$f4,%lo(var7f1b50fc)($at)
/*  f1243e0:	10000010 */ 	b	.L0f124424
/*  f1243e4:	e7a401bc */ 	swc1	$f4,0x1bc($sp)
.L0f1243e8:
/*  f1243e8:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1243ec:	00000000 */ 	nop
/*  f1243f0:	8fae04dc */ 	lw	$t6,0x4dc($sp)
/*  f1243f4:	8fb804e0 */ 	lw	$t8,0x4e0($sp)
/*  f1243f8:	3c013e80 */ 	lui	$at,0x3e80
/*  f1243fc:	c5c6002c */ 	lwc1	$f6,0x2c($t6)
/*  f124400:	c70a002c */ 	lwc1	$f10,0x2c($t8)
/*  f124404:	44812000 */ 	mtc1	$at,$f4
/*  f124408:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f12440c:	44815000 */ 	mtc1	$at,$f10
/*  f124410:	46044182 */ 	mul.s	$f6,$f8,$f4
/*  f124414:	460a0201 */ 	sub.s	$f8,$f0,$f10
/*  f124418:	46004107 */ 	neg.s	$f4,$f8
/*  f12441c:	46062283 */ 	div.s	$f10,$f4,$f6
/*  f124420:	e7aa01bc */ 	swc1	$f10,0x1bc($sp)
.L0f124424:
/*  f124424:	3c05b400 */ 	lui	$a1,0xb400
/*  f124428:	02001025 */ 	or	$v0,$s0,$zero
/*  f12442c:	ac450000 */ 	sw	$a1,0x0($v0)
/*  f124430:	8fb904dc */ 	lw	$t9,0x4dc($sp)
/*  f124434:	444ff800 */ 	cfc1	$t7,$31
/*  f124438:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f12443c:	44cef800 */ 	ctc1	$t6,$31
/*  f124440:	c728002c */ 	lwc1	$f8,0x2c($t9)
/*  f124444:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124448:	02001825 */ 	or	$v1,$s0,$zero
/*  f12444c:	46004124 */ 	cvt.w.s	$f4,$f8
/*  f124450:	3c19b200 */ 	lui	$t9,0xb200
/*  f124454:	444ef800 */ 	cfc1	$t6,$31
/*  f124458:	00000000 */ 	nop
/*  f12445c:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f124460:	11c00012 */ 	beqz	$t6,.L0f1244ac
/*  f124464:	3c014f00 */ 	lui	$at,0x4f00
/*  f124468:	44812000 */ 	mtc1	$at,$f4
/*  f12446c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f124470:	46044101 */ 	sub.s	$f4,$f8,$f4
/*  f124474:	44cef800 */ 	ctc1	$t6,$31
/*  f124478:	00000000 */ 	nop
/*  f12447c:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f124480:	444ef800 */ 	cfc1	$t6,$31
/*  f124484:	00000000 */ 	nop
/*  f124488:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f12448c:	15c00005 */ 	bnez	$t6,.L0f1244a4
/*  f124490:	00000000 */ 	nop
/*  f124494:	440e2000 */ 	mfc1	$t6,$f4
/*  f124498:	3c018000 */ 	lui	$at,0x8000
/*  f12449c:	10000007 */ 	b	.L0f1244bc
/*  f1244a0:	01c17025 */ 	or	$t6,$t6,$at
.L0f1244a4:
/*  f1244a4:	10000005 */ 	b	.L0f1244bc
/*  f1244a8:	240effff */ 	addiu	$t6,$zero,-1
.L0f1244ac:
/*  f1244ac:	440e2000 */ 	mfc1	$t6,$f4
/*  f1244b0:	00000000 */ 	nop
/*  f1244b4:	05c0fffb */ 	bltz	$t6,.L0f1244a4
/*  f1244b8:	00000000 */ 	nop
.L0f1244bc:
/*  f1244bc:	3c01ce80 */ 	lui	$at,0xce80
/*  f1244c0:	01c1c025 */ 	or	$t8,$t6,$at
/*  f1244c4:	ac580004 */ 	sw	$t8,0x4($v0)
/*  f1244c8:	44cff800 */ 	ctc1	$t7,$31
/*  f1244cc:	ac790000 */ 	sw	$t9,0x0($v1)
/*  f1244d0:	8faf04e0 */ 	lw	$t7,0x4e0($sp)
/*  f1244d4:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1244d8:	02002025 */ 	or	$a0,$s0,$zero
/*  f1244dc:	c5e6002c */ 	lwc1	$f6,0x2c($t7)
/*  f1244e0:	8faf04d4 */ 	lw	$t7,0x4d4($sp)
/*  f1244e4:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1244e8:	4600328d */ 	trunc.w.s	$f10,$f6
/*  f1244ec:	c5e8002c */ 	lwc1	$f8,0x2c($t7)
/*  f1244f0:	4600410d */ 	trunc.w.s	$f4,$f8
/*  f1244f4:	44185000 */ 	mfc1	$t8,$f10
/*  f1244f8:	00000000 */ 	nop
/*  f1244fc:	0018cc00 */ 	sll	$t9,$t8,0x10
/*  f124500:	44182000 */ 	mfc1	$t8,$f4
/*  f124504:	00000000 */ 	nop
/*  f124508:	03387825 */ 	or	$t7,$t9,$t8
/*  f12450c:	ac6f0004 */ 	sw	$t7,0x4($v1)
/*  f124510:	ac850000 */ 	sw	$a1,0x0($a0)
/*  f124514:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f124518:	afa401b0 */ 	sw	$a0,0x1b0($sp)
/*  f12451c:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f124520:	e7a0005c */ 	swc1	$f0,0x5c($sp)
/*  f124524:	c7a6005c */ 	lwc1	$f6,0x5c($sp)
/*  f124528:	3c013e80 */ 	lui	$at,0x3e80
/*  f12452c:	44814000 */ 	mtc1	$at,$f8
/*  f124530:	46060280 */ 	add.s	$f10,$f0,$f6
/*  f124534:	0fc54be8 */ 	jal	func0f152fa0
/*  f124538:	46085301 */ 	sub.s	$f12,$f10,$f8
/*  f12453c:	8fae01b0 */ 	lw	$t6,0x1b0($sp)
/*  f124540:	02001825 */ 	or	$v1,$s0,$zero
/*  f124544:	3c19b200 */ 	lui	$t9,0xb200
/*  f124548:	adc20004 */ 	sw	$v0,0x4($t6)
/*  f12454c:	ac790000 */ 	sw	$t9,0x0($v1)
/*  f124550:	afa301ac */ 	sw	$v1,0x1ac($sp)
/*  f124554:	c7ac01bc */ 	lwc1	$f12,0x1bc($sp)
/*  f124558:	0fc54be8 */ 	jal	func0f152fa0
/*  f12455c:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124560:	8fa301ac */ 	lw	$v1,0x1ac($sp)
/*  f124564:	02002025 */ 	or	$a0,$s0,$zero
/*  f124568:	3c18b400 */ 	lui	$t8,0xb400
/*  f12456c:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f124570:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f124574:	afa401a8 */ 	sw	$a0,0x1a8($sp)
/*  f124578:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f12457c:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124580:	0fc54be8 */ 	jal	func0f152fa0
/*  f124584:	46000306 */ 	mov.s	$f12,$f0
/*  f124588:	8faf01a8 */ 	lw	$t7,0x1a8($sp)
/*  f12458c:	02001825 */ 	or	$v1,$s0,$zero
/*  f124590:	3c0eb200 */ 	lui	$t6,0xb200
/*  f124594:	ade20004 */ 	sw	$v0,0x4($t7)
/*  f124598:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f12459c:	afa301a4 */ 	sw	$v1,0x1a4($sp)
/*  f1245a0:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1245a4:	0fc54be8 */ 	jal	func0f152fa0
/*  f1245a8:	4600a306 */ 	mov.s	$f12,$f20
/*  f1245ac:	8fa301a4 */ 	lw	$v1,0x1a4($sp)
/*  f1245b0:	02002025 */ 	or	$a0,$s0,$zero
/*  f1245b4:	3c19b400 */ 	lui	$t9,0xb400
/*  f1245b8:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f1245bc:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f1245c0:	afa401a0 */ 	sw	$a0,0x1a0($sp)
/*  f1245c4:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1245c8:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1245cc:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1245d0:	e7a0005c */ 	swc1	$f0,0x5c($sp)
/*  f1245d4:	c7a4005c */ 	lwc1	$f4,0x5c($sp)
/*  f1245d8:	3c013e80 */ 	lui	$at,0x3e80
/*  f1245dc:	44815000 */ 	mtc1	$at,$f10
/*  f1245e0:	46040180 */ 	add.s	$f6,$f0,$f4
/*  f1245e4:	0fc54be8 */ 	jal	func0f152fa0
/*  f1245e8:	460a3301 */ 	sub.s	$f12,$f6,$f10
/*  f1245ec:	8fb801a0 */ 	lw	$t8,0x1a0($sp)
/*  f1245f0:	02001825 */ 	or	$v1,$s0,$zero
/*  f1245f4:	3c0fb200 */ 	lui	$t7,0xb200
/*  f1245f8:	af020004 */ 	sw	$v0,0x4($t8)
/*  f1245fc:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f124600:	afa3019c */ 	sw	$v1,0x19c($sp)
/*  f124604:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124608:	0fc54be8 */ 	jal	func0f152fa0
/*  f12460c:	4600a306 */ 	mov.s	$f12,$f20
/*  f124610:	8fa3019c */ 	lw	$v1,0x19c($sp)
/*  f124614:	10000094 */ 	b	.L0f124868
/*  f124618:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f12461c:	8fae04dc */ 	lw	$t6,0x4dc($sp)
.L0f124620:
/*  f124620:	8fb904e0 */ 	lw	$t9,0x4e0($sp)
/*  f124624:	3c013f80 */ 	lui	$at,0x3f80
/*  f124628:	c5c8002c */ 	lwc1	$f8,0x2c($t6)
/*  f12462c:	c724002c */ 	lwc1	$f4,0x2c($t9)
/*  f124630:	44815000 */ 	mtc1	$at,$f10
/*  f124634:	46044181 */ 	sub.s	$f6,$f8,$f4
/*  f124638:	460a303c */ 	c.lt.s	$f6,$f10
/*  f12463c:	00000000 */ 	nop
/*  f124640:	45000003 */ 	bc1f	.L0f124650
/*  f124644:	3c017f1b */ 	lui	$at,%hi(var7f1b5100)
/*  f124648:	1000000e */ 	b	.L0f124684
/*  f12464c:	c42e5100 */ 	lwc1	$f14,%lo(var7f1b5100)($at)
.L0f124650:
/*  f124650:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f124654:	00000000 */ 	nop
/*  f124658:	8fb804dc */ 	lw	$t8,0x4dc($sp)
/*  f12465c:	8faf04e0 */ 	lw	$t7,0x4e0($sp)
/*  f124660:	3c013e80 */ 	lui	$at,0x3e80
/*  f124664:	c708002c */ 	lwc1	$f8,0x2c($t8)
/*  f124668:	c5e4002c */ 	lwc1	$f4,0x2c($t7)
/*  f12466c:	44815000 */ 	mtc1	$at,$f10
/*  f124670:	46044181 */ 	sub.s	$f6,$f8,$f4
/*  f124674:	44812000 */ 	mtc1	$at,$f4
/*  f124678:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f12467c:	46040181 */ 	sub.s	$f6,$f0,$f4
/*  f124680:	46083383 */ 	div.s	$f14,$f6,$f8
.L0f124684:
/*  f124684:	02001025 */ 	or	$v0,$s0,$zero
/*  f124688:	3c0eb400 */ 	lui	$t6,0xb400
/*  f12468c:	ac4e0000 */ 	sw	$t6,0x0($v0)
/*  f124690:	8fb904dc */ 	lw	$t9,0x4dc($sp)
/*  f124694:	4458f800 */ 	cfc1	$t8,$31
/*  f124698:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f12469c:	44cff800 */ 	ctc1	$t7,$31
/*  f1246a0:	c72a002c */ 	lwc1	$f10,0x2c($t9)
/*  f1246a4:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1246a8:	02001825 */ 	or	$v1,$s0,$zero
/*  f1246ac:	46005124 */ 	cvt.w.s	$f4,$f10
/*  f1246b0:	3c19b200 */ 	lui	$t9,0xb200
/*  f1246b4:	444ff800 */ 	cfc1	$t7,$31
/*  f1246b8:	00000000 */ 	nop
/*  f1246bc:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f1246c0:	11e00012 */ 	beqz	$t7,.L0f12470c
/*  f1246c4:	3c014f00 */ 	lui	$at,0x4f00
/*  f1246c8:	44812000 */ 	mtc1	$at,$f4
/*  f1246cc:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f1246d0:	46045101 */ 	sub.s	$f4,$f10,$f4
/*  f1246d4:	44cff800 */ 	ctc1	$t7,$31
/*  f1246d8:	00000000 */ 	nop
/*  f1246dc:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f1246e0:	444ff800 */ 	cfc1	$t7,$31
/*  f1246e4:	00000000 */ 	nop
/*  f1246e8:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f1246ec:	15e00005 */ 	bnez	$t7,.L0f124704
/*  f1246f0:	00000000 */ 	nop
/*  f1246f4:	440f2000 */ 	mfc1	$t7,$f4
/*  f1246f8:	3c018000 */ 	lui	$at,0x8000
/*  f1246fc:	10000007 */ 	b	.L0f12471c
/*  f124700:	01e17825 */ 	or	$t7,$t7,$at
.L0f124704:
/*  f124704:	10000005 */ 	b	.L0f12471c
/*  f124708:	240fffff */ 	addiu	$t7,$zero,-1
.L0f12470c:
/*  f12470c:	440f2000 */ 	mfc1	$t7,$f4
/*  f124710:	00000000 */ 	nop
/*  f124714:	05e0fffb */ 	bltz	$t7,.L0f124704
/*  f124718:	00000000 */ 	nop
.L0f12471c:
/*  f12471c:	3c01ce00 */ 	lui	$at,0xce00
/*  f124720:	01e17025 */ 	or	$t6,$t7,$at
/*  f124724:	ac4e0004 */ 	sw	$t6,0x4($v0)
/*  f124728:	44d8f800 */ 	ctc1	$t8,$31
/*  f12472c:	ac790000 */ 	sw	$t9,0x0($v1)
/*  f124730:	8fb804e0 */ 	lw	$t8,0x4e0($sp)
/*  f124734:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124738:	02002025 */ 	or	$a0,$s0,$zero
/*  f12473c:	c706002c */ 	lwc1	$f6,0x2c($t8)
/*  f124740:	8fb804d4 */ 	lw	$t8,0x4d4($sp)
/*  f124744:	3c0fb400 */ 	lui	$t7,0xb400
/*  f124748:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f12474c:	c70a002c */ 	lwc1	$f10,0x2c($t8)
/*  f124750:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124754:	4600510d */ 	trunc.w.s	$f4,$f10
/*  f124758:	440e4000 */ 	mfc1	$t6,$f8
/*  f12475c:	00000000 */ 	nop
/*  f124760:	000ecc00 */ 	sll	$t9,$t6,0x10
/*  f124764:	440e2000 */ 	mfc1	$t6,$f4
/*  f124768:	00000000 */ 	nop
/*  f12476c:	032ec025 */ 	or	$t8,$t9,$t6
/*  f124770:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f124774:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*  f124778:	e7ae0198 */ 	swc1	$f14,0x198($sp)
/*  f12477c:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f124780:	afa4018c */ 	sw	$a0,0x18c($sp)
/*  f124784:	0fc54be8 */ 	jal	func0f152fa0
/*  f124788:	46000306 */ 	mov.s	$f12,$f0
/*  f12478c:	8fb9018c */ 	lw	$t9,0x18c($sp)
/*  f124790:	c7ac0198 */ 	lwc1	$f12,0x198($sp)
/*  f124794:	02001825 */ 	or	$v1,$s0,$zero
/*  f124798:	3c0eb200 */ 	lui	$t6,0xb200
/*  f12479c:	af220004 */ 	sw	$v0,0x4($t9)
/*  f1247a0:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f1247a4:	afa30188 */ 	sw	$v1,0x188($sp)
/*  f1247a8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1247ac:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1247b0:	8fa30188 */ 	lw	$v1,0x188($sp)
/*  f1247b4:	02002025 */ 	or	$a0,$s0,$zero
/*  f1247b8:	3c18b400 */ 	lui	$t8,0xb400
/*  f1247bc:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f1247c0:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f1247c4:	afa40184 */ 	sw	$a0,0x184($sp)
/*  f1247c8:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f1247cc:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1247d0:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1247d4:	e7a0005c */ 	swc1	$f0,0x5c($sp)
/*  f1247d8:	c7a6005c */ 	lwc1	$f6,0x5c($sp)
/*  f1247dc:	3c013e80 */ 	lui	$at,0x3e80
/*  f1247e0:	44815000 */ 	mtc1	$at,$f10
/*  f1247e4:	46060200 */ 	add.s	$f8,$f0,$f6
/*  f1247e8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1247ec:	460a4301 */ 	sub.s	$f12,$f8,$f10
/*  f1247f0:	8faf0184 */ 	lw	$t7,0x184($sp)
/*  f1247f4:	02001825 */ 	or	$v1,$s0,$zero
/*  f1247f8:	3c19b200 */ 	lui	$t9,0xb200
/*  f1247fc:	ade20004 */ 	sw	$v0,0x4($t7)
/*  f124800:	ac790000 */ 	sw	$t9,0x0($v1)
/*  f124804:	afa30180 */ 	sw	$v1,0x180($sp)
/*  f124808:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12480c:	0fc54be8 */ 	jal	func0f152fa0
/*  f124810:	4600a306 */ 	mov.s	$f12,$f20
/*  f124814:	8fa30180 */ 	lw	$v1,0x180($sp)
/*  f124818:	02002025 */ 	or	$a0,$s0,$zero
/*  f12481c:	3c0eb400 */ 	lui	$t6,0xb400
/*  f124820:	ac620004 */ 	sw	$v0,0x4($v1)
/*  f124824:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f124828:	afa4017c */ 	sw	$a0,0x17c($sp)
/*  f12482c:	0fc2d5fe */ 	jal	currentPlayerGetScreenLeft
/*  f124830:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124834:	0fc54be8 */ 	jal	func0f152fa0
/*  f124838:	46000306 */ 	mov.s	$f12,$f0
/*  f12483c:	8fb8017c */ 	lw	$t8,0x17c($sp)
/*  f124840:	02001825 */ 	or	$v1,$s0,$zero
/*  f124844:	3c0fb200 */ 	lui	$t7,0xb200
/*  f124848:	af020004 */ 	sw	$v0,0x4($t8)
/*  f12484c:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f124850:	afa30178 */ 	sw	$v1,0x178($sp)
/*  f124854:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f124858:	0fc54be8 */ 	jal	func0f152fa0
/*  f12485c:	4600a306 */ 	mov.s	$f12,$f20
/*  f124860:	8fa30178 */ 	lw	$v1,0x178($sp)
/*  f124864:	ac620004 */ 	sw	$v0,0x4($v1)
.L0f124868:
/*  f124868:	8fa804cc */ 	lw	$t0,0x4cc($sp)
/*  f12486c:	c7a003c0 */ 	lwc1	$f0,0x3c0($sp)
/*  f124870:	8fa704c8 */ 	lw	$a3,0x4c8($sp)
/*  f124874:	c504000c */ 	lwc1	$f4,0xc($t0)
/*  f124878:	8fa904c4 */ 	lw	$t1,0x4c4($sp)
/*  f12487c:	8fab04e0 */ 	lw	$t3,0x4e0($sp)
/*  f124880:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f124884:	3c017f1b */ 	lui	$at,%hi(var7f1b5104)
/*  f124888:	e7a603b0 */ 	swc1	$f6,0x3b0($sp)
/*  f12488c:	c4e8000c */ 	lwc1	$f8,0xc($a3)
/*  f124890:	c7b003b0 */ 	lwc1	$f16,0x3b0($sp)
/*  f124894:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f124898:	e7aa03b4 */ 	swc1	$f10,0x3b4($sp)
/*  f12489c:	c524000c */ 	lwc1	$f4,0xc($t1)
/*  f1248a0:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f1248a4:	c7a403b4 */ 	lwc1	$f4,0x3b4($sp)
/*  f1248a8:	4610203c */ 	c.lt.s	$f4,$f16
/*  f1248ac:	e7a603b8 */ 	swc1	$f6,0x3b8($sp)
/*  f1248b0:	c568000c */ 	lwc1	$f8,0xc($t3)
/*  f1248b4:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f1248b8:	c7a003b8 */ 	lwc1	$f0,0x3b8($sp)
/*  f1248bc:	45000002 */ 	bc1f	.L0f1248c8
/*  f1248c0:	e7aa03bc */ 	swc1	$f10,0x3bc($sp)
/*  f1248c4:	46002406 */ 	mov.s	$f16,$f4
.L0f1248c8:
/*  f1248c8:	4610003c */ 	c.lt.s	$f0,$f16
/*  f1248cc:	00000000 */ 	nop
/*  f1248d0:	45020003 */ 	bc1fl	.L0f1248e0
/*  f1248d4:	c7a003bc */ 	lwc1	$f0,0x3bc($sp)
/*  f1248d8:	46000406 */ 	mov.s	$f16,$f0
/*  f1248dc:	c7a003bc */ 	lwc1	$f0,0x3bc($sp)
.L0f1248e0:
/*  f1248e0:	4610003c */ 	c.lt.s	$f0,$f16
/*  f1248e4:	00000000 */ 	nop
/*  f1248e8:	45000002 */ 	bc1f	.L0f1248f4
/*  f1248ec:	00000000 */ 	nop
/*  f1248f0:	46000406 */ 	mov.s	$f16,$f0
.L0f1248f4:
/*  f1248f4:	c4205104 */ 	lwc1	$f0,%lo(var7f1b5104)($at)
/*  f1248f8:	3c013f00 */ 	lui	$at,0x3f00
/*  f1248fc:	44813000 */ 	mtc1	$at,$f6
/*  f124900:	c5080034 */ 	lwc1	$f8,0x34($t0)
/*  f124904:	46068402 */ 	mul.s	$f16,$f16,$f6
/*  f124908:	00000000 */ 	nop
/*  f12490c:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f124910:	e7aa039c */ 	swc1	$f10,0x39c($sp)
/*  f124914:	c4e40034 */ 	lwc1	$f4,0x34($a3)
/*  f124918:	46102182 */ 	mul.s	$f6,$f4,$f16
/*  f12491c:	e7a603a0 */ 	swc1	$f6,0x3a0($sp)
/*  f124920:	c5280034 */ 	lwc1	$f8,0x34($t1)
/*  f124924:	46104282 */ 	mul.s	$f10,$f8,$f16
/*  f124928:	c7a8039c */ 	lwc1	$f8,0x39c($sp)
/*  f12492c:	e7aa03a4 */ 	swc1	$f10,0x3a4($sp)
/*  f124930:	c5640034 */ 	lwc1	$f4,0x34($t3)
/*  f124934:	46102182 */ 	mul.s	$f6,$f4,$f16
/*  f124938:	e7a603a8 */ 	swc1	$f6,0x3a8($sp)
/*  f12493c:	c50a0020 */ 	lwc1	$f10,0x20($t0)
/*  f124940:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*  f124944:	e7a4036c */ 	swc1	$f4,0x36c($sp)
/*  f124948:	c5060024 */ 	lwc1	$f6,0x24($t0)
/*  f12494c:	4604a03e */ 	c.le.s	$f20,$f4
/*  f124950:	46064282 */ 	mul.s	$f10,$f8,$f6
/*  f124954:	00000000 */ 	nop
/*  f124958:	46004182 */ 	mul.s	$f6,$f8,$f0
/*  f12495c:	e7aa0370 */ 	swc1	$f10,0x370($sp)
/*  f124960:	c7aa03a0 */ 	lwc1	$f10,0x3a0($sp)
/*  f124964:	e7a60374 */ 	swc1	$f6,0x374($sp)
/*  f124968:	c4e80020 */ 	lwc1	$f8,0x20($a3)
/*  f12496c:	46085182 */ 	mul.s	$f6,$f10,$f8
/*  f124970:	e7a60378 */ 	swc1	$f6,0x378($sp)
/*  f124974:	c4e80024 */ 	lwc1	$f8,0x24($a3)
/*  f124978:	46085182 */ 	mul.s	$f6,$f10,$f8
/*  f12497c:	00000000 */ 	nop
/*  f124980:	46005202 */ 	mul.s	$f8,$f10,$f0
/*  f124984:	e7a6037c */ 	swc1	$f6,0x37c($sp)
/*  f124988:	c7a603a4 */ 	lwc1	$f6,0x3a4($sp)
/*  f12498c:	e7a80380 */ 	swc1	$f8,0x380($sp)
/*  f124990:	c52a0020 */ 	lwc1	$f10,0x20($t1)
/*  f124994:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f124998:	e7a80384 */ 	swc1	$f8,0x384($sp)
/*  f12499c:	c52a0024 */ 	lwc1	$f10,0x24($t1)
/*  f1249a0:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*  f1249a4:	00000000 */ 	nop
/*  f1249a8:	46003282 */ 	mul.s	$f10,$f6,$f0
/*  f1249ac:	e7a80388 */ 	swc1	$f8,0x388($sp)
/*  f1249b0:	c7a803a8 */ 	lwc1	$f8,0x3a8($sp)
/*  f1249b4:	e7aa038c */ 	swc1	$f10,0x38c($sp)
/*  f1249b8:	c5660020 */ 	lwc1	$f6,0x20($t3)
/*  f1249bc:	46064282 */ 	mul.s	$f10,$f8,$f6
/*  f1249c0:	c7a803a8 */ 	lwc1	$f8,0x3a8($sp)
/*  f1249c4:	e7aa0390 */ 	swc1	$f10,0x390($sp)
/*  f1249c8:	c5660024 */ 	lwc1	$f6,0x24($t3)
/*  f1249cc:	46064282 */ 	mul.s	$f10,$f8,$f6
/*  f1249d0:	c7a803a8 */ 	lwc1	$f8,0x3a8($sp)
/*  f1249d4:	46004182 */ 	mul.s	$f6,$f8,$f0
/*  f1249d8:	c7a00370 */ 	lwc1	$f0,0x370($sp)
/*  f1249dc:	e7aa0394 */ 	swc1	$f10,0x394($sp)
/*  f1249e0:	45000003 */ 	bc1f	.L0f1249f0
/*  f1249e4:	e7a60398 */ 	swc1	$f6,0x398($sp)
/*  f1249e8:	10000003 */ 	b	.L0f1249f8
/*  f1249ec:	46002086 */ 	mov.s	$f2,$f4
.L0f1249f0:
/*  f1249f0:	c7a2036c */ 	lwc1	$f2,0x36c($sp)
/*  f1249f4:	46001087 */ 	neg.s	$f2,$f2
.L0f1249f8:
/*  f1249f8:	4600a03e */ 	c.le.s	$f20,$f0
/*  f1249fc:	00000000 */ 	nop
/*  f124a00:	45020004 */ 	bc1fl	.L0f124a14
/*  f124a04:	46000387 */ 	neg.s	$f14,$f0
/*  f124a08:	10000002 */ 	b	.L0f124a14
/*  f124a0c:	46000386 */ 	mov.s	$f14,$f0
/*  f124a10:	46000387 */ 	neg.s	$f14,$f0
.L0f124a14:
/*  f124a14:	c7a00378 */ 	lwc1	$f0,0x378($sp)
/*  f124a18:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124a1c:	00000000 */ 	nop
/*  f124a20:	45020004 */ 	bc1fl	.L0f124a34
/*  f124a24:	46000307 */ 	neg.s	$f12,$f0
/*  f124a28:	10000002 */ 	b	.L0f124a34
/*  f124a2c:	46000306 */ 	mov.s	$f12,$f0
/*  f124a30:	46000307 */ 	neg.s	$f12,$f0
.L0f124a34:
/*  f124a34:	460c103c */ 	c.lt.s	$f2,$f12
/*  f124a38:	00000000 */ 	nop
/*  f124a3c:	45020009 */ 	bc1fl	.L0f124a64
/*  f124a40:	c7a0037c */ 	lwc1	$f0,0x37c($sp)
/*  f124a44:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124a48:	00000000 */ 	nop
/*  f124a4c:	45020004 */ 	bc1fl	.L0f124a60
/*  f124a50:	46000087 */ 	neg.s	$f2,$f0
/*  f124a54:	10000002 */ 	b	.L0f124a60
/*  f124a58:	46000086 */ 	mov.s	$f2,$f0
/*  f124a5c:	46000087 */ 	neg.s	$f2,$f0
.L0f124a60:
/*  f124a60:	c7a0037c */ 	lwc1	$f0,0x37c($sp)
.L0f124a64:
/*  f124a64:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124a68:	00000000 */ 	nop
/*  f124a6c:	45020004 */ 	bc1fl	.L0f124a80
/*  f124a70:	46000307 */ 	neg.s	$f12,$f0
/*  f124a74:	10000002 */ 	b	.L0f124a80
/*  f124a78:	46000306 */ 	mov.s	$f12,$f0
/*  f124a7c:	46000307 */ 	neg.s	$f12,$f0
.L0f124a80:
/*  f124a80:	460c703c */ 	c.lt.s	$f14,$f12
/*  f124a84:	e7b003ac */ 	swc1	$f16,0x3ac($sp)
/*  f124a88:	4502000b */ 	bc1fl	.L0f124ab8
/*  f124a8c:	c7a00384 */ 	lwc1	$f0,0x384($sp)
/*  f124a90:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124a94:	00000000 */ 	nop
/*  f124a98:	45020005 */ 	bc1fl	.L0f124ab0
/*  f124a9c:	46000387 */ 	neg.s	$f14,$f0
/*  f124aa0:	46000386 */ 	mov.s	$f14,$f0
/*  f124aa4:	10000003 */ 	b	.L0f124ab4
/*  f124aa8:	e7b003ac */ 	swc1	$f16,0x3ac($sp)
/*  f124aac:	46000387 */ 	neg.s	$f14,$f0
.L0f124ab0:
/*  f124ab0:	e7b003ac */ 	swc1	$f16,0x3ac($sp)
.L0f124ab4:
/*  f124ab4:	c7a00384 */ 	lwc1	$f0,0x384($sp)
.L0f124ab8:
/*  f124ab8:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124abc:	00000000 */ 	nop
/*  f124ac0:	45020004 */ 	bc1fl	.L0f124ad4
/*  f124ac4:	46000307 */ 	neg.s	$f12,$f0
/*  f124ac8:	10000002 */ 	b	.L0f124ad4
/*  f124acc:	46000306 */ 	mov.s	$f12,$f0
/*  f124ad0:	46000307 */ 	neg.s	$f12,$f0
.L0f124ad4:
/*  f124ad4:	460c103c */ 	c.lt.s	$f2,$f12
/*  f124ad8:	00000000 */ 	nop
/*  f124adc:	45020009 */ 	bc1fl	.L0f124b04
/*  f124ae0:	c7a00388 */ 	lwc1	$f0,0x388($sp)
/*  f124ae4:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124ae8:	00000000 */ 	nop
/*  f124aec:	45020004 */ 	bc1fl	.L0f124b00
/*  f124af0:	46000087 */ 	neg.s	$f2,$f0
/*  f124af4:	10000002 */ 	b	.L0f124b00
/*  f124af8:	46000086 */ 	mov.s	$f2,$f0
/*  f124afc:	46000087 */ 	neg.s	$f2,$f0
.L0f124b00:
/*  f124b00:	c7a00388 */ 	lwc1	$f0,0x388($sp)
.L0f124b04:
/*  f124b04:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124b08:	00000000 */ 	nop
/*  f124b0c:	45020004 */ 	bc1fl	.L0f124b20
/*  f124b10:	46000307 */ 	neg.s	$f12,$f0
/*  f124b14:	10000002 */ 	b	.L0f124b20
/*  f124b18:	46000306 */ 	mov.s	$f12,$f0
/*  f124b1c:	46000307 */ 	neg.s	$f12,$f0
.L0f124b20:
/*  f124b20:	460c703c */ 	c.lt.s	$f14,$f12
/*  f124b24:	00000000 */ 	nop
/*  f124b28:	45020009 */ 	bc1fl	.L0f124b50
/*  f124b2c:	c7a00390 */ 	lwc1	$f0,0x390($sp)
/*  f124b30:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124b34:	00000000 */ 	nop
/*  f124b38:	45020004 */ 	bc1fl	.L0f124b4c
/*  f124b3c:	46000387 */ 	neg.s	$f14,$f0
/*  f124b40:	10000002 */ 	b	.L0f124b4c
/*  f124b44:	46000386 */ 	mov.s	$f14,$f0
/*  f124b48:	46000387 */ 	neg.s	$f14,$f0
.L0f124b4c:
/*  f124b4c:	c7a00390 */ 	lwc1	$f0,0x390($sp)
.L0f124b50:
/*  f124b50:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124b54:	00000000 */ 	nop
/*  f124b58:	45020004 */ 	bc1fl	.L0f124b6c
/*  f124b5c:	46000307 */ 	neg.s	$f12,$f0
/*  f124b60:	10000002 */ 	b	.L0f124b6c
/*  f124b64:	46000306 */ 	mov.s	$f12,$f0
/*  f124b68:	46000307 */ 	neg.s	$f12,$f0
.L0f124b6c:
/*  f124b6c:	460c103c */ 	c.lt.s	$f2,$f12
/*  f124b70:	e7a20364 */ 	swc1	$f2,0x364($sp)
/*  f124b74:	4502000a */ 	bc1fl	.L0f124ba0
/*  f124b78:	c7a00394 */ 	lwc1	$f0,0x394($sp)
/*  f124b7c:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124b80:	00000000 */ 	nop
/*  f124b84:	45020004 */ 	bc1fl	.L0f124b98
/*  f124b88:	46000087 */ 	neg.s	$f2,$f0
/*  f124b8c:	10000003 */ 	b	.L0f124b9c
/*  f124b90:	e7a00364 */ 	swc1	$f0,0x364($sp)
/*  f124b94:	46000087 */ 	neg.s	$f2,$f0
.L0f124b98:
/*  f124b98:	e7a20364 */ 	swc1	$f2,0x364($sp)
.L0f124b9c:
/*  f124b9c:	c7a00394 */ 	lwc1	$f0,0x394($sp)
.L0f124ba0:
/*  f124ba0:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124ba4:	00000000 */ 	nop
/*  f124ba8:	45020004 */ 	bc1fl	.L0f124bbc
/*  f124bac:	46000307 */ 	neg.s	$f12,$f0
/*  f124bb0:	10000002 */ 	b	.L0f124bbc
/*  f124bb4:	46000306 */ 	mov.s	$f12,$f0
/*  f124bb8:	46000307 */ 	neg.s	$f12,$f0
.L0f124bbc:
/*  f124bbc:	460c703c */ 	c.lt.s	$f14,$f12
/*  f124bc0:	e7ae0368 */ 	swc1	$f14,0x368($sp)
/*  f124bc4:	4502000a */ 	bc1fl	.L0f124bf0
/*  f124bc8:	c7aa036c */ 	lwc1	$f10,0x36c($sp)
/*  f124bcc:	4600a03e */ 	c.le.s	$f20,$f0
/*  f124bd0:	00000000 */ 	nop
/*  f124bd4:	45020004 */ 	bc1fl	.L0f124be8
/*  f124bd8:	46000387 */ 	neg.s	$f14,$f0
/*  f124bdc:	10000003 */ 	b	.L0f124bec
/*  f124be0:	e7a00368 */ 	swc1	$f0,0x368($sp)
/*  f124be4:	46000387 */ 	neg.s	$f14,$f0
.L0f124be8:
/*  f124be8:	e7ae0368 */ 	swc1	$f14,0x368($sp)
.L0f124bec:
/*  f124bec:	c7aa036c */ 	lwc1	$f10,0x36c($sp)
.L0f124bf0:
/*  f124bf0:	c7a80370 */ 	lwc1	$f8,0x370($sp)
/*  f124bf4:	c7a60374 */ 	lwc1	$f6,0x374($sp)
/*  f124bf8:	e7aa0354 */ 	swc1	$f10,0x354($sp)
/*  f124bfc:	c7aa037c */ 	lwc1	$f10,0x37c($sp)
/*  f124c00:	c7a40378 */ 	lwc1	$f4,0x378($sp)
/*  f124c04:	e7a80358 */ 	swc1	$f8,0x358($sp)
/*  f124c08:	e7a6035c */ 	swc1	$f6,0x35c($sp)
/*  f124c0c:	e7aa0338 */ 	swc1	$f10,0x338($sp)
/*  f124c10:	e7a40334 */ 	swc1	$f4,0x334($sp)
/*  f124c14:	c7a80380 */ 	lwc1	$f8,0x380($sp)
/*  f124c18:	c7a40388 */ 	lwc1	$f4,0x388($sp)
/*  f124c1c:	c7aa038c */ 	lwc1	$f10,0x38c($sp)
/*  f124c20:	c7a60384 */ 	lwc1	$f6,0x384($sp)
/*  f124c24:	e7a8033c */ 	swc1	$f8,0x33c($sp)
/*  f124c28:	e7a40318 */ 	swc1	$f4,0x318($sp)
/*  f124c2c:	e7aa031c */ 	swc1	$f10,0x31c($sp)
/*  f124c30:	e7a60314 */ 	swc1	$f6,0x314($sp)
/*  f124c34:	c5080030 */ 	lwc1	$f8,0x30($t0)
/*  f124c38:	27a302f4 */ 	addiu	$v1,$sp,0x2f4
/*  f124c3c:	27a60334 */ 	addiu	$a2,$sp,0x334
/*  f124c40:	e7a80360 */ 	swc1	$f8,0x360($sp)
/*  f124c44:	c4e60030 */ 	lwc1	$f6,0x30($a3)
/*  f124c48:	27a70324 */ 	addiu	$a3,$sp,0x324
/*  f124c4c:	27a20354 */ 	addiu	$v0,$sp,0x354
/*  f124c50:	e7a60340 */ 	swc1	$f6,0x340($sp)
/*  f124c54:	c5240030 */ 	lwc1	$f4,0x30($t1)
/*  f124c58:	27a402d4 */ 	addiu	$a0,$sp,0x2d4
/*  f124c5c:	27a50314 */ 	addiu	$a1,$sp,0x314
/*  f124c60:	e7a40320 */ 	swc1	$f4,0x320($sp)
.L0f124c64:
/*  f124c64:	c4400000 */ 	lwc1	$f0,0x0($v0)
/*  f124c68:	c4ca0000 */ 	lwc1	$f10,0x0($a2)
/*  f124c6c:	c4a60000 */ 	lwc1	$f6,0x0($a1)
/*  f124c70:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f124c74:	46005201 */ 	sub.s	$f8,$f10,$f0
/*  f124c78:	00a7082b */ 	sltu	$at,$a1,$a3
/*  f124c7c:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f124c80:	46003101 */ 	sub.s	$f4,$f6,$f0
/*  f124c84:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f124c88:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f124c8c:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f124c90:	e468fffc */ 	swc1	$f8,-0x4($v1)
/*  f124c94:	1420fff3 */ 	bnez	$at,.L0f124c64
/*  f124c98:	e484fffc */ 	swc1	$f4,-0x4($a0)
/*  f124c9c:	27a302f4 */ 	addiu	$v1,$sp,0x2f4
/*  f124ca0:	27a20354 */ 	addiu	$v0,$sp,0x354
/*  f124ca4:	27a402d4 */ 	addiu	$a0,$sp,0x2d4
/*  f124ca8:	27a70294 */ 	addiu	$a3,$sp,0x294
/*  f124cac:	27a502b4 */ 	addiu	$a1,$sp,0x2b4
/*  f124cb0:	27a80274 */ 	addiu	$t0,$sp,0x274
/*  f124cb4:	27a60254 */ 	addiu	$a2,$sp,0x254
/*  f124cb8:	c7b20410 */ 	lwc1	$f18,0x410($sp)
/*  f124cbc:	c7b0040c */ 	lwc1	$f16,0x40c($sp)
/*  f124cc0:	27a90264 */ 	addiu	$t1,$sp,0x264
.L0f124cc4:
/*  f124cc4:	c4800000 */ 	lwc1	$f0,0x0($a0)
/*  f124cc8:	c4620000 */ 	lwc1	$f2,0x0($v1)
/*  f124ccc:	c7a80418 */ 	lwc1	$f8,0x418($sp)
/*  f124cd0:	46120282 */ 	mul.s	$f10,$f0,$f18
/*  f124cd4:	3c013780 */ 	lui	$at,0x3780
/*  f124cd8:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f124cdc:	46024182 */ 	mul.s	$f6,$f8,$f2
/*  f124ce0:	44814000 */ 	mtc1	$at,$f8
/*  f124ce4:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f124ce8:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f124cec:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f124cf0:	24e70004 */ 	addiu	$a3,$a3,0x4
/*  f124cf4:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f124cf8:	46065101 */ 	sub.s	$f4,$f10,$f6
/*  f124cfc:	25080004 */ 	addiu	$t0,$t0,0x4
/*  f124d00:	46082302 */ 	mul.s	$f12,$f4,$f8
/*  f124d04:	e4ecfffc */ 	swc1	$f12,-0x4($a3)
/*  f124d08:	c7aa0414 */ 	lwc1	$f10,0x414($sp)
/*  f124d0c:	460a1182 */ 	mul.s	$f6,$f2,$f10
/*  f124d10:	44815000 */ 	mtc1	$at,$f10
/*  f124d14:	00c9082b */ 	sltu	$at,$a2,$t1
/*  f124d18:	46008102 */ 	mul.s	$f4,$f16,$f0
/*  f124d1c:	46043201 */ 	sub.s	$f8,$f6,$f4
/*  f124d20:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f124d24:	e4a6fffc */ 	swc1	$f6,-0x4($a1)
/*  f124d28:	c7a40484 */ 	lwc1	$f4,0x484($sp)
/*  f124d2c:	c4aafffc */ 	lwc1	$f10,-0x4($a1)
/*  f124d30:	46046202 */ 	mul.s	$f8,$f12,$f4
/*  f124d34:	c444fffc */ 	lwc1	$f4,-0x4($v0)
/*  f124d38:	e488fffc */ 	swc1	$f8,-0x4($a0)
/*  f124d3c:	c7a60484 */ 	lwc1	$f6,0x484($sp)
/*  f124d40:	e4c4fffc */ 	swc1	$f4,-0x4($a2)
/*  f124d44:	46065382 */ 	mul.s	$f14,$f10,$f6
/*  f124d48:	e46efffc */ 	swc1	$f14,-0x4($v1)
/*  f124d4c:	1420ffdd */ 	bnez	$at,.L0f124cc4
/*  f124d50:	e50efffc */ 	swc1	$f14,-0x4($t0)
/*  f124d54:	8fa304dc */ 	lw	$v1,0x4dc($sp)
/*  f124d58:	c568002c */ 	lwc1	$f8,0x2c($t3)
/*  f124d5c:	8fa204d4 */ 	lw	$v0,0x4d4($sp)
/*  f124d60:	c46a002c */ 	lwc1	$f10,0x2c($v1)
/*  f124d64:	c4640010 */ 	lwc1	$f4,0x10($v1)
/*  f124d68:	c44e0010 */ 	lwc1	$f14,0x10($v0)
/*  f124d6c:	460a4003 */ 	div.s	$f0,$f8,$f10
/*  f124d70:	c5660010 */ 	lwc1	$f6,0x10($t3)
/*  f124d74:	3c014780 */ 	lui	$at,0x4780
/*  f124d78:	44816000 */ 	mtc1	$at,$f12
/*  f124d7c:	46047201 */ 	sub.s	$f8,$f14,$f4
/*  f124d80:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f124d84:	46004282 */ 	mul.s	$f10,$f8,$f0
/*  f124d88:	460a3100 */ 	add.s	$f4,$f6,$f10
/*  f124d8c:	e7a40170 */ 	swc1	$f4,0x170($sp)
/*  f124d90:	c4660014 */ 	lwc1	$f6,0x14($v1)
/*  f124d94:	c4420014 */ 	lwc1	$f2,0x14($v0)
/*  f124d98:	c5680014 */ 	lwc1	$f8,0x14($t3)
/*  f124d9c:	46061281 */ 	sub.s	$f10,$f2,$f6
/*  f124da0:	46005102 */ 	mul.s	$f4,$f10,$f0
/*  f124da4:	46044180 */ 	add.s	$f6,$f8,$f4
/*  f124da8:	e7a6016c */ 	swc1	$f6,0x16c($sp)
/*  f124dac:	c4680018 */ 	lwc1	$f8,0x18($v1)
/*  f124db0:	c4500018 */ 	lwc1	$f16,0x18($v0)
/*  f124db4:	c56a0018 */ 	lwc1	$f10,0x18($t3)
/*  f124db8:	46088101 */ 	sub.s	$f4,$f16,$f8
/*  f124dbc:	46002182 */ 	mul.s	$f6,$f4,$f0
/*  f124dc0:	46065200 */ 	add.s	$f8,$f10,$f6
/*  f124dc4:	e7a80168 */ 	swc1	$f8,0x168($sp)
/*  f124dc8:	c46a001c */ 	lwc1	$f10,0x1c($v1)
/*  f124dcc:	c452001c */ 	lwc1	$f18,0x1c($v0)
/*  f124dd0:	c564001c */ 	lwc1	$f4,0x1c($t3)
/*  f124dd4:	460a9181 */ 	sub.s	$f6,$f18,$f10
/*  f124dd8:	46003202 */ 	mul.s	$f8,$f6,$f0
/*  f124ddc:	46082280 */ 	add.s	$f10,$f4,$f8
/*  f124de0:	460c7182 */ 	mul.s	$f6,$f14,$f12
/*  f124de4:	e7aa0164 */ 	swc1	$f10,0x164($sp)
/*  f124de8:	4459f800 */ 	cfc1	$t9,$31
/*  f124dec:	44cef800 */ 	ctc1	$t6,$31
/*  f124df0:	00000000 */ 	nop
/*  f124df4:	46003124 */ 	cvt.w.s	$f4,$f6
/*  f124df8:	444ef800 */ 	cfc1	$t6,$31
/*  f124dfc:	00000000 */ 	nop
/*  f124e00:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f124e04:	11c00012 */ 	beqz	$t6,.L0f124e50
/*  f124e08:	3c014f00 */ 	lui	$at,0x4f00
/*  f124e0c:	44812000 */ 	mtc1	$at,$f4
/*  f124e10:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f124e14:	46043101 */ 	sub.s	$f4,$f6,$f4
/*  f124e18:	44cef800 */ 	ctc1	$t6,$31
/*  f124e1c:	00000000 */ 	nop
/*  f124e20:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f124e24:	444ef800 */ 	cfc1	$t6,$31
/*  f124e28:	00000000 */ 	nop
/*  f124e2c:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f124e30:	15c00005 */ 	bnez	$t6,.L0f124e48
/*  f124e34:	00000000 */ 	nop
/*  f124e38:	440e2000 */ 	mfc1	$t6,$f4
/*  f124e3c:	3c018000 */ 	lui	$at,0x8000
/*  f124e40:	10000007 */ 	b	.L0f124e60
/*  f124e44:	01c17025 */ 	or	$t6,$t6,$at
.L0f124e48:
/*  f124e48:	10000005 */ 	b	.L0f124e60
/*  f124e4c:	240effff */ 	addiu	$t6,$zero,-1
.L0f124e50:
/*  f124e50:	440e2000 */ 	mfc1	$t6,$f4
/*  f124e54:	00000000 */ 	nop
/*  f124e58:	05c0fffb */ 	bltz	$t6,.L0f124e48
/*  f124e5c:	00000000 */ 	nop
.L0f124e60:
/*  f124e60:	44d9f800 */ 	ctc1	$t9,$31
/*  f124e64:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f124e68:	afae0160 */ 	sw	$t6,0x160($sp)
/*  f124e6c:	460c1202 */ 	mul.s	$f8,$f2,$f12
/*  f124e70:	4458f800 */ 	cfc1	$t8,$31
/*  f124e74:	44cff800 */ 	ctc1	$t7,$31
/*  f124e78:	00000000 */ 	nop
/*  f124e7c:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f124e80:	444ff800 */ 	cfc1	$t7,$31
/*  f124e84:	00000000 */ 	nop
/*  f124e88:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f124e8c:	11e00012 */ 	beqz	$t7,.L0f124ed8
/*  f124e90:	3c014f00 */ 	lui	$at,0x4f00
/*  f124e94:	44815000 */ 	mtc1	$at,$f10
/*  f124e98:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f124e9c:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f124ea0:	44cff800 */ 	ctc1	$t7,$31
/*  f124ea4:	00000000 */ 	nop
/*  f124ea8:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f124eac:	444ff800 */ 	cfc1	$t7,$31
/*  f124eb0:	00000000 */ 	nop
/*  f124eb4:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f124eb8:	15e00005 */ 	bnez	$t7,.L0f124ed0
/*  f124ebc:	00000000 */ 	nop
/*  f124ec0:	440f5000 */ 	mfc1	$t7,$f10
/*  f124ec4:	3c018000 */ 	lui	$at,0x8000
/*  f124ec8:	10000007 */ 	b	.L0f124ee8
/*  f124ecc:	01e17825 */ 	or	$t7,$t7,$at
.L0f124ed0:
/*  f124ed0:	10000005 */ 	b	.L0f124ee8
/*  f124ed4:	240fffff */ 	addiu	$t7,$zero,-1
.L0f124ed8:
/*  f124ed8:	440f5000 */ 	mfc1	$t7,$f10
/*  f124edc:	00000000 */ 	nop
/*  f124ee0:	05e0fffb */ 	bltz	$t7,.L0f124ed0
/*  f124ee4:	00000000 */ 	nop
.L0f124ee8:
/*  f124ee8:	3c014780 */ 	lui	$at,0x4780
/*  f124eec:	44d8f800 */ 	ctc1	$t8,$31
/*  f124ef0:	44810000 */ 	mtc1	$at,$f0
/*  f124ef4:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f124ef8:	afaf015c */ 	sw	$t7,0x15c($sp)
/*  f124efc:	46008182 */ 	mul.s	$f6,$f16,$f0
/*  f124f00:	4459f800 */ 	cfc1	$t9,$31
/*  f124f04:	44cef800 */ 	ctc1	$t6,$31
/*  f124f08:	00000000 */ 	nop
/*  f124f0c:	46003124 */ 	cvt.w.s	$f4,$f6
/*  f124f10:	444ef800 */ 	cfc1	$t6,$31
/*  f124f14:	00000000 */ 	nop
/*  f124f18:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f124f1c:	11c00012 */ 	beqz	$t6,.L0f124f68
/*  f124f20:	3c014f00 */ 	lui	$at,0x4f00
/*  f124f24:	44812000 */ 	mtc1	$at,$f4
/*  f124f28:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f124f2c:	46043101 */ 	sub.s	$f4,$f6,$f4
/*  f124f30:	44cef800 */ 	ctc1	$t6,$31
/*  f124f34:	00000000 */ 	nop
/*  f124f38:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f124f3c:	444ef800 */ 	cfc1	$t6,$31
/*  f124f40:	00000000 */ 	nop
/*  f124f44:	31ce0078 */ 	andi	$t6,$t6,0x78
/*  f124f48:	15c00005 */ 	bnez	$t6,.L0f124f60
/*  f124f4c:	00000000 */ 	nop
/*  f124f50:	440e2000 */ 	mfc1	$t6,$f4
/*  f124f54:	3c018000 */ 	lui	$at,0x8000
/*  f124f58:	10000007 */ 	b	.L0f124f78
/*  f124f5c:	01c17025 */ 	or	$t6,$t6,$at
.L0f124f60:
/*  f124f60:	10000005 */ 	b	.L0f124f78
/*  f124f64:	240effff */ 	addiu	$t6,$zero,-1
.L0f124f68:
/*  f124f68:	440e2000 */ 	mfc1	$t6,$f4
/*  f124f6c:	00000000 */ 	nop
/*  f124f70:	05c0fffb */ 	bltz	$t6,.L0f124f60
/*  f124f74:	00000000 */ 	nop
.L0f124f78:
/*  f124f78:	44d9f800 */ 	ctc1	$t9,$31
/*  f124f7c:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f124f80:	afae0158 */ 	sw	$t6,0x158($sp)
/*  f124f84:	46009202 */ 	mul.s	$f8,$f18,$f0
/*  f124f88:	4458f800 */ 	cfc1	$t8,$31
/*  f124f8c:	44cff800 */ 	ctc1	$t7,$31
/*  f124f90:	00000000 */ 	nop
/*  f124f94:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f124f98:	444ff800 */ 	cfc1	$t7,$31
/*  f124f9c:	00000000 */ 	nop
/*  f124fa0:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f124fa4:	11e00012 */ 	beqz	$t7,.L0f124ff0
/*  f124fa8:	3c014f00 */ 	lui	$at,0x4f00
/*  f124fac:	44815000 */ 	mtc1	$at,$f10
/*  f124fb0:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f124fb4:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f124fb8:	44cff800 */ 	ctc1	$t7,$31
/*  f124fbc:	00000000 */ 	nop
/*  f124fc0:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f124fc4:	444ff800 */ 	cfc1	$t7,$31
/*  f124fc8:	00000000 */ 	nop
/*  f124fcc:	31ef0078 */ 	andi	$t7,$t7,0x78
/*  f124fd0:	15e00005 */ 	bnez	$t7,.L0f124fe8
/*  f124fd4:	00000000 */ 	nop
/*  f124fd8:	440f5000 */ 	mfc1	$t7,$f10
/*  f124fdc:	3c018000 */ 	lui	$at,0x8000
/*  f124fe0:	10000007 */ 	b	.L0f125000
/*  f124fe4:	01e17825 */ 	or	$t7,$t7,$at
.L0f124fe8:
/*  f124fe8:	10000005 */ 	b	.L0f125000
/*  f124fec:	240fffff */ 	addiu	$t7,$zero,-1
.L0f124ff0:
/*  f124ff0:	440f5000 */ 	mfc1	$t7,$f10
/*  f124ff4:	00000000 */ 	nop
/*  f124ff8:	05e0fffb */ 	bltz	$t7,.L0f124fe8
/*  f124ffc:	00000000 */ 	nop
.L0f125000:
/*  f125000:	8fb904d8 */ 	lw	$t9,0x4d8($sp)
/*  f125004:	afaf0154 */ 	sw	$t7,0x154($sp)
/*  f125008:	44d8f800 */ 	ctc1	$t8,$31
/*  f12500c:	c4440028 */ 	lwc1	$f4,0x28($v0)
/*  f125010:	c7260028 */ 	lwc1	$f6,0x28($t9)
/*  f125014:	3c013e80 */ 	lui	$at,0x3e80
/*  f125018:	44815000 */ 	mtc1	$at,$f10
/*  f12501c:	46043201 */ 	sub.s	$f8,$f6,$f4
/*  f125020:	c7a40170 */ 	lwc1	$f4,0x170($sp)
/*  f125024:	460a4182 */ 	mul.s	$f6,$f8,$f10
/*  f125028:	460e2201 */ 	sub.s	$f8,$f4,$f14
/*  f12502c:	0fc54be8 */ 	jal	func0f152fa0
/*  f125030:	46064303 */ 	div.s	$f12,$f8,$f6
/*  f125034:	8fa304d4 */ 	lw	$v1,0x4d4($sp)
/*  f125038:	afa20150 */ 	sw	$v0,0x150($sp)
/*  f12503c:	c7aa016c */ 	lwc1	$f10,0x16c($sp)
/*  f125040:	c4640014 */ 	lwc1	$f4,0x14($v1)
/*  f125044:	8fae04d8 */ 	lw	$t6,0x4d8($sp)
/*  f125048:	3c013e80 */ 	lui	$at,0x3e80
/*  f12504c:	46045201 */ 	sub.s	$f8,$f10,$f4
/*  f125050:	c46a0028 */ 	lwc1	$f10,0x28($v1)
/*  f125054:	c5c60028 */ 	lwc1	$f6,0x28($t6)
/*  f125058:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f12505c:	44813000 */ 	mtc1	$at,$f6
/*  f125060:	00000000 */ 	nop
/*  f125064:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f125068:	0fc54be8 */ 	jal	func0f152fa0
/*  f12506c:	460a4303 */ 	div.s	$f12,$f8,$f10
/*  f125070:	8fa304d4 */ 	lw	$v1,0x4d4($sp)
/*  f125074:	afa2014c */ 	sw	$v0,0x14c($sp)
/*  f125078:	c7a40168 */ 	lwc1	$f4,0x168($sp)
/*  f12507c:	c4660018 */ 	lwc1	$f6,0x18($v1)
/*  f125080:	8fb804d8 */ 	lw	$t8,0x4d8($sp)
/*  f125084:	3c013e80 */ 	lui	$at,0x3e80
/*  f125088:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f12508c:	c4640028 */ 	lwc1	$f4,0x28($v1)
/*  f125090:	c70a0028 */ 	lwc1	$f10,0x28($t8)
/*  f125094:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f125098:	44815000 */ 	mtc1	$at,$f10
/*  f12509c:	00000000 */ 	nop
/*  f1250a0:	460a3102 */ 	mul.s	$f4,$f6,$f10
/*  f1250a4:	0fc54be8 */ 	jal	func0f152fa0
/*  f1250a8:	46044303 */ 	div.s	$f12,$f8,$f4
/*  f1250ac:	8fa304d4 */ 	lw	$v1,0x4d4($sp)
/*  f1250b0:	afa20148 */ 	sw	$v0,0x148($sp)
/*  f1250b4:	c7a60164 */ 	lwc1	$f6,0x164($sp)
/*  f1250b8:	c46a001c */ 	lwc1	$f10,0x1c($v1)
/*  f1250bc:	8faf04d8 */ 	lw	$t7,0x4d8($sp)
/*  f1250c0:	3c013e80 */ 	lui	$at,0x3e80
/*  f1250c4:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f1250c8:	c4660028 */ 	lwc1	$f6,0x28($v1)
/*  f1250cc:	c5e40028 */ 	lwc1	$f4,0x28($t7)
/*  f1250d0:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f1250d4:	44812000 */ 	mtc1	$at,$f4
/*  f1250d8:	00000000 */ 	nop
/*  f1250dc:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f1250e0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1250e4:	46064303 */ 	div.s	$f12,$f8,$f6
/*  f1250e8:	8fa304dc */ 	lw	$v1,0x4dc($sp)
/*  f1250ec:	8fb904d4 */ 	lw	$t9,0x4d4($sp)
/*  f1250f0:	afa20144 */ 	sw	$v0,0x144($sp)
/*  f1250f4:	c46a0010 */ 	lwc1	$f10,0x10($v1)
/*  f1250f8:	c7240010 */ 	lwc1	$f4,0x10($t9)
/*  f1250fc:	c466002c */ 	lwc1	$f6,0x2c($v1)
/*  f125100:	3c013e80 */ 	lui	$at,0x3e80
/*  f125104:	46045201 */ 	sub.s	$f8,$f10,$f4
/*  f125108:	c72a002c */ 	lwc1	$f10,0x2c($t9)
/*  f12510c:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f125110:	44813000 */ 	mtc1	$at,$f6
/*  f125114:	00000000 */ 	nop
/*  f125118:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f12511c:	0fc54be8 */ 	jal	func0f152fa0
/*  f125120:	460a4303 */ 	div.s	$f12,$f8,$f10
/*  f125124:	8fa304dc */ 	lw	$v1,0x4dc($sp)
/*  f125128:	8fae04d4 */ 	lw	$t6,0x4d4($sp)
/*  f12512c:	afa20130 */ 	sw	$v0,0x130($sp)
/*  f125130:	afa20140 */ 	sw	$v0,0x140($sp)
/*  f125134:	c4640014 */ 	lwc1	$f4,0x14($v1)
/*  f125138:	c5c60014 */ 	lwc1	$f6,0x14($t6)
/*  f12513c:	c46a002c */ 	lwc1	$f10,0x2c($v1)
/*  f125140:	3c013e80 */ 	lui	$at,0x3e80
/*  f125144:	46062201 */ 	sub.s	$f8,$f4,$f6
/*  f125148:	c5c4002c */ 	lwc1	$f4,0x2c($t6)
/*  f12514c:	46045181 */ 	sub.s	$f6,$f10,$f4
/*  f125150:	44815000 */ 	mtc1	$at,$f10
/*  f125154:	00000000 */ 	nop
/*  f125158:	460a3102 */ 	mul.s	$f4,$f6,$f10
/*  f12515c:	0fc54be8 */ 	jal	func0f152fa0
/*  f125160:	46044303 */ 	div.s	$f12,$f8,$f4
/*  f125164:	8fb804dc */ 	lw	$t8,0x4dc($sp)
/*  f125168:	8faf04d4 */ 	lw	$t7,0x4d4($sp)
/*  f12516c:	afa2012c */ 	sw	$v0,0x12c($sp)
/*  f125170:	afa2013c */ 	sw	$v0,0x13c($sp)
/*  f125174:	c7060018 */ 	lwc1	$f6,0x18($t8)
/*  f125178:	c5ea0018 */ 	lwc1	$f10,0x18($t7)
/*  f12517c:	c704002c */ 	lwc1	$f4,0x2c($t8)
/*  f125180:	3c013e80 */ 	lui	$at,0x3e80
/*  f125184:	460a3201 */ 	sub.s	$f8,$f6,$f10
/*  f125188:	c5e6002c */ 	lwc1	$f6,0x2c($t7)
/*  f12518c:	46062281 */ 	sub.s	$f10,$f4,$f6
/*  f125190:	44812000 */ 	mtc1	$at,$f4
/*  f125194:	00000000 */ 	nop
/*  f125198:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f12519c:	0fc54be8 */ 	jal	func0f152fa0
/*  f1251a0:	46064303 */ 	div.s	$f12,$f8,$f6
/*  f1251a4:	8fb904dc */ 	lw	$t9,0x4dc($sp)
/*  f1251a8:	8fae04d4 */ 	lw	$t6,0x4d4($sp)
/*  f1251ac:	3c013e80 */ 	lui	$at,0x3e80
/*  f1251b0:	c72a001c */ 	lwc1	$f10,0x1c($t9)
/*  f1251b4:	c5c4001c */ 	lwc1	$f4,0x1c($t6)
/*  f1251b8:	c726002c */ 	lwc1	$f6,0x2c($t9)
/*  f1251bc:	46045201 */ 	sub.s	$f8,$f10,$f4
/*  f1251c0:	c5ca002c */ 	lwc1	$f10,0x2c($t6)
/*  f1251c4:	afa20138 */ 	sw	$v0,0x138($sp)
/*  f1251c8:	afa20128 */ 	sw	$v0,0x128($sp)
/*  f1251cc:	460a3101 */ 	sub.s	$f4,$f6,$f10
/*  f1251d0:	44813000 */ 	mtc1	$at,$f6
/*  f1251d4:	00000000 */ 	nop
/*  f1251d8:	46062282 */ 	mul.s	$f10,$f4,$f6
/*  f1251dc:	0fc54be8 */ 	jal	func0f152fa0
/*  f1251e0:	460a4303 */ 	div.s	$f12,$f8,$f10
/*  f1251e4:	8fab015c */ 	lw	$t3,0x15c($sp)
/*  f1251e8:	8faa0160 */ 	lw	$t2,0x160($sp)
/*  f1251ec:	3c09ffff */ 	lui	$t1,0xffff
/*  f1251f0:	02001825 */ 	or	$v1,$s0,$zero
/*  f1251f4:	01697824 */ 	and	$t7,$t3,$t1
/*  f1251f8:	8fac0128 */ 	lw	$t4,0x128($sp)
/*  f1251fc:	8fad0138 */ 	lw	$t5,0x138($sp)
/*  f125200:	8fbf0158 */ 	lw	$ra,0x158($sp)
/*  f125204:	000fcc02 */ 	srl	$t9,$t7,0x10
/*  f125208:	0149c024 */ 	and	$t8,$t2,$t1
/*  f12520c:	3c08b400 */ 	lui	$t0,0xb400
/*  f125210:	03197025 */ 	or	$t6,$t8,$t9
/*  f125214:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125218:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f12521c:	ac680000 */ 	sw	$t0,0x0($v1)
/*  f125220:	02002025 */ 	or	$a0,$s0,$zero
/*  f125224:	3c0fb200 */ 	lui	$t7,0xb200
/*  f125228:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*  f12522c:	8fb90154 */ 	lw	$t9,0x154($sp)
/*  f125230:	03e9c024 */ 	and	$t8,$ra,$t1
/*  f125234:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125238:	03297024 */ 	and	$t6,$t9,$t1
/*  f12523c:	000e7c02 */ 	srl	$t7,$t6,0x10
/*  f125240:	030fc825 */ 	or	$t9,$t8,$t7
/*  f125244:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f125248:	02002825 */ 	or	$a1,$s0,$zero
/*  f12524c:	aca80000 */ 	sw	$t0,0x0($a1)
/*  f125250:	8faf014c */ 	lw	$t7,0x14c($sp)
/*  f125254:	8fae0150 */ 	lw	$t6,0x150($sp)
/*  f125258:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12525c:	01e9c824 */ 	and	$t9,$t7,$t1
/*  f125260:	01c9c024 */ 	and	$t8,$t6,$t1
/*  f125264:	00197402 */ 	srl	$t6,$t9,0x10
/*  f125268:	030e7825 */ 	or	$t7,$t8,$t6
/*  f12526c:	acaf0004 */ 	sw	$t7,0x4($a1)
/*  f125270:	3c05b200 */ 	lui	$a1,0xb200
/*  f125274:	02003025 */ 	or	$a2,$s0,$zero
/*  f125278:	acc50000 */ 	sw	$a1,0x0($a2)
/*  f12527c:	8fae0144 */ 	lw	$t6,0x144($sp)
/*  f125280:	8fb90148 */ 	lw	$t9,0x148($sp)
/*  f125284:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125288:	01c97824 */ 	and	$t7,$t6,$t1
/*  f12528c:	0329c024 */ 	and	$t8,$t9,$t1
/*  f125290:	000fcc02 */ 	srl	$t9,$t7,0x10
/*  f125294:	03197025 */ 	or	$t6,$t8,$t9
/*  f125298:	acce0004 */ 	sw	$t6,0x4($a2)
/*  f12529c:	02001825 */ 	or	$v1,$s0,$zero
/*  f1252a0:	3179ffff */ 	andi	$t9,$t3,0xffff
/*  f1252a4:	000ac400 */ 	sll	$t8,$t2,0x10
/*  f1252a8:	03197025 */ 	or	$t6,$t8,$t9
/*  f1252ac:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1252b0:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f1252b4:	ac680000 */ 	sw	$t0,0x0($v1)
/*  f1252b8:	02002025 */ 	or	$a0,$s0,$zero
/*  f1252bc:	ac850000 */ 	sw	$a1,0x0($a0)
/*  f1252c0:	8fb90154 */ 	lw	$t9,0x154($sp)
/*  f1252c4:	001fc400 */ 	sll	$t8,$ra,0x10
/*  f1252c8:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1252cc:	332effff */ 	andi	$t6,$t9,0xffff
/*  f1252d0:	030e7825 */ 	or	$t7,$t8,$t6
/*  f1252d4:	ac8f0004 */ 	sw	$t7,0x4($a0)
/*  f1252d8:	02003825 */ 	or	$a3,$s0,$zero
/*  f1252dc:	ace80000 */ 	sw	$t0,0x0($a3)
/*  f1252e0:	8faf014c */ 	lw	$t7,0x14c($sp)
/*  f1252e4:	8fb80150 */ 	lw	$t8,0x150($sp)
/*  f1252e8:	8faa0140 */ 	lw	$t2,0x140($sp)
/*  f1252ec:	31f9ffff */ 	andi	$t9,$t7,0xffff
/*  f1252f0:	00187400 */ 	sll	$t6,$t8,0x10
/*  f1252f4:	8fa8013c */ 	lw	$t0,0x13c($sp)
/*  f1252f8:	01d9c025 */ 	or	$t8,$t6,$t9
/*  f1252fc:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125300:	acf80004 */ 	sw	$t8,0x4($a3)
/*  f125304:	02001825 */ 	or	$v1,$s0,$zero
/*  f125308:	3c0fb200 */ 	lui	$t7,0xb200
/*  f12530c:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f125310:	8faf0144 */ 	lw	$t7,0x144($sp)
/*  f125314:	8fb90148 */ 	lw	$t9,0x148($sp)
/*  f125318:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12531c:	31eeffff */ 	andi	$t6,$t7,0xffff
/*  f125320:	0019c400 */ 	sll	$t8,$t9,0x10
/*  f125324:	030ec825 */ 	or	$t9,$t8,$t6
/*  f125328:	0109c024 */ 	and	$t8,$t0,$t1
/*  f12532c:	ac790004 */ 	sw	$t9,0x4($v1)
/*  f125330:	00187402 */ 	srl	$t6,$t8,0x10
/*  f125334:	01497824 */ 	and	$t7,$t2,$t1
/*  f125338:	01eec825 */ 	or	$t9,$t7,$t6
/*  f12533c:	02002025 */ 	or	$a0,$s0,$zero
/*  f125340:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125344:	3c1fb400 */ 	lui	$ra,0xb400
/*  f125348:	ac990004 */ 	sw	$t9,0x4($a0)
/*  f12534c:	02002825 */ 	or	$a1,$s0,$zero
/*  f125350:	00493024 */ 	and	$a2,$v0,$t1
/*  f125354:	ac9f0000 */ 	sw	$ra,0x0($a0)
/*  f125358:	00067c02 */ 	srl	$t7,$a2,0x10
/*  f12535c:	01a97024 */ 	and	$t6,$t5,$t1
/*  f125360:	01cfc825 */ 	or	$t9,$t6,$t7
/*  f125364:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125368:	3c18b200 */ 	lui	$t8,0xb200
/*  f12536c:	acb80000 */ 	sw	$t8,0x0($a1)
/*  f125370:	acb90004 */ 	sw	$t9,0x4($a1)
/*  f125374:	02001825 */ 	or	$v1,$s0,$zero
/*  f125378:	ac7f0000 */ 	sw	$ra,0x0($v1)
/*  f12537c:	8fae012c */ 	lw	$t6,0x12c($sp)
/*  f125380:	8fb80130 */ 	lw	$t8,0x130($sp)
/*  f125384:	01e03025 */ 	or	$a2,$t7,$zero
/*  f125388:	01c9c824 */ 	and	$t9,$t6,$t1
/*  f12538c:	03097824 */ 	and	$t7,$t8,$t1
/*  f125390:	0019c402 */ 	srl	$t8,$t9,0x10
/*  f125394:	01f87025 */ 	or	$t6,$t7,$t8
/*  f125398:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12539c:	02002025 */ 	or	$a0,$s0,$zero
/*  f1253a0:	01897824 */ 	and	$t7,$t4,$t1
/*  f1253a4:	ac6e0004 */ 	sw	$t6,0x4($v1)
/*  f1253a8:	01e6c025 */ 	or	$t8,$t7,$a2
/*  f1253ac:	3c19b200 */ 	lui	$t9,0xb200
/*  f1253b0:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f1253b4:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1253b8:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f1253bc:	02002825 */ 	or	$a1,$s0,$zero
/*  f1253c0:	000acc00 */ 	sll	$t9,$t2,0x10
/*  f1253c4:	310fffff */ 	andi	$t7,$t0,0xffff
/*  f1253c8:	032fc025 */ 	or	$t8,$t9,$t7
/*  f1253cc:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1253d0:	acb80004 */ 	sw	$t8,0x4($a1)
/*  f1253d4:	acbf0000 */ 	sw	$ra,0x0($a1)
/*  f1253d8:	02005825 */ 	or	$t3,$s0,$zero
/*  f1253dc:	304fffff */ 	andi	$t7,$v0,0xffff
/*  f1253e0:	000dcc00 */ 	sll	$t9,$t5,0x10
/*  f1253e4:	032fc025 */ 	or	$t8,$t9,$t7
/*  f1253e8:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1253ec:	3c1fb200 */ 	lui	$ra,0xb200
/*  f1253f0:	ad7f0000 */ 	sw	$ra,0x0($t3)
/*  f1253f4:	ad780004 */ 	sw	$t8,0x4($t3)
/*  f1253f8:	02003825 */ 	or	$a3,$s0,$zero
/*  f1253fc:	3c0eb400 */ 	lui	$t6,0xb400
/*  f125400:	acee0000 */ 	sw	$t6,0x0($a3)
/*  f125404:	8fae012c */ 	lw	$t6,0x12c($sp)
/*  f125408:	8faf0130 */ 	lw	$t7,0x130($sp)
/*  f12540c:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f125410:	31d9ffff */ 	andi	$t9,$t6,0xffff
/*  f125414:	000fc400 */ 	sll	$t8,$t7,0x10
/*  f125418:	03197825 */ 	or	$t7,$t8,$t9
/*  f12541c:	acef0004 */ 	sw	$t7,0x4($a3)
/*  f125420:	3059ffff */ 	andi	$t9,$v0,0xffff
/*  f125424:	02004025 */ 	or	$t0,$s0,$zero
/*  f125428:	000cc400 */ 	sll	$t8,$t4,0x10
/*  f12542c:	03197825 */ 	or	$t7,$t8,$t9
/*  f125430:	3c013d00 */ 	lui	$at,0x3d00
/*  f125434:	ad0f0004 */ 	sw	$t7,0x4($t0)
/*  f125438:	ad1f0000 */ 	sw	$ra,0x0($t0)
/*  f12543c:	44817000 */ 	mtc1	$at,$f14
/*  f125440:	c7a40364 */ 	lwc1	$f4,0x364($sp)
/*  f125444:	c7a80368 */ 	lwc1	$f8,0x368($sp)
/*  f125448:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f12544c:	460e2182 */ 	mul.s	$f6,$f4,$f14
/*  f125450:	c7a403ac */ 	lwc1	$f4,0x3ac($sp)
/*  f125454:	27a20204 */ 	addiu	$v0,$sp,0x204
/*  f125458:	460e4282 */ 	mul.s	$f10,$f8,$f14
/*  f12545c:	27a501f4 */ 	addiu	$a1,$sp,0x1f4
/*  f125460:	27a402d4 */ 	addiu	$a0,$sp,0x2d4
/*  f125464:	27a60214 */ 	addiu	$a2,$sp,0x214
/*  f125468:	e7a60234 */ 	swc1	$f6,0x234($sp)
/*  f12546c:	460e2182 */ 	mul.s	$f6,$f4,$f14
/*  f125470:	27a302f4 */ 	addiu	$v1,$sp,0x2f4
/*  f125474:	e7aa0238 */ 	swc1	$f10,0x238($sp)
/*  f125478:	3c013f80 */ 	lui	$at,0x3f80
/*  f12547c:	e7a6023c */ 	swc1	$f6,0x23c($sp)
.L0f125480:
/*  f125480:	c4800000 */ 	lwc1	$f0,0x0($a0)
/*  f125484:	4600a03e */ 	c.le.s	$f20,$f0
/*  f125488:	00000000 */ 	nop
/*  f12548c:	45020004 */ 	bc1fl	.L0f1254a0
/*  f125490:	46000307 */ 	neg.s	$f12,$f0
/*  f125494:	10000002 */ 	b	.L0f1254a0
/*  f125498:	46000306 */ 	mov.s	$f12,$f0
/*  f12549c:	46000307 */ 	neg.s	$f12,$f0
.L0f1254a0:
/*  f1254a0:	c4620000 */ 	lwc1	$f2,0x0($v1)
/*  f1254a4:	460e6202 */ 	mul.s	$f8,$f12,$f14
/*  f1254a8:	4602a03e */ 	c.le.s	$f20,$f2
/*  f1254ac:	00000000 */ 	nop
/*  f1254b0:	45000003 */ 	bc1f	.L0f1254c0
/*  f1254b4:	e4c80000 */ 	swc1	$f8,0x0($a2)
/*  f1254b8:	10000002 */ 	b	.L0f1254c4
/*  f1254bc:	46001306 */ 	mov.s	$f12,$f2
.L0f1254c0:
/*  f1254c0:	46001307 */ 	neg.s	$f12,$f2
.L0f1254c4:
/*  f1254c4:	460e6282 */ 	mul.s	$f10,$f12,$f14
/*  f1254c8:	24a50004 */ 	addiu	$a1,$a1,0x4
/*  f1254cc:	24630004 */ 	addiu	$v1,$v1,0x4
/*  f1254d0:	24840004 */ 	addiu	$a0,$a0,0x4
/*  f1254d4:	24c60004 */ 	addiu	$a2,$a2,0x4
/*  f1254d8:	14a2ffe9 */ 	bne	$a1,$v0,.L0f125480
/*  f1254dc:	e4aafffc */ 	swc1	$f10,-0x4($a1)
/*  f1254e0:	c7a20214 */ 	lwc1	$f2,0x214($sp)
/*  f1254e4:	c7a40234 */ 	lwc1	$f4,0x234($sp)
/*  f1254e8:	c7ac0218 */ 	lwc1	$f12,0x218($sp)
/*  f1254ec:	46021180 */ 	add.s	$f6,$f2,$f2
/*  f1254f0:	c7aa01f4 */ 	lwc1	$f10,0x1f4($sp)
/*  f1254f4:	c7ae021c */ 	lwc1	$f14,0x21c($sp)
/*  f1254f8:	44811000 */ 	mtc1	$at,$f2
/*  f1254fc:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f125500:	c7a40238 */ 	lwc1	$f4,0x238($sp)
/*  f125504:	3c013a80 */ 	lui	$at,0x3a80
/*  f125508:	460c6180 */ 	add.s	$f6,$f12,$f12
/*  f12550c:	46085000 */ 	add.s	$f0,$f10,$f8
/*  f125510:	c7a801f8 */ 	lwc1	$f8,0x1f8($sp)
/*  f125514:	46062280 */ 	add.s	$f10,$f4,$f6
/*  f125518:	c7a4023c */ 	lwc1	$f4,0x23c($sp)
/*  f12551c:	460e7180 */ 	add.s	$f6,$f14,$f14
/*  f125520:	460a4400 */ 	add.s	$f16,$f8,$f10
/*  f125524:	c7aa01fc */ 	lwc1	$f10,0x1fc($sp)
/*  f125528:	46062200 */ 	add.s	$f8,$f4,$f6
/*  f12552c:	44812000 */ 	mtc1	$at,$f4
/*  f125530:	e7b001d8 */ 	swc1	$f16,0x1d8($sp)
/*  f125534:	4610003c */ 	c.lt.s	$f0,$f16
/*  f125538:	46085480 */ 	add.s	$f18,$f10,$f8
/*  f12553c:	45020004 */ 	bc1fl	.L0f125550
/*  f125540:	4612003c */ 	c.lt.s	$f0,$f18
/*  f125544:	46008006 */ 	mov.s	$f0,$f16
/*  f125548:	e7b001d8 */ 	swc1	$f16,0x1d8($sp)
/*  f12554c:	4612003c */ 	c.lt.s	$f0,$f18
.L0f125550:
/*  f125550:	e7b201dc */ 	swc1	$f18,0x1dc($sp)
/*  f125554:	45000003 */ 	bc1f	.L0f125564
/*  f125558:	00000000 */ 	nop
/*  f12555c:	46009006 */ 	mov.s	$f0,$f18
/*  f125560:	e7b201dc */ 	swc1	$f18,0x1dc($sp)
.L0f125564:
/*  f125564:	46040002 */ 	mul.s	$f0,$f0,$f4
/*  f125568:	4600103c */ 	c.lt.s	$f2,$f0
/*  f12556c:	00000000 */ 	nop
/*  f125570:	45020005 */ 	bc1fl	.L0f125588
/*  f125574:	e7a001d4 */ 	swc1	$f0,0x1d4($sp)
/*  f125578:	46001503 */ 	div.s	$f20,$f2,$f0
/*  f12557c:	10000003 */ 	b	.L0f12558c
/*  f125580:	e7a001d4 */ 	swc1	$f0,0x1d4($sp)
/*  f125584:	e7a001d4 */ 	swc1	$f0,0x1d4($sp)
.L0f125588:
/*  f125588:	46001506 */ 	mov.s	$f20,$f2
.L0f12558c:
/*  f12558c:	c7a60254 */ 	lwc1	$f6,0x254($sp)
/*  f125590:	e7b401c4 */ 	swc1	$f20,0x1c4($sp)
/*  f125594:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f125598:	0fc54be8 */ 	jal	func0f152fa0
/*  f12559c:	00000000 */ 	nop
/*  f1255a0:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1255a4:	c7aa0258 */ 	lwc1	$f10,0x258($sp)
/*  f1255a8:	afa200e0 */ 	sw	$v0,0xe0($sp)
/*  f1255ac:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f1255b0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1255b4:	00000000 */ 	nop
/*  f1255b8:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1255bc:	c7a8025c */ 	lwc1	$f8,0x25c($sp)
/*  f1255c0:	afa200dc */ 	sw	$v0,0xdc($sp)
/*  f1255c4:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f1255c8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1255cc:	00000000 */ 	nop
/*  f1255d0:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1255d4:	c7a40260 */ 	lwc1	$f4,0x260($sp)
/*  f1255d8:	afa200d8 */ 	sw	$v0,0xd8($sp)
/*  f1255dc:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f1255e0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1255e4:	00000000 */ 	nop
/*  f1255e8:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1255ec:	c7a602d4 */ 	lwc1	$f6,0x2d4($sp)
/*  f1255f0:	afa200d4 */ 	sw	$v0,0xd4($sp)
/*  f1255f4:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f1255f8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1255fc:	00000000 */ 	nop
/*  f125600:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f125604:	c7aa02d8 */ 	lwc1	$f10,0x2d8($sp)
/*  f125608:	afa200d0 */ 	sw	$v0,0xd0($sp)
/*  f12560c:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f125610:	0fc54be8 */ 	jal	func0f152fa0
/*  f125614:	00000000 */ 	nop
/*  f125618:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f12561c:	c7a802dc */ 	lwc1	$f8,0x2dc($sp)
/*  f125620:	afa200cc */ 	sw	$v0,0xcc($sp)
/*  f125624:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f125628:	0fc54be8 */ 	jal	func0f152fa0
/*  f12562c:	00000000 */ 	nop
/*  f125630:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f125634:	c7a402e0 */ 	lwc1	$f4,0x2e0($sp)
/*  f125638:	afa200c8 */ 	sw	$v0,0xc8($sp)
/*  f12563c:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f125640:	0fc54be8 */ 	jal	func0f152fa0
/*  f125644:	00000000 */ 	nop
/*  f125648:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f12564c:	c7a602f4 */ 	lwc1	$f6,0x2f4($sp)
/*  f125650:	afa200c4 */ 	sw	$v0,0xc4($sp)
/*  f125654:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f125658:	0fc54be8 */ 	jal	func0f152fa0
/*  f12565c:	00000000 */ 	nop
/*  f125660:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f125664:	c7aa02f8 */ 	lwc1	$f10,0x2f8($sp)
/*  f125668:	afa200b0 */ 	sw	$v0,0xb0($sp)
/*  f12566c:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f125670:	0fc54be8 */ 	jal	func0f152fa0
/*  f125674:	00000000 */ 	nop
/*  f125678:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f12567c:	c7a802fc */ 	lwc1	$f8,0x2fc($sp)
/*  f125680:	afa200ac */ 	sw	$v0,0xac($sp)
/*  f125684:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f125688:	0fc54be8 */ 	jal	func0f152fa0
/*  f12568c:	00000000 */ 	nop
/*  f125690:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f125694:	c7a40300 */ 	lwc1	$f4,0x300($sp)
/*  f125698:	afa200a8 */ 	sw	$v0,0xa8($sp)
/*  f12569c:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f1256a0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1256a4:	00000000 */ 	nop
/*  f1256a8:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1256ac:	c7a60274 */ 	lwc1	$f6,0x274($sp)
/*  f1256b0:	afa200a4 */ 	sw	$v0,0xa4($sp)
/*  f1256b4:	4606a302 */ 	mul.s	$f12,$f20,$f6
/*  f1256b8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1256bc:	00000000 */ 	nop
/*  f1256c0:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1256c4:	c7aa0278 */ 	lwc1	$f10,0x278($sp)
/*  f1256c8:	afa200c0 */ 	sw	$v0,0xc0($sp)
/*  f1256cc:	460aa302 */ 	mul.s	$f12,$f20,$f10
/*  f1256d0:	0fc54be8 */ 	jal	func0f152fa0
/*  f1256d4:	00000000 */ 	nop
/*  f1256d8:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1256dc:	c7a8027c */ 	lwc1	$f8,0x27c($sp)
/*  f1256e0:	afa200bc */ 	sw	$v0,0xbc($sp)
/*  f1256e4:	4608a302 */ 	mul.s	$f12,$f20,$f8
/*  f1256e8:	0fc54be8 */ 	jal	func0f152fa0
/*  f1256ec:	00000000 */ 	nop
/*  f1256f0:	c7b401c4 */ 	lwc1	$f20,0x1c4($sp)
/*  f1256f4:	c7a40280 */ 	lwc1	$f4,0x280($sp)
/*  f1256f8:	afa200b8 */ 	sw	$v0,0xb8($sp)
/*  f1256fc:	4604a302 */ 	mul.s	$f12,$f20,$f4
/*  f125700:	0fc54be8 */ 	jal	func0f152fa0
/*  f125704:	00000000 */ 	nop
/*  f125708:	8fa800b8 */ 	lw	$t0,0xb8($sp)
/*  f12570c:	8fab00d4 */ 	lw	$t3,0xd4($sp)
/*  f125710:	8fbf00e0 */ 	lw	$ra,0xe0($sp)
/*  f125714:	3c0db400 */ 	lui	$t5,0xb400
/*  f125718:	ae0d0000 */ 	sw	$t5,0x0($s0)
/*  f12571c:	8fb800dc */ 	lw	$t8,0xdc($sp)
/*  f125720:	3c09ffff */ 	lui	$t1,0xffff
/*  f125724:	03e97024 */ 	and	$t6,$ra,$t1
/*  f125728:	0309c824 */ 	and	$t9,$t8,$t1
/*  f12572c:	00197c02 */ 	srl	$t7,$t9,0x10
/*  f125730:	01cfc025 */ 	or	$t8,$t6,$t7
/*  f125734:	ae180004 */ 	sw	$t8,0x4($s0)
/*  f125738:	26040008 */ 	addiu	$a0,$s0,0x8
/*  f12573c:	3c19b200 */ 	lui	$t9,0xb200
/*  f125740:	ac990000 */ 	sw	$t9,0x0($a0)
/*  f125744:	8fae00d8 */ 	lw	$t6,0xd8($sp)
/*  f125748:	0169c024 */ 	and	$t8,$t3,$t1
/*  f12574c:	0018cc02 */ 	srl	$t9,$t8,0x10
/*  f125750:	01c97824 */ 	and	$t7,$t6,$t1
/*  f125754:	01f97025 */ 	or	$t6,$t7,$t9
/*  f125758:	ac8e0004 */ 	sw	$t6,0x4($a0)
/*  f12575c:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f125760:	acad0000 */ 	sw	$t5,0x0($a1)
/*  f125764:	8fb900cc */ 	lw	$t9,0xcc($sp)
/*  f125768:	8fb800d0 */ 	lw	$t8,0xd0($sp)
/*  f12576c:	24a60008 */ 	addiu	$a2,$a1,0x8
/*  f125770:	03297024 */ 	and	$t6,$t9,$t1
/*  f125774:	03097824 */ 	and	$t7,$t8,$t1
/*  f125778:	000ec402 */ 	srl	$t8,$t6,0x10
/*  f12577c:	01f8c825 */ 	or	$t9,$t7,$t8
/*  f125780:	acb90004 */ 	sw	$t9,0x4($a1)
/*  f125784:	8fac00c4 */ 	lw	$t4,0xc4($sp)
/*  f125788:	3c0eb200 */ 	lui	$t6,0xb200
/*  f12578c:	acce0000 */ 	sw	$t6,0x0($a2)
/*  f125790:	8faf00c8 */ 	lw	$t7,0xc8($sp)
/*  f125794:	0189c824 */ 	and	$t9,$t4,$t1
/*  f125798:	00197402 */ 	srl	$t6,$t9,0x10
/*  f12579c:	01e9c024 */ 	and	$t8,$t7,$t1
/*  f1257a0:	030e7825 */ 	or	$t7,$t8,$t6
/*  f1257a4:	accf0004 */ 	sw	$t7,0x4($a2)
/*  f1257a8:	24c30008 */ 	addiu	$v1,$a2,0x8
/*  f1257ac:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*  f1257b0:	8fae00dc */ 	lw	$t6,0xdc($sp)
/*  f1257b4:	001fc400 */ 	sll	$t8,$ra,0x10
/*  f1257b8:	24700008 */ 	addiu	$s0,$v1,0x8
/*  f1257bc:	31cfffff */ 	andi	$t7,$t6,0xffff
/*  f1257c0:	030fc825 */ 	or	$t9,$t8,$t7
/*  f1257c4:	ac790004 */ 	sw	$t9,0x4($v1)
/*  f1257c8:	3c0eb200 */ 	lui	$t6,0xb200
/*  f1257cc:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f1257d0:	8faf00d8 */ 	lw	$t7,0xd8($sp)
/*  f1257d4:	316effff */ 	andi	$t6,$t3,0xffff
/*  f1257d8:	26070008 */ 	addiu	$a3,$s0,0x8
/*  f1257dc:	000fcc00 */ 	sll	$t9,$t7,0x10
/*  f1257e0:	032ec025 */ 	or	$t8,$t9,$t6
/*  f1257e4:	ae180004 */ 	sw	$t8,0x4($s0)
/*  f1257e8:	aced0000 */ 	sw	$t5,0x0($a3)
/*  f1257ec:	8fb800cc */ 	lw	$t8,0xcc($sp)
/*  f1257f0:	8fb900d0 */ 	lw	$t9,0xd0($sp)
/*  f1257f4:	8fab00c0 */ 	lw	$t3,0xc0($sp)
/*  f1257f8:	330fffff */ 	andi	$t7,$t8,0xffff
/*  f1257fc:	00197400 */ 	sll	$t6,$t9,0x10
/*  f125800:	8fa600bc */ 	lw	$a2,0xbc($sp)
/*  f125804:	01cfc825 */ 	or	$t9,$t6,$t7
/*  f125808:	acf90004 */ 	sw	$t9,0x4($a3)
/*  f12580c:	3c0db200 */ 	lui	$t5,0xb200
/*  f125810:	24e30008 */ 	addiu	$v1,$a3,0x8
/*  f125814:	ac6d0000 */ 	sw	$t5,0x0($v1)
/*  f125818:	8fae00c8 */ 	lw	$t6,0xc8($sp)
/*  f12581c:	3199ffff */ 	andi	$t9,$t4,0xffff
/*  f125820:	24640008 */ 	addiu	$a0,$v1,0x8
/*  f125824:	000e7c00 */ 	sll	$t7,$t6,0x10
/*  f125828:	01f9c025 */ 	or	$t8,$t7,$t9
/*  f12582c:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f125830:	3c0eb400 */ 	lui	$t6,0xb400
/*  f125834:	00c9c824 */ 	and	$t9,$a2,$t1
/*  f125838:	0019c402 */ 	srl	$t8,$t9,0x10
/*  f12583c:	ac8e0000 */ 	sw	$t6,0x0($a0)
/*  f125840:	01697824 */ 	and	$t7,$t3,$t1
/*  f125844:	01f87025 */ 	or	$t6,$t7,$t8
/*  f125848:	00497824 */ 	and	$t7,$v0,$t1
/*  f12584c:	ac8e0004 */ 	sw	$t6,0x4($a0)
/*  f125850:	000fc402 */ 	srl	$t8,$t7,0x10
/*  f125854:	0109c824 */ 	and	$t9,$t0,$t1
/*  f125858:	24850008 */ 	addiu	$a1,$a0,0x8
/*  f12585c:	03387025 */ 	or	$t6,$t9,$t8
/*  f125860:	acae0004 */ 	sw	$t6,0x4($a1)
/*  f125864:	acad0000 */ 	sw	$t5,0x0($a1)
/*  f125868:	8fbf00ac */ 	lw	$ra,0xac($sp)
/*  f12586c:	8fad00b0 */ 	lw	$t5,0xb0($sp)
/*  f125870:	00405025 */ 	or	$t2,$v0,$zero
/*  f125874:	24b00008 */ 	addiu	$s0,$a1,0x8
/*  f125878:	8fac00a8 */ 	lw	$t4,0xa8($sp)
/*  f12587c:	8fa700a4 */ 	lw	$a3,0xa4($sp)
/*  f125880:	02001025 */ 	or	$v0,$s0,$zero
/*  f125884:	3c0fb400 */ 	lui	$t7,0xb400
/*  f125888:	03e9c024 */ 	and	$t8,$ra,$t1
/*  f12588c:	00187402 */ 	srl	$t6,$t8,0x10
/*  f125890:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f125894:	01a9c824 */ 	and	$t9,$t5,$t1
/*  f125898:	032e7825 */ 	or	$t7,$t9,$t6
/*  f12589c:	ac4f0004 */ 	sw	$t7,0x4($v0)
/*  f1258a0:	26030008 */ 	addiu	$v1,$s0,0x8
/*  f1258a4:	3c18b200 */ 	lui	$t8,0xb200
/*  f1258a8:	00e97024 */ 	and	$t6,$a3,$t1
/*  f1258ac:	000e7c02 */ 	srl	$t7,$t6,0x10
/*  f1258b0:	ac780000 */ 	sw	$t8,0x0($v1)
/*  f1258b4:	0189c824 */ 	and	$t9,$t4,$t1
/*  f1258b8:	032fc025 */ 	or	$t8,$t9,$t7
/*  f1258bc:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f1258c0:	24700008 */ 	addiu	$s0,$v1,0x8
/*  f1258c4:	3c0eb400 */ 	lui	$t6,0xb400
/*  f1258c8:	ae0e0000 */ 	sw	$t6,0x0($s0)
/*  f1258cc:	000b7c00 */ 	sll	$t7,$t3,0x10
/*  f1258d0:	30d8ffff */ 	andi	$t8,$a2,0xffff
/*  f1258d4:	01f87025 */ 	or	$t6,$t7,$t8
/*  f1258d8:	ae0e0004 */ 	sw	$t6,0x4($s0)
/*  f1258dc:	26050008 */ 	addiu	$a1,$s0,0x8
/*  f1258e0:	3c19b200 */ 	lui	$t9,0xb200
/*  f1258e4:	acb90000 */ 	sw	$t9,0x0($a1)
/*  f1258e8:	314effff */ 	andi	$t6,$t2,0xffff
/*  f1258ec:	0008c400 */ 	sll	$t8,$t0,0x10
/*  f1258f0:	030ec825 */ 	or	$t9,$t8,$t6
/*  f1258f4:	acb90004 */ 	sw	$t9,0x4($a1)
/*  f1258f8:	24a30008 */ 	addiu	$v1,$a1,0x8
/*  f1258fc:	3c0fb400 */ 	lui	$t7,0xb400
/*  f125900:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f125904:	33f9ffff */ 	andi	$t9,$ra,0xffff
/*  f125908:	000d7400 */ 	sll	$t6,$t5,0x10
/*  f12590c:	01d97825 */ 	or	$t7,$t6,$t9
/*  f125910:	ac6f0004 */ 	sw	$t7,0x4($v1)
/*  f125914:	24640008 */ 	addiu	$a0,$v1,0x8
/*  f125918:	3c18b300 */ 	lui	$t8,0xb300
/*  f12591c:	ac980000 */ 	sw	$t8,0x0($a0)
/*  f125920:	000ccc00 */ 	sll	$t9,$t4,0x10
/*  f125924:	30efffff */ 	andi	$t7,$a3,0xffff
/*  f125928:	032fc025 */ 	or	$t8,$t9,$t7
/*  f12592c:	ac980004 */ 	sw	$t8,0x4($a0)
/*  f125930:	24820008 */ 	addiu	$v0,$a0,0x8
.L0f125934:
/*  f125934:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*  f125938:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f12593c:	8fb00020 */ 	lw	$s0,0x20($sp)
/*  f125940:	03e00008 */ 	jr	$ra
/*  f125944:	27bd04d0 */ 	addiu	$sp,$sp,0x4d0
);

GLOBAL_ASM(
glabel func0f125948
/*  f125948:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*  f12594c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f125950:	afa40028 */ 	sw	$a0,0x28($sp)
/*  f125954:	afa5002c */ 	sw	$a1,0x2c($sp)
/*  f125958:	0c002f40 */ 	jal	viGetViewLeft
/*  f12595c:	afa60030 */ 	sw	$a2,0x30($sp)
/*  f125960:	0c002f44 */ 	jal	viGetViewTop
/*  f125964:	afa20024 */ 	sw	$v0,0x24($sp)
/*  f125968:	0c002f22 */ 	jal	viGetViewWidth
/*  f12596c:	afa20020 */ 	sw	$v0,0x20($sp)
/*  f125970:	0c002f26 */ 	jal	viGetViewHeight
/*  f125974:	afa2001c */ 	sw	$v0,0x1c($sp)
/*  f125978:	8fa30024 */ 	lw	$v1,0x24($sp)
/*  f12597c:	8fa4002c */ 	lw	$a0,0x2c($sp)
/*  f125980:	8fae001c */ 	lw	$t6,0x1c($sp)
/*  f125984:	0083082a */ 	slt	$at,$a0,$v1
/*  f125988:	14200020 */ 	bnez	$at,.L0f125a0c
/*  f12598c:	006e7821 */ 	addu	$t7,$v1,$t6
/*  f125990:	008f082a */ 	slt	$at,$a0,$t7
/*  f125994:	1020001d */ 	beqz	$at,.L0f125a0c
/*  f125998:	8fa30020 */ 	lw	$v1,0x20($sp)
/*  f12599c:	8fa50030 */ 	lw	$a1,0x30($sp)
/*  f1259a0:	0062c021 */ 	addu	$t8,$v1,$v0
/*  f1259a4:	00a3082a */ 	slt	$at,$a1,$v1
/*  f1259a8:	14200018 */ 	bnez	$at,.L0f125a0c
/*  f1259ac:	00b8082a */ 	slt	$at,$a1,$t8
/*  f1259b0:	50200017 */ 	beqzl	$at,.L0f125a10
/*  f1259b4:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*  f1259b8:	0fc2d5f6 */ 	jal	currentPlayerGetScreenWidth
/*  f1259bc:	00000000 */ 	nop
/*  f1259c0:	4600010d */ 	trunc.w.s	$f4,$f0
/*  f1259c4:	8fa90030 */ 	lw	$t1,0x30($sp)
/*  f1259c8:	8fab002c */ 	lw	$t3,0x2c($sp)
/*  f1259cc:	3c0e8008 */ 	lui	$t6,%hi(var800844f0)
/*  f1259d0:	44082000 */ 	mfc1	$t0,$f4
/*  f1259d4:	8dce44f0 */ 	lw	$t6,%lo(var800844f0)($t6)
/*  f1259d8:	8fa20028 */ 	lw	$v0,0x28($sp)
/*  f1259dc:	01090019 */ 	multu	$t0,$t1
/*  f1259e0:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f1259e4:	00005012 */ 	mflo	$t2
/*  f1259e8:	014b6021 */ 	addu	$t4,$t2,$t3
/*  f1259ec:	000c6840 */ 	sll	$t5,$t4,0x1
/*  f1259f0:	01ae7821 */ 	addu	$t7,$t5,$t6
/*  f1259f4:	ac4f0008 */ 	sw	$t7,0x8($v0)
/*  f1259f8:	8fb8002c */ 	lw	$t8,0x2c($sp)
/*  f1259fc:	a458000e */ 	sh	$t8,0xe($v0)
/*  f125a00:	8fb90030 */ 	lw	$t9,0x30($sp)
/*  f125a04:	a4480000 */ 	sh	$t0,0x0($v0)
/*  f125a08:	a459000c */ 	sh	$t9,0xc($v0)
.L0f125a0c:
/*  f125a0c:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f125a10:
/*  f125a10:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*  f125a14:	03e00008 */ 	jr	$ra
/*  f125a18:	00000000 */ 	nop
);

f32 func0f125a1c(struct bootbufferthingdeep *arg0)
{
	f32 sum = 0;
	s32 i;

	for (i = 0; i < 8; i++) {
		if (arg0[i].unk00 == 1 && arg0[i].unk02 == 0xfffc) {
			sum += 0.125f;
		}
	}

	return sum;
}

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f125a6c
.late_rodata
glabel var7f1b5108
.word 0x3d888889
.text
/*  f12656c:	27bdfe90 */ 	addiu	$sp,$sp,-368
/*  f126570:	afbf008c */ 	sw	$ra,0x8c($sp)
/*  f126574:	afbe0088 */ 	sw	$s8,0x88($sp)
/*  f126578:	afb70084 */ 	sw	$s7,0x84($sp)
/*  f12657c:	afb60080 */ 	sw	$s6,0x80($sp)
/*  f126580:	afb5007c */ 	sw	$s5,0x7c($sp)
/*  f126584:	afb40078 */ 	sw	$s4,0x78($sp)
/*  f126588:	afb30074 */ 	sw	$s3,0x74($sp)
/*  f12658c:	afb20070 */ 	sw	$s2,0x70($sp)
/*  f126590:	afb1006c */ 	sw	$s1,0x6c($sp)
/*  f126594:	afb00068 */ 	sw	$s0,0x68($sp)
/*  f126598:	f7be0060 */ 	sdc1	$f30,0x60($sp)
/*  f12659c:	f7bc0058 */ 	sdc1	$f28,0x58($sp)
/*  f1265a0:	f7ba0050 */ 	sdc1	$f26,0x50($sp)
/*  f1265a4:	f7b80048 */ 	sdc1	$f24,0x48($sp)
/*  f1265a8:	f7b60040 */ 	sdc1	$f22,0x40($sp)
/*  f1265ac:	f7b40038 */ 	sdc1	$f20,0x38($sp)
/*  f1265b0:	afa40170 */ 	sw	$a0,0x170($sp)
/*  f1265b4:	0fc2d706 */ 	jal	currentPlayerGetMatrix1740
/*  f1265b8:	afa50174 */ 	sw	$a1,0x174($sp)
/*  f1265bc:	0fc2d70e */ 	jal	currentPlayerGetUnk1754
/*  f1265c0:	afa2016c */ 	sw	$v0,0x16c($sp)
/*  f1265c4:	0fc599d3 */ 	jal	skyGetCurrent
/*  f1265c8:	afa20168 */ 	sw	$v0,0x168($sp)
/*  f1265cc:	afa20144 */ 	sw	$v0,0x144($sp)
/*  f1265d0:	904e000b */ 	lbu	$t6,0xb($v0)
/*  f1265d4:	3c0f8008 */ 	lui	$t7,0x8008
/*  f1265d8:	19c00008 */ 	blez	$t6,.PF0f1265fc
/*  f1265dc:	00000000 */ 	nop
/*  f1265e0:	8def4a40 */ 	lw	$t7,0x4a40($t7)
/*  f1265e4:	3c18800a */ 	lui	$t8,0x800a
/*  f1265e8:	11e00004 */ 	beqz	$t7,.PF0f1265fc
/*  f1265ec:	00000000 */ 	nop
/*  f1265f0:	8f18a824 */ 	lw	$t8,-0x57dc($t8)
/*  f1265f4:	13000003 */ 	beqz	$t8,.PF0f126604
/*  f1265f8:	00000000 */ 	nop
.PF0f1265fc:
/*  f1265fc:	10000208 */ 	b	.PF0f126e20
/*  f126600:	8fa20170 */ 	lw	$v0,0x170($sp)
.PF0f126604:
/*  f126604:	0c002e91 */ 	jal	viGetViewLeft
/*  f126608:	00000000 */ 	nop
/*  f12660c:	0c002e95 */ 	jal	viGetViewTop
/*  f126610:	a7a20166 */ 	sh	$v0,0x166($sp)
/*  f126614:	0c002e73 */ 	jal	viGetViewWidth
/*  f126618:	a7a20164 */ 	sh	$v0,0x164($sp)
/*  f12661c:	0c002e77 */ 	jal	viGetViewHeight
/*  f126620:	a7a20162 */ 	sh	$v0,0x162($sp)
/*  f126624:	87b90162 */ 	lh	$t9,0x162($sp)
/*  f126628:	44824000 */ 	mtc1	$v0,$f8
/*  f12662c:	8fa30144 */ 	lw	$v1,0x144($sp)
/*  f126630:	44992000 */ 	mtc1	$t9,$f4
/*  f126634:	468042a0 */ 	cvt.s.w	$f10,$f8
/*  f126638:	a7a20160 */ 	sh	$v0,0x160($sp)
/*  f12663c:	3c14800a */ 	lui	$s4,0x800a
/*  f126640:	3c013f80 */ 	lui	$at,0x3f80
/*  f126644:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f126648:	e7aa0150 */ 	swc1	$f10,0x150($sp)
/*  f12664c:	e7a600c8 */ 	swc1	$f6,0xc8($sp)
/*  f126650:	e7a60154 */ 	swc1	$f6,0x154($sp)
/*  f126654:	8c76000c */ 	lw	$s6,0xc($v1)
/*  f126658:	afa0013c */ 	sw	$zero,0x13c($sp)
/*  f12665c:	9068000b */ 	lbu	$t0,0xb($v1)
/*  f126660:	590001ef */ 	blezl	$t0,.PF0f126e20
/*  f126664:	8fa20170 */ 	lw	$v0,0x170($sp)
/*  f126668:	4480e000 */ 	mtc1	$zero,$f28
/*  f12666c:	4481d000 */ 	mtc1	$at,$f26
/*  f126670:	26943988 */ 	addiu	$s4,$s4,0x3988
/*  f126674:	c6d00004 */ 	lwc1	$f16,0x4($s6)
.PF0f126678:
/*  f126678:	8fac0174 */ 	lw	$t4,0x174($sp)
/*  f12667c:	e6900000 */ 	swc1	$f16,0x0($s4)
/*  f126680:	c6d20008 */ 	lwc1	$f18,0x8($s6)
/*  f126684:	e6920004 */ 	swc1	$f18,0x4($s4)
/*  f126688:	c6c4000c */ 	lwc1	$f4,0xc($s6)
/*  f12668c:	e6840008 */ 	swc1	$f4,0x8($s4)
/*  f126690:	92c90001 */ 	lbu	$t1,0x1($s6)
/*  f126694:	8fa4016c */ 	lw	$a0,0x16c($sp)
/*  f126698:	a3a90148 */ 	sb	$t1,0x148($sp)
/*  f12669c:	92ca0002 */ 	lbu	$t2,0x2($s6)
/*  f1266a0:	a3aa0149 */ 	sb	$t2,0x149($sp)
/*  f1266a4:	92cb0003 */ 	lbu	$t3,0x3($s6)
/*  f1266a8:	158001d2 */ 	bnez	$t4,.PF0f126df4
/*  f1266ac:	a3ab014a */ 	sb	$t3,0x14a($sp)
/*  f1266b0:	0c00563d */ 	jal	mtx4TransformVecInPlace
/*  f1266b4:	02802825 */ 	move	$a1,$s4
/*  f1266b8:	8fa40168 */ 	lw	$a0,0x168($sp)
/*  f1266bc:	0c00563d */ 	jal	mtx4TransformVecInPlace
/*  f1266c0:	02802825 */ 	move	$a1,$s4
/*  f1266c4:	c6800008 */ 	lwc1	$f0,0x8($s4)
/*  f1266c8:	4600d03c */ 	c.lt.s	$f26,$f0
/*  f1266cc:	00000000 */ 	nop
/*  f1266d0:	450201c9 */ 	bc1fl	.PF0f126df8
/*  f1266d4:	8fa9013c */ 	lw	$t1,0x13c($sp)
/*  f1266d8:	c6880000 */ 	lwc1	$f8,0x0($s4)
/*  f1266dc:	3c013f00 */ 	lui	$at,0x3f00
/*  f1266e0:	44811000 */ 	mtc1	$at,$f2
/*  f1266e4:	46004283 */ 	div.s	$f10,$f8,$f0
/*  f1266e8:	87af0166 */ 	lh	$t7,0x166($sp)
/*  f1266ec:	c7a40154 */ 	lwc1	$f4,0x154($sp)
/*  f1266f0:	8fb0013c */ 	lw	$s0,0x13c($sp)
/*  f1266f4:	448f3000 */ 	mtc1	$t7,$f6
/*  f1266f8:	3c0e800a */ 	lui	$t6,0x800a
/*  f1266fc:	87b90164 */ 	lh	$t9,0x164($sp)
/*  f126700:	46803520 */ 	cvt.s.w	$f20,$f6
/*  f126704:	25ce39b0 */ 	addiu	$t6,$t6,0x39b0
/*  f126708:	00106880 */ 	sll	$t5,$s0,0x2
/*  f12670c:	01ae8821 */ 	addu	$s1,$t5,$t6
/*  f126710:	3c18800a */ 	lui	$t8,0x800a
/*  f126714:	3c088008 */ 	lui	$t0,0x8008
/*  f126718:	271839c0 */ 	addiu	$t8,$t8,0x39c0
/*  f12671c:	2508e064 */ 	addiu	$t0,$t0,-8092
/*  f126720:	01b89021 */ 	addu	$s2,$t5,$t8
/*  f126724:	01a84821 */ 	addu	$t1,$t5,$t0
/*  f126728:	01a08025 */ 	move	$s0,$t5
/*  f12672c:	afa90094 */ 	sw	$t1,0x94($sp)
/*  f126730:	afa00120 */ 	sw	$zero,0x120($sp)
/*  f126734:	461a5400 */ 	add.s	$f16,$f10,$f26
/*  f126738:	44995000 */ 	mtc1	$t9,$f10
/*  f12673c:	46028482 */ 	mul.s	$f18,$f16,$f2
/*  f126740:	c6900004 */ 	lwc1	$f16,0x4($s4)
/*  f126744:	468055a0 */ 	cvt.s.w	$f22,$f10
/*  f126748:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f12674c:	c7aa0150 */ 	lwc1	$f10,0x150($sp)
/*  f126750:	46008487 */ 	neg.s	$f18,$f16
/*  f126754:	46009103 */ 	div.s	$f4,$f18,$f0
/*  f126758:	46143200 */ 	add.s	$f8,$f6,$f20
/*  f12675c:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f126760:	461a2180 */ 	add.s	$f6,$f4,$f26
/*  f126764:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f126768:	00000000 */ 	nop
/*  f12676c:	460a4402 */ 	mul.s	$f16,$f8,$f10
/*  f126770:	46168480 */ 	add.s	$f18,$f16,$f22
/*  f126774:	0c002eee */ 	jal	viGetFovY
/*  f126778:	e6520000 */ 	swc1	$f18,0x0($s2)
/*  f12677c:	3c014270 */ 	lui	$at,0x4270
/*  f126780:	44812000 */ 	mtc1	$at,$f4
/*  f126784:	86ca0010 */ 	lh	$t2,0x10($s6)
/*  f126788:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*  f12678c:	46002183 */ 	div.s	$f6,$f4,$f0
/*  f126790:	448a4000 */ 	mtc1	$t2,$f8
/*  f126794:	c7b200c8 */ 	lwc1	$f18,0xc8($sp)
/*  f126798:	468042a0 */ 	cvt.s.w	$f10,$f8
/*  f12679c:	460a3602 */ 	mul.s	$f24,$f6,$f10
/*  f1267a0:	4618a401 */ 	sub.s	$f16,$f20,$f24
/*  f1267a4:	460c803e */ 	c.le.s	$f16,$f12
/*  f1267a8:	00000000 */ 	nop
/*  f1267ac:	45020182 */ 	bc1fl	.PF0f126db8
/*  f1267b0:	8fad0120 */ 	lw	$t5,0x120($sp)
/*  f1267b4:	4612a080 */ 	add.s	$f2,$f20,$f18
/*  f1267b8:	46181100 */ 	add.s	$f4,$f2,$f24
/*  f1267bc:	4604603c */ 	c.lt.s	$f12,$f4
/*  f1267c0:	00000000 */ 	nop
/*  f1267c4:	4502017c */ 	bc1fl	.PF0f126db8
/*  f1267c8:	8fad0120 */ 	lw	$t5,0x120($sp)
/*  f1267cc:	4618b201 */ 	sub.s	$f8,$f22,$f24
/*  f1267d0:	c64e0000 */ 	lwc1	$f14,0x0($s2)
/*  f1267d4:	c7a60150 */ 	lwc1	$f6,0x150($sp)
/*  f1267d8:	460e403e */ 	c.le.s	$f8,$f14
/*  f1267dc:	00000000 */ 	nop
/*  f1267e0:	45020175 */ 	bc1fl	.PF0f126db8
/*  f1267e4:	8fad0120 */ 	lw	$t5,0x120($sp)
/*  f1267e8:	4606b000 */ 	add.s	$f0,$f22,$f6
/*  f1267ec:	3c0b8008 */ 	lui	$t3,0x8008
/*  f1267f0:	256be058 */ 	addiu	$t3,$t3,-8104
/*  f1267f4:	020b6021 */ 	addu	$t4,$s0,$t3
/*  f1267f8:	46180280 */ 	add.s	$f10,$f0,$f24
/*  f1267fc:	240f0001 */ 	li	$t7,0x1
/*  f126800:	460a703c */ 	c.lt.s	$f14,$f10
/*  f126804:	00000000 */ 	nop
/*  f126808:	4502016b */ 	bc1fl	.PF0f126db8
/*  f12680c:	8fad0120 */ 	lw	$t5,0x120($sp)
/*  f126810:	8fad013c */ 	lw	$t5,0x13c($sp)
/*  f126814:	460ca03e */ 	c.le.s	$f20,$f12
/*  f126818:	448f8000 */ 	mtc1	$t7,$f16
/*  f12681c:	000d7080 */ 	sll	$t6,$t5,0x2
/*  f126820:	01cd7021 */ 	addu	$t6,$t6,$t5
/*  f126824:	000e7140 */ 	sll	$t6,$t6,0x5
/*  f126828:	afae0098 */ 	sw	$t6,0x98($sp)
/*  f12682c:	afac009c */ 	sw	$t4,0x9c($sp)
/*  f126830:	450000aa */ 	bc1f	.PF0f126adc
/*  f126834:	468087a0 */ 	cvt.s.w	$f30,$f16
/*  f126838:	4602603c */ 	c.lt.s	$f12,$f2
/*  f12683c:	00000000 */ 	nop
/*  f126840:	450200a7 */ 	bc1fl	.PF0f126ae0
/*  f126844:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f126848:	460eb03e */ 	c.le.s	$f22,$f14
/*  f12684c:	00000000 */ 	nop
/*  f126850:	450200a3 */ 	bc1fl	.PF0f126ae0
/*  f126854:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f126858:	4600703c */ 	c.lt.s	$f14,$f0
/*  f12685c:	87a30166 */ 	lh	$v1,0x166($sp)
/*  f126860:	87a20164 */ 	lh	$v0,0x164($sp)
/*  f126864:	87b80162 */ 	lh	$t8,0x162($sp)
/*  f126868:	4500009c */ 	bc1f	.PF0f126adc
/*  f12686c:	2470000f */ 	addiu	$s0,$v1,0xf
/*  f126870:	87b90160 */ 	lh	$t9,0x160($sp)
/*  f126874:	00789821 */ 	addu	$s3,$v1,$t8
/*  f126878:	267efff0 */ 	addiu	$s8,$s3,-16
/*  f12687c:	0059b821 */ 	addu	$s7,$v0,$t9
/*  f126880:	26e8fff0 */ 	addiu	$t0,$s7,-16
/*  f126884:	afa800a0 */ 	sw	$t0,0xa0($sp)
/*  f126888:	0c00090f */ 	jal	bbufGetIndex0Buffer
/*  f12688c:	2455000f */ 	addiu	$s5,$v0,0xf
/*  f126890:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*  f126894:	3c01447a */ 	lui	$at,0x447a
/*  f126898:	44811000 */ 	mtc1	$at,$f2
/*  f12689c:	4600648d */ 	trunc.w.s	$f18,$f12
/*  f1268a0:	24090001 */ 	li	$t1,0x1
/*  f1268a4:	00403825 */ 	move	$a3,$v0
/*  f1268a8:	afa90120 */ 	sw	$t1,0x120($sp)
/*  f1268ac:	44039000 */ 	mfc1	$v1,$f18
/*  f1268b0:	8fad00a0 */ 	lw	$t5,0xa0($sp)
/*  f1268b4:	0070082a */ 	slt	$at,$v1,$s0
/*  f1268b8:	10200008 */ 	beqz	$at,.PF0f1268dc
/*  f1268bc:	3c01447a */ 	lui	$at,0x447a
/*  f1268c0:	44812000 */ 	mtc1	$at,$f4
/*  f1268c4:	46006006 */ 	mov.s	$f0,$f12
/*  f1268c8:	4604603c */ 	c.lt.s	$f12,$f4
/*  f1268cc:	00000000 */ 	nop
/*  f1268d0:	45020003 */ 	bc1fl	.PF0f1268e0
/*  f1268d4:	c64e0000 */ 	lwc1	$f14,0x0($s2)
/*  f1268d8:	46000086 */ 	mov.s	$f2,$f0
.PF0f1268dc:
/*  f1268dc:	c64e0000 */ 	lwc1	$f14,0x0($s2)
.PF0f1268e0:
/*  f1268e0:	4600720d */ 	trunc.w.s	$f8,$f14
/*  f1268e4:	44024000 */ 	mfc1	$v0,$f8
/*  f1268e8:	00000000 */ 	nop
/*  f1268ec:	0055082a */ 	slt	$at,$v0,$s5
/*  f1268f0:	50200007 */ 	beqzl	$at,.PF0f126910
/*  f1268f4:	03c3082a */ 	slt	$at,$s8,$v1
/*  f1268f8:	4602703c */ 	c.lt.s	$f14,$f2
/*  f1268fc:	46007006 */ 	mov.s	$f0,$f14
/*  f126900:	45020003 */ 	bc1fl	.PF0f126910
/*  f126904:	03c3082a */ 	slt	$at,$s8,$v1
/*  f126908:	46000086 */ 	mov.s	$f2,$f0
/*  f12690c:	03c3082a */ 	slt	$at,$s8,$v1
.PF0f126910:
/*  f126910:	1020000a */ 	beqz	$at,.PF0f12693c
/*  f126914:	266cffff */ 	addiu	$t4,$s3,-1
/*  f126918:	448c3000 */ 	mtc1	$t4,$f6
/*  f12691c:	00000000 */ 	nop
/*  f126920:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f126924:	460c5001 */ 	sub.s	$f0,$f10,$f12
/*  f126928:	4602003c */ 	c.lt.s	$f0,$f2
/*  f12692c:	00000000 */ 	nop
/*  f126930:	45020003 */ 	bc1fl	.PF0f126940
/*  f126934:	01a2082a */ 	slt	$at,$t5,$v0
/*  f126938:	46000086 */ 	mov.s	$f2,$f0
.PF0f12693c:
/*  f12693c:	01a2082a */ 	slt	$at,$t5,$v0
.PF0f126940:
/*  f126940:	1020000a */ 	beqz	$at,.PF0f12696c
/*  f126944:	26eeffff */ 	addiu	$t6,$s7,-1
/*  f126948:	448e8000 */ 	mtc1	$t6,$f16
/*  f12694c:	00000000 */ 	nop
/*  f126950:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f126954:	460e9001 */ 	sub.s	$f0,$f18,$f14
/*  f126958:	4602003c */ 	c.lt.s	$f0,$f2
/*  f12695c:	00000000 */ 	nop
/*  f126960:	45020003 */ 	bc1fl	.PF0f126970
/*  f126964:	461a1081 */ 	sub.s	$f2,$f2,$f26
/*  f126968:	46000086 */ 	mov.s	$f2,$f0
.PF0f12696c:
/*  f12696c:	461a1081 */ 	sub.s	$f2,$f2,$f26
.PF0f126970:
/*  f126970:	3c017f1b */ 	lui	$at,0x7f1b
/*  f126974:	461c103c */ 	c.lt.s	$f2,$f28
/*  f126978:	00000000 */ 	nop
/*  f12697c:	45000002 */ 	bc1f	.PF0f126988
/*  f126980:	00000000 */ 	nop
/*  f126984:	4600e086 */ 	mov.s	$f2,$f28
.PF0f126988:
/*  f126988:	c42463f8 */ 	lwc1	$f4,0x63f8($at)
/*  f12698c:	8faf009c */ 	lw	$t7,0x9c($sp)
/*  f126990:	46041002 */ 	mul.s	$f0,$f2,$f4
/*  f126994:	4600d03c */ 	c.lt.s	$f26,$f0
/*  f126998:	e5e00000 */ 	swc1	$f0,0x0($t7)
/*  f12699c:	8fb8009c */ 	lw	$t8,0x9c($sp)
/*  f1269a0:	45020003 */ 	bc1fl	.PF0f1269b0
/*  f1269a4:	8fb90098 */ 	lw	$t9,0x98($sp)
/*  f1269a8:	e71a0000 */ 	swc1	$f26,0x0($t8)
/*  f1269ac:	8fb90098 */ 	lw	$t9,0x98($sp)
.PF0f1269b0:
/*  f1269b0:	2465fff9 */ 	addiu	$a1,$v1,-7
/*  f1269b4:	24460001 */ 	addiu	$a2,$v0,0x1
/*  f1269b8:	03278021 */ 	addu	$s0,$t9,$a3
/*  f1269bc:	0fc49912 */ 	jal	func0f125948
/*  f1269c0:	02002025 */ 	move	$a0,$s0
/*  f1269c4:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f1269c8:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f1269cc:	26040014 */ 	addiu	$a0,$s0,0x14
/*  f1269d0:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f1269d4:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f1269d8:	44053000 */ 	mfc1	$a1,$f6
/*  f1269dc:	44068000 */ 	mfc1	$a2,$f16
/*  f1269e0:	24a5fffb */ 	addiu	$a1,$a1,-5
/*  f1269e4:	0fc49912 */ 	jal	func0f125948
/*  f1269e8:	24c6fffd */ 	addiu	$a2,$a2,-3
/*  f1269ec:	c6320000 */ 	lwc1	$f18,0x0($s1)
/*  f1269f0:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*  f1269f4:	26040028 */ 	addiu	$a0,$s0,0x28
/*  f1269f8:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f1269fc:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f126a00:	44052000 */ 	mfc1	$a1,$f4
/*  f126a04:	44063000 */ 	mfc1	$a2,$f6
/*  f126a08:	24a5fffd */ 	addiu	$a1,$a1,-3
/*  f126a0c:	0fc49912 */ 	jal	func0f125948
/*  f126a10:	24c60005 */ 	addiu	$a2,$a2,0x5
/*  f126a14:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f126a18:	c6520000 */ 	lwc1	$f18,0x0($s2)
/*  f126a1c:	2604003c */ 	addiu	$a0,$s0,0x3c
/*  f126a20:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f126a24:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f126a28:	44058000 */ 	mfc1	$a1,$f16
/*  f126a2c:	44062000 */ 	mfc1	$a2,$f4
/*  f126a30:	24a5ffff */ 	addiu	$a1,$a1,-1
/*  f126a34:	0fc49912 */ 	jal	func0f125948
/*  f126a38:	24c6fff9 */ 	addiu	$a2,$a2,-7
/*  f126a3c:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f126a40:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f126a44:	26040050 */ 	addiu	$a0,$s0,0x50
/*  f126a48:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f126a4c:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f126a50:	44053000 */ 	mfc1	$a1,$f6
/*  f126a54:	44068000 */ 	mfc1	$a2,$f16
/*  f126a58:	24a50001 */ 	addiu	$a1,$a1,0x1
/*  f126a5c:	0fc49912 */ 	jal	func0f125948
/*  f126a60:	24c60007 */ 	addiu	$a2,$a2,0x7
/*  f126a64:	c6320000 */ 	lwc1	$f18,0x0($s1)
/*  f126a68:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*  f126a6c:	26040064 */ 	addiu	$a0,$s0,0x64
/*  f126a70:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f126a74:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f126a78:	44052000 */ 	mfc1	$a1,$f4
/*  f126a7c:	44063000 */ 	mfc1	$a2,$f6
/*  f126a80:	24a50003 */ 	addiu	$a1,$a1,0x3
/*  f126a84:	0fc49912 */ 	jal	func0f125948
/*  f126a88:	24c6fffb */ 	addiu	$a2,$a2,-5
/*  f126a8c:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f126a90:	c6520000 */ 	lwc1	$f18,0x0($s2)
/*  f126a94:	26040078 */ 	addiu	$a0,$s0,0x78
/*  f126a98:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f126a9c:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f126aa0:	44058000 */ 	mfc1	$a1,$f16
/*  f126aa4:	44062000 */ 	mfc1	$a2,$f4
/*  f126aa8:	24a50005 */ 	addiu	$a1,$a1,0x5
/*  f126aac:	0fc49912 */ 	jal	func0f125948
/*  f126ab0:	24c60003 */ 	addiu	$a2,$a2,0x3
/*  f126ab4:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f126ab8:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f126abc:	2604008c */ 	addiu	$a0,$s0,0x8c
/*  f126ac0:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f126ac4:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f126ac8:	44053000 */ 	mfc1	$a1,$f6
/*  f126acc:	44068000 */ 	mfc1	$a2,$f16
/*  f126ad0:	24a50007 */ 	addiu	$a1,$a1,0x7
/*  f126ad4:	0fc49912 */ 	jal	func0f125948
/*  f126ad8:	24c6ffff */ 	addiu	$a2,$a2,-1
.PF0f126adc:
/*  f126adc:	8fa20094 */ 	lw	$v0,0x94($sp)
.PF0f126ae0:
/*  f126ae0:	3c0d800a */ 	lui	$t5,0x800a
/*  f126ae4:	8dada544 */ 	lw	$t5,-0x5abc($t5)
/*  f126ae8:	8c4c0000 */ 	lw	$t4,0x0($v0)
/*  f126aec:	3c05800b */ 	lui	$a1,0x800b
/*  f126af0:	240f0002 */ 	li	$t7,0x2
/*  f126af4:	018d7021 */ 	addu	$t6,$t4,$t5
/*  f126af8:	ac4e0000 */ 	sw	$t6,0x0($v0)
/*  f126afc:	8ca5bb40 */ 	lw	$a1,-0x44c0($a1)
/*  f126b00:	24180001 */ 	li	$t8,0x1
/*  f126b04:	afb80014 */ 	sw	$t8,0x14($sp)
/*  f126b08:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f126b0c:	27a40170 */ 	addiu	$a0,$sp,0x170
/*  f126b10:	24060004 */ 	li	$a2,0x4
/*  f126b14:	00003825 */ 	move	$a3,$zero
/*  f126b18:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f126b1c:	0fc2cfb8 */ 	jal	func0f0b39c0
/*  f126b20:	24a5003c */ 	addiu	$a1,$a1,0x3c
/*  f126b24:	8fb90170 */ 	lw	$t9,0x170($sp)
/*  f126b28:	3c09ba00 */ 	lui	$t1,0xba00
/*  f126b2c:	35291402 */ 	ori	$t1,$t1,0x1402
/*  f126b30:	27280008 */ 	addiu	$t0,$t9,0x8
/*  f126b34:	afa80170 */ 	sw	$t0,0x170($sp)
/*  f126b38:	af200004 */ 	sw	$zero,0x4($t9)
/*  f126b3c:	af290000 */ 	sw	$t1,0x0($t9)
/*  f126b40:	8faa0170 */ 	lw	$t2,0x170($sp)
/*  f126b44:	3c0cba00 */ 	lui	$t4,0xba00
/*  f126b48:	358c0602 */ 	ori	$t4,$t4,0x602
/*  f126b4c:	254b0008 */ 	addiu	$t3,$t2,0x8
/*  f126b50:	afab0170 */ 	sw	$t3,0x170($sp)
/*  f126b54:	240d00c0 */ 	li	$t5,0xc0
/*  f126b58:	ad4d0004 */ 	sw	$t5,0x4($t2)
/*  f126b5c:	ad4c0000 */ 	sw	$t4,0x0($t2)
/*  f126b60:	8fae0170 */ 	lw	$t6,0x170($sp)
/*  f126b64:	3c190050 */ 	lui	$t9,0x50
/*  f126b68:	3c18b900 */ 	lui	$t8,0xb900
/*  f126b6c:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f126b70:	afaf0170 */ 	sw	$t7,0x170($sp)
/*  f126b74:	3718031d */ 	ori	$t8,$t8,0x31d
/*  f126b78:	373941c8 */ 	ori	$t9,$t9,0x41c8
/*  f126b7c:	add90004 */ 	sw	$t9,0x4($t6)
/*  f126b80:	add80000 */ 	sw	$t8,0x0($t6)
/*  f126b84:	8fa80170 */ 	lw	$t0,0x170($sp)
/*  f126b88:	3c0aba00 */ 	lui	$t2,0xba00
/*  f126b8c:	354a1301 */ 	ori	$t2,$t2,0x1301
/*  f126b90:	25090008 */ 	addiu	$t1,$t0,0x8
/*  f126b94:	afa90170 */ 	sw	$t1,0x170($sp)
/*  f126b98:	ad000004 */ 	sw	$zero,0x4($t0)
/*  f126b9c:	ad0a0000 */ 	sw	$t2,0x0($t0)
/*  f126ba0:	8fab0170 */ 	lw	$t3,0x170($sp)
/*  f126ba4:	3c0db900 */ 	lui	$t5,0xb900
/*  f126ba8:	35ad0002 */ 	ori	$t5,$t5,0x2
/*  f126bac:	256c0008 */ 	addiu	$t4,$t3,0x8
/*  f126bb0:	afac0170 */ 	sw	$t4,0x170($sp)
/*  f126bb4:	ad600004 */ 	sw	$zero,0x4($t3)
/*  f126bb8:	ad6d0000 */ 	sw	$t5,0x0($t3)
/*  f126bbc:	8fae0170 */ 	lw	$t6,0x170($sp)
/*  f126bc0:	3c18ba00 */ 	lui	$t8,0xba00
/*  f126bc4:	37181001 */ 	ori	$t8,$t8,0x1001
/*  f126bc8:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f126bcc:	afaf0170 */ 	sw	$t7,0x170($sp)
/*  f126bd0:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f126bd4:	add80000 */ 	sw	$t8,0x0($t6)
/*  f126bd8:	8fb90170 */ 	lw	$t9,0x170($sp)
/*  f126bdc:	3c09ba00 */ 	lui	$t1,0xba00
/*  f126be0:	35290903 */ 	ori	$t1,$t1,0x903
/*  f126be4:	27280008 */ 	addiu	$t0,$t9,0x8
/*  f126be8:	afa80170 */ 	sw	$t0,0x170($sp)
/*  f126bec:	240a0c00 */ 	li	$t2,0xc00
/*  f126bf0:	af2a0004 */ 	sw	$t2,0x4($t9)
/*  f126bf4:	af290000 */ 	sw	$t1,0x0($t9)
/*  f126bf8:	8fab0170 */ 	lw	$t3,0x170($sp)
/*  f126bfc:	3c0dba00 */ 	lui	$t5,0xba00
/*  f126c00:	35ad0e02 */ 	ori	$t5,$t5,0xe02
/*  f126c04:	256c0008 */ 	addiu	$t4,$t3,0x8
/*  f126c08:	afac0170 */ 	sw	$t4,0x170($sp)
/*  f126c0c:	ad600004 */ 	sw	$zero,0x4($t3)
/*  f126c10:	ad6d0000 */ 	sw	$t5,0x0($t3)
/*  f126c14:	8fae0170 */ 	lw	$t6,0x170($sp)
/*  f126c18:	3c18ba00 */ 	lui	$t8,0xba00
/*  f126c1c:	37180c02 */ 	ori	$t8,$t8,0xc02
/*  f126c20:	25cf0008 */ 	addiu	$t7,$t6,0x8
/*  f126c24:	afaf0170 */ 	sw	$t7,0x170($sp)
/*  f126c28:	24192000 */ 	li	$t9,0x2000
/*  f126c2c:	add90004 */ 	sw	$t9,0x4($t6)
/*  f126c30:	add80000 */ 	sw	$t8,0x0($t6)
/*  f126c34:	8fa80170 */ 	lw	$t0,0x170($sp)
/*  f126c38:	3c0bffa7 */ 	lui	$t3,0xffa7
/*  f126c3c:	3c0afc50 */ 	lui	$t2,0xfc50
/*  f126c40:	25090008 */ 	addiu	$t1,$t0,0x8
/*  f126c44:	afa90170 */ 	sw	$t1,0x170($sp)
/*  f126c48:	354ad2a1 */ 	ori	$t2,$t2,0xd2a1
/*  f126c4c:	356bffff */ 	ori	$t3,$t3,0xffff
/*  f126c50:	ad0b0004 */ 	sw	$t3,0x4($t0)
/*  f126c54:	ad0a0000 */ 	sw	$t2,0x0($t0)
/*  f126c58:	8fa30170 */ 	lw	$v1,0x170($sp)
/*  f126c5c:	3c0efb00 */ 	lui	$t6,0xfb00
/*  f126c60:	3c01437f */ 	lui	$at,0x437f
/*  f126c64:	246d0008 */ 	addiu	$t5,$v1,0x8
/*  f126c68:	afad0170 */ 	sw	$t5,0x170($sp)
/*  f126c6c:	ac6e0000 */ 	sw	$t6,0x0($v1)
/*  f126c70:	8faf009c */ 	lw	$t7,0x9c($sp)
/*  f126c74:	44812000 */ 	mtc1	$at,$f4
/*  f126c78:	3c013f00 */ 	lui	$at,0x3f00
/*  f126c7c:	c5f20000 */ 	lwc1	$f18,0x0($t7)
/*  f126c80:	93aa0148 */ 	lbu	$t2,0x148($sp)
/*  f126c84:	93ae0149 */ 	lbu	$t6,0x149($sp)
/*  f126c88:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f126c8c:	44819000 */ 	mtc1	$at,$f18
/*  f126c90:	93a9014a */ 	lbu	$t1,0x14a($sp)
/*  f126c94:	000a5e00 */ 	sll	$t3,$t2,0x18
/*  f126c98:	4612c002 */ 	mul.s	$f0,$f24,$f18
/*  f126c9c:	000e7c00 */ 	sll	$t7,$t6,0x10
/*  f126ca0:	00095200 */ 	sll	$t2,$t1,0x8
/*  f126ca4:	3c02800b */ 	lui	$v0,0x800b
/*  f126ca8:	240e0001 */ 	li	$t6,0x1
/*  f126cac:	240d0001 */ 	li	$t5,0x1
/*  f126cb0:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f126cb4:	461e0102 */ 	mul.s	$f4,$f0,$f30
/*  f126cb8:	27a40170 */ 	addiu	$a0,$sp,0x170
/*  f126cbc:	27a50134 */ 	addiu	$a1,$sp,0x134
/*  f126cc0:	44193000 */ 	mfc1	$t9,$f6
/*  f126cc4:	27a6012c */ 	addiu	$a2,$sp,0x12c
/*  f126cc8:	332800ff */ 	andi	$t0,$t9,0xff
/*  f126ccc:	010b6025 */ 	or	$t4,$t0,$t3
/*  f126cd0:	018fc025 */ 	or	$t8,$t4,$t7
/*  f126cd4:	030a4025 */ 	or	$t0,$t8,$t2
/*  f126cd8:	ac680004 */ 	sw	$t0,0x4($v1)
/*  f126cdc:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f126ce0:	c6500000 */ 	lwc1	$f16,0x0($s2)
/*  f126ce4:	8c42bb40 */ 	lw	$v0,-0x44c0($v0)
/*  f126ce8:	e7a4012c */ 	swc1	$f4,0x12c($sp)
/*  f126cec:	e7a00130 */ 	swc1	$f0,0x130($sp)
/*  f126cf0:	e7aa0134 */ 	swc1	$f10,0x134($sp)
/*  f126cf4:	e7b00138 */ 	swc1	$f16,0x138($sp)
/*  f126cf8:	904b0041 */ 	lbu	$t3,0x41($v0)
/*  f126cfc:	90470040 */ 	lbu	$a3,0x40($v0)
/*  f126d00:	240f0001 */ 	li	$t7,0x1
/*  f126d04:	240c0001 */ 	li	$t4,0x1
/*  f126d08:	afac0020 */ 	sw	$t4,0x20($sp)
/*  f126d0c:	afaf0028 */ 	sw	$t7,0x28($sp)
/*  f126d10:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f126d14:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f126d18:	afad0018 */ 	sw	$t5,0x18($sp)
/*  f126d1c:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f126d20:	0fc2c99c */ 	jal	func0f0b2150
/*  f126d24:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f126d28:	8fb90170 */ 	lw	$t9,0x170($sp)
/*  f126d2c:	3c18e700 */ 	lui	$t8,0xe700
/*  f126d30:	3c0bba00 */ 	lui	$t3,0xba00
/*  f126d34:	27290008 */ 	addiu	$t1,$t9,0x8
/*  f126d38:	afa90170 */ 	sw	$t1,0x170($sp)
/*  f126d3c:	af200004 */ 	sw	$zero,0x4($t9)
/*  f126d40:	af380000 */ 	sw	$t8,0x0($t9)
/*  f126d44:	8faa0170 */ 	lw	$t2,0x170($sp)
/*  f126d48:	356b0602 */ 	ori	$t3,$t3,0x602
/*  f126d4c:	240d0040 */ 	li	$t5,0x40
/*  f126d50:	25480008 */ 	addiu	$t0,$t2,0x8
/*  f126d54:	afa80170 */ 	sw	$t0,0x170($sp)
/*  f126d58:	ad4d0004 */ 	sw	$t5,0x4($t2)
/*  f126d5c:	ad4b0000 */ 	sw	$t3,0x0($t2)
/*  f126d60:	8fae0170 */ 	lw	$t6,0x170($sp)
/*  f126d64:	3c0fba00 */ 	lui	$t7,0xba00
/*  f126d68:	35ef1301 */ 	ori	$t7,$t7,0x1301
/*  f126d6c:	25cc0008 */ 	addiu	$t4,$t6,0x8
/*  f126d70:	afac0170 */ 	sw	$t4,0x170($sp)
/*  f126d74:	3c190008 */ 	lui	$t9,0x8
/*  f126d78:	add90004 */ 	sw	$t9,0x4($t6)
/*  f126d7c:	adcf0000 */ 	sw	$t7,0x0($t6)
/*  f126d80:	8fa90170 */ 	lw	$t1,0x170($sp)
/*  f126d84:	3c0aba00 */ 	lui	$t2,0xba00
/*  f126d88:	354a1001 */ 	ori	$t2,$t2,0x1001
/*  f126d8c:	25380008 */ 	addiu	$t8,$t1,0x8
/*  f126d90:	afb80170 */ 	sw	$t8,0x170($sp)
/*  f126d94:	3c080001 */ 	lui	$t0,0x1
/*  f126d98:	ad280004 */ 	sw	$t0,0x4($t1)
/*  f126d9c:	0c00091c */ 	jal	bbufGetIndex1Buffer
/*  f126da0:	ad2a0000 */ 	sw	$t2,0x0($t1)
/*  f126da4:	8fab0098 */ 	lw	$t3,0x98($sp)
/*  f126da8:	0fc49947 */ 	jal	func0f125a1c
/*  f126dac:	004b2021 */ 	addu	$a0,$v0,$t3
/*  f126db0:	e7a00124 */ 	swc1	$f0,0x124($sp)
/*  f126db4:	8fad0120 */ 	lw	$t5,0x120($sp)
.PF0f126db8:
/*  f126db8:	c7a80124 */ 	lwc1	$f8,0x124($sp)
/*  f126dbc:	51a0000c */ 	beqzl	$t5,.PF0f126df0
/*  f126dc0:	8fb90094 */ 	lw	$t9,0x94($sp)
/*  f126dc4:	4608e03c */ 	c.lt.s	$f28,$f8
/*  f126dc8:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f126dcc:	3c0c800a */ 	lui	$t4,0x800a
/*  f126dd0:	45020007 */ 	bc1fl	.PF0f126df0
/*  f126dd4:	8fb90094 */ 	lw	$t9,0x94($sp)
/*  f126dd8:	8c4e0000 */ 	lw	$t6,0x0($v0)
/*  f126ddc:	8d8ca544 */ 	lw	$t4,-0x5abc($t4)
/*  f126de0:	01cc7821 */ 	addu	$t7,$t6,$t4
/*  f126de4:	10000003 */ 	b	.PF0f126df4
/*  f126de8:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f126dec:	8fb90094 */ 	lw	$t9,0x94($sp)
.PF0f126df0:
/*  f126df0:	af200000 */ 	sw	$zero,0x0($t9)
.PF0f126df4:
/*  f126df4:	8fa9013c */ 	lw	$t1,0x13c($sp)
.PF0f126df8:
/*  f126df8:	8faa0144 */ 	lw	$t2,0x144($sp)
/*  f126dfc:	2694000c */ 	addiu	$s4,$s4,0xc
/*  f126e00:	25380001 */ 	addiu	$t8,$t1,0x1
/*  f126e04:	afb8013c */ 	sw	$t8,0x13c($sp)
/*  f126e08:	9148000b */ 	lbu	$t0,0xb($t2)
/*  f126e0c:	26d60014 */ 	addiu	$s6,$s6,0x14
/*  f126e10:	0308082a */ 	slt	$at,$t8,$t0
/*  f126e14:	5420fe18 */ 	bnezl	$at,.PF0f126678
/*  f126e18:	c6d00004 */ 	lwc1	$f16,0x4($s6)
/*  f126e1c:	8fa20170 */ 	lw	$v0,0x170($sp)
.PF0f126e20:
/*  f126e20:	8fbf008c */ 	lw	$ra,0x8c($sp)
/*  f126e24:	d7b40038 */ 	ldc1	$f20,0x38($sp)
/*  f126e28:	d7b60040 */ 	ldc1	$f22,0x40($sp)
/*  f126e2c:	d7b80048 */ 	ldc1	$f24,0x48($sp)
/*  f126e30:	d7ba0050 */ 	ldc1	$f26,0x50($sp)
/*  f126e34:	d7bc0058 */ 	ldc1	$f28,0x58($sp)
/*  f126e38:	d7be0060 */ 	ldc1	$f30,0x60($sp)
/*  f126e3c:	8fb00068 */ 	lw	$s0,0x68($sp)
/*  f126e40:	8fb1006c */ 	lw	$s1,0x6c($sp)
/*  f126e44:	8fb20070 */ 	lw	$s2,0x70($sp)
/*  f126e48:	8fb30074 */ 	lw	$s3,0x74($sp)
/*  f126e4c:	8fb40078 */ 	lw	$s4,0x78($sp)
/*  f126e50:	8fb5007c */ 	lw	$s5,0x7c($sp)
/*  f126e54:	8fb60080 */ 	lw	$s6,0x80($sp)
/*  f126e58:	8fb70084 */ 	lw	$s7,0x84($sp)
/*  f126e5c:	8fbe0088 */ 	lw	$s8,0x88($sp)
/*  f126e60:	03e00008 */ 	jr	$ra
/*  f126e64:	27bd0170 */ 	addiu	$sp,$sp,0x170
);
#else
GLOBAL_ASM(
glabel func0f125a6c
.late_rodata
glabel var7f1b5108
.word 0x3d888889
.text
/*  f125a6c:	27bdfe90 */ 	addiu	$sp,$sp,-368
/*  f125a70:	afbf008c */ 	sw	$ra,0x8c($sp)
/*  f125a74:	afbe0088 */ 	sw	$s8,0x88($sp)
/*  f125a78:	afb70084 */ 	sw	$s7,0x84($sp)
/*  f125a7c:	afb60080 */ 	sw	$s6,0x80($sp)
/*  f125a80:	afb5007c */ 	sw	$s5,0x7c($sp)
/*  f125a84:	afb40078 */ 	sw	$s4,0x78($sp)
/*  f125a88:	afb30074 */ 	sw	$s3,0x74($sp)
/*  f125a8c:	afb20070 */ 	sw	$s2,0x70($sp)
/*  f125a90:	afb1006c */ 	sw	$s1,0x6c($sp)
/*  f125a94:	afb00068 */ 	sw	$s0,0x68($sp)
/*  f125a98:	f7be0060 */ 	sdc1	$f30,0x60($sp)
/*  f125a9c:	f7bc0058 */ 	sdc1	$f28,0x58($sp)
/*  f125aa0:	f7ba0050 */ 	sdc1	$f26,0x50($sp)
/*  f125aa4:	f7b80048 */ 	sdc1	$f24,0x48($sp)
/*  f125aa8:	f7b60040 */ 	sdc1	$f22,0x40($sp)
/*  f125aac:	f7b40038 */ 	sdc1	$f20,0x38($sp)
/*  f125ab0:	afa40170 */ 	sw	$a0,0x170($sp)
/*  f125ab4:	0fc2d5be */ 	jal	currentPlayerGetMatrix1740
/*  f125ab8:	afa50174 */ 	sw	$a1,0x174($sp)
/*  f125abc:	0fc2d5c6 */ 	jal	currentPlayerGetUnk1754
/*  f125ac0:	afa2016c */ 	sw	$v0,0x16c($sp)
/*  f125ac4:	0fc595f3 */ 	jal	skyGetCurrent
/*  f125ac8:	afa20168 */ 	sw	$v0,0x168($sp)
/*  f125acc:	afa20144 */ 	sw	$v0,0x144($sp)
/*  f125ad0:	904e000b */ 	lbu	$t6,0xb($v0)
/*  f125ad4:	24030001 */ 	addiu	$v1,$zero,0x1
/*  f125ad8:	3c0f8008 */ 	lui	$t7,%hi(var800844f0)
/*  f125adc:	19c00009 */ 	blez	$t6,.L0f125b04
/*  f125ae0:	00000000 */ 	nop
/*  f125ae4:	8def44f0 */ 	lw	$t7,%lo(var800844f0)($t7)
/*  f125ae8:	3c18800a */ 	lui	$t8,%hi(g_Vars+0x314)
/*  f125aec:	11e00005 */ 	beqz	$t7,.L0f125b04
/*  f125af0:	00000000 */ 	nop
/*  f125af4:	8f18a2d4 */ 	lw	$t8,%lo(g_Vars+0x314)($t8)
/*  f125af8:	3c198007 */ 	lui	$t9,%hi(g_ViRes)
/*  f125afc:	13000003 */ 	beqz	$t8,.L0f125b0c
/*  f125b00:	00000000 */ 	nop
.L0f125b04:
/*  f125b04:	1000020d */ 	b	.L0f12633c
/*  f125b08:	8fa20170 */ 	lw	$v0,0x170($sp)
.L0f125b0c:
/*  f125b0c:	8f3906c8 */ 	lw	$t9,%lo(g_ViRes)($t9)
/*  f125b10:	24010001 */ 	addiu	$at,$zero,0x1
/*  f125b14:	17210002 */ 	bne	$t9,$at,.L0f125b20
/*  f125b18:	00000000 */ 	nop
/*  f125b1c:	24030002 */ 	addiu	$v1,$zero,0x2
.L0f125b20:
/*  f125b20:	0c002f40 */ 	jal	viGetViewLeft
/*  f125b24:	afa30128 */ 	sw	$v1,0x128($sp)
/*  f125b28:	0c002f44 */ 	jal	viGetViewTop
/*  f125b2c:	a7a20166 */ 	sh	$v0,0x166($sp)
/*  f125b30:	0c002f22 */ 	jal	viGetViewWidth
/*  f125b34:	a7a20164 */ 	sh	$v0,0x164($sp)
/*  f125b38:	0c002f26 */ 	jal	viGetViewHeight
/*  f125b3c:	a7a20162 */ 	sh	$v0,0x162($sp)
/*  f125b40:	87a80162 */ 	lh	$t0,0x162($sp)
/*  f125b44:	44824000 */ 	mtc1	$v0,$f8
/*  f125b48:	8fa30144 */ 	lw	$v1,0x144($sp)
/*  f125b4c:	44882000 */ 	mtc1	$t0,$f4
/*  f125b50:	468042a0 */ 	cvt.s.w	$f10,$f8
/*  f125b54:	a7a20160 */ 	sh	$v0,0x160($sp)
/*  f125b58:	3c14800a */ 	lui	$s4,%hi(var800a33e8)
/*  f125b5c:	3c013f80 */ 	lui	$at,0x3f80
/*  f125b60:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f125b64:	e7aa0150 */ 	swc1	$f10,0x150($sp)
/*  f125b68:	e7a600c8 */ 	swc1	$f6,0xc8($sp)
/*  f125b6c:	e7a60154 */ 	swc1	$f6,0x154($sp)
/*  f125b70:	8c76000c */ 	lw	$s6,0xc($v1)
/*  f125b74:	afa0013c */ 	sw	$zero,0x13c($sp)
/*  f125b78:	9069000b */ 	lbu	$t1,0xb($v1)
/*  f125b7c:	592001ef */ 	blezl	$t1,.L0f12633c
/*  f125b80:	8fa20170 */ 	lw	$v0,0x170($sp)
/*  f125b84:	4480e000 */ 	mtc1	$zero,$f28
/*  f125b88:	4481d000 */ 	mtc1	$at,$f26
/*  f125b8c:	269433e8 */ 	addiu	$s4,$s4,%lo(var800a33e8)
/*  f125b90:	c6d00004 */ 	lwc1	$f16,0x4($s6)
.L0f125b94:
/*  f125b94:	8fad0174 */ 	lw	$t5,0x174($sp)
/*  f125b98:	e6900000 */ 	swc1	$f16,0x0($s4)
/*  f125b9c:	c6d20008 */ 	lwc1	$f18,0x8($s6)
/*  f125ba0:	e6920004 */ 	swc1	$f18,0x4($s4)
/*  f125ba4:	c6c4000c */ 	lwc1	$f4,0xc($s6)
/*  f125ba8:	e6840008 */ 	swc1	$f4,0x8($s4)
/*  f125bac:	92ca0001 */ 	lbu	$t2,0x1($s6)
/*  f125bb0:	8fa4016c */ 	lw	$a0,0x16c($sp)
/*  f125bb4:	a3aa0148 */ 	sb	$t2,0x148($sp)
/*  f125bb8:	92cb0002 */ 	lbu	$t3,0x2($s6)
/*  f125bbc:	a3ab0149 */ 	sb	$t3,0x149($sp)
/*  f125bc0:	92cc0003 */ 	lbu	$t4,0x3($s6)
/*  f125bc4:	15a001d2 */ 	bnez	$t5,.L0f126310
/*  f125bc8:	a3ac014a */ 	sb	$t4,0x14a($sp)
/*  f125bcc:	0c0056d9 */ 	jal	mtx4TransformVecInPlace
/*  f125bd0:	02802825 */ 	or	$a1,$s4,$zero
/*  f125bd4:	8fa40168 */ 	lw	$a0,0x168($sp)
/*  f125bd8:	0c0056d9 */ 	jal	mtx4TransformVecInPlace
/*  f125bdc:	02802825 */ 	or	$a1,$s4,$zero
/*  f125be0:	c6800008 */ 	lwc1	$f0,0x8($s4)
/*  f125be4:	4600d03c */ 	c.lt.s	$f26,$f0
/*  f125be8:	00000000 */ 	nop
/*  f125bec:	450201c9 */ 	bc1fl	.L0f126314
/*  f125bf0:	8faa013c */ 	lw	$t2,0x13c($sp)
/*  f125bf4:	c6880000 */ 	lwc1	$f8,0x0($s4)
/*  f125bf8:	3c013f00 */ 	lui	$at,0x3f00
/*  f125bfc:	44811000 */ 	mtc1	$at,$f2
/*  f125c00:	46004283 */ 	div.s	$f10,$f8,$f0
/*  f125c04:	87b80166 */ 	lh	$t8,0x166($sp)
/*  f125c08:	c7a40154 */ 	lwc1	$f4,0x154($sp)
/*  f125c0c:	8fb0013c */ 	lw	$s0,0x13c($sp)
/*  f125c10:	44983000 */ 	mtc1	$t8,$f6
/*  f125c14:	3c0f800a */ 	lui	$t7,%hi(var800a3410)
/*  f125c18:	87a80164 */ 	lh	$t0,0x164($sp)
/*  f125c1c:	46803520 */ 	cvt.s.w	$f20,$f6
/*  f125c20:	25ef3410 */ 	addiu	$t7,$t7,%lo(var800a3410)
/*  f125c24:	00107080 */ 	sll	$t6,$s0,0x2
/*  f125c28:	01cf8821 */ 	addu	$s1,$t6,$t7
/*  f125c2c:	3c19800a */ 	lui	$t9,%hi(var800a3420)
/*  f125c30:	3c098008 */ 	lui	$t1,%hi(var8007db94)
/*  f125c34:	27393420 */ 	addiu	$t9,$t9,%lo(var800a3420)
/*  f125c38:	2529db94 */ 	addiu	$t1,$t1,%lo(var8007db94)
/*  f125c3c:	01d99021 */ 	addu	$s2,$t6,$t9
/*  f125c40:	01c95021 */ 	addu	$t2,$t6,$t1
/*  f125c44:	01c08025 */ 	or	$s0,$t6,$zero
/*  f125c48:	afaa0094 */ 	sw	$t2,0x94($sp)
/*  f125c4c:	afa00120 */ 	sw	$zero,0x120($sp)
/*  f125c50:	461a5400 */ 	add.s	$f16,$f10,$f26
/*  f125c54:	44885000 */ 	mtc1	$t0,$f10
/*  f125c58:	46028482 */ 	mul.s	$f18,$f16,$f2
/*  f125c5c:	c6900004 */ 	lwc1	$f16,0x4($s4)
/*  f125c60:	468055a0 */ 	cvt.s.w	$f22,$f10
/*  f125c64:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f125c68:	c7aa0150 */ 	lwc1	$f10,0x150($sp)
/*  f125c6c:	46008487 */ 	neg.s	$f18,$f16
/*  f125c70:	46009103 */ 	div.s	$f4,$f18,$f0
/*  f125c74:	46143200 */ 	add.s	$f8,$f6,$f20
/*  f125c78:	e6280000 */ 	swc1	$f8,0x0($s1)
/*  f125c7c:	461a2180 */ 	add.s	$f6,$f4,$f26
/*  f125c80:	46023202 */ 	mul.s	$f8,$f6,$f2
/*  f125c84:	00000000 */ 	nop
/*  f125c88:	460a4402 */ 	mul.s	$f16,$f8,$f10
/*  f125c8c:	46168480 */ 	add.s	$f18,$f16,$f22
/*  f125c90:	0c002f9d */ 	jal	viGetFovY
/*  f125c94:	e6520000 */ 	swc1	$f18,0x0($s2)
/*  f125c98:	3c014270 */ 	lui	$at,0x4270
/*  f125c9c:	44812000 */ 	mtc1	$at,$f4
/*  f125ca0:	86cb0010 */ 	lh	$t3,0x10($s6)
/*  f125ca4:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*  f125ca8:	46002183 */ 	div.s	$f6,$f4,$f0
/*  f125cac:	448b4000 */ 	mtc1	$t3,$f8
/*  f125cb0:	c7b200c8 */ 	lwc1	$f18,0xc8($sp)
/*  f125cb4:	468042a0 */ 	cvt.s.w	$f10,$f8
/*  f125cb8:	460a3602 */ 	mul.s	$f24,$f6,$f10
/*  f125cbc:	4618a401 */ 	sub.s	$f16,$f20,$f24
/*  f125cc0:	460c803e */ 	c.le.s	$f16,$f12
/*  f125cc4:	00000000 */ 	nop
/*  f125cc8:	45020182 */ 	bc1fl	.L0f1262d4
/*  f125ccc:	8fae0120 */ 	lw	$t6,0x120($sp)
/*  f125cd0:	4612a080 */ 	add.s	$f2,$f20,$f18
/*  f125cd4:	46181100 */ 	add.s	$f4,$f2,$f24
/*  f125cd8:	4604603c */ 	c.lt.s	$f12,$f4
/*  f125cdc:	00000000 */ 	nop
/*  f125ce0:	4502017c */ 	bc1fl	.L0f1262d4
/*  f125ce4:	8fae0120 */ 	lw	$t6,0x120($sp)
/*  f125ce8:	4618b201 */ 	sub.s	$f8,$f22,$f24
/*  f125cec:	c64e0000 */ 	lwc1	$f14,0x0($s2)
/*  f125cf0:	c7a60150 */ 	lwc1	$f6,0x150($sp)
/*  f125cf4:	460e403e */ 	c.le.s	$f8,$f14
/*  f125cf8:	00000000 */ 	nop
/*  f125cfc:	45020175 */ 	bc1fl	.L0f1262d4
/*  f125d00:	8fae0120 */ 	lw	$t6,0x120($sp)
/*  f125d04:	4606b000 */ 	add.s	$f0,$f22,$f6
/*  f125d08:	3c0c8008 */ 	lui	$t4,%hi(var8007db88)
/*  f125d0c:	258cdb88 */ 	addiu	$t4,$t4,%lo(var8007db88)
/*  f125d10:	020c6821 */ 	addu	$t5,$s0,$t4
/*  f125d14:	46180280 */ 	add.s	$f10,$f0,$f24
/*  f125d18:	460a703c */ 	c.lt.s	$f14,$f10
/*  f125d1c:	00000000 */ 	nop
/*  f125d20:	4502016c */ 	bc1fl	.L0f1262d4
/*  f125d24:	8fae0120 */ 	lw	$t6,0x120($sp)
/*  f125d28:	8fae013c */ 	lw	$t6,0x13c($sp)
/*  f125d2c:	8fb80128 */ 	lw	$t8,0x128($sp)
/*  f125d30:	460ca03e */ 	c.le.s	$f20,$f12
/*  f125d34:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f125d38:	44988000 */ 	mtc1	$t8,$f16
/*  f125d3c:	01ee7821 */ 	addu	$t7,$t7,$t6
/*  f125d40:	000f7940 */ 	sll	$t7,$t7,0x5
/*  f125d44:	afaf0098 */ 	sw	$t7,0x98($sp)
/*  f125d48:	afad009c */ 	sw	$t5,0x9c($sp)
/*  f125d4c:	450000aa */ 	bc1f	.L0f125ff8
/*  f125d50:	468087a0 */ 	cvt.s.w	$f30,$f16
/*  f125d54:	4602603c */ 	c.lt.s	$f12,$f2
/*  f125d58:	00000000 */ 	nop
/*  f125d5c:	450200a7 */ 	bc1fl	.L0f125ffc
/*  f125d60:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f125d64:	460eb03e */ 	c.le.s	$f22,$f14
/*  f125d68:	00000000 */ 	nop
/*  f125d6c:	450200a3 */ 	bc1fl	.L0f125ffc
/*  f125d70:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f125d74:	4600703c */ 	c.lt.s	$f14,$f0
/*  f125d78:	87a30166 */ 	lh	$v1,0x166($sp)
/*  f125d7c:	87a20164 */ 	lh	$v0,0x164($sp)
/*  f125d80:	87b90162 */ 	lh	$t9,0x162($sp)
/*  f125d84:	4500009c */ 	bc1f	.L0f125ff8
/*  f125d88:	2470000f */ 	addiu	$s0,$v1,0xf
/*  f125d8c:	87a80160 */ 	lh	$t0,0x160($sp)
/*  f125d90:	00799821 */ 	addu	$s3,$v1,$t9
/*  f125d94:	267efff0 */ 	addiu	$s8,$s3,-16
/*  f125d98:	0048b821 */ 	addu	$s7,$v0,$t0
/*  f125d9c:	26e9fff0 */ 	addiu	$t1,$s7,-16
/*  f125da0:	afa900a0 */ 	sw	$t1,0xa0($sp)
/*  f125da4:	0c000913 */ 	jal	bbufGetIndex0Buffer
/*  f125da8:	2455000f */ 	addiu	$s5,$v0,0xf
/*  f125dac:	c62c0000 */ 	lwc1	$f12,0x0($s1)
/*  f125db0:	3c01447a */ 	lui	$at,0x447a
/*  f125db4:	44811000 */ 	mtc1	$at,$f2
/*  f125db8:	4600648d */ 	trunc.w.s	$f18,$f12
/*  f125dbc:	240a0001 */ 	addiu	$t2,$zero,0x1
/*  f125dc0:	00403825 */ 	or	$a3,$v0,$zero
/*  f125dc4:	afaa0120 */ 	sw	$t2,0x120($sp)
/*  f125dc8:	44039000 */ 	mfc1	$v1,$f18
/*  f125dcc:	8fae00a0 */ 	lw	$t6,0xa0($sp)
/*  f125dd0:	0070082a */ 	slt	$at,$v1,$s0
/*  f125dd4:	10200008 */ 	beqz	$at,.L0f125df8
/*  f125dd8:	3c01447a */ 	lui	$at,0x447a
/*  f125ddc:	44812000 */ 	mtc1	$at,$f4
/*  f125de0:	46006006 */ 	mov.s	$f0,$f12
/*  f125de4:	4604603c */ 	c.lt.s	$f12,$f4
/*  f125de8:	00000000 */ 	nop
/*  f125dec:	45020003 */ 	bc1fl	.L0f125dfc
/*  f125df0:	c64e0000 */ 	lwc1	$f14,0x0($s2)
/*  f125df4:	46000086 */ 	mov.s	$f2,$f0
.L0f125df8:
/*  f125df8:	c64e0000 */ 	lwc1	$f14,0x0($s2)
.L0f125dfc:
/*  f125dfc:	4600720d */ 	trunc.w.s	$f8,$f14
/*  f125e00:	44024000 */ 	mfc1	$v0,$f8
/*  f125e04:	00000000 */ 	nop
/*  f125e08:	0055082a */ 	slt	$at,$v0,$s5
/*  f125e0c:	50200007 */ 	beqzl	$at,.L0f125e2c
/*  f125e10:	03c3082a */ 	slt	$at,$s8,$v1
/*  f125e14:	4602703c */ 	c.lt.s	$f14,$f2
/*  f125e18:	46007006 */ 	mov.s	$f0,$f14
/*  f125e1c:	45020003 */ 	bc1fl	.L0f125e2c
/*  f125e20:	03c3082a */ 	slt	$at,$s8,$v1
/*  f125e24:	46000086 */ 	mov.s	$f2,$f0
/*  f125e28:	03c3082a */ 	slt	$at,$s8,$v1
.L0f125e2c:
/*  f125e2c:	1020000a */ 	beqz	$at,.L0f125e58
/*  f125e30:	266dffff */ 	addiu	$t5,$s3,-1
/*  f125e34:	448d3000 */ 	mtc1	$t5,$f6
/*  f125e38:	00000000 */ 	nop
/*  f125e3c:	468032a0 */ 	cvt.s.w	$f10,$f6
/*  f125e40:	460c5001 */ 	sub.s	$f0,$f10,$f12
/*  f125e44:	4602003c */ 	c.lt.s	$f0,$f2
/*  f125e48:	00000000 */ 	nop
/*  f125e4c:	45020003 */ 	bc1fl	.L0f125e5c
/*  f125e50:	01c2082a */ 	slt	$at,$t6,$v0
/*  f125e54:	46000086 */ 	mov.s	$f2,$f0
.L0f125e58:
/*  f125e58:	01c2082a */ 	slt	$at,$t6,$v0
.L0f125e5c:
/*  f125e5c:	1020000a */ 	beqz	$at,.L0f125e88
/*  f125e60:	26efffff */ 	addiu	$t7,$s7,-1
/*  f125e64:	448f8000 */ 	mtc1	$t7,$f16
/*  f125e68:	00000000 */ 	nop
/*  f125e6c:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f125e70:	460e9001 */ 	sub.s	$f0,$f18,$f14
/*  f125e74:	4602003c */ 	c.lt.s	$f0,$f2
/*  f125e78:	00000000 */ 	nop
/*  f125e7c:	45020003 */ 	bc1fl	.L0f125e8c
/*  f125e80:	461a1081 */ 	sub.s	$f2,$f2,$f26
/*  f125e84:	46000086 */ 	mov.s	$f2,$f0
.L0f125e88:
/*  f125e88:	461a1081 */ 	sub.s	$f2,$f2,$f26
.L0f125e8c:
/*  f125e8c:	3c017f1b */ 	lui	$at,%hi(var7f1b5108)
/*  f125e90:	461c103c */ 	c.lt.s	$f2,$f28
/*  f125e94:	00000000 */ 	nop
/*  f125e98:	45000002 */ 	bc1f	.L0f125ea4
/*  f125e9c:	00000000 */ 	nop
/*  f125ea0:	4600e086 */ 	mov.s	$f2,$f28
.L0f125ea4:
/*  f125ea4:	c4245108 */ 	lwc1	$f4,%lo(var7f1b5108)($at)
/*  f125ea8:	8fb8009c */ 	lw	$t8,0x9c($sp)
/*  f125eac:	46041002 */ 	mul.s	$f0,$f2,$f4
/*  f125eb0:	4600d03c */ 	c.lt.s	$f26,$f0
/*  f125eb4:	e7000000 */ 	swc1	$f0,0x0($t8)
/*  f125eb8:	8fb9009c */ 	lw	$t9,0x9c($sp)
/*  f125ebc:	45020003 */ 	bc1fl	.L0f125ecc
/*  f125ec0:	8fa80098 */ 	lw	$t0,0x98($sp)
/*  f125ec4:	e73a0000 */ 	swc1	$f26,0x0($t9)
/*  f125ec8:	8fa80098 */ 	lw	$t0,0x98($sp)
.L0f125ecc:
/*  f125ecc:	2465fff9 */ 	addiu	$a1,$v1,-7
/*  f125ed0:	24460001 */ 	addiu	$a2,$v0,0x1
/*  f125ed4:	01078021 */ 	addu	$s0,$t0,$a3
/*  f125ed8:	0fc49652 */ 	jal	func0f125948
/*  f125edc:	02002025 */ 	or	$a0,$s0,$zero
/*  f125ee0:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f125ee4:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f125ee8:	26040014 */ 	addiu	$a0,$s0,0x14
/*  f125eec:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f125ef0:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f125ef4:	44053000 */ 	mfc1	$a1,$f6
/*  f125ef8:	44068000 */ 	mfc1	$a2,$f16
/*  f125efc:	24a5fffb */ 	addiu	$a1,$a1,-5
/*  f125f00:	0fc49652 */ 	jal	func0f125948
/*  f125f04:	24c6fffd */ 	addiu	$a2,$a2,-3
/*  f125f08:	c6320000 */ 	lwc1	$f18,0x0($s1)
/*  f125f0c:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*  f125f10:	26040028 */ 	addiu	$a0,$s0,0x28
/*  f125f14:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f125f18:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f125f1c:	44052000 */ 	mfc1	$a1,$f4
/*  f125f20:	44063000 */ 	mfc1	$a2,$f6
/*  f125f24:	24a5fffd */ 	addiu	$a1,$a1,-3
/*  f125f28:	0fc49652 */ 	jal	func0f125948
/*  f125f2c:	24c60005 */ 	addiu	$a2,$a2,0x5
/*  f125f30:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f125f34:	c6520000 */ 	lwc1	$f18,0x0($s2)
/*  f125f38:	2604003c */ 	addiu	$a0,$s0,0x3c
/*  f125f3c:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f125f40:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f125f44:	44058000 */ 	mfc1	$a1,$f16
/*  f125f48:	44062000 */ 	mfc1	$a2,$f4
/*  f125f4c:	24a5ffff */ 	addiu	$a1,$a1,-1
/*  f125f50:	0fc49652 */ 	jal	func0f125948
/*  f125f54:	24c6fff9 */ 	addiu	$a2,$a2,-7
/*  f125f58:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f125f5c:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f125f60:	26040050 */ 	addiu	$a0,$s0,0x50
/*  f125f64:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f125f68:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f125f6c:	44053000 */ 	mfc1	$a1,$f6
/*  f125f70:	44068000 */ 	mfc1	$a2,$f16
/*  f125f74:	24a50001 */ 	addiu	$a1,$a1,0x1
/*  f125f78:	0fc49652 */ 	jal	func0f125948
/*  f125f7c:	24c60007 */ 	addiu	$a2,$a2,0x7
/*  f125f80:	c6320000 */ 	lwc1	$f18,0x0($s1)
/*  f125f84:	c6480000 */ 	lwc1	$f8,0x0($s2)
/*  f125f88:	26040064 */ 	addiu	$a0,$s0,0x64
/*  f125f8c:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f125f90:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f125f94:	44052000 */ 	mfc1	$a1,$f4
/*  f125f98:	44063000 */ 	mfc1	$a2,$f6
/*  f125f9c:	24a50003 */ 	addiu	$a1,$a1,0x3
/*  f125fa0:	0fc49652 */ 	jal	func0f125948
/*  f125fa4:	24c6fffb */ 	addiu	$a2,$a2,-5
/*  f125fa8:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f125fac:	c6520000 */ 	lwc1	$f18,0x0($s2)
/*  f125fb0:	26040078 */ 	addiu	$a0,$s0,0x78
/*  f125fb4:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f125fb8:	4600910d */ 	trunc.w.s	$f4,$f18
/*  f125fbc:	44058000 */ 	mfc1	$a1,$f16
/*  f125fc0:	44062000 */ 	mfc1	$a2,$f4
/*  f125fc4:	24a50005 */ 	addiu	$a1,$a1,0x5
/*  f125fc8:	0fc49652 */ 	jal	func0f125948
/*  f125fcc:	24c60003 */ 	addiu	$a2,$a2,0x3
/*  f125fd0:	c6280000 */ 	lwc1	$f8,0x0($s1)
/*  f125fd4:	c64a0000 */ 	lwc1	$f10,0x0($s2)
/*  f125fd8:	2604008c */ 	addiu	$a0,$s0,0x8c
/*  f125fdc:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f125fe0:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f125fe4:	44053000 */ 	mfc1	$a1,$f6
/*  f125fe8:	44068000 */ 	mfc1	$a2,$f16
/*  f125fec:	24a50007 */ 	addiu	$a1,$a1,0x7
/*  f125ff0:	0fc49652 */ 	jal	func0f125948
/*  f125ff4:	24c6ffff */ 	addiu	$a2,$a2,-1
.L0f125ff8:
/*  f125ff8:	8fa20094 */ 	lw	$v0,0x94($sp)
.L0f125ffc:
/*  f125ffc:	3c0e800a */ 	lui	$t6,%hi(g_Vars+0x34)
/*  f126000:	8dce9ff4 */ 	lw	$t6,%lo(g_Vars+0x34)($t6)
/*  f126004:	8c4d0000 */ 	lw	$t5,0x0($v0)
/*  f126008:	3c05800b */ 	lui	$a1,%hi(var800ab5a0)
/*  f12600c:	24180002 */ 	addiu	$t8,$zero,0x2
/*  f126010:	01ae7821 */ 	addu	$t7,$t5,$t6
/*  f126014:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f126018:	8ca5b5a0 */ 	lw	$a1,%lo(var800ab5a0)($a1)
/*  f12601c:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f126020:	afb90014 */ 	sw	$t9,0x14($sp)
/*  f126024:	afb80010 */ 	sw	$t8,0x10($sp)
/*  f126028:	27a40170 */ 	addiu	$a0,$sp,0x170
/*  f12602c:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f126030:	00003825 */ 	or	$a3,$zero,$zero
/*  f126034:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f126038:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f12603c:	24a5003c */ 	addiu	$a1,$a1,0x003c
/*  f126040:	8fa80170 */ 	lw	$t0,0x170($sp)
/*  f126044:	3c0aba00 */ 	lui	$t2,0xba00
/*  f126048:	354a1402 */ 	ori	$t2,$t2,0x1402
/*  f12604c:	25090008 */ 	addiu	$t1,$t0,0x8
/*  f126050:	afa90170 */ 	sw	$t1,0x170($sp)
/*  f126054:	ad000004 */ 	sw	$zero,0x4($t0)
/*  f126058:	ad0a0000 */ 	sw	$t2,0x0($t0)
/*  f12605c:	8fab0170 */ 	lw	$t3,0x170($sp)
/*  f126060:	3c0dba00 */ 	lui	$t5,0xba00
/*  f126064:	35ad0602 */ 	ori	$t5,$t5,0x602
/*  f126068:	256c0008 */ 	addiu	$t4,$t3,0x8
/*  f12606c:	afac0170 */ 	sw	$t4,0x170($sp)
/*  f126070:	240e00c0 */ 	addiu	$t6,$zero,0xc0
/*  f126074:	ad6e0004 */ 	sw	$t6,0x4($t3)
/*  f126078:	ad6d0000 */ 	sw	$t5,0x0($t3)
/*  f12607c:	8faf0170 */ 	lw	$t7,0x170($sp)
/*  f126080:	3c080050 */ 	lui	$t0,0x50
/*  f126084:	3c19b900 */ 	lui	$t9,0xb900
/*  f126088:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f12608c:	afb80170 */ 	sw	$t8,0x170($sp)
/*  f126090:	3739031d */ 	ori	$t9,$t9,0x31d
/*  f126094:	350841c8 */ 	ori	$t0,$t0,0x41c8
/*  f126098:	ade80004 */ 	sw	$t0,0x4($t7)
/*  f12609c:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f1260a0:	8fa90170 */ 	lw	$t1,0x170($sp)
/*  f1260a4:	3c0bba00 */ 	lui	$t3,0xba00
/*  f1260a8:	356b1301 */ 	ori	$t3,$t3,0x1301
/*  f1260ac:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f1260b0:	afaa0170 */ 	sw	$t2,0x170($sp)
/*  f1260b4:	ad200004 */ 	sw	$zero,0x4($t1)
/*  f1260b8:	ad2b0000 */ 	sw	$t3,0x0($t1)
/*  f1260bc:	8fac0170 */ 	lw	$t4,0x170($sp)
/*  f1260c0:	3c0eb900 */ 	lui	$t6,0xb900
/*  f1260c4:	35ce0002 */ 	ori	$t6,$t6,0x2
/*  f1260c8:	258d0008 */ 	addiu	$t5,$t4,0x8
/*  f1260cc:	afad0170 */ 	sw	$t5,0x170($sp)
/*  f1260d0:	ad800004 */ 	sw	$zero,0x4($t4)
/*  f1260d4:	ad8e0000 */ 	sw	$t6,0x0($t4)
/*  f1260d8:	8faf0170 */ 	lw	$t7,0x170($sp)
/*  f1260dc:	3c19ba00 */ 	lui	$t9,0xba00
/*  f1260e0:	37391001 */ 	ori	$t9,$t9,0x1001
/*  f1260e4:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f1260e8:	afb80170 */ 	sw	$t8,0x170($sp)
/*  f1260ec:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f1260f0:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f1260f4:	8fa80170 */ 	lw	$t0,0x170($sp)
/*  f1260f8:	3c0aba00 */ 	lui	$t2,0xba00
/*  f1260fc:	354a0903 */ 	ori	$t2,$t2,0x903
/*  f126100:	25090008 */ 	addiu	$t1,$t0,0x8
/*  f126104:	afa90170 */ 	sw	$t1,0x170($sp)
/*  f126108:	240b0c00 */ 	addiu	$t3,$zero,0xc00
/*  f12610c:	ad0b0004 */ 	sw	$t3,0x4($t0)
/*  f126110:	ad0a0000 */ 	sw	$t2,0x0($t0)
/*  f126114:	8fac0170 */ 	lw	$t4,0x170($sp)
/*  f126118:	3c0eba00 */ 	lui	$t6,0xba00
/*  f12611c:	35ce0e02 */ 	ori	$t6,$t6,0xe02
/*  f126120:	258d0008 */ 	addiu	$t5,$t4,0x8
/*  f126124:	afad0170 */ 	sw	$t5,0x170($sp)
/*  f126128:	ad800004 */ 	sw	$zero,0x4($t4)
/*  f12612c:	ad8e0000 */ 	sw	$t6,0x0($t4)
/*  f126130:	8faf0170 */ 	lw	$t7,0x170($sp)
/*  f126134:	3c19ba00 */ 	lui	$t9,0xba00
/*  f126138:	37390c02 */ 	ori	$t9,$t9,0xc02
/*  f12613c:	25f80008 */ 	addiu	$t8,$t7,0x8
/*  f126140:	afb80170 */ 	sw	$t8,0x170($sp)
/*  f126144:	24082000 */ 	addiu	$t0,$zero,0x2000
/*  f126148:	ade80004 */ 	sw	$t0,0x4($t7)
/*  f12614c:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f126150:	8fa90170 */ 	lw	$t1,0x170($sp)
/*  f126154:	3c0cffa7 */ 	lui	$t4,0xffa7
/*  f126158:	3c0bfc50 */ 	lui	$t3,0xfc50
/*  f12615c:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f126160:	afaa0170 */ 	sw	$t2,0x170($sp)
/*  f126164:	356bd2a1 */ 	ori	$t3,$t3,0xd2a1
/*  f126168:	358cffff */ 	ori	$t4,$t4,0xffff
/*  f12616c:	ad2c0004 */ 	sw	$t4,0x4($t1)
/*  f126170:	ad2b0000 */ 	sw	$t3,0x0($t1)
/*  f126174:	8fa30170 */ 	lw	$v1,0x170($sp)
/*  f126178:	3c0ffb00 */ 	lui	$t7,0xfb00
/*  f12617c:	3c01437f */ 	lui	$at,0x437f
/*  f126180:	246e0008 */ 	addiu	$t6,$v1,0x8
/*  f126184:	afae0170 */ 	sw	$t6,0x170($sp)
/*  f126188:	ac6f0000 */ 	sw	$t7,0x0($v1)
/*  f12618c:	8fb8009c */ 	lw	$t8,0x9c($sp)
/*  f126190:	44812000 */ 	mtc1	$at,$f4
/*  f126194:	3c013f00 */ 	lui	$at,0x3f00
/*  f126198:	c7120000 */ 	lwc1	$f18,0x0($t8)
/*  f12619c:	93ab0148 */ 	lbu	$t3,0x148($sp)
/*  f1261a0:	93af0149 */ 	lbu	$t7,0x149($sp)
/*  f1261a4:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f1261a8:	44819000 */ 	mtc1	$at,$f18
/*  f1261ac:	93aa014a */ 	lbu	$t2,0x14a($sp)
/*  f1261b0:	000b6600 */ 	sll	$t4,$t3,0x18
/*  f1261b4:	4612c002 */ 	mul.s	$f0,$f24,$f18
/*  f1261b8:	000fc400 */ 	sll	$t8,$t7,0x10
/*  f1261bc:	000a5a00 */ 	sll	$t3,$t2,0x8
/*  f1261c0:	3c02800b */ 	lui	$v0,%hi(var800ab5a0)
/*  f1261c4:	240f0001 */ 	addiu	$t7,$zero,0x1
/*  f1261c8:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f1261cc:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f1261d0:	461e0102 */ 	mul.s	$f4,$f0,$f30
/*  f1261d4:	27a40170 */ 	addiu	$a0,$sp,0x170
/*  f1261d8:	27a50134 */ 	addiu	$a1,$sp,0x134
/*  f1261dc:	44083000 */ 	mfc1	$t0,$f6
/*  f1261e0:	27a6012c */ 	addiu	$a2,$sp,0x12c
/*  f1261e4:	310900ff */ 	andi	$t1,$t0,0xff
/*  f1261e8:	012c6825 */ 	or	$t5,$t1,$t4
/*  f1261ec:	01b8c825 */ 	or	$t9,$t5,$t8
/*  f1261f0:	032b4825 */ 	or	$t1,$t9,$t3
/*  f1261f4:	ac690004 */ 	sw	$t1,0x4($v1)
/*  f1261f8:	c62a0000 */ 	lwc1	$f10,0x0($s1)
/*  f1261fc:	c6500000 */ 	lwc1	$f16,0x0($s2)
/*  f126200:	8c42b5a0 */ 	lw	$v0,%lo(var800ab5a0)($v0)
/*  f126204:	e7a4012c */ 	swc1	$f4,0x12c($sp)
/*  f126208:	e7a00130 */ 	swc1	$f0,0x130($sp)
/*  f12620c:	e7aa0134 */ 	swc1	$f10,0x134($sp)
/*  f126210:	e7b00138 */ 	swc1	$f16,0x138($sp)
/*  f126214:	904c0041 */ 	lbu	$t4,0x41($v0)
/*  f126218:	90470040 */ 	lbu	$a3,0x40($v0)
/*  f12621c:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f126220:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f126224:	afad0020 */ 	sw	$t5,0x20($sp)
/*  f126228:	afb80028 */ 	sw	$t8,0x28($sp)
/*  f12622c:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f126230:	afaf001c */ 	sw	$t7,0x1c($sp)
/*  f126234:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f126238:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f12623c:	0fc2c854 */ 	jal	func0f0b2150
/*  f126240:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f126244:	8fa80170 */ 	lw	$t0,0x170($sp)
/*  f126248:	3c19e700 */ 	lui	$t9,0xe700
/*  f12624c:	3c0cba00 */ 	lui	$t4,0xba00
/*  f126250:	250a0008 */ 	addiu	$t2,$t0,0x8
/*  f126254:	afaa0170 */ 	sw	$t2,0x170($sp)
/*  f126258:	ad000004 */ 	sw	$zero,0x4($t0)
/*  f12625c:	ad190000 */ 	sw	$t9,0x0($t0)
/*  f126260:	8fab0170 */ 	lw	$t3,0x170($sp)
/*  f126264:	358c0602 */ 	ori	$t4,$t4,0x602
/*  f126268:	240e0040 */ 	addiu	$t6,$zero,0x40
/*  f12626c:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f126270:	afa90170 */ 	sw	$t1,0x170($sp)
/*  f126274:	ad6e0004 */ 	sw	$t6,0x4($t3)
/*  f126278:	ad6c0000 */ 	sw	$t4,0x0($t3)
/*  f12627c:	8faf0170 */ 	lw	$t7,0x170($sp)
/*  f126280:	3c18ba00 */ 	lui	$t8,0xba00
/*  f126284:	37181301 */ 	ori	$t8,$t8,0x1301
/*  f126288:	25ed0008 */ 	addiu	$t5,$t7,0x8
/*  f12628c:	afad0170 */ 	sw	$t5,0x170($sp)
/*  f126290:	3c080008 */ 	lui	$t0,0x8
/*  f126294:	ade80004 */ 	sw	$t0,0x4($t7)
/*  f126298:	adf80000 */ 	sw	$t8,0x0($t7)
/*  f12629c:	8faa0170 */ 	lw	$t2,0x170($sp)
/*  f1262a0:	3c0bba00 */ 	lui	$t3,0xba00
/*  f1262a4:	356b1001 */ 	ori	$t3,$t3,0x1001
/*  f1262a8:	25590008 */ 	addiu	$t9,$t2,0x8
/*  f1262ac:	afb90170 */ 	sw	$t9,0x170($sp)
/*  f1262b0:	3c090001 */ 	lui	$t1,0x1
/*  f1262b4:	ad490004 */ 	sw	$t1,0x4($t2)
/*  f1262b8:	0c000920 */ 	jal	bbufGetIndex1Buffer
/*  f1262bc:	ad4b0000 */ 	sw	$t3,0x0($t2)
/*  f1262c0:	8fac0098 */ 	lw	$t4,0x98($sp)
/*  f1262c4:	0fc49687 */ 	jal	func0f125a1c
/*  f1262c8:	004c2021 */ 	addu	$a0,$v0,$t4
/*  f1262cc:	e7a00124 */ 	swc1	$f0,0x124($sp)
/*  f1262d0:	8fae0120 */ 	lw	$t6,0x120($sp)
.L0f1262d4:
/*  f1262d4:	c7a80124 */ 	lwc1	$f8,0x124($sp)
/*  f1262d8:	51c0000c */ 	beqzl	$t6,.L0f12630c
/*  f1262dc:	8fa80094 */ 	lw	$t0,0x94($sp)
/*  f1262e0:	4608e03c */ 	c.lt.s	$f28,$f8
/*  f1262e4:	8fa20094 */ 	lw	$v0,0x94($sp)
/*  f1262e8:	3c0d800a */ 	lui	$t5,%hi(g_Vars+0x34)
/*  f1262ec:	45020007 */ 	bc1fl	.L0f12630c
/*  f1262f0:	8fa80094 */ 	lw	$t0,0x94($sp)
/*  f1262f4:	8c4f0000 */ 	lw	$t7,0x0($v0)
/*  f1262f8:	8dad9ff4 */ 	lw	$t5,%lo(g_Vars+0x34)($t5)
/*  f1262fc:	01edc021 */ 	addu	$t8,$t7,$t5
/*  f126300:	10000003 */ 	b	.L0f126310
/*  f126304:	ac580000 */ 	sw	$t8,0x0($v0)
/*  f126308:	8fa80094 */ 	lw	$t0,0x94($sp)
.L0f12630c:
/*  f12630c:	ad000000 */ 	sw	$zero,0x0($t0)
.L0f126310:
/*  f126310:	8faa013c */ 	lw	$t2,0x13c($sp)
.L0f126314:
/*  f126314:	8fab0144 */ 	lw	$t3,0x144($sp)
/*  f126318:	2694000c */ 	addiu	$s4,$s4,0xc
/*  f12631c:	25590001 */ 	addiu	$t9,$t2,0x1
/*  f126320:	afb9013c */ 	sw	$t9,0x13c($sp)
/*  f126324:	9169000b */ 	lbu	$t1,0xb($t3)
/*  f126328:	26d60014 */ 	addiu	$s6,$s6,0x14
/*  f12632c:	0329082a */ 	slt	$at,$t9,$t1
/*  f126330:	5420fe18 */ 	bnezl	$at,.L0f125b94
/*  f126334:	c6d00004 */ 	lwc1	$f16,0x4($s6)
/*  f126338:	8fa20170 */ 	lw	$v0,0x170($sp)
.L0f12633c:
/*  f12633c:	8fbf008c */ 	lw	$ra,0x8c($sp)
/*  f126340:	d7b40038 */ 	ldc1	$f20,0x38($sp)
/*  f126344:	d7b60040 */ 	ldc1	$f22,0x40($sp)
/*  f126348:	d7b80048 */ 	ldc1	$f24,0x48($sp)
/*  f12634c:	d7ba0050 */ 	ldc1	$f26,0x50($sp)
/*  f126350:	d7bc0058 */ 	ldc1	$f28,0x58($sp)
/*  f126354:	d7be0060 */ 	ldc1	$f30,0x60($sp)
/*  f126358:	8fb00068 */ 	lw	$s0,0x68($sp)
/*  f12635c:	8fb1006c */ 	lw	$s1,0x6c($sp)
/*  f126360:	8fb20070 */ 	lw	$s2,0x70($sp)
/*  f126364:	8fb30074 */ 	lw	$s3,0x74($sp)
/*  f126368:	8fb40078 */ 	lw	$s4,0x78($sp)
/*  f12636c:	8fb5007c */ 	lw	$s5,0x7c($sp)
/*  f126370:	8fb60080 */ 	lw	$s6,0x80($sp)
/*  f126374:	8fb70084 */ 	lw	$s7,0x84($sp)
/*  f126378:	8fbe0088 */ 	lw	$s8,0x88($sp)
/*  f12637c:	03e00008 */ 	jr	$ra
/*  f126380:	27bd0170 */ 	addiu	$sp,$sp,0x170
);
#endif

#if VERSION >= VERSION_PAL_FINAL
GLOBAL_ASM(
glabel func0f126384
.late_rodata
glabel var7f1b510c
.word 0x3c23d70a
glabel var7f1b5110
.word 0x3bda740e
glabel var7f1b5114
.word 0x3d23d70a
glabel var7f1b5118
.word 0x3c4ccccd
glabel var7f1b511c
.word 0x3dcccccd
.text
/*  f126e68:	27bdfe68 */ 	addiu	$sp,$sp,-408
/*  f126e6c:	3c0f8008 */ 	lui	$t7,0x8008
/*  f126e70:	afbf008c */ 	sw	$ra,0x8c($sp)
/*  f126e74:	afbe0088 */ 	sw	$s8,0x88($sp)
/*  f126e78:	afb70084 */ 	sw	$s7,0x84($sp)
/*  f126e7c:	afb60080 */ 	sw	$s6,0x80($sp)
/*  f126e80:	afb5007c */ 	sw	$s5,0x7c($sp)
/*  f126e84:	afb40078 */ 	sw	$s4,0x78($sp)
/*  f126e88:	afb30074 */ 	sw	$s3,0x74($sp)
/*  f126e8c:	afb20070 */ 	sw	$s2,0x70($sp)
/*  f126e90:	afb1006c */ 	sw	$s1,0x6c($sp)
/*  f126e94:	afb00068 */ 	sw	$s0,0x68($sp)
/*  f126e98:	f7be0060 */ 	sdc1	$f30,0x60($sp)
/*  f126e9c:	f7bc0058 */ 	sdc1	$f28,0x58($sp)
/*  f126ea0:	f7ba0050 */ 	sdc1	$f26,0x50($sp)
/*  f126ea4:	f7b80048 */ 	sdc1	$f24,0x48($sp)
/*  f126ea8:	f7b60040 */ 	sdc1	$f22,0x40($sp)
/*  f126eac:	f7b40038 */ 	sdc1	$f20,0x38($sp)
/*  f126eb0:	afa40198 */ 	sw	$a0,0x198($sp)
/*  f126eb4:	25efe070 */ 	addiu	$t7,$t7,-8080
/*  f126eb8:	8de10000 */ 	lw	$at,0x0($t7)
/*  f126ebc:	8de80004 */ 	lw	$t0,0x4($t7)
/*  f126ec0:	27ae0164 */ 	addiu	$t6,$sp,0x164
/*  f126ec4:	adc10000 */ 	sw	$at,0x0($t6)
/*  f126ec8:	adc80004 */ 	sw	$t0,0x4($t6)
/*  f126ecc:	8de8000c */ 	lw	$t0,0xc($t7)
/*  f126ed0:	8de10008 */ 	lw	$at,0x8($t7)
/*  f126ed4:	3c0a8008 */ 	lui	$t2,0x8008
/*  f126ed8:	adc8000c */ 	sw	$t0,0xc($t6)
/*  f126edc:	adc10008 */ 	sw	$at,0x8($t6)
/*  f126ee0:	8de10010 */ 	lw	$at,0x10($t7)
/*  f126ee4:	8de80014 */ 	lw	$t0,0x14($t7)
/*  f126ee8:	254ae088 */ 	addiu	$t2,$t2,-8056
/*  f126eec:	adc10010 */ 	sw	$at,0x10($t6)
/*  f126ef0:	adc80014 */ 	sw	$t0,0x14($t6)
/*  f126ef4:	8d4d0004 */ 	lw	$t5,0x4($t2)
/*  f126ef8:	8d410000 */ 	lw	$at,0x0($t2)
/*  f126efc:	27a9014c */ 	addiu	$t1,$sp,0x14c
/*  f126f00:	ad2d0004 */ 	sw	$t5,0x4($t1)
/*  f126f04:	ad210000 */ 	sw	$at,0x0($t1)
/*  f126f08:	8d410008 */ 	lw	$at,0x8($t2)
/*  f126f0c:	8d4d000c */ 	lw	$t5,0xc($t2)
/*  f126f10:	3c188008 */ 	lui	$t8,0x8008
/*  f126f14:	ad210008 */ 	sw	$at,0x8($t1)
/*  f126f18:	ad2d000c */ 	sw	$t5,0xc($t1)
/*  f126f1c:	8d4d0014 */ 	lw	$t5,0x14($t2)
/*  f126f20:	8d410010 */ 	lw	$at,0x10($t2)
/*  f126f24:	2718e0a0 */ 	addiu	$t8,$t8,-8032
/*  f126f28:	ad2d0014 */ 	sw	$t5,0x14($t1)
/*  f126f2c:	ad210010 */ 	sw	$at,0x10($t1)
/*  f126f30:	8f080004 */ 	lw	$t0,0x4($t8)
/*  f126f34:	8f010000 */ 	lw	$at,0x0($t8)
/*  f126f38:	27b90134 */ 	addiu	$t9,$sp,0x134
/*  f126f3c:	af280004 */ 	sw	$t0,0x4($t9)
/*  f126f40:	af210000 */ 	sw	$at,0x0($t9)
/*  f126f44:	8f010008 */ 	lw	$at,0x8($t8)
/*  f126f48:	8f08000c */ 	lw	$t0,0xc($t8)
/*  f126f4c:	4487b000 */ 	mtc1	$a3,$f22
/*  f126f50:	af210008 */ 	sw	$at,0x8($t9)
/*  f126f54:	af28000c */ 	sw	$t0,0xc($t9)
/*  f126f58:	8f080014 */ 	lw	$t0,0x14($t8)
/*  f126f5c:	8f010010 */ 	lw	$at,0x10($t8)
/*  f126f60:	4485d000 */ 	mtc1	$a1,$f26
/*  f126f64:	4486e000 */ 	mtc1	$a2,$f28
/*  f126f68:	af280014 */ 	sw	$t0,0x14($t9)
/*  f126f6c:	0c002e73 */ 	jal	viGetViewWidth
/*  f126f70:	af210010 */ 	sw	$at,0x10($t9)
/*  f126f74:	44822000 */ 	mtc1	$v0,$f4
/*  f126f78:	3c017f1b */ 	lui	$at,0x7f1b
/*  f126f7c:	c43463fc */ 	lwc1	$f20,0x63fc($at)
/*  f126f80:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f126f84:	3c013f00 */ 	lui	$at,0x3f00
/*  f126f88:	4481f000 */ 	mtc1	$at,$f30
/*  f126f8c:	00000000 */ 	nop
/*  f126f90:	461e3202 */ 	mul.s	$f8,$f6,$f30
/*  f126f94:	4608d281 */ 	sub.s	$f10,$f26,$f8
/*  f126f98:	46145102 */ 	mul.s	$f4,$f10,$f20
/*  f126f9c:	0c002e77 */ 	jal	viGetViewHeight
/*  f126fa0:	e7a40130 */ 	swc1	$f4,0x130($sp)
/*  f126fa4:	44823000 */ 	mtc1	$v0,$f6
/*  f126fa8:	3c16800b */ 	lui	$s6,0x800b
/*  f126fac:	26d6bb40 */ 	addiu	$s6,$s6,-17600
/*  f126fb0:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f126fb4:	8ec50000 */ 	lw	$a1,0x0($s6)
/*  f126fb8:	27b50198 */ 	addiu	$s5,$sp,0x198
/*  f126fbc:	240c0002 */ 	li	$t4,0x2
/*  f126fc0:	240b0001 */ 	li	$t3,0x1
/*  f126fc4:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f126fc8:	461e4282 */ 	mul.s	$f10,$f8,$f30
/*  f126fcc:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f126fd0:	02a02025 */ 	move	$a0,$s5
/*  f126fd4:	24060004 */ 	li	$a2,0x4
/*  f126fd8:	00003825 */ 	move	$a3,$zero
/*  f126fdc:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f126fe0:	24a50048 */ 	addiu	$a1,$a1,0x48
/*  f126fe4:	460ae101 */ 	sub.s	$f4,$f28,$f10
/*  f126fe8:	46142182 */ 	mul.s	$f6,$f4,$f20
/*  f126fec:	0fc2cfb8 */ 	jal	func0f0b39c0
/*  f126ff0:	e7a6012c */ 	swc1	$f6,0x12c($sp)
/*  f126ff4:	8fa90198 */ 	lw	$t1,0x198($sp)
/*  f126ff8:	3c10ba00 */ 	lui	$s0,0xba00
/*  f126ffc:	36101402 */ 	ori	$s0,$s0,0x1402
/*  f127000:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f127004:	afaa0198 */ 	sw	$t2,0x198($sp)
/*  f127008:	ad200004 */ 	sw	$zero,0x4($t1)
/*  f12700c:	ad300000 */ 	sw	$s0,0x0($t1)
/*  f127010:	8fad0198 */ 	lw	$t5,0x198($sp)
/*  f127014:	3c0eba00 */ 	lui	$t6,0xba00
/*  f127018:	35ce0602 */ 	ori	$t6,$t6,0x602
/*  f12701c:	25af0008 */ 	addiu	$t7,$t5,0x8
/*  f127020:	afaf0198 */ 	sw	$t7,0x198($sp)
/*  f127024:	24190040 */ 	li	$t9,0x40
/*  f127028:	adb90004 */ 	sw	$t9,0x4($t5)
/*  f12702c:	adae0000 */ 	sw	$t6,0x0($t5)
/*  f127030:	8fb80198 */ 	lw	$t8,0x198($sp)
/*  f127034:	3c0cba00 */ 	lui	$t4,0xba00
/*  f127038:	358c0402 */ 	ori	$t4,$t4,0x402
/*  f12703c:	27080008 */ 	addiu	$t0,$t8,0x8
/*  f127040:	afa80198 */ 	sw	$t0,0x198($sp)
/*  f127044:	af000004 */ 	sw	$zero,0x4($t8)
/*  f127048:	af0c0000 */ 	sw	$t4,0x0($t8)
/*  f12704c:	8fab0198 */ 	lw	$t3,0x198($sp)
/*  f127050:	3c11b900 */ 	lui	$s1,0xb900
/*  f127054:	3c120050 */ 	lui	$s2,0x50
/*  f127058:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f12705c:	afa90198 */ 	sw	$t1,0x198($sp)
/*  f127060:	365241c8 */ 	ori	$s2,$s2,0x41c8
/*  f127064:	3631031d */ 	ori	$s1,$s1,0x31d
/*  f127068:	ad710000 */ 	sw	$s1,0x0($t3)
/*  f12706c:	ad720004 */ 	sw	$s2,0x4($t3)
/*  f127070:	8faa0198 */ 	lw	$t2,0x198($sp)
/*  f127074:	3c0fba00 */ 	lui	$t7,0xba00
/*  f127078:	35ef1301 */ 	ori	$t7,$t7,0x1301
/*  f12707c:	254d0008 */ 	addiu	$t5,$t2,0x8
/*  f127080:	afad0198 */ 	sw	$t5,0x198($sp)
/*  f127084:	ad400004 */ 	sw	$zero,0x4($t2)
/*  f127088:	ad4f0000 */ 	sw	$t7,0x0($t2)
/*  f12708c:	8fae0198 */ 	lw	$t6,0x198($sp)
/*  f127090:	3c13b900 */ 	lui	$s3,0xb900
/*  f127094:	36730002 */ 	ori	$s3,$s3,0x2
/*  f127098:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f12709c:	afb90198 */ 	sw	$t9,0x198($sp)
/*  f1270a0:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f1270a4:	add30000 */ 	sw	$s3,0x0($t6)
/*  f1270a8:	8fb80198 */ 	lw	$t8,0x198($sp)
/*  f1270ac:	3c0cba00 */ 	lui	$t4,0xba00
/*  f1270b0:	358c1001 */ 	ori	$t4,$t4,0x1001
/*  f1270b4:	27080008 */ 	addiu	$t0,$t8,0x8
/*  f1270b8:	afa80198 */ 	sw	$t0,0x198($sp)
/*  f1270bc:	af000004 */ 	sw	$zero,0x4($t8)
/*  f1270c0:	af0c0000 */ 	sw	$t4,0x0($t8)
/*  f1270c4:	8fab0198 */ 	lw	$t3,0x198($sp)
/*  f1270c8:	3c14ba00 */ 	lui	$s4,0xba00
/*  f1270cc:	36940903 */ 	ori	$s4,$s4,0x903
/*  f1270d0:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f1270d4:	afa90198 */ 	sw	$t1,0x198($sp)
/*  f1270d8:	240a0c00 */ 	li	$t2,0xc00
/*  f1270dc:	ad6a0004 */ 	sw	$t2,0x4($t3)
/*  f1270e0:	ad740000 */ 	sw	$s4,0x0($t3)
/*  f1270e4:	8fad0198 */ 	lw	$t5,0x198($sp)
/*  f1270e8:	3c0eba00 */ 	lui	$t6,0xba00
/*  f1270ec:	35ce0e02 */ 	ori	$t6,$t6,0xe02
/*  f1270f0:	25af0008 */ 	addiu	$t7,$t5,0x8
/*  f1270f4:	afaf0198 */ 	sw	$t7,0x198($sp)
/*  f1270f8:	ada00004 */ 	sw	$zero,0x4($t5)
/*  f1270fc:	adae0000 */ 	sw	$t6,0x0($t5)
/*  f127100:	8fb90198 */ 	lw	$t9,0x198($sp)
/*  f127104:	3c08ba00 */ 	lui	$t0,0xba00
/*  f127108:	35080c02 */ 	ori	$t0,$t0,0xc02
/*  f12710c:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f127110:	afb80198 */ 	sw	$t8,0x198($sp)
/*  f127114:	240c2000 */ 	li	$t4,0x2000
/*  f127118:	af2c0004 */ 	sw	$t4,0x4($t9)
/*  f12711c:	af280000 */ 	sw	$t0,0x0($t9)
/*  f127120:	8fab0198 */ 	lw	$t3,0x198($sp)
/*  f127124:	3c0dff36 */ 	lui	$t5,0xff36
/*  f127128:	3c0afcff */ 	lui	$t2,0xfcff
/*  f12712c:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f127130:	afa90198 */ 	sw	$t1,0x198($sp)
/*  f127134:	354a9bff */ 	ori	$t2,$t2,0x9bff
/*  f127138:	35adff7f */ 	ori	$t5,$t5,0xff7f
/*  f12713c:	ad6d0004 */ 	sw	$t5,0x4($t3)
/*  f127140:	0c002eee */ 	jal	viGetFovY
/*  f127144:	ad6a0000 */ 	sw	$t2,0x0($t3)
/*  f127148:	8faf0198 */ 	lw	$t7,0x198($sp)
/*  f12714c:	3c17fb00 */ 	lui	$s7,0xfb00
/*  f127150:	3c013f00 */ 	lui	$at,0x3f00
/*  f127154:	25ee0008 */ 	addiu	$t6,$t7,0x8
/*  f127158:	afae0198 */ 	sw	$t6,0x198($sp)
/*  f12715c:	adf70000 */ 	sw	$s7,0x0($t7)
/*  f127160:	c7a801b0 */ 	lwc1	$f8,0x1b0($sp)
/*  f127164:	4481a000 */ 	mtc1	$at,$f20
/*  f127168:	3c01437f */ 	lui	$at,0x437f
/*  f12716c:	46164282 */ 	mul.s	$f10,$f8,$f22
/*  f127170:	44812000 */ 	mtc1	$at,$f4
/*  f127174:	2401ff00 */ 	li	$at,-256
/*  f127178:	240a0001 */ 	li	$t2,0x1
/*  f12717c:	27be0184 */ 	addiu	$s8,$sp,0x184
/*  f127180:	240e0001 */ 	li	$t6,0x1
/*  f127184:	24190001 */ 	li	$t9,0x1
/*  f127188:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f12718c:	03c02825 */ 	move	$a1,$s8
/*  f127190:	02a02025 */ 	move	$a0,$s5
/*  f127194:	4616a102 */ 	mul.s	$f4,$f20,$f22
/*  f127198:	27a6017c */ 	addiu	$a2,$sp,0x17c
/*  f12719c:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f1271a0:	4604a180 */ 	add.s	$f6,$f20,$f4
/*  f1271a4:	44184000 */ 	mfc1	$t8,$f8
/*  f1271a8:	00000000 */ 	nop
/*  f1271ac:	330800ff */ 	andi	$t0,$t8,0xff
/*  f1271b0:	01016025 */ 	or	$t4,$t0,$at
/*  f1271b4:	adec0004 */ 	sw	$t4,0x4($t7)
/*  f1271b8:	c7aa01a8 */ 	lwc1	$f10,0x1a8($sp)
/*  f1271bc:	3c014270 */ 	lui	$at,0x4270
/*  f1271c0:	44812000 */ 	mtc1	$at,$f4
/*  f1271c4:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f1271c8:	8ec20000 */ 	lw	$v0,0x0($s6)
/*  f1271cc:	e7ba0184 */ 	swc1	$f26,0x184($sp)
/*  f1271d0:	e7bc0188 */ 	swc1	$f28,0x188($sp)
/*  f1271d4:	240f0001 */ 	li	$t7,0x1
/*  f1271d8:	24180001 */ 	li	$t8,0x1
/*  f1271dc:	46002283 */ 	div.s	$f10,$f4,$f0
/*  f1271e0:	46085182 */ 	mul.s	$f6,$f10,$f8
/*  f1271e4:	4600310d */ 	trunc.w.s	$f4,$f6
/*  f1271e8:	448a3000 */ 	mtc1	$t2,$f6
/*  f1271ec:	44092000 */ 	mfc1	$t1,$f4
/*  f1271f0:	46803620 */ 	cvt.s.w	$f24,$f6
/*  f1271f4:	44895000 */ 	mtc1	$t1,$f10
/*  f1271f8:	00000000 */ 	nop
/*  f1271fc:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f127200:	46144082 */ 	mul.s	$f2,$f8,$f20
/*  f127204:	00000000 */ 	nop
/*  f127208:	46181102 */ 	mul.s	$f4,$f2,$f24
/*  f12720c:	e7a20180 */ 	swc1	$f2,0x180($sp)
/*  f127210:	e7a4017c */ 	swc1	$f4,0x17c($sp)
/*  f127214:	904d004d */ 	lbu	$t5,0x4d($v0)
/*  f127218:	9047004c */ 	lbu	$a3,0x4c($v0)
/*  f12721c:	afb80028 */ 	sw	$t8,0x28($sp)
/*  f127220:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f127224:	afb90020 */ 	sw	$t9,0x20($sp)
/*  f127228:	afae001c */ 	sw	$t6,0x1c($sp)
/*  f12722c:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f127230:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f127234:	0fc2c99c */ 	jal	func0f0b2150
/*  f127238:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f12723c:	8ec50000 */ 	lw	$a1,0x0($s6)
/*  f127240:	24080002 */ 	li	$t0,0x2
/*  f127244:	240c0001 */ 	li	$t4,0x1
/*  f127248:	afac0014 */ 	sw	$t4,0x14($sp)
/*  f12724c:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f127250:	02a02025 */ 	move	$a0,$s5
/*  f127254:	24060004 */ 	li	$a2,0x4
/*  f127258:	00003825 */ 	move	$a3,$zero
/*  f12725c:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f127260:	0fc2cfb8 */ 	jal	func0f0b39c0
/*  f127264:	24a5000c */ 	addiu	$a1,$a1,0xc
/*  f127268:	8fab0198 */ 	lw	$t3,0x198($sp)
/*  f12726c:	3c0fba00 */ 	lui	$t7,0xba00
/*  f127270:	35ef0602 */ 	ori	$t7,$t7,0x602
/*  f127274:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f127278:	afa90198 */ 	sw	$t1,0x198($sp)
/*  f12727c:	ad600004 */ 	sw	$zero,0x4($t3)
/*  f127280:	ad700000 */ 	sw	$s0,0x0($t3)
/*  f127284:	8faa0198 */ 	lw	$t2,0x198($sp)
/*  f127288:	240e0040 */ 	li	$t6,0x40
/*  f12728c:	3c08ba00 */ 	lui	$t0,0xba00
/*  f127290:	254d0008 */ 	addiu	$t5,$t2,0x8
/*  f127294:	afad0198 */ 	sw	$t5,0x198($sp)
/*  f127298:	ad4e0004 */ 	sw	$t6,0x4($t2)
/*  f12729c:	ad4f0000 */ 	sw	$t7,0x0($t2)
/*  f1272a0:	8fb90198 */ 	lw	$t9,0x198($sp)
/*  f1272a4:	35080402 */ 	ori	$t0,$t0,0x402
/*  f1272a8:	3c0dba00 */ 	lui	$t5,0xba00
/*  f1272ac:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f1272b0:	afb80198 */ 	sw	$t8,0x198($sp)
/*  f1272b4:	af200004 */ 	sw	$zero,0x4($t9)
/*  f1272b8:	af280000 */ 	sw	$t0,0x0($t9)
/*  f1272bc:	8fac0198 */ 	lw	$t4,0x198($sp)
/*  f1272c0:	35ad1301 */ 	ori	$t5,$t5,0x1301
/*  f1272c4:	3c08ba00 */ 	lui	$t0,0xba00
/*  f1272c8:	258b0008 */ 	addiu	$t3,$t4,0x8
/*  f1272cc:	afab0198 */ 	sw	$t3,0x198($sp)
/*  f1272d0:	ad920004 */ 	sw	$s2,0x4($t4)
/*  f1272d4:	ad910000 */ 	sw	$s1,0x0($t4)
/*  f1272d8:	8fa90198 */ 	lw	$t1,0x198($sp)
/*  f1272dc:	35081001 */ 	ori	$t0,$t0,0x1001
/*  f1272e0:	3c017f1b */ 	lui	$at,0x7f1b
/*  f1272e4:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f1272e8:	afaa0198 */ 	sw	$t2,0x198($sp)
/*  f1272ec:	ad200004 */ 	sw	$zero,0x4($t1)
/*  f1272f0:	ad2d0000 */ 	sw	$t5,0x0($t1)
/*  f1272f4:	8faf0198 */ 	lw	$t7,0x198($sp)
/*  f1272f8:	24090c00 */ 	li	$t1,0xc00
/*  f1272fc:	4480b000 */ 	mtc1	$zero,$f22
/*  f127300:	25ee0008 */ 	addiu	$t6,$t7,0x8
/*  f127304:	afae0198 */ 	sw	$t6,0x198($sp)
/*  f127308:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f12730c:	adf30000 */ 	sw	$s3,0x0($t7)
/*  f127310:	8fb90198 */ 	lw	$t9,0x198($sp)
/*  f127314:	3c0fba00 */ 	lui	$t7,0xba00
/*  f127318:	35ef0e02 */ 	ori	$t7,$t7,0xe02
/*  f12731c:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f127320:	afb80198 */ 	sw	$t8,0x198($sp)
/*  f127324:	af200004 */ 	sw	$zero,0x4($t9)
/*  f127328:	af280000 */ 	sw	$t0,0x0($t9)
/*  f12732c:	8fac0198 */ 	lw	$t4,0x198($sp)
/*  f127330:	3c18ba00 */ 	lui	$t8,0xba00
/*  f127334:	37180c02 */ 	ori	$t8,$t8,0xc02
/*  f127338:	258b0008 */ 	addiu	$t3,$t4,0x8
/*  f12733c:	afab0198 */ 	sw	$t3,0x198($sp)
/*  f127340:	ad890004 */ 	sw	$t1,0x4($t4)
/*  f127344:	ad940000 */ 	sw	$s4,0x0($t4)
/*  f127348:	8faa0198 */ 	lw	$t2,0x198($sp)
/*  f12734c:	24082000 */ 	li	$t0,0x2000
/*  f127350:	3c09fcff */ 	lui	$t1,0xfcff
/*  f127354:	254d0008 */ 	addiu	$t5,$t2,0x8
/*  f127358:	afad0198 */ 	sw	$t5,0x198($sp)
/*  f12735c:	ad400004 */ 	sw	$zero,0x4($t2)
/*  f127360:	ad4f0000 */ 	sw	$t7,0x0($t2)
/*  f127364:	8fae0198 */ 	lw	$t6,0x198($sp)
/*  f127368:	3c0aff36 */ 	lui	$t2,0xff36
/*  f12736c:	354aff7f */ 	ori	$t2,$t2,0xff7f
/*  f127370:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f127374:	afb90198 */ 	sw	$t9,0x198($sp)
/*  f127378:	adc80004 */ 	sw	$t0,0x4($t6)
/*  f12737c:	add80000 */ 	sw	$t8,0x0($t6)
/*  f127380:	8fac0198 */ 	lw	$t4,0x198($sp)
/*  f127384:	35299bff */ 	ori	$t1,$t1,0x9bff
/*  f127388:	27b4014c */ 	addiu	$s4,$sp,0x14c
/*  f12738c:	258b0008 */ 	addiu	$t3,$t4,0x8
/*  f127390:	afab0198 */ 	sw	$t3,0x198($sp)
/*  f127394:	ad8a0004 */ 	sw	$t2,0x4($t4)
/*  f127398:	ad890000 */ 	sw	$t1,0x0($t4)
/*  f12739c:	c43e6400 */ 	lwc1	$f30,0x6400($at)
/*  f1273a0:	3c014316 */ 	lui	$at,0x4316
/*  f1273a4:	e7bc01a0 */ 	swc1	$f28,0x1a0($sp)
/*  f1273a8:	4481e000 */ 	mtc1	$at,$f28
/*  f1273ac:	3c013f80 */ 	lui	$at,0x3f80
/*  f1273b0:	e7ba019c */ 	swc1	$f26,0x19c($sp)
/*  f1273b4:	4481d000 */ 	mtc1	$at,$f26
/*  f1273b8:	3c017f1b */ 	lui	$at,0x7f1b
/*  f1273bc:	e7b80094 */ 	swc1	$f24,0x94($sp)
/*  f1273c0:	c4386404 */ 	lwc1	$f24,0x6404($at)
/*  f1273c4:	8fb301ac */ 	lw	$s3,0x1ac($sp)
/*  f1273c8:	27b1014c */ 	addiu	$s1,$sp,0x14c
/*  f1273cc:	27b20164 */ 	addiu	$s2,$sp,0x164
/*  f1273d0:	27b00134 */ 	addiu	$s0,$sp,0x134
.PF0f1273d4:
/*  f1273d4:	2a61004b */ 	slti	$at,$s3,0x4b
/*  f1273d8:	1020000c */ 	beqz	$at,.PF0f12740c
/*  f1273dc:	266dffb5 */ 	addiu	$t5,$s3,-75
/*  f1273e0:	2a610019 */ 	slti	$at,$s3,0x19
/*  f1273e4:	10200007 */ 	beqz	$at,.PF0f127404
/*  f1273e8:	00000000 */ 	nop
/*  f1273ec:	44935000 */ 	mtc1	$s3,$f10
/*  f1273f0:	00000000 */ 	nop
/*  f1273f4:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f1273f8:	46184082 */ 	mul.s	$f2,$f8,$f24
/*  f1273fc:	10000011 */ 	b	.PF0f127444
/*  f127400:	8e2f0000 */ 	lw	$t7,0x0($s1)
.PF0f127404:
/*  f127404:	1000000e */ 	b	.PF0f127440
/*  f127408:	4600d086 */ 	mov.s	$f2,$f26
.PF0f12740c:
/*  f12740c:	448d3000 */ 	mtc1	$t5,$f6
/*  f127410:	00000000 */ 	nop
/*  f127414:	46803120 */ 	cvt.s.w	$f4,$f6
/*  f127418:	4604e281 */ 	sub.s	$f10,$f28,$f4
/*  f12741c:	461e5202 */ 	mul.s	$f8,$f10,$f30
/*  f127420:	00000000 */ 	nop
/*  f127424:	46144082 */ 	mul.s	$f2,$f8,$f20
/*  f127428:	4616103c */ 	c.lt.s	$f2,$f22
/*  f12742c:	00000000 */ 	nop
/*  f127430:	45000002 */ 	bc1f	.PF0f12743c
/*  f127434:	00000000 */ 	nop
/*  f127438:	4600b086 */ 	mov.s	$f2,$f22
.PF0f12743c:
/*  f12743c:	46141080 */ 	add.s	$f2,$f2,$f20
.PF0f127440:
/*  f127440:	8e2f0000 */ 	lw	$t7,0x0($s1)
.PF0f127444:
/*  f127444:	c7aa0130 */ 	lwc1	$f10,0x130($sp)
/*  f127448:	8fa30198 */ 	lw	$v1,0x198($sp)
/*  f12744c:	448f3000 */ 	mtc1	$t7,$f6
/*  f127450:	c7a4019c */ 	lwc1	$f4,0x19c($sp)
/*  f127454:	8e4e0000 */ 	lw	$t6,0x0($s2)
/*  f127458:	46803020 */ 	cvt.s.w	$f0,$f6
/*  f12745c:	24780008 */ 	addiu	$t8,$v1,0x8
/*  f127460:	c7a601a0 */ 	lwc1	$f6,0x1a0($sp)
/*  f127464:	afb80198 */ 	sw	$t8,0x198($sp)
/*  f127468:	3c014f80 */ 	lui	$at,0x4f80
/*  f12746c:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f127470:	c7aa012c */ 	lwc1	$f10,0x12c($sp)
/*  f127474:	ac770000 */ 	sw	$s7,0x0($v1)
/*  f127478:	8e020000 */ 	lw	$v0,0x0($s0)
/*  f12747c:	304800ff */ 	andi	$t0,$v0,0xff
/*  f127480:	46082301 */ 	sub.s	$f12,$f4,$f8
/*  f127484:	460a0102 */ 	mul.s	$f4,$f0,$f10
/*  f127488:	448e4000 */ 	mtc1	$t6,$f8
/*  f12748c:	44885000 */ 	mtc1	$t0,$f10
/*  f127490:	46804420 */ 	cvt.s.w	$f16,$f8
/*  f127494:	c7a801b0 */ 	lwc1	$f8,0x1b0($sp)
/*  f127498:	46043381 */ 	sub.s	$f14,$f6,$f4
/*  f12749c:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f1274a0:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f1274a4:	05010004 */ 	bgez	$t0,.PF0f1274b8
/*  f1274a8:	00000000 */ 	nop
/*  f1274ac:	44812000 */ 	mtc1	$at,$f4
/*  f1274b0:	00000000 */ 	nop
/*  f1274b4:	46043180 */ 	add.s	$f6,$f6,$f4
.PF0f1274b8:
/*  f1274b8:	460a3102 */ 	mul.s	$f4,$f6,$f10
/*  f1274bc:	02a02025 */ 	move	$a0,$s5
/*  f1274c0:	00027e02 */ 	srl	$t7,$v0,0x18
/*  f1274c4:	000f7600 */ 	sll	$t6,$t7,0x18
/*  f1274c8:	00024402 */ 	srl	$t0,$v0,0x10
/*  f1274cc:	310c00ff */ 	andi	$t4,$t0,0xff
/*  f1274d0:	00027a02 */ 	srl	$t7,$v0,0x8
/*  f1274d4:	4600220d */ 	trunc.w.s	$f8,$f4
/*  f1274d8:	46148482 */ 	mul.s	$f18,$f16,$f20
/*  f1274dc:	03c02825 */ 	move	$a1,$s8
/*  f1274e0:	27a6017c */ 	addiu	$a2,$sp,0x17c
/*  f1274e4:	440b4000 */ 	mfc1	$t3,$f8
/*  f1274e8:	00000000 */ 	nop
/*  f1274ec:	316900ff */ 	andi	$t1,$t3,0xff
/*  f1274f0:	012ec825 */ 	or	$t9,$t1,$t6
/*  f1274f4:	31e900ff */ 	andi	$t1,$t7,0xff
/*  f1274f8:	000c5c00 */ 	sll	$t3,$t4,0x10
/*  f1274fc:	032b5025 */ 	or	$t2,$t9,$t3
/*  f127500:	00097200 */ 	sll	$t6,$t1,0x8
/*  f127504:	014ec025 */ 	or	$t8,$t2,$t6
/*  f127508:	ac780004 */ 	sw	$t8,0x4($v1)
/*  f12750c:	c7a60094 */ 	lwc1	$f6,0x94($sp)
/*  f127510:	8ec20000 */ 	lw	$v0,0x0($s6)
/*  f127514:	e7ac0184 */ 	swc1	$f12,0x184($sp)
/*  f127518:	46069282 */ 	mul.s	$f10,$f18,$f6
/*  f12751c:	e7ae0188 */ 	swc1	$f14,0x188($sp)
/*  f127520:	e7b20180 */ 	swc1	$f18,0x180($sp)
/*  f127524:	240c0001 */ 	li	$t4,0x1
/*  f127528:	e7aa017c */ 	swc1	$f10,0x17c($sp)
/*  f12752c:	90480011 */ 	lbu	$t0,0x11($v0)
/*  f127530:	90470010 */ 	lbu	$a3,0x10($v0)
/*  f127534:	afac0028 */ 	sw	$t4,0x28($sp)
/*  f127538:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f12753c:	afa00020 */ 	sw	$zero,0x20($sp)
/*  f127540:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f127544:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f127548:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f12754c:	0fc2c99c */ 	jal	func0f0b2150
/*  f127550:	afa80010 */ 	sw	$t0,0x10($sp)
/*  f127554:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f127558:	26310004 */ 	addiu	$s1,$s1,0x4
/*  f12755c:	1614ff9d */ 	bne	$s0,$s4,.PF0f1273d4
/*  f127560:	26520004 */ 	addiu	$s2,$s2,0x4
/*  f127564:	0c002e73 */ 	jal	viGetViewWidth
/*  f127568:	00000000 */ 	nop
/*  f12756c:	44822000 */ 	mtc1	$v0,$f4
/*  f127570:	3c013f00 */ 	lui	$at,0x3f00
/*  f127574:	4481c000 */ 	mtc1	$at,$f24
/*  f127578:	46802220 */ 	cvt.s.w	$f8,$f4
/*  f12757c:	c7aa019c */ 	lwc1	$f10,0x19c($sp)
/*  f127580:	46184182 */ 	mul.s	$f6,$f8,$f24
/*  f127584:	0c002e77 */ 	jal	viGetViewHeight
/*  f127588:	460a3501 */ 	sub.s	$f20,$f6,$f10
/*  f12758c:	44822000 */ 	mtc1	$v0,$f4
/*  f127590:	c7aa01a0 */ 	lwc1	$f10,0x1a0($sp)
/*  f127594:	46802220 */ 	cvt.s.w	$f8,$f4
/*  f127598:	46184182 */ 	mul.s	$f6,$f8,$f24
/*  f12759c:	460a3001 */ 	sub.s	$f0,$f6,$f10
/*  f1275a0:	4614a102 */ 	mul.s	$f4,$f20,$f20
/*  f1275a4:	00000000 */ 	nop
/*  f1275a8:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f1275ac:	0c0127b4 */ 	jal	sqrtf
/*  f1275b0:	46082300 */ 	add.s	$f12,$f4,$f8
/*  f1275b4:	3c014220 */ 	lui	$at,0x4220
/*  f1275b8:	44813000 */ 	mtc1	$at,$f6
/*  f1275bc:	3c017f1b */ 	lui	$at,0x7f1b
/*  f1275c0:	c4246408 */ 	lwc1	$f4,0x6408($at)
/*  f1275c4:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f1275c8:	3c19800a */ 	lui	$t9,0x800a
/*  f1275cc:	c7a601b0 */ 	lwc1	$f6,0x1b0($sp)
/*  f1275d0:	46045302 */ 	mul.s	$f12,$f10,$f4
/*  f1275d4:	4616603c */ 	c.lt.s	$f12,$f22
/*  f1275d8:	00000000 */ 	nop
/*  f1275dc:	45000002 */ 	bc1f	.PF0f1275e8
/*  f1275e0:	00000000 */ 	nop
/*  f1275e4:	4600b306 */ 	mov.s	$f12,$f22
.PF0f1275e8:
/*  f1275e8:	8f39a544 */ 	lw	$t9,-0x5abc($t9)
/*  f1275ec:	3c017f1b */ 	lui	$at,0x7f1b
/*  f1275f0:	c428640c */ 	lwc1	$f8,0x640c($at)
/*  f1275f4:	0333082a */ 	slt	$at,$t9,$s3
/*  f1275f8:	14200002 */ 	bnez	$at,.PF0f127604
/*  f1275fc:	46086300 */ 	add.s	$f12,$f12,$f8
/*  f127600:	4600b306 */ 	mov.s	$f12,$f22
.PF0f127604:
/*  f127604:	460cb03c */ 	c.lt.s	$f22,$f12
/*  f127608:	00000000 */ 	nop
/*  f12760c:	4502000d */ 	bc1fl	.PF0f127644
/*  f127610:	8fad0198 */ 	lw	$t5,0x198($sp)
/*  f127614:	460c3282 */ 	mul.s	$f10,$f6,$f12
/*  f127618:	3c01437f */ 	lui	$at,0x437f
/*  f12761c:	44812000 */ 	mtc1	$at,$f4
/*  f127620:	00000000 */ 	nop
/*  f127624:	46045202 */ 	mul.s	$f8,$f10,$f4
/*  f127628:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f12762c:	44043000 */ 	mfc1	$a0,$f6
/*  f127630:	00000000 */ 	nop
/*  f127634:	00802825 */ 	move	$a1,$a0
/*  f127638:	0fc49f81 */ 	jal	func0f127334
/*  f12763c:	00803025 */ 	move	$a2,$a0
/*  f127640:	8fad0198 */ 	lw	$t5,0x198($sp)
.PF0f127644:
/*  f127644:	3c09ba00 */ 	lui	$t1,0xba00
/*  f127648:	35290602 */ 	ori	$t1,$t1,0x602
/*  f12764c:	25af0008 */ 	addiu	$t7,$t5,0x8
/*  f127650:	afaf0198 */ 	sw	$t7,0x198($sp)
/*  f127654:	240a0040 */ 	li	$t2,0x40
/*  f127658:	adaa0004 */ 	sw	$t2,0x4($t5)
/*  f12765c:	ada90000 */ 	sw	$t1,0x0($t5)
/*  f127660:	8fae0198 */ 	lw	$t6,0x198($sp)
/*  f127664:	3c08ba00 */ 	lui	$t0,0xba00
/*  f127668:	35080402 */ 	ori	$t0,$t0,0x402
/*  f12766c:	25d80008 */ 	addiu	$t8,$t6,0x8
/*  f127670:	afb80198 */ 	sw	$t8,0x198($sp)
/*  f127674:	240c00c0 */ 	li	$t4,0xc0
/*  f127678:	adcc0004 */ 	sw	$t4,0x4($t6)
/*  f12767c:	adc80000 */ 	sw	$t0,0x0($t6)
/*  f127680:	8fb90198 */ 	lw	$t9,0x198($sp)
/*  f127684:	3c0dba00 */ 	lui	$t5,0xba00
/*  f127688:	35ad1301 */ 	ori	$t5,$t5,0x1301
/*  f12768c:	272b0008 */ 	addiu	$t3,$t9,0x8
/*  f127690:	afab0198 */ 	sw	$t3,0x198($sp)
/*  f127694:	3c0f0008 */ 	lui	$t7,0x8
/*  f127698:	af2f0004 */ 	sw	$t7,0x4($t9)
/*  f12769c:	af2d0000 */ 	sw	$t5,0x0($t9)
/*  f1276a0:	8fa90198 */ 	lw	$t1,0x198($sp)
/*  f1276a4:	3c0eba00 */ 	lui	$t6,0xba00
/*  f1276a8:	35ce1001 */ 	ori	$t6,$t6,0x1001
/*  f1276ac:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f1276b0:	afaa0198 */ 	sw	$t2,0x198($sp)
/*  f1276b4:	3c180001 */ 	lui	$t8,0x1
/*  f1276b8:	ad380004 */ 	sw	$t8,0x4($t1)
/*  f1276bc:	ad2e0000 */ 	sw	$t6,0x0($t1)
/*  f1276c0:	8fbf008c */ 	lw	$ra,0x8c($sp)
/*  f1276c4:	8fbe0088 */ 	lw	$s8,0x88($sp)
/*  f1276c8:	8fb70084 */ 	lw	$s7,0x84($sp)
/*  f1276cc:	8fb60080 */ 	lw	$s6,0x80($sp)
/*  f1276d0:	8fb5007c */ 	lw	$s5,0x7c($sp)
/*  f1276d4:	8fb40078 */ 	lw	$s4,0x78($sp)
/*  f1276d8:	8fb30074 */ 	lw	$s3,0x74($sp)
/*  f1276dc:	8fb20070 */ 	lw	$s2,0x70($sp)
/*  f1276e0:	8fb1006c */ 	lw	$s1,0x6c($sp)
/*  f1276e4:	8fb00068 */ 	lw	$s0,0x68($sp)
/*  f1276e8:	d7be0060 */ 	ldc1	$f30,0x60($sp)
/*  f1276ec:	d7bc0058 */ 	ldc1	$f28,0x58($sp)
/*  f1276f0:	d7ba0050 */ 	ldc1	$f26,0x50($sp)
/*  f1276f4:	d7b80048 */ 	ldc1	$f24,0x48($sp)
/*  f1276f8:	d7b60040 */ 	ldc1	$f22,0x40($sp)
/*  f1276fc:	d7b40038 */ 	ldc1	$f20,0x38($sp)
/*  f127700:	8fa20198 */ 	lw	$v0,0x198($sp)
/*  f127704:	03e00008 */ 	jr	$ra
/*  f127708:	27bd0198 */ 	addiu	$sp,$sp,0x198
);
#else
GLOBAL_ASM(
glabel func0f126384
.late_rodata
glabel var7f1b510c
.word 0x3c23d70a
glabel var7f1b5110
.word 0x3bb60b61
glabel var7f1b5114
.word 0x3d088889
glabel var7f1b5118
.word 0x3c4ccccd
glabel var7f1b511c
.word 0x3dcccccd
.text
/*  f126384:	27bdfe70 */ 	addiu	$sp,$sp,-400
/*  f126388:	3c0f8008 */ 	lui	$t7,%hi(var8007dba0)
/*  f12638c:	afbf0084 */ 	sw	$ra,0x84($sp)
/*  f126390:	afb70080 */ 	sw	$s7,0x80($sp)
/*  f126394:	afb6007c */ 	sw	$s6,0x7c($sp)
/*  f126398:	afb50078 */ 	sw	$s5,0x78($sp)
/*  f12639c:	afb40074 */ 	sw	$s4,0x74($sp)
/*  f1263a0:	afb30070 */ 	sw	$s3,0x70($sp)
/*  f1263a4:	afb2006c */ 	sw	$s2,0x6c($sp)
/*  f1263a8:	afb10068 */ 	sw	$s1,0x68($sp)
/*  f1263ac:	afb00064 */ 	sw	$s0,0x64($sp)
/*  f1263b0:	f7be0058 */ 	sdc1	$f30,0x58($sp)
/*  f1263b4:	f7bc0050 */ 	sdc1	$f28,0x50($sp)
/*  f1263b8:	f7ba0048 */ 	sdc1	$f26,0x48($sp)
/*  f1263bc:	f7b80040 */ 	sdc1	$f24,0x40($sp)
/*  f1263c0:	f7b60038 */ 	sdc1	$f22,0x38($sp)
/*  f1263c4:	f7b40030 */ 	sdc1	$f20,0x30($sp)
/*  f1263c8:	afa40190 */ 	sw	$a0,0x190($sp)
/*  f1263cc:	25efdba0 */ 	addiu	$t7,$t7,%lo(var8007dba0)
/*  f1263d0:	8de10000 */ 	lw	$at,0x0($t7)
/*  f1263d4:	8de80004 */ 	lw	$t0,0x4($t7)
/*  f1263d8:	27ae015c */ 	addiu	$t6,$sp,0x15c
/*  f1263dc:	adc10000 */ 	sw	$at,0x0($t6)
/*  f1263e0:	adc80004 */ 	sw	$t0,0x4($t6)
/*  f1263e4:	8de8000c */ 	lw	$t0,0xc($t7)
/*  f1263e8:	8de10008 */ 	lw	$at,0x8($t7)
/*  f1263ec:	3c0a8008 */ 	lui	$t2,%hi(var8007dbb8)
/*  f1263f0:	adc8000c */ 	sw	$t0,0xc($t6)
/*  f1263f4:	adc10008 */ 	sw	$at,0x8($t6)
/*  f1263f8:	8de10010 */ 	lw	$at,0x10($t7)
/*  f1263fc:	8de80014 */ 	lw	$t0,0x14($t7)
/*  f126400:	254adbb8 */ 	addiu	$t2,$t2,%lo(var8007dbb8)
/*  f126404:	adc10010 */ 	sw	$at,0x10($t6)
/*  f126408:	adc80014 */ 	sw	$t0,0x14($t6)
/*  f12640c:	8d4d0004 */ 	lw	$t5,0x4($t2)
/*  f126410:	8d410000 */ 	lw	$at,0x0($t2)
/*  f126414:	27a90144 */ 	addiu	$t1,$sp,0x144
/*  f126418:	ad2d0004 */ 	sw	$t5,0x4($t1)
/*  f12641c:	ad210000 */ 	sw	$at,0x0($t1)
/*  f126420:	8d410008 */ 	lw	$at,0x8($t2)
/*  f126424:	8d4d000c */ 	lw	$t5,0xc($t2)
/*  f126428:	3c188008 */ 	lui	$t8,%hi(var8007dbd0)
/*  f12642c:	ad210008 */ 	sw	$at,0x8($t1)
/*  f126430:	ad2d000c */ 	sw	$t5,0xc($t1)
/*  f126434:	8d4d0014 */ 	lw	$t5,0x14($t2)
/*  f126438:	8d410010 */ 	lw	$at,0x10($t2)
/*  f12643c:	2718dbd0 */ 	addiu	$t8,$t8,%lo(var8007dbd0)
/*  f126440:	ad2d0014 */ 	sw	$t5,0x14($t1)
/*  f126444:	ad210010 */ 	sw	$at,0x10($t1)
/*  f126448:	8f080004 */ 	lw	$t0,0x4($t8)
/*  f12644c:	8f010000 */ 	lw	$at,0x0($t8)
/*  f126450:	27b9012c */ 	addiu	$t9,$sp,0x12c
/*  f126454:	af280004 */ 	sw	$t0,0x4($t9)
/*  f126458:	af210000 */ 	sw	$at,0x0($t9)
/*  f12645c:	8f010008 */ 	lw	$at,0x8($t8)
/*  f126460:	8f08000c */ 	lw	$t0,0xc($t8)
/*  f126464:	3c0c8007 */ 	lui	$t4,%hi(g_ViRes)
/*  f126468:	af210008 */ 	sw	$at,0x8($t9)
/*  f12646c:	af28000c */ 	sw	$t0,0xc($t9)
/*  f126470:	8f080014 */ 	lw	$t0,0x14($t8)
/*  f126474:	8f010010 */ 	lw	$at,0x10($t8)
/*  f126478:	4487b000 */ 	mtc1	$a3,$f22
/*  f12647c:	af280014 */ 	sw	$t0,0x14($t9)
/*  f126480:	af210010 */ 	sw	$at,0x10($t9)
/*  f126484:	8d8c06c8 */ 	lw	$t4,%lo(g_ViRes)($t4)
/*  f126488:	4485d000 */ 	mtc1	$a1,$f26
/*  f12648c:	4486e000 */ 	mtc1	$a2,$f28
/*  f126490:	24010001 */ 	addiu	$at,$zero,0x1
/*  f126494:	15810002 */ 	bne	$t4,$at,.L0f1264a0
/*  f126498:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f12649c:	24100002 */ 	addiu	$s0,$zero,0x2
.L0f1264a0:
/*  f1264a0:	0c002f22 */ 	jal	viGetViewWidth
/*  f1264a4:	00000000 */ 	nop
/*  f1264a8:	44822000 */ 	mtc1	$v0,$f4
/*  f1264ac:	3c017f1b */ 	lui	$at,%hi(var7f1b510c)
/*  f1264b0:	c434510c */ 	lwc1	$f20,%lo(var7f1b510c)($at)
/*  f1264b4:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f1264b8:	3c013f00 */ 	lui	$at,0x3f00
/*  f1264bc:	4481f000 */ 	mtc1	$at,$f30
/*  f1264c0:	00000000 */ 	nop
/*  f1264c4:	461e3202 */ 	mul.s	$f8,$f6,$f30
/*  f1264c8:	4608d281 */ 	sub.s	$f10,$f26,$f8
/*  f1264cc:	46145102 */ 	mul.s	$f4,$f10,$f20
/*  f1264d0:	0c002f26 */ 	jal	viGetViewHeight
/*  f1264d4:	e7a40128 */ 	swc1	$f4,0x128($sp)
/*  f1264d8:	44823000 */ 	mtc1	$v0,$f6
/*  f1264dc:	3c16800b */ 	lui	$s6,%hi(var800ab5a0)
/*  f1264e0:	26d6b5a0 */ 	addiu	$s6,$s6,%lo(var800ab5a0)
/*  f1264e4:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f1264e8:	8ec50000 */ 	lw	$a1,0x0($s6)
/*  f1264ec:	27b50190 */ 	addiu	$s5,$sp,0x190
/*  f1264f0:	240b0002 */ 	addiu	$t3,$zero,0x2
/*  f1264f4:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f1264f8:	afa90014 */ 	sw	$t1,0x14($sp)
/*  f1264fc:	461e4282 */ 	mul.s	$f10,$f8,$f30
/*  f126500:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f126504:	02a02025 */ 	or	$a0,$s5,$zero
/*  f126508:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f12650c:	00003825 */ 	or	$a3,$zero,$zero
/*  f126510:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f126514:	24a50048 */ 	addiu	$a1,$a1,0x48
/*  f126518:	460ae101 */ 	sub.s	$f4,$f28,$f10
/*  f12651c:	46142182 */ 	mul.s	$f6,$f4,$f20
/*  f126520:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f126524:	e7a60124 */ 	swc1	$f6,0x124($sp)
/*  f126528:	8faa0190 */ 	lw	$t2,0x190($sp)
/*  f12652c:	3c11ba00 */ 	lui	$s1,0xba00
/*  f126530:	36311402 */ 	ori	$s1,$s1,0x1402
/*  f126534:	254d0008 */ 	addiu	$t5,$t2,0x8
/*  f126538:	afad0190 */ 	sw	$t5,0x190($sp)
/*  f12653c:	ad400004 */ 	sw	$zero,0x4($t2)
/*  f126540:	ad510000 */ 	sw	$s1,0x0($t2)
/*  f126544:	8faf0190 */ 	lw	$t7,0x190($sp)
/*  f126548:	3c19ba00 */ 	lui	$t9,0xba00
/*  f12654c:	37390602 */ 	ori	$t9,$t9,0x602
/*  f126550:	25ee0008 */ 	addiu	$t6,$t7,0x8
/*  f126554:	afae0190 */ 	sw	$t6,0x190($sp)
/*  f126558:	24180040 */ 	addiu	$t8,$zero,0x40
/*  f12655c:	adf80004 */ 	sw	$t8,0x4($t7)
/*  f126560:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f126564:	8fa80190 */ 	lw	$t0,0x190($sp)
/*  f126568:	3c0bba00 */ 	lui	$t3,0xba00
/*  f12656c:	356b0402 */ 	ori	$t3,$t3,0x402
/*  f126570:	250c0008 */ 	addiu	$t4,$t0,0x8
/*  f126574:	afac0190 */ 	sw	$t4,0x190($sp)
/*  f126578:	ad000004 */ 	sw	$zero,0x4($t0)
/*  f12657c:	ad0b0000 */ 	sw	$t3,0x0($t0)
/*  f126580:	8fa90190 */ 	lw	$t1,0x190($sp)
/*  f126584:	3c12b900 */ 	lui	$s2,0xb900
/*  f126588:	3c130050 */ 	lui	$s3,0x50
/*  f12658c:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f126590:	afaa0190 */ 	sw	$t2,0x190($sp)
/*  f126594:	367341c8 */ 	ori	$s3,$s3,0x41c8
/*  f126598:	3652031d */ 	ori	$s2,$s2,0x31d
/*  f12659c:	ad320000 */ 	sw	$s2,0x0($t1)
/*  f1265a0:	ad330004 */ 	sw	$s3,0x4($t1)
/*  f1265a4:	8fad0190 */ 	lw	$t5,0x190($sp)
/*  f1265a8:	3c0eba00 */ 	lui	$t6,0xba00
/*  f1265ac:	35ce1301 */ 	ori	$t6,$t6,0x1301
/*  f1265b0:	25af0008 */ 	addiu	$t7,$t5,0x8
/*  f1265b4:	afaf0190 */ 	sw	$t7,0x190($sp)
/*  f1265b8:	ada00004 */ 	sw	$zero,0x4($t5)
/*  f1265bc:	adae0000 */ 	sw	$t6,0x0($t5)
/*  f1265c0:	8fb90190 */ 	lw	$t9,0x190($sp)
/*  f1265c4:	3c14b900 */ 	lui	$s4,0xb900
/*  f1265c8:	36940002 */ 	ori	$s4,$s4,0x2
/*  f1265cc:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f1265d0:	afb80190 */ 	sw	$t8,0x190($sp)
/*  f1265d4:	af200004 */ 	sw	$zero,0x4($t9)
/*  f1265d8:	af340000 */ 	sw	$s4,0x0($t9)
/*  f1265dc:	8fa80190 */ 	lw	$t0,0x190($sp)
/*  f1265e0:	3c0bba00 */ 	lui	$t3,0xba00
/*  f1265e4:	356b1001 */ 	ori	$t3,$t3,0x1001
/*  f1265e8:	250c0008 */ 	addiu	$t4,$t0,0x8
/*  f1265ec:	afac0190 */ 	sw	$t4,0x190($sp)
/*  f1265f0:	ad000004 */ 	sw	$zero,0x4($t0)
/*  f1265f4:	ad0b0000 */ 	sw	$t3,0x0($t0)
/*  f1265f8:	8fa90190 */ 	lw	$t1,0x190($sp)
/*  f1265fc:	3c0dba00 */ 	lui	$t5,0xba00
/*  f126600:	35ad0903 */ 	ori	$t5,$t5,0x903
/*  f126604:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f126608:	afaa0190 */ 	sw	$t2,0x190($sp)
/*  f12660c:	240f0c00 */ 	addiu	$t7,$zero,0xc00
/*  f126610:	ad2f0004 */ 	sw	$t7,0x4($t1)
/*  f126614:	ad2d0000 */ 	sw	$t5,0x0($t1)
/*  f126618:	8fae0190 */ 	lw	$t6,0x190($sp)
/*  f12661c:	3c18ba00 */ 	lui	$t8,0xba00
/*  f126620:	37180e02 */ 	ori	$t8,$t8,0xe02
/*  f126624:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f126628:	afb90190 */ 	sw	$t9,0x190($sp)
/*  f12662c:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f126630:	add80000 */ 	sw	$t8,0x0($t6)
/*  f126634:	8fa80190 */ 	lw	$t0,0x190($sp)
/*  f126638:	3c0bba00 */ 	lui	$t3,0xba00
/*  f12663c:	356b0c02 */ 	ori	$t3,$t3,0xc02
/*  f126640:	250c0008 */ 	addiu	$t4,$t0,0x8
/*  f126644:	afac0190 */ 	sw	$t4,0x190($sp)
/*  f126648:	24092000 */ 	addiu	$t1,$zero,0x2000
/*  f12664c:	ad090004 */ 	sw	$t1,0x4($t0)
/*  f126650:	ad0b0000 */ 	sw	$t3,0x0($t0)
/*  f126654:	8faa0190 */ 	lw	$t2,0x190($sp)
/*  f126658:	3c0eff36 */ 	lui	$t6,0xff36
/*  f12665c:	3c0ffcff */ 	lui	$t7,0xfcff
/*  f126660:	254d0008 */ 	addiu	$t5,$t2,0x8
/*  f126664:	afad0190 */ 	sw	$t5,0x190($sp)
/*  f126668:	35ef9bff */ 	ori	$t7,$t7,0x9bff
/*  f12666c:	35ceff7f */ 	ori	$t6,$t6,0xff7f
/*  f126670:	ad4e0004 */ 	sw	$t6,0x4($t2)
/*  f126674:	0c002f9d */ 	jal	viGetFovY
/*  f126678:	ad4f0000 */ 	sw	$t7,0x0($t2)
/*  f12667c:	8fb90190 */ 	lw	$t9,0x190($sp)
/*  f126680:	3c17fb00 */ 	lui	$s7,0xfb00
/*  f126684:	3c013f00 */ 	lui	$at,0x3f00
/*  f126688:	27380008 */ 	addiu	$t8,$t9,0x8
/*  f12668c:	afb80190 */ 	sw	$t8,0x190($sp)
/*  f126690:	af370000 */ 	sw	$s7,0x0($t9)
/*  f126694:	c7a801a8 */ 	lwc1	$f8,0x1a8($sp)
/*  f126698:	4481a000 */ 	mtc1	$at,$f20
/*  f12669c:	3c01437f */ 	lui	$at,0x437f
/*  f1266a0:	46164282 */ 	mul.s	$f10,$f8,$f22
/*  f1266a4:	44812000 */ 	mtc1	$at,$f4
/*  f1266a8:	2401ff00 */ 	addiu	$at,$zero,-256
/*  f1266ac:	24180001 */ 	addiu	$t8,$zero,0x1
/*  f1266b0:	240e0001 */ 	addiu	$t6,$zero,0x1
/*  f1266b4:	24080001 */ 	addiu	$t0,$zero,0x1
/*  f1266b8:	02a02025 */ 	or	$a0,$s5,$zero
/*  f1266bc:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f1266c0:	27a5017c */ 	addiu	$a1,$sp,0x17c
/*  f1266c4:	27a60174 */ 	addiu	$a2,$sp,0x174
/*  f1266c8:	4616a102 */ 	mul.s	$f4,$f20,$f22
/*  f1266cc:	4600320d */ 	trunc.w.s	$f8,$f6
/*  f1266d0:	4604a180 */ 	add.s	$f6,$f20,$f4
/*  f1266d4:	440c4000 */ 	mfc1	$t4,$f8
/*  f1266d8:	00000000 */ 	nop
/*  f1266dc:	318b00ff */ 	andi	$t3,$t4,0xff
/*  f1266e0:	01614825 */ 	or	$t1,$t3,$at
/*  f1266e4:	af290004 */ 	sw	$t1,0x4($t9)
/*  f1266e8:	c7aa01a0 */ 	lwc1	$f10,0x1a0($sp)
/*  f1266ec:	3c014270 */ 	lui	$at,0x4270
/*  f1266f0:	44812000 */ 	mtc1	$at,$f4
/*  f1266f4:	46065202 */ 	mul.s	$f8,$f10,$f6
/*  f1266f8:	8ec20000 */ 	lw	$v0,0x0($s6)
/*  f1266fc:	e7ba017c */ 	swc1	$f26,0x17c($sp)
/*  f126700:	e7bc0180 */ 	swc1	$f28,0x180($sp)
/*  f126704:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f126708:	46002283 */ 	div.s	$f10,$f4,$f0
/*  f12670c:	46085182 */ 	mul.s	$f6,$f10,$f8
/*  f126710:	4600310d */ 	trunc.w.s	$f4,$f6
/*  f126714:	44903000 */ 	mtc1	$s0,$f6
/*  f126718:	440d2000 */ 	mfc1	$t5,$f4
/*  f12671c:	46803620 */ 	cvt.s.w	$f24,$f6
/*  f126720:	448d5000 */ 	mtc1	$t5,$f10
/*  f126724:	00000000 */ 	nop
/*  f126728:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f12672c:	46144082 */ 	mul.s	$f2,$f8,$f20
/*  f126730:	00000000 */ 	nop
/*  f126734:	46181102 */ 	mul.s	$f4,$f2,$f24
/*  f126738:	e7a20178 */ 	swc1	$f2,0x178($sp)
/*  f12673c:	e7a40174 */ 	swc1	$f4,0x174($sp)
/*  f126740:	904f004d */ 	lbu	$t7,0x4d($v0)
/*  f126744:	9047004c */ 	lbu	$a3,0x4c($v0)
/*  f126748:	afa80028 */ 	sw	$t0,0x28($sp)
/*  f12674c:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f126750:	afb80020 */ 	sw	$t8,0x20($sp)
/*  f126754:	afb9001c */ 	sw	$t9,0x1c($sp)
/*  f126758:	afae0018 */ 	sw	$t6,0x18($sp)
/*  f12675c:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f126760:	0fc2c854 */ 	jal	func0f0b2150
/*  f126764:	afaf0010 */ 	sw	$t7,0x10($sp)
/*  f126768:	8ec50000 */ 	lw	$a1,0x0($s6)
/*  f12676c:	240c0002 */ 	addiu	$t4,$zero,0x2
/*  f126770:	240b0001 */ 	addiu	$t3,$zero,0x1
/*  f126774:	afab0014 */ 	sw	$t3,0x14($sp)
/*  f126778:	afac0010 */ 	sw	$t4,0x10($sp)
/*  f12677c:	02a02025 */ 	or	$a0,$s5,$zero
/*  f126780:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f126784:	00003825 */ 	or	$a3,$zero,$zero
/*  f126788:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f12678c:	0fc2ce70 */ 	jal	func0f0b39c0
/*  f126790:	24a5000c */ 	addiu	$a1,$a1,0xc
/*  f126794:	8fa90190 */ 	lw	$t1,0x190($sp)
/*  f126798:	3c0eba00 */ 	lui	$t6,0xba00
/*  f12679c:	35ce0602 */ 	ori	$t6,$t6,0x602
/*  f1267a0:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f1267a4:	afaa0190 */ 	sw	$t2,0x190($sp)
/*  f1267a8:	ad200004 */ 	sw	$zero,0x4($t1)
/*  f1267ac:	ad310000 */ 	sw	$s1,0x0($t1)
/*  f1267b0:	8fad0190 */ 	lw	$t5,0x190($sp)
/*  f1267b4:	24190040 */ 	addiu	$t9,$zero,0x40
/*  f1267b8:	3c0cba00 */ 	lui	$t4,0xba00
/*  f1267bc:	25af0008 */ 	addiu	$t7,$t5,0x8
/*  f1267c0:	afaf0190 */ 	sw	$t7,0x190($sp)
/*  f1267c4:	adb90004 */ 	sw	$t9,0x4($t5)
/*  f1267c8:	adae0000 */ 	sw	$t6,0x0($t5)
/*  f1267cc:	8fb80190 */ 	lw	$t8,0x190($sp)
/*  f1267d0:	358c0402 */ 	ori	$t4,$t4,0x402
/*  f1267d4:	3c0fba00 */ 	lui	$t7,0xba00
/*  f1267d8:	27080008 */ 	addiu	$t0,$t8,0x8
/*  f1267dc:	afa80190 */ 	sw	$t0,0x190($sp)
/*  f1267e0:	af000004 */ 	sw	$zero,0x4($t8)
/*  f1267e4:	af0c0000 */ 	sw	$t4,0x0($t8)
/*  f1267e8:	8fab0190 */ 	lw	$t3,0x190($sp)
/*  f1267ec:	35ef1301 */ 	ori	$t7,$t7,0x1301
/*  f1267f0:	3c0cba00 */ 	lui	$t4,0xba00
/*  f1267f4:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f1267f8:	afa90190 */ 	sw	$t1,0x190($sp)
/*  f1267fc:	ad730004 */ 	sw	$s3,0x4($t3)
/*  f126800:	ad720000 */ 	sw	$s2,0x0($t3)
/*  f126804:	8faa0190 */ 	lw	$t2,0x190($sp)
/*  f126808:	358c1001 */ 	ori	$t4,$t4,0x1001
/*  f12680c:	3c017f1b */ 	lui	$at,%hi(var7f1b5110)
/*  f126810:	254d0008 */ 	addiu	$t5,$t2,0x8
/*  f126814:	afad0190 */ 	sw	$t5,0x190($sp)
/*  f126818:	ad400004 */ 	sw	$zero,0x4($t2)
/*  f12681c:	ad4f0000 */ 	sw	$t7,0x0($t2)
/*  f126820:	8fae0190 */ 	lw	$t6,0x190($sp)
/*  f126824:	3c0aba00 */ 	lui	$t2,0xba00
/*  f126828:	354a0903 */ 	ori	$t2,$t2,0x903
/*  f12682c:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f126830:	afb90190 */ 	sw	$t9,0x190($sp)
/*  f126834:	adc00004 */ 	sw	$zero,0x4($t6)
/*  f126838:	add40000 */ 	sw	$s4,0x0($t6)
/*  f12683c:	8fb80190 */ 	lw	$t8,0x190($sp)
/*  f126840:	240d0c00 */ 	addiu	$t5,$zero,0xc00
/*  f126844:	3c19ba00 */ 	lui	$t9,0xba00
/*  f126848:	27080008 */ 	addiu	$t0,$t8,0x8
/*  f12684c:	afa80190 */ 	sw	$t0,0x190($sp)
/*  f126850:	af000004 */ 	sw	$zero,0x4($t8)
/*  f126854:	af0c0000 */ 	sw	$t4,0x0($t8)
/*  f126858:	8fab0190 */ 	lw	$t3,0x190($sp)
/*  f12685c:	37390e02 */ 	ori	$t9,$t9,0xe02
/*  f126860:	3c0cba00 */ 	lui	$t4,0xba00
/*  f126864:	25690008 */ 	addiu	$t1,$t3,0x8
/*  f126868:	afa90190 */ 	sw	$t1,0x190($sp)
/*  f12686c:	ad6d0004 */ 	sw	$t5,0x4($t3)
/*  f126870:	ad6a0000 */ 	sw	$t2,0x0($t3)
/*  f126874:	8faf0190 */ 	lw	$t7,0x190($sp)
/*  f126878:	240b2000 */ 	addiu	$t3,$zero,0x2000
/*  f12687c:	358c0c02 */ 	ori	$t4,$t4,0xc02
/*  f126880:	25ee0008 */ 	addiu	$t6,$t7,0x8
/*  f126884:	afae0190 */ 	sw	$t6,0x190($sp)
/*  f126888:	ade00004 */ 	sw	$zero,0x4($t7)
/*  f12688c:	adf90000 */ 	sw	$t9,0x0($t7)
/*  f126890:	8fb80190 */ 	lw	$t8,0x190($sp)
/*  f126894:	3c0fff36 */ 	lui	$t7,0xff36
/*  f126898:	3c0dfcff */ 	lui	$t5,0xfcff
/*  f12689c:	27080008 */ 	addiu	$t0,$t8,0x8
/*  f1268a0:	afa80190 */ 	sw	$t0,0x190($sp)
/*  f1268a4:	af0b0004 */ 	sw	$t3,0x4($t8)
/*  f1268a8:	af0c0000 */ 	sw	$t4,0x0($t8)
/*  f1268ac:	8fa90190 */ 	lw	$t1,0x190($sp)
/*  f1268b0:	35ad9bff */ 	ori	$t5,$t5,0x9bff
/*  f1268b4:	35efff7f */ 	ori	$t7,$t7,0xff7f
/*  f1268b8:	252a0008 */ 	addiu	$t2,$t1,0x8
/*  f1268bc:	afaa0190 */ 	sw	$t2,0x190($sp)
/*  f1268c0:	ad2f0004 */ 	sw	$t7,0x4($t1)
/*  f1268c4:	ad2d0000 */ 	sw	$t5,0x0($t1)
/*  f1268c8:	c43e5110 */ 	lwc1	$f30,%lo(var7f1b5110)($at)
/*  f1268cc:	3c014334 */ 	lui	$at,0x4334
/*  f1268d0:	e7bc0198 */ 	swc1	$f28,0x198($sp)
/*  f1268d4:	4481e000 */ 	mtc1	$at,$f28
/*  f1268d8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1268dc:	e7ba0194 */ 	swc1	$f26,0x194($sp)
/*  f1268e0:	4481d000 */ 	mtc1	$at,$f26
/*  f1268e4:	3c017f1b */ 	lui	$at,%hi(var7f1b5114)
/*  f1268e8:	e7b8009c */ 	swc1	$f24,0x9c($sp)
/*  f1268ec:	4480b000 */ 	mtc1	$zero,$f22
/*  f1268f0:	c4385114 */ 	lwc1	$f24,%lo(var7f1b5114)($at)
/*  f1268f4:	8fb301a4 */ 	lw	$s3,0x1a4($sp)
/*  f1268f8:	27b40144 */ 	addiu	$s4,$sp,0x144
/*  f1268fc:	27b2015c */ 	addiu	$s2,$sp,0x15c
/*  f126900:	27b10144 */ 	addiu	$s1,$sp,0x144
/*  f126904:	27b0012c */ 	addiu	$s0,$sp,0x12c
.L0f126908:
/*  f126908:	2a61005a */ 	slti	$at,$s3,0x5a
/*  f12690c:	1020000c */ 	beqz	$at,.L0f126940
/*  f126910:	266effa6 */ 	addiu	$t6,$s3,-90
/*  f126914:	2a61001e */ 	slti	$at,$s3,0x1e
/*  f126918:	10200007 */ 	beqz	$at,.L0f126938
/*  f12691c:	00000000 */ 	nop
/*  f126920:	44935000 */ 	mtc1	$s3,$f10
/*  f126924:	00000000 */ 	nop
/*  f126928:	46805220 */ 	cvt.s.w	$f8,$f10
/*  f12692c:	46184082 */ 	mul.s	$f2,$f8,$f24
/*  f126930:	10000011 */ 	b	.L0f126978
/*  f126934:	8e390000 */ 	lw	$t9,0x0($s1)
.L0f126938:
/*  f126938:	1000000e */ 	b	.L0f126974
/*  f12693c:	4600d086 */ 	mov.s	$f2,$f26
.L0f126940:
/*  f126940:	448e3000 */ 	mtc1	$t6,$f6
/*  f126944:	00000000 */ 	nop
/*  f126948:	46803120 */ 	cvt.s.w	$f4,$f6
/*  f12694c:	4604e281 */ 	sub.s	$f10,$f28,$f4
/*  f126950:	461e5202 */ 	mul.s	$f8,$f10,$f30
/*  f126954:	00000000 */ 	nop
/*  f126958:	46144082 */ 	mul.s	$f2,$f8,$f20
/*  f12695c:	4616103c */ 	c.lt.s	$f2,$f22
/*  f126960:	00000000 */ 	nop
/*  f126964:	45000002 */ 	bc1f	.L0f126970
/*  f126968:	00000000 */ 	nop
/*  f12696c:	4600b086 */ 	mov.s	$f2,$f22
.L0f126970:
/*  f126970:	46141080 */ 	add.s	$f2,$f2,$f20
.L0f126974:
/*  f126974:	8e390000 */ 	lw	$t9,0x0($s1)
.L0f126978:
/*  f126978:	c7aa0128 */ 	lwc1	$f10,0x128($sp)
/*  f12697c:	8fa30190 */ 	lw	$v1,0x190($sp)
/*  f126980:	44993000 */ 	mtc1	$t9,$f6
/*  f126984:	c7a40194 */ 	lwc1	$f4,0x194($sp)
/*  f126988:	8e580000 */ 	lw	$t8,0x0($s2)
/*  f12698c:	46803020 */ 	cvt.s.w	$f0,$f6
/*  f126990:	246c0008 */ 	addiu	$t4,$v1,0x8
/*  f126994:	c7a60198 */ 	lwc1	$f6,0x198($sp)
/*  f126998:	afac0190 */ 	sw	$t4,0x190($sp)
/*  f12699c:	3c014f80 */ 	lui	$at,0x4f80
/*  f1269a0:	460a0202 */ 	mul.s	$f8,$f0,$f10
/*  f1269a4:	c7aa0124 */ 	lwc1	$f10,0x124($sp)
/*  f1269a8:	ac770000 */ 	sw	$s7,0x0($v1)
/*  f1269ac:	8e020000 */ 	lw	$v0,0x0($s0)
/*  f1269b0:	304b00ff */ 	andi	$t3,$v0,0xff
/*  f1269b4:	46082301 */ 	sub.s	$f12,$f4,$f8
/*  f1269b8:	460a0102 */ 	mul.s	$f4,$f0,$f10
/*  f1269bc:	44984000 */ 	mtc1	$t8,$f8
/*  f1269c0:	448b5000 */ 	mtc1	$t3,$f10
/*  f1269c4:	46804420 */ 	cvt.s.w	$f16,$f8
/*  f1269c8:	c7a801a8 */ 	lwc1	$f8,0x1a8($sp)
/*  f1269cc:	46043381 */ 	sub.s	$f14,$f6,$f4
/*  f1269d0:	468051a0 */ 	cvt.s.w	$f6,$f10
/*  f1269d4:	46024282 */ 	mul.s	$f10,$f8,$f2
/*  f1269d8:	05610004 */ 	bgez	$t3,.L0f1269ec
/*  f1269dc:	00000000 */ 	nop
/*  f1269e0:	44812000 */ 	mtc1	$at,$f4
/*  f1269e4:	00000000 */ 	nop
/*  f1269e8:	46043180 */ 	add.s	$f6,$f6,$f4
.L0f1269ec:
/*  f1269ec:	460a3102 */ 	mul.s	$f4,$f6,$f10
/*  f1269f0:	02a02025 */ 	or	$a0,$s5,$zero
/*  f1269f4:	0002ce02 */ 	srl	$t9,$v0,0x18
/*  f1269f8:	0019c600 */ 	sll	$t8,$t9,0x18
/*  f1269fc:	00025c02 */ 	srl	$t3,$v0,0x10
/*  f126a00:	316900ff */ 	andi	$t1,$t3,0xff
/*  f126a04:	0002ca02 */ 	srl	$t9,$v0,0x8
/*  f126a08:	4600220d */ 	trunc.w.s	$f8,$f4
/*  f126a0c:	46148482 */ 	mul.s	$f18,$f16,$f20
/*  f126a10:	27a5017c */ 	addiu	$a1,$sp,0x17c
/*  f126a14:	27a60174 */ 	addiu	$a2,$sp,0x174
/*  f126a18:	440a4000 */ 	mfc1	$t2,$f8
/*  f126a1c:	00000000 */ 	nop
/*  f126a20:	314d00ff */ 	andi	$t5,$t2,0xff
/*  f126a24:	01b84025 */ 	or	$t0,$t5,$t8
/*  f126a28:	332d00ff */ 	andi	$t5,$t9,0xff
/*  f126a2c:	00095400 */ 	sll	$t2,$t1,0x10
/*  f126a30:	010a7825 */ 	or	$t7,$t0,$t2
/*  f126a34:	000dc200 */ 	sll	$t8,$t5,0x8
/*  f126a38:	01f86025 */ 	or	$t4,$t7,$t8
/*  f126a3c:	ac6c0004 */ 	sw	$t4,0x4($v1)
/*  f126a40:	c7a6009c */ 	lwc1	$f6,0x9c($sp)
/*  f126a44:	8ec20000 */ 	lw	$v0,0x0($s6)
/*  f126a48:	e7ac017c */ 	swc1	$f12,0x17c($sp)
/*  f126a4c:	46069282 */ 	mul.s	$f10,$f18,$f6
/*  f126a50:	e7ae0180 */ 	swc1	$f14,0x180($sp)
/*  f126a54:	e7b20178 */ 	swc1	$f18,0x178($sp)
/*  f126a58:	24090001 */ 	addiu	$t1,$zero,0x1
/*  f126a5c:	e7aa0174 */ 	swc1	$f10,0x174($sp)
/*  f126a60:	904b0011 */ 	lbu	$t3,0x11($v0)
/*  f126a64:	90470010 */ 	lbu	$a3,0x10($v0)
/*  f126a68:	afa90028 */ 	sw	$t1,0x28($sp)
/*  f126a6c:	afa00024 */ 	sw	$zero,0x24($sp)
/*  f126a70:	afa00020 */ 	sw	$zero,0x20($sp)
/*  f126a74:	afa0001c */ 	sw	$zero,0x1c($sp)
/*  f126a78:	afa00018 */ 	sw	$zero,0x18($sp)
/*  f126a7c:	afa00014 */ 	sw	$zero,0x14($sp)
/*  f126a80:	0fc2c854 */ 	jal	func0f0b2150
/*  f126a84:	afab0010 */ 	sw	$t3,0x10($sp)
/*  f126a88:	26100004 */ 	addiu	$s0,$s0,0x4
/*  f126a8c:	26310004 */ 	addiu	$s1,$s1,0x4
/*  f126a90:	1614ff9d */ 	bne	$s0,$s4,.L0f126908
/*  f126a94:	26520004 */ 	addiu	$s2,$s2,0x4
/*  f126a98:	0c002f22 */ 	jal	viGetViewWidth
/*  f126a9c:	00000000 */ 	nop
/*  f126aa0:	44822000 */ 	mtc1	$v0,$f4
/*  f126aa4:	3c013f00 */ 	lui	$at,0x3f00
/*  f126aa8:	4481c000 */ 	mtc1	$at,$f24
/*  f126aac:	46802220 */ 	cvt.s.w	$f8,$f4
/*  f126ab0:	c7aa0194 */ 	lwc1	$f10,0x194($sp)
/*  f126ab4:	46184182 */ 	mul.s	$f6,$f8,$f24
/*  f126ab8:	0c002f26 */ 	jal	viGetViewHeight
/*  f126abc:	460a3501 */ 	sub.s	$f20,$f6,$f10
/*  f126ac0:	44822000 */ 	mtc1	$v0,$f4
/*  f126ac4:	c7aa0198 */ 	lwc1	$f10,0x198($sp)
/*  f126ac8:	46802220 */ 	cvt.s.w	$f8,$f4
/*  f126acc:	46184182 */ 	mul.s	$f6,$f8,$f24
/*  f126ad0:	460a3001 */ 	sub.s	$f0,$f6,$f10
/*  f126ad4:	4614a102 */ 	mul.s	$f4,$f20,$f20
/*  f126ad8:	00000000 */ 	nop
/*  f126adc:	46000202 */ 	mul.s	$f8,$f0,$f0
/*  f126ae0:	0c012974 */ 	jal	sqrtf
/*  f126ae4:	46082300 */ 	add.s	$f12,$f4,$f8
/*  f126ae8:	3c014220 */ 	lui	$at,0x4220
/*  f126aec:	44813000 */ 	mtc1	$at,$f6
/*  f126af0:	3c017f1b */ 	lui	$at,%hi(var7f1b5118)
/*  f126af4:	c4245118 */ 	lwc1	$f4,%lo(var7f1b5118)($at)
/*  f126af8:	46003281 */ 	sub.s	$f10,$f6,$f0
/*  f126afc:	3c08800a */ 	lui	$t0,%hi(g_Vars+0x34)
/*  f126b00:	c7a601a8 */ 	lwc1	$f6,0x1a8($sp)
/*  f126b04:	46045302 */ 	mul.s	$f12,$f10,$f4
/*  f126b08:	4616603c */ 	c.lt.s	$f12,$f22
/*  f126b0c:	00000000 */ 	nop
/*  f126b10:	45000002 */ 	bc1f	.L0f126b1c
/*  f126b14:	00000000 */ 	nop
/*  f126b18:	4600b306 */ 	mov.s	$f12,$f22
.L0f126b1c:
/*  f126b1c:	8d089ff4 */ 	lw	$t0,%lo(g_Vars+0x34)($t0)
/*  f126b20:	3c017f1b */ 	lui	$at,%hi(var7f1b511c)
/*  f126b24:	c428511c */ 	lwc1	$f8,%lo(var7f1b511c)($at)
/*  f126b28:	0113082a */ 	slt	$at,$t0,$s3
/*  f126b2c:	14200002 */ 	bnez	$at,.L0f126b38
/*  f126b30:	46086300 */ 	add.s	$f12,$f12,$f8
/*  f126b34:	4600b306 */ 	mov.s	$f12,$f22
.L0f126b38:
/*  f126b38:	460cb03c */ 	c.lt.s	$f22,$f12
/*  f126b3c:	00000000 */ 	nop
/*  f126b40:	4502000d */ 	bc1fl	.L0f126b78
/*  f126b44:	8fae0190 */ 	lw	$t6,0x190($sp)
/*  f126b48:	460c3282 */ 	mul.s	$f10,$f6,$f12
/*  f126b4c:	3c01437f */ 	lui	$at,0x437f
/*  f126b50:	44812000 */ 	mtc1	$at,$f4
/*  f126b54:	00000000 */ 	nop
/*  f126b58:	46045202 */ 	mul.s	$f8,$f10,$f4
/*  f126b5c:	4600418d */ 	trunc.w.s	$f6,$f8
/*  f126b60:	44043000 */ 	mfc1	$a0,$f6
/*  f126b64:	00000000 */ 	nop
/*  f126b68:	00802825 */ 	or	$a1,$a0,$zero
/*  f126b6c:	0fc49ccd */ 	jal	func0f127334
/*  f126b70:	00803025 */ 	or	$a2,$a0,$zero
/*  f126b74:	8fae0190 */ 	lw	$t6,0x190($sp)
.L0f126b78:
/*  f126b78:	3c0dba00 */ 	lui	$t5,0xba00
/*  f126b7c:	35ad0602 */ 	ori	$t5,$t5,0x602
/*  f126b80:	25d90008 */ 	addiu	$t9,$t6,0x8
/*  f126b84:	afb90190 */ 	sw	$t9,0x190($sp)
/*  f126b88:	240f0040 */ 	addiu	$t7,$zero,0x40
/*  f126b8c:	adcf0004 */ 	sw	$t7,0x4($t6)
/*  f126b90:	adcd0000 */ 	sw	$t5,0x0($t6)
/*  f126b94:	8fb80190 */ 	lw	$t8,0x190($sp)
/*  f126b98:	3c0bba00 */ 	lui	$t3,0xba00
/*  f126b9c:	356b0402 */ 	ori	$t3,$t3,0x402
/*  f126ba0:	270c0008 */ 	addiu	$t4,$t8,0x8
/*  f126ba4:	afac0190 */ 	sw	$t4,0x190($sp)
/*  f126ba8:	240900c0 */ 	addiu	$t1,$zero,0xc0
/*  f126bac:	af090004 */ 	sw	$t1,0x4($t8)
/*  f126bb0:	af0b0000 */ 	sw	$t3,0x0($t8)
/*  f126bb4:	8fa80190 */ 	lw	$t0,0x190($sp)
/*  f126bb8:	3c0eba00 */ 	lui	$t6,0xba00
/*  f126bbc:	35ce1301 */ 	ori	$t6,$t6,0x1301
/*  f126bc0:	250a0008 */ 	addiu	$t2,$t0,0x8
/*  f126bc4:	afaa0190 */ 	sw	$t2,0x190($sp)
/*  f126bc8:	3c190008 */ 	lui	$t9,0x8
/*  f126bcc:	ad190004 */ 	sw	$t9,0x4($t0)
/*  f126bd0:	ad0e0000 */ 	sw	$t6,0x0($t0)
/*  f126bd4:	8fad0190 */ 	lw	$t5,0x190($sp)
/*  f126bd8:	3c18ba00 */ 	lui	$t8,0xba00
/*  f126bdc:	37181001 */ 	ori	$t8,$t8,0x1001
/*  f126be0:	25af0008 */ 	addiu	$t7,$t5,0x8
/*  f126be4:	afaf0190 */ 	sw	$t7,0x190($sp)
/*  f126be8:	3c0c0001 */ 	lui	$t4,0x1
/*  f126bec:	adac0004 */ 	sw	$t4,0x4($t5)
/*  f126bf0:	adb80000 */ 	sw	$t8,0x0($t5)
/*  f126bf4:	8fbf0084 */ 	lw	$ra,0x84($sp)
/*  f126bf8:	8fb70080 */ 	lw	$s7,0x80($sp)
/*  f126bfc:	8fb6007c */ 	lw	$s6,0x7c($sp)
/*  f126c00:	8fb50078 */ 	lw	$s5,0x78($sp)
/*  f126c04:	8fb40074 */ 	lw	$s4,0x74($sp)
/*  f126c08:	8fb30070 */ 	lw	$s3,0x70($sp)
/*  f126c0c:	8fb2006c */ 	lw	$s2,0x6c($sp)
/*  f126c10:	8fb10068 */ 	lw	$s1,0x68($sp)
/*  f126c14:	8fb00064 */ 	lw	$s0,0x64($sp)
/*  f126c18:	d7be0058 */ 	ldc1	$f30,0x58($sp)
/*  f126c1c:	d7bc0050 */ 	ldc1	$f28,0x50($sp)
/*  f126c20:	d7ba0048 */ 	ldc1	$f26,0x48($sp)
/*  f126c24:	d7b80040 */ 	ldc1	$f24,0x40($sp)
/*  f126c28:	d7b60038 */ 	ldc1	$f22,0x38($sp)
/*  f126c2c:	d7b40030 */ 	ldc1	$f20,0x30($sp)
/*  f126c30:	8fa20190 */ 	lw	$v0,0x190($sp)
/*  f126c34:	03e00008 */ 	jr	$ra
/*  f126c38:	27bd0190 */ 	addiu	$sp,$sp,0x190
);
#endif

/**
 * Render a single lens flare artifact.
 */
Gfx *func0f126c3c(Gfx *gdl, f32 x, f32 y, f32 z, f32 arg4, f32 arg5)
{
	struct coord sp64;

	sp64.x = x;
	sp64.y = y;
	sp64.z = z;

	mtx4TransformVecInPlace(currentPlayerGetMatrix1740(), &sp64);
	mtx4TransformVecInPlace(currentPlayerGetUnk1754(), &sp64);

	if (sp64.z > 1.0f) {
		f32 xpos;
		f32 ypos;
		s16 viewlefti = viGetViewLeft();
		s16 viewtopi = viGetViewTop();
		s16 viewwidthi = viGetViewWidth();
		s16 viewheighti = viGetViewHeight();
		f32 viewleft = viewlefti;
		f32 viewwidth = viewwidthi;
		f32 viewtop = viewtopi;
		f32 viewheight = viewheighti;

		xpos = viewleft + (sp64.f[0] / sp64.f[2] + 1.0f) * 0.5f * viewwidth;
		ypos = viewtop + (-sp64.f[1] / sp64.f[2] + 1.0f) * 0.5f * viewheight;

		if (xpos >= viewleft && xpos < viewleft + viewwidth
				&& ypos >= viewtop && ypos < viewtop + viewheight) {
			gdl = func0f126384(gdl, xpos, ypos, arg5, arg4, PALDOWN(90), 1.0f);
		}
	}

	return gdl;
}

/**
 * Render lens flares during teleport.
 */
Gfx *func0f126de8(Gfx *gdl)
{
	f32 sp154 = var80061630 * M_BADTAU;
	s32 i;
	f32 f20 = 0.0f;
	f32 f20_2;
	f32 f22;
	f32 f22_3;
	struct pad pad;
	struct coord spe0;
	f32 spd0[4];
	Mtxf mtx;
	f32 f24;
	f32 f30;

	if (g_Vars.currentplayer->teleportstate == TELEPORTSTATE_PREENTER) {
		f20 = g_Vars.currentplayer->teleporttime / 24.0f * 0.33f;
	} else if (g_Vars.currentplayer->teleportstate == TELEPORTSTATE_ENTERING) {
		f20 = g_Vars.currentplayer->teleporttime / 48.0f * 0.66f + 0.33f;
	}

	f30 = f20 * 6.0f;
	f22 = f20 * 1.3f;

	if (f22 > 1.0f) {
		f22 = 1.0f;
	}

	if (f30 > 1.0f) {
		f30 = 1.0f;
	}

	f20 *= 1.7f;

	if (f20 > 1.0f) {
		f20 = 1.0f;
	}

	padUnpack(g_Vars.currentplayer->teleportpad, PADFIELD_POS | PADFIELD_LOOK | PADFIELD_UP, &pad);

	g_TeleportToPos.x = pad.pos.x;
	g_TeleportToPos.y = pad.pos.y;
	g_TeleportToPos.z = pad.pos.z;
	g_TeleportToLook.x = pad.look.x;
	g_TeleportToLook.y = pad.look.y;
	g_TeleportToLook.z = pad.look.z;
	g_TeleportToUp.x = pad.up.x;
	g_TeleportToUp.y = pad.up.y;
	g_TeleportToUp.z = pad.up.z;

	f22 = -cosf(f22 * M_PI) * 0.5f + .5f;
	f24 = 100 * f22;

	for (i = 0; i < 5; i++) {
		spe0.x = g_TeleportToLook.f[0] * f24;
		spe0.y = g_TeleportToLook.f[1] * f24;
		spe0.z = g_TeleportToLook.f[2] * f24;

		f22_3 = sp154 + i * 1.2564370632172f;
		f20_2 = sinf(f22_3);

		spd0[0] = cosf(f22_3);
		spd0[1] = g_TeleportToUp.f[0] * f20_2;
		spd0[2] = g_TeleportToUp.f[1] * f20_2;
		spd0[3] = g_TeleportToUp.f[2] * f20_2;

		func0f096ed4(spd0, &mtx);
		mtx4RotateVecInPlace(&mtx, &spe0);

		spe0.x += g_TeleportToPos.x;
		spe0.y += g_TeleportToPos.y;
		spe0.z += g_TeleportToPos.z;

		gdl = func0f126c3c(gdl, spe0.x, spe0.y, spe0.z, f20 * 200, f30);
	}

	return gdl;
}

/**
 * Render teleport lens flare and sun lens flares.
 */
Gfx *func0f12715c(Gfx *gdl)
{
	struct sky *sky = skyGetCurrent();
	struct sun *sun;
	s32 i;

	if (g_Vars.currentplayer->teleportstate == TELEPORTSTATE_PREENTER
			|| g_Vars.currentplayer->teleportstate == TELEPORTSTATE_ENTERING) {
		gdl = func0f126de8(gdl);
	}

	if (sky->numsuns <= 0 || !var800844f0 || g_Vars.mplayerisrunning) {
		return gdl;
	}

	sun = sky->suns;

	for (i = 0; i < sky->numsuns; i++) {
		if (sun->lens_flare && var800a33e8[i][2] > 1) {
			struct bootbufferthing *thing = bbufGetIndex1Buffer();
			f32 value = func0f125a1c(thing->unk00[i]);

			if (value > 0.0f) {
				gdl = func0f126384(gdl, var800a3410[i], var800a3420[i], value, sun->orb_size, var8007db94[i], var8007db88[i]);
			}
		}

		sun++;
	}

	return gdl;
}

void func0f127334(s32 arg0, s32 arg1, s32 arg2)
{
	g_Vars.currentplayer->unk1c28 = sqrtf(g_Vars.currentplayer->unk1c28 * g_Vars.currentplayer->unk1c28 + arg0 * arg0);
	g_Vars.currentplayer->unk1c2c = sqrtf(g_Vars.currentplayer->unk1c2c * g_Vars.currentplayer->unk1c2c + arg1 * arg1);
	g_Vars.currentplayer->unk1c30 = sqrtf(g_Vars.currentplayer->unk1c30 * g_Vars.currentplayer->unk1c30 + arg2 * arg2);

	if (g_Vars.currentplayer->unk1c28 > 0xcc) {
		g_Vars.currentplayer->unk1c28 = 0xcc;
	}

	if (g_Vars.currentplayer->unk1c2c > 0xcc) {
		g_Vars.currentplayer->unk1c2c = 0xcc;
	}

	if (g_Vars.currentplayer->unk1c30 > 0xcc) {
		g_Vars.currentplayer->unk1c30 = 0xcc;
	}
}

s32 func0f127490(s32 arg0, s32 arg1)
{
	if (arg1 >= arg0) {
		if (arg1 - arg0 > 8) {
			return arg0 + 8;
		}

		return arg1;
	}

	if (arg0 - arg1 > 8) {
		return arg0 - 8;
	}

	return arg1;
}

Gfx *func0f1274d8(Gfx *gdl)
{
	s32 value;
	u32 stack;

	g_Vars.currentplayer->unk1c28 = func0f127490(g_Vars.currentplayer->unk1c34, g_Vars.currentplayer->unk1c28);
	g_Vars.currentplayer->unk1c2c = func0f127490(g_Vars.currentplayer->unk1c38, g_Vars.currentplayer->unk1c2c);
	g_Vars.currentplayer->unk1c30 = func0f127490(g_Vars.currentplayer->unk1c3c, g_Vars.currentplayer->unk1c30);

	value = (g_Vars.currentplayer->unk1c28 > g_Vars.currentplayer->unk1c2c && g_Vars.currentplayer->unk1c28 > g_Vars.currentplayer->unk1c30)
		? g_Vars.currentplayer->unk1c28
		: g_Vars.currentplayer->unk1c2c > g_Vars.currentplayer->unk1c30
		? g_Vars.currentplayer->unk1c2c
		: g_Vars.currentplayer->unk1c30;

	if (!g_InCutscene && EYESPYINACTIVE() && value > 0) {
		f32 r = g_Vars.currentplayer->unk1c28 * (255.0f / value);
		f32 g = g_Vars.currentplayer->unk1c2c * (255.0f / value);
		f32 b = g_Vars.currentplayer->unk1c30 * (255.0f / value);

		f32 a = (g_Vars.currentplayer->unk1c28
			+ g_Vars.currentplayer->unk1c2c
			+ g_Vars.currentplayer->unk1c30) * (1.0f / 3.0f);

		gDPSetTexturePersp(gdl++, G_TP_NONE);
		gDPSetColorDither(gdl++, G_CD_DISABLE);
		gDPSetRenderMode(gdl++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
		gDPSetCombineMode(gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

		if (USINGDEVICE(DEVICE_NIGHTVISION)) {
			r *= 0.5f;
			g *= 0.75f;
			b *= 0.5f;
		} else if (USINGDEVICE(DEVICE_IRSCANNER)) {
			r *= 0.75f;
			g *= 0.5f;
			b *= 0.5f;
		}

		gDPSetPrimColor(gdl++, 0, 0, (s32)r, (s32)g, (s32)b, (s32)a);

		gDPFillRectangle(gdl++,
				viGetViewLeft(),
				viGetViewTop(),
				viGetViewLeft() + viGetViewWidth(),
				viGetViewTop() + viGetViewHeight());

		gDPPipeSync(gdl++);
	}

	gDPSetColorDither(gdl++, G_CD_BAYER);
	gDPSetTexturePersp(gdl++, G_TP_PERSP);

	g_Vars.currentplayer->unk1c34 = g_Vars.currentplayer->unk1c28;
	g_Vars.currentplayer->unk1c38 = g_Vars.currentplayer->unk1c2c;
	g_Vars.currentplayer->unk1c3c = g_Vars.currentplayer->unk1c30;
	g_Vars.currentplayer->unk1c28 = 0;
	g_Vars.currentplayer->unk1c2c = 0;
	g_Vars.currentplayer->unk1c30 = 0;

	return gdl;
}
