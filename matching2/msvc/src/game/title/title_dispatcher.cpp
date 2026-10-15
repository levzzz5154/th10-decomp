// 0x0042CDF0..0x0042D257: the title screen's per-frame dispatcher: the idle
// counter that starts a demo replay, then the handler of the current mode.
//
// A draft measured with `equivalence.py --layout`; it is linked beside the
// title cluster's own dispatcher stand-in, which the exact handlers depend
// on and which stays untouched.
#include "th10/game/ending_screen_0042d300.hpp"
#include "th10/render/animation_resource_removal.hpp"
#include <stdlib.h>
#include <string.h>

struct TitleCallback { unsigned int reserved; unsigned int flags; };
struct TitlePrefix {
    unsigned char reserved[0x10];
    TitleCallback* callback;
    void* resource;
    void* secondary_resource;
    int mode;
};
typedef char TitleModeOffset[offsetof(TitlePrefix, mode) == 0x1c ? 1 : -1];
struct DemoHeader {
    unsigned char reserved[0x50];
    int character;
    int shot;
    int difficulty;
};
struct DemoStageRecord { int present; unsigned char reserved[0x20]; };
struct DemoFile {
    unsigned char reserved_000[0x18];
    DemoHeader* header;
    unsigned char reserved_01c[0xb0 - 0x1c];
    DemoStageRecord stages[8];
};
typedef char DemoStageOffset[offsetof(DemoFile, stages) == 0xb0 ? 1 : -1];
// The game state object at 0x00474C44 as the title screen uses it.
struct TitleGameState {
    unsigned char reserved_00[0x24];
    int character;                      // 0x00474C68
    int shot;                           // 0x00474C6C
    int reserved_2c;
    int difficulty;                     // 0x00474C74
    int menu_difficulty;                // 0x00474C78: the difficulty to restore after a demo
    int stage;                          // 0x00474C7C
    int first_stage;                    // 0x00474C80
    unsigned char reserved_40[0x5C - 0x40];
    unsigned int flags;                 // 0x00474CA0: 0x20 = demo playback
    int idle_frames;                    // 0x00474CA4
    int next_demo;                      // 0x00474CA8
};
typedef char TitleGameStateFlags[offsetof(TitleGameState, flags) == 0x5c ? 1 : -1];
extern "C" {
    extern unsigned int g_input_keys_raw;
    extern TitleGameState g_globals_score;
    extern int g_main_state, g_main_mode_request;
    extern unsigned int g_app_flags;
    extern const char* g_title_demo_paths[4];
    extern char g_replay_path[];
    extern unsigned char g_stage_routes[];
    extern unsigned char* g_stage_route_current;
    extern GameThread_0040c540* g_ascii_manager;
    extern float flt_0_99, flt_1_01, flt_1;
}
// These declarations describe logical inputs, not promises about retail ABI.
__declspec(noinline) DemoFile* __stdcall TitleLoadDemo(const char* path);
__declspec(noinline) void __stdcall TitleReleaseDemo(DemoFile* file);
__declspec(noinline) void __stdcall TitleSetMusicFile(int slot, const char* path);
__declspec(noinline) void __stdcall TitlePlayMusic(int first, int second);
__declspec(noinline) void TitleDispatchGame();
__declspec(noinline) int __stdcall TitleMainMenu(Title* room);
__declspec(noinline) int __stdcall TitleOptions(Title* room);
__declspec(noinline) int __stdcall TitleMenuFlow(Title* room);
__declspec(noinline) int __stdcall TitleMode6(Title* room);
__declspec(noinline) int __stdcall TitleMode7(Title* room);
__declspec(noinline) int __stdcall TitleMode8(Title* room);
__declspec(noinline) int __stdcall TitleMode9(Title* room);
__declspec(noinline) int __stdcall TitleMode11(Title* room);
__declspec(noinline) int __stdcall TitleMode12(Title* room);
__declspec(noinline) int __stdcall TitleNameEntry(Title* room);
__declspec(noinline) int __stdcall TitleMode16(Title* room);

static __forceinline void SetSelection(MenuCursor* cursor, int requested) {
    if (cursor->item_count != 0)
        cursor->selection = requested >= cursor->item_count ? cursor->item_count - 1 : requested;
    else
        cursor->selection = requested;
}
// Frames added per tick, read as the timer's own accessor does.
static __forceinline float TimerSpeed(const RecoveryTimer_0040bd80& timer) { return *timer.speed; }
static __forceinline void MarkTitleCallback(Title* room) {
    reinterpret_cast<TitlePrefix*>(room)->callback->flags |= 2;
}

