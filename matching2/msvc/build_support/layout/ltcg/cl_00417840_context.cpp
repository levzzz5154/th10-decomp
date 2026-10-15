// Compiler context only; never selected as recovered game code.
#include <string.h>
#include "../../../src/unreferenced/unassigned_00417840.cpp"
extern "C" void __cdecl crt_free_startup(void* block);

#pragma code_seg(".text$03anchor")
__declspec(noinline) char __fastcall GameConfig_00417840_InitDefaults(
        int reserved, GameConfig_00417840* config) {
    memset(config, 0, 0x34);
    *(int*)(config->bytes + 0x00) = 0x100003;
    *(unsigned short*)(config->bytes + 0x16) = 0x258;
    *(unsigned short*)(config->bytes + 0x18) = 0x258;
    *(int*)(config->bytes + 0x30) |= 0x100;
    config->bytes[0x10] = 2;
    config->bytes[0x1f] = 2;
    config->bytes[0x21] = 0x50;
    crt_free_startup(config);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ResetContext_00417840(Object_00417840** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        Object_00417840* one = items[i];
        one->pad_000[0] = (unsigned char)i;
        total += (int)one->Reset();
        total += one->flags_20;
    }
    return total;
}
#pragma code_seg()
