// 0x004148c0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject;
extern "C" void Front_DestroyState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* ReleaseComposite_DeletingDestructor(OwnedObject* object, unsigned int flags);
#pragma code_seg(".text$01delete004148c0")
void* ReleaseComposite_DeletingDestructor(OwnedObject* object, unsigned int flags) {
    Front_DestroyState(object);
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
