#pragma pack(push, 1)
struct GameConfig_00418c30 {
    unsigned char bytes[0x34];
    __declspec(noinline) GameConfig_00418c30* Reset();
};
#pragma pack(pop)
char __fastcall InitConfigAnchor_00418c40(int reserved, GameConfig_00418c30* config);
#pragma code_seg(".text$01reset")
GameConfig_00418c30* GameConfig_00418c30::Reset() {
    InitConfigAnchor_00418c40(0, this);
    return this;
}
#pragma code_seg()
