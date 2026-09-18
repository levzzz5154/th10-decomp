# 0x00409230 ReleaseFlaggedEntities - blocked on the 0x004451C0 dispatcher's private convention

2026-09-19. Worker `ReleaseFlaggedEntities`. **No promotion**: the region is not
EXACT and nothing in the maintained tree changed except this note. All work was
done in a scratch copy (`cp -a matching2/msvc /tmp/ReleaseFlaggedEntities/msvc`);
the copy's manifest, sources, layout and driver never left `/tmp`.

The short version: the enclosing body is ordinary C++ and the cluster path
reproduces **49 of the 50 bytes**, including both call targets; the last byte
pair is the *argument register* of the two calls, and that register is chosen by
the linker's whole-program pass for the **callee**, which is still assembly.
Landing this region therefore needs the callee `0x004451C0` (216 bytes of
dispatch) recovered in the same `/LTCG` link, not a different model of this
region.

## The region

`0x00409230..0x00409261`, 50 bytes, `_asm_ReleaseFlaggedEntities_ScoreRuntimeState_00409230`
in the manifest. Retail:

```
409230  56                push esi
409231  8b f1             mov  esi,ecx
409233  f6 86 8c370000 01 test byte ptr [esi+378Ch],1
40923a  74 1f             je   40925b
40923c  8b 0d 101c4900    mov  ecx,dword ptr [491C10h]      ; the animation manager
409242  8d 46 10          lea  eax,[esi+10h]               ; the embedded VM
409245  e8 76bfffff       call 004451C0h
40924a  8b 0d 101c4900    mov  ecx,dword ptr [491C10h]
409250  8d 86 bc030000    lea  eax,[esi+3BCh]              ; the next embedded VM
409256  e8 65bfffff       call 004451C0h
40925b  b8 01000000       mov  eax,1
409260  5e                pop  esi
409261  c3                ret
```

Recovered shape: `int ScoreRuntimeState::ReleaseFlaggedEntities()` - a
`__thiscall` member with `this` in ECX that returns 1 unconditionally and, when
bit 0 of the byte at `+0x378C` is set, releases two embedded animation VMs
(`+0x10` and `+0x3BC`, one 0x3AC-byte stride apart) through the shared
dispatcher at `0x004451C0`. The output byte at `+0x378C`, `+0x491C10` and the
0x3AC stride all agree with the sibling family below.

The caller is a scheduler registration, at `0x004089EA`:

```
4089ea  68 30924000       push 00409230h
4089ef  ...               call 00449ED0h   ; SchedulerCallback_Create
```

so the function's **address escapes** the `/LTCG` scope. That is why its own
receiver is the public `ECX` convention, and why the cluster layout below needs
an explicit `roots` entry to stop the pass from re-choosing it (a `roots`-less
build does re-choose it - see the third measurement).

## Why the two calls cannot be written as C++

`0x004451C0` reads its object from **EAX** (`mov edx,[eax+35Ch]` are its first
instructions) and a second input from **ECX** (it is pushed through to its case
helpers). Every one of the 23 call sites of that address in the image carries the
object in EAX - the manager comes from `ds:0x00491C10` at 19 of them
(e.g. `0x00402B3A`, `0x00406747`, `0x00415820`, `0x00415AB0`) and is already
live in ECX/EDI at the other four (`0x0041D863`, `0x0041EAE3`, `0x004263AE`,
`0x004489B0`).
No MSVC prototype produces an argument in EAX; measured with the project
toolkit (`~/.local/share/th10-toolchains/msvc-13.10.6030`, `/O2 /Gz /MT /Gy /G6
/GF /GS /Zl`) over these shapes, all of which put the pointer elsewhere:

