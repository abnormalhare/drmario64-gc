#include "dolphin/dsp.h"
#include "dolphin/os.h"

#include "dolphin/hw_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DEBUG
const char* __DSPVersion = "<< Dolphin SDK - DSP\tdebug build: Sep  5 2002 ??:??:?? (0x2301) >>";
#else
const char* __DSPVersion = "<< Dolphin SDK - DSP\trelease build: Sep  5 2002 05:35:13 (0x2301) >>";
#endif

static s32 __DSP_init_flag = 0;
extern DSPTaskInfo* __DSP_tmp_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_curr_task;

extern void __DSPHandler(__OSInterrupt, OSContext*);
extern void __DSP_debug_printf(const char* fmt, ...);
extern void __DSP_boot_task(DSPTaskInfo* task);

u32 DSPCheckMailToDSP(void) { return (__DSPRegs[0] >> 0xF) & 1; }

u32 DSPCheckMailFromDSP(void) { return (__DSPRegs[2] >> 0xF) & 1; }

u32 DSPReadMailFromDSP() {
  u16 reg1;
  u16 reg2;
  reg1 = __DSPRegs[2];
  reg2 = __DSPRegs[3];
  return reg1 << 16 | reg2;
}

void DSPSendMailToDSP(u32 mail) {
  __DSPRegs[0] = mail >> 16;
  __DSPRegs[1] = mail;
}

void DSPInit(void) {
  u32 oldInt;
  u16 reg;
  __DSP_debug_printf("DSPInit(): Build Date: %s %s\n", "Sep  5 2002", "05:35:13");

  if (__DSP_init_flag == 1) {
    return;
  }
  OSRegisterVersion(__DSPVersion);
  oldInt = OSDisableInterrupts();
  __OSSetInterruptHandler(7, __DSPHandler);
  __OSUnmaskInterrupts(0x1000000);
  reg = __DSPRegs[5];
  reg = (reg & ~0xA8) | 0x800;
  __DSPRegs[5] = reg;
  reg = __DSPRegs[5];
  reg = reg & ~0xAC;
  __DSPRegs[5] = reg;
  __DSP_tmp_task = 0;
  __DSP_curr_task = 0;
  __DSP_last_task = 0;
  __DSP_first_task = 0;
  __DSP_init_flag = 1;
  OSRestoreInterrupts(oldInt);
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task) {
  u32 oldInt;
  oldInt = OSDisableInterrupts();
  __DSP_insert_task(task);
  task->state = 0;
  task->flags = 1;
  OSRestoreInterrupts(oldInt);
  if (task == __DSP_first_task) {
    __DSP_boot_task(task);
  }

  return task;
}

#ifdef __cplusplus
}
#endif
