// 0x00413790: enable `count` records of the animation manager's fixed nine-record
// table and disable the rest.
struct AnimationRecord {
    unsigned int flags_0000;             // +0x000
    unsigned char pad_0004[0x3AC - 4];
};

struct AnimationManager4 {
    unsigned char pad_0000[0x4CDC];
    AnimationRecord records_4cdc[9];
    __declspec(noinline) void SetActiveCount(int count);
};

#pragma code_seg(".text$01accessor")
void AnimationManager4::SetActiveCount(int count) {
    int index = 0;
    for (; index < count; ++index)
        records_4cdc[index].flags_0000 |= 2;
    if (index >= 9)
        return;
    for (; index < 9; ++index)
        records_4cdc[index].flags_0000 &= ~2u;
}
#pragma code_seg()
