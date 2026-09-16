# DatArchive Reset at 0x00434C20

The isolated 10-byte retail wrapper is `push esi; mov esi,ecx; call DatArchive_Close_00434D10; pop esi; ret`. The Close body reads its receiver in ESI, so this wrapper establishes a private register convention before the call.

A bounded ordinary C++ candidate called the existing Close symbol from `DatArchive_Reset_00434c20(void* archive)`. The focused proposal probe rejected it: compiler output occupied 5 bytes rather than the required 10. Keeping `archive` in a volatile local still emitted a 5-byte function and failed the same extent gate. No semantic region was promoted. The maintained assembly and `regions.json` are unchanged.

Recovery needs a linked semantic Close implementation and caller that makes the ESI receiver convention visible to LTCG, or another evidence-backed way to recover that private call ABI. Repeating an isolated C++ call to the raw Close symbol cannot carry the receiver in ESI.
