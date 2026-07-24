#pragma once

#include <cstdint>

enum TitleOptionsInput : uint32_t {
    TITLE_OPTIONS_UP = 0x10,
    TITLE_OPTIONS_DOWN = 0x20,
    TITLE_OPTIONS_LEFT = 0x40,
    TITLE_OPTIONS_RIGHT = 0x80,
    TITLE_OPTIONS_CANCEL = 0x0A,
    TITLE_OPTIONS_CONFIRM = 0x1001,
};

enum TitleOptionsAction {
    TITLE_OPTIONS_ACTION_NONE = 0,
    TITLE_OPTIONS_ACTION_VALUE_CHANGED,
    TITLE_OPTIONS_ACTION_DEFAULTS,
    TITLE_OPTIONS_ACTION_KEY_CONFIG,
    TITLE_OPTIONS_ACTION_RETURN,
};

struct TitleOptionsConfig {
    int bgm_mode;
    int music_volume;
    int sound_volume;
};

struct TitleOptionsState {
    int phase;
    int selection;
    int previous_selection;
    int phase_frame;
    TitleOptionsAction pending_action;
};

void TitleOptions_Initialize(TitleOptionsState* state);
TitleOptionsAction TitleOptions_Update(TitleOptionsState* state,
                                       TitleOptionsConfig* config,
                                       uint32_t input_flags);
