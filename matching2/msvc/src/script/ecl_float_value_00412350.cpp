// 0x00412350: floating-point ECL values, with a native 51-entry switch table.
#include <stddef.h>
#include <math.h>

struct EntityAngleFromPoint_00426660 {
    unsigned char reserved_000[0x3C0];
    float origin_x;
    float origin_y;

    __declspec(noinline) float AngleFromPoint(const float* point);
};



#include "th10/math/rng.hpp"

// The adjacent entry at 0x00412300 selects integer destinations from the
// same ECL object. This dispatcher reads the corresponding scalar values.
struct EclFloatSource_00412350 {
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
    unsigned char padding_10e4[0x54];
    int value_1138;
    int value_113c;
    int value_1140;
    int value_1144;
    float value_1148;
    float value_114c;
    float value_1150;
    float value_1154;
    unsigned char padding_1158[8];
    float value_1160;
    unsigned char padding_1164[0x1298];
    int value_23fc;
    unsigned char padding_2400[0x80];
    unsigned int flags_2480;

    __declspec(noinline) float ResolveFloatValue(int encoded_selector) const;
};

struct EclFloatManager_00412350 {
    unsigned char padding_0000[0x10];
    EclFloatSource_00412350* current_entity;
};


#define ECL_FLOAT_OFFSET(field, offset) \
    typedef char EclFloat_##field##_offset[offsetof(EclFloatSource_00412350, field) == offset ? 1 : -1]
ECL_FLOAT_OFFSET(origin_x, 0x3C0);
ECL_FLOAT_OFFSET(origin_y, 0x3C4);
ECL_FLOAT_OFFSET(flags_2480, 0x2480);
ECL_FLOAT_OFFSET(value_1068, 0x1068);
ECL_FLOAT_OFFSET(value_106c, 0x106C);
ECL_FLOAT_OFFSET(value_1074, 0x1074);
ECL_FLOAT_OFFSET(value_1078, 0x1078);
ECL_FLOAT_OFFSET(value_1094, 0x1094);
ECL_FLOAT_OFFSET(value_1098, 0x1098);
ECL_FLOAT_OFFSET(value_10ac, 0x10AC);
ECL_FLOAT_OFFSET(value_10b0, 0x10B0);
ECL_FLOAT_OFFSET(value_10b4, 0x10B4);
ECL_FLOAT_OFFSET(value_10c0, 0x10C0);
ECL_FLOAT_OFFSET(value_10c4, 0x10C4);
ECL_FLOAT_OFFSET(value_10d8, 0x10D8);
ECL_FLOAT_OFFSET(value_10dc, 0x10DC);
ECL_FLOAT_OFFSET(value_10e0, 0x10E0);
ECL_FLOAT_OFFSET(value_1138, 0x1138);
ECL_FLOAT_OFFSET(value_113c, 0x113C);
ECL_FLOAT_OFFSET(value_1140, 0x1140);
ECL_FLOAT_OFFSET(value_1144, 0x1144);
ECL_FLOAT_OFFSET(value_1148, 0x1148);
ECL_FLOAT_OFFSET(value_114c, 0x114C);
ECL_FLOAT_OFFSET(value_1150, 0x1150);
ECL_FLOAT_OFFSET(value_1154, 0x1154);
ECL_FLOAT_OFFSET(value_1160, 0x1160);
ECL_FLOAT_OFFSET(value_23fc, 0x23FC);
#undef ECL_FLOAT_OFFSET
typedef char EclFloat_manager_entity_offset[offsetof(EclFloatManager_00412350, current_entity) == 0x10 ? 1 : -1];

extern "C" EclFloatSource_00412350* g_player;
extern "C" EclFloatManager_00412350* data_00477704;
extern "C" int data_00474c74;
extern "C" int data_00474c98;
extern "C" float data_00470afc;
extern "C" float data_00470b04;
extern "C" float data_00470b08;
extern "C" float data_00470b18;
extern "C" float data_00470b94;
extern "C" float data_00470bd4;


#pragma code_seg(".text$02dispatch")
float EclFloatSource_00412350::ResolveFloatValue(int encoded_selector) const {
    // The two origin-selector pairs share values but remain separate switch arms.
    float result;
    switch (encoded_selector) {
    case -10000:
        result = (float)Rng_NextU32((RngState*)0x004918B0);
        break;
    case -9999:
        result = Rng_NextFloat((RngState*)0x004918B0);
        break;
    case -9987:
        result = Rng_NextFloatSigned((RngState*)0x004918B0);
        break;
    case -9998:
        result = Rng_NextFloatSigned((RngState*)0x004918B0) * data_00470b18;
        break;
    case -9991:
        result = g_player->origin_x;
        break;
    case -9990:
        result = g_player->origin_y;
        break;
    case -9989:
        result = ((EntityAngleFromPoint_00426660*)g_player)->AngleFromPoint(&value_1068);
        break;
    case -9988:
        result = value_1160;
        break;
    case -9986:
        result = (float)((flags_2480 >> 16) & 1);
        break;
    case -9985:
        result = (float)value_1138;
        break;
    case -9984:
        result = (float)value_113c;
        break;
    case -9983:
        result = (float)value_1140;
        break;
    case -9982:
        result = (float)value_1144;
        break;
    case -9981:
        result = (float)value_1148;
        break;
    case -9980:
        result = (float)value_114c;
        break;
    case -9979:
        result = (float)value_1150;
        break;
    case -9978:
        result = (float)value_1154;
        break;
    case -9997:
    case -9977:
        result = value_1068;
        break;
    case -9996:
    case -9976:
        result = value_106c;
        break;
    case -9995:
    case -9975:
        result = value_1094;
        break;
    case -9994:
    case -9974:
        result = value_1098;
        break;
    case -9993:
    case -9973:
        result = value_10c0;
        break;
    case -9992:
    case -9972:
        result = value_10c4;
        break;
    case -9971:
        result = value_10b0;
        break;
    case -9970:
        result = value_10dc;
        break;
    case -9958:
        result = (float)atan2((double)value_1078, (double)value_1074);
        break;
    case -9969:
        result = value_10ac;
        break;
    case -9968:
        result = value_10d8;
        break;
    case -9967:
        result = value_10b4;
        break;
    case -9966:
        result = value_10e0;
        break;
    case -9965:
        result = g_player->origin_x;
        break;
    case -9964:
        result = g_player->origin_y;
        break;
    case -9963:
        result = data_00477704->current_entity->value_1068;
        break;
    case -9962:
        result = data_00477704->current_entity->value_106c;
        break;
    case -9960:
        result = (float)data_00474c98;
        break;
    case -9959:
        result = (float)data_00474c74;
        break;
    case -9957:
        result = data_00470afc;
        break;
    case -9956:
        result = ((EntityAngleFromPoint_00426660*)g_player)->AngleFromPoint(&value_1094);
        break;
    case -9955:
        result = ((EntityAngleFromPoint_00426660*)g_player)->AngleFromPoint(&value_10c0);
        break;
    case -9954:
        result = (float)value_23fc;
        break;
    case -9953:
        result = (float)(data_00474c74 == data_00470b04);
        break;
    case -9952:
        result = (float)(data_00474c74 == data_00470afc);
        break;
    case -9951:
        result = (float)(data_00474c74 == data_00470b08);
        break;
    case -9950:
        result = (float)(data_00474c74 == data_00470bd4);
        break;
    default: result = data_00470b04;
        break;
    }
    return result;
}
#pragma code_seg()
