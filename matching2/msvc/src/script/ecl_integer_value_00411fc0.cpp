// 0x00411FC0: integer ECL value resolver and its compiler-generated switch table.
#include <stddef.h>
#include "th10/render/animation_validate_handle_00449450.hpp"
__declspec(noinline) void* ResolveAnimationHandle(AnimationHandle_00449450* handle);
#include <math.h>

#include "th10/math/rng.hpp"

// The adjacent entry at 0x00412300 selects integer destinations from the
// same ECL object. This dispatcher reads the corresponding scalar values.
struct EclIntegerSource {
    unsigned char padding_0000[0x3C0];
    float origin_x;                         // +0x3C0
    float origin_y;                         // +0x3C4
    unsigned char padding_03c8[0xCA0];
    float value_1068;
    float value_106c;
    unsigned char padding_1070[4];
    float value_1074;
    float value_1078;
    unsigned char padding_107c[0x18];
    float value_1094;
    float value_1098;
    unsigned char padding_109c[0x10];
    float value_10ac;
    float value_10b0;
    float value_10b4;
    unsigned char padding_10b8[8];
    float value_10c0;
    float value_10c4;
    unsigned char padding_10c8[0x10];
    float value_10d8;
    float value_10dc;
    float value_10e0;
    unsigned char padding_10e4[0x18];
    mutable AnimationHandle_00449450 animation_handle;
    unsigned char padding_1100[0x38];
    int value_1138;
    int value_113c;
    int value_1140;
    int value_1144;
    float value_1148;
    float value_114c;
    float value_1150;
    float value_1154;
    unsigned char padding_1158[4];
    int value_115c;
    float value_1160;
    unsigned char padding_1164[0x1298];
    int value_23fc;
    unsigned char padding_2400[0x82];
    unsigned char flags_2482;

    __declspec(noinline) int ResolveIntegerValue(int encoded_selector) const;
};

struct EclIntegerManager {
    unsigned char padding_0000[0x10];
    EclIntegerSource* current_entity;
};

struct EclAnimationValue {
    unsigned char reserved_000[0x38A];
    short value_38a;
};

#define ECL_OFFSET(type, field, offset) \
    typedef char type##_##field##_offset[offsetof(type, field) == offset ? 1 : -1]
ECL_OFFSET(EclIntegerSource, origin_x, 0x3C0);
ECL_OFFSET(EclIntegerSource, origin_y, 0x3C4);
ECL_OFFSET(EclIntegerSource, animation_handle, 0x10FC);
ECL_OFFSET(EclIntegerSource, flags_2482, 0x2482);
ECL_OFFSET(EclIntegerSource, value_1068, 0x1068);
ECL_OFFSET(EclIntegerSource, value_106c, 0x106C);
ECL_OFFSET(EclIntegerSource, value_1074, 0x1074);
ECL_OFFSET(EclIntegerSource, value_1078, 0x1078);
ECL_OFFSET(EclIntegerSource, value_1094, 0x1094);
ECL_OFFSET(EclIntegerSource, value_1098, 0x1098);
ECL_OFFSET(EclIntegerSource, value_10ac, 0x10AC);
ECL_OFFSET(EclIntegerSource, value_10b0, 0x10B0);
ECL_OFFSET(EclIntegerSource, value_10b4, 0x10B4);
ECL_OFFSET(EclIntegerSource, value_10c0, 0x10C0);
ECL_OFFSET(EclIntegerSource, value_10c4, 0x10C4);
ECL_OFFSET(EclIntegerSource, value_10d8, 0x10D8);
ECL_OFFSET(EclIntegerSource, value_10dc, 0x10DC);
ECL_OFFSET(EclIntegerSource, value_10e0, 0x10E0);
ECL_OFFSET(EclIntegerSource, value_1138, 0x1138);
ECL_OFFSET(EclIntegerSource, value_113c, 0x113C);
ECL_OFFSET(EclIntegerSource, value_1140, 0x1140);
ECL_OFFSET(EclIntegerSource, value_1144, 0x1144);
ECL_OFFSET(EclIntegerSource, value_1148, 0x1148);
ECL_OFFSET(EclIntegerSource, value_114c, 0x114C);
ECL_OFFSET(EclIntegerSource, value_1150, 0x1150);
ECL_OFFSET(EclIntegerSource, value_1154, 0x1154);
ECL_OFFSET(EclIntegerSource, value_115c, 0x115C);
ECL_OFFSET(EclIntegerSource, value_1160, 0x1160);
ECL_OFFSET(EclIntegerSource, value_23fc, 0x23FC);
ECL_OFFSET(EclIntegerManager, current_entity, 0x10);
ECL_OFFSET(EclAnimationValue, value_38a, 0x38A);
#undef ECL_OFFSET

extern "C" EclIntegerSource* data_00477834;
extern "C" EclIntegerManager* data_00477704;
extern "C" int data_00474c74;
extern "C" int data_00474c98;

#pragma code_seg(".text$02dispatch")
int EclIntegerSource::ResolveIntegerValue(int encoded_selector) const {
    switch (encoded_selector) {
    case -10000:
        return Rng_NextU32((RngState*)0x004918B0);
    case -9999:
        return (int)Rng_NextFloat((RngState*)0x004918B0);
    case -9987:
        return (int)Rng_NextFloatSigned((RngState*)0x004918B0);
    case -9991:
        return (int)data_00477834->origin_x;
    case -9990:
        return (int)data_00477834->origin_y;
    case -9988:
        return value_115c;
    case -9986:
        return flags_2482 & 1;
    case -9985:
        return value_1138;
    case -9984:
        return value_113c;
    case -9983:
        return value_1140;
    case -9982:
        return value_1144;
    case -9981:
        return (int)value_1148;
    case -9980:
        return (int)value_114c;
    case -9979:
        return (int)value_1150;
    case -9978:
        return (int)value_1154;
    case -9997:
    case -9977:
        return (int)value_1068;
    case -9995:
    case -9975:
        return (int)value_1094;
    case -9994:
    case -9974:
        return (int)value_1098;
    case -9993:
    case -9973:
        return (int)value_10c0;
    case -9992:
    case -9972:
        return (int)value_10c4;
    case -9971:
        return (int)value_10b0;
    case -9970:
        return (int)value_10dc;
    case -9958:
        return (int)atan2((double)value_1078, (double)value_1074);
    case -9969:
        return (int)value_10ac;
    case -9968:
        return (int)value_10d8;
    case -9967:
        return (int)value_10b4;
    case -9966:
        return (int)value_10e0;
    case -9965:
        return (int)data_00477834->origin_x;
    case -9964:
        return (int)data_00477834->origin_y;
    case -9963:
        return (int)data_00477704->current_entity->value_1068;
    case -9962:
        return (int)data_00477704->current_entity->value_106c;
    case -9996:
    case -9976:
        return (int)value_106c;
    case -9961: {
        const EclAnimationValue* object = static_cast<const EclAnimationValue*>(
            ResolveAnimationHandle(&animation_handle));
        return object->value_38a;
    }
    case -9960:
        return data_00474c98;
    case -9959:
        return data_00474c74;
    case -9954:
        return value_23fc;
    case -9953:
        return data_00474c74 == 0;
    case -9952:
        return data_00474c74 == 1;
    case -9951:
        return data_00474c74 == 2;
    case -9950:
        return data_00474c74 == 3;
    case -9957:
        return 1;
    default:
        return 0;
    }
}
#pragma code_seg()
