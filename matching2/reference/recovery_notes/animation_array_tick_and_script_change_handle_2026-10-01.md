# Animation array tick and script-change handle

2026-10-01. Two complete assembly regions, totaling 80 bytes, are now ordinary
C++: the 44-byte animation array tick at `0x00441590` and the 36-byte handle
script-change wrapper at `0x004496D0`. Both pass the normal focused native-LTCG
probe without masking or rewriting instructions or address operands.

## Animation array tick

`src/render/animation_array_tick_00441590.cpp` walks `count` consecutive
animations with stride `0x3AC`. It calls the genuine VM at `0x0043EE30` only
when the current animation's signed 16-bit script index at `+0x38A` is
nonnegative. Compile-time checks verify the stride and index offset. The count
is unsigned so decrement uses the original 32-bit wrapping arithmetic.

Native LTCG retains array ECX and count EAX, with plain RET. A top-tested
`while (count)` gives retail's initial TEST EAX, unconditional ESI save, and
conditional EDI save. The earlier do-while candidate had the same 44-byte
extent and exact loop tail, but saved EDI and copied the count before testing
it; its first ten bytes differed. The final complete contribution includes
the six-byte loop-alignment LEA and both exit paths.

The 7-byte native compiler context at `0x00441600` is unselected. Its layout
gaps are also unselected. The VM declaration models its real stack object
argument and RET4. Ghidra's current disassembly confirms the signed comparison,
stride, stack call and conditional register save. Its decompilation includes
phantom ECX/EDX VM parameters; these are not meaningful inputs to the VM body.

## Script-change handle

`src/render/animation_handle_change_script_004496d0.cpp` finds the handle's
animation in the global manager, then changes that object's current resource
to the requested script. The handle arrives in EAX; the script index stays on
the stack and the wrapper returns with RET4. The ID is a four-byte record,
which preserves the lookup's stack argument. The lookup result remains in
EAX for the script changer; the index goes into ECX and resource into EDX.

The compiler sees the complete real lookup and a semantic script-change body
as unselected ABI anchors. The lookup's entire 73 bytes match retail. A typed
pair for script base/cursor and references to slot words reproduce the script
changer's full mask and clock-store schedule. That anchor has the original
287-byte extent, but 22 bytes differ in ESI/EDI allocation and entry order.
It is not exported or counted as recovered. The final executable still calls
the genuine 287-byte assembly region at `0x0043E8B0`.

The native context and anchors cannot contribute recovered bytes through this
scope. Only the complete 36-byte wrapper is exported. Field checks cover the
ID/handle extent, resource table and loading flag, manager counter and both
lookup buckets. Live Ghidra caller/callee evidence confirms these offsets and
the object EAX/resource EDX/index ECX script-change convention.

## Verification and remaining work

The complete 487,936-byte executable matches the oracle byte-for-byte; its
.text interval is also exact. The focused probe covers two regions / 80 bytes. Its native reports record
fresh source/header/layout hashes, zero masked bytes, zero changed instruction
or address bytes, and no retail bytes used for building. The companion evidence
record contains the focused result, machine call targets, complete anchor
comparisons, Ghidra results and full executable verification.

The final manifest has 1,847 semantic regions / 96,715 bytes and 451 assembly
regions / 226,183 bytes. Semantic regions account for approximately 30.0% of
the tracked semantic-plus-assembly function bytes. Runtime libraries remain
325 regions / 66,500 bytes. Some previously classified semantic regions still
contain inline x87 blocks, so the fully assembly-free objective remains active.

The retained subagent timer candidates are not promoted: animation timer
`0x00441F50` is 116/116 bytes with seven differences, while playback timer
`0x00442300` is 130/130 with 33 differences. A one-byte aggregate playback
mode establishes the observed three stack arguments and RET12. The script
changer's 22-byte allocation residual also remains for a future recovery.
