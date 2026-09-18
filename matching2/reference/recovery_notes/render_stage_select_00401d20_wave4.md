# 0x00401D20 (`RenderStageState::SelectStage`) — EXACT through a merged native-LTCG cluster

2026-09-19. Region `0x00401D20` (60 bytes, `asm_GameThread_SelectRenderStageRetail_00401d20`,
`src/render/render_stage_select.cpp`) is recovered as
`RenderStageState::SelectStage(int)` and probes **EXACT** (0 differing bytes,
`60 bytes` emitted). It calls the already landed `0x004215A0`
(`RenderCamera::Apply`, `src/render/camera_apply.cpp`), so the two regions now
share one cluster: `layout/ltcg/anm_batch_flush_00442f50.json`. All 18 functions
that cluster already owned still probe **EXACT** after the merge (measured, see
below), so no landed region is disturbed.

## The region

```asm
401d20: 8b c3                 mov    %ebx,%eax
401d22: 69 c0 18 01 00 00     imul   $0x118,%eax,%eax
401d28: 57                    push   %edi
401d29: 8d bc 30 54 01 00 00  lea    0x154(%eax,%esi,1),%edi
401d30: 89 be 84 03 00 00     mov    %edi,0x384(%esi)
401d36: e8 65 f8 01 00        call   0x4215a0
401d3b: 8b 96 84 03 00 00     mov    0x384(%esi),%edx
401d41: 8b 46 08              mov    0x8(%esi),%eax
401d44: 8b 08                 mov    (%eax),%ecx
401d46: 81 c2 cc 00 00 00     add    $0xcc,%edx
401d4c: 52                    push   %edx
401d4d: 50                    push   %eax
401d4e: ff 91 bc 00 00 00     call   *0xbc(%ecx)
401d54: 89 9e 88 03 00 00     mov    %ebx,0x388(%esi)
401d5a: 5f                    pop    %edi
401d5b: c3                    ret
```

`ESI` is the game-wide state object whose address the caller materialises
(`0x00491C28`), `EBX` the stage index, and `EDI` a callee-saved local that holds
the selected record and is the register `RenderCamera::Apply` reads its camera
from. No stack argument, plain `RET` — a private `/GL` convention, not a
declared one.

## What the object is, and the corroboration

The four offsets are fixed by three already-recovered neighbours:

* `0x00401A50` (region `asm_FUN_00401a50_00401a50`) contains the **same
  sequence twice, inlined**, on the same fields by absolute address:
  `mov edi,491D7Ch / mov [data_00491fac],edi / call 0x004215a0 /
  mov edx,[data_00491fac] / mov eax,[data_00491c30] / mov ecx,[eax] /
  add edx,0CCh / push edx / push eax / call [ecx+0BCh] /
  mov [data_00491fb0],0`, then the identical block with `491E94h` and index `1`.
  `0x00491D7C = 0x00491C28 + 0x154` and `0x00491E94 = 0x00491D7C + 0x118`, so
  `ESI + 0x154` is the stage-record array, `0x118` its stride, `ESI + 0x384`
  the active stage (`0x00491FAC`) and `ESI + 0x388` the active index
  (`0x00491FB0`) — the exact fields the asm listing reaches through `ESI`.
* `0x00491C30` is the render device pointer the landed `camera_apply.cpp`
  declares (`extern "C" RenderDevice* data_00491c30;`), i.e. `ESI + 0x08` here;
  the call is the `RenderDevice::Viewport` helper of `quad_batch.hpp`
  (`vtable[0xBC/4]`, `this` pushed, viewport pushed) at the `+0xCC` block that
  `DeviceViewport`/`RenderTargetViewport` place there.
* `0x00405300` is a byte-for-byte twin of this region that calls `0x00421480`
  instead of `0x004215A0`, and `src/game/set_input_mode_0040ac90.cpp` records
  the same global (`0x00491C28`) as "the object retail callers push", so the
  receiver convention is the family's, not this region's invention.

