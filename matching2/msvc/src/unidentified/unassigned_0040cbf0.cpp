#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040cbf0 { unsigned char pad_000[0x4]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __fastcall
Init_0040cbf0(void* unused, Rec_0040cbf0* obj) {
    (void)unused;
    memset((char*)obj + 0x4, 0, 0x30);
}
#pragma code_seg()
