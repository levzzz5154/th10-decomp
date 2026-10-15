// 0x0044CBB0..0x0044CBE1 (50 bytes): scalar deleting destructor.
//
// When the object's +0x78 word is one, the body closes the handle held at
// +0x8C through the kernel32 import the image keeps at 0x004660CC and stamps
// -1 over it; when bit 0 of the incoming flags is set it then hands the object
// to the CRT free entry at 0x004524A1 and returns the object in EAX. The object
// arrives in ESI, a receiver no C++ declaration names, so the body is compiled
// in the native-LTCG cluster build_support/layout/ltcg/dtor_delete_0044cbb0.json whose
// array-walking synthetic caller establishes that convention.

extern "C" void __cdecl entry_free_004524a1(void* block);
extern "C" void (__stdcall* data_004660cc)(void* handle);

struct Deletable_0044cbb0 {
    unsigned char unknown_0000[0x78];
    int field_78;                       // +0x78
    unsigned char unknown_07c[0x8C - 0x7C];
    int field_8C;                       // +0x8C
};

__declspec(noinline) void* Deletable_0044cbb0_Delete(Deletable_0044cbb0* object, int flags);

#pragma code_seg(".text$01del")
void* Deletable_0044cbb0_Delete(Deletable_0044cbb0* object, int flags) {
    if (object->field_78 == 1) {
        data_004660cc((void*)object->field_8C);
        object->field_8C = -1;
    }
    if ((flags & 1) != 0) {
        entry_free_004524a1(object);
    }
    return object;
}
#pragma code_seg()
