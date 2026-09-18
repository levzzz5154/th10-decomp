# 0x00409230 ReleaseFlaggedEntities - model verified; blocked on the 0x004451C0 dispatcher's definition in the link

2026-09-19. Worker `ReleaseFlaggedEntities`. **No promotion**: the region is not
EXACT in the maintained tree and nothing in it changed except this note. All work
was done in a scratch copy (`cp -a matching2/msvc /tmp/ReleaseFlaggedEntities/msvc`).

The result in one paragraph: the region's recovered source is now **verified
byte-exact** - with a callee body present in the same `/LTCG` link at
`0x004451C0`, the region compiles to retail's 50 bytes with **zero differing
bytes**, including both call displacements. What cannot be landed today is the
callee: `0x004451C0` is an unrecovered 216-byte dispatcher whose private
convention (VM in **EAX**, manager in **ECX**) is chosen by the whole-program pass
from *its* body, and an absolutely-bound callee gets no such convention.

## The region

`0x00409230..0x00409261`, 50 bytes,
`_asm_ReleaseFlaggedEntities_ScoreRuntimeState_00409230` in the manifest:

```
409230  56                push esi
409231  8b f1             mov  esi,ecx
409233  f6 86 8c370000 01 test byte ptr [esi+378Ch],1
40923a  74 1f             je   40925b
40923c  8b 0d 101c4900    mov  ecx,dword ptr [491C10h]      ; the animation manager
409242  8d 46 10          lea  eax,[esi+10h]               ; the embedded VM
409245  e8 76bfffff       call 004451C0h
40924a  8b 0d 101c4900    mov  ecx,dword ptr [491C10h]     ; reloaded: the callee clobbers ECX
409250  8d 86 bc030000    lea  eax,[esi+3BCh]              ; the next embedded VM
409256  e8 65bfffff       call 004451C0h
40925b  b8 01000000       mov  eax,1
409260  5e                pop  esi
409261  c3                ret
```

`this` arrives in ECX (public `__thiscall`), is kept in ESI because it must
survive both calls, and the flag lives in the byte at `+0x378C`. The caller is a
scheduler registration at `0x004089EA`:

```
4089ea  68 30924000   push 00409230h
4089ef  ...           call 00449ED0h   ; SchedulerCallback_Create
```

so the function's address escapes and its receiver stays the public convention -
which is why the cluster layout below declares `roots` (or the pass re-chooses
ESI/EDX, as the second measurement shows).

## The recovered source

```cpp
extern "C" void* data_00491c10;
extern "C" int asm_FUN_004451c0_004451c0(void* manager, void* vm);   // 0x004451C0

struct ScoreRuntimeState_00409230 {
    unsigned char unknown_0000[0x378C];
    unsigned char release_flag_378C;
    unsigned char unknown_378D[0x400];

    __declspec(noinline) int ReleaseFlaggedEntities();
};

int ScoreRuntimeState_00409230::ReleaseFlaggedEntities() {
    if (release_flag_378C & 1) {
        asm_FUN_004451c0_004451c0(data_00491c10, (char*)this + 0x10);
        asm_FUN_004451c0_004451c0(data_00491c10, (char*)this + 0x3BC);
    }
    return 1;
}
```

The two embedded VMs at `+0x10` and `+0x3BC` are one 0x3AC-byte stride apart, the
same stride the sibling's two arrays use. The dispatcher takes the manager first
and the VM second; the pass assigns **argument 1 to ECX and argument 2 to EAX**,
which is exactly retail's pair, and the caller's `push esi` / `mov esi,ecx` and
the ECX reload follow from the callee's clobbers. Nothing in the model is
tuned: the same caller body produced the 50-byte exact region (below) with a
callee in the link, and the 2-byte-off region with an opaque callee.

## Verification: exact with the callee's definition in the link

Scratch cluster (patched copy of `build_cluster` that only relaxes the duplicate
tolerance for the experiment; the maintained tooling is untouched), callee
defined in the same source, `roots` naming the region:

```cpp
extern "C" int opaque_helper_00443080(void* manager, void* vm);      // 0x00443080, bound relatively

#pragma code_seg(".text$03standin")
extern "C" __declspec(noinline) int asm_FUN_004451c0_004451c0(void* manager, void* vm) {
    return opaque_helper_00443080(manager, vm);                      // stand-in body, NOT the retail dispatcher
}
#pragma code_seg()
```

Layout gaps `0x00401000+0x8230`, then `0x00409262 + 0x3BF5E` so that the
`.text$03standin` contribution lands at `0x004451C0` (the map confirms
`_asm_FUN_004451c0_004451c0@8  004451c0 f  cluster.obj`). The selected region's
50 bytes:

