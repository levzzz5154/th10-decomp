#pragma once
#include "th10/game/game_thread_queue_native.hpp"

// Complete local formatter definition lets LTCG derive the retail private ABI.
__declspec(noinline) void __cdecl AsciiManager_AddFormatted(
    const Vec3_00401530* position, GameThread_00401530* thread,
    const char* format, ...);
