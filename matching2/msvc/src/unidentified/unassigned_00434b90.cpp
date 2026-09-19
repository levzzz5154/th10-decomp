// 0x00434B90..0x00434B94: the record's leading word plus the incoming value.
struct Object_00434b90 {
    __declspec(noinline) int Plus(int value) const;
};

#pragma code_seg(".text$01accessor")
int Object_00434b90::Plus(int value) const {
    return *(int*)this + value;
}

#pragma code_seg()
