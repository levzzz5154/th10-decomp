# Key binding reassignment — 0x00430250

## Recovered behavior

The function updates one of five signed 16-bit key bindings stored at object
offset `0x59CC` (array stride two). It reads the old value for the selected
slot and returns immediately when the requested value is already present.
Otherwise it scans all five slots, excluding the selected slot, and replaces
every duplicate of the requested key with the selected slot's old key. It then
stores the requested key in the selected slot. Under the normal uniqueness
invariant this is a two-slot swap; the loop also defines behavior if corrupted
state contains multiple copies.

The caller at `0x0042F540` supplies the object in EAX, selected slot in ECX,
and newly polled joystick button in EDX at `0x0042F6D6..0x0042F6D8`. The caller
limits the selected slot to values no greater than four; the semantic body
keeps the observed five-slot indexing and does not add a bounds check.

## Helper effects

After changing the array, retail calls `0x0042F8B0` with the config object
still in EAX. Its Ghidra body reads the five values at `+0x59CC..+0x59D4` and
configures the displayed key labels, so the semantic source represents it as
`refresh_labels(state)`.

Retail next calls `0x0043DC90` with ECX=`0x00492590`, EDI=`10`, and a stack
argument of zero. Ghidra identifies this routine as the animation manager's
resource queue; the semantic source records the call as
`queue_resource(0x00492590, 10, 0)`. This evidence supports describing it as
an animation-resource queue operation; it does not establish an audio effect.

## Source and exactness limits

`matching2/msvc/src/game/key_config.cpp` now contains a semantic manifest
region with the original C symbol retained for the source definition. It uses
ordinary C++ and explicit arguments. The retail routine instead consumes its
receiver, slot index, and
new key from private EAX/ECX/EDX inputs, and its helper calls rely on that
register state. The semantic callbacks make the observed side effects
readable without preserving that private ABI. Its callback-injected C++
signature is therefore kept source-local; the shared retail anchor remains an
opaque declaration so it cannot be mistaken for a callable C++ ABI.

The earlier readable five-slot candidate measured 128 bytes against the
200-byte retail extent. That near-match is not byte-exact evidence for this
semantic interface. This conversion is behavior-oriented; it makes no claim
that the compiler output reproduces the retail extent or bytes.
