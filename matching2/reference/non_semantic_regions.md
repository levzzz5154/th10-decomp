# Non-semantic region ledger

Historical snapshot: the ledger counts and manifest hashes below predate the
current worktree. Use `make progress` and `msvc/regions.json` for current
accounting; [the eighth 2026-09-28 recovery checkpoint](recovery_notes/native_recoveries_2026-09-28_eighth.md)
records the latest verified conversions.

This snapshot includes the exact worker-shutdown, joystick/logger-cluster, and
FrameTimer/cursor-cluster promotions through 2026-09-13, including the third
animation cursor at `0x0043C460` and its rebound compiler literal. The machine-readable JSON is the authoritative
region tuple inventory; this page records the same accounting in reviewable
form.

This ledger inventories the live non-semantic entries in
`matching2/msvc/regions.json`. The machine-readable inventory is
[`non_semantic_regions.json`](non_semantic_regions.json); its compact region tuple
is `[address, size, source_id]`, with `source_id` resolved through the top-level
`sources` array. Each group supplies the category, evidence IDs, and revisit
criteria inherited by its tuples.

The snapshot was taken on 2026-09-13 from the current worktree. The manifest is
intentionally read-only evidence here: its SHA-256 is
`5f1654001e0e37811d0b206426ac146abbf9d66e76ff7ec87a1508e3dd6a5d96`.
The oracle is `matching2/build/oracle/th10.exe`, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

## Current accounting

The live manifest contains 4,427 regions and 412,672 `.text` bytes. Its
non-semantic portion is 3,991 regions and 389,884 bytes. The verified whole
EXE exact build covers 487,936 bytes:

| Ledger category | Regions | Bytes | Interpretation |
| --- | ---: | ---: | --- |
| `compiler_crt_runtime` | 327 | 54,411 | Exact VC7.1 library-section matches outside relocations |
| `embedded_text_data` | 25 | 8,157 | Byte overlays in `.text` classified as data |
| `alignment_padding` | 1,817 | 15,533 | Evidence-backed non-instruction filler |
| `game_code_still_recoverable` | 533 | 247,745 | Known-domain non-CRT assembly still in the recovery queue |
| `exact_assembly_required` | 15 | 289 | Only documented fixed-body/toolchain blockers |
| `unclassified_assembly` | 1,274 | 63,749 | Evidence hold; no stronger claim is made |
| **Total non-semantic** | **3,991** | **389,884** | **Accounts for every `kind != semantic` entry** |

For comparison, the live manifest’s native kinds are 436 semantic / 22,788
bytes, 2,149 asm / 366,194 bytes, 25 data / 8,157 bytes, and 1,817 padding /
15,533 bytes. Older counts in `matching2/tools/waves/ROADMAP.md` were measured
at a prior commit and are not used for this snapshot.

The exact `0x0042C620`, `0x00434F30`, `0x00436000`, `0x0043BD40`, `0x0043C230`,
`0x0043C460`, `0x00442F50`,
`0x004493E0`, `0x0044A0C0`, `0x0044B810`, `0x0044C100`, `0x0044C130`,
`0x0044C150`, `0x0044D300`, `0x0044D370`, `0x0044D550`, `0x0044D5D0`,
`0x0044D600`, `0x0044DCA0`, `0x0043D790`, and `0x0044D4E0` semantic promotions
are therefore excluded from this ledger; their previous
asm records are retained only as `previous_record` in the manifest. Promotion
evidence is recorded in the [archive-codec recovery note](recovery_notes/archive_codec_cursor_00434d10_00434dd0_00434f30_00435dc0_0044b0d0_0044b220_0044dd40_0044de10.md),
the [score/archive recovery note](recovery_notes/score_archive_records_0042b1e0_004359b0_00436000.md),
the [render-effect recovery note](recovery_notes/render_effect_cluster_00442050_00442f50_004452f0.md),
and the [manager-teardown recovery note](recovery_notes/manager_teardown_00409f90.md),
the [D3D/logger recovery note](recovery_notes/d3d_init_00439890.md), and the
[recovery-leaves note](recovery_notes/recovery_leaves_cluster_00413450_0044dca0.md).
The [joystick/logger cluster note](recovery_notes/joystick_probe_text_log_cluster_0044a0c0.md)
records the caller/callee ABI experiment and exact 105-byte promotion. The
[FrameTimer/cursor cluster note](recovery_notes/frame_timer_cursor_cluster_0043c230.md)
records the exact 93-byte and 133-byte caller promotions and their three-method
timer cluster. The
[third-cursor cluster note](recovery_notes/frame_timer_cursor_cluster_0043c460.md)
records the exact 154-byte promotion and the `constant_aliases` rebind that
places its compiler float literal. The
worker-shutdown cluster is described in
[`whole_program_ltcg.md`](whole_program_ltcg.md).
The already-semantic `0x00405730` region is behaviorally named
`semantic_PlayerRuntime_ReleaseAndFree_00405730`; this [entity-helper recovery note](recovery_notes/entity_player_helpers_00401de0_00405d00_00405620_004059f0.md)
documents the rename without changing non-semantic accounting.
The [camera/viewport recovery note](recovery_notes/camera_viewport_cluster_00421480_0043bcd0_00448270_00448450.md)
records a non-exact ordinary semantic attempt and does not change ledger
accounting.

