# Bullet effect vectors at 0x004043D0

Ghidra identifies a 59-byte function with no incoming xrefs. Retail receives
a bullet object in EDX and two three-word source vectors in ECX and EAX. It
sets the word at bullet offset `0x1EEC` to one, then copies the first vector
to `0x1EF0` and the second to `0x1EFC`, preserving component order. Other
bullet code checks and clears the word at `0x1EEC`.

The [C++ source](../semantic_candidates/bullet_effect_vectors_004043d0.cpp)
uses typed `BulletEntity` and `Vector3` pointers and a small overlay for the
effect block. The manifest retains the old assembly record in
`previous_record`. The typed cdecl arguments replace the retail register ABI;
byte matching remains unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
