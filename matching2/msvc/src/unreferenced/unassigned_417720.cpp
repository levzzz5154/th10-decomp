
extern "C" void* __stdcall find_opaque(unsigned int id);
extern "C" char* g_sprt_ctrl;

struct AnimationNode5 {
    AnimationNode5* object;
    AnimationNode5* next;
    unsigned char pad_008[0x14 - 0x08];
    AnimationNode5* children;
    int children_flagged;
    unsigned char pad_01c[0x304 - 0x1C];
    unsigned short stop_frame;
};

struct AnimationHandle5 {
    unsigned short id;
};

__declspec(noinline) void StopHandleAnchor2(AnimationHandle5* handle);

struct Entity3 {
    unsigned char pad_000[0x9E14];
    AnimationHandle5 handle;
    __declspec(noinline) void StopHandle();
};

#pragma code_seg(".text$03stop")
void Entity3::StopHandle() {
    StopHandleAnchor2(&this->handle);
}
#pragma code_seg()
