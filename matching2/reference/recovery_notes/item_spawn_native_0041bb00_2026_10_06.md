# Item spawn native recovery, 2026-10-06

Status: complete ordinary C++ candidate, **unselected and not exact**. Production
`src/game/item_spawn.cpp` and its 819-byte ownership remain unchanged.

The maintained candidate is `reference/semantic_candidates/item_spawn_0041bb00/`.
Its full native contribution is 819 bytes, including the 23-byte switch-table
material. After diagnostic address normalization, all but two bytes match the
oracle. Neither difference is accepted or masked:

| Retail address | Retail | Candidate |
| --- | --- | --- |
| 0x0041BC79 | `mov eax,[esp+18h]` | `mov ecx,[esp+18h]` |
| 0x0041BC7E | `mov [esi+2FCh],eax` | `mov [esi+2FCh],ecx` |

The differing byte offsets are `0x17A` and `0x17F`. They copy the identifier
following the kind-10 script-start call. Both switch tables have literal full
byte equality after address normalization. The generic diagnostic reports four
instruction groups: the two above and two table-reference correspondence
entries with identical printed instructions. The receipt separately records
literal comparison of the entire 819 bytes, including the tables; no difference
is suppressed to create an exact claim.

Full normalized body SHA-256:
`1ba0bada9dffd3ce25cb561034d153ccf279cb6415e90425d8b7e3aabd4f1263`.

## Reproduction and preserved source

From the repository root:

```sh
python matching2/reference/semantic_candidates/item_spawn_0041bb00/measure.py genuine_saved_candidate
```

Current outputs go to `build/experiments/item_spawn_flow_2026_10_06/genuine_saved_candidate/`.
The compiler builds the ordinary sources before the runner opens the oracle.
It links two bases only for diagnostic address normalization. The native PE,
MAP, commands, code-only disassemblies, complete native body, complete retail
body, and full comparison are retained separately. `receipt.json` hashes every
local source, header, layout, and runner. The candidate contains no inline asm,
naked declarations, emitted opcodes, code patches, or reference-code build use.
A raw fixed-address whole-contribution proof is still required before promotion.

The manager-EAX, position-ECX, four-stack-argument/RET16 contract is now
derived by the genuine complete line callers and retained public polar
methods, without a synthetic caller or entry. The earlier measurements used
a compiler-only context, which is archived as historical evidence.
The allocator retains the full 150-slot normal search, clamp, timer seed/reset,
kind remapping, animation retirement/configuration, identifier writes, special
2048-slot ring, signed remainder branches, and count/cursor updates.

## What improved the result

The old source result reproduces at 819 bytes with 28 unequal overlapping bytes:
one resource-bank load occupies a different place across the kind-11 branch.
Removing its existing timer barriers produces 85 unequal bytes and is rejected.

A nontrivial `ItemBankSnapshot` value moves that load to the original position
without declaring the global pointer volatile. It is a compiler/source
hypothesis, not a recovered original class declaration. The first resulting
model has four unequal bytes from scratch-register choices. Using the genuine
free script-start interface instead of the old configured-entity member model
reduces this to the two-byte identifier-copy residual. A direct first resource
argument gives the same result and is the simpler saved spelling.

Items now contain an actual `Entity` animation object followed by a `Vector3`
position. The normal and special position assignments operate on those real
objects. Both complete line callers pass a `Vector3` base pointer; their point
constructors preserve the original layout. Their polar step contains the actual
polar receiver rather than viewing an unrelated temporary as that receiver.
The bounded caller writes three named animation-position members instead of
indexing past the first float subobject. Static checks retain the 0x3F0 item
stride, +0x3AC position, +0x3DC state, both pool starts and cursor offset.
These representation corrections preserve the strongest native result.

