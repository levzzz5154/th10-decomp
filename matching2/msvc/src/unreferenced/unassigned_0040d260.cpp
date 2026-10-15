#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040d260 {
    unsigned int flags_000;
    unsigned char pad_004[0x50 - 0x04];
    unsigned int field_050;
    unsigned char pad_054[0x68 - 0x54];
};
extern "C" Rec_0040d260* g_enemy_ctrl;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040d260* __fastcall
Init_0040d260(void* unused, Rec_0040d260* obj) {
    (void)unused;
    unsigned int* flag = (unsigned int*)((char*)obj + 0x50);
    *flag &= ~1u;
    memset(obj, 0, sizeof(Rec_0040d260));
    obj->flags_000 |= 2u;
    g_enemy_ctrl = obj;
    return obj;
}
#pragma code_seg()
