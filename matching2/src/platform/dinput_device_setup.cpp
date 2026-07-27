#include "th10/platform/dinput_device_setup.hpp"

namespace {

// Retail tests bit 8 of the byte at +336 before touching anything.
const unsigned int kAlreadyInitialized = 8;
// SetCooperativeLevel arguments, retail's own literals: 22 for the keyboard
// (NOWINKEY | FOREGROUND | NONEXCLUSIVE) and 10 for the pad
// (BACKGROUND | NONEXCLUSIVE).
const int kKeyboardCooperativeLevel = 22;
const int kJoystickCooperativeLevel = 10;
// dword_491C44 = 44 - the DIDEVCAPS dwSize retail stamps before asking.
const int kDeviceCapsSize = 44;

void ReleaseDevice(void*& device, const DirectInputSetupEnv* env) {
    if (device != 0) {
        env->release(device);
        device = 0;
    }
}

}  // namespace

// 0x0043B8D0 - Create and configure the keyboard and optional joystick.
// Both keyboard setup failures unwind the keyboard and then the
// IDirectInput8 (the second one through 0x00421D20) and differ only in the
// line they log. The pad block issues its four calls unconditionally: retail
// discards every one of those results and logs "pad found" regardless.
int Input_InitializeDevices(DirectInputDevices* input,
                            const DirectInputSetupEnv* env) {
    void* instance = env->window_instance();
    if (input->flags & kAlreadyInitialized) {
        return -1;
    }

    input->direct_input = env->create_input(instance);
    if (input->direct_input == 0) {
        env->log(kDirectInputCreateFailed);
        return -1;
    }

    input->keyboard = env->create_keyboard(input->direct_input);
    if (input->keyboard == 0) {
        env->log(kDirectInputDeviceFailed);
        ReleaseDevice(input->direct_input, env);
        return -1;
    }

    void* window = env->window_handle();
    if (env->keyboard_format(input->keyboard)) {
        env->log(kDirectInputDataFormatFailed);
        ReleaseDevice(input->keyboard, env);
        ReleaseDevice(input->direct_input, env);
        return -1;
    }
    if (env->cooperative(input->keyboard, window,
                         kKeyboardCooperativeLevel)) {
        ReleaseDevice(input->keyboard, env);
        // 0x00421D20: release the IDirectInput8 held at +12 and clear it.
        ReleaseDevice(input->direct_input, env);
        env->log(kDirectInputCooperativeFailed);
        return -1;
    }

    env->acquire(input->keyboard);
    env->log(kDirectInputReady);
    input->joystick = env->enumerate_controller(input->direct_input);
    if (input->joystick != 0) {
        env->joystick_format(input->joystick);
        env->cooperative(input->joystick, window, kJoystickCooperativeLevel);
        env->capabilities(input->joystick, kDeviceCapsSize);
        env->objects(input->joystick);
        env->log(kDirectInputPadFound);
    }

    return 0;
}

// 0x0043BA90 - clear the two device-present bits of the status word, run
// 0x0043B8D0, then set bit 0x200 when a keyboard was created and bit 0x400
// when a pad was. 0x0044A4E0 reads bit 0x400 to choose between the
// DirectInput pad and joyGetPosEx.
unsigned int Input_InitializeAndPublishFlags(DirectInputDevices* input,
                                             unsigned int* status_flags,
                                             const DirectInputSetupEnv* env) {
    *status_flags &= 0xFFFFF9FFu;
    Input_InitializeDevices(input, env);
    if (input->keyboard != 0) {
        *status_flags |= 0x200u;
    }
    if (input->joystick != 0) {
        *status_flags |= 0x400u;
    }
    return *status_flags;
}
