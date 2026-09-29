// 0x0040C590: whether the leading id equals the given value.
struct IdHolder_0040c590 {
    int id;
    __declspec(noinline) int Matches(int value);
};

#pragma code_seg(".text$01accessor")
int IdHolder_0040c590::Matches(int value) {
    return id == value;
}
#pragma code_seg()
