// 0x00448E30..0x00448E78: create an animation object and prepend it to the
// manager's primary-front list.
struct AnimationObject_00448e30 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;
    unsigned char reserved_024[0x35C - 0x24];
    unsigned int flags_035c;
};

struct AnimationResource_00449870 {
    void* __declspec(noinline) InitializeObject(void* object, int index);
};

extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50(
    void* manager, void** out, void* entity);

#pragma code_seg(".text$05aa_front")
__declspec(noinline)
void** __stdcall AnimationManager_CreatePrimaryFront_00448e30(
        void* resource, void** out, int index, int render_bucket) {
    AnimationObject_00448e30* object =
        (AnimationObject_00448e30*)asm_FUN_00449950_00449950(g_sprt_ctrl);
    unsigned int flags = object->flags_035c;
    object->render_bucket_020 = render_bucket;
    object->flags_035c = flags | 0x40000000u;
    ((AnimationResource_00449870*)resource)->InitializeObject(object, index);
    asm_AnimationManager_RegisterPrimaryFront_00448a50(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg()
