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

The existing `tools/matching/ltcg_cluster.py` now accepts schema 2 alongside
the unchanged schema-1 synthetic-context route. The worked manifest is
[`platform_worker_shutdown.json`](../msvc/layout/ltcg/platform_worker_shutdown.json).

1. `source` and `additional_sources` name all maintained inputs in the batch.
   Each is compiled separately with the existing retail flags plus `/GL`.
   Optional schema-2 `roots` retain selected functions that are not reachable
   from `entry`.
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

Recovery accounting after the worker and joystick promotions is 433 regions /
22,408 bytes of ordinary C++; assembly is 2,152 regions / 366,574 bytes.

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
