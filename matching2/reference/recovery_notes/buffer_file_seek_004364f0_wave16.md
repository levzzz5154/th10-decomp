# Wave 16: BufferFile::Seek (0x004364F0) — the shared tail's owner, measured (no landing)

2026-09-19, worker `BufferSeek`. Explored in `/tmp/BufferSeek/msvc` (a `cp -a` of
`matching2/msvc`) with `matching2/tools/matching/probe.py`. **Nothing landed**: no
manifest record, layout, source or cluster entry in the maintained tree was
touched, and the maintained tree is byte-clean (`git status --porcelain
matching2/msvc` empty). A non-exact layout must never be registered.

## Result — 107/107, seven bytes, and where they are

The wave-15 model reproduces exactly, first difference `0x436539`:

```text
$ python3 matching2/tools/matching/probe.py --source src/platform/memory_file.cpp \
      --project /tmp/BufferSeek/msvc --output /tmp/BufferSeek/out --show 64
0x004364f0     107 bytes  ?Seek@BufferFile@@UAEEJI@Z  DIFFERENT
  first difference at 0x00436539
  expected: e0 32 c0 5e c2 08 00 8b 44 24 08 85 c0 7c f2 3b 41 04 73 ed 8b 51 0c 03 d0 89 51 08 b0 01 5e c2 08 00
  actual:   16 32 c0 5e c2 08 00 8b 54 24 08 85 d2 7c f2 3b 51 04 73 ed 8b 41 0c 03 c2 89 41 08 b0 01 5e c2 08 00
  0x00436538: 7f e0  jg 0x43651a   vs actual 7f 16  jg 0x436550
```

`--json` reports `different_bytes: 7`, at exactly

| offset | retail | model | meaning |
|---|---|---|---|
| `0x436539` | `e0` | `16` | case 1's `jg` displacement: retail targets the tail inside **case 2's** block (`0x43651A`), the model the tail inside **case 0's** block (`0x436550`) |
| `0x436541` | `44` | `54` | case 0: retail `mov eax,[esp+8]` (distance), model `mov edx,[esp+8]` |
| `0x436545` | `c0` | `d2` | `test eax,eax` vs `test edx,edx` |
| `0x436549` | `41` | `51` | `cmp eax,[ecx+4]` vs `cmp [ecx+4],edx` |
| `0x43654e` | `51` | `41` | retail `mov edx,[ecx+0Ch]` (base), model `mov eax,[ecx+0Ch]` |
| `0x436551` | `d0` | `c2` | `add eax,edx` vs `add edx,eax` |
| `0x436553` | `51` | `41` | `mov [ecx+8],edx` vs `mov [ecx+8],eax` |

Everything else — the whole entry block, case 2's block including its own
`add/store/epilogue`, case 1's block, the `xor al,al; pop esi; ret 8` fail block
and the extent — is byte-identical. The two functions differ only in *which*
of two identical copies of `position_ = base + distance` (`+ mov al,1; pop esi;
ret 8`) case 1's success edge targets, and in the register case 0 must therefore
use.

## Why the seven bytes are a consequence, not a spelling

