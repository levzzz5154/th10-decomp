// Initialize the complete large global state, retaining member initialization
// before its original object-wide zero fill.
#include <string.h>
#include "th10/game/large_initialization_state.hpp"
extern "C" const void* const g_anm_vm_vtable[];
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#pragma code_seg(".text$01anchor")
extern "C" __declspec(noinline) LargeInitializationState* __stdcall
Init11(LargeInitializationState* state) {
    GameConfig_InitializeDefaults(0, &state->config);
    state->timer.previous = 0;
    state->timer.current = 0;
    state->timer.elapsed = 0;
    state->timer.control = 0;
    state->timer.vtable = g_anm_vm_vtable;
    _ReadWriteBarrier();
    memset(state, 0, sizeof(*state));
    state->flags |= 0x140u;
    return state;
}
#pragma code_seg()
