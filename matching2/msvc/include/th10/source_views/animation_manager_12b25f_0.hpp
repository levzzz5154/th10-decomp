#pragma once
#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"

// 0x0043EC70..0x0043ECFF: read an integer-valued animation variable.
struct AnimationObjectVariables {
    unsigned char reserved_000[0x30c];
    int integer_0;
    int integer_1;
    int integer_2;
    int integer_3;
    float float_0;
    float float_1;
    float float_2;
    float float_3;
    int integer_8;
    int integer_9;

    __declspec(noinline) int ReadIntegerVariable(int variable) const;
};

#pragma code_seg(".text$01readvar")
