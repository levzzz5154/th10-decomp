# Recovery emitter reset at `0x0040C9A0`: caller ABI audit

## Decision

Keep the exact assembly bodies for `0x0040C9A0`, `0x0040C9D0`, and the
`0x0040E770` ECL dispatcher. The call-site values are now understood, but the
helper graph crosses two private register conventions and the dispatcher is
a fixed-size assembly owner. A standalone ordinary C++ body would need ABI
bridges or a larger conversion cluster; converting only the 48-byte reset
stub would leave those hidden contracts in place.

No source body or call site was changed for this audit. No build, probe, or test
was run.

## Caller evidence

Ghidra reports one direct caller of `0x0040C9A0`: the call at `0x0040FEA7` in
`FUN_0040E770`. The instructions immediately before it are:

```asm
0040FE9E  lea eax,[ebx+0x2c]
0040FEA1  lea edi,[ebx+0x13cc]
0040FEA7  call 0x0040C9A0
```

Thus the reset entry receives a position pointer in EAX (`EBX + 0x2C`) and a
counter-array pointer in EDI (`EBX + 0x13CC`), with no stack arguments. The
call is inside the `0x0040E770..0x00411D2E` fixed-size ECL dispatcher owner.
Changing it to a normal stack-argument C call requires argument pushes and
caller cleanup, which grows that owner. Reassigning the dispatcher as a
semantic/LTCG region is outside this audit's allowed files.

## Helper contracts

When `*EDI > 0`, `0x0040C9A0` saves ESI, copies EAX to ESI, and calls
`0x0041BB00` with:

* EAX = `[0x00477818]`, the manager/pool context;
* ECX = the position pointer previously received in EAX;
* stack words, in callee order: count, `-1`, `-pi/2`, and `2.2`.

The helper is not a normal stack-only call. Its body saves EBX/EBP/ESI/EDI,
reads the count and trailing floats from the stack, uses EAX as the manager
base, and reads three coordinates through ECX. It then either takes its
count-8 special path or allocates an available `0x3F0`-byte manager slot,
copies/clamps coordinates, sets polar and render fields, and stores the
`-1` value. Ghidra lists thirteen direct callers, so this is a shared private
ABI boundary rather than a reset-specific helper.

`0x0040C9D0` is stdcall with one explicit stack argument: the counter-array
pointer, cleaned by `ret 4`. It also consumes ESI as a hidden position pointer.
It seeds and advances RNG state, processes counter slots 1 through 11,
computes ellipse offsets, calls the custom `0x0041BB00` allocator for positive
counts, and clears slots 1 through 12. Back in `0x0040C9A0`, slot 0 is then
cleared. `0x0040C9D0` has another direct caller at `0x0040E66E` in
`FUN_0040E5F0`; that caller establishes its own ESI position pointer before
passing the counter pointer. Converting the reset stub alone cannot turn this
into an ordinary typed helper call without preserving or resolving the hidden
ESI contract.

## Next useful conversion boundary

A safe semantic cutover needs an explicit typed boundary for the pair
`(position, counters)` and ABI adapters for both helper contracts, or a broader
conversion that includes the scatter helper and its RNG/vector dependencies.
The current task forbids editing the dispatcher region mapping, so this pass
records the caller and helper facts while retaining all three exact bodies.
