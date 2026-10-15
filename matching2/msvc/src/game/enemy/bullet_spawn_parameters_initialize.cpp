#include "th10/source_views/bullet_99a1d5_0.hpp"
#include "th10/source_views/bullet_99a1d5_1.hpp"
#include "th10/source_views/bullet_99a1d5_2.hpp"
BulletSpawnParameters* __fastcall BulletSpawnParameters_Initialize(
        void* unused, BulletSpawnParameters* parameters) {
    (void)unused;
    for (int index = 0; index < 0x7E; ++index)
        parameters->fields[index] = 0;
    parameters->fields[0x0B] = 0x41000000;
    return parameters;
}
