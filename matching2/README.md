# Documented matching reimplementation

This tree contains readable C++ reconstructions of game functions. Compile with
the original MSVC 7.1 code-generation settings.

## Source architecture

`matching2` is organized by runtime subsystem rather than original address:

```text
include/th10/
  archive/    DAT headers, entry layouts, cipher, and compression interfaces
  game/       Entity, game-state, player, and scoring layouts
  platform/   Win32-compatible types and ABI declarations
  script/     ECL instruction and VM layouts
  util/       ABI-compatible containers and allocation owners
src/
  archive/    DAT ownership, registry, encryption, and LZSS codecs
  game/       Gameplay object lifecycle and state transitions
  math/       Timers, vectors, and numeric helpers
  platform/   Win32 window and process integration
  render/     Direct3D initialization and rendering state
  script/     ECL virtual machine implementation
  util/       Heap ownership and legacy container operations
tools/        COFF comparison and fixed-address hybrid PE builder
```

The separate `matching/` tree remains address-oriented because it is the
byte-exact assembly oracle. New readable implementations belong in `matching2`
under their owning subsystem.

## Runnable hybrid build

The current reimplementation is built as a hybrid PE. The original executable
provides functions and data that have not been reconstructed yet; verified
functions compiled from this directory are overlaid at their original virtual
addresses. The builder rejects any overlay whose non-relocation bytes differ.
This maintains a playable checkpoint throughout the decompilation instead of
waiting for the complete function and global-data layout to be recovered.

```bash
./build.sh
./test.sh
./run.sh
```

Coverage is generated from the union of Ghidra's tracked-function index and
the verified hybrid overlay list:

```bash
python3 tools/coverage_report.py --write
python3 tools/coverage_report.py --check
```

The machine-readable raw-function registry connects every successful Ghidra
export to its address, pseudocode file, current recovery status, promoted C++
source, and exact overlay metadata when applicable:

```bash
python3 tools/function_registry.py --write
python3 tools/function_registry.py --check
```

`function_registry.json` is generated directly from the Ghidra index and the
same in-memory evidence used by the coverage ledger. This makes it safe to use
for tooling without treating raw pseudocode as a build input.

Standalone progress is tracked separately from broad recovery coverage:

```bash
python3 tools/standalone_readiness.py --write
python3 tools/standalone_readiness.py --check
```

The generated `standalone_readiness.json` follows the direct game-owned call
closure from `GameMain` and the indirectly scheduled title initializer. A
reachable function counts as source-ready only when it has semantic C++ or an
exact overlay. The report gives both function-count and retail-byte-weighted scores,
ranks unresolved functions by the number of reachable callers they block, and
counts indirect/virtual call sites that still require manual target auditing.
Standalone completion requires zero retail-backed functions, zero unaudited
indirect sites, a retail-free link target and executable, and a passing runtime
smoke test. System DLL imports remain ordinary host dependencies.
Because retail `GameMain` contains initialization, the main loop, and teardown
in one function, its static closure conservatively includes some shutdown work
that execution does not reach before the title screen; the report records this
deliberate over-approximation rather than presenting it as an exact trace.

The generated `coverage.json` classifies every tracked address as unrecovered,
researched, partial, semantic C++, or an exact overlay. Source annotations and
the overlay tuple are authoritative; build artifacts are deliberately excluded
so the ledger is reproducible from a clean checkout. It also reports semantic
and exact retail-byte totals plus progress in tiny, small, medium, and large
function-size bands.

Use the repository-evidence candidate ranker to select a dependency-first batch:

```bash
python3 tools/rank_candidates.py --limit 30
python3 tools/rank_candidates.py --subsystem animation_manager
```

The score favors bounded leaf functions, recovered address neighborhoods,
matching assembly, and an existing subsystem test harness, while penalizing
unresolved Ghidra callees. Its subsystem label is inferred from the nearest
recovered function and is a triage hint rather than a recovered symbol name.

