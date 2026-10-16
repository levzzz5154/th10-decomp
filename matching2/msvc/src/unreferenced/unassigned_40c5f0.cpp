
struct EclFrame;

int __fastcall resolve_operand(int unused, EclFrame* frame, int selector);

struct OperandSource {
    unsigned char pad_000[4];
    void* field_004;
    __declspec(noinline) int Resolve(int value);
};

#pragma code_seg(".text$01resolve")
int OperandSource::Resolve(int value) {
    return resolve_operand((int)this, (EclFrame*)field_004, value);
}
#pragma code_seg()
