#include "asm_symbols.hpp"

// 0x0045DFFA..0x0045E039: runtime probe for the Pentium FDIV defect.
// Retail constants are 4195835.0, 3145727.0, and the threshold 1.0.
extern "C" int __cdecl asm_ms_p5_test_fdiv_0045dffa() {
    volatile double numerator =
        *reinterpret_cast<const double*>(&data_0046c560);
    volatile double denominator =
        *reinterpret_cast<const double*>(&data_0046c568);

    // Keep both operands and the residual in binary64 memory as retail does.
    // Volatile also keeps the division on the running CPU.
    volatile double residual =
        numerator - (numerator / denominator) * denominator;
    const double threshold =
        *reinterpret_cast<const double*>(&data_0046ac28);
    return residual > threshold ? 1 : 0;
}
