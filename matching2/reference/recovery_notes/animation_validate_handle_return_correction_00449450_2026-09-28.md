# Animation handle lookup return correction — 0x00449450

> Integration status (2026-09-28): the exact routine or return correction described here is integrated and passes its maintained normal probe. The combined 487,936-byte executable matches retail byte for byte. See [the fifth checkpoint](native_recoveries_2026-09-28_fifth.md) for current proof. Scratch-only status and parent handoff instructions below describe the original investigation; unmatched and unselected context bodies add no recovered bytes.


Status: isolated correction ready for parent integration. Maintained inputs were not changed by this worker. This corrects an existing semantic prototype; the selected region remains 21 bytes, so it does not increase recovered-byte counts.

Fresh live Ghidra MCP disassembly of `th10.exe` proves that the helper returns its looked-up object in EAX. The existing `void` declaration omitted an observable return contract even though its compiled instructions preserved EAX. At `00449450`, the helper loads the handle ID through ESI, loads the global lookup context into EDX, pushes the ID, and calls `004491C0`. It tests the returned EAX, writes null to the handle only on lookup failure, and returns without changing EAX. Its effective ABI is handle in ESI, object/null result in EAX, no consumed stack argument, plain RET. Incoming ECX is unused.

The script executor supplies the handle pointer at `0040BE9C`, calls the helper at `0040BEA0`, then moves the returned EAX into ESI at `0040BEAC` before calling `00447A50`. That callee accesses the object at `[ESI+0x3A0]`. Ghidra's current decompiler prints a void prototype; the disassembly and consuming caller prove the omitted pointer return.

The corrected signature retains the original class and method names:

```cpp
void* __cdecl AnimationManager_00449450::ValidateHandle(
    AnimationHandle_00449450* handle);
```

The body saves `Find`'s pointer, clears the handle when that pointer is null, and returns the saved pointer. The explicit source calling convention reproduces retail's plain RET under native LTCG. The pointer-return thiscall and fastcall member variants emitted the same first 20 bytes followed by RET 4 (23 bytes total); these were rejected. The corrected cdecl member emits all 21 bytes exactly. The source receiver is unused; synthetic context details do not establish an ECX input requirement for the retail helper.

The cluster now includes the genuine complete 73-byte `004491C0` lookup body as an unselected ABI anchor. Both lookup buckets and the zero-ID return are ordinary C++ from the existing recovered body. This anchor independently matches all 73 retail bytes. The array-walking compiler context remains unselected and has a measured 46-byte contribution, replacing the previous 44-byte context extent.

Normal production probe `probe_final01.json` passed the entire existing selected family (one 21-byte region), with zero differing bytes and no failures. Native report records zero instruction-byte rewrites, zero masks, and no reference bytes used to build. Independent review passed source logic, actual ABI, anchor completeness, context exclusion, and all five input hashes. No inline assembly, naked functions, emitted opcodes, or encoded implementations occur in the correction.

Evidence directory: `matching2/build/experiments/recovery_script_executor_0040bd80_2026_09_28/validate_return_correction`.

- `ghidra_evidence.json`: five fresh disassembly/decompilation records, including helper, lookup, consuming executor, and object callee.
- `probe_final01.json`: normal selected-region proof and native build metadata.
- `anchor_comparison.json`: unmasked native-PE/oracle comparison of the helper and full lookup anchor.
- `promotion_delta.json`: five explicit files and SHA-256 hashes; parent alone may apply them.
- `independent_review.txt`: read-only independent review.

Selected helper machine SHA-256: `5b6ee5ed99e6f83450ec79b500044f04be0ab472cea9f6693699b0bc48b6347c`.

Lookup anchor machine SHA-256: `fc3dd480f30c27aa9dcf4168de57e19933d0125f22f6df88a09cc2d792ad69e9`.

The full readable, matching, assembly-free C++ objective remains active. Parent integration still requires a fresh maintained probe and the next full-image verification.
