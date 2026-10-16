// 0x00449A30: zero the 0x130-byte record the caller passes in EDX and return it.
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec14 { unsigned char pad_000[0x130]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec14* __fastcall
Init15(void* unused, Rec14* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec14));
    return obj;
}
#pragma code_seg()
