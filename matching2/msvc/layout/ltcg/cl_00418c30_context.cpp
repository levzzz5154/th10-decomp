// Compiler context only; never selected as recovered game code.
#include <string.h>
#include "../../src/unreferenced/unassigned_00418c30.cpp"

extern "C" void __cdecl entry_free_004524a1(void* block);

#pragma code_seg(".text$03anchor")
__declspec(noinline) char __fastcall InitConfigAnchor_00418c40(int reserved, GameConfig_00418c30* config) {
    memset(config, 0, 0x34);
    *(int*)(config->bytes + 0x00) = 0x100003;
    *(unsigned short*)(config->bytes + 0x16) = 0x258;
    *(unsigned short*)(config->bytes + 0x18) = 0x258;
    *(int*)(config->bytes + 0x30) |= 0x100;
    config->bytes[0x10] = 2;
    config->bytes[0x21] = 0x50;
    entry_free_004524a1(config);
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall ResetContext_00418c30(GameConfig_00418c30** items, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        GameConfig_00418c30* one = items[i];
        one->bytes[0] = (unsigned char)i;
        total += (int)one->Reset();
        total += one->bytes[2];
    }
    return total;
}
#pragma code_seg()
