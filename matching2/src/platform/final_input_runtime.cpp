#include "th10/platform/final_input_runtime.hpp"

namespace th10::input_final {
namespace {

std::uint16_t Publish(State& state, std::uint16_t bits) {
    state.previous = state.current;
    state.current = bits;
    state.pressed = (state.previous ^ bits) & bits;
    state.released = (state.previous ^ bits) & ~bits;
    state.repeat = 0;

    for (int index = 0; index < 16; ++index) {
        const std::uint16_t mask = std::uint16_t(1u << index);
        if ((bits & mask) != 0) {
            if (++state.held[index] >= 26) {
                state.repeat |= mask;
                state.held[index] = std::uint16_t(state.held[index] - 8);
            }
        } else {
            state.held[index] = 0;
        }
    }
    return bits;
}

std::uint16_t MappedBits(const std::array<std::uint8_t, 256>& keys,
                         const std::array<int, 16>& mapping) {
    std::uint16_t bits = 0;
    for (int index = 0; index < 16; ++index) {
        const int key = mapping[index];
        if (key >= 0 && key < 256 &&
            (keys[static_cast<std::size_t>(key)] & 0x80) != 0)
            bits |= std::uint16_t(1u << index);
    }
    return bits;
}

// These are the byte indices used by retail's two input acquisition branches.
// The paired entries are the cursor/arrow alternatives visible in the IDA
// mask-building sequence, while the keypad diagonals contribute two axis bits.
std::uint16_t RetailKeyboardBits(const std::array<std::uint8_t, 256>& keys) {
    auto down = [&keys](int index) {
        return (keys[static_cast<std::size_t>(index)] & 0x80) != 0;
    };
    std::uint16_t bits = 0;
    if (down(0x5A)) bits |= 0x0001; // Z
    if (down(0x58)) bits |= 0x0002; // X
    if (down(0x10)) bits |= 0x0004; // shift
    if (down(0x1B)) bits |= 0x0008; // escape
    if (down(0x68) || down(0x26)) bits |= 0x0010; // numpad 8 / up
    if (down(0x62) || down(0x28)) bits |= 0x0020; // numpad 2 / down
    if (down(0x64) || down(0x25)) bits |= 0x0040; // numpad 4 / left
    if (down(0x66) || down(0x29)) bits |= 0x0080; // numpad 6 / right
    if (down(0x67)) bits |= 0x0050; // numpad 7: up + left
    if (down(0x69)) bits |= 0x0090; // numpad 9: up + right
    if (down(0x61)) bits |= 0x0060; // numpad 1: down + left
    if (down(0x63)) bits |= 0x00A0; // numpad 3: down + right
    return bits;
}

std::uint16_t RetailDirectInputBits(
        const std::array<std::uint8_t, 256>& keys) {
    auto down = [&keys](int index) {
        return (keys[static_cast<std::size_t>(index)] & 0x80) != 0;
    };
    std::uint16_t bits = 0;
    if (down(0x2C)) bits |= 0x0001; // DIK_Z
    if (down(0x2D)) bits |= 0x0002; // DIK_X
    if (down(0x2A)) bits |= 0x0004; // DIK_LSHIFT
    if (down(0x01)) bits |= 0x0008; // DIK_ESCAPE
    if (down(0x48) || down(0xC8)) bits |= 0x0010; // H/up or numpad 8
    if (down(0x50) || down(0xD0)) bits |= 0x0020; // B/down or numpad 2
    if (down(0x4B) || down(0xCB)) bits |= 0x0040; // K/left or numpad 4
    if (down(0x4D) || down(0xCD)) bits |= 0x0080; // M/right or numpad 6
    if (down(0xC7)) bits |= 0x0050; // numpad 7: up + left
    if (down(0xC9)) bits |= 0x0090; // numpad 9: up + right
    if (down(0xCF)) bits |= 0x0060; // numpad 1: down + left
    if (down(0xD1)) bits |= 0x00A0; // numpad 3: down + right
    return bits;
}

} // namespace

// 0x0044A5F0 - partial extraction of input_final::Poll. The state tail below
// (previous/current publication, edge masks, 16 held counters, repeat
// threshold 26, and subtraction of 8) matches the retail tail. Its original
// acquisition owns DirectInput/GetKeyboardState globals and the 0x0044A190
// joystick adapter; callers inject those boundaries here.
std::uint16_t Poll(State& state,
                   const std::array<std::uint8_t, 256>& keys,
                   const std::array<int, 16>& mapping,
                   std::uint16_t joystick,
                   bool enabled) {
    std::uint16_t bits = enabled ? MappedBits(keys, mapping) : 0;
    bits = std::uint16_t(bits | joystick);
    return Publish(state, bits);
}

// This helper covers the statically recovered acquisition sequence while
// keeping the ownership and callback dispatch boundary explicit. Retail
// invokes the joystick adapter even when input acquisition fails; the injected
// joystick word therefore remains part of every published frame.
std::uint16_t PollAcquired(State& state, const AcquisitionEnv& env) {
    std::array<std::uint8_t, 256> keys{};
    std::uint16_t keyboard_bits = 0;

    if (env.input_gate) {
        if (!env.use_direct_input) {
            // GetKeyboardState returns nonzero on success. Retail does not
            // branch on this return value; zeroing a failed read gives the
            // host a deterministic contract without claiming that undefined
            // stack bytes are part of reconstruction fidelity.
            if (env.get_keyboard_state != nullptr &&
                env.get_keyboard_state(env.context, keys.data()) != 0) {
                keyboard_bits = RetailKeyboardBits(keys);
            }
        } else if (env.get_device_state != nullptr && env.device != nullptr) {
            const int result = env.get_device_state(env.device, 256, keys.data());
            if (result == 0) {
                keyboard_bits = RetailDirectInputBits(keys);
            } else if (env.acquire_device != nullptr) {
                // Both DIERR_INPUTLOST and other failed reads call the
                // device's Acquire method before publishing the tail.
                env.acquire_device(env.device);
            }
        }
    }

    return Publish(state, std::uint16_t(keyboard_bits | env.joystick));
}

} // namespace th10::input_final
