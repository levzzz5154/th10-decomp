// 0x0041AF90: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster.

struct OwnedObject_0041af90;
extern "C" void __stdcall ItemManager_Destroy_0041adf0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0041af90(OwnedObject_0041af90* object, unsigned int flags);
#pragma code_seg(".text$01delete0041af90")
void* DestroyOwned_DeletingDestructor_0041af90(OwnedObject_0041af90* object, unsigned int flags) {
    ItemManager_Destroy_0041adf0(object);
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
