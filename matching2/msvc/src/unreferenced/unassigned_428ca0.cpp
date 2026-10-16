// 0x00428CA0..0x00428CD3 (52 bytes): cancel every slot that carries an id.
//
// Retail clears the current-slot pair at +0x3504/+0x3508 when it holds the
// cancelled id, then walks the 0x80 records of the array at +0x4E8 (stride
// 0x5C) and clears the id of each match.  The record arrives in EAX and the id
// in EDX, so the two are register arguments.

struct Slot_00428ca0 {                     // stride 0x5C
    int id;                                // +0x00
    unsigned char unknown_04[0x58];
};

struct SlotTable3 {
    unsigned char unknown_0000[0x4E8];
    Slot_00428ca0 slots[0x80];             // +0x4E8 .. +0x32E8
    unsigned char unknown_32e8[0x21C];     // +0x32E8 .. +0x3504
    int current_id;                        // +0x3504
    unsigned char current_flag;            // +0x3508

    __declspec(noinline) void Cancel(int id);
};

#pragma code_seg(".text$01cancel")
void SlotTable3::Cancel(int id) {
    if (current_id == id) {
        current_id = 0;
        current_flag = 0;
    }
    Slot_00428ca0* slot = slots;
    for (int index = 0; index < 0x80; ++index) {
        if (slot->id == id) {
            slot->id = 0;
        }
        ++slot;
    }
}
#pragma code_seg()
