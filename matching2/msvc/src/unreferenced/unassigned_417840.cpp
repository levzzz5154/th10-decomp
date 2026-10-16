#include <string.h>
extern "C" void __cdecl crt_free_startup(void* block);

#pragma pack(push, 1)
struct GameConfig2 { unsigned char bytes[0x34]; };
#pragma pack(pop)
char __fastcall GameConfig_00417840_InitDefaults(int reserved, GameConfig2* config);

struct Object4 {
    unsigned char pad_000[0x20];
    unsigned int flags_20;
    GameConfig2 config_24;
    unsigned char pad_058[8];
    __declspec(noinline) Object4* Reset();
};

#pragma code_seg(".text$01reset")
Object4* Object4::Reset() {
    flags_20 &= ~1u;
    GameConfig_00417840_InitDefaults(0, &config_24);
    memset(this, 0, 0x60);
    return this;
}
#pragma code_seg()