```
56 8b f1 f6 86 8c 37 00 00 01 74 1f 8b 0d 10 1c 49 00 8d 46 10 e8 76 bf 03 00
8b 0d 10 1c 49 00 8d 86 bc 03 00 00 e8 65 bf 03 00 b8 01 00 00 00 5e c3
```

matches retail byte for byte: **`differing = 0`**, call targets included. (The
stand-in body is a placeholder; only the region under recovery is compared.)

Two control shapes show what the caller needs from the callee:

| callee body in the link | region body | receiver/convention |
| --- | --- | --- |
| `return opaque_helper(manager, vm);` (calls out, clobbers) | **50 bytes, 0 differing** | `push esi / mov esi,ecx`, ECX reloaded per call |
| leaf body, no call (`cached = manager; flags = 0; return 0;`) | 42 bytes | pass keeps the receiver in EDX, loads the manager once |
| declared only, bound `relative_code` (see below) | 48 bytes | declared `__thiscall`: `push manager / lea ecx,[...]` |
| the dispatcher's **own naked `__asm` body**, same symbol, caller declaring a two-argument `__cdecl` prototype | longer than 50 and structurally different (`push eax / push ecx / call`, `add esp,10h`) | pass keeps the declared `__cdecl` stack convention |

That last row is the important negative: co-compiling the dispatcher's *existing
assembly body* does not help. A `__declspec(naked)` definition is not eligible
for an ABI change, so the caller falls back to the declared convention; the body
has to be **compiled from C++** inside the link. The exact caller bytes also
need that C++ body to call out (the retail dispatcher's case bodies delegate to
ten helpers), which is what fixes `this` in ESI and forces the ECX reload.

## Why the call cannot be written against an opaque callee

`0x004451C0` reads its object from **EAX** (`mov edx,[eax+35Ch]` first) and a
second input from **ECX**. Every one of the 23 call sites of that address carries
the object in EAX; the manager comes from `ds:0x00491C10` at 19 of them and is
already live at the other four (`0x0041D863`, `0x0041EAE3`, `0x004263AE`,
`0x004489B0`). Its address is never taken anywhere in the image, so the retail
pass was free to invent that convention.

No MSVC 13.10 prototype produces an argument in EAX. Measured with the project
toolkit (`~/.local/share/th10-toolchains/msvc-13.10.6030`, `/O2 /Gz /MT /Gy /G6
/GF /GS /Zl`) over: `__cdecl`/`__stdcall` 1-3 args, `__fastcall` 1-3 args,
`long long` arguments, 4/8/16/32-byte struct arguments and 4/8/32-byte struct
*returns* on both free and member functions, member functions with struct
returns, and a vararg `__fastcall` - the pointer always lands in ECX, EDX or the
stack, never EAX. The results measured on the region itself:

