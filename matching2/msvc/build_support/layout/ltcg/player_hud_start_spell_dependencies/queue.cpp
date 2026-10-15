// Compiler context only: the real sound queue request 0x0043DC90, so the pass sees the callee's body and
// gives its callers the private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$0043dc90_fn")
#include "../../../../src/core/sound/animation_manager_queue_resource_0043dc90.cpp"
