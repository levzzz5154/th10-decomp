# 0x00405300 — `RenderStageState_00405300::SelectDefaultStage`, EXACT with one loader allowance

2026-09-19. Region `0x00405300` (60 bytes, `asm_FUN_00405300_00405300`,
`src/game/fun_00405300_00405300.cpp`) is modelled as the render-stage selector
that reapplies the **default** camera. The emitted body is **byte-identical to
retail (60/60, 0 differing bytes)** and the maintained probe prints `EXACT`,
but only after the two-line `scaffolding` allowance in
`matching2/tools/matching/ltcg_cluster.py` that
`animation_manager_clear_resource_slot_004477d0_cluster.md` already recommended:
the cluster needs two support functions (the compiler context and the ABI anchor
for the callee), and the loader currently admits only the context.

This region is the **twin of the already landed `0x00401D20`**
(`RenderStageState::SelectStage`, `render_stage_select_00401d20_wave4.md`): same
60-byte shape, same state object, same `+0x384`/`+0x388` fields, same ESI/EBX
entry registers, same EDI local — the only difference is the callee: this one
calls `0x00421480` (the default camera set-up) where `0x00401D20` calls
`0x004215A0` (`RenderCamera::Apply`). `0x00401D20` landed by merging into
`anm_batch_flush_00442f50`, whose link already contains `RenderCamera::Apply`;
`0x00421480` is *not* modelled, which is why this region needs the anchor.

## The region

```asm
405300: 8b c3                 mov    %ebx,%eax
405302: 69 c0 18 01 00 00     imul   $0x118,%eax,%eax
405308: 57                    push   %edi
405309: 8d bc 30 54 01 00 00  lea    0x154(%eax,%esi,1),%edi
405310: 89 be 84 03 00 00     mov    %edi,0x384(%esi)
405316: e8 65 c1 01 00        call   0x421480
40531b: 8b 96 84 03 00 00     mov    0x384(%esi),%edx
405321: 8b 46 08              mov    0x8(%esi),%eax
405324: 8b 08                 mov    (%eax),%ecx
405326: 81 c2 cc 00 00 00     add    $0xcc,%edx
40532c: 52                    push   %edx
40532d: 50                    push   %eax
40532e: ff 91 bc 00 00 00     call   *0xbc(%ecx)
405334: 89 9e 88 03 00 00     mov    %ebx,0x388(%esi)
40533a: 5f                    pop    %edi
40533b: c3                    ret
```

`ESI` is the game-wide state object (`0x00491C28`), `EBX` the stage index, `EDI`
a callee-saved local holding the selected 0x118-byte stage record. `0x00421480`
reads its record from **EDI**; the record's `+0xCC` block goes to the device
vtable slot `0xBC` (the `RenderDevice::Viewport` helper of `quad_batch.hpp`).

Corroboration of the object shape is the landed twin: `0x00401D20` uses the same
`ESI` object, the same `+0x154` record array with the same `0x118` stride, the
same `+0x384`/`+0x388` fields and the same `+0x08` device pointer, and its
source (`src/render/render_stage_select.cpp`) is the template this model
follows.

## Recovered source (`src/game/fun_00405300_00405300.cpp`)

```cpp
// 0x00405300 - Select the active render stage and reapply the *default* camera:
// point the state's active stage at the indexed 0x118-byte stage record, hand
// that record to the camera-default routine at 0x00421480, give its viewport
// block to the render device and publish the index.
//
// Retail reaches the body with the state object in ESI and the index in EBX -
// the only call site (0x00402AEC, the game thread) loads the state's address
// 0x00491C28 into ESI and zeroes EBX - and 0x00421480 reads its record from
// EDI. Those are whole-program register choices, so the body is compiled
// through the native-LTCG cluster
// layout/ltcg/render_stage_select_00405300.json.
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera the default setup rewrites followed by
// the fields that make the record the 0x118 bytes the index stride shows. The
// camera sits at offset 0, so the viewport block the device receives is the
// record's +0xCC.
struct RenderStage_00405300 {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide state object at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 and the active index at +0x388.
struct RenderStageState_00405300 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                        // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage_00405300 stages[2];              // +0x154, stride 0x118
    RenderStage_00405300* active_stage;          // +0x384
    int stage_index;                             // +0x388

    __declspec(noinline) void SelectDefaultStage(int index);
};

// 0x00421480. Its record arrives in EDI, which no declaration names; the
// cluster's driver carries the ABI anchor for it. The symbol is the maintained
// assembly region, so nothing about it is invented.
extern "C" void __cdecl asm_Camera_ApplyRetail_00421480(RenderCamera* camera);

#pragma code_seg(".text$01select")
void RenderStageState_00405300::SelectDefaultStage(int index) {
    active_stage = &stages[index];
    asm_Camera_ApplyRetail_00421480(&active_stage->camera);
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = index;
}
#pragma code_seg()
```

