# Camera defaults initializer at `0x004216F0`

## Ghidra evidence

Connected `th10.exe` analysis identifies `FUN_004216f0` at `0x004216F0` with
body `0x004216F0..0x004218C0` inclusive (465 bytes) and a no-argument,
`__stdcall` signature. The decompiler shows a leaf that stores constants to
the two render-stage camera records. Disassembly reaches one `RET` at
`0x004218C0`; it makes no calls and uses no incoming argument or custom
register input. The body adjusts its own 12-byte local stack area and restores
it before returning. It does not touch EBX, ESI, EDI, or EBP. The existing
`__cdecl` C-linkage definition has the same stack contract because there are
no arguments for either convention to clean up.

`get_function_xrefs(0x004216F0)` reports one direct call xref, from
`0x004201CB`. Ghidra disassembles that site as `CALL 0x004216F0`, with no
argument setup. The following instruction calls an unrelated function
pointer, so the initializer's incidental EAX value is not consumed. Ghidra's
caller-list API does not resolve a containing caller function for that site;
the call-site xref itself is present. The current local source
`src/unidentified/FUN_004201b0_004201b0.cpp` places the call in that
initializer sequence.

The function has no callees. Ghidra's decompiler resolves the writes as:

* At `0x00491D7C`, position `(0, 0, 1000)`, direction `(0, 0, 0)`, up
  `(0, 1, 0)`, eye offset `(0, 0, 0)`, FOV bits `0x3F060A92`, viewport
  `(32, 16, 384, 448, 0, 1)`, and `unknown_0e4 = 0`.
* At `0x00491E94`, the same position, direction, up, eye offset, and FOV;
  viewport `(0, 0, 640, 480, 0, 1)` and `unknown_0e4 = 1`.

These addresses are the camera members at the start of the two `0x118`-byte
render-stage records established in the stage-selection recovery notes. The
readable source writes only the fields present in Ghidra's output. It leaves
the `unknown_0e4` name as-is and does not clear the rest of either camera, in
particular the matrices and other state not written by this routine.

## Exactness status

The previous `D3801` exact-codegen attempt recorded a 218/465-byte match; its
direct typed-store variant had a reported 401-byte extent, and its
temporary-vector variant emitted 465 bytes but differed in 247 bytes. The
source expresses the Ghidra-observed field writes as ordinary C++. The
manifest now classifies the entry as semantic, binds
`_RenderCamera_InitializeDefaults_004216f0`, and retains the old
`_asm_FUN_004216f0_004216f0` alias for the naked caller. This turn did not
rebuild or compare bytes, so exact placement and code identity remain
unverified.
