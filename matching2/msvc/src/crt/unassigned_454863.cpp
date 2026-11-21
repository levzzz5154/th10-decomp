extern "C" unsigned int g_crt_heap_type;
extern "C" unsigned int g_crt_heap_size_copy;
extern "C" int __cdecl crt_sbh_heap_init(unsigned int size);

extern "C" int __cdecl crt_unassigned_454863(unsigned int size) {
    if (g_crt_heap_type == 3) {
        if (size <= 0x3F8) {
            g_crt_heap_size_copy = size;
            return 1;
        }
        return 0;
    }
    if (g_crt_heap_type == 1 && size > 0 && size <= 0x3F8 && crt_sbh_heap_init(size)) {
        g_crt_heap_size_copy = size;
        g_crt_heap_type = 3;
        return 1;
    }
    return 0;
}
