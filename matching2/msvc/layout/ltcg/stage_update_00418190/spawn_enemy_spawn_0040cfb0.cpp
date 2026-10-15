#define data_00491c10 stage_spawn_data_00491c10
#define data_0047770c stage_spawn_data_0047770c
#define data_00474c40 stage_spawn_data_00474c40
#define g_ascii_manager stage_spawn_data_004776e0
#define data_00477704 stage_spawn_data_00477704
#define g_player stage_spawn_data_00477834
#define data_00477838 stage_spawn_data_00477838
#define data_0047783c stage_spawn_data_0047783c
#define data_00476f78 stage_spawn_data_00476f78
#define data_00491fc4 stage_spawn_data_00491fc4
#define data_00491fb8 stage_spawn_data_00491fb8
#define data_00492590 stage_spawn_data_00492590
// 0x0040CFB0..0x0040D1F1: create an enemy.
//
// The record is allocated and bound to the named script entry, takes its
// position, life, score, drop item, two flags and eight script variables from
// the spawn description, and runs its script up to the first wait. Enemies
// flagged for boss-style drops swap the two power item kinds for their large
// forms. The death sound alternates with the creation count, the death effect
// follows the enemy kind the script chose, and the enemy joins the end of the
// manager's list. The switch tables follow the body.
//
// The spawn description arrives in EAX.
#include "enemy_spawn.hpp"
#include <string.h>

#pragma code_seg(".text$0040cfb0_fn")
Enemy_0040cfb0* EnemySpawn_0040cfb0::Create(EnemyManager_0040cfb0* manager, const char* entry) {
    Enemy_0040cfb0* enemy = new Enemy_0040cfb0(entry);

    enemy->data.position = position;
    enemy->data.life = life;
    enemy->data.score = score;
    enemy->data.drop_item = drop_item;
    enemy->data.flags.mirrored = mirrored;
    enemy->difficulty_mask = (unsigned char)(1 << data_00474c40.difficulty);
    memcpy(enemy->data.variables, variables, sizeof(variables));
    enemy->data.invulnerable_timer.Set(2);
    enemy->data.flags.quiet = quiet;
    EnemyData_Start_0040dc80(&enemy->data);

    if (enemy->data.flags.boss_items) {
        int item = enemy->data.drop_item;
        if (item == 1)
            item = 10;
        else if (item == 4)
            item = 11;
        enemy->data.drop_item = item;
    }

    enemy->data.death_sound = (manager->created & 1) + 2;
    enemy->data.death_effect = 0x167;
    if (enemy->data.kind == 1) {
        switch (enemy->data.kind_index) {
        case 0:
        case 20:
        case 49:
            enemy->data.death_effect = 0x167;
            break;
        case 5:
        case 25:
        case 50:
            enemy->data.death_effect = 0x164;
            break;
        case 15:
        case 35:
        case 52:
            enemy->data.death_effect = 0x16D;
            break;
        case 10:
        case 30:
        case 51:
            enemy->data.death_effect = 0x16A;
            break;
        }
    }
    enemy->data.death_callback = 0;

    EnemyNode_0040cfb0* node = &enemy->data.node;
    if (manager->head == 0) {
        manager->head = node;
    } else {
        EnemyNode_0040cfb0* tail = manager->tail;
        if (tail->next != 0) {
            node->next = tail->next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    manager->tail = node;
    ++manager->count;
    ++manager->created;
    return enemy;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
