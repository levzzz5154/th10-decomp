// Compiler context only: the real sound queue request 0x0043DC90, so the pass
// sees the callee's body and gives its callers the private register convention
// (queue in ECX, sound id in EDI, request on the stack). Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$0043dc90_fn")
#include "../../../../src/core/sound/animation_manager_queue_resource_0043dc90.cpp"
