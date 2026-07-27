#pragma once

// Per-button joystick state publish (retail 0x0044A4E0).
//
// Retail keeps the result in byte_497BB0, a 128-byte array holding 0x80 for
// every pressed button. Which source fills it depends on bit 0x400 of the
// status word 0x00491FF4, which 0x0043BA90 sets when 0x0043B8D0 managed to
// create a DirectInput pad: with the bit set the pad is polled and the
// DIJOYSTATE2 rgbButtons block is copied out, otherwise joyGetPosEx supplies
// the low 32 buttons.

struct JoystickButtonEnv {
	// dword_491FF4. Only bit 0x400 is read.
	unsigned int status_flags;
	// dword_491C3C - the DirectInput pad table indexed by the argument.
	void* const* devices;
	// IDirectInputDevice8::Poll, vtable +100. Negative = failed.
	int (*poll)(void* device);
	// IDirectInputDevice8::GetDeviceState, vtable +36; retail asks for the
	// full 272-byte DIJOYSTATE2.
	int (*device_state)(void* device, unsigned int bytes, void* state);
	// IDirectInputDevice8::Acquire, vtable +28. Retail compares the result
	// against DIERR_INPUTLOST (0x8007001E).
	int (*acquire)(void* device);
	// joyGetPosEx(0, &pji) with dwSize 52 and dwFlags 0xFF; zero on
	// success, and *buttons receives pji.dwButtons.
	unsigned int (*legacy_position)(unsigned int* buttons);
};

// 0x0044A4E0 - fill the 128-byte per-button state block. The block is
// cleared first, so an unreadable device simply reports nothing pressed.
void Input_ReadJoystickButtons(int device_index, unsigned char* buttons,
                               const JoystickButtonEnv* env);
