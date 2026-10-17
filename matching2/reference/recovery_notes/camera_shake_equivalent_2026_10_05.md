# Linear camera shake C++ equivalence recovery, 2026-10-05

The complete 439-byte callback at `0x0043C550` is now an equivalent recovery
using `equivalent/platform/camera_shake_0043c550.cpp`. The default build uses
its compiled C++; `make EXACT=1` retains the byte-exact assembly owner.

This uses the complete controller/timer model and RNG storage model from
`camera_shake_0043c550_genuine_graph_2026_10_02.md`. Each axis discards one RNG
advance and duplicates the second word into both halves before reducing it
modulo 3. The model preserves the high seed-storage word and generation count.
The same callback code is reproduced with a compiler-only escaping callback
pointer as the root, without copying the large selector/scheduler graph. The
callback pointer preserves the genuine public ECX argument boundary; it and
its wrapper are not part of the game output.

The existing equivalence gate reports 134 instructions, with only FIDIV
scheduled differently. The manifest records its insertion at `+0xB6` and
removal at `+0xCE` as two exact `evaluation-order` entries. Between these
positions retail executes only:

```text
xor eax,0x9630
sub eax,0x6553
mov cx,ax
shr cx,0xe
lea edx,[eax*4]
```

These instructions read/write only EAX, ECX, EDX and integer arithmetic flags.
FIDIV reads the unchanged divisor at `[esp+8]`, operates on x87 ST(0), and
does not read/write those general registers or integer flags. No intervening
instruction writes memory, changes ESP, calls, branches, or uses x87 state.
Both schedules therefore reach the next instruction with identical live
integer and x87 values and the same memory; neither introduces an extra
rounding/store step. As with native compiler scheduling, this comparison is
of normal execution, not debugger snapshots during an unmasked arithmetic
exception.

Everything else, including branch destinations, instruction encodings,
addresses, and the 439-byte extent, is checked without another allowance.
The equivalence tool and compiler flags are unchanged. The focused production
equivalence probe passes; full gates are run with the surrounding recovery
batch.

## 2026-10-17: the fidiv position sweep, still parked

The queue's "inlined RNG ordered differently around a fidiv" was re-attacked
with the x87 and scheduler levers. Everything tried leaves the model at 133 of
134 with the same two `evaluation-order` hunks (the FIDIV at +0xB6 where
retail has it at +0xCE):

- the 0x004452F0 conversion shape on either operand (`(float)delta` as a
  named local, the product split into named locals, both conversions named):
  each moves the fidiv earlier and adds the `fld`/`fadd` operand-order hunk at
  +0x48 (130-131 of 134); naming the divisor conversion replaces the `fidiv`
  by `fild`/`fdivp` outright (124 of 134);
- the +-one-temp-class shapes near the amount statement (a named `elapsed`
  local, a second `limit` local, a named dropped RNG advance): unchanged;
- moving the discarded `ShakeRandom()` advance before the amount computation
  (RNG order preserved, the amount is RNG-free): shifts the whole register
  assignment to EDI (119 of 134).

The residual is the list scheduler's per-cycle pick between the x87 FIDIV and
the integer RNG chain (`msvc-c2-list-scheduler-priority`: priority = path +
successors + 32-if-load, ties by sequence number). Closing it needs the
scheduler trace (`compiler_traces/scheduler/`) to compute which priority must
change by one and which dependency edge produces it. Region stays equivalent.
