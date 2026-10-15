// 0x0040C540..0x0040C58A (75 bytes): arm the game thread's animation handle.
//
// The body builds the twelve-byte position record from its two float
// arguments, returns early when the cached handle at +0x89A4 is already armed,
// and otherwise asks the animation manager's positioned-primary creation
// (0x00448D50) for a new object, storing the handle it returns through the
// caller-supplied out slot at +0x89A4.  The function returns that handle, which
// is what the whole-program pass keeps in EAX across the tail.
//
// Retail enters this body with the game thread in ESI (a register no MSVC
// declaration names for a member function), so the region is compiled in the
// cluster build_support/layout/ltcg/lazy_animation_resource_0040c540_wave11.json.  Its driver
// carries the compiled body of 0x00448D50 as an ABI anchor - retail hands that
// callee the position record in **EDI**, which only a native /LTCG link that
// can see the callee's body assigns - together with the three callees
// 0x00448D50 itself needs (0x00449950 manager in ESI, 0x0043E710 resource in
// ECX / object in EAX / index in EBX, 0x004489D0 manager in EDX / entity in EBX
// / handle record in EAX).  The anchors are placed at their retail addresses
// and are never exported as recovered code.
//
// The tail pins the register too: with the handle declared as a consumed
// temporary that is then assigned to the live member, no value is live in EAX
// at the end of the body and the backend picks ECX for the load
// (`mov (%eax),%ecx; mov %ecx,0x89a4(%esi)`), two bytes away from retail.  With
// the handle returned instead, the pass has to leave it in EAX and emits
// retail's own `mov (%eax),%eax; mov %eax,0x89a4(%esi)`.
#pragma code_seg(".text$01lazy")

// The twelve-byte position record handed to the animation manager (the same
// record 0x00448D50 fills into the object at +0x340).
struct AnimationPosition_00448d50 {
    float x;
    float y;
    float z;
};

struct GameThread_0040c540 {
    unsigned char reserved_0000[0x8994];
    void* animation_resource;                       // +0x8994
    unsigned char reserved_8998[0x89A4 - 0x8998];
    void* animation_handle;                         // +0x89A4
    __declspec(noinline) void* EnsureAnimationResource(float x, float y);
};

// The animation manager's positioned-primary creation, recovered at
// 0x00448D50; the cluster driver carries its compiled body as an ABI anchor.
void** __stdcall AnimationManager_CreatePositionedPrimary_00448d50(
    void* resource, void** out, int index,
    const AnimationPosition_00448d50* position);

__declspec(noinline)
void* GameThread_0040c540::EnsureAnimationResource(float x, float y) {
    AnimationPosition_00448d50 position;
    position.x = x;
    position.y = y;
    position.z = 0.0f;
    if (animation_handle != 0) {
        return animation_handle;
    }
    void* handle;
    void** slot = AnimationManager_CreatePositionedPrimary_00448d50(
        animation_resource, &handle, 6, &position);
    animation_handle = *slot;
    return animation_handle;
}
#pragma code_seg()
