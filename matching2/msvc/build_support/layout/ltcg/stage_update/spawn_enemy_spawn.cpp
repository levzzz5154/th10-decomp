#define g_sprt_ctrl stage_spawn_g_sprt_ctrl
#define g_front stage_spawn_g_front
#define g_globals stage_spawn_data_00474c40
#define g_ascii_manager stage_spawn_data_004776e0
#define g_enemy_ctrl stage_spawn_g_enemy_ctrl
#define g_player stage_spawn_data_00477834
#define g_replay stage_spawn_data_00477838
#define g_score stage_spawn_data_0047783c
#define g_game_speed stage_spawn_data_00476f78
#define g_stage_flags stage_spawn_data_00491fc4
#define g_main_state stage_spawn_data_00491fb8
#define g_sound_manager stage_spawn_data_00492590
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
Enemy4* EnemySpawn2::Create(EnemyCtrlSpawnView* manager, const char* entry) {
    Enemy4* enemy = new Enemy4(entry);

    enemy->data.position = position;
    enemy->data.life = life;
    enemy->data.score = score;
    enemy->data.drop_item = drop_item;
    enemy->data.flags.mirrored = mirrored;
    enemy->difficulty_mask = (unsigned char)(1 << g_globals.difficulty);
    memcpy(enemy->data.variables, variables, sizeof(variables));
    enemy->data.invulnerable_timer.Set(2);
    enemy->data.flags.quiet = quiet;
    EnemyData_Start(&enemy->data);

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

    EnemyNode2* node = &enemy->data.node;
    if (manager->head == 0) {
        manager->head = node;
    } else {
        EnemyNode2* tail = manager->tail;
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
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
