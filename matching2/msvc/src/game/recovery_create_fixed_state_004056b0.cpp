// 0x004056B0..0x00405704 (85 bytes): Recovery_CreateFixedState
//
// Allocates the 0x48-byte fixed-state pair, zeroes it, clears bit 0 of its
// flag word at +0x24, raises bit 1 of its published flags and publishes it
// through data_004776EC.  The scheduler callbacks are then installed; when the
// installation fails the freshly built pair is released and freed again, and
// the factory reports NULL so callers can tell "not created" from "created".
//
// Retail keeps the pair in EBX across the installation, the release and the
// free. That is a whole-program register agreement: the installer at 0x004055C0
// holds the pair across the two scheduler registrations it reaches, which
// themselves keep the callback in ESI and the priority in EDI, so the pair is
// left in EBX. This source is therefore compiled in the same native-LTCG link
// as that callee chain (see layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include <string.h>

void *__cdecl operator new(unsigned int size);

struct RawPair_004056b0 {
    unsigned int flags_000;             // +0x00, bit 1 = published
    unsigned char pad_004[4];
    void *callback_008;                 // +0x08
    void *callback_00C;                 // +0x0C
    unsigned char pad_010[0x14];
    unsigned int flags_024;             // +0x24
    unsigned char pad_028[0x20];
};

extern "C" void *data_004776ec;
extern "C" void __cdecl entry_free_004524a1(void *block);
extern "C" int __stdcall asm_Recovery_InstallPairSetFlags_004055c0(
        RawPair_004056b0 *pair);
extern "C" void __stdcall asm_Recovery_ReleaseRawPairAndReset_00405620(
        RawPair_004056b0 *pair);

#pragma code_seg(".text$00_xfixed")
extern "C" __declspec(noinline) void *__cdecl asm_Recovery_CreateFixedState_004056b0(void) {
    RawPair_004056b0 *fresh = new RawPair_004056b0;
    RawPair_004056b0 *state;
    if (fresh) {
        // The pair's low header flag is cleared before the block is zeroed.
        unsigned int *owned = (unsigned int *)((char *)fresh + 0x24);
        *owned &= ~1u;
        memset(fresh, 0, sizeof(RawPair_004056b0));
        fresh->flags_000 |= 2u;
        data_004776ec = fresh;
        state = fresh;
    } else {
        state = 0;
    }
    if (asm_Recovery_InstallPairSetFlags_004055c0(state) != 0) {
        if (state) {
            asm_Recovery_ReleaseRawPairAndReset_00405620(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
