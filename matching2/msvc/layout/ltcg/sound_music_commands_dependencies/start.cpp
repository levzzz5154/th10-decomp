// Compiler context only: the real stream start 0x0044D440, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a03s")
#include "../../../src/core/zwave/sound_stream_start.cpp"
