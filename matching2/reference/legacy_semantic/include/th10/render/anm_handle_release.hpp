#pragma once

#include <cstdint>

#include "th10/render/anm_propagate.hpp"

// 0x00421300 - Release the three tracked overlay animation handles
// (retail globals 0x00477824 / 0x00477828 / 0x0047782C) once the
// owner's phase word (retail owner+0x6FC) reaches 1: each handle that
// resolves (retail 0x004491C0 against the global game state manager)
// gets sprite word 2, propagating to every child when the object is not
// solo; the three globals then clear and the phase advances to 2.
// Independently, the retail latch at 0x00491BEC clears when set.
void Anm_ReleaseTrackedHandles(uint32_t* phase, AnmResolveFn resolve);