`0x4215A0` is `RenderCamera::Apply`, and the record layout the index stride
implies is `RenderCamera` (0xF0 as declared in `camera_batch.hpp`) followed by
0x28 unmodelled bytes; the camera sits at offset 0, which is why the selected
record is exactly the pointer `Apply` receives in EDI and exactly the pointer
the `+0xCC` viewport block belongs to.

## Why the plain path and a fresh cluster both fail, and why the merge

Plain `/O2`: the state pointer and the index arrive on the stack, and the call
to `0x4215A0` is emitted as `mov ecx,...` (`this` in ECX) — no MSVC declaration
places an argument in EDI, and neither ESI nor EBX is a declared receiver
register. The private ABI only exists in a `/LTCG` link in which **both sides of
the private call are visible** (`whole_program_ltcg.md`), and the callee here is
already owned: `src/render/camera_apply.cpp` is an `additional_sources` entry of
`anm_batch_flush_00442f50`, so a second cluster claiming it is rejected
(`clusters must have distinct maintained sources`). The existing cluster
therefore grew:

* the region's own source joins as an `additional_sources` entry,
* one more entry in `functions` (each function carries its own `source`),
* `_data_00491c28` added to `absolute_symbols`,
* the first layout gap `0x00401000..0x004215A0` split around the new function —
  the new function's `code_seg` tag must sort *after* the shortened gap and
  *before* the gap that follows it, because cluster sections are placed in name
  order: `.text$000layout` < `.text$000pgselect` < `.text$000zlayout` <
  `.text$00bcamera` (the last is `camera_apply.cpp`'s section, which must keep
  landing at `0x004215A0`),
* the driver's synthetic caller extended with the one call that establishes the
  convention. Its emitted extent grew 294 → 308 bytes, which is the only layout
  correction this landing needed (the first build failed with
  `function is not its entire declared compiler contribution:
  ?RenderBatchContext...`).

`ltcg_clusters` is untouched (the path was already registered) and `roots` stays
as it was: rooting `SelectStage` would pin its declared `__thiscall` ABI and
bring the state pointer back in ECX.

The context passes the **same constants retail's caller does** — a
link-time address for the state object and literal `0` for the index, exactly
the `mov $0x491C28,%esi` / `xor %ebx,%ebx` pair at `0x0040E8A1` — and its result
is that the allocator gives `this` → **ESI**, the first parameter → **EBX** and
the record local → **EDI**, the same pattern `win32_timer`'s `Start(delay,
callback, user)` shows (`this` in ESI, first parameter in EBX, pointer
parameter in EDI).

## The caller's registers, and what the emitted body keeps

The region has exactly one call site in the whole image: `0x0040E8A1`, inside
`asm_FUN_0040e770_0040e770` (`src/script/ecl_vm.cpp`).

```asm
40e88f: 8b 43 34        mov    0x34(%ebx),%eax
40e892: 31 db           xor    %ebx,%ebx        ; stage index := 0     -> EBX
40e894: be 28 1c 49 00  mov    $0x491c28,%esi  ; state object        -> ESI
40e899: d9 5c 24 28     fstps  0x28(%esp)
40e89d: 89 44 24 2c     mov    %eax,0x2c(%esp)
40e8a1: e8 7a 34 ff ff  call   0x401d20
40e8d9: 8b 74 24 18     mov    0x18(%esp),%esi ; caller reloads its own ESI
40e8e4: 8b 5c 24 30     mov    0x30(%esp),%ebx ; ... EBX
40e8fc: 8b 7c 24 1c     mov    0x1c(%esp),%edi ; ... EDI
```

So retail's caller supplies the state in **ESI**, the index in **EBX** and
nothing on the stack, and it reloads ESI/EBX/EDI from its frame afterwards —
the callee's obligation is only to preserve EDI, which the emitted body does
(`push %edi` at `0x00401D28`, `pop %edi` at `0x00401D5A`); ESI and EBX are read,
never written. The emitted body is byte-identical, including the `REL32` to
`0x004215A0`, the imm32 form of `add $0xcc,%edx` (`81 c2 cc 00 00 00`, the same
form `0x00443B60` uses for the same `+0xCC` field), the `call *0xbc(%ecx)`
through the device vtable, and the `call` that needs no setup because the
record is already in EDI:

```
actual:   8b c3 69 c0 18 01 00 00 57 8d bc 30 54 01 00 00 89 be 84 03 00 00 e8 65 f8 01 00 8b 96 84 03 00 00 8b 46 08 8b 08 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00 89 9e 88 03 00 00 5f c3
expected: 8b c3 69 c0 18 01 00 00 57 8d bc 30 54 01 00 00 89 be 84 03 00 00 e8 65 f8 01 00 8b 96 84 03 00 00 8b 46 08 8b 08 81 c2 cc 00 00 00 52 50 ff 91 bc 00 00 00 89 9e 88 03 00 00 5f c3
different_bytes: 0
```

### Measured result

```
python3 matching2/tools/matching/probe.py --source src/render/render_stage_select.cpp \
  --project /tmp/SelectRenderStage/msvc --output /tmp/SelectRenderStage/out --show 30

