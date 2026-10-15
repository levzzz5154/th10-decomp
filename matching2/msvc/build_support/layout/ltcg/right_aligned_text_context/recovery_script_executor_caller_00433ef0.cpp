#include "../../../include/contexts/game/right_aligned_text_context/recovery_script_executor_caller_00433ef0.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" GameThread_0040c540* g_ascii_manager;
extern "C" SoundQueue data_00492590;
extern "C" unsigned int data_00474e36;
extern "C" unsigned short recovery_music_repeat_00474e34;
extern "C" unsigned char* recovery_music_player_0047783c;
extern "C" unsigned char recovery_music_mode_00491d78;
extern "C" void* recovery_music_preview_resource_00491fec;
extern "C" float data_00476f78;
extern "C" float recovery_music_row_y_00470c80;
extern "C" float recovery_music_row_step_00470ca0;
extern "C" float recovery_music_jump_threshold_00470c64;
extern "C" double recovery_music_selected_offset_00470c98;
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
        reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Find(
            reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl), id));
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

static __forceinline int MusicFirstSelection(int count) {
    if (count == 0)
        return 0;
    if (count < 1)
        return count - 1;
    return 0;
}

// Full genuine ancillary callees are retained here because their private
// argument allocations cannot be represented by opaque external declarations.
#pragma code_seg(".text$0042c5c0_fn")
void Title::DisableTimerWithOwner(int owner) {
    int* request = &timer_owner;
    request[0] = owner;
    request[1] = 0;
    MusicResetTimer(&timer);
}
#pragma code_seg(".text$0042c620_fn")
void Title::SetTimerTarget(int target) {
    phase = target;
    MusicResetTimer(&timer);
}
#pragma code_seg(".text$0042c670_fn")
__declspec(noinline) void __stdcall RecoveryMusicInstallSlot_0042c670(
        Title* room, int index) {
    void* resource = room->animation_resource;
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        asm_FUN_00449950_00449950(g_sprt_ctrl));
    object->flags |= 0x40000000u;
    object->render_bucket = 15;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object, index);
    void* handle;
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, &handle, object);
    room->animation_slots[index] = reinterpret_cast<unsigned int>(handle);
}
#pragma code_seg(".text$004349e0_fn")
__declspec(noinline) char* __stdcall RecoveryMusicSkipLine_004349e0(char* cursor, int* remaining) {
    while (*cursor != '\n' && *cursor != '\r') {
        if (*remaining == 0)
            return cursor;
        ++cursor;
        --*remaining;
    }
    if (*remaining != 0) {
        while (*cursor == '\n' || *cursor == '\r') {
            if (*remaining == 0)
                break;
            ++cursor;
            --*remaining;
        }
    }
    return cursor;
}
#pragma code_seg(".text$00434a20_fn")
__declspec(noinline) char* __stdcall RecoveryMusicExtractLine_00434a20(
        char* cursor, char* destination, int* remaining) {
    char* end = cursor;
    while (*end != '\n') {
        if (*end == '\r')
            break;
        if (*remaining == 0)
            return end;
        ++end;
        --*remaining;
    }
    if (*remaining == 0)
        return end;
    *end = 0;
    while ((*destination++ = *cursor++) != 0) {}
    ++end;
    --*remaining;
    while (*end == '\n' || *end == '\r') {
        if (*remaining == 0)
            break;
        ++end;
        --*remaining;
    }
    return end;
}
#pragma code_seg(".text$00434a80_fn")
void RecoveryMusicVm_00433ef0::InitializeTransition(
        const RecoveryMusicVector_00433ef0* base,
        const RecoveryMusicVector_00433ef0* target, int mode, unsigned char flag) {
    transition_mode = mode;
    const RecoveryMusicVector_00433ef0& defaults = recovery_music_defaults_00491c14;
    defaults_088 = defaults;
    defaults_094 = defaults;
    transition_flag = flag;
    base_transition = *base;
    target_transition = *target;
    MusicResetTimer(&transition_timer);
}
#pragma code_seg(".text$0043e460_fn")
char* RecoveryMusicResourceQueue_0043e460::RegisterResource(
        const char* name, int kind, int parameter) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);
    int slot;
    for (slot = 0; slot < 31; ++slot) {
        unsigned char* record = bytes + 0x1F88 + slot * 0x10C;
        if (*reinterpret_cast<int*>(record) == 0) {
            *reinterpret_cast<int*>(record) = kind;
            *reinterpret_cast<int*>(record + 4) = parameter;
            char* destination = reinterpret_cast<char*>(record + 12);
            while ((*destination++ = *name++) != 0) {}
            *reinterpret_cast<int*>(record + 8) = 0;
            return const_cast<char*>(name);
        }
    }
    return reinterpret_cast<char*>(slot);
}
#pragma code_seg(".text$00409e50_fn")
__declspec(noinline) void __stdcall RecoveryMusicStopHandle_00409e50(RecoveryHandle_0040bd80* handle) {
    MusicSetTreeFrame(MusicFind(handle->value), 1);
}
#pragma code_seg(".text$0044be70_fn")
void MenuCursor::PopSelection() {
    --history_depth;
    if (history_depth < 0)
        history_depth = 0;
    selection = selection_history[history_depth];
    item_count = item_count_history[history_depth];
    disabled_count = 0;
}
#pragma code_seg(".text$0044bea0_fn")
int MenuCursor::Advance(int delta) {
    int count = item_count;
    if (count > 0) {
    retry_selection:
        selection += delta;
        while (selection >= item_count) {
            if (wrap)
                selection -= count;
            else
                selection = count - 1;
        }
        while (selection < 0) {
            if (wrap)
                selection += count;
            else
                selection = 0;
        }
        for (int index = 0; index < disabled_count; ++index)
            if (disabled_items[index] == selection)
                goto retry_selection;
    }
    return selection;
}
#pragma code_seg()

