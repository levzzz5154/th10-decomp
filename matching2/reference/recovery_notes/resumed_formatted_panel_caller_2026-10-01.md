# Verified checkpoint: ordinary formatter and real panel display

Two complete functions were recovered as native C++: the ordinary variadic
formatter at 0x00401630 (85 bytes) and its genuine panel-display caller at
0x00429A70 (182 bytes). All seven complete functions in the FPS/formatter/queue/
panel native closure match literally across 969 bytes. The existing five
functions and their ownership records are preserved without additional credit.
The real scheduler wrapper at 0x0042A430 establishes the panel's unused nominal
ECX slot and actual EDX receiver. Six original call edges are independently
verified; no synthetic caller supplies the variadic helper's private registers.

Since permissions were fixed, 38 complete routines/4,233 bytes have been
recovered: 35 former assembly routines/4,203 bytes and three narrowly corrected
game exception handlers/30 bytes. The earlier 23-routine checkpoint was 2,935
bytes, or 0.7112% of the 412,672-byte text section. The current gain is 1.0258%.
Fully assembly-free C++ now covers 1,901 regions/100,243 bytes, or 24.2912%.
Semantic ownership is 1,906 regions/104,694 bytes; five older x87 semantic
regions/4,451 bytes still contain assembly. Remaining assembly is 397 regions/
218,254 bytes; libraries 320/66,450, embedded text data 7/7,779, and padding
1,770/15,495. The goal remains active and incomplete.

The full executable remains literally identical to the 487,936-byte original,
SHA256 2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040.
Current build: matching2/build/resumed_wave13_msvc_2026_10_01. All 1,876 maintained
sources completed without failure. Whole and
native receipts: wave13_verified.json and wave13_native_verified.json under
matching2/build/experiments/wine_startup_diagnosis_2026_10_01. The whole auditor
checks the current source/manifest snapshot and all 38 new complete owners. The
native auditor checks 53 complete bodies; 47 match across 7,091 bytes, six
nonmatching models and three other contexts remain unselected. Its 1,963 new
bytes cover a historical native-cluster subset, rather than the full 4,233-byte
permissions-baseline total. No framework, compiler-profile, masks, oracle-fed
inputs, instruction rewrites, or address-operand rewrites were introduced.

The genuine Stats task factory model at 0x00413350 emits the complete original
151-byte extent but differs in 52 bytes, beginning with zero scratch register
allocation. Eight supporting bodies/1,100 bytes match. The strict probe rejects
the factory, and it remains assembly in main with zero new credit. The model,
fresh live Ghidra evidence, hashes and independent verifier are frozen under
native_fps_task_owner_2026_10_01. No model header, callback signature, task flags,
or secondary-scheduler source changes were integrated.

An independent inventory establishes 20 original game exception-handler
families/936 routine bytes, with 168 bytes of original CC alignment and 18
handler rows misattributed as library. Original parent pushes, FuncInfo records,
unwind tables and complete actions establish ownership. This inventory alone
provides zero recovery credit or reclassification; PE adjacency does not prove
original compiler contribution boundaries. Its evidence and executable verifier
are under constructor_eh_owner_inventory_2026_10_01.

The final formatter integration recipe, strict probe, live original evidence,
full native contributions and frozen independent verifier are under
native_formatted_panel_caller_2026_10_01. Prior wave12 receipts remain historical
snapshots. Current proof paths and hashes accompany this note in its evidence JSON.
