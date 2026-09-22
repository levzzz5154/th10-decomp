// 0x00434B50..0x00434B5F: compare a record word against an integer.
// Native LTCG caller context supplies the register ordering seen in retail.
struct Object_00434b50 {
    int value;
};
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) int __stdcall Greater_00434b50(
        Object_00434b50* self, int other) {
    return self->value > other;
}
#pragma code_seg()
