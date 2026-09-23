# ECL scratch frame push/pop pair: semantic models, cluster not rechecked

2026-09-23. This note supersedes the earlier Pop-only source/layout discussion
in this file. It also qualifies the 2026-09-19 exact result in
`ecl_push_scratch_value_00450690_wave13.md`: that 64-byte result used the
Push-only compiler context and layout. The current shared pair context has not
been compiled or compared, so neither pair member has a current exact-output
claim.

## Live Ghidra evidence

The connected Ghidra project is `th10`, program `th10.exe` (x86, image base
`0x00400000`). Both functions are leaves that use the same scratch frame passed
as `&vm->frame` in EAX. They read the frame's stack pointer at `+0x1000` and
frame base at `+0x1004`.

### Push, `0x00450690..0x004506CF` (64 bytes)

Ghidra's decompilation and disassembly show that Push reads the old stack offset,
adds its size, and returns `-1` in EAX when the result is at least `0x1000`.
Otherwise it records the new offset; if `next + 4 < 0x1000`, it writes the
previous frame base at `frame + next` and advances the offset by four. It then
sets the frame base to the old offset and returns zero. The only code xref is
the call at `0x0044E446` in `FUN_0044E1A0`. Immediately before that call, the
caller puts `&vm->frame` in EAX and the byte count in ECX; no stack argument is
pushed. Retail ends with a plain `RET`.

### Pop, `0x004506D0..0x004506F8` (41 bytes)

Pop subtracts four from the stack offset. When the result is nonnegative, it
stores that offset and reloads the frame base from `frame + offset`. In either
case, it restores the old frame base into the stack-offset field and returns
zero in EAX. Its two code xrefs are `0x0044E211` and `0x0044E453`, both in
`FUN_0044E1A0`. The first caller forms `ESI + 8` in EDI and copies it to EAX;
the second forms `ESI + 8` directly in EAX. Neither pushes an argument. The
body ends with a plain `RET`.

Thus the shared C++ model in [ecl_scratch_frame_00450690.hpp](../../msvc/include/th10/script/ecl_scratch_frame_00450690.hpp)
has `scratch[0x1000]`, `sp` at `+0x1000`, and `frame_base` at `+0x1004`. Push
and Pop are ordinary C++ member implementations in their respective source
files. No inline assembly is used.

## Pair layout changes

The registered layout path is still
`layout/ltcg/ecl_push_scratch_value_00450690.json`; it now declares Pop as an
`additional_sources` input and a second selected function. The driver includes
the primary Push source only. Pop is compiled from its own additional source,
which avoids defining it twice in the driver. Both sources include the declared
shared header.

The old Push-only layout left `0x004506D0..0x004506DF` as a 16-byte gap and
placed its compiler context at `0x004506E0`; that occupied Pop's retail entry.
The pair layout instead places Push in `.text$01push` at `0x00450690`, Pop in
`.text$02pop` at `0x004506D0`, a seven-byte `.text$03layout` gap at
`0x004506F9..0x004506FF`, and the synthetic context at the next 16-byte
boundary, `0x00450700`. The image head gap remains `0x00401000..0x0045068F`
(325,264 bytes).

The driver's added Pop call establishes a real C++ call edge for the EAX
receiver convention, instead of rooting Pop without any call-site evidence.
However, the layout's `context.size` is still the old Push-only value (42); the
updated driver's emitted extent is unknown. This metadata is therefore
provisional and the registered cluster is **not build-ready** until that size
and both emitted bodies are checked under the allowed native-LTCG workflow.
Because this task explicitly forbids builds, probes, and tests, no compiler
output was generated here and no byte-exact result is claimed for either
member in the pair. The earlier Push exact result applies only to the old
Push-only context.

Pop's prior standalone native-LTCG measurement was 41 bytes but differed in the
encoding of the decrement: retail uses `add ecx,-4`, while the candidate used
`sub ecx,4`. That historical result does not prove what the current shared
context emits.

## Manifest integration

The static cluster registration has promoted `0x004506D0` to
`?PopScratchValue@EclFrame_00450690@@QAEHXZ`, preserving the old record as
`previous_record`. The `symbols` map still binds
`_asm_ECL_PopScratchValue_004506d0` to `0x004506D0`, so the interpreter's
existing inline-assembly call sites retain their raw address alias. No change
was made to `asm_symbols.hpp`. Registration ran only the helper's static
ownership/range checks; it did not compile anything. Until an allowed exact
recheck succeeds, neither Pop nor the modified Push cluster is byte-exact.
