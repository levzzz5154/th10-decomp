extern "C" void __cdecl Sound_ForwardDouble(double value);

// 0x00427C50: widen the sound parameter and pass it to the runtime entry.
void Sound_ForwardFloatAsDouble(float value) {
    Sound_ForwardDouble(static_cast<double>(value));
}
