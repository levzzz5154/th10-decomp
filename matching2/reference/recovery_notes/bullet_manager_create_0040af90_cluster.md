# 0x0040AF90 `BulletManager_Create` — model complete, landing blocked by the LoadScripts receiver

2026-09-19. Region `0x0040AF90` (86 bytes, `src/game/bullet_manager_create_0040af90.cpp`)
was modelled as ordinary C++ and driven through the native-LTCG cluster path in a
throwaway copy. **The model is byte-identical to retail in every byte except the
register that holds the manager**, and it becomes exactly retail's 86 bytes as soon
as `0x40AE70` participates in the same `/LTCG` link. `0x40AE70` is still assembly,
and its own receiver register is a compiler-chosen convention, so this region is
**coupled to the LoadScripts recovery** and did not land this wave. Nothing in the
maintained tree was changed.

## What the region is

```
0040af90  53              push  ebx
0040af91  6a 18           push  18h
0040af93  e8 fb740400     call  00452493          ; operator new(0x18)
0040af98  83 c4 04        add   esp,4
0040af9b  85 c0           test  eax,eax
0040af9d  74 21           je    0040afc0
0040af9f  33 c9           xor   ecx,ecx
0040afa1  8b d0           mov   edx,eax
0040afa3  89 0a           mov   [edx],ecx        ; memset(state, 0, 0x18) inlined
0040afa5  89 4a 04        mov   [edx+4],ecx
0040afa8  89 4a 08        mov   [edx+8],ecx
0040afab  89 4a 0c        mov   [edx+0Ch],ecx
0040afae  89 4a 10        mov   [edx+10h],ecx
0040afb1  89 4a 14        mov   [edx+14h],ecx
0040afb4  83 08 02        or    [eax],2          ; state->flags |= 2
0040afb7  a3 fc764700     mov   ds:004776fc,eax ; the manager global
0040afbc  8b d8           mov   ebx,eax
0040afbe  eb 02           jmp   0040afc2
0040afc0  33 db           xor   ebx,ebx
0040afc2  e8 a9feffff     call  0040ae70          ; LoadScripts, receiver in EBX
0040afc7  85 c0           test  eax,eax
0040afc9  74 17           je    0040afe2
0040afcb  85 db           test  ebx,ebx
0040afcd  74 0f           je    0040afde
0040afcf  53              push  ebx
0040afd0  e8 2bffffff     call  0040af00          ; Release(state), RET 4
0040afd5  53              push  ebx
0040afd6  e8 c6740400     call  004524a1          ; free(state)
0040afdb  83 c4 04        add   esp,4
0040afde  33 c0           xor   eax,eax
0040afe0  5b              pop   ebx
0040afe1  c3              ret
0040afe2  8b c3           mov   eax,ebx
0040afe4  5b              pop   ebx
0040afe5  c3              ret
```

The manager lives in **EBX** across the LoadScripts call and the two teardown
calls, which is also the register LoadScripts itself reads (`mov [ebx+10h],eax`,
`mov [ebx+8],esi`, `mov [ebx+0Ch],esi`) and the one pushed to Release and `free`.
Only `0x417B8B` calls this region (`call 0040af90; test eax,eax; je ...`), i.e. no
argument is set up and the result is returned in EAX.

## The model

Verified source (this is the text that produced the byte-exact body in the run
below; the callee spelling must match whatever the recovered `0x40AE70` source
defines, and the layout binds that symbol):

```cpp
// 0x0040AF90 (86 bytes) - BulletManager_Create
//
// Allocate the 0x18-byte bullet-manager state, clear it, raise its live flag,
// publish it through the manager global and load the bullet scripts.  On a
// script-load failure the freshly built manager is released and freed, and the
// factory reports NULL, so callers can tell "not created" from "created".
//
// Retail keeps the manager in EBX across the script-load and release calls -
// that is the register LoadScripts receives it in and the register the teardown
// calls are reached with.

struct BulletManagerState_0040af90 {
    unsigned flags;             // +0x00
    unsigned reserved_004;      // +0x04
    void *primary_callback;     // +0x08
    void *secondary_callback;   // +0x0C
    void *bullet_resource;      // +0x10
    unsigned reserved_014;      // +0x14
};

extern "C" void *__cdecl memset(void *dest, int value, unsigned size);
extern "C" int __stdcall BulletManager_LoadScripts_0040ae70(
        BulletManagerState_0040af90 *state);
extern "C" void __stdcall asm_BulletManager_Release_0040af00(
        BulletManagerState_0040af90 *state);
extern "C" void __cdecl entry_free_004524a1(void *memory);
extern "C" BulletManagerState_0040af90 *data_004776fc;

__declspec(noinline) BulletManagerState_0040af90 *BulletManager_Create_0040af90();
#pragma code_seg(".text$05accessor")
BulletManagerState_0040af90 *BulletManager_Create_0040af90() {
    BulletManagerState_0040af90 *fresh = new BulletManagerState_0040af90;
    BulletManagerState_0040af90 *state;
    if (fresh) {
        memset(fresh, 0, sizeof(BulletManagerState_0040af90));
        fresh->flags |= 2u;
        data_004776fc = fresh;
        state = fresh;
    } else {
        state = 0;
    }
    if (BulletManager_LoadScripts_0040ae70(state)) {
        if (state) {
            asm_BulletManager_Release_0040af00(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}
#pragma code_seg()
```

