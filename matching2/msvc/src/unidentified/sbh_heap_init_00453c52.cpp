#include "asm_symbols.hpp"

// Semantic model for 0x00453C52..0x00453C99 (___sbh_heap_init).
typedef void* (__stdcall *HeapAllocFn_00453c52)(void* heap, unsigned int flags,
                                                unsigned int bytes);

extern "C" int __cdecl asm_sbh_heap_init_00453c52(unsigned int size) {
    HeapAllocFn_00453c52 heap_alloc =
        *(HeapAllocFn_00453c52*)&data_004661e4;
    void* heap = *(void**)&data_00499340;
    void* table = heap_alloc(heap, 0, 0x140);

    *(void**)&data_0049932c = table;
    if (table == 0) {
        return 0;
    }

    *(unsigned int*)&data_00499324 = 0;
    *(unsigned int*)&data_00499328 = 0;
    *(void**)&data_00499334 = table;
    *(unsigned int*)&data_00499330 = size;
    *(unsigned int*)&data_00499338 = 0x10;
    return 1;
}
