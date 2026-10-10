# 0x00437750 font atlas blend: equivalent recovery, 2026-10-10

`FontAtlas_BlendToSurface_00437750` locks a surface and blends the software
font atlas into it at (column, row), for A8R8G8B8, A4R4G4B4 and A1R5G5B5.
Nothing in retail calls it or takes its address. The C++ is
`matching2/msvc/equivalent/platform/font_atlas_blend_00437750.cpp`: 219 of 222
instructions identical, same frame, same registers, 645 bytes against 645.

## What decided the shape

- **Private convention from the parameter order.** Retail has the row in EAX,
  the atlas in EDX and the column in ECX, with surface, width and height on
  the stack (`ret 0xC`). The parameter order `(atlas, column, row, surface,
  width, height)` with a direct caller in the same link gives exactly that;
  the caller passes values from walked arrays.
- **One shared failure return** reached with `goto fail` (not ready, lock
  failed, unknown format), and the three formats as a `switch` whose `default`
  jumps there.
- **Loop counters `x` and `y` declared once, outside the switch**, and the row
  step written as `src += pitch - x * N`, which reuses the counter after the
  inner loop (the `add eax,eax; sub edx,eax` tails).
- **Destination channels as `int` locals** (`int blue = d[0]`) give the
  `movzx` load and the byte `add` narrowed by the store.
- **4-bit path: `green` is declared before `alpha_out`.** Both read `d[1]`.
  With `alpha_out` first the loaded byte lands in EDX, `green` gets a stack
  home (frame 0x4C) and the preceding `d[0] |= ...` is split into
  load/or/store. With `green` first the byte is loaded into EAX, copied to EDX
  for `green`, the frame is 0x48 and the `or BYTE PTR [edi],dl` stays whole.
  This one swap took the function from 659 to 645 bytes.
- **The low nibble is blended against the value just stored.** Retail masks
  the stored register in place (`and eax,0xf`), so the original code reads the
  destination nibble after it has been overwritten (it is always zero).

## The remaining difference

Retail computes the high nibble with a byte add and shift on the register it
then masks as 32 bits:

    sar eax,4 / add al,dl / shl al,4 / mov [edi],al / ... / and eax,0xf

- An `int` temporary (`* 16`, shipped) gives `add eax,edx; shl eax,4` and the
  mask one instruction earlier. Written `<< 4` the shift is distributed over
  the add (`shl edx,4; and eax,~0xf; add eax,edx`).
- A byte temporary or a direct `d[0] = ...` followed by `d[0] & 0x0F` gives the
  exact retail instructions for the store and the mask, but then the compiler
  also forwards the stored byte into `d[0] |= ...` (`or dl,al; mov [edi],dl`)
  and the whole function is allocated differently (46 instructions match).
- `unsigned char v; v &= 0x0F` keeps the `or` on memory but masks as a byte
  and zero-extends (`and al,0xf; movzx ebx,al`).
- The forwarding into `|=` stops only when the stored byte variable is
  redefined, with a surviving use, before the `|=` (for example reusing it for
  `d[1]`, which then loads `d[1]` too early). Dead or single-use
  redefinitions, a `volatile` access, signed/unsigned casts and a 16-bit pixel
  pointer do not stop it or change the load.

So the retail source has some natural redefinition of that byte variable that
was not found. The stored bytes are identical either way.
