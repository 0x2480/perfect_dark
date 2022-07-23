#include <ultra64.h>
#include "lib/tlb.h"
#include "lib/boot.h"
#include "lib/reset.h"
#include "lib/segments.h"
#include "constants.h"
#include "game/menugfx.h"
#include "bss.h"
#include "lib/args.h"
#include "lib/rzip.h"
#include "lib/crash.h"
#include "lib/main.h"
#include "lib/snd.h"
#include "lib/pimgr.h"
#include "lib/videbug.h"
#include "lib/rmon.h"
#include "lib/lib_48150.h"
#include "data.h"
#include "types.h"

OSThread g_RmonThread;
OSThread g_IdleThread;
OSThread g_MainThread;
OSThread g_SchedThread;
OSMesgQueue g_SchedMesgQueue;
OSMesg var8008db48[32];
OSMesgQueue *g_SchedCmdQ;
u32 var8008dbcc;
OSSched g_Sched;
OSScClient var8008dca8;
u32 g_OsMemSize;

u32 var8005ce00 = 0;
u32 var8005ce04 = 0;
u32 var8005ce08 = 0;
u32 var8005ce0c = 0;
u8 *g_StackLeftAddrs[7] = {0};
u8 *g_StackRightAddrs[7] = {0};
u8 *g_StackAllocatedPos = (u8 *)0x80400000;
u32 var8005ce4c = 0x00000002;
u32 var8005ce50 = 0x10000000;

extern u8 *_libSegmentStart;
extern u8 *_datazipSegmentRomStart;
extern u8 *_datazipSegmentRomEnd;
extern u8 *_dataSegmentStart;
extern u8 *_inflateSegmentStart;
extern u8 *_inflateSegmentRomStart;
extern u8 *_inflateSegmentRomEnd;
extern u32 var803f50b8;
extern u16 varbc000c02;
extern u16 *var800902e4;
extern s16 var800902e8;

