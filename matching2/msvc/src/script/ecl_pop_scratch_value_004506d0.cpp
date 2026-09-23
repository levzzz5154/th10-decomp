// 0x004506D0..0x004506F8: pop the current value from the ECL scratch stack.
// The interpreter passes the VM/frame pointer in EAX and supplies no stack
// arguments. This is a private register ABI; a native-LTCG context is needed to
// keep the receiver in EAX instead of the ordinary __thiscall ECX register.
struct EclVm_004506d0 {
    unsigned char pad_000[0x1000];
    unsigned int scratch_offset; // +0x1000
    int scratch_value;           // +0x1004
    __declspec(noinline) int PopScratchValue();
};

#pragma code_seg(".text$01accessor")
int EclVm_004506d0::PopScratchValue() {
    int offset = -4 + scratch_offset;
    int value = scratch_value;
    if (offset >= 0) {
        scratch_offset = offset;
        scratch_value = *(int*)((unsigned char*)this + offset);
    }
    scratch_offset = value;
    return 0;
}
#pragma code_seg()
