#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec6 {
    unsigned char pad_000[0x34];
    float field_034;
    float field_038;
};
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) void __fastcall
Init6(void* unused, Rec6* obj) {
    (void)unused;
    memset(obj, 0, sizeof(Rec6));
    obj->field_038 = 32.0f;
    obj->field_034 = 32.0f;
}
#pragma code_seg()
