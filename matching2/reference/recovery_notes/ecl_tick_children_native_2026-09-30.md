# ECL root and child traversal at 0x0044FD10

2026-09-30. The complete 146-byte function is recovered as ordinary C++ in
`src/script/ecl_vm_children.cpp`, with the typed owner/list view in
`include/th10/script/ecl_children.hpp`. Native MSVC 13.10 LTCG emits every byte
of the retail body, including its private EDI owner argument, stack float,
EAX status result and RET 4. There is no inline assembly or assembly entry shim.

## Behavior and layout

The owner keeps its active interpreter at +4, its embedded root at +8, and its
embedded list node at +0x1030. The existing reset recovery at 0x0040C730 also
identifies the 0x1024-byte interpreter and the intervening script pointer at
owner +0x102C. The new view keeps the interpreter opaque, since this traversal
never accesses its internals. Compile-time checks cover the interpreter extent,
all accessed owner offsets, the script offset and the twelve-byte node size.

Traversal begins at the embedded node and saves each successor before running
its interpreter. It publishes the node's interpreter through the owner's active
pointer. A nonzero result from the first/root interpreter immediately returns
-1. For later heap children, a nonzero result frees the active interpreter,
repairs both neighboring links, clears the removed node's links and frees that
node. Traversal continues from the saved successor. Normal completion restores
the active pointer to the embedded root and returns zero. The early failure
path preserves retail's active-pointer state.

Live Ghidra MCP disassembly confirms the EDI owner, both calls at 0x0044FD33
and 0x0044FD45, the two free calls and both RET 4 paths. Fresh xrefs identify
the existing callers at 0x0040E0FE, 0x0040E205 and 0x0042BFFE. The dispatcher
entry at 0x0044E1A0 consumes its interpreter in EAX and its delta on the stack.

## Compiler context and selection

`layout/ltcg/ecl_tick_children.json` selects only the complete 146-byte traversal.
Its separate driver has a synthetic array-walking caller and a 14-byte dispatcher
ABI stand-in at the actual dispatcher address. The stand-in's time/status view
is deliberately synthetic and makes no claim about dispatcher behavior. It
establishes the EAX interpreter, stack delta and RET 4 call contract. Neither
that stand-in, the 47-byte caller nor layout gaps enter the game image or count
as recovered bytes. The actual 7020-byte dispatcher remains separately owned
by `src/script/ecl_core_interpreter.cpp` and remains assembly.

The initial ordinary model and array-loop context emitted an exact 146-byte
body after measuring the unselected context extents. No instruction changes,
address-operand edits or masks were needed. The production probe recompiled
the final maintained source/header/layout/driver and again matched every byte.
The native body and exported COFF body both have SHA-256
`009341c6a7d4a5e2c0eb2536c14e4ca4d2452f6bb01152faae149e9e95a20eb3`.
Legacy caller bindings still point at 0x0044FD10, so existing callers need no
source changes. Whole-image verification checks the real dispatcher and caller
bodies together with the recovered traversal.

## Verification and remaining work

Reproduction:

```sh
python3 matching2/tools/matching/probe.py --source src/script/ecl_vm_children.cpp
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
make progress
```

The focused probe is exact for the entire 146-byte region. The full build
compares all .text bytes and the complete 487,936-byte executable with the
independent oracle. The executable SHA-256 is
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The companion evidence JSON retains final source fingerprints, native compiler
provenance, complete function comparison, Ghidra evidence and whole-image proof.
Scratch artifacts are under `matching2/build/experiments/ecl_tick_children_2026_09_30`.

Earlier experiments in this work period did not pass and were not selected.
Ten animation-registration counter shapes retained register/scheduling or
extent differences; the closest complete back-registration body was 118 bytes
with forty differing bytes. Replay-pool cursor/zeroing variants retained the
six-byte store/LEA difference or a seven-byte zeroing preparation difference.
Those maintained routines remain assembly. Their scratch artifacts are under
`animation_registration_2026_09_30` and `replay_pool_schedule_2026_09_30`.

Manifest accounting is now 1,841 semantic regions / 96,453 bytes and 458
assembly regions / 226,444 bytes. Some semantic rendering sources still contain
inline x87 blocks. The full no-inline-assembly objective remains incomplete.
