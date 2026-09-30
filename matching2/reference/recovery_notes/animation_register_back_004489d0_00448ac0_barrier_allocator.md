# Back-list registrars: inner barrier reaches the retail ESI split, zero arm still folds

2026-09-27. Both complete 118-byte regions remain unmatched and unregistered.
No maintained source or manifest was changed. Fresh work uses the current
creator-twin clusters copied to
`matching2/build/experiments/register_back_lists/msvc`.

Fresh Ghidra MCP decompilation and disassembly responses for `th10.exe` are
retained in that experiment directory. They confirm the entity's embedded node
at **+4 in both leaves**, manager in EDX, entity in EBX, out slot in EAX, and
plain RET. Retail primary and secondary bodies differ at only four bytes:
the head/tail displacement low bytes at offsets 22, 32, 40, and 70. Secondary
head/tail offsets are primary offsets +8. The historical convention note's
secondary node +0x24 is contradicted by both live Ghidra and retail bytes.

## Fresh, gap-aligned native results

| Family | Candidate size | Different bytes | First difference | Existing creators |
| --- | ---: | ---: | --- | --- |
| Primary P | 118 | 40 | +0x1C | 73/73 and 95/95 exact |
| Secondary P | 118 | 40 | +0x1C | 73/73 and 95/95 exact |
| Primary inner-barrier | 121 | 28 | +0x5D | 73/73 and 95/95 exact |
| Secondary inner-barrier | 121 | 28 | +0x5D | 73/73 and 95/95 exact |

All comparisons cover the entire emitted contribution, include length
differences, and mask nothing. Final manifests use the actual measured
contribution extents and adjusted following zero gaps, so these creator checks
are at their retail addresses. Reports and exact measured byte strings are in
`summary.json` and each `final_*/measurement.json`; native build provenance is
in each `final_*/report.json`.

The P candidate reproduces the old wave-12/13/14 residual on the current
cluster. The new candidate is P with two instruction-free scheduling barriers:

```cpp
    manager_tail = node;
    _ReadWriteBarrier();
    int id = ++manager_counter;
    if (id == 0) {
        _ReadWriteBarrier();
        manager_counter = id + 1;
    }
    entity_id = manager_counter;
    out_id = manager_counter;
```

The source declares the intrinsic with `extern "C" void _ReadWriteBarrier();`
and `#pragma intrinsic(_ReadWriteBarrier)`. Actual candidates keep ordinary
alias-sensitive manager/entity/out accesses, preserving the two final reloads.

This changes the previously measured allocator result: the entire first 93
bytes match retail, including the shrink-wrapped EDI save/restore, common tail
store, ESI counter load/increment, ECX surviving copy, TEST, ESI counter store,
and POP ESI. The residual begins at the JNE displacement, followed by the zero
arm's folded ten-byte `mov counter,1` rather than retail's seven-byte
`inc ecx; mov counter,ecx`. The new arm is three bytes longer and shifts the
otherwise identical final reload/stamp sequence.

This **supersedes wave 14's claim that a split counter can never reach ESI**:
an inner zero-arm barrier does reach it. It does not yet recover the required
nonfolded zero arm. A barrier after the zero-arm store preserves its INC ECX
but returns to the EDI counter and entry PUSH EDI residual. A tail-store
barrier alone still leaves EDI, as wave 14 already established.

## Targeted probes and toolchain limits

The experiment completed 44 focused initial builds plus four final aligned
builds. Initial probes include Ghidra's old-value `old + 2` shape, barriers
before/after the counter store and zero arm, four-byte aggregate ID copies,
small skip-zero inline helpers using value/reference/store forms, and
equivalent unsigned equality/pointer-cast zero conditions. None is exact.
The inline helpers and aggregate copy with an inner barrier reproduce the
121-byte ESI/folded residual; a helper with its barrier after the store
reproduces the 118-byte EDI residual.

`_WriteBarrier` is accepted but retains the EDI residual. `_ReadBarrier` does
not resolve as an intrinsic in this MSVC 13.10 toolchain and fails the link.
Link-only `__restrict` aliases fail compilation with C4235: that keyword is
unsupported in this product. These failed probes are preserved, not silently
replaced with successful builds.

Scripts: `lab.py`, `inner_barriers.py`, `aggregates.py`,
`fold_boundary.py`, and `preserve.py`. Scratch candidates:
`final_primary_p118.cpp`, `final_secondary_p118.cpp`,
`final_primary_esi121.cpp`, and `final_secondary_esi121.cpp`.
No source, manifest, or encoded bytes from this experiment should be promoted
as recovered code until the full 118-byte region matches.
