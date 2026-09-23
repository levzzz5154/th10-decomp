// Compiler context only; never selected as recovered game code.
#include "../../src/platform/resource_file.cpp"

#pragma code_seg(".text$03context")
int __stdcall PackedColorFillCompilerContext(
        PackedColorBuffer_00436CA0** buffers,
        const unsigned int* colors,
        int count) {
    while (count-- > 0) {
        PackedColorBuffer_00436CA0* buffer = *buffers++;
        buffer->Fill(*colors++);
    }
    return 0;
}
#pragma code_seg()
