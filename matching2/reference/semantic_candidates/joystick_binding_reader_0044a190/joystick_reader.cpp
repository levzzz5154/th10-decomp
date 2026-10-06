#include "joystick_reader.hpp"
#include <string.h>

#pragma code_seg(".text$a10joystick")
extern "C" unsigned short __fastcall JoystickReadBindings(
        unsigned int flags, JoystickSelection selection) {
    JoystickBindings* binding = &data_00474e30[selection.binding_set];
    if ((data_00491ff4 & 0x400) == 0) {
        JoystickPosition info;
        memset(&info, 0, sizeof(info));
        info.size = sizeof(info);
        info.flags = 0xff;
        int device = selection.device;
        if (data_00466280(device != 0, &info) == 0) {
            unsigned int buttons = info.buttons;
            if (binding->fire >= 0)
                flags |= (buttons & (1u << binding->fire)) ? JoystickFire : 0;
            if (binding->bomb >= 0)
                flags |= (buttons & (1u << binding->bomb)) ? JoystickBomb : 0;
            if (binding->escape >= 0)
                flags |= (buttons & (1u << binding->escape)) ? JoystickEscape : 0;
            if (binding->slow >= 0)
                flags |= (buttons & (1u << binding->slow)) ? JoystickSlow : 0;
            if (binding->control >= 0)
                flags |= (buttons & (1u << binding->control)) ? JoystickControl : 0;

            const JoystickCapabilities* caps = &data_004918b8[selection.device];
            unsigned int band_x = (caps->x_max - caps->x_min) >> 2;
            unsigned int upper_x = ((caps->x_min + caps->x_max) >> 1) + band_x;
            unsigned int lower_x = ((caps->x_min + caps->x_max) >> 1) - band_x;
            flags |= (info.x > upper_x ? JoystickRight : 0) | (info.x < lower_x ? JoystickLeft : 0);
            unsigned int band_y = (caps->y_max - caps->y_min) >> 2;
            unsigned int lower_y = ((caps->y_min + caps->y_max) >> 1) - band_y;
            unsigned int upper_y = ((caps->y_min + caps->y_max) >> 1) + band_y;
            return static_cast<unsigned short>(flags |
                    (info.y < lower_y ? JoystickUp : 0) | (info.y > upper_y ? JoystickDown : 0));
        }
    } else {
        JoystickDevice* pad = data_00491c3c[selection.device];
        if (pad->vtable->Poll(pad) < 0) {
            int retry_device = selection.device;
            pad = data_00491c3c[retry_device];
            int attempts = 0;
            long result = pad->vtable->Acquire(pad);
            if (result == static_cast<long>(0x8007001e)) {
                while (true) {
                    pad = data_00491c3c[retry_device];
                    result = pad->vtable->Acquire(pad);
                    ++attempts;
                    if (attempts >= 400)
                        break;
                    if (result != static_cast<long>(0x8007001e))
                        return static_cast<unsigned short>(flags);
                }
            }
        } else {
            int state_device = selection.device;
            __declspec(align(8)) JoystickDeviceState state;
            memset(&state, 0, sizeof(state));
            pad = data_00491c3c[state_device];
            if (pad->vtable->GetState(pad, sizeof(state), &state) >= 0) {
                if (binding->fire >= 0)
                    flags |= state.buttons[binding->fire] >> 7;
                if (binding->bomb >= 0)
                    flags |= (state.buttons[binding->bomb] >> 6) & JoystickBomb;
                if (binding->escape >= 0)
                    flags |= (state.buttons[binding->escape] >> 4) & JoystickEscape;
                if (binding->slow >= 0)
                    flags |= (state.buttons[binding->slow] >> 5) & JoystickSlow;
                if (binding->control >= 0)
                    flags |= (state.buttons[binding->control] & 0x80) << 1;

                // Subtracting one from an inside-limit predicate produces
                // an all-ones mask only outside the signed axis limit.
                return static_cast<unsigned short>(flags |
                        ((static_cast<unsigned int>(state.x >= -data_00491d5e) - 1) & JoystickLeft) |
                        ((static_cast<unsigned int>(state.y >= -data_00491d60) - 1) & JoystickUp) |
                        ((static_cast<unsigned int>(state.x <= data_00491d5e) - 1) & JoystickRight) |
                        ((static_cast<unsigned int>(state.y <= data_00491d60) - 1) & JoystickDown));
            }
        }
    }
    return static_cast<unsigned short>(flags);
}
#pragma code_seg()
