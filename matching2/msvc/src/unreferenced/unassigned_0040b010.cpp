// 0x0040B010..0x0040B022 (18 bytes): release a possibly-absent object.
//
// Retail answers a null object immediately; otherwise it runs the cleanup at
// 0x0040AF00 (the callee takes the object as a stack argument and cleans it,
// RET 4), hands the object to the CRT free entry at 0x004524A1 and returns.
// The object lives in ESI, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_release_0040b010.json whose array-walking synthetic caller establishes that
// convention.

extern "C" void __stdcall asm_BulletManager_Release_0040af00(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Destroyable_0040b010 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void Destroyable_0040b010_Release(Destroyable_0040b010* object);

#pragma code_seg(".text$01rel")
void Destroyable_0040b010_Release(Destroyable_0040b010* object) {
    if (object != 0) {
        asm_BulletManager_Release_0040af00(object);
        entry_free_004524a1(object);
    }
}
#pragma code_seg()
