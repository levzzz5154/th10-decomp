# Texture surface clear (`0x00449700`)

## Disposition

No semantic body was promoted. The 111-byte source region remains the exact
naked wrapper in `src/unidentified/FUN_00449700_00449700.cpp`. The behavior is
recoverable with high confidence, but its input arrives in EAX, which an
ordinary MSVC x86 C++ free-function signature cannot express. Ghidra also has
no function or caller xref at this address, so there is no known caller whose
register setup could anchor an ABI-aware cluster.

## Boundary and Ghidra evidence

Live Ghidra MCP queries against `th10.exe` on 2026-09-23 returned:

- `get_function_by_address(0x00449700)`: no function found.
- `get_xrefs_to(0x00449700)`: no references found; consequently no direct
  callers are known.
- `get_xrefs_from(0x00449700)`: no references found. The body uses indirect
  COM dispatch, which does not yield direct callee xrefs.
- `disassemble_bytes(0x00449680, 384)` decoded the candidate from
  `0x00449700` through its `RET` at `0x0044976E`, then an `INT3` at
  `0x0044976F`; the next instruction-aligned sequence begins at `0x00449770`.
- Ghidra recognizes the later `FUN_004497D0`, whose seven callers and direct
  callee `FUN_004491C0` do not establish a relationship with this body.

The manifest records exactly 111 bytes at `0x00449700`. Although Ghidra has not
typed them as a function, the retail code begins at a 16-byte boundary with a
complete stack-frame setup (`sub esp, 0x2c`, save EDI), restores EDI and the
frame, and ends in a plain `ret`. The following `INT3` and aligned next code
sequence support treating `0x00449700..0x0044976E` as a complete body rather
than a fragment. This is a byte-boundary conclusion, not proof of a direct
caller.

## Recovered behavior and register contract

The entry consumes a pointer-to-texture-pointer in EAX:

1. Load the texture object from `[*EAX]`.
2. Indirectly call the texture vtable at `+0x48` with level zero and a local
   output slot. This is consistent with `IDirect3DTexture9::GetSurfaceLevel`.
3. Call the returned surface's vtable at `+0x30` with a local description
   record, then `+0x34` with a local locked-rectangle record, null rectangle,
   and zero flags. These slots and arguments are consistent with
   `IDirect3DSurface9::GetDesc` and `LockRect`.
4. Clear `lockedRect.Pitch * desc.Height` bytes starting at
   `lockedRect.pBits`, using `rep stosd` plus a byte tail.
5. Call surface `+0x38` (`UnlockRect`), then call `+0x08` (`IUnknown::Release`)
   if the local surface pointer is non-null.

The interface names are an inference from the vtable offsets and argument
shapes. Microsoft documents `GetSurfaceLevel(0, &surface)` as returning the
top-level surface and incrementing its reference count, and documents
`LockRect` as filling a `D3DLOCKED_RECT` that must later be unlocked. See
[GetSurfaceLevel](https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3dtexture9-getsurfacelevel),
[LockRect](https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3dsurface9-lockrect),
and [UnlockRect](https://learn.microsoft.com/en-us/windows/win32/api/d3d9helper/nf-d3d9helper-idirect3dsurface9-unlockrect).

The local layout explains the zero length: `D3DSURFACE_DESC.Height` is at
`[esp+0x2c]`, `D3DLOCKED_RECT.Pitch` at `[esp+0x8]`, and `pBits` at
`[esp+0x0c]` after the calls return. The code does not use the width and does
not check any HRESULT. It returns the EAX value left by `Release` when the
surface pointer is non-null; if that pointer is null, the tested EAX is zero
and that zero reaches the plain `ret`.

The only established input is the pointer held in EAX. The function has no
stack arguments, uses a plain `ret`, and saves/restores EDI. ECX and EDX carry
the indirect vtable call setup; the standard volatile registers are otherwise
not preserved. An earlier IDA-based candidate ledger independently recorded
`int __usercall sub_449700@<eax>(_DWORD *a1@<eax>)`, consistent with this
interpretation, but it does not supply caller evidence.

## Next useful lever

Recover the source/caller path that places the texture-pointer address in EAX,
then try the whole call cluster in an ABI-aware native-LTCG context. Do not
map this body to an ordinary C++ symbol based on a stack-argument prototype:
that would change how the input is delivered even if the COM behavior matched.
