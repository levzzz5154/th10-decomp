# Region 0x0040C540 (75 bytes) - wave 7

Date: 2026-09-19. Region `asm_FUN_0040c540_0040c540` in
`src/game/animation_resource_lazy_fetch.cpp`. **Result: not EXACT**, and nothing
was registered. Work was done in a throwaway copy (`/tmp/lazyfetch/msvc`); the
maintained manifest, sources and layouts are unchanged (`git status` clean).

The model is right in every respect except one instruction:
`lea edi,[esp+10h]` - the position record's register at the call to `0x00448D50`.
Everything up to `0x40C563` is byte-identical and the whole extent is 2 bytes
short, because the register is EDI (a convention no MSVC declaration can
express) and its save/restore is what those 2 bytes are.

## Retail

```
40c540: sub  $0xc,%esp            40c564: mov  0x8994(%esi),%eax   ; resource
40c543: mov  0x10(%esp),%eax      40c56a: push %edi
40c547: mov  0x14(%esp),%ecx      40c56b: push $0x6
40c54b: mov  %eax,(%esp)          40c56d: lea  0x18(%esp),%edx    ; &out
40c54e: mov  0x89a4(%esi),%eax    40c571: push %edx
40c554: test %eax,%eax            40c572: push %eax
40c556: mov  %ecx,0x4(%esp)       40c573: lea  0x10(%esp),%edi    ; &position
40c55a: movl $0x0,0x8(%esp)       40c577: call 0x448d50
40c562: jne  0x40c585             40c57c: mov  (%eax),%eax
                                  40c57e: mov  %eax,0x89a4(%esi)
                                  40c584: pop  %edi
                                  40c585: add  $0xc,%esp
                                  40c588: ret  $0x8
```

## Caller and callee ABI (read off the image, not guessed)

Retail's callers put the game thread's address in **ESI** and nothing else in a
register: `mov 0x4776e0,%esi; push $0x43c40000; push $0x43f00000; call
0x40c540` at `0x40c2d4`, `0x417d2b`, `0x417d53`, `0x417d6f`, `0x430e9f`,
`0x431339`, `0x4319e7`, so `arg1 = 480.0f`, `arg2 = 392.0f` and the callee pops
8 bytes of stack. Three of those sites are an *inlined* copy of the same body
(`0x417cc6`, `0x40b63f`, one more), which is what fixes the callee's contract.

`0x00448D50` is reached from six sites: every one of them passes
`(resource, &out, 6)` **on the stack** and the 12-byte position record in
**EDI**, and every caller then reads `*ret` (the callee returns the out slot):
`call; mov (%eax),%eax; mov %eax,0x89a4(%esi)`. Inside, EDI's three dwords are
copied to `[node+0x340]` (the animation position), `arg2` is handed to
`0x004489D0` as the slot it fills with the new handle, `arg1` reaches
`0x0043E710` in ECX and `arg3` reaches it in EBX. The callee is
`ret 0xC`. So the source-level signature is the legacy semantic one -
`(resource, out, index, position)` - with *one* register parameter, and that
register is EDI.

The emitted body keeps every one of these: receiver in ESI, the two floats at
`[esp+0x10]`/`[esp+0x14]`, the 12-byte position at `[esp]`, `sub esp,0Ch`,
`ret 8`, and retail's exact instruction schedule (`mov eax,[esp+10h]`,
`mov [esp],eax`, then the handle load and test *between* the position stores).

## Best model (source, driver, layout)

`src/game/animation_resource_lazy_fetch.cpp`:

