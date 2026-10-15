// 0x0040CDC0: conditional enemy-slot setter.
// The object arrives in EAX and the value on the stack (__usercall), so the
// region compiles as a native-LTCG cluster
// (build_support/layout/ltcg/enemy_slot_conditional_set_0040cdc0.json). The object layout
// matches EnemyState_0040cde0: enemy pointer at +0x3504, mirror flag at
// +0x3508 (see src/unreferenced/FUN_0040cde0_0040cde0.cpp).
struct EnemySlotWriter_0040cdc0 {
    unsigned char pad_000[0x3504];
    void* enemy;    // +0x3504
    unsigned char mirror; // +0x3508
    __declspec(noinline) void SetEnemyIfUnmirrored(void* candidate);
};
#pragma code_seg(".text$01slot")
void EnemySlotWriter_0040cdc0::SetEnemyIfUnmirrored(void* candidate) {
    if (!mirror) enemy = candidate;
}
#pragma code_seg()
