// 0x00428EA0..0x00428EB7: indexed two-word copy from a private LTCG ABI.
//
// The native-LTCG caller keeps this source object in ECX, the destination
// base in EDX, and the slot index in EAX.  The fixed +0x32DC anchor and 0x98
// stride are intentionally spelled out so the selected body retains retail's
// exact address arithmetic.
struct IndexedCopySource {
    unsigned int first;
    unsigned int second;

    __declspec(noinline) void Copy(void* base, int index);
};

#pragma code_seg(".text$01ea")
__declspec(noinline) void IndexedCopySource::Copy(void* base, int index) {
    unsigned char* destination =
        reinterpret_cast<unsigned char*>(base) + index * 0x98 + 0x32DC;
    *reinterpret_cast<unsigned int*>(destination) = first;
    *reinterpret_cast<unsigned int*>(destination + 4) = second;
}
#pragma code_seg()
