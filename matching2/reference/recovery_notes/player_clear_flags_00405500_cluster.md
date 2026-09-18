# 0x00405500 - player clear-expired-flags: structure decoded, extent 89 vs 81

2026-09-18. `Player_ClearExpiredFlagsRetail` (81 bytes) is an EAX-entry store
filler with a guard: once `[eax+0x3738]` reaches `0x3C`, clear flag bit 1 on the
player and on seven owned entity slots.

Decoded structure: the store targets `0x0AD4`, `0x0E80`, `0x15D8`, `0x1984`,
`0x1D30`, `0x20DC`, `0x2488` are a **stride-`0x3AC` array** (Entity's size) whose
element `flags_378` is the written field, so the slots live at `0x75C + i*0x3AC`
for `i = 0, 1, 3, 4, 5, 6, 7` - slot 2 is skipped, which is the shape the model
implements. `[eax+0x378C]` is cleared bit 1 and `[eax+0x3790]` zeroed first.

Measured with the cluster path: **89 bytes against retail's 81**, 65 differing,
first difference at byte 8, where retail uses the `81 /7` form of `cmp` with a
full 32-bit immediate (`... 3c 00 00 00`) while the model emits the sign-extended
`83` form. Retail's branch is `jl` (a signed compare), so this is not the
signed/unsigned choice; the immediate's width is a compiler selection the model
has not matched yet, and eight bytes of extent remain unexplained.

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
