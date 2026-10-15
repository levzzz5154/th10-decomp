// 0x004148E0: delete the item manager (destructor, then free). Retail keeps the pointer in ESI.

struct ItemManager;
extern "C" void asm_FUN_004145f0_004145f0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ItemManager_Delete(ItemManager* object);
#pragma code_seg(".text$01destroy004148e0")
void ItemManager_Delete(ItemManager* object) {
    if (object) {
        asm_FUN_004145f0_004145f0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
