# D3D resource list initialization leaf, 0x00449A50 (32 bytes)

Status: measured native-LTCG candidate; **not integrated**. The maintained region remains assembly. No instruction rewriting, reference-byte construction, contribution truncation, or inline assembly was used in the candidate.

Fresh Ghidra MCP `read_memory` evidence covers exactly 32 bytes at 0x00449A50 (`matching2/build/experiments/d3d_init_leaf/ghidra_read_memory.json`). Ghidra has no Function object at this head. Retail enters with the list in EAX and returns with plain RET. It loads flags +4 into EDX, zeros ECX, clears +8/+C/+10/+0, masks flags with ~1, stores flags +4, stores the list pointer +14, and clears +18/+1C.

The synthetic array-walking caller reproduces EAX and the exact 32-byte complete contribution. The straightforward field model uses the correct EDX flags and ECX zero, but schedules AND before the four initial zero stores: 9 differing bytes (`probe_plain2.json`). A `_ReadWriteBarrier` after the +0 store gives the exact retail instruction order and complete extent, but flags and zero are allocated to ECX and EDX respectively: **10 differing bytes**, first difference 0x00449A51 (`probe_final_ordered.json`).

Scratch artifacts are under `matching2/build/experiments/d3d_init_leaf/`: `msvc/` holds the final ordered candidate, layout and driver; `best_ordered_source.cpp` and `best_plain_source.cpp` retain both shapes. The final ordered probe contains no failures, but correctly reports `exact: false`.

Targeted variants did not solve the final permutation: return-zero, repeated-call, postincrement and indexed array contexts; barriers after the flags load, each pending store, flags store, owner store and final store; signed or pointer field types. Volatile pending stores reduced the reordering difference to 8 bytes but did not restore the full instruction order. Disabling global optimization enlarged the contribution to 102 bytes. `_ReadBarrier` is not recognized as a native intrinsic by MSVC 13.10 and leaves an unresolved external; it is rejected rather than bound to any synthetic code.

The adjacent two-list initializer at 0x00449AA0 was recovered independently; its register allocation does not prove this leaf exact. A future useful lever must change the single-list scratch-register allocation while retaining the EAX entry and ordered stores. None of these candidates should be promoted without a new complete exact probe.
