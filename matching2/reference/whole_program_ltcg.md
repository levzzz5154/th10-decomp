# Whole-program LTCG recovery: measured pipeline

2026-09-13. The worker shutdown callers at `0x0044C100` and `0x0044C130`,
and their shared callee at `0x0044C150`, are now ordinary C++ and byte-exact
together: 36 + 16 + 101 bytes. All three were assembly regions before this
change. The complete 487,936-byte executable also passes its existing retail
hash gate.

## What the experiment established

MSVC 13.10.6030 / LINK 7.10.6030 can choose the retail private calling
convention across **separate `/GL` translation units**. A unity source is not
required for this cluster. The relevant boundary is the native optimization
scope: both sides of the private call must be visible to the same `/LTCG`
invocation, and the callee must remain eligible for ABI changes.

The baseline experiment uses two maintained C++ implementations. Their
declarations remain ordinary member functions. Both definitions use
`__declspec(noinline)` to retain the functions being recovered. There are no
register adapters, assembly bodies, instruction substitutions, or byte masks.
The source model produced the matching pair; the experiments change compiler
visibility rather than tune individual function bodies.

| Experiment | Caller bytes | Callee bytes | Callee receiver | Retail match |
| --- | ---: | ---: | --- | --- |
| Both sources separately `/GL`, one `/LTCG` link | 16 | 101 | ESI | exact |
| Neither source `/GL`; linker still `/LTCG` | 11 | 105 | ECX | different |
| Native caller, `/GL` callee | 11 | 105 | ECX | different |
| `/GL` caller, native callee | 11 | 105 | ECX | different |
| Both sources included in one `/GL` unity source | 16 | 101 | ESI | exact |
| Both `/GL`, but callee exported | 11 | 105 | ECX | different |
| Both `/GL`, but callee address escapes through an exported member-pointer getter | 11 | 105 | ECX | different |
| Fresh separate-source `/GL` rebuild | 16 | 101 | ESI | exact |

All five negative controls produce identical complete caller/callee bodies.
All three positive cases produce identical complete bodies, including address
operands. PE timestamps vary; selected function bytes do not.

## A second caller and an explicit LTCG root

Adding the `Destroy` caller at `0x0044C100` as a second direct C++ edge to
`Stop` is byte-exact when the manifest entry is `StopNoDelete` and `Destroy`
is the sole extra linker root. A control that roots every selected symbol
(including the callee) instead makes LINK 7.1 select the public ECX
convention, producing the 11-byte `StopNoDelete` and 105-byte callee
variants. The retail image has two callers that both preserve `ESI` and a
101-byte ESI-entry callee; the root set is therefore part of the reproducible
whole-program context.

Because `Destroy` is not reachable from the manifest entry, schema 2 now has
an optional `roots` array. The native link emits `/INCLUDE:` only for those
declared selected functions, retaining their complete contributions without
rooting the shared callee or changing its compiler convention. The worker
manifest declares `Destroy` as the sole extra root. Both caller-to-callee
edges remain ordinary C++ calls and are validated as direct unmodified REL32
targets.

The resulting three-function batch is reproducible with separate `/GL`
objects and one native `/LTCG` link. Measured body hashes are:

```text
0044C100 (36)  7aacd3b8f9e2b1ca7407614222181a02935ed64b41d28994d50206f19d84f255
0044C130 (16)  905781906110b560dfa5e0c6d79302f154b35eb833e56d982786c5dbb5b25c74
0044C150 (101) cfb40c11e58c6679c6865c790c8bf2a2f54b69a441729bcc0b4a1d3780df9
```

Other focused probes stayed out of the production inputs. At `0x004200D0`,
the ordinary C++ caller kept the exact callee but emitted `xor`/register-zero
stores instead of retail's two immediate absolute stores; size optimization
switched the stores but changed the remaining arithmetic. At `0x00420D90`,
the C++ virtual-dispatch model matched 32 of 33 bytes and tail-jumped where
retail retains an unreachable trailing `ret`; disabling frame-pointer
omission changed the prologue. These are source/optimization-layout clues,
not accepted recoveries.

With ordinary compilation, `StopNoDelete` stores the base vtable through ECX
and tail-jumps to `Stop`, which saves ESI and copies ECX into it. With both
functions in LTCG, the caller itself supplies ESI:

