# Exact input-mask reader and stage-loader adapter

Two complete retail functions were recovered as readable C++ without inline
assembly. Both production probes and both full builds pass. `make EXACT=1`
produces the byte-identical 487,936-byte retail executable; the normal build
remains exact outside the three preexisting equivalent C++ regions.

## Input-mask flag reader, 0x0044A160, 43 bytes

`src/input/indexed_flags.cpp` now also owns `ReadSignedMaskFlag`. A negative
signed 16-bit index returns zero. Otherwise the function tests the corresponding
bit of its by-value mask, ORs the selected 16-bit flag (or zero) into the output,
and returns the selected flag or zero. Unlike the adjacent byte-table reader,
the mask does not need rereading after the output write: it is a value argument.

The native entry is index in CX, output pointer in EDX, selected flag in SI,
and the source mask on the stack; RET 4. Extending the existing indexed-reader
array context preserves the complete 37-byte byte reader and supplies exactly
this convention to the mask reader. The unselected context grows from 72 to
87 bytes, and its entire native contribution is declared in the layout.

The source shift deliberately follows the pinned MSVC 13 x86 lowering. The
emitted SHL CL masks the count to five bits, including nonnegative mapped
indices greater than 31. This is target/compiler-specific behavior, not a
portable C++ promise for an out-of-range shift. Explicitly writing `index & 31`
emitted an additional three-byte AND instruction and failed the full extent
gate (46 instead of 43 bytes). The retained source reproduces the complete
retail behavior through its exact native instructions.

Ghidra's live decompilation confirms the negative-index check, by-value mask,
output OR and selected-bit result. The old naked owner
`src/unidentified/unassigned_0044a160.cpp` was deleted and its manifest record
retained as previous-record metadata.

## Stage ECL result adapter, 0x00403080, 11 bytes

`src/script/stage_ecl_load_normalized_00403080.cpp` defines
`StageEclLoader_00403850::LoadNormalized`. It forwards the filename to the
already recovered public thiscall `Load` and returns zero for success or -1
for any nonzero result. The class gains only a method declaration, with no
layout change. Native LTCG places its private filename argument in EAX while
preserving the receiver in ECX, emitting exactly:

```
push eax
call 0x00403850
neg eax
sbb eax,eax
ret
```

The dedicated native cluster declares the public loader dependency and an
unselected 59-byte array caller. The first ordinary compilation emitted
17 bytes; compiling in the registered native cluster recovered all 11 bytes.
Earlier GCC/Clang trials had failed on this adapter; they do not describe the
current MSVC result.

Ghidra initially had no function here. Creating it with disassembly enabled
produced an 11-byte body, and decompilation confirmed `-(result != 0)` with
the filename arriving in EAX. The old 25-byte assembly region began at
0x00403077 and contained nine leading INT3 bytes, the adapter, and five trailing
INT3 bytes. These 14 bytes are now explicit padding arrays in
`src/data/text_0040.cpp`. They receive no recovery credit. The old naked owner
was deleted.

## Verification and retained evidence

Reproduce the production checks:

```
python3 matching2/tools/matching/probe.py --source src/input/indexed_flags.cpp
python3 matching2/tools/matching/probe.py --source src/script/stage_ecl_load_normalized_00403080.cpp
make
make EXACT=1
```

Native PE images, MAP files, final source snapshots, layouts, and direct
unmasked SHA-256 comparisons are retained under
`matching2/build/experiments/indexed_mask_and_stage_adapter_2026_10_04`.
Both full function windows have zero different bytes. The production totals
are 2,169 ordinary exact C++ regions / 160,681 bytes and 143 remaining assembly
regions / 128,858 bytes. Three equivalent C++ regions and the remaining assembly
still prevent completion of the full objective.
