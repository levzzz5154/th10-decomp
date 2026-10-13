# Joystick binding reader 0x0044A190: equivalent-recovery reconnaissance (2026-10-13)

Still inline assembly. This note records what a session of equivalence-tool
measurements and native-LTCG allocator traces established, so the next attempt
does not re-derive it. It extends
`joystick_binding_reader_0044a190_allocator_findings_2026_10_11.md`, whose
findings were all measured with **standalone `cl /O2` compiles**; this session
measured the **native `/LTCG` link** that the production cluster and
`equivalence.py` actually build, and the two environments allocate
systematically differently.

## The measurement harness

`matching2/tools/matching/equivalence.py --layout
layout/equivalent/joystick_poll_0044a190.json` compiles a draft source with
`/GL`, links it natively with `/ENTRY:` and `/INCLUDE:` roots, and compares the
function at 0x0044A190 instruction by instruction. For every source shape
tried, the tool's link produced **exactly 833 bytes** for the function body —
the extent always fits the region; only the instruction streams differ.
`matching2/build/msvc/text.bin` (extracted from the oracle image) must exist
for the tool to run.

## What the /LTCG link does differently from a standalone compile

Measured repeatedly across ~40 source shapes (the 2026-10-11 helper and
single-function models, plus new shapes):

- **The action mask gets an entry spill.** Every shape emits
  `mov [esp+X],ecx` immediately before the flags branch, in addition to the
  retail `mov esi,ecx`. The spill's readers are the three shared-exit blocks
  (`mov ax,WORD PTR [esp+X]` instead of retail's `mov ax,si`) and every
  DirectInput button test (`mov eax,[esp+X]` before each `or esi,...`).
  The spill exists because the allocator gives the DirectInput byte temps the
  mask's ESI home; retail keeps the temps in EAX by self-overwriting the index
  register (`movzx eax,BYTE PTR [esp+eax*1+0x78]`), which the /LTCG scheduler
  does not do when the spill has freed ESI. The two are mutually reinforcing:
  the spill frees ESI, the temps take ESI, the exits then need the spill.
- **The buttons word lands in EAX instead of EDX**, and the per-test
  temporaries shift accordingly (`mov esi,0x1; shl esi,cl` against retail's
  `mov eax,0x1`).
- **The binding record is rematerialized per path** (an `imul` at the first
  button test of each path, home EAX) instead of retail's persistent
  entry-computed EBX with the `mov ebx,eax` copy from a dead EAX temporary.
- **The pad index is cached in a callee-saved register** (EDI/ESI) across the
  DirectInput path; standalone compiles reload `[ebp+0xc]` per use as retail
  does. `volatile` on the pad restores the reloads but then also re-reads the
  pad for every JOYCAPS access (seven `imul ...,0x194` instead of one) and
  turns `pad != 0` into the `neg/sbb/neg` idiom instead of retail's
  `test/setne`, and the frame drops to 0x14c.
- The winmm axis block folds all four terms into one chain and merges the mask
  last; retail finishes the X pair into the mask (`or esi,edi`) before the Y
  pair. Because the model's mask home is the spill slot, its axis block
  additionally evicts ESI for `wYmax` and writes the mask back after every
  button test.

## Levers tried and rejected (all measured through the tool or the
isolated-TU cluster `layout/ltcg/joystick_poll_0044a190.json` in the scratch
tree)

- **ABI pins** (volatile/global/absolute-address escapes of the function
  pointer) and **direct, real-caller (`FUN_0044a5f0` co-compiled), indirect
  and no-caller contexts**: the whole-program pass re-derives the ABI for
  every shape that has a direct call edge and a body with call demand
  (ECX goes to the first-used parameter — the binding-set index — and the
  mask is demoted to the stack). The declared `__fastcall` ABI only survives
  with no caller edge at all, which the equivalent tool's `roots` mechanism
  provides; the allocation nevertheless keeps the entry spill.
- **`unsigned __int64 selection` parameter** (low half = binding set, high
  half = pad): reproduces the retail stack layout and is not re-homed by the
  pass, but does not change the allocator's mask decision.
- **`volatile` pad** (standalone and cluster): restores the pad reloads and
  the retail test/setne shape via a by-value `PadSelection` struct, and with
  a delayed binding computation it puts the mask in ESI at entry — but bloats
  the winmm axis block (seven pad re-reads) and drops the frame to 0x14c.
- **16-bit truncation boundaries** between the X and Y merges
  (`(unsigned short)mask` intermediates, a volatile round-trip through the
  dead `info.dwReserved1`): the round-trip variant does force the X/Y split
  and reaches 92 identical instructions, but every pure 16-bit spelling folds
  legally because the return value is only read as AX.
