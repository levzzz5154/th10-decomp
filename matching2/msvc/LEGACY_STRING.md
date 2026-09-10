# Legacy string recovery

[`src/util/legacy_string.cpp`](src/util/legacy_string.cpp) contains the recovered
ordinary C++98 operations on the MSVC 7.1 string representation. The layout in
[`heap.hpp`](include/th10/util/heap.hpp) stores up to 15 characters inline;
capacity values of 16 or more select the owned heap pointer instead.

| Address | Operation | Compiled bytes |
| --- | --- | ---: |
| `0x00438260` | Assign a bounded substring, including self-assignment | 227 |
| `0x00438350` | Assign a NUL-terminated string | 37 |
| `0x00438380` | Reset or return to inline storage | 83 |
| `0x00438420` | Assign a counted range, including interior-pointer input | 234 |
| `0x00438510` | Erase a bounded range and close the gap | 117 |

Previously recovered data access, length, ownership, clear, and termination
helpers now live in the same ordinary C++ translation unit. Allocator and
unrecovered heap operations remain in `src/util/heap.cpp`.

`AssignRange` detects a source pointer inside the current string and delegates
to substring assignment. Self-assignment removes the suffix before the prefix,
preserving overlapping characters. `Erase` clamps an oversized count and uses
`memmove` for the remaining suffix. Invalid offsets call the original range
error routine; impossible lengths call the original length error routine.
Those exception helpers and `Grow` remain assembly-backed dependencies.

The historical name `Reserve` at `0x00438380` was misleading. Its actual
arguments are a release flag followed by the new length, and it returns no
value. `ResetInlineStorage(true, length)` copies an owned buffer into inline
storage before freeing it. The caller must supply a length at most 15 that
fits the existing contents. `ResetInlineStorage(false, 0)` initializes an
unbuilt string without inspecting or releasing an old heap pointer.

The compiler emits all 37 bytes of `Assign`, including its three-byte aligned
loop padding at `0x0043835D`. These bytes previously belonged to a separate
padding region between two assembly fragments. They now belong to one complete
compiler-generated function section; no hand-authored padding is selected for
that function. The original disassembler's body ranges remain reference claims
in the ownership ledger.

`make test` exercises the maintained C++ against `std::string` results and
scripted allocation/exception boundaries. It covers self-assignment, overlap,
embedded NUL characters, empty ranges, count clamping, errors, and release
ordering. The scripted growth boundary does not establish recovery of `Grow`.
`make verify` separately compiles with MSVC 13.10.6030 and checks every linked
instruction, address operand, and byte of the complete executable.
