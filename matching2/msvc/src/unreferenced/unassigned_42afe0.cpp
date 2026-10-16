// 0x0042AFE0: scalar deleting destructor. Retail keeps the object in ESI and
// the delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.
struct OwnedObject11;
extern "C" void __cdecl crt_free(void* memory);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor6(OwnedObject11* object, unsigned int flags);
#pragma code_seg(".text$01delete0042afe0")
void* DestroyOwned_DeletingDestructor6(OwnedObject11* object, unsigned int flags) {
    void** fields = (void**)object;
    if (fields[0]) { crt_free(fields[0]); fields[0] = 0; }
    if (fields[1]) { crt_free(fields[1]); fields[1] = 0; }
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
