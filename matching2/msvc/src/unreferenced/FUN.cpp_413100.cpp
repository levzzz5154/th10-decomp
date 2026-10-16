// 0x00413100. Slot at offset 0 of a small input-state record: the assigned
// value is both stored and returned.
struct RecoverySlot2 {
    int value;
    int SetValue(int new_value);
};

int RecoverySlot2::SetValue(int new_value) {
    value = new_value;
    return new_value;
}
