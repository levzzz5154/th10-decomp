#pragma once
#include "th10/game/game_thread_queue_native.hpp"

// Complete local formatter definition lets LTCG derive the retail private ABI.
__declspec(noinline) void __cdecl AsciiManager_AddFormatted(
    const Vec32* position, GameThread2* thread,
    const char* format, ...);
