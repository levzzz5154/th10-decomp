# 0x00418A00 landed as a native-LTCG cluster: `ScoreState::DecayGauge`

2026-09-19, wave 5. Region `0x00418A00..0x00418A40`, 65 bytes, source
`src/game/recovery_decay_counter_00418a00.cpp`. **EXACT via the native-LTCG
cluster path**, as a *merge* into the already-registered
`layout/ltcg/frame_timer.json` (one new function in a new additional source; the
seven functions that cluster already carried are untouched and still exact).

Probe line (throwaway copy, `--project /tmp/DecayCounter/msvc`):

```text
0x00404ed0      72 bytes  ?Tick@FrameTimer@@QAEXXZ  EXACT
0x00405410      57 bytes  ?SetSchedulerValue@PlayerSchedulerRecord@@QAEXH@Z  EXACT
0x00418a00      65 bytes  ?DecayGauge@ScoreState@@QAEXXZ  EXACT
0x00428dd0      20 bytes  ?Decrement@FrameTimer@@QAEXH@Z  EXACT
0x0043bd40      93 bytes  ?Tick@AnimationCursor_0043bd40@@QAEHXZ  EXACT
0x0043c230     133 bytes  ?Tick@AnimationCursor_0043c230@@QAEHXZ  EXACT
0x0043c460     154 bytes  ?Tick@AnimationCursor_0043c460@@QAEHXZ  EXACT
0x0044bf40      88 bytes  ?Advance@FrameTimer@@QAEXM@Z  EXACT
EXACT
```

```
python3 matching2/tools/matching/probe.py \
    --source src/game/recovery_decay_counter_00418a00.cpp \
    --project /tmp/DecayCounter/msvc --output /tmp/DecayCounter/out --show 30
```

All 65 bytes equal retail's, and the emitted interactive disassembly is
retail's instruction for instruction (exported body, `bodies.obj`, section
`.r000008`):

```text
   0:	mov    0x18(%eax),%ecx
   3:	test   %ecx,%ecx
   5:	push   %esi
   6:	jle    17
   8:	push   $0xbf800000
   d:	lea    0x14(%eax),%esi
  10:	call   0x44bf40
  15:	pop    %esi
  16:	ret
  17:	mov    0xc(%eax),%ecx
  1a:	mov    $0x1388,%esi
  1f:	cmp    %esi,%ecx
  21:	jle    3f
  23:	mov    0x10(%eax),%edx
  26:	sub    %edx,%ecx
  28:	cmp    $0x12,%edx
  2b:	mov    %ecx,0xc(%eax)
  2e:	jge    37
  30:	movl   $0x12,0x10(%eax)
  37:	cmp    %esi,0xc(%eax)
  3a:	jge    3f
  3c:	mov    %esi,0xc(%eax)
  3f:	pop    %esi
  40:	ret
```

## What the region is

The receiver is the **global score record at `0x00474C40`**: retail's only
caller reaches it as a bare address constant —

```text
0041875f:  mov eax,474C40h
00418764:  call asm_Recovery_DecayCounter_00418a00
```

(`src/game/stage_update.cpp`, region `asm_FUN_00418190_00418190`, still naked
assembly, so nothing else needs a cutover). That object is the project's
`ScoreState` (`include/th10/game/score.hpp`), and the region is one of its
methods:

| offset | member | how the region reads it |
|---|---:|---|
| +0x0C | `gauge` | the value that decays |
| +0x10 | `gauge_decay` | the per-frame step, floored at 18 |
| +0x14 | `gauge_timer` (`FrameTimer`) | `current` at +0x18 is the guard, and `&gauge_timer` is what the call is handed |

The independent confirmation that +0x14 is a `FrameTimer` is `0x0042A6A0`,
which initialises exactly that shape (`previous = current - 1`,
`elapsed = (float)current`, `speed = &DAT_00476F78`, `flags |= 1`), and
`ScoreState::SetGauge` at `0x00418B80` in the same manifest family, which
resets the same five words. The gauge floor of 5000 is the floor
`ScoreState::ReduceGauge` uses, and `capped_count` at +0x50 is
`ScoreState::IncrementCappedCount`, the very next region (0x00418A90) — the
object is the score record, not an anonymous blob.

So, in readable terms: while the gauge timer still has frames on it
(`gauge_timer.current > 0`) the timer is advanced by `-1.0f` and the gauge is
left alone; once the timer has run out, the gauge bleeds off by `gauge_decay`
per frame, with the step floored at 18 and the gauge floored at 5000.

