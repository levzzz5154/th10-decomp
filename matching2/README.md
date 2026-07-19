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
