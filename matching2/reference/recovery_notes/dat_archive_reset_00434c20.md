# DatArchive Reset at 0x00434C20

The 10-byte retail wrapper is `push esi; mov esi,ecx; call DatArchive_Close_00434D10; pop esi; ret`. The Close body reads its receiver in ESI, so Reset establishes a private register convention before the call.

An earlier isolated C++ candidate called the existing Close symbol from `DatArchive_Reset_00434c20(void* archive)`. Its focused proposal probe emitted 5 bytes rather than the required 10; keeping the pointer in a volatile local produced the same extent. That candidate was rejected.

The current candidate models Reset and Close as a linked C++ pair using the
shared archive types. Reset passes 256 retail comparisons with the actual
vector-destructor helper executing inside Close. Its Clang body is 7 bytes;
the real Close call still requires private ESI convention recovery. Both
production regions remain assembly. The previously described LTCG layout and
64-byte synthetic context were abandoned proposals, not verified promotions.

See `archive_cleanup_00434c20_00434d10.md` for the source and layout details.
