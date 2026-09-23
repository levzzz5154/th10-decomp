# Vector cross helper at `0x00421B90`

## Disposition

The 77-byte region remains a naked assembly entry. A normal MSVC 13.10 x86
C++ declaration cannot express its incoming register assignment: EAX holds
the destination pointer, ECX the left vector, and EDX the right vector. The
compiler's `__fastcall` uses ECX and EDX for its first two arguments and EAX
for a return value; it cannot accept a third pointer in EAX. This ABI blocker
prevents replacing the entry with ordinary C++ while preserving its retail
call interface.

## Ghidra evidence

The live Ghidra program is `/th10.exe`, the x86 little-endian PE at
`/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`. At `0x00421B90`,
Ghidra identifies `FUN_00421b90`, with the body from `0x00421B90` through
`0x00421BDC` inclusive (77 bytes, 28 instructions).

Ghidra's provisional signature is
`undefined __fastcall FUN_00421b90(float *param_1, float *param_2)`, with
`param_1` stored in ECX and `param_2` in EDX. Its decompiler separately shows
`in_EAX` as a phantom `float *` input, confirming that the destination pointer
is not part of the ordinary two-parameter signature. The listing begins with
`sub esp, 0xc`, reads the two three-float vectors through ECX and EDX, and
copies EAX into ECX at `0x00421BBB` before writing three floats at offsets
0, 4, and 8. It restores the 12-byte local area with `add esp, 0xc` and ends
with a plain `ret`, so the callee does not pop arguments from the caller's
stack.

Ghidra reports zero incoming xrefs, zero callers, zero callees, and no
call instructions. The function has no global-data references; its data
accesses are through the two input pointers and the output pointer. No caller
is available in the current image to corroborate the private register ABI.

## Recovered operation

Let `left` be the three floats addressed by ECX and `right` the three floats
addressed by EDX. The writes through the pointer passed in EAX are:

```text
out.x = left.z * right.y - right.z * left.y
out.y = right.z * left.x - left.z * right.x
out.z = right.x * left.y - left.x * right.y
```

These formulas compute `right × left` under the conventional cross-product
definition. The first two components are staged in the local stack area. The
third component's input products are loaded before the first output store, so
the observed instruction ordering preserves source values when the output
aliases either input. The routine performs no null checks.

## Symbol and verification limits

The source and `regions.json` currently use the canonical decorated symbol
`_asm_Vector3_Cross_00421b90`. Keep that raw symbol available for the region's
address binding; no separate alias declaration or other source reference to
this symbol was found in `matching2/msvc`.

The source retains the instruction sequence as inline assembly, but no rebuild
or byte comparison was performed. Byte identity of the resulting object or
linked image is therefore unverified.
