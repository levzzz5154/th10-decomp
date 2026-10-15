// Compiler context only: the real stream record selector 0x0044DCA0, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a07select")
#include "../../../../src/core/zwave/platform_select_stream_record_0044dca0.cpp"
