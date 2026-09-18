# 0x0040BD20 landed as a native-LTCG cluster: the ending-script state tick

Date: 2026-09-19
Region: `0x0040BD20..0x0040BD7C`, 93 bytes, source
`src/game/recovery_tick_state_0040bd20.cpp`. **EXACT via the native-LTCG
cluster path** (one function + one synthetic context, no additional sources).

```
0x0040bd20      93 bytes  ?TickRecoveryState_0040bd20@@YGHPAURecoveryTickState_0040bd20@@@Z  EXACT
EXACT
```

All 93 emitted bytes equal retail's, and the emitted interactive disassembly is
instruction-for-instruction retail's:

```text
40bd20: push   %esi
40bd21: call   0x40bd80
40bd26: test   %eax,%eax
40bd28: je     0x40bd30
40bd2a: mov    $0x1,%eax
40bd2f: ret
40bd30: mov    0x8(%esi),%edx
40bd33: mov    0x10(%esi),%ecx
40bd36: mov    %edx,0x4(%esi)
40bd39: flds   (%ecx)
40bd3b: fcomps 0x470b68
40bd41: fnstsw %ax
40bd43: test   $0x41,%ah
40bd46: jne    0x40bd6a
40bd48: flds   (%ecx)
40bd4a: fcomps 0x470b64
40bd50: fnstsw %ax
40bd52: test   $0x5,%ah
40bd55: jp     0x40bd6a
40bd57: flds   0xc(%esi)
40bd5a: inc    %edx
40bd5b: fadds  0x470afc
40bd61: mov    %edx,0x8(%esi)
40bd64: xor    %eax,%eax
40bd66: fstps  0xc(%esi)
40bd69: ret
40bd6a: flds   0xc(%esi)
40bd6d: fadds  (%ecx)
40bd6f: fsts   0xc(%esi)
40bd72: call   0x463b2c
40bd77: mov    %eax,0x8(%esi)
40bd7a: xor    %eax,%eax
40bd7c: ret
```

## What the region computes

It is the frame tick of the ending/credits script state, whose constructor is
`0x0040BA90` (`src/game/ending_text.cpp`). That constructor writes the exact
`FrameTimer` shape at `+0x04`: `previous = -1`, `current = 0`, `elapsed = 0`,
`speed = &DAT_00476F78`, `flags |= 1` (the same five fields `th10/math/timer.hpp`
declares, three such timers at `+0x04`, `+0x18`, `+0x2C`), sets
`this+0x54 = script` and `this+0x74 |= 1`. This region ticks the first one:

1. `if (sub_0040BD80(state)) return 1;` — the "script finished?" query at
   `0x0040BD80`, which reads `state+0x54`, `+0x1c`, `+0x74`, `+0x40`, `+0x78`;
2. `previous = current`;
3. at normal speed (`*speed` inside the shared `0.99f/1.01f` window) it advances
   the counter by one frame and adds `1.0f` to `elapsed`;
4. otherwise it accumulates `*speed` into `elapsed` and truncates that
   accumulation into `current`;
5. returns `0`.

The window comparison is retail's `fcomps`/`fnstsw`/`test ah,41h` + `test ah,5h`
pair, i.e. `*speed > 0.99f && *speed < 1.01f` with the unordered cases folded
into the else path exactly as MSVC emits it. The `+=` value stays on the x87
stack (`fsts`, not `fstps`) for the `int` conversion, which is why `current` is
read once into EDX at `+0x30` and incremented with a bare `inc`.

## Register evidence

* Retail's only caller, `Recovery_UpdateEmitterDecision_0040B9F0` (still
  `__declspec(naked)` asm), does `push esi / mov esi,[edi+18h] / call
  0x0040BD20`: the state is a **live-in in ESI**, handed over without any stack
  argument, and the callee never writes ESI (the `push esi` at entry is the
  argument to `0x0040BD80`, a `__stdcall` that cleans it with `ret 4`). Hence
  all three returns are plain `C3`.
