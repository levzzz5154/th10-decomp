// 0x0042CDB0: destroy and free an owned object. Retail keeps the pointer in ESI.

struct Title;
extern "C" void asm_Title_Destroy(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void Title_Delete(Title* object);
#pragma code_seg(".text$01destroy0042cdb0")
void Title_Delete(Title* object) {
    if (object) {
        asm_Title_Destroy(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
