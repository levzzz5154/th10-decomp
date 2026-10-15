// 0x0040AD10..0x0040AD15: copy the first dword into the second.
// Native LTCG selects the object pointer in EAX for this private helper.
struct CopyPair_0040ad10 {
    int first_000;
    int second_004;

    __declspec(noinline) void CopyFirstToSecond();
};

typedef char CopyPair_0040ad10_size_must_fit[
    sizeof(CopyPair_0040ad10) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01copy")
void CopyPair_0040ad10::CopyFirstToSecond() {
    second_004 = first_000;
}
#pragma code_seg()