// Count the idle frames of the title and the main menu; after 900 of them
// set up the next demo replay.  Returns how the title is to be entered.
static __forceinline int UpdateIdleDemo(TitlePrefix* title) {
    switch (title->mode) { case 1: case 2:
        ++g_globals_score.idle_frames;
        if ((g_input_keys_raw & 0x160b) != 0) {
            g_globals_score.idle_frames = 0;
        } else if (g_globals_score.idle_frames >= 900) {
            g_globals_score.flags = (g_globals_score.flags & ~0x40u) | 0x20;
            strcpy(g_replay_path, g_title_demo_paths[g_globals_score.next_demo]);
            DemoFile* file = TitleLoadDemo(g_replay_path);
            g_globals_score.next_demo = (g_globals_score.next_demo + 1) % 4;
            int stage = 0;
            while (stage < 8 && file->stages[stage].present == 0)
                ++stage;
            g_stage_route_current = g_stage_routes + stage * 0x30;
            g_globals_score.stage = stage;
            g_globals_score.first_stage = stage;
            g_main_state = 12;
            DemoHeader* header = file->header;
            g_globals_score.character = header->character;
            g_globals_score.menu_difficulty = g_globals_score.difficulty;
            g_globals_score.shot = header->shot;
            g_globals_score.difficulty = header->difficulty;
            TitleReleaseDemo(file);
            free(file);
            int mode = title->mode;
            g_globals_score.idle_frames = 0;
            return g_main_mode_request = mode != 1;
        }
    }
    return g_main_mode_request;
}

#pragma code_seg(".text$0042cdf0_model")
__declspec(noinline) int __stdcall TitleDispatcher_Model(
        Title* room) {
    TitlePrefix* title = reinterpret_cast<TitlePrefix*>(room);
    int transition = UpdateIdleDemo(title);
    switch (title->mode) {
    case 0: {
        unsigned char* manager_bytes = reinterpret_cast<unsigned char*>(g_sprt_ctrl);
        SprtCtrl* manager = reinterpret_cast<SprtCtrl*>(g_sprt_ctrl);
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad084));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad088));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad074));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad078));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad06c));
        RecoveryHandle* handle = reinterpret_cast<RecoveryHandle*>(
            reinterpret_cast<unsigned char*>(g_ascii_manager) + 0x89a4);
        RecoveryMusicStopHandle(handle);
        handle->value = 0;
        if (transition == 3) {
            MenuCursor* cursor = &room->cursor;
            room->cursor.item_count = 10;
            SetSelection(cursor, 0);
            cursor->PushSelection();
            room->DisableTimerWithOwner(15);
            RecoveryMusicInstallSlot(room, 91);
            room->SetSlotFrame(91, 9);
            g_main_mode_request = 1;
            MarkTitleCallback(room);
            TitleNameEntry(room);
            break;
        }
        if ((g_globals_score.flags & 0x20) == 0) {
            TitleSetMusicFile(0, "bgm/th10_02.wav");
            TitlePlayMusic(0, 0);
            transition = g_main_mode_request;
        } else {
            g_globals_score.difficulty = g_globals_score.menu_difficulty;
        }
        g_globals_score.flags &= ~0x20u;
        if (transition == 0) {
            room->DisableTimerWithOwner(1);
            g_main_mode_request = 1;
        } else if (transition == 1) {
            if (g_globals_score.difficulty == 4)
                SetSelection(&room->cursor, 1);
            room->DisableTimerWithOwner(2);
            RecoveryMusicInstallSlot(room, 91);
            MarkTitleCallback(room);
            TitleMainMenu(room);
            break;
        } else if (transition == 2) {
            MenuCursor* cursor = &room->cursor;
            room->cursor.item_count = 10;
            SetSelection(cursor, 3);
            cursor->PushSelection();
            room->DisableTimerWithOwner(12);
            RecoveryMusicInstallSlot(room, 91);
            room->SetSlotFrame(91, 9);
            g_main_mode_request = 1;
            MarkTitleCallback(room);
            TitleMode12(room);
            break;
        }
        EndingScreen_Update_0042d300(room);
        break;
    }
    case 1: EndingScreen_Update_0042d300(room); break;
    case 2: MarkTitleCallback(room); TitleMainMenu(room); break;
    case 4: TitleOptions(room); break;
    case 5: TitleMenuFlow(room); break;
    case 3:
        g_main_state = (~(g_app_flags >> 12) & 1) | 2;
        // The same launch path serves modes 3, 10, and 13.
    case 10: case 13: TitleDispatchGame(); break;
    case 6: TitleMode6(room); break;
    case 7: TitleMode7(room); break;
    case 8: TitleMode8(room); break;
    case 9: TitleMode9(room); break;
    case 14: Title_UpdateMusicRoom(room); break;
    case 11: TitleMode11(room); break;
    case 12: TitleMode12(room); break;
    case 15: TitleNameEntry(room); break;
    case 16: TitleMode16(room); break;
    }
    room->timer.previous = room->timer.current;
    if (*room->timer.speed > 0.99f && TimerSpeed(room->timer) < 1.01f) {
        ++room->timer.current;
        room->timer.elapsed += 1.0f;
    } else {
        room->timer.current = int(room->timer.elapsed += *room->timer.speed);
    }
    return 1;
}


// The dispatcher's one caller (0x0042D2E0), and the game state as one object
// whose address escapes in the whole program.
struct TitleModel {
    __declspec(noinline) int Update();
};
int TitleModel::Update() {
    return TitleDispatcher_Model(reinterpret_cast<Title*>(this));
}
extern "C" void __stdcall TitleDispatcherEscape(void** objects) {
    objects[0] = &g_globals_score;
}
#pragma code_seg()
