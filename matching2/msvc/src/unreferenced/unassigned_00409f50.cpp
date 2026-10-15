#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_00409f50 { int words[0x10]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_00409f50* __fastcall
Init_00409f50(void* unused, Rec_00409f50* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec_00409f50));
    return obj;
}
#pragma code_seg()
