extern "C" unsigned int __fastflag;

// 0x00456AC4..0x00456AD3: Replace a global value and return its old value.
extern "C" unsigned int __cdecl crt_helper_456ac4(unsigned int value) {
    unsigned int previous = __fastflag;
    __fastflag = value;
    return previous;
}
