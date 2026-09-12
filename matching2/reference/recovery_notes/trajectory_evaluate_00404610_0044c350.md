# Trajectory evaluator recovery attempt (0x00404610 / 0x0044C350)

Status: rejected after independent native-LTCG probes. Both live production
files were restored byte-for-byte to their pre-attempt inline-assembly bodies.
Neither target was promoted in `matching2/msvc/regions.json`; the existing
manifest entries remain `asm` at 887 bytes (`0x00404610`) and 576 bytes
(`0x0044C350`). The archived semantic sizes are 912 and 640 bytes,
respectively, so the legacy sizes are not the maintained live extents.

## Retail evidence and recovered behavior

The evidence set was `reference/legacy_semantic/src/game/trajectory_evaluate.cpp`
and its `include/th10/game/trajectory_evaluate.hpp`, together with the
augmented IDA/Ghidra listings and the live callers.

`0x00404610` operates on the 0x4c-byte movement record used by the event and
bullet paths:

| offset | semantic field |
| --- | --- |
| `+0x00` | start triple |
| `+0x0c` | target/velocity triple |
| `+0x18` | cubic control-A triple |
| `+0x24` | cubic control-B/increment triple |
| `+0x30` | previous frame |
| `+0x34` | current frame |
| `+0x38` | elapsed time |
| `+0x3c` | speed pointer |
| `+0x40` | timer flags |
| `+0x44` | duration |
| `+0x48` | mode |

For an armed duration it copies current to previous, advances elapsed by the
speed, and uses the retail x87 conversion helper at `0x00463B2C` for the
non-unit-speed integer frame. Near-unit speed increments both values by one.
Completion initializes the sentinel (`previous = -999999`, zero elapsed,
default speed `0x00476F78`, flag bit 0), publishes the terminal frame, and
disarms duration. Mode 7 integrates start by target; mode 17 integrates
control-B by target; mode 8 evaluates the cubic four-basis curve; all other
modes interpolate target-start through `0x0044C350`.

`0x0044C350` computes `t = elapsed / duration` in x87 and dispatches modes
1-6 (power/ease-in-out), 9-14 (the doubled-`t` half-curves), 15 (zero), and
16 (one), with the ratio as the default. The retail jump table is embedded at
`0x0044C550` inside the maintained 576-byte extent.

The live ABI is custom and was preserved in the task-local trial:

* `0x00404610`: state in EAX, output triple in EDI, output pointer returned in
  EAX, plain `RET`. This setup is visible in event-script callers around
  `0x004042C5`/`0x004042F4` and bullet callers around
  `0x0040DD7D`/`0x0040DE10`.
* `0x0044C350`: mode in EAX, elapsed at `[ESP+4]`, duration at `[ESP+8]`,
  x87 result in ST0, `RET 8`. The shape is used by the math/interpolator
  callers and by the fallback call from `0x00404915`.
* `0x00463B2C`: x87 ST0 to EAX integer conversion with the retail negative and
  extended-precision behavior; the trial bound it as `__ftol2` at the retail
  absolute address.

## Bounded native-LTCG results

A combined task-local cluster linked successfully and confirmed the shared
ABI context, but its contributions were 580 bytes for the evaluator, 648
bytes for the ease routine, and 182 bytes for the synthetic context. The
target-2 contribution consequently shifted before the independent probe; it
was not used as a promotion.

The independent evaluator cluster placed the candidate at `0x00404610` and
validated its complete 581-byte compiler contribution and 77-byte context.
The candidate body SHA-256 was
`ec0fdb545efed63e57162d93d6d7aa0c53f1173b1cd1763ee65d447d19daa229`.
Against the first 581 retail bytes (`cce8d6761100d9928c07902ee7666a48280ce8ccb3cf84b719463f01849967e1`),
the first mismatch was `0x00404612`: retail `44`, candidate `0c`, with 560
mismatches in the overlap. The closest compiler shape was still useful: it
did choose state EAX/output EDI and return EAX, and it used the retail
`0x00463B2C` call, but it emitted a 0x0c-byte frame instead of retail's
0x44-byte scratch frame and reordered the speed comparisons and x87 stores.

The independent ease cluster placed the candidate at `0x0044C350` with the
observed EAX/stack/x87 ABI, but strict validation rejected its complete
`.text$01ease` contribution at 648 bytes versus the declared live 576 bytes.
The candidate body SHA-256 was
`53ebb52979116ed09a9e6a475b8ed3fb4f637dfd8c4f13245792723964b1098a`; the
live 576-byte body SHA-256 was
`d7c59f0eece31d014aad2548683ef9f56c5daf64422eeaf3e247f33f6ab76797`.
The first mismatch was `0x0044C35E`: retail `e8`, candidate `30`. This is the
short-branch displacement to the default case; the longer native case bodies
also move the jump table and prevent an exact focused extent.

The semantic source was readable and behaviorally named, but these extent and
byte failures fail the promotion gate. The task-local layout header, compiler
contexts, and proposals were deleted after the probes; no shared tooling or
other source was edited.

## Next dependency

The next high-payoff dependency is an exact x87 spelling/context for the
shared pair: first preserve the `0x00463B2C` extended-value handoff while
forcing the evaluator's retail 0x44-byte scratch-frame/branch schedule, then
match the ease routine's native jump-table/case contribution (or retain that
table as a bounded local dependency). Reattempt the two-region cluster only
after each focused candidate again has its retail address, complete extent,
and bytes.
