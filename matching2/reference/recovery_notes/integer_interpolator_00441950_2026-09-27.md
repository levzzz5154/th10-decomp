# Integer interpolator `0x00441950`: 367-byte native model

2026-09-27. The complete retail region remains **370 bytes** and is still
assembly in the maintained project. The strongest readable model from this
bounded pass contributes **367 bytes** with the correct private ESI receiver,
integer EAX result, plain RET, and 8-byte local frame. It is not exact and must
not be promoted. No maintained source or manifest was changed.

The current candidate, native layout/context, and genuine easing compiler
anchor are retained below
`matching2/build/experiments/integer_interpolator/msvc/`. Its source is
`src/math/fun_00441950_00441950.cpp`; its manifest still requires 370 bytes.
The final normal focused probe correctly rejects the shorter complete
function contribution instead of selecting padding or reducing the target.

## Established layout and behavior

The object has integer value/target/control/velocity fields at `+0/+4/+8/+C`,
followed by the existing five-word `FrameTimer` at `+0x10`: previous/current
frames, float elapsed time, speed pointer, and flags. Duration is `+0x24`;
mode is `+0x28`. The output is the returned integer, not a general writeback
to the value field. Mode 7 adds the target/step to the value; mode 17 adds
velocity to the value and then target/acceleration to velocity. Those modes
write their corresponding state fields. Mode 8 returns a truncated cubic
Hermite result. Other modes return a truncated eased blend between the value
and target. Completion clamps the timer, clears duration, and returns value
for mode 7 or target otherwise.

Live Ghidra MCP evidence is retained as `ghidra_decompilation.txt` and
`ghidra_disassembly.txt` below the experiment. Animation VM callers load ESI
with their embedded interpolator (`VM+0x108` or `VM+0x208`), call this entry,
and use returned AL for alpha.

## Resolved source/compiler questions

The deleted previous candidates were 390/399 bytes with unwanted preserved
registers. A contiguous-array native caller in this pass already selects the
required ESI receiver. A separate `__forceinline` timer helper is essential:
manual flat timer code kept duration in EDI, requiring a save/restore. The
helper restores the retail duration reload and removes EDI completely.

The timer compares `*speed` directly twice, then loads `float step=*speed`
inside the fractional branch. Its source uses
`current = int(elapsed = (double)step + elapsed)`. This reproduces the
retail repeated FLD/FCOMP sequence and FST-before-`__ftol2`, preserving the
wide x87 sum while storing binary32 elapsed time. An eager speed local kept
ST0 live through the comparisons and emitted a different sequence.

A separate inline timer-set helper restores the retail order of current,
previous, elapsed, mode, and duration stores. Ordinary float Hermite locals
produce the retail single-precision constant operands at `0x00470AFC` and
`0x00470BD4`; double locals instead generated 64-bit constants. Grouping each
integer coefficient with its float weight restores FIMUL and the expected
x87 stack depth. Removing an unnecessary double cast from the default blend
also restores the retail FIMUL followed by FIADD and tail `__ftol2` jump.

## Easing dependency and ABI are proven

An ordinary external declaration cannot express the easing selector in EAX
or promise ECX preservation, which this caller requires. The compiler-only
anchor is copied from the genuine maintained `EvaluateCurve_0044c350` C++
body, with only its function name and section changed. Native LTCG places
it at `0x0044C350`, passes the selector in EAX and the two float arguments
on the stack, returns ST0 with RET 8, and retains the interpolation start
in ECX across the call.

The final native anchor's **complete 576 bytes** were compared independently
with retail and match. Its SHA-256 is
`d7c59f0eece31d014aad2548683ef9f56c5daf64422eeaf3e247f33f6ab76797`.
This anchor is context only and is not exported as recovered game code.
Its input copy is
`layout/ltcg/integer_interpolator_00441950_easing_context.cpp` below the scratch
project. The selected candidate contains calls only to that correct retail
address and the already semantic `__ftol2` at `0x00463B2C`.

## Remaining differences

1. Retail stores duration to `[ESP]` at `0x004419B0`, then repeats the same
   three-byte `mov [esp],ecx` at `0x004419BA` after testing the initialization
   flag. The model eliminates the second write. This accounts for the full
   three-byte extent deficit and shifts all subsequent block addresses.
2. The model's Hermite schedule evaluates the control term before velocity;
   retail evaluates velocity before control. The grouped float model otherwise
   uses the expected coefficient operations, x87 stack cleanup, and calls.

The first differing byte is `+0x0D`, an earlier branch displacement caused
by the missing later spill. The overlapping 367 bytes contain 257 differing
bytes after those shifts; that count is not a semantic-equivalence score.
The genuine target stays 370 bytes, and no masking, instruction rewriting,
binary padding in the selected contribution, or artificial byte emission was
used.

A last narrow check wrote through a volatile view of the existing local
limit only at the clamp. It preserved a duplicate write but emitted **371
bytes**, changed duration allocation to EAX, moved the write before the flag
load, and forced a post-initialization `[ESP]` reload. The frame remained 8
bytes. That diagnostic is retained as `volatile_limit_source.cpp`,
`volatile_limit_body.bin`, `.dis`, and `volatile_limit_result.json`; it was
not retained as the final candidate.

## Retained tests and final artifacts

- `variants.json`: five timer/type/grouping variants; 365, 369, 372, and 388
  byte contributions. Separate inline timer code is the effective new lever.
- `set_variants.json`: four timer-set/default-blend variants; removing the
  double blend cast reaches 367 bytes with the expected default instructions.
- `last_variants.json`: nested initialization, separate polynomial terms,
  grouped addition, and long frame-parameter spelling. All remain 367 bytes;
  none restores the redundant spill or the retail Hermite schedule.
- `final_probe.json`: a fresh focused probe using the unchanged 370-byte
  region and current 367-byte candidate; it correctly reports NOT EXACT.
- `final_body.bin` and `final_body.dis`: the complete current native function
  at `0x00441950` with real dependency addresses.
- `measured_residual.json`: complete contribution size, byte differences,
  source/body hashes, 576-byte anchor comparison, and absence of rewriting.

Final candidate source SHA-256:
`873aa89093d4c8dd93166a6021259f80bd57fd87378114ec339935199f769405`.
Final 367-byte native body SHA-256:
`878978e3138255425f7d88fccffc3fe80161eb29dbe4c1eae318ae365e0b7982`.
The next targeted lever must preserve the specific second spill without
changing the frame or ordinary register reads, and obtain the velocity-first
Hermite term order. Repeating the same context/type/grouping variants is not
justified by these measurements.
