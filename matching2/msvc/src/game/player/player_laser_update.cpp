// 0x00428C20..0x00428C9C: PlayerLaser_Update (ShotDefinition::on_update[2]).
// Pins an active MarisaB player laser (EDX = PlayerBullet*) to its firing
// option's world position (ECX = Player*; options[0] is at +0x32A0, stride
// 0x98, position at +0x3C, and 1-based option index simplifies to +0x3244 + 152*slot),
// then adds the shot offset and compensates for velocity.
struct Vector3 {
    float x;
    float y;
    float z;
};

struct PlayerLaserDef {          // state->source, at state + 0x58
    char pad_000[4];
    float value;                  // +0x04
    float maximum;                // +0x08
    char pad_00c[0x1C - 0x0C];
    signed char slot;             // +0x1C
};

struct PlayerLaserBullet {
    char pad_000[0x14];
    Vector3 position;             // +0x14
    float offset_x;               // +0x20
    float offset_y;               // +0x24
    char pad_028[0x58 - 0x28];
    PlayerLaserDef* source;      // +0x58
};

int __fastcall PlayerLaser_Update(int* manager, PlayerLaserBullet* state) {
    Vector3 position;
    PlayerLaserDef* source = state->source;
    int* entry = (int*)((char*)manager + 152 * source->slot + 0x3244);
    Vector3* dst = &state->position;

    position.x = (float)entry[0] * 0.01f;
    position.y = (float)entry[1] * 0.01f;
    position.z = 0.0f;
    *dst = position;
    state->position.x = source->value - state->offset_x + state->position.x;
    state->position.y = state->source->maximum - state->offset_y + state->position.y;
    return 0;
}

