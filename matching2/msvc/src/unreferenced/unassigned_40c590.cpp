// 0x0040C590: whether the leading id equals the given value.
struct IdHolder {
    int id;
    __declspec(noinline) int Matches(int value);
};

#pragma code_seg(".text$01accessor")
int IdHolder::Matches(int value) {
    return id == value;
}
#pragma code_seg()
