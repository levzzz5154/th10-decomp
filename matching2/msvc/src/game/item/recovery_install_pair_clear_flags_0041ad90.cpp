// 0x0041AD90..0x0041ADE3 (84 bytes): ?Recovery_InstallPairClearFlags@@
//
// The clear-flags counterpart of ?Recovery_InstallPairSetFlags@@ (0x004055C0):
// it builds the two scheduler callbacks that drive a freshly created pair,
// clears the reserved flag the set-flags installer raises, publishes each
// callback on the pair and registers the pair with the scheduler's primary and
// secondary lists.
//
// Retail receives the pair in EBX - not a parameter register of any MSVC
// convention - and returns the status in EAX. As in the set-flags installer,
// the pair stays live across both registration calls while the freshly created
// callback occupies ESI and the priority EDI, so the register is a whole-program
// agreement: this source is compiled in the same native-LTCG link as the
// registration pair it calls (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/core/func_ctrl.hpp"

struct RawPair_0041ad90 {
    unsigned char pad_000[8];
    void *callback_008;                 // +0x08, primary scheduler callback
    void *callback_00C;                 // +0x0C, secondary scheduler callback
};

extern "C" SchedulerTask *__stdcall SchedulerCallback_Create_00449ed0(void *callback);
extern "C" void *g_func_ctrl;

#pragma code_seg(".text$00e_installclear")
extern "C" __declspec(noinline) int __stdcall
asm_Recovery_InstallPairClearFlags_0041ad90(RawPair_0041ad90 *pair) {
    SchedulerTask *primary = SchedulerCallback_Create_00449ed0((void *)0x41BA00);
    primary->reserved_flags &= ~1u;
    primary->context = pair;
    FuncCtrl_RegisterPrimary((FuncCtrl *)g_func_ctrl, primary, 0x15);
    pair->callback_008 = primary;

    SchedulerTask *secondary = SchedulerCallback_Create_00449ed0((void *)0x41BA30);
    secondary->reserved_flags &= ~1u;
    secondary->context = pair;
    FuncCtrl_RegisterSecondary((FuncCtrl *)g_func_ctrl, secondary, 0x19);
    pair->callback_00C = secondary;
    return 0;
}
#pragma code_seg()
