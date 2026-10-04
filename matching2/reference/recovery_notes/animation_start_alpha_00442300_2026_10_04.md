# Primary alpha interpolation starter: exact C++

The complete 130-byte primary alpha starter at 0x00442300 is now C++ in
`src/render/animation_start_byte_interpolation_00441f50.cpp`, as
`AnimationInterpolatedObject::StartChannel108`. It shares the established
animation interpolator layout and FrameTimer_Restart implementation. A new
compile-time assertion checks the primary channel's +0x108 offset.

The method clears both control fields before assigning its duration, easing
mode, initial alpha and goal alpha, then restarts the interpolation timer.
This source ordering reproduces native LTCG's private EAX object / ECX duration
ABI, with all three byte arguments on the stack and RET 12. The prior candidate
put one byte in EDX and returned with RET 8. The corrected ordering was present
in the later full animation-VM C++ model and was tested here independently.

The existing byte/color interpolation cluster now owns all four complete
functions: primary alpha 130 bytes, secondary alpha 116 bytes, and both color
starters 208 bytes each. Its synthetic array caller invokes all four methods;
its complete native extent is 157 bytes. All four production probe windows are
EXACT, with no byte patches, masks, assembly helpers or truncated contributions.

The old naked body was removed from recovery_leaves.cpp; its other maintained
regions remain in that source. Region provenance retains the old record.
Live Ghidra decompilation confirms both control clears, the widened byte values,
the conditional timer initialization, and the final timer reset. Native probe
artifacts, source/layout snapshots and Ghidra output are retained under
`matching2/build/experiments/animation_start_alpha_2026_10_04`.

Both normal and exact-mode full builds pass. Independent cmp confirms the
complete 487,936-byte exact-mode executable equals retail. The normal build
retains the three preexisting equivalent C++ regions. Ordinary exact C++ now
covers 2,181 regions / 161,957 bytes; assembly remains in 134 regions / 127,612
bytes. The full inline-assembly-free objective is therefore still incomplete.
