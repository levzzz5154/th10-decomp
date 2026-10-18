#include <string.h>
#include "../../../build_support/include/contexts/game/marktext_dispatcher_context/recovery_script_executor.hpp"
// Every mutable game global below is re-read from memory at each use in the
// retail image: the manager, owner and game-thread pointers are reassigned by
// init/teardown paths, the key-state masks by the window procedure and the
// input recorder. Volatile-qualified lvalue reads keep the plain externs' ODR
// intact while matching the retail reloads.
extern "C" void* g_sprt_ctrl;
__declspec(noinline) RecoveryTextVm* __cdecl RecoveryValidateHandle(RecoveryHandle* handle);
__declspec(noinline) void* __fastcall RecoverySetFlag(RecoveryLookupContext* context, int id);
__declspec(noinline) char* __stdcall LoadAsset(AssetBuffer* buffer, const char* name);
#define MANAGER (*(void* const volatile*)&g_sprt_ctrl)
extern "C" RecoveryScriptOwner* g_ending;
#define OWNER (*(RecoveryScriptOwner* const volatile*)&g_ending)
extern "C" GameThread6* g_ascii_manager;


// The key-state mask is written asynchronously by the window procedure and by
// the input recorder between this function's calls, so every read is volatile
// in the retail image; the plain-qualified extern keeps the ODR intact.
extern "C" unsigned int g_input_keys_raw;
#define INPUT_MASK (*(const volatile unsigned int*)&g_input_keys_raw)
extern "C" unsigned int g_input_keys_held;
#define SOUND_FLAGS (*(const volatile unsigned int*)&g_input_keys_held)

extern "C" int g_globals_difficulty;
#define GAME_MODE (*(const volatile int*)&g_globals_difficulty)

extern "C" unsigned int g_screen_effects_frozen;
#define RING_FLAG (*(volatile unsigned int*)&g_screen_effects_frozen)

extern "C" const char recovery_script_empty_text[];
extern "C" const char recovery_script_special_music[];
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
extern "C" int __stdcall recovery_replace_extension(int selector, const char* path);
extern "C" int __stdcall recovery_play_dummy(int selector, int slot);
extern "C" int __stdcall recovery_play_random_voice(float fade);
extern "C" unsigned int __stdcall recovery_background_thread(void* state);

static __forceinline RecoveryCommand* NextRecoveryCommand(RecoveryCommand* command) {
    return reinterpret_cast<RecoveryCommand*>(reinterpret_cast<unsigned char*>(command) + command->argument_bytes + 4);
}
#pragma code_seg(".text$0040bd80_fn")
// The three game-mode animation cases are one operation at three mode
// constants. Retail stores each expansion's animation-object output record in
// its own consecutive frame slot (three adjacent dwords) and reuses the
// incoming state-pointer argument home for the opcode-eight record.
static __forceinline void CreateModeSlotAnimation(
    RecoveryScriptState* state, void** output_record) {
    reinterpret_cast<RecoveryHandle*>(&state->animation_handles[state->command->arguments[0]])->MarkForRemoval();
    state->animation_handles[state->command->arguments[0]] =
        reinterpret_cast<unsigned int>(*AnimationManager_CreatePrimaryBack(
            state->resources[state->command->arguments[1]], output_record,
            state->command->arguments[2], 15));
}

