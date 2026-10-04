# Effect spawn 0x0040B110: entry ordering controls

A fresh isolated native cluster confirms the previously reported 148-byte model.
It has the correct EAX kind, three stack slots including hidden result, RET12,
and every instruction following the entry window matches the retail body.
The candidate emits SHL EAX,4 before PUSH ESI / MOV ESI,[0x491C10]; retail places
it afterwards. No body was promoted.

Three distinct controls were measured:

- Turning off speed preference for this function emits 141 bytes, failing its
  complete 148-byte extent. The fixed compiler tool contract remains unchanged.
- Making the manager pointer volatile emits 150 bytes and retains the wrong
  SHL position. Do not add this qualifier to the shared production header.
- Unsigned rather than signed effect-kind parameter emits the identical complete
  148-byte machine body, verified by SHA-256. This type control is exhausted.

The cluster includes the complete existing allocation, registration and lookup
models; their declared extents remain complete. Scratch ownership uses a separate
additional-source wrapper to avoid double ownership with the exact 0x40B070
cluster. Production manifests, source/header files and byte gates are unchanged.

Receipts, native executables/maps, source variants and setup script are archived in
`matching2/build/experiments/effect_spawn_entry_order_2026_10_04`.
Scratch project is `/tmp/th10-effect-spawn/msvc`.

Avoid repeating these controls or the earlier parameter-order/table-address forms.
Further work needs a different compiler scheduling or actual type/context model.
