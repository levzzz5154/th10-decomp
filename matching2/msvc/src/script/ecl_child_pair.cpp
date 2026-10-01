// Only the complete142-byte SpawnChild at0x004500D0 is selected for recovery.
// The complete StartChild model supplies compiler scope; its549 emitted bytes
// remain nonexact against the550-byte retail callee at0x0044DF70.
#include <stddef.h>
#include "th10/script/ecl_children.hpp"
#include "th10/script/ecl_float_values.hpp"
#include "script_resolver_00450470.hpp"

struct EclFrame;
__declspec(noinline) int __fastcall ECL_ResolveIntValue_0044ff00(int unused, EclFrame* source, int selector, int value);
extern "C" void* __cdecl operator_new_child(unsigned int size);

struct EclCompleteChild {
    int time;
    EclFloatOperandTable* instruction;
    EclTaggedStack stack;
    unsigned char reserved_1018[4];
    unsigned char mask;
    unsigned char reserved_101d[7];
};
typedef char ChildExtent[sizeof(EclCompleteChild) == 0x1024 ? 1 : -1];
typedef char ChildMaskOffset[offsetof(EclCompleteChild, mask) == 0x101C ? 1 : -1];

static void PushChildWord(EclCompleteChild* child, int value) {
    int cursor = child->stack.cursor;
    if (cursor + 4 < 0x1000) {
        *(int*)&child->stack.data[cursor] = value;
        child->stack.cursor += 4;
    }
}

#pragma code_seg(".text$01start")
extern "C" __declspec(noinline) int __stdcall EclStartChild(
        EclCompleteChild* child, EclCompleteChild* volatile source, int index) {
    EclFloatOperandTable** instruction = &source->instruction;
    int descriptor = *(int*)&(*instruction)->values[0] + 4 + index * 4;
    int popped = 0;
    int original_cursor = child->stack.cursor;
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
                float value = reinterpret_cast<EclFloatVm*>(source)->ResolveFloatValue(
                        selector, (*instruction)->values[operand_offset >> 2]);
                if (((unsigned char*)*instruction)[0x11 + descriptor] == 'f')
                    *(float*)destination = value;
                else
                    *destination = (int)value;
            } else {
                int value = ECL_ResolveIntValue_0044ff00(0, (EclFrame*)source,
                        selector, *(int*)&(*instruction)->values[operand_offset >> 2]);
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
        int cursor = child->stack.cursor - 4;
        if (cursor >= 0) {
            child->stack.cursor = cursor;
            popped = *(int*)&child->stack.data[cursor];
        }
        child->stack.cursor = original_cursor;
        *(int*)&child->stack.data[original_cursor - 4] = popped;
        PushChildWord(child, source->time);
        PushChildWord(child, (int)*instruction);
    } else {
        child->stack.cursor = 4;
        PushChildWord(child, 0);
        PushChildWord(child, 0);
    }
    EclChildOwner* owner = (EclChildOwner*)source->stack.context;
    EclChildState* previous = owner->active;
    owner->active = (EclChildState*)child;
    owner = (EclChildOwner*)source->stack.context;
    EclCompleteChild* active = (EclCompleteChild*)owner->active;
    active->instruction = (EclFloatOperandTable*)((ScriptTable_00450470*)owner->script)->Resolve(
            (const char*)*instruction + 0x14);
    ((EclCompleteChild*)owner->active)->time = 0;
    if (!((EclCompleteChild*)owner->active)->instruction) {
        *instruction = 0;
        return -1;
    }
    ((EclChildOwner*)source->stack.context)->active = previous;
    return 0;
}
#pragma code_seg(".text$07spawn")
extern "C" __declspec(noinline) int __stdcall EclSpawnChild(
        EclChildOwner* owner, int id, int index) {
    EclCompleteChild* memory = (EclCompleteChild*)operator_new_child(sizeof(EclCompleteChild));
    EclCompleteChild* child;
    if (memory) {
        memory->stack.cursor = 0;
        memory->stack.frame_base = 0;
        child = memory;
    } else child = 0;
    EclChildNode* node = (EclChildNode*)operator_new_child(sizeof(EclChildNode));
    child->stack.slots = (void*)id;
    child->stack.context = (EclFloatValueContext*)owner;
    child->time = 0;
    child->instruction = 0;
    child->mask = ((EclCompleteChild*)owner->active)->mask;
    node->state = (EclChildState*)child;
    node->next = 0;
    node->previous = 0;
    EclChildNode* anchor = &owner->children;
    if (anchor->next) {
        node->next = anchor->next;
        anchor->next->previous = node;
    }
    anchor->next = node;
    node->previous = anchor;
    return EclStartChild(child, (EclCompleteChild*)owner->active, index);
}
#pragma code_seg()
