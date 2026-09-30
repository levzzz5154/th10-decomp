# UI thread spawn at 0x00420EA0: exact C++ in the worker cluster

2026-09-27. `GameUiThreadHost::Spawn` replaces the 118-byte region at
0x00420EA0 with ordinary C++, free of inline assembly. The fresh native LTCG
probe in `matching2/build/experiments/thread_spawn/probe_final.json` proves all
six selected functions exact: Spawn 118 bytes, Destroy 36, StopNoDelete 16,
Stop 101, Start 56, and StartSuspended 56. Instruction changes, address rewrites,
and masked bytes are all zero. The probe uses the immutable retail oracle and
the production native-cluster export path.

Live Ghidra instance 2136235 confirms the target has an EDI receiver and two
stack arguments: thread entry first, thread context second, with `RET 8`. It
enters the critical section at receiver +0x6DC, increments the byte at +0x6FA,
stops the embedded worker at +0x62C, and creates a replacement thread with
`_beginthreadex(0, 0, entry, context, 0, &worker.thread_id)`. After saving the
handle, it leaves the critical section, decrements that byte, and returns zero.
The byte uses unsigned wrapping increments and decrements.

The embedded worker uses the already recovered `PlatformWorker` layout.
Retail keeps its address in ESI across Stop and `_beginthreadex`, its critical
section address in EBX across Enter/Leave, and the thread entry in EBP across
all calls. The first source model accessed the worker directly as an embedded
member. It earned the correct register ABI but emitted 133 bytes: after Stop,
the compiler used long EDI-relative field displacements instead of retaining
the ESI-relative subobject accesses. The explicit local
`PlatformWorker* active_worker = &worker` preserves that worker address for
the subsequent stores and thread-ID pointer, reproducing all 118 bytes.

The sole live caller is 0x0041813F inside `GameUi_CreateAndPublish` at
0x004180E0. It pushes context zero and entry 0x00417C70, loads EDI with the
host singleton 0x00491C28, and keeps the separately allocated UI in ESI across
the call before returning it. `ghidra_decompile.txt` and
`ghidra_disassembly.txt` in the experiment directory retain the target evidence.

## Promotion inputs

Copy these files from `matching2/build/experiments/thread_spawn/msvc` into the
same paths under `matching2/msvc`:

- `src/game/thread_spawn.cpp`
- `include/th10/game/ui_thread_host.hpp`
- `layout/ltcg/worker_start_0044c1c0.json`
- `layout/ltcg/worker_start_0044c1c0_context.cpp`

Merge the single region in `thread_spawn/proposal.json` by address; preserve
its `previous_record`. Do not replace the maintained manifest with the scratch
manifest. The new symbol is
`?Spawn@GameUiThreadHost@@QAEHP6GIPAX@Z0@Z`.

The registered worker cluster path remains unchanged. Spawn is an additional
source and selected `.text$02spawn` contribution. Its region appears before
the existing worker family, so the former initial gap is split around
0x00420EA0–0x00420F15. The second zero layout gap begins at 0x00420F16 and
ends at the existing Destroy address 0x0044C100. These are compiler-layout
padding, never recovered game code. The context remains at 0x0044C240 and
grows from 88 to 113 bytes. Its array loop calls both worker Start variants and
the UI host's Spawn; all five previous contributions remain byte-identical.

The cluster binds the imported EnterCriticalSection and LeaveCriticalSection
slots to 0x004660B0 and 0x004660B4. Stop's complete real C++ body stays visible
to the same LTCG link, preserving its ESI receiver across all callers. Only
Destroy and StopNoDelete remain public roots; Spawn is reached by the synthetic
compiler context and retains its private EDI convention.

Reproduce:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/platform/worker_start.cpp \
  --project matching2/build/experiments/thread_spawn/msvc \
  --output matching2/build/experiments/thread_spawn/reprobe --json
```

The new source and shared layout are verified together. Whole-executable
integration still requires the ordinary full build after promotion.
