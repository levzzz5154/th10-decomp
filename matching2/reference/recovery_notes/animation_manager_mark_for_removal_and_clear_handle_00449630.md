# `AnimationManager_MarkForRemovalAndClearHandle` (`0x00449630`)

## Current status

Keep this 21-byte region in its retail assembly source until its ESI live-in is
reproduced by an exact C++ call cluster. Its semantic behavior is understood;
the blocker is the fixed-address entry ABI. Earlier ordinary C++ candidates
assigned the handle pointer to a public argument register and changed the
call/prologue sequence.

## Live Ghidra evidence (`th10.exe`)

Ghidra reports body `0x00449630..0x00449644` (21 bytes, including the `RET` at
`0x00449644`), one callee,
`0x004492A0`, and three direct caller functions. The retail listing is:

```text
00449630  mov eax,[esi]          ; handle value
00449632  mov edx,[491c10]       ; global animation manager; ECX passes through
00449638  push eax
00449639  call 004492a0          ; SetFlag(manager in EDX, handle on stack)
0044963e  mov dword ptr [esi],0  ; clear caller's handle after the call
00449644  ret
```

Ghidra's decompile expresses the body as `SetFlag(global_manager, *ESI)`
followed by `*ESI = 0`. `SetFlag` (`0x004492A0`) takes the handle as one stack
argument, looks up the animation through `0x004491C0`, sets bit `0x04000000`
in the object's flags at `+0x35C`, and, when the object's child flag at
`+0x18` is clear, sets that bit on objects referenced by the child-list nodes
at `+0x14`. `SetFlag` returns with `RET 4` to remove its pushed handle
argument; ECX passes through as the helper's unused first fastcall parameter.
The wrapper itself ends with a plain `RET`.

Ghidra reports seven direct callsites across these three functions:

| Caller | Callsite(s) | ESI setup |
| --- | --- | --- |
| `0x0040BD80` | `0x0040C08E`, `0x0040C0DB`, `0x0040C128` | Each path forms ESI as the address of one handle in an interpreter state array at `[EBP+0x90+index*4]`. |
| `0x0040E770` | `0x0040ED7D`, `0x0040F002`, `0x0040F0CB` | Each path forms ESI as an animation handle slot at `[EBX+0xC0+index*4]`; on the first path it later writes the selected handle through `[ESI]`. |
| `0x00428630` | `0x004287DD` | The player pickup sweep forms ESI as the slot address `[EBX+0x44]` before the call. |

The callers do not pass the handle pointer in ECX, EDX, or on the stack. The
fixed function relies on that pointer arriving in ESI, then loads the current
handle value from it. An ordinary standalone MSVC x86 declaration cannot
name ESI as a formal argument.

## Failed exact-output route and next dependency

The earlier D2702 experiment kept the exact wrapper and legacy semantic
model, then tried a measured extern-C `__fastcall` candidate. That candidate
was 24 bytes with 22 differing bytes; the retail region is 21 bytes. No C++
candidate was retained. `__fastcall` does not make the incoming pointer an
ESI argument, so changing the prototype alone cannot solve the mismatch.

The next useful experiment is a native-LTCG cluster with semantic versions of
all three direct caller functions (or equivalent contexts that preserve their
ESI handle-slot values), this wrapper, and the `0x004492A0`/`0x004491C0`
`SetFlag`/`Find` dependency chain. Include the neighboring `0x00449450`
handle-validation path if the shared caller model needs it. The cluster must
make ESI's slot pointer a compiler-visible live value at the entry, preserve
EDX as the manager and the handle as the one pushed stack key for `SetFlag`,
and emit exactly 21 bytes before the production representation can change.
