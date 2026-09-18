// 0x00441E50: scale a three-component integer vector by a float rate and
// truncate every product toward zero.
//
// Retail: DB 47 04 / D8 4C 24 0C   fild [edi+4]; fmul [esp+0xC]
//         E8 .. / 8B D8             call __ftol2; mov ebx,eax
//         DB 47 08 / D8 4C 24 0C   fild [edi+8]; fmul [esp+0xC]
//         E8 .. / 8B E8             call __ftol2; mov ebp,eax
//         DB 07 / D8 4C 24 0C      fild [edi]; fmul [esp+0xC]
//         E8 ..                     call __ftol2
//         89 6E 08 / 5D / 89 06 / 89 5E 04 / 8B C6 / 5B / C2 04 00
//
// The source vector arrives in EDI, the destination in ESI, the rate on the
// stack, and the destination is returned in EAX, so the scaler is compiled as
// a native LTCG cluster (layout/ltcg/random_vector_store_rounded_scalar.json).
//
// The three products are computed in the order y, z, x and stored in the order
// +8, +0, +4. MSVC rotates the statement sequence left by one, so writing the
// components in declaration order reproduces retail's schedule; writing them
// in retail's emitted order (y, z, x) rotates it once more and misses.

struct RandomVectorSource { int x, y, z; };
struct RandomVectorResult { int x, y, z; };

#pragma code_seg(".text$01store")
__declspec(noinline) RandomVectorResult* __stdcall RandomVector_StoreRoundedScalar(
        RandomVectorSource* source, RandomVectorResult* result, float scale) {
    int x = int(source->x * scale);
    int y = int(source->y * scale);
    int z = int(source->z * scale);
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}
#pragma code_seg()
