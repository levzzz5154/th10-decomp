#include "th10/game/pause_result_open_004231d0/dispatcher_contract.hpp"

// Complete packed-command dispatcher at 0x00415E90. This is unselected compiler
// context; the 4,480-byte retail owner is not claimed as a recovered region.
static DispatcherStageState* StageState() {
    return reinterpret_cast<DispatcherStageState*>(data_0047770c);
}
static unsigned char* ProgressBytes() {
    return reinterpret_cast<unsigned char*>(data_0047783c);
}
static __forceinline int* ClearCount() {
    return reinterpret_cast<int*>(ProgressBytes() + 0x4D0 +
        ((data_00474c6c + data_00474c68 * 3) * 0x10DF + data_00474c74) * 4);
}
static DispatcherMusicRecord* MusicRecord();
extern "C" DispatcherMusicRecord* data_00477848;
static DispatcherMusicRecord* MusicRecord() { return data_00477848; }

// Preserve the manager and resolved animation across the decode call, as the
// actual caller does. A failed lookup clears the handle, but SetText is still
// invoked with its null result; the callee owns that behavior.
static __forceinline void DecodeAndSetText(ResultDispatcherState* state, DispatcherHandle* handle) {
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    DispatcherObject* animation = DispatcherFindAnimation(context, handle->id);
    if (!animation)
        handle->id.value = 0;
    char* text = Path_DecodeXor(reinterpret_cast<const char*>(
        &state->command->first_operand));
    AnimationLookupContext* manager =
        reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    animation->MarkText(manager, state->text_parameters[state->text_side], text);
}
static __forceinline void BlankText(ResultDispatcherState* state, DispatcherHandle* handle) {
    AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    DispatcherObject* animation = DispatcherFindAnimation(context, handle->id);
    if (!animation)
        handle->id.value = 0;
    AnimationLookupContext* manager =
        reinterpret_cast<AnimationLookupContext*>(data_00491c10);
    animation->MarkText(manager, state->text_parameters[state->text_side], " ");
}