The complete script loader returns the observed manager pointer/null result.
Its 203 bytes remain exact after diagnostic normalization. Both complete line
callers are also exact in this graph (609 and 623 bytes). Other helpers remain
complete but **not exact**: script-start 204 versus actual 202, registration
114 versus 118, positioned creation 111 versus 118, and allocation 165 versus
161. The ordinary cos/sin polar helpers emit 30-byte FCOS/FSIN bodies; they are
compiler context only and do not recover the retail FSINCOS helpers. Inherited
raw helper views are not globally certified as portable C++ by this attempt.

## Compiler trace and rejected controls

A read-only winedbg/GDB trace replays the native link against c2.dll. It is saved
under `build/experiments/item_spawn_flow_2026_10_06/trace/`; the traced input is
the no-barrier diagnostic variant. Its resource-bank load is already after the
branch at the first `FgDoLateFlowOpts` dump and remains there through
`FgCodeMotion` and `MscClean`. Thus the recorded misplaced load is not created
by those late passes. Debugger breakpoints observe the compiler without forcing
an allocation choice or changing its register values.

The initial 21 full native trials in `rejected_variants.json` show that volatile bank
snapshots also reach four unequal bytes, but the saved model uses ordinary
reads. Resource constructors and references retain four; a resource copy
constructor regresses to 451. The corrected free script-start interface gives
two. Exposing the full one-input initializer makes it exact in its own 273-byte
body, but changes script-start's receiver and grows the allocator to 823 bytes;
that context is rejected. Long, unsigned, and trivial value-type identifier
parameters, explicit shared exits, and a direct first resource argument retain
the same two-byte residual. Returning the observed result from the full loader
also leaves those two bytes unchanged.

The following audits trace the first kind-10 identifier copy's physical-register
choice and its genuine script-start preservation context. Do not accept the
residual as an equivalence or patch the two register encodings. Production
ordinary C++ coverage remains 197229 / 321483 bytes (61.3%); the full goal stays
active and incomplete.


## Temporary-register audit and source cleanup

The fresh `register_audit` build reproduces all 819 bytes of the retained native
contribution and the two literal oracle differences. Read-only winedbg/GDB
traces are under `build/experiments/item_spawn_register_2026_10_06/`. They replay
the compiler link command and compare the entire traced native function with
an uninstrumented build; all 819 native bytes are equal. The saved evidence
hashes cl.exe, link.exe and c2.dll and records the relevant compiler addresses,
temporary nodes and scan results. No compiler allocation choice or register
value was forced; no retail code or comparison allowance was modified.

The first identifier load is temporary `0x189`, instruction node `0x03620B10`
in this trace. `RegAssign` chooses physical register 2 (ECX). The second is
`0x188`, node `0x035FB258`, and receives physical register 1 (EAX). The stores
already use these registers at `Riscify` entry and retain them at its exit.
Thus later scratch-register splitting and instruction encoding do not create
the residual.

For the first copy, the expression-temporary occupancy entry for EAX is zero,
and its per-register interference bitmap does not contain temporary `0x189`.
The candidate scan nevertheless starts with register 2 at table cursor
`0x108AB744` and immediately accepts it. For the second, the scan starts with
register 1 at `0x108AB740` and immediately accepts it. The available EAX is not
rejected by a conflict; it is never the first candidate for the earlier copy.
The source lever must therefore affect this temporary allocation history or
representation while preserving the entire function, rather than adding
register liveness or changing the later `GetReg` rotation.

All five additional permutations of the genuine script-start parameters
reproduce the same two-byte residual. Preserving the helper's observed manager
pointer/null return also leaves it unchanged. Four-byte identifier memcpy
spellings, in the first arm or both arms, likewise retain the same native body.
These results extend `rejected_variants.json`; no model is promoted.

