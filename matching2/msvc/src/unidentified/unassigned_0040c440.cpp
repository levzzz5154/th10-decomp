
extern "C" void* __stdcall find_opaque_004491c0(unsigned int id);
extern "C" char* data_00491c10;

struct AnimationNode_0040c440 {
    AnimationNode_0040c440* object;
    AnimationNode_0040c440* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode_0040c440* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

struct AnimationHandle_0040c440 { unsigned short id; };

__declspec(noinline) void StopHandleAnchor_00409e50(AnimationHandle_0040c440* handle);

struct Entity_0040c440 {
    unsigned char pad_000[0x89A4];
    unsigned int handle;
    __declspec(noinline) void StopHandleAndClear();
};

#pragma code_seg(".text$03stop")
void Entity_0040c440::StopHandleAndClear() {
    AnimationHandle_0040c440* handle = (AnimationHandle_0040c440*)&this->handle;
    StopHandleAnchor_00409e50(handle);
    this->handle = 0;
}
#pragma code_seg()
