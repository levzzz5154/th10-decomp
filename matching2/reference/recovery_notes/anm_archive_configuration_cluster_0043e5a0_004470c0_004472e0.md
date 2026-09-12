# ANM archive/configuration cluster — 0x0043E5A0, 0x004470C0, 0x004472E0

Status: attempted native-LTCG semantic recovery; no promotion.  The live
manifest extents are authoritative: 0x0043E5A0 is 356 bytes,
0x004470C0 is 433 bytes, and 0x004472E0 is 214 bytes (1003 bytes total).
All three production rows remain `kind: asm`, with their existing source and
symbol ownership.  This attempt did not change `regions.json`, shared tooling,
or unrelated sources.

## Semantic and binary evidence

The archived semantic references used for the attempt were:

- `matching2/reference/legacy_semantic/src/render/anm_archive.cpp` and
  `include/th10/render/anm_archive.hpp`: archive mounting walks the linked ANM
  entry headers, accumulates sprite/script counts, allocates the 0x130-byte
  archive state plus 0x10 texture slots and 0x44-byte resource records, then
  loads each external texture through the per-entry helper.
- `matching2/reference/legacy_semantic/src/game/pool_constructors.cpp` and
  `include/th10/game/pool_constructors.hpp`: `EffectRuntime_Preload` documents
  the 0x0043E5A0 field writes, 0x44-byte bank records, identity rows, 1/256
  dimension scale, aspect ratios, and the 0x40-byte mirror.
- `decompiled/ghidra_augmented/functions/004470C0.c/.asm`,
  `004472E0.c/.asm`, and `00405BD0.c/.asm`, plus the IDA listing in
  `ida/th10.exe.c`: the 0x004470C0 loader publishes at
  `manager+0x3AD06C+index*4`, stores the loaded image at state+0x108, and
  uses linked headers at +0x38; 0x004472E0 checks entry format +0x28 and
  external-name flag +0x34 before filling state+0x120 slots; 0x0043E5A0
  consumes `archive+0x118 + index*0x44` and writes the object fields through
  +0x394, +0x4c, +0x50, +0x23c..+0x2f8.

The live callers confirm the ABI is not a normal portable signature:

- 0x004472E0 receives the entry index in ECX, archive state in EDX, and the
  entry pointer as its stack argument, with `ret 4`.
- 0x0043E5A0 is called with the object in EAX, archive/resource manager in
  ECX, and entry index in EDX; callers include the animation/effect setup
  paths in `fun_0042f8b0_0042f8b0.cpp` and the Ghidra setup callers.
- 0x004470C0 is declared by IDA as the three-argument stdcall loader
  (manager, index, name), but the live body preserves/uses a nonstandard
  register/stack arrangement around its 0x110-byte frame.  The nearby
  `unassigned_00447080.cpp` wrapper pushes EAX/ECX/ESI before the call.  This
  arrangement must be modeled explicitly before a C++ body can reproduce the
  retail register allocation.

## Disposable native-LTCG probe

A disposable candidate TU modeled the three bodies as named archive mount,
entry texture creation, and animation-object resource configuration methods.
The driver kept all three live in one compiler context and bound the known
archive loader, allocator, logger, sprintf, scale constant, and security
symbols.  No candidate source, layout, manifest entry, or proposal was left
in production after the failed probe.

The first fixed-address build showed these compiler contributions:

| region | observed candidate extent | first byte evidence |
| --- | ---: | --- |
| 0x0043E5A0 | 374 bytes (0x176), vs 356 | retail `0x0043E5A3: 57` (`push edi`); candidate `33 c9` (`xor ecx,ecx`) |
| 0x004470C0 | 545 bytes (0x221), vs 433 | candidate prologue `81 ec 18 01 00 00` (`sub esp,118h`); retail `81 ec 10 01 00 00` (`sub esp,110h`) |
| 0x004472E0 | 214 bytes, extent exact | retail `0x004472FD: 53` (`push ebx`); candidate emitted `56` (`push esi`) at the corresponding +0x1d body position |

