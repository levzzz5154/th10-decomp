// 0x004055C0..0x00405613 (84 bytes): Bomb_RegisterTasks - install the bomb's
// update (0x00405840) and draw (0x00405850) tasks.
//
// Builds the two scheduler callbacks that drive a fixed-state pair, publishes
// each one on the pair, and registers them with the scheduler's primary and
// secondary lists.
//
// Retail receives the pair in EBX - not a parameter register of any MSVC
// convention. The register is a whole-program agreement the LTCG pass derives
// from the pair being live across both registration calls while the freshly
// created callback occupies ESI: this source is therefore compiled in the same
// native-LTCG link as the registration pair it calls (see
// build_support/layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/core/func_ctrl.hpp"

struct RawPair_004055c0 {
    unsigned char pad_000[8];
    void *callback_008;                 // +0x08, primary scheduler callback
    void *callback_00C;                 // +0x0C, secondary scheduler callback
};

extern "C" SchedulerTask *__stdcall SchedulerTask_Create(void *callback);
extern "C" void *g_func_ctrl;

#pragma code_seg(".text$00_vinstall")
extern "C" __declspec(noinline) int __stdcall
Bomb_RegisterTasks(RawPair_004055c0 *pair) {
    SchedulerTask *primary = SchedulerTask_Create((void *)0x405840);
    primary->reserved_flags |= 1u;
    primary->context = pair;
    FuncCtrl_RegisterPrimary((FuncCtrl *)g_func_ctrl, primary, 0x11);
    pair->callback_008 = primary;

    SchedulerTask *secondary = SchedulerTask_Create((void *)0x405850);
    secondary->reserved_flags |= 1u;
    secondary->context = pair;
    FuncCtrl_RegisterSecondary((FuncCtrl *)g_func_ctrl, secondary, 0x22);
    pair->callback_00C = secondary;
    return 0;
}
#pragma code_seg()
