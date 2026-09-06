# Sparse semantic reconstruction audit — 2026-09-05

Five functions classified `semantic` in the cleanup working tree based on
`554cfff` were checked against the local IDA Hex-Rays export, IDA disassembly,
and raw Ghidra export. Three were selected because their implementation files
looked unusually small or explicitly admitted missing work; two were controls.
This is a deliberately suspicious sample, not a random estimate of repo quality.

The audit initially found no reconstruction bodies or ledger classifications
changed for these five entries. The follow-up implementation pass now records
the three recommended demotions explicitly in the source ledger.
The runtime was not compared against a fresh retail execution. Small C++ probes
compiled the actual reconstruction sources; expected results were derived from
the static references. Those probes and extracted IDA excerpts are available in
`/tmp/th10-sparse-audit/` for this session.

| Address / function | Verdict |
| --- | --- |
| `0x0040BD80` EndingScript_Update | Materially incorrect partial model; semantic credit is unjustified. |
| `0x004250B0` player_front::UpdatePlayer | Materially incomplete, with concrete input/control differences; semantic credit is unjustified. |
| `0x0044A5F0` input_final::Poll | Credible input-state tail, not reconstruction of the whole retail polling function. |
| `0x0042B9C0` ScorePopup_Enqueue | Credible reconstruction of the inspected valid-state behavior. |
| `0x00412AC0` Trajectory_Evaluate2D | Credible algorithm/control structure; x87 rounding fidelity remains unestablished. |

## EndingScript_Update: waits, timekeeping, and reload are wrong

[C++](../src/game/event_script_runtime.cpp), lines 15–77;
[IDA pseudocode](../../ida/th10.exe.c), lines 20110–20384;
[IDA disassembly](../../ida/th10.exe.asm), lines 15669–16195;
[Ghidra](../../decompiled/ghidra_raw/0040BD80_FUN_0040bd80.c).

- Retail opcode 5 initializes/decrements the wait timer and returns without
  advancing the command pointer when neither confirmation nor the permitted skip
  condition releases the wait. IDA lines 20217–20234, Ghidra lines 102–126, and
  assembly `loc_40BEFA` / `loc_40BF30` agree. C++ calls an optional void notification
  and unconditionally advances. The callback contract has no wait result. A
  60-frame wait followed by a color command at time zero immediately executes
  both in C++ (`cursor=2`, color `0x123456`); retail with no confirm/skip remains
  on the wait (`cursor=0`, original color). Opcode 6 has the same missing wait.
- The claimed faithful scaled time advance mixes incompatible units: normal-speed
  ticks add 1 to an integer `fraction`, while fractional-speed ticks add
  `int(speed*1000)` and divide by 1000. Ten normal ticks followed by speed 0.5
  produce time **0**. Retail's float accumulator yields **10** (elapsed 10.5).
  See IDA lines 20368–20383, Ghidra lines 261 onward, and assembly `loc_40C27C`
  / `loc_40C33A`.
- Retail opcode 12 calls `sub_40B480` to load the named next script, handles load
  failure, and installs that new stream. C++ clears state and starts the same
  vector again. A time-zero opcode 12 loops indefinitely in the probe; the
  one-second subprocess timeout fired. See IDA lines 20289–20310, assembly
  `loc_40C1B8`, and Ghidra `case 0xc`.

The existing [test](../tests/next10_large_recovery_test.cpp), line 19, explicitly
expects commands after a wait to execute in the same call. It validates the
simplification rather than retail behavior. The source even says `PARTIAL`, but
the annotation-driven ledger still promotes it to semantic.

Recommendation: partial; recover the timer and stream ownership before crediting
this as an ending-script implementation.

## UpdatePlayer: the API cannot represent the retail function

