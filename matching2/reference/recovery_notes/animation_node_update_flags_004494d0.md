# Animation flag update at `0x004494D0`

Ghidra now defines one 89-byte function at `0x004494D0`. The old manifest
split its body into a 63-byte region, a one-byte NOP overlay, and a 25-byte
loop tail at `0x00449510`. The disassembly shows the first body jumps to that
tail, which walks the linked list and returns. The NOP at `0x0044950F` is an
internal alignment byte, so the manifest now assigns the complete span to one
function and removes the old standalone tail source and data overlay.

The routine looks up an object using the receiver's first field and global
context `0x00491C10`. If lookup succeeds, it clears flag bit 1 and sets bit 17
on the object. When its field at `+0x18` is zero, the same transition is
applied to each linked object starting at `+0x14`; links hold an object pointer
at `+0` and their next pointer at `+4`. The meaning of bit 17, exact class
name, and original method name remain unknown.

The maintained source expresses this behavior in
`AnimationNode_004494D0::UpdateFlags()`. The schema-1 LTCG context attempts to
establish the EAX receiver. The 89-byte compiler contribution and private ABI
are unverified; no build or probe was run.
