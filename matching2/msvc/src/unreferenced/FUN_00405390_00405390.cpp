// 0x00405390. Read the dword at +0x4 of the object handed in EAX.
//
//   L_00405390: mov eax,dword ptr [eax+4]   ; 8b 40 04
//               ret                         ; c3
//
// The accessor sits in the same 16-byte-slot table as 0x00405360 and is only
// reached indirectly in retail, so the field's role is unknown; the object is
// the one whose +0x8 pointer 0x00405300 calls a vtable slot through. The body
// is compiled in the native LTCG cluster of build_support/layout/ltcg/object_field04_getter.json
// so MSVC keeps the argument and the result in EAX.

struct ManagedObject {
    unsigned char unknown_00[4];
    int field_04;   // +0x04
};

__declspec(noinline) int ManagedObject_GetField04(ManagedObject* object);

#pragma code_seg(".text$01get")
int ManagedObject_GetField04(ManagedObject* object) {
    return object->field_04;
}
#pragma code_seg()
