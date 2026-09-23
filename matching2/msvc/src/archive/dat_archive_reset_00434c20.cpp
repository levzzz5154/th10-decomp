#include "../../layout/ltcg/archive_cleanup_00434c20_00434d10_types.hpp"

// 0x00434C20 receives the archive in ECX. The matching Close body has a
// private ESI receiver in retail, so the native-LTCG pair context keeps this
// call together with Close while the compiler chooses its internal register
// assignment. That register assignment has not been byte-probed yet.
#pragma code_seg(".text$01reset")
__declspec(noinline) void __fastcall DatArchive_Reset(
    DatArchiveCleanup_00434c20_00434d10* archive) {
    DatArchive_Close(archive);
}
#pragma code_seg()
