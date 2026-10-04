# Stage-manager destructor: complete exact C++

Recovered `src/game/stage_manager_destructor_00424ed0.cpp` and its compiler
exception machinery as three complete native contributions:

| Address | Size | Contribution |
| --- | ---: | --- |
| 0x00424ED0 | 325 | `StageManager_00424ed0` destructor |
| 0x00465280 | 11 | Sprite member unwind cleanup |
| 0x0046528B | 10 | Destructor EH handler |

The readable destructor unregisters its two scheduler tasks and clears the
published stage pointer. When the stage-transition flag is set, it marks the
animation resource for removal and passes the stage data to the transition
global. Otherwise it releases animation bank 8, frees the stage data, and
clears that global. Its owned sprite then frees its allocation at owner+0x36C.

The earlier raw-offset cleanup model did not express ownership of the sprite
at +0x14, so the compiler did not generate the required exception frame. The
new class uses the same 0x3AC-byte common sprite ownership as `GameThreadSlot`,
with an explicit stage-sprite typedef. The sprite allocation at member+0x358
therefore lands at owner+0x36C. Compile-time checks verify the sprite offset
and stage-data pointer at +0x45C. The class describes the destructor's view;
it makes no claim about the full extent of an object used by other methods.

Native LTCG selects the retail stack receiver and RET 4. The compiler-only
context keeps the shared sprite destructor at its public ECX thiscall ABI
using the same context-only export used by the recovered GameThread
destructor. The export and all helper anchors are absent from the final image.
The unwind cleanup consequently loads the owner from EBP+4, adds 0x14, and
tail-calls the existing 34-byte sprite destructor at 0x00401FF0.

The dedicated cluster compiles complete helper bodies for scheduler removal,
animation-bank release, and resource marking. The marker's source now accepts
a section-selection macro; its default section and independently owned
machine code are unchanged. The cluster selects only the stage destructor
and its two exception functions, with no inline assembly or modified output.

The native unwind map and FuncInfo occupy exactly 36 bytes at 0x004712F0.
The first probe mistakenly included four bytes belonging to the next retail
data record in that validation extent and was rejected. Restricting validation
to the compiler's complete 36-byte contribution yields an exact table, with
no byte patching or masking. The destructor and both exception functions
were already byte-identical in that first native build.

The handler at 0x0046528B was previously attributed to a generic library
`std::basic_string::_Copy` handler in `clog.obj`. Its retail FuncInfo references
this stage destructor's sprite cleanup. The manifest now assigns it to the
actual compiler-generated application handler and retains the previous
library record as provenance. That library member owned no other region, so
its stale translation-unit entry was removed. The old stage and unwind naked
source files were also removed.

Live Ghidra decompilation confirms the task removals, transition branches,
resource frees and exception chain. Native PE/MAP files, the source and layout,
Ghidra output, and unmasked SHA-256 evidence are retained in
`matching2/build/experiments/stage_manager_destructor_2026_10_04`. All three
function windows and the full 36-byte EH data contribution have zero byte
differences.

Validation: the production probe reports all three contributions EXACT; the
normal full build passes outside the three preexisting equivalent C++ regions.
`make EXACT=1` passes too: the whole 487,936-byte executable matches retail
with the preexisting equivalent regions using their assembly fallbacks.
There are now 2,172 ordinary exact C++ regions / 161,027 bytes and 141 remaining
assembly regions / 128,522 bytes. The handler reclassification reduces toolkit
runtime ownership to 323 regions / 68,438 bytes. The full objective remains
incomplete.
