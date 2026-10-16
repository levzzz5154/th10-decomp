// 0x00449FE0..0x00449FFF (32 bytes): scalar deleting destructor.
//
// The body clears the three tail words of the object and, when bit 0 of the
// incoming flags is set, hands the object to the CRT free entry at 0x004524A1,
// returning the object in EAX. The object arrives in ESI, a receiver no C++
// declaration names, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_delete_449fe0.json whose array-walking synthetic caller
// establishes that convention.

extern "C" void __cdecl crt_free_startup(void* block);

struct Deletable17 {
    unsigned char unknown_0000[0x08];
    int field_08;   // +0x08
    int field_0C;   // +0x0C
    int field_10;   // +0x10
};

__declspec(noinline) void* Deletable_00449fe0_Delete(Deletable17* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00449fe0_Delete(Deletable17* object, int flags) {
    object->field_08 = 0;
    object->field_0C = 0;
    object->field_10 = 0;
    if ((flags & 1) != 0) {
        crt_free_startup(object);
    }
    return object;
}
#pragma code_seg()
