# 0x00421480 `RenderCamera::ApplyDefault` — wave 10: EXACT 287/287, and 0x00405300 loses its ABI anchor

2026-09-19, agent `CameraByte`. Region `0x00421480..0x0042159E`, source
`src/render/camera_setup.cpp`, 287 bytes. **Landed EXACT**, and the same landing
retires `layout/ltcg/render_stage_select_00405300.json`, its driver and the
`Camera_ApplyRetail_00421480_abi_anchor` stand-in for this region: 0x00405300's
body moves into the camera cluster, where the callee is now the modelled member.

## Disposition

```sh
python3 matching2/build/waves/results10/CameraApply/apply_package.py matching2/msvc
# landing applied to matching2/msvc
#   functions in layout/ltcg/anm_batch_flush_00442f50.json: 20, gaps 20, context 321, aliases 2
#   ltcg_clusters: 260 -> 259
#   removed layout/ltcg/render_stage_select_00405300.json and layout/ltcg/render_stage_select_00405300_context.cpp
```

Probe against the maintained tree:

```sh
python3 matching2/tools/matching/probe.py --source src/render/camera_setup.cpp \
  --source src/game/fun_00405300_00405300.cpp --project matching2/msvc --show 16
0x00405300      60 bytes  ?SelectDefaultStage@RenderStageState_00405300@@QAEXH@Z  EXACT
0x00421480     287 bytes  ?ApplyDefault@RenderCamera@@QAEXXZ  EXACT
0x004215A0     330 bytes  ?Apply@RenderCamera@@QAEXXZ  EXACT
... (all 20 functions of the cluster) ...
EXACT
```

The cluster build validates every declared contribution before it reports; a byte
comparison of each declared function's emitted extent against retail then shows
all 20 identical, i.e. no sibling function in the camera span moved:

```text
0x00421480   287 RenderCamera_ApplyDefault                    EXACT
0x00405300    60 RenderStageState_00405300_SelectDefaultStage EXACT
0x00401d20    60 RenderStageState_SelectStage_00401d20        EXACT
0x004215a0   330 RenderCamera_Apply                           EXACT
0x00442f50   133 AnimationManager_00442F50_Flush              EXACT
... 15 more ...
differing functions: 0 of 20
```

```text
0x00421480 287 bytes  identical True
  sha256 08e001207ac9a8e4516334f28bbbe653b823be84d01c03c8629bf398904a4f86
0x00405300  60 bytes  identical True
  sha256 6ef13bf3bd7024e9303d0803362c46b4659159e6aebf9ae4deaf9af4ddc4d482
```

The region's body:

```text
83 ec 2c 53 56 8b 35 10 1c 49 00 85 f6 74 05 e8 bc 1a 02 00 8b 87 d4 00 00 00
db 87 d4 00 00 00 85 c0 7d 06 d8 05 98 0b 47 00 8b 8f d8 00 00 00 d9 54 24 08
85 c9 d8 0d 0c 0b 47 00 db 87 d8 00 00 00 7d 06 d8 05 98 0b 47 00 d9 54 24 0c
8d 54 24 10 d8 0d 0c 0b 47 00 52 d9 44 24 0c 8d 44 24 20 d8 74 24 10 50 8d 4c
24 30 51 8d 77 4c 56 c7 44 24 34 00 00 00 00 c7 44 24 20 00 00 00 00 c7 44 24
24 00 00 80 bf c7 44 24 28 00 00 00 00 d9 5c 24 1c d9 c1 d9 5c 24 38 d9 54 24
3c dd 05 a0 0b 47 00 d9 f2 dd d8 d8 f9 d9 5c 24 40 d9 c9 d9 5c 24 2c d9 5c 24
30 e8 58 0c 03 00 ...
```

`fstp [esp+0x1c]` (`d9 5c 24 1c`) and `fdivr st,st(1)` (`d8 f9`) are retail's own
bytes: the two wave-9 defects — the kept register copy of the quotient and the
duplicated `half_height` — are gone.

`build_msvc.validate_project` accepts the manifest this landing produced:
4425 regions, 2395 translation units, `ltcg_clusters` 260 → 259 (one removed, none
added; the region merged into the existing camera layout). `load_clusters` accepts
all 259 layouts. The recovered-byte ledger moves exactly by the region:
`semantic` 39112 → 39399 (**+287**), `asm` 349916 → 349629 (**−287**), `data` and
`padding` unchanged.

## The source

