#pragma once
#include <string.h>
#include "../../../build_support/include/asm_encoding.hpp"
#include "th10/platform/windows_types.hpp"
#include "../../../build_support/include/asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"


extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);

