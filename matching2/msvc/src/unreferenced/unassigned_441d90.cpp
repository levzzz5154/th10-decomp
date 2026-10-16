struct CurveObject5 {
    unsigned char padding_000[0x18];
    float elapsed;
    unsigned char padding_01c[0x24 - 0x1c];
    int duration;
    unsigned int operation;

    __declspec(noinline) float Evaluate();
};

// Native LTCG retains the retail EAX receiver and the kernel's x87 result.
float __stdcall EvaluateCurveAnchor(unsigned int operation,
                                             float elapsed,
                                             float duration);

#pragma code_seg(".text$01evaluate")
float CurveObject5::Evaluate() {
    return EvaluateCurveAnchor(operation, elapsed, (float)duration);
}
#pragma code_seg()
