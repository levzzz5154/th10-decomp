#include "th10/archive/dat_archive_types.hpp"

// Static archive cleanup callback registered by the CRT. Its ordinary C++
// call to DatArchive::Close lets LTCG supply the private ESI receiver.
#pragma code_seg(".text$03global")
extern "C" __declspec(noinline) void __cdecl CloseGlobalArchive_00465a60() {
    reinterpret_cast<DatArchive*>(0x00497990)->Close();
}
#pragma code_seg()
