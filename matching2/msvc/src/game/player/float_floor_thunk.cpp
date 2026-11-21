// 0x00427C50: Math_FloorFloat
extern "C" void __cdecl crt_floor_double(double value);

// 0x00427C50 widens a float for the CRT floor routine. Its retail callers
// consume the x87 ST(0) result as a float, so keep the source return void to
// model that register side channel without changing the wrapper's code shape.
void Math_FloorFloat(float value) {
    crt_floor_double(static_cast<double>(value));
}
