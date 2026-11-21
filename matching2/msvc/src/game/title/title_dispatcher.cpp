// 0x0042CDF0..0x0042D257: the title screen's per-frame dispatcher: the idle
// counter that starts a demo replay, then the handler of the current mode.
// Built in the title_dispatcher LTCG cluster, whose driver adds its caller.
#include "th10/game/ending_screen.hpp"
#include "th10/game/stage_route.hpp"
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
    DemoStageRecord stages[StageRouteCount];
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
    extern GameThread6* g_ascii_manager;
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
static __forceinline float TimerSpeed(const GameFrameTimer& timer) { return *timer.speed; }
static __forceinline void MarkTitleCallback(Title* room) {
    reinterpret_cast<TitlePrefix*>(room)->callback->flags |= 2;
}

enum TitleModeId {
    TITLE_MODE_INIT = 0,
    TITLE_MODE_OPENING = 1,
    TITLE_MODE_MAIN_MENU = 2,
    TITLE_MODE_LEAVE = 3,
    TITLE_MODE_OPTIONS = 4,
    TITLE_MODE_KEY_CONFIG = 5,
    TITLE_MODE_DIFFICULTY = 6,
    TITLE_MODE_CHARACTER = 7,
    TITLE_MODE_SHOT_TYPE = 8,
    TITLE_MODE_PRACTICE_STAGE = 9,
    TITLE_MODE_LAUNCH_REPLAY = 10,
    TITLE_MODE_SPELL_RECORD = 11,
    TITLE_MODE_REPLAY_SELECT = 12,
    TITLE_MODE_LAUNCH_STAGE = 13,
    TITLE_MODE_MUSIC_ROOM = 14,
    TITLE_MODE_NAME_ENTRY = 15,
    TITLE_MODE_REPLAY_SAVE = 16
};

enum TitleGlobalFlags {
    TITLE_FLAG_DEMO_PLAYBACK = 0x20u,
    TITLE_FLAG_CLEAR_FOR_DEMO = 0x40u,
    TITLE_IDLE_RESET_KEYS = 0x160B
};

// Count the idle frames of the title and the main menu; after 900 of them
// set up the next demo replay.  Returns how the title is to be entered.
static __forceinline int UpdateIdleDemo(TitlePrefix* title) {
    if (title->mode == TITLE_MODE_OPENING || title->mode == TITLE_MODE_MAIN_MENU) {
        ++g_globals_score.idle_frames;
        if ((g_input_keys_raw & TITLE_IDLE_RESET_KEYS) != 0) {
            g_globals_score.idle_frames = 0;
        } else if (g_globals_score.idle_frames >= 900) {
            g_globals_score.flags = (g_globals_score.flags & ~TITLE_FLAG_CLEAR_FOR_DEMO) | TITLE_FLAG_DEMO_PLAYBACK;
            strcpy(g_replay_path, g_title_demo_paths[g_globals_score.next_demo]);
            DemoFile* file = TitleLoadDemo(g_replay_path);
            g_globals_score.next_demo = (g_globals_score.next_demo + 1) % 4;
            int stage = 0;
            while (stage < StageRouteCount && file->stages[stage].present == 0)
                ++stage;
            g_stage_route_current = &g_stage_routes[stage];
            g_globals_score.stage = stage;
            g_globals_score.first_stage = stage;
            g_main_state = 12;
            DemoHeader* header = file->header;
            g_globals_score.character = header->character;
            // Evaluation order matters: the shot load runs before the save of
            // the old difficulty, which fixes the scratch-register rotation.
            g_globals_score.shot = header->shot;
            g_globals_score.menu_difficulty = g_globals_score.difficulty;
            g_globals_score.difficulty = header->difficulty;
            TitleReleaseDemo(file);
            free(file);
            int mode = title->mode;
            g_globals_score.idle_frames = 0;
            return g_main_mode_request = mode != TITLE_MODE_OPENING;
        }
    }
    return g_main_mode_request;
}

