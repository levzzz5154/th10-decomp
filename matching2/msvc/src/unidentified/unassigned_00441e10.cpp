struct Vec_00441e10 { int x; int y; int z; };
__declspec(noinline) Vec_00441e10* Subtract_00441e10(Vec_00441e10* result,
                                                     const Vec_00441e10* a,
                                                     const Vec_00441e10* b);
#pragma code_seg(".text$01accessor")
Vec_00441e10* Subtract_00441e10(Vec_00441e10* result, const Vec_00441e10* a, const Vec_00441e10* b) {
    int x = a->x - b->x;
    int y = a->y - b->y;
    int z = a->z - b->z;
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}
#pragma code_seg()
