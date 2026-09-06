# Coordinator semantic audit report

This report covers only the `coordinator` partition in
`semantic_exhaustive_audit_manifest.md`. The partition owns 81 whole source
files, 237 semantic addresses, and 99,351 tracked retail bytes. The manifest
is generated from `coverage.json`; the 693-function `function_registry.json`
is a Ghidra-export view and is not the exhaustive scope.

The audit records exact-address evidence. A source file or neighboring address
is not considered reviewed because one function in the file was reviewed.
Each row below must name the IDA pseudocode/disassembly and raw Ghidra evidence
actually inspected, then state the remaining contract boundary. Assembly
citations refer to `../ida/th10.exe.asm` line ranges.

The bounded audit stopped after Batch 2 at the user's direction. It records 36
unique coordinator addresses (21 grounded, 15 partial) out of the 237-address
coordinator partition; 201 coordinator addresses remain pending. The
trajectory pair `0x00404610`/`0x0044C350` is counted through the ending report
cross-reference below and was not re-audited here. The machine-readable
address ledger is `docs/semantic_audit_coordinator_results.json`.

## Criteria and verdict vocabulary

- `grounded`: control flow and relevant fields/constants agree across source,
  IDA pseudocode, IDA assembly, and raw Ghidra for the reviewed behavior;
  contract limits are still recorded.
- `partial`: a real slice is supported, but a material branch, owner, ABI, or
  side effect is missing or contradicted.
- `unresolved`: the local evidence is missing/corrupt or the source could not
  be compared responsibly in this batch.

Focused tests are validation evidence only. They do not upgrade a source to
grounded status without an independent retail comparison.

## Batch 1 — source and raw-reference inventory

Batch 1 is prepared from the first coordinator files in manifest order. The
address-level rows will be filled only after inspecting all four artifacts.

| Source | Addresses | Status |
| --- | --- | --- |
| `src/app/frame_clock.cpp` | `0x00439540`, `0x00439D20` | reviewed: grounded, grounded |
| `src/app/game_state_init.cpp` | `0x00445900` | reviewed: partial |
| `src/app/main_tasks.cpp` | `0x0041FF80`, `0x00420270`, `0x00420470`, `0x00420670`, `0x00420870` | reviewed: grounded, grounded, partial, partial, grounded |
| `src/archive/crypt.cpp` | `0x0044B0D0`, `0x0044B220` | reviewed: grounded, grounded |
| `src/archive/lzss.cpp` | `0x00435DC0` | reviewed: grounded |
| `src/archive/resource_manager.cpp` | `0x004356F0`, `0x00435800`, `0x004358E0` | reviewed: partial, partial, partial |
| `src/game/archive_cursor.cpp` | `0x0044DD40` | reviewed: grounded |
| `src/game/archive_cursor_read.cpp` | `0x0044DE10` | reviewed: grounded |
| `src/game/asset_buffer.cpp` | `0x0040B480` | reviewed: partial |

## Address-level findings

The exact evidence rows for this batch follow. Source line numbers identify the
implementation inspected; the two retail columns identify the matching IDA
pseudocode and raw Ghidra artifact. A host hook or conventional ABI is recorded
as a boundary where it is the only abstraction; it does not by itself lower a
verdict.

