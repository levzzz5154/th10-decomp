// 0x0040CF10. Slot at offset 0x44: the assigned value is both stored and
// returned.
struct RecoverySlot {
    int reserved[17];
    int value;
    int SetValue(int new_value);
};

int RecoverySlot::SetValue(int new_value) {
    value = new_value;
    return new_value;
}