## Register evidence: what retail's callers use, and what the body keeps

* **The `ScoreState` arrives in EAX.** The only caller materialises the address
  as `mov eax,474C40h` — a 5-byte immediate load, the cheapest form for an
  address constant — and never passes it on the stack. Across that call EAX, ECX
  and EDX are all dead (the caller reloads ECX from `data_00474c88` and EAX from
  `data_00474c8c` at `0x418769`/`0x41876F`) while EDI, EBP, ESI and EBX stay
  live, so the receiver has to come to rest in one of the volatile registers;
  the pass picked EAX. The emitted body reads the record only through EAX
  (`0x18(%eax)`, `0xc(%eax)`, `0x10(%eax)`), so that agreement is kept.
* **The nested timer arrives in ESI.** Retail does `push esi`, then
  `lea esi,[eax+14h]; call 0x0044BF40`; `FrameTimer::Advance` is the
  `this in ESI; delta at [ESP+4]; RET 4` function already recorded in
  `frame_timer.json`, so ESI is the whole-program timer agreement. The emitted
  body is `push %esi` … `lea 0x14(%eax),%esi; call 0x44bf40` … `pop %esi` on
  both exits, i.e. the same ESI use and the same two plain `RET`s (no stack
  argument, no cleanup).
* No register is reassigned anywhere in the body, and the 4-byte `call` REL32
  reaches `0x0044BF40` unmodified (`0x418A10 + 5 + 0x3352B`).

## Why the cluster, and not a plain translation unit

The body is a `ScoreState` member with no arguments, so both the receiver and
the nested `this` are register conventions no MSVC declaration can express. The
The same model compiled as a plain translation unit (`plain.py`, measured on a
standalone object): **68 bytes against retail's 65, 59 differing bytes**, because
`this` arrives in ECX —

```text
retail 8b 48 18   mov ecx,[eax+0x18]     ours 8b 41 18   mov eax,[ecx+0x18]
retail 85 c9      test ecx,ecx           ours 85 c0      test eax,eax
retail 56         push esi               ours 7e 0e      jle +0xe (no push)
retail 8d 70 14   lea esi,[eax+0x14]     ours 83 c1 14   add ecx,0x14
```

— and the timer pointer is built in ECX for a `__thiscall` call rather than ESI.
The declaration (ordinary `__thiscall`) fixes nothing: the *linker* has to see
`FrameTimer::Advance` in the same native-LTCG unit and agree on ESI, which is
exactly what `layout/ltcg/frame_timer.json` already does for the three
animation cursors. Hence the merge rather than a standalone cluster: a new
cluster would have had to declare `?Advance@FrameTimer@@QAEXM@Z` opaque, and an
opaque callee can only ever be called through its declared ECX convention.

The four `ScoreState` setters in `layout/ltcg/score_bookkeeping.json` reproduce
the same shape (`states[index]->IncrementCappedCount()` comes out with the
record in EAX and a plain RET), which is the precedent the driver below leans
on; that cluster was not used because it cannot carry `frame_timer.cpp`, which
is already claimed.

## Files

* `src/game/recovery_decay_counter_00418a00.cpp` — the model. The file owns only
  this region, so the cutover is complete: it no longer defines
  `asm_Recovery_DecayCounter_00418a00`, and the naked caller in
  `src/game/stage_update.cpp` keeps resolving through the manifest's `symbols`
  entry `_asm_Recovery_DecayCounter_00418a00 = 0x00418A00`, which
  `make_link_script` writes into the link script because the region now defines
  the decorated name instead.
* `include/th10/game/score.hpp` — one added declaration,
  `__declspec(noinline) void DecayGauge();`, next to the other `ScoreState`
  methods. A declaration only; it changes no emitted byte of the score cluster.
* `layout/ltcg/frame_timer.json` — the merge (new function entry, the new
  additional source, the score header, one split layout gap, a recomputed
  context extent and the tail gap). Complete text below.
* `layout/ltcg/frame_timer_context.cpp` — the driver, extended with an eighth
  parameter and the array walk over the gauge records.

## The model, verbatim (`src/game/recovery_decay_counter_00418a00.cpp`)

