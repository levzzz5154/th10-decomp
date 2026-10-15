
extern "C" void* __stdcall find_opaque_004491c0(unsigned int id);
extern "C" char* g_sprt_ctrl;

struct AnimationNode_00417720 {
    AnimationNode_00417720* object;
    AnimationNode_00417720* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode_00417720* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

struct AnimationHandle_00417720 {
    unsigned short id;
};

__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_00417720* handle);

struct Entity_00417720 {
    unsigned char pad_000[0x9E14];
    AnimationHandle_00417720 handle;
    __declspec(noinline) void StopHandle();
};

#pragma code_seg(".text$03stop")
void Entity_00417720::StopHandle() {
    StopHandleAnchor_00409e50(&this->handle);
}
#pragma code_seg()
