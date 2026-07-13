// =============================================================================
// entity.cpp - Base entity lifecycle: destructor, constructor, init, destroy
// Functions: 0x00401FF0, 0x00402050, 0x00401DE0, 0x00438A30
// =============================================================================
#include "th10/game/entity.hpp"

extern "C" void __cdecl _free(void*);
extern "C" void* __cdecl operator_new(uint32_t size);

// ============================================================================
// 0x00401FF0 - Entity Destructor
// Frees the resource at +0x358 and nulls it.
// __fastcall: ECX = this
// Pure C++: 100% byte match (only call _free relocation differs)
// ============================================================================
void __fastcall Entity_Destructor(Entity* e) {
    void* res = e->resource;
    if (res) _free(res);
    e->resource = 0;
}

// ============================================================================
// 0x0041AD60 - Release the entity-owned animation/resource allocation.
// This second call site belongs to a different concrete entity class but has
// the same base layout and destruction semantics as 0x00401FF0.
// Pure C++: 100% byte match when relocation operands are excluded.
// ============================================================================
void __fastcall EntityAnimation_Release(Entity* e) {
    void* resource = e->resource;
    if (resource) _free(resource);
    e->resource = 0;
}

// ============================================================================
// 0x00405DE0 - Release the secondary allocation at Entity +0x360.
// Pure C++; the layout and unconditional null assignment reproduce the retail
// destructor helper.
// ============================================================================
void __fastcall EntitySecondaryResource_Release(Entity* e) {
    void* resource = e->secondary_resource;
    if (resource) _free(resource);
    e->secondary_resource = 0;
}

// ============================================================================
// 0x00402050 - Entity Constructor
// Clears flag bits across the entity, zeroes 0xEB dwords, sets end marker.
// __fastcall: ECX = this, returns this in EAX
// Documented asm (inlined base-class constructor pattern)
// ============================================================================
__declspec(naked) Entity* __fastcall Entity_Constructor(Entity* e) {
    __asm {
        mov edx, ecx
        mov ecx, [edx+6Ch]
        mov eax, 0FFFFFFFEh
        and ecx, eax
        mov [edx+6Ch], ecx
        push edi
        and [edx+0B0h], eax
        and [edx+0FCh], eax
        and [edx+128h], eax
        and [edx+174h], eax
        and [edx+1B0h], eax
        and [edx+1FCh], eax
        and [edx+228h], eax
        and [edx+378h], eax
        xor eax, eax
        mov ecx, 0EBh
        mov edi, edx
        rep stosd
        mov word ptr [edx+384h], 0FFFFh
        mov eax, edx
        pop edi
        ret
    }
}

