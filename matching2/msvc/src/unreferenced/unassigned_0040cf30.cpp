#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040cf30 { int words[0x77]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040cf30* __fastcall
Init_0040cf30(void* unused, Rec_0040cf30* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec_0040cf30));
    return obj;
}
#pragma code_seg()
