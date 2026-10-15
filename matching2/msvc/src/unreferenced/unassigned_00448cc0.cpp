// 0x00448CC0..0x00448CF1 (50 bytes): scalar deleting destructor.
//
// The body releases the pointer held at +0x358 through the CRT free entry at
// 0x00452422, clears the field, and -- when bit 0 of the incoming flags is set
// -- hands the object itself to the CRT free entry at 0x004524A1, returning the
// object in EAX. The object arrives in ESI, a receiver no C++ declaration
// names, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/dtor_delete_00448cc0.json whose array-walking synthetic caller
// establishes that convention.

extern "C" void __cdecl entry_free_00452422(void* block);
extern "C" void __cdecl entry_free_004524a1(void* block);

struct Deletable_00448cc0 {
    unsigned char unknown_0000[0x358];
    void* field_358;                    // +0x358
};

__declspec(noinline) void* Deletable_00448cc0_Delete(Deletable_00448cc0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_00448cc0_Delete(Deletable_00448cc0* object, int flags) {
    if (object->field_358 != 0) {
        entry_free_00452422(object->field_358);
    }
    object->field_358 = 0;
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
