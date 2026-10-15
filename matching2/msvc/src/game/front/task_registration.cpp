// 0x00413980..0x00413A12: load the front animation and register its tasks.
#include "th10/game/front_tasks.hpp"

struct BulletResourceCache;
struct TextLog_0044b810 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* Append(char* format, ...);
};
extern "C" {
void* __fastcall Recovery_LoadCachedResource(
    int index, BulletResourceCache* cache, const char* name);
SchedulerTask* __stdcall SchedulerTask_Create(TaskRoutine routine);
int __stdcall ScoreTask_Setup(void* state);
extern BulletResourceCache* g_sprt_ctrl;
extern FuncCtrl* g_func_ctrl;
extern TextLog_0044b810 g_log;
extern char str_data_corrupted[];
extern char str_front_anm[];
int __fastcall ItemFront_UpdateThunk(void* state);
int __fastcall ItemFront_RenderThunk(void* state);
}

#pragma code_seg(".text$00d_ciitem")
extern "C" __declspec(noinline) int __stdcall
Front_RegisterTasks(FrontTaskView* state) {
    void* resource = Recovery_LoadCachedResource(
        6, g_sprt_ctrl, str_front_anm);
    state->front_resource = resource;
    if (!resource) {
        g_log.Append(str_data_corrupted);
        return -1;
    }
    if (ScoreTask_Setup(state) != 0)
        return -1;

    SchedulerTask* update = SchedulerTask_Create(
        ItemFront_UpdateThunk);
    update->reserved_flags &= ~1u;
    update->context = state;
    FuncCtrl_RegisterPrimary(g_func_ctrl, update, 0x18);
    state->update_task = update;

    SchedulerTask* render = SchedulerTask_Create(
        ItemFront_RenderThunk);
    render->reserved_flags &= ~1u;
    render->context = state;
    FuncCtrl_RegisterSecondary(g_func_ctrl, render, 0x2b);
    state->render_task = render;
    return 0;
}
#pragma code_seg()