The diagnostic placement required shifting the oversized later bodies in the
disposable image; those shifted addresses were used only to compare candidate
body bytes against the original retail bytes.  The 0x004472E0 extent match is
not a byte match (171 of 214 bytes differed in that comparison), so it is not
an independent promotion.  This is ordinary compiler/ABI mismatch evidence,
not proof that any of these bodies is irreducible or exact-assembly-required.

## Next dependency

The next useful bounded dependency is an explicit compiler-visible context for
the 0x004470C0 manager register path, while keeping 0x004472E0 as a separate
noinline internal-ABI callee.  The 0x0044B360 loader’s proven native-LTCG
context should be reused for its name/size/disk-flag call shape.  The archive
entry registration/resource-record writers between 0x004473C0 and
0x00447470 remain coupled evidence before attempting to claim the archive
state is complete.  Until those contexts are modeled, the production asm
bodies should remain intact.

## Focused ANM archive follow-up — 0x004470C0, 0x004472E0, 0x004473C0, 0x00447470

Status: attempted the 1471-byte live follow-up; no region was independently
exact and nothing was promoted. The authoritative live extents were
0x004470C0=433, 0x004472E0=214, 0x004473C0=174, and 0x00447470=650 bytes.
The production rows remain asm with their existing source and symbol
ownership. The proven semantic 0x0044B360 `Archive_LoadFile` body and its
LTCG context were reused read-only. This follow-up did not edit
`regions.json`, shared tooling, or other production sources.

The bounded candidate TU used the archived semantic references in
`legacy_semantic/src/render/anm_archive.cpp`, `anm_texture_upload.cpp`, and
`anm_entry_load.cpp` (and their headers), together with the live IDA/Ghidra
listings `004470C0`, `004472E0`, `004473C0`, and `00447470`. It modeled the
archive state allocation, texture/resource/script tables, cursor traversal,
sprite-record derivation, and resource-record writers. The manager path was
kept compiler-visible, while 0x004472E0 was a separate noinline ECX/EDX
internal-ABI callee: ECX is the entry index, EDX the archive state, the entry
pointer is on the stack, and the callee has `ret 4`. The cursor/loader model
also preserved the hidden EAX texture index, five stack arguments, and
`ret 14h` shape of 0x00447470. 0x004473C0 reads state +0x108/+0x124 and
passes the accumulated cursor/resource bases into that loader.

The fixed-address validator first exposed compiler extents and placement
before byte comparison. In the disposable native image the candidate map
was:

| region | candidate VA / extent | live extent | first retail-byte comparison mismatch |
| --- | --- | ---: | --- |
| 0x004470C0 | 0x004470C0 / 510 | 433 | +0x0D: candidate `85 C9` (`test ecx,ecx`), retail `55` (`push ebp`) |
| 0x004472E0 | 0x00447330 / 214 | 214 | +0x1D: candidate `56` (`push esi`), retail `53` (`push ebx`) |
| 0x004473C0 | 0x00447410 / 147 | 174 | +0x03: candidate `56` (`push esi`), retail `8B 6C 24 14` (`mov ebp,[esp+14h]`) |
| 0x00447470 | 0x004474B0 / 505 | 650 | +0x00: candidate `81 EC 10 01 00 00` (`sub esp,110h`), retail `83 EC 68` (`sub esp,68h`) |

For the shifted diagnostic comparisons, 399 of the first 433 mount bytes,
171 of 214 texture bytes, 129 of the first 147 cursor bytes, and 484 of the
first 505 loader bytes differed. Although 0x004472E0 had the requested
extent, its bytes were not exact. These are ordinary compiler/register-ABI
and body-shape mismatches, not proof of an exact-assembly-required function.

No semantic source, task-local layout/context, proposal, or temporary build
artifact from this follow-up was retained. The next dependency is a more
faithful compiler-visible manager-register context for 0x004470C0 and an
explicit hidden-EAX/five-stack-argument model for 0x00447470, including the
custom ABI of its 0x00446EB0/0x00446F40/0x00447050 texture/resource writers;
the proven 0x0044B360 context remains reusable.
