# Script/UI-state destructor: exact C++ and worker unwind

Recovered the complete 491-byte destructor at 0x0042CB60 in
`src/game/script_state_destructor_0042cb60.cpp`. Its owned worker generates the
14-byte unwind cleanup at 0x00465620 and the 10-byte EH handler at 0x0046562E.
All three contributions are byte-exact, with no inline assembly in the source.

The 0x5ACC-byte state has scheduler tasks at +0x0C/+0x10, an animation id at
+0x5D0, 50 owned effect-manager pointers at +0x59E4, a file buffer at +0x5AAC,
and the worker at +0x5AB0. Compile-time checks verify its size and pool/worker
offsets. The destructor stops the worker, unregisters both tasks, releases
animation banks 25 and 26, destroys/frees the effect managers, and sets the
animation and its eligible children to stop frame 1. It frees the file buffer,
clears the published state pointer, and then destroys the worker member.

The first typed model had the correct 491-byte extent and matched the entire
body except 22 bytes in its initial EH-state/vtable scheduling. It assigned a
raw vtable pointer in the C++ body, so MSVC installed EH state zero before that
assignment. Retail first restores the state vtable. The retail table at
0x0046ECF0 points to the 0x0042C5B0 method, whose complete six-byte body returns
0x5ACC. Declaring the state's actual virtual object-size method makes the
compiler's own destructor vtable setup reproduce retail's order. No barrier,
volatile access, fake argument, instruction patch or byte masking is used.

The worker uses the existing `PlatformWorker` representation and Stop body.
Its destructor restores the worker table at 0x004703E4 before stopping. A
compiler-context-only export keeps the out-of-line destructor's public ECX
entry for the unwind tail call. Its normal inlined member destruction matches
the retail tail too. Direct native comparisons confirm both the unselected
16-byte worker destructor at 0x0044C130 and the complete 101-byte Stop function
at 0x0044C150. The neighboring request-stop function at 0x0044C140 is a separate
owner; it is not part of that destructor's compiler contribution.

The cluster compiles complete scheduler removal, bank release and worker Stop
helpers. It selects only the state destructor, worker unwind and EH handler.
Its synthetic destroying caller and context-only export never enter the final
image. The full 36-byte unwind map/FuncInfo contribution at 0x00471670 matches
retail exactly.

The handler previously attributed to a generic `wlocale.obj` library function
is now assigned to the actual application destructor. Previous ownership is
retained in manifest metadata. Existing library regions from that member remain
owned as before. The two replaced naked source files were deleted.

Live Ghidra decompilation confirms the task/bank releases, 50-element loop,
two-list animation lookup, child stop-frame writes, worker calls and exception
chain. Sources, layout, Ghidra output, native PE/MAP files and unmasked SHA-256
evidence are retained in
`matching2/build/experiments/script_state_destructor_2026_10_04`.

Validation: the production probe reports all three contributions EXACT.
`make` passes outside the three preexisting equivalent C++ regions, and
`make EXACT=1` produces the byte-identical 487,936-byte retail executable.
Remaining assembly is 139 regions / 128,017 bytes; ordinary exact C++ is
2,175 regions / 161,542 bytes. The full objective remains incomplete.
