// Shapes shared by the ECL operand thunks at 0x0040C650, 0x0040C680 and
// 0x00412A00 and the resolvers they forward to.
#pragma once

struct EclInterpreter;
struct EclFrame;

// An operand slot records its interpreter at +4.
struct EclOperandSlot {
    int previous;
    EclInterpreter* interpreter;
};

// The entity's ECL VM keeps its current operand slot at +0x14D8.
struct EclEntityVm {
    char prior[0x14d8];
    EclOperandSlot* slot;
};

// 0x0044FE40 and 0x0044FF80 take the interpreter in EAX and the selector in
// ECX, which no declaration names; see the ecl_operand_thunks layout.
extern "C" __declspec(noinline) float __cdecl asm_ECL_ResolveFloatOperand_0044fe40(
        EclInterpreter* interpreter, int selector);
extern "C" __declspec(noinline) float __stdcall asm_ECL_ResolveFloatValue_0044ff80(
        EclInterpreter* interpreter, int selector, float operand);

// 0x0044FDB0 ignores ECX and takes the frame in EDX and the selector on the stack.
int __fastcall ECL_ResolveIntOperand(int unused, EclFrame* frame, int selector);
