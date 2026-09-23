# Abnormal termination check at `0x00459946`

The 35-byte routine at `0x00459946..0x00459968` is now represented by a
readable C++ check of the current x86 exception registration record. The
source uses MSVC's `__readfsdword(0)` intrinsic to read `FS:[0]`; Microsoft
documents this intrinsic for x86 in [`<intrin.h>`](https://learn.microsoft.com/en-us/cpp/intrinsics/readfsbyte-readfsdword-readfsqword-readfsword?view=msvc-170).

## Ghidra evidence

Live Ghidra identifies `__abnormal_termination` as `int __cdecl(void)`, with
the body ending in a plain `RET` at `0x00459968`. It has one direct caller,
`FUN_0046332a`, at `0x0046338A`, and no callees.

The retail instructions clear EAX, load the registration record from
`FS:[0]`, compare the record's handler at `+4` with `0x004598BC`, then compare
the record's state at `+8` with the state at `+0xC` in the record's scope data.
EAX becomes one only when both comparisons match. The caller tests the result
and passes it to `___DestructExceptionObject`.

## Source and symbol integration

`abnormal_termination_00459946.cpp` expresses the same checks with named record
fields and the x86 FS-read intrinsic. Its canonical C-linkage symbol is
`_AbnormalTermination_00459946`; the old assembly reference
`_asm_abnormal_termination_00459946` is retained in the manifest symbol map and
routes to the semantic entry through a linker fallback. The manifest keeps
the former assembly row under `previous_record`.

The semantic classification describes the recovered behavior and caller ABI;
the compiler output and byte equivalence remain unverified. No build, probe,
or test was run.
