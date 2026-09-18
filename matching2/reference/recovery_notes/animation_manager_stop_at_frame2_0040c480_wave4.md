# StopAtFrame2 (0x0040C480) and StopAtFrame3 (0x0040C4D0): EXACT

2026-09-19, wave 4. Both 65-byte animations-stop regions are recovered as C++
that compiles to the retail bytes, together with the lookup they call. The two
bodies differ in one constant (2 against 3), exactly as the brief expected.

Landed as `fc936b3b` (203 bytes of `.text` become semantic). The
StopAtFrame3 side independently rebuilt the same texts in a fresh copy of the
maintained tree and probed all five regions exact (`4a8eb97c`). One follow-up
was needed after the landing: the manual multi-source manifest write left
`translation_units` stale, which `build_msvc.validate_project` rejects even
though every probe passes, because `probe.py` never calls it (`b58bfce5`).

```
$ python3 matching2/tools/matching/probe.py \
    --source src/render/animation_manager_stop_at_frame2_0040c480.cpp \
    --project /tmp/StopAtFrame2/msvc --output /tmp/StopAtFrame2/probe_pair --show 40
0x0040c480      65 bytes  ?StopAtFrame2@AnimationHandle@@QAEXXZ  EXACT
0x0040c4d0      65 bytes  ?StopAtFrame3@AnimationHandle@@QAEXXZ  EXACT
0x004491c0      73 bytes  ?Find@AnimationManager@@QAIPAXPAUAnimationLookupContext@@UAnimationScriptId@@@Z  EXACT
```

```
$ python3 matching2/tools/matching/probe.py \
    --source src/render/animation_manager.cpp \
    --project /tmp/StopAtFrame2/msvc --output /tmp/StopAtFrame2/probe_plain
0x0043ec70     144 bytes  _asm_AnimationObject_ReadIntegerVariable_0043ec70  EXACT
0x004492a0      66 bytes  ?SetFlag@AnimationManager@@QAIPAXPAUAnimationLookupContext@@H@Z  EXACT
```

The second probe is the regression gate on the carve below: the unit the lookup
moves out of keeps both of its own regions byte-identical.

## Registers retail's callers use, and what the emitted body keeps

Retail's callers (`lea eax,[ebp+40h]; call 0x0040C480`) put the **handle slot
address in EAX and nothing else**: no ECX, no EDX, nothing on the stack, and
`ret` with no operand. The emitted bodies keep exactly that: EAX carries the
handle, the lookup is reached with EDX = the manager global and the script id on
the stack, and the epilogue is a plain `ret`.

```
retail / emitted (0x0040C480)            note
8b 00        mov  eax,[eax]              handle slot -> id, reusing EAX
8b 15 10 1c 49 00  mov edx,ds:0x491c10  lookup context in EDX
50           push eax                    script id on the stack
e8 32 cd 03 00  call 0x4491c0            internal lookup
85 c0        test eax,eax
74 2e        je   done
8b 50 18     mov  edx,[eax+0x18]         children already flagged
85 d2        test edx,edx
b9 02 00 00 00  mov ecx,2                frame constant (3 in the sibling)
66 89 88 04 03 00 00  mov word [eax+0x304],cx
75 1b        jne  done
8b 40 14     mov  eax,[eax+0x14]         child list head
85 c0        test eax,eax
74 14        je   done
8d 64 24 00  lea  esp,[esp+0]            16-byte loop alignment
8b 10        mov  edx,[eax]               child->object
66 89 8a 04 03 00 00  mov word [edx+0x304],cx
8b 40 04     mov  eax,[eax+0x4]           child->next
85 c0        test eax,eax
75 f0        jne  loop
c3           ret
```

The alignment `nop` is not written in the source: it appears because the
preceding statements are retail's length, so MSVC aligns the loop head itself.

## Why the region needs a cluster, and what the shapes cost

The animation lookup is called with **ECX never written**. That is only true if
the lookup's receiver is dead: retail's original link dropped the lookup's
unused receiver parameter, so no caller sets ECX. Bound opaquely the receiver
cannot be dropped and every shape fails:

