#include "th10/archive/dat_archive_types.hpp"

// 0x00465A60: atexit destructor of the global archive at 0x00497990. Its ordinary C++
// call to DatArchive::Close lets LTCG supply the private ESI receiver.
#pragma code_seg(".text$03global")
extern "C" __declspec(noinline) void __cdecl StaticExit_Archive() {
    reinterpret_cast<DatArchive*>(0x00497990)->Close();
}
#pragma code_seg()
