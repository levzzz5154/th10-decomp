struct CrtWordPair { unsigned int key; unsigned int value; };
extern "C" CrtWordPair g_crt_wctype_pairs[29];

// 0x0045E894..0x0045E8B3: Look up a CRT key in the 29-entry table.
extern "C" unsigned int __cdecl asm_unassigned_0045e894(unsigned int key) {
    for (int index = 0; index < 29; ++index) {
        if (g_crt_wctype_pairs[index].key == key)
            return g_crt_wctype_pairs[index].value;
    }
    return 0;
}
