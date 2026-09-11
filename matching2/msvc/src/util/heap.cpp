#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/util/heap.hpp"




// Recovered semantic C++ definitions.

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void __cdecl entry_free_004524a1(void*);
#ifdef _MSC_VER
void* __cdecl operator new(uint32_t size);
#else
void* operator new(decltype(sizeof(0)) size);
#endif

HeapBuffer::HeapBuffer() : data(0) {
}

void* LegacyAllocator::Allocate(uint32_t count) {
    return ::operator new(count);
}

void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    entry_free_004524a1(memory);
}

uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
}

void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data != 0) {
        entry_free_00452422(data);
        buffer->data = 0;
    }
}
