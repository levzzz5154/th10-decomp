#pragma once

// DirectInput keyboard and optional joystick creation (retail 0x0043B8D0),
// and the flag publish its only caller performs (retail 0x0043BA90).

// The retail input object lives at 0x00491C28. Only four of its fields are
// touched here; the retail offsets are named beside each one.
struct DirectInputDevices {
	unsigned flags;      // retail +336, bit 8 = "already initialised"
	void* direct_input;  // retail +12  (0x00491C34)
	void* keyboard;      // retail +16  (0x00491C38)
	void* joystick;      // retail +20  (0x00491C3C)
};

// The log lines 0x0043B8D0 hands to 0x0044B810, in retail's own order. The
// address beside each is the .rdata VA of the string retail pushes.
enum DirectInputSetupMessage {
	kDirectInputCreateFailed = 1,       // 0x0046F9E0 "DirectInput ..."
	kDirectInputDeviceFailed = 2,       // 0x0046F9E0, the same string
	kDirectInputDataFormatFailed = 3,   // 0x0046F9B0 "... SetDataFormat ..."
	kDirectInputCooperativeFailed = 4,  // 0x0046F97C "... SetCooperativeLevel"
	kDirectInputReady = 5,              // 0x0046F954 "DirectInput ..."
	kDirectInputPadFound = 6,           // 0x0046F934 "...pad found..."
};

struct DirectInputSetupEnv {
	// GetWindowLongA(hWnd, GWL_HINSTANCE).
	void* (*window_instance)();
	void* (*window_handle)();
	// DirectInput8Create(instance, 0x0800, IID_IDirectInput8A, &out, 0).
	void* (*create_input)(void* instance);
	// IDirectInput8::CreateDevice(GUID_SysKeyboard, &out, 0), vtable +12.
	void* (*create_keyboard)(void* direct_input);
	// IDirectInputDevice8::SetDataFormat, vtable +44. Nonzero = failed.
	int (*keyboard_format)(void* device);
	// IDirectInputDevice8::SetCooperativeLevel, vtable +52. Nonzero = failed.
	int (*cooperative)(void* device, void* window, int level);
	// IDirectInputDevice8::Acquire, vtable +28.
	int (*acquire)(void* device);
	// IDirectInput8::EnumDevices(4, 0x0043BAF0, 0, 1), vtable +16; the
	// retail callback creates the first attached game controller. Returns
	// the created device, or null when no pad answered.
	void* (*enumerate_controller)(void* direct_input);
	// IDirectInputDevice8::SetDataFormat with c_dfDIJoystick2, vtable +44.
	void (*joystick_format)(void* device);
	// IDirectInputDevice8::GetCapabilities, vtable +12. Retail keeps the
	// DIDEVCAPS at 0x00491C44 and stamps its dwSize with 44 first.
	void (*capabilities)(void* device, int caps_size);
	// IDirectInputDevice8::EnumObjects(0x0043BB30, 0, 0), vtable +16; the
	// retail callback puts every axis on the -1000..1000 range property.
	void (*objects)(void* device);
	// IUnknown::Release, vtable +8.
	void (*release)(void* device);
	// 0x0044B810 with one of the DirectInputSetupMessage strings.
	void (*log)(int message);
};

int Input_InitializeDevices(DirectInputDevices*, const DirectInputSetupEnv*);

// 0x0043BA90 - the only caller: clear bits 0x200|0x400 of the status word
// (0x00491FF4), run 0x0043B8D0, then republish bit 0x200 from the keyboard
// pointer and bit 0x400 from the joystick pointer.
unsigned int Input_InitializeAndPublishFlags(DirectInputDevices* input,
                                             unsigned int* status_flags,
                                             const DirectInputSetupEnv* env);
