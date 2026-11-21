// Unselected caller and callee code used to recover the native interpreter ABI.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"
#pragma code_seg(".text$084pop")
int EclStack::Pop() {
    int b = base;
    if (sp - (int)sizeof(int) >= 0) { sp -= sizeof(int); base = *(int*)(data + sp); }
    sp = b;
    return 0;
}
#pragma code_seg(".text$083push")
int EclStack::Push(int size) {
    int old = sp; int next = old + size;
    if (next >= 0x1000) return -1;
    sp = next;
    if (next + 4 < 0x1000) { *(int*)(data + next) = base; sp = sp + 4; }
    base = old;
    return 0;
}
#pragma code_seg(".text$082write")
int EclStack::Write(char type, unsigned int size, const void* source) {
    if (sp + (int)size >= 0x1000) return -1;
    if (type != 0) { data[sp] = (unsigned char)type; sp += 4; }
    memcpy(data + sp, source, size);
    sp += (int)size;
    return 0;
}
#pragma code_seg(".text$080find")
EclNode* EclOwner::FindVariable(int id) {
    EclNode* node = &children;
    while (node != 0) {
        if (node->vm->id == id) return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg(".text$081reset")
void EclOwner::ResetVariableBindings() {
    EclNode* node = children.next;
    while (node != 0) { EclNode* next = node->next; node->vm->instr = 0; node = next; }
}
#pragma code_seg(".text$06intdest")
int* EclVm::IntDest(int index) {
    if (instr->mask & (1 << index)) {
        const int& offset = instr->i[index];
        if (offset >= 0) {
            EclStack* frame = &this->stack;
            return (int*)((char*)frame + frame->base + offset);
        }
        return owner->ResolveIntDest(offset);
    }
    return 0;
}
#pragma code_seg(".text$06zfloatdest")
float* EclVm::FloatDest(int index) {
    if (instr->mask & (1 << index)) {
        const float& displacement = instr->f[index];
        if (displacement >= 0.0f) {
            EclStack* frame = &this->stack;
            return (float*)((char*)frame + frame->base + (int)displacement);
        }
        return owner->ResolveFloatDest((int)displacement);
    }
    return 0;
}
#pragma code_seg(".text$04floatoperand")
float EclVm::FloatOperand(int selector) {
    EclInstr* operands = instr;
    unsigned short mask = operands->mask;
    if (mask & (1 << selector)) {
        const float& d = operands->f[selector];
        if (d >= flt_0) {
            return *(float*)&stack.data[stack.base + (int)d];
        } else if (d == flt_neg1) {
            union { int integer; float real; } value;
            if (stack.sp - 4 >= 0) {
                stack.sp -= 4;
                value.integer = *(int*)&stack.data[stack.sp];
                stack.sp -= 4;
                char tag = stack.data[stack.sp];
                if (tag == 'f') return value.real;
                if (tag == 'i') return (float)value.integer;
            }
            return value.real;
        } else {
            return owner->ResolveFloat((int)d);
        }
    }
    return operands->f[selector];
}
#pragma code_seg(".text$03intoperand")
#include "../../../../src/script/sptcmd/ecl_int_operand.cpp"
#pragma code_seg(".text$04zintvalue")
#include "../../../../src/script/sptcmd/ecl_int_value.cpp"
#pragma code_seg(".text$001tick")
int EclOwner::Tick(float delta) {
    EclNode* node = &children;
    int first = 1;
    while (node) {
        EclNode* next = node->next;
        active = node->vm;
        if (first) {
            if (active->Run(delta)) return -1;
            first = 0;
        } else if (active->Run(delta)) {
            free(active);
            if (node->next) node->next->previous = node->previous;
            if (node->previous) node->previous->next = node->next;
            node->next = 0; node->previous = 0;
            free(node);
        }
        node = next;
    }
    active = &root;
    return 0;
}
#pragma code_seg(".text$000entry")
extern "C" int __stdcall RigEntry(EclOwner* owner, float delta) {
    return owner->Tick(delta);
}
#pragma code_seg()
