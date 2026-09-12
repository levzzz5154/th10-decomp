#pragma once

// Live/replay input recorder and playback step (retail 0x004297D0).
struct InputRecorderStream {
    const unsigned char* command_cursor;
    const unsigned char* analog_cursor;
    int consumed;
    int command_count;
};

struct InputRecorderHost {
    int playback;
    int stream_index;
    int frame;
    unsigned char analog_value;
    InputRecorderStream streams[4];
};

struct InputRecorderEnv {
    int game_available;
    unsigned int live_buttons;
    unsigned int supervisor_buttons;
    float analog_source;
    unsigned short held_frames;
    unsigned int input_word;
    unsigned int auxiliary_word;
    void (*poll_live_input)(unsigned int* buttons);
    void (*record_analog)(unsigned char value);
    // Returns nonzero when the current recording packet is complete.
    int (*encode_frame)(unsigned int buttons, unsigned int auxiliary_word,
                        short auxiliary_high);
    void (*advance_record_stream)(InputRecorderHost* host);
};

int InputRecorder_Step(InputRecorderHost* host, InputRecorderEnv* env);
