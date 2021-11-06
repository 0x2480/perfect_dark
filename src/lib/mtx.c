#include <ultra64.h>
#include "constants.h"
#include "game/atan2f.h"
#include "game/padhalllv.h"
#include "bss.h"
#include "lib/mtx.h"
#include "data.h"
#include "types.h"

void mtx00016110(f32 mtx1[3][3], f32 mtx2[3][3])
{
	f32 mtx3[3][3];

	mtx00016140(mtx1, mtx2, mtx3);
	mtx3Copy(mtx3, mtx2);
}

void mtx00016140(f32 mtx1[3][3], f32 mtx2[3][3], f32 dst[3][3])
{
	s32 i;
	s32 j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			dst[j][i] = mtx1[0][i] * mtx2[j][0] + mtx1[1][i] * mtx2[j][1] + mtx1[2][i] * mtx2[j][2];
		}
	}
}

void mtx000161b0(f32 mtx[3][3], f32 src[3], f32 dest[3])
{
	s32 i;

	for (i = 0; i < 3; i++) {
		dest[i] = mtx[0][i] * src[0] + mtx[1][i] * src[1] + mtx[2][i] * src[2];
	}
}

void mtx00016208(f32 mtx[3][3], struct coord *coord)
{
	f32 tmp[3];

	mtx000161b0(mtx, (f32 *)coord, tmp);

	coord->x = tmp[0];
	coord->y = tmp[1];
	coord->z = tmp[2];
}

void mtx4LoadYRotationWithTranslation(struct coord *coord, f32 angle, Mtxf *matrix)
{
	f32 cos = cosf(angle);
	f32 sin = sinf(angle);

	matrix->m[0][0] = cos;
	matrix->m[0][1] = 0;
	matrix->m[0][2] = -sin;
	matrix->m[0][3] = 0;

	matrix->m[1][0] = 0;
	matrix->m[1][1] = 1;
	matrix->m[1][2] = 0;
	matrix->m[1][3] = 0;

	matrix->m[2][0] = sin;
	matrix->m[2][1] = 0;
	matrix->m[2][2] = cos;
	matrix->m[2][3] = 0;

	matrix->m[3][0] = coord->x;
	matrix->m[3][1] = coord->y;
	matrix->m[3][2] = coord->z;
	matrix->m[3][3] = 1;
}

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func000171d8nb
/*    171d8:	27bdffe0 */ 	addiu	$sp,$sp,-32
/*    171dc:	afbf0014 */ 	sw	$ra,0x14($sp)
/*    171e0:	afa50024 */ 	sw	$a1,0x24($sp)
/*    171e4:	afa40020 */ 	sw	$a0,0x20($sp)
/*    171e8:	c7ac0024 */ 	lwc1	$f12,0x24($sp)
/*    171ec:	0c006d52 */ 	jal	cosf
/*    171f0:	afa60028 */ 	sw	$a2,0x28($sp)
/*    171f4:	c7ac0024 */ 	lwc1	$f12,0x24($sp)
/*    171f8:	0c006d55 */ 	jal	sinf
/*    171fc:	e7a0001c */ 	swc1	$f0,0x1c($sp)
/*    17200:	8fa60028 */ 	lw	$a2,0x28($sp)
/*    17204:	8fa20020 */ 	lw	$v0,0x20($sp)
/*    17208:	c7ae001c */ 	lwc1	$f14,0x1c($sp)
/*    1720c:	44801000 */ 	mtc1	$zero,$f2
/*    17210:	3c013f80 */ 	lui	$at,0x3f80
/*    17214:	44816000 */ 	mtc1	$at,$f12
/*    17218:	46000107 */ 	neg.s	$f4,$f0
/*    1721c:	e4c00018 */ 	swc1	$f0,0x18($a2)
/*    17220:	e4c40024 */ 	swc1	$f4,0x24($a2)
/*    17224:	e4ce0014 */ 	swc1	$f14,0x14($a2)
/*    17228:	e4ce0028 */ 	swc1	$f14,0x28($a2)
/*    1722c:	e4c20004 */ 	swc1	$f2,0x4($a2)
/*    17230:	e4c20008 */ 	swc1	$f2,0x8($a2)
/*    17234:	e4c2000c */ 	swc1	$f2,0xc($a2)
/*    17238:	e4c20010 */ 	swc1	$f2,0x10($a2)
/*    1723c:	e4c2001c */ 	swc1	$f2,0x1c($a2)
/*    17240:	e4c20020 */ 	swc1	$f2,0x20($a2)
/*    17244:	e4c2002c */ 	swc1	$f2,0x2c($a2)
/*    17248:	e4cc0000 */ 	swc1	$f12,0x0($a2)
/*    1724c:	c4460000 */ 	lwc1	$f6,0x0($v0)
/*    17250:	e4c60030 */ 	swc1	$f6,0x30($a2)
/*    17254:	c4480004 */ 	lwc1	$f8,0x4($v0)
/*    17258:	e4c80034 */ 	swc1	$f8,0x34($a2)
/*    1725c:	c44a0008 */ 	lwc1	$f10,0x8($v0)
/*    17260:	e4cc003c */ 	swc1	$f12,0x3c($a2)
/*    17264:	e4ca0038 */ 	swc1	$f10,0x38($a2)
/*    17268:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*    1726c:	27bd0020 */ 	addiu	$sp,$sp,0x20
/*    17270:	03e00008 */ 	jr	$ra
/*    17274:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

void mtx4LoadXRotation(f32 angle, Mtxf *matrix)
{
	f32 cos = cosf(angle);
	f32 sin = sinf(angle);

	matrix->m[0][0] = 1;
	matrix->m[0][1] = 0;
	matrix->m[0][2] = 0;
	matrix->m[0][3] = 0;

	matrix->m[1][0] = 0;
	matrix->m[1][1] = cos;
	matrix->m[1][2] = sin;
	matrix->m[1][3] = 0;

	matrix->m[2][0] = 0;
	matrix->m[2][1] = -sin;
	matrix->m[2][2] = cos;
	matrix->m[2][3] = 0;

	matrix->m[3][0] = 0;
	matrix->m[3][1] = 0;
	matrix->m[3][2] = 0;
	matrix->m[3][3] = 1;
}

void mtx4LoadYRotation(f32 angle, Mtxf *matrix)
{
	f32 cos = cosf(angle);
	f32 sin = sinf(angle);

	matrix->m[0][0] = cos;
	matrix->m[0][1] = 0;
	matrix->m[0][2] = -sin;
	matrix->m[0][3] = 0;

	matrix->m[1][0] = 0;
	matrix->m[1][1] = 1;
	matrix->m[1][2] = 0;
	matrix->m[1][3] = 0;

	matrix->m[2][0] = sin;
	matrix->m[2][1] = 0;
	matrix->m[2][2] = cos;
	matrix->m[2][3] = 0;

	matrix->m[3][0] = 0;
	matrix->m[3][1] = 0;
	matrix->m[3][2] = 0;
	matrix->m[3][3] = 1;
}

void mtx4LoadZRotation(f32 angle, Mtxf *matrix)
{
	f32 cos = cosf(angle);
	f32 sin = (float)sinf(angle);

	matrix->m[0][0] = cos;
	matrix->m[0][1] = sin;
	matrix->m[0][2] = 0;
	matrix->m[0][3] = 0;

	matrix->m[1][0] = -sin;
	matrix->m[1][1] = cos;
	matrix->m[1][2] = 0;
	matrix->m[1][3] = 0;

	matrix->m[2][0] = 0;
	matrix->m[2][1] = 0;
	matrix->m[2][2] = 1;
	matrix->m[2][3] = 0;

	matrix->m[3][0] = 0;
	matrix->m[3][1] = 0;
	matrix->m[3][2] = 0;
	matrix->m[3][3] = 1;
}

void mtx4LoadRotation(struct coord *src, Mtxf *dest)
{
	f32 xcos = cosf(src->x);
	f32 xsin = sinf(src->x);
	f32 ycos = cosf(src->y);
	f32 ysin = sinf(src->y);
	f32 zcos = cosf(src->z);
	f32 zsin = sinf(src->z);
	f32 a = xsin * zsin;
	f32 b = xcos * zsin;
	f32 c = xsin * zcos;
	f32 d = xcos * zcos;

	dest->m[0][0] = ycos * zcos;
	dest->m[0][1] = ycos * zsin;
	dest->m[0][2] = -ysin;
	dest->m[0][3] = 0;

	dest->m[1][0] = c * ysin - xcos * zsin;
	dest->m[1][1] = a * ysin + xcos * zcos;
	dest->m[1][2] = xsin * ycos;
	dest->m[1][3] = 0;

	dest->m[2][0] = d * ysin + xsin * zsin;
	dest->m[2][1] = b * ysin - xsin * zcos;
	dest->m[2][2] = xcos * ycos;
	dest->m[2][3] = 0;

	dest->m[3][0] = 0;
	dest->m[3][1] = 0;
	dest->m[3][2] = 0;
	dest->m[3][3] = 1;
}

GLOBAL_ASM(
glabel mtx000165d8
/*    165d8:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*    165dc:	afbf001c */ 	sw	$ra,0x1c($sp)
/*    165e0:	afb10018 */ 	sw	$s1,0x18($sp)
/*    165e4:	afb00014 */ 	sw	$s0,0x14($sp)
/*    165e8:	c4800018 */ 	lwc1	$f0,0x18($a0)
/*    165ec:	c4820028 */ 	lwc1	$f2,0x28($a0)
/*    165f0:	00808025 */ 	or	$s0,$a0,$zero
/*    165f4:	46000102 */ 	mul.s	$f4,$f0,$f0
/*    165f8:	00a08825 */ 	or	$s1,$a1,$zero
/*    165fc:	46021182 */ 	mul.s	$f6,$f2,$f2
/*    16600:	0c012974 */ 	jal	sqrtf
/*    16604:	46062300 */ 	add.s	$f12,$f4,$f6
/*    16608:	3c013600 */ 	lui	$at,0x3600
/*    1660c:	44814000 */ 	mtc1	$at,$f8
/*    16610:	e7a00024 */ 	swc1	$f0,0x24($sp)
/*    16614:	4600403c */ 	c.lt.s	$f8,$f0
/*    16618:	00000000 */ 	nop
/*    1661c:	45020010 */ 	bc1fl	.L00016660
/*    16620:	44805000 */ 	mtc1	$zero,$f10
/*    16624:	c60c0018 */ 	lwc1	$f12,0x18($s0)
/*    16628:	0fc259d4 */ 	jal	atan2f
/*    1662c:	c60e0028 */ 	lwc1	$f14,0x28($s0)
/*    16630:	e6200000 */ 	swc1	$f0,0x0($s1)
/*    16634:	c60c0008 */ 	lwc1	$f12,0x8($s0)
/*    16638:	c7ae0024 */ 	lwc1	$f14,0x24($sp)
/*    1663c:	0fc259d4 */ 	jal	atan2f
/*    16640:	46006307 */ 	neg.s	$f12,$f12
/*    16644:	e6200004 */ 	swc1	$f0,0x4($s1)
/*    16648:	c60e0000 */ 	lwc1	$f14,0x0($s0)
/*    1664c:	0fc259d4 */ 	jal	atan2f
/*    16650:	c60c0004 */ 	lwc1	$f12,0x4($s0)
/*    16654:	1000000e */ 	b	.L00016690
/*    16658:	e6200008 */ 	swc1	$f0,0x8($s1)
/*    1665c:	44805000 */ 	mtc1	$zero,$f10
.L00016660:
/*    16660:	00000000 */ 	nop
/*    16664:	e62a0000 */ 	swc1	$f10,0x0($s1)
/*    16668:	c60c0008 */ 	lwc1	$f12,0x8($s0)
/*    1666c:	c7ae0024 */ 	lwc1	$f14,0x24($sp)
/*    16670:	0fc259d4 */ 	jal	atan2f
/*    16674:	46006307 */ 	neg.s	$f12,$f12
/*    16678:	e6200004 */ 	swc1	$f0,0x4($s1)
/*    1667c:	c60c0010 */ 	lwc1	$f12,0x10($s0)
/*    16680:	c60e0014 */ 	lwc1	$f14,0x14($s0)
/*    16684:	0fc259d4 */ 	jal	atan2f
/*    16688:	46006307 */ 	neg.s	$f12,$f12
/*    1668c:	e6200008 */ 	swc1	$f0,0x8($s1)
.L00016690:
/*    16690:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*    16694:	8fb00014 */ 	lw	$s0,0x14($sp)
/*    16698:	8fb10018 */ 	lw	$s1,0x18($sp)
/*    1669c:	03e00008 */ 	jr	$ra
/*    166a0:	27bd0028 */ 	addiu	$sp,$sp,0x28
);

