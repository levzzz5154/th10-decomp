// 0x00449140..0x004491B5 (118 bytes): create an animation object at a
// playfield position and prepend it to the secondary-front list.
//
// The twin of 0x004490E0, except that the caller's position is in playfield
// coordinates: the playfield origin sits at (224, 16) on screen, so x and y are
// shifted by that before the record is stored at +0x340.
//
// Like its twin, the body enters with the position in EDI and the other three
// arguments on the stack, and its callees take registers no declaration can
// name, so it is compiled in the cluster layout/ltcg/positioned_secondary_front_004490e0.json.
#pragma code_seg(".text$05qscreen")

struct AnimationPosition_00449140 {
    float x;
    float y;
    float z;
};

// The animation object this region fills in; only the fields it writes are
// described.
struct AnimationObject_00449140 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition_00449140 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                       // +0x35C
};

extern "C" void* data_00491c10;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void __cdecl asm_AnimationObject_LoadScript_0043e710(
    void* resource, void* object, int index);
extern "C" void** __cdecl asm_AnimationManager_RegisterSecondaryFront_00448b40(
    void* manager, void** out, void* entity);

enum { kAnimationPositioned = 0x40000000 };

__declspec(noinline)
void** __stdcall AnimationManager_CreateScreenPositionedSecondaryFront_00449140(
    void* resource, void** out, int index, const AnimationPosition_00449140* position) {
    AnimationObject_00449140* object =
        (AnimationObject_00449140*)asm_FUN_00449950_00449950(data_00491c10);
    unsigned int flags = *(volatile unsigned int*)&object->flags_035c;
    *(volatile int*)&object->render_bucket_020 = 0;
    *(volatile unsigned int*)&object->flags_035c = flags | kAnimationPositioned;
    object->position_340.x = position->x + 224.0f;
    object->position_340.y = position->y + 16.0f;
    object->position_340.z = position->z;
    asm_AnimationObject_LoadScript_0043e710(resource, object, index);
    asm_AnimationManager_RegisterSecondaryFront_00448b40(data_00491c10, out, object);
    return out;
}
#pragma code_seg()
