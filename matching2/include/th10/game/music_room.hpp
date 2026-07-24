#pragma once

// Music room track list load (retail 0x00426520).
#include "th10/util/scalars.hpp"

// --- 0x00426520 --------------------------------------------------------------
int MusicRoom_LoadTrackList(Byte** slot,
                            Byte* (*load_file)(unsigned int* size_out,
                                                     int bank),
                            float sine_value,
                            const Word* accent_table_a,
                            const Word* accent_table_b,
                            const Word* accent_table_c,
                            const Word* accent_table_d);