```cpp
// 0x00418A00..0x00418A40 (65 bytes): ScoreState::DecayGauge
//
// The gauge is raised by SetGauge/AddGauge and then runs down again. Two
// stages do that: while the gauge timer at +0x14 still has frames on it the
// timer is advanced by -1.0f, and once it has run out the gauge itself bleeds
// off by the decay step at +0x10, one step per frame, with the gauge held at
// the 5000 floor the other gauge updates use and the step held at 18.
//
// Retail, in order:
//     8B 48 18        mov ecx,[eax+18h]      ; gauge_timer.current
//     85 C9           test ecx,ecx
//     56              push esi
//     7E 0F           jle decay
//     68 00 00 80 BF  push 0BF800000h        ; -1.0f
//     8D 70 14        lea esi,[eax+14h]      ; &gauge_timer
//     E8 .. .. .. ..  call FrameTimer::Advance
//     5E C3           pop esi / ret
//  decay:
//     8B 48 0C        mov ecx,[eax+0Ch]      ; gauge
//     BE 88 13 00 00  mov esi,5000
//     3B CE           cmp ecx,esi
//     7E 1C           jle done
//     8B 50 10        mov edx,[eax+10h]      ; gauge_decay
//     2B CA           sub ecx,edx
//     83 FA 12        cmp edx,18
//     89 48 0C        mov [eax+0Ch],ecx
//     7D 07           jge skip
//     C7 40 10 12 00 00 00  mov [eax+10h],18
//  skip:
//     39 70 0C        cmp [eax+0Ch],esi
//     7D 03           jge done
//     89 70 0C        mov [eax+0Ch],esi
//  done:
//     5E C3           pop esi / ret
//
// The receiver arrives in EAX and the nested timer in ESI. Neither is a
// register an MSVC convention can express, so this source is compiled in the
// native-LTCG link that also carries FrameTimer::Advance
// (see layout/ltcg/frame_timer.json): the whole-program pass selects EAX for
// the gauge record and ESI for the timer the advance call is handed.
#include "th10/game/score.hpp"

#pragma code_seg(".text$04zdecay")
void ScoreState::DecayGauge() {
    if (gauge_timer.current > 0) {
        gauge_timer.Advance(-1.0f);
        return;
    }
    if (gauge > 5000) {
        gauge -= gauge_decay;
        if (gauge_decay < 18)
            gauge_decay = 18;
        if (gauge < 5000)
            gauge = 5000;
    }
}
#pragma code_seg()
```

The 65-byte extent is not a coincidence: the guard is the `> 0` form
(`test ecx,ecx` / `jle`, no `cmp`), the step's floor is a signed `< 18`
(`cmp edx,12h` / `jge`), and the gauge floor is the signed and the unsigned
comparison retail uses (5000 fits both, and MSVC picks the `cmp ecx,esi`
register form because 5000 is hoisted into ESI and reused by the tail). Writing
the three statements in retail's own order — subtract, then the step floor, then
the gauge floor — is what keeps the store of the decremented gauge ahead of the
branch on the old step (statement reordering is not needed and must not be
done: the compiler rotates a run of component statements by one).

## The driver, verbatim (`layout/ltcg/frame_timer_context.cpp`)

```cpp
// Compiler context only: this caller is not a recovered application function.
// One native-LTCG unit reaches the FrameTimer methods, all three animation
// cursors, and the scheduler store, so MSVC selects the verified internal
// register conventions: ECX cursor entries, EAX for the scheduler receiver,
// and ESI for the embedded timers.  The cursors are additional linker roots,
// which keeps their public ECX entry while their internal calls stay private.
#include "../../src/math/frame_timer.cpp"
#include "th10/game/score.hpp"

struct PlayerSchedulerRecord {
    void SetSchedulerValue(int value);
};
struct AnimationCursor_0043bd40 { int Tick(); };
struct AnimationCursor_0043c230 { int Tick(); };
struct AnimationCursor_0043c460 { int Tick(); };

#pragma code_seg(".text$15context")
extern "C" void __stdcall AnimationTimerSchedulerCompilerContext(
        FrameTimer* timers, int count, int delta,
        AnimationCursor_0043bd40* cursor_bd40,
        AnimationCursor_0043c230* cursor_c230,
        AnimationCursor_0043c460* cursor_c460,
        PlayerSchedulerRecord* scheduler,
        ScoreState* scores) {
    for (int index = 0; index < count; ++index) {
        timers[index].Tick();
        timers[index].Advance(float(delta));
        timers[index].Decrement(delta);
    }
    if (cursor_bd40 != 0)
        cursor_bd40->Tick();
    if (cursor_c230 != 0)
        cursor_c230->Tick();
    if (cursor_c460 != 0)
        cursor_c460->Tick();
    if (scheduler != 0)
        scheduler->SetSchedulerValue(delta);
    if (scores != 0) {
        for (int index = 0; index < count; ++index)
            scores[index].DecayGauge();
    }
}
#pragma code_seg()
```

