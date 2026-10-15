// Compiler context only; these search records and this caller are not game
// code. Their shared uses establish the observed internal register ABI.
#pragma code_seg(".text$30context")
#include "../../../src/core/sound/resource_chunks.cpp"

struct ResourceChunkSearch {
    const unsigned char* data;
    unsigned int size;
    const unsigned char* payload;
};

#pragma code_seg(".text$30context")
void __stdcall ResourceChunkCompilerContext(ResourceChunkSearch* searches,
                                             int count, const char* tag,
                                             unsigned int* payload_size) {
    for (int index = 0; index < count; ++index) {
        searches[index].payload = Resource_FindChunk(
            searches[index].data, searches[index].size, tag, payload_size);
    }
}
#pragma code_seg()
