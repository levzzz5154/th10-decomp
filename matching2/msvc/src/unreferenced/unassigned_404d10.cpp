
struct CurveObject2 {
    unsigned char pad_000[0x78];
    float field_78;
    unsigned char pad_f[0x84 - 0x7C];
    int field_84;
    int field_88;
    __declspec(noinline) float Evaluate();
};
float __stdcall EvaluateCurveAnchor(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject2::Evaluate() {
    return EvaluateCurveAnchor(field_88, field_78, (float)field_84);
}
#pragma code_seg()
