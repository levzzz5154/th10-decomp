#pragma once


// The operand table the interpreter resolves a script operand through: +0x8 is
// the bitmap of slots holding an indirect reference, +0x10 the slot array.
struct EclOperandTable {
    unsigned char pad_00[8];
    unsigned short indirect_mask;      // +0x08
    unsigned char pad_0A[6];
    int slots[1];                      // +0x10
};

// Accessor object reached through +0x1014. Its second virtual entry resolves a
// slot that refers to a live script variable.
struct EclVariableContext {
    virtual void Reserved();           // +0x00
    virtual int ResolveSlot(int slot); // +0x04
};

// The interpreter's value stack and the cursor words that address slots inside
// it. The frame embeds it, so every access goes through this member.
struct EclStack {
    unsigned char data[0x1000];        // +0x0000
    int stack_pointer;                 // +0x1000
    int frame_base;                    // +0x1004
    void* variable_slots;              // +0x1008
    EclVariableContext* context;       // +0x100C
};

struct EclFrame {
    unsigned char pad_00[4];
    EclOperandTable* operand_table;    // +0x0004
    EclStack stack;                    // +0x0008
};

// 0x0044FDB0: resolve an integer operand from its immediate, frame-relative,
// scratch-stack, or external-variable representation. ECX is ignored, the VM
// is in EDX, and the stack-passed selector is removed by RET 4.
// Popping a scratch value consumes its value word, then its tag word. Keep the
// cursor updates as separate pops; float-tagged values are converted through x87.
