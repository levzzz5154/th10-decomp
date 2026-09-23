# Point translation at `0x004187F0`

Ghidra identifies a 29-byte leaf that writes a three-float point translated
by `(224.0, 16.0)`: x and y are offset, and z is copied. The source point is in
ECX and the aggregate result buffer is in EAX. Ghidra found no callers or
incoming references. The likely playfield-coordinate role is inferred from the
constants at `0x00470B4C` and `0x00470B48` and nearby point helpers.

The maintained source now models a `Vector3_004187F0::Translate() const`
aggregate return. Its schema-1 native-LTCG layout supplies a synthetic
null-terminated point-array caller and aliases the float constants to their
retail addresses. The context placement/extent and C++ contribution are
unverified; no build or probe was run.
