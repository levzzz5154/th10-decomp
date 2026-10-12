// 0x00433EF0..0x004349DB: the music room of the title menu (and its
// four-entry phase table), reached from the main menu.
//
// Phase 0 loads musiccmt.txt on the first frame and parses it into 32 track
// titles, comments and eight preview lines each; the title rows slide in
// while the timer runs.  Phase 1 reveals the comment of the selected track
// two characters per even frame.  Phase 2 moves the cursor over the tracks;
// confirm starts the preview of the selected track (with an extra
// acknowledgement when its comment is a spoiler warning), cancel leaves
// through phase 3, which removes the screen and returns to the main menu.
//
// The room is a stack argument; the handler is linked with the title
// dispatcher and the real bodies of its leaves
// (layout/ltcg/difficulty_select_update_00430320.json).
//
// Equivalent recovery: the x87 row positions, the vararg title drawing and
// the inlined parser keep source-level shapes the image does not record
// (reference/recovery_notes/ui_final_runtime_00433ef0_equivalent_2026_10_12.md).
#include "th10/game/ui_final_runtime_00433ef0.hpp"
#include "th10/game/difficulty_select_update_00430320.hpp"
#include "th10/game/game_thread.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/render/resource_registrar_0043e460.hpp"

// The per-track "heard" flags live behind the progress pointer at +0x1D892.
struct MusicProgressHeard_00433ef0 {
    unsigned char reserved_00000[0x1D892];
    unsigned char track_heard[32];
};

extern "C" {
extern char* __stdcall StageText_SkipLine(char* cursor, int* remaining);
extern char* __stdcall StageText_ExtractLine(char* cursor, char* destination,
                                             int* remaining);
extern const char data_0046ecf4[];               // "No.%d  ？？？？？？？？？？？"
extern AnimationManager_0043e460 g_music_requests;  // 0x00492590
extern unsigned char g_config_flags;             // 0x00491D78
extern MusicProgressHeard_00433ef0* g_music_progress;  // 0x0047783C
extern const float data_00470ca0;                // 20.0: the row pitch
extern const double data_00470c98;               // 4.0: the selected row's y offset
extern const float data_00470c64;                // 40.0: the slide-in threshold
extern const char data_0046df98[];               // "dummy": the request placeholder
extern const float data_00470c80;                // 96.0: the first row's y
}

// Select an item, clamped to the last one when the menu has items.
static __forceinline void SelectItem_00433ef0(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// The animation a handle refers to (0x00449450): look it up through the
// manager's Find and blank the slot when nothing answers.
static __forceinline RecoveryMusicVm_00433ef0* ValidateHandle_00433ef0(
        RecoveryHandle_0040bd80* slot) {
    RecoveryMusicVm_00433ef0* found = reinterpret_cast<RecoveryMusicVm_00433ef0*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
            reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
            *reinterpret_cast<RecoveryScriptId_0040bd80*>(slot)));
    if (found == 0)
        slot->value = 0;
    return found;
}

// Stop an animation and its children at a frame.
static __forceinline void SetTreeFrame_00433ef0(RecoveryMusicVm_00433ef0* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild_00433ef0* child = object->children; child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

// Flag (or clear) the "sliding" bit of an animation and its children.
static __forceinline void SetTreeFlag_00433ef0(RecoveryMusicVm_00433ef0* object, unsigned int mask, int on) {
    if (object != 0) {
        object->flags = on ? object->flags | mask : object->flags & ~mask;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild_00433ef0* child = object->children; child != 0; child = child->next)
                child->object->flags =
                    on ? child->object->flags | mask : child->object->flags & ~mask;
        }
    }
}

// The music test resource requests (0x0043E460, "dummy" commands).
static __forceinline void MusicCommand_00433ef0(int command) {
    g_music_requests.RegisterResource(data_0046df98, command, 0);
}



