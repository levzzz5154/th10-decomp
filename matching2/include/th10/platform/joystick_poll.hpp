#pragma once

// Joystick polling through winmm and DirectInput (retail 0x0044A190).
#include "th10/util/scalars.hpp"

// Packed input-state bits. The retail key config stores button indices in
// the order shot, bomb, slow, pause, ..., skip (DAT_00474e88 records).
enum InputBit {
	kPadShoot = 0x001,
	kPadBomb = 0x002,
	kPadFocus = 0x004, // the retail config calls this "slow"
	kPadPause = 0x008,
	kPadUp = 0x010,
	kPadDown = 0x020,
	kPadLeft = 0x040,
	kPadRight = 0x080,
	kPadSkip = 0x100,
};

// DIERR_INPUTLOST: the DirectInput device must be re-acquired.
constexpr int kDInputInputLost = (int)0x8007001E;

struct PadButtons { // retail DAT_00474e88 + config*0x6A
	short shoot;       // +0x00, sets kPadShoot ("shot" in config)
	short bomb;        // +0x02, sets kPadBomb
	short focus;       // +0x04, sets kPadFocus ("slow" in config)
	short pause;       // +0x06, sets kPadPause
	short reserved[4]; // +0x08
	short skip;        // +0x10, sets kPadSkip
};

struct WinmmState {
	Word buttons; // JOYINFOEX dwButtons
	Word x;       // dwXpos
	Word y;       // dwYpos
};

struct JoyCalibration { // retail DAT_004918dc + pad*0x194
	int x_min;
	int x_max;
	int y_min;
	int y_max;
};

struct DirectInputState { // DIJOYSTATE2 fields the poll reads
	int x;                    // lX
	int y;                    // lY
	Byte buttons[128]; // rgbButtons (bit 7 = pressed)
};

struct JoyPollEnv {
	int use_direct_input;             // retail DAT_00491ff4 & 0x400
	const PadButtons* configs; // indexed by config_index
	// winmm path
	int (*get_position)(int pad, WinmmState* out); // joyGetPosEx
	const JoyCalibration* calibrations; // indexed by pad
	// DirectInput path
	void** devices;              // retail DAT_00491c3c, indexed by pad
	int (*poll)(void* device);   // device vtable +0x64
	int (*acquire)(void* device); // device vtable +0x1C
	int (*get_state)(void* device, DirectInputState* out); // +0x24
	short threshold_x;           // retail DAT_00491d5e
	short threshold_y;           // retail DAT_00491d60
};

Half Joystick_Poll(Half state, int config_index, int pad,
                          JoyPollEnv* env);
