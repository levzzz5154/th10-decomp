// Real body of the sprite configuration 0x0043E5A0 the label refresh calls,
// placed at its retail address.
#define code_seg(name) code_seg(".text$0043e5a0_fn")
#include "../../../../src/core/sprtanim/animation_object_configure_from_resource.cpp"
#undef code_seg
#pragma code_seg()
