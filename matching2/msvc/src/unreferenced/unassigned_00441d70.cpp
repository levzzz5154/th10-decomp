
struct CurveObject_00441d70 {
    unsigned char pad_000[0x38];
    float field_38;
    unsigned char pad_3C[0x44 - 0x3C];
    int field_44;
    int field_48;
    __declspec(noinline) float Evaluate();
};
float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject_00441d70::Evaluate() {
    return EvaluateCurveAnchor_0044c350(field_48, field_38, (float)field_44);
}
#pragma code_seg()