`build.sh` verifies the supported retail executable by SHA-256 and writes
`build/th10_reimpl.exe`. `run.sh` exposes the retail `th10.dat`, `thbgm.dat`, and
configuration through symlinks beside the rebuilt executable, then starts it
under Wine. Override the defaults with `TH10_ORIGINAL_EXE` and `TH10_GAME_DIR`.
Every C++ translation unit under `src/` is compiled on each build; duplicate
basenames are rejected so object selection remains deterministic.
`test.sh` runs host-side semantic tests for cleaned portable algorithms. The
current suite checks the retail `th10.dat` header cipher and decoded metadata,
the retail content-cipher parameter table, filename-based cipher selection and
round-trip decoding, packed entry-table parsing and lookup, plus literal and
overlapping-reference LZSS streams. The cleaned encoder is checked against a
deterministic back-reference vector and round-tripped through the decoder. A
fully synthetic DAT archive additionally
tests backend ownership, index loading, sentinel construction, reopening,
named asset reads, and cleanup as one end-to-end path.
The file/resource boundary now also tracks executable-relative path resolution
at `0x00435610`, the retail LZSS decoder at `0x00435DC0`, and the complete
ResourceFile destructor chain at `0x00436680`. Focused tests cover drive-qualified
paths, executables without a directory component, copied RCDATA ownership,
missing resources, and exactly-once buffer release.
The shared-file open leaves at `0x0044B620` (create/truncate for writing) and
`0x0044B6B0` (sequential open for reading) complete the probe/write/read
family; both publish the shared handle, hold the file-system critical-section
depth on success, and unwind it through the error hook on failure.
The next IDA-guided continuation promotes queued text rendering at `0x00401760`, including camera/view transitions, both font banks, proportional and fixed advances, newline behavior, half-alpha shadow passes, and final view restoration; focused tests cover glyph selection and exact draw positions.
The IDA-guided continuation promotes the descriptor-driven watch/effect spawner at `0x00427E90`, including its 128-slot scan, mode-3 source exclusivity, timer initialization, polar placement, animation VM creation, callback, and sound paths; focused tests cover exclusive and non-exclusive descriptors.
The latest recovery batch adds transparent-pixel border repair at `0x00436DA0` for both BGRA and A4R4G4B4 surfaces, plus the shared-path asset-buffer replacement helper at `0x0040B480`; focused tests cover neighbour averaging, row bounds, 16-bit nibble conversion, path composition, and exactly-once replacement ownership.
The following recovery batch reconstructs the six-channel particle seed combiner at `0x00404E10` and the urgent stage-tip creation path at `0x00424650`; tests cover float-channel addition, four independent RNG bytes, active-list aging, duration clamping, and highlighted tip style.
The floating-score ring writer at `0x0042B9C0` is now reconstructed with its 720-entry wrap, least-significant-first decimal encoding, minus glyph, lazy timer initialization, position copy, and color publication; dedicated tests cover positive, zero, negative, wrap, and timer-reuse paths.
The next large-leaf batch reconstructs manager cleanup dispatch at `0x0041C850`, format-specific alpha inversion at `0x00437160`, and locked-surface transparent-color repair at `0x004465B0`; tests cover mutation-safe list walking and BGRA/A1R5G5B5/A4R4G4B4 paths.
The latest continuation reconstructs queued text rendering at `0x00401A50`,
centered formatted debug text at `0x00447BB0`, and the live/replay input step at
`0x004297D0`. Focused tests cover font-bank transitions, spaces and newlines,
scaled glyph selection, default debug font sizing and centering, held-input
repeat conversion, analog sampling, and six-byte replay packet advancement.
The utility coverage also exercises inline and allocated `LegacyString`
assignment, substring aliasing, erase, reserve/shrink, ownership checks, and
termination without depending on the retail CRT.
Render coverage exercises reset-target release, lost-device recovery, and
numbered screenshot selection without launching the game.
Scheduler coverage checks callback construction, replacement handling, and
priority-ordered insertion into both retail callback lists.
The secondary scheduler factory at `0x0044A030` is also reconstructed; its
owned zero-priority callback path is covered through registration and teardown.
Primary and secondary scheduler dispatch (`0x00449C00` / `0x00449D40`) now walk
live callback chains, honor callback result codes, and safely retire callbacks
while preserving iteration.
Gameplay-runtime coverage checks fractional/normal/reverse frame-timer
advancement, animation lookup across both manager lists, shared-position
updates, pool allocation, handle registration, and player animation creation.
The owner-aware timer disable at `0x0042C5C0` is now available as
`GameState_DisableTimerWithOwner`, complementing the existing
`0x0042C620` target setter; the test exercises both the first-call sentinel
initialization and the post-init field reset.
The game-thread queue append at `0x00401530` is now typed with bounded 256-entry
insertion, record-name copying, and propagation of the thread's state words.
Its formatted companions at `0x00401630` and `0x00401690` now cover bounded
formatted names and the marked-record variant.
It also covers root-to-child propagation, stop-frame updates, script restart,
generic flag changes, resource retirement, handle validation, child lookup,
and pooled-object removal. Ghidra-guided tests also cover the animation
interpreter's integer and float variable banks, writable operand resolution,
base-position operands, and literal/fallback behavior.
The score gauge add-with-minimum at `0x00412E70` is now exposed as
`ScoreGauge_AddWithMinimum`, clamping the result to 5000 so the gauge
never empties below the retail baseline. The score-runtime test exercises
the clamp with a sub-baseline value, a healthy add, and a second drop.
The two byte-identical viewport predicates at `0x0041F7A0` and `0x00428D70`
are now available as `Position_IsPartiallyInViewport`, returning 0 when a
position with the supplied radii is at least partially on screen and 1
when every edge is off-screen. The dedicated harness exercises the four
off-screen edges and confirms a tightly-bound position straddling the
left/top border is still reported as visible.
The ECL operand wrapper at `0x00412A00` is now available as
`ECL_ResolveIntFromEntity`, pulling the cursor from the VM state stored
at `entity+0x14D8` and delegating to the existing `ECL_ResolveIntOperand`.
The clean API removes the hidden manager pointer convention.
Animation resource-record configuration at `0x0043E5A0` is now typed, including
readiness gating, metadata selection, transform defaults, and derived extents.
The standalone ECL operand family at `0x0044FDB0` through `0x0044FF80` now
uses conventional typed entry points for instruction-backed and pre-decoded
integer/float values. Its dedicated harness verifies mask-controlled literals,
local-variable addressing, virtual external-variable resolution, typed stack
conversion, pop order, and empty-stack fallbacks.
The large dispatcher at `0x0040E770` is explicitly tracked as partial while
its recovered flag, boundary, difficulty, and range leaf cases coexist with
the remaining retail-backed opcode families.
The next stateful leaf batch covers opcodes `0x14A`, `0x14B`, and `0x15A`:
high-bit difficulty remapping, shared difficulty-state reset, and squared
float assignment. Tests exercise the manager-wide reset fields and negative
input squaring through the real dispatcher entry point.
Opcode `0x15B` is now included in that typed batch; it evaluates the integer,
float, and slot operands in retail order and writes the normalized pair into
the shared difficulty table.
The batch now also covers `0x15D–0x15F`, including all stage-progress threshold
branches, writable float destinations, and the normalized interpolation curve.
It now extends through `0x164`, adding integer threshold selection,
signed integer interpolation, and difficulty-mode integer/float selection with
typed writable destinations.
The bounded global/action pair `0x168–0x169` is also reconstructed: the first
writes the shared difficulty slot and the second resolves and forwards its
integer operand to the gameplay action hook.
The gameplay animation shorthands at `0x0040C480` and `0x0040C4D0` now resolve
their handle through the global animation manager and propagate stop frames 2
and 3 across root animations and their direct children.
The shared encrypted-text transform used by `0x165–0x167` is now available as
`ECL_DecodeEncryptedString`, with the retail `0x77` seed and increasing-step
XOR sequence covered by a deterministic round-trip test. The surrounding
branches remain partial because they orchestrate animation, score, and external
text-state dependencies.
Registration coverage now exercises front and back insertion in both the
primary and secondary manager lists, including head/tail repair after removal.
Per-frame coverage walks both active lists, removes retired objects without
invalidating iteration, invokes update/draw callbacks, distributes primary
objects into 19 render buckets, queues secondary objects in bucket 19, and
renders the resulting chains.
The bullet subsystem now also has a typed 0x18-byte `BulletManagerState` that
the matching2 recovery tracks end-to-end. `BulletManager_Create` (`0x0040AF90`)
zeroes the state, marks it initialized, publishes it through the global
pointer, and asks `BulletManager_LoadScripts` (`0x0040AE70`) to look up
`bullet.anm` and register the primary/secondary scheduler callbacks that
fire on every tick. `BulletManager_Release` (`0x0040AF00`) retires both
callbacks inside the scheduler critical section and clears the global
pointer. A dedicated host harness drives the success path (resource
present, both callbacks linked into the correct primary/secondary lists at
the right priorities, the manager-wide flag set, the global pointer
published) and the missing-resource path (no callbacks registered, global
pointer cleared) without depending on the retail binary.
Bullet animation-resource retirement at `0x0040CEA0` is now typed as well: it
sets the bullet state bit, forwards the active animation handle to the shared
removal hook, and clears that handle after dispatch.
The math subsystem now includes the complete retail random-number generator
family behind a typed six-byte `RngState` (16-bit seed at +0x00, 32-bit
generation counter at +0x04). Every entry performs the 16-bit
linear-congruential step (XOR `0x9630`, subtract `0x6553`, multiply-and-fold)
verified against the retail disassembly: `Rng_NextU32` (`0x0044B9E0`) advances
twice and returns both outputs packed as `(first << 16) | second`,
`Rng_NextU32DoubleStep` (`0x0044BA80`, no surviving retail caller) advances
four steps while returning the first pair, `Rng_NextFloat` (`0x0044BB20`)
scales the unsigned output by 2^-32 for `[0, 1)`, and `Rng_NextFloatSigned`
(`0x0044BB90`) scales by 2^-31 and shifts by 1.0 for `[-1, 1)`. The float
leaves reproduce the retail x87 conversion (signed load with a 2^32 bias for
negative values, exact power-of-two scaling, single final rounding) by
evaluating in double; the dedicated harness checks the full zero-seed
sequence and the exact result bit patterns. The adjacent angle-wrapping pair
is typed as `Angle_Normalize` (`0x0044BC70`) and `Angle_NormalizeSum`
(`0x0044BC10`), folding their input into `[-pi, pi]` with the retail 0x20
iteration cap shared across both adjustment loops.
Menu navigation now has a typed 0xD8-byte `MenuCursor`:
`MenuCursor_Advance` (`0x0044BEA0`) moves the position by the requested
delta, wraps or clamps at the item-count boundary according to the mode flag,
and bypasses any position listed in the 16-entry skip table by advancing
again. The pause, title, and practice menu handlers drive their selection
through this leaf on every up/down input edge; coverage exercises wrapping,
clamping, single and consecutive skips, skip entries at the wrap boundary,
and the empty-list no-op.
The persistent progress block at `DAT_0047783c` gains its first two typed
leaves. `GameProgress_HasAnyPlayRecord` (`0x0042C850`) reports whether any of
the six main shot-type record flags at `+0x1D888` is set — the main-menu gate
disables its stage-practice item while the answer is no.
`GameProgress_UnlockAllStages` (`0x0042C8C0`) sets all sixteen shot-type
record flags at `+0x1D882` and marks the first six 8-byte stage records in
every per-shot-type 0x437C-byte table at `+0x4E9`, reproducing the hidden
key-sequence effect from the practice menu; retail's four redundant store
passes per table are preserved.
The archive cipher recovery now covers both directions. `Dat_Decrypt`
(`0x0044B0D0`) uses the retail signed processed-prefix calculation, including
the odd-size trailing-fragment case, while `Dat_Encrypt` (`0x0044B220`)
implements its inverse interleaving and rolling XOR. Exact small vectors,
multi-layer round trips, and the 69-byte parity edge are covered by the host
harness. The file family also includes `File_WriteWholeFile` (`0x0044B540`),
which models create, complete/short write, error reporting, close ownership,
and critical-section depth unwinding on every path.
The startup diagnostics buffer at `DAT_00474F70` is represented by the typed
`TextLog`: `TextLog_Append` (`0x0044B810`) and `TextLog_AppendLine`
(`0x0044B8E0`) format and append under the retail lock, enforce the cursor's
0x2000-byte boundary, and preserve the dirty-flag behavior. Two additional
platform leaves are readable: `Platform_GetOsVersionCode` (`0x0044BD10`)
maps `GetVersionExA` results to the game's legacy numeric codes, and
`TimerWin32_Release` (`0x004203C0`) kills an active multimedia timer and
reproduces retail's duplicated `timeEndPeriod` call.
A final low-dependency leaf batch raises readable coverage past 40%. It
includes the game-thread and ECL forwarding wrappers at `0x00401520` and
`0x00412AA0`; deleting-destructor wrappers at `0x0040CC50` and `0x0044CF00`;
the score intrusive-list insertion at `0x00413200`; ECL resource-slot setup
at `0x00412720`; nine-record animation activation at `0x00413790`; embedded
timer and path resets at `0x00412DB0` and `0x00417800`; circular and
elliptical polar-vector leaves at `0x00441EF0` and `0x00413270`; and the
platform interface invocation/aggregation leaves at `0x0044D5D0` and
`0x0044D550`. A focused host harness covers callback ordering, ownership
flags, list repair, conditional slot writes, record boundaries, reset
sentinels, vector results, missing-interface errors, and aggregated statuses.
The next blocker-focused pass adds the complete piecewise animation easing
table at `0x0044C350` as `Easing_Evaluate`, including quadratic through
quartic ease-in/ease-out modes and the constant/default selectors. It also
adds `AnimationManager_ReleaseResourceBatch` (`0x00447810`), which performs
owner synchronization, per-entry interface/resource retirement, and the
auxiliary allocation releases in retail order. Runtime tests pin the easing
branches and verify release/free ordering and idempotent empty cleanup.
The following timer-adjacent leaves are now typed as well: the rounded
three-lane scalar sampler at `0x00441E50` (`RandomVector_StoreRoundedScalar`)
and the embedded timer disable/reset at `0x004050D0`
(`EmbeddedTimer_Reset`). Their tests cover positive and negative rounding,
sentinel initialization, speed-pointer publication, and repeat-reset behavior.

