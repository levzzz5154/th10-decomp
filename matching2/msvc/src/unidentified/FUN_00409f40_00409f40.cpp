// 0x00409F40..0x00409F49: indexed value lookup.
//
// Native LTCG keeps the private object/index pair in EAX/EDX for this member.
struct H3301Entry_00409f40 {
    int value_000;
    int reserved_004;
};

struct H3301Table_00409f40 {
    unsigned char pad_000[0x8C];
    H3301Entry_00409f40* entries_08C;
    __declspec(noinline) int GetValue(int index) const;
};

#pragma code_seg(".text$01target")
int H3301Table_00409f40::GetValue(int index) const {
    return entries_08C[index].value_000;
}
#pragma code_seg()
