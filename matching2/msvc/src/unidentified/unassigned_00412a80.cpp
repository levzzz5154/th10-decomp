
struct EclFrame;
int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame,
                                            int selector, int value);

struct EclOperandSource_00412a80 {
    unsigned char pad_000[0x14D8];
    int* field_14D8;
    __declspec(noinline) int Resolve(int selector, int value);
};

#pragma code_seg(".text$01resolve")
int EclOperandSource_00412a80::Resolve(int selector, int value) {
    int* source = field_14D8;
    return ECL_ResolveIntValue_0044ff00(selector, (EclFrame*)source[1], value, selector);
}
#pragma code_seg()
