# Region `0x00419040` (79 bytes) — wave 5

Date: 2026-09-19. Status: **EXACT**, landed as the single-function cluster
`layout/ltcg/recovery_clear_eight_buckets_00419040.json`.

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/recovery_clear_eight_buckets_00419040.cpp \
      --project matching2/msvc --output /tmp/CEB/out3 --show 30
0x00419040      79 bytes  ?ClearBuckets@Manager_00419040@@QAEXXZ  EXACT
EXACT
```

Registration went through exactly one
`register_cluster.py --layout layout/ltcg/recovery_clear_eight_buckets_00419040.json
--apply` (the region's source is its own file and had no other claimant), so
`translation_units` was rewritten by that single-cluster path; it is checked
sorted, unique and 2393 entries, and the region's source was already in it.

## What the region is

Retail walks two parallel eight-element arrays of 12-byte bucket records.  The
receiver is in **EAX**, the walk pointer in EDI (`= receiver + 0x7C`, the second
array, with the first read as `[edi-0x60]`), the outer counter in EBX, and the
chain link in ESI.  Each bucket's chain is released with `entry_free_004524a1`
(`0x004524A1`, `__cdecl`) applied to `node->block`, the link stepping through
`node->next` at `+4`.  Neither chain head is nulled, so this is a teardown path,
not a reset.

Both retail callers pass the receiver in EAX and neither needs a result:

* `0x00419027`, inside `asm_FUN_00418ee0_00418ee0`: `mov 0x8(%esp),%edx`;
  `mov %edx,%eax`; `call 0x419040`.  EBX/EBP/ESI/EDI have already been popped.
* `0x00419ABE`, inside `asm_FUN_00419960_00419960`:
  `mov 0x38(%esp),%eax`; `call 0x419040`.  EBX, EBP, ESI and EDI are live across
  the call (`mov 0x1c(%esp),%edi` / `mov 0x24(%esp),%esi` right afterwards).

The recovered body keeps every one of those registers: it pushes and pops
EBX/ESI/EDI, never touches EBP, and clobbers only ECX (the free argument) and
EDX (untouched in fact), both dead at both call sites.  It also reproduces the
`lea 0x0(%ecx),%ecx` the compiler inserts to align the outer loop body at
`0x00419050`, and the asymmetric inner-loop allocation retail shows — the first
chain's argument load targets EAX, the second's ECX.

## Source `src/game/recovery_clear_eight_buckets_00419040.cpp`

```cpp
// 0x00419040..0x0041908E: release every chain a manager holds in its two
// eight-way bucket arrays.
//
// The region is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// layout/ltcg/recovery_clear_eight_buckets_00419040.json supplies that
// convention while keeping the recovered operation readable.

extern "C" void __cdecl entry_free_004524a1(void* memory);   // 0x004524A1

// One releasing chain node: the block to release, then the link to the next.
struct ChainNode_00419040 {
    void* block;
    ChainNode_00419040* next;
};

// One bucket: a chain head.  The rest of the element lies outside this region.
struct Bucket_00419040 {
    ChainNode_00419040* head;
    unsigned reserved_004[2];
};

struct Manager_00419040 {
    unsigned char reserved_000[0x1C];
    Bucket_00419040 primary[8];
    Bucket_00419040 secondary[8];

    __declspec(noinline) void ClearBuckets();
};

