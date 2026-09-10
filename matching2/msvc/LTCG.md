# Native LTCG clusters

Some retail functions use register conventions that MSVC chooses only during
link-time code generation. The maintained build routes those functions through
[ltcg_cluster.py](../tools/matching/ltcg_cluster.py). Their ordinary C++ source
still compiles with MSVC 13.10.6030; LINK 7.10.6030 generates the final bodies
before the normal fixed-address link and whole-executable byte checks.

The project manifest lists each cluster layout under `ltcg_clusters`. A layout
must identify the complete set of semantic regions owned by its maintained
source, with identical symbols, addresses and extents. That source is excluded
from the ordinary COFF compilation route. Each native cluster has an explicit
compiler-context driver and declared headers. Compiler context is separate from
recovered application code and contributes no progress bytes.

## FrameTimer recovery

[frame_timer.cpp](src/math/frame_timer.cpp) implements the five-word timer in
[timer.hpp](include/th10/math/timer.hpp). The remaining GameState timer reset
in [timer.cpp](src/math/timer.cpp) still uses assembly.

| Method | Retail address | Bytes | Actual native ABI |
| --- | --- | ---: | --- |
| `FrameTimer::Tick` | `0x00404ED0` | 72 | `this` in ESI; RET |
| `FrameTimer::Decrement` | `0x00428DD0` | 20 | `this` in ESI; count in EAX; RET |
| `FrameTimer::Advance` | `0x0044BF40` | 88 | `this` in ESI; delta at `[ESP+4]`; RET 4 |

The ordinary source declarations use `__thiscall`. The synthetic array caller
in [frame_timer_context.cpp](layout/ltcg/frame_timer_context.cpp), compiled in
the same LTCG unit, causes MSVC to select the observed internal conventions.
This caller is compiler context, not a recovered game function or evidence of
the original translation-unit boundaries. It is never copied into the game.
Existing unrecovered callers retain their fixed-address assembly aliases.

Both advancement methods save the previous integer count first. Speeds strictly
between the two bounds use the normal-speed path. `Tick` increments the count
and adds one frame; its scaled path converts the value of `elapsed += *speed`,
retaining the x87 sum through the field store. `Advance` converts the field
after its branch, so it reloads the stored binary32 value. `Decrement` negates
the supplied count before converting it to a float and advancing.

The native cluster reproduces every instruction byte and address operand of
these three methods. A host C++ behavior test covers finite, in-range examples;
the native byte check establishes the custom ABI and x87 instruction details.
The host test does not establish portable NaN, out-of-range conversion or
signed-overflow behavior.

## Placement and provenance

[frame_timer.json](layout/ltcg/frame_timer.json) specifies dedicated `.text$`
contributions for each method and the compiler context. Generated ordinary C++
zero-filled arrays occupy native-link layout gaps, including the gap before
the compiler's `1.0f` constant. Only those gap objects have their COFF section
flags/alignment adjusted. The tool checks that every array is zero-filled,
contains no relocations and retains its exact payload. None of these arrays is
selected as game code.

A section-free COFF object supplies absolute external-symbol metadata. For
native LINK 7.10, an absolute symbol referenced by REL32 contains the target RVA;
absolute data symbols contain their full VAs. The manifest records the intended
VA and binding kind explicitly. This produces the final operands through the
linker, without instruction rewriting.

Every build uses a newly created native output directory. Missing compiler or
linker outputs fail; old objects and reports cannot serve as a fallback. The
build records current implementation, driver, layout and header hashes, checks
compiler include reports against declared inputs, and verifies inputs and
compiler/linker binaries remain unchanged during compilation.

Before selecting any method, the tool cross-checks the PE and MAP, exact symbol
address, compiler object origin and named CODE contribution. That contribution
must start at the symbol and have exactly the entire declared method extent.
Interior symbols, undeclared functions, altered context/layout, misplaced
constants and incorrect bindings fail validation.

Only the three validated, complete compiler-generated bodies are copied into
COFF containers. Their bytes remain unchanged; there are no remaining
relocations because the native linker has resolved them at their final
addresses. The outer linker asserts those same addresses and extents. The
existing unmasked `.text` and complete executable hashes remain the acceptance
gates. Normal cluster builds read no retail bytes, assembly baseline, probe
outputs or prebuilt implementation objects.

The main `port-report.json` identifies each native cluster and includes its
compiler/link commands, source and toolchain hashes, native PE/MAP hashes,
actual ABIs and unchanged-body export report. Detailed outputs remain under
`build/msvc/clusters/<name>/`. Compiler context and layout-gap bytes are explicitly
reported as unselected and excluded from recovered-code progress.

Host-only rejection tests live in
[ltcg_cluster_test.py](../tests/ltcg_cluster_test.py). The separate
[ltcg_semantic.py](../tools/matching/ltcg_semantic.py) remains available for
exploratory native-link experiments; an experiment alone does not classify a
maintained region as recovered C++.
