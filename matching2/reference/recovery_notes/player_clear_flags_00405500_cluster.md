# Player clear-expired-flags at `0x00405500`

2026-09-27 update: the best native-LTCG source emits the complete **81-byte**
function with the correct EAX receiver, identical instruction forms and identical
branch targets. Eleven bytes still differ because the old-flags temporary and
the shared mask exchange ECX/EDX. At `+0x0A` the candidate loads old flags into
ECX; retail loads them into EDX, then materializes -3 into ECX at `+0x19`.
The seven final memory ANDs also consequently name the other mask register.
This is a measured register residual, so the region remains assembly.

Live Ghidra MCP decompilation and xrefs confirm the sixty-frame guard, the
pending-state clear, the eight flag clears and `InitializePlayer`'s EAX setup
before the call at `0x00405982`. A byte-backed object view lets the explicit
old-flags load precede `pendingState = 0`. A later typed-field model with a
zero-instruction barrier after the zero store also emits this same 81-byte
body; without that barrier it emits 89 bytes. The typed candidate is now
retained in `reference/semantic_candidates/player_clear_expired_flags_00405500.cpp`,
with probe evidence in `typed_barrier.json`. The historical immediate-width explanation
below was incorrect: retail and the current 81-byte candidate both use the
seven-byte `83 /7` comparison with immediate `0x3C`.

Reproducible scratch project: `matching2/build/experiments/player_flags/msvc`.
The first complete comparison is `probe2`/`report2.json`; later reports cover
signed fields, a free function, fastcall, commuted AND operands, and barriers
before the flags load, after the flags load, and after the zero store. Each of
those complete 81-byte variants retains the same eleven-byte permutation.
An explicit mask parameter emits 76 bytes and is also rejected. The barrier
experiments use `_ReadWriteBarrier`, which emits no machine instruction.
These tests narrow the next step to the register-selection context or to the
real caller; they do not establish an irreducible assembly requirement.

## Historical model

2026-09-18. `Player_ClearExpiredFlagsRetail` (81 bytes) is an EAX-entry store
filler with a guard: once `[eax+0x3738]` reaches `0x3C`, clear flag bit 1 on the
player and on seven owned entity slots.

Decoded structure: the store targets `0x0AD4`, `0x0E80`, `0x15D8`, `0x1984`,
`0x1D30`, `0x20DC`, `0x2488` are a **stride-`0x3AC` array** (Entity's size) whose
element `flags_378` is the written field, so the slots live at `0x75C + i*0x3AC`
for `i = 0, 1, 3, 4, 5, 6, 7` - slot 2 is skipped, which is the shape the model
implements. `[eax+0x378C]` is cleared bit 1 and `[eax+0x3790]` zeroed first.

Historical measurement with the cluster path: **89 bytes against retail's 81**, 65 differing,
first difference at byte 8. The original note attributed this to the compare
immediate width; the 2026-09-27 byte comparison above disproves that
interpretation. The retained model also orders the flags assignment before
the pending-state zeroing, unlike retail.

## The model (verbatim, as measured)

```cpp
// 0x00405500: once the timer has expired, clear flag bit 1 on the player and on
// the seven entity slots it owns.
// The player arrives in EAX, a convention only a native LTCG link chooses, so
// this region is compiled as a cluster.

struct PlayerSlot_00405500 {
    unsigned char pad_000[0x378];
    unsigned int flags_378;          // +0x378
    unsigned char pad_37c[0x30];     // stride 0x3AC
};

struct Player_00405500 {
    unsigned char pad_000[0x75C];
    PlayerSlot_00405500 slots[8];    // +0x75C, stride 0x3AC
    unsigned char pad_24b8[0x127C];
    int field_3738;                  // +0x3738
    unsigned char pad_373c[0x50];
    unsigned int flags_378c;         // +0x378C
    int field_3790;                  // +0x3790
    __declspec(noinline) void ClearExpiredFlags();
};

#pragma code_seg(".text$01accessor")
void Player_00405500::ClearExpiredFlags() {
    if (field_3738 < 0x3C) {
        return;
    }
    flags_378c &= ~2u;
    field_3790 = 0;
    slots[0].flags_378 &= ~2u;
    slots[1].flags_378 &= ~2u;
    slots[3].flags_378 &= ~2u;
    slots[4].flags_378 &= ~2u;
    slots[5].flags_378 &= ~2u;
    slots[6].flags_378 &= ~2u;
    slots[7].flags_378 &= ~2u;
}
#pragma code_seg()
```
