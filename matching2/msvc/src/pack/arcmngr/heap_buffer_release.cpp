#include "th10/source_views/heap_0e4835_0.hpp"
void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data != 0) {
        crt_free(data);
        buffer->data = 0;
    }
}
