// 0x0041AFB0: destroy and free an owned object. Retail keeps the pointer in ESI.

struct OwnedObject_0041afb0;
extern "C" void __stdcall BulletManager_Destroy_0041adf0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void DestroyOwned_0041afb0(OwnedObject_0041afb0* object);
#pragma code_seg(".text$01destroy0041afb0")
void DestroyOwned_0041afb0(OwnedObject_0041afb0* object) {
    if (object) {
        BulletManager_Destroy_0041adf0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
