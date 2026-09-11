// 0x00404D40: component-wise difference of two six-float records, with the
// result's four channel bytes derived from its last four components.
//
// Retail: D9 41 14 / D8 60 14   fld [ecx+0x14]; fsub [eax+0x14]
//         ... six differences, pushed back to front
//         D9 1E / D9 5E 04      fstp [esi]; fstp [esi+4]
//         D9 56 08              fst  [esi+8]
//         D9 C1 / D9 5E 0C      fld st(1); fstp [esi+0xC]
//         D9 C2 / D9 5E 10      fld st(2); fstp [esi+0x10]
//         D9 C3 / D9 5E 14      fld st(3); fstp [esi+0x14]
//         E8 .. / 88 46 18      call __ftol2; mov [esi+0x18],al   (x4, channels)
//         8B C6                 mov eax,esi
//         C3                    ret
// The left operand arrives in ECX, the right in EAX and the result in ESI, so
// the subtraction is compiled as a native LTCG cluster.
// Carved out of src/math/math_utils.cpp (asm_Vec_Subtract_00404d40).

struct VecSubtractOperand {
    float values[6];
};

struct VecSubtractResult {
    float values[6];
    unsigned char channels[4];
};

#pragma code_seg(".text$01vecsubtract")
__declspec(noinline) VecSubtractResult* Vec_Subtract(const VecSubtractOperand* left,
                                                     const VecSubtractOperand* right,
                                                     VecSubtractResult* result) {
    // The six differences are computed last-to-first: retail's x87 pushes run
    // back to front, and only that order keeps all six in registers.
    float value5 = left->values[5] - right->values[5];
    float value4 = left->values[4] - right->values[4];
    float value3 = left->values[3] - right->values[3];
    float value2 = left->values[2] - right->values[2];
    float value1 = left->values[1] - right->values[1];
    float value0 = left->values[0] - right->values[0];
    result->values[0] = value0;
    result->values[1] = value1;
    result->values[2] = value2;
    result->values[3] = value3;
    result->values[4] = value4;
    result->values[5] = value5;
    result->channels[0] = (unsigned char)value2;
    result->channels[1] = (unsigned char)value3;
    result->channels[2] = (unsigned char)value4;
    result->channels[3] = (unsigned char)value5;
    return result;
}
#pragma code_seg()
