// 0x00419100: release an owned object and free it. Retail keeps the object in ESI.

struct OwnedObject_00419100;
extern "C" void __stdcall asm_FUN_00418ee0_00418ee0(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void ReleaseOwned_00419100(OwnedObject_00419100* object);
#pragma code_seg(".text$01release00419100")
void ReleaseOwned_00419100(OwnedObject_00419100* object) {
    if (object) {
        asm_FUN_00418ee0_00418ee0(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
