# Resumed native decompilation checkpoint

Full access resolved Wine's Unix socket restriction. The goal is active,
and native MSVC compilation and Ghidra MCP now work. The build framework,
pinned toolchain, compiler profiles, and comparison gates remain unchanged.

The complete build at `matching2/build/resumed_wave4_msvc_2026_10_01` compiled
1,892 maintained sources with zero failures. All **487,936 executable bytes**
literally match retail, and every maintained source hash is current. SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

Since the verified pre-resumption baseline, **17 assembly regions / 2,260
bytes** moved to fully assembly-free C++. One additional **10-byte exception
handler** was correctly reattributed from library ownership to native C++.
The first eleven recoveries are documented in
`permissions_restored_native_wave_2026-10-01.md`. Subsequent additions are:

| Address | Complete native region | Bytes |
| --- | --- | ---: |
| `00405840` | Player scheduler callback | 10 |
| `0044D440` | Sound-stream start | 145 |
| `0044DAD0` | Sound-stream restart | 213 |
| `00438880` | D3D resource manager destructor | 103 |
| `00465350` | Generated primary unwind cleanup | 8 |
| `00465358` | Generated secondary unwind cleanup | 11 |
| `00465363` | Generated manager exception handler; attribution corrected | 10 |

| Ownership | Regions | Bytes |
| --- | ---: | ---: |
| Semantic C++ | 1,886 | 102,731 |
| Fully assembly-free C++ | 1,881 | 98,280 |
| Assembly | 415 | 220,197 |
| Toolkit runtime library | 322 | 66,470 |
| Embedded .text data | 7 | 7,779 |
| Padding | 1,770 | 15,495 |

Assembly-free C++ is a subset of semantic C++. Five semantic functions still
contain six x87 assembly blocks covering 4,451 bytes. The complete goal
remains unfinished.

All new owned regions have complete native compiler extents and literal
original bodies, with zero instruction changes, operand changes, or masked
bytes. Retail code was not used to construct native output. Already-semantic
helpers and unselected compiler contexts earn no additional credit.

The player callback uses the genuine primary and secondary scheduler
callbacks. Its private Update model has a complete 218-byte native body,
which differs from the original 223-byte body and remains unselected. Other
nonmatching private helper contexts are explicitly recorded in its audit.
The maintained Update owner remains assembly. Start and Restart use genuine
complete command callers as unselected contexts; their owned bodies and
their complete restore, fill, and cursor anchors match literally.

The renderer destructor uses the genuine scalar deleting destructor as its
complete unselected caller. Modeling the list's actual pending integer
fields retains the original register allocation. The complete generated
29-byte exception contribution and 44-byte metadata match original output.
The original manager's handler registration, handler FuncInfo operand,
unwind map, cleanup targets, and native generated symbol independently prove
that `00465363` belongs to this manager. Its earlier string-library attribution
was incorrect; the old record and symbol alias are preserved. Moving the
existing StopNoDelete owner between clusters also passes all eight complete
worker-start collateral owners. The existing scalar deleting destructor's
main source, owner, and cluster remain unchanged.

Player, Item, and Game constructor diagnostics earn zero credit: their
faithful ordinary factory callers generate additional exception suffixes
that fail the complete-contribution gate. Synthetic-caller and
exception-suppressing preliminary proofs are explicitly ineligible.
Nonmatching emitter, parser, pixel-fill, Update, and x87 diagnostics are
preserved separately. Ghidra's emitter remainder-condition comment was
corrected and saved without changing code or ownership.

Repeat the current whole-build provenance audit with:

```sh
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_resumed_eh_build.py
```

This checks the frozen manifest snapshot, every current source hash, complete
executable equality, all eighteen new native regions, compiler inputs and
includes, native PE/MAP/object/report hashes, old symbol bindings, unchanged
compiler profiles, and the original exception-handler attribution. Only the
specifically proven library correction is permitted. Subsequent integrations
require another fresh snapshot and build. The companion evidence JSON
preserves this checkpoint; earlier builds remain separate historical artifacts.