The current recovery pass reaches the 50% function-count milestone: 361 of
the 722 tracked retail functions are readable semantic C++ or verified
overlays. The added low-dependency leaves cover timer/state setters, interface
array selection and teardown, resource/path helpers, animation slot lifecycle,
packet and schedule dispatch, color/tint setup, and callback-backed allocation
and device-reset paths. The standalone-readiness report remains separate: the
retail-free link, executable, and startup-to-title smoke gates are still open.

The supported original executable has SHA-256:

```text
2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040
```

The current overlays are byte-identical, so the resulting PE is still identical
to that retail executable. As readable implementations are completed, this
provides the fixed-address integration point for replacing retail code safely.

## Manual function comparison

Compile an individual source file with:

```bash
mkdir -p build
WINEDEBUG=-all wine "$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003/bin/cl.exe" \
  /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
  "/I$(winepath -w include)" "/Fo$(winepath -w build/entity.obj)" \
  "$(winepath -w src/game/entity.cpp)"
```

Compare a single COFF COMDAT function against its original virtual address with
the relocation-aware comparison tool:

```bash
python3 tools/compare_obj.py build/entity.obj Entity_Destructor 0x401FF0
python3 tools/compare_obj.py build/entity.obj Entity_Constructor 0x402050
python3 tools/compare_obj.py build/entity.obj Entity_Init 0x401DE0
python3 tools/compare_obj.py build/entity.obj DestroyEntityList 0x438A30
```

The comparison length is the compiled function's section size. Relocation
operands are excluded because their final values are assigned by the linker.
The Win32 file abstraction also has its retail eight-slot vtable typed in C++;
the adjacent whole-file loader (`0x00435580`) is readable and functional, but
is not overlaid yet because its optimized cleanup-block ordering is not an
exact code-generation match. Module-relative/absolute path resolution
(`0x00435610`) and the `r`/`w`/`a` open path (`0x00435370`) are reconstructed
behind the same interface. `DatArchive` now models the retail four-field owner
layout and connects that backend to header/index loading and entry extraction.
The adjacent `BufferFile` and embedded `ResourceFile` vtables are typed too,
and the 20-slot resource manager resolves `archive/entry` paths through loaded
DAT files before falling back to ordinary disk files.

Current exact-overlay results with MSVC 7.1:

| Function | Comparable bytes | Result |
|---|---:|---:|
| `Entity_Destructor` | 30 | 100% |
| `Entity_Constructor` | 88 | semantic C++ |
| `EntitySecondaryResource_Release` | 30 | 100% |
| `EntityAnimation_Release` | 30 | 100% |
| `Entity_AttachResourceSnapshot` | 56 | 100% |
| `BulletSpawnParameters_Initialize` | 23 | 100% |
| `HeapBuffer_Release` | 22 | 100% |
| `HeapBuffer::HeapBuffer` | 9 | 100% |
| `FileHandle` scalar deleting destructor | 22 | 100% |
| `FileHandle::~FileHandle` | 34 | 100% |
| `FileHandle::Close` | 30 | 100% |
| `FileHandle::Read` | 53 | 100% |
| `FileHandle::Write` | 59 | 100% |
| `FileHandle::Tell` | 21 | 100% |
| `FileHandle::GetSize` | 17 | 100% |
| `FileHandle::Seek` | 33 | 100% |
| `FileInterface::~FileInterface` | 3 | 100% |
| `FileInterface` scalar deleting destructor | 23 | 100% |
| `BufferFile::Write` | 5 | 100% |
| `BufferFile` scalar deleting destructor | 22 | 100% |
| `BufferFile::~BufferFile` | 37 | 100% |
| `BufferFile::Close` | 33 | 100% |
| `BufferFile::Read` | 108 | 100% |
| `BufferFile::Tell` | 7 | 100% |
| `BufferFile::GetSize` | 4 | 100% |
| `ResourceFile` scalar deleting destructor | 22 | 100% |
| `LegacyString_Clear` | 34 | 100% |
| `LegacyString::Length` | 4 | 100% |
| `LegacyString::Data` | 14 | 100% |
| `LegacyAllocator::Deallocate` | 10 | 100% |
| `LegacyAllocator::MaxSize` | 6 | 100% |
| `LegacyString::OwnsPointer` | 57 | 100% |
| `LegacyAllocator::Allocate` | 12 | 100% |
| `RuntimeAllocationPool_Initialize` | 22 | 100% |
| `DestroyEntityList` | 43 | semantic C++ |
| `Entity_Init` | 273 | semantic C++ |
| `BulletManager_Release` | 144 | semantic C++ |
| `BulletManager_Create` | 384 | semantic C++ |
| `BulletManager_LoadScripts` | 144 | semantic C++ |
| `StageTip_Initialize` | 51 | partial; 45 matching bytes |
| `Vector2::SetPolar` | 28 | semantic; separate `FSIN`/`FCOS` scheduling |
| `LegacyString::Assign` | 28 | semantic; equivalent null scan |
| `LegacyString::AssignRange` | 213 | semantic; SSO, alias, growth, and copy paths |
| `LegacyString::AssignSubstring` | 247 | semantic; external and self-substring paths |
| `LegacyString::Erase` | 103 | partial; exact validation and range clamp |
| `LegacyString::SetLength` | 31 | partial; 29 matching bytes |
| `LegacyString::Grow` | 160 | semantic; retail capacity policy and ownership |
| `LegacyString::Reserve` | 181 | semantic; growth and heap-to-inline shrink paths |
| `D3DResourceList_ReleaseResources` | 78 | semantic; synchronized D3D release walk |
| `D3DResourceManager_Destroy` | 51 | semantic; worker and two-list cleanup |
| `GameRenderTargets_Release` | 57 | semantic; capture and primary reset targets |
| `Render_HandleDeviceResetAndSnapshot` | 156 | semantic; reset and snapshot dispatch |

