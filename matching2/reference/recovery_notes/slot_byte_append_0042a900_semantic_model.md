# Slot byte append at `0x0042A900`

`0x0042A900..0x0042A925` is a 38-byte leaf that appends one byte through a
cursor stored at object offset `+0x6274`. The readable model is in
`matching2/msvc/src/unidentified/unassigned_0042a900.cpp`.

## Behavior

The retail instructions load the cursor and write the input byte through it,
then reload the cursor at `+0x6274`, increment it, and store it back. They
compute the advanced cursor's signed 32-bit offset from the object, subtract
`0x5464`, and return whether the result is at least `0x78`. The model now
preserves that reload order and expresses the signed comparison with 32-bit
address arithmetic. For a valid cursor into the byte array beginning at
`+0x5464`, the function reports true after the cursor advances 120 bytes.

The layout places the byte array at `+0x5464` and the cursor pointer at
`+0x6274`, matching the neighboring cursor accessor documented in
`00420b60_0042cdd0_wave18.md`.

## Retail ABI and reference status

The private entry ABI is:

| Value | Location |
| --- | --- |
| Buffer object | `EAX` |
| Byte to append | `DL` |
| Boolean result | `EAX` (`0` or `1`) |
| Stack arguments | None |
| Return | Plain `RET` |

There is no call instruction in the body. Ghidra's `get_function_by_address`
did not find a function boundary at `0x0042A900`, and `get_xrefs_to` returned no
references to the entry, so no direct caller or callee was identified. These
results do not rule out an indirect dispatch path.

## Model status

The source contains ordinary C++ and no inline assembly. Its `__cdecl`
object-and-byte parameters are an explicit semantic interface only; they do
not model the retail `EAX` receiver and `DL` input. The existing C-linkage
symbol spelling is retained for the current manifest reference, but this
change does not promote the manifest region or establish byte equivalence.
No build, probe, or test was run for this model.
