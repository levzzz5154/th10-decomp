#pragma once

#include "th10/platform/windows_types.hpp"

// The startup confirmation stores its checkbox in configuration bit 0x100
// and closes with IDYES (6) or IDNO (7).
INT_PTR __stdcall StartupDialog_Procedure(HWND window, UINT message,
                                         WPARAM command, LPARAM parameter);
