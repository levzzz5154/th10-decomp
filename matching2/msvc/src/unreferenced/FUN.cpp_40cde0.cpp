// 0x0040CDE0: mark the enemy-state record mirrored.
// The object pointer arrives in EAX, which only a native LTCG link
// chooses, so this region is compiled as a cluster
// (build_support/layout/ltcg/enemy_state_set_mirrored.json).
// The adjacent load at 0x0040CDB0 reads the enemy pointer at +0x3504;
// this byte at +0x3508 is the mirror flag (see EnemyState3
// in src/game/enemy/enemy_lifecycle.cpp).

struct EnemyState2 {
    unsigned char pad_000[0x3504];
    void* enemy; // +0x3504
    unsigned char mirror; // +0x3508
    __declspec(noinline) void SetMirrored();
};
// The compiler tails the single trailing byte to a dword boundary.
typedef char EnemyState_0040cde0_size_must_fit[sizeof(EnemyState2) == 0x350C ? 1 : -1];

#pragma code_seg(".text$01mirror")
void EnemyState2::SetMirrored() {
    mirror = 1;
}
#pragma code_seg()
