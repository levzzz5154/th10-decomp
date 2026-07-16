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
// The flag clears visible before the bulk clear are compiler artifacts; the
// observable result is a zeroed base record with an invalid end marker.
// ============================================================================
Entity* __fastcall Entity_Constructor(Entity* e) {
    uint32_t* destination = (uint32_t*)e;
    for (int remaining = 0xEB; remaining != 0; --remaining) {
        *destination++ = 0;
    }
    e->end_marker = 0xFFFF;
    return e;
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
//   [ESP+0x10] = EAX (render_bucket)
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
    struct PreservedPositionBits {
        uint32_t x;
        uint32_t y;
        uint32_t z;
    };
    // Preserve the aggregate bit-for-bit. Using integer words here reproduces
    // retail's EBX/EBP/spill allocation; a float Vector3 copy makes old MSVC
    // generate a substantially different prologue and store schedule.
    PreservedPositionBits saved_position =
        *(PreservedPositionBits*)&entity->position;
    int32_t saved_render_bucket = entity->render_bucket;

    // Zero entire entity (0xEB dwords = 0x3AC bytes)
    uint32_t* p = (uint32_t*)entity;
    for (int i = 0xEB; i != 0; i--) {
        *p++ = 0;
    }

    // Restore saved fields
    PreservedPositionBits* destination =
        (PreservedPositionBits*)&entity->position;
    destination->x = saved_position.x;
    destination->y = saved_position.y;
    entity->render_bucket = saved_render_bucket;
    destination->z = saved_position.z;

    // Set defaults
    entity->primary_color = 0xFFFFFFFF;
    entity->scale_x = 1.0f;    // +0x3C
    entity->scale_y = 1.0f;    // +0x40

    // Construct the local D3D transform as an identity matrix. The reverse
    // store order mirrors retail MSVC code generation without obscuring the
    // fact that these sixteen fields are one matrix.
    entity->local_transform.values[3][2] = 0.0f;
    entity->local_transform.values[3][1] = 0.0f;
    entity->local_transform.values[3][0] = 0.0f;
    entity->local_transform.values[2][3] = 0.0f;
    entity->local_transform.values[2][1] = 0.0f;
    entity->local_transform.values[2][0] = 0.0f;
    entity->local_transform.values[1][3] = 0.0f;
    entity->local_transform.values[1][2] = 0.0f;
    entity->local_transform.values[1][0] = 0.0f;
    entity->local_transform.values[0][3] = 0.0f;
    entity->local_transform.values[0][2] = 0.0f;
    entity->local_transform.values[0][1] = 0.0f;
    entity->local_transform.values[3][3] = 1.0f;
    entity->local_transform.values[2][2] = 1.0f;
    entity->local_transform.values[1][1] = 1.0f;
    entity->local_transform.values[0][0] = 1.0f;

    entity->end_marker = 7;                 // +0x35C
    entity->current_frame = 0;              // +0x60
    entity->previous_frame = 0xFFF0BDC1;    // +0x5C sentinel
    entity->frame_elapsed = 0.0f;           // +0x64

    // Zero timer/scheduler slots
    entity->pad_0B4[0] = 0;
    entity->pad_100[0] = 0;
    entity->pad_12C[0] = 0;
    entity->pad_178[0] = 0;
    entity->pad_1B4[0] = 0;
    entity->pad_200[0] = 0;
    entity->pad_22C[0] = 0;

    // Empty embedded list nodes retain their owning animation pointer.
    entity->manager_node_animation = entity;
    entity->manager_node_next = 0;
    entity->manager_node_previous = 0;
    entity->child_node_animation = entity;
    entity->child_node_next = 0;
    entity->child_node_previous = 0;
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
void __cdecl DestroyEntityList(void* base) {
    void** slots = (void**)((uint8_t*)base + 0x3AD4E0);
    for (int index = 0; index < 0x20; ++index) {
        void* object = slots[index];
        if (object) {
            void** vtable = *(void***)object;
            typedef void (__stdcall *DestroyFunction)(void*);
            ((DestroyFunction)vtable[2])(object);
            slots[index] = 0;
        }
    }
}
