// Compute left x right, staging all components before publishing the result.
// Native LTCG supplies destination EAX, left EDX, and right ECX; plain RET.
struct CrossVector { float x, y, z; };
#pragma code_seg(".text$01cross")
__declspec(noinline) CrossVector* VectorCross(CrossVector* result, const CrossVector* left, const CrossVector* right) {
 // The intermediate record permits destination to alias either input.
 CrossVector staged;
 staged.x = left->y * right->z - right->y * left->z;
 staged.y = right->x * left->z - left->x * right->z;
 staged.z = right->y * left->x - left->y * right->x;
 *result = staged;
 return result;
}
#pragma code_seg()
