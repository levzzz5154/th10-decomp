# CRT OS-handle slots at 0x0045F5D9 and 0x0045F655

Ghidra identifies both complete cdecl functions. The first installs an OS
handle in an unused CRT descriptor; the second is the Visual Studio 2003
`__free_osfhnd` routine and clears an open descriptor's handle. Their table
has 32 entries per block, each 0x24 bytes, with the OS handle at offset
`+0x00` and the open flag at `+0x04`.

Both routines check the descriptor limit at `0x004991E4`. For descriptors
zero through two, when `0x00473074` equals one, they update the Windows
standard handle through the import at `0x004661BC`: values `-10`, `-11`,
and `-12` for input, output, and error. On invalid use they set CRT errno
to 9, clear doserrno, and return `-1`. Successful calls return zero.

The [C++ source](../semantic_candidates/os_handle_slots_0045f5d9.cpp)
shares a typed descriptor entry and the common error path. The manifest
retains both previous assembly records. These routines have ordinary cdecl
arguments, but byte matching remains unverified. No build or byte
comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
