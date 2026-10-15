// 0x004055A0: the bomb's out-of-line constructor; nothing calls it.
#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_004055a0 {
    unsigned int flags_000;
    unsigned char pad_004[0x24 - 0x04];
    unsigned int field_024;
    unsigned char pad_028[0x48 - 0x28];
};
extern "C" Rec_004055a0* g_bomb;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_004055a0* __fastcall
Bomb_Construct(void* unused, Rec_004055a0* obj) {
    (void)unused;
    unsigned int* flag = (unsigned int*)((char*)obj + 0x24);
    *flag &= ~1u;
    memset(obj, 0, sizeof(Rec_004055a0));
    obj->flags_000 |= 2u;
    g_bomb = obj;
    return obj;
}
#pragma code_seg()
