// Compiler context only: the real pool allocator 0x00449950, so the pass sees the callee's body and
// gives its callers the private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$00449950_fn")
#include "../result_open/allocate.cpp"
