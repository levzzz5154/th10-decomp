#include <string.h>
#include "th10/game/marktext_dispatcher_context/recovery_script_executor_0040bd80.hpp"
extern "C" void* data_00491c10;
extern "C" RecoveryScriptOwner_0040bd80* data_00477700;
extern "C" GameThread_0040c540* g_ascii_manager;
extern "C" unsigned int data_00474e30;
extern "C" unsigned int data_00474e36;
extern "C" int data_00474c74;
extern "C" unsigned int data_004918a4;
extern "C" const char recovery_script_empty_text_0046cfd4[];
extern "C" const char recovery_script_special_music_0046cfc4[];
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
extern "C" int __stdcall recovery_replace_extension_00420a90(int selector, const char* path);
extern "C" int __stdcall recovery_play_dummy_00420b10(int selector, int slot);
extern "C" int __stdcall recovery_play_random_voice_00420c30(float fade);
extern "C" unsigned int __stdcall recovery_background_thread_0040c3a0(void* state);

static __forceinline RecoveryCommand_0040bd80* NextRecoveryCommand(RecoveryCommand_0040bd80* command) {
    return reinterpret_cast<RecoveryCommand_0040bd80*>(reinterpret_cast<unsigned char*>(command) + command->argument_bytes + 4);
}
#pragma code_seg(".text$0040bd80_fn")
extern "C" __declspec(noinline) int __stdcall RecoveryScript_Execute_0040bd80(RecoveryScriptState_0040bd80* state) {
    const unsigned int flags = state->flags;
    if (flags & 4u)
        return 0;
    if (!(data_00477700->flags_020 & 1u) && !(flags & 2u) &&
        (data_00474e30 & 0x100u) && (flags & 1u))
        state->command_timer.Set(state->command->frame);

    while (state->command->frame <= state->command_timer.current) {
        RecoveryCommand_0040bd80* command = state->command;
        switch (command->opcode) {
        case 0:
            return -1;
        case 3:
            if (state->text_ring_position == 0) {
                RecoveryHandle_0040bd80* handle = state->text_handles;
                for (int remaining = 5; remaining != 0; --remaining, ++handle) {
                    RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10);
                    RecoveryScriptId_0040bd80 id = { static_cast<int>(handle->value) };
                    RecoveryTextVm_00447a50* object = static_cast<RecoveryTextVm_00447a50*>(manager->Find(reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id));
                    if (object == 0)
                        handle->value = 0;
                    object->MarkText(data_00491c10, 0xFFFFFFu, recovery_script_empty_text_0046cfd4);
                    handle->StopAtFrame3();
                }
                RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10);
                RecoveryScriptId_0040bd80 id = { static_cast<int>(state->text_handles[0].value) };
                RecoveryTextVm_00447a50* object = static_cast<RecoveryTextVm_00447a50*>(manager->Find(reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), id));
                if (object == 0)
                    state->text_handles[0].value = 0;
                const char* text = RecoveryDecodePath_00417010(reinterpret_cast<const unsigned char*>(state->command) + 4);
                object->MarkText(data_00491c10, state->color, text);
                state->text_handles[0].StopAtFrame2();
                ++state->text_ring_position;
            } else {
                const char* text = RecoveryDecodePath_00417010(reinterpret_cast<const unsigned char*>(command) + 4);
                RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10);
                RecoveryTextVm_00447a50* object = static_cast<RecoveryTextVm_00447a50*>(manager->Validate(&state->text_handles[state->text_ring_position]));
                object->MarkText(data_00491c10, state->color, text);
                state->text_handles[state->text_ring_position].StopAtFrame2();
                ++state->text_ring_position;
                if (state->text_ring_position >= 5)
                    state->text_ring_position = 0;
            }
            break;
        case 4: {
            RecoveryHandle_0040bd80* handle = state->text_handles;
            for (int remaining = 5; remaining != 0; --remaining, ++handle)
                handle->StopAtFrame3();
            break;
        }
        case 5:
            if (state->wait_timer.current <= 0)
                state->wait_timer.Set(command->arguments[0]);
            state->wait_timer.Advance(-1.0f);
            if (state->command->arguments[0] < 0)
                state->wait_timer.Set(999);
            if (!(data_00474e36 & 0x1001u) && state->wait_timer.current > 0) {
                if (data_00477700->flags_020 & 1u)
                    return 0;
                if (!(data_00474e30 & 0x100u))
                    return 0;
                if (state->wait_timer.current % 6 != 0)
                    return 0;
                state->wait_timer.Set(0);
            } else {
                data_00492590.Queue(0, 0);
                state->wait_timer.Set(0);
            }
            break;
        case 6:
            if (state->wait_timer.current <= 0)
                state->wait_timer.Set(command->arguments[0]);
            state->wait_timer.Advance(-1.0f);
            if (!(data_00474e36 & 0x1001u) && state->wait_timer.current > 0) {
                if (data_00477700->flags_020 & 1u)
                    return 0;
                if (!(data_00474e30 & 0x100u))
                    return 0;
                if (state->wait_timer.current % 6 != 0)
                    return 0;
            } else {
                data_00492590.Queue(0, 0);
            }
            state->wait_timer.Set(0);
            state->text_ring_position = 0;
            data_004918a4 = 0;
            break;
        case 7:
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
            reinterpret_cast<AnimationManager_004477d0*>(data_00491c10)->ClearResourceSlot(state->command->arguments[0] + 29);
            state->background_data = reinterpret_cast<const unsigned char*>(state->command) + 8;
            state->flags |= 4u;
            state->worker.Start(state, recovery_background_thread_0040c3a0);
            state->command = NextRecoveryCommand(state->command);
            return 0;
        case 8: {
            const int slot = command->arguments[0];
            RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10);
            manager->SetFlag(reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), static_cast<int>(state->animation_handles[slot]));
            state->animation_handles[slot] = 0;
            void* created;
            void** result = AnimationManager_CreatePrimaryBack_00448d00(state->resources[state->command->arguments[1]], &created, state->command->arguments[2], 15);
            state->animation_handles[state->command->arguments[0]] = reinterpret_cast<unsigned int>(*result);
            break;
        }
        case 9:
            state->color = static_cast<unsigned int>(command->arguments[0]);
            break;
        case 10: {
            recovery_replace_extension_00420a90(0, reinterpret_cast<const char*>(command) + 4);
            const char* name = reinterpret_cast<const char*>(state->command) + 4;
            if (memcmp(name, recovery_script_special_music_0046cfc4, 16) == 0)
                recovery_play_dummy_00420b10(0, 15);
            else
                recovery_play_dummy_00420b10(0, 16);
            break;
        }
        case 11:
            recovery_play_random_voice_00420c30(3.0f);
            state->flags &= ~1u;
            break;
        case 12: {
            RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(data_00491c10);
            RecoveryHandle_0040bd80* handle = state->text_handles;
            for (int remaining = 5; remaining != 0; --remaining, ++handle) {
                manager->SetFlag(reinterpret_cast<RecoveryLookupContext_0040bd80*>(data_00491c10), static_cast<int>(handle->value));
                handle->value = 0;
            }
            char* loaded = LoadAsset(reinterpret_cast<const char*>(state->command) + 4, reinterpret_cast<AssetBuffer*>(data_00477700));
            if (loaded == 0)
                return -1;
            memset(state, 0, sizeof(*state));
            state->command = reinterpret_cast<RecoveryCommand_0040bd80*>(loaded + *reinterpret_cast<int*>(loaded + 4));
            state->outer_timer.Set(0);
            state->command_timer.Set(0);
            state->wait_timer.Set(0);
            state->color = 0xFFFFFFu;
            state->flags |= 2u;
            continue;
        }
        case 13:
            RecoveryAscii_Create_0043c8b0(0x31, 0, static_cast<unsigned int>(command->arguments[0]), 0, 0, 0);
            break;
        case 14:
            RecoveryAscii_Create_0043c8b0(0x31, 5, static_cast<unsigned int>(command->arguments[0]), 0, 0, 0);
            break;
        case 15:
            if (data_00474c74 == 1) {
                reinterpret_cast<RecoveryHandle_0040bd80*>(&state->animation_handles[command->arguments[0]])->MarkForRemoval();
                void* created;
                void** result = AnimationManager_CreatePrimaryBack_00448d00(state->resources[state->command->arguments[1]], &created, state->command->arguments[2], 15);
                state->animation_handles[state->command->arguments[0]] = reinterpret_cast<unsigned int>(*result);
            }
            break;
        case 16:
            if (data_00474c74 == 2) {
                reinterpret_cast<RecoveryHandle_0040bd80*>(&state->animation_handles[command->arguments[0]])->MarkForRemoval();
                void* created;
                void** result = AnimationManager_CreatePrimaryBack_00448d00(state->resources[state->command->arguments[1]], &created, state->command->arguments[2], 15);
                state->animation_handles[state->command->arguments[0]] = reinterpret_cast<unsigned int>(*result);
            }
            break;
        case 17:
            if (data_00474c74 == 3) {
                reinterpret_cast<RecoveryHandle_0040bd80*>(&state->animation_handles[command->arguments[0]])->MarkForRemoval();
                void* created;
                void** result = AnimationManager_CreatePrimaryBack_00448d00(state->resources[state->command->arguments[1]], &created, state->command->arguments[2], 15);
                state->animation_handles[state->command->arguments[0]] = reinterpret_cast<unsigned int>(*result);
            }
            break;
        }
        state->command = NextRecoveryCommand(state->command);
    }
    state->command_timer.previous = state->command_timer.current;
    if (*state->command_timer.speed > g_frame_timer_normal_lower &&
        *state->command_timer.speed < g_frame_timer_normal_upper) {
        state->command_timer.elapsed += 1.0f;
        ++state->command_timer.current;
    } else {
        state->command_timer.current = int(state->command_timer.elapsed += *state->command_timer.speed);
    }
    return 0;
}
#pragma code_seg()
