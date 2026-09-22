// The paired animation slot setter is intentionally kept as a separate
// contribution so native LTCG preserves the retail entry and reload shape.
struct AnimationSlot_004177e0 {
    unsigned char reserved_000[4];
    unsigned int flags;
};

struct AnimationSlots_004177e0 {
    unsigned char reserved_000[8];
    AnimationSlot_004177e0* first;
    AnimationSlot_004177e0* second;
    __declspec(noinline) void SetFlags();
};

#pragma code_seg(".text$03settere0")
void AnimationSlots_004177e0::SetFlags() {
    first->flags |= 2;
    second->flags |= 2;
}
#pragma code_seg()
