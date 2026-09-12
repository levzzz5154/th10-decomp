#pragma once

// Float-to-double forwarding shim into the sound layer (retail 0x00427C50).

void Sound_ForwardFloatAsDouble(float value, void (*forward)(double value));
