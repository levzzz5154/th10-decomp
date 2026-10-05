# Plain atlas text drawing C++ equivalence recovery, 2026-10-05

The complete 509-byte routine at `0x00437FE0` now has a C++ implementation
selected by `layout/equivalent/font_atlas_draw_text_00437fe0.json`. The default
build uses it; `make EXACT=1` retains the original assembly. The model is the
natural source from `font_atlas_draw_plain_text_00437fe0_parked_2026_10_05.md`,
with its real surface-fill dependency compiled in the same native LTCG scope.
The draw function itself is rooted to preserve its public six-argument stdcall
entry and RET 24. The fill call is rebound to the existing owner at 0x00436CA0.

The comparison reports 166 instructions, 117 identical, and 44 recorded hunks.
Most hunks repeat the same size/font register substitution across the fifteen
font-selection branches. No unproven branch targets, frame shifts, or
base/index differences are admitted. The full function remains 509 bytes.

## Allocation and instruction review

After all four callee-saved pushes, both bodies have the same frame and public
argument addresses. Every saved register is restored on both surface-release
paths, and the same 24 argument bytes are removed on return.

| Value | Retail | C++ |
| --- | --- | --- |
| font size during selection | EBP | EDI |
| selected font | EDI | EBX |
| device context | ESI | ESI |
| SelectObject import pointer | EBX | EBP |
| drawn row count | EDI | EDI |
| previous selected object | dead size-argument slot | EBX |
| size after the first SelectObject | EBP | size-argument slot |
| temporary surface output | dead color-argument slot | dead size-argument slot |

At `+0xD6`, the C++ clamps the size in its argument home and reloads it instead
of keeping it solely in EBP. That home is private to this call, its updated
value is used for the source rectangle height, and it is reused as the
surface output only after the final size use. The inline upload helper bounds
that output local's lifetime. The three recorded surface-slot offsets refer
to the same value across GetSurfaceLevel, upload and conditional release;
the temporary's address itself does not escape that call's output contract.

All fifteen font pointers, size thresholds and comparison signedness agree.
The moved initial size load accounts for the intervening pushes in its ESP
offset. The previous-object value is preserved across calls in either a saved
register or an unused argument slot. Both restore that first SelectObject
result twice, regardless of the later SelectObject return values.

The width calculation loads `destination.left` into EDX before loading the
right edge, rather than subtracting the left-edge memory operand directly.
The rectangle is unchanged during this calculation, no call or memory write
intervenes, and both compute `(right - left) * 2 + 22` with the same 32-bit
arithmetic and signed 1024 clamp. The reloaded size computes the same bottom
edge. A four-byte LEA alignment filler disappears; it has no flag, stack or
memory effect. External-call ordering and all other operations agree.

## Differential execution

`matching2/tests/font_atlas_draw_plain_text_differential.py` compiles the
maintained C++ through the **strict** equivalence gate, then executes that
native body and retail under Unicorn. It compares every external call's
arguments and source/destination rectangle contents, including the private
fill ABI, and poisons EAX/ECX/EDX at each call to exercise preserved values.
Only private output-slot addresses are normalized to the value written.

All **3528 cases pass**: every font threshold, negative and extreme sizes,
four x coordinates including a wrap boundary, widths below/at/above the
1024 clamp, empty/ASCII/multibyte text, and valid/null surface outputs. Each
case also checks callee-saved registers, stack cleanup, unmodified destination,
one text call, two restores of the first object, and conditional release.
The helpers and Windows/COM calls are stubs: this validates the routine's
boundary behavior, not GDI rasterization or Direct3D output pixels.

Reproduce using Python with Unicorn installed:

```sh
python3 matching2/tests/font_atlas_draw_plain_text_differential.py
```

The local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`. The full normal
and exact image gates are run after integration.