```asm
0044C130  push esi
0044C131  mov  esi, ecx
0044C133  mov  dword ptr [ecx], 004703E4h
0044C139  call 0044C150h
0044C13E  pop  esi
0044C13F  ret

0044C150  mov  eax, dword ptr [esi+4]
0044C153  push ebp
```

The callee's decorated symbol still says it is an ordinary member function.
That spelling does **not** describe its selected ESI convention. An external
C++ caller using that declaration alone emits the wrong call site. This is
why making a callee readable did not unblock the old per-region workflow.

Microsoft's contemporary [2002 LTCG explanation](https://learn.microsoft.com/en-us/archive/msdn-magazine/2002/may/under-the-hood-link-time-code-generation)
describes the backend receiving IL from multiple objects and requiring
visibility of all calls before changing a convention. The experiment above
verifies this behavior on the actual 7.1 toolkit, including the effects of
native callers, exports, and escaping function addresses. It does not infer
retail's original translation-unit organization.

## Smallest production change

The existing `tools/matching/ltcg_cluster.py` supports both schema-1
synthetic-context clusters and schema-2 real-entry batches. Schema 1 now also
accepts explicit roots when a context must preserve an independently reachable
public ABI. The worked manifest is
[`platform_worker_shutdown.json`](../msvc/layout/ltcg/platform_worker_shutdown.json).

1. `source` and `additional_sources` name all maintained inputs in the batch.
   Each is compiled separately with the existing retail flags plus `/GL`.
   Optional `roots` retain selected functions that are not reachable from the
   schema-1 context or schema-2 `entry`.
2. `entry` names a selected real function. In this example it preserves the
   public ECX entry of `PlatformWorker::StopNoDelete`. No `driver` or synthetic
   `context` is permitted in schema 2.
3. `functions` assigns complete compiler contributions to their source,
   retail address, and extent. `calls` declares the actual internal call sites
   and both selected endpoints; neither endpoint can be an external binding.
4. Native LINK places the functions at retail addresses using the existing
   zero-filled layout sections and absolute data/import bindings. The worker
   cluster has no external game-code dependencies: its outgoing calls are
   the standard Win32 wait, sleep, and close-handle imports.
5. The validator checks each function's MAP origin against its declared source,
   complete contribution extent, native PE address, and direct call target.
   Both bodies are exported together into the existing fixed-address outer
   link. No instruction or address operand is rewritten.

The normal build and `probe.py` already select all regions owned by a cluster.
Requesting either member therefore verifies both. Existing assembly callers
continue to resolve their legacy aliases to the same addresses; the final
whole-image hash proves those edges and the rest of the image are unchanged.

The compiler inputs contain no retail code bytes. Layout gaps are zero arrays,
including the gap over `0x0044C140`; that gap is never selected into the outer
image. Only the complete C++ caller and callee contributions count as recovery.

The export control also exposed native LINK's implicit `.edata`-to-`.rdata`
merge. MAP validation now derives that mapping from the PE export directory
and rejects mismatched addresses or extents. It does not assume section names
or section ordinals are interchangeable.

## Reproduce and inspect

Requirements are the toolkit and build tools listed in the root README.
The normal build needs no retail EXE. The experiment uses either a prior exact
build or a supplied retail EXE only for comparison after compilation.

```sh
make
make ltcg-proof
# Alternatively:
make ltcg-proof LTCG_ARGS='--oracle /path/to/th10.exe --toolkit /path/to/toolkit'

python3 matching2/tools/matching/probe.py \
  --source src/platform/platform_stop_worker_no_delete_0044c130.cpp
python3 matching2/tools/matching/probe.py \
  --source src/platform/platform_stop_worker_0044c150.cpp
python3 matching2/tools/matching/probe.py \
  --source src/platform/platform_destroy_worker_0044c100.cpp
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_0043c460_0043c460.cpp
python3 -m unittest matching2.tools.matching.test_ltcg_cluster
```

