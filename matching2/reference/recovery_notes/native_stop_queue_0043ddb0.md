# Native stop-queue recovery at `0x0043DDB0`

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27. An isolated native MSVC 7.1 `/GL` + `/LTCG` experiment recovers the complete 52-byte stop producer with ordinary C++ and zero differing bytes against the retail oracle. The selected compiler contribution has SHA-256 `943e81138044ce7dd480ba8be950f4c1d62704ab943b843f9c50298897eeaa52`; extraction changes zero instruction bytes and zero address operands. The proof is `matching2/build/experiments/stop_queue/exact.json`, with the native map, executable and provenance report under its `exact/clusters/stop_queue` directory.

The source scans twelve signed pending sound IDs at owner `+0x620`. A negative entry receives the requested sound ID, while a matching entry keeps its existing ID. Both cases store `-1` in the paired pending pan count at `+0x650`, which requests a stop when the dispatcher consumes the queue. A full queue with no matching ID is unchanged. The machine body leaves the selected slot, or twelve when full, in EAX. The readable C++ declaration remains `void`, reflecting the absence of an explicit return in the saved decompiler signature; the byte proof covers this observed EAX value too.

The synthetic context loops over an array of owner pointers with one sound ID fixed for the loop. Native LTCG chooses ESI for the owner, EDI for the sound ID, ECX for the advancing slot pointer, EDX for each loaded ID and EAX for the slot index. The callee ends with plain RET. Only the selected 52-byte function enters recovered code; the 42-byte context is compiler input, not game code.

The successful body uses a signed `for` index, a pointer advancing in parallel, a break on a negative ID and a shared stop-store label on an ID match. The guard after the loop produces the second `cmp eax, 12` retained by retail. An initial `while (*cursor >= 0)` experiment selected the correct ESI/EDI ABI but hoisted the first load, used EDX for the index and removed the guard, producing 56 bytes. `for`, `do` and bounded `while` variants with the break inside the loop all produced the exact 52-byte instruction sequence. The signed `for` version is retained for readability.

The isolated project is `matching2/build/experiments/stop_queue/project`. Its promotion artifacts are:

- `src/unidentified/unassigned_0043ddb0.cpp`
- `layout/ltcg/stop_queue.json`
- `layout/ltcg/stop_queue_context.cpp`

The region symbol is `?QueueEffectStop@StopQueue_0043ddb0@@QAEXH@Z`, and the cluster name is `stop_queue`. Integration must copy those three files, set the maintained region at `0x0043DDB0` to `kind: "semantic"` with that symbol, and register `layout/ltcg/stop_queue.json` in `ltcg_clusters`. The maintained source and manifest were not changed during experimentation.

The exact isolated probe was:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/unassigned_0043ddb0.cpp \
  --project matching2/build/experiments/stop_queue/project \
  --output matching2/build/experiments/stop_queue/exact --json
```

This evidence proves this function's private entry convention and complete bytes. Promotion still requires the maintained-project probe and whole-executable gates. The existing sound-effect differential test independently documents queue and dispatcher semantics; its conventional-interface candidate is preserved as reference material rather than selected code.