Two source details are load-bearing and were arrived at by measurement:

* the clear must be `memset(state, 0, sizeof *state)`. Retail's cursor copy
  (`mov edx,eax` + six `mov [edx+n],ecx`) is MSVC's inline memset expansion, whose
  return value stays in EAX; that is what makes the following `or [eax],2` and the
  short `mov ds:...,eax` (`a3`) encodings appear. Six explicit field stores compile
  to 85 bytes and a `mov [esi],2` instead of an `or`.
* the conditional must be written as an if/else that assigns the manager variable
  in both arms (`if (fresh) { ...; state = fresh; } else { state = 0; }`).
  That is what produces retail's `mov ebx,eax / jmp / xor ebx,ebx` join; with a
  plain `if (state) { ... }` MSVC keeps the value in a register from the
  allocation onwards and the body is 83 bytes.

## Evidence

### 1. Byte-exact body when `0x40AE70` participates (0 differing bytes)

Cluster: `src/game/bullet_manager_create_0040af90.cpp` (the model above) plus a
stand-in callee region at `0x40AE70`, driver = synthetic array walker, bound
externals `_asm_BulletManager_Release_0040af00@4`, `_entry_free_004524a1`,
`??2@YAPAXI@Z`, `_memset`, `_data_004776fc`.

```
LANDED fn=86 callee=95@0x40ae70 ctx=47@0x40aff0 differing=0
```

The emitted `0x0040AF90` bytes are exactly the listing at the top of this note.
The stand-in callee's emitted body proves the agreement:

```
0040ae70  push 7 ; call 00447280 ; ... ; mov [ebx+10h],eax
0040ae92  push esi ; push edi ; ... ; mov [esi+20h],ebx ... mov [edi+20h],ebx
```

i.e. the pass gave that callee its receiver in EBX (its own two locals took ESI and
EDI), and the caller's manager followed into EBX. Stand-in source used (its bytes
are irrelevant; only the shape that claims ESI+EDI for two locals is):

```cpp
struct BulletManagerState_0040af90 {
    unsigned flags; unsigned reserved_004; void *primary_callback;
    void *secondary_callback; void *bullet_resource; unsigned reserved_014;
};
extern "C" int __cdecl resource_lookup(int id);
extern "C" int __cdecl log_failure(const char *text);
extern "C" void *__cdecl callback_create(void *fn);
extern "C" void __cdecl callback_register(void *cb, int id, void *device);

__declspec(noinline) int __stdcall SyntheticLoad(BulletManagerState_0040af90 *state);
#pragma code_seg(".text$02callee")
int __stdcall SyntheticLoad(BulletManagerState_0040af90 *state) {
    int resource = resource_lookup(7);
    state->bullet_resource = (void *)(long)resource;
    if (resource == 0) { log_failure("bullet.anm"); return -1; }
    void *primary = callback_create((void *)0x40B050);
    void *secondary = callback_create((void *)0x40B060);
    *((void **)primary + 8) = state;
    *((void **)secondary + 8) = state;
    callback_register(primary, 0x17, secondary);
    state->primary_callback = primary;
    state->secondary_callback = secondary;
    if (primary == secondary) return -1;
    return 0;
}
#pragma code_seg()
```

