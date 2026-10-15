// Signed-index byte-table flag reader. Native LTCG supplies the private register ABI.
#pragma code_seg(".text$01byte")
extern "C" __declspec(noinline) unsigned int __stdcall ReadSignedByteFlag(short index, const signed char* table, unsigned short* output, unsigned short bit) {
    if (index >= 0) {
        const signed char* entry = table + index;
        *output |= (*entry & 0x80) != 0 ? bit : 0;
        // Read again after the word write: table and output may overlap.
        if ((*entry & 0x80) != 0) return bit;
    }
    return 0;
}
#pragma code_seg()

// Signed-index mask flag reader. The pinned MSVC x86 compiler emits SHL CL,
// whose native behavior masks the shift count to five bits. This source is
// tied to that compiler/target, including mapped indices greater than 31.
#pragma code_seg(".text$03mask")
extern "C" __declspec(noinline) unsigned int __stdcall ReadSignedMaskFlag(short index, unsigned int mask, unsigned short* output, unsigned short bit) {
    if (index >= 0) {
        unsigned int selected = (1u << index) & mask;
        *output |= selected ? bit : 0;
        if (selected) return bit;
    }
    return 0;
}
#pragma code_seg()
