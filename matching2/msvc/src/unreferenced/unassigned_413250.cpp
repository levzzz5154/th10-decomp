// 0x00413250: scale the three floats at +0x00..+0x08 by the argument
// The object pointer arrives in EAX, which only a native LTCG link chooses, so
// this region is compiled as a cluster.

#pragma pack(push, 1)
struct ObjectAccessor_00413250 {
    float x;
    float y;
    float z;
    __declspec(noinline) void Scale(float factor);
};
#pragma pack(pop)

#pragma code_seg(".text$01accessor")
void ObjectAccessor_00413250::Scale(float factor) {
    x *= factor;
    y *= factor;
    z *= factor;
}
#pragma code_seg()
