// 0x0041c2f0: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject_0041c2f0;
extern "C" void __stdcall asm_LaserManager_Destroy_0041c1c0(
    void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* ScoreExtendedObject_Destroy_DeletingDestructor_0041c2f0(OwnedObject_0041c2f0* object, unsigned int flags);
#pragma code_seg(".text$01delete0041c2f0")
void* ScoreExtendedObject_Destroy_DeletingDestructor_0041c2f0(OwnedObject_0041c2f0* object, unsigned int flags) {
    asm_LaserManager_Destroy_0041c1c0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
