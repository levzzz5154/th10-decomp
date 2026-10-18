#include "th10/game/pause_result_open/dispatcher_contract.hpp"

// Complete packed-command dispatcher at 0x00415E90. This is unselected compiler
// context; the 4,480-byte retail owner is not claimed as a recovered region.
static DispatcherStageState* StageState() {
    return reinterpret_cast<DispatcherStageState*>(g_front);
}
static unsigned char* ProgressBytes() {
    return reinterpret_cast<unsigned char*>(g_score);
}
static __forceinline int* ClearCount() {
    return reinterpret_cast<int*>(ProgressBytes() + 0x4D0 +
        ((g_globals_shot_type + g_globals_character * 3) * 0x10DF + g_globals_difficulty) * 4);
}
static DispatcherMusicRecord* MusicRecord();
extern "C" DispatcherMusicRecord* g_stage_route_current;
static DispatcherMusicRecord* MusicRecord() { return g_stage_route_current; }


// The pool creation 0x00448D00 as this walker calls it: the reference comes
// back through the record the caller supplies (EDI), and the caller reads it
// through the returned pointer.
__declspec(noinline) int* __stdcall DispatcherCreateAt(
    AnimationBank* resource, int* out, int script_index, int render_bucket);
// The resource is a named local: retail allocates it apart from the
// rotating expression temporaries.
#define CREATE_INTO(target, resource, script) \
    { AnimationBank* bank = resource; int created; target = *DispatcherCreateAt(bank, &created, script, 15); }

// Preserve the manager and resolved animation across the decode call, as the
// actual caller does. A failed lookup clears the handle, but SetText is still
// invoked with its null result; the callee owns that behavior.
static __forceinline void DecodeAndSetText(ResultDispatcherState* state, DispatcherHandle* handle) {
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    DispatcherObject* animation = DispatcherFindAnimation(context, handle->id);
    if (!animation)
        handle->id.value = 0;
    char* text = Path_DecodeXor(reinterpret_cast<const char*>(
        &state->command->first_operand));
    AnimationLookupContext* manager =
        reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    animation->MarkText(manager, state->text_parameters[state->text_side], text);
}
static __forceinline void BlankText(ResultDispatcherState* state, DispatcherHandle* handle) {
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    DispatcherObject* animation = DispatcherFindAnimation(context, handle->id);
    if (!animation)
        handle->id.value = 0;
    AnimationLookupContext* manager =
        reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    animation->MarkText(manager, state->text_parameters[state->text_side], " ");
}

// Opcode 13 selects two child sprites from the boss resource. Retail reads the
// resource before the operand for each call, so it is assigned first.
#define SELECT_PAIR(c1, k1, c2, k2) { \
    AnimationBank* resource = g_enemy_ctrl->resource; \
    state->right_portrait.FindChildRef(c1).SelectResourceSprite(resource, state->command->first_operand + k1); \
    resource = g_enemy_ctrl->resource; \
    state->right_portrait.FindChildRef(c2).SelectResourceSprite(resource, state->command->first_operand + k2); }

// 0x004492F0 with its retail parameter order: the position is evaluated
// before the id is pushed.
__declspec(noinline) void __stdcall SetAnimationPosition(
    AnimationLookupContext* context, AnimationScriptId id, const DispatcherVec3* position);

// Bit 0 of the walker flags: the command stream may be skipped with the shot key.
struct DispatcherFlagBits {
    unsigned skippable : 1;
};