- **Accumulator locals** (`unsigned int acc = mask;`), delayed binding
  computations, `break`-form retry loops, `unsigned int` return types,
  named buttons locals: all coalesced or measured worse.
- The **copy-defined binding** (`mov ebx,eax` from a dead EAX temporary) is
  the linchpin of retail's allocation: with it, the binding occupies EBX from
  entry, the buttons fall to EDX, the temporaries to EAX, ESI stays the mask,
  and the spill has no reason to exist. Every source spelling that should
  produce it (the inlined-helper argument, intermediate locals, by-value
  wrappers) is coalesced by the 13.10 front end before allocation.

## Closest measured state

`equivalent/platform/joystick_poll_0044a190.cpp` (the 2026-10-11
`inline_helper_int_mask` model plus a non-calling entry stub) through the
tool's native link: **833 of 833 bytes, 126 of 282 instructions identical,
145 listed (30 hunks) plus 11 frame-offset** at frame delta −8 — 68.1 %
covered against the 33.3 % total budget. The draft layout and source stay
under `layout/equivalent/` and `equivalent/platform/` for `--layout`
measurement; they are not registered.

## Next lever

One of two things would close this function:

1. A source construct that keeps the binding's `mov ebx,eax` copy alive
   through the /LTCG link (the copy demotes the binding below the mask, which
   cascades the buttons to EDX, the temporaries to EAX and removes the entry
   spill — the whole 50-instruction residual). Reverse-engineering c2's
   copy-coalescing pass (the Ghidra c2.dll project) to learn what suppresses
   it would target this directly.
