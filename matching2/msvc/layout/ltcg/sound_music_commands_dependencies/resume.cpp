// Compiler context only: the real stream resume 0x0044D5D0, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a05invoke")
#include "../../../src/core/zwave/platform_invoke_configured_0044d5d0.cpp"