## High-confidence classifications

`compiler_crt_runtime` is supported by the existing `match_crt.py` report at
`matching2/build/waves/crt-matches.json` (SHA-256
`5aefb1f9e617f36fd48d90da2b196bc785967b944e819c0039ca90342898b833`). It has
3,805 raw library-section rows, deduplicated to 327 current manifest addresses
and 54,411 bytes after equivalent-library matches are counted once per address:

| Canonical library | Regions | Bytes |
| --- | ---: | ---: |
| `libc.lib` | 224 | 32,599 |
| `libcmt.lib` | 98 | 21,584 |
| `libcp.lib` | 5 | 228 |

The ledger records the validation rule: every unique report address is a live
`asm` region with `owner == address` and the same size. This is vendor-runtime
provenance, not a claim that game source is irreducible.

The 25 data regions are emitted by `src/data/text_0040.cpp` through
`text_0045.cpp`. Twenty-four carry the source annotation
`text_range_map:defined_data` plus full/augmented-listing typed-data evidence
(1,437 bytes). `0x00450730..0x0045216F` is the separately documented 420-record,
16-byte-stride table (6,720 bytes), with repeated `.rdata` pointers, monotonic
selectors, no code xref to its start, and no instruction promotion.

The 1,817 padding regions are retained as individual manifest extents. Their
source evidence breaks down as follows:

| Evidence family | Regions | Bytes |
| --- | ---: | ---: |
| Repeated `CC/00` or inspected INT3 run | 819 | 7,433 |
| Live Ghidra missed-code candidate boundary | 422 | 3,476 |
| Live Ghidra unresolved-range boundary | 493 | 4,114 |
| Single INT3 after authenticated RET/JMP | 34 | 34 |
| Exact MSVC NOP `0x8BFF` | 7 | 14 |
| Exact MSVC NOP `0x8D4900` | 19 | 57 |
| Exact MSVC NOP `0x90` | 22 | 22 |
| PE `.text` raw tail beyond `virtual_size` | 1 | 383 |

The one extra repeated-INT3 entry is the prose-annotated
`0x004387F3..0x004387FF` Grow catch-all-trap boundary in `text_0043.cpp`.

## Fixed-body assembly evidence

Only two patterns are currently in `exact_assembly_required`; ordinary near
misses, register-allocation differences, split functions, and unresolved
calling conventions remain recoverable or pending.

The eight 30-byte `fsincos` bodies (240 bytes) are:

`0x00408750`, `0x00413270`, `0x0041BEB0`, `0x0041F800`, `0x00441EF0`,
`0x004458B0`, `0x0044C5D0`, `0x004501B0`.

The oracle scan finds `d9 fb` in each body. The cited wave reports document
VC7.1 translation-unit and `/GL` + `/LTCG` experiments that emit separate
`fsin`/`fcos` for the tested source forms, and no `d9 fb` in the CRT libraries.
The older roadmap’s “four regions” count is stale relative to this live
manifest; the ledger uses the reproducible current scan of eight.

The seven 7-byte `mov eax,ecx; jmp rel32` trampolines (49 bytes) are:

`0x00403050`, `0x00426510`, `0x0042B9A0`, `0x0042D2E0`, `0x0042D2F0`,
`0x004485D0`, `0x004485E0`.

