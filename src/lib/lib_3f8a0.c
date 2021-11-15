#include <ultra64.h>
#include "constants.h"
#include "lib/lib_3e8c0.h"
#include "lib/lib_43dd0.h"
#include "lib/lib_45ed0.h"
#include "lib/lib_461c0.h"
#include "lib/lib_46650.h"
#include "lib/lib_47550.h"
#include "lib/libc/ll.h"
#include "data.h"
#include "types.h"

u8 var8009c400[0x90];
u8 var8009c490[0x120];
u8 var8009c5b0[0x90];
u8 *var8009c640;
u8 *var8009c644;
u32 var8009c648;

u32 var8005f670 = 0x00000000;
u32 var8005f674 = (u32) &var70054b40;
u32 var8005f678 = (u32) &var70054b68;
u32 var8005f67c = (u32) &var70054bb8;
u32 var8005f680 = (u32) &var70054c08;
u32 var8005f684 = (u32) &var70054c08;
u32 var8005f688 = (u32) &var70054c90;
u32 var8005f68c = (u32) &var70054d18;
u32 var8005f690 = (u32) &var70054e40;
u32 var8005f694 = (u32) &var70054f68;
u32 var8005f698 = (u32) &var70055090;
u32 var8005f69c = (u32) &var70055298;
u32 var8005f6a0 = (u32) &var700554a0;
u32 var8005f6a4 = (u32) &var700556a8;
u32 var8005f6a8 = (u32) &var70055eb0;
u32 var8005f6ac = (u32) &var70055eb0;
u32 var8005f6b0 = (u32) &var700566b8;
u32 var8005f6b4 = (u32) &var700566b8;
u32 var8005f6b8 = (u32) &var700566b8;
u32 var8005f6bc = (u32) &var700566b8;
u32 var8005f6c0 = (u32) &var700566b8;
u32 var8005f6c4 = (u32) &var700566b8;
u32 var8005f6c8 = (u32) &var700566b8;
u32 var8005f6cc = (u32) &var700566b8;
u32 var8005f6d0 = (u32) &var70056ec0;
u32 var8005f6d4 = (u32) &var70056ec0;
u32 var8005f6d8 = (u32) &var70056ec0;
u32 var8005f6dc = (u32) &var70056ec0;
u32 var8005f6e0 = (u32) &var70056ec0;
u32 var8005f6e4 = (u32) &var70056ec0;
u32 var8005f6e8 = (u32) &var70056ec0;
u32 var8005f6ec = (u32) &var70056ec0;
u32 var8005f6f0 = (u32) &var700576c8;
u32 var8005f6f4 = (u32) &var70057750;
u8 *var8005f6f8 = NULL;
u8 *var8005f6fc = NULL;

const u32 var70054b40[] = {0x00000100};
const u32 var70054b44[] = {0x00000001};
const u32 var70054b48[] = {0x00010300};
const u32 var70054b4c[] = {0x00000004};
const u32 var70054b50[] = {0x01000200};
const u32 var70054b54[] = {0x00000002};
const u32 var70054b58[] = {0x01010300};
const u32 var70054b5c[] = {0x00000000};
const u32 var70054b60[] = {0x64646400};
const u32 var70054b64[] = {0x00000000};
const u32 var70054b68[] = {0x00000100};
const u32 var70054b6c[] = {0x00000001};
const u32 var70054b70[] = {0x00010300};
const u32 var70054b74[] = {0x00000002};
const u32 var70054b78[] = {0x00020600};
const u32 var70054b7c[] = {0x00000020};
const u32 var70054b80[] = {0x01000300};
const u32 var70054b84[] = {0x00000006};
const u32 var70054b88[] = {0x01010300};
const u32 var70054b8c[] = {0x00000004};
const u32 var70054b90[] = {0x01020500};
const u32 var70054b94[] = {0x00000010};
const u32 var70054b98[] = {0x02000500};
const u32 var70054b9c[] = {0x00000018};
const u32 var70054ba0[] = {0x02010500};
const u32 var70054ba4[] = {0x00000008};
const u32 var70054ba8[] = {0x02020600};
const u32 var70054bac[] = {0x00000000};
const u32 var70054bb0[] = {0x64646400};
const u32 var70054bb4[] = {0x00000000};
const u32 var70054bb8[] = {0x00000200};
const u32 var70054bbc[] = {0x00000003};
const u32 var70054bc0[] = {0x00010200};
const u32 var70054bc4[] = {0x00000001};
const u32 var70054bc8[] = {0x00020600};
const u32 var70054bcc[] = {0x00000020};
const u32 var70054bd0[] = {0x01000300};
const u32 var70054bd4[] = {0x00000004};
const u32 var70054bd8[] = {0x01010200};
const u32 var70054bdc[] = {0x00000002};
const u32 var70054be0[] = {0x01020500};
const u32 var70054be4[] = {0x00000010};
const u32 var70054be8[] = {0x02000500};
const u32 var70054bec[] = {0x00000018};
const u32 var70054bf0[] = {0x02010500};
const u32 var70054bf4[] = {0x00000008};
const u32 var70054bf8[] = {0x02020600};
const u32 var70054bfc[] = {0x00000000};
const u32 var70054c00[] = {0x64646400};
const u32 var70054c04[] = {0x00000000};
const u32 var70054c08[] = {0x00000100};
const u32 var70054c0c[] = {0x00000001};
const u32 var70054c10[] = {0x00010300};
const u32 var70054c14[] = {0x00000002};
const u32 var70054c18[] = {0x00020600};
const u32 var70054c1c[] = {0x00000018};
const u32 var70054c20[] = {0x00030700};
const u32 var70054c24[] = {0x00000050};
const u32 var70054c28[] = {0x01000300};
const u32 var70054c2c[] = {0x00000006};
const u32 var70054c30[] = {0x01010300};
const u32 var70054c34[] = {0x00000004};
const u32 var70054c38[] = {0x01020600};
const u32 var70054c3c[] = {0x00000008};
const u32 var70054c40[] = {0x01030700};
const u32 var70054c44[] = {0x00000010};
const u32 var70054c48[] = {0x02000600};
const u32 var70054c4c[] = {0x00000038};
const u32 var70054c50[] = {0x02010600};
const u32 var70054c54[] = {0x00000028};
const u32 var70054c58[] = {0x02020700};
const u32 var70054c5c[] = {0x00000070};
const u32 var70054c60[] = {0x02030800};
const u32 var70054c64[] = {0x00000080};
const u32 var70054c68[] = {0x03000700};
const u32 var70054c6c[] = {0x00000030};
const u32 var70054c70[] = {0x03010600};
const u32 var70054c74[] = {0x00000020};
const u32 var70054c78[] = {0x03020700};
const u32 var70054c7c[] = {0x00000040};
const u32 var70054c80[] = {0x03030800};
const u32 var70054c84[] = {0x00000000};
const u32 var70054c88[] = {0x64646400};
const u32 var70054c8c[] = {0x00000000};
const u32 var70054c90[] = {0x00000300};
const u32 var70054c94[] = {0x00000007};
const u32 var70054c98[] = {0x00010300};
const u32 var70054c9c[] = {0x00000006};
const u32 var70054ca0[] = {0x00020500};
const u32 var70054ca4[] = {0x00000014};
const u32 var70054ca8[] = {0x00030700};
const u32 var70054cac[] = {0x00000040};
const u32 var70054cb0[] = {0x01000300};
const u32 var70054cb4[] = {0x00000003};
const u32 var70054cb8[] = {0x01010200};
const u32 var70054cbc[] = {0x00000001};
const u32 var70054cc0[] = {0x01020400};
const u32 var70054cc4[] = {0x0000000c};
const u32 var70054cc8[] = {0x01030500};
const u32 var70054ccc[] = {0x00000008};
const u32 var70054cd0[] = {0x02000400};
const u32 var70054cd4[] = {0x0000000a};
const u32 var70054cd8[] = {0x02010400};
const u32 var70054cdc[] = {0x00000002};
const u32 var70054ce0[] = {0x02020500};
const u32 var70054ce4[] = {0x00000004};
const u32 var70054ce8[] = {0x02030600};
const u32 var70054cec[] = {0x00000020};
const u32 var70054cf0[] = {0x03000600};
const u32 var70054cf4[] = {0x00000030};
const u32 var70054cf8[] = {0x03010500};
const u32 var70054cfc[] = {0x00000018};
const u32 var70054d00[] = {0x03020600};
const u32 var70054d04[] = {0x00000010};
const u32 var70054d08[] = {0x03030700};
const u32 var70054d0c[] = {0x00000000};
const u32 var70054d10[] = {0x64646400};
const u32 var70054d14[] = {0x00000000};
const u32 var70054d18[] = {0x00000100};
const u32 var70054d1c[] = {0x00000001};
const u32 var70054d20[] = {0x00010300};
const u32 var70054d24[] = {0x00000002};
const u32 var70054d28[] = {0x00020600};
const u32 var70054d2c[] = {0x00000014};
const u32 var70054d30[] = {0x00030800};
const u32 var70054d34[] = {0x000000c8};
const u32 var70054d38[] = {0x00040800};
const u32 var70054d3c[] = {0x00000008};
const u32 var70054d40[] = {0x00050900};
const u32 var70054d44[] = {0x000000a0};
const u32 var70054d48[] = {0x01000300};
const u32 var70054d4c[] = {0x00000006};
const u32 var70054d50[] = {0x01010400};
const u32 var70054d54[] = {0x0000000c};
const u32 var70054d58[] = {0x01020600};
const u32 var70054d5c[] = {0x00000038};
const u32 var70054d60[] = {0x01030700};
const u32 var70054d64[] = {0x00000028};
const u32 var70054d68[] = {0x01040700};
const u32 var70054d6c[] = {0x00000050};
const u32 var70054d70[] = {0x01050800};
const u32 var70054d74[] = {0x000000c0};
const u32 var70054d78[] = {0x02000600};
const u32 var70054d7c[] = {0x00000034};
const u32 var70054d80[] = {0x02010500};
const u32 var70054d84[] = {0x00000004};
const u32 var70054d88[] = {0x02020700};
const u32 var70054d8c[] = {0x00000058};
const u32 var70054d90[] = {0x02030800};
const u32 var70054d94[] = {0x00000088};
const u32 var70054d98[] = {0x02040800};
const u32 var70054d9c[] = {0x00000010};
const u32 var70054da0[] = {0x02050900};
const u32 var70054da4[] = {0x00000040};
const u32 var70054da8[] = {0x03000700};
const u32 var70054dac[] = {0x00000018};
const u32 var70054db0[] = {0x03010700};
const u32 var70054db4[] = {0x00000068};
const u32 var70054db8[] = {0x03020800};
const u32 var70054dbc[] = {0x00000048};
const u32 var70054dc0[] = {0x03030900};
const u32 var70054dc4[] = {0x000001e0};
const u32 var70054dc8[] = {0x03040900};
const u32 var70054dcc[] = {0x000001a0};
const u32 var70054dd0[] = {0x03050900};
const u32 var70054dd4[] = {0x00000080};
const u32 var70054dd8[] = {0x04000700};
const u32 var70054ddc[] = {0x00000070};
const u32 var70054de0[] = {0x04010700};
const u32 var70054de4[] = {0x00000030};
const u32 var70054de8[] = {0x04020800};
const u32 var70054dec[] = {0x00000090};
const u32 var70054df0[] = {0x04030900};
const u32 var70054df4[] = {0x000000e0};
const u32 var70054df8[] = {0x04040900};
const u32 var70054dfc[] = {0x00000180};
const u32 var70054e00[] = {0x04050a00};
const u32 var70054e04[] = {0x00000200};
const u32 var70054e08[] = {0x05000800};
const u32 var70054e0c[] = {0x00000060};
const u32 var70054e10[] = {0x05010800};
const u32 var70054e14[] = {0x00000020};
const u32 var70054e18[] = {0x05020900};
const u32 var70054e1c[] = {0x00000140};
const u32 var70054e20[] = {0x05030a00};
const u32 var70054e24[] = {0x00000300};
const u32 var70054e28[] = {0x05040a00};
const u32 var70054e2c[] = {0x00000100};
const u32 var70054e30[] = {0x05050a00};
const u32 var70054e34[] = {0x00000000};
const u32 var70054e38[] = {0x64646400};
const u32 var70054e3c[] = {0x00000000};
const u32 var70054e40[] = {0x00000200};
const u32 var70054e44[] = {0x00000003};
const u32 var70054e48[] = {0x00010300};
const u32 var70054e4c[] = {0x00000001};
const u32 var70054e50[] = {0x00020600};
const u32 var70054e54[] = {0x00000018};
const u32 var70054e58[] = {0x00030800};
const u32 var70054e5c[] = {0x00000048};
const u32 var70054e60[] = {0x00040800};
const u32 var70054e64[] = {0x00000030};
const u32 var70054e68[] = {0x00050900};
const u32 var70054e6c[] = {0x00000140};
const u32 var70054e70[] = {0x01000300};
const u32 var70054e74[] = {0x00000005};
const u32 var70054e78[] = {0x01010200};
const u32 var70054e7c[] = {0x00000002};
const u32 var70054e80[] = {0x01020400};
const u32 var70054e84[] = {0x00000004};
const u32 var70054e88[] = {0x01030800};
const u32 var70054e8c[] = {0x00000008};
const u32 var70054e90[] = {0x01040800};
const u32 var70054e94[] = {0x00000090};
const u32 var70054e98[] = {0x01050800};
const u32 var70054e9c[] = {0x000000c0};
const u32 var70054ea0[] = {0x02000600};
const u32 var70054ea4[] = {0x00000038};
const u32 var70054ea8[] = {0x02010400};
const u32 var70054eac[] = {0x0000000c};
const u32 var70054eb0[] = {0x02020600};
const u32 var70054eb4[] = {0x00000028};
const u32 var70054eb8[] = {0x02030800};
const u32 var70054ebc[] = {0x00000070};
const u32 var70054ec0[] = {0x02040800};
const u32 var70054ec4[] = {0x000000e0};
const u32 var70054ec8[] = {0x02050900};
const u32 var70054ecc[] = {0x00000180};
const u32 var70054ed0[] = {0x03000800};
const u32 var70054ed4[] = {0x000000c8};
const u32 var70054ed8[] = {0x03010800};
const u32 var70054edc[] = {0x00000088};
const u32 var70054ee0[] = {0x03020800};
const u32 var70054ee4[] = {0x000000f0};
const u32 var70054ee8[] = {0x03030900};
const u32 var70054eec[] = {0x00000160};
const u32 var70054ef0[] = {0x03040900};
const u32 var70054ef4[] = {0x000000a0};
const u32 var70054ef8[] = {0x03050a00};
const u32 var70054efc[] = {0x00000080};
const u32 var70054f00[] = {0x04000800};
const u32 var70054f04[] = {0x000000b0};
const u32 var70054f08[] = {0x04010700};
const u32 var70054f0c[] = {0x00000050};
const u32 var70054f10[] = {0x04020800};
const u32 var70054f14[] = {0x00000010};
const u32 var70054f18[] = {0x04030900};
const u32 var70054f1c[] = {0x000001a0};
const u32 var70054f20[] = {0x04040a00};
const u32 var70054f24[] = {0x00000280};
const u32 var70054f28[] = {0x04050a00};
const u32 var70054f2c[] = {0x00000200};
const u32 var70054f30[] = {0x05000900};
const u32 var70054f34[] = {0x00000060};
const u32 var70054f38[] = {0x05010800};
const u32 var70054f3c[] = {0x00000020};
const u32 var70054f40[] = {0x05020900};
const u32 var70054f44[] = {0x00000040};
const u32 var70054f48[] = {0x05030900};
const u32 var70054f4c[] = {0x00000100};
const u32 var70054f50[] = {0x05040b00};
const u32 var70054f54[] = {0x00000400};
const u32 var70054f58[] = {0x05050b00};
const u32 var70054f5c[] = {0x00000000};
const u32 var70054f60[] = {0x64646400};
const u32 var70054f64[] = {0x00000000};
const u32 var70054f68[] = {0x00000300};
const u32 var70054f6c[] = {0x00000007};
const u32 var70054f70[] = {0x00010300};
const u32 var70054f74[] = {0x00000005};
const u32 var70054f78[] = {0x00020500};
const u32 var70054f7c[] = {0x00000012};
const u32 var70054f80[] = {0x00030600};
const u32 var70054f84[] = {0x0000001c};
const u32 var70054f88[] = {0x00040800};
const u32 var70054f8c[] = {0x000000f0};
const u32 var70054f90[] = {0x00050900};
const u32 var70054f94[] = {0x000001c0};
const u32 var70054f98[] = {0x01000300};
const u32 var70054f9c[] = {0x00000003};
const u32 var70054fa0[] = {0x01010300};
const u32 var70054fa4[] = {0x00000001};
const u32 var70054fa8[] = {0x01020400};
const u32 var70054fac[] = {0x0000000a};
const u32 var70054fb0[] = {0x01030500};
const u32 var70054fb4[] = {0x00000014};
const u32 var70054fb8[] = {0x01040600};
const u32 var70054fbc[] = {0x00000018};
const u32 var70054fc0[] = {0x01050800};
const u32 var70054fc4[] = {0x000000e0};
const u32 var70054fc8[] = {0x02000400};
const u32 var70054fcc[] = {0x0000000e};
const u32 var70054fd0[] = {0x02010400};
const u32 var70054fd4[] = {0x00000006};
const u32 var70054fd8[] = {0x02020500};
const u32 var70054fdc[] = {0x00000002};
const u32 var70054fe0[] = {0x02030600};
const u32 var70054fe4[] = {0x00000004};
const u32 var70054fe8[] = {0x02040700};
const u32 var70054fec[] = {0x00000008};
const u32 var70054ff0[] = {0x02050800};
const u32 var70054ff4[] = {0x000000a0};
const u32 var70054ff8[] = {0x03000600};
const u32 var70054ffc[] = {0x0000003c};
const u32 var70055000[] = {0x03010500};
const u32 var70055004[] = {0x0000000c};
const u32 var70055008[] = {0x03020600};
const u32 var7005500c[] = {0x00000024};
const u32 var70055010[] = {0x03030700};
const u32 var70055014[] = {0x00000028};
const u32 var70055018[] = {0x03040700};
const u32 var7005501c[] = {0x00000050};
const u32 var70055020[] = {0x03050800};
const u32 var70055024[] = {0x00000080};
const u32 var70055028[] = {0x04000700};
const u32 var7005502c[] = {0x00000068};
const u32 var70055030[] = {0x04010600};
const u32 var70055034[] = {0x00000038};
const u32 var70055038[] = {0x04020700};
const u32 var7005503c[] = {0x00000048};
const u32 var70055040[] = {0x04030700};
const u32 var70055044[] = {0x00000030};
const u32 var70055048[] = {0x04040800};
const u32 var7005504c[] = {0x00000020};
const u32 var70055050[] = {0x04050900};
const u32 var70055054[] = {0x00000100};
const u32 var70055058[] = {0x05000800};
const u32 var7005505c[] = {0x00000070};
const u32 var70055060[] = {0x05010700};
const u32 var70055064[] = {0x00000010};
const u32 var70055068[] = {0x05020800};
const u32 var7005506c[] = {0x00000060};
const u32 var70055070[] = {0x05030800};
const u32 var70055074[] = {0x00000040};
const u32 var70055078[] = {0x05040900};
const u32 var7005507c[] = {0x000000c0};
const u32 var70055080[] = {0x05050900};
const u32 var70055084[] = {0x00000000};
const u32 var70055088[] = {0x64646400};
const u32 var7005508c[] = {0x00000000};
const u32 var70055090[] = {0x00000100};
const u32 var70055094[] = {0x00000001};
const u32 var70055098[] = {0x00010300};
const u32 var7005509c[] = {0x00000002};
const u32 var700550a0[] = {0x00020600};
const u32 var700550a4[] = {0x00000014};
const u32 var700550a8[] = {0x00030800};
const u32 var700550ac[] = {0x000000e8};
const u32 var700550b0[] = {0x00040900};
const u32 var700550b4[] = {0x00000188};
const u32 var700550b8[] = {0x00050900};
const u32 var700550bc[] = {0x000000f0};
const u32 var700550c0[] = {0x00060900};
const u32 var700550c4[] = {0x00000060};
const u32 var700550c8[] = {0x00070a00};
const u32 var700550cc[] = {0x00000220};
const u32 var700550d0[] = {0x01000300};
const u32 var700550d4[] = {0x00000006};
const u32 var700550d8[] = {0x01010400};
const u32 var700550dc[] = {0x0000000c};
const u32 var700550e0[] = {0x01020600};
const u32 var700550e4[] = {0x00000004};
const u32 var700550e8[] = {0x01030700};
const u32 var700550ec[] = {0x00000018};
const u32 var700550f0[] = {0x01040800};
const u32 var700550f4[] = {0x00000048};
const u32 var700550f8[] = {0x01050900};
const u32 var700550fc[] = {0x00000150};
const u32 var70055100[] = {0x01060800};
const u32 var70055104[] = {0x00000030};
const u32 var70055108[] = {0x01070800};
const u32 var7005510c[] = {0x000000e0};
const u32 var70055110[] = {0x02000600};
const u32 var70055114[] = {0x00000034};
const u32 var70055118[] = {0x02010600};
const u32 var7005511c[] = {0x00000024};
const u32 var70055120[] = {0x02020700};
const u32 var70055124[] = {0x00000078};
const u32 var70055128[] = {0x02030800};
const u32 var7005512c[] = {0x000000a8};
const u32 var70055130[] = {0x02040900};
const u32 var70055134[] = {0x00000008};
const u32 var70055138[] = {0x02050a00};
const u32 var7005513c[] = {0x00000050};
const u32 var70055140[] = {0x02060900};
const u32 var70055144[] = {0x00000190};
const u32 var70055148[] = {0x02070900};
const u32 var7005514c[] = {0x000000c0};
const u32 var70055150[] = {0x03000700};
const u32 var70055154[] = {0x00000038};
const u32 var70055158[] = {0x03010700};
const u32 var7005515c[] = {0x00000058};
const u32 var70055160[] = {0x03020800};
const u32 var70055164[] = {0x00000068};
const u32 var70055168[] = {0x03030900};
const u32 var7005516c[] = {0x00000088};
const u32 var70055170[] = {0x03040a00};
const u32 var70055174[] = {0x000001d0};
const u32 var70055178[] = {0x03050a00};
const u32 var7005517c[] = {0x000003a0};
const u32 var70055180[] = {0x03060900};
const u32 var70055184[] = {0x00000090};
const u32 var70055188[] = {0x03070a00};
const u32 var7005518c[] = {0x00000380};
const u32 var70055190[] = {0x04000800};
const u32 var70055194[] = {0x00000028};
const u32 var70055198[] = {0x04010800};
const u32 var7005519c[] = {0x000000c8};
const u32 var700551a0[] = {0x04020900};
const u32 var700551a4[] = {0x00000108};
const u32 var700551a8[] = {0x04030a00};
const u32 var700551ac[] = {0x000003d0};
const u32 var700551b0[] = {0x04040a00};
const u32 var700551b4[] = {0x00000360};
const u32 var700551b8[] = {0x04050a00};
const u32 var700551bc[] = {0x000001a0};
const u32 var700551c0[] = {0x04060a00};
const u32 var700551c4[] = {0x00000240};
const u32 var700551c8[] = {0x04070a00};
const u32 var700551cc[] = {0x00000300};
const u32 var700551d0[] = {0x05000900};
const u32 var700551d4[] = {0x000001f0};
const u32 var700551d8[] = {0x05010900};
const u32 var700551dc[] = {0x000000d0};
const u32 var700551e0[] = {0x05020a00};
const u32 var700551e4[] = {0x00000250};
const u32 var700551e8[] = {0x05030a00};
const u32 var700551ec[] = {0x00000160};
const u32 var700551f0[] = {0x05040b00};
const u32 var700551f4[] = {0x00000540};
const u32 var700551f8[] = {0x05050b00};
const u32 var700551fc[] = {0x00000140};
const u32 var70055200[] = {0x05060a00};
const u32 var70055204[] = {0x00000280};
const u32 var70055208[] = {0x05070b00};
const u32 var7005520c[] = {0x00000600};
const u32 var70055210[] = {0x06000800};
const u32 var70055214[] = {0x00000070};
const u32 var70055218[] = {0x06010800};
const u32 var7005521c[] = {0x000000b0};
const u32 var70055220[] = {0x06020900};
const u32 var70055224[] = {0x000000a0};
const u32 var70055228[] = {0x06030a00};
const u32 var7005522c[] = {0x00000340};
const u32 var70055230[] = {0x06040a00};
const u32 var70055234[] = {0x00000020};
const u32 var70055238[] = {0x06050a00};
const u32 var7005523c[] = {0x00000180};
const u32 var70055240[] = {0x06060b00};
const u32 var70055244[] = {0x00000500};
const u32 var70055248[] = {0x06070b00};
const u32 var7005524c[] = {0x00000400};
const u32 var70055250[] = {0x07000900};
const u32 var70055254[] = {0x00000120};
const u32 var70055258[] = {0x07010800};
const u32 var7005525c[] = {0x00000010};
const u32 var70055260[] = {0x07020900};
const u32 var70055264[] = {0x000001c0};
const u32 var70055268[] = {0x07030a00};
const u32 var7005526c[] = {0x00000040};
const u32 var70055270[] = {0x07040a00};
const u32 var70055274[] = {0x00000080};
const u32 var70055278[] = {0x07050b00};
const u32 var7005527c[] = {0x00000100};
const u32 var70055280[] = {0x07060b00};
const u32 var70055284[] = {0x00000200};
const u32 var70055288[] = {0x07070b00};
const u32 var7005528c[] = {0x00000000};
const u32 var70055290[] = {0x64646400};
const u32 var70055294[] = {0x00000000};
const u32 var70055298[] = {0x00000200};
const u32 var7005529c[] = {0x00000003};
const u32 var700552a0[] = {0x00010300};
const u32 var700552a4[] = {0x00000001};
const u32 var700552a8[] = {0x00020500};
const u32 var700552ac[] = {0x0000000a};
const u32 var700552b0[] = {0x00030700};
const u32 var700552b4[] = {0x0000000c};
const u32 var700552b8[] = {0x00040800};
const u32 var700552bc[] = {0x00000044};
const u32 var700552c0[] = {0x00050900};
const u32 var700552c4[] = {0x00000108};
const u32 var700552c8[] = {0x00060800};
const u32 var700552cc[] = {0x000000a8};
const u32 var700552d0[] = {0x00070900};
const u32 var700552d4[] = {0x000001e0};
const u32 var700552d8[] = {0x01000300};
const u32 var700552dc[] = {0x00000005};
const u32 var700552e0[] = {0x01010300};
const u32 var700552e4[] = {0x00000006};
const u32 var700552e8[] = {0x01020400};
const u32 var700552ec[] = {0x00000002};
const u32 var700552f0[] = {0x01030600};
const u32 var700552f4[] = {0x00000014};
const u32 var700552f8[] = {0x01040800};
const u32 var700552fc[] = {0x00000004};
const u32 var70055300[] = {0x01050800};
const u32 var70055304[] = {0x00000088};
const u32 var70055308[] = {0x01060700};
const u32 var7005530c[] = {0x00000068};
const u32 var70055310[] = {0x01070800};
const u32 var70055314[] = {0x00000050};
const u32 var70055318[] = {0x02000500};
const u32 var7005531c[] = {0x0000001a};
const u32 var70055320[] = {0x02010500};
const u32 var70055324[] = {0x0000001c};
const u32 var70055328[] = {0x02020600};
const u32 var7005532c[] = {0x0000002c};
const u32 var70055330[] = {0x02030700};
const u32 var70055334[] = {0x00000024};
const u32 var70055338[] = {0x02040800};
const u32 var7005533c[] = {0x00000078};
const u32 var70055340[] = {0x02050900};
const u32 var70055344[] = {0x000001f0};
const u32 var70055348[] = {0x02060800};
const u32 var7005534c[] = {0x00000028};
const u32 var70055350[] = {0x02070800};
const u32 var70055354[] = {0x000000a0};
const u32 var70055358[] = {0x03000700};
const u32 var7005535c[] = {0x0000004c};
const u32 var70055360[] = {0x03010600};
const u32 var70055364[] = {0x00000034};
const u32 var70055368[] = {0x03020700};
const u32 var7005536c[] = {0x00000064};
const u32 var70055370[] = {0x03030900};
const u32 var70055374[] = {0x000001b8};
const u32 var70055378[] = {0x03040800};
const u32 var7005537c[] = {0x000000d8};
const u32 var70055380[] = {0x03050a00};
const u32 var70055384[] = {0x00000120};
const u32 var70055388[] = {0x03060800};
const u32 var7005538c[] = {0x00000030};
const u32 var70055390[] = {0x03070900};
const u32 var70055394[] = {0x00000140};
const u32 var70055398[] = {0x04000800};
const u32 var7005539c[] = {0x000000c4};
const u32 var700553a0[] = {0x04010800};
const u32 var700553a4[] = {0x00000084};
const u32 var700553a8[] = {0x04020800};
const u32 var700553ac[] = {0x000000f8};
const u32 var700553b0[] = {0x04030900};
const u32 var700553b4[] = {0x000000b8};
const u32 var700553b8[] = {0x04040900};
const u32 var700553bc[] = {0x000000f0};
const u32 var700553c0[] = {0x04050a00};
const u32 var700553c4[] = {0x00000020};
const u32 var700553c8[] = {0x04060900};
const u32 var700553cc[] = {0x000001c0};
const u32 var700553d0[] = {0x04070a00};
const u32 var700553d4[] = {0x00000280};
const u32 var700553d8[] = {0x05000800};
const u32 var700553dc[] = {0x00000038};
const u32 var700553e0[] = {0x05010800};
const u32 var700553e4[] = {0x00000058};
const u32 var700553e8[] = {0x05020900};
const u32 var700553ec[] = {0x00000008};
const u32 var700553f0[] = {0x05030a00};
const u32 var700553f4[] = {0x00000320};
const u32 var700553f8[] = {0x05040a00};
const u32 var700553fc[] = {0x00000220};
const u32 var70055400[] = {0x05050b00};
const u32 var70055404[] = {0x00000780};
const u32 var70055408[] = {0x05060a00};
const u32 var7005540c[] = {0x00000040};
const u32 var70055410[] = {0x05070b00};
const u32 var70055414[] = {0x00000380};
const u32 var70055418[] = {0x06000800};
const u32 var7005541c[] = {0x00000070};
const u32 var70055420[] = {0x06010700};
const u32 var70055424[] = {0x00000018};
const u32 var70055428[] = {0x06020700};
const u32 var7005542c[] = {0x00000048};
const u32 var70055430[] = {0x06030800};
const u32 var70055434[] = {0x000000b0};
const u32 var70055438[] = {0x06040900};
const u32 var7005543c[] = {0x000000e0};
const u32 var70055440[] = {0x06050a00};
const u32 var70055444[] = {0x00000240};
const u32 var70055448[] = {0x06060a00};
const u32 var7005544c[] = {0x00000080};
const u32 var70055450[] = {0x06070a00};
const u32 var70055454[] = {0x00000200};
const u32 var70055458[] = {0x07000800};
const u32 var7005545c[] = {0x000000d0};
const u32 var70055460[] = {0x07010700};
const u32 var70055464[] = {0x00000010};
const u32 var70055468[] = {0x07020800};
const u32 var7005546c[] = {0x00000060};
const u32 var70055470[] = {0x07030900};
const u32 var70055474[] = {0x000000c0};
const u32 var70055478[] = {0x07040a00};
const u32 var7005547c[] = {0x00000180};
const u32 var70055480[] = {0x07050a00};
const u32 var70055484[] = {0x00000300};
const u32 var70055488[] = {0x07060a00};
const u32 var7005548c[] = {0x00000100};
const u32 var70055490[] = {0x07070a00};
const u32 var70055494[] = {0x00000000};
const u32 var70055498[] = {0x64646400};
const u32 var7005549c[] = {0x00000000};
const u32 var700554a0[] = {0x00000400};
const u32 var700554a4[] = {0x00000009};
const u32 var700554a8[] = {0x00010300};
const u32 var700554ac[] = {0x00000003};
const u32 var700554b0[] = {0x00020500};
const u32 var700554b4[] = {0x00000001};
const u32 var700554b8[] = {0x00030700};
const u32 var700554bc[] = {0x00000042};
const u32 var700554c0[] = {0x00040800};
const u32 var700554c4[] = {0x00000094};
const u32 var700554c8[] = {0x00050900};
const u32 var700554cc[] = {0x000001c8};
const u32 var700554d0[] = {0x00060900};
const u32 var700554d4[] = {0x000000c8};
const u32 var700554d8[] = {0x00070900};
const u32 var700554dc[] = {0x000000b0};
const u32 var700554e0[] = {0x01000300};
const u32 var700554e4[] = {0x00000007};
const u32 var700554e8[] = {0x01010300};
const u32 var700554ec[] = {0x00000005};
const u32 var700554f0[] = {0x01020400};
const u32 var700554f4[] = {0x00000006};
const u32 var700554f8[] = {0x01030500};
const u32 var700554fc[] = {0x00000012};
const u32 var70055500[] = {0x01040700};
const u32 var70055504[] = {0x00000074};
const u32 var70055508[] = {0x01050700};
const u32 var7005550c[] = {0x00000004};
const u32 var70055510[] = {0x01060800};
const u32 var70055514[] = {0x00000058};
const u32 var70055518[] = {0x01070800};
const u32 var7005551c[] = {0x000000d0};
const u32 var70055520[] = {0x02000500};
const u32 var70055524[] = {0x00000011};
const u32 var70055528[] = {0x02010400};
const u32 var7005552c[] = {0x0000000e};
const u32 var70055530[] = {0x02020500};
const u32 var70055534[] = {0x0000001a};
const u32 var70055538[] = {0x02030600};
const u32 var7005553c[] = {0x0000001c};
const u32 var70055540[] = {0x02040700};
const u32 var70055544[] = {0x00000054};
const u32 var70055548[] = {0x02050800};
const u32 var7005554c[] = {0x00000078};
const u32 var70055550[] = {0x02060700};
const u32 var70055554[] = {0x00000028};
const u32 var70055558[] = {0x02070800};
const u32 var7005555c[] = {0x000000e0};
const u32 var70055560[] = {0x03000600};
const u32 var70055564[] = {0x00000022};
const u32 var70055568[] = {0x03010500};
const u32 var7005556c[] = {0x0000000a};
const u32 var70055570[] = {0x03020600};
const u32 var70055574[] = {0x0000003c};
const u32 var70055578[] = {0x03030600};
const u32 var7005557c[] = {0x0000000c};
const u32 var70055580[] = {0x03040700};
const u32 var70055584[] = {0x00000024};
const u32 var70055588[] = {0x03050800};
const u32 var7005558c[] = {0x00000038};
const u32 var70055590[] = {0x03060800};
const u32 var70055594[] = {0x00000070};
const u32 var70055598[] = {0x03070800};
const u32 var7005559c[] = {0x000000a0};
const u32 var700555a0[] = {0x04000700};
const u32 var700555a4[] = {0x00000002};
const u32 var700555a8[] = {0x04010600};
const u32 var700555ac[] = {0x0000002c};
const u32 var700555b0[] = {0x04020700};
const u32 var700555b4[] = {0x00000034};
const u32 var700555b8[] = {0x04030700};
const u32 var700555bc[] = {0x00000064};
const u32 var700555c0[] = {0x04040800};
const u32 var700555c4[] = {0x00000048};
const u32 var700555c8[] = {0x04050800};
const u32 var700555cc[] = {0x00000008};
const u32 var700555d0[] = {0x04060800};
const u32 var700555d4[] = {0x00000090};
const u32 var700555d8[] = {0x04070900};
const u32 var700555dc[] = {0x00000140};
const u32 var700555e0[] = {0x05000800};
const u32 var700555e4[] = {0x00000014};
const u32 var700555e8[] = {0x05010700};
const u32 var700555ec[] = {0x00000044};
const u32 var700555f0[] = {0x05020800};
const u32 var700555f4[] = {0x000000f8};
const u32 var700555f8[] = {0x05030800};
const u32 var700555fc[] = {0x000000b8};
const u32 var70055600[] = {0x05040800};
const u32 var70055604[] = {0x00000088};
const u32 var70055608[] = {0x05050900};
const u32 var7005560c[] = {0x00000160};
const u32 var70055610[] = {0x05060800};
const u32 var70055614[] = {0x00000020};
const u32 var70055618[] = {0x05070900};
const u32 var7005561c[] = {0x00000080};
const u32 var70055620[] = {0x06000800};
const u32 var70055624[] = {0x000000d8};
const u32 var70055628[] = {0x06010700};
const u32 var7005562c[] = {0x00000018};
const u32 var70055630[] = {0x06020700};
const u32 var70055634[] = {0x00000068};
const u32 var70055638[] = {0x06030800};
const u32 var7005563c[] = {0x000000f0};
const u32 var70055640[] = {0x06040800};
const u32 var70055644[] = {0x00000050};
const u32 var70055648[] = {0x06050900};
const u32 var7005564c[] = {0x000001c0};
const u32 var70055650[] = {0x06060900};
const u32 var70055654[] = {0x00000040};
const u32 var70055658[] = {0x06070a00};
const u32 var7005565c[] = {0x00000200};
const u32 var70055660[] = {0x07000900};
const u32 var70055664[] = {0x000001b0};
const u32 var70055668[] = {0x07010800};
const u32 var7005566c[] = {0x00000030};
const u32 var70055670[] = {0x07020800};
const u32 var70055674[] = {0x00000010};
const u32 var70055678[] = {0x07030900};
const u32 var7005567c[] = {0x00000060};
const u32 var70055680[] = {0x07040900};
const u32 var70055684[] = {0x000000c0};
const u32 var70055688[] = {0x07050900};
const u32 var7005568c[] = {0x00000180};
const u32 var70055690[] = {0x07060900};
const u32 var70055694[] = {0x00000100};
const u32 var70055698[] = {0x07070a00};
const u32 var7005569c[] = {0x00000000};
const u32 var700556a0[] = {0x64646400};
const u32 var700556a4[] = {0x00000000};
const u32 var700556a8[] = {0x00000100};
const u32 var700556ac[] = {0x00000001};
const u32 var700556b0[] = {0x00010400};
const u32 var700556b4[] = {0x0000000a};
const u32 var700556b8[] = {0x00020600};
const u32 var700556bc[] = {0x0000001c};
const u32 var700556c0[] = {0x00030700};
const u32 var700556c4[] = {0x00000054};
const u32 var700556c8[] = {0x00040800};
const u32 var700556cc[] = {0x00000044};
const u32 var700556d0[] = {0x00050900};
const u32 var700556d4[] = {0x00000198};
const u32 var700556d8[] = {0x00060900};
const u32 var700556dc[] = {0x000000e8};
const u32 var700556e0[] = {0x00070a00};
const u32 var700556e4[] = {0x00000388};
const u32 var700556e8[] = {0x00080900};
const u32 var700556ec[] = {0x000000a8};
const u32 var700556f0[] = {0x00090a00};
const u32 var700556f4[] = {0x000000b0};
const u32 var700556f8[] = {0x000a0b00};
const u32 var700556fc[] = {0x00000110};
const u32 var70055700[] = {0x000b0b00};
const u32 var70055704[] = {0x00000160};
const u32 var70055708[] = {0x000c0c00};
const u32 var7005570c[] = {0x00000c20};
const u32 var70055710[] = {0x000d0c00};
const u32 var70055714[] = {0x00000340};
const u32 var70055718[] = {0x000e0d00};
const u32 var7005571c[] = {0x00001a80};
const u32 var70055720[] = {0x000f0d00};
const u32 var70055724[] = {0x00001900};
const u32 var70055728[] = {0x01000300};
const u32 var7005572c[] = {0x00000006};
const u32 var70055730[] = {0x01010400};
const u32 var70055734[] = {0x00000002};
const u32 var70055738[] = {0x01020600};
const u32 var7005573c[] = {0x0000000c};
const u32 var70055740[] = {0x01030700};
const u32 var70055744[] = {0x00000064};
const u32 var70055748[] = {0x01040800};
const u32 var7005574c[] = {0x000000f8};
const u32 var70055750[] = {0x01050800};
const u32 var70055754[] = {0x00000058};
const u32 var70055758[] = {0x01060900};
const u32 var7005575c[] = {0x00000068};
const u32 var70055760[] = {0x01070900};
const u32 var70055764[] = {0x00000108};
const u32 var70055768[] = {0x01080900};
const u32 var7005576c[] = {0x000001f0};
const u32 var70055770[] = {0x01090900};
const u32 var70055774[] = {0x00000030};
const u32 var70055778[] = {0x010a0a00};
const u32 var7005577c[] = {0x00000010};
const u32 var70055780[] = {0x010b0a00};
const u32 var70055784[] = {0x00000060};
const u32 var70055788[] = {0x010c0b00};
const u32 var7005578c[] = {0x000007c0};
const u32 var70055790[] = {0x010d0c00};
const u32 var70055794[] = {0x00000c40};
const u32 var70055798[] = {0x010e0c00};
const u32 var7005579c[] = {0x00000680};
const u32 var700557a0[] = {0x010f0c00};
const u32 var700557a4[] = {0x00000700};
const u32 var700557a8[] = {0x02000600};
const u32 var700557ac[] = {0x0000003c};
const u32 var700557b0[] = {0x02010600};
const u32 var700557b4[] = {0x0000002c};
const u32 var700557b8[] = {0x02020700};
const u32 var700557bc[] = {0x00000074};
const u32 var700557c0[] = {0x02030800};
const u32 var700557c4[] = {0x00000024};
const u32 var700557c8[] = {0x02040900};
const u32 var700557cc[] = {0x000001b8};
const u32 var700557d0[] = {0x02050900};
const u32 var700557d4[] = {0x00000118};
const u32 var700557d8[] = {0x02060a00};
const u32 var700557dc[] = {0x000002c8};
const u32 var700557e0[] = {0x02070a00};
const u32 var700557e4[] = {0x00000208};
const u32 var700557e8[] = {0x02080900};
const u32 var700557ec[] = {0x00000170};
const u32 var700557f0[] = {0x02090a00};
const u32 var700557f4[] = {0x00000050};
const u32 var700557f8[] = {0x020a0a00};
const u32 var700557fc[] = {0x000001e0};
const u32 var70055800[] = {0x020b0b00};
const u32 var70055804[] = {0x000000a0};
const u32 var70055808[] = {0x020c0b00};
const u32 var7005580c[] = {0x000006c0};
const u32 var70055810[] = {0x020d0c00};
const u32 var70055814[] = {0x00000840};
const u32 var70055818[] = {0x020e0d00};
const u32 var7005581c[] = {0x00000a80};
const u32 var70055820[] = {0x020f0d00};
const u32 var70055824[] = {0x00000100};
const u32 var70055828[] = {0x03000700};
const u32 var7005582c[] = {0x00000034};
const u32 var70055830[] = {0x03010700};
const u32 var70055834[] = {0x00000014};
const u32 var70055838[] = {0x03020800};
const u32 var7005583c[] = {0x000000a4};
const u32 var70055840[] = {0x03030900};
const u32 var70055844[] = {0x00000178};
const u32 var70055848[] = {0x03040900};
const u32 var7005584c[] = {0x00000038};
const u32 var70055850[] = {0x03050a00};
const u32 var70055854[] = {0x000003c8};
const u32 var70055858[] = {0x03060a00};
const u32 var7005585c[] = {0x00000248};
const u32 var70055860[] = {0x03070a00};
const u32 var70055864[] = {0x00000008};
const u32 var70055868[] = {0x03080a00};
const u32 var7005586c[] = {0x00000350};
const u32 var70055870[] = {0x03090b00};
const u32 var70055874[] = {0x00000190};
const u32 var70055878[] = {0x030a0b00};
const u32 var7005587c[] = {0x000000e0};
const u32 var70055880[] = {0x030b0b00};
const u32 var70055884[] = {0x00000520};
const u32 var70055888[] = {0x030c0b00};
const u32 var7005588c[] = {0x000002c0};
const u32 var70055890[] = {0x030d0c00};
const u32 var70055894[] = {0x00000f80};
const u32 var70055898[] = {0x030e0d00};
const u32 var7005589c[] = {0x00001300};
const u32 var700558a0[] = {0x030f0d00};
const u32 var700558a4[] = {0x00000e00};
const u32 var700558a8[] = {0x04000800};
const u32 var700558ac[] = {0x000000c4};
const u32 var700558b0[] = {0x04010700};
const u32 var700558b4[] = {0x00000004};
const u32 var700558b8[] = {0x04020900};
const u32 var700558bc[] = {0x00000078};
const u32 var700558c0[] = {0x04030900};
const u32 var700558c4[] = {0x00000138};
const u32 var700558c8[] = {0x04040a00};
const u32 var700558cc[] = {0x00000218};
const u32 var700558d0[] = {0x04050a00};
const u32 var700558d4[] = {0x00000348};
const u32 var700558d8[] = {0x04060b00};
const u32 var700558dc[] = {0x00000270};
const u32 var700558e0[] = {0x04070b00};
const u32 var700558e4[] = {0x000006d0};
const u32 var700558e8[] = {0x04080a00};
const u32 var700558ec[] = {0x000001b0};
const u32 var700558f0[] = {0x04090b00};
const u32 var700558f4[] = {0x00000490};
const u32 var700558f8[] = {0x040a0b00};
const u32 var700558fc[] = {0x00000760};
const u32 var70055900[] = {0x040b0c00};
const u32 var70055904[] = {0x00000940};
const u32 var70055908[] = {0x040c0c00};
const u32 var7005590c[] = {0x000000c0};
const u32 var70055910[] = {0x040d0d00};
const u32 var70055914[] = {0x00001580};
const u32 var70055918[] = {0x040e0d00};
const u32 var7005591c[] = {0x00001d00};
const u32 var70055920[] = {0x040f0e00};
const u32 var70055924[] = {0x00000600};
const u32 var70055928[] = {0x05000900};
const u32 var7005592c[] = {0x000000b8};
const u32 var70055930[] = {0x05010800};
const u32 var70055934[] = {0x000000d8};
const u32 var70055938[] = {0x05020900};
const u32 var7005593c[] = {0x00000098};
const u32 var70055940[] = {0x05030a00};
const u32 var70055944[] = {0x00000018};
const u32 var70055948[] = {0x05040a00};
const u32 var7005594c[] = {0x000000c8};
const u32 var70055950[] = {0x05050a00};
const u32 var70055954[] = {0x00000188};
const u32 var70055958[] = {0x05060b00};
const u32 var7005595c[] = {0x000005d0};
const u32 var70055960[] = {0x05070b00};
const u32 var70055964[] = {0x00000150};
const u32 var70055968[] = {0x05080b00};
const u32 var7005596c[] = {0x00000590};
const u32 var70055970[] = {0x05090b00};
const u32 var70055974[] = {0x000002e0};
const u32 var70055978[] = {0x050a0c00};
const u32 var7005597c[] = {0x00000f20};
const u32 var70055980[] = {0x050b0b00};
const u32 var70055984[] = {0x000005c0};
const u32 var70055988[] = {0x050c0d00};
const u32 var7005598c[] = {0x00000a40};
const u32 var70055990[] = {0x050d0d00};
const u32 var70055994[] = {0x00001180};
const u32 var70055998[] = {0x050e0e00};
const u32 var7005599c[] = {0x00002500};
const u32 var700559a0[] = {0x050f0e00};
const u32 var700559a4[] = {0x00002200};
const u32 var700559a8[] = {0x06000900};
const u32 var700559ac[] = {0x000001e8};
const u32 var700559b0[] = {0x06010900};
const u32 var700559b4[] = {0x00000168};
const u32 var700559b8[] = {0x06020a00};
const u32 var700559bc[] = {0x000001c8};
const u32 var700559c0[] = {0x06030a00};
const u32 var700559c4[] = {0x00000148};
const u32 var700559c8[] = {0x06040b00};
const u32 var700559cc[] = {0x00000670};
const u32 var700559d0[] = {0x06050b00};
const u32 var700559d4[] = {0x000003d0};
const u32 var700559d8[] = {0x06060b00};
const u32 var700559dc[] = {0x000002d0};
const u32 var700559e0[] = {0x06070b00};
const u32 var700559e4[] = {0x00000790};
const u32 var700559e8[] = {0x06080b00};
const u32 var700559ec[] = {0x00000510};
const u32 var700559f0[] = {0x06090c00};
const u32 var700559f4[] = {0x00000ca0};
const u32 var700559f8[] = {0x060a0c00};
const u32 var700559fc[] = {0x00000e20};
const u32 var70055a00[] = {0x060b0c00};
const u32 var70055a04[] = {0x000004c0};
const u32 var70055a08[] = {0x060c0d00};
const u32 var70055a0c[] = {0x00001b80};
const u32 var70055a10[] = {0x060d0d00};
const u32 var70055a14[] = {0x00000c80};
const u32 var70055a18[] = {0x060e0e00};
const u32 var70055a1c[] = {0x00000900};
const u32 var70055a20[] = {0x060f0e00};
const u32 var70055a24[] = {0x00003c00};
const u32 var70055a28[] = {0x07000a00};
const u32 var70055a2c[] = {0x00000048};
const u32 var70055a30[] = {0x07010900};
const u32 var70055a34[] = {0x00000088};
const u32 var70055a38[] = {0x07020a00};
const u32 var70055a3c[] = {0x00000070};
const u32 var70055a40[] = {0x07030b00};
const u32 var70055a44[] = {0x000007d0};
const u32 var70055a48[] = {0x07040b00};
const u32 var70055a4c[] = {0x000001d0};
const u32 var70055a50[] = {0x07050b00};
const u32 var70055a54[] = {0x00000550};
const u32 var70055a58[] = {0x07060c00};
const u32 var70055a5c[] = {0x00000da0};
const u32 var70055a60[] = {0x07070c00};
const u32 var70055a64[] = {0x000005a0};
const u32 var70055a68[] = {0x07080c00};
const u32 var70055a6c[] = {0x000006a0};
const u32 var70055a70[] = {0x07090c00};
const u32 var70055a74[] = {0x00000920};
const u32 var70055a78[] = {0x070a0d00};
const u32 var70055a7c[] = {0x00001640};
const u32 var70055a80[] = {0x070b0d00};
const u32 var70055a84[] = {0x00001040};
const u32 var70055a88[] = {0x070c0d00};
const u32 var70055a8c[] = {0x00001980};
const u32 var70055a90[] = {0x070d0e00};
const u32 var70055a94[] = {0x00000d00};
const u32 var70055a98[] = {0x070e1000};
const u32 var70055a9c[] = {0x0000d400};
const u32 var70055aa0[] = {0x070f1000};
const u32 var70055aa4[] = {0x00005400};
const u32 var70055aa8[] = {0x08000900};
const u32 var70055aac[] = {0x000001a8};
const u32 var70055ab0[] = {0x08010800};
const u32 var70055ab4[] = {0x00000028};
const u32 var70055ab8[] = {0x08020900};
const u32 var70055abc[] = {0x000000f0};
const u32 var70055ac0[] = {0x08030a00};
const u32 var70055ac4[] = {0x000000d0};
const u32 var70055ac8[] = {0x08040a00};
const u32 var70055acc[] = {0x000003b0};
const u32 var70055ad0[] = {0x08050b00};
const u32 var70055ad4[] = {0x00000390};
const u32 var70055ad8[] = {0x08060b00};
const u32 var70055adc[] = {0x00000090};
const u32 var70055ae0[] = {0x08070c00};
const u32 var70055ae4[] = {0x00000ea0};
const u32 var70055ae8[] = {0x08080c00};
const u32 var70055aec[] = {0x00000720};
const u32 var70055af0[] = {0x08090c00};
const u32 var70055af4[] = {0x00000bc0};
const u32 var70055af8[] = {0x080a0c00};
const u32 var70055afc[] = {0x00000740};
const u32 var70055b00[] = {0x080b0d00};
const u32 var70055b04[] = {0x00000d80};
const u32 var70055b08[] = {0x080c0d00};
const u32 var70055b0c[] = {0x00001480};
const u32 var70055b10[] = {0x080d0e00};
const u32 var70055b14[] = {0x00001e00};
const u32 var70055b18[] = {0x080e0f00};
const u32 var70055b1c[] = {0x00001400};
const u32 var70055b20[] = {0x080f0f00};
const u32 var70055b24[] = {0x00000400};
const u32 var70055b28[] = {0x09000a00};
const u32 var70055b2c[] = {0x000002b0};
const u32 var70055b30[] = {0x09010900};
const u32 var70055b34[] = {0x00000130};
const u32 var70055b38[] = {0x09020a00};
const u32 var70055b3c[] = {0x00000250};
const u32 var70055b40[] = {0x09030a00};
const u32 var70055b44[] = {0x00000290};
const u32 var70055b48[] = {0x09040b00};
const u32 var70055b4c[] = {0x000001a0};
const u32 var70055b50[] = {0x09050b00};
const u32 var70055b54[] = {0x000006e0};
const u32 var70055b58[] = {0x09060b00};
const u32 var70055b5c[] = {0x00000360};
const u32 var70055b60[] = {0x09070d00};
const u32 var70055b64[] = {0x00001140};
const u32 var70055b68[] = {0x09080c00};
const u32 var70055b6c[] = {0x00000420};
const u32 var70055b70[] = {0x09090d00};
const u32 var70055b74[] = {0x00000640};
const u32 var70055b78[] = {0x090a0d00};
const u32 var70055b7c[] = {0x00001380};
const u32 var70055b80[] = {0x090b0e00};
const u32 var70055b84[] = {0x00001b00};
const u32 var70055b88[] = {0x090c0e00};
const u32 var70055b8c[] = {0x00002900};
const u32 var70055b90[] = {0x090d0e00};
const u32 var70055b94[] = {0x00001200};
const u32 var70055b98[] = {0x090e1000};
const u32 var70055b9c[] = {0x0000e400};
const u32 var70055ba0[] = {0x090f0f00};
const u32 var70055ba4[] = {0x00006800};
const u32 var70055ba8[] = {0x0a000a00};
const u32 var70055bac[] = {0x00000310};
const u32 var70055bb0[] = {0x0a010a00};
const u32 var70055bb4[] = {0x00000210};
const u32 var70055bb8[] = {0x0a020a00};
const u32 var70055bbc[] = {0x000003e0};
const u32 var70055bc0[] = {0x0a030b00};
const u32 var70055bc4[] = {0x000004e0};
const u32 var70055bc8[] = {0x0a040b00};
const u32 var70055bcc[] = {0x000002a0};
const u32 var70055bd0[] = {0x0a050c00};
const u32 var70055bd4[] = {0x000004a0};
const u32 var70055bd8[] = {0x0a060c00};
const u32 var70055bdc[] = {0x00000120};
const u32 var70055be0[] = {0x0a070d00};
const u32 var70055be4[] = {0x00000140};
const u32 var70055be8[] = {0x0a080c00};
const u32 var70055bec[] = {0x00000f40};
const u32 var70055bf0[] = {0x0a090d00};
const u32 var70055bf4[] = {0x00000b80};
const u32 var70055bf8[] = {0x0a0a0e00};
const u32 var70055bfc[] = {0x00003b00};
const u32 var70055c00[] = {0x0a0b0d00};
const u32 var70055c04[] = {0x00001500};
const u32 var70055c08[] = {0x0a0c0e00};
const u32 var70055c0c[] = {0x00001a00};
const u32 var70055c10[] = {0x0a0d0f00};
const u32 var70055c14[] = {0x00002c00};
const u32 var70055c18[] = {0x0a0e1000};
const u32 var70055c1c[] = {0x00006400};
const u32 var70055c20[] = {0x0a0f1100};
const u32 var70055c24[] = {0x0000d000};
const u32 var70055c28[] = {0x0b000b00};
const u32 var70055c2c[] = {0x00000560};
const u32 var70055c30[] = {0x0b010a00};
const u32 var70055c34[] = {0x00000260};
const u32 var70055c38[] = {0x0b020a00};
const u32 var70055c3c[] = {0x000003a0};
const u32 var70055c40[] = {0x0b030b00};
const u32 var70055c44[] = {0x00000320};
const u32 var70055c48[] = {0x0b040c00};
const u32 var70055c4c[] = {0x00000620};
const u32 var70055c50[] = {0x0b050c00};
const u32 var70055c54[] = {0x000003c0};
const u32 var70055c58[] = {0x0b060c00};
const u32 var70055c5c[] = {0x00000cc0};
const u32 var70055c60[] = {0x0b070c00};
const u32 var70055c64[] = {0x00000240};
const u32 var70055c68[] = {0x0b080d00};
const u32 var70055c6c[] = {0x00001d80};
const u32 var70055c70[] = {0x0b090d00};
const u32 var70055c74[] = {0x00000b00};
const u32 var70055c78[] = {0x0b0a0d00};
const u32 var70055c7c[] = {0x00000880};
const u32 var70055c80[] = {0x0b0b0e00};
const u32 var70055c84[] = {0x00003a00};
const u32 var70055c88[] = {0x0b0c0f00};
const u32 var70055c8c[] = {0x00006c00};
const u32 var70055c90[] = {0x0b0d0f00};
const u32 var70055c94[] = {0x00003800};
const u32 var70055c98[] = {0x0b0e0f00};
const u32 var70055c9c[] = {0x00004800};
const u32 var70055ca0[] = {0x0b0f1000};
const u32 var70055ca4[] = {0x0000e000};
const u32 var70055ca8[] = {0x0c000b00};
const u32 var70055cac[] = {0x00000220};
const u32 var70055cb0[] = {0x0c010b00};
const u32 var70055cb4[] = {0x00000020};
const u32 var70055cb8[] = {0x0c020b00};
const u32 var70055cbc[] = {0x000001c0};
const u32 var70055cc0[] = {0x0c030c00};
const u32 var70055cc4[] = {0x00000e40};
const u32 var70055cc8[] = {0x0c040c00};
const u32 var70055ccc[] = {0x000008c0};
const u32 var70055cd0[] = {0x0c050d00};
const u32 var70055cd4[] = {0x00001a40};
const u32 var70055cd8[] = {0x0c060c00};
const u32 var70055cdc[] = {0x00000780};
const u32 var70055ce0[] = {0x0c070d00};
const u32 var70055ce4[] = {0x00000580};
const u32 var70055ce8[] = {0x0c080e00};
const u32 var70055cec[] = {0x00000300};
const u32 var70055cf0[] = {0x0c090e00};
const u32 var70055cf4[] = {0x00000500};
const u32 var70055cf8[] = {0x0c0a0f00};
const u32 var70055cfc[] = {0x00001600};
const u32 var70055d00[] = {0x0c0b0f00};
const u32 var70055d04[] = {0x00001c00};
const u32 var70055d08[] = {0x0c0c0f00};
const u32 var70055d0c[] = {0x00002400};
const u32 var70055d10[] = {0x0c0d1000};
const u32 var70055d14[] = {0x00008800};
const u32 var70055d18[] = {0x0c0e1000};
const u32 var70055d1c[] = {0x00009000};
const u32 var70055d20[] = {0x0c0f1000};
const u32 var70055d24[] = {0x0000a000};
const u32 var70055d28[] = {0x0d000c00};
const u32 var70055d2c[] = {0x00000b40};
const u32 var70055d30[] = {0x0d010b00};
const u32 var70055d34[] = {0x00000540};
const u32 var70055d38[] = {0x0d020c00};
const u32 var70055d3c[] = {0x00000440};
const u32 var70055d40[] = {0x0d030d00};
const u32 var70055d44[] = {0x00000040};
const u32 var70055d48[] = {0x0d040d00};
const u32 var70055d4c[] = {0x00000380};
const u32 var70055d50[] = {0x0d050d00};
const u32 var70055d54[] = {0x00000980};
const u32 var70055d58[] = {0x0d060e00};
const u32 var70055d5c[] = {0x00002300};
const u32 var70055d60[] = {0x0d070e00};
const u32 var70055d64[] = {0x00002d00};
const u32 var70055d68[] = {0x0d080e00};
const u32 var70055d6c[] = {0x00003e00};
const u32 var70055d70[] = {0x0d090e00};
const u32 var70055d74[] = {0x00003200};
const u32 var70055d78[] = {0x0d0a0e00};
const u32 var70055d7c[] = {0x00000c00};
const u32 var70055d80[] = {0x0d0b0f00};
const u32 var70055d84[] = {0x00007800};
const u32 var70055d88[] = {0x0d0c1000};
const u32 var70055d8c[] = {0x00005000};
const u32 var70055d90[] = {0x0d0d0f00};
const u32 var70055d94[] = {0x00007000};
const u32 var70055d98[] = {0x0d0e1000};
const u32 var70055d9c[] = {0x00006000};
const u32 var70055da0[] = {0x0d0f1000};
const u32 var70055da4[] = {0x0000c000};
const u32 var70055da8[] = {0x0e000d00};
const u32 var70055dac[] = {0x00000180};
const u32 var70055db0[] = {0x0e010c00};
const u32 var70055db4[] = {0x00000e80};
const u32 var70055db8[] = {0x0e020c00};
const u32 var70055dbc[] = {0x00000280};
const u32 var70055dc0[] = {0x0e030d00};
const u32 var70055dc4[] = {0x00001c80};
const u32 var70055dc8[] = {0x0e040d00};
const u32 var70055dcc[] = {0x00000480};
const u32 var70055dd0[] = {0x0e050d00};
const u32 var70055dd4[] = {0x00001880};
const u32 var70055dd8[] = {0x0e060f00};
const u32 var70055ddc[] = {0x00005600};
const u32 var70055de0[] = {0x0e070e00};
const u32 var70055de4[] = {0x00002a00};
const u32 var70055de8[] = {0x0e080e00};
const u32 var70055dec[] = {0x00000200};
const u32 var70055df0[] = {0x0e091100};
const u32 var70055df4[] = {0x0001d000};
const u32 var70055df8[] = {0x0e0a0f00};
const u32 var70055dfc[] = {0x00005800};
const u32 var70055e00[] = {0x0e0b0f00};
const u32 var70055e04[] = {0x00002800};
const u32 var70055e08[] = {0x0e0c0f00};
const u32 var70055e0c[] = {0x00003000};
const u32 var70055e10[] = {0x0e0d1100};
const u32 var70055e14[] = {0x00010000};
const u32 var70055e18[] = {0x0e0e1000};
const u32 var70055e1c[] = {0x00002000};
const u32 var70055e20[] = {0x0e0f1000};
const u32 var70055e24[] = {0x00004000};
const u32 var70055e28[] = {0x0f000c00};
const u32 var70055e2c[] = {0x00000080};
const u32 var70055e30[] = {0x0f010c00};
const u32 var70055e34[] = {0x00000f00};
const u32 var70055e38[] = {0x0f020d00};
const u32 var70055e3c[] = {0x00001100};
const u32 var70055e40[] = {0x0f030e00};
const u32 var70055e44[] = {0x00003600};
const u32 var70055e48[] = {0x0f040e00};
const u32 var70055e4c[] = {0x00002600};
const u32 var70055e50[] = {0x0f050e00};
const u32 var70055e54[] = {0x00000a00};
const u32 var70055e58[] = {0x0f060f00};
const u32 var70055e5c[] = {0x00005c00};
const u32 var70055e60[] = {0x0f070e00};
const u32 var70055e64[] = {0x00003400};
const u32 var70055e68[] = {0x0f080f00};
const u32 var70055e6c[] = {0x00004400};
const u32 var70055e70[] = {0x0f090f00};
const u32 var70055e74[] = {0x00001800};
const u32 var70055e78[] = {0x0f0a1000};
const u32 var70055e7c[] = {0x00000800};
const u32 var70055e80[] = {0x0f0b1000};
const u32 var70055e84[] = {0x00001000};
const u32 var70055e88[] = {0x0f0c1300};
const u32 var70055e8c[] = {0x00040000};
const u32 var70055e90[] = {0x0f0d1200};
const u32 var70055e94[] = {0x00020000};
const u32 var70055e98[] = {0x0f0e1300};
const u32 var70055e9c[] = {0x00000000};
const u32 var70055ea0[] = {0x0f0f1000};
const u32 var70055ea4[] = {0x00008000};
const u32 var70055ea8[] = {0x64646400};
const u32 var70055eac[] = {0x00000000};
const u32 var70055eb0[] = {0x00000300};
const u32 var70055eb4[] = {0x00000007};
const u32 var70055eb8[] = {0x00010400};
const u32 var70055ebc[] = {0x00000003};
const u32 var70055ec0[] = {0x00020500};
const u32 var70055ec4[] = {0x00000009};
const u32 var70055ec8[] = {0x00030700};
const u32 var70055ecc[] = {0x00000056};
const u32 var70055ed0[] = {0x00040700};
const u32 var70055ed4[] = {0x0000007a};
const u32 var70055ed8[] = {0x00050800};
const u32 var70055edc[] = {0x00000032};
const u32 var70055ee0[] = {0x00060900};
const u32 var70055ee4[] = {0x0000007c};
const u32 var70055ee8[] = {0x00070900};
const u32 var70055eec[] = {0x0000006c};
const u32 var70055ef0[] = {0x00080900};
const u32 var70055ef4[] = {0x00000134};
const u32 var70055ef8[] = {0x00090a00};
const u32 var70055efc[] = {0x00000378};
const u32 var70055f00[] = {0x000a0a00};
const u32 var70055f04[] = {0x000000d8};
const u32 var70055f08[] = {0x000b0b00};
const u32 var70055f0c[] = {0x00000770};
const u32 var70055f10[] = {0x000c0b00};
const u32 var70055f14[] = {0x000006b0};
const u32 var70055f18[] = {0x000d0b00};
const u32 var70055f1c[] = {0x00000450};
const u32 var70055f20[] = {0x000e0c00};
const u32 var70055f24[] = {0x000005e0};
const u32 var70055f28[] = {0x000f0d00};
const u32 var70055f2c[] = {0x00001f80};
const u32 var70055f30[] = {0x01000400};
const u32 var70055f34[] = {0x0000000b};
const u32 var70055f38[] = {0x01010300};
const u32 var70055f3c[] = {0x00000005};
const u32 var70055f40[] = {0x01020500};
const u32 var70055f44[] = {0x00000001};
const u32 var70055f48[] = {0x01030600};
const u32 var70055f4c[] = {0x00000036};
const u32 var70055f50[] = {0x01040700};
const u32 var70055f54[] = {0x0000003a};
const u32 var70055f58[] = {0x01050700};
const u32 var70055f5c[] = {0x00000012};
const u32 var70055f60[] = {0x01060800};
const u32 var70055f64[] = {0x000000bc};
const u32 var70055f68[] = {0x01070800};
const u32 var70055f6c[] = {0x000000cc};
const u32 var70055f70[] = {0x01080800};
const u32 var70055f74[] = {0x00000054};
const u32 var70055f78[] = {0x01090900};
const u32 var70055f7c[] = {0x000000c4};
const u32 var70055f80[] = {0x010a0900};
const u32 var70055f84[] = {0x00000058};
const u32 var70055f88[] = {0x010b0a00};
const u32 var70055f8c[] = {0x00000328};
const u32 var70055f90[] = {0x010c0a00};
const u32 var70055f94[] = {0x00000208};
const u32 var70055f98[] = {0x010d0a00};
const u32 var70055f9c[] = {0x00000250};
const u32 var70055fa0[] = {0x010e0b00};
const u32 var70055fa4[] = {0x000006e0};
const u32 var70055fa8[] = {0x010f0b00};
const u32 var70055fac[] = {0x00000120};
const u32 var70055fb0[] = {0x02000500};
const u32 var70055fb4[] = {0x00000019};
const u32 var70055fb8[] = {0x02010500};
const u32 var70055fbc[] = {0x00000011};
const u32 var70055fc0[] = {0x02020500};
const u32 var70055fc4[] = {0x0000001e};
const u32 var70055fc8[] = {0x02030600};
const u32 var70055fcc[] = {0x00000006};
const u32 var70055fd0[] = {0x02040700};
const u32 var70055fd4[] = {0x0000004a};
const u32 var70055fd8[] = {0x02050700};
const u32 var70055fdc[] = {0x00000022};
const u32 var70055fe0[] = {0x02060800};
const u32 var70055fe4[] = {0x000000dc};
const u32 var70055fe8[] = {0x02070800};
const u32 var70055fec[] = {0x0000000c};
const u32 var70055ff0[] = {0x02080800};
const u32 var70055ff4[] = {0x00000014};
const u32 var70055ff8[] = {0x02090900};
const u32 var70055ffc[] = {0x00000004};
const u32 var70056000[] = {0x020a0900};
const u32 var70056004[] = {0x00000098};
const u32 var70056008[] = {0x020b0a00};
const u32 var7005600c[] = {0x000001c8};
const u32 var70056010[] = {0x020c0a00};
const u32 var70056014[] = {0x000001f0};
const u32 var70056018[] = {0x020d0b00};
const u32 var7005601c[] = {0x00000050};
const u32 var70056020[] = {0x020e0b00};
const u32 var70056024[] = {0x000000e0};
const u32 var70056028[] = {0x020f0b00};
const u32 var7005602c[] = {0x00000420};
const u32 var70056030[] = {0x03000600};
const u32 var70056034[] = {0x0000002e};
const u32 var70056038[] = {0x03010600};
const u32 var7005603c[] = {0x0000000e};
const u32 var70056040[] = {0x03020600};
const u32 var70056044[] = {0x00000026};
const u32 var70056048[] = {0x03030700};
const u32 var7005604c[] = {0x0000006a};
const u32 var70056050[] = {0x03040700};
const u32 var70056054[] = {0x00000072};
const u32 var70056058[] = {0x03050800};
const u32 var7005605c[] = {0x000000fc};
const u32 var70056060[] = {0x03060800};
const u32 var70056064[] = {0x000000ec};
const u32 var70056068[] = {0x03070900};
const u32 var7005606c[] = {0x00000174};
const u32 var70056070[] = {0x03080900};
const u32 var70056074[] = {0x00000064};
const u32 var70056078[] = {0x03090900};
const u32 var7005607c[] = {0x000001b8};
const u32 var70056080[] = {0x030a0a00};
const u32 var70056084[] = {0x000002e8};
const u32 var70056088[] = {0x030b0a00};
const u32 var7005608c[] = {0x00000048};
const u32 var70056090[] = {0x030c0a00};
const u32 var70056094[] = {0x000001b0};
const u32 var70056098[] = {0x030d0b00};
const u32 var7005609c[] = {0x00000690};
const u32 var700560a0[] = {0x030e0b00};
const u32 var700560a4[] = {0x00000260};
const u32 var700560a8[] = {0x030f0b00};
const u32 var700560ac[] = {0x000005c0};
const u32 var700560b0[] = {0x04000700};
const u32 var700560b4[] = {0x00000016};
const u32 var700560b8[] = {0x04010600};
const u32 var700560bc[] = {0x0000001a};
const u32 var700560c0[] = {0x04020700};
const u32 var700560c4[] = {0x0000002a};
const u32 var700560c8[] = {0x04030700};
const u32 var700560cc[] = {0x0000000a};
const u32 var700560d0[] = {0x04040800};
const u32 var700560d4[] = {0x000000c2};
const u32 var700560d8[] = {0x04050800};
const u32 var700560dc[] = {0x0000009c};
const u32 var700560e0[] = {0x04060900};
const u32 var700560e4[] = {0x000001f4};
const u32 var700560e8[] = {0x04070900};
const u32 var700560ec[] = {0x000001e4};
const u32 var700560f0[] = {0x04080900};
const u32 var700560f4[] = {0x00000024};
const u32 var700560f8[] = {0x04090900};
const u32 var700560fc[] = {0x00000138};
const u32 var70056100[] = {0x040a0a00};
const u32 var70056104[] = {0x00000268};
const u32 var70056108[] = {0x040b0a00};
const u32 var7005610c[] = {0x00000288};
const u32 var70056110[] = {0x040c0a00};
const u32 var70056114[] = {0x00000230};
const u32 var70056118[] = {0x040d0b00};
const u32 var7005611c[] = {0x00000210};
const u32 var70056120[] = {0x040e0b00};
const u32 var70056124[] = {0x000003a0};
const u32 var70056128[] = {0x040f0b00};
const u32 var7005612c[] = {0x000006c0};
const u32 var70056130[] = {0x05000800};
const u32 var70056134[] = {0x000000b2};
const u32 var70056138[] = {0x05010700};
const u32 var7005613c[] = {0x00000052};
const u32 var70056140[] = {0x05020700};
const u32 var70056144[] = {0x00000062};
const u32 var70056148[] = {0x05030800};
const u32 var7005614c[] = {0x00000042};
const u32 var70056150[] = {0x05040800};
const u32 var70056154[] = {0x0000005c};
const u32 var70056158[] = {0x05050800};
const u32 var7005615c[] = {0x0000002c};
const u32 var70056160[] = {0x05060900};
const u32 var70056164[] = {0x000001b4};
const u32 var70056168[] = {0x05070900};
const u32 var7005616c[] = {0x000000a4};
const u32 var70056170[] = {0x05080900};
const u32 var70056174[] = {0x000000f8};
const u32 var70056178[] = {0x05090900};
const u32 var7005617c[] = {0x00000018};
const u32 var70056180[] = {0x050a0a00};
const u32 var70056184[] = {0x000003c8};
const u32 var70056188[] = {0x050b0a00};
const u32 var7005618c[] = {0x000003f0};
const u32 var70056190[] = {0x050c0b00};
const u32 var70056194[] = {0x000002d0};
const u32 var70056198[] = {0x050d0b00};
const u32 var7005619c[] = {0x000003e0};
const u32 var700561a0[] = {0x050e0b00};
const u32 var700561a4[] = {0x000000a0};
const u32 var700561a8[] = {0x050f0c00};
const u32 var700561ac[] = {0x00000640};
const u32 var700561b0[] = {0x06000900};
const u32 var700561b4[] = {0x0000017c};
const u32 var700561b8[] = {0x06010700};
const u32 var700561bc[] = {0x00000002};
const u32 var700561c0[] = {0x06020800};
const u32 var700561c4[] = {0x0000003c};
const u32 var700561c8[] = {0x06030800};
const u32 var700561cc[] = {0x0000001c};
const u32 var700561d0[] = {0x06040800};
const u32 var700561d4[] = {0x0000004c};
const u32 var700561d8[] = {0x06050900};
const u32 var700561dc[] = {0x00000074};
const u32 var700561e0[] = {0x06060900};
const u32 var700561e4[] = {0x000000e4};
const u32 var700561e8[] = {0x06070900};
const u32 var700561ec[] = {0x00000104};
const u32 var700561f0[] = {0x06080900};
const u32 var700561f4[] = {0x000001d8};
const u32 var700561f8[] = {0x06090a00};
const u32 var700561fc[] = {0x000003a8};
const u32 var70056200[] = {0x060a0a00};
const u32 var70056204[] = {0x00000388};
const u32 var70056208[] = {0x060b0a00};
const u32 var7005620c[] = {0x00000330};
const u32 var70056210[] = {0x060c0b00};
const u32 var70056214[] = {0x00000490};
const u32 var70056218[] = {0x060d0b00};
const u32 var7005621c[] = {0x00000660};
const u32 var70056220[] = {0x060e0c00};
const u32 var70056224[] = {0x00000620};
const u32 var70056228[] = {0x060f0c00};
const u32 var7005622c[] = {0x00000780};
const u32 var70056230[] = {0x07000900};
const u32 var70056234[] = {0x0000016c};
const u32 var70056238[] = {0x07010800};
const u32 var7005623c[] = {0x000000ac};
const u32 var70056240[] = {0x07020800};
const u32 var70056244[] = {0x0000008c};
const u32 var70056248[] = {0x07030900};
const u32 var7005624c[] = {0x000000f4};
const u32 var70056250[] = {0x07040900};
const u32 var70056254[] = {0x00000034};
const u32 var70056258[] = {0x07050900};
const u32 var7005625c[] = {0x000001a4};
const u32 var70056260[] = {0x07060900};
const u32 var70056264[] = {0x00000084};
const u32 var70056268[] = {0x07070a00};
const u32 var7005626c[] = {0x00000178};
const u32 var70056270[] = {0x07080a00};
const u32 var70056274[] = {0x00000368};
const u32 var70056278[] = {0x07090a00};
const u32 var7005627c[] = {0x00000248};
const u32 var70056280[] = {0x070a0a00};
const u32 var70056284[] = {0x00000070};
const u32 var70056288[] = {0x070b0a00};
const u32 var7005628c[] = {0x00000150};
const u32 var70056290[] = {0x070c0b00};
const u32 var70056294[] = {0x00000010};
const u32 var70056298[] = {0x070d0b00};
const u32 var7005629c[] = {0x000001a0};
const u32 var700562a0[] = {0x070e0b00};
const u32 var700562a4[] = {0x00000540};
const u32 var700562a8[] = {0x070f0c00};
const u32 var700562ac[] = {0x00000980};
const u32 var700562b0[] = {0x08000900};
const u32 var700562b4[] = {0x000000b4};
const u32 var700562b8[] = {0x08010800};
const u32 var700562bc[] = {0x000000d4};
const u32 var700562c0[] = {0x08020800};
const u32 var700562c4[] = {0x00000094};
const u32 var700562c8[] = {0x08030900};
const u32 var700562cc[] = {0x00000164};
const u32 var700562d0[] = {0x08040900};
const u32 var700562d4[] = {0x00000124};
const u32 var700562d8[] = {0x08050900};
const u32 var700562dc[] = {0x000001f8};
const u32 var700562e0[] = {0x08060900};
const u32 var700562e4[] = {0x00000038};
const u32 var700562e8[] = {0x08070a00};
const u32 var700562ec[] = {0x000000e8};
const u32 var700562f0[] = {0x08080a00};
const u32 var700562f4[] = {0x000002c8};
const u32 var700562f8[] = {0x08090a00};
const u32 var700562fc[] = {0x00000108};
const u32 var70056300[] = {0x080a0a00};
const u32 var70056304[] = {0x000003d0};
const u32 var70056308[] = {0x080b0b00};
const u32 var7005630c[] = {0x00000610};
const u32 var70056310[] = {0x080c0b00};
const u32 var70056314[] = {0x00000060};
const u32 var70056318[] = {0x080d0c00};
const u32 var7005631c[] = {0x00000ac0};
const u32 var70056320[] = {0x080e0c00};
const u32 var70056324[] = {0x00000240};
const u32 var70056328[] = {0x080f0c00};
const u32 var7005632c[] = {0x00000280};
const u32 var70056330[] = {0x09000900};
const u32 var70056334[] = {0x000001c4};
const u32 var70056338[] = {0x09010800};
const u32 var7005633c[] = {0x00000044};
const u32 var70056340[] = {0x09020900};
const u32 var70056344[] = {0x00000184};
const u32 var70056348[] = {0x09030900};
const u32 var7005634c[] = {0x00000078};
const u32 var70056350[] = {0x09040900};
const u32 var70056354[] = {0x000000b8};
const u32 var70056358[] = {0x09050900};
const u32 var7005635c[] = {0x00000118};
const u32 var70056360[] = {0x09060a00};
const u32 var70056364[] = {0x00000068};
const u32 var70056368[] = {0x09070a00};
const u32 var7005636c[] = {0x000000c8};
const u32 var70056370[] = {0x09080a00};
const u32 var70056374[] = {0x00000308};
const u32 var70056378[] = {0x09090b00};
const u32 var7005637c[] = {0x000002b0};
const u32 var70056380[] = {0x090a0b00};
const u32 var70056384[] = {0x00000710};
const u32 var70056388[] = {0x090b0b00};
const u32 var7005638c[] = {0x00000360};
const u32 var70056390[] = {0x090c0b00};
const u32 var70056394[] = {0x00000320};
const u32 var70056398[] = {0x090d0c00};
const u32 var7005639c[] = {0x00000e40};
const u32 var700563a0[] = {0x090e0c00};
const u32 var700563a4[] = {0x00000e80};
const u32 var700563a8[] = {0x090f0c00};
const u32 var700563ac[] = {0x00000f00};
const u32 var700563b0[] = {0x0a000a00};
const u32 var700563b4[] = {0x000002d8};
const u32 var700563b8[] = {0x0a010900};
const u32 var700563bc[] = {0x00000158};
const u32 var700563c0[] = {0x0a020900};
const u32 var700563c4[] = {0x00000198};
const u32 var700563c8[] = {0x0a030900};
const u32 var700563cc[] = {0x000001e8};
const u32 var700563d0[] = {0x0a040a00};
const u32 var700563d4[] = {0x00000168};
const u32 var700563d8[] = {0x0a050a00};
const u32 var700563dc[] = {0x00000128};
const u32 var700563e0[] = {0x0a060a00};
const u32 var700563e4[] = {0x00000170};
const u32 var700563e8[] = {0x0a070a00};
const u32 var700563ec[] = {0x00000270};
const u32 var700563f0[] = {0x0a080a00};
const u32 var700563f4[] = {0x00000030};
const u32 var700563f8[] = {0x0a090b00};
const u32 var700563fc[] = {0x00000090};
const u32 var70056400[] = {0x0a0a0b00};
const u32 var70056404[] = {0x000004e0};
const u32 var70056408[] = {0x0a0b0b00};
const u32 var7005640c[] = {0x000004a0};
const u32 var70056410[] = {0x0a0c0b00};
const u32 var70056414[] = {0x00000740};
const u32 var70056418[] = {0x0a0d0c00};
const u32 var7005641c[] = {0x00000d80};
const u32 var70056420[] = {0x0a0e0d00};
const u32 var70056424[] = {0x00000f80};
const u32 var70056428[] = {0x0a0f0c00};
const u32 var7005642c[] = {0x00000900};
const u32 var70056430[] = {0x0b000a00};
const u32 var70056434[] = {0x000001a8};
const u32 var70056438[] = {0x0b010900};
const u32 var7005643c[] = {0x000000a8};
const u32 var70056440[] = {0x0b020900};
const u32 var70056444[] = {0x00000028};
const u32 var70056448[] = {0x0b030900};
const u32 var7005644c[] = {0x00000148};
const u32 var70056450[] = {0x0b040a00};
const u32 var70056454[] = {0x00000188};
const u32 var70056458[] = {0x0b050a00};
const u32 var7005645c[] = {0x00000008};
const u32 var70056460[] = {0x0b060a00};
const u32 var70056464[] = {0x000000b0};
const u32 var70056468[] = {0x0b070a00};
const u32 var7005646c[] = {0x00000350};
const u32 var70056470[] = {0x0b080b00};
const u32 var70056474[] = {0x00000310};
const u32 var70056478[] = {0x0b090b00};
const u32 var7005647c[] = {0x00000760};
const u32 var70056480[] = {0x0b0a0b00};
const u32 var70056484[] = {0x000002a0};
const u32 var70056488[] = {0x0b0b0b00};
const u32 var7005648c[] = {0x000004c0};
const u32 var70056490[] = {0x0b0c0c00};
const u32 var70056494[] = {0x00000b80};
const u32 var70056498[] = {0x0b0d0c00};
const u32 var7005649c[] = {0x00000480};
const u32 var700564a0[] = {0x0b0e0c00};
const u32 var700564a4[] = {0x00000d00};
const u32 var700564a8[] = {0x0b0f0d00};
const u32 var700564ac[] = {0x00001a00};
const u32 var700564b0[] = {0x0c000b00};
const u32 var700564b4[] = {0x00000370};
const u32 var700564b8[] = {0x0c010a00};
const u32 var700564bc[] = {0x00000088};
const u32 var700564c0[] = {0x0c020900};
const u32 var700564c4[] = {0x000000f0};
const u32 var700564c8[] = {0x0c030a00};
const u32 var700564cc[] = {0x000003b0};
const u32 var700564d0[] = {0x0c040a00};
const u32 var700564d4[] = {0x00000130};
const u32 var700564d8[] = {0x0c050a00};
const u32 var700564dc[] = {0x000001d0};
const u32 var700564e0[] = {0x0c060b00};
const u32 var700564e4[] = {0x00000290};
const u32 var700564e8[] = {0x0c070b00};
const u32 var700564ec[] = {0x00000410};
const u32 var700564f0[] = {0x0c080b00};
const u32 var700564f4[] = {0x00000460};
const u32 var700564f8[] = {0x0c090b00};
const u32 var700564fc[] = {0x00000720};
const u32 var70056500[] = {0x0c0a0b00};
const u32 var70056504[] = {0x000000c0};
const u32 var70056508[] = {0x0c0b0b00};
const u32 var7005650c[] = {0x00000040};
const u32 var70056510[] = {0x0c0c0c00};
const u32 var70056514[] = {0x00000680};
const u32 var70056518[] = {0x0c0d0c00};
const u32 var7005651c[] = {0x00000b00};
const u32 var70056520[] = {0x0c0e0d00};
const u32 var70056524[] = {0x00000e00};
const u32 var70056528[] = {0x0c0f0d00};
const u32 var7005652c[] = {0x00001c00};
const u32 var70056530[] = {0x0d000b00};
const u32 var70056534[] = {0x000006d0};
const u32 var70056538[] = {0x0d010a00};
const u32 var7005653c[] = {0x000000d0};
const u32 var70056540[] = {0x0d020a00};
const u32 var70056544[] = {0x00000390};
const u32 var70056548[] = {0x0d030a00};
const u32 var7005654c[] = {0x00000190};
const u32 var70056550[] = {0x0d040a00};
const u32 var70056554[] = {0x00000110};
const u32 var70056558[] = {0x0d050b00};
const u32 var7005655c[] = {0x000007e0};
const u32 var70056560[] = {0x0d060b00};
const u32 var70056564[] = {0x00000160};
const u32 var70056568[] = {0x0d070b00};
const u32 var7005656c[] = {0x000005a0};
const u32 var70056570[] = {0x0d080b00};
const u32 var70056574[] = {0x000007c0};
const u32 var70056578[] = {0x0d090c00};
const u32 var7005657c[] = {0x000002c0};
const u32 var70056580[] = {0x0d0a0c00};
const u32 var70056584[] = {0x00000380};
const u32 var70056588[] = {0x0d0b0c00};
const u32 var7005658c[] = {0x00000c80};
const u32 var70056590[] = {0x0d0c0c00};
const u32 var70056594[] = {0x00000700};
const u32 var70056598[] = {0x0d0d0c00};
const u32 var7005659c[] = {0x00000100};
const u32 var700565a0[] = {0x0d0e0d00};
const u32 var700565a4[] = {0x00001200};
const u32 var700565a8[] = {0x0d0f0d00};
const u32 var700565ac[] = {0x00001800};
const u32 var700565b0[] = {0x0e000c00};
const u32 var700565b4[] = {0x00000de0};
const u32 var700565b8[] = {0x0e010b00};
const u32 var700565bc[] = {0x000001e0};
const u32 var700565c0[] = {0x0e020b00};
const u32 var700565c4[] = {0x000002e0};
const u32 var700565c8[] = {0x0e030b00};
const u32 var700565cc[] = {0x00000560};
const u32 var700565d0[] = {0x0e040b00};
const u32 var700565d4[] = {0x000007a0};
const u32 var700565d8[] = {0x0e050b00};
const u32 var700565dc[] = {0x000006a0};
const u32 var700565e0[] = {0x0e060b00};
const u32 var700565e4[] = {0x00000020};
const u32 var700565e8[] = {0x0e070b00};
const u32 var700565ec[] = {0x00000340};
const u32 var700565f0[] = {0x0e080c00};
const u32 var700565f4[] = {0x00000a40};
const u32 var700565f8[] = {0x0e090c00};
const u32 var700565fc[] = {0x00000180};
const u32 var70056600[] = {0x0e0a0c00};
const u32 var70056604[] = {0x00000880};
const u32 var70056608[] = {0x0e0b0c00};
const u32 var7005660c[] = {0x00000300};
const u32 var70056610[] = {0x0e0c0d00};
const u32 var70056614[] = {0x00001e00};
const u32 var70056618[] = {0x0e0d0d00};
const u32 var7005661c[] = {0x00000a00};
const u32 var70056620[] = {0x0e0e0c00};
const u32 var70056624[] = {0x00000400};
const u32 var70056628[] = {0x0e0f0d00};
const u32 var7005662c[] = {0x00001000};
const u32 var70056630[] = {0x0f000c00};
const u32 var70056634[] = {0x00000e20};
const u32 var70056638[] = {0x0f010b00};
const u32 var7005663c[] = {0x00000520};
const u32 var70056640[] = {0x0f020b00};
const u32 var70056644[] = {0x00000220};
const u32 var70056648[] = {0x0f030b00};
const u32 var7005664c[] = {0x000003c0};
const u32 var70056650[] = {0x0f040b00};
const u32 var70056654[] = {0x000001c0};
const u32 var70056658[] = {0x0f050b00};
const u32 var7005665c[] = {0x00000140};
const u32 var70056660[] = {0x0f060b00};
const u32 var70056664[] = {0x00000440};
const u32 var70056668[] = {0x0f070c00};
const u32 var7005666c[] = {0x00000580};
const u32 var70056670[] = {0x0f080c00};
const u32 var70056674[] = {0x00000a80};
const u32 var70056678[] = {0x0f090c00};
const u32 var7005667c[] = {0x00000080};
const u32 var70056680[] = {0x0f0a0c00};
const u32 var70056684[] = {0x00000500};
const u32 var70056688[] = {0x0f0b0c00};
const u32 var7005668c[] = {0x00000600};
const u32 var70056690[] = {0x0f0c0d00};
const u32 var70056694[] = {0x00000200};
const u32 var70056698[] = {0x0f0d0d00};
const u32 var7005669c[] = {0x00000c00};
const u32 var700566a0[] = {0x0f0e0d00};
const u32 var700566a4[] = {0x00000800};
const u32 var700566a8[] = {0x0f0f0d00};
const u32 var700566ac[] = {0x00000000};
const u32 var700566b0[] = {0x64646400};
const u32 var700566b4[] = {0x00000000};
const u32 var700566b8[] = {0x00000100};
const u32 var700566bc[] = {0x00000001};
const u32 var700566c0[] = {0x00010400};
const u32 var700566c4[] = {0x0000000a};
const u32 var700566c8[] = {0x00020600};
const u32 var700566cc[] = {0x0000001c};
const u32 var700566d0[] = {0x00030800};
const u32 var700566d4[] = {0x00000034};
const u32 var700566d8[] = {0x00040900};
const u32 var700566dc[] = {0x000000a4};
const u32 var700566e0[] = {0x00050900};
const u32 var700566e4[] = {0x000001f8};
const u32 var700566e8[] = {0x00060a00};
const u32 var700566ec[] = {0x000001d8};
const u32 var700566f0[] = {0x00070a00};
const u32 var700566f4[] = {0x000002e8};
const u32 var700566f8[] = {0x00080b00};
const u32 var700566fc[] = {0x000001a8};
const u32 var70056700[] = {0x00090b00};
const u32 var70056704[] = {0x00000548};
const u32 var70056708[] = {0x000a0b00};
const u32 var7005670c[] = {0x00000288};
const u32 var70056710[] = {0x000b0c00};
const u32 var70056714[] = {0x000004f0};
const u32 var70056718[] = {0x000c0c00};
const u32 var7005671c[] = {0x00000870};
const u32 var70056720[] = {0x000d0c00};
const u32 var70056724[] = {0x00000c30};
const u32 var70056728[] = {0x000e0d00};
const u32 var7005672c[] = {0x000003d0};
const u32 var70056730[] = {0x000f0900};
const u32 var70056734[] = {0x00000110};
const u32 var70056738[] = {0x01000300};
const u32 var7005673c[] = {0x00000006};
const u32 var70056740[] = {0x01010400};
const u32 var70056744[] = {0x00000002};
const u32 var70056748[] = {0x01020600};
const u32 var7005674c[] = {0x0000000c};
const u32 var70056750[] = {0x01030700};
const u32 var70056754[] = {0x00000014};
const u32 var70056758[] = {0x01040800};
const u32 var7005675c[] = {0x000000c4};
const u32 var70056760[] = {0x01050900};
const u32 var70056764[] = {0x000000f8};
const u32 var70056768[] = {0x01060900};
const u32 var7005676c[] = {0x00000158};
const u32 var70056770[] = {0x01070900};
const u32 var70056774[] = {0x000001e8};
const u32 var70056778[] = {0x01080a00};
const u32 var7005677c[] = {0x00000328};
const u32 var70056780[] = {0x01090a00};
const u32 var70056784[] = {0x00000348};
const u32 var70056788[] = {0x010a0a00};
const u32 var7005678c[] = {0x00000088};
const u32 var70056790[] = {0x010b0b00};
const u32 var70056794[] = {0x00000770};
const u32 var70056798[] = {0x010c0c00};
const u32 var7005679c[] = {0x00000930};
const u32 var700567a0[] = {0x010d0b00};
const u32 var700567a4[] = {0x000006b0};
const u32 var700567a8[] = {0x010e0c00};
const u32 var700567ac[] = {0x00000f30};
const u32 var700567b0[] = {0x010f0800};
const u32 var700567b4[] = {0x00000090};
const u32 var700567b8[] = {0x02000600};
const u32 var700567bc[] = {0x0000003c};
const u32 var700567c0[] = {0x02010600};
const u32 var700567c4[] = {0x0000002c};
const u32 var700567c8[] = {0x02020700};
const u32 var700567cc[] = {0x00000074};
const u32 var700567d0[] = {0x02030800};
const u32 var700567d4[] = {0x00000064};
const u32 var700567d8[] = {0x02040900};
const u32 var700567dc[] = {0x00000184};
const u32 var700567e0[] = {0x02050900};
const u32 var700567e4[] = {0x000000b8};
const u32 var700567e8[] = {0x02060a00};
const u32 var700567ec[] = {0x00000398};
const u32 var700567f0[] = {0x02070a00};
const u32 var700567f4[] = {0x00000168};
const u32 var700567f8[] = {0x02080b00};
const u32 var700567fc[] = {0x00000428};
const u32 var70056800[] = {0x02090a00};
const u32 var70056804[] = {0x00000048};
const u32 var70056808[] = {0x020a0b00};
const u32 var7005680c[] = {0x000007f0};
const u32 var70056810[] = {0x020b0b00};
const u32 var70056814[] = {0x00000570};
const u32 var70056818[] = {0x020c0b00};
const u32 var7005681c[] = {0x000003b0};
const u32 var70056820[] = {0x020d0c00};
const u32 var70056824[] = {0x000008b0};
const u32 var70056828[] = {0x020e0c00};
const u32 var7005682c[] = {0x00000730};
const u32 var70056830[] = {0x020f0900};
const u32 var70056834[] = {0x00000010};
const u32 var70056838[] = {0x03000800};
const u32 var7005683c[] = {0x000000b4};
const u32 var70056840[] = {0x03010700};
const u32 var70056844[] = {0x00000054};
const u32 var70056848[] = {0x03020800};
const u32 var7005684c[] = {0x000000e4};
const u32 var70056850[] = {0x03030900};
const u32 var70056854[] = {0x00000144};
const u32 var70056858[] = {0x03040900};
const u32 var7005685c[] = {0x00000004};
const u32 var70056860[] = {0x03050a00};
const u32 var70056864[] = {0x00000138};
const u32 var70056868[] = {0x03060a00};
const u32 var7005686c[] = {0x00000318};
const u32 var70056870[] = {0x03070a00};
const u32 var70056874[] = {0x000003a8};
const u32 var70056878[] = {0x03080b00};
const u32 var7005687c[] = {0x000003c8};
const u32 var70056880[] = {0x03090b00};
const u32 var70056884[] = {0x00000188};
const u32 var70056888[] = {0x030a0c00};
const u32 var7005688c[] = {0x000003f0};
const u32 var70056890[] = {0x030b0c00};
const u32 var70056894[] = {0x000002b0};
const u32 var70056898[] = {0x030c0c00};
const u32 var7005689c[] = {0x00000e30};
const u32 var700568a0[] = {0x030d0d00};
const u32 var700568a4[] = {0x00001830};
const u32 var700568a8[] = {0x030e0d00};
const u32 var700568ac[] = {0x000016d0};
const u32 var700568b0[] = {0x030f0a00};
const u32 var700568b4[] = {0x00000160};
const u32 var700568b8[] = {0x04000900};
const u32 var700568bc[] = {0x000001a4};
const u32 var700568c0[] = {0x04010800};
const u32 var700568c4[] = {0x00000024};
const u32 var700568c8[] = {0x04020900};
const u32 var700568cc[] = {0x00000044};
const u32 var700568d0[] = {0x04030900};
const u32 var700568d4[] = {0x00000104};
const u32 var700568d8[] = {0x04040a00};
const u32 var700568dc[] = {0x00000338};
const u32 var700568e0[] = {0x04050a00};
const u32 var700568e4[] = {0x00000298};
const u32 var700568e8[] = {0x04060b00};
const u32 var700568ec[] = {0x00000668};
const u32 var700568f0[] = {0x04070b00};
const u32 var700568f4[] = {0x00000128};
const u32 var700568f8[] = {0x04080b00};
const u32 var700568fc[] = {0x000006c8};
const u32 var70056900[] = {0x04090c00};
const u32 var70056904[] = {0x00000108};
const u32 var70056908[] = {0x040a0c00};
const u32 var7005690c[] = {0x000006f0};
const u32 var70056910[] = {0x040b0c00};
const u32 var70056914[] = {0x00000470};
const u32 var70056918[] = {0x040c0d00};
const u32 var7005691c[] = {0x00001a30};
const u32 var70056920[] = {0x040d0d00};
const u32 var70056924[] = {0x00000fd0};
const u32 var70056928[] = {0x040e0d00};
const u32 var7005692c[] = {0x00000ad0};
const u32 var70056930[] = {0x040f0900};
const u32 var70056934[] = {0x00000120};
const u32 var70056938[] = {0x05000900};
const u32 var7005693c[] = {0x00000084};
const u32 var70056940[] = {0x05010800};
const u32 var70056944[] = {0x00000078};
const u32 var70056948[] = {0x05020900};
const u32 var7005694c[] = {0x000001b8};
const u32 var70056950[] = {0x05030900};
const u32 var70056954[] = {0x00000038};
const u32 var70056958[] = {0x05040a00};
const u32 var7005695c[] = {0x00000198};
const u32 var70056960[] = {0x05050b00};
const u32 var70056964[] = {0x000004e8};
const u32 var70056968[] = {0x05060b00};
const u32 var7005696c[] = {0x000005a8};
const u32 var70056970[] = {0x05070c00};
const u32 var70056974[] = {0x00000908};
const u32 var70056978[] = {0x05080b00};
const u32 var7005697c[] = {0x00000388};
const u32 var70056980[] = {0x05090c00};
const u32 var70056984[] = {0x00000bf0};
const u32 var70056988[] = {0x050a0c00};
const u32 var7005698c[] = {0x00000170};
const u32 var70056990[] = {0x050b0d00};
const u32 var70056994[] = {0x00000130};
const u32 var70056998[] = {0x050c0d00};
const u32 var7005699c[] = {0x00000430};
const u32 var700569a0[] = {0x050d0d00};
const u32 var700569a4[] = {0x00000bd0};
const u32 var700569a8[] = {0x050e0e00};
const u32 var700569ac[] = {0x00002f60};
const u32 var700569b0[] = {0x050f0a00};
const u32 var700569b4[] = {0x00000020};
const u32 var700569b8[] = {0x06000a00};
const u32 var700569bc[] = {0x000003d8};
const u32 var700569c0[] = {0x06010900};
const u32 var700569c4[] = {0x000000d8};
const u32 var700569c8[] = {0x06020900};
const u32 var700569cc[] = {0x00000058};
const u32 var700569d0[] = {0x06030a00};
const u32 var700569d4[] = {0x00000098};
const u32 var700569d8[] = {0x06040b00};
const u32 var700569dc[] = {0x000000e8};
const u32 var700569e0[] = {0x06050b00};
const u32 var700569e4[] = {0x00000268};
const u32 var700569e8[] = {0x06060b00};
const u32 var700569ec[] = {0x00000028};
const u32 var700569f0[] = {0x06070b00};
const u32 var700569f4[] = {0x00000508};
const u32 var700569f8[] = {0x06080c00};
const u32 var700569fc[] = {0x00000808};
const u32 var70056a00[] = {0x06090c00};
const u32 var70056a04[] = {0x000002f0};
const u32 var70056a08[] = {0x060a0c00};
const u32 var70056a0c[] = {0x00000270};
const u32 var70056a10[] = {0x060b0c00};
const u32 var70056a14[] = {0x000009b0};
const u32 var70056a18[] = {0x060c0d00};
const u32 var70056a1c[] = {0x00001030};
const u32 var70056a20[] = {0x060d0d00};
const u32 var70056a24[] = {0x00000ed0};
const u32 var70056a28[] = {0x060e0e00};
const u32 var70056a2c[] = {0x000034d0};
const u32 var70056a30[] = {0x060f0a00};
const u32 var70056a34[] = {0x00000140};
const u32 var70056a38[] = {0x07000a00};
const u32 var70056a3c[] = {0x00000118};
const u32 var70056a40[] = {0x07010900};
const u32 var70056a44[] = {0x00000018};
const u32 var70056a48[] = {0x07020a00};
const u32 var70056a4c[] = {0x00000368};
const u32 var70056a50[] = {0x07030a00};
const u32 var70056a54[] = {0x00000068};
const u32 var70056a58[] = {0x07040b00};
const u32 var70056a5c[] = {0x00000528};
const u32 var70056a60[] = {0x07050b00};
const u32 var70056a64[] = {0x000005c8};
const u32 var70056a68[] = {0x07060b00};
const u32 var70056a6c[] = {0x00000148};
const u32 var70056a70[] = {0x07070c00};
const u32 var70056a74[] = {0x00000a08};
const u32 var70056a78[] = {0x07080c00};
const u32 var70056a7c[] = {0x000001f0};
const u32 var70056a80[] = {0x07090d00};
const u32 var70056a84[] = {0x00001d30};
const u32 var70056a88[] = {0x070a0d00};
const u32 var70056a8c[] = {0x00001630};
const u32 var70056a90[] = {0x070b0d00};
const u32 var70056a94[] = {0x000005d0};
const u32 var70056a98[] = {0x070c0d00};
const u32 var70056a9c[] = {0x000007d0};
const u32 var70056aa0[] = {0x070d0f00};
const u32 var70056aa4[] = {0x00004f60};
const u32 var70056aa8[] = {0x070e0f00};
const u32 var70056aac[] = {0x00001760};
const u32 var70056ab0[] = {0x070f0a00};
const u32 var70056ab4[] = {0x00000040};
const u32 var70056ab8[] = {0x08000a00};
const u32 var70056abc[] = {0x000002a8};
const u32 var70056ac0[] = {0x08010a00};
const u32 var70056ac4[] = {0x000000a8};
const u32 var70056ac8[] = {0x08020a00};
const u32 var70056acc[] = {0x00000228};
const u32 var70056ad0[] = {0x08030b00};
const u32 var70056ad4[] = {0x000007c8};
const u32 var70056ad8[] = {0x08040b00};
const u32 var70056adc[] = {0x000001c8};
const u32 var70056ae0[] = {0x08050b00};
const u32 var70056ae4[] = {0x00000788};
const u32 var70056ae8[] = {0x08060c00};
const u32 var70056aec[] = {0x00000208};
const u32 var70056af0[] = {0x08070c00};
const u32 var70056af4[] = {0x000009f0};
const u32 var70056af8[] = {0x08080d00};
const u32 var70056afc[] = {0x00001ab0};
const u32 var70056b00[] = {0x08090d00};
const u32 var70056b04[] = {0x00001130};
const u32 var70056b08[] = {0x080a0d00};
const u32 var70056b0c[] = {0x00000230};
const u32 var70056b10[] = {0x080b0d00};
const u32 var70056b14[] = {0x00001fd0};
const u32 var70056b18[] = {0x080c0e00};
const u32 var70056b1c[] = {0x00003ad0};
const u32 var70056b20[] = {0x080d0e00};
const u32 var70056b24[] = {0x000024d0};
const u32 var70056b28[] = {0x080e0e00};
const u32 var70056b2c[] = {0x000008d0};
const u32 var70056b30[] = {0x080f0a00};
const u32 var70056b34[] = {0x00000380};
const u32 var70056b38[] = {0x09000b00};
const u32 var70056b3c[] = {0x000002c8};
const u32 var70056b40[] = {0x09010a00};
const u32 var70056b44[] = {0x000000c8};
const u32 var70056b48[] = {0x09020a00};
const u32 var70056b4c[] = {0x00000248};
const u32 var70056b50[] = {0x09030b00};
const u32 var70056b54[] = {0x00000588};
const u32 var70056b58[] = {0x09040b00};
const u32 var70056b5c[] = {0x00000608};
const u32 var70056b60[] = {0x09050c00};
const u32 var70056b64[] = {0x00000008};
const u32 var70056b68[] = {0x09060c00};
const u32 var70056b6c[] = {0x00000af0};
const u32 var70056b70[] = {0x09070d00};
const u32 var70056b74[] = {0x00000ab0};
const u32 var70056b78[] = {0x09080d00};
const u32 var70056b7c[] = {0x00000d30};
const u32 var70056b80[] = {0x09090d00};
const u32 var70056b84[] = {0x00000a30};
const u32 var70056b88[] = {0x090a0d00};
const u32 var70056b8c[] = {0x00000030};
const u32 var70056b90[] = {0x090b0e00};
const u32 var70056b94[] = {0x00003ed0};
const u32 var70056b98[] = {0x090c0d00};
const u32 var70056b9c[] = {0x00001cd0};
const u32 var70056ba0[] = {0x090d0e00};
const u32 var70056ba4[] = {0x000018d0};
const u32 var70056ba8[] = {0x090e0d00};
const u32 var70056bac[] = {0x000000d0};
const u32 var70056bb0[] = {0x090f0b00};
const u32 var70056bb4[] = {0x00000680};
const u32 var70056bb8[] = {0x0a000b00};
const u32 var70056bbc[] = {0x00000688};
const u32 var70056bc0[] = {0x0a010b00};
const u32 var70056bc4[] = {0x00000408};
const u32 var70056bc8[] = {0x0a020a00};
const u32 var70056bcc[] = {0x00000308};
const u32 var70056bd0[] = {0x0a030b00};
const u32 var70056bd4[] = {0x000005f0};
const u32 var70056bd8[] = {0x0a040c00};
const u32 var70056bdc[] = {0x00000ef0};
const u32 var70056be0[] = {0x0a050c00};
const u32 var70056be4[] = {0x00000970};
const u32 var70056be8[] = {0x0a060c00};
const u32 var70056bec[] = {0x00000a70};
const u32 var70056bf0[] = {0x0a070c00};
const u32 var70056bf4[] = {0x00000db0};
const u32 var70056bf8[] = {0x0a080d00};
const u32 var70056bfc[] = {0x00001230};
const u32 var70056c00[] = {0x0a090e00};
const u32 var70056c04[] = {0x000039d0};
const u32 var70056c08[] = {0x0a0a0e00};
const u32 var70056c0c[] = {0x000021d0};
const u32 var70056c10[] = {0x0a0b0e00};
const u32 var70056c14[] = {0x000002d0};
const u32 var70056c18[] = {0x0a0c0f00};
const u32 var70056c1c[] = {0x00005760};
const u32 var70056c20[] = {0x0a0d0f00};
const u32 var70056c24[] = {0x00002760};
const u32 var70056c28[] = {0x0a0e0e00};
const u32 var70056c2c[] = {0x00003b60};
const u32 var70056c30[] = {0x0a0f0a00};
const u32 var70056c34[] = {0x00000080};
const u32 var70056c38[] = {0x0b000c00};
const u32 var70056c3c[] = {0x00000cf0};
const u32 var70056c40[] = {0x0b010b00};
const u32 var70056c44[] = {0x000000f0};
const u32 var70056c48[] = {0x0b020b00};
const u32 var70056c4c[] = {0x00000370};
const u32 var70056c50[] = {0x0b030b00};
const u32 var70056c54[] = {0x00000670};
const u32 var70056c58[] = {0x0b040c00};
const u32 var70056c5c[] = {0x00000c70};
const u32 var70056c60[] = {0x0b050c00};
const u32 var70056c64[] = {0x00000fb0};
const u32 var70056c68[] = {0x0b060d00};
const u32 var70056c6c[] = {0x00000630};
const u32 var70056c70[] = {0x0b070e00};
const u32 var70056c74[] = {0x000015d0};
const u32 var70056c78[] = {0x0b080e00};
const u32 var70056c7c[] = {0x000019d0};
const u32 var70056c80[] = {0x0b090e00};
const u32 var70056c84[] = {0x000001d0};
const u32 var70056c88[] = {0x0b0a0e00};
const u32 var70056c8c[] = {0x000022d0};
const u32 var70056c90[] = {0x0b0b0e00};
const u32 var70056c94[] = {0x000004d0};
const u32 var70056c98[] = {0x0b0c0e00};
const u32 var70056c9c[] = {0x000010d0};
const u32 var70056ca0[] = {0x0b0d0d00};
const u32 var70056ca4[] = {0x00001f60};
const u32 var70056ca8[] = {0x0b0e0e00};
const u32 var70056cac[] = {0x00000b60};
const u32 var70056cb0[] = {0x0b0f0b00};
const u32 var70056cb4[] = {0x00000300};
const u32 var70056cb8[] = {0x0c000c00};
const u32 var70056cbc[] = {0x00000530};
const u32 var70056cc0[] = {0x0c010c00};
const u32 var70056cc4[] = {0x00000070};
const u32 var70056cc8[] = {0x0c020c00};
const u32 var70056ccc[] = {0x000007b0};
const u32 var70056cd0[] = {0x0c030c00};
const u32 var70056cd4[] = {0x000005b0};
const u32 var70056cd8[] = {0x0c040c00};
const u32 var70056cdc[] = {0x000001b0};
const u32 var70056ce0[] = {0x0c050d00};
const u32 var70056ce4[] = {0x00001430};
const u32 var70056ce8[] = {0x0c060d00};
const u32 var70056cec[] = {0x00000830};
const u32 var70056cf0[] = {0x0c070d00};
const u32 var70056cf4[] = {0x000017d0};
const u32 var70056cf8[] = {0x0c080d00};
const u32 var70056cfc[] = {0x000006d0};
const u32 var70056d00[] = {0x0c090f00};
const u32 var70056d04[] = {0x00000f60};
const u32 var70056d08[] = {0x0c0a0e00};
const u32 var70056d0c[] = {0x00003760};
const u32 var70056d10[] = {0x0c0b0e00};
const u32 var70056d14[] = {0x000030d0};
const u32 var70056d18[] = {0x0c0c0e00};
const u32 var70056d1c[] = {0x00000760};
const u32 var70056d20[] = {0x0c0d0e00};
const u32 var70056d24[] = {0x00002b60};
const u32 var70056d28[] = {0x0c0e1000};
const u32 var70056d2c[] = {0x00000360};
const u32 var70056d30[] = {0x0c0f0b00};
const u32 var70056d34[] = {0x00000100};
const u32 var70056d38[] = {0x0d000e00};
const u32 var70056d3c[] = {0x000035d0};
const u32 var70056d40[] = {0x0d010c00};
const u32 var70056d44[] = {0x00000cb0};
const u32 var70056d48[] = {0x0d020c00};
const u32 var70056d4c[] = {0x000004b0};
const u32 var70056d50[] = {0x0d030c00};
const u32 var70056d54[] = {0x000000b0};
const u32 var70056d58[] = {0x0d040d00};
const u32 var70056d5c[] = {0x000009d0};
const u32 var70056d60[] = {0x0d050d00};
const u32 var70056d64[] = {0x00001bd0};
const u32 var70056d68[] = {0x0d060e00};
const u32 var70056d6c[] = {0x00001ed0};
const u32 var70056d70[] = {0x0d070e00};
const u32 var70056d74[] = {0x000032d0};
const u32 var70056d78[] = {0x0d080e00};
const u32 var70056d7c[] = {0x000014d0};
const u32 var70056d80[] = {0x0d091000};
const u32 var70056d84[] = {0x0000e360};
const u32 var70056d88[] = {0x0d0a0f00};
const u32 var70056d8c[] = {0x00006760};
const u32 var70056d90[] = {0x0d0b0f00};
const u32 var70056d94[] = {0x00005b60};
const u32 var70056d98[] = {0x0d0c0f00};
const u32 var70056d9c[] = {0x00001b60};
const u32 var70056da0[] = {0x0d0d1100};
const u32 var70056da4[] = {0x00018360};
const u32 var70056da8[] = {0x0d0e0f00};
const u32 var70056dac[] = {0x00004360};
const u32 var70056db0[] = {0x0d0f0b00};
const u32 var70056db4[] = {0x00000200};
const u32 var70056db8[] = {0x0e000d00};
const u32 var70056dbc[] = {0x000013d0};
const u32 var70056dc0[] = {0x0e010d00};
const u32 var70056dc4[] = {0x000011d0};
const u32 var70056dc8[] = {0x0e020b00};
const u32 var70056dcc[] = {0x00000330};
const u32 var70056dd0[] = {0x0e030c00};
const u32 var70056dd4[] = {0x00000dd0};
const u32 var70056dd8[] = {0x0e040e00};
const u32 var70056ddc[] = {0x00001ad0};
const u32 var70056de0[] = {0x0e050e00};
const u32 var70056de4[] = {0x000012d0};
const u32 var70056de8[] = {0x0e060d00};
const u32 var70056dec[] = {0x00000cd0};
const u32 var70056df0[] = {0x0e070e00};
const u32 var70056df4[] = {0x000038d0};
const u32 var70056df8[] = {0x0e080e00};
const u32 var70056dfc[] = {0x000028d0};
const u32 var70056e00[] = {0x0e090f00};
const u32 var70056e04[] = {0x00002360};
const u32 var70056e08[] = {0x0e0a1000};
const u32 var70056e0c[] = {0x00006360};
const u32 var70056e10[] = {0x0e0b0f00};
const u32 var70056e14[] = {0x00007360};
const u32 var70056e18[] = {0x0e0c1100};
const u32 var70056e1c[] = {0x00008360};
const u32 var70056e20[] = {0x0e0d0f00};
const u32 var70056e24[] = {0x00003360};
const u32 var70056e28[] = {0x0e0e0e00};
const u32 var70056e2c[] = {0x00001360};
const u32 var70056e30[] = {0x0e0f0b00};
const u32 var70056e34[] = {0x00000000};
const u32 var70056e38[] = {0x0f000900};
const u32 var70056e3c[] = {0x00000060};
const u32 var70056e40[] = {0x0f010800};
const u32 var70056e44[] = {0x00000050};
const u32 var70056e48[] = {0x0f020800};
const u32 var70056e4c[] = {0x000000e0};
const u32 var70056e50[] = {0x0f030900};
const u32 var70056e54[] = {0x000001a0};
const u32 var70056e58[] = {0x0f040900};
const u32 var70056e5c[] = {0x000000a0};
const u32 var70056e60[] = {0x0f050a00};
const u32 var70056e64[] = {0x00000220};
const u32 var70056e68[] = {0x0f060a00};
const u32 var70056e6c[] = {0x00000340};
const u32 var70056e70[] = {0x0f070a00};
const u32 var70056e74[] = {0x00000240};
const u32 var70056e78[] = {0x0f080b00};
const u32 var70056e7c[] = {0x00000580};
const u32 var70056e80[] = {0x0f090b00};
const u32 var70056e84[] = {0x00000180};
const u32 var70056e88[] = {0x0f0a0b00};
const u32 var70056e8c[] = {0x00000280};
const u32 var70056e90[] = {0x0f0b0b00};
const u32 var70056e94[] = {0x00000700};
const u32 var70056e98[] = {0x0f0c0b00};
const u32 var70056e9c[] = {0x00000500};
const u32 var70056ea0[] = {0x0f0d0b00};
const u32 var70056ea4[] = {0x00000600};
const u32 var70056ea8[] = {0x0f0e0b00};
const u32 var70056eac[] = {0x00000400};
const u32 var70056eb0[] = {0x0f0f0800};
const u32 var70056eb4[] = {0x000000c0};
const u32 var70056eb8[] = {0x64646400};
const u32 var70056ebc[] = {0x00000000};
const u32 var70056ec0[] = {0x00000400};
const u32 var70056ec4[] = {0x0000000f};
const u32 var70056ec8[] = {0x00010400};
const u32 var70056ecc[] = {0x0000000b};
const u32 var70056ed0[] = {0x00020600};
const u32 var70056ed4[] = {0x0000001d};
const u32 var70056ed8[] = {0x00030700};
const u32 var70056edc[] = {0x00000005};
const u32 var70056ee0[] = {0x00040800};
const u32 var70056ee4[] = {0x00000049};
const u32 var70056ee8[] = {0x00050900};
const u32 var70056eec[] = {0x000000c1};
const u32 var70056ef0[] = {0x00060900};
const u32 var70056ef4[] = {0x0000003e};
const u32 var70056ef8[] = {0x00070a00};
const u32 var70056efc[] = {0x00000136};
const u32 var70056f00[] = {0x00080a00};
const u32 var70056f04[] = {0x00000156};
const u32 var70056f08[] = {0x00090b00};
const u32 var70056f0c[] = {0x000005ca};
const u32 var70056f10[] = {0x000a0b00};
const u32 var70056f14[] = {0x0000058a};
const u32 var70056f18[] = {0x000b0b00};
const u32 var70056f1c[] = {0x0000048a};
const u32 var70056f20[] = {0x000c0b00};
const u32 var70056f24[] = {0x000005b2};
const u32 var70056f28[] = {0x000d0b00};
const u32 var70056f2c[] = {0x00000502};
const u32 var70056f30[] = {0x000e0c00};
const u32 var70056f34[] = {0x00000102};
const u32 var70056f38[] = {0x000f0900};
const u32 var70056f3c[] = {0x00000034};
const u32 var70056f40[] = {0x01000400};
const u32 var70056f44[] = {0x00000007};
const u32 var70056f48[] = {0x01010400};
const u32 var70056f4c[] = {0x00000003};
const u32 var70056f50[] = {0x01020500};
const u32 var70056f54[] = {0x00000015};
const u32 var70056f58[] = {0x01030600};
const u32 var70056f5c[] = {0x00000019};
const u32 var70056f60[] = {0x01040700};
const u32 var70056f64[] = {0x00000071};
const u32 var70056f68[] = {0x01050800};
const u32 var70056f6c[] = {0x00000041};
const u32 var70056f70[] = {0x01060800};
const u32 var70056f74[] = {0x0000005e};
const u32 var70056f78[] = {0x01070900};
const u32 var70056f7c[] = {0x00000036};
const u32 var70056f80[] = {0x01080900};
const u32 var70056f84[] = {0x00000116};
const u32 var70056f88[] = {0x01090900};
const u32 var70056f8c[] = {0x000000c6};
const u32 var70056f90[] = {0x010a0a00};
const u32 var70056f94[] = {0x0000038a};
const u32 var70056f98[] = {0x010b0a00};
const u32 var70056f9c[] = {0x0000026a};
const u32 var70056fa0[] = {0x010c0a00};
const u32 var70056fa4[] = {0x000003f2};
const u32 var70056fa8[] = {0x010d0a00};
const u32 var70056fac[] = {0x00000252};
const u32 var70056fb0[] = {0x010e0a00};
const u32 var70056fb4[] = {0x000003a2};
const u32 var70056fb8[] = {0x010f0800};
const u32 var70056fbc[] = {0x00000054};
const u32 var70056fc0[] = {0x02000600};
const u32 var70056fc4[] = {0x0000003d};
const u32 var70056fc8[] = {0x02010500};
const u32 var70056fcc[] = {0x0000000d};
const u32 var70056fd0[] = {0x02020600};
const u32 var70056fd4[] = {0x00000025};
const u32 var70056fd8[] = {0x02030700};
const u32 var70056fdc[] = {0x00000029};
const u32 var70056fe0[] = {0x02040700};
const u32 var70056fe4[] = {0x00000011};
const u32 var70056fe8[] = {0x02050800};
const u32 var70056fec[] = {0x00000001};
const u32 var70056ff0[] = {0x02060800};
const u32 var70056ff4[] = {0x0000001e};
const u32 var70056ff8[] = {0x02070900};
const u32 var70056ffc[] = {0x00000176};
const u32 var70057000[] = {0x02080900};
const u32 var70057004[] = {0x000001e6};
const u32 var70057008[] = {0x02090900};
const u32 var7005700c[] = {0x00000086};
const u32 var70057010[] = {0x020a0900};
const u32 var70057014[] = {0x000000da};
const u32 var70057018[] = {0x020b0a00};
const u32 var7005701c[] = {0x000000aa};
const u32 var70057020[] = {0x020c0a00};
const u32 var70057024[] = {0x00000372};
const u32 var70057028[] = {0x020d0a00};
const u32 var7005702c[] = {0x00000392};
const u32 var70057030[] = {0x020e0b00};
const u32 var70057034[] = {0x000005c2};
const u32 var70057038[] = {0x020f0700};
const u32 var7005703c[] = {0x00000024};
const u32 var70057040[] = {0x03000700};
const u32 var70057044[] = {0x00000045};
const u32 var70057048[] = {0x03010600};
const u32 var7005704c[] = {0x00000039};
const u32 var70057050[] = {0x03020700};
const u32 var70057054[] = {0x00000069};
const u32 var70057058[] = {0x03030700};
const u32 var7005705c[] = {0x00000031};
const u32 var70057060[] = {0x03040800};
const u32 var70057064[] = {0x00000061};
const u32 var70057068[] = {0x03050800};
const u32 var7005706c[] = {0x000000be};
const u32 var70057070[] = {0x03060800};
const u32 var70057074[] = {0x0000002e};
const u32 var70057078[] = {0x03070900};
const u32 var7005707c[] = {0x00000076};
const u32 var70057080[] = {0x03080900};
const u32 var70057084[] = {0x00000066};
const u32 var70057088[] = {0x03090900};
const u32 var7005708c[] = {0x000000fa};
const u32 var70057090[] = {0x030a0900};
const u32 var70057094[] = {0x0000009a};
const u32 var70057098[] = {0x030b0a00};
const u32 var7005709c[] = {0x0000028a};
const u32 var700570a0[] = {0x030c0a00};
const u32 var700570a4[] = {0x000003b2};
const u32 var700570a8[] = {0x030d0a00};
const u32 var700570ac[] = {0x00000292};
const u32 var700570b0[] = {0x030e0a00};
const u32 var700570b4[] = {0x000003c2};
const u32 var700570b8[] = {0x030f0700};
const u32 var700570bc[] = {0x00000004};
const u32 var700570c0[] = {0x04000800};
const u32 var700570c4[] = {0x000000c9};
const u32 var700570c8[] = {0x04010700};
const u32 var700570cc[] = {0x00000009};
const u32 var700570d0[] = {0x04020700};
const u32 var700570d4[] = {0x00000051};
const u32 var700570d8[] = {0x04030800};
const u32 var700570dc[] = {0x000000e1};
const u32 var700570e0[] = {0x04040800};
const u32 var700570e4[] = {0x000000fe};
const u32 var700570e8[] = {0x04050800};
const u32 var700570ec[] = {0x0000006e};
const u32 var700570f0[] = {0x04060800};
const u32 var700570f4[] = {0x0000000e};
const u32 var700570f8[] = {0x04070900};
const u32 var700570fc[] = {0x00000096};
const u32 var70057100[] = {0x04080900};
const u32 var70057104[] = {0x00000026};
const u32 var70057108[] = {0x04090900};
const u32 var7005710c[] = {0x0000007a};
const u32 var70057110[] = {0x040a0a00};
const u32 var70057114[] = {0x0000001a};
const u32 var70057118[] = {0x040b0a00};
const u32 var7005711c[] = {0x0000030a};
const u32 var70057120[] = {0x040c0a00};
const u32 var70057124[] = {0x00000132};
const u32 var70057128[] = {0x040d0a00};
const u32 var7005712c[] = {0x000002e2};
const u32 var70057130[] = {0x040e0b00};
const u32 var70057134[] = {0x000001c2};
const u32 var70057138[] = {0x040f0700};
const u32 var7005713c[] = {0x00000038};
const u32 var70057140[] = {0x05000900};
const u32 var70057144[] = {0x000001c1};
const u32 var70057148[] = {0x05010700};
const u32 var7005714c[] = {0x00000021};
const u32 var70057150[] = {0x05020800};
const u32 var70057154[] = {0x00000081};
const u32 var70057158[] = {0x05030800};
const u32 var7005715c[] = {0x0000007e};
const u32 var70057160[] = {0x05040800};
const u32 var70057164[] = {0x000000ee};
const u32 var70057168[] = {0x05050800};
const u32 var7005716c[] = {0x0000004e};
const u32 var70057170[] = {0x05060900};
const u32 var70057174[] = {0x000000d6};
const u32 var70057178[] = {0x05070900};
const u32 var7005717c[] = {0x000000a6};
const u32 var70057180[] = {0x05080900};
const u32 var70057184[] = {0x00000006};
const u32 var70057188[] = {0x05090900};
const u32 var7005718c[] = {0x0000005a};
const u32 var70057190[] = {0x050a0a00};
const u32 var70057194[] = {0x000002aa};
const u32 var70057198[] = {0x050b0a00};
const u32 var7005719c[] = {0x000002f2};
const u32 var700571a0[] = {0x050c0a00};
const u32 var700571a4[] = {0x000002d2};
const u32 var700571a8[] = {0x050d0a00};
const u32 var700571ac[] = {0x00000262};
const u32 var700571b0[] = {0x050e0a00};
const u32 var700571b4[] = {0x00000182};
const u32 var700571b8[] = {0x050f0700};
const u32 var700571bc[] = {0x00000018};
const u32 var700571c0[] = {0x06000900};
const u32 var700571c4[] = {0x0000013e};
const u32 var700571c8[] = {0x06010800};
const u32 var700571cc[] = {0x000000de};
const u32 var700571d0[] = {0x06020800};
const u32 var700571d4[] = {0x0000009e};
const u32 var700571d8[] = {0x06030800};
const u32 var700571dc[] = {0x000000ae};
const u32 var700571e0[] = {0x06040800};
const u32 var700571e4[] = {0x0000008e};
const u32 var700571e8[] = {0x06050900};
const u32 var700571ec[] = {0x000001d6};
const u32 var700571f0[] = {0x06060900};
const u32 var700571f4[] = {0x000000e6};
const u32 var700571f8[] = {0x06070900};
const u32 var700571fc[] = {0x00000186};
const u32 var70057200[] = {0x06080900};
const u32 var70057204[] = {0x0000013a};
const u32 var70057208[] = {0x06090a00};
const u32 var7005720c[] = {0x0000036a};
const u32 var70057210[] = {0x060a0a00};
const u32 var70057214[] = {0x0000014a};
const u32 var70057218[] = {0x060b0a00};
const u32 var7005721c[] = {0x000000b2};
const u32 var70057220[] = {0x060c0a00};
const u32 var70057224[] = {0x00000312};
const u32 var70057228[] = {0x060d0a00};
const u32 var7005722c[] = {0x00000022};
const u32 var70057230[] = {0x060e0b00};
const u32 var70057234[] = {0x00000082};
const u32 var70057238[] = {0x060f0700};
const u32 var7005723c[] = {0x00000028};
const u32 var70057240[] = {0x07000a00};
const u32 var70057244[] = {0x00000336};
const u32 var70057248[] = {0x07010800};
const u32 var7005724c[] = {0x000000ce};
const u32 var70057250[] = {0x07020800};
const u32 var70057254[] = {0x000000f6};
const u32 var70057258[] = {0x07030800};
const u32 var7005725c[] = {0x000000b6};
const u32 var70057260[] = {0x07040900};
const u32 var70057264[] = {0x00000196};
const u32 var70057268[] = {0x07050900};
const u32 var7005726c[] = {0x000001a6};
const u32 var70057270[] = {0x07060900};
const u32 var70057274[] = {0x00000046};
const u32 var70057278[] = {0x07070900};
const u32 var7005727c[] = {0x000001ba};
const u32 var70057280[] = {0x07080a00};
const u32 var70057284[] = {0x0000021a};
const u32 var70057288[] = {0x07090a00};
const u32 var7005728c[] = {0x000000ca};
const u32 var70057290[] = {0x070a0a00};
const u32 var70057294[] = {0x00000272};
const u32 var70057298[] = {0x070b0a00};
const u32 var7005729c[] = {0x00000152};
const u32 var700572a0[] = {0x070c0a00};
const u32 var700572a4[] = {0x00000362};
const u32 var700572a8[] = {0x070d0b00};
const u32 var700572ac[] = {0x00000642};
const u32 var700572b0[] = {0x070e0b00};
const u32 var700572b4[] = {0x000005f4};
const u32 var700572b8[] = {0x070f0800};
const u32 var700572bc[] = {0x00000088};
const u32 var700572c0[] = {0x08000a00};
const u32 var700572c4[] = {0x00000356};
const u32 var700572c8[] = {0x08010900};
const u32 var700572cc[] = {0x00000056};
const u32 var700572d0[] = {0x08020900};
const u32 var700572d4[] = {0x00000016};
const u32 var700572d8[] = {0x08030900};
const u32 var700572dc[] = {0x00000166};
const u32 var700572e0[] = {0x08040900};
const u32 var700572e4[] = {0x00000126};
const u32 var700572e8[] = {0x08050900};
const u32 var700572ec[] = {0x00000106};
const u32 var700572f0[] = {0x08060900};
const u32 var700572f4[] = {0x000000ba};
const u32 var700572f8[] = {0x08070900};
const u32 var700572fc[] = {0x0000011a};
const u32 var70057300[] = {0x08080900};
const u32 var70057304[] = {0x0000012a};
const u32 var70057308[] = {0x08090a00};
const u32 var7005730c[] = {0x0000000a};
const u32 var70057310[] = {0x080a0a00};
const u32 var70057314[] = {0x000003d2};
const u32 var70057318[] = {0x080b0a00};
const u32 var7005731c[] = {0x000001e2};
const u32 var70057320[] = {0x080c0a00};
const u32 var70057324[] = {0x000000c2};
const u32 var70057328[] = {0x080d0b00};
const u32 var7005732c[] = {0x00000202};
const u32 var70057330[] = {0x080e0b00};
const u32 var70057334[] = {0x000004f4};
const u32 var70057338[] = {0x080f0800};
const u32 var7005733c[] = {0x00000008};
const u32 var70057340[] = {0x09000a00};
const u32 var70057344[] = {0x000003ca};
const u32 var70057348[] = {0x09010900};
const u32 var7005734c[] = {0x000001c6};
const u32 var70057350[] = {0x09020900};
const u32 var70057354[] = {0x00000146};
const u32 var70057358[] = {0x09030900};
const u32 var7005735c[] = {0x000001fa};
const u32 var70057360[] = {0x09040900};
const u32 var70057364[] = {0x0000017a};
const u32 var70057368[] = {0x09050900};
const u32 var7005736c[] = {0x0000015a};
const u32 var70057370[] = {0x09060900};
const u32 var70057374[] = {0x000000ea};
const u32 var70057378[] = {0x09070a00};
const u32 var7005737c[] = {0x000002ca};
const u32 var70057380[] = {0x09080a00};
const u32 var70057384[] = {0x0000020a};
const u32 var70057388[] = {0x09090a00};
const u32 var7005738c[] = {0x00000232};
const u32 var70057390[] = {0x090a0a00};
const u32 var70057394[] = {0x00000212};
const u32 var70057398[] = {0x090b0a00};
const u32 var7005739c[] = {0x00000322};
const u32 var700573a0[] = {0x090c0b00};
const u32 var700573a4[] = {0x00000482};
const u32 var700573a8[] = {0x090d0b00};
const u32 var700573ac[] = {0x000006f4};
const u32 var700573b0[] = {0x090e0b00};
const u32 var700573b4[] = {0x00000674};
const u32 var700573b8[] = {0x090f0800};
const u32 var700573bc[] = {0x000000d0};
const u32 var700573c0[] = {0x0a000b00};
const u32 var700573c4[] = {0x000001ca};
const u32 var700573c8[] = {0x0a010900};
const u32 var700573cc[] = {0x0000003a};
const u32 var700573d0[] = {0x0a020900};
const u32 var700573d4[] = {0x000001da};
const u32 var700573d8[] = {0x0a030900};
const u32 var700573dc[] = {0x0000019a};
const u32 var700573e0[] = {0x0a040900};
const u32 var700573e4[] = {0x000001ea};
const u32 var700573e8[] = {0x0a050a00};
const u32 var700573ec[] = {0x0000006a};
const u32 var700573f0[] = {0x0a060a00};
const u32 var700573f4[] = {0x0000034a};
const u32 var700573f8[] = {0x0a070a00};
const u32 var700573fc[] = {0x00000172};
const u32 var70057400[] = {0x0a080a00};
const u32 var70057404[] = {0x00000032};
const u32 var70057408[] = {0x0a090a00};
const u32 var7005740c[] = {0x00000112};
const u32 var70057410[] = {0x0a0a0a00};
const u32 var70057414[] = {0x000002a2};
const u32 var70057418[] = {0x0a0b0b00};
const u32 var7005741c[] = {0x00000242};
const u32 var70057420[] = {0x0a0c0b00};
const u32 var70057424[] = {0x000007f4};
const u32 var70057428[] = {0x0a0d0b00};
const u32 var7005742c[] = {0x00000574};
const u32 var70057430[] = {0x0a0e0b00};
const u32 var70057434[] = {0x000003b4};
const u32 var70057438[] = {0x0a0f0800};
const u32 var7005743c[] = {0x00000050};
const u32 var70057440[] = {0x0b000b00};
const u32 var70057444[] = {0x0000018a};
const u32 var70057448[] = {0x0b010a00};
const u32 var7005744c[] = {0x0000016a};
const u32 var70057450[] = {0x0b020900};
const u32 var70057454[] = {0x000001aa};
const u32 var70057458[] = {0x0b030900};
const u32 var7005745c[] = {0x0000002a};
const u32 var70057460[] = {0x0b040900};
const u32 var70057464[] = {0x0000004a};
const u32 var70057468[] = {0x0b050a00};
const u32 var7005746c[] = {0x000001f2};
const u32 var70057470[] = {0x0b060a00};
const u32 var70057474[] = {0x000002b2};
const u32 var70057478[] = {0x0b070a00};
const u32 var7005747c[] = {0x00000352};
const u32 var70057480[] = {0x0b080a00};
const u32 var70057484[] = {0x000003e2};
const u32 var70057488[] = {0x0b090a00};
const u32 var7005748c[] = {0x000000a2};
const u32 var70057490[] = {0x0b0a0a00};
const u32 var70057494[] = {0x00000382};
const u32 var70057498[] = {0x0b0b0b00};
const u32 var7005749c[] = {0x00000402};
const u32 var700574a0[] = {0x0b0c0b00};
const u32 var700574a4[] = {0x00000774};
const u32 var700574a8[] = {0x0b0d0b00};
const u32 var700574ac[] = {0x00000074};
const u32 var700574b0[] = {0x0b0e0b00};
const u32 var700574b4[] = {0x000002b4};
const u32 var700574b8[] = {0x0b0f0800};
const u32 var700574bc[] = {0x00000060};
const u32 var700574c0[] = {0x0c000b00};
const u32 var700574c4[] = {0x0000008a};
const u32 var700574c8[] = {0x0c010a00};
const u32 var700574cc[] = {0x0000010a};
const u32 var700574d0[] = {0x0c020a00};
const u32 var700574d4[] = {0x000000f2};
const u32 var700574d8[] = {0x0c030a00};
const u32 var700574dc[] = {0x00000072};
const u32 var700574e0[] = {0x0c040a00};
const u32 var700574e4[] = {0x00000332};
const u32 var700574e8[] = {0x0c050a00};
const u32 var700574ec[] = {0x000001d2};
const u32 var700574f0[] = {0x0c060a00};
const u32 var700574f4[] = {0x00000092};
const u32 var700574f8[] = {0x0c070a00};
const u32 var700574fc[] = {0x000000e2};
const u32 var70057500[] = {0x0c080a00};
const u32 var70057504[] = {0x000002c2};
const u32 var70057508[] = {0x0c090a00};
const u32 var7005750c[] = {0x00000282};
const u32 var70057510[] = {0x0c0a0b00};
const u32 var70057514[] = {0x00000002};
const u32 var70057518[] = {0x0c0b0b00};
const u32 var7005751c[] = {0x000000f4};
const u32 var70057520[] = {0x0c0c0b00};
const u32 var70057524[] = {0x00000274};
const u32 var70057528[] = {0x0c0d0b00};
const u32 var7005752c[] = {0x000001b4};
const u32 var70057530[] = {0x0c0e0b00};
const u32 var70057534[] = {0x00000734};
const u32 var70057538[] = {0x0c0f0800};
const u32 var7005753c[] = {0x00000020};
const u32 var70057540[] = {0x0d000b00};
const u32 var70057544[] = {0x000001b2};
const u32 var70057548[] = {0x0d010a00};
const u32 var7005754c[] = {0x000000d2};
const u32 var70057550[] = {0x0d020a00};
const u32 var70057554[] = {0x00000052};
const u32 var70057558[] = {0x0d030a00};
const u32 var7005755c[] = {0x00000192};
const u32 var70057560[] = {0x0d040a00};
const u32 var70057564[] = {0x00000012};
const u32 var70057568[] = {0x0d050a00};
const u32 var7005756c[] = {0x00000162};
const u32 var70057570[] = {0x0d060a00};
const u32 var70057574[] = {0x00000222};
const u32 var70057578[] = {0x0d070a00};
const u32 var7005757c[] = {0x00000142};
const u32 var70057580[] = {0x0d080b00};
const u32 var70057584[] = {0x00000602};
const u32 var70057588[] = {0x0d090b00};
const u32 var7005758c[] = {0x000001f4};
const u32 var70057590[] = {0x0d0a0b00};
const u32 var70057594[] = {0x00000374};
const u32 var70057598[] = {0x0d0b0b00};
const u32 var7005759c[] = {0x00000474};
const u32 var700575a0[] = {0x0d0c0b00};
const u32 var700575a4[] = {0x000005b4};
const u32 var700575a8[] = {0x0d0d0b00};
const u32 var700575ac[] = {0x000004b4};
const u32 var700575b0[] = {0x0d0e0b00};
const u32 var700575b4[] = {0x00000534};
const u32 var700575b8[] = {0x0d0f0800};
const u32 var700575bc[] = {0x00000040};
const u32 var700575c0[] = {0x0e000c00};
const u32 var700575c4[] = {0x00000902};
const u32 var700575c8[] = {0x0e010a00};
const u32 var700575cc[] = {0x00000062};
const u32 var700575d0[] = {0x0e020a00};
const u32 var700575d4[] = {0x000001a2};
const u32 var700575d8[] = {0x0e030a00};
const u32 var700575dc[] = {0x00000122};
const u32 var700575e0[] = {0x0e040a00};
const u32 var700575e4[] = {0x00000342};
const u32 var700575e8[] = {0x0e050a00};
const u32 var700575ec[] = {0x00000042};
const u32 var700575f0[] = {0x0e060a00};
const u32 var700575f4[] = {0x00000302};
const u32 var700575f8[] = {0x0e070b00};
const u32 var700575fc[] = {0x000003f4};
const u32 var70057600[] = {0x0e080b00};
const u32 var70057604[] = {0x000002f4};
const u32 var70057608[] = {0x0e090b00};
const u32 var7005760c[] = {0x00000174};
const u32 var70057610[] = {0x0e0a0b00};
const u32 var70057614[] = {0x000007b4};
const u32 var70057618[] = {0x0e0b0b00};
const u32 var7005761c[] = {0x000006b4};
const u32 var70057620[] = {0x0e0c0b00};
const u32 var70057624[] = {0x000000b4};
const u32 var70057628[] = {0x0e0d0b00};
const u32 var7005762c[] = {0x00000334};
const u32 var70057630[] = {0x0e0e0b00};
const u32 var70057634[] = {0x00000134};
const u32 var70057638[] = {0x0e0f0800};
const u32 var7005763c[] = {0x00000000};
const u32 var70057640[] = {0x0f000800};
const u32 var70057644[] = {0x000000d4};
const u32 var70057648[] = {0x0f010700};
const u32 var7005764c[] = {0x00000014};
const u32 var70057650[] = {0x0f020700};
const u32 var70057654[] = {0x00000064};
const u32 var70057658[] = {0x0f030700};
const u32 var7005765c[] = {0x00000044};
const u32 var70057660[] = {0x0f040700};
const u32 var70057664[] = {0x00000078};
const u32 var70057668[] = {0x0f050700};
const u32 var7005766c[] = {0x00000058};
const u32 var70057670[] = {0x0f060700};
const u32 var70057674[] = {0x00000068};
const u32 var70057678[] = {0x0f070700};
const u32 var7005767c[] = {0x00000048};
const u32 var70057680[] = {0x0f080700};
const u32 var70057684[] = {0x00000070};
const u32 var70057688[] = {0x0f090700};
const u32 var7005768c[] = {0x00000030};
const u32 var70057690[] = {0x0f0a0700};
const u32 var70057694[] = {0x00000010};
const u32 var70057698[] = {0x0f0b0800};
const u32 var7005769c[] = {0x000000e0};
const u32 var700576a0[] = {0x0f0c0800};
const u32 var700576a4[] = {0x000000a0};
const u32 var700576a8[] = {0x0f0d0800};
const u32 var700576ac[] = {0x000000c0};
const u32 var700576b0[] = {0x0f0e0800};
const u32 var700576b4[] = {0x00000080};
const u32 var700576b8[] = {0x0f0f0400};
const u32 var700576bc[] = {0x0000000c};
const u32 var700576c0[] = {0x64646400};
const u32 var700576c4[] = {0x00000000};
const u32 var700576c8[] = {0x00000100};
const u32 var700576cc[] = {0x00000001};
const u32 var700576d0[] = {0x01010400};
const u32 var700576d4[] = {0x0000000a};
const u32 var700576d8[] = {0x02020400};
const u32 var700576dc[] = {0x00000002};
const u32 var700576e0[] = {0x03030500};
const u32 var700576e4[] = {0x00000014};
const u32 var700576e8[] = {0x04040400};
const u32 var700576ec[] = {0x00000006};
const u32 var700576f0[] = {0x05050600};
const u32 var700576f4[] = {0x00000028};
const u32 var700576f8[] = {0x06060500};
const u32 var700576fc[] = {0x00000004};
const u32 var70057700[] = {0x07070600};
const u32 var70057704[] = {0x00000008};
const u32 var70057708[] = {0x08080400};
const u32 var7005770c[] = {0x0000000e};
const u32 var70057710[] = {0x09090500};
const u32 var70057714[] = {0x00000018};
const u32 var70057718[] = {0x0a0a0500};
const u32 var7005771c[] = {0x0000000c};
const u32 var70057720[] = {0x0b0b0600};
const u32 var70057724[] = {0x00000000};
const u32 var70057728[] = {0x0c0c0500};
const u32 var7005772c[] = {0x0000001c};
const u32 var70057730[] = {0x0d0d0600};
const u32 var70057734[] = {0x00000010};
const u32 var70057738[] = {0x0e0e0600};
const u32 var7005773c[] = {0x00000030};
const u32 var70057740[] = {0x0f0f0600};
const u32 var70057744[] = {0x00000020};
const u32 var70057748[] = {0x64646400};
const u32 var7005774c[] = {0x00000000};
const u32 var70057750[] = {0x00000400};
const u32 var70057754[] = {0x0000000f};
const u32 var70057758[] = {0x01010400};
const u32 var7005775c[] = {0x00000007};
const u32 var70057760[] = {0x02020400};
const u32 var70057764[] = {0x0000000b};
const u32 var70057768[] = {0x03030400};
const u32 var7005776c[] = {0x00000003};
const u32 var70057770[] = {0x04040400};
const u32 var70057774[] = {0x0000000d};
const u32 var70057778[] = {0x05050400};
const u32 var7005777c[] = {0x00000005};
const u32 var70057780[] = {0x06060400};
const u32 var70057784[] = {0x00000009};
const u32 var70057788[] = {0x07070400};
const u32 var7005778c[] = {0x00000001};
const u32 var70057790[] = {0x08080400};
const u32 var70057794[] = {0x0000000e};
const u32 var70057798[] = {0x09090400};
const u32 var7005779c[] = {0x00000006};
const u32 var700577a0[] = {0x0a0a0400};
const u32 var700577a4[] = {0x0000000a};
const u32 var700577a8[] = {0x0b0b0400};
const u32 var700577ac[] = {0x00000002};
const u32 var700577b0[] = {0x0c0c0400};
const u32 var700577b4[] = {0x0000000c};
const u32 var700577b8[] = {0x0d0d0400};
const u32 var700577bc[] = {0x00000004};
const u32 var700577c0[] = {0x0e0e0400};
const u32 var700577c4[] = {0x00000008};
const u32 var700577c8[] = {0x0f0f0400};
const u32 var700577cc[] = {0x00000000};
const u32 var700577d0[] = {0x64646400};
const u32 var700577d4[] = {0x00000000};

const s32 var700577d8[34] = {
	0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
	0,  0,  0,  0,  0, 0, 1, 2, 3, 4,
	6,  8,  10, 13, 4, 5, 6, 7, 8, 9,
	11, 13, -1, -1,
};

const s16 var70057860[2][3][22] = {
	{
		{ 5, 11, 17, 23, 29, 35, 43, 53, 65, 79, 95, 115, 139, 167, 199, 237, 283, 335, 395, 463, 521, 575 },
		{ 5, 11, 17, 23, 29, 35, 43, 53, 65, 79, 95, 113, 135, 161, 193, 231, 277, 331, 393, 463, 539, 575 },
		{ 5, 11, 17, 23, 29, 35, 43, 53, 65, 79, 95, 115, 139, 167, 199, 237, 283, 335, 395, 463, 521, 575 },
	}, {
		{ 3, 7,  11, 15, 19, 23, 29, 35, 43, 51, 61, 73,  89,  109, 133, 161, 195, 237, 287, 341, 417, 575 },
		{ 3, 7,  11, 15, 19, 23, 29, 35, 41, 49, 59, 71,  87,  105, 127, 155, 189, 229, 275, 329, 383, 575 },
		{ 3, 7,  11, 15, 19, 23, 29, 35, 43, 53, 65, 81,  101, 125, 155, 193, 239, 295, 363, 447, 549, 575 },
	},
};

const u8 var70057968[2][3][13] = {
	{
		{ 3, 7, 11, 17, 23, 31, 41, 55, 73, 99,  131, 173, 191 },
		{ 3, 7, 11, 17, 25, 35, 47, 61, 79, 103, 135, 179, 191 },
		{ 3, 7, 11, 17, 25, 35, 47, 61, 79, 103, 133, 173, 191 },
	}, {
		{ 3, 7, 11, 15, 21, 29, 39, 51, 65, 83,  105, 135, 191 },
		{ 3, 7, 11, 15, 21, 27, 37, 49, 63, 79,  99,  125, 191 },
		{ 3, 7, 11, 15, 21, 29, 41, 57, 77, 103, 137, 179, 191 },
	},
};

const u32 var700579b8[] = {0x00000006};
const u32 var700579bc[] = {0x000c0012};
const u32 var700579c0[] = {0x0018001e};
const u32 var700579c4[] = {0x0024002c};

const u32 var700579c8[] = {0x00360042};
const u32 var700579cc[] = {0x00500060};
const u32 var700579d0[] = {0x0074008c};
const u32 var700579d4[] = {0x00a800c8};
const u32 var700579d8[] = {0x00ee011c};
const u32 var700579dc[] = {0x0150018c};
const u32 var700579e0[] = {0x01d0020a};

const u32 var700579e4[] = {0x02400000};

const u32 var700579e8[] = {0x00040008};

const u32 var700579ec[] = {0x000c0012};
const u32 var700579f0[] = {0x00180020};
const u32 var700579f4[] = {0x002a0038};
const u32 var700579f8[] = {0x004a0064};
const u32 var700579fc[] = {0x008400ae};
const u32 var70057a00[] = {0x00c00000};
const u32 var70057a04[] = {0x0006000c};
const u32 var70057a08[] = {0x00120018};
const u32 var70057a0c[] = {0x001e0024};
const u32 var70057a10[] = {0x002c0036};
const u32 var70057a14[] = {0x00420050};
const u32 var70057a18[] = {0x00600072};
const u32 var70057a1c[] = {0x008800a2};
const u32 var70057a20[] = {0x00c200e8};
const u32 var70057a24[] = {0x0116014a};
const u32 var70057a28[] = {0x018a01d0};
const u32 var70057a2c[] = {0x021c0240};
const u32 var70057a30[] = {0x00000004};
const u32 var70057a34[] = {0x0008000c};
const u32 var70057a38[] = {0x0012001a};
const u32 var70057a3c[] = {0x00240030};
const u32 var70057a40[] = {0x003e0050};
const u32 var70057a44[] = {0x00680088};
const u32 var70057a48[] = {0x00b400c0};
const u32 var70057a4c[] = {0x00000006};
const u32 var70057a50[] = {0x000c0012};
const u32 var70057a54[] = {0x0018001e};
const u32 var70057a58[] = {0x0024002c};
const u32 var70057a5c[] = {0x00360042};
const u32 var70057a60[] = {0x00500060};
const u32 var70057a64[] = {0x0074008c};
const u32 var70057a68[] = {0x00a800c8};
const u32 var70057a6c[] = {0x00ee011c};
const u32 var70057a70[] = {0x0150018c};
const u32 var70057a74[] = {0x01d0020a};
const u32 var70057a78[] = {0x02400000};
const u32 var70057a7c[] = {0x00040008};
const u32 var70057a80[] = {0x000c0012};
const u32 var70057a84[] = {0x001a0024};
const u32 var70057a88[] = {0x0030003e};
const u32 var70057a8c[] = {0x00500068};
const u32 var70057a90[] = {0x008600ae};
const u32 var70057a94[] = {0x00c00000};
const u32 var70057a98[] = {0x00040008};
const u32 var70057a9c[] = {0x000c0010};
const u32 var70057aa0[] = {0x00140018};
const u32 var70057aa4[] = {0x001e0024};
const u32 var70057aa8[] = {0x002c0034};
const u32 var70057aac[] = {0x003e004a};
const u32 var70057ab0[] = {0x005a006e};
const u32 var70057ab4[] = {0x008600a2};
const u32 var70057ab8[] = {0x00c400ee};
const u32 var70057abc[] = {0x01200156};
const u32 var70057ac0[] = {0x01a20240};
const u32 var70057ac4[] = {0x00000004};
const u32 var70057ac8[] = {0x0008000c};
const u32 var70057acc[] = {0x00100016};
const u32 var70057ad0[] = {0x001e0028};
const u32 var70057ad4[] = {0x00340042};
const u32 var70057ad8[] = {0x0054006a};
const u32 var70057adc[] = {0x008800c0};
const u32 var70057ae0[] = {0x00000004};
const u32 var70057ae4[] = {0x0008000c};
const u32 var70057ae8[] = {0x00100014};
const u32 var70057aec[] = {0x0018001e};
const u32 var70057af0[] = {0x0024002a};
const u32 var70057af4[] = {0x0032003c};
const u32 var70057af8[] = {0x00480058};
const u32 var70057afc[] = {0x006a0080};
const u32 var70057b00[] = {0x009c00be};
const u32 var70057b04[] = {0x00e60114};
const u32 var70057b08[] = {0x014a0180};
const u32 var70057b0c[] = {0x02400000};
const u32 var70057b10[] = {0x00040008};
const u32 var70057b14[] = {0x000c0010};
const u32 var70057b18[] = {0x0016001c};
const u32 var70057b1c[] = {0x00260032};
const u32 var70057b20[] = {0x00400050};
const u32 var70057b24[] = {0x0064007e};
const u32 var70057b28[] = {0x00c00000};
const u32 var70057b2c[] = {0x00040008};
const u32 var70057b30[] = {0x000c0010};
const u32 var70057b34[] = {0x00140018};
const u32 var70057b38[] = {0x001e0024};
const u32 var70057b3c[] = {0x002c0036};
const u32 var70057b40[] = {0x00420052};
const u32 var70057b44[] = {0x0066007e};
const u32 var70057b48[] = {0x009c00c2};
const u32 var70057b4c[] = {0x00f00128};
const u32 var70057b50[] = {0x016c01c0};
const u32 var70057b54[] = {0x02260240};
const u32 var70057b58[] = {0x00000004};
const u32 var70057b5c[] = {0x0008000c};
const u32 var70057b60[] = {0x00100016};
const u32 var70057b64[] = {0x001e002a};
const u32 var70057b68[] = {0x003a004e};
const u32 var70057b6c[] = {0x0068008a};
const u32 var70057b70[] = {0x00b400c0};

const u32 var70057b74[] = {0x00060b10};

const u32 var70057b78[] = {0x1500060c};

const u32 var70057b7c[] = {0x00000000};
const u32 var70057b80[] = {0x03010101};
const u32 var70057b84[] = {0x02020203};
const u32 var70057b88[] = {0x03030404};

const u32 var70057b8c[] = {0x00010203};
const u32 var70057b90[] = {0x00010203};
const u32 var70057b94[] = {0x01020301};
const u32 var70057b98[] = {0x02030203};

const s16 var70057b9c[2][3][576] = {
	{
		{
			0,   1,   2,   3,   6,   7,   8,   9,   12,  13,  14,  15,  4,   5,   18,  19,
			10,  11,  24,  25,  16,  17,  30,  31,  20,  21,  22,  23,  26,  27,  28,  29,
			32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
			48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
			64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  90,  91,
			78,  79,  80,  81,  82,  83,  96,  97,  84,  85,  86,  87,  88,  89,  102, 103,
			92,  93,  94,  95,  108, 109, 110, 111, 112, 113, 98,  99,  100, 101, 114, 115,
			116, 117, 118, 119, 104, 105, 106, 107, 120, 121, 122, 123, 124, 125, 126, 127,
			128, 129, 130, 131, 144, 145, 146, 147, 148, 149, 162, 163, 132, 133, 134, 135,
			136, 137, 150, 151, 152, 153, 154, 155, 168, 169, 138, 139, 140, 141, 142, 143,
			156, 157, 158, 159, 160, 161, 174, 175, 164, 165, 166, 167, 180, 181, 182, 183,
			184, 185, 198, 199, 200, 201, 202, 203, 216, 217, 170, 171, 172, 173, 186, 187,
			188, 189, 190, 191, 204, 205, 206, 207, 208, 209, 222, 223, 176, 177, 178, 179,
			192, 193, 194, 195, 196, 197, 210, 211, 212, 213, 214, 215, 228, 229, 218, 219,
			220, 221, 234, 235, 236, 237, 238, 239, 252, 253, 254, 255, 256, 257, 270, 271,
			272, 273, 274, 275, 288, 289, 290, 291, 224, 225, 226, 227, 240, 241, 242, 243,
			244, 245, 258, 259, 260, 261, 262, 263, 276, 277, 278, 279, 280, 281, 294, 295,
			296, 297, 230, 231, 232, 233, 246, 247, 248, 249, 250, 251, 264, 265, 266, 267,
			268, 269, 282, 283, 284, 285, 286, 287, 300, 301, 302, 303, 292, 293, 306, 307,
			308, 309, 310, 311, 324, 325, 326, 327, 328, 329, 342, 343, 344, 345, 346, 347,
			360, 361, 362, 363, 364, 365, 378, 379, 380, 381, 382, 383, 298, 299, 312, 313,
			314, 315, 316, 317, 330, 331, 332, 333, 334, 335, 348, 349, 350, 351, 352, 353,
			366, 367, 368, 369, 370, 371, 384, 385, 386, 387, 388, 389, 304, 305, 318, 319,
			320, 321, 322, 323, 336, 337, 338, 339, 340, 341, 354, 355, 356, 357, 358, 359,
			372, 373, 374, 375, 376, 377, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
			400, 401, 414, 415, 416, 417, 418, 419, 432, 433, 434, 435, 436, 437, 450, 451,
			452, 453, 454, 455, 468, 469, 470, 471, 472, 473, 486, 487, 488, 489, 490, 491,
			504, 505, 506, 507, 508, 509, 402, 403, 404, 405, 406, 407, 420, 421, 422, 423,
			424, 425, 438, 439, 440, 441, 442, 443, 456, 457, 458, 459, 460, 461, 474, 475,
			476, 477, 478, 479, 492, 493, 494, 495, 496, 497, 510, 511, 512, 513, 514, 515,
			408, 409, 410, 411, 412, 413, 426, 427, 428, 429, 430, 431, 444, 445, 446, 447,
			448, 449, 462, 463, 464, 465, 466, 467, 480, 481, 482, 483, 484, 485, 498, 499,
			500, 501, 502, 503, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527,
			540, 541, 542, 543, 544, 545, 558, 559, 560, 561, 562, 563, 528, 529, 530, 531,
			532, 533, 546, 547, 548, 549, 550, 551, 564, 565, 566, 567, 568, 569, 534, 535,
			536, 537, 538, 539, 552, 553, 554, 555, 556, 557, 570, 571, 572, 573, 574, 575,
		}, {
			0,   1,   2,   3,   6,   7,   8,   9,   12,  13,  14,  15,  4,   5,   18,  19,
			10,  11,  24,  25,  16,  17,  30,  31,  20,  21,  22,  23,  26,  27,  28,  29,
			32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
			48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  72,  73,  60,  61,
			62,  63,  64,  65,  78,  79,  66,  67,  68,  69,  70,  71,  84,  85,  74,  75,
			76,  77,  90,  91,  92,  93,  94,  95,  80,  81,  82,  83,  96,  97,  98,  99,
			100, 101, 86,  87,  88,  89,  102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
			112, 113, 126, 127, 128, 129, 130, 131, 114, 115, 116, 117, 118, 119, 132, 133,
			134, 135, 136, 137, 120, 121, 122, 123, 124, 125, 138, 139, 140, 141, 142, 143,
			144, 145, 146, 147, 148, 149, 162, 163, 164, 165, 166, 167, 180, 181, 150, 151,
			152, 153, 154, 155, 168, 169, 170, 171, 172, 173, 186, 187, 156, 157, 158, 159,
			160, 161, 174, 175, 176, 177, 178, 179, 192, 193, 182, 183, 184, 185, 198, 199,
			200, 201, 202, 203, 216, 217, 218, 219, 220, 221, 234, 235, 188, 189, 190, 191,
			204, 205, 206, 207, 208, 209, 222, 223, 224, 225, 226, 227, 240, 241, 194, 195,
			196, 197, 210, 211, 212, 213, 214, 215, 228, 229, 230, 231, 232, 233, 246, 247,
			236, 237, 238, 239, 252, 253, 254, 255, 256, 257, 270, 271, 272, 273, 274, 275,
			288, 289, 290, 291, 292, 293, 306, 307, 242, 243, 244, 245, 258, 259, 260, 261,
			262, 263, 276, 277, 278, 279, 280, 281, 294, 295, 296, 297, 298, 299, 312, 313,
			248, 249, 250, 251, 264, 265, 266, 267, 268, 269, 282, 283, 284, 285, 286, 287,
			300, 301, 302, 303, 304, 305, 318, 319, 308, 309, 310, 311, 324, 325, 326, 327,
			328, 329, 342, 343, 344, 345, 346, 347, 360, 361, 362, 363, 364, 365, 378, 379,
			380, 381, 382, 383, 396, 397, 398, 399, 314, 315, 316, 317, 330, 331, 332, 333,
			334, 335, 348, 349, 350, 351, 352, 353, 366, 367, 368, 369, 370, 371, 384, 385,
			386, 387, 388, 389, 402, 403, 404, 405, 320, 321, 322, 323, 336, 337, 338, 339,
			340, 341, 354, 355, 356, 357, 358, 359, 372, 373, 374, 375, 376, 377, 390, 391,
			392, 393, 394, 395, 408, 409, 410, 411, 400, 401, 414, 415, 416, 417, 418, 419,
			432, 433, 434, 435, 436, 437, 450, 451, 452, 453, 454, 455, 468, 469, 470, 471,
			472, 473, 486, 487, 488, 489, 490, 491, 504, 505, 506, 507, 508, 509, 522, 523,
			524, 525, 526, 527, 406, 407, 420, 421, 422, 423, 424, 425, 438, 439, 440, 441,
			442, 443, 456, 457, 458, 459, 460, 461, 474, 475, 476, 477, 478, 479, 492, 493,
			494, 495, 496, 497, 510, 511, 512, 513, 514, 515, 528, 529, 530, 531, 532, 533,
			412, 413, 426, 427, 428, 429, 430, 431, 444, 445, 446, 447, 448, 449, 462, 463,
			464, 465, 466, 467, 480, 481, 482, 483, 484, 485, 498, 499, 500, 501, 502, 503,
			516, 517, 518, 519, 520, 521, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543,
			544, 545, 558, 559, 560, 561, 562, 563, 546, 547, 548, 549, 550, 551, 564, 565,
			566, 567, 568, 569, 552, 553, 554, 555, 556, 557, 570, 571, 572, 573, 574, 575,
		}, {
			0,   1,   2,   3,   6,   7,   8,   9,   12,  13,  14,  15,  4,   5,   18,  19,
			10,  11,  24,  25,  16,  17,  30,  31,  20,  21,  22,  23,  26,  27,  28,  29,
			32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
			48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  72,  73,  60,  61,
			62,  63,  64,  65,  78,  79,  66,  67,  68,  69,  70,  71,  84,  85,  74,  75,
			76,  77,  90,  91,  92,  93,  94,  95,  80,  81,  82,  83,  96,  97,  98,  99,
			100, 101, 86,  87,  88,  89,  102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
			112, 113, 126, 127, 128, 129, 130, 131, 114, 115, 116, 117, 118, 119, 132, 133,
			134, 135, 136, 137, 120, 121, 122, 123, 124, 125, 138, 139, 140, 141, 142, 143,
			144, 145, 146, 147, 148, 149, 162, 163, 164, 165, 166, 167, 180, 181, 150, 151,
			152, 153, 154, 155, 168, 169, 170, 171, 172, 173, 186, 187, 156, 157, 158, 159,
			160, 161, 174, 175, 176, 177, 178, 179, 192, 193, 182, 183, 184, 185, 198, 199,
			200, 201, 202, 203, 216, 217, 218, 219, 220, 221, 234, 235, 188, 189, 190, 191,
			204, 205, 206, 207, 208, 209, 222, 223, 224, 225, 226, 227, 240, 241, 194, 195,
			196, 197, 210, 211, 212, 213, 214, 215, 228, 229, 230, 231, 232, 233, 246, 247,
			236, 237, 238, 239, 252, 253, 254, 255, 256, 257, 270, 271, 272, 273, 274, 275,
			288, 289, 290, 291, 292, 293, 306, 307, 242, 243, 244, 245, 258, 259, 260, 261,
			262, 263, 276, 277, 278, 279, 280, 281, 294, 295, 296, 297, 298, 299, 312, 313,
			248, 249, 250, 251, 264, 265, 266, 267, 268, 269, 282, 283, 284, 285, 286, 287,
			300, 301, 302, 303, 304, 305, 318, 319, 308, 309, 310, 311, 324, 325, 326, 327,
			328, 329, 342, 343, 344, 345, 346, 347, 360, 361, 362, 363, 364, 365, 378, 379,
			380, 381, 382, 383, 396, 397, 314, 315, 316, 317, 330, 331, 332, 333, 334, 335,
			348, 349, 350, 351, 352, 353, 366, 367, 368, 369, 370, 371, 384, 385, 386, 387,
			388, 389, 402, 403, 320, 321, 322, 323, 336, 337, 338, 339, 340, 341, 354, 355,
			356, 357, 358, 359, 372, 373, 374, 375, 376, 377, 390, 391, 392, 393, 394, 395,
			408, 409, 398, 399, 400, 401, 414, 415, 416, 417, 418, 419, 432, 433, 434, 435,
			436, 437, 450, 451, 452, 453, 454, 455, 468, 469, 470, 471, 472, 473, 486, 487,
			488, 489, 490, 491, 504, 505, 506, 507, 508, 509, 404, 405, 406, 407, 420, 421,
			422, 423, 424, 425, 438, 439, 440, 441, 442, 443, 456, 457, 458, 459, 460, 461,
			474, 475, 476, 477, 478, 479, 492, 493, 494, 495, 496, 497, 510, 511, 512, 513,
			514, 515, 410, 411, 412, 413, 426, 427, 428, 429, 430, 431, 444, 445, 446, 447,
			448, 449, 462, 463, 464, 465, 466, 467, 480, 481, 482, 483, 484, 485, 498, 499,
			500, 501, 502, 503, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527,
			540, 541, 542, 543, 544, 545, 558, 559, 560, 561, 562, 563, 528, 529, 530, 531,
			532, 533, 546, 547, 548, 549, 550, 551, 564, 565, 566, 567, 568, 569, 534, 535,
			536, 537, 538, 539, 552, 553, 554, 555, 556, 557, 570, 571, 572, 573, 574, 575,
		},
	}, {
		{
			0,   1,   2,   3,   6,   7,   8,   9,   12,  13,  14,  15,  4,   5,   18,  19,
			10,  11,  24,  25,  16,  17,  30,  31,  20,  21,  22,  23,  26,  27,  28,  29,
			32,  33,  34,  35,  36,  37,  38,  39,  42,  43,  44,  45,  48,  49,  50,  51,
			40,  41,  54,  55,  56,  57,  46,  47,  60,  61,  62,  63,  52,  53,  66,  67,
			68,  69,  58,  59,  72,  73,  74,  75,  76,  77,  64,  65,  78,  79,  80,  81,
			82,  83,  70,  71,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
			108, 109, 110, 111, 96,  97,  98,  99,  100, 101, 114, 115, 116, 117, 102, 103,
			104, 105, 106, 107, 120, 121, 122, 123, 112, 113, 126, 127, 128, 129, 130, 131,
			144, 145, 146, 147, 118, 119, 132, 133, 134, 135, 136, 137, 150, 151, 152, 153,
			124, 125, 138, 139, 140, 141, 142, 143, 156, 157, 158, 159, 148, 149, 162, 163,
			164, 165, 166, 167, 180, 181, 182, 183, 184, 185, 154, 155, 168, 169, 170, 171,
			172, 173, 186, 187, 188, 189, 190, 191, 160, 161, 174, 175, 176, 177, 178, 179,
			192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 216, 217, 218, 219,
			220, 221, 234, 235, 236, 237, 238, 239, 204, 205, 206, 207, 208, 209, 222, 223,
			224, 225, 226, 227, 240, 241, 242, 243, 244, 245, 210, 211, 212, 213, 214, 215,
			228, 229, 230, 231, 232, 233, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255,
			256, 257, 270, 271, 272, 273, 274, 275, 288, 289, 290, 291, 292, 293, 306, 307,
			308, 309, 258, 259, 260, 261, 262, 263, 276, 277, 278, 279, 280, 281, 294, 295,
			296, 297, 298, 299, 312, 313, 314, 315, 264, 265, 266, 267, 268, 269, 282, 283,
			284, 285, 286, 287, 300, 301, 302, 303, 304, 305, 318, 319, 320, 321, 310, 311,
			324, 325, 326, 327, 328, 329, 342, 343, 344, 345, 346, 347, 360, 361, 362, 363,
			364, 365, 378, 379, 380, 381, 382, 383, 396, 397, 398, 399, 316, 317, 330, 331,
			332, 333, 334, 335, 348, 349, 350, 351, 352, 353, 366, 367, 368, 369, 370, 371,
			384, 385, 386, 387, 388, 389, 402, 403, 404, 405, 322, 323, 336, 337, 338, 339,
			340, 341, 354, 355, 356, 357, 358, 359, 372, 373, 374, 375, 376, 377, 390, 391,
			392, 393, 394, 395, 408, 409, 410, 411, 400, 401, 414, 415, 416, 417, 418, 419,
			432, 433, 434, 435, 436, 437, 450, 451, 452, 453, 454, 455, 468, 469, 470, 471,
			472, 473, 486, 487, 488, 489, 490, 491, 504, 505, 506, 507, 508, 509, 522, 523,
			524, 525, 526, 527, 540, 541, 542, 543, 544, 545, 558, 559, 560, 561, 562, 563,
			406, 407, 420, 421, 422, 423, 424, 425, 438, 439, 440, 441, 442, 443, 456, 457,
			458, 459, 460, 461, 474, 475, 476, 477, 478, 479, 492, 493, 494, 495, 496, 497,
			510, 511, 512, 513, 514, 515, 528, 529, 530, 531, 532, 533, 546, 547, 548, 549,
			550, 551, 564, 565, 566, 567, 568, 569, 412, 413, 426, 427, 428, 429, 430, 431,
			444, 445, 446, 447, 448, 449, 462, 463, 464, 465, 466, 467, 480, 481, 482, 483,
			484, 485, 498, 499, 500, 501, 502, 503, 516, 517, 518, 519, 520, 521, 534, 535,
			536, 537, 538, 539, 552, 553, 554, 555, 556, 557, 570, 571, 572, 573, 574, 575,
		}, {
			0,   1,   2,   3,   6,   7,   8,   9,   12,  13,  14,  15,  4,   5,   18,  19,
			10,  11,  24,  25,  16,  17,  30,  31,  20,  21,  22,  23,  26,  27,  28,  29,
			32,  33,  34,  35,  36,  37,  38,  39,  42,  43,  44,  45,  48,  49,  50,  51,
			40,  41,  54,  55,  56,  57,  46,  47,  60,  61,  62,  63,  52,  53,  66,  67,
			68,  69,  58,  59,  72,  73,  74,  75,  64,  65,  78,  79,  80,  81,  70,  71,
			84,  85,  86,  87,  76,  77,  90,  91,  92,  93,  94,  95,  108, 109, 82,  83,
			96,  97,  98,  99,  100, 101, 114, 115, 88,  89,  102, 103, 104, 105, 106, 107,
			120, 121, 110, 111, 112, 113, 126, 127, 128, 129, 130, 131, 144, 145, 116, 117,
			118, 119, 132, 133, 134, 135, 136, 137, 150, 151, 122, 123, 124, 125, 138, 139,
			140, 141, 142, 143, 156, 157, 146, 147, 148, 149, 162, 163, 164, 165, 166, 167,
			180, 181, 182, 183, 152, 153, 154, 155, 168, 169, 170, 171, 172, 173, 186, 187,
			188, 189, 158, 159, 160, 161, 174, 175, 176, 177, 178, 179, 192, 193, 194, 195,
			184, 185, 198, 199, 200, 201, 202, 203, 216, 217, 218, 219, 220, 221, 234, 235,
			190, 191, 204, 205, 206, 207, 208, 209, 222, 223, 224, 225, 226, 227, 240, 241,
			196, 197, 210, 211, 212, 213, 214, 215, 228, 229, 230, 231, 232, 233, 246, 247,
			236, 237, 238, 239, 252, 253, 254, 255, 256, 257, 270, 271, 272, 273, 274, 275,
			288, 289, 290, 291, 242, 243, 244, 245, 258, 259, 260, 261, 262, 263, 276, 277,
			278, 279, 280, 281, 294, 295, 296, 297, 248, 249, 250, 251, 264, 265, 266, 267,
			268, 269, 282, 283, 284, 285, 286, 287, 300, 301, 302, 303, 292, 293, 306, 307,
			308, 309, 310, 311, 324, 325, 326, 327, 328, 329, 342, 343, 344, 345, 346, 347,
			360, 361, 362, 363, 364, 365, 298, 299, 312, 313, 314, 315, 316, 317, 330, 331,
			332, 333, 334, 335, 348, 349, 350, 351, 352, 353, 366, 367, 368, 369, 370, 371,
			304, 305, 318, 319, 320, 321, 322, 323, 336, 337, 338, 339, 340, 341, 354, 355,
			356, 357, 358, 359, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383,
			396, 397, 398, 399, 400, 401, 414, 415, 416, 417, 418, 419, 432, 433, 434, 435,
			436, 437, 450, 451, 452, 453, 454, 455, 468, 469, 470, 471, 472, 473, 486, 487,
			488, 489, 490, 491, 504, 505, 506, 507, 508, 509, 522, 523, 524, 525, 526, 527,
			540, 541, 542, 543, 544, 545, 558, 559, 560, 561, 562, 563, 384, 385, 386, 387,
			388, 389, 402, 403, 404, 405, 406, 407, 420, 421, 422, 423, 424, 425, 438, 439,
			440, 441, 442, 443, 456, 457, 458, 459, 460, 461, 474, 475, 476, 477, 478, 479,
			492, 493, 494, 495, 496, 497, 510, 511, 512, 513, 514, 515, 528, 529, 530, 531,
			532, 533, 546, 547, 548, 549, 550, 551, 564, 565, 566, 567, 568, 569, 390, 391,
			392, 393, 394, 395, 408, 409, 410, 411, 412, 413, 426, 427, 428, 429, 430, 431,
			444, 445, 446, 447, 448, 449, 462, 463, 464, 465, 466, 467, 480, 481, 482, 483,
			484, 485, 498, 499, 500, 501, 502, 503, 516, 517, 518, 519, 520, 521, 534, 535,
			536, 537, 538, 539, 552, 553, 554, 555, 556, 557, 570, 571, 572, 573, 574, 575,
		}, {
			0,   1,   2,   3,   6,   7,   8,   9,   12,  13,  14,  15,  4,   5,   18,  19,
			10,  11,  24,  25,  16,  17,  30,  31,  20,  21,  22,  23,  26,  27,  28,  29,
			32,  33,  34,  35,  36,  37,  38,  39,  42,  43,  44,  45,  48,  49,  50,  51,
			40,  41,  54,  55,  56,  57,  46,  47,  60,  61,  62,  63,  52,  53,  66,  67,
			68,  69,  58,  59,  72,  73,  74,  75,  76,  77,  64,  65,  78,  79,  80,  81,
			82,  83,  70,  71,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
			108, 109, 110, 111, 112, 113, 96,  97,  98,  99,  100, 101, 114, 115, 116, 117,
			118, 119, 102, 103, 104, 105, 106, 107, 120, 121, 122, 123, 124, 125, 126, 127,
			128, 129, 130, 131, 144, 145, 146, 147, 148, 149, 162, 163, 164, 165, 132, 133,
			134, 135, 136, 137, 150, 151, 152, 153, 154, 155, 168, 169, 170, 171, 138, 139,
			140, 141, 142, 143, 156, 157, 158, 159, 160, 161, 174, 175, 176, 177, 166, 167,
			180, 181, 182, 183, 184, 185, 198, 199, 200, 201, 202, 203, 216, 217, 218, 219,
			220, 221, 172, 173, 186, 187, 188, 189, 190, 191, 204, 205, 206, 207, 208, 209,
			222, 223, 224, 225, 226, 227, 178, 179, 192, 193, 194, 195, 196, 197, 210, 211,
			212, 213, 214, 215, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
			252, 253, 254, 255, 256, 257, 270, 271, 272, 273, 274, 275, 288, 289, 290, 291,
			292, 293, 306, 307, 240, 241, 242, 243, 244, 245, 258, 259, 260, 261, 262, 263,
			276, 277, 278, 279, 280, 281, 294, 295, 296, 297, 298, 299, 312, 313, 246, 247,
			248, 249, 250, 251, 264, 265, 266, 267, 268, 269, 282, 283, 284, 285, 286, 287,
			300, 301, 302, 303, 304, 305, 318, 319, 308, 309, 310, 311, 324, 325, 326, 327,
			328, 329, 342, 343, 344, 345, 346, 347, 360, 361, 362, 363, 364, 365, 378, 379,
			380, 381, 382, 383, 396, 397, 398, 399, 400, 401, 314, 315, 316, 317, 330, 331,
			332, 333, 334, 335, 348, 349, 350, 351, 352, 353, 366, 367, 368, 369, 370, 371,
			384, 385, 386, 387, 388, 389, 402, 403, 404, 405, 406, 407, 320, 321, 322, 323,
			336, 337, 338, 339, 340, 341, 354, 355, 356, 357, 358, 359, 372, 373, 374, 375,
			376, 377, 390, 391, 392, 393, 394, 395, 408, 409, 410, 411, 412, 413, 414, 415,
			416, 417, 418, 419, 432, 433, 434, 435, 436, 437, 450, 451, 452, 453, 454, 455,
			468, 469, 470, 471, 472, 473, 486, 487, 488, 489, 490, 491, 504, 505, 506, 507,
			508, 509, 522, 523, 524, 525, 526, 527, 420, 421, 422, 423, 424, 425, 438, 439,
			440, 441, 442, 443, 456, 457, 458, 459, 460, 461, 474, 475, 476, 477, 478, 479,
			492, 493, 494, 495, 496, 497, 510, 511, 512, 513, 514, 515, 528, 529, 530, 531,
			532, 533, 426, 427, 428, 429, 430, 431, 444, 445, 446, 447, 448, 449, 462, 463,
			464, 465, 466, 467, 480, 481, 482, 483, 484, 485, 498, 499, 500, 501, 502, 503,
			516, 517, 518, 519, 520, 521, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543,
			544, 545, 558, 559, 560, 561, 562, 563, 546, 547, 548, 549, 550, 551, 564, 565,
			566, 567, 568, 569, 552, 553, 554, 555, 556, 557, 570, 571, 572, 573, 574, 575,
		},
	},
};

const f32 var7005969c[] = {
	-0.51449573040009,
	-0.47173196077347,
	-0.31337743997574,
	-0.18191319704056,
	-0.094574190676212,
	-0.040965583175421,
	-0.01419856864959,
	-0.0036999746225774,
};

const f32 var700596bc[] = {
	0.85749292373657,
	0.88174200057983,
	0.94962865114212,
	0.9833145737648,
	0.99551779031754,
	0.99916058778763,
	0.99989920854568,
	0.99999314546585,
};

const u32 var700596dc[] = {0x00000000};
const u32 var700596e0[] = {0x00001f40};
const u32 var700596e4[] = {0x00003e80};
const u32 var700596e8[] = {0x00005dc0};
const u32 var700596ec[] = {0x00007d00};
const u32 var700596f0[] = {0x00009c40};
const u32 var700596f4[] = {0x0000bb80};
const u32 var700596f8[] = {0x0000dac0};
const u32 var700596fc[] = {0x0000fa00};
const u32 var70059700[] = {0x00013880};
const u32 var70059704[] = {0x00017700};
const u32 var70059708[] = {0x0001b580};
const u32 var7005970c[] = {0x0001f400};
const u32 var70059710[] = {0x00023280};
const u32 var70059714[] = {0x00027100};
const u32 var70059718[] = {0x00000000};
const u32 var7005971c[] = {0x00007d00};
const u32 var70059720[] = {0x00009c40};
const u32 var70059724[] = {0x0000bb80};
const u32 var70059728[] = {0x0000dac0};
const u32 var7005972c[] = {0x0000fa00};
const u32 var70059730[] = {0x00013880};
const u32 var70059734[] = {0x00017700};
const u32 var70059738[] = {0x0001b580};
const u32 var7005973c[] = {0x0001f400};
const u32 var70059740[] = {0x00027100};
const u32 var70059744[] = {0x0002ee00};
const u32 var70059748[] = {0x00036b00};
const u32 var7005974c[] = {0x0003e800};
const u32 var70059750[] = {0x0004e200};

const u32 var70059754[] = {0x00005622};
const u32 var70059758[] = {0x00005dc0};
const u32 var7005975c[] = {0x00003e80};
const u32 var70059760[] = {0x00005622};
const u32 var70059764[] = {0x0000ac44};
const u32 var70059768[] = {0x0000bb80};
const u32 var7005976c[] = {0x00007d00};
const u32 var70059770[] = {0x0000ac44};
const u32 var70059774[] = {0xbd03ba34};
const u32 var70059778[] = {0x3dd41398};
const u32 var7005977c[] = {0xbe3aec8d};
const u32 var70059780[] = {0x3e8890b4};
const u32 var70059784[] = {0xbeb50508};
const u32 var70059788[] = {0x3ee17918};
const u32 var7005978c[] = {0xbf0649c3};
const u32 var70059790[] = {0x3f1a8273};
const u32 var70059794[] = {0xbf2cc954};
const u32 var70059798[] = {0x3f3c902e};
const u32 var7005979c[] = {0xbf495c64};
const u32 var700597a0[] = {0x3f52ca58};
const u32 var700597a4[] = {0xbf5890a3};
const u32 var700597a8[] = {0x3f5a8284};
const u32 var700597ac[] = {0xbf5890a3};
const u32 var700597b0[] = {0x3f52ca47};
const u32 var700597b4[] = {0xbf495c64};
const u32 var700597b8[] = {0x3f3c902e};
const u32 var700597bc[] = {0xbf2cc954};
const u32 var700597c0[] = {0x3f1a8273};
const u32 var700597c4[] = {0xbf0649d4};
const u32 var700597c8[] = {0x3ee1793a};
const u32 var700597cc[] = {0xbeb504e6};
const u32 var700597d0[] = {0x3e8890b4};
const u32 var700597d4[] = {0xbe3aecd0};
const u32 var700597d8[] = {0x3dd41398};
const u32 var700597dc[] = {0xbd03ba34};
const u32 var700597e0[] = {0xbcf168f9};
const u32 var700597e4[] = {0x3da2bb66};
const u32 var700597e8[] = {0xbdee2b06};
const u32 var700597ec[] = {0x3e0e2ef5};
const u32 var700597f0[] = {0xbe15f5f1};
const u32 var700597f4[] = {0x3e0e2ef5};
const u32 var700597f8[] = {0xbdee2b06};
const u32 var700597fc[] = {0x3da2bb66};
const u32 var70059800[] = {0xbcf168f9};
const u32 var70059804[] = {0xbd03ba34};
const u32 var70059808[] = {0x3dd41398};
const u32 var7005980c[] = {0xbe3aec8d};
const u32 var70059810[] = {0x3e8890b4};
const u32 var70059814[] = {0xbeb50508};
const u32 var70059818[] = {0x3ee17918};
const u32 var7005981c[] = {0xbf0649c3};
const u32 var70059820[] = {0x3f1a8273};
const u32 var70059824[] = {0xbf2cc954};
const u32 var70059828[] = {0x3f3c902e};
const u32 var7005982c[] = {0xbf495c64};
const u32 var70059830[] = {0x3f52ca58};
const u32 var70059834[] = {0xbf5890a3};
const u32 var70059838[] = {0x3f5a8284};
const u32 var7005983c[] = {0xbf5890a3};
const u32 var70059840[] = {0x3f52ca47};
const u32 var70059844[] = {0xbf495c64};
const u32 var70059848[] = {0x3f3c902e};
const u32 var7005984c[] = {0xbf2cf377};
const u32 var70059850[] = {0x3f1bd7c3};
const u32 var70059854[] = {0xbf098c7e};
const u32 var70059858[] = {0x3eec6a5d};
const u32 var7005985c[] = {0xbec3ef07};
const u32 var70059860[] = {0x3e99f623};
const u32 var70059864[] = {0xbe5bbcf5};
const u32 var70059868[] = {0x3df6f7e4};
const u32 var7005986c[] = {0xbd0dbf05};
const u32 var70059870[] = {0xbcd987c6};
const u32 var70059874[] = {0x3d4c985f};
const u32 var70059878[] = {0xbce76ea4};
const u32 var7005987c[] = {0x00000000};
const u32 var70059880[] = {0x00000000};
const u32 var70059884[] = {0x00000000};
const u32 var70059888[] = {0x00000000};
const u32 var7005988c[] = {0x00000000};
const u32 var70059890[] = {0x00000000};
const u32 var70059894[] = {0xbdd41398};
const u32 var70059898[] = {0x3eb50508};
const u32 var7005989c[] = {0xbf1a8273};
const u32 var700598a0[] = {0x3f495c64};
const u32 var700598a4[] = {0xbf5a8284};
const u32 var700598a8[] = {0x3f495c64};
const u32 var700598ac[] = {0xbf1a8273};
const u32 var700598b0[] = {0x3eb504e6};
const u32 var700598b4[] = {0xbdd41398};
const u32 var700598b8[] = {0xbda2bb66};
const u32 var700598bc[] = {0x3e15f5f1};
const u32 var700598c0[] = {0xbda2bb66};
const u32 var700598c4[] = {0x00000000};
const u32 var700598c8[] = {0x00000000};
const u32 var700598cc[] = {0x00000000};
const u32 var700598d0[] = {0x00000000};
const u32 var700598d4[] = {0x00000000};
const u32 var700598d8[] = {0x00000000};
const u32 var700598dc[] = {0x00000000};
const u32 var700598e0[] = {0x00000000};
const u32 var700598e4[] = {0x00000000};
const u32 var700598e8[] = {0x00000000};
const u32 var700598ec[] = {0x00000000};
const u32 var700598f0[] = {0x00000000};
const u32 var700598f4[] = {0x00000000};
const u32 var700598f8[] = {0x00000000};
const u32 var700598fc[] = {0x00000000};
const u32 var70059900[] = {0x00000000};
const u32 var70059904[] = {0x00000000};
const u32 var70059908[] = {0x00000000};
const u32 var7005990c[] = {0x00000000};
const u32 var70059910[] = {0x00000000};
const u32 var70059914[] = {0x00000000};
const u32 var70059918[] = {0x00000000};
const u32 var7005991c[] = {0x00000000};
const u32 var70059920[] = {0x00000000};
const u32 var70059924[] = {0x00000000};
const u32 var70059928[] = {0x00000000};
const u32 var7005992c[] = {0x00000000};
const u32 var70059930[] = {0x00000000};
const u32 var70059934[] = {0x00000000};
const u32 var70059938[] = {0x00000000};
const u32 var7005993c[] = {0xbe027d89};
const u32 var70059940[] = {0x3ec24207};
const u32 var70059944[] = {0xbf1bb1d1};
const u32 var70059948[] = {0x3f4ae7b4};
const u32 var7005994c[] = {0xbf6a7d67};
const u32 var70059950[] = {0x3f77cb2e};
const u32 var70059954[] = {0xbf7426cc};
const u32 var70059958[] = {0x3f6c8366};
const u32 var7005995c[] = {0xbf631327};
const u32 var70059960[] = {0x3f57e879};
const u32 var70059964[] = {0xbf4b192f};
const u32 var70059968[] = {0x3f3cbe2f};
const u32 var7005996c[] = {0xbf2cc954};
const u32 var70059970[] = {0x3f1a8273};
const u32 var70059974[] = {0xbf0649d4};
const u32 var70059978[] = {0x3ee1793a};
const u32 var7005997c[] = {0xbeb504e6};
const u32 var70059980[] = {0x3e8890b4};
const u32 var70059984[] = {0xbe3aecd0};
const u32 var70059988[] = {0x3dd41398};
const u32 var7005998c[] = {0xbd03ba34};
const u32 var70059990[] = {0xbcf168f9};
const u32 var70059994[] = {0x3da2bb66};
const u32 var70059998[] = {0xbdee2b06};
const u32 var7005999c[] = {0x3e0e2ef5};
const u32 var700599a0[] = {0xbe15f5f1};
const u32 var700599a4[] = {0x3e0e2ef5};
const u32 var700599a8[] = {0xbdee2b06};
const u32 var700599ac[] = {0x3da2bb66};
const u32 var700599b0[] = {0xbcf168f9};
const u32 var700599b4[] = {0xbe327e95};
const u32 var700599b8[] = {0xbf0483ed};
const u32 var700599bc[] = {0xbf586174};
const u32 var700599c0[] = {0xbf92d5e9};
const u32 var700599c4[] = {0xbfb504f7};
const u32 var700599c8[] = {0xbfd1b3f2};
const u32 var700599cc[] = {0xbfe803cd};
const u32 var700599d0[] = {0xbff746ed};
const u32 var700599d4[] = {0xbfff069a};
const u32 var700599d8[] = {0x3e327e95};
const u32 var700599dc[] = {0x3f0483ed};
const u32 var700599e0[] = {0x3f586174};
const u32 var700599e4[] = {0x3f92d5e9};
const u32 var700599e8[] = {0x3fb504f7};
const u32 var700599ec[] = {0x3fd1b3f2};
const u32 var700599f0[] = {0x3fe803cd};
const u32 var700599f4[] = {0x3ff746ed};
const u32 var700599f8[] = {0x3fff069a};
const u32 var700599fc[] = {0xbe327e95};
const u32 var70059a00[] = {0xbf0483ed};
const u32 var70059a04[] = {0xbf586174};
const u32 var70059a08[] = {0xbf92d5e9};
const u32 var70059a0c[] = {0xbfb504f7};
const u32 var70059a10[] = {0xbfd1b3f2};
const u32 var70059a14[] = {0xbfe803cd};
const u32 var70059a18[] = {0xbff746ed};
const u32 var70059a1c[] = {0xbfff069a};
const u32 var70059a20[] = {0x3e327e95};
const u32 var70059a24[] = {0x3f0483ed};
const u32 var70059a28[] = {0x3f586174};
const u32 var70059a2c[] = {0x3f92d5e9};
const u32 var70059a30[] = {0x3fb504f7};
const u32 var70059a34[] = {0x3fd1b3f2};
const u32 var70059a38[] = {0x3fe803cd};
const u32 var70059a3c[] = {0x3ff746ed};
const u32 var70059a40[] = {0x3fff069a};
const u32 var70059a44[] = {0xbf0483ed};
const u32 var70059a48[] = {0xbfb504d5};
const u32 var70059a4c[] = {0xbff746dc};
const u32 var70059a50[] = {0x3f0483ed};
const u32 var70059a54[] = {0x3fb504d5};
const u32 var70059a58[] = {0x3ff746dc};
const u32 var70059a5c[] = {0x00000000};
const u32 var70059a60[] = {0x00000000};
const u32 var70059a64[] = {0x00000000};
const u32 var70059a68[] = {0x00000000};
const u32 var70059a6c[] = {0x00000000};
const u32 var70059a70[] = {0x00000000};
const u32 var70059a74[] = {0x00000000};
const u32 var70059a78[] = {0x00000000};
const u32 var70059a7c[] = {0x00000000};
const u32 var70059a80[] = {0x00000000};
const u32 var70059a84[] = {0x00000000};
const u32 var70059a88[] = {0x00000000};
const u32 var70059a8c[] = {0xbe327e95};
const u32 var70059a90[] = {0xbf0483ed};
const u32 var70059a94[] = {0xbf586174};
const u32 var70059a98[] = {0xbf92d5e9};
const u32 var70059a9c[] = {0xbfb504f7};
const u32 var70059aa0[] = {0xbfd1b3f2};
const u32 var70059aa4[] = {0xbfe803cd};
const u32 var70059aa8[] = {0xbff746ed};
const u32 var70059aac[] = {0xbfff069a};
const u32 var70059ab0[] = {0x3e327e95};
const u32 var70059ab4[] = {0x3f0483ed};
const u32 var70059ab8[] = {0x3f586174};
const u32 var70059abc[] = {0x3f92d5e9};
const u32 var70059ac0[] = {0x3fb504f7};
const u32 var70059ac4[] = {0x3fd1b3f2};
const u32 var70059ac8[] = {0x3fe803cd};
const u32 var70059acc[] = {0x3ff746ed};
const u32 var70059ad0[] = {0x3fff069a};

const u32 var70059ad4[] = {0x80402010};
const u32 var70059ad8[] = {0x08040201};

GLOBAL_ASM(
glabel func0003f8a0
.late_rodata
glabel var70059c54
.word 0x3db2b8c2
glabel var70059c58
.word 0x3db2b8c2
glabel var70059c5c
.word 0x3e860a92
glabel var70059c60
.word 0x3e860a92
glabel var70059c64
.word 0x3db2b8c2
glabel var70059c68
.word 0x3faaaaab
.text
/*    3f8a0:	27bdfd90 */ 	addiu	$sp,$sp,-624
/*    3f8a4:	afbf001c */ 	sw	$ra,0x1c($sp)
/*    3f8a8:	afb00018 */ 	sw	$s0,0x18($sp)
/*    3f8ac:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    3f8b0:	afae0260 */ 	sw	$t6,0x260($sp)
/*    3f8b4:	3c187006 */ 	lui	$t8,%hi(var70059ad4)
/*    3f8b8:	27189ad4 */ 	addiu	$t8,$t8,%lo(var70059ad4)
/*    3f8bc:	8f080000 */ 	lw	$t0,0x0($t8)
/*    3f8c0:	8f190004 */ 	lw	$t9,0x4($t8)
/*    3f8c4:	27af0248 */ 	addiu	$t7,$sp,0x248
/*    3f8c8:	ade80000 */ 	sw	$t0,0x0($t7)
/*    3f8cc:	adf90004 */ 	sw	$t9,0x4($t7)
/*    3f8d0:	afa00234 */ 	sw	$zero,0x234($sp)
/*    3f8d4:	afa0026c */ 	sw	$zero,0x26c($sp)
.L0003f8d8:
/*    3f8d8:	8fa9026c */ 	lw	$t1,0x26c($sp)
/*    3f8dc:	3c013f00 */ 	lui	$at,0x3f00
/*    3f8e0:	44814000 */ 	mtc1	$at,$f8
/*    3f8e4:	44892000 */ 	mtc1	$t1,$f4
/*    3f8e8:	3c017006 */ 	lui	$at,%hi(var70059c54)
/*    3f8ec:	c4309c54 */ 	lwc1	$f16,%lo(var70059c54)($at)
/*    3f8f0:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    3f8f4:	46083280 */ 	add.s	$f10,$f6,$f8
/*    3f8f8:	46105302 */ 	mul.s	$f12,$f10,$f16
/*    3f8fc:	0c0068f7 */ 	jal	sinf
/*    3f900:	00000000 */ 	nop
/*    3f904:	8faa026c */ 	lw	$t2,0x26c($sp)
/*    3f908:	3c01800a */ 	lui	$at,%hi(var8009c400)
/*    3f90c:	000a5880 */ 	sll	$t3,$t2,0x2
/*    3f910:	002b0821 */ 	addu	$at,$at,$t3
/*    3f914:	e420c400 */ 	swc1	$f0,%lo(var8009c400)($at)
/*    3f918:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    3f91c:	258d0001 */ 	addiu	$t5,$t4,0x1
/*    3f920:	29a10024 */ 	slti	$at,$t5,0x24
/*    3f924:	1420ffec */ 	bnez	$at,.L0003f8d8
/*    3f928:	afad026c */ 	sw	$t5,0x26c($sp)
/*    3f92c:	afa0026c */ 	sw	$zero,0x26c($sp)
.L0003f930:
/*    3f930:	8fae026c */ 	lw	$t6,0x26c($sp)
/*    3f934:	3c013f00 */ 	lui	$at,0x3f00
/*    3f938:	44813000 */ 	mtc1	$at,$f6
/*    3f93c:	448e9000 */ 	mtc1	$t6,$f18
/*    3f940:	3c017006 */ 	lui	$at,%hi(var70059c58)
/*    3f944:	c42a9c58 */ 	lwc1	$f10,%lo(var70059c58)($at)
/*    3f948:	46809120 */ 	cvt.s.w	$f4,$f18
/*    3f94c:	46062200 */ 	add.s	$f8,$f4,$f6
/*    3f950:	460a4302 */ 	mul.s	$f12,$f8,$f10
/*    3f954:	0c0068f7 */ 	jal	sinf
/*    3f958:	00000000 */ 	nop
/*    3f95c:	8faf026c */ 	lw	$t7,0x26c($sp)
/*    3f960:	3c01800a */ 	lui	$at,%hi(var8009c490)
/*    3f964:	000fc080 */ 	sll	$t8,$t7,0x2
/*    3f968:	00380821 */ 	addu	$at,$at,$t8
/*    3f96c:	e420c490 */ 	swc1	$f0,%lo(var8009c490)($at)
/*    3f970:	8fb9026c */ 	lw	$t9,0x26c($sp)
/*    3f974:	27280001 */ 	addiu	$t0,$t9,0x1
/*    3f978:	29010012 */ 	slti	$at,$t0,0x12
/*    3f97c:	1420ffec */ 	bnez	$at,.L0003f930
/*    3f980:	afa8026c */ 	sw	$t0,0x26c($sp)
/*    3f984:	24090012 */ 	addiu	$t1,$zero,0x12
/*    3f988:	afa9026c */ 	sw	$t1,0x26c($sp)
.L0003f98c:
/*    3f98c:	8faa026c */ 	lw	$t2,0x26c($sp)
/*    3f990:	3c013f80 */ 	lui	$at,0x3f80
/*    3f994:	44818000 */ 	mtc1	$at,$f16
/*    3f998:	3c01800a */ 	lui	$at,%hi(var8009c490)
/*    3f99c:	000a5880 */ 	sll	$t3,$t2,0x2
/*    3f9a0:	002b0821 */ 	addu	$at,$at,$t3
/*    3f9a4:	e430c490 */ 	swc1	$f16,%lo(var8009c490)($at)
/*    3f9a8:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    3f9ac:	258d0001 */ 	addiu	$t5,$t4,0x1
/*    3f9b0:	29a10018 */ 	slti	$at,$t5,0x18
/*    3f9b4:	1420fff5 */ 	bnez	$at,.L0003f98c
/*    3f9b8:	afad026c */ 	sw	$t5,0x26c($sp)
/*    3f9bc:	240e0018 */ 	addiu	$t6,$zero,0x18
/*    3f9c0:	afae026c */ 	sw	$t6,0x26c($sp)
.L0003f9c4:
/*    3f9c4:	8faf026c */ 	lw	$t7,0x26c($sp)
/*    3f9c8:	3c013f00 */ 	lui	$at,0x3f00
/*    3f9cc:	44813000 */ 	mtc1	$at,$f6
/*    3f9d0:	448f9000 */ 	mtc1	$t7,$f18
/*    3f9d4:	3c014190 */ 	lui	$at,0x4190
/*    3f9d8:	44815000 */ 	mtc1	$at,$f10
/*    3f9dc:	46809120 */ 	cvt.s.w	$f4,$f18
/*    3f9e0:	3c017006 */ 	lui	$at,%hi(var70059c5c)
/*    3f9e4:	c4329c5c */ 	lwc1	$f18,%lo(var70059c5c)($at)
/*    3f9e8:	46062200 */ 	add.s	$f8,$f4,$f6
/*    3f9ec:	460a4401 */ 	sub.s	$f16,$f8,$f10
/*    3f9f0:	46128302 */ 	mul.s	$f12,$f16,$f18
/*    3f9f4:	0c0068f7 */ 	jal	sinf
/*    3f9f8:	00000000 */ 	nop
/*    3f9fc:	8fb8026c */ 	lw	$t8,0x26c($sp)
/*    3fa00:	3c01800a */ 	lui	$at,%hi(var8009c490)
/*    3fa04:	0018c880 */ 	sll	$t9,$t8,0x2
/*    3fa08:	00390821 */ 	addu	$at,$at,$t9
/*    3fa0c:	e420c490 */ 	swc1	$f0,%lo(var8009c490)($at)
/*    3fa10:	8fa8026c */ 	lw	$t0,0x26c($sp)
/*    3fa14:	25090001 */ 	addiu	$t1,$t0,0x1
/*    3fa18:	2921001e */ 	slti	$at,$t1,0x1e
/*    3fa1c:	1420ffe9 */ 	bnez	$at,.L0003f9c4
/*    3fa20:	afa9026c */ 	sw	$t1,0x26c($sp)
/*    3fa24:	240a001e */ 	addiu	$t2,$zero,0x1e
/*    3fa28:	afaa026c */ 	sw	$t2,0x26c($sp)
.L0003fa2c:
/*    3fa2c:	8fab026c */ 	lw	$t3,0x26c($sp)
/*    3fa30:	44802000 */ 	mtc1	$zero,$f4
/*    3fa34:	3c01800a */ 	lui	$at,%hi(var8009c490)
/*    3fa38:	000b6080 */ 	sll	$t4,$t3,0x2
/*    3fa3c:	002c0821 */ 	addu	$at,$at,$t4
/*    3fa40:	e424c490 */ 	swc1	$f4,%lo(var8009c490)($at)
/*    3fa44:	8fad026c */ 	lw	$t5,0x26c($sp)
/*    3fa48:	25ae0001 */ 	addiu	$t6,$t5,0x1
/*    3fa4c:	29c10024 */ 	slti	$at,$t6,0x24
/*    3fa50:	1420fff6 */ 	bnez	$at,.L0003fa2c
/*    3fa54:	afae026c */ 	sw	$t6,0x26c($sp)
/*    3fa58:	afa0026c */ 	sw	$zero,0x26c($sp)
.L0003fa5c:
/*    3fa5c:	8faf026c */ 	lw	$t7,0x26c($sp)
/*    3fa60:	44803000 */ 	mtc1	$zero,$f6
/*    3fa64:	3c01800a */ 	lui	$at,%hi(var8009c5b0)
/*    3fa68:	000fc080 */ 	sll	$t8,$t7,0x2
/*    3fa6c:	00380821 */ 	addu	$at,$at,$t8
/*    3fa70:	e426c5b0 */ 	swc1	$f6,%lo(var8009c5b0)($at)
/*    3fa74:	8fb9026c */ 	lw	$t9,0x26c($sp)
/*    3fa78:	27280001 */ 	addiu	$t0,$t9,0x1
/*    3fa7c:	29010006 */ 	slti	$at,$t0,0x6
/*    3fa80:	1420fff6 */ 	bnez	$at,.L0003fa5c
/*    3fa84:	afa8026c */ 	sw	$t0,0x26c($sp)
/*    3fa88:	24090006 */ 	addiu	$t1,$zero,0x6
/*    3fa8c:	afa9026c */ 	sw	$t1,0x26c($sp)
.L0003fa90:
/*    3fa90:	8faa026c */ 	lw	$t2,0x26c($sp)
/*    3fa94:	3c013f00 */ 	lui	$at,0x3f00
/*    3fa98:	44818000 */ 	mtc1	$at,$f16
/*    3fa9c:	448a4000 */ 	mtc1	$t2,$f8
/*    3faa0:	3c0140c0 */ 	lui	$at,0x40c0
/*    3faa4:	44812000 */ 	mtc1	$at,$f4
/*    3faa8:	468042a0 */ 	cvt.s.w	$f10,$f8
/*    3faac:	3c017006 */ 	lui	$at,%hi(var70059c60)
/*    3fab0:	c4289c60 */ 	lwc1	$f8,%lo(var70059c60)($at)
/*    3fab4:	46105480 */ 	add.s	$f18,$f10,$f16
/*    3fab8:	46049181 */ 	sub.s	$f6,$f18,$f4
/*    3fabc:	46083302 */ 	mul.s	$f12,$f6,$f8
/*    3fac0:	0c0068f7 */ 	jal	sinf
/*    3fac4:	00000000 */ 	nop
/*    3fac8:	8fab026c */ 	lw	$t3,0x26c($sp)
/*    3facc:	3c01800a */ 	lui	$at,%hi(var8009c5b0)
/*    3fad0:	000b6080 */ 	sll	$t4,$t3,0x2
/*    3fad4:	002c0821 */ 	addu	$at,$at,$t4
/*    3fad8:	e420c5b0 */ 	swc1	$f0,%lo(var8009c5b0)($at)
/*    3fadc:	8fad026c */ 	lw	$t5,0x26c($sp)
/*    3fae0:	25ae0001 */ 	addiu	$t6,$t5,0x1
/*    3fae4:	29c1000c */ 	slti	$at,$t6,0xc
/*    3fae8:	1420ffe9 */ 	bnez	$at,.L0003fa90
/*    3faec:	afae026c */ 	sw	$t6,0x26c($sp)
/*    3faf0:	240f000c */ 	addiu	$t7,$zero,0xc
/*    3faf4:	afaf026c */ 	sw	$t7,0x26c($sp)
.L0003faf8:
/*    3faf8:	8fb8026c */ 	lw	$t8,0x26c($sp)
/*    3fafc:	3c013f80 */ 	lui	$at,0x3f80
/*    3fb00:	44815000 */ 	mtc1	$at,$f10
/*    3fb04:	3c01800a */ 	lui	$at,%hi(var8009c5b0)
/*    3fb08:	0018c880 */ 	sll	$t9,$t8,0x2
/*    3fb0c:	00390821 */ 	addu	$at,$at,$t9
/*    3fb10:	e42ac5b0 */ 	swc1	$f10,%lo(var8009c5b0)($at)
/*    3fb14:	8fa8026c */ 	lw	$t0,0x26c($sp)
/*    3fb18:	25090001 */ 	addiu	$t1,$t0,0x1
/*    3fb1c:	29210012 */ 	slti	$at,$t1,0x12
/*    3fb20:	1420fff5 */ 	bnez	$at,.L0003faf8
/*    3fb24:	afa9026c */ 	sw	$t1,0x26c($sp)
/*    3fb28:	240a0012 */ 	addiu	$t2,$zero,0x12
/*    3fb2c:	afaa026c */ 	sw	$t2,0x26c($sp)
.L0003fb30:
/*    3fb30:	8fab026c */ 	lw	$t3,0x26c($sp)
/*    3fb34:	3c013f00 */ 	lui	$at,0x3f00
/*    3fb38:	44812000 */ 	mtc1	$at,$f4
/*    3fb3c:	448b8000 */ 	mtc1	$t3,$f16
/*    3fb40:	3c017006 */ 	lui	$at,%hi(var70059c64)
/*    3fb44:	c4289c64 */ 	lwc1	$f8,%lo(var70059c64)($at)
/*    3fb48:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    3fb4c:	46049180 */ 	add.s	$f6,$f18,$f4
/*    3fb50:	46083302 */ 	mul.s	$f12,$f6,$f8
/*    3fb54:	0c0068f7 */ 	jal	sinf
/*    3fb58:	00000000 */ 	nop
/*    3fb5c:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    3fb60:	3c01800a */ 	lui	$at,%hi(var8009c5b0)
/*    3fb64:	000c6880 */ 	sll	$t5,$t4,0x2
/*    3fb68:	002d0821 */ 	addu	$at,$at,$t5
/*    3fb6c:	e420c5b0 */ 	swc1	$f0,%lo(var8009c5b0)($at)
/*    3fb70:	8fae026c */ 	lw	$t6,0x26c($sp)
/*    3fb74:	25cf0001 */ 	addiu	$t7,$t6,0x1
/*    3fb78:	29e10024 */ 	slti	$at,$t7,0x24
/*    3fb7c:	1420ffec */ 	bnez	$at,.L0003fb30
/*    3fb80:	afaf026c */ 	sw	$t7,0x26c($sp)
/*    3fb84:	3c18800a */ 	lui	$t8,%hi(var8009c640)
/*    3fb88:	8f18c640 */ 	lw	$t8,%lo(var8009c640)($t8)
/*    3fb8c:	17000003 */ 	bnez	$t8,.L0003fb9c
/*    3fb90:	00000000 */ 	nop
/*    3fb94:	1000016e */ 	b	.L00040150
/*    3fb98:	00001025 */ 	or	$v0,$zero,$zero
.L0003fb9c:
/*    3fb9c:	3c04800a */ 	lui	$a0,%hi(var8009c640)
/*    3fba0:	8c84c640 */ 	lw	$a0,%lo(var8009c640)($a0)
/*    3fba4:	0c012c30 */ 	jal	bzero
/*    3fba8:	3405a410 */ 	dli	$a1,0xa410
/*    3fbac:	afa00264 */ 	sw	$zero,0x264($sp)
.L0003fbb0:
/*    3fbb0:	8fb90264 */ 	lw	$t9,0x264($sp)
/*    3fbb4:	3c098006 */ 	lui	$t1,%hi(var8005f670)
/*    3fbb8:	00194080 */ 	sll	$t0,$t9,0x2
/*    3fbbc:	01284821 */ 	addu	$t1,$t1,$t0
/*    3fbc0:	8d29f670 */ 	lw	$t1,%lo(var8005f670)($t1)
/*    3fbc4:	afa90254 */ 	sw	$t1,0x254($sp)
/*    3fbc8:	8faa0254 */ 	lw	$t2,0x254($sp)
/*    3fbcc:	15400008 */ 	bnez	$t2,.L0003fbf0
/*    3fbd0:	00000000 */ 	nop
/*    3fbd4:	8fab0264 */ 	lw	$t3,0x264($sp)
/*    3fbd8:	3c01800a */ 	lui	$at,%hi(var8009c650)
/*    3fbdc:	000b6080 */ 	sll	$t4,$t3,0x2
/*    3fbe0:	002c0821 */ 	addu	$at,$at,$t4
/*    3fbe4:	ac20c650 */ 	sw	$zero,%lo(var8009c650)($at)
/*    3fbe8:	1000010e */ 	b	.L00040024
/*    3fbec:	00000000 */ 	nop
.L0003fbf0:
/*    3fbf0:	8fad0234 */ 	lw	$t5,0x234($sp)
/*    3fbf4:	8fb90264 */ 	lw	$t9,0x264($sp)
/*    3fbf8:	3c0f800a */ 	lui	$t7,%hi(var8009c640)
/*    3fbfc:	8defc640 */ 	lw	$t7,%lo(var8009c640)($t7)
/*    3fc00:	3c01800a */ 	lui	$at,%hi(var8009c650)
/*    3fc04:	000d7080 */ 	sll	$t6,$t5,0x2
/*    3fc08:	00194080 */ 	sll	$t0,$t9,0x2
/*    3fc0c:	00280821 */ 	addu	$at,$at,$t0
/*    3fc10:	01cfc021 */ 	addu	$t8,$t6,$t7
/*    3fc14:	ac38c650 */ 	sw	$t8,%lo(var8009c650)($at)
/*    3fc18:	8fa90264 */ 	lw	$t1,0x264($sp)
/*    3fc1c:	3c0b800a */ 	lui	$t3,%hi(var8009c650)
/*    3fc20:	00095080 */ 	sll	$t2,$t1,0x2
/*    3fc24:	016a5821 */ 	addu	$t3,$t3,$t2
/*    3fc28:	8d6bc650 */ 	lw	$t3,%lo(var8009c650)($t3)
/*    3fc2c:	afab0250 */ 	sw	$t3,0x250($sp)
/*    3fc30:	afa00268 */ 	sw	$zero,0x268($sp)
.L0003fc34:
/*    3fc34:	8fae0268 */ 	lw	$t6,0x268($sp)
/*    3fc38:	8fad0250 */ 	lw	$t5,0x250($sp)
/*    3fc3c:	240cffff */ 	addiu	$t4,$zero,-1
/*    3fc40:	000e7880 */ 	sll	$t7,$t6,0x2
/*    3fc44:	01afc821 */ 	addu	$t9,$t5,$t7
/*    3fc48:	a32c0002 */ 	sb	$t4,0x2($t9)
/*    3fc4c:	8fa90268 */ 	lw	$t1,0x268($sp)
/*    3fc50:	8fa80250 */ 	lw	$t0,0x250($sp)
/*    3fc54:	2418ffff */ 	addiu	$t8,$zero,-1
/*    3fc58:	00095080 */ 	sll	$t2,$t1,0x2
/*    3fc5c:	010a5821 */ 	addu	$t3,$t0,$t2
/*    3fc60:	a1780003 */ 	sb	$t8,0x3($t3)
/*    3fc64:	8fae0268 */ 	lw	$t6,0x268($sp)
/*    3fc68:	25cd0001 */ 	addiu	$t5,$t6,0x1
/*    3fc6c:	29a12904 */ 	slti	$at,$t5,0x2904
/*    3fc70:	1420fff0 */ 	bnez	$at,.L0003fc34
/*    3fc74:	afad0268 */ 	sw	$t5,0x268($sp)
/*    3fc78:	240f0001 */ 	addiu	$t7,$zero,0x1
/*    3fc7c:	afaf0230 */ 	sw	$t7,0x230($sp)
/*    3fc80:	240c0001 */ 	addiu	$t4,$zero,0x1
/*    3fc84:	afac0228 */ 	sw	$t4,0x228($sp)
/*    3fc88:	27a40028 */ 	addiu	$a0,$sp,0x28
/*    3fc8c:	0c012c30 */ 	jal	bzero
/*    3fc90:	24050200 */ 	addiu	$a1,$zero,0x200
/*    3fc94:	24190001 */ 	addiu	$t9,$zero,0x1
/*    3fc98:	afb90260 */ 	sw	$t9,0x260($sp)
/*    3fc9c:	8fa90228 */ 	lw	$t1,0x228($sp)
/*    3fca0:	1120006c */ 	beqz	$t1,.L0003fe54
/*    3fca4:	00000000 */ 	nop
.L0003fca8:
/*    3fca8:	afa00228 */ 	sw	$zero,0x228($sp)
/*    3fcac:	8fa80264 */ 	lw	$t0,0x264($sp)
/*    3fcb0:	3c188006 */ 	lui	$t8,%hi(var8005f670)
/*    3fcb4:	afa0022c */ 	sw	$zero,0x22c($sp)
/*    3fcb8:	00085080 */ 	sll	$t2,$t0,0x2
/*    3fcbc:	030ac021 */ 	addu	$t8,$t8,$t2
/*    3fcc0:	8f18f670 */ 	lw	$t8,%lo(var8005f670)($t8)
/*    3fcc4:	24010064 */ 	addiu	$at,$zero,0x64
/*    3fcc8:	afb80254 */ 	sw	$t8,0x254($sp)
/*    3fccc:	930b0000 */ 	lbu	$t3,0x0($t8)
/*    3fcd0:	1161005a */ 	beq	$t3,$at,.L0003fe3c
/*    3fcd4:	00000000 */ 	nop
.L0003fcd8:
/*    3fcd8:	8fae022c */ 	lw	$t6,0x22c($sp)
/*    3fcdc:	000e6840 */ 	sll	$t5,$t6,0x1
/*    3fce0:	03ad7821 */ 	addu	$t7,$sp,$t5
/*    3fce4:	85ef0028 */ 	lh	$t7,0x28($t7)
/*    3fce8:	afaf025c */ 	sw	$t7,0x25c($sp)
/*    3fcec:	8fb90254 */ 	lw	$t9,0x254($sp)
/*    3fcf0:	8fac0230 */ 	lw	$t4,0x230($sp)
/*    3fcf4:	93290002 */ 	lbu	$t1,0x2($t9)
/*    3fcf8:	012c082a */ 	slt	$at,$t1,$t4
/*    3fcfc:	14200045 */ 	bnez	$at,.L0003fe14
/*    3fd00:	00000000 */ 	nop
/*    3fd04:	8fa80254 */ 	lw	$t0,0x254($sp)
/*    3fd08:	8fb80230 */ 	lw	$t8,0x230($sp)
/*    3fd0c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    3fd10:	8d0a0004 */ 	lw	$t2,0x4($t0)
/*    3fd14:	270b001f */ 	addiu	$t3,$t8,0x1f
/*    3fd18:	016e6804 */ 	sllv	$t5,$t6,$t3
/*    3fd1c:	014d7824 */ 	and	$t7,$t2,$t5
/*    3fd20:	11e00003 */ 	beqz	$t7,.L0003fd30
/*    3fd24:	00000000 */ 	nop
/*    3fd28:	10000002 */ 	b	.L0003fd34
/*    3fd2c:	24100001 */ 	addiu	$s0,$zero,0x1
.L0003fd30:
/*    3fd30:	00008025 */ 	or	$s0,$zero,$zero
.L0003fd34:
/*    3fd34:	8fac025c */ 	lw	$t4,0x25c($sp)
/*    3fd38:	8fb90250 */ 	lw	$t9,0x250($sp)
/*    3fd3c:	000c4880 */ 	sll	$t1,$t4,0x2
/*    3fd40:	03294021 */ 	addu	$t0,$t9,$t1
/*    3fd44:	0110c021 */ 	addu	$t8,$t0,$s0
/*    3fd48:	afb80258 */ 	sw	$t8,0x258($sp)
/*    3fd4c:	8fae0258 */ 	lw	$t6,0x258($sp)
/*    3fd50:	91cb0000 */ 	lbu	$t3,0x0($t6)
/*    3fd54:	1160000a */ 	beqz	$t3,.L0003fd80
/*    3fd58:	00000000 */ 	nop
/*    3fd5c:	8faf022c */ 	lw	$t7,0x22c($sp)
/*    3fd60:	8faa0258 */ 	lw	$t2,0x258($sp)
/*    3fd64:	000f6040 */ 	sll	$t4,$t7,0x1
/*    3fd68:	03acc821 */ 	addu	$t9,$sp,$t4
/*    3fd6c:	87390028 */ 	lh	$t9,0x28($t9)
/*    3fd70:	914d0000 */ 	lbu	$t5,0x0($t2)
/*    3fd74:	01b94821 */ 	addu	$t1,$t5,$t9
/*    3fd78:	1000000a */ 	b	.L0003fda4
/*    3fd7c:	afa9025c */ 	sw	$t1,0x25c($sp)
.L0003fd80:
/*    3fd80:	8fa80260 */ 	lw	$t0,0x260($sp)
/*    3fd84:	8fb8025c */ 	lw	$t8,0x25c($sp)
/*    3fd88:	8fab0258 */ 	lw	$t3,0x258($sp)
/*    3fd8c:	01187023 */ 	subu	$t6,$t0,$t8
/*    3fd90:	a16e0000 */ 	sb	$t6,0x0($t3)
/*    3fd94:	8faa0260 */ 	lw	$t2,0x260($sp)
/*    3fd98:	254f0001 */ 	addiu	$t7,$t2,0x1
/*    3fd9c:	afaf0260 */ 	sw	$t7,0x260($sp)
/*    3fda0:	afaa025c */ 	sw	$t2,0x25c($sp)
.L0003fda4:
/*    3fda4:	8fac0254 */ 	lw	$t4,0x254($sp)
/*    3fda8:	8fb90230 */ 	lw	$t9,0x230($sp)
/*    3fdac:	918d0002 */ 	lbu	$t5,0x2($t4)
/*    3fdb0:	15b90010 */ 	bne	$t5,$t9,.L0003fdf4
/*    3fdb4:	00000000 */ 	nop
/*    3fdb8:	8fa90254 */ 	lw	$t1,0x254($sp)
/*    3fdbc:	8fae025c */ 	lw	$t6,0x25c($sp)
/*    3fdc0:	8fb80250 */ 	lw	$t8,0x250($sp)
/*    3fdc4:	91280000 */ 	lbu	$t0,0x0($t1)
/*    3fdc8:	000e5880 */ 	sll	$t3,$t6,0x2
/*    3fdcc:	030b5021 */ 	addu	$t2,$t8,$t3
/*    3fdd0:	a1480002 */ 	sb	$t0,0x2($t2)
/*    3fdd4:	8faf0254 */ 	lw	$t7,0x254($sp)
/*    3fdd8:	8fb9025c */ 	lw	$t9,0x25c($sp)
/*    3fddc:	8fad0250 */ 	lw	$t5,0x250($sp)
/*    3fde0:	91ec0001 */ 	lbu	$t4,0x1($t7)
/*    3fde4:	00194880 */ 	sll	$t1,$t9,0x2
/*    3fde8:	01a97021 */ 	addu	$t6,$t5,$t1
/*    3fdec:	10000004 */ 	b	.L0003fe00
/*    3fdf0:	a1cc0003 */ 	sb	$t4,0x3($t6)
.L0003fdf4:
/*    3fdf4:	8fb80228 */ 	lw	$t8,0x228($sp)
/*    3fdf8:	270b0001 */ 	addiu	$t3,$t8,0x1
/*    3fdfc:	afab0228 */ 	sw	$t3,0x228($sp)
.L0003fe00:
/*    3fe00:	8faa022c */ 	lw	$t2,0x22c($sp)
/*    3fe04:	8fa8025c */ 	lw	$t0,0x25c($sp)
/*    3fe08:	000a7840 */ 	sll	$t7,$t2,0x1
/*    3fe0c:	03afc821 */ 	addu	$t9,$sp,$t7
/*    3fe10:	a7280028 */ 	sh	$t0,0x28($t9)
.L0003fe14:
/*    3fe14:	8fad0254 */ 	lw	$t5,0x254($sp)
/*    3fe18:	8fac022c */ 	lw	$t4,0x22c($sp)
/*    3fe1c:	24010064 */ 	addiu	$at,$zero,0x64
/*    3fe20:	25a90008 */ 	addiu	$t1,$t5,0x8
/*    3fe24:	258e0001 */ 	addiu	$t6,$t4,0x1
/*    3fe28:	afae022c */ 	sw	$t6,0x22c($sp)
/*    3fe2c:	afa90254 */ 	sw	$t1,0x254($sp)
/*    3fe30:	91380000 */ 	lbu	$t8,0x0($t1)
/*    3fe34:	1701ffa8 */ 	bne	$t8,$at,.L0003fcd8
/*    3fe38:	00000000 */ 	nop
.L0003fe3c:
/*    3fe3c:	8fab0230 */ 	lw	$t3,0x230($sp)
/*    3fe40:	256a0001 */ 	addiu	$t2,$t3,0x1
/*    3fe44:	afaa0230 */ 	sw	$t2,0x230($sp)
/*    3fe48:	8fa80228 */ 	lw	$t0,0x228($sp)
/*    3fe4c:	1500ff96 */ 	bnez	$t0,.L0003fca8
/*    3fe50:	00000000 */ 	nop
.L0003fe54:
/*    3fe54:	8faf0234 */ 	lw	$t7,0x234($sp)
/*    3fe58:	8fb90260 */ 	lw	$t9,0x260($sp)
/*    3fe5c:	01f96821 */ 	addu	$t5,$t7,$t9
/*    3fe60:	afad0234 */ 	sw	$t5,0x234($sp)
/*    3fe64:	8fac0264 */ 	lw	$t4,0x264($sp)
/*    3fe68:	3c098006 */ 	lui	$t1,%hi(var8005f670)
/*    3fe6c:	24010064 */ 	addiu	$at,$zero,0x64
/*    3fe70:	000c7080 */ 	sll	$t6,$t4,0x2
/*    3fe74:	012e4821 */ 	addu	$t1,$t1,$t6
/*    3fe78:	8d29f670 */ 	lw	$t1,%lo(var8005f670)($t1)
/*    3fe7c:	afa90254 */ 	sw	$t1,0x254($sp)
/*    3fe80:	91380000 */ 	lbu	$t8,0x0($t1)
/*    3fe84:	13010067 */ 	beq	$t8,$at,.L00040024
/*    3fe88:	00000000 */ 	nop
.L0003fe8c:
/*    3fe8c:	8fab0254 */ 	lw	$t3,0x254($sp)
/*    3fe90:	916a0002 */ 	lbu	$t2,0x2($t3)
/*    3fe94:	29410008 */ 	slti	$at,$t2,0x8
/*    3fe98:	10200003 */ 	beqz	$at,.L0003fea8
/*    3fe9c:	00000000 */ 	nop
/*    3fea0:	10000003 */ 	b	.L0003feb0
/*    3fea4:	afaa0244 */ 	sw	$t2,0x244($sp)
.L0003fea8:
/*    3fea8:	24080008 */ 	addiu	$t0,$zero,0x8
/*    3feac:	afa80244 */ 	sw	$t0,0x244($sp)
.L0003feb0:
/*    3feb0:	a3a00243 */ 	sb	$zero,0x243($sp)
/*    3feb4:	8faf0244 */ 	lw	$t7,0x244($sp)
/*    3feb8:	afa0026c */ 	sw	$zero,0x26c($sp)
/*    3febc:	19e00015 */ 	blez	$t7,.L0003ff14
/*    3fec0:	00000000 */ 	nop
.L0003fec4:
/*    3fec4:	8fb90254 */ 	lw	$t9,0x254($sp)
/*    3fec8:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    3fecc:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    3fed0:	8f2d0004 */ 	lw	$t5,0x4($t9)
/*    3fed4:	018e4804 */ 	sllv	$t1,$t6,$t4
/*    3fed8:	01a9c024 */ 	and	$t8,$t5,$t1
/*    3fedc:	13000007 */ 	beqz	$t8,.L0003fefc
/*    3fee0:	00000000 */ 	nop
/*    3fee4:	8faa026c */ 	lw	$t2,0x26c($sp)
/*    3fee8:	93ab0243 */ 	lbu	$t3,0x243($sp)
/*    3feec:	03aa4021 */ 	addu	$t0,$sp,$t2
/*    3fef0:	91080248 */ 	lbu	$t0,0x248($t0)
/*    3fef4:	01687825 */ 	or	$t7,$t3,$t0
/*    3fef8:	a3af0243 */ 	sb	$t7,0x243($sp)
.L0003fefc:
/*    3fefc:	8fb9026c */ 	lw	$t9,0x26c($sp)
/*    3ff00:	8fac0244 */ 	lw	$t4,0x244($sp)
/*    3ff04:	272e0001 */ 	addiu	$t6,$t9,0x1
/*    3ff08:	01cc082a */ 	slt	$at,$t6,$t4
/*    3ff0c:	1420ffed */ 	bnez	$at,.L0003fec4
/*    3ff10:	afae026c */ 	sw	$t6,0x26c($sp)
.L0003ff14:
/*    3ff14:	8fad0254 */ 	lw	$t5,0x254($sp)
/*    3ff18:	91a90002 */ 	lbu	$t1,0x2($t5)
/*    3ff1c:	29210009 */ 	slti	$at,$t1,0x9
/*    3ff20:	1420000b */ 	bnez	$at,.L0003ff50
/*    3ff24:	00000000 */ 	nop
/*    3ff28:	8fb80264 */ 	lw	$t8,0x264($sp)
/*    3ff2c:	93ab0243 */ 	lbu	$t3,0x243($sp)
/*    3ff30:	3c0f8006 */ 	lui	$t7,%hi(var8005f6fc)
/*    3ff34:	8deff6fc */ 	lw	$t7,%lo(var8005f6fc)($t7)
/*    3ff38:	00185200 */ 	sll	$t2,$t8,0x8
/*    3ff3c:	014b4021 */ 	addu	$t0,$t2,$t3
/*    3ff40:	01e8c821 */ 	addu	$t9,$t7,$t0
/*    3ff44:	a3200000 */ 	sb	$zero,0x0($t9)
/*    3ff48:	1000002f */ 	b	.L00040008
/*    3ff4c:	00000000 */ 	nop
.L0003ff50:
/*    3ff50:	8fae0244 */ 	lw	$t6,0x244($sp)
/*    3ff54:	240c0100 */ 	addiu	$t4,$zero,0x100
/*    3ff58:	01cc6807 */ 	srav	$t5,$t4,$t6
/*    3ff5c:	afad023c */ 	sw	$t5,0x23c($sp)
/*    3ff60:	8fa90254 */ 	lw	$t1,0x254($sp)
/*    3ff64:	91380001 */ 	lbu	$t8,0x1($t1)
/*    3ff68:	912b0000 */ 	lbu	$t3,0x0($t1)
/*    3ff6c:	00185100 */ 	sll	$t2,$t8,0x4
/*    3ff70:	014b7825 */ 	or	$t7,$t2,$t3
/*    3ff74:	afaf0238 */ 	sw	$t7,0x238($sp)
/*    3ff78:	8fa8023c */ 	lw	$t0,0x23c($sp)
/*    3ff7c:	afa0026c */ 	sw	$zero,0x26c($sp)
/*    3ff80:	19000021 */ 	blez	$t0,.L00040008
/*    3ff84:	00000000 */ 	nop
.L0003ff88:
/*    3ff88:	93b90243 */ 	lbu	$t9,0x243($sp)
/*    3ff8c:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    3ff90:	032c7025 */ 	or	$t6,$t9,$t4
/*    3ff94:	afae0024 */ 	sw	$t6,0x24($sp)
/*    3ff98:	93b80243 */ 	lbu	$t8,0x243($sp)
/*    3ff9c:	8fa9026c */ 	lw	$t1,0x26c($sp)
/*    3ffa0:	8fab0264 */ 	lw	$t3,0x264($sp)
/*    3ffa4:	3c198006 */ 	lui	$t9,%hi(var8005f6f8)
/*    3ffa8:	8f39f6f8 */ 	lw	$t9,%lo(var8005f6f8)($t9)
/*    3ffac:	8fad0238 */ 	lw	$t5,0x238($sp)
/*    3ffb0:	03095025 */ 	or	$t2,$t8,$t1
/*    3ffb4:	000b7a00 */ 	sll	$t7,$t3,0x8
/*    3ffb8:	01ea4021 */ 	addu	$t0,$t7,$t2
/*    3ffbc:	03286021 */ 	addu	$t4,$t9,$t0
/*    3ffc0:	a18d0000 */ 	sb	$t5,0x0($t4)
/*    3ffc4:	93b80243 */ 	lbu	$t8,0x243($sp)
/*    3ffc8:	8fa9026c */ 	lw	$t1,0x26c($sp)
/*    3ffcc:	8faf0264 */ 	lw	$t7,0x264($sp)
/*    3ffd0:	3c088006 */ 	lui	$t0,%hi(var8005f6fc)
/*    3ffd4:	8d08f6fc */ 	lw	$t0,%lo(var8005f6fc)($t0)
/*    3ffd8:	8fae0244 */ 	lw	$t6,0x244($sp)
/*    3ffdc:	03095825 */ 	or	$t3,$t8,$t1
/*    3ffe0:	000f5200 */ 	sll	$t2,$t7,0x8
/*    3ffe4:	014bc821 */ 	addu	$t9,$t2,$t3
/*    3ffe8:	01196821 */ 	addu	$t5,$t0,$t9
/*    3ffec:	a1ae0000 */ 	sb	$t6,0x0($t5)
/*    3fff0:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    3fff4:	8fa9023c */ 	lw	$t1,0x23c($sp)
/*    3fff8:	25980001 */ 	addiu	$t8,$t4,0x1
/*    3fffc:	0309082a */ 	slt	$at,$t8,$t1
/*    40000:	1420ffe1 */ 	bnez	$at,.L0003ff88
/*    40004:	afb8026c */ 	sw	$t8,0x26c($sp)
.L00040008:
/*    40008:	8faf0254 */ 	lw	$t7,0x254($sp)
/*    4000c:	24010064 */ 	addiu	$at,$zero,0x64
/*    40010:	25ea0008 */ 	addiu	$t2,$t7,0x8
/*    40014:	afaa0254 */ 	sw	$t2,0x254($sp)
/*    40018:	914b0000 */ 	lbu	$t3,0x0($t2)
/*    4001c:	1561ff9b */ 	bne	$t3,$at,.L0003fe8c
/*    40020:	00000000 */ 	nop
.L00040024:
/*    40024:	8fa80264 */ 	lw	$t0,0x264($sp)
/*    40028:	25190001 */ 	addiu	$t9,$t0,0x1
/*    4002c:	2b210022 */ 	slti	$at,$t9,0x22
/*    40030:	1420fedf */ 	bnez	$at,.L0003fbb0
/*    40034:	afb90264 */ 	sw	$t9,0x264($sp)
/*    40038:	3c0e800a */ 	lui	$t6,%hi(var8009c644)
/*    4003c:	8dcec644 */ 	lw	$t6,%lo(var8009c644)($t6)
/*    40040:	3c01800a */ 	lui	$at,%hi(var8009c648)
/*    40044:	ac2ec648 */ 	sw	$t6,%lo(var8009c648)($at)
/*    40048:	3c0d800a */ 	lui	$t5,%hi(var8009c648)
/*    4004c:	8dadc648 */ 	lw	$t5,%lo(var8009c648)($t5)
/*    40050:	15a00003 */ 	bnez	$t5,.L00040060
/*    40054:	00000000 */ 	nop
/*    40058:	1000003d */ 	b	.L00040150
/*    4005c:	00001025 */ 	or	$v0,$zero,$zero
.L00040060:
/*    40060:	afa0026c */ 	sw	$zero,0x26c($sp)
.L00040064:
/*    40064:	8fac026c */ 	lw	$t4,0x26c($sp)
/*    40068:	3c017006 */ 	lui	$at,%hi(var70059c68)
/*    4006c:	c42e9c68 */ 	lwc1	$f14,%lo(var70059c68)($at)
/*    40070:	448c5000 */ 	mtc1	$t4,$f10
/*    40074:	0c0117b4 */ 	jal	func00045ed0
/*    40078:	46805320 */ 	cvt.s.w	$f12,$f10
/*    4007c:	8fa9026c */ 	lw	$t1,0x26c($sp)
/*    40080:	3c18800a */ 	lui	$t8,%hi(var8009c648)
/*    40084:	8f18c648 */ 	lw	$t8,%lo(var8009c648)($t8)
/*    40088:	00097880 */ 	sll	$t7,$t1,0x2
/*    4008c:	030f5021 */ 	addu	$t2,$t8,$t7
/*    40090:	e5400000 */ 	swc1	$f0,0x0($t2)
/*    40094:	8fab026c */ 	lw	$t3,0x26c($sp)
/*    40098:	25680001 */ 	addiu	$t0,$t3,0x1
/*    4009c:	29012000 */ 	slti	$at,$t0,0x2000
/*    400a0:	1420fff0 */ 	bnez	$at,.L00040064
/*    400a4:	afa8026c */ 	sw	$t0,0x26c($sp)
/*    400a8:	afa0026c */ 	sw	$zero,0x26c($sp)
.L000400ac:
/*    400ac:	8fb9026c */ 	lw	$t9,0x26c($sp)
/*    400b0:	3c014000 */ 	lui	$at,0x4000
/*    400b4:	44816000 */ 	mtc1	$at,$f12
/*    400b8:	44998000 */ 	mtc1	$t9,$f16
/*    400bc:	3c01bf00 */ 	lui	$at,0xbf00
/*    400c0:	44812000 */ 	mtc1	$at,$f4
/*    400c4:	468084a0 */ 	cvt.s.w	$f18,$f16
/*    400c8:	46049382 */ 	mul.s	$f14,$f18,$f4
/*    400cc:	0c0117b4 */ 	jal	func00045ed0
/*    400d0:	00000000 */ 	nop
/*    400d4:	8fad026c */ 	lw	$t5,0x26c($sp)
/*    400d8:	3c0e800a */ 	lui	$t6,%hi(var8009c6d8)
/*    400dc:	8dcec6d8 */ 	lw	$t6,%lo(var8009c6d8)($t6)
/*    400e0:	000d6080 */ 	sll	$t4,$t5,0x2
/*    400e4:	01cc4821 */ 	addu	$t1,$t6,$t4
/*    400e8:	e5200000 */ 	swc1	$f0,0x0($t1)
/*    400ec:	8fb8026c */ 	lw	$t8,0x26c($sp)
/*    400f0:	3c014000 */ 	lui	$at,0x4000
/*    400f4:	44816000 */ 	mtc1	$at,$f12
/*    400f8:	44983000 */ 	mtc1	$t8,$f6
/*    400fc:	3c01c000 */ 	lui	$at,0xc000
/*    40100:	44815000 */ 	mtc1	$at,$f10
/*    40104:	46803220 */ 	cvt.s.w	$f8,$f6
/*    40108:	460a4382 */ 	mul.s	$f14,$f8,$f10
/*    4010c:	0c0117b4 */ 	jal	func00045ed0
/*    40110:	00000000 */ 	nop
/*    40114:	8faa026c */ 	lw	$t2,0x26c($sp)
/*    40118:	3c0f800a */ 	lui	$t7,%hi(var8009c6dc)
/*    4011c:	8defc6dc */ 	lw	$t7,%lo(var8009c6dc)($t7)
/*    40120:	000a5880 */ 	sll	$t3,$t2,0x2
/*    40124:	01eb4021 */ 	addu	$t0,$t7,$t3
/*    40128:	e5000000 */ 	swc1	$f0,0x0($t0)
/*    4012c:	8fb9026c */ 	lw	$t9,0x26c($sp)
/*    40130:	272d0001 */ 	addiu	$t5,$t9,0x1
/*    40134:	29a10100 */ 	slti	$at,$t5,0x100
/*    40138:	1420ffdc */ 	bnez	$at,.L000400ac
/*    4013c:	afad026c */ 	sw	$t5,0x26c($sp)
/*    40140:	10000003 */ 	b	.L00040150
/*    40144:	24020001 */ 	addiu	$v0,$zero,0x1
/*    40148:	10000001 */ 	b	.L00040150
/*    4014c:	00000000 */ 	nop
.L00040150:
/*    40150:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*    40154:	8fb00018 */ 	lw	$s0,0x18($sp)
/*    40158:	27bd0270 */ 	addiu	$sp,$sp,0x270
/*    4015c:	03e00008 */ 	jr	$ra
/*    40160:	00000000 */ 	nop
);

const u32 var70059adc[] = {0x00000000};
const u32 var70059ae0[] = {0x00000000};
const u32 var70059ae4[] = {0x00000000};
const u32 var70059ae8[] = {0x00000000};
const u32 var70059aec[] = {0x00000000};
const u32 var70059af0[] = {0x00000000};
const u32 var70059af4[] = {0x00000000};
const u32 var70059af8[] = {0x00000000};
const u32 var70059afc[] = {0x00000000};
const u32 var70059b00[] = {0x00000000};
const u32 var70059b04[] = {0x00000000};
const u32 var70059b08[] = {0x00000001};
const u32 var70059b0c[] = {0x00000001};
const u32 var70059b10[] = {0x00000001};
const u32 var70059b14[] = {0x00000001};
const u32 var70059b18[] = {0x00000002};
const u32 var70059b1c[] = {0x00000002};
const u32 var70059b20[] = {0x00000003};
const u32 var70059b24[] = {0x00000003};
const u32 var70059b28[] = {0x00000003};
const u32 var70059b2c[] = {0x00000002};
const u32 var70059b30[] = {0x00000000};

GLOBAL_ASM(
glabel func00040164
/*    40164:	27bdfe40 */ 	addiu	$sp,$sp,-448
/*    40168:	afbf001c */ 	sw	$ra,0x1c($sp)
/*    4016c:	afa401c0 */ 	sw	$a0,0x1c0($sp)
/*    40170:	afa501c4 */ 	sw	$a1,0x1c4($sp)
/*    40174:	afa601c8 */ 	sw	$a2,0x1c8($sp)
/*    40178:	afb00018 */ 	sw	$s0,0x18($sp)
/*    4017c:	3c0f7006 */ 	lui	$t7,%hi(var70059adc)
/*    40180:	25ef9adc */ 	addiu	$t7,$t7,%lo(var70059adc)
/*    40184:	25e80054 */ 	addiu	$t0,$t7,0x54
/*    40188:	27ae0158 */ 	addiu	$t6,$sp,0x158
.L0004018c:
/*    4018c:	8df90000 */ 	lw	$t9,0x0($t7)
/*    40190:	25ef000c */ 	addiu	$t7,$t7,0xc
/*    40194:	25ce000c */ 	addiu	$t6,$t6,0xc
/*    40198:	add9fff4 */ 	sw	$t9,-0xc($t6)
/*    4019c:	8df8fff8 */ 	lw	$t8,-0x8($t7)
/*    401a0:	add8fff8 */ 	sw	$t8,-0x8($t6)
/*    401a4:	8df9fffc */ 	lw	$t9,-0x4($t7)
/*    401a8:	15e8fff8 */ 	bne	$t7,$t0,.L0004018c
/*    401ac:	add9fffc */ 	sw	$t9,-0x4($t6)
/*    401b0:	8df90000 */ 	lw	$t9,0x0($t7)
/*    401b4:	add90000 */ 	sw	$t9,0x0($t6)
/*    401b8:	8fa901c0 */ 	lw	$t1,0x1c0($sp)
/*    401bc:	8d2b3ba4 */ 	lw	$t3,0x3ba4($t1)
/*    401c0:	8d2a3bb4 */ 	lw	$t2,0x3bb4($t1)
/*    401c4:	000b6080 */ 	sll	$t4,$t3,0x2
/*    401c8:	018b6023 */ 	subu	$t4,$t4,$t3
/*    401cc:	014c6821 */ 	addu	$t5,$t2,$t4
/*    401d0:	afad01bc */ 	sw	$t5,0x1bc($sp)
/*    401d4:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*    401d8:	8fa801c0 */ 	lw	$t0,0x1c0($sp)
/*    401dc:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*    401e0:	000f7080 */ 	sll	$t6,$t7,0x2
/*    401e4:	010ec021 */ 	addu	$t8,$t0,$t6
/*    401e8:	00194880 */ 	sll	$t1,$t9,0x2
/*    401ec:	03095821 */ 	addu	$t3,$t8,$t1
/*    401f0:	8d6a3c98 */ 	lw	$t2,0x3c98($t3)
/*    401f4:	11400033 */ 	beqz	$t2,.L000402c4
/*    401f8:	00000000 */ 	nop
/*    401fc:	8d6c3ca0 */ 	lw	$t4,0x3ca0($t3)
/*    40200:	24010002 */ 	addiu	$at,$zero,0x2
/*    40204:	1581002f */ 	bne	$t4,$at,.L000402c4
/*    40208:	00000000 */ 	nop
/*    4020c:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*    40210:	8fad01c0 */ 	lw	$t5,0x1c0($sp)
/*    40214:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*    40218:	000f4080 */ 	sll	$t0,$t7,0x2
/*    4021c:	01a87021 */ 	addu	$t6,$t5,$t0
/*    40220:	0019c080 */ 	sll	$t8,$t9,0x2
/*    40224:	01d84821 */ 	addu	$t1,$t6,$t8
/*    40228:	8d2a3ca8 */ 	lw	$t2,0x3ca8($t1)
/*    4022c:	1140000c */ 	beqz	$t2,.L00040260
/*    40230:	00000000 */ 	nop
/*    40234:	8fab01bc */ 	lw	$t3,0x1bc($sp)
/*    40238:	3c0f7005 */ 	lui	$t7,%hi(var700579b8+0x2)
/*    4023c:	000b60c0 */ 	sll	$t4,$t3,0x3
/*    40240:	018b6021 */ 	addu	$t4,$t4,$t3
/*    40244:	000c6080 */ 	sll	$t4,$t4,0x2
/*    40248:	018b6021 */ 	addu	$t4,$t4,$t3
/*    4024c:	000c6040 */ 	sll	$t4,$t4,0x1
/*    40250:	01ec7821 */ 	addu	$t7,$t7,$t4
/*    40254:	85ef79ba */ 	lh	$t7,%lo(var700579b8+0x2)($t7)
/*    40258:	10000018 */ 	b	.L000402bc
/*    4025c:	afaf01b8 */ 	sw	$t7,0x1b8($sp)
.L00040260:
/*    40260:	8fad01bc */ 	lw	$t5,0x1bc($sp)
/*    40264:	3c197005 */ 	lui	$t9,%hi(var700579e8)
/*    40268:	000d40c0 */ 	sll	$t0,$t5,0x3
/*    4026c:	010d4021 */ 	addu	$t0,$t0,$t5
/*    40270:	00084080 */ 	sll	$t0,$t0,0x2
/*    40274:	010d4021 */ 	addu	$t0,$t0,$t5
/*    40278:	00084040 */ 	sll	$t0,$t0,0x1
/*    4027c:	0328c821 */ 	addu	$t9,$t9,$t0
/*    40280:	873979e8 */ 	lh	$t9,%lo(var700579e8)($t9)
/*    40284:	00197080 */ 	sll	$t6,$t9,0x2
/*    40288:	01d97023 */ 	subu	$t6,$t6,$t9
/*    4028c:	afae01b8 */ 	sw	$t6,0x1b8($sp)
/*    40290:	8fb801bc */ 	lw	$t8,0x1bc($sp)
/*    40294:	3c0a7005 */ 	lui	$t2,%hi(var700579e8)
/*    40298:	001848c0 */ 	sll	$t1,$t8,0x3
/*    4029c:	01384821 */ 	addu	$t1,$t1,$t8
/*    402a0:	00094880 */ 	sll	$t1,$t1,0x2
/*    402a4:	01384821 */ 	addu	$t1,$t1,$t8
/*    402a8:	00094840 */ 	sll	$t1,$t1,0x1
/*    402ac:	01495021 */ 	addu	$t2,$t2,$t1
/*    402b0:	854a79e8 */ 	lh	$t2,%lo(var700579e8)($t2)
/*    402b4:	afaa01b0 */ 	sw	$t2,0x1b0($sp)
/*    402b8:	afa001b4 */ 	sw	$zero,0x1b4($sp)
.L000402bc:
/*    402bc:	1000000b */ 	b	.L000402ec
/*    402c0:	00000000 */ 	nop
.L000402c4:
/*    402c4:	8fab01bc */ 	lw	$t3,0x1bc($sp)
/*    402c8:	3c0f7005 */ 	lui	$t7,%hi(var700579b8+0x2)
/*    402cc:	000b60c0 */ 	sll	$t4,$t3,0x3
/*    402d0:	018b6021 */ 	addu	$t4,$t4,$t3
/*    402d4:	000c6080 */ 	sll	$t4,$t4,0x2
/*    402d8:	018b6021 */ 	addu	$t4,$t4,$t3
/*    402dc:	000c6040 */ 	sll	$t4,$t4,0x1
/*    402e0:	01ec7821 */ 	addu	$t7,$t7,$t4
/*    402e4:	85ef79ba */ 	lh	$t7,%lo(var700579b8+0x2)($t7)
/*    402e8:	afaf01b8 */ 	sw	$t7,0x1b8($sp)
.L000402ec:
/*    402ec:	8fa801c4 */ 	lw	$t0,0x1c4($sp)
/*    402f0:	8fad01c0 */ 	lw	$t5,0x1c0($sp)
/*    402f4:	8fb801c8 */ 	lw	$t8,0x1c8($sp)
/*    402f8:	0008c880 */ 	sll	$t9,$t0,0x2
/*    402fc:	01b97021 */ 	addu	$t6,$t5,$t9
/*    40300:	00184880 */ 	sll	$t1,$t8,0x2
/*    40304:	01c95021 */ 	addu	$t2,$t6,$t1
/*    40308:	8d4b3c88 */ 	lw	$t3,0x3c88($t2)
/*    4030c:	3c014000 */ 	lui	$at,0x4000
/*    40310:	44816000 */ 	mtc1	$at,$f12
/*    40314:	448b2000 */ 	mtc1	$t3,$f4
/*    40318:	3c014352 */ 	lui	$at,0x4352
/*    4031c:	44814000 */ 	mtc1	$at,$f8
/*    40320:	468021a0 */ 	cvt.s.w	$f6,$f4
/*    40324:	3c013e80 */ 	lui	$at,0x3e80
/*    40328:	44818000 */ 	mtc1	$at,$f16
/*    4032c:	46083281 */ 	sub.s	$f10,$f6,$f8
/*    40330:	46105382 */ 	mul.s	$f14,$f10,$f16
/*    40334:	0c0117b4 */ 	jal	func00045ed0
/*    40338:	00000000 */ 	nop
/*    4033c:	e7a00060 */ 	swc1	$f0,0x60($sp)
/*    40340:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*    40344:	8fac01c0 */ 	lw	$t4,0x1c0($sp)
/*    40348:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*    4034c:	000f4080 */ 	sll	$t0,$t7,0x2
/*    40350:	01886821 */ 	addu	$t5,$t4,$t0
/*    40354:	0019c080 */ 	sll	$t8,$t9,0x2
/*    40358:	01b87021 */ 	addu	$t6,$t5,$t8
/*    4035c:	8dc93cf8 */ 	lw	$t1,0x3cf8($t6)
/*    40360:	afa90054 */ 	sw	$t1,0x54($sp)
/*    40364:	afa0005c */ 	sw	$zero,0x5c($sp)
.L00040368:
/*    40368:	8fab01c4 */ 	lw	$t3,0x1c4($sp)
/*    4036c:	8faa01c0 */ 	lw	$t2,0x1c0($sp)
/*    40370:	8fa801c8 */ 	lw	$t0,0x1c8($sp)
/*    40374:	8fae005c */ 	lw	$t6,0x5c($sp)
/*    40378:	000b7880 */ 	sll	$t7,$t3,0x2
/*    4037c:	014f6021 */ 	addu	$t4,$t2,$t7
/*    40380:	0008c880 */ 	sll	$t9,$t0,0x2
/*    40384:	000e4880 */ 	sll	$t1,$t6,0x2
/*    40388:	03a97821 */ 	addu	$t7,$sp,$t1
/*    4038c:	01996821 */ 	addu	$t5,$t4,$t9
/*    40390:	8db83cf0 */ 	lw	$t8,0x3cf0($t5)
/*    40394:	8def0158 */ 	lw	$t7,0x158($t7)
/*    40398:	000bc940 */ 	sll	$t9,$t3,0x5
/*    4039c:	032bc823 */ 	subu	$t9,$t9,$t3
/*    403a0:	01f80019 */ 	multu	$t7,$t8
/*    403a4:	00087140 */ 	sll	$t6,$t0,0x5
/*    403a8:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*    403ac:	01c87023 */ 	subu	$t6,$t6,$t0
/*    403b0:	000e70c0 */ 	sll	$t6,$t6,0x3
/*    403b4:	01596821 */ 	addu	$t5,$t2,$t9
/*    403b8:	01ae7821 */ 	addu	$t7,$t5,$t6
/*    403bc:	01e9c021 */ 	addu	$t8,$t7,$t1
/*    403c0:	8f0b3d08 */ 	lw	$t3,0x3d08($t8)
/*    403c4:	8fb90054 */ 	lw	$t9,0x54($sp)
/*    403c8:	00006012 */ 	mflo	$t4
/*    403cc:	018b5021 */ 	addu	$t2,$t4,$t3
/*    403d0:	27280001 */ 	addiu	$t0,$t9,0x1
/*    403d4:	01480019 */ 	multu	$t2,$t0
/*    403d8:	00006812 */ 	mflo	$t5
/*    403dc:	afad004c */ 	sw	$t5,0x4c($sp)
/*    403e0:	00000000 */ 	nop
/*    403e4:	8faf004c */ 	lw	$t7,0x4c($sp)
/*    403e8:	3c0e800a */ 	lui	$t6,%hi(var8009c6d8)
/*    403ec:	8dcec6d8 */ 	lw	$t6,%lo(var8009c6d8)($t6)
/*    403f0:	000f4880 */ 	sll	$t1,$t7,0x2
/*    403f4:	c7a40060 */ 	lwc1	$f4,0x60($sp)
/*    403f8:	01c9c021 */ 	addu	$t8,$t6,$t1
/*    403fc:	c7120000 */ 	lwc1	$f18,0x0($t8)
/*    40400:	8fac005c */ 	lw	$t4,0x5c($sp)
/*    40404:	46049182 */ 	mul.s	$f6,$f18,$f4
/*    40408:	000c5880 */ 	sll	$t3,$t4,0x2
/*    4040c:	03abc821 */ 	addu	$t9,$sp,$t3
/*    40410:	e7260100 */ 	swc1	$f6,0x100($t9)
/*    40414:	8faa005c */ 	lw	$t2,0x5c($sp)
/*    40418:	25480001 */ 	addiu	$t0,$t2,0x1
/*    4041c:	29010016 */ 	slti	$at,$t0,0x16
/*    40420:	1420ffd1 */ 	bnez	$at,.L00040368
/*    40424:	afa8005c */ 	sw	$t0,0x5c($sp)
/*    40428:	afa00058 */ 	sw	$zero,0x58($sp)
.L0004042c:
/*    4042c:	afa0005c */ 	sw	$zero,0x5c($sp)
.L00040430:
/*    40430:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*    40434:	8fb801c8 */ 	lw	$t8,0x1c8($sp)
/*    40438:	8fad01c0 */ 	lw	$t5,0x1c0($sp)
/*    4043c:	000f7080 */ 	sll	$t6,$t7,0x2
/*    40440:	8fb90058 */ 	lw	$t9,0x58($sp)
/*    40444:	01cf7023 */ 	subu	$t6,$t6,$t7
/*    40448:	00186080 */ 	sll	$t4,$t8,0x2
/*    4044c:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40450:	01986023 */ 	subu	$t4,$t4,$t8
/*    40454:	000c6080 */ 	sll	$t4,$t4,0x2
/*    40458:	01ae4821 */ 	addu	$t1,$t5,$t6
/*    4045c:	012c5821 */ 	addu	$t3,$t1,$t4
/*    40460:	00195080 */ 	sll	$t2,$t9,0x2
/*    40464:	016a4021 */ 	addu	$t0,$t3,$t2
/*    40468:	8d0f3cc8 */ 	lw	$t7,0x3cc8($t0)
/*    4046c:	afaf0050 */ 	sw	$t7,0x50($sp)
/*    40470:	8fae01c4 */ 	lw	$t6,0x1c4($sp)
/*    40474:	8faa0058 */ 	lw	$t2,0x58($sp)
/*    40478:	8fac01c8 */ 	lw	$t4,0x1c8($sp)
/*    4047c:	8fad01c0 */ 	lw	$t5,0x1c0($sp)
/*    40480:	000ec140 */ 	sll	$t8,$t6,0x5
/*    40484:	030ec023 */ 	subu	$t8,$t8,$t6
/*    40488:	000a4080 */ 	sll	$t0,$t2,0x2
/*    4048c:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    40490:	010a4023 */ 	subu	$t0,$t0,$t2
/*    40494:	000cc940 */ 	sll	$t9,$t4,0x5
/*    40498:	8fae005c */ 	lw	$t6,0x5c($sp)
/*    4049c:	00084080 */ 	sll	$t0,$t0,0x2
/*    404a0:	032cc823 */ 	subu	$t9,$t9,$t4
/*    404a4:	01b84821 */ 	addu	$t1,$t5,$t8
/*    404a8:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*    404ac:	010a4021 */ 	addu	$t0,$t0,$t2
/*    404b0:	00084080 */ 	sll	$t0,$t0,0x2
/*    404b4:	01395821 */ 	addu	$t3,$t1,$t9
/*    404b8:	01687821 */ 	addu	$t7,$t3,$t0
/*    404bc:	000e6880 */ 	sll	$t5,$t6,0x2
/*    404c0:	8fa90054 */ 	lw	$t1,0x54($sp)
/*    404c4:	01edc021 */ 	addu	$t8,$t7,$t5
/*    404c8:	8f0c3d64 */ 	lw	$t4,0x3d64($t8)
/*    404cc:	25390001 */ 	addiu	$t9,$t1,0x1
/*    404d0:	01990019 */ 	multu	$t4,$t9
/*    404d4:	00005012 */ 	mflo	$t2
/*    404d8:	afaa004c */ 	sw	$t2,0x4c($sp)
/*    404dc:	00000000 */ 	nop
/*    404e0:	8fb80050 */ 	lw	$t8,0x50($sp)
/*    404e4:	3c0d800a */ 	lui	$t5,%hi(var8009c6dc)
/*    404e8:	8dadc6dc */ 	lw	$t5,%lo(var8009c6dc)($t5)
/*    404ec:	00184880 */ 	sll	$t1,$t8,0x2
/*    404f0:	c7b00060 */ 	lwc1	$f16,0x60($sp)
/*    404f4:	01a96021 */ 	addu	$t4,$t5,$t1
/*    404f8:	c58a0000 */ 	lwc1	$f10,0x0($t4)
/*    404fc:	8fa8004c */ 	lw	$t0,0x4c($sp)
/*    40500:	3c0b800a */ 	lui	$t3,%hi(var8009c6d8)
/*    40504:	460a8482 */ 	mul.s	$f18,$f16,$f10
/*    40508:	8d6bc6d8 */ 	lw	$t3,%lo(var8009c6d8)($t3)
/*    4050c:	00087080 */ 	sll	$t6,$t0,0x2
/*    40510:	8fb90058 */ 	lw	$t9,0x58($sp)
/*    40514:	016e7821 */ 	addu	$t7,$t3,$t6
/*    40518:	c5e80000 */ 	lwc1	$f8,0x0($t7)
/*    4051c:	00195080 */ 	sll	$t2,$t9,0x2
/*    40520:	8fa8005c */ 	lw	$t0,0x5c($sp)
/*    40524:	46124102 */ 	mul.s	$f4,$f8,$f18
/*    40528:	01595023 */ 	subu	$t2,$t2,$t9
/*    4052c:	000a5080 */ 	sll	$t2,$t2,0x2
/*    40530:	01595021 */ 	addu	$t2,$t2,$t9
/*    40534:	000a5080 */ 	sll	$t2,$t2,0x2
/*    40538:	00085880 */ 	sll	$t3,$t0,0x2
/*    4053c:	014b7021 */ 	addu	$t6,$t2,$t3
/*    40540:	03ae7821 */ 	addu	$t7,$sp,$t6
/*    40544:	e5e40064 */ 	swc1	$f4,0x64($t7)
/*    40548:	8fb8005c */ 	lw	$t8,0x5c($sp)
/*    4054c:	270d0001 */ 	addiu	$t5,$t8,0x1
/*    40550:	29a1000d */ 	slti	$at,$t5,0xd
/*    40554:	1420ffb6 */ 	bnez	$at,.L00040430
/*    40558:	afad005c */ 	sw	$t5,0x5c($sp)
/*    4055c:	8fa90058 */ 	lw	$t1,0x58($sp)
/*    40560:	252c0001 */ 	addiu	$t4,$t1,0x1
/*    40564:	29810003 */ 	slti	$at,$t4,0x3
/*    40568:	1420ffb0 */ 	bnez	$at,.L0004042c
/*    4056c:	afac0058 */ 	sw	$t4,0x58($sp)
/*    40570:	afa0005c */ 	sw	$zero,0x5c($sp)
/*    40574:	afa00048 */ 	sw	$zero,0x48($sp)
/*    40578:	8fa801c8 */ 	lw	$t0,0x1c8($sp)
/*    4057c:	8fb901c0 */ 	lw	$t9,0x1c0($sp)
/*    40580:	00085080 */ 	sll	$t2,$t0,0x2
/*    40584:	032a5821 */ 	addu	$t3,$t9,$t2
/*    40588:	8d6e465c */ 	lw	$t6,0x465c($t3)
/*    4058c:	afae0044 */ 	sw	$t6,0x44($sp)
/*    40590:	8fb801c8 */ 	lw	$t8,0x1c8($sp)
/*    40594:	8faf01c0 */ 	lw	$t7,0x1c0($sp)
/*    40598:	001868c0 */ 	sll	$t5,$t8,0x3
/*    4059c:	01b86821 */ 	addu	$t5,$t5,$t8
/*    405a0:	000d6a00 */ 	sll	$t5,$t5,0x8
/*    405a4:	01ed4821 */ 	addu	$t1,$t7,$t5
/*    405a8:	252c4664 */ 	addiu	$t4,$t1,0x4664
/*    405ac:	afac0040 */ 	sw	$t4,0x40($sp)
/*    405b0:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*    405b4:	8fa801c0 */ 	lw	$t0,0x1c0($sp)
/*    405b8:	001950c0 */ 	sll	$t2,$t9,0x3
/*    405bc:	01595021 */ 	addu	$t2,$t2,$t9
/*    405c0:	000a5140 */ 	sll	$t2,$t2,0x5
/*    405c4:	01595021 */ 	addu	$t2,$t2,$t9
/*    405c8:	000a5080 */ 	sll	$t2,$t2,0x2
/*    405cc:	010a5821 */ 	addu	$t3,$t0,$t2
/*    405d0:	256e3f94 */ 	addiu	$t6,$t3,0x3f94
/*    405d4:	afae003c */ 	sw	$t6,0x3c($sp)
/*    405d8:	8faf01c8 */ 	lw	$t7,0x1c8($sp)
/*    405dc:	8fb801c0 */ 	lw	$t8,0x1c0($sp)
/*    405e0:	000f68c0 */ 	sll	$t5,$t7,0x3
/*    405e4:	01af6821 */ 	addu	$t5,$t5,$t7
/*    405e8:	000d6940 */ 	sll	$t5,$t5,0x5
/*    405ec:	01af6821 */ 	addu	$t5,$t5,$t7
/*    405f0:	000d6840 */ 	sll	$t5,$t5,0x1
/*    405f4:	030d4821 */ 	addu	$t1,$t8,$t5
/*    405f8:	252c4418 */ 	addiu	$t4,$t1,0x4418
/*    405fc:	afac0038 */ 	sw	$t4,0x38($sp)
/*    40600:	8fa801c4 */ 	lw	$t0,0x1c4($sp)
/*    40604:	8fb901c0 */ 	lw	$t9,0x1c0($sp)
/*    40608:	8fae01c8 */ 	lw	$t6,0x1c8($sp)
/*    4060c:	00085080 */ 	sll	$t2,$t0,0x2
/*    40610:	032a5821 */ 	addu	$t3,$t9,$t2
/*    40614:	000e7880 */ 	sll	$t7,$t6,0x2
/*    40618:	016fc021 */ 	addu	$t8,$t3,$t7
/*    4061c:	8f103ca0 */ 	lw	$s0,0x3ca0($t8)
/*    40620:	3a100002 */ 	xori	$s0,$s0,0x2
/*    40624:	2e100001 */ 	sltiu	$s0,$s0,0x1
/*    40628:	12000003 */ 	beqz	$s0,.L00040638
/*    4062c:	00000000 */ 	nop
/*    40630:	8f103ca8 */ 	lw	$s0,0x3ca8($t8)
/*    40634:	2e100001 */ 	sltiu	$s0,$s0,0x1
.L00040638:
/*    40638:	afb00034 */ 	sw	$s0,0x34($sp)
/*    4063c:	8fa901c4 */ 	lw	$t1,0x1c4($sp)
/*    40640:	8fad01c0 */ 	lw	$t5,0x1c0($sp)
/*    40644:	8fb901c8 */ 	lw	$t9,0x1c8($sp)
/*    40648:	00096080 */ 	sll	$t4,$t1,0x2
/*    4064c:	01ac4021 */ 	addu	$t0,$t5,$t4
/*    40650:	00195080 */ 	sll	$t2,$t9,0x2
/*    40654:	010a7021 */ 	addu	$t6,$t0,$t2
/*    40658:	8dd03ca0 */ 	lw	$s0,0x3ca0($t6)
/*    4065c:	3a100002 */ 	xori	$s0,$s0,0x2
/*    40660:	2e100001 */ 	sltiu	$s0,$s0,0x1
/*    40664:	12000003 */ 	beqz	$s0,.L00040674
/*    40668:	00000000 */ 	nop
/*    4066c:	8dd03ca8 */ 	lw	$s0,0x3ca8($t6)
/*    40670:	0010802b */ 	sltu	$s0,$zero,$s0
.L00040674:
/*    40674:	afb00030 */ 	sw	$s0,0x30($sp)
/*    40678:	8faf01c4 */ 	lw	$t7,0x1c4($sp)
/*    4067c:	8fab01c0 */ 	lw	$t3,0x1c0($sp)
/*    40680:	8fad01c8 */ 	lw	$t5,0x1c8($sp)
/*    40684:	000fc080 */ 	sll	$t8,$t7,0x2
/*    40688:	01784821 */ 	addu	$t1,$t3,$t8
/*    4068c:	000d6080 */ 	sll	$t4,$t5,0x2
/*    40690:	012cc821 */ 	addu	$t9,$t1,$t4
/*    40694:	8f283c98 */ 	lw	$t0,0x3c98($t9)
/*    40698:	afa8002c */ 	sw	$t0,0x2c($sp)
/*    4069c:	8faa0048 */ 	lw	$t2,0x48($sp)
/*    406a0:	8fae0044 */ 	lw	$t6,0x44($sp)
/*    406a4:	014e082a */ 	slt	$at,$t2,$t6
/*    406a8:	102001a9 */ 	beqz	$at,.L00040d50
/*    406ac:	00000000 */ 	nop
.L000406b0:
/*    406b0:	8faf01b8 */ 	lw	$t7,0x1b8($sp)
/*    406b4:	8fab0044 */ 	lw	$t3,0x44($sp)
/*    406b8:	016f082a */ 	slt	$at,$t3,$t7
/*    406bc:	10200003 */ 	beqz	$at,.L000406cc
/*    406c0:	00000000 */ 	nop
/*    406c4:	8fb80044 */ 	lw	$t8,0x44($sp)
/*    406c8:	afb801b8 */ 	sw	$t8,0x1b8($sp)
.L000406cc:
/*    406cc:	8fad002c */ 	lw	$t5,0x2c($sp)
/*    406d0:	11a0001f */ 	beqz	$t5,.L00040750
/*    406d4:	00000000 */ 	nop
/*    406d8:	8fa90034 */ 	lw	$t1,0x34($sp)
/*    406dc:	15200008 */ 	bnez	$t1,.L00040700
/*    406e0:	00000000 */ 	nop
/*    406e4:	8fac0030 */ 	lw	$t4,0x30($sp)
/*    406e8:	11800019 */ 	beqz	$t4,.L00040750
/*    406ec:	00000000 */ 	nop
/*    406f0:	8fb90048 */ 	lw	$t9,0x48($sp)
/*    406f4:	2b210024 */ 	slti	$at,$t9,0x24
/*    406f8:	14200015 */ 	bnez	$at,.L00040750
/*    406fc:	00000000 */ 	nop
.L00040700:
/*    40700:	8fa80048 */ 	lw	$t0,0x48($sp)
/*    40704:	8faa01b4 */ 	lw	$t2,0x1b4($sp)
/*    40708:	8faf01b0 */ 	lw	$t7,0x1b0($sp)
/*    4070c:	010a7023 */ 	subu	$t6,$t0,$t2
/*    40710:	01cf001a */ 	div	$zero,$t6,$t7
/*    40714:	00005812 */ 	mflo	$t3
/*    40718:	afab0058 */ 	sw	$t3,0x58($sp)
/*    4071c:	15e00002 */ 	bnez	$t7,.L00040728
/*    40720:	00000000 */ 	nop
/*    40724:	0007000d */ 	break	0x7
.L00040728:
/*    40728:	2401ffff */ 	addiu	$at,$zero,-1
/*    4072c:	15e10004 */ 	bne	$t7,$at,.L00040740
/*    40730:	3c018000 */ 	lui	$at,0x8000
/*    40734:	15c10002 */ 	bne	$t6,$at,.L00040740
/*    40738:	00000000 */ 	nop
/*    4073c:	0006000d */ 	break	0x6
.L00040740:
/*    40740:	8fb801b4 */ 	lw	$t8,0x1b4($sp)
/*    40744:	8fad01b0 */ 	lw	$t5,0x1b0($sp)
/*    40748:	030d4821 */ 	addu	$t1,$t8,$t5
/*    4074c:	afa90028 */ 	sw	$t1,0x28($sp)
.L00040750:
/*    40750:	8fac0048 */ 	lw	$t4,0x48($sp)
/*    40754:	8fb901b8 */ 	lw	$t9,0x1b8($sp)
/*    40758:	0199082a */ 	slt	$at,$t4,$t9
/*    4075c:	1020008f */ 	beqz	$at,.L0004099c
/*    40760:	00000000 */ 	nop
.L00040764:
/*    40764:	8fa8002c */ 	lw	$t0,0x2c($sp)
/*    40768:	11000054 */ 	beqz	$t0,.L000408bc
/*    4076c:	00000000 */ 	nop
/*    40770:	8faa0034 */ 	lw	$t2,0x34($sp)
/*    40774:	15400008 */ 	bnez	$t2,.L00040798
/*    40778:	00000000 */ 	nop
/*    4077c:	8fae0030 */ 	lw	$t6,0x30($sp)
/*    40780:	11c0004e */ 	beqz	$t6,.L000408bc
/*    40784:	00000000 */ 	nop
/*    40788:	8faf0048 */ 	lw	$t7,0x48($sp)
/*    4078c:	29e10024 */ 	slti	$at,$t7,0x24
/*    40790:	1420004a */ 	bnez	$at,.L000408bc
/*    40794:	00000000 */ 	nop
.L00040798:
/*    40798:	8fab0048 */ 	lw	$t3,0x48($sp)
/*    4079c:	8fb80028 */ 	lw	$t8,0x28($sp)
/*    407a0:	0178082a */ 	slt	$at,$t3,$t8
/*    407a4:	14200008 */ 	bnez	$at,.L000407c8
/*    407a8:	00000000 */ 	nop
/*    407ac:	8fad0028 */ 	lw	$t5,0x28($sp)
/*    407b0:	8fa901b0 */ 	lw	$t1,0x1b0($sp)
/*    407b4:	01a96021 */ 	addu	$t4,$t5,$t1
/*    407b8:	afac0028 */ 	sw	$t4,0x28($sp)
/*    407bc:	8fb90058 */ 	lw	$t9,0x58($sp)
/*    407c0:	27280001 */ 	addiu	$t0,$t9,0x1
/*    407c4:	afa80058 */ 	sw	$t0,0x58($sp)
.L000407c8:
/*    407c8:	8faa0058 */ 	lw	$t2,0x58($sp)
/*    407cc:	27af0064 */ 	addiu	$t7,$sp,0x64
/*    407d0:	000a7080 */ 	sll	$t6,$t2,0x2
/*    407d4:	01ca7023 */ 	subu	$t6,$t6,$t2
/*    407d8:	000e7080 */ 	sll	$t6,$t6,0x2
/*    407dc:	01ca7021 */ 	addu	$t6,$t6,$t2
/*    407e0:	000e7080 */ 	sll	$t6,$t6,0x2
/*    407e4:	01cf5821 */ 	addu	$t3,$t6,$t7
/*    407e8:	afab0024 */ 	sw	$t3,0x24($sp)
/*    407ec:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    407f0:	93100000 */ 	lbu	$s0,0x0($t8)
/*    407f4:	270d0001 */ 	addiu	$t5,$t8,0x1
/*    407f8:	afad0038 */ 	sw	$t5,0x38($sp)
/*    407fc:	12000018 */ 	beqz	$s0,.L00040860
/*    40800:	00000000 */ 	nop
/*    40804:	8fae003c */ 	lw	$t6,0x3c($sp)
/*    40808:	8fac005c */ 	lw	$t4,0x5c($sp)
/*    4080c:	3c0a800a */ 	lui	$t2,%hi(var8009c648)
/*    40810:	85cf0000 */ 	lh	$t7,0x0($t6)
/*    40814:	8d4ac648 */ 	lw	$t2,%lo(var8009c648)($t2)
/*    40818:	8fa90024 */ 	lw	$t1,0x24($sp)
/*    4081c:	000cc880 */ 	sll	$t9,$t4,0x2
/*    40820:	000f5880 */ 	sll	$t3,$t7,0x2
/*    40824:	014bc021 */ 	addu	$t8,$t2,$t3
/*    40828:	01394021 */ 	addu	$t0,$t1,$t9
/*    4082c:	c5060000 */ 	lwc1	$f6,0x0($t0)
/*    40830:	c7100000 */ 	lwc1	$f16,0x0($t8)
/*    40834:	8fad0040 */ 	lw	$t5,0x40($sp)
/*    40838:	46103282 */ 	mul.s	$f10,$f6,$f16
/*    4083c:	46005207 */ 	neg.s	$f8,$f10
/*    40840:	e5a80000 */ 	swc1	$f8,0x0($t5)
/*    40844:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*    40848:	8fac0040 */ 	lw	$t4,0x40($sp)
/*    4084c:	27280002 */ 	addiu	$t0,$t9,0x2
/*    40850:	25890004 */ 	addiu	$t1,$t4,0x4
/*    40854:	afa90040 */ 	sw	$t1,0x40($sp)
/*    40858:	10000016 */ 	b	.L000408b4
/*    4085c:	afa8003c */ 	sw	$t0,0x3c($sp)
.L00040860:
/*    40860:	8fad003c */ 	lw	$t5,0x3c($sp)
/*    40864:	8faf005c */ 	lw	$t7,0x5c($sp)
/*    40868:	3c18800a */ 	lui	$t8,%hi(var8009c648)
/*    4086c:	85ac0000 */ 	lh	$t4,0x0($t5)
/*    40870:	8f18c648 */ 	lw	$t8,%lo(var8009c648)($t8)
/*    40874:	8fae0024 */ 	lw	$t6,0x24($sp)
/*    40878:	000f5080 */ 	sll	$t2,$t7,0x2
/*    4087c:	000c4880 */ 	sll	$t1,$t4,0x2
/*    40880:	0309c821 */ 	addu	$t9,$t8,$t1
/*    40884:	01ca5821 */ 	addu	$t3,$t6,$t2
/*    40888:	c5720000 */ 	lwc1	$f18,0x0($t3)
/*    4088c:	c7240000 */ 	lwc1	$f4,0x0($t9)
/*    40890:	8fa80040 */ 	lw	$t0,0x40($sp)
/*    40894:	46049182 */ 	mul.s	$f6,$f18,$f4
/*    40898:	e5060000 */ 	swc1	$f6,0x0($t0)
/*    4089c:	8faa003c */ 	lw	$t2,0x3c($sp)
/*    408a0:	8faf0040 */ 	lw	$t7,0x40($sp)
/*    408a4:	254b0002 */ 	addiu	$t3,$t2,0x2
/*    408a8:	25ee0004 */ 	addiu	$t6,$t7,0x4
/*    408ac:	afae0040 */ 	sw	$t6,0x40($sp)
/*    408b0:	afab003c */ 	sw	$t3,0x3c($sp)
.L000408b4:
/*    408b4:	10000031 */ 	b	.L0004097c
/*    408b8:	00000000 */ 	nop
.L000408bc:
/*    408bc:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    408c0:	91b00000 */ 	lbu	$s0,0x0($t5)
/*    408c4:	25ac0001 */ 	addiu	$t4,$t5,0x1
/*    408c8:	afac0038 */ 	sw	$t4,0x38($sp)
/*    408cc:	12000017 */ 	beqz	$s0,.L0004092c
/*    408d0:	00000000 */ 	nop
/*    408d4:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*    408d8:	8fae005c */ 	lw	$t6,0x5c($sp)
/*    408dc:	3c18800a */ 	lui	$t8,%hi(var8009c648)
/*    408e0:	85390000 */ 	lh	$t9,0x0($t1)
/*    408e4:	8f18c648 */ 	lw	$t8,%lo(var8009c648)($t8)
/*    408e8:	000e5080 */ 	sll	$t2,$t6,0x2
/*    408ec:	00194080 */ 	sll	$t0,$t9,0x2
/*    408f0:	03aa5821 */ 	addu	$t3,$sp,$t2
/*    408f4:	03087821 */ 	addu	$t7,$t8,$t0
/*    408f8:	c5f00000 */ 	lwc1	$f16,0x0($t7)
/*    408fc:	c56a0100 */ 	lwc1	$f10,0x100($t3)
/*    40900:	8fad0040 */ 	lw	$t5,0x40($sp)
/*    40904:	46105202 */ 	mul.s	$f8,$f10,$f16
/*    40908:	46004487 */ 	neg.s	$f18,$f8
/*    4090c:	e5b20000 */ 	swc1	$f18,0x0($t5)
/*    40910:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*    40914:	8fac0040 */ 	lw	$t4,0x40($sp)
/*    40918:	27380002 */ 	addiu	$t8,$t9,0x2
/*    4091c:	25890004 */ 	addiu	$t1,$t4,0x4
/*    40920:	afa90040 */ 	sw	$t1,0x40($sp)
/*    40924:	10000015 */ 	b	.L0004097c
/*    40928:	afb8003c */ 	sw	$t8,0x3c($sp)
.L0004092c:
/*    4092c:	8faf003c */ 	lw	$t7,0x3c($sp)
/*    40930:	8fad005c */ 	lw	$t5,0x5c($sp)
/*    40934:	3c08800a */ 	lui	$t0,%hi(var8009c648)
/*    40938:	85ee0000 */ 	lh	$t6,0x0($t7)
/*    4093c:	8d08c648 */ 	lw	$t0,%lo(var8009c648)($t0)
/*    40940:	000d6080 */ 	sll	$t4,$t5,0x2
/*    40944:	000e5080 */ 	sll	$t2,$t6,0x2
/*    40948:	03ac4821 */ 	addu	$t1,$sp,$t4
/*    4094c:	010a5821 */ 	addu	$t3,$t0,$t2
/*    40950:	c5640000 */ 	lwc1	$f4,0x0($t3)
/*    40954:	c5260100 */ 	lwc1	$f6,0x100($t1)
/*    40958:	8fb90040 */ 	lw	$t9,0x40($sp)
/*    4095c:	46043282 */ 	mul.s	$f10,$f6,$f4
/*    40960:	e72a0000 */ 	swc1	$f10,0x0($t9)
/*    40964:	8fae003c */ 	lw	$t6,0x3c($sp)
/*    40968:	8fb80040 */ 	lw	$t8,0x40($sp)
/*    4096c:	25c80002 */ 	addiu	$t0,$t6,0x2
/*    40970:	270f0004 */ 	addiu	$t7,$t8,0x4
/*    40974:	afaf0040 */ 	sw	$t7,0x40($sp)
/*    40978:	afa8003c */ 	sw	$t0,0x3c($sp)
.L0004097c:
/*    4097c:	8faa0048 */ 	lw	$t2,0x48($sp)
/*    40980:	254b0001 */ 	addiu	$t3,$t2,0x1
/*    40984:	afab0048 */ 	sw	$t3,0x48($sp)
/*    40988:	8fad0048 */ 	lw	$t5,0x48($sp)
/*    4098c:	8fac01b8 */ 	lw	$t4,0x1b8($sp)
/*    40990:	01ac082a */ 	slt	$at,$t5,$t4
/*    40994:	1420ff73 */ 	bnez	$at,.L00040764
/*    40998:	00000000 */ 	nop
.L0004099c:
/*    4099c:	8fb901c4 */ 	lw	$t9,0x1c4($sp)
/*    409a0:	8fa901c0 */ 	lw	$t1,0x1c0($sp)
/*    409a4:	8fae01c8 */ 	lw	$t6,0x1c8($sp)
/*    409a8:	0019c080 */ 	sll	$t8,$t9,0x2
/*    409ac:	01387821 */ 	addu	$t7,$t1,$t8
/*    409b0:	000e4080 */ 	sll	$t0,$t6,0x2
/*    409b4:	01e85021 */ 	addu	$t2,$t7,$t0
/*    409b8:	8d4b3c98 */ 	lw	$t3,0x3c98($t2)
/*    409bc:	116000d0 */ 	beqz	$t3,.L00040d00
/*    409c0:	00000000 */ 	nop
/*    409c4:	8d4d3ca0 */ 	lw	$t5,0x3ca0($t2)
/*    409c8:	24010002 */ 	addiu	$at,$zero,0x2
/*    409cc:	15a100cc */ 	bne	$t5,$at,.L00040d00
/*    409d0:	00000000 */ 	nop
/*    409d4:	8fb901c4 */ 	lw	$t9,0x1c4($sp)
/*    409d8:	8fac01c0 */ 	lw	$t4,0x1c0($sp)
/*    409dc:	8fae01c8 */ 	lw	$t6,0x1c8($sp)
/*    409e0:	00194880 */ 	sll	$t1,$t9,0x2
/*    409e4:	0189c021 */ 	addu	$t8,$t4,$t1
/*    409e8:	000e7880 */ 	sll	$t7,$t6,0x2
/*    409ec:	030f4021 */ 	addu	$t0,$t8,$t7
/*    409f0:	8d0b3ca8 */ 	lw	$t3,0x3ca8($t0)
/*    409f4:	1160008e */ 	beqz	$t3,.L00040c30
/*    409f8:	00000000 */ 	nop
/*    409fc:	8faa01bc */ 	lw	$t2,0x1bc($sp)
/*    40a00:	3c197005 */ 	lui	$t9,%hi(var700579c8)
/*    40a04:	8fac0048 */ 	lw	$t4,0x48($sp)
/*    40a08:	000a68c0 */ 	sll	$t5,$t2,0x3
/*    40a0c:	01aa6821 */ 	addu	$t5,$t5,$t2
/*    40a10:	000d6880 */ 	sll	$t5,$t5,0x2
/*    40a14:	01aa6821 */ 	addu	$t5,$t5,$t2
/*    40a18:	000d6840 */ 	sll	$t5,$t5,0x1
/*    40a1c:	032dc821 */ 	addu	$t9,$t9,$t5
/*    40a20:	873979c8 */ 	lh	$t9,%lo(var700579c8)($t9)
/*    40a24:	172c0031 */ 	bne	$t9,$t4,.L00040aec
/*    40a28:	00000000 */ 	nop
/*    40a2c:	8fa901bc */ 	lw	$t1,0x1bc($sp)
/*    40a30:	3c187005 */ 	lui	$t8,%hi(var700579ec+0x2)
/*    40a34:	000970c0 */ 	sll	$t6,$t1,0x3
/*    40a38:	01c97021 */ 	addu	$t6,$t6,$t1
/*    40a3c:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40a40:	01c97021 */ 	addu	$t6,$t6,$t1
/*    40a44:	000e7040 */ 	sll	$t6,$t6,0x1
/*    40a48:	030ec021 */ 	addu	$t8,$t8,$t6
/*    40a4c:	871879ee */ 	lh	$t8,%lo(var700579ec+0x2)($t8)
/*    40a50:	00187880 */ 	sll	$t7,$t8,0x2
/*    40a54:	01f87823 */ 	subu	$t7,$t7,$t8
/*    40a58:	afaf01b8 */ 	sw	$t7,0x1b8($sp)
/*    40a5c:	24080003 */ 	addiu	$t0,$zero,0x3
/*    40a60:	afa8005c */ 	sw	$t0,0x5c($sp)
/*    40a64:	8fab01bc */ 	lw	$t3,0x1bc($sp)
/*    40a68:	8fad005c */ 	lw	$t5,0x5c($sp)
/*    40a6c:	3c097005 */ 	lui	$t1,%hi(var700579b8)
/*    40a70:	000b50c0 */ 	sll	$t2,$t3,0x3
/*    40a74:	014b5021 */ 	addu	$t2,$t2,$t3
/*    40a78:	000a5080 */ 	sll	$t2,$t2,0x2
/*    40a7c:	014b5021 */ 	addu	$t2,$t2,$t3
/*    40a80:	000a5040 */ 	sll	$t2,$t2,0x1
/*    40a84:	000dc840 */ 	sll	$t9,$t5,0x1
/*    40a88:	252979b8 */ 	addiu	$t1,$t1,%lo(var700579b8)
/*    40a8c:	01596021 */ 	addu	$t4,$t2,$t9
/*    40a90:	01597821 */ 	addu	$t7,$t2,$t9
/*    40a94:	01e94021 */ 	addu	$t0,$t7,$t1
/*    40a98:	01897021 */ 	addu	$t6,$t4,$t1
/*    40a9c:	85d80030 */ 	lh	$t8,0x30($t6)
/*    40aa0:	850b002e */ 	lh	$t3,0x2e($t0)
/*    40aa4:	030b6823 */ 	subu	$t5,$t8,$t3
/*    40aa8:	afad01b0 */ 	sw	$t5,0x1b0($sp)
/*    40aac:	8fac01bc */ 	lw	$t4,0x1bc($sp)
/*    40ab0:	8faa005c */ 	lw	$t2,0x5c($sp)
/*    40ab4:	3c097005 */ 	lui	$t1,%hi(var700579e4+0x2)
/*    40ab8:	000c70c0 */ 	sll	$t6,$t4,0x3
/*    40abc:	01cc7021 */ 	addu	$t6,$t6,$t4
/*    40ac0:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40ac4:	01cc7021 */ 	addu	$t6,$t6,$t4
/*    40ac8:	000e7040 */ 	sll	$t6,$t6,0x1
/*    40acc:	000ac840 */ 	sll	$t9,$t2,0x1
/*    40ad0:	01d97821 */ 	addu	$t7,$t6,$t9
/*    40ad4:	012f4821 */ 	addu	$t1,$t1,$t7
/*    40ad8:	852979e6 */ 	lh	$t1,%lo(var700579e4+0x2)($t1)
/*    40adc:	00094080 */ 	sll	$t0,$t1,0x2
/*    40ae0:	01094023 */ 	subu	$t0,$t0,$t1
/*    40ae4:	10000050 */ 	b	.L00040c28
/*    40ae8:	afa801b4 */ 	sw	$t0,0x1b4($sp)
.L00040aec:
/*    40aec:	8fab01bc */ 	lw	$t3,0x1bc($sp)
/*    40af0:	3c0c7005 */ 	lui	$t4,%hi(var700579c8)
/*    40af4:	8fb80048 */ 	lw	$t8,0x48($sp)
/*    40af8:	000b68c0 */ 	sll	$t5,$t3,0x3
/*    40afc:	01ab6821 */ 	addu	$t5,$t5,$t3
/*    40b00:	000d6880 */ 	sll	$t5,$t5,0x2
/*    40b04:	01ab6821 */ 	addu	$t5,$t5,$t3
/*    40b08:	000d6840 */ 	sll	$t5,$t5,0x1
/*    40b0c:	018d6021 */ 	addu	$t4,$t4,$t5
/*    40b10:	858c79c8 */ 	lh	$t4,%lo(var700579c8)($t4)
/*    40b14:	030c082a */ 	slt	$at,$t8,$t4
/*    40b18:	10200011 */ 	beqz	$at,.L00040b60
/*    40b1c:	00000000 */ 	nop
/*    40b20:	8faa01bc */ 	lw	$t2,0x1bc($sp)
/*    40b24:	8fb0005c */ 	lw	$s0,0x5c($sp)
/*    40b28:	3c097005 */ 	lui	$t1,%hi(var700579b8+0x2)
/*    40b2c:	000a70c0 */ 	sll	$t6,$t2,0x3
/*    40b30:	01ca7021 */ 	addu	$t6,$t6,$t2
/*    40b34:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40b38:	01ca7021 */ 	addu	$t6,$t6,$t2
/*    40b3c:	26100001 */ 	addiu	$s0,$s0,0x1
/*    40b40:	0010c840 */ 	sll	$t9,$s0,0x1
/*    40b44:	000e7040 */ 	sll	$t6,$t6,0x1
/*    40b48:	01d97821 */ 	addu	$t7,$t6,$t9
/*    40b4c:	012f4821 */ 	addu	$t1,$t1,$t7
/*    40b50:	852979ba */ 	lh	$t1,%lo(var700579b8+0x2)($t1)
/*    40b54:	afb0005c */ 	sw	$s0,0x5c($sp)
/*    40b58:	10000033 */ 	b	.L00040c28
/*    40b5c:	afa901b8 */ 	sw	$t1,0x1b8($sp)
.L00040b60:
/*    40b60:	8fa801bc */ 	lw	$t0,0x1bc($sp)
/*    40b64:	8fb0005c */ 	lw	$s0,0x5c($sp)
/*    40b68:	3c0c7005 */ 	lui	$t4,%hi(var700579e8)
/*    40b6c:	000858c0 */ 	sll	$t3,$t0,0x3
/*    40b70:	01685821 */ 	addu	$t3,$t3,$t0
/*    40b74:	000b5880 */ 	sll	$t3,$t3,0x2
/*    40b78:	01685821 */ 	addu	$t3,$t3,$t0
/*    40b7c:	26100001 */ 	addiu	$s0,$s0,0x1
/*    40b80:	00106840 */ 	sll	$t5,$s0,0x1
/*    40b84:	000b5840 */ 	sll	$t3,$t3,0x1
/*    40b88:	016dc021 */ 	addu	$t8,$t3,$t5
/*    40b8c:	01986021 */ 	addu	$t4,$t4,$t8
/*    40b90:	858c79e8 */ 	lh	$t4,%lo(var700579e8)($t4)
/*    40b94:	afb0005c */ 	sw	$s0,0x5c($sp)
/*    40b98:	000c5080 */ 	sll	$t2,$t4,0x2
/*    40b9c:	014c5023 */ 	subu	$t2,$t2,$t4
/*    40ba0:	afaa01b8 */ 	sw	$t2,0x1b8($sp)
/*    40ba4:	8fae01bc */ 	lw	$t6,0x1bc($sp)
/*    40ba8:	8faf005c */ 	lw	$t7,0x5c($sp)
/*    40bac:	3c0b7005 */ 	lui	$t3,%hi(var700579b8)
/*    40bb0:	000ec8c0 */ 	sll	$t9,$t6,0x3
/*    40bb4:	032ec821 */ 	addu	$t9,$t9,$t6
/*    40bb8:	0019c880 */ 	sll	$t9,$t9,0x2
/*    40bbc:	032ec821 */ 	addu	$t9,$t9,$t6
/*    40bc0:	0019c840 */ 	sll	$t9,$t9,0x1
/*    40bc4:	000f4840 */ 	sll	$t1,$t7,0x1
/*    40bc8:	256b79b8 */ 	addiu	$t3,$t3,%lo(var700579b8)
/*    40bcc:	03294021 */ 	addu	$t0,$t9,$t1
/*    40bd0:	03296021 */ 	addu	$t4,$t9,$t1
/*    40bd4:	018b5021 */ 	addu	$t2,$t4,$t3
/*    40bd8:	010b6821 */ 	addu	$t5,$t0,$t3
/*    40bdc:	85b80030 */ 	lh	$t8,0x30($t5)
/*    40be0:	854e002e */ 	lh	$t6,0x2e($t2)
/*    40be4:	030e7823 */ 	subu	$t7,$t8,$t6
/*    40be8:	afaf01b0 */ 	sw	$t7,0x1b0($sp)
/*    40bec:	8fa801bc */ 	lw	$t0,0x1bc($sp)
/*    40bf0:	8fb9005c */ 	lw	$t9,0x5c($sp)
/*    40bf4:	3c0b7005 */ 	lui	$t3,%hi(var700579e4+0x2)
/*    40bf8:	000868c0 */ 	sll	$t5,$t0,0x3
/*    40bfc:	01a86821 */ 	addu	$t5,$t5,$t0
/*    40c00:	000d6880 */ 	sll	$t5,$t5,0x2
/*    40c04:	01a86821 */ 	addu	$t5,$t5,$t0
/*    40c08:	000d6840 */ 	sll	$t5,$t5,0x1
/*    40c0c:	00194840 */ 	sll	$t1,$t9,0x1
/*    40c10:	01a96021 */ 	addu	$t4,$t5,$t1
/*    40c14:	016c5821 */ 	addu	$t3,$t3,$t4
/*    40c18:	856b79e6 */ 	lh	$t3,%lo(var700579e4+0x2)($t3)
/*    40c1c:	000b5080 */ 	sll	$t2,$t3,0x2
/*    40c20:	014b5023 */ 	subu	$t2,$t2,$t3
/*    40c24:	afaa01b4 */ 	sw	$t2,0x1b4($sp)
.L00040c28:
/*    40c28:	10000033 */ 	b	.L00040cf8
/*    40c2c:	00000000 */ 	nop
.L00040c30:
/*    40c30:	8fb801bc */ 	lw	$t8,0x1bc($sp)
/*    40c34:	8fb0005c */ 	lw	$s0,0x5c($sp)
/*    40c38:	3c197005 */ 	lui	$t9,%hi(var700579e8)
/*    40c3c:	001870c0 */ 	sll	$t6,$t8,0x3
/*    40c40:	01d87021 */ 	addu	$t6,$t6,$t8
/*    40c44:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40c48:	01d87021 */ 	addu	$t6,$t6,$t8
/*    40c4c:	26100001 */ 	addiu	$s0,$s0,0x1
/*    40c50:	00107840 */ 	sll	$t7,$s0,0x1
/*    40c54:	000e7040 */ 	sll	$t6,$t6,0x1
/*    40c58:	01cf4021 */ 	addu	$t0,$t6,$t7
/*    40c5c:	0328c821 */ 	addu	$t9,$t9,$t0
/*    40c60:	873979e8 */ 	lh	$t9,%lo(var700579e8)($t9)
/*    40c64:	afb0005c */ 	sw	$s0,0x5c($sp)
/*    40c68:	00196880 */ 	sll	$t5,$t9,0x2
/*    40c6c:	01b96823 */ 	subu	$t5,$t5,$t9
/*    40c70:	afad01b8 */ 	sw	$t5,0x1b8($sp)
/*    40c74:	8fa901bc */ 	lw	$t1,0x1bc($sp)
/*    40c78:	8fab005c */ 	lw	$t3,0x5c($sp)
/*    40c7c:	3c0e7005 */ 	lui	$t6,%hi(var700579b8)
/*    40c80:	000960c0 */ 	sll	$t4,$t1,0x3
/*    40c84:	01896021 */ 	addu	$t4,$t4,$t1
/*    40c88:	000c6080 */ 	sll	$t4,$t4,0x2
/*    40c8c:	01896021 */ 	addu	$t4,$t4,$t1
/*    40c90:	000c6040 */ 	sll	$t4,$t4,0x1
/*    40c94:	000b5040 */ 	sll	$t2,$t3,0x1
/*    40c98:	25ce79b8 */ 	addiu	$t6,$t6,%lo(var700579b8)
/*    40c9c:	018ac021 */ 	addu	$t8,$t4,$t2
/*    40ca0:	018ac821 */ 	addu	$t9,$t4,$t2
/*    40ca4:	032e6821 */ 	addu	$t5,$t9,$t6
/*    40ca8:	030e7821 */ 	addu	$t7,$t8,$t6
/*    40cac:	85e80030 */ 	lh	$t0,0x30($t7)
/*    40cb0:	85a9002e */ 	lh	$t1,0x2e($t5)
/*    40cb4:	01095823 */ 	subu	$t3,$t0,$t1
/*    40cb8:	afab01b0 */ 	sw	$t3,0x1b0($sp)
/*    40cbc:	8fb801bc */ 	lw	$t8,0x1bc($sp)
/*    40cc0:	8fac005c */ 	lw	$t4,0x5c($sp)
/*    40cc4:	3c0e7005 */ 	lui	$t6,%hi(var700579e4+0x2)
/*    40cc8:	001878c0 */ 	sll	$t7,$t8,0x3
/*    40ccc:	01f87821 */ 	addu	$t7,$t7,$t8
/*    40cd0:	000f7880 */ 	sll	$t7,$t7,0x2
/*    40cd4:	01f87821 */ 	addu	$t7,$t7,$t8
/*    40cd8:	000f7840 */ 	sll	$t7,$t7,0x1
/*    40cdc:	000c5040 */ 	sll	$t2,$t4,0x1
/*    40ce0:	01eac821 */ 	addu	$t9,$t7,$t2
/*    40ce4:	01d97021 */ 	addu	$t6,$t6,$t9
/*    40ce8:	85ce79e6 */ 	lh	$t6,%lo(var700579e4+0x2)($t6)
/*    40cec:	000e6880 */ 	sll	$t5,$t6,0x2
/*    40cf0:	01ae6823 */ 	subu	$t5,$t5,$t6
/*    40cf4:	afad01b4 */ 	sw	$t5,0x1b4($sp)
.L00040cf8:
/*    40cf8:	10000010 */ 	b	.L00040d3c
/*    40cfc:	00000000 */ 	nop
.L00040d00:
/*    40d00:	8fa801bc */ 	lw	$t0,0x1bc($sp)
/*    40d04:	8fb0005c */ 	lw	$s0,0x5c($sp)
/*    40d08:	3c0c7005 */ 	lui	$t4,%hi(var700579b8+0x2)
/*    40d0c:	000848c0 */ 	sll	$t1,$t0,0x3
/*    40d10:	01284821 */ 	addu	$t1,$t1,$t0
/*    40d14:	00094880 */ 	sll	$t1,$t1,0x2
/*    40d18:	01284821 */ 	addu	$t1,$t1,$t0
/*    40d1c:	26100001 */ 	addiu	$s0,$s0,0x1
/*    40d20:	00105840 */ 	sll	$t3,$s0,0x1
/*    40d24:	00094840 */ 	sll	$t1,$t1,0x1
/*    40d28:	012bc021 */ 	addu	$t8,$t1,$t3
/*    40d2c:	01986021 */ 	addu	$t4,$t4,$t8
/*    40d30:	858c79ba */ 	lh	$t4,%lo(var700579b8+0x2)($t4)
/*    40d34:	afb0005c */ 	sw	$s0,0x5c($sp)
/*    40d38:	afac01b8 */ 	sw	$t4,0x1b8($sp)
.L00040d3c:
/*    40d3c:	8faf0048 */ 	lw	$t7,0x48($sp)
/*    40d40:	8faa0044 */ 	lw	$t2,0x44($sp)
/*    40d44:	01ea082a */ 	slt	$at,$t7,$t2
/*    40d48:	1420fe59 */ 	bnez	$at,.L000406b0
/*    40d4c:	00000000 */ 	nop
.L00040d50:
/*    40d50:	8fb90048 */ 	lw	$t9,0x48($sp)
/*    40d54:	2b210240 */ 	slti	$at,$t9,0x240
/*    40d58:	1020000b */ 	beqz	$at,.L00040d88
/*    40d5c:	00000000 */ 	nop
/*    40d60:	8fad01c8 */ 	lw	$t5,0x1c8($sp)
/*    40d64:	8fae01c0 */ 	lw	$t6,0x1c0($sp)
/*    40d68:	8fa40040 */ 	lw	$a0,0x40($sp)
/*    40d6c:	000d4080 */ 	sll	$t0,$t5,0x2
/*    40d70:	01c84821 */ 	addu	$t1,$t6,$t0
/*    40d74:	8d254660 */ 	lw	$a1,0x4660($t1)
/*    40d78:	0c012c30 */ 	jal	bzero
/*    40d7c:	00052880 */ 	sll	$a1,$a1,0x2
/*    40d80:	10000005 */ 	b	.L00040d98
/*    40d84:	24020001 */ 	addiu	$v0,$zero,0x1
.L00040d88:
/*    40d88:	10000003 */ 	b	.L00040d98
/*    40d8c:	24020001 */ 	addiu	$v0,$zero,0x1
/*    40d90:	10000001 */ 	b	.L00040d98
/*    40d94:	00000000 */ 	nop
.L00040d98:
/*    40d98:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*    40d9c:	8fb00018 */ 	lw	$s0,0x18($sp)
/*    40da0:	27bd01c0 */ 	addiu	$sp,$sp,0x1c0
/*    40da4:	03e00008 */ 	jr	$ra
/*    40da8:	00000000 */ 	nop
);

GLOBAL_ASM(
glabel func00040dac
/*    40dac:	27bdffc8 */ 	addiu	$sp,$sp,-56
/*    40db0:	afbf001c */ 	sw	$ra,0x1c($sp)
/*    40db4:	afa40038 */ 	sw	$a0,0x38($sp)
/*    40db8:	afa5003c */ 	sw	$a1,0x3c($sp)
/*    40dbc:	afa60040 */ 	sw	$a2,0x40($sp)
/*    40dc0:	afb10018 */ 	sw	$s1,0x18($sp)
/*    40dc4:	afb00014 */ 	sw	$s0,0x14($sp)
/*    40dc8:	8faf003c */ 	lw	$t7,0x3c($sp)
/*    40dcc:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    40dd0:	8fa80040 */ 	lw	$t0,0x40($sp)
/*    40dd4:	000fc080 */ 	sll	$t8,$t7,0x2
/*    40dd8:	01d8c821 */ 	addu	$t9,$t6,$t8
/*    40ddc:	00084880 */ 	sll	$t1,$t0,0x2
/*    40de0:	03295021 */ 	addu	$t2,$t9,$t1
/*    40de4:	8d4b3c98 */ 	lw	$t3,0x3c98($t2)
/*    40de8:	1160015c */ 	beqz	$t3,.L0004135c
/*    40dec:	00000000 */ 	nop
/*    40df0:	8d4c3ca0 */ 	lw	$t4,0x3ca0($t2)
/*    40df4:	24010002 */ 	addiu	$at,$zero,0x2
/*    40df8:	15810158 */ 	bne	$t4,$at,.L0004135c
/*    40dfc:	00000000 */ 	nop
/*    40e00:	8faf003c */ 	lw	$t7,0x3c($sp)
/*    40e04:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    40e08:	8fa80040 */ 	lw	$t0,0x40($sp)
/*    40e0c:	000f7080 */ 	sll	$t6,$t7,0x2
/*    40e10:	01aec021 */ 	addu	$t8,$t5,$t6
/*    40e14:	0008c880 */ 	sll	$t9,$t0,0x2
/*    40e18:	03194821 */ 	addu	$t1,$t8,$t9
/*    40e1c:	8d2b3ca8 */ 	lw	$t3,0x3ca8($t1)
/*    40e20:	116000cf */ 	beqz	$t3,.L00041160
/*    40e24:	00000000 */ 	nop
/*    40e28:	afa00030 */ 	sw	$zero,0x30($sp)
.L00040e2c:
/*    40e2c:	8fac003c */ 	lw	$t4,0x3c($sp)
/*    40e30:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    40e34:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    40e38:	000c7880 */ 	sll	$t7,$t4,0x2
/*    40e3c:	014f6821 */ 	addu	$t5,$t2,$t7
/*    40e40:	000e4080 */ 	sll	$t0,$t6,0x2
/*    40e44:	01a8c021 */ 	addu	$t8,$t5,$t0
/*    40e48:	8f193c90 */ 	lw	$t9,0x3c90($t8)
/*    40e4c:	3c097005 */ 	lui	$t1,%hi(var70057b7c)
/*    40e50:	01394821 */ 	addu	$t1,$t1,$t9
/*    40e54:	91297b7c */ 	lbu	$t1,%lo(var70057b7c)($t1)
/*    40e58:	11200015 */ 	beqz	$t1,.L00040eb0
/*    40e5c:	00000000 */ 	nop
/*    40e60:	2544001c */ 	addiu	$a0,$t2,0x1c
/*    40e64:	25452020 */ 	addiu	$a1,$t2,0x2020
/*    40e68:	0c0118b1 */ 	jal	func000462c4
/*    40e6c:	01203025 */ 	or	$a2,$t1,$zero
/*    40e70:	8fac003c */ 	lw	$t4,0x3c($sp)
/*    40e74:	8fad0040 */ 	lw	$t5,0x40($sp)
/*    40e78:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    40e7c:	000c7940 */ 	sll	$t7,$t4,0x5
/*    40e80:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    40e84:	01ec7823 */ 	subu	$t7,$t7,$t4
/*    40e88:	000d4140 */ 	sll	$t0,$t5,0x5
/*    40e8c:	000f78c0 */ 	sll	$t7,$t7,0x3
/*    40e90:	010d4023 */ 	subu	$t0,$t0,$t5
/*    40e94:	000840c0 */ 	sll	$t0,$t0,0x3
/*    40e98:	016f7021 */ 	addu	$t6,$t3,$t7
/*    40e9c:	01c8c021 */ 	addu	$t8,$t6,$t0
/*    40ea0:	00195080 */ 	sll	$t2,$t9,0x2
/*    40ea4:	030a4821 */ 	addu	$t1,$t8,$t2
/*    40ea8:	10000010 */ 	b	.L00040eec
/*    40eac:	ad223d08 */ 	sw	$v0,0x3d08($t1)
.L00040eb0:
/*    40eb0:	8fab003c */ 	lw	$t3,0x3c($sp)
/*    40eb4:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    40eb8:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    40ebc:	000b7940 */ 	sll	$t7,$t3,0x5
/*    40ec0:	8fb80030 */ 	lw	$t8,0x30($sp)
/*    40ec4:	01eb7823 */ 	subu	$t7,$t7,$t3
/*    40ec8:	000e4140 */ 	sll	$t0,$t6,0x5
/*    40ecc:	000f78c0 */ 	sll	$t7,$t7,0x3
/*    40ed0:	010e4023 */ 	subu	$t0,$t0,$t6
/*    40ed4:	000840c0 */ 	sll	$t0,$t0,0x3
/*    40ed8:	018f6821 */ 	addu	$t5,$t4,$t7
/*    40edc:	01a8c821 */ 	addu	$t9,$t5,$t0
/*    40ee0:	00185080 */ 	sll	$t2,$t8,0x2
/*    40ee4:	032a4821 */ 	addu	$t1,$t9,$t2
/*    40ee8:	ad203d08 */ 	sw	$zero,0x3d08($t1)
.L00040eec:
/*    40eec:	8fab0030 */ 	lw	$t3,0x30($sp)
/*    40ef0:	256c0001 */ 	addiu	$t4,$t3,0x1
/*    40ef4:	29810008 */ 	slti	$at,$t4,0x8
/*    40ef8:	1420ffcc */ 	bnez	$at,.L00040e2c
/*    40efc:	afac0030 */ 	sw	$t4,0x30($sp)
/*    40f00:	240f0003 */ 	addiu	$t7,$zero,0x3
/*    40f04:	afaf0030 */ 	sw	$t7,0x30($sp)
.L00040f08:
/*    40f08:	afa0002c */ 	sw	$zero,0x2c($sp)
.L00040f0c:
/*    40f0c:	8fad003c */ 	lw	$t5,0x3c($sp)
/*    40f10:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    40f14:	8fb90040 */ 	lw	$t9,0x40($sp)
/*    40f18:	000d4080 */ 	sll	$t0,$t5,0x2
/*    40f1c:	01c8c021 */ 	addu	$t8,$t6,$t0
/*    40f20:	00195080 */ 	sll	$t2,$t9,0x2
/*    40f24:	030a4821 */ 	addu	$t1,$t8,$t2
/*    40f28:	8d2b3c90 */ 	lw	$t3,0x3c90($t1)
/*    40f2c:	3c0c7005 */ 	lui	$t4,%hi(var70057b7c)
/*    40f30:	018b6021 */ 	addu	$t4,$t4,$t3
/*    40f34:	918c7b7c */ 	lbu	$t4,%lo(var70057b7c)($t4)
/*    40f38:	1180001c */ 	beqz	$t4,.L00040fac
/*    40f3c:	00000000 */ 	nop
/*    40f40:	25c4001c */ 	addiu	$a0,$t6,0x1c
/*    40f44:	25c52020 */ 	addiu	$a1,$t6,0x2020
/*    40f48:	0c0118b1 */ 	jal	func000462c4
/*    40f4c:	01803025 */ 	or	$a2,$t4,$zero
/*    40f50:	8fad003c */ 	lw	$t5,0x3c($sp)
/*    40f54:	8fab002c */ 	lw	$t3,0x2c($sp)
/*    40f58:	8fb80040 */ 	lw	$t8,0x40($sp)
/*    40f5c:	000d4140 */ 	sll	$t0,$t5,0x5
/*    40f60:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    40f64:	010d4023 */ 	subu	$t0,$t0,$t5
/*    40f68:	000b7080 */ 	sll	$t6,$t3,0x2
/*    40f6c:	01cb7023 */ 	subu	$t6,$t6,$t3
/*    40f70:	00185140 */ 	sll	$t2,$t8,0x5
/*    40f74:	8fad0030 */ 	lw	$t5,0x30($sp)
/*    40f78:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40f7c:	000840c0 */ 	sll	$t0,$t0,0x3
/*    40f80:	01585023 */ 	subu	$t2,$t2,$t8
/*    40f84:	000a50c0 */ 	sll	$t2,$t2,0x3
/*    40f88:	01cb7021 */ 	addu	$t6,$t6,$t3
/*    40f8c:	01e8c821 */ 	addu	$t9,$t7,$t0
/*    40f90:	032a4821 */ 	addu	$t1,$t9,$t2
/*    40f94:	000e7080 */ 	sll	$t6,$t6,0x2
/*    40f98:	012e6021 */ 	addu	$t4,$t1,$t6
/*    40f9c:	000d7880 */ 	sll	$t7,$t5,0x2
/*    40fa0:	018f4021 */ 	addu	$t0,$t4,$t7
/*    40fa4:	10000017 */ 	b	.L00041004
/*    40fa8:	ad023d64 */ 	sw	$v0,0x3d64($t0)
.L00040fac:
/*    40fac:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*    40fb0:	8fac002c */ 	lw	$t4,0x2c($sp)
/*    40fb4:	8fa90040 */ 	lw	$t1,0x40($sp)
/*    40fb8:	00195140 */ 	sll	$t2,$t9,0x5
/*    40fbc:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    40fc0:	01595023 */ 	subu	$t2,$t2,$t9
/*    40fc4:	000c7880 */ 	sll	$t7,$t4,0x2
/*    40fc8:	01ec7823 */ 	subu	$t7,$t7,$t4
/*    40fcc:	00097140 */ 	sll	$t6,$t1,0x5
/*    40fd0:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    40fd4:	000f7880 */ 	sll	$t7,$t7,0x2
/*    40fd8:	000a50c0 */ 	sll	$t2,$t2,0x3
/*    40fdc:	01c97023 */ 	subu	$t6,$t6,$t1
/*    40fe0:	000e70c0 */ 	sll	$t6,$t6,0x3
/*    40fe4:	01ec7821 */ 	addu	$t7,$t7,$t4
/*    40fe8:	030a5821 */ 	addu	$t3,$t8,$t2
/*    40fec:	016e6821 */ 	addu	$t5,$t3,$t6
/*    40ff0:	000f7880 */ 	sll	$t7,$t7,0x2
/*    40ff4:	01af4021 */ 	addu	$t0,$t5,$t7
/*    40ff8:	0019c080 */ 	sll	$t8,$t9,0x2
/*    40ffc:	01185021 */ 	addu	$t2,$t0,$t8
/*    41000:	ad403d64 */ 	sw	$zero,0x3d64($t2)
.L00041004:
/*    41004:	8fa9002c */ 	lw	$t1,0x2c($sp)
/*    41008:	252b0001 */ 	addiu	$t3,$t1,0x1
/*    4100c:	29610003 */ 	slti	$at,$t3,0x3
/*    41010:	1420ffbe */ 	bnez	$at,.L00040f0c
/*    41014:	afab002c */ 	sw	$t3,0x2c($sp)
/*    41018:	8fae0030 */ 	lw	$t6,0x30($sp)
/*    4101c:	25cc0001 */ 	addiu	$t4,$t6,0x1
/*    41020:	29810006 */ 	slti	$at,$t4,0x6
/*    41024:	1420ffb8 */ 	bnez	$at,.L00040f08
/*    41028:	afac0030 */ 	sw	$t4,0x30($sp)
/*    4102c:	240d0006 */ 	addiu	$t5,$zero,0x6
/*    41030:	afad0030 */ 	sw	$t5,0x30($sp)
.L00041034:
/*    41034:	afa0002c */ 	sw	$zero,0x2c($sp)
.L00041038:
/*    41038:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*    4103c:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    41040:	8faa0040 */ 	lw	$t2,0x40($sp)
/*    41044:	00194080 */ 	sll	$t0,$t9,0x2
/*    41048:	01e8c021 */ 	addu	$t8,$t7,$t0
/*    4104c:	000a4880 */ 	sll	$t1,$t2,0x2
/*    41050:	03095821 */ 	addu	$t3,$t8,$t1
/*    41054:	8d6e3c90 */ 	lw	$t6,0x3c90($t3)
/*    41058:	3c0c7005 */ 	lui	$t4,%hi(var70057b8c)
/*    4105c:	018e6021 */ 	addu	$t4,$t4,$t6
/*    41060:	918c7b8c */ 	lbu	$t4,%lo(var70057b8c)($t4)
/*    41064:	1180001c */ 	beqz	$t4,.L000410d8
/*    41068:	00000000 */ 	nop
/*    4106c:	25e4001c */ 	addiu	$a0,$t7,0x1c
/*    41070:	25e52020 */ 	addiu	$a1,$t7,0x2020
/*    41074:	0c0118b1 */ 	jal	func000462c4
/*    41078:	01803025 */ 	or	$a2,$t4,$zero
/*    4107c:	8fb9003c */ 	lw	$t9,0x3c($sp)
/*    41080:	8fae002c */ 	lw	$t6,0x2c($sp)
/*    41084:	8fb80040 */ 	lw	$t8,0x40($sp)
/*    41088:	00194140 */ 	sll	$t0,$t9,0x5
/*    4108c:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    41090:	01194023 */ 	subu	$t0,$t0,$t9
/*    41094:	000e7880 */ 	sll	$t7,$t6,0x2
/*    41098:	01ee7823 */ 	subu	$t7,$t7,$t6
/*    4109c:	00184940 */ 	sll	$t1,$t8,0x5
/*    410a0:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    410a4:	000f7880 */ 	sll	$t7,$t7,0x2
/*    410a8:	000840c0 */ 	sll	$t0,$t0,0x3
/*    410ac:	01384823 */ 	subu	$t1,$t1,$t8
/*    410b0:	000948c0 */ 	sll	$t1,$t1,0x3
/*    410b4:	01ee7821 */ 	addu	$t7,$t7,$t6
/*    410b8:	01a85021 */ 	addu	$t2,$t5,$t0
/*    410bc:	01495821 */ 	addu	$t3,$t2,$t1
/*    410c0:	000f7880 */ 	sll	$t7,$t7,0x2
/*    410c4:	016f6021 */ 	addu	$t4,$t3,$t7
/*    410c8:	00196880 */ 	sll	$t5,$t9,0x2
/*    410cc:	018d4021 */ 	addu	$t0,$t4,$t5
/*    410d0:	10000017 */ 	b	.L00041130
/*    410d4:	ad023d64 */ 	sw	$v0,0x3d64($t0)
.L000410d8:
/*    410d8:	8faa003c */ 	lw	$t2,0x3c($sp)
/*    410dc:	8fac002c */ 	lw	$t4,0x2c($sp)
/*    410e0:	8fab0040 */ 	lw	$t3,0x40($sp)
/*    410e4:	000a4940 */ 	sll	$t1,$t2,0x5
/*    410e8:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    410ec:	012a4823 */ 	subu	$t1,$t1,$t2
/*    410f0:	000c6880 */ 	sll	$t5,$t4,0x2
/*    410f4:	01ac6823 */ 	subu	$t5,$t5,$t4
/*    410f8:	000b7940 */ 	sll	$t7,$t3,0x5
/*    410fc:	8faa0030 */ 	lw	$t2,0x30($sp)
/*    41100:	000d6880 */ 	sll	$t5,$t5,0x2
/*    41104:	000948c0 */ 	sll	$t1,$t1,0x3
/*    41108:	01eb7823 */ 	subu	$t7,$t7,$t3
/*    4110c:	000f78c0 */ 	sll	$t7,$t7,0x3
/*    41110:	01ac6821 */ 	addu	$t5,$t5,$t4
/*    41114:	03097021 */ 	addu	$t6,$t8,$t1
/*    41118:	01cfc821 */ 	addu	$t9,$t6,$t7
/*    4111c:	000d6880 */ 	sll	$t5,$t5,0x2
/*    41120:	032d4021 */ 	addu	$t0,$t9,$t5
/*    41124:	000ac080 */ 	sll	$t8,$t2,0x2
/*    41128:	01184821 */ 	addu	$t1,$t0,$t8
/*    4112c:	ad203d64 */ 	sw	$zero,0x3d64($t1)
.L00041130:
/*    41130:	8fab002c */ 	lw	$t3,0x2c($sp)
/*    41134:	256e0001 */ 	addiu	$t6,$t3,0x1
/*    41138:	29c10003 */ 	slti	$at,$t6,0x3
/*    4113c:	1420ffbe */ 	bnez	$at,.L00041038
/*    41140:	afae002c */ 	sw	$t6,0x2c($sp)
/*    41144:	8faf0030 */ 	lw	$t7,0x30($sp)
/*    41148:	25ec0001 */ 	addiu	$t4,$t7,0x1
/*    4114c:	2981000c */ 	slti	$at,$t4,0xc
/*    41150:	1420ffb8 */ 	bnez	$at,.L00041034
/*    41154:	afac0030 */ 	sw	$t4,0x30($sp)
/*    41158:	10000065 */ 	b	.L000412f0
/*    4115c:	00000000 */ 	nop
.L00041160:
/*    41160:	afa00034 */ 	sw	$zero,0x34($sp)
.L00041164:
/*    41164:	8fb90034 */ 	lw	$t9,0x34($sp)
/*    41168:	3c0d7005 */ 	lui	$t5,%hi(var70057b74)
/*    4116c:	25ad7b74 */ 	addiu	$t5,$t5,%lo(var70057b74)
/*    41170:	032d5021 */ 	addu	$t2,$t9,$t5
/*    41174:	91480005 */ 	lbu	$t0,0x5($t2)
/*    41178:	afa80030 */ 	sw	$t0,0x30($sp)
/*    4117c:	91580006 */ 	lbu	$t8,0x6($t2)
/*    41180:	0118082a */ 	slt	$at,$t0,$t8
/*    41184:	10200055 */ 	beqz	$at,.L000412dc
/*    41188:	00000000 */ 	nop
.L0004118c:
/*    4118c:	afa0002c */ 	sw	$zero,0x2c($sp)
.L00041190:
/*    41190:	8fab003c */ 	lw	$t3,0x3c($sp)
/*    41194:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    41198:	8fac0040 */ 	lw	$t4,0x40($sp)
/*    4119c:	000b7080 */ 	sll	$t6,$t3,0x2
/*    411a0:	012e7821 */ 	addu	$t7,$t1,$t6
/*    411a4:	000cc880 */ 	sll	$t9,$t4,0x2
/*    411a8:	8fa80034 */ 	lw	$t0,0x34($sp)
/*    411ac:	01f96821 */ 	addu	$t5,$t7,$t9
/*    411b0:	8daa3c90 */ 	lw	$t2,0x3c90($t5)
/*    411b4:	3c0e7005 */ 	lui	$t6,%hi(var70057b7c)
/*    411b8:	0008c100 */ 	sll	$t8,$t0,0x4
/*    411bc:	25ce7b7c */ 	addiu	$t6,$t6,%lo(var70057b7c)
/*    411c0:	030a5821 */ 	addu	$t3,$t8,$t2
/*    411c4:	016e6021 */ 	addu	$t4,$t3,$t6
/*    411c8:	918f0000 */ 	lbu	$t7,0x0($t4)
/*    411cc:	11e0001e */ 	beqz	$t7,.L00041248
/*    411d0:	00000000 */ 	nop
/*    411d4:	030ac821 */ 	addu	$t9,$t8,$t2
/*    411d8:	032e6821 */ 	addu	$t5,$t9,$t6
/*    411dc:	91a60000 */ 	lbu	$a2,0x0($t5)
/*    411e0:	2524001c */ 	addiu	$a0,$t1,0x1c
/*    411e4:	0c0118b1 */ 	jal	func000462c4
/*    411e8:	25252020 */ 	addiu	$a1,$t1,0x2020
/*    411ec:	8fab003c */ 	lw	$t3,0x3c($sp)
/*    411f0:	8fb9002c */ 	lw	$t9,0x2c($sp)
/*    411f4:	8fa90040 */ 	lw	$t1,0x40($sp)
/*    411f8:	000b6140 */ 	sll	$t4,$t3,0x5
/*    411fc:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    41200:	018b6023 */ 	subu	$t4,$t4,$t3
/*    41204:	00197080 */ 	sll	$t6,$t9,0x2
/*    41208:	01d97023 */ 	subu	$t6,$t6,$t9
/*    4120c:	0009c140 */ 	sll	$t8,$t1,0x5
/*    41210:	8fab0030 */ 	lw	$t3,0x30($sp)
/*    41214:	000e7080 */ 	sll	$t6,$t6,0x2
/*    41218:	000c60c0 */ 	sll	$t4,$t4,0x3
/*    4121c:	0309c023 */ 	subu	$t8,$t8,$t1
/*    41220:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    41224:	01d97021 */ 	addu	$t6,$t6,$t9
/*    41228:	010c7821 */ 	addu	$t7,$t0,$t4
/*    4122c:	01f85021 */ 	addu	$t2,$t7,$t8
/*    41230:	000e7080 */ 	sll	$t6,$t6,0x2
/*    41234:	014e6821 */ 	addu	$t5,$t2,$t6
/*    41238:	000b4080 */ 	sll	$t0,$t3,0x2
/*    4123c:	01a86021 */ 	addu	$t4,$t5,$t0
/*    41240:	10000017 */ 	b	.L000412a0
/*    41244:	ad823d64 */ 	sw	$v0,0x3d64($t4)
.L00041248:
/*    41248:	8faf003c */ 	lw	$t7,0x3c($sp)
/*    4124c:	8fad002c */ 	lw	$t5,0x2c($sp)
/*    41250:	8faa0040 */ 	lw	$t2,0x40($sp)
/*    41254:	000fc140 */ 	sll	$t8,$t7,0x5
/*    41258:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    4125c:	030fc023 */ 	subu	$t8,$t8,$t7
/*    41260:	000d4080 */ 	sll	$t0,$t5,0x2
/*    41264:	010d4023 */ 	subu	$t0,$t0,$t5
/*    41268:	000a7140 */ 	sll	$t6,$t2,0x5
/*    4126c:	8faf0030 */ 	lw	$t7,0x30($sp)
/*    41270:	00084080 */ 	sll	$t0,$t0,0x2
/*    41274:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    41278:	01ca7023 */ 	subu	$t6,$t6,$t2
/*    4127c:	000e70c0 */ 	sll	$t6,$t6,0x3
/*    41280:	010d4021 */ 	addu	$t0,$t0,$t5
/*    41284:	0138c821 */ 	addu	$t9,$t1,$t8
/*    41288:	032e5821 */ 	addu	$t3,$t9,$t6
/*    4128c:	00084080 */ 	sll	$t0,$t0,0x2
/*    41290:	01686021 */ 	addu	$t4,$t3,$t0
/*    41294:	000f4880 */ 	sll	$t1,$t7,0x2
/*    41298:	0189c021 */ 	addu	$t8,$t4,$t1
/*    4129c:	af003d64 */ 	sw	$zero,0x3d64($t8)
.L000412a0:
/*    412a0:	8faa002c */ 	lw	$t2,0x2c($sp)
/*    412a4:	25590001 */ 	addiu	$t9,$t2,0x1
/*    412a8:	2b210003 */ 	slti	$at,$t9,0x3
/*    412ac:	1420ffb8 */ 	bnez	$at,.L00041190
/*    412b0:	afb9002c */ 	sw	$t9,0x2c($sp)
/*    412b4:	8fab0034 */ 	lw	$t3,0x34($sp)
/*    412b8:	3c087005 */ 	lui	$t0,%hi(var70057b78+0x2)
/*    412bc:	8fae0030 */ 	lw	$t6,0x30($sp)
/*    412c0:	010b4021 */ 	addu	$t0,$t0,$t3
/*    412c4:	91087b7a */ 	lbu	$t0,%lo(var70057b78+0x2)($t0)
/*    412c8:	25cd0001 */ 	addiu	$t5,$t6,0x1
/*    412cc:	afad0030 */ 	sw	$t5,0x30($sp)
/*    412d0:	01a8082a */ 	slt	$at,$t5,$t0
/*    412d4:	1420ffad */ 	bnez	$at,.L0004118c
/*    412d8:	00000000 */ 	nop
.L000412dc:
/*    412dc:	8faf0034 */ 	lw	$t7,0x34($sp)
/*    412e0:	25ec0001 */ 	addiu	$t4,$t7,0x1
/*    412e4:	29810002 */ 	slti	$at,$t4,0x2
/*    412e8:	1420ff9e */ 	bnez	$at,.L00041164
/*    412ec:	afac0034 */ 	sw	$t4,0x34($sp)
.L000412f0:
/*    412f0:	afa0002c */ 	sw	$zero,0x2c($sp)
.L000412f4:
/*    412f4:	8fb8003c */ 	lw	$t8,0x3c($sp)
/*    412f8:	8fa8002c */ 	lw	$t0,0x2c($sp)
/*    412fc:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    41300:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    41304:	00185140 */ 	sll	$t2,$t8,0x5
/*    41308:	00087880 */ 	sll	$t7,$t0,0x2
/*    4130c:	01585023 */ 	subu	$t2,$t2,$t8
/*    41310:	01e87823 */ 	subu	$t7,$t7,$t0
/*    41314:	000e5940 */ 	sll	$t3,$t6,0x5
/*    41318:	000f7880 */ 	sll	$t7,$t7,0x2
/*    4131c:	000a50c0 */ 	sll	$t2,$t2,0x3
/*    41320:	016e5823 */ 	subu	$t3,$t3,$t6
/*    41324:	000b58c0 */ 	sll	$t3,$t3,0x3
/*    41328:	01e87821 */ 	addu	$t7,$t7,$t0
/*    4132c:	012ac821 */ 	addu	$t9,$t1,$t2
/*    41330:	032b6821 */ 	addu	$t5,$t9,$t3
/*    41334:	000f7880 */ 	sll	$t7,$t7,0x2
/*    41338:	01af6021 */ 	addu	$t4,$t5,$t7
/*    4133c:	ad803d94 */ 	sw	$zero,0x3d94($t4)
/*    41340:	8fb8002c */ 	lw	$t8,0x2c($sp)
/*    41344:	27090001 */ 	addiu	$t1,$t8,0x1
/*    41348:	29210003 */ 	slti	$at,$t1,0x3
/*    4134c:	1420ffe9 */ 	bnez	$at,.L000412f4
/*    41350:	afa9002c */ 	sw	$t1,0x2c($sp)
/*    41354:	100000a1 */ 	b	.L000415dc
/*    41358:	00000000 */ 	nop
.L0004135c:
/*    4135c:	afa00034 */ 	sw	$zero,0x34($sp)
.L00041360:
/*    41360:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    41364:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    41368:	8fa80034 */ 	lw	$t0,0x34($sp)
/*    4136c:	000ec9c0 */ 	sll	$t9,$t6,0x7
/*    41370:	01595821 */ 	addu	$t3,$t2,$t9
/*    41374:	00086880 */ 	sll	$t5,$t0,0x2
/*    41378:	016d7821 */ 	addu	$t7,$t3,$t5
/*    4137c:	8dec3bf8 */ 	lw	$t4,0x3bf8($t7)
/*    41380:	11800004 */ 	beqz	$t4,.L00041394
/*    41384:	00000000 */ 	nop
/*    41388:	8fb8003c */ 	lw	$t8,0x3c($sp)
/*    4138c:	17000063 */ 	bnez	$t8,.L0004151c
/*    41390:	00000000 */ 	nop
.L00041394:
/*    41394:	8fa90034 */ 	lw	$t1,0x34($sp)
/*    41398:	3c0e7005 */ 	lui	$t6,%hi(var70057b74)
/*    4139c:	25ce7b74 */ 	addiu	$t6,$t6,%lo(var70057b74)
/*    413a0:	012e5021 */ 	addu	$t2,$t1,$t6
/*    413a4:	91590000 */ 	lbu	$t9,0x0($t2)
/*    413a8:	afb90030 */ 	sw	$t9,0x30($sp)
/*    413ac:	91480001 */ 	lbu	$t0,0x1($t2)
/*    413b0:	0328082a */ 	slt	$at,$t9,$t0
/*    413b4:	10200057 */ 	beqz	$at,.L00041514
/*    413b8:	00000000 */ 	nop
.L000413bc:
/*    413bc:	8fab0034 */ 	lw	$t3,0x34($sp)
/*    413c0:	29610002 */ 	slti	$at,$t3,0x2
/*    413c4:	10200003 */ 	beqz	$at,.L000413d4
/*    413c8:	00000000 */ 	nop
/*    413cc:	10000002 */ 	b	.L000413d8
/*    413d0:	00008025 */ 	or	$s0,$zero,$zero
.L000413d4:
/*    413d4:	24100001 */ 	addiu	$s0,$zero,0x1
.L000413d8:
/*    413d8:	8faf003c */ 	lw	$t7,0x3c($sp)
/*    413dc:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    413e0:	8fa90040 */ 	lw	$t1,0x40($sp)
/*    413e4:	000f6080 */ 	sll	$t4,$t7,0x2
/*    413e8:	01acc021 */ 	addu	$t8,$t5,$t4
/*    413ec:	00097080 */ 	sll	$t6,$t1,0x2
/*    413f0:	030e5021 */ 	addu	$t2,$t8,$t6
/*    413f4:	8d593c90 */ 	lw	$t9,0x3c90($t2)
/*    413f8:	00104100 */ 	sll	$t0,$s0,0x4
/*    413fc:	3c0f7005 */ 	lui	$t7,%hi(var70057b7c)
/*    41400:	01195821 */ 	addu	$t3,$t0,$t9
/*    41404:	01eb7821 */ 	addu	$t7,$t7,$t3
/*    41408:	91ef7b7c */ 	lbu	$t7,%lo(var70057b7c)($t7)
/*    4140c:	11e00028 */ 	beqz	$t7,.L000414b0
/*    41410:	00000000 */ 	nop
/*    41414:	8fad0034 */ 	lw	$t5,0x34($sp)
/*    41418:	29a10002 */ 	slti	$at,$t5,0x2
/*    4141c:	10200003 */ 	beqz	$at,.L0004142c
/*    41420:	00000000 */ 	nop
/*    41424:	10000002 */ 	b	.L00041430
/*    41428:	00008825 */ 	or	$s1,$zero,$zero
.L0004142c:
/*    4142c:	24110001 */ 	addiu	$s1,$zero,0x1
.L00041430:
/*    41430:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*    41434:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    41438:	8faa0040 */ 	lw	$t2,0x40($sp)
/*    4143c:	0009c080 */ 	sll	$t8,$t1,0x2
/*    41440:	01987021 */ 	addu	$t6,$t4,$t8
/*    41444:	000a4080 */ 	sll	$t0,$t2,0x2
/*    41448:	01c8c821 */ 	addu	$t9,$t6,$t0
/*    4144c:	8f2b3c90 */ 	lw	$t3,0x3c90($t9)
/*    41450:	00117900 */ 	sll	$t7,$s1,0x4
/*    41454:	3c067005 */ 	lui	$a2,%hi(var70057b7c)
/*    41458:	01eb6821 */ 	addu	$t5,$t7,$t3
/*    4145c:	00cd3021 */ 	addu	$a2,$a2,$t5
/*    41460:	90c67b7c */ 	lbu	$a2,%lo(var70057b7c)($a2)
/*    41464:	2584001c */ 	addiu	$a0,$t4,0x1c
/*    41468:	0c0118b1 */ 	jal	func000462c4
/*    4146c:	25852020 */ 	addiu	$a1,$t4,0x2020
/*    41470:	8fac003c */ 	lw	$t4,0x3c($sp)
/*    41474:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    41478:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    4147c:	000cc140 */ 	sll	$t8,$t4,0x5
/*    41480:	8faf0030 */ 	lw	$t7,0x30($sp)
/*    41484:	030cc023 */ 	subu	$t8,$t8,$t4
/*    41488:	000e4140 */ 	sll	$t0,$t6,0x5
/*    4148c:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    41490:	010e4023 */ 	subu	$t0,$t0,$t6
/*    41494:	000840c0 */ 	sll	$t0,$t0,0x3
/*    41498:	01385021 */ 	addu	$t2,$t1,$t8
/*    4149c:	0148c821 */ 	addu	$t9,$t2,$t0
/*    414a0:	000f5880 */ 	sll	$t3,$t7,0x2
/*    414a4:	032b6821 */ 	addu	$t5,$t9,$t3
/*    414a8:	10000010 */ 	b	.L000414ec
/*    414ac:	ada23d08 */ 	sw	$v0,0x3d08($t5)
.L000414b0:
/*    414b0:	8fa9003c */ 	lw	$t1,0x3c($sp)
/*    414b4:	8faa0040 */ 	lw	$t2,0x40($sp)
/*    414b8:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    414bc:	0009c140 */ 	sll	$t8,$t1,0x5
/*    414c0:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    414c4:	0309c023 */ 	subu	$t8,$t8,$t1
/*    414c8:	000a4140 */ 	sll	$t0,$t2,0x5
/*    414cc:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    414d0:	010a4023 */ 	subu	$t0,$t0,$t2
/*    414d4:	000840c0 */ 	sll	$t0,$t0,0x3
/*    414d8:	01987021 */ 	addu	$t6,$t4,$t8
/*    414dc:	01c87821 */ 	addu	$t7,$t6,$t0
/*    414e0:	00195880 */ 	sll	$t3,$t9,0x2
/*    414e4:	01eb6821 */ 	addu	$t5,$t7,$t3
/*    414e8:	ada03d08 */ 	sw	$zero,0x3d08($t5)
.L000414ec:
/*    414ec:	8fb80034 */ 	lw	$t8,0x34($sp)
/*    414f0:	3c0a7005 */ 	lui	$t2,%hi(var70057b74+0x1)
/*    414f4:	8fa90030 */ 	lw	$t1,0x30($sp)
/*    414f8:	01585021 */ 	addu	$t2,$t2,$t8
/*    414fc:	914a7b75 */ 	lbu	$t2,%lo(var70057b74+0x1)($t2)
/*    41500:	252c0001 */ 	addiu	$t4,$t1,0x1
/*    41504:	afac0030 */ 	sw	$t4,0x30($sp)
/*    41508:	018a082a */ 	slt	$at,$t4,$t2
/*    4150c:	1420ffab */ 	bnez	$at,.L000413bc
/*    41510:	00000000 */ 	nop
.L00041514:
/*    41514:	10000020 */ 	b	.L00041598
/*    41518:	00000000 */ 	nop
.L0004151c:
/*    4151c:	8fae0034 */ 	lw	$t6,0x34($sp)
/*    41520:	3c087005 */ 	lui	$t0,%hi(var70057b74)
/*    41524:	25087b74 */ 	addiu	$t0,$t0,%lo(var70057b74)
/*    41528:	01c8c821 */ 	addu	$t9,$t6,$t0
/*    4152c:	932f0000 */ 	lbu	$t7,0x0($t9)
/*    41530:	afaf0030 */ 	sw	$t7,0x30($sp)
/*    41534:	932b0001 */ 	lbu	$t3,0x1($t9)
/*    41538:	01eb082a */ 	slt	$at,$t7,$t3
/*    4153c:	10200016 */ 	beqz	$at,.L00041598
/*    41540:	00000000 */ 	nop
.L00041544:
/*    41544:	8fa90040 */ 	lw	$t1,0x40($sp)
/*    41548:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    4154c:	8faa0030 */ 	lw	$t2,0x30($sp)
/*    41550:	0009c140 */ 	sll	$t8,$t1,0x5
/*    41554:	0309c023 */ 	subu	$t8,$t8,$t1
/*    41558:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    4155c:	01b86021 */ 	addu	$t4,$t5,$t8
/*    41560:	000a7080 */ 	sll	$t6,$t2,0x2
/*    41564:	018e4021 */ 	addu	$t0,$t4,$t6
/*    41568:	8d193d08 */ 	lw	$t9,0x3d08($t0)
/*    4156c:	ad193e00 */ 	sw	$t9,0x3e00($t0)
/*    41570:	8fa90034 */ 	lw	$t1,0x34($sp)
/*    41574:	3c0d7005 */ 	lui	$t5,%hi(var70057b74+0x1)
/*    41578:	8faf0030 */ 	lw	$t7,0x30($sp)
/*    4157c:	01a96821 */ 	addu	$t5,$t5,$t1
/*    41580:	91ad7b75 */ 	lbu	$t5,%lo(var70057b74+0x1)($t5)
/*    41584:	25eb0001 */ 	addiu	$t3,$t7,0x1
/*    41588:	afab0030 */ 	sw	$t3,0x30($sp)
/*    4158c:	016d082a */ 	slt	$at,$t3,$t5
/*    41590:	1420ffec */ 	bnez	$at,.L00041544
/*    41594:	00000000 */ 	nop
.L00041598:
/*    41598:	8fb80034 */ 	lw	$t8,0x34($sp)
/*    4159c:	270a0001 */ 	addiu	$t2,$t8,0x1
/*    415a0:	29410004 */ 	slti	$at,$t2,0x4
/*    415a4:	1420ff6e */ 	bnez	$at,.L00041360
/*    415a8:	afaa0034 */ 	sw	$t2,0x34($sp)
/*    415ac:	8fae003c */ 	lw	$t6,0x3c($sp)
/*    415b0:	8faf0040 */ 	lw	$t7,0x40($sp)
/*    415b4:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    415b8:	000ec940 */ 	sll	$t9,$t6,0x5
/*    415bc:	032ec823 */ 	subu	$t9,$t9,$t6
/*    415c0:	000f4940 */ 	sll	$t1,$t7,0x5
/*    415c4:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*    415c8:	012f4823 */ 	subu	$t1,$t1,$t7
/*    415cc:	000948c0 */ 	sll	$t1,$t1,0x3
/*    415d0:	01994021 */ 	addu	$t0,$t4,$t9
/*    415d4:	01095821 */ 	addu	$t3,$t0,$t1
/*    415d8:	ad603d60 */ 	sw	$zero,0x3d60($t3)
.L000415dc:
/*    415dc:	10000003 */ 	b	.L000415ec
/*    415e0:	24020001 */ 	addiu	$v0,$zero,0x1
/*    415e4:	10000001 */ 	b	.L000415ec
/*    415e8:	00000000 */ 	nop
.L000415ec:
/*    415ec:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*    415f0:	8fb00014 */ 	lw	$s0,0x14($sp)
/*    415f4:	8fb10018 */ 	lw	$s1,0x18($sp)
/*    415f8:	03e00008 */ 	jr	$ra
/*    415fc:	27bd0038 */ 	addiu	$sp,$sp,0x38
);

const u32 var70059b34[] = {0x00000006};
const u32 var70059b38[] = {0x00000005};
const u32 var70059b3c[] = {0x00000005};
const u32 var70059b40[] = {0x00000005};
const u32 var70059b44[] = {0x00000009};
const u32 var70059b48[] = {0x00000009};
const u32 var70059b4c[] = {0x00000009};
const u32 var70059b50[] = {0x00000009};
const u32 var70059b54[] = {0x00000006};
const u32 var70059b58[] = {0x00000009};
const u32 var70059b5c[] = {0x00000009};
const u32 var70059b60[] = {0x00000009};
const u32 var70059b64[] = {0x00000006};
const u32 var70059b68[] = {0x00000005};
const u32 var70059b6c[] = {0x00000007};
const u32 var70059b70[] = {0x00000003};
const u32 var70059b74[] = {0x00000009};
const u32 var70059b78[] = {0x00000009};
const u32 var70059b7c[] = {0x0000000c};
const u32 var70059b80[] = {0x00000006};
const u32 var70059b84[] = {0x00000006};
const u32 var70059b88[] = {0x00000009};
const u32 var70059b8c[] = {0x0000000c};
const u32 var70059b90[] = {0x00000006};
const u32 var70059b94[] = {0x0000000b};
const u32 var70059b98[] = {0x0000000a};
const u32 var70059b9c[] = {0x00000000};
const u32 var70059ba0[] = {0x00000000};
const u32 var70059ba4[] = {0x00000012};
const u32 var70059ba8[] = {0x00000012};
const u32 var70059bac[] = {0x00000000};
const u32 var70059bb0[] = {0x00000000};
const u32 var70059bb4[] = {0x0000000f};
const u32 var70059bb8[] = {0x00000012};
const u32 var70059bbc[] = {0x00000000};
const u32 var70059bc0[] = {0x00000000};
const u32 var70059bc4[] = {0x00000007};
const u32 var70059bc8[] = {0x00000007};
const u32 var70059bcc[] = {0x00000007};
const u32 var70059bd0[] = {0x00000000};
const u32 var70059bd4[] = {0x0000000c};
const u32 var70059bd8[] = {0x0000000c};
const u32 var70059bdc[] = {0x0000000c};
const u32 var70059be0[] = {0x00000000};
const u32 var70059be4[] = {0x00000006};
const u32 var70059be8[] = {0x0000000f};
const u32 var70059bec[] = {0x0000000c};
const u32 var70059bf0[] = {0x00000000};
const u32 var70059bf4[] = {0x00000006};
const u32 var70059bf8[] = {0x00000006};
const u32 var70059bfc[] = {0x00000006};
const u32 var70059c00[] = {0x00000003};
const u32 var70059c04[] = {0x0000000c};
const u32 var70059c08[] = {0x00000009};
const u32 var70059c0c[] = {0x00000009};
const u32 var70059c10[] = {0x00000006};
const u32 var70059c14[] = {0x00000006};
const u32 var70059c18[] = {0x0000000c};
const u32 var70059c1c[] = {0x00000009};
const u32 var70059c20[] = {0x00000006};
const u32 var70059c24[] = {0x00000008};
const u32 var70059c28[] = {0x00000008};
const u32 var70059c2c[] = {0x00000005};
const u32 var70059c30[] = {0x00000000};
const u32 var70059c34[] = {0x0000000f};
const u32 var70059c38[] = {0x0000000c};
const u32 var70059c3c[] = {0x00000009};
const u32 var70059c40[] = {0x00000000};
const u32 var70059c44[] = {0x00000006};
const u32 var70059c48[] = {0x00000012};
const u32 var70059c4c[] = {0x00000009};
const u32 var70059c50[] = {0x00000000};

GLOBAL_ASM(
glabel func00041600
/*    41600:	27bdfe70 */ 	addiu	$sp,$sp,-400
/*    41604:	afbf0014 */ 	sw	$ra,0x14($sp)
/*    41608:	afa40190 */ 	sw	$a0,0x190($sp)
/*    4160c:	afa50194 */ 	sw	$a1,0x194($sp)
/*    41610:	afa60198 */ 	sw	$a2,0x198($sp)
/*    41614:	3c0f7006 */ 	lui	$t7,%hi(var70059b34)
/*    41618:	25ef9b34 */ 	addiu	$t7,$t7,%lo(var70059b34)
/*    4161c:	25e80120 */ 	addiu	$t0,$t7,0x120
/*    41620:	27ae0070 */ 	addiu	$t6,$sp,0x70
.L00041624:
/*    41624:	8df90000 */ 	lw	$t9,0x0($t7)
/*    41628:	25ef000c */ 	addiu	$t7,$t7,0xc
/*    4162c:	25ce000c */ 	addiu	$t6,$t6,0xc
/*    41630:	add9fff4 */ 	sw	$t9,-0xc($t6)
/*    41634:	8df8fff8 */ 	lw	$t8,-0x8($t7)
/*    41638:	add8fff8 */ 	sw	$t8,-0x8($t6)
/*    4163c:	8df9fffc */ 	lw	$t9,-0x4($t7)
/*    41640:	15e8fff8 */ 	bne	$t7,$t0,.L00041624
/*    41644:	add9fffc */ 	sw	$t9,-0x4($t6)
/*    41648:	8faa0198 */ 	lw	$t2,0x198($sp)
/*    4164c:	8fa90190 */ 	lw	$t1,0x190($sp)
/*    41650:	000a5880 */ 	sll	$t3,$t2,0x2
/*    41654:	012b6021 */ 	addu	$t4,$t1,$t3
/*    41658:	8d8d3c90 */ 	lw	$t5,0x3c90($t4)
/*    4165c:	afad005c */ 	sw	$t5,0x5c($sp)
/*    41660:	8faf0198 */ 	lw	$t7,0x198($sp)
/*    41664:	8fa80190 */ 	lw	$t0,0x190($sp)
/*    41668:	000f7080 */ 	sll	$t6,$t7,0x2
/*    4166c:	010ec021 */ 	addu	$t8,$t0,$t6
/*    41670:	27193cf0 */ 	addiu	$t9,$t8,0x3cf0
/*    41674:	afb90058 */ 	sw	$t9,0x58($sp)
/*    41678:	8fa90198 */ 	lw	$t1,0x198($sp)
/*    4167c:	8faa0190 */ 	lw	$t2,0x190($sp)
/*    41680:	00095880 */ 	sll	$t3,$t1,0x2
/*    41684:	014b6021 */ 	addu	$t4,$t2,$t3
/*    41688:	8d8d3ca8 */ 	lw	$t5,0x3ca8($t4)
/*    4168c:	afad0054 */ 	sw	$t5,0x54($sp)
/*    41690:	8fa80198 */ 	lw	$t0,0x198($sp)
/*    41694:	8faf0190 */ 	lw	$t7,0x190($sp)
/*    41698:	00087080 */ 	sll	$t6,$t0,0x2
/*    4169c:	01eec021 */ 	addu	$t8,$t7,$t6
/*    416a0:	8f193ca0 */ 	lw	$t9,0x3ca0($t8)
/*    416a4:	afb90050 */ 	sw	$t9,0x50($sp)
/*    416a8:	8faa0198 */ 	lw	$t2,0x198($sp)
/*    416ac:	8fa90190 */ 	lw	$t1,0x190($sp)
/*    416b0:	000a5880 */ 	sll	$t3,$t2,0x2
/*    416b4:	012b6021 */ 	addu	$t4,$t1,$t3
/*    416b8:	8d8d3c98 */ 	lw	$t5,0x3c98($t4)
/*    416bc:	afad004c */ 	sw	$t5,0x4c($sp)
/*    416c0:	8fa80190 */ 	lw	$t0,0x190($sp)
/*    416c4:	24010001 */ 	addiu	$at,$zero,0x1
/*    416c8:	8d0f3bc4 */ 	lw	$t7,0x3bc4($t0)
/*    416cc:	11e10004 */ 	beq	$t7,$at,.L000416e0
/*    416d0:	00000000 */ 	nop
/*    416d4:	24010003 */ 	addiu	$at,$zero,0x3
/*    416d8:	15e10005 */ 	bne	$t7,$at,.L000416f0
/*    416dc:	00000000 */ 	nop
.L000416e0:
/*    416e0:	8fae0198 */ 	lw	$t6,0x198($sp)
/*    416e4:	24010001 */ 	addiu	$at,$zero,0x1
/*    416e8:	11c10074 */ 	beq	$t6,$at,.L000418bc
/*    416ec:	00000000 */ 	nop
.L000416f0:
/*    416f0:	afa00048 */ 	sw	$zero,0x48($sp)
/*    416f4:	8fb8005c */ 	lw	$t8,0x5c($sp)
/*    416f8:	2b010190 */ 	slti	$at,$t8,0x190
/*    416fc:	10200026 */ 	beqz	$at,.L00041798
/*    41700:	00000000 */ 	nop
/*    41704:	8fb9005c */ 	lw	$t9,0x5c($sp)
/*    41708:	24010005 */ 	addiu	$at,$zero,0x5
/*    4170c:	27ab0060 */ 	addiu	$t3,$sp,0x60
/*    41710:	00195103 */ 	sra	$t2,$t9,0x4
/*    41714:	0141001a */ 	div	$zero,$t2,$at
/*    41718:	00004812 */ 	mflo	$t1
/*    4171c:	ad690000 */ 	sw	$t1,0x0($t3)
/*    41720:	00000000 */ 	nop
/*    41724:	8fac005c */ 	lw	$t4,0x5c($sp)
/*    41728:	24010005 */ 	addiu	$at,$zero,0x5
/*    4172c:	27af0060 */ 	addiu	$t7,$sp,0x60
/*    41730:	000c6903 */ 	sra	$t5,$t4,0x4
/*    41734:	01a1001a */ 	div	$zero,$t5,$at
/*    41738:	00004010 */ 	mfhi	$t0
/*    4173c:	ade80004 */ 	sw	$t0,0x4($t7)
/*    41740:	00000000 */ 	nop
/*    41744:	8fae005c */ 	lw	$t6,0x5c($sp)
/*    41748:	27aa0060 */ 	addiu	$t2,$sp,0x60
/*    4174c:	05c10004 */ 	bgez	$t6,.L00041760
/*    41750:	31d8000f */ 	andi	$t8,$t6,0xf
/*    41754:	13000002 */ 	beqz	$t8,.L00041760
/*    41758:	00000000 */ 	nop
/*    4175c:	2718fff0 */ 	addiu	$t8,$t8,-16
.L00041760:
/*    41760:	0018c883 */ 	sra	$t9,$t8,0x2
/*    41764:	ad590008 */ 	sw	$t9,0x8($t2)
/*    41768:	8fa9005c */ 	lw	$t1,0x5c($sp)
/*    4176c:	27ac0060 */ 	addiu	$t4,$sp,0x60
/*    41770:	05210004 */ 	bgez	$t1,.L00041784
/*    41774:	312b0003 */ 	andi	$t3,$t1,0x3
/*    41778:	11600002 */ 	beqz	$t3,.L00041784
/*    4177c:	00000000 */ 	nop
/*    41780:	256bfffc */ 	addiu	$t3,$t3,-4
.L00041784:
/*    41784:	ad8b000c */ 	sw	$t3,0xc($t4)
/*    41788:	8fad0058 */ 	lw	$t5,0x58($sp)
/*    4178c:	ada00000 */ 	sw	$zero,0x0($t5)
/*    41790:	1000004a */ 	b	.L000418bc
/*    41794:	afa00044 */ 	sw	$zero,0x44($sp)
.L00041798:
/*    41798:	8fa8005c */ 	lw	$t0,0x5c($sp)
/*    4179c:	29010190 */ 	slti	$at,$t0,0x190
/*    417a0:	14200026 */ 	bnez	$at,.L0004183c
/*    417a4:	00000000 */ 	nop
/*    417a8:	290101f4 */ 	slti	$at,$t0,0x1f4
/*    417ac:	10200023 */ 	beqz	$at,.L0004183c
/*    417b0:	00000000 */ 	nop
/*    417b4:	8faf005c */ 	lw	$t7,0x5c($sp)
/*    417b8:	24010005 */ 	addiu	$at,$zero,0x5
/*    417bc:	27aa0060 */ 	addiu	$t2,$sp,0x60
/*    417c0:	25eefe70 */ 	addiu	$t6,$t7,-400
/*    417c4:	000ec083 */ 	sra	$t8,$t6,0x2
/*    417c8:	0301001a */ 	div	$zero,$t8,$at
/*    417cc:	0000c812 */ 	mflo	$t9
/*    417d0:	ad590000 */ 	sw	$t9,0x0($t2)
/*    417d4:	00000000 */ 	nop
/*    417d8:	8fa9005c */ 	lw	$t1,0x5c($sp)
/*    417dc:	24010005 */ 	addiu	$at,$zero,0x5
/*    417e0:	27a80060 */ 	addiu	$t0,$sp,0x60
/*    417e4:	252bfe70 */ 	addiu	$t3,$t1,-400
/*    417e8:	000b6083 */ 	sra	$t4,$t3,0x2
/*    417ec:	0181001a */ 	div	$zero,$t4,$at
/*    417f0:	00006810 */ 	mfhi	$t5
/*    417f4:	ad0d0004 */ 	sw	$t5,0x4($t0)
/*    417f8:	00000000 */ 	nop
/*    417fc:	8faf005c */ 	lw	$t7,0x5c($sp)
/*    41800:	27b90060 */ 	addiu	$t9,$sp,0x60
/*    41804:	25eefe70 */ 	addiu	$t6,$t7,-400
/*    41808:	05c10004 */ 	bgez	$t6,.L0004181c
/*    4180c:	31d80003 */ 	andi	$t8,$t6,0x3
/*    41810:	13000002 */ 	beqz	$t8,.L0004181c
/*    41814:	00000000 */ 	nop
/*    41818:	2718fffc */ 	addiu	$t8,$t8,-4
.L0004181c:
/*    4181c:	af380008 */ 	sw	$t8,0x8($t9)
/*    41820:	27aa0060 */ 	addiu	$t2,$sp,0x60
/*    41824:	ad40000c */ 	sw	$zero,0xc($t2)
/*    41828:	8fa90058 */ 	lw	$t1,0x58($sp)
/*    4182c:	ad200000 */ 	sw	$zero,0x0($t1)
/*    41830:	240b0001 */ 	addiu	$t3,$zero,0x1
/*    41834:	10000021 */ 	b	.L000418bc
/*    41838:	afab0044 */ 	sw	$t3,0x44($sp)
.L0004183c:
/*    4183c:	8fac005c */ 	lw	$t4,0x5c($sp)
/*    41840:	298101f4 */ 	slti	$at,$t4,0x1f4
/*    41844:	1420001d */ 	bnez	$at,.L000418bc
/*    41848:	00000000 */ 	nop
/*    4184c:	29810200 */ 	slti	$at,$t4,0x200
/*    41850:	1020001a */ 	beqz	$at,.L000418bc
/*    41854:	00000000 */ 	nop
/*    41858:	8fad005c */ 	lw	$t5,0x5c($sp)
/*    4185c:	24010003 */ 	addiu	$at,$zero,0x3
/*    41860:	27ae0060 */ 	addiu	$t6,$sp,0x60
/*    41864:	25a8fe0c */ 	addiu	$t0,$t5,-500
/*    41868:	0101001a */ 	div	$zero,$t0,$at
/*    4186c:	00007812 */ 	mflo	$t7
/*    41870:	adcf0000 */ 	sw	$t7,0x0($t6)
/*    41874:	00000000 */ 	nop
/*    41878:	8fb8005c */ 	lw	$t8,0x5c($sp)
/*    4187c:	24010003 */ 	addiu	$at,$zero,0x3
/*    41880:	27a90060 */ 	addiu	$t1,$sp,0x60
/*    41884:	2719fe0c */ 	addiu	$t9,$t8,-500
/*    41888:	0321001a */ 	div	$zero,$t9,$at
/*    4188c:	00005010 */ 	mfhi	$t2
/*    41890:	ad2a0004 */ 	sw	$t2,0x4($t1)
/*    41894:	00000000 */ 	nop
/*    41898:	27ab0060 */ 	addiu	$t3,$sp,0x60
/*    4189c:	ad600008 */ 	sw	$zero,0x8($t3)
/*    418a0:	27ac0060 */ 	addiu	$t4,$sp,0x60
/*    418a4:	ad80000c */ 	sw	$zero,0xc($t4)
/*    418a8:	8fa80058 */ 	lw	$t0,0x58($sp)
/*    418ac:	240d0001 */ 	addiu	$t5,$zero,0x1
/*    418b0:	ad0d0000 */ 	sw	$t5,0x0($t0)
/*    418b4:	240f0002 */ 	addiu	$t7,$zero,0x2
/*    418b8:	afaf0044 */ 	sw	$t7,0x44($sp)
.L000418bc:
/*    418bc:	8fae0190 */ 	lw	$t6,0x190($sp)
/*    418c0:	24010001 */ 	addiu	$at,$zero,0x1
/*    418c4:	8dd83bc4 */ 	lw	$t8,0x3bc4($t6)
/*    418c8:	13010004 */ 	beq	$t8,$at,.L000418dc
/*    418cc:	00000000 */ 	nop
/*    418d0:	24010003 */ 	addiu	$at,$zero,0x3
/*    418d4:	17010083 */ 	bne	$t8,$at,.L00041ae4
/*    418d8:	00000000 */ 	nop
.L000418dc:
/*    418dc:	8fb90198 */ 	lw	$t9,0x198($sp)
/*    418e0:	24010001 */ 	addiu	$at,$zero,0x1
/*    418e4:	1721007f */ 	bne	$t9,$at,.L00041ae4
/*    418e8:	00000000 */ 	nop
/*    418ec:	8faa005c */ 	lw	$t2,0x5c($sp)
/*    418f0:	8fab0190 */ 	lw	$t3,0x190($sp)
/*    418f4:	05410004 */ 	bgez	$t2,.L00041908
/*    418f8:	31490001 */ 	andi	$t1,$t2,0x1
/*    418fc:	11200002 */ 	beqz	$t1,.L00041908
/*    41900:	00000000 */ 	nop
/*    41904:	2529fffe */ 	addiu	$t1,$t1,-2
.L00041908:
/*    41908:	ad693ef8 */ 	sw	$t1,0x3ef8($t3)
/*    4190c:	8fac005c */ 	lw	$t4,0x5c($sp)
/*    41910:	000c6843 */ 	sra	$t5,$t4,0x1
/*    41914:	afad0038 */ 	sw	$t5,0x38($sp)
/*    41918:	24080001 */ 	addiu	$t0,$zero,0x1
/*    4191c:	afa80048 */ 	sw	$t0,0x48($sp)
/*    41920:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    41924:	29e100b4 */ 	slti	$at,$t7,0xb4
/*    41928:	10200024 */ 	beqz	$at,.L000419bc
/*    4192c:	00000000 */ 	nop
/*    41930:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    41934:	24010024 */ 	addiu	$at,$zero,0x24
/*    41938:	27b90060 */ 	addiu	$t9,$sp,0x60
/*    4193c:	01c1001a */ 	div	$zero,$t6,$at
/*    41940:	0000c012 */ 	mflo	$t8
/*    41944:	af380000 */ 	sw	$t8,0x0($t9)
/*    41948:	00000000 */ 	nop
/*    4194c:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    41950:	24010024 */ 	addiu	$at,$zero,0x24
/*    41954:	27ac0060 */ 	addiu	$t4,$sp,0x60
/*    41958:	0141001a */ 	div	$zero,$t2,$at
/*    4195c:	00004810 */ 	mfhi	$t1
/*    41960:	24010006 */ 	addiu	$at,$zero,0x6
/*    41964:	00000000 */ 	nop
/*    41968:	0121001a */ 	div	$zero,$t1,$at
/*    4196c:	00005812 */ 	mflo	$t3
/*    41970:	ad8b0004 */ 	sw	$t3,0x4($t4)
/*    41974:	00000000 */ 	nop
/*    41978:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    4197c:	24010024 */ 	addiu	$at,$zero,0x24
/*    41980:	27ae0060 */ 	addiu	$t6,$sp,0x60
/*    41984:	01a1001a */ 	div	$zero,$t5,$at
/*    41988:	00004010 */ 	mfhi	$t0
/*    4198c:	24010006 */ 	addiu	$at,$zero,0x6
/*    41990:	00000000 */ 	nop
/*    41994:	0101001a */ 	div	$zero,$t0,$at
/*    41998:	00007810 */ 	mfhi	$t7
/*    4199c:	adcf0008 */ 	sw	$t7,0x8($t6)
/*    419a0:	00000000 */ 	nop
/*    419a4:	27b80060 */ 	addiu	$t8,$sp,0x60
/*    419a8:	af00000c */ 	sw	$zero,0xc($t8)
/*    419ac:	8fb90058 */ 	lw	$t9,0x58($sp)
/*    419b0:	af200000 */ 	sw	$zero,0x0($t9)
/*    419b4:	1000004b */ 	b	.L00041ae4
/*    419b8:	afa00044 */ 	sw	$zero,0x44($sp)
.L000419bc:
/*    419bc:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    419c0:	294100b4 */ 	slti	$at,$t2,0xb4
/*    419c4:	14200028 */ 	bnez	$at,.L00041a68
/*    419c8:	00000000 */ 	nop
/*    419cc:	294100f4 */ 	slti	$at,$t2,0xf4
/*    419d0:	10200025 */ 	beqz	$at,.L00041a68
/*    419d4:	00000000 */ 	nop
/*    419d8:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    419dc:	27a80060 */ 	addiu	$t0,$sp,0x60
/*    419e0:	252bff4c */ 	addiu	$t3,$t1,-180
/*    419e4:	05610004 */ 	bgez	$t3,.L000419f8
/*    419e8:	316c003f */ 	andi	$t4,$t3,0x3f
/*    419ec:	11800002 */ 	beqz	$t4,.L000419f8
/*    419f0:	00000000 */ 	nop
/*    419f4:	258cffc0 */ 	addiu	$t4,$t4,-64
.L000419f8:
/*    419f8:	000c6903 */ 	sra	$t5,$t4,0x4
/*    419fc:	ad0d0000 */ 	sw	$t5,0x0($t0)
/*    41a00:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    41a04:	27aa0060 */ 	addiu	$t2,$sp,0x60
/*    41a08:	25eeff4c */ 	addiu	$t6,$t7,-180
/*    41a0c:	05c10004 */ 	bgez	$t6,.L00041a20
/*    41a10:	31d8000f */ 	andi	$t8,$t6,0xf
/*    41a14:	13000002 */ 	beqz	$t8,.L00041a20
/*    41a18:	00000000 */ 	nop
/*    41a1c:	2718fff0 */ 	addiu	$t8,$t8,-16
.L00041a20:
/*    41a20:	0018c883 */ 	sra	$t9,$t8,0x2
/*    41a24:	ad590004 */ 	sw	$t9,0x4($t2)
/*    41a28:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    41a2c:	27ad0060 */ 	addiu	$t5,$sp,0x60
/*    41a30:	252bff4c */ 	addiu	$t3,$t1,-180
/*    41a34:	05610004 */ 	bgez	$t3,.L00041a48
/*    41a38:	316c0003 */ 	andi	$t4,$t3,0x3
/*    41a3c:	11800002 */ 	beqz	$t4,.L00041a48
/*    41a40:	00000000 */ 	nop
/*    41a44:	258cfffc */ 	addiu	$t4,$t4,-4
.L00041a48:
/*    41a48:	adac0008 */ 	sw	$t4,0x8($t5)
/*    41a4c:	27a80060 */ 	addiu	$t0,$sp,0x60
/*    41a50:	ad00000c */ 	sw	$zero,0xc($t0)
/*    41a54:	8faf0058 */ 	lw	$t7,0x58($sp)
/*    41a58:	ade00000 */ 	sw	$zero,0x0($t7)
/*    41a5c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    41a60:	10000020 */ 	b	.L00041ae4
/*    41a64:	afae0044 */ 	sw	$t6,0x44($sp)
.L00041a68:
/*    41a68:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    41a6c:	2b0100f4 */ 	slti	$at,$t8,0xf4
/*    41a70:	1420001c */ 	bnez	$at,.L00041ae4
/*    41a74:	00000000 */ 	nop
/*    41a78:	2b0100ff */ 	slti	$at,$t8,0xff
/*    41a7c:	10200019 */ 	beqz	$at,.L00041ae4
/*    41a80:	00000000 */ 	nop
/*    41a84:	8fb90038 */ 	lw	$t9,0x38($sp)
/*    41a88:	24010003 */ 	addiu	$at,$zero,0x3
/*    41a8c:	27ab0060 */ 	addiu	$t3,$sp,0x60
/*    41a90:	272aff0c */ 	addiu	$t2,$t9,-244
/*    41a94:	0141001a */ 	div	$zero,$t2,$at
/*    41a98:	00004812 */ 	mflo	$t1
/*    41a9c:	ad690000 */ 	sw	$t1,0x0($t3)
/*    41aa0:	00000000 */ 	nop
/*    41aa4:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    41aa8:	24010003 */ 	addiu	$at,$zero,0x3
/*    41aac:	27af0060 */ 	addiu	$t7,$sp,0x60
/*    41ab0:	258dff0c */ 	addiu	$t5,$t4,-244
/*    41ab4:	01a1001a */ 	div	$zero,$t5,$at
/*    41ab8:	00004010 */ 	mfhi	$t0
/*    41abc:	ade80004 */ 	sw	$t0,0x4($t7)
/*    41ac0:	00000000 */ 	nop
/*    41ac4:	27ae0060 */ 	addiu	$t6,$sp,0x60
/*    41ac8:	adc00008 */ 	sw	$zero,0x8($t6)
/*    41acc:	27b80060 */ 	addiu	$t8,$sp,0x60
/*    41ad0:	af00000c */ 	sw	$zero,0xc($t8)
/*    41ad4:	8fb90058 */ 	lw	$t9,0x58($sp)
/*    41ad8:	af200000 */ 	sw	$zero,0x0($t9)
/*    41adc:	240a0002 */ 	addiu	$t2,$zero,0x2
/*    41ae0:	afaa0044 */ 	sw	$t2,0x44($sp)
.L00041ae4:
/*    41ae4:	8fa9004c */ 	lw	$t1,0x4c($sp)
/*    41ae8:	11200019 */ 	beqz	$t1,.L00041b50
/*    41aec:	00000000 */ 	nop
/*    41af0:	8fab0050 */ 	lw	$t3,0x50($sp)
/*    41af4:	24010002 */ 	addiu	$at,$zero,0x2
/*    41af8:	15610015 */ 	bne	$t3,$at,.L00041b50
/*    41afc:	00000000 */ 	nop
/*    41b00:	8fac0048 */ 	lw	$t4,0x48($sp)
/*    41b04:	8fa80044 */ 	lw	$t0,0x44($sp)
/*    41b08:	8fb80054 */ 	lw	$t8,0x54($sp)
/*    41b0c:	000c68c0 */ 	sll	$t5,$t4,0x3
/*    41b10:	00087880 */ 	sll	$t7,$t0,0x2
/*    41b14:	01ac6821 */ 	addu	$t5,$t5,$t4
/*    41b18:	01e87823 */ 	subu	$t7,$t7,$t0
/*    41b1c:	000f7900 */ 	sll	$t7,$t7,0x4
/*    41b20:	000d6900 */ 	sll	$t5,$t5,0x4
/*    41b24:	01af7021 */ 	addu	$t6,$t5,$t7
/*    41b28:	0018c900 */ 	sll	$t9,$t8,0x4
/*    41b2c:	01d95021 */ 	addu	$t2,$t6,$t9
/*    41b30:	25490010 */ 	addiu	$t1,$t2,0x10
/*    41b34:	27ab0070 */ 	addiu	$t3,$sp,0x70
/*    41b38:	012b2021 */ 	addu	$a0,$t1,$t3
/*    41b3c:	27a50028 */ 	addiu	$a1,$sp,0x28
/*    41b40:	0c012c5c */ 	jal	bcopy
/*    41b44:	24060010 */ 	addiu	$a2,$zero,0x10
/*    41b48:	1000000f */ 	b	.L00041b88
/*    41b4c:	00000000 */ 	nop
.L00041b50:
/*    41b50:	8fac0048 */ 	lw	$t4,0x48($sp)
/*    41b54:	8fad0044 */ 	lw	$t5,0x44($sp)
/*    41b58:	27ae0070 */ 	addiu	$t6,$sp,0x70
/*    41b5c:	000c40c0 */ 	sll	$t0,$t4,0x3
/*    41b60:	000d7880 */ 	sll	$t7,$t5,0x2
/*    41b64:	010c4021 */ 	addu	$t0,$t0,$t4
/*    41b68:	01ed7823 */ 	subu	$t7,$t7,$t5
/*    41b6c:	000f7900 */ 	sll	$t7,$t7,0x4
/*    41b70:	00084100 */ 	sll	$t0,$t0,0x4
/*    41b74:	010fc021 */ 	addu	$t8,$t0,$t7
/*    41b78:	030e2021 */ 	addu	$a0,$t8,$t6
/*    41b7c:	27a50028 */ 	addiu	$a1,$sp,0x28
/*    41b80:	0c012c5c */ 	jal	bcopy
/*    41b84:	24060010 */ 	addiu	$a2,$zero,0x10
.L00041b88:
/*    41b88:	afa00024 */ 	sw	$zero,0x24($sp)
/*    41b8c:	8fb9004c */ 	lw	$t9,0x4c($sp)
/*    41b90:	13200007 */ 	beqz	$t9,.L00041bb0
/*    41b94:	00000000 */ 	nop
/*    41b98:	13200051 */ 	beqz	$t9,.L00041ce0
/*    41b9c:	00000000 */ 	nop
/*    41ba0:	8faa0050 */ 	lw	$t2,0x50($sp)
/*    41ba4:	24010002 */ 	addiu	$at,$zero,0x2
/*    41ba8:	1141004d */ 	beq	$t2,$at,.L00041ce0
/*    41bac:	00000000 */ 	nop
.L00041bb0:
/*    41bb0:	afa00040 */ 	sw	$zero,0x40($sp)
.L00041bb4:
/*    41bb4:	8fa90040 */ 	lw	$t1,0x40($sp)
/*    41bb8:	00095880 */ 	sll	$t3,$t1,0x2
/*    41bbc:	03ab6021 */ 	addu	$t4,$sp,$t3
/*    41bc0:	8d8c0060 */ 	lw	$t4,0x60($t4)
/*    41bc4:	afac0020 */ 	sw	$t4,0x20($sp)
/*    41bc8:	8fad0020 */ 	lw	$t5,0x20($sp)
/*    41bcc:	24080001 */ 	addiu	$t0,$zero,0x1
/*    41bd0:	01a87804 */ 	sllv	$t7,$t0,$t5
/*    41bd4:	25f8ffff */ 	addiu	$t8,$t7,-1
/*    41bd8:	afb8001c */ 	sw	$t8,0x1c($sp)
/*    41bdc:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    41be0:	afa0003c */ 	sw	$zero,0x3c($sp)
/*    41be4:	000ec880 */ 	sll	$t9,$t6,0x2
/*    41be8:	03b95021 */ 	addu	$t2,$sp,$t9
/*    41bec:	8d4a0028 */ 	lw	$t2,0x28($t2)
/*    41bf0:	19400034 */ 	blez	$t2,.L00041cc4
/*    41bf4:	00000000 */ 	nop
.L00041bf8:
/*    41bf8:	8fa90020 */ 	lw	$t1,0x20($sp)
/*    41bfc:	11200011 */ 	beqz	$t1,.L00041c44
/*    41c00:	00000000 */ 	nop
/*    41c04:	8fab0190 */ 	lw	$t3,0x190($sp)
/*    41c08:	01203025 */ 	or	$a2,$t1,$zero
/*    41c0c:	2564001c */ 	addiu	$a0,$t3,0x1c
/*    41c10:	0c0118b1 */ 	jal	func000462c4
/*    41c14:	25652020 */ 	addiu	$a1,$t3,0x2020
/*    41c18:	8fa80198 */ 	lw	$t0,0x198($sp)
/*    41c1c:	8fac0190 */ 	lw	$t4,0x190($sp)
/*    41c20:	8fb80024 */ 	lw	$t8,0x24($sp)
/*    41c24:	00086940 */ 	sll	$t5,$t0,0x5
/*    41c28:	01a86823 */ 	subu	$t5,$t5,$t0
/*    41c2c:	000d68c0 */ 	sll	$t5,$t5,0x3
/*    41c30:	018d7821 */ 	addu	$t7,$t4,$t5
/*    41c34:	00187080 */ 	sll	$t6,$t8,0x2
/*    41c38:	01eec821 */ 	addu	$t9,$t7,$t6
/*    41c3c:	1000000b */ 	b	.L00041c6c
/*    41c40:	af223d08 */ 	sw	$v0,0x3d08($t9)
.L00041c44:
/*    41c44:	8fab0198 */ 	lw	$t3,0x198($sp)
/*    41c48:	8faa0190 */ 	lw	$t2,0x190($sp)
/*    41c4c:	8fac0024 */ 	lw	$t4,0x24($sp)
/*    41c50:	000b4940 */ 	sll	$t1,$t3,0x5
/*    41c54:	012b4823 */ 	subu	$t1,$t1,$t3
/*    41c58:	000948c0 */ 	sll	$t1,$t1,0x3
/*    41c5c:	01494021 */ 	addu	$t0,$t2,$t1
/*    41c60:	000c6880 */ 	sll	$t5,$t4,0x2
/*    41c64:	010dc021 */ 	addu	$t8,$t0,$t5
/*    41c68:	af003d08 */ 	sw	$zero,0x3d08($t8)
.L00041c6c:
/*    41c6c:	8faf0198 */ 	lw	$t7,0x198($sp)
/*    41c70:	11e00007 */ 	beqz	$t7,.L00041c90
/*    41c74:	00000000 */ 	nop
/*    41c78:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    41c7c:	8fb90190 */ 	lw	$t9,0x190($sp)
/*    41c80:	8fae001c */ 	lw	$t6,0x1c($sp)
/*    41c84:	000b5080 */ 	sll	$t2,$t3,0x2
/*    41c88:	032a4821 */ 	addu	$t1,$t9,$t2
/*    41c8c:	ad2e3efc */ 	sw	$t6,0x3efc($t1)
.L00041c90:
/*    41c90:	8fac0024 */ 	lw	$t4,0x24($sp)
/*    41c94:	25880001 */ 	addiu	$t0,$t4,0x1
/*    41c98:	afa80024 */ 	sw	$t0,0x24($sp)
/*    41c9c:	8fad003c */ 	lw	$t5,0x3c($sp)
/*    41ca0:	8faf0040 */ 	lw	$t7,0x40($sp)
/*    41ca4:	25b80001 */ 	addiu	$t8,$t5,0x1
/*    41ca8:	000f5880 */ 	sll	$t3,$t7,0x2
/*    41cac:	03abc821 */ 	addu	$t9,$sp,$t3
/*    41cb0:	afb8003c */ 	sw	$t8,0x3c($sp)
/*    41cb4:	8f390028 */ 	lw	$t9,0x28($t9)
/*    41cb8:	0319082a */ 	slt	$at,$t8,$t9
/*    41cbc:	1420ffce */ 	bnez	$at,.L00041bf8
/*    41cc0:	00000000 */ 	nop
.L00041cc4:
/*    41cc4:	8faa0040 */ 	lw	$t2,0x40($sp)
/*    41cc8:	254e0001 */ 	addiu	$t6,$t2,0x1
/*    41ccc:	29c10004 */ 	slti	$at,$t6,0x4
/*    41cd0:	1420ffb8 */ 	bnez	$at,.L00041bb4
/*    41cd4:	afae0040 */ 	sw	$t6,0x40($sp)
/*    41cd8:	1000014f */ 	b	.L00042218
/*    41cdc:	00000000 */ 	nop
.L00041ce0:
/*    41ce0:	8fa90050 */ 	lw	$t1,0x50($sp)
/*    41ce4:	24010002 */ 	addiu	$at,$zero,0x2
/*    41ce8:	1521014b */ 	bne	$t1,$at,.L00042218
/*    41cec:	00000000 */ 	nop
/*    41cf0:	8fac0054 */ 	lw	$t4,0x54($sp)
/*    41cf4:	15800087 */ 	bnez	$t4,.L00041f14
/*    41cf8:	00000000 */ 	nop
/*    41cfc:	afa00040 */ 	sw	$zero,0x40($sp)
.L00041d00:
/*    41d00:	8fa80040 */ 	lw	$t0,0x40($sp)
/*    41d04:	00086880 */ 	sll	$t5,$t0,0x2
/*    41d08:	03ad7821 */ 	addu	$t7,$sp,$t5
/*    41d0c:	8def0060 */ 	lw	$t7,0x60($t7)
/*    41d10:	afaf0020 */ 	sw	$t7,0x20($sp)
/*    41d14:	8fab0020 */ 	lw	$t3,0x20($sp)
/*    41d18:	24180001 */ 	addiu	$t8,$zero,0x1
/*    41d1c:	0178c804 */ 	sllv	$t9,$t8,$t3
/*    41d20:	272affff */ 	addiu	$t2,$t9,-1
/*    41d24:	afaa001c */ 	sw	$t2,0x1c($sp)
/*    41d28:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    41d2c:	afa0003c */ 	sw	$zero,0x3c($sp)
/*    41d30:	000e4880 */ 	sll	$t1,$t6,0x2
/*    41d34:	03a96021 */ 	addu	$t4,$sp,$t1
/*    41d38:	8d8c0028 */ 	lw	$t4,0x28($t4)
/*    41d3c:	1980006e */ 	blez	$t4,.L00041ef8
/*    41d40:	00000000 */ 	nop
.L00041d44:
/*    41d44:	8fa80020 */ 	lw	$t0,0x20($sp)
/*    41d48:	11000011 */ 	beqz	$t0,.L00041d90
/*    41d4c:	00000000 */ 	nop
/*    41d50:	8fad0190 */ 	lw	$t5,0x190($sp)
/*    41d54:	01003025 */ 	or	$a2,$t0,$zero
/*    41d58:	25a4001c */ 	addiu	$a0,$t5,0x1c
/*    41d5c:	0c0118b1 */ 	jal	func000462c4
/*    41d60:	25a52020 */ 	addiu	$a1,$t5,0x2020
/*    41d64:	8fb80198 */ 	lw	$t8,0x198($sp)
/*    41d68:	8faf0190 */ 	lw	$t7,0x190($sp)
/*    41d6c:	8faa0024 */ 	lw	$t2,0x24($sp)
/*    41d70:	00185940 */ 	sll	$t3,$t8,0x5
/*    41d74:	01785823 */ 	subu	$t3,$t3,$t8
/*    41d78:	000b58c0 */ 	sll	$t3,$t3,0x3
/*    41d7c:	01ebc821 */ 	addu	$t9,$t7,$t3
/*    41d80:	000a7080 */ 	sll	$t6,$t2,0x2
/*    41d84:	032e4821 */ 	addu	$t1,$t9,$t6
/*    41d88:	1000000b */ 	b	.L00041db8
/*    41d8c:	ad223d64 */ 	sw	$v0,0x3d64($t1)
.L00041d90:
/*    41d90:	8fad0198 */ 	lw	$t5,0x198($sp)
/*    41d94:	8fac0190 */ 	lw	$t4,0x190($sp)
/*    41d98:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    41d9c:	000d4140 */ 	sll	$t0,$t5,0x5
/*    41da0:	010d4023 */ 	subu	$t0,$t0,$t5
/*    41da4:	000840c0 */ 	sll	$t0,$t0,0x3
/*    41da8:	0188c021 */ 	addu	$t8,$t4,$t0
/*    41dac:	000f5880 */ 	sll	$t3,$t7,0x2
/*    41db0:	030b5021 */ 	addu	$t2,$t8,$t3
/*    41db4:	ad403d64 */ 	sw	$zero,0x3d64($t2)
.L00041db8:
/*    41db8:	8fb90020 */ 	lw	$t9,0x20($sp)
/*    41dbc:	13200011 */ 	beqz	$t9,.L00041e04
/*    41dc0:	00000000 */ 	nop
/*    41dc4:	8fae0190 */ 	lw	$t6,0x190($sp)
/*    41dc8:	03203025 */ 	or	$a2,$t9,$zero
/*    41dcc:	25c4001c */ 	addiu	$a0,$t6,0x1c
/*    41dd0:	0c0118b1 */ 	jal	func000462c4
/*    41dd4:	25c52020 */ 	addiu	$a1,$t6,0x2020
/*    41dd8:	8fad0198 */ 	lw	$t5,0x198($sp)
/*    41ddc:	8fa90190 */ 	lw	$t1,0x190($sp)
/*    41de0:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    41de4:	000d6140 */ 	sll	$t4,$t5,0x5
/*    41de8:	018d6023 */ 	subu	$t4,$t4,$t5
/*    41dec:	000c60c0 */ 	sll	$t4,$t4,0x3
/*    41df0:	012c4021 */ 	addu	$t0,$t1,$t4
/*    41df4:	000fc080 */ 	sll	$t8,$t7,0x2
/*    41df8:	01185821 */ 	addu	$t3,$t0,$t8
/*    41dfc:	1000000b */ 	b	.L00041e2c
/*    41e00:	ad623d98 */ 	sw	$v0,0x3d98($t3)
.L00041e04:
/*    41e04:	8fae0198 */ 	lw	$t6,0x198($sp)
/*    41e08:	8faa0190 */ 	lw	$t2,0x190($sp)
/*    41e0c:	8fa90024 */ 	lw	$t1,0x24($sp)
/*    41e10:	000ec940 */ 	sll	$t9,$t6,0x5
/*    41e14:	032ec823 */ 	subu	$t9,$t9,$t6
/*    41e18:	0019c8c0 */ 	sll	$t9,$t9,0x3
/*    41e1c:	01596821 */ 	addu	$t5,$t2,$t9
/*    41e20:	00096080 */ 	sll	$t4,$t1,0x2
/*    41e24:	01ac7821 */ 	addu	$t7,$t5,$t4
/*    41e28:	ade03d98 */ 	sw	$zero,0x3d98($t7)
.L00041e2c:
/*    41e2c:	8fa80020 */ 	lw	$t0,0x20($sp)
/*    41e30:	11000011 */ 	beqz	$t0,.L00041e78
/*    41e34:	00000000 */ 	nop
/*    41e38:	8fb80190 */ 	lw	$t8,0x190($sp)
/*    41e3c:	01003025 */ 	or	$a2,$t0,$zero
/*    41e40:	2704001c */ 	addiu	$a0,$t8,0x1c
/*    41e44:	0c0118b1 */ 	jal	func000462c4
/*    41e48:	27052020 */ 	addiu	$a1,$t8,0x2020
/*    41e4c:	8fae0198 */ 	lw	$t6,0x198($sp)
/*    41e50:	8fab0190 */ 	lw	$t3,0x190($sp)
/*    41e54:	8fa90024 */ 	lw	$t1,0x24($sp)
/*    41e58:	000e5140 */ 	sll	$t2,$t6,0x5
/*    41e5c:	014e5023 */ 	subu	$t2,$t2,$t6
/*    41e60:	000a50c0 */ 	sll	$t2,$t2,0x3
/*    41e64:	016ac821 */ 	addu	$t9,$t3,$t2
/*    41e68:	00096880 */ 	sll	$t5,$t1,0x2
/*    41e6c:	032d6021 */ 	addu	$t4,$t9,$t5
/*    41e70:	1000000b */ 	b	.L00041ea0
/*    41e74:	ad823dcc */ 	sw	$v0,0x3dcc($t4)
.L00041e78:
/*    41e78:	8fb80198 */ 	lw	$t8,0x198($sp)
/*    41e7c:	8faf0190 */ 	lw	$t7,0x190($sp)
/*    41e80:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    41e84:	00184140 */ 	sll	$t0,$t8,0x5
/*    41e88:	01184023 */ 	subu	$t0,$t0,$t8
/*    41e8c:	000840c0 */ 	sll	$t0,$t0,0x3
/*    41e90:	01e87021 */ 	addu	$t6,$t7,$t0
/*    41e94:	000b5080 */ 	sll	$t2,$t3,0x2
/*    41e98:	01ca4821 */ 	addu	$t1,$t6,$t2
/*    41e9c:	ad203dcc */ 	sw	$zero,0x3dcc($t1)
.L00041ea0:
/*    41ea0:	8fb90198 */ 	lw	$t9,0x198($sp)
/*    41ea4:	13200007 */ 	beqz	$t9,.L00041ec4
/*    41ea8:	00000000 */ 	nop
/*    41eac:	8fb80024 */ 	lw	$t8,0x24($sp)
/*    41eb0:	8fac0190 */ 	lw	$t4,0x190($sp)
/*    41eb4:	8fad001c */ 	lw	$t5,0x1c($sp)
/*    41eb8:	00187880 */ 	sll	$t7,$t8,0x2
/*    41ebc:	018f4021 */ 	addu	$t0,$t4,$t7
/*    41ec0:	ad0d3f14 */ 	sw	$t5,0x3f14($t0)
.L00041ec4:
/*    41ec4:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    41ec8:	256e0001 */ 	addiu	$t6,$t3,0x1
/*    41ecc:	afae0024 */ 	sw	$t6,0x24($sp)
/*    41ed0:	8faa003c */ 	lw	$t2,0x3c($sp)
/*    41ed4:	8fb90040 */ 	lw	$t9,0x40($sp)
/*    41ed8:	25490003 */ 	addiu	$t1,$t2,0x3
/*    41edc:	0019c080 */ 	sll	$t8,$t9,0x2
/*    41ee0:	03b86021 */ 	addu	$t4,$sp,$t8
/*    41ee4:	afa9003c */ 	sw	$t1,0x3c($sp)
/*    41ee8:	8d8c0028 */ 	lw	$t4,0x28($t4)
/*    41eec:	012c082a */ 	slt	$at,$t1,$t4
/*    41ef0:	1420ff94 */ 	bnez	$at,.L00041d44
/*    41ef4:	00000000 */ 	nop
.L00041ef8:
/*    41ef8:	8faf0040 */ 	lw	$t7,0x40($sp)
/*    41efc:	25ed0001 */ 	addiu	$t5,$t7,0x1
/*    41f00:	29a10004 */ 	slti	$at,$t5,0x4
/*    41f04:	1420ff7e */ 	bnez	$at,.L00041d00
/*    41f08:	afad0040 */ 	sw	$t5,0x40($sp)
/*    41f0c:	100000c2 */ 	b	.L00042218
/*    41f10:	00000000 */ 	nop
.L00041f14:
/*    41f14:	27a80060 */ 	addiu	$t0,$sp,0x60
/*    41f18:	8d0b0000 */ 	lw	$t3,0x0($t0)
/*    41f1c:	afab0020 */ 	sw	$t3,0x20($sp)
/*    41f20:	8fae0020 */ 	lw	$t6,0x20($sp)
/*    41f24:	240a0001 */ 	addiu	$t2,$zero,0x1
/*    41f28:	01cac804 */ 	sllv	$t9,$t2,$t6
/*    41f2c:	2738ffff */ 	addiu	$t8,$t9,-1
/*    41f30:	afb8001c */ 	sw	$t8,0x1c($sp)
/*    41f34:	afa0003c */ 	sw	$zero,0x3c($sp)
.L00041f38:
/*    41f38:	8fa90020 */ 	lw	$t1,0x20($sp)
/*    41f3c:	11200011 */ 	beqz	$t1,.L00041f84
/*    41f40:	00000000 */ 	nop
/*    41f44:	8fac0190 */ 	lw	$t4,0x190($sp)
/*    41f48:	01203025 */ 	or	$a2,$t1,$zero
/*    41f4c:	2584001c */ 	addiu	$a0,$t4,0x1c
/*    41f50:	0c0118b1 */ 	jal	func000462c4
/*    41f54:	25852020 */ 	addiu	$a1,$t4,0x2020
/*    41f58:	8fad0198 */ 	lw	$t5,0x198($sp)
/*    41f5c:	8faf0190 */ 	lw	$t7,0x190($sp)
/*    41f60:	8faa0024 */ 	lw	$t2,0x24($sp)
/*    41f64:	000d4140 */ 	sll	$t0,$t5,0x5
/*    41f68:	010d4023 */ 	subu	$t0,$t0,$t5
/*    41f6c:	000840c0 */ 	sll	$t0,$t0,0x3
/*    41f70:	01e85821 */ 	addu	$t3,$t7,$t0
/*    41f74:	000a7080 */ 	sll	$t6,$t2,0x2
/*    41f78:	016ec821 */ 	addu	$t9,$t3,$t6
/*    41f7c:	1000000b */ 	b	.L00041fac
/*    41f80:	af223d08 */ 	sw	$v0,0x3d08($t9)
.L00041f84:
/*    41f84:	8fac0198 */ 	lw	$t4,0x198($sp)
/*    41f88:	8fb80190 */ 	lw	$t8,0x190($sp)
/*    41f8c:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    41f90:	000c4940 */ 	sll	$t1,$t4,0x5
/*    41f94:	012c4823 */ 	subu	$t1,$t1,$t4
/*    41f98:	000948c0 */ 	sll	$t1,$t1,0x3
/*    41f9c:	03096821 */ 	addu	$t5,$t8,$t1
/*    41fa0:	000f4080 */ 	sll	$t0,$t7,0x2
/*    41fa4:	01a85021 */ 	addu	$t2,$t5,$t0
/*    41fa8:	ad403d08 */ 	sw	$zero,0x3d08($t2)
.L00041fac:
/*    41fac:	8fab0198 */ 	lw	$t3,0x198($sp)
/*    41fb0:	11600007 */ 	beqz	$t3,.L00041fd0
/*    41fb4:	00000000 */ 	nop
/*    41fb8:	8fac0024 */ 	lw	$t4,0x24($sp)
/*    41fbc:	8fb90190 */ 	lw	$t9,0x190($sp)
/*    41fc0:	8fae001c */ 	lw	$t6,0x1c($sp)
/*    41fc4:	000cc080 */ 	sll	$t8,$t4,0x2
/*    41fc8:	03384821 */ 	addu	$t1,$t9,$t8
/*    41fcc:	ad2e3efc */ 	sw	$t6,0x3efc($t1)
.L00041fd0:
/*    41fd0:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    41fd4:	25ed0001 */ 	addiu	$t5,$t7,0x1
/*    41fd8:	afad0024 */ 	sw	$t5,0x24($sp)
/*    41fdc:	8fa8003c */ 	lw	$t0,0x3c($sp)
/*    41fe0:	250a0001 */ 	addiu	$t2,$t0,0x1
/*    41fe4:	29410006 */ 	slti	$at,$t2,0x6
/*    41fe8:	1420ffd3 */ 	bnez	$at,.L00041f38
/*    41fec:	afaa003c */ 	sw	$t2,0x3c($sp)
/*    41ff0:	27ab0028 */ 	addiu	$t3,$sp,0x28
/*    41ff4:	8d6c0000 */ 	lw	$t4,0x0($t3)
/*    41ff8:	2599fffa */ 	addiu	$t9,$t4,-6
/*    41ffc:	ad790000 */ 	sw	$t9,0x0($t3)
/*    42000:	24180003 */ 	addiu	$t8,$zero,0x3
/*    42004:	afb80024 */ 	sw	$t8,0x24($sp)
/*    42008:	afa00040 */ 	sw	$zero,0x40($sp)
.L0004200c:
/*    4200c:	8fae0040 */ 	lw	$t6,0x40($sp)
/*    42010:	000e4880 */ 	sll	$t1,$t6,0x2
/*    42014:	03a97821 */ 	addu	$t7,$sp,$t1
/*    42018:	8def0060 */ 	lw	$t7,0x60($t7)
/*    4201c:	afaf0020 */ 	sw	$t7,0x20($sp)
/*    42020:	8fad0020 */ 	lw	$t5,0x20($sp)
/*    42024:	24080001 */ 	addiu	$t0,$zero,0x1
/*    42028:	01a85004 */ 	sllv	$t2,$t0,$t5
/*    4202c:	254cffff */ 	addiu	$t4,$t2,-1
/*    42030:	afac001c */ 	sw	$t4,0x1c($sp)
/*    42034:	8fb90040 */ 	lw	$t9,0x40($sp)
/*    42038:	afa0003c */ 	sw	$zero,0x3c($sp)
/*    4203c:	00195880 */ 	sll	$t3,$t9,0x2
/*    42040:	03abc021 */ 	addu	$t8,$sp,$t3
/*    42044:	8f180028 */ 	lw	$t8,0x28($t8)
/*    42048:	1b00006e */ 	blez	$t8,.L00042204
/*    4204c:	00000000 */ 	nop
.L00042050:
/*    42050:	8fae0020 */ 	lw	$t6,0x20($sp)
/*    42054:	11c00011 */ 	beqz	$t6,.L0004209c
/*    42058:	00000000 */ 	nop
/*    4205c:	8fa90190 */ 	lw	$t1,0x190($sp)
/*    42060:	01c03025 */ 	or	$a2,$t6,$zero
/*    42064:	2524001c */ 	addiu	$a0,$t1,0x1c
/*    42068:	0c0118b1 */ 	jal	func000462c4
/*    4206c:	25252020 */ 	addiu	$a1,$t1,0x2020
/*    42070:	8fa80198 */ 	lw	$t0,0x198($sp)
/*    42074:	8faf0190 */ 	lw	$t7,0x190($sp)
/*    42078:	8fac0024 */ 	lw	$t4,0x24($sp)
/*    4207c:	00086940 */ 	sll	$t5,$t0,0x5
/*    42080:	01a86823 */ 	subu	$t5,$t5,$t0
/*    42084:	000d68c0 */ 	sll	$t5,$t5,0x3
/*    42088:	01ed5021 */ 	addu	$t2,$t7,$t5
/*    4208c:	000cc880 */ 	sll	$t9,$t4,0x2
/*    42090:	01595821 */ 	addu	$t3,$t2,$t9
/*    42094:	1000000b */ 	b	.L000420c4
/*    42098:	ad623d64 */ 	sw	$v0,0x3d64($t3)
.L0004209c:
/*    4209c:	8fa90198 */ 	lw	$t1,0x198($sp)
/*    420a0:	8fb80190 */ 	lw	$t8,0x190($sp)
/*    420a4:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    420a8:	00097140 */ 	sll	$t6,$t1,0x5
/*    420ac:	01c97023 */ 	subu	$t6,$t6,$t1
/*    420b0:	000e70c0 */ 	sll	$t6,$t6,0x3
/*    420b4:	030e4021 */ 	addu	$t0,$t8,$t6
/*    420b8:	000f6880 */ 	sll	$t5,$t7,0x2
/*    420bc:	010d6021 */ 	addu	$t4,$t0,$t5
/*    420c0:	ad803d64 */ 	sw	$zero,0x3d64($t4)
.L000420c4:
/*    420c4:	8faa0020 */ 	lw	$t2,0x20($sp)
/*    420c8:	11400011 */ 	beqz	$t2,.L00042110
/*    420cc:	00000000 */ 	nop
/*    420d0:	8fb90190 */ 	lw	$t9,0x190($sp)
/*    420d4:	01403025 */ 	or	$a2,$t2,$zero
/*    420d8:	2724001c */ 	addiu	$a0,$t9,0x1c
/*    420dc:	0c0118b1 */ 	jal	func000462c4
/*    420e0:	27252020 */ 	addiu	$a1,$t9,0x2020
/*    420e4:	8fa90198 */ 	lw	$t1,0x198($sp)
/*    420e8:	8fab0190 */ 	lw	$t3,0x190($sp)
/*    420ec:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    420f0:	0009c140 */ 	sll	$t8,$t1,0x5
/*    420f4:	0309c023 */ 	subu	$t8,$t8,$t1
/*    420f8:	0018c0c0 */ 	sll	$t8,$t8,0x3
/*    420fc:	01787021 */ 	addu	$t6,$t3,$t8
/*    42100:	000f4080 */ 	sll	$t0,$t7,0x2
/*    42104:	01c86821 */ 	addu	$t5,$t6,$t0
/*    42108:	1000000b */ 	b	.L00042138
/*    4210c:	ada23d98 */ 	sw	$v0,0x3d98($t5)
.L00042110:
/*    42110:	8fb90198 */ 	lw	$t9,0x198($sp)
/*    42114:	8fac0190 */ 	lw	$t4,0x190($sp)
/*    42118:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    4211c:	00195140 */ 	sll	$t2,$t9,0x5
/*    42120:	01595023 */ 	subu	$t2,$t2,$t9
/*    42124:	000a50c0 */ 	sll	$t2,$t2,0x3
/*    42128:	018a4821 */ 	addu	$t1,$t4,$t2
/*    4212c:	000bc080 */ 	sll	$t8,$t3,0x2
/*    42130:	01387821 */ 	addu	$t7,$t1,$t8
/*    42134:	ade03d98 */ 	sw	$zero,0x3d98($t7)
.L00042138:
/*    42138:	8fae0020 */ 	lw	$t6,0x20($sp)
/*    4213c:	11c00011 */ 	beqz	$t6,.L00042184
/*    42140:	00000000 */ 	nop
/*    42144:	8fa80190 */ 	lw	$t0,0x190($sp)
/*    42148:	01c03025 */ 	or	$a2,$t6,$zero
/*    4214c:	2504001c */ 	addiu	$a0,$t0,0x1c
/*    42150:	0c0118b1 */ 	jal	func000462c4
/*    42154:	25052020 */ 	addiu	$a1,$t0,0x2020
/*    42158:	8fb90198 */ 	lw	$t9,0x198($sp)
/*    4215c:	8fad0190 */ 	lw	$t5,0x190($sp)
/*    42160:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    42164:	00196140 */ 	sll	$t4,$t9,0x5
/*    42168:	01996023 */ 	subu	$t4,$t4,$t9
/*    4216c:	000c60c0 */ 	sll	$t4,$t4,0x3
/*    42170:	01ac5021 */ 	addu	$t2,$t5,$t4
/*    42174:	000b4880 */ 	sll	$t1,$t3,0x2
/*    42178:	0149c021 */ 	addu	$t8,$t2,$t1
/*    4217c:	1000000b */ 	b	.L000421ac
/*    42180:	af023dcc */ 	sw	$v0,0x3dcc($t8)
.L00042184:
/*    42184:	8fa80198 */ 	lw	$t0,0x198($sp)
/*    42188:	8faf0190 */ 	lw	$t7,0x190($sp)
/*    4218c:	8fad0024 */ 	lw	$t5,0x24($sp)
/*    42190:	00087140 */ 	sll	$t6,$t0,0x5
/*    42194:	01c87023 */ 	subu	$t6,$t6,$t0
/*    42198:	000e70c0 */ 	sll	$t6,$t6,0x3
/*    4219c:	01eec821 */ 	addu	$t9,$t7,$t6
/*    421a0:	000d6080 */ 	sll	$t4,$t5,0x2
/*    421a4:	032c5821 */ 	addu	$t3,$t9,$t4
/*    421a8:	ad603dcc */ 	sw	$zero,0x3dcc($t3)
.L000421ac:
/*    421ac:	8faa0198 */ 	lw	$t2,0x198($sp)
/*    421b0:	11400007 */ 	beqz	$t2,.L000421d0
/*    421b4:	00000000 */ 	nop
/*    421b8:	8fa80024 */ 	lw	$t0,0x24($sp)
/*    421bc:	8fb80190 */ 	lw	$t8,0x190($sp)
/*    421c0:	8fa9001c */ 	lw	$t1,0x1c($sp)
/*    421c4:	00087880 */ 	sll	$t7,$t0,0x2
/*    421c8:	030f7021 */ 	addu	$t6,$t8,$t7
/*    421cc:	adc93f14 */ 	sw	$t1,0x3f14($t6)
.L000421d0:
/*    421d0:	8fad0024 */ 	lw	$t5,0x24($sp)
/*    421d4:	25b90001 */ 	addiu	$t9,$t5,0x1
/*    421d8:	afb90024 */ 	sw	$t9,0x24($sp)
/*    421dc:	8fac003c */ 	lw	$t4,0x3c($sp)
/*    421e0:	8faa0040 */ 	lw	$t2,0x40($sp)
/*    421e4:	258b0003 */ 	addiu	$t3,$t4,0x3
/*    421e8:	000a4080 */ 	sll	$t0,$t2,0x2
/*    421ec:	03a8c021 */ 	addu	$t8,$sp,$t0
/*    421f0:	afab003c */ 	sw	$t3,0x3c($sp)
/*    421f4:	8f180028 */ 	lw	$t8,0x28($t8)
/*    421f8:	0178082a */ 	slt	$at,$t3,$t8
/*    421fc:	1420ff94 */ 	bnez	$at,.L00042050
/*    42200:	00000000 */ 	nop
.L00042204:
/*    42204:	8faf0040 */ 	lw	$t7,0x40($sp)
/*    42208:	25e90001 */ 	addiu	$t1,$t7,0x1
/*    4220c:	29210004 */ 	slti	$at,$t1,0x4
/*    42210:	1420ff7e */ 	bnez	$at,.L0004200c
/*    42214:	afa90040 */ 	sw	$t1,0x40($sp)
.L00042218:
/*    42218:	10000003 */ 	b	.L00042228
/*    4221c:	24020001 */ 	addiu	$v0,$zero,0x1
/*    42220:	10000001 */ 	b	.L00042228
/*    42224:	00000000 */ 	nop
.L00042228:
/*    42228:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*    4222c:	27bd0190 */ 	addiu	$sp,$sp,0x190
/*    42230:	03e00008 */ 	jr	$ra
/*    42234:	00000000 */ 	nop
);

extern u32 var8009c650[34];

bool func00042238(struct asistream *stream, u32 gr, u32 ch)
{
	s32 sp64 = stream->unk2020;
	s32 sp60;
	s32 sp54[3];
	const s16 *sp50;
	const u8 *sp4c;
	s32 sp48;
	u8 *sp44;
	u8 *sp40;
	s32 i;
	u32 sp38;
	s32 sp34;
	s32 sp30;
	s32 sp2c;
	s32 sp28;

	if (stream->unk3ba4) {
		func00040dac(stream, gr, ch);
	} else {
		func00041600(stream, gr, ch);
	}

	sp60 = stream->unk3c80[gr][ch] * 2;
	sp50 = var70057860[stream->unk3ba4][stream->unk3bb4];
	sp4c = var70057968[stream->unk3ba4][stream->unk3bb4];

	if (stream->unk3c98[gr][ch] == 0 && stream->blocktypes[gr][ch] == 0) {
		sp54[0] = sp50[stream->unk3ce0[gr][ch]] + 1;

		if (sp54[0] > sp60) {
			sp54[0] = sp54[1] = sp60;
		} else {
			sp54[1] = sp50[stream->unk3ce0[gr][ch] + stream->unk3ce8[gr][ch] + 1] + 1;

			if (sp54[1] > sp60) {
				sp54[1] = sp60;
			}
		}
	} else {
		if (stream->blocktypes[gr][ch] == 2 && stream->unk3ca8[gr][ch] == 0) {
			sp54[0] = sp4c[2] * 3 + 3;
		} else {
			sp54[0] = sp50[7] + 1;
		}

		if (sp54[0] > sp60) {
			sp54[0] = sp60;
		}

		sp54[1] = sp60;
	}

	sp54[2] = sp60;
	sp48 = 0;
	sp44 = stream->unk3f94[ch];
	sp40 = stream->unk4418[ch];

	for (i = 0; i < 3; i++) {
		sp38 = stream->unk3cb0[gr][ch][i];
		sp34 = var700577d8[sp38];
		sp30 = sp54[i];

		if (var8009c650[sp38] == 0) {
			sp2c = sp30 - sp48;

			bzero(sp44, sp2c * 2);

			sp44 += sp2c * 2;
			sp40 += sp2c;
			sp48 = sp30;
		} else {
			sp48 = func000462f8(stream->unk1c, &stream->unk2020, sp38, sp48, sp34, sp30, &sp44, &sp40);
		}
	}

	sp38 = stream->unk3d00[gr][ch] + 32;
	sp28 = stream->unk3c78[gr][ch] + sp64;
	sp48 = func000464a8(stream->unk1c, &stream->unk2020, sp38, sp48, sp28, &sp44, &sp40);
	stream->unk2020 = sp28;

	if (sp48 > 576) {
		stream->unk465c[ch] = 576;
	} else {
		stream->unk465c[ch] = sp48;
	}

	if (sp48 < 576) {
		stream->unk4660[ch] = 576 - sp48;
		bzero(sp44, stream->unk4660[ch] * 2);
	} else {
		stream->unk4660[ch] = 0;
	}

	return true;
}

bool func000427d8(struct asistream *stream, u32 gr)
{
	const s16 *sp14 = var70057b9c[stream->unk3ba4][stream->unk3bb4];
	f32 *sp10 = stream->unk4f64[0][0].unk00;
	f32 *sp0c = stream->unk4664[0].unk00;
	s32 i = 0;

	if (stream->unk3c98[gr][0] && stream->unk3c98[gr][2] == 2) {
		if (stream->unk3c98[gr][4]) {
			while (i++ < 36) {
				*(sp10++) = *(sp0c++);
			}
		}

		while (i < 576) {
			sp10[sp14[i++]] = *(sp0c++);
		}
	} else {
		while (i++ < 576) {
			*(sp10++) = *(sp0c++);
		}
	}

	return true;
}

bool func00042990(struct asistream *stream, u32 gr, u32 ch)
{
	s32 i;

	if (stream->unk3c98[gr][ch] && stream->blocktypes[gr][ch] == 2) {
		return true;
	}

	for (i = 1; i < 32; i++) {
		struct asistream_4f64 *sp08 = &stream->unk4f64[ch][i];
		f32 sp04;
		f32 sp00;

		sp04 = sp08->unk00[0];
		sp00 = sp08->unk00[-1];
		sp08->unk00[-1] = sp00 * var700596bc[0] - var7005969c[0] * sp04;
		sp08->unk00[0] = sp04 * var700596bc[0] + var7005969c[0] * sp00;

		sp04 = sp08->unk00[1];
		sp00 = sp08->unk00[-2];
		sp08->unk00[-2] = sp00 * var700596bc[1] - var7005969c[1] * sp04;
		sp08->unk00[1] = sp04 * var700596bc[1] + var7005969c[1] * sp00;

		sp04 = sp08->unk00[2];
		sp00 = sp08->unk00[-3];
		sp08->unk00[-3] = sp00 * var700596bc[2] - var7005969c[2] * sp04;
		sp08->unk00[2] = sp04 * var700596bc[2] + var7005969c[2] * sp00;

		sp04 = sp08->unk00[3];
		sp00 = sp08->unk00[-4];
		sp08->unk00[-4] = sp00 * var700596bc[3] - var7005969c[3] * sp04;
		sp08->unk00[3] = sp04 * var700596bc[3] + var7005969c[3] * sp00;

		sp04 = sp08->unk00[4];
		sp00 = sp08->unk00[-5];
		sp08->unk00[-5] = sp00 * var700596bc[4] - var7005969c[4] * sp04;
		sp08->unk00[4] = sp04 * var700596bc[4] + var7005969c[4] * sp00;

		sp04 = sp08->unk00[5];
		sp00 = sp08->unk00[-6];
		sp08->unk00[-6] = sp00 * var700596bc[5] - var7005969c[5] * sp04;
		sp08->unk00[5] = sp04 * var700596bc[5] + var7005969c[5] * sp00;

		sp04 = sp08->unk00[6];
		sp00 = sp08->unk00[-7];
		sp08->unk00[-7] = sp00 * var700596bc[6] - var7005969c[6] * sp04;
		sp08->unk00[6] = sp04 * var700596bc[6] + var7005969c[6] * sp00;

		sp04 = sp08->unk00[7];
		sp00 = sp08->unk00[-8];
		sp08->unk00[-8] = sp00 * var700596bc[7] - var7005969c[7] * sp04;
		sp08->unk00[7] = sp04 * var700596bc[7] + var7005969c[7] * sp00;
	}

	return true;
}

GLOBAL_ASM(
glabel func00042e38
/*    42e38:	27bdffc8 */ 	addiu	$sp,$sp,-56
/*    42e3c:	afbf0014 */ 	sw	$ra,0x14($sp)
/*    42e40:	afa40038 */ 	sw	$a0,0x38($sp)
/*    42e44:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    42e48:	8dcf3ba4 */ 	lw	$t7,0x3ba4($t6)
/*    42e4c:	11e0000e */ 	beqz	$t7,.L00042e88
/*    42e50:	00000000 */ 	nop
/*    42e54:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    42e58:	24010003 */ 	addiu	$at,$zero,0x3
/*    42e5c:	8f193bc0 */ 	lw	$t9,0x3bc0($t8)
/*    42e60:	17210004 */ 	bne	$t9,$at,.L00042e74
/*    42e64:	00000000 */ 	nop
/*    42e68:	24080011 */ 	addiu	$t0,$zero,0x11
/*    42e6c:	10000004 */ 	b	.L00042e80
/*    42e70:	af08206c */ 	sw	$t0,0x206c($t8)
.L00042e74:
/*    42e74:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    42e78:	24090020 */ 	addiu	$t1,$zero,0x20
/*    42e7c:	ad49206c */ 	sw	$t1,0x206c($t2)
.L00042e80:
/*    42e80:	1000000c */ 	b	.L00042eb4
/*    42e84:	00000000 */ 	nop
.L00042e88:
/*    42e88:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    42e8c:	24010003 */ 	addiu	$at,$zero,0x3
/*    42e90:	8d6c3bc0 */ 	lw	$t4,0x3bc0($t3)
/*    42e94:	15810004 */ 	bne	$t4,$at,.L00042ea8
/*    42e98:	00000000 */ 	nop
/*    42e9c:	240d0009 */ 	addiu	$t5,$zero,0x9
/*    42ea0:	10000004 */ 	b	.L00042eb4
/*    42ea4:	ad6d206c */ 	sw	$t5,0x206c($t3)
.L00042ea8:
/*    42ea8:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    42eac:	240e0011 */ 	addiu	$t6,$zero,0x11
/*    42eb0:	adee206c */ 	sw	$t6,0x206c($t7)
.L00042eb4:
/*    42eb4:	8fb90038 */ 	lw	$t9,0x38($sp)
/*    42eb8:	2407ffff */ 	addiu	$a3,$zero,-1
/*    42ebc:	8f282068 */ 	lw	$t0,0x2068($t9)
/*    42ec0:	8f240000 */ 	lw	$a0,0x0($t9)
/*    42ec4:	8f26206c */ 	lw	$a2,0x206c($t9)
/*    42ec8:	03282821 */ 	addu	$a1,$t9,$t0
/*    42ecc:	8f390004 */ 	lw	$t9,0x4($t9)
/*    42ed0:	24a52024 */ 	addiu	$a1,$a1,0x2024
/*    42ed4:	0320f809 */ 	jalr	$t9
/*    42ed8:	00000000 */ 	nop
/*    42edc:	afa20034 */ 	sw	$v0,0x34($sp)
/*    42ee0:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    42ee4:	8faa0034 */ 	lw	$t2,0x34($sp)
/*    42ee8:	8f09206c */ 	lw	$t1,0x206c($t8)
/*    42eec:	112a0003 */ 	beq	$t1,$t2,.L00042efc
/*    42ef0:	00000000 */ 	nop
/*    42ef4:	10000205 */ 	b	.L0004370c
/*    42ef8:	00001025 */ 	or	$v0,$zero,$zero
.L00042efc:
/*    42efc:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    42f00:	8d8d0018 */ 	lw	$t5,0x18($t4)
/*    42f04:	8d8b206c */ 	lw	$t3,0x206c($t4)
/*    42f08:	01ab7021 */ 	addu	$t6,$t5,$t3
/*    42f0c:	ad8e0018 */ 	sw	$t6,0x18($t4)
/*    42f10:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    42f14:	24010003 */ 	addiu	$at,$zero,0x3
/*    42f18:	8de83bc0 */ 	lw	$t0,0x3bc0($t7)
/*    42f1c:	15010004 */ 	bne	$t0,$at,.L00042f30
/*    42f20:	00000000 */ 	nop
/*    42f24:	24190001 */ 	addiu	$t9,$zero,0x1
/*    42f28:	10000004 */ 	b	.L00042f3c
/*    42f2c:	adf93f8c */ 	sw	$t9,0x3f8c($t7)
.L00042f30:
/*    42f30:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    42f34:	24180002 */ 	addiu	$t8,$zero,0x2
/*    42f38:	ad383f8c */ 	sw	$t8,0x3f8c($t1)
.L00042f3c:
/*    42f3c:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    42f40:	8d4d3ba4 */ 	lw	$t5,0x3ba4($t2)
/*    42f44:	11a00004 */ 	beqz	$t5,.L00042f58
/*    42f48:	00000000 */ 	nop
/*    42f4c:	240b0002 */ 	addiu	$t3,$zero,0x2
/*    42f50:	10000004 */ 	b	.L00042f64
/*    42f54:	ad4b3f90 */ 	sw	$t3,0x3f90($t2)
.L00042f58:
/*    42f58:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    42f5c:	240e0001 */ 	addiu	$t6,$zero,0x1
/*    42f60:	ad8e3f90 */ 	sw	$t6,0x3f90($t4)
.L00042f64:
/*    42f64:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    42f68:	8d193ba4 */ 	lw	$t9,0x3ba4($t0)
/*    42f6c:	1320001a */ 	beqz	$t9,.L00042fd8
/*    42f70:	00000000 */ 	nop
/*    42f74:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    42f78:	24060009 */ 	addiu	$a2,$zero,0x9
/*    42f7c:	25e42024 */ 	addiu	$a0,$t7,0x2024
/*    42f80:	0c0118b1 */ 	jal	func000462c4
/*    42f84:	25e52064 */ 	addiu	$a1,$t7,0x2064
/*    42f88:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    42f8c:	af023bf4 */ 	sw	$v0,0x3bf4($t8)
/*    42f90:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    42f94:	24010001 */ 	addiu	$at,$zero,0x1
/*    42f98:	8d2d3f8c */ 	lw	$t5,0x3f8c($t1)
/*    42f9c:	15a10007 */ 	bne	$t5,$at,.L00042fbc
/*    42fa0:	00000000 */ 	nop
/*    42fa4:	25242024 */ 	addiu	$a0,$t1,0x2024
/*    42fa8:	25252064 */ 	addiu	$a1,$t1,0x2064
/*    42fac:	0c0118b1 */ 	jal	func000462c4
/*    42fb0:	24060005 */ 	addiu	$a2,$zero,0x5
/*    42fb4:	10000006 */ 	b	.L00042fd0
/*    42fb8:	00000000 */ 	nop
.L00042fbc:
/*    42fbc:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    42fc0:	24060003 */ 	addiu	$a2,$zero,0x3
/*    42fc4:	25642024 */ 	addiu	$a0,$t3,0x2024
/*    42fc8:	0c0118b1 */ 	jal	func000462c4
/*    42fcc:	25652064 */ 	addiu	$a1,$t3,0x2064
.L00042fd0:
/*    42fd0:	10000018 */ 	b	.L00043034
/*    42fd4:	00000000 */ 	nop
.L00042fd8:
/*    42fd8:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    42fdc:	24060008 */ 	addiu	$a2,$zero,0x8
/*    42fe0:	25442024 */ 	addiu	$a0,$t2,0x2024
/*    42fe4:	0c0118b1 */ 	jal	func000462c4
/*    42fe8:	25452064 */ 	addiu	$a1,$t2,0x2064
/*    42fec:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    42ff0:	adc23bf4 */ 	sw	$v0,0x3bf4($t6)
/*    42ff4:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    42ff8:	24010001 */ 	addiu	$at,$zero,0x1
/*    42ffc:	8d883f8c */ 	lw	$t0,0x3f8c($t4)
/*    43000:	15010007 */ 	bne	$t0,$at,.L00043020
/*    43004:	00000000 */ 	nop
/*    43008:	25842024 */ 	addiu	$a0,$t4,0x2024
/*    4300c:	25852064 */ 	addiu	$a1,$t4,0x2064
/*    43010:	0c0118b1 */ 	jal	func000462c4
/*    43014:	24060001 */ 	addiu	$a2,$zero,0x1
/*    43018:	10000006 */ 	b	.L00043034
/*    4301c:	00000000 */ 	nop
.L00043020:
/*    43020:	8fb90038 */ 	lw	$t9,0x38($sp)
/*    43024:	24060002 */ 	addiu	$a2,$zero,0x2
/*    43028:	27242024 */ 	addiu	$a0,$t9,0x2024
/*    4302c:	0c0118b1 */ 	jal	func000462c4
/*    43030:	27252064 */ 	addiu	$a1,$t9,0x2064
.L00043034:
/*    43034:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    43038:	8df83ba4 */ 	lw	$t8,0x3ba4($t7)
/*    4303c:	13000021 */ 	beqz	$t8,.L000430c4
/*    43040:	00000000 */ 	nop
/*    43044:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    43048:	afa00030 */ 	sw	$zero,0x30($sp)
/*    4304c:	8da93f8c */ 	lw	$t1,0x3f8c($t5)
/*    43050:	1920001c */ 	blez	$t1,.L000430c4
/*    43054:	00000000 */ 	nop
.L00043058:
/*    43058:	afa0002c */ 	sw	$zero,0x2c($sp)
.L0004305c:
/*    4305c:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    43060:	24060001 */ 	addiu	$a2,$zero,0x1
/*    43064:	25642024 */ 	addiu	$a0,$t3,0x2024
/*    43068:	0c0118b1 */ 	jal	func000462c4
/*    4306c:	25652064 */ 	addiu	$a1,$t3,0x2064
/*    43070:	8fae0030 */ 	lw	$t6,0x30($sp)
/*    43074:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    43078:	8fb9002c */ 	lw	$t9,0x2c($sp)
/*    4307c:	000e41c0 */ 	sll	$t0,$t6,0x7
/*    43080:	01486021 */ 	addu	$t4,$t2,$t0
/*    43084:	00197880 */ 	sll	$t7,$t9,0x2
/*    43088:	018fc021 */ 	addu	$t8,$t4,$t7
/*    4308c:	af023bf8 */ 	sw	$v0,0x3bf8($t8)
/*    43090:	8fad002c */ 	lw	$t5,0x2c($sp)
/*    43094:	25a90001 */ 	addiu	$t1,$t5,0x1
/*    43098:	29210004 */ 	slti	$at,$t1,0x4
/*    4309c:	1420ffef */ 	bnez	$at,.L0004305c
/*    430a0:	afa9002c */ 	sw	$t1,0x2c($sp)
/*    430a4:	8fab0030 */ 	lw	$t3,0x30($sp)
/*    430a8:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    430ac:	256e0001 */ 	addiu	$t6,$t3,0x1
/*    430b0:	afae0030 */ 	sw	$t6,0x30($sp)
/*    430b4:	8d483f8c */ 	lw	$t0,0x3f8c($t2)
/*    430b8:	01c8082a */ 	slt	$at,$t6,$t0
/*    430bc:	1420ffe6 */ 	bnez	$at,.L00043058
/*    430c0:	00000000 */ 	nop
.L000430c4:
/*    430c4:	8fb90038 */ 	lw	$t9,0x38($sp)
/*    430c8:	8f2c3ba4 */ 	lw	$t4,0x3ba4($t9)
/*    430cc:	11800004 */ 	beqz	$t4,.L000430e0
/*    430d0:	00000000 */ 	nop
/*    430d4:	240f0004 */ 	addiu	$t7,$zero,0x4
/*    430d8:	10000003 */ 	b	.L000430e8
/*    430dc:	afaf0028 */ 	sw	$t7,0x28($sp)
.L000430e0:
/*    430e0:	24180009 */ 	addiu	$t8,$zero,0x9
/*    430e4:	afb80028 */ 	sw	$t8,0x28($sp)
.L000430e8:
/*    430e8:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    430ec:	afa00024 */ 	sw	$zero,0x24($sp)
/*    430f0:	8da93f90 */ 	lw	$t1,0x3f90($t5)
/*    430f4:	19200138 */ 	blez	$t1,.L000435d8
/*    430f8:	00000000 */ 	nop
.L000430fc:
/*    430fc:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    43100:	afa00030 */ 	sw	$zero,0x30($sp)
/*    43104:	8d6a3f8c */ 	lw	$t2,0x3f8c($t3)
/*    43108:	1940012b */ 	blez	$t2,.L000435b8
/*    4310c:	00000000 */ 	nop
.L00043110:
/*    43110:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    43114:	2406000c */ 	addiu	$a2,$zero,0xc
/*    43118:	25c42024 */ 	addiu	$a0,$t6,0x2024
/*    4311c:	0c0118b1 */ 	jal	func000462c4
/*    43120:	25c52064 */ 	addiu	$a1,$t6,0x2064
/*    43124:	8fb90024 */ 	lw	$t9,0x24($sp)
/*    43128:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    4312c:	8fb80030 */ 	lw	$t8,0x30($sp)
/*    43130:	00196080 */ 	sll	$t4,$t9,0x2
/*    43134:	010c7821 */ 	addu	$t7,$t0,$t4
/*    43138:	00186880 */ 	sll	$t5,$t8,0x2
/*    4313c:	01ed4821 */ 	addu	$t1,$t7,$t5
/*    43140:	ad223c78 */ 	sw	$v0,0x3c78($t1)
/*    43144:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    43148:	24060009 */ 	addiu	$a2,$zero,0x9
/*    4314c:	25642024 */ 	addiu	$a0,$t3,0x2024
/*    43150:	0c0118b1 */ 	jal	func000462c4
/*    43154:	25652064 */ 	addiu	$a1,$t3,0x2064
/*    43158:	8fae0024 */ 	lw	$t6,0x24($sp)
/*    4315c:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    43160:	8fac0030 */ 	lw	$t4,0x30($sp)
/*    43164:	000ec880 */ 	sll	$t9,$t6,0x2
/*    43168:	01594021 */ 	addu	$t0,$t2,$t9
/*    4316c:	000cc080 */ 	sll	$t8,$t4,0x2
/*    43170:	01187821 */ 	addu	$t7,$t0,$t8
/*    43174:	ade23c80 */ 	sw	$v0,0x3c80($t7)
/*    43178:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    4317c:	24060008 */ 	addiu	$a2,$zero,0x8
/*    43180:	25a42024 */ 	addiu	$a0,$t5,0x2024
/*    43184:	0c0118b1 */ 	jal	func000462c4
/*    43188:	25a52064 */ 	addiu	$a1,$t5,0x2064
/*    4318c:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    43190:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    43194:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    43198:	000b7080 */ 	sll	$t6,$t3,0x2
/*    4319c:	012e5021 */ 	addu	$t2,$t1,$t6
/*    431a0:	00196080 */ 	sll	$t4,$t9,0x2
/*    431a4:	014c4021 */ 	addu	$t0,$t2,$t4
/*    431a8:	ad023c88 */ 	sw	$v0,0x3c88($t0)
/*    431ac:	8fb80028 */ 	lw	$t8,0x28($sp)
/*    431b0:	1300000f */ 	beqz	$t8,.L000431f0
/*    431b4:	00000000 */ 	nop
/*    431b8:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    431bc:	03003025 */ 	or	$a2,$t8,$zero
/*    431c0:	25e42024 */ 	addiu	$a0,$t7,0x2024
/*    431c4:	0c0118b1 */ 	jal	func000462c4
/*    431c8:	25e52064 */ 	addiu	$a1,$t7,0x2064
/*    431cc:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    431d0:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    431d4:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    431d8:	000b4880 */ 	sll	$t1,$t3,0x2
/*    431dc:	01a97021 */ 	addu	$t6,$t5,$t1
/*    431e0:	00195080 */ 	sll	$t2,$t9,0x2
/*    431e4:	01ca6021 */ 	addu	$t4,$t6,$t2
/*    431e8:	10000009 */ 	b	.L00043210
/*    431ec:	ad823c90 */ 	sw	$v0,0x3c90($t4)
.L000431f0:
/*    431f0:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    431f4:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    431f8:	8fad0030 */ 	lw	$t5,0x30($sp)
/*    431fc:	000fc080 */ 	sll	$t8,$t7,0x2
/*    43200:	01185821 */ 	addu	$t3,$t0,$t8
/*    43204:	000d4880 */ 	sll	$t1,$t5,0x2
/*    43208:	0169c821 */ 	addu	$t9,$t3,$t1
/*    4320c:	af203c90 */ 	sw	$zero,0x3c90($t9)
.L00043210:
/*    43210:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    43214:	24060001 */ 	addiu	$a2,$zero,0x1
/*    43218:	25c42024 */ 	addiu	$a0,$t6,0x2024
/*    4321c:	0c0118b1 */ 	jal	func000462c4
/*    43220:	25c52064 */ 	addiu	$a1,$t6,0x2064
/*    43224:	8fac0024 */ 	lw	$t4,0x24($sp)
/*    43228:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    4322c:	8fb80030 */ 	lw	$t8,0x30($sp)
/*    43230:	000c7880 */ 	sll	$t7,$t4,0x2
/*    43234:	014f4021 */ 	addu	$t0,$t2,$t7
/*    43238:	00186880 */ 	sll	$t5,$t8,0x2
/*    4323c:	010d5821 */ 	addu	$t3,$t0,$t5
/*    43240:	ad623c98 */ 	sw	$v0,0x3c98($t3)
/*    43244:	8fb90024 */ 	lw	$t9,0x24($sp)
/*    43248:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    4324c:	8faa0030 */ 	lw	$t2,0x30($sp)
/*    43250:	00197080 */ 	sll	$t6,$t9,0x2
/*    43254:	012e6021 */ 	addu	$t4,$t1,$t6
/*    43258:	000a7880 */ 	sll	$t7,$t2,0x2
/*    4325c:	018fc021 */ 	addu	$t8,$t4,$t7
/*    43260:	8f083c98 */ 	lw	$t0,0x3c98($t8)
/*    43264:	1100005d */ 	beqz	$t0,.L000433dc
/*    43268:	00000000 */ 	nop
/*    4326c:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    43270:	24060002 */ 	addiu	$a2,$zero,0x2
/*    43274:	25a42024 */ 	addiu	$a0,$t5,0x2024
/*    43278:	0c0118b1 */ 	jal	func000462c4
/*    4327c:	25a52064 */ 	addiu	$a1,$t5,0x2064
/*    43280:	8fb90024 */ 	lw	$t9,0x24($sp)
/*    43284:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    43288:	8faa0030 */ 	lw	$t2,0x30($sp)
/*    4328c:	00194880 */ 	sll	$t1,$t9,0x2
/*    43290:	01697021 */ 	addu	$t6,$t3,$t1
/*    43294:	000a6080 */ 	sll	$t4,$t2,0x2
/*    43298:	01cc7821 */ 	addu	$t7,$t6,$t4
/*    4329c:	ade23ca0 */ 	sw	$v0,0x3ca0($t7)
/*    432a0:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    432a4:	24060001 */ 	addiu	$a2,$zero,0x1
/*    432a8:	27042024 */ 	addiu	$a0,$t8,0x2024
/*    432ac:	0c0118b1 */ 	jal	func000462c4
/*    432b0:	27052064 */ 	addiu	$a1,$t8,0x2064
/*    432b4:	8fad0024 */ 	lw	$t5,0x24($sp)
/*    432b8:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    432bc:	8fa90030 */ 	lw	$t1,0x30($sp)
/*    432c0:	000dc880 */ 	sll	$t9,$t5,0x2
/*    432c4:	01195821 */ 	addu	$t3,$t0,$t9
/*    432c8:	00095080 */ 	sll	$t2,$t1,0x2
/*    432cc:	016a7021 */ 	addu	$t6,$t3,$t2
/*    432d0:	adc23ca8 */ 	sw	$v0,0x3ca8($t6)
/*    432d4:	afa00020 */ 	sw	$zero,0x20($sp)
.L000432d8:
/*    432d8:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    432dc:	24060005 */ 	addiu	$a2,$zero,0x5
/*    432e0:	25842024 */ 	addiu	$a0,$t4,0x2024
/*    432e4:	0c0118b1 */ 	jal	func000462c4
/*    432e8:	25852064 */ 	addiu	$a1,$t4,0x2064
/*    432ec:	8fb80024 */ 	lw	$t8,0x24($sp)
/*    432f0:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    432f4:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    432f8:	00186880 */ 	sll	$t5,$t8,0x2
/*    432fc:	8faa0020 */ 	lw	$t2,0x20($sp)
/*    43300:	01b86823 */ 	subu	$t5,$t5,$t8
/*    43304:	00194880 */ 	sll	$t1,$t9,0x2
/*    43308:	000d6880 */ 	sll	$t5,$t5,0x2
/*    4330c:	01394823 */ 	subu	$t1,$t1,$t9
/*    43310:	00094880 */ 	sll	$t1,$t1,0x2
/*    43314:	01ed4021 */ 	addu	$t0,$t7,$t5
/*    43318:	01095821 */ 	addu	$t3,$t0,$t1
/*    4331c:	000a7080 */ 	sll	$t6,$t2,0x2
/*    43320:	016e6021 */ 	addu	$t4,$t3,$t6
/*    43324:	ad823cb0 */ 	sw	$v0,0x3cb0($t4)
/*    43328:	8fb80020 */ 	lw	$t8,0x20($sp)
/*    4332c:	270f0001 */ 	addiu	$t7,$t8,0x1
/*    43330:	29e10002 */ 	slti	$at,$t7,0x2
/*    43334:	1420ffe8 */ 	bnez	$at,.L000432d8
/*    43338:	afaf0020 */ 	sw	$t7,0x20($sp)
/*    4333c:	8fb90024 */ 	lw	$t9,0x24($sp)
/*    43340:	8faa0030 */ 	lw	$t2,0x30($sp)
/*    43344:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    43348:	00194080 */ 	sll	$t0,$t9,0x2
/*    4334c:	01194023 */ 	subu	$t0,$t0,$t9
/*    43350:	000a5880 */ 	sll	$t3,$t2,0x2
/*    43354:	00084080 */ 	sll	$t0,$t0,0x2
/*    43358:	016a5823 */ 	subu	$t3,$t3,$t2
/*    4335c:	000b5880 */ 	sll	$t3,$t3,0x2
/*    43360:	01a84821 */ 	addu	$t1,$t5,$t0
/*    43364:	012b7021 */ 	addu	$t6,$t1,$t3
/*    43368:	adc03cb8 */ 	sw	$zero,0x3cb8($t6)
/*    4336c:	afa0001c */ 	sw	$zero,0x1c($sp)
.L00043370:
/*    43370:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    43374:	24060003 */ 	addiu	$a2,$zero,0x3
/*    43378:	25842024 */ 	addiu	$a0,$t4,0x2024
/*    4337c:	0c0118b1 */ 	jal	func000462c4
/*    43380:	25852064 */ 	addiu	$a1,$t4,0x2064
/*    43384:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    43388:	8fa80030 */ 	lw	$t0,0x30($sp)
/*    4338c:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    43390:	000fc880 */ 	sll	$t9,$t7,0x2
/*    43394:	8fab001c */ 	lw	$t3,0x1c($sp)
/*    43398:	032fc823 */ 	subu	$t9,$t9,$t7
/*    4339c:	00085080 */ 	sll	$t2,$t0,0x2
/*    433a0:	0019c880 */ 	sll	$t9,$t9,0x2
/*    433a4:	01485023 */ 	subu	$t2,$t2,$t0
/*    433a8:	000a5080 */ 	sll	$t2,$t2,0x2
/*    433ac:	03196821 */ 	addu	$t5,$t8,$t9
/*    433b0:	01aa4821 */ 	addu	$t1,$t5,$t2
/*    433b4:	000b7080 */ 	sll	$t6,$t3,0x2
/*    433b8:	012e6021 */ 	addu	$t4,$t1,$t6
/*    433bc:	ad823cc8 */ 	sw	$v0,0x3cc8($t4)
/*    433c0:	8faf001c */ 	lw	$t7,0x1c($sp)
/*    433c4:	25f80001 */ 	addiu	$t8,$t7,0x1
/*    433c8:	2b010003 */ 	slti	$at,$t8,0x3
/*    433cc:	1420ffe8 */ 	bnez	$at,.L00043370
/*    433d0:	afb8001c */ 	sw	$t8,0x1c($sp)
/*    433d4:	10000045 */ 	b	.L000434ec
/*    433d8:	00000000 */ 	nop
.L000433dc:
/*    433dc:	8fa80024 */ 	lw	$t0,0x24($sp)
/*    433e0:	8fb90038 */ 	lw	$t9,0x38($sp)
/*    433e4:	8fab0030 */ 	lw	$t3,0x30($sp)
/*    433e8:	00086880 */ 	sll	$t5,$t0,0x2
/*    433ec:	032d5021 */ 	addu	$t2,$t9,$t5
/*    433f0:	000b4880 */ 	sll	$t1,$t3,0x2
/*    433f4:	01497021 */ 	addu	$t6,$t2,$t1
/*    433f8:	adc03ca0 */ 	sw	$zero,0x3ca0($t6)
/*    433fc:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    43400:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    43404:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    43408:	000fc080 */ 	sll	$t8,$t7,0x2
/*    4340c:	01984021 */ 	addu	$t0,$t4,$t8
/*    43410:	00196880 */ 	sll	$t5,$t9,0x2
/*    43414:	010d5821 */ 	addu	$t3,$t0,$t5
/*    43418:	ad603ca8 */ 	sw	$zero,0x3ca8($t3)
/*    4341c:	afa00020 */ 	sw	$zero,0x20($sp)
.L00043420:
/*    43420:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    43424:	24060005 */ 	addiu	$a2,$zero,0x5
/*    43428:	25442024 */ 	addiu	$a0,$t2,0x2024
/*    4342c:	0c0118b1 */ 	jal	func000462c4
/*    43430:	25452064 */ 	addiu	$a1,$t2,0x2064
/*    43434:	8fae0024 */ 	lw	$t6,0x24($sp)
/*    43438:	8fb80030 */ 	lw	$t8,0x30($sp)
/*    4343c:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    43440:	000e7880 */ 	sll	$t7,$t6,0x2
/*    43444:	8fad0020 */ 	lw	$t5,0x20($sp)
/*    43448:	01ee7823 */ 	subu	$t7,$t7,$t6
/*    4344c:	0018c880 */ 	sll	$t9,$t8,0x2
/*    43450:	000f7880 */ 	sll	$t7,$t7,0x2
/*    43454:	0338c823 */ 	subu	$t9,$t9,$t8
/*    43458:	0019c880 */ 	sll	$t9,$t9,0x2
/*    4345c:	012f6021 */ 	addu	$t4,$t1,$t7
/*    43460:	01994021 */ 	addu	$t0,$t4,$t9
/*    43464:	000d5880 */ 	sll	$t3,$t5,0x2
/*    43468:	010b5021 */ 	addu	$t2,$t0,$t3
/*    4346c:	ad423cb0 */ 	sw	$v0,0x3cb0($t2)
/*    43470:	8fae0020 */ 	lw	$t6,0x20($sp)
/*    43474:	25c90001 */ 	addiu	$t1,$t6,0x1
/*    43478:	29210003 */ 	slti	$at,$t1,0x3
/*    4347c:	1420ffe8 */ 	bnez	$at,.L00043420
/*    43480:	afa90020 */ 	sw	$t1,0x20($sp)
/*    43484:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    43488:	24060004 */ 	addiu	$a2,$zero,0x4
/*    4348c:	25e42024 */ 	addiu	$a0,$t7,0x2024
/*    43490:	0c0118b1 */ 	jal	func000462c4
/*    43494:	25e52064 */ 	addiu	$a1,$t7,0x2064
/*    43498:	8fac0024 */ 	lw	$t4,0x24($sp)
/*    4349c:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    434a0:	8fa80030 */ 	lw	$t0,0x30($sp)
/*    434a4:	000cc880 */ 	sll	$t9,$t4,0x2
/*    434a8:	03196821 */ 	addu	$t5,$t8,$t9
/*    434ac:	00085880 */ 	sll	$t3,$t0,0x2
/*    434b0:	01ab5021 */ 	addu	$t2,$t5,$t3
/*    434b4:	ad423ce0 */ 	sw	$v0,0x3ce0($t2)
/*    434b8:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    434bc:	24060003 */ 	addiu	$a2,$zero,0x3
/*    434c0:	25c42024 */ 	addiu	$a0,$t6,0x2024
/*    434c4:	0c0118b1 */ 	jal	func000462c4
/*    434c8:	25c52064 */ 	addiu	$a1,$t6,0x2064
/*    434cc:	8faf0024 */ 	lw	$t7,0x24($sp)
/*    434d0:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    434d4:	8fb90030 */ 	lw	$t9,0x30($sp)
/*    434d8:	000f6080 */ 	sll	$t4,$t7,0x2
/*    434dc:	012cc021 */ 	addu	$t8,$t1,$t4
/*    434e0:	00194080 */ 	sll	$t0,$t9,0x2
/*    434e4:	03086821 */ 	addu	$t5,$t8,$t0
/*    434e8:	ada23ce8 */ 	sw	$v0,0x3ce8($t5)
.L000434ec:
/*    434ec:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    434f0:	8d6a3ba4 */ 	lw	$t2,0x3ba4($t3)
/*    434f4:	1140000e */ 	beqz	$t2,.L00043530
/*    434f8:	00000000 */ 	nop
/*    434fc:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    43500:	24060001 */ 	addiu	$a2,$zero,0x1
/*    43504:	25c42024 */ 	addiu	$a0,$t6,0x2024
/*    43508:	0c0118b1 */ 	jal	func000462c4
/*    4350c:	25c52064 */ 	addiu	$a1,$t6,0x2064
/*    43510:	8fa90024 */ 	lw	$t1,0x24($sp)
/*    43514:	8faf0038 */ 	lw	$t7,0x38($sp)
/*    43518:	8fb80030 */ 	lw	$t8,0x30($sp)
/*    4351c:	00096080 */ 	sll	$t4,$t1,0x2
/*    43520:	01ecc821 */ 	addu	$t9,$t7,$t4
/*    43524:	00184080 */ 	sll	$t0,$t8,0x2
/*    43528:	03286821 */ 	addu	$t5,$t9,$t0
/*    4352c:	ada23cf0 */ 	sw	$v0,0x3cf0($t5)
.L00043530:
/*    43530:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    43534:	24060001 */ 	addiu	$a2,$zero,0x1
/*    43538:	25642024 */ 	addiu	$a0,$t3,0x2024
/*    4353c:	0c0118b1 */ 	jal	func000462c4
/*    43540:	25652064 */ 	addiu	$a1,$t3,0x2064
/*    43544:	8fae0024 */ 	lw	$t6,0x24($sp)
/*    43548:	8faa0038 */ 	lw	$t2,0x38($sp)
/*    4354c:	8fac0030 */ 	lw	$t4,0x30($sp)
/*    43550:	000e4880 */ 	sll	$t1,$t6,0x2
/*    43554:	01497821 */ 	addu	$t7,$t2,$t1
/*    43558:	000cc080 */ 	sll	$t8,$t4,0x2
/*    4355c:	01f8c821 */ 	addu	$t9,$t7,$t8
/*    43560:	af223cf8 */ 	sw	$v0,0x3cf8($t9)
/*    43564:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    43568:	24060001 */ 	addiu	$a2,$zero,0x1
/*    4356c:	25042024 */ 	addiu	$a0,$t0,0x2024
/*    43570:	0c0118b1 */ 	jal	func000462c4
/*    43574:	25052064 */ 	addiu	$a1,$t0,0x2064
/*    43578:	8fab0024 */ 	lw	$t3,0x24($sp)
/*    4357c:	8fad0038 */ 	lw	$t5,0x38($sp)
/*    43580:	8fa90030 */ 	lw	$t1,0x30($sp)
/*    43584:	000b7080 */ 	sll	$t6,$t3,0x2
/*    43588:	01ae5021 */ 	addu	$t2,$t5,$t6
/*    4358c:	00096080 */ 	sll	$t4,$t1,0x2
/*    43590:	014c7821 */ 	addu	$t7,$t2,$t4
/*    43594:	ade23d00 */ 	sw	$v0,0x3d00($t7)
/*    43598:	8fb80030 */ 	lw	$t8,0x30($sp)
/*    4359c:	8fa80038 */ 	lw	$t0,0x38($sp)
/*    435a0:	27190001 */ 	addiu	$t9,$t8,0x1
/*    435a4:	afb90030 */ 	sw	$t9,0x30($sp)
/*    435a8:	8d0b3f8c */ 	lw	$t3,0x3f8c($t0)
/*    435ac:	032b082a */ 	slt	$at,$t9,$t3
/*    435b0:	1420fed7 */ 	bnez	$at,.L00043110
/*    435b4:	00000000 */ 	nop
.L000435b8:
/*    435b8:	8fad0024 */ 	lw	$t5,0x24($sp)
/*    435bc:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    435c0:	25ae0001 */ 	addiu	$t6,$t5,0x1
/*    435c4:	afae0024 */ 	sw	$t6,0x24($sp)
/*    435c8:	8d2a3f90 */ 	lw	$t2,0x3f90($t1)
/*    435cc:	01ca082a */ 	slt	$at,$t6,$t2
/*    435d0:	1420feca */ 	bnez	$at,.L000430fc
/*    435d4:	00000000 */ 	nop
.L000435d8:
/*    435d8:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    435dc:	3c0d7006 */ 	lui	$t5,%hi(var700596dc)
/*    435e0:	8d8f3ba4 */ 	lw	$t7,0x3ba4($t4)
/*    435e4:	8d883bb0 */ 	lw	$t0,0x3bb0($t4)
/*    435e8:	000fc100 */ 	sll	$t8,$t7,0x4
/*    435ec:	030fc023 */ 	subu	$t8,$t8,$t7
/*    435f0:	0018c080 */ 	sll	$t8,$t8,0x2
/*    435f4:	0008c880 */ 	sll	$t9,$t0,0x2
/*    435f8:	03195821 */ 	addu	$t3,$t8,$t9
/*    435fc:	01ab6821 */ 	addu	$t5,$t5,$t3
/*    43600:	8dad96dc */ 	lw	$t5,%lo(var700596dc)($t5)
/*    43604:	ad8d3f7c */ 	sw	$t5,0x3f7c($t4)
/*    43608:	8fa90038 */ 	lw	$t1,0x38($sp)
/*    4360c:	3c197006 */ 	lui	$t9,%hi(var70059754)
/*    43610:	8d2e3ba4 */ 	lw	$t6,0x3ba4($t1)
/*    43614:	8d2f3bb4 */ 	lw	$t7,0x3bb4($t1)
/*    43618:	000e5100 */ 	sll	$t2,$t6,0x4
/*    4361c:	000f4080 */ 	sll	$t0,$t7,0x2
/*    43620:	0148c021 */ 	addu	$t8,$t2,$t0
/*    43624:	0338c821 */ 	addu	$t9,$t9,$t8
/*    43628:	8f399754 */ 	lw	$t9,%lo(var70059754)($t9)
/*    4362c:	ad393f80 */ 	sw	$t9,0x3f80($t1)
/*    43630:	8fab0038 */ 	lw	$t3,0x38($sp)
/*    43634:	8d6d3ba4 */ 	lw	$t5,0x3ba4($t3)
/*    43638:	11a00015 */ 	beqz	$t5,.L00043690
/*    4363c:	00000000 */ 	nop
/*    43640:	8fac0038 */ 	lw	$t4,0x38($sp)
/*    43644:	8d8e3f7c */ 	lw	$t6,0x3f7c($t4)
/*    43648:	8d8a3f80 */ 	lw	$t2,0x3f80($t4)
/*    4364c:	000e78c0 */ 	sll	$t7,$t6,0x3
/*    43650:	01ee7821 */ 	addu	$t7,$t7,$t6
/*    43654:	000f7900 */ 	sll	$t7,$t7,0x4
/*    43658:	01ea001a */ 	div	$zero,$t7,$t2
/*    4365c:	00004012 */ 	mflo	$t0
/*    43660:	ad883f84 */ 	sw	$t0,0x3f84($t4)
/*    43664:	15400002 */ 	bnez	$t2,.L00043670
/*    43668:	00000000 */ 	nop
/*    4366c:	0007000d */ 	break	0x7
.L00043670:
/*    43670:	2401ffff */ 	addiu	$at,$zero,-1
/*    43674:	15410004 */ 	bne	$t2,$at,.L00043688
/*    43678:	3c018000 */ 	lui	$at,0x8000
/*    4367c:	15e10002 */ 	bne	$t7,$at,.L00043688
/*    43680:	00000000 */ 	nop
/*    43684:	0006000d */ 	break	0x6
.L00043688:
/*    43688:	10000013 */ 	b	.L000436d8
/*    4368c:	00000000 */ 	nop
.L00043690:
/*    43690:	8fb80038 */ 	lw	$t8,0x38($sp)
/*    43694:	8f193f7c */ 	lw	$t9,0x3f7c($t8)
/*    43698:	8f0b3f80 */ 	lw	$t3,0x3f80($t8)
/*    4369c:	001948c0 */ 	sll	$t1,$t9,0x3
/*    436a0:	01394821 */ 	addu	$t1,$t1,$t9
/*    436a4:	000948c0 */ 	sll	$t1,$t1,0x3
/*    436a8:	012b001a */ 	div	$zero,$t1,$t3
/*    436ac:	00006812 */ 	mflo	$t5
/*    436b0:	af0d3f84 */ 	sw	$t5,0x3f84($t8)
/*    436b4:	15600002 */ 	bnez	$t3,.L000436c0
/*    436b8:	00000000 */ 	nop
/*    436bc:	0007000d */ 	break	0x7
.L000436c0:
/*    436c0:	2401ffff */ 	addiu	$at,$zero,-1
/*    436c4:	15610004 */ 	bne	$t3,$at,.L000436d8
/*    436c8:	3c018000 */ 	lui	$at,0x8000
/*    436cc:	15210002 */ 	bne	$t1,$at,.L000436d8
/*    436d0:	00000000 */ 	nop
/*    436d4:	0006000d */ 	break	0x6
.L000436d8:
/*    436d8:	8fae0038 */ 	lw	$t6,0x38($sp)
/*    436dc:	8dcf3f84 */ 	lw	$t7,0x3f84($t6)
/*    436e0:	8dca3bb8 */ 	lw	$t2,0x3bb8($t6)
/*    436e4:	8dcc2068 */ 	lw	$t4,0x2068($t6)
/*    436e8:	8dd9206c */ 	lw	$t9,0x206c($t6)
/*    436ec:	01ea4021 */ 	addu	$t0,$t7,$t2
/*    436f0:	01994821 */ 	addu	$t1,$t4,$t9
/*    436f4:	01095823 */ 	subu	$t3,$t0,$t1
/*    436f8:	adcb3f88 */ 	sw	$t3,0x3f88($t6)
/*    436fc:	10000003 */ 	b	.L0004370c
/*    43700:	24020001 */ 	addiu	$v0,$zero,0x1
/*    43704:	10000001 */ 	b	.L0004370c
/*    43708:	00000000 */ 	nop
.L0004370c:
/*    4370c:	8fbf0014 */ 	lw	$ra,0x14($sp)
/*    43710:	27bd0038 */ 	addiu	$sp,$sp,0x38
/*    43714:	03e00008 */ 	jr	$ra
/*    43718:	00000000 */ 	nop
);

bool func0004371c(struct asistream *stream)
{
	s32 sp954;
	s32 gr = 0;
	s32 ch;
	s32 sp948;
	s32 sp944;
	s32 sp940;
	s32 i;
	s32 j;
	u16 *sp934;
	struct asistream_4f64 sp34[32];
	f32 sp30;
	f32 sp2c;
	f32 sp28;
	s32 sp24;
	s32 sp20;

	sp934 = stream->unk2070[stream->unk3ba0].unk00;
	sp954 = func00043dd0(stream);

	if (sp954 == -1) {
		return false;
	}

	stream->unk2020 = (sp954 - stream->unk3bf4) * 8;

	if (stream->unk2020 < 0) {
		return true;
	}

	for (ch = 0; ch < stream->numchannels; ch++) {
		func00042238(stream, gr, ch);
		func00040164(stream, gr, ch);
	}

	func000427d8(stream, gr);

	if (stream->unk3c98[gr][0] != 0 && stream->blocktypes[gr][0] == 2) {
		sp948 = 32;
	} else {
		sp944 = (stream->unk465c[0] - 1) / 18 + 1;
		sp948 = sp944;
	}

	for (ch = 0; ch < stream->numchannels; ch++) {
		func00042990(stream, gr, ch);

		if (stream->unk3c98[gr][ch] != 0
				&& stream->blocktypes[gr][ch] == 2
				&& stream->unk3ca8[gr][ch] != 0) {
			sp940 = 0;
		} else if (stream->unk3c98[gr][ch] == 0) {
			sp940 = 0;
		} else {
			sp940 = stream->blocktypes[gr][ch];
		}

		if (sp940 == 2) {
			for (i = 0; i < 2; i++) {
				func00047550(&stream->unk4f64[ch][i], i, &sp34[i], &stream->unk6a64[ch][i]);
			}
		} else {
			for (i = 0; i < 2; i++) {
				func00046650(&stream->unk4f64[ch][i], i, &sp34[i], &stream->unk6a64[ch][i], &var8009c400[sp940 * 0x90]);
			}
		}

		if (stream->unk3c98[gr][ch]
					&& stream->blocktypes[gr][ch] == 2
					&& stream->unk3ca8[gr][ch]) {
			sp940 = 2;
		}

		if (sp940 == 2) {
			for (i = 2; i < sp948; i++) {
				func00047550(&stream->unk4f64[ch][i], i, &sp34[i], &stream->unk6a64[ch][i]);
			}
		} else {
			for (i = 2; i < sp948; i++) {
				func00046650(&stream->unk4f64[ch][i], i, &sp34[i], &stream->unk6a64[ch][i], &var8009c400[sp940 * 0x90]);
			}
		}

		while (i < 32) {
			bcopy(&stream->unk6a64[ch][i], &sp34[i], sizeof(struct asistream_4f64));
			bzero(&stream->unk6a64[ch][i], sizeof(struct asistream_4f64));
			i++;
		}

		sp30 = 65536;
		sp28 = 1;
		sp20 = sp30 * sp28 * 16;
		*sp934 = sp20 >> 16;
		sp934++;

		*sp934 = sp20 & 0xffff;
		sp934++;

		sp20 = -sp20;
		*sp934 = sp20 >> 16;
		sp934++;

		*sp934 = sp20 & 0xffff;
		sp934++;

		sp2c = 2048 / sp28;

		for (j = 0; j < 18; j++) {
			for (i = 0; i < 32; i++) {
				sp24 = sp34[i].unk00[j] * sp2c;
				*sp934 = sp24;
				sp934++;
			}
		}
	}

	return true;
}
