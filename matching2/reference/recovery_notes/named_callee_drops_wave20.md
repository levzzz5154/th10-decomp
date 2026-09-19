# The named-callee drops (wave 20) - 3 landed, and the anchor lever's real limits

2026-09-19, agent `NamedCalleeDrops`. Target: the drops the wave-18 and wave-19
blocks left with the callee and its convention named. Worked in
`/tmp/NamedCalleeDrops/msvc` (`cp -a matching2/msvc`) and promoted with
`promote_scratch.py --apply` per address.

**3 landed EXACT (123 bytes):** `0x00441D70` (20), `0x0043BBA0` (77),
`0x004658F0` (26). Each was re-probed against the **maintained** tree after
promotion, with the maintained layout set loaded:

```text
0x00441d70      20 bytes  ?Evaluate@CurveObject_00441d70@@QAEMXZ  EXACT
0x0043bba0      77 bytes  ?StartWorker_0043bba0@@YGXXZ  EXACT
0x004658f0      26 bytes  ?StartThread_004658f0@@YGXXZ  EXACT
```

## What worked

1. **An existing anchor is reusable verbatim.** `0x00441D70` is byte-identical to
   the landed `0x00404CF0` (the third twin of the `0x44C350` curve leaf): the whole
   region is the same 20-byte x87 call site, so `cl_00441d70.json` carries the same
   `?EvaluateCurveAnchor_0044c350@@YGMIMM@Z` anchor (320 bytes at `0x0044C350`) and
   the same array-walking context, with only the type name and the address changed.
   The anchor earns `op` in EAX, exactly as it does for `0x412E10`/`0x404CF0`/`0x404D10`.

2. **`WorkerThread_00439390::Stop()` is the reusable "object in ESI across calls"
   anchor.** `0x0043BBA0` is the freestanding twin of the landed
   `PlatformWorker::Start` (`0x0044C1C0`): it stops the global worker at
   `0x474DD4` and then calls `_beginthreadex`. The declaration-only `Stop()` made
   the pass emit the thiscall register (`mov ecx,0x474DD4`, 5 bytes) against
   retail's `mov esi,474DD4h` + `push esi`/`pop esi` (7). Compiling a Stop body as
   an **anchor at `0x44C150`** whose object lives across the wait/close calls
   earns ESI, and the call site comes out `push esi / mov esi,474DD4h / call /
   ... / pop esi`. The anchor body is the one from
   `src/platform/platform_stop_worker_0044c150.cpp` (87 bytes emitted; declared
   size corrected to it).

3. **An anchor may sit *before* the modelled function, but then the section names
   must follow the addresses.** `0x004658F0` calls `0x421F00` (below it), whose
   object register is ESI. The naive `.text$03anchor` / `.text$01start` naming
   made the linker emit the sections in name order, not address order, and the
   whole span shifted; renaming the anchor `.text$01anchor` (and the function
   `.text$03start`) fixed it. Two more harness points: the context's declared
   address must be mirrored into `spec['entry_address']`, and a mutating retry
   must keep the loader-generated `_ltcg_gap_N` symbols (`spec['gaps']` may be
   edited in place, not replaced).

## Source text

### `0x00441D70` (20) - `src/unidentified/unassigned_00441d70.cpp`

layout `layout/ltcg/cl_00441d70.json`, driver `layout/ltcg/cl_00441d70_context.cpp`

```cpp
struct CurveObject_00441d70 {
    unsigned char pad_000[0x38];
    float field_38;
    unsigned char pad_3C[0x44 - 0x3C];
    int field_44;
    int field_48;
    __declspec(noinline) float Evaluate();
};
float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first, float second);

#pragma code_seg(".text$01evaluate")
float CurveObject_00441d70::Evaluate() {
    return EvaluateCurveAnchor_0044c350(field_48, field_38, (float)field_44);
}
#pragma code_seg()
```

### `0x0043BBA0` (77) - `src/unidentified/unassigned_0043bba0.cpp`

