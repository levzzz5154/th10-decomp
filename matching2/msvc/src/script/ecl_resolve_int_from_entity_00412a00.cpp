// The VM arrives in EAX and its integer selector in ECX. Follow the entity's
// ECL frame at +0x14D8 and pass its +4 interpreter in EDX; the resolver
// consumes the selector from the stack and returns its integer result in EAX.
struct EclEntityOperandFrame {
    int previous;
    void* interpreter;
};

struct EclEntityOperandVm {
    char prior[0x14d8];
    EclEntityOperandFrame* frame;
};

extern "C" int __attribute__((regparm(2), stdcall))
asm_ECL_ResolveIntOperand_0044fdb0(EclEntityOperandFrame* frame,
                                     void* interpreter, int selector);

extern "C" __attribute__((regparm(3), noinline, used))
int asm_ECL_ResolveIntFromEntity_00412a00(EclEntityOperandVm* vm,
                                            void* unused, int selector) {
    EclEntityOperandFrame* frame = vm->frame;
    return asm_ECL_ResolveIntOperand_0044fdb0(frame, frame->interpreter,
                                                selector);
}
