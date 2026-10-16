// 0x0040ADA0: publish the strided record selected by an index and stamp that
// index into the record's +0x3C/+0x40 fields.  The index arrives in EAX and the
// record in ECX, the pointer-argument pair convention the EAX driver earns.
struct Indexed2 {
    unsigned char pad_000[0x3c];
    unsigned int field_03c;              // +0x03C
    unsigned int field_040;              // +0x040
};
extern "C" unsigned int* g_stage_route_current;
extern "C" __declspec(noinline) void __stdcall Publish2(unsigned int index, Indexed2* record);
#pragma code_seg(".text$01pub")
void __stdcall Publish2(unsigned int index, Indexed2* record) {
    g_stage_route_current = (unsigned int*)(index * 0x30 + 0x00474788);
    record->field_03c = index;
    record->field_040 = index;
}
#pragma code_seg()
