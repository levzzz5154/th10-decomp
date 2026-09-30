# Player reset animation-flag lifetime trial, 2026-09-28

**Unpromoted.** The complete `0x004246C0` constructor remains 244 bytes with
six register-operand differences; its maintained assembly body is unchanged.
The [frozen normal probes](../../build/experiments/player_reset_animation_lifetimes_2026_09_28/terminal_summary.json)
retain the three whole-body sources, native reports, original-address
comparisons, source hashes, and fresh Ghidra disassembly/decompilation/xrefs.

The receiver enters in ESI, the result leaves in EAX, and the body ends with
plain RET. The genuine factory at `0x00425020` calls it at `0x00425035`.
The source preserves all flag clears, the embedded and full-block clears,
and global publication. Its disjoint record layout was corroborated by the
complete pickup sweep in the earlier factory experiment.

Two new animation subobject representations were tested against the same
complete 244-byte original gate: a class method accepting each already loaded
flag, and a class method reading and clearing its own flag. Both compile to the
identical `f29b5210…` body as the disjoint direct-store baseline. All three
have 238 equal bytes and six differences at `0x0042473F`, `0x0042474B`,
`0x0042474D`, `0x00424766`, `0x00424771`, and `0x00424773`.
Retail uses EDI for the first animation flag and EDX for the third, whereas
native MSVC chooses ECX for both. The second ECX flag and fourth direct-memory
AND match. All three probes report zero instruction or address-operand
rewrites; no bytes were masked or supplied to the compiler from the oracle.

Changing the inlined method identity does not alter these register choices.
The remaining structural lead is a complete genuine initializer/call graph or
an independently grounded animation lifetime boundary. This trial adds zero
new C++ recovered bytes.
