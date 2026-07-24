#pragma once

#include <cstddef>

// Stage controller projected-position update and callbacks (retail 0x00426360).
// --- 0x00426360: update one stage-background controller ---------------------
struct StageControllerVec3 { float x, y, z; };

struct StageController {
	int mode; // retail +0x458; mode 2 is dormant
	StageControllerVec3 position;       // retail +0x3C0
	StageControllerVec3 camera_offset;  // clean form of +0x334/+0x338/+0x33C
	StageControllerVec3 layer_offset;   // clean form of +0x340/+0x344/+0x348
	StageControllerVec3 projected;      // retail +0x354
	void (*callbacks[4])(void* context);
	void* callback_contexts[4];
};

struct StageControllerEnv {
	float projected_x_bias; // retail DAT_00470b4c
	float projected_y_bias; // retail DAT_00470b48
	bool effects_enabled;
	float effect_x_bias;    // retail DAT_00470cbc - DAT_00470b48
	float effect_y_bias;    // retail DAT_00470cb4 - DAT_00470be8
	void (*apply_camera)(StageController* controller);
	void (*spawn_effect)(float coordinate);
	void (*flush_effects)();
};

int StageController_Tick(StageController* controller,
                         StageControllerEnv* env);
