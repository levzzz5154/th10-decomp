// Ordinary C++ model of retail 0x00421300.
//
// Its only caller pushes one stack argument and expects the callee to remove
// it. The old assembler name is kept as a linker fallback for that call site;
// the implementation itself has the proper one-argument __stdcall contract.
#pragma comment(linker, "/alternatename:_asm_FUN_00421300_00421300=_ReleaseAnimationHandles_00421300@4")

extern "C" int data_00477824;
extern "C" int data_00477828;
extern "C" int data_0047782c;
extern "C" unsigned int data_00491bec;

struct AnimationLookupNode_00421300 {
    void* object; // +0x00: animation object registered in this bucket
    AnimationLookupNode_00421300* next; // +0x04
};

struct AnimationLookupContext_00421300 {
    unsigned char reserved_000000[0x72DAD4];
    AnimationLookupNode_00421300* primary_bucket; // +0x72DAD4
    unsigned int reserved_72DAD8;
    AnimationLookupNode_00421300* secondary_bucket; // +0x72DADC
};

extern "C" AnimationLookupContext_00421300* data_00491c10;

struct AnimationObject_00421300 {
    int script_handle; // +0x00
    unsigned char reserved_0004[0x10];
    AnimationLookupNode_00421300* children; // +0x14
    int children_already_flagged; // +0x18
    unsigned char reserved_001c[0x2E8];
    unsigned short release_state; // +0x304
};

struct AnimationReleaseControl_00421300 {
    unsigned char reserved_0000[0x6FC];
    int state; // +0x6FC
};

namespace {

AnimationObject_00421300* FindInBucket_00421300(
        AnimationLookupNode_00421300* node, int handle) {
    for (; node != 0; node = node->next) {
        AnimationObject_00421300* const object =
            static_cast<AnimationObject_00421300*>(node->object);
        if (object->script_handle == handle)
            return object;
    }
    return 0;
}

AnimationObject_00421300* FindAnimationObject_00421300(
        AnimationLookupContext_00421300* context, int handle) {
    if (handle == 0)
        return 0;

    AnimationObject_00421300* object =
        FindInBucket_00421300(context->primary_bucket, handle);
    if (object != 0)
        return object;
    return FindInBucket_00421300(context->secondary_bucket, handle);
}

void MarkAnimationObject_00421300(AnimationObject_00421300* object) {
    object->release_state = 2;
    if (object->children_already_flagged == 0) {
        for (AnimationLookupNode_00421300* child = object->children;
             child != 0; child = child->next) {
            static_cast<AnimationObject_00421300*>(child->object)->release_state = 2;
        }
    }
}

void MarkHandle_00421300(AnimationLookupContext_00421300* context, int handle) {
    AnimationObject_00421300* const object =
        FindAnimationObject_00421300(context, handle);
    if (object != 0)
        MarkAnimationObject_00421300(object);
}

} // namespace

extern "C" __declspec(noinline) void __stdcall ReleaseAnimationHandles_00421300(
        void* control_block) {
    AnimationReleaseControl_00421300* const control =
        static_cast<AnimationReleaseControl_00421300*>(control_block);

    if (control->state == 1) {
        AnimationLookupContext_00421300* const context =
            data_00491c10;

        MarkHandle_00421300(context, data_00477824);
        MarkHandle_00421300(context, data_00477828);
        MarkHandle_00421300(context, data_0047782c);

        data_00477824 = 0;
        data_00477828 = 0;
        data_0047782c = 0;
        control->state = 2;
    }

    if (data_00491bec != 0)
        data_00491bec = 0;
}