`Entity_Constructor`, `Entity_Init`, and `DestroyEntityList` are kept as
readable semantic C++. They are not hybrid overlays because reproducing their
retail register allocation would require handwritten naked assembly; the
hybrid executable continues to use the verified retail bodies at those
addresses.
The gameplay layouts now also include the complete 0x1F8-byte bullet spawn
parameter record and the 0x88-byte linked stage-tip record used by the stage
text parser. Polar-to-Cartesian vector initialization is readable C++ as well;
the retail build combines the two trigonometric operations into `FSINCOS`.
The entity block at `+0x23C` is now a named 4x4 local transformation matrix,
followed by its world and backup matrices, rather than sixteen unrelated offset
stores. Identity initialization retains retail's reverse store order so the
MSVC function extent remains 273 bytes with limited scheduling differences.
The six-component math record at `0x00404DA0/0x00404D40` is typed as a float
vector with four quantized trailing bytes. Earlier notes incorrectly called
the helper at `0x00463B2C` a random-number generator and misnamed
`0x00404D40` as addition; it is float-to-int conversion after subtraction.
`LegacyString` now covers both null-terminated and explicit-range assignment,
including self-referential input, small-string storage, growth, and termination.
Its substring, erase, capacity-growth, storage-selection, and allocator helpers
are reconstructed too, removing the remaining retail dependencies from normal
string mutation paths.
The `GameMain` allocation registry is now a typed 0xA004 owner with matching
initialization and complete shutdown cleanup. The adjacent 0x48 D3D resource
manager models both embedded lists, synchronized resource release, worker
shutdown, and list reset behavior.
The first 0x4C bytes of `GameStateManager` are now modeled as the two signed
render-target handles plus their recreation parameters. The device-reset path
releases both targets, performs lost-device recovery, and selects the first
free `snapshot/thNNN.bmp` filename before dispatching capture.
The callback scheduler now has a typed 0x24-byte callback record and explicit
primary/secondary priority-list insertion. `GameThread` and `GameState`
creation pass their object pointers and priorities normally instead of relying
on hidden EAX/ESI/EDI state, load their callback chains, and propagate
initialization failures. Player collision, update, draw, animation positioning,
and bullet spawning likewise use explicit typed arguments; bullet allocation
now runs the recovered 0x2518-byte initializer before copying spawn parameters
and linking the entity into its manager.
The player path no longer relies on retail shims for its five-word frame timer
or basic animation-manager operations. The 4,096-object animation pool,
fallback allocation, primary handle list, nonzero handle generation, script
selection/reset, child-position propagation, and translated player-animation
creation are readable C++ now. The large animation instruction interpreter at
`0x0043EE30` remains the downstream dependency for actually executing the
selected script.
The three operand helpers immediately before that interpreter are now readable
C++: `0x0043EC70` reads IDs 10000 through 10009 from four integer variables,
four float variables, and two extra integer variables; `0x0043EDA0` resolves
writable integer operands; and `0x0043ED00` resolves writable float operands,
including IDs 10013 through 10015 for the base-position vector. These names
replace unexplained accesses at entity offsets `+0x30C` through `+0x33C` while
retaining explicit retail-offset accessors for 32/64-bit test portability.
Cross-checking the interpreter with the renderer and sprite-selection helper
also identifies the early transform/timing block: rotation and angular
velocity at `+0x24..+0x38`, scale and scale velocity at `+0x3C..+0x48`, sprite
dimensions at `+0x4C/+0x50`, wrapped UV scroll at `+0x54/+0x58`, and frame
timing at `+0x5C..+0x68`. The late runtime block now names the start frame,
sprite/script indices, script base and instruction cursor, and sprite metadata
at `+0x380..+0x394`.
The ECL dispatcher now has the verified 0x14-byte TH10 instruction header and
typed cursor indirection and readable float-operand resolution for literals,
locals, external variables, and argument-stack values. Hitbox dimensions,
flag set/clear, movement-boundary setup/clear, and difficulty-slot reset
(`0x140` through `0x146`) are readable leaf operations. Integer operand
resolution, difficulty-slot assignment, and range parameters extend that
contiguous cluster through `0x148`; the remaining opcode families still
execute from the retail image.
The surrounding handle API is now broader than that initial creation path:
animation stop frames can be changed with or without immediately running the
script, arbitrary object flags propagate through root child lists, resource
owners can be retired across both manager lists, stale handles are cleared,
children can be selected by script index, and removal detaches both embedded
list memberships before releasing pooled or fallback storage.
All four retail registration variants (`0x004489D0`, `0x00448A50`,
`0x00448AC0`, and `0x00448B40`) share one typed list/insertion API. The
state-preserving script loader at `0x0043E7E0` and child-object setup wrapper at
`0x00449870` are reconstructed as well, preserving existing entity state while
resetting script cursors, timers, transform fields, and interpreter markers.
The manager update functions at `0x00448860` and `0x00448900` are now readable
C++ too. They preserve the retail ordering of callback execution, script
advancement, completion removal, active-object accounting, and render-chain
construction. The adjacent `0x00448980` bucket walk dispatches draw callbacks
and the downstream object renderer while skipping objects marked for removal.
The animation-owned lifecycle around those loops is reconstructed as well.
Initialization now expresses the final state produced by `GameStateInit`'s
full 0x732460-byte clear, establishes its render-target and runtime defaults,
and initializes all 4,096 pooled entities. Shutdown reproduces `0x00446220`:
both active lists are drained safely through the normal remover, the 20 render
bucket sentinels and complete pool are destructed, and the manager-owned buffer
at `+0x3AD488` is released. Scheduler callback registration remains in the
larger `GameStateInit` function and is the next boundary around this lifecycle.
The animation-manager boundary now also maps twenty additional retail entry
points from `0x00446220` through `0x00449870`. These include the four
primary/secondary front/back creation variants, positioned creation, pooled
and fallback removal, both stop-frame forms, root/child flag propagation,
translated positioning, resource retirement, sprite-selection wrappers,
child lookup, script-state initialization, and complete manager teardown.
The single-slot resource cleanup at `0x004477D0` now validates its 33-entry
index, releases and frees populated slots, and clears their ownership pointer.
The render preparation wrapper at `0x00443F80` now returns `-1` on preparation
failure and forwards successful setup to the normal draw callback.
The resource chunk walker at `0x0043D250` now scans bounded length-prefixed
four-byte records, returning the matching payload and size safely.
The render reset leaf at `0x00444580` now restores all four scale factors to
identity, with direct coverage of the reset values.
The embedded timer target setter at `0x0042C620` now stores the owner value,
initializes the timer sentinel on first use, and applies the requested target.
The paired animation-slot leaves at `0x0042C730` and `0x0042C750` now forward
indexed handles from the state block at `+0x2C4` through typed dispatch hooks.
The nullable owner cleanup at `0x00418150` now runs an injected cleanup hook
before releasing the allocation, while preserving null no-op behavior.
The explicit-delta timer advance behind `0x00428DD0`/`0x0044BF40` now preserves
previous/current ordering and applies speed-scaled accumulation.
The worker deleting destructor at `0x0044C100` now restores its vtable, stops
the worker, and conditionally releases the object allocation.
The resource basename lookup at `0x0043D2A0` now strips slash/backslash
prefixes and searches fixed-stride name tables with bounded comparisons.
The secondary nullable destructor at `0x0042CDB0` now has an address-specific
typed cleanup/free wrapper with the same null-safe ownership ordering.
The COM interface leaf at `0x0044D5B0` now returns `0x800401F0` for missing
interfaces, clears its status field, and invokes present interfaces via a hook.
The small digit-triplet dispatcher at `0x004054B0` now emits the requested
value followed by its decimal tens and ones animation indices.
The final bounded manager wrapper at `0x004496D0` and its dependency at
`0x0043E8B0` now switch an existing object to another script while preserving
the entity allocation. The semantic form retains the retail no-op behavior for
missing scripts and resources that are still loading, resets the script runtime
fields in retail order, runs the instruction interpreter, and updates the
manager script-run counter.
The Win32 boundary now uses typed `WNDCLASSA`, `STARTUPINFOA`, and a conventional
four-argument window procedure. Window creation receives its `HINSTANCE`
explicitly instead of relying on hidden EBX state, and MIDI output-completion
cleanup likewise exposes the retail EDX/ESI inputs as ordinary arguments.
Run-score accumulation at `0x00409D90` is modeled by `GameScore::AddScaled`,
including divide-by-ten awards and saturation at 999,999,999. The adjacent
`0x00409E20` callback retirement helper is typed too. Startup handling now
models the shell-link COM interfaces, resolves chained `.lnk` targets with
explicit arguments instead of hidden EBX/EDI state, and detects replay paths
relative to the running executable.
The score-object constructor at `0x0041C030` is also reconstructed, including
its bulk state clear and scheduler-sentinel initialization.
The extended score/entity constructor at `0x0041C5B0` now clears both embedded
entity blocks and restores their end markers and construction flags.
Its paired teardown at `0x0041C1C0` now retires the two callback slots and
drains owned score records through explicit cleanup hooks.
The score activation transition at `0x00408030` now models phase gating,
geometry-result branching, spawn dispatch, and scheduler-link initialization.
The deterministic joystick-button encoding core of `0x0044A4E0` is exposed as a
typed helper, mapping all 32 button bits to the engine's 0x80 input markers.
Keyboard-state update at `0x0044B010` now clears the full 256-byte buffer and
routes enabled input through injectable keyboard or direct-input providers.
The companion normalization leaf at `0x0044B080` strips transient high bits
from the keyboard buffer before publishing it through an injectable setter.
The input-history step at `0x0044BE70` now clamps the history index, restores
both paired state words, and clears the transient field after each step.
Its companion save leaf at `0x0044BE20` now records both current input words,
saturates the history cursor at slot 15, and clears the same transient field.
The file-existence probe at `0x0044B4D0` now models successful handle closure
and failure ownership through injectable open/close providers.
The paired probe-handle close path at `0x0044B7E0` now guards invalid handles,
closes valid ones, and decrements the critical-section depth exactly once.
The shared diagnostic writer at `0x0044B740` now reports complete versus short
writes through injectable providers and retires the handle on failure.
The matching reader at `0x0044B790` now models shared-buffer allocation,
allocation-failure handle retirement, and provider-backed reads.
The XOR string decoder at `0x00417010` is now exposed as a bounded-independent
typed helper with coverage for its advancing key and terminator handling.
The adjacent polar-vector leaf at `0x0041BEB0` is exposed as a typed score
helper and covered at cardinal-angle inputs.
The render-side polar-vector leaf at `0x004458B0` now shares the typed
`Vector2_SetPolar` implementation and has its own cardinal-angle coverage.
The worker shutdown pair at `0x0044C130`/`0x0044C150` now polls pending waits,
resets worker state, and closes the handle through injectable platform hooks.
The paired entity-angle leaves at `0x00426610` and `0x00426660` now compute
forward and inverse displacement angles, returning π for coincident points.
The flag-dependent dummy dispatcher at `0x00420C00` now emits the `dummy`
request with index 3 or 4 according to the state flag.
The frame-value snapshot at `0x00421F60` now updates its object slot and raises
the retained maximum only when the current value exceeds it.
The unpause transition at `0x00422C30` now clears the pause bit, emits the
`UnPause` request, retires its animation handle, and restores the saved frame.
Player scheduler-link reset at `0x00405BE0` is now typed too, covering both
inactive sentinel chains and their shared timer-state initialization.
The adjacent MIDI lifecycle now has explicit layouts and conventional APIs for
buffer-table cleanup (`0x0043AA60`), playback shutdown (`0x0043AE20`), and
completed-header retirement (`0x0043AEB0`). The window procedure dispatches
`MM_MOM_DONE` through that readable header-retirement path. Gameplay teardown
at `0x00409230` likewise exposes its manager and entity-release callback rather
than relying on the retail global and hidden EAX input. The adjacent
`0x004091C0` callback now releases the eight- and five-entity trailing arrays
at `+0x778` and `+0x24D8`; `0x00409270` is its typed scheduler wrapper. This
corrects the raw decompiler's loss of the entity pointer passed through EAX.