#pragma code_seg(".text$01accessor")
void Manager_00419040::ClearBuckets() {
    for (int index = 0; index < 8; ++index) {
        for (ChainNode_00419040* node = primary[index].head; node != 0; ) {
            ChainNode_00419040* next = node->next;
            entry_free_004524a1(node->block);
            node = next;
        }
        for (ChainNode_00419040* node = secondary[index].head; node != 0; ) {
            ChainNode_00419040* next = node->next;
            entry_free_004524a1(node->block);
            node = next;
        }
    }
}
#pragma code_seg()
```

sha256 `295328feb90903d3700382b81ac0b3e2a2074242a8ca4b0fcd0fd8aa3d66c165`.

## Driver `layout/ltcg/recovery_clear_eight_buckets_00419040_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_clear_eight_buckets_00419040.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryClearEightBucketsCompilerContext(
        Manager_00419040** managers, int count) {
    while (count--)
        (*managers++)->ClearBuckets();
    return 0;
}
#pragma code_seg()
```

sha256 `93928d8c80fbd867e538d7edbad1084635f55e799c2e72320f6e13199988e959`.
The array-walking caller is what moves the member's `this` out of ECX into EAX;
the emitted context is 36 bytes at `0x004190A0`.

## Layout `layout/ltcg/recovery_clear_eight_buckets_00419040.json`

```json
{
  "schema_version": 1,
  "name": "recovery_clear_eight_buckets_00419040",
  "source": "src/game/recovery_clear_eight_buckets_00419040.cpp",
  "driver": "layout/ltcg/recovery_clear_eight_buckets_00419040_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Eight-way chain release compiled with native LTCG so the manager arrives in EAX.",
  "functions": [
    {
      "name": "ClearBuckets",
      "symbol": "?ClearBuckets@Manager_00419040@@QAEXXZ",
      "section": ".text$01accessor",
      "address": "0x00419040",
      "size": 79,
      "actual_abi": "manager in EAX; plain RET"
    }
  ],
  "context": {
    "symbol": "?RecoveryClearEightBucketsCompilerContext@@YGHPAPAUManager_00419040@@H@Z",
    "section": ".text$03context",
    "address": "0x004190A0",
    "size": 36,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 98368
    },
    {
      "section": ".text$02layout",
      "address": "0x0041908F",
      "size": 17
    }
  ],
  "constants": [],
  "absolute_symbols": [
    {
      "symbol": "_entry_free_004524a1",
      "address": "0x004524A1",
      "kind": "relative_code"
    }
  ]
}
```

sha256 `3e3ee44e9be9e88ddb29abc133e801e981ff11cf006a0efc52eee025a24f1dc6`.

## Shapes tried

* **A — both arrays subscripted by the same loop index** (the landed shape):
  emits 79 bytes, byte-identical to retail on the first build.  MSVC keeps one
  running pointer in EDI for the second array and addresses the first as
  `[edi-0x60]`, and picks EBX for the counter, exactly as retail does.
* **B — two explicit running bucket pointers** (`first = primary; second =
  secondary; ... ++first, ++second`): 81 bytes, first difference at offset
  `0x1`.  The two pointers cost a fourth callee-saved register, so the compiler
  emits `push ebp`, `mov $0x8,%ebp` and reaches the second array as
  `mov (%ebx,%edi,1),%eax`; retail has no EBP use and one pointer.  The
  subscripted form is therefore the shape retail compiled.

Nothing else was needed: no float pool, no `constant_aliases`, no `roots`, and
the region is a single-function cluster with no `additional_sources`.

## The two naked callers keep working

`src/game/fun_00418ee0_00418ee0.cpp:214` and `src/game/stage_tip_parser.cpp:251`
still contain `call asm_Recovery_ClearEightBuckets_00419040`, and
`src/game/recovery_leaves.cpp:1043` still holds a duplicate naked body of the
region.  None of that had to change: `symbols` still binds
`_asm_Recovery_ClearEightBuckets_00419040` = `0x00419040`, and
`make_link_script` emits every name that is *not* a selected region definition as
an absolute assignment, so both call sites resolve to the recovered body and
`recovery_leaves.obj`'s extra body is never placed.  This is the same shape as
the already-landed `0x0040C6E0` (`_asm_BulletEntity_ClearResourceList_0040c6e0`
renamed to `?ClearResourceList@BulletEntity_0040c6e0@@QAEXXZ`, old name still in
`symbols`, duplicate still in `recovery_leaves.cpp`); 116 landed regions have an
old asm symbol that another unit still references.

Only the region record and `ltcg_clusters` changed in `regions.json`, both
through `register_cluster.py --apply`; `translation_units` was recomputed by that
same call and is unchanged in content (the source already owned the region).
