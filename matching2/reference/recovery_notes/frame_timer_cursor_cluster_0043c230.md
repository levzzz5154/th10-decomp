# FrameTimer/cursor caller cluster (`0x0043BD40`, `0x0043C230`)

## Disposition

The 93-byte animation-cursor callback at `0x0043BD40` and the 133-byte
callback at `0x0043C230` are now readable C++ and byte-exact.  Both are linked
with the existing `FrameTimer` methods at `0x00404ED0`, `0x00428DD0`, and
`0x0044BF40` as one native MSVC 7.1 `/LTCG` cluster.  The complete executable
remains byte-identical to the retail oracle.  The old assembly records are
retained as `previous_record` only for manifest history.

The two callbacks share the same embedded timer topology: their object
receiver enters in `ECX`, while the nested `FrameTimer::Tick` call uses the
retail private `ESI` receiver.  Recovering `0x0043BD40` therefore extends the
same caller/callee experiment rather than introducing a second ABI mechanism.

## Ordinary-TU blocker

The `0x0043C230` callback updates the cursor value from `elapsed * 255 /
length`, clamps negative values, stops after the terminal frame, and ticks the
embedded `FrameTimer` at `this + 0x30` unless the active scene has flag bit 2
set.  Its retail ABI enters with the cursor in `ECX`, but the nested timer
call supplies the receiver in `ESI`:

```asm
0043C2A5  add  esi, 30h
0043C2A8  call 00404ED0h
```

A standalone readable member-function candidate reproduced the body extent
and all control flow, but emitted `lea ecx,[esi+30h]` for the timer call.  The
two differing opcode bytes are the unexpressible private receiver convention;
the ordinary candidate is therefore not accepted per region.

## Native-LTCG experiment

`matching2/msvc/layout/ltcg/frame_timer.json` now declares both cursor sources
as `additional_sources` inputs.  The three implementation sources are compiled
with `/GL`; the synthetic context calls one cursor and all three timer methods
in a single native `/LTCG` link.  Both cursor methods are explicit schema-1
`roots` entries, emitting `/INCLUDE` directives for their decorated symbols.
Those roots are important: without one LINK treats a cursor as an internal
callee and reorders its prologue, while the root preserves the retail public
`ECX` entry and still lets the timer call use private `ESI`.

The field read is declared `volatile` only to preserve the retail x87 operand
order (`fld [elapsed]` followed by `fmul [data_00470bf8]`) under LTCG.  It does
not add an instruction or change the observable callback behavior.  Absolute
bindings provide the three fixed-address globals at `0x004918A4`, `0x00477810`,
and `0x00470BF8`; layout gaps retain the original addresses through `.rdata`.
No instruction bytes are patched or masked.

The `0x0043BD40` candidate uses the same typed embedded timer and a volatile
elapsed field.  Its standalone object already had the exact 93-byte extent and
all control flow; the only ordinary-TU mismatch was `lea ecx,[esi+30h]` in
place of retail `add esi,30h`.  Adding the source as a second `/GL` input and
rooting `?Tick@AnimationCursor_0043bd40@@QAEHXZ` reproduces the retail private
receiver while leaving the existing cursor and timer contributions unchanged.

Reproduce the focused proof with:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_0043bd40_0043bd40.cpp \
  --output matching2/build/probe_43bd40_cluster_rooted --json
```

The retained report is
`matching2/build/probe_43bd40_cluster_rooted/clusters/frame_timer/report.json`.
All five selected contributions compare exactly:

| Function | Extent | SHA-256 | Differences |
| --- | ---: | --- | ---: |
| `AnimationCursor_Tick_0043bd40` (`0x0043BD40`) | 93 | `eb77f9ae62bf28287002b87c29b886a0d5c534a2084fdec0ccb4279dbbafb4ce` | 0 |
| `AnimationCursor_Tick` (`0x0043C230`) | 133 | `bd823ee212b505f3db6785f9fbc6bbdd7acf8bb50024f79f8dfb36fcc24d039f` | 0 |
| `FrameTimer_Tick` (`0x00404ED0`) | 72 | `5349f4fd279892f975448c3dd7bd04000cead49a6aef8ae46bd11ae580fcbde5` | 0 |
| `FrameTimer_Decrement` (`0x00428DD0`) | 20 | `456bf129ca25bafdf3ff19604ea7e6067aca5da1737cd9fa8bf8dc8b075a8aee` | 0 |
| `FrameTimer_Advance` (`0x0044BF40`) | 88 | `c2c9591f6bcbfcf769892730b28e2da6d7d28af165ecde58ece3622068bcd4fd` | 0 |

The earlier four-contribution report was:

| Function | Extent | SHA-256 | Differences |
| --- | ---: | --- | ---: |
| `AnimationCursor_Tick` (`0x0043C230`) | 133 | `bd823ee212b505f3db6785f9fbc6bbdd7acf8bb50024f79f8dfb36fcc24d039f` | 0 |
| `FrameTimer_Tick` (`0x00404ED0`) | 72 | `5349f4fd279892f975448c3dd7bd04000cead49a6aef8ae46bd11ae580fcbde5` | 0 |
| `FrameTimer_Decrement` (`0x00428DD0`) | 20 | `456bf129ca25bafdf3ff19604ea7e6067aca5da1737cd9fa8bf8dc8b075a8aee` | 0 |
| `FrameTimer_Advance` (`0x0044BF40`) | 88 | `c2c9591f6bcbfcf769892730b28e2da6d7d28af165ecde58ece3622068bcd4fd` | 0 |

The two promotions remove 226 bytes of game-code assembly.  They also
exercise schema-1 roots for two independently reachable functions, matching
the schema-2 whole-program root behavior.
