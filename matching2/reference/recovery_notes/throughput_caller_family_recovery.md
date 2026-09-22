# Throughput recovery: expand proven caller/callee clusters

## Recommendation

Prioritize small-to-medium caller families around already recovered native-LTCG
callees, rather than repeating isolated tiny-leaf screens or starting the largest
unrecovered managers. Optimize for **new byte-exact readable bytes landed per
experiment**, not attempted addresses or semantic-looking output.

The useful unit of work is a dependency cluster: one recovered private ABI can
unlock several callers, and those callers can constrain one another's register
allocation. Keep failed experiments outside the maintained tree. Snapshot an
exact landing before attempting any stretch target.

## Verified landing

The starting working tree already contained uncommitted recoveries. The following
are the additional promotions relative to the session's starting snapshot; no
pre-existing work or compiler-only context is credited again.

| Family | Retail addresses | New regions | New bytes |
| --- | --- | ---: | ---: |
| Boss/render callbacks | `0041D7C0`, `0041EA40`, `0043C2C0`, `0043C3C0`, `0043C410` | 5 | 550 |
| Timer factory | `00422360` | 1 | 67 |
| Script resolver callers | `00450500`, `00450560`, `00450580`, `00450700` | 4 | 192 |
| Total | | 10 | 809 |

The render family extends `msvc/layout/ltcg/anm_batch_flush_00442f50.json`.
The factory uses `msvc/layout/ltcg/timer_factory_00422360.json`, selecting only
the factory and not its compiler-only dependency models.
The script family uses `msvc/layout/ltcg/script_resolver_callers.json`, replacing
the registered standalone resolver cluster. Existing resolver `00450470` remains
exact but is not new recovery. Its shared declaration is now in
`msvc/include/script_resolver_00450470.hpp`.

Verification after all ten integrations:

- Fresh script-cluster probe: all five selected functions exact, including the
  pre-existing resolver.
- `make build`: whole executable exact, **487,936 bytes**, zero compile failures.
- `make progress`: **1,081 C++ regions / 58,137 bytes**; **1,605 assembly regions /
  330,970 bytes**. These are a verification snapshot, not a perpetual status claim.
- `git diff --check`: clean.
- Every promoted `previous_record` equals its complete starting record, and each
  owner is unchanged, including null owners.
- Starting WIP sources at `004014D0`, `00405220`, `00427DA0`, `00428DF0`, and the
  starting `src/data/text_0040.cpp` are unchanged by this recovery batch.

## Next-work ordering and stop rules

1. Salvage exact checkpoints from interrupted workers before spending another
   compiler search budget. The script worker saved its four-function exact packet
   before pursuing a nonmatching larger constructor; only the exact packet was
   integrated.
2. Prefer additional callers of the now-shared render and script interfaces where
   original ABI evidence and dependency bodies are available. Verify every old
   cluster member as well as each new member after expanding a cluster.
3. Give near-matching archive/resource callers one bounded dependency-aware retry;
   promote only on a fresh full-function exact result. They are not part of the
   landing above.
4. Defer scheduler/main-task and larger constructor roots when the remaining
   mismatch is private-ABI topology or global register pressure. Retrying the same
   isolated signature is not a new compiler lever. Consult the scheduler and
   allocator recovery notes, then validate their historical assumptions against
   actual callers before another experiment.
5. Use short worker slices that fit below the runtime's actual timeout. Require a
   saved source/layout packet and exact-probe receipt before optional stretch work.
   Review an integrated wave rather than launching reviewers per tiny leaf.

## Screening and fidelity cautions

- A prologue `push esi` can preserve a register rather than consume a semantic
  input. A screen that rejects every such read has not proved the candidate pool
  exhausted. Check reads before writes, restoration, and real call sites.
- Source labels and successful assembly probes do not prove recovery. Require a
  readable C++ body, a compiler-emitted symbol, exact extent, relocations/targets,
  and exact bytes without rewriting or masking instruction bytes.
- Preserve retail quirks. The VM creation path initializes only the observed
  fields and retains the original null-allocation fall-through; do not invent
  frame initialization or allocation guards to make the code look safer.
- When promoting several members together, merge all required headers, caller
  sources, layout/context changes, and original manifest provenance. Remove the
  superseded cluster registration rather than compiling the same selected body
  through competing clusters.
- Final acceptance is the whole executable hash gate. Individual exact functions
  do not establish a valid global region partition or unchanged neighboring code.