layout `layout/ltcg/start_0043bba0.json`, driver
`layout/ltcg/start_0043bba0_context.cpp` (anchor
`?Stop@PlatformWorker_0043bba0@@QAEXXZ` at `0x0044C150`, 87 bytes)

```cpp
struct PlatformWorker_0043bba0 {
    const void* vtable;
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    void* entry;
    __declspec(noinline) void Stop();
};
extern "C" PlatformWorker_0043bba0 data_00474dd4;
extern "C" void* data_00474dd8;
extern "C" unsigned int data_00474ddc;
extern "C" int data_00474de0;
extern "C" int data_00474de4;
extern "C" void* data_00474dec;
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
        void* security, unsigned int stack_size, void* start, void* arglist,
        unsigned int initflag, unsigned int* thread_id);

#pragma code_seg(".text$01start")
__declspec(noinline) void StartWorker_0043bba0() {
    data_00474dd4.Stop();
    data_00474dec = (void*)0x43BA90;
    data_00474de4 = 1;
    data_00474de0 = 0;
    data_00474dd8 = (void*)asm_beginthreadex_00453683(0, 0, (void*)0x43BA90,
                                                     (void*)0x491C28, 0, &data_00474ddc);
}
#pragma code_seg()
```

### `0x004658F0` (26) - `src/unidentified/unassigned_004658f0.cpp`

layout `layout/ltcg/start_004658f0.json`, driver
`layout/ltcg/start_004658f0_context.cpp` (anchor `_Init_00421f00@4` at
`0x00421F00`, 83 bytes, placed **before** the function)

```cpp
extern "C" void __stdcall Init_00421f00(void* object);
extern "C" void __cdecl Register_00452e0a(void* entry);
extern "C" char data_00491c28;
#pragma code_seg(".text$03start")
__declspec(noinline) void StartThread_004658f0() {
    Init_00421f00(&data_00491c28);
    Register_00452e0a((void*)0x4659F0);
}
#pragma code_seg()
```

## Drops, with deltas

Measured this wave (probe `EXACT` gate, first differing byte in `got`/`want`):

| address | size | model | result |
| --- | ---: | --- | --- |
| `0x0040B320` | 73 | member `Update()` (polar record inline at `this+0xC`), `AdvancePolarMotion`/`Angle_Normalize`/`PolarToVectorRetail` bound absolutely; six driver shapes (array walk, index loop, extra live pointer, field read-after, two-accumulator, nested) | emitted **72**, first `+0` got `f6` want `56`. Every driver gives ESI-entry (`testb $1,0x28(%esi)` with no prologue) where retail has EAX-entry (`push esi; mov eax,esi`). The pass minimises the callee: ESI-entry needs no save because the custom ABI clobbers ESI, so it is never worth the extra `mov`. Same blocker as `0x415E30`. |
| `0x00413300` | 71 | member `Release()` with `@Scheduler_Remove@8` bound; early-return and declaration-flipped spellings | emitted **71, 2 differing at `+0x21`**: got `d7` (`mov edx,edi`) want `ce` (`mov ecx,esi`) - the two argument-setup moves come out reversed. Pure setup-order tie-break; `int*`/`void*` parameter type swaps do not move it. |
| `0x00439080` | 28 | member `Destroy(flags)` and `__stdcall` free-function spellings, both with an EAX `0x43A910` anchor | emitted **30**, first `+0` got `56` (`push esi`) want `8b`. Because the anchor consumes the object in EAX, the pass puts `this` in EAX (saving 2 bytes at the call) and pays a `push esi`/`pop esi` where retail's ESI-entry pays neither. |
| `0x00428F30` / `0x0041ACB0` | 42 / 54 | EH vector-constructor call to `0x45252D` plus `rep stosd`; needs a five-argument anchor at the callee's retail address | **structural drop.** `0x45252D` is not 16-byte aligned (`mod 16 == 13`), so the linker places the anchor at `0x452530` and the caller's baked `call rel32` cannot be retail's. No body shape can fix a section that cannot start where retail's call points. |

