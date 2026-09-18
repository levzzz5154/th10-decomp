# `0x00401440` CreateGameThread - decoded, one byte short of the EAX-carried call

2026-09-19. Second-wave agent `CreateGameThread`. The region was **not landed**.
Measured extent is exact at **69 bytes** in both the plain path and the native
cluster path; the cluster path leaves **exactly one differing byte**, the ModRM
of the register transfer that hands the object to `LoadGameThreadResources`
(`0x00401110`), which reads that object from **EAX** and is not co-compilable
without recovering three further regions.

## 1. The listing, and which APIs it calls

```asm
00401440  56              push  esi
00401441  68 ac 89 00 00  push  0x89AC
00401446  e8 ..           call  ??2@YAPAXI@Z                    0x00452493  operator new
0040144b  83 c4 04        add   esp,4
0040144e  85 c0           test  eax,eax
00401450  74 0b           je    0040145D
00401452  8b f0           mov   esi,eax                        ; ctor receiver := ESI
00401454  e8 ..           call  ??0GameThread@@QAE@XZ           0x00401000
00401459  8b f0           mov   esi,eax                        ; result := returned this
0040145b  eb 02           jmp   0040145F
0040145d  33 f6           xor   esi,esi
0040145f  8b c6           mov   eax,esi                        ; loader receiver := EAX
00401461  e8 ..           call  LoadGameThreadResources_00401110 0x00401110
00401466  85 c0           test  eax,eax
00401468  74 17           je    00401481
0040146a  85 f6           test  esi,esi
0040146c  74 0f           je    0040147D
0040146e  56              push  esi
0040146f  e8 ..           call  DestroyGameThread_00401260      0x00401260   (RET 4)
00401474  56              push  esi
00401475  e8 ..           call  free_004524a1                   0x004524A1
0040147a  83 c4 04        add   esp,4
0040147d  33 c0           xor   eax,eax
0040147f  5e              pop   esi
00401480  c3              ret
00401481  8b c6           mov   eax,esi
00401483  5e              pop   esi
00401484  c3              ret
```

**No thread or handle API is involved.** The name is only Ghidra's label for the
game-thread *factory*: there is no `CreateThread`/`_beginthreadex`, no handle
anywhere, and therefore no `__imp__*` import to bind. The five callees are

| call | address | ABI as retail uses it | bound in the manifest? |
| --- | --- | --- | --- |
| `??2@YAPAXI@Z` | `0x00452493` | `__cdecl(unsigned)` | yes - `??2@YAPAXI@Z`, `_asm_operator_new_00452493` |
| `??0GameThread@@QAE@XZ` | `0x00401000` | receiver in **ESI**, returns this in EAX | yes - landed semantic region (`src/game/game_thread.cpp`) |
| `LoadGameThreadResources_00401110` | `0x00401110` | receiver in **EAX**, plain RET | yes - `_asm_LoadGameThreadResources_00401110` |
| `DestroyGameThread_00401260` | `0x00401260` | `__stdcall(GameThread*)`, RET 4 | yes - `_asm_DestroyGameThread_00401260`, `@asm_DestroyGameThread_00401260@4` |
| `free_004524a1` | `0x004524A1` | `__cdecl(void*)` | yes - `_asm_free_004524a1`, `_entry_free_004524a1` |

`0x00401440` is the **only** caller of both `0x00401000` and `0x00401110` in the
whole image, so both of those private receiver conventions were chosen for this
call site.

The semantics are the ordinary factory:

```cpp
GameThread* thread = new GameThread;                    // operator new + in-place ctor
if (LoadGameThreadResources(thread) != 0) {             // nonzero = failure
    if (thread) { DestroyGameThread(thread); free(thread); }
    return 0;
}
return thread;
```

Source-shape detail worth keeping: the **failure test must be written first**
(`if (load(...) != 0) { ...; return 0; } return thread;`). With
`if (load(...) == 0) return thread;` first, MSVC inverts the branch and emits
`jne` into an *inline* success epilogue (69 bytes, mismatch at `0x00401468`).
The failure-first spelling emits retail's `je 0x00401481` into the out-of-line
success epilogue byte for byte.

## 2. Plain path: 69 bytes, two differing bytes

Scratch models were built in `/tmp/CreateGameThread/plain` and
`/tmp/CreateGameThread/msvc` (throwaway copies; the maintained tree was not
touched except for this note).

