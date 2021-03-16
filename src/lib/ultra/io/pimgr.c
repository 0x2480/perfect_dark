#include <libultra_internal.h>
#include "bss.h"
#include "data.h"

OSThread piThread;
u32 var800905c0;
u32 var800905c4;
u32 var800905c8;
u32 var800905cc;
u32 var800905d0;
u32 var800905d4;
u32 var800905d8;
u32 var800905dc;
u32 var800905e0;
u32 var800905e4;
u32 var800905e8;
u32 var800905ec;
u32 var800905f0;
u32 var800905f4;
u32 var800905f8;
u32 var800905fc;
u32 var80090600;
u32 var80090604;
u32 var80090608;
u32 var8009060c;
u32 var80090610;
u32 var80090614;
u32 var80090618;
u32 var8009061c;
u32 var80090620;
u32 var80090624;
u32 var80090628;
u32 var8009062c;
u32 var80090630;
u32 var80090634;
u32 var80090638;
u32 var8009063c;
u32 var80090640;
u32 var80090644;
u32 var80090648;
u32 var8009064c;
u32 var80090650;
u32 var80090654;
u32 var80090658;
u32 var8009065c;
u32 var80090660;
u32 var80090664;
u32 var80090668;
u32 var8009066c;
u32 var80090670;
u32 var80090674;
u32 var80090678;
u32 var8009067c;
u32 var80090680;
u32 var80090684;
u32 var80090688;
u32 var8009068c;
u32 var80090690;
u32 var80090694;
u32 var80090698;
u32 var8009069c;
u32 var800906a0;
u32 var800906a4;
u32 var800906a8;
u32 var800906ac;
u32 var800906b0;
u32 var800906b4;
u32 var800906b8;
u32 var800906bc;
u32 var800906c0;
u32 var800906c4;
u32 var800906c8;
u32 var800906cc;
u32 var800906d0;
u32 var800906d4;
u32 var800906d8;
u32 var800906dc;
u32 var800906e0;
u32 var800906e4;
u32 var800906e8;
u32 var800906ec;
u32 var800906f0;
u32 var800906f4;
u32 var800906f8;
u32 var800906fc;
u32 var80090700;
u32 var80090704;
u32 var80090708;
u32 var8009070c;
u32 var80090710;
u32 var80090714;
u32 var80090718;
u32 var8009071c;
u32 var80090720;
u32 var80090724;
u32 var80090728;
u32 var8009072c;
u32 var80090730;
u32 var80090734;
u32 var80090738;
u32 var8009073c;
u32 var80090740;
u32 var80090744;
u32 var80090748;
u32 var8009074c;
u32 var80090750;
u32 var80090754;
u32 var80090758;
u32 var8009075c;
u32 var80090760;
u32 var80090764;
u32 var80090768;
u32 var8009076c;
u32 var80090770;
u32 var80090774;
u32 var80090778;
u32 var8009077c;
u32 var80090780;
u32 var80090784;
u32 var80090788;
u32 var8009078c;
u32 var80090790;
u32 var80090794;
u32 var80090798;
u32 var8009079c;
u32 var800907a0;
u32 var800907a4;
u32 var800907a8;
u32 var800907ac;
u32 var800907b0;
u32 var800907b4;
u32 var800907b8;
u32 var800907bc;
u32 piEventQueue;
u32 var800907c4;
u32 var800907c8;
u32 var800907cc;
u32 var800907d0;
u32 var800907d4;
u32 piEventBuf;
u32 var800907dc;
u32 var800907e0;
u32 var800907e4;
u32 var800907e8;
u32 var800907ec;

OSDevMgr __osPiDevMgr = {0};
u32 var8005cf1c = 0;
u32 __osCurrentHandle = (u32) &var800902a0;
u32 var8005cf24 = (u32) &var80090318;

