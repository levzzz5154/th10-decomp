// 0x00449860: compare two handles by their leading id.
struct Handle_00449860 {
    int id;
    __declspec(noinline) int Equals(const Handle_00449860* other) const;
};

#pragma code_seg(".text$01accessor")
int Handle_00449860::Equals(const Handle_00449860* other) const {
    return id == other->id;
}
#pragma code_seg()
