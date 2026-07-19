#pragma once

// Three-component integer result used by the random animation displacement
// path. Retail supplies the scalar through x87 ST(0); the clean form exposes
// it as a double and stores the same rounded low 32-bit value in each lane.
void RandomVector_StoreRoundedScalar(int output[3], double scalar);
