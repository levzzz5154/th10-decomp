// 0x0044DF30: advance a byte pointer by an offset.

#pragma code_seg(".text$01accessor")
__declspec(noinline) char* __stdcall AdvanceBytes(char* base, int offset) {
    return base + offset;
}
#pragma code_seg()