#if VERSION >= VERSION_NTSC_1_0
s32 bootGetMemSize(void)
{
	return g_OsMemSize;
}
#endif

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel bootPhase1
/*     16cc:	3c0e8000 */ 	lui	$t6,%hi(osResetType)
/*     16d0:	8dce030c */ 	lw	$t6,%lo(osResetType)($t6)
/*     16d4:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*     16d8:	24010001 */ 	addiu	$at,$zero,0x1
/*     16dc:	afbf0024 */ 	sw	$ra,0x24($sp)
/*     16e0:	15c10007 */ 	bne	$t6,$at,.L00001700
/*     16e4:	afb00020 */ 	sw	$s0,0x20($sp)
/*     16e8:	3c0f803f */ 	lui	$t7,0x803f
/*     16ec:	8df850b8 */ 	lw	$t8,0x50b8($t7)
/*     16f0:	3c028009 */ 	lui	$v0,%hi(g_OsMemSize)
/*     16f4:	2442dcb4 */ 	addiu	$v0,$v0,%lo(g_OsMemSize)
/*     16f8:	10000008 */ 	b	.L0000171c
/*     16fc:	ac580000 */ 	sw	$t8,0x0($v0)
.L00001700:
/*     1700:	3c198000 */ 	lui	$t9,%hi(osMemSize)
/*     1704:	8f390318 */ 	lw	$t9,%lo(osMemSize)($t9)
/*     1708:	3c028009 */ 	lui	$v0,%hi(g_OsMemSize)
/*     170c:	2442dcb4 */ 	addiu	$v0,$v0,%lo(g_OsMemSize)
/*     1710:	3c0a803f */ 	lui	$t2,0x803f
/*     1714:	ac590000 */ 	sw	$t9,0x0($v0)
/*     1718:	ad5950b8 */ 	sw	$t9,0x50b8($t2)
.L0000171c:
/*     171c:	3c040004 */ 	lui	$a0,%hi(_datazipSegmentRomStart)
/*     1720:	3c0b0005 */ 	lui	$t3,%hi(_datazipSegmentRomEnd)
/*     1724:	3c0c0005 */ 	lui	$t4,%hi(_inflateSegmentRomEnd)
/*     1728:	3c0d0005 */ 	lui	$t5,%hi(_inflateSegmentRomStart)
/*     172c:	25ade850 */ 	addiu	$t5,$t5,%lo(_inflateSegmentRomStart)
/*     1730:	258cfc40 */ 	addiu	$t4,$t4,%lo(_inflateSegmentRomEnd)
/*     1734:	256be850 */ 	addiu	$t3,$t3,%lo(_datazipSegmentRomEnd)
/*     1738:	24849850 */ 	addiu	$a0,$a0,%lo(_datazipSegmentRomStart)
/*     173c:	01644023 */ 	subu	$t0,$t3,$a0
/*     1740:	018d7023 */ 	subu	$t6,$t4,$t5
/*     1744:	010e1821 */ 	addu	$v1,$t0,$t6
/*     1748:	2462ffff */ 	addiu	$v0,$v1,-1
/*     174c:	0440000b */ 	bltz	$v0,.L0000177c
/*     1750:	3c057000 */ 	lui	$a1,%hi(_libSegmentStart)
/*     1754:	3c017000 */ 	lui	$at,0x7000
/*     1758:	3c0f7020 */ 	lui	$t7,0x7020
/*     175c:	01e88023 */ 	subu	$s0,$t7,$t0
/*     1760:	00811825 */ 	or	$v1,$a0,$at
.L00001764:
/*     1764:	0062c021 */ 	addu	$t8,$v1,$v0
/*     1768:	93190000 */ 	lbu	$t9,0x0($t8)
/*     176c:	02024821 */ 	addu	$t1,$s0,$v0
/*     1770:	2442ffff */ 	addiu	$v0,$v0,-1
/*     1774:	0441fffb */ 	bgez	$v0,.L00001764
/*     1778:	a1390000 */ 	sb	$t9,0x0($t1)
.L0000177c:
/*     177c:	24a51050 */ 	addiu	$a1,$a1,%lo(_libSegmentStart)
/*     1780:	3c07702c */ 	lui	$a3,0x702c
/*     1784:	3c0a7020 */ 	lui	$t2,0x7020
/*     1788:	01488023 */ 	subu	$s0,$t2,$t0
/*     178c:	34e793e0 */ 	ori	$a3,$a3,0x93e0
/*     1790:	24a52000 */ 	addiu	$a1,$a1,0x2000
/*     1794:	00002025 */ 	or	$a0,$zero,$zero
/*     1798:	3c037028 */ 	lui	$v1,0x7028
.L0000179c:
/*     179c:	00a45821 */ 	addu	$t3,$a1,$a0
/*     17a0:	8d6c0000 */ 	lw	$t4,0x0($t3)
/*     17a4:	24630004 */ 	addiu	$v1,$v1,0x4
/*     17a8:	0067082b */ 	sltu	$at,$v1,$a3
/*     17ac:	24840004 */ 	addiu	$a0,$a0,0x4
/*     17b0:	1420fffa */ 	bnez	$at,.L0000179c
/*     17b4:	ac6cfffc */ 	sw	$t4,-0x4($v1)
/*     17b8:	3c047028 */ 	lui	$a0,0x7028
/*     17bc:	0c0005ab */ 	jal	segInflate
/*     17c0:	3c068030 */ 	lui	$a2,0x8030
/*     17c4:	3c058006 */ 	lui	$a1,%hi(_dataSegmentStart)
/*     17c8:	24a59fe0 */ 	addiu	$a1,$a1,%lo(_dataSegmentStart)
/*     17cc:	02002025 */ 	or	$a0,$s0,$zero
/*     17d0:	0c0005ab */ 	jal	segInflate
/*     17d4:	3c068030 */ 	lui	$a2,0x8030
/*     17d8:	3c0da000 */ 	lui	$t5,0xa000
/*     17dc:	8dae02e8 */ 	lw	$t6,0x2e8($t5)
/*     17e0:	3c01c86e */ 	lui	$at,0xc86e
/*     17e4:	34212000 */ 	ori	$at,$at,0x2000
/*     17e8:	11c10003 */ 	beq	$t6,$at,.L000017f8
/*     17ec:	24040001 */ 	addiu	$a0,$zero,0x1
.L000017f0:
/*     17f0:	1000ffff */ 	b	.L000017f0
/*     17f4:	00000000 */ 	nop
.L000017f8:
/*     17f8:	0c00058d */ 	jal	tlbUnmapRange
/*     17fc:	2405001f */ 	addiu	$a1,$zero,0x1f
/*     1800:	3c048006 */ 	lui	$a0,%hi(g_StackLeftAddrs)
/*     1804:	3c038006 */ 	lui	$v1,%hi(g_StackRightAddrs)
/*     1808:	3c028006 */ 	lui	$v0,%hi(g_StackRightAddrs+0x1c)
/*     180c:	2442ce48 */ 	addiu	$v0,$v0,%lo(g_StackRightAddrs+0x1c)
/*     1810:	2463ce2c */ 	addiu	$v1,$v1,%lo(g_StackRightAddrs)
/*     1814:	2484ce10 */ 	addiu	$a0,$a0,%lo(g_StackLeftAddrs)
.L00001818:
/*     1818:	24630004 */ 	addiu	$v1,$v1,0x4
/*     181c:	24840004 */ 	addiu	$a0,$a0,0x4
/*     1820:	ac80fffc */ 	sw	$zero,-0x4($a0)
/*     1824:	1462fffc */ 	bne	$v1,$v0,.L00001818
/*     1828:	ac60fffc */ 	sw	$zero,-0x4($v1)
/*     182c:	0c0016d8 */ 	jal	osInitialize
/*     1830:	00000000 */ 	nop
/*     1834:	0c012048 */ 	jal	osWritebackDCacheAll
/*     1838:	00000000 */ 	nop
/*     183c:	3c048000 */ 	lui	$a0,0x8000
/*     1840:	0c012054 */ 	jal	osInvalICache
/*     1844:	24054000 */ 	addiu	$a1,$zero,0x4000
/*     1848:	0c012074 */ 	jal	__osGetFpcCsr
/*     184c:	00000000 */ 	nop
/*     1850:	0c012078 */ 	jal	__osSetFpcCsr
/*     1854:	34440e80 */ 	ori	$a0,$v0,0xe80
/*     1858:	24040003 */ 	addiu	$a0,$zero,0x3
/*     185c:	0c00062b */ 	jal	bootAllocateStack
/*     1860:	34059800 */ 	dli	$a1,0x9800
/*     1864:	3c108009 */ 	lui	$s0,%hi(g_MainThread)
/*     1868:	2610d6d0 */ 	addiu	$s0,$s0,%lo(g_MainThread)
/*     186c:	3c067000 */ 	lui	$a2,%hi(bootPhase2)
/*     1870:	2409000a */ 	addiu	$t1,$zero,0xa
/*     1874:	afa90014 */ 	sw	$t1,0x14($sp)
/*     1878:	24c61aa4 */ 	addiu	$a2,$a2,%lo(bootPhase2)
/*     187c:	02002025 */ 	or	$a0,$s0,$zero
/*     1880:	24050003 */ 	addiu	$a1,$zero,0x3
/*     1884:	00003825 */ 	or	$a3,$zero,$zero
/*     1888:	0c000fb8 */ 	jal	osCreateThread
/*     188c:	afa20010 */ 	sw	$v0,0x10($sp)
/*     1890:	0c01207c */ 	jal	osStartThread
/*     1894:	02002025 */ 	or	$a0,$s0,$zero
/*     1898:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*     189c:	8fb00020 */ 	lw	$s0,0x20($sp)
/*     18a0:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*     18a4:	03e00008 */ 	jr	$ra
/*     18a8:	00000000 */ 	nop
);
#else
GLOBAL_ASM(
glabel bootPhase1
/*     1720:	3c040003 */ 	lui	$a0,0x3
/*     1724:	3c0e0004 */ 	lui	$t6,0x4
/*     1728:	3c0f0004 */ 	lui	$t7,0x4
/*     172c:	3c180004 */ 	lui	$t8,0x4
/*     1730:	27182850 */ 	addiu	$t8,$t8,0x2850
/*     1734:	25ef3c40 */ 	addiu	$t7,$t7,0x3c40
/*     1738:	25ce2850 */ 	addiu	$t6,$t6,0x2850
/*     173c:	24840850 */ 	addiu	$a0,$a0,0x850
/*     1740:	01c44023 */ 	subu	$t0,$t6,$a0
/*     1744:	01f8c823 */ 	subu	$t9,$t7,$t8
/*     1748:	01191821 */ 	addu	$v1,$t0,$t9
/*     174c:	27bdffd8 */ 	addiu	$sp,$sp,-40
/*     1750:	2462ffff */ 	addiu	$v0,$v1,-1
/*     1754:	afbf0024 */ 	sw	$ra,0x24($sp)
/*     1758:	0440000b */ 	bltz	$v0,.L00001788
/*     175c:	afb00020 */ 	sw	$s0,0x20($sp)
/*     1760:	3c017000 */ 	lui	$at,0x7000
/*     1764:	3c097020 */ 	lui	$t1,0x7020
/*     1768:	01288023 */ 	subu	$s0,$t1,$t0
/*     176c:	00811825 */ 	or	$v1,$a0,$at
.L00001770:
/*     1770:	00625021 */ 	addu	$t2,$v1,$v0
/*     1774:	914b0000 */ 	lbu	$t3,0x0($t2)
/*     1778:	02026021 */ 	addu	$t4,$s0,$v0
/*     177c:	2442ffff */ 	addiu	$v0,$v0,-1
/*     1780:	0441fffb */ 	bgez	$v0,.L00001770
/*     1784:	a18b0000 */ 	sb	$t3,0x0($t4)
.L00001788:
/*     1788:	3c057000 */ 	lui	$a1,0x7000
/*     178c:	24a51050 */ 	addiu	$a1,$a1,0x1050
/*     1790:	3c0d7020 */ 	lui	$t5,0x7020
/*     1794:	3c07702c */ 	lui	$a3,0x702c
/*     1798:	34e793e0 */ 	ori	$a3,$a3,0x93e0
/*     179c:	01a88023 */ 	subu	$s0,$t5,$t0
/*     17a0:	24a52000 */ 	addiu	$a1,$a1,0x2000
/*     17a4:	00002025 */ 	move	$a0,$zero
/*     17a8:	3c037028 */ 	lui	$v1,0x7028
.L000017ac:
/*     17ac:	00a47021 */ 	addu	$t6,$a1,$a0
/*     17b0:	8dcf0000 */ 	lw	$t7,0x0($t6)
/*     17b4:	24630004 */ 	addiu	$v1,$v1,0x4
/*     17b8:	0067082b */ 	sltu	$at,$v1,$a3
/*     17bc:	24840004 */ 	addiu	$a0,$a0,0x4
/*     17c0:	1420fffa */ 	bnez	$at,.L000017ac
/*     17c4:	ac6ffffc */ 	sw	$t7,-0x4($v1)
/*     17c8:	3c047028 */ 	lui	$a0,0x7028
/*     17cc:	0c0005c3 */ 	jal	segInflate
/*     17d0:	3c068030 */ 	lui	$a2,0x8030
/*     17d4:	3c058006 */ 	lui	$a1,0x8006
/*     17d8:	24a5b760 */ 	addiu	$a1,$a1,-18592
/*     17dc:	02002025 */ 	move	$a0,$s0
/*     17e0:	0c0005c3 */ 	jal	segInflate
/*     17e4:	3c068030 */ 	lui	$a2,0x8030
/*     17e8:	24040001 */ 	li	$a0,0x1
/*     17ec:	0c00059c */ 	jal	tlbUnmapRange
/*     17f0:	2405001f */ 	li	$a1,0x1f
/*     17f4:	3c048006 */ 	lui	$a0,0x8006
/*     17f8:	3c038006 */ 	lui	$v1,0x8006
/*     17fc:	3c028006 */ 	lui	$v0,0x8006
/*     1800:	2442e5c8 */ 	addiu	$v0,$v0,-6712
/*     1804:	2463e5ac */ 	addiu	$v1,$v1,-6740
/*     1808:	2484e590 */ 	addiu	$a0,$a0,-6768
.L0000180c:
/*     180c:	24630004 */ 	addiu	$v1,$v1,0x4
/*     1810:	24840004 */ 	addiu	$a0,$a0,0x4
/*     1814:	ac80fffc */ 	sw	$zero,-0x4($a0)
/*     1818:	1462fffc */ 	bne	$v1,$v0,.L0000180c
/*     181c:	ac60fffc */ 	sw	$zero,-0x4($v1)
/*     1820:	0c001728 */ 	jal	osInitialize
/*     1824:	00000000 */ 	nop
/*     1828:	0c01253c */ 	jal	osWritebackDCacheAll
/*     182c:	00000000 */ 	nop
/*     1830:	3c048000 */ 	lui	$a0,0x8000
/*     1834:	0c012548 */ 	jal	osInvalICache
/*     1838:	24054000 */ 	li	$a1,0x4000
/*     183c:	0c012568 */ 	jal	__osGetFpcCsr
/*     1840:	00000000 */ 	nop
/*     1844:	0c01256c */ 	jal	__osSetFpcCsr
/*     1848:	34440e80 */ 	ori	$a0,$v0,0xe80
/*     184c:	3c03bc00 */ 	lui	$v1,0xbc00
/*     1850:	34630c02 */ 	ori	$v1,$v1,0xc02
/*     1854:	3c018009 */ 	lui	$at,0x8009
/*     1858:	ac2302e4 */ 	sw	$v1,0x2e4($at)
/*     185c:	3c018009 */ 	lui	$at,0x8009
/*     1860:	240a4040 */ 	li	$t2,0x4040
/*     1864:	a42a02e8 */ 	sh	$t2,0x2e8($at)
/*     1868:	240b4040 */ 	li	$t3,0x4040
/*     186c:	a46b0000 */ 	sh	$t3,0x0($v1)
/*     1870:	24040003 */ 	li	$a0,0x3
/*     1874:	0c000631 */ 	jal	bootAllocateStack
/*     1878:	34059800 */ 	li	$a1,0x9800
/*     187c:	3c108009 */ 	lui	$s0,0x8009
/*     1880:	2610fd00 */ 	addiu	$s0,$s0,-768
/*     1884:	3c067000 */ 	lui	$a2,0x7000
/*     1888:	240c000a */ 	li	$t4,0xa
/*     188c:	afac0014 */ 	sw	$t4,0x14($sp)
/*     1890:	24c61b04 */ 	addiu	$a2,$a2,0x1b04
/*     1894:	02002025 */ 	move	$a0,$s0
/*     1898:	24050003 */ 	li	$a1,0x3
/*     189c:	00003825 */ 	move	$a3,$zero
/*     18a0:	0c00107c */ 	jal	osCreateThread
/*     18a4:	afa20010 */ 	sw	$v0,0x10($sp)
/*     18a8:	0c012570 */ 	jal	osStartThread
/*     18ac:	02002025 */ 	move	$a0,$s0
/*     18b0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*     18b4:	8fb00020 */ 	lw	$s0,0x20($sp)
/*     18b8:	27bd0028 */ 	addiu	$sp,$sp,0x28
/*     18bc:	03e00008 */ 	jr	$ra
/*     18c0:	00000000 */ 	nop
);
#endif

