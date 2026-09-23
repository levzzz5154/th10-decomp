# Queued animation cleanup, 0x00421070

## Decision

Ghidra provides a complete semantic model for `0x00421070`, and the retail
entry can be represented by an ordinary x86 C++ `__stdcall` function taking
the queued state pointer. The live source candidate is
`matching2/msvc/src/render/queued_anm_cleanup.cpp`.

The decompiler labels the entry `__thiscall` with an ECX receiver and one
stack parameter. The caller disassembly gives the stronger machine-level
contract: `0x00417870` pushes `0x00491c28`, calls `0x00421070` at `0x00417c2b`,
and does not adjust ESP afterward. The callee ends in `ret 4`. ECX is not read
for a decision or memory access by `0x00421070`; the decompiler's phantom
`extraout_ECX` values arise from forwarding that register to the lookup.

The three lookup calls at `0x0042109b`, `0x004210d9`, and `0x00421119` load
their identifier from the stack and the animation context into EDX. At
`0x004491c0`, disassembly shows the stack identifier reloaded into ECX and
then used for comparison, while EDX supplies the context buckets. The
incoming ECX receiver is not used. Its recovered C++ entry is already declared
as `AnimationManager::Find(AnimationLookupContext*, AnimationScriptId)` with
the x86 `__fastcall` split: receiver in ECX, context in EDX, and the four-byte
identifier aggregate on the stack. The candidate calls this typed entry with a
local empty receiver; changing that unused receiver does not affect the
lookup result.

## Recovered behavior

When the state word at `+0x6FC` is exactly 1, the routine looks up the three
pending identifiers at `0x00477824`, `0x00477828`, and `0x0047782C` using the
context pointer stored at `0x00491C10`. For every found animation it writes
the 16-bit value 1 at `+0x304`. If the animation's dword at `+0x18` is zero, it
walks the child links beginning at `+0x14` and writes the same value to each
linked object at `+0x304`. It then clears all three pending identifiers and
the state word at `+0x6FC`. Regardless of that state-word test, it clears the
dword at `0x00491BEC` when nonzero.

The focused Ghidra evidence used for this decision was:

- `decompile_function(0x00421070)` and `disassemble_function(0x00421070)`;
- callers and complete-function analysis for `0x00421070`, identifying its
  sole caller `0x00417870` and its sole callee `0x004491C0`;
- decompilation and disassembly of `0x004491C0`, confirming its key/context
  inputs and that its incoming ECX receiver is ignored;
- decompilation and the call-site disassembly in `0x00417870`, confirming the
  pushed state address and caller-side stack cleanup behavior.

## Limits and integration

This establishes the source behavior and a representable call contract; it
does not establish byte equivalence. The candidate has not been rebuilt or
compared with retail bytes. C++ loop lowering, helper inlining, register
allocation, section placement, and the new stdcall symbol decoration can all
change emitted bytes. The manifest now binds the semantic row to the stdcall
symbol and retains the prior assembly alias for its naked caller. The alias's
legacy C++ declaration remains only for that inline-assembly edge; future C++
calls should use the typed entry. No build, probe, or test was run for this
review.
