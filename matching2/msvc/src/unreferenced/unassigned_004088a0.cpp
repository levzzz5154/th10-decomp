
struct Slot_004088a0 { unsigned char bytes[8]; };

__declspec(noinline) int SlotIndex_004088a0(int index, int base);

#pragma code_seg(".text$01index")
__declspec(noinline) int SlotIndex_004088a0(int index, int base) {
    return index * 0x437C + base + 8;
}
#pragma code_seg()
