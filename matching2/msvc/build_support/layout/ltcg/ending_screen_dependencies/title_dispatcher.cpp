// Complete readable caller baseline. Unselected; private leaf ABIs require LTCG.
#include "th10/game/ending_screen_0042d300.hpp"
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
    extern unsigned int data_00474e30;
    extern unsigned int data_00474ca0;
    extern int data_00474ca4, data_00474ca8;
    extern int data_00474c68, data_00474c6c, data_00474c74, data_00474c78;
    extern int data_00474c7c, data_00474c80, data_00491fb8, data_00491c00;
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
__declspec(noinline) void TitleSaveInputHistory_0044be20();
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
        ++data_00474ca4;
        if ((data_00474e30 & 0x160b) != 0) {
            data_00474ca4 = 0;
        } else if (data_00474ca4 >= 900) {
            data_00474ca0 = (data_00474ca0 & ~0x40u) | 0x20;
            const char* source = data_00476ff8[data_00474ca8];
            char* destination = data_00477710;
            do { *destination++ = *source; } while (*source++ != '\0');
            DemoFile* file = TitleLoadDemo_004296f0(data_00477710);
            data_00474ca8 = (data_00474ca8 + 1) % 4;
            int stage = 0;
            while (stage < 8 && file->stages[stage].present == 0)
                ++stage;
            data_00474c7c = stage;
            data_00474c80 = stage;
            data_00491fb8 = 12;
            DemoHeader* header = file->header;
            data_00474c68 = header->character;
            data_00477848 = data_00474788 + stage * 0x30;
            data_00474c6c = header->shot;
            data_00474c78 = data_00474c74;
            data_00474c74 = header->difficulty;
            TitleReleaseDemo_004294a0(file);
            free(file);
            data_00474ca4 = 0;
            data_00491c00 = title->mode != 1;
        }
    }
    int transition = data_00491c00;
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
            room->cursor.item_count = 10;
            SetSelection(&room->cursor, 0);
            TitleSaveInputHistory_0044be20();
            room->DisableTimerWithOwner(15);
            RecoveryMusicInstallSlot_0042c670(room, 91);
            room->SetSlotFrame(91, 9);
            data_00491c00 = 1;
            MarkTitleCallback(room);
            TitleNameEntry_00432cb0(room);
            break;
        }
        if ((data_00474ca0 & 0x20) == 0) {
            TitleSetMusicFile_00420a90(0, "bgm/th10_02.wav");
            TitlePlayMusic_00420b10(0, 0);
            transition = data_00491c00;
        } else {
            data_00474c74 = data_00474c78;
        }
        data_00474ca0 &= ~0x20u;
        if (transition == 0) {
            room->DisableTimerWithOwner(1);
            data_00491c00 = 1;
        } else if (transition == 1) {
            if (data_00474c74 == 4)
                SetSelection(&room->cursor, 1);
            room->DisableTimerWithOwner(2);
            RecoveryMusicInstallSlot_0042c670(room, 91);
            MarkTitleCallback(room);
            TitleMainMenu_0042d420(room);
            break;
        } else if (transition == 2) {
            room->cursor.item_count = 10;
            SetSelection(&room->cursor, 3);
            TitleSaveInputHistory_0044be20();
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
    case 3:
        data_00491fb8 = (~(data_00491ff4 >> 12) & 1) | 2;
        // The same launch path serves modes 3, 10, and 13.
    case 10: case 13: TitleDispatchGame_00420c00(); break;
    case 4: TitleOptions_0042d920(room); break;
    case 5: TitleMenuFlow_0042f540(room); break;
    case 6: TitleMode6_00430320(room); break;
    case 7: TitleMode7_004306a0(room); break;
    case 8: TitleMode8_00430a60(room); break;
    case 9: TitleMode9_00430ff0(room); break;
    case 11: TitleMode11_00431ee0(room); break;
    case 12: TitleMode12_004315c0(room); break;
    case 14: Title_UpdateMusicRoom(room); break;
    case 15: TitleNameEntry_00432cb0(room); break;
    case 16: TitleMode16_00433570(room); break;
    }
    room->timer.previous = room->timer.current;
    if (data_00470b68 < *room->timer.speed && *room->timer.speed < data_00470b64) {
        room->timer.elapsed += data_00470afc;
        ++room->timer.current;
    } else {
        room->timer.elapsed += *room->timer.speed;
        room->timer.current = static_cast<int>(room->timer.elapsed);
    }
    return 1;
}

#pragma code_seg()
