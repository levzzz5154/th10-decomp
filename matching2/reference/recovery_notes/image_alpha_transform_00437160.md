# Image alpha transform at `0x00437160`

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27: recovered ordinary C++ for the complete 157-byte retail region.
Three fresh native `/GL` + `/LTCG` builds and the ordinary maintained
plain-source probe path matched every byte, with no relocations, no masks,
and no rewritten bytes. The final source therefore requires no LTCG cluster.
The source and promotion files are retained in
`matching2/build/experiments/image_alpha/msvc/`; the source and region have been promoted into the maintained project.
No optional alpha investigation cluster was registered. The full-executable
rebuild remains the final integration gate.

## Source and ABI

`ImageSurface_00437160::InvertAlpha(int row_count)` has the observed public
`__thiscall` entry: receiver in ECX, row count at `[ESP+4]`, success in AL,
and `RET 4`. The routine makes no calls. Only its accessed fields are declared:
format at `+0x100`, pitch at `+0x110`, and pixel pointer at `+0x120`.
The names and wider class relationship remain provisional.

For format `0x15`, it complements byte offsets 3, 7, 11, and so on. For
`0x1A`, it XORs `0xF0` into odd byte offsets. For `0x19`, the packed
`Pixel1555` view exposes 15 color bits and one alpha bit; it assigns
`pixel.alpha = !pixel.alpha` and clears the color bits when the new alpha
is zero. Its forward loop advances the byte pointer and index by two.
Every supported format returns 1, including empty spans; other formats
return 0.

## What resolved the residual

The retained arithmetic-expression candidate emitted 156 bytes under native
LTCG and put the byte span in ESI. Array, ignored-return, global-surface,
bracketed-transform, and full recovered `sub_437DB0` caller contexts emitted
the same body. The real caller alone was therefore insufficient.

A packed one-bit alpha field assigned with logical negation reproduced the
retail pixel-operation sequence, including its zero-extended 16-bit load,
five complement/XOR operations, `test ah,ah`, and masked color clearing.
A forward byte-pointer loop reproduced retail's EDX pointer and ESI counter
inside that loop. Finally, making all successful switch cases `break` to one
trailing `return 1` selected EAX for the initial byte span, ECX for the
`0x1A` index, and ESI for the `0x15` index. The compiler also emitted the
retail one-byte NOP at `0x004371AF` through native loop alignment.

The load order, all loop instructions, complete block layout, and every
return now match. No artificial volatile access, inline assembly, binary
padding in the selected function, instruction patch, or changed extent is
used. The optional investigation layout roots the method's own symbol to preserve
the public ECX receiver. The ordinary compilation path also retains that ABI
and emits the same exact 157-byte body.

## Live Ghidra evidence

The live MCP endpoint was read on 2026-09-27; decompilation and assembly are
retained as `image_alpha/ghidra_decompilation.txt` and
`image_alpha/ghidra_disassembly.txt` under the experiment directory.
Known callers are `0x00437DB0` and `0x00437FE0`. Calls at `0x00437ECA`,
`0x00437F3D`, `0x004380E7`, and `0x00438142` push one row count, load
ECX with the global surface at `0x00474CB0`, and ignore AL. Both callers
calculate `2 * max(font_height, 17) + 6` rows and bracket GDI text drawing
with the alpha transform.

Surface creation at `0x00436AF0` confirms the intervening layout: width
`+0x104`, height `+0x108`, image byte size `+0x10C`, HDC `+0x114`, previous
bitmap `+0x118`, and HBITMAP `+0x11C`. These fields are not accessed by this
region and need not be introduced into its partial declaration.

## Verification and promotion files

- Source: `matching2/build/experiments/image_alpha/msvc/src/render/image_alpha_transform.cpp`.
- Optional native-LTCG investigation layout and driver: `matching2/build/experiments/image_alpha/msvc/layout/ltcg/image_alpha_transform_00437160{.json,_context.cpp}`.
- Plain region proposal: `matching2/build/experiments/image_alpha/plain_proposal.json`.
- Final ordinary probe: `matching2/build/experiments/image_alpha/final_plain_probe.json`
  reports the whole 157-byte region exact, zero differing bytes, no relocations,
  and no failures. The intermediate direct plain-object comparison is retained
  in `plain_final/result.json`.
- Fresh probe reports: `matching2/build/experiments/image_alpha/final_probe1.json`
  and `final_probe2.json`, plus `final_probe3.json` with the formatted driver;
  each reports one 157-byte exact region,
  `different_bytes: 0`, no relocations, and no failures.
- Native build reports are below each probe's
  `clusters/image_alpha_transform_00437160/report.json`; these validate the
  complete named contribution, public root, input/toolchain hashes, and
  unmodified native bytes.

Verified source SHA-256:
`ee2d135006e8395bc682488302461b8e439743da69d0ada1cd4e58a772fceea2`.
The earlier residual trail is retained in `00408880_wave17.md` and the
experiment's context/variant reports; it is superseded by these full-byte
proofs.