The model's source has one store after the switch, so `position_ = base +
distance` is a **single block T with three predecessors** (case 0, case 1,
case 2). The register allocator ties T's `base` phi to case 1's natural shape —
`eax = base`, `edx = distance` — which case 2 also produces. Case 0 then *must*
hand its `data_` over in `eax` and keep `distance` in `edx`, so it emits
`mov edx,[esp+8] … mov eax,[ecx+0Ch]; add edx,eax`. That is the model.

Retail's case 0 is a **separately allocated copy** (`base` in `edx`, `distance`
in `eax`), which is only possible if case 0 does **not** flow into T at all.
Every shape that takes case 0 out of T was built and measured; all of them fail
for one of two structural reasons, both of which are the compiler's, not the
statement's:

1. **The callee-save shrinks.** When case 0 owns its store and returns, its
   block uses no `esi`, so MSVC moves `push esi` out of the entry block into
   the non-case-0 dispatch path (it lands after the `je` to case 0), and case 0's
   own `return 0` then becomes a second, `pop`-less fail block. Retail's
   `push esi` *is* in the entry block at `0x4364F7`, which requires `esi` to be
   live on case 0's path — i.e. case 0's **failure** must reach the shared
   `xor al,al; pop esi; ret 8` block. Once that holds (all failures via one
   `fail:` label) the push stays at the top and case 0's block becomes retail's
   byte for byte — and then the layout duplicates T for case 1 (below).
2. **The layout duplicates the tail.** With case 0 separate and case 1/case 2
   sharing T, the compiler places T's canonical copy after **case 2** (retail's
   position) but gives case 1 a *second, 11-byte copy* as the fallthrough of its
   success arm, because case 1's fallthrough successor is T and T is already
   placed. It then emits case 1 as `jle fail` + fallthrough (the inverse of
   retail's `jg T`) instead of a backward `jg` into the copy that already
   exists.

## The levers asked for, measured (each compiled and byte-compared)

~200 shapes were probed against the retail image. The three named levers, and
the larger families they live in:

| shape | emitted | differing | first diff |
|---|---:|---:|---|
| wave-15 baseline (shared `base`, tail after the switch) | 107 | 7 | `0x436539` |
| **anti-mirror**: case 2 owns its store, case 0/case 1 break to the switch tail | 107 | 7 | `0x436526` |
| **best near-miss**: case 0 owns its store, *all* failures `goto fail` | 118 | — | extent |
| case 0 owns its store, failures `return 0` (the wave-15 "case 0 ends in a return" lever) | 122 | — | extent |
| case 0 owns its store, case 0 `goto fail`, case 1/case 2 `return 0` | 122 | — | extent |
| case 0 `return 0`, case 1/case 2 `goto fail` | 111 | — | extent |
| all three cases own their store (`+ return 1`) | 117 | — | extent |
| case 0 stores then breaks to the shared tail | 113 | — | extent |
| **inlined tail helper** `BYTE Finish(BYTE** slot, BYTE* base, LONG)` called once after the switch | 107 | 7 | `0x436539` |
| inlined helper `Finish(BufferFile* self, …)` (via a derived-class accessor) | 107 | 7 | `0x436539` |
| helper returning `BYTE`, called from **each** case's `return` | 117 | — | extent |
| helper only in case 0, cases 1/2 break to the tail | 122 | — | extent |
| **single-use accumulators**: `BYTE* t = base; t = t + distance; position_ = t;` per case | 117 | — | extent |
| single-use accumulator for the tail only (`base = base + distance; position_ = base;`) | 107 | 7 | `0x436539` |
| case 0 written as a stepwise accumulator `target = data_; target = target + distance;` | 122 | — | extent |

Also built and non-exact/identical to the mirror: all six source orders of the
case bodies (three families), `default` first/middle/last, all eight
`return 0` / `goto fail` failure-style assignments over the three cases with
`signed`/`unsigned`/`DWORD`/`size_t`/`char*`/`void*` base variables, `BYTE*
base = 0/data_/position_` initialisers, `BYTE* self = this` aliasing, cached
`data_`/`size_`/`position_` locals, `(BYTE**)((char*)this + 8)` stores,
`LONG`/`DWORD`/`size_t` base arithmetic, inlined-helper argument orders, the
`goto apply` / `goto out` / single-`fail`-label joins, `for(;;)`, `while(1)`,
`do{}while(0)` and `if (origin <= 2)` wrappers, a second empty `switch`, and
seven dead-statement perturbations. A six-spelling `if/else if` chain instead
reproduces a different dispatch (`cmp $1`/`cmp $2`) and emits 110–114 bytes, so
the `switch` lowering is required.

## The two closest shapes in full

**118 bytes — retail byte for byte except case 1** (`case 0` store + `return 1`,
everything else `goto fail` to one label). Emitted:

```text
0x00  8b 44 24 08           mov eax,[esp+8]        <- entry, retail
...
0x35  8b 51 04 8b 71 0c 8b 41 08 03 f2 8b 54 24 08 2b f0 3b f2
      7f/7e ...              <- case 1, retail's registers
0x4a  <11-byte copy of the tail>   <- the extra block
0x55  8b 44 24 08 85 c0 7c f2 3b 41 04 73 ed 8b 51 0c 03 d0 89 51 08
      5e c2 08 00            <- case 0, byte-identical to retail 0x436540
0x70  32 c0 5e c2 08 00     <- fail, byte-identical to retail 0x43653A
```

```cpp
BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    BYTE* base;
    switch (origin) {
    case 0:
        if (distance < 0 || (DWORD)distance >= size_)
            goto fail;
        position_ = data_ + distance;
        return 1;
    case 1: {
        LONG remaining = (LONG)((data_ + size_) - position_);
        if (remaining <= distance)
            goto fail;
        base = position_;
        break;
    }
    case 2: {
        if (distance > 0)
            goto fail;
        if ((DWORD)(distance < 0 ? -distance : distance) >= size_)
            goto fail;
        base = data_ + size_;
        break;
    }
    default:
        goto fail;
    }
    position_ = base + distance;
    return 1;
