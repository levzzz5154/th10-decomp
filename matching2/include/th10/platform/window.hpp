#pragma once

#include "th10/platform/windows_types.hpp"

LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM wparam,
                                 LPARAM lparam);
void SaveSystemSettings();
DWORD CreateGameWindow(HINSTANCE instance);
BOOL ResolveShortcutTarget(const char* shortcut_path, char* target_path,
                           DWORD target_capacity);
int InstanceCheck();
