// 0x00412EC0: angle of the pair at +0x00/+0x04
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00412ec0 {
    float field_000;
    float field_004;
    __declspec(noinline) float LoadValue() const;
};
#pragma pack(pop)
#include <math.h>

#pragma code_seg(".text$01accessor")
float ObjectAccessor_00412ec0::LoadValue() const {
    return atan2f(field_004, field_000);
}
#pragma code_seg()