| shape tried | emitted | delta |
|---|---|---|
| free `__fastcall` lookup `(value, manager, id)` + manager-receiver region | `mov ecx,[eax]; push ecx; mov ecx,[esp+8]; call` | 41 differing bytes, `ret 4` for `ret` |
| lookup as `extern "C"` member/`__fastcall` variants, direct caller, array-walk caller, fastcall caller | same three instructions | same |
| lookup included in the cluster but with `int id` | `mov ecx,[eax]; mov edx,ctx; call` (id promoted into ECX) | the id left its stack slot |
| lookup included and `noinline`, region modelled as a member of the **manager** | `mov eax,[eax]; mov edx,ctx; push eax; call` then `ret 4` | 2 bytes: the dead manager stayed a stack parameter |
| **final**: lookup in the cluster with a 4-byte id record, region modelled as a member of the **handle** | exact | 0 |

Two devices carry the conventions, and both are load-bearing:

- the region is a member of the *handle* with no parameters, so the pass has one
  live pointer to place and picks EAX, leaving no stack parameter;
- the lookup's script id is a four-byte **record** (`AnimationScriptId`), which
  MSVC always passes in memory. As a plain `int` the pass hoists it out of the
  stack slot into the freed ECX. With the record the emitted call site is
  retail's `mov edx,ctx; push id; call` with ECX untouched, and the lookup's own
  body is byte-identical to the landed one either way (the record's dword is read
  straight from `[esp+4]`).

`__declspec(noinline)` on the lookup is mandatory: without it the whole-program
pass inlines the 73-byte lookup into both regions.

## The cluster

`layout/ltcg/stop_at_frame_pair_0040c480.json` owns three regions: the two
StopAtFrame bodies and the lookup. The lookup has to be a *selected* function of
the cluster rather than an opaque binding, and it therefore has to leave the
file that shared it with the flag setter.

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

The section tags sort into address order (`00`, `10`, `20`, `30`, `40`, `50`,
`60`, `70`), the context sits 23 bytes after the lookup and lands 16-byte
aligned at its declared 0x449220, and the 15-byte gap between the two bodies is
the `int3` padding the image keeps in its own data unit.

### Driver `layout/ltcg/stop_at_frame_pair_0040c480_context.cpp`

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

## Source `src/render/animation_manager_stop_at_frame2_0040c480.cpp`

```cpp
// 0x0040C480 - set the stop frame of the animation object registered under an
// animation handle to 2, and of that object's not-yet-flagged children.
//
// The handle is the receiver and the only input: retail's callers put its
// address in EAX and nothing else, and the animation lookup never reads its own
// receiver, so the whole-program pass leaves EAX holding the dereferenced
// pointer and hands the lookup's id back on the stack.  Both are conventions
// only a native-LTCG cluster reaches
// (layout/ltcg/stop_at_frame_pair_0040c480.json).

struct AnimationLookupContext;

// The script id is a four-byte record so the lookup reads it from its stack
// slot; see the note in animation_manager_find_004491c0.cpp.
struct AnimationScriptId {
    int value;
};

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

struct AnimationHandle {
    unsigned int value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
};

extern "C" AnimationLookupContext* data_00491c10;

#pragma code_seg(".text$10stop2")
void AnimationHandle::StopAtFrame2() {
    AnimationScriptId id;
    id.value = (int)value;
    AnimationTreeNode* node = reinterpret_cast<AnimationTreeNode*>(
        reinterpret_cast<AnimationManager*>(data_00491c10)->Find(data_00491c10, id));
    if (node != 0) {
        node->stop_frame = 2;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 2;
        }
    }
}
#pragma code_seg()
```

## Source `src/render/animation_manager_stop_at_frame3_0040c4d0.cpp`

Byte-for-byte the same model with `3` in both stores and the section tag
`.text$30stop3`; it declares both `StopAtFrame2` and `StopAtFrame3` so the driver
can reach either.

```cpp
// 0x0040C4D0 - set the stop frame of the animation object registered under an
// animation handle to 3, and of that object's not-yet-flagged children.
// The same model as 0x0040C480; only the frame constant differs.

struct AnimationLookupContext;

struct AnimationScriptId {
    int value;
};

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

## New source `src/render/animation_manager_find_004491c0.cpp`

The landed `AnimationManager::Find` moved out of `src/render/animation_manager.cpp`
(the body is unchanged apart from `id` becoming `id.value`); the file it left
keeps `SetFlag` and the naked `0x43EC70` and stays an ordinary unit, so neither
of those regions goes under `/GL` and no carve of the naked region is needed.

```cpp
// 0x004491C0 - look a script id up in the primary and then the secondary
// animation bucket, returning the registered object of the matching entry.
//
// Two conventions come out of the whole-program pass rather than the source.
// The script id is a four-byte record, so MSVC leaves it in the caller's push
// slot; as a plain int the pass promotes it into ECX - the receiver register,
// which retail's callers never write because this lookup never reads its own
// receiver.  Both shapes are what the retail callers and the StopAtFrame pair
// require, so this unit is compiled as a cluster
// (layout/ltcg/stop_at_frame_pair_0040c480.json).

