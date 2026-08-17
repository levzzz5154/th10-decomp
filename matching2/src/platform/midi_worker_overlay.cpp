// MSVC-only exact overlay for the MIDI worker message pump (retail
// 0x0043E3A0). The readable semantic reconstruction lives in
// midi_worker.cpp; this translation unit keeps the overlay free of C++11 so
// the MSVC 7.1 hybrid build can compile it.
