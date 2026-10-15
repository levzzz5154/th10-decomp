// 0x00435660..0x00435668: the absolute value of the record's leading word.
struct Object_00436560 {
    __declspec(noinline) int Abs() const;
};

#pragma code_seg(".text$01accessor")
int Object_00436560::Abs() const {
    int value = *(int*)this;
    return value < 0 ? -value : value;
}

#pragma code_seg()
