// Complete readable caller baseline. Unselected; private leaf ABIs require LTCG.
#include "ending_screen.cpp"
#include "th10/render/animation_resource_removal.hpp"
#include <stdlib.h>

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
extern "C" {
    extern unsigned int g_input_keys_raw;
    extern unsigned int g_globals_flags;
    extern int g_title_idle_frames, g_title_demo_index;
    extern int g_globals_character, g_globals_shot_type, g_globals_difficulty, g_menu_difficulty_saved;
    extern int g_globals_stage, g_globals_stage_shown, g_main_state, g_main_mode_request;
    extern unsigned int g_app_flags;
    extern const char* g_title_demo_paths[4];
    extern char g_replay_path[];
    extern unsigned char g_stage_routes[];
    extern unsigned char* g_stage_route_current;
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
    int count = cursor->item_count;
    if (count == 0)
        cursor->selection = requested;
    else if (count <= requested)
        cursor->selection = count - 1;
    else
        cursor->selection = requested;
}
static __forceinline void MarkTitleCallback(Title* room) {
    reinterpret_cast<TitlePrefix*>(room)->callback->flags |= 2;
}

#pragma code_seg(".text$0042cdf0_fn")
__declspec(noinline) int __stdcall Title_DispatchUpdate(
        Title* room) {
    TitlePrefix* title = reinterpret_cast<TitlePrefix*>(room);
    if (title->mode == 1 || title->mode == 2) {
        ++g_title_idle_frames;
        if ((g_input_keys_raw & 0x160b) != 0) {
            g_title_idle_frames = 0;
        } else if (g_title_idle_frames >= 900) {
            g_globals_flags = (g_globals_flags & ~0x40u) | 0x20;
            const char* source = g_title_demo_paths[g_title_demo_index];
            char* destination = g_replay_path;
            do { *destination++ = *source; } while (*source++ != '\0');
            DemoFile* file = TitleLoadDemo(g_replay_path);
            g_title_demo_index = (g_title_demo_index + 1) % 4;
            int stage = 0;
            while (stage < 8 && file->stages[stage].present == 0)
                ++stage;
            g_globals_stage = stage;
            g_globals_stage_shown = stage;
            g_main_state = 12;
            DemoHeader* header = file->header;
            g_globals_character = header->character;
            g_stage_route_current = g_stage_routes + stage * 0x30;
            g_globals_shot_type = header->shot;
            g_menu_difficulty_saved = g_globals_difficulty;
            g_globals_difficulty = header->difficulty;
            TitleReleaseDemo(file);
            free(file);
            g_title_idle_frames = 0;
            g_main_mode_request = title->mode != 1;
        }
    }
    int transition = g_main_mode_request;
    switch (title->mode) {
    case 0: {
        unsigned char* manager_bytes = reinterpret_cast<unsigned char*>(g_sprt_ctrl);
        SprtCtrl* manager = reinterpret_cast<SprtCtrl*>(g_sprt_ctrl);
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad084));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad088));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad074));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad078));
        manager->MarkResourceForRemoval(*reinterpret_cast<void**>(manager_bytes + 0x3ad06c));
        AnimationHandle3* handle = reinterpret_cast<AnimationHandle3*>(
            reinterpret_cast<unsigned char*>(g_ascii_manager) + 0x89a4);
        StopHandle2(handle);
        handle->id = 0;
        if (transition == 3) {
            room->cursor.item_count = 10;
            SetSelection(&room->cursor, 0);
            room->cursor.PushSelection();
            room->DisableTimerWithOwner(15);
            RecoveryMusicInstallSlot(room, 91);
            room->SetSlotFrame(91, 9);
            g_main_mode_request = 1;
            MarkTitleCallback(room);
            TitleNameEntry(room);
            break;
        }
        if ((g_globals_flags & 0x20) == 0) {
            TitleSetMusicFile(0, "bgm/th10_02.wav");
            TitlePlayMusic(0, 0);
            transition = g_main_mode_request;
        } else {
            g_globals_difficulty = g_menu_difficulty_saved;
        }
        g_globals_flags &= ~0x20u;
        if (transition == 0) {
            room->DisableTimerWithOwner(1);
            g_main_mode_request = 1;
        } else if (transition == 1) {
            if (g_globals_difficulty == 4)
                SetSelection(&room->cursor, 1);
            room->DisableTimerWithOwner(2);
            RecoveryMusicInstallSlot(room, 91);
            MarkTitleCallback(room);
            TitleMainMenu(room);
            break;
        } else if (transition == 2) {
            room->cursor.item_count = 10;
            SetSelection(&room->cursor, 3);
            room->cursor.PushSelection();
            room->DisableTimerWithOwner(12);
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
    case 1: EndingScreen_Update2(room); break;
    case 2: MarkTitleCallback(room); TitleMainMenu(room); break;
    case 3:
        g_main_state = (~(g_app_flags >> 12) & 1) | 2;
        // The same launch path serves modes 3, 10, and 13.
    case 10: case 13: TitleDispatchGame(); break;
    case 4: TitleOptions(room); break;
    case 5: TitleMenuFlow(room); break;
    case 6: TitleMode6(room); break;
    case 7: TitleMode7(room); break;
    case 8: TitleMode8(room); break;
    case 9: TitleMode9(room); break;
    case 11: TitleMode11(room); break;
    case 12: TitleMode12(room); break;
    case 14: Title_UpdateMusicRoom(room); break;
    case 15: TitleNameEntry(room); break;
    case 16: TitleMode16(room); break;
    }
    room->timer.previous = room->timer.current;
    if (flt_0_99 < *room->timer.speed && *room->timer.speed < flt_1_01) {
        room->timer.elapsed += flt_1;
        ++room->timer.current;
    } else {
        room->timer.elapsed += *room->timer.speed;
        room->timer.current = static_cast<int>(room->timer.elapsed);
    }
    return 1;
}

#pragma code_seg()
