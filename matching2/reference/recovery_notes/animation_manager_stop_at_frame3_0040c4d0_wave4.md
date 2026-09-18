# StopAtFrame3 `0x0040C4D0` (65 bytes): EXACT, in the shared pair cluster

2026-09-19, wave 4. Region `0x0040C4D0` is recovered as C++ that compiles to the
retail bytes. It lands as the third function of the single cluster
`layout/ltcg/stop_at_frame_pair_0040c480.json`, which StopAtFrame2 authored and
which also owns `0x0040C480` and the shared lookup `0x004491C0`; the lookup can
only be claimed once, so this note records my region and its independent
verification rather than a second layout. The shared recipe is in
`animation_manager_stop_at_frame2_0040c480_wave4.md`.

## Verification

The pair landing is already in the maintained tree (sources, layout, driver and
the three region records); I verified it there too, from a fresh copy that was
never built in place (`/tmp/AnmStopAtFrame3/verify`), so the numbers below are
for the texts that actually landed, not just for my own:

```
$ python3 matching2/tools/matching/probe.py \
    --source src/render/animation_manager_stop_at_frame2_0040c480.cpp \
    --project /tmp/AnmStopAtFrame3/verify --output /tmp/AnmStopAtFrame3/verify_probe --show 10
0x0040c480      65 bytes  ?StopAtFrame2@AnimationHandle@@QAEXXZ  EXACT
0x0040c4d0      65 bytes  ?StopAtFrame3@AnimationHandle@@QAEXXZ  EXACT
0x004491c0      73 bytes  ?Find@AnimationManager@@QAIPAXPAUAnimationLookupContext@@UAnimationScriptId@@@Z  EXACT
EXACT
```

**Manifest defect found here, since fixed**: the manifest's `translation_units`
was missing `src/render/animation_manager_find_004491c0.cpp`, which now owns
`0x004491C0`. Probes did not catch it — `probe.py`'s `load_manifest` only
re-checks the text hash — but the whole-image build did:

```
$ python3 -c "import json,sys; sys.path.insert(0,'.'); \
  from matching2.tools.matching.build_msvc import validate_project; \
  validate_project(json.load(open('matching2/msvc/regions.json')), \
                   json.load(open('matching2/msvc/pe_layout.json'))['reference'])"
ValueError: translation unit list disagrees with region ownership
```

The manual multi-source write recomputed the cluster list and the region records
but not this derived list; the integration owner added the entry
(`translation_units` 2392 → 2393) and `validate_project` now returns 4425
regions over 2393 units. The recompute `register_cluster.py` performs
automatically is `translation_units = sorted({region['source'] for region in regions})`.

## Independent rebuild (second sandbox)

Scratch tree `/tmp/AnmStopAtFrame3/msvc` (never the maintained tree), rebuilt
from the three cluster sources, the layout and the driver below:

```
$ python3 matching2/tools/matching/probe.py \
    --source src/render/animation_manager_stop_at_frame2_0040c480.cpp \
    --project /tmp/AnmStopAtFrame3/msvc --output /tmp/AnmStopAtFrame3/probe_pair --show 30
0x0040c480      65 bytes  ?StopAtFrame2@AnimationHandle@@QAEXXZ  EXACT
0x0040c4d0      65 bytes  ?StopAtFrame3@AnimationHandle@@QAEXXZ  EXACT
0x004491c0      73 bytes  ?Find@AnimationManager@@QAIPAXPAUAnimationLookupContext@@UAnimationScriptId@@@Z  EXACT
EXACT
```

The carve moves `0x004491C0` out of `src/render/animation_manager.cpp`, so that
unit is re-probed as the regression gate on the carve; both of its remaining
regions stay byte-identical:

```
$ python3 matching2/tools/matching/probe.py \
    --source src/render/animation_manager.cpp \
    --project /tmp/AnmStopAtFrame3/msvc --output /tmp/AnmStopAtFrame3/probe_plain2
0x0043ec70     144 bytes  _asm_AnimationObject_ReadIntegerVariable_0043ec70  EXACT
0x004492a0      66 bytes  ?SetFlag@AnimationManager@@QAIPAXPAUAnimationLookupContext@@H@Z  EXACT
EXACT
```

