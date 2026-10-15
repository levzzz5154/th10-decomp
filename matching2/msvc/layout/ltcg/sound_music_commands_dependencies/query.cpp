// Compiler context only: the real buffer rewind 0x0044D600, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a05q")
#include "../../../src/core/zwave/platform_query_interfaces_0044d600.cpp"
