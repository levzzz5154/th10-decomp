# Sound effect buffers 0x0043DB60: genuine title caller graph

The earlier native model used a synthetic repeated caller. A new scratch graph
replaces it with the complete title-assets initializer based on live Ghidra and
retail assembly at 0x0041F990. It co-compiles the existing worker-stop body, music
launch and stop bodies, archive loader, aggregate rewind, and real text-log
implementation. The log must be co-compiled: its ordinary imported variadic
member ABI does not spell the private ECX logger contract.

The complete genuine title model emits 282 bytes, versus 299 retail, and remains
unselected. Its measured native extent is used when placing following complete
helpers. The effect initializer still emits 300 bytes with manager in EDI and
-1 held in EBX; retail is 295 bytes with manager EBX and initial -1 in EAX.
It still converts a cached music-volume value from a stack temporary rather
than using retail's FILD of the manager field. Replacing the repeated caller with
this genuine graph therefore does not resolve this allocation problem.

Widening the curve's factor/squared intermediates to double is also measured.
It emits 300 bytes and generates double constant-pool operands. The verifier
rejects the existing float constant aliases, correctly: they cannot be rebound
to double data. This variant is not promoted and constants are not patched.

The original floating model, complete source graph, images/maps and receipts are
archived in `matching2/build/experiments/sound_effects_title_graph_2026_10_04`.
The current scratch project is `/tmp/th10-effects-title/msvc`. The selected
retail extent deliberately remains 295, so complete-contribution rejection is
expected for the 300-byte candidate. No compiler gate was relaxed; no production
source, header, ownership record or executable changed.

Next work should target the initializer's own constant lifetime and music-volume
reload. Do not repeat the synthetic-to-title caller change or the widened-double
curve without new evidence. Further register-pressure or fake ABI callers are
not a substitute for this genuine path.

## Further volume and sentinel controls

A signed 32-bit music-volume bitfield preserves the object layout but emits the
identical complete 300-byte body (SHA-256 66e80da8dd83e144384a4d27dfb41e6cfb0ea263d710afc435a4296698434288). It does not force
a memory-form FILD and remains unpromoted.

Replacing the twelve volatile pointer casts with ordinary explicit assignments
still gives twelve individual stores and a 300-byte function. It moves the ESI
save/global-manager load before the stores and retains EDI receiver / EBX -1,
so it is not an exact improvement. Do not infer that those casts are necessary
for unrolling. The frozen closest candidate remains unchanged.

Native images, maps, source/type variants and measurements are archived in
`matching2/build/experiments/sound_effects_volume_controls_2026_10_04`.
These two controls are exhausted; production source and ownership are unchanged.
