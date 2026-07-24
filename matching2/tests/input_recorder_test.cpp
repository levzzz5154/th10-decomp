#include "th10/game/input_recorder.hpp"
#include <cassert>
#include <cstdio>

namespace {
int polled, recorded, encoded, advanced;
unsigned char recorded_value;
void Poll(unsigned int*) { ++polled; }
void Record(unsigned char value) { ++recorded; recorded_value = value; }
int Encode(unsigned int, unsigned int, short) { ++encoded; return 1; }
void Advance(InputRecorderHost*) { ++advanced; }
}

int main() {
    InputRecorderHost host = {};
    InputRecorderEnv env = {};
    env.game_available = 1;
    env.live_buttons = 1;
    env.supervisor_buttons = 0x200;
    env.analog_source = 12.6f;
    env.poll_live_input = Poll;
    env.record_analog = Record;
    env.encode_frame = Encode;
    env.advance_record_stream = Advance;
    for (int i = 0; i < 8; ++i) InputRecorder_Step(&host, &env);
    assert(env.held_frames == 8);
    assert((env.input_word & 0xffffu) == 5u);
    assert(polled == 8 && recorded == 1 && recorded_value == 13);
    assert(encoded == 8 && advanced == 8);

    const unsigned char packets[] = {
        0x34, 0x12, 1, 2, 3, 4,
        0x78, 0x56, 5, 6, 7, 8,
    };
    const unsigned char analog[] = {9, 10};
    host = InputRecorderHost();
    host.playback = 1;
    host.stream_index = 0;
    host.streams[0].command_cursor = packets;
    host.streams[0].analog_cursor = analog;
    host.streams[0].command_count = 2;
    env.input_word = 0xabcd0000u;
    env.auxiliary_word = 0;
    InputRecorder_Step(&host, &env);
    assert(env.input_word == 0x00001234u);
    assert(env.auxiliary_word == 0x04030201u);
    assert(host.analog_value == 9);
    assert(host.streams[0].analog_cursor == analog + 1);
    InputRecorder_Step(&host, &env);
    assert(env.input_word == 0x12345678u);
    assert(env.auxiliary_word == 0x08070605u);
    assert(host.streams[0].analog_cursor == analog + 1);
    InputRecorder_Step(&host, &env);
    assert((env.input_word & 0xffffu) == 0 && env.auxiliary_word == 0);

    host.stream_index = -1;
    env.input_word = 0x00000077u;
    InputRecorder_Step(&host, &env);
    assert(env.input_word == 0x00770000u && env.auxiliary_word == 0);

    std::puts("recovery_batch44_test passed");
}