* The emitted body keeps exactly that: `push %esi` as the guard argument, the
  state read only through ESI, plain `ret` at `+0x0F`, `+0x49`, `+0x5C`, and no
  prologue/epilogue at all. No register was reassigned.
* The two window bounds stay in ECX across both comparisons: the source
  dereferences `state->speed` twice, and MSVC CSEs the member load. Writing the
  pointer into a local changes nothing.

## Files

* `src/game/recovery_tick_state_0040bd20.cpp` — the model (this source owns only
  this region, so the cutover is complete).
* `layout/ltcg/recovery_tick_state_0040bd20.json` — layout below.
* `layout/ltcg/recovery_tick_state_0040bd20_context.cpp` — synthetic
  array-walking caller; establishes the convention, contributes no game code.

```cpp
// 0x0040BD20..0x0040BD7C: TickRecoveryState_0040bd20
//
// The state this runs on is the ending/credits script object constructed at
// 0x0040BA90. At +0x04 it carries the FrameTimer shape shared by the whole
// image: a previous/current integer pair (+0x04/+0x08), an elapsed float
// (+0x0C) and a pointer (+0x10) to the shared game speed. Retail, in order:
//
//     push esi                 ; the state arrives in ESI; the push is the
//     call 0x0040BD80          ; argument to the finished? query, which pops it
//     test eax,eax / je
//     mov eax,1 / ret          ; finished -> report 1
//     mov edx,[esi+8]          ; current
//     mov ecx,[esi+10h]        ; speed
//     mov [esi+4],edx          ; previous = current
//     ...
//     xor eax,eax / ret        ; still running -> 0
//
// The timer body at +0x04 is the usual frame tick: at normal speed it advances
// the frame counter and adds 1.0 to the elapsed field, otherwise it converts
// the elapsed accumulation of the speed pointer into the new counter.

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

extern "C" int __stdcall asm_FUN_0040bd80_0040bd80(void* state);

struct RecoveryTickState_0040bd20 {
    int pad_00;             // +0x00
    int previous;           // +0x04
    int current;            // +0x08
    float elapsed;          // +0x0C
    const float* speed;     // +0x10
};

#pragma code_seg(".text$01tick")
__declspec(noinline) int __stdcall TickRecoveryState_0040bd20(RecoveryTickState_0040bd20* state) {
    if (asm_FUN_0040bd80_0040bd80(state))
        return 1;

    state->previous = state->current;
    if (*state->speed > g_frame_timer_normal_lower &&
        *state->speed < g_frame_timer_normal_upper) {
        ++state->current;
        state->elapsed += 1.0f;
    } else {
        state->current = int(state->elapsed += *state->speed);
    }
    return 0;
}
#pragma code_seg()
```

```cpp
// layout/ltcg/recovery_tick_state_0040bd20_context.cpp
// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: the state in ESI, plain RET.
#include "../../src/game/recovery_tick_state_0040bd20.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryTickStateCompilerContext_0040bd20(RecoveryTickState_0040bd20** states,
                                                       int count) {
    int result = 0;
    for (int index = 0; index < count; ++index)
        result = TickRecoveryState_0040bd20(states[index]);
    return result;
}
#pragma code_seg()
```

Layout (`layout/ltcg/recovery_tick_state_0040bd20.json`), complete:

