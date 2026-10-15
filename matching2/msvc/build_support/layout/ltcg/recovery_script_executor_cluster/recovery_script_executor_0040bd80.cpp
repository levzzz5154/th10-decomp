#include <string.h>
#include "th10/game/recovery_script_executor_cluster/recovery_script_executor_0040bd80.hpp"
// Every mutable game global below is re-read from memory at each use in the
// retail image: the manager, owner and game-thread pointers are reassigned by
// init/teardown paths, the key-state masks by the window procedure and the
// input recorder. Volatile-qualified lvalue reads keep the plain externs' ODR
// intact while matching the retail reloads.
extern "C" void* g_sprt_ctrl;
#define MANAGER_00491c10 (*(void* const volatile*)&g_sprt_ctrl)
extern "C" RecoveryScriptOwner_0040bd80* g_ending;
#define OWNER_00477700 (*(RecoveryScriptOwner_0040bd80* const volatile*)&g_ending)
extern "C" GameThread_0040c540* g_ascii_manager;


// The key-state mask is written asynchronously by the window procedure and by
// the input recorder between this function's calls, so every read is volatile
// in the retail image; the plain-qualified extern keeps the ODR intact.
extern "C" unsigned int g_input_keys_raw;
#define INPUT_MASK_00474e30 (*(const volatile unsigned int*)&g_input_keys_raw)
extern "C" unsigned int g_input_keys_held;
#define SOUND_FLAGS_00474e36 (*(const volatile unsigned int*)&g_input_keys_held)

extern "C" int g_globals_difficulty;
#define GAME_MODE_00474c74 (*(const volatile int*)&g_globals_difficulty)

extern "C" unsigned int g_screen_effects_frozen;
#define RING_FLAG_004918a4 (*(volatile unsigned int*)&g_screen_effects_frozen)

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
// The three game-mode animation cases are one operation at three mode
// constants. Retail stores each expansion's animation-object output record in
// its own consecutive frame slot (three adjacent dwords) and reuses the
// incoming state-pointer argument home for the opcode-eight record.
static __forceinline void CreateModeSlotAnimation(
    RecoveryScriptState_0040bd80* state, void** output_record) {
    reinterpret_cast<RecoveryHandle_0040bd80*>(&state->animation_handles[state->command->arguments[0]])->MarkForRemoval();
    state->animation_handles[state->command->arguments[0]] =
        reinterpret_cast<unsigned int>(*AnimationManager_CreatePrimaryBack_00448d00(
            state->resources[state->command->arguments[1]], output_record,
            state->command->arguments[2], 15));
}

