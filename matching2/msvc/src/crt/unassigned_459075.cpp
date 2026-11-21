struct CrtLookupPair { unsigned int key; unsigned int value; };
extern "C" CrtLookupPair crt_libcmt_crt0msg_rterrs[20];

// 0x00459075..0x0045909E: Find a key in the CRT lookup table.
extern "C" unsigned int __cdecl crt_unassigned_459075(unsigned int key) {
    unsigned int index = 0;
    while (index < 19 && key != crt_libcmt_crt0msg_rterrs[index].key)
        ++index;
    if (key == crt_libcmt_crt0msg_rterrs[index].key)
        return crt_libcmt_crt0msg_rterrs[index].value;
    return 0;
}
