// 0x0041fd70: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject9;
extern "C" void Loading_Release(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void ReleaseOwned4(OwnedObject9* object);
#pragma code_seg(".text$01release0041fd70")
void ReleaseOwned4(OwnedObject9* object) {
    if (object) {
        Loading_Release(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
