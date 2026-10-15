// 0x00433EF0: the music room of the title menu.
//
// Phase 0 loads musiccmt.txt on its first frame, parses it into the track
// files, titles and eight comment lines each, and slides two title rows in
// per frame. Phase 1 reveals the comment of the chosen track, one line every
// other frame. Phase 2 does the same and moves the cursor over the tracks;
// confirm plays the chosen track (a track not heard yet first shows a
// spoiler warning and wants a second confirm), cancel leaves through phase 3,
// which removes the screen and returns to the main menu.
//
// Written from the retail instructions block by block; linked with the
// title-menu cluster (layout/ltcg/difficulty_select_update_00430320.json)
// for the bodies of the routines it calls.
#include "th10/game/title_menu.hpp"
#include "th10/game/difficulty_select_update_00430320.hpp"
#include "th10/render/resource_registrar_0043e460.hpp"
#include <math.h>

extern "C" void* data_00491c10;
extern "C" GameThread_0040c540* g_ascii_manager;
extern "C" SoundQueue data_00492590;
extern "C" unsigned int data_00474e36;
extern "C" unsigned short recovery_music_repeat_00474e34;
extern "C" unsigned char* recovery_music_player_0047783c;
extern "C" unsigned char recovery_music_mode_00491d78;
extern "C" void* recovery_music_preview_resource_00491fec;
extern "C" float data_00476f78;
extern "C" RecoveryMusicVector_00433ef0 recovery_music_defaults_00491c14;
extern "C" const char recovery_music_locked_format_0046ecf4[];
extern "C" const char recovery_music_comment_file_0046ed14[];
extern "C" const char recovery_music_dummy_0046df98[];
extern "C" const char recovery_music_restore_bgm_0046f018[];
extern "C" const char* recovery_music_preview_table_00476fd8[8];
extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* object);
struct AnimationResource_00449870 {
    __declspec(noinline) void* InitializeObject(void* object, int index);
};
extern "C" int __stdcall recovery_replace_extension_00420a90(int selector, const char* path);
extern "C" int __stdcall recovery_play_dummy_00420b10(int selector, int slot);

static __forceinline RecoveryMusicVm_00433ef0* MusicFind(unsigned int handle) {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle) };
    return static_cast<RecoveryMusicVm_00433ef0*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
            reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id));
}

static __forceinline void MusicSetTreeFrame(RecoveryMusicVm_00433ef0* object, unsigned short frame) {
    if (object != 0) {
        object->stop_frame = frame;
        if (object->children_flagged == 0) {
            for (RecoveryMusicChild_00433ef0* child = object->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

static __forceinline void MusicResetTimer(RecoveryTimer_0040bd80* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &data_00476f78;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}

// Select an item, clamped to the last one when the menu has items.
static __forceinline void MusicSelect(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : index;
    else
        cursor.selection = index;
}

// 0x0042C670, 0x004349E0, 0x00434A20: defined in their own sources.
void __stdcall RecoveryMusicInstallSlot_0042c670(Title* room, int index);
char* __stdcall StageText_SkipLine(char* cursor, int* remaining);
char* __stdcall StageText_ExtractLine(char* cursor, char* destination, int* remaining);
void __stdcall RecoveryMusicStopHandle_00409e50(RecoveryHandle_0040bd80* handle);

// The body of 0x00448D00, where the whole-program link expanded it in place.
static __forceinline void** MusicCreateInPlace(void* resource, void** out, int script, int bucket) {
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        asm_FUN_00449950_00449950(data_00491c10));
    unsigned int flags = object->flags;
    object->render_bucket = bucket;
    object->flags = flags | 0x40000000u;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object, script);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10, out, object);
    return out;
}
// The body of 0x00449450, likewise.
static __forceinline RecoveryMusicVm_00433ef0* MusicValidateInPlace(RecoveryHandle_0040bd80* handle) {
    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle->value) };
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10)->Find(
            reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id));
    if (object == 0)
        handle->value = 0;
    return object;
}

static __forceinline unsigned int MusicRegisterObject(void* resource, int script) {
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        asm_FUN_00449950_00449950(data_00491c10));
    object->flags |= 0x40000000u;
    object->render_bucket = 15;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object, script);
    void* handle;
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10, &handle, object);
    return reinterpret_cast<unsigned int>(handle);
}

// The body of 0x004491C0: the object registered under an id, in the primary
// list and then the secondary one.
static __forceinline RecoveryMusicVm_00433ef0* MusicFindInPlace(
        RecoveryLookupContext_0040bd80* context, unsigned int id) {
    RecoveryLookupNode_0040bd80* node;
    if (!id)
        return 0;
    for (node = context->primary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object)->id == id)
            return reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object);
    for (node = context->secondary; node != 0; node = node->next)
        if (reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object)->id == id)
            return reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object);
    return 0;
}

