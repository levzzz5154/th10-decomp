struct CrtHeapBlock { unsigned char prefix[12]; unsigned int base; unsigned char tail[4]; };
extern "C" unsigned int __sbh_cntHeaderList;
extern "C" CrtHeapBlock* g_crt_heap_head;

// 0x00453C9A..0x00453CC4: Find the heap block containing an address.
extern "C" CrtHeapBlock* __cdecl crt_sbh_find_block(unsigned int address) {
    CrtHeapBlock* end = g_crt_heap_head + __sbh_cntHeaderList;
    CrtHeapBlock* current = g_crt_heap_head;
    while (current < end) {
        if (address - current->base < 0x100000) return current;
        ++current;
    }
    return 0;
}
