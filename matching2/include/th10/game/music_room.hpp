#pragma once

// Parameter-file load and relocate (retail 0x00426520).
#include "th10/util/scalars.hpp"

// --- 0x00426520 --------------------------------------------------------------
// This was previously called MusicRoom_LoadTrackList, which it is not. Retail's
// signature is sub_426520(const CHAR* filename, int owner), and its only caller
// is 0x004247F0, which selects the filename from a per-character/per-shot table
// (off_476FC0 indexed by DAT_00474C68 and DAT_00474C6C). It has nothing to do
// with the music room, which loads musiccmt.txt through sub_44B360 from its own
// handler at 0x00433EF0 and has no recovered loader of its own.
//
// The body is a faithful recovery: the header's base extents at +0x10/+0x14 are
// scaled by sin(pi/4) into +0x18/+0x1C, then every entry in the 8-byte-stride
// table at +0x110 has its payload offset relocated into a pointer and each
// 0x34-byte record's four accent indices resolved through the lookup tables.
int ParameterFile_LoadAndRelocate(Byte** slot,
                                  Byte* (*load_file)(unsigned int* size_out,
                                                     int bank),
                                  float sine_value,
                                  const Word* accent_table_a,
                                  const Word* accent_table_b,
                                  const Word* accent_table_c,
                                  const Word* accent_table_d);
