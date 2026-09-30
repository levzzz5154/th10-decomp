# Complete replay-pool release at 0x0042AB20 — exact C++ recovery

Maintained integration is complete after independent review and exact normal probes. The sixth checkpoint matches all 487,936 retail executable bytes using all 3,964 current project inputs. Five existing Ghidra Function annotations were saved and read back. Proof: `matching2/build/experiments/native_recoveries_2026-09-28_sixth_verified.json` and `native_recoveries_2026-09-28_sixth_ghidra_verified.json`.

The complete **93-byte** retail body at **0x0042AB20..0x0042AB7C** is recovered as readable, inline-assembly-free C++. This work produced a standalone selected recovery and changed only the isolated scratch project. Maintained inputs were not edited.

Canonical normal proof: `matching2/build/experiments/replay_pool_full_caller_2026_09_28/release_selected_probe/probe01.json`. The standard `matching2/tools/matching/probe.py` native-LTCG gate passed on the first attempt, **93/93 bytes exact**, zero differing bytes. Native body and stable-oracle SHA-256 are both `84a48e66ece6617e49b9afd6239363056cb10f063279a5ccade7a4a9dcd6e82f`. Build normalization rewrites zero instructions and zero address operands, masks zero bytes, and uses no reference bytes to build code. A direct whole-body native PE comparison is retained as `independent_selected_comparison.json` in that directory.

The source-owner path is `src/game/linked_pool_release.cpp`. The ordinary source declaration is `extern "C" __declspec(noinline) void __stdcall ReplayPool_Clear_0042ab20(int stage, ReplayPoolLists_0042aa50* lists)`, symbol `_ReplayPool_Clear_0042ab20@8`, section `.text$40release`. The actual private entry uses **stage EAX**, **lists ECX**, and **plain RET**. Fresh Ghidra decompile/full disassembly are retained: the first instruction multiplies EAX by three; the next reads `[ECX+EAX*4+0x40]`, and the last is plain RET. The CRT `free` call retains its genuine public **cdecl**, one pointer stack argument, caller cleanup of four bytes, bound to `0x004524A1`.

The full authentic source is byte-identical to the genuine dependency model used by the complete snapshot caller experiment: source SHA-256 `c9bc70a6a9282a7e15e37cd762793090703fd4d05cdc5f575e2c538dd2ef4677`. That real-caller native image independently matched all 93 bytes as an unselected dependency; `full_model_dependency_comparison.json` records that evidence. The selected standalone proof is separate and includes no unmatched snapshot body.

The accurately typed header is `include/th10/game/replay_pool_append_0042aa50.hpp`, SHA-256 `61fd526869bd6b3be0f6564496d12e895b7881ad13a3a9026678827e8f3a7718`. Stage sentinel links start at list-owner `+0x3C`, each link is 12 bytes, and its next slot therefore matches `+0x40 + stage*12`. A complete pool is `0x6284` bytes, with its embedded link at `+0x6278`, successor at `+0x627C`, and predecessor at `+0x6280`. The header retains the complete authentic pool layout and constructor, and compile-time checks verify pool size, embedded link, cursor/record offsets, stage-array location and list-owner size. Its constructor is unused by the selected release cluster.

The recovered routine saves the next list node before processing the current pool. For nonnull pool pointers it updates successor/predecessor links, clears both links in the released pool, calls free, then follows the saved next node. It preserves null-pool handling and the absence of added stage checks. No abbreviated private helper, register surrogate, barrier, inline assembly or byte patch is used.

The new schema-1 layout is `layout/ltcg/replay_pool_release_0042ab20.json`, cluster name `replay_pool_release_0042ab20`. Its only selected function is the entire original 93-byte release. The compiler context is a complete **18-byte** ordinary stdcall forwarding caller at `0x0042AB90..0x0042ABA1`:

```cpp
int __stdcall ReplayPoolReleaseCompilerContext_0042ab20(int stage, ReplayPoolLists_0042aa50* lists) {
    ReplayPool_Clear_0042ab20(stage, lists);
    return 0;
}
```

It forwards both genuine arguments and establishes the observed private register convention. It is explicitly unselected compiler context, not recovered game code. There are no additional function anchors. The exact source/header/layout/context/manifest and successful normal/native reports are preserved under `release_selected_probe`; `release_handoff.json` provides all hashes and four explicit promotion files. The maintained probe and full image gate subsequently passed. The full thread goal remains active.