// ============================================================================
// 0x00401DE0 - Entity Full Init
// Saves 4 fields, zeroes entire entity (0xEB dwords), restores saved fields,
// sets default values (scales=1.0f, timers, linked list self-refs).
// __fastcall: ECX = param_1 (unused), EDX = entity pointer
//
// Disassembly:
//   SUB ESP,0x10; PUSH EBX,EBP,ESI
//   LEA ESI,[EDX+0x340]        ; saved fields area
//   EBX = [EDX+0x340], EBP = [EDX+0x344]
//   ECX = [EDX+0x348], EAX = [EDX+0x20]
//   PUSH EDI
//   [ESP+0x1c] = ECX (field_348)
//   [ESP+0x10] = EAX (field_020)
//   XOR EAX,EAX; MOV ECX,0xEB; MOV EDI,EDX; REP STOSD
//   Restore: [EDX+0x340]=EBX, [EDX+0x344]=EBP, [EDX+0x20]=[ESP+0x10], [EDX+0x348]=[ESP+0x1c]
//   Set defaults: 0xFFFFFFFF at +0x2FC, 1.0f at +0x3C/+0x40,
//     zeros at +0x240..+0x274, 1.0f at +0x250/+0x264/+0x278/+0x23C
//     word 7 at +0x35C, 0xFFF0BDC1 at +0x5C, zeros at +0x60/+0x64
//     zeros at +0xB4/+0x100/+0x12C/+0x178/+0x1B4/+0x200/+0x22C
//     self-ref: [EDX+4]=EDX, [EDX+8]=0, [EDX+0xC]=0, [EDX+0x10]=EDX, [EDX+0x14]=0, [EDX+0x18]=0
// ============================================================================
void __fastcall Entity_Init(void* unused, Entity* entity) {
    // These three fields are copied as one aggregate in the original source.
    // Keeping that shape is significant: MSVC 7.1 then holds the first two
    // words in EBX/EBP and spills the third, matching the original register
    // allocation.
    struct PreservedFields {
        uint32_t field_340;
        uint32_t field_344;
        uint32_t field_348;
    };
    PreservedFields saved = *(PreservedFields*)((uint8_t*)entity + 0x340);
    uint32_t saved_flags = entity->field_020;

    // Zero entire entity (0xEB dwords = 0x3AC bytes)
    uint32_t* p = (uint32_t*)entity;
    for (int i = 0xEB; i != 0; i--) {
        *p++ = 0;
    }

    // Restore saved fields
    PreservedFields* destination =
        (PreservedFields*)((uint8_t*)entity + 0x340);
    destination->field_340 = saved.field_340;
    destination->field_344 = saved.field_344;
    entity->field_020 = saved_flags;
    destination->field_348 = saved.field_348;

    // Set defaults
    *(uint32_t*)((uint8_t*)entity + 0x2FC) = 0xFFFFFFFF;
    entity->scaleX = 1.0f;    // +0x3C
    entity->scaleY = 1.0f;    // +0x40

    // Zero groups and set 1.0f defaults
    *(uint32_t*)((uint8_t*)entity + 0x274) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x270) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x26C) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x268) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x260) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x25C) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x258) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x254) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x24C) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x248) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x244) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x240) = 0;

    *(float*)((uint8_t*)entity + 0x278) = 1.0f;
    *(float*)((uint8_t*)entity + 0x264) = 1.0f;
    *(float*)((uint8_t*)entity + 0x250) = 1.0f;
    *(float*)((uint8_t*)entity + 0x23C) = 1.0f;

    entity->end_marker = 7;                 // +0x35C
    entity->field_060 = 0;                  // +0x60
    entity->scheduler_timer = 0xFFF0BDC1;   // +0x5C
    entity->field_064 = 0;                  // +0x64

    // Zero timer/scheduler slots
    *(uint32_t*)((uint8_t*)entity + 0xB4) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x100) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x12C) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x178) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x1B4) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x200) = 0;
    *(uint32_t*)((uint8_t*)entity + 0x22C) = 0;

    // Self-referencing linked lists (empty list sentinel)
    entity->list1_prev = entity;   // +0x004 = self
    entity->list1_next = 0;        // +0x008 = 0
    entity->field_00C = 0;         // +0x00C = 0
    entity->list2_prev = entity;   // +0x010 = self
    entity->list2_next = 0;        // +0x014 = 0
    entity->field_018 = 0;         // +0x018 = 0
}

// ============================================================================
// 0x00438A30 - DestroyEntityList
// Iterates 32 entity slots at (EAX + 0x3AD4E0), calls each entity's vtable+8
// (destructor), then zeros the slot.
// Non-standard: takes base pointer in EAX (not ECX/EDX).
//
// Disassembly:
//   PUSH ESI; MOV ESI,EAX; PUSH EDI
//   ADD ESI,0x3AD4E0
//   MOV EDI,0x20
//   loop:
//     MOV EAX,[ESI]; TEST EAX,EAX; JZ skip
//     MOV ECX,[EAX]; PUSH EAX; CALL [ECX+8]; MOV [ESI],0
//   skip: ADD ESI,4; DEC EDI; JNZ loop
//   POP EDI; POP ESI; RET
// ============================================================================
__declspec(naked) void __cdecl DestroyEntityList(void* base) {
    __asm {
        push esi
        mov esi, eax
        push edi
        add esi, 0x3AD4E0
        mov edi, 0x20
        nop
    loop_start:
        mov eax, [esi]
        test eax, eax
        jz skip
        mov ecx, [eax]
        push eax
        call dword ptr [ecx + 8]
        mov dword ptr [esi], 0
    skip:
        add esi, 4
        dec edi
        jnz loop_start
        pop edi
        pop esi
        ret
    }
}
