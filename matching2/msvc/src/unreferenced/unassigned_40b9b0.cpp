// 0x0040B9B0..0x0040B9CB (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x0040B7B0 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/dtor_delete_40b9b0.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_FUN_0040b7b0_0040b7b0(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Deletable8 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_0040b9b0_Delete(Deletable8* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0040b9b0_Delete(Deletable8* object, int flags) {
    asm_FUN_0040b7b0_0040b7b0(object);
    if ((flags & 1) != 0) {
        crt_free_startup(object);
    }
    return object;
}
#pragma code_seg()
