// Complete caller model for native ending-text allocation cleanup.
// Only the generated EH functions are selected; the 584-byte initializer
// candidate still differs in instruction order and remains an ABI anchor.
// EndingText is supplied by the cluster driver before this source.
#include <string.h>
#include "th10/game/scheduler.hpp"
#include "th10/render/animation_public_callers.hpp"
#include "th10/platform/archive_file.hpp"
#include "th10/platform/text_log.hpp"
extern "C" Scheduler* data_00491be4;
extern "C" int __fastcall MessageUpdate(void*);
extern "C" int __fastcall MessageDraw(void*);
extern "C" int data_00474c68, data_00474c6c, data_00474c90, data_00474c74;
extern "C" const char* data_00474440[12];
extern "C" char data_00497c38[260];
extern "C" char data_0046cb68[];
extern "C" TextLog_0044b810 data_00474f70;
struct EndingUnlocks {
    unsigned char reserved[0x1D882];
    unsigned char endings[12];
    unsigned char alternate;
};
extern "C" EndingUnlocks* data_0047783c;
struct MessageThread {
    unsigned char reserved[0x8994];
    void* resource;
    unsigned char reserved_8998[12];
    int background_id;
};
typedef EndingText MessageEndingText;
void* __cdecl operator new(unsigned int);
inline void InitializeMessageTaskLink(TaskLink& link, SchedulerTask* task) {
    link.task = task; link.next = 0; link.previous = 0;
}
struct MessageTask : SchedulerTask {
    MessageTask() {
        on_tick = 0; on_register = 0; on_remove = 0;
        priority = 0; heap_owned = 0;
        InitializeMessageTaskLink(link, this);
    }
};
struct MessageManager {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    int reserved_010;
    char* file;
    MessageEndingText* text;
    int ending_index;
    unsigned int flags;
    __declspec(noinline) int Initialize();
};
#pragma code_seg(".text$01main")
int MessageManager::Initialize() {
    SchedulerTask* task = new MessageTask;
    task->heap_owned = 1; task->reserved_flags |= 1;
    task->on_tick = MessageUpdate; task->on_register = 0; task->on_remove = 0;
    task->context = this;
    Scheduler_RegisterPrimary(data_00491be4, task, 28);
    update_task = task;
    task = new MessageTask;
    task->heap_owned = 1; task->reserved_flags |= 1;
    task->on_tick = MessageDraw; task->on_register = 0; task->on_remove = 0;
    task->context = this;
    Scheduler_RegisterSecondary(data_00491be4, task, 6);
    draw_task = task;
    int& background = ((MessageThread*)data_004776e0)->background_id;
    AnimationPosition_00448d50 position(480.0f, 392.0f, 0.0f);
    if (!background) {
        int id;
        background = *(int*)AnimationManager_CreatePositionedPrimary_00448d50(
            ((MessageThread*)data_004776e0)->resource, (void**)&id, 6, &position);
    }
    ending_index = data_00474c68 * 3 + data_00474c6c;
    if (!data_00474c90 && data_00474c74 >= 1) ending_index += 6;
    unsigned char* unlocks = (unsigned char*)data_0047783c;
    if (!unlocks[0x1D882 + ending_index]) flags |= 1;
    if (!unlocks[0x1D88E]) flags |= 2;
    unlocks[0x1D882 + ending_index] = 1;
    if (ending_index >= 6) unlocks[0x1D88E] = 1;
    const char* filename = data_00474440[ending_index];
    data_00497c38[0] = 0;
    strcat(data_00497c38, filename);
    file = Archive_LoadFile(data_00497c38, 0, 0);
    if (!file) { data_00474f70.Append(data_0046cb68); return -1; }
    text = new MessageEndingText(file + *(int*)(file + 4));
    return 0;
}
#pragma code_seg()
