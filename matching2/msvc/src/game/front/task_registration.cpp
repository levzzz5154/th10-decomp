// 0x00413980..0x00413A12: load the front animation and register its tasks.
#include "th10/game/front_tasks.hpp"

struct BulletResourceCache_0040ae70;
struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};
extern "C" {
void* __fastcall Recovery_LoadCachedResource_00447280(
    int index, BulletResourceCache_0040ae70* cache, const char* name);
SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(TaskRoutine routine);
int __stdcall ScoreTask_Setup_00413a20(void* state);
extern BulletResourceCache_0040ae70* g_sprt_ctrl;
extern FuncCtrl* g_func_ctrl;
extern TextLog_0044b810 g_log;
extern char str_data_corrupted[];
extern char str_front_anm[];
int __fastcall ItemFront_UpdateThunk_00415ae0(void* state);
int __fastcall ItemFront_RenderThunk_00415af0(void* state);
}

#pragma code_seg(".text$00d_ciitem")
extern "C" __declspec(noinline) int __stdcall
Front_RegisterTasks(FrontTaskView* state) {
    void* resource = Recovery_LoadCachedResource_00447280(
        6, g_sprt_ctrl, str_front_anm);
    state->front_resource = resource;
    if (!resource) {
        g_log.Append(str_data_corrupted);
        return -1;
    }
    if (ScoreTask_Setup_00413a20(state) != 0)
        return -1;

    SchedulerTask* update = SchedulerCallback_Create_00449ed0(
        ItemFront_UpdateThunk_00415ae0);
    update->reserved_flags &= ~1u;
    update->context = state;
    FuncCtrl_RegisterPrimary(g_func_ctrl, update, 0x18);
    state->update_task = update;

    SchedulerTask* render = SchedulerCallback_Create_00449ed0(
        ItemFront_RenderThunk_00415af0);
    render->reserved_flags &= ~1u;
    render->context = state;
    FuncCtrl_RegisterSecondary(g_func_ctrl, render, 0x2b);
    state->render_task = render;
    return 0;
}
#pragma code_seg()
