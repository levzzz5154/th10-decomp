# Enemy script record initializer, 0x0040D830

> Integration status (2026-09-27): the exact routine(s) described here are now integrated in the maintained project. The combined 487,936-byte executable matches retail byte for byte. See [the fourth checkpoint](native_recoveries_2026-09-27_fourth.md) for current proof and remaining work. Scratch-only and promotion instructions below describe the original recovery handoff. Unmatched candidates remain in scratch.

The complete 673-byte function is EXACT in two independent normal native-LTCG
probes. The second probe includes the final source comments and final layout
description. Its selected-byte SHA-256 is
`9b85417ddb84333049b749fa71928c2efe8283ecf05e624d8e4f40430dd2c02d`.
The normal gate reports zero different bytes, zero masked bytes, zero changed
instruction bytes, and no reference bytes used for the build. No maintained
files were changed by this recovery.

## Promotion files

The authoritative project is `opaque_variant/msvc`. Copy these five paths
relative to that project, then register its single selected region with the
normal cluster registration tool:

- `src/game/fun_0040d830_0040d830.cpp`
- `include/th10/game/enemy_script_bind_0040d830.hpp`
- `layout/ltcg/enemy_script_bind_0040d830.json`
- `layout/ltcg/enemy_script_bind_0040d830_context.cpp`
- `layout/ltcg/enemy_script_bind_resolve_anchor.cpp`

`promotion_artifacts.json` records the final artifact hashes. Normal gate output
is retained in `opaque_variant/probe_final_01.json` and
`opaque_variant/probe_final_02.json`; the final native report is
`opaque_variant/probe_final_02/clusters/enemy_script_bind_0040d830/report.json`.
An independent worker probe is retained under
`clear_inline_variants/probe_scratch_flag_slots_alias`.

## Live evidence and semantics

Fresh Ghidra evidence from `th10.exe` is saved as
`ghidra_decompile_0040d830.json`, `ghidra_disassembly_0040d830.json`,
`ghidra_disassembly_0040cfb0.json`, and `ghidra_disassembly_0040cc70.json`.
The caller at 0x0040CFCE pushes the script name and supplies the allocated
record in ESI. The target returns that record in EAX and executes RET4.

The 0x2518-byte record embeds its interpreter instance at +0x8, active-instance
cursor at +0x4, script-table pointer at +0x102C, and own instance-chain node at
+0x1030. It sets the vtable to 0x0046D0C0, calls ClearAnims on the payload at
+0x103C, and clears the complete 0x14DC-byte payload. The instance is reset
and linked as the record's only interpreter instance. Three eleven-word
snapshots are cleared in C/B/A order; four bounds are initialized to 24.
The fifteen-float auxiliary block at +0x2408 is cleared, with its last two
floats initialized to 32. Three frame timers are reset at +0x1158, +0x2458,
and +0x246C, using the speed address 0x00476F78. The record takes the active
game's script table from the global at 0x00477704, resolves the supplied name,
sets its first instruction and time zero, clears position, and resets all eight
markers. Unidentified reset words retain offset-based names.

The old retained model incorrectly described the script resolver as a texture
lookup and the frame timers as scheduler chains. This source uses the
authoritative typed script table from the maintained resolver family instead.

## Compiler context and ABI

The selected function is expressed as legal fastcall C++ with an ignored
incoming ECX value, entity pointer, and one-word script-name aggregate. The
unselected array context keeps the entity live across repeated calls; native
LTCG colors it into ESI and preserves the script name on stack. The first
parameter preserves the input ECX solely across the call to ClearAnims.
ClearAnims has a legal ordinary fastcall declaration taking its owner in EDX;
the actual function at 0x0040CC70 ignores its ECX argument and returns its
owner. Its symbol is bound directly to 0x0040CC70. Making its entire body
compiler-visible changed the caller's EDX lifetime and emitted the wrong
register schedule, so it is opaque in the exact final cluster.

The full ordinary script-resolver body is compiler-visible as a genuine
136-byte unselected anchor at 0x00450470. It performs binary search using
intrinsic strcmp, and returns the script value plus 16 or zero. LTCG chooses
its native EAX receiver, single stack-name word, and RET4 without an illegal
ABI declaration. The final context is 60 bytes at 0x00450510. Anchors and
context are unselected and add zero recovered bytes.

## Source-shape findings

The initial full native model already emitted 673 bytes, with an exact
436-byte suffix beginning at 0x0040D91D. Four ordinary inline clear/memset
helper boundaries left its prefix unchanged. Ordering barriers emitted a
672-byte body and were rejected. The exact source uses no ordering barriers.

The inline instance Reset takes retained flags as a scalar argument, keeping
the flags in ECX. A typed local pointer to its unknown reset word gives the
retail store order. Typed pointer views also retain the placement of the
instance-name and identifier stores. Six separate typed word views for the
payload reset fields keep the first snapshot memset's EAX zeroing after those
stores. Finally, the adjacent scratch-word pointer gives the retail placement
of MOV EDX,EDI after the two scratch stores. Together these ordinary C++
expressions reproduce every byte of the original function without assembly,
naked functions, emitted bytes, instruction rewriting, masks, or shortened
extents.