void mtx000166a4(struct coord *pos, struct coord *rot, Mtxf *matrix)
{
	mtx4LoadRotation(rot, matrix);
	mtx4SetTranslation(pos, matrix);
}

void mtx000166dc(struct coord *pos, Mtxf *matrix)
{
	mtx4LoadIdentity(matrix);
	mtx4SetTranslation(pos, matrix);
}

void mtx00016710(f32 mult, f32 mtx[4][4])
{
	mtx[0][2] *= mult;
	mtx[1][2] *= mult;
	mtx[2][2] *= mult;
	mtx[3][2] *= mult;
}

void mtx00016748(f32 arg0)
{
	var8005ef10[0] = 65536 * arg0;
}

void mtx00016760(void)
{
	g_Vars.unk000510 = var8005ef10[0];
	var8005ef10[0] = 65536;
}

void mtx00016784(void)
{
	var8005ef10[0] = g_Vars.unk000510;
}

GLOBAL_ASM(
glabel mtx00016798
/*    16798:	3c0a8006 */ 	lui	$t2,%hi(var8005ef10)
/*    1679c:	254aef10 */ 	addiu	$t2,$t2,%lo(var8005ef10)
/*    167a0:	00001025 */ 	or	$v0,$zero,$zero
/*    167a4:	00803825 */ 	or	$a3,$a0,$zero
/*    167a8:	240b0008 */ 	addiu	$t3,$zero,0x8
/*    167ac:	3c09ffff */ 	lui	$t1,0xffff
.L000167b0:
/*    167b0:	8ce30000 */ 	lw	$v1,0x0($a3)
/*    167b4:	8ce60020 */ 	lw	$a2,0x20($a3)
/*    167b8:	c5480000 */ 	lwc1	$f8,0x0($t2)
/*    167bc:	0069c024 */ 	and	$t8,$v1,$t1
/*    167c0:	0006cc02 */ 	srl	$t9,$a2,0x10
/*    167c4:	03196025 */ 	or	$t4,$t8,$t9
/*    167c8:	448c2000 */ 	mtc1	$t4,$f4
/*    167cc:	000278c0 */ 	sll	$t7,$v0,0x3
/*    167d0:	00af4021 */ 	addu	$t0,$a1,$t7
/*    167d4:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    167d8:	00036c00 */ 	sll	$t5,$v1,0x10
/*    167dc:	30ceffff */ 	andi	$t6,$a2,0xffff
/*    167e0:	01ae7825 */ 	or	$t7,$t5,$t6
/*    167e4:	448f8000 */ 	mtc1	$t7,$f16
/*    167e8:	30580001 */ 	andi	$t8,$v0,0x1
/*    167ec:	46083283 */ 	div.s	$f10,$f6,$f8
/*    167f0:	0018c880 */ 	sll	$t9,$t8,0x2
/*    167f4:	01596021 */ 	addu	$t4,$t2,$t9
/*    167f8:	24420001 */ 	addiu	$v0,$v0,0x1
/*    167fc:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    16800:	24e70004 */ 	addiu	$a3,$a3,0x4
/*    16804:	e50a0000 */ 	swc1	$f10,0x0($t0)
/*    16808:	c5840000 */ 	lwc1	$f4,0x0($t4)
/*    1680c:	46049183 */ 	div.s	$f6,$f18,$f4
/*    16810:	144bffe7 */ 	bne	$v0,$t3,.L000167b0
/*    16814:	e5060004 */ 	swc1	$f6,0x4($t0)
/*    16818:	03e00008 */ 	jr	$ra
/*    1681c:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel mtx00016820
/*    16820:	00001025 */ 	or	$v0,$zero,$zero
/*    16824:	00803825 */ 	or	$a3,$a0,$zero
/*    16828:	240a0008 */ 	addiu	$t2,$zero,0x8
/*    1682c:	3c09ffff */ 	lui	$t1,0xffff
.L00016830:
/*    16830:	8ce30000 */ 	lw	$v1,0x0($a3)
/*    16834:	8ce60020 */ 	lw	$a2,0x20($a3)
/*    16838:	000278c0 */ 	sll	$t7,$v0,0x3
/*    1683c:	0069c024 */ 	and	$t8,$v1,$t1
/*    16840:	00036400 */ 	sll	$t4,$v1,0x10
/*    16844:	0006cc02 */ 	srl	$t9,$a2,0x10
/*    16848:	30cdffff */ 	andi	$t5,$a2,0xffff
/*    1684c:	24420001 */ 	addiu	$v0,$v0,0x1
/*    16850:	03195825 */ 	or	$t3,$t8,$t9
/*    16854:	00af4021 */ 	addu	$t0,$a1,$t7
/*    16858:	018d7025 */ 	or	$t6,$t4,$t5
/*    1685c:	24e70004 */ 	addiu	$a3,$a3,0x4
/*    16860:	ad0b0000 */ 	sw	$t3,0x0($t0)
/*    16864:	144afff2 */ 	bne	$v0,$t2,.L00016830
/*    16868:	ad0e0004 */ 	sw	$t6,0x4($t0)
/*    1686c:	03e00008 */ 	jr	$ra
/*    16870:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel mtx00016874
/*    16874:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*    16878:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*    1687c:	c7b40058 */ 	lwc1	$f20,0x58($sp)
/*    16880:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*    16884:	c7b6005c */ 	lwc1	$f22,0x5c($sp)
/*    16888:	4614a102 */ 	mul.s	$f4,$f20,$f20
/*    1688c:	f7b80020 */ 	sdc1	$f24,0x20($sp)
/*    16890:	c7b80060 */ 	lwc1	$f24,0x60($sp)
/*    16894:	4616b182 */ 	mul.s	$f6,$f22,$f22
/*    16898:	afbf0044 */ 	sw	$ra,0x44($sp)
/*    1689c:	f7be0038 */ 	sdc1	$f30,0x38($sp)
/*    168a0:	4618c282 */ 	mul.s	$f10,$f24,$f24
/*    168a4:	f7bc0030 */ 	sdc1	$f28,0x30($sp)
/*    168a8:	f7ba0028 */ 	sdc1	$f26,0x28($sp)
/*    168ac:	afa5004c */ 	sw	$a1,0x4c($sp)
/*    168b0:	afa60050 */ 	sw	$a2,0x50($sp)
/*    168b4:	46062200 */ 	add.s	$f8,$f4,$f6
/*    168b8:	afa70054 */ 	sw	$a3,0x54($sp)
/*    168bc:	afa40048 */ 	sw	$a0,0x48($sp)
/*    168c0:	0c012974 */ 	jal	sqrtf
/*    168c4:	460a4300 */ 	add.s	$f12,$f8,$f10
/*    168c8:	3c01bf80 */ 	lui	$at,0xbf80
/*    168cc:	44812000 */ 	mtc1	$at,$f4
/*    168d0:	c7a60068 */ 	lwc1	$f6,0x68($sp)
/*    168d4:	c7aa006c */ 	lwc1	$f10,0x6c($sp)
/*    168d8:	46002083 */ 	div.s	$f2,$f4,$f0
/*    168dc:	4602a502 */ 	mul.s	$f20,$f20,$f2
/*    168e0:	00000000 */ 	nop
/*    168e4:	4602b582 */ 	mul.s	$f22,$f22,$f2
/*    168e8:	00000000 */ 	nop
/*    168ec:	4602c602 */ 	mul.s	$f24,$f24,$f2
/*    168f0:	00000000 */ 	nop
/*    168f4:	46183202 */ 	mul.s	$f8,$f6,$f24
/*    168f8:	00000000 */ 	nop
/*    168fc:	46165102 */ 	mul.s	$f4,$f10,$f22
/*    16900:	46044681 */ 	sub.s	$f26,$f8,$f4
/*    16904:	46145202 */ 	mul.s	$f8,$f10,$f20
/*    16908:	c7a40064 */ 	lwc1	$f4,0x64($sp)
/*    1690c:	46182282 */ 	mul.s	$f10,$f4,$f24
/*    16910:	460a4701 */ 	sub.s	$f28,$f8,$f10
/*    16914:	46162202 */ 	mul.s	$f8,$f4,$f22
/*    16918:	00000000 */ 	nop
/*    1691c:	46143282 */ 	mul.s	$f10,$f6,$f20
/*    16920:	460a4781 */ 	sub.s	$f30,$f8,$f10
/*    16924:	461ad102 */ 	mul.s	$f4,$f26,$f26
/*    16928:	00000000 */ 	nop
/*    1692c:	461ce182 */ 	mul.s	$f6,$f28,$f28
/*    16930:	46062200 */ 	add.s	$f8,$f4,$f6
/*    16934:	461ef282 */ 	mul.s	$f10,$f30,$f30
/*    16938:	0c012974 */ 	jal	sqrtf
/*    1693c:	460a4300 */ 	add.s	$f12,$f8,$f10
/*    16940:	3c013f80 */ 	lui	$at,0x3f80
/*    16944:	44812000 */ 	mtc1	$at,$f4
/*    16948:	00000000 */ 	nop
/*    1694c:	46002083 */ 	div.s	$f2,$f4,$f0
/*    16950:	4602d682 */ 	mul.s	$f26,$f26,$f2
/*    16954:	00000000 */ 	nop
/*    16958:	4602e702 */ 	mul.s	$f28,$f28,$f2
/*    1695c:	00000000 */ 	nop
/*    16960:	4602f782 */ 	mul.s	$f30,$f30,$f2
/*    16964:	00000000 */ 	nop
/*    16968:	461eb182 */ 	mul.s	$f6,$f22,$f30
/*    1696c:	00000000 */ 	nop
/*    16970:	461cc202 */ 	mul.s	$f8,$f24,$f28
/*    16974:	00000000 */ 	nop
/*    16978:	461ac282 */ 	mul.s	$f10,$f24,$f26
/*    1697c:	00000000 */ 	nop
/*    16980:	461ea102 */ 	mul.s	$f4,$f20,$f30
/*    16984:	46083381 */ 	sub.s	$f14,$f6,$f8
/*    16988:	461ca182 */ 	mul.s	$f6,$f20,$f28
/*    1698c:	00000000 */ 	nop
/*    16990:	461ab202 */ 	mul.s	$f8,$f22,$f26
/*    16994:	e7ae0064 */ 	swc1	$f14,0x64($sp)
/*    16998:	46045401 */ 	sub.s	$f16,$f10,$f4
/*    1699c:	460e7282 */ 	mul.s	$f10,$f14,$f14
/*    169a0:	00000000 */ 	nop
/*    169a4:	46108102 */ 	mul.s	$f4,$f16,$f16
/*    169a8:	e7b00068 */ 	swc1	$f16,0x68($sp)
/*    169ac:	46083481 */ 	sub.s	$f18,$f6,$f8
/*    169b0:	46129202 */ 	mul.s	$f8,$f18,$f18
/*    169b4:	46045180 */ 	add.s	$f6,$f10,$f4
/*    169b8:	e7b2006c */ 	swc1	$f18,0x6c($sp)
/*    169bc:	0c012974 */ 	jal	sqrtf
/*    169c0:	46083300 */ 	add.s	$f12,$f6,$f8
/*    169c4:	3c013f80 */ 	lui	$at,0x3f80
/*    169c8:	44815000 */ 	mtc1	$at,$f10
/*    169cc:	c7ae0064 */ 	lwc1	$f14,0x64($sp)
/*    169d0:	c7ac0068 */ 	lwc1	$f12,0x68($sp)
/*    169d4:	46005083 */ 	div.s	$f2,$f10,$f0
/*    169d8:	c7a4006c */ 	lwc1	$f4,0x6c($sp)
/*    169dc:	8fa40048 */ 	lw	$a0,0x48($sp)
/*    169e0:	46027382 */ 	mul.s	$f14,$f14,$f2
/*    169e4:	00000000 */ 	nop
/*    169e8:	46026302 */ 	mul.s	$f12,$f12,$f2
/*    169ec:	00000000 */ 	nop
/*    169f0:	46022182 */ 	mul.s	$f6,$f4,$f2
/*    169f4:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*    169f8:	e49a0000 */ 	swc1	$f26,0x0($a0)
/*    169fc:	e49c0010 */ 	swc1	$f28,0x10($a0)
/*    16a00:	e49e0020 */ 	swc1	$f30,0x20($a0)
/*    16a04:	c7a8004c */ 	lwc1	$f8,0x4c($sp)
/*    16a08:	c7a40050 */ 	lwc1	$f4,0x50($sp)
/*    16a0c:	461a4282 */ 	mul.s	$f10,$f8,$f26
/*    16a10:	00000000 */ 	nop
/*    16a14:	461c2182 */ 	mul.s	$f6,$f4,$f28
/*    16a18:	c7a40054 */ 	lwc1	$f4,0x54($sp)
/*    16a1c:	e48e0004 */ 	swc1	$f14,0x4($a0)
/*    16a20:	e48c0014 */ 	swc1	$f12,0x14($a0)
/*    16a24:	46065200 */ 	add.s	$f8,$f10,$f6
/*    16a28:	461e2282 */ 	mul.s	$f10,$f4,$f30
/*    16a2c:	460a4180 */ 	add.s	$f6,$f8,$f10
/*    16a30:	46003107 */ 	neg.s	$f4,$f6
/*    16a34:	e4840030 */ 	swc1	$f4,0x30($a0)
/*    16a38:	e7ae0064 */ 	swc1	$f14,0x64($sp)
/*    16a3c:	c7ae006c */ 	lwc1	$f14,0x6c($sp)
/*    16a40:	e7ac0068 */ 	swc1	$f12,0x68($sp)
/*    16a44:	c7ac004c */ 	lwc1	$f12,0x4c($sp)
/*    16a48:	c7a20050 */ 	lwc1	$f2,0x50($sp)
/*    16a4c:	c7a00054 */ 	lwc1	$f0,0x54($sp)
/*    16a50:	e48e0024 */ 	swc1	$f14,0x24($a0)
/*    16a54:	c7a80064 */ 	lwc1	$f8,0x64($sp)
/*    16a58:	c7a60068 */ 	lwc1	$f6,0x68($sp)
/*    16a5c:	e4940008 */ 	swc1	$f20,0x8($a0)
/*    16a60:	46086282 */ 	mul.s	$f10,$f12,$f8
/*    16a64:	e4960018 */ 	swc1	$f22,0x18($a0)
/*    16a68:	e4980028 */ 	swc1	$f24,0x28($a0)
/*    16a6c:	46061102 */ 	mul.s	$f4,$f2,$f6
/*    16a70:	46045200 */ 	add.s	$f8,$f10,$f4
/*    16a74:	460e0182 */ 	mul.s	$f6,$f0,$f14
/*    16a78:	46064280 */ 	add.s	$f10,$f8,$f6
/*    16a7c:	46146202 */ 	mul.s	$f8,$f12,$f20
/*    16a80:	00000000 */ 	nop
/*    16a84:	46161182 */ 	mul.s	$f6,$f2,$f22
/*    16a88:	46005107 */ 	neg.s	$f4,$f10
/*    16a8c:	e4840034 */ 	swc1	$f4,0x34($a0)
/*    16a90:	46180102 */ 	mul.s	$f4,$f0,$f24
/*    16a94:	44800000 */ 	mtc1	$zero,$f0
/*    16a98:	00000000 */ 	nop
/*    16a9c:	e480000c */ 	swc1	$f0,0xc($a0)
/*    16aa0:	46064280 */ 	add.s	$f10,$f8,$f6
/*    16aa4:	e480001c */ 	swc1	$f0,0x1c($a0)
/*    16aa8:	e480002c */ 	swc1	$f0,0x2c($a0)
/*    16aac:	46045200 */ 	add.s	$f8,$f10,$f4
/*    16ab0:	44815000 */ 	mtc1	$at,$f10
/*    16ab4:	46004187 */ 	neg.s	$f6,$f8
/*    16ab8:	e48a003c */ 	swc1	$f10,0x3c($a0)
/*    16abc:	e4860038 */ 	swc1	$f6,0x38($a0)
/*    16ac0:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*    16ac4:	d7be0038 */ 	ldc1	$f30,0x38($sp)
/*    16ac8:	d7bc0030 */ 	ldc1	$f28,0x30($sp)
/*    16acc:	d7ba0028 */ 	ldc1	$f26,0x28($sp)
/*    16ad0:	d7b80020 */ 	ldc1	$f24,0x20($sp)
/*    16ad4:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*    16ad8:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*    16adc:	03e00008 */ 	jr	$ra
/*    16ae0:	27bd0048 */ 	addiu	$sp,$sp,0x48
);

