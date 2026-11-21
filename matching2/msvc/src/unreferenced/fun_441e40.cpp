// 0x00441E40..0x00441E4E: Triple3 constructor
//
// Native MSVC 13.10/LTCG assigns the aggregate result pointer to EAX and
// keeps the first two constructor arguments in ECX/EDX.  The final argument
// remains on the stack, producing the retail 15-byte constructor body.
struct Triple3 {
    int first;
    int second;
    int third;

    __declspec(noinline) Triple3(int a, int b, int c);
};

#pragma code_seg(".text$01target")
Triple3::Triple3(int a, int b, int c)
    : first(a), second(b), third(c) {}
#pragma code_seg()
