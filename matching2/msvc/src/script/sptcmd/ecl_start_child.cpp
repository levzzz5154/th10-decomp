// A call or spawn enters a named ECL subroutine with a fresh or nested frame.
#include <string.h>
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"
#include "script_resolver.hpp"

typedef char ChildExtent[sizeof(EclVm) == 0x1024 ? 1 : -1];
typedef char MaskOffset[offsetof(EclVm, rank) == 0x101c ? 1 : -1];

// Every eight-byte call record begins with source type and destination type.
struct EclArgumentTypes { char source; char destination; };
static __forceinline const EclArgumentTypes& ArgumentTypes(const EclInstr* call, int descriptor) {
    return *(const EclArgumentTypes*)(call->s + descriptor);
}

#pragma intrinsic(memcpy)
static __forceinline void PushBytes(EclStack* stack, unsigned int size, const void* in) {
    if (stack->sp + (int)size >= (int)sizeof(stack->data)) return;
    memcpy(stack->data + stack->sp, in, size);
    stack->sp += (int)size;
}
static __forceinline void PushWord(EclStack* stack, const void* in) {
    PushBytes(stack, sizeof(int), in);
}
#pragma code_seg(".text$01start")
// The caller's instruction can change inside an operand resolver. Re-read it
// for the destination type and the loop bound.
int EclVm::Start(EclVm* volatile source, int index) {
    EclInstr** instruction = &source->instr;
    // Skip the length-prefixed sub name and the preceding fixed-width words.
    int descriptor = (*instruction)->i[0] + 4 + index * 4;
    int saved_frame = 0;
    int original_cursor = stack.sp;
    int arguments_offset = original_cursor + 8;
    if (original_cursor == 0) {
        PushWord(&stack, &saved_frame);
        arguments_offset = 12;
    }
    for (int selector = index + 1; selector < (*instruction)->argc;
         ++selector, descriptor += 8, arguments_offset += 4) {
        char source_type = ArgumentTypes(*instruction, descriptor).source;
        if (source_type == 'f' || source_type == 'g') {
            float value = FloatValue(selector, source, (*instruction)->f[(unsigned int)(descriptor + 4) >> 2]);
            if (ArgumentTypes(*instruction, descriptor).destination == 'f')
                *(float*)&stack.data[arguments_offset] = value;
            else
                *(int*)&stack.data[arguments_offset] = (int)value;
        } else {
            unsigned int operand = (unsigned int)(descriptor + 4) >> 2;
            int value = source->IntValue(selector, (*instruction)->i[operand]);
            if (ArgumentTypes(*instruction, descriptor).destination == 'f')
                *(float*)&stack.data[arguments_offset] = (float)value;
            else
                *(int*)&stack.data[arguments_offset] = value;
        }
    }
    EclVm* caller = source;
    if (original_cursor != 0) {
        // Re-link the saved frame word below the arguments, then save time and pc.
        stack.PopRaw(&saved_frame);
        stack.sp = original_cursor;
        *(int*)&stack.data[original_cursor - 4] = saved_frame;
        PushWord(&stack, &caller->time);
        PushWord(&stack, instruction);
    } else {
        int zero = 0;
        stack.sp = 4;
        PushWord(&stack, &zero);
        PushWord(&stack, &zero);
    }
    // Make the child current while its sub is looked up by name.
    EclOwner* owner = caller->owner;
    EclVm* previous = owner->active;
    owner->active = this;
    owner = caller->owner;
    EclVm* active = owner->active;
    active->instr = (EclInstr*)((ScriptTable2*)owner->script)->Resolve((*instruction)->s + 4);
    owner->active->time = 0;
    if (!owner->active->instr) {
        *instruction = 0;
        return -1;
    }
    source->owner->active = previous;
    return 0;
}
#pragma code_seg()

extern "C" void* __cdecl operator_new_child(unsigned int size);

// Allocate the child VM and link its node into the owner before entering the sub.
#pragma code_seg(".text$07spawn")
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
#pragma code_seg()
