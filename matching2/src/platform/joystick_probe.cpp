#include "th10/platform/joystick_probe.hpp"

#include <cstring>

// 0x0044A0C0 - Probe for a joystick. Device 0 is preferred: only when
// its position query fails is device 1 tried, and only when both fail
// does the missing-joystick report run. The WinMM edges are injected.
uint32_t Joystick_Probe(
        uint32_t (*get_position)(uint32_t device_id, JoystickProbeInfo* info),
        uint32_t (*get_capabilities)(uint32_t device_id, void* capabilities,
                                     uint32_t size),
        void (*report_missing)()) {
    JoystickProbeInfo info;
    memset(&info, 0, sizeof(info));
    info.size = 0x34;
    info.flags = 0xFF;
    if (get_position(0, &info) != 0 && get_position(1, &info) != 0) {
        if (report_missing != 0) {
            report_missing();
        }
        return 1;
    }
    return get_capabilities(0, DAT_004918b8, 0x194) & 0xFFFF0000u;
}
