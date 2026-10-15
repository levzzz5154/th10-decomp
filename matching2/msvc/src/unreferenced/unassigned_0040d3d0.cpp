#include <stddef.h>
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);

struct Rec_0040d3d0 {
    void* vtable_000;
    unsigned char pad_004[0x1090 - 0x04];
    unsigned int tail_1090;
    unsigned int tail_1094;
};
extern "C" unsigned char g_enemy_ctrl_vtable;
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) Rec_0040d3d0* __fastcall
Init_0040d3d0(void* unused, Rec_0040d3d0* obj) {
    (void)unused;
    unsigned int* tail = (unsigned int*)((char*)obj + 0x1090);
    tail[0] = 0;
    tail[1] = 0;
    memset(obj, 0, sizeof(Rec_0040d3d0));
    obj->vtable_000 = &g_enemy_ctrl_vtable;
    return obj;
}
#pragma code_seg()
