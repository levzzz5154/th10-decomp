# 0x0043A5C0 private-ABI audit

## Disassembly boundary and references

The active Ghidra program is `th10.exe` (`x86:LE:32:default`). Ghidra has no
Function defined at `0x0043A5C0`, so the live listing does not establish a
function object or prototype there. It does disassemble the manifest-owned
range `0x0043A5C0..0x0043A5FE` as 23 instructions spanning exactly 63 bytes.
The preceding instruction sequence returns at `0x0043A5BC`; `0x0043A5BF` is
`INT3`. This body returns at `0x0043A5FE`; `0x0043A5FF` is `INT3`, and the next
manifest-owned function starts at `0x0043A600`.

Bulk xrefs over every byte in the range found no incoming reference. The only
in-range control-flow xref is the loop back-edge from `0x0043A5EE` to
`0x0043A5E6`. Outgoing references are:

- `0x0043A5C3` reads the stack-cookie global at `0x00473660`.
- `0x0043A5D6` calls through the import slot at `0x00466294`. Ghidra resolves
  the slot to `midiOutGetDevCapsA`.
- `0x0043A5F6` calls `__security_check_cookie` at `0x00458EA5`.

## Behavior and ABI

The entry saves `cookie ^ ESP` at `[ESP+0x34]`. It then calls
`midiOutGetDevCapsA` with the device identifier in `ECX`, a local `0x34`-byte
capabilities record, and `0x34` as the record size. The code reads the record's
name at local offset 8 and copies bytes, including the first NUL, to the
destination address held in `ESI`. It does not inspect the API return value or
bound the copy by a destination capacity. The API name and the argument order
identify the record as `MIDIOUTCAPSA`; the field interpretation follows from
that identification and the fixed offset used by the instructions.

The epilogue reloads and unmasks the saved cookie, then passes it in `ECX` to
`__security_check_cookie`. The helper compares it with `0x00473660`, returns on
a match, and jumps to the failure routine on mismatch.

The required live-ins are `ECX` for the device ID and `ESI` for the destination
pointer. Ordinary MSVC x86 C++ signatures cannot place a second parameter in
`ESI`: `__fastcall` uses `EDX` for its second register parameter, and the other
standard conventions use stack parameters. A typed ordinary C++ conversion
would therefore change the calling contract. The byte-preserving naked body
remains the faithful representation until a real caller or native LTCG cluster
provides the private register contract.

## Link symbol

The current `regions.json` row owns 63 assembly bytes at `0x0043A5C0` under the
canonical linker symbol `_asm_FUN_0043a5c0_0043a5c0`. Ghidra has no function
entry or static caller references for a separate `FUN_0043a5c0` alias, so the
live evidence does not require a second raw alias. Keep the existing canonical
symbol while this assembly region is retained; any later semantic rename must
preserve the manifest's required symbol or provide an explicit alias.
