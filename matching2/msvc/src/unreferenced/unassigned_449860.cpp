// 0x00449860: compare two handles by their leading id.
struct Handle2 {
    int id;
    __declspec(noinline) int Equals(const Handle2* other) const;
};

#pragma code_seg(".text$01accessor")
int Handle2::Equals(const Handle2* other) const {
    return id == other->id;
}
#pragma code_seg()
