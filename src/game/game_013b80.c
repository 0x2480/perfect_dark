#include <ultra64.h>
#include "constants.h"
#include "bss.h"
#include "lib/memp.h"
#include "data.h"
#include "types.h"

void func0f013b80(void)
{
	g_TexCacheCount = 0;
	var800aabc8.unk00 = NULL;
	var800aabc8.unk04 = NULL;
	var800aabc8.unk0c = NULL;
}

void func0f013ba0(void)
{
	s32 i;
	s32 j;
	s32 num;
	s32 val;

	for (i = 0; i < 4; i++) {
		if (PLAYERCOUNT() >= 2) {
			val = var8007e3d0[i].valifmp;
			num = var8007e3d0[i].numifmp;
		} else if (g_Vars.stagenum >= STAGE_TITLE) {
			val = var8007e3d0[i].valifspecial;
			num = var8007e3d0[i].numifspecial;
		} else {
			val = var8007e3d0[i].valifsp;
			num = var8007e3d0[i].numifsp;
		}

		if (num > 0) {
			var8007e3d0[i].unk24 = mempAlloc(num * sizeof(struct var8007e3d0_data), MEMPOOL_STAGE);
		}

		for (j = 0; j < num; j++) {
			var8007e3d0[i].unk24[j].unk0e = 0;
		}

		var8007e3d0[i].numallocated = num;
		var8007e3d0[i].val1 = val;
		var8007e3d0[i].val2 = val;
	}
}
