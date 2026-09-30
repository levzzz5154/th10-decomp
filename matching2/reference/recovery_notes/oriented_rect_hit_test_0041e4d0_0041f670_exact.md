# Oriented rectangle contact tests — exact C++ recovery

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27. Both `0x0041E4D0..0x0041E5B1` and
`0x0041F670..0x0041F751` have an ordinary MSVC 13.10.6030 C++ implementation
that matches all 226 bytes. Neither function needs inline assembly, a native
LTCG cluster, or additional compiler flags.

The two bodies are byte-identical. Live Ghidra MCP `read_memory` requests for
both complete spans returned the same bytes, whose SHA-256 is
`deac61a529943758798cceeb1adf22ffdac1070c5b6c55ef353db5f450f9a9d0`.
The receiver enters in ECX, the point pointer and radius enter on the stack,
the result is in EAX, and both return paths use `RET 8`. There are no outgoing
calls in either body.

## Implementation

The point is translated by the stored three-component center, then passed by
value to an inline rotation helper. That helper returns a three-component
point. Computing the lower and upper edge vectors before testing the bounds
gives retail's 24-byte stack frame, three-component copy, and subsequent dead
slot reuse. The stored rotation is negated; X is tested against the interval
`[0, extent_x_040]` and Y against
`[-extent_y_044 / 2, extent_y_044 / 2]`, with the radius expanding both sides.
The function returns 2 when the expanded point overlaps and 0 otherwise.

The remaining x87 scheduling difference was resolved by caching sine in a
small class with an inline float conversion:

```cpp
struct OrientedRectSine {
    float value;
    OrientedRectSine(float angle) : value(sin(angle)) {}
    __forceinline operator float() const { return value; }
};
```

The conversion preserves the float expression type while allowing the
optimizer to consume the cached x87 value at its last use. This produces the
retail sequence `FSIN`, `FXCH`, `FCOS`, followed by the exact four products and
their stack operations. A plain float sine local instead retained an extra
x87 value and emitted a discard; direct repeated trigonometric expressions
used the opposite sine/cosine schedule.

The comparisons are written as negated rejection tests. This preserves the
retail `TEST AH,41h` / `JE` and `TEST AH,5` / `JNP` behavior, including
unordered comparisons. Replacing these with a conjunction of `<=` tests
rejects NaNs and does not match the function.

The maintained source files share the assembly-free helper types in
`matching2/msvc/include/th10/math/oriented_rect_contact.hpp`. The two receiver
types remain distinct because identical bodies alone do not establish that
their enclosing retail classes are the same.

## Verification and integration

The project probe compiled both named implementations with the standard
manifest flags and selected their complete compiler sections. Both regions
reported `different_bytes: 0`, `exact: true`, no dropped sections, and all
three literal relocations matched the retail addresses:

| Literal | Address | Binding |
| --- | --- | --- |
| 0.5f | `0x00470B0C` | Existing `__real@3f000000` binding |
| 0.0f | `0x00470B04` | Source alias to `_data_00470b04` |
| -0.5f | `0x00470B78` | Source alias to `_data_00470b78` |

The aliases only rename COFF metadata; they do not rewrite instruction bytes.
They are required for both translation units.

The scratch promotion proposal and normal probe evidence are retained at:

- `matching2/build/experiments/rect_0041f670/promotion.json`
- `matching2/build/experiments/rect_0041f670/official_probe_twins.json`
- `matching2/build/experiments/rect_0041f670/ghidra_memory.json`
- `matching2/build/experiments/rect_0041f670/ghidra_memory_0041e4d0.json`
- `matching2/build/experiments/rect_trig_explorer/trig4/results.json`

The exact decorated symbols are
`?IntersectsCircle@OrientedRect_0041E4D0@@QBEHPBUPoint3_OrientedRect@@M@Z` and
`?IntersectsCircle@OrientedRect_0041F670@@QBEHPBUPoint3_OrientedRect@@M@Z`.
This supersedes the earlier 207/226 and 220/226 models and the deferred
native-LTCG suggestion for `0x0041F670`. The full maintained executable gate
remains the parent's integration check.
