// Equivalent recovery of EclStartChild (0x0044DF70): starts a child ECL
// context for a call instruction. The call's arguments after operand
// `index` are resolved in the caller's context and copied onto the child's
// value stack, the caller frame (saved frame word, time and instruction
// pointer) is pushed above them, and the child is pointed at the named sub.
// Built with SpawnChild (0x004500D0) and a synthetic caller so the link
// derives the retail private convention (child in EAX, caller and operand
// index on the stack, RET 8). Remaining register-choice and code-shape
// differences are recorded in build_support/layout/equivalent/ecl_start_child.json;
// see reference/recovery_notes/ecl_start_child_0044df70_parked_2026_10_11.md.
#include <stddef.h>
#include "th10/script/ecl_children.hpp"
#include "th10/script/ecl_float_values.hpp"
#include "script_resolver.hpp"

struct EclFrame;
__declspec(noinline) int __fastcall ECL_ResolveIntValue2(int unused, EclFrame* source, int selector, int value);
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

// A call instruction: the parameter count is the header byte at +0x0B; the
// operands start at +0x10 with the sub name's length, the name at +0x14, and
// then one 8-byte descriptor per argument: destination type, source type,
// two pad bytes and the operand word. 'f' marks a float, 'g' a float variable.
static __forceinline unsigned char ParameterCount(const EclFloatOperandTable* call) {
    return ((const unsigned char*)call)[0xB];
}
static __forceinline char ArgumentType(const EclFloatOperandTable* call, int descriptor, int which) {
    return ((const char*)call)[0x10 + which + descriptor];
}

static __forceinline void PushWord(EclTaggedStack* stack, const void* in) {
    if (stack->cursor + 4 < 0x1000) {
        *(int*)&stack->data[stack->cursor] = *(const int*)in;
        stack->cursor += 4;
    }
}
static __forceinline void PushValue(EclTaggedStack* stack, int value) {
    if (stack->cursor + 4 < 0x1000) {
        *(int*)&stack->data[stack->cursor] = value;
        stack->cursor += 4;
    }
}
static __forceinline int PopValue(EclTaggedStack* stack, int fallback) {
    int cursor = stack->cursor - 4;
    if (cursor >= 0) {
        stack->cursor = cursor;
        return *(int*)&stack->data[cursor];
    }
    return fallback;
}

#pragma code_seg(".text$01start")
// `source` is volatile and the operand index is read again through a volatile
// access: retail keeps both in their stack slots and reloads them per block.
extern "C" __declspec(noinline) int __stdcall EclStartChild(
        EclCompleteChild* child, EclCompleteChild* volatile source, int index) {
    EclFloatOperandTable** instruction = &source->instruction;
    int descriptor = *(int*)&(*instruction)->values[0] + 4 + index * 4;
    int saved_frame = 0;
    int original_cursor = child->stack.cursor;
    int arguments_offset = original_cursor + 8;
    if (original_cursor == 0) {
        PushValue(&child->stack, saved_frame);
        arguments_offset = 12;
    }
    for (int selector = *(volatile int*)&index + 1; selector < ParameterCount(*instruction); ++selector) {
        int* destination = (int*)&child->stack.data[arguments_offset];
        char source_type = ArgumentType(*instruction, descriptor, 0);
        if (source_type == 'f' || source_type == 'g') {
            float value = reinterpret_cast<EclFloatVm*>(source)->ResolveFloatValue(
                    selector, (*instruction)->values[(unsigned int)(descriptor + 4) >> 2]);
            if (ArgumentType(*instruction, descriptor, 1) == 'f')
                *(float*)destination = value;
            else
                *destination = (int)value;
        } else {
            int operand = *(int*)&(*instruction)->values[(unsigned int)(descriptor + 4) >> 2];
            int value = ECL_ResolveIntValue2(operand, (EclFrame*)source, selector, operand);
            if (ArgumentType(*instruction, descriptor, 1) == 'f')
                *(float*)destination = (float)value;
            else
                *destination = value;
        }
        arguments_offset += 4;
        descriptor += 8;
    }
    EclCompleteChild* caller = source;
    if (original_cursor != 0) {
        // Re-link the saved frame word below the arguments, then save time and pc.
        saved_frame = PopValue(&child->stack, saved_frame);
        child->stack.cursor = original_cursor;
        *(int*)&child->stack.data[original_cursor - 4] = saved_frame;
        PushWord(&child->stack, &caller->time);
        PushWord(&child->stack, instruction);
    } else {
        child->stack.cursor = 4;
        PushValue(&child->stack, 0);
        PushValue(&child->stack, 0);
    }
    // Make the child current while its sub is looked up by name.
    EclChildOwner* owner = (EclChildOwner*)caller->stack.context;
    EclChildState* previous = owner->active;
    owner->active = (EclChildState*)child;
    owner = (EclChildOwner*)caller->stack.context;
    EclCompleteChild* active = (EclCompleteChild*)owner->active;
    active->instruction = (EclFloatOperandTable*)((ScriptTable2*)owner->script)->Resolve(
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
#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) int __stdcall EclChildPairContext(EclCompleteChild** sources, int id, int index, int count) {
 int result=0;
 while(count--) {
  EclCompleteChild* source=*sources++;
  EclChildOwner* owner=(EclChildOwner*)source->stack.context;
  result += EclSpawnChild(owner,id,index);
  result += EclStartChild(source,source,index);
 }
 return result;
}
#pragma code_seg()
