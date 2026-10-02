// 0x0040E5F0: what a dying enemy leaves behind.
//
// It plays its death sound panned to its position, starts its death burst,
// throws its main item and scatters the rest, and holds the gauge for ten
// frames. The enemy arrives on the stack.
#include "th10/game/enemy_death_release_0040e5f0.hpp"
#include "th10/game/player_update_collision.hpp"
struct Vector3;

void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** out, int index, const Vector3* position);

#pragma code_seg(".text$079k_death")
int __stdcall Enemy_ReleaseOnDeath_0040e5f0(Enemy_0040e5f0* enemy) {
    if (enemy->death_sound >= 0)
        data_00492590.QueuePan(enemy->death_sound, enemy->position.position[0]);
    if (enemy->death_script >= 0) {
        void* burst;
        ItemAnimation_CreateOffset_00448db0(
            data_00477704->animation_files[enemy->death_file], &burst,
            enemy->death_script, (const Vector3*)&enemy->position);
    }
    DropSource_0040c9a0* source = &enemy->position;
    ItemDrops_0040c9a0* drops = &enemy->drops;
    if (drops->main_item > 0)
        data_00477818->Spawn(source->position, drops->main_item, -1, -1.5707964f, 2.2f);
    source->ScatterDrops(drops);
    drops->main_item = 0;
    data_00474c40.AdvanceGaugeTimer(10);
    return 1;
}
#pragma code_seg()
