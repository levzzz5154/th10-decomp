// Compiler context only: the real stream restart 0x0044DAD0, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a06restart")
#include "../../../src/core/zwave/streamer_restart_retail_0044dad0.cpp"