| Address | Source evidence | IDA pseudocode | IDA assembly | Raw Ghidra evidence | Verdict and remaining boundary |
| --- | --- | --- | --- | --- | --- |
| `0x00439540` | `src/app/frame_clock.cpp:10-33` | `../ida/th10.exe.c:53733-53767` | `../ida/th10.exe.asm:83190-83279` | `../decompiled/ghidra_raw/00439540_FUN_00439540.c:12-48` | **grounded**: critical-section, QPC/timeGetTime branches, wrap adjustment, minimum sample, and 1000/0.001 scaling agree. The hook supplies Win32 clock/lock calls; the host state collapses the retail split QPC frequency words. |
| `0x00439D20` | `src/app/frame_clock.cpp:87-127` | `../ida/th10.exe.c:54056-54103` | `../ida/th10.exe.asm:83861-84098` | `../decompiled/ghidra_raw/00439D20_FUN_00439d20.c:10-56` | **grounded**: all 19 render, 8 texture-stage, and 6 sampler writes agree in order and value, followed by manager byte writes. Device and manager ownership is delegated to hooks. |
| `0x00445900` | `src/app/game_state_init.cpp:22-129` | `../ida/th10.exe.c:62199-62867` | `../ida/th10.exe.asm:101319-102083` | `../decompiled/ghidra_raw/00445900_GameStateInit.c:12-519` | **partial**: entity tables, slot clears, matrix constants, entity binding, and final device call agree, but retail `memset(a1, 0, 0x732460)` (`IDA:62301`) is replaced by a bounded tail clear, and retail always creates/registers 2 primary plus 18 secondary nodes while source accepts caller counts and delegates node shaping. |
| `0x0041FF80` | `src/app/main_tasks.cpp:6-18` | `../ida/th10.exe.c:33033-33050` | `../ida/th10.exe.asm:45026-45075` | `../decompiled/ghidra_raw/0041FF80_FUN_0041ff80.c:12-31` | **grounded**: replay gate, input advance/device poll, busy result 4, callback result mapping 1/4, and mode-apply fallthrough agree. Hook fields represent the retail owner and callees. |
| `0x00420270` | `src/app/main_tasks.cpp:48-64` | `../ida/th10.exe.c:33133-33214` | `../ida/th10.exe.asm:45278-45396` | `../decompiled/ghidra_raw/00420270_FUN_00420270.c:12-93` | **grounded**: stop flag placement and the full release sequence agree. Resource/object/timer ownership is expressed as ordered hooks; retail null checks live inside those providers. |
| `0x00420470` | `src/app/main_tasks.cpp:20-46` | `../ida/th10.exe.c:33278-33325` | `../ida/th10.exe.asm:45502-45565` | `../decompiled/ghidra_raw/00420470_FUN_00420470.c:12-45` | **partial**: state initialization, primary failure gate, three secondary registrations, and priorities 1/40/50 agree, but retail writes each 0x24-byte node's flags/context/callback fields in this body; source delegates that shaping and callback identity to `create_node`. |
| `0x00420670` | `src/app/main_tasks.cpp:126-185` | `../ida/th10.exe.c:33327-33418` | `../ida/th10.exe.asm:45681-45862` | `../decompiled/ghidra_raw/00420670_FUN_00420670.c:12-104` | **partial**: wait, 640x480 bottom-up 32-to-24-bit copy, BMP dimensions, and writer handoff are represented, but return behavior is inverted (retail returns 0 on the supported path and 1 for unsupported formats), the retail header allocation is 0x2c plus in-object fields rather than one 0x36 buffer, and the writer/COM surface ABI is hidden behind hooks. |
| `0x00420870` | `src/app/main_tasks.cpp:67-124` | `../ida/th10.exe.c:33420-33495` | `../ida/th10.exe.asm:45868-46030` | `../decompiled/ghidra_raw/00420870_FUN_00420870.c:12-98` | **grounded**: defaults, 0x34-byte image copy, six mode checks, magic/size checks, accepted key publication, fallback defaults/logging, runtime-flag sequence, and write-failure -1 agree. The source clamps short-image copying for host safety; file/log/global ownership is hooked. |
| `0x0044B0D0` | `src/archive/crypt.cpp:57-106` | `../ida/th10.exe.c:66902-66989` | `../ida/th10.exe.asm:110537-110691` | `../decompiled/ghidra_raw/0044B0D0_FUN_0044b0d0.c:10-77` | **grounded**: temporary-size selection, signed processed-prefix formula, odd/even descending writes, rolling key, block/limit loop, cleanup, and return agree. Explicit size/block/limit parameters reify the retail ABI. |
| `0x0044B220` | `src/archive/crypt.cpp:108-155` | `../ida/th10.exe.c:66991-67076` | `../ida/th10.exe.asm:110697-110847` | `../decompiled/ghidra_raw/0044B220_FUN_0044b220.c:10-77` | **grounded**: inverse snapshot traversal, odd/even source order, rolling key, prefix/limit loop, cleanup, and return agree. Explicit parameters reify the retail ABI. |
| `0x00435DC0` | `src/archive/lzss.cpp:150-194` | `../ida/th10.exe.c:51069-51226` | `../ida/th10.exe.asm:77147-77387` | `../decompiled/ghidra_raw/00435DC0_FUN_00435dc0.c:10-147` | **grounded**: dictionary position 1, literal and back-reference bit order, 0x2000 mask, length +3, terminator offset 0, and output allocation agree. The source adds a typed input-size/output-size boundary around the retail pointer ABI. |
| `0x004356F0` | `src/archive/resource_manager.cpp:22-33` | `../ida/th10.exe.c:50639-50671` | `../ida/th10.exe.asm:76396-76508` | `../decompiled/ghidra_raw/004356F0_FUN_004356f0.c:12-76` | **partial**: slash-to-`.dat` normalization and linear name lookup agree, but retail searches the fixed global 0x4923B0/0x477850 table while source searches a local `DatArchive` array. Also, `src/platform/path.cpp:58-79` independently labels `Resource_ArchivePathForAsset` as `0x004356F0`, creating a duplicate address annotation that must be resolved before treating this address as uniquely owned. |
| `0x00435800` | `src/archive/resource_manager.cpp:56-70` | `../ida/th10.exe.c:50673-50713` | `../ida/th10.exe.asm:76528-76618` | `../decompiled/ghidra_raw/00435800_FUN_00435800.c:10-52` | **partial**: archive lookup, post-slash entry read, fallback open/size/read, and close are structurally present, but local archive/file abstractions replace the retail owner and the fallback source does not preserve the retail `Block` output argument through `sub_435580`. |
| `0x004358E0` | `src/archive/resource_manager.cpp:72-85` | `../ida/th10.exe.c:50715-50764` | `../ida/th10.exe.asm:76624-76712` | `../decompiled/ghidra_raw/004358E0_FUN_004358e0.c:10-48` | **partial**: archive size and fallback `GetFileSize` paths agree, but source uses local archives and `FileHandle` ownership instead of the retail global table and stack-polymorphic owner. |
| `0x0044DD40` | `src/game/archive_cursor.cpp:55-102` | `../ida/th10.exe.c:69001-69051` | `../ida/th10.exe.asm:115332-115409` | `../decompiled/ghidra_raw/0044DD40_FUN_0044dd40.c:10-49` | **grounded**: file/memory branches, invalid handle HRESULT, section base/write offsets, remaining-length updates, and SetFilePointer calls agree. Win32 `SetFilePointer` remains an external production ABI. |
| `0x0044DE10` | `src/game/archive_cursor_read.cpp:27-106` | `../ida/th10.exe.c:69053-69103` | `../ida/th10.exe.asm:115415-115518` | `../decompiled/ghidra_raw/0044DE10_FUN_0044de10.c:10-61` | **grounded**: file and memory branches, clamping, copy loops, cursor advance, HRESULTs, and the retail `ReadFile` bytes-read ABI reification agree. Source adds null checks and uses 64-bit pointer arithmetic on host builds. |
| `0x0040B480` | `src/game/asset_buffer.cpp:5-18` | `../ida/th10.exe.c:19536-19550` | `../ida/th10.exe.asm:14688-14742` | `../decompiled/ghidra_raw/0040B480_FUN_0040b480.c:10-50` | **partial**: load/free/publish ownership agrees, but retail clears `DAT_00497C38[0]` before `strcat` (`IDA:19541`, raw:21); source appends to the caller's existing shared buffer without that reset. |
| `0x00404610` | Cross-reference: `docs/semantic_audit_ending.md:16-57` | `../ida/th10.exe.c:14247-14455` | `../ida/th10.exe.asm:4613-4943` | `../decompiled/ghidra_raw/00404610_FUN_00404610.c:12-137` | **partial; audited in ending report**: do not duplicate. That report records matching timer/mode control flow with x87 conversion and typed-ABI boundaries. |
| `0x0044C350` | Cross-reference: `docs/semantic_audit_ending.md:59-78` | `../ida/th10.exe.c:67760-67874` | `../ida/th10.exe.asm:112589-112802` | `../decompiled/ghidra_raw/0044C350_FUN_0044c350.c:12-98` | **partial; audited in ending report**: do not duplicate. That report records matching mode-table control flow with extended-return and float-precision boundaries. |

