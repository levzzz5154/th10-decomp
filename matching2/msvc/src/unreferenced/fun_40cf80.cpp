// 0x0040CF80..0x0040CF8C: FUN7
// Stores the sole argument in the object field at +0x440.
struct Object2 {
    unsigned char reserved_000[0x440];
    int field_440;                       // +0x440
    void SetField(int value);
};

void Object2::SetField(int value) {
    field_440 = value;
}
