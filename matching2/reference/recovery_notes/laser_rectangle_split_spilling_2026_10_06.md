# Rectangle splitter — byte spilling and faithful counter controls

This continuation made diagnostic progress after the earlier constant-extraction trace. It establishes why the byte mask tests recover immediate zeros while the dword hit-count test keeps a register. Five faithful local-record forms and a complete-family CPU-option control supply no improved candidate. **Zero production bytes were recovered**; the full requested C++ decompilation remains active and incomplete.

## Spill mechanism, observed without compiler writes

[`trace_target_spill_link.py`](../compiler_traces/flowgraph/trace_target_spill_link.py) replays the ordinary current rectangle-splitter `/LTCG` command with four hardware breakpoints: `CmdSpillImmedBytes`, its shared return tail, `GrgChangeRegToImmed`, and `Riscify`. The return-tail observation is accepted only when its stack matches a captured spill entry. Calls to the replacement helper capture the real constant symbol, use tuple, operand kind and operand type. Full tuple snapshots are retained at spill entry/exit and `Riscify`; replacement calls retain their small argument records.

The current run completes normally with 22 events. All **4096 emitted native code bytes**, including the full **1171-byte** selected splitter, equal the unobserved baseline. Its native-body SHA-256 remains `c676de1bc5131cbc175f209b80af257121e3432fc943e3b3b08b1fd3b2a7419e`. No compiler data, emitted instructions or allocation decisions are changed. The normal candidate is still 27 differing bytes from retail: 13 in the prologue and 14 around the hit test/cursor initialization.

The first observed byte-spill invocation rewrites four mask comparisons against the shared zero through `GrgChangeRegToImmed`. All four source operands have compiler type 1 and are comparisons with opcode `2F`. The hit-count comparison has type 4 for both sources and remains the same before and after that invocation. It is absent from every captured immediate-replacement call. Its constant lifetime therefore survives this byte-only step; the preceding allocation trace establishes that the later split range receives EAX. This explains the current difference between mask-byte tests and the dword hit test. It does not prove the original source or an unavoidable compiler limitation.

The compiler DLL was imported into Ghidra as `/compiler_reference/c2.dll`. A Function object was created at the PDB-verified `CmdSpillImmedBytes` entry, and its callee was discovered during disassembly. No game Function object or prototype was changed. The compiler-reference disassembly independently shows the operand-type mask `0FFF` and comparison with 1. Ghidra's inferred signatures are not authoritative private-ABI descriptions; live argument/operand records supply that evidence. The compiler file retains its established SHA-256.

## Five local records, no additional state

Each control contains only values already present in the retained algorithm. The [recipe and source snapshots](../semantic_candidates/laser_rectangle_cut_0041eb00/evidence/spill_followup/) preserve their complete function bodies and use the non-overlapping diagnostic image base `00100000`.

| Existing sampling state grouped in one record | Native extent | Differing overlap bytes | Groups |
| --- | ---: | ---: | ---: |
| Two counters, separate zero assignments | 1171 | 72 | 33 |
| Two counters, reversed field declaration order | 1171 | 72 | 33 |
| Two counters, aggregate zero initializer | 1171 | 72 | 33 |
| Two counters and the existing volatile progress | 1180 | 318 | 63 |
| Existing 256-byte mask and two counters | 1170 | 1102 | 71 |

These are rejected measurement controls, not behavioral or normal-gate proofs. They do not improve the 27-byte retained residue. In particular, a matching extent in the first three rows does not establish equality.

## Complete-family `/G5` control

Replacing `/G6` with `/G5` in **all thirteen actual source translation units** leaves all sixteen address-bound emitted function bodies byte-identical to the retained family graph. This is distinct from the earlier target-only option test. A syntax-only compiler replay succeeds without an unsupported-option warning. The full commands, per-function hashes and [reproducer](../semantic_candidates/laser_rectangle_cut_0041eb00/evidence/spill_followup/family_g5_control.py) are preserved. No CPU-option change is proposed for production.

## Reproduce and continue

Run from the repository root after rebuilding the retained individual candidate:

```sh
python3 matching2/reference/compiler_traces/flowgraph/trace_target_spill_link.py matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current/commands.json matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current_spill_trace CutRectangle
python3 matching2/reference/compiler_traces/verify_target_trace.py matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current_spill_trace matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/layout.json matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current_spill_trace/proof.json
python3 matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/evidence/spill_followup/rectangle_counter_controls.py
```

The next useful source investigation is the genuine upstream type/graph and constant lifetimes leading to the retained dword range. Repeating these record forms, byte spilling, late scheduling or `/G5` supplies no new answer. The current source/receipt and whole executable were revalidated; production source, flags, ownership and verification rules remain unchanged. Exact ordinary C++ remains 2254 regions / 199062 bytes, with 60 actual assembly regions / 89245 bytes remaining.
