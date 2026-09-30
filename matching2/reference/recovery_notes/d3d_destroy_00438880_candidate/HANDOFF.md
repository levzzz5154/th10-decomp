# D3DResourceManager_Destroy 00438880 — measured compiler blocker

No promotion, no main-tree edits, and no commits. All work is under this scratch directory; copied the current maintained `matching2/msvc` tree, not HEAD.

## Reproduce

From `/home/levzzz/Games/th10Decomp`:

```
python3 /home/levzzz/.hermes/cache/scratch/d3d-destroy-native/run_probe.py fresh-repeat
```

The runner compiles with pinned MSVC 13.10.6030 `/GL /EHsc` and native LINK `/LTCG`. It produces fresh PE/MAP/object/log/disassembly/report artifacts. Its oracle is the maintained complete exact image `matching2/build/msvc/th10.exe`. Comparison never masks or rewrites instruction bytes. Zero-filled declarative layout contributions use the existing `_prepare_padding_object` metadata-only helper. This is an investigative native probe, not a validated integration manifest or whole-build gate.

## Best result: final-fresh/report.json

* Destroy at 00438880: **101 bytes versus required 103**, exact prefix **53 bytes**, first instruction mismatch at **+0x35**.
* List Release at 00449E50: **82/82 bytes exact**, native EAX receiver / stack owner / RET4.
* PlatformWorker::Stop at 0044C150: **101/101 bytes exact**, native ESI receiver.
* List pending-clear destructor at 00449A90: **12/12 bytes exact**.
* Compiler-synthesized complete `.text$x` unwind contribution at 00465350: **29/29 bytes exact**, including handler 00465363.
* Compiler-synthesized complete `.xdata$x` at 004713B4: **44/44 bytes exact**.

The library `basic_string::_Copy` handler label in the manifest is not evidence of string semantics here. Actual retail data and generated metadata establish two genuine embedded-list destructor cleanups. The unwind map entries are `(-1,00465350)` and `(0,00465358)`; the two funclets load the manager from `[EBP+4]`, and the secondary funclet adds 0x24. Both tail-jump to 00449A90. FuncInfo at 004713C4 has magic 19930520, maxState=2, unwindMap=004713B4, no try blocks/catches. The shared handler loads 004713C4 and jumps to **0046276D**. This was reproduced naturally from C++ member destruction, without fabricated RAII state or hand-built handler/table bytes.

## Remaining mismatch

Retail at +0x35:

```
lea esi,[edi+24h]
push edi
mov eax,esi
call 00449E50
```

Candidate:

```
push edi
lea eax,[edi+24h]
call 00449E50
```

The candidate then clears secondary slots through `[EDI+2C/30/34]`, while retail uses `[ESI+8/C/10]`. Private calls, FS:0 prologue/epilogue, state=1, stack manager, saved ESI/EDI, RET4, and genuine exception metadata now reproduce. Residual blocker is secondary-list address retention in ESI / scheduling, not unavailable callee ABI or unknown exception semantics. No claim that this function is exact.

## Source and adapter

Candidate: `msvc/src/render/d3_d_resource_manager_destroy_00438880.cpp`.

The initial candidate reused the canonical volatile one-word owner aggregate and emitted 106 bytes, with an unnecessary caller volatile spill and altered EH scheduling. A returned owner temporary emitted 110 bytes. The retained address-qualified ABI adapter places volatility only on the callee's stack owner read, using `*static_cast<Scheduler* volatile*>(&owner)`, which avoids caller volatile temporaries while reproducing the canonical 82-byte Release body exactly. Its header and implementation are `msvc/include/th10/game/resource_list_destroy_abi.hpp` and `msvc/layout/ltcg/destroy_release_adapter.cpp`. The actual canonical production owner and declaration remain untouched. Adapter/callee/clear/EH bytes receive zero recovery credit.

The non-selected stdcall wrapper roots an ordinary C++ destructor; native LTCG selects the observed stack-this / RET4 convention. Attempting an explicit stdcall destructor showed that this compiler ignores that convention on destructors; the final source removes that misleading annotation. A memory-barrier variant stayed 101 bytes but worsened scheduling, and was discarded.

`final-fresh/inputs` preserves the final compiled C++ input snapshots; the report includes input/tool hashes, candidate/retail streams, addresses/extents, and EH comparisons. The copied canonical release source is still available in scratch. There is no promotable manifest because Destroy's complete contribution fails extent and byte gates. Whole-build/play testing was not run, since nothing was integrated and game execution is not needed for this byte-contract blocker.