u32 __osGetFpcCsr(void);
void __osSetFpcCsr(u32 arg0);

/**
 * Prepares the inflate, .data and lib segments, then creates and starts the
 * main thread.
 *
 * This function relies on the fact that the N64 BIOS loads the first 1MB of ROM
 * data into memory at power on. The inflate, .data and lib segments are already
 * in RAM thanks to this but need to be relocated, and .data and lib need to be
 * unzipped too.
 */
// Mismatch: Reordered instructions.
// Remove U from 75000U for another interesting codegen.
//void bootPhase1(void)
//{
//	s32 datacomplen;
//	s32 inflatelen;
//	u32 dataziprom;
//	u32 datazipram;
//	u32 libram;
//	u32 libzipram;
//	u32 dataram;
//	u32 copylen;
//	s32 i;
//
//#if VERSION >= VERSION_NTSC_1_0
//	if (osResetType == 1) {
//		g_OsMemSize = *(u32 *)0x803f50b8;
//	} else {
//		*(u32 *)0x803f50b8 = g_OsMemSize = osMemSize;
//	}
//#endif
//
//	// Copy compressed .data and inflate segments
//	// .data is copied from ROM to 0x701eb000 - 0x70200000
//	// inflate is copied from ROM to 0x70200000 - 0x702013f0
//	datacomplen = (s32)&_datazipSegmentRomEnd - (s32)&_datazipSegmentRomStart;
//	inflatelen = (s32)&_inflateSegmentRomEnd - (s32)&_inflateSegmentRomStart;
//	copylen = datacomplen + inflatelen;
//	libram = (u32)&_libSegmentStart + 0x2000;
//	libzipram = 0x70280000;
//	dataziprom = (u32)&_datazipSegmentRomStart | 0x70000000;
//	datazipram = 0x70200000 - datacomplen;
//	dataram = (u32)&_dataSegmentStart;
//
//	for (i = copylen - 1; i >= 0; i--) {
//		((u8 *)datazipram)[i] = ((u8 *)dataziprom)[i];
//	}
//
//	// Copy the compressed part of lib to 0x70280000.
//	// lib is compressed from 2KB onwards.
//	// It's assumed that lib's compressed length is less than 75000 words.
//	// This is fine, as it's about half that.
//	for (i = 0; i < 75000U; i++) {
//		((u32 *)libzipram)[i] = ((u32 *)libram)[i];
//	}
//
//	// Inflate compressed part of lib
//	segInflate((void *) libzipram, (void *) libram, (void *) 0x80300000);
//
//	// Inflate .data
//	segInflate((void *) datazipram, (void *) dataram, (void *) 0x80300000);
//
//#if PIRACYCHECKS
//	if (IO_READ(0xa00002e8) != 0xc86e2000) {
//		while (1);
//	}
//#endif
//
//	tlbUnmapRange(1, NTLBENTRIES);
//
//	// Clear the stack allocation pointers
//	for (i = 0; i < ARRAYCOUNT(g_StackLeftAddrs); i++) {
//		g_StackLeftAddrs[i] = NULL;
//		g_StackRightAddrs[i] = NULL;
//	}
//
//	osInitialize();
//
//	// Write all data memory cache into physical memory
//	osWritebackDCacheAll();
//
//	// Invalidate all instruction cache
//	osInvalICache((void *) 0x80000000, ICACHE_SIZE);
//
//	// Enable inexact operation, overflow, division by zero and invalid operation
//	__osSetFpcCsr(__osGetFpcCsr() | (FPCSR_EI | FPCSR_EO | FPCSR_EZ | FPCSR_EV));
//
//#if VERSION < VERSION_NTSC_1_0
//	var800902e4 = &varbc000c02;
//	var800902e8 = 0x4040;
//	varbc000c02 = 0x4040;
//#endif
//
//	// Create and start the main thread
//	osCreateThread(&g_MainThread, THREAD_MAIN, bootPhase2, NULL, bootAllocateStack(THREAD_MAIN, STACKSIZE_MAIN), THREADPRI_MAIN);
//	osStartThread(&g_MainThread);
//}

