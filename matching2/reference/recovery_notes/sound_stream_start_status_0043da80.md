# Sound stream start/status at `0x0043DA80`

## Algorithm

The routine reads a stream pointer from the owner at `+0x5208`. A null pointer
returns `-1`. Otherwise it calls `0x0044D440` with arguments `0` and `1` and
returns `-1` if the helper status is negative. On a nonnegative status, it
copies the one stack argument to the owner field at `+0x5210` and returns `0`.

## Parameters and return

- Owner/context: implicit in `ESI`; the observed accesses are `ESI+0x5208` and
  `ESI+0x5210`.
- Value: one 32-bit value in the single 4-byte x86 stack slot. The retail
  load and store operate on the full 32-bit slot/field, so the recovered source
  keeps the value as `unsigned int` without truncation.
- Return: `0` when the start helper succeeds, `-1` for a missing stream or a
  negative helper status. Retail removes the argument slot with `RET 4`.

## Ghidra evidence

Ghidra analysis of `0x0043DA80` shows the edge at `0x0043DA8E` to
`0x0044D440`, with pushed constants `0` and `1`, and the two branches described
above. The helper analysis confirms it takes its stream from `EAX`
(`mov edi,eax` at entry), also reads the inherited `ECX` interface context,
returns an `int`, and uses `RET 8`. Ghidra reports no incoming references to
`0x0043DA80`; the helper has two direct call sites, `0x0043DA8E` and
`0x0043E183`.

## ABI and exactness limitation

This is a readable semantic body, not a byte-equivalent replacement. Retail
passes the owner privately in `ESI`, while the helper expects its stream in
`EAX`, two stack arguments, and the inherited `ECX` interface context. MSVC's
ordinary C++ calling conventions cannot express these private register
inputs. The helper function-pointer alias expresses the semantic receiver and
two arguments as a `__thiscall`; that places the receiver in `ECX`, while
retail requires it in `EAX` and also consumes an `ECX` context. It documents
the operation only and is not safe as a native ABI bridge without an adapter.
No caller references to `0x0043DA80` were found, and no build or probe was run
for this source.
