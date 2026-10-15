// 0x00418170: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_00418170;
extern "C" void asm_FUN_00417c80_00417c80(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_00418170(OwnedObject_00418170* object, unsigned int flags);
#pragma code_seg(".text$01delete00418170")
void* DestroyOwned_DeletingDestructor_00418170(OwnedObject_00418170* object, unsigned int flags) {
    asm_FUN_00417c80_00417c80(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
