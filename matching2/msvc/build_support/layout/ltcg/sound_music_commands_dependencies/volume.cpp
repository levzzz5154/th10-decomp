// Compiler context only: the real volume setter 0x0044D4E0, so the pass sees the
// callee's body and gives the handler its private register convention. The
// macro moves the body into a section that sorts at its retail address here.
// Never selected from this cluster.
#define code_seg(name) code_seg(".text$a03v")
#include "../../../../src/core/zwave/platform_set_operation_deadline.cpp"
