# Title worker starter at 0x0041FAC0

> Integration status (2026-09-27): the exact routine(s) described here are now integrated in the maintained project. The combined 487,936-byte executable matches retail byte for byte. See [the fourth checkpoint](native_recoveries_2026-09-27_fourth.md) for current proof and remaining work. Scratch-only and promotion instructions below describe the original recovery handoff. Unmatched candidates remain in scratch.

2026-09-27. `TitleWorkerOwner::StartWorker` matches all **140 bytes** of the
retail region through the normal native-LTCG probe. It is ordinary C++, without
inline assembly, naked functions, instruction rewriting, address-operand
rewriting, or masked comparisons. Final evidence is `probe_final.json`.

Live Ghidra instance 2136235 confirms that the owner arrives in EBX and the
function returns zero in EAX with a plain RET. Its only code caller is
0x0041FD21. The body creates callbacks for 0x0041FEB0 and 0x0041FEF0, clears
callback flag 0x2, stores the owner as both callback contexts, and registers
them at primary priority 3 and secondary priority 2. It saves the task pointers
at owner +8 and +0xC, stops the embedded worker at +0x10, and starts
`TitleWorkerThreadMain` at 0x0041F990 with the owner as its thread context.

The worker pointer local keeps ESI live across Stop and `_beginthreadex`,
matching the retained worker-subobject accesses. Scheduler registration uses
ESI for the callback, EDI for priority, and a stack scheduler argument. The
array-walking compiler context lets the whole-program pass select EBX for the
owner while the helper bodies use ESI and EDI. No C++ declaration assigns a
private register explicitly.

Only the starter is selected as recovered code. Its separate schema-1 cluster
uses three unselected genuine C++ ABI anchors: the 131-byte primary and
secondary scheduler registration bodies copied from the maintained timer
factory context, and the 101-byte recovered PlatformWorker::Stop body. All
three anchor emissions were also compared directly to the immutable oracle and
match exactly; `anchor_evidence.json` retains that verification. Their bytes
are not exported from this cluster, and the existing registered scheduler and
worker clusters keep ownership of those functions.

The first typed model already reproduced the 140-byte instruction shape and
register allocation. Four bytes differed because callback and thread entry
symbols used relative-code bindings despite being taken as function pointers.
Those address-of references require full executable addresses: the layout uses
absolute bindings (`kind: data`) for these three code-pointer symbols. Direct
calls retain relative-code bindings. This is normal linker input metadata;
no emitted instruction or address operand is rewritten.

The synthetic caller is 35 bytes at 0x0044C1C0. It and the zero layout gaps are
compiler context only, excluded from the recovered image. Source and layout
snapshots, compiler inputs, native PE/MAP, and all byte comparisons are recorded
by the production probe path.

## Integration

Copy from this experiment's `msvc/` tree into the same paths under maintained
`matching2/msvc/`:

- `src/game/recovery_start_worker_0041fac0.cpp`
- `layout/ltcg/title_worker_start_0041fac0.json`
- `layout/ltcg/title_worker_start_0041fac0_context.cpp`

Merge the single record in `proposal.json` by address, preserving its
`previous_record`, and add `layout/ltcg/title_worker_start_0041fac0.json` to
`ltcg_clusters`. No maintained header change is needed. The recovered symbol
is `?StartWorker@TitleWorkerOwner@@QAEHXZ`.

Reproduce:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/game/recovery_start_worker_0041fac0.cpp \
  --project matching2/build/experiments/title_worker_start_0041fac0_2026_09_27/msvc \
  --output matching2/build/experiments/title_worker_start_0041fac0_2026_09_27/reprobe --json
```

`ghidra_decompile.txt`, `ghidra_disassembly.txt`, and `disassembly.txt` retain
the live reference and final compiled body. Whole-executable validation remains
the parent's integration step. No maintained file was changed by this recovery.
