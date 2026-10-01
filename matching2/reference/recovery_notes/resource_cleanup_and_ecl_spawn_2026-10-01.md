# Resource cleanup and ECL child spawn

Two complete functions, totaling 488 bytes, now compile as readable C++ without inline assembly. The maintained full build matches all 487,936 bytes of the retail executable. Current recovery is 1,852 semantic regions / 97,493 bytes, with 446 assembly regions / 225,405 bytes remaining. Five semantic functions still contain inline x87 blocks; excluding those functions leaves 1,847 fully assembly-free semantic regions / 93,042 bytes. The full decompilation goal remains incomplete.

| Function | Address | Recovered bytes | Actual native convention |
| --- | --- | ---: | --- |
| `ResourceCleanup` | `0x00418EE0` | 346 | Manager on stack; RET 4 |
| `EclSpawnChild` | `0x004500D0` | 142 | Parent EDI; id and operand index on stack; status EAX; RET 8 |

## Resource-manager cleanup

`matching2/msvc/src/game/resource_manager_cleanup_00418ee0.cpp` removes the manager's two tasks under the scheduler lock, updating the lock-depth byte around each removal. It visits ten animation keys, searches both animation-manager lists, marks matching objects and their eligible children for removal, and clears each key. When the global mode equals two, it saves hints to the genuine `hint/hint_auto.txt` path. It then releases the blocks in the manager's eight primary and eight secondary bucket chains and clears the global published-manager pointer.

The new shared `th10/game/resource_cleanup.hpp` declares the task pair, both bucket arrays, and the ten keys as fields of the same manager. Compile-time checks cover the task-pair size, bucket stride, and offsets 0x1C, 0x7C, and 0xDC. The cleanup calls the manager member directly. Its native compiler driver includes the actual maintained bucket and scheduler sources, giving the optimizer the genuine complete callee bodies without duplicating their implementations in context files.

The bucket source accepts a section-name override so this compiler scope places its complete 79-byte body at the original 0x00419040 address. The scheduler source similarly exposes its complete 114-byte removal body for this scope; the other scheduler functions remain present in the regular build. Both bodies match all retail bytes in the new native PE and remain owned by their pre-existing semantic regions. Only the 346-byte cleanup adds recovered bytes. The selective scheduler inclusion also avoids redundant empty MAP section markers produced by unused functions; the verifier is unchanged.

The maintained source probe checks all 39 affected regions / 4,718 bytes, all exact. It covers the cleanup, bucket member, and the existing scheduler scopes affected by the shared source edits. Its two scheduler call sites target 0x00449F60, the hint-save call targets 0x0041A200, and the final bucket call targets 0x00419040. Allocation-release calls bind to the genuine 0x004524A1 entry. The previous assembly record and `_asm_FUN_00418ee0_00418ee0` alias remain preserved.

Fresh Ghidra independently confirms task offsets, critical-section depth updates, list search and flag propagation, ten-key traversal, hint path, and final cleanup. The earlier native scheduling concern over the depth decrement is resolved by the current complete helper scope; the accepted cleanup requires no compiler barrier.

## ECL child spawn

`matching2/msvc/src/script/ecl_child_pair.cpp` allocates a 0x1024-byte child state and a 12-byte intrusive-list node. It clears the child's stack cursor and frame base, records the supplied id and parent context, resets its time and instruction, and copies the active parent's script mask at offset 0x101C. It inserts the node at the owner's child-list anchor at offset 0x1030, updating the old head's back link, then calls the existing StartChild entry at 0x0044DF70 with the new state and original operand index.

The child overlay is POD: the unused constructor in the initial candidate was removed before the accepted production probe. Its extent and mask offset are checked at compile time, and the owner and list-node offsets come from the maintained ECL child header. The complete 142-byte body matches, including both allocation calls to 0x00452493, node-link writes, final call, and RET 8. The old `_asm_EclVm_SpawnChild_004500d0` alias and original region record remain bound to the original address.

Native LTCG sees the complete readable StartChild candidate together with the genuine integer, floating-value, and script-label resolver bodies. Keeping StartChild's source pointer in a volatile stack home reproduces its real EAX child argument and two stack arguments. That callee scope in turn derives EDI for SpawnChild's parent argument. The integer resolver is exported only inside the disposable native context to preserve its genuine fastcall contract; no export enters the selected outer object or final game EXE.

All three unselected resolver bodies match their complete retail extents: integer 124 bytes, floating value 171 bytes, and script-label lookup 136 bytes. The floating resolver includes its maintained source. They do not add recovered bytes at this checkpoint.

**StartChild is not recovered.** Its complete C++ candidate emits 549 bytes against the original 550-byte function, with 416 differences including the extent. It is an unselected compiler anchor only; the final EXE retains the existing exact 550-byte assembly body at 0x0044DF70. Its candidate retains typed operand dispatch, stack bounds, conversions, frame restoration, temporary active-child replacement, and success/failure behavior. Further volatile-index and instruction-pointer variants did not improve the complete-function result. The new evidence does not infer a StartChild byte match from the exact SpawnChild caller.

## Verification

The [checkpoint evidence](resource_cleanup_and_ecl_spawn_2026-10-01.evidence.json) records both complete regions, their current native-build and source hashes, the 39-region cleanup probe and single-region spawn probe, full comparisons of all genuine anchors, preserved aliases, and decoded direct-call targets. It verifies the contiguous 412,672-byte `.text` partition and exact source ownership. No retail bytes are used for native compilation; no bytes are masked; native extraction changes no instruction or address-operand bytes.

The final command was:

```sh
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
```

All 1,912 maintained source builds succeeded. The complete EXE SHA-256 remains `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`; `.text` remains `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`. `git diff --check` passed.

Reproducible scratch proofs are retained under `resource_cleanup_shared_2026_10_01`, `subagent_resource_cleanup_2026_10_01`, `subagent_ecl_child_pair_2026_10_01`, and `resource_cleanup_and_ecl_spawn_2026_10_01` in `matching2/build/experiments`. The last directory contains the full build log and evidence-generation script. Historical notes below describe their original audit states; this checkpoint supersedes their statements about the cleanup and spawn still requiring assembly.
