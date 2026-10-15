// Context for the 0x004067D0 recovery: the script starter 0x00404F30 with the
// compiled script loader it calls, as in its own cluster
// (build_support/layout/ltcg/entity_start_script_00404f30_context.cpp). The loader takes the
// index in EBX, so the starter takes it in EAX and the spawner computes it
// there. The sections are moved past the spawner's jump tables.
#define code_seg(name) code_seg(".text$zz_00404f30")
#include "../../../../../src/core/sprtanim/animation_object_load_script_0043e710.cpp"

// 0x00401DE0 takes the entity in EDX; the stand-in hides its register kill set
// behind an external call, as in the starter's cluster.
extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);

#pragma code_seg(".text$00h_init")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()

#include "../../../../../src/game/background/entity_start_script_00404f30.cpp"
#undef code_seg
