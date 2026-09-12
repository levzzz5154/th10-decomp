#pragma once

// Result overlay mode switch and eight-digit display (retail 0x004172E0).
// Retail function 0x004172E0 (__userpurge, 768 bytes).

struct ResultOverlayState {
	int digit_handles[8]; // retail +0x9DF4
	int main_handle;      // +0x9E14
	int secondary_handle; // +0x9E18
	void* resource;       // +0x9EC8
};

struct ResultDigitVm {
	int handle;
	int layer;
	unsigned int flags;
};

struct ResultOverlayEnv {
	void (*retire)(int handle);
	int (*create_animation)(void* resource, int script, int layer);
	ResultDigitVm* (*allocate_digit_vm)();
	void (*assign_script)(void* resource, ResultDigitVm* vm, int script);
	int (*register_vm)(ResultDigitVm* vm);
	void (*configure_digit)(int handle, int sprite_index); // digit + 8
	void (*show)(int* handle_slot);   // retail 0x00449590
	void (*hide)(int* handle_slot);   // retail 0x004495E0
};

// 0x004172E0 - Switch the result overlay. Mode 0 creates script 71 and an
// eight-digit script-39..46 display for number; 1/6 replace the main handle
// with scripts 72/76; 2..4 replace the secondary with scripts 73..75;
// mode 5 and out-of-range modes are no-ops.
void ResultOverlay_SetMode(ResultOverlayState* state, int mode, int number,
                           const ResultOverlayEnv* env);
