# `__amsg_exit` at `0x0045373D`

## Current production state

Checked 2026-09-30: `matching2/msvc/regions.json` still classifies this
37-byte interval as the toolkit-library entry `__amsg_exit` from
`wincrt0.obj`. The readable model in
`matching2/reference/semantic_candidates/amsg_exit_0045373d.cpp` remains an
unintegrated candidate. It must not be described as a maintained semantic
region until the exact build gate passes.

Ghidra identifies a cdecl error-code input, conditionally calls
`FF_MSGBANNER` when `data_0047720c == 1`, reports the code through
`0x00458EFD`, then calls the `__exit` function pointer at `0x00473070` with
`0xFF`. The retail sequence is:

```text
cmp [0x47720c], 1
jne skip_banner
call 0x45909f
skip_banner:
push [esp+4]
call 0x458efd
push 0xff
call dword ptr [0x473070]
pop ecx
pop ecx
ret
```

## Byte-matching probes

An isolated probe with the pinned Clang i386 profile confirmed the first 23
bytes, including the condition and both direct calls. The remaining mismatch
is the indirect exit and cleanup sequence:

- With a volatile function-pointer slot, Clang emits a 37-byte body but loads
  the pointer to EAX and calls through EAX, followed by `pop eax; ret`.
  Retail calls directly through `[0x473070]` and uses `pop ecx; pop ecx; ret`.
- With a nonvolatile slot, Clang emits the direct absolute indirect call, but
  the body is 38 bytes and ends in `add esp, 4; ret`, one byte longer than the
  two retail pops and `ret`.

The probe declared `0x00458EFD` with a callee-pop attribute to preserve the
retail placement of its pushed argument. The real `__NMSG_WRITE` entry is
cdecl, so that declaration is only a code-generation model for this terminal
path. The candidate has not been promoted; the production manifest remains on
the original library region.
