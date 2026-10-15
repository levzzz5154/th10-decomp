// Message-manager initializer at 0x0040B560 and its native ending-text
// allocation cleanup.
// EndingText is supplied by the cluster driver before this source.
#include <string.h>
#include "th10/game/scheduler.hpp"
#include "th10/render/animation_public_callers.hpp"
#include "th10/platform/archive_file.hpp"
#include "th10/platform/text_log.hpp"
extern "C" Scheduler* data_00491be4;
extern "C" int __fastcall MessageUpdate(void*);
extern "C" int __fastcall MessageDraw(void*);
// The running game's counters at 0x00474C44: one object whose address is
// taken elsewhere, so stores through other pointers order against its fields.
struct GameCounters_0040b560 {
    unsigned char reserved_00[0x24];
    int character;                // 0x00474C68
    int shot_type;                // 0x00474C6C
    int reserved_2c;
    int difficulty;               // 0x00474C74
    unsigned char reserved_34[0x18];
    int continued;                // 0x00474C90
};
extern "C" GameCounters_0040b560 data_00474c44;
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
    void* Resource() const { return resource; }
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
inline void RaiseFlag(unsigned int& flags, unsigned int bit) { flags |= bit; }
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
    SchedulerTask* update = new MessageTask;
    update->heap_owned = 1; update->reserved_flags |= 1;
    update->on_tick = MessageUpdate; update->on_register = 0; update->on_remove = 0;
    update->context = this;
    Scheduler_RegisterPrimary(data_00491be4, update, 28);
    update_task = update;
    SchedulerTask* draw = new MessageTask;
    draw->heap_owned = 1; draw->reserved_flags |= 1;
    draw->on_tick = MessageDraw; draw->on_register = 0; draw->on_remove = 0;
    draw->context = this;
    Scheduler_RegisterSecondary(data_00491be4, draw, 6);
    draw_task = draw;
    int& background = ((MessageThread*)g_ascii_manager)->background_id;
    AnimationPosition_00448d50 position(480.0f, 392.0f, 0.0f);
    if (!background) {
        int id;
        background = *(int*)AnimationManager_CreatePositionedPrimary_00448d50(
            ((MessageThread*)g_ascii_manager)->Resource(), (void**)&id, 6, &position);
    }
    ending_index = data_00474c44.character * 3 + data_00474c44.shot_type;
    if (!data_00474c44.continued && data_00474c44.difficulty >= 1) ending_index += 6;
    if (!data_0047783c->endings[ending_index]) RaiseFlag(flags, 1);
    if (!data_0047783c->alternate) RaiseFlag(flags, 2);
    data_0047783c->endings[ending_index] = 1;
    if (ending_index >= 6) data_0047783c->alternate = 1;
    const char* filename = data_00474440[ending_index];
    data_00497c38[0] = 0;
    strcat(data_00497c38, filename);
    file = Archive_LoadFile(data_00497c38, 0, 0);
    if (!file) { data_00474f70.Append(data_0046cb68); return -1; }
    text = new MessageEndingText(file + *(int*)(file + 4));
    return 0;
}
#pragma code_seg()