// 0x00449450: the object a handle names; a stale handle is cleared.
__declspec(noinline) RecoveryMusicVm_00433ef0* __stdcall MusicValidate_00449450(
    RecoveryHandle_0040bd80* handle);

// Show the next line of the chosen track's comment, every other frame. A
// track that has not been heard shows the spoiler warning instead, until the
// player confirms a second time.
static __forceinline void MusicRevealLine(Title* room) {
    if (room->timer.current % 2 == 0 && room->preview_cursor < 8) {
        RecoveryMusicVm_00433ef0* object =
            MusicValidate_00449450(&room->preview_handles[room->preview_cursor]);
        RecoveryTextVm_00447a50* text = reinterpret_cast<RecoveryTextVm_00447a50*>(object);
        if (!recovery_music_player_0047783c[0x1D892 + room->displayed_track] && room->preview_armed)
            text->MarkText(data_00491c10, 0x8080FFu,
                           recovery_music_preview_table_00476fd8[room->preview_cursor]);
        else
            text->MarkText(data_00491c10, 0xFFFFFFu, static_cast<const char*>(
                room->preview_lines[room->displayed_track][room->preview_cursor]));
        object->stop_frame = 2;
        ++room->preview_cursor;
    }
}

#pragma code_seg(".text$00433ef0_model")
__declspec(noinline) int __stdcall TitleMusicRoom_00433ef0(Title* room) {
    RecoveryMusicVector_00433ef0 position;
    void* handle;
    int remaining;
    int index;
    AnimationManager_0043e460* requests;

    switch (room->phase) {
    case 0:
        if (room->timer.current == 1) {
            room->cursor.item_count = 6;
            MusicSelect(room->cursor, 0);
            if (MusicFind(room->animation_slots[95]) == 0) {
                RecoveryMusicInstallSlot_0042c670(room, 95);
                room->fallback_handle.value = reinterpret_cast<unsigned int>(
                    *AnimationManager_CreatePrimaryBack_00448d00(
                        g_ascii_manager->animation_resource, &handle, 8, 15));
            }
            RecoveryMusicInstallSlot_0042c670(room, 103);
            int tracks = 0;
            char* text = Archive_LoadFile(recovery_music_comment_file_0046ed14, &remaining, 0);
            room->file_buffer = text;
            if (text == 0)
                goto leave_room;
            while (remaining > 0) {
                if (*text == '#' || *text != '@') {
                    text = StageText_SkipLine(text, &remaining);
                } else {
                    text = StageText_ExtractLine(text + 1, room->titles[tracks], &remaining);
                    text = StageText_ExtractLine(text, room->comments[tracks], &remaining);
                    for (int row = 0; row < 8; ++row)
                        text = StageText_ExtractLine(text, room->preview_lines[tracks][row],
                                                     &remaining);
                    ++tracks;
                }
            }
            room->cursor.item_count = tracks;
            MusicSelect(room->cursor, 0);
            room->scroll_origin = 0;
            room->parsed_track_count = tracks;
            for (int row = 0; row < 8; ++row)
                room->preview_handles[row].value =
                    MusicRegisterObject(recovery_music_preview_resource_00491fec, row + 39);
            room->preview_cursor = 0;
            room->displayed_track = 0;
            room->preview_armed = 0;
        }
        if (room->timer.current < 10) {
            // Two more title rows slide in each frame.
            position.x = 64.0f;
            position.z = 0;
            position.y = 96.0f
                - static_cast<float>(room->scroll_origin) * 20.0f
                + static_cast<float>(room->timer.current * 40 - 40);
            for (index = room->timer.current * 2 - 2; index < room->timer.current * 2; ++index) {
                if (index >= room->parsed_track_count)
                    break;
                void* created;
                room->row_handles[index].value = reinterpret_cast<unsigned int>(
                    *MusicCreateInPlace(room->animation_resource, &created, index + 173, 15));
                RecoveryMusicVm_00433ef0* object = MusicValidateInPlace(&room->row_handles[index]);
                RecoveryTextVm_00447a50* text = reinterpret_cast<RecoveryTextVm_00447a50*>(object);
                if (recovery_music_player_0047783c[0x1D892 + index])
                    text->MarkText(data_00491c10, 0xFFFFFFu,
                                   static_cast<const char*>(room->comments[index]));
                else
                    text->MarkText(data_00491c10, 0xFFFFFFu,
                                   recovery_music_locked_format_0046ecf4, index + 1);
                if (index < room->scroll_origin || index >= room->scroll_origin + 10)
                    object->flags &= ~2u;
                else
                    object->flags |= 2u;
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x - 4.0);
                object->InitializeTransition(&object->position, &position, 4, 0);
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x + 4.0);
                position.y = position.y + 20.0f;
                object->stop_frame = static_cast<unsigned short>(2 + (index != room->cursor.selection));
            }
        }
        if (room->timer.current >= 10) {
            room->phase = 1;
            MusicResetTimer(&room->timer);
        }
        break;
    case 1:
        MusicRevealLine(room);
        if (room->timer.current > 4)
            room->SetTimerTarget(2);
        break;
    case 2: {
        MusicRevealLine(room);
        MenuCursor* cursor = &room->cursor;
        cursor->previous_selection = cursor->selection;
        if (data_00474e30.InputMaskActive(0x10))
            cursor->Advance(-1);
        if (data_00474e30.InputMaskActive(0x20))
            cursor->Advance(1);
        if (cursor->previous_selection != cursor->selection) {
            data_00492590.Queue(12, 0);
            // Keep the cursor inside the ten visible rows.
            int scroll = room->scroll_origin;
            int selection = cursor->selection;
            if (selection < scroll)
                room->scroll_origin = selection;
            else if (selection >= scroll + 10)
                room->scroll_origin = selection - 9;
            position.x = 64.0f;
            position.z = 0;
            position.y = 96.0f
                - static_cast<float>(room->scroll_origin) * 20.0f;
            for (index = 0; index < room->parsed_track_count; ++index) {
                RecoveryMusicVm_00433ef0* object = MusicValidateInPlace(&room->row_handles[index]);
                if (index < room->scroll_origin || index >= room->scroll_origin + 10)
                    object->flags &= ~2u;
                else
                    object->flags |= 2u;
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x - 4.0);
                // A row that is near its place slides to it; one far away jumps.
                if (fabs(object->position.y - position.y) < 40.0f)
                    object->InitializeTransition(&object->position, &position, 4, 0);
                else
                    object->position = position;
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x + 4.0);
                position.y = position.y + 20.0f;
                object->stop_frame = static_cast<unsigned short>(2 + (index != room->cursor.selection));
            }
            room->preview_armed = 0;
        }
        if (data_00474e36 & 0x1001u) {
            // Confirm: clear the comment lines and play the track.
            for (int row = 0; row < 8; ++row)
                MusicSetTreeFrame(MusicFind(room->preview_handles[row].value), 3);
            room->displayed_track = room->cursor.selection;
            room->preview_cursor = 0;
            MusicResetTimer(&room->timer);
            requests = reinterpret_cast<AnimationManager_0043e460*>(&data_00492590);
            if (!recovery_music_player_0047783c[0x1D892 + room->displayed_track]
                    && !room->preview_armed) {
                if (recovery_music_mode_00491d78 & 0x10u)
                    requests->RegisterResource(recovery_music_dummy_0046df98, 4, 0);
                else
                    requests->RegisterResource(recovery_music_dummy_0046df98, 3, 0);
                room->preview_armed = 1;
                break;
            }
            recovery_replace_extension_00420a90(0, room->titles[room->cursor.selection]);
            if (recovery_music_mode_00491d78 & 0x10u)
                requests->RegisterResource(recovery_music_dummy_0046df98, 4, 0);
            requests->RegisterResource(recovery_music_dummy_0046df98, 2, 0);
            recovery_music_player_0047783c[0x1D892] = 1;
            room->preview_armed = 0;
            break;
        }
        if (!(data_00474e36 & 0xAu))
            break;
