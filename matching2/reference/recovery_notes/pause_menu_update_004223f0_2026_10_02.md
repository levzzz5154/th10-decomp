# Pause menu update and scheduler callback

2026-10-02: `0x004223F0` and `0x00422A90` compile to their complete retail
contributions from ordinary C++ in
`src/game/fun_004223f0_004223f0.cpp`. The new schema-2 layout is
`layout/ltcg/pause_menu_update_004223f0.json`.

| Address | Complete contribution | Bytes | SHA-256 |
| --- | --- | ---: | --- |
| `0x004223F0` | `PauseMenuState_004223f0::Update` | 206 | `46dc68832271a4f8263c1b061a0f5a6ca27d9a36d4931daa1fb9891a8e744009` |
| `0x00422A90` | `PauseMenuUpdateCallback_00422a90` | 10 | `33986ac448aa0955cf29a90f71ee5ccd301e2f752cbe4e7d15f7acb57f3f804c` |

The first contribution includes the code, the compiler's alignment byte,
three jump-table addresses and the fourteen-byte case-index table. The
whole contribution was measured and compared; no suffix or table bytes are
supplied manually. The callback is the real registered scheduler boundary,
with the incoming context in ECX. Native LTCG derives the callee's ESI
receiver from its complete body and emits retail's ten-byte save/call/restore
adapter. There is no synthetic caller, inline assembly, volatile control,
barrier, foreign compiler, or tool change.

Ghidra's current `th10.exe` decompilation and call graph confirmed the phase
groups and that `InvokePairCallback` is the only direct caller. The existing
task installer also declares this callback with an integer result. Ghidra's
`undefined8` return comes from the incidental EDX values on the worker's exit
paths; ordinary integer returns naturally reproduce those instructions.

The timer fast path must add the literal `1.0f`, bound to its retail pooled
constant at `0x00470AFC`. Treating that address as a mutable external float
reversed the first `FLD`/`FADD` operands and differed in nine bytes. With the
literal, the entire worker and callback match. The remaining timer path adds
the speed to the elapsed value and converts the retained x87 result after its
binary32 store, as retail does.

The compiler gate was run on the maintained source and layout using the
unchanged default MSVC 13.10.6030 `/GL` and LINK 7.10.6030 `/LTCG` path. Both
entire compiler contributions were compared without masking to the stable
retail oracle. Retained evidence:

- `matching2/build/experiments/x87_menu_update_2026_10_02/maintained_verified/report.json`
- `matching2/build/experiments/x87_menu_update_2026_10_02/verified_bytes.json`
- `matching2/build/experiments/x87_menu_update_2026_10_02/integration_proposal.json`

The manifest is integrated. The incremental whole-executable gate passed
with 1,611 unchanged units reused and two compiled units: all 487,936 bytes
match retail. Executable SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The former callback source was removed after ownership moved to the shared
update source; its original symbol remains an address alias for existing callers.