/**
 * Allocate stack space for the given thread ID.
 *
 * Each allocation is aligned to 16 bytes.
 *
 * Allocations start from the end of onboard memory (0x80400000) and are
 * allocated right to left.
 *
 * The returned address leaves 8 bytes free on the right side of the stack,
 * presumably for identification purposes. So the actual stack space available
 * can be 8 bytes above or below what was requested.
 *
 * The stack is initialised with the thread's ID. This makes it easier to
 * identify in memory and detect when a stack overflow has occurred.
 */
void *bootAllocateStack(s32 threadid, s32 size)
{
	u8 *ptr8;
	u32 *ptr32;
	s32 i;
	s32 j;
	u8 *tmp;

	g_StackRightAddrs[threadid] = g_StackAllocatedPos;
	size = (size + 0xf) & 0xfffffff0;

	g_StackAllocatedPos -= size;
	g_StackLeftAddrs[threadid] = (tmp = g_StackAllocatedPos);

	ptr8 = g_StackAllocatedPos;

	for (i = 0; i < size; i++) {
		ptr8[i] = ((0xf - (threadid & 0xf)) << 4) | (threadid & 0xf);
	}

#if VERSION < VERSION_NTSC_1_0
	// Mark the first 8 words specially
	ptr32 = (u32 *)g_StackLeftAddrs[threadid];

	for (j = 0; j < 8; j++) {
		*ptr32 = 0xdeadbabe;
		ptr32++;
	}
#endif

	return g_StackAllocatedPos + size - 8;
}

