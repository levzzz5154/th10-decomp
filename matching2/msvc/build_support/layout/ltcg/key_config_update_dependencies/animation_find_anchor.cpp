// The lookup at 0x004491C0 as the animation restart 0x00449250 sees it. That
// address already holds this link's other view of the same function, so this
// copy is laid out in the unused bytes at 0x00449340.
#define code_seg(name) code_seg(".text$00449340_fn")
#include "../../../../src/core/sprtlib/animation_manager_find_004491c0.cpp"
#undef code_seg
#pragma code_seg()
