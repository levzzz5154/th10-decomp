struct CurveObject_00441db0 {
    unsigned char padding_000[0x28];
    float elapsed;
    unsigned char padding_02c[0x34 - 0x2c];
    int duration;
    unsigned int operation;

    __declspec(noinline) float Evaluate();
};

// Native LTCG retains the retail EAX receiver and the kernel's x87 result.
float __stdcall EvaluateCurveAnchor(unsigned int operation,
                                             float elapsed,
                                             float duration);

#pragma code_seg(".text$01evaluate")
float CurveObject_00441db0::Evaluate() {
    return EvaluateCurveAnchor(operation, elapsed, (float)duration);
}
#pragma code_seg()
