# Pentium FDIV probe at 0x0045DFFA

Ghidra identifies the 64-byte function as `__ms_p5_test_fdiv`, called by
`__ms_p5_mp_test_fdiv` at `0x0045E05E`. It has no arguments and returns an
integer. Retail loads binary64 constants `4195835.0` and `3145727.0`, stores
each in a stack local, computes

```text
residual = 4195835.0 - (4195835.0 / 3145727.0) * 3145727.0
```

and stores and reloads the residual before comparing it with `1.0`. It
returns `1` only when the residual is greater than `1.0`; equality, smaller
values, and unordered comparisons return `0`.

The maintained [C++ source](../semantic_candidates/ms_p5_test_fdiv_0045dffa.cpp)
reads the three retail constants and uses volatile binary64 locals to keep
the division at runtime. The manifest marks this region semantic and retains
the assembly record in `previous_record`. Source-level floating-point
evaluation order and x87 status flags still need comparison with retail.
No build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
