struct Rec_00413080 {
    unsigned char pad_000[4];
    int field_004;
};
__declspec(noinline) int __stdcall Greater_00413080(Rec_00413080* self, int value);
#pragma code_seg(".text$01accessor")
int __stdcall Greater_00413080(Rec_00413080* self, int value) {
    return self->field_004 > value;
}
#pragma code_seg()
