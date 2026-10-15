#pragma once
#include <stddef.h>
#include "th10/game/pause_choice_00422c80/cursor.hpp"
#include "th10/platform/sound_queue.hpp"
#include "th10/game/pause_choice_00422c80/animation.hpp"

struct PlayerSchedulerRecord {
    int field_00;
    int field_04;
    float field_08;
    int field_0C;
    int flags_10;
    __declspec(noinline) void SetSchedulerValue(int value);
};
struct KeyRepeatState {
    unsigned char unknown_00[4];
    unsigned short pressed;
    unsigned short unknown_06;
    __declspec(noinline) int InputMaskActive(unsigned short mask);
};
struct InputState {
    unsigned char unknown_0000[0x390];
    int mode_390;
    unsigned char unknown_0394[0x3CC - 0x394];
    unsigned int flags_3CC;
};
__declspec(noinline) void SetInputMode(InputState* state, int mode);
extern "C" KeyRepeatState g_input_keys_raw;
extern "C" unsigned int g_input_keys_held;
extern "C" InputState g_application;
extern "C" int g_main_state;
struct ChoiceRuntime { unsigned char reserved[0x5C]; int replay_mode; };
extern "C" ChoiceRuntime* g_game;
struct PauseChoiceState {
    int reserved_00;
    int phase;
    unsigned char reserved_08[8];
    PlayerSchedulerRecord timer;
    PauseChoiceCursor cursor;
    unsigned char reserved_fc[0x1D4-0xFC];
    Handle4 background;
    Handle4 cursor_animation;
    Handle4 pause_animation;
    unsigned char reserved_1e0[0x2C0-0x1E0];
    float saved_speed;
};
typedef char ChoiceTimerOffset[offsetof(PauseChoiceState,timer)==0x10 ? 1:-1];
typedef char ChoiceCursorOffset[offsetof(PauseChoiceState,cursor)==0x24 ? 1:-1];
typedef char ChoiceBackgroundOffset[offsetof(PauseChoiceState,background)==0x1D4 ? 1:-1];
typedef char ChoiceSavedSpeedOffset[offsetof(PauseChoiceState,saved_speed)==0x2C0 ? 1:-1];
