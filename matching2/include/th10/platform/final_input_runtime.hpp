#pragma once

#include <array>
#include <cstdint>

namespace th10::input_final {

// This is the state block written by the tail of retail 0x0044A5F0. The
// acquisition and joystick objects that precede it are deliberately kept out
// of this ABI-neutral state type.
struct State {
    std::uint16_t current{};
    std::uint16_t previous{};
    std::uint16_t pressed{};
    std::uint16_t released{};
    std::uint16_t repeat{};
    std::array<std::uint16_t, 16> held{};
};

// Testable form of the recovered state tail. ``mapping`` is a host binding:
// each entry names the keyboard byte that contributes to one logical bit.
// ``joystick`` is the result of the separate 0x0044A190 adapter.
std::uint16_t Poll(State& state,
                   const std::array<std::uint8_t, 256>& keys,
                   const std::array<int, 16>& mapping,
                   std::uint16_t joystick,
                   bool enabled);

// The acquisition contract visible in retail 0x0044A5F0. The callback
// conventions match the Win32/DirectInput calls used by the original:
// keyboard reads return nonzero on success, while GetDeviceState returns
// zero on success and an HRESULT on failure. A failed device read invokes
// acquire and publishes no device key bits for that frame.
struct AcquisitionEnv {
    void* context{};
    bool input_gate{};              // DAT_004924FC
    bool use_direct_input{};        // DAT_00491FF4 & 0x200
    void* device{};                 // DAT_00491C38
    int (*get_keyboard_state)(void* context,
                              std::uint8_t* state){};
    int (*get_device_state)(void* device,
                            unsigned int byte_count,
                            std::uint8_t* state){};
    int (*acquire_device)(void* device){};
    std::uint16_t joystick{};       // output of the 0x0044A190 adapter
};

// Fixed keyboard/scancode mappings recovered from the two static acquisition
// branches. This helper captures only acquisition plus the input-state tail;
// callback dispatch through the retail global manager remains out of scope.
std::uint16_t PollAcquired(State& state, const AcquisitionEnv& env);

} // namespace th10::input_final