```cpp
// 0x00421480: construct a centered perspective view from the viewport dimensions.
//
// The viewport's width and height are converted once, kept in memory, and the
// ratio is materialised at the definition because the camera's perspective
// matrix reads it after the view matrix call.  `*(volatile float*)&aspect` is a
// measured code-generation lever, not recovered style: it is the only spelling
// that makes the /O2 generator store the quotient where retail stores it
// instead of keeping it in an x87 register to the call.
#include "th10/render/camera_batch.hpp"
#include <math.h>
extern "C" const double data_00470ba0;
#pragma code_seg(".text$00adefault")
void RenderCamera::ApplyDefault() {
    if (data_00491c10) data_00491c10->Flush();
    float viewport_width = (float)width;
    float half_width = viewport_width * 0.5f;
    float viewport_height = (float)height;
    float half_height = viewport_height * 0.5f;
    float aspect;
    *(volatile float*)&aspect = viewport_width / viewport_height;
    CameraVector view_up, target, eye;
    eye.x = half_width; eye.y = half_height; eye.z = half_height / (float)tan(data_00470ba0);
    target.x = half_width; target.y = half_height; target.z = 0.0f;
    view_up.x = 0.0f; view_up.y = -1.0f; view_up.z = 0.0f;
    CameraLookAt(&view, &eye, &target, &view_up);
    CameraPerspective(&projection, 0.31415927f, aspect, 1.0f, 10000.0f);
    typedef long (__stdcall *SetTransform)(void*, unsigned int, const CameraMatrix*);
    RenderDevice* device = data_00491c30;
    ((SetTransform)device->vtable[0xB0 / 4])(device, 2, &view);
    device = data_00491c30;
    ((SetTransform)device->vtable[0xB0 / 4])(device, 3, &projection);
    if (data_00491c10) {
        ((int*)data_00491c10)[0x5C / 4] = clip_x;
        ((int*)data_00491c10)[0x60 / 4] = clip_y;
    }
}
#pragma code_seg()
```

`include/th10/render/camera_batch.hpp` gains the model's declaration (the body
adds no data, so no other member offset moves):

```cpp
    __declspec(noinline) void Apply();          // existing
    __declspec(noinline) void ApplyDefault();   // added
```

## The two levers, measured

Wave 9 left the body 4 bytes off: `fst` + a dead `fstp [esp+0x18]` where retail
has one popping `fstp [esp+0x1c]`, plus `fld st(0)` + `fdivp st(1),st` where
retail has `fdivr st,st(1)`. Both are x87 register-plan decisions, and both are
source-spelling-dependent; the plain `/O2` translation unit proxy (`0.4 s`, no
`/GL`) reproduces the cluster's decisions on every shape below, so ~250 further
shapes were searched through it.

**1. The quotient must have exactly one destination, and the call must read it as
a plain lvalue.** Wave 9's `volatile float aspect = W / H;` *plus* the argument
re-dividing `W / H` gives the CSE'd quotient two memory homes (the volatile's and
the argument's), so MSVC emits `fst` (keep) + a dead `fstp`. Making the argument
read the variable instead removes the second home but makes it a *volatile* read
(`fld [slot]; fstp [esp]`, frame `0x28`, and `viewport_width` back in an x87
register, so the frame loses its slot). The shape that fixes both at once stores
through an address the compiler cannot scalarise — `*(volatile float*)&aspect =
W / H;` — and then reads the plain variable at the call. The division is
materialised at the definition (retail's position), the store is a single
`fstp [esp+0x1c]`, the argument is `mov edx,[esp+0x1c]; push edx`, and because
the quotient is now written far from the conversions, `viewport_width` and
`viewport_height` keep retail's memory homes (`fst [esp+0x8]`, `fst [esp+0xc]`,
`fld [esp+0xc]`, `fdiv [esp+0x10]`).

