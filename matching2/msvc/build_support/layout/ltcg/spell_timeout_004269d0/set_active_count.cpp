// Complete compiler context for the count helper at 0x00413790.
// Uses the same complete implementation as src/game/fps/animation_set_active_count_00413790.cpp.
#pragma code_seg(".text$00413790_fn")
void AnimationManager_00413790::SetActiveCount(int count) {
    int index = 0;
    for (; index < count; ++index)
        records_4cdc[index].flags_0000 |= 2;
    if (index >= 9)
        return;
    for (; index < 9; ++index)
        records_4cdc[index].flags_0000 &= ~2u;
}
#pragma code_seg()
