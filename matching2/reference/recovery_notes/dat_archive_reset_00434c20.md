# DatArchive Reset at 0x00434C20

The 10-byte retail wrapper is `push esi; mov esi,ecx; call DatArchive_Close_00434D10; pop esi; ret`. The Close body reads its receiver in ESI, so Reset establishes a private register convention before the call.

`DatArchive::Reset()` now uses the real caller-inclusive native-LTCG cluster
in `../../msvc/layout/ltcg/dat_archive_close_shutdown.json`. Together with Close
and the global shutdown callback, ordinary C++ member calls compile to the
exact retail bytes. The production focused probe reports Reset's full 10-byte
body exact, with no masks or relocation rewrites. See
`archive_cleanup_00434c20_00434d10.md` for hashes and cluster details.
