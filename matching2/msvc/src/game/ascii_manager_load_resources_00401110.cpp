// 0x00401110: load the ASCII manager's three animation files (ascii.anm,
// text.anm, capture.anm), register its update (primary list, priority 4) and
// two draw tasks (secondary list, priorities 0x30 and 0x26), and bind its two
// sprites to entries 0 and 0x62 of ascii.anm. A missing file logs "data is
// corrupted" and returns -1.
//
// Native LTCG passes the manager in EBX, so this is compiled in the same link
// as the scheduler registration functions and the text log it calls
// (layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/text_log.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"

struct AsciiManager_00401110 {
    unsigned char pad_000[0x0C];
    SchedulerTask* update_task;              // +0x0000C
    SchedulerTask* draw_task;                // +0x00010
    Entity primary_sprite;                   // +0x00014
    Entity secondary_sprite;                 // +0x003C0
    unsigned char pad_76c[0x8994 - 0x76C];
    Resource_0043e5a0* ascii_resource;       // +0x08994
    Resource_0043e5a0* capture_resource;     // +0x08998
    Resource_0043e5a0* text_resource;        // +0x0899C
    unsigned char pad_89a0[0x08];
    SchedulerTask* overlay_draw_task;        // +0x089A8

    __declspec(noinline) int LoadResources();
};


extern "C" {
void *__fastcall Recovery_LoadCachedResource_00447280(int id, void *cache, const char *name);
SchedulerTask *__stdcall SchedulerCallback_Create_00449ed0(void *callback);
int __fastcall AsciiManagerUpdate_004014f0(void *manager);
int __fastcall AsciiManagerDraw_00401510(void *manager);
int __fastcall AsciiManagerDrawOverlay_00401520(void *manager);
extern void *data_00491c10;
extern Scheduler *data_00491be4;
}

#pragma code_seg(".text$00_b_load")
int AsciiManager_00401110::LoadResources() {
    AsciiManager_00401110 *manager = this;
    manager->ascii_resource = (Resource_0043e5a0 *)Recovery_LoadCachedResource_00447280(
            2, data_00491c10, "ascii.anm");
    if (!manager->ascii_resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CB68);
        return -1;
    }
    manager->text_resource = (Resource_0043e5a0 *)Recovery_LoadCachedResource_00447280(
            0, data_00491c10, "text.anm");
    if (!manager->text_resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CB68);
        return -1;
    }
    manager->capture_resource = (Resource_0043e5a0 *)Recovery_LoadCachedResource_00447280(
            3, data_00491c10, "capture.anm");
    if (!manager->capture_resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CB68);
        return -1;
    }

    SchedulerTask *task = SchedulerCallback_Create_00449ed0((void *)AsciiManagerUpdate_004014f0);
    task->reserved_flags &= ~1u;
    task->context = manager;
    Scheduler_RegisterPrimary(data_00491be4, task, 4);
    manager->update_task = task;

    task = SchedulerCallback_Create_00449ed0((void *)AsciiManagerDraw_00401510);
    task->context = manager;
    task->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x30);
    manager->draw_task = task;

    task = SchedulerCallback_Create_00449ed0((void *)AsciiManagerDrawOverlay_00401520);
    task->context = manager;
    task->reserved_flags &= ~1u;
    Scheduler_RegisterSecondary(data_00491be4, task, 0x26);
    manager->overlay_draw_task = task;

    Entity *sprite = &manager->primary_sprite;
    Resource_0043e5a0 *resource = manager->ascii_resource;
    Entity_Init(0, sprite);
    sprite->script_resource = resource;
    resource->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0 *>(sprite), 0);
    sprite = &manager->secondary_sprite;
    resource = manager->ascii_resource;
    Entity_Init(0, sprite);
    sprite->script_resource = resource;
    resource->ConfigureObject(reinterpret_cast<AnimationObject_0043e5a0 *>(sprite), 0x62);
    return 0;
}
#pragma code_seg()
