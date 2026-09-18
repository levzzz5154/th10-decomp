# 0x00413790 `AnimationManager::SetActiveCount` — recovered EXACT

2026-09-19, wave 6. 77 bytes, EXACT on the first build. Landed through the
native-LTCG cluster path as a member of the animation manager with the receiver
in EAX and the count in ECX.

## Probe

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/animation_set_active_count_00413790.cpp \
      --project matching2/msvc --output /tmp/SetActiveCount/out2 --show 30
0x00413790      77 bytes  ?SetActiveCount@AnimationManager_00413790@@QAEXH@Z  EXACT
EXACT
```

Emitted extent 77, retail extent 77, `different_bytes` 0. The emitted bytes are
identical to retail's, including the 3-byte `lea 0(%ecx),%ecx` that MSVC puts in
front of the 16-byte-aligned second loop and the `jmp` that skips it:

```
413790: xor    %edx,%edx
413792: test   %ecx,%ecx
413794: push   %edi
413795: mov    %eax,%edi
413797: jle    0x4137b5
413799: push   %esi
41379a: lea    0x4cdc(%edi),%eax
4137a0: mov    %ecx,%esi
4137a2: mov    %ecx,%edx
4137a4: orl    $0x2,(%eax)
4137a7: add    $0x3ac,%eax
4137ac: dec    %esi
4137ad: jne    0x4137a4
4137af: cmp    $0x9,%ecx
4137b2: pop    %esi
4137b3: jge    0x4137db
4137b5: mov    %edx,%eax
4137b7: imul   $0x3ac,%eax,%eax
4137bd: mov    $0x9,%ecx
4137c2: lea    0x4cdc(%eax,%edi,1),%eax
4137c9: sub    %edx,%ecx
4137cb: jmp    0x4137d0
4137cd: lea    0x0(%ecx),%ecx
4137d0: andl   $0xfffffffd,(%eax)
4137d3: add    $0x3ac,%eax
4137d8: dec    %ecx
4137d9: jne    0x4137d0
4137db: pop    %edi
4137dc: ret
```

## Semantics

Enable the animation manager's first `count` records and disable the remainder of
its fixed nine-record table. Records live at manager `+0x4CDC`, stride `0x3AC`,
the enabled bit is bit 1 of the record's first dword.

## Retail ABI

Entry: **EAX = manager (`this`), ECX = count**. EDI is saved; ESI is saved only on
the `count > 0` path (the `jle` at 0x413797 jumps past `push esi`); EAX is the
scratch walking pointer, EDX the surviving record index. There are no calls, so
the whole body is a leaf and the `ret` is plain. EAX on return holds the
end-of-table pointer — no caller reads it.

Every caller loads exactly that pair:

- `src/game/pause_menu_reset.cpp:99,105,109` — `mov eax,[data_0047770c]`, then
  `mov ecx,[data_00474c70]`, `pop edi`, `jmp` 0x413790 (tail jump).
- `src/game/spell_timeout.cpp:77,79` — `mov eax,[data_0047770c]`, `call`.
- `src/game/recovery_increment_animation_count_004188a0.cpp:35-39` and `:85-93` —
  `mov ecx,[data_00474c70]` / `mov eax,[data_0047770c]` / `call`.

`data_0047770c` is the manager singleton pointer, `data_00474c70` the count. The
sibling that keeps the count is the partially recovered
`src/game/recovery_increment_animation_count_004188a0.cpp` (no separate
`animation_set_active_count.cpp` exists in the tree): it writes
`[eax+0x30]` clamped to 9 into `data_00474c70` at `:35`/`:89` before calling, so
the count this model sees is `0..9` and the unbounded first loop never leaves the
nine-record table in practice. The emitted body keeps those registers: EDI/ESI are
restored on every path, EAX/ECX/EDX are the declared scratch, and the callee does
not touch the stack beyond the two saved registers. Both callers that keep a live
EDI around the call (`pause_menu_reset.cpp`,
`recovery_increment_animation_count_004188a0.cpp`) rely on it, and the emitted body
preserves it.

## Landed source — `src/game/animation_set_active_count_00413790.cpp`

```cpp
// 0x00413790: enable `count` records of the animation manager's fixed nine-record
// table and disable the rest.
struct AnimationRecord_00413790 {
    unsigned int flags_0000;             // +0x000
    unsigned char pad_0004[0x3AC - 4];
};

struct AnimationManager_00413790 {
    unsigned char pad_0000[0x4CDC];
    AnimationRecord_00413790 records_4cdc[9];
    __declspec(noinline) void SetActiveCount(int count);
};

#pragma code_seg(".text$01accessor")
void AnimationManager_00413790::SetActiveCount(int count) {
    int index = 0;
    for (; index < count; ++index)
        records_4cdc[index].flags_0000 |= 2;
    if (index >= 9)
        return;
    for (; index < 9; ++index)
        records_4cdc[index].flags_0000 &= ~2u;
}
#pragma code_seg()
```

`index >= 9` is the source's own test: retail's guard is `jge` (`0x7d`). The test
is only emitted on the `count > 0` path, where the compiler knows `index == count`;
on the `count <= 0` path `index == 0` folds it away, which is exactly how retail
reaches the clearing loop at 0x4137B5 with no test at all.

## Driver — `layout/ltcg/animation_set_active_count_00413790_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/animation_set_active_count_00413790.cpp"