**2. The eye.z division must be float/float.** `half_height / tan(data_00470ba0)`
leaves the divisor a `double`, and the generator duplicates the dividend to keep
one copy across the widening (`fld st(0)` + `fdivp st(1),st`, +2 bytes).
`half_height / (float)tan(data_00470ba0)` — the *inner* cast only; an outer
`(float)(...)` cast changes nothing — emits retail's `fld QWORD PTR
ds:0x470ba0 / fptan / fstp st(0) / fdivr st,st(1)`.

Each lever alone is necessary:

| eye.z expression (aspect block fixed) | x87 instructions |
| --- | ---: |
| `half_height / tan(data_00470ba0)` | 23 |
| `half_height / (float)tan(data_00470ba0)` | **22 (retail)** |
| `(float)(half_height / (float)tan(data_00470ba0))` | **22 (retail)** |
| `(float)(half_height / tan(data_00470ba0))` | 23 |

| aspect spelling | emitted | frame | x87 | what broke |
| --- | ---: | --- | ---: | --- |
| `volatile float aspect`, call re-divides (wave 9) | 293 | `0x2c` | 24 | two quotient homes: `fst` + dead `fstp` |
| `volatile float aspect`, call reads the variable | 288 | `0x28` | 25 | quotient in an x87 register, `W` loses its slot, x87 argument read |
| **`*(volatile float*)&aspect = W / H;`, call reads the variable** | **287** | **`0x2c`** | **22** | — |
| same, call re-divides (CSE) | 293 | `0x2c` | 24 | two quotient homes again |

The search also re-confirmed the wave-9 negative results: unnamed conversions
(`(float)width * 0.5f`, `(float)width / (float)height`) put the multiplicand back
in a register (`x87` 23-24, frames `0x28`/`0x2c`), plain/`const`/reference aspect
spellings leave the division deferred to the argument, and construction through
`CameraVector` constructors or moved statements reorders the four immediate
stores off retail's order.

## The layout delta

`layout/ltcg/anm_batch_flush_00442f50.json` grew by two functions; the render
functions landed in waves 5-9 are untouched (all 20 verified EXACT above).

```json
{"name": "RenderCamera_ApplyDefault", "symbol": "?ApplyDefault@RenderCamera@@QAEXXZ",
 "section": ".text$00adefault", "address": "0x00421480", "size": 287,
 "actual_abi": "EDI camera; plain RET", "source": "src/render/camera_setup.cpp"}
{"name": "RenderStageState_00405300_SelectDefaultStage",
 "symbol": "?SelectDefaultStage@RenderStageState_00405300@@QAEXH@Z",
 "section": ".text$000zselect", "address": "0x00405300", "size": 60,
 "actual_abi": "state in ESI; index in EBX; plain RET",
 "source": "src/game/fun_00405300_00405300.cpp"}
```

Gaps: the leading span `0x00401D5C + 129092` is split by the two new functions
(the split names come from `promote_scratch.merge_layout`, and each sorts between
the function it follows and the next section):

```json
{"section": ".text$000zlayout",   "address": "0x00401D5C", "size": 13732}   // ends 0x405300
{"section": ".text$000zselectz",  "address": "0x0040533C", "size": 115012}  // ends 0x421480
{"section": ".text$00adefaultz",  "address": "0x0042159F", "size": 1}       // ends 0x4215A0
```

Two corrections the function merge cannot express:

* the `.rdata` layout gap (`0x00446000 + 175000`) is replaced by the region's two
  `constant_aliases`. The region adds a pooled literal (`0.5f`) to the cluster and
  moves the compiler pool, so `__real@4f800000` is no longer at the gap's end;
  both of the region's pool references are rebound to retail's own addresses
  instead. No other function in this cluster references a pooled literal at all —
  that is why the gap could go, and all 18 pre-existing bodies stayed EXACT.

```json
"constants": [],
"constant_aliases": [{"symbol": "__real@3f000000", "address": "0x00470B0C", "value": 0.5},
                     {"symbol": "__real@4f800000", "address": "0x00470B98", "value": 4294967296.0}]
```

* the context's emitted extent grows 308 → 321 bytes, because the synthetic
  caller now also calls the two new functions:

```json
"context": {"symbol": "?RenderBatchContext@@YGHPAPBUScreenRect@@PBIHPAPBURenderEntity@@PAPBXPAPAURenderCamera@@@Z",
            "section": ".text$07context", "address": "0x00445200", "size": 321, ...}
```

`additional_sources` gains `src/game/fun_00405300_00405300.cpp` and
`src/render/camera_setup.cpp`; `absolute_symbols` gains `_data_00470ba0`.
`roots` is unchanged: rooting either new function would pin its declared
`__thiscall` ABI and bring the receiver back in ECX, so both are kept alive by a
call from the context instead.

## The driver

`layout/ltcg/render_batch_context.cpp`, the only edits being the two calls that
keep the new bodies and the declaration of 0x00405300's state type:

```cpp
// Compiler context only; no context bytes count as recovered code.
#include "../../src/render/texture_stage_reset.cpp"
#include "th10/render/camera_batch.hpp"

// The state object the ECL thread hands to SelectStage in ESI. Declared rather
// than included: the model is a separate additional_source translation unit.
struct RenderStageState {
    unsigned char reserved_000[0x388];
    __declspec(noinline) void SelectStage(int index);
};
extern "C" RenderStageState data_00491c28;

// 0x00405300's body is the modelled member of the recovered source; declared
// here so this context keeps it alive without pinning its declared __thiscall
// ABI through `roots`, exactly as 0x00401D20 is kept alive by the call below.
struct RenderStageState_00405300 {
    unsigned char reserved_000[0x388];
    __declspec(noinline) void SelectDefaultStage(int index);
};

