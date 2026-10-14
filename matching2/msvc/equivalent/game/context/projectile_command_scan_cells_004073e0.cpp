// Context for the 0x00406D90 recovery: the real grid scanner 0x004073E0 with
// the callee models of its byte-exact cluster (the cell-spawner stand-in and
// the panned sound queue), so the /GL pass gives the scanner and the sound
// queue their retail private conventions (pattern in EAX; sound id in EBX).
// The sections are moved past the interpreter's jump tables, so the gate sees
// the calls as leaving the function.
#define code_seg(name) code_seg(".text$zz_004073e0")
#include "../../../layout/ltcg/enemy_grid_scan_004073e0_anchors.cpp"
#include "../../../src/game/enemy_grid_scan.cpp"
#undef code_seg
