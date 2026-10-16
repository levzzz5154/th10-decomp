// Real body of the resource request queue 0x0043E460 (queue in EAX, name in
// EDX), placed at its retail address.
#define code_seg(name) code_seg(".text$0043e460_fn")
#include "../../../../src/core/sprtanim/animation_manager_register_resource.cpp"
#undef code_seg
#pragma code_seg()
