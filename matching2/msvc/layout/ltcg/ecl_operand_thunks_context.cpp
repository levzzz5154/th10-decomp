// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../src/unidentified/FUN_0040c650_0040c650.cpp"

float __fastcall ResolveSlotFloatValue_0040c680(int selector, EclOperandSlot* slot, float operand);
int ResolveEntityIntOperand_00412a00(EclEntityVm* vm, int selector);

// ABI stand-ins for the two float resolvers recovered in separate clusters.
// They enter on (EAX interpreter, ECX selector). This layout places them at retail
// addresses so the thunks' tail jumps bake retail's displacements; only their
// parameter homes matter. Shifting by the selector keeps it in CL.
struct EclInterpreter {
    unsigned int mask;
    float values[2];
};

#pragma code_seg(".text$09float_operand")
extern "C" __declspec(noinline) float __cdecl asm_ECL_ResolveFloatOperand_0044fe40(
        EclInterpreter* interpreter, int selector) {
    return interpreter->values[(interpreter->mask >> selector) & 1];
}
#pragma code_seg()

#pragma code_seg(".text$11float_value")
extern "C" __declspec(noinline) float __stdcall asm_ECL_ResolveFloatValue_0044ff80(
        EclInterpreter* interpreter, int selector, float operand) {
    if ((interpreter->mask >> selector) & 1)
        return interpreter->values[0];
    return operand;
}
#pragma code_seg()

#pragma code_seg(".text$13context")
float __stdcall EclOperandThunksCompilerContext(EclOperandSlot** slots, EclEntityVm** vms,
                                              int count) {
    float total = 0.0f;
    int integers = 0;
    while (count--) {
        EclOperandSlot* slot = *slots++;
        EclEntityVm* vm = *vms++;
        total += ResolveSlotFloatOperand_0040c650(slot, count);
        total += ResolveSlotFloatValue_0040c680(count, slot, total);
        integers += ResolveEntityIntOperand_00412a00(vm, count);
    }
    return total + integers;
}
#pragma code_seg()
