// 0x00438240..0x0043824D: the small-string pointer for the object arriving in
// EAX: the heap pointer at +0x04 once the capacity at +0x18 reaches 0x10, the
// inline buffer at +0x04 otherwise.
struct Object_00438240 {
    unsigned char pad_000[4];
    char* heap;
    unsigned char pad_008[0x10];
    unsigned int capacity;
    __declspec(noinline) const char* Data() const;
};

#pragma code_seg(".text$01accessor")
const char* Object_00438240::Data() const {
    if (capacity >= 0x10) {
        return heap;
    }
    return (const char*)this + 4;
}

#pragma code_seg()