#pragma code_seg(".text$00415e90_fn")
extern "C" __declspec(noinline) int __stdcall
ResultDispatcher2(ResultDispatcherState* state) {
    if (state->countdown > 0)
        --state->countdown;
    if ((state->flags & 1) && (g_input & 0x100)) {
        int frame = state->command->frame;
        FrameTimer* timer = &state->timer;
        if (!(timer->flags & 1)) {
            timer->current = 0;
            timer->previous = -999999;
            timer->elapsed = 0.0f;
            timer->speed = &g_game_speed;
            timer->flags |= 1;
        }
        timer->current = frame;
        timer->previous = frame - 1;
        timer->elapsed = static_cast<float>(frame);
    }
    while (state->timer.current >= (int)state->command->frame) {
            switch (state->command->opcode) {
            case 14:
                DecodeAndSetText(state, &state->first_text);
                state->first_text.StopAtFrame2();
                break;
            case 15:
                DecodeAndSetText(state, &state->second_text);
                state->second_text.StopAtFrame2();
                break;
            case 16:
                if (!state->alternate_text) {
                    BlankText(state, &state->first_text);
                    BlankText(state, &state->second_text);
                    DecodeAndSetText(state, &state->first_text);
                    state->first_text.StopAtFrame2();
                    state->second_text.StopAtFrame3();
                    ++state->alternate_text;
                } else {
                    DecodeAndSetText(state, &state->second_text);
                    state->second_text.StopAtFrame2();
                    state->alternate_text = 0;
                }
                break;
            case 17:
                state->first_text.StopAtFrame3();
                state->second_text.StopAtFrame3();
                break;
            case 3:
                CREATE_INTO(state->background.id.value, StageState()->resource, 0x5A)
                break;
            case 1:
                switch (g_globals_character) {
                case 0: CREATE_INTO(state->left_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1D) break;
                case 1: CREATE_INTO(state->left_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1D) break;
                }
                break;
            case 2:
                if (g_globals_stage == 6) {
                    switch (g_globals_character) {
                    case 0: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x20) break;
                    case 1: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x20) break;
                    }
                } else if (g_globals_stage == 7 && state->variant < 1) {
                    switch (g_globals_character) {
                    case 0: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x25) break;
                    case 1: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x25) break;
                    }
                } else {
                    switch (g_globals_character) {
                    case 0: CREATE_INTO(state->right_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1E) break;
                    case 1: CREATE_INTO(state->right_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1E) break;
                    }
                }
                break;
            case 22:
                state->left_portrait.SetStopFrame(7);
                break;
            case 23:
                state->right_portrait.SetStopFrame(7);
                break;
            case 4:
                state->left_portrait.StopAtFrame1();
                state->left_portrait.id.value = 0;
                break;
            case 5:
                state->right_portrait.StopAtFrame1();
                state->right_portrait.id.value = 0;
                state->stage_title.StopAtFrame1();
                break;
            case 6:
                state->background.StopAtFrame1();
                state->first_text.StopAtFrame1();
                state->second_text.StopAtFrame1();
                break;
            case 7: {
                state->right_portrait.StopAtFrame3();
                state->left_portrait.StopAtFrame2();
                AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
                state->text_side = 0;
                SetAnimationPosition(context, state->first_text.id, &state->text_positions[0]);
                SetAnimationPosition(context, state->second_text.id,
                    &state->text_positions[state->text_side]);
                state->alternate_text = 0;
                break;
            }
            case 8: {
                state->left_portrait.StopAtFrame3();
                state->right_portrait.StopAtFrame2();
                AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
                state->text_side = 1;
                SetAnimationPosition(context, state->first_text.id, &state->text_positions[1]);
                SetAnimationPosition(context, state->second_text.id,
                    &state->text_positions[state->text_side]);
                state->alternate_text = 0;
                break;
            }
            case 9:
                reinterpret_cast<DispatcherFlagBits*>(&state->flags)->skippable =
                    static_cast<unsigned char>(state->command->first_operand);
                break;
            case 12:
                switch (g_globals_character) {
                case 0:
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x34);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x3C);
                    break;
                case 1:
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x2D);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x35);
                    break;
                }
                break;
            case 13:
                switch (g_globals_stage) {
                case 1:
                    switch (g_globals_character) {
                    case 0:
                        SELECT_PAIR(24, 0xf, 27, 0x17)
                        break;
                    case 1:
                        SELECT_PAIR(24, 0xf, 27, 0x17)
                        break;
                    }
                    break;
                case 2:
                    switch (g_globals_character) {
                    case 0:
                        SELECT_PAIR(24, 0x15, 27, 0x1e)
                        break;
                    case 1:
                        SELECT_PAIR(24, 0x15, 27, 0x1e)
                        break;
                    }
                    break;
                case 3:
                    switch (g_globals_character) {
                    case 0:
                        SELECT_PAIR(24, 0x22, 27, 0x2b)
                        break;
                    case 1:
                        SELECT_PAIR(24, 0x22, 27, 0x2b)
                        break;
                    }
                    break;
                case 4:
                    switch (g_globals_character) {
                    case 0:
                        SELECT_PAIR(24, 0x25, 27, 0x2e)
                        break;
                    case 1:
                        SELECT_PAIR(24, 0x25, 27, 0x2e)
                        break;
                    }
                    break;
                case 5:
                    switch (g_globals_character) {
                    case 0:
                        SELECT_PAIR(24, 0x16, 27, 0x1f)
                        break;
                    case 1:
                        SELECT_PAIR(24, 0x16, 27, 0x1f)
                        break;
                    }
                    break;
                case 6:
                    switch (g_globals_character) {
                    case 0:
                        SELECT_PAIR(28, 0x30, 31, 0x39)
                        break;
                    case 1:
                        SELECT_PAIR(28, 0x30, 31, 0x39)
                        break;
                    }
                    break;
                case 7:
                    if (state->variant < 1) {
                        switch (g_globals_character) {
                        case 0:
                            SELECT_PAIR(33, 0x44, 36, 0x4d)
                            break;
                        case 1:
                            SELECT_PAIR(33, 0x44, 36, 0x4d)
                            break;
                        }
                    } else {
                        switch (g_globals_character) {
                        case 0:
                            SELECT_PAIR(24, 0x2e, 27, 0x37)
                            break;
                        case 1:
                            SELECT_PAIR(24, 0x2e, 27, 0x37)
                            break;
                        }
                    }
                    break;
                }
                break;
            case 10:
                if (state->wait.current <= 0)
                    state->wait.SetSchedulerValue(state->command->first_operand);
                reinterpret_cast<FrameTimer*>(&state->wait)->Advance(-1.0f);
                if (!(g_input_keys_secondary & 0x1001) && state->wait.current > 0) {
                    if (!(state->flags & 1) || !(g_input & 0x100))
                        return 0;
                    state->wait.SetSchedulerValue(0);
                    state->alternate_text = 0;
                } else {
                    g_sound_manager.Queue(0, 0);
                    state->wait.SetSchedulerValue(0);
                    state->alternate_text = 0;
                }
                break;
            case 11:
                state->countdown = 1;
                break;
            case 18:
                asm_Sound_PlayDummyRetail_00420b10(1, MusicRecord()->music_slot);
                { int created; DispatcherCreateAt(StageState()->effect_resource, &created, 2, 15); }
                break;
            case 19:
                switch (g_globals_stage) {
                case 1: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x0D)
                    break;
                }
                case 2: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x10)
                    break;
                }
                case 3: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x14)
                    break;
                }
                case 4: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x15)
                    break;
                }
                case 5: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x0E)
                    break;
                }
                case 6: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x23)
                    break;
                }
                case 7: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x1D)
                    break;
                }
                default: goto next_command;
                }
                break;
            case 20: {
                if (g_globals_difficulty != 4) {
                    ProgressBytes()[(g_globals_shot_type + g_globals_character * 3) * 0x437C + 0x4E1 +
                        (g_globals_stage + g_globals_difficulty * 3 * 2) * 8] = 1;
                    ProgressBytes()[(g_globals_shot_type + g_globals_character * 3) * 0x437C +
                        (g_globals_stage + (g_globals_difficulty * 3 + 0x4E) * 2) * 8] = 1;
                }
                if (g_globals_flags & 0x10) {
                    g_pause->OpenResult();
                    break;
                }
                if (g_globals_stage == 6) {
                    StageState()->flags |= 0x20;
                    g_globals.AddScore(g_globals_gauge * 1000);
                    switch (g_globals_difficulty) {
                    case 0:
                        g_globals.AddScore(g_globals_lives * 20000000);
                        g_globals.AddScore(g_globals_power * 100000);
                        break;
                    case 1:
                        g_globals.AddScore(g_globals_lives * 25000000);
                        g_globals.AddScore(g_globals_power * 100000);
                        break;
                    case 2:
                        g_globals.AddScore(g_globals_lives * 35000000);
                        g_globals.AddScore(g_globals_power * 200000);
                        break;
                    case 3:
                        g_globals.AddScore(g_globals_lives * 40000000);
                        g_globals.AddScore(g_globals_power * 300000);
                        break;
                    case 4:
                        g_globals.AddScore(g_globals_lives * 40000000);
                        g_globals.AddScore(g_globals_power * 400000);
                        break;
                    }
                    // The replay branch is the else arm so both copies sit
                    // out of line and merge, as in retail.
                    if (g_replay->replay_mode != 1) {
                        Screen_Create(0x31, 5, 0x78, 0, 0, 0);
                        DispatcherStageState* stage = StageState();
                        stage->result_phase = 0;
                        stage->flags |= 0x10;
                        // The count expression is written out twice: the
                        // second write-out is what keeps the difficulty load
                        // in the temporaries' rotation at both copies, as in
                        // retail.
                        if (*ClearCount() < 99999)
                            ++*ClearCount();
                    } else {
                        SetInputMode(&g_application, 4);
                    }
                } else if (g_globals_stage == 7) {
                    StageState()->flags |= 0x20;
                    g_globals.AddScore(g_globals_gauge * 1000);
                    g_globals.AddScore(g_globals_lives * 40000000);
                    g_globals.AddScore(g_globals_power * 400000);
                    if (g_replay->replay_mode != 1) {
                        g_pause->OpenResult();
                        // The count expression is written out twice: the
                        // second write-out is what keeps the difficulty load
                        // in the temporaries' rotation at both copies, as in
                        // retail.
                        if (*ClearCount() < 99999)
                            ++*ClearCount();
                    } else {
                        SetInputMode(&g_application, 4);
                    }
                } else {
                    DispatcherStageState* stage = StageState();
                    int* transition = &stage->transition_animation.value;
                    DispatcherRemoveAnimation(reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl),
                        stage->transition_animation);
                    *transition = 0;
                    { int created; *transition = *DispatcherCreateAt(stage->resource, &created, 0x4C, 15); }
                    SetInputMode(&g_application, 11);
                    reinterpret_cast<DispatcherRankState*>(&g_globals)->AdvanceLevel();
                }
                break;
            }
            case 21:
                if (g_globals_stage != 6)
                    asm_Sound_PlayRandomVoiceRetail_00420c30(2.0f);
                else
                    asm_Sound_PlayRandomVoiceRetail_00420c30(8.0f);
                break;
            case 0:
                if (g_stage_progress)
                    g_stage_progress_echo = 0;
                g_stage_progress = 0;
                return -1;
}
        next_command:
            state->command = reinterpret_cast<DispatcherCommand*>(
                reinterpret_cast<unsigned char*>(state->command) +
                4 + state->command->operand_size);
    }
    state->timer.Tick();
    return 0;
}
#pragma code_seg()

