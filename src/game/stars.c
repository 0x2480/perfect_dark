#include <ultra64.h>
#include "constants.h"
#include "game/game_006900.h"
#include "game/tex.h"
#include "game/stars.h"
#include "game/game_1531a0.h"
#include "bss.h"
#include "lib/vi.h"
#include "lib/memp.h"
#include "lib/rng.h"
#include "lib/mtx.h"
#include "data.h"
#include "types.h"

s32 g_StarCount;
s8 *g_StarPositions = NULL;
f32 *g_StarData3;
s32 g_StarGridSize;
s32 *g_StarPosIndexes;

bool g_StarsBelowHorizon = false;

void stars0f135c70(void)
{
	u32 stack[4];
	struct coord coord;
	f32 mult;
	s32 i;
	s32 j;
	s32 k;
	f32 tmp = g_StarGridSize * 0.5f;

	for (i = 0; i < 6; i++) {
		for (j = 0; j <= g_StarGridSize; j++) {
			for (k = 0; k <= g_StarGridSize; k++) {
				s32 index = ((i * (g_StarGridSize + 1) * (g_StarGridSize + 1)) + k + (j * (g_StarGridSize + 1))) * 3;

				switch (i) {
				case 0:
				case 1:
					coord.x = (i == 0 ? -1.0f : 1.0f);
					coord.y = k / tmp - 1;
					coord.z = j / tmp - 1;
					break;
				case 2:
				case 3:
					coord.y = (i == 2 ? -1.0f : 1.0f);
					coord.x = j / tmp - 1;
					coord.z = k / tmp - 1;
					break;
				case 4:
				case 5:
					coord.z = (i == 4 ? -1.0f : 1.0f);
					coord.x = k / tmp - 1;
					coord.y = j / tmp - 1;
					break;
				}

				mult = 1.0f / sqrtf(coord.f[0] * coord.f[0] + coord.f[1] * coord.f[1] + coord.f[2] * coord.f[2]);

				g_StarData3[index + 0] = coord.x * mult;
				g_StarData3[index + 1] = coord.y * mult;
				g_StarData3[index + 2] = coord.z * mult;
			}
		}
	}
}

/**
 * Insert a star position *after* the given index.
 */
void starInsert(s32 index, struct coord *arg1)
{
	s32 i;

	// Shuffle g_StarPositions forward after the insertion point
	for (i = g_StarPosIndexes[g_StarGridSize * 6 * g_StarGridSize] - 1; i >= g_StarPosIndexes[index + 1]; i--) {
		g_StarPositions[i * 3 + 3] = g_StarPositions[i * 3 + 0];
		g_StarPositions[i * 3 + 4] = g_StarPositions[i * 3 + 1];
		g_StarPositions[i * 3 + 5] = g_StarPositions[i * 3 + 2];
	}

	// Write new data
	g_StarPositions[g_StarPosIndexes[index + 1] * 3 + 0] = arg1->x * 127;
	g_StarPositions[g_StarPosIndexes[index + 1] * 3 + 1] = arg1->y * 127;
	g_StarPositions[g_StarPosIndexes[index + 1] * 3 + 2] = arg1->z * 127;

	// Increment indexes after the insertion point
	for (i = index + 1; i <= g_StarGridSize * 6 * g_StarGridSize; i++) {
		g_StarPosIndexes[i]++;
	}
}

