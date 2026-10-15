// 0x00406140 (18 bytes): delete the bullet manager.
//
// retail:
//   test esi,esi / je done
//   push esi / call 0x00405F70      ; ~BulletManager, __stdcall
//   push esi / call 0x004524A1      ; operator delete, __cdecl
//   pop ecx / done: ret
// The object pointer arrives in ESI because it stays live across both calls,
// which the link-time register allocator satisfies with a preserved register.
// The synthetic caller below is compiled in the same /LTCG cluster so the
// allocator makes the same choice.

struct BulletManager;

extern "C" __stdcall void asm_ItemManager_DestroyRetail_00405f70(BulletManager* item);
void __cdecl operator delete(void* block);

#pragma code_seg(".text$01release")
__declspec(noinline) void BulletManager_Delete(BulletManager* item) {
    if (item) {
        asm_ItemManager_DestroyRetail_00405f70(item);
        operator delete(item);
    }
}
#pragma code_seg()