void mtx00016ae4(Mtxf *matrix, f32 posx, f32 posy, f32 posz, f32 lookx, f32 looky, f32 lookz, f32 upx, f32 upy, f32 upz)
{
	mtx00016874(matrix, posx, posy, posz, lookx - posx, looky - posy, lookz - posz, upx, upy, upz);
}

GLOBAL_ASM(
glabel mtx00016b58
/*    16b58:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*    16b5c:	f7b40010 */ 	sdc1	$f20,0x10($sp)
/*    16b60:	c7b40058 */ 	lwc1	$f20,0x58($sp)
/*    16b64:	f7b60018 */ 	sdc1	$f22,0x18($sp)
/*    16b68:	c7b6005c */ 	lwc1	$f22,0x5c($sp)
/*    16b6c:	4614a102 */ 	mul.s	$f4,$f20,$f20
/*    16b70:	f7b80020 */ 	sdc1	$f24,0x20($sp)
/*    16b74:	c7b80060 */ 	lwc1	$f24,0x60($sp)
/*    16b78:	4616b182 */ 	mul.s	$f6,$f22,$f22
/*    16b7c:	afbf0044 */ 	sw	$ra,0x44($sp)
/*    16b80:	f7be0038 */ 	sdc1	$f30,0x38($sp)
/*    16b84:	4618c282 */ 	mul.s	$f10,$f24,$f24
/*    16b88:	f7bc0030 */ 	sdc1	$f28,0x30($sp)
/*    16b8c:	f7ba0028 */ 	sdc1	$f26,0x28($sp)
/*    16b90:	afa5004c */ 	sw	$a1,0x4c($sp)
/*    16b94:	afa60050 */ 	sw	$a2,0x50($sp)
/*    16b98:	46062200 */ 	add.s	$f8,$f4,$f6
/*    16b9c:	afa70054 */ 	sw	$a3,0x54($sp)
/*    16ba0:	afa40048 */ 	sw	$a0,0x48($sp)
/*    16ba4:	0c012974 */ 	jal	sqrtf
/*    16ba8:	460a4300 */ 	add.s	$f12,$f8,$f10
/*    16bac:	3c01bf80 */ 	lui	$at,0xbf80
/*    16bb0:	44812000 */ 	mtc1	$at,$f4
/*    16bb4:	c7a60068 */ 	lwc1	$f6,0x68($sp)
/*    16bb8:	c7aa006c */ 	lwc1	$f10,0x6c($sp)
/*    16bbc:	46002083 */ 	div.s	$f2,$f4,$f0
/*    16bc0:	4602a502 */ 	mul.s	$f20,$f20,$f2
/*    16bc4:	00000000 */ 	nop
/*    16bc8:	4602b582 */ 	mul.s	$f22,$f22,$f2
/*    16bcc:	00000000 */ 	nop
/*    16bd0:	4602c602 */ 	mul.s	$f24,$f24,$f2
/*    16bd4:	00000000 */ 	nop
/*    16bd8:	46183202 */ 	mul.s	$f8,$f6,$f24
/*    16bdc:	00000000 */ 	nop
/*    16be0:	46165102 */ 	mul.s	$f4,$f10,$f22
/*    16be4:	46044681 */ 	sub.s	$f26,$f8,$f4
/*    16be8:	46145202 */ 	mul.s	$f8,$f10,$f20
/*    16bec:	c7a40064 */ 	lwc1	$f4,0x64($sp)
/*    16bf0:	46182282 */ 	mul.s	$f10,$f4,$f24
/*    16bf4:	460a4701 */ 	sub.s	$f28,$f8,$f10
/*    16bf8:	46162202 */ 	mul.s	$f8,$f4,$f22
/*    16bfc:	00000000 */ 	nop
/*    16c00:	46143282 */ 	mul.s	$f10,$f6,$f20
/*    16c04:	460a4781 */ 	sub.s	$f30,$f8,$f10
/*    16c08:	461ad102 */ 	mul.s	$f4,$f26,$f26
/*    16c0c:	00000000 */ 	nop
/*    16c10:	461ce182 */ 	mul.s	$f6,$f28,$f28
/*    16c14:	46062200 */ 	add.s	$f8,$f4,$f6
/*    16c18:	461ef282 */ 	mul.s	$f10,$f30,$f30
/*    16c1c:	0c012974 */ 	jal	sqrtf
/*    16c20:	460a4300 */ 	add.s	$f12,$f8,$f10
/*    16c24:	3c013f80 */ 	lui	$at,0x3f80
/*    16c28:	44812000 */ 	mtc1	$at,$f4
/*    16c2c:	00000000 */ 	nop
/*    16c30:	46002083 */ 	div.s	$f2,$f4,$f0
/*    16c34:	4602d682 */ 	mul.s	$f26,$f26,$f2
/*    16c38:	00000000 */ 	nop
/*    16c3c:	4602e702 */ 	mul.s	$f28,$f28,$f2
/*    16c40:	00000000 */ 	nop
/*    16c44:	4602f782 */ 	mul.s	$f30,$f30,$f2
/*    16c48:	00000000 */ 	nop
/*    16c4c:	461eb182 */ 	mul.s	$f6,$f22,$f30
/*    16c50:	00000000 */ 	nop
/*    16c54:	461cc202 */ 	mul.s	$f8,$f24,$f28
/*    16c58:	00000000 */ 	nop
/*    16c5c:	461ac282 */ 	mul.s	$f10,$f24,$f26
/*    16c60:	00000000 */ 	nop
/*    16c64:	461ea102 */ 	mul.s	$f4,$f20,$f30
/*    16c68:	46083381 */ 	sub.s	$f14,$f6,$f8
/*    16c6c:	461ca182 */ 	mul.s	$f6,$f20,$f28
/*    16c70:	00000000 */ 	nop
/*    16c74:	461ab202 */ 	mul.s	$f8,$f22,$f26
/*    16c78:	e7ae0064 */ 	swc1	$f14,0x64($sp)
/*    16c7c:	46045401 */ 	sub.s	$f16,$f10,$f4
/*    16c80:	460e7282 */ 	mul.s	$f10,$f14,$f14
/*    16c84:	00000000 */ 	nop
/*    16c88:	46108102 */ 	mul.s	$f4,$f16,$f16
/*    16c8c:	e7b00068 */ 	swc1	$f16,0x68($sp)
/*    16c90:	46083481 */ 	sub.s	$f18,$f6,$f8
/*    16c94:	46129202 */ 	mul.s	$f8,$f18,$f18
/*    16c98:	46045180 */ 	add.s	$f6,$f10,$f4
/*    16c9c:	e7b2006c */ 	swc1	$f18,0x6c($sp)
/*    16ca0:	0c012974 */ 	jal	sqrtf
/*    16ca4:	46083300 */ 	add.s	$f12,$f6,$f8
/*    16ca8:	3c013f80 */ 	lui	$at,0x3f80
/*    16cac:	44815000 */ 	mtc1	$at,$f10
/*    16cb0:	c7ae0064 */ 	lwc1	$f14,0x64($sp)
/*    16cb4:	c7ac0068 */ 	lwc1	$f12,0x68($sp)
/*    16cb8:	46005083 */ 	div.s	$f2,$f10,$f0
/*    16cbc:	c7a4006c */ 	lwc1	$f4,0x6c($sp)
/*    16cc0:	8fa40048 */ 	lw	$a0,0x48($sp)
/*    16cc4:	44800000 */ 	mtc1	$zero,$f0
/*    16cc8:	46027382 */ 	mul.s	$f14,$f14,$f2
/*    16ccc:	00000000 */ 	nop
/*    16cd0:	46026302 */ 	mul.s	$f12,$f12,$f2
/*    16cd4:	00000000 */ 	nop
/*    16cd8:	46022182 */ 	mul.s	$f6,$f4,$f2
/*    16cdc:	e7a6006c */ 	swc1	$f6,0x6c($sp)
/*    16ce0:	e49a0000 */ 	swc1	$f26,0x0($a0)
/*    16ce4:	e48e0010 */ 	swc1	$f14,0x10($a0)
/*    16ce8:	e4940020 */ 	swc1	$f20,0x20($a0)
/*    16cec:	c7a8004c */ 	lwc1	$f8,0x4c($sp)
/*    16cf0:	e49c0004 */ 	swc1	$f28,0x4($a0)
/*    16cf4:	e48c0014 */ 	swc1	$f12,0x14($a0)
/*    16cf8:	e4960024 */ 	swc1	$f22,0x24($a0)
/*    16cfc:	e4880030 */ 	swc1	$f8,0x30($a0)
/*    16d00:	c7aa0050 */ 	lwc1	$f10,0x50($sp)
/*    16d04:	e49e0008 */ 	swc1	$f30,0x8($a0)
/*    16d08:	44814000 */ 	mtc1	$at,$f8
/*    16d0c:	e48a0034 */ 	swc1	$f10,0x34($a0)
/*    16d10:	c7a4006c */ 	lwc1	$f4,0x6c($sp)
/*    16d14:	e4980028 */ 	swc1	$f24,0x28($a0)
/*    16d18:	e4840018 */ 	swc1	$f4,0x18($a0)
/*    16d1c:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*    16d20:	e480000c */ 	swc1	$f0,0xc($a0)
/*    16d24:	e480001c */ 	swc1	$f0,0x1c($a0)
/*    16d28:	e480002c */ 	swc1	$f0,0x2c($a0)
/*    16d2c:	e488003c */ 	swc1	$f8,0x3c($a0)
/*    16d30:	e4860038 */ 	swc1	$f6,0x38($a0)
/*    16d34:	8fbf0044 */ 	lw	$ra,0x44($sp)
/*    16d38:	d7be0038 */ 	ldc1	$f30,0x38($sp)
/*    16d3c:	d7bc0030 */ 	ldc1	$f28,0x30($sp)
/*    16d40:	d7ba0028 */ 	ldc1	$f26,0x28($sp)
/*    16d44:	d7b80020 */ 	ldc1	$f24,0x20($sp)
/*    16d48:	d7b60018 */ 	ldc1	$f22,0x18($sp)
/*    16d4c:	d7b40010 */ 	ldc1	$f20,0x10($sp)
/*    16d50:	03e00008 */ 	jr	$ra
/*    16d54:	27bd0048 */ 	addiu	$sp,$sp,0x48
);

