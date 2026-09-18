# Region 0x0040C730 (71 bytes) - wave 8

Date: 2026-09-19. Region `asm_FUN_0040c730_0040c730` in
`src/game/fun_0040c730_0040c730.cpp`. **Result: EXACT**, registered as
`semantic_EclRecord_0040c730_Reset_0040c730` (`?Reset@EclRecord_0040c730@@QAEXXZ`)
from a new source `src/game/ecl_record_reset_0040c730.cpp`. Emitted extent 71
against the declared 71, **0 differing bytes**. Exploration ran in a throwaway
copy (`/tmp/Fun40C730/msvc`); the maintained tree carries only the verified
result.

## Probe

```
$ python3 matching2/tools/matching/probe.py --source src/game/ecl_record_reset_0040c730.cpp \
      --project matching2/msvc --output /tmp/Fun40C730/out_maint --show 30

0x0040c730      71 bytes  ?Reset@EclRecord_0040c730@@QAEXXZ  EXACT
EXACT
```

`build_msvc.validate_project` also passes on the maintained manifest afterwards
(4425 regions, 2394 translation units; semantic count 546 -> 547, semantic .text
bytes +71).

## What the region is (read off the image)

The receiver is a **script record**, not the game thread of the neighbouring
`lazy_animation_resource_0040c540_wave7.md` note: the two live in different
subsystems and share only their entry convention (object in EAX).

| offset | meaning | evidence |
|---|---|---|
| +0x0000 | method table (0x46D0C0 live / 0x46D0D8 released) | `0x40D830` ctor, `0x40C7B0` deleting destructor |
| +0x0004 | cursor: the instance the interpreter is on | `0x44FD10` `mov [edi+4],eax` with `eax = node->payload` |
| +0x0008 | the record's own 0x1024-byte interpreter state | `0x4500D0` allocates exactly `0x1024` for a child of the same type; `0x44E1A0`'s `esi` is this pointer and addresses `[esi+1008h]`.. |
| +0x1018 | instance name/id (-1 while unnamed) | `0x450160` compares `[payload+1010h]` with its key; the instance base is +8, so +0x1018 is instance+0x1010 |
| +0x101C | owning record (the reset stores `this`) | `0x4500D0` sets a child's `[esi+1014h] = edi` = the parent record |
| +0x1028 | instance+0x1020 flag dword, bit 0 | interpreter cases 18/19 `or`/`and dword [eax+1020h],1` |
| +0x1030 | the record's own link node `{instance,next,prev}` | `0x44FD10` `lea esi,[edi+1030h]` then walks `[esi]`, `[esi+4]`, `[esi+8]` |
| +0x1034/+0x1038 | that node's `next` / `prev` | `0x40C7B0` frees the chain from +0x1034; `0x44FD10` restores `[edi+4] = edi+8` when done |

`0x40C6E0` (`BulletEntity_0040c6e0::ClearResourceList`, already semantic) walks
the same +0x1034 chain, and the two call sites of this region are immediately
after it (`0x40E1D8`, `0x40E291`), so the schedule is "drop the resource list,
then re-arm the record".

`0x40D830` (still asm) contains an **inlined copy of the same ten stores** in a
different order (`[8]`, `[0C]`, `[101C]`, flag, `[1020]`, `[4]`, `[1018]`,
`[1030]`, `[1034]`, `[1038]`, with the flag load hoisted to the top). That is
independent evidence that this reset is one operation the compiler both outlined
(here) and inlined (there), and it constrains whoever models `0x40D830`.

Retail body (71 bytes, oracle):

```
56 8b b0 28 10 00 00 33 d2 8d 48 08 83 e6 fe 89 b0 28 10 00 00 89 11 89 50 0c
89 80 1c 10 00 00 c7 80 18 10 00 00 ff ff ff ff 89 90 20 10 00 00 89 48 04 89 88
30 10 00 00 89 90 34 10 00 00 89 90 38 10 00 00 5e c3
```

## Best model (source, layout, driver)

`src/game/ecl_record_reset_0040c730.cpp`:

