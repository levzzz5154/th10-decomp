# Animation surface loader `0x00447C80`: contiguous stack aggregate trial

The full 576-byte surface loader is still unresolved. A source-grounded local
aggregate preserves the four adjacent retail homes, but MSVC 13.10 /LTCG emits
the exact same 575-byte body as the prior best source. The normal full-function
gate rejects it; no maintained source or region was promoted.

The fresh Ghidra dry-run listing covers all 576 bytes and was saved as
`matching2/build/experiments/surface_stack_aggregate_2026_09_28/ghidra_surface_576_dry_run.json`.
There is still no Function object at this address. Relative to ESP after the
prologue, retail uses `temporary` at `+0x10`, `memory` at `+0x14`, the saved
primary-resource pointer at `+0x18`, and `size` at `+0x1C`. The 260-byte path
buffer begins at `+0x20`, and the cookie home is at `+0x124`. The apparent
`ESP+0x24` and `ESP+0x28` path references occur after argument pushes.

The aggregate source in the scratch `msvc/` tree declares these fields in that
order, leaves it uninitialized as the control flow requires, and passes member
addresses to the real archive and D3D calls. Only the saved primary pointer is
volatile; the prior source's member-specific volatile reads of `size` and
`memory` remain. This is a lawful representation of the actual stack values:
`Archive_LoadFile` writes `size`, and `CreateOffscreenPlainSurface` writes
`temporary`. The early creation-failure return does not read `temporary`.

The normal probe reported `function AnimationLoadSurface extent is outside a
MAP CODE contribution`, because the contribution is 575 bytes while the full
retail region is 576. Raw native PE/MAP measurement at `0x00447C80` gives
326 differing bytes in the 575-byte overlap and one missing byte. Candidate
SHA-256 `257c4dc38a6a7d30e2597d7a51c9fb5268b3a6a20ef17ba303ed199c1f308416`
equals the old best body byte for byte. The aggregate source SHA-256 is
`7b506101f57b1584df88b3f149e4fabe53b50959232bf5748b5af223ef028d20`.
The complete real dependencies at `0x00447EC0` (169 bytes), `0x00447F70`
(87), `0x0044B360` (360), and `0x0044B8E0` (201) remain exactly equal to
retail in the fresh linked image.

The first byte difference at `0x00447D0D` is a branch displacement caused by
the shifted epilogue. The first substantive divergence is `0x00447D5B`:
retail loads `size` into ECX and `memory` into EDX, builds the 28-byte image
index through EAX into EBX, then loads `temporary` into EAX before pushing
arguments. The aggregate candidate still loads size into EAX and memory into
ECX, builds EBX with `ADD`, and reloads temporary after four pushes. Grouping
the locals alone therefore does not change the optimizer's register/lifetime
decision. The next useful hypothesis must change a genuine address escape or
live range while preserving the whole function; cosmetic field grouping has
been exhausted.

Evidence and reproducibility: the scratch directory retains the source,
`attempt02_gate.json`, `attempt01_measurement.json`, both fresh native images
and maps, and `verify.py`. From the repository root, run
`PYTHONPATH=. python3 matching2/build/experiments/surface_stack_aggregate_2026_09_28/verify.py`.
It checks the complete mapped contribution, old-body equality, all four
anchors, Ghidra range, and the failed normal gate. No assembly, comparison
masks, truncated region, synthetic caller, or Ghidra Function head was used.

The copied prior source still computes an `imageOwner` pointer by treating an
interior manager address as a whole manager object. That questionable C++
pointer provenance would need correction before any future promotion; this
trial does not claim to be a selected recovery.
