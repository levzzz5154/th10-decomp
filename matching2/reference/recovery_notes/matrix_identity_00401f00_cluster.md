# 0x00401F00 — Matrix4x4::SetIdentity (native-LTCG cluster)

2026-09-19. Region `asm_unassigned_00401f00` (55 bytes, `src/unidentified/
unassigned_00401f00.cpp`) is promoted to semantic C++ through the native-LTCG
cluster path. Focused probe: **EXACT, 55/55 bytes, 0 differing, no
relocations**. Whole-image build not run by the recovering agent.

## What the region is

```
00401f00  xor  ecx,ecx
00401f02  mov  [eax+38h],ecx      00401f0e  mov [eax+24h],ecx     <- off-diagonal
...                               00401f23  mov [eax+4],ecx          run, descending
00401f26  mov  ecx,3F800000h
00401f2b  mov  [eax+3Ch],ecx      00401f2e  mov [eax+28h],ecx     <- diagonal,
00401f31  mov  [eax+14h],ecx      00401f34  mov [eax],ecx           descending
00401f36  ret
```

The four `1.0f` stores sit at `+0x00, +0x14, +0x28, +0x3C` — the diagonal of a
row-major 4x4 float matrix (stride 0x14). So the region is the out-of-line copy
of the identity write that `InitializeEntity` (`0x00401DE0`) also inlines for
the entity's `local_transform` at `+0x23C`; the inlined copy emits the same
store order there. The region has **no xref at all** — neither a `call rel32`
nor a dword holding `0x00401F00` exists anywhere in the image — which is why the
original arm was an unreferenced non-static member function and why the
whole-program pass was free to leave the object pointer in EAX.

## ABI and source

Entry register EAX holds the matrix; ECX is the single scratch register that
retail reuses for both constants; plain `ret`. Only the cluster path can express
this, so the model is a member function of a local 4x4 matrix type (same shape
as `FUN_00405130`/`FUN_00401f80`) and `layout/ltcg/matrix_identity_00401f00_context.cpp`
supplies the array-walking caller that makes LTCG choose EAX.

```cpp
// 0x00401F00..0x00401F36: write the identity transform into the 0x40-byte
// row-major D3D 4x4 matrix whose address arrives in EAX. ...
struct Matrix4x4 {
    float values[4][4];

    __declspec(noinline) void SetIdentity();
};

#pragma code_seg(".text$01identity")
void Matrix4x4::SetIdentity() {
    values[3][2] = 0.0f;   // twelve off-diagonal elements, descending offsets,
    ...                    // then the diagonal — the order retail emits
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}
#pragma code_seg()
```

Layout: `layout/ltcg/matrix_identity_00401f00.json`, cluster name
`matrix_identity_00401f00`, function symbol `?SetIdentity@Matrix4x4@@QAEXXZ`,
section `.text$01identity`, size 55, context `?MatrixIdentityCompilerContext@@YGHPAPAUMatrix4x4@@H@Z`
at `0x401F50` (40 bytes), gaps 0x401000/0xF00 and 0x401F37/0x19, and
`__fltused` bound as an absolute `metadata` symbol.

## Store order is source order

Fifteen shapes were compiled in the throwaway project. MSVC **preserves the
statement order** of a run of same-constant stores to one base register: writing
the off-diagonal elements in reading order moves bytes (12 differ, first at
`+0x04`), and writing the diagonal in ascending order moves the four diagonal
stores (10 differ, first at `+0x2C`). That fixes the recovered source order as
the emitted one — off-diagonal descending, then diagonal descending — matching
the convention already recorded for `0x00401DE0` ("chained identity assignments
in ascending source order produce the descending stores retail uses"). Chained
assignments (`values[3][2] = ... = 0.0f;`) reproduce it as well: the chain
assigns right-to-left, so an ascending chain emits descending stores.

Shapes that do **not** reproduce the region, with the emitted body:

| shape | emitted | note |
|---|---:|---|
| `memset(values, 0, sizeof(values))` + diagonal (with `<string.h>`, also `memset(this, ...)`) | 30 B | MSVC expands the 64-byte memset to `push edi` + `rep stos`, not to dword stores |
| `for (index = 15; index >= 0; --index) words[index] = 0;` + chained diagonal | 33 B | loop stays rolled, and its counter forces `this` into **ECX** |
| the same loop ascending | 68 B | rolled |
| descending `row`/`column` loop with an `(row == column)` ternary | 55 B | extent matches by coincidence, all 55 bytes differ |
| flat descending ternary loop over 16 floats | 44 B | rolled |

The rolled-loop result is the useful warning here: any counter live in EAX
pushes the object pointer to ECX and the region can never match, so an
unrolled, counter-free source is required.

## Integration

Copy three files into the maintained project — `src/unidentified/
unassigned_00401f00.cpp` (model), `layout/ltcg/matrix_identity_00401f00.json`
and `layout/ltcg/matrix_identity_00401f00_context.cpp` — then run
`python3 matching2/tools/waves/register_cluster.py --layout
layout/ltcg/matrix_identity_00401f00.json --apply` from `matching2/msvc`. That
turns the region semantic, sets the symbol, adds the layout to `ltcg_clusters`
and leaves `translation_units` unchanged. The agent's probe copy is
`/tmp/Leaf401F00/msvc`.