```cpp
// 0x0040C540 - arm the game thread's animation resource handle once.
struct AnimationPosition { float x; float y; float z; };

// 0x00448D50 - the animation manager's positioned primary creation.
void** __stdcall AnimationManager_CreatePositionedPrimary_00448d50(
        void* resource, void** out, int index, const AnimationPosition* position);

struct GameThread_0040c540 {
    unsigned char reserved_000[0x8994];
    void* animation_resource;             // +0x8994
    unsigned char reserved_898[0x0C];
    void* animation_handle;               // +0x89A4
    __declspec(noinline) void EnsureAnimationResource(float x, float y);
};

#pragma code_seg(".text$01lazy")
void GameThread_0040c540::EnsureAnimationResource(float x, float y) {
    AnimationPosition position;
    position.x = x;
    position.y = y;
    position.z = 0.0f;
    if (animation_handle != 0)
        return;
    void* handle;
    animation_handle = *AnimationManager_CreatePositionedPrimary_00448d50(
        animation_resource, &handle, 6, &position);
}
#pragma code_seg()
```

Driver `layout/ltcg/lazy_resource_fetch_0040c540_context.cpp`:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/animation_resource_lazy_fetch.cpp"
#pragma code_seg(".text$03context")
int __stdcall LazyFetchCompilerContext(GameThread_0040c540** items, int count) {
    while (count--) {
        GameThread_0040c540* thread = *items++;
        thread->EnsureAnimationResource(480.0f, 392.0f);
    }
    return 0;
}
#pragma code_seg()
```

Layout (`functions[0].symbol` = `?EnsureAnimationResource@GameThread_0040c540@@QAEXMM@Z`,
context `.text$03context` at `0x40C5B0` size 47, gaps
`.text$00layout 0x401000/0xB540` and `.text$02layout 0x40C58B/0x25`,
`absolute_symbols`: the callee and `__fltused` at `0x00000000` kind
`metadata`):

```json
"absolute_symbols": [
  {"symbol": "?AnimationManager_CreatePositionedPrimary_00448d50@@YGPAPAXPAXPAPAXHPBUAnimationPosition@@@Z",
   "address": "0x00448D50", "kind": "relative_code"},
  {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"}
]
```

## Measurement

Emitted extent **73 bytes** against the declared 75; **32** differing bytes,
first at `0x23` - that is one byte into `mov eax,[esi+8994h]`, because this
variant reaches the resource in ECX. (It pushes the position as the fourth
`__stdcall` argument, so its push list is position/index/out/resource.)

The `__thiscall`-on-the-position variant is also 73 bytes but **31** differing
bytes and a cleaner mapping, so its delta is the one tabulated. Both reproduce
retail byte-for-byte through `0x40C563` (35 bytes: the prologue, the position
stores, the handle load, `test` and the `jne` opcode).

Instruction-level delta of the thiscall variant (retail -> emitted):

| retail | emitted | bytes |
|---|---|---|
| `mov 0x8994(%esi),%eax` | identical | 0 |
| `push %edi` | `push $0x6` | retail has one byte more here |
| `push $0x6` | `lea 0x14(%esp),%edx` | push imm8 (2) vs lea disp8 (4) |
| `lea 0x18(%esp),%edx` | `push %edx` | - |
| `push %edx` | `push %eax` | - |
| `push %eax` | `lea 0xc(%esp),%ecx` | ModRM ECX vs EDI, disp `0x0c` vs `0x10` |
| `lea 0x10(%esp),%edi` | `call 0x448d50` | call displacement differs (site is 1 byte lower) |
| `call 0x448d50` | `mov (%eax),%ecx` | ModRM |
| `mov (%eax),%eax` | `mov %ecx,0x89a4(%esi)` | ModRM |
| `mov %eax,0x89a4(%esi)` | `add $0xc,%esp` (at `0x40c583`) | - |
| `pop %edi` | `ret $0x8` (at `0x40c586`) | - |
| `jne 0x40c585` | `jne 0x40c583` | rel8 |

The 2-byte extent deficit is exactly `push %edi`/`pop %edi`. Everything else is
the ECX/EDI ModRM difference and the four-byte frame shift it causes in the two
`lea` displacements, the call displacement and the two tail offsets.

## Shapes tried (all through `register_cluster.py` against the copy)

1. `if (handle) return;` first - 74 bytes: the pass hoists the `[esi+0x89A4]`
   load above `sub esp,0Ch`, so the schedule is wrong from byte 0. Rejected.
2. position first, then `if (handle) return;` (the model above) - the whole
   35-byte head becomes exact. Kept.
3. same body with `AnimationPosition position = {x, y, 0.0f};` - identical
   bytes to (2).
4. callee bound as a `__thiscall` member of `AnimationPosition` (the position
   as `this`, so ECX) - 73 bytes, 31 differing: the closest match.
5. callee bound as a four-parameter `__stdcall` - 73 bytes, 32 differing.
6. **callee co-compiled** (a `__declspec(noinline)` C++ twin of `0x448D50` in
   `src/render/animation_manager_create_positioned_primary_00448d50.cpp`, in
   the same `/GL` scope, with the same four parameters) - 76 bytes, and the
   pass *did* choose a register for the position, but **EBX**, with `out` in
   EDI:

```
40c564: mov 0x8994(%esi),%edx     ; resource
40c56a: push %ebx                 ; position -> EBX
40c56b: push %edi                 ; out      -> EDI
40c56c: push $0x6
40c56e: push %edx
40c56f: lea 0x10(%esp),%edi       ; &out
40c573: lea 0x20(%esp),%ebx       ; &position
40c577: call 0x448d50
```

So the mechanism lesson 12 describes is confirmed: a co-compiled callee does
get a whole-program register convention for its parameters. The *choice*
follows the callee's own register pressure, and a twin whose three internal
calls are bound opaquely cannot reproduce retail's pressure - retail's
`0x448D50` receives its manager in ESI, its node in EAX, its resource in ECX
and its index in EBX from the callees it calls, all of which an opaque
declaration must put somewhere else.

## Why an opaque binding can never produce EDI

MSVC x86 has only ECX and EDX as parameter registers (`__fastcall`'s two,
`__thiscall`'s `this`); EDI, ESI, EBX and EAX are never parameter registers of
any declared convention, and the `/GL` pass only re-conventions a function
compiled into the same LTCG scope. Retail's EDI is a whole-program agreement of
`0x00448D50` with all six of its callers, so it can only be reproduced by
compiling that callee in the cluster - and the loader requires every declared
cluster function to be byte-exact, so the callee has to be recovered as real
C++, not bound.

## The closure the sanctioned route needs

`0x448D50`'s own 95 bytes pin the conventions of the three functions it calls,
so all three have to be co-compiled as exact contributions too:

| region | size | why it must be in the cluster |
|---|---:|---|
| `0x00448D50` | 95 | the position arrives in EDI; returns `out` in EAX |
| `0x00449950` | 161 | manager in **ESI**, object in EAX |
| `0x0043E710` | 203 | node in **EAX**, resource in ECX, index in **EBX** |
| `0x004489D0` | 118 | manager in EDX, node in **EBX**, out in **EAX** |
| `0x00401DE0` | 273 | object in **EDX** (called by 449950 and 43E710) |
| `0x00402050` | 88 | object in ECX - expressible opaquely, but it shares `src/game/entity.cpp` with `0x00401DE0` |

Their own callees that stay bindable: `0x00452493` (`operator new`, cdecl),
`0x0043EE30` (one stack argument), `0x00452422` (one stack argument, called
from `0x00401DE0`). `0x00401DE0` also makes an indirect `call *%ebx`.

`src/game/entity.cpp` owns both `0x00401DE0` and `0x00402050`, so that cluster
needs the `apply_package.py` route the way `results10/ScoreManagerCreate/` did
(a payload that moves `0x00401DE0` into its own unit) - `register_cluster.py`
cannot express it.

## What would land this region

Recover that closure as byte-exact C++ in one cluster with the model above.
The head of the model is already exact, so the region itself needs no further
work: with the position in EDI the emitted body is retail's 75 bytes.

Nothing was registered: the layout is 2 bytes short of the declared extent, so
by the project's rule it must not be.