Two source corrections are retained because their combined rebuild preserves
the identical full native body. The kind-3 animation call now receives the
address of a real local `void* retired_handle`, replacing the cast of the float
speed argument to `void**`. Both block-local and function-local declarations
produce the same machine code: the compiler naturally reuses the dead speed
argument's stack home. The registrar now copies its four-byte output into its
declared pointer storage with memcpy rather than writing through an int pointer
view of that pointer object. Other inherited raw helper layouts are still not
globally certified; this is a scoped correction, not a portability claim for
the entire graph.

The maintained-source `post_register_audit` rebuild confirms 819 bytes,
identical full normalized SHA-256
`1ba0bada9dffd3ce25cb561034d153ccf279cb6415e90425d8b7e3aabd4f1263`,
matching table bytes, and the same two remaining register-encoding differences.
Updated source hashes verify against every file named by the receipt.
Production source, region ownership, masks and build tools are unchanged.

## Cursor reset audit and the embedded timer

The item now embeds the existing five-word `FrameTimer` at +0x3C8 instead of
duplicating its five scalar fields. A static offset check accompanies the
existing 0x3F0 size check. Resetting its named fields preserves every byte of
the full 819-byte native contribution. Calling `FrameTimer::Set(0)` instead
changes store order and leaves 28 unequal bytes, so that spelling is rejected.
The maintained `timer_recovery` rebuild still has only offsets 0x17A and 0x17F
unequal and retains both exact switch tables and all three exact helper results.

Static compiler analysis finds a cursor reset at 0x1079BDF3, storing table start
0x108AB740 into `NextIntPos` at 0x108A9D0C. The other reset, 0x107E1763, is gated
by the compiler flag at 0x108AB138 and IR opcode 0x2D3. The live trace observes
one function-start reset for Spawn, flag zero throughout, and no marker resets.
Thus this function does not inherit the preceding function's cursor position;
the relevant allocation history is within Spawn. Interprocedural context can
still affect its IR, so this does not rule out all effects of compiler context.

The reusable read-only debugger runner is
`reference/compiler_traces/regalloc/trace_temporary_cursor.py`. It checks the
specific c2.dll hash, redirects replay outputs, and records cursor updates and
temporary choices. Reproduce after the maintained candidate build with:

```sh
python matching2/reference/compiler_traces/regalloc/trace_temporary_cursor.py \
  matching2/build/experiments/item_spawn_flow_2026_10_06/genuine_saved_candidate/commands.json \
  matching2/build/experiments/item_spawn_cursor_2026_10_06/maintained_trace
```

The full replayed 819-byte native body is identical to the untraced build.
`register_assignment_evidence.json` records current source and trace hashes.
Debugger breakpoints observe the compiler; they do not force an allocation
result, change its data/register values, or modify an output instruction.

The 29 additional full trials bring the recorded total to 61. Fastcall, inline
identifier setters, memcpy position copies, first-arm bank snapshots, converted
resource handles, entity references, and volatile input hypotheses retain the
two-byte residual. Cdecl grows the root to 823 bytes; named component copies,
some switch/conditional layouts, resource references, and aggregate resource copies
regress. Aggregate resource parameters reproduce the first identifier register
but change the later resource load and identifier register (four unequal bytes).
No qualification hypothesis is retained. Only the actual embedded timer cleanup
is retained, and the candidate remains unselected. A next source
attempt must explain the difference between aggregate and pointer resource
lowering without accepting either register residual or introducing dummy code.


## Genuine native graph replaces the synthetic entry

The current maintained graph removes `PublishPolarCompilerContext` entirely.
Its former source, layout, runner, receipt and all-segment caller are retained
under `evidence/legacy_synthetic_context/` as historical evidence, excluded from
compilation. `runtime_graph.cpp` includes complete ordinary allocator,
animation and polar definitions; `all.cpp` is the other complete line caller.
The runner links a valid `/DLL /NOENTRY` native module and uses `/INCLUDE` for
the actual public all-segment, bounded-segment and two polar methods. There
is no new entry routine, shortened caller, method-address publisher or exported
proxy. Retaining real methods directly supplies their declared public ABI.
Spawn itself is not a public root: the two real line callers earn its private
manager-EAX/position-ECX/four-stack-word/RET16 convention.

