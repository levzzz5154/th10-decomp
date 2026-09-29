// The interpreter arrives in EAX. Its slot at +4 is the resolver's EAX input;
// the resolver's other live-in registers pass through this tail call unchanged.
struct EclOperandSlot {
    int previous;
    void* interpreter;
};

extern "C" float __attribute__((regparm(1)))
asm_ECL_ResolveFloatOperand_0044fe40(void* interpreter);

extern "C" __attribute__((regparm(1), noinline, used))
float asm_FUN_0040c650_0040c650(EclOperandSlot* slot) {
    return asm_ECL_ResolveFloatOperand_0044fe40(slot->interpreter);
}
