# Player manager task initialization at `0x004089C0`

> Integration status (2026-09-28): the exact routine or return correction described here is integrated and passes its maintained normal probe. The combined 487,936-byte executable matches retail byte for byte. See [the fifth checkpoint](native_recoveries_2026-09-28_fifth.md) for current proof. Scratch-only status and parent handoff instructions below describe the original investigation; unmatched and unselected context bodies add no recovered bytes.


2026-09-27. An isolated ordinary C++ candidate now matches the complete
211-byte retail function. Parent integration and the combined executable gate
remain separate steps; this note records the exact candidate evidence.

## Semantics and ABI

Fresh live Ghidra MCP `th10.exe` decompilation and disassembly confirm three
task allocations and registrations. The sole caller `0x00408C90` moves its
manager result from EAX into EBX at `0x00408CCA`, then calls this entry at
`0x00408CD8`. The initializer consumes the owner in EBX and returns zero in
EAX with a plain RET. The member declaration lets native LTCG infer that
private ABI from its compiler context.

The initializer registers callback `0x00409220` in the primary scheduler at
priority `0x16`, callback `0x00409230` in the secondary scheduler at priority
`0x0E`, and callback `0x00409270` in the secondary scheduler at priority
`0x25`. It clears physical callback flag `0x2`, assigns owner context at task
`+0x20`, and stores the resulting task pointers at owner `+8`, `+0x0C`, and
`+0x37AC`. The shared task declaration represents the physical flag through
its 31-bit `reserved_flags` field, so `reserved_flags &= ~1u` performs this
physical bit-two clear.

The embedded `FrameTimer` at owner `+0x3734` receives lazy defaults when its
flags lack bit one: previous `0xFFF0BDC1`, current/elapsed zero, speed pointer
`0x00476F78`, and flags with bit one set. It then always resets current and
elapsed to zero and previous to `-1`. Two compiler-only `_ReadWriteBarrier`
intrinsics retain the observed publication/default/reset store ordering;
they emit no machine instruction.

The owner declaration has a checked `0x37B0` size and checked callback/timer
offsets. It describes the suffix this function accesses without inventing
semantics for its reserved bytes. Callback entries retain their observed
ECX context contract. Ghidra has no Function object at `0x00409220`; a bounded
fresh memory read records its ten-byte `PUSH EDI; MOV EDI,ECX; CALL; POP EDI;
RET` thunk rather than inventing an analysis object.

## Native evidence

Scratch root:
`matching2/build/experiments/manager_tasks_004089c0_2026_09_27`.
Final project is its `msvc` directory. `probe_final.json` reports the whole
211-byte selected region exact. The final input file hashes and explicit
four-file promotion list are in `promotion_proposal.json`.

The synthetic array-walking receiver caller is compiler context, not recovered
game code. Its driver contains genuine full 131-byte primary and secondary
scheduler registration bodies. Both are unselected ABI anchors; independent
complete-body comparison in `anchor_comparison_final.json` reports exact for
each, as well as for the selected initializer.

Selected machine-code SHA-256:
`49945124b055b7e5be1379cdcc36a023efc4ab417381ee393b129b2a874be6cd`.

Selected C++ source SHA-256:
`f36717249e8ec1cf88977fcd52d92574e64864daf5d1de9e711f5f1252151209`.

The final native report records zero changed instruction bytes, zero changed
address operands, zero masked bytes, and `reference_bytes_used_for_build=false`.
All selected code is ordinary C++ without inline assembly, naked functions,
encoded instructions, or register-forcing hacks. Full callback pointer
immediates use absolute data bindings; scheduler calls use independently
compiled, exactly placed genuine bodies.

The first two attempts were build setup errors (VS2003 has no `intrin.h`,
then missing floating-point metadata). They yielded no byte comparison. The
first successfully generated native candidate (`attempt03.json`) was already
exact. Formatting and additional offset assertions were followed by the
independent final normal probe, which remained exact. The D3802 unmeasured
assembly-source comment is superseded by this evidence when parent promotion
is completed.
