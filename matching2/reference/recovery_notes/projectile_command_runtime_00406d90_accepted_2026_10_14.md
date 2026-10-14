# Projectile command interpreter `0x00406D90` — accepted as an equivalent recovery (2026-10-14)

Verdict: 302 of 337 instructions identical, 1,604 of 1,604 bytes used, 25
recorded differences covering 44 instructions (total budget 112). Structural
differences cover 12 instructions (budget 42); the rest are evaluation-order (21),
register-choice (9), stack-slot-order (1) and alignment-padding (1).

## Region extent

The region was re-extended from 1454 to 1604 bytes (0x406D90..0x4073D4), as
approved in the 2026-10-13 note. It now absorbs `text_padding_0040733e` and the
switch tables `text_data_00407340`; those bytes are `_emit` lines at the end of
the asm source, and both data regions are gone from regions.json and
src/data/text_0040.cpp. `make EXACT=1` stays bit-identical.

## What closed the "receiver in EBX vs retail EBP" wall

Earlier sessions put this down to c2's frame-spill heuristic. It was actually
an interprocedural convention chain:

1. Retail's sound queue 0x43DD10 takes the sound id in EBX. In the model link
   the sound id stayed on the stack, and the interpreter's 0x20000 case then
   did not clobber EBX across a call. That left EBX free for the receiver.
2. MdmFlexParams (0x107ADBE0) refused the sound id because EBX was in the
   function's excluded-register set at entry. The set gets EBX (bit 0x10)
   when the callee's call-graph node has flag 0x1000 at +0x50
   (`107F71DC`).
3. Flag 0x1000 is set by the call-graph pass at 0x1070C961 on every direct
   callee of a function whose front-end attribute word (+0x69, read from the
   IL by `build_Symbols_seg`) has bit 0x40000.
4. The interpreter had 0x40000 because of `__declspec(align(8))` on its
   pattern word buffer. Explicit over-alignment is the trigger. The frame
   still aligns without it (`and esp,-8` stays), as in retail.

Dropping the `align(8)` gave the sound queue its EBX parameter, and the
receiver moved to EBP. The retail prologue
`push ebx; push ebp; push esi; push edi; mov ebp,ecx` with the 0x210 frame
followed: 176 -> 297 identical.

## Other fixes in this pass

- The score polar setter 0x408750 (GCC-compiled in retail, outside the /GL
  pass) is an absolute symbol instead of a context body. The body let LTCG
  flex its receiver into EAX, while retail passes it in ECX (`lea ecx`).
- The command is a pointer that the grid case advances (`++command`) to read
  the second grid record. Retail's `add esi,0x18` is that increment; a
  reference plus `(&command)[1]` folds into +0x18 offsets.
- Context: the real grid scanner 0x4073E0 with its byte-exact cluster's
  anchors, moved past the interpreter's tables with a `code_seg` macro wrapper
  (`equivalent/game/context/projectile_command_scan_cells_004073e0.cpp`).

## Tracers used (scratch copies of trace_flex_params.py)

- MdmFlexParams entry-block scan: break at 0x1077FA59 (load candidate),
  0x1077FFC2 (parameter marked stack-only), 0x1077FAD6 (excluded-register
  set).
- Call-graph seed: 0x107C1606 (node whose function has +0x69 & 0x40000).
- Hardware watch on node+0x50 / function+0x6B to find the writers.
