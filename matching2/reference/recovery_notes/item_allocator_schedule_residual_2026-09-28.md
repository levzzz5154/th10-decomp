# Full item allocator and all-segment schedule residual, 2026-09-28

This bounded continuation owns only
`matching2/build/experiments/item_allocator_schedule_2026_09_28` and this new note.
Maintained inputs and prior experiments were preserved. It starts from the actual
final823-byte allocator /601-byte all-segment models and the now maintained exact
623-byte bounded sweep, not the older827 or private-kind815 branches.

Fresh Ghidra instance/program records confirm `th10.exe` in project `th10` at
`/run/user/1000/ghidra-mcp/ghidra-2136235.sock`. Fresh full allocator, E260 and item
polar disassemblies are retained in `ghidra_*.json`. `baseline02` independently
revalidates823/601/623 and the previous full body hashes.

## Terminal whole-original normal result

The canonical inputs are frozen in `terminal_inputs/`, with
`terminal_input_hashes.json` and `terminal_summary.json`. `combined02.json` is the
ordinary native probe for **both full original819/609 contributions**. It reaches
byte comparison with no compiler/extent failures and rejects both; no new routine
is promotable. The original source owners remain `src/game/item_spawn.cpp` and
`src/game/line_effect_sweep.cpp` (see explicit ownership records in the summary).
The probe's displayed per-unit source is the primary item source for its joint
output; the manifest/layout ownership itself is preserved.

| Original contribution | Complete native | Differences | First difference |
|---|---:|---:|---|
| 0041BB00 allocator819 | 819 | 736 | 0041BB0E |
| 0041E260 all segments609 | 609 | 33 | 0041E2F4 |
| retained 0041F400 bounded623 anchor | 623 | 0 | none |

`combined02_measurement.json` reads the entire actual native CODE contributions;
`combined02_complete/` retains raw native/retail bodies and disassemblies. Normal
normalization records instruction changes0, address changes0, masked bytes0 and
`reference_bytes_used_for_build=false`. The sole allocator original819 normal
byte gate is also retained at `independent_allocator/probe02.json` (736 genuine
byte differences, no compiler failures).

Terminal native body SHA256 values:

- allocator819: `6393e9877e1387e611de9fd74e1e64491346bc64f4bc5c9cb8b52a08faee4d59`
- E260609: `cd82b3e9b655bb7c14e81b9cd8d4f581f6ce263d08097424cc0673df7974b52a`
- unchanged F400623: `f064ada0633637ffbd6631367e900d6d1415569100052bf52bae824735db874f`

## Grounded allocator representations

Three full representations were measured, preserving allocation search, full-pool
return, remapping, timers, signed cursor/remainder arithmetic, all vector writes
and animation calls.

1. A conventional bounded for-loop unrolled six entries and changed position to a
   stack argument. Its complete contribution is927 bytes, and it was rejected.
2. An explicit free-slot exit with exhausted-pool return and direct mutation of
   the original kind value produces the full819-byte body. Its initial incoming
   kind load into EBP now matches retail. Manager is still saved in EDI instead
   of ESI at41BB0D, and the compiler peels the first allocation-state test.
3. A complete aggregate Vector3 copy produces the retail three-word copy sequence
   and postpones clamping until after all three copies. It totals815 bytes,
   with702 overlap differences. Its complete source and diagnostic are retained;
   it is not selected or truncated to match819.

The established EAX manager / ECX position / four stack arguments / RET16 call
agreement remains intact in the terminal819/609/623 models. A remaining ABI-context
lead is concrete: retail's special-item pointer stays in EDX across41BEB0 and its
following timer stores. The genuine retail polar leaf preserves EDX; the current
lawful opaque public declaration gives the compiler a conservative volatile-EDX
summary. A future complete co-visible polar context must preserve that fact while
also retaining the genuine stack-kind agreement. It cannot be replaced with a
register stub or an exact-rounding claim about FCOS/FSIN versus FSINCOS.

## Grounded E260 representations and remaining scheduling

`e260_work/README.md` retains the child’s three complete models and its independent
whole609 normal gate. A full force-inline registrar with a real local output
shortened to598 and was rejected. The actual float-position subrecord view fixes
all animation/position/inline node-registry bytes through41E3A7, leaving601 bytes.
Writing the zero-counter correction as `next_handle = handle + 1` restores the
missing8 bytes and reaches the whole609 byte gate with35 differences. Transferring
F400's proven local volatile point-Z reference restores the final two Z operand
bytes, yielding the terminal33 differences.

Exactly two residual blocks remain in the full609 body:

- 19 bytes at41E2F4..41E313: count load/store ordering relative to script load/index.
- 14 bytes at41E3A2..41E3B8: the counter load hoists ahead of the tail store and uses
 EDX instead of retail ECX.

The next genuine source levers are incrementing the segment count before the
script/resource work and a plain integer view of the actual counter subrecord,
formed after assigning the tail. These have not been swept here. Entire original
819/609 byte gates and full genuine dependencies remain required.

The exact F400 source and raw body remain unchanged in the canonical joint native
context. Its complete623 body and the complete line polar30, Configure204,
loader203, registrar114, positioned-create111, Allocate165 and compiler-context66
contributions remain visible and have their actual emitted extents declared.
The line polar FCOS/FSIN body is unselected ABI context only; the retail FSINCOS
polar bodies remain assembly in the maintained manifest.
