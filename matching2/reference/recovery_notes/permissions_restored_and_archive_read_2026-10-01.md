# Permissions restored and archive read verified

The user enabled full access and resumed the decompilation on 2026-10-01.
Wine now starts, an independent Unix socket bind/listen succeeds, and live
Ghidra decompilation succeeds. The previous `wineserver: bind: Operation not
permitted` was caused by the session restriction. No Wine reinstall, prefix
reset, or build-framework change was needed. The existing writable cloned
prefix `/tmp/th10-decomp-wine-20261001` is used for these builds.

The fresh baseline build verified the previously integrated resource/overlay
recoveries: all 487,936 executable bytes matched retail, and every maintained
source hash matched its build report. That snapshot is preserved in
`matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verified_baseline.json`.

ArchiveCursor_Read at `0x0044DE10` then passed the ordinary production probe
for all 202 original bytes. Its four frozen C++/header/context/layout inputs
were copied into main; the unselected context is correctly bounded at 90
bytes. The old assembly row is retained as `previous_record`, its three
symbol aliases are preserved, and the sole-owner assembly file was backed
up and removed. No other region ownership was changed.

Both the main focused probe and a subsequent fresh whole-project build pass.
`matching2/build/archive_read_msvc_2026_10_01/th10.exe` literally equals the
487,936-byte retail executable; all source hashes are current. Executable
SHA-256 is `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
No instruction or address operand was changed, no comparison byte was masked,
and retail bytes were not used to construct the compiler output.

At this verified checkpoint, ordinary C++ covers **1,869 regions / 100,663
bytes**; assembly covers **431 / 222,255**; toolkit runtime library covers
**323 / 66,480**. Five semantic functions still contain six x87 assembly
blocks totaling 4,451 bytes. Fully assembly-free C++ therefore covers
**1,864 regions / 96,212 bytes**. The complete decompilation goal remains
incomplete; later integrations must establish a new whole-build checkpoint.

The selected recovery uses pinned MSVC's intrinsic `memcpy`, whose generated
forward REP MOVSD/REP MOVSB sequence exactly preserves the original native
transfer behavior. This is a compiler/target contract, with no portable ISO
C++ overlap guarantee. The memory-mode output aliasing and unsigned wrapping
clamp, field reloads, and ignored ReadFile BOOL match the original body.
The ReadFile count output reuses the destination argument's stack slot.
No new dynamic differential test of this particular source is claimed.

Repeat the provenance and whole-build audit with:

```sh
python3 matching2/build/experiments/archive_cursor_production_ready_2026_10_01/verify_ordinary.py \
  --main-focused-probe matching2/build/experiments/archive_cursor_production_ready_2026_10_01/main_probe.json \
  --whole-report matching2/build/archive_read_msvc_2026_10_01/port-report.json
```

The machine-readable checkpoint is
`permissions_restored_and_archive_read_2026-10-01.evidence.json`; full native
sources, reports, compiler artifacts, disassemblies and historical backups
remain under the archive production experiment. Subsequent source changes
make the current-source audit fail, preserving the distinction between this
verified snapshot and later work.