GLOBAL_ASM(
glabel starsReset
/*  f1360e8:	27bdff18 */ 	addiu	$sp,$sp,-232
/*  f1360ec:	3c05800a */ 	lui	$a1,%hi(g_Vars)
/*  f1360f0:	24a59fc0 */ 	addiu	$a1,$a1,%lo(g_Vars)
/*  f1360f4:	8cae006c */ 	lw	$t6,0x6c($a1)
/*  f1360f8:	afb00044 */ 	sw	$s0,0x44($sp)
/*  f1360fc:	3c108008 */ 	lui	$s0,%hi(g_StarPositions)
/*  f136100:	2610f120 */ 	addiu	$s0,$s0,%lo(g_StarPositions)
/*  f136104:	afbf004c */ 	sw	$ra,0x4c($sp)
/*  f136108:	afb10048 */ 	sw	$s1,0x48($sp)
/*  f13610c:	f7be0038 */ 	sdc1	$f30,0x38($sp)
/*  f136110:	f7bc0030 */ 	sdc1	$f28,0x30($sp)
/*  f136114:	f7ba0028 */ 	sdc1	$f26,0x28($sp)
/*  f136118:	f7b80020 */ 	sdc1	$f24,0x20($sp)
/*  f13611c:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*  f136120:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*  f136124:	11c00003 */ 	beqz	$t6,.L0f136134
/*  f136128:	ae000000 */ 	sw	$zero,0x0($s0)
/*  f13612c:	10000002 */ 	b	.L0f136138
/*  f136130:	24060001 */ 	addiu	$a2,$zero,0x1
.L0f136134:
/*  f136134:	00003025 */ 	or	$a2,$zero,$zero
.L0f136138:
/*  f136138:	8caf0068 */ 	lw	$t7,0x68($a1)
/*  f13613c:	00001825 */ 	or	$v1,$zero,$zero
/*  f136140:	00002025 */ 	or	$a0,$zero,$zero
/*  f136144:	11e00003 */ 	beqz	$t7,.L0f136154
/*  f136148:	00001025 */ 	or	$v0,$zero,$zero
/*  f13614c:	10000001 */ 	b	.L0f136154
/*  f136150:	24030001 */ 	addiu	$v1,$zero,0x1
.L0f136154:
/*  f136154:	8cb80064 */ 	lw	$t8,0x64($a1)
/*  f136158:	3c088008 */ 	lui	$t0,%hi(g_StarsBelowHorizon)
/*  f13615c:	2508f124 */ 	addiu	$t0,$t0,%lo(g_StarsBelowHorizon)
/*  f136160:	13000003 */ 	beqz	$t8,.L0f136170
/*  f136164:	240c0003 */ 	addiu	$t4,$zero,0x3
/*  f136168:	10000001 */ 	b	.L0f136170
/*  f13616c:	24040001 */ 	addiu	$a0,$zero,0x1
.L0f136170:
/*  f136170:	8cb90070 */ 	lw	$t9,0x70($a1)
/*  f136174:	13200003 */ 	beqz	$t9,.L0f136184
/*  f136178:	00000000 */ 	nop
/*  f13617c:	10000001 */ 	b	.L0f136184
/*  f136180:	24020001 */ 	addiu	$v0,$zero,0x1
.L0f136184:
/*  f136184:	00444821 */ 	addu	$t1,$v0,$a0
/*  f136188:	01235021 */ 	addu	$t2,$t1,$v1
/*  f13618c:	01465821 */ 	addu	$t3,$t2,$a2
/*  f136190:	29610002 */ 	slti	$at,$t3,0x2
/*  f136194:	102001ae */ 	beqz	$at,.L0f136850
/*  f136198:	3c03800a */ 	lui	$v1,%hi(g_StarGridSize)
/*  f13619c:	8ca204b4 */ 	lw	$v0,0x4b4($a1)
/*  f1361a0:	24634158 */ 	addiu	$v1,$v1,%lo(g_StarGridSize)
/*  f1361a4:	2401004e */ 	addiu	$at,$zero,0x4e
/*  f1361a8:	ad000000 */ 	sw	$zero,0x0($t0)
/*  f1361ac:	14410007 */ 	bne	$v0,$at,.L0f1361cc
/*  f1361b0:	ac6c0000 */ 	sw	$t4,0x0($v1)
/*  f1361b4:	240d0001 */ 	addiu	$t5,$zero,0x1
/*  f1361b8:	ad0d0000 */ 	sw	$t5,0x0($t0)
/*  f1361bc:	240e0640 */ 	addiu	$t6,$zero,0x640
/*  f1361c0:	3c01800a */ 	lui	$at,%hi(g_StarCount)
/*  f1361c4:	10000018 */ 	b	.L0f136228
/*  f1361c8:	ac2e4150 */ 	sw	$t6,%lo(g_StarCount)($at)
.L0f1361cc:
/*  f1361cc:	24010030 */ 	addiu	$at,$zero,0x30
/*  f1361d0:	10410003 */ 	beq	$v0,$at,.L0f1361e0
/*  f1361d4:	240f00c8 */ 	addiu	$t7,$zero,0xc8
/*  f1361d8:	24010022 */ 	addiu	$at,$zero,0x22
/*  f1361dc:	14410005 */ 	bne	$v0,$at,.L0f1361f4
.L0f1361e0:
/*  f1361e0:	3c01800a */ 	lui	$at,%hi(g_StarCount)
/*  f1361e4:	ac2f4150 */ 	sw	$t7,%lo(g_StarCount)($at)
/*  f1361e8:	24180002 */ 	addiu	$t8,$zero,0x2
/*  f1361ec:	1000000e */ 	b	.L0f136228
/*  f1361f0:	ac780000 */ 	sw	$t8,0x0($v1)
.L0f1361f4:
/*  f1361f4:	24010034 */ 	addiu	$at,$zero,0x34
/*  f1361f8:	14410007 */ 	bne	$v0,$at,.L0f136218
/*  f1361fc:	240a00c8 */ 	addiu	$t2,$zero,0xc8
/*  f136200:	24190001 */ 	addiu	$t9,$zero,0x1
/*  f136204:	ad190000 */ 	sw	$t9,0x0($t0)
/*  f136208:	240904b0 */ 	addiu	$t1,$zero,0x4b0
/*  f13620c:	3c01800a */ 	lui	$at,%hi(g_StarCount)
/*  f136210:	10000005 */ 	b	.L0f136228
/*  f136214:	ac294150 */ 	sw	$t1,%lo(g_StarCount)($at)
.L0f136218:
/*  f136218:	3c01800a */ 	lui	$at,%hi(g_StarCount)
/*  f13621c:	ac2a4150 */ 	sw	$t2,%lo(g_StarCount)($at)
/*  f136220:	240b0002 */ 	addiu	$t3,$zero,0x2
/*  f136224:	ac6b0000 */ 	sw	$t3,0x0($v1)
.L0f136228:
/*  f136228:	8c670000 */ 	lw	$a3,0x0($v1)
/*  f13622c:	24060006 */ 	addiu	$a2,$zero,0x6
/*  f136230:	3c0c800a */ 	lui	$t4,%hi(g_StarCount)
/*  f136234:	24e20001 */ 	addiu	$v0,$a3,0x1
/*  f136238:	000270c0 */ 	sll	$t6,$v0,0x3
/*  f13623c:	01c27021 */ 	addu	$t6,$t6,$v0
/*  f136240:	000e70c0 */ 	sll	$t6,$t6,0x3
/*  f136244:	01c20019 */ 	multu	$t6,$v0
/*  f136248:	8d8c4150 */ 	lw	$t4,%lo(g_StarCount)($t4)
/*  f13624c:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f136250:	000c6880 */ 	sll	$t5,$t4,0x2
/*  f136254:	01ac6823 */ 	subu	$t5,$t5,$t4
/*  f136258:	00007812 */ 	mflo	$t7
/*  f13625c:	01afc021 */ 	addu	$t8,$t5,$t7
/*  f136260:	00000000 */ 	nop
/*  f136264:	00e60019 */ 	multu	$a3,$a2
/*  f136268:	0000c812 */ 	mflo	$t9
/*  f13626c:	00000000 */ 	nop
/*  f136270:	00000000 */ 	nop
/*  f136274:	03270019 */ 	multu	$t9,$a3
/*  f136278:	00004812 */ 	mflo	$t1
/*  f13627c:	00095080 */ 	sll	$t2,$t1,0x2
/*  f136280:	030a2021 */ 	addu	$a0,$t8,$t2
/*  f136284:	24840043 */ 	addiu	$a0,$a0,0x43
/*  f136288:	348b003f */ 	ori	$t3,$a0,0x3f
/*  f13628c:	0c0048f2 */ 	jal	mempAlloc
/*  f136290:	3964003f */ 	xori	$a0,$t3,0x3f
/*  f136294:	24060006 */ 	addiu	$a2,$zero,0x6
/*  f136298:	1040016d */ 	beqz	$v0,.L0f136850
/*  f13629c:	ae020000 */ 	sw	$v0,0x0($s0)
/*  f1362a0:	3c08800a */ 	lui	$t0,%hi(g_StarGridSize)
/*  f1362a4:	25084158 */ 	addiu	$t0,$t0,%lo(g_StarGridSize)
/*  f1362a8:	8d070000 */ 	lw	$a3,0x0($t0)
/*  f1362ac:	3c0e800a */ 	lui	$t6,%hi(g_StarCount)
/*  f1362b0:	8dce4150 */ 	lw	$t6,%lo(g_StarCount)($t6)
/*  f1362b4:	00e60019 */ 	multu	$a3,$a2
/*  f1362b8:	3c04800a */ 	lui	$a0,%hi(g_StarPosIndexes)
/*  f1362bc:	000e6880 */ 	sll	$t5,$t6,0x2
/*  f1362c0:	01ae6823 */ 	subu	$t5,$t5,$t6
/*  f1362c4:	2484415c */ 	addiu	$a0,$a0,%lo(g_StarPosIndexes)
/*  f1362c8:	01a27821 */ 	addu	$t7,$t5,$v0
/*  f1362cc:	ac8f0000 */ 	sw	$t7,0x0($a0)
/*  f1362d0:	00001025 */ 	or	$v0,$zero,$zero
/*  f1362d4:	00008825 */ 	or	$s1,$zero,$zero
/*  f1362d8:	0000c812 */ 	mflo	$t9
/*  f1362dc:	00000000 */ 	nop
/*  f1362e0:	00000000 */ 	nop
/*  f1362e4:	03270019 */ 	multu	$t9,$a3
/*  f1362e8:	00001812 */ 	mflo	$v1
/*  f1362ec:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f1362f0:	58600013 */ 	blezl	$v1,.L0f136340
/*  f1362f4:	8c8c0000 */ 	lw	$t4,0x0($a0)
/*  f1362f8:	8c890000 */ 	lw	$t1,0x0($a0)
.L0f1362fc:
/*  f1362fc:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f136300:	0122c021 */ 	addu	$t8,$t1,$v0
/*  f136304:	af000000 */ 	sw	$zero,0x0($t8)
/*  f136308:	8d070000 */ 	lw	$a3,0x0($t0)
/*  f13630c:	24420004 */ 	addiu	$v0,$v0,0x4
/*  f136310:	00e60019 */ 	multu	$a3,$a2
/*  f136314:	00005012 */ 	mflo	$t2
/*  f136318:	00000000 */ 	nop
/*  f13631c:	00000000 */ 	nop
/*  f136320:	01470019 */ 	multu	$t2,$a3
/*  f136324:	00001812 */ 	mflo	$v1
/*  f136328:	24630001 */ 	addiu	$v1,$v1,0x1
/*  f13632c:	0223082a */ 	slt	$at,$s1,$v1
/*  f136330:	5420fff2 */ 	bnezl	$at,.L0f1362fc
/*  f136334:	8c890000 */ 	lw	$t1,0x0($a0)
/*  f136338:	00008825 */ 	or	$s1,$zero,$zero
/*  f13633c:	8c8c0000 */ 	lw	$t4,0x0($a0)
.L0f136340:
/*  f136340:	00035880 */ 	sll	$t3,$v1,0x2
/*  f136344:	3c01800a */ 	lui	$at,%hi(g_StarData3)
/*  f136348:	016c7021 */ 	addu	$t6,$t3,$t4
/*  f13634c:	0fc4d71c */ 	jal	stars0f135c70
/*  f136350:	ac2e4154 */ 	sw	$t6,%lo(g_StarData3)($at)
/*  f136354:	3c0d800a */ 	lui	$t5,%hi(g_StarCount)
/*  f136358:	8dad4150 */ 	lw	$t5,%lo(g_StarCount)($t5)
/*  f13635c:	3c013f80 */ 	lui	$at,0x3f80
/*  f136360:	c7b800bc */ 	lwc1	$f24,0xbc($sp)
/*  f136364:	19a0013a */ 	blez	$t5,.L0f136850
/*  f136368:	c7b600c0 */ 	lwc1	$f22,0xc0($sp)
/*  f13636c:	4481f000 */ 	mtc1	$at,$f30
/*  f136370:	3c012f80 */ 	lui	$at,0x2f80
/*  f136374:	4481e000 */ 	mtc1	$at,$f28
/*  f136378:	3c01bf80 */ 	lui	$at,0xbf80
/*  f13637c:	4481d000 */ 	mtc1	$at,$f26
/*  f136380:	4480a000 */ 	mtc1	$zero,$f20
/*  f136384:	8fb000b0 */ 	lw	$s0,0xb0($sp)
.L0f136388:
/*  f136388:	0c004b70 */ 	jal	random
/*  f13638c:	00000000 */ 	nop
/*  f136390:	44822000 */ 	mtc1	$v0,$f4
/*  f136394:	3c014f80 */ 	lui	$at,0x4f80
/*  f136398:	04410004 */ 	bgez	$v0,.L0f1363ac
/*  f13639c:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f1363a0:	44814000 */ 	mtc1	$at,$f8
/*  f1363a4:	00000000 */ 	nop
/*  f1363a8:	46083180 */ 	add.s	$f6,$f6,$f8
.L0f1363ac:
/*  f1363ac:	461c3002 */ 	mul.s	$f0,$f6,$f28
/*  f1363b0:	3c0f8008 */ 	lui	$t7,%hi(g_StarsBelowHorizon)
/*  f1363b4:	8deff124 */ 	lw	$t7,%lo(g_StarsBelowHorizon)($t7)
/*  f1363b8:	46000280 */ 	add.s	$f10,$f0,$f0
/*  f1363bc:	461e5381 */ 	sub.s	$f14,$f10,$f30
/*  f1363c0:	11e0000f */ 	beqz	$t7,.L0f136400
/*  f1363c4:	e7ae00d4 */ 	swc1	$f14,0xd4($sp)
/*  f1363c8:	0c004b70 */ 	jal	random
/*  f1363cc:	00000000 */ 	nop
/*  f1363d0:	44822000 */ 	mtc1	$v0,$f4
/*  f1363d4:	3c014f80 */ 	lui	$at,0x4f80
/*  f1363d8:	04410004 */ 	bgez	$v0,.L0f1363ec
/*  f1363dc:	46802220 */ 	cvt.s.w	$f8,$f4
/*  f1363e0:	44813000 */ 	mtc1	$at,$f6
/*  f1363e4:	00000000 */ 	nop
/*  f1363e8:	46064200 */ 	add.s	$f8,$f8,$f6
.L0f1363ec:
/*  f1363ec:	461c4002 */ 	mul.s	$f0,$f8,$f28
/*  f1363f0:	46000280 */ 	add.s	$f10,$f0,$f0
/*  f1363f4:	461e5401 */ 	sub.s	$f16,$f10,$f30
/*  f1363f8:	1000000c */ 	b	.L0f13642c
/*  f1363fc:	e7b000d8 */ 	swc1	$f16,0xd8($sp)
.L0f136400:
/*  f136400:	0c004b70 */ 	jal	random
/*  f136404:	00000000 */ 	nop
/*  f136408:	44822000 */ 	mtc1	$v0,$f4
/*  f13640c:	3c014f80 */ 	lui	$at,0x4f80
/*  f136410:	04410004 */ 	bgez	$v0,.L0f136424
/*  f136414:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f136418:	44814000 */ 	mtc1	$at,$f8
/*  f13641c:	00000000 */ 	nop
/*  f136420:	46083180 */ 	add.s	$f6,$f6,$f8
.L0f136424:
/*  f136424:	461c3402 */ 	mul.s	$f16,$f6,$f28
/*  f136428:	e7b000d8 */ 	swc1	$f16,0xd8($sp)
.L0f13642c:
/*  f13642c:	0c004b70 */ 	jal	random
/*  f136430:	00000000 */ 	nop
/*  f136434:	44825000 */ 	mtc1	$v0,$f10
/*  f136438:	3c014f80 */ 	lui	$at,0x4f80
/*  f13643c:	04410004 */ 	bgez	$v0,.L0f136450
/*  f136440:	46805120 */ 	cvt.s.w	$f4,$f10
/*  f136444:	44814000 */ 	mtc1	$at,$f8
/*  f136448:	00000000 */ 	nop
/*  f13644c:	46082100 */ 	add.s	$f4,$f4,$f8
.L0f136450:
/*  f136450:	461c2002 */ 	mul.s	$f0,$f4,$f28
/*  f136454:	27a400d4 */ 	addiu	$a0,$sp,0xd4
/*  f136458:	27a500d8 */ 	addiu	$a1,$sp,0xd8
/*  f13645c:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f136460:	46000180 */ 	add.s	$f6,$f0,$f0
/*  f136464:	461e3301 */ 	sub.s	$f12,$f6,$f30
/*  f136468:	0c0011e4 */ 	jal	guNormalize
/*  f13646c:	e7ac00dc */ 	swc1	$f12,0xdc($sp)
/*  f136470:	c7ae00d4 */ 	lwc1	$f14,0xd4($sp)
/*  f136474:	c7b000d8 */ 	lwc1	$f16,0xd8($sp)
/*  f136478:	c7ac00dc */ 	lwc1	$f12,0xdc($sp)
/*  f13647c:	4614703c */ 	c.lt.s	$f14,$f20
/*  f136480:	00000000 */ 	nop
/*  f136484:	45020004 */ 	bc1fl	.L0f136498
/*  f136488:	46007086 */ 	mov.s	$f2,$f14
/*  f13648c:	10000002 */ 	b	.L0f136498
/*  f136490:	46007087 */ 	neg.s	$f2,$f14
/*  f136494:	46007086 */ 	mov.s	$f2,$f14
.L0f136498:
/*  f136498:	4614803c */ 	c.lt.s	$f16,$f20
/*  f13649c:	00000000 */ 	nop
/*  f1364a0:	45020004 */ 	bc1fl	.L0f1364b4
/*  f1364a4:	46008006 */ 	mov.s	$f0,$f16
/*  f1364a8:	10000002 */ 	b	.L0f1364b4
/*  f1364ac:	46008007 */ 	neg.s	$f0,$f16
/*  f1364b0:	46008006 */ 	mov.s	$f0,$f16
.L0f1364b4:
/*  f1364b4:	4602003c */ 	c.lt.s	$f0,$f2
/*  f1364b8:	00000000 */ 	nop
/*  f1364bc:	45020027 */ 	bc1fl	.L0f13655c
/*  f1364c0:	4614803c */ 	c.lt.s	$f16,$f20
/*  f1364c4:	4614703c */ 	c.lt.s	$f14,$f20
/*  f1364c8:	c7ac00dc */ 	lwc1	$f12,0xdc($sp)
/*  f1364cc:	45020004 */ 	bc1fl	.L0f1364e0
/*  f1364d0:	46007086 */ 	mov.s	$f2,$f14
/*  f1364d4:	10000002 */ 	b	.L0f1364e0
/*  f1364d8:	46007087 */ 	neg.s	$f2,$f14
/*  f1364dc:	46007086 */ 	mov.s	$f2,$f14
.L0f1364e0:
/*  f1364e0:	4614603c */ 	c.lt.s	$f12,$f20
/*  f1364e4:	00000000 */ 	nop
/*  f1364e8:	45020004 */ 	bc1fl	.L0f1364fc
/*  f1364ec:	46006006 */ 	mov.s	$f0,$f12
/*  f1364f0:	10000002 */ 	b	.L0f1364fc
/*  f1364f4:	46006007 */ 	neg.s	$f0,$f12
/*  f1364f8:	46006006 */ 	mov.s	$f0,$f12
.L0f1364fc:
/*  f1364fc:	4602003c */ 	c.lt.s	$f0,$f2
/*  f136500:	00000000 */ 	nop
/*  f136504:	4502000b */ 	bc1fl	.L0f136534
/*  f136508:	4614603c */ 	c.lt.s	$f12,$f20
/*  f13650c:	4614703c */ 	c.lt.s	$f14,$f20
/*  f136510:	00000000 */ 	nop
/*  f136514:	45020004 */ 	bc1fl	.L0f136528
/*  f136518:	46007006 */ 	mov.s	$f0,$f14
/*  f13651c:	10000032 */ 	b	.L0f1365e8
/*  f136520:	46007007 */ 	neg.s	$f0,$f14
/*  f136524:	46007006 */ 	mov.s	$f0,$f14
.L0f136528:
/*  f136528:	10000030 */ 	b	.L0f1365ec
/*  f13652c:	46007483 */ 	div.s	$f18,$f14,$f0
/*  f136530:	4614603c */ 	c.lt.s	$f12,$f20
.L0f136534:
/*  f136534:	00000000 */ 	nop
/*  f136538:	45020004 */ 	bc1fl	.L0f13654c
/*  f13653c:	46006006 */ 	mov.s	$f0,$f12
/*  f136540:	10000002 */ 	b	.L0f13654c
/*  f136544:	46006007 */ 	neg.s	$f0,$f12
/*  f136548:	46006006 */ 	mov.s	$f0,$f12
.L0f13654c:
/*  f13654c:	46000086 */ 	mov.s	$f2,$f0
/*  f136550:	10000025 */ 	b	.L0f1365e8
/*  f136554:	46001006 */ 	mov.s	$f0,$f2
/*  f136558:	4614803c */ 	c.lt.s	$f16,$f20
.L0f13655c:
/*  f13655c:	00000000 */ 	nop
/*  f136560:	45020004 */ 	bc1fl	.L0f136574
/*  f136564:	46008086 */ 	mov.s	$f2,$f16
/*  f136568:	10000002 */ 	b	.L0f136574
/*  f13656c:	46008087 */ 	neg.s	$f2,$f16
/*  f136570:	46008086 */ 	mov.s	$f2,$f16
.L0f136574:
/*  f136574:	4614603c */ 	c.lt.s	$f12,$f20
/*  f136578:	00000000 */ 	nop
/*  f13657c:	45020004 */ 	bc1fl	.L0f136590
/*  f136580:	46006006 */ 	mov.s	$f0,$f12
/*  f136584:	10000002 */ 	b	.L0f136590
/*  f136588:	46006007 */ 	neg.s	$f0,$f12
/*  f13658c:	46006006 */ 	mov.s	$f0,$f12
.L0f136590:
/*  f136590:	4602003c */ 	c.lt.s	$f0,$f2
/*  f136594:	00000000 */ 	nop
/*  f136598:	4502000b */ 	bc1fl	.L0f1365c8
/*  f13659c:	4614603c */ 	c.lt.s	$f12,$f20
/*  f1365a0:	4614803c */ 	c.lt.s	$f16,$f20
/*  f1365a4:	00000000 */ 	nop
/*  f1365a8:	45020004 */ 	bc1fl	.L0f1365bc
/*  f1365ac:	46008006 */ 	mov.s	$f0,$f16
/*  f1365b0:	1000000c */ 	b	.L0f1365e4
/*  f1365b4:	46008087 */ 	neg.s	$f2,$f16
/*  f1365b8:	46008006 */ 	mov.s	$f0,$f16
.L0f1365bc:
/*  f1365bc:	10000009 */ 	b	.L0f1365e4
/*  f1365c0:	46000086 */ 	mov.s	$f2,$f0
/*  f1365c4:	4614603c */ 	c.lt.s	$f12,$f20
.L0f1365c8:
/*  f1365c8:	00000000 */ 	nop
/*  f1365cc:	45020004 */ 	bc1fl	.L0f1365e0
/*  f1365d0:	46006006 */ 	mov.s	$f0,$f12
/*  f1365d4:	10000002 */ 	b	.L0f1365e0
/*  f1365d8:	46006007 */ 	neg.s	$f0,$f12
/*  f1365dc:	46006006 */ 	mov.s	$f0,$f12
.L0f1365e0:
/*  f1365e0:	46000086 */ 	mov.s	$f2,$f0
.L0f1365e4:
/*  f1365e4:	46001006 */ 	mov.s	$f0,$f2
.L0f1365e8:
/*  f1365e8:	46007483 */ 	div.s	$f18,$f14,$f0
.L0f1365ec:
/*  f1365ec:	3c07800a */ 	lui	$a3,%hi(g_StarGridSize)
/*  f1365f0:	8ce74158 */ 	lw	$a3,%lo(g_StarGridSize)($a3)
/*  f1365f4:	3c013f80 */ 	lui	$at,0x3f80
/*  f1365f8:	44812000 */ 	mtc1	$at,$f4
/*  f1365fc:	00e70019 */ 	multu	$a3,$a3
/*  f136600:	e7ac00dc */ 	swc1	$f12,0xdc($sp)
/*  f136604:	e7ae00d4 */ 	swc1	$f14,0xd4($sp)
/*  f136608:	e7b000d8 */ 	swc1	$f16,0xd8($sp)
/*  f13660c:	3c013f80 */ 	lui	$at,0x3f80
/*  f136610:	00004012 */ 	mflo	$t0
/*  f136614:	46008283 */ 	div.s	$f10,$f16,$f0
/*  f136618:	46122032 */ 	c.eq.s	$f4,$f18
/*  f13661c:	46006203 */ 	div.s	$f8,$f12,$f0
/*  f136620:	e7aa00cc */ 	swc1	$f10,0xcc($sp)
/*  f136624:	45010006 */ 	bc1t	.L0f136640
/*  f136628:	e7a800d0 */ 	swc1	$f8,0xd0($sp)
/*  f13662c:	4612d032 */ 	c.eq.s	$f26,$f18
/*  f136630:	c7a000cc */ 	lwc1	$f0,0xcc($sp)
/*  f136634:	c7ae00d0 */ 	lwc1	$f14,0xd0($sp)
/*  f136638:	45020018 */ 	bc1fl	.L0f13669c
/*  f13663c:	3c013f80 */ 	lui	$at,0x3f80
.L0f136640:
/*  f136640:	4612d032 */ 	c.eq.s	$f26,$f18
/*  f136644:	44813000 */ 	mtc1	$at,$f6
/*  f136648:	c7a000cc */ 	lwc1	$f0,0xcc($sp)
/*  f13664c:	c7ae00d0 */ 	lwc1	$f14,0xd0($sp)
/*  f136650:	45000003 */ 	bc1f	.L0f136660
/*  f136654:	e7b200c8 */ 	swc1	$f18,0xc8($sp)
/*  f136658:	10000002 */ 	b	.L0f136664
/*  f13665c:	00008025 */ 	or	$s0,$zero,$zero
.L0f136660:
/*  f136660:	24100001 */ 	addiu	$s0,$zero,0x1
.L0f136664:
/*  f136664:	3c014000 */ 	lui	$at,0x4000
/*  f136668:	44814000 */ 	mtc1	$at,$f8
/*  f13666c:	46060280 */ 	add.s	$f10,$f0,$f6
/*  f136670:	3c013f80 */ 	lui	$at,0x3f80
/*  f136674:	44812000 */ 	mtc1	$at,$f4
/*  f136678:	3c014000 */ 	lui	$at,0x4000
/*  f13667c:	46085083 */ 	div.s	$f2,$f10,$f8
/*  f136680:	44815000 */ 	mtc1	$at,$f10
/*  f136684:	46000586 */ 	mov.s	$f22,$f0
/*  f136688:	46007606 */ 	mov.s	$f24,$f14
/*  f13668c:	46047180 */ 	add.s	$f6,$f14,$f4
/*  f136690:	1000004c */ 	b	.L0f1367c4
/*  f136694:	460a3303 */ 	div.s	$f12,$f6,$f10
/*  f136698:	3c013f80 */ 	lui	$at,0x3f80
.L0f13669c:
/*  f13669c:	44814000 */ 	mtc1	$at,$f8
/*  f1366a0:	3c013f80 */ 	lui	$at,0x3f80
/*  f1366a4:	46004032 */ 	c.eq.s	$f8,$f0
/*  f1366a8:	00000000 */ 	nop
/*  f1366ac:	45030006 */ 	bc1tl	.L0f1366c8
/*  f1366b0:	4600d032 */ 	c.eq.s	$f26,$f0
/*  f1366b4:	4600d032 */ 	c.eq.s	$f26,$f0
/*  f1366b8:	00000000 */ 	nop
/*  f1366bc:	45020016 */ 	bc1fl	.L0f136718
/*  f1366c0:	3c013f80 */ 	lui	$at,0x3f80
/*  f1366c4:	4600d032 */ 	c.eq.s	$f26,$f0
.L0f1366c8:
/*  f1366c8:	44812000 */ 	mtc1	$at,$f4
/*  f1366cc:	3c014000 */ 	lui	$at,0x4000
/*  f1366d0:	44815000 */ 	mtc1	$at,$f10
/*  f1366d4:	45000003 */ 	bc1f	.L0f1366e4
/*  f1366d8:	46047180 */ 	add.s	$f6,$f14,$f4
/*  f1366dc:	10000002 */ 	b	.L0f1366e8
/*  f1366e0:	24100002 */ 	addiu	$s0,$zero,0x2
.L0f1366e4:
/*  f1366e4:	24100003 */ 	addiu	$s0,$zero,0x3
.L0f1366e8:
/*  f1366e8:	3c013f80 */ 	lui	$at,0x3f80
/*  f1366ec:	44814000 */ 	mtc1	$at,$f8
/*  f1366f0:	3c014000 */ 	lui	$at,0x4000
/*  f1366f4:	460a3083 */ 	div.s	$f2,$f6,$f10
/*  f1366f8:	44813000 */ 	mtc1	$at,$f6
/*  f1366fc:	46007586 */ 	mov.s	$f22,$f14
/*  f136700:	46009606 */ 	mov.s	$f24,$f18
/*  f136704:	46089100 */ 	add.s	$f4,$f18,$f8
/*  f136708:	e7b200c8 */ 	swc1	$f18,0xc8($sp)
/*  f13670c:	1000002d */ 	b	.L0f1367c4
/*  f136710:	46062303 */ 	div.s	$f12,$f4,$f6
/*  f136714:	3c013f80 */ 	lui	$at,0x3f80
.L0f136718:
/*  f136718:	44815000 */ 	mtc1	$at,$f10
/*  f13671c:	3c013f80 */ 	lui	$at,0x3f80
/*  f136720:	460e5032 */ 	c.eq.s	$f10,$f14
/*  f136724:	00000000 */ 	nop
/*  f136728:	45030006 */ 	bc1tl	.L0f136744
/*  f13672c:	460ed032 */ 	c.eq.s	$f26,$f14
/*  f136730:	460ed032 */ 	c.eq.s	$f26,$f14
/*  f136734:	00000000 */ 	nop
/*  f136738:	45020016 */ 	bc1fl	.L0f136794
/*  f13673c:	3c013f80 */ 	lui	$at,0x3f80
/*  f136740:	460ed032 */ 	c.eq.s	$f26,$f14
.L0f136744:
/*  f136744:	44814000 */ 	mtc1	$at,$f8
/*  f136748:	3c014000 */ 	lui	$at,0x4000
/*  f13674c:	44813000 */ 	mtc1	$at,$f6
/*  f136750:	45000003 */ 	bc1f	.L0f136760
/*  f136754:	46089100 */ 	add.s	$f4,$f18,$f8
/*  f136758:	10000002 */ 	b	.L0f136764
/*  f13675c:	24100004 */ 	addiu	$s0,$zero,0x4
.L0f136760:
/*  f136760:	24100005 */ 	addiu	$s0,$zero,0x5
.L0f136764:
/*  f136764:	3c013f80 */ 	lui	$at,0x3f80
/*  f136768:	44815000 */ 	mtc1	$at,$f10
/*  f13676c:	3c014000 */ 	lui	$at,0x4000
/*  f136770:	46062083 */ 	div.s	$f2,$f4,$f6
/*  f136774:	44812000 */ 	mtc1	$at,$f4
/*  f136778:	46009586 */ 	mov.s	$f22,$f18
/*  f13677c:	46000606 */ 	mov.s	$f24,$f0
/*  f136780:	460a0200 */ 	add.s	$f8,$f0,$f10
/*  f136784:	e7b200c8 */ 	swc1	$f18,0xc8($sp)
/*  f136788:	1000000e */ 	b	.L0f1367c4
/*  f13678c:	46044303 */ 	div.s	$f12,$f8,$f4
/*  f136790:	3c013f80 */ 	lui	$at,0x3f80
.L0f136794:
/*  f136794:	44813000 */ 	mtc1	$at,$f6
/*  f136798:	3c014000 */ 	lui	$at,0x4000
/*  f13679c:	44814000 */ 	mtc1	$at,$f8
/*  f1367a0:	4606b280 */ 	add.s	$f10,$f22,$f6
/*  f1367a4:	3c013f80 */ 	lui	$at,0x3f80
/*  f1367a8:	44812000 */ 	mtc1	$at,$f4
/*  f1367ac:	3c014000 */ 	lui	$at,0x4000
/*  f1367b0:	46085083 */ 	div.s	$f2,$f10,$f8
/*  f1367b4:	44815000 */ 	mtc1	$at,$f10
/*  f1367b8:	e7b200c8 */ 	swc1	$f18,0xc8($sp)
/*  f1367bc:	4604c180 */ 	add.s	$f6,$f24,$f4
/*  f1367c0:	460a3303 */ 	div.s	$f12,$f6,$f10
.L0f1367c4:
/*  f1367c4:	44874000 */ 	mtc1	$a3,$f8
/*  f1367c8:	00000000 */ 	nop
/*  f1367cc:	46804020 */ 	cvt.s.w	$f0,$f8
/*  f1367d0:	46001102 */ 	mul.s	$f4,$f2,$f0
/*  f1367d4:	00000000 */ 	nop
/*  f1367d8:	46006282 */ 	mul.s	$f10,$f12,$f0
/*  f1367dc:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f1367e0:	4600520d */ 	trunc.w.s	$f8,$f10
/*  f1367e4:	44023000 */ 	mfc1	$v0,$f6
/*  f1367e8:	44034000 */ 	mfc1	$v1,$f8
/*  f1367ec:	14470002 */ 	bne	$v0,$a3,.L0f1367f8
/*  f1367f0:	00000000 */ 	nop
/*  f1367f4:	2442ffff */ 	addiu	$v0,$v0,-1
.L0f1367f8:
/*  f1367f8:	14670002 */ 	bne	$v1,$a3,.L0f136804
/*  f1367fc:	00000000 */ 	nop
/*  f136800:	2463ffff */ 	addiu	$v1,$v1,-1
.L0f136804:
/*  f136804:	00e30019 */ 	multu	$a3,$v1
/*  f136808:	27a500d4 */ 	addiu	$a1,$sp,0xd4
/*  f13680c:	0000c012 */ 	mflo	$t8
/*  f136810:	03023021 */ 	addu	$a2,$t8,$v0
/*  f136814:	00000000 */ 	nop
/*  f136818:	02080019 */ 	multu	$s0,$t0
/*  f13681c:	00005012 */ 	mflo	$t2
/*  f136820:	01462021 */ 	addu	$a0,$t2,$a2
/*  f136824:	0fc4d7c2 */ 	jal	starInsert
/*  f136828:	00000000 */ 	nop
/*  f13682c:	3c0b800a */ 	lui	$t3,%hi(g_StarCount)
/*  f136830:	8d6b4150 */ 	lw	$t3,%lo(g_StarCount)($t3)
/*  f136834:	26310001 */ 	addiu	$s1,$s1,0x1
/*  f136838:	022b082a */ 	slt	$at,$s1,$t3
/*  f13683c:	1420fed2 */ 	bnez	$at,.L0f136388
/*  f136840:	00000000 */ 	nop
/*  f136844:	e7b800bc */ 	swc1	$f24,0xbc($sp)
/*  f136848:	e7b600c0 */ 	swc1	$f22,0xc0($sp)
/*  f13684c:	afb000b0 */ 	sw	$s0,0xb0($sp)
.L0f136850:
/*  f136850:	8fbf004c */ 	lw	$ra,0x4c($sp)
/*  f136854:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*  f136858:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*  f13685c:	d7b80020 */ 	ldc1	$f24,0x20($sp)
/*  f136860:	d7ba0028 */ 	ldc1	$f26,0x28($sp)
/*  f136864:	d7bc0030 */ 	ldc1	$f28,0x30($sp)
/*  f136868:	d7be0038 */ 	ldc1	$f30,0x38($sp)
/*  f13686c:	8fb00044 */ 	lw	$s0,0x44($sp)
/*  f136870:	8fb10048 */ 	lw	$s1,0x48($sp)
/*  f136874:	03e00008 */ 	jr	$ra
/*  f136878:	27bd00e8 */ 	addiu	$sp,$sp,0xe8
);

