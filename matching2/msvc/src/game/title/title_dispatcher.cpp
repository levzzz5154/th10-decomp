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
    extern unsigned int data_00474e30;
    extern TitleGameState data_00474c44;
    extern int data_00491fb8, data_00491c00;
    extern unsigned int data_00491ff4;
    extern const char* data_00476ff8[4];
    extern char data_00477710[];
    extern unsigned char data_00474788[];
    extern unsigned char* data_00477848;
    extern GameThread_0040c540* g_ascii_manager;
    extern float data_00470b68, data_00470b64, data_00470afc;
}
// These declarations describe logical inputs, not promises about retail ABI.
__declspec(noinline) DemoFile* __stdcall TitleLoadDemo_004296f0(const char* path);
__declspec(noinline) void __stdcall TitleReleaseDemo_004294a0(DemoFile* file);
__declspec(noinline) void __stdcall TitleSetMusicFile_00420a90(int slot, const char* path);
__declspec(noinline) void __stdcall TitlePlayMusic_00420b10(int first, int second);
__declspec(noinline) void TitleDispatchGame_00420c00();
__declspec(noinline) int __stdcall TitleMainMenu_0042d420(Title* room);
__declspec(noinline) int __stdcall TitleOptions_0042d920(Title* room);
__declspec(noinline) int __stdcall TitleMenuFlow_0042f540(Title* room);
__declspec(noinline) int __stdcall TitleMode6_00430320(Title* room);
__declspec(noinline) int __stdcall TitleMode7_004306a0(Title* room);
__declspec(noinline) int __stdcall TitleMode8_00430a60(Title* room);
__declspec(noinline) int __stdcall TitleMode9_00430ff0(Title* room);
__declspec(noinline) int __stdcall TitleMode11_00431ee0(Title* room);
__declspec(noinline) int __stdcall TitleMode12_004315c0(Title* room);
__declspec(noinline) int __stdcall TitleNameEntry_00432cb0(Title* room);
__declspec(noinline) int __stdcall TitleMode16_00433570(Title* room);

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
        ++data_00474c44.idle_frames;
        if ((data_00474e30 & 0x160b) != 0) {
            data_00474c44.idle_frames = 0;
        } else if (data_00474c44.idle_frames >= 900) {
            data_00474c44.flags = (data_00474c44.flags & ~0x40u) | 0x20;
            strcpy(data_00477710, data_00476ff8[data_00474c44.next_demo]);
            DemoFile* file = TitleLoadDemo_004296f0(data_00477710);
            data_00474c44.next_demo = (data_00474c44.next_demo + 1) % 4;
            int stage = 0;
            while (stage < 8 && file->stages[stage].present == 0)
                ++stage;
            data_00477848 = data_00474788 + stage * 0x30;
            data_00474c44.stage = stage;
            data_00474c44.first_stage = stage;
            data_00491fb8 = 12;
            DemoHeader* header = file->header;
            data_00474c44.character = header->character;
            data_00474c44.menu_difficulty = data_00474c44.difficulty;
            data_00474c44.shot = header->shot;
            data_00474c44.difficulty = header->difficulty;
            TitleReleaseDemo_004294a0(file);
            free(file);
            int mode = title->mode;
            data_00474c44.idle_frames = 0;
            return data_00491c00 = mode != 1;
        }
    }
    return data_00491c00;
}

#pragma code_seg(".text$0042cdf0_model")
__declspec(noinline) int __stdcall TitleDispatcher_Model_0042cdf0(
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
        RecoveryHandle_0040bd80* handle = reinterpret_cast<RecoveryHandle_0040bd80*>(
            reinterpret_cast<unsigned char*>(g_ascii_manager) + 0x89a4);
        RecoveryMusicStopHandle_00409e50(handle);
        handle->value = 0;
        if (transition == 3) {
            MenuCursor* cursor = &room->cursor;
            room->cursor.item_count = 10;
            SetSelection(cursor, 0);
            cursor->PushSelection();
            room->DisableTimerWithOwner(15);
            RecoveryMusicInstallSlot_0042c670(room, 91);
            room->SetSlotFrame(91, 9);
            data_00491c00 = 1;
            MarkTitleCallback(room);
            TitleNameEntry_00432cb0(room);
            break;
        }
        if ((data_00474c44.flags & 0x20) == 0) {
            TitleSetMusicFile_00420a90(0, "bgm/th10_02.wav");
            TitlePlayMusic_00420b10(0, 0);
            transition = data_00491c00;
        } else {
            data_00474c44.difficulty = data_00474c44.menu_difficulty;
        }
        data_00474c44.flags &= ~0x20u;
        if (transition == 0) {
            room->DisableTimerWithOwner(1);
            data_00491c00 = 1;
        } else if (transition == 1) {
            if (data_00474c44.difficulty == 4)
                SetSelection(&room->cursor, 1);
            room->DisableTimerWithOwner(2);
            RecoveryMusicInstallSlot_0042c670(room, 91);
            MarkTitleCallback(room);
            TitleMainMenu_0042d420(room);
            break;
        } else if (transition == 2) {
            MenuCursor* cursor = &room->cursor;
            room->cursor.item_count = 10;
            SetSelection(cursor, 3);
            cursor->PushSelection();
            room->DisableTimerWithOwner(12);
            RecoveryMusicInstallSlot_0042c670(room, 91);
            room->SetSlotFrame(91, 9);
            data_00491c00 = 1;
            MarkTitleCallback(room);
            TitleMode12_004315c0(room);
            break;
        }
        EndingScreen_Update_0042d300(room);
        break;
    }
    case 1: EndingScreen_Update_0042d300(room); break;
    case 2: MarkTitleCallback(room); TitleMainMenu_0042d420(room); break;
    case 4: TitleOptions_0042d920(room); break;
    case 5: TitleMenuFlow_0042f540(room); break;
    case 3:
        data_00491fb8 = (~(data_00491ff4 >> 12) & 1) | 2;
        // The same launch path serves modes 3, 10, and 13.
    case 10: case 13: TitleDispatchGame_00420c00(); break;
    case 6: TitleMode6_00430320(room); break;
    case 7: TitleMode7_004306a0(room); break;
    case 8: TitleMode8_00430a60(room); break;
    case 9: TitleMode9_00430ff0(room); break;
    case 14: Title_UpdateMusicRoom(room); break;
    case 11: TitleMode11_00431ee0(room); break;
    case 12: TitleMode12_004315c0(room); break;
    case 15: TitleNameEntry_00432cb0(room); break;
    case 16: TitleMode16_00433570(room); break;
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
struct TitleModel_0042cdf0 {
    __declspec(noinline) int Update();
};
int TitleModel_0042cdf0::Update() {
    return TitleDispatcher_Model_0042cdf0(reinterpret_cast<Title*>(this));
}
extern "C" void __stdcall TitleDispatcherEscape_0042cdf0(void** objects) {
    objects[0] = &data_00474c44;
}
#pragma code_seg()
