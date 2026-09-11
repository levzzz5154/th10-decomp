// 0x0040C6C0..0x0040C6C4 - stub that ignores its argument and returns 0.
// The retail return is the callee-popped (__stdcall) form, so the unused
// argument stays in the prototype.
extern "C" int __stdcall FUN_0040c6c0(int unused) {
    (void)unused;
    return 0;
}
