// Link context for the 0x0044E1A0 equivalent recovery: models of the helpers it
// calls and of its caller, so the checking LTCG link derives the same private
// register conventions as retail. Only EclVm::Run is compared.
#include "ecl_core_interpreter_0044e1a0.hpp"
float data_00470b04 = 0.0f;
float data_00470b60 = -1.0f;
int EclStack::Pop() {
    int b = base;
    if (sp - (int)sizeof(int) >= 0) { sp -= sizeof(int); base = *(int*)(data + sp); }
    sp = b;
    return 0;
}
int EclStack::Push(int size) {
    int old = sp; int next = old + size;
    if (next >= 0x1000) return -1;
    sp = next;
    if (next + 4 < 0x1000) { *(int*)(data + next) = base; sp = sp + 4; }
    base = old;
    return 0;
}
int EclStack::Write(char type, unsigned int size, const void* source) {
    if (sp + (int)size >= 0x1000) return -1;
    if (type != 0) { data[sp] = (unsigned char)type; sp += 4; }
    memcpy(data + sp, source, size);
    sp += (int)size;
    return 0;
}
EclNode* EclOwner::FindVariable(int id) {
    EclNode* node = &children;
    while (node != 0) {
        if (node->vm->id == id) return node;
        node = node->next;
    }
    return 0;
}
void EclOwner::ResetVariableBindings() {
    EclNode* node = children.next;
    while (node != 0) { EclNode* next = node->next; node->vm->instr = 0; node = next; }
}
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
float EclVm::FloatOperand(int selector) {
    EclInstr* operands = instr;
    unsigned short mask = operands->mask;
    if (mask & (1 << selector)) {
        const float& d = operands->f[selector];
        if (d >= data_00470b04) {
            return *(float*)&stack.data[stack.base + (int)d];
        } else if (d == data_00470b60) {
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
float EclVm::FloatValue(int selector, EclVm* vm, float value) {
    unsigned short mask = vm->instr->mask;
    if (mask & (1 << selector)) {
        if (value >= data_00470b04) {
            return *(float*)&vm->stack.data[vm->stack.base + (int)value];
        } else if (value == data_00470b60) {
            vm->stack.PopFloat(&value);
        } else {
            return vm->owner->ResolveFloat((int)value);
        }
    }
    return value;
}
int EclVm::IntOperand(int selector) {
    EclInstr* table = instr;
    unsigned short mask = table->mask;
    if ((mask & (1 << selector)) != 0) {
        int value = table->i[selector];
        if (value >= 0) {
            return *(int*)&stack.data[stack.base + value];
        } else if (value == -1) {
            int o;
            if (stack.sp - 4 >= 0) {
                stack.sp -= 4; o = stack.sp;
                selector = *(int*)&stack.data[o];
                stack.sp -= 4; o = stack.sp;
                if (stack.data[o] == 'f') return (int)*(float*)&selector;
            }
            return selector;
        } else {
            return owner->ResolveInt(value);
        }
    }
    return table->i[selector];
}
int EclVm::IntValue(int selector, int value) {
    if ((instr->mask & (1 << selector)) != 0) {
        if (value >= 0) {
            EclStack* s = &stack;
            return *(int*)&s->data[s->base + value];
        } else if (value == -1) {
            stack.PopInt(&value);
            return value;
        } else {
            return owner->ResolveInt(value);
        }
    }
    return value;
}
struct ScriptTable { __declspec(noinline) int Resolve(const char* name); };
extern "C" void* __cdecl operator_new_child(unsigned int size);
static void PushChildWord(EclVm* child, int value) {
    int cursor = child->stack.sp;
    if (cursor + 4 < 0x1000) {
        *(int*)&child->stack.data[cursor] = value;
        child->stack.sp += 4;
    }
}
int EclVm::Start(EclVm* volatile source, int index) {
    EclVm* child = this;
    EclInstr** instruction = &source->instr;
    int descriptor = (*instruction)->i[0] + 4 + index * 4;
    int popped = 0;
    int original_cursor = child->stack.sp;
    int arguments_offset = original_cursor + 8;
    if (original_cursor == 0) {
        PushChildWord(child, 0);
        arguments_offset = 12;
    }
    int selector = index + 1;
    if (selector < ((unsigned char*)(*instruction))[0xB]) {
        int* destination = (int*)&child->stack.data[arguments_offset];
        unsigned int operand_offset = descriptor + 4;
        do {
            unsigned char* packed = (unsigned char*)*instruction + 0x10;
            char source_type = packed[descriptor];
            if (source_type == 'f' || source_type == 'g') {
                float value = EclVm::FloatValue(selector, source, (*instruction)->f[operand_offset >> 2]);
                if (((unsigned char*)*instruction)[0x11 + descriptor] == 'f')
                    *(float*)destination = value;
                else
                    *destination = (int)value;
            } else {
                int value = source->IntValue(selector, (*instruction)->i[operand_offset >> 2]);
                if (((unsigned char*)*instruction)[0x11 + descriptor] == 'f')
                    *(float*)destination = (float)value;
                else
                    *destination = value;
            }
            ++destination;
            ++selector;
            operand_offset += 8;
            descriptor += 8;
        } while (selector < ((unsigned char*)*instruction)[0xB]);
    }
    if (original_cursor != 0) {
        int cursor = child->stack.sp - 4;
        if (cursor >= 0) {
            child->stack.sp = cursor;
            popped = *(int*)&child->stack.data[cursor];
        }
        child->stack.sp = original_cursor;
        *(int*)&child->stack.data[original_cursor - 4] = popped;
        PushChildWord(child, *(int*)&source->time);
        PushChildWord(child, (int)*instruction);
    } else {
        child->stack.sp = 4;
        PushChildWord(child, 0);
        PushChildWord(child, 0);
    }
    EclOwner* own = source->owner;
    EclVm* previous = own->active;
    own->active = child;
    own = source->owner;
    EclVm* active = own->active;
    active->instr = (EclInstr*)((ScriptTable*)own->script)->Resolve((const char*)*instruction + 0x14);
    own->active->time = 0;
    if (!own->active->instr) {
        *instruction = 0;
        return -1;
    }
    source->owner->active = previous;
    return 0;
}
int EclOwner::SpawnChild(int id, int index) {
    EclVm* memory = (EclVm*)operator_new_child(sizeof(EclVm));
    EclVm* child;
    if (memory) {
        memory->stack.sp = 0;
        memory->stack.base = 0;
        child = memory;
    } else child = 0;
    EclNode* node = (EclNode*)operator_new_child(sizeof(EclNode));
    child->id = id;
    child->owner = this;
    child->time = 0;
    child->instr = 0;
    child->rank = active->rank;
    node->vm = child;
    node->next = 0;
    node->previous = 0;
    EclNode* anchor = &children;
    if (anchor->next) {
        node->next = anchor->next;
        anchor->next->previous = node;
    }
    anchor->next = node;
    node->previous = anchor;
    return child->Start(active, index);
}
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
extern "C" int __stdcall RigEntry(EclOwner* owner, float delta) {
    return owner->Tick(delta);
}
