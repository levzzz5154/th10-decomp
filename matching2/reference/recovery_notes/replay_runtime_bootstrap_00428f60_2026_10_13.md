# Replay runtime bootstrap at 0x00428F60 — equivalent recovery, 2026-10-13

## Outcome

The 1,344-byte region `asm_FUN_00428f60_00428f60` is recovered as readable C++
under `matching2/msvc/equivalent/game/replay_runtime_bootstrap_00428f60.cpp`,
accepted through the equivalent-recovery path:

```
replay_runtime_bootstrap_00428f60: 1,344 of 1,344 bytes used, 387 of 389
instructions identical, 0 base/index swaps, 0 frame-offset, 2 instructions in
3 recorded differences
```

The recorded set (layout `matching2/msvc/layout/equivalent/replay_runtime_bootstrap_00428f60.json`):

- `0x330`/`0x345` (`code-shape`): the stage-node cursor and count stores.
  Retail encodes them through the scaled stage index
  (`mov [ebx+edx*4+0xa4],ecx` / `mov [ebx+edx*4+0xb4],ebp`); the model
  materialises the node pointer one statement early and encodes the same two
  stores as `mov [eax+0x4],ecx` / `mov [eax+0x14],ebp`. Same addresses, same
  values, same order; 8 bytes shorter, which also explains the trailing
  `alignment-padding` hunk (the model image's inter-function filler where
  retail's body used the bytes).
- `0x53f` (`alignment-padding`): eight `int3` filler bytes, a consequence of
  the shorter stores. Not recovered code.

Everything else — the register-only entry (receiver EBX, mode EAX, path ECX),
the whole allocator/new/null-check-ctor chain, the flag-parity block, all six
scheduler-node registrations, every call target and global — is byte-exact.

## Files

- `matching2/msvc/equivalent/game/replay_runtime_bootstrap_00428f60.cpp` — the
  body (`ReplayManager_004296f0::Start`).
- `matching2/msvc/layout/ltcg/replay_runtime_bootstrap_00428f60_context.cpp` —
  the compiler context: the factory 0x00429610 (via its registered source) plus
  stand-in bodies for every callee whose register convention no declaration
  names (loader 0x0042A200 receiver-in-ESI, pool clear 0x0042AB20
  stage-EAX/lists-ECX, pool page append 0x0042AA50 slot-ESI/owner-pushed,
  configuration defaults 0x00418C40 dead-first-arg/EDX, frame timer 0x0042A930
  receiver-in-EAX, both scheduler registrations task-ESI/priority-EDI), and the
  manager destructor stand-in the factory's `delete` needs.
- `matching2/msvc/layout/equivalent/replay_runtime_bootstrap_00428f60.json` —
  the recorded differences and bindings.

`regions.json` keeps the region's `asm` source (the naked body still ships the
retail bytes); the only delta is appending to `equivalent_recoveries`:

```json
{"region": "asm_FUN_00428f60_00428f60", "layout": "layout/equivalent/replay_runtime_bootstrap_00428f60.json"}
```

The 0x00429610 cluster manifests are untouched. The obsolete draft header
`include/th10/game/replay_runtime_start_00428f60.hpp` is removed.

## Nonobvious insights

1. **The image entry blocks LTCG parameter rehoming.** The first model link
   used `?Start@ReplayManager_004296f0@@QAEHHPBD@Z` as `/ENTRY` (mirroring the
   region's function) and the whole-program pass compiled it with the plain
   thiscall convention (mode and path on the stack, `ret 8`). Pointing
   `/ENTRY` at a synthetic context that calls the factory
   (`?ReplayManagerStartCompilerContext@@YGHHPBD@Z`, rooted through
   `roots: ["?ReplayManager_Create_00429610@@..."]`) let the pass treat Start
   as an ordinary internal function and reproduce the retail register homes.
2. **The context must not define a competing Start.** The cluster drivers
   shape a stand-in `Start` for call-resolution; an equivalent model that
   pulls such a driver in duplicates the symbol. The context file therefore
   carries every stand-in *except* Start, whose definition is the model's.
3. **Scheduling pins.** Three `_ReadWriteBarrier()` placements pin the
   record-fill and rng-restore store/load orders (the compiler otherwise
   hoists the parity loads above the stage/seed stores and sinks the
   generation store below the SetGauge argument push). The boss-gauge
   condition reads the configuration word through its retail address
   (`*(int *)0x00491FC4`) because the parity expression consumes the loaded
   copy; without the fresh read the compiler compares the register
   (`3b cd`) where retail compares memory (`39 2d`).
4. **The stage-node rewind shape.** Retail keeps the scaled index in a
   register across the cursor/count stores and materialises the node pointer
   only for the cursor_end pair. Every cached-pointer spelling produced the
   short `[eax+disp]` store forms; the array-of-nine-dwords view reproduces
   retail's prefix exactly and leaves only the two recorded store encodings.

An exact (semantic) recovery may still be possible by co-compiling the body
inside the `replay_manager_create_00429610` cluster — the two store encodings
are the only residual — but the scheduler Materialises the node base before
the cursor/count stores under every source shape tried, so the equivalent
path is the one landed here.

## 2026-10-17: store-encoding spellings probed; parked

The two recorded store encodings were probed again from the byte side: the
region's 507 differing bytes run from the first store (the byte runs start at
the store pair and continue to the region tail), so the two `mov [eax+disp]`
short forms shift every following instruction. Inlining the node pointer
behind the stores and the flat dword-index spelling
(`((unsigned int*)nodes)[stage*9+N]`) both keep the short encodings (the
hunks merely move); re-reading `g_globals.stage` at each store adds an
unbound-symbol reference the layout would have to bind.

Region stays equivalent (507 differing bytes). The remaining lever is the
one the note names: an addressing-mode decision in c2 that no source
spelling has been found to steer.

## Byte-side note for future attempts

The instruction verdict reports only 3 hunks here while 507 bytes differ:
the encodings' length difference shifts the whole tail. Any future variant
must be measured with the byte script, not the hunk count.

## 2026-10-18: addressing-mode mechanism solved; region stays parked

The residual is the c2 disp-less-base address CSE: store targets are
address-values sharing one node with the pair's pointer (trace: succ22=10,
`lea` picked 3rd → hoisted before the stores, 507 differing bytes); retail's
node has only the pair as uses (stores fold as chains, `lea` sits before the
pair). ~70 spellings measured by bytes across the model and a plain-cl repro:
every single-expression spelling keeps the hoisted `lea`; every
split-expression spelling is canonicalised (×36 ≡ ×9×4) into the
registered-index families (`shl eax,2` / `[eax+ebx*1+disp]` /
`lea eax,[ebx+edx*4]`+disps). `_ReadWriteBarrier`, volatile
stores/loads/pointers, field-pointer slots, param-field slots, disp-in-base,
helper accessors, reference aliases, second assignments and statement
reordering all ruled out. Scheduler mechanism rule:
`msvc-c2-address-cse-use-set-def-placement`.
