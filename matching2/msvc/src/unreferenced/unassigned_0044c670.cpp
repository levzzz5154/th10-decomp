// 0x0044C670..0x0044C6A3: initialise the nine 16-bit slot indices.
//
// Slots 0..3 take their own index and the four reserved slots take -1; the
// function hands the object back in EAX, so it returns this.
struct UnassignedSlots_0044c670 {
    unsigned char pad_00[0x58];
    short slots[9];  // +0x0058

    __declspec(noinline) UnassignedSlots_0044c670* Reset();
};

UnassignedSlots_0044c670* UnassignedSlots_0044c670::Reset() {
    slots[0] = 0;
    slots[1] = 1;
    slots[2] = 2;
    slots[3] = 3;
    slots[4] = -1;
    slots[5] = -1;
    slots[6] = -1;
    slots[7] = -1;
    slots[8] = 4;
    return this;
}