The type names carry the region's address because the shared type is not public
yet; when `0x00421480` lands the source loses only the `asm_…` declaration (the
call becomes a `RenderCamera::ApplyDefault()` member, the name
`render_stage_select.cpp` already uses for the family).

`device->Viewport(...)` is the inline helper of `quad_batch.hpp`, i.e. the same
`((Call)vtable[0xBC/4])(this, viewport)` shape `camera_apply.cpp` and the landed
twin use. It emits the pushed device / `%ecx` = vtable / `call *0xbc(%ecx)`
triple unchanged.

## Driver (`layout/ltcg/render_stage_select_00405300_context.cpp`)

```cpp
// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/game/fun_00405300_00405300.cpp"

extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x00421480 takes its camera record in EDI - all six retail call sites set it -
// and no declaration can name that register. Only a native /LTCG link can, and
// only for a callee whose body it can see, so the driver carries this anchor
// body. Its shape is the one measured to earn EDI: the record stays live across
// a loop that calls out (the same rule the 0x004477D0 note records); a body
// without such a loop put the record in ESI, EBX or EAX instead. The layout's
// gaps place the section at the retail address, so the region's own call bakes
// retail's displacement. None of these bytes are selected as recovered code.
#pragma code_seg(".text$03camera")
extern "C" __declspec(noinline) void __cdecl asm_Camera_ApplyRetail_00421480(RenderCamera* camera) {
    unsigned int* words = (unsigned int*)camera;
    for (int word = 0; word < 0x118 / 4; word += 4) {
        entry_free_004524a1((void*)words[word]);
    }
    words[0] = 0;
}
#pragma code_seg()

// Synthetic caller: it materialises the state object's link-time address and a
// literal index, exactly the `mov esi,0x491c28 / xor ebx,ebx` pair retail's only
// call site at 0x00402AEC uses, which is what makes the whole-program pass give
// the region ESI for the state and EBX for the index.
extern "C" RenderStageState_00405300 data_00491c28;

#pragma code_seg(".text$05context")
int __stdcall RenderStageSelectCompilerContext(int count) {
    while (count--) {
        data_00491c28.SelectDefaultStage(0);
    }
    return count;
}
#pragma code_seg()
```

The anchor's own emitted body reads its record from **EDI**
(`mov eax,[edi+esi*4]`, `mov [edi],0`), and with this anchor shape the region's
record lands in EDI and the state in ESI (measured; other anchor shapes move the
record to ESI/EBX/EAX, see *Shapes tried*). Its symbol is the maintained assembly
symbol `_asm_Camera_ApplyRetail_00421480`, laid out at the retail address by the
layout gaps, so the region's `call` bakes retail's `e8 65 c1 01 00` with no
binding and no byte patched. `export_bodies` writes only `functions`, so no
anchor byte reaches the image.

## Layout (`layout/ltcg/render_stage_select_00405300.json`)