```json
{
  "schema_version": 1,
  "name": "recovery_tick_state_0040bd20",
  "source": "src/game/recovery_tick_state_0040bd20.cpp",
  "driver": "layout/ltcg/recovery_tick_state_0040bd20_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Ending-script state tick compiled with native LTCG so the state arrives in ESI and the call returns with a plain RET.",
  "functions": [
    {
      "name": "TickRecoveryState_0040bd20",
      "symbol": "?TickRecoveryState_0040bd20@@YGHPAURecoveryTickState_0040bd20@@@Z",
      "section": ".text$01tick",
      "address": "0x0040BD20",
      "size": 93,
      "actual_abi": "state in ESI; plain RET"
    }
  ],
  "context": {
    "symbol": "?RecoveryTickStateCompilerContext_0040bd20@@YGHPAPAURecoveryTickState_0040bd20@@H@Z",
    "section": ".text$03context",
    "address": "0x0040BD90",
    "size": 41,
    "description": "Synthetic array-walking caller that establishes the observed internal register convention; not recovered game code."
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 44320},
    {"section": ".text$02layout", "address": "0x0040BD7D", "size": 19}
  ],
  "constants": [],
  "constant_aliases": [
    {"symbol": "__real@3f800000", "address": "0x00470AFC", "value": 1.0}
  ],
  "absolute_symbols": [
    {"symbol": "?g_frame_timer_normal_lower@@3MA", "address": "0x00470B68", "kind": "data"},
    {"symbol": "?g_frame_timer_normal_upper@@3MA", "address": "0x00470B64", "kind": "data"},
    {"symbol": "_asm_FUN_0040bd80_0040bd80@4", "address": "0x0040BD80", "kind": "relative_code"},
    {"symbol": "__ftol2", "address": "0x00463B2C", "kind": "relative_code"},
    {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"}
  ]
}
```

`constant_aliases` is load-bearing: the `1.0f` literal has to be read at retail's
shared pool slot `0x470AFC`, which a one-function cluster cannot reach (its own
pooled copy lands next to the context). An `extern float` 1.0f instead of the
alias compiles to the same extent but the wrong instruction *order* (see shape 2
below), so the literal must stay a literal and only its address is rebound.

## Integration

```
python3 matching2/tools/waves/register_cluster.py \
    --project matching2/msvc \
    --layout layout/ltcg/recovery_tick_state_0040bd20.json --apply
```

then the focused probe (above) and the whole build; semantic bytes rise by 93.

Nothing else needs a cutover: the naked caller `asm_Recovery_TickState_0040bd20`
in `src/game/recovery_update_emitter_decision_0040b9f0.cpp` keeps resolving
through the manifest's `symbols` entry `_asm_Recovery_TickState_0040bd20 =
0x0040BD20` (the link script supplies it because the region now defines the
decorated name instead), and the stale naked copy inside
`src/game/recovery_leaves.cpp` is not selected by any region and is dropped by
normalization exactly as before.

## Shapes tried

All three were compiled with the project profile; shapes 1-2 were measured on
their standalone objects, which is enough to see the two failure modes.

| # | shape | result |
| --- | --- | --- |
| 1 | member `RecoveryTickState_0040bd20::Tick()` + `1.0f` literal | 99 bytes: the entry is still ECX, so MSVC emits `push esi / mov ecx,esi` and, because the receiver is callee-saved, one `pop esi` before every `ret` (three returns). The x87 operand orders are already retail's. |
| 2 | free `__stdcall` function with `elapsed += g_frame_timer_one` (`extern float`) in place of the literal | 107 bytes on the stack ABI, and the in-range pair comes out `flds g_frame_timer_one / fadds 0xc(%esi)` — the reverse of retail's `flds 0xc(%esi) / fadds [pool]`. The literal cannot be faked by a global: only the *address* may be rebound, never the operand kind. |
| 3 | free `__stdcall` function + array-walking context + literal with the `__real@3f800000` alias | **EXACT**, 93 bytes, ESI entry, plain RET. |

Shape 3's standalone baseline is already the retail body apart from the
convention — `push esi / mov 0x8(%esp),%esi / push esi / call / ... / pop esi /
ret 4` — so the model is register-assignment-neutral and only the synthetic
caller's shape decides the ESI entry. Shape 3 also confirms the two window
bounds need nothing special: they stay `fcomps` against the bound globals.
