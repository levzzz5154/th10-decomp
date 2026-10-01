# Overlay draw callback at `0x0043C500`

The maintained callback is now readable C++ with an exact retained ordinary
MSVC/LTCG probe for its complete **74-byte** body. Its source, cluster layout,
driver, shared helper sources, and header are identical to the recorded
compiler inputs. The manifest preserves the complete former assembly record
and its original symbol alias. Integration evidence is in
[the resource and overlay checkpoint](resource_load_size_and_overlay_2026-10-01.md).
A fresh whole-project build remains pending.

The receiver arrives in ECX. The callback reads alpha at `+0x18` and color at
`+0x24`, combines `(color & 0x00ffffffu) | (alpha << 24)`, builds rectangle
`{32.0f, 16.0f, 416.0f, 464.0f}`, and returns integer 1 with plain RET. The
source asserts both field offsets. Retained original/native disassembly
confirms the rectangle reaches `0x0043BDA0` in EDI and color in EBX.

The callback calls the genuine `DrawSolidQuad` source. The driver includes
its complete 483-byte body and the complete 133-byte animation batch flush
at `0x00442F50`, allowing LTCG to recover their private register conventions.
Both unselected helpers independently match every original byte and their
MAP contributions have the original complete lengths. Their existing main
owners remain unchanged; they add zero recovered bytes in this checkpoint.
The unselected array walker is compiler context.

The previous note described an unverified candidate that expanded helper
behavior into the callback. That candidate has been superseded by the
complete-helper cluster. No opcode rewriting, operand rewriting, masked
bytes, or oracle code in the build was used. The independent repeatable
audit is `matching2/build/experiments/ascii_overlay_2026_10_01/audit_overlay.py`.
