// 0x00412F10..0x00412F19: FUN10
// Stores the sole argument in the object field at +0x10.
struct Object3 {
    unsigned char reserved_000[0x10];
    int field_10;                        // +0x10
    void SetField(int value);
};

void Object3::SetField(int value) {
    field_10 = value;
}