| declared callee | where the pointer lands |
| --- | --- |
| `__cdecl f(void*)` / `__stdcall f(void*)` | stack |
| `__fastcall f(void*)` | ECX |
| `__fastcall f(void*, void*)` | ECX, EDX |
| `__fastcall f(void*, void*, void*)` | ECX, EDX, stack |
| `__fastcall f(long long)`, `f(long long, void*)` | stack (MSVC 13.10 does not use a register pair) |
| `Big __fastcall f(void*, void*)` (4/8/32-byte return) | return pointer in EDX/stack, arg in ECX/stack |
| `__fastcall f(void*, P4)` / `(void*, P8)` by value | EDX (plus a stack slot for P8) |
| `__thiscall f(void*)`, `__thiscall Big f(void*)` (member, any return) | ECX receiver, argument on the stack |
| `__fastcall f(void*, ...)` | ECX plus a stack vararg tail |

EAX is only ever the *return* register in these conventions. The one mechanism
that reaches an EAX-carried parameter is the private whole-program convention,
which per `matching2/reference/whole_program_ltcg.md` requires **both sides of
the private call to be visible to the same `/LTCG` invocation** and the callee
to stay eligible for an ABI change - i.e. the callee's body has to be compiled
in the same `cluster_attempt` unit. That is what landed `0x00405ED0` today (its
source was merged into the registered cluster of its visible callee
`0x004493E0`), and it is not available here: `0x004451C0` is an
unrecovered `kind: asm` region owned by `src/render/anm_vm_draw_dispatch.cpp`.

That callee is not a small dependency: 216 bytes ending in a 10-entry jump table
at `0x00445270`, each case calling a different helper (`0x00443080`,
`0x004436C0`, `0x00443F80`, `0x00444580`, `0x00443FB0`, `0x004445C0`,
`0x00444760`, `0x00444CE0`, `0x00443290`, `0x00443910`) with its own private
register/stack arrangement (`push ecx / mov esi,eax / call` and friends), and
its own address is never taken anywhere in the image (no absolute reference to
`0x004451C0` exists), so the pass was free to invent its convention in retail.
Reproducing it is a dispatcher-plus-helpers cluster, not a one-region change.

## Measured attempts

Probe form:
`python3 matching2/tools/matching/probe.py --source src/game/release_flagged_entities_score_runtime_state_00409230.cpp --project /tmp/ReleaseFlaggedEntities/msvc --output /tmp/ReleaseFlaggedEntities/out --show 30`

**1. Plain path, C++ body with the two call sequences in one inline `__asm`
block** (the shape `0x00443B60` uses for its `fsincos` sequences): compiles to
**46 bytes against the declared 50**.

```
f6 81 8c 37 00 00 01   test BYTE PTR [ecx+378Ch],1     ; retail f6 86 ... [esi+...]
74 1f                  je
8b 0d <491C10>         mov  ecx,ds:491C10h
8d 46 10               lea  eax,[esi+10h]              ; the asm block is exact
e8 <4451C0>            call
8b 0d <491C10>         mov  ecx,ds:491C10h
8d 86 bc 03 00 00      lea  eax,[esi+3BCh]
e8 <4451C0>            call
b8 01 00 00 00         mov  eax,1
c3                     ret
```

Delta: `push esi` / `mov esi,ecx` (3 bytes) and `pop esi` (1 byte) are absent and
the flag test reads through ECX. The compiler has no reason to keep `this` in
ESI: the only calls in its view are opaque `__asm` blocks, so nothing is live
across them. Putting `push esi / mov esi,ecx` *inside* the asm block fixes the
bytes but then the whole body is assembly, which is the region's current state,
not a recovery.

**2. Native-LTCG cluster with the callee declared `extern "C" __fastcall`
(`ECX`, `EDX`) and bound as `@asm_FUN_004451c0_004451c0@8 -> 0x004451C0`
(`relative_code`)**, with the region's own symbol in `roots` so its public ECX
receiver is retained. `this` is then live across the first call, ESI is used, and
the region compiles to **exactly 50 bytes with 2 differing bytes**:

