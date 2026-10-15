#include "../../../include/contexts/game/right_aligned_text_context/recovery_script_executor_caller_00419120.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void __cdecl asm_AnimationObject_LoadScript_0043e710(
    void* resource, void* object, int index);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** result, void* object);
extern "C" float recovery_indicator_x_origin_00470b4c;
extern "C" float recovery_indicator_y_origin_00470b48;

// Full 00448DB0 body. Its real allocator, script loader and list registrar
// are co-visible; the compiler chooses the private position-register ABI.
#pragma code_seg(".text$00448db0_fn")
void** __stdcall RecoveryPlayerAnimationCreate_00448db0(
        void* resource, void** result, int script,
        const HintPosition_00419120* position) {
    unsigned char* object = static_cast<unsigned char*>(
        asm_FUN_00449950_00449950(g_sprt_ctrl));
    *reinterpret_cast<unsigned int*>(object + 0x35C) |= 0x40000000u;
    *reinterpret_cast<int*>(object + 0x20) = 0;
    HintPosition_00419120* object_position =
        reinterpret_cast<HintPosition_00419120*>(object + 0x340);
    object_position->x = position->x + recovery_indicator_x_origin_00470b4c;
    object_position->y = position->y + recovery_indicator_y_origin_00470b48;
    object_position->z = position->z;
    asm_AnimationObject_LoadScript_0043e710(resource, object, script);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, result, object);
    return result;
}
#pragma code_seg()

// Full maintained 0041AB70 model, with a dedicated section for this cluster.
#pragma code_seg(".text$0041ab70_fn")
void EntityMovementSlot_0041ab70::Initialise(
        const MovementPair_0041ab70* source_value,
        const MovementPair_0041ab70* destination_value,
        int mode_value, unsigned char interpolation_value) {
    mode = mode_value;
    interpolation = interpolation_value;
    source = *source_value;
    destination = *destination_value;
    if (!(flags & 1)) {
        previous = 0;
        timer = -999999;
        elapsed = 0;
        speed = (const float*)0x00476F78;
        flags |= 1;
    }
    previous = 0;
    elapsed = 0;
    timer = -1;
}
#pragma code_seg()
