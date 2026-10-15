// 0x0042b6b0..0x0042B6CB (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x0042b570 -- the callee takes the object as
// a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both
// calls, a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/dtor_delete_0042b6b0.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void Cleanup_0042b570(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Deletable_0042b6b0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0042b6b0_Delete(Deletable_0042b6b0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0042b6b0_Delete(Deletable_0042b6b0* object, int flags) {
    Cleanup_0042b570(object);
    if ((flags & 1) != 0) {
        crt_free_startup(object);
    }
    return object;
}
#pragma code_seg()
