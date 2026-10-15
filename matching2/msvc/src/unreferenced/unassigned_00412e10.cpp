
struct CurveObject_00412e10 {
    unsigned char pad_000[0x28];
    float field_28;
    unsigned char pad_2C[0x34 - 0x2C];
    int field_34;
    int field_38;
    __declspec(noinline) float Evaluate();
};

float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject_00412e10::Evaluate() {
    return EvaluateCurveAnchor_0044c350(field_38, field_28, (float)field_34);
}
#pragma code_seg()
