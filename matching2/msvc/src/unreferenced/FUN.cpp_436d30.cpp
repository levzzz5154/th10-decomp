#include "../../build_support/include/asm_symbols.hpp"

// 0x00436D30..0x00436D5D: accumulate one enabled RGB record.
struct ColorAccumulator {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

struct ColorRecord {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char enabled;
};

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) void __cdecl asm_FUN_00436d30_00436d30(
        ColorAccumulator *result,
        unsigned int *count,
        const ColorRecord *record) {
    if (record->enabled != 0) {
        result->red += record->blue;
        result->green += record->green;
        result->blue += record->red;
        ++*count;
    }
}
#pragma code_seg()
