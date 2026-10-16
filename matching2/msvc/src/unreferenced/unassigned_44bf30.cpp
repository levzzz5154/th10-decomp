// 0x0044BF30..0x0044BF3D: hand a slot over to a replacement.
//
// Both arguments arrive in registers (the slot pointer in ECX, the replacement
// in EDX) and the previous occupant gives up one reference before the slot is
// overwritten.
struct UnassignedNode_0044bf30 {
    unsigned char pad_00[4];
    int references;  // +0x0004
};

struct UnassignedSlot_0044bf30 {
    unsigned char pad_00[0x0C];
    UnassignedNode_0044bf30* occupant;  // +0x000C
};

extern "C" void __fastcall UnassignedSlot_Replace(UnassignedSlot_0044bf30* slot,
                                                  UnassignedNode_0044bf30* replacement) {
    UnassignedNode_0044bf30* previous = slot->occupant;
    if (previous != 0)
        --previous->references;
    slot->occupant = replacement;
}
