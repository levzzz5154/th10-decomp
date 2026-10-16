struct CrtHeapBlock { unsigned char prefix[12]; unsigned int base; unsigned char tail[4]; };
extern "C" unsigned int g_crt_heap_size;
extern "C" CrtHeapBlock* g_crt_heap_head;

// 0x00453C9A..0x00453CC4: Find the heap block containing an address.
extern "C" CrtHeapBlock* __cdecl asm_sbh_find_block_00453c9a(unsigned int address) {
    CrtHeapBlock* end = g_crt_heap_head + g_crt_heap_size;
    CrtHeapBlock* current = g_crt_heap_head;
    while (current < end) {
        if (address - current->base < 0x100000) return current;
        ++current;
    }
    return 0;
}
