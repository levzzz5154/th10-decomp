// 0x0042BDD0..0x0042BE08 (56 bytes): scalar deleting destructor with a vtable
// republish.
//
// Retail reads the owned block pointer at +0x8C first, republishes the class
// vtable at +0x00, releases the block through the CRT entry at 0x00452422 and
// clears the field, then -- when bit 0 of the incoming flags is set -- hands
// the object itself to the CRT free entry at 0x004524A1, and finally returns
// the object in EAX.  The object lives in ESI across both calls, a receiver no
// C++ declaration names, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/disposable_destroy_0042bdd0.json whose array-walking synthetic
// caller establishes that convention.
//
// The vtable address is taken through an array declaration, which is the shape
// that stores the absolute address the manifest binds for 0x0046D0F0.

extern "C" char g_enemy_eff_vtable[];
extern "C" void __cdecl entry_free_00452422(void* block);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Disposable_0042bdd0 {
    void* vtable;                          // +0x00
    unsigned char unknown_04[0x88];
    void* block;                           // +0x8C
};

__declspec(noinline) void* Disposable_0042bdd0_Destroy(Disposable_0042bdd0* object, int flags);

#pragma code_seg(".text$01del")
void* Disposable_0042bdd0_Destroy(Disposable_0042bdd0* object, int flags) {
    void* block = object->block;
    object->vtable = g_enemy_eff_vtable;
    if (block != 0) {
        entry_free_00452422(block);
        object->block = 0;
    }
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