GLOBAL_ASM(
glabel osCreatePiPanager
/*     3360:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*     3364:	afb00020 */ 	sw	$s0,0x20($sp)
/*     3368:	3c108006 */ 	lui	$s0,%hi(__osPiDevMgr)
/*     336c:	2610cf00 */ 	addiu	$s0,$s0,%lo(__osPiDevMgr)
/*     3370:	8e0e0000 */ 	lw	$t6,0x0($s0)
/*     3374:	afbf0024 */ 	sw	$ra,0x24($sp)
/*     3378:	afa40030 */ 	sw	$a0,0x30($sp)
/*     337c:	afa50034 */ 	sw	$a1,0x34($sp)
/*     3380:	15c0004e */ 	bnez	$t6,.L000034bc
/*     3384:	afa60038 */ 	sw	$a2,0x38($sp)
/*     3388:	00a02025 */ 	or	$a0,$a1,$zero
/*     338c:	00c02825 */ 	or	$a1,$a2,$zero
/*     3390:	0c0120d0 */ 	jal	osCreateMesgQueue
/*     3394:	00e03025 */ 	or	$a2,$a3,$zero
/*     3398:	3c048009 */ 	lui	$a0,%hi(piEventQueue)
/*     339c:	3c058009 */ 	lui	$a1,%hi(piEventBuf)
/*     33a0:	24a507d8 */ 	addiu	$a1,$a1,%lo(piEventBuf)
/*     33a4:	248407c0 */ 	addiu	$a0,$a0,%lo(piEventQueue)
/*     33a8:	0c0120d0 */ 	jal	osCreateMesgQueue
/*     33ac:	24060004 */ 	addiu	$a2,$zero,0x4
/*     33b0:	3c0f8006 */ 	lui	$t7,%hi(__osPiAccessQueueEnabled)
/*     33b4:	8def0920 */ 	lw	$t7,%lo(__osPiAccessQueueEnabled)($t7)
/*     33b8:	15e00003 */ 	bnez	$t7,.L000033c8
/*     33bc:	00000000 */ 	nop
/*     33c0:	0c0126a4 */ 	jal	__osPiCreateAccessQueue
/*     33c4:	00000000 */ 	nop
.L000033c8:
/*     33c8:	3c058009 */ 	lui	$a1,%hi(piEventQueue)
/*     33cc:	3c062222 */ 	lui	$a2,0x2222
/*     33d0:	34c62222 */ 	ori	$a2,$a2,0x2222
/*     33d4:	24a507c0 */ 	addiu	$a1,$a1,%lo(piEventQueue)
/*     33d8:	0c012148 */ 	jal	osSetEventMesg
/*     33dc:	24040008 */ 	addiu	$a0,$zero,0x8
/*     33e0:	2418ffff */ 	addiu	$t8,$zero,-1
/*     33e4:	afb80028 */ 	sw	$t8,0x28($sp)
/*     33e8:	0c012230 */ 	jal	osGetThreadPri
/*     33ec:	00002025 */ 	or	$a0,$zero,$zero
/*     33f0:	8fb90030 */ 	lw	$t9,0x30($sp)
/*     33f4:	00002025 */ 	or	$a0,$zero,$zero
/*     33f8:	0059082a */ 	slt	$at,$v0,$t9
/*     33fc:	10200003 */ 	beqz	$at,.L0000340c
/*     3400:	03202825 */ 	or	$a1,$t9,$zero
/*     3404:	0c01210c */ 	jal	osSetThreadPri
/*     3408:	afa20028 */ 	sw	$v0,0x28($sp)
.L0000340c:
/*     340c:	0c01256c */ 	jal	__osDisableInt
/*     3410:	00000000 */ 	nop
/*     3414:	8fa90034 */ 	lw	$t1,0x34($sp)
/*     3418:	8faf0030 */ 	lw	$t7,0x30($sp)
/*     341c:	3c048009 */ 	lui	$a0,%hi(piThread)
/*     3420:	3c0a8009 */ 	lui	$t2,%hi(piEventQueue)
/*     3424:	3c0b800a */ 	lui	$t3,%hi(__osPiAccessQueue)
/*     3428:	3c0c7005 */ 	lui	$t4,%hi(osPiRawStartDma)
/*     342c:	3c0d7005 */ 	lui	$t5,%hi(osEPiRawStartDma)
/*     3430:	3c0e8009 */ 	lui	$t6,%hi(piEventQueue)
/*     3434:	24840390 */ 	addiu	$a0,$a0,%lo(piThread)
/*     3438:	24080001 */ 	addiu	$t0,$zero,0x1
/*     343c:	254a07c0 */ 	addiu	$t2,$t2,%lo(piEventQueue)
/*     3440:	256bc7a8 */ 	addiu	$t3,$t3,%lo(__osPiAccessQueue)
/*     3444:	258c9b50 */ 	addiu	$t4,$t4,%lo(osPiRawStartDma)
/*     3448:	25ad9c20 */ 	addiu	$t5,$t5,%lo(osEPiRawStartDma)
/*     344c:	25ce07c0 */ 	addiu	$t6,$t6,%lo(piEventQueue)
/*     3450:	3c067005 */ 	lui	$a2,%hi(__osDevMgrMain)
/*     3454:	afa2002c */ 	sw	$v0,0x2c($sp)
/*     3458:	ae080000 */ 	sw	$t0,0x0($s0)
/*     345c:	ae040004 */ 	sw	$a0,0x4($s0)
/*     3460:	ae0a000c */ 	sw	$t2,0xc($s0)
/*     3464:	ae0b0010 */ 	sw	$t3,0x10($s0)
/*     3468:	ae0c0014 */ 	sw	$t4,0x14($s0)
/*     346c:	ae0d0018 */ 	sw	$t5,0x18($s0)
/*     3470:	24c69e00 */ 	addiu	$a2,$a2,%lo(__osDevMgrMain)
/*     3474:	afae0010 */ 	sw	$t6,0x10($sp)
/*     3478:	00002825 */ 	or	$a1,$zero,$zero
/*     347c:	02003825 */ 	or	$a3,$s0,$zero
/*     3480:	ae090008 */ 	sw	$t1,0x8($s0)
/*     3484:	0c000fb8 */ 	jal	osCreateThread
/*     3488:	afaf0014 */ 	sw	$t7,0x14($sp)
/*     348c:	3c048009 */ 	lui	$a0,%hi(piThread)
/*     3490:	0c01207c */ 	jal	osStartThread
/*     3494:	24840390 */ 	addiu	$a0,$a0,%lo(piThread)
/*     3498:	0c012588 */ 	jal	__osRestoreInt
/*     349c:	8fa4002c */ 	lw	$a0,0x2c($sp)
/*     34a0:	8fb80028 */ 	lw	$t8,0x28($sp)
/*     34a4:	2401ffff */ 	addiu	$at,$zero,-1
/*     34a8:	00002025 */ 	or	$a0,$zero,$zero
/*     34ac:	53010004 */ 	beql	$t8,$at,.L000034c0
/*     34b0:	8fbf0024 */ 	lw	$ra,0x24($sp)
/*     34b4:	0c01210c */ 	jal	osSetThreadPri
/*     34b8:	03002825 */ 	or	$a1,$t8,$zero
.L000034bc:
/*     34bc:	8fbf0024 */ 	lw	$ra,0x24($sp)
.L000034c0:
/*     34c0:	8fb00020 */ 	lw	$s0,0x20($sp)
/*     34c4:	27bd0030 */ 	addiu	$sp,$sp,0x30
/*     34c8:	03e00008 */ 	jr	$ra
/*     34cc:	00000000 */ 	nop
);
