// 0x00424440: whether the current value differs from the previous one.
struct ValuePair_00424440 {
    int previous;                     // +0x00
    int current;                      // +0x04
    __declspec(noinline) int Changed() const;
};

#pragma code_seg(".text$01accessor")
int ValuePair_00424440::Changed() const {
    return current != previous;
}
#pragma code_seg()
