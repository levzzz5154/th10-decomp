# FrameTimer/cursor caller cluster (`0x0043C230`)

## Disposition

The 133-byte animation-cursor callback at `0x0043C230` is now readable C++
and byte-exact.  It is linked with the existing `FrameTimer` methods at
`0x00404ED0`, `0x00428DD0`, and `0x0044BF40` as one native MSVC 7.1 `/LTCG`
cluster.  The complete executable remains byte-identical to the retail
oracle.  The old assembly record is retained as `previous_record` only for
manifest history.

## Ordinary-TU blocker

The callback updates the cursor value from `elapsed * 255 / length`, clamps
negative values, stops after the terminal frame, and ticks the embedded
`FrameTimer` at `this + 0x30` unless the active scene has flag bit 2 set.  Its
retail ABI enters with the cursor in `ECX`, but the nested timer call supplies
the receiver in `ESI`:

```asm
0043C2A5  add  esi, 30h
0043C2A8  call 00404ED0h
```

A standalone readable member-function candidate reproduced the body extent
and all control flow, but emitted `lea ecx,[esi+30h]` for the timer call.  The
two differing opcode bytes are the unexpressible private receiver convention;
the ordinary candidate is therefore not accepted per region.

## Native-LTCG experiment

`matching2/msvc/layout/ltcg/frame_timer.json` now declares the cursor source as
an `additional_sources` input.  Both source files are compiled separately with
`/GL`; the synthetic context calls the cursor and all three timer methods in a
single native `/LTCG` link.  The cursor method is also an explicit schema-1
`roots` entry, which emits `/INCLUDE:?Tick@AnimationCursor_0043c230@@QAEHXZ`.
That root is important: without it LINK treats the cursor as an internal
callee and reorders its prologue, while the root preserves the retail public
`ECX` entry and still lets the timer call use private `ESI`.

The field read is declared `volatile` only to preserve the retail x87 operand
order (`fld [elapsed]` followed by `fmul [data_00470bf8]`) under LTCG.  It does
not add an instruction or change the observable callback behavior.  Absolute
bindings provide the three fixed-address globals at `0x004918A4`, `0x00477810`,
and `0x00470BF8`; layout gaps retain the original addresses through `.rdata`.
No instruction bytes are patched or masked.

Reproduce the focused proof with:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_0043c230_0043c230.cpp \
  --output matching2/build/probe_43c230_cluster_rooted --json
```

The retained report is
`matching2/build/probe_43c230_cluster_rooted/clusters/frame_timer/report.json`.
All four selected contributions compare exactly:

| Function | Extent | SHA-256 | Differences |
| --- | ---: | --- | ---: |
| `AnimationCursor_Tick` (`0x0043C230`) | 133 | `bd823ee212b505f3db6785f9fbc6bbdd7acf8bb50024f79f8dfb36fcc24d039f` | 0 |
| `FrameTimer_Tick` (`0x00404ED0`) | 72 | `5349f4fd279892f975448c3dd7bd04000cead49a6aef8ae46bd11ae580fcbde5` | 0 |
| `FrameTimer_Decrement` (`0x00428DD0`) | 20 | `456bf129ca25bafdf3ff19604ea7e6067aca5da1737cd9fa8bf8dc8b075a8aee` | 0 |
| `FrameTimer_Advance` (`0x0044BF40`) | 88 | `c2c9591f6bcbfcf769892730b28e2da6d7d28af165ecde58ece3622068bcd4fd` | 0 |

The promotion removes one 133-byte game-code assembly region.  It also
generalizes the cluster driver: schema-1 roots are now validated and emitted
for independently reachable functions, matching the schema-2 whole-program
root behavior.
