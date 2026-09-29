# Sound-stream command publication at `0x0043DA80`

2026-09-26. The complete 44-byte wrapper is now a tested ordinary C++ candidate
in `semantic_candidates/unassigned_0043da80.cpp`. It reads the stream at manager
`+0x5208`, calls start with priority 0 and flags 1, and maps a missing stream or
negative start status to -1. After nonnegative status it stores the full 32-bit
command at `+0x5210` and returns zero. The field is written after the callback,
so a callback's command-field change is overwritten only on success.

The prior interpretation of inherited ECX as a helper context was incorrect.
In `0x44D440`, the saved word is passed as the restore-output local to
`0x44D300`, which initializes it before start inspects it. The helper's semantic
inputs are stream, priority and flags. The old function-pointer cast has been
removed from the candidate; it now uses the explicit typed start declaration.
See [stream-start evidence and tests](sound_stream_start_0044d440.md).

Retail still takes the manager in ESI and command as a stack argument with
RET 4. The candidate instead uses two explicit stdcall arguments and RET 8.
Retail start takes stream in EAX plus two stack arguments with RET 8; its
candidate uses three explicit stdcall arguments and RET 12. No native ABI
bridge or byte identity is claimed. Clang emits 54 bytes for the wrapper.

The shared stream-start suite passes 222 individual and 73 integrated
comparisons. Wrapper cases cover null streams, HRESULT signs, complete command
values, callback changes to the stream/command fields, and execution through
the actual compiled start/selection/restoration/rewind/volume bodies. Refill is
scripted. Original instruction bytes supply the comparison; live Ghidra access
is currently denied and native MSVC/Wine execution remains unavailable.
Production retains the assembly pending complete-region and whole-executable
verification.
