// 0x0041FDD0: initialize the loading screen's signature (sig.anm) and cached interface animations,
// then advance its effect frame counter.
#include <string.h>
#include "th10/render/animation_public_callers.hpp"
struct TitleEffectState {
    unsigned char reserved_000[0x3DC];
    int signature_handle; // +0x3DC
    AnimationBank* signature_resource; // +0x3E0
    int signature_ready; // +0x3E4
    int interface_ready; // +0x3E8
    int frame_counter; // +0x3EC
};
struct TitleGameThread {
    unsigned char reserved_000[0x8994];
    void* ascii_resource;
    unsigned char reserved_8998[0xC];
    AnimationScriptId cached_animation_handle;
    void* AsciiResource() { return ascii_resource; }
};
#pragma code_seg(".text$05title")
extern "C" int __stdcall TitleEffectsAdvance(TitleEffectState* state) {
    if (state->signature_ready == 1) {
        AnimationBank* resource = state->signature_resource;
        Entity* object = ((AnimationPool*)g_sprt_ctrl)->Allocate();
        unsigned int flags = object->AnimationFlags();
        object->render_bucket = 15;
        object->AnimationFlags() = flags | 0x40000000u;
        resource->InitializeObject(object, 0);
        int handle;
        asm_AnimationManager_RegisterPrimaryBack_004489d0(g_sprt_ctrl, (void**)&handle, object);
        state->signature_handle = handle;
        ++state->signature_ready;
    }
    if (state->interface_ready == 1) {
        AnimationScriptId* cached = &((TitleGameThread*)g_ascii_manager)->cached_animation_handle;
        AnimationPosition position(480.0f,392.0f,0.0f);
        if (cached->value == 0) {
            int handle;
            AnimationScriptId* result = (AnimationScriptId*)AnimationManager_CreatePositionedPrimary(
                ((TitleGameThread*)g_ascii_manager)->AsciiResource(), (void**)&handle, 6, &position);
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
#include "../../../build_support/layout/ltcg/animation_public_callers_anchors.cpp"
