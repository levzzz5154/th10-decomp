// 0x0042A9F0: construct a zeroed configuration holder. The embedded
// configuration is filled with its defaults first and then cleared again by
// the holder's own memset, exactly as the retail constructor orders it.
// Native LTCG passes the holder in ESI and returns it in EAX.
#include <string.h>

struct GameConfig;
__declspec(noinline) char __fastcall GameConfig_InitializeDefaults(int unused, GameConfig* config);

struct GameConfigHolder_0042a9f0 {
    unsigned char reserved_00[0x14];
    unsigned char config[0x34];             // +0x14: GameConfig
    unsigned char reserved_48[0x64 - 0x48];

    __declspec(noinline) GameConfigHolder_0042a9f0* Construct();
};

#pragma code_seg(".text$00xfn")
GameConfigHolder_0042a9f0* GameConfigHolder_0042a9f0::Construct() {
    GameConfig_InitializeDefaults(0, reinterpret_cast<GameConfig*>(config));
    memset(this, 0, sizeof(*this));
    return this;
}
#pragma code_seg()
