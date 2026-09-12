#pragma once

// Joystick property block setup (retail 0x0044C7E0).
#include "th10/util/scalars.hpp"

struct JoyPropertyBlock {
	Word size;        // 0x24
	Word header_size; // 1
	Word object;      // 0
	Word how;         // 0
	Word value;       // packed range value
};

struct JoyPropertyEnv {
	void** device_slot;
	int (*prepare_device)(void* device);
	int (*set_property)(void* device, const JoyPropertyBlock* block);
};

int Input_SetJoystickProperty(Half range, short scale,
                              JoyPropertyEnv* env);
