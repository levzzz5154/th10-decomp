// 0x00442180: copy the three bytes of a source triple into the +0/+4/+8 fields
// of a destination record.  Modelled as a method of the SOURCE type, so the
// natural __thiscall receiver keeps the source in ECX and the whole-program pass
// promotes the destination argument to EAX, which is retail's register pair.
struct Holder4 { unsigned int field_000, field_004, field_008; };
struct Triple4 {
    unsigned char b0, b1, b2;
    __declspec(noinline) void CopyTo(Holder4* dest);
};
#pragma code_seg(".text$01copy")
void Triple4::CopyTo(Holder4* dest) {
    dest->field_008 = b2;
    dest->field_004 = b1;
    dest->field_000 = b0;
}
#pragma code_seg()
