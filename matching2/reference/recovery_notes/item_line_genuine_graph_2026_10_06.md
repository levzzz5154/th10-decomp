# Line sweeps: exact production bodies with the actual dependency graph

The already selected 609-byte all-segment sweep at 0x0041E260 and 623-byte
bounded sweep at 0x0041F400 now compile with their complete allocator and
animation dependencies and real public polar methods. This improves source
readability and removes a synthetic compiler entry; it adds no coverage.

The maintained owners are
[line_effect_create_all_segments_0041e260.cpp](../../msvc/src/game/line_effect_create_all_segments_0041e260.cpp)
and [fun_0041f400_0041f400.cpp](../../msvc/src/game/fun_0041f400_0041f400.cpp).
Their existing
[layout](../../msvc/layout/ltcg/item_line_bounded_0041f400_2026_09_28.json)
now uses the private
[driver](../../msvc/layout/ltcg/item_line_runtime_0041e260/driver.cpp).
The eight private files contain complete ordinary C++ bodies and typed views.
The old context files remain historical, unused inputs.

Both sweeps store velocity in an actual polar object and pass a Vector3
position to Spawn. The all-segment sweep writes through a Vector3 pointer to
the animation's position, preserving the original X/Z/Y store order without
indexing beyond an individual float subobject. The bounded sweep also names
the output vector's members. FrameTimer and Entity are real embedded objects
in the allocator's item view, with compile-time size and offset checks.

The link entry is the complete actual 30-byte ItemPolarVelocity::SetPolar
method at 0x0041BEB0. Both selected sweeps are explicit public roots, as is the
line polar helper. No synthetic entry, method-address publisher or fabricated
caller participates in this selected graph. The native allocator retains its
observed manager-EAX/position-ECX/four-stack-word/RET16 convention through the
real line calls; rooting it publicly would change that convention.

The dependency bodies are unselected and earn no recovery credit. In
particular, Spawn still has the two literal identifier-copy differences at
offsets 17A/17F. The contextual MSVC polar methods emit FCOS/FSIN; the separate
selected GCC C++ polar recoveries produce retail FSINCOS. The inherited
Entity_Init external ABI boundary and raw helper views are not newly certified
as portable C++ by this cleanup.

## Verification

An isolated copy first passed the normal cluster verifier, including source
and include ownership and native contribution/address checks. Both complete
bodies were then compared directly from the native PE at their retail
addresses. Production repeated the same direct comparison after the graph
was applied:

| Body | Size | Complete raw SHA-256 |
| --- | --- | --- |
| 0x0041E260 | 609 | `0f407d65898d373dc40df48afc5f748b24a84dc543e9d14df6bd21cbaec02745` |
| 0x0041F400 | 623 | `f064ada0633637ffbd6631367e900d6d1415569100052bf52bae824735db874f` |

The production report records zero changed instruction bytes, zero address
operand changes, zero masked bytes and `reference_bytes_used_for_build: false`.
No comparison normalization is needed for the raw native proof.

Both `make` and `make EXACT=1` pass. The exact executable equals all 487,936
oracle bytes and retains SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The manifest-based audit covers all 961 current native cluster reports and
1,481 selected functions: every selected hash matches the oracle, and every
report records zero instruction changes, zero masks and no reference bytes
used for compilation. Historical reports are excluded by selecting each
current layout's name and checking its complete symbol/address/size set.

The production report is
`matching2/build/msvc/clusters/item_line_bounded_0041f400_2026_09_28/report.json`.
Isolated and production receipts are retained under
`matching2/build/experiments/item_line_genuine_production_2026_10_06/`, including
`raw_selected_proof.json` and `production_receipt.json`.

Coverage remains 2,252 ordinary regions / 197,229 bytes (61.3% byte-exact C++),
eight equivalent regions / 33,176 bytes and 62 assembly regions / 91,078 bytes.
The full readable, byte-matching, inline-assembly-free decompilation goal
remains active and incomplete.