#if VERSION < VERSION_NTSC_1_0
u8 *bootGetStackPos(void)
{
	return g_StackAllocatedPos;
}
#endif

#if VERSION < VERSION_NTSC_1_0
void func00001978(void)
{
	var8005ce4c = 1;
	var8005ce50 = 0x10000000;
}
#endif

void idleproc(void *data)
{
	while (true);
}

void bootCreateIdleThread(void)
{
	osCreateThread(&g_IdleThread, THREAD_IDLE, idleproc, NULL, bootAllocateStack(THREAD_IDLE, STACKSIZE_IDLE), THREADPRI_IDLE);
	osStartThread(&g_IdleThread);
}

void bootCreateRmonThread(void)
{
	osCreateThread(&g_RmonThread, THREAD_RMON, rmonproc, NULL, bootAllocateStack(THREAD_RMON, STACKSIZE_RMON), THREADPRI_RMON);
	osStartThread(&g_RmonThread);
}

void bootCreateSchedThread(void)
{
	osCreateMesgQueue(&g_SchedMesgQueue, var8008db48, ARRAYCOUNT(var8008db48));

	if (osTvType == OS_TV_MPAL) {
		osCreateScheduler(&g_Sched, &g_SchedThread, OS_VI_MPAL_LAN1, 1);
	} else {
		osCreateScheduler(&g_Sched, &g_SchedThread, OS_VI_NTSC_LAN1, 1);
	}

	osScAddClient(&g_Sched, &var8008dca8, &g_SchedMesgQueue, 0);
	g_SchedCmdQ = osScGetCmdQ(&g_Sched);
}

