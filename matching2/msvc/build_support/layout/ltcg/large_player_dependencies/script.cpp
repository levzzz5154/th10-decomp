// 0x0043E710..0x0043E7DA (203 bytes): load animation script `index` of
// `resource` into `object`.
//
// The body zeroes the object and returns when the slot is empty or the resource
// is still loading; otherwise it initialises the entity, records the script
// resource, the resource's id and the index, clears two bits of the +0x35C flag
// word, installs the script base and cursor, re-seeds the frame state (frame 0,
// elapsed 0, previous frame -1, and the 0xFFF0BDC1 / 0x476F78 pair when the
// +0x6C flag word has not been primed yet), clears bit 0 of +0x35C through a
// pointer and finally runs the script once (0x0043EE30) and advances the
// manager's script tick counter.
//
// Retail's entry convention is object in EAX, resource in ECX and index in EBX:
// the resource is copied to ESI and keeps that home for the rest of the body,
// the object is copied to EDI, the index stays in EBX and the shared zero lives
// in EBP.  That is a whole-program decision made from this body's own IR - the
// declaration names no register, and only the *parameter order* matters: the
// pass hands the first parameter ECX and the second EAX, so the resource must
// be declared first.
//
// Two statement shapes are load-bearing (both measured against the image):
//
//  * The first flag mask is a named local stored afterwards
//    (`mask = flags & 0xFFFFF9FF; ... flags = mask;`).  Written as an in-place
//    `&=`, MSVC folds it into `andl $imm,mem` and retail's hoisted load /
//    deferred store is lost.
//  * The final clear is a read-modify-write through a plain (non-`volatile`)
//    `uint32_t*`.  The direct `flags &= ~1u;` folds into the wrong in-place
//    `andl`, while a `volatile` pointer forces the coalesced entry
//    (resource in ESI) and loses retail's `push esi; mov esi,ecx`.  The plain
//    pointer keeps both retail's load/and/store shape and retail's entry.
#include <string.h>
#include "th10/game/entity.hpp"

struct AnimationObjectFile : Entity {
};

struct AnimationResourceFile {
    uint16_t id;                               // +0x000
    unsigned char reserved_002[0x11C - 0x002];
    void** scripts;                            // +0x11C
    unsigned char reserved_120[0x124 - 0x120];
    int loading;                               // +0x124
};

struct AnimationManager_0043e710 {
    unsigned char reserved_00[0x4C];
    int script_tick_counter;                   // +0x4C
};

extern "C" void* g_sprt_ctrl;
extern "C" float g_game_speed;
extern "C" void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
extern "C" void __stdcall LoadScript_0043e710(AnimationResourceFile* resource,
                                             AnimationObjectFile* object,
                                             int index);

#pragma code_seg(".text$a13body")
__declspec(noinline) void __stdcall LoadScript_0043e710(
    AnimationResourceFile* resource, AnimationObjectFile* object,
    int index) {
    void* script = resource->scripts[index];
    if (script == 0 || resource->loading != 0) {
        memset(object, 0, sizeof(Entity));
        return;
    }
    Entity_Init(script, object);               // leading slot is dead in this ABI
    uint32_t mask = object->AnimationFlags() & 0xFFFFF9FFu;
    object->ScriptIndex() = static_cast<int16_t>(index);
    object->ScriptResourceId() = resource->id;
    object->ScriptResource() = resource;
    object->AnimationFlags() = mask;
    void* fresh = resource->scripts[index];
    object->ScriptBase() = fresh;
    object->ScriptCursor() = fresh;
    if ((object->flags_06C & 1) == 0) {
        object->current_frame = 0;
        object->previous_frame = static_cast<int32_t>(0xFFF0BDC1u);
        object->frame_elapsed = 0.0f;
        object->time_scale = &g_game_speed;
        object->flags_06C |= 1;
    }
    object->current_frame = 0;
    object->frame_elapsed = 0.0f;
    object->previous_frame = -1;
    uint32_t* flag_word = &object->AnimationFlags();
    *flag_word &= ~1u;
    asm_FUN_0043ee30_0043ee30(object);
    ++static_cast<AnimationManager_0043e710*>(g_sprt_ctrl)->script_tick_counter;
}
#pragma code_seg()
