#include "th10/game/ending_script_caller.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl AnimationPool_AllocateEntry(void* manager);
extern "C" void __cdecl AnmVm_LoadScript(
    void* resource, void* object, int index);
extern "C" void** __cdecl AnimationManager_RegisterPrimaryBack(
    void* manager, void** result, void* object);
extern "C" float recovery_indicator_x_origin_00470b4c;
extern "C" float recovery_indicator_y_origin_00470b48;

// Full 00448DB0 body. Its real allocator, script loader and list registrar
// are co-visible; the compiler chooses the private position-register ABI.
#pragma code_seg(".text$00448db0_fn")
void** __stdcall AnmManager_CreatePositionedAnimation(
        void* resource, void** result, int script,
        const HintPosition* position) {
    unsigned char* object = static_cast<unsigned char*>(
        AnimationPool_AllocateEntry(g_sprt_ctrl));
    *reinterpret_cast<unsigned int*>(object + 0x35C) |= 0x40000000u;
    *reinterpret_cast<int*>(object + 0x20) = 0;
    HintPosition* object_position =
        reinterpret_cast<HintPosition*>(object + 0x340);
    object_position->x = position->x + recovery_indicator_x_origin_00470b4c;
    object_position->y = position->y + recovery_indicator_y_origin_00470b48;
    object_position->z = position->z;
    AnmVm_LoadScript(resource, object, script);
    AnimationManager_RegisterPrimaryBack(g_sprt_ctrl, result, object);
    return result;
}
#pragma code_seg()

// Full maintained 0041AB70 model, with a dedicated section for this cluster.
#pragma code_seg(".text$0041ab70_fn")
void EntityMovementSlot::Initialise(
        const MovementPair* source_value,
        const MovementPair* destination_value,
        int mode_value, unsigned char interpolation_value) {
    mode = mode_value;
    interpolation = interpolation_value;
    source = *source_value;
    destination = *destination_value;
    if (!(flags & 1)) {
        current = 0;
        previous = -999999;
        elapsed = 0;
        speed = (const float*)0x00476F78;
        flags |= 1;
    }
    current = 0;
    elapsed = 0;
    previous = -1;
}
#pragma code_seg()
