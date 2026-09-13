# Archive resource caller expansion

Three complete game functions add 563 bytes to the compiler-visible archive
loader cluster: asset-buffer replacement (106 bytes), parameter-file loading and
relocation (229 bytes), and optional map-companion loading (228 bytes).

The existing script and executable-checksum public entries are the only roots.
The cluster now uses schema 1: an array-loop context calls the three additional
private entries. The loader remains EAX filename / two stack arguments; the asset
function receives EAX filename with its buffer on the stack; the parameter loader
uses ESI receiver and EAX filename; the map loader uses ESI receiver with a stack
filename. All definitions share one native /LTCG link. The six real contributions
are recovered; the 111-byte context and layout gaps count as zero recovered bytes.

## Source and first-probe evidence

The asset and map functions matched their full extents and bytes on their first
source attempts. The asset's filename copy uses ordinary strcat and retains the
old-buffer free/reset sequence. The map function builds the companion path,
changes its three extension characters, probes for the file, loads it from disk,
and converts its stored offsets to addresses. Its loop alignment, split return
paths, and compiler-generated stack-cookie checks match without substitutions.

The parameter file has counted groups of signed-kind records, terminated by a
negative record kind. The source relocates each group's record pointer, then
maps four record indices through the existing runtime tables. The compiler emits
both aligned nested loops and their complete retail padding. All loop bytes
matched on the first attempt; only the projection prefix differed.

A double projection local caused the compiler to load each float dimension and
multiply against an x87 stack value. A float local initialized from sin gives
the retail FLD ST(0) / FMUL memory sequence and consumes the last retained value
on the fourth store. This removes the entire mismatch while preserving the
229-byte extent. Both projection passes are present in retail and in the source.
The compiler itself emits FSIN; no assembly intrinsic or substitute instruction
is used. The existing read-only angle is a normal data binding, not a literal
alias.

## Validation

`python3 matching2/tools/matching/probe.py --source src/game/music_room.cpp
--output matching2/build/probe_archive_resources` reports all six real functions
EXACT. `make verify MSVC_ARGS='--jobs 32'` passes with all 487,936 bytes identical.
Progress is 459 C++ regions / 28,579 bytes; 2,126 assembly regions / 360,403 bytes.
Whole executable SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The native report records no instruction/address changes, aliases, masked bytes,
or reference bytes used to build code. The previous three recovered bodies
remain exact after the context and source-section changes.

| Address | Function | Bytes | Native body SHA-256 |
| --- | --- | ---: | --- |
| 0x0040B480 | LoadAsset | 106 | `b81d34dde29a05dd46889394c9346d8a12c28438b2a9b437c6040896ab66c84e` |
| 0x0043E9D0 | MapResource_LoadMap | 228 | `3a12e283263a4bfa4c5b57f96d67ce6d70362edfc491bb73071deec03024d22f` |
| 0x00426520 | ParameterLoader_Load | 229 | `268307c702403c47448c68e49efadd0d668ace2f4f79b31d24be149456f21e96` |
