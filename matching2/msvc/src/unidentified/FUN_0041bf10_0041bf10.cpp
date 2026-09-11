// 0x0041BF10..0x0041BF12 - stub predicate that always reports "no".
// The retail body is a bare zero return; the caller's test is what gives it
// meaning, so the name keeps its address until a caller identifies it.
extern "C" int __cdecl FUN_0041bf10(void) {
    return 0;
}
