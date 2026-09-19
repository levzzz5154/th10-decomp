// 0x004148c0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_004148c0;
extern "C" void asm_FUN_004145f0_004145f0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* ReleaseComposite_DeletingDestructor_004148c0(OwnedObject_004148c0* object, unsigned int flags);
#pragma code_seg(".text$01delete004148c0")
void* ReleaseComposite_DeletingDestructor_004148c0(OwnedObject_004148c0* object, unsigned int flags) {
    asm_FUN_004145f0_004145f0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
