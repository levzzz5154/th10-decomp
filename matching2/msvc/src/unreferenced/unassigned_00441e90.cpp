struct Vec_00441e90 {
    int x;
    int y;
    int z;
    __declspec(noinline) Vec_00441e90* Add(
            Vec_00441e90* result, const Vec_00441e90* lhs) const;
};
#pragma code_seg(".text$01accessor")
Vec_00441e90* Vec_00441e90::Add(
        Vec_00441e90* result, const Vec_00441e90* lhs) const {
    int x = lhs->x + this->x;
    int y = lhs->y + this->y;
    int z = lhs->z + this->z;
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}
#pragma code_seg()
