// 0x00405E20: load bullet.anm, point the manager's cursor at its first
// bullet, and register its update (primary list, priority 0x14) and draw
// (secondary list, priority 0x1D) tasks. A missing bullet.anm logs
// "the data is missing or corrupted" and returns -1.
//
// Native LTCG passes the manager in EBX.
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/text_log.hpp"

struct BulletSlot3 {
    unsigned char reserved_000[0x446];
    short mode;                              // +0x446
    unsigned char reserved_448[0x7F0 - 0x448];
};

struct BulletManager4 {
    unsigned char reserved_000[0x08];
    SchedulerTask* update_task;              // +0x0000008
    SchedulerTask* draw_task;                // +0x000000C
    BulletSlot3* cursor;             // +0x0000010
    unsigned char reserved_014[0x60 - 0x14];
    BulletSlot3 bullets[2001];       // +0x0000060
    void* bullet_resource;                   // +0x03E0B50
};

extern "C" {
void *__fastcall Recovery_LoadCachedResource(int id, void *cache, const char *name);
SchedulerTask *__stdcall SchedulerTask_Create(void *callback);
int __fastcall BulletManagerUpdate(void *manager);
int __fastcall BulletManagerDraw(void *manager);
extern void *g_sprt_ctrl;
extern FuncCtrl *g_func_ctrl;
}

#pragma code_seg(".text$00_b_init")
extern "C" __declspec(noinline) int __stdcall
BulletManager_Initialize(BulletManager4 *manager) {
    manager->bullet_resource = Recovery_LoadCachedResource(
            7, g_sprt_ctrl, "bullet.anm");
    if (!manager->bullet_resource) {
        ((TextLog4 *)0x474F70)->Append((char *)0x46CD54);
        return -1;
    }
    manager->cursor = &manager->bullets[0];
    manager->bullets[2000].mode = 5;

    SchedulerTask *task = SchedulerTask_Create((void *)BulletManagerUpdate);
    task->context = manager;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, 0x14);
    manager->update_task = task;

    task = SchedulerTask_Create((void *)BulletManagerDraw);
    task->context = manager;
    task->reserved_flags &= ~1u;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, 0x1D);
    manager->draw_task = task;
    return 0;
}
#pragma code_seg()

typedef char BulletManager_00405e20_resource_offset[
    sizeof(BulletManager4) == 0x3E0B54 ? 1 : -1];
