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
waiting for all 1,196 functions and the global data layout to be complete.

```bash
./build.sh
./test.sh
./run.sh
```

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
| `Entity_Constructor` | 88 | 100% |
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
| `DestroyEntityList` | 43 | 100% |
| `Entity_Init` | 273 | partial; exact first 45 bytes |
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

`Entity_Init` is functionally reconstructed, but MSVC currently schedules its
register restores and callee-save pops differently after the entity clear.
The gameplay layouts now also include the complete 0x1F8-byte bullet spawn
parameter record and the 0x88-byte linked stage-tip record used by the stage
text parser. Polar-to-Cartesian vector initialization is readable C++ as well;
the retail build combines the two trigonometric operations into `FSINCOS`.
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
