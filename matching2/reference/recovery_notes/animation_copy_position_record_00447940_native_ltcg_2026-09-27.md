# Animation position record copy, 0x00447940

Recovered all 143 bytes as readable C++ with no inline assembly. The normal
native-LTCG probe reports zero differing bytes and no relocations. This
supersedes the private-ABI blocker formerly recorded in the maintained source.

Fresh live Ghidra analysis confirms the actual inputs: index in EAX, manager in
EDX, source record in EBX, plain RET. The destination array pointer is at
manager +0x118; each record occupies 0x44 bytes. The function copies the whole
record, calculates four normalized coordinates, and calculates two scale
factors using the source dimensions at +0x38 and +0x3C.

The recovered aggregate assignment naturally emits `rep movsd` for 17 words.
Repeated typed destination expressions preserve the retail array-pointer
reloads and x87 operation order. A synthetic indexed traversal establishes the
private argument registers. It is compiler context only and contributes no
recovered bytes. No barriers or instruction transformations are needed.

Maintained artifacts:

- `src/render/animation_manager_copy_position_record_00447940.cpp`
- `layout/ltcg/copy_position_record.json`
- `layout/ltcg/copy_position_record_context.cpp`

Scratch evidence is under `matching2/build/experiments/copy_position_record/`.
The complete function body SHA-256 is
`04a35315b06c19a0bf69b3c2dc617701daf001ed6e5e67f7a0465a8e3f5ddb82`.
The initial native contribution was already 143 bytes; correcting the declared
symbol to the compiler's default stdcall decoration and the synthetic context
extent to 46 bytes allowed the normal exact probe to pass. Promotion re-probes
the final source and layout before updating the maintained manifest.

Whole-executable validation is recorded in the current recovery checkpoint.
