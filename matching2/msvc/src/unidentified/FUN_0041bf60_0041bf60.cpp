// 0x0041BF60. Three stack arguments are cleaned by the callee and the result
// is always zero: the empty implementation of a three-argument __stdcall slot.
int __stdcall RecoveryZeroSlot_0041bf60(int, int, int) {
    return 0;
}
