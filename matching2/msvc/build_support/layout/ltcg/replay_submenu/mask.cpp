// Complete 0x0040ACE0 key-mask test as a scoped view: the retail body takes
// the repeat state in ECX and the mask in EAX, a convention no declaration
// names, so the body is co-compiled into this cluster and anchored at its
// retail address. The maintained copy (src/game/eclview/input_mask_active.cpp)
// is scoped to its own cluster and declares its own record type, so this
// cluster carries the same body on the shared state.hpp view instead.
#include "th10/game/replay_submenu/state.hpp"

#pragma code_seg(".text$01mask")
int KeyRepeatState::InputMaskActive(unsigned short mask) {
    return (mask & unknown_06) != 0 || (mask & pressed) != 0;
}
#pragma code_seg()
