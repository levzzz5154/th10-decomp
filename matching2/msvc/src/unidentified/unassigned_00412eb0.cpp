// 0x00412EB0: angle of the pair at +0x0C/+0x10
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00412eb0 {
    unsigned char pad_000[0xC];
    float field_00C;
    float field_010;
    __declspec(noinline) float LoadValue() const;
};
#pragma pack(pop)
#include <math.h>

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412eb0::LoadValue() const {
    return atan2f(field_010, field_00C);
}
#pragma code_seg()
