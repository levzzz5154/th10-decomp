// Semantic candidate for 0x00434C20..0x00434C29 (10 bytes).
// The ECX receiver matches retail. Its call to the ESI-based Close entry
// still requires native LTCG recovery before exact-build integration.
#include "dat_archive_types.hpp"

extern "C" void __fastcall DatArchive_Reset_00434c20(DatArchive* archive) {
    DatArchive_Close_00434d10(archive);
}
