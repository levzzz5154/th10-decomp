#pragma once

// DirectInput keyboard and optional joystick creation (retail 0x0043B8D0).
// Retail function 0x0043B8D0.
struct DirectInputDevices{unsigned flags;void*direct_input;void*keyboard;void*joystick;};
struct DirectInputSetupEnv{void*(*window_instance)();void*(*window_handle)();void*(*create_input)(void*);void*(*create_keyboard)(void*);int(*keyboard_format)(void*);int(*cooperative)(void*,void*,int);int(*acquire)(void*);void*(*enumerate_controller)(void*);int(*joystick_format)(void*);int(*property)(void*,int);int(*objects)(void*);void(*release)(void*);void(*log)(int);};
int Input_InitializeDevices(DirectInputDevices*,const DirectInputSetupEnv*);
