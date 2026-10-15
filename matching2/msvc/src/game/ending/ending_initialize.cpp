// The ending's initializer at 0x0040B560 (ending.cpp, EndingInf) and its native ending-text
// allocation cleanup.
// EndingText is supplied by the cluster driver before this source.
#include <string.h>
#include "th10/core/func_ctrl.hpp"
#include "th10/render/animation_public_callers.hpp"
#include "th10/platform/archive_file.hpp"
#include "th10/platform/text_log.hpp"
extern "C" FuncCtrl* g_func_ctrl;
extern "C" int __fastcall Ending_UpdateTask(void*);
extern "C" int __fastcall Ending_DrawTask(void*);
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
extern "C" GameCounters_0040b560 g_globals_score;
extern "C" const char* g_ending_files[12];
extern "C" char g_recovery_script_path[260];
extern "C" char str_data_corrupted[];
extern "C" TextLog_0044b810 g_log;
struct EndingUnlocks {
    unsigned char reserved[0x1D882];
    unsigned char endings[12];
    unsigned char alternate;
};
extern "C" EndingUnlocks* g_score;
struct EndingAsciiView {
    unsigned char reserved[0x8994];
    void* resource;
    void* Resource() const { return resource; }
    unsigned char reserved_8998[12];
    int background_id;
};
void* __cdecl operator new(unsigned int);
inline void InitializeEndingTaskLink(TaskLink& link, SchedulerTask* task) {
    link.task = task; link.next = 0; link.previous = 0;
}
struct EndingTask : SchedulerTask {
    EndingTask() {
        on_tick = 0; on_register = 0; on_remove = 0;
        priority = 0; heap_owned = 0;
        InitializeEndingTaskLink(link, this);
    }
};
inline void RaiseFlag(unsigned int& flags, unsigned int bit) { flags |= bit; }
struct Ending {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    int reserved_010;
    char* file;
    EndingText* text;
    int ending_index;
    unsigned int flags;
    __declspec(noinline) int Initialize();
};
#pragma code_seg(".text$01main")
int Ending::Initialize() {
    SchedulerTask* update = new EndingTask;
    update->heap_owned = 1; update->reserved_flags |= 1;
    update->on_tick = Ending_UpdateTask; update->on_register = 0; update->on_remove = 0;
    update->context = this;
    FuncCtrl_RegisterPrimary(g_func_ctrl, update, 28);
    update_task = update;
    SchedulerTask* draw = new EndingTask;
    draw->heap_owned = 1; draw->reserved_flags |= 1;
    draw->on_tick = Ending_DrawTask; draw->on_register = 0; draw->on_remove = 0;
    draw->context = this;
    FuncCtrl_RegisterSecondary(g_func_ctrl, draw, 6);
    draw_task = draw;
    int& background = ((EndingAsciiView*)g_ascii_manager)->background_id;
    AnimationPosition_00448d50 position(480.0f, 392.0f, 0.0f);
    if (!background) {
        int id;
        background = *(int*)AnimationManager_CreatePositionedPrimary_00448d50(
            ((EndingAsciiView*)g_ascii_manager)->Resource(), (void**)&id, 6, &position);
    }
    ending_index = g_globals_score.character * 3 + g_globals_score.shot_type;
    if (!g_globals_score.continued && g_globals_score.difficulty >= 1) ending_index += 6;
    if (!g_score->endings[ending_index]) RaiseFlag(flags, 1);
    if (!g_score->alternate) RaiseFlag(flags, 2);
    g_score->endings[ending_index] = 1;
    if (ending_index >= 6) g_score->alternate = 1;
    const char* filename = g_ending_files[ending_index];
    g_recovery_script_path[0] = 0;
    strcat(g_recovery_script_path, filename);
    file = Archive_LoadFile(g_recovery_script_path, 0, 0);
    if (!file) { g_log.Append(str_data_corrupted); return -1; }
    text = new EndingText(file + *(int*)(file + 4));
    return 0;
}
#pragma code_seg()
