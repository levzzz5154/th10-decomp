// MSVC-only exact overlay for the main game-thread constructor (retail
// 0x00401000). The readable semantic reconstruction lives in
// game_thread.cpp for host builds; this translation unit keeps the overlay
// free of C++11 so the MSVC 7.1 hybrid build can compile it.