// One node of a lookup bucket; the object it registers carries its script id
// in its first word.
struct AnimationEntry {
    AnimationEntry* object;             // +0x00: object registered by this node
    AnimationEntry* next;               // +0x04: next node of the bucket list
    unsigned char reserved_08[0x0C];
    AnimationEntry* children;           // +0x14: head of the child node list
    int children_flagged;               // +0x18: children already flagged
    unsigned char reserved_1c[0x340];
    unsigned int flags;                  // +0x35C
};

// The lookup buckets live far inside the animation context, the large runtime
// structure this lookup receives in EDX.
struct AnimationLookupContext {
    unsigned char reserved[0x72DAD4];
    AnimationEntry* primary_bucket;     // +0x72DAD4
    int reserved_2;                     // +0x72DAD8
    AnimationEntry* secondary_bucket;   // +0x72DADC
};

struct AnimationScriptId {
    int value;
};

class AnimationManager {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId id);
};

#pragma code_seg(".text$50find")
__declspec(noinline) void* __fastcall AnimationManager::Find(
        AnimationLookupContext* context, AnimationScriptId id) {
    if (!id.value)
        return 0;
    for (AnimationEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (AnimationEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()
```

## Edits the landing needs

1. Replace `src/render/animation_manager_stop_at_frame2_0040c480.cpp` and
   `src/render/animation_manager_stop_at_frame3_0040c4d0.cpp` with the models
   above (each file currently holds only that region's naked body, so the region
   records keep their source).
2. Add `src/render/animation_manager_find_004491c0.cpp` and delete from
   `src/render/animation_manager.cpp` the `Find` member declaration
   (`void* __fastcall Find(AnimationLookupContext* context, int id);`) and its
   definition with the comment above it. The lookup's scripts stay byte-identical:
   `SetFlag` reaches it through the existing `_asm_AnimationManager_Find_004491c0`
   binding at `0x004491C0`, which the manifest already carries.
3. Add the layout `layout/ltcg/stop_at_frame_pair_0040c480.json` and the driver
   `layout/ltcg/stop_at_frame_pair_0040c480_context.cpp`, append the layout to
   `ltcg_clusters`, and set the three regions:

```text
0x0040C480  source src/render/animation_manager_stop_at_frame2_0040c480.cpp
            symbol ?StopAtFrame2@AnimationHandle@@QAEXXZ  kind semantic
0x0040C4D0  source src/render/animation_manager_stop_at_frame3_0040c4d0.cpp
            symbol ?StopAtFrame3@AnimationHandle@@QAEXXZ  kind semantic
0x004491C0  source src/render/animation_manager_find_004491c0.cpp
            symbol ?Find@AnimationManager@@QAIPAXPAUAnimationLookupContext@@UAnimationScriptId@@@Z
            kind semantic
```

4. Recompute `translation_units = sorted({region["source"] for region in regions})`
   in the same write. The registered tools do this themselves
   (`register_cluster.py`, `promote_clusters.py`, `repair_units.py`); skipping
   it leaves the build aborting in `build_msvc.validate_project` with
   "translation unit list disagrees with region ownership" while every per-unit
   probe still passes, because `probe.py` never calls `validate_project`. It cost
   a follow-up commit after this landing.

`register_cluster.py` refuses this layout: it compares every function's region
source with the layout's single `source`, and two of the three functions belong
to additional sources (the same situation as the registered
`recovery_select_archive_entry_0043d790` layout). The manifest update therefore
has to go through the multi-source path, taking point 4 with it.

Latitude: the two handle types and the two `AnimationHandle`/`AnimationManager`
declarations are per-file models, so the exact type names only have to agree
between the two region sources and the lookup unit (the emitted symbols must
match the layout). Anything else that keeps the shapes - the handle receiver,
the record id, `noinline`, and the separate lookup unit - will reproduce the same
bytes.

## Artifacts

Sandbox `/tmp/StopAtFrame2/msvc` holds the exact tree; `drive_pair.py` rebuilds it
from the sources and re-probes, and `pair_run.txt` has the full disassembly of
the emitted and retail bodies.
