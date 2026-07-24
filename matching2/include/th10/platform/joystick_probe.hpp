#pragma once

#include <cstdint>

// Probe record passed to the position edge (retail JOYINFOEX with
// dwSize 0x34 and dwFlags 0xFF; the payload stays opaque).
struct JoystickProbeInfo {
    uint32_t size;
    uint32_t flags;
    uint8_t payload[0x2C];
};

// Captured capabilities of joystick 0 (retail global 0x004918B8,
// 0x194 bytes; the host test provides the symbol).
extern uint8_t DAT_004918b8[0x194];

// 0x0044A0C0 - Probe for a joystick: query the position of devices 0
// and 1 (retail joyGetPosEx with dwSize 0x34 / dwFlags 0xFF); when both
// fail the retail error record (0x0044B810 with 0x00474F70 /
// 0x00470580) is reported and the call returns 1 (retail leaves the
// high half indeterminate). Otherwise the capabilities of device 0 are
// captured into the retail buffer at 0x004918B8 (joyGetDevCapsA, 0x194
// bytes) and the result's low half is masked off, so success yields 0.
uint32_t Joystick_Probe(
    uint32_t (*get_position)(uint32_t device_id, JoystickProbeInfo* info),
    uint32_t (*get_capabilities)(uint32_t device_id, void* capabilities,
                                 uint32_t size),
    void (*report_missing)());
