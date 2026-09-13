# Third animation cursor and scheduler cluster (`0x0043C460`)

## Disposition

The 154-byte animation-cursor callback at `0x0043C460` is now readable C++ and
byte-exact.  It is linked with the three `FrameTimer` methods, the other two
cursors, and the scheduler store as one native MSVC 7.1 `/LTCG` cluster
(`layout/ltcg/frame_timer.json`).  The complete executable remains
byte-identical to the retail oracle.  The old assembly record is retained as
`previous_record` only for manifest history.

The callback shares the retail object topology of `0x0043BD40` and
`0x0043C230`: the cursor arrives in `ECX`, and the record at `+0x30` is both
the embedded `FrameTimer` (`ESI` receiver when ticking) and the scheduler
record (`EAX` receiver when storing).  Recovering it therefore extended the
existing caller/callee cluster instead of introducing a second ABI mechanism.

## Ordinary-TU blocker: one compiler literal address

The readable candidate reproduced the complete 154-byte flow, including the
retail unsigned-to-float conversion.  Exactly one byte differed: the
displacement of the conversion's `fadd`:

```asm
0043C480  test edi, edi
0043C482  mov  [esp+0Ch], edi
0043C486  fild dword ptr [esp+0Ch]
0043C48A  jge  0043C492
0043C48C  fadd dword ptr [00470B98h]      ; __real@4f800000, 2^32
0043C492  fmul dword ptr [esi+38h]
```

The literal is MSVC's own `__real@4f800000` pool entry, emitted for the
unsigned conversion.  A compiler pools each distinct literal once, and the
synthetic cluster placed the pooled copy at the next free `.rdata` address
(`0x00470B00`, four bytes after the cluster's `__real@3f800000`) instead of
retail's `0x00470B98`.  Pool placement depends on the whole translation-unit
set, not on the cluster layout, so no gap arrangement reaches the retail
address.  Rewriting the conversion in source to name an external bias is not a
substitute: `(float)mode` plus a manual `if (mode < 0)` correction schedules
the spill and the branch differently, and the body stops matching around the
prologue.

## Constant aliases in the LTCG pipeline

`matching2/tools/matching/ltcg_cluster.py` now accepts a schema-1
`constant_aliases` array.  Each entry names a compiler literal
(`__real@<binary32 bits>`), the retail address it must resolve to, and the
value that name encodes:

```json
"constant_aliases": [
  {"symbol": "__real@4f800000", "address": "0x00470B98", "value": 4294967296}
]
```

The loader rejects any entry whose value does not pack to the bits in its own
name and any symbol that is not a compiler literal.  The bindings object
defines the literal absolutely at the declared address, and only then does the
link add `/FORCE:MULTIPLE`, so the pooled copy is discarded instead of being
fatal.  Validation then requires

- the map to contain the literal exactly once, as a segment-0 symbol at the
  declared address, with no pooled copy left in `.rdata`;
- at least one selected function body to reference that address;
- the link log to report exactly one discarded duplicate definition per
  declared alias, and no undeclared duplicate at all.

The last two conditions are what keep `/FORCE:MULTIPLE` from being a blanket
relaxation: an alias that never binds, and any other duplicate definition,
both fail the cluster build.  No instruction byte or address operand is
patched; the alias wins ordinary symbol resolution.

## Cluster result

The seven complete contributions are byte-exact:

| Function | Extent | SHA-256 | Differences |
| --- | ---: | --- | ---: |
| `AnimationCursor_Tick_0043c460` (`0x0043C460`) | 154 | `163af6e09bccfa886237605c73d49764955d16b251b1731a1a834f914284131a` | 0 |
| `AnimationCursor_Tick_0043c230` (`0x0043C230`) | 133 | `bd823ee212b505f3db6785f9fbc6bbdd7acf8bb50024f79f8dfb36fcc24d039f` | 0 |
| `AnimationCursor_Tick_0043bd40` (`0x0043BD40`) | 93 | `eb77f9ae62bf28287002b87c29b886a0d5c534a2084fdec0ccb4279dbbafb4ce` | 0 |
| `FrameTimer_Tick` (`0x00404ED0`) | 72 | `5349f4fd279892f975448c3dd7bd04000cead49a6aef8ae46bd11ae580fcbde5` | 0 |
| `PlayerSchedulerRecord_SetSchedulerValue` (`0x00405410`) | 57 | `35c87a356741f4c628319bcf25c8e73cca3a554bff2ca59d1cb67d86fa0862e0` | 0 |
| `FrameTimer_Advance` (`0x0044BF40`) | 88 | `c2c9591f6bcbfcf769892730b28e2da6d7d28af165ecde58ece3622068bcd4fd` | 0 |
| `FrameTimer_Decrement` (`0x00428DD0`) | 20 | `456bf129ca25bafdf3ff19604ea7e6067aca5da1737cd9fa8bf8dc8b075a8aee` | 0 |

The scheduler store moved into this cluster from the retired standalone
`player_set_scheduler_value_00405410` manifest; `player_set_scheduler_value_00405410.cpp`
now uses the `.text$03scheduler` contribution the merged layout places at
`0x00405410`, and its `EAX` receiver is still selected by the same synthetic
caller plus the new cursor call site.

Reproduce the focused proof with:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_0043c460_0043c460.cpp \
  --output matching2/build/probe_43c460_cluster_alias --json
```

The retained report is
`matching2/build/probe_43c460_cluster_alias/clusters/frame_timer/report.json`.
Its `constant_aliases` field records the rebind and its `duplicate_definitions`
field records the single tolerated pooled copy:

```text
CIL library( CIL module) : warning LNK4006: __real@4f800000 already defined in
a previous module; second definition ignored
```

The promotion removes 154 bytes of game-code assembly.
