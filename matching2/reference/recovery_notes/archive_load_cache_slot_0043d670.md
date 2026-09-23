# Archive-load cache slot helper at `0x0043D670`

## Recovered behavior

Ghidra identifies a 32-byte routine spanning `0x0043D670..0x0043D68F`. Its
direct call at `0x0043D674` reaches `0x0044B360`; after the call, the returned
pointer is stored at `owner + 0x1F84`. The helper stores null on failure and
returns `0` for a non-null pointer or `-1` for null. The final bytes are
`C2 04 00` (`RET 4`). Ghidra reports no incoming callers or xrefs to this
entry.

The callee's Ghidra decompilation exposes an implicit `in_EAX` filename. The
two zero values pushed by this routine are its size-output pointer and
`fromDisk` flag. A zero flag selects the packed-archive lookup/load path; the
loaded buffer is returned to the caller.

The readable source model is in
`msvc/src/unidentified/unassigned_0043d670.cpp`. It calls
`Archive_LoadFile(file_name, 0, 0)`, stores the resulting pointer at byte
offset `0x1F84`, and returns the retail success/failure values.

## ABI and exactness

At retail entry, EAX holds the filename and `[ESP+4]` holds the owner. The
routine pushes two zero arguments for `0x0044B360`; that callee cleans those
arguments with `RET 8`. The wrapper then returns with `RET 4`, cleaning the
owner argument. There are no direct incoming xrefs in Ghidra, so a caller that
supplies the EAX filename was not recovered in this pass.

The ordinary C++ model makes the filename and owner explicit parameters and
uses the shared `Archive_LoadFile` interface. That signature does not by
itself express the retail EAX filename / stack owner split, nor guarantee the
helper's EAX-plus-stack calling sequence. The body is behaviorally readable,
but its byte extent and custom ABI remain unverified. The manifest now
classifies this span as semantic and preserves its former assembly record. No
build, probe, or test was run.