extern "C" __declspec(noinline) int __stdcall RecoveryScript_Execute2(RecoveryScriptState* state) {
    void* output_records[3];
    const unsigned int flags = state->flags;
    if (flags & 4u)
        return 0;
    if (!(OWNER->flags_020 & 1u) && !(flags & 2u) &&
        (INPUT_MASK & 0x100u) && (flags & 1u))
        state->command_timer.Set(state->command->frame);

    while (state->command_timer.current >= static_cast<int>(state->command->frame)) {
        RecoveryCommand* command = state->command;
        switch (command->opcode) {
        case 0:
            return -1;
        case 3:
            if (state->text_ring_position == 0) {
                int remaining = 5;
                RecoveryHandle* handle = state->text_handles;
                for (; remaining != 0; --remaining, ++handle) {
                    RecoveryLookup* manager = reinterpret_cast<RecoveryLookup*>(MANAGER);
                    RecoveryScriptId id = { static_cast<int>(handle->value) };
                    RecoveryTextVm* object = static_cast<RecoveryTextVm*>(manager->Find(reinterpret_cast<RecoveryLookupContext*>(manager), id));
                    if (object == 0)
                        handle->value = 0;
                    object->MarkText(reinterpret_cast<void*>(manager), 0xFFFFFFu, recovery_script_empty_text);
                    handle->StopAtFrame3();
                }
                RecoveryLookup* manager = reinterpret_cast<RecoveryLookup*>(MANAGER);
                RecoveryScriptId id = { static_cast<int>(state->text_handles[0].value) };
                RecoveryTextVm* object = static_cast<RecoveryTextVm*>(manager->Find(reinterpret_cast<RecoveryLookupContext*>(manager), id));
                if (object == 0)
                    state->text_handles[0].value = 0;
                const char* text = RecoveryDecodePath(reinterpret_cast<const unsigned char*>(state->command) + 4);
                object->MarkText(reinterpret_cast<void*>(manager), state->color, text);
                state->text_handles[0].StopAtFrame2();
                ++state->text_ring_position;
            } else {
                const char* else_text = RecoveryDecodePath(reinterpret_cast<const unsigned char*>(command) + 4);
                RecoveryHandle* else_handle = &state->text_handles[state->text_ring_position];
                unsigned int else_color = state->color;
                RecoveryValidateHandle(else_handle)->MarkText(g_sprt_ctrl, else_color, else_text);
                state->text_handles[state->text_ring_position].StopAtFrame2();
                ++state->text_ring_position;
                if (state->text_ring_position >= 5)
                    state->text_ring_position = 0;
            }
            break;
        case 4: {
            RecoveryHandle* handle = state->text_handles;
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
            if (!(SOUND_FLAGS & 0x1001u) && state->wait_timer.current > 0) {
                if (OWNER->flags_020 & 1u)
                    return 0;
                if (!(INPUT_MASK & 0x100u))
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
            if (!(SOUND_FLAGS & 0x1001u) && state->wait_timer.current > 0) {
                if (OWNER->flags_020 & 1u)
                    return 0;
                if (!(INPUT_MASK & 0x100u))
                    return 0;
                if (state->wait_timer.current % 6 != 0)
                    return 0;
            } else {
                g_sound_manager.Queue(0, 0);
            }
            state->wait_timer.Set(0);
            state->text_ring_position = 0;
            RING_FLAG = 0;
            break;
        case 7:
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
            reinterpret_cast<AnimationManager13*>(MANAGER)->ClearResourceSlot(state->command->arguments[0] + 29);
            state->flags |= 4u;
            state->background_data = reinterpret_cast<const unsigned char*>(state->command) + 8;
            state->worker.Start(state, recovery_background_thread);
            state->command = NextRecoveryCommand(state->command);
            return 0;
        case 8: {
            void* record;
            unsigned int* handle = &state->animation_handles[command->arguments[0]];
            RecoveryLookup* manager = reinterpret_cast<RecoveryLookup*>(MANAGER);
            RecoverySetFlag(reinterpret_cast<RecoveryLookupContext*>(manager), static_cast<int>(*handle));
            *handle = 0;
            state->animation_handles[state->command->arguments[0]] =
                reinterpret_cast<unsigned int>(*AnimationManager_CreatePrimaryBack(
                    state->resources[state->command->arguments[1]], &record,
                    state->command->arguments[2], 15));
            break;
        }
        case 15:
            if (GAME_MODE == 1)
                CreateModeSlotAnimation(state, &output_records[0]);
            break;
        case 16:
            if (GAME_MODE == 2)
                CreateModeSlotAnimation(state, &output_records[1]);
            break;
        case 17:
            if (GAME_MODE == 3)
                CreateModeSlotAnimation(state, &output_records[2]);
            break;
        case 9:
            state->color = static_cast<unsigned int>(command->arguments[0]);
            break;
        case 10: {
            recovery_replace_extension(0, reinterpret_cast<const char*>(command) + 4);
            const char* name = reinterpret_cast<const char*>(state->command) + 4;
            if (strcmp(name, "bgm/th10_13.wav") == 0)
                recovery_play_dummy(0, 15);
            else
                recovery_play_dummy(0, 16);
            break;
        }
        case 11:
            recovery_play_random_voice(3.0f);
            state->flags &= ~1u;
            break;
        case 12: {
            RecoveryLookup* manager = reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl);
            for (int i = 0; i < 5; ++i) {
                RecoverySetFlag(reinterpret_cast<RecoveryLookupContext*>(manager), static_cast<int>(state->text_handles[i].value));
                state->text_handles[i].value = 0;
            }
            char* loaded = LoadAsset(reinterpret_cast<AssetBuffer*>(OWNER), reinterpret_cast<const char*>(state->command) + 4);
            if (loaded == 0)
                return -1;
            memset(state, 0, sizeof(*state));
            state->command = reinterpret_cast<RecoveryCommand*>(loaded + *reinterpret_cast<int*>(loaded + 4));
            state->outer_timer.Set(0);
            state->command_timer.Set(0);
            state->wait_timer.Set(0);
            state->color = 0xFFFFFFu;
            state->flags |= 2u;
            continue;
        }
        case 13:
            RecoveryAscii_Create(0x31, 0, static_cast<unsigned int>(command->arguments[0]), 0, 0, 0);
            break;
        case 14:
            RecoveryAscii_Create(0x31, 5, static_cast<unsigned int>(command->arguments[0]), 0, 0, 0);
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
