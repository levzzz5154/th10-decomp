// 0x00442170: store the private EAX value into object field +0x48 and return it.
// Native MSVC LTCG supplies the value in EAX and the object in ECX.
struct ObjectAccessor_00442170 {
    unsigned char pad_000[0x48];
    int field_048;
    __declspec(noinline) int StoreValue(int value);
};
typedef char ObjectAccessor_00442170_size_must_fit[
    sizeof(ObjectAccessor_00442170) == 0x4c ? 1 : -1];

#pragma code_seg(".text$01accessor00442170")
int ObjectAccessor_00442170::StoreValue(int value) {
    field_048 = value;
    return value;
}
#pragma code_seg()
// The former naked entry is retained only as regions.json previous_record
// history; the live region targets ObjectAccessor_00442170::StoreValue.