void mtx00016d58(Mtxf *matrix, f32 posx, f32 posy, f32 posz, f32 lookx, f32 looky, f32 lookz, f32 upx, f32 upy, f32 upz)
{
	mtx00016b58(matrix, posx, posy, posz, lookx - posx, looky - posy, lookz - posz, upx, upy, upz);
}

u32 mtx00016dcc(f32 arg0, f32 arg1)
{
	f32 sum = arg0 + arg1;
	u16 result;

	if (sum <= 2) {
		result = 0xffff;
	} else {
		result = 0x20000 / sum;

		if (result <= 0) {
			result = 1;
		}
	}

	return result;
}

GLOBAL_ASM(
glabel mtx00016e98
/*    16e98:	27bdffb8 */ 	addiu	$sp,$sp,-72
/*    16e9c:	afb00020 */ 	sw	$s0,0x20($sp)
/*    16ea0:	f7b40018 */ 	sdc1	$f20,0x18($sp)
/*    16ea4:	4485a000 */ 	mtc1	$a1,$f20
/*    16ea8:	00808025 */ 	or	$s0,$a0,$zero
/*    16eac:	afbf0024 */ 	sw	$ra,0x24($sp)
/*    16eb0:	afa60050 */ 	sw	$a2,0x50($sp)
/*    16eb4:	afa70054 */ 	sw	$a3,0x54($sp)
/*    16eb8:	27a60058 */ 	addiu	$a2,$sp,0x58
/*    16ebc:	27a40050 */ 	addiu	$a0,$sp,0x50
/*    16ec0:	0c0011e4 */ 	jal	guNormalize
/*    16ec4:	27a50054 */ 	addiu	$a1,$sp,0x54
/*    16ec8:	0c0068f7 */ 	jal	sinf
/*    16ecc:	4600a306 */ 	mov.s	$f12,$f20
/*    16ed0:	e7a00044 */ 	swc1	$f0,0x44($sp)
/*    16ed4:	0c0068f4 */ 	jal	cosf
/*    16ed8:	4600a306 */ 	mov.s	$f12,$f20
/*    16edc:	c7a20050 */ 	lwc1	$f2,0x50($sp)
/*    16ee0:	c7ae0058 */ 	lwc1	$f14,0x58($sp)
/*    16ee4:	e7a00040 */ 	swc1	$f0,0x40($sp)
/*    16ee8:	46021102 */ 	mul.s	$f4,$f2,$f2
/*    16eec:	00000000 */ 	nop
/*    16ef0:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*    16ef4:	0c012974 */ 	jal	sqrtf
/*    16ef8:	46062300 */ 	add.s	$f12,$f4,$f6
/*    16efc:	4480a000 */ 	mtc1	$zero,$f20
/*    16f00:	c7a80050 */ 	lwc1	$f8,0x50($sp)
/*    16f04:	c7aa0040 */ 	lwc1	$f10,0x40($sp)
/*    16f08:	46140032 */ 	c.eq.s	$f0,$f20
/*    16f0c:	c7a40044 */ 	lwc1	$f4,0x44($sp)
/*    16f10:	4501003e */ 	bc1t	.L0001700c
/*    16f14:	00000000 */ 	nop
/*    16f18:	460a4302 */ 	mul.s	$f12,$f8,$f10
/*    16f1c:	3c013f80 */ 	lui	$at,0x3f80
/*    16f20:	c7a60058 */ 	lwc1	$f6,0x58($sp)
/*    16f24:	46044382 */ 	mul.s	$f14,$f8,$f4
/*    16f28:	44814000 */ 	mtc1	$at,$f8
/*    16f2c:	460a3402 */ 	mul.s	$f16,$f6,$f10
/*    16f30:	00000000 */ 	nop
/*    16f34:	46043482 */ 	mul.s	$f18,$f6,$f4
/*    16f38:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*    16f3c:	e7ae0030 */ 	swc1	$f14,0x30($sp)
/*    16f40:	460e3102 */ 	mul.s	$f4,$f6,$f14
/*    16f44:	e7b0002c */ 	swc1	$f16,0x2c($sp)
/*    16f48:	46008287 */ 	neg.s	$f10,$f16
/*    16f4c:	46004083 */ 	div.s	$f2,$f8,$f0
/*    16f50:	46045201 */ 	sub.s	$f8,$f10,$f4
/*    16f54:	46024182 */ 	mul.s	$f6,$f8,$f2
/*    16f58:	e7a20038 */ 	swc1	$f2,0x38($sp)
/*    16f5c:	e6060000 */ 	swc1	$f6,0x0($s0)
/*    16f60:	c7aa0044 */ 	lwc1	$f10,0x44($sp)
/*    16f64:	46005102 */ 	mul.s	$f4,$f10,$f0
/*    16f68:	e6040010 */ 	swc1	$f4,0x10($s0)
/*    16f6c:	c7a80054 */ 	lwc1	$f8,0x54($sp)
/*    16f70:	e6140030 */ 	swc1	$f20,0x30($s0)
/*    16f74:	46124182 */ 	mul.s	$f6,$f8,$f18
/*    16f78:	46066281 */ 	sub.s	$f10,$f12,$f6
/*    16f7c:	46025102 */ 	mul.s	$f4,$f10,$f2
/*    16f80:	e6040020 */ 	swc1	$f4,0x20($s0)
/*    16f84:	c7a80054 */ 	lwc1	$f8,0x54($sp)
/*    16f88:	460c4182 */ 	mul.s	$f6,$f8,$f12
/*    16f8c:	46069281 */ 	sub.s	$f10,$f18,$f6
/*    16f90:	46025102 */ 	mul.s	$f4,$f10,$f2
/*    16f94:	e6040004 */ 	swc1	$f4,0x4($s0)
/*    16f98:	c7a80040 */ 	lwc1	$f8,0x40($sp)
/*    16f9c:	46004182 */ 	mul.s	$f6,$f8,$f0
/*    16fa0:	e6060014 */ 	swc1	$f6,0x14($s0)
/*    16fa4:	c7aa0054 */ 	lwc1	$f10,0x54($sp)
/*    16fa8:	c7a4002c */ 	lwc1	$f4,0x2c($sp)
/*    16fac:	c7a60030 */ 	lwc1	$f6,0x30($sp)
/*    16fb0:	46045202 */ 	mul.s	$f8,$f10,$f4
/*    16fb4:	46003287 */ 	neg.s	$f10,$f6
/*    16fb8:	c7a60038 */ 	lwc1	$f6,0x38($sp)
/*    16fbc:	e6140034 */ 	swc1	$f20,0x34($s0)
/*    16fc0:	46085101 */ 	sub.s	$f4,$f10,$f8
/*    16fc4:	46062282 */ 	mul.s	$f10,$f4,$f6
/*    16fc8:	e60a0024 */ 	swc1	$f10,0x24($s0)
/*    16fcc:	c7a80050 */ 	lwc1	$f8,0x50($sp)
/*    16fd0:	46004107 */ 	neg.s	$f4,$f8
/*    16fd4:	e6040008 */ 	swc1	$f4,0x8($s0)
/*    16fd8:	c7a60054 */ 	lwc1	$f6,0x54($sp)
/*    16fdc:	46003287 */ 	neg.s	$f10,$f6
/*    16fe0:	44813000 */ 	mtc1	$at,$f6
/*    16fe4:	e60a0018 */ 	swc1	$f10,0x18($s0)
/*    16fe8:	c7a80058 */ 	lwc1	$f8,0x58($sp)
/*    16fec:	e6140038 */ 	swc1	$f20,0x38($s0)
/*    16ff0:	e614000c */ 	swc1	$f20,0xc($s0)
/*    16ff4:	46004107 */ 	neg.s	$f4,$f8
/*    16ff8:	e614001c */ 	swc1	$f20,0x1c($s0)
/*    16ffc:	e6040028 */ 	swc1	$f4,0x28($s0)
/*    17000:	e614002c */ 	swc1	$f20,0x2c($s0)
/*    17004:	10000003 */ 	b	.L00017014
/*    17008:	e606003c */ 	swc1	$f6,0x3c($s0)
.L0001700c:
/*    1700c:	0c00566c */ 	jal	mtx4LoadIdentity
/*    17010:	02002025 */ 	or	$a0,$s0,$zero
.L00017014:
/*    17014:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*    17018:	d7b40018 */ 	ldc1	$f20,0x18($sp)
/*    1701c:	8fb00020 */ 	lw	$s0,0x20($sp)
/*    17020:	03e00008 */ 	jr	$ra
/*    17024:	27bd0048 */ 	addiu	$sp,$sp,0x48
);

