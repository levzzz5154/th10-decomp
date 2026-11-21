extern "C" void* __cdecl crt_heap_alloc(unsigned int);
extern "C" int __cdecl crt_callnewh(unsigned int);

extern "C" void* __cdecl crt_nh_malloc(unsigned int size, int retry) {
    if (size <= 0xffffffe0u) {
        do {
            void* block = crt_heap_alloc(size);
            if (block || !retry) return block;
        } while (crt_callnewh(size));
    }
    return 0;
}
