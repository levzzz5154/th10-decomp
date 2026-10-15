// 0x004014B0..0x004014C2 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x00401260 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_release_004014b0.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_DestroyGameThread_00401260(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Destroyable_004014b0 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_004014b0_Release(Destroyable_004014b0* object);

#pragma code_seg(".text$01rel")
void Destroyable_004014b0_Release(Destroyable_004014b0* object) {
    if (object != 0) {
        asm_DestroyGameThread_00401260(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