```json
{
  "schema_version": 1,
  "name": "render_stage_select_00405300",
  "source": "src/game/fun_00405300_00405300.cpp",
  "driver": "layout/ltcg/render_stage_select_00405300_context.cpp",
  "headers": [
    "include/th10/render/quad_batch.hpp",
    "include/th10/render/camera_batch.hpp"
  ],
  "image_base": "0x00400000",
  "description": "RenderStageState_00405300::SelectDefaultStage compiled with native LTCG so the state arrives in ESI, the index in EBX and the camera-default call in EDI. The .text$03camera section is an ABI anchor for the assembly region at 0x00421480 whose bytes are never selected; it is declared through the layout's scaffolding list.",
  "functions": [
    {
      "name": "RenderStageState_00405300_SelectDefaultStage",
      "symbol": "?SelectDefaultStage@RenderStageState_00405300@@QAEXH@Z",
      "section": ".text$01select",
      "address": "0x00405300",
      "size": 60,
      "actual_abi": "state in ESI; index in EBX; plain RET"
    }
  ],
  "context": {
    "symbol": "?RenderStageSelectCompilerContext@@YGHH@Z",
    "section": ".text$05context",
    "address": "0x004214F0",
    "size": 48,
    "description": "Synthetic caller that materialises the state object's link-time address and a literal index, the shape retail's only call site at 0x00402AEC uses; not recovered game code."
  },
  "gaps": [
    { "section": ".text$00layout", "address": "0x00401000", "size": 17152 },
    { "section": ".text$02layout", "address": "0x0040533C", "size": 115012 },
    { "section": ".text$04layout", "address": "0x0042149F", "size": 81 }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    { "symbol": "_entry_free_004524a1", "address": "0x004524A1", "kind": "relative_code" },
    { "symbol": "_data_00491c28", "address": "0x00491C28", "kind": "data" }
  ],
  "scaffolding": ["_asm_Camera_ApplyRetail_00421480"]
}
```

Section order matters and is what places every piece: `.text$00layout`
(0x00401000) < `.text$01select` (0x00405300, 60) < `.text$02layout` (0x0040533C,
115012) < `.text$03camera` (the anchor, 0x00421480, 31 bytes) < `.text$04layout`
(0x0042149F, 81) < `.text$05context` (0x004214F0, 48). The anchor's `code_seg`
tag must sort after the gap that reaches 0x00421480 and before the gap that
follows it. The link map reads:

```
0001:00004300       ?SelectDefaultStage@RenderStageState_00405300@@QAEXH@Z 00405300 f   cluster.obj
0001:00020480       _asm_Camera_ApplyRetail_00421480 00421480 f   cluster.obj
0001:000204f0       ?RenderStageSelectCompilerContext@@YGHH@Z 004214f0 f   cluster.obj
```

## The loader allowance (the only blocker)

A native /LTCG link assigns a private register convention only to functions whose
IL it can see, and **no declaration names EDI**: `__fastcall` gives ECX/EDX,
`__thiscall` ECX, `/Gz` stdcall puts arguments on the stack, and an external
symbol that is bound absolutely (declaration only, no IL) is always compiled with
its declared convention. Measured here: with the callee declared and bound
absolutely but **not defined** in the cluster, the body is 62 bytes with the
record in EAX, the index in EDI and the argument **pushed** — the full delta is
below. The region can therefore only be reproduced by a callee whose body is in
the same link, and `validate_native_output` fences that link to the selected
functions plus the compiler context:

```python
declared = {item['symbol'] for item in spec['functions']}
if spec['context']:
    context_symbol = spec['context']['symbol']
    declared |= {context_symbol, '_' + context_symbol}
if any('f' in symbol.flags and symbol.segment and symbol.name not in declared for symbol in link_map.symbols):
    raise LTCGClusterError('native compiler emitted an undeclared function')
```

The two-line allowance (already recommended by the 0x004477D0 note, which needed
the same function and instead recovered its callee) is exactly:

```python
# load_cluster(): admit the declared anchor symbols
    allowed = required | {'additional_sources', 'roots', 'constant_aliases', 'data_aliases',
                          'scaffolding'}

# validate_native_output(): the layout, not the name fence, declares the anchor
        declared |= {str(item) for item in spec.get('scaffolding', [])}
```

With that allowance the maintained probe reports, in the sandbox copy
(`/tmp/RenderStageLeaf`, tools copied to `/tmp/RenderStageLeaf/matching2/tools`
and patched with those two lines):

