// Chase the ECL VM's operand frame at +0x14D8, then its interpreter at +4.
// EAX carries the VM and then the resolver receiver; ECX passes through as
// the float selector. A tail call forwards the resolver's x87 result.
struct EclFloatOperandFrame {
    int previous;
    void* interpreter;
};

struct EclFloatOperandVm {
    char prior[0x14d8];
    EclFloatOperandFrame* frame;
};

extern "C" float __attribute__((regparm(1)))
asm_ECL_ResolveFloatOperand_0044fe40(void* interpreter);

extern "C" __attribute__((regparm(1), noinline, used))
float asm_FUN_00412a60_00412a60(EclFloatOperandVm* vm) {
    return asm_ECL_ResolveFloatOperand_0044fe40(vm->frame->interpreter);
}
