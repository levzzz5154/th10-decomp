# Centred VM text formatter at `0x00447BB0`

2026-10-02. `src/game/recovery_centered_text_00447bb0.cpp` owns the 194-byte
formatter. It was already modelled as an unselected anchor of the
`right_aligned_text_00447ae0` cluster; it is now a second selected function of
that cluster and the anchor copy is gone.

The anchor compiled to 195 bytes. Retail keeps the font height byte in AL,
tests it and only then widens it, which needs the same source shape as the
right-aligned sibling: an `unsigned char` copy of the height and a default of
17 replaced when the byte is positive.
