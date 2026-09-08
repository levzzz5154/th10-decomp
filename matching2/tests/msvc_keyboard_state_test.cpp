#include <cassert>
#include <cstring>

#define __declspec(attribute)
#define __stdcall
#define __cdecl
#define __fastcall
#include "../msvc/src/platform/keyboard_state.cpp"

static BYTE captured[256];
static int get_calls;
static int set_calls;
static BOOL get_result;
static BOOL set_result;
int g_input_enabled;
unsigned int g_input_mode;
KeyboardDevice* g_keyboard_device;
static int device_state_calls;
static int acquire_calls;
static int device_result;

static int Acquire(KeyboardDevice* device) {
    assert(device == g_keyboard_device);
    ++acquire_calls;
    return -77;
}

static int GetDeviceState(KeyboardDevice* device, unsigned int size, void* state) {
    assert(device == g_keyboard_device && size == 256);
    ++device_state_calls;
    std::memset(state, 0x5a, size);
    return device_result;
}

extern "C" BOOL GetKeyboardState(BYTE* state) {
    ++get_calls;
    for (int index = 0; index < 256; ++index)
        state[index] = (BYTE)((index * 37) ^ 0x80);
    return get_result;
}

extern "C" BOOL SetKeyboardState(BYTE* state) {
    ++set_calls;
    std::memcpy(captured, state, sizeof(captured));
    return set_result;
}

static void run_case(BOOL get_value, BOOL set_value) {
    get_calls = set_calls = 0;
    get_result = get_value;
    set_result = set_value;
    std::memset(captured, 0xff, sizeof(captured));
    Input_NormalizeKeyboardState();
    assert(get_calls == 1 && set_calls == 1);
    for (int index = 0; index < 256; ++index) {
        BYTE input = (BYTE)((index * 37) ^ 0x80);
        assert(captured[index] == (BYTE)(input & 0x7f));
    }
}

static void run_update_case(bool enabled, bool direct_input, int result,
                            int expected_return, int expected_acquires) {
    BYTE state[256];
    std::memset(state, 0xcc, sizeof(state));
    get_calls = device_state_calls = acquire_calls = 0;
    g_input_enabled = enabled;
    g_input_mode = direct_input ? 0x200 : 0;
    device_result = result;
    int actual = Input_UpdateKeyboardState((void*)0x12345678, state);
    assert(actual == expected_return && acquire_calls == expected_acquires);
    if (!enabled) {
        assert(get_calls == 0 && device_state_calls == 0);
        for (int index = 0; index < 256; ++index) assert(state[index] == 0);
    } else if (!direct_input) {
        assert(get_calls == 1 && device_state_calls == 0);
        for (int index = 0; index < 256; ++index)
            assert(state[index] == (BYTE)((index * 37) ^ 0x80));
    } else {
        assert(get_calls == 0 && device_state_calls == 1);
        for (int index = 0; index < 256; ++index) assert(state[index] == 0x5a);
    }
}

int main() {
    KeyboardDeviceVtable vtable;
    std::memset(&vtable, 0, sizeof(vtable));
    vtable.Acquire = Acquire;
    vtable.GetDeviceState = GetDeviceState;
    KeyboardDevice device = {&vtable};
    g_keyboard_device = &device;

    run_case(1, 1);
    run_case(0, 1);  // Retail still normalizes/publishes after get failure.
    run_case(1, 0);  // The publish result is deliberately ignored too.
    run_case(0, 0);
    run_update_case(false, false, 0, 0, 0);
    run_update_case(true, false, 0, 0, 0);
    run_update_case(true, true, 0, 1, 0);
    run_update_case(true, true, (int)0x8007001e, 1, 1);
    run_update_case(true, true, -9, 1, 1);
}
