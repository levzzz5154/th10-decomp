#include "th10/game/pause_result_open/dispatcher_contract.hpp"

// 0x00415E90: packed stage-dialogue and stage-clear command dispatcher (byte-exact
// through build_support/layout/ltcg/front_script_tick_00415e90.json).
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

enum FrontMsgOpcode {
    MSG_END = 0,
    MSG_CREATE_LEFT_PORTRAIT = 1,
    MSG_CREATE_RIGHT_PORTRAIT = 2,
    MSG_CREATE_TEXTBOX = 3,
    MSG_HIDE_LEFT_PORTRAIT = 4,
    MSG_HIDE_RIGHT_PORTRAIT = 5,
    MSG_HIDE_TEXTBOX = 6,
    MSG_FOCUS_LEFT = 7,
    MSG_FOCUS_RIGHT = 8,
    MSG_SET_SKIPPABLE = 9,
    MSG_WAIT_INPUT = 10,
    MSG_START_COUNTDOWN = 11,
    MSG_SET_LEFT_EXPRESSION = 12,
    MSG_SET_RIGHT_EXPRESSION = 13,
    MSG_SET_LINE_1 = 14,
    MSG_SET_LINE_2 = 15,
    MSG_ADD_TEXT_LINE = 16,
    MSG_CLEAR_TEXT = 17,
    MSG_PLAY_BOSS_BGM = 18,
    MSG_SHOW_STAGE_TITLE = 19,
    MSG_STAGE_CLEAR = 20,
    MSG_PLAY_RANDOM_VOICE = 21,
    MSG_DIM_LEFT_PORTRAIT = 22,
    MSG_DIM_RIGHT_PORTRAIT = 23
};

enum FrontMsgKeyMask {
    MSG_KEY_SKIP = 0x0100,
    MSG_KEY_ADVANCE = 0x1001
};

enum FrontMsgDomainIds {
    MSG_CHAR_REIMU = 0,
    MSG_CHAR_MARISA = 1,
    MSG_DIFF_EASY = 0,
    MSG_DIFF_NORMAL = 1,
    MSG_DIFF_HARD = 2,
    MSG_DIFF_LUNATIC = 3,
    MSG_DIFF_EXTRA = 4,
    MSG_STAGE_1 = 1,
    MSG_STAGE_2 = 2,
    MSG_STAGE_3 = 3,
    MSG_STAGE_4 = 4,
    MSG_STAGE_5 = 5,
    MSG_STAGE_6 = 6,
    MSG_STAGE_EXTRA = 7,
    MSG_GLOBAL_FLAG_PRACTICE = 0x10
};

