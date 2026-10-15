// 0x0042BAA0 - store one word into the object's slot at +0x340 and return it.
// The value arrives on the stack (ECX is the object), so this is the __thiscall
// setter of that slot.
struct Object0042baa0 {
    unsigned char pad_000[0x340];
    int field_340;  // +0x340

    int SetField(int value);
};

int Object0042baa0::SetField(int value) {
    field_340 = value;
    return value;
}
