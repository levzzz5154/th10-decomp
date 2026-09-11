// 0x00412F10..0x00412F19: FUN_00412f10
// Stores the sole argument in the object field at +0x10.
struct Object_00412f10 {
    unsigned char reserved_000[0x10];
    int field_10;                        // +0x10
    void SetField(int value);
};

void Object_00412f10::SetField(int value) {
    field_10 = value;
}