void bootPhase2(void *arg)
{
	bootCreateIdleThread();
	videbugCreate();
	pimgrCreate();
	bootCreateRmonThread();

	if (argsParseDebugArgs()) {
		osStopThread(NULL);
	}

	osSetThreadPri(0, THREADPRI_MAIN);
	bootCreateSchedThread();
	mainProc();
}

#if VERSION < VERSION_NTSC_1_0
GLOBAL_ASM(
glabel func00001b70nb
/*     1b70:	3c048006 */ 	lui	$a0,0x8006
/*     1b74:	3c068006 */ 	lui	$a2,0x8006
/*     1b78:	24c6e5ac */ 	addiu	$a2,$a2,-6740
/*     1b7c:	2484e590 */ 	addiu	$a0,$a0,-6768
/*     1b80:	00001025 */ 	move	$v0,$zero
/*     1b84:	240a0007 */ 	li	$t2,0x7
/*     1b88:	2409000f */ 	li	$t1,0xf
.L00001b8c:
/*     1b8c:	8c830000 */ 	lw	$v1,0x0($a0)
/*     1b90:	24840004 */ 	addiu	$a0,$a0,0x4
/*     1b94:	8cc50000 */ 	lw	$a1,0x0($a2)
/*     1b98:	10600011 */ 	beqz	$v1,.L00001be0
/*     1b9c:	3047000f */ 	andi	$a3,$v0,0xf
/*     1ba0:	90780020 */ 	lbu	$t8,0x20($v1)
/*     1ba4:	01277023 */ 	subu	$t6,$t1,$a3
/*     1ba8:	000e7900 */ 	sll	$t7,$t6,0x4
/*     1bac:	01e74025 */ 	or	$t0,$t7,$a3
/*     1bb0:	1518000b */ 	bne	$t0,$t8,.L00001be0
/*     1bb4:	24630020 */ 	addiu	$v1,$v1,0x20
/*     1bb8:	0065082b */ 	sltu	$at,$v1,$a1
/*     1bbc:	50200009 */ 	beqzl	$at,.L00001be4
/*     1bc0:	24420001 */ 	addiu	$v0,$v0,0x1
/*     1bc4:	90790001 */ 	lbu	$t9,0x1($v1)
.L00001bc8:
/*     1bc8:	24630001 */ 	addiu	$v1,$v1,0x1
/*     1bcc:	0065082b */ 	sltu	$at,$v1,$a1
/*     1bd0:	55190004 */ 	bnel	$t0,$t9,.L00001be4
/*     1bd4:	24420001 */ 	addiu	$v0,$v0,0x1
/*     1bd8:	5420fffb */ 	bnezl	$at,.L00001bc8
/*     1bdc:	90790001 */ 	lbu	$t9,0x1($v1)
.L00001be0:
/*     1be0:	24420001 */ 	addiu	$v0,$v0,0x1
.L00001be4:
/*     1be4:	144affe9 */ 	bne	$v0,$t2,.L00001b8c
/*     1be8:	24c60004 */ 	addiu	$a2,$a2,0x4
/*     1bec:	03e00008 */ 	jr	$ra
/*     1bf0:	00000000 */ 	nop
);
#endif

