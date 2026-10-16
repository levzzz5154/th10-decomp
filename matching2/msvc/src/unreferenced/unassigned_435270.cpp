// 0x00435270..0x0043527B: advance a pointer by one integer and read it.
// Native LTCG caller context supplies the private EAX cursor convention.
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) int __stdcall Advance2(int** cursor) {
    *cursor += 1;
    return **cursor;
}
#pragma code_seg()