The array walk over `ScoreState*` in a loop that already holds the timers and
the cursors is what colours the record into EAX: the pointer is re-derived per
iteration, ECX/EDX are wanted by the timer calls and the cursor mix, and ESI is
spoken for by `Advance`. The context moved 116 -> **147** bytes and its
decoration from `@28` to `@32` (an eighth stack argument).

## Layout (`layout/ltcg/frame_timer.json`), complete

The seven original function entries, `roots`, `constants`, `constant_aliases`
and `absolute_symbols` are unchanged; the deltas are the new function, the new
`additional_sources` entry (appended last, so the module order of the existing
sources — and therefore their codegen — is untouched), the `score.hpp` header,
`context.symbol`/`context.size`, the split gap and the recomputed tail gap.

```json
{
  "schema_version": 1,
  "name": "frame_timer",
  "source": "src/math/frame_timer.cpp",
  "additional_sources": [
    "src/game/player_set_scheduler_value_00405410.cpp",
    "src/unidentified/FUN_0043bd40_0043bd40.cpp",
    "src/unidentified/FUN_0043c230_0043c230.cpp",
    "src/unidentified/FUN_0043c460_0043c460.cpp",
    "src/game/recovery_decay_counter_00418a00.cpp"
  ],
  "driver": "layout/ltcg/frame_timer_context.cpp",
  "roots": [
    "?Tick@AnimationCursor_0043bd40@@QAEHXZ",
    "?Tick@AnimationCursor_0043c230@@QAEHXZ",
    "?Tick@AnimationCursor_0043c460@@QAEHXZ"
  ],
  "headers": ["include/th10/math/timer.hpp", "include/th10/game/score.hpp"],
  "image_base": "0x00400000",
  "description": "FrameTimer methods, the three animation cursors, and the scheduler store compiled as ordinary C++ with a synthetic caller under native LTCG; the scheduler receiver stays in EAX and the embedded timers in ESI. Compiler context and layout gaps are never selected as game code.",
  "functions": [
    {
      "name": "FrameTimer_Tick",
      "symbol": "?Tick@FrameTimer@@QAEXXZ",
      "section": ".text$01tick",
      "address": "0x00404ED0",
      "size": 72,
      "actual_abi": "this in ESI; plain RET"
    },
    {
      "name": "PlayerSchedulerRecord_SetSchedulerValue",
      "source": "src/game/player_set_scheduler_value_00405410.cpp",
      "symbol": "?SetSchedulerValue@PlayerSchedulerRecord@@QAEXH@Z",
      "section": ".text$03scheduler",
      "address": "0x00405410",
      "size": 57,
      "actual_abi": "this in EAX; value on the stack; RET 4"
    },
    {
      "name": "FrameTimer_Decrement",
      "symbol": "?Decrement@FrameTimer@@QAEXH@Z",
      "section": ".text$05decrement",
      "address": "0x00428DD0",
      "size": 20,
      "actual_abi": "this in ESI; count in EAX; plain RET"
    },
    {
      "name": "AnimationCursor_Tick_0043bd40",
      "source": "src/unidentified/FUN_0043bd40_0043bd40.cpp",
      "symbol": "?Tick@AnimationCursor_0043bd40@@QAEHXZ",
      "section": ".text$07bd40",
      "address": "0x0043BD40",
      "size": 93,
      "actual_abi": "cursor in ECX; nested FrameTimer receiver selected in ESI; plain RET"
    },
    {
      "name": "AnimationCursor_Tick_0043c230",
      "source": "src/unidentified/FUN_0043c230_0043c230.cpp",
      "symbol": "?Tick@AnimationCursor_0043c230@@QAEHXZ",
      "section": ".text$09c230",
      "address": "0x0043C230",
      "size": 133,
      "actual_abi": "cursor in ECX; nested FrameTimer receiver selected in ESI; plain RET"
    },
    {
      "name": "AnimationCursor_Tick_0043c460",
      "source": "src/unidentified/FUN_0043c460_0043c460.cpp",
      "symbol": "?Tick@AnimationCursor_0043c460@@QAEHXZ",
      "section": ".text$11c460",
      "address": "0x0043C460",
      "size": 154,
      "actual_abi": "cursor in ECX; scheduler receiver in EAX; nested FrameTimer receiver in ESI; plain RET"
    },
    {
      "name": "FrameTimer_Advance",
      "symbol": "?Advance@FrameTimer@@QAEXM@Z",
      "section": ".text$13advance",
      "address": "0x0044BF40",
      "size": 88,
      "actual_abi": "this in ESI; delta at [ESP+4]; RET 4"
    },
    {
      "name": "ScoreState_DecayGauge",
      "source": "src/game/recovery_decay_counter_00418a00.cpp",
      "symbol": "?DecayGauge@ScoreState@@QAEXXZ",
      "section": ".text$04zdecay",
      "address": "0x00418A00",
      "size": 65,
      "actual_abi": "gauge record in EAX; nested timer in ESI; plain RET"
    }
  ],
  "context": {
    "symbol": "AnimationTimerSchedulerCompilerContext@32",
    "section": ".text$15context",
    "address": "0x0044BFA0",
    "size": 147,
    "description": "Synthetic caller roots every cursor, timer, gauge and scheduler edge; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 16080},
    {"section": ".text$02layout", "address": "0x00404F18", "size": 1272},
    {"section": ".text$04layout", "address": "0x00405449", "size": 79287},
    {"section": ".text$04zzlayout", "address": "0x00418A41", "size": 66447},
    {"section": ".text$06layout", "address": "0x00428DE4", "size": 77660},
    {"section": ".text$08layout", "address": "0x0043BD9D", "size": 1171},
    {"section": ".text$10layout", "address": "0x0043C2B5", "size": 427},
    {"section": ".text$12layout", "address": "0x0043C4FA", "size": 64070},
    {"section": ".text$14layout", "address": "0x0044BF98", "size": 8},
    {"section": ".text$16layout", "address": "0x0044C033", "size": 147405},
    {"section": ".rdata", "address": "0x00470000", "size": 2812}
  ],
  "constants": [
    {"symbol": "__real@3f800000", "address": "0x00470AFC", "value": 1.0}
  ],
  "constant_aliases": [
    {"symbol": "__real@4f800000", "address": "0x00470B98", "value": 4294967296}
  ],
  "absolute_symbols": [
    {"symbol": "_data_004918a4", "address": "0x004918A4", "kind": "data"},
    {"symbol": "_data_00477810", "address": "0x00477810", "kind": "data"},
    {"symbol": "_data_00470bf8", "address": "0x00470BF8", "kind": "data"},
    {"symbol": "?g_frame_timer_normal_lower@@3MA", "address": "0x00470B68", "kind": "data"},
    {"symbol": "?g_frame_timer_normal_upper@@3MA", "address": "0x00470B64", "kind": "data"},
    {"symbol": "__ftol2", "address": "0x00463B2C", "kind": "relative_code"},
    {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"}
  ]
}
```

