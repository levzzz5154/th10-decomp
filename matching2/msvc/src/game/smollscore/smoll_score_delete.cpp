// 0x0042B6D0: delete the score popups (SmollScore) (destructor, then free). Retail keeps the pointer in ESI.

struct SmollScore;
extern "C" void asm_FUN_0042b570_0042b570(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void SmollScore_Delete(SmollScore* object);
#pragma code_seg(".text$01destroy0042b6d0")
void SmollScore_Delete(SmollScore* object) {
    if (object) {
        asm_FUN_0042b570_0042b570(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
