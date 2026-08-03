#include "th10/script/ecl_vm_children.hpp"

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif
#include <cstring>
#include <vector>

#ifdef _MSC_VER
extern "C" void* sub_452493(unsigned long);
extern "C" void sub_44DF70(void*, void*, void*);
extern "C" int sub_44E1A0(void*);
extern "C" void sub_4524A1(void*);
extern "C" int sub_44FF00(void*, int);
extern "C" float sub_44FF80(void*, int);
extern "C" void* sub_450470(void*);
extern "C" long __cdecl __ftol2(void);
#endif

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
#ifdef _MSC_VER
__declspec(naked) int EclVm_StartChildRetail() {
    __asm {
        sub esp, 10h
        mov edx, [esp+18h]
        push ebx
        push ebp
        push esi
        push edi
        mov edi, [esp+24h]
        add edi, 4
        mov esi, eax
        mov eax, [edi]
        mov ecx, [eax+10h]
        mov eax, [esi+1008h]
        lea ebp, [ecx+edx*4+4]
        xor edx, edx
        test eax, eax
        mov [esp+14h], edx
        mov [esp+1Ch], eax
        lea ecx, [eax+8]
        jnz loc_44DFC1
        mov ecx, eax
        lea ebx, [ecx+4]
        cmp ebx, 1000h
        jge loc_44DFBC
        mov [ecx+esi+8], edx
        add dword ptr [esi+1008h], 4
loc_44DFBC:
        mov ecx, 0Ch
loc_44DFC1:
        mov edx, [edi]
        mov ebx, [esp+28h]
        movzx edx, byte ptr [edx+0Bh]
        inc ebx
        cmp ebx, edx
        jge loc_44E08E
        lea eax, [ecx+esi+8]
        mov [esp+28h], eax
        lea eax, [ebp+4]
        mov [esp+10h], eax
        jmp loc_44DFF0
loc_44DFE5:
        mov eax, [esp+10h]
        _emit 8Dh
        _emit 0A4h
        _emit 24h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
loc_44DFF0:
        mov ecx, [edi]
        mov dl, byte ptr [ecx+ebp+10h]
        cmp dl, 66h
        jz loc_44E033
        cmp dl, 67h
        jz loc_44E033
        mov edx, [esp+24h]
        shr eax, 2
        mov ecx, [ecx+eax*4+10h]
        push ecx
        push ebx
        call sub_44FF00
        mov edx, [edi]
        cmp byte ptr [edx+ebp+11h], 66h
        mov [esp+18h], eax
        jnz loc_44E02B
        fild dword ptr [esp+18h]
        mov eax, [esp+28h]
        fstp dword ptr [eax]
        jmp loc_44E062
loc_44E02B:
        mov ecx, [esp+28h]
        mov [ecx], eax
        jmp loc_44E062
loc_44E033:
        shr eax, 2
        mov edx, [ecx+eax*4+10h]
        mov eax, [esp+24h]
        push edx
        mov ecx, ebx
        call sub_44FF80
        mov eax, [edi]
        cmp byte ptr [eax+ebp+11h], 66h
        jnz loc_44E057
        mov ecx, [esp+28h]
        fstp dword ptr [ecx]
        jmp loc_44E062
loc_44E057:
        call __ftol2
        mov edx, [esp+28h]
        mov [edx], eax
loc_44E062:
        mov ecx, [esp+28h]
        mov eax, [edi]
        mov edx, [esp+10h]
        add ecx, 4
        mov [esp+28h], ecx
        movzx ecx, byte ptr [eax+0Bh]
        inc ebx
        add edx, 8
        add ebp, 8
        cmp ebx, ecx
        mov [esp+10h], edx
        jl loc_44DFE5
        mov eax, [esp+1Ch]
loc_44E08E:
        test eax, eax
        mov edx, [esp+24h]
        mov ebx, 4
        jz loc_44E0F4
        mov ecx, [esi+1008h]
        add ecx, 0FFFFFFFCh
        js loc_44E0B4
        mov [esi+1008h], ecx
        mov ecx, [ecx+esi+8]
        mov [esp+14h], ecx
loc_44E0B4:
        mov ecx, [esp+14h]
        mov [esi+1008h], eax
        mov [eax+esi+4], ecx
        mov eax, [esi+1008h]
        lea ecx, [eax+4]
        cmp ecx, 1000h
        jge loc_44E0DF
        mov ecx, [edx]
        mov [eax+esi+8], ecx
        add [esi+1008h], ebx
loc_44E0DF:
        mov eax, [esi+1008h]
        lea ecx, [eax+4]
        cmp ecx, 1000h
        jge loc_44E12E
        mov ecx, [edi]
        jmp loc_44E124
loc_44E0F4:
        mov eax, ebx
        lea ebp, [eax+4]
        xor ecx, ecx
        cmp ebp, 1000h
        mov [esi+1008h], ebx
        jge loc_44E113
        mov [eax+esi+8], ecx
        add [esi+1008h], ebx
loc_44E113:
        mov eax, [esi+1008h]
        lea ebp, [eax+4]
        cmp ebp, 1000h
        jge loc_44E12E
loc_44E124:
        mov [eax+esi+8], ecx
        add [esi+1008h], ebx
loc_44E12E:
        mov eax, [edx+1014h]
        mov ebx, [eax+4]
        mov [eax+4], esi
        mov esi, [edx+1014h]
        mov edx, [edi]
        mov eax, [esi+102Ch]
        add edx, 14h
        push edx
        call sub_450470
        mov ecx, [esi+4]
        mov [ecx+4], eax
        mov edx, [esi+4]
        mov dword ptr [edx], 0
        mov eax, [esi+4]
        mov ecx, [eax+4]
        test ecx, ecx
        jnz loc_44E17D
        mov dword ptr [edi], 0
        pop edi
        pop esi
        pop ebp
        or eax, 0FFFFFFFFh
        pop ebx
        add esp, 10h
        ret 8
loc_44E17D:
        mov ecx, [esp+24h]
        mov edx, [ecx+1014h]
        pop edi
        pop esi
        pop ebp
        mov [edx+4], ebx
        xor eax, eax
        pop ebx
        add esp, 10h
        ret 8
    }
}
#else
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
#endif

