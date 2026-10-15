// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/game/enemy_manager_delete.cpp"

// As 0x0040D530 reads it: a slot word at +0x08.
struct AnchorEntity_0040d710 {
    unsigned char reserved_000[0x08];
    unsigned int slot;
};

// 0x0040D530's body.  It is compiled only so the whole-program pass can hand it
// the object in EAX: its only caller is the modelled deleting destructor and no
// declaration names that register.  The layout's gaps place this section at the
// retail address, so the destructor's call bakes retail's own displacement.
// None of these bytes are selected as recovered code.
#pragma code_seg(".text$01anchor")
extern "C" __declspec(noinline) void __cdecl asm_FUN_0040d530_0040d530(void* object) {
    AnchorEntity_0040d710* entity = (AnchorEntity_0040d710*)object;
    entity->slot = 0;
    // The real teardown calls out, so it preserves none of EAX/ECX/EDX.
    entry_free_004524a1(0);
}
#pragma code_seg()

#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_0040d710(EnemyManager** items, int count) {
    int freed = 0;
    while (count--) {
        EnemyManager_Delete(*items);
        freed += EnemyManager_DeletingDestructor(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
