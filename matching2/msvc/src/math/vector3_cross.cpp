// Compute left x right, staging all components before publishing the result.
// Native LTCG supplies destination EAX, left EDX, and right ECX; plain RET.
struct CrossVector_00421b90 { float x, y, z; };
#pragma code_seg(".text$01cross")
__declspec(noinline) CrossVector_00421b90* VectorCross_00421b90(CrossVector_00421b90* result, const CrossVector_00421b90* left, const CrossVector_00421b90* right) {
 // The intermediate record permits destination to alias either input.
 CrossVector_00421b90 staged;
 staged.x = left->y * right->z - right->y * left->z;
 staged.y = right->x * left->z - left->x * right->z;
 staged.z = right->y * left->x - left->y * right->x;
 *result = staged;
 return result;
}
#pragma code_seg()
