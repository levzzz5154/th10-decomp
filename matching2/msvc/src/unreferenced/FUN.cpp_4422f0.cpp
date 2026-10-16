// 0x004422F0..0x004422FE: Bytes2 constructor
//
// Native MSVC 13.10/LTCG assigns the aggregate result pointer to EAX and
// keeps the first two constructor arguments in CL/DL.  The final byte
// remains on the stack, producing the retail 15-byte constructor body.
struct Bytes2 {
    unsigned char first;
    unsigned char second;
    unsigned char third;

    __declspec(noinline) Bytes2(unsigned char a, unsigned char b,
                                         unsigned char c);
};

#pragma code_seg(".text$01target")
Bytes2::Bytes2(unsigned char a, unsigned char b,
                               unsigned char c)
    : first(a), second(b), third(c) {}
#pragma code_seg()
