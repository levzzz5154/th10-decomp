extern "C" unsigned int __sse2_available;
extern "C" unsigned int __use_sse2_mathfcns;

// 0x00458C25..0x00458C38: Set the masked CRT flag when enabled.
extern "C" void __cdecl crt_unassigned_458c25(unsigned int enabled) {
    __use_sse2_mathfcns = enabled ? __sse2_available : 0;
}
