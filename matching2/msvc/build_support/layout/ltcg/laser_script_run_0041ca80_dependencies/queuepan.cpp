// Compiler context only: the real sound queue pan request 0x0043DD10, so the
// pass sees the callee's body and gives its callers the private register
// convention (queue in ESI, sound id in EBX, pan on the stack). Never selected
// from this cluster.
#define code_seg(name) code_seg(".text$0043dd10_fn")
#include "../../../../src/core/sound/sound_queue_pan_0043dd10.cpp"
