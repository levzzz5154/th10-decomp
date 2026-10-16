// Compiler context only: the real script loader 0x0043E710, so the pass sees
// the callee's body and gives its callers the private register convention.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$0043e710_fn")
#include "../../../../src/core/sprtanim/animation_object_load_script.cpp"