The render staging leaf at `0x00442FE0` now expands one quad into the manager's
six-vertex triangle list (0,1,2 / 1,2,3), advancing the staging cursor and the
staged-quad counter through a typed staging struct. The archive-cursor open at
`0x0044DBF0` completes the cursor trio alongside the seek (`0x0044DD40`) and
read (`0x0044DE10`) paths: it validates the path, opens the file for
sequential read, attaches the section descriptor, and performs the initial
seek to the section base plus the shared `DAT_004977A4` offset, with the
retail HRESULT codes preserved. The score gauge leaf at `0x00418B80` stores
one tenth of its input and disables its embedded timer through the shared
five-word sentinel pattern; its neighbor at `0x00418A90` increments a counter
word clamped at 9. The configuration defaults initializer at `0x00418C40`
resets a 0x34-byte record to the retail defaults (version tag `0x00100003`,
600/600 axis thresholds, mode 2, the 100/0x50 volume pair, and the preset
block copied from `0x00474E88`). The stage-tip manager constructor at
`0x00418D40` zeroes its 0x1A8-byte state, self-links all sixteen intrusive
list sentinels, and publishes the instance through `DAT_00477814`; tip
creation at `0x0041A120` allocates an 0x88-byte record through an injectable
allocator, runs the same initialization as `StageTip_Initialize`
(`0x00418D00`), appends to the tail of the per-difficulty chain selected by
`DAT_00474C7C` (sentinels 8..15 of the same manager), and fills the position,
0x40-byte text, and display fields from the difficulty globals. The sound
worker shutdown at `0x0043CC40` raises the stop flag and polls both worker
handles with injectable wait/sleep/close hooks before clearing their slots.
Host-side builds now pull the real `<cstdint>` in `entity.hpp` (the manual
typedefs remain for the MSVC 7.1 production target) so mixed headers link
into the combined `recovery_batch_test`.

The second mass-recovery batch pushes the ledger past the 400-function mark
with 55 new semantic reconstructions across game, render, platform, and math
units. Highlights: the scheduler-pair registration family (`0x00418E30`,
`0x00422150`, `0x0041C120`, `0x00413980`, `0x0042CAA0`) shares one
create-and-register skeleton with injected callback hooks; the manager
factories (`0x0041C290`, `0x004180E0`, `0x00413350`, `0x004246C0`,
`0x0042B430`, `0x0042C920`, `0x00413810`, `0x004175E0`) reproduce the retail
allocate/zero/publish pattern for the `0x00477700`-block globals; the ANM
handle sweeps (`0x00409E50`, `0x0042C770`, `0x0040B3A0`, `0x00421300`)
propagate sprite words through child lists with the solo-flag gate; and the
platform layer gains sound-stream startup (`0x0044D440`), MIDI sequencing
leaves (`0x0043A730`, `0x0043ACE0`), joystick probing (`0x0044A0C0`), and
worker start/stop (`0x0044C1C0`, `0x0043DAB0`). All 39 new translation units
compile with `-Wall -Wextra -Werror` and link into the combined
`recovery_batch2_test`, which asserts behavior for 21 of the new functions
(render-state sync transitions, faith-gauge boundary crossings, score-queue
linking, task-registration wiring, and the sound/joystick error paths).

## Standalone startup-to-title milestone

The retail-free integration harness now exercises the reconstructed boot
orchestrator and title-task initializer. The latest audit no longer treats a
source address comment as proof that a function is complete: only explicit
semantic-completion annotations and verified overlays count as source-ready.
The recovery campaign added 52 candidate blocker implementations across 13 new
translation units: the boot orchestrator `GameMain` (`0x00438AD0`), the
0x732460-byte game-state arena constructor (`0x00445900`), the frame
clock/advance pair (`0x00439540`/`0x00439390`), the 33-state default device
block (`0x00439D20`), main-task registration and shutdown
(`0x00420470`/`0x00420270`), config load/validate (`0x00420870`), the pack
file loader (`0x0044B360`), the sound worker command drain and streaming
buffer family (`0x0043DDF0`, `0x0044CBF0`–`0x0044DAD0`), camera/viewport
setup, ANM archive mounting, the full ANM VM opcode interpreter
(`0x0043EE30`), the LZSS score-save path, and the fifteen-manager stage
teardown (`0x00417C80`).

Every one of the 144 indirect call sites reachable from the milestone roots
is classified in `docs/dynamic_call_site_audit.md` as either a COM interface
vtable slot (host-provided) or a game-owned callback whose targets are all
closure members. `standalone/host_main.cpp` wires the reconstructed hook
surfaces to a stub platform layer, `standalone/build.sh` (or
`./build_standalone.sh`) links only reconstructed sources into
`build/standalone/th10_standalone`, and `./run_standalone.sh` runs it. The
runner boots through config load, device defaults, arena construction (2
primary + 18 secondary scheduler callbacks), invokes `Title_RegisterTasks`,
resolves the synthetic host resources for `title.anm` and `title_v.anm`, runs
60 title frames, and shuts down cleanly; `test.sh` requires this smoke test to
print `SMOKE_PASS`. The conservative source audit currently reports 5/179
reachable functions source-ready and 174 blockers. All three integration
gates pass, but the milestone is not declared retail-code-independent until
the remaining functions receive explicit completion evidence.

Scope note: this is a semantic reconstruction running against a host stub
layer (no Direct3D/DirectSound), not a byte-exact retail replacement, and it
does not yet parse real `th10.dat` game assets.

## Recovery batch 7

The former `manager_factories` sources (now dissolved into `src/util/legacy_string_funclets.cpp`, `src/platform/sound_float_forward.cpp`, `src/game/player_motion.cpp`, … and 10 more topical files)
add 26 more readable reconstructions (~4.3 KB of retail code) in the same
conventional-ABI, dependency-injected style as the earlier recovery leaves:

- String/exception funclets: `0x00438723`, `0x004387C2`
- Forwarding thunks: `0x00427C50`, `0x0040678E`
- Player field wrap + animation: `0x00407DA0`, `0x00407E40`, `0x004074B0`
- ECL child-VM spawn/tick: `0x004500D0`, `0x0044FD10`
- Manager lifecycle/registration: `0x0040D6B0`, `0x0043C8B0`, `0x004296F0`,
  `0x0042AE60`, `0x0042B4D0`, `0x00405E20`, `0x00405ED0`
- Enemy/boss/UI sync: `0x004066E0`, `0x0041D7C0`, `0x0040E5F0`
- Effect pool droplets: `0x0042B6F0`
- Render/ANM/platform: `0x00401D20`, `0x0040C3C0`, `0x004473C0`,
  `0x00446F40`, `0x00446C70`, `0x0043E3A0`

`tests/manager_factories_test.cpp` exercises every leaf (20 test groups) and
is wired into `test.sh`.

## Recovery batch 8