#pragma code_seg(".text$07context")
int __stdcall RenderBatchContext(const ScreenRect** rects, const unsigned int* colors, int count,
                                  const RenderEntity** entities, const void** vertices, RenderCamera** cameras) {
    for (int i = 0; i < count; ++i) {
        DrawGradientQuad(rects[i], colors[4*i], colors[4*i+1], colors[4*i+2], colors[4*i+3]);
        data_00491c10->DrawStrip(entities[i], vertices[i], colors[i]);
        data_00491c10->DrawQuad(entities[i], (const TexturedVertex*)vertices[i]);
        data_00491c10->DrawFan(entities[i], vertices[i], colors[i]);
        data_00491c10->DrawSolidStrip(entities[i], vertices[i], colors[i]);
        data_00491c10->DrawSolidFan(entities[i], vertices[i], colors[i]);
        data_00491c10->SubmitSpriteQuad(entities[i], colors[i]);
        data_00491c10->SubmitSpriteQuadMirrored(entities[i], colors[i]);
        cameras[i]->Apply();
        cameras[i]->ApplyDefault();
    }
    data_00491c28.SelectStage(0);
    ((RenderStageState_00405300*)&data_00491c28)->SelectDefaultStage(0);
    return count;
}
#pragma code_seg()
```

## 0x00405300, without its anchor

`layout/ltcg/render_stage_select_00405300.json` and its driver are deleted and the
layout is unregistered; the region record is unchanged (`semantic`,
`src/game/fun_00405300_00405300.cpp`, 60 bytes) because the region keeps its
source, its symbol and its extent - only its cluster changes. Its source now
calls the modelled member and carries the camera cluster's section tag:

```cpp
#pragma code_seg(".text$000zselect")
void RenderStageState_00405300::SelectDefaultStage(int index) {
    active_stage = &stages[index];
    active_stage->camera.ApplyDefault();
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = index;
}
#pragma code_seg()
```

Its bytes are retail's, including the call whose displacement the layout bakes:

```text
8b c3 69 c0 18 01 00 00 57 8d bc 30 54 01 00 00 89 be 84 03 00 00 e8 65 c1 01 00
8b 96 84 03 00 00 8b 46 08 8b 08 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00 89 9e
88 03 00 00 5f c3
```

so the hand-written anchor body, the `_entry_free_004524a1` binding that existed
only to shape it, and the cluster are all gone. The `anchors` mechanism itself is
untouched and still used by `score_records_advance_frame_0041c480.json`.

## Regions this landing unblocks

`0x00421480` has six call sites in the image; `render_stage_select_00405300_wave4.md`
records that all of them load the record into **EDI** before the call (this
landing re-measured only the first row):

| call site | region | state |
| --- | --- | --- |
| `0x00405316` | `0x00405300` `RenderStageState_00405300::SelectDefaultStage` | landed here without an anchor |
| `0x004393FF` | `0x00439390` (`src/platform/fun_00439390_00439390.cpp`) | assembly |
| `0x0044862F` | `0x00448620` (`src/unidentified/FUN_00448620_00448620.cpp`) | assembly |
| `0x0044877F` | `0x00448770` (`src/unidentified/FUN_00448770_00448770.cpp`) | assembly |
| `0x004487CF` | `0x004487C0` (`src/unidentified/FUN_004487c0_004487c0.cpp`) | assembly |
| `0x0044881F` | `0x00448810` (`src/unidentified/FUN_00448810_00448810.cpp`) | assembly |

Those five no longer need a stand-in: each can join the camera cluster the way
`0x00405300` just did - add its source to `additional_sources`, add its function
entry, and call the modelled member - because the callee's body is now compiled
in that link, which is the only thing that earns EDI.

## Files

```text
13d09685f1e25edb68e6e63f91be37a2a18df54c3b3c553228042624a8f40707  src/render/camera_setup.cpp
73aa1fc8e211aef69c448fa0b366e959e78ce42f682ceb8de322bf4f1f2ea21a  src/game/fun_00405300_00405300.cpp
997b65d789867d1953c5a99898f41a9b6f699dcf9eac0c2298e65a8640d1db5f  layout/ltcg/anm_batch_flush_00442f50.json
3612d2bd8e01ac29bf529c1f098252a8db8c15056770fa683a8a4b44fabc7dd0  layout/ltcg/render_batch_context.cpp
a2b824cd15ee5db297e45a6a75dd04dff4c108679cba03a7d3c644a6a7729706  include/th10/render/camera_batch.hpp
fef0883a23f69884f8eba92502a40dff93c677171e7bcc0762c20d9503c983c5  matching2/build/waves/results10/CameraApply/apply_package.py
```

deleted:

```text
layout/ltcg/render_stage_select_00405300.json
layout/ltcg/render_stage_select_00405300_context.cpp
```

The package (payload sources, `apply_package.py`, `probe.txt`, `bytes.txt`,
`summary.json`, and the landed layout/driver under `staged/`) is
`matching2/build/waves/results10/CameraApply/`. `apply_package.py` re-reads the
maintained layout and unions the functions through
`matching2.tools.waves.promote_scratch.merge_layout` inside the manifest lock, so
a sibling landing into the same span is carried over rather than reverted.
