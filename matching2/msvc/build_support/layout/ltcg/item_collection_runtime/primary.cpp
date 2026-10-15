// Complete primary-back creator, using its actual allocator and initializer.
#include "types/update.hpp"
#include "types/animation_public.hpp"
#pragma code_seg(".text$f00448d00F")
void** __stdcall ItemAnimation_CreatePrimaryBack(
        void* resource,void** output,int script,int layer) {
    Entity* object=static_cast<AnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned int flags=object->flags_35C;
    object->render_bucket=layer;
    object->flags_35C=flags|0x40000000u;
    static_cast<AnimationResource_00449870*>(resource)->InitializeObject(object,script);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl,output,object);
    return output;
}
#pragma code_seg()
