# Signed field comparison at `0x00413050`

The manifest assigns a 17-byte span (`0x00413050` through `0x00413060`,
inclusive) to this fragment. Its instruction sequence loads the signed dword
at receiver offset `+0x04`, loads one dword from `[esp+4]`, compares the field
against that argument, sets `AL` for signed-less-than, and returns with `ret 4`.
The observed result is therefore `this->value_004 < rhs`, returned as a
zero-or-one boolean. The ordinary C++ candidate in
`src/unidentified/unassigned_00413050.cpp` models this as a member function:
the receiver arrives in `ECX`, the integer operand is stack-passed, and the
callee removes that operand. `int` preserves the signed comparison indicated
by `setl`; the neutral struct and field names do not assert a recovered class
identity or domain meaning.

This is semantic recovery, not an exact byte-reconstruction claim. The earlier
extern-C `cdecl` and `stdcall` spellings recorded in the source's M2701 history
were near-matches (19- and 21-byte extents, respectively, each first differing
at `0x00413051`). The wave-18 comparison note likewise records that the old
ordinary spellings loaded the receiver field into `ECX` where retail uses
`EDX` ([`0041xxxx_wave18.md`](0041xxxx_wave18.md)). The new member-style source
captures the observed conventional ABI and signed semantics; no emitted-byte
match has been measured for it.

The parent review reported that Ghidra has no function defined at this address
and no xrefs/callers. Accordingly, the 17-byte manifest span is not presented
here as an independently established function boundary, and caller identity
or call-site ABI evidence remains unavailable. The maintained region binding
and aliases are unchanged by this candidate.

No build, probe, or test was run.
