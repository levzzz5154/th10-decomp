// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0044c080.cpp"

struct ByteRange_0044c080 {
    const unsigned char* bytes;
    int count;
};

#pragma code_seg(".text$03context")
int __stdcall ByteSumContext_0044c080(const ByteRange_0044c080* ranges, int range_count) {
    unsigned int total = 0;
    for (int index = 0; index < range_count; ++index)
        total += SumAlternateBytes_0044c080(ranges[index].bytes, ranges[index].count);
    return static_cast<int>(total);
}
#pragma code_seg()
