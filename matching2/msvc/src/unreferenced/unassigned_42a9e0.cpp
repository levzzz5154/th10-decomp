// 0x0042A9E0: zero the 0x1C4-byte record the caller passes in EDX and return it.
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec13 { unsigned char pad_000[0x1C4]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec13* __fastcall
Init12(void* unused, Rec13* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec13));
    return obj;
}
#pragma code_seg()
