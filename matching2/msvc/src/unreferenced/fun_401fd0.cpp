// 0x00401FD0..0x00401FEE: invoke a callback once per strided element of a run.
// Retail keeps the count in EAX, the cursor in ECX, the callback in EBX and the
// stride in the single stack argument that the callee pops.

#pragma code_seg(".text$01invoke")
__declspec(noinline) int InvokeStridedCallback(int count, int cursor, int stride,
                          int (__fastcall *callback)(int)) {
    int result = count - 1;
    if (result >= 0) {
        int remaining = result + 1;
        do {
            result = callback(cursor);
            cursor += stride;
        } while (--remaining);
    }
    return result;
}
#pragma code_seg()
