#pragma once

#include "th10/platform/windows_types.hpp"

LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM wparam,
                                 LPARAM lparam);
void SaveSystemSettings();
DWORD CreateGameWindow(HINSTANCE instance);
// The Win32 leaves WinMain (0x00438AD0) executes inline. They are transcribed
// out of the retail listing and operate on the same retail globals.
void RestoreSystemSettings();     // WinMain tail, after loc_438F9A
void DisableImeAndCursor();       // 0x00438C6D
void SetForegroundGameWindow();   // loc_438C82
void DestroyGameWindow();         // loc_438E4A .. loc_438E7F
void RestartGracePump();          // loc_438EAE .. loc_438EEE
BOOL ResolveShortcutTarget(const char* shortcut_path, char* target_path,
                           DWORD target_capacity);
int InstanceCheck();
