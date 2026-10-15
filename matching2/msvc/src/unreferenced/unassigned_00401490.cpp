// 0x00401490..0x004014AB (27 bytes): scalar deleting destructor.
//
// Retail runs the object cleanup at 0x00401260 -- the callee takes the object
// as a stack argument and cleans it (RET 4) -- then, when bit 0 of the incoming
// flags is set, hands the object to the CRT free entry at 0x004524A1, and
// finally returns the object in EAX.  The object lives in ESI across both calls,
// a receiver no C++ declaration names, so the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/dtor_delete_00401490.json whose array-walking synthetic
// caller establishes that convention.

extern "C" void asm_DestroyGameThread_00401260(void* object);
extern "C" void __cdecl crt_free_startup(void* block);

struct Deletable_00401490 {
    unsigned char unknown_0000[0x04];
};

__declspec(noinline) void* Deletable_00401490_Delete(Deletable_00401490* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00401490_Delete(Deletable_00401490* object, int flags) {
    asm_DestroyGameThread_00401260(object);
    if ((flags & 1) != 0) {
        crt_free_startup(object);
    }
    return object;
}
#pragma code_seg()