leave_room:
        // Cancel, or no comment file: drop the screen and go to phase 3.
        if (room->file_buffer != 0) {
            entry_free_00452422(room->file_buffer);
            room->file_buffer = 0;
        }
        room->file_buffer = 0;
        room->cursor.PopSelection();
        for (int row = 0; row < room->parsed_track_count; ++row)
            RecoveryMusicStopHandle_00409e50(&room->row_handles[row]);
        // 0x00409E50 on each comment line, the search of 0x004491C0 expanded in place.
        for (int row = 0; row < 8; ++row)
            MusicSetTreeFrame(MusicFindInPlace(
                reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10),
                room->preview_handles[row].value), 1);
        data_00492590.Queue(11, 0);
        room->phase = 3;
        MusicResetTimer(&room->timer);
        break;
    }
    case 3:
        if (room->timer.current >= 10) {
            room->ClearAnimationSlot(103);
            room->SetSlotFrame(90, 8);
            room->SetSlotFrame(91, 8);
            room->ClearAnimationSlot(95);
            RecoveryMusicStopHandle_00409e50(&room->fallback_handle);
            room->DisableTimerWithOwner(2);
            recovery_replace_extension_00420a90(0, recovery_music_restore_bgm_0046f018);
            recovery_play_dummy_00420b10(0, 0);
            room->cursor.PopSelection();
        }
        break;
    }
    return 0;
}

// Context for the checking link: stand-in for 0x00449450, which the
// whole-program link passes its handle in ESI.
#pragma code_seg(".text$00449450_model")
__declspec(noinline) RecoveryMusicVm_00433ef0* __stdcall MusicValidate_00449450(
        RecoveryHandle_0040bd80* handle) {
    RecoveryMusicVm_00433ef0* object = MusicFind(handle->value);
    if (object == 0)
        handle->value = 0;
    return object;
}
#pragma code_seg()
