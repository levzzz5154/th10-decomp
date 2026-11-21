// 0x00424620: store one value into each of the four 0x98-byte slots at +0x332C.
struct Slot4Rec {
    int value;
    unsigned char reserved_004[0x98 - 0x04];
};
struct SlotSet {
    unsigned char reserved_000[0x332C];
    Slot4Rec slots[4];          // +0x332C
    __declspec(noinline) void SetAll(int value);
};

#pragma code_seg(".text$01accessor")
void SlotSet::SetAll(int value) {
    for (int i = 0; i < 4; ++i) {
        slots[i].value = value;
    }
}
#pragma code_seg()
