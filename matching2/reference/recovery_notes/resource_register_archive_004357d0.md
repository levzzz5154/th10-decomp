# Archive registration at `0x004357D0`

Ghidra confirms a 36-byte routine that selects the next 16-byte record from
the archive table at `0x004923B0`, calls the archive open routine at
`0x00434C30`, and increments the count at `0x00477850` only if opening
succeeds. It has no capacity check or extra initialization. The path enters in
EAX, the archive receiver is passed in ECX, and the result is returned in AL.
Ghidra reports no direct callers or references.

The maintained source now expresses the operation as
`Resource_RegisterArchive(path)`. Its LTCG layout contains a compiler-only
`Open` ABI anchor and a synthetic path-array caller. The anchor/context extents
and the EAX convention are unverified; no build or probe was run.