Already carrying a measured delta from the sweep notes and **not re-attempted**
(callee/convention named, no new lever found; deltas as recorded there):

| address | size | delta / blocker |
| --- | ---: | --- |
| `0x00415E30` | 93 | 92 vs 93; receiver in ESI where retail has EAX (same as `0x40B320`). |
| `0x0044BFA0` | 74 | 74 vs 74, 12 differing; the two `[esi+4]`/`[esi+0Ch]` loads swap registers and the first x87 pair is `fld 1.0f; fadd [esi+8]` vs retail's `fld [esi+8]; fadd 1.0f`. |
| `0x00418850` | 65 | `strcat` spelling 65 vs 65, 30 differing; hand-written 64 vs 65 (retail keeps `text` in EAX, pushes ESI/EDI after the length loop). |
| `0x00437200` | 159 | 176 vs 159; excess in the `0x19` branch's `(value == 0) ? 0 : 0x80` flag and the loop bounds. |
| `0x0041BE40` | 46 | anchor earns `(EAX body, ESI owner, stack arg)` but the scheduler still reorders the pool/argument (45 vs 46, 36 differing from `+0`). |
| `0x00434B80` | 15 | anchor-body job for `0x43E460` (EAX object, EDX string, 2 stack args); the caller is a bare EAX-live-in forwarding thunk, no model emitted. |
| `0x004357D0` | 36 | EAX live-in feeding `0x434C30`'s second parameter (also EAX); both ends need the EAX convention. |
| `0x00439700` | 45 | 41 vs 45; `TextLog_0044B8E0::AppendLine` puts its log object in EDI, which a declared call site reproduces only by pushing it. |
| `0x0043D640` / `0x0043D670` | 37 / 32 | anchor body for `0x44B360`; handed to sibling `VeinCalls`, which landed them. |
| `0x0043DA80` | 44 | anchor body for `0x44D440` (`mov edi,eax` callee). |
| `0x00446530` / `0x00446570` / `0x00436D60` | 55 each | three live-in registers (EAX accumulator, EDX packed word, ESI counter pointer); no declaration names that triple. |
| `0x0044C6E0` | 114 | 106 vs 114; the pass promotes `a0`/`a1` to ECX/EDX and pops `ret 38` where retail keeps all sixteen on the stack (`ret 40`). Needs a caller with ECX/EDX occupied, which a synthetic context cannot express. |
| `0x0044D740` | 67 | callee `0x44D4E0` is recovered and earns EAX, but the region's other branch is a double-indirected virtual `call *0x48(%ecx)` through `[[this+4]]`, so the source cannot be spelled without a second anchor. Not emitted. |

`0x0043C910` was on this list and was landed by `VeinCalls` before the sweep
reached it; it is not counted here.

## Manifest / source edits and validation

* Three region records flipped to `semantic` (`0x00441D70`, `0x0043BBA0`,
  `0x004658F0`) and three layouts added to `ltcg_clusters`
  (`layout/ltcg/cl_00441d70.json`, `layout/ltcg/start_0043bba0.json`,
  `layout/ltcg/start_004658f0.json`), all through
  `promote_scratch.py --scratch /tmp/NamedCalleeDrops/msvc --address <addr> --apply`.
  No manifest field was hand-edited.
* `0x004658F0`'s promotion first tripped `merge_layout`'s `int(g['address'], 16)`
  because the harness wrote two gap addresses as ints; `load_cluster` and
  `register_cluster` accept both, and the cluster was registered and the record
  flipped before the merge step, so the promotion is complete (confirmed by the
  maintained-tree probe above). Future layouts should keep gap addresses as
  strings.
* The scratch held one unverified cluster (`polar_0040b320.json`, the failed
  `0x40B320` model); it was unregistered with
  `register_cluster.py --unregister --apply` and its files removed **before**
  promotion, so `promote_scratch` did not carry it into the tree.
* `build_msvc.validate_project(config, reference)` passes on the result:
  `4425 regions / 2354 units`. `make` was not run.
