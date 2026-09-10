#include <cassert>

#define __declspec(attribute)
#define __stdcall
#define __cdecl
#define __fastcall
#include "../msvc/src/platform/startup_dialog.cpp"
#include "../msvc/src/platform/midi_timer.cpp"

unsigned int g_startup_config_flags;

namespace {
    enum Event { FindCheckbox, CheckCheckbox, ReadCheckbox, CloseDialog };
    Event events[4];
    int event_count;
    int window_storage;
    int checkbox_storage;
    HWND dialog_window = &window_storage;
    HWND checkbox_window = &checkbox_storage;
    HWND found_checkbox;
    UINT checked_state;
    INT_PTR close_result;
    unsigned int flags_at_read;

    void reset_calls() {
        event_count = 0;
        close_result = -1;
        found_checkbox = checkbox_window;
    }

    void record(Event event) {
        assert(event_count < 4);
        events[event_count++] = event;
    }
}

extern "C" HWND GetDlgItem(HWND window, int control) {
    assert(window == dialog_window && control == 202);
    record(FindCheckbox);
    return found_checkbox;
}

extern "C" void* SendMessageA(HWND window, UINT message, DWORD value, DWORD parameter) {
    assert(window == found_checkbox && message == 0xF1);
    assert(value == 1 && parameter == 0);
    record(CheckCheckbox);
    return 0;
}

extern "C" UINT IsDlgButtonChecked(HWND window, int control) {
    assert(window == dialog_window && control == 202);
    record(ReadCheckbox);
    // The configuration load occurs after this API returns in the reference.
    g_startup_config_flags = flags_at_read;
    return checked_state;
}

extern "C" BOOL EndDialog(HWND window, INT_PTR result) {
    assert(window == dialog_window);
    record(CloseDialog);
    close_result = result;
    return 0; // Its failure result does not change the callback's return.
}

static void test_initialization() {
    for (int missing_control = 0; missing_control != 2; ++missing_control) {
        reset_calls();
        if (missing_control)
            found_checkbox = 0;
        g_startup_config_flags = 0xA537;
        assert(StartupDialog_Procedure(dialog_window, 0x110, 0x12345678, -9) == 0);
        assert(event_count == 2);
        assert(events[0] == FindCheckbox && events[1] == CheckCheckbox);
        assert(g_startup_config_flags == 0xA537 && close_result == -1);
    }
}

static void test_choices() {
    const UINT states[] = {0, 1, 2, 0xffffffff};
    const unsigned int initial_flags[] = {0, 0x100, 0xA537, 0xffffffff};
    for (int choice = 0; choice != 2; ++choice) {
        for (int state = 0; state != 4; ++state) {
            for (int flags = 0; flags != 4; ++flags) {
                reset_calls();
                checked_state = states[state];
                flags_at_read = initial_flags[flags];
                g_startup_config_flags = ~flags_at_read;
                // WM_COMMAND selects the low word; its notification high word
                // and the LPARAM value do not affect the retail choice.
                WPARAM command = 0xABCD0000u | (choice ? 203 : 201);
                assert(StartupDialog_Procedure(dialog_window, 0x111, command, -1) == 0);
                assert(event_count == 2);
                assert(events[0] == ReadCheckbox && events[1] == CloseDialog);
                assert(close_result == (choice ? 7 : 6));
                assert((g_startup_config_flags & ~0x100u) == (flags_at_read & ~0x100u));
                assert((g_startup_config_flags & 0x100u) == (states[state] == 1 ? 0x100u : 0));
            }
        }
    }
}

static void test_unhandled_messages() {
    const UINT messages[] = {0, 0x10, 0x100, 0x112, 0xffffffff};
    for (int index = 0; index != 5; ++index) {
        reset_calls();
        g_startup_config_flags = 0x7F031234;
        assert(StartupDialog_Procedure(dialog_window, messages[index], 201, 0) == 0);
        assert(event_count == 0 && g_startup_config_flags == 0x7F031234);
    }
    const WPARAM commands[] = {0, 1, 200, 202, 204, 0xffff, 201u << 16};
    for (int index = 0; index != 7; ++index) {
        reset_calls();
        g_startup_config_flags = 0x7F031234;
        assert(StartupDialog_Procedure(dialog_window, 0x111, commands[index], 0) == 0);
        assert(event_count == 0 && g_startup_config_flags == 0x7F031234);
    }
}

struct CountingTimer : MidiTimerTarget {
    int calls;
    int result;
    CountingTimer(int return_value) : calls(0), result(return_value) {}
    virtual int OnTimer() {
        ++calls;
        return result;
    }
};

static void test_timer_target() {
    CountingTimer first(-7);
    CountingTimer second(42);
    MidiTimer_Callback(0, 0, &first, 0, 0);
    MidiTimer_Callback(0xffffffff, 0x12345678, &second, 17, 99);
    MidiTimer_Callback(3, 4, &first, 5, 6);
    assert(first.calls == 2 && second.calls == 1);
}

int main() {
    test_initialization();
    test_choices();
    test_unhandled_messages();
    test_timer_target();
}
