// 0x0042AEF0..0x0042AF1C (45 bytes): release the two owned blocks.
//
// Retail frees the pointer at +0x00 and then the one at +0x04, clearing each
// slot after the free and skipping a null.  The pair itself lives in ESI, the
// callee-saved register that survives both calls, and EAX carries the loaded
// pointer, so the receiver is a register no C++ declaration names: the body is
// compiled in the native-LTCG cluster
// build_support/layout/ltcg/raw_pair_release.json whose array-walking synthetic
// caller establishes that convention.
//
// The allocator at 0x00452422 is bound as an absolute address, the shape the
// project uses for a CRT entry point compiled from another unit.

extern "C" void __cdecl crt_free(void* block);

struct RawPair4 {
    void* first;                           // +0x00
    void* second;                          // +0x04
};

__declspec(noinline) void RawPair_0042aef0_Release(RawPair4* pair);

#pragma code_seg(".text$01rel")
void RawPair_0042aef0_Release(RawPair4* pair) {
    if (pair->first != 0) {
        crt_free(pair->first);
        pair->first = 0;
    }
    if (pair->second != 0) {
        crt_free(pair->second);
        pair->second = 0;
    }
}
#pragma code_seg()
