// 0x0040A130..0x0040A199 (106 bytes): installs the two scheduler tasks that
// drive the 0x688-byte game state.
//
// Retail receives the state in EBX - not a parameter register of any MSVC
// convention.  The register is a whole-program agreement the LTCG pass derives
// from the state being live across both registration calls while the freshly
// created task occupies ESI and the priority occupies EDI: this source is
// therefore compiled in the same native-LTCG link as the registration pair it
// calls (see build_support/layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/core/func_ctrl.hpp"

struct RawState_0040a130 {
    unsigned char pad_000[8];
    void *primary_task_008;             // +0x008, installed here
    void *secondary_task_00C;           // +0x00C, installed here
};

extern "C" SchedulerTask *__stdcall SchedulerCallback_Create_00449ed0(void *callback);
extern "C" FuncCtrl *g_func_ctrl;
extern "C" unsigned char g_stage_route_current;
extern "C" unsigned char g_globals_stage;
extern "C" unsigned char g_globals_stage_shown;

#pragma code_seg(".text$00_ystatereg")
extern "C" __declspec(noinline) int __stdcall
EclView_RegisterTasks(RawState_0040a130 *state) {
    *(void **)&g_stage_route_current = (void *)0x474788;
    *(unsigned int *)&g_globals_stage = 0;
    *(unsigned int *)&g_globals_stage_shown = 0;

    SchedulerTask *primary = SchedulerCallback_Create_00449ed0((void *)0x40ABE0);
    primary->reserved_flags |= 1u;
    primary->context = state;
    FuncCtrl_RegisterPrimary(g_func_ctrl, primary, 5);
    state->primary_task_008 = primary;

    SchedulerTask *secondary = SchedulerCallback_Create_00449ed0((void *)0x40ABF0);
    secondary->reserved_flags |= 1u;
    secondary->context = state;
    FuncCtrl_RegisterSecondary(g_func_ctrl, secondary, 0x27);
    state->secondary_task_00C = secondary;
    return 0;
}
#pragma code_seg()
