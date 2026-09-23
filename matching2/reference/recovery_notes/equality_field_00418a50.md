# Equality leaf at `0x00418A50`

The 17-byte leaf loads the dword at receiver offset `+0x04`, loads its one
stack argument, compares them, returns the equality result in `AL`, and uses
`ret 4`. This supports a private `__thiscall`-style member operation that
compares a receiver field with a 32-bit value. Neither the field's domain nor
the class identity is established, so the maintained model uses neutral names
and `unsigned int` only to represent the observed 32-bit comparison.

`src/unidentified/unassigned_00418a50.cpp` now expresses that operation as
`EqualityReceiver_00418A50::MatchesValue`. The earlier five ordinary member
spellings are documented in the source and wave-18 notes as near misses: the
closest output was 14/17 bytes, with the first difference being the register
chosen for loading the receiver field. A native-LTCG anchor/context was
considered, but no caller or neighboring anchor that constrains this isolated
leaf's `EDX`/`ECX` allocation is known. Adding a synthetic caller alone would
not establish that register assignment, so no speculative layout was added.

This is a semantic candidate, not an exact-reconstruction claim. No build,
probe, or test was run. Ghidra did not have a function defined at this address
in the parent review, so this recovery adds no Ghidra annotations.