[C++](../src/game/player_front_runtime.cpp), lines 67–115;
[header](../include/th10/game/player_front_runtime.hpp);
[IDA pseudocode](../../ida/th10.exe.c), lines 36917–37309;
[IDA disassembly](../../ida/th10.exe.asm), lines 52140–52699;
[Ghidra](../../decompiled/ghidra_raw/004250B0_FUN_004250b0.c).

- For simultaneous opposing direction bits `0x30`, retail checks `0x20` before
  `0x10` after rejecting diagonals, yielding direction **2**. The C++ ternary
  prioritizes `0x10`, yielding **1**. The compiled probe confirms the C++ result.
  See IDA lines 36990 onward, assembly line 52191 (`test al,20h`), and Ghidra
  lines 52–70. Use the bit values here: the model's axis names are not a reliable
  mapping to retail input/position slots.
- Retail has four independent speed fields: normal cardinal `+0x3D4`, slow
  cardinal `+0x3D8`, normal diagonal `+0x3DC`, slow diagonal `+0x3E0`. The model
  accepts only `speed` and `slow`, using the same magnitude for cardinal and
  diagonal components. Assembly `loc_425319` versus `loc_425345` and the slow
  switch, plus both decompilers, establish the separate fields. A diagonal call
  with speed 400 gives components `(-400,-400)` regardless of the retail diagonal
  setting; no argument can express a different diagonal magnitude.
- The model updates `slow_age` for every enabled character/shot. Retail updates
  it in that branch only when `3*dword_474C68 + dword_474C6C == 5` (IDA lines
  37019 onward, Ghidra lines 80–90, assembly before `loc_4251B6`). That selection
  is absent from the model's API.
- The source admits missing orbit/trail handling and substitutes handle `1` for
  actual sprite allocation. Callback extraction alone would be fine; pretending
  the omitted state transitions are a complete function is not.

Recommendation: partial. Fix the model's data contract and branch behavior;
do not treat its handful of direction/clamp assertions as full-function evidence.

## Poll: a real tail behind a much narrower contract

[C++](../src/platform/final_input_runtime.cpp), line 11;
[IDA pseudocode](../../ida/th10.exe.c), lines 66357–66512;
[IDA disassembly](../../ida/th10.exe.asm), lines 109393–109736;
[Ghidra](../../decompiled/ghidra_raw/0044A5F0_FUN_0044a5f0.c).

The edge and repeat tail is grounded: previous/current publication, pressed and
released masks, 16 held counters, repeat threshold 26, and subtraction of 8 match
both decompilers and assembly `loc_44A8E0` onward. A 90-frame probe with holds,
release, and changed masks agreed with a reference transcription of that tail.

However, retail obtains keyboard state through two distinct paths, handles
DirectInput failures/reacquisition, uses fixed key combinations, applies gates,
and calls `sub_44A190` before publishing the state. C++ accepts injected arrays,
a generic one-key-per-bit mapping, and a precomputed joystick mask. That can be
a useful extracted helper; it does not establish the omitted polling behavior.

Recommendation: partial for address `0x0044A5F0`, or explicitly credit only an
input-state helper and separately recover/verify the actual acquisition adapter.
The one-line formatting is poor, but over-broad address credit is the substantive
problem.

## ScorePopup_Enqueue: a positive control

[C++](../src/game/score_popup.cpp);
[IDA pseudocode](../../ida/th10.exe.c), lines 42029–42086;
[IDA disassembly](../../ida/th10.exe.asm), lines 61502–61577;
[Ghidra](../../decompiled/ghidra_raw/0042B9C0_FUN_0042b9c0.c).

The 720-entry wrap, active flag, reverse decimal digits, zero case, single glyph
10 for negative values, color/position writes, lazy timer initialization, and
final timer reset agree across all three references. In particular, displaying
only a minus glyph for negatives looks suspicious but **is retail behavior**.
The probe checked zero, negative, positive, INT_MAX, and wrapping at 720.

