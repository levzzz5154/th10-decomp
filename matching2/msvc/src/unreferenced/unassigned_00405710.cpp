// 0x00405710..0x0040572B (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00405620 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/dtor_delete_00405710.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void __stdcall asm_Recovery_ReleaseRawPairAndReset_00405620(void* object);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00405710 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_00405710_Delete(Deletable_00405710* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00405710_Delete(Deletable_00405710* object, int flags) {
    asm_Recovery_ReleaseRawPairAndReset_00405620(object);
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
