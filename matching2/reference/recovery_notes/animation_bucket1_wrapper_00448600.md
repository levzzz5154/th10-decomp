# Render bucket 1 wrapper at `0x00448600`

Ghidra identifies a 15-byte `__thiscall` wrapper that saves EDI, puts the
constant slot index 1 in EAX, copies the manager receiver from ECX to EDI, and
calls the semantic bucket renderer at `0x00448980`. It returns the renderer's
result in EAX. Ghidra also records a code reference from the task setup at
`0x00445C46`.

The maintained source models this as `RenderBucket1()` returning
`RenderBucket(1)`. The native-LTCG context includes the existing renderer body
as an ABI anchor to expose the private EDI/EAX call convention. The wrapper
extent is known, but the C++ output is unverified; no build or probe was run.
