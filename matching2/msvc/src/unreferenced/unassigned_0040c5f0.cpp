
struct EclFrame;

int __fastcall resolve_operand_0044fdb0(int unused, EclFrame* frame, int selector);

struct OperandSource_0040c5f0 {
    unsigned char pad_000[4];
    void* field_004;
    __declspec(noinline) int Resolve(int value);
};

#pragma code_seg(".text$01resolve")
int OperandSource_0040c5f0::Resolve(int value) {
    return resolve_operand_0044fdb0((int)this, (EclFrame*)field_004, value);
}
#pragma code_seg()
