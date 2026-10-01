# Script-table sweep, indexed byte flags, and playback-state switching

Three complete functions, totaling 290 bytes, now compile as readable C++ without inline assembly. The maintained full build matches every byte of the 487,936-byte retail executable. The checkpoint contains 1,850 semantic regions / 97,005 bytes and 448 remaining assembly regions / 225,893 bytes. Five semantic functions still contain six inline x87 blocks; excluding those complete functions leaves 1,845 fully assembly-free semantic regions / 92,554 bytes. The full decompilation goal remains incomplete.

| Function | Address | Bytes | Native entry convention |
| --- | --- | ---: | --- |
| `ScriptTableSweep::Sweep` | `0x00403990` | 154 | Receiver EBX; plain RET |
| `ReadSignedByteFlag` | `0x0044A130` | 37 | Signed index AX, table ECX, output EDX, selected bit SI; result EAX; plain RET |
| `PlaybackState::SwitchPlaybackState` | `0x00427AE0` | 99 | Receiver EDI; plain RET |

## Script-table sweep

`matching2/msvc/src/render/anm_script_table_sweep.cpp` visits active entries in the script table. The table count and instruction opcode, length, and animation index are signed 16-bit fields. An entry's records begin at offset 0x1C. Each record selects an animation from the pool using its index and the genuine 0x3AC stride, calls the existing animation interpreter at 0x0043EE30, and checks the script cursor at animation offset 0x390. When none of the referenced animations has a cursor, the function clears active bit zero in the entry flags at offset three. Typed records, explicit reserved fields, and compile-time offset checks express these relationships.

Native LTCG derives the EBX receiver from the unselected compiler context. The complete 154-byte contribution matches; the context and layout gaps do not count toward recovered bytes. The existing entry and interior aliases remain bound to 0x00403990, 0x004039B0, and 0x00403A24. The recovered call at 0x004039E3 targets the genuine interpreter at 0x0043EE30. Ghidra independently confirms the record walk, signed fields, activity test, and clearing behavior; its inferred interpreter prototype omits the private ABI details established by the native call.

## Indexed byte flags

`matching2/msvc/src/input/indexed_flags.cpp` returns zero for a negative index. Otherwise it tests the high bit of the indexed signed byte, ORs the supplied bit into the output word when set, then reads the table byte again to decide its return value. The second read follows the word write because the byte table and output word can overlap. An explicit high-bit predicate generates the retail JNS branches; the initial signed-comparison spelling generated JGE instead. Both memory accesses and the complete 37-byte extent now match.

The layout selects this whole function only. Its array-walking context supplies AX/ECX/EDX/SI without assembly, and remains unselected. Ownership moves from the old unidentified assembly file to the input source; the previous record and `_asm_unassigned_0044a130` address alias are preserved.

The neighboring 43-byte mask reader remains assembly. A naturally shifted C++ model matches its bytes but has undefined behavior for indexes at least 32, and there is no demonstrated caller bound that excludes those indexes. A defined `_rotl(1u, index)` candidate reproduces its complete extent with one differing byte, selecting ROL where retail uses SHL. Neither candidate is promoted.

## Playback-state switching

`matching2/msvc/src/game/recovery_switch_playback_state_00427ae0.cpp` reads the requested mode from `[data_00477834 + 0x4474]`. In live mode it requests animation frame six on a transition and copies the coordinate words at 0x3C/0x40 to 0x4C/0x50. In playback mode it requests frame three on a transition and copies the saved words into 0x34/0x38. Both branches store the selected mode at offset 0x84. The source treats the coordinate payloads as words, preserving their bits without assuming a floating-point interpretation.

The common final assignment avoids constant propagation of a larger immediate-zero store in the live branch. Volatile coordinate and mode views preserve the observed load/store sequence. The recovered body uses ordinary C++ control flow and accesses; it has no compiler barrier or inline assembly. Shared headers declare `PlaybackState` and its four-byte stop-frame handle consistently for the selected body, genuine callee, and compiler context. Compile-time checks cover all accessed offsets.

The existing stop-frame cluster adds the genuine 99-byte function and its data binding. Both new call instructions, at 0x00427B03 and 0x00427B29, target the maintained `SetStopFrame` at 0x00449470 with the frame in SI. Native LTCG derives EDI for the playback receiver by seeing that real callee. All fourteen pre-existing complete functions remain exact: the expanded cluster probe checks fifteen regions / 913 bytes. Its synthetic context grows from 162 to 169 bytes and remains unselected. Ghidra confirms the branches and field copies, and the retained disassembly resolves its incomplete animation-frame inference.

## Verification and remaining evidence

The [checkpoint evidence](sweep_indexed_playback_2026-10-01.evidence.json) records the three new complete regions, current source and native-input hashes, focused probe results, whole-build compiler provenance, preserved aliases, and decoded call targets. It checks the contiguous 412,672-byte `.text` partition and source ownership. Fresh native compilation uses no retail bytes, masks no bytes, and changes no instruction or address-operand bytes during extraction.

The full command was:

```sh
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
```

All 1,912 maintained source builds succeeded. Full executable SHA-256 is `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`; `.text` SHA-256 is `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`. `git diff --check` also passed.

Scratch evidence under `matching2/build/experiments/` remains available for the rejected candidates:

- `configuration_timer_followup_2026_10_01`: complete 130-byte playback timer has two differing bytes, both ECX/EDX mode-temporary allocation; the 116-byte timer has seven. New getter, conversion, and formal-order spellings reproduce those residuals. Seven additional models under `subagent_independent_2026_10_01/timer_subobjects` use actual arrays and nested records to make all output accesses defined, with identical playback bytes. The best defined array model and its current native-input hashes are retained in `typed_output.evidence.json`; the assembly regions are unchanged.
- `subagent_application_batch_2026_10_01`: complete 57-byte batch loop has sixteen differing bytes in its prologue and epilogue; the loop itself matches. Native compilation saves the resource receiver inside the count guard, while retail captures it eagerly. Its genuine LoadScript anchor matches all 203 bytes.
- `subagent_no_inline_x87_2026_10_01`: the audited five semantic functions retain 4,451 bytes of selected code containing inline assembly. A complete GCC intrinsic rotated-builder candidate emits FSINCOS without assembly, but its measured 452/599/634-byte variants fail the original 591-byte body. The frame, comparison instructions, scheduling, and private callee conventions remain unresolved. These functions are included in the semantic count but excluded from the fully assembly-free count above.

The manifest retains each original assembly ownership record in `previous_record`. Historical checkpoints describe their own verified states; this note records the newer combined state.
