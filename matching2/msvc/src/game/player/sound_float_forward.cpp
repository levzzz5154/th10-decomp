extern "C" void __cdecl Sound_ForwardDouble(double value);

// 0x00427C50 widens a float for the CRT floor routine. Its retail callers
// consume the x87 ST(0) result as a float, so keep the source return void to
// model that register side channel without changing the wrapper's code shape.
void Sound_ForwardFloatAsDouble(float value) {
    Sound_ForwardDouble(static_cast<double>(value));
}
