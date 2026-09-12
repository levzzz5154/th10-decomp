#include "th10/platform/dinput_device_setup.hpp"

namespace {

const unsigned int kAlreadyInitialized = 8;
const int kKeyboardCooperativeLevel = 0x16;
const int kJoystickCooperativeLevel = 10;
const int kAxisRangeProperty = 44;

void ReleaseDevice(void*& device, const DirectInputSetupEnv* env) {
    if (device != 0) {
        env->release(device);
        device = 0;
    }
}

}  // namespace

// 0x0043B8D0 - Create and configure the keyboard and optional joystick.
// Keyboard setup failures unwind both mandatory interfaces; a joystick setup
// failure releases only the optional joystick and leaves keyboard input live.
int Input_InitializeDevices(DirectInputDevices* input,
                            const DirectInputSetupEnv* env) {
    void* instance = env->window_instance();
    if (input->flags & kAlreadyInitialized) {
        return -1;
    }

    input->direct_input = env->create_input(instance);
    if (input->direct_input == 0) {
        env->log(1);
        return -1;
    }

    input->keyboard = env->create_keyboard(input->direct_input);
    if (input->keyboard == 0) {
        env->log(2);
        ReleaseDevice(input->direct_input, env);
        return -1;
    }

    void* window = env->window_handle();
    if (env->keyboard_format(input->keyboard) ||
        env->cooperative(input->keyboard, window,
                         kKeyboardCooperativeLevel)) {
        env->log(3);
        ReleaseDevice(input->keyboard, env);
        ReleaseDevice(input->direct_input, env);
        return -1;
    }

    env->acquire(input->keyboard);
    input->joystick = env->enumerate_controller(input->direct_input);
    if (input->joystick != 0) {
        if (env->joystick_format(input->joystick) ||
            env->cooperative(input->joystick, window,
                             kJoystickCooperativeLevel) ||
            env->property(input->joystick, kAxisRangeProperty) ||
            env->objects(input->joystick)) {
            ReleaseDevice(input->joystick, env);
        } else {
            env->log(4);
        }
    }

    return 0;
}
