# Sound-buffer playing check at 0x0044D640

Ghidra identifies the complete 88-byte body through `0x0044D697` and
reports no incoming references. Retail receives the owner in EDI. The owner
has a buffer table at offset `+0x04` and its count at `+0x10`. For every
nonnull buffer, it calls virtual method `+0x24` with an output status word,
then combines bit zero of those words. It ignores the method's return code
and returns zero when the table is absent.

The surrounding recovered DirectSound wrappers use the same table layout,
and virtual method `+0x48` is their Stop operation. The local Wine
`/usr/include/wine/windows/dsound.h` declaration lists `GetStatus` as the
tenth method (offset `+0x24` on x86) and defines `DSBSTATUS_PLAYING` as bit
zero. The
[shared sound-buffer type](../../msvc/include/th10/platform/sound_buffer.hpp)
now names method `+0x24` as `get_status` and offset `+0x10` as
`buffer_count`. The [C++ source](../semantic_candidates/sound_buffer_any_playing_0044d640.cpp)
expresses the loop and its status-bit aggregation directly. The manifest
retains the previous assembly record.

The source uses a cdecl parameter for the retail EDI input. Byte matching
is unverified; no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
