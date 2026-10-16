#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec8 { int words[0x77]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec8* __fastcall
Init8(void* unused, Rec8* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec8));
    return obj;
}
#pragma code_seg()
