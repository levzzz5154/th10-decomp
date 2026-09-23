# Curve wrapper at `0x00441D90`

Ghidra MCP confirms this is a 20-byte leaf wrapper around the curve kernel at
`0x0044C350`. The receiver arrives in EAX. The wrapper reads elapsed time at
`+0x18`, converts the signed duration at `+0x24` to float, and passes the
operation at `+0x28` with those two values to the kernel. The returned float
remains in ST0, and the wrapper uses plain `RET`.

The C++ source model uses a member returning `float` and mirrors the promoted
wrapper at `0x00441D70`, including its native-LTCG synthetic caller and kernel
anchor. The source has no inline assembly. Ghidra's function name and header
comment were updated to record the recovered fields and register ABI.

This promotion is based on the same source and call shape as the exact
`0x00441D70` twin, with the field offsets adjusted to match this entry's
disassembly. The `0x00441D90` source has not yet been run through the focused
probe or whole-image build, so its byte match remains unverified.

## Sibling wrapper at `0x00441DB0`

Ghidra MCP also confirmed the 20-byte wrapper at `0x00441DB0` has the same
instruction and call shape, using elapsed time at `+0x28`, signed duration at
`+0x34`, and operation at `+0x38`. It calls the same kernel and returns its
float in ST0. Its source, LTCG driver, and region entry now use the same model
with those offsets. Ghidra's function name and header comment record the
recovered ABI and fields. As with `0x00441D90`, this is not yet byte-probe or
whole-image verified.
