// MSVC-only exact overlay for the main-menu task registration and timer
// reset (retail 0x00422150). The readable semantic reconstruction lives in
// main_menu_dispatch.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