fail:
    return 0;
}
```

The entry, case 2's block (tail included), case 1's *registers*, case 0's block
and the fail block are each byte-identical to retail's corresponding block. The
delta is exactly (a) case 1's `jle 0x70` where retail has a backward
`jg 0x43651A` into case 2's tail, (b) the 11-byte duplicate of `add edx,eax;
mov [ecx+8],eax; mov al,1; pop esi; ret 8` the compiler emits after case 1 as
that fallthrough, and consequently (c) the fail block landing at the end
(0x70) instead of between case 1 and case 0 as in retail — case 0 is byte-equal
to retail's but sits 5 bytes early.

**107 bytes, the anti-mirror** — case 2 owns its store, case 0 and case 1 break
to the switch tail. Case 0's block and case 2's block are then byte-identical to
retail's, and *case 1* is the one the phi constrains (its `size_`/`position_`/
`distance` registers swap: differences at `0x436526`, `0x43652c`, `0x43652f`,
`0x436531`, `0x436535`, `0x436537`, `0x436539`). This is the wave-15 mirror with
the 7 bytes moved from case 0 to case 1; it proves the tail's owner decides the
whole allocation and that the compiler will always bind case 1 to whichever
copy the layout makes canonical.

## LTCG is not the lever (measured, this time with a live body)

Wave 15 could not read its `/GL`+`/LTCG` control because `/INCLUDE:` did not
retain an unreferenced `/GL` body. Built here with a real caller and entry:

```text
wine cl.exe /nologo /c /O2 /Gz /MT /Gy /G6 /GF /GS /Zl /GL /I<project>\include 
     /Foseek_probe.obj seek_probe.cpp          (body + __stdcall SeekProbeEntry
                                                calling file->BufferFile::Seek(0,1))
wine link.exe /nologo /LTCG /MACHINE:X86 /BASE:0x400000 /SUBSYSTEM:WINDOWS 
     /ENTRY:SeekProbeEntry@4 /FIXED /INCREMENTAL:NO /NODEFAULTLIB /OPT:REF 
     /OPT:NOICF /OUT:probe.exe seek_probe.obj
```

The LTCG-generated body is the model's mirrored body **byte for byte**,
including `jg 0x401060` and case 0 with `edx` holding `distance`. So the
cluster path cannot flip this region's tail ownership; the decision is inside
the translation unit's backend either way.

## An inline definition in the class is not the lever either

Moving the same body out of `memory_file.cpp` and into `BufferFile` as an
in-class `virtual BYTE Seek(LONG distance, DWORD origin) { … }` (so the
out-of-line copy is emitted by the vtable-owning TU through the inline path) is
byte-identical to the `.cpp` definition: 107/107, 7 differing, first `0x436539`.

## Compiler flags

Added one at a time through `source_flags` for this source: `/Ob1 /Oi- /G5 /Op
/Oh /GS- /GF- /Ot- /Ob2` all reproduce 107/7 identically; `/Os`, `/Oy-`, `/G7`,
`/Ow`, `/Oa` change *other* regions of `memory_file.cpp` (so they are not the
retail TU's flags). No flag flips the tail owner.

## What would unblock it

The bytes are decided by two coupled compiler decisions that no statement
spelling reached in ~200 attempts: the callee-save shrink-wrap point (which
follows whether case 0's failure reaches the shared fail block) and which
predecessor gets the canonical `position_ = base + distance` block (which the
layout's fallthrough chain picks and then duplicates). A lever that pins the
save in the entry block *while* case 0 is not a T predecessor would land this
region; nothing in the source language tested here expresses it. The sibling
`0x0042A3E0` (68 bytes, `..._wave15.md`) is stalled on the same class of
decision, and `src/platform/memory_file.cpp` keeps the region as
`asm_FUN_004364f0_004364f0` until that lever exists.

**Regions unblocked: none.** The region itself stays `asm`; neither the model nor
any measured variant is eligible to register.

## Probe line used for every variant

```text
python3 matching2/tools/matching/probe.py --source src/platform/memory_file.cpp \
    --project /tmp/BufferSeek/msvc --output /tmp/BufferSeek/out --show 64
