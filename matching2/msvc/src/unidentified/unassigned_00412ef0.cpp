// 0x00412EF0: squared distance to the other vector
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Vector2_00412ef0 {
    float x;
    float y;
    __declspec(noinline) float DistanceSquared(const Vector2_00412ef0* other) const;
};
#pragma code_seg(".text$01accessor")
float Vector2_00412ef0::DistanceSquared(const Vector2_00412ef0* other) const {
    float dy = y - other->y;
    float dx = x - other->x;
    return dx * dx + dy * dy;
}
#pragma code_seg()