The former `bullet_systems` sources (now dissolved into `src/game/enemy_grid_scan.cpp`, `src/game/manager_factories.cpp`, `src/game/enemy_lifecycle.cpp`, … and 13 more topical files)
add 24 more readable reconstructions (~5.5 KB of retail code) in the same
conventional-ABI, dependency-injected style:

- Manager factories: `0x00408C90` (player), `0x00414830` (item),
  `0x00406060` (bullet pool), `0x0041AED0` (effect pool),
  `0x00429610` (stage-from-script)
- Menus and config: `0x004223F0` (main-menu state dispatch),
  `0x00430250` (key rebinding with conflict swap), `0x00426520`
  (music-room track list), `0x004135D0` (FPS counter overlay)
- Enemy/player ticks: `0x004073E0` (shot-grid scan), `0x0040E6A0`
  (dead-for-capture sweep), `0x0040D750` (interpolator tick),
  `0x004076A0` (death shrink)
- Bullets: `0x00404450` (sprite re-registration), `0x00404F30`
  (slot construct), `0x00405300` (shot-type select)
- Render/ANM: `0x004450E0` (rect fan draw), `0x00447700`
  (pending-entry service), `0x00447AE0` (shadowed overlay text),
  `0x0043C410` (ASCII draw callback)
- Sound/replay/script: `0x0043DD10` (sound event queue), `0x0043D690`
  (stream thread start), `0x00415DB0` (replay stage load),
  `0x00419F40` (script text line reader)

`tests/bullet_systems_test.cpp` exercises all 24 leaves (22 test groups)
and is wired into `test.sh`.

## Recovery batch 9

The former `enemy_motion_steps` sources (now dissolved into `src/app/fps_counter.cpp`, `src/game/ending_screen.cpp`, `src/render/default_viewport.cpp`, … and 12 more topical files) add 22
more readable reconstructions (~6.9 KB of retail code) from the medium size
band, in the same dependency-injected style as the earlier batches:

- Core loop and menus: `0x004134B0` FrameRateCounter_Update, `0x0042D300`
  EndingState_Dispatch, `0x0041F990` TitleScreen_LoadCoreAssets, `0x00424D90`
  PauseMenu_ResetTimers.
- Bullet system: `0x004065C0` BulletManager_RelinkActive, `0x00402720`
  BulletManager_OnDraw.
- Enemy system: `0x00407560` Enemy_AccelStep, `0x00407EF0` Enemy_HomingStep,
  `0x004078E0` Enemy_EaseStopStep, `0x00407780` Enemy_EaseTurnStep,
  `0x0040B110` EnemySpawner_CreateFromTable, `0x00408100`
  EnemyPool_BlastRadius.
- Stage scripting: `0x00403850` StageScript_Load (the retail in-place offset
  relocation is widened to a host pointer table).
- Items: `0x004266B0` Item_TestFieldContact.
- Rendering / ANM: `0x0043C1A0` Renderer_ApplyDefaultViewport, `0x0043C2C0`
  Ascii_OnResetDevice, `0x004451C0` AnmVm_DrawDispatch, `0x00446D70`
  AnmTexture_UploadSurface (semantic reconstruction of a corrupted decompile),
  `0x00447FD0` AnmArchive_RestoreTexture, `0x00448120`
  AnmArchive_RestoreTextureRect.
- Audio: `0x0043B7A0` MidiOutput_ApplyChannelVolumes, `0x0043DB60`
  SoundManager_InitCommonBuffers.

`tests/enemy_motion_steps_test.cpp` covers every function with assert-based
behavioral tests (state dispatch, clamping, linked-list relinking, quad
rotation math, clock advancement, and failure paths) and is wired into
`test.sh` (`BATCH9_TESTS_PASS`).

## Recovery batch 10

22 more retail functions reconstructed in
The former `game_systems` sources (now dissolved into `src/platform/joystick_property.cpp`, `src/game/enemy_lifecycle.cpp`, `src/script/ecl_name_table.cpp`, … and 15 more topical files):

- 0x0040C730 `BulletRing_Reset`, 0x0040DAE0 `Enemy_Destroy`,
  0x00407BE0 `Enemy_BounceStep` — enemy/bullet lifecycle and movement
- 0x00450220 `EclNameTable_Register`, 0x0040CD20 `EclArchive_LoadFile` — ECL
  script loading
- 0x004127A0 `SpellTimer_Update`, 0x00409C00 `SpellCard_OnEnd` — spell-card
  timing and teardown
- 0x004462F0 `AnmManager_UploadClipQuad`, 0x004423E0
  `AnmManager_ApplyBlendColorWrap`, 0x0043BFA0 `Renderer_InitTextureStages`
  — renderer state
- 0x00436AF0 `GdiSurface_Create` — GDI font surface creation
- 0x0044C7E0 `Input_SetJoystickProperty` — DirectInput axis property setup
- 0x0042AF20 `ScoreData_CreateGlobal`, 0x00412FF0 `ReplayTimer_ClampToEnd`,
  0x00413A20 `ScoreTask_Init`, 0x004224C0 `NameEntry_DrawCharGrid`,
  0x0041FDD0 `ResultScreen_LazyCreateEffects`, 0x00422AB0 `PauseMenu_Open`,
  0x004231D0 `ResultMenu_Open`, 0x00423570 `NameEntry_Init` — score, replay,
  and menu flow
- 0x0041D2C0 `Effect_AccelStep`, 0x00427960 `StageBackground_SyncScroll` —
  effects and backgrounds

`tests/game_systems_test.cpp` covers every function with assert-based
behavioral tests and is wired into `test.sh` (`BATCH10_TESTS_PASS`).

## Recovery batch 11

6 more retail functions reconstructed in
The former `spell_and_input` sources (now dissolved into `src/render/anm_script_table_sweep.cpp`, `src/game/enemy_motion_steps.cpp`, `src/game/score_tasks.cpp`, … and 3 more topical files):

- 0x00403990 `AnmScriptTable_Sweep` — ANM script sweep over the record table
- 0x00407A30 `Enemy_HomingRelaunchStep` — decelerate-and-relaunch homing step
- 0x0041C330 `ScoreTaskList_Tick` — score-task list walk with retirement
- 0x0042A6A0 `SpellCard_Dispatch` — spell-card history/activation dispatch
- 0x00437750 `FontCache_BlendToSurface` — GDI font-cache blend (A8R8G8B8,
  A1R5G5B5, A4R4G4B4)
- 0x0044A190 `Joystick_Poll` — joystick poll (winmm + DirectInput paths)

Candidates skipped this pass because their Ghidra exports are corrupted or
oversized for reliable reconstruction: 0x00444240, 0x00443B60, 0x00403090,
0x00424480.

`tests/spell_and_input_test.cpp` covers every function with assert-based
behavioral tests and is wired into `test.sh` (`BATCH11_TESTS_PASS`).

## Recovery batch 12

3 more retail functions reconstructed in
The former `game_mode_transitions` sources (now dissolved into `src/app/version_marker.cpp`, `src/game/game_mode_switch.cpp`, `src/game/stage_controller_tick.cpp`):

- 0x00420100 `VersionMarker_Load` — executable-version marker probe, generated
  filename load, publication, and diagnostic failure paths
