#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

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
extern "C" DispatcherMusicRecord* data_00477848;
static DispatcherMusicRecord* MusicRecord() { return data_00477848; }

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
    animation->MarkText(context, state->text_parameters[state->text_side], text);
}
static __forceinline void BlankText(ResultDispatcherState* state, DispatcherHandle* handle) {
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
    DispatcherObject* animation = DispatcherFindAnimation(context, handle->id);
    if (!animation)
        handle->id.value = 0;
    animation->MarkText(context, state->text_parameters[state->text_side], " ");
}

#pragma code_seg(".text$00415e90_fn")
extern "C" __declspec(noinline) int __stdcall
ResultDispatcher_00415e90(ResultDispatcherState* state) {
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
    if (state->command->frame <= state->timer.current) {
        do {
            switch (state->command->opcode) {
            case 0:
                if (data_00474c84)
                    data_00474c8c = 0;
                data_00474c84 = 0;
                return -1;
            case 1:
                if (g_globals_character == 0 || g_globals_character == 1)
                    state->left_portrait.id.value =
                        DispatcherCreateAnimation(static_cast<AnimationResource_00449870*>(g_player->animation_file), 0x1D, 15).value;
                break;
            case 2:
                if (g_globals_character == 0 || g_globals_character == 1) {
                    if (g_globals_stage == 6)
                        state->right_portrait.id.value =
                            DispatcherCreateAnimation(g_enemy_ctrl->resource, 0x20, 15).value;
                    else if (g_globals_stage == 7 && state->variant < 1)
                        state->right_portrait.id.value =
                            DispatcherCreateAnimation(g_enemy_ctrl->resource, 0x25, 15).value;
                    else
                        state->right_portrait.id.value =
                            DispatcherCreateAnimation(static_cast<AnimationResource_00449870*>(g_player->animation_file), 0x1E, 15).value;
                }
                break;
            case 3:
                state->background.id.value =
                    DispatcherCreateAnimation(StageState()->resource, 0x5A, 15).value;
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
                DispatcherSetPosition(&state->text_positions[0], context, state->first_text.id);
                DispatcherSetPosition(&state->text_positions[state->text_side], context,
                    state->second_text.id);
                state->alternate_text = 0;
                break;
            }
            case 8: {
                state->left_portrait.StopAtFrame3();
                state->right_portrait.StopAtFrame2();
                AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl);
                state->text_side = 1;
                DispatcherSetPosition(&state->text_positions[1], context, state->first_text.id);
                DispatcherSetPosition(&state->text_positions[state->text_side], context,
                    state->second_text.id);
                state->alternate_text = 0;
                break;
            }
            case 9:
                state->flags ^= (static_cast<unsigned char>(state->command->first_operand) ^
                    state->flags) & 1;
                break;
            case 10:
                if (state->wait.current < 1)
                    state->wait.SetSchedulerValue(state->command->first_operand);
                reinterpret_cast<FrameTimer*>(&state->wait)->Advance(-1.0f);
                if (!(data_00474e62 & 0x1001) && state->wait.current > 0) {
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
            case 12:
                if (g_globals_character == 0) {
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x34);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x3C);
                } else if (g_globals_character == 1) {
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x2D);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x35);
                }
                break;
            case 13: {
                int first_index, second_index;
                int first_child = 0x18, second_child = 0x1B;
                switch (g_globals_stage) {
                case 1: first_index = 0x0F; second_index = 0x17; break;
                case 2: first_index = 0x15; second_index = 0x1E; break;
                case 3: first_index = 0x22; second_index = 0x2B; break;
                case 4: first_index = 0x25; second_index = 0x2E; break;
                case 5: first_index = 0x16; second_index = 0x1F; break;
                case 6:
                    first_index = 0x30; second_index = 0x39;
                    first_child = 0x1C; second_child = 0x1F;
                    break;
                case 7:
                    if (state->variant < 1) {
                        first_index = 0x44; second_index = 0x4D;
                        first_child = 0x21; second_child = 0x24;
                    } else {
                        first_index = 0x2E; second_index = 0x37;
                    }
                    break;
                default:
                    goto next_command;
                }
                if (g_globals_character == 0 || g_globals_character == 1) {
                    // Fetch these genuine operands before FindChildRef, as
                    // retail does; fetch the second pair after the first call.
                    int index = state->command->first_operand + first_index;
                    AnimationResource_00449870* resource = g_enemy_ctrl->resource;
                    state->right_portrait.FindChildRef(first_child).SelectResourceSprite(
                        resource, index);
                    index = state->command->first_operand + second_index;
                    resource = g_enemy_ctrl->resource;
                    state->right_portrait.FindChildRef(second_child).SelectResourceSprite(
                        resource, index);
                }
                break;
            }
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
            case 18:
                asm_Sound_PlayDummyRetail_00420b10(1, MusicRecord()->music_slot);
                DispatcherCreateAnimation(StageState()->effect_resource, 2, 15);
                break;
            case 19: {
                int script;
                switch (g_globals_stage) {
                case 1: script = 0x0D; break;
                case 2: script = 0x10; break;
                case 3: script = 0x14; break;
                case 4: script = 0x15; break;
                case 5: script = 0x0E; break;
                case 6: script = 0x23; break;
                case 7: script = 0x1D; break;
                default: goto next_command;
                }
                state->stage_title.id.value =
                    DispatcherCreateAnimation(g_enemy_ctrl->resource, script, 15).value;
                break;
            }
            case 20: {
                if (g_globals_difficulty != 4) {
                    unsigned char* progress = ProgressBytes();
                    int route = (g_globals_shot_type + g_globals_character * 3) * 0x437C;
                    progress[route + 0x4E1 + (g_globals_stage + g_globals_difficulty * 6) * 8] = 1;
                    route = (g_globals_shot_type + g_globals_character * 3) * 0x437C;
                    progress[route + (g_globals_stage + (g_globals_difficulty * 3 + 0x4E) * 2) * 8] = 1;
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
                    if (g_replay->replay_mode == 1) {
                        SetInputMode(&g_application, 4);
                        break;
                    }
                    Screen_Create(0x31, 5, 0x78, 0, 0, 0);
                    DispatcherStageState* stage = StageState();
                    stage->result_phase = 0;
                    stage->flags |= 0x10;
                    int* count = ClearCount();
                    if (*count < 99999)
                        ++*count;
                } else if (g_globals_stage == 7) {
                    StageState()->flags |= 0x20;
                    g_globals.AddScore(g_globals_gauge * 1000);
                    g_globals.AddScore(g_globals_lives * 40000000);
                    g_globals.AddScore(g_globals_power * 400000);
                    if (g_replay->replay_mode == 1) {
                        SetInputMode(&g_application, 4);
                        break;
                    }
                    g_pause->OpenResult();
                    int* count = ClearCount();
                    if (*count < 99999)
                        ++*count;
                } else {
                    DispatcherStageState* stage = StageState();
                    DispatcherRemoveAnimation(reinterpret_cast<AnimationLookupContext*>(g_sprt_ctrl),
                        stage->transition_animation);
                    stage->transition_animation.value = 0;
                    stage->transition_animation.value =
                        DispatcherCreateAnimation(stage->resource, 0x4C, 15).value;
                    SetInputMode(&g_application, 11);
                    reinterpret_cast<DispatcherRankState*>(&g_globals)->AdvanceLevel();
                }
                break;
            }
            case 21:
                asm_Sound_PlayRandomVoiceRetail_00420c30(g_globals_stage == 6 ? 8.0f : 2.0f);
                break;
            case 22:
                state->left_portrait.SetStopFrame(7);
                break;
            case 23:
                state->right_portrait.SetStopFrame(7);
                break;
            }
        next_command:
            state->command = reinterpret_cast<DispatcherCommand*>(
                reinterpret_cast<unsigned char*>(state->command) +
                4 + state->command->operand_size);
        } while (state->command->frame <= state->timer.current);
    }
    state->timer.Tick();
    return 0;
}
#pragma code_seg()