```
0x00409230      50 bytes  ?ReleaseFlaggedEntities@ScoreRuntimeState_00409230@@QAEHXZ  DIFFERENT
  first difference at 0x00409243
  expected: 46 10 e8 76 bf 03 00 ... 8d 86 bc 03 00 00 ...   0x00409242: 8d 46 10  lea eax,[esi+0x10]
  actual:   56 10 e8 76 bf 03 00 ... 8d 96 bc 03 00 00 ...   0x00409242: 8d 56 10  lea edx,[esi+0x10]
```

The two differences are byte `+0x13` (`46` vs `56`) and byte `+0x21` (`86` vs
`96`): `lea edx,[esi+0x10]` and `lea edx,[esi+0x3BC]` where retail has
`lea eax,...`. Every other byte, including both `call` displacements and their
target `0x004451C0`, is identical. This is a **2-byte, semantically wrong**
model: the callee reads its VM pointer from EAX, so the EDX model would hand it
garbage. It is recorded as a failure, not a recovery.

**3. The same cluster with `roots` removed**: the pass takes the liberty the
escaping address normally denies it, moves the receiver to ESI, and emits 46
bytes that are retail `0x00409190` byte-for-byte except the same two `lea edx`
modrm bytes (the two `call` displacements differ only because the body sits at
`0x00409230` instead of `0x00409190` in this scratch image):

```
f6 86 8c370000 01   test BYTE PTR [esi+378Ch],1     ; ESI receiver, no prologue - retail 0x00409190
...
actual   ... 8d 56 10 ... 8d 96 bc 03 00 00 ...
expected ... 8d 46 10 ... 8d 86 bc 03 00 00 ...
```

So the entry *register* is reproducible (both the callback's ECX entry and the
ESI-entry clone), and the argument register is not - the same single blocker.

Shapes tried, in order: `extern "C" __cdecl` (symbol-compatible, stack
arguments, 8 bytes larger); inline `__asm` for the calls with the surrounding
body in C++ (46 bytes, above); member-function model in the cluster without
`roots` (ESI receiver, 46 bytes); with `roots` (ECX receiver, 50 bytes, 2 bytes
off). The cluster layout and driver used are below; they are scratch artefacts
and must not be registered as they stand, because they bind a `__fastcall`
prototype for a callee that is not one.

### Scratch layout `layout/ltcg/release_flagged_entities_00409230.json`

```json
{
  "schema_version": 1,
  "name": "release_flagged_entities_00409230",
  "source": "src/game/release_flagged_entities_score_runtime_state_00409230.cpp",
  "driver": "layout/ltcg/release_flagged_entities_00409230_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Scheduler callback compiled with native LTCG; measures the call shape reached for the dispatcher 0x004451C0 whose VM argument is carried in EAX.",
  "functions": [
    {
      "name": "ScoreRuntimeState_ReleaseFlaggedEntities",
      "symbol": "?ReleaseFlaggedEntities@ScoreRuntimeState_00409230@@QAEHXZ",
      "section": ".text$01release",
      "address": "0x00409230",
      "size": 50,
      "actual_abi": "this in ECX; releases the VMs at +0x10 and +0x3BC; plain RET"
    }
  ],
  "context": {
    "symbol": "?ReleaseFlaggedEntitiesCompilerContext@@YGHPAPAUScoreRuntimeState_00409230@@H@Z",
    "section": ".text$03context",
    "address": "0x00409270",
    "size": 40,
    "description": "Synthetic array-walking caller that supplies the callback's receiver shape; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 33328 },
    { "section": ".text$02layout", "address": "0x00409262", "size": 14 }
  ],
  "constants": [],
  "absolute_symbols": [
    { "symbol": "@asm_FUN_004451c0_004451c0@8", "address": "0x004451C0", "kind": "relative_code" },
    { "symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data" }
  ],
  "roots": ["?ReleaseFlaggedEntities@ScoreRuntimeState_00409230@@QAEHXZ"]
}
```

(The `roots` entry is what keeps the ECX receiver; without it the pass emits the
46-byte ESI-receiver body. `size` 40 for the context is the measured emitted
size, and 14 for the trailing gap is what aligns the context at `0x00409270`.)

