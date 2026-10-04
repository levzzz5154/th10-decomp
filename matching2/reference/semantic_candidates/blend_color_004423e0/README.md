# Exact blend/color/filter update, 2026-10-04

The full 440-byte region at `0x004423E0` is ordinary C++ in `src/render/animation_manager_apply_blend_color_004423e0.cpp`. It updates cached blend mode, selects the entity's primary or secondary color, scales and saturates each channel when fading is enabled, updates texture-factor color and filtering, and increments the state-change counter. Native entry receives manager EAX and entity EBX and returns with plain RET.

A four-byte packed-color union exposes both the integer word and its byte channels under the target's little-endian MSVC storage model. Reading red, green, blue and alpha directly through `channels[2]`, `[1]`, `[0]` and `[3]` resolves the earlier 33 differing color-modulation bytes. The saturation formula remains `(channel * tint) >> 7`, capped at 255. No volatility, barriers, fabricated arguments, assembly or output patches were added.

A controlled fresh matrix distinguishes the source choice: the scalar baseline and a union with packed shift extraction retain 33 differences; the union byte-channel version and its tint-first helper variant both match all 440 retail bytes. Complete sources, compiler outputs and raw comparison measurements are retained under `matching2/build/experiments/blend_color_2026_10_04/` and recorded in the evidence JSON.

The cluster retains the complete genuine transformed-quad caller, batch flusher and render dispatcher as unselected native compiler context. Their duplicated context bodies receive no recovery credit and do not change their independent production ownership. The legacy assembly symbol remains a static address alias for existing callers.

Fresh maintained proof: `matching2/build/experiments/blend_color_2026_10_04/production_probe/clusters/blend_color_004423e0/report.json`. Complete raw native SHA-256: `cfcfb2eef162591bd0e9d7c33edf0999083ba0954ba69f13ec035fe194c2f7db`. Every recorded input hash was checked against the current file. Both `make -j2` and `make EXACT=1 -j2` passed; the blend region, spell-card setup, four animation registrars, resource initializer and preserving loader match retail in both final outputs. The whole 487,936-byte EXACT executable equals the oracle, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

`matching2/reference/semantic_candidates/blend_color_004423e0/overlay/` preserves the complete current compiler inputs. `before_exact_promotion/` preserves the replaced assembly and prior recovery note.

Replay:

```sh
python3 matching2/tools/matching/probe.py --source src/render/animation_manager_apply_blend_color_004423e0.cpp --output matching2/build/experiments/blend_color_004423e0_replay
```
