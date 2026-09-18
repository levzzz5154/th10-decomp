# Region `0x00417770` (66 bytes) — wave 6

Date: 2026-09-19. Status: **EXACT**, landed as the single-function cluster
`layout/ltcg/recovery_linked_cleanup_00417770.json`.

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/recovery_linked_cleanup_00417770.cpp \
      --project matching2/msvc --output /tmp/LinkedCleanup/out --show 30
0x00417770      66 bytes  ?ReleaseChain@ScoreChain_00417770@@QAEXXZ  EXACT
EXACT
```

Registration went through exactly one `register_cluster.py --layout
layout/ltcg/recovery_linked_cleanup_00417770.json --apply`, so the region record
and `ltcg_clusters` (252 entries) changed only through that path;
`translation_units` was recomputed by that same call, is checked sorted, unique
and 2394 entries, and this region's source was already in it. No other region
names any of the three files added here, so this layout is the only claimant.

## What the region is

Retail walks one chain of intrusive list nodes and releases each of them:

```
push esi
mov  esi,[eax+0x18]        ; node = owner->head
test esi,esi / je end
push edi
lea  esp,[esp+0x0]         ; loop-body alignment
loop:
mov  edx,[esi]             ; vtable
mov  edi,[esi+0x8]         ; next = node->next
mov  ecx,esi
call [edx+0x10]            ; node->Release()          (5th virtual slot)
mov  eax,[esi+0x4]         ; prev  = node->prev
mov  ecx,[esi+0x8]         ; next
mov  [eax+0x8],ecx         ; prev->next = node->next
mov  eax,[esi+0x8]         ; next
test eax,eax / je skip
mov  edx,[esi+0x4]         ; prev
mov  [eax+0x4],edx         ; next->prev = node->prev
skip:
push esi / call 0x004524A1 / add esp,4     ; entry_free(node)
test edi,edi / mov esi,edi / jne loop
pop edi / pop esi / ret
```

The node is `vtable +0x00, prev +0x04, next +0x08, state +0x0C`; the chain head
is at `+0x18` of the receiver. Its shape is corroborated by four independent
retail sites:

* `0x00417750` (23-byte leaf, the same splice with the node in EAX) and
  `0x0041BF30` (the same splice as a `ret`-zero member) — identical instruction
  sequence, so the splice is a real shared operation rather than inlining noise.
* `0x0041C4E0` walks the chain at `+0x18` through `+0x08`, testing the state word
  at `+0x0C`, and calls virtual slot 3 (`[edx+0x0C]`); `0x00415D70` and
  `0x00425A60` walk the same chain and call slot 5 (`[edx+0x14]`). The chain
  link followed from the head is therefore `+0x08`, and the class has at least
  six virtual slots. This toolchain has no RTTI in the vtable (the already-landed
  `FUN_0041c4e0` binds its 4th declared virtual to `+0x0C`), so this region's
  `[edx+0x10]` is the **fifth declared virtual**.
* `0x0041C23C` carries a byte-for-byte inlined copy of the whole loop inside the
  score-extended-object destructor `0x0041C1C0`, which then stores `0` into
  `ds:0x47781c`. That copy is what fixed the loop shape.
* The factory `asm_ScoreManager_CreateAndInitRetail_0041c290`
  (`src/game/object_factories.cpp`) allocates the 0x45C
  receiver and puts the embedded score object at `+0x10`, so the receiver's
  `+0x18` is `+0x08` of that embedded object. The `prev` load at `+0x04` has **no
  null test**, so the head node's predecessor must be a valid object whose `+0x08`
  is the head slot — exactly the embedded score object whose address the same
  factory publishes at manager `+0x434`. The model keeps that by naming `+0x04`
  the predecessor/container link; a `next`-only singly linked list cannot be
  spliced this way and would have needed the null test retail does not have.

The chain head is never nulled, so this is a teardown, not a reset (the resets
live in the two callers).

## Callers and registers

Both callers are inside `asm_FUN_00418190_00418190` (`src/game/stage_update.cpp`)
and load the receiver into EAX in front of the call:

* `0x00418261`: `mov eax,ds:0x47781c` / `call 0x417770`; ESI held `0x477834`'s
  object from `0x00418233` and EDI is the caller's arena pointer; EBP is the
  caller's frame pointer. EBX is re-loaded at `0x00418266`, so it is not live in.
* `0x00418460`: `mov eax,ds:0x47781c` / `call 0x417770`; ESI held `0x477834`'s
  object from `0x00418433` and EDI is set at `0x0041843e`, EBX re-loaded at
  `0x00418465`.

So the body must keep ESI, EDI, EBX and EBP, and may clobber only ECX/EDX. The
landed body **pushes and pops exactly ESI and EDI, never touches EBX or EBP, and
uses ECX for the virtual receiver and the free argument and EDX for the table
pointer/predecessor** — the same registers retail's bytes use, and both are dead
at both call sites. The emitted bytes are identical to retail's, so every
register claim here is read off the same listing.

The emitted synthetic context is 13 bytes and reproduces the caller shape
exactly: `a1 1c 78 47 00` (`mov eax,ds:0x47781c`) `e8 96 ff ff ff` (`call`) `33 c0`
(`xor eax,eax`) `c3`. The manager arrives in EAX because the whole-program pass
puts the global load there, which is why this region needs the cluster path at
all.

## Source `src/game/recovery_linked_cleanup_00417770.cpp`

```cpp
// 0x00417770..0x004177B1: release a whole chain of score-list nodes.
//
// The region is entered with the owning score object in EAX rather than in the
// ordinary MSVC thiscall slot: both retail callers do
// `mov eax, ds:0x47781c; call 0x417770` (0x00418261, 0x00418460), and the
// native-LTCG pass picked EAX for the receiver because the manager pointer is
// already there.  The chain itself lives at +0x18 of the object, which is the
// first link field of the embedded score object; every node keeps the
// predecessor that points at it in +0x04, so the head node points back at its
// container and the splice never needs a null test on that side.  The same
// splice appears as a separate leaf at 0x00417750 and as the fourth virtual slot
// of the embedded score object (0x0041BF30), and the same chain is walked with
// the same link offsets by 0x0041C4E0, 0x00415D70 and 0x00425A60.
//
// The receiver convention is a whole-program decision, so this model lives in
// the native-LTCG cluster
// layout/ltcg/recovery_linked_cleanup_00417770.json, whose driver carries the
// synthetic caller that establishes it.

