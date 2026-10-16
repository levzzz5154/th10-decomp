// 0x004190e0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject3;
extern "C" void __stdcall asm_FUN_00418ee0_00418ee0(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor2(OwnedObject3* object, unsigned int flags);
#pragma code_seg(".text$01delete004190e0")
void* DestroyOwned_DeletingDestructor2(OwnedObject3* object, unsigned int flags) {
    asm_FUN_00418ee0_00418ee0(object);
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