void mtx4Align(f32 mtx[4][4], f32 angle, f32 x, f32 y, f32 z)
{
	angle = RAD2DEG(angle);
	guAlignF(mtx, angle, x, y, z);
}

#if VERSION < VERSION_NTSC_1_0
void mtx4Print(f32 mtx[4][4])
{
	s32 i;
	s32 j;

	for (i = 0; i < 4; i++) {
		rmonPrintf("(");

		for (j = 0; j < 4; j++) {
			rmonPrintf("%s%s %9f", "", "", mtx[i][j]);
		}

		rmonPrintf(" )\n");
	}
}
#endif

void mtx4LoadRotationFrom(f32 src[4][4], f32 dst[4][4])
{
	dst[0][0] = src[0][0];
	dst[0][1] = src[1][0];
	dst[0][2] = src[2][0];

	dst[1][0] = src[0][1];
	dst[1][1] = src[1][1];
	dst[1][2] = src[2][1];

	dst[2][0] = src[0][2];
	dst[2][1] = src[1][2];
	dst[2][2] = src[2][2];

	dst[3][0] = 0;
	dst[3][1] = 0;
	dst[3][2] = 0;

	dst[0][3] = 0;
	dst[1][3] = 0;
	dst[2][3] = 0;
	dst[3][3] = 1;
}

GLOBAL_ASM(
glabel mtx000170e4
/*    170e4:	c48c0000 */ 	lwc1	$f12,0x0($a0)
/*    170e8:	c48e0010 */ 	lwc1	$f14,0x10($a0)
/*    170ec:	c4820020 */ 	lwc1	$f2,0x20($a0)
/*    170f0:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*    170f4:	3c013f80 */ 	lui	$at,0x3f80
/*    170f8:	44818000 */ 	mtc1	$at,$f16
/*    170fc:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*    17100:	46062200 */ 	add.s	$f8,$f4,$f6
/*    17104:	46021282 */ 	mul.s	$f10,$f2,$f2
/*    17108:	44801000 */ 	mtc1	$zero,$f2
/*    1710c:	46085000 */ 	add.s	$f0,$f10,$f8
/*    17110:	46008003 */ 	div.s	$f0,$f16,$f0
/*    17114:	46006482 */ 	mul.s	$f18,$f12,$f0
/*    17118:	e4b20000 */ 	swc1	$f18,0x0($a1)
/*    1711c:	c4840010 */ 	lwc1	$f4,0x10($a0)
/*    17120:	46002182 */ 	mul.s	$f6,$f4,$f0
/*    17124:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*    17128:	c48a0020 */ 	lwc1	$f10,0x20($a0)
/*    1712c:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    17130:	e4a80008 */ 	swc1	$f8,0x8($a1)
/*    17134:	c4920004 */ 	lwc1	$f18,0x4($a0)
/*    17138:	46009102 */ 	mul.s	$f4,$f18,$f0
/*    1713c:	e4a40010 */ 	swc1	$f4,0x10($a1)
/*    17140:	c4860014 */ 	lwc1	$f6,0x14($a0)
/*    17144:	46003282 */ 	mul.s	$f10,$f6,$f0
/*    17148:	e4aa0014 */ 	swc1	$f10,0x14($a1)
/*    1714c:	c4880024 */ 	lwc1	$f8,0x24($a0)
/*    17150:	46004482 */ 	mul.s	$f18,$f8,$f0
/*    17154:	e4b20018 */ 	swc1	$f18,0x18($a1)
/*    17158:	c4840008 */ 	lwc1	$f4,0x8($a0)
/*    1715c:	46002182 */ 	mul.s	$f6,$f4,$f0
/*    17160:	e4a60020 */ 	swc1	$f6,0x20($a1)
/*    17164:	c48a0018 */ 	lwc1	$f10,0x18($a0)
/*    17168:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    1716c:	e4a80024 */ 	swc1	$f8,0x24($a1)
/*    17170:	c4920028 */ 	lwc1	$f18,0x28($a0)
/*    17174:	e4b0003c */ 	swc1	$f16,0x3c($a1)
/*    17178:	e4a20030 */ 	swc1	$f2,0x30($a1)
/*    1717c:	46009102 */ 	mul.s	$f4,$f18,$f0
/*    17180:	e4a20034 */ 	swc1	$f2,0x34($a1)
/*    17184:	e4a20038 */ 	swc1	$f2,0x38($a1)
/*    17188:	e4a2000c */ 	swc1	$f2,0xc($a1)
/*    1718c:	e4a2001c */ 	swc1	$f2,0x1c($a1)
/*    17190:	e4a2002c */ 	swc1	$f2,0x2c($a1)
/*    17194:	03e00008 */ 	jr	$ra
/*    17198:	e4a40028 */ 	swc1	$f4,0x28($a1)
);

