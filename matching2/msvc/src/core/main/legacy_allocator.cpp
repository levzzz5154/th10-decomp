#include "th10/source_views/heap_0e4835_0.hpp"
void* LegacyAllocator::Allocate(uint32_t count) {
    return ::operator new(count);
}


#include "th10/source_views/heap_0e4835_0.hpp"
void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    crt_free_startup(memory);
}


#include "th10/source_views/heap_0e4835_0.hpp"
uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
}

