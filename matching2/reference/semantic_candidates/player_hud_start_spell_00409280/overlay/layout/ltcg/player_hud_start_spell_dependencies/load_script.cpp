// Compiler context only: the real script loader 0x0043E710, so the pass sees the callee's body and
// gives its callers the private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$0043e710_fn")
#include "../../../src/render/animation_object_load_script.cpp"
