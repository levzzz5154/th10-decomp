#include "th10/script/ecl_vm_children.hpp"

#include <cstdint>
#include <cstring>
#include <vector>


namespace {

void PushStartWord(EclStartVm* vm, unsigned int value) {
    if (vm->stack_top + 4 >= sizeof(vm->stack)) return;
    memcpy(vm->stack + vm->stack_top, &value, sizeof(value));
    vm->stack_top += 4;
}

unsigned int PopStartWord(EclStartVm* vm) {
    if (vm->stack_top < 4) return 0;
    vm->stack_top -= 4;
    unsigned int value;
    memcpy(&value, vm->stack + vm->stack_top, sizeof(value));
    return value;
}

}  // namespace

// 0x0044DF70 - Start a child at the label embedded in the parent's call
// instruction. Retail keeps a zero/link word at the base, converts every
// remaining argument to its declared destination type, appends the parent's
// return offset and instruction pointer, and temporarily publishes the child
// as the active VM while resolving its label.
int EclVm_StartChild(EclStartVm* child, EclStartVm* parent,
                     EclStartOwner* owner,
                     const EclStartInstruction* instruction,
                     unsigned int first_argument,
                     const EclStartHooks* hooks) {
    const unsigned int original_top = child->stack_top;
    std::vector<unsigned int> converted;
    for (unsigned int index = first_argument + 1;
         index < instruction->argument_count; ++index) {
        const EclStartArgument& argument = instruction->arguments[index];
        EclStartValue value = {};
        if (argument.source_type == 'f' || argument.source_type == 'g') {
            const float resolved =
                hooks->resolve_float(parent, index, argument.value.float_value);
            if (argument.destination_type == 'f') {
                value.float_value = resolved;
            } else {
                value.int_value = static_cast<int>(resolved);
            }
        } else {
            const int resolved =
                hooks->resolve_int(parent, index, argument.value.int_value);
            if (argument.destination_type == 'f') {
                value.float_value = static_cast<float>(resolved);
            } else {
                value.int_value = resolved;
            }
        }
        unsigned int word;
        memcpy(&word, &value, sizeof(word));
        converted.push_back(word);
    }

    if (original_top == 0) {
        PushStartWord(child, 0);
    } else {
        const unsigned int link = PopStartWord(child);
        child->stack_top = original_top;
        PushStartWord(child, link);
        PushStartWord(child, parent->instruction_offset);
    }
    const uintptr_t return_instruction =
        reinterpret_cast<uintptr_t>(parent->instruction);
    PushStartWord(child, static_cast<unsigned int>(return_instruction));
    for (std::vector<unsigned int>::const_iterator it = converted.begin();
         it != converted.end(); ++it) {
        PushStartWord(child, *it);
    }

    EclStartVm* previous = owner->active_vm;
    owner->active_vm = child;
    child->instruction = hooks->find_label(instruction->label);
    child->instruction_offset = 0;
    if (child->instruction == 0) {
        parent->instruction = 0;
        return -1;
    }
    owner->active_vm = previous;
    return 0;
}

// 0x004500D0 - Spawn a child ECL VM. Retail allocates the 0x1024-byte VM
// record and a 12-byte list link, clears the VM's instruction offset, wait
// counter, and both interpolator slots, binds the script handle and owning
// interpreter, copies the difficulty mask byte (+0x101C) from the currently
// active VM, pushes the link at the head of the owner's child list
// (anchor +0x1030 / head +0x1034), and forwards the start argument to the
// child-start helper (retail 0x0044DF70) with the active VM.
EclChildVm* EclVm_SpawnChild(EclOwner* owner, void* script,
                                   float* start_argument,
                                   void* (*allocate)(unsigned int size),
                                   void (*start)(void* active_vm,
                                                 float* argument)) {
    EclChildVm* child = (EclChildVm*)allocate(0x1024);
    if (child != 0) {
        child->interpolator_slot_a = 0;
        child->interpolator_slot_b = 0;
    }
    EclChildLink* link = (EclChildLink*)allocate(0xC);
    if (child == 0 || link == 0) return 0;
    child->script = script;
    child->owner = owner;
    child->instruction_offset = 0;
    child->wait_counter = 0;
    child->difficulty_mask =
        ((EclChildVm*)owner->active_vm)->difficulty_mask;
    link->vm = child;
    link->next = 0;
    link->previous = 0;
    if (owner->anchor.next != 0) {
        link->next = owner->anchor.next;
        owner->anchor.next->previous = link;
    }
    owner->anchor.next = link;
    link->previous = &owner->anchor;
    if (start != 0) start(owner->active_vm, start_argument);
    return child;
}

// 0x0044FD10 - Tick the interpreter's VM chain for one frame. The first
// pass runs the anchor's own VM and aborts the whole frame with -1 when it
// fails. Every following node runs its child VM; children whose tick
// reports completion are freed and unlinked in place. When the walk ends,
// the active-VM slot is restored to the interpreter's embedded root VM.
int EclVm_TickChildren(EclOwner* owner, float frame_delta,
                       int (*tick)(EclOwner* owner, float delta),
                       void (*free_memory)(void* memory)) {
    int first_pass = 1;
    EclChildLink* node = &owner->anchor;
    while (node != 0) {
        EclChildLink* current = node;
        node = current->next;
        owner->active_vm = current->vm;
        if (first_pass) {
            if (tick(owner, frame_delta) != 0) return -1;
            first_pass = 0;
            continue;
        }
        if (tick(owner, frame_delta) != 0) {
            free_memory(owner->active_vm);
            if (current->next != 0) current->next->previous = current->previous;
            if (current->previous != 0) current->previous->next = current->next;
            current->next = 0;
            current->previous = 0;
            free_memory(current);
        }
    }
    owner->active_vm = owner->root_vm;
    return 0;
}

// --- Manager lifecycle leaves ---------------------------------------------------