`cmp` of the emitted cluster bytes against the image at `0x0040C4D0` (65/65) is
`IDENTICAL`; emitted and retail disassembly agree instruction for instruction,
including the `lea 0x0(%esp),%esp` loop-alignment nop at `+0x2C`:

```
retail / emitted (0x0040C4D0)               note
8b 00           mov  eax,[eax]              handle's script id, loaded in place in EAX
8b 15 10 1c 49 00  mov edx,ds:0x491c10     lookup context in EDX
50              push eax                    script id on the stack (the lookup's arg 3)
e8 e2 cc 03 00  call 0x004491c0             internal lookup; ECX is never written
85 c0           test eax,eax
74 2e           je   done
8b 50 18        mov  edx,[eax+0x18]         children flagged
85 d2           test edx,edx
b9 03 00 00 00  mov ecx,3                   frame constant (2 in the sibling)
66 89 88 04 03 00 00  mov word [eax+0x304],cx
75 1b           jne  done
8b 40 14        mov  eax,[eax+0x14]         child list head
85 c0           test eax,eax
74 14           je   done
8d 64 24 00     lea  esp,[esp+0]            16-byte loop alignment
8b 10           mov  edx,[eax]              child->object
66 89 8a 04 03 00 00  mov word [edx+0x304],cx
8b 40 04        mov  eax,[eax+0x4]          child->next
85 c0           test eax,eax
75 f0           jne  loop
c3              ret
```

## Registers retail's callers use, and whether the emitted body keeps them

Every one of the 20 recovered call sites loads **only EAX** (`lea eax,[ebp+4Ch];
call 0x0040C4D0`) and cleans no stack (`call` with no following `add esp`), so
the entry convention is: handle-slot address in EAX, nothing else, and a plain
`ret`. A scan of the preceding 80 instructions at each `StopAtFrame2/3` call
site finds ECX holding an unrelated leftover at all of them (`mov ecx,[ebp+84h]`,
`mov ecx,edi`, `inc ecx`, `mov ecx,492590h`, …), so retail's ECX at the lookup
call is undefined, not a live value.

The emitted body keeps exactly that: EAX carries the handle, EAX is reused for
the dereferenced id, EDX carries the manager global, the id goes to the stack,
**no instruction touches ECX** before the lookup call, and the epilogue is a
plain `ret` (65 bytes, no stack parameter).

## Shapes tried, and the delta each produced

All against the emitted region at `0x0040C4D0`; "diffs" is the differing-byte
count over the 65-byte region.

| shape | emitted | delta |
|---|---|---|
| node-class member, `Find(field_000, ctx, (int)field_000)` opaque, array-walk context | `mov ecx,[eax]; mov edx,ctx; push ecx; call` | 2 differing bytes (`8b 08`/`51` for `8b 00`/`50`) |
| same, but `Find(this, ctx, (int)field_000)` | `mov eax,[ecx]; …` | 1 byte (`8b 01` for `8b 00`): `this` moved to ECX, the load base with it |
| manager-member `StopAtFrame3(const int*)` + opaque 3-arg lookup, 8 context shapes (single call, pair walk, two arrays, manager from a global, manager hoisted, fastcall context, member context, 2-array fresh-load loop) | `mov ecx,[eax]; mov edx,ctx; push ecx; mov ecx,[esp+8]; call`, `ret 4` | 42: the dead receiver stayed a stack parameter |
| free `__fastcall (owner, handle)` / `__stdcall (owner, handle)` / `(handle, owner)`, same contexts | same | 42 |
| node-member with an `owner` parameter (thiscall and fastcall members) | same | 42 |
| lookup bound opaquely but declared with an `int` id (landed `SetFlag` shape) | `mov ecx,[eax]; push ecx` | 2 |
| lookup **internal** (locally defined body) but not ABI-pinned | `mov ecx,[eax]; mov edx,ctx; call` | the pass re-conventioned the lookup and hoisted the `int` id into ECX; the id left the stack slot |
| lookup internal with `int id` | same | id promoted into ECX |
| lookup internal, `AnimationScriptId` record, region modelled as a member of the **manager** | `mov eax,[eax]; mov edx,ctx; push eax; call` … `ret 4` | 2: correct call site, but the dead manager stayed a stack parameter |
| **final**: lookup a selected cluster function with `__declspec(noinline)` and a four-byte record id, region modelled as a member of the **handle** | exact | 0 |