```cpp
// 0x0040C730 - reset one script record so it can run a new script.
//
// A record owns its script instance in place at +0x0008 and keeps the instance
// the interpreter walks in the +0x0004 cursor; the record's own link node at
// +0x1030 heads the chain of instances it drives, so the reset points the
// cursor and that node at the embedded instance and empties the chain behind it.
//
// The record is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// layout/ltcg/ecl_record_reset_0040c730.json supplies that convention while
// keeping the recovered operation readable.

struct EclInstance_0040c730;
struct EclRecord_0040c730;

// One entry of the record's instance chain: the instance it names, then the
// chain links.  The record's own node is embedded at +0x1030.
struct EclInstanceNode_0040c730 {
    EclInstance_0040c730* instance;        // +0x00
    EclInstanceNode_0040c730* next;        // +0x04
    EclInstanceNode_0040c730* prev;        // +0x08
};

// The 0x1024-byte interpreter state.  A record embeds one at +0x0008 and the
// interpreter reaches it through whichever cursor the record holds.
struct EclInstance_0040c730 {
    float timer;                           // +0x0000  compared with the instruction's time
    void* instruction;                     // +0x0004  instruction being run
    unsigned char unknown_008[0x1008 - 0x008];
    int scratch_cursor;                    // +0x1008  offset into the scratch area at +0x0008
    int unknown_100C;                      // +0x100C
    int name;                              // +0x1010  lookup key; -1 while unnamed
    EclRecord_0040c730* owner;             // +0x1014  record this instance belongs to
    int unknown_1018;                      // +0x1018
    unsigned char mask;                    // +0x101C  copied into spawned children
    unsigned char unknown_101D[3];         // +0x101D
    unsigned int flags;                    // +0x1020  bit 0 is cleared by the reset
};

struct EclRecord_0040c730 {
    void* vtable;                          // +0x0000
    EclInstance_0040c730* running;         // +0x0004  instance the interpreter is on
    EclInstance_0040c730 instance;         // +0x0008
    void* script;                          // +0x102C
    EclInstanceNode_0040c730 self;         // +0x1030

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01reset")
void EclRecord_0040c730::Reset() {
    instance.timer = 0.0f;
    instance.instruction = 0;
    instance.flags &= ~1u;
    instance.owner = this;
    instance.name = -1;
    instance.unknown_1018 = 0;
    running = &instance;
    self.instance = &instance;
    self.next = 0;
    self.prev = 0;
}
#pragma code_seg()
```

The statement order matters and is *not* retail's emitted order: c1 schedules the
flag load to the top and the flag store ahead of the two instance stores, which
is what produces retail's `mov esi,[eax+1028h]` / `xor edx,edx` /
`lea ecx,[eax+8]` / `and esi,-2` / `mov [eax+1028h],esi` sequence (see below).

Layout `layout/ltcg/ecl_record_reset_0040c730.json`:

```json
{
  "schema_version": 1,
  "name": "ecl_record_reset_0040c730",
  "source": "src/game/ecl_record_reset_0040c730.cpp",
  "driver": "layout/ltcg/ecl_record_reset_0040c730_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Script-record reset compiled with native LTCG so the record pointer arrives in EAX.",
  "functions": [
    {"name": "EclRecord_0040c730_Reset", "symbol": "?Reset@EclRecord_0040c730@@QAEXXZ",
     "section": ".text$01reset", "address": "0x0040C730", "size": 71,
     "actual_abi": "record in EAX; plain RET"}
  ],
  "context": {
    "symbol": "?EclRecordResetCompilerContext@@YGHPAPAUEclRecord_0040c730@@H@Z",
    "section": ".text$03context", "address": "0x0040C790", "size": 36,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 46896},
    {"section": ".text$02layout", "address": "0x0040C777", "size": 25}
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"}
  ]
}
```

Driver `layout/ltcg/ecl_record_reset_0040c730_context.cpp`:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/ecl_record_reset_0040c730.cpp"

