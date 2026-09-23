# DatArchive Reset at 0x00434C20

The 10-byte retail wrapper is `push esi; mov esi,ecx; call DatArchive_Close_00434D10; pop esi; ret`. The Close body reads its receiver in ESI, so Reset establishes a private register convention before the call.

An earlier isolated C++ candidate called the existing Close symbol from `DatArchive_Reset_00434c20(void* archive)`. Its focused proposal probe emitted 5 bytes rather than the required 10; keeping the pointer in a volatile local produced the same extent. That candidate was rejected.

The current source models Reset and Close as a linked C++ pair. Their LTCG cluster, `archive_cleanup_00434c20_00434d10`, adds a synthetic caller intended to expose the ECX-to-ESI private receiver path. The regions have been promoted to readable C++ candidates, while the old `_asm_DatArchive_Reset_00434c20` and `_asm_DatArchive_Close_00434d10` aliases remain for existing assembly callers. The new pair and its 64-byte context extent have not been built or probed; output and ABI remain unverified.

See `archive_cleanup_00434c20_00434d10.md` for the source and layout details.
