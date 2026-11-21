// 0x004148E0: delete the HUD (destructor, then free). Retail keeps the pointer in ESI.

struct Front;
extern "C" void Front_DestroyState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void Front_Delete(Front* object);
#pragma code_seg(".text$01destroy004148e0")
void Front_Delete(Front* object) {
    if (object) {
        Front_DestroyState(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
