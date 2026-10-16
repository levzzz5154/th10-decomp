
struct VectorExpr {
    unsigned char pad_000[0x28];
    int field_28;
    int field_2C;
    __declspec(noinline) int Evaluate();
};

#pragma code_seg(".text$01evaluate")
int VectorExpr::Evaluate() {
    return field_28 * 3 + field_2C;
}
#pragma code_seg()
