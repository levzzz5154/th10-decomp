// 0x0041AFB0: delete the item manager (destructor, then free). Retail keeps the pointer in ESI.

struct ItemManager;
extern "C" void __stdcall ItemManager_Destroy_0041adf0(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void ItemManager_Delete(ItemManager* object);
#pragma code_seg(".text$01destroy0041afb0")
void ItemManager_Delete(ItemManager* object) {
    if (object) {
        ItemManager_Destroy_0041adf0(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
