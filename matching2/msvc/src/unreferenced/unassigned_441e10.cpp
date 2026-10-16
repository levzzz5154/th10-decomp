struct Vec { int x; int y; int z; };
__declspec(noinline) Vec* Subtract2(Vec* result,
                                                     const Vec* a,
                                                     const Vec* b);
#pragma code_seg(".text$01accessor")
Vec* Subtract2(Vec* result, const Vec* a, const Vec* b) {
    int x = a->x - b->x;
    int y = a->y - b->y;
    int z = a->z - b->z;
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}
#pragma code_seg()
