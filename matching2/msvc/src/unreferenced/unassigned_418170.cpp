// 0x00418170: scalar deleting destructor. Retail keeps the object in ESI and the
// delete flag in the first stack argument, so this body is a cluster whose
// synthetic caller walks an array of the objects.

struct OwnedObject2;
extern "C" void Game_DestroyState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor(OwnedObject2* object, unsigned int flags);
#pragma code_seg(".text$01delete00418170")
void* DestroyOwned_DeletingDestructor(OwnedObject2* object, unsigned int flags) {
    Game_DestroyState(object);
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
