// 0x0042BA90..0x0042BA9C: store the incoming value in the object's +0x344 field
// and hand the same value back in EAX. The object arrives in ECX, matching the
// retail member ABI (one stack argument, callee cleans).
struct GaugeState {
    int unknown_000[0xD1];           // +0x000..+0x343
    int field_344;                   // +0x344

    int SetValue_0042ba90(int value);
};

int GaugeState::SetValue_0042ba90(int value) {
    field_344 = value;
    return value;
}
