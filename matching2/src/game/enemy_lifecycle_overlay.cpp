// MSVC-only exact overlay for the enemy death sweep and timer interpolation
// (retail 0x0040E6A0). The readable semantic reconstruction lives in
// enemy_lifecycle.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
