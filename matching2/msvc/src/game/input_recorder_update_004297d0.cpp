// Input recorder per-frame update at 0x004297D0: while recording it samples
// the masked key state (with the optional hold-to-slow assist), stores one
// analog sample every 30 frames and appends the input packet; during
// playback it feeds the recorded packet back into the key state.
#include "../../layout/ltcg/input_recorder.hpp"

#pragma code_seg(".text$03update")
int InputRecorder_004297D0::Update() {
    if (!data_00477810)
        return 1;
    if (!playback_mode) {
        data_00474e30.previous_keys = data_00474e30.held_keys;
        data_00474e30.held_keys = static_cast<unsigned short>(data_00474e30.raw_keys & 0x1F7);
        if (data_00491d78 & 0x200) {
            if (static_cast<unsigned char>(data_00474e30.held_keys) & 1) {
                unsigned short frames = data_00474e30.held_frames + 1;
                data_00474e30.held_frames = frames;
                if (frames >= 8) {
                    data_00474e30.held_keys |= 4;
                    data_00474e30.held_frames = 8;
                }
            } else {
                data_00474e30.held_frames = 0;
            }
        }
        data_00474e30.Update();
        if (frame_count % 30 == 0) {
            float rounded = data_00477708->value + 0.5f;
            unsigned int value;
            if (rounded >= 256.0f)
                value = 255;
            else
                value = static_cast<unsigned char>(static_cast<int>(rounded));
            RecorderPool* pool = current_pool->pool;
            *pool->storage.state_cursor = value;
            ++pool->storage.state_cursor;
        }
        RecorderPool* pool = current_pool->pool;
        if (pool->AppendPacket(
                static_cast<unsigned short>(data_00474e30.input_word),
                data_00474e30.new_press,
                data_00474e30.new_release)) {
            current_pool = reinterpret_cast<RecorderPoolLink*>(
                reinterpret_cast<RecorderPoolLists*>(this)->AppendPage(active_stage));
        }
        ++frame_count;
        return 1;
    }
    if (active_stage >= 0) {
        data_00474e30.previous_keys = data_00474e30.held_keys;
        if (playback[active_stage].consumed < playback[active_stage].header->input_count) {
            data_00474e30.held_keys = playback[active_stage].input_cursor->buttons;
            data_00474e30.new_press = playback[active_stage].input_cursor->value_02;
            data_00474e30.new_release = playback[active_stage].input_cursor->value_04;
            sample = *playback[active_stage].sample_cursor;
            ++playback[active_stage].input_cursor;
            if (frame_count % 30 == 0)
                ++playback[active_stage].sample_cursor;
        } else {
            data_00474e30.held_keys = 0;
            data_00474e30.new_press = 0;
            data_00474e30.new_release = 0;
        }
        ++playback[active_stage].consumed;
        ++frame_count;
        return 1;
    }
    data_00474e30.held_keys = 0;
    data_00474e30.new_press = 0;
    data_00474e30.new_release = 0;
    ++frame_count;
    return 1;
}
#pragma code_seg()
