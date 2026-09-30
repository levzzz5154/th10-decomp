# Item spawn allocator 0041BB00: complete native C++ residual, 2026-09-28

Status: **unpromoted; not byte-exact**. Maintained `src/game/item_spawn.cpp`
remains the exact assembly body. This investigation changes no maintained input.
The authoritative target extent is **819 bytes**, including native switch-table
material after the final RET; the legacy semantic header's 896-byte claim is stale.

Fresh Ghidra MCP evidence was read from live `th10.exe` using
`/run/user/1000/ghidra-mcp/ghidra-2136235.sock`. The retained decompile, complete
function disassembly, xrefs and helper-work evidence are under
`matching2/build/experiments/item_spawn_0041bb00_2026_09_28/`.

The full ordinary C++ candidate uses a checked 0x3F0 item layout and the real
0x14 normal-pool start, 0x24EB4 special-pool start, 0x21CEB8 ring cursor and
0x21CEBC count offsets. It includes the 150-slot first-free allocation search,
normal-position copy and [-192,192] x clamp, velocity call, complete conditional
timer seeding and reset, fragment-dependent type remapping, retirement of old
kind-3 animation, kind/display-kind changes, script configuration, identifier
write, the 2048-slot kind-8 ring, all four signed density variant remainder
branches, occupied-slot handling, count increment and cursor advance. Every exit
returns zero. No behavioral branch was removed to reduce the contribution size.

The genuine complete helper models include the vector-constructor animation
configuration, allocation and positioned animation creation, script loading and
primary registration. The initializer's actual ignored-ECX/EDX-object fastcall
and the tick interpreter's one-stack-object/RET4 boundary are accurately
represented by opaque declarations. Earlier reused 207-byte loader context had
inconsistent opaque cdecl boundaries; the final candidate instead uses the
maintained complete 203-byte `LoadScript_0043e710` body with its correct contracts.
Its independently compared full body is **203/203 bytes exact** in this cluster.

The polar setter ABI context is a complete cos(angle)/sin(angle) C++ member body.
It emits **28 bytes of FCOS/FSIN**, is unselected, and is not claimed to recover
the maintained 30-byte FSINCOS setter or prove identical x87 rounding. It
preserves EDX in its actual native instructions but receives its destination in
EAX, while retail uses the public ECX receiver. Two bounded address-taking
compiler contexts did not retain the desired ECX boundary. All other unselected
helper extents and their residuals are explicitly recorded in the measurement.

Seven bounded models and a separate final native probe were compiled. Natural
changes tested free-function/member receiver forms, the allocation loop shape,
typed vector copies, source ordering barriers, scalar parameter order and a
separate mapped-kind local. The separate local reduced the complete contribution
to **827 bytes**, while the maintained region requires 819.

Final fresh NORMAL `probe.py` result is **NOT EXACT**, with the error
`function is not its entire declared compiler contribution`. The map places the
827-byte body at 0041BB00 and all unselected native bodies at their declared
addresses; the selector correctly refuses to truncate it to the maintained
819-byte ownership. Raw native diagnostic comparison, separate from the failed
normal extraction, reports **754 overlapping differences**, first at
**0041BB02**. Native SHA256:

`0db1e835bb6f02ae4b0e29deffd6856a29d9d02d7cf6173284130b1124481a92`

`measured_residual.json` records the complete native contribution, exact artifact
paths, input hashes, source snapshot, per-anchor comparisons and zero instruction
rewrites, address rewrites, comparison masks or reference-code build use. The
native PE was freshly compiled from C++; the oracle was read only afterward for
byte comparison. Sources, headers, contexts and helper bodies contain no inline
assembly, naked declarations or emitted opcodes.

The current candidate receives the manager in EDX and the position in EAX;
retail requires the manager in EAX and the position in ECX, with kind,
identifier, angle and speed on the stack and RET16. The zero is correctly held
in EBX in the final model, but kind/receiver homes, the peeled allocation loop
and helper call agreements remain different. The next concrete lever is to
compile the complete genuine **0041E260/0041F400 callers** with this full
allocator body, then resolve the genuine public-ECX polar setter boundary and
its visible preservation contract. Another empty helper or fabricated register
stub would not close this dependency.

Artifacts:

- `matching2/build/experiments/item_spawn_0041bb00_2026_09_28/msvc/src/game/item_spawn.cpp`
- `matching2/build/experiments/item_spawn_0041bb00_2026_09_28/msvc/layout/ltcg/item_spawn_0041bb00.json`
- `matching2/build/experiments/item_spawn_0041bb00_2026_09_28/probe_final_01.json`
- `matching2/build/experiments/item_spawn_0041bb00_2026_09_28/measured_residual.json`
- `matching2/build/experiments/item_spawn_0041bb00_2026_09_28/final_inputs/`
- `matching2/build/experiments/item_spawn_0041bb00_2026_09_28/helper_work/anchor_handoff.md`

The full readable, byte-matching, inline-assembly-free objective remains active.
