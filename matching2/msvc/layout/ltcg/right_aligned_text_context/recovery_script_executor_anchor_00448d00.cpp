// 0x00448D00..0x00448D48: create an animation object and append it to the
// manager's primary-back list.
struct AnimationObject_00448d00 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;
    unsigned char reserved_024[0x35C - 0x24];
    unsigned int flags_035c;
};

struct AnimationResource_00449870 {
    void* __declspec(noinline) InitializeObject(void* object, int index);
};

extern "C" void* data_00491c10;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* entity);

#pragma code_seg(".text$00448d00_fn")
__declspec(noinline)
void** __stdcall AnimationManager_CreatePrimaryBack_00448d00(
        void* resource, void** out, int index, int render_bucket) {
    AnimationObject_00448d00* object =
        (AnimationObject_00448d00*)asm_FUN_00449950_00449950(data_00491c10);
    unsigned int flags = object->flags_035c;
    object->render_bucket_020 = render_bucket;
    object->flags_035c = flags | 0x40000000u;
    ((AnimationResource_00449870*)resource)->InitializeObject(object, index);
    asm_AnimationManager_RegisterPrimaryBack_004489d0(data_00491c10, out, object);
    return out;
}
#pragma code_seg()