GLOBAL_ASM(
glabel mtx0001719c
/*    1719c:	c48c0000 */ 	lwc1	$f12,0x0($a0)
/*    171a0:	c48e0010 */ 	lwc1	$f14,0x10($a0)
/*    171a4:	c4820020 */ 	lwc1	$f2,0x20($a0)
/*    171a8:	460c6102 */ 	mul.s	$f4,$f12,$f12
/*    171ac:	3c013f80 */ 	lui	$at,0x3f80
/*    171b0:	44818000 */ 	mtc1	$at,$f16
/*    171b4:	460e7182 */ 	mul.s	$f6,$f14,$f14
/*    171b8:	46062200 */ 	add.s	$f8,$f4,$f6
/*    171bc:	46021282 */ 	mul.s	$f10,$f2,$f2
/*    171c0:	46085000 */ 	add.s	$f0,$f10,$f8
/*    171c4:	46008003 */ 	div.s	$f0,$f16,$f0
/*    171c8:	46006482 */ 	mul.s	$f18,$f12,$f0
/*    171cc:	e4b20000 */ 	swc1	$f18,0x0($a1)
/*    171d0:	c4840010 */ 	lwc1	$f4,0x10($a0)
/*    171d4:	46002182 */ 	mul.s	$f6,$f4,$f0
/*    171d8:	e4a60004 */ 	swc1	$f6,0x4($a1)
/*    171dc:	c48a0020 */ 	lwc1	$f10,0x20($a0)
/*    171e0:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    171e4:	e4a80008 */ 	swc1	$f8,0x8($a1)
/*    171e8:	c4920004 */ 	lwc1	$f18,0x4($a0)
/*    171ec:	46009102 */ 	mul.s	$f4,$f18,$f0
/*    171f0:	e4a40010 */ 	swc1	$f4,0x10($a1)
/*    171f4:	c4860014 */ 	lwc1	$f6,0x14($a0)
/*    171f8:	46003282 */ 	mul.s	$f10,$f6,$f0
/*    171fc:	e4aa0014 */ 	swc1	$f10,0x14($a1)
/*    17200:	c4880024 */ 	lwc1	$f8,0x24($a0)
/*    17204:	46004482 */ 	mul.s	$f18,$f8,$f0
/*    17208:	e4b20018 */ 	swc1	$f18,0x18($a1)
/*    1720c:	c4840008 */ 	lwc1	$f4,0x8($a0)
/*    17210:	46002182 */ 	mul.s	$f6,$f4,$f0
/*    17214:	e4a60020 */ 	swc1	$f6,0x20($a1)
/*    17218:	c48a0018 */ 	lwc1	$f10,0x18($a0)
/*    1721c:	c4a60000 */ 	lwc1	$f6,0x0($a1)
/*    17220:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    17224:	e4a80024 */ 	swc1	$f8,0x24($a1)
/*    17228:	c4920028 */ 	lwc1	$f18,0x28($a0)
/*    1722c:	46009102 */ 	mul.s	$f4,$f18,$f0
/*    17230:	c4b20010 */ 	lwc1	$f18,0x10($a1)
/*    17234:	44800000 */ 	mtc1	$zero,$f0
/*    17238:	e4a40028 */ 	swc1	$f4,0x28($a1)
/*    1723c:	c48a0030 */ 	lwc1	$f10,0x30($a0)
/*    17240:	c4840034 */ 	lwc1	$f4,0x34($a0)
/*    17244:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*    17248:	00000000 */ 	nop
/*    1724c:	46049182 */ 	mul.s	$f6,$f18,$f4
/*    17250:	c4a40020 */ 	lwc1	$f4,0x20($a1)
/*    17254:	c4920038 */ 	lwc1	$f18,0x38($a0)
/*    17258:	46064280 */ 	add.s	$f10,$f8,$f6
/*    1725c:	46049202 */ 	mul.s	$f8,$f18,$f4
/*    17260:	c4a40004 */ 	lwc1	$f4,0x4($a1)
/*    17264:	460a4180 */ 	add.s	$f6,$f8,$f10
/*    17268:	46003487 */ 	neg.s	$f18,$f6
/*    1726c:	c4a60014 */ 	lwc1	$f6,0x14($a1)
/*    17270:	e4b20030 */ 	swc1	$f18,0x30($a1)
/*    17274:	c4880030 */ 	lwc1	$f8,0x30($a0)
/*    17278:	c4920034 */ 	lwc1	$f18,0x34($a0)
/*    1727c:	46082282 */ 	mul.s	$f10,$f4,$f8
/*    17280:	00000000 */ 	nop
/*    17284:	46123102 */ 	mul.s	$f4,$f6,$f18
/*    17288:	c4b20024 */ 	lwc1	$f18,0x24($a1)
/*    1728c:	c4860038 */ 	lwc1	$f6,0x38($a0)
/*    17290:	46045200 */ 	add.s	$f8,$f10,$f4
/*    17294:	46123282 */ 	mul.s	$f10,$f6,$f18
/*    17298:	c4b20008 */ 	lwc1	$f18,0x8($a1)
/*    1729c:	46085100 */ 	add.s	$f4,$f10,$f8
/*    172a0:	46002187 */ 	neg.s	$f6,$f4
/*    172a4:	c4a40018 */ 	lwc1	$f4,0x18($a1)
/*    172a8:	e4a60034 */ 	swc1	$f6,0x34($a1)
/*    172ac:	c48a0030 */ 	lwc1	$f10,0x30($a0)
/*    172b0:	c4860034 */ 	lwc1	$f6,0x34($a0)
/*    172b4:	460a9202 */ 	mul.s	$f8,$f18,$f10
/*    172b8:	00000000 */ 	nop
/*    172bc:	46062482 */ 	mul.s	$f18,$f4,$f6
/*    172c0:	c4a60028 */ 	lwc1	$f6,0x28($a1)
/*    172c4:	c4840038 */ 	lwc1	$f4,0x38($a0)
/*    172c8:	e4b0003c */ 	swc1	$f16,0x3c($a1)
/*    172cc:	e4a0000c */ 	swc1	$f0,0xc($a1)
/*    172d0:	e4a0001c */ 	swc1	$f0,0x1c($a1)
/*    172d4:	e4a0002c */ 	swc1	$f0,0x2c($a1)
/*    172d8:	46124280 */ 	add.s	$f10,$f8,$f18
/*    172dc:	46062202 */ 	mul.s	$f8,$f4,$f6
/*    172e0:	460a4480 */ 	add.s	$f18,$f8,$f10
/*    172e4:	46009107 */ 	neg.s	$f4,$f18
/*    172e8:	03e00008 */ 	jr	$ra
/*    172ec:	e4a40038 */ 	swc1	$f4,0x38($a1)
);

GLOBAL_ASM(
glabel mtx000172f0
/*    172f0:	c4820000 */ 	lwc1	$f2,0x0($a0)
/*    172f4:	c48c0014 */ 	lwc1	$f12,0x14($a0)
/*    172f8:	c48e0028 */ 	lwc1	$f14,0x28($a0)
/*    172fc:	c4900004 */ 	lwc1	$f16,0x4($a0)
/*    17300:	460c1102 */ 	mul.s	$f4,$f2,$f12
/*    17304:	c4920018 */ 	lwc1	$f18,0x18($a0)
/*    17308:	c48a0020 */ 	lwc1	$f10,0x20($a0)
/*    1730c:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*    17310:	3c013f80 */ 	lui	$at,0x3f80
/*    17314:	e7aa0010 */ 	swc1	$f10,0x10($sp)
/*    17318:	c7a80010 */ 	lwc1	$f8,0x10($sp)
/*    1731c:	460e2002 */ 	mul.s	$f0,$f4,$f14
/*    17320:	c48a0008 */ 	lwc1	$f10,0x8($a0)
/*    17324:	46128182 */ 	mul.s	$f6,$f16,$f18
/*    17328:	e7aa000c */ 	swc1	$f10,0xc($sp)
/*    1732c:	c7aa000c */ 	lwc1	$f10,0xc($sp)
/*    17330:	46083102 */ 	mul.s	$f4,$f6,$f8
/*    17334:	c4860010 */ 	lwc1	$f6,0x10($a0)
/*    17338:	e7a60008 */ 	swc1	$f6,0x8($sp)
/*    1733c:	c7a60008 */ 	lwc1	$f6,0x8($sp)
/*    17340:	46040000 */ 	add.s	$f0,$f0,$f4
/*    17344:	c4840024 */ 	lwc1	$f4,0x24($a0)
/*    17348:	e7a80000 */ 	swc1	$f8,0x0($sp)
/*    1734c:	e7a4001c */ 	swc1	$f4,0x1c($sp)
/*    17350:	46065102 */ 	mul.s	$f4,$f10,$f6
/*    17354:	c7a8001c */ 	lwc1	$f8,0x1c($sp)
/*    17358:	46082102 */ 	mul.s	$f4,$f4,$f8
/*    1735c:	46040000 */ 	add.s	$f0,$f0,$f4
/*    17360:	460c5102 */ 	mul.s	$f4,$f10,$f12
/*    17364:	c7aa0000 */ 	lwc1	$f10,0x0($sp)
/*    17368:	460a2102 */ 	mul.s	$f4,$f4,$f10
/*    1736c:	00000000 */ 	nop
/*    17370:	46068282 */ 	mul.s	$f10,$f16,$f6
/*    17374:	46040001 */ 	sub.s	$f0,$f0,$f4
/*    17378:	460e5102 */ 	mul.s	$f4,$f10,$f14
/*    1737c:	00000000 */ 	nop
/*    17380:	46121182 */ 	mul.s	$f6,$f2,$f18
/*    17384:	44811000 */ 	mtc1	$at,$f2
/*    17388:	46040001 */ 	sub.s	$f0,$f0,$f4
/*    1738c:	46083282 */ 	mul.s	$f10,$f6,$f8
/*    17390:	460a0001 */ 	sub.s	$f0,$f0,$f10
/*    17394:	460e6102 */ 	mul.s	$f4,$f12,$f14
/*    17398:	00000000 */ 	nop
/*    1739c:	46124182 */ 	mul.s	$f6,$f8,$f18
/*    173a0:	46001003 */ 	div.s	$f0,$f2,$f0
/*    173a4:	46062281 */ 	sub.s	$f10,$f4,$f6
/*    173a8:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    173ac:	e4a80000 */ 	swc1	$f8,0x0($a1)
/*    173b0:	c4840018 */ 	lwc1	$f4,0x18($a0)
/*    173b4:	c4860020 */ 	lwc1	$f6,0x20($a0)
/*    173b8:	c4880028 */ 	lwc1	$f8,0x28($a0)
/*    173bc:	46062282 */ 	mul.s	$f10,$f4,$f6
/*    173c0:	c4840010 */ 	lwc1	$f4,0x10($a0)
/*    173c4:	46044182 */ 	mul.s	$f6,$f8,$f4
/*    173c8:	46065201 */ 	sub.s	$f8,$f10,$f6
/*    173cc:	46004102 */ 	mul.s	$f4,$f8,$f0
/*    173d0:	e4a40010 */ 	swc1	$f4,0x10($a1)
/*    173d4:	c48a0010 */ 	lwc1	$f10,0x10($a0)
/*    173d8:	c4860024 */ 	lwc1	$f6,0x24($a0)
/*    173dc:	c4840020 */ 	lwc1	$f4,0x20($a0)
/*    173e0:	46065202 */ 	mul.s	$f8,$f10,$f6
/*    173e4:	c48a0014 */ 	lwc1	$f10,0x14($a0)
/*    173e8:	460a2182 */ 	mul.s	$f6,$f4,$f10
/*    173ec:	46064101 */ 	sub.s	$f4,$f8,$f6
/*    173f0:	46002282 */ 	mul.s	$f10,$f4,$f0
/*    173f4:	e4aa0020 */ 	swc1	$f10,0x20($a1)
/*    173f8:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    173fc:	c4860024 */ 	lwc1	$f6,0x24($a0)
/*    17400:	c48a0028 */ 	lwc1	$f10,0x28($a0)
/*    17404:	46064102 */ 	mul.s	$f4,$f8,$f6
/*    17408:	c4880004 */ 	lwc1	$f8,0x4($a0)
/*    1740c:	46085182 */ 	mul.s	$f6,$f10,$f8
/*    17410:	46062281 */ 	sub.s	$f10,$f4,$f6
/*    17414:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    17418:	e4a80004 */ 	swc1	$f8,0x4($a1)
/*    1741c:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    17420:	c4860028 */ 	lwc1	$f6,0x28($a0)
/*    17424:	c4880020 */ 	lwc1	$f8,0x20($a0)
/*    17428:	46062282 */ 	mul.s	$f10,$f4,$f6
/*    1742c:	c4840008 */ 	lwc1	$f4,0x8($a0)
/*    17430:	46044182 */ 	mul.s	$f6,$f8,$f4
/*    17434:	46065201 */ 	sub.s	$f8,$f10,$f6
/*    17438:	46004102 */ 	mul.s	$f4,$f8,$f0
/*    1743c:	e4a40014 */ 	swc1	$f4,0x14($a1)
/*    17440:	c48a0004 */ 	lwc1	$f10,0x4($a0)
/*    17444:	c4860020 */ 	lwc1	$f6,0x20($a0)
/*    17448:	c4840024 */ 	lwc1	$f4,0x24($a0)
/*    1744c:	46065202 */ 	mul.s	$f8,$f10,$f6
/*    17450:	c48a0000 */ 	lwc1	$f10,0x0($a0)
/*    17454:	460a2182 */ 	mul.s	$f6,$f4,$f10
/*    17458:	46064101 */ 	sub.s	$f4,$f8,$f6
/*    1745c:	46002282 */ 	mul.s	$f10,$f4,$f0
/*    17460:	e4aa0024 */ 	swc1	$f10,0x24($a1)
/*    17464:	c4880004 */ 	lwc1	$f8,0x4($a0)
/*    17468:	c4860018 */ 	lwc1	$f6,0x18($a0)
/*    1746c:	c48a0014 */ 	lwc1	$f10,0x14($a0)
/*    17470:	46064102 */ 	mul.s	$f4,$f8,$f6
/*    17474:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    17478:	46085182 */ 	mul.s	$f6,$f10,$f8
/*    1747c:	46062281 */ 	sub.s	$f10,$f4,$f6
/*    17480:	46005202 */ 	mul.s	$f8,$f10,$f0
/*    17484:	e4a80008 */ 	swc1	$f8,0x8($a1)
/*    17488:	c4860010 */ 	lwc1	$f6,0x10($a0)
/*    1748c:	c4840008 */ 	lwc1	$f4,0x8($a0)
/*    17490:	c4880018 */ 	lwc1	$f8,0x18($a0)
/*    17494:	46062282 */ 	mul.s	$f10,$f4,$f6
/*    17498:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    1749c:	46044182 */ 	mul.s	$f6,$f8,$f4
/*    174a0:	46065201 */ 	sub.s	$f8,$f10,$f6
/*    174a4:	46004102 */ 	mul.s	$f4,$f8,$f0
/*    174a8:	e4a40018 */ 	swc1	$f4,0x18($a1)
/*    174ac:	c4860014 */ 	lwc1	$f6,0x14($a0)
/*    174b0:	c48a0000 */ 	lwc1	$f10,0x0($a0)
/*    174b4:	c4840010 */ 	lwc1	$f4,0x10($a0)
/*    174b8:	46065202 */ 	mul.s	$f8,$f10,$f6
/*    174bc:	c48a0004 */ 	lwc1	$f10,0x4($a0)
/*    174c0:	460a2182 */ 	mul.s	$f6,$f4,$f10
/*    174c4:	46064101 */ 	sub.s	$f4,$f8,$f6
/*    174c8:	c4a60000 */ 	lwc1	$f6,0x0($a1)
/*    174cc:	46002282 */ 	mul.s	$f10,$f4,$f0
/*    174d0:	44800000 */ 	mtc1	$zero,$f0
/*    174d4:	e4aa0028 */ 	swc1	$f10,0x28($a1)
/*    174d8:	c4880030 */ 	lwc1	$f8,0x30($a0)
/*    174dc:	c48a0034 */ 	lwc1	$f10,0x34($a0)
/*    174e0:	46064102 */ 	mul.s	$f4,$f8,$f6
/*    174e4:	c4a80010 */ 	lwc1	$f8,0x10($a1)
/*    174e8:	46085182 */ 	mul.s	$f6,$f10,$f8
/*    174ec:	c4a80020 */ 	lwc1	$f8,0x20($a1)
/*    174f0:	46062280 */ 	add.s	$f10,$f4,$f6
/*    174f4:	c4840038 */ 	lwc1	$f4,0x38($a0)
/*    174f8:	46044182 */ 	mul.s	$f6,$f8,$f4
/*    174fc:	460a3200 */ 	add.s	$f8,$f6,$f10
/*    17500:	c4aa0004 */ 	lwc1	$f10,0x4($a1)
/*    17504:	46004107 */ 	neg.s	$f4,$f8
/*    17508:	e4a40030 */ 	swc1	$f4,0x30($a1)
/*    1750c:	c4860030 */ 	lwc1	$f6,0x30($a0)
/*    17510:	c4840034 */ 	lwc1	$f4,0x34($a0)
/*    17514:	460a3202 */ 	mul.s	$f8,$f6,$f10
/*    17518:	c4a60014 */ 	lwc1	$f6,0x14($a1)
/*    1751c:	46062282 */ 	mul.s	$f10,$f4,$f6
/*    17520:	c4a60024 */ 	lwc1	$f6,0x24($a1)
/*    17524:	460a4100 */ 	add.s	$f4,$f8,$f10
/*    17528:	c4880038 */ 	lwc1	$f8,0x38($a0)
/*    1752c:	46083282 */ 	mul.s	$f10,$f6,$f8
/*    17530:	46045180 */ 	add.s	$f6,$f10,$f4
/*    17534:	c4a40008 */ 	lwc1	$f4,0x8($a1)
/*    17538:	46003207 */ 	neg.s	$f8,$f6
/*    1753c:	e4a80034 */ 	swc1	$f8,0x34($a1)
/*    17540:	c48a0030 */ 	lwc1	$f10,0x30($a0)
/*    17544:	c4880034 */ 	lwc1	$f8,0x34($a0)
/*    17548:	46045182 */ 	mul.s	$f6,$f10,$f4
/*    1754c:	c4aa0018 */ 	lwc1	$f10,0x18($a1)
/*    17550:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*    17554:	c4aa0028 */ 	lwc1	$f10,0x28($a1)
/*    17558:	46043200 */ 	add.s	$f8,$f6,$f4
/*    1755c:	c4860038 */ 	lwc1	$f6,0x38($a0)
/*    17560:	27bd0030 */ 	addiu	$sp,$sp,0x30
/*    17564:	e4a2003c */ 	swc1	$f2,0x3c($a1)
/*    17568:	46065102 */ 	mul.s	$f4,$f10,$f6
/*    1756c:	e4a0000c */ 	swc1	$f0,0xc($a1)
/*    17570:	e4a0001c */ 	swc1	$f0,0x1c($a1)
/*    17574:	e4a0002c */ 	swc1	$f0,0x2c($a1)
/*    17578:	46082280 */ 	add.s	$f10,$f4,$f8
/*    1757c:	46005187 */ 	neg.s	$f6,$f10
/*    17580:	03e00008 */ 	jr	$ra
/*    17584:	e4a60038 */ 	swc1	$f6,0x38($a1)
);