#pragma code_seg(".text$00415e90_fn")
extern "C" __declspec(noinline) int __stdcall
ResultDispatcher_00415e90(ResultDispatcherState* state) {
    if (state->countdown > 0)
        --state->countdown;
    if ((state->flags & 1) && (data_00474e5c & 0x100)) {
        int frame = state->command->frame;
        FrameTimer* timer = &state->timer;
        if (!(timer->flags & 1)) {
            timer->current = 0;
            timer->previous = -999999;
            timer->elapsed = 0.0f;
            timer->speed = &data_00476f78;
            timer->flags |= 1;
        }
        timer->current = frame;
        timer->previous = frame - 1;
        timer->elapsed = static_cast<float>(frame);
    }
    if (state->timer.current >= (int)state->command->frame) {
        do {
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
                { DispatcherRef created = DispatcherCreateAnimation(StageState()->resource, 0x5A, 15); state->background.id.value = created.value; }
                break;
            case 1:
                if (data_00474c68 == 1)
                    { DispatcherRef created = DispatcherCreateAnimation(data_00477834->resource, 0x1D, 15); state->left_portrait.id.value = created.value; }
                else if (data_00474c68 == 0)
                    { DispatcherRef created = DispatcherCreateAnimation(data_00477834->resource, 0x1D, 15); state->left_portrait.id.value = created.value; }
                break;
            case 2:
                if (data_00474c7c == 6) {
                    if (data_00474c68 == 1)
                        { DispatcherRef created = DispatcherCreateAnimation(data_00477704->resource, 0x20, 15); state->right_portrait.id.value = created.value; }
                    else if (data_00474c68 == 1)
                        { DispatcherRef created2 = DispatcherCreateAnimation(data_00477704->resource, 0x20, 15); state->right_portrait.id.value = created2.value; }
                } else if (data_00474c7c == 7 && state->variant < 1) {
                    if (data_00474c68 == 0)
                        { DispatcherRef created = DispatcherCreateAnimation(data_00477704->resource, 0x25, 15); state->right_portrait.id.value = created.value; }
                    else if (data_00474c68 == 1)
                        { DispatcherRef created = DispatcherCreateAnimation(data_00477704->resource, 0x25, 15); state->right_portrait.id.value = created.value; }
                } else {
                    if (data_00474c68 == 0)
                        { DispatcherRef created = DispatcherCreateAnimation(data_00477834->resource, 0x1E, 15); state->right_portrait.id.value = created.value; }
                    else if (data_00474c68 == 1)
                        { DispatcherRef created = DispatcherCreateAnimation(data_00477834->resource, 0x1E, 15); state->right_portrait.id.value = created.value; }
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
                AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
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
                AnimationLookupContext* context = reinterpret_cast<AnimationLookupContext*>(data_00491c10);
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
                if (data_00474c68 == 0) {
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x34);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x3C);
                } else if (data_00474c68 == 1) {
                    state->left_portrait.FindChildRef(0x17).SelectCurrentSprite(
                        state->command->first_operand + 0x2D);
                    state->left_portrait.FindChildRef(0x1A).SelectCurrentSprite(
                        state->command->first_operand + 0x35);
                }
                break;
            case 13: {
                unsigned int mode = data_00474c68;
                volatile int* mode_addr = &data_00474c68;
                switch (data_00474c7c) {
                case 1:
                    if (mode == 1) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0xf);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x17);
                    }
                    if (*mode_addr == 1) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0xf);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x17);
                    }
                    break;
                case 2:
                    if (mode == 0) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x15);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x1e);
                    }
                    if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x15);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x1e);
                    }
                    break;
                case 3:
                    if (mode == 1) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x22);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x2b);
                    }
                    if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x22);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x2b);
                    }
                    break;
                case 4:
                    if (mode == 1) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x25);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x2e);
                    }
                    if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x25);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x2e);
                    }
                    break;
                case 5:
                    if (mode == 1) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x16);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x1f);
                    }
                    if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x16);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x1f);
                    }
                    break;
                case 6:
                    if (mode == 1) {
                        state->right_portrait.FindChildRef(28).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x30);
                        state->right_portrait.FindChildRef(31).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x39);
                    }
                    if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(28).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x30);
                        state->right_portrait.FindChildRef(31).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x39);
                    }
                    break;
                case 7:
                    if (state->variant < 1) {
                        if (mode == 1) {
                        state->right_portrait.FindChildRef(33).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x44);
                        state->right_portrait.FindChildRef(36).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x4d);
                        }
                        if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(33).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x44);
                        state->right_portrait.FindChildRef(36).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x4d);
                        }
                    } else {
                        if (mode == 1) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x2e);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x37);
                        }
                        if (*mode_addr == 0) {
                        state->right_portrait.FindChildRef(24).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x2e);
                        state->right_portrait.FindChildRef(27).SelectResourceSprite(data_00477704->resource, state->command->first_operand + 0x37);
                        }
                    }
                    break;
                }
                break;
            }
            case 11:
                if (state->wait.current < 1)
                    state->wait.SetSchedulerValue(state->command->first_operand);
                reinterpret_cast<FrameTimer*>(&state->wait)->Advance(-1.0f);
                if (!(data_00474e62 & 0x1001) && state->wait.current > 0) {
                    if (!(state->flags & 1) || !(data_00474e5c & 0x100))
                        return 0;
                    state->wait.SetSchedulerValue(0);
                    state->alternate_text = 0;
                } else {
                    data_00492590.Queue(0, 0);
                    state->wait.SetSchedulerValue(0);
                    state->alternate_text = 0;
                }
                break;
            case 12:
                state->countdown = 1;
                break;
            case 18:
                asm_Sound_PlayDummyRetail_00420b10(1, MusicRecord()->music_slot);
                DispatcherCreateAnimation(StageState()->effect_resource, 2, 15);
                break;
            case 19:
                switch (data_00474c7c) {
                case 1: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x0D, 15).value;
                    break;
                }
                case 2: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x10, 15).value;
                    break;
                }
                case 3: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x14, 15).value;
                    break;
                }
                case 4: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x15, 15).value;
                    break;
                }
                case 5: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x0E, 15).value;
                    break;
                }
                case 6: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x23, 15).value;
                    break;
                }
                case 7: {
                    state->stage_title.id.value =
                        DispatcherCreateAnimation(data_00477704->resource, 0x1D, 15).value;
                    break;
                }
                default: goto next_command;
                }
                break;
            case 20: {
                if (data_00474c74 != 4) {
                    unsigned char* progress = ProgressBytes();
                    int route = (data_00474c6c + data_00474c68 * 3) * 0x437C;
                    int stage = data_00474c7c;
                    progress[route + 0x4E1 + (stage + data_00474c74 * 6) * 8] = 1;
                    route = (data_00474c6c + data_00474c68 * 3) * 0x437C;
                    progress[route + (stage + (data_00474c74 * 3 + 0x4E) * 2) * 8] = 1;
                }
                if (data_00474ca0 & 0x10) {
                    data_00477830->OpenResult();
                    break;
                }
                if (data_00474c7c == 6) {
                    StageState()->flags |= 0x20;
                    data_00474c40.AddScore(data_00474c4c * 1000);
                    switch (data_00474c74) {
                    case 0:
                        data_00474c40.AddScore(data_00474c70 * 20000000);
                        data_00474c40.AddScore(data_00474c48 * 100000);
                        break;
                    case 1:
                        data_00474c40.AddScore(data_00474c70 * 25000000);
                        data_00474c40.AddScore(data_00474c48 * 100000);
                        break;
                    case 2:
                        data_00474c40.AddScore(data_00474c70 * 35000000);
                        data_00474c40.AddScore(data_00474c48 * 200000);
                        break;
                    case 3:
                        data_00474c40.AddScore(data_00474c70 * 40000000);
                        data_00474c40.AddScore(data_00474c48 * 300000);
                        break;
                    case 4:
                        data_00474c40.AddScore(data_00474c70 * 40000000);
                        data_00474c40.AddScore(data_00474c48 * 400000);
                        break;
                    }
                    if (data_00477838->replay_mode == 1) {
                        SetInputMode(&data_00491c28, 4);
                        break;
                    }
                    CreateScreenEffect_0043c8b0(0x31, 5, 0x78, 0, 0, 0);
                    DispatcherStageState* stage = StageState();
                    stage->result_phase = 0;
                    stage->flags |= 0x10;
                    int* count = ClearCount();
                    if (*count < 99999)
                        ++*count;
                } else if (data_00474c7c == 7) {
                    StageState()->flags |= 0x20;
                    data_00474c40.AddScore(data_00474c4c * 1000);
                    data_00474c40.AddScore(data_00474c70 * 40000000);
                    data_00474c40.AddScore(data_00474c48 * 400000);
                    if (data_00477838->replay_mode == 1) {
                        SetInputMode(&data_00491c28, 4);
                        break;
                    }
                    data_00477830->OpenResult();
                    int* count = ClearCount();
                    if (*count < 99999)
                        ++*count;
                } else {
                    DispatcherStageState* stage = StageState();
                    DispatcherRemoveAnimation(reinterpret_cast<AnimationLookupContext*>(data_00491c10),
                        stage->transition_animation);
                    stage->transition_animation.value = 0;
                    stage->transition_animation.value =
                        DispatcherCreateAnimation(stage->resource, 0x4C, 15).value;
                    SetInputMode(&data_00491c28, 11);
                    reinterpret_cast<DispatcherRankState*>(&data_00474c40)->AdvanceLevel();
                }
                break;
            }
            case 21:
                asm_Sound_PlayRandomVoiceRetail_00420c30(data_00474c7c == 6 ? 8.0f : 2.0f);
                break;
            case 0:
                if (data_00474c84)
                    data_00474c8c = 0;
                data_00474c84 = 0;
                return -1;
}
        next_command:
            state->command = reinterpret_cast<DispatcherCommand*>(
                reinterpret_cast<unsigned char*>(state->command) +
                4 + state->command->operand_size);
        } while (state->timer.current >= (int)state->command->frame);
    }
    state->timer.Tick();
    return 0;
}
#pragma code_seg()

