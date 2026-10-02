# 0x0042A3E0 replay frame-step callback (parked again, 2026-10-02)

Retried in a native LTCG cluster (callback kept `__fastcall` through a stored
pointer). About 25 more shapes; none exact.

Retail layout: `... je RET; mov eax, 6; RET: ret; NULL: mov eax, 1; ret`. The
four failure branches (EAX already 1) share the `ret` after `mov eax, 6`; the
null-UI path owns the trailing `mov eax, 1; ret`.

- Any form whose last source `return 1` is the null path gives the right
  instructions but sends the failure branches to the trailing `ret`
  (function exit label sits after the last source return).
- An early `if (!ui) return 1;` puts the null block first instead of last.
- A `result` variable initialised before the flag test hoists `mov eax, 1`
  above the null test and keeps the UI pointer in EDX.
- An inlined `int`/`bool` helper for "UI missing or paused" materialises the
  flag value on the stack.

So retail needs the null block placed after the function's exit label, which
no source ordering tried produces.
