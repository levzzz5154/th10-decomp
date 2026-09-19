struct Holder_00442180 { unsigned int field_000, field_004, field_008; };
struct Triple_00442180 {
    unsigned char b0, b1, b2;
    __declspec(noinline) void CopyTo(Holder_00442180* dest);
};
#pragma code_seg(".text$01copy")
void Triple_00442180::CopyTo(Holder_00442180* dest) {
    dest->field_008 = b2;
    dest->field_004 = b1;
    dest->field_000 = b0;
}
#pragma code_seg()
