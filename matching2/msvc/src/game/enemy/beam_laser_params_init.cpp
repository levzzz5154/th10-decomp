// 0x0040CF40: BeamLaserParams_Construct
#include "th10/source_views/bullet_99a1d5_0.hpp"
#include "th10/source_views/bullet_99a1d5_1.hpp"
#include "th10/source_views/bullet_99a1d5_2.hpp"
BeamLaserParams* __fastcall BeamLaserParams_Construct(
        void* unused, BeamLaserParams* parameters) {
    (void)unused;
    for (int index = 0; index < 0x7E; ++index)
        parameters->fields[index] = 0;
    parameters->fields[0x0B] = 0x41000000;
    return parameters;
}
