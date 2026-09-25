#include "asm_symbols.hpp"

// 0x00456AD4..0x00456AF1: __fpmath
// Initialize the CRT floating-point hooks and its Pentium FDIV feature flag.
extern "C" void __cdecl asm_fpmath_00456ad4(int set_default_precision) {
    asm_FUN_00456a8c_00456a8c();

    // The helper returns the API/fallback result in EAX. Its shared declaration
    // is void, so use the same entry point through the observed int-return ABI.
    typedef int (__cdecl *ProcessorFeatureProbe_00456ad4)();
    const ProcessorFeatureProbe_00456ad4 probe = reinterpret_cast<ProcessorFeatureProbe_00456ad4>(
        &asm_ms_p5_mp_test_fdiv_0045e03a);
    const int has_fdiv_erratum = probe();

    // Ghidra shows a 32-bit write here and a later 32-bit read at 0x00463BC6.
    *reinterpret_cast<unsigned int*>(&data_00477388) =
        static_cast<unsigned int>(has_fdiv_erratum);

    if (set_default_precision != 0) {
        asm_setdefaultprecision_0045dfe8();
    }

    // This CRT helper snapshots the status word before issuing FNCLEX; the
    // original __fpmath ignored the status and only needed the clear side effect.
    asm_clrfp_0045ed7b();
}
