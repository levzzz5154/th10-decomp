#pragma once
#include "th10/game/game_thread_queue_native.hpp"

// Complete local formatter definition lets LTCG derive the retail private ABI.
__declspec(noinline) void __cdecl AppendFormatted_00401630(
    const Vec3_00401530* position, GameThread_00401530* thread,
    const char* format, ...);
