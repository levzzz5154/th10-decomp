// MSVC-only exact overlay for the DirectInput joystick property setter
// (retail 0x0044C7E0). The readable semantic reconstruction lives in
// joystick_property.cpp; this translation unit keeps the overlay free of
// C++11 so the MSVC 7.1 hybrid build can compile it.
