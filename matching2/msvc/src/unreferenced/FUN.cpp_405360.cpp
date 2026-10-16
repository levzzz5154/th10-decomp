// 0x00405360. Read the interface pointer stored at +0x8 of the object handed
// in EAX. Retail is three bytes of body:
//
//   L2: mov eax,dword ptr [eax+8]   ; 8b 40 08
//               ret                         ; c3
//
// The field is a vtable-bearing pointer: 0x00405300 loads it into EAX, reads
// [EAX] as the vtable and calls slot +0xBC with the slot record as the second
// argument. Plain C++ cannot name EAX, so the body is compiled as part of the
// native LTCG cluster in build_support/layout/ltcg/object_interface_getter.json, where the
// synthetic caller makes MSVC pick EAX for both the argument and the result.

struct ManagedObject {
    unsigned char unknown_04[8];
    void*         interface_08;   // +0x08, points at an object with a vtable
};

// Keeping the accessor out of line is what lets the native LTCG link keep a
// copy of its body: without it the allocator inlines it into the caller and
// the section is emitted empty.
__declspec(noinline) void* ManagedObject_GetInterface(ManagedObject* object);

#pragma code_seg(".text$01get")
void* ManagedObject_GetInterface(ManagedObject* object) {
    return object->interface_08;
}
#pragma code_seg()
