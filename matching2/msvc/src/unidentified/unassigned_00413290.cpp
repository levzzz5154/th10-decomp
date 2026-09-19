// 0x00413290: one signed random value scaled by the retail constant at 0x470B18.
// The receiver in ECX is handed straight to the generator at 0x44BB90.

struct RngState;

struct ObjectAccessor_00413290 {
    __declspec(noinline) float LoadValue() const;
};

float __fastcall Rng_NextFloatSigned(RngState* state);
extern "C" float data_00470b18;

float ObjectAccessor_00413290::LoadValue() const {
    return Rng_NextFloatSigned((RngState*)this) * data_00470b18;
}
