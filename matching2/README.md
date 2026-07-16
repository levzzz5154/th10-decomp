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
The utility coverage also exercises inline and allocated `LegacyString`
assignment, substring aliasing, erase, reserve/shrink, ownership checks, and
termination without depending on the retail CRT.
Render coverage exercises reset-target release, lost-device recovery, and
numbered screenshot selection without launching the game.
Scheduler coverage checks callback construction, replacement handling, and
priority-ordered insertion into both retail callback lists.
Gameplay-runtime coverage checks fractional/normal/reverse frame-timer
advancement, animation lookup across both manager lists, shared-position
updates, pool allocation, handle registration, and player animation creation.
It also covers root-to-child propagation, stop-frame updates, script restart,
generic flag changes, resource retirement, handle validation, child lookup,
and pooled-object removal. Ghidra-guided tests also cover the animation
interpreter's integer and float variable banks, writable operand resolution,
base-position operands, and literal/fallback behavior.
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
Registration coverage now exercises front and back insertion in both the
primary and secondary manager lists, including head/tail repair after removal.
Per-frame coverage walks both active lists, removes retired objects without
invalidating iteration, invokes update/draw callbacks, distributes primary
objects into 19 render buckets, queues secondary objects in bucket 19, and
renders the resulting chains.

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
The adjacent MIDI lifecycle now has explicit layouts and conventional APIs for
buffer-table cleanup (`0x0043AA60`), playback shutdown (`0x0043AE20`), and
completed-header retirement (`0x0043AEB0`). The window procedure dispatches
`MM_MOM_DONE` through that readable header-retirement path. Gameplay teardown
at `0x00409230` likewise exposes its manager and entity-release callback rather
than relying on the retail global and hidden EAX input. The adjacent
`0x004091C0` callback now releases the eight- and five-entity trailing arrays
at `+0x778` and `+0x24D8`; `0x00409270` is its typed scheduler wrapper. This
corrects the raw decompiler's loss of the entity pointer passed through EAX.
