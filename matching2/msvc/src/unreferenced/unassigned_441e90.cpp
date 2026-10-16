struct VecList {
    int x;
    int y;
    int z;
    __declspec(noinline) VecList* Add(
            VecList* result, const VecList* lhs) const;
};
#pragma code_seg(".text$01accessor")
VecList* VecList::Add(
        VecList* result, const VecList* lhs) const {
    int x = lhs->x + this->x;
    int y = lhs->y + this->y;
    int z = lhs->z + this->z;
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}
#pragma code_seg()
