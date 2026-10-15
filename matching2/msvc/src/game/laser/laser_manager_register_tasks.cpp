// 0x0041C120..0x0041C1B1 (146 bytes): LaserManager_RegisterTasks
//
// Loads the laser resource, then creates and registers the two
// scheduler callbacks that drive it; a failure to load the resource is logged
// through the constant text log and reported as -1.
//
// Retail receives the manager in EBX and keeps the callback under construction
// in ESI with the registration priority in EDI - none of those are parameter
// registers of any MSVC convention, they are whole-program agreements.  This
// source is therefore compiled in the same native-LTCG link as the scheduler
// registration functions and the constant-log formatter it calls (see
// build_support/layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/core/func_ctrl.hpp"

struct LaserManagerView {
    unsigned char pad_000[0x08];
    void *primary_task_008;             // +0x008, primary display task
    void *secondary_task_00C;           // +0x00C, secondary display task
    unsigned char head_laser_010[0x424];     // +0x010, embedded head laser (base Laser)
    void *head_laser_pointer_434;            // +0x434, address of the embedded object
    unsigned char pad_438[0x20];
    void *display_resource_458;         // +0x458, filled by this routine
};

typedef char LaserManagerView_size_must_be_45c[
    sizeof(LaserManagerView) == 0x45C ? 1 : -1];

// Declared here exactly as the co-compiled TextLog translation unit defines it,
// so the whole-program pass can pick the register agreement retail used.
struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void *__fastcall Recovery_LoadCachedResource(
        int id, void *cache, const char *name);
extern "C" SchedulerTask *__stdcall SchedulerTask_Create(void *callback);
extern "C" void *g_sprt_ctrl;
extern "C" FuncCtrl *g_func_ctrl;

extern "C" __declspec(noinline) int __stdcall
LaserManager_RegisterTasks(LaserManagerView *manager);
#pragma code_seg(".text$00gascoredisplay")
extern "C" __declspec(noinline) int __stdcall
LaserManager_RegisterTasks(LaserManagerView *manager) {
    void *resource = Recovery_LoadCachedResource(
            7, g_sprt_ctrl, (const char *)0x46CD88);
    manager->display_resource_458 = resource;
    if (!resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CD54);
        return -1;
    }

    SchedulerTask *primary = SchedulerTask_Create((void *)0x41C480);
    primary->reserved_flags &= ~1u;
    primary->context = manager;
    FuncCtrl_RegisterPrimary(g_func_ctrl, primary, 0x13);
    manager->primary_task_008 = primary;

    SchedulerTask *secondary = SchedulerTask_Create((void *)0x41C4E0);
    secondary->reserved_flags &= ~1u;
    secondary->context = manager;
    FuncCtrl_RegisterSecondary(g_func_ctrl, secondary, 0x1B);
    manager->secondary_task_00C = secondary;
    manager->head_laser_pointer_434 = manager->head_laser_010;
    return 0;
}
#pragma code_seg()
