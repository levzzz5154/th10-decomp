extern "C" void* __cdecl asm_heap_alloc_0045265f(unsigned int);
extern "C" int __cdecl asm_callnewh_00455737(unsigned int);

extern "C" void* __cdecl asm_nh_malloc_004526da(unsigned int size, int retry) {
    if (size <= 0xffffffe0u) {
        do {
            void* block = asm_heap_alloc_0045265f(size);
            if (block || !retry) return block;
        } while (asm_callnewh_00455737(size));
    }
    return 0;
}
