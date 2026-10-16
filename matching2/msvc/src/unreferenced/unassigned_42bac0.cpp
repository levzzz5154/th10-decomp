// 0x0042BAC0..0x0042BACD (14 bytes): does the inner record hold a value?
//
// Retail walks two pointers: the inner record from +0x04 of the object in EAX,
// then the pointer at +0x04 of that record, and returns 1 when it is non-null.
// Neither load is guarded, so the inner record is always present.

struct Inner {
    unsigned char unknown_00[0x04];
    void* value;                   // +0x04
};

struct Outer2 {
    unsigned char unknown_00[0x04];
    Inner* inner;         // +0x04

    __declspec(noinline) int HasValue();
};

#pragma code_seg(".text$01has")
int Outer2::HasValue() {
    return inner->value != 0;
}
#pragma code_seg()