0x00401d20      60 bytes  ?SelectStage@RenderStageState@@QAEXH@Z  EXACT
0x004215a0     330 bytes  ?Apply@RenderCamera@@QAEXXZ              EXACT
0x0043bc40     135 bytes  ?ClearAndPresentTwice@@YGHI@Z            EXACT
0x0043bcd0     108 bytes  ?ApplyDefaultViewport@@YGHI@Z             EXACT
0x0043bda0     483 bytes  ?DrawSolidQuad@@YGHPBUScreenRect@@I@Z     EXACT
0x0043bfa0     501 bytes  ?DrawGradientQuad@@YGHPBUScreenRect@@IIII@Z EXACT
0x0043c1a0     134 bytes  ?Draw@ColorViewport@@QAEHXZ               EXACT
0x004423c0      25 bytes  ?AnimationColor_MultiplyChannel@@YGIEE@Z  EXACT
0x004425a0     201 bytes  ?SyncRenderState@AnimationManager_00442F50@@QAEXPBURenderEntity@@@Z EXACT
0x00442670    1111 bytes  ?SubmitSpriteQuad@AnimationManager_00442F50@@QAEHPBURenderEntity@@I@Z EXACT
0x00442ad0    1111 bytes  ?SubmitSpriteQuadMirrored@AnimationManager_00442F50@@QAEHPBURenderEntity@@I@Z EXACT
0x00442f50     133 bytes  ?Flush@AnimationManager_00442F50@@QAEHXZ  EXACT
0x00442fe0     157 bytes  ?AppendQuad@AnimationManager_00442F50@@QAEHPBUTexturedVertex@@@Z EXACT
0x00444ce0     224 bytes  ?DrawStrip@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z EXACT
0x00444dc0     145 bytes  ?DrawQuad@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBUTexturedVertex@@@Z EXACT
0x00444e60     315 bytes  ?DrawSolidStrip@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z EXACT
0x00444fa0     315 bytes  ?DrawSolidFan@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z EXACT
0x004450e0     211 bytes  ?DrawFan@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z EXACT
EXACT
```

Re-run twice from a fresh build directory: identical (`different_bytes: 0`). The
link map shows `?SelectStage@RenderStageState@@QAEXH@Z 00401d20 f source_000.obj`
with contribution `.text$000pgselect 0001:00000d20 0000003cH`, i.e. exactly the
60 bytes at exactly the retail address.

## Artifacts

All four live in the sandbox `/tmp/SelectRenderStage/msvc`; the maintained tree
was not touched except for this note.

### `src/render/render_stage_select.cpp` (replaces the naked body)

```cpp
// 0x00401D20 - Select the active render stage: point the state's active stage
// at the indexed 0x118-byte stage record, reapply that camera, hand its
// viewport block to the render device and publish the index.
//
// Retail reaches the body with the state object in ESI and the index in EBX -
// the only call site (0x0040E8A1, the ECL thread) loads the state's address
// 0x00491C28 into ESI and zeroes EBX - and it calls RenderCamera::Apply with
// the camera in EDI. Those are whole-program register choices, so the body is
// compiled inside the native-LTCG cluster
// layout/ltcg/anm_batch_flush_00442f50.json, whose link already contains
// RenderCamera::Apply (src/render/camera_apply.cpp).
#include "th10/render/camera_batch.hpp"