**1. Plain path, calls in one inline `__asm` block** (the shape `0x00443B60`
uses for `fsincos`): 46 bytes against the declared 50 - the `push esi` /
`mov esi,ecx` prologue and the `pop esi` epilogue are absent and the flag test
reads `[ecx+378Ch]` (`f6 81 ...` against retail's `f6 86 ...`). The compiler has
no reason to keep `this` in ESI: the only calls in its view are opaque asm.

**2. Cluster with the callee declared and bound `relative_code`, region in
`roots`**: 50 bytes, **2 differing bytes** at `+0x13` and `+0x21` -
`lea edx,[esi+10h]` / `lea edx,[esi+3BCh]` where retail has `lea eax,...`.
Everything else, both call displacements included, is identical. Byte-exact but
*rejected*: the callee reads its VM from EAX, so EDX would hand it garbage.

```
0x00409230      50 bytes  ?ReleaseFlaggedEntities@ScoreRuntimeState_00409230@@QAEHXZ  DIFFERENT
  first difference at 0x00409243
  expected: 46 10 e8 76 bf 03 00 ...   0x00409242: 8d 46 10  lea eax,[esi+0x10]
  actual:   56 10 e8 76 bf 03 00 ...   0x00409242: 8d 56 10  lea edx,[esi+0x10]
```

**3. Same cluster without `roots`**: the pass moves the receiver to ESI itself
and emits 46 bytes that are retail `0x00409190` byte for byte except the same two
`lea edx` bytes (the call displacements differ only because the body sits at
`0x00409230` in this image). So the receiver register is reproducible both ways
and the argument register is the single blocker.

**4. Absolutely-bound callee ("shape witness")**: with the callee *defined* in
the link **and** its symbol bound `relative_code` at `0x004451C0`, LINK 7.10
tolerates the duplicate (`warning LNK4006 ... second definition ignored`, needs
`/FORCE:MULTIPLE`), the absolute binding keeps the call target at `0x004451C0`,
and the witness's contribution collapses to a **zero-length** section - the
mechanism works mechanically. But the pass then does **not** customize the
callee's ABI: the call site falls back to the declared `__thiscall` convention
(the manager pushed, the receiver loaded into ECX - `push edi; lea ecx,[esi+10h];
call` for one witness body, `push esi; lea ecx,[edx+10h]; call` for another) and
the region shrinks to 48 or 42 bytes depending on the witness body. So a
discarded definition cannot steer the convention; the callee has to *be* the
definition in the link. (It also means the device, if it were ever wanted, needs
a manifest field for a declared code alias: `build_cluster` passes
`/FORCE:MULTIPLE` only when a `constant_aliases`/`data_aliases` entry is
declared, and `_verify_duplicates` then requires every tolerated duplicate to be
a declared alias.)

## Prerequisite for landing

Recover `0x004451C0` as C++ inside the same `/LTCG` link, as a *selected*
function of the cluster (its maintained region's `source`/`symbol`/`kind`
records re-pointed the way `promote_clusters.py` does). This region's 50 bytes
then come out exact, as measured above. What that recovery has to cover is
larger than the one function: the dispatcher is
173 bytes of code plus 3 bytes of alignment padding plus a **10-entry jump table
at `0x00445270`**, and its ten case bodies call ten different helpers
(`0x00443080`, `0x004436C0`, `0x00443F80`, `0x00444580`, `0x00443FB0`,
`0x004445C0`, `0x00444760`, `0x00444CE0`, `0x00443290`, `0x00443910`) with
private register arrangements of their own (`push ecx / mov esi,eax / call` and
siblings). Recovering the dispatcher's bytes therefore drags in those helpers'
conventions: it is a dispatcher-plus-helpers cluster, not a one-region change.
Until it exists, `0x00409230` must stay `kind: asm`.

## Scratch layout and driver (proven configuration)

`layout/ltcg/release_flagged_entities_00409230.json`:

```json
{
  "schema_version": 1,
  "name": "release_flagged_entities_00409230",
  "source": "src/game/release_flagged_entities_score_runtime_state_00409230.cpp",
  "driver": "layout/ltcg/release_flagged_entities_00409230_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Scheduler callback compiled with native LTCG; the dispatcher body has to sit in the same /LTCG link at 0x004451C0.",
  "functions": [
    {
      "name": "ScoreRuntimeState_ReleaseFlaggedEntities",
      "symbol": "?ReleaseFlaggedEntities@ScoreRuntimeState_00409230@@QAEHXZ",
      "section": ".text$01release",
      "address": "0x00409230",
      "size": 50,
      "actual_abi": "this in ECX; VM in EAX and manager in ECX at both calls; plain RET"
    }
  ],
  "context": {
    "symbol": "?ReleaseFlaggedEntitiesCompilerContext@@YGHPAPAUScoreRuntimeState_00409230@@H@Z",
    "section": ".text$05context",
    "address": "0x00445300",
    "size": 40,
    "description": "Synthetic array-walking caller supplying the callback's receiver shape; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 33328 },
    { "section": ".text$02layout", "address": "0x00409262", "size": 245598 },
    { "section": ".text$04layout", "address": "0x004451C8", "size": 312 }
  ],
  "constants": [],
  "absolute_symbols": [
    { "symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data" }
  ],
  "roots": ["?ReleaseFlaggedEntities@ScoreRuntimeState_00409230@@QAEHXZ"]
}
```

The gap sizes and the context address are only correct once a callee
contribution sits at `0x004451C0` (`0x00409262 + 0x3BF5E = 0x004451C0`); in the
verification run the stand-in occupied `0x004451C0..0x004451C8` and the trailing
gap `0x004451C8..0x00445300`. With the real dispatcher the extents change to
`0x004451C0 + 216` and both trailing gaps must be recomputed. The callee's
section must sort after `.text$02layout` and before the context
(`.text$03…` in the run). Two caveats on that arithmetic: LINK aligns the
context section itself, so in the verification build the context landed at
`0x004452F0` against a declared `0x00445300` and `validate_native_output`
refused the layout (the selected region's bytes were read straight out of that
private image, which is all the measurement needed); the trailing gap size has
to be set so the emitted context address equals the declared one. Note also that
there is deliberately **no** absolute binding for the dispatcher: binding it
absolutely is what costs the convention (measurement 4).

`layout/ltcg/release_flagged_entities_00409230_context.cpp`:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/release_flagged_entities_score_runtime_state_00409230.cpp"

#pragma code_seg(".text$05context")
int __stdcall ReleaseFlaggedEntitiesCompilerContext(ScoreRuntimeState_00409230** states, int count) {
    int released = 0;
    while (count--) {
        released += (*states++)->ReleaseFlaggedEntities();
    }
    return released;
}
#pragma code_seg()
```

Probe form used throughout:

```
python3 matching2/tools/matching/probe.py \
  --source src/game/release_flagged_entities_score_runtime_state_00409230.cpp \
  --project /tmp/ReleaseFlaggedEntities/msvc --output /tmp/ReleaseFlaggedEntities/out --show 30
```

With the callee bound opaquely the probe reports the 2-byte difference at
`0x00409243` described above; with the callee's definition in the link (and
declared, which needs its region promoted) the same probe reports EXACT.

## Integration

- **No header edit is needed**: the record type is declared in the region's own
  source, as the landed cluster sources do.
- **The additional source file needed is the callee's**, not this region's:
  `0x004451C0` (and, for its own bytes, its ten case helpers). This region's
  source, the layout and the driver above are complete as they stand; the layout
  only has to be extended with the dispatcher's `functions` entry and its gap
  arithmetic recomputed.
- The region should stay `kind: asm` until then.

## Sibling `0x004091C0` - same blocker, one more

`0x004091C0..0x0040921E`, 95 bytes,
`_asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0`. Not modelled past
the shared blocker:

```
4091c0  f6 83 8c370000 01  test BYTE PTR [ebx+378Ch],1     ; receiver in EBX
4091c7  74 50               je   409219
4091c9  56 57               push esi / push edi
4091cb  8d b3 78070000      lea  esi,[ebx+778h]            ; 8 VMs
4091d1  bf 08000000         mov  edi,8
4091d6  eb 08               jmp  4091e0                   ; 7-byte nop pad (8d a4 24 00000000 90)
4091e0  8b 0d 101c4900      mov  ecx,ds:491C10h
4091e6  8b c6               mov  eax,esi
4091e8  e8 d3bfffff         call 004451C0h
4091ed  81 c6 ac030000      add  esi,3ACh
4091f3  4f                  dec  edi
4091f4  75 ea               jne  4091e0
4091f6  8d b3 d8240000      lea  esi,[ebx+24D8h]          ; 5 VMs
4091fc  bf 05000000         mov  edi,5
409201  ...  same four-instruction loop body
409217  5f 5e               pop edi / pop esi
409219  b8 01000000         mov  eax,1
40921e  c3                  ret
```

1. Its four calls are the same `(ECX = manager, EAX = vm)` convention with the
   same unrecovered callee, so they carry the same per-call-site register delta.
2. Its receiver is **EBX**, which is neither the declared `__thiscall`
   convention nor a free choice: its only caller, `0x00409270`
   (`_asm_RunArrayReleaseCallback_ScoreRuntimeState_00409270`, itself a scheduler
   callback, registered at `0x00408A11`), exists to supply it:

```
409270  53          push ebx
409271  8b d9       mov  ebx,ecx
409273  e8 48ffffff call 004091C0h
409278  5b          pop ebx
409279  c3          ret
```

   So `0x00409270 -> 0x004091C0` is itself an `/LTCG` convention pair (the caller
   supplies the receiver register), the mirror image of the ESI-entry clone
   described below. A two-function cluster could plausibly reproduce it, but only
   with the callee's body in the link - and rooting either function forces its
   public convention, which is the wrong receiver for the callee. The sibling is
   therefore gated on the same prerequisite, one convention deeper.

## Adjacent evidence worth keeping

`0x00409190` (46 bytes, `src/unidentified/unassigned_00409190.cpp`) is a
receiver clone of this region's body: identical to `0x00409230` minus the ESI
prologue/epilogue, taking the state in ESI. **Nothing in the image references
it** - no `call`/`jmp` rel32, no rel8, and no little-endian `0x00409190` dword
anywhere in the file - so it is dead code in retail. Its bytes are reproduced
exactly by the `roots`-less cluster run except for the same two `lea edx` bytes,
which confirms both that the pass generated the clone (receiver-register
specialisation) and that receiver variants are reachable from a synthetic
context while the argument register is not.

The sibling's family stride is confirmed twice over: `0x10 -> 0x3BC` here and
`0x778 -> 0x24D8` there are both exact multiples of `0x3AC`, the same block size
`0x004451C0`'s callers in `0x00402B30` and `0x00415820` walk.
