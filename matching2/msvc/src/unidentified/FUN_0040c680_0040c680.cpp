// The interpreter arrives in EDX; the original EAX is unused. Pass its
// +4 slot to the resolver in EAX, preserving the remaining live-in registers.
struct EclValueSlot {
    int previous;
    void* interpreter;
};

extern "C" float __attribute__((regparm(1)))
asm_ECL_ResolveFloatValue_0044ff80(void* interpreter);

extern "C" __attribute__((regparm(2), noinline, used))
float asm_FUN_0040c680_0040c680(void* unused, EclValueSlot* slot) {
    return asm_ECL_ResolveFloatValue_0044ff80(slot->interpreter);
}