Two mechanical points about the layout, both measured rather than computed:

* **The gap split.** `.text$04layout` was one 145,799-byte filler from
  `0x405449` to `0x428DD0`, and `0x418A00` sits inside it. It is now
  `0x405449 + 79,287` (ends exactly at `0x418A00`), the function's own
  `.text$04zdecay`, and `.text$04zzlayout` at `0x418A41` covering the remaining
  66,447 bytes to `0x428DD0`. The two tags sort between `.text$04layout` and
  `.text$05decrement` (`l < z`, and `04z…`/`04zz…` < `05…`), and the gap
  contributions land byte-aligned — the map shows `.text$04zdecay` at
  `0x418A00` and `.text$04zzlayout` at `0x418A41`, unaligned, exactly like the
  pre-existing `.text$08layout` at `0x43BD9D`. The 15 bytes of
  `text_padding_00418a41` are therefore *not* claimed by the cluster; they stay
  with `src/data/text_0041.cpp` in the outer image, and the cluster's own .text
  simply has no contribution there.
* **The tail gap had to be recomputed from the emitted context.** The context
  grew 116 -> 147, so `.text$16layout` moves from `0x44C014` to `0x44C033` and
  its size from 147,436 to 147,405, keeping `.rdata` at `0x470000`. Read the
  size from `cluster.map`'s `.text$15context` column, never guess it.

## Integration

Landed in the maintained project. The region record became

```json
{"name": "semantic_ScoreState_DecayGauge_00418a00",
 "source": "src/game/recovery_decay_counter_00418a00.cpp",
 "symbol": "?DecayGauge@ScoreState@@QAEXXZ",
 "address": "0x00418A00", "size": 65, "kind": "semantic", "owner": "0x00418A00",
 "previous_record": {"name": "asm_Recovery_DecayCounter_00418a00",
                     "symbol": "_asm_Recovery_DecayCounter_00418a00",
                     "kind": "asm", "...": "the rest of the pre-registration record"}}
```

