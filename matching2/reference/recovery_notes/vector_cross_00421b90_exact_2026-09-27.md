# Vector cross product, 0x00421B90

All 77 bytes are recovered as readable C++ in a native-LTCG cluster, with no
inline assembly, masking, instruction changes, or address-operand changes.
The normal probe compares the entire compiler contribution at its retail
address. This supersedes the earlier absence-of-caller ABI blocker.

The C++ function computes conventional `left x right` and returns its output
pointer. Native LTCG places that output in EAX, **formal left in EDX**, and
**formal right in ECX**. EAX still holds the output on return, with plain RET.
An intermediate three-float record preserves aliasing with either input.

Independent execution of the original retail bytes confirms the physical
mapping: ECX-vector x-axis and EDX-vector y-axis produce `(0,0,-1)`, because
the operation is EDX-vector cross ECX-vector. Reversing the inputs yields
`(0,0,1)`. A nontrivial pair and destination aliasing either input were also
checked. Disassembly of the synthetic caller establishes that its source
`left` pointer is supplied in EDX and `right` in ECX.

The earlier Ghidra reverse-cross interpretation used ECX-first parameter
labels and was correct for those labels. It is not evidence that FSUBP has
reversed arithmetic semantics. The C++ source uses ordinary operand names,
with the actual register mapping stated explicitly above.

The initial void-return model emitted 75 bytes and gave the output a different
register. Returning the output pointer establishes EAX and reproduces the
77-byte aggregate copy. Correctly matching formal versus physical operand
roles completes the exact body. No volatile fields or barriers are needed.

Artifacts:

- `src/math/vector3_cross.cpp`
- `layout/ltcg/vector_cross.json`
- `layout/ltcg/vector_cross_context.cpp`

Scratch proof is under `matching2/build/experiments/vector_cross/`: normal
probes, native disassembly, and independent Unicorn execution results plus
compiler-context register derivation under `review/`. The emulator and its
test scaffolding are verification artifacts only and supply no recovered
instructions. The synthetic context is also excluded from recovered code.

Whole-executable validation is recorded in the current recovery checkpoint.
