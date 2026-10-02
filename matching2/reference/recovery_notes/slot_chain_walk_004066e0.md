# 0x004066E0 slot chain walk

`SlotOwner_004067a0::AdvanceSlot`, 134 bytes, promoted from the ABI anchor in
`enemy_slot_advance_004067a0`.

- The draw dispatcher at 0x004451C0 takes the sprite in EAX and the manager in
  ECX. Declaring it `__fastcall` put the sprite in EDX; the cluster now carries
  the same small `__cdecl` stand-in the player sprite cluster uses, so LTCG
  derives the pair.
- With plain member stores the compiler hoisted the flag load and the z copy
  above the float stores and tested the flag in a register (135 bytes).
  Copying the position through two `Vec3*` locals keeps the stores in source
  order and gives retail's `test dword ptr [esi+364h], imm32`.
- The quarter turn is 0x3FC90FDB (`1.5707964f`), not `1.5707963f`.
