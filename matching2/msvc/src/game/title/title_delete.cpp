// 0x0042CDB0: destroy and free an owned object. Retail keeps the pointer in ESI.

struct Title;
extern "C" void Title_DestroyState(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void Title_Delete(Title* object);
#pragma code_seg(".text$01destroy0042cdb0")
void Title_Delete(Title* object) {
    if (object) {
        Title_DestroyState(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
