#include "th10/platform/startup_dialog.hpp"

extern "C" __declspec(dllimport) UINT __stdcall IsDlgButtonChecked(HWND, int);
extern "C" __declspec(dllimport) BOOL __stdcall EndDialog(HWND, INT_PTR);
extern "C" __declspec(dllimport) HWND __stdcall GetDlgItem(HWND, int);

extern unsigned int g_startup_config_flags;

namespace {
    enum {
        kInitializeDialog = 0x110,
        kCommand = 0x111,
        kSetCheck = 0xF1,
        kChecked = 1,
        kYesButton = 201,
        kConfirmOnStartupCheckbox = 202,
        kNoButton = 203,
        kYesResult = 6,
        kNoResult = 7,
        kConfirmOnStartup = 0x100
    };
}

// 0x0043A3A0: initialize the confirmation checkbox, then save its setting
// when either choice closes the dialog. Unhandled messages return zero.
INT_PTR __stdcall StartupDialog_Procedure(HWND window, UINT message,
                                         WPARAM command, LPARAM) {
    switch (message) {
    case kInitializeDialog:
        SendMessageA(GetDlgItem(window, kConfirmOnStartupCheckbox),
                     kSetCheck, kChecked, 0);
        return 0;
    case kCommand:
        switch (static_cast<unsigned short>(command)) {
        case kYesButton:
            if (IsDlgButtonChecked(window, kConfirmOnStartupCheckbox) == kChecked)
                g_startup_config_flags |= kConfirmOnStartup;
            else
                g_startup_config_flags &= ~kConfirmOnStartup;
            EndDialog(window, kYesResult);
            break;
        case kNoButton:
            if (IsDlgButtonChecked(window, kConfirmOnStartupCheckbox) == kChecked)
                g_startup_config_flags |= kConfirmOnStartup;
            else
                g_startup_config_flags &= ~kConfirmOnStartup;
            EndDialog(window, kNoResult);
            break;
        default:
            return 0;
        }
        break;
    }
    return 0;
}
