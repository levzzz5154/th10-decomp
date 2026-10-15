#include <string.h>
extern "C" void __cdecl crt_free_startup(void* block);

#pragma pack(push, 1)
struct GameConfig_00417840 { unsigned char bytes[0x34]; };
#pragma pack(pop)
char __fastcall GameConfig_00417840_InitDefaults(int reserved, GameConfig_00417840* config);

struct Object_00417840 {
    unsigned char pad_000[0x20];
    unsigned int flags_20;
    GameConfig_00417840 config_24;
    unsigned char pad_058[8];
    __declspec(noinline) Object_00417840* Reset();
};

#pragma code_seg(".text$01reset")
Object_00417840* Object_00417840::Reset() {
    flags_20 &= ~1u;
    GameConfig_00417840_InitDefaults(0, &config_24);
    memset(this, 0, 0x60);
    return this;
}
#pragma code_seg()
