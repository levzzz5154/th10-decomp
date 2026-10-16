// 0x0041fd50: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject8;
extern "C" void Loading_Release(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor4(OwnedObject8* object, unsigned int flags);
#pragma code_seg(".text$01delete0041fd50")
void* DestroyOwned_DeletingDestructor4(OwnedObject8* object, unsigned int flags) {
    Loading_Release(object);
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