#pragma code_seg(".text$00415e90_fn")
extern "C" __declspec(noinline) int __stdcall
ResultDispatcher2(ResultDispatcherState* state) {
    if (state->countdown > 0)
        --state->countdown;
    if ((state->flags & 1) && (g_input & MSG_KEY_SKIP)) {
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
            case MSG_SET_LINE_1:
                DecodeAndSetText(state, &state->first_text);
                state->first_text.StopAtFrame2();
                break;
            case MSG_SET_LINE_2:
                DecodeAndSetText(state, &state->second_text);
                state->second_text.StopAtFrame2();
                break;
            case MSG_ADD_TEXT_LINE:
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
            case MSG_CLEAR_TEXT:
                state->first_text.StopAtFrame3();
                state->second_text.StopAtFrame3();
                break;
            case MSG_CREATE_TEXTBOX:
                CREATE_INTO(state->background.id.value, StageState()->resource, 0x5A)
                break;
            case MSG_CREATE_LEFT_PORTRAIT:
                switch (g_globals_character) {
                case MSG_CHAR_REIMU: CREATE_INTO(state->left_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1D) break;
                case MSG_CHAR_MARISA: CREATE_INTO(state->left_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1D) break;
                }
                break;
            case MSG_CREATE_RIGHT_PORTRAIT:
                if (g_globals_stage == MSG_STAGE_6) {
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x20) break;
                    case MSG_CHAR_MARISA: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x20) break;
                    }
                } else if (g_globals_stage == MSG_STAGE_EXTRA && state->variant < 1) {
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x25) break;
                    case MSG_CHAR_MARISA: CREATE_INTO(state->right_portrait.id.value, g_enemy_ctrl->resource, 0x25) break;
                    }
                } else {
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU: CREATE_INTO(state->right_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1E) break;
                    case MSG_CHAR_MARISA: CREATE_INTO(state->right_portrait.id.value, static_cast<AnimationBank*>(g_player->animation_file), 0x1E) break;
                    }
                }
                break;
            case MSG_DIM_LEFT_PORTRAIT:
                state->left_portrait.SetStopFrame(7);
                break;
            case MSG_DIM_RIGHT_PORTRAIT:
                state->right_portrait.SetStopFrame(7);
                break;
            case MSG_HIDE_LEFT_PORTRAIT:
                state->left_portrait.StopAtFrame1();
                state->left_portrait.id.value = 0;
                break;
            case MSG_HIDE_RIGHT_PORTRAIT:
                state->right_portrait.StopAtFrame1();
                state->right_portrait.id.value = 0;
                state->stage_title.StopAtFrame1();
                break;
            case MSG_HIDE_TEXTBOX:
                state->background.StopAtFrame1();
                state->first_text.StopAtFrame1();
                state->second_text.StopAtFrame1();
                break;
            case MSG_FOCUS_LEFT: {
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
            case MSG_FOCUS_RIGHT: {
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
            case MSG_SET_SKIPPABLE:
                reinterpret_cast<DispatcherFlagBits*>(&state->flags)->skippable =
                    static_cast<unsigned char>(state->command->first_operand);
                break;
            case MSG_SET_LEFT_EXPRESSION:
                switch (g_globals_character) {
                case MSG_CHAR_REIMU:
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x34);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x3C);
                    break;
                case MSG_CHAR_MARISA:
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x2D);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x35);
                    break;
                }
                break;
            case MSG_SET_RIGHT_EXPRESSION:
                switch (g_globals_stage) {
                case MSG_STAGE_1:
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU:
                        SELECT_PAIR(24, 0xf, 27, 0x17)
                        break;
                    case MSG_CHAR_MARISA:
                        SELECT_PAIR(24, 0xf, 27, 0x17)
                        break;
                    }
                    break;
                case MSG_STAGE_2:
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU:
                        SELECT_PAIR(24, 0x15, 27, 0x1e)
                        break;
                    case MSG_CHAR_MARISA:
                        SELECT_PAIR(24, 0x15, 27, 0x1e)
                        break;
                    }
                    break;
                case MSG_STAGE_3:
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU:
                        SELECT_PAIR(24, 0x22, 27, 0x2b)
                        break;
                    case MSG_CHAR_MARISA:
                        SELECT_PAIR(24, 0x22, 27, 0x2b)
                        break;
                    }
                    break;
                case MSG_STAGE_4:
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU:
                        SELECT_PAIR(24, 0x25, 27, 0x2e)
                        break;
                    case MSG_CHAR_MARISA:
                        SELECT_PAIR(24, 0x25, 27, 0x2e)
                        break;
                    }
                    break;
                case MSG_STAGE_5:
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU:
                        SELECT_PAIR(24, 0x16, 27, 0x1f)
                        break;
                    case MSG_CHAR_MARISA:
                        SELECT_PAIR(24, 0x16, 27, 0x1f)
                        break;
                    }
                    break;
                case MSG_STAGE_6:
                    switch (g_globals_character) {
                    case MSG_CHAR_REIMU:
                        SELECT_PAIR(28, 0x30, 31, 0x39)
                        break;
                    case MSG_CHAR_MARISA:
                        SELECT_PAIR(28, 0x30, 31, 0x39)
                        break;
                    }
                    break;
                case MSG_STAGE_EXTRA:
                    if (state->variant < 1) {
                        switch (g_globals_character) {
                        case MSG_CHAR_REIMU:
                            SELECT_PAIR(33, 0x44, 36, 0x4d)
                            break;
                        case MSG_CHAR_MARISA:
                            SELECT_PAIR(33, 0x44, 36, 0x4d)
                            break;
                        }
                    } else {
                        switch (g_globals_character) {
                        case MSG_CHAR_REIMU:
                            SELECT_PAIR(24, 0x2e, 27, 0x37)
                            break;
                        case MSG_CHAR_MARISA:
                            SELECT_PAIR(24, 0x2e, 27, 0x37)
                            break;
                        }
                    }
                    break;
                }
                break;
            case MSG_WAIT_INPUT:
                if (state->wait.current <= 0)
                    state->wait.SetSchedulerValue(state->command->first_operand);
                reinterpret_cast<FrameTimer*>(&state->wait)->Advance(-1.0f);
                if (!(g_input_keys_secondary & MSG_KEY_ADVANCE) && state->wait.current > 0) {
                    if (!(state->flags & 1) || !(g_input & MSG_KEY_SKIP))
                        return 0;
                    state->wait.SetSchedulerValue(0);
                    state->alternate_text = 0;
                } else {
                    g_sound_manager.Queue(0, 0);
                    state->wait.SetSchedulerValue(0);
                    state->alternate_text = 0;
                }
                break;
            case MSG_START_COUNTDOWN:
                state->countdown = 1;
                break;
            case MSG_PLAY_BOSS_BGM:
                asm_Sound_PlayDummyRetail_00420b10(1, g_stage_route_current->music_tracks[1]);
                { int created; DispatcherCreateAt(StageState()->effect_resource, &created, 2, 15); }
                break;
            case MSG_SHOW_STAGE_TITLE:
                switch (g_globals_stage) {
                case MSG_STAGE_1: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x0D)
                    break;
                }
                case MSG_STAGE_2: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x10)
                    break;
                }
                case MSG_STAGE_3: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x14)
                    break;
                }
                case MSG_STAGE_4: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x15)
                    break;
                }
                case MSG_STAGE_5: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x0E)
                    break;
                }
                case MSG_STAGE_6: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x23)
                    break;
                }
                case MSG_STAGE_EXTRA: {
                    CREATE_INTO(state->stage_title.id.value, g_enemy_ctrl->resource, 0x1D)
                    break;
                }
                default: goto next_command;
                }
                break;
            case MSG_STAGE_CLEAR: {
                if (g_globals_difficulty != MSG_DIFF_EXTRA) {
                    ProgressBytes()[(g_globals_shot_type + g_globals_character * 3) * 0x437C + 0x4E1 +
                        (g_globals_stage + g_globals_difficulty * 3 * 2) * 8] = 1;
                    ProgressBytes()[(g_globals_shot_type + g_globals_character * 3) * 0x437C +
                        (g_globals_stage + (g_globals_difficulty * 3 + 0x4E) * 2) * 8] = 1;
                }
                if (g_globals_flags & MSG_GLOBAL_FLAG_PRACTICE) {
                    g_pause->OpenResult();
                    break;
                }
                if (g_globals_stage == MSG_STAGE_6) {
                    StageState()->flags |= 0x20;
                    g_globals.AddScore(g_globals_gauge * 1000);
                    switch (g_globals_difficulty) {
                    case MSG_DIFF_EASY:
                        g_globals.AddScore(g_globals_lives * 20000000);
                        g_globals.AddScore(g_globals_power * 100000);
                        break;
                    case MSG_DIFF_NORMAL:
                        g_globals.AddScore(g_globals_lives * 25000000);
                        g_globals.AddScore(g_globals_power * 100000);
                        break;
                    case MSG_DIFF_HARD:
                        g_globals.AddScore(g_globals_lives * 35000000);
                        g_globals.AddScore(g_globals_power * 200000);
                        break;
                    case MSG_DIFF_LUNATIC:
                        g_globals.AddScore(g_globals_lives * 40000000);
                        g_globals.AddScore(g_globals_power * 300000);
                        break;
                    case MSG_DIFF_EXTRA:
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
                        // MATCH: writing the count expression twice keeps the
                        // difficulty load in the temporaries' rotation at both copies.
                        if (*ClearCount() < 99999)
                            ++*ClearCount();
                    } else {
                        SetInputMode(&g_application, 4);
                    }
                } else if (g_globals_stage == MSG_STAGE_EXTRA) {
                    StageState()->flags |= 0x20;
                    g_globals.AddScore(g_globals_gauge * 1000);
                    g_globals.AddScore(g_globals_lives * 40000000);
                    g_globals.AddScore(g_globals_power * 400000);
                    if (g_replay->replay_mode != 1) {
                        g_pause->OpenResult();
                        // MATCH: writing the count expression twice keeps the
                        // difficulty load in the temporaries' rotation at both copies.
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
            case MSG_PLAY_RANDOM_VOICE:
                if (g_globals_stage != 6)
                    asm_Sound_PlayRandomVoiceRetail_00420c30(2.0f);
                else
                    asm_Sound_PlayRandomVoiceRetail_00420c30(8.0f);
                break;
            case MSG_END:
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