static __forceinline unsigned int MusicRegisterObject(void* resource, int script) {
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        asm_FUN_00449950_00449950(g_sprt_ctrl));
    object->flags |= 0x40000000u;
    object->render_bucket = 15;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object, script);
    void* handle;
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, &handle, object);
    return reinterpret_cast<unsigned int>(handle);
}

#pragma code_seg(".text$00433ef0_fn")
extern "C" __declspec(noinline) int __stdcall Title_UpdateMusicRoom(
        Title* room) {
    switch (room->phase) {
    case 0:
        if (room->timer.current == 1) {
            room->cursor.item_count = 6;
            room->cursor.selection = MusicFirstSelection(room->cursor.item_count);
            if (MusicFind(room->animation_slots[95]) == 0) {
                RecoveryMusicInstallSlot_0042c670(room, 95);
                void* handle;
                void** result = AnimationManager_CreatePrimaryBack_00448d00(
                    g_ascii_manager->animation_resource, &handle, 8, 15);
                room->fallback_handle.value = reinterpret_cast<unsigned int>(*result);
            }
            RecoveryMusicInstallSlot_0042c670(room, 103);
            int remaining;
            int tracks = 0;
            char* text = Archive_LoadFile(recovery_music_comment_file_0046ed14, &remaining, 0);
            room->file_buffer = text;
            if (text == 0)
                goto leave_room;
            if (remaining > 0) {
                char* title = &room->titles[0][0];
                char* comment = &room->comments[0][0];
                char* preview = &room->preview_lines[0][0][0];
                do {
                    if (*text == '#' || *text != '@') {
                        text = RecoveryMusicSkipLine_004349e0(text, &remaining);
                    } else {
                        text = RecoveryMusicExtractLine_00434a20(text + 1, title, &remaining);
                        text = RecoveryMusicExtractLine_00434a20(text, comment, &remaining);
                        for (int row = 8; row != 0; --row) {
                            text = RecoveryMusicExtractLine_00434a20(text, preview, &remaining);
                            preview += 66;
                        }
                        ++tracks;
                        title += 64;
                        comment += 66;
                    }
                } while (remaining > 0);
            }
            room->cursor.item_count = tracks;
            room->cursor.selection = MusicFirstSelection(tracks);
            room->scroll_origin = 0;
            room->parsed_track_count = tracks;
            for (int row = 0; row < 8; ++row)
                room->preview_handles[row].value = MusicRegisterObject(recovery_music_preview_resource_00491fec, row + 39);
            room->preview_cursor = 0;
            room->displayed_track = 0;
            room->preview_armed = 0;
        }
        if (room->timer.current < 10) {
            int index = room->timer.current * 2 - 2;
            RecoveryMusicVector_00433ef0 position;
            position.x = 64.0f;
            position.z = 0;
            position.y = recovery_music_row_y_00470c80 - static_cast<float>(room->scroll_origin) * recovery_music_row_step_00470ca0
                + static_cast<float>(room->timer.current * 40 - 40);
            char* comment = reinterpret_cast<char*>(room) + 0xE98 + index * 66;
            RecoveryHandle_0040bd80* handle = room->row_handles + index;
            while (index < room->timer.current * 2) {
                if (index >= room->parsed_track_count)
                    break;
                handle->value = MusicRegisterObject(room->animation_resource, index + 173);
                RecoveryMusicVm_00433ef0* object = MusicFind(handle->value);
                if (object == 0)
                    handle->value = 0;
                RecoveryTextVm_00447a50* text = reinterpret_cast<RecoveryTextVm_00447a50*>(object);
                if (recovery_music_player_0047783c[0x1D892 + index])
                    text->MarkText(g_sprt_ctrl, 0xFFFFFFu, static_cast<const char*>(comment));
                else
                    text->MarkText(g_sprt_ctrl, 0xFFFFFFu, recovery_music_locked_format_0046ecf4, index + 1);
                if (index < room->scroll_origin || index >= room->scroll_origin + 10)
                    object->flags &= ~2u;
                else
                    object->flags |= 2u;
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x - recovery_music_selected_offset_00470c98);
                object->InitializeTransition(&object->position, &position, 4, 0);
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x + recovery_music_selected_offset_00470c98);
                position.y += recovery_music_row_step_00470ca0;
                comment += 66;
                ++handle;
                object->stop_frame = static_cast<unsigned short>(2 + (index != room->cursor.selection));
                ++index;
            }
        }
        if (room->timer.current >= 10) {
            room->phase = 1;
            MusicResetTimer(&room->timer);
            return 0;
        }
        break;
    case 1:
        if (room->timer.current % 2 == 0 && room->preview_cursor < 8) {
            RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
                reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Validate(&room->preview_handles[room->preview_cursor]));
            RecoveryTextVm_00447a50* text = reinterpret_cast<RecoveryTextVm_00447a50*>(object);
            if (!recovery_music_player_0047783c[0x1D892 + room->displayed_track] && room->preview_armed)
                text->MarkText(g_sprt_ctrl, 0x8080FFu, recovery_music_preview_table_00476fd8[room->preview_cursor]);
            else
                text->MarkText(g_sprt_ctrl, 0xFFFFFFu, static_cast<const char*>(room->preview_lines[room->displayed_track][room->preview_cursor]));
            object->stop_frame = 2;
            ++room->preview_cursor;
        }
        if (room->timer.current > 4) {
            room->SetTimerTarget(2);
            return 0;
        }
        break;
    case 2:
        if (room->timer.current % 2 == 0 && room->preview_cursor < 8) {
            RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
                reinterpret_cast<RecoveryLookup_0040bd80*>(g_sprt_ctrl)->Validate(&room->preview_handles[room->preview_cursor]));
            RecoveryTextVm_00447a50* text = reinterpret_cast<RecoveryTextVm_00447a50*>(object);
            if (!recovery_music_player_0047783c[0x1D892 + room->displayed_track] && room->preview_armed)
                text->MarkText(g_sprt_ctrl, 0x8080FFu, recovery_music_preview_table_00476fd8[room->preview_cursor]);
            else
                text->MarkText(g_sprt_ctrl, 0xFFFFFFu, static_cast<const char*>(room->preview_lines[room->displayed_track][room->preview_cursor]));
            object->stop_frame = 2;
            ++room->preview_cursor;
        }
        room->cursor.previous_selection = room->cursor.selection;
        if ((data_00474e36 & 0x10u) || (recovery_music_repeat_00474e34 & 0x10u))
            room->cursor.Advance(-1);
        if ((data_00474e36 & 0x20u) || (recovery_music_repeat_00474e34 & 0x20u))
            room->cursor.Advance(1);
        if (room->cursor.previous_selection != room->cursor.selection) {
            data_00492590.Queue(12, 0);
            if (room->cursor.selection < room->scroll_origin)
                room->scroll_origin = room->cursor.selection;
            else if (room->cursor.selection >= room->scroll_origin + 10)
                room->scroll_origin = room->cursor.selection - 9;
            RecoveryMusicVector_00433ef0 position;
            position.x = 64.0f;
            position.y = recovery_music_row_y_00470c80 - static_cast<float>(room->scroll_origin) * recovery_music_row_step_00470ca0;
            position.z = 0;
            for (int index = 0; index < room->parsed_track_count; ++index) {
                RecoveryMusicVm_00433ef0* object = MusicFind(room->row_handles[index].value);
                if (object == 0)
                    room->row_handles[index].value = 0;
                if (index < room->scroll_origin || index >= room->scroll_origin + 10)
                    object->flags &= ~2u;
                else
                    object->flags |= 2u;
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x - recovery_music_selected_offset_00470c98);
                float difference = object->position.y - position.y;
                if (difference < 0)
                    difference = -difference;
                if (difference < recovery_music_jump_threshold_00470c64)
                    object->InitializeTransition(&object->position, &position, 4, 0);
                else
                    object->position = position;
                if (index == room->cursor.selection)
                    position.x = static_cast<float>(position.x + recovery_music_selected_offset_00470c98);
                position.y += recovery_music_row_step_00470ca0;
                object->stop_frame = static_cast<unsigned short>(2 + (index != room->cursor.selection));
            }
            room->preview_armed = 0;
        }
        if (data_00474e36 & 0x1001u) {
            for (int row = 0; row < 8; ++row)
                MusicSetTreeFrame(MusicFind(room->preview_handles[row].value), 3);
            room->displayed_track = room->cursor.selection;
            room->preview_cursor = 0;
            MusicResetTimer(&room->timer);
            RecoveryMusicResourceQueue_0043e460* queue = reinterpret_cast<RecoveryMusicResourceQueue_0043e460*>(&data_00492590);
            if (!recovery_music_player_0047783c[0x1D892 + room->displayed_track] && !room->preview_armed) {
                queue->RegisterResource(recovery_music_dummy_0046df98, (recovery_music_mode_00491d78 & 0x10u) ? 4 : 3, 0);
                room->preview_armed = 1;
                return 0;
            }
            recovery_replace_extension_00420a90(0, room->titles[room->cursor.selection]);
            if (recovery_music_mode_00491d78 & 0x10u)
                queue->RegisterResource(recovery_music_dummy_0046df98, 4, 0);
            queue->RegisterResource(recovery_music_dummy_0046df98, 2, 0);
            recovery_music_player_0047783c[0x1D892] = 1;
            room->preview_armed = 0;
            return 0;
        }
        if (data_00474e36 & 0xAu)
            goto leave_room;
        break;
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