#pragma code_seg(".text$03context")
int __stdcall AnimationSetActiveCountCompilerContext(AnimationManager_00413790** managers,
                                                     int count) {
    for (int index = 0; index < count; ++index)
        managers[index]->SetActiveCount(count);
    return 0;
}
#pragma code_seg()
```

The indexing caller puts the manager in EAX and leaves the count in ECX; the second
argument of the call is the same live `count`, which is what fixes ECX. Emitted
context: 40 bytes at 0x4137F0 (declared identically, so no adaptive retry was
needed).

## Layout — `layout/ltcg/animation_set_active_count_00413790.json`

```json
{
  "schema_version": 1,
  "name": "animation_set_active_count_00413790",
  "source": "src/game/animation_set_active_count_00413790.cpp",
  "driver": "layout/ltcg/animation_set_active_count_00413790_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "AnimationManager_SetActiveCount compiled with native LTCG so the manager arrives in EAX and the count in ECX.",
  "functions": [
    {
      "name": "AnimationManager_SetActiveCount",
      "symbol": "?SetActiveCount@AnimationManager_00413790@@QAEXH@Z",
      "section": ".text$01accessor",
      "address": "0x00413790",
      "size": 77,
      "actual_abi": "this in EAX; count in ECX; plain RET"
    }
  ],
  "context": {
    "symbol": "?AnimationSetActiveCountCompilerContext@@YGHPAPAUAnimationManager_00413790@@H@Z",
    "section": ".text$03context",
    "address": "0x004137F0",
    "size": 40,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 75664 },
    { "section": ".text$02layout", "address": "0x004137DD", "size": 19 }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": []
}
```

Section order is load-bearing: `.text$01accessor` < `.text$02layout` <
`.text$03context` puts the model in the retail slot and the synthetic context after
it. No `absolute_symbols` and no roots — the model calls nothing.

## Shapes tried

1. **Free function `void Animation_SetActiveCount(void* state, int count)`** (the
   legacy-semantic reconstruction's signature) — rejected on paper, never built:
   under `/Gz` that is `__stdcall` with both arguments on the stack, so no receiver
   in EAX. The legacy model in
   `reference/legacy_semantic/src/game/recovery_leaves.cpp:93` supplied the
   semantics; only the signature had to change.
2. **Member, byte arithmetic** — `*(unsigned int*)((unsigned char*)this + 0x4CDC +
   index * 0x3AC)` with the first loop written as `for (; index < count; ++index)`
   and the second as `for (; index < 9; ++index)` — 77/77, `different_bytes` 0.
3. **Member, 0x3AC-stride record array** — the landed shape. Also 77/77,
   `different_bytes` 0, byte-for-byte the same as (2). Landed because it states the
   nine-record table and the record stride rather than raw offsets.

`__declspec(noinline)` was carried from the first build on the cluster lessons'
word (without it the `/GL` pass folds the model into the driver and the entry
collapses); no build here needed to prove that, every attempt already had it.

## One tool wrinkle worth recording

`cluster_attempt.py::_map_section` matches the map's length field with
`([0-9A-F]{8})H`, which is case-sensitive, while MSVC prints the length in
lowercase hex. Any function whose emitted size contains a hex letter therefore
reads back as `None`: 77 = `0000004dH` hit this, the sweep printed
`ERR size=None ctx=40`, and the error attributed to it was
"native function address or compiler origin differs" even though both the function
and the context were at exactly the addresses the layout declared. The real
failure was only the declared context size (48) against the emitted 40. Declaring
40 directly converged on the first build. (`[0-9A-Fa-f]` would fix the sweep.)

## Landed state and what else it touches

- `regions.json` was changed only by
  `python3 matching2/tools/waves/register_cluster.py --layout
  layout/ltcg/animation_set_active_count_00413790.json --apply` (run from
  `matching2/msvc`): region 0x00413790 became
  `semantic_AnimationManager_SetActiveCount_00413790` /
  `?SetActiveCount@AnimationManager_00413790@@QAEXH@Z`, the pre-registration record
  was kept under `previous_record`, and the layout was appended to `ltcg_clusters`.
  Nothing was hand-edited in the manifest. `translation_units` was re-derived by
  that tool and is unchanged: the sorted set of region sources equals the previous
  2394-entry list exactly.
- `build_msvc.validate_project` passes on the maintained manifest; the region
  partition still runs 0x401000..0x465C00 with no gap or overlap.
- The three caller units are untouched and keep calling the region by name. Their
  `_asm_Animation_SetActiveCount_00413790` reference is satisfied the same way 4342
  other fixed bindings are: the symbol stays in `config['symbols']`, is no longer a
  region symbol, so `make_link_script` emits it as an absolute assignment
  (`"_asm_Animation_SetActiveCount_00413790" = 0x413790;`) instead of skipping it.
  2424 of the current layout's bindings are referenced by some normalized object and
  defined by none, so absolute resolution of an undefined external is the proven
  path. `_asm_Animation_SetActiveCount_part_004137d0` (0x4137D0) keeps its binding,
  now unused.
- The stale duplicate naked copy in `src/game/recovery_leaves.cpp:608` (a bucket
  file, not the region's owner) is dropped by `normalize_unit`; the last full
  build's `unit0258.normalized.obj` already listed the symbol as an undefined
  reference only, so removing the definition from `unit0035` cannot create a
  duplicate definition.
- No project-wide build was run from this agent; `make`/`build_msvc.py` remain the
  integration owner's single per-wave gate.
