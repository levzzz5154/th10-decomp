#pragma once

#include <cstdint>

// 0x00420B10 - Play the "dummy" cue and latch a progress byte: when bit
// 4 of the retail device flags at 0x00491D78 is set, an extra
// mode-4/value-0 "dummy" call precedes the mode-2 call carrying the
// argument (both through retail 0x0043E460, injected). Finally the byte
// at offset 0x1D892+slot inside the published progress block (retail
// global 0x0047783C) is set to 1. Always returns 0.
uint32_t Sound_PlayDummy(void* context, uint32_t argument, int32_t slot,
                         void (*play)(void* context, const char* name,
                                      int32_t mode, uint32_t value));
