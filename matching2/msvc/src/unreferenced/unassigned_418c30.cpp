#pragma pack(push, 1)
struct GameConfig3 {
    unsigned char bytes[0x34];
    __declspec(noinline) GameConfig3* Reset();
};
#pragma pack(pop)
char __fastcall InitConfigAnchor(int reserved, GameConfig3* config);
#pragma code_seg(".text$01reset")
GameConfig3* GameConfig3::Reset() {
    InitConfigAnchor(0, this);
    return this;
}
#pragma code_seg()
