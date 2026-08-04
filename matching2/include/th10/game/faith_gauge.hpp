#pragma once

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

// 0x00418930 - Add to a faith gauge level (retail int16 at +0x08 of the
// gauge record). A level already above 99 rejects the add (returns
// false). Otherwise the amount accumulates; crossing 100 clamps to 100
// and swaps the celebration animation on the front UI manager
// (published at retail 0x0047770C): the old handle at +0x9E18 is
// released (retail 0x004492A0 against the global game state manager),
// cleared, and replaced by a fresh spawn (retail 0x00448D00) of script
// 0x49 on layer 0xF from the "front.anm" resource at +0x9EC8. Returns
// whether the add crossed a multiple-of-20 boundary (retail division
// comparison on the final level).
bool FaithGauge_Add(int16_t* level, int16_t amount, void* context,
                    void (*release_anm)(void* context, uint32_t handle),
                    const uint32_t* (*spawn_anm)(uint32_t resource,
                                                 int32_t script,
                                                 int32_t layer));
