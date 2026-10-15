struct CrtLookupPair { unsigned int key; unsigned int value; };
extern "C" CrtLookupPair g_crt_lcid_lookup[20];

// 0x00459075..0x0045909E: Find a key in the CRT lookup table.
extern "C" unsigned int __cdecl asm_unassigned_00459075(unsigned int key) {
    unsigned int index = 0;
    while (index < 19 && key != g_crt_lcid_lookup[index].key)
        ++index;
    if (key == g_crt_lcid_lookup[index].key)
        return g_crt_lcid_lookup[index].value;
    return 0;
}
