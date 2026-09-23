# CRT environment and 64-bit conversion entries

Live Ghidra audit of `th10.exe` for `0x0045E0E4`, `0x0046074C`,
`0x0046077D`, `0x00461E83`, and `0x00461ED0`. The five current manifest
entries were assembly rows when audited. This pass changes only the two
64-bit conversion source files; it does not edit the manifest or shared
symbol declarations.

## `_getenv` at `0x0045E0E4`

Ghidra has no Function object or incoming reference at this entry. The
disassembled `0x36`-byte body takes one pointer at `[EBP+8]`, returns with a
plain `RET`, and therefore has the ordinary one-argument cdecl stack shape.
Its calls are:

- `__SEH_prolog(0x0C, 0x0046C598)` at `0x0045E0EB`;
- lock number 7 at `0x0045E0F2`;
- `__getenv_lk(argument)` at `0x0045E0FF`;
- cleanup at `0x0045E10C`, which unlocks lock 7;
- `__SEH_epilog` at `0x0045E114`.

The wrapper saves the `__getenv_lk` result across unlock and returns it in
EAX. Although its normal path is clear, the entry installs a custom SEH frame
and handler and uses a status slot to coordinate cleanup. A plain lock/call/
unlock C++ wrapper would omit that exceptional cleanup contract. The entry
also has no registered callers or incoming references, so it remains assembly
pending a caller-aware SEH conversion.

## `__i64toa` and `__ui64toa` at `0x0046074C` and `0x0046077D`

Ghidra reports no direct callers or incoming xrefs to either wrapper. Both
have ordinary cdecl signatures with three arguments (an eight-byte value, a
destination pointer, and an `int` radix), return the destination in EAX, and
use plain `RET` so the caller cleans the 16 argument bytes.

Each wrapper calls `FID_conflict:@x64toa@20` at `0x004606DF`. That helper is
not an ordinary C++ callee: its destination arrives in EAX, its four
four-byte arguments are on the stack, and it returns with `RET 16`. It calls
`__aulldvrm` at `0x0045A1B0` to obtain quotient and remainder, emits digits in
reverse order, terminates the buffer, and reverses the digit span. Remainders
below 10 map to `'0'` onward; the others map to lowercase `'a'` onward. The
signed wrapper enables a leading minus only for a negative value in radix 10;
the unsigned wrapper never does.

The two source entries now spell out this shared conversion loop in typed C++
instead of calling the EAX-based helper. Both regions are promoted to semantic
rows while retaining their raw C-linkage names and preserving the prior
manifest records. The shared header now declares the standard cdecl
signatures. The algorithm models the CRT radix domain (2 through 36); buffer
capacity remains the caller’s responsibility, as in the retail routine. No
compiled-byte match was checked.

## `findenv` at `0x00461E83`

Ghidra reports one direct call, from `FUN_00461F31` at `0x00461FF2`. The
function takes the key pointer on the stack, but the key length is a hidden
input in EDI. The caller computes that length from the key and the `=`
delimiter (`0x00461FE6–0x00461FEF`) before the call. The body scans the
environment pointer table at `DAT_00477490`, compares keys with
`__mbsnbicoll`, checks for `=` or NUL after the key, and returns the matching
slot index or a negative insertion index. The EDI input prevents a faithful
standalone standard C++ prototype; it remains assembly until the caller edge
is normalized.

## `copy_environ` at `0x00461ED0`

Ghidra reports one direct call, from `FUN_00461F31` at `0x00461F83`. It has no
stack parameters: the source `char**` is passed in EDI. The caller loads that
pointer from `DAT_00477490` into EDI immediately before the call. The callee
counts the entries, allocates a null-terminated pointer array, duplicates
each string with `__strdup`, and calls `__amsg_exit(9)` if allocation fails;
it returns the new array in EAX (or null when EDI is null). Because the
environment pointer is an implicit EDI input, the apparent no-argument
signature is not a standard C++ ABI and the entry remains assembly.

No build, probe, or test was run during this audit.