Disassembly and W308/W601 evidence show that their tail targets consume the
receiver in EAX, while the documented standalone C++ route emits a different
forwarder shape. These are fixed under the current standalone route, but the
ledger deliberately leaves a revisit path for manifest-level EAX support,
fragment merging, or a native-LTCG cluster.

## Recoverable-investigation evidence

These five restored candidates remain in `game_code_still_recoverable`.
Their notes record behavior, ABI/layout constraints, and the next experiment;
none is promoted to `exact_assembly_required` merely because a semantic probe
was not exact or was not run.

| Target | Extent | Current evidence |
| --- | ---: | --- |
| `0x0042D920` title-options handler | 3,188 bytes | [recovery note](recovery_notes/title_options_menu_0042d920.md): retail assembly remains pending topology-safe semantic work; no irreducibility claim |
| `0x00419960` stage-tip parser | 1,498 bytes | [recovery note](recovery_notes/stage_tip_parser_00419960.md): restored body has an exact focused probe; semantic recovery is not integrated |
| `0x00408210` entity-region sweep | 585 bytes | [recovery note](recovery_notes/entity_region_sweep_00408210.md): behavior is documented, but the candidate was not probed; next focused recovery is defined |
| `0x004267F0` trigger-region classifier | 471 bytes | [recovery note](recovery_notes/trigger_region_004267f0.md): a 483-byte semantic candidate was non-exact and production asm was restored |
| `0x00409F90` manager teardown partition | 118 bytes | [recovery note](recovery_notes/manager_teardown_00409f90.md): the coupled `0x004493E0` helper is promoted exactly, but the target remains asm after a bounded 16-byte prologue/register mismatch; no irreducibility claim |

The ledger’s JSON evidence catalog and dedicated groups point to the active
recovery notes, preserving the distinction between a recoverable investigation
and an irreducible exact-assembly blocker.

## What remains deliberately unclassified

The 539 known-domain entries come from `src/game`, `src/render`, `src/script`,
`src/math`, `src/platform`, `src/app`, `src/archive`, or `src/util`. They are
recovery targets, not already-matching C++ and not proof of easy conversion.

The 1,277 `unclassified_assembly` entries are non-CRT, non-fixed-body entries
under `src/unidentified`. They may contain game code, compiler/runtime code,
fragments, tables, or boundary artifacts. Filename alone is not enough to
classify them. In particular, a failed C++ attempt is never promoted to
`exact_assembly_required` without a repeatable compiler/toolchain or
disassembly proof.

## Ledger schema and future Luna-worker process

The JSON schema is intentionally additive and manifest-independent: it records
the snapshot hashes, category definitions, evidence catalog, revisit catalog,
source table, grouped region tuples, and accounting summary. A future worker
should:

1. Hash the current manifest and oracle, then run
   `python3 matching2/tools/matching/progress.py --json`.
2. Select every current region whose `kind` is not `semantic`; preserve its
   address, size, and manifest source exactly. Check for duplicate or overlapping
   extents and make category-byte totals equal the selected manifest total.
3. For `data` and `padding`, require the matching `src/data/text_*.cpp` range
   annotation plus IDA/Ghidra boundary or byte evidence. Do not infer data or
   padding from a byte pattern alone.
4. Run `python3 matching2/tools/waves/match_crt.py --project matching2/msvc`
   when the toolkit/oracle is available. Deduplicate report rows by manifest
   address, record the report hash, and validate address, owner, and size.
5. Use source-domain provenance only for a recoverable queue. Keep unidentified
   entries on evidence hold until disassembly or a named source establishes
   ownership.
6. Use `exact_assembly_required` only for a repeated, address-specific proof
   that the current exact-output route cannot emit the observed bytes. Record
   the opcode/body signature, compiler experiments, and the next alternative
   route. Near misses remain recoverable/pending.
7. Before handoff, validate with
   `python3 -m json.tool matching2/reference/non_semantic_regions.json` and
   re-run the accounting check from the JSON summary. Never edit
   `matching2/msvc/regions.json`, build sources, or recovery code as part of
   ledger maintenance.

Every group has explicit revisit criteria in `revisit_catalog`. Reclassification
requires new positive evidence and a fresh snapshot; unchanged external state
or an ordinary failed source experiment is not a reason to promote an
irreducible label.