#pragma code_seg(".text$00433ef0_fn")
__declspec(noinline) int __stdcall TitleMusicRoom_00433ef0(RecoveryMusicRoom_00433ef0* room) {
    MusicRoom_00433ef0* music = reinterpret_cast<MusicRoom_00433ef0*>(room);
    char* cursor;
    int remaining;
    switch (room->phase) {
    case 0:
        if (room->timer.current == 1) {
            room->cursor.item_count = 6;
            SelectItem_00433ef0(room->cursor, 0);
            if (ValidateHandle_00433ef0(reinterpret_cast<RecoveryHandle_0040bd80*>(&room->animation_slots[95])) == 0) {
                RecoveryMusicInstallSlot_0042c670(room, 95);
                void* resource = data_004776e0->animation_resource;
                void* handle;
                void** result = AnimationManager_CreatePrimaryBack_00448d00(resource, &handle, 8, 15);
                room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
            }
            RecoveryMusicInstallSlot_0042c670(room, 103);
            music->file_buffer = Archive_LoadFile("musiccmt.txt", &remaining, 0);
            if (music->file_buffer == 0)
                goto cancel;
            cursor = music->file_buffer;
            int parsed;
            parsed = 0;
            while (remaining > 0) {
                char c = *cursor;
                if (c != '#' && c != '@') {
                    cursor = StageText_SkipLine(cursor, &remaining);
                    continue;
                }
                cursor = StageText_ExtractLine(cursor + 1, music->titles[parsed], &remaining);
                cursor = StageText_ExtractLine(cursor, music->comments[parsed], &remaining);
                for (int line = 0; line < 8; ++line)
                    cursor = StageText_ExtractLine(
                        cursor, music->preview_lines[parsed][line], &remaining);
                ++parsed;
            }
            music->parsed_track_count = parsed;
            SelectItem_00433ef0(room->cursor, 0);
            music->scroll_origin = 0;
            music->preview_cursor = 0;
            music->displayed_track = 0;
            music->preview_armed = 0;
        }
        if (room->timer.current >= 10) {
            room->SetTimerTarget(1);
            break;
        }
        {
            // Slide the next two rows in and draw the revealed ones.
            float y = data_00470c80
                - static_cast<float>(music->scroll_origin) * data_00470ca0
                + static_cast<float>(room->timer.current * 40 - 40);
            float position_y = 64.0f;
            for (int i = room->timer.current * 2 - 2;
                 i < room->timer.current * 2 && i < music->parsed_track_count; ++i) {
                RecoveryMusicVm_00433ef0* row = ValidateHandle_00433ef0(&room->row_handles[i]);
                row->flags |= 0x40000000u;
                row->render_bucket = 15;
                if (g_music_progress->track_heard[i] != 0)
                    reinterpret_cast<RecoveryTextVm_00447a50*>(row)->MarkText(
                        data_00491c10, 0x00FFFFFFu, static_cast<const char*>(music->comments[i]));
                else
                    reinterpret_cast<RecoveryTextVm_00447a50*>(row)->MarkText(
                        data_00491c10, 0x00FFFFFFu, "No.%d", i + 1);
                SetTreeFlag_00433ef0(row, 2u, music->scroll_origin <= i && i < music->scroll_origin + 10);
                if (i == room->cursor.selection)
                    position_y -= static_cast<float>(data_00470c98);
                StageTextVector_00434a80 position = {position_y, y, 0.0f};
                reinterpret_cast<StageText_00434a80*>(row)->Initialize(
                    reinterpret_cast<const StageTextVector_00434a80*>(&row->position),
                    &position, 4, 0);
                if (i == room->cursor.selection)
                    position_y += static_cast<float>(data_00470c98);
                y += data_00470ca0;
                row->flags = (row->flags & ~0xFFFFu) | (i != room->cursor.selection ? 4u : 2u);
            }
        }
        break;
    case 1:
        if (room->timer.current % 2 == 0 && music->preview_cursor < 8) {
            RecoveryMusicVm_00433ef0* line = ValidateHandle_00433ef0(
                &room->preview_handles[music->preview_cursor]);
            reinterpret_cast<RecoveryTextVm_00447a50*>(line)->MarkText(
                data_00491c10,
                g_music_progress->track_heard[music->displayed_track] != 0
                        && music->preview_armed != 0
                    ? 0x8080FFu : 0x00FFFFFFu,
                static_cast<const char*>(music->preview_lines[music->displayed_track]
                                                             [music->preview_cursor]));
            line->flags = (line->flags & ~0xFFFFu) | 2u;
            ++music->preview_cursor;
        }
        if (room->timer.current > 4)
            room->SetTimerTarget(2);
        break;
    case 2: {
        if (room->timer.current % 2 == 0 && music->preview_cursor < 8) {
            RecoveryMusicVm_00433ef0* line = ValidateHandle_00433ef0(
                &room->preview_handles[music->preview_cursor]);
            reinterpret_cast<RecoveryTextVm_00447a50*>(line)->MarkText(
                data_00491c10,
                g_music_progress->track_heard[music->displayed_track] != 0
                        && music->preview_armed != 0
                    ? 0x8080FFu : 0x00FFFFFFu,
                static_cast<const char*>(music->preview_lines[music->displayed_track]
                                                             [music->preview_cursor]));
            line->flags = (line->flags & ~0xFFFFu) | 2u;
            ++music->preview_cursor;
        }
        room->cursor.previous_selection = room->cursor.selection;
        if ((short)data_00474e30.InputMaskActive(0x10)) room->cursor.Advance(-1);
        if ((short)data_00474e30.InputMaskActive(0x20)) room->cursor.Advance(1);
        if (room->cursor.previous_selection != room->cursor.selection) {
            data_00492590.Queue(12, 0);
            int selection = room->cursor.selection;
            if (selection >= music->scroll_origin) {
                if (selection >= music->scroll_origin + 10)
                    selection += -9;
            }
            music->scroll_origin = selection;
            float y = data_00470c80 - static_cast<float>(music->scroll_origin) * data_00470ca0;
            float position_y = 64.0f;
            for (int i = 0; i < music->parsed_track_count; ++i) {
                RecoveryMusicVm_00433ef0* row = ValidateHandle_00433ef0(&room->row_handles[i]);
                SetTreeFlag_00433ef0(row, 2u, music->scroll_origin <= i && i < music->scroll_origin + 10);
                if (i == room->cursor.selection)
                    position_y -= static_cast<float>(data_00470c98);
                if (data_00470c64 <= row->position.y - y && row->position.y - y <= data_00470c64) {
                    StageTextVector_00434a80 position = {position_y, y, 0.0f};
                    reinterpret_cast<StageText_00434a80*>(row)->Initialize(
                        reinterpret_cast<const StageTextVector_00434a80*>(&row->position),
                        &position, 4, 0);
                } else {
                    row->position.x = position_y;
                    row->position.y = y;
                    row->position.z = 0.0f;
                }
                if (i == room->cursor.selection)
                    position_y += static_cast<float>(data_00470c98);
                y += data_00470ca0;
                row->flags = (row->flags & ~0xFFFFu) | (i != room->cursor.selection ? 4u : 2u);
            }
            music->preview_armed = 0;
        }
        if ((data_00474e36 & 0x1001) != 0) {
            // Confirm: stop the row text objects and start the preview.
            for (int i = 0; i < 8; ++i)
                SetTreeFrame_00433ef0(
                    ValidateHandle_00433ef0(&room->preview_handles[i]), 3);
            music->displayed_track = room->cursor.selection;
            music->preview_cursor = 0;
            room->SetTimerTarget(1);
            if (g_music_progress->track_heard[music->displayed_track] == 0
                    && music->preview_armed == 0) {
                // Spoiler warning: require a second confirm.
                MusicCommand_00433ef0(g_config_flags & 0x10 ? 4 : 3);
                music->preview_armed = 1;
                return 0;
            }
            Music_Load_00420a90(0, music->preview_lines[music->displayed_track][0]);
            if (g_config_flags & 0x10)
                MusicCommand_00433ef0(4);
            MusicCommand_00433ef0(2);
            g_music_progress->track_heard[music->displayed_track] = 1;
            music->preview_armed = 0;
            return 0;
        }
        if ((data_00474e36 & 0xA) != 0) {
cancel:
            // Cancel: release the file and leave through phase 3.
            if (music->file_buffer != 0) {
                entry_free_00452422(music->file_buffer);
                music->file_buffer = 0;
            }
            room->cursor.PopSelection();
            for (int i = 0; i < music->parsed_track_count; ++i)
                RecoveryMusicStopHandle_00409e50(&room->row_handles[i]);
            for (int i = 0; i < 8; ++i)
                SetTreeFlag_00433ef0(
                    ValidateHandle_00433ef0(&room->preview_handles[i]), 1u, 1);
            data_00492590.Queue(11, 0);
            room->SetTimerTarget(3);
            return 0;
        }
        break;
    }
    case 3:
        if (room->timer.current >= 10) {
            room->ClearAnimationSlot(103);
            reinterpret_cast<AnimationSlotOwner_0042c750*>(room)->StopSlot(90);
            reinterpret_cast<AnimationSlotOwner_0042c750*>(room)->StopSlot(91);
            room->ClearAnimationSlot(95);
            RecoveryMusicStopHandle_00409e50(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            Music_Load_00420a90(0, "bgm/th10_02.wav");
            Music_Play_00420b10(0, 0);
            room->cursor.PopSelection();
        }
        break;
    }
    return 0;
}
#pragma code_seg()
