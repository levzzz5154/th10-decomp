// Compiler context for the laser_cut cluster: CutVector::SetPolar (0041F800).
// Retail's body is x87 asm (fsincos) that only touches EAX and ECX, so its
// callers keep values in EDX across the call (TrimCircle keeps the sample index
// there). Without a body in the link the compiler assumes EDX is lost.
// The volatile receiver home gives retail's push ecx/pop ecx (ECX clobbered),
// and taking the address keeps the standard thiscall convention; a plain body
// gets a private convention with the receiver in EAX.
// The production region is src/game/laser/polar_vector.cpp.
#include "types.hpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$f0041f800F")
CutVector* CutVector::SetPolar(float angle,float speed) {
 CutVector* volatile self=this;
 CutVector* out=self;
 out->x=static_cast<float>(cos(angle)*speed);
 out->y=static_cast<float>(sin(angle)*speed);
 return out;
}
#pragma code_seg()
CutVector* (CutVector::*const cut_polar_taken)(float,float) = &CutVector::SetPolar;
