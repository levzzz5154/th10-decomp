// 0x0040CF80..0x0040CF8C: FUN_0040cf80
// Stores the sole argument in the object field at +0x440.
struct Object_0040cf80 {
    unsigned char reserved_000[0x440];
    int field_440;                       // +0x440
    void SetField(int value);
};

void Object_0040cf80::SetField(int value) {
    field_440 = value;
}