#define ABS2(value) ((value) < 0 ? -(value) : (value))

//void starsReset(void)
//{
//	struct coord spd4;
//	struct coord spc8;
//	f32 spbc[2];
//	s32 spb0;
//	f32 f12;
//	f32 f0;
//	f32 f2;
//	s32 v0;
//	s32 v1;
//	s32 i;
//	s32 tmp;
//
//	g_StarPositions = NULL;
//
//	if (PLAYERCOUNT() < 2) {
//		g_StarsBelowHorizon = false;
//		g_StarGridSize = 3;
//
//		if (g_Vars.stagenum == STAGE_TEST_OLD) {
//			g_StarsBelowHorizon = true;
//			g_StarCount = 1600;
//		} else if (g_Vars.stagenum == STAGE_DEFECTION || g_Vars.stagenum == STAGE_EXTRACTION) {
//			g_StarCount = 200;
//			g_StarGridSize = 2;
//		} else if (g_Vars.stagenum == STAGE_ATTACKSHIP) {
//			g_StarsBelowHorizon = true;
//			g_StarCount = 1200;
//		} else {
//			g_StarCount = 200;
//			g_StarGridSize = 2;
//		}
//
//		tmp = g_StarGridSize + 1;
//		g_StarPositions = mempAlloc(ALIGN64(g_StarCount * 3 + tmp * 72 * tmp + g_StarGridSize * 6 * g_StarGridSize * 4 + 4), MEMPOOL_STAGE);
//
//		if (g_StarPositions != NULL) {
//			s32 tmp;
//			g_StarPosIndexes = (s32 *)(g_StarPositions + g_StarCount * 3);
//
//			for (i = 0; i < (g_StarGridSize * 6 * g_StarGridSize + 1); i++) {
//				g_StarPosIndexes[i] = 0;
//			}
//
//			g_StarData3 = (f32 *)((u32)g_StarPosIndexes + (g_StarGridSize * 6 * g_StarGridSize + 1) * sizeof(f32));
//
//			stars0f135c70();
//
//			for (i = 0; i < g_StarCount; i++) {
//				spd4.f[0] = 2.0f * (random() * (1.0f / U32_MAX)) - 1.0f;
//
//				if (g_StarsBelowHorizon) {
//					spd4.f[1] = 2.0f * (random() * (1.0f / U32_MAX)) - 1.0f;
//				} else {
//					spd4.f[1] = random() * (1.0f / U32_MAX);
//				}
//
//				spd4.f[2] = 2.0f * (random() * (1.0f / U32_MAX)) - 1.0f;
//
//				guNormalize(&spd4.f[0], &spd4.f[1], &spd4.f[2]);
//
//				if (ABS2(spd4.f[1]) < ABS2(spd4.f[0])) {
//					f0 = ABS2(spd4.f[2]) < ABS2(spd4.f[0]) ? ABS2(spd4.f[0]) : ABS2(spd4.f[2]);
//				} else {
//					f0 = ABS2(spd4.f[2]) < ABS2(spd4.f[1]) ? ABS2(spd4.f[1]) : ABS2(spd4.f[2]);
//				}
//
//				// 5e0
//				tmp = g_StarGridSize * g_StarGridSize;
//
//				spc8.f[0] = spd4.f[0] / f0;
//				spc8.f[1] = spd4.f[1] / f0;
//				spc8.f[2] = spd4.f[2] / f0;
//
//				if (spc8.f[0] == 1.0f || spc8.f[0] == -1.0f) {
//					spb0 = spc8.f[0] == -1.0f ? 0 : 1;
//					spbc[0] = spc8.f[2];
//					spbc[1] = spc8.f[1];
//					f12 = (spbc[0] + 1.0f) / 2.0f;
//					f2 = (spbc[1] + 1.0f) / 2.0f;
//				} else if (spc8.f[1] == 1.0f || spc8.f[1] == -1.0f) {
//					spb0 = spc8.f[1] == -1.0f ? 2 : 3;
//					spbc[0] = spc8.f[0];
//					spbc[1] = spc8.f[2];
//					f12 = (spbc[0] + 1.0f) / 2.0f;
//					f2 = (spbc[1] + 1.0f) / 2.0f;
//				} else if (spc8.f[2] == 1.0f || spc8.f[2] == -1.0f) {
//					spb0 = spc8.f[2] == -1.0f ? 4 : 5;
//					spbc[0] = spc8.f[1];
//					spbc[1] = spc8.f[0];
//					f12 = (spbc[0] + 1.0f) / 2.0f;
//					f2 = (spbc[1] + 1.0f) / 2.0f;
//				} else{
//					f12 = (spbc[0] + 1.0f) / 2.0f;
//					f2 = (spbc[1] + 1.0f) / 2.0f;
//				}
//
//				v0 = f2 * g_StarGridSize;
//				v1 = f12 * g_StarGridSize;
//
//				if (v0 == g_StarGridSize) {
//					v0--;
//				}
//
//				if (v1 == g_StarGridSize) {
//					v1--;
//				}
//
//				starInsert(spb0 * tmp + (g_StarGridSize * v1) + v0, spd4.f);
//			}
//		}
//	}
//}

