# Stage startup 0x00417870: byte-exact C++ recovery

`msvc/src/game/stage_entry.cpp` now owns all 1,009 bytes as readable ordinary
C++. `StageStartup` has one context pointer on the stack, returns 0 on success
or -1 on failure, and uses RET 4. The owner is `_StageStartup@4`; the previous
assembly record is retained in the manifest. No inline assembly remains in
this implementation or its native cluster inputs.

Startup waits for animation preparation, initializes the score and lives,
registers the update and draw callbacks, copies the stage configuration, and
creates the stage resources. Playback takes the replay initialization path.
Both exits signal the worker and retire callbacks; failure uses the retail
inlined retirement, while success calls the complete out-of-line helper.
The code retains the original cancellation check, resource failure order,
music setup, timing reset, and final synchronization wait.

## Complete native call graph

`msvc/layout/ltcg/stage_startup_00417870.json` builds five genuine `/GL` inputs
with the existing project compiler flags. The driver contains the complete
already-recovered worker at 0x00417C70, which pushes the published context and
calls startup. Its 12 bytes match exactly and remain owned by the existing
worker source. The startup symbol is separately rooted to preserve its public
stdcall boundary. Every helper in the cluster is a complete ordinary C++
definition; native LTCG chooses its internal register convention.

| Body | Address | Complete extent | Native result |
| --- | --- | ---: | --- |
| StageStartup | 0x00417870 | 1,009 | Exact; selected new owner |
| Worker callback | 0x00417C70 | 12 | Exact; existing owner |
| SetSchedulerValue | 0x00405410 | 57 | Exact |
| RetireCallbacks | 0x00409E20 | 28 | Exact |
| ResetPath | 0x00417800 | 58 | Exact |
| SetGauge | 0x00418B80 | 73 | Exact |
| BeginReplayStage | 0x0042A6A0 | 356 | Same extent and EBX receiver; nonexact |
| RegisterPrimary | 0x00449AE0 | 131 | Exact |
| RegisterSecondary | 0x00449B70 | 131 | Exact |
| CreateCallback | 0x00449ED0 | 74 | Exact |

Only startup is selected from this graph. The replay helper has five
instruction-order difference hunks (84 differing byte positions) in this
context, so it is an ABI anchor rather than a new exact owner. Its separately
maintained `replay_stage_begin_0042a6a0` cluster continues to supply the exact
356-byte production body. The other helpers receive no additional recovery
credit. No body is shortened, padded to its expected extent, or replaced with
an assembly stub.

This resolves the historical private-EBX startup dependency: the ordinary
`BeginStage` declaration and its visible complete callee let native LTCG derive
the retail EBX call boundary. The schema-1 layout supports independently
compiled, unselected helper inputs. Each body occupies its own fixed-address
section in the fresh native PE; the layout gaps receive no recovery credit.

## Source and layout evidence

`include/th10/game/stage_startup_00417870.hpp` provides checked partial views of
the actual run-state and application objects. Representing flags and worker
fields as unrelated standalone scalar globals made whole-program compilation
move loads across stores and calls. Modeling their real containing objects,
whose addresses the genuine helpers already receive, restored retail ordering
without added escape calls, volatile accesses, or barriers. The stage run-state
uses a distinct tag so this recovery does not change the canonical replay
run-state definition.

The two callback flag updates intentionally retain their different source
forms. The primary callback computes the active flags, assigns the context,
then stores the flags; the secondary callback uses a direct masked update.
The existing callback creator's full constructor and flag read are preserved.
Its definition is marked noinline to retain the actual retail call.

The score lookup expresses the difficulty page as bytes using the real
`ScoreRecordSection` and `ScoreRankEntry` sizes and named field offsets. A
scalar `memcpy` reads the high score, and a signed byte reads the continues
count. The runtime play counter also uses scalar `memcpy` through its reserved
byte tail. These forms preserve legal byte access and reproduce the original
address arithmetic. The flag check used for the initial replay-related counter
explicitly reads the low byte. The two timing doubles require four-byte
packing, with checked offsets 0x24 and 0x2C.

Preparatory models are retained under
`matching2/build/experiments/stage_entry_native_2026_10_06/`. Early outputs had
an inlined callback creator, an incorrect double alignment, or callback-pointer
metadata modeled as a relative CALL target; those were diagnosed and replaced
before promotion. Function addresses used as callback values require absolute
pointer bindings. The first valid model using the real object views emitted
1,011 bytes; the byte-page score lookup removed the remaining two-byte address
arithmetic difference and matched all 1,009 bytes.

`score_byte_view/` retains the first equal diagnostic model. `fixed_project/`
and `fixed_probe/` retain the subsequent isolated maintained-layout proof.
The final production report and native MAP independently verify the complete
CODE contribution and address. `maintained-helper-audit.json` in the experiment
directory compares every complete native body above directly with the retail
image after compilation. It documents the nonexact replay anchor explicitly.

Two strict integration checks caught driver/include closure and unused
zero-length scheduler sections. The schema-1 driver now includes the full
startup source, and the scheduler context contains the two complete reachable
registration functions. Unused unrelated methods were omitted as whole
functions. No instruction inside a retained helper was truncated.

Validation on 2026-10-06:

- Native startup contribution: 1,009 bytes exact; SHA-256
  `177320c96d3ef9ad36ed7d1a04824748c1cc584916943bd8c05a9f039d2a510e`.
- Native extraction: zero changed instruction bytes, zero changed address
  operands, zero masks, and no reference bytes used for compilation.
- `make`: full-image and existing equivalence gates passed.
- `make EXACT=1`: all 487,936 executable bytes exact after final source changes.
- Independent whole-file equality: exact; executable SHA-256
  `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
- `git diff --check`: passed.

Progress: 2,248 exact ordinary C++ regions / 192,381 bytes (59.8% of game code);
8 equivalent regions / 33,176 bytes; 66 assembly regions / 95,926 bytes.
Ordinary plus equivalent recovery is 70.2%. The full byte-exact,
assembly-free objective remains incomplete.
