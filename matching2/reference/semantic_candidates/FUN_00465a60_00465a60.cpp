#include "../../layout/ltcg/archive_cleanup_00434c20_00434d10_types.hpp"

// 0x00465A60 is the no-argument cleanup thunk for the global DAT archive.
// The retail code supplied the receiver to CloseDatArchive through ESI;
// DatArchive_Close models that same cleanup with an explicit archive pointer.
extern "C" void __cdecl asm_FUN_00465a60_00465a60() {
    DatArchive_Close(
        reinterpret_cast<DatArchiveCleanup_00434c20_00434d10*>(0x00497990UL));
}