// 0x004500D0 - Spawn a child ECL VM. Retail allocates the 0x1024-byte VM
// record and a 12-byte list link, clears the VM's instruction offset, wait
// counter, and both interpolator slots, binds the script handle and owning
// interpreter, copies the difficulty mask byte (+0x101C) from the currently
// active VM, pushes the link at the head of the owner's child list
// (anchor +0x1030 / head +0x1034), and forwards the start argument to the
// child-start helper (retail 0x0044DF70) with the active VM.
#ifdef _MSC_VER
__declspec(naked) EclChildVm* EclVm_SpawnChild(
        EclOwner* owner, void* script, float* start_argument,
        void* (*allocate)(unsigned int size),
        void (*start)(void* active_vm, float* argument)) {
    __asm {
        push ebx
        push esi
        push 1024h
        call sub_452493
        xor ebx, ebx
        add esp, 4
        cmp eax, ebx
        je child_null
        mov [eax+1008h], ebx
        mov [eax+100Ch], ebx
        mov esi, eax
        jmp after_child
child_null:
        xor esi, esi
after_child:
        push 0Ch
        call sub_452493
        mov ecx, [esp+10h]
        mov [esi+1010h], ecx
        mov [esi+1014h], edi
        mov [esi], ebx
        mov [esi+4], ebx
        mov edx, [edi+4]
        mov cl, [edx+101Ch]
        mov [esi+101Ch], cl
        lea ecx, [edi+1030h]
        mov [eax], esi
        mov [eax+4], ebx
        mov [eax+8], ebx
        mov edx, [ecx+4]
        add esp, 4
        cmp edx, ebx
        je no_next
        mov [eax+4], edx
        mov edx, [ecx+4]
        mov [edx+8], eax
no_next:
        mov [ecx+4], eax
        mov [eax+8], ecx
        mov eax, [esp+10h]
        mov ecx, [edi+4]
        push eax
        push ecx
        mov eax, esi
        call sub_44DF70
        pop esi
        pop ebx
        ret 8
    }
}
#else
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
#endif

// 0x0044FD10 - Tick the interpreter's VM chain for one frame. The first
// pass runs the anchor's own VM and aborts the whole frame with -1 when it
// fails. Every following node runs its child VM; children whose tick
// reports completion are freed and unlinked in place. When the walk ends,
// the active-VM slot is restored to the interpreter's embedded root VM.
#ifdef _MSC_VER
__declspec(naked) int EclVm_TickChildren(
        EclOwner* owner, float frame_delta,
        int (*tick)(EclOwner* owner, float delta),
        void (*free_memory)(void* memory)) {
    __asm {
        push ebx
        push ebp
        push esi
        lea esi, [edi+1030h]
        test esi, esi
        mov ebp, 1
        je finish
walk_loop:
        test ebp, ebp
        mov eax, [esi]
        mov ebx, [esi+4]
        mov [edi+4], eax
        je first_pass
        mov ecx, [esp+10h]
        push ecx
        call sub_44E1A0
        test eax, eax
        jne fail
        xor ebp, ebp
        jmp next
first_pass:
        mov edx, [esp+10h]
        push edx
        call sub_44E1A0
        test eax, eax
        je next
        mov eax, [edi+4]
        push eax
        call sub_4524A1
        mov eax, [esi+4]
        xor ecx, ecx
        add esp, 4
        cmp eax, ecx
        je unlink_previous
        mov edx, [esi+8]
        mov [eax+8], edx
unlink_previous:
        mov eax, [esi+8]
        cmp eax, ecx
        je free_link
        mov edx, [esi+4]
        mov [eax+4], edx
free_link:
        push esi
        mov [esi+4], ecx
        mov [esi+8], ecx
        call sub_4524A1
        add esp, 4
next:
        test ebx, ebx
        mov esi, ebx
        jne walk_loop
finish:
        pop esi
        lea eax, [edi+8]
        pop ebp
        mov [edi+4], eax
        xor eax, eax
        pop ebx
        ret 4
fail:
        pop esi
        pop ebp
        or eax, 0FFFFFFFFh
        pop ebx
        ret 4
    }
}
#else
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
#endif

// --- Manager lifecycle leaves ---------------------------------------------------