leave_room:
    if (room->file_buffer != 0) {
        entry_free_00452422(room->file_buffer);
        room->file_buffer = 0;
    }
    room->file_buffer = 0;
    room->cursor.PopSelection();
    for (int row = 0; row < room->parsed_track_count; ++row)
        RecoveryMusicStopHandle_00409e50(&room->row_handles[row]);
    // Retail inlines the two-list lookup for this eight-handle cleanup.
    RecoveryLookupContext_0040bd80* context = reinterpret_cast<RecoveryLookupContext_0040bd80*>(g_sprt_ctrl);
    for (int row = 0; row < 8; ++row) {
        const unsigned int handle = room->preview_handles[row].value;
        RecoveryMusicVm_00433ef0* object = 0;
        if (handle != 0) {
            RecoveryLookupNode_0040bd80* node;
            for (node = context->primary; node != 0; node = node->next) {
                RecoveryMusicVm_00433ef0* candidate = reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object);
                if (candidate->id == handle) {
                    object = candidate;
                    break;
                }
            }
            if (node == 0) {
                for (node = context->secondary; node != 0; node = node->next) {
                    RecoveryMusicVm_00433ef0* candidate = reinterpret_cast<RecoveryMusicVm_00433ef0*>(node->object);
                    if (candidate->id == handle) {
                        object = candidate;
                        break;
                    }
                }
            }
        }
        MusicSetTreeFrame(object, 1);
    }
    data_00492590.Queue(11, 0);
    room->phase = 3;
    MusicResetTimer(&room->timer);
    return 0;
}
#pragma code_seg()
