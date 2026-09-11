// 0x0040C6B0..0x0040C6B8: returns the shared single-precision constant held at
// 0x00470B04 widened to the double result the callers expect. The argument is
// unused; it only travels on the stack so the caller keeps the __stdcall ABI.
extern "C" unsigned char data_00470b04;

double __stdcall FloatConstantAsDouble_0040c6b0(int unused) {
    return *(float*)&data_00470b04;
}