```cpp
// 0x00401440..0x00401484: CreateGameThread
struct GameThread {
    unsigned char bytes[0x89AC];

    __declspec(noinline) GameThread();
};

void* __cdecl operator new(unsigned int size);

extern "C" int __fastcall LoadGameThreadResources_00401110(GameThread* thread);
extern "C" void __stdcall DestroyGameThread_00401260(GameThread* thread);
extern "C" void __cdecl Free_004524a1(void* memory);

GameThread* CreateGameThread_00401440() {
    GameThread* thread = new GameThread;
    if (LoadGameThreadResources_00401110(thread) != 0) {
        if (thread) {
            DestroyGameThread_00401260(thread);
            Free_004524a1(thread);
        }
        return 0;
    }
    return thread;
}
```

```
python3 matching2/tools/matching/probe.py --source src/game/create_game_thread_00401440.cpp \
  --project /tmp/CreateGameThread/plain --output /tmp/CreateGameThread/out_plain --show 30
0x00401440      69 bytes  ?CreateGameThread_00401440@@YGPAUGameThread@@XZ  DIFFERENT
  first difference at 0x00401453
  expected: f0 e8 a7 fb ff ff 8b f0 eb 02 33 f6 8b c6 e8 aa fc ff ff 85 c0 74 17 85 f6 74 0f 56 e8 ec
  actual:   c8 e8 00 00 00 00 8b f0 eb 02 33 f6 8b ce e8 00 00 00 00 85 c0 74 17 85 f6 74 0f 56 e8 00
  0x00401452: 8b f0  mov    esi,eax      vs  actual 8b c8  mov    ecx,eax
NOT EXACT
```

`--json` reports `different_bytes: 2`, at `0x00401453` (`8b c8`/`mov ecx,eax`
instead of `8b f0`/`mov esi,eax`) and `0x00401460` (`8b ce`/`mov ecx,esi`
instead of `8b c6`/`mov eax,esi`). Every other byte, both branch targets, both
relocations (`??2@YAPAXI@Z`, the constructor) and the whole control flow are
identical. So the plain path is blocked by exactly the two receiver registers,
which is what the ordinary-TU report must say: the extent and flow are proven,
the ABI is not.

## 3. Native cluster: 69 bytes, one differing byte

`/tmp/CreateGameThread/msvc/layout/ltcg/create_game_thread.json` extends the
landed `game_thread` cluster: the same source pair is linked as one native
`/LTCG` image, so the constructor keeps its retail private convention (ESI in,
this in EAX out) and the factory's construction call becomes exact.

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/create_game_thread_00401440.cpp"

#pragma code_seg(".text$03context")
inline void* __cdecl operator new(unsigned int, void* memory) {
    return memory;
}

inline void __cdecl operator delete(void*, void*) {
}

int __stdcall CreateGameThreadCompilerContext(GameThread* threads, int count) {
    for (int index = 0; index < count; ++index)
        new (&threads[index]) GameThread;
    return CreateGameThread_00401440() != 0;
}
#pragma code_seg()
```

```cpp
// src/game/create_game_thread_00401440.cpp (cluster model)
struct GameThread {
    unsigned char bytes[0x89AC];

    __declspec(noinline) GameThread();
};

void* __cdecl operator new(unsigned int size);

extern "C" int __fastcall LoadGameThreadResources_00401110(GameThread* thread);
extern "C" void __stdcall DestroyGameThread_00401260(GameThread* thread);
extern "C" void __cdecl Free_004524a1(void* memory);

