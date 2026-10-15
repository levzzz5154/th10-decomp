// 0x0040D710..0x0040D72C (28 bytes): the enemy manager's scalar deleting destructor.
//
// Retail copies the object from ESI to EAX before the cleanup at 0x0040D530 --
// that callee reads its object from EAX -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1 and
// returns it in EAX.  The object stays in ESI across the call, a receiver no
// C++ declaration names, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_delete_0040d710.json; the callee is compiled into the same link as an
// ABI anchor so the pass hands it the object in EAX.

extern "C" void __cdecl asm_FUN_0040d530_0040d530(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct EnemyManager {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* EnemyManager_DeletingDestructor(EnemyManager* object, int flags);

#pragma code_seg(".text$03del")
void* EnemyManager_DeletingDestructor(EnemyManager* object, int flags) {
    asm_FUN_0040d530_0040d530(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()

// 0x0040D730..0x0040D742 (19 bytes): destroy and free the object when there is
// one -- a `delete` of the same class with the null check kept. The object is
// again in ESI.
__declspec(noinline) void EnemyManager_Delete(EnemyManager* object);

#pragma code_seg(".text$04m_delete")
void EnemyManager_Delete(EnemyManager* object) {
    if (object != 0) {
        asm_FUN_0040d530_0040d530(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
