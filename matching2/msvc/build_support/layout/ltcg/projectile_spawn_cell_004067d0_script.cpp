// Compiler context only; this translation unit is never selected as recovered
// game code. It supplies the 0x004067D0 model's script-starter callees at
// their retail addresses: the compiled script loader 0x0043E710, the
// 0x00401DE0 initializer stand-in the starter calls, and the starter
// 0x00404F30 itself.
#define code_seg(name) code_seg(".text$0043e710_fn")
#include "../../../src/core/sprtanim/animation_object_load_script.cpp"
#undef code_seg

extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);

// 0x00401DE0's initializer tail is not part of this recovery; the model only
// needs a body with the retail call convention to keep the starter's call.
#pragma code_seg(".text$00401de0_fn")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()

#define code_seg(name) code_seg(".text$00404f30_fn")
#include "../../../src/game/background/entity_start_script.cpp"
#undef code_seg
