// 0x0040BD80: EndingScript_Execute
#include <string.h>
#include "th10/game/ending_script/script_executor.hpp"
// The animation manager is read as a plain global: its address is never
// taken, so the whole-program optimizer keeps one load across callees that
// cannot write it (Find, the path decoder) and reloads it after the text
// writer, as retail does. Taking its address anywhere in the link (a volatile
// read) disables that and changes the register assignment of case 3.
extern "C" void* g_sprt_ctrl;
// The callees as the executor calls them: handle validation 0x00449450 with
// the handle in ESI and no receiver; the text writer 0x00447A50 with the text
// object as an explicit second argument; the flag setter 0x004492A0 with only
// the id pushed; the script loader 0x0040B480 with the buffer first.
__declspec(noinline) AnmTextVm* __cdecl AnmHandle_Validate(AnmScriptHandle* handle);
__declspec(noinline) void __cdecl EndingScript_MarkText(void* manager, AnmTextVm* vm, ...);
__declspec(noinline) void* __fastcall AnmHandle_SetFlag(AnmLookupContext* context, int id);
__declspec(noinline) char* __stdcall LoadAsset(AssetBuffer* buffer, const char* name);
// The owner pointer is reassigned by init/teardown paths and the key-state
// masks by the window procedure and the input recorder; retail re-reads them
// at each use. Volatile-qualified lvalue reads keep the plain externs' ODR
// intact while matching the retail reloads.
extern "C" EndingOwner* g_ending;
#define OWNER (*(EndingOwner* const volatile*)&g_ending)
extern "C" GameThreadResourceView* g_ascii_manager;


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

static __forceinline EndingScriptCommand* NextRecoveryCommand(EndingScriptCommand* command) {
    return reinterpret_cast<EndingScriptCommand*>(reinterpret_cast<unsigned char*>(command) + command->argument_bytes + 4);
}

// The body of 0x00449450 (look up a handle's object, clear a stale handle),
// which the whole-program link expanded in place in the ring-reset path and
// called out of line in the else branch. The id is passed as an expression:
// a named id local becomes a register candidate instead of an expression
// temporary and shifts the EAX/ECX/EDX temporary rotation of case 3.
static __forceinline AnmTextVm* ValidateInPlace(AnmScriptHandle* handle) {
    AnmTextVm* object = static_cast<AnmTextVm*>(
        reinterpret_cast<AnmLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl),
            *reinterpret_cast<const AnimationScriptId*>(&handle->value)));
    if (object == 0)
        handle->value = 0;
    return object;
}
#pragma code_seg(".text$0040bd80_fn")
// The three game-mode animation cases are one operation at three mode
// constants. Retail stores each expansion's animation-object output record in
// its own consecutive frame slot (three adjacent dwords) and reuses the
// incoming state-pointer argument home for the opcode-eight record.
static __forceinline void CreateModeSlotAnimation(
    EndingScriptState* state, void** output_record) {
    reinterpret_cast<AnmScriptHandle*>(&state->animation_handles[state->command->arguments[0]])->MarkForRemoval();
    state->animation_handles[state->command->arguments[0]] =
        reinterpret_cast<unsigned int>(*AnimationManager_CreatePrimaryBack(
            state->resources[state->command->arguments[1]], output_record,
            state->command->arguments[2], 15));
}

enum EndingScriptOpcode {
    END_OP_STOP = 0,
    END_OP_PRINT_TEXT = 3,
    END_OP_CLEAR_TEXT = 4,
    END_OP_WAIT = 5,
    END_OP_WAIT_AND_RESET = 6,
    END_OP_LOAD_RESOURCE_ASYNC = 7,
    END_OP_CREATE_SPRITE = 8,
    END_OP_SET_TEXT_COLOR = 9,
    END_OP_PLAY_BGM = 10,
    END_OP_FADE_OUT_BGM = 11,
    END_OP_LOAD_NEXT_SCRIPT = 12,
    END_OP_FADE_IN = 13,
    END_OP_FADE_OUT = 14,
    END_OP_CREATE_SPRITE_NORMAL = 15,
    END_OP_CREATE_SPRITE_HARD = 16,
    END_OP_CREATE_SPRITE_LUNATIC = 17
};