#pragma code_seg(".text$03context")
int __stdcall EclRecordResetCompilerContext(EclRecord_0040c730** records, int count) {
    while (count--)
        (*records++)->Reset();
    return 0;
}
#pragma code_seg()
```

`__fltused` is bound as `metadata` because the model touches the `float timer`
field; without it the native link fails with `LNK2001: unresolved external symbol
__fltused`. The context address is the converged 0x40C790/36; a declared size of
40 at 0x40C780 is retried to 36 by the machinery and then reports "compiler
context extent is outside a MAP CODE contribution", so the converged values are
the ones that belong in the layout.

## The move off the old source

The old unit `src/game/fun_0040c730_0040c730.cpp` also carried a naked body; the
cluster loader requires every region a cluster source owns to be a declared,
selected function, so the model had to live alone. The region's `source` moved to
`src/game/ecl_record_reset_0040c730.cpp`, `translation_units` lost the old file
and gained the new one, and the old file - which owned no other region (its
0x00402720 comment was stale; that region lives in `src/game/bullet_manager.cpp`)
- was deleted. `_asm_FUN_0040c730_0040c730` stays in the manifest's `symbols` at
0x0040C730, which is what the two `call asm_FUN_0040c730_0040c730` sites in
`bullet.cpp`'s naked regions still resolve through.

## Shapes tried

Every shape below was written into the scratch source and built through
`build_cluster` against the retail oracle; the flag statement's position is the
only thing that changes.

| shape | statement order of the flag update | emitted | differing | where the flag temp landed |
|---|---|---:|---:|---|
| A | `instance.flags &= ~1u;` first | 69 | 59 | **ECX**, no `push esi`; `lea ecx,[eax+8]` sunk after the flag store |
| G | `instance.active = 0;` (bitfield at the same dword) first | 69 | 59 | identical bytes to A |
| H | `instance_ptr = &instance;` then all stores through it | 69 | 59 | record in **ECX**, instance pointer in EAX - the local pointer took the EAX convention |
| D | `flags = instance.flags & ~1u;` first, `instance.flags = flags;` last | 69 | 63 | ECX, and the store sank to the very end |
| E | `flags = instance.flags;` first, `instance.flags = flags & ~1u;` third | **71** | **0** | ESI with `push esi`/`pop esi` |
| F | `instance.flags &= ~1u;` third (after the timer/instruction stores) | **71** | **0** | ESI with `push esi`/`pop esi` |

F is what landed: it needs no temporary local, and it reads as a plain ordered
reset.

## Why A is four bytes short - the mechanism

A's emitted body is retail's instruction for instruction except that the flag
value is carried in **ECX** and `lea ecx,[eax+8]` is therefore *sunk* to its first
use, after the flag store:

```
A  40c730: mov 0x1028(%eax),%ecx          retail: push %esi
   40c736: and $0xfffffffe,%ecx                   mov 0x1028(%eax),%esi
   40c739: xor %edx,%edx                          xor %edx,%edx
   40c73b: mov %ecx,0x1028(%eax)                  lea 0x8(%eax),%ecx
   40c741: lea 0x8(%eax),%ecx                     and $0xfffffffe,%esi
   40c744: mov %edx,(%ecx)                        mov %esi,0x1028(%eax)
   ...                                            mov %edx,(%ecx)
```

The two live ranges explain it. The scheduler runs before the register allocator:
in A it emitted the flag chain back to back, so `&instance` (a virtual register)
only becomes live at its first use *after* the flag value dies, and the allocator
happily colours both ECX. In E and F the scheduler hoisted `xor edx,edx` and
`lea ecx,[eax+8]` into the flag load's stall slot - the schedule retail has - so
`&instance` and the zero constant are live *across* the `and`, EAX is `this`, and
the only register left for the flag value is a callee-saved one: ESI, saved with
`push`/`pop`, which is exactly retail's two extra bytes.

So for this shape of body the *statement order in the source* is the lever that
picks the flag register, and `&= ~1u` on a plain dword field, an explicit
load/and/store through a local, and a bitfield write are all the same code - the
only thing that moved the bytes was putting two stores in front of the flag
update.

## What this lands, and whether a waiting model now lands

**No waiting model is converted by this region.** The 0x0040C540 note's closure is
`0x00448D50` (position in EDI), `0x00449950`, `0x0043E710`, `0x004489D0`,
`0x00401DE0`, `0x00402050` - `0x0040C730` is not among them, and no note in
`reference/recovery_notes/` mentions `0x40C730` at all. The only callers are the
the two sites inside the 2412-byte asm region `0x0040DC80` (`src/game/bullet.cpp`,
the `call` instructions at `0x40E1DE` and `0x40E297`), which stays assembly;
whoever models that manager
update now finds this callee already semantic instead of binding it.

## Registration state

- new `src/game/ecl_record_reset_0040c730.cpp`,
  `layout/ltcg/ecl_record_reset_0040c730.json`,
  `layout/ltcg/ecl_record_reset_0040c730_context.cpp`;
- deleted `src/game/fun_0040c730_0040c730.cpp`;
- `regions.json`: region 0x40C730 flipped to `semantic`, symbol
  `?Reset@EclRecord_0040c730@@QAEXXZ`, `previous_record` preserved through
  `promote_scratch.py --apply`; `ltcg_clusters` gained the layout;
  `translation_units` recomputed by the same tools;
- `validate_project` passes; the probe above is EXACT.
