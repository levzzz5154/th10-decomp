// 0x00408880..0x00408894: saturating tick of one counter field.
//
// The body is a plain member: `this` arrives in ECX, the field at +0x84 is
// read, incremented while it is below 99999 and written back. The image leaves
// the resulting value in EAX, which a void member reproduces exactly; the
// region has no caller and no pointer to it anywhere in the executable, so the
// result register is dead.
//
// 0x00408860 is the same body one field lower at +0x80 and stays assembly.

struct CounterState2 {
    char pad_000[0x84];
    int field_084;
    __declspec(noinline) void Tick();
};

void CounterState2::Tick() {
    if (field_084 < 99999)
        ++field_084;
}
