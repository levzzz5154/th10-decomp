# 0x0044C1C0 (`PlatformWorker::Start`) landed through a merged native-LTCG cluster

2026-09-19. `0x0044C1C0` (56 bytes) is recovered as `PlatformWorker::Start` and
probes `EXACT` together with the three worker functions that were already landed
(`0x0044C100`, `0x0044C130`, `0x0044C150`). This note records why the region
cannot be landed as a single-source cluster, and the exact integration steps.

## The region

```asm
push esi / mov esi,eax / call 0044C150          ; PlatformWorker::Stop
mov ecx,[esp+8] / lea eax,[esi+8] / push eax / push 0 / push ecx / push edi / push 0 / push 0
mov [esi+18h],edi / mov [esi+10h],1 / mov [esi+0Ch],0
call 00453683 / add esp,18h / mov [esi+4],eax / pop esi / ret 4
```

`_beginthreadex(0, 0, entry, context, 0, &thread_id)`. Its three callers (inside
the unrecovered `0x0040A764`, `0x0040C2F5` and `0x0042C1AD` bodies) all do
`push <host>; lea eax,[<host>+off]; mov edi,<entry>; call`, so the region's
internal ABI is `EAX = receiver`, `EDI = thread entry`, `context` on the stack,
`ret 4`; `ESI` holds the receiver across the two calls and is saved/restored.

## What the plain and the single-source cluster paths cannot do

* A plain `__thiscall` model compiles to 60 bytes: the receiver would arrive in
  `ECX`, the entry would sit at `[esp+8]`, and the function would `ret 8`.
* A cluster with `Stop` bound as an opaque absolute symbol emits **54** bytes,
  with the receiver arriving in `ESI` and `mov ecx,esi / call 44c150`; the only
  differing bytes are `+0..1` (`8b ce` against retail's `8b f0`) and the absent
  `push esi`/`pop esi`. Both a plain array-walking caller and a context shaped
  exactly like the retail callers (host object live across the call, worker
  address computed fresh) produced the same 54-byte emission, because with an
  opaque callee the whole-program pass hands the receiver to `ESI` instead of
  moving it there. Retail's `mov esi,eax` is *both* the move of the receiver to
  a callee-saved register and the argument setup for `Stop`; that coincidence
  only appears when `Stop`'s own body is visible to the same `/LTCG` invocation.

`recovery_notes/whole_program_ltcg.md` states the rule this meets: both sides of
the private call must be in one `/LTCG` link. `Stop`'s source is owned by the
registered `layout/ltcg/platform_worker_shutdown.json` cluster, and
`load_clusters` refuses two clusters that share a maintained source
("clusters must have distinct maintained sources"), so the worker family has to
be one cluster.

## The cluster

Schema 1 with a synthetic context, the other three worker sources as
`additional_sources`, `Destroy`/`StopNoDelete` as `roots` (both keep their
public `ECX` receiver exactly as in the old schema-2 cluster) and a synthetic
array-walking caller as the `/ENTRY`. `Stop` stays a non-rooted callee because
three `/GL` callers reach it. The context mirrors the retail callers: a host
object holds the worker at `+0x10`, the host pointer stays live across the call
and is passed as the thread context, and the worker's address is computed fresh
for the call.

Layout: `layout/ltcg/worker_start_0044c1c0.json` (functions at `0x0044C100`,
`0x0044C130`, `0x0044C150`, `0x0044C1C0`; gaps `0x0044C124`, `0x0044C140`,
`0x0044C1B5`, `0x0044C1F8`; context `0x0044C200`, 69 bytes).
Driver: `layout/ltcg/worker_start_0044c1c0_context.cpp`.
Measured with `probe.py --source src/platform/worker_start.cpp`:
36 / 16 / 101 / 56 bytes, all four `EXACT`.

## Integration steps (multi-source layout, so `register_cluster.py` cannot do them)

1. `src/platform/worker_start.cpp`: the model (see the wave report).
2. `include/th10/platform/worker.hpp`: add
   `__declspec(noinline) void Start(void* context, PlatformWorkerEntry start);`
   next to the other members (the model includes the header, like
   `win32_timer.cpp` does; `noinline` goes on the declaration).
3. Add `layout/ltcg/worker_start_0044c1c0.json` and
   `layout/ltcg/worker_start_0044c1c0_context.cpp`.
4. Region record at `0x0044C1C0` becomes `semantic` with symbol
   `?Start@PlatformWorker@@QAEXPAXP6GI0@Z@Z` and name
   `semantic_PlatformWorker_Start_0044c1c0`, keeping the old record under
   `previous_record`.
5. Replace `layout/ltcg/platform_worker_shutdown.json` in `ltcg_clusters` with
   `layout/ltcg/worker_start_0044c1c0.json` and delete the superseded layout
   file; its three functions are declared by the merged layout. Registering
   both is rejected by `load_clusters` ("clusters must have distinct maintained
   sources"). Equivalently, move the merged layout onto the already-registered
   `platform_worker_shutdown.json` path (keeping its `name`) and add the driver
   beside it, which leaves `ltcg_clusters` untouched.

`register_cluster.py` (single-source only) can still do step 4 if it is run
against a one-function layout at the same path first: the registration records
only the region's symbol/extent and the layout path, both of which the merged
layout keeps. That is how the scratch copy was registered.

## Alternative model without the header edit

Declaring `struct PlatformWorker` locally in `worker_start.cpp` (as
`player_adjustpower_00405b60.cpp` does) with the same field offsets also probes
`EXACT` for all four regions; it was the first form tested and only differs in
where the class comes from.
