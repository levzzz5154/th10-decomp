// Compiler context only: the real translated position setter 0x00449350, so the pass sees the callee's body and
// gives its callers the private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$00449350_fn")
#include "../../../src/render/animation_manager_set_translated_position_00449350.cpp"