2. A c2-level understanding of the pre-allocation memory-home decision that
   spills the mask at the path split; the regalloc tracers in
   `reference/compiler_traces/regalloc/` can already dump
   `ChoosePhysReg`/`Spill` events for this exact link (reproduce with the
   link command from `equivalence.py`'s `build_model`), and the mask
   candidate's re-queue with the restricted register set {EBX,ESI} is visible
   there.

## 2026-10-13 addendum: c2.dll landmarks and the plain-static variant

Ghidra (`/compiler_reference/c2.dll`, base 0x10700000) confirmed and named:

- `ChoosePhysReg` at **0x107AAB62** (function created; the score table it
  clears is at 0x10882678, the conflict hash at 0x108827B0 — the same
  addresses the regalloc tracer reads).
- The **allocator driver** at **0x107A926D** (contains the ChoosePhysReg call
  site at 0x107A9EEA and the tracer's `blk` hook 0x107A98EE). Inside it, at
  **0x107A9313**, the candidate's +0x40 weight is *decremented by a product*
  (`imul` against [ESP+0x24]) — the live "minus the candidate's own
  preferences" term of the score note.
- A **candidate-picking function** at **0x107A9D71** that walks the conflict
  hash, compares the +0xC priority fields directly (`cmp esi,ecx; jg`) and
  calls `Spill` (0x107B3C97) for the loser — the spill-versus-register
  decision point for a candidate.
- Candidate flags at +0x4 correlate with the role: 0x0C02 marks candidates
  that serve as memory-address bases (the caps base, the X limits, the
  binding), 0x0402 the rest; 0x28402 marks the CL-constrained shift-count
  temporaries.

A final variant — the helper left as a **plain `static`** (inlined at the
/LTCG stage instead of the front end) — was linked manually (the
equivalence tool cannot read its map: the LTCG placement contradicts the map
symbol values). Its entry has **no `[esp+X]` spill**: the mask's memory home
lands in the *dead set-parameter slot* (`mov DWORD PTR [ebp+0x8],ebx` — the
set value dies at the imul and the compiler reuses its stack slot), with the
exits reading EBX and the DirectInput temporaries in ECX. The binding still
rematerializes per path in ESI and the buttons stay in EAX, so the residual
remains ~200 instructions of diff lines; the map quirk also blocks tool
measurement of this shape.

The 833-byte ceiling is hard for every shape measured: the tool rejects
models whose body exceeds the region (all volatile-pad variants, which would
need ~155 bytes, fail there), and the two shapes that fit exactly (the
2026-10-11 helper model and the struct-param variant) both keep the
entry-spill allocation.

## 2026-10-13 addendum 2: the plain-static wrapper and the copy theory

Linking the plain-`static` helper shape manually explained the tool error and
killed the leading theory. The /LTCG inliner does **not** inline the helper
into ReadPad; it emits ReadPad as an **argument-shuffle wrapper** at the map
address:

```text
mov eax,ecx                 ; the mask (ECX) aside
mov ecx,[esp+4]             ; the binding-set index
imul ecx,ecx,0x6a
add ecx,0x474e30            ; the binding record, computed in volatile ECX
mov [esp+4],eax             ; the mask stored into the freed stack slot
jmp 0x401000                ; tail-jump to the inlined body
```

The body therefore receives the mask **copy-defined** (in EAX and on the
stack) and the binding **copy-defined** (`mov esi,ecx` from the volatile ECX
computation) — both copies alive, exactly the structure the copy theory
requires. The allocation still assigns ESI to the binding and EBX plus the
reused `[ebp+8]` slot to the mask: **copy-definition alone does not promote a
candidate**, and the binding's priority outranks the mask's in every shape
measured. The equivalence tool cannot measure this shape anyway: the LTCG
linker's map reports section lengths that contradict the placement (the
function spans past the mapped `.text` raw data), so `PEImage.read` rejects
the region.

What remains undecided in c2 is the priority computation itself (candidate
field +0xC): the pick function at 0x107A9D71 compares it directly
(`cmp esi,ecx; jg`) and spills the loser, and the driver at 0x107A9313
decrements the +0x40 weight by a product, but the code that *initializes*
+0xC from the use tuples was not located. That initialization is the next
reverse-engineering target: whatever makes the 17-use mask candidate score
43-66 while the 10-use binding scores 114 is the rule the source must defeat.

## 2026-10-13 addendum 3: the priority accumulation, decoded

The driver disassembly (0x107A926D..0x107A9D6E) plus the two walk functions
decode the priority as a **position- and loop-weighted accumulation over the
candidate's register references**:

- Per reference (the walk at 0x107A9659): the candidate's +0x18 field
  accumulates a per-reference value (`f18 += eax`), its +0x40 weight
  accumulates `eax × [ESP+0x24]` (the block's loop-depth weight), its +0x24
  reference count increments, and **the +6 |= 0x10 flag is set** — 0x10 marks
  "this candidate's references have been counted". The per-reference value
  comes from `0x107A99D9(ECX = the walk position marker)`.
- Per block (the tracer's `blk` hook, 0x107A98EA): `eax` counts the block's
  reference chain, `edx = eax × [ESP+0x24]`, and then for each candidate in
  the chain: **`priority += f18 × edx` and `f18 = 0`** (0x107A991C), with a
  **subtraction path** (`priority -= edx`, 0x107A997E) for candidates flagged
  `+6 & 0x10` on one branch. `ChoosePhysReg` then scores registers against
  this priority.

The consequence for 0x0044A190: the mask's *late* references (the shared-exit
reads, which are the function's last blocks) and its post-spill references
(the DirectInput button tests read the spill slot — a **different**, memory
candidate — and therefore do not count for the register candidate at all)
leave the register-resident mask candidate with only its mid-function OR
references, weighted less than the binding's reads. In retail, where no spill
exists, every reference — including the exits — counts for the one ESI
candidate, which is why retail's mask outranks the binding, the retry counter
and the axis limits.

This closes the loop on the mechanism but does not yet yield a source lever:
the split that moves the exit references onto the memory candidate is itself
the thing the spill causes. The remaining reverse-engineering target is the
per-reference value function 0x107A99D9 (what the walk position contributes)
and the earlier pass that decides the initial memory home for an incoming
register parameter that is live across calls and modified after them.

## 2026-10-13 addendum 4: the register-provenance hypothesis, disconfirmed

The three retail callers pass the mask from callee-saved registers (EDI at
0x0044A5F0 and 0x0044A9D0, ESI at 0x0044AD30 - `mov ecx,edi` / `mov ecx,esi`
before the call). The hypothesis: the whole-program pass inherits that
provenance into the callee's initial-home decision, which is why retail's
mask has no spill. Tested with a cluster whose context pins the ABI (the
volatile address escape), calls the reader **directly** (the whole-program
edge visible) and carries the mask **loop-carried through the call** (`held =
f(held, ...)` — the value the caller provably holds in a callee-saved register
across the call). Result: the ABI stays pinned (`mov ebx,ecx` at entry) but
the allocation is unchanged — binding ESI, mask EBX plus the `[esp+X]` spill.
Register provenance does not reach the candidate's initial-home decision.

The decoded accumulation also explains why no source spelling can flip the
ordering: the priority is a fixed function of the reference structure
(tuple-weight sum × reference count × loop weight per block). The mask's
references are inherently spread across the function's late, low-weight
blocks (the ORs, the axis merges, the three exits), while the binding's
cluster in the mid-weight button-test blocks and the retry counter's sit
inside the loop (loop-tuple weights). The CFG is fixed by retail semantics,
so the relative ordering binding > mask is not reachable from the source.

The two remaining unknowns are c2-internal and not source-reachable: the
tuple-weight initialization inside the per-reference walk (function
0x107A99D9 returns per-tuple-type constants 1-4 and loop-depth+1 for loop
tuples, but the block-level combination that produced 43/66/114/132 was not
fully inverted), and the earlier pass that chooses the initial memory home
for an incoming register parameter that is live across calls and written
after them.