Two facts do all the work: the lookup must be *internal* to the whole-program
pass (a bound symbol cannot have its unused receiver dropped, and every opaque
shape keeps the receiver live and ends `ret 4`), and the script id must be a
**record** rather than an `int`, otherwise the pass hoists it out of the caller's
push slot into the freed ECX.

Rejected alternative: keeping the lookup in `src/render/animation_manager.cpp`
and pinning that file's three regions with `#pragma code_seg` instead of carving
it. It does keep all four regions EXACT (probed), but it drags `SetFlag` under
`/GL` and needs six address gaps; the carve keeps `SetFlag` and the naked
`0x43EC70` as an ordinary unit, so it is the shape that should land.

## Source `src/render/animation_manager_stop_at_frame3_0040c4d0.cpp`

This is the text built and probed in `/tmp/AnmStopAtFrame3`. It is
interchangeable with the text in the pair note — same declarations, same code,
comment wording only — so exactly one of the two may be installed; the pair note
is the canonical copy for the shared cluster.

```cpp
// 0x0040C4D0 - stop-frame setter for an animation handle: look the handle's
// object up, pin its stop frame to 3 and, when that object has no children of
// its own yet, write the same frame into every object on its child chain.
//
// The handle is the receiver and the only input: retail's callers put its
// address in EAX and set no other register, and the animation lookup never
// reads its own receiver, so the whole-program pass leaves the dereferenced
// script id in EAX and hands it to the lookup in the stack slot.  Only a
// native-LTCG cluster reaches that convention; the pair lives in
// layout/ltcg/stop_at_frame_pair_0040c480.json.

struct AnimationLookupContext;

// The script id is a four-byte record so the lookup reads it from its stack
// slot; as a plain int the pass would promote it into ECX, the receiver
// register retail never writes (see animation_manager_find_004491c0.cpp).
struct AnimationScriptId {
    int value;
};

// One node of the lookup result's child chain; the object it points at carries
// its script id in its first word.
struct AnimationTreeNode {
    AnimationTreeNode* object;              // +0x000
    AnimationTreeNode* next;                // +0x004
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;            // +0x014
    int children_flagged;                   // +0x018
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;              // +0x304
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

// The handle the callers pass by address; its first word is the script id.
struct AnimationHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
};

extern "C" AnimationLookupContext* data_00491c10;

#pragma code_seg(".text$30stop3")
void AnimationHandle::StopAtFrame3() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node != 0) {
        node->stop_frame = 3;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 3;
        }
    }
}
#pragma code_seg()
```

## Layout `layout/ltcg/stop_at_frame_pair_0040c480.json`

Shared with `0x0040C480` and `0x004491C0`; reproduced verbatim from the copy this
region was verified in.

