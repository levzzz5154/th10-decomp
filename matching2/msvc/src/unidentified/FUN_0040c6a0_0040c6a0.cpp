// 0x0040C6A0 - constant leaf: this predicate always reports "no" (zero in EAX).
// Its single stack argument is never read, so the __stdcall callee still pops
// it (ret 4).
int __stdcall FUN_0040c6a0_0040c6a0(int unused) {
    (void)unused;
    return 0;
}
