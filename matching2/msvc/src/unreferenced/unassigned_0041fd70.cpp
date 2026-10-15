// 0x0041fd70: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_0041fd70;
extern "C" void Loading_Release(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_0041fd70(OwnedObject_0041fd70* object);
#pragma code_seg(".text$01release0041fd70")
void ReleaseOwned_0041fd70(OwnedObject_0041fd70* object) {
    if (object) {
        Loading_Release(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
