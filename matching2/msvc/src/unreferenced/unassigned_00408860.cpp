// 0x00408860..0x00408874: saturating tick of one counter field.
//
// The body is a plain member: `this` arrives in ECX, the field at +0x80 is
// read, incremented while it is below 99999 and written back. The image leaves
// the resulting value in EAX, which a void member reproduces exactly; the
// region has no caller and no pointer to it anywhere in the executable, so the
// result register is dead.
//
// 0x00408880 is the same body one field higher at +0x84 and is recovered in
// src/unreferenced/unassigned_00408880.cpp.

struct CounterState_00408860 {
    char pad_000[0x80];
    int field_080;
    __declspec(noinline) void Tick();
};

void CounterState_00408860::Tick() {
    if (field_080 < 99999)
        ++field_080;
}
