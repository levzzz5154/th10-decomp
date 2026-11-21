// 0x00405590..0x00405594: indexed dword accessor.
// Native LTCG supplies the object pointer in EAX and the index in ECX.
struct IndexAccessor {
    unsigned char pad_000[0x10];
    int values[1];

    __declspec(noinline) int Load(int index) const;
};

#pragma code_seg(".text$01target")
int IndexAccessor::Load(int index) const {
    return values[index];
}
#pragma code_seg()