extern "C" void __cdecl entry_free_004524a1(void* memory);   // 0x004524A1

// One chain node: a virtual release hook, the predecessor link, the successor
// link and a state word.  Slots 3, 4 and 5 are reached by 0x0041C4E0,
// 0x00415D70 / 0x00425A60 and by this region respectively, so the hook this
// region calls is the fifth declared virtual.
struct LinkedNode_00417770 {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Release();          // vtable +0x10, called here
    virtual void Slot5(void* arg);

    LinkedNode_00417770* prev;       // +0x04: predecessor, or the container
    LinkedNode_00417770* next;       // +0x08: successor
    int state;                       // +0x0C
};

struct ScoreChain_00417770 {
    unsigned char reserved_000[0x18];
    LinkedNode_00417770* head;       // +0x18

    __declspec(noinline) void ReleaseChain();
};

#pragma code_seg(".text$01release")
void ScoreChain_00417770::ReleaseChain() {
    LinkedNode_00417770* node = head;
    while (node != 0) {
        LinkedNode_00417770* next = node->next;
        node->Release();
        node->prev->next = node->next;
        if (node->next != 0)
            node->next->prev = node->prev;
        entry_free_004524a1(node);
        node = next;
    }
}
#pragma code_seg()
```

sha256 `ad42e357336ec22a1d02acfa5016c2debd0746c9a6c079bf8600a0932c3f5ed7`.

The old `_asm_RecoveryLinkedCleanup_00417770` binding is untouched in `symbols`,
so `src/game/stage_update.cpp:123` and `:427` keep their naked `call
asm_RecoveryLinkedCleanup_00417770` and the duplicate naked body at
`src/game/recovery_leaves.cpp:758` is never placed — the same shape as the
landed `0x0040C6E0` and `0x00419040` regions.

## Driver `layout/ltcg/recovery_linked_cleanup_00417770_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_linked_cleanup_00417770.cpp"

extern "C" ScoreChain_00417770* data_0047781c;

#pragma code_seg(".text$03context")
int __stdcall RecoveryLinkedCleanupCompilerContext() {
    ScoreChain_00417770* manager = data_0047781c;
    manager->ReleaseChain();
    return 0;
}
#pragma code_seg()
```

sha256 `303056e714b9a4af55b98d25dc2562aa0050d06154c0d165d42ea452641884bf`.
The global load in the caller is what moves the member's `this` from ECX to EAX;
the emitted context is 13 bytes at `0x004177D0`.

## Layout `layout/ltcg/recovery_linked_cleanup_00417770.json`

```json
{
  "schema_version": 1,
  "name": "recovery_linked_cleanup_00417770",
  "source": "src/game/recovery_linked_cleanup_00417770.cpp",
  "driver": "layout/ltcg/recovery_linked_cleanup_00417770_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Score chain release compiled with native LTCG so the owning score object arrives in EAX.",
  "functions": [
    {
      "name": "ScoreChain_00417770_ReleaseChain",
      "symbol": "?ReleaseChain@ScoreChain_00417770@@QAEXXZ",
      "section": ".text$01release",
      "address": "0x00417770",
      "size": 66,
      "actual_abi": "owner in EAX; plain RET"
    }
  ],
  "context": {
    "symbol": "?RecoveryLinkedCleanupCompilerContext@@YGHXZ",
    "section": ".text$03context",
    "address": "0x004177D0",
    "size": 13,
    "description": "Synthetic manager-calling entry that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 92016
    },
    {
      "section": ".text$02layout",
      "address": "0x004177B2",
      "size": 30
    }
  ],
  "constants": [],
  "absolute_symbols": [
    {
      "symbol": "_entry_free_004524a1",
      "address": "0x004524A1",
      "kind": "relative_code"
    },
    {
      "symbol": "_data_0047781c",
      "address": "0x0047781C",
      "kind": "data"
    }
  ]
}
```

sha256 `1e5a9e8767cfa1272bbc32b0d72d6d7d50e9ad7f379c23c4a5c9f9f9a2ca59e8`.

## Shapes tried

* **A — member with the container's head cached in a local, `while` loop** (the
  landed shape): emits 66 bytes, byte-identical to retail on the first build.
  MSVC keeps the head in ESI, `next` in EDI, the vtable in EDX and the virtual
  receiver in ECX, and reproduces the `lea esp,[esp+0x0]` alignment instruction,
  the asymmetric `eax`/`ecx` reload of `node->next` around the call, and the
  placement of `push edi` after the initial null test. The variant that reported
  `len=66 (want 66) different=0` is the same text reproduced above.

No second shape was needed: no float pool, no `constant_aliases`, no `roots`,
no additional sources, and no register bridges. The only enabling decision was
to model the operation as a member (`this` in ECX by declaration) and let the
synthetic caller's global load move the receiver into EAX, exactly as the /GL
pass did in retail.
