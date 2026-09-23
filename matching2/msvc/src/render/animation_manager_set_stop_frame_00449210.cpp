// The retail entry receives its lookup context in EDX and script id on the
// stack. Its only current caller initializes SI to 1 before the call, so the
// reachable program behavior is to set the stop frame to one. SI itself is a
// private live-in and is not represented as a general C++ parameter here.
#pragma comment(linker, "/alternatename:_asm_AnimationManager_SetStopFrame_00449210=@AnimationManager_SetStopFrame_00449210@12")
#pragma comment(linker, "/alternatename:_asm_AnimationManager_SetStopFrame_00449210@4=@AnimationManager_SetStopFrame_00449210@12")
#pragma comment(linker, "/alternatename:@asm_AnimationManager_SetStopFrame_00449210@4=@AnimationManager_SetStopFrame_00449210@12")

struct AnimationStopFrameChild_00449210;

struct AnimationStopFrameObject_00449210 {
    unsigned char reserved_000[0x14];
    AnimationStopFrameChild_00449210* children; // +0x14
    int children_flagged;                       // +0x18
    unsigned char reserved_01c[0x2e8];
    unsigned short stop_frame;                  // +0x304
};

struct AnimationStopFrameChild_00449210 {
    AnimationStopFrameObject_00449210* object; // +0x00
    AnimationStopFrameChild_00449210* next;    // +0x04
};

extern "C" AnimationStopFrameObject_00449210* __fastcall
AnimationManager_Find_004491c0(
        void* ecx_live_in,
        void* lookup_context,
        int script_id);

#pragma code_seg(".text$55stopframe")
extern "C" __declspec(noinline) void __fastcall
AnimationManager_SetStopFrame_00449210(
        void* ecx_live_in,
        void* lookup_context,
        int script_id) {
    AnimationStopFrameObject_00449210* object =
        AnimationManager_Find_004491c0(ecx_live_in, lookup_context, script_id);
    if (object == 0) {
        return;
    }

    const int children_flagged = object->children_flagged;
    object->stop_frame = 1;
    if (children_flagged != 0) {
        return;
    }

    for (AnimationStopFrameChild_00449210* child = object->children;
         child != 0;
         child = child->next) {
        child->object->stop_frame = 1;
    }
}
#pragma code_seg()