```json
{
  "schema_version": 1,
  "name": "stop_at_frame_pair_0040c480",
  "source": "src/render/animation_manager_stop_at_frame2_0040c480.cpp",
  "additional_sources": [
    "src/render/animation_manager_stop_at_frame3_0040c4d0.cpp",
    "src/render/animation_manager_find_004491c0.cpp"
  ],
  "driver": "layout/ltcg/stop_at_frame_pair_0040c480_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "StopAtFrame2/StopAtFrame3 pair compiled with the animation lookup as an internal callee, so the whole-program pass drops the receiver the lookup never reads and leaves the dereferenced handle pointer in EAX.",
  "functions": [
    {
      "name": "AnimationManager_StopAtFrame2",
      "symbol": "?StopAtFrame2@AnimationHandle@@QAEXXZ",
      "section": ".text$10stop2",
      "address": "0x40c480",
      "size": 65,
      "actual_abi": "handle address in EAX; nothing on the stack; plain RET",
      "source": "src/render/animation_manager_stop_at_frame2_0040c480.cpp"
    },
    {
      "name": "AnimationManager_StopAtFrame3",
      "symbol": "?StopAtFrame3@AnimationHandle@@QAEXXZ",
      "section": ".text$30stop3",
      "address": "0x40c4d0",
      "size": 65,
      "actual_abi": "handle address in EAX; nothing on the stack; plain RET",
      "source": "src/render/animation_manager_stop_at_frame3_0040c4d0.cpp"
    },
    {
      "name": "AnimationManager_Find",
      "symbol": "?Find@AnimationManager@@QAIPAXPAUAnimationLookupContext@@UAnimationScriptId@@@Z",
      "section": ".text$50find",
      "address": "0x4491c0",
      "size": 73,
      "actual_abi": "context in EDX; script id on the stack; RET 4",
      "source": "src/render/animation_manager_find_004491c0.cpp"
    }
  ],
  "context": {
    "symbol": "?StopAtFrameCompilerContext@@YGHPAUAnimationHandle@@H@Z",
    "section": ".text$70context",
    "address": "0x449220",
    "size": 43,
    "description": "Synthetic caller that establishes the internal register convention; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x401000", "size": 46208},
    {"section": ".text$20layout", "address": "0x40c4c1", "size": 15},
    {"section": ".text$40layout", "address": "0x40c511", "size": 249007},
    {"section": ".text$60layout", "address": "0x449209", "size": 23}
  ],
  "constants": [],
  "absolute_symbols": [
    {"symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data"}
  ]
}
```

The 15-byte `.text$20layout` gap between the two bodies is the image's own
`0x0040C4C1` padding; the section tags `00 10 20 30 40 50 60 70` sort into
address order, and the 23-byte `.text$60layout` puts the context on its declared
16-byte-aligned `0x449220`.

## Driver `layout/ltcg/stop_at_frame_pair_0040c480_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/render/animation_manager_stop_at_frame2_0040c480.cpp"

#pragma code_seg(".text$70context")
int __stdcall StopAtFrameCompilerContext(AnimationHandle* handles, int count) {
    while (count--) {
        handles->StopAtFrame2();
        handles->StopAtFrame3();
        handles++;
    }
    return 0;
}
#pragma code_seg()
```

## Landing note

`register_cluster.py --apply` refuses this layout because it compares every
function's region source with the layout's single `source`; reproduced against
the throwaway copy:

```text
refused: region 0x40c4d0 is owned by src/render/animation_manager_stop_at_frame3_0040c4d0.cpp,
         not src/render/animation_manager_stop_at_frame2_0040c480.cpp
```

The manifest update therefore goes through the multi-source path the integration
owner uses for the other registered multi-source clusters
(`recovery_select_archive_entry_0043d790`, `sound_queue`, `bullet_manager_load_scripts`).
It has to move one region between sources: `0x004491C0` changes from
`src/render/animation_manager.cpp` to the new
`src/render/animation_manager_find_004491c0.cpp` (with the new symbol shown in
the layout), which also adds that translation unit; `0x0040C480` and `0x0040C4D0`
keep their sources and only change symbol/extent metadata — and that new
translation unit is what the stale `translation_units` list above is missing.

This recovery wrote nothing but this note into the maintained tree: every layout,
source and manifest edit above was made in `/tmp/AnmStopAtFrame3`, and the
`register_cluster.py` runs that produced the throwaway registrations were always
passed `--project /tmp/AnmStopAtFrame3/msvc`. The landing itself is
StopAtFrame2's; my scratch copy's single-source attempt was unregistered and its
layout and driver deleted, so the pair layout is the only claimant of the lookup.
