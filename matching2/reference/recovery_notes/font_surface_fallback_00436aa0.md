# 0x00436AA0 font surface create with fallback

76 bytes, no caller in retail: it is the out-of-line copy of a helper whose one
call (in the font cache initialiser at 0x00437A00) was inlined. Formats 0x19
and 0x1A fall back to 0x15, 0x17 to 0x16.

Retail's copy takes the surface in EBX, the width in EDI, the height in ESI
and only the format on the stack. To get that:

- it lives in its own schema-1 cluster (`font_surface_fallback_00436aa0`);
  a schema-2 cluster cannot keep an unreferenced function, and a root would
  pin the declared `__stdcall` frame;
- the context `#include`s the real release and create bodies as ABI anchors
  at their retail addresses, so the create keeps its EAX surface argument;
- the synthetic caller is compiled under `#pragma inline_depth(0)`, which
  keeps the call out of line without marking the helper `noinline`.

The same recipe should serve other caller-less out-of-line copies.
