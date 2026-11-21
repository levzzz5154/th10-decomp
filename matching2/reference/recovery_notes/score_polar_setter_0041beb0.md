# Polar setter at `0x0041BEB0`

The [maintained setter](../../msvc/src/game/item/polar_vector.cpp) is
`ItemPolarVelocity2::SetPolar(float angle, float speed)`. Its **30 native
bytes match retail**, without inline assembly. It writes cosine times speed
to `x` and sine times speed to `y`, leaves depth velocity alone, and returns
the destination in EAX.

The receiver arrives in ECX; `ret 8` removes the two stack arguments. The
four call sites are `0x0041BB9D` and `0x0041BD99` in the allocator and
`0x0041B23F` and `0x0041B2C9` in the update.

The [shared C++ implementation](../../msvc/include/th10/math/scaled_polar.hpp)
uses the pinned GCC `sincosl` builtin. Each x87 result is scaled before its
component is stored as a float. The unselected MSVC caller context uses
separate cosine and sine expressions to model register and memory effects;
it is not the setter packaged in the executable.
