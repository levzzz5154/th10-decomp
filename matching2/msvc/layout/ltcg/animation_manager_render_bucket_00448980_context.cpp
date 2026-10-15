// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/core/sprtlib/animation_manager_render_bucket_00448980.cpp"

// A drawable entity as 0x004451C0 reads it: the visible flag byte at +0x2FF, the
// flag word at +0x35C - bits 0 and 1 gate the draw, bits 22..25 select the
// pipeline - and the two counts the strip pipeline consumes.
struct DrawEntity_004451c0 {
    unsigned char reserved_000[0x2FF];
    unsigned char visible;                  // +0x2FF
    unsigned char reserved_300[0x30C - 0x300];
    unsigned int count;                     // +0x30C
    unsigned char reserved_310[0x358 - 0x310];
    unsigned int vertex_count;              // +0x358
    unsigned int flags;                     // +0x35C
};

// The ten pipelines the dispatch selects between.  The nine still-unnamed ones
// are opaque here and bound at their retail addresses: the anchor exists for this
// body's register assignment only, and its own bytes are never exported.
extern "C" int __cdecl asm_FUN_00443080_00443080(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_00443290_00443290(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_004436c0_004436c0(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_00443910_00443910(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_00443f80_00443f80(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_00443fb0_00443fb0(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_00444580_00444580(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_004445c0_004445c0(DrawEntity_004451c0* entity, void* manager);
extern "C" int __cdecl asm_FUN_00444760_00444760(DrawEntity_004451c0* entity, void* manager);

// 0x004451C0's body.  It is compiled only so the whole-program pass can put the
// entity in EAX and the manager in ECX: its only caller is the modelled bucket
// walk and no declaration names either register.  The layout's gaps place this
// section at the retail address, so the walk's call bakes retail's own
// displacement and needs no relocation.  None of these bytes are selected as
// recovered code.
//
// The manager is declared first on purpose.  The pass assigns the registers by
// role - the entity, whose live range ends at each branch's call, takes EAX, and
// the manager, which the callees also want, takes ECX - while the declaration
// order decides the order in which the caller materialises them.  Retail's caller
// sets the entity up first, so the manager has to be the first parameter.
#pragma code_seg(".text$01anchor")
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
        void* manager, RenderSlotNode_00448980* entity) {
    DrawEntity_004451c0* record = (DrawEntity_004451c0*)entity;
    unsigned int flags = record->flags;
    if ((flags & 0x1) == 0 || (flags & 0x2) == 0 || record->visible == 0) {
        return -1;
    }
    switch ((flags >> 22) & 0xF) {
    case 0: return asm_FUN_00443080_00443080(record, manager);
    case 1: return asm_FUN_004436c0_004436c0(record, manager);
    case 2: return asm_FUN_00443f80_00443f80(record, manager);
    case 3: return asm_FUN_00444580_00444580(record, manager);
    case 4: return asm_FUN_00443fb0_00443fb0(record, manager);
    case 5: return asm_FUN_004445c0_004445c0(record, manager);
    case 6: return asm_FUN_00444760_00444760(record, manager);
    case 7: return ((AnimationManager_00442F50*)manager)->DrawStrip(
                (const RenderEntity*)record, 0, record->vertex_count);
    case 8: return asm_FUN_00443290_00443290(record, manager);
    case 9: return asm_FUN_00443910_00443910(record, manager);
    default: return 0;
    }
}
#pragma code_seg()

// Synthetic caller that establishes the bucket walk's register convention: it
// walks an array of animation managers and draws one bucket of each.  Not
// recovered game code.
#pragma code_seg(".text$05context")
int __stdcall RenderBucketContext(AnimationManager_00442F50** managers, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        result = managers[index]->RenderBucket(index);
    }
    return result;
}
#pragma code_seg()
