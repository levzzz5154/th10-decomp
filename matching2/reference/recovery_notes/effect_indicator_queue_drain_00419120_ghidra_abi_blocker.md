# Effect indicator queue drain `0x00419120`: live Ghidra ABI audit

Audited the open `th10.exe` program in the `th10` Ghidra project. The manifest
row in `matching2/msvc/regions.json` spans 1,317 bytes (`0x00419120` through
`0x00419644`), matching the function body through its `RET 8`. Ghidra reports
346 instructions, 58 basic blocks, and 12 calls. Its displayed prototype,
`undefined4 FUN_00419120(int param_1, int param_2)`, omits an input that is
live in EAX and therefore does not describe the call ABI.

## Entry and caller evidence

The only Ghidra caller is `FUN_00419650`. At `0x00419677` it loads the queue
head from `[EBX + ECX*4 + 0x1c]` into EAX, pushes `1` at `0x00419672`, pushes
the state pointer from EBX at `0x0041967b`, and calls `0x00419120` at
`0x0041967c`. At entry, the callee tests EAX and reads the current queue node
through `[EAX]` and its successor through `[EAX+4]`. It loads the first stack
argument into EBP at `0x00419126`; the second stack argument is read as the
release flag at `0x00419612`. The function returns zero in EAX and uses
`RET 8` at `0x00419642`.

This is a mixed private-register / stack ABI: queue head in EAX, state pointer
at `[ESP+4]`, and release flag at `[ESP+8]`. Ordinary MSVC x86 `cdecl`,
`stdcall`, `thiscall`, and `fastcall` signatures cannot declare the queue head
in EAX. A semantic body with a normal C++ signature would receive a different
register/stack layout at the existing call site, so this function remains a
naked assembly body. No Ghidra prototype edit was made.

## Behavior visible in the live listing

The routine walks queued nodes and decrements the count at node offset `+0x60`
when the tag at `+0x68` is zero or matches the global tag. Nodes with a
positive count are skipped. For an expired node, it retires the existing
handle in the current rotating slot, advances a node float by a scaled value,
creates or looks up an animation, configures its alpha and vector values, and
copies the resulting position and node data into the ten-slot state. The node
mode selects one of three formatting helpers and one of three position
adjustments. It sets the animation flags, advances the slot modulo ten,
unlinks the node from both neighboring links, clears those links, and frees
the node when the second stack argument is nonzero. The saved successor in a
stack local drives the next iteration.

Direct calls in the Ghidra listing include `0x00448db0`, `0x004491c0`,
`0x0041ab70`, `0x00447bb0`, `0x00447a50`, `0x00447ae0`, `0x00463b2c`, and the
free routine at `0x004524a1`. These calls are already preserved in the
assembly implementation; this audit did not attempt to infer new prototypes
for them.

## Integration if the caller ABI is changed later

A normal semantic candidate could use an ordinary fastcall contract such as
`int __fastcall EffectIndicatorQueue_Drain(EffectIndicatorNode* head,
EffectIndicatorState* state, int release)`: head in ECX, state in EDX, release
on the stack, and zero returned in EAX. That contract does **not** match the
current call site. Converting the leaf therefore requires changing
`FUN_00419650` to move the head to ECX and state to EDX, then updating the
source declaration/alias and the manifest symbol to the candidate's MSVC
fastcall symbol (the old `_asm_FUN_00419120_00419120` cdecl assembly symbol is
currently declared in `include/asm_symbols.hpp`). Without that caller and
alias integration, keep the existing `asm_FUN_00419120_00419120` symbol and
body.

No source body, shared header, caller, manifest, or layout was changed in this
audit; only the source-local audit comment and this note were added. No build,
probe, or test was run.
