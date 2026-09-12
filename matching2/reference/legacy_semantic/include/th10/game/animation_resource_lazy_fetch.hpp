// 0x0040C540 FUN_0040c540
// Readable reconstruction of retail helper FUN_0040c540.
//
// FUN_0040c540 lazy-initialises a game-thread-cached animation-resource
// handle.  Retail ABI has the game thread pointer carried in the
// preserved-ESI register across the call, so the readable signature
// reifies it as the first parameter.  The second parameter is the
// "fetch handle" callback that wraps FUN_00448d50 (the animation
// manager's per-resource lookup path); the readable version of
// FUN_00448d50 lives in ``src/render/animation_resource_lookup.cpp``
// (TODO) and the dispatcher plumbs it through this helper so the
// lazy-init remains testable in isolation.
//
// Layout (offsets relative to ``game_thread``):
//   0x8994 : pointer to the animation script resource being looked up
//   0x89a4 : cached animation handle (the first 4 bytes of the record
//            returned by FUN_00448d50)

#ifndef TH10_GAME_ANIMATION_RESOURCE_LAZY_FETCH_HPP
#define TH10_GAME_ANIMATION_RESOURCE_LAZY_FETCH_HPP

#include <cstdint>

// Fetch the cached animation handle stored at game_thread + 0x89a4 if
// it has already been armed; otherwise invoke ``fetch_handle`` to build
// the handle (retail FUN_00448d50) and store its first 4 bytes at
// game_thread + 0x89a4.  Safe to call with game_thread == 0 (no-op).
void GameStateThread_EnsureAnimationHandle(
    void* game_thread,
    uint32_t (*fetch_handle)(void* game_thread));

#endif  // TH10_GAME_ANIMATION_RESOURCE_LAZY_FETCH_HPP