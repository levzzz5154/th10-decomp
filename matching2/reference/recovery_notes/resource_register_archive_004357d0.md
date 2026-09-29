# Archive registration at `0x004357D0`

Ghidra confirms a 36-byte routine that selects the next 16-byte record from
the archive table at `0x004923B0`, calls the archive open routine at
`0x00434C30`, and increments the count at `0x00477850` only if opening
succeeds. It has no capacity check or extra initialization. The path enters in
EAX, the archive receiver is passed in ECX, and the result is returned in AL.
Ghidra reports no direct callers or references.

The repaired candidate at `reference/semantic_candidates/unassigned_004357d0.cpp`
now calls the actual recovered opener interface and shares the archive types.
It passes 120 retail comparisons, including count changes during Open and
32-bit increment wrapping. See
[resource dispatch recovery](resource_paths_004357d0_0043599d.md).

The earlier compiler-only Open anchor was an unverified proposal. The current
production region remains assembly; the explicit candidate path parameter
has not been lowered to the retail EAX entry under native MSVC.
