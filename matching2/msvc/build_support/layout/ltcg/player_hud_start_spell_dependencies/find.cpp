// Compiler context only: the real animation lookup 0x004491C0, so the pass sees the callee's body and
// gives its callers the private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$004491c0_fn")
#include "../position_setter_find_anchor.cpp"
