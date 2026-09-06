#include "th10/platform/final_input_runtime.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>

using namespace th10::input_final;

struct Fixture {
    std::array<std::uint8_t, 256> bytes{};
    int keyboard_calls{};
    int device_calls{};
    int acquire_calls{};
    int device_result{};
    unsigned int requested_bytes{};
};

static int ReadKeyboard(void* context, std::uint8_t* destination) {
    auto* fixture = static_cast<Fixture*>(context);
    ++fixture->keyboard_calls;
    std::memcpy(destination, fixture->bytes.data(), fixture->bytes.size());
    return 1; // GetKeyboardState succeeds with a nonzero result.
}

static int ReadDevice(void* device, unsigned int byte_count,
                      std::uint8_t* destination) {
    auto* fixture = static_cast<Fixture*>(device);
    ++fixture->device_calls;
    fixture->requested_bytes = byte_count;
    if (fixture->device_result == 0)
        std::memcpy(destination, fixture->bytes.data(), fixture->bytes.size());
    return fixture->device_result;
}

static int Acquire(void* device) {
    ++static_cast<Fixture*>(device)->acquire_calls;
    return 0;
}

int main() {
    // The keyboard branch uses the retail fixed virtual-key pairs and the
    // keypad diagonals contribute both direction bits.
    Fixture keyboard;
    keyboard.bytes[0x5A] = 0x80; // Z
    keyboard.bytes[0x63] = 0x80; // numpad 3: down + right
    AcquisitionEnv env{};
    env.context = &keyboard;
    env.input_gate = true;
    env.get_keyboard_state = ReadKeyboard;
    env.joystick = 0x400;
    State state;
    assert(PollAcquired(state, env) == 0x4A1);
    assert(state.pressed == 0x4A1 && keyboard.keyboard_calls == 1);

    // The retail gate skips both acquisition branches but still publishes the
    // adapter's joystick result into the state tail.
    env.input_gate = false;
    keyboard.bytes.fill(0);
    assert(PollAcquired(state, env) == 0x400);
    assert(state.released == 0xA1 && keyboard.keyboard_calls == 1);

    // DirectInput uses the corresponding scan-code table and requests the
    // complete 256-byte device state.
    Fixture direct;
    direct.bytes[0x2D] = 0x80; // DIK_X
    direct.bytes[0xC7] = 0x80; // numpad 7: up + left
    AcquisitionEnv direct_env{};
    direct_env.input_gate = true;
    direct_env.use_direct_input = true;
    direct_env.device = &direct;
    direct_env.get_device_state = ReadDevice;
    direct_env.acquire_device = Acquire;
    State direct_state;
    assert(PollAcquired(direct_state, direct_env) == 0x52);
    assert(direct.device_calls == 1 && direct.requested_bytes == 256);

    // Any failed device read follows the observed Acquire edge and leaves
    // device bits clear for this frame; the independent joystick word stays.
    direct.device_result = static_cast<int>(0x8007001E);
    direct_env.joystick = 0x200;
    assert(PollAcquired(direct_state, direct_env) == 0x200);
    assert(direct.acquire_calls == 1 && direct_state.released == 0x52);

    // The extracted tail keeps the 26-frame repeat threshold and subtracts 8
    // after publishing a repeat event.
    std::array<std::uint8_t, 256> keys{};
    std::array<int, 16> mapping{};
    mapping.fill(-1);
    mapping[0] = 7;
    State mapped;
    keys[7] = 0x80;
    assert(Poll(mapped, keys, mapping, 0, true) == 1);
    for (int frame = 0; frame < 24; ++frame)
        Poll(mapped, keys, mapping, 0, true);
    assert(mapped.held[0] == 25 && mapped.repeat == 0);
    Poll(mapped, keys, mapping, 0, true);
    assert(mapped.held[0] == 18 && mapped.repeat == 1);

    std::puts("FINAL_INPUT_RUNTIME_TESTS_PASS");
    return 0;
}
