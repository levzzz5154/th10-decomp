// Compiler context only: the real angle helper 0x00426660, so the pass sees
// the callee's body and gives its callers the private register convention
// (entity in ECX, point in EAX). Never selected from this cluster.
#define code_seg(name) code_seg(".text$00426660_fn")
#include "../../../src/game/entity_angle_from_point_00426660.cpp"
