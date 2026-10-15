// 0x00448FB0..0x0044900E (95 bytes): create a positioned animation object and
// append it to the manager's secondary-back list.
//
// The body takes the object out of the manager's animation pool, marks it
// positioned (bit 30 of the +0x35C flag word), clears its render bucket at
// +0x20, copies the caller's 12-byte position record into +0x340, loads the
// script for the requested index, and hands the object to the secondary-back list
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
// with the resource in ECX and the index in EBX, and 0x00448AC0 reads the
// manager from EDX, the entity from EBX and the handle record from EAX.  Only
// a native /LTCG link that can see the callees' bodies assigns those
// registers, so the region is compiled in the cluster
// layout/ltcg/positioned_secondary_back_00448fb0.json, whose driver carries a
// compiled ABI anchor for each of the three - placed at the retail address,
// resolving the call displacements without a relocation, and never exported as
// recovered code.
#pragma code_seg(".text$05positionedsecondaryback")

struct AnimationPosition_00448fb0 {
    float x;
    float y;
    float z;
};

// The animation object this region fills in; only the fields it writes are
// described.
struct AnimationObject_00448fb0 {
    unsigned char reserved_000[0x20];
    int render_bucket_020;                          // +0x20
    unsigned char reserved_024[0x340 - 0x24];
    AnimationPosition_00448fb0 position_340;        // +0x340
    unsigned char reserved_34c[0x35C - 0x34C];
    unsigned int flags_035c;                        // +0x35C
};

extern "C" void* data_00491c10;
extern "C" void* __cdecl asm_FUN_00449950_00449950(void* manager);
extern "C" void __cdecl asm_AnimationObject_LoadScript_0043e710(
    void* resource, void* object, int index);
// The secondary-back registration, spelled with the handle record retail keeps in
// EAX second: it is the object the assigned id is written to, while the entity
// in EBX is the one whose embedded node is linked.
extern "C" void** __cdecl asm_AnimationManager_RegisterSecondaryBack_00448ac0(
    void* manager, void** out, void* entity);

// noinline: the whole-program pass must keep this body as its own contribution
// at 0x00448FB0 instead of inlining it into the synthetic caller.
__declspec(noinline)
void** __stdcall AnimationManager_CreatePositionedSecondaryBack_00448fb0(
    void* resource, void** out, int index, const AnimationPosition_00448fb0* position) {
    AnimationObject_00448fb0* object =
        (AnimationObject_00448fb0*)asm_FUN_00449950_00449950(data_00491c10);
    object->flags_035c |= 0x40000000u;
    object->render_bucket_020 = 0;
    object->position_340 = *position;
    asm_AnimationObject_LoadScript_0043e710(resource, object, index);
    asm_AnimationManager_RegisterSecondaryBack_00448ac0(data_00491c10, out, object);
    return out;
}
#pragma code_seg()
