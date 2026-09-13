# Joystick probe / text-log caller cluster (`0x0044A0C0`, `0x0044B810`)

## Disposition

`0x0044A0C0` is now readable semantic C++ and is byte-exact in the
production image.  Its 105-byte body is linked with the already recovered
`TextLog_0044b810::Append` at `0x0044B810` as one native MSVC 7.1 `/LTCG`
cluster.  The complete executable remains byte-identical to the retail
oracle.  The old assembly symbol `_asm_FUN_0044a0c0_0044a0c0` remains an
address alias for callers that have not yet been recovered.

## Ordinary-TU blocker

The probe reads the WinMM `joyGetPosEx` slot at `0x00466280`, queries devices
zero and one with a 52-byte `JOYINFOEX`-compatible record, and, when both
queries succeed, appends the message at `0x00470580` to the singleton log at
`0x00474F70`.  Otherwise it calls the `joyGetDevCaps` slot at `0x0046627C`
for the capabilities block at `0x004918B8` and returns zero.

A readable standalone `__stdcall` implementation produced the correct 105
bytes except for the logger call.  Retail moves the singleton into `ECX` and
performs caller cleanup for the format argument; an ordinary member
declaration emitted a stack `push` of the receiver and the wrong cleanup
amount.  The mismatch was exactly the custom variadic-member ABI already
observed in `TextLog_0044B810`, so changing local types or the probe's control
flow could not solve it per region.

## Native-LTCG experiment

The existing schema-1 layout
`matching2/msvc/layout/ltcg/d3d_text_log_append_0044b810.json` now includes
the probe as an `additional_sources` input.  The probe is compiled separately
with `/GL` in `.text$01joystick`; the logger remains in `.text$03textlog` and
the synthetic context is in `.text$05context`.  The context calls the probe
and the logger through the same native `/LTCG` invocation, making the private
receiver and caller-pop convention available to the backend.  Absolute
bindings preserve the two WinMM slots, the singleton log, and the existing
CRT/import targets; no output bytes are patched or masked.

Reproduce the proof with:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/platform/joystick_probe.cpp \
  --output matching2/build/probe_joystick_cluster --json
```

The resulting report is
`matching2/build/probe_joystick_cluster3/clusters/d3d_text_log_append_0044b810/report.json`.
It records zero instruction-byte changes for both selected functions:

| Function | Extent | SHA-256 | Differences |
| --- | ---: | --- | ---: |
| `Joystick_Probe` (`0x0044A0C0`) | 105 | `35af7bf413eea413af24bdcc336b1857d7a2cb28115e4615780b9452f5dbade5` | 0 |
| `TextLog_Append` (`0x0044B810`) | 201 | `e656c1d4e04a4fe1113db4f817c541683da7b711b7a93fbe82fb20b8fdf2cbbb` | 0 |

The two bodies are exported from the same native cluster, and the normal
`make verify` gate passes with a 487,936-byte exact executable.  The
promotion removes one 105-byte game-code assembly region; the logger was
already semantic and is unchanged in the non-semantic accounting.

## Reusable lesson

When a caller's only near miss is a callee's private register/caller-cleanup
convention, keep both definitions visible to one native LTCG link.  The
declaration may still spell an ordinary member function; the selected ABI is
an optimizer decision and is not expressible in that C++ declaration alone.
