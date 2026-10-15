#include "th10/game/pause_initializer_00422ab0.hpp"
struct AnimationObject_0043e7e0;
struct AnimationResource_0043e7e0;
__declspec(noinline) void __stdcall LoadScriptPreservingState(AnimationResource_0043e7e0*, AnimationObject_0043e7e0*, int);
struct AnimationPositionValue { float x,y,z; AnimationPositionValue(float x,float y,float z):x(x),y(y),z(z){} };
#pragma code_seg(".text$15resource")
__declspec(dllexport) void AnimationBank::InitializeObject(Entity* object, int index) {
    *reinterpret_cast<AnimationPositionValue*>(&object->position) = AnimationPositionValue(0,0,0);
    *reinterpret_cast<AnimationPositionValue*>(&object->base_position) = AnimationPositionValue(0,0,0);
    unsigned int flags = object->AnimationFlags();
    *reinterpret_cast<AnimationPositionValue*>(&object->render_offset) = AnimationPositionValue(0,0,0);
    object->AnimationFlags() = flags | 0x40000000;
    object->ScriptIndex() = (short)index;
    reinterpret_cast<unsigned char*>(object)[0x3A1] = 16;
    reinterpret_cast<unsigned char*>(object)[0x3A0] = 16;
    LoadScriptPreservingState(reinterpret_cast<AnimationResource_0043e7e0*>(this),reinterpret_cast<AnimationObject_0043e7e0*>(object),index);
}
#pragma code_seg()
