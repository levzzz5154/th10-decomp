#include "asm_symbols.hpp"

// 0x00436D30..0x00436D5D: accumulate one enabled RGB record.
struct ColorAccumulator_00436d30 {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

struct ColorRecord_00436d30 {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char enabled;
};

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) void __cdecl asm_FUN_00436d30_00436d30(
        ColorAccumulator_00436d30 *result,
        unsigned int *count,
        const ColorRecord_00436d30 *record) {
    if (record->enabled != 0) {
        result->red += record->blue;
        result->green += record->green;
        result->blue += record->red;
        ++*count;
    }
}
#pragma code_seg()
