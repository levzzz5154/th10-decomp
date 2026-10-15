// 0x0040D660..0x0040D67D (30 bytes): scalar deleting destructor.
//
// Retail hands the object to the resource release at 0x0040D680 -- that callee
// carries its object in ESI -- then, when bit 0 of the incoming flags is set,
// hands the object to the CRT free entry at 0x004524A1 and returns it in EAX.
// ESI is saved and restored around the call, so the receiver arrives in a
// caller-saved register while ESI stays a callee-saved one; no C++ declaration
// names that arrangement, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_delete_0040d660.json, whose callee is compiled into the same link as an
// ABI anchor.

extern "C" void __cdecl crt_free_startup(void* block);

struct BulletEntity_0040d680 {
    unsigned int vtable;
    unsigned char reserved_004[0x88];
    void* owned_resource;

    __declspec(noinline) void ReleaseResource();
};

struct Releaseable_0040d660 {
    unsigned char unknown_0000[0x04];

    __declspec(noinline) void* Delete(int flags);
};

#pragma code_seg(".text$01del")
void* Releaseable_0040d660::Delete(int flags) {
    ((BulletEntity_0040d680*)this)->ReleaseResource();
    if ((flags & 1) != 0) {
        crt_free_startup(this);
    }
    return this;
}
#pragma code_seg()
