// 0x0041FDD0: initialize title signature and cached interface animations,
// then advance the title effect frame counter.
#include <string.h>
#include "th10/render/animation_public_callers.hpp"
struct TitleEffectState_0041fdd0 {
    unsigned char reserved_000[0x3DC];
    int signature_handle; // +0x3DC
    AnimationResource_00449870* signature_resource; // +0x3E0
    int signature_ready; // +0x3E4
    int interface_ready; // +0x3E8
    int frame_counter; // +0x3EC
};
struct TitleGameThread_0041fdd0 {
    unsigned char reserved_000[0x8994];
    void* ascii_resource;
    unsigned char reserved_8998[0xC];
    AnimationScriptId cached_animation_handle;
    void* AsciiResource() { return ascii_resource; }
};
#pragma code_seg(".text$05title")
extern "C" int __stdcall TitleEffectsAdvance_0041fdd0(TitleEffectState_0041fdd0* state) {
    if (state->signature_ready == 1) {
        AnimationResource_00449870* resource = state->signature_resource;
        Entity* object = ((AnimationPool*)data_00491c10)->Allocate();
        unsigned int flags = object->AnimationFlags();
        object->render_bucket = 15;
        object->AnimationFlags() = flags | 0x40000000u;
        resource->InitializeObject(object, 0);
        int handle;
        asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10, (void**)&handle, object);
        state->signature_handle = handle;
        ++state->signature_ready;
    }
    if (state->interface_ready == 1) {
        AnimationScriptId* cached = &((TitleGameThread_0041fdd0*)g_ascii_manager)->cached_animation_handle;
        AnimationPosition_00448d50 position(480.0f,392.0f,0.0f);
        if (cached->value == 0) {
            int handle;
            AnimationScriptId* result = (AnimationScriptId*)AnimationManager_CreatePositionedPrimary_00448d50(
                ((TitleGameThread_0041fdd0*)g_ascii_manager)->AsciiResource(), (void**)&handle, 6, &position);
            memcpy(cached, result, sizeof(AnimationScriptId));
        }
        ++state->interface_ready;
    }
    ++state->frame_counter;
    return 1;
}
#pragma code_seg()

// Complete existing animation dependencies provide the private LTCG ABIs.
// The layout exports only this worker and its real scheduler callback.
#include "../../layout/ltcg/animation_public_callers_anchors.cpp"
