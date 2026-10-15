extern "C" int g_crt_heap_selector;
extern "C" unsigned int g_crt_heap_rover;

extern "C" int __cdecl asm_heap_select_004539b1() {
    if (g_crt_heap_selector == 2 && g_crt_heap_rover >= 5) return 1;
    return 3;
}
