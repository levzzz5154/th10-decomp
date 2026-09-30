#include "th10/archive/dat_archive_types.hpp"

// Keep the public ECX receiver while LTCG passes this archive to Close in ESI.
#pragma code_seg(".text$01reset")
__declspec(noinline) void DatArchive::Reset() {
    Close();
}
#pragma code_seg()
