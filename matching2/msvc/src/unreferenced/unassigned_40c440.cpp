
extern "C" void* __stdcall find_opaque(unsigned int id);
extern "C" char* g_sprt_ctrl;

struct AnimationNode3 {
    AnimationNode3* object;
    AnimationNode3* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode3* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

struct AnimationHandle4 { unsigned short id; };

__declspec(noinline) void StopHandleAnchor2(AnimationHandle4* handle);

struct Entity2 {
    unsigned char pad_000[0x89A4];
    unsigned int handle;
    __declspec(noinline) void StopHandleAndClear();
};

#pragma code_seg(".text$03stop")
void Entity2::StopHandleAndClear() {
    AnimationHandle4* handle = (AnimationHandle4*)&this->handle;
    StopHandleAnchor2(handle);
    this->handle = 0;
}
#pragma code_seg()
