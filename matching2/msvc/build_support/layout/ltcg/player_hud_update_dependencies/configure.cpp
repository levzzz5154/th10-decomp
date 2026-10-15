// Compiler context only: the real sprite configure 0x0043E5A0, so the pass sees the callee's body and
// gives the update its private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$a02configure")
#include "../../../../src/core/sprtanim/animation_object_configure_from_resource_0043e5a0.cpp"
