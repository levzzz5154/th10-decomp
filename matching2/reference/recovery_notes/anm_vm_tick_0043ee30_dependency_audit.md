# ANM VM tick `0x0043EE30` dependency audit

Audit date: 2026-09-23. Source disposition: retained retail assembly in
`matching2/msvc/src/script/anm_vm_tick.cpp`; no production C++ body was
substituted. The existing `matching2/reference/legacy_semantic` implementation
is useful as a behavior reference, but it is a hook-driven host model rather
than a layout- and ABI-compatible body for the retail object.

## Live Ghidra boundary and callers

The live Ghidra program `th10.exe` identifies `FUN_0043ee30` at
`0x0043EE30`, with body through `0x004413A2` and a 9,574-byte size metric.
Its final instructions restore the saved global speed, clear EAX, and return
with `ret 4` at `0x004413A0`. The retail source region is 9,964 bytes; after
the function, its source layout includes an alignment NOP at `0x004413A3` and
the 376-byte / 94-entry dispatch table at `0x004413A4..0x0044151B`.

Ghidra infers
`ulonglong __fastcall(undefined4 param_1, uint param_2, int param_3)`:
`param_1` is in ECX and unused, `param_2` is in EDX, and `param_3` is the
stack object pointer. The prologue loads that pointer from `[esp+0x104]`
after reserving locals and saving EBP; each return removes the one stack
argument with `ret 4`. EDX appears in the upper half of Ghidra's inferred
64-bit early-return values, while callers inspected here consume no result.
For example, caller `0x0043E8B0` clears ECX, loads EDX from the object's
`+0x6C` field, pushes the object, and calls `0x0043EE30`; it next updates the
global animation tick count. Caller `0x0043E710` likewise pushes the object
and does not use EAX or EDX after the call. This supports a semantic boundary
of one stack object pointer and `ret 4`; the inherited EDX value remains
relevant to byte-level register scheduling.

Ghidra reports 18 direct caller functions:

```text
0x00402720  0x00403990  0x00406240  0x004067D0  0x00408D60
0x00414900  0x00417040  0x0041AFD0  0x0041D3D0  0x0041E700
0x00425730  0x0043E710  0x0043E7E0  0x0043E8B0  0x00448860
0x00448900  0x00449250  0x00441590
```

The caller boundary itself does not require a conversion cluster: those
callers can continue to push the object and rely on the callee's `ret 4`.

## Control and data flow

Ghidra's control-flow analysis reports 532 basic blocks, 2,752 instructions,
362 conditional branches, 93 loops, and 203 call instructions. The main
dispatcher reads the animation object from the stack argument. It returns
complete when `object+0x390` (script PC) is null, returns active when flag
`object+0x35C & 0x20000` is set, and temporarily overrides the global frame
delta at `0x00476F78` when bit `0x20000000` is set.

When an interrupt id is pending at `object+0x304`, the routine scans the
script from `object+0x38C` for opcode `0x40`, remembers an exact-id handler
and the first `-1` fallback, saves/restores the animation timing and PC fields,
and routes through the same instruction loop. The loop compares each
instruction's signed timestamp at `PC+4` against `object+0x60`, dispatches
the opcode through the table at `0x004413A4`, advances or redirects `PC`, and
then performs the frame update. The dispatch domain covers the `0xFFFF`
terminator and opcodes `0x00..0x5C` (94 table slots after the index bias).
Post-dispatch work integrates velocity, rotation, scale, and growth; advances
position/scale/growth/color/alpha interpolation; refreshes ring-mode vertices;
updates the integer/fractional frame clock; and restores `0x00476F78`.

## Direct dependency and ABI blocker

Ghidra reports 203 call sites to 33 unique direct callees. They are spread
across operand resolution, x87 conversion and angle math, interpolation,
frame/timer updates, manager creation/handle validation, score-list insertion,
and allocation:

```text
VM / operand:       0x0043E5A0 0x0043EAC0 0x0043EC70 0x0043ED00
                    0x0043EDA0 0x0041AB70
Numeric / x87:      0x0043CB80 0x0044BB20 0x0044BC10 0x0044BF40
                    0x00463B2C 0x00463BBA 0x00463BF0
Interpolation:      0x00404610 0x00441600 0x00441950 0x00441AD0
                    0x00441EF0 0x00441F50 0x00442050 0x00442220
                    0x00442300 0x004452F0
Animation actions:  0x00428DD0 0x00448D00 0x00448E30 0x00448F60
                    0x00449090 0x00449450 0x00413200 0x004050D0
                    0x00405410 0x00452706
```

Several call edges cannot be represented by ordinary C++ declarations without
first replacing their private entry conventions. The VM calls
`0x0043EC70` with the object in ECX; calls `0x0043EDA0` after arranging
operand/object values in registers; calls `0x00404610` with a state pointer in
EAX and an output scratch pointer in EDI; and calls `0x00463B2C` with a live
x87 ST(0) value, receiving the converted frame value in EAX. For example, the
last call at `0x0044137F` leaves the accumulated time in ST(0), invokes
`0x00463B2C`, then stores EAX at `object+0x60`. The interpolation and manager
action families add more register-driven call surfaces. The large function
also shares PC, timing, interrupt, register-save, and frame-update state
across all opcode branches, so an individual case is not a sound conversion
cut.

The legacy model in `reference/legacy_semantic/src/script/anm_vm_tick.cpp`
expresses the opcode behavior with `AnmVmHooks` and a separately defined
`AnmVmState`. Its hooks stand in for the retail variable, timing, manager,
random, and drawing helpers. It is not a direct view of the retail object
layout (`+0x304`, `+0x35C`, `+0x38C`, `+0x390`, and embedded interpolators) and
does not preserve the per-call register/x87 inputs above. It should guide
opcode names and behavior, not be wired in as the implementation.

The smallest useful semantic cut is the complete `0x0043EE30` dispatcher plus
the nonstandard helper surfaces it calls, with its ordinary-ABI direct helpers
typed as dependencies. Converting only the entry while retaining guessed
no-argument declarations would discard real EAX/ECX/EDX/EDI or ST(0) inputs.
Converting callers is not required for semantics because the stack argument
and `ret 4` boundary is stable. Related evidence includes
`0043e710_wave11.md` (the one-stack-argument caller contract),
`fun_00414900_semantic_candidate.md` (animation-tick dependency context), and
`vector2_animation_polar_00441ef0.md` (an interpolation/math helper called
inside this dispatcher).

No build, probe, or test was run for this audit.
