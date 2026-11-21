// Compiler context only: the real sound queue request 0x0043DC90, so the pass
// sees the callee's body and gives its callers the private register convention
// (queue in ECX, sound id in EDI, request on the stack). Never selected from
// this cluster.
#define TH10_SOUND_QUEUE_SECTION ".text$0043dc90_fn"
#include "../../../../src/core/sound/sound_queue.cpp"
