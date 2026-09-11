// 0x00404DA0: scale a colour record by a factor and derive its four channel
// bytes from the scaled components.
//
// Retail: D9 44 24 04 / D8 48 14    fld [esp+4]; fmul [eax+0x14]
//         ... six scaled components, pushed back to front
//         D9 1E / D9 5E 04          fstp [esi]; fstp [esi+4]
//         D9 56 08                  fst  [esi+8]
//         D9 C1 / D9 5E 0C          fld st(1); fstp [esi+0xC]
//         D9 C2 / D9 5E 10          fld st(2); fstp [esi+0x10]
//         D9 C3 / D9 5E 14          fld st(3); fstp [esi+0x14]
//         E8 .. / 88 46 18          call __ftol2; mov [esi+0x18],al   (x4, channels)
//         8B C6                     mov eax,esi
//         C2 04 00                  ret 4
// The source pointer arrives in EAX and the destination in ESI, so the scaler
// is compiled as a native LTCG cluster.
// Carved out of src/game/recovery_leaves.cpp
// (asm_Recovery_ScaleColor_00404da0).

struct RecoveryScaleColorSource {
    float values[6];
};

struct RecoveryScaleColorResult {
    float values[6];
    unsigned char channels[4];
};

#pragma code_seg(".text$01scalecolor")
__declspec(noinline) RecoveryScaleColorResult* RecoveryScaleColor_Scale(
        const RecoveryScaleColorSource* source, RecoveryScaleColorResult* result, float scale) {
    // The six scaled components are computed last-to-first: retail's x87 pushes
    // run back to front, and only that order keeps all six in registers.
    float value5 = scale * source->values[5];
    float value4 = scale * source->values[4];
    float value3 = scale * source->values[3];
    float value2 = scale * source->values[2];
    float value1 = scale * source->values[1];
    float value0 = scale * source->values[0];
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
