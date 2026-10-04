# Interpolators (0x00441950, 0x00441AD0, 0x00404610, 0x00441600 exact)

`Interpolator<T>::Step` in `include/th10/math/interpolator_step.hpp` compiles
byte-exact for `int` (0x00441950), `Vec2` (0x00441AD0) and `Vec3`
(0x00404610). All three are built in the `evaluate_curve_0044c350` cluster,
one source per instantiation.

- Template members take the `#pragma code_seg` in effect at the end of the
  translation unit, so each instantiating source ends with its section pragma.
  An explicit instantiation under a pragma does not move them.
- `Step` is defined in a separate header that only the instantiating sources
  include; the context includes the declaration only, otherwise it would
  emit its own copies.
- What the shapes needed: the finish test as `if (mode != 7) return target;
  return value;`, modes 7 and 17 through a named `T current`, the Hermite
  weights as four named floats, `T result = ...; return result;`, and vector
  operators that return through a constructor (`return Vec2(x + v.x, ...)`).
- The curve call is the in-class `Rate()`; retail kept its out-of-line copies
  at 0x00441D70/D90/DB0.

## 0x00441600: landed three-int specialization

`src/math/interpolators.cpp` now contains the readable `Interpolator<Int3>::Step`
specialization. `include/th10/math/int3.hpp` defines the colour vector and its
component-wise arithmetic. The specialization uses the same frame timer,
finish behavior, accumulating modes 7/17, and Hermite weights as the shared
template.

The four Hermite terms call the noinline integer scale operator. Linear easing
uses the force-inlined `InterpolateLinear` helper and `Int3::Scale`, preserving
retail's direct component calculations. Every scaled component truncates toward
zero before addition. The helper boundary also preserves MSVC's operand schedule;
writing the final expression directly produced 822 bytes instead of 820.

The integer specialization keeps the shared Step header unchanged: factoring the
linear expression through a shared helper produced an exact Int3 instance but
changed operand order in the previously exact Vec2 and Vec3 instances.

The existing easing cluster now includes the Int3 instance and a 56-byte scale
anchor at `0x00441E50`. The anchor was independently compared with retail and is
byte-exact; the final image still uses the already recovered scaler owned by
`src/math/random_vector.cpp`. No instruction bytes are patched.

The integrated probe reports all five selected functions exact:

```sh
python3 matching2/tools/matching/probe.py --source src/math/interpolators.cpp
```

## Original inlining investigation (resolved by the specialization)

The same template gives all 285 instructions once the scale operator is
called at the four Hermite sites and expanded on the easing path. The
helpers retail kept at 0x00441E10 (`-`), 0x00441E40 (constructor),
0x00441E50 (`* float`) and 0x00441E90 (`+`) are reproduced exactly by

    Int3 operator*(float f) const {
        int rx = int(x * f); int ry = int(y * f); int rz = int(z * f);
        return Int3(rx, ry, rz);
    }

and the same local-then-construct form for `+` and `-`. With that operator
the compiler expands all five scale calls (841 bytes instead of 820).

The decision was read out of `c2.dll` (`InlCallGraphDecision`, see the
`msvc-ltcg-inliner-decision-formula` memory): score = callee bytes (56)
- argument benefit - 10; the Hermite calls score 36 at block weight
9,375,000 and anything up to 37 is expanded. Retail needs 38 or more there
and 37 or less on the easing path (which scores 33 because `this` is a
temporary). A 58-byte operator (`Int3 r; r.x = ...; return r;`) lands in
that window and produces retail's call pattern, but its out-of-line body is
not retail's.

So the original gives the Hermite calls either a block weight of at most
8.85M (one more conditional level than the easing path, or about 5 to 13
percent more of the flow leaving before the mode tests) or two points less
argument benefit. Not found: else-if chains, a switch (changes the layout),
array or expression weights, direct return, accumulating into `result`.