- 0x004218D0 `GameMode_ApplyRequested` — serialized high-level game-mode
  transitions, including gameplay cleanup, difficulty publication, and exit
  dispatch
- 0x00426360 `StageController_Tick` — stage-background projection, four-slot
  callback dispatch, and conditional paired effect emission

`tests/game_mode_transitions_test.cpp` covers success, failure, transition, dormant,
and callback/effect paths and is wired into `test.sh` (`BATCH12_TESTS_PASS`).

## Recovery batch 13

3 more retail functions reconstructed in
The former `spell_timeout` sources (now dissolved into `src/math/oriented_rect.cpp`, `src/game/trigger_region.cpp`, `src/render/special_quad.cpp`, `src/game/spell_timeout.cpp`):

- 0x0041E4D0 `OrientedRect_IntersectsCircle` — rectangle-local rotation and
  expanded-axis circle overlap classification
- 0x004267F0 `TriggerRegion_Classify` — inner activation, outer transition-band
  classification, suppression, mode gating, and cooldown handling
- 0x0043BDA0 `Renderer_DrawSpecialQuad` — special-quad texture-stage setup,
  draw dispatch, renderer-cache publication, and normal-state restoration

`tests/spell_timeout_test.cpp` covers rotated and rejected collisions,
activation gating, transition-band classification, exact render-state ordering,
and cache updates and is wired into `test.sh` (`BATCH13_TESTS_PASS`).

## Recovery batch 14

2 more retail functions reconstructed in
The former `trigger_activation` sources (now dissolved into `src/game/trigger_activation.cpp`, `src/game/projectile_bounce.cpp`):

- 0x00426CF0 `TriggerRegion_Activate` — active-state entry, 33-effect creation,
  clock reset, sound/animation dispatch, and late-stage visibility cleanup
- 0x0041CFD0 `Projectile_BounceAtBounds` — projected boundary detection,
  horizontal and vertical reflection, sound dispatch, and one-shot flag cleanup

`tests/trigger_activation_test.cpp` covers clock registration, effect counts,
sound and stage gates, in-bounds behavior, both reflection axes, suppression,
and exact flag clearing and is wired into `test.sh` (`BATCH14_TESTS_PASS`).

## Recovery batch 15

3 more retail functions reconstructed in `font_texture_draw`:

- 0x00437DB0 / 0x00437FE0 — shadowed and plain GDI text rasterization,
  alpha conversion, transparent-edge repair, and texture upload
- 0x0043C500 — persistent special-quad render callback

## Recovery batch 16

2 more retail functions reconstructed in `font_cache_init`:

- 0x00437A00 — font-cache surface, deterministic seed pixels, and 15-font setup
- 0x00421070 — queued three-handle animation-tree cleanup

## Recovery batch 17

2 more retail functions reconstructed in `sprite_test_overlay`:

- 0x0042C360 — sprite-test debug overlay states and color restoration
- 0x00443080 — scaled, anchored quad construction and render dispatch

The batch 15–17 harnesses are wired into `test.sh` and report
`BATCH15_TESTS_PASS`, `BATCH16_TESTS_PASS`, and `BATCH17_TESTS_PASS`.

## Recovery batch 18

0x00417040 is reconstructed as `ScoreHud_Update` in `score_hud_update`. It
covers score easing, velocity clamping, high-score/rank snapshots, nine-digit
publication, crossing markers, and normal/special extend thresholds. The
focused harness reports `BATCH18_TESTS_PASS`.

## Recovery batch 19

The register-accurate naked x86 sources supplied in `backups.tar.gz` resolve
the earlier calling-convention and D3DX argument roadblock. Five functions are
now reconstructed in `projection_quads`:

- 0x00444240 `ProjectedQuad_Update` — dirty world-matrix rebuild, layered
  translation, anchor selection, four-corner projection, and matrix publication
- 0x00443B60 `Billboard_BuildProjectedQuad` — depth gate, perspective extent,
  anchor selection, and rotated projected billboard construction
- 0x00403090 `ProjectedBox_IsOutside` — distance precheck, eight-corner
  projection, normalized-depth filtering, and viewport overlap classification
- 0x00424480 `WindowDescriptor_Configure` — register-confirmed descriptor
  population and sprite-resource metadata conversion
- 0x00423370 `ResultMenu_OpenRecovered` — supervisor shortcut, paired effects,
  result-window setup, BGM/sound initialization, and frame-scale handoff

`tests/projection_quads_test.cpp` covers all five recovered paths and reports
`BATCH19_TESTS_PASS`.

## Recovery batches 20–21

Assembly-backed follow-on reconstruction continued through three dependent
paths:

- 0x004445C0 `FadedProjectedQuad_Draw` — projected-quad update, world-space
  distance probes, per-vertex RGB attenuation, mode-2 draw, and RHW reset
- 0x00403A30 `AnmRecordTable_DrawVisible` — typed record filtering, projected
  box culling, VM position/scale updates, render-state switching, and counters
- 0x0042A200 `ReplayArchive_Load` — disk/resource replay load, header validation,
  two cipher passes, decompression, and slot-index construction

Focused tests report `BATCH20_TESTS_PASS` and `BATCH21_TESTS_PASS`.

## Current semantic-recovery roadblock

The next candidates expose complete instructions, but not enough trustworthy
high-level ownership/type information for a non-speculative C++ model:

- 0x0040BA90 constructs scheduler-owned objects through an intrusive list and
  MSVC exception-unwind path whose lifetime contract is not identified.
- 0x0044D850 is a DirectSound streaming-buffer lock/refill/unlock path; the
  archive does not supply a runnable 32-bit DirectSound contract for verifying
  split-buffer and failure behavior.
- 0x00445620 mutates overlapping particle/vector records through several
  differently strided views; the record union and active-count invariants are
  not identified by the assembly alone.

These can be retained as exact assembly overlays, but promoting them to named,
typed semantic C++ now requires additional type/lifetime evidence or runtime
traces. This is the next evidence-backed stopping point.

## Naming pass

`docs/naming.md` is the naming ledger: it records every naming decision for
reconstructed structures, globals, and constants together with its evidence
and a confidence tier (confirmed / inferred / unidentified). The first pass
covered the recovery batches:

- Batch 11 gained named constants: `InputBit` (shoot/bomb/focus/pause/
  directions/skip), `FontPixelFormat` (D3DFMT codes 0x15/0x19/0x1A),
  `SpellCardState` (declare/activate), `kEnemyModeRelaunchArmed`,
  `kDInputInputLost` (DIERR_INPUTLOST), and `kRelaunchHalfPi`.
- The spell-card record and UI globals were renamed from raw offsets to
  semantic names: `bonus_initial`, `bonus_active`, `bonus_gauge`, `duration`,
  `history_captures`/`history_attempts` (the "History x/y" pair shown on
  declaration), `title_text`, and honestly-labeled `activation_param_a`/`_b`
  where semantics remain unidentified.
- The joystick config fields were renamed `shoot`/`focus` (retail config
  "shot"/"slow") and all packed input bits now use the named enum.
- Batch 10's `field_1020` became `control_flags` after tracing ECL opcodes
  0x12/0x13 toggling its bit 0 in the instruction dispatcher (0x0044E1A0).

Unresolved names are listed under "Open questions" in the ledger; revisit
them as more callers are recovered.
