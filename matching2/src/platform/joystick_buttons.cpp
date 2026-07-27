#include "th10/platform/joystick_buttons.hpp"

#include <cstring>

namespace {

// byte_497BB0 is 128 bytes; retail clears it with "mov ecx, 20h; rep stosd".
const unsigned int kButtonBytes = 128;
// DIJOYSTATE2: retail asks GetDeviceState for 0x110 bytes and copies the
// 128 rgbButtons bytes that start 0x30 into the block.
const unsigned int kJoyStateBytes = 272;
const unsigned int kButtonsOffset = 48;
// DIERR_INPUTLOST, the only status retail retries on, and its retry cap.
const int kInputLost = static_cast<int>(0x8007001E);
const int kAcquireRetries = 400;

}  // namespace

// 0x0044A4E0 - Publish the per-button joystick state.
void Input_ReadJoystickButtons(int device_index, unsigned char* buttons,
                               const JoystickButtonEnv* env) {
    std::memset(buttons, 0, kButtonBytes);
    if ((env->status_flags & 0x400u) != 0) {
        void* device = env->devices[device_index];
        if (env->poll(device) >= 0) {
            unsigned char state[kJoyStateBytes];
            env->device_state(device, kJoyStateBytes, state);
            std::memcpy(buttons, state + kButtonsOffset, kButtonBytes);
        } else if (env->acquire(device) == kInputLost) {
            // Retail re-acquires up to 400 times while the device keeps
            // answering DIERR_INPUTLOST, and reads nothing this frame.
            int attempts = 0;
            int status;
            do {
                status = env->acquire(device);
                ++attempts;
            } while (attempts < kAcquireRetries && status == kInputLost);
        }
        return;
    }
    unsigned int pressed = 0;
    if (env->legacy_position(&pressed) == 0) {
        for (unsigned int index = 0; index != 32; ++index) {
            if ((pressed & 1u) != 0) {
                buttons[index] = 0x80;
            }
            pressed >>= 1;
        }
    }
}
