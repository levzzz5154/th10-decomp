// Complete primary-back creator, using its actual allocator and initializer.
#include "th10/game/item_update_0041afd0.hpp"
#include "th10/render/animation_public_callers.hpp"
#pragma code_seg(".text$126primary")
void** __stdcall ItemAnimation_CreatePrimaryBack(
        void* resource,void** output,int script,int layer) {
    Entity* object=static_cast<AnimationPool*>(data_00491c10)->Allocate();
    unsigned int flags=object->flags_35C;
    object->render_bucket=layer;
    object->flags_35C=flags|0x40000000u;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object,script);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10,output,object);
    return output;
}
#pragma code_seg()
