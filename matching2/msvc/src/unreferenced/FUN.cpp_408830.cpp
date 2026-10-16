// 0x00408830..0x00408834: indexed dword accessor.
// Native LTCG supplies the object pointer in EAX and the index in ECX.
struct IndexAccessor2 {
    unsigned char pad_000[0x30];
    int values[1];

    __declspec(noinline) int Load(int index) const;
};

#pragma code_seg(".text$01target")
int IndexAccessor2::Load(int index) const {
    return values[index];
}
#pragma code_seg()
