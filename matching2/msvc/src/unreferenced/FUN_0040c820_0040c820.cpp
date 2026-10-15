// 0x0040C820..0x0040C824: indexed dword accessor.
// Native LTCG supplies the object pointer in EAX and the index in ECX.
struct IndexAccessor_0040c820 {
    unsigned char pad_000[0x0c];
    int values[1];

    __declspec(noinline) int Load(int index) const;
};

#pragma code_seg(".text$01target")
int IndexAccessor_0040c820::Load(int index) const {
    return values[index];
}
#pragma code_seg()