#if VERSION < VERSION_NTSC_1_0
const char var700539b0nb[] = "Stack overflow thread %d";

GLOBAL_ASM(
glabel func00001bf4nb
/*     1bf4:	27bdff28 */ 	addiu	$sp,$sp,-216
/*     1bf8:	afbe0038 */ 	sw	$s8,0x38($sp)
/*     1bfc:	afb5002c */ 	sw	$s5,0x2c($sp)
/*     1c00:	afb40028 */ 	sw	$s4,0x28($sp)
/*     1c04:	afb70034 */ 	sw	$s7,0x34($sp)
/*     1c08:	afb60030 */ 	sw	$s6,0x30($sp)
/*     1c0c:	afb30024 */ 	sw	$s3,0x24($sp)
/*     1c10:	afb20020 */ 	sw	$s2,0x20($sp)
/*     1c14:	3c14dead */ 	lui	$s4,0xdead
/*     1c18:	3c157005 */ 	lui	$s5,0x7005
/*     1c1c:	3c1e8006 */ 	lui	$s8,0x8006
/*     1c20:	afbf003c */ 	sw	$ra,0x3c($sp)
/*     1c24:	afb1001c */ 	sw	$s1,0x1c($sp)
/*     1c28:	afb00018 */ 	sw	$s0,0x18($sp)
/*     1c2c:	27dee590 */ 	addiu	$s8,$s8,-6768
/*     1c30:	26b539b0 */ 	addiu	$s5,$s5,0x39b0
/*     1c34:	3694babe */ 	ori	$s4,$s4,0xbabe
/*     1c38:	27b2004c */ 	addiu	$s2,$sp,0x4c
/*     1c3c:	00009825 */ 	move	$s3,$zero
/*     1c40:	24160045 */ 	li	$s6,0x45
/*     1c44:	24170008 */ 	li	$s7,0x8
.L00001c48:
/*     1c48:	8fc20000 */ 	lw	$v0,0x0($s8)
/*     1c4c:	00008825 */ 	move	$s1,$zero
/*     1c50:	10400010 */ 	beqz	$v0,.L00001c94
/*     1c54:	00408025 */ 	move	$s0,$v0
.L00001c58:
/*     1c58:	8e0e0000 */ 	lw	$t6,0x0($s0)
/*     1c5c:	528e000b */ 	beql	$s4,$t6,.L00001c8c
/*     1c60:	26310001 */ 	addiu	$s1,$s1,0x1
/*     1c64:	0c0006dc */ 	jal	func00001b70nb
/*     1c68:	00000000 */ 	nop
/*     1c6c:	02402025 */ 	move	$a0,$s2
/*     1c70:	02a02825 */ 	move	$a1,$s5
/*     1c74:	0c004fc1 */ 	jal	sprintf
/*     1c78:	02603025 */ 	move	$a2,$s3
/*     1c7c:	0c003074 */ 	jal	crashSetMessage
/*     1c80:	02402025 */ 	move	$a0,$s2
/*     1c84:	a0160000 */ 	sb	$s6,0x0($zero)
/*     1c88:	26310001 */ 	addiu	$s1,$s1,0x1
.L00001c8c:
/*     1c8c:	1637fff2 */ 	bne	$s1,$s7,.L00001c58
/*     1c90:	26100004 */ 	addiu	$s0,$s0,0x4
.L00001c94:
/*     1c94:	26730001 */ 	addiu	$s3,$s3,0x1
/*     1c98:	24010007 */ 	li	$at,0x7
/*     1c9c:	1661ffea */ 	bne	$s3,$at,.L00001c48
/*     1ca0:	27de0004 */ 	addiu	$s8,$s8,0x4
/*     1ca4:	8fbf003c */ 	lw	$ra,0x3c($sp)
/*     1ca8:	8fb00018 */ 	lw	$s0,0x18($sp)
/*     1cac:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*     1cb0:	8fb20020 */ 	lw	$s2,0x20($sp)
/*     1cb4:	8fb30024 */ 	lw	$s3,0x24($sp)
/*     1cb8:	8fb40028 */ 	lw	$s4,0x28($sp)
/*     1cbc:	8fb5002c */ 	lw	$s5,0x2c($sp)
/*     1cc0:	8fb60030 */ 	lw	$s6,0x30($sp)
/*     1cc4:	8fb70034 */ 	lw	$s7,0x34($sp)
/*     1cc8:	8fbe0038 */ 	lw	$s8,0x38($sp)
/*     1ccc:	03e00008 */ 	jr	$ra
/*     1cd0:	27bd00d8 */ 	addiu	$sp,$sp,0xd8
);
#endif
