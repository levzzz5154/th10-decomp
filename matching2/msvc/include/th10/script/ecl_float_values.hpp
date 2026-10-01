#pragma once

// ECL operand and tagged-stack view shared by the float resolvers. The VM's
// operand table follows its time field; the byte stack starts at VM +0x08.
// These globals are the retail 0.0f and -1.0f constants.
extern "C" float data_00470b04;
extern "C" float data_00470b60;
struct EclFloatOperandTable {
    unsigned char pad_000[8];
    unsigned short indirect_mask;  // +0x08: one bit per operand
    unsigned char pad_00a[6];
    float values[1];               // +0x10: variable-length operand array
};
struct EclFloatValueContext {
    virtual void Reserved0();
    virtual int ResolveInt(int selector);
    virtual int* ResolveIntDestination(int selector);
    virtual float ResolveFloat(int selector);
};
struct EclTaggedStack {
    unsigned char data[0x1000];    // +0x0000: tagged value words
    int cursor;                    // +0x1000: byte offset of stack top
    int frame_base;                // +0x1004: frame-relative byte base
    void* slots;                   // +0x1008: variable bindings
    EclFloatValueContext* context; // +0x100C: external-variable owner
};
struct EclFloatVm {
    float time;                    // +0x0000
    EclFloatOperandTable* table;   // +0x0004
    EclTaggedStack stack;          // +0x0008
    __declspec(noinline) float ResolveFloatOperand(int selector);
    __declspec(noinline) float ResolveFloatValue(int selector, float value);
};

typedef char EclTaggedStack_size_check[sizeof(EclTaggedStack) == 0x1010 ? 1 : -1];
typedef char EclFloatVm_size_check[sizeof(EclFloatVm) == 0x1018 ? 1 : -1];

struct EclFloatOperandSlot {
    int previous;
    EclFloatVm* interpreter;
};
struct EclFloatEntityVm {
    unsigned char state[0x14D8];
    EclFloatOperandSlot* current;
};

__declspec(noinline) float __stdcall ForwardEclFloat(
        EclFloatEntityVm* vm, int selector, float operand);
