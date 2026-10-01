# Key binding reassignment — 0x00430250

The [2026-10-01 native checkpoint](runtime_and_helpers_2026-10-01.md) recovers all **200 bytes** as readable C++ without inline assembly. The maintained whole executable is byte-exact. The earlier callback-based semantic candidate is superseded.

The function updates five signed-short bindings at object `+0x59CC`, stride two. It returns when the selected binding already matches the requested key. Otherwise five explicit duplicate checks swap other copies with the selected slot's old key, then store the requested key. The first duplicate check uses the cached old key; the remaining checks reload the selected binding. The caller limits the selected slot to zero through four, and the body preserves the original indexing without an added guard.

The actual entry receives state in EAX, slot in ECX, and key in EDX, with plain RET. It calls the genuine label refresh at `0x0042F8B0` with state EAX, then `SoundQueue::Queue` at `0x0043DC90` with queue ECX, ID 10 in EDI, and stack request zero. Native LTCG derives those conventions from complete original helper models; the maintained source has no callback substitutions.

The maintained source is `matching2/msvc/src/game/key_config.cpp`, with `layout/ltcg/key_config_reassign.json`. The old `_asm_KeyConfig_ReassignSlotRetail_00430250` alias and original region record are preserved. Complete Refresh (2,452 bytes), Queue (123), and Find (73) anchors are exact. Configure's complete 356-byte model has six differences in two float addresses, remains unselected, and contributes no recovered bytes.

The [checkpoint evidence](runtime_and_helpers_2026-10-01.evidence.json) checks the maintained full 200-byte native extent, original call targets, current inputs, and exact executable. This recovery has zero masks and zero instruction/address rewrites. The earlier 128-byte loop model was a failed compiler candidate and is not used.
