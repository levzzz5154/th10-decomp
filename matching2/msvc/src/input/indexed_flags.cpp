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
