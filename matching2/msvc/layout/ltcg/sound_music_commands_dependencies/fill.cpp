// Compiler context only: the real buffer fill 0x0044D110, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a03f")
#include "../../../src/core/zwave/sound_stream_fill_model.cpp"
