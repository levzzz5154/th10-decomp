struct CrtLookupPair { unsigned int key; unsigned int value; };
extern "C" CrtLookupPair data_00473670[20];

// 0x00459075..0x0045909E: Find a key in the CRT lookup table.
extern "C" unsigned int __cdecl asm_unassigned_00459075(unsigned int key) {
    unsigned int index = 0;
    while (index < 19 && key != data_00473670[index].key)
        ++index;
    if (key == data_00473670[index].key)
        return data_00473670[index].value;
    return 0;
}
