#include "th10/game/key_config_refresh_0042f8b0.hpp"
#include "th10/platform/sound_queue.hpp"
extern "C" __declspec(noinline) void __stdcall RefreshTitleKeyConfigView(TitleKeyConfigView*);

// Replace every duplicate of the requested key with the selected slot's old
// binding, assign the new key, refresh labels, and queue the feedback event.
#pragma code_seg(".text$03reassign")
extern "C" __declspec(noinline) void __stdcall KeyConfigReassignSlot_00430250(
        TitleKeyConfigView* state, int slot, int key) {
    short old_key = state->bindings_59cc[slot];
    if (old_key == key)
        return;
    if (slot != 0 && state->bindings_59cc[0] == key)
        state->bindings_59cc[0] = old_key;
    if (slot != 1 && state->bindings_59cc[1] == key)
        state->bindings_59cc[1] = state->bindings_59cc[slot];
    if (slot != 2 && state->bindings_59cc[2] == key)
        state->bindings_59cc[2] = state->bindings_59cc[slot];
    if (slot != 3 && state->bindings_59cc[3] == key)
        state->bindings_59cc[3] = state->bindings_59cc[slot];
    if (slot != 4 && state->bindings_59cc[4] == key)
        state->bindings_59cc[4] = state->bindings_59cc[slot];
    state->bindings_59cc[slot] = static_cast<short>(key);
    RefreshTitleKeyConfigView(state);
    g_sound_manager.Queue(10, 0);
}
#pragma code_seg()