GLOBAL_ASM(
glabel mtx00017588
/*    17588:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*    1758c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*    17590:	afa40018 */ 	sw	$a0,0x18($sp)
/*    17594:	0c005d85 */ 	jal	mtx00017614
/*    17598:	afa5001c */ 	sw	$a1,0x1c($sp)
/*    1759c:	0c005e9e */ 	jal	mtx00017a78
/*    175a0:	8fa40018 */ 	lw	$a0,0x18($sp)
/*    175a4:	3c013f80 */ 	lui	$at,0x3f80
/*    175a8:	44812000 */ 	mtc1	$at,$f4
/*    175ac:	00002825 */ 	or	$a1,$zero,$zero
/*    175b0:	8fa6001c */ 	lw	$a2,0x1c($sp)
/*    175b4:	24040004 */ 	addiu	$a0,$zero,0x4
/*    175b8:	46002083 */ 	div.s	$f2,$f4,$f0
.L000175bc:
/*    175bc:	00001825 */ 	or	$v1,$zero,$zero
/*    175c0:	00c01025 */ 	or	$v0,$a2,$zero
/*    175c4:	c4500000 */ 	lwc1	$f16,0x0($v0)
/*    175c8:	24630001 */ 	addiu	$v1,$v1,0x1
/*    175cc:	46028482 */ 	mul.s	$f18,$f16,$f2
/*    175d0:	50640008 */ 	beql	$v1,$a0,.L000175f4
/*    175d4:	24420004 */ 	addiu	$v0,$v0,0x4
.L000175d8:
/*    175d8:	c4500004 */ 	lwc1	$f16,0x4($v0)
/*    175dc:	24630001 */ 	addiu	$v1,$v1,0x1
/*    175e0:	e4520000 */ 	swc1	$f18,0x0($v0)
/*    175e4:	46028482 */ 	mul.s	$f18,$f16,$f2
/*    175e8:	1464fffb */ 	bne	$v1,$a0,.L000175d8
/*    175ec:	24420004 */ 	addiu	$v0,$v0,0x4
/*    175f0:	24420004 */ 	addiu	$v0,$v0,0x4
.L000175f4:
/*    175f4:	e452fffc */ 	swc1	$f18,-0x4($v0)
/*    175f8:	24a50001 */ 	addiu	$a1,$a1,0x1
/*    175fc:	14a4ffef */ 	bne	$a1,$a0,.L000175bc
/*    17600:	24c60010 */ 	addiu	$a2,$a2,0x10
/*    17604:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*    17608:	27bd0018 */ 	addiu	$sp,$sp,0x18
/*    1760c:	03e00008 */ 	jr	$ra
/*    17610:	00000000 */ 	nop
);

void mtx00017614(f32 arg0[4][4], f32 arg1[4][4])
{
	f32 mtx00, mtx10, mtx20, mtx30;
	f32 mtx04, mtx14, mtx24, mtx34;
	f32 mtx08, mtx18, mtx28, mtx38;
	f32 mtx0c, mtx1c, mtx2c, mtx3c;

	mtx00 = arg0[0][0]; mtx04 = arg0[0][1];
	mtx08 = arg0[0][2]; mtx0c = arg0[0][3];
	mtx10 = arg0[1][0]; mtx14 = arg0[1][1];
	mtx18 = arg0[1][2]; mtx1c = arg0[1][3];
	mtx20 = arg0[2][0]; mtx24 = arg0[2][1];
	mtx28 = arg0[2][2]; mtx2c = arg0[2][3];
	mtx30 = arg0[3][0]; mtx34 = arg0[3][1];
	mtx38 = arg0[3][2]; mtx3c = arg0[3][3];

	arg1[0][0] =  mtx00017c2c(mtx14, mtx24, mtx34, mtx18, mtx28, mtx38, mtx1c, mtx2c, mtx3c);
	arg1[1][0] = -mtx00017c2c(mtx10, mtx20, mtx30, mtx18, mtx28, mtx38, mtx1c, mtx2c, mtx3c);
	arg1[2][0] =  mtx00017c2c(mtx10, mtx20, mtx30, mtx14, mtx24, mtx34, mtx1c, mtx2c, mtx3c);
	arg1[3][0] = -mtx00017c2c(mtx10, mtx20, mtx30, mtx14, mtx24, mtx34, mtx18, mtx28, mtx38);
	arg1[0][1] = -mtx00017c2c(mtx04, mtx24, mtx34, mtx08, mtx28, mtx38, mtx0c, mtx2c, mtx3c);
	arg1[1][1] =  mtx00017c2c(mtx00, mtx20, mtx30, mtx08, mtx28, mtx38, mtx0c, mtx2c, mtx3c);
	arg1[2][1] = -mtx00017c2c(mtx00, mtx20, mtx30, mtx04, mtx24, mtx34, mtx0c, mtx2c, mtx3c);
	arg1[3][1] =  mtx00017c2c(mtx00, mtx20, mtx30, mtx04, mtx24, mtx34, mtx08, mtx28, mtx38);
	arg1[0][2] =  mtx00017c2c(mtx04, mtx14, mtx34, mtx08, mtx18, mtx38, mtx0c, mtx1c, mtx3c);
	arg1[1][2] = -mtx00017c2c(mtx00, mtx10, mtx30, mtx08, mtx18, mtx38, mtx0c, mtx1c, mtx3c);
	arg1[2][2] =  mtx00017c2c(mtx00, mtx10, mtx30, mtx04, mtx14, mtx34, mtx0c, mtx1c, mtx3c);
	arg1[3][2] = -mtx00017c2c(mtx00, mtx10, mtx30, mtx04, mtx14, mtx34, mtx08, mtx18, mtx38);
	arg1[0][3] = -mtx00017c2c(mtx04, mtx14, mtx24, mtx08, mtx18, mtx28, mtx0c, mtx1c, mtx2c);
	arg1[1][3] =  mtx00017c2c(mtx00, mtx10, mtx20, mtx08, mtx18, mtx28, mtx0c, mtx1c, mtx2c);
	arg1[2][3] = -mtx00017c2c(mtx00, mtx10, mtx20, mtx04, mtx14, mtx24, mtx0c, mtx1c, mtx2c);
	arg1[3][3] =  mtx00017c2c(mtx00, mtx10, mtx20, mtx04, mtx14, mtx24, mtx08, mtx18, mtx28);
}

