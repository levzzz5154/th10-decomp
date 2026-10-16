// 0x0041AF90: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster.

struct OwnedObject5;
extern "C" void __stdcall ItemManager_Destroy(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor3(OwnedObject5* object, unsigned int flags);
#pragma code_seg(".text$01delete0041af90")
void* DestroyOwned_DeletingDestructor3(OwnedObject5* object, unsigned int flags) {
    ItemManager_Destroy(object);
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
