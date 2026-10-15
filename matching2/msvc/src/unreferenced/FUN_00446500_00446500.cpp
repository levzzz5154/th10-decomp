#include "../../build_support/include/asm_symbols.hpp"

// 0x00446500..0x0044652D: accumulate one enabled RGB record.
struct ColorAccumulator_00446500 {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

struct ColorRecord_00446500 {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char enabled;
};

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) void __cdecl asm_FUN_00446500_00446500(
        ColorAccumulator_00446500 *result,
        unsigned int *count,
        const ColorRecord_00446500 *record) {
    if (record->enabled != 0) {
        result->red += record->blue;
        result->green += record->green;
        result->blue += record->red;
        ++*count;
    }
}
#pragma code_seg()
