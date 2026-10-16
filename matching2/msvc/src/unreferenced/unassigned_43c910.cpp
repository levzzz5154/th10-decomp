// 0x0043C910..0x0043C921 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x0043CB00 (the callee takes the object as a stack argument and cleans it,
// RET 4) and hands the object to the CRT free entry at 0x004524A1. The object
// lives in ESI, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_release_43c910.json whose array-walking synthetic caller
// establishes that convention.

extern "C" void asm_Recovery_ReleaseRawPair_0043cb00(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Destroyable6 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_0043c910_Release(Destroyable6* object);

#pragma code_seg(".text$01rel")
void Destroyable_0043c910_Release(Destroyable6* object) {
    if (object != 0) {
        asm_Recovery_ReleaseRawPair_0043cb00(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
