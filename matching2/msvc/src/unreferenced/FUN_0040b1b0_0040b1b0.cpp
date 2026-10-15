#include "th10/render/animation_public_callers.hpp"
// 0x0040B1B0: create a bucket-15 animation, attach callbacks, and return its handle.
#pragma code_seg(".text$03callbacks")
extern "C" AnimationScriptId* __stdcall AnimationCreateWithCallbacks_0040b1b0(
        AnimationScriptId* out, AnimationBank* resource, AnimationScriptId script,
        void* context, AnimationInitializer_0040b1b0 initialize,
        AnimationCallback_0040b1b0 update, AnimationCallback_0040b1b0 draw) {
    // Retail captures the result pointer before allocation and callback calls.
    AnimationScriptId* result = *(AnimationScriptId* const volatile*)&out;
    Entity* object = ((AnimationPool*)g_sprt_ctrl)->Allocate();
    unsigned int flags = object->AnimationFlags();
    object->render_bucket = 15;
    object->AnimationFlags() = flags | 0x40000000u;
    resource->InitializeObject(object, (short)script.value);
    void* manager = g_sprt_ctrl;
    asm_AnimationManager_RegisterPrimaryBack_004489d0(manager, (void**)&script.value, object);
    AnimationScriptId handle;
    // Registration replaces the script argument slot with the assigned handle.
    // Capture that fresh value before looking up the registered object.
    handle.value = *(const volatile int*)&script.value;
    object = (Entity*)((SprtCtrl*)manager)->Find((AnimationLookupContext*)manager, handle);
    if (object == 0) handle.value = 0;
    if (initialize != 0) initialize(object, context);
    *(AnimationCallback_0040b1b0*)((unsigned char*)object + 0x398) = update;
    *(AnimationCallback_0040b1b0*)((unsigned char*)object + 0x39C) = draw;
    *result = handle;
    return result;
}
#pragma code_seg()
