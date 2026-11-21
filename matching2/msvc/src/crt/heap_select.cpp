extern "C" int g_crt_heap_selector;
extern "C" unsigned int g_crt_heap_rover;

extern "C" int __cdecl crt_heap_select() {
    if (g_crt_heap_selector == 2 && g_crt_heap_rover >= 5) return 1;
    return 3;
}
