// 0x0042C670 (95 bytes): create a script-owned animation object in render
// bucket 15, start script `index` of the room's animation resource on it,
// register it at the back of the primary list and remember its handle in the
// room's slot `index`.
//
// Native LTCG passes the index in EDI; the room stays on the stack.
#include "th10/game/recovery_script_executor_caller_00433ef0.hpp"

extern "C" void* data_00491c10;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* object);
struct AnimationResource_00449870 {
    __declspec(noinline) void* InitializeObject(void* object, int index);
};

#pragma code_seg(".text$0042c670_fn")
__declspec(noinline) void __stdcall RecoveryMusicInstallSlot_0042c670(
        RecoveryMusicRoom_00433ef0* room, int index) {
    void* resource = room->animation_resource;
    RecoveryMusicVm_00433ef0* object = static_cast<RecoveryMusicVm_00433ef0*>(
        asm_FUN_00449950_00449950(data_00491c10));
    object->render_bucket = 15;
    object->flags |= 0x40000000u;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object, index);
    void* handle;
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10, &handle, object);
    room->animation_slots[index] = reinterpret_cast<unsigned int>(handle);
}
#pragma code_seg()