`layout/ltcg/frame_timer.json` was already in `ltcg_clusters`. Nothing else in
the manifest moved: the source keeps owning exactly this one region, and
`translation_units` already listed it (the region's `source` never changed, so
no unit was added or removed). `make_link_script` needs no help either — the
naked caller in `src/game/stage_update.cpp` keeps resolving to `0x00418A00`
through the existing `symbols` entry `_asm_Recovery_DecayCounter_00418a00`,
which is now an absolute assignment rather than a definition.

Re-probed against the **maintained** project after the integration, not just
the sandbox:

```
python3 matching2/tools/matching/probe.py \
    --source src/game/recovery_decay_counter_00418a00.cpp \
    --project matching2/msvc --output /tmp/DecayCounter/real --show 30
0x00404ed0      72 bytes  ?Tick@FrameTimer@@QAEXXZ  EXACT
0x00405410      57 bytes  ?SetSchedulerValue@PlayerSchedulerRecord@@QAEXH@Z  EXACT
0x00418a00      65 bytes  ?DecayGauge@ScoreState@@QAEXXZ  EXACT
0x00428dd0      20 bytes  ?Decrement@FrameTimer@@QAEXH@Z  EXACT
0x0043bd40      93 bytes  ?Tick@AnimationCursor_0043bd40@@QAEHXZ  EXACT
0x0043c230     133 bytes  ?Tick@AnimationCursor_0043c230@@QAEHXZ  EXACT
0x0043c460     154 bytes  ?Tick@AnimationCursor_0043c460@@QAEHXZ  EXACT
0x0044bf40      88 bytes  ?Advance@FrameTimer@@QAEXM@Z  EXACT
EXACT
```

**Disclosure (pitfall 11).** I did *not* write the maintained
`regions.json`; the integration owner applied that record from the sandbox.
`register_cluster.py --apply` cannot register this cluster at all — it refuses
any layout whose functions' region sources differ from `layout["source"]`
("region 0x40af90 is owned by …", reproduced against the existing
`bullet_manager_load_scripts_0040ae70` layout), and this layout is a merge by
construction, so the record had to be applied by the integration path. The
sandbox had it applied at `/tmp/DecayCounter/msvc/regions.json`, which is what
the first probe above reads; every other file was copied into the project
verbatim.

The `translation_units` list never needed a change, but it was checked anyway
rather than assumed: `build_msvc.validate_project` (which the probes do not
run) accepts both the sandbox and the maintained manifest with the new record —
4,425 regions and 2,393 units in each, `load_clusters` accepts every registered
cluster, and the region at `0x418A00` is reported as
`semantic_ScoreState_DecayGauge_00418a00` /
`?DecayGauge@ScoreState@@QAEXXZ` / `semantic` with `frame_timer` carrying six
sources.


## Shapes tried

The merged model was exact on the first build; the only measurement needed was
the convention baseline, which is what justifies the cluster:

| # | shape | result |
| --- | --- | --- |
| 1 | the model as a plain translation unit (`__thiscall` member, standalone object) | 68 bytes, 59 differing: `this` in ECX (`8b 41 18`), no `push esi`, and the timer built with `83 c1 14` for an ECX receiver. The convention is unreachable without the callee in the link. |
| 2 | the model as an additional source of `frame_timer.json`, driver extended with an eighth `ScoreState*` parameter and an array walk | **EXACT**, 65 bytes, record in EAX, timer in ESI, both exits `pop esi; ret`. The seven pre-existing functions of the cluster are byte-identical too, so the added module did not disturb the plan. |

## Files left in the sandbox

`/tmp/DecayCounter/msvc` (also mirrored, together with both scripts, to
`matching2/build/waves/lab/DecayCounter/msvc`, which probes EXACT on its own):
`src/game/recovery_decay_counter_00418a00.cpp`,
`include/th10/game/score.hpp`, `layout/ltcg/frame_timer.json`,
`layout/ltcg/frame_timer_context.cpp`. `/tmp/DecayCounter/try.py` rebuilds the
cluster from the layout alone (ownership records are derived from the layout, so
a merge can be iterated before anything is registered) and prints the
byte-level diff of every function in it; `/tmp/DecayCounter/plain.py` is the
plain-translation-unit baseline above.
