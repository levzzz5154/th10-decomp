# 2D polar vector setter at `0x00408750`

Ghidra identifies a 30-byte member-shaped leaf. The receiver is in ECX,
`angle` and `scale` are stack floats, and `ret 8` removes both arguments. The
routine stores `cos(angle) * scale` at receiver offset `0` and
`sin(angle) * scale` at offset `4`. Nine callsites use the same receiver and
argument layout.

The semantic candidate is
`PolarVector2_00408750::SetPolar(float, float)` in `src/game/score.cpp`. The
two-component layout and conventional member ABI follow the observed accesses
and caller setup. The retail function uses a single `FSINCOS`; the C++ calls to
`cosf` and `sinf` express the component values but do not establish the same
x87 instruction sequence or floating-point behavior. No byte comparison,
build, or probe has been performed for this candidate.

The bodies at `0x0041F800` and `0x004458B0` have the same 30-byte instruction
sequence. They remain separate assembly regions because they are distinct
addresses and may have separate original symbols or caller contexts. The
`asm_Score_SetPolarVector_00408750` alias is retained for existing assembly
callers.
