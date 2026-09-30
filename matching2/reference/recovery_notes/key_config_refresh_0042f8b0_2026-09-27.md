# Key configuration refresh 0x0042F8B0: EXACT 2452/2452

> Integration status (2026-09-27): the exact routine(s) described here are now integrated in the maintained project. The combined 487,936-byte executable matches retail byte for byte. See [the fourth checkpoint](native_recoveries_2026-09-27_fourth.md) for current proof and remaining work. Scratch-only and promotion instructions below describe the original recovery handoff. Unmatched candidates remain in scratch.

2026-09-27. Complete typed C++ reconstruction of retail
`0x0042F8B0..0x00430243`, without inline assembly. All work is scratch-only;
maintained files have not been modified by this agent.

## Authoritative behavior

Fresh Ghidra MCP decompilation, the complete disassembly and all 2452 raw bytes
are retained in `/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/ghidra_evidence.json`. The retained
`reference/semantic_candidates/key_config.cpp` only models 0x00430250; it does
not contain a refresh implementation. This full refresh model was derived
from current Ghidra evidence and the maintained byte listing.

The object arrives in EAX; it has no stack inputs and ends with a plain RET or
the final Configure tail call. Its parent handle is at +0x2CC and five signed
short bindings occupy +0x59CC..+0x59D4. Every digit first looks the parent up via
Find, clears its parent handle if lookup fails, then traverses the parent's
EMBEDDED link at +0x10 (object pointer +0, next +4). A matching child's short tag
at +0x38A yields its first dword handle; Find resolves that handle a second time.
A resolved digit is configured using its resource at +0x308 and the corresponding
binding's signed division or remainder by 10, plus 0x33.

All twenty visits are explicit:
`67,68,77,78,69,70,79,80,71,72,81,82, 73,74,83,84,75,76,85,86`.
Each binding has tens/ones at its base tags and again at base+10 tags. The full
source preserves the repeated parent/child lookups and the observed embedded
link address formation after failed parent lookup, without introducing a null
guard. Compile-time checks verify parent/binding, child-link, resource and tag
offsets and the 12-byte child-link size.

## Compiler-visible callees and the ABI lever

The driver contains the genuine full maintained Find and Configure behavioral
models, with cluster-local types; they are compiled at their retail addresses
as ABI anchors and never exported as recovered code.

- Find at 0x004491C0, 73 bytes: noinline __fastcall member with unused receiver,
  context EDX, four-byte ScriptId aggregate on stack, RET4. Its primary and
  secondary bucket lookup body is retained in full.
- Configure at 0x0043E5A0, 356 bytes: the complete matrix/resource configuration
  body is retained, but expressed as an ordinary free __stdcall function
  `(resource, object, index)`. This yields resource ECX/object EAX/index EDX and
  makes the caller assign state EAX→ESI, manager EDI, zero EBX and digit ECX.
- A synthetic array caller at 0x00449210, 38 bytes, retains the refresh body and
  establishes its private entry. It and all zero-filled gaps are unselected.

Using the genuine Configure body as a MEMBER produced 2439 bytes and different
register assignments. Free/membership declaration of refresh and five different
caller contexts did not fix that. The explicit Configure parameter interface
was the decisive lever: the selected full body became 2452 bytes and matched
all retail instructions, loop alignment, cold found-child paths, delayed EBP
saves, signed arithmetic, and final tail call.

The inline child lookup helpers require __forceinline; plain inline let the
compiler outline an 82-byte helper and shrink the selected refresh to 980 bytes.
The final source remains one complete 2452-byte compiler contribution.

Configure's compiler-pooled float literal remains in the anchor's native .rdata;
its address is not referenced by selected refresh bytes. No constant alias or
reference bytes are needed. The only absolute symbols are `_data_00491c10`
(0x00491C10) and `__fltused` (0). No Queue model is required by this function;
Queue is only called by the separate reassignment routine 0x00430250.

## Final exact proof

```sh
python3 matching2/tools/matching/probe.py \
  --source src/game/fun_0042f8b0_0042f8b0.cpp \
  --project /home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/msvc \
  --output /home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/probe_final --json
```

`/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/probe_final.json`: exact true, failures [], different_bytes 0,
relocations []. Native report:
`/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/probe_final/clusters/key_config_refresh_0042f8b0/report.json`.
Normalization changes zero instruction bytes and zero address operands,
masked_bytes 0, reference_bytes_used_for_build false. The full 2452-byte selected
compiler contribution is accepted by the native loader.

Native/retail SHA-256: `1c8190ce6d9917294072ae0c8f07ae588851c615e2130d2b9f4ffb51d1eb25c3`.

## Promotion artifacts

Copy these four files from scratch to matching maintained paths:

- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/msvc/src/game/fun_0042f8b0_0042f8b0.cpp`
- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/msvc/include/th10/game/key_config_refresh_0042f8b0.hpp`
- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/msvc/layout/ltcg/key_config_refresh_0042f8b0.json`
- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/msvc/layout/ltcg/key_config_refresh_0042f8b0_context.cpp`

Then register atomically and run the maintained normal probe:

```sh
python3 matching2/tools/waves/register_cluster.py \
  --project matching2/msvc \
  --layout layout/ltcg/key_config_refresh_0042f8b0.json --apply
```

Selected symbol `_RefreshKeyConfigLabels_0042f8b0@4` has the source-level stdcall
spelling, with private EAX/noargs/plainRET after native LTCG. Existing maintained
`regions.json.symbols['_asm_FUN_0042f8b0_0042f8b0'] = '0x0042F8B0'` supplies the
old callers' address alias; preserve it. No new aliases are required. The
Configure/Find anchors are private compiled context, so their local symbols
are never exported into the maintained image.

Independent failed member-context experiments remain under
`/home/levzzz/Games/th10Decomp/matching2/build/experiments/key_config_refresh_0042f8b0_2026_09_27/member_context_variant/` for future compiler-recovery comparisons.
