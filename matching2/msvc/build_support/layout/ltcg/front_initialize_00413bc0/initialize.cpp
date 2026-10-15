// 0x00449870: reset animation vectors and start a script while preserving object state.
#include "th10/game/entity_script_start.hpp"
#include "th10/game/front_initialize_00413bc0.hpp"
struct AnimationObject_0043e7e0;
struct AnimationResource_0043e7e0;
__declspec(noinline) void *__stdcall
InitializePreservingLoader_0043e7e0(AnimationResource_0043e7e0 *resource,
                                    AnimationObject_0043e7e0 *object, int index);
struct AnimationFlagValue {
    unsigned int value;
    AnimationFlagValue(unsigned int bits) : value(bits) {}
    AnimationFlagValue operator|(unsigned int bits) const {
        return AnimationFlagValue(value | bits);
    }
};

#pragma code_seg(".text$00449870_fn")
void FrontAnimationResource::InitializeObject(Entity *object, int index) {
    AnimationFlagValue flags = *reinterpret_cast<AnimationFlagValue *>(&object->AnimationFlags());
    object->Position() = Vector3Value(0.0f, 0.0f, 0.0f);
    object->BasePosition() = Vector3Value(0.0f, 0.0f, 0.0f);
    object->AnimationFlags() = (flags | 0x40000000u).value;
    object->ScriptIndex() = static_cast<short>(index);
    object->RenderOffset() = Vector3Value(0.0f, 0.0f, 0.0f);
    EntityTail(object)->layer_3a1 = 0x10;
    EntityTail(object)->layer_3a0 = 0x10;
    InitializePreservingLoader_0043e7e0((AnimationResource_0043e7e0 *)this,
                                        (AnimationObject_0043e7e0 *)object, index);
}
#pragma code_seg()
