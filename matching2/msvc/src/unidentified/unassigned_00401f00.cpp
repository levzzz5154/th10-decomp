// 0x00401F00..0x00401F36: write the identity transform into the 0x40-byte
// row-major D3D 4x4 matrix whose address arrives in EAX. The object address
// lives in the entry register, so the function is compiled with the native-LTCG
// cluster driver that reproduces the retail internal convention.
//
// The elements are written in the order retail emits them: the twelve
// off-diagonal elements first, each in descending offset order, then the
// diagonal. MSVC preserves this statement order for a run of constant stores
// to one base register, so reading order would move bytes without changing the
// result.

struct Matrix4x4 {
    float values[4][4];

    __declspec(noinline) void SetIdentity();
};

#pragma code_seg(".text$01identity")
void Matrix4x4::SetIdentity() {
    values[3][2] = 0.0f;
    values[3][1] = 0.0f;
    values[3][0] = 0.0f;
    values[2][3] = 0.0f;
    values[2][1] = 0.0f;
    values[2][0] = 0.0f;
    values[1][3] = 0.0f;
    values[1][2] = 0.0f;
    values[1][0] = 0.0f;
    values[0][3] = 0.0f;
    values[0][2] = 0.0f;
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}
#pragma code_seg()
