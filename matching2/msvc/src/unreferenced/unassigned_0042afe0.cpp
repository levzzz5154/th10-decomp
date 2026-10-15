// 0x0042AFE0: scalar deleting destructor. Retail keeps the object in ESI and
// the delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.
struct OwnedObject_0042afe0;
extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0042afe0(OwnedObject_0042afe0* object, unsigned int flags);
#pragma code_seg(".text$01delete0042afe0")
void* DestroyOwned_DeletingDestructor_0042afe0(OwnedObject_0042afe0* object, unsigned int flags) {
    void** fields = (void**)object;
    if (fields[0]) { entry_free_00452422(fields[0]); fields[0] = 0; }
    if (fields[1]) { entry_free_00452422(fields[1]); fields[1] = 0; }
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
