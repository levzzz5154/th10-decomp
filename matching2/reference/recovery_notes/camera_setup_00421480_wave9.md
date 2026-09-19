# 0x00421480 `RenderCamera::ApplyDefault` — wave 9: the aspect block is reproduced, the last two instructions are the codegen's register plan

2026-09-19. Region `0x00421480` (287 bytes, `asm_Camera_ApplyRetail_00421480`,
`src/render/camera_setup.cpp`, still `kind: asm`) is **not** landed. The model
below emits **293 bytes against the declared 287**, frame **`0x2C` exactly**
(retail's own 44-byte frame), and after deleting its two redundant instructions
the body is **287 bytes differing in 4 bytes**, three of which are the
position-dependent relative call displacements that correct themselves at the
right extent. The remaining single real byte is `fst` where retail has `fstp`.

The wave-4 measurement (196 differing, every model spilling the aspect into a
third slot and recomputing the division at the perspective call) is superseded:
the division is now materialised **in retail's own position** from retail's own
two slots. What is left is the x87 register plan around it, not the block.

**0x00405300 (`RenderStageState_00405300::SelectDefaultStage`) keeps its ABI
anchor.** Nothing here is registered: the maintained tree is untouched (no
layout, no driver, no source, no manifest edit), so
`layout/ltcg/render_stage_select_00405300.json` and its
`Camera_ApplyRetail_00421480_abi_anchor` entry stand as they are.

## The measured delta

```
emitted 293 bytes (retail 287), frame 0x2C (retail 0x2C), differing 127 bytes
first difference 0x421490: got cc 1a 02 00 8b 87 d4 00  want bc 1a 02 00 8b 87 d4 00
```

The first difference is the `call 0x442F50` displacement: a 293-byte
contribution moves the laid-out Flush callee by 16, exactly the artefact the
wave-4 note recorded for the failed longer contributions. The instruction-level
comparison from `0x004214EF` (the four immediate stores) to `0x0042153D` is a
pure 6-byte shift plus two insertions:

| retail | model | note |
| --- | --- | --- |
| `d9 5c 24 1c` `fstp [esp+0x1c]` | `d9 54 24 1c` `fst [esp+0x1c]` | same store, the model keeps the x87 register |
| — | `d9 5c 24 18` `fstp [esp+0x18]` | **+4 bytes**, dead second copy of the same value |
| `dd 05 a0 0b 47 00` | `d9 c0` + `dd 05 a0 0b 47 00` | **+2 bytes**, `fld st(0)` duplicate of `half_height` |
| `d8 f9` `fdivr st,st(1)` | `de f9` `fdivp st(1),st` | same length, same result, different encoding |

Deleting the two inserted instructions and re-encoding the divide yields **287
bytes that differ from retail in 4 bytes**: `0x421510` (`0x54` vs `0x5c`, the
`fst`/`fstp` above) and the three rel32 call sites (`0x421490`, `0x421538`,
`0x421558`), which are a function of the extent and land exactly once the
contribution is 287 bytes.

Everything else is equal byte for byte: the prologue and both saved registers,
the Flush call, both unsigned conversions with their `test/jge/fadd` fixups, the
two `fst`+`fmul DWORD PTR ds:0x470B0C` half-widths, **`fld [esp+8]` + `fdiv
[esp+0xc]` in retail's position and with retail's memory operands**, the four
immediate stores in retail's order, the eye/target store sequence, the `fptan`
chain, both device transforms, the clip tail and `add esp,0x2c; ret`.

## The model (`src/render/camera_setup.cpp`, camera-lab project)

```cpp
// 0x00421480: construct a centered perspective view from the viewport dimensions.
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
    volatile float aspect = viewport_width / viewport_height;
    CameraVector view_up, target, eye;
    eye.x = half_width; eye.y = half_height; eye.z = half_height / tan(data_00470ba0);
    target.x = half_width; target.y = half_height; target.z = 0.0f;
    view_up.x = 0.0f; view_up.y = -1.0f; view_up.z = 0.0f;
    CameraLookAt(&view, &eye, &target, &view_up);
    CameraPerspective(&projection, 0.31415927f, viewport_width / viewport_height, 1.0f, 10000.0f);
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

The `volatile` and the repeated `viewport_width / viewport_height` are the two
load-bearing (and deliberately unnatural) levers found here, not recovered
style: see *Mechanism* below. `CameraVector`/`RenderCamera` and the two
`__stdcall` matrix helpers are the camera-lab project's existing
`include/th10/render/camera_batch.hpp`; the model is compiled inside the
existing `layout/ltcg/anm_batch_flush_00442f50.json` cluster, which already
selects `RenderCamera_ApplyDefault` at `0x00421480` with the measured
`EDI camera; plain RET` convention, so the whole-program pass gives the region
EDI both here and in the wave-4 and wave-8 runs.

## Reproduction

```bash
cp -a matching2/build/camera-lab/project /tmp/CameraApply/cam/msvc
python3 camverify.py <variant>      # writes src/render/camera_setup.cpp, builds the
                                    # cluster, prints extent / differing / first diff
```

`camverify.py` (harness, `/tmp/CameraApply/camverify.py`) loads
`layout/ltcg/anm_batch_flush_00442f50.json`, builds it with the project's own
flags plus the native `/GL` link, and reads the emitted body at
`0x00421480` out of the linked PE. The harness itself is disposable: it only
writes the variant into `src/render/camera_setup.cpp`, calls
`build_cluster(spec, toolkit, out, config['flags'])` from
`matching2.tools.matching.ltcg_cluster`, and reads
`PEImage(exe).read(0x00421480, 287)`. Each build is ~6 s. The variant file for
the model above is `/tmp/CameraApply/variants/w4_f06_eye_tgt_up.camera.cpp`;
`variants/w7_j_yzx_tu.camera.cpp` is the same instruction set in a different
intra-statement order and reports 114 differing (alignment luck) at the same
293 bytes. The plain-`/O2` proxy reads the same body through
`python3 plain_shape.py <variant>` (0.4 s).

## Mechanism: the aspect division is materialised lazily, and only a forced store moves it

The wave-4 note's diagnosis is confirmed and sharpened.

1. **The division is not sunk by LTCG.** Compiling the same source as a plain
   translation unit with the project's flags minus `/GL`
   (`wine cl.exe /c /O2 /Gz /MT /Gy /G6 /GF /GS /Zl`) emits the same x87
   sequence, including the deferred `fld [W]; fdiv [H]` after the `CameraLookAt`
   call. `/GL` is not the cause; the `/O2` code generator simply materialises
   `a / b` whose operands live in memory at the use, and it rematerialises the
   value at the perspective argument instead of spilling it.
2. **A store at the assignment is the only lever that moves it.** With
   `volatile float aspect = viewport_width / viewport_height;` the division is
   emitted at the definition (`fld [esp+8]; fdiv [esp+0xc]`, retail's operands
   and position) and the result is spilled into retail's own slot. Address-taken
   (`const float* p = &aspect;`) behaves the same way *only* while the pointer is
   live; `const float&` and a local struct/array either scalarise away or add a
   frame slot.
3. **The two conversion locals keep a memory home only when they are used after
   the call.** In the plain named-local shape the compiler keeps `viewport_width`
   in an x87 register (`fld [0x470B0C]; fmul st,st(1)`) and divides out of that
   register (`fxch st(2); fdiv [H]`), which is 4 bytes shorter and frame `0x28`.
   The memory homes with retail's `fst`+`fmul [mem]` and `fld [W]; fdiv [H]`
   appear exactly when the aspect expression is also *written* at the
   perspective call, i.e. when the compiler must treat `viewport_width` and
   `viewport_height` as live across `CameraLookAt`.
4. **Together they reproduce the whole block but cost two instructions.** The
   volatile store and the call's own copy of the same value are two destinations
   for one CSE'd division, so the compiler emits `fst [esp+0x1c]` (keep) plus a
   dead `fstp [esp+0x18]`; the kept register is then also what makes it
   duplicate `half_height` (`fld st(0)`) instead of dividing the register it
   already holds (`fdivr st,st(1)`). Every shape that fixes one artifact breaks
   the other: removing the volatile restores the deferral, using the volatile
   variable as the argument (one store, `fstp`) drops `viewport_width` back into
   a register and the frame to `0x28`.

## Two other near-misses (for the next attempt)

| shape | emitted | frame | what matched | what broke |
| --- | ---: | --- | --- | --- |
| `volatile` aspect, call reads the variable, conversions named | 288 | `0x28` | one `fstp` aspect store into retail's slot `[esp+0x1c]`, division materialised early, `fld [esp+0xc]` divisor | `viewport_width` stays in an x87 register (`fld [0x470B0C]; fmul st,st(1)` + `fxch st(2); fdiv [mem]`), so the frame loses `W`'s slot |
| `volatile float viewport_width` + `volatile` aspect, call reads the variable | 296 | `0x2C` | **the division reads both operands from memory exactly as retail**, one popping aspect store | the volatile forces `fstp [W]` + a reloading `fld [W]` where retail has one `fst [W]`, and the aspect's read at the call becomes `fld [slot]; fstp [esp]` instead of retail's `mov edx,[slot]; push edx` |

The second row is the closest *operand-location* match found: it proves the
division's memory form is reachable, and that the cost is the volatile store's
popping/reloading shape.

## Shapes tried

All rows are measured builds. The archived and wave-4 rows are the wave-4
note's cluster builds; every other row was re-measured here through the native
`/GL` cluster (`camverify.py`, ~6 s). A plain-`/O2` translation unit (no `/GL`)
read through the same normalised disassembly comparison reproduces the cluster's
decisions on every source below and runs in 0.4 s, so ~200 further shapes were
searched through that proxy before the ones above were confirmed in the cluster.

| shape family | emitted | frame | differing | outcome |
| --- | ---: | --- | ---: | --- |
| archived wave-4 (`camera1/2`, `default1`–`default6`) | 291–329 | `0x2C`/`0x30` | 197–233 | division recomputed at the call |
| wave-4 sweep: float order × vector order (10) | 291–300 | `0x2C`/`0x30` | 196–233 | best 196, aspect deferred |
| aspect statement moved: after the halves / after the vectors / after the up members | 284–292 | `0x2C`/`0x30` | 189–197 | optimizer normalises all of them back |
| aspect as the argument expression, named `aspect`, `const`, `const&`, inlined helpers | 284–293 | `0x2C`/`0x30` | 127–229 | same normalisation |
| member-wise construction, 6 store permutations × {up/target/eye, eye/target/up} | 284–295 | `0x28`–`0x30` | 114–224 | **locked the frame at `0x2C` and retail's store order** |
| `volatile` aspect + call re-dividing (member-wise, eye/target/up) | **293** | **`0x2C`** | **127** | best; only the two instructions above differ |
| same, call using the variable / a `ratio` local / a pointer / casts / the halves | 285–330 | `0x28`/`0x30` | 114–239 | one of the four defects each |
| conversions unnamed, halves from the casts (`c5`, `c6`) | 291 | `0x2C` | 233 | multiply becomes `fld [0x470B0C]; fmul st,st(1)` |

The proxy also covered `0.5f * value` and `(float)` cast spellings (frame
`0x30`, deferred division) and the local array/struct and reference forms (`SRA`
either scalarises them back to the plain shape or adds a frame slot).

## Next step

The residual is a two-destination store and a duplicated register, both decided
by the `/O2` code generator after the IL is fixed. A route that has not been
tried is making the aspect's store and the call's operand the *same* value in
the IL — e.g. reading the aspect through an lvalue whose address is genuinely
observable (a member or an out-parameter) while the conversion locals stay live
past the `CameraLookAt` call — or a build whose scheduler hoists the division
itself. Until then the region stays assembly and `0x00405300` keeps the anchor.
