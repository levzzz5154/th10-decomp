# Vector polar setters — a six-region family at the exact extent

2026-09-18. Screening the remaining assembly for no-call game regions with a
plain ABI surfaced a uniform family: **six 30-byte `__thiscall` setters**, all 11
instructions, all with the identical shape modulo their address:

| region | source file |
| --- | --- |
| `0x004458B0` `Vector2_SetPolar` | `src/math/vector.cpp` |
| `0x0044C5D0` `Recovery_PolarToVectorRetail` | `src/math/vector2_polar.cpp` |
| `0x00441EF0` `Vector2_SetAnimationPolar` | `src/game/recovery_leaves.cpp` |
| `0x0041F800` `SetPolar_Vector2` | `src/math/vector.cpp` |
| `0x0041BEB0` `FUN_0041beb0` | `src/game/score.cpp` |
| `0x00413270` `Vector2_SetEllipticPolar` | `src/game/recovery_leaves.cpp` |

Retail listing (`0x004458B0`):

```
51            push ecx
89 0c 24      mov [esp],ecx          ; this spilled to a frame slot
8b 04 24      mov eax,[esp]          ; loaded back for the destination
d9 44 24 08   fld dword [esp+8]      ; angle
d9 fb         fsincos                ; one fused sin+cos
d8 4c 24 0c   fmul dword [esp+0Ch]   ; * radius
d9 18         fstp dword [eax]       ; x = cos * radius
d8 4c 24 0c   fmul dword [esp+0Ch]
d9 58 04      fstp dword [eax+4]     ; y = sin * radius
59            pop ecx
c2 08 00      ret 8
```

## Measured model and its two discriminators

A member `SetPolar(float angle, float radius)` that computes both results and
stores x from the cosine, y from the sine — with `cosf`/`sinf`, float locals,
double locals, `(double)` casts on the argument, a float copy of the argument, or
a named result pointer — compiles to **exactly 30 bytes** but selects different
instructions:

```
d9 44 24 04   fld dword [esp+4]
8b c1         mov eax,ecx              ; this stays in a register
d9 ff         fcos                     ; not fused
d8 4c 24 08   fmul dword [esp+8]
d9 18         fstp dword [eax]
d9 44 24 04   fld dword [esp+4]       ; angle reloaded
d9 fe         fsin
d8 4c 24 08   fmul dword [esp+8]
d9 58 04      fstp dword [eax+4]
c2 08 00      ret 8
```

So the extent, the calling convention, the argument layout and the store order
all already match; exactly two things do not:

1. **`fsincos` instead of `fcos`+`fsin`.** MSVC 7.1 fuses the sine and cosine
   intrinsics of one argument, but with the maintained `/O2 /G6` profile every
   spelling above expands them separately. Whether the fusion is reachable
   outside a `/GL` pass is the open question for this family.
2. **The `this` spill.** Retail pushes a four-byte frame slot for `this`
   (`push ecx; mov [esp],ecx`) and reloads it into EAX; the model keeps `this` in
   ECX and copies it to EAX. Whatever raises retail's pressure to memory-home
   `this` is the second unknown.

Once either is explained the other five members should follow from the same
source with only their class names changed — the listings are identical.

## Native-LTCG path measured for this family: rejected

The cluster machinery was exercised for `0x004458B0` in the throwaway copy
(schema-1 cluster, synthetic float-returning context, `__fltused` bound as
metadata — the `clear_angular_velocity_x` layout shows that binding is the
established way to link float code into a cluster):

```
.text$01accessor  0000001cH   ← 28 bytes under /GL + /LTCG
```

The whole-program pass re-compiles the setter to **28 bytes**, two short of
retail's 30. Retail's extent therefore matches the *plain* translation unit, not
the LTCG one, so this family is not a cluster target: the remaining gap is
purely the instruction selection inside a plain `/O2 /G6` build (`fsincos`
instead of `fcos`+`fsin`, and the `this` spill), exactly as recorded above.