### Scratch driver `layout/ltcg/release_flagged_entities_00409230_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/release_flagged_entities_score_runtime_state_00409230.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReleaseFlaggedEntitiesCompilerContext(ScoreRuntimeState_00409230** states, int count) {
    int released = 0;
    while (count--) {
        released += (*states++)->ReleaseFlaggedEntities();
    }
    return released;
}
#pragma code_seg()
```

and the scratch model the cluster compiled:

```cpp
extern "C" void* data_00491c10;
extern "C" void __fastcall asm_FUN_004451c0_004451c0(void* manager, void* vm);

struct ScoreRuntimeState_00409230 {
    unsigned char unknown_0000[0x378C];
    unsigned char release_flag_378C;
    unsigned char unknown_378D[0x400];
    __declspec(noinline) int ReleaseFlaggedEntities();
};

#pragma code_seg(".text$01release")
int ScoreRuntimeState_00409230::ReleaseFlaggedEntities() {
    if (release_flag_378C & 1) {
        asm_FUN_004451c0_004451c0(data_00491c10, (char*)this + 0x10);
        asm_FUN_004451c0_004451c0(data_00491c10, (char*)this + 0x3BC);
    }
    return 1;
}
#pragma code_seg()
```

## Integration

- **No header edit is needed.** The model is self-contained (the record type is
  declared in the region's own source, as the landed cluster sources do).
- **No additional source file is needed for this region**; the missing piece is
  the callee's. Landing it means recovering `0x004451C0` and its ten case
  helpers as one cluster and adding *that* source to the layout's
  `additional_sources` (or one merged layout), with this region's function
  listed and identical gap arithmetic. `register_cluster.py --apply` would
  refuse the pair as configured today only because `0x004451C0`'s maintained
  region is `kind: asm` and owned by a different source; that ownership change
  is the campaign's decision, not this region's.
- Until then the region should stay `kind: asm`.

## Sibling `0x004091C0` - same blocker, one more

`0x004091C0..0x0040921E`, 95 bytes, `_asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0`.
Not EXACT either, and not modelled further once the shared blocker was measured:

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

Two obstacles, not one:

1. The four calls are all the same `(ECX = [491C10h], EAX = vm)` convention, so
   they carry the same 2-byte-per-call-site delta, and their callee is the same
   unrecovered `0x004451C0`.
2. Its receiver is **EBX**, which is neither the declared `__thiscall`
   convention nor a free choice: its only caller, `0x00409270`
   (`_asm_RunArrayReleaseCallback_ScoreRuntimeState_00409270`, itself a
   scheduler callback, registered at `0x00408A11`), exists purely to supply it:

```
409270  53        push ebx
409271  8b d9     mov  ebx,ecx
409273  e8 48ffffff  call 004091C0h
409278  5b        pop  ebx
409279  c3        ret
```

So the pair `0x00409270 -> 0x004091C0` is itself an `/LTCG` convention pair
(caller supplies EBX, callee is re-choosing its receiver register), the same
mechanism as `0x00409230`'s ESI clone. A two-function cluster could plausibly
reproduce it, but only with the callee's body co-compiled, and the pass would
have to re-choose EBX - rooting either function forces its public convention
instead, which is the wrong receiver for the callee. Both regions are therefore
gated on recovering `0x004451C0` first; neither can be modelled in isolation.

## Adjacent evidence worth keeping

`0x00409190` (46 bytes, `src/unidentified/unassigned_00409190.cpp`) is a
receiver-clone of the same body: identical to `0x00409230` minus the ESI
prologue/epilogue, taking the state in ESI. **Nothing in the image references
it** - no `call`/`jmp` rel32, no rel8, and no little-endian `0x00409190` dword
anywhere in the file - so it is dead in retail, and its bytes are reproduced
exactly by the `roots`-less cluster measurement above except for the two
`lea edx` bytes. That confirms the clone was produced by the same whole-program
pass that chose the receiver registers, and that ESI/EBX receiver variants are
reachable from a synthetic context (ECX is not, once `roots` is declared).
