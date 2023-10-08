#ifndef _IN_DEBUGGER_H
#define _IN_DEBUGGER_H

#include <PR/ultratypes.h>

extern s32 g_DebuggerActive;
extern s32 g_DebuggerTimePasses;
extern s32 g_DebuggerFrameAdvance;

void debuggerInit(void);
void debuggerProcessEvent(void *event);

void debuggerStartFrame(void);
void debuggerFrame(void);
void debuggerEndFrame(void);

#endif