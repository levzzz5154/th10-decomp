# Worker suspended start at `0x0044C200`

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27. Integrated as ordinary C++ in the existing worker cluster.

The native MSVC 13.10 `/LTCG` scratch cluster replaces 0x0044C200 (56 bytes)
with `PlatformWorker::StartSuspended(void*, PlatformWorkerEntry)`, readable C++
without inline assembly. It first stops the previous thread, saves the callback,
sets the running/stop-request state, then calls `_beginthreadex` with initialization
flag 4 (`CREATE_SUSPENDED`). Receiver EAX, callback EDI, context at stack +4,
and RET 4 are chosen by the compiler when both Start variants and Stop are visible
in the same whole-program link.

Live Ghidra MCP evidence is in `ghidra_disassembly.json` and
`ghidra_decompile.txt`. This region was not initially defined as a Ghidra function;
the bounded 56-byte function was created at 0x0044C200, and decompilation confirms
the fields and CRT arguments. Ghidra reports no incoming references.

The registered `layout/ltcg/worker_start_0044c1c0.json` now selects this fifth
function, with its context moved to `0x0044C240` (88 bytes). The added call in
the context preserves the existing register conventions and all four prior
function contributions. `PlatformWorker::StartSuspended` is declared in the
shared worker header, and its source owns the original 56-byte region.

The maintained-source probe in
`matching2/build/experiments/worker_suspended/maintained.json` reports all five
functions EXACT (36/16/101/56/56 bytes). The baseline whole-image build before
integration passed across all 487,936 bytes. A whole-image rebuild of the
integrated changes remains required before claiming that gate.