#pragma code_seg(".text$0042cdf0_fn")
__declspec(noinline) int __stdcall TitleDispatcher(
        Title* room) {
    TitlePrefix* title = reinterpret_cast<TitlePrefix*>(room);
    int transition = UpdateIdleDemo(title);
    switch (title->mode) {
    case TITLE_MODE_INIT: {
        unsigned char* manager_bytes = reinterpret_cast<unsigned char*>(g_sprt_ctrl);
        SprtCtrl* manager = reinterpret_cast<SprtCtrl*>(g_sprt_ctrl);
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad084));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad088));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad074));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad078));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad06c));
        AnmScriptHandle* handle = reinterpret_cast<AnmScriptHandle*>(
            reinterpret_cast<unsigned char*>(g_ascii_manager) + 0x89a4);
        RecoveryMusicStopHandle(handle);
        handle->value = 0;
        if (transition == 3) {
            MenuCursor* cursor = &room->cursor;
            room->cursor.item_count = 10;
            SetSelection(cursor, 0);
            cursor->PushSelection();
            room->DisableTimerWithOwner(TITLE_MODE_NAME_ENTRY);
            RecoveryMusicInstallSlot(room, 91);
            room->SetSlotFrame(91, 9);
            g_main_mode_request = 1;
            MarkTitleCallback(room);
            TitleNameEntry(room);
            break;
        }
        if ((g_globals_score.flags & TITLE_FLAG_DEMO_PLAYBACK) == 0) {
            TitleSetMusicFile(0, "bgm/th10_02.wav");
            TitlePlayMusic(0, 0);
            transition = g_main_mode_request;
        } else {
            g_globals_score.difficulty = g_globals_score.menu_difficulty;
        }
        g_globals_score.flags &= ~TITLE_FLAG_DEMO_PLAYBACK;
        if (transition == 0) {
            // MATCH: transition is 0 here; the sum (one more expression temporary)
            // puts the closing timer add's fld/fadd in retail's order.
            room->DisableTimerWithOwner(transition + 1);
            g_main_mode_request = 1;
        } else if (transition == 1) {
            if (g_globals_score.difficulty == 4)
                SetSelection(&room->cursor, 1);
            room->DisableTimerWithOwner(TITLE_MODE_MAIN_MENU);
            RecoveryMusicInstallSlot(room, 91);
            // Entering the main menu shares mode 2's handler call.
            goto main_menu;
        } else if (transition == 2) {
            MenuCursor* cursor = &room->cursor;
            room->cursor.item_count = 10;
            SetSelection(cursor, 3);
            cursor->PushSelection();
            room->DisableTimerWithOwner(TITLE_MODE_REPLAY_SELECT);
            RecoveryMusicInstallSlot(room, 91);
            room->SetSlotFrame(91, 9);
            g_main_mode_request = 1;
            MarkTitleCallback(room);
            TitleMode12(room);
            break;
        }
        EndingScreen_Update2(room);
        break;
    }
    case TITLE_MODE_OPENING: EndingScreen_Update2(room); break;
    case TITLE_MODE_MAIN_MENU: main_menu: MarkTitleCallback(room); TitleMainMenu(room); break;
    case TITLE_MODE_OPTIONS: TitleOptions(room); break;
    case TITLE_MODE_KEY_CONFIG: TitleMenuFlow(room); break;
    case TITLE_MODE_LEAVE:
        g_main_state = (~(g_app_flags >> 12) & 1) | 2;
        // The same launch/leave path serves modes 3, 10, and 13.
    case TITLE_MODE_LAUNCH_REPLAY: case TITLE_MODE_LAUNCH_STAGE: TitleDispatchGame(); break;
    case TITLE_MODE_DIFFICULTY: TitleMode6(room); break;
    case TITLE_MODE_CHARACTER: TitleMode7(room); break;
    case TITLE_MODE_SHOT_TYPE: TitleMode8(room); break;
    case TITLE_MODE_PRACTICE_STAGE: TitleMode9(room); break;
    case TITLE_MODE_MUSIC_ROOM: Title_UpdateMusicRoom(room); break;
    case TITLE_MODE_SPELL_RECORD: TitleMode11(room); break;
    case TITLE_MODE_REPLAY_SELECT: TitleMode12(room); break;
    case TITLE_MODE_NAME_ENTRY: TitleNameEntry(room); break;
    case TITLE_MODE_REPLAY_SAVE: TitleMode16(room); break;
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

#pragma code_seg()
