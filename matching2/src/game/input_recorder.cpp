#include "th10/game/input_recorder.hpp"

namespace {
unsigned short ReadU16(const unsigned char* data) {
    return static_cast<unsigned short>(data[0] | (data[1] << 8));
}
unsigned int ReadU32(const unsigned char* data) {
    return static_cast<unsigned int>(data[0]) |
           (static_cast<unsigned int>(data[1]) << 8) |
           (static_cast<unsigned int>(data[2]) << 16) |
           (static_cast<unsigned int>(data[3]) << 24);
}
}

// 0x004297D0 - update the shared input words from either live controls or the
// selected six-byte replay packet stream. The high half of input_word always
// retains the preceding frame's low buttons, matching the retail edge-state
// convention.
int InputRecorder_Step(InputRecorderHost* host, InputRecorderEnv* env) {
    if (!env->game_available) {
        return 1;
    }

    if (!host->playback) {
        env->input_word = (env->input_word << 16) |
                          (env->live_buttons & 0x1f7u);
        if ((env->supervisor_buttons & 0x200u) != 0) {
            if ((env->live_buttons & 1u) != 0) {
                if (++env->held_frames >= 8u) {
                    env->input_word = (env->input_word & 0xffff0000u) |
                                      ((env->live_buttons & 0x1f3u) | 4u);
                    env->held_frames = 8;
                }
            } else {
                env->held_frames = 0;
            }
        }
        env->poll_live_input(&env->input_word);

        if (host->frame % 30 == 0) {
            float rounded = env->analog_source + 0.5f;
            const unsigned char value = rounded < 256.0f
                ? static_cast<unsigned char>(static_cast<unsigned int>(rounded))
                : static_cast<unsigned char>(255);
            env->record_analog(value);
        }
        if (env->encode_frame(env->input_word, env->auxiliary_word,
                              static_cast<short>(env->auxiliary_word >> 16))) {
            env->advance_record_stream(host);
        }
        ++host->frame;
        return 1;
    }

    if (host->stream_index < 0) {
        env->input_word = (env->input_word << 16);
        env->auxiliary_word = 0;
        ++host->frame;
        return 1;
    }

    InputRecorderStream& stream = host->streams[host->stream_index];
    env->input_word <<= 16;
    if (stream.consumed >= stream.command_count) {
        env->auxiliary_word = 0;
    } else {
        env->input_word |= ReadU16(stream.command_cursor);
        env->auxiliary_word = ReadU32(stream.command_cursor + 2);
        host->analog_value = *stream.analog_cursor;
        stream.command_cursor += 6;
        if (host->frame % 30 == 0) {
            ++stream.analog_cursor;
        }
    }
    ++stream.consumed;
    ++host->frame;
    return 1;
}
