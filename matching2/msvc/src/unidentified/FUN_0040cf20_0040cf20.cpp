// 0x0040CF20..0x0040CF29: FUN_0040cf20
// Recovered: plain setter; stores its argument at offset 0x48 of the object and
// returns it. The retail body is __thiscall (object in ECX, value on the
// stack), so the second __fastcall register argument stays unused.
int __fastcall FUN_0040cf20(int* self, int unused, int value) {
    (void)unused;
    self[18] = value;
    return value;
}