// One render stage record: the camera Retail reapplies followed by the fields
// that make the record the 0x118 bytes the index stride shows. The camera sits
// at offset 0, so the viewport block the device receives is the record's +0xCC.
struct RenderStage {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};

// The game-wide state object at 0x00491C28: the render device at +0x08 (the
// pointer 0x00491C30 other render code loads), the stage records at +0x154 with
// a 0x118 stride, the active stage at +0x384 and the active index at +0x388.
struct RenderStageState {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                 // +0x08
    unsigned char reserved_00C[0x154 - 0x0C];
    RenderStage stages[2];                // +0x154, stride 0x118
    RenderStage* active_stage;            // +0x384
    int stage_index;                      // +0x388

    __declspec(noinline) void SelectStage(int index);
};

#pragma code_seg(".text$000pgselect")
void RenderStageState::SelectStage(int index) {
    active_stage = &stages[index];
    active_stage->camera.Apply();
    device->Viewport(&active_stage->camera.viewport_x);
    stage_index = index;
}
#pragma code_seg()
```

`device->Viewport` is the inline `RenderDevice` helper of `quad_batch.hpp`
(`((Call)vtable[0xBC/4])(this, viewport)`), which is what emits the pushed
device/`%ecx` = vtable/`call *0xbc(%ecx)` triple unchanged.

### `layout/ltcg/render_batch_context.cpp` (adds the convention-establishing call)

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
    }
    data_00491c28.SelectStage(0);
    return count;
}
#pragma code_seg()
```

The one added call sits *after* the loop, so the loop's live values are dead
there; the call reads a link-time address and a literal, which is exactly what
retail's caller materialises into ESI/EBX. Nothing else in the driver changed,
and every other function of the cluster kept its ABI (measured above).

### `layout/ltcg/anm_batch_flush_00442f50.json` (merged; replaces the 18-function layout)

Delta against the maintained file: the last entry of `functions`, the first
`additional_sources` entry, the last `absolute_symbols` entry, the first gap
split in two, and `context.size` 294 → 308.

