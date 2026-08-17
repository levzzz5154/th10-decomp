#include "th10/math/random_vector.hpp"


// 0x00441E50 - Convert the current scalar animation value to the three
// repeated integer lanes consumed by the random-vector branch. The retail
// helper rounds through the x87 control word before narrowing to 32 bits.
void RandomVector_StoreRoundedScalar(int output[3], double scalar) {
    long long rounded = scalar >= 0.0
        ? (long long)(scalar + 0.5)
        : (long long)(scalar - 0.5);
    int value = (int)rounded;
    output[0] = value;
    output[1] = value;
    output[2] = value;
}
