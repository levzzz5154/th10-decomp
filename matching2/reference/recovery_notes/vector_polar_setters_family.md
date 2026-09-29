# Vector polar setters — a seven-region family at the exact extent

Current maintained-source status, 2026-09-27: `projection_quads.cpp` still
contains its two inline `FSINCOS` blocks and passes the current full executable
comparison. Its conversion remains incomplete. The active goal requires both
byte matching and freedom from inline assembly; later passages accepting
unverified semantic-only output describe an earlier scope and source snapshot.
See the [verified checkpoint](native_recoveries_2026-09-27_third.md).

2026-09-18. Screening the remaining assembly for no-call game regions with a
plain ABI surfaced a family of **seven 30-byte `__thiscall` setters** sharing
the same `FSINCOS` component pattern. The elliptic variant uses separate
horizontal and vertical scales:

| region | source file |
| --- | --- |
| `0x004458B0` `Vector2_SetPolar` | `src/math/x87_polar_setters.cpp` |
| `0x0044C5D0` `Recovery_PolarToVectorRetail` | `src/math/x87_polar_setters.cpp` |
| `0x00441EF0` `Vector2_SetAnimationPolar` | `src/math/x87_polar_setters.cpp` |
| `0x0041F800` `SetPolar_Vector2` | `src/math/x87_polar_setters.cpp` |
| `0x0041BEB0` `FUN_0041beb0` | `src/math/x87_polar_setters.cpp` |
| `0x00413270` `Vector2_SetEllipticPolar` | `src/math/x87_polar_setters.cpp` |
| `0x004501B0` `ECL_SetPolarVector` | `src/math/x87_polar_setters.cpp` |

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

Once either is explained the other six members should follow from the same
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


## `0x00443B60` now uses semantic C++ trig calls

As of 2026-09-23, both inline `FSINCOS` blocks in the already-landed
`0x00443B60` (`src/render/projection_quads.cpp`, 1047 bytes) have been replaced
with `cosf(angle)` and `sinf(angle)`. This removes inline assembly from that
semantic source and keeps the recovered rotation calculation readable. The
compiler output and numerical equivalence, including exceptional inputs and
x87 rounding details, have not been rebuilt or probed for this change.

The earlier observation in `wave8_large_region_blockers.md` that MSVC does not
emit `FSINCOS` from `sinf`/`cosf` still applies to exact retail reproduction:
MSVC produces separate FSIN/FCOS operations. For this family, the *entire*
eleven-instruction body is the sincos sequence and two scaled stores, so an
equivalent exact body would be almost entirely inline assembly. The current
source goal accepts semantic C++ for these simple setters; exact retail
instruction selection therefore remains unverified. The `this` spill is moot
for that semantic model because it is part of the retail instruction sequence
rather than the component-level operation.

## Historical semantic C++ proposals at `0x00441EF0`

Earlier exploratory `cosf`/`sinf` models described the seven setters as
semantic-only C++; the table records those proposals, not current manifest
ownership:

| entry | C++ representation | parameters after `this` |
| --- | --- | --- |
| `0x0041F800` | `PolarVector2_0041F800::SetPolar` | angle, scale |
| `0x004458B0` | `PolarVector2_004458B0::SetPolar` | angle, scale |
| `0x0041BEB0` | `PolarVector2_0041BEB0::SetPolar` | angle, scale |
| `0x0044C5D0` | `RecoveryPolarVector2_0044C5D0::SetFromPolar` | angle, scale |
| `0x00413270` | `EllipticPolarVector2_00413270::SetEllipticPolar` | angle, horizontal scale, vertical scale |
| `0x004501B0` | `EclPolarVector2_004501B0::SetPolar` | angle, scale |

The historical `cosf`/`sinf` proposals above did not reproduce retail's
`FSINCOS` or x87 precision. The maintained
[`x87_polar_setters.cpp`](../../msvc/src/math/x87_polar_setters.cpp) now
defines all seven original setters plus `0x00408750` as byte-exact ordinary
C++. GCC's `__builtin_sincosl` emits `FSINCOS`, and the pinned generic
stack-home pass matches retail's receiver spill. The elliptic setter loads
separate horizontal and vertical scales and returns with `RET 12`; the others
return with `RET 8`. A focused probe matched all eight complete 30-byte
bodies and their affected source units. The migrated external symbols keep
existing callers bound to the compiled definitions. The unrelated
`projection_quads.cpp` inline trigonometry remains to be recovered.
