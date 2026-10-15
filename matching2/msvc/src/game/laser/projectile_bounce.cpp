#include "th10/game/laser_spawn_0041c510.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" float data_00470b40, data_00470b3c, data_00470b04, data_00470b38, data_00470b18;
extern "C" float __stdcall Angle_Normalize_0044bc70(float value);

struct BounceVector2 {
    float x, y;
    void SetPolar(float angle, float speed);
};
// Parameters passed to the line laser initializer: 0x1DC bytes at +0x424.
struct BounceSpawnParameters : LaserSpawnParameters_0041c510 {
    Vector3 position;
    float angle;
    float reserved_434;
    float speed;                       // +0x438
    unsigned char reserved_43c[0x444 - 0x43c];
    float width;
    unsigned char reserved_448[0x600 - 0x448];
};
struct LineLaserBounce_0041cfd0 {
    virtual void Slot00() = 0;
    virtual void Slot01() = 0;
    virtual void Slot02() = 0;
    virtual void Slot03() = 0;
    virtual void Slot04() = 0;
    virtual void Slot05() = 0;
    virtual void Slot06() = 0;
    virtual void Slot07() = 0;
    virtual void Slot08() = 0;
    virtual void Slot09() = 0;
    virtual void Slot10() = 0;
    virtual void Slot11() = 0;
    virtual void Slot12() = 0;
    virtual void Slot13() = 0;
    virtual void Slot14() = 0;
    virtual void Bounce();
    unsigned char reserved_004[0x24 - 4];
    Vector3 position;
    unsigned char reserved_030[0x3c - 0x30];
    float angle;
    float speed;
    unsigned char reserved_044[0x13c - 0x44];
    float width;
    unsigned char reserved_140[0x404 - 0x140];
    unsigned int flags;
    int reserved_408;
    int sound_id;
    unsigned char reserved_410[0x424 - 0x410];
    BounceSpawnParameters parameters;  // +0x424
    LaserSprite_0041c510 beam;          // +0x600
    LaserSprite_0041c510 flare;         // +0x9AC
};
typedef char BounceParametersSize[sizeof(BounceSpawnParameters) == 0x1DC ? 1 : -1];
typedef char BounceLineLaserSize[sizeof(LineLaserBounce_0041cfd0) == 0xD58 ? 1 : -1];
typedef char BouncePositionOffset[offsetof(LineLaserBounce_0041cfd0, position) == 0x24 ? 1 : -1];
typedef char BounceFlagsOffset[offsetof(LineLaserBounce_0041cfd0, flags) == 0x404 ? 1 : -1];
typedef char BounceParametersOffset[offsetof(LineLaserBounce_0041cfd0, parameters) == 0x424 ? 1 : -1];
// 0x0041CFD0: virtual slot 15 of the line-laser table at 0x0046DA60.
// Test the next position before reflecting. The inclusive outer test can
// queue the sound when merely touching a lower boundary; reflection uses
// strict lower bounds. Either reflection clears the pending bounce flags.
#pragma code_seg(".text$a09bounce")
void LineLaserBounce_0041cfd0::Bounce() {
    Vector3 next;
    reinterpret_cast<BounceVector2*>(&next)->SetPolar(angle, speed);
    next.x += position.x;
    next.z = 0;
    next.y += position.y;
    if (next.x <= data_00470b40 || next.x >= data_00470b3c ||
        next.y <= data_00470b04 || next.y >= data_00470b38) {
        int reflected = 0;
        if (sound_id >= 0)
            g_sound_manager.Queue(sound_id, 0);
        if (next.x < data_00470b40 || next.x >= data_00470b3c) {
            parameters.position = next;
            parameters.angle = Angle_Normalize_0044bc70(-angle - data_00470b18);
            parameters.width = width;
            reflected = 1;
            parameters.SpawnIn(g_laser_manager, 0);
        }
        if (!(flags & 0x08000000) &&
            (next.y < data_00470b04 ||
             (next.y >= data_00470b38 && (flags & 0x400)))) {
            parameters.angle = -angle;
            parameters.position = next;
            parameters.width = width;
            parameters.SpawnIn(g_laser_manager, 0);
        } else if (!reflected)
            return;
        flags &= ~0x08000c00u;
    }
}
#pragma code_seg()