```json
{
  "schema_version": 1,
  "name": "anm_batch_flush_00442f50",
  "source": "src/render/texture_stage_reset.cpp",
  "headers": [
    "include/th10/render/quad_batch.hpp",
    "include/th10/render/camera_batch.hpp"
  ],
  "image_base": "0x00400000",
  "description": "Native-LTCG render batch with compiler-visible camera application, state synchronization, quad appending, and primitive callers. Only the real ColorViewport::Draw and ApplyDefaultViewport public entries are rooted. The array-loop context establishes private conventions and contributes zero recovered game-code bytes.",
  "functions": [
    {"name": "AnimationManager_00442F50_Flush", "symbol": "?Flush@AnimationManager_00442F50@@QAEHXZ", "section": ".text$05flush", "address": "0x00442F50", "size": 133, "actual_abi": "manager in ESI; draw-call result in EAX; plain RET", "source": "src/render/anm_batch_flush.cpp"},
    {"name": "DrawSolidQuad", "source": "src/render/special_quad.cpp", "symbol": "?DrawSolidQuad@@YGHPBUScreenRect@@I@Z", "section": ".text$01quad", "address": "0x0043BDA0", "size": 483, "actual_abi": "EDI rect; EBX color"},
    {"name": "ColorViewport_Draw", "source": "src/render/default_viewport.cpp", "symbol": "?Draw@ColorViewport@@QAEHXZ", "section": ".text$03viewport", "address": "0x0043C1A0", "size": 134, "actual_abi": "ECX this"},
    {"name": "ClearAndPresentTwice", "source": "src/game/recovery_reset_device_streams_0043bc40.cpp", "symbol": "?ClearAndPresentTwice@@YGHI@Z", "section": ".text$01aclear", "address": "0x0043BC40", "size": 135, "actual_abi": "color in ESI; plain RET"},
    {"name": "ApplyDefaultViewport", "source": "src/render/viewport_apply_default_retail_0043bcd0.cpp", "symbol": "?ApplyDefaultViewport@@YGHI@Z", "section": ".text$01capply", "address": "0x0043BCD0", "size": 108, "actual_abi": "color on stack; RET 4"},
    {"name": "DrawGradientQuad", "source": "src/render/texture_stage_reset.cpp", "symbol": "?DrawGradientQuad@@YGHPBUScreenRect@@IIII@Z", "section": ".text$02gradient", "address": "0x0043BFA0", "size": 501, "actual_abi": "rect in EDI; four colors on stack; RET 16"},
    {"name": "SyncRenderState", "source": "src/render/render_state_sync.cpp", "symbol": "?SyncRenderState@AnimationManager_00442F50@@QAEXPBURenderEntity@@@Z", "section": ".text$04bsync", "address": "0x004425A0", "size": 201, "actual_abi": "EAX manager; EDI entity"},
    {"name": "DrawStrip", "source": "src/render/edge_strip_draw.cpp", "symbol": "?DrawStrip@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z", "section": ".text$06bstrip", "address": "0x00444CE0", "size": 224, "actual_abi": "ECX manager; EAX entity; vertices and count on stack; RET 8"},
    {"name": "AppendQuad", "source": "src/render/quad_vertex_append.cpp", "symbol": "?AppendQuad@AnimationManager_00442F50@@QAEHPBUTexturedVertex@@@Z", "section": ".text$05happend", "address": "0x00442FE0", "size": 157, "actual_abi": "EAX manager; EDX vertices; plain RET"},
    {"name": "DrawQuad", "source": "src/unidentified/unassigned_00444dc0.cpp", "symbol": "?DrawQuad@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBUTexturedVertex@@@Z", "section": ".text$06dquad", "address": "0x00444DC0", "size": 145, "actual_abi": "ECX manager; EAX entity; vertices on stack; RET 4"},
    {"name": "DrawFan", "source": "src/render/rect_fan_draw.cpp", "symbol": "?DrawFan@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z", "section": ".text$06ffan", "address": "0x004450E0", "size": 211, "actual_abi": "ECX manager; EAX entity; vertices/count on stack; RET 8"},
    {"name": "DrawSolidStrip", "source": "src/unidentified/unassigned_00444e60.cpp", "symbol": "?DrawSolidStrip@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z", "section": ".text$06ebstrip", "address": "0x00444E60", "size": 315, "actual_abi": "EAX manager; EDI entity; vertices/count on stack; RET 8"},
    {"name": "DrawSolidFan", "source": "src/unidentified/unassigned_00444fa0.cpp", "symbol": "?DrawSolidFan@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z", "section": ".text$06edfan", "address": "0x00444FA0", "size": 315, "actual_abi": "EAX manager; EDI entity; vertices/count on stack; RET 8"},
    {"name": "RenderCamera_Apply", "source": "src/render/camera_apply.cpp", "symbol": "?Apply@RenderCamera@@QAEXXZ", "section": ".text$00bcamera", "address": "0x004215A0", "size": 330, "actual_abi": "EDI camera; plain RET"},
    {"name": "AnimationColor_MultiplyChannel", "symbol": "?AnimationColor_MultiplyChannel@@YGIEE@Z", "section": ".text$04amult", "address": "0x004423C0", "size": 25, "actual_abi": "value in AL; scale in CL; result in EAX", "source": "src/render/animation_color_multiply_channel_004423c0.cpp"},
    {"name": "SubmitSpriteQuad", "symbol": "?SubmitSpriteQuad@AnimationManager_00442F50@@QAEHPBURenderEntity@@I@Z", "section": ".text$04c2quad", "address": "0x00442670", "size": 1111, "actual_abi": "EAX entity; ECX manager; mode on stack; plain RET 4", "source": "src/render/sprite_quad_submit.cpp"},
    {"name": "SubmitSpriteQuadMirrored", "symbol": "?SubmitSpriteQuadMirrored@AnimationManager_00442F50@@QAEHPBURenderEntity@@I@Z", "section": ".text$04c4mirror", "address": "0x00442AD0", "size": 1111, "actual_abi": "EAX entity; ECX manager; mode on stack; plain RET 4", "source": "src/render/sprite_quad_submit_mirrored.cpp"},
    {"name": "RenderStageState_SelectStage_00401d20", "symbol": "?SelectStage@RenderStageState@@QAEXH@Z", "section": ".text$000pgselect", "address": "0x00401D20", "size": 60, "actual_abi": "state in ESI; stage index in EBX; plain RET", "source": "src/render/render_stage_select.cpp"}
  ],
  "gaps": [
    {"section": ".text$000layout", "address": "0x00401000", "size": 3360},
    {"section": ".text$000zlayout", "address": "0x00401D5C", "size": 129092},
    {"section": ".text$02alayout", "address": "0x0043BF83", "size": 29},
    {"section": ".text$04alayout", "address": "0x0043C226", "size": 24986},
    {"section": ".text$04azlayout", "address": "0x004423D9", "size": 455},
    {"section": ".text$01blayout", "address": "0x0043BCC7", "size": 9},
    {"section": ".text$01dlayout", "address": "0x0043BD3C", "size": 100},
    {"section": ".text$02zlayout", "address": "0x0043C195", "size": 11},
    {"section": ".text$06alayout", "address": "0x0044307D", "size": 7267},
    {"section": ".text$04c1layout", "address": "0x00442669", "size": 7},
    {"section": ".text$04c3layout", "address": "0x00442AC7", "size": 9},
    {"section": ".text$04c5layout", "address": "0x00442F27", "size": 41},
    {"section": ".text$05glayout", "address": "0x00442FD5", "size": 11},
    {"section": ".text$06ealayout", "address": "0x00444E51", "size": 15},
    {"section": ".text$06glayout", "address": "0x004451B3", "size": 77},
    {"section": ".text$06eclayout", "address": "0x00444F9B", "size": 5},
    {"section": ".text$06eelayout", "address": "0x004450DB", "size": 5},
    {"section": ".text$00clayout", "address": "0x004216EA", "size": 107862},
    {"section": ".rdata", "address": "0x00446000", "size": 175000}
  ],
  "constants": [
    {"symbol": "__real@4f800000", "address": "0x00470B98", "value": 4294967296.0}
  ],
  "roots": ["?ApplyDefaultViewport@@YGHI@Z", "?Draw@ColorViewport@@QAEHXZ"],
  "absolute_symbols": [
    {"symbol": "_data_00491c10", "address": "0x00491C10", "kind": "data"},
    {"symbol": "_data_00491c30", "address": "0x00491C30", "kind": "data"},
    {"symbol": "_data_00491cf4", "address": "0x00491CF4", "kind": "data"},
    {"symbol": "__fltused", "address": "0x00000000", "kind": "metadata"},
    {"symbol": "_data_00491d0c", "address": "0x00491D0C", "kind": "data"},
    {"symbol": "_CameraLookAt@16", "address": "0x00452194", "kind": "relative_code"},
    {"symbol": "_CameraPerspective@20", "address": "0x0045219A", "kind": "relative_code"},
    {"symbol": "_CameraNormalize@8", "address": "0x0045217C", "kind": "relative_code"},
    {"symbol": "_data_004978c0", "address": "0x004978C0", "kind": "data"},
    {"symbol": "_data_00491fac", "address": "0x00491FAC", "kind": "data"},
    {"symbol": "_data_00470e8", "address": "0x004700E8", "kind": "data"},
    {"symbol": "_data_00470ec", "address": "0x004700EC", "kind": "data"},
    {"symbol": "_data_00491c28", "address": "0x00491C28", "kind": "data"}
  ],
  "additional_sources": [
    "src/render/render_stage_select.cpp",
    "src/render/anm_batch_flush.cpp",
    "src/render/special_quad.cpp",
    "src/render/default_viewport.cpp",
    "src/game/recovery_reset_device_streams_0043bc40.cpp",
    "src/render/viewport_apply_default_retail_0043bcd0.cpp",
    "src/render/render_state_sync.cpp",
    "src/render/edge_strip_draw.cpp",
    "src/render/quad_vertex_append.cpp",
    "src/unidentified/unassigned_00444dc0.cpp",
    "src/render/rect_fan_draw.cpp",
    "src/unidentified/unassigned_00444e60.cpp",
    "src/unidentified/unassigned_00444fa0.cpp",
    "src/render/camera_apply.cpp",
    "src/render/animation_color_multiply_channel_004423c0.cpp",
    "src/render/sprite_quad_submit.cpp",
    "src/render/sprite_quad_submit_mirrored.cpp"
  ],
  "driver": "layout/ltcg/render_batch_context.cpp",
  "context": {
    "symbol": "?RenderBatchContext@@YGHPAPBUScreenRect@@PBIHPAPBURenderEntity@@PAPBXPAPAURenderCamera@@@Z",
    "section": ".text$07context",
    "address": "0x00445200",
    "size": 308,
    "description": "Synthetic caller of gradient, entity primitive draws, sprite quad submission, and camera application; not recovered game code."
  }
}
```

