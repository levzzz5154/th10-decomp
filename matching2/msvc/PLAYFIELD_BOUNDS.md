# Playfield boundary recovery

The maintained C++98 implementation is
[`src/game/playfield_bounds.cpp`](src/game/playfield_bounds.cpp). It replaces
the 91-byte routine at `0x004086B0` with an ordinary `thiscall` method on a
two-float point.

The two known callers at `0x00408058` and `0x004081C3` establish the point in
ECX and push horizontal and vertical margins. The resulting method expands the
allowed interval by those margins and returns 1 when the point touches or
crosses an expanded minimum or maximum. Boundary contact is therefore outside.

The source deliberately spells the four inside checks as negated comparisons.
That reproduces the x87 status-word branches and preserves the less obvious
unordered contract: if a coordinate or relevant margin is NaN, none of the
four boundaries classifies it as outside.

The manifest records all four absolute relocations to the playfield limits at
`0x00470B40`, `0x00470B3C`, `0x00470B04`, and `0x00470B38`. The native C++98
contract test covers an interior point, exact contact on all four expanded
edges, values just inside and outside, and unordered coordinates and margins.
The fixed-address MSVC build remains the authoritative byte and `thiscall` ABI
gate.

The adjacent wrapped-angle and polar-vector helpers remain assembly. Compiler
experiments recover their broad arithmetic meaning, but MSVC emits a different
x87 operand order for the angle helper and separate trigonometric instructions
instead of retail's combined `fsincos` sequence.