`make ltcg-proof` prints the fresh `matching2/build/ltcg-experiment/run-*/experiment.json`
path. It fails if any positive case differs, any negative case matches, the
negative bodies differ from ordinary compilation, or fresh positive bodies
are not reproducible. The report records source/toolchain hashes, exact
commands, function bytes and hashes, extents, and differences. Each case keeps
its native PE, MAP, logs, and `disassembly.txt`. The production cases also keep
the normal provenance report and validated COFF bodies.

Measured SHA-256 values:

```text
0044C130 (16)  905781906110b560dfa5e0c6d79302f154b35eb833e56d982786c5dbb5b25c74
0044C150 (101) cfb40c11e58c6679c6865c790c8bf2a2f54b69a441729bcc8ac0b4a1d3780df9
.text         c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998
whole EXE     2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040
```

Recovery accounting after the worker, joystick, and FrameTimer/cursor
promotions is 436 regions / 22,788 bytes of ordinary C++; assembly is 2,149
regions / 366,194 bytes.

## Joystick probe caller recovered through the logger cluster

The blocked 105-byte probe at `0x0044A0C0` was a direct test of the logger's
private ABI. Its readable implementation initializes a 52-byte
`JOYINFOEX`-compatible record, calls the two WinMM slots at `0x00466280`,
logs `0x00470580` through the singleton at `0x00474F70` when both devices
answer, and otherwise calls `joyGetDevCaps` at `0x0046627C`.

As a standalone translation unit the candidate matched the complete control
flow and extent, but differed at the logger call: retail loads the receiver
with `mov ecx, 00474F70h` and pops only the format argument, whereas the
ordinary member-call spelling pushed the receiver and used the wrong cleanup.
This is the same caller/callee convention that cannot be represented by the
source declaration alone.

The existing schema-1 native-LTCG layout
`d3d_text_log_append_0044b810.json` now compiles the probe separately with
`/GL` and roots it from the synthetic context alongside the exact
`TextLog_0044B810::Append` implementation. Ordered code sections place the
probe at `0x0044A0C0`, the logger at `0x0044B810`, and the context after both.
The cluster report records zero instruction-byte changes for both complete
contributions:

```text
0044A0C0 (105)  35af7bf413eea413af24bdcc336b1857d7a2cb28115e4615780b9452f5dbade5
0044B810 (201)  e656c1d4e04a4fe1113db4f817c541683da7b711b7a93fbe82fb20b8fdf2cbbb
```

The focused report is retained at
`matching2/build/probe_joystick_cluster3/clusters/d3d_text_log_append_0044b810/report.json`;
`make verify` also passes with the unchanged 487,936-byte executable. The
promotion is documented in
[`joystick_probe_text_log_cluster_0044a0c0.md`](recovery_notes/joystick_probe_text_log_cluster_0044a0c0.md).

## FrameTimer/cursor callers recovered through the timer cluster

The blocked 93-byte animation-cursor callback at `0x0043BD40` and the blocked
133-byte callback at `0x0043C230` were the next caller/callee cases. Standalone
C++ member functions matched their extents and control flow but emitted
`lea ecx,[esi+30h]` instead of retail's `add esi,30h` before calling
`FrameTimer::Tick`. The larger callback also reversed the two x87 operands for
the elapsed-scale multiply when the timer methods were visible to LTCG.

The existing schema-1 `frame_timer.json` now compiles both cursors as separate
`/GL` inputs with the three timer methods. Both cursors are explicit schema-1
`roots` entries (`/INCLUDE`), preserving their retail `ECX` entries while the
co-compiled timer calls receive `ESI`. Declaring each elapsed field volatile
preserves the exact `fld [elapsed]` / `fmul [data_00470BF8]` order under the
same native link. The cluster's five complete contributions are byte-exact:

```text
0043BD40 (93)  eb77f9ae62bf28287002b87c29b886a0d5c534a2084fdec0ccb4279dbbafb4ce
0043C230 (133) bd823ee212b505f3db6785f9fbc6bbdd7acf8bb50024f79f8dfb36fcc24d039f
00404ED0 (72)  5349f4fd279892f975448c3dd7bd04000cead49a6aef8ae46bd11ae580fcbde5
00428DD0 (20)  456bf129ca25bafdf3ff19604ea7e6067aca5da1737cd9fa8bf8dc8b075a8aee
0044BF40 (88)  c2c9591f6bcbfcf769892730b28e2da6d7d28af165ecde58ece3622068bcd4fd
```