Fresh Ghidra xrefs to 41BB00 confirm both line callers at 41E445 and 41F5FF,
plus eleven other incoming calls. The live instance remains the opened
`th10.exe` in project `th10`. The full 41BA50 conversion-sweep decompilation is
retained too; that sweep is not substituted for either line caller in this
native graph. The xrefs and decompilation are in `evidence/`.

The all-segment position output now uses `Vector3* out=&object->position` and
its named `x`, `z`, `y` members. This corrects indexing beyond the individual
`position.x` float subobject while preserving the original store order and
complete 609-byte contribution. Directly naming each field without retaining
the vector cursor gives the same extent but six diagnostic instruction groups;
the typed cursor preserves the full body. The 623-byte bounded caller and
203-byte script loader also remain completely exact after diagnostic address
normalization.

The current full allocator is still **819 bytes with exactly the same two
literal diagnostic differences**, offsets 17A/17F. Its complete normalized
SHA-256 and both 23-byte switch tables are unchanged. There is no promotion
or accepted register difference. Other complete contextual helpers retain
their earlier non-exact results; notably the MSVC polar methods still emit
FCOS/FSIN. Production's separate GCC C++ polar recoveries already match the
FSINCOS leaves, but these contextual methods are not new leaf recoveries.
The inherited private Entity_Init boundary and other raw helper views are not
newly certified as portable C++ by this graph cleanup.

Six additional measured controls bring the ledger to **67**. Retaining Spawn
as a public root changes its ABI to manager ECX / five stack words / RET20,
with a non-exact 815-byte body. Making the polar setters opaque imported
boundaries retains that public-root ABI and gives 811 bytes. Retaining only
the actual line callers restores Spawn's original private ABI and full 819
bytes, but leaves 76 literal differences. Retaining the actual public polar
methods closes those graph differences, leaving the old two-byte residual.
The typed vector output preserves both callers. A genuinely opaque `void*`
script-resource formal also retains the two-byte residual and is not kept.
The initial only-line-caller diagnostic incorrectly assumed no switch tables;
inspection confirmed all 23 table bytes remain, and the comparison was rerun
with the corrected code/table split. No built instruction changed.

A fresh read-only compiler replay uses the current genuine graph's commands,
not the deleted synthetic entry's build inputs. All **3,072 raw native .text
bytes** equal the uninstrumented current build, including all ten complete
function contributions, tables and compiler padding. Their SHA-256 is
`526605813f01140d2c57d17cc7f59c008515bbc895128bc3ddb635df567f20d2`.
The trace completes with 72 events, one function cursor reset and no marker
resets. Its two identifier temporaries are now 1A9 and 1A8, selected as ECX
and EAX respectively, with cursors 108AB744 and 108AB740. Source changes affect
IR numbering; they do not change the measured native body. The trace observes
allocation choices without forcing them or writing compiler data/registers.
`evidence/genuine_graph_register_trace.json` and the retained raw event log
record this fresh evidence and current source/artifact hashes.

This rules out dependence on the fabricated runtime request as the reason for
the first identifier-copy residual. The next byte-level investigation remains
the aggregate-versus-pointer script-resource argument and its genuine
expression-temporary allocation history. That candidate follow-up changed no
production selection, source, cluster, matching tool or comparison allowance.

## Subsequent production caller cleanup

The complete raw fixed-layout proof is now available for both line sweeps.
Production uses the actual dependency graph, typed position/velocity objects
and the complete real ItemPolarVelocity method as its native link entry.
Both selected caller bodies remain raw exact, and both production build modes
pass. The allocator remains unselected with its two-byte residual. The
[production graph note](item_line_genuine_graph_2026_10_06.md) records the
selected body hashes, full executable equality and current cluster audit.