enum EndingScriptFlags {
    END_FLAG_SKIP_ALLOWED = 1u,
    END_FLAG_SKIP_LOCKED = 2u,
    END_FLAG_ASYNC_BUSY = 4u
};

enum EndingInputMask {
    END_KEY_FAST_FORWARD = 0x100u,
    END_KEY_CONFIRM = 0x1001u
};

extern "C" __declspec(noinline) int __stdcall EndingScript_Execute(EndingScriptState* state) {
    void* output_records[3];
    const unsigned int flags = state->flags;
    if (flags & END_FLAG_ASYNC_BUSY)
        return 0;
    if (!(OWNER->flags_020 & 1u) && !(flags & END_FLAG_SKIP_LOCKED) &&
        (INPUT_MASK & END_KEY_FAST_FORWARD) && (flags & END_FLAG_SKIP_ALLOWED))
        state->command_timer.Set(state->command->frame);

    while (state->command_timer.current >= static_cast<int>(state->command->frame)) {
        EndingScriptCommand* command = state->command;
        switch (command->opcode) {
        case END_OP_STOP:
            return -1;
        case END_OP_PRINT_TEXT:
            if (state->text_ring_position == 0) {
                for (int i = 0; i < 5; ++i) {
                    AnmTextVm* object = ValidateInPlace(&state->text_handles[i]);
                    EndingScript_MarkText(g_sprt_ctrl, object, 0xFFFFFFu, recovery_script_empty_text);
                    state->text_handles[i].StopAtFrame3();
                }
                AnmTextVm* object = ValidateInPlace(&state->text_handles[0]);
                const char* text = EndingScript_DecodePath(reinterpret_cast<const unsigned char*>(state->command) + 4);
                EndingScript_MarkText(g_sprt_ctrl, object, state->color, text);
                state->text_handles[0].StopAtFrame2();
                ++state->text_ring_position;
            } else {
                // One expression: retail validates the handle between the color
                // push and the manager load.
                EndingScript_MarkText(g_sprt_ctrl,
                    AnmHandle_Validate(&state->text_handles[state->text_ring_position]),
                    state->color, EndingScript_DecodePath(reinterpret_cast<const unsigned char*>(command) + 4));
                state->text_handles[state->text_ring_position].StopAtFrame2();
                ++state->text_ring_position;
                if (state->text_ring_position >= 5)
                    state->text_ring_position = 0;
            }
            break;
        case END_OP_CLEAR_TEXT: {
            AnmScriptHandle* handle = state->text_handles;
            for (int remaining = 5; remaining != 0; --remaining, ++handle)
                handle->StopAtFrame3();
            break;
        }
        case END_OP_WAIT:
            if (state->wait_timer.current <= 0)
                state->wait_timer.Set(command->arguments[0]);
            state->wait_timer.Advance(-1.0f);
            if (state->command->arguments[0] < 0)
                state->wait_timer.Set(999);
            if (!(SOUND_FLAGS & END_KEY_CONFIRM) && state->wait_timer.current > 0) {
                if (OWNER->flags_020 & 1u)
                    return 0;
                if (!(INPUT_MASK & END_KEY_FAST_FORWARD))
                    return 0;
                if (state->wait_timer.current % 6 != 0)
                    return 0;
                state->wait_timer.Set(0);
            } else {
                g_sound_manager.Queue(0, 0);
                state->wait_timer.Set(0);
            }
            break;
        case END_OP_WAIT_AND_RESET:
            if (state->wait_timer.current <= 0)
                state->wait_timer.Set(command->arguments[0]);
            state->wait_timer.Advance(-1.0f);
            if (!(SOUND_FLAGS & END_KEY_CONFIRM) && state->wait_timer.current > 0) {
                if (OWNER->flags_020 & 1u)
                    return 0;
                if (!(INPUT_MASK & END_KEY_FAST_FORWARD))
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
        case END_OP_LOAD_RESOURCE_ASYNC:
            g_ascii_manager->EnsureAnimationResource(480.0f, 392.0f);
            reinterpret_cast<AnmSlotManager*>(g_sprt_ctrl)->ClearResourceSlot(state->command->arguments[0] + 29);
            state->flags |= END_FLAG_ASYNC_BUSY;
            state->background_data = reinterpret_cast<const unsigned char*>(state->command) + 8;
            state->worker.Start(state, recovery_background_thread);
            state->command = NextRecoveryCommand(state->command);
            return 0;
        case END_OP_CREATE_SPRITE: {
            void* record;
            unsigned int* handle = &state->animation_handles[command->arguments[0]];
            AnmHandle_SetFlag(reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), static_cast<int>(*handle));
            *handle = 0;
            state->animation_handles[state->command->arguments[0]] =
                reinterpret_cast<unsigned int>(*AnimationManager_CreatePrimaryBack(
                    state->resources[state->command->arguments[1]], &record,
                    state->command->arguments[2], 15));
            break;
        }
        case END_OP_CREATE_SPRITE_NORMAL:
            if (GAME_MODE == 1)
                CreateModeSlotAnimation(state, &output_records[0]);
            break;
        case END_OP_CREATE_SPRITE_HARD:
            if (GAME_MODE == 2)
                CreateModeSlotAnimation(state, &output_records[1]);
            break;
        case END_OP_CREATE_SPRITE_LUNATIC:
            if (GAME_MODE == 3)
                CreateModeSlotAnimation(state, &output_records[2]);
            break;
        case END_OP_SET_TEXT_COLOR:
            state->color = static_cast<unsigned int>(command->arguments[0]);
            break;
        case END_OP_PLAY_BGM: {
            recovery_replace_extension(0, reinterpret_cast<const char*>(command) + 4);
            const char* name = reinterpret_cast<const char*>(state->command) + 4;
            if (strcmp(name, "bgm/th10_13.wav") == 0)
                recovery_play_dummy(0, 15);
            else
                recovery_play_dummy(0, 16);
            break;
        }
        case END_OP_FADE_OUT_BGM:
            recovery_play_random_voice(3.0f);
            state->flags &= ~END_FLAG_SKIP_ALLOWED;
            break;
        case END_OP_LOAD_NEXT_SCRIPT: {
            for (int i = 0; i < 5; ++i) {
                AnmHandle_SetFlag(reinterpret_cast<AnmLookupContext*>(g_sprt_ctrl), static_cast<int>(state->text_handles[i].value));
                state->text_handles[i].value = 0;
            }
            char* loaded = LoadAsset(reinterpret_cast<AssetBuffer*>(OWNER), reinterpret_cast<const char*>(state->command) + 4);
            if (loaded == 0)
                return -1;
            memset(state, 0, sizeof(*state));
            state->command = reinterpret_cast<EndingScriptCommand*>(loaded + *reinterpret_cast<int*>(loaded + 4));
            state->outer_timer.Set(0);
            state->command_timer.Set(0);
            state->wait_timer.Set(0);
            state->color = 0xFFFFFFu;
            state->flags |= END_FLAG_SKIP_LOCKED;
            continue;
        }
        case END_OP_FADE_IN:
            AsciiText_Create(0x31, 0, static_cast<unsigned int>(command->arguments[0]), 0, 0, 0);
            break;
        case END_OP_FADE_OUT:
            AsciiText_Create(0x31, 5, static_cast<unsigned int>(command->arguments[0]), 0, 0, 0);
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
