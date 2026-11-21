#pragma once
#include <string.h>
#include "th10/platform/windows_types.hpp"
#include "th10/runtime/asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"


extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);