Driver (synthetic walker; also the `/ENTRY`):

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/bullet_manager_create_0040af90.cpp"
#pragma code_seg(".text$05context")
int __stdcall BulletManagerCreateCompilerContext(
        BulletManagerState_0040af90 **slots, int count) {
    int live = 0;
    for (int index = 0; index < count; ++index) {
        BulletManagerState_0040af90 *state = BulletManager_Create_0040af90();
        slots[index] = state;
        if (state) ++live;
    }
    return live;
}
#pragma code_seg()
```

Layout schema-1 body that was built (sections in `.text$NN` order; `$00layout` covers
`0x401000..0x40AE70`, `$02callee` is the stand-in, `$04layout` fills
`0x40AE70+size..0x40AF90`, `$05accessor` is the region, `$05context` the walker):

```json
{
  "schema_version": 1,
  "name": "bullet_manager_create_0040af90",
  "source": "src/game/bullet_manager_create_0040af90.cpp",
  "driver": "layout/ltcg/bullet_manager_create_0040af90_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "BulletManager_Create_0040af90 compiled with the native LTCG cluster that carries LoadScripts' EBX receiver.",
  "functions": [
    {"name": "BulletManager_Create_0040af90",
     "symbol": "?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ",
     "section": ".text$05accessor", "address": "0x0040AF90", "size": 86,
     "actual_abi": "no arguments; manager in EBX across the script-load and release calls; result in EAX"},
    {"name": "BulletManager_LoadScripts_0040ae70",
     "symbol": "?SyntheticLoad@@YGHPAUBulletManagerState_0040af90@@@Z",
     "source": "src/game/scratch_callee.cpp", "section": ".text$02callee",
     "address": "0x0040AE70", "size": 95,
     "actual_abi": "manager in EBX; plain RET"}
  ],
  "additional_sources": ["src/game/scratch_callee.cpp"],
  "context": {
    "symbol": "?BulletManagerCreateCompilerContext@@YGHPAPAUBulletManagerState_0040af90@@H@Z",
    "section": ".text$05context", "address": "0x0040AFF0", "size": 47,
    "description": "Synthetic array-walking caller; not recovered game code."},
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 40560},
    {"section": ".text$04layout", "address": "0x0040AECF", "size": 193}],
  "constants": [],
  "roots": ["?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ"],
  "absolute_symbols": [
    {"symbol": "_asm_BulletManager_Release_0040af00@4", "address": "0x0040AF00", "kind": "relative_code"},
    {"symbol": "_entry_free_004524a1", "address": "0x004524A1", "kind": "relative_code"},
    {"symbol": "??2@YAPAXI@Z", "address": "0x00452493", "kind": "relative_code"},
    {"symbol": "_memset", "address": "0x0045BED0", "kind": "relative_code"},
    {"symbol": "_data_004776fc", "address": "0x004776FC", "kind": "data"}
  ]
}
```

(`roots` keeps the region alive: nothing in the synthetic context calls it here,
because the region is the *caller* of the context-shaped callee. `size`/`address`
of the stand-in and the context are the emitted values, as the loader requires.)

### 2. What the same model emits when `0x40AE70` is opaque (the delta)

Registered standalone, with the callee bound to `0x40AE70` as an opaque
`__stdcall` function — i.e. the configuration that can be registered today:

```
python3 matching2/tools/matching/probe.py \
  --source src/game/bullet_manager_create_0040af90.cpp \
  --project /tmp/<copy>/msvc --show 24
0x0040af90      86 bytes  ?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ  DIFFERENT
  first difference at 0x0040af90
  expected: 53 6a 18 e8 fb 74 04 00 83 c4 04 85 c0 74 21 33 c9 8b d0 89 0a 89 4a 04   0x0040af90: 53  push   ebx
  actual:   56 6a 18 e8 fb 74 04 00 83 c4 04 85 c0 74 21 33 c9 8b d0 89 0a 89 4a 04   0x0040af90: 56  push   esi
