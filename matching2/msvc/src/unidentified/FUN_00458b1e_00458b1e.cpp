#include <emmintrin.h>

// 0x00458B1E..0x00458B52: probe whether the OS permits XMM instructions.
// The caller checks CPUID's SSE2 bit before calling. The retail SEH filter
// accepts any exception; its handler leaves this result at zero if the probe
// faults. MSVC's SEH syntax and an intrinsic keep that behavior without asm.
extern "C" int __cdecl asm_FUN_00458b1e_00458b1e() {
    int available = 0;
    __try {
        volatile __m128d probe = _mm_setzero_pd();
        (void)probe;
        available = 1;
    } __except (1) {
        available = 0;
    }
    return available;
}