#pragma code_seg(".text$04create")
__declspec(noinline) GameThread* CreateGameThread_00401440() {
    GameThread* thread = new GameThread;
    if (LoadGameThreadResources_00401110(thread) != 0) {
        if (thread) {
            DestroyGameThread_00401260(thread);
            Free_004524a1(thread);
        }
        return 0;
    }
    return thread;
}
#pragma code_seg()
```

Layout (schema 1), with the two functions, the context and the two gaps whose
sizes make the emitted addresses land on `0x00401000` and `0x00401440`:

```json
{
  "schema_version": 1, "name": "create_game_thread",
  "source": "src/game/create_game_thread_00401440.cpp",
  "additional_sources": ["src/game/game_thread.cpp"],
  "driver": "layout/ltcg/create_game_thread_context.cpp",
  "headers": [], "image_base": "0x00400000",
  "description": "CreateGameThread plus the GameThread in-place constructor in one native-LTCG link so the object pointer reaches the constructor in ESI and its result returns in EAX.",
  "functions": [
    {"name": "GameThread_Construct", "source": "src/game/game_thread.cpp",
     "symbol": "??0GameThread@@QAE@XZ", "section": ".text$01thread",
     "address": "0x00401000", "size": 251,
     "actual_abi": "this in ESI; returns this in EAX; plain RET"},
    {"name": "CreateGameThread_00401440",
     "symbol": "?CreateGameThread_00401440@@YGPAUGameThread@@XZ", "section": ".text$04create",
     "address": "0x00401440", "size": 69,
     "actual_abi": "no arguments; object in EAX; plain RET"}
  ],
  "context": {"symbol": "?CreateGameThreadCompilerContext@@YGHPAUGameThread@@H@Z",
              "section": ".text$03context", "address": "0x00401100", "size": 50,
              "description": "Synthetic placement-construction caller that establishes the observed register convention; not recovered game code."},
  "gaps": [
    {"section": ".text$02layout",  "address": "0x004010FB", "size": 1},
    {"section": ".text$03zlayout", "address": "0x00401132", "size": 782}
  ],
  "constants": [],
  "roots": ["?CreateGameThread_00401440@@YGPAUGameThread@@XZ"],
  "absolute_symbols": [
    {"symbol": "_data_0046cb14", "address": "0x0046CB14", "kind": "data"},
    {"symbol": "_data_004776e0", "address": "0x004776E0", "kind": "data"},
    {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"},
    {"symbol": "??2@YAPAXI@Z", "address": "0x00452493", "kind": "relative_code"},
    {"symbol": "@LoadGameThreadResources_00401110@4", "address": "0x00401110", "kind": "relative_code"},
    {"symbol": "_DestroyGameThread_00401260@4", "address": "0x00401260", "kind": "relative_code"},
    {"symbol": "_Free_004524a1", "address": "0x004524A1", "kind": "relative_code"}
  ]
}
```

```
python3 matching2/tools/matching/probe.py --source src/game/create_game_thread_00401440.cpp \
  --project /tmp/CreateGameThread/msvc --output /tmp/CreateGameThread/out_final --show 30
0x00401000     251 bytes  ??0GameThread@@QAE@XZ                      EXACT
0x00401440      69 bytes  ?CreateGameThread_00401440@@YGPAUGameThread@@XZ  DIFFERENT
  first difference at 0x00401460
  expected: c6 e8 aa fc ff ff 85 c0 74 17 85 f6 74 0f 56 e8 ec fd ff ff 56 e8 27 10 05 00 83 c4 04 33
  actual:   ce e8 aa fc ff ff 85 c0 74 17 85 f6 74 0f 56 e8 ec fd ff ff 56 e8 27 10 05 00 83 c4 04 33
  0x0040145f: 8b c6  mov    eax,esi      vs  actual 8b ce  mov    ecx,esi
NOT EXACT
```

`different_bytes: 1`. The constructor call is now retail's `mov esi,eax` and the
whole failure/success block order is retail's. The landed `0x00401000` still
probes `EXACT` inside the merged link, so extending the cluster does not disturb
it. Gaps were calibrated from the link map (context emitted 50 bytes at
`0x00401100`; the second gap starts at the context's end `0x00401132`).

## 4. Why the last byte needs three more regions

`LoadGameThreadResources` (`0x00401110`) reads its object from **EAX**
(`mov 0x491c10,%edx; ...; mov %eax,%ebx` at entry) and no MSVC 7.1 prototype
puts an argument in EAX: `__fastcall` gives ECX/EDX, `__thiscall` ECX, the
`__stdcall`/`__cdecl` pair the stack. Only a function *bodied in the same /LTCG
link* can get that register, which is precisely how the constructor's ESI was
recovered. Three measured attempts:

| shape | result |
| --- | --- |
| plain TU, loader declared `__fastcall` (ECX) | `mov ecx,esi`; 2 bytes differ |
| loader bound as an opaque symbol, constructor co-compiled | `mov ecx,esi`; 1 byte differs |
| placeholder body for `0x401110` co-compiled, **member** model | allocator kept the declared `this` in ECX; unchanged |
| placeholder body co-compiled, **free-function** model, receiver live across two `__fastcall` calls | allocator reallocated the receiver, but to **EDI**, coalescing with the caller's variable and dropping the transfer instruction (22 bytes differ) |
| placeholder body co-compiled, **free-function** model, receiver dead after two field reads, EAX used as loop scratch | receiver in **ECX**; still 1 byte differs |

Rooting `0x401110` as a schema-1 root was rejected without a build: per the
frame_timer note a root *preserves the declared public convention*, and no
MSVC 7.1 declaration places an argument in EAX, so a root can only pin
ECX/EDX/stack - never the retail register.

So co-compiling the callee's body is *necessary but not sufficient*: the private
receiver register is a whole-program allocator decision, and none of the model
shapes measured produced EAX. Retail's own body (which uses ECX and EDX as
scratch for its own `__fastcall` callees, copies the receiver out of EAX into
EBX at entry, and runs 330 bytes) has to be in the link before that decision can
be re-tested; the 244 landed layouts are the evidence that matching bodies do
reproduce retail's private conventions.

Landing `0x00401440` therefore needs this whole cluster recovered together:

- `0x00401110` `LoadGameThreadResources`, 330 bytes, `src/game/load_game_thread_resources_00401110.cpp`.
  Its own callees are `?Recovery_LoadCachedResource@...` (ECX/EDX/stack, expressible),
  `TextLog_0044b810::Append` (ECX/stack), `SchedulerCallback_Create_00449ed0` and
  `Scheduler_RegisterPrimary/Secondary` (stack, expressible) - **plus two
  unexpressible receivers**: `InitializeEntity_00401de0` is called with the entity
  in **EDX** (`lea 0x14(%ebx),%esi; mov %esi,%edx; call 00401de0`) and
  `AnimationObject_ConfigureFromResource_0043e5a0` is called with
  ECX/EDX/**EAX** (`xor %edx,%edx; mov %esi,%eax; mov %edi,%ecx; call 0043e5a0`).
  For `0x00401110`'s own bytes to match, those two bodies must be in the same link.
- `0x00401DE0` `InitializeEntity`, 273 bytes, **no calls** - but its region is
  owned by `src/game/entity.cpp`, which owns eight regions: six landed semantic
  ones (`0x00401FF0`, `0x00402050`, `0x00405DE0`, `0x00406160`, `0x004061D0`,
  `0x0041AD60`) and a second unfixed asm region `0x00405D00` (215 bytes). A
  cluster must own *every* region of every source it declares, so that region
  has to be re-homed to its own translation unit (manifest `source` change plus
  the assembly removed from `entity.cpp`) before it can join; otherwise the six
  landed regions would have to be re-validated inside the cluster as well.
- `0x0043E5A0` `AnimationObject_ConfigureFromResource`, 356 bytes, **no calls**,
  own source file, unclaimed by any cluster.

Two of the three receiver conventions in that web (EDX for `0x00401DE0`,
ECX/EDX/EAX for `0x0043E5A0`) carry the same open allocator question as
`0x00401110`'s EAX.

## 5. Integration statement

- **Nothing from this run should be integrated**: no region landed, and the
  measured cluster is registered only in the throwaway copy
  `/tmp/CreateGameThread/msvc`.
- **Header edits**: none are *required* for the measured cluster - each source
  declares the minimal `GameThread` skeleton it needs. The clean cutover for the
  full recovery is one shared `include/th10/game/game_thread.hpp` (type marker,
  the two slot blocks, the scalar defaults, `GameThread()`,
  `LoadGameThreadResources()`) declared in the layout's `headers`, so the
  constructor, the loader and the factory agree on one type instead of three
  hand-kept padding structs.
- **Additional source files**: one new driver
  `layout/ltcg/create_game_thread_context.cpp` and one new layout
  `layout/ltcg/create_game_thread.json`; for EXACT also
  `src/game/initialize_entity_00401de0.cpp` (re-homed out of `entity.cpp`) and
  the recovered bodies of `src/game/load_game_thread_resources_00401110.cpp`
  and `src/game/animation_object_configure_from_resource_0043e5a0.cpp`.
- **Clusters**: the layout claims `src/game/game_thread.cpp`, which
  `layout/ltcg/game_thread.json` already owns, and `load_clusters` rejects two
  clusters claiming the same maintained source. The wave therefore has to
  **replace** `layout/ltcg/game_thread.json` with the merged layout above (that
  is what the measured build does) rather than add a second one, and the
  constructor's region has to be promoted through
  `matching2/tools/waves/promote_clusters.py`'s path:
  `register_cluster.py --apply` refuses a layout whose function's region is
  owned by a different file than the layout's `source`, which is exactly the
  constructor's case here.
- **Manifest**: with the merged layout, only the factory region
  (`0x00401440`, `kind` `asm` -> `semantic`) changes; the constructor's record
  and every symbol binding above already exist. No `symbols` entry has to be
  added for the measured cluster, and no `__imp__*` binding exists to copy
  because the region imports nothing.

Reproduce the two measurements with the two probe lines above; the scratch
copies also hold `build_loop.py` (section-size calibration against the link map)
and `side_by_side.py` (retail/compiled instruction pairing).
