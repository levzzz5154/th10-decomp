// Semantic model for the four encoded integer slots selected at 0x00412300.
// The surrounding disassembly establishes the ECX receiver, one stack
// selector, EAX pointer result, and callee cleanup of that selector.
struct EclIntegerSlots_00412300 {
    unsigned char padding_0000[0x1138];
    int slot_1138;
    int slot_113c;
    int slot_1140;
    int slot_1144;

    __declspec(noinline) int* ResolveSlot(int encoded_slot);
};

#pragma code_seg(".text$01accessor")
int* EclIntegerSlots_00412300::ResolveSlot(int encoded_slot) {
    const unsigned slot = static_cast<unsigned>(encoded_slot) + 0x2701u;
    switch (slot) {
    case 0:
        return &slot_1138;
    case 1:
        return &slot_113c;
    case 2:
        return &slot_1140;
    case 3:
        return &slot_1144;
    default:
        return 0;
    }
}
#pragma code_seg()