GLOBAL_ASM(
glabel mtx00017a78
/*    17a78:	27bdff80 */ 	addiu	$sp,$sp,-128
/*    17a7c:	afbf002c */ 	sw	$ra,0x2c($sp)
/*    17a80:	c4840000 */ 	lwc1	$f4,0x0($a0)
/*    17a84:	e7a40078 */ 	swc1	$f4,0x78($sp)
/*    17a88:	c4860004 */ 	lwc1	$f6,0x4($a0)
/*    17a8c:	e7a60068 */ 	swc1	$f6,0x68($sp)
/*    17a90:	c4880008 */ 	lwc1	$f8,0x8($a0)
/*    17a94:	e7a80058 */ 	swc1	$f8,0x58($sp)
/*    17a98:	c48a000c */ 	lwc1	$f10,0xc($a0)
/*    17a9c:	e7aa0048 */ 	swc1	$f10,0x48($sp)
/*    17aa0:	c4840018 */ 	lwc1	$f4,0x18($a0)
/*    17aa4:	c4800014 */ 	lwc1	$f0,0x14($a0)
/*    17aa8:	c48c0010 */ 	lwc1	$f12,0x10($a0)
/*    17aac:	e7a40054 */ 	swc1	$f4,0x54($sp)
/*    17ab0:	c4860028 */ 	lwc1	$f6,0x28($a0)
/*    17ab4:	c482001c */ 	lwc1	$f2,0x1c($a0)
/*    17ab8:	c4900024 */ 	lwc1	$f16,0x24($a0)
/*    17abc:	c48e0020 */ 	lwc1	$f14,0x20($a0)
/*    17ac0:	e7a60050 */ 	swc1	$f6,0x50($sp)
/*    17ac4:	c4880030 */ 	lwc1	$f8,0x30($a0)
/*    17ac8:	c492002c */ 	lwc1	$f18,0x2c($a0)
/*    17acc:	44070000 */ 	mfc1	$a3,$f0
/*    17ad0:	e7a8006c */ 	swc1	$f8,0x6c($sp)
/*    17ad4:	c48a0034 */ 	lwc1	$f10,0x34($a0)
/*    17ad8:	8fa6006c */ 	lw	$a2,0x6c($sp)
/*    17adc:	e7aa005c */ 	swc1	$f10,0x5c($sp)
/*    17ae0:	c4840038 */ 	lwc1	$f4,0x38($a0)
/*    17ae4:	c7a8005c */ 	lwc1	$f8,0x5c($sp)
/*    17ae8:	e7a4004c */ 	swc1	$f4,0x4c($sp)
/*    17aec:	c486003c */ 	lwc1	$f6,0x3c($a0)
/*    17af0:	e7a00064 */ 	swc1	$f0,0x64($sp)
/*    17af4:	e7ac0074 */ 	swc1	$f12,0x74($sp)
/*    17af8:	e7a6003c */ 	swc1	$f6,0x3c($sp)
/*    17afc:	c7aa003c */ 	lwc1	$f10,0x3c($sp)
/*    17b00:	e7a20044 */ 	swc1	$f2,0x44($sp)
/*    17b04:	e7a20018 */ 	swc1	$f2,0x18($sp)
/*    17b08:	e7b00060 */ 	swc1	$f16,0x60($sp)
/*    17b0c:	e7b00010 */ 	swc1	$f16,0x10($sp)
/*    17b10:	e7ae0070 */ 	swc1	$f14,0x70($sp)
/*    17b14:	e7b20040 */ 	swc1	$f18,0x40($sp)
/*    17b18:	e7b2001c */ 	swc1	$f18,0x1c($sp)
/*    17b1c:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*    17b20:	0c005f0b */ 	jal	mtx00017c2c
/*    17b24:	e7aa0020 */ 	swc1	$f10,0x20($sp)
/*    17b28:	c7a40050 */ 	lwc1	$f4,0x50($sp)
/*    17b2c:	c7a6004c */ 	lwc1	$f6,0x4c($sp)
/*    17b30:	c7a80044 */ 	lwc1	$f8,0x44($sp)
/*    17b34:	e7a40010 */ 	swc1	$f4,0x10($sp)
/*    17b38:	c7a4003c */ 	lwc1	$f4,0x3c($sp)
/*    17b3c:	c7aa0040 */ 	lwc1	$f10,0x40($sp)
/*    17b40:	e7a00030 */ 	swc1	$f0,0x30($sp)
/*    17b44:	c7ac0074 */ 	lwc1	$f12,0x74($sp)
/*    17b48:	c7ae0070 */ 	lwc1	$f14,0x70($sp)
/*    17b4c:	8fa6006c */ 	lw	$a2,0x6c($sp)
/*    17b50:	8fa70054 */ 	lw	$a3,0x54($sp)
/*    17b54:	e7a60014 */ 	swc1	$f6,0x14($sp)
/*    17b58:	e7a80018 */ 	swc1	$f8,0x18($sp)
/*    17b5c:	e7a40020 */ 	swc1	$f4,0x20($sp)
/*    17b60:	0c005f0b */ 	jal	mtx00017c2c
/*    17b64:	e7aa001c */ 	swc1	$f10,0x1c($sp)
/*    17b68:	c7a60050 */ 	lwc1	$f6,0x50($sp)
/*    17b6c:	c7a8004c */ 	lwc1	$f8,0x4c($sp)
/*    17b70:	c7aa0044 */ 	lwc1	$f10,0x44($sp)
/*    17b74:	e7a60010 */ 	swc1	$f6,0x10($sp)
/*    17b78:	c7a6003c */ 	lwc1	$f6,0x3c($sp)
/*    17b7c:	c7a40040 */ 	lwc1	$f4,0x40($sp)
/*    17b80:	e7a00034 */ 	swc1	$f0,0x34($sp)
/*    17b84:	c7ac0064 */ 	lwc1	$f12,0x64($sp)
/*    17b88:	c7ae0060 */ 	lwc1	$f14,0x60($sp)
/*    17b8c:	8fa6005c */ 	lw	$a2,0x5c($sp)
/*    17b90:	8fa70054 */ 	lw	$a3,0x54($sp)
/*    17b94:	e7a80014 */ 	swc1	$f8,0x14($sp)
/*    17b98:	e7aa0018 */ 	swc1	$f10,0x18($sp)
/*    17b9c:	e7a60020 */ 	swc1	$f6,0x20($sp)
/*    17ba0:	0c005f0b */ 	jal	mtx00017c2c
/*    17ba4:	e7a4001c */ 	swc1	$f4,0x1c($sp)
/*    17ba8:	c7a80060 */ 	lwc1	$f8,0x60($sp)
/*    17bac:	c7aa005c */ 	lwc1	$f10,0x5c($sp)
/*    17bb0:	c7a40054 */ 	lwc1	$f4,0x54($sp)
/*    17bb4:	e7a80010 */ 	swc1	$f8,0x10($sp)
/*    17bb8:	c7a8004c */ 	lwc1	$f8,0x4c($sp)
/*    17bbc:	c7a60050 */ 	lwc1	$f6,0x50($sp)
/*    17bc0:	e7a00038 */ 	swc1	$f0,0x38($sp)
/*    17bc4:	c7ac0074 */ 	lwc1	$f12,0x74($sp)
/*    17bc8:	c7ae0070 */ 	lwc1	$f14,0x70($sp)
/*    17bcc:	8fa6006c */ 	lw	$a2,0x6c($sp)
/*    17bd0:	8fa70064 */ 	lw	$a3,0x64($sp)
/*    17bd4:	e7aa0014 */ 	swc1	$f10,0x14($sp)
/*    17bd8:	e7a40018 */ 	swc1	$f4,0x18($sp)
/*    17bdc:	e7a80020 */ 	swc1	$f8,0x20($sp)
/*    17be0:	0c005f0b */ 	jal	mtx00017c2c
/*    17be4:	e7a6001c */ 	swc1	$f6,0x1c($sp)
/*    17be8:	c7aa0078 */ 	lwc1	$f10,0x78($sp)
/*    17bec:	c7a40038 */ 	lwc1	$f4,0x38($sp)
/*    17bf0:	c7a80068 */ 	lwc1	$f8,0x68($sp)
/*    17bf4:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*    17bf8:	46045182 */ 	mul.s	$f6,$f10,$f4
/*    17bfc:	c7aa0034 */ 	lwc1	$f10,0x34($sp)
/*    17c00:	460a4102 */ 	mul.s	$f4,$f8,$f10
/*    17c04:	c7aa0058 */ 	lwc1	$f10,0x58($sp)
/*    17c08:	46043201 */ 	sub.s	$f8,$f6,$f4
/*    17c0c:	c7a60030 */ 	lwc1	$f6,0x30($sp)
/*    17c10:	46065102 */ 	mul.s	$f4,$f10,$f6
/*    17c14:	c7a60048 */ 	lwc1	$f6,0x48($sp)
/*    17c18:	27bd0080 */ 	addiu	$sp,$sp,0x80
/*    17c1c:	46044280 */ 	add.s	$f10,$f8,$f4
/*    17c20:	46060202 */ 	mul.s	$f8,$f0,$f6
/*    17c24:	03e00008 */ 	jr	$ra
/*    17c28:	46085001 */ 	sub.s	$f0,$f10,$f8
);

f32 mtx00017c2c(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8)
{
	f32 sp24;
	f32 sp20;
	f32 sp1c;

	sp1c = mtx00017cbc(arg1, arg2, arg7, arg8);
	sp20 = mtx00017cbc(arg4, arg5, arg7, arg8);
	sp24 = mtx00017cbc(arg1, arg2, arg4, arg5);

	return sp24 * arg6 + (arg0 * sp20 - arg3 * sp1c);
}

f32 mtx00017cbc(f32 arg0, f32 arg1, f32 arg2, f32 arg3)
{
	return arg0 * arg3 - arg1 * arg2;
}
