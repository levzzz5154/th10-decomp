// 0x00412F20..0x00412F29 - store one dword into the object's fourth slot.
// The object arrives in ECX, so the slot belongs to a class member; the stored
// value is handed back in EAX.
struct Object00412f20 {
    unsigned char unused_0000[0x0C];
    int value_0C;                          // +0x0C
    int StoreValue(int value);
};

int Object00412f20::StoreValue(int value) {
    value_0C = value;
    return value;
}