```
$ python3 matching2/tools/matching/probe.py --source src/game/fun_00405300_00405300.cpp \
      --project /tmp/RenderStageLeaf/msvc --output /tmp/RenderStageLeaf/out4 --show 30
0x00405300      60 bytes  ?SelectDefaultStage@RenderStageState_00405300@@QAEXH@Z  EXACT
EXACT
```

Against the unpatched loader the same layout is refused, before anything is
built or written:

```
$ python3 matching2/tools/waves/register_cluster.py --project /tmp/RenderStageLeaf/msvc \
      --layout layout/ltcg/render_stage_select_00405300.json --apply
refused: layout rejected by the loader: cluster manifest has missing or unknown fields
```

Dropping the `scaffolding` line and re-probing with the maintained tools (so the
loader accepts the layout) shows the anchor is then the only difference left —
the same failure the 0x004477D0 note recorded:

```
$ python3 matching2/tools/matching/probe.py --source src/game/fun_00405300_00405300.cpp \
      --project /tmp/RenderStageLeaf/msvc --output /tmp/RenderStageLeaf/out9 --show 30
src/game/fun_00405300_00405300.cpp: FAILED TO COMPILE
native compiler emitted an undeclared function
NOT EXACT
```

## Shapes tried

Every row is a measured cluster build (native /LTCG, wine MSVC 13.10.6030); the
region bytes are read out of the link's PE at 0x00405300.

| shape | emitted | differing | entry registers reached |
| --- | ---: | ---: | --- |
| declaration only, callee bound absolutely at 0x00421480 (no IL) | 62 | 31 | state ESI, index **EDI**, record EAX; argument pushed, `add esp,4`; no EDI save |
| anchor: two summing loops, no call | 60 | 8 | state **EDI**, index EBX, record **ESI** (state and record swap) |
| anchor: summing loops plus a call-bearing loop and more pressure | 60 | 6 | state ESI, index **EDI**, record **EBX** |
| anchor: `CameraLookAt` loop (record live across a call, but the pass still picked a caller-saved register) | 58 | — | state ESI, index **EDI**, record EAX, no EDI save at all |
| anchor: loop calling out with the record **live across the calls** (adopted) | **60** | **0** | state ESI, index EBX, record EDI |
| adopted anchor, context swept (array walk, `hosts[index]`, pointer walk `*hosts++`, global state with literal 0, literal/loop index) | 60 | 0 with the adopted anchor | unchanged — the anchor's body, not the caller's shape, fixes the convention |

The anchor's parameter register is a joint choice of the anchor's body and the
caller's state - rows 2-4 show it moving to ESI, EBX and EAX for other bodies -
so the merge option below has to re-measure it once `0x00421480` is modelled.

The declaration-only row in full (`got` then retail; the last two retail bytes
are padding):

```
got : 8b c7 69 c0 18 01 00 00 8d 84 30 54 01 00 00 50 89 86 84 03 00 00 e8 65 c1 01 00
      8b 96 84 03 00 00 8b 46 08 8b 08 83 c4 04 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00
      89 be 88 03 00 00 c3
want: 8b c3 69 c0 18 01 00 00 57 8d bc 30 54 01 00 00 89 be 84 03 00 00 e8 65 c1 01 00
      8b 96 84 03 00 00 8b 46 08 8b 08 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00
      89 9e 88 03 00 00 5f c3
```

i.e. the declaration-only body has four instruction-level differences (31
differing bytes): the index is EDI
(`8b c7`) instead of EBX (`8b c3`); there is no `push edi`/`pop edi` because
nothing is live across the call; the record is computed into and stored from EAX
(`8d 84 …` / `89 86 …`) instead of EDI (`8d bc …` / `89 be …`); and the cdecl
argument costs `50` + `83 c4 04` (net +2 bytes, 62 emitted); `mov [esi+0x388]`
stores EDI instead of EBX.

## The caller's registers, and what the emitted body keeps

