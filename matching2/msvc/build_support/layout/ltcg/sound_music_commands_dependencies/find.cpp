// Compiler context only: the real free buffer lookup 0x0044D370, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a03h")
#include "../../../../src/core/zwave/platform_find_available_0044d370.cpp"
