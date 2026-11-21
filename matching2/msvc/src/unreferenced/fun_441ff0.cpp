// 0x00441FF0: copy the first object word to the destination pointer.
// Native LTCG selects the observed source/destination register convention.
struct H3701F10 {
    __declspec(noinline) void Copy(unsigned int* destination);
};

#pragma code_seg(".text$01f")
void H3701F10::Copy(unsigned int* destination) {
    *destination = *(unsigned int*)this;
}
#pragma code_seg()
