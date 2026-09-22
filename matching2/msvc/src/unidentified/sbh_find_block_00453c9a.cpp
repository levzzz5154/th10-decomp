struct CrtHeapBlock { unsigned char prefix[12]; unsigned int base; unsigned char tail[4]; };
extern "C" unsigned int data_00499328;
extern "C" CrtHeapBlock* data_0049932c;

// 0x00453C9A..0x00453CC4: Find the heap block containing an address.
extern "C" CrtHeapBlock* __cdecl asm_sbh_find_block_00453c9a(unsigned int address) {
    CrtHeapBlock* end = data_0049932c + data_00499328;
    CrtHeapBlock* current = data_0049932c;
    while (current < end) {
        if (address - current->base < 0x100000) return current;
        ++current;
    }
    return 0;
}
