
struct CurveObject3 {
    unsigned char pad_000[0x28];
    float field_28;
    unsigned char pad_2C[0x34 - 0x2C];
    int field_34;
    int field_38;
    __declspec(noinline) float Evaluate();
};

float __stdcall EvaluateCurveAnchor(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject3::Evaluate() {
    return EvaluateCurveAnchor(field_38, field_28, (float)field_34);
}
#pragma code_seg()
