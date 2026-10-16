#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec4 { int words[0x10]; };
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec4* __fastcall
Init4(void* unused, Rec4* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec4));
    return obj;
}
#pragma code_seg()
