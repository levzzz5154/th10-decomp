// 0x00413150..0x00413159 - store one dword into an object field.
// The object arrives in ECX, so the field belongs to a class member; the
// stored value is returned unchanged.
struct Object00413150 {
    unsigned char unused_0000[0x20];
    int value_20;                          // +0x20
    int StoreValue(int value);
};

int Object00413150::StoreValue(int value) {
    value_20 = value;
    return value;
}
