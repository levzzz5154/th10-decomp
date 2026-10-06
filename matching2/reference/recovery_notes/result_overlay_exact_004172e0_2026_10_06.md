# Result overlay 0x004172E0: byte-exact ordinary C++

`msvc/src/game/result_overlay.cpp` now provides the complete result-caption
routine in ordinary C++. All 668 retail bytes match: 640 bytes of instructions
and the compiler's seven-entry, 28-byte switch table. Native LTCG derives the
private entry with kind in EAX, the front state and number on the stack, and
RET 8 from the logical stdcall declaration and complete callees. The selected
symbol is `?ResultOverlay_SetMode@@YGXHPAUResultOverlayState_004172e0@@H@Z`.
No assembly adapter, table literal, output patch, or comparison mask is used.

Mode 0 replaces the main caption with script 71 and creates eight digit
animations with scripts 39 through 46. It divides the signed input by powers
of ten, configures each digit's sprite, and hides leading zeroes. Mode 1 uses
main-caption script 72, modes 2 through 4 use secondary-caption scripts 73
through 75, and mode 6 uses main-caption script 76. Mode 5 and out-of-range
values do nothing. Retirement precedes the resource reload and creation, as
in retail. The partial state has checked offsets for all eight digit handles,
both captions, and their resource.

## Complete native graph and public helper boundary

`msvc/layout/ltcg/result_overlay_004172e0.json` contains the complete real
spell-end source as its link entry, together with thirteen complete animation
and support helpers. The public resource initializer at 0x00449870 must retain
its ECX receiver and two stack arguments. Rooting that complete helper preserves
the public boundary while the overlay's kind parameter remains a private EAX
input. No invented helper bodies or synthetic outer caller are required.

The existing `anchor_roots` metadata now also accepts complete non-generated
`/GL` helpers. Previously its parser restricted roots to separately compiled
ordinary EH anchors, even though the native linker and full contribution checks
already supported both kinds. This is a root-expression extension: native
compiler origin, address, complete CODE extent, and selected byte checks still
apply. Unknown, duplicate, and generated roots remain disallowed. Rooted
helpers remain unselected and receive no new recovery credit.

The strict positive graph gives the initializer its exact 217-byte public
body. Removing its root in an otherwise identical graph produces a 210-byte
private initializer and a 672-byte overlay contribution. The strict probe
rejects that output at the existing complete-contribution gate. Unknown and
duplicate root controls also fail at metadata validation. A native initializer
whose object is removed from the declared compiled inputs fails the new rooted
helper provenance check. Receipts are in `anchor_root_controls.json` and
`without_public_helper_root.log` below.

`python3 matching2/tests/ltcg_public_anchor.py` reproduces these controls from
the maintained project. It freshly compiles the positive graph and compares
all 668 overlay bytes and 217 public-helper bytes directly with retail, then
compiles the unrooted negative graph in an isolated project copy. The native
ABI, undeclared-origin, unknown-root and duplicate-root controls all reject;
the positive comparisons pass. Its full receipt is
`matching2/build/tests/ltcg_public_anchor/controls.json`.

Only the overlay is newly selected. The complete spell-end context emits 394
bytes with a public ECX receiver; it is deliberately not substituted for the
already-maintained exact 399-byte private-EAX spell-end owner. Likewise, the
existing owners of every helper remain unchanged.

Eleven unselected helpers also match their entire raw native retail bodies:
create animation 73, register primary-back 118, pool allocator 161, resource
initializer 217, show 67, hide 67, lookup 73, retirement 66, sound queue 123,
entity initializer 273, and preserving script loader 194 bytes.
The 64-byte effect-stop context differs in register allocation. The complete
356-byte sprite configuration context differs only at the two pooled-float
addresses: its generated `1/256` literal is at 0x0044A000 rather than retail's
0x00470B7C. The native layout verifies that literal's value. These two context
bodies are not claimed as exact recoveries; their existing production bodies
are retained.

## Source-shape controls

All experiments live under
`matching2/build/experiments/result_overlay_native_2026_10_06/`. The initial
complete source compiled successfully and reproduced the EAX mode boundary.
Its helper graph initially permitted the resource initializer to change ABI;
adding the complete preserving-loader body and retaining the initializer's
public root made the animation creation and registration helpers exact.

Evaluating the caption resource before retirement incorrectly hoisted its
load. Reloading it after `Release` preserves the observed callback-visible
ordering. Expanding each switch case directly gives the compiler distinct
structure-return temporaries and reproduces the forty-byte frame and retail
tail merging. The digit loop preserves the incoming number in `remaining`,
then reuses the input slot for the digit index. Keeping the quotient's remainder
as a separate local and assigning it before reducing the divisor reproduces
the final reload, arithmetic scheduling, stack slots, and cold-case register
allocation. These are ordinary source operations; no barriers or extra
volatile qualifiers were introduced. IDs use an unsigned field so allocation
wraps through zero with defined arithmetic.

`remainder_first/` is the first exact relocated diagnostic model.
`real_caller_entry/` and `real_caller_constant/` verify that the complete real
spell-end entry suffices without the synthetic outer loop. `fixed_probe/` and
`fixed_final_probe/` establish the actual final addresses and complete CODE
extent after the result-specific type names, offset checks, and unsigned ID
field. The diagnostic instruction aligner reports one apparent switch-target
hunk because it spells an end-of-code target differently; direct comparison
of all 668 bytes, including every table entry, has zero differences.

`fixed-final-helper-audit.json` records independent whole-body comparisons
against retail after compilation. The compiler never reads oracle bytes.
The authoritative selected-body SHA-256 is
`b37d87f17bc0f0000b12f0da66200abc16694d784eea460dda7fde384da8bbe1`.
Native extraction reports zero changed instruction bytes, zero changed
address operands, zero masked bytes, and no reference bytes used for the build.

Validation on 2026-10-06:

- Strict final native probe: all 668 bytes exact, including the switch table.
- Public-anchor compiler test: exact positive bodies; all four negative
  controls rejected.
- `make`: all 1,676 maintained source units and eight existing equivalence
  gates passed; output exact outside the existing equivalent regions.
- `make EXACT=1`: fresh full rebuild passed after the rooted-helper provenance
  check; all 487,936 executable bytes exact.
- Independent whole-file equality: exact; executable SHA-256
  `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
- Maintained native report: selected SHA-256 above, zero instruction/address
  changes, zero masks, no oracle build input.
- `git diff --check`: passed.

Progress: 2,249 exact ordinary C++ regions / 193,049 bytes (60.0% of game code);
8 equivalent regions / 33,176 bytes; 65 remaining assembly regions / 95,258
bytes. Ordinary plus equivalent recovery is 70.4%. The full readable,
byte-exact, assembly-free objective remains incomplete.
