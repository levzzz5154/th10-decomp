# Animation-manager destructor and array unwinds: exact C++

The complete 206-byte animation-manager destructor at 0x00446220 is now
readable C++ in `src/render/anm_storage_destructor_00446220.cpp`, without inline
assembly. Its native member ownership generates all three retail unwind
functions and the EH handler:

| Address | Size | Contribution |
| --- | ---: | --- |
| 0x00446220 | 206 | Animation-manager storage destructor |
| 0x004651E0 | 28 | 4,096-sprite pool unwind |
| 0x004651FC | 14 | Middle sprite unwind |
| 0x0046520A | 27 | 20 layer-sprite unwind |
| 0x00465225 | 10 | Destructor EH handler |

The class represents the actual 0x732460-byte storage: pooled sprites begin at
+0x68, the middle sprite is at +0x3AD130, and layer sprites begin at +0x72DAE4.
Compile-time checks verify all three offsets and the full extent. The sprite
type uses the same common 0x3AC-byte ownership as `GameThreadSlot`, through an
animation-sprite typedef. Its owned resource is at +0x358.

The destructor drains both update lists, saving each next node before calling
the recovered RemoveVm algorithm. The compiler then destroys the layer array,
middle sprite, and pooled array in member order. This yields the two native
CRT vector-destructor calls and the inlined middle-resource free at owner
+0x3AD488. It also yields retail's EH state changes and its complete 52-byte
unwind map/FuncInfo at 0x00471274.

An existing title compiler context had an ordinary 193-byte version of this
owner with matching unselected unwind functions. The new dedicated native
LTCG cluster compiles the destructor with the full RemoveVm and Entity_Init
helper bodies. Native visibility assigns the manager to EDI and the removed
VM to ESI, reproducing both retail loops and the complete 206-byte destructor.
The shared sprite destructor is exported only in compiler context to preserve
its public ECX callback ABI; the export is absent from the final image.

The unselected RemoveVm contribution is 268 bytes in this context, rather than
the 282-byte retail owner. Its full emitted extent is declared and its gap
starts at 0x00448CBC; no helper bytes are truncated or selected for recovery.
The independent exact RemoveVm owner remains unchanged. The Entity_Init helper
accepts a code-section macro so this link can lay out its native contribution;
the existing title cluster keeps the original default section.

The production probe matches all five selected contributions with zero byte
differences, and validates all 52 exception-data bytes. Live Ghidra decompilation
confirms the two list-draining loops, member array destruction, middle-resource
free, and exception-state progression. Native PE/MAP files, final source and
layout snapshots, Ghidra output and unmasked SHA-256 comparisons are retained
under `matching2/build/experiments/anm_storage_destructor_2026_10_04`.

The four old naked sources were deleted. The EH handler was previously
attributed to `newopnt.obj`; it now belongs to the actual application destructor,
with its prior record retained as provenance. Existing title compiler anchors
and their selected title/score owners remain intact.

The normal full build passes outside the three preexisting equivalent C++
regions. `make EXACT=1` passes too: the whole 487,936-byte executable matches
retail with those preexisting equivalent regions using their assembly fallbacks.
Ordinary exact C++ is now 2,180 regions / 161,827 bytes. Remaining
assembly is 135 regions / 127,742 bytes, so the full objective is incomplete.
