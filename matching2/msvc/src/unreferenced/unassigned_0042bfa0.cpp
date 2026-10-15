// 0x0042bfa0..0x0042BFB2 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x0042bc30 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_release_0042bfa0.json whose array-walking synthetic caller establishes
// that convention.

extern "C" void Cleanup_0042bc30(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Releasable_0042bfa0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Releasable_0042bfa0_Release(Releasable_0042bfa0* object);

#pragma code_seg(".text$01rel")
void Releasable_0042bfa0_Release(Releasable_0042bfa0* object) {
    if (object != 0) {
        Cleanup_0042bc30(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
