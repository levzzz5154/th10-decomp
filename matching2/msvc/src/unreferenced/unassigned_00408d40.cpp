// 0x00408D40..0x00408D52 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x00408AF0 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_release_00408d40.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void asm_FUN_00408af0_00408af0(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Destroyable_00408d40 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_00408d40_Release(Destroyable_00408d40* object);

#pragma code_seg(".text$01rel")
void Destroyable_00408d40_Release(Destroyable_00408d40* object) {
    if (object != 0) {
        asm_FUN_00408af0_00408af0(object);
        crt_free_startup(object);
    }
}
#pragma code_seg()