## Batch 2 — bullet and indicator helpers

These rows cover the next coordinator files in manifest order. Two address
ownership collisions are recorded explicitly: `0x00402720` has both the
bullet-manager and game-state source annotations, and `0x004065C0` has both
the fixed-pool and generic relink source annotations. `0x00428160` is
implemented in `recovery_leaves.cpp` despite the manifest's
`effect_indicator_slots.cpp` source attribution.

| Address | Source evidence | IDA pseudocode | IDA assembly | Raw Ghidra evidence | Verdict and remaining boundary |
| --- | --- | --- | --- | --- | --- |
| `0x00402720` | `src/game/bullet_manager.cpp:399-425`; duplicate `src/game/game_state.cpp:81-128` | `../ida/th10.exe.c:12775-12822` | `../ida/th10.exe.asm:2014-2101` | `../decompiled/ghidra_raw/00402720_FUN_00402720.c:10-68` | **partial**: the bullet-manager body matches the retail gate, five recoil clears, normalization, eight primary/three overlay renders, scale restore, camera copy, and counter. The same exact address is independently annotated as `GameState_Update` with a competing direct implementation; this duplicate ownership is a material audit blocker. |
| `0x00404450` | `src/game/bullet_manager.cpp:285-307` | `../ida/th10.exe.c:14149-14200` | `../ida/th10.exe.asm:4463-4549` | `../decompiled/ghidra_raw/00404450_FUN_00404450.c:10-48` | **grounded**: scheduler flag enables, bank activation, record traversal/assignment, sprite registration hook, and cursor rewind agree. The sprite-construction ABI is represented by the host callback. |
| `0x00404F30` | `src/game/bullet_manager.cpp:335-347` | `../ida/th10.exe.c:14732-14750` | `../ida/th10.exe.asm:5489-5542` | `../decompiled/ghidra_raw/00404F30_FUN_00404f30.c:10-31` | **grounded**: base initialization, nine accumulator clears, scale bytes, slot id, and timer initialization agree. The typed timer hook absorbs the retail multi-register constructor ABI and discarded return pointer. |
| `0x00405300` | `src/game/bullet_manager.cpp:349-364` | `../ida/th10.exe.c:14830-14845` | `../ida/th10.exe.asm:5813-5831` | `../decompiled/ghidra_raw/00405300_FUN_00405300.c:10-22` | **partial**: active entry address, refresh, palette offset `+0xCC`, and selected index agree, but retail returns the device upload result while the promoted function is `void` and discards it. |
| `0x00405E20` | `src/game/bullet_manager.cpp:193-263` (also duplicate `:228-263`) | `../ida/th10.exe.c:15402-15441` | `../ida/th10.exe.asm:6952-7002` | `../decompiled/ghidra_raw/00405E20_FUN_00405e20.c:10-39` | **partial**: resource lookup, cursor/state setup, callback flags/owners, and failure result agree, but the source registers both nodes with priority `0`; retail uses priorities `20` and `29`. The file also contains two competing `0x00405E20` annotations. |
| `0x00405ED0` | `src/game/bullet_manager.cpp:265-281` | `../ida/th10.exe.c:15442-15454` | `../ida/th10.exe.asm:7008-7023` | `../decompiled/ghidra_raw/00405ED0_FUN_00405ed0.c:10-25` | **grounded**: animation rebind, complete pool zeroing, cursor reset, and state word `5` agree. Pool count and ownership are explicit host parameters; retail uses the fixed `0xF82BC` dword count. |
| `0x00406060` | `src/game/bullet_manager.cpp:309-333` | `../ida/th10.exe.c:15489-15519` | `../ida/th10.exe.asm:7148-7224` | `../decompiled/ghidra_raw/00406060_FUN_00406060.c:10-49` | **grounded**: `0x3E0B54` allocation, 0x7D1 vector construction at `+0x60`, full zero, global publication, initializer, failure destroy/free, and return agree. Allocation/constructor/destructor are host hooks. |
| `0x004065C0` | `src/game/bullet_manager.cpp:55-119` and duplicate `:366-397` | `../ida/th10.exe.c:15704-15771` | `../ida/th10.exe.asm:7649-7751` | `../decompiled/ghidra_raw/004065C0_FUN_004065c0.c:12-85` | **partial**: fixed 2000-slot admission, capture gate, six relink lists, clock thresholds, and return agree in the pool body, but a null `env->update_bullet` drops live records where retail always calls `0x00406240`; a second generic relink implementation owns the same address. |
| `0x0040C730` | `src/game/bullet_manager.cpp:427-439` | `../ida/th10.exe.c:20572-20587` | `../ida/th10.exe.asm:16636-16654` | `../decompiled/ghidra_raw/0040C730_FUN_0040c730.c:10-28` | **grounded**: flag clear, sentinel links, self pointer, cursor/head links, and zero counts agree. Pointer fields are represented with the host ring layout. |
| `0x00406240` | `src/game/bullet_runtime_update.cpp:17-84` | `../ida/th10.exe.c:15566-15703` | `../ida/th10.exe.asm:7362-7643` | `../decompiled/ghidra_raw/00406240_FUN_00406240.c:12-196` | **grounded**: destroy gate, modes 1/2/3 movement, behavior bits, delayed toggle, collision outcomes, target behaviors, lifetime/delay decrements, animation tick, and `-1` retirement agree. Behavior, collision, animation, and sound leaves are typed hooks. |
| `0x00419120` | `src/game/effect_indicator_queue.cpp:2` | `../ida/th10.exe.c:28154-28418` | `../ida/th10.exe.asm:34905-35335` | `../decompiled/ghidra_raw/00419120_FUN_00419120.c:12-213` | **grounded**: owner countdown, VM retirement/spawn styles 2/12, alpha and scale thresholds, anchor offsets, ten-slot rotation, text formatting, unlink, optional release, and queue iteration agree. VM/resource ownership is delegated through `EffectIndicatorOps`. |
| `0x004050D0` | Actual body: `src/math/timer.cpp:81-94` (manifest source attribution points at effect-indicator slots) | `../ida/th10.exe.c:14767-14788` | `../ida/th10.exe.asm:5622-5640` | `../decompiled/ghidra_raw/004050D0_FUN_004050d0.c:10-26` | **partial**: lazy sentinel initialization and disable writes agree, but retail always wires the first-use speed to global `&flt_476F78`; source accepts and stores an arbitrary caller `speed`, and the manifest/source ownership is inconsistent. |
| `0x00427B50` | `src/game/effect_indicator_slots.cpp:35-71` | `../ida/th10.exe.c:39054-39097` | `../ida/th10.exe.asm:55593-55668` | `../decompiled/ghidra_raw/00427B50_FUN_00427b50.c:10-59` | **grounded**: 32-slot scan, 0x6C wipe, flags, position/kind/argument, timer sentinel/countdown, mode/counter/limit/phase defaults, one-past-pool return, and constants agree. Pool ownership is explicit in the host layout. |
| `0x00427D80` | `src/game/effect_indicator_slots.cpp:73-79` | `../ida/th10.exe.c:39098-39120` (unnamed block between `sub_427D70` and `sub_427DF0`) | `../ida/th10.exe.asm:55808-55819` | `../decompiled/ghidra_raw/00427D80_FUN_00427d80.c:10-19` | **grounded**: both pair components are read before stores and multiplied by the scalar. The raw/IDA symbol boundary is unnamed in IDA pseudocode but exact in assembly/raw export. |
| `0x00427E90` | `src/game/effect_indicator_slots.cpp:82-179` | `../ida/th10.exe.c:39146-39330` | `../ida/th10.exe.asm:55929-56205` | `../decompiled/ghidra_raw/00427E90_FUN_00427e90.c:12-135` | **grounded**: exclusivity gate, first inactive slot, timer initialization, source/player origin, polar carry path, primary/secondary VM setup, flag propagation, callback, sound, and zero return agree. VM list lookup/creation is a typed host boundary. |
| `0x00428160` | Actual body: `src/game/recovery_leaves.cpp:691-708`; manifest attributes it to `src/game/effect_indicator_slots.cpp` | `../ida/th10.exe.c:39331-39353` | `../ida/th10.exe.asm:56211-56261` | `../decompiled/ghidra_raw/00428160_FUN_00428160.c:10-37` | **partial**: retail derives difficulty bucket from `DAT_00474C48`, selects one of ten tables at manager `+0x45C`, and calls `0x00427E90`; source instead accepts an external schedule/count and dispatch callback. This is a confirmed behavior/ownership mismatch, not merely an ABI adapter. |
| `0x0042A930` | `src/game/effect_indicator_slots.cpp:17-33` | `../ida/th10.exe.c:41232-41252` | `../ida/th10.exe.asm:59853-59878` | `../decompiled/ghidra_raw/0042A930_FUN_0042a930.c:10-26` | **grounded**: first-use sentinel, global speed pointer, initialized bit, current/target frame values, and float image store agree. The timer pointer is explicit in the host API. |
