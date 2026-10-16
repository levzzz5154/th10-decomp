// 0x00448E80..0x00448EDE (95 bytes): create a positioned animation object and
// prepend it to the manager's primary list.
//
// The body is byte-for-byte the twin of 0x00448D50
// (`src/core/sprtlib/animation_manager_create_positioned_primary.cpp`); the
// only difference is the list operation it ends with.  0x00448D50 appends to
// the primary list through 0x004489D0 (RegisterPrimaryBack, tail insert), this
// one prepends through 0x00448A50 (RegisterPrimaryFront, head insert).  Its
// siblings in the manager's create family are
//   0x00448FB0  secondary back   (call 0x00448AC0)
//   0x004490E0  secondary front  (call 0x00448B40)
// so it is ?AnimationManager_CreatePositionedPrimaryFront.
//
// The body takes the object out of the manager's animation pool, marks it
// positioned (bit 30 of the +0x35C flag word), clears its render bucket at
// +0x20, copies the caller's 12-byte position record into +0x340, loads the
// script for the requested index, and hands the object to the primary-front
// registration, which assigns the handle and stores it through the caller's
// out slot; the out slot is what the function returns.
//
// Retail enters this body with the position record in EDI and the other three
// arguments on the stack, and returns with `ret 0xC` - the whole-program pass
// picks that convention for the accessor out of the synthetic caller in the
// cluster's driver, not out of a declaration.
//
// The three calls it makes enter on registers no MSVC declaration can name:
// 0x00449950 reads its manager from ESI, 0x0043E710 reads the object from EAX
// with the resource in ECX and the index in EBX, and 0x00448A50 reads the
// manager from EDX, the entity from EBX and the handle record from EAX.  Only
// a native /LTCG link that can see the callees' bodies assigns those
// registers, so the region is compiled in the cluster
// build_support/layout/ltcg/positioned_primary_front_00448e80_wave12.json, whose driver
// carries a compiled ABI anchor for each of the three - placed at the retail
// address, resolving the call displacements without a relocation, and never
// exported as recovered code.
#pragma code_seg(".text$05accessor")

struct AnimationPosition3 {
    float x;
    float y;
    float z;
};

// The animation object this region fills in; only the fields it writes are
// described.
struct AnimationObject9 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition3 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                        // +0x35C
};

extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void __cdecl asm_AnimationObject_LoadScript_0043e710(
    void* resource, void* object, int index);
// The primary-list front registration, spelled with the handle record retail
// keeps in EAX second: it is the object the assigned id is written to, while
// the entity in EBX is the one whose embedded node is linked.
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50(
    void* manager, void** out, void* entity);

// noinline: the whole-program pass must keep this body as its own contribution
// at 0x00448E80 instead of inlining it into the synthetic caller.
__declspec(noinline)
void** __stdcall AnimationManager_CreatePositionedPrimaryFront(
    void* resource, void** out, int index, const AnimationPosition3* position) {
    AnimationObject9* object =
        (AnimationObject9*)asm_FUN_00449950_00449950(g_sprt_ctrl);
    object->flags_035c |= 0x40000000u;
    object->render_bucket_020 = 0;
    object->position_340 = *position;
    asm_AnimationObject_LoadScript_0043e710(resource, object, index);
    asm_AnimationManager_RegisterPrimaryFront_00448a50(g_sprt_ctrl, out, object);
    return out;
}
#pragma code_seg()
