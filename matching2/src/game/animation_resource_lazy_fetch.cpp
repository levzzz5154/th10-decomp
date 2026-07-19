// 0x0040C540 FUN_0040c540
// Readable reconstruction of retail helper FUN_0040c540.
//
// See the header for the slot layout.  The readable body mirrors the
// retail control flow exactly: return early when the cached handle is
// already armed, otherwise call the injected ``fetch_handle`` callback
// (retail FUN_00448d50) and store its result at game_thread + 0x89a4.

#include "th10/game/animation_resource_lazy_fetch.hpp"

#include <cstdint>


void GameStateThread_EnsureAnimationHandle(
    void* game_thread,
    uint32_t (*fetch_handle)(void* game_thread)) {
    if (game_thread == 0) return;
    uint8_t* bytes = static_cast<uint8_t*>(game_thread);
    uint32_t* cached_handle =
        reinterpret_cast<uint32_t*>(bytes + 0x89a4);
    if (*cached_handle != 0) return;
    if (fetch_handle == 0) return;
    *cached_handle = fetch_handle(game_thread);
}