extern "C" __declspec(noinline) int __stdcall RecoveryScript_Execute_0040bd80(RecoveryScriptState_0040bd80* state) {
    void* output_records[3];
    const unsigned int flags = state->flags;
    if (flags & 4u)
        return 0;
    if (!(OWNER_00477700->flags_020 & 1u) && !(flags & 2u) &&
        (INPUT_MASK_00474e30 & 0x100u) && (flags & 1u))
        state->command_timer.Set(state->command->frame);

    while (state->command_timer.current >= static_cast<int>(state->command->frame)) {
        RecoveryCommand_0040bd80* command = state->command;
        switch (command->opcode) {
        case 0:
            return -1;
        case 3:
            if (state->text_ring_position == 0) {
                int remaining = 5;
                RecoveryHandle_0040bd80* handle = state->text_handles;
                for (; remaining != 0; --remaining, ++handle) {
                    RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(MANAGER_00491c10);
                    RecoveryScriptId id = { static_cast<int>(handle->value) };
                    RecoveryTextVm* object = static_cast<RecoveryTextVm*>(manager->Find(reinterpret_cast<RecoveryLookupContext*>(manager), id));
                    if (object == 0)
                        handle->value = 0;
                    object->MarkText(reinterpret_cast<void*>(manager), 0xFFFFFFu, recovery_script_empty_text_0046cfd4);
                    handle->StopAtFrame3();
                }
                RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(MANAGER_00491c10);
                RecoveryScriptId id = { static_cast<int>(state->text_handles[0].value) };
                RecoveryTextVm* object = static_cast<RecoveryTextVm*>(manager->Find(reinterpret_cast<RecoveryLookupContext*>(manager), id));
                if (object == 0)
                    state->text_handles[0].value = 0;
                const char* text = RecoveryDecodePath_00417010(reinterpret_cast<const unsigned char*>(state->command) + 4);
                object->MarkText(MANAGER_00491c10, state->color, text);
                state->text_handles[0].StopAtFrame2();
                ++state->text_ring_position;
            } else {
                const char* text = RecoveryDecodePath_00417010(reinterpret_cast<const unsigned char*>(command) + 4);
                RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(MANAGER_00491c10);
                RecoveryTextVm* object = static_cast<RecoveryTextVm*>(manager->Validate(&state->text_handles[state->text_ring_position]));
                object->MarkText(MANAGER_00491c10, state->color, text);
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
            if (!(SOUND_FLAGS_00474e36 & 0x1001u) && state->wait_timer.current > 0) {
                if (OWNER_00477700->flags_020 & 1u)
                    return 0;
                if (!(INPUT_MASK_00474e30 & 0x100u))
                    return 0;
                if (state->wait_timer.current % 6 != 0)
                    return 0;
                state->wait_timer.Set(0);
            } else {
                g_sound_manager.Queue(0, 0);
                state->wait_timer.Set(0);
            }
            break;
        case 6:
            if (state->wait_timer.current <= 0)
                state->wait_timer.Set(command->arguments[0]);
            state->wait_timer.Advance(-1.0f);
            if (!(SOUND_FLAGS_00474e36 & 0x1001u) && state->wait_timer.current > 0) {
                if (OWNER_00477700->flags_020 & 1u)
                    return 0;
                if (!(INPUT_MASK_00474e30 & 0x100u))
                    return 0;
                if (state->wait_timer.current % 6 != 0)
                    return 0;
            } else {
                g_sound_manager.Queue(0, 0);
            }
            state->wait_timer.Set(0);
            state->text_ring_position = 0;
            RING_FLAG_004918a4 = 0;
            break;
        case 7:
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
            reinterpret_cast<AnimationManager_004477d0*>(MANAGER_00491c10)->ClearResourceSlot(state->command->arguments[0] + 29);
            state->background_data = reinterpret_cast<const unsigned char*>(state->command) + 8;
            state->flags |= 4u;
            state->worker.Start(state, recovery_background_thread_0040c3a0);
            state->command = NextRecoveryCommand(state->command);
            return 0;
        case 8: {
            const int slot = command->arguments[0];
            RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(MANAGER_00491c10);
            manager->SetFlag(reinterpret_cast<RecoveryLookupContext*>(manager), static_cast<int>(state->animation_handles[slot]));
            state->animation_handles[slot] = 0;
            state->animation_handles[state->command->arguments[0]] =
                reinterpret_cast<unsigned int>(*AnimationManager_CreatePrimaryBack_00448d00(
                    state->resources[state->command->arguments[1]], &output_records[0],
                    state->command->arguments[2], 15));
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
            RecoveryLookup_0040bd80* manager = reinterpret_cast<RecoveryLookup_0040bd80*>(MANAGER_00491c10);
            RecoveryHandle_0040bd80* handle = state->text_handles;
            for (int remaining = 5; remaining != 0; --remaining, ++handle) {
                manager->SetFlag(reinterpret_cast<RecoveryLookupContext*>(manager), static_cast<int>(handle->value));
                handle->value = 0;
            }
            char* loaded = LoadAsset(reinterpret_cast<const char*>(state->command) + 4, reinterpret_cast<AssetBuffer*>(OWNER_00477700));
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
            if (GAME_MODE_00474c74 == 1)
                CreateModeSlotAnimation(state, &output_records[0]);
            break;
        case 16:
            if (GAME_MODE_00474c74 == 2)
                CreateModeSlotAnimation(state, &output_records[1]);
            break;
        case 17:
            if (GAME_MODE_00474c74 == 3)
                CreateModeSlotAnimation(state, &output_records[2]);
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
