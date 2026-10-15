// Compiler context only: the real buffer recreation 0x0044CF20, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a03d")
#include "../../../../src/core/zwave/sound_stream_recreate_buffers_0044cf20.cpp"
