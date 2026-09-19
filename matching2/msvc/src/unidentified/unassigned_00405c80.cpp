#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_00405c80 {
    unsigned char pad_000[0x204];
    int field_204;
    unsigned char pad_208[0x210 - 0x208];
};
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_00405c80* __fastcall
Init_00405c80(Rec_00405c80* obj) {
    memset(obj, 0, sizeof(Rec_00405c80));
    obj->field_204 = -1;
    return obj;
}
#pragma code_seg()
