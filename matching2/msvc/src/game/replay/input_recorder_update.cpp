// Input recorder per-frame update at 0x004297D0: while recording it samples
// the masked key state (with the optional hold-to-slow assist), stores one
// analog sample every 30 frames and appends the input packet; during
// playback it feeds the recorded packet back into the key state.
#include "../../../build_support/layout/ltcg/input_recorder.hpp"

#pragma code_seg(".text$03update")
int InputRecorder::Update() {
    if (!g_game)
        return 1;
    if (!playback_mode) {
        g_input_keys_raw.previous_keys = g_input_keys_raw.held_keys;
        g_input_keys_raw.held_keys = static_cast<unsigned short>(g_input_keys_raw.raw_keys & 0x1F7);
        if (g_sound_flags & 0x200) {
            if (static_cast<unsigned char>(g_input_keys_raw.held_keys) & 1) {
                unsigned short frames = g_input_keys_raw.held_frames + 1;
                g_input_keys_raw.held_frames = frames;
                if (frames >= 8) {
                    g_input_keys_raw.held_keys |= 4;
                    g_input_keys_raw.held_frames = 8;
                }
            } else {
                g_input_keys_raw.held_frames = 0;
            }
        }
        g_input_keys_raw.Update();
        if (frame_count % 30 == 0) {
            float rounded = g_fps->value + 0.5f;
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
                static_cast<unsigned short>(g_input_keys_raw.input_word),
                g_input_keys_raw.new_press,
                g_input_keys_raw.new_release)) {
            current_pool = reinterpret_cast<RecorderPoolLink*>(
                reinterpret_cast<RecorderPoolLists*>(this)->AppendPage(active_stage));
        }
        ++frame_count;
        return 1;
    }
    if (active_stage >= 0) {
        g_input_keys_raw.previous_keys = g_input_keys_raw.held_keys;
        if (playback[active_stage].consumed < playback[active_stage].header->input_count) {
            g_input_keys_raw.held_keys = playback[active_stage].input_cursor->buttons;
            g_input_keys_raw.new_press = playback[active_stage].input_cursor->value_02;
            g_input_keys_raw.new_release = playback[active_stage].input_cursor->value_04;
            sample = *playback[active_stage].sample_cursor;
            ++playback[active_stage].input_cursor;
            if (frame_count % 30 == 0)
                ++playback[active_stage].sample_cursor;
        } else {
            g_input_keys_raw.held_keys = 0;
            g_input_keys_raw.new_press = 0;
            g_input_keys_raw.new_release = 0;
        }
        ++playback[active_stage].consumed;
        ++frame_count;
        return 1;
    }
    g_input_keys_raw.held_keys = 0;
    g_input_keys_raw.new_press = 0;
    g_input_keys_raw.new_release = 0;
    ++frame_count;
    return 1;
}
#pragma code_seg()