The C++ adds a negative-index guard and returns the record through its explicit
API. Those are contract differences, not fabricated central behavior. This review
supports valid-state algorithmic reconstruction, not proof of raw ABI equivalence
or integration into the retail draw path.

Recommendation: retain semantic classification with that contract understood.

## Trajectory_Evaluate2D: credible, with a precision boundary

[C++](../src/game/trajectory_evaluate.cpp), lines 11–103;
[IDA pseudocode](../../ida/th10.exe.c), lines 22407–22571;
[IDA disassembly](../../ida/th10.exe.asm), lines 25302–25541;
[Ghidra](../../decompiled/ghidra_raw/00412AC0_FUN_00412ac0.c).

Modes 7/17, Hermite interpolation, easing delegation, duration completion, and
terminal-value selection have identifiable counterparts in both decompilers and
assembly. This is substantially more than a placeholder.

There is a precision difference worth investigating. At assembly line 25342,
`fst [esi+28h]` stores the rounded float but retains the x87 intermediate for the
following `__ftol2`. C++ updates its float `elapsed` and then converts that stored
float. With elapsed 1.5 and speed `nextafter(0.5f,0)`, retained extended arithmetic
truncates to **1**, while the rounded float converts to **2**. For duration 2,
mode 7, p0=10, velocity=2, the compiled C++ completes with output **10**; the
extended-precision instruction model remains active and produces **12**.

This is conditional on the active x87 precision. I did not measure the retail
control word in a live run, and single-precision operation may erase this example.
Hermite intermediate rounding also needs a deliberate numerical comparison.
Do not describe this probe as a captured retail gameplay divergence.

Recommendation: retain as a recognizable semantic algorithm, track numerical
fidelity separately, and verify the actual FP environment before patching it.

## What this says about progress

At least three of these five whole-function semantic credits are too broad. That
ratio cannot be extrapolated: the sample deliberately targeted suspicious files.
The recurring problem is partial models and tests of their own assumptions being
promoted by address comments.

A direct source-call search found EndingScript_Update, this UpdatePlayer model,
and input_final::Poll used by focused tests but no direct production callers for
those exact functions. Their mismatch establishes bad reconstruction credit, not
that the current standalone gameplay necessarily executes these particular models.
Trajectory_Evaluate2D does have production callers in `src/game/bullet.cpp`.

Prioritize demoting the three over-credited entries and adding retail-derived
counterexamples before rewriting bodies. Keep the grounded score-popup code;
blanket rejection of everything marked semantic would discard real work.

## Follow-up implementation evidence — 2026-09-05

The source ledger now classifies `0x0040BD80` (EndingScript_Update),
`0x004250B0` (player_front::UpdatePlayer), and `0x0044A5F0`
(input_final::Poll) as `partial`, with blockers recorded by
`tools/coverage_report.py`. The focused ending and player tests preserve their
recoverable slices while making the omitted contracts explicit.

The input slice also has a callback-backed acquisition helper and regression
coverage in [final_input_runtime_test.cpp](../tests/final_input_runtime_test.cpp).
Its fixed virtual-key and DirectInput scan-code masks are transcribed from the
IDA acquisition branches, including the gate, 256-byte device read, acquire
edge, keypad diagonals, and joystick-word publication. This is static retail
evidence; no live retail input capture was available, so the whole function
remains partial and the joystick/global-owner boundary remains open.

The focused evidence commands are:

```text
g++ -std=c++17 -Wall -Wextra -Werror -Iinclude \
  src/platform/final_input_runtime.cpp tests/final_input_runtime_test.cpp
g++ -std=c++17 -Wall -Wextra -Werror -Iinclude \
  src/game/event_script_runtime.cpp tests/ending_script_runtime_test.cpp
```

The generated `coverage.json`, `function_registry.json`, and
`standalone_readiness.json` were refreshed after the demotions. Readiness still
reports static startup/title closure only; it does not certify a fresh build,
smoke run, or retail-vs-reconstruction input trace.
