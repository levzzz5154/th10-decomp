#pragma once

#pragma code_seg()

// ---- compiled bodies for the two callees whose receiver registers no
// declaration can name.  They are placed at their retail addresses by the
// layout, the call above bakes retail's displacements, and export_bodies never
// selects them: the image keeps the maintained assembly regions.

extern "C" int __cdecl entry_free_004524a1(void*);

// 0x00420C90..0x00420D50: the fog and depth-write switches, read through the
// render state's own device pointer at +0x08.  The state stays live across
// 0x00442F50, which is the pressure that earns the receiver EDI in retail.
#pragma code_seg(".text$00a420c90")
