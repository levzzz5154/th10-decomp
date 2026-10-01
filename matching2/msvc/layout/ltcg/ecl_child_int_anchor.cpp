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


#pragma code_seg(".text$03intvalue")
__declspec(dllexport) int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* frame, int selector, int value) {
    EclOperandTable* table = frame->operand_table;
    unsigned short mask = table->indirect_mask;
    int result = value;
    if ((mask & (1 << selector)) != 0) {
        if (value >= 0) {
            EclStack* stack = &frame->stack;
            result = *(int*)&stack->data[stack->frame_base + value];
        } else if (value == -1) {
            if (frame->stack.stack_pointer - 4 >= 0) {
                frame->stack.stack_pointer -= 4;
                int raw = *(int*)&frame->stack.data[frame->stack.stack_pointer];
                frame->stack.stack_pointer -= 4;
                float typed = *(float*)&raw;
                if (frame->stack.data[frame->stack.stack_pointer] == 0x66)
                    result = (int)typed;
                else
                    result = raw;
            }
        } else {
            result = frame->stack.context->ResolveSlot(value);
        }
    }
    return result;
}








#pragma code_seg()
