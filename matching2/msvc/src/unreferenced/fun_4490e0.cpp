// 0x004490E0..0x0044913E: create a positioned animation and prepend it
// to the manager's secondary list. Native LTCG preserves the retail ABI.
#pragma code_seg(".text$05positionedsecondaryfront")

struct AnimationPosition7 {
    float x;
    float y;
    float z;
};

// The animation object this region fills in; only the fields it writes are
// described.
struct AnimationObject15 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition7 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                        // +0x35C
};

extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl AnimationPool_AllocateEntry(void* manager);
extern "C" void __cdecl AnmVm_LoadScript(
    void* resource, void* object, int index);
// The secondary-list front registration, spelled with the handle record retail
// keeps in EAX second: it is the object the assigned id is written to, while
// the entity in EBX is the one whose embedded node is linked.
extern "C" void** __cdecl AnimationManager_RegisterSecondaryFront(
    void* manager, void** out, void* entity);

// noinline: the whole-program pass must keep this body as its own contribution
// at 0x004490E0 instead of inlining it into the synthetic caller.
__declspec(noinline)
void** __stdcall AnimationManager_CreatePositionedSecondaryFront(
    void* resource, void** out, int index, const AnimationPosition7* position) {
    AnimationObject15* object =
        (AnimationObject15*)AnimationPool_AllocateEntry(g_sprt_ctrl);
    object->flags_035c |= 0x40000000u;
    object->render_bucket_020 = 0;
    object->position_340 = *position;
    AnmVm_LoadScript(resource, object, index);
    AnimationManager_RegisterSecondaryFront(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg()
