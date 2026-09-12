#include "th10/game/game_ui_create.hpp"

#include <cstring>

#include "th10/game/game_config_defaults.hpp"


// Published game UI manager (retail 0x00477810).
uint32_t* DAT_00477810;

// 0x004180E0 - Create the game UI manager. Retail news 0x60 bytes,
// constructs the embedded config record at word 9 (0x00418C40), then
// zeroes all 0x18 words - killing the construction - before evicting
// managed device resources, stashing the caller's return address in
// word 0x17, publishing the pointer, setting the started bit, and
// spawning the UI worker thread.
uint32_t* GameUi_CreateAndPublish(void* (*allocate)(uint32_t size),
                                  void (*evict_managed_resources)(),
                                  void (*spawn_worker)(void* start_address,
                                                       void* argument),
                                  void* worker_proc,
                                  uint32_t return_address) {
    uint32_t* state =
        allocate != 0 ? (uint32_t*)allocate(0x60) : (uint32_t*)0;
    if (state != 0) {
        state[8] &= ~1u;  // dead: the wipe below covers it
        GameConfig_InitializeDefaults(
            (GameConfigRecord*)(state + 9));  // dead: wiped below
        memset(state, 0, 0x18 * sizeof(uint32_t));
    }
    if (evict_managed_resources != 0) {
        evict_managed_resources();
    }
    if (state == 0) {
        // Retail continues and writes through the null pointer here.
        return 0;
    }
    state[0x17] = return_address;
    DAT_00477810 = state;
    state[0x16] |= 4u;
    if (spawn_worker != 0) {
        spawn_worker(worker_proc, 0);
    }
    return state;
}