The focused report is retained at
`matching2/build/probe_43bd40_cluster_rooted/clusters/frame_timer/report.json`.
The complete executable continues to pass the 487,936-byte retail hash gate.
The implementation and experiment are documented in
[`frame_timer_cursor_cluster_0043c230.md`](recovery_notes/frame_timer_cursor_cluster_0043c230.md).

## Third cursor recovered with a rebound compiler literal

The blocked 154-byte cursor at `0x0043C460` is the largest of the animation
callbacks. It converts its byte mode through the compiler's unsigned-to-float
idiom, scales it by `elapsed / length`, clamps the result, and otherwise
decrements its countdown, stores `0` through the scheduler record it shares
with the embedded `FrameTimer` at `+0x30`, and ticks that timer. As a
standalone translation unit it reproduced the complete flow and all but one
byte.

That byte is the displacement of `fadd dword ptr [00470B98h]`: the compiler's
own `__real@4f800000` (2^32) literal, which the unsigned conversion adds for a
negative input. Retail's literal pool put it at `0x00470B98`; the synthetic
cluster reproduces the pooled copy at the next free `.rdata` address instead.
Pooled literal placement depends on the whole translation-unit set, so the
layout cannot reach the retail address.

Schema 1 now accepts `constant_aliases`: a compiler literal may be bound
absolutely at its retail address instead of being placed. The bindings object
defines `__real@4f800000` at `0x00470B98`, the forced link discards the pooled
copy, and the alias wins the symbol resolution outright, so the emitted
displacement is retail's and no byte is patched. The tool passes
`/FORCE:MULTIPLE` only for a cluster that declares aliases, and then requires
the link log to report exactly one discarded duplicate per declared alias and
no other duplicate definition.

`frame_timer.json` now also compiles
`src/game/player_set_scheduler_value_00405410.cpp` and the new cursor source in
the same `/LTCG` scope, retiring the standalone scheduler cluster. The
scheduler keeps its retail `EAX` receiver, the cursors their `ECX` entry, and
the embedded timers their `ESI` receiver. All seven complete contributions are
byte-exact:

```text
00404ED0 (72)  5349f4fd279892f975448c3dd7bd04000cead49a6aef8ae46bd11ae580fcbde5
00405410 (57)  35c87a356741f4c628319bcf25c8e73cca3a554bff2ca59d1cb67d86fa0862e0
00428DD0 (20)  456bf129ca25bafdf3ff19604ea7e6067aca5da1737cd9fa8bf8dc8b075a8aee
0043BD40 (93)  eb77f9ae62bf28287002b87c29b886a0d5c534a2084fdec0ccb4279dbbafb4ce
0043C230 (133) bd823ee212b505f3db6785f9fbc6bbdd7acf8bb50024f79f8dfb36fcc24d039f
0043C460 (154) 163af6e09bccfa886237605c73d49764955d16b251b1731a1a834f914284131a
0044BF40 (88)  c2c9591f6bcbfcf769892730b28e2da6d7d28af165ecde58ece3622068bcd4fd
```

The focused report is retained at
`matching2/build/probe_43c460_cluster_alias/clusters/frame_timer/report.json`.
Its `constant_aliases` and `duplicate_definitions` fields record the rebound
literal and the tolerated pooled copy, and the complete executable continues to
pass the 487,936-byte retail hash gate. The implementation and experiment are
documented in
[`frame_timer_cursor_cluster_0043c460.md`](recovery_notes/frame_timer_cursor_cluster_0043c460.md).

## Consequence for further recovery

Choose a caller/callee dependency group, put the definitions on both sides of
each private ABI edge in the same native link, and validate the group together.
Keep external dependencies at conventions their declarations can actually
express. For further private callees, expand the group. Do not link old native
callers against the new IL callee merely to keep it live: that can pin the
callee's public convention, as the controls demonstrate.

This removes the requirement to recover those call sites independently and
disproves a requirement for one giant source file in this case. It does not
guarantee a matching register choice for every larger graph. Inlining,
register pressure, live values, address escapes, and other caller contexts
can still change generated code. The remaining compiler-layout and source-
recovery problems retain the same byte-exact acceptance gate.