```

`build_msvc.validate_project` was deliberately not run: nothing was promoted, so
there is no manifest change to validate.

## 2026-10-05: structure found, one shrink-wrap decision left (not recovered)

Rig: `build/experiments/seek_4364f0_claude` (`run.py name...` compiles
`v/<name>.cpp` with plain `/O2` and diffs the disassembly; `ltcg.py` does the
same through a minimal `/GL` + `/LTCG` link). Tracers:
`reference/compiler_traces/flowgraph/trace_lateflow_cl.py` and
`trace_points_cl.py`, `shrinkwrap/trace_shrinkwrap.py <source.cpp>`.

### What the retail layout means

c2 lays blocks out in reverse post-order (branch target visited first), and
re-threads them the same way inside `MscShrinkWrap`. A join block therefore
always follows all of its predecessors. Retail has the shared store after
case 2 but *before* case 1, and the fail block before case 0, so neither was a
join when the blocks were ordered:

* every case owns its `position_ = ...; return 1;`;
* case 1 and case 2 (and the default) fail through one `fail:` block, which
  reverse post-order puts right after case 1;
* case 0 fails with its own `return 0`.

The shared tails are then made by the late flow pass
(`FgDoLateFlowOptsOnce`, mode 2): `FgDoCommonTailMerge` refuses tails shorter
than 20 bytes when optimising for speed, *except* through
`FgTailMergeWithoutCheck`, which accepts a tail that is a whole block after an
unconditional jump, or a tail of the form `jcc L; <tail>; L:` where `L` runs
straight into the epilogue. Case 1's `jle fail; add; store; mov al,1` followed
by `fail:` is exactly the second form, which is why it becomes
`jg <case 2's tail>` and falls into `fail`.

### Best model (variant `q1`, 47 instructions, all of retail's except three)

```cpp
BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    switch (origin) {
    case 0:
        if (distance < 0 || (DWORD)distance >= size_)
            return 0;
        position_ = data_ + distance;
        return 1;
    case 1:
        if ((LONG)((data_ + size_) - position_) <= distance)
            goto fail;
        position_ += distance;
        return 1;
    case 2:
        if (distance > 0)
            goto fail;
        if ((DWORD)(distance < 0 ? -distance : distance) >= size_)
            goto fail;
        position_ = data_ + size_ + distance;
        return 1;
    }
fail:
    return 0;
}
```

Case 2, the shared store, case 1 (`jg` back into case 2), the fail block and
case 0's instructions are retail's. The one remaining difference: c2
shrink-wraps `push esi` to after `je case0`, so case 0 returns without
`pop esi` and keeps a private `xor al,al; ret 8`. Retail pushes ESI in the
entry block; case 0's own fail block is then identical to `fail` and is merged
into it.

### What does not move the push

Case order, `return`/`goto`/`break` exit styles (48 combinations), a shared
`ok:` label, spelling of case 0, locals cached before the switch, an emitted
vtable, and a `/GL` + `/LTCG` build all leave the push after the first branch.
Sharing the fail block with case 0 moves it to the entry but makes the fail
block a join of case 0, which puts it last (the 118-byte shape).

For the Riscify scratch register of case 0's `cmp eax,[ecx+4]` to be ESI (the
only way found for case 0 to touch ESI before shrink-wrapping) EDX would have
to be live across that compare; `GetReg` picks EDX there with live set
{EAX, ECX}. Open question: what keeps ESI (or EDX) busy on case 0's path in
retail.

## 2026-10-05 (later): recovered

`BufferFile::Seek` is now ordinary C++ in `src/platform/memory_file.cpp`
(107 bytes, probe EXACT, `make` and `make EXACT=1` pass). The asm file is gone.

Two source facts close the gap left above:

1. **All origins share `return 1`** (each case ends in `break`). The restore
   of ESI then has a common successor with case 0, so `MscShrinkWrap` keeps
   `push esi` in the entry block. The late flow pass copies the shared return
   back into each case, so the bytes show three separate `mov al,1` tails.
2. **Case 0's range check is an inline `bool` helper**
   (`Contains(offset)`: `offset >= 0 && (DWORD)offset < size_`) and its
   failure is a plain `return 0`, not `goto fail`.

Why 2 matters (traced with `trace_lateflow_cl.py`): with the check written
inline, the block list before the late flow pass is
`case 2, case 1, fail, case-1 store, case 0, return 1, fail0, EXIT`.
`FgTryTailMerge` compares the code before a `jmp EXIT` with the code that
falls into `EXIT`; `fail0` falls into `EXIT`, so `fail` is deleted, its
references move to the end and case 1 loses the `jcc L; tail; L:` shape that
lets its store merge into case 2's. Retail keeps `fail` in the middle, so the
block falling into `EXIT` was not a `return 0`. Branch polarity in the source
(`&&`, `||`, nesting, `goto`) is normalised away and never changes this; the
inlined helper does (interpretation: its boolean result makes the success
path the first one reached from case 0 when blocks are ordered, so case 0's
failure block is no longer last).

Variants `h1`, `h4`, `h5`, `h7` in the rig all match; `h7` is the same thing
with a local `bool ok`. The helper form was promoted as the most natural.
