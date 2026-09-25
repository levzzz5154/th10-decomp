# Entity leaf boundaries at 0x00401CE0 and 0x00401D60

Live Ghidra disassembly separates the former 44-byte assembly row at
`0x00401CE0` into a 32-byte setter ending at `0x00401CFF` and a 12-byte
record accessor at `0x00401D00..0x00401D0B`. Both functions were created and
documented in Ghidra. No incoming xrefs were reported for either entry.

The first function receives an `Entity*` in EAX and two 32-bit stack values.
It writes the values at entity offsets `0x4C` and `0x50`, which the current
entity layout names `sprite_width` and `sprite_height`, then sets bit 3 of the
flag word at `0x35C`. The second receives an index in EAX and a container in
ECX; it returns the pointer stored at container offset `0x118` plus
`index * 0x44`. [Semantic C++](../semantic_candidates/entity_runtime_leaf_helpers_00401ce0.cpp)
now models both functions, and the manifest has separate regions for their
actual boundaries.

Ghidra also identifies the setter at `0x00401D60..0x00401D7F` as writing
`scale_x` and `scale_y` at offsets `0x3C` and `0x40` and setting the same flag
bit. [Semantic C++](../semantic_candidates/entity_scale_00401d60.cpp)
models that setter. The trailing `RET` at `0x00401D80` has no incoming xrefs;
it is represented as a separate tentative empty function. The two manifest
regions are 32 and 1 bytes, matching Ghidra's instruction boundaries.

The setters and accessor originally use private EAX/ECX inputs. Their C++
models use explicit arguments, so original entry ABI and exact retail bytes
remain unverified. No build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
