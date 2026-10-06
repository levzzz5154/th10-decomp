# Complete laser cutter family — unselected native C++ candidate

All four complete cutters share the same vector, animation-ID, spawn-parameter and virtual-interface definitions. The two line trimmers copy the complete 476-byte parameter record; the two beam splitters clear a new record. The genuine supporting routines are complete. Unused virtual slots are declarations only: no dummy method body, caller or vtable is supplied.

| Entry | Retail bytes | Native bytes | Differing overlap bytes | Cases |
|---|---:|---:|---:|---:|
| Rectangle trim, `0041D880` | 1269 | 1269 | 13 | 249 |
| Circle trim, `0041DD80` | 1238 | 1237 | 876 | 236 |
| Rectangle split, `0041EB00` | 1171 | 1171 | 27 | 199 |
| Circle split, `0041EFA0` | 1108 | 1108 | 433 | 186 |

The shared native build preserves every individual cutter's diagnostic body and observations. All 870 bounded cases pass, observing 1,155 item calls, 2,644 effects and 170 spawned lasers. The individual fixture scopes and shared scripted boundaries still apply. This is not full game integration or a byte-equality proof. No cutter is promoted and no recovered code bytes are credited.

Run from the repository root:

```sh
python3 matching2/reference/semantic_candidates/laser_cutter_family/measure.py cutter_family_maintained
python3 matching2/reference/semantic_candidates/laser_cutter_family/safe_link.py cutter_family_maintained
python3 matching2/reference/semantic_candidates/laser_cutter_family/differential.py cutter_family_maintained
python3 matching2/reference/semantic_candidates/laser_cutter_family/include_probe.py cutter_family_maintained
```

The larger family image at the usual diagnostic base overlaps an address used by an emulator callback. `safe_link.py` replays the ordinary native link at `0x00100000`, adjusts only sectionless COFF symbol metadata and lets the real linker perform address fixups. It then verifies all 16 emitted function bodies against the original build after diagnostic address binding. The execution harness maps that actual PE below retail code. No instruction is patched and no compiler decision is forced.

`include_probe.py` audits actual preprocessor dependencies without replacing a compiled object. Current sources, reports, input hashes and execution-image identity are recorded in `receipt.json` and `evidence/`.

Thirty-three bounded source/build configurations were checked during this follow-up, including the two shared-family builds. None earns promotion. Target-only CPU flags do not change emission; `/G7` applied to every translation unit substantially changes the bodies and is rejected. The fully visible typed creator definitions retain a genuine public creator root. A separate trim variant improves one overlap byte, to 875, and passes all 236 circle-trim cases; it remains one byte short and is preserved under `variants/circle_trim_visible/`. The shared graph retains its original inlining choices. Reproduce one control group with `controls.py entry`, `origin`, `record`, `memory`, `flags`, `visible`, or `revision`. The older compiler is optional and requires the local Toolkit 2003 installation named in that recipe.

Read-only traces now identify the rectangle trim's equal-priority cookie-store/EBX-save choice and show the splitter's zero reuse already present at `Riscify` entry. Evidence lives in the individual rectangle candidates. The responsible earlier pass, and the original compiler input that produced retail, remain open questions. See [the recovery note](../../recovery_notes/laser_cutter_family_followup_2026_10_06.md).

The visible trim's default-base diagnostic had a numeric allocator/`Entity_Init` binding collision. Its maintained variant links directly at `0x00100000` and records the correct allocator call; the corrected residue is 875 bytes / 58 groups. Historical default-base normalized bytes are rejected as proof for that alternate. Current control reproduction also uses the non-overlapping diagnostic base.
