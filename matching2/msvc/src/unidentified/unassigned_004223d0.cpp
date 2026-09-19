// 0x004223d0..0x004223E2 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x00422220 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// layout/ltcg/dtor_release_004223d0.json whose array-walking synthetic caller establishes
// that convention.

extern "C" void Cleanup_00422220(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Releasable_004223d0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Releasable_004223d0_Release(Releasable_004223d0* object);

#pragma code_seg(".text$01rel")
void Releasable_004223d0_Release(Releasable_004223d0* object) {
    if (object != 0) {
        Cleanup_00422220(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
