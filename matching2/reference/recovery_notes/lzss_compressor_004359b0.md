# LZSS compressor `0x004359B0`

Date: 2026-09-23

Status: retained retail assembly. This pass used read-only live Ghidra MCP
queries against `th10.exe`; it did not change the compressor body, build,
probe, or test the project.

## Live boundary and ABI

Ghidra reports one function at `0x004359B0` with body ending at
`0x00435DB4`; the `RET 0x0C` at `0x00435DB2` makes the byte interval
`[0x004359B0, 0x00435DB5)` exactly 1029 bytes. The current manifest also
assigns 1029 bytes. The source comment above the retained body has been
corrected to describe the full extent; the assembly is unchanged.

The effective live ABI is `byte * __stdcall(byte *input, int input_size,
int *output_size)`: it accepts three stack arguments, returns the allocated
compressed buffer in `EAX`, and pops the arguments itself. Ghidra's function
metadata types the inputs but leaves the return type undefined; the return
value follows from the body and both callers rely on it and on callee cleanup:

| Caller | Call instruction | Evidence after return |
| --- | --- | --- |
| `FUN_00429B60` | `0x00429E5D` | Reads the returned pointer from `EAX`; there is no `add esp, 0x0C`. |
| `FUN_0042B1E0` | `0x0042B315` | Immediately moves `EAX` to `EDI`; there is no caller cleanup. |

`matching2/msvc/include/asm_symbols.hpp` currently declares this entry as
`void __cdecl asm_FUN_004359b0_004359b0()` with no parameters. A readable
definition cannot replace that declaration in `score_save.cpp` alone while
preserving the observed return type, argument layout, stack cleanup, and link
symbol. Correcting the declaration and the semantic symbol/manifest entry is
a coordinated change outside this pass's source ownership.

## Behavior and dependencies

Live Ghidra identifies three direct callees: allocator `0x00452706`, match
tree insertion `0x00436000`, and tree deletion `0x00436210`. The checked-in
`MemoryFile_RemoveNode` symbol name for `0x00436210` is stale: its live body
operates on the compressor's match tree. The insertion helper has already been recovered as semantic
`Lzss_InsertString_00436000` in `score_save.cpp`. The deletion helper remains
assembly and takes its node index in `ECX`; it calls the predecessor search
at `0x00436330`, relinking helper at `0x00436260`, itself recursively, and
replacement helper at `0x004362B0`. These routines mutate the same 12-byte
node records rooted at `0x00477858`. Their private register contracts are
not represented by the generic C declarations in `asm_symbols.hpp`.

On allocation success, the compressor first writes zero to `*output_size`,
clears the `0x2000`-byte ring window at `0x0048F868` and the corresponding
tree storage, initializes the tree/window globals, and primes up to 18 input
bytes. It emits a literal for match lengths below three; longer matches emit
an MSB-first flag, a 13-bit ring position, and a four-bit length-minus-three.
For each consumed byte it removes the expired ring node and asks
`0x00436000` to update the best match. At end of input it writes the final
padding bits, stores the produced byte count through `output_size`, and
returns the allocation. The caller owns and frees the returned buffer.

The allocation-failure path returns null before touching `*output_size`;
that observable detail should be kept if the function is rewritten. The
decompiler shows comparisons of zero-extended input bytes with `0xFFFFFFFF`;
those comparisons cannot match, so this pass does not assign sentinel-byte
semantics to `0xFF`.

## Recovery decision

An earlier readable candidate measured 622 bytes against the 1029-byte live
function and did not preserve the retail compiler schedule. That mismatch
alone does not prevent a semantic implementation, but a correct production
replacement still needs a properly declared `__stdcall` public entry and a
typed route through the register-ABI tree deletion helpers. The current
`score_save.cpp`-only ownership cannot make the public ABI declaration
consistent, and the other files that define that ABI were explicitly outside
this pass. The assembly body is therefore retained until the symbol and
compression-tree interfaces can be updated together.