```

Emitted extent **86 against the declared 86** (the whole instruction *sequence* is
retail's, byte for byte, including the `a3` short store and the join). The nine
differing bytes are the entire delta and every one of them is the ESI/EBX encoding
of the same instruction:

```
0x40af90  56 -> 53   push  esi                         / push  ebx
0x40afbd  f0 -> d8   mov   esi,eax                     / mov   ebx,eax
0x40afc1  f6 -> db   xor   esi,esi                     / xor   ebx,ebx
0x40afcc  f6 -> db   test  esi,esi                     / test  ebx,ebx
0x40afcf  56 -> 53   push  esi                         / push  ebx
0x40afd5  56 -> 53   push  esi                         / push  ebx
0x40afe0  5e -> 5b   pop   esi                         / pop   ebx
0x40afe3  c6 -> c3   mov   eax,esi                     / mov   eax,ebx
0x40afe4  5e -> 5b   pop   esi                         / pop   ebx
```

The opaque-callee form is therefore not only inexact, it is also **wrong at
runtime**: the current `0x40AE70` assembly reads EBX, and this shape leaves the
manager in ESI (the register argument would be whatever the caller had in EBX). It
must not be registered.

For completeness: the shape whose declaration follows an ordinary calling
convention (`__stdcall f(state)`, so the manager really is passed as the callee's
argument and no implicit register is assumed) emits **87 bytes** with the manager
pushed (`56 e8 a8feffff` where retail has `e8 a9feffff`) — one byte long, 37
differing bytes. That is the honest standalone model, and it is the one to keep in
the tree if the region is ever registered before `0x40AE70` is recovered; against
today's assembly stub, which reads EBX, it would pass the manager in the wrong
place. Both expressible shapes were measured; neither is exact.

## Why the register cannot be forced from the model

The manager's register is not a model choice: it is the native-LTCG pass assigning
a caller/callee register agreement. Measured in the copy:

* A single long-lived local with an opaque callee always lands in **ESI** (also for
  a `__stdcall` parameter that gets promoted), including through a `/GL` cluster
  and with three different synthetic callers. Micro-functions that keep one value
  live across a call (`new` + call + return, parameter-valued, loop-carried) all
  chose ESI; the only variants that moved off ESI were the ones with a second
  live value.
* As soon as a **participating** function at the callee's address needs two live
  locals, the pass gives *its* receiver EBX and the caller's manager follows into
  EBX. That is exactly retail's shape: LoadScripts pushes ESI and EDI for its two
  callback/priority locals (`mov edi,17h`, `mov edi,20h` reach
  `Scheduler_RegisterPrimary/Secondary`), leaving EBX for its receiver.
* The single synthetic function a schema-1 layout may add — the context, which is
  the `/ENTRY` — cannot play that role: LTCG preserves the declared ABI of the
  entry. Driving `0x40AE70` as the context symbol with a LoadScripts-shaped body
  emits `push esi; call 0040ae70; add esp,4` in Create (**90 bytes**, the parameter
  coming from the stack inside the context), and every LoadScripts-shaped variant
  tried (`two_live_locals`, `three_live_locals`) behaved the same. Schema 2 has the
  same restriction (every `/GL` input must own a selected region), and a naked
  assembly stub cannot be pulled in either — the cluster loads only declared
  sources/headers and rejects undeclared includes.

So the only configuration that reproduces retail is one where `0x40AE70` itself is
a selected function in the same `/LTCG` link.

## Integration

* Headers: **no header edit needed.**
* Manifest: the region `0x0040AF90`'s record must be replaced by
  `semantic_BulletManager_Create_0040af90_0040af90` / `?BulletManager_Create_0040af90@@YGPAUBulletManagerState_0040af90@@XZ`
  and `layout/ltcg/bullet_manager_create_0040af90.json` added to `ltcg_clusters`
  (both done by `register_cluster.py --apply` once the layout is registered).
* Additional source files: **required — `0x40AE70` (LoadScripts) must be recovered
  and selected in the same cluster.** It cannot be declared through a prototype:
  its receiver register is EBX, which no MSVC calling convention can express.
  `0x40AF00` (Release, `__stdcall`, RET 4) and the allocator/free/global bindings
  are fine as opaque externals.
* LoadScripts' own callees `0x449AE0`/`0x449B70` reach it with the task in ESI, the
  priority in EDI and the scheduler on the stack. That convention environment
  already exists in the landed `layout/ltcg/scheduler_tasks.json`
  (`Scheduler_RegisterPrimary/Secondary`, 131 bytes each, `actual_abi` "task in
  ESI, priority in EDI, scheduler on stack"). The natural home for this region is
  therefore an **extended** `scheduler_tasks` cluster: add the recovered
  LoadScripts source and this source as its additional sources/functions, so the
  pass can choose the same registers it chose in retail. `scheduler_tasks.cpp`
  stays in exactly one cluster, and this region needs no separate layout.
  Two risks there: the four scheduler functions in that layout must stay
  byte-exact under the extended link, and LoadScripts itself must come out at 134
  bytes.

Partial progress for whoever takes `0x40AE70`: everything above is reproducible from
the copy at `/tmp/BulletManagerCreate` (`exp7.py` rebuilds the exact configuration,
`exp5.py`/`exp6.py` the convention sweeps).
