# Animation-manager constructor: measured C++ candidate, not promoted

The 2,315-byte constructor at 0x00445900 remains owned by its assembly source.
A new standalone experiment represents its three sprite members as native C++
objects: the 4,096-element pool at +0x68, the middle sprite at +0x3AD130, and
20 layer sprites at +0x72DAE4. The complete owner has size 0x732460. Automatic
member construction and cleanup now generate the expected three unwind
functions and exception handler; the old callback-only candidate did not.

The candidate also represents all twenty 36-byte scheduler task allocations,
the two primary registrations and eighteen secondary registrations, matrix
initialization, the pool reset loop, and the final device call. Scheduler
callback addresses are data immediates in cluster bindings, rather than
relative-code bindings (which produce image-relative values for address-taking).
The recovered callback 0x004486F0 uses priority 23, not 22.

A pointer-taking inline flag helper and a force-inlined sprite constructor
produce the complete 88-byte sprite constructor at 0x00402050. Direct member
bit assignments originally produced 152 bytes and an out-of-line middle-sprite
constructor call. The sprite destructor retains its complete 34-byte ECX ABI
via a compiler-context-only export. Entity_Init needs an explicit section in
its compiler-only copy because its production definition uses the default
text section.

Probe 2 emits a 2,296-byte manager constructor. The middle-sprite initialization
and scheduler allocation patterns now follow retail, but LTCG keeps the pool
pointer in EDX and the loop count in EDI. Retail keeps the pointer in EDI and
spills the count at stack +0x10. A volatile loop counter in probe 3 produces
2,308 bytes and restores the expected stack-sized exception frame, including
the ordering of its prologue. The pointer still remains in EDX, and the loop
uses ECX instead of EAX for the spilled counter. This changes subsequent
register allocation as well. Probe 3 is the saved baseline.

The cluster is deliberately not accepted or installed: its declared retail
extent is larger than its emitted contribution, and the compiler context has
an additional placement-new null branch (22 emitted bytes rather than the
initial 5-byte assumption). These are real native layout differences. No bytes
were padded, truncated, patched or masked to claim a match.

Exporting Entity_Init after matching declarations did not resolve the loop:
probe 6 emits 2,310 bytes and materializes the otherwise dead ECX argument.
Disabling frame-pointer omission only for the unselected helper changes its
extent from 273 to 276 bytes and still leaves the constructor at 2,308 bytes
(probe 7). Neither variant was retained in the baseline helper.

Source/layout snapshots, the initial setup script, seven native probe outputs,
and disassembly comparisons are retained under
`matching2/build/experiments/anm_storage_constructor_2026_10_04`. The snapshot
contains only a candidate; production region ownership is unchanged. Next work
should investigate the pool call's register-preservation visibility before
changing the already matching task-construction expressions.

## Follow-up: call visibility and source ABI

Five additional probes are archived in the same experiment directory. Making
Entity_Init use an ordinary, non-intrinsic CRT memset preserves its semantics
but causes native LTCG to select a private ESI receiver. Probe 8 emits a
283-byte unselected helper and a 2,301-byte constructor. Taking the helper's
address in the compiler context forces its public EDX argument, but also
materializes the dead ECX argument on every loop iteration: probe 9 emits a
287-byte helper and a 2,312-byte constructor. Neither gives retail's loop.

A fastcall entry context cannot be linked directly by the present cluster
entry-name handling (probe 10, unresolved `_@ConstructAnmStorageContext@8`).
An exported fastcall adapter with a normal stdcall entry was therefore tested
instead: it still calls the private ESI helper and emits a 2,294-byte owner
(probe 11, ordinary loop counter). Changing the original initializer to a
one-argument cdecl source declaration, with intrinsic memset restored, yields
the same 273-byte helper and 2,296-byte constructor as the earlier nonvolatile
baseline (probe 12). No constructor, helper, manifest or ABI changes from these
experiments were promoted. The next source lever must distinguish native input
argument allocation from the optimizer's register-preservation knowledge.

## Recovered 2026-10-05

`src/app/anm_storage_construct_00445900.cpp` now compiles to the retail 2,315
bytes, the three unwind functions and the frame handler in the
`anm_storage_construct_00445900` cluster. `make` and `make EXACT=1` pass.

The missing fact was the linkage of the callee, not the loop: Entity_Init
(0x00401DE0) is a header-inline function. None of its ten retail call sites
relies on EDX surviving the call, although the body never writes EDX. Declared
`inline` (COMDAT, defined in every unit that uses it) instead of out-of-line
`noinline`, the compiler-context copy keeps its 273 bytes and its EDX argument,
and the constructor's loop keeps the pool pointer in EDI, copies it to EDX per
iteration and spills the plain `int remaining` counter to the stack - no
`volatile` needed. A callee stand-in that really clobbers EDX is not an
alternative: LTCG then moves the argument to ECX.

The compiler context is a placement-new caller (22 bytes, with the null
branch). The handler at 0x004657A5 was previously labelled as a libcpmt
`time_get` handler; it belongs to this constructor.
