// 0x00413140. Slot at offset 0x24: the assigned value is both stored and
// returned.
struct RecoverySlot_00413140 {
    int reserved[9];
    int value;
    int SetValue(int new_value);
};

int RecoverySlot_00413140::SetValue(int new_value) {
    value = new_value;
    return new_value;
}
