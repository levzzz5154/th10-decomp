// 0x0042CAA0: register the title screen's update (primary list, priority 6)
// and draw (secondary list, priority 3) tasks, then load title.anm and
// title_v.anm. A missing file logs "data is corrupted" and returns -1.
//
// Native LTCG passes the title state in EBX, so this is compiled in the same
// link as the scheduler registration functions and the text log it calls
// (layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/core/func_ctrl.hpp"

struct Title {
    unsigned char pad_000[0x0C];
    SchedulerTask* update_task;          // +0x00C
    SchedulerTask* draw_task;            // +0x010
    void* title_resource;                // +0x014
    void* title_v_resource;              // +0x018
    unsigned char pad_01c[0xF4 - 0x1C];
    int ready;                           // +0x0F4
};

// Declared here exactly as the co-compiled TextLog translation unit defines it.
struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void *__fastcall Recovery_LoadCachedResource_00447280(
        int id, void *cache, const char *name);
extern "C" SchedulerTask *__stdcall SchedulerCallback_Create_00449ed0(void *callback);
extern "C" void *g_sprt_ctrl;
extern "C" FuncCtrl *g_func_ctrl;
extern "C" int data_004918a4;

#pragma code_seg(".text$00hbstartupzmzt")
extern "C" __declspec(noinline) int __stdcall
Title_RegisterTasks(Title *title) {
    SchedulerTask *task = SchedulerCallback_Create_00449ed0((void *)0x42D2E0);
    task->reserved_flags &= ~1u;
    task->context = title;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, 6);
    title->update_task = task;

    task = SchedulerCallback_Create_00449ed0((void *)0x42D2F0);
    task->context = title;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 3);
    title->draw_task = task;

    title->title_resource = Recovery_LoadCachedResource_00447280(
            0x19, g_sprt_ctrl, "title.anm");
    if (!title->title_resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CB68);
        return -1;
    }
    title->title_v_resource = Recovery_LoadCachedResource_00447280(
            0x1A, g_sprt_ctrl, "title_v.anm");
    if (!title->title_v_resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CB68);
        return -1;
    }
    title->ready = 1;
    data_004918a4 = 0;
    return 0;
}
#pragma code_seg()
