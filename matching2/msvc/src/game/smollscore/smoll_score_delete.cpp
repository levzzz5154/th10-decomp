// 0x0042B6D0: delete the score popups (SmollScore) (destructor, then free). Retail keeps the pointer in ESI.

struct SmollScore;
extern "C" void SmollScore_DestroyState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void SmollScore_Delete(SmollScore* object);
#pragma code_seg(".text$01destroy0042b6d0")
void SmollScore_Delete(SmollScore* object) {
    if (object) {
        SmollScore_DestroyState(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
