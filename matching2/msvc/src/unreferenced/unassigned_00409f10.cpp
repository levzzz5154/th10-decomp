#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_00409f10 { unsigned char pad_000[0x14]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __fastcall
Init_00409f10(void* unused, Rec_00409f10* obj) {
    (void)unused;
    memset((char*)obj + 0x14, 0, 0x21CEA0);
}
#pragma code_seg()