### Manifest region record

```json
{
  "name": "semantic_RenderStageState_SelectStage_00401d20",
  "source": "src/render/render_stage_select.cpp",
  "symbol": "?SelectStage@RenderStageState@@QAEXH@Z",
  "address": "0x00401D20",
  "size": 60,
  "kind": "semantic",
  "owner": "0x00401D20",
  "previous_record": {
    "name": "asm_GameThread_SelectRenderStageRetail_00401d20",
    "source": "src/render/render_stage_select.cpp",
    "symbol": "_asm_GameThread_SelectRenderStageRetail_00401d20",
    "address": "0x00401D20",
    "size": 60,
    "kind": "asm",
    "owner": "0x00401D20"
  }
}
```

## Integration

1. Replace the naked body in `src/render/render_stage_select.cpp` with the model
   (the file's only region, so nothing has to be carved).
2. Copy the merged layout over `layout/ltcg/anm_batch_flush_00442f50.json` (same
   path and `name`, so `ltcg_clusters` is untouched — the path is already
   registered) and the extended driver over
   `layout/ltcg/render_batch_context.cpp`.
3. Rewrite just the `0x00401D20` region record, keeping `previous_record`, as
   above. `register_cluster.py --apply` cannot do this step: it compares every
   function's region source against the layout's single `source`, and this
   cluster now spans seventeen sources, so it refuses before touching the
   manifest.
4. `asm_symbols.hpp` and the manifest `symbols` table need **no** change: the
   `_asm_GameThread_SelectRenderStageRetail_00401d20 -> 0x00401D20` binding stays
   (as it did for the earlier merges), so the `call
   asm_GameThread_SelectRenderStageRetail_00401d20` inside
   `src/script/ecl_vm.cpp`'s naked body still resolves to the same address.

## Pitfalls this cost a build each (both recorded, both cheap)

* A merged `additional_source` still needs its own `#pragma code_seg`, and its
  section tag has to sort between the two gap sections that surround it —
  `.text$000layout` < `.text$000pgselect` < `.text$000zlayout` <
  `.text$00bcamera`. Cluster sections are placed in name order, so a `code_seg`
  tag that sorts past `camera_apply.cpp`'s moves the camera out of `0x004215A0`.
* The driver's declared extent must equal the emitted one: adding the single
  call grew `RenderBatchContext` by 14 bytes, so `context.size` had to go
  294 → 308 or the link aborts with `function is not its entire declared
  compiler contribution`. Nothing else in the layout moved, and the 18 landed
  functions re-probed `EXACT` unchanged after the edit — the merge is additive.
