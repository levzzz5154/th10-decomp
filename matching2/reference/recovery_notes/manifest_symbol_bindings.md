# The manifest's `symbols` table binds calls in plain translation units

2026-09-18. `regions.json` carries a `symbols` map (5,284 entries) from a symbol
name to an address - `_data_00491c10` -> `0x00491C10`,
`_asm_Recovery_LoadCachedResource_00447280` -> `0x00447280` and so on. It is what
lets **plain** translation units, not only clusters, resolve references to the
assembly around them: a declaration whose emitted name is in the table links
against the retail address without any cluster machinery.

Measured on `0x00445880`: adding `?Issue@Manager_00445880@@QAEXII@Z` ->
`0x004450E0` to the table and compiling the region as an ordinary member function
in a plain unit produced a clean build with the call resolved - so the *member*
declaration, and therefore the ECX-plus-two-callee-popped-stack-arguments shape,
works outside the cluster path too.

The plain path is worth preferring wherever the region's entry convention is
already expressible (a `__thiscall` member, or a stack-only function), because it
avoids the whole-program pass' liberty to re-choose conventions - the wall behind
`0x0041C880` and `0x0043C8B0`. The comparison on `0x00445880` shows why neither
path is a silver bullet though: in a plain unit the compiler reads the field
through `ecx` (`8b 81 58 03 00 00`), pushes EAX and loads the manager early, while
retail copies `this` to EAX first (`8b c1`), reads through `eax`, pushes ECX and
loads the manager after the pushes.
