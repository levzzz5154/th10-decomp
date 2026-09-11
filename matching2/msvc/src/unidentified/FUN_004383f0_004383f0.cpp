// 0x004383F0..0x004383F4 - the object pointer arrives in ECX and is handed
// straight back in EAX; the stack argument is never read.
struct Object004383f0 {
    Object004383f0* Self(int unused);
};

Object004383f0* Object004383f0::Self(int unused) {
    (void)unused;
    return this;
}
