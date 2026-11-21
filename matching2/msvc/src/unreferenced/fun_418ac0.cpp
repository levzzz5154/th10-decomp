// 0x00418AC0: write the pair of defaults and return the object in EAX.
// The object pointer arrives in EAX, which only a native LTCG link chooses,
// so this region is compiled as a cluster (state_reset_pair.json).

struct GameAppStateReset {
    unsigned char pad_000[0xC];
    int field_00C; // +0x0C
    int field_010; // +0x10
    __declspec(noinline) void ResetPair();
};
typedef char GameAppStateReset_00418ac0_size_must_fit[sizeof(GameAppStateReset) == 0x14 ? 1 : -1];

#pragma code_seg(".text$01resetpair00418ac0")
void GameAppStateReset::ResetPair() {
    field_010 = 0;
    field_00C = 1;
}
#pragma code_seg()
