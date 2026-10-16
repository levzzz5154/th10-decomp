// 0x004053D0. Read the dword at +0x3C of the object handed in EAX.
//
//   L4: mov eax,dword ptr [eax+3Ch]   ; 8b 40 3c
//               ret                           ; c3
//
// Same indirectly-called accessor table as 0x00405360/0x00405390; +0x3C is
// beyond the two pointers those two read. The body is compiled in the native
// LTCG cluster of build_support/layout/ltcg/object_field3c_getter.json so MSVC keeps the
// argument and the result in EAX.

struct ManagedObject {
    unsigned char unknown_04[0x3C];
    int field_3C;   // +0x3C
};

__declspec(noinline) int ManagedObject_GetField3C(ManagedObject* object);

#pragma code_seg(".text$01get")
int ManagedObject_GetField3C(ManagedObject* object) {
    return object->field_3C;
}
#pragma code_seg()