GLOBAL_ASM(
glabel starsRender
.late_rodata
glabel var7f1b57b8
.word 0x3c8efa03
glabel var7f1b57bc
.word 0x43837333
.text
/*  f13687c:	27bdfe50 */ 	addiu	$sp,$sp,-432
/*  f136880:	afbf006c */ 	sw	$ra,0x6c($sp)
/*  f136884:	afb1004c */ 	sw	$s1,0x4c($sp)
/*  f136888:	afb00048 */ 	sw	$s0,0x48($sp)
/*  f13688c:	00808025 */ 	or	$s0,$a0,$zero
/*  f136890:	afbe0068 */ 	sw	$s8,0x68($sp)
/*  f136894:	afb70064 */ 	sw	$s7,0x64($sp)
/*  f136898:	afb60060 */ 	sw	$s6,0x60($sp)
/*  f13689c:	afb5005c */ 	sw	$s5,0x5c($sp)
/*  f1368a0:	afb40058 */ 	sw	$s4,0x58($sp)
/*  f1368a4:	afb30054 */ 	sw	$s3,0x54($sp)
/*  f1368a8:	afb20050 */ 	sw	$s2,0x50($sp)
/*  f1368ac:	f7be0040 */ 	sdc1	$f30,0x40($sp)
/*  f1368b0:	f7bc0038 */ 	sdc1	$f28,0x38($sp)
/*  f1368b4:	f7ba0030 */ 	sdc1	$f26,0x30($sp)
/*  f1368b8:	f7b80028 */ 	sdc1	$f24,0x28($sp)
/*  f1368bc:	f7b60020 */ 	sdc1	$f22,0x20($sp)
/*  f1368c0:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*  f1368c4:	0c002f40 */ 	jal	viGetViewLeft
/*  f1368c8:	00008825 */ 	or	$s1,$zero,$zero
/*  f1368cc:	44822000 */ 	mtc1	$v0,$f4
/*  f1368d0:	0c002f22 */ 	jal	viGetViewWidth
/*  f1368d4:	46802520 */ 	cvt.s.w	$f20,$f4
/*  f1368d8:	44823000 */ 	mtc1	$v0,$f6
/*  f1368dc:	00000000 */ 	nop
/*  f1368e0:	46803220 */ 	cvt.s.w	$f8,$f6
/*  f1368e4:	0c002f44 */ 	jal	viGetViewTop
/*  f1368e8:	46144600 */ 	add.s	$f24,$f8,$f20
/*  f1368ec:	44825000 */ 	mtc1	$v0,$f10
/*  f1368f0:	0c002f26 */ 	jal	viGetViewHeight
/*  f1368f4:	468055a0 */ 	cvt.s.w	$f22,$f10
/*  f1368f8:	3c13800a */ 	lui	$s3,%hi(g_Vars)
/*  f1368fc:	26739fc0 */ 	addiu	$s3,$s3,%lo(g_Vars)
/*  f136900:	44828000 */ 	mtc1	$v0,$f16
/*  f136904:	8e630284 */ 	lw	$v1,0x284($s3)
/*  f136908:	3c0e8008 */ 	lui	$t6,%hi(g_StarPositions)
/*  f13690c:	468084a0 */ 	cvt.s.w	$f18,$f16
/*  f136910:	8dcef120 */ 	lw	$t6,%lo(g_StarPositions)($t6)
/*  f136914:	c464170c */ 	lwc1	$f4,0x170c($v1)
/*  f136918:	c4661720 */ 	lwc1	$f6,0x1720($v1)
/*  f13691c:	c4681710 */ 	lwc1	$f8,0x1710($v1)
/*  f136920:	c46a1724 */ 	lwc1	$f10,0x1724($v1)
/*  f136924:	46169680 */ 	add.s	$f26,$f18,$f22
/*  f136928:	46062700 */ 	add.s	$f28,$f4,$f6
/*  f13692c:	15c00003 */ 	bnez	$t6,.L0f13693c
/*  f136930:	460a4780 */ 	add.s	$f30,$f8,$f10
/*  f136934:	1000020a */ 	b	.L0f137160
/*  f136938:	02001025 */ 	or	$v0,$s0,$zero
.L0f13693c:
/*  f13693c:	8e6204b4 */ 	lw	$v0,0x4b4($s3)
/*  f136940:	24010030 */ 	addiu	$at,$zero,0x30
/*  f136944:	10410003 */ 	beq	$v0,$at,.L0f136954
/*  f136948:	24010022 */ 	addiu	$at,$zero,0x22
/*  f13694c:	54410003 */ 	bnel	$v0,$at,.L0f13695c
/*  f136950:	3c014000 */ 	lui	$at,0x4000
.L0f136954:
/*  f136954:	24110001 */ 	addiu	$s1,$zero,0x1
/*  f136958:	3c014000 */ 	lui	$at,0x4000
.L0f13695c:
/*  f13695c:	44816000 */ 	mtc1	$at,$f12
/*  f136960:	0fc01ac2 */ 	jal	func0f006b08
/*  f136964:	00000000 */ 	nop
/*  f136968:	3c01437f */ 	lui	$at,0x437f
/*  f13696c:	44818000 */ 	mtc1	$at,$f16
/*  f136970:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136974:	3c057777 */ 	lui	$a1,0x7777
/*  f136978:	46100482 */ 	mul.s	$f18,$f0,$f16
/*  f13697c:	34a5777f */ 	ori	$a1,$a1,0x777f
/*  f136980:	2404ff7f */ 	addiu	$a0,$zero,-129
/*  f136984:	444ff800 */ 	cfc1	$t7,$31
/*  f136988:	44c6f800 */ 	ctc1	$a2,$31
/*  f13698c:	00000000 */ 	nop
/*  f136990:	46009124 */ 	cvt.w.s	$f4,$f18
/*  f136994:	4446f800 */ 	cfc1	$a2,$31
/*  f136998:	00000000 */ 	nop
/*  f13699c:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f1369a0:	10c00012 */ 	beqz	$a2,.L0f1369ec
/*  f1369a4:	3c014f00 */ 	lui	$at,0x4f00
/*  f1369a8:	44812000 */ 	mtc1	$at,$f4
/*  f1369ac:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f1369b0:	46049101 */ 	sub.s	$f4,$f18,$f4
/*  f1369b4:	44c6f800 */ 	ctc1	$a2,$31
/*  f1369b8:	00000000 */ 	nop
/*  f1369bc:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f1369c0:	4446f800 */ 	cfc1	$a2,$31
/*  f1369c4:	00000000 */ 	nop
/*  f1369c8:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f1369cc:	14c00005 */ 	bnez	$a2,.L0f1369e4
/*  f1369d0:	00000000 */ 	nop
/*  f1369d4:	44062000 */ 	mfc1	$a2,$f4
/*  f1369d8:	3c018000 */ 	lui	$at,0x8000
/*  f1369dc:	10000007 */ 	b	.L0f1369fc
/*  f1369e0:	00c13025 */ 	or	$a2,$a2,$at
.L0f1369e4:
/*  f1369e4:	10000005 */ 	b	.L0f1369fc
/*  f1369e8:	2406ffff */ 	addiu	$a2,$zero,-1
.L0f1369ec:
/*  f1369ec:	44062000 */ 	mfc1	$a2,$f4
/*  f1369f0:	00000000 */ 	nop
/*  f1369f4:	04c0fffb */ 	bltz	$a2,.L0f1369e4
/*  f1369f8:	00000000 */ 	nop
.L0f1369fc:
/*  f1369fc:	44cff800 */ 	ctc1	$t7,$31
/*  f136a00:	0fc01a40 */ 	jal	colourBlend
/*  f136a04:	00000000 */ 	nop
/*  f136a08:	3c014080 */ 	lui	$at,0x4080
/*  f136a0c:	44816000 */ 	mtc1	$at,$f12
/*  f136a10:	0fc01ac2 */ 	jal	func0f006b08
/*  f136a14:	afa2011c */ 	sw	$v0,0x11c($sp)
/*  f136a18:	3c01437f */ 	lui	$at,0x437f
/*  f136a1c:	44813000 */ 	mtc1	$at,$f6
/*  f136a20:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136a24:	3c052222 */ 	lui	$a1,0x2222
/*  f136a28:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f136a2c:	34a5ff7f */ 	ori	$a1,$a1,0xff7f
/*  f136a30:	3404aa7f */ 	dli	$a0,0xaa7f
/*  f136a34:	4458f800 */ 	cfc1	$t8,$31
/*  f136a38:	44c6f800 */ 	ctc1	$a2,$31
/*  f136a3c:	00000000 */ 	nop
/*  f136a40:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f136a44:	4446f800 */ 	cfc1	$a2,$31
/*  f136a48:	00000000 */ 	nop
/*  f136a4c:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f136a50:	10c00012 */ 	beqz	$a2,.L0f136a9c
/*  f136a54:	3c014f00 */ 	lui	$at,0x4f00
/*  f136a58:	44815000 */ 	mtc1	$at,$f10
/*  f136a5c:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136a60:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f136a64:	44c6f800 */ 	ctc1	$a2,$31
/*  f136a68:	00000000 */ 	nop
/*  f136a6c:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f136a70:	4446f800 */ 	cfc1	$a2,$31
/*  f136a74:	00000000 */ 	nop
/*  f136a78:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f136a7c:	14c00005 */ 	bnez	$a2,.L0f136a94
/*  f136a80:	00000000 */ 	nop
/*  f136a84:	44065000 */ 	mfc1	$a2,$f10
/*  f136a88:	3c018000 */ 	lui	$at,0x8000
/*  f136a8c:	10000007 */ 	b	.L0f136aac
/*  f136a90:	00c13025 */ 	or	$a2,$a2,$at
.L0f136a94:
/*  f136a94:	10000005 */ 	b	.L0f136aac
/*  f136a98:	2406ffff */ 	addiu	$a2,$zero,-1
.L0f136a9c:
/*  f136a9c:	44065000 */ 	mfc1	$a2,$f10
/*  f136aa0:	00000000 */ 	nop
/*  f136aa4:	04c0fffb */ 	bltz	$a2,.L0f136a94
/*  f136aa8:	00000000 */ 	nop
.L0f136aac:
/*  f136aac:	44d8f800 */ 	ctc1	$t8,$31
/*  f136ab0:	0fc01a40 */ 	jal	colourBlend
/*  f136ab4:	00000000 */ 	nop
/*  f136ab8:	3c014000 */ 	lui	$at,0x4000
/*  f136abc:	44816000 */ 	mtc1	$at,$f12
/*  f136ac0:	0fc01ad5 */ 	jal	func0f006b54
/*  f136ac4:	afa20120 */ 	sw	$v0,0x120($sp)
/*  f136ac8:	3c01437f */ 	lui	$at,0x437f
/*  f136acc:	44818000 */ 	mtc1	$at,$f16
/*  f136ad0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136ad4:	3c055555 */ 	lui	$a1,0x5555
/*  f136ad8:	46100482 */ 	mul.s	$f18,$f0,$f16
/*  f136adc:	34a5ff7f */ 	ori	$a1,$a1,0xff7f
/*  f136ae0:	3404ff7f */ 	dli	$a0,0xff7f
/*  f136ae4:	4459f800 */ 	cfc1	$t9,$31
/*  f136ae8:	44c6f800 */ 	ctc1	$a2,$31
/*  f136aec:	00000000 */ 	nop
/*  f136af0:	46009124 */ 	cvt.w.s	$f4,$f18
/*  f136af4:	4446f800 */ 	cfc1	$a2,$31
/*  f136af8:	00000000 */ 	nop
/*  f136afc:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f136b00:	10c00012 */ 	beqz	$a2,.L0f136b4c
/*  f136b04:	3c014f00 */ 	lui	$at,0x4f00
/*  f136b08:	44812000 */ 	mtc1	$at,$f4
/*  f136b0c:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136b10:	46049101 */ 	sub.s	$f4,$f18,$f4
/*  f136b14:	44c6f800 */ 	ctc1	$a2,$31
/*  f136b18:	00000000 */ 	nop
/*  f136b1c:	46002124 */ 	cvt.w.s	$f4,$f4
/*  f136b20:	4446f800 */ 	cfc1	$a2,$31
/*  f136b24:	00000000 */ 	nop
/*  f136b28:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f136b2c:	14c00005 */ 	bnez	$a2,.L0f136b44
/*  f136b30:	00000000 */ 	nop
/*  f136b34:	44062000 */ 	mfc1	$a2,$f4
/*  f136b38:	3c018000 */ 	lui	$at,0x8000
/*  f136b3c:	10000007 */ 	b	.L0f136b5c
/*  f136b40:	00c13025 */ 	or	$a2,$a2,$at
.L0f136b44:
/*  f136b44:	10000005 */ 	b	.L0f136b5c
/*  f136b48:	2406ffff */ 	addiu	$a2,$zero,-1
.L0f136b4c:
/*  f136b4c:	44062000 */ 	mfc1	$a2,$f4
/*  f136b50:	00000000 */ 	nop
/*  f136b54:	04c0fffb */ 	bltz	$a2,.L0f136b44
/*  f136b58:	00000000 */ 	nop
.L0f136b5c:
/*  f136b5c:	44d9f800 */ 	ctc1	$t9,$31
/*  f136b60:	0fc01a40 */ 	jal	colourBlend
/*  f136b64:	00000000 */ 	nop
/*  f136b68:	3c014080 */ 	lui	$at,0x4080
/*  f136b6c:	44816000 */ 	mtc1	$at,$f12
/*  f136b70:	0fc01ad5 */ 	jal	func0f006b54
/*  f136b74:	afa20124 */ 	sw	$v0,0x124($sp)
/*  f136b78:	3c01437f */ 	lui	$at,0x437f
/*  f136b7c:	44813000 */ 	mtc1	$at,$f6
/*  f136b80:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136b84:	3c04aaaa */ 	lui	$a0,0xaaaa
/*  f136b88:	46060202 */ 	mul.s	$f8,$f0,$f6
/*  f136b8c:	3c057777 */ 	lui	$a1,0x7777
/*  f136b90:	34a5ff7f */ 	ori	$a1,$a1,0xff7f
/*  f136b94:	3484ff7f */ 	ori	$a0,$a0,0xff7f
/*  f136b98:	444ef800 */ 	cfc1	$t6,$31
/*  f136b9c:	44c6f800 */ 	ctc1	$a2,$31
/*  f136ba0:	00000000 */ 	nop
/*  f136ba4:	460042a4 */ 	cvt.w.s	$f10,$f8
/*  f136ba8:	4446f800 */ 	cfc1	$a2,$31
/*  f136bac:	00000000 */ 	nop
/*  f136bb0:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f136bb4:	10c00012 */ 	beqz	$a2,.L0f136c00
/*  f136bb8:	3c014f00 */ 	lui	$at,0x4f00
/*  f136bbc:	44815000 */ 	mtc1	$at,$f10
/*  f136bc0:	24060001 */ 	addiu	$a2,$zero,0x1
/*  f136bc4:	460a4281 */ 	sub.s	$f10,$f8,$f10
/*  f136bc8:	44c6f800 */ 	ctc1	$a2,$31
/*  f136bcc:	00000000 */ 	nop
/*  f136bd0:	460052a4 */ 	cvt.w.s	$f10,$f10
/*  f136bd4:	4446f800 */ 	cfc1	$a2,$31
/*  f136bd8:	00000000 */ 	nop
/*  f136bdc:	30c60078 */ 	andi	$a2,$a2,0x78
/*  f136be0:	14c00005 */ 	bnez	$a2,.L0f136bf8
/*  f136be4:	00000000 */ 	nop
/*  f136be8:	44065000 */ 	mfc1	$a2,$f10
/*  f136bec:	3c018000 */ 	lui	$at,0x8000
/*  f136bf0:	10000007 */ 	b	.L0f136c10
/*  f136bf4:	00c13025 */ 	or	$a2,$a2,$at
.L0f136bf8:
/*  f136bf8:	10000005 */ 	b	.L0f136c10
/*  f136bfc:	2406ffff */ 	addiu	$a2,$zero,-1
.L0f136c00:
/*  f136c00:	44065000 */ 	mfc1	$a2,$f10
/*  f136c04:	00000000 */ 	nop
/*  f136c08:	04c0fffb */ 	bltz	$a2,.L0f136bf8
/*  f136c0c:	00000000 */ 	nop
.L0f136c10:
/*  f136c10:	44cef800 */ 	ctc1	$t6,$31
/*  f136c14:	0fc01a40 */ 	jal	colourBlend
/*  f136c18:	00000000 */ 	nop
/*  f136c1c:	1220000a */ 	beqz	$s1,.L0f136c48
/*  f136c20:	afa20128 */ 	sw	$v0,0x128($sp)
/*  f136c24:	27b1011c */ 	addiu	$s1,$sp,0x11c
/*  f136c28:	27b20128 */ 	addiu	$s2,$sp,0x128
/*  f136c2c:	8e240000 */ 	lw	$a0,0x0($s1)
.L0f136c30:
/*  f136c30:	2406005f */ 	addiu	$a2,$zero,0x5f
/*  f136c34:	0fc01a40 */ 	jal	colourBlend
/*  f136c38:	308500ff */ 	andi	$a1,$a0,0xff
/*  f136c3c:	26310004 */ 	addiu	$s1,$s1,0x4
/*  f136c40:	5632fffb */ 	bnel	$s1,$s2,.L0f136c30
/*  f136c44:	8e240000 */ 	lw	$a0,0x0($s1)
.L0f136c48:
/*  f136c48:	0c002f9d */ 	jal	viGetFovY
/*  f136c4c:	00000000 */ 	nop
/*  f136c50:	0c002f72 */ 	jal	viGetAspect
/*  f136c54:	e7a00090 */ 	swc1	$f0,0x90($sp)
/*  f136c58:	c7b00090 */ 	lwc1	$f16,0x90($sp)
/*  f136c5c:	3c013f00 */ 	lui	$at,0x3f00
/*  f136c60:	44812000 */ 	mtc1	$at,$f4
/*  f136c64:	46008483 */ 	div.s	$f18,$f16,$f0
/*  f136c68:	3c0142b4 */ 	lui	$at,0x42b4
/*  f136c6c:	44814000 */ 	mtc1	$at,$f8
/*  f136c70:	3c017f1b */ 	lui	$at,%hi(var7f1b57b8)
/*  f136c74:	c43057b8 */ 	lwc1	$f16,%lo(var7f1b57b8)($at)
/*  f136c78:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f136c7c:	46064281 */ 	sub.s	$f10,$f8,$f6
/*  f136c80:	46105302 */ 	mul.s	$f12,$f10,$f16
/*  f136c84:	0c0068f4 */ 	jal	cosf
/*  f136c88:	00000000 */ 	nop
/*  f136c8c:	27b1016c */ 	addiu	$s1,$sp,0x16c
/*  f136c90:	02202025 */ 	or	$a0,$s1,$zero
/*  f136c94:	0c00566c */ 	jal	mtx4LoadIdentity
/*  f136c98:	e7a00154 */ 	swc1	$f0,0x154($sp)
/*  f136c9c:	0fc2d5be */ 	jal	camGetMatrix1740
/*  f136ca0:	00000000 */ 	nop
/*  f136ca4:	00402025 */ 	or	$a0,$v0,$zero
/*  f136ca8:	0c0056f8 */ 	jal	mtx00015be0
/*  f136cac:	02202825 */ 	or	$a1,$s1,$zero
/*  f136cb0:	44800000 */ 	mtc1	$zero,$f0
/*  f136cb4:	3c017f1b */ 	lui	$at,%hi(var7f1b57bc)
/*  f136cb8:	c42c57bc */ 	lwc1	$f12,%lo(var7f1b57bc)($at)
/*  f136cbc:	02202825 */ 	or	$a1,$s1,$zero
/*  f136cc0:	e7a0019c */ 	swc1	$f0,0x19c($sp)
/*  f136cc4:	e7a001a0 */ 	swc1	$f0,0x1a0($sp)
/*  f136cc8:	0c0057e2 */ 	jal	mtx00015f88
/*  f136ccc:	e7a001a4 */ 	swc1	$f0,0x1a4($sp)
/*  f136cd0:	8e630284 */ 	lw	$v1,0x284($s3)
/*  f136cd4:	c7b20170 */ 	lwc1	$f18,0x170($sp)
/*  f136cd8:	c7a60180 */ 	lwc1	$f6,0x180($sp)
/*  f136cdc:	c4641734 */ 	lwc1	$f4,0x1734($v1)
/*  f136ce0:	02002025 */ 	or	$a0,$s0,$zero
/*  f136ce4:	2405ffff */ 	addiu	$a1,$zero,-1
/*  f136ce8:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f136cec:	c7b20190 */ 	lwc1	$f18,0x190($sp)
/*  f136cf0:	e7a80170 */ 	swc1	$f8,0x170($sp)
/*  f136cf4:	c46a1734 */ 	lwc1	$f10,0x1734($v1)
/*  f136cf8:	460a3402 */ 	mul.s	$f16,$f6,$f10
/*  f136cfc:	c7a6016c */ 	lwc1	$f6,0x16c($sp)
/*  f136d00:	e7b00180 */ 	swc1	$f16,0x180($sp)
/*  f136d04:	c4641734 */ 	lwc1	$f4,0x1734($v1)
/*  f136d08:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f136d0c:	c7b2017c */ 	lwc1	$f18,0x17c($sp)
/*  f136d10:	e7a80190 */ 	swc1	$f8,0x190($sp)
/*  f136d14:	c46a1730 */ 	lwc1	$f10,0x1730($v1)
/*  f136d18:	460a3402 */ 	mul.s	$f16,$f6,$f10
/*  f136d1c:	c7a6018c */ 	lwc1	$f6,0x18c($sp)
/*  f136d20:	e7b0016c */ 	swc1	$f16,0x16c($sp)
/*  f136d24:	c4641730 */ 	lwc1	$f4,0x1730($v1)
/*  f136d28:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f136d2c:	e7a8017c */ 	swc1	$f8,0x17c($sp)
/*  f136d30:	c46a1730 */ 	lwc1	$f10,0x1730($v1)
/*  f136d34:	460a3402 */ 	mul.s	$f16,$f6,$f10
/*  f136d38:	e7b0018c */ 	swc1	$f16,0x18c($sp)
/*  f136d3c:	c4721bbc */ 	lwc1	$f18,0x1bbc($v1)
/*  f136d40:	e7b20148 */ 	swc1	$f18,0x148($sp)
/*  f136d44:	c4641bc0 */ 	lwc1	$f4,0x1bc0($v1)
/*  f136d48:	e7a4014c */ 	swc1	$f4,0x14c($sp)
/*  f136d4c:	c4681bc4 */ 	lwc1	$f8,0x1bc4($v1)
/*  f136d50:	0fc54df7 */ 	jal	gfxSetPrimColour
/*  f136d54:	e7a80150 */ 	swc1	$f8,0x150($sp)
/*  f136d58:	c7ae0154 */ 	lwc1	$f14,0x154($sp)
/*  f136d5c:	3c0fb900 */ 	lui	$t7,0xb900
/*  f136d60:	3c180050 */ 	lui	$t8,0x50
/*  f136d64:	3c013f80 */ 	lui	$at,0x3f80
/*  f136d68:	37184340 */ 	ori	$t8,$t8,0x4340
/*  f136d6c:	35ef031d */ 	ori	$t7,$t7,0x31d
/*  f136d70:	3c1f800a */ 	lui	$ra,%hi(g_StarPosIndexes)
/*  f136d74:	44816000 */ 	mtc1	$at,$f12
/*  f136d78:	ac4f0000 */ 	sw	$t7,0x0($v0)
/*  f136d7c:	ac580004 */ 	sw	$t8,0x4($v0)
/*  f136d80:	24500008 */ 	addiu	$s0,$v0,0x8
/*  f136d84:	27ff415c */ 	addiu	$ra,$ra,%lo(g_StarPosIndexes)
/*  f136d88:	0000b825 */ 	or	$s7,$zero,$zero
/*  f136d8c:	241e0001 */ 	addiu	$s8,$zero,0x1
/*  f136d90:	24160003 */ 	addiu	$s6,$zero,0x3
/*  f136d94:	3c14f600 */ 	lui	$s4,0xf600
/*  f136d98:	27b3011c */ 	addiu	$s3,$sp,0x11c
/*  f136d9c:	3c12fa00 */ 	lui	$s2,0xfa00
.L0f136da0:
/*  f136da0:	3c198008 */ 	lui	$t9,%hi(g_StarsBelowHorizon)
/*  f136da4:	8f39f124 */ 	lw	$t9,%lo(g_StarsBelowHorizon)($t9)
/*  f136da8:	24010002 */ 	addiu	$at,$zero,0x2
/*  f136dac:	3c11800a */ 	lui	$s1,%hi(g_StarGridSize)
/*  f136db0:	17200003 */ 	bnez	$t9,.L0f136dc0
/*  f136db4:	00000000 */ 	nop
/*  f136db8:	52e100e4 */ 	beql	$s7,$at,.L0f13714c
/*  f136dbc:	26f70001 */ 	addiu	$s7,$s7,0x1
.L0f136dc0:
/*  f136dc0:	8e314158 */ 	lw	$s1,%lo(g_StarGridSize)($s1)
/*  f136dc4:	0000a825 */ 	or	$s5,$zero,$zero
/*  f136dc8:	06200036 */ 	bltz	$s1,.L0f136ea4
/*  f136dcc:	00000000 */ 	nop
.L0f136dd0:
/*  f136dd0:	0620002f */ 	bltz	$s1,.L0f136e90
/*  f136dd4:	00006825 */ 	or	$t5,$zero,$zero
/*  f136dd8:	26220001 */ 	addiu	$v0,$s1,0x1
/*  f136ddc:	00570019 */ 	multu	$v0,$s7
/*  f136de0:	3c06800a */ 	lui	$a2,%hi(g_StarData3)
/*  f136de4:	00157880 */ 	sll	$t7,$s5,0x2
/*  f136de8:	27b800d0 */ 	addiu	$t8,$sp,0xd0
/*  f136dec:	01f86021 */ 	addu	$t4,$t7,$t8
/*  f136df0:	8cc64154 */ 	lw	$a2,%lo(g_StarData3)($a2)
/*  f136df4:	00007012 */ 	mflo	$t6
/*  f136df8:	00000000 */ 	nop
/*  f136dfc:	00000000 */ 	nop
/*  f136e00:	01c20019 */ 	multu	$t6,$v0
/*  f136e04:	00002012 */ 	mflo	$a0
/*  f136e08:	00000000 */ 	nop
/*  f136e0c:	00000000 */ 	nop
/*  f136e10:	02a20019 */ 	multu	$s5,$v0
/*  f136e14:	00002812 */ 	mflo	$a1
/*  f136e18:	00000000 */ 	nop
/*  f136e1c:	00000000 */ 	nop
.L0f136e20:
/*  f136e20:	008dc821 */ 	addu	$t9,$a0,$t5
/*  f136e24:	03257021 */ 	addu	$t6,$t9,$a1
/*  f136e28:	01d60019 */ 	multu	$t6,$s6
/*  f136e2c:	c7a60148 */ 	lwc1	$f6,0x148($sp)
/*  f136e30:	c7b2014c */ 	lwc1	$f18,0x14c($sp)
/*  f136e34:	25ad0001 */ 	addiu	$t5,$t5,0x1
/*  f136e38:	022d082a */ 	slt	$at,$s1,$t5
/*  f136e3c:	00001812 */ 	mflo	$v1
/*  f136e40:	00037880 */ 	sll	$t7,$v1,0x2
/*  f136e44:	00cf1021 */ 	addu	$v0,$a2,$t7
/*  f136e48:	c44a0000 */ 	lwc1	$f10,0x0($v0)
/*  f136e4c:	c4440004 */ 	lwc1	$f4,0x4($v0)
/*  f136e50:	460a3402 */ 	mul.s	$f16,$f6,$f10
/*  f136e54:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*  f136e58:	46049202 */ 	mul.s	$f8,$f18,$f4
/*  f136e5c:	c7b20150 */ 	lwc1	$f18,0x150($sp)
/*  f136e60:	46125102 */ 	mul.s	$f4,$f10,$f18
/*  f136e64:	46088180 */ 	add.s	$f6,$f16,$f8
/*  f136e68:	46062000 */ 	add.s	$f0,$f4,$f6
/*  f136e6c:	460e003e */ 	c.le.s	$f0,$f14
/*  f136e70:	00000000 */ 	nop
/*  f136e74:	45020004 */ 	bc1fl	.L0f136e88
/*  f136e78:	ad800000 */ 	sw	$zero,0x0($t4)
/*  f136e7c:	10000002 */ 	b	.L0f136e88
/*  f136e80:	ad9e0000 */ 	sw	$s8,0x0($t4)
/*  f136e84:	ad800000 */ 	sw	$zero,0x0($t4)
.L0f136e88:
/*  f136e88:	1020ffe5 */ 	beqz	$at,.L0f136e20
/*  f136e8c:	258c0010 */ 	addiu	$t4,$t4,0x10
.L0f136e90:
/*  f136e90:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f136e94:	0235082a */ 	slt	$at,$s1,$s5
/*  f136e98:	1020ffcd */ 	beqz	$at,.L0f136dd0
/*  f136e9c:	00000000 */ 	nop
/*  f136ea0:	0000a825 */ 	or	$s5,$zero,$zero
.L0f136ea4:
/*  f136ea4:	5a2000a9 */ 	blezl	$s1,.L0f13714c
/*  f136ea8:	26f70001 */ 	addiu	$s7,$s7,0x1
.L0f136eac:
/*  f136eac:	1a2000a2 */ 	blez	$s1,.L0f137138
/*  f136eb0:	00006825 */ 	or	$t5,$zero,$zero
/*  f136eb4:	0015c080 */ 	sll	$t8,$s5,0x2
/*  f136eb8:	27b900d0 */ 	addiu	$t9,$sp,0xd0
/*  f136ebc:	03196021 */ 	addu	$t4,$t8,$t9
.L0f136ec0:
/*  f136ec0:	8d8e0000 */ 	lw	$t6,0x0($t4)
/*  f136ec4:	11c0000a */ 	beqz	$t6,.L0f136ef0
/*  f136ec8:	00000000 */ 	nop
/*  f136ecc:	8d8f0010 */ 	lw	$t7,0x10($t4)
/*  f136ed0:	11e00007 */ 	beqz	$t7,.L0f136ef0
/*  f136ed4:	00000000 */ 	nop
/*  f136ed8:	8d980004 */ 	lw	$t8,0x4($t4)
/*  f136edc:	13000004 */ 	beqz	$t8,.L0f136ef0
/*  f136ee0:	00000000 */ 	nop
/*  f136ee4:	8d990014 */ 	lw	$t9,0x14($t4)
/*  f136ee8:	57200090 */ 	bnezl	$t9,.L0f13712c
/*  f136eec:	25ad0001 */ 	addiu	$t5,$t5,0x1
.L0f136ef0:
/*  f136ef0:	02310019 */ 	multu	$s1,$s1
/*  f136ef4:	00002825 */ 	or	$a1,$zero,$zero
/*  f136ef8:	00007012 */ 	mflo	$t6
/*  f136efc:	00000000 */ 	nop
/*  f136f00:	00000000 */ 	nop
/*  f136f04:	01d70019 */ 	multu	$t6,$s7
/*  f136f08:	8fee0000 */ 	lw	$t6,0x0($ra)
/*  f136f0c:	00007812 */ 	mflo	$t7
/*  f136f10:	01edc021 */ 	addu	$t8,$t7,$t5
/*  f136f14:	00000000 */ 	nop
/*  f136f18:	02b10019 */ 	multu	$s5,$s1
/*  f136f1c:	0000c812 */ 	mflo	$t9
/*  f136f20:	03195821 */ 	addu	$t3,$t8,$t9
/*  f136f24:	000b3880 */ 	sll	$a3,$t3,0x2
/*  f136f28:	01c74021 */ 	addu	$t0,$t6,$a3
/*  f136f2c:	8d020000 */ 	lw	$v0,0x0($t0)
/*  f136f30:	8d090004 */ 	lw	$t1,0x4($t0)
/*  f136f34:	3c198008 */ 	lui	$t9,%hi(g_StarPositions)
/*  f136f38:	00560019 */ 	multu	$v0,$s6
/*  f136f3c:	01225023 */ 	subu	$t2,$t1,$v0
/*  f136f40:	8f39f120 */ 	lw	$t9,%lo(g_StarPositions)($t9)
/*  f136f44:	00403025 */ 	or	$a2,$v0,$zero
/*  f136f48:	05410003 */ 	bgez	$t2,.L0f136f58
/*  f136f4c:	000a7883 */ 	sra	$t7,$t2,0x2
/*  f136f50:	25410003 */ 	addiu	$at,$t2,0x3
/*  f136f54:	00017883 */ 	sra	$t7,$at,0x2
.L0f136f58:
/*  f136f58:	0000c012 */ 	mflo	$t8
/*  f136f5c:	0049082a */ 	slt	$at,$v0,$t1
/*  f136f60:	25ea0001 */ 	addiu	$t2,$t7,0x1
/*  f136f64:	00402025 */ 	or	$a0,$v0,$zero
/*  f136f68:	1020006f */ 	beqz	$at,.L0f137128
/*  f136f6c:	03191821 */ 	addu	$v1,$t8,$t9
.L0f136f70:
/*  f136f70:	14c40009 */ 	bne	$a2,$a0,.L0f136f98
/*  f136f74:	02001025 */ 	or	$v0,$s0,$zero
/*  f136f78:	00057080 */ 	sll	$t6,$a1,0x2
/*  f136f7c:	026e7821 */ 	addu	$t7,$s3,$t6
/*  f136f80:	ac520000 */ 	sw	$s2,0x0($v0)
/*  f136f84:	8df80000 */ 	lw	$t8,0x0($t7)
/*  f136f88:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f136f8c:	24a50001 */ 	addiu	$a1,$a1,0x1
/*  f136f90:	00ca3021 */ 	addu	$a2,$a2,$t2
/*  f136f94:	ac580004 */ 	sw	$t8,0x4($v0)
.L0f136f98:
/*  f136f98:	80790000 */ 	lb	$t9,0x0($v1)
/*  f136f9c:	24630003 */ 	addiu	$v1,$v1,0x3
/*  f136fa0:	44998000 */ 	mtc1	$t9,$f16
/*  f136fa4:	00000000 */ 	nop
/*  f136fa8:	46808220 */ 	cvt.s.w	$f8,$f16
/*  f136fac:	c7b00174 */ 	lwc1	$f16,0x174($sp)
/*  f136fb0:	e7a800c4 */ 	swc1	$f8,0xc4($sp)
/*  f136fb4:	806efffe */ 	lb	$t6,-0x2($v1)
/*  f136fb8:	c7a800c4 */ 	lwc1	$f8,0xc4($sp)
/*  f136fbc:	448e5000 */ 	mtc1	$t6,$f10
/*  f136fc0:	00000000 */ 	nop
/*  f136fc4:	468054a0 */ 	cvt.s.w	$f18,$f10
/*  f136fc8:	46088282 */ 	mul.s	$f10,$f16,$f8
/*  f136fcc:	e7b200c8 */ 	swc1	$f18,0xc8($sp)
/*  f136fd0:	806fffff */ 	lb	$t7,-0x1($v1)
/*  f136fd4:	c7b20184 */ 	lwc1	$f18,0x184($sp)
/*  f136fd8:	448f2000 */ 	mtc1	$t7,$f4
/*  f136fdc:	00000000 */ 	nop
/*  f136fe0:	468021a0 */ 	cvt.s.w	$f6,$f4
/*  f136fe4:	c7a400c8 */ 	lwc1	$f4,0xc8($sp)
/*  f136fe8:	e7a600cc */ 	swc1	$f6,0xcc($sp)
/*  f136fec:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f136ff0:	c7b200cc */ 	lwc1	$f18,0xcc($sp)
/*  f136ff4:	46065400 */ 	add.s	$f16,$f10,$f6
/*  f136ff8:	c7aa0194 */ 	lwc1	$f10,0x194($sp)
/*  f136ffc:	460a9182 */ 	mul.s	$f6,$f18,$f10
/*  f137000:	46103280 */ 	add.s	$f10,$f6,$f16
/*  f137004:	c7a60170 */ 	lwc1	$f6,0x170($sp)
/*  f137008:	460a6003 */ 	div.s	$f0,$f12,$f10
/*  f13700c:	c7aa0180 */ 	lwc1	$f10,0x180($sp)
/*  f137010:	46083402 */ 	mul.s	$f16,$f6,$f8
/*  f137014:	00000000 */ 	nop
/*  f137018:	46045182 */ 	mul.s	$f6,$f10,$f4
/*  f13701c:	46068280 */ 	add.s	$f10,$f16,$f6
/*  f137020:	c7b00190 */ 	lwc1	$f16,0x190($sp)
/*  f137024:	46109182 */ 	mul.s	$f6,$f18,$f16
/*  f137028:	460a3400 */ 	add.s	$f16,$f6,$f10
/*  f13702c:	46008182 */ 	mul.s	$f6,$f16,$f0
/*  f137030:	461e3280 */ 	add.s	$f10,$f6,$f30
/*  f137034:	460ab03c */ 	c.lt.s	$f22,$f10
/*  f137038:	e7aa00b8 */ 	swc1	$f10,0xb8($sp)
/*  f13703c:	45000031 */ 	bc1f	.L0f137104
/*  f137040:	00000000 */ 	nop
/*  f137044:	461a503c */ 	c.lt.s	$f10,$f26
/*  f137048:	c7b0016c */ 	lwc1	$f16,0x16c($sp)
/*  f13704c:	4502002e */ 	bc1fl	.L0f137108
/*  f137050:	8fef0000 */ 	lw	$t7,0x0($ra)
/*  f137054:	46088182 */ 	mul.s	$f6,$f16,$f8
/*  f137058:	c7b0017c */ 	lwc1	$f16,0x17c($sp)
/*  f13705c:	46048202 */ 	mul.s	$f8,$f16,$f4
/*  f137060:	c7a4018c */ 	lwc1	$f4,0x18c($sp)
/*  f137064:	46083400 */ 	add.s	$f16,$f6,$f8
/*  f137068:	46049182 */ 	mul.s	$f6,$f18,$f4
/*  f13706c:	46103200 */ 	add.s	$f8,$f6,$f16
/*  f137070:	46004482 */ 	mul.s	$f18,$f8,$f0
/*  f137074:	4612e081 */ 	sub.s	$f2,$f28,$f18
/*  f137078:	4602a03c */ 	c.lt.s	$f20,$f2
/*  f13707c:	e7a200b4 */ 	swc1	$f2,0xb4($sp)
/*  f137080:	45020021 */ 	bc1fl	.L0f137108
/*  f137084:	8fef0000 */ 	lw	$t7,0x0($ra)
/*  f137088:	4618103c */ 	c.lt.s	$f2,$f24
/*  f13708c:	e7a200b4 */ 	swc1	$f2,0xb4($sp)
/*  f137090:	c7a400b4 */ 	lwc1	$f4,0xb4($sp)
/*  f137094:	4502001c */ 	bc1fl	.L0f137108
/*  f137098:	8fef0000 */ 	lw	$t7,0x0($ra)
/*  f13709c:	4600218d */ 	trunc.w.s	$f6,$f4
/*  f1370a0:	02001025 */ 	or	$v0,$s0,$zero
/*  f1370a4:	26100008 */ 	addiu	$s0,$s0,0x8
/*  f1370a8:	4600540d */ 	trunc.w.s	$f16,$f10
/*  f1370ac:	44193000 */ 	mfc1	$t9,$f6
/*  f1370b0:	440f8000 */ 	mfc1	$t7,$f16
/*  f1370b4:	afb900ac */ 	sw	$t9,0xac($sp)
/*  f1370b8:	25f90001 */ 	addiu	$t9,$t7,0x1
/*  f1370bc:	332e03ff */ 	andi	$t6,$t9,0x3ff
/*  f1370c0:	8fb900ac */ 	lw	$t9,0xac($sp)
/*  f1370c4:	afaf00b0 */ 	sw	$t7,0xb0($sp)
/*  f1370c8:	000e7880 */ 	sll	$t7,$t6,0x2
/*  f1370cc:	01f4c025 */ 	or	$t8,$t7,$s4
/*  f1370d0:	272e0001 */ 	addiu	$t6,$t9,0x1
/*  f1370d4:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*  f1370d8:	000fcb80 */ 	sll	$t9,$t7,0xe
/*  f1370dc:	03197025 */ 	or	$t6,$t8,$t9
/*  f1370e0:	ac4e0000 */ 	sw	$t6,0x0($v0)
/*  f1370e4:	8faf00b0 */ 	lw	$t7,0xb0($sp)
/*  f1370e8:	8fae00ac */ 	lw	$t6,0xac($sp)
/*  f1370ec:	31f803ff */ 	andi	$t8,$t7,0x3ff
/*  f1370f0:	0018c880 */ 	sll	$t9,$t8,0x2
/*  f1370f4:	31cf03ff */ 	andi	$t7,$t6,0x3ff
/*  f1370f8:	000fc380 */ 	sll	$t8,$t7,0xe
/*  f1370fc:	03387025 */ 	or	$t6,$t9,$t8
/*  f137100:	ac4e0004 */ 	sw	$t6,0x4($v0)
.L0f137104:
/*  f137104:	8fef0000 */ 	lw	$t7,0x0($ra)
.L0f137108:
/*  f137108:	24840001 */ 	addiu	$a0,$a0,0x1
/*  f13710c:	01e7c821 */ 	addu	$t9,$t7,$a3
/*  f137110:	8f380004 */ 	lw	$t8,0x4($t9)
/*  f137114:	0098082a */ 	slt	$at,$a0,$t8
/*  f137118:	1420ff95 */ 	bnez	$at,.L0f136f70
/*  f13711c:	00000000 */ 	nop
/*  f137120:	3c11800a */ 	lui	$s1,%hi(g_StarGridSize)
/*  f137124:	8e314158 */ 	lw	$s1,%lo(g_StarGridSize)($s1)
.L0f137128:
/*  f137128:	25ad0001 */ 	addiu	$t5,$t5,0x1
.L0f13712c:
/*  f13712c:	01b1082a */ 	slt	$at,$t5,$s1
/*  f137130:	1420ff63 */ 	bnez	$at,.L0f136ec0
/*  f137134:	258c0010 */ 	addiu	$t4,$t4,0x10
.L0f137138:
/*  f137138:	26b50001 */ 	addiu	$s5,$s5,0x1
/*  f13713c:	02b1082a */ 	slt	$at,$s5,$s1
/*  f137140:	1420ff5a */ 	bnez	$at,.L0f136eac
/*  f137144:	00000000 */ 	nop
/*  f137148:	26f70001 */ 	addiu	$s7,$s7,0x1
.L0f13714c:
/*  f13714c:	24010006 */ 	addiu	$at,$zero,0x6
/*  f137150:	16e1ff13 */ 	bne	$s7,$at,.L0f136da0
/*  f137154:	00000000 */ 	nop
/*  f137158:	0fc54e0e */ 	jal	func0f153838
/*  f13715c:	02002025 */ 	or	$a0,$s0,$zero
.L0f137160:
/*  f137160:	8fbf006c */ 	lw	$ra,0x6c($sp)
/*  f137164:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*  f137168:	d7b60020 */ 	ldc1	$f22,0x20($sp)
/*  f13716c:	d7b80028 */ 	ldc1	$f24,0x28($sp)
/*  f137170:	d7ba0030 */ 	ldc1	$f26,0x30($sp)
/*  f137174:	d7bc0038 */ 	ldc1	$f28,0x38($sp)
/*  f137178:	d7be0040 */ 	ldc1	$f30,0x40($sp)
/*  f13717c:	8fb00048 */ 	lw	$s0,0x48($sp)
/*  f137180:	8fb1004c */ 	lw	$s1,0x4c($sp)
/*  f137184:	8fb20050 */ 	lw	$s2,0x50($sp)
/*  f137188:	8fb30054 */ 	lw	$s3,0x54($sp)
/*  f13718c:	8fb40058 */ 	lw	$s4,0x58($sp)
/*  f137190:	8fb5005c */ 	lw	$s5,0x5c($sp)
/*  f137194:	8fb60060 */ 	lw	$s6,0x60($sp)
/*  f137198:	8fb70064 */ 	lw	$s7,0x64($sp)
/*  f13719c:	8fbe0068 */ 	lw	$s8,0x68($sp)
/*  f1371a0:	03e00008 */ 	jr	$ra
/*  f1371a4:	27bd01b0 */ 	addiu	$sp,$sp,0x1b0
);