The region has exactly one call site in the whole image, `0x00402AEC` inside
`0x00402850` (`src/game/game_state.cpp`, still assembly):

```asm
402ae5: 33 db           xor    %ebx,%ebx        ; stage index := 0  -> EBX
402ae7: be 28 1c 49 00  mov    $0x491c28,%esi  ; state object      -> ESI
402aec: e8 0f 28 00 00  call   0x405300
402af1: 8b fe           mov    %esi,%edi        ; caller reloads EDI right after
```

so retail supplies the state in **ESI**, the index in **EBX** and nothing on the
stack, and the callee's only obligation is to preserve EDI. The five other
callers of `0x00421480` (`0x004393FF`, `0x0044862F`, `0x0044877F`, `0x004487CF`,
`0x0044881F`) are the same family — they all load the record into EDI
immediately before the `call`, which is the evidence that the register belongs to
the callee, not to this region.

The emitted body keeps all three: `ESI` is the state (read, never written),
`EBX` is the index (read, never written), `EDI` is the record (`push %edi` at
0x00405308, `pop %edi` at 0x0040533A) and the record is already in EDI at the
call, exactly as retail has it. The emitted 60 bytes and the retail 60 bytes are
equal including the baked `e8 65 c1 01 00`:

```
actual:   8b c3 69 c0 18 01 00 00 57 8d bc 30 54 01 00 00 89 be 84 03 00 00 e8 65 c1 01 00
          8b 96 84 03 00 00 8b 46 08 8b 08 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00
          89 9e 88 03 00 00 5f c3
expected: 8b c3 69 c0 18 01 00 00 57 8d bc 30 54 01 00 00 89 be 84 03 00 00 e8 65 c1 01 00
          8b 96 84 03 00 00 8b 46 08 8b 08 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00
          89 9e 88 03 00 00 5f c3
different_bytes: 0
```

Re-probed twice from fresh build directories: identical, `EXACT`.

## Integration options

1. **Adopt the allowance** (`scaffolding`, two lines) and register
   `layout/ltcg/render_stage_select_00405300.json`. It is a standalone cluster
   with its own driver, so no landed cluster is touched: `register_cluster.py
   --apply` maps the region to `?SelectDefaultStage@RenderStageState_00405300@@QAEXH@Z`
   and adds the layout to `ltcg_clusters`; the manifest's `symbols` entry
   `_asm_FUN_00405300_00405300` stays, so the asm caller at 0x00402AEC keeps
   resolving. `roots` must stay empty — the twin's landing measured that rooting
   the function pins its declared `__thiscall` ABI and brings the state back in
   ECX.
2. **Recover `0x00421480` first** (287 bytes; the camera-lab models in
   `matching2/build/recovery-lab/prepare_camera_default.py` reached 291/292 with
   the correct 44-byte frame) and then land this region the way `0x00401D20`
   landed: as an `additional_sources` / one more `functions` entry in the camera
   cluster (`anm_batch_flush_00442f50`, or wherever `0x00421480` ends up). The
   driver's anchor then disappears and the source's callee becomes the modelled
   member. Nothing else in this model changes.

The maintained tree was not touched except for this note; every artifact below
lives in `/tmp/RenderStageLeaf/msvc`.

## Artifacts

* `src/game/fun_00405300_00405300.cpp`
  sha256 `8945bff799acd508534bcc1d5ba103cc2a7cd23cd0dc05366937d03a5126343b`
* `layout/ltcg/render_stage_select_00405300_context.cpp`
  sha256 `c63b20e2492d572968b8c6062b83173d9c89af8485851c74f234d54c8e478b14`
* `layout/ltcg/render_stage_select_00405300.json`
  sha256 `e91e55e4636f5729386ef5e5e26279370df590a5c053800d55cc96f347fc9345`
* driver script and byte comparison: `/tmp/RenderStageLeaf/verify.py`
  (`python3 verify.py landed` prints the emitted and retail bytes)
* patched tools copy for the probe: `/tmp/RenderStageLeaf/matching2/tools`
  (two lines added to `ltcg_cluster.py`, diff in *The loader allowance* above)
