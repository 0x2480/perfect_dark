#ifndef IN_GAME_DATA_0160B0_H
#define IN_GAME_DATA_0160B0_H
#include <ultra64.h>

extern struct menudialog g_2PMissionOptionsHMenuDialog;
extern struct menudialog g_2PMissionOptionsVMenuDialog;

extern u32 var80070090;
extern u32 var80070098;
extern u32 var800700a0;
extern u32 var80070120;
extern u32 var80070124;
extern u32 var80070128;
extern u32 var80070134;
extern u32 var80070140;
extern u32 var8007014c;
extern u32 var800701ac;
extern u32 var800701b8;
extern u32 var800701c0;
extern u32 var800701dc;
extern u32 var800701e4;
extern struct remoteminething var80070200[2];
extern u32 var80070210;
extern u32 var8007021c;
extern u32 var8007022c;
extern u32 var80070238;
extern u32 var80070244;
extern u32 var80070250;
extern u32 var8007025c;
extern u32 var8007029c;
extern u32 var800702e0;
extern u32 var800702e8;
extern u32 var800702ec;
extern u32 var80070314;
extern u32 var80070318;
extern u32 var80070360;
extern struct ammotype g_AmmoTypes[33];
extern u32 var80070500;
extern u32 var8007050c;
extern u32 var80070518;
extern s32 var80070524;
extern u32 var80070528;
extern u32 var80070534;
extern u32 var80070574;
extern u32 var80070578;
extern u32 var8007057c;
extern u32 var80070580;
extern u32 var80070584;
extern u32 var80070590;
extern u32 var800705a0;
extern u32 var800705a4;
extern bool var800705a8;
extern u32 var800705ac;
extern u32 var800705b0;
extern u32 var800705b4;
extern u32 var800705b8;
extern u32 var800705bc;
extern struct vimode g_ViModes[];
extern s32 g_ViMode;
extern bool g_HiResEnabled;
extern s32 var8007072c;
extern u32 var80070738;
extern u32 var8007073c;
extern struct gecreditsdata *g_CurrentGeCreditsData;
extern u32 var80070744;
extern u32 var80070748;
extern u32 var8007074c;
extern bool g_PlayersWithControl[];
extern bool g_PlayerInvincible;
extern s32 g_InCutscene;
extern s16 g_DeathAnimations[];
extern u32 g_NumDeathAnimations;
extern u32 var80070780;
extern u32 var8007078c;
extern u32 var800707a4;
extern u32 var800707f4;
extern u32 var80070800;
extern u32 var8007080c;
extern u32 var80070818;
extern u32 var80070824;
extern u32 var80070830;
extern u32 var8007083c;
extern u32 g_GlobalMenuRoot;
extern struct healthdamagetype g_HealthDamageTypes[];
extern u32 var800709c4;
extern u32 var800709d0;
extern u32 var800709dc;
extern u32 var800709e8;
extern u32 var80070ba4;
extern u32 var80070e50;
extern u32 var80070e5c;
extern u32 var80070e68;
extern u32 var80070e84;
extern u32 var80070e90;
extern u32 var80070e9c;
extern u32 var80070ea8;
extern u8 var80070ec0;
extern u8 var80070ec4;
extern f32 g_EyespyMaxHeight;
extern f32 g_EyespyMinHeight;
extern u32 var80070ed8;
extern u32 var80070edc;
extern u32 var80070ee0;
extern u32 var80070eec;
extern u32 var80070ef8;
extern u32 var80070f10;
extern u32 var80070f14;
extern u32 var80070f18;
extern u32 var80070f1c;
extern u32 var80070f20;
extern u32 var80070f24;
extern u32 var80070f28;
extern u32 var80070f2c;
extern u32 var80070f30;
extern u32 var80070f34;
extern u32 var80070f38;
extern u32 var80070f3c;
extern u32 var80070f40;
extern u32 var80070f44;
extern u32 var80070f48;
extern u32 var80070f4c;
extern u32 var80070f50;
extern u32 var80070f54;
extern u32 var80070f58;
extern u32 var80070f5c;
extern u32 var80070f60;
extern u32 var80070f64;
extern u32 var80070f68;
extern u32 var80070f6c;
extern u32 var80070f70;
extern u32 var80070f80;
extern u32 var80070f94;
extern u32 var80070f9c;
extern u32 var80070fa0;
extern u32 g_Colours[];
extern s32 g_NumHudMessages;
extern struct hudmessage *g_HudMessages;
extern struct hudmessageconfig g_HudMessageConfigs[];
extern u32 var80071170;
extern u32 var80071180;
extern u32 var80071184;
extern s32 g_ScissorX1;
extern s32 g_ScissorX2;
extern s32 g_ScissorY1;
extern s32 g_ScissorY2;
extern s32 var800711a0;
extern s32 var800711a4;
extern u8 g_KeyboardKeys[5][10];
extern u32 var800711e0;
extern u32 var800711e8;
extern u32 var800711f4;
extern char *g_StringPointer;
extern char *g_StringPointer2;
extern s32 g_MpPlayerNum;
extern u32 var8007144c;
extern u32 var80071468;
extern u32 var80071470;
extern u32 var80071480;
extern u32 var800714c0;
extern u32 var800714c4;
extern u32 var800714c8;
extern u32 var800714d8;
extern u32 var800714dc;
extern u32 var800714e0;
extern u32 var800714ec;
extern u32 var800714f0;
extern u32 var800714f4;
extern struct menudialog g_PakRemovedMenuDialog;
extern struct menudialog g_PakRepairSuccessMenuDialog;
extern struct menudialog g_PakRepairFailedMenuDialog;
extern struct menudialog g_PakAttemptRepairMenuDialog;
extern u16 savelocations[];
extern struct menudialog g_PakDamagedMenuDialog;
extern struct menudialog g_PakFullMenuDialog;
extern struct menudialog g_PakCannotReadGameBoyMenuDialog;
extern struct menudialog g_PakDataLostMenuDialog;
extern struct menudialog g_AmPickTargetMenuDialog;
extern u8 var800719a0[3][3];
extern u16 options_controlmode[];
extern u16 g_AimControlOptions[];
extern u16 g_SoundModeOptions[];
extern u16 g_ScreenSizeOptions[];
extern u16 g_ScreenRatioOptions[];
extern u16 g_ScreenSplitOptions[];
extern struct menudialog g_PreAndPostMissionBriefingMenuDialog;
extern struct menudialog g_ChangeAgentMenuDialog;
extern struct menudialog g_AcceptMissionMenuDialog;
extern struct menudialog g_PdModeSettingsMenuDialog;
extern struct menudialog g_SoloMissionDifficultyMenuDialog;
extern struct menudialog g_CoopOptionsMenuDialog;
extern struct menudialog g_AntiOptionsMenuDialog;
extern struct menudialog g_CoopMissionDifficultyMenuDialog;
extern struct menudialog g_AntiMissionDifficultyMenuDialog;
extern struct stageoverviewentry g_StageNames[NUM_SOLOSTAGES];
extern struct mission missions[];
extern struct menudialog g_2PMissionControlStyleMenuDialog;
extern struct menudialog g_SoloMissionControlStyleMenuDialog;
extern struct menudialog g_CiControlStyleMenuDialog;
extern struct menudialog g_CiControlStylePlayer2MenuDialog;
extern u32 var80072d8c;
extern u8 g_CassNecklaceUsername[10];
extern u8 g_CassNecklacePassword[14];
extern struct menudialog g_FrWeaponsAvailableMenuDialog;
extern struct menudialog g_MissionAbortMenuDialog;
extern struct menudialog g_SoloMissionPauseMenuDialog;
extern struct menudialog g_AudioOptionsMenuDialog;
extern struct menudialog g_2PMissionAudioOptionsVMenuDialog;
extern struct menudialog g_VideoOptionsMenuDialog;
extern struct menudialog g_2PMissionVideoOptionsMenuDialog;
extern struct menudialog g_MissionControlOptionsMenuDialog;
extern struct menudialog g_MissionDisplayOptionsMenuDialog;
extern struct menudialog g_2PMissionDisplayOptionsVMenuDialog;
extern struct menudialog g_CiDisplayMenuDialog;
extern struct menudialog g_SoloMissionBriefingMenuDialog;
extern struct menudialog g_2PMissionBriefingHMenuDialog;
extern struct menudialog g_2PMissionBriefingVMenuDialog;
extern struct menudialog g_CiControlPlayer2MenuDialog;
extern struct menudialog g_CiControlOptionsMenuDialog;
extern struct menuitem g_2PMissionOptionsVMenuItems[];
extern struct menudialog g_SoloMissionOptionsMenuDialog;
extern struct menudialog g_SoloMissionInventoryMenuDialog;
extern struct menudialog g_2PMissionPauseHMenuDialog;
extern struct menudialog g_2PMissionPauseVMenuDialog;
extern struct cutscene g_Cutscenes[];
extern struct cutscenegroup cutscenegrouptable[];
extern struct menudialog g_CinemaMenuDialog;
extern struct menudialog g_SelectMissionMenuDialog;
extern struct menudialog g_CiOptionsViaPcMenuDialog;
extern struct menudialog g_CiOptionsViaPauseMenuDialog;
extern struct menudialog g_CiMenuViaPauseMenuDialog;
extern struct menudialog g_CiMenuViaPcMenuDialog;
extern struct cheat g_Cheats[NUM_CHEATS];
extern struct menuitem g_CheatsBuddiesMenuItems[];
extern struct menudialog g_CheatsBuddiesMenuDialog;

#endif